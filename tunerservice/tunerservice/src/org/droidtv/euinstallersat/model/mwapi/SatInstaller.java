package org.droidtv.euinstallersat.model.mwapi;

import java.io.IOException;
import java.io.InputStream;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.model.mwapi.OperatorProfileSearchStatus;
import org.droidtv.euinstallersat.model.mwapi.OperatorProfileStatusInfo;
import org.droidtv.euinstallersat.model.mwapi.OperatorProfileNitData;
import org.droidtv.euinstallersat.model.mwapi.OperatorProfileTuneData;
import org.droidtv.euinstallersat.model.mwapi.OperatorSearchSettings;
import org.droidtv.euinstallersat.model.mwapi.OperatorTuneStatus;
import org.droidtv.euinstallersat.model.mwapi.SatInstallerTvProviderData;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_MEDIUM;
import org.droidtv.tv.media.ITvMediaCI.CICamIdInfo;
import org.droidtv.tv.frontend.ITuning;
import org.droidtv.tv.frontend.ITuning.OnChangeListener;
import org.droidtv.tv.frontend.ITuningDvbS;
import org.droidtv.tv.frontend.ITuningDvbS.DvbSParams;
import org.droidtv.tv.frontend.ITuningDvbS.DvbSLNBConfig;
import org.droidtv.tv.frontend.ITuningDvbS.DvbSCustomLNBConfig;
import org.droidtv.tv.frontend.ITuningDvbS.DvbSUnicableConfig;
import org.droidtv.tv.media.ITvMediaCI.CIMmiEnq;
import org.droidtv.tv.media.ITvMediaCI.CIMmiMenuList;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.media.ITvMediaCI.CIMmiResponse;
import org.droidtv.tv.media.ITvMediaOp.OpSearchSettings;
import org.droidtv.tv.media.ITvMediaOp.OPTuneStatus;
import org.droidtv.tv.media.ITvMediaOp.OpProfileSearchStatus;
import org.droidtv.tv.media.ITvMediaOp.OpProfileStatusInfo;
import org.droidtv.tv.media.ITvMediaOp.OpProfileNitData;
import org.droidtv.tv.media.ITvMediaOp.OpProfileTuneData;
import org.droidtv.tv.media.ITvMediaOp;
import org.droidtv.tv.media.ITvMediaOp.IOnOpChangeListener;
import org.droidtv.tv.media.ITvMediaCI.IOnCIChangeListener;
//import org.droidtv.tv.provider.IChannelMapUpdaterControl;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.tvinput.ITVCIControl;
import org.droidtv.tv.tvclock.ITvClockManager;
import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;
import android.media.tv.TvContract;
import android.os.Bundle;
import android.view.Surface;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.InstallationCountryConstants;


public class SatInstaller extends IOnOpChangeListener {

	private String TAG = SatInstaller.class.getName();
	private Context mActivityInstance;
	// notification instance handler holder
	private NotificationHandler ntf = NotificationHandler.getInstance();
	private ITuning frontendTun = null;
	private ITuningDvbS s = null;
	private int javaSatInstHandler;
	private ITuningDvbS.DvbSParams params;
	private ITuningDvbS.DvbSLNBConfig configLNB;
	private ITuningDvbS.DvbSCustomLNBConfig configCustomLNB;
	private ITuningDvbS.DvbSUnicableConfig configUniCable;
	private final int INSTALL = 3;
	private AssetManager assetManager = null; // context.getAssets();
	private ITvMediaOp tvMop = null;
	private ITvMediaCI tvMci = null;
	private ITvSettingsManager m_settings = ITvSettingsManager.Instance.getInterface();
	private boolean isOPSupported = false;
	private CIMmiEnq mmiEnqCmd;
	private CIMmiMenuList mmiMenuCmd;
	private CIMmiMenuList mmiListCmd;
	private int currentMmiID;
	private int currentListChoice;
	private int currentMenuChoice;
	private int maximumNoOflistChoice;
	private int maximumNoOfMenuChoice;
	private final int MINIMUM_NO_OF_CHOICE = 0;
	private final static int CAM_DVBS_HINT = 0x2;
	private boolean menuChoiceExists;
	private boolean listChoiceExists;
	private boolean mMMIInProgress;
	private int mLastSelectedMenuIndex;
	private int menuItemcount;
	private int[] lastselectedMenuItem;
	private final String DefaultStr = "a";
	private int mPrevCipStatus = 0;
	private TunerID currentTunerID = TunerID.TUNER1;
	private String operatorProfilePackageName = "";
	private CIChangeListener ciChangeListener = null;
	private OpChangeListener opListener = null;
	private boolean ifOPProfLaterPressed = false;
	private boolean isOpInstallationCompleteTrigger = false;
	ITvClockManager mtvclockmanager = null;
	private int CiCamIdForOP = 0;
	private int OpInfoVersion = 0;
	private int Opdeliverysystemhint = 0;
	private boolean opacked = false;
	private boolean NewCamOpInstalled = false;
	private int presetNumber = 0;
	private OpPresentStatus opPresentStatus = OpPresentStatus.WAITING;
	private TimerTask localOPProgTimerTask  = null;
    private Timer     localOPProgTimer      = null;
	private long CachedDemuxHandle = -1;
	
	private SessionHandlerTIF sessionHandlerInstance = null;
	public SESSION_MEDIUM sessionTuneMedium = SESSION_MEDIUM.DVBS2;

	public enum TunerID {
		TUNER1, TUNER2
	}

	public enum MmiType {
		MmiTypeEnquiry(0), MmiTypeMenu(1), MmiTypeList(2);
		private final int value;

		private MmiType(int val) {
			this.value = val;
		}
	}

	public enum OpPresentStatus {
		PRESENT, NOT_PRESENT, WAITING 
	}
	
	public enum CiPlusStatus {
		StatusInactive(0), StatusInitialising(1), StatusInitialsed(2), StatusAuthorised(3), StatusNOTauthorised(4), StatusV1(5);
		private final int value;

		private CiPlusStatus(int val) {
			this.value = val;
		}
	}

	/**
	 * Static block Gets executed before class is instantiated and loads the JNI
	 * library.
	 * 
	 */

	static {
		try {
			System.loadLibrary("satInstallerjni");
		} catch (UnsatisfiedLinkError e) {
			// Log.d(TAG,"Native code library failed to load.\n" + e);
		}
	}

	public void initMainActivityInstance(Context argCtx) {
		mActivityInstance = argCtx;

		if (assetManager == null) {
			Log.d(TAG, "initMainActivityInstance ");
			assetManager = argCtx.getAssets();
		}
	}

	public void setSessionHandler(SessionHandlerTIF argSessionHandler) {
		Log.d(TAG, "setSessionHandler " + argSessionHandler);
		sessionHandlerInstance = argSessionHandler;
	}

	public void setSessionTuneWithMedium(SESSION_MEDIUM argMedium) {
		// at native api wrapper level is already registered so i'll get call
		// back sessionOnChannelRetuned
		Log.d(TAG, "setSessionTuneWithMedium " + argMedium);
		if (ifValidSession()) {
			Bundle bundle = new Bundle();

			sessionTuneMedium = argMedium;

			// populate bundle based on medium
			// ref:
			// http://2k15-xref.tpvision.com:8080/source/xref/device/tpvision/common/plf/tvjar/java/src/org/droidtv/tv/tvinput/ITVSessionContext.java
			String bundleModeString = "";
			if (argMedium == SESSION_MEDIUM.DVBS2) {
				bundleModeString = TvContract.Channels.TYPE_DVB_S2;
			}else if(argMedium == SESSION_MEDIUM.SATIP){
				bundleModeString = ITvContractExtras.TYPE_DVB_SATIP;
			}

			String[] params = { TvContract.Channels.COLUMN_TYPE };
			bundle.putString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE, ITVSessionContext.TUNE_REQUEST_TYPE_CUSTOM);
			bundle.putStringArray(ITVSessionContext.TUNING_PARAMETERS, params);
			bundle.putString(TvContract.Channels.COLUMN_TYPE, bundleModeString);

			//Uri passURI = TvContract.buildChannelsUriForInput(SessionHandlerTIF.CREATE_SESSION_URI);
			//Uri passURI = TvContract.buildChannelUri(0);
			//sessionHandlerInstance.tuneWithBundle(Uri.parse("tv://tuner"), bundle);
			sessionHandlerInstance.tuneWithBundle(bundle);

			// after this the control goes to callback sessionOnChannelRetuned
		}
	}

	public void sessionOnChannelRetuned() {
		// after tuning the call will come here
		Log.d(TAG, "sessionOnChannelRetuned ");

		if (ifValidSession()) {
			if (currentTunerID == TunerID.TUNER1) {
				registerAndReqForOpProf();
			}
			setTunnigParametersForMedium(SESSION_MEDIUM.DVBS2);
			
			if (currentTunerID == TunerID.TUNER1) {
				ntf.notifyAllObservers(EventIDs.NATIVELAYER_INIT_DONE, "");
			} else if (currentTunerID == TunerID.TUNER2) {
				ntf.notifyAllObservers(EventIDs.NATIVELAYER_INIT_DONE_TUNER2, "");
			}
		}
	}
	
	public void createMWInstance() {
		Log.d(TAG, "createMWInstance " + javaSatInstHandler);
		if (javaSatInstHandler == 0) {
			javaSatInstHandler = CreateInstance(0, this);
			loadPrescanXML();
		}
	}

	public void setTunnigParametersForMedium(SESSION_MEDIUM argMedium) {
		Log.d(TAG, "setTunnigParametersForMode " + argMedium);
		if (ifValidSession()) {

			frontendTun = GetTuningInstance();
			if (argMedium == SESSION_MEDIUM.DVBS2) {

				s = sessionHandlerInstance.getSessionContext().getITuningDvbS();
				
				Log.d(TAG, "s: " + s);
				if (s != null) {
					params = new DvbSParams();
					configLNB = new DvbSLNBConfig();
					configCustomLNB = new DvbSCustomLNBConfig();
					configUniCable = new DvbSUnicableConfig();
				}

			}
		}
	}

	void setDemuxIntf()
	{
			long DmxHandle = 0;

			DmxHandle = sessionHandlerInstance.getSessionContext().getDemux();
			Log.d(TAG,"GetDemux token " + DmxHandle + "CachedDemuxHandle " + CachedDemuxHandle);
			if((DmxHandle != 0) && (CachedDemuxHandle != DmxHandle) && (javaSatInstHandler != 0)) {
				setDemuxHandle(DmxHandle);
				CachedDemuxHandle = DmxHandle;
			}
	}
			
	private void loadPrescanXML() {
		Log.d(TAG, "loadPrescanXML Enter");

		assetManager = mActivityInstance.getApplicationContext().getAssets();

		int sizePrescan = 0;
		String PreScanxml = null;
		try {
			InputStream is = assetManager.open("PrescanEntry.xml");
			Log.d(TAG, "SatInstaller: File Opened Sucess");
			sizePrescan = is.available();
			byte[] buffer = new byte[sizePrescan];
			is.read(buffer);
			is.close();
			PreScanxml = new String(buffer);
			// Log.w(TAG, "SatInstaller: " + PreScanxml);
		} catch (IOException e) {
			//e.printStackTrace();
		}

		int sizeSate = 0;
		String SatelliteXml = null;
		try {
			InputStream is = assetManager.open("SatellitePackageList.xml");
			Log.d(TAG, "SatInstaller: Satellite File Opened Sucess");
			sizeSate = is.available();
			byte[] buffer = new byte[sizeSate];
			is.read(buffer);
			is.close();
			SatelliteXml = new String(buffer);
			// Log.w(TAG, "SatInstaller: " + SatelliteXml);
		} catch (IOException e) {
			//e.printStackTrace();
		}
		UpdateConfigXmlStrings(PreScanxml, sizePrescan, SatelliteXml, sizeSate);
		asset_manager_init(assetManager);

		Log.d(TAG, "loadPrescanXML Exit");
	}

	private ITuning GetTuningInstance() {
		Log.d(TAG, "GetTuningInstance Entry");
		ITuning returnFrontendTuner;
		if (frontendTun != null) {
			try {
				Log.d(TAG, "GetTuningInstance unregister");
				frontendTun.unregisterListener(onChangeListener);
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}

		returnFrontendTuner = sessionHandlerInstance.getSessionContext().getITuning();
		if(returnFrontendTuner != null) {
			Log.d(TAG, "registering ");
			try {
				returnFrontendTuner.registerListener(onChangeListener);
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
			Log.d(TAG, "GetTuningInstance Exit");
		}
		return returnFrontendTuner;
	}

	public boolean ifValidSession() {
		boolean returnStatus = false;

		if ((sessionHandlerInstance != null) && (sessionHandlerInstance.getSessionState() != SessionHandlerTIF.SESSION_STATE.INVALID)) {
			returnStatus = true;
		}
		Log.d(TAG, "ifValidSession " + returnStatus);
		return returnStatus;
	}

	public void StopMWInstIfInstExists() {
		Log.d(TAG, "StopMWInstIfInstanceExists Enter " + javaSatInstHandler);
		if (javaSatInstHandler != 0) {
			StopInstallation();
		}
		Log.d(TAG, "StopMWInstIfInstanceExists Exit");
	}

	public void getFrequency_Range(int freqValue[]) {
		freqValue[0] = ITuningDvbS.TUNING_DVBS_START_FREQUENCY;
		freqValue[1] = ITuningDvbS.TUNING_DVBS_END_FREQUENCY;
	}

	private SatInstaller() {
		Log.w(TAG, "SatInstaller() sould not be called directly:");
	}

	public SatInstaller(TunerID argTunerID) {
		currentTunerID = argTunerID;
		if (argTunerID == TunerID.TUNER1) {
			TAG = SatInstaller.class.getName() + currentTunerID;
		} else if (argTunerID == TunerID.TUNER2) {
			TAG = SatInstaller.class.getName() + currentTunerID;
		}

		Log.w(TAG, "SatInstaller:" + argTunerID);

		lastselectedMenuItem = new int[100];
		menuItemcount = 0;
	}

	public void ExitSatInstaller() {
		if (frontendTun != null) {
			Log.w(TAG, "SatInstaller: unregisterListener");
			frontendTun.unregisterListener(onChangeListener);
			frontendTun = null;
		}
	}

	public native int CreateInstance(int tokenId, SatInstaller obj);

	public native int GetCurrentInstallationState();

	public native int GetCurrentInstallationMode();

	public native int StartInstallation(int Source, int Lnb, int Mode);

	public native int StopInstallation();

	public native void ResetInstallation();

	public native int GetNumberOfTvChannelsFound(int Lnb);

	public native int GetNumberofRadioChannelsFound(int Lnb);

	public native int GetNumberOfTvChannelsRemoved(int Lnb);

	public native int GetNumberofRadioChannelsRemoved(int Lnb);

	public native String GetSatelliteName(int Lnb);

	public native int GetNumberOfDigitalChannelsAdded();

	public native int GetNumberOfDigitalChannelsRemoved();

	public native int GetNumberOfDigitalChannelsMoved();

	public native int IdentifyPackagesAvailable();

	public native int GetTotalNumberOfPackagesFound();

	public native int InstallAddedSatellites();

	public native int ResetAddedSatellites();

	public native int RemoveSatelliteEntry(int LnbNumber);

	public native int GetSatelliteSignalStrength(int LnbNumber);

	public native int GetSatelliteSignalQuality(int LnbNumber);

	public native int LoadManualInstallationDefaultValues();

	public native int StoreManualInstallationValues();

	public native int GetAttribute(int Mode, int AttributeId);

	public native int SetAttribute(int Mode, int AttributeId, int Value);

	public native int GetScanProgressStatus(int Mode);

	public native void EnableUnicable(int LnbNumber, boolean Enable);

	public native void StopSignalStrengthMeas(int LnbNumber);

	public native int GetSignalQuality(int Param);

	public native void StartSignalStrengthMeas(int LnbNumber);

	public native int GetSignalStrength(int param);

	public native int StartPredefinedListCopy();

	public native int SetUserPackageIndex(short PackageIndex);

	public native HsvPackageStructure GetPackageByIndex(int Index);

	public native boolean GetUserPackageIndex();

	public native HsvInstalledSatellites GetInstalledSatellites(int mode);

	public native SITableIds GetSITableIds();

	public native HsvSDMSIDataValues GetSIDetails();

	public native String GetPackageName(int pkgid);

	// public native LnbSettingsEntry GetLnbSettings(int index);
	public native int ResetLnbSettings();

	public native int ResetToDefaultLnbSettings();

	public native int GetLNBType();

	public native void SetBouquetIndex(int index);

	public native int GetFirstInstalledChannel();

	// public native void SetLnbSettings(int index, LnbSettingsEntry
	// lnbsettings);
	// public native void SetLnbSettingsviaIndex(int lnbindex,LnbSettingsEntry
	// lnbsettings);
	public native void SaveSatelliteSettingsToPersistent();

	public native void CommitSatelliteSettingsToPersistent();

	public native void SetUnicableUBNumber(int ubNum);

	public native void SetUnicableUBFreq(int ubFrequency);

	public native void UpdateConfigXmlStrings(String PrescanXmlString, int PrescanXmlStringLen, String SatellitePackageXmlString, int SatellitePackageXmlStringLen);

	public native void asset_manager_init(AssetManager assetObject);

	public native int GetSatId(int index);

	public native int getLnbStatus(int index);

	public native int GetHighLoFreq(int index);

	public native int GetLnbType(int index);

	public native int GetLowLoFreq(int index);

	public native byte GetToneControl(int index);

	public native byte GetLnbPower(int index);

	public native byte GetUserBand(int index);

	public native int GetUserFrequency(int index);

	public native boolean GetUpdateInstallEnabled(int index);

	// Notification Native Calls
	public native int onScanAborted_JNICall();

	public native int onScanEnded_JNICall();

	public native int onScanningStandardDetected_JNICall(int arg0, int arg1);

	public native int onTuned_JNICall(int arg0, int arg1);

	public native void OnOpSearchStatus(OperatorProfileSearchStatus opStatus);

	public native void OnOpStatusInfo(OperatorProfileStatusInfo statusInfo);

	public native void OnOpNIT(OperatorProfileNitData nitData);

	public native void OnOpTune(OperatorProfileTuneData tuneData);

	public native void setPostCode(int pCodeLen, String pCode);

	public native void setConnectionType(int CntType, int DualTunerEnabled);

	public native void SelectLNBForUpdate(int index, boolean flag);

	public native void setLnbpower(int index, byte poweroff);

	public native void settotone(int index, byte tone);

	public native void setlnbLowLoFrequency(int index, int frequency);

	public native void setlnbHighLoFrequency(int index, int frequency);

	public native void SetUnicableUBFreqTuner2(int frequency, int tunerType);

	public native int GetUnicableUBFreqTuner2(int tunerType2);

	public native void SetUnicableUBNumberTuner2(int ubNum);

	public native void OnCAMStatusChanged(int status);
	
	public native void startTricolorRegionParsing();
	public native void setTricolorRegionIndex(int selectedRegionIndex);
	public native String[] getTricolorRegionNames ();

	/*** TVPROVIDER IMPLEMENTATION START ***/
	public native int GetNumberOfDatabaseRecords(int TSDataOnly);
	public native SatInstallerTvProviderData GetTvProviderBlobDataByIndex(int Index, int TSDataOnly);
	public native void PopulateMW(SatInstallerTvProviderData TvpData, int Clear);
	public native void syncUniqueIdToMW (SatInstallerTvProviderData TvpData);

	/*** TVPROVIDER IMPLEMENTATION END ***/

	public native void setDemuxHandle(long demuxHandle);

	public int SatInstaller_onEvent(int eventid, int val) {
		Log.d(TAG, "onEvent from native eventid: " + eventid + " val: " + val);
		Log.d(TAG, "thread id : " + android.os.Process.myTid());

		// InstallationState insState = GetCurrentInstallationState();

		if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsStarted) {
			Log.d(TAG, "onEvent from native EVENT_INS_STARTED");
			presetNumber = 0;
			if (GetCurrentInstallationMode() == MwDataTypes.IHsvSatelliteInstallation_InstallationBackground)
			{
				Log.d(TAG,"Sending Installation start in case of background ");
				ntf.notifyAllObservers(EventIDs.EVENT_INST_STARTED, "");
			}
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsStopped) {
			Log.d(TAG, "onEvent from native EVENT_INS_STOPPED");
			ntf.notifyAllObservers(EventIDs.EVENT_INS_STOPPED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsCompleted) {
			Log.d(TAG, "onEvent from native EVENT_INS_COMPLETED");
			ntf.notifyAllObservers(EventIDs.SERVICE_SCAN_COMPLETE, "");
			if(isOperatorProfileSupported() == false)
			unRegisterCIListener();
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsFailed) {
			Log.d(TAG, "onEvent from native EVENT_INS_FAILED");
			ntf.notifyAllObservers(EventIDs.INSTALLATION_FAILED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSatelliteFound) {
			Log.d(TAG, "onEvent from native EVENT_SATELLITE_FOUND");
			ntf.notifyAllObservers(EventIDs.PRESCAN_SUCCESS, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSatelliteNotFound) {
			Log.d(TAG, "onEvent from native EVENT_SATELLITE_NOTFOUND");
			ntf.notifyAllObservers(EventIDs.PRESCAN_FAIL, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSortingStarted) {
			Log.d(TAG, "onEvent from native EVENT_SORTING_STARTED");
			ntf.notifyAllObservers(EventIDs.SORTING_STARTED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSortStopped) {
			Log.d(TAG, "onEvent from native EVENT_SORT_STOPPED");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSortCompleted) {
			Log.d(TAG, "onEvent from native EVENT_SORT_COMPLETED");
			ntf.notifyAllObservers(EventIDs.SERVICE_SCAN_COMPLETE, "");
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.EVENT_INST_COMPLETED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSortInProgress) {
			Log.d(TAG, "onEvent from native EVENT_SORT_INPROGRESS");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventChannelFound) {
			Log.d(TAG, "onEvent from native EVENT_CHANNEL_FOUND");
			ntf.notifyAllObservers(EventIDs.SERVICE_SCAN_UPDATE, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventChannelNotFound) {
			Log.d(TAG, "onEvent from native EVENT_CHANNEL_NOTFOUND");
			ntf.notifyAllObservers(EventIDs.MANUAL_INSTALL_FAILED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsProgress) {
			Log.d(TAG, "onEvent from native EVENT_INS_PROGRESS");
			ntf.notifyAllObservers(EventIDs.PRESCAN_UPDATE, "");
			ntf.notifyAllObservers(EventIDs.SERVICE_SCAN_UPDATE, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsCompletedForLnb) {
			Log.d(TAG, "onEvent from native EVENT_INS_COMPLETEDFORLNB");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSatLnbRemovalCompleted) {
			Log.d(TAG, "onEvent from native EVENT_SAT_LNB_REMOVAL_COMPLETE");
			ntf.notifyAllObservers(EventIDs.SATELLITE_REMOVED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventContentLibRead) {
			Log.d(TAG, "onEvent from native EVENT_CONTENT_LIBREAD");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPkgInstallStart) {
			Log.d(TAG, "onEvent from native EVENT_PKG_INSTALLSTART");
			ntf.notifyAllObservers(EventIDs.PACKAGE_INSTALL_STARTED, "");
		}else if(eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventCamNitInstallation){
			Log.d(TAG,"onEvent from native CAM_NIT_INSTALLATION");
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.CAM_NIT_INSTALLATION,"");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPkgInstallEnd) {
			Log.d(TAG, "onEvent from native EVENT_PKG_INSTALL_END");
			ntf.notifyAllObservers(EventIDs.PACKAGE_INSTALL_FINISHED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventLNBStart) {
			Log.d(TAG, "onEvent from native EVENT_LNBSTART");
			ntf.notifyAllObservers(EventIDs.LNB_INSTALL_STARTED, String.valueOf(val));
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventLNBEnd) {
			Log.d(TAG, "onEvent from native EVENT_LNBEND");
			ntf.notifyAllObservers(EventIDs.LNB_INSTALL_FINISHED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSatLnbRemovalStarted) {
			Log.d(TAG, "onEvent from native EVENT_SAT_LNBREMOVALSTARTED");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSatRemovalCompleted) {
			Log.d(TAG, "onEvent from native IHsvSatelliteInstallationNotify_EventSatRemovalCompleted");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPackageInstallFailed) {
			Log.d(TAG, "onEvent from native EventPackageInstallFailed");
			ntf.notifyAllObservers(EventIDs.INSTALLATION_FAILED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPackageId) {

		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPredefinedListCopySuccesful) {

		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPredefinedListCopyGenericError) {

		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPredefinedListCopyOlderVersion) {

		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventDifferentSatelliteFound) {
			ntf.notifyAllObservers(EventIDs.FOUND_DIFFERENT_SATELLITE, "");

		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPkgParsingStarted) {

		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPkgParsingCompleted) {
			Log.d(TAG, "onEvent from native EventPkgParsingCompleted");
			ntf.notifyAllObservers(EventIDs.PACKAGE_LIST_CREATED, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventTriggerBckgndUpdateInstall) {
			Log.d(TAG, "onEvent from native EventTriggerBckgndUpdateInstall");
			//ntf.notifyAllObservers(EventIDs.TRIGGER_BACKGROUND_UPDATE_INSTALL, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsOpProfileRequestNormal) {
			Log.d(TAG, "onEvent from native EventInsOpProfileRequestNormal");
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.OP_PROFILE_INSTALL_REQUEST_URGENT, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsOpProfileRequestUrgent) {
			Log.d(TAG, "onEvent from native EventInsOpProfileRequestUrgent");
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.OP_PROFILE_INSTALL_REQUEST_URGENT, "");
		} else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventInsOpProfileRequestImmediate) {
			Log.d(TAG, "onEvent from native EventInsOpProfileRequestImmediate");
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.OP_PROFILE_INSTALL_REQUEST_IMMEDIATE, "");
		}
		else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventRegionScanEnd) {
			Log.d(TAG, "onEvent from native EventRegionScanEnd");
			ntf.notifyAllObservers(EventIDs.REGION_SCAN_END, "");
		}
		else if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventSetDateTime) {
			Log.d(TAG, "Date & Time Received in OP Installation");
			SetDateTime(String.valueOf(val));
		}
		if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPresetAdded) {
			ntf.notifyAllObservers(EventIDs.MAJORVERSION_UPDATE, "");
		}
		if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventPresetDeleted) {
			presetNumber = val;
			Log.d(TAG, "onEvent from native DELETED PRESET " + presetNumber);
			
			ntf.notifyAllObservers(EventIDs.MAJORVERSION_UPDATE, "");		
		}
		if (eventid == MwDataTypes.IHsvSatelliteInstallationNotify_EventUpdated) {
			ntf.notifyAllObservers(EventIDs.MAJORVERSION_UPDATE, "");
		}
		
		return 0;
	}
	public int getDeletedPresetNumber()
	{
		return presetNumber;
	}
	
	public void SetDateTime(String timesecs)
	{
		int l_installState = GetCurrentInstallationMode();
		Log.d(TAG, "Entered into setdatetime call");
		int ChangeDateinsecs = GetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributeChangeDate);
		int nextTimeOffset = GetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributeNextTimeOffset);
		int timeOffset = GetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributeTimeOffset);
		long text = 1000 * ChangeDateinsecs;
		/*
		* set next lto : so that if set time is called then clock
		 * service will check for next lto date is reached, if so
		 * then next time offset will be set by clock service
		 */

		Log.d(TAG, "changeDate = " + text);
		if((ifValidSession()) && (mtvclockmanager != null))
		if (text > 0) {
			mtvclockmanager.SetNextLtoChange(text,(int) (nextTimeOffset* 1000),ITvClockManager.eClockSources.TOT);
			Log.d(TAG, "NEXT LTO TIME[" + text + "ms]"+ "NEXT LTO OFFSET["+ nextTimeOffset+ "]");
		}

		/* set time from TOT */
		text = 1000 * Long.parseLong(String.valueOf(timesecs));
		Log.d(TAG, "datetime = " + text);
		mtvclockmanager = ITvClockManager.Instance.getInterface();
		if((ifValidSession()) && (mtvclockmanager != null))
		if (text > 0) {
			Log.d(TAG, "TIME CHANGED TO : " + text + " ms");
			mtvclockmanager.SetTime(text,(timeOffset * 1000),ITvClockManager.eClockSources.TOT);
		}
	}
	public void SetUnicableUBFreqTuner(int freq) {
		if (TunerID.TUNER2 == currentTunerID) {
			SetUnicableUBFreqTuner2(freq, 1);
		} else {
			SetUnicableUBFreqTuner2(freq, 0);
		}
	}

	public int GetUnicableUBFreqTuner() {
		int frequency;
		Log.d(TAG, "GetUnicableUBFreqTuner TunerID " + currentTunerID);

		frequency = GetUnicableUBFreqTuner2(1);

		Log.d(TAG, "GetUnicableUBFreqTuner " + frequency);
		return frequency;
	}

	public int getParams_SatInst(final int retparams[]) {
		Log.d(TAG, "getParams_SatInst ");
		getParams();
		retparams[0] = params.constel;
		retparams[1] = params.symbolrate;
		retparams[2] = params.polarization;
		retparams[3] = params.lock;
		retparams[4] = params.LnbNumber;
		retparams[5] = params.sqi;
		retparams[6] = params.ssi;
		retparams[7] = params.ber;
		Log.d(TAG, "getParams_SatInst exit");
		return 0;
	}

	public int configureLNB_SatInst(final int LNBType, final int LNBNumber, final int UserBandNumber, final int UserBandFrequency, final int BurstSelect, final int Tone, final int Custom_High_LO,
			final int Custom_Low_LO, final int CustomPow) {
		int ret = -1;
		Log.d(TAG, "ConfigureLNB_SatInst " + "LnbType " + LNBType + "LnbNumber " + LNBNumber + "UBNum " + UserBandNumber + "UBFreq " + UserBandFrequency + "High LO " + Custom_High_LO + "Low_LO "
				+ Custom_Low_LO + "CustomPow " + CustomPow);
		if (s != null) {
			configLNB.LNBType = LNBType;
			configLNB.LNBNumber = LNBNumber;
			configLNB.LUserBandNumber = UserBandNumber;
			configLNB.LUserBandFrequency = UserBandFrequency;
			configLNB.BurstSelect = BurstSelect;
			configLNB.Tone = Tone;
			configCustomLNB.Custom_High_LO_Value = Custom_High_LO;
			configCustomLNB.Custom_Low_LO_Value = Custom_Low_LO;
			configCustomLNB.CustomPow = CustomPow;

			s.configureLNB(configLNB, configCustomLNB);
			/*
			 * if (ret != 0) { Log.d (TAG, "ConfigureLNB failed "+"ret "+ret); }
			 */
		}
		Log.d(TAG, "configureLNB_SatInst exit");
		return ret;
	}

	public int configureUnicable_SatInst(final int UserBandNumber, final int UserBandFrequency) {
		int ret = -1;

		Log.d(TAG, "configureUnicable_SatInst" + "UBNumber" + UserBandNumber + "UBF" + UserBandFrequency);

		/*
		 * This API will be removed, only Configure LNB to be used for Unicable
		 * also
		 */
		/*
		 * if(s != null) { configUniCable.UserBandNumber = UserBandNumber;
		 * configUniCable.UserBandFrequency = UserBandFrequency;
		 * 
		 * ret = s.configureUnicable (configUniCable); if (ret != 0) { Log.d
		 * (TAG, "configureUnicable failed" + "ret" + ret); } }
		 */

		return ret;
	}

	public int setPolarization_SatInst(final int polarization) {
		int ret = -1;

		Log.d(TAG, "setPolarization_SatInst" + "polarization" + polarization);
		if (s != null) {
			try {
				s.setPolarization(polarization);
				/*
				 * if (ret != 0) { Log.d (TAG, "SetPolarization failed" + "ret"
				 * + ret); }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		return ret;
	}

	public int setSymbolRate_SatInst(final int srdetectmode, final int symbolrate) {
		int ret = -1;

		Log.d(TAG, "setSymbolRate_SatInst" + "DetectMode" + srdetectmode + "symbolrate" + symbolrate);
		if (s != null) {
			try {
				s.setSymbolRate(srdetectmode, symbolrate);
				/*
				 * if (ret != 0) { Log.d (TAG, "setSymbolRate failed " + "ret" +
				 * ret); }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		return ret;
	}

	public int setPLP_SatInst(final int plpid) {
		int ret = -1;

		Log.d(TAG, "setPLP_SatInst" + "plpid " + plpid);
		if (s != null) {
			try {
				s.setPLP((byte) plpid);
				/*
				 * if (ret != 0) { Log.d (TAG, "setPLP failed " + "ret" + ret);
				 * }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		return ret;
	}

	public int setBand_SatInst(final int band) {
		int ret = -1;

		Log.d(TAG, "setBand_SatInst" + "band " + band);
		if (s != null) {
			try {
				s.setBand(band);
				/*
				 * if (ret != 0) { Log.d (TAG, "setBand failed " + "ret" + ret);
				 * }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		return ret;
	}

	public int getValueFromContentProvider_SatInst(final int id, final int val[]) {
		Log.d(TAG, "getValue_FromContentProvider" + "id " + id);
		int ret = 0;

		int channel = m_settings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2, 0, 0);
		val[0] = NativeAPIWrapper.getInstance().getChannelfromID(channel);
		Log.d(TAG, "getValue_FromContentProvider" + val[0]);

		return 0;
	}

	public int setLNBConnectionType_SatInst(final int connectiontype) {
		int ret = -1;

		Log.d(TAG, "setLNBConnectionType_SatInst" + "connectiontype " + connectiontype);
		if (s != null) {
			try {
				s.setLNBConnectionType(connectiontype);
				/*
				 * if (ret != 0) { Log.d (TAG, "setLNBConnectionType failed " +
				 * "ret" + ret); }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		return ret;
	}

	public int GetCountry() {
		Log.d(TAG, "GetCountry entry");
		int l_countryId = 0;
		l_countryId = m_settings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		Log.d(TAG, "GetCountry returning" + String.valueOf(l_countryId));
		return l_countryId;
	}
	public int setSatIPParams_SatInst(final int modsys,final int modtype,final int RollOff,final int fec,final int pilots) {
		int ret = -1;

		Log.d(TAG, "setSatIPParams_SatInst" + "modsys " + modsys + "modtype " + modtype + "RollOff " + RollOff + "fec " + fec + "pilots " + pilots);
		if (s != null) {
			try {
				s.setModulationSystem(modsys); 
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
			
			try {
				s.setModulationType(modtype); 
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}

			try {
				s.setRollOffFactor(RollOff); 
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}

			try {
				s.setFECInner(fec); 
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}

			try {
				s.setPilots(pilots); 
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}

		}
		return ret;
	}

	public int[] getSymbolRateRange() {
		int[] returnSymRateRange = new int[2];
		Log.d(TAG, "getSymbolRateRange");
		returnSymRateRange[0] = ITuningDvbS.TUNING_DVBS_SYMBOLRATE_MIN;
		returnSymRateRange[1] = ITuningDvbS.TUNING_DVBS_SYMBOLRATE_MAX;
		return returnSymRateRange;
	}

	public int GetCurrentLNB() {
		int getCurrentLNB = 0;
		Log.d(TAG, "GetCurrentLNB entry");
		getParams();
		if (params != null) {
			getCurrentLNB = params.LnbNumber;
		} else {
			Log.d(TAG, "GetCurrentLNB Params is NULL ");
		}

		Log.d(TAG, "GetCurrentLNB exit");
		return getCurrentLNB;
	}

	public int tune_SatInst(final int freq, final boolean finetune) {
		int ret = -1;

		Log.d(TAG, "tune_SatInst" + "freq" + freq + "finetune" + finetune);
		if (frontendTun != null) {
			try {
				frontendTun.tune(freq, finetune);
				/*
				 * if (ret != 0) { Log.d (TAG, "tune failed " + "ret" + ret); }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		Log.d(TAG, "tune_SatInst exit");
		return ret;
	}

	public int getFreq_SatInst(final int freq[]) {
		Log.d(TAG, "getFreq_SatInst entry");
		int ret = -1;
		if (frontendTun != null) {
			try {
				freq[0] = frontendTun.getFreq();
				/*
				 * if(ret != 0) { Log.d(TAG,
				 * "getFrequency_JavInst Freq Failed with Return Value" + ret);
				 * }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
				freq[0] = 0;
			}
		}
		Log.d(TAG, "getFreq_SatInst returning" + freq[0]);

		return ret;
	}

	public int scanStart_SatInst(final int startfreq, final int endfreq, final boolean scanforward) {
		int ret = -1;

		Log.d(TAG, "scanStart_SatInst entry" + "StartFreq" + startfreq + "EndFreq " + endfreq + "scanfwd " + scanforward);
		if (frontendTun != null) {
			try {
				frontendTun.scanStart(startfreq, endfreq, scanforward);
				/*
				 * if (ret != 0) { Log.d (TAG, "scanStart failed " + "ret" +
				 * ret); }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		Log.d(TAG, "scanStart_SatInst exit");
		return ret;
	}

	public int scanAbort_SatInst() {
		int ret = -1;

		Log.d(TAG, "scanAbort_SatInst");
		if (frontendTun != null) {
			try {
				frontendTun.scanAbort();
				/*
				 * if (ret != 0) { Log.d (TAG, "scanAbort failed " + "ret" +
				 * ret); }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		Log.d(TAG, "scanAbort_SatInst exit");
		return ret;
	}

	public int mscanNext_SatInst() {
		int ret = -1;

		Log.d(TAG, "mscanNext_SatInst entry");
		if (frontendTun != null) {
			try {
				frontendTun.scanNext();
				/*
				 * if (ret != 0) { Log.d (TAG, "scanNext failed " + "ret" +
				 * ret); }
				 */
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		Log.d(TAG, "mscanNext_SatInst exit");
		return ret;
	}

	public int getSigQuality_SatInst(int ssm, int Strength) {
		int sigQuality = 0;
		Log.d(TAG, "getSigQuality_SatInst entry");
		getParams();
		if (params != null) {
			sigQuality = params.sqi;
		} else {
			Log.d(TAG, "getSigQuality_SatInst params is null");
		}
		Log.d(TAG, "getSigQuality_SatInst sigQuality: " + sigQuality);

		return sigQuality;
	}

	public int getSigStrength_SatInst(int ssm, int Strength) {
		int sigStrength = 0;
		Log.d(TAG, "getSigStrength_SatInst entry");
		getParams();
		if (params != null) {
			sigStrength = params.ssi;
		} else {
			Log.d(TAG, "getSigStrength_SatInst params is null");
		}

		Log.d(TAG, "getSigStrength_SatInst sigStrength: " + sigStrength);
		return sigStrength;
	}

	public int getSigStrengthRange_SatInst(int MinStrength, int MaxStrength) {
		Log.d(TAG, "getSigStrengthRange_SatInst");
		return 0;
	}

	public int getBer_SatInst(int Ber) {
		Log.d(TAG, "getBer_JavaInst");
		return 0;
	}

	public void requestStatusInfo_SatInst() {
		Log.d(TAG, "requestStatusInfo_SatInst");
		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				opIntf.requestOpStatusInfo();
			}
		} else {
			Log.d(TAG, "invalid session requestStatusInfo_SatInst");
		}
	}

	public void requestStatusInfoOnInsCompletion(){
		Log.d(TAG, "requestStatusInfoOnInsCompletion");
		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				isOpInstallationCompleteTrigger = true;
				opIntf.requestOpStatusInfo();
			}
		} else {
			Log.d(TAG, "invalid session requestStatusInfo_SatInst");
		}			
	}
	public void requestNit_SatInst() {
		Log.d(TAG, "requestNit_SatInst");
		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				opIntf.requestOpNit();
			}
		} else {
			Log.d(TAG, "invalid session requestNit_SatInst");
		}
	}

	public void sendOpExit_SatInst() {
		Log.d(TAG, "sendOpExit_SatInst");
		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				opIntf.sendOpExit();
			}
		} else {
			Log.d(TAG, "invalid session sendOpExit_SatInst");
		}
	}

	public void sendOpAck_SatInst() {
		Log.d(TAG, "sendOpAck_SatInst");
		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				opIntf.sendOpEntAck();
			}
			opacked = true;
		} else {
			Log.d(TAG, "invalid session sendOpAck_SatInst");
		}
	}

	public void sendOpSearchCancel_SatInst() {
		Log.d(TAG, "sendOpSearchCancel_SatInst");
		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				opIntf.sendOpSearchCancel();
			}
		} else {
			Log.d(TAG, "invalid session sendOpSearchCancel_SatInst");
		}
	}

	public void sendOperatorSearchStart_SatInst(OperatorSearchSettings opSearchSettings) {
		Log.d(TAG, "sendOperatorSearchStart_SatInst");
		int i = 0;
		OpSearchSettings settings = new OpSearchSettings();

		// hardcoded values
		opSearchSettings.Unattended_Flag = 1;//Fransat fix
		opSearchSettings.Service_Type_Length = 17;

		int serviceArray[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x10, 0x0A, 0x0C, 0x11, 0x16, 0x17, 0x18, 0x19, 0x1C, 0x20, 0x21 };

		for (i = 0; i < opSearchSettings.Service_Type_Length; i++) {
			opSearchSettings.Service_Type[i] = serviceArray[i];
		}

		opSearchSettings.Delivery_Cap_Length = 2;
		int deliveryArray[] = { 67, 121 };

		for (i = 0; i < opSearchSettings.Delivery_Cap_Length; i++) {
			opSearchSettings.Delivery_Capability[i] = deliveryArray[i];
		}

		opSearchSettings.Application_Cap_Length = 0;
		// hardcoded values

		Log.d(TAG, "opSearchSettings.Unattended_Flag " + opSearchSettings.Unattended_Flag);
		Log.d(TAG, "opSearchSettings.Service_Type_Length " + opSearchSettings.Service_Type_Length);

		settings.Unattended_Flag = opSearchSettings.Unattended_Flag;
		settings.Service_Type_Length = opSearchSettings.Service_Type_Length;

		for (i = 0; i < opSearchSettings.Service_Type_Length; i++) {
			settings.Service_Type[i] = opSearchSettings.Service_Type[i];
			Log.d(TAG, "opSearchSettings.Service_Type [" + i + "] " + opSearchSettings.Service_Type[i]);
		}

		settings.Delivery_Cap_Length = opSearchSettings.Delivery_Cap_Length;
		Log.d(TAG, "opSearchSettings.Delivery_Cap_Length " + opSearchSettings.Delivery_Cap_Length);

		for (i = 0; i < opSearchSettings.Delivery_Cap_Length; i++) {
			settings.Delivery_Capability[i] = opSearchSettings.Delivery_Capability[i];
			Log.d(TAG, "opSearchSettings.Delivery_Capability [" + i + "] " + opSearchSettings.Delivery_Capability[i]);
		}

		Log.d(TAG, "opSearchSettings.Application_Cap_Length " + opSearchSettings.Application_Cap_Length);
		settings.Application_Cap_Length = opSearchSettings.Application_Cap_Length;

		for (i = 0; i < opSearchSettings.Application_Cap_Length; i++) {
			settings.Application_Capability[i] = opSearchSettings.Application_Capability[i];
			Log.d(TAG, "opSearchSettings.Application_Capability [" + i + "] " + opSearchSettings.Application_Capability[i]);
		}

		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				registerCIListener();
				opIntf.sendOpSearchStart(settings);
			}
		} else {
			Log.d(TAG, "invalid session sendOperatorSearchStart_SatInst");
		}
	}

	public void sendOpTuneStatus_SatInst(OperatorTuneStatus tuneStatus) {
		Log.d(TAG, "sendOpTuneStatus_SatInst");
		int i = 0;
		OPTuneStatus status = new OPTuneStatus();

		status.Descriptor_Number = tuneStatus.Descriptor_Number;
		status.Signal_Strength = tuneStatus.Signal_Strength;
		status.Signal_Quality = tuneStatus.Signal_Quality;
		status.Status = tuneStatus.Status;
		status.TuneDataLength = tuneStatus.Descriptor_Loop_Length;

		for (i = 0; i < status.TuneDataLength; i++)
			status.TuneData[i] = tuneStatus.Descriptor_Loop[i];

		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				opIntf.sendOpTuneStatus(status);
			}
		} else {
			Log.d(TAG, "invalid session sendOpTuneStatus_SatInst");
		}
	}

	public void mCacheOperatorData_JavaInst() {
		Log.d(TAG, "mCacheOperatorData_JavaInst");
		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				opIntf.storeOperatorData();
			}
		} else {
			Log.d(TAG, "invalid session mCacheOperatorData_JavaInst");
		}
	}

	public OperatorProfileStatusInfo getStoredOperatorData_SatInst() {
		Log.d(TAG, "getStoredOperatorData_SatInst");
		OpProfileStatusInfo info = null;

		if (ifValidSession()) {
			ITvMediaOp opIntf = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(opIntf != null) {
				info = opIntf.getStoredOperatorData();
			}
		} else {
			Log.d(TAG, "invalid session getStoredOperatorData_SatInst");
		}

		OperatorProfileStatusInfo Info = null;
		if (info != null) {
			Info = new OperatorProfileStatusInfo(info);
		}
		return Info;
	}

	public int getCipStatus_SatInst() {

		int status = 0;

		Log.d(TAG, "getCipStatus_SatInst");

		if (ifValidSession()) {
			ITvMediaCI tvMediaCi = sessionHandlerInstance.getSessionContext().getITvMediaCI();
			if(tvMediaCi != null) {
				status = tvMediaCi.getCipStatus();
			}
		} else {
			Log.d(TAG, "invalid session getCipStatus_SatInst");
		}
	
		return status;
	}

	public void registerAndReqForOpProf() {
		Log.d(TAG, "registerForOpProf called");
		
		if (ifValidSession()) {

			if (null == tvMop) {
								
				tvMop = sessionHandlerInstance.getSessionContext().getITvMediaOp();
				
				if (null != tvMop) {
					Log.d(TAG, "Got TV Media Op Instance:" + tvMop);

					// register only once
					if (opListener == null) {
						opListener = new OpChangeListener();
						tvMop.registerOpChangeListener((IOnOpChangeListener) opListener);
					}
					tvMop.requestOpStatusInfo();
					Log.d(TAG, "Got TV Media Op Instance");
				} else {
					Log.d(TAG, "TV Media Op Instance is NULL");
				}
			}
			
			if (null == tvMci) {
				tvMci =  sessionHandlerInstance.getSessionContext().getITvMediaCI();
			}
		} else {
			Log.d(TAG, "invalid session registerAndReqForOpProf");
		}
	}

	public void registerCIListener() {
		Log.d(TAG, "registerCIListener called");
		if(ifValidSession()){
			ITVCIControl tvCiControl = sessionHandlerInstance.getSessionContext().getITVCIControl();
			if(tvCiControl != null) {
				tvCiControl.enableCAMUI(true);
			}
		}
	}

	public void unRegisterCIListener() {
		Log.d(TAG, "unRegisterCIListener called");
		if(ifValidSession()){
			ITVCIControl tvCiControl = sessionHandlerInstance.getSessionContext().getITVCIControl();
			if(tvCiControl != null) {
				tvCiControl.enableCAMUI(false);
			}
		}
	}

	public void SetHostControlStatus(boolean OnOff) {
		if(ifValidSession()){
			if (tvMci != null) {
				Log.d(TAG, "SatInstaller:HostControl  " + OnOff);
				tvMci.hCEnable(OnOff, 1);
			}
		}
	}

	public void setTunerModeToIdle(boolean ifActive) {
		Log.d(TAG, "setTunerModeToIdle " + ifActive + " s:" + s);
		if(ifValidSession()){
			if (s != null) {
				if (ifActive) {
					try {
						s.setIdleMode(1);
					}
					catch (Exception e) {
					}
				} else {
					try {
						s.setIdleMode(0);
					}
					catch (Exception e) {
					}

				}
			}
		}
	}

	public int GetPolarization() {
		int getPolar = 0;
		Log.d(TAG, "GetPolarisation entry");
		getParams();
		if (params != null) {
			getPolar = params.polarization;
		} else {
			Log.d(TAG, "GetPolarisation param is NULL ");
		}
		Log.d(TAG, "GetPolarisation exit");
		return getPolar;
	}

	public int GetSymbolRate() {
		int getSymbolRate = 0;
		Log.d(TAG, "GetSymbolRate entry");
		getParams();
		if (params != null) {
			getSymbolRate = params.symbolrate;
		} else {
			Log.d(TAG, "GetSymbolRate param is NULL ");
		}
		Log.d(TAG, "GetSymbolRate exit");
		return getSymbolRate;
	}

	public void setSurface(Surface p_surface) {
        if (ifValidSession()) {
			sessionHandlerInstance.setSurface(p_surface);
		}
		//tvMpl.setSurface(p_surface);
		//tvMpl.start();
	}

	public int getParams() {
		Log.d(TAG, "getParams entry");
		if(ifValidSession()){
			if (s != null) {
				try {
					s.getParams(params);
				} catch (IllegalStateException e) {
					//e.printStackTrace();
				}
			}
			Log.d(TAG, "getParams exit");
		}
		return 0;
	}

	public int configureLNB() {
		Log.d(TAG, "configureLNB ");
		return 0;
	}

	public int configureUnicable() {
		Log.d(TAG, "configureUnicable ");
		return 0;
	}

	public int setPolarization() {
		Log.d(TAG, "setPolarization ");
		return 0;
	}

	public int setSymbolRate() {
		Log.d(TAG, "setSymbolRate ");
		return 0;
	}

	public int setPLP() {
		Log.d(TAG, "setPLP ");

		return 0;
	}

	private OnChangeListener onChangeListener = new OnChangeListener() {

		public int onScanningStandardDetected(ITuning.paramsOnScanningStandardDetected scanStdParam) {
			Log.d(TAG, "onScanningStandardDetected Listner");
			if (currentTunerID == TunerID.TUNER1) {
				onScanningStandardDetected_JNICall(scanStdParam.std, scanStdParam.freq);
			}
			return 0;
		}

		public int onScanAborted() {
			Log.d(TAG, "onScanAborted Listner");
			if (currentTunerID == TunerID.TUNER1) {
				onScanAborted_JNICall();
			}
			return 0;
		}

		public int onScanEnded() {
			Log.d(TAG, "onScanEnded Listner");
			if (currentTunerID == TunerID.TUNER1) {
				onScanEnded_JNICall();
			}
			return 0;
		}

		public int onTuned(ITuning.paramsOnTuned onTunedParams) {
			Log.d(TAG, "#### onTuned Listner");
			if (currentTunerID == TunerID.TUNER1) {
				onTuned_JNICall(onTunedParams.tuningresult, onTunedParams.freq);
			}
			return 0;
		}
	};

	public void SetConnectionType(int CntType) {

		if (TunerID.TUNER2 == currentTunerID) {
			setConnectionType(CntType, 1);
		} else {
			setConnectionType(CntType, 0);

		}
	}

	/****************************** MMI Calls ******************************/
	public boolean setMmiEnable() {
		Log.d(TAG, "Entered setMmiEnable");
		if(tvMci != null)
			tvMci.mmiEnable();
		return true;
	}

	public boolean setMmiDisable() {
		Log.d(TAG, "Entered setMmiDisable");
		if(tvMci != null)
			tvMci.mmiDisable();
		return true;
	}

	public void setMMIInProgress(boolean mmiProgress) {
		mMMIInProgress = mmiProgress;
	}

	public boolean setExitResponse() {
		boolean retval = true;
		if(tvMci != null) 
		{
			if (tvMci.mmiClose(currentMmiID)) {
				Log.d(TAG, "MMI Closed so resetting last selected Menu Index");
				mLastSelectedMenuIndex = 0;
			} else {
				Log.d(TAG, "MMI Close not successful");
				retval = false;
			}
		}
		return (retval);
	}

	public boolean setExitToOSD() {
		// send event to UI handler...event_OnEvent(evids_CIExitCIState);
		// mNotificationHandler.notifyAllObservers(EventIDs.CI_EXIT_CI_STATE,
		// "");
		return true;
	}

	public boolean setMmiOKMenuCmdResponse(int choice) {
		Log.d(TAG, "setMmiOKMenuCmdResponse: choice = " + choice);
		Log.d(TAG, "setMmiOKMenuCmdResponse: CurrentMmiID = " + currentMmiID);
		CIMmiResponse CmdEnqRes = new CIMmiResponse();
		CmdEnqRes.SelectIndex = choice;
		// mLastSelectedMenuIndex = choice;
		if (menuItemcount >= 0) {
			lastselectedMenuItem[menuItemcount++] = choice;
		}
		CmdEnqRes.ResponseString = DefaultStr;

		if (mmiMenuCmd.NumberOfChoices > 0) {
			if(tvMci != null)
				tvMci.mmiCmdResponse(currentMmiID, MmiType.MmiTypeMenu.value, CmdEnqRes);
		}
		return true;
	}

	public boolean setMmiCancelMenuCmdResponse() {
		Log.d(TAG, "setMmiCancelMenuCmdResponse is called");
		CIMmiResponse CmdEnqRes = new CIMmiResponse();
		CmdEnqRes.SelectIndex = 0;
		CmdEnqRes.ResponseString = DefaultStr;
		if (menuItemcount > 0) {
			--menuItemcount;
		}
		if(tvMci != null)
			tvMci.mmiCmdResponse(currentMmiID, MmiType.MmiTypeMenu.value, CmdEnqRes);
		return true;
	}

	public CIMmiMenuList getMmiMenuItems() {
		Log.d(TAG, "getMmiMenuItems is called");
		return mmiMenuCmd;
	}

	public int getLastSelectedMenuIndex() {
		Log.d(TAG, "Count value is  " + menuItemcount);
		return lastselectedMenuItem[menuItemcount];
	}

	public boolean setMmiOKListCmdResponse(int choice) {
		Log.d(TAG, "setMmiOKListCmdResponse is called with choice " + choice);
		CIMmiResponse CmdEnqRes = new CIMmiResponse();
		CmdEnqRes.SelectIndex = choice;
		CmdEnqRes.ResponseString = DefaultStr;

		if (mmiListCmd.NumberOfChoices > 0) {
			if(tvMci != null)
				tvMci.mmiCmdResponse(currentMmiID, MmiType.MmiTypeList.value, CmdEnqRes);
		}
		return true;
	}

	public boolean setMmiCancelListCmdResponse() {
		Log.d(TAG, "setMmiCancelListCmdResponse is called");
		CIMmiResponse CmdEnqRes = new CIMmiResponse();
		CmdEnqRes.SelectIndex = 0;
		CmdEnqRes.ResponseString = DefaultStr;
		if(tvMci != null)
			tvMci.mmiCmdResponse(currentMmiID, MmiType.MmiTypeList.value, CmdEnqRes);
		return true;
	}

	public CIMmiMenuList getMmiListItems() {
		Log.d(TAG, "getMmiListItems is called");
		return mmiListCmd;
	}

	public boolean setMmiOKEnqCmdResponse(String AnsStr) {
		CIMmiResponse CmdEnqRes = new CIMmiResponse();
		Log.d(TAG, "Received Ans = " + AnsStr);
		if (AnsStr.length() > mmiEnqCmd.LengthOfAnswer) {
			Log.d(TAG, "String Length is Not same As required by CI");
		}
		CmdEnqRes.SelectIndex = 1; // Answer ID
		CmdEnqRes.ResponseString = AnsStr;
		if(tvMci != null)
			tvMci.mmiCmdResponse(currentMmiID, MmiType.MmiTypeEnquiry.value, CmdEnqRes);
		return true;
	}

	public boolean setMmiCancelEnqCmdResponse() {
		CIMmiResponse CmdEnqRes = new CIMmiResponse();
		CmdEnqRes.SelectIndex = 0; // Answer ID
		CmdEnqRes.ResponseString = DefaultStr;
		if(tvMci != null)
			tvMci.mmiCmdResponse(currentMmiID, MmiType.MmiTypeEnquiry.value, CmdEnqRes);
		return true;
	}

	public CIMmiEnq getMmiCmdEnq() {
		return mmiEnqCmd;
	}

	public CICamIdInfo getCamIDInfo(int value) {
		if (tvMci != null) {
			return tvMci.GetCICamIdInfo(value);
		}
		return null;
	}

	class CIChangeListener extends IOnCIChangeListener {
		@Override
		public void onCAMStatusChanged(int status) {

			Log.d(TAG, "onCAMStatusChanged status:" + status);
			Log.d(TAG, "onCAMStatusChanged mPrevCipStatus:" + mPrevCipStatus);
			if ((status == CiPlusStatus.StatusInactive.value) && (mPrevCipStatus != CiPlusStatus.StatusInactive.value)) {
				Log.d(TAG, "isOPSupported = false");
				isOPSupported = false;
				ifOPProfLaterPressed = false;
				isOpInstallationCompleteTrigger = false;
				ntf.notifyAllObservers(EventIDs.CI_INACTIVE_STATE, "");
			}
			mPrevCipStatus = status;
			// ntf.registerForNotification (NativeAPIWrapper.getInstance());
			// ntf.notifyAllObservers (EventIDs.EVENT_CAM_STATUS,
			// Integer.toString(status));
			// OnCAMStatusChanged (status);
		}

		@Override
		public void onMmiClosed(int arg0) {
			if(tvMci != null)
			{
				if (tvMci.getCipStatus() > CiPlusStatus.StatusInactive.value) {
					ntf.notifyAllObservers(EventIDs.CI_CLOSEMMI_WIDGET, "");
					Log.d(TAG, "Clear MMIInProgress Flag so that AMMI can be allowed ");
				}
			}
		}
		

		@Override
		public void onMmiCmdEnq(int mmiId, CIMmiEnq mmiCmd) {
			mmiEnqCmd = mmiCmd;
			currentMmiID = mmiId;
			Log.d(TAG, "Ans len = " + mmiEnqCmd.LengthOfAnswer);
			Log.d(TAG, "PromptText = " + mmiEnqCmd.PromptText);
			ntf.notifyAllObservers(EventIDs.CI_OPENENQUIRY_WIDGET, "");
		}

		@Override
		public void onMmiCmdList(int mmiId, CIMmiMenuList mmiCmd) {

			Log.d(TAG, "OnMmiCmdList is called");
			mmiListCmd = mmiCmd;
			currentMmiID = mmiId;
			currentListChoice = MINIMUM_NO_OF_CHOICE;
			maximumNoOflistChoice = MINIMUM_NO_OF_CHOICE;
			if (mmiListCmd.NumberOfChoices > 0) {
				listChoiceExists = true;
				maximumNoOflistChoice = (mmiListCmd.NumberOfChoices - 1);
			} else {
				listChoiceExists = false;
			}
			ntf.notifyAllObservers(EventIDs.CI_OPENLIST_WIDGET, "");

		}

		@Override
		public void onMmiCmdMenu(int mmiId, CIMmiMenuList mmiCmd) {

			Log.d(TAG, "OnMmiCmdMenu is called");
			mmiMenuCmd = mmiCmd;
			currentMmiID = mmiId;
			currentMenuChoice = MINIMUM_NO_OF_CHOICE;
			maximumNoOfMenuChoice = MINIMUM_NO_OF_CHOICE;
			Log.d(TAG, "Number of Choice = " + mmiMenuCmd.NumberOfChoices + ", CurrentMmiID = " + currentMmiID);
			for (int i = 0; i < mmiMenuCmd.NumberOfChoices + 3; i++) {
				Log.d(TAG, "MmiMenuCmd.MenuStrings[" + i + "] = " + mmiMenuCmd.MenuStrings[i]);
			}
			if (mmiMenuCmd.NumberOfChoices > 0) {
				menuChoiceExists = true;
				maximumNoOfMenuChoice = (mmiMenuCmd.NumberOfChoices - 1);
			} else {
				menuChoiceExists = false;
			}
			ntf.notifyAllObservers(EventIDs.CI_OPENMENU_WIDGET, "");

		}

		@Override
		public void onMmiOpenRequest(int mmiId) {
			Log.d(TAG, "OnMmiOpenRequest is called");
			currentMmiID = mmiId;
			// send notification to UI handler to open
			// MMI...event_OnEvent(evids_CIOpenMmiWidget);
			ntf.notifyAllObservers(EventIDs.CI_OPENMMI_WIDGET, "");
		}

	}

	private boolean isOpsupportedmedium(){
		boolean retVal = false;
		int countryID = GetCountry();
		// flag should be set only if statusinfo.Profile_Type == 1
		if ((countryID == InstallationCountryConstants.FRANCE) && ((Opdeliverysystemhint & CAM_DVBS_HINT) == CAM_DVBS_HINT))	{
			retVal = true;
		}
		Log.d(TAG, "isOpsupportedmedium returns " + retVal);
		return retVal;
	}
		
	public void storecicamdata(){
		Log.d(TAG, "Store camdata");
		ntf.notifyAllObservers(EventIDs.STORE_OP_CICAMID, "");
		ntf.notifyAllObservers(EventIDs.STORE_OP_INFO_VERSION, String.valueOf(OpInfoVersion));	
	}
	class OpChangeListener extends IOnOpChangeListener {
		@Override
		public void onOpSearchStatus(OpProfileSearchStatus opStatus) {
			if(isOpsupportedmedium()) {
				OperatorProfileSearchStatus status = new OperatorProfileSearchStatus();

				status.Info_Version = opStatus.Info_Version;
				status.NIT_Version = opStatus.NIT_Version;
				status.Profile_Type = opStatus.Profile_Type;
				status.Initialised_Flag = opStatus.Initialised_Flag;
				status.Entitlement_Change_Flag = opStatus.Entitlement_Change_Flag;
				status.Entitlement_Valid_Flag = opStatus.Entitlement_Valid_Flag;
				status.Refresh_Request_Flag = opStatus.Refresh_Request_Flag;
				status.Error_Flag = opStatus.Error_Flag;
				status.Delivery_System_Hint = opStatus.Delivery_System_Hint;
				status.Refresh_Request_Date = opStatus.Refresh_Request_Date;
				status.Refresh_Request_Time = opStatus.Refresh_Request_Time;
	
				Log.d(TAG, "Native OnOpSearchStatus called");
				OnOpSearchStatus(status);
			}
		}

		@Override
		public void onOpStatusInfo(OpProfileStatusInfo statusInfo) {

			int i = 0;
			int countryID = GetCountry();
			// flag should be set only if statusinfo.Profile_Type == 1
			if ((countryID == InstallationCountryConstants.FRANCE) && ((statusInfo.Delivery_System_Hint & CAM_DVBS_HINT) == CAM_DVBS_HINT)) {
			Log.d(TAG, "isOPSupported = true");
			isOPSupported = true;

			OperatorProfileStatusInfo statusinfo = new OperatorProfileStatusInfo();

			statusinfo.Info_Version = statusInfo.Status_Info_Version;
			statusinfo.NIT_Version = statusInfo.NIT_Version;
			statusinfo.Profile_Type = statusInfo.Profile_Type;
			statusinfo.Initialised_Flag = statusInfo.Initialised_Flag;
			statusinfo.Entitlement_Change_Flag = statusInfo.Entitlement_Change_Flag;
			statusinfo.Entitlement_Valid_Flag = statusInfo.Entitlement_Valid_Flag;
			statusinfo.Refresh_Request_Flag = statusInfo.Refresh_Request_Flag;
			statusinfo.Error_Flag = statusInfo.Error_Flag;
			statusinfo.Delivery_System_Hint = statusInfo.Delivery_System_Hint;
			Opdeliverysystemhint = statusinfo.Delivery_System_Hint;
			statusinfo.Refresh_Request_Date = statusInfo.Refresh_Request_Date;
			statusinfo.Refresh_Request_Time = statusInfo.Refresh_Request_Time;

			statusinfo.InfoValid = statusInfo.info_Valid;
			statusinfo.ProfileInfoVersion = statusInfo.info_Version;
			statusinfo.CiCamOriginalNetworkId = statusInfo.cicam_Original_Network_Id;
			OpInfoVersion = statusinfo.ProfileInfoVersion;
			Log.d(TAG, "OpInfoVersion " + OpInfoVersion + "statusinfo.ProfileInfoVersion " + statusinfo.ProfileInfoVersion + "statusInfo.info_Version " + statusInfo.info_Version);
			statusinfo.CiCamIdentifier = statusInfo.cicam_Identifier;
			CiCamIdForOP = statusinfo.CiCamIdentifier ;
			statusinfo.CharacterCodeTable = statusInfo.character_Code_Table;
			statusinfo.CharacterCodeTable2 = statusInfo.character_Code_Table_2;
			statusinfo.CharacterCodeTable3 = statusInfo.character_Code_Table_3;
			statusinfo.SdtRunningTrusted = statusInfo.sDT_Running_Trusted;
			statusinfo.EitRunningTrusted = statusInfo.eIT_Running_Trusted;
			statusinfo.EitPfUsage = statusInfo.eIT_Pf_Usage;
			statusinfo.EitScheduleUsage = statusInfo.eIT_Schedule_Usage;
			statusinfo.ExtendedEventUsage = statusInfo.extended_Event_Usage;
			statusinfo.SdtOtherTrusted = statusInfo.sDT_Other_Trusted;
			statusinfo.EitEventTrigger = statusInfo.eIT_Event_Trigger;

			statusinfo.ISO639LangCode = new int[3];
			for (i = 0; i < 3; i++) {
				statusinfo.ISO639LangCode[i] = statusInfo.iSO_639_Lang_Code[i];
			}

			statusinfo.ProfileNameLength = statusInfo.profile_Name_Length;
			statusinfo.ProfileName = new int[statusInfo.profile_Name_Length];
			char[] name = new char[statusInfo.profile_Name_Length];

			for (i = 0; i < statusinfo.ProfileNameLength; i++) {
				statusinfo.ProfileName[i] = statusInfo.profile_Name[i];
				name[i] = (char) statusInfo.profile_Name[i];
			}
			Log.d(TAG, "ProfileNameLength " + statusinfo.ProfileNameLength + "\n ProfileName : " + new String(name));

			setOperatorProfilePackageName(new String(name));
			Log.d(TAG, "Native OnOpStatusInfo called");
			if(opacked == true)
			{
				opacked = false;
				Log.d(TAG, "Ack sent!! so update the persisten!!");
				storecicamdata();
			}
			Log.d(TAG, "NewCamOpInstalled " + NewCamOpInstalled);
			// new cam inserted
			if ((statusinfo.Initialised_Flag == 0) && (isOpInstallationCompleteTrigger == false)) {
				Log.d(TAG, "statusinfo.Initialised_Flag " + statusinfo.Initialised_Flag);
				ntf.notifyAllObservers(EventIDs.OP_PROFILE_INSTALL_REQUEST_IMMEDIATE, "");
			}
			else if((NewCamOpInstalled != true) && (isOpInstallationCompleteTrigger == false))
			{
            ntf.notifyAllObservers(EventIDs.CHECK_START_NEW_CAM_OP, String.valueOf(statusinfo.CiCamIdentifier));
			}
			// if mw instance exists
			if (javaSatInstHandler != 0) {
				Log.d(TAG, "MW instance exists");
				if((NewCamOpInstalled == false) && (isOpInstallationCompleteTrigger == false))
					{
						OnOpStatusInfo(statusinfo);
					}
					else
					{
						storecicamdata();
						NewCamOpInstalled = false;
						if(isOpInstallationCompleteTrigger == true)
						{
							isOpInstallationCompleteTrigger = false;
							ntf.notifyAllObservers(EventIDs.TRIGGER_OP_INSTALL_COMPLETE, "");
						}
					}
				} else {
					Log.d(TAG, "MW instance dosen't exist");
				}
			}

		}

		@Override
		public void onOpNIT(OpProfileNitData nitData) {
			int i = 0;
			if(isOpsupportedmedium()) {
				OperatorProfileNitData nitdata = new OperatorProfileNitData();
		
				nitdata.NitStatus = nitData.NitStatus;
				if (nitdata.NitStatus == 1) {
					nitdata.NitDataLength = nitData.NitDataLength;
					nitdata.NitData = new int[nitdata.NitDataLength];
					Log.d(TAG, "SatInstaller : onOpNIT : IN\n");
					Log.d(TAG, "NitStatus  " + nitData.NitStatus);
					Log.d(TAG, "NitDataLength  " + nitData.NitDataLength);
					for (i = 0; i < nitdata.NitDataLength; i++) {
						Log.d(TAG, "NitData[" + i + "]   " + nitData.NitData[i]);
						nitdata.NitData[i] = nitData.NitData[i];
					}
				} else {
					Log.d(TAG, "Native onOpNIT is not processed as it is invalid/Timeout");
				}
	
				Log.d(TAG, "Native onOpNIT called");
				Log.d(TAG, "Storing new cicam id " + CiCamIdForOP);
            	ntf.notifyAllObservers(EventIDs.STORE_OP_CICAMID, "");
				ntf.notifyAllObservers(EventIDs.STORE_OP_INFO_VERSION, String.valueOf(OpInfoVersion));
				if((CiCamIdForOP == 0) && (NewCamOpInstalled == false))
				{
					Log.d(TAG, "Its CAM case");
					NewCamOpInstalled = true;
				//	requestStatusInfo_SatInst();
				}
				OnOpNIT(nitdata);
			}
		}

		@Override
		public void onOpTune(OpProfileTuneData tuneData) {
			int i = 0;
			if(isOpsupportedmedium()) {
				OperatorProfileTuneData tunedata = new OperatorProfileTuneData();
	
				tunedata.TuneDataLength = tuneData.TuneDataLength;
				tunedata.TuneData = new int[tuneData.TuneDataLength];
				for (i = 0; i < tuneData.TuneDataLength; i++) {
					Log.d(TAG, "tuneData.TuneData[" + i + "] " + tuneData.TuneData[i]);
					tunedata.TuneData[i] = tuneData.TuneData[i];
				}
	
				Log.d(TAG, "Native OnOpTune called");
				OnOpTune(tunedata);
			}
		}

	};

	public boolean isOperatorProfileSupported() {
		Log.d(TAG, "isOperatorProfileSupported entry");
		boolean l_ret = isOPSupported;

		// l_ret =
		// tvMpl.getTvMediaPlayerContext().getTvMediaOp().isOperatorProfileSupported();

		Log.d(TAG, "isOperatorProfileSupported returning " + l_ret);

		return l_ret;
	}

	public String getOperatorProfilePackageName() {
		if (operatorProfilePackageName == null) {
			operatorProfilePackageName = "";
		}
		Log.d(TAG, "getOperatorProfilePackageName " + operatorProfilePackageName);
		return operatorProfilePackageName;
	}

	public int getOpProfileinfoversion() {
		Log.d(TAG, "getOpProfileinfoversion returning info version value" + OpInfoVersion);
		return OpInfoVersion;
	}

	public int getOpProfileCiCamId() {
		Log.d(TAG, "getOpProfileCiCamId returning info version value" + CiCamIdForOP);
		return CiCamIdForOP;
	}
	
	public void setOperatorProfilePackageName(String pkgName) {
		Log.d(TAG, "setOperatorProfilePackageName " + pkgName);
		operatorProfilePackageName = pkgName;
	}

	public void setOPProfLaterPressed(boolean argValue) {
		ifOPProfLaterPressed = argValue;
		Log.d(TAG, "ifOPProfLaterPressed " + ifOPProfLaterPressed);

	}

	public boolean ifOPProfLaterPressed() {
		Log.d(TAG, "ifOPProfLaterPressed " + ifOPProfLaterPressed);
		return ifOPProfLaterPressed;

	}
	
	public OpPresentStatus getOpPresenceStatus() {
		Log.d(TAG,"GetOpPresenceStatus: " + opPresentStatus);
		return opPresentStatus; 
	}
	
	public void stopCAMOPStatusCheck(){
		if (localOPProgTimerTask != null) { localOPProgTimerTask.cancel();}
		if (localOPProgTimer != null) { localOPProgTimer.cancel(); }
	}
	
	public void triggerCAMOPStatusCheck(){
		// if cam already detected and op also present, dont run timers
		if(isOperatorProfileSupported()){
			opPresentStatus = OpPresentStatus.PRESENT;
			stopCAMOPStatusCheck();
		}else {
			// poll based mechanism to start timer and check for availability of CAM
			
			// start local timers
			
			// if timer already cancel and start
			stopCAMOPStatusCheck();
			
			// start the timer
			localOPProgTimerTask = new TimerTask() {
				int secCount = 0;
				@Override
				public void run() {
					secCount++;
					if(isOperatorProfileSupported()){
						opPresentStatus = OpPresentStatus.PRESENT;
						stopCAMOPStatusCheck();
					}else{
						if (ifValidSession()) {
							if(tvMci.getCipStatus() != CiPlusStatus.StatusInactive.value){ // cam is present
								if(secCount > 10) {
									 opPresentStatus = OpPresentStatus.NOT_PRESENT;
									 stopCAMOPStatusCheck();
								}else{
									// wait till op opens and updates opPresentStatus
								}
							}else { // cam is not present ( might be waiting for the stack to init)
								if(secCount > 5) {
									opPresentStatus = OpPresentStatus.NOT_PRESENT;
									stopCAMOPStatusCheck();
								}else{
									// wait for cam detection
								}
							}
						}
					}
				}
			};
			
			localOPProgTimer = new Timer();
			localOPProgTimer.schedule(localOPProgTimerTask, 0, 1000);
		}
		
	}
}
