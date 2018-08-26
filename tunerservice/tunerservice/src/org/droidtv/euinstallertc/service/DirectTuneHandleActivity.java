package org.droidtv.euinstallertc.service;

import java.util.Observable;
import java.util.Observer;

import org.droidtv.tunerservice.R;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.util.ContextHelper;
import org.droidtv.euinstallertc.util.EventIDs;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Window;

public class DirectTuneHandleActivity extends Activity implements Observer{
	
	private static final String TAG = DirectTuneHandleActivity.class.getSimpleName();
	
	private NativeAPIWrapper mWrapper = NativeAPIWrapper.getInstance();
	private NotificationHandler mNtf = NotificationHandler.getInstance();
	private InstallerActivityManager mInstActManager = InstallerActivityManager.getInstance();
	private ITvSettingsManager mTvSettingsManager =ITvSettingsManager.Instance.getInterface();
	private DirectTuneHandleActivity mContext;
	private int miChFreq;
	private int miTuneType; //0:Antenna 1:Cable
	private int miServID = 0;
	private Integer miNID = null;
	private Integer miONID = null;
	private Integer miTSID = null;
	private Integer miMod = null;
	private Integer miSymRt = null;
	private Integer miChID = null;
	private boolean mbIsInstRunning = false;
	private Handler mHandler = null;
	private boolean mbIsDTOP = true;
	private boolean mbIsHandleInstComplete = false;
	private boolean mbIsNewDTRequestArrival = false;
	private boolean mbIsDVBT2 = false;
	
	private int mviPlpIDs[] = null;
	private int miPlpSelIdx = -1;
	private int miFocusedPlpID = -1; 
	
	private static final String KEYNAME_RESULT = "Result";
	private static final String KEYNAME_PLPSIZE = "PlpSize";
	private static final String KEYNAME_PLPIDX = "PlpIdx";
	
	
	public static final int KEYVALUE_TUNETYPE_TERRESTRIAL = 0;
	public static final int KEYVALUE_TUNETYPE_CABLE = 1;
	
	private DirectTuneUtility.DirectTuneResultInterface mResultHandler = null; 

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
			
			if(fParamSet != null && fParamSet.containsKey(EuInstallerService.KEYNAME_VALUE)) {
				
				//if(EuInstallerService.KEYVALUE_DIRECT_INST.equals(fParamSet.getString(EuInstallerService.KEYNAME_VALUE))) {
				//	Log.d(TAG, "This is a single frequency installation.");
				//	mbIsDTOP = false;
				//}
				//else
				//	Log.d(TAG, "This is a direct tuning.");
				
				if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_FREQ) 
						&& fParamSet.containsKey(EuInstallerService.KEYNAME_DT_TUNETYPE)) {
					
					miChFreq = fParamSet.getInt(EuInstallerService.KEYNAME_DT_FREQ);
					miTuneType = fParamSet.getInt(EuInstallerService.KEYNAME_DT_TUNETYPE);
					
					if(miTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T2)
					{
						miTuneType = 0;
						mbIsDVBT2 = true;
					}
					
					if(mbIsDTOP) {
						if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_SERVID)) {
							miServID = fParamSet.getInt(EuInstallerService.KEYNAME_DT_SERVID);
							fbAreParametersEnough = true;
							
							if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_NID))
								miNID = fParamSet.getInt(EuInstallerService.KEYNAME_DT_NID);
							
							if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_ONID))
								miONID = fParamSet.getInt(EuInstallerService.KEYNAME_DT_ONID);
							
							if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_TSID))
								miTSID = fParamSet.getInt(EuInstallerService.KEYNAME_DT_TSID);
							
							if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_MOD))
								miMod = fParamSet.getInt(EuInstallerService.KEYNAME_DT_MOD);
							
							if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_SYMRT))
								miSymRt = fParamSet.getInt(EuInstallerService.KEYNAME_DT_SYMRT);
							
							if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_PLPID))
								miFocusedPlpID = fParamSet.getInt(EuInstallerService.KEYNAME_DT_PLPID);
                            Log.d(TAG, "onCreate miFocusedPlpID:" + miFocusedPlpID );
							if(fParamSet.containsKey(EuInstallerService.KEYNAME_DT_CHID))
								miChID = fParamSet.getInt(EuInstallerService.KEYNAME_DT_CHID);
							
						}
					}
					else {
						fbAreParametersEnough = true;
					}
				}
				
			}					
		} 
		
		if (!fbAreParametersEnough) {
			Log.d(TAG, "Error: Some parameters needed for DTR are missing.");
			mResultHandler.sendDTResultIntent(1);
			finish();
		}							
				
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		mWrapper.setApplicationContext(this);
		
		mInstActManager.addActivityToStack(this);
		
		mWrapper.setApplicationState(NativeAPIEnums.ApplicationState.INST_WIZARD);
		mWrapper.enterNonInteruptableMode();
		mWrapper.setUseHtvDTRTuneType(true, miTuneType==0?true:false);		
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
	
	private Runnable mTimeoutChecker = new Runnable() {
		@Override
		public void run() {
			if(mbIsInstRunning) {
				EventHandler fEvtHandler = new EventHandler(EventIDs.EVENT_INST_CHANNEL_NOT_FOUND);
				fEvtHandler.run();
			}
		}
	}; 
    
    class EventHandler implements Runnable {
    	
    	private int miEventID;
    	private String msMsg = null;
    	
    	public EventHandler(int aiEventID) {
			miEventID = aiEventID;
		}
    	
    	public EventHandler(int aiEventID, String asMsg) {
			miEventID = aiEventID;
			msMsg = asMsg;
		}

		@Override
		public void run() {
			
			Log.d(TAG, "Handle event..... ID:" + miEventID);
			
			switch(miEventID) {
			case EventIDs.EVENT_INST_ONPREPAREDTV:
				Log.d(TAG, "EVENT_INST_ONPREPAREDTV");

				if(mbIsNewDTRequestArrival) {
					mbIsInstRunning = true;
					mHandler.post(mTimeoutChecker);
				} else if(!mbIsInstRunning) {
					mWrapper.muteAudio(true);

					mHandler.post(new Runnable() {
						@Override
						public void run() {
							Log.d(TAG, "Prepare to do DTR...");

							mWrapper.autoSetSystemCountryToMW(true);
							mWrapper.setLCNSortingControl(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_LCN, 0, 0));
							mWrapper.setMedium(miTuneType==0?NativeAPIEnums.DVBTOrDVBC.DVBT:NativeAPIEnums.DVBTOrDVBC.DVBC);
							//mWrapper.setDVBTOrDVBC(miTuneType==0?NativeAPIEnums.DVBTOrDVBC.DVBT:NativeAPIEnums.DVBTOrDVBC.DVBC);

							sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
                            Log.d(TAG, "run  miFocusedPlpID:" + miFocusedPlpID );
							mbIsInstRunning = true;							
							mHandler.postDelayed(mTimeoutChecker, 15000);

							mWrapper.stopDTRInstallation();
							mWrapper.setDTRMonitorServID(miServID);							
							mWrapper.setFocusedDVBT2PlpID(miFocusedPlpID);
							mWrapper.setExtractScanResult(miChID!=null);
							mWrapper.setTestReceptionFrequencyEx(miChFreq/10, mbIsDTOP);

						}
					});
				}

				break;
			case EventIDs.EVENT_PLPIDS_DETECTED:
				Log.d(TAG, "EVENT_PLPIDS_DETECTED");
				
				mviPlpIDs = mWrapper.getPLPIDs();
				if (mviPlpIDs != null && mviPlpIDs.length > 1) {
					miPlpSelIdx = 0;					
					mWrapper.setIsDVBT2Scan(true);					
				}												
				break;
			case EventIDs.EVENT_T2_SWITCH_PLP_ID:
				Log.d(TAG, "EVENT_T2_SWITCH_PLP_ID " + msMsg);
				
				if(msMsg != null) {
					if(mviPlpIDs == null){
						mviPlpIDs = new int[] {-1};
						miPlpSelIdx = 0;
					}

					try{
						mviPlpIDs[miPlpSelIdx] = Integer.parseInt(msMsg);
					}
					catch(NumberFormatException e) {
						Log.d(TAG, "Error: PLP ID convertion failed.");
					}
				}
				
				mHandler.removeCallbacks(mTimeoutChecker);
				mHandler.postDelayed(mTimeoutChecker, 6000);
				break;
			case EventIDs.EVENT_LCN_CONFLICT:
				Log.d(TAG, "EVENT_LCN_CONFLICT");
				break;
			case EventIDs.EVENT_SERVICE_FOUND:
			{				
				Log.d(TAG, "EVENT_SERVICE_FOUND");
				
				if(mbIsInstRunning) {
					
					updateChannelInfo();
					mbIsInstRunning = false;
					
					sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
					
					mNtf.unregisterForNotification(mContext);
					mWrapper.StopManualSearch();
					mWrapper.setIsDVBT2Scan(false);
					mWrapper.setDTRMonitorServID(0);
					mWrapper.setFocusedDVBT2PlpID(-1);
					mWrapper.setExtractScanResult(false);
					mWrapper.setUseHtvDTRTuneType(false,false);
					mWrapper.setLCNSortingControl(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_LCN, 0, 0));
					mInstActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
					//mWrapper.releaseHTVDTSemaphore();
					
					if(!mbIsNewDTRequestArrival)
						mResultHandler.switchToSpecificChannel(miChID);					
				}
								
			}								
				break;
			case EventIDs.EVENT_HTV_DT_CANCEL:
				Log.d(TAG, "EVENT_HTV_DT_CANCEL");
				mbIsInstRunning = true;
			case EventIDs.EVENT_NEW_HTV_DT_REQUEST_ARRIVAL:
				Log.d(TAG, "EVENT_NEW_HTV_DT_REQUEST_ARRIVAL");
				mbIsNewDTRequestArrival = true;				
			case EventIDs.EVENT_SERVICE_NOT_FOUND:
				
				Log.d(TAG, "EVENT_SERVICE_NOT_FOUND");
			/*	
				if(!mbIsNewDTRequestArrival && mviPlpIDs!=null && mviPlpIDs.length>1 && miPlpSelIdx < (mviPlpIDs.length-1)) {
					mHandler.removeCallbacks(mTimeoutChecker);
					miPlpSelIdx++;
					
					Log.d(TAG, "Info: Scan next PLP: " + miPlpSelIdx);
					
					mbIsInstRunning = true;
					mWrapper.setIsDVBT2Scan(true);
					mWrapper.setPLPID(mviPlpIDs[miPlpSelIdx]);
					mWrapper.setTestReceptionFrequencyEx(miChFreq/10, mbIsDTOP);
					mHandler.postDelayed(mTimeoutChecker, 10000);
					
					break;
				}*/
			case EventIDs.EVENT_INST_CHANNEL_NOT_FOUND:
			case EventIDs.EVENT_INST_TUNING_STATION_NOT_FOUND:
				Log.d(TAG, "No digital channel found.");
				if(mbIsInstRunning) {
					mWrapper.CancelTestReceptionInstallation();
					sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
					
					if(miChID == null && !mbIsNewDTRequestArrival)
						mResultHandler.sendDTResultIntent(3);
					
					mbIsInstRunning = false;
					
					mNtf.unregisterForNotification(mContext);
					mWrapper.StopManualSearch();
					mWrapper.setIsDVBT2Scan(false);
					mWrapper.setDTRMonitorServID(0);
					mWrapper.setFocusedDVBT2PlpID(-1);
					mWrapper.setExtractScanResult(false);
					mWrapper.setUseHtvDTRTuneType(false,false);
					mWrapper.setLCNSortingControl(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_LCN, 0, 0));
					mWrapper.exitNonInteruptableMode();
					mInstActManager.exitInstallation((miEventID == EventIDs.EVENT_HTV_DT_CANCEL)?EXIT_INSTALLER_REASON.POWER_STATE_TO_SEMISTANDY:EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
					
					if(miChID != null && !mbIsNewDTRequestArrival)
						mWrapper.switchToSpecificChannelEx(miChID,true);
				}				
				break;	
			case EventIDs.EVENT_DIGIT_CH_FOUND:
				Log.d(TAG, "Digital channel found.");
				if(mbIsInstRunning) {
					if(mbIsNewDTRequestArrival)
						mHandler.post(mTimeoutChecker);
					else
					{
						mbIsInstRunning = false;
						mWrapper.StoreTestReceptionInstallation();
						mbIsHandleInstComplete = true;					
					}
				}
				break;
			case EventIDs.EVENT_INST_COMPLETED:
				Log.d(TAG, "EVENT_INST_COMPLETED");
				
				if(!mbIsHandleInstComplete)
					break;
				
				if(!mbIsDTOP)
					mWrapper.setUseHtvDTRTuneType(false,false);
				
				mWrapper.commitDatabaseToTvProvider(false);								
				break;
			case EventIDs.EVENT_COMMIT_FINISHED:
				Log.d(TAG, "EVENT_COMMIT_FINISHED");
				
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
				
				mNtf.unregisterForNotification(mContext);
				mWrapper.setIsDVBT2Scan(false);
				mWrapper.setDTRMonitorServID(0);
				mWrapper.setFocusedDVBT2PlpID(-1);
				mWrapper.setExtractScanResult(false);
				mWrapper.setUseHtvDTRTuneType(false,false);
				mWrapper.setLCNSortingControl(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_LCN, 0, 0));
				
				if(mbIsDTOP) {
					
					int fiFoundChId = mWrapper.findDigitalChannel(miChFreq, miTuneType, miServID, miNID, miONID, miTSID, miMod, miSymRt, miFocusedPlpID);
					
					mInstActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
					//mWrapper.releaseHTVDTSemaphore();
					
					if(!mbIsNewDTRequestArrival) {
						if(fiFoundChId != -1) {
							Log.d(TAG, "The required channel is found.");
							mResultHandler.sendDTResultIntent(0);
							mResultHandler.switchToSpecificChannel(fiFoundChId);
						}
						else {
							Log.d(TAG, "The required channel is still not found.");
							
							mResultHandler.sendDTResultIntent(3);
						}
					}					
				}
				else {
					mInstActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
					//mWrapper.releaseHTVDTSemaphore();
				}
								
				break;
			}
			
		}
    	
    }
    
    private void sendIntent(String p_action) {
		Log.d(TAG, "sendIntent " + p_action);
		Intent l_intent = new Intent(p_action);
		l_intent.putExtra("InstallMode", "DTR");
		if (miTuneType > 0) {
			l_intent.putExtra("InstallMedium", "Cable");
		} else {
			l_intent.putExtra("InstallMedium", "Terrestrial");
		}
		mContext.sendStickyBroadcast(l_intent);
	}
    
    @Override
	protected void onNewIntent(Intent intent) {
		Log.d(TAG, "onNewIntent() is called.");
		super.onNewIntent(intent);
	}



	@Override
	protected void onDestroy()
	{
		Log.d(TAG, "onDestroy");
		mInstActManager.removeActivityFromStack(this);
		mWrapper.releaseHTVDTSemaphore();
		super.onDestroy();
	}

	@Override
	public void update(Observable observable, Object data) {
		
		int fiEventID = ((NotificationInfoObject) data).actionID;
		
		Log.d(TAG, "Received event. ID:" + fiEventID);
		
		runOnUiThread(new EventHandler(fiEventID, ((NotificationInfoObject) data).message));		
	}
	
	private boolean updateChannelInfo() {
		
		Log.d(TAG, "updateChannelInfo() is called.");
		
		boolean fbResult = false;
		
		if(miChID != null
				&& ((miTuneType == 0 && mbIsDVBT2 && mviPlpIDs != null && miPlpSelIdx != -1) || (miTuneType == 0 && !mbIsDVBT2) || miTuneType == 1)) {

			String[] fsvProjections = new String[]{Channels.COLUMN_INTERNAL_PROVIDER_DATA, Channels.COLUMN_NETWORK_AFFILIATION, Channels.COLUMN_DISPLAY_NAME};
			String mSelecion = "_id=?";
			String[] mSelectionArgs = new String[] {String.valueOf(miChID)};
			ContentValues fvValues = new ContentValues();			
			
			int fiONID = mWrapper.getDTRMonitorServONID();
			int fiTSID = mWrapper.getDTRMonitorServTsID();
			String fsServName = mWrapper.getDTRMonitorServName();
			int fiSymRt = 0;

			do {
				
				if(miTuneType == 1)
					if((fiSymRt = mWrapper.getDTRMonitorSymbolRate()) <= 0) {
						Log.d(TAG, "The detected symbol rate is invalid.");
						break;
					}
				
				if(fiONID != -1)
					fvValues.put(Channels.COLUMN_ORIGINAL_NETWORK_ID, fiONID);
				
				if(fiTSID != -1)
					fvValues.put(Channels.COLUMN_TRANSPORT_STREAM_ID, fiTSID);
				
				fvValues.put(Channels.COLUMN_NETWORK_AFFILIATION,"");
					
				Cursor fCursor = getContentResolver().query(TvContract.Channels.CONTENT_URI, fsvProjections, mSelecion, mSelectionArgs, null);
				
				if(fCursor != null){
					if(fCursor.getCount()>0){
						fCursor.moveToFirst();
						
						if(NativeAPIWrapper.HTV_DI_CHANNEL_CHECK_FLAG.equals(fCursor.getString(1))) {
							fvValues.put(Channels.COLUMN_NETWORK_AFFILIATION, NativeAPIWrapper.HTV_DI_CHANNEL_FLAG);
							
							if(!fsServName.isEmpty()) {
								String fsChName = fCursor.getString(2);
								
								if((fsChName != null && fsChName.isEmpty()) || fsChName == null)
									fvValues.put(Channels.COLUMN_DISPLAY_NAME, fsServName);
							}							
						}
						else if(!fsServName.isEmpty())
							fvValues.put(Channels.COLUMN_DISPLAY_NAME, fsServName);
						
						try{
							IIntKeyValueables fKeyvalues = IIntKeyValueables.Instance.getInterface();
							
							fKeyvalues.setBlob(fCursor.getBlob(0));	
							
							if(miTuneType == 0){
								
								if(mbIsDVBT2){
									fKeyvalues.put(ITvContractExtras.C_PLPID, mviPlpIDs[miPlpSelIdx]);
								
									Log.d(TAG, "Update DVB-T2 channel info. _id:" + miChID + "  Name:" + fsServName + "  ONID:" + fiONID + "  TSID:" + fiTSID + "  PLPID:" + mviPlpIDs[miPlpSelIdx]);
								}
								else {
									fKeyvalues.put(ITvContractExtras.C_BANDWIDTH, mWrapper.getDTRMonitorBandwidth());
									
									Log.d(TAG, "Update DVB-T channel info. _id:" + miChID + "  Name:" + fsServName + "  ONID:" + fiONID + "  TSID:" + fiTSID + "  BandWidth:" + mWrapper.getDTRMonitorBandwidth());
								}
							}
							else {			
															
								fKeyvalues.put(ITvContractExtras.C_SYMBOLRATE, fiSymRt);
								
								Log.d(TAG, "Update DVB-C channel info. _id:" + miChID + "  Name:" + fsServName + "  ONID:" + fiONID + "  TSID:" + fiTSID + "  SymRt:" + fiSymRt);
							}
												
							fvValues.put(Channels.COLUMN_INTERNAL_PROVIDER_DATA, fKeyvalues.getBlob());						
						}
						catch(Exception e)
						{
							Log.d(TAG, "Error: during process Blob data. Msg:" + e.getMessage());
						}
					}
					
					fCursor.close();
					fCursor = null;
				}
											
				if(getContentResolver().update(TvContract.Channels.CONTENT_URI, fvValues, mSelecion, mSelectionArgs) > 0) 
				{
					Log.d(TAG, "Update channel info: success.");
					
					fbResult = true;
				}
					
				
			}while(false);
		}

		return fbResult;
	}
	
	

}
