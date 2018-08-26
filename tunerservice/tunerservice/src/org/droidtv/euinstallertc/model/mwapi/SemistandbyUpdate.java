package org.droidtv.euinstallertc.model.mwapi;

import java.util.Calendar;
import java.util.Observable;
import java.util.Observer;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.ApplicationState;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DVBTOrDVBC;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.service.EuInstallerService;
import org.droidtv.euinstallertc.service.LogoAssociationHandler.ILogoAssociationListner;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl.ITvSemiStandbyCallback;

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
	private ITvSemiStandbyControl ssbyIntf = null;
	private EuInstallerService eusvc = null;
	private boolean ifMajorVersionUpdate = false;
    private int year, month, day;
    private int hour,minute;
    private long camscheduletimeinmsecs = 0,currenttimeinmillisecs = 0;
	final Calendar alarmTime = Calendar.getInstance();
	private boolean ifInstallationInProgress = false;


	private final static int TCALARM_HOUR = 4;
	final int MIN_TOL = 10; 

	
	public SemistandbyUpdate(Context ctx) {
		Log.d(TAG, "Semistandby update ");
		mContext = ctx;
		thisInstance = this;
		
		Intent i = new Intent(TvIntent.ACTION_SERVICE_SBYSERVICE);
		(mContext).bindService(i, mssbyConnection,
				Context.BIND_AUTO_CREATE);

	}
	
	public void registerServiceInstance(EuInstallerService argeusvc){
		eusvc = argeusvc;
	}
	
	private void broadcastIntent(String intentName){
		Log.d(TAG,"broadcastIntent " + intentName);
		Intent intent = new Intent(intentName);
		intent.putExtra("InstallMode", "Background");

		if (DVBTOrDVBC.DVBC == nwrap.getSelectedDVBTOrDVBCFromTVS()){
			intent.putExtra("InstallMedium", "Cable");
		}else{
			intent.putExtra("InstallMedium", "Terrestrial");

		}
		mContext.sendStickyBroadcast(intent);
	}
	
	private void broadcastIntentSemistandby(String intentName) {
		Log.d(TAG,"broadcastIntentSemistandby " + intentName);
		Intent intent = new Intent(intentName);
		intent.putExtra("InstallMode", "Update");

		if (DVBTOrDVBC.DVBC == nwrap.getSelectedDVBTOrDVBCFromTVS()){
			intent.putExtra("InstallMedium", "Cable");
		}else{
			intent.putExtra("InstallMedium", "Terrestrial");

		}
		mContext.sendStickyBroadcast(intent);
	}
	
	

	@Override
	public void update(Observable observable, Object data) {

		final int eventID = ((NotificationInfoObject) data).actionID;

		switch (eventID) {
		case EventIDs.EVENT_LCN_CONFLICT:
			// no user intervention
			Log.d(TAG, "EVENT_LCN_CONFLICT ");
			nwrap.stopBckInstallation();
			nwrap.networkChangeDetected(true);
			ntf.unregisterForNotification(thisInstance);
			nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
			ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);	
			broadcastIntentSemistandby("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
			break;
		case  EventIDs.EVENT_INST_STARTED:
			Log.d(TAG, "EVENT_INST_STARTED ");
			broadcastIntentSemistandby("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
			break;

		case EventIDs.EVENT_INST_STOPPED:
				ntf.unregisterForNotification(thisInstance);
				nwrap.UnregisterTuningInstance();
				nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
				ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
				broadcastIntentSemistandby("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
				ifInstallationInProgress = false;
			break;
		case EventIDs.EVENT_MAJORVERSION_UPDATE:
			Log.d(TAG, "EventIDs.EVENT_MAJORVERSION_UPDATE");
			ifMajorVersionUpdate = true;
			break;
		case EventIDs.EVENT_INST_COMPLETED:
			Log.d(TAG, "EVENT_INST_COMPLETED ");
			ifInstallationInProgress = false;
			// check if channels added /removed
			if (nwrap.mLcnConflictCountry() == true) {
				if ((nwrap.getDigitalChannelCount() > 0) || (nwrap.getDigitalChannelsRemoved() > 0)) {
					Log.d(TAG, "Sweden Channels Updated");
					nwrap.channelsUpdated(true);
				}
			}
			else if (true == ifMajorVersionUpdate) {
				Log.d(TAG, "Channels Updated");
				nwrap.channelsUpdated(true);
				ifMajorVersionUpdate = false;
			}
			
			// reset pending network update flag
			nwrap.networkChangeDetected(false);

			nwrap.commitDatabaseToTvProvider(false);
			break;
		case EventIDs.EVENT_INST_ONPREPAREDTV:
			Log.d(TAG, "EVENT_INST_ONPREPAREDTV ");
			if(!ifInstallationInProgress) {
				nwrap.initInstallSettings();
			
				if(nwrap.isOpsemistandbyInstallationtriggered() == true)
				{
					Log.d(TAG, "Triggering CAM installation ");
					nwrap.startInstallation(NativeAPIEnums.InstallationMode.CAM_INSTALLATION);
					//ifInstallationInProgress = true;
				} else {
					ifMajorVersionUpdate = false;
					nwrap.startInstallation(NativeAPIEnums.InstallationMode.BACKGROUND_UPDATE);
					ifInstallationInProgress = true;
				}
			}
			break;
		case EventIDs.EVENT_UNREGISTER_SERVICE:
			Log.d(TAG, "EVENT_UNREGISTER_SERVICE ");
			ntf.unregisterForNotification(thisInstance);
			break;
		case EventIDs.EVENT_CAM_SCHEDULE_UPDATE_TIME:
			if (eusvc != null) {
				eusvc.camSchedulUpdateTime(Integer.parseInt((String) ((NotificationInfoObject) data).message));
			}
			break;
		case EventIDs.EVENT_CAM_SCHEDULE_UPDATE_DATE:
			if (eusvc != null) {
				eusvc.camscheduleUpdateDate(Integer.parseInt((String) ((NotificationInfoObject) data).message));
			}
			break;
		case EventIDs.EVENT_NETWORK_UPDATE_DETECTED:
			Log.d(TAG, "EVENT_NETWORK_UPDATE_DETECTED ");
 			break;
		case EventIDs.EVENT_DIGIT_CH_FOUND:
			Log.d(TAG, "EventIDs.EVENT_DIGIT_CH_FOUND");
			// query mw for digital channel count
			// update digit channels count
			nwrap.getDigitalChannelCount();
			break;
		case EventIDs.EVENT_DIGIT_CH_ADDED:
			Log.d(TAG, "EventIDs.EVENT_DIGIT_CH_ADDED");
			nwrap.getDigitalChannelCount();
			break;
		case EventIDs.EVENT_DIGIT_CH_REMOVED:
			Log.d(TAG, "EventIDs.EVENT_DIGIT_CH_REMOVED");
			nwrap.getDigitalChannelsRemoved();
			break;
		case EventIDs.EVENT_COMMIT_FINISHED:
			Log.d(TAG, "EVENT_COMMIT_FINISHED  ");
			broadcastIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
			// start logo association & wait for the callback
			nwrap.startLogoAssociation(nwrap.getSelectedDVBTOrDVBCFromTVS(), new ILogoAssociationListner() {
				
				@Override
				public void notifyLogoAssociationComplete() {
					onSemiStandbyExit();
				}
				
				@Override
				public void notifyLogoAssociationAborted() {
					onSemiStandbyExit();
				}
			});
			break;
		case EventIDs.EVENT_SESSION_TUNE_FAILED:
			/* Session tune has failed. Notify OnActionCompleted to PlayTv */
			ntf.unregisterForNotification(thisInstance);
			nwrap.setApplicationState(ApplicationState.IDLE);
			broadcastIntentSemistandby("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
			nwrap.UnregisterTuningInstance();
			nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
			/*Notify SSby Service*/
			ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
			break;
		}
	}
	public void camSchedulUpdateTime(int Time) {
		minute = (Time % 10) * 6;
		hour = (Time / 10);
		Log.d(TAG, "Minute obtained is  " + minute + "Hour obtained is  "
				+ hour);
		long clientTime = Long.MAX_VALUE;
		camscheduletimeinmsecs = Long.MAX_VALUE;
		Calendar alarmTime = Calendar.getInstance();
		String mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		clientTime = alarmTime.getTimeInMillis();
		Log.d(TAG, "current time is " + mydate + "And time in milli secs is "
				+ clientTime);
		alarmTime.set(Calendar.YEAR, year);
		alarmTime.set(Calendar.MONTH, (month - 1)); // One month ahead issue
		alarmTime.set(Calendar.DAY_OF_MONTH, day);
		alarmTime.set(Calendar.HOUR_OF_DAY, (hour + 1)); // Due to current issue in clock - 1 hr ahead
		alarmTime.set(Calendar.MINUTE, minute);
		alarmTime.set(Calendar.SECOND, 0);
		mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		Log.d(TAG, "Alarm time is " + mydate);
		camscheduletimeinmsecs = alarmTime.getTimeInMillis();
		Log.d(TAG, "Alarm time is " + mydate + " timeinmsecs"
				+ camscheduletimeinmsecs);
		nwrap.storeCamData(camscheduletimeinmsecs);	
//		ssbyIntf.registerSemiStandbyAction(ITvSemiStandbyControl.ACTION_TC_INSTALLATION,ssbyListner);
		ssbyIntf.setAlarmForSemiStandbyAction(ITvSemiStandbyControl.ACTION_TC_INSTALLATION, getNextAlarmTimeMSecs());

	}
	
	public void camscheduleUpdateDate(int Date) {
		Log.d(TAG, "Started parsing Date from CAM OP - Scheduled Update");
		int tempyear = 0, tempmonth = 0;
		int K = 0;
		tempyear = (int) ((Date - 15078.2) / 365.25);
		tempmonth = (int) (((int) ((Date - 14956.1) - ((int) (tempyear * 365.25))) / 30.6001));
		day = Date - 14956 - ((int) (tempyear * 365.25))
				- ((int) (tempmonth * 30.6001));
		if ((tempmonth == 14) || (tempmonth == 15)) {
			K = 1;
		} else {
			K = 0;
		}
		year = tempyear + K + 1900;// To make sync with current year
		month = tempmonth - 1 - K * 12;
		Log.d(TAG, "Year obtained is  " + year + "Month obtained is  " + month
				+ "Day obtained is  " + day);

	}
	
	public void checkStartScheduleUpdate()
	{
		Log.d(TAG,"checkStartScheduleUpdate in euinstallerservice \n");
        
		//AlarmManager alarmMgr = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
		camscheduletimeinmsecs = scheduleUpdateAlarmTime();
		long time_difference = 0;
		time_difference = getCurrentTimeinMillisec() - currenttimeinmillisecs;
		Log.d(TAG,"currenttimeinmillisecs is " + currenttimeinmillisecs);
		Log.d(TAG,"time difference is " + time_difference);
		if((camscheduletimeinmsecs != 0) && (time_difference > 240000))//4      
		{ //if difference is greater than 4 mins
//			ssbyIntf.registerSemiStandbyAction(ITvSemiStandbyControl.ACTION_TC_INSTALLATION,ssbyListner);
			if(ssbyIntf!=null) {
				ssbyIntf.setAlarmForSemiStandbyAction(ITvSemiStandbyControl.ACTION_TC_INSTALLATION, getNextAlarmTimeMSecs());
			}
		}
		currenttimeinmillisecs = getCurrentTimeinMillisec();
	}

	public long scheduleUpdateAlarmTime()
	{
		long retTime = 0;
		if((nwrap.getStoredScheduleUpdateTime() > getCurrentTimeinMillisec()) && (nwrap.IsCamSchedPerformed()))
		{
			Log.d(TAG,"Alarm time need to be set\n");
			retTime = nwrap.getStoredScheduleUpdateTime();
		}else if(nwrap.IsCamSchedPerformed()) {
			retTime = nwrap.getStoredScheduleUpdateTime();
		}
		Log.d(TAG,"scheduleUpdateAlarmTime returns "+ retTime);
		return retTime;
	}

	public long getCurrentTimeinMillisec()
	{
		final Calendar alarmTime = Calendar.getInstance();
		
		long currentTimeinMilliSec = alarmTime.getTimeInMillis();
		Log.d(TAG,"Current Time is "  +currentTimeinMilliSec);
		return currentTimeinMilliSec;

	}
	public long getNextAlarmTimeMSecs() {
		long timeinmsecs = Long.MAX_VALUE;
		
		Calendar alarmTime = Calendar.getInstance();
		String mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		Log.d(TAG,"current time is " + mydate);
		
		
		int currenthour = alarmTime.get(Calendar.HOUR_OF_DAY);
		if(currenthour>=TCALARM_HOUR) {
			alarmTime.add(Calendar.DAY_OF_MONTH, 1);
		}
				
		alarmTime.set(Calendar.HOUR_OF_DAY, TCALARM_HOUR);
		alarmTime.set(Calendar.MINUTE, 0);
		alarmTime.set(Calendar.SECOND, 0);
		
		mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		Log.d(TAG,"Alarm time is " + mydate);
		
		timeinmsecs = alarmTime.getTimeInMillis();
		camscheduletimeinmsecs = scheduleUpdateAlarmTime();
		if((camscheduletimeinmsecs !=0) && (camscheduletimeinmsecs < timeinmsecs))
		{
			timeinmsecs = camscheduletimeinmsecs;
			Log.d(TAG,"Alarm time is updated with schedule update alarm time");
		}
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
						nwrap.stopBckInstallation();
						nwrap.setApplicationState(ApplicationState.INST_SERVICE);
						ntf.registerForNotification(thisInstance);
						
						// initialize for session creation. Callback sends EVENT_INST_ONPREPAREDTV
						/*if(nwrap.isHtvDTChannelExistent()){
							nwrap.RemoveHtvDTChannel();
							nwrap.LoadTvProviderData();
							nwrap.LoadFreqMapDataData();
						}*/
						nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
						
					}
					else{
						Log.d(TAG,"update installation is not required on Shutdown");
						
						/*if(nwrap.isHtvDTChannelExistent()){
							nwrap.stopBckInstallation();
							nwrap.RemoveHtvDTChannel();
							nwrap.LoadTvProviderData();
							nwrap.LoadFreqMapDataData();
						}*/
												
						ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
					}
				}
				else if((nwrap.getFromPowerState() == PowerStates.POWER_STATE_DDR_STANDBY) && (nwrap.getToPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY) && (isTCstandbyUpdate() == true)){
					
					Log.d(TAG,"System woke up from DDR Standby ");
					if( nwrap.isSemiStandbyUpdateRequiredOnAlarmWakeup()){
						nwrap.setApplicationState(ApplicationState.INST_SERVICE);
						ntf.registerForNotification(thisInstance);
						// initialize for session creation. Callback sends EVENT_INST_ONPREPAREDTV
						nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
						
					}
					else{
						Log.d(TAG,"update installation is not required on Wakeup");
						ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
					}
					
				}
				else if(nwrap.isScheduleUpdateNeeded(getCurrentTimeinMillisec())) {
						nwrap.setApplicationState(ApplicationState.INST_SERVICE);
						ntf.registerForNotification(thisInstance);
						// initialize for session creation. Callback sends EVENT_INST_ONPREPAREDTV
						nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 	
						nwrap.OpsemistandbyInstallationstarted();
						//nwrap.startInstallation(NativeAPIEnums.InstallationMode.CAM_INSTALLATION);
				}
				else {
					Log.d(TAG,"Power state did not match");
					ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
				}
			
			}
			@Override
			public void onStopAction() {
				Log.d(TAG,"onStopAction ");
				// If installation is in progress on stop notificataion from MW notification is sent to PlayTV
				nwrap.stopBckInstallation();
				if(ifInstallationInProgress == false)
				{
					nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
					//ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
					ntf.unregisterForNotification(thisInstance);
				}
				//KT --start-- setActionCompleted here,
				//[TF415PHIEUMTK66-1207] Tv does not enter green powermode after overnight test
				//#13 log , client stop but seems not set completed, next time run semi will not run and freeze
				ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
				//KT --end--
				nwrap.setApplicationState(ApplicationState.IDLE);		
			}
			@Override
			public long onGetNextAlarm(){ 
				Log.d(TAG,"onGetNextAlarm ");
				return getNextAlarmTimeMSecs();
			}

			@Override
			public void onAlarmFired() {
				Log.d(TAG,"onAlarmFired ");
				
				//AlarmManager alarmMgr = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
				camscheduletimeinmsecs = scheduleUpdateAlarmTime();
				long time_difference = 0;
				time_difference = getCurrentTimeinMillisec() - camscheduletimeinmsecs;
				Log.d(TAG,"currenttimeinmillisecs is " + currenttimeinmillisecs);
				Log.d(TAG,"time difference is " + time_difference);
				if((camscheduletimeinmsecs != 0) && (time_difference < 240000))//4	
				{ //if difference is greater than 4 mins
					Log.d(TAG,"Calling onAlarmFired of Nwrap");
					nwrap.onAlarmFired();
				}
			}
		};


	private boolean isTCstandbyUpdate() {
		Log.d(TAG,"entered into isTCstandbyUpdate ");
		boolean isTcSemistandbyupdate = false;
		final Calendar alarmTime = Calendar.getInstance();
		 
		int currenthour = alarmTime.get(Calendar.HOUR_OF_DAY);	
		int currentmin	= alarmTime.get(Calendar.MINUTE);
		Log.d(TAG,"  isTCstandbyUpdate currenthour " + currenthour + "currentmin " + currentmin);
		if((currenthour == TCALARM_HOUR) && (currentmin<MIN_TOL)){
			Log.d(TAG,"6 AM update\n");
			isTcSemistandbyupdate = true;
		}
		return isTcSemistandbyupdate;

	}	
	
	private ServiceConnection mssbyConnection = new ServiceConnection() {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG, "onServiceConnected for ssbyservice");

			ssbyIntf = ITvSemiStandbyControl.Instance.asInterface(service);
			if (ssbyIntf != null) {
				Log.d(TAG, "ssbyIntf is not null");
				// Register Action
				ssbyIntf.registerSemiStandbyAction(ITvSemiStandbyControl.ACTION_TC_INSTALLATION,ssbyListner);
				//Set Alarm
				Log.d(TAG, "Setting Alaram");
				ssbyIntf.setAlarmForSemiStandbyAction(ITvSemiStandbyControl.ACTION_TC_INSTALLATION, getNextAlarmTimeMSecs());
				checkStartScheduleUpdate();
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
	
	private void onSemiStandbyExit(){
		Log.d(TAG, "onSemiStandbyExit");
		/* CIPLUS: Enabled Host control here */
		nwrap.SetHostControlStatus(true);
		
		ntf.unregisterForNotification(thisInstance);
		nwrap.setApplicationState(ApplicationState.IDLE);
		broadcastIntentSemistandby("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
		nwrap.UnregisterTuningInstance();
		nwrap.closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
		/*Notify SSby Service*/
		ssbyIntf.setActionCompleted(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
	}

}
