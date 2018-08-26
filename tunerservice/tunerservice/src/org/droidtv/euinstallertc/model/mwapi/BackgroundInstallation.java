package org.droidtv.euinstallertc.model.mwapi;

import java.util.Observable;
import java.util.Observer;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.ApplicationState;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DVBTOrDVBC;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.notification.NetworkUpdateDialogActivity;
import org.droidtv.euinstallertc.util.EventIDs;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class BackgroundInstallation implements Observer {

	private final String TAG = BackgroundInstallation.class.getName();
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private NotificationHandler ntf = NotificationHandler.getInstance();
	private Context mContext;
	private BackgroundInstallation thisInstance;
    private int presetAfterBackgroundUpdate = -1;

	public BackgroundInstallation(Context ctx) {
		Log.d(TAG, "BackgroundInstallatione " + ctx);
		mContext = ctx;
		thisInstance = this;
	}

	public void startBackgroundInstallation() {
		Log.d(TAG, "startBackgroundInstallation " + mContext);
		presetAfterBackgroundUpdate = -1;
		if ((nwrap.getApplicationState() == ApplicationState.IDLE) || (nwrap.getApplicationState() == ApplicationState.INST_SERVICE)) {
			nwrap.stopBckInstallation();
			nwrap.setApplicationState(ApplicationState.INST_SERVICE);
			nwrap.background_SetSystemCountry();
			
			try{
				ntf.unregisterForNotification(thisInstance);
			}catch(Exception ex){
			}
			ntf.registerForNotification(thisInstance);
			nwrap.startInstallation(NativeAPIEnums.InstallationMode.BACKGROUND_INSTALLATION);
			///nwrap.stopAndRestartInstallation(NativeAPIEnums.InstallationMode.BACKGROUND_INSTALLATION);
		}
	}

	
	public void stopBackgroundInstallation() {
		Log.d(TAG, "stopBackgroundInstallation " + mContext);
		if ((nwrap.getApplicationState() == ApplicationState.IDLE) || (nwrap.getApplicationState() == ApplicationState.INST_SERVICE)) {
			nwrap.stopBckInstallation();
			nwrap.setApplicationState(ApplicationState.IDLE);
			nwrap.UnregisterTuningInstance();
			ntf.unregisterForNotification(thisInstance);
		}
	}

	private void broadcastIntent(String intentName) {
		Log.d(TAG, "broadcastIntent " + intentName);
		Intent intent = new Intent(intentName);
		intent.putExtra("InstallMode", "Background");

		if (DVBTOrDVBC.DVBC == nwrap.getSelectedDVBTOrDVBCFromTVS()) {
			intent.putExtra("InstallMedium", "Cable");
		} else {
			intent.putExtra("InstallMedium", "Terrestrial");

		}
		mContext.sendStickyBroadcast(intent);
	}

	@Override
	public void update(Observable observable, Object data) {
		// TODO Auto-generated method stub
		final int eventID = ((NotificationInfoObject) data).actionID;

		if ((nwrap.getApplicationState() == ApplicationState.IDLE) || (nwrap.getApplicationState() == ApplicationState.INST_SERVICE)) {

			switch (eventID) {
			case EventIDs.EVENT_INST_STARTED:
				Log.d(TAG, "EVENT_INST_STARTED ");
				broadcastIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
				break;

			case EventIDs.EVENT_INST_STOPPED:
				break;

			case EventIDs.EVENT_INST_COMPLETED:
				Log.d(TAG, "EVENT_INST_COMPLETED ");
				// check if channels added /removed
				nwrap.commitDatabaseToTvProvider(false);
				break;

			case EventIDs.EVENT_NETWORK_UPDATE_DETECTED:
				Log.d(TAG, "EVENT_NETWORK_UPDATE_DETECTED ");
				// The Update dialog is only needed for UPC operator : CR AN-717
				Log.d(TAG, "Current Operator" + nwrap.getOperatorFromMW());
				if (nwrap.getOperatorFromMW() == NativeAPIEnums.Operators.UPC){
					Log.d(TAG, "UPC operator or APMEAbackgroundNWupdateDVBT\n");
					if (mContext != null) {
						// unregister service from notification framework
						ntf.unregisterForNotification(thisInstance);
						Log.d(TAG, "service context not null");
						// stop installation if in progress
						// nwrap.stopInstallation(false); instead of doing this
						// we
						// will call stop-restart api in nativeapiwrapper
						if (nwrap.ifNetworkChangeDetected() == false) { // AN-49771
							Intent l_intent = new Intent(mContext, NetworkUpdateDialogActivity.class);
							l_intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
							mContext.startActivity(l_intent);
						} else {
							Log.d(TAG, "User has already selected Later");
						}
					}
				} else if(nwrap.IsAPMEAbackgroundNWupdate() && (DVBTOrDVBC.DVBT == nwrap.getSelectedDVBTOrDVBCFromTVS())){
					Log.d(TAG,"APMEA network update");
					// requirement APMEA Smitha TF515PHIALLMTK01-17521
					if (nwrap.ifNetworkChangeDetected() == false) {
						nwrap.showTVNofification(mContext, mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CHANNEL_UPDATE_NEEDED));
					}
					nwrap.networkChangeDetected(true);
				}else {
					// for all other non UPC countries
					nwrap.networkChangeDetected(true);
				}
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
			case EventIDs.EVENT_MAJORVERSION_UPDATE:
				Log.d(TAG, "EventIDs.EVENT_MAJORVERSION_UPDATE");
				nwrap.setMajorVersion();
				break;
			case EventIDs.EVENT_NEWPRESETNUMBER:
				int presetNum = -1;
				String l_msg1 = (String) ((NotificationInfoObject) data).message; 
				presetNum = Integer.parseInt(l_msg1);
                presetAfterBackgroundUpdate = presetNum;
				break;				
			case EventIDs.EVENT_COMMIT_FINISHED:
				nwrap.startLogoAssociation(nwrap.getSelectedDVBTOrDVBCFromTVS(), null);
				broadcastIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
            	if (presetAfterBackgroundUpdate != -1) {                            
				    nwrap.HandleTuneToLowestPreset (presetAfterBackgroundUpdate);
                }
				break;
			case EventIDs.EVENT_TELENET_NAME_UPDATE:
				int presetNbr = -1, CABLE_MEDIUM = 1;
				String l_msg2 = (String) ((NotificationInfoObject) data).message; 
				presetNbr = Integer.parseInt(l_msg2);
				/* Currently this will happen only for Telenet */
                nwrap.SyncSingleChannelToDatabase (CABLE_MEDIUM, presetNbr);
				break;
			case EventIDs.EVENT_TELENET_MAJOR_VERSION_UPDATE:
				nwrap.mUpdateDatabaseVersion(true);
				broadcastIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
				break;
			}
		}
	}
}
