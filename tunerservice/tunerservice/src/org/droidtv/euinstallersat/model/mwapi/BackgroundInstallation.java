package org.droidtv.euinstallersat.model.mwapi;

import java.util.Observable;
import java.util.Observer;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.notification.BackGroundUpdateInstallActivity;
import org.droidtv.euinstallersat.util.EventIDs;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class BackgroundInstallation implements Observer {

	private static final String TAG = BackgroundInstallation.class.getName();
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private NotificationHandler ntf = NotificationHandler.getInstance();
	private Context mContext;
	private BackgroundInstallation thisInstance;

	public BackgroundInstallation(Context ctx) {
		Log.d(TAG, "BackgroundInstallatione " + ctx);
		mContext = ctx;
		thisInstance = this;
	}

	public void startBackgroundInstallation() {
		Log.d(TAG, "startBackgroundInstallation " + mContext);
		if ((nwrap.getApplicationState() == NativeAPIWrapper.STATE_IDLE) || (nwrap.getApplicationState() == NativeAPIWrapper.STATE_SERVICE)) {
			nwrap.stopBckInstallation();
			nwrap.setApplicationState(NativeAPIWrapper.STATE_SERVICE);
			try{
				ntf.unRegisterForNotification(thisInstance);
			}catch(Exception ex){
			}
			ntf.registerForNotification(thisInstance);
			nwrap.SetScanStarts(MwDataTypes.IHsvSatelliteInstallation_InstallationBackground,0);
		}
	}

	
	public void stopBackgroundInstallation() {
		Log.d(TAG, "stopBackgroundInstallation " + mContext);
		if ((nwrap.getApplicationState() == NativeAPIWrapper.STATE_IDLE) || (nwrap.getApplicationState() == NativeAPIWrapper.STATE_SERVICE)) {
			nwrap.stopBckInstallation();
			nwrap.setApplicationState(NativeAPIWrapper.STATE_IDLE);
			ntf.unRegisterForNotification(thisInstance);
		}
	}

	private void broadcastIntent(String intentName){
		Log.d(TAG,"broadcastIntent " + intentName);
		Intent intent = new Intent(intentName);
		intent.putExtra("InstallMode", "Background");
		mContext.sendStickyBroadcast(intent);
	}
	
	public void launchTriggerBackgroundUpdateInstall() {
		Log.d(TAG, "Entered launchTriggerBackgroundUpdateInstall Entry");

		if (mContext != null) {
			Log.d(TAG, "service context not null");
			Intent l_intentBgUpInstall = new Intent(mContext, BackGroundUpdateInstallActivity.class);
			l_intentBgUpInstall.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			mContext.startActivity(l_intentBgUpInstall);
		}

		Log.d(TAG, "launchTriggerBackgroundUpdateInstall Exit ");
	}

	@Override
	public void update(Observable observable, Object data) {
		final int eventID = ((NotificationInfoObject) data).actionID;

		if ((nwrap.getApplicationState() == NativeAPIWrapper.STATE_IDLE) || (nwrap.getApplicationState() == NativeAPIWrapper.STATE_SERVICE)) {

			switch (eventID) {
			case EventIDs.SERVICE_SCAN_COMPLETE:
				Log.d(TAG, "SERVICE_SCAN_COMPLETE ");
				nwrap.commitDatabaseToTvProvider(nwrap.INSTALL_TYPE_BACKGROUND);
				nwrap.SetMajorVersion(false);
				break;
			case EventIDs.EVENT_INST_STARTED:
				Log.d(TAG, "EVENT_INST_STARTED ");
				broadcastIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
			break;
			case EventIDs.INSTALLATION_FAILED:
				Log.d(TAG, "EVENT_INST_FAILED ");
				nwrap.SetHostControlStatus(TunerName.TUNER1, true);
				nwrap.SetHostControlStatus(TunerName.TUNER2, true);
				break;
				
			case EventIDs.TRIGGER_BACKGROUND_UPDATE_INSTALL:
				Log.d(TAG, "TRIGGER_BACKGROUND_UPDATE_INSTALL");
				if (nwrap.ifRecordingIsInProgress() == false) {
					launchTriggerBackgroundUpdateInstall();
				} else {
					Log.d(TAG, "Recording is going on so background installation is blocked");
				}
				break;
			case EventIDs.COMMIT_TVPROVIDER_FINISHED:
				Log.d(TAG, "COMMIT_TVPROVIDER_FINISHED");
				broadcastIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_COMPLETE");
				break;
			case EventIDs.MAJORVERSION_UPDATE:
				nwrap.SetMajorVersion(true);
				break;

			}
		}
	}

}
