package org.droidtv.euinstallertc.service;

import java.util.Observable;
import java.util.Observer;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.AnalogSystemCountry;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.InstallationMode;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.settings.ChannelSettingsActivity;
import org.droidtv.euinstallertc.util.EventIDs;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Window;

public class AnalogDirectTuneHandleActivity extends Activity implements Observer {
	
	private static final String TAG = AnalogDirectTuneHandleActivity.class.getSimpleName();
	
	private NativeAPIWrapper mWrapper = NativeAPIWrapper.getInstance();
	private NotificationHandler mNtf = NotificationHandler.getInstance();
	private InstallerActivityManager mInstActManager = InstallerActivityManager.getInstance();
	private AnalogDirectTuneHandleActivity mContext;
	private Handler mHandler = null;
	private boolean mbIsInstRunning = false;
	private boolean mbIsNewDTRequestArrival = false;

	private int miChFreq;
	private int miTvSys;
	
	private DirectTuneUtility.DirectTuneResultInterface mResultHandler = null; 
	
	public AnalogDirectTuneHandleActivity() {
		
	}
	
	

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		Log.d(TAG, "onCreate() is called.");
		boolean fbIsFromWIXP = false;

		super.onCreate(savedInstanceState);
		
		mContext = this;
		
		mResultHandler = DirectTuneUtility.getDirectTuneResultHandler(false, mContext);
		
		boolean fbAreParametersEnough = false;
		Intent fIntent = getIntent();
		
		if(fIntent != null) {
			Bundle fParamSet = fIntent.getExtras();
			
			if(fParamSet != null && fParamSet.containsKey(EuInstallerService.KEYNAME_DT_WIXP)) {
				mResultHandler = DirectTuneUtility.getDirectTuneResultHandler(true, mContext);
				fbIsFromWIXP = true;
			}
			
			if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_FREQ)					
					&& fParamSet.containsKey(EuInstallerService.KEYNAME_DT_TVSYS)) {
				
				miChFreq = fParamSet.getInt(EuInstallerService.KEYNAME_DT_FREQ);
				miTvSys = fParamSet.getInt(EuInstallerService.KEYNAME_DT_TVSYS);
				
				fbAreParametersEnough = true;
			}
		}
		
		if (!fbAreParametersEnough) {
			Log.d(TAG, "Error: Some parameters needed for ATR are missing.");
			mResultHandler.sendDTResultIntent(1);
			finish();
		}	
		
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		mWrapper.setApplicationContext(this);
		
		mInstActManager.addActivityToStack(this);
		
		mWrapper.setApplicationState(NativeAPIEnums.ApplicationState.INST_SETTINGS);
		mWrapper.enterNonInteruptableMode();
		mWrapper.setUseHtvDTRTuneType(true, true);
				
		mHandler = new Handler();
		
		if(fbIsFromWIXP)
			setContentView(R.layout.direct_tune_handler_bg_tslt_layout);
		else
			setContentView(R.layout.direct_tune_handler_layout);
		
		mNtf.registerForNotification(mContext);
		
		mHandler.post(new Runnable() {

			@Override
			public void run() {
				Log.d(TAG, "Info: Try to acquire HTV DT semaphore.");
				mWrapper.acquireHTVDTSemaphore();
				Log.d(TAG, "Info: Acquiring semaphore is done.");
			}
			
		});
		
		// initialize for session creation. Callback sends EVENT_INST_ONPREPAREDTV
		mWrapper.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
	}



	@Override
	protected void onDestroy() {
	
		mInstActManager.removeActivityFromStack(this);
		mWrapper.releaseHTVDTSemaphore();
		super.onDestroy();
	}
	
	class EventHandler implements Runnable {
    	
    	private int miEventID;
    	
    	public EventHandler(int aiEventID) {
			miEventID = aiEventID;
		}

		@Override
		public void run() {
			
			Log.d(TAG, "Handle event..... ID:" + miEventID);
			
			switch(miEventID) {
			case EventIDs.EVENT_INST_ONPREPAREDTV:
				Log.d(TAG, "EVENT_INST_ONPREPAREDTV");
				
				if(!mbIsNewDTRequestArrival) {
					if(!mbIsInstRunning) {
						mWrapper.setCachedAnalogSytemCountry(convertAnalogSystemCountry(miTvSys));
						mWrapper.updateUserEnteredManualFreq(miChFreq);
						mWrapper.startInstallation(InstallationMode.MANUAL_INSTALLATION);
						mbIsInstRunning = true;
						sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
					}
					break;
				}								
			case EventIDs.EVENT_COMMIT_FINISHED:
				Log.d(TAG, "EVENT_COMMIT_FINISHED");
				
				if(!mbIsNewDTRequestArrival) {
					sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
															
					int fiFoundChId = mWrapper.findAnalogChannel(miChFreq, 0, miTvSys);
					
					onScreenExit();
					mInstActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
					
					if(fiFoundChId != -1) {
						Log.d(TAG, "The required channel is found.");
						mResultHandler.sendDTResultIntent(0);
						mResultHandler.switchToSpecificChannel(fiFoundChId);
					}
					else {
						Log.d(TAG, "The required channel is still not found.");
						
						mResultHandler.sendDTResultIntent(3);
					}
					
					break;
				}
			
			case EventIDs.EVENT_HTV_DT_CANCEL:
				Log.d(TAG, "EVENT_HTV_DT_CANCEL");
				mbIsInstRunning = true;
			case EventIDs.EVENT_NEW_HTV_DT_REQUEST_ARRIVAL:
				Log.d(TAG, "EVENT_NEW_HTV_DT_REQUEST_ARRIVAL");
				mbIsNewDTRequestArrival = true;	
			case EventIDs.EVENT_INST_TUNING_STATION_NOT_FOUND:
				Log.d(TAG, "search failed EVENT_INST_TUNING_STATION_NOT_FOUND");
				
				if(mbIsInstRunning) {
					mbIsInstRunning = false;
					onScreenExit();
					sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
					
					if(!mbIsNewDTRequestArrival)
						mResultHandler.sendDTResultIntent(3);
					
					mInstActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
				}
				break;
				
			case EventIDs.EVENT_SHOW_SEARCH_AFTER_STRING: // search is
				// complete
				Log.d(TAG, "search success EVENT_SHOW_SEARCH_AFTER_STRING");
				
				if(mbIsInstRunning) {
					mbIsInstRunning = false;
					mWrapper.updateCachedAnalogSytemCountry();
					mWrapper.setStoreAsNewChannelStatus(true);
					mWrapper.StoreManualInstallAsNewChannel();
				}
				break;							
			}
		}
	}

	@Override
	public void update(Observable observable, Object data) {
		
		int fiEventID = ((NotificationInfoObject) data).actionID;
		
		Log.d(TAG, "Received event. ID:" + fiEventID);
		
		runOnUiThread(new EventHandler(fiEventID));	
	}
	
	private void sendIntent(String p_action) {
		Log.d(TAG, "sendIntent " + p_action);
		Intent l_intent = new Intent(p_action);
		l_intent.putExtra("InstallMode", "AnalogueManual");
		if (mWrapper.AvailableCableMedium()) {
			l_intent.putExtra("InstallMedium", "Cable");
		} else {
			l_intent.putExtra("InstallMedium", "Terrestrial");
		}
		mContext.sendStickyBroadcast(l_intent);
	}
	
	private AnalogSystemCountry convertAnalogSystemCountry(int aiIdx) {
		
		AnalogSystemCountry feResult;
		
		switch(aiIdx) {		
		case 1:
			feResult = AnalogSystemCountry.EAST_EUROPE;
			break;
		case 2:
			feResult = AnalogSystemCountry.UK;
			break;
		case 3:
			feResult = AnalogSystemCountry.FRANCE;
			break;
		case 0:
		default:
			feResult = AnalogSystemCountry.WEST_EUROPE;		
		}
		
		return feResult;
	}
	
	private void onScreenExit() {
		Log.d(TAG, "onScreenExit");
		mWrapper.StopManualSearch();
		NotificationHandler.getInstance().unregisterForNotification(this);
		mWrapper.setUseHtvDTRTuneType(false,false);
		mWrapper.exitNonInteruptableMode();
		
		
	}
    

}
