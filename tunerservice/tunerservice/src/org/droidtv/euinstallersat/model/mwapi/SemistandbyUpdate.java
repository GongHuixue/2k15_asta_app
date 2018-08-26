package org.droidtv.euinstallersat.model.mwapi;

import java.util.Observable;
import java.util.Observer;
import java.util.Calendar;

import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.service.InstallerTVSettings;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.tvinput.ILogoAssociationControl.ILogoAssociationListener;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl.ITvSemiStandbyCallback;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.tv.context.TvIntent;


import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.util.Log;

public class SemistandbyUpdate implements Observer {

	private static final String TAG = SemistandbyUpdate.class.getName();
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private NotificationHandler ntf = NotificationHandler.getInstance();
	private Context mContext;
	private SemistandbyUpdate thisInstance;
	private ILogoAssociationControl logoAssoInt = null;
	private ListenerImpl listener = new ListenerImpl();
	private ITvSemiStandbyControl ssbyIntf = null;

	private final static int SATALARM_HOUR = 4;

	private boolean ifInstallationInProgress = false;
	
	public SemistandbyUpdate(Context ctx) {
		Log.d(TAG, "Semistandby update ");
		mContext = ctx;
		thisInstance = this;
		
		Intent i = new Intent(TvIntent.ACTION_SERVICE_SBYSERVICE);
		(mContext).bindService(i, mssbyConnection,
				Context.BIND_AUTO_CREATE);
	}
	
	private void broadcastIntent(String intentName){
		Log.d(TAG,"broadcastIntent " + intentName);
		Intent intent = new Intent(intentName);
		intent.putExtra("InstallMode", "Background");
		mContext.sendStickyBroadcast(intent);
	}

	@Override
	public void update(Observable observable, Object data) {

		final int eventID = ((NotificationInfoObject) data).actionID;
		switch (eventID) {

			case EventIDs.EVENT_INST_COMPLETED:
				Log.d(TAG, "EVENT_INST_COMPLETED ");
				Log.d(TAG,"LNB Update ");
				nwrap.UpdateLnbTypeOnSemistandbyUpdate();
				nwrap.commitDatabaseToTvProvider(nwrap.INSTALL_TYPE_UPDATE);
				ifInstallationInProgress = false;
				break;
				
			case EventIDs.EVENT_INS_STOPPED:
				Log.d(TAG, "EVENT_INS_STOPPED ");
				ntf.unRegisterForNotification(thisInstance);
				broadcastIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_COMPLETE");
				nwrap.setApplicationState(NativeAPIWrapper.STATE_IDLE);
				nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
				/*Notify SSby Service*/
				ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
				ifInstallationInProgress = false;
				break;
			
			case EventIDs.EVENT_INST_STARTED:
				Log.d(TAG, "EVENT_INST_STARTED ");
				broadcastIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
				break;
			
			case EventIDs.INSTALLATION_FAILED:
				Log.d(TAG, "EVENT_INST_FAILED ");
				nwrap.setApplicationState(NativeAPIWrapper.STATE_IDLE);	
				nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
				ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
				break;
				
			case EventIDs.NATIVELAYER_INIT_DONE:
				Log.d(TAG, "NATIVELAYER_INIT_DONE ");
				nwrap.updateInstllation();
				ifInstallationInProgress = true;
				break;
				
			case EventIDs.COMMIT_TVPROVIDER_FINISHED:
				Log.d(TAG, "COMMIT_TVPROVIDER_FINISHED  ");
				// start logo association & wait for the callback
				startLogoAssiciation();
				break;

		}
	}
	

	private void startLogoAssiciation() {
		Log.d(TAG, "startLogoAssiciation");
		Intent i = new Intent("org.droidtv.tvcontentprovider.LogoService");
		(mContext).bindService(i, mConnection,
				Context.BIND_AUTO_CREATE);
	}


	public long getNextAlarmTimeMSecs() {
		long timeinmsecs = Long.MAX_VALUE;
		
		Calendar alarmTime = Calendar.getInstance();
		String mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		Log.d(TAG,"current time is " + mydate);
		
		
		int currenthour = alarmTime.get(Calendar.HOUR_OF_DAY);
		if(currenthour>=SATALARM_HOUR) {
			alarmTime.add(Calendar.DAY_OF_MONTH, 1);
		}
				
		alarmTime.set(Calendar.HOUR_OF_DAY, SATALARM_HOUR);
		alarmTime.set(Calendar.MINUTE, 0);
		alarmTime.set(Calendar.SECOND, 0);
		
		mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		Log.d(TAG,"Alarm time is " + mydate);
		
		timeinmsecs = alarmTime.getTimeInMillis();
		Log.d(TAG,"Alarm time is " + mydate + " timeinmsecs" + timeinmsecs);
		
		return timeinmsecs;
	}

	
	private ITvSemiStandbyCallback ssbyListner = new ITvSemiStandbyCallback(){
	
			@Override
			public void onStartAction() {
				Log.d(TAG,"onStartAction ");
				if((nwrap.getFromPowerState() == PowerStates.POWER_STATE_FULL_SYSTEM_START) && (nwrap.getToPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY)){
					Log.d(TAG,"System going to Semistandby state ");
					if( nwrap.isSemiStandbyUpdateRequiredOnShutdown()){
						Log.d(TAG,"Fransat update is going on ... wait for the update to be completed ");
						nwrap.setApplicationState(NativeAPIWrapper.STATE_SERVICE);
						ntf.registerForNotification(thisInstance);						
						nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
					}
					else{
						Log.d(TAG,"update installation is not required on Shutdown");
						ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
					}
				}
				else if((nwrap.getFromPowerState() == PowerStates.POWER_STATE_DDR_STANDBY) && (nwrap.getToPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY)){
					
					Log.d(TAG,"System woke up from DDR Standby ");
					if( nwrap.isSemiStandbyUpdateRequiredOnAlarmWakeup()){
						nwrap.setApplicationState(NativeAPIWrapper.STATE_SERVICE);
						ntf.registerForNotification(thisInstance);
						// initialize for session creation. Callback sends EVENT_INST_ONPREPAREDTV
						nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
						
					}
					else{
						Log.d(TAG,"update installation is not required on Wakeup");
						ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
					}
					
				}
				else{
					Log.d(TAG,"Power state did not match");
					ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
				}
			
			}
			@Override
			public void onStopAction() {
				Log.d(TAG,"onStopAction ");
				nwrap.stopBckInstallation();
				if(ifInstallationInProgress == false){
					Log.d(TAG,"Installation is not in progress, close TIF session set actioncompleted ");
					ntf.unRegisterForNotification(thisInstance);
					nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
					// /*Notify SSby Service*/
					// ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
				}
				//KT --start-- setActionCompleted here,
				//[TF415PHIEUMTK66-1207] Tv does not enter green powermode after overnight test
				//#13 log , client stop but seems not set completed, next time run semi will not run and freeze
				/*Notify SSby Service*/
				ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
				//KT --end--
				nwrap.setApplicationState(NativeAPIWrapper.STATE_IDLE);	
			}
			@Override
			public long onGetNextAlarm(){ 
				Log.d(TAG,"onGetNextAlarm ");
				return getNextAlarmTimeMSecs();
			}
	
		};

	
	private ServiceConnection mssbyConnection = new ServiceConnection() {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG, "onServiceConnected for ssbyservice");

			ssbyIntf = ITvSemiStandbyControl.Instance.asInterface(service);
			if (ssbyIntf != null) {
				Log.d(TAG, "ssbyIntf is not null");
				// Register Action
				ssbyIntf.registerSemiStandbyAction(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION,ssbyListner);
				//Set Alarm
				Log.d(TAG, "Setting Alaram");
				ssbyIntf.setAlarmForSemiStandbyAction(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION, getNextAlarmTimeMSecs());
				
			} else {
				Log.d(TAG, "NULL ssbyIntf found");
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d(TAG, "onServiceDisconnected for ssbyservice");
			// TODO Auto-generated method
			// stub

		}
	};

	private ServiceConnection mConnection = new ServiceConnection() {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG, "ILogoAssociationControl called");

			logoAssoInt = ILogoAssociationControl.Instance.asInterface(service);
			if (logoAssoInt != null) {
				Log.d(TAG, "logoAssoInt is not null");
				logoAssoInt.registerListenerCallback(listener);
				logoAssoInt.StartLogoAssociation(ILogoAssociationControl.MEDIUM_SATELLITE);


			} else {
				Log.d(TAG, "NULL logoAssoInt found");
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			// TODO Auto-generated method
			// stub

		}
	};

	public class ListenerImpl extends ILogoAssociationListener {

		@Override
		public void onLogoAssociationStateChanged(int state) {
			Log.d(TAG, "onLogoAssociationStateChanged called with State:"
					+ state);

			if (state == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_COMPLETE) {
				Log.d(TAG, "Logo Association complete received");

				// Navigating to next screen
				try {
					(mContext).unbindService(mConnection);
				} catch (Exception ex) {
					Log.d(TAG,
							"Exception caught while unbinding service org.droidtv.tvcontentprovider.LogoService");
				}

				ntf.unRegisterForNotification(thisInstance);
				broadcastIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_COMPLETE");
				nwrap.setApplicationState(NativeAPIWrapper.STATE_IDLE);
				nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
				/*Notify SSby Service*/
				ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
				
			}
			
		}
	}

}
