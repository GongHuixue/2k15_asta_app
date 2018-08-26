package org.droidtv.euinstallertc.model.mwapi;

import org.droidtv.euinstallertc.model.mwapi.MwDataTypes.EventConstants;
import org.droidtv.euinstallertc.model.mwapi.MwDataTypes.InstallerConstants;
import org.droidtv.euinstallertc.model.mwapi.MwDataTypes.opProfileSearchStatus;
import org.droidtv.euinstallertc.model.mwapi.MwDataTypes.opProfileStatusInfo;
import org.droidtv.euinstallertc.model.mwapi.MwDataTypes.opProfileNitData;
import org.droidtv.euinstallertc.model.mwapi.MwDataTypes.opProfileTuneData;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_MEDIUM;
import org.droidtv.euinstallertc.model.mwapi.TcInstallerTvProviderData;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.tv.frontend.ITuning;
import org.droidtv.tv.frontend.ITuning.OnChangeListener;
import org.droidtv.tv.frontend.ITuningAna;
import org.droidtv.tv.frontend.ITuningAna.ChangeListener;
import org.droidtv.tv.frontend.ITuningDvbC;
import org.droidtv.tv.frontend.ITuningDvbC.DvbCSearchRateList;
import org.droidtv.tv.frontend.ITuningDvbC.DvbCParams;
import org.droidtv.tv.frontend.ITuningDvbT;
import org.droidtv.tv.frontend.ITuningDvbT.SignalInfo;
import org.droidtv.tv.frontend.ITuningDvbT.ParamsDvbTSpecific;
import org.droidtv.tv.frontend.ITuningDvbT.ParamsDvbT2Specific;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.media.ITvMediaOp.OpSearchSettings;
import org.droidtv.tv.media.ITvMediaOp.OPTuneStatus;
import org.droidtv.tv.media.ITvMediaOp.OpProfileStatusInfo;
import org.droidtv.tv.media.ITvMediaOp.OpProfileSearchStatus;
import org.droidtv.tv.media.ITvMediaOp.OpProfileNitData;
import org.droidtv.tv.media.ITvMediaOp.OpProfileTuneData;
import org.droidtv.tv.media.ITvMediaOp;
import org.droidtv.tv.media.ITvMediaOp.IOnOpChangeListener;
import org.droidtv.tv.media.ITvMediaCI.IOnCIChangeListener;
//import org.droidtv.tv.provider.IChannelMapUpdaterControl;

import android.content.Context;
import android.media.tv.TvContract;
import android.util.Log;
import android.view.Surface;
import android.os.Bundle;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.ITVCIControl;

public class EuInstallerTC {

	private static final String TAG = EuInstallerTC.class.getName();
	private Context mActivityInstance;
	// notification instance handler holder
	private ITvSettingsManager mTvSettingsManager = ITvSettingsManager.Instance.getInterface();
	private NotificationHandler ntf = NotificationHandler.getInstance();
	public final static int DVBT = 6; // This is for T/T2
	public final static int DVBC = 8;
	public final static int ANALOG = 1;
	public final static int INSTALL = 3;
	public final static int DVBTONLY = 2; // only for T

	public SESSION_MEDIUM sessionTuneMedium = SESSION_MEDIUM.ANTENNA;

	private final static int MW_ANALOG = 1;
	private final static int MW_DVBT = 2;
	private final static int MW_DVBC = 4;
	private Boolean ifSourceSetupFromMW = false;

	private final static int CAM_DVBC_HINT = 0x1;
	private final static int CAM_DVBT_HINT = 0x4;
	private final static int CAM_DVBS_HINT = 0x2;

	private int camDeliverySysHint = 0;

	private int userSelectedCountry = 0;
	private int mCurrentACIIndex = 0;

	private MwDataTypes mwIns = new MwDataTypes();
	private EventConstants euEventConst = mwIns.new EventConstants();
	private InstallerConstants InsEventConst = mwIns.new InstallerConstants();
	private OpChangeListener oplistener = null;

	private ITuning frontendTun = null;
	private ITuningDvbT t = null;
	private ITuningDvbC c = null;
	private ITuningAna a = null;
	private int javaInstHandler = 0;

	private ITvMediaOp tvmop;
	private ITvMediaCI tvmci;

	private SignalInfo sig;
	private ParamsDvbTSpecific tSpec;
	private ParamsDvbT2Specific t2Spec;

	private DvbCParams params;
	private int DetectedStandard = 0;
	private boolean isOPSupported = false;
	private int mProfileNameLength;
	private int[] mProfileName;

	private long startTime = 0;
	private boolean IsScanOngoing = false;
	
	private long CachedDemuxHandle = -1;

	private SessionHandlerTIF sessionHandlerInstance = null;

	/**
	 * Static block Gets executed before class is instantiated and loads the JNI
	 * library.
	 * 
	 */

	static {
		try {
			System.loadLibrary("tcinstallerjni");
		} catch (UnsatisfiedLinkError e) {
			Log.e(TAG, "Native code library failed to load.\n" + e);
		}
	}

	public void initMainActivityInstance(Context argCtx) {
		mActivityInstance = argCtx;
	}

	public void setSessionHandler(SessionHandlerTIF argSessionHandler) {
		Log.i(TAG, "setSessionHandler " + argSessionHandler);
		sessionHandlerInstance = argSessionHandler;
	}

	public void setSessionTuneWithMedium(SESSION_MEDIUM argMedium) {
		// at native api wrapper level is already registered so i'll get call
		// back sessionOnChannelRetuned
		Log.i(TAG, "setSessionTuneWithMedium " + argMedium);
		if (ifValidSession()) {
			Bundle bundle = new Bundle();

			sessionTuneMedium = argMedium;

			// populate bundle based on medium
			// ref: http://2k15-xref.tpvision.com:8080/source/xref/device/tpvision/common/plf/tvjar/java/src/org/droidtv/tv/tvinput/ITVSessionContext.java
			// int bundleMode = 0;
			String bundleModeString = "";
			if (argMedium == SESSION_MEDIUM.ANALOG) {
				//bundleMode = ANALOG;
				bundleModeString = TvContract.Channels.TYPE_PAL;
			} else if (argMedium == SESSION_MEDIUM.CABLE) {
				//bundleMode = DVBC;
				bundleModeString = TvContract.Channels.TYPE_DVB_C;
			} else if (argMedium == SESSION_MEDIUM.ANTENNA) {
				bundleModeString = TvContract.Channels.TYPE_DVB_T;
				if (NativeAPIWrapper.getInstance().ifTLiteCountry()) {
					//bundleMode = DVBTONLY;
					bundleModeString = TvContract.Channels.TYPE_DVB_T;
				} else {
					int mChannelDecoder = mTvSettingsManager.getInt(TvSettingsConstants.OPCHANNELDECODER, 0, 0);
					//int mDecoderType = DVBT;
					Log.i(TAG, " MediaPlayerInit Mode " + mChannelDecoder);
					if ((mChannelDecoder == 0) || (mChannelDecoder == 4)) {
						bundleModeString = TvContract.Channels.TYPE_DVB_T;
						//mDecoderType = 2; // internal channel decoder (T/C) ::::: H
						// External channel decoderdual (S2TC) Si21672 ::::::::K
					} else if ((mChannelDecoder == 2) || (mChannelDecoder == 3) || (mChannelDecoder == 5)) {
						bundleModeString = TvContract.Channels.TYPE_DVB_T2;
						//mDecoderType = 6;// External channel decoder (T2/T/C)Si2168 :::::::T
						// External channel decoder (S2/T2/T/C) Si2169 ;;;;;;;;S
						// External channel decoder dual (S2/T2/T/C) Si 21692
					}
					//bundleMode = mDecoderType;
				}
			}
			
			String[] params = {TvContract.Channels.COLUMN_TYPE};
			bundle.putString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE, ITVSessionContext.TUNE_REQUEST_TYPE_CUSTOM);
			bundle.putStringArray(ITVSessionContext.TUNING_PARAMETERS,params);
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
		

		if (ifValidSession()) {
			// moved all the ci code to one function
			//setCIInterfacesOnSessionCreated();
			setTunnigParametersForMedium(sessionTuneMedium);
			
			long DmxHandle = 0, VbiHandle = 0;
			
			
			
			if(sessionTuneMedium == SESSION_MEDIUM.ANALOG)
			{
				VbiHandle = sessionHandlerInstance.getSessionContext().getVbi();
				Log.i(TAG,"GetVbi token " + VbiHandle);
				if((VbiHandle != 0) && (javaInstHandler != 0))
					setVbiHandle(VbiHandle);
			} else {
				DmxHandle = sessionHandlerInstance.getSessionContext().getDemux();
				Log.i(TAG,"GetDemux token " + DmxHandle + "CachedHandle" + CachedDemuxHandle);
				if((DmxHandle != 0) && (CachedDemuxHandle != DmxHandle) && (javaInstHandler != 0)) {
					setDemuxHandle(DmxHandle);
					CachedDemuxHandle = DmxHandle;
				}
					
			}
			
			Log.i(TAG, "ifSourceSetupFromMW " + ifSourceSetupFromMW);
			if (ifSourceSetupFromMW){
				// flag set by callback from MW in SourceSetupApply_JavaInst
				if(javaInstHandler != 0)
				{
				OnSourceSetupApplied(0);
				}
				// reset flag
				ifSourceSetupFromMW = false;
			}
			
			ntf.notifyAllObservers(EventIDs.EVENT_INST_ONPREPAREDTV, "");
		}
	}
	
	public void setCIInterfacesOnSessionCreated() {
		if(null == tvmop)
		{
			tvmop = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if (tvmop != null) {
				Log.i(TAG, "Got TV Media Op Instance:" + tvmop + "oplistener" + oplistener + "IOnOpChangeListener" + (IOnOpChangeListener) oplistener);
				if (oplistener == null) {
					oplistener = new OpChangeListener();
					tvmop.registerOpChangeListener((IOnOpChangeListener) oplistener);
				}
				tvmop.requestOpStatusInfo();
			} else {
				Log.v(TAG, "TV Media Op Instance is NULL");
			}
		}
			tvmci = sessionHandlerInstance.getSessionContext().getITvMediaCI();
			int CiStatus = 0;
			if (tvmci != null) {
				CIChangeListener cilistener = new CIChangeListener();
				Log.i(TAG, "Got TV Media CI Instance:" + tvmci + "cilistener" + cilistener + "IOnCIChangeListener" + (IOnCIChangeListener) cilistener);
				//tvmci.registerCIChangeListener((IOnCIChangeListener) cilistener);
				CiStatus = tvmci.getCipStatus();
				cilistener.onCAMStatusChanged(CiStatus);
			} else {
				Log.v(TAG, "TV Media CI Instance is NULL");
			}
			
		//unRegisterCIListener();
	}

	public void createMWInstance() {
		Log.d(TAG, "createMWInstance " + javaInstHandler);
		if (javaInstHandler == 0) {
			javaInstHandler = CreateInstance(0, this);
		}
	}

	public void setTunnigParametersForMedium(SESSION_MEDIUM argMedium) {
		Log.i(TAG, "setTunnigParametersForMode " + argMedium);
		if (ifValidSession()) {

			if (argMedium == null) {
				// get the medium from NVM
				int dvbMediumID = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);

				if (dvbMediumID == TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA) {
					sessionTuneMedium = SESSION_MEDIUM.ANTENNA;
				} else {
					sessionTuneMedium = SESSION_MEDIUM.CABLE;
				}
			}
			Log.d(TAG, "setTunnigParametersForMode sessionTuneMedium " + sessionTuneMedium);
			frontendTun = GetTuningInstance();
			if (argMedium == SESSION_MEDIUM.ANALOG) {
				// SetMedium(0);
				a = sessionHandlerInstance.getSessionContext().getITuningAna();
				if( a != null) {
					try {
						a.registerListener(changeListener);
					} catch (IllegalStateException e) {
						//e.printStackTrace();
					}
				}else {
					Log.e(TAG, "ITuningAna : registerListener failed!!!");
				}

				ntf.notifyAllObservers(EventIDs.EVENT_ANALOG_SWITCH_DONE, "");
			} else if (argMedium == SESSION_MEDIUM.CABLE) {
				
				if(ifSourceSetupFromMW == false){
					if (javaInstHandler != 0) {
						SetMedium(1);
					}
				}

				try {
					c = sessionHandlerInstance.getSessionContext().getITuningDvbC();
					params = new DvbCParams();
				} catch (IllegalStateException e) {
					//e.printStackTrace();
				}

				ntf.notifyAllObservers(EventIDs.EVENT_SWITCH_TC, "");
			} else if (argMedium == SESSION_MEDIUM.ANTENNA) {
			
				if(ifSourceSetupFromMW == false){
					if (javaInstHandler != 0) {
						SetMedium(0);
					}
				}

				try {
					t = sessionHandlerInstance.getSessionContext().getITuningDvbT();
					sig = new SignalInfo();
					tSpec = new ParamsDvbTSpecific();
					t2Spec = new ParamsDvbT2Specific();
				} catch (IllegalStateException e) {
					//e.printStackTrace();
				}

				ntf.notifyAllObservers(EventIDs.EVENT_SWITCH_TC, "");
			}
		}
	}

	public void UnregisterTuningInstance () {
		if (frontendTun != null) {
			try {
				frontendTun.unregisterListener(onChangeListener);
			} catch (IllegalStateException e) {
				Log.v(TAG, "GetTuningInstance unregister : IllegalStateException");
			}
			frontendTun = null;
		}
	}
	
	private ITuning GetTuningInstance() {
		ITuning returnFrontendTuner = null;
		if (frontendTun != null) {
			try {
				frontendTun.unregisterListener(onChangeListener);
			} catch (IllegalStateException e) {
				Log.v(TAG, "GetTuningInstance unregister : IllegalStateException");
			}
		}

		returnFrontendTuner = sessionHandlerInstance.getSessionContext().getITuning();
		if(returnFrontendTuner != null) {
			try {
				returnFrontendTuner.registerListener(onChangeListener);
			} catch (IllegalStateException e) {
				Log.v(TAG, "GetTuningInstance register : IllegalStateException");
			}
		}

		return returnFrontendTuner;
	}

	public boolean ifValidSession() {
		boolean returnStatus = false;

		if ((sessionHandlerInstance != null) && ((sessionHandlerInstance.getSessionState() != SessionHandlerTIF.SESSION_STATE.INVALID) && 
												 (sessionHandlerInstance.getSessionState() != SessionHandlerTIF.SESSION_STATE.SESSION_CREATION_INPRGRESS))) {
			returnStatus = true;
		}
		Log.i(TAG, "ifValidSession " + returnStatus);
		return returnStatus;
	}

	// callback from MW
	public int SourceSetupApply_JavaInst(int argMedium, final int result[]) {
		Log.i(TAG, "SourceSetupApply_JavaInst " + result[0] + " Medium " + argMedium);

		if (argMedium == MW_DVBT) {
			if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
				if (NativeAPIWrapper.getInstance().ifTLiteCountry()) {
					// do forceful source setup as earlier source setup might be
					// with T/T2
					result[0] = 3; // WaitForSourceSetupApplyNotify
					ifSourceSetupFromMW = true;
					setSessionTuneWithMedium(SESSION_MEDIUM.ANTENNA);
				} else {
					// same mode don't do anything
					result[0] = 0; // Success
				}
			} else {
				// do source setup
				result[0] = 3; // WaitForSourceSetupApplyNotify
				ifSourceSetupFromMW = true;
				setSessionTuneWithMedium(SESSION_MEDIUM.ANTENNA);
			}
		} else if (argMedium == MW_DVBC) {
			if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
				result[0] = 0; // Success
				// same mode don't do anything
			} else {
				// do source setup
				result[0] = 3; // WaitForSourceSetupApplyNotify
				ifSourceSetupFromMW = true;
				setSessionTuneWithMedium(SESSION_MEDIUM.CABLE);
			}
		} else if (argMedium == MW_ANALOG) {
			if (sessionTuneMedium == SESSION_MEDIUM.ANALOG) {
				result[0] = 0; // Success
				// same mode don't do anything
			} else {
				// do source setup
				result[0] = 3; // WaitForSourceSetupApplyNotify
				ifSourceSetupFromMW = true;
				setSessionTuneWithMedium(SESSION_MEDIUM.ANALOG);
			}
		}
		return 0;
	}

	public void StopMWInstIfInstExists() {
		if (javaInstHandler != 0) {
			StopInstallation();
		}
	}

	public void updateUserSelectedCountry(int argUserSelectedCountry) {
		// store the user selected country for later set
		userSelectedCountry = argUserSelectedCountry;
	}

	public EuInstallerTC() {
		int dvbMediumID = mTvSettingsManager.getInt(
					TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);

			if (dvbMediumID == TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA) {
				sessionTuneMedium = SESSION_MEDIUM.ANTENNA;
			} else {
				sessionTuneMedium = SESSION_MEDIUM.CABLE;
			}
		
		
	}

	public void ExitEuInstallerTC() {

		if (frontendTun != null) {
			try {
				frontendTun.unregisterListener(onChangeListener);
			} catch (IllegalStateException e) {
				Log.v(TAG, "EuInstallerTC: unregisterListener : IllegalStateException");
			}
			frontendTun = null;
		}

		if (a != null) {
			try {
				a.unregisterListener(changeListener);
			} catch (IllegalStateException e) {
				Log.v(TAG, "EuInstallerTCAna: unregisterListener : IllegalStateException");
			}
		}
		/*if (oplistener != null) {
			if (tvmop != null) {
				tvmop.unregisterOpChangeListener((IOnOpChangeListener) oplistener);
				oplistener = null;
			}
		}*/
		// reset the flags to default values
		sessionHandlerInstance = null;
		sessionTuneMedium = null;

		ifSourceSetupFromMW = false;
		t = null;
		c = null;
		a = null;
	}

	public void setSurface(Surface p_surface) {
		if (ifValidSession()) {
			sessionHandlerInstance.setSurface(p_surface);
			//sessionHandlerInstance.getTunerSession().start();
		}
	}

	public void SetHostControlStatus(boolean OnOff) {
		if (tvmci != null) {
			tvmci.hCEnable(OnOff, 1);
		}
	}

	public native int CreateInstance(int tokenId, EuInstallerTC obj);

	public native void DeleteInstance();

	public native int StartInstallation(int source, int ptc, int mode);

	public native int StopInstallation();

	public native void SetManualFrequency(int frequency, int offset, boolean finetune);

	public native ManFreqValues GetManualFrequency();

	public native boolean IsManualInstallationModeSupported(int mode);

	public native void SetManualInstallationMode(int mode);

	public native int GetManualInstallationMode();

	public native void StoreManualInstallationValues(int channelNo);

	public native boolean AutoStoreManualInstallationValues();

	public native boolean StartFrequencySearch();

	public native int GetTunerFrequency();

	public native void SetTunerFrequency(int freq, boolean fineTune);

	public native int GetNumberOfAnalogChannelsFound();

	public native int GetNumberOfDigitalChannelsFound();

	public native int GetNumberOfDigitalChannelsRemoved();

	public native int GetInstallationStatus();

	public native int GetInstallationMode();

	public native boolean IsUpdateInstallationSupported();

	public native void SetManualChannel(int channel, boolean finetune);

	public native ManChanInfo GetManualChannel();

	public native SigStrengthRange GetSigStrengthRange(int measmode);

	public native int StoreWeakSignalInstallationChannel();

	public native int GetInstalledWeakSignalChannel();

	public native boolean IsFrequencySearchDirectionSupported(boolean searchup);

	public native void SetFrequencySearchDirection(boolean searchup);

	public native boolean GetFrequencySearchDirection();

	public native int GetMinFrequency();

	public native int GetMaxFrequency();

	public native int GetCurrentPass();

	public native int GetNoOfPass();

	public native int GetCurrentPassType();

	public native boolean IsMediumSupported(int medium);

	public native int GetMedium();

	public native void SetMedium(int medium);

	public native void SetInstalledMedium(int medium);

	public native boolean IsTvSystemSupported(int tvsystem);

	public native void SetTvSystem(int tvsystem);

	public native int GetTvSystem();

	public native boolean IsColorSystemSupported(int colorsystem);

	public native void SetColorSystem(int colorsystem);

	public native int GetColorSystem();

	public native boolean IsValidPTC(int medium, int PTC);

	public native int GetMinPTC(int medium);

	public native int GetMaxPTC(int medium);

	public native int GetLastPTCFound();

	public native int GetNumberOfPTCsFound();

	public native void StartSigStrMeas(int measmode);

	public native void StopSigStrMeas(int measmode);

	public native boolean IsSignalStrengthMeasurementValid(int measmode);

	public native AttributeRange GetAttributeRange(int installationmode, int attribute);

	public native boolean SetAttributeMode(int installationmode, int attribute, int attributeMode);

	public native boolean SetAttribute(int installationmode, int attribute, int value);

	public native int GetAttributeMode(int installationmode, int attribute);

	public native int GetAttribute(int installationmode, int attribute);

	public native boolean IsAvailable(int installationmode, int attribute);

	public native void ResetAttributeToDefault(int installationmode, int attribute);

	public native void ResetAttributeToPersistent(int installationmode, int attribute);

	public native NitType GetTargetNitType();

	public native boolean IsNetworkUpdateDetected();

	public native void Initialise();

	public native int SkipInstallationScans(int ScanTypes);

	public native TsValues GetAltTSValues();

	public native void SetUserSymbolRates(int installationmode, int[] values, int len);

	public native int[] GetUserSymbolRates(int installationmode);

	public native int[] GetPredefinedSymbolRates(int installationmode);

	public native int GetNetworkIDList();

	public native String GetNetworkIDName(int index); // used for DVB-T
														// favourite arg:index
														// get
														// networkname
	public native String GetChannelListIDName(int index);
														
	public native void SetFavouriteRegion(int mode, int index, int regionType);

	public native void SetFavouriteNetworkID(int mode, int index, int regionType);

	public native void SetUserSelectConflictService(int LcnIndex, int SvcIndex);

	public native int GetNumberOfChannelListIds();
	
	public native int GetChannelListIdByIndex(int index);

	public native void SetFavouriteChannelListId(int mode,int attrib,int index);

	public native void ConflictsSelectionDone(boolean UserSelection);

	public native int GetInstallationVersion();

	public native int GetInstallationState();

	public native int[] GetPLPIds();

	public native void UserSelectionDone(boolean UserSelection);

	public native int GetFavouriteRegion(int mode, int RegionType);

	public native boolean ZiggoNetworkDataSet(boolean ActionValue);

	public native void ClearPersistent();

	// Notification Native Calls
	public native int onScanAborted_CallNative();

	public native int onScanEnded_CallNative();

	public native int onScanningStandardDetected_CallNative(int arg0, int arg1);

	public native int onTvSystemDetected_CallNative(int tvsys);

	public native int onTuned_CallNative(int arg0, int arg1);

	public native void SetLCNSortingControl(int mode);

	public native void SetInstallCountry(int countryCode);

	public native void SetSystemCountry(int countryCode);

	public native void SetRfSetting(int value);
	
	public native void SetPbsMode(int value);
	
	public native void PrepareChNameUpdate(int ChUniID, int ServID);
	
	public native String GetUpdatedChannelName();
	
	public native int GetUpdatedONID();
	
	public native int GetUpdatedTsID();
	
	public native void SetIsDVBT2Scan(int abIsTrue);
	
	public native void SetFocusedPlpId(int aiPlpId);
	
	public native void SetExtractScanResult(int abIsTrue);
	
	public native int GetUpdatedSymbolRate();
	
	public native void setDigitalOrAnalaog(int setDigrAnalog);

	public native int getDigitalOrAnalaog();

	public native int getPogressStatus();

	public native int GetFirstIntalledAnalogueChannel();

	public native int GetFirstIntalledDigitalChannel();

	public native int GetFirstIntalledRadioChannel();

	public native int GetFirstInstalledChannel();

	public native boolean ifValidNetworkFreqEntered(int nwtFreq);

	public native boolean GetDigitalChannelOnOrOff();

	public native String getNetworkName(int nid); // used for DVB-C popup pass
													// nid & get network name

	public native int[] getNIDsFound();

	public native int getDefaultNetworkID();

	public native boolean ifValidNetworkIDEntered(int nwtId);

	public native String[] getFavNetworkList();

	public native void SetConflictSelectinDone(int val);

	public native void skipNetworkFreq();

	public native void skipNetworkID();

	/*
	 * [arg0 - Primary:0 Secondary:1 Tertiary:2] [arg1 - valid for Primary,
	 * Secondary & Tertiary, selected PrimaryID] [arg2 - valid for Secondary &
	 * Tertiary, selected SecondaryID] [arg3 - valid for Tertiary, selected
	 * TertiaryID]
	 */
	public native String[] getRegionList(int pri0_sec1_ter2, int priID, int secID);

	public native void setRegionList(int pri0_sec1_ter2, int value);

	public native int setLowestNetworkID();

	public native int[] getConflictingChannelNumbers();

	public native String[] getConflictingChannelNames(int channelID);

	public native void setSymbolRatesOneTwo(int instMode, int symb0_symb1, int value);

	public native void OnSourceSetupApplied(int status);

	public native void SetStreamPriority(int plpID);

	public native void OnOpSearchStatus(opProfileSearchStatus opStatus);

	public native void OnOpStatusInfo(opProfileStatusInfo statusInfo);

	public native void OnOpNIT(opProfileNitData nitData);

	public native void OnOpTune(opProfileTuneData tuneData);

	public native void StartPageDisplay();

	public native int GetNoOfMtpItems();

	public native void SetCursor(int item);

	public native void RemoveCursor();

	public native void SelectIndex(int index);

	public native void SetGfxHandle(Surface txtsurface);

	/*** TVPROVIDER IMPLEMENTATION START ***/
	public native int GetNumberOfDatabaseRecords(int TSDataOnly);
	public native TcInstallerTvProviderData GetTvProviderBlobDataByIndex(int Index,int TSDataOnly);
	public native void PopulateMW(TcInstallerTvProviderData TvpData, int Clear);
	public native void syncUniqueIdToMW (TcInstallerTvProviderData TvpData);
	/*** TVPROVIDER IMPLEMENTATION END ***/

	public native void setVbiHandle(long vbiHandle);
	public native void setDemuxHandle(long demuxHandle);
	
	public native int GetLastAnalogPresetNumber();

	private OnChangeListener onChangeListener = new OnChangeListener() {

		public int onScanningStandardDetected(ITuning.paramsOnScanningStandardDetected scanStdParam) {
			DetectedStandard = scanStdParam.std;
			if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
				if (t != null) {
					try {
						t.getParams(sig, tSpec, t2Spec);
						Log.i(TAG, "Bandwidth from TVPlayer " + sig.bandwidth);
					} catch (IllegalStateException e) {
						Log.v(TAG, "getParams : IllegalStateException");
					}
				} else {
					Log.v(TAG, "t is NULL");
				}

			} else if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
				if (c != null) {
					try {
						c.getParams(params);
					} catch (IllegalStateException e) {
						Log.v(TAG, "getParams : IllegalStateException");
					}
				} else {
					Log.v(TAG, "c is NULL");
				}
			}
			onScanningStandardDetected_CallNative(scanStdParam.std, scanStdParam.freq);

			return 0;
		}

		public int onScanAborted() {
			IsScanOngoing = false;
			onScanAborted_CallNative();
			return 0;
		}

		public int onScanEnded() {
			IsScanOngoing = false;
			onScanEnded_CallNative();
			return 0;
		}

		public int onTuned(ITuning.paramsOnTuned onTunedParams) {
			if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
				if (t != null) {
					try {
						t.getParams(sig, tSpec, t2Spec);
					} catch (IllegalStateException e) {
						Log.v(TAG, "getParams : IllegalStateException");
					}
					Log.i(TAG, "onTuned hiermode" + tSpec.hiermode);
					DetectedStandard = sig.standard;
				}
			} else if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
				if (c != null) {
					try {
						c.getParams(params);
					} catch (IllegalStateException e) {
						Log.v(TAG, "getParams : IllegalStateException");
					}
				}
			}
			onTuned_CallNative(onTunedParams.tuningresult, onTunedParams.freq);
			return 0;
		}
	};

	private ChangeListener changeListener = new ChangeListener() {

		public int onTvSystemDetected(final int tvsys) {
			onTvSystemDetected_CallNative(tvsys);
			return 0;
		}

	};
	
	public int tune_JavInst(final int freq, final boolean val) {
		Log.i(TAG, "tune_JavInst freq and value " + freq + val);
		int ret = 0;
		if (frontendTun != null) {
			try {
				frontendTun.tune(freq, val);
			} catch (IllegalStateException e) {
				onScanEnded_CallNative();
				ret = 1;
			}
		}
		return ret;
	}

	public int getValue_FromContentProvider(final int id, final int val[]) {
		//Log.d(TAG, "getValue_FromContentProvider" + "id " + id);

		int channel = mTvSettingsManager.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC, 0, 0);
		val[0] = NativeAPIWrapper.getInstance().getChannelfromID(channel);

		//Log.d(TAG, "getValue_FromContentProvider" + val[0]);
		return 0;
	}

	public int getFreq_JavInst(final int freq[]) {
		//Log.d(TAG, "frontendTun: " + frontendTun);
		if (frontendTun != null) {
			try {
				freq[0] = frontendTun.getFreq();
			} catch (IllegalStateException e) {
				//e.printStackTrace();
				freq[0] = 0;
			}
		}
		Log.d(TAG, "getFrequency_JavInst Freq " + freq[0]);
		return 0;
	}

	public int getFreqRange_JavInst(final int minFreq[], final int maxFreq[]) {
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			minFreq[0] = ITuningDvbT.TUNING_DVBT_START_FREQUENCY;
			maxFreq[0] = ITuningDvbT.TUNING_DVBT_END_FREQUENCY;
		}
		if (sessionTuneMedium == SESSION_MEDIUM.ANALOG) {
			minFreq[0] = ITuningAna.TUNING_ANA_START_FREQUENCY;
			maxFreq[0] = ITuningAna.TUNING_ANA_END_FREQUENCY;
		}
		if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			minFreq[0] = ITuningDvbC.TUNING_DVBC_START_FREQUENCY;
			maxFreq[0] = ITuningDvbC.TUNING_DVBC_END_FREQUENCY;
		}
		return 0;
	}

	public int scanStart_JavInst(final int startfreq, final int endfreq, final boolean scanforward) {
		Log.i(TAG, " scanStart_JavInst startfreq " + startfreq + " endfreq " + endfreq + " scanforward " + scanforward);
		int ret = 0;
		if (frontendTun != null){
			try {
				IsScanOngoing = true;
				frontendTun.scanStart(startfreq, endfreq, scanforward);
			} catch (IllegalStateException e) {
				IsScanOngoing = false;
				onScanEnded_CallNative();
				ret = 1;
			}
		}
		return ret;
	}

	public int scanAbort_JavInst() {
		int ret = 0;
		if (frontendTun != null) {
			try {
				IsScanOngoing = false;
				frontendTun.scanAbort();
			} catch (IllegalStateException e) {
				onScanEnded_CallNative();
				ret = 1;
			}
		}
		return ret;
	}

	public int scanNext_JavInst() {
		int ret = 0;
		if (frontendTun != null) {
			try {
				frontendTun.scanNext();
			} catch (IllegalStateException e) {
				IsScanOngoing = false;
				onScanEnded_CallNative();
				ret = 1;
			}
		}
		return ret;
	}

	public int setSymbolRate_JavInst(final int srtmode, final int rate) {
		if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			if (c != null) {
				try {
					//Log.d(TAG, "setSymbolRate_JavInst():  mode:" + srtmode + "  rate:" + rate);
					c.setSymbolRate(srtmode, rate);
				} catch (IllegalStateException e) {
					Log.v(TAG, "setSymbolRate_JavInst : IllegalStateException");
				}
			}
		}
		return 0;
	}

	public int setTVSystem_JavaInst(final int tvsystem, final int errorcode[]) {
		if (a != null) {
			int scheme = ITuningAna.TUNING_ANA_MODSCHEME_NEGATIVE;
			if (tvsystem == ITuningAna.TUNING_ANA_TVSYS_L) {
				scheme = ITuningAna.TUNING_ANA_MODSCHEME_POSITIVE;
			}

			Log.v(TAG, "setTVSystem_JavaInst Calling ITuningAna.setTvSystem");
			try {
				a.setTvSystem(scheme, tvsystem);
			} catch (IllegalStateException e) {
				errorcode[0] = 1;
			}
		}
		return errorcode[0];
	}

	public int getTVSystem_JavaInst(final int tvsystem[], final int errorcode[]) {
		if (a != null) {
			try {
				tvsystem[0] = a.getTvSystem();
			} catch (IllegalStateException e) {
				tvsystem[0] = 0;
			}
			Log.i(TAG, "getTVSystem_JavaInst tvsystem " + tvsystem[0]);
		} else {
			errorcode[0] = 1;
			Log.i(TAG, "getTVSystem_JavaInst errorcode " + errorcode[0]);
		}
		return tvsystem[0];
	}

	public int getTVSystemID() {
		int tvsysid = 0;
		int tvsystem = 0;
		Log.i(TAG, "getTVSystemID entry a=" + a);
		if (a != null) {
			try {
				tvsysid = a.getTvSystem();
			} catch (IllegalStateException e) {
				tvsysid = 0;
			}
			Log.i(TAG, "getTVSystemID tvsysid " + tvsysid);

			if (tvsysid == ITuningAna.TUNING_ANA_TVSYS_BG) {
				tvsystem = InsEventConst.IHsvInstallation2_InsTvSystemBg;
			} else if (tvsysid == ITuningAna.TUNING_ANA_TVSYS_DK) {
				tvsystem = InsEventConst.IHsvInstallation2_InsTvSystemDk;
			} else if (tvsysid == ITuningAna.TUNING_ANA_TVSYS_I) {
				tvsystem = InsEventConst.IHsvInstallation2_InsTvSystemI;
			} else if (tvsysid == ITuningAna.TUNING_ANA_TVSYS_L) {
				tvsystem = InsEventConst.IHsvInstallation2_InsTvSystemL;
			} else if (tvsysid == ITuningAna.TUNING_ANA_TVSYS_BG_A2)
			{
				tvsystem = InsEventConst.IHsvInstallation2_InsTvSystemBG_A2;
			}else if (tvsysid == ITuningAna.TUNING_ANA_TVSYS_DK_A2) 
			{
				tvsystem = InsEventConst.IHsvInstallation2_InsTvSystemDK_A2;
			}
		}
		Log.i(TAG, "getTVSystemID returning " + tvsystem);
		return tvsystem;
	}

	public int setTVSystemID(final int tvsystem) {
		Log.i(TAG, "setTVSystemID" + tvsystem);
		int errorcode = 0;
		int tvsysid = 0;
		if (a != null) {
			if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemBg) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_BG;
			} else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemDk) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_DK;
			} else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemI) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_I;
			} else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemL) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_L;
			} else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemBG_A2) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_BG_A2;
			} else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemDK_A2) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_DK_A2;
			}

			int scheme = ITuningAna.TUNING_ANA_MODSCHEME_NEGATIVE;
			if (tvsysid == ITuningAna.TUNING_ANA_TVSYS_L) {
				scheme = ITuningAna.TUNING_ANA_MODSCHEME_POSITIVE;
			}

			try {
				a.setTvSystem(scheme, tvsysid);
			} catch (IllegalStateException e) {
				errorcode = 1;
				Log.v(TAG, "setTVSystemID : IllegalStateException");
			}
		}
		return errorcode;
	}

	public int DetectTvSystemIdID(final int tvsystem) {
		Log.i(TAG, "DetectTvSystemIdID" + tvsystem);
		int errorcode = 0;
		int tvsysid = 0;
		if (a != null) {
			if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemBg) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_BG;
			} else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemDk) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_DK;
			} else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemI) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_I;
			} else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemL) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_L;
			}
			 else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemBG_A2) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_BG_A2;
			}
			  else if (tvsystem == InsEventConst.IHsvInstallation2_InsTvSystemDK_A2) {
				tvsysid = ITuningAna.TUNING_ANA_TVSYS_DK_A2;
			}

			int scheme = ITuningAna.TUNING_ANA_MODSCHEME_NEGATIVE;
			if (tvsysid == ITuningAna.TUNING_ANA_TVSYS_L) {
				scheme = ITuningAna.TUNING_ANA_MODSCHEME_POSITIVE;
			}

			try {
				a.detectTvSystem(scheme, tvsysid);
			} catch (IllegalStateException e) {
				errorcode = 1;
				Log.v(TAG, "detectTvSystemIdID : IllegalStateException");
			}
		}
		return errorcode;
	}

	public int getSymbolRateRange_JavInst(final int symbolRate[]) {
		if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			symbolRate[0] = ITuningDvbC.TUNING_DVBC_SYMBOLRATE_MIN;
			symbolRate[1] = ITuningDvbC.TUNING_DVBC_SYMBOLRATE_MAX;
		}
		return 0;
	}

	public int setScanStep_JavInst(int value) {
		if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			if (c != null) {
				try {
					c.setScanStep(value);
				} catch (IllegalStateException e) {
					Log.v(TAG, "setScanStep_JavInst : IllegalStateException");
				}
			}
		}
		return 0;
	}

	public int setSearchRates_JavaInst(DvbCSearchRateList[] searchrates, final int listsize) {
		Log.i(TAG, "setSearchRates_JavaInst size" + listsize);
		if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			/*for (int i = 0; i < listsize; i++) {
				Log.d(TAG, "setSearchRates_JavaInst Constell" + searchrates[i].constellation);
				Log.d(TAG, "setSearchRates_JavaInst SymbolRate" + searchrates[i].symbolrate);
			}*/
			if (c != null) {
				try {
					c.setSearchRates(searchrates, listsize);
				} catch (IllegalStateException e) {
					Log.v(TAG, "setSearchRates_JavaInst : IllegalStateException");
				}
			}
		}
		return 0;
	}

	public int setStreamPriority_JavaInst(int streamprio) {
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if (t != null) {
				try {
					t.setStreamPriority(streamprio);
				} catch (IllegalStateException e) {
					Log.v(TAG, "setStreamPriority_JavaInst : IllegalStateException");
				}
			}
		}
		return 0;
	}

	public int setBandwidth_JavaInst(int bandwidth) {
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if (t != null) {
				try {
					Log.d(TAG, "setBandwidth_JavaInst : BW:" + bandwidth);
					t.setBandwidth(bandwidth);
				} catch (IllegalStateException e) {
					Log.v(TAG, "setBandwidth_JavaInst : IllegalStateException");
				}
			}
		}
		return 0;
	}

	public int setPLP_JavaInst(byte plpid) {
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if (t != null) {
				try {
					//Log.d(TAG, "setPLP_JavaInst() idx:" + plpid);
					t.setPLP(plpid);
				} catch (IllegalStateException e) {
					Log.v(TAG, "setPLP_JavaInst : IllegalStateException");
				}
			}
		}
		return 0;
	}

	public int GetFreqStep_JavaInst(final int step[]) {
		step[0] = 1;
		return 0;
	}

	public int getActualCodeRate_JavInst(final int rate[]) {
		rate[0] = 10;
		return 0;
	}

	public int getSymbolRate_JavInst(final int symbolRate[]) {
		if (c != null) {
			try {
				c.getParams(params);
				if (params != null) {
					symbolRate[0] = params.symbolrate;
					Log.i(TAG, "getSymbolRate_JavInst SymbolRate " + symbolRate[0]);
				}
			} catch (IllegalStateException e) {
				//e.printStackTrace();
			}
		}
		return 0;
	}

	public int getActualChanBandwidth_JavaInst(final int bandwidth[]) {
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA && sig != null) {
			Log.i(TAG, " DVBT Mode BW while query " + sig.bandwidth);
			bandwidth[0] = sig.bandwidth;
		}
		return 0;
	}
	
	public int getTPSId_JavaInst(final int TPSId[]){
		Log.v(TAG, "getTpsID_JavaInst");
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			try {
				try {
					if (t == null) {
						Log.v (TAG, "T params not ready. Reacquirring");
						t = sessionHandlerInstance.getSessionContext().getITuningDvbT();
						sig = new SignalInfo();
						tSpec = new ParamsDvbTSpecific();
						t2Spec = new ParamsDvbT2Specific();						
					}
				}
				catch (Exception e)
				{
				}
				if(t != null) {
					t.getParams(sig, tSpec, t2Spec);
					if (sig != null) {
						TPSId[0] = sig.cellid;
						Log.i(TAG, " DVBT Mode TPSId while query " + sig.cellid);
					}
				}
			} catch (IllegalStateException e) {
				Log.v(TAG, "getSigConstellation : IllegalStateException while calling getParams");
			}
		}
		return 0;
	}

	public int getStreamPriority_JavaInst(final int streamPrio[]) {
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if (tSpec != null) {
				streamPrio[0] = tSpec.streamprio;
			}
		}
		return 0;
	}

	public int getHierarchyMode_JavaInst(final int HierarchyMode[]) {
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if (tSpec != null) {
				if (tSpec.hiermode == true) {
					HierarchyMode[0] = 1;
					Log.i(TAG, "getHierarchyMode_JavaInst tSpec.hiermode" + HierarchyMode[0]);
				} else {
					HierarchyMode[0] = 0;
				}

			}
		}
		Log.d(TAG, "getHierarchyMode_JavaInst " + HierarchyMode[0]);
		return 0;
	}

	public int getActualConstellation_JavaInst(final int constellation[]) {
		if(sessionTuneMedium != null) {
			if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
				try {
					if(t != null) {
						t.getParams(sig, tSpec, t2Spec);
						if (sig != null) {
							constellation[0] = sig.constellation;
						}
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSigConstellation : IllegalStateException while calling getParams");
				}
			} else if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
				try {
					Log.v(TAG, "getSigConstellation DVBC");
					if(c != null) {
						c.getParams(params);
						if (params != null) {
							constellation[0] = params.constellation;
						}
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSigConstellation : IllegalStateException while calling getParams");
				}
			}
		}
		Log.i(TAG, "getActualConstellation_JavaInst Exit " + constellation[0]);
		
		return 0;
	}

	public int setConstellation_JavaInst(int constellation) {

		return 0;
	}

	public int getBer_JavaInst(final int Ber[]) {
		Ber[0] = 0;
		return 0;
	}

	public int getCarrierPresent_JavaInst(final int Present[]) {
		Present[0] = 0;
		return 0;
	}

	public int getSigStrengthRange_JavaInst(int MinStrength, int MaxStrength) {
		return 0;
	}

	public int start_JavaInst(int ssm, boolean Avail) {
		return 0;
	}

	public int stop_JavaInst(int ssm, boolean Stopped) {
		return 0;
	}

	public int getMeasValid_JavaInst(int ssm, boolean Valid) {
		return 0;
	}

	public int getSigStrength_JavaInst(int ssm, int Strength[]) {

		int sigStrengthValue = 0;
		int sigQualityalue = 0;

		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if (t != null) {
				try {
					try {
						/* Handling below use case.
							1. Zap triggered at end of installation. On ChannelChangeStart and ChannelChangeEnd notifications received. 
							2. OnChannelChangeEnd notification, tuning/DVBT/C/Analog interfaces queried.
							3. Interfaces may not be ready. 
							4. OnChannelRetuned comes late. Next time Native background installation queries the T/C parameters, interfaces are NULL.
							So on first query reacquiring the interface if not already received */
						if (t == null) {
							Log.v (TAG, "T params not ready. Reacquirring");
							t = sessionHandlerInstance.getSessionContext().getITuningDvbT();
							sig = new SignalInfo();
							tSpec = new ParamsDvbTSpecific();
							t2Spec = new ParamsDvbT2Specific();						
						}
					}
					catch (Exception e)
					{
					}

					t.getParams(sig, tSpec, t2Spec);
					if (sig != null) {
						sigStrengthValue = sig.ssi;
						sigQualityalue = sig.sqi;
					}
				} catch (IllegalStateException e) {
					//e.printStackTrace();
				}

			}
		} else if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			if (c != null) {
				try {
					c.getParams(params);
					if (params != null) {
						sigStrengthValue = params.ssi;
						sigQualityalue = params.sqi;
					}
				} catch (IllegalStateException e) {
					//e.printStackTrace();
				}
			}
		} else if (sessionTuneMedium == SESSION_MEDIUM.ANALOG) {
			if (a != null) {
				try {
					sigStrengthValue = a.getSSI();
				} catch (IllegalStateException e) {
					//e.printStackTrace();
				}
			}
		}
		switch (ssm) {
		case 0: // assm
		case 1: // vssm
			Strength[0] = sigStrengthValue;
			break;
		case 2: // Qssm
		case 3: // Sssm
		default:
			Strength[0] = sigQualityalue;
			break;
		}

		Log.i(TAG, "SignalStregth for " + ssm + "is" + Strength[0]);
		return 0;
	}

	// For Events from the Native Layer
	public int javaInstaller_onEvent(int eventid, int val) {
		Log.d(TAG, "onEvent from native eventid " + eventid + " val " + val);

		if (eventid == euEventConst.IHsvInstallationNotify_EventInstallationCompleted) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_INST_COMPLETED, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventInstallationStarted) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_INST_STARTED, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventInstallationStopped) {
			
			SetHostControlStatus(true);
			ntf.notifyAllObservers(EventIDs.EVENT_INST_STOPPED, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventInstallationPaused) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventInstallationContinued) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventChannelFound) {
			
			if (sessionTuneMedium == SESSION_MEDIUM.ANALOG) {
				ntf.notifyAllObservers(EventIDs.EVENT_ANALOG_CH_FOUND, "");
			} else {
				ntf.notifyAllObservers(EventIDs.EVENT_DIGIT_CH_FOUND, "");
			}
			ntf.notifyAllObservers(EventIDs.EVENT_SHOW_SEARCH_AFTER_STRING, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventChannelNotFound) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_INST_CHANNEL_NOT_FOUND, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventSearchInProgress) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_INST_PROGRESS, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventTuningStarted) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventTuningStationFound) {
			
			if (sessionTuneMedium == SESSION_MEDIUM.ANALOG) {
				ntf.notifyAllObservers(EventIDs.EVENT_ANALOG_CH_FOUND, "");
			} else {
				ntf.notifyAllObservers(EventIDs.EVENT_INST_TUNING_STATION_FOUND, "");
			}
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventTuningStationNotFound) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_INST_TUNING_STATION_NOT_FOUND, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventManualInstallationCniExtractionStarted) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventManualInstallationCniExtractionEnded) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventATSSortingStarted) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventAciStoreStarted) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_ANALOG_CH_FOUND, "");
			Log.v(TAG, "EVENT_ANALOG_CH_FOUND signalled on ACI Installation complete");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventTvSystemChanged) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventMediumChanged) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventSignalStrengthChanged) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventBackGroundCNIUpdated) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventPresetStored) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_SHOW_MANUAL_STORE_MESSAGE, Integer.toString(val));
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventPhaseStarted) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventPhaseCompleted) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventChannelIterationStarted) {
			ntf.notifyAllObservers(EventIDs.EVENT_INST_SORT_STARTED, "");
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventHeirarchyModeDetected) {
			ntf.notifyAllObservers(EventIDs.EVENT_HIERARCHICAL_MUX_FOUND, "");
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventChannelAdded) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_DIGIT_CH_ADDED, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventChannelRemoved) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_DIGIT_CH_REMOVED, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventNetworkUpdateDetected) {
			
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_UPDATE_DETECTED, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventDisplayNetworkNames) {
			ntf.notifyAllObservers(EventIDs.EVENT_FAV_NETWORK, "");
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventNIDInvalid) {
			
			if (val == 1) {
				ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_ID, "");
			}
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventNetworkUpdateNotDetected) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventOnConflictsDetected) {
			ntf.notifyAllObservers(EventIDs.EVENT_LCN_CONFLICT, "");
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventDisplayRegionNames) {
			ntf.notifyAllObservers(EventIDs.RESET_REGION_SELECTION, "");
			ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
			
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventPLPsDetected) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_PLPIDS_DETECTED, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_NetworkOperator) {
			
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventCamInstallRequestNormal) {
			
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.EVENT_CAM_INSTALL_REQUEST_NORMAL, "dialog");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventCamInstallRequestUrgent) {
			
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.EVENT_CAM_INSTALL_REQUEST_URGENT, "urgent");
		}
		if (eventid == euEventConst.IHsvInstallationNotify_EventPresetAdded) {
			ntf.notifyAllObservers(EventIDs.EVENT_MAJORVERSION_UPDATE, "");
		}
		if (eventid == euEventConst.IHsvInstallationNotify_EventPresetDeleted) {
			ntf.notifyAllObservers(EventIDs.EVENT_MAJORVERSION_UPDATE, "");
		}
		if (eventid == euEventConst.IHsvInstallationNotify_EventUpdated) {
			 ntf.notifyAllObservers(EventIDs.EVENT_MAJORVERSION_UPDATE, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventMultiPackageFound) {
			
			mCurrentACIIndex = 0;
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventMultiPackageToBeDisplayed) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_LAUNCH_ACI_PAGE, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventMultiPackageRemoved) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_CLOSE_ACI_PAGE, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventNewPresetNumber) {
			Log.d(TAG, " Raise a intent to playtv prestNumber " + Integer.toString(val));
			ntf.notifyAllObservers(EventIDs.EVENT_NEWPRESETNUMBER, Integer.toString(val));
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventTelenetNameUpdate) {
			Log.i(TAG, " Telenet: ChannelName Updated for Preset : " + Integer.toString(val));
			ntf.notifyAllObservers(EventIDs.EVENT_TELENET_NAME_UPDATE, Integer.toString(val));
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventTelenetMajorVersionUpdate) {
			
			ntf.notifyAllObservers(EventIDs.EVENT_TELENET_MAJOR_VERSION_UPDATE, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventDisplayChannelListId) {
			
			  ntf.notifyAllObservers(EventIDs.EVENT_FAV_CHANNELLIST, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventLanguageUpdate) {
			
			  ntf.notifyAllObservers(EventIDs.EVENT_LANGUAGE_UPDATED, Integer.toString(val));
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventChannelNameUpdate) {
			  ntf.notifyAllObservers(EventIDs.EVENT_CHANNEL_NAME_UPDATED, Integer.toString(val));
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventServiceFound) {
			  ntf.notifyAllObservers(EventIDs.EVENT_SERVICE_FOUND, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventServiceNotFound) {
			  ntf.notifyAllObservers(EventIDs.EVENT_SERVICE_NOT_FOUND, "");
		} else if (eventid == euEventConst.IHsvInstallationNotify_EventT2SwitchPLPID) {
			  ntf.notifyAllObservers(EventIDs.EVENT_T2_SWITCH_PLP_ID, Integer.toString(val));
		}
		

		return 0;
	}

	public void StopOngoingScan() {
		if(ifValidSession()){
	
			if ((frontendTun != null) && (IsScanOngoing == true)) {
				try {
					IsScanOngoing = false;
					frontendTun.scanAbort();
				} catch (IllegalStateException e) {
					Log.e(TAG, "StopOngoingScan exiting ");
				}
			}
		}
	}
	
	public boolean isOperatorProfileSupported() {
		Log.i(TAG, "isOperatorProfileSupported: sessionTuneMedium = " + sessionTuneMedium + "camDeliverySysHint = " + camDeliverySysHint);
		boolean l_ret = isOPSupported;

		if (((camDeliverySysHint & CAM_DVBS_HINT) > 0) && ((camDeliverySysHint & CAM_DVBC_HINT) == 0) && ((camDeliverySysHint & CAM_DVBT_HINT) == 0)) {
			Log.i(TAG, "Improper delivery system hint for DVBC. camDeliverySysHint = " + camDeliverySysHint);
			l_ret = false;
		}
		Log.d(TAG, "isOperatorProfileSupported returning " + l_ret);

		return l_ret;
	}

	public String getOperatorName() {
		String l_opName = "";

		l_opName = GetCamProfileName();

		// return l_statusInfo.profile_Name;

		return l_opName;

	}

	public void UnregisterTuningNotification() {
		if (frontendTun != null) {
			Log.v(TAG, "UnregisterTuningNotification unregister");
			try {
				frontendTun.unregisterListener(onChangeListener);
			} catch (IllegalStateException e) {
				Log.v(TAG, "UnregisterTuningNotification unregister : IllegalStateException");
			}
			frontendTun = null;
			t = null;
			c = null;
			a = null;
		}
	}

	public void SetAciSurface(Surface txtsurface) {
		SetGfxHandle(txtsurface);
		StartPageDisplay();
	}

	public void MoveToNextAciItem() {

		if (mCurrentACIIndex < (GetNoOfMtpItems() - 1)) {
			Log.v(TAG, "MoveToNextAciItem ");
			RemoveCursor();
			mCurrentACIIndex++;
			SetCursor(mCurrentACIIndex);
		}
	}

	public void MoveToPreviousAciItem() {

		if (mCurrentACIIndex > 0) {
			Log.v(TAG, "MoveToPreviousAciItem Entered");
			RemoveCursor();
			mCurrentACIIndex--;
			SetCursor(mCurrentACIIndex);
		}
	}

	public void SelectAciItem() {
		SelectIndex((int) mCurrentACIIndex);
	}

	public int getSignalBer() {
		int berValue = 0;
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if(t != null) {
				try {
					t.getParams(sig, tSpec, t2Spec);
					if (sig != null) {
						berValue = sig.ber;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSignalBer : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSignalBer : intf t is null!!!");
			}
		} else if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			if(c != null) {
				try {
					c.getParams(params);
					if (params != null) {
						berValue = params.ber;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSignalBer : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSignalBer : intf c is null");
			}
		}
		return berValue;
	}

	public int getSignalStrenght(int measmode) {
		int sigStrengthValue = 0;
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if(t != null) {
				try {
					t.getParams(sig, tSpec, t2Spec);
					if (sig != null) {
						sigStrengthValue = sig.ssi;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSignalStrenght : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSignalStrenght : intf t is null!!!");
			}
		} else if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			if(c != null) {
				try {
					c.getParams(params);
					if (params != null) {
						sigStrengthValue = params.ssi;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSignalStrenght : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSignalStrenght : intf c is null!!!");
			}
		}
		return sigStrengthValue;
	}

	public int getSignalQuality() {
		int sigQualityalue = 0;
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if(t != null) {
				try {
					t.getParams(sig, tSpec, t2Spec);
					if (sig != null) {
						sigQualityalue = sig.sqi;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSignalQuality : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSignalQuality : intf t is null!!!");
			}
		} else if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			if(c != null) {
				try {
					c.getParams(params);
					if (params != null) {
						sigQualityalue = params.sqi;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSignalQuality : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSignalQuality : intf c is null!!!");
			}
		}
		return sigQualityalue;
	}

	public int getSigBanwidth() {
		int sigbandwidthValue = 0;
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if(t != null) {
				try {
					t.getParams(sig, tSpec, t2Spec);
					if (sig != null) {
						sigbandwidthValue = sig.bandwidth;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSigBanwidth : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSigBanwidth : intf t is null!!!");
			}
		}
		return sigbandwidthValue;
	}

	public int getSigConstellation() {
		int sigConsteValue = 0;
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if(t != null) {
				try {
					t.getParams(sig, tSpec, t2Spec);
					if (sig != null) {
						sigConsteValue = sig.constellation;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSigConstellation : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSigConstellation : intf t is null!!!");
			}
		} else if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			if(c != null) {
				try {
					c.getParams(params);
					if (params != null) {
						sigConsteValue = params.constellation;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSigConstellation : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSigConstellation : intf c is null!!!");
			}
		}
		Log.i(TAG, "getSigConstellation End" + sigConsteValue);
		return sigConsteValue;
	}

	public int getSigSymbolRate() {
		int sigSymRateValue = 0;
		if (sessionTuneMedium == SESSION_MEDIUM.CABLE) {
			if(c != null) {
				try {
					c.getParams(params);
					if (params != null) {
						sigSymRateValue = params.symbolrate;
						Log.i(TAG, "getSigSymbolRate symbolrate" + sigSymRateValue);
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSigSymbolRate : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSigSymbolRate : intf c is null!!!");
			}
		}
		return sigSymRateValue;
	}

	public int getSigStreamPriority() {
		int sigPriorityValue = 0;
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if(t != null) {
				try {
					t.getParams(sig, tSpec, t2Spec);
					if (tSpec != null) {
						sigPriorityValue = tSpec.streamprio;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSigStreamPriority : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSigStreamPriority : intf t is null!!!");
			}
		}
		return sigPriorityValue;
	}

	public boolean getSigHiermode() {
		boolean sigHiermodeValue = false;
		if (sessionTuneMedium == SESSION_MEDIUM.ANTENNA) {
			if( t != null) {
				try {
					t.getParams(sig, tSpec, t2Spec);
					if (tSpec != null) {
						sigHiermodeValue = tSpec.hiermode;
					}
				} catch (IllegalStateException e) {
					Log.v(TAG, "getSigHiermode : IllegalStateException while calling getParams");
				}
			}else {
				Log.v(TAG, "getSigHiermode : intf t is null!!!");
			}
		}
		return sigHiermodeValue;
	}

	public int[] getSymbolRateRange() {
		int[] returnSymRateRange = new int[2];
		returnSymRateRange[0] = ITuningDvbC.TUNING_DVBC_SYMBOLRATE_MIN;
		returnSymRateRange[1] = ITuningDvbC.TUNING_DVBC_SYMBOLRATE_MAX;
		return returnSymRateRange;
	}

	public String GetCamProfileName() {
		int i = 0;
		char[] ProfileName = new char[mProfileNameLength];
		for (i = 0; i < mProfileNameLength; i++) {
			ProfileName[i] = (char) mProfileName[i];
		}
		String CamProfileName = new String(ProfileName);
		return CamProfileName;
	}

	public int GetT2CarrierPresent_JavaInst(final boolean Present[]) {

		Log.i(TAG, "sessionTuneMedium " + sessionTuneMedium);
		if (t != null) {
			try {
				t.getParams(sig, tSpec, t2Spec);
				Log.i(TAG, "####  Sig Param " + sig.standard);
				DetectedStandard = sig.standard;
			} catch (IllegalStateException e) {
				Log.v(TAG, "GetT2CarrierPresent_JavaInst : IllegalStateException");
			}
		}

		Log.i(TAG, "DetectedStd " + DetectedStandard);
		if (DetectedStandard == 2) /* ANEESH: REmove this hardcoding */
		{
			Log.i(TAG, "GetT2CarrierPresent_JavaInst DVBT2 " + DetectedStandard);
			Present[0] = true;
		} else {
			Log.i(TAG, "GetT2CarrierPresent_JavaInst DVBT " + DetectedStandard);
			Present[0] = false;
		}
		return 0;
	}

	public int GetActivePlpId_JavaInst(final int PlpId[]) {
		if(t != null) {
			try {
				t.getParams(sig, tSpec, t2Spec);
				PlpId[0] = t2Spec.activeplp;
			} catch (IllegalStateException e) {
				Log.v(TAG, "GetActivePlpId_JavaInst : IllegalStateException");
			}
		}else {
			Log.v(TAG, "GetActivePlpId_JavaInst : intf t is null!!!");
		}
		return 0;
	}

	public int SelectPlpId_JavaInst(int PlpId) {
		if(t != null) {
			try {
				t.setPLP(PlpId);
			} catch (IllegalStateException e) {
				Log.v(TAG, "SelectPlpId_JavaInst : IllegalStateException");
			}
		}else {
			Log.v(TAG, "SelectPlpId_JavaInst : intf t is null!!!");
		}
		return 0;
	}

	public int GetDetectedPlpIds_JavaInst(int NoOfRfids[], int PlpIds[]) {
		int i = 0;
		if(t != null) {
			try {
				t.getParams(sig, tSpec, t2Spec);
				NoOfRfids[0] = t2Spec.plpcount;
				for (i = 0; i < t2Spec.plpcount; i++) {
					PlpIds[i] = (int) t2Spec.plpids[i];
				}
			} catch (IllegalStateException e) {
				Log.v(TAG, "GetDetectedPlpIds_JavaInst : IllegalStateException");
			}
		}else {
			Log.v(TAG, "GetDetectedPlpIds_JavaInst : intf t is null!!!");
		}
		return 0;
	}

	public int[] GetDetectedPlpIds_Tvplayer() {
		int i = 0;
		int PlpIds[] = null;
		
		if(t != null) {
			try {
				t.getParams(sig, tSpec, t2Spec);
				// int NoOfRfids[0] = t2Spec.plpcount;
				PlpIds = new int[t2Spec.plpcount];
				for (i = 0; i < t2Spec.plpcount; i++) {
					PlpIds[i] = (int) t2Spec.plpids[i];
				}
			} catch (IllegalStateException e) {
				Log.v(TAG, "GetDetectedPlpIds_Tvplayer : IllegalStateException");
			}
		}else {
			Log.v(TAG, "GetDetectedPlpIds_Tvplayer : intf t is null!!!");
		}
		return PlpIds;
	}

	public void RequestStatusInfo_JavaInst() {
		if (ifValidSession()) {
			ITvMediaOp tvMediaOp = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(tvMediaOp != null) {
				tvMediaOp.requestOpStatusInfo();
			}
		} else {
			Log.v(TAG, "invalid session RequestStatusInfo_JavaInst");
		}
	}

	public void RequestNit_JavaInst() {
		if (ifValidSession()) {
			ITvMediaOp tvMediaOp = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(tvMediaOp != null) {
				tvMediaOp.requestOpNit();
			}
		} else {
			Log.v(TAG, "invalid session RequestNit_JavaInst");
		}
	}

	public void SendOpExit_JavaInst() {
		if (ifValidSession()) {
			ITvMediaOp tvMediaOp = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(tvMediaOp != null) {
				tvMediaOp.sendOpExit();
			}
		} else {
			Log.v(TAG, "invalid session SendOpExit_JavaInst");
		}
	}

	public void SendOpAck_JavaInst() {
		if (ifValidSession()) {
			ITvMediaOp tvMediaOp = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(tvMediaOp != null) {
				tvMediaOp.sendOpEntAck();
			}
		} else {
			Log.v(TAG, "invalid session SendOpAck_JavaInst");
		}
	}

	public void SendOpSearchCancel_JavaInst() {
		if (ifValidSession()) {
			ITvMediaOp tvMediaOp = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(tvMediaOp != null) {
				tvMediaOp.sendOpSearchCancel();
			}
		} else {
			Log.v(TAG, "invalid session SendOpSearchCancel_JavaInst");
		}
	}

	public void mCacheOperatorData_JavaInst() {
		if (ifValidSession()) {
			ITvMediaOp tvMediaOp = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(tvMediaOp != null) {
				tvMediaOp.storeOperatorData();
			}
		} else {
			Log.v(TAG, "invalid session mCacheOperatorData_JavaInst");
		}
	}

	public void SendOperatorSearchStart_JavaInst(int Unattended_Flag, int Service_Type_Length, int Service_Type[], int Delivery_Cap_Length, int Delivery_Capability[], int Application_Cap_Length,
			int Application_Capability[]) {
		int i = 0;
		OpSearchSettings settings = new OpSearchSettings();

		settings.Unattended_Flag = Unattended_Flag;
		settings.Service_Type_Length = Service_Type_Length;
		settings.Service_Type = new int[Service_Type_Length];
		for (i = 0; i < Service_Type_Length; i++) {
			settings.Service_Type[i] = Service_Type[i];
			Log.i(TAG, " " + settings.Service_Type[i]);
		}
		settings.Delivery_Cap_Length = Delivery_Cap_Length;
		settings.Delivery_Capability = new int[Delivery_Cap_Length];
		for (i = 0; i < Delivery_Cap_Length; i++) {
			settings.Delivery_Capability[i] = Delivery_Capability[i];
			Log.i(TAG, " " + settings.Delivery_Capability[i]);
		}
		settings.Application_Cap_Length = Application_Cap_Length;
		settings.Application_Capability = new int[Application_Cap_Length];
		for (i = 0; i < Application_Cap_Length; i++) {
			settings.Application_Capability[i] = Application_Capability[i];
			Log.i(TAG, " " + settings.Application_Capability[i]);
		}
		Log.i(TAG, "SendOperatorSearchStart_JavaInst Values are " + settings.Unattended_Flag + settings.Service_Type_Length + settings.Delivery_Cap_Length + settings.Application_Cap_Length);

		if (ifValidSession()) {
			ITvMediaOp tvMediaOp = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(tvMediaOp != null) {
				tvMediaOp.sendOpSearchStart(settings);
			}
		} else {
			Log.v(TAG, "invalid session SendOperatorSearchStart_JavaInst");
		}
	}

	public void SendOpTuneStatus_JavaInst(int Descriptor_Number, int Signal_Strength, int Signal_Quality, int Status, int Descriptor_Loop_Length, int Descriptor_Loop[]) {
		int i = 0;
		OPTuneStatus status = new OPTuneStatus();

		status.Descriptor_Number = Descriptor_Number;
		status.Signal_Strength = Signal_Strength;
		status.Signal_Quality = Signal_Quality;
		status.Status = Status;
		status.TuneDataLength = Descriptor_Loop_Length;
		status.TuneData = new int[Descriptor_Loop_Length];

		Log.i(TAG, "SendOpTuneStatus_JavaInst Tune data status value is" + status.Status + Status);

		for (i = 0; i < status.TuneDataLength; i++) {
			status.TuneData[i] = Descriptor_Loop[i];
			Log.i(TAG, "SendOpTuneStatus_JavaInst Tune data value is " + status.TuneData[i]);
		}

		if (ifValidSession()) {
			ITvMediaOp tvMediaOp = sessionHandlerInstance.getSessionContext().getITvMediaOp();
			if(tvMediaOp != null) {
				tvMediaOp.sendOpTuneStatus(status);
			}
		} else {
			Log.v(TAG, "invalid session SendOpTuneStatus_JavaInst");
		}
	}


	class CIChangeListener extends IOnCIChangeListener {
		@Override
		public void onCAMStatusChanged(int Status) {
			// To do for Op Schedule Update
			Log.i(TAG, "onCAMStatusChanged Status" + Status);
			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.EVENT_CAM_STATUS, Integer.toString(Status));
		}
	}

	class OpChangeListener extends IOnOpChangeListener {
		@Override
		public void onOpSearchStatus(OpProfileSearchStatus opStatus) {

			opProfileSearchStatus status = new opProfileSearchStatus();

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

			ntf.registerForNotification(NativeAPIWrapper.getInstance());
			ntf.notifyAllObservers(EventIDs.EVENT_CAM_SCHEDULE_UPDATE_INSTALL_DONE, "");
			OnOpSearchStatus(status);
		}

		@Override
		public void onOpStatusInfo(OpProfileStatusInfo statusInfo) {

			int i = 0;
			isOPSupported = true;
			opProfileStatusInfo statusinfo = new opProfileStatusInfo();

			statusinfo.Info_Version = statusInfo.Status_Info_Version;
			statusinfo.NIT_Version = statusInfo.NIT_Version;
			statusinfo.Profile_Type = statusInfo.Profile_Type;
			statusinfo.Initialised_Flag = statusInfo.Initialised_Flag;
			statusinfo.Entitlement_Change_Flag = statusInfo.Entitlement_Change_Flag;
			statusinfo.Entitlement_Valid_Flag = statusInfo.Entitlement_Valid_Flag;
			statusinfo.Refresh_Request_Flag = statusInfo.Refresh_Request_Flag;
			statusinfo.Error_Flag = statusInfo.Error_Flag;
			statusinfo.Delivery_System_Hint = statusInfo.Delivery_System_Hint;
			statusinfo.Refresh_Request_Date = statusInfo.Refresh_Request_Date;
			statusinfo.Refresh_Request_Time = statusInfo.Refresh_Request_Time;

			statusinfo.InfoValid = statusInfo.info_Valid;
			statusinfo.ProfileInfoVersion = statusInfo.info_Version;
			statusinfo.CiCamOriginalNetworkId = statusInfo.cicam_Original_Network_Id;
			statusinfo.CiCamIdentifier = statusInfo.cicam_Identifier;
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

			camDeliverySysHint = statusinfo.Delivery_System_Hint;
			statusinfo.ISO639LangCode = new int[3];
			for (i = 0; i < 3; i++)
				statusinfo.ISO639LangCode[i] = statusInfo.iSO_639_Lang_Code[i];

			statusinfo.ProfileNameLength = statusInfo.profile_Name_Length;
			mProfileNameLength = statusInfo.profile_Name_Length;
			Log.i(TAG, "Profile name length is %d" + mProfileNameLength);
			// Log.d(TAG, "Profile name is %s" + mProfileName);
			mProfileName = new int[mProfileNameLength];
			statusinfo.ProfileName = new int[mProfileNameLength];
			for (i = 0; i < statusinfo.ProfileNameLength; i++) {
				statusinfo.ProfileName[i] = statusInfo.profile_Name[i];
				mProfileName[i] = statusInfo.profile_Name[i];
			}

			if (statusinfo.InfoValid == 0) {
				Log.v(TAG, "As Info valid is 0.. assign hard coded name as CI+CAMPROFILE");
				mProfileName = new int[13];
				mProfileName[0] = 67;
				mProfileName[1] = 73;
				mProfileName[2] = 43;
				mProfileName[3] = 67;
				mProfileName[4] = 65;
				mProfileName[5] = 77;
				mProfileName[6] = 80;
				mProfileName[7] = 82;
				mProfileName[8] = 79;
				mProfileName[9] = 70;
				mProfileName[10] = 73;
				mProfileName[11] = 76;
				mProfileName[12] = 69;
				mProfileNameLength = 13;
			}

			if (statusinfo.Refresh_Request_Flag == 3) {
				Log.v(TAG, "Op statusInfo not send to MW as it is Schedule Update\n");
				ntf.registerForNotification(NativeAPIWrapper.getInstance());
				ntf.notifyAllObservers(EventIDs.EVENT_CAM_SCHEDULE_UPDATE_DATE, Integer.toString(statusinfo.Refresh_Request_Date));
				Log.v(TAG, "onEvent to Notifiers  EVENT_CAM_SCHEDULE_UPDATE_TIME");
				ntf.notifyAllObservers(EventIDs.EVENT_CAM_SCHEDULE_UPDATE_TIME, Integer.toString(statusinfo.Refresh_Request_Time));
			}
			// else
			// {
			OnOpStatusInfo(statusinfo);
			// }
		}

		@Override
		public void onOpNIT(OpProfileNitData nitData) {

			int i = 0;
			opProfileNitData nitdata = new opProfileNitData();
			nitdata.NitStatus = nitData.NitStatus;
			if (nitdata.NitStatus == 1) {
				nitdata.NitDataLength = nitData.NitDataLength;
				nitdata.NitData = new int[nitdata.NitDataLength];
				for (i = 0; i < nitdata.NitDataLength; i++)
					nitdata.NitData[i] = nitData.NitData[i];
			} else {
				Log.v(TAG, "Native onOpNIT is not processed as it is invalid/Timeout");
			}

			OnOpNIT(nitdata);
		}

		@Override
		public void onOpTune(OpProfileTuneData tuneData) {

			int i = 0;
			opProfileTuneData tunedata = new opProfileTuneData();

			tunedata.TuneDataLength = tuneData.TuneDataLength;
			tunedata.TuneData = new int[tunedata.TuneDataLength];
			for (i = 0; i < tunedata.TuneDataLength; i++)
				tunedata.TuneData[i] = tuneData.TuneData[i];

			OnOpTune(tunedata);
		}

	}
	
	public void registerCIListener() {
		if(ifValidSession()){
			ITVCIControl tvCiControl = sessionHandlerInstance.getSessionContext().getITVCIControl();
			if(tvCiControl != null) {
				tvCiControl.enableCAMUI(true);
			}else {
				Log.e(TAG, "registerCIListener failed!!!");
			}
		}
	}

	public void unRegisterCIListener() {
		if(ifValidSession()){
			ITVCIControl tvCiControl = sessionHandlerInstance.getSessionContext().getITVCIControl();
			if(tvCiControl != null) {
				tvCiControl.enableCAMUI(false);
			}else {
				Log.v(TAG, "unRegisterCIListener failed!!!");
			}
		}
	}

}
