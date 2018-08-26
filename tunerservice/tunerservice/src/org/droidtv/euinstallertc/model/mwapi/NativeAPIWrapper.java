/*
/*
 *  Copyright(C) 2012 TP Vision Holding B.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of TP Vision Holding B.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of TP Vision Holding B.V.
 *
 */
package org.droidtv.euinstallertc.model.mwapi;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Observable;
import java.util.Timer;
import java.util.concurrent.Semaphore;
import java.util.List;
import java.io.File;
import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallertc.model.mwapi.MwDataTypes.InstallerConstants;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.AnalogSystemCountry;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.ApplicationState;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DTRScreenMode;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DVBTOrDVBC;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DVBTOrDVBCMacro;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.InstallationMode;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_MEDIUM;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallertc.model.notification.INotificationListener;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.notification.CamUpdateDialogActivity;
import org.droidtv.euinstallertc.notification.NetworkUpdateDialogActivity;
import org.droidtv.euinstallertc.service.EuInstallerService;
import org.droidtv.euinstallertc.service.LogoAssociationHandler;
import org.droidtv.euinstallertc.service.LogoAssociationHandler.ILogoAssociationListner;
import org.droidtv.euinstallertc.settings.ChannelSettingsActivity;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.euinstallertc.wizard.InstallerWizardActivity;
import org.droidtv.tv.audio.ITvAudioManager;
import org.droidtv.tv.frontend.ITuningAna;
import org.droidtv.tv.frontend.ITuningDvbC;
import org.droidtv.tv.frontend.ITuningDvbT;
import org.droidtv.tv.media.ITvMediaPlayerContext;
import org.droidtv.tv.media.ITvServerConfig;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.ITvSettingsManager.ITvSettingsManagerNotify;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tunerservice.util.PlayTvUtils;

import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.provider.IFrequencyListContract;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.tvclock.ITvClockManager;
import org.droidtv.tv.tvinput.ITVTunerSession;
//import com.android.providers.tv.TvProvider;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;

import android.annotation.SuppressLint;
import android.app.AlarmManager;
import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.OperationApplicationException;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.database.Cursor;
import android.media.tv.TvContentRating;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.media.tv.TvInputManager;
import android.media.tv.TvTrackInfo;
import android.database.ContentObserver;
import android.content.ContentResolver;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.Looper;
import android.os.Process;
import android.os.RemoteException;
import android.util.Log;
import android.util.SparseIntArray;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import android.media.tv.TvTrackInfo;
import android.media.tv.TvContentRating;
import android.media.tv.TvInputManager;

import android.media.tv.TvInputInfo;
import org.droidtv.htv.provider.HtvContract.HtvChannelList;
import org.droidtv.htv.provider.HtvContract;

import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.LastSelectedDeviceConstants;
import android.content.ContentProviderOperation;
import android.content.OperationApplicationException;
import android.os.RemoteException;
import android.content.ContentProviderResult;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import android.os.SystemProperties;


public class NativeAPIWrapper implements INotificationListener,ILogoAssociationListner {

	private static final String TAG = NativeAPIWrapper.class.getName();
	private Context ctx;
	
	private Context wizardActivityCtx = null;
	private Context settingsActivityCtx = null;
	private Context serviceCtx = null;
	
	// notification instance handler holder
	private NotificationHandler ntf = NotificationHandler.getInstance();
	private ITvSettingsManager mTvSettingsManager =ITvSettingsManager.Instance.getInterface();

	/*********************************************/
	private final boolean STUB_MODE = false;
	/*********************************************/
	private int mSearchingFrequency = 0;
	private int m_lastSelectedPresetTC = 0;

	// native api instance holder
	private EuInstallerTC euInst = new EuInstallerTC();
	private MwDataTypes mwInst = new MwDataTypes();
	private InstallerConstants euInstConst = mwInst.new InstallerConstants();

	private SharedPreferences mStoredSharedPreferences = null;
	private Editor edit = null;

	// TVSettings and TvSettingsManager ( Binder Wrapper)
	// local cached variables
	private int instProgressPercentage = 0;
	private int digitalChannelCount = 0;
	private int digitalChannelsRemoved = 0;
	private int analogueChannelCount = 0;
	private int selectedCountryID = 0;
	private int selectedRfSetting = 0;
	private int mTVSCselectedCountryID = 0;
	private String selectedOperatorStr = "";
	private boolean m_isHierarchicalMuxFound = false;
	private int timeZoneIndex = 0;
	private int operatorIndex = 0;
	private String timeZoneName = "";
	
	private int primaryRegionIndex = 0;
	private int secondaryRegionIndex = 0;
	private int lcnConflictChannelNumber = 0;

	private String[] primaryRegions;
	private String[] secondaryRegions;
	private String[] teritaryRegions;
	private String[] lcnServiceNames;
	private int[] plpIDs;
	private boolean opsemistandbyins = false;
	private int operatorIdTVS = 0;

	private NativeAPIEnums.AnalogSystemCountry analogSystemCountry = AnalogSystemCountry.EAST_EUROPE;
	private NativeAPIEnums.DVBTOrDVBC isDVBTorDVBC;
	private NativeAPIEnums.AnalogueOrDigital analogOrDigital = null;
	private NativeAPIEnums.InstallationMode currentInstallationMode = null;
	private NativeAPIEnums.Regions currentRegionMode = NativeAPIEnums.Regions.PRIMARY;
	private int isFreeOrFreeScrambled = 1;// 0:FTA only 1: SCR + FTA
	private boolean ifDigitalOn = true; // 0:off 1:on
	private int frequencyScanMode = 0; // quickscan fullscan
	private int frequencyStepSize = 0; // 1mhz 8mhz
	private int networkIDMode = 0; // 0:Automatic 1:Manual
	private int networkFreqMode = 0; // 0:Automatic 1:Manual

	private final int PRIMARY_REGION_CASE = 0;
	private final int SECONDARY_REGION_CASE = 1;
	private final int TERTIARY_REGION_CASE = 2;

	private TCSurface m_surface;
	// single instance holder
	private static NativeAPIWrapper singletonInstance = null;
	private boolean analogSourceSetupDone = false;
	public Object installerserviceschedulelock = new Object();
	public Object installerservicescheduleTime = new Object();
	private boolean m_isCamUpdateMode = false;
	private boolean ifStopAndRestartInstallation = false;
	public Handler mCipHandler = null;
	private ITvPowerManager mTvPowerManager = null;
	public boolean onAlarmFiredFlag = false;
	private SharedPreferences mCamScheduleShrdPref = null;
	private Editor editor = null;
	private NativeAPIEnums.ApplicationState currentAppState = NativeAPIEnums.ApplicationState.IDLE;

	private PowerStates currentPowerState;
	private ITvClockManager tvclkManager;
	private PowerStates fromPowerStates;
	private PowerStates toPowerStates;
	private String POWER_CHANGE_DETECTED = "POWER_CHANGE_DETECTED";
	private String FACTORY_RESET_DETECTED = "FACTORY_RESET_DETECTED";
	
	private String UDATE_NEEDED_NOTIFICATION = "UDATE_NEEDED_NOTIFICATION";
	private String CHANNEL_LIST_NOTIFICATION = "CHANNEL_LIST_NOTIFICATION";
	private String LCN_CONFLICT_NOTIFICATION = "LCN_CONFLICT_NOTIFICATION";
	private String DEFAULT_POWER_ON_CASE = "DEFAULT_POWER_ON_CASE";
	private String EXIT_INSTALLATION = "EXIT_INSTALLATION";

	private DTRScreenMode currentDTRScreenMode = DTRScreenMode.LOAD_CHANNEL_FREQ;
	private TvMediaPlayer tvMpl = null;
	private ITvMediaPlayerContext iTvMplCtx = null; 
	private ITvServerConfig iTvSrvConfig = null;
	
	public boolean ifPendingNonInteruptableRequest = false;
	private ArrayList<Timer> allTimerTasks = new ArrayList<Timer>();
	
	private BackgroundInstallation backInstallInst = null;
	private SemistandbyUpdate	ssbyInstallInst = null;
	private boolean IsMajorVersionChange = false;

	private LooperThread looperThread;
	private TvInputManager mTvInputManager = null;
	
	public static final int DATA_ALL_TABLE = 0;
	public static final int DATA_TS_TABLE = 1;
	private boolean ifEnteredSorting = false;
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;

	private String DB_UPDATE_BACKGROUND = "DB_UPDATE_BACKGROUND";
	private boolean ifAnalogDBSyncTriggered = false;
	private ITvAudioManager mTvAudioMgr =null;
	private Handler TVPHandler= new Handler();
	public static final String PACKAGE_NAME_TUNERSERVICE="org.droidtv.tunerservice";
	private TvProviderListener mObserver;
	private boolean IsBGInstallEnabled = true;
	private boolean IsChanneRenameInProgress = false;
	private boolean IsLogoAssociationOngoing = false;
	private int cachedMajorVesrion = 0;
	private boolean mStoreAsNewChannelEnabled = false;

	private final int SERVICE_TYPE_HEVC = 0x1F;
	private LogoAssociationHandler logoAssoHandler = new LogoAssociationHandler();
	private ILogoAssociationListner logoAssoListner = null;
	
	private boolean mbUseHtvDTRTuneType = false;
	private NativeAPIEnums.DVBTOrDVBC meHtvDTRTuneType;
	public static final String HTV_DT_CHANNEL_FLAG = "HTVDT";
	public static final String HTV_DI_CHANNEL_FLAG = "HTVDI";
	public static final String HTV_DI_CHANNEL_CHECK_FLAG = "HTVDICHK";
	public static final String HTV_DI_CHANNEL_UPDATE_FLAG = "HTVDIUPD";
	public static final String HTV_DT_CHANNEL_UPDATE_FLAG = "HTVDTUPD";
	private static final String KEYNAME_FORCE_CHANNEL_TUNING = "FRTUNE";
	private Semaphore mSemForHTVDT = null;
	private ArrayList<Long> mviHtvChNameUpdateList = new ArrayList<Long>();

	/* YanFu 2017/09/25 fix [GZ-CET][V5.249.5.075] Can't change channels by ch+/ch- and key numbers, can only select witch channel list */
	private static final String SOURCE_SELECT_CHANGE = "pbs.source.select.change";
	
	/**
	 * Private Constructor
	 */
	private NativeAPIWrapper() {
		looperThread = new LooperThread(); //Every slot will have one looper thread
		looperThread.start();
		mCipHandler = new Handler();
		mSemForHTVDT = new Semaphore(1, true);

		/*register notificartion for Major version change*/
		GlobalSettingsChangeListener GlobalSettingsListener = new GlobalSettingsChangeListener();
		int[] property = new int [1];
		property[0] = TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION;//220
		mTvSettingsManager.SetCallBacks(GlobalSettingsListener, property);
		cachedMajorVesrion = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, 0);
		
		synchronized(looperThread) {
				while(!looperThread.getLooperThreadHandlerStatus()) {
					try {
						Log.d(TAG,"Runnable waiting..");
						looperThread.wait();
						Log.d(TAG,"Runnable wait finish");
					} catch (InterruptedException e) {
						//e.printStackTrace();
					}
				}
			}
	}
	class  GlobalSettingsChangeListener extends ITvSettingsManagerNotify{
		public void OnUpdate(int iProperty){
			Log.d(TAG, "Notification From Global Setting Received for property:  " + iProperty + " IsChanneRenameInProgress: " + IsChanneRenameInProgress + " LogoAssociation: "+ IsLogoAssociationOngoing);
			if(iProperty == TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION){
				int MajorVesrion = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, 0);
				if(cachedMajorVesrion != MajorVesrion){
					if(true == IsChanneRenameInProgress){
						IsChanneRenameInProgress = false;
					}
					else if (true == IsLogoAssociationOngoing) {
						IsLogoAssociationOngoing = false;
					}
					else{
						Log.d(TAG, "CachedVersion" + cachedMajorVesrion + "NewVersion " + MajorVesrion);
						IsBGInstallEnabled = false;
						setBGInstalltoSharedPref(IsBGInstallEnabled);
					}
					cachedMajorVesrion = MajorVesrion;
				}
				else{
					Log.d(TAG, "Majorversion is not changed  " + MajorVesrion);
				}
			}
		}
	};

	// get single instance of NativeAPIHandler class
	public synchronized static NativeAPIWrapper getInstance() {
		if (singletonInstance == null) {
			singletonInstance = new NativeAPIWrapper();
		}
		return singletonInstance;
	}

	/**
	 * Sets the application context, all the resource calls will be on this
	 * context
	 * 
	 * @param Context
	 *            main application context
	 */
	public void setApplicationContext(Context appContext) {
		ctx = appContext;
		Log.d(TAG, "setApplicationContext " + appContext);
		NotificationHandler.getInstance().registerForNotification(this);
		// donot modify the existing stable functionality only 
		// add the required behavior that is why ctx is not modified
		if(appContext instanceof InstallerWizardActivity){
			wizardActivityCtx = appContext;
		}else if(appContext instanceof ChannelSettingsActivity){
			settingsActivityCtx = appContext;
		}else if(appContext instanceof EuInstallerService){
			serviceCtx = appContext;
		}
		
		if (STUB_MODE) {
		} else {
			euInst.initMainActivityInstance(appContext);
		}
		
		mStoredSharedPreferences = ctx.getApplicationContext().getSharedPreferences("euinstallertc", Context.MODE_PRIVATE);
		edit = mStoredSharedPreferences.edit();
		mCamScheduleShrdPref = ctx.getApplicationContext().getSharedPreferences("mCamScheduleShrdPref", Context.MODE_PRIVATE);
		editor  = mCamScheduleShrdPref.edit();
		IsBGInstallEnabled = getBGInstallFromSharedPref();
		
	}
	
	public Context getSettingsActivity(){
		Log.d(TAG, "getSettingsActivity() " + settingsActivityCtx);
		return settingsActivityCtx;
	}
	
	public Context getApplicationServiceContext(){
		Log.d(TAG, "getApplicationServiceContext " + serviceCtx);
		return serviceCtx;
	}

	public Context getCurrentContext(){
		Log.d(TAG, "getCurrentContext " + ctx);
		return ctx;
	}
	
	public void background_SetSystemCountry()
	{
		 Log.d(TAG, "background_SetSystemCountry()  ");
	        // directly read country from TVSettigns
	        mTVSCselectedCountryID = mTvSettingsManager.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
	        // update user selected country ID in EuinstallerTC
	        euInst.updateUserSelectedCountry(mTVSCselectedCountryID);

			
		//	isDVBTorDVBC= getSelectedDVBTOrDVBCFromTVS();		
	}
	
    public void autoSetSystemCountryToMW(Boolean ifSetCallToMW) {
        Log.d(TAG, "autoSetSystemCountryToMW() ifSetCallToMW " + ifSetCallToMW);
        // directly read country from TVSettigns
        mTVSCselectedCountryID = mTvSettingsManager.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
        // update user selected country ID in EuinstallerTC
        euInst.updateUserSelectedCountry(mTVSCselectedCountryID);
        if(ifSetCallToMW){
            // same country ID is mapped in MW
            euInst.SetSystemCountry(mTVSCselectedCountryID);
        }
    }
	

	public void createMWInstance() {
		Log.d(TAG, "createMWInstance start ");
		if (STUB_MODE) {

		} else {
			// create MW instance
			euInst.createMWInstance();
		}
		Log.d(TAG, "createMWInstance end ");
	}

	/*
	public void resetModeFlag() {
		euInst.resetMediumFlag();
	}

	public void SetModeFlag () {
		Log.d(TAG, "set_Medium start ");
		int dvbMediumID = mTvSettingsManager.getInt(
				TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
		euInst.SetMediumFlag(dvbMediumID);
		Log.d(TAG, "set_Medium end ");
	}
	
	public void set_Medium() {
		Log.d(TAG, "set_Medium start ");
		int dvbMediumID = mTvSettingsManager.getInt(
				TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
		euInst.SetMedium(dvbMediumID);
		Log.d(TAG, "set_Medium end ");
	}*/
		
	public void reInitializeCachedSelections() {
		instProgressPercentage = 0;
		digitalChannelCount = 0;
		digitalChannelsRemoved = 0;
		analogueChannelCount = 0;
		/* selectedCountryID = 0; */getSelectedCountyID();
		isDVBTorDVBC = getSelectedDVBTOrDVBCFromTVS();
		analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE;
		currentInstallationMode = NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION;
		selectedOperatorStr = "";
		isFreeOrFreeScrambled = 1; // all (free + scrambled)
		timeZoneName = "";
		timeZoneIndex = 0;
		
		if(ifVirginInstallation()){
			// update the country to mw
			mTVSCselectedCountryID = mTvSettingsManager.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
			// same country ID is mapped in MW 	355
			euInst.SetSystemCountry(mTVSCselectedCountryID);
		}
	}
	
	public void resetCachedBeforeInstallation(){
	    instProgressPercentage = 0;
        digitalChannelCount = 0;
        digitalChannelsRemoved = 0;
        analogueChannelCount = 0;
        ifAnalogDBSyncTriggered = false;
	}

	
	/**
	 * Returns the if Update Installation is supported
	 * 
	 * @param
	 * @return boolean if update installation is available
	 */
	public boolean ifUpdateInstallationSupported() {
		
		Boolean returnStatus = false;
		/*
		 * Update (Update digital channels) (*) (**) (*) Controllable: DVB-T
		 * Installation is supported: Always. DVB-C installation is supported:
		 * Channel list is not empty or the installation parameters (see
		 * functional part) are known. (**) Initially selected if controllable;
		 * else: Autostore.
		 */

		if (STUB_MODE) {
			returnStatus = false;
		} else {
			if (getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBT) {
				returnStatus = true;
			} else if ((getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC)
					&& (getNoOfInstalledChannels() > 0)) {
				returnStatus = true;
			}
		}
		return returnStatus;
	}

	/**
	 * Returns the if Update Installation is available
	 * 
	 * @param
	 * @return boolean if update installation is available
	 */
	public boolean ifUpdateInsatallationAvailable() {
		Boolean returnStatus = true;
		Boolean EnableDVBC = true;
		Boolean EnableDVBT = true;
		
		if (STUB_MODE) {
			returnStatus = true;
		} else {
			/*
			 * Update function available is true if Operator is not Ziggo/Other
			 * in case of DVB-C Netherlands AND - DVB-T full (not light!) OR -
			 * DVB-C full OR - DVB-C light and Digital channels is Yes. -
			 * Channel list is not empty.
			 */

		    String selectedCountryInTVS = getCountryNameFromTVS();
			NativeAPIEnums.DVBTOrDVBC selectedMediumInTVS = getSelectedDVBTOrDVBCFromTVS();
			if (getNoOfInstalledChannels() > 0) {
				if(PlayTvUtils.isPbsMode()) {
					EnableDVBC = (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_C_C2, 0, 0));
					EnableDVBT = (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_T_T2, 0, 0));

					if (EnableDVBC) {
						if (selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))) {
							if ((getOperatorFromTVS() == NativeAPIEnums.Operators.Ziggo) || (getOperatorFromTVS() == NativeAPIEnums.Operators.Other)) {
								returnStatus = false;
							}
						}
						if (selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))) {
							if (getOperatorFromTVS() == NativeAPIEnums.Operators.Telenet) {
								returnStatus = false;
							}
						}
						if (selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY)) || 
							selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN))) {
							if (getOperatorFromTVS() == NativeAPIEnums.Operators.CanalDigital) {
								if(getWSFreqScanMode() == 0)
									returnStatus = false;
							}
						}
						if (selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))) {
							if (getOperatorFromTVS() == NativeAPIEnums.Operators.YouSee) {
								if(getWSFreqScanMode() == 0)
								returnStatus = false;
							}
						}

						if (((false == ifDigitalOptionOn()) &&
							(countrySupportsDVBCFullorLite(selectedCountryInTVS) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)) ||
							((euInst.IsAvailable(euInstConst.IHsvInstallation2_InstallationModeAutomatic, euInstConst.IHsvInstallation2_AttributeUpdateInstall) == false)  )){
							returnStatus = false;
						}				
					} 

					if (EnableDVBT) {
						if ((countrySupportsDVBTFullorLite(selectedCountryInTVS) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light)) {
							returnStatus = false;
						}
					}
					
				}
				else {
				
				// some channels are installed
				Log.d(TAG, "ifUpdateInsatallationAvailable() 1 " + returnStatus);
				if ((selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBC)
						&& selectedCountryInTVS.equalsIgnoreCase(ctx
								.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))) {
					if ((getOperatorFromTVS() == NativeAPIEnums.Operators.Ziggo)
							|| (getOperatorFromTVS() == NativeAPIEnums.Operators.Other)) {
						returnStatus = false;
					}
				}

				Log.d(TAG, "ifUpdateInsatallationAvailable() 2 " + returnStatus);
				if ((selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBC)
						&& selectedCountryInTVS.equalsIgnoreCase(ctx
								.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))) {
					if (getOperatorFromTVS() == NativeAPIEnums.Operators.Telenet) {
						returnStatus = false;
					}
				}
				if ((selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBC)
						&& (selectedCountryInTVS.equalsIgnoreCase(ctx
								.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY)) || 
							selectedCountryInTVS.equalsIgnoreCase(ctx
								.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN)))) {
									if (getOperatorFromTVS() == NativeAPIEnums.Operators.CanalDigital) {
										if(getWSFreqScanMode() == 0)
											returnStatus = false;
									}
				}
				if ((selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBC)
						&& selectedCountryInTVS.equalsIgnoreCase(ctx
								.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))) {
					if (getOperatorFromTVS() == NativeAPIEnums.Operators.YouSee) {
						if(getWSFreqScanMode() == 0)
							returnStatus = false;
					}
				}

				Log.d(TAG, "ifUpdateInsatallationAvailable() 3 " + returnStatus);
				if (((selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBC)
						&& (false == ifDigitalOptionOn())
						&& (countrySupportsDVBCFullorLite(selectedCountryInTVS) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)) ||
						 ((euInst.IsAvailable(euInstConst.IHsvInstallation2_InstallationModeAutomatic, euInstConst.IHsvInstallation2_AttributeUpdateInstall) == false)  )){
					returnStatus = false;
				}

				Log.d(TAG, "ifUpdateInsatallationAvailable() 4 " + returnStatus);
				if ((selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBT)
						&& (countrySupportsDVBTFullorLite(selectedCountryInTVS) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light)) {
					returnStatus = false;
				}

				}

			} else {
				// no channels installed
				returnStatus = false;
			}

			// explicitly call getSelectedCountyID() to update the cached
			// country variable
			getSelectedCountyID();
		}

		Log.d(TAG, "ifUpdateInsatallationAvailable() " + returnStatus);
		return returnStatus;
	}

	/**
	 * ifDVBCSupportedCountry supports DVBC
	 * 
	 * @param
	 * @return returns true if the country supports DVB-C
	 */
	public boolean ifDVBCSupportedCountry(String argCountry) {
		boolean returnStatus = false;

		if ((countrySupportsDVBCFullorLite(argCountry) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Full)
				|| (countrySupportsDVBCFullorLite(argCountry) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)) {
			returnStatus = true;
		}

		Log.d(TAG, "ifDVBCSupportedCountry() " + argCountry + ":"
				+ returnStatus);
		return returnStatus;
	}

	/**
	 * ifDVBTSupportedCountry supports DVBC
	 * 
	 * @param
	 * @return returns true if the country supports DVB-C
	 */
	public boolean ifDVBTSupportedCountry(String argCountry) {
		boolean returnStatus = false;

		if ((countrySupportsDVBTFullorLite(argCountry) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Full)
				|| (countrySupportsDVBTFullorLite(argCountry) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light)) {
			returnStatus = true;
		}
		return returnStatus;
	}

	/**
	 * ifCountry supports DVBT-Full/Light
	 * 
	 * @param
	 * @return returns DVBT-Full or DVBT-Light or DVBT_NotSupported
	 */
	public NativeAPIEnums.DVBTOrDVBCMacro countrySupportsDVBTFullorLite(
			String argCountry) {
		NativeAPIEnums.DVBTOrDVBCMacro returnMacro = NativeAPIEnums.DVBTOrDVBCMacro.DVBT_NotSupported; // if
		// the
		// country
		// dosen't
		// support
		// DVB-T

		Log.d(TAG, "countrySupportsDVBTFullorLite argCountry " + argCountry);
		String[] dvbTFullCountry = { 
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELARUS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CROATIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CZECH_REP),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ESTONIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GREECE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ISRAEL),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LATVIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LITHUANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LUXEMBOURG),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MACEDONIA_FYROM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVAKIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UK),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UKRAINE), 
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AZERBAIJAN), /*AN-24687 */
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SERBIA),/*AN-45722 */
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TAIWAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA),
                ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UNITED_ARAB_EMIRATES),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM)};


		String[] dvbTLightCountry = { 
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ALBANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ARMENIA),
				/*ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AZERBAIJAN), */
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOSNIA_HERZEGOVINA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GEORGIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKHSTAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MONTENEGRO),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA),
				/*ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SERBIA), */
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TURKEY) };

		int localIndex = 0;

		for (localIndex = 0; localIndex < dvbTFullCountry.length; localIndex++) {
			if (argCountry.equalsIgnoreCase(dvbTFullCountry[localIndex])) {
				returnMacro = NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Full;
				break;
			}
		}

		if (returnMacro == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_NotSupported) {
			for (localIndex = 0; localIndex < dvbTLightCountry.length; localIndex++) {
				if (argCountry.equalsIgnoreCase(dvbTLightCountry[localIndex])) {
					returnMacro = NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light;
					break;
				}
			}
		}

		Log.d(TAG, "countrySupportsDVBTFullorLite returnMacro " + returnMacro);

		return returnMacro;
	}

	/**
	 * ifCountry supports DVBC-Full/Light
	 * 
	 * @param
	 * @return returns DVBC-Full or DVBC-Light
	 */
	public NativeAPIEnums.DVBTOrDVBCMacro countrySupportsDVBCFullorLite(
			String argCountry) {
		// if the country dosen't support DVBC
		NativeAPIEnums.DVBTOrDVBCMacro returnMacro = NativeAPIEnums.DVBTOrDVBCMacro.DVBC_NotSupported;

		String[] dvbCFullCountry = { ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA), /*New Implementation.Bulgaria moved to Full from Lite.CR number unknown. Rahul*/
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UKRAINE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA)
				};

		String[] dvbCLightCountry = { ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ALBANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ARMENIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AZERBAIJAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELARUS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOSNIA_HERZEGOVINA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CROATIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CZECH_REP),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ESTONIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GEORGIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GREECE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ISRAEL),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKHSTAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LATVIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LITHUANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LUXEMBOURG),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MACEDONIA_FYROM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MONTENEGRO),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SERBIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVAKIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TURKEY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UK),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TAIWAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UNITED_ARAB_EMIRATES),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM)};
		int localIndex = 0;

		for (localIndex = 0; localIndex < dvbCFullCountry.length; localIndex++) {
			if (argCountry.equalsIgnoreCase(dvbCFullCountry[localIndex])) {
				returnMacro = NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Full;
				break;
			}
		}

		if (returnMacro == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_NotSupported) {
			for (localIndex = 0; localIndex < dvbCLightCountry.length; localIndex++) {
				if (argCountry.equalsIgnoreCase(dvbCLightCountry[localIndex])) {
					returnMacro = NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light;
					break;
				}
			}
		}

		return returnMacro;
	}

	/**
	 * Gets id digital channels option is available from MW
	 * 
	 * @param
	 * @return if digital option available
	 */
	public Boolean ifAvailableDigitalChannels() {
		Boolean returnStatus = false;
		if (STUB_MODE) {
			returnStatus = true;
		} else {
			if (euInst.GetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDigitalOption) > 0) {
				returnStatus = true;
			} else {
				returnStatus = false;
			}
		}
		return returnStatus;
	}

	/**
	 * Gets the channel count from MW
	 * 
	 * @param
	 * @return channel count
	 */
	public int getNoOfInstalledChannels() {
		int presetCount = 0;
		if (STUB_MODE) {
			presetCount = 2;
		} else {

			try {
				String[] projection = new String[] { Channels._ID };
				String mselection = Channels.COLUMN_TYPE + "= ?" + " OR " + Channels.COLUMN_TYPE + "=?" + " OR " + Channels.COLUMN_TYPE + "=?" + " OR " + Channels.COLUMN_TYPE + "=?";
				String[] mselectionargs = new String[] { Channels.TYPE_DVB_T, Channels.TYPE_DVB_C, Channels.TYPE_DVB_T2, Channels.TYPE_PAL };

				Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

				if (cursor != null) {
					presetCount = cursor.getCount();
					cursor.close();
					cursor=null;
				} else {
					Log.d(TAG, "TCCursor NULL");
				}

			} catch (Exception e) {
				Log.e(TAG, "Error TVContentProvider  " + e);
			}
		}

		Log.d(TAG, "getNoOfInstalledChannels() " + presetCount);
		return presetCount;
	}

	/**
	 * Gets the selected country name from TV Settings
	 * 
	 * @param
	 * @return String country Name
	 */
	public String getCachedCountryName() {
		String retCountryName = null;

		String[] localCountryArray = getSortedCountyList();
		retCountryName = localCountryArray[getCachedCountryID()];

		//Log.d(TAG, "getCachedCountryName() " + retCountryName);
		// return the country ID
		return retCountryName;
	}

	/**
	 * Gets the selected country name from TV Settings
	 * 
	 * @param
	 * @return String country Name
	 */
	public String getCountryNameFromTVS() {
		String retCountryName = null;

		if (STUB_MODE) {
			retCountryName = ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY);
		} else {
			mTVSCselectedCountryID = mTvSettingsManager.getInt(
					TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
			Log.d(TAG,
					"getCountryNameFromTVS() from TVSettings mTVSCselectedCountryID "
							+ mTVSCselectedCountryID);
			String[] tvscCountryArray = getCountyListMappedToTVSettings();
			retCountryName = tvscCountryArray[mTVSCselectedCountryID];
		}

		Log.d(TAG, "getCountryNameFromTVS() " + retCountryName);
		// return the country Name
		// update local cached country

		return retCountryName;
	}

	/**
	 * Gets the selected cached country ID
	 * 
	 * @param
	 * @return int local country ID
	 */

	public int getCachedCountryID() {
		//Log.d(TAG, "getCachedCountryID() " + selectedCountryID);
		return selectedCountryID;
	}

	/**
	 * Set the selected cached country ID
	 * 
	 * @param int local country ID
	 */

	public void setCachedCountryID(int argCountryID) {
		selectedCountryID = argCountryID;
		Log.d(TAG, "setCachedCountryID() " + selectedCountryID);
				
		if (STUB_MODE) {

		} else {
			// update the countryID in MW
			int tvscCountryID = 0;
			String[] localCountryArray = getSortedCountyList();
			String[] tvscCountryArray = getCountyListMappedToTVSettings();
			String localCountry = localCountryArray[selectedCountryID];

            // update the country ID in MW
            for (tvscCountryID = 0; tvscCountryID < tvscCountryArray.length; tvscCountryID++) {
                if (localCountry.equalsIgnoreCase(tvscCountryArray[tvscCountryID])) {
                    // same country ID is mapped in MW
                    euInst.SetSystemCountry(tvscCountryID);
                    
                    // update user selected country ID in EuinstallerTC
                    euInst.updateUserSelectedCountry(tvscCountryID);
                    
                    Log.d(TAG, "setCachedCountryID() to MW " + tvscCountryID);
                    break;
                }
            }
			
			restoreScreenAttribBasedOnCounty();
		}
	}
	
	private void restoreScreenAttribBasedOnCounty(){
		// based on selected country 
		
		// timezone
		timeZoneIndex = getTimeZoneIndexFromTVS(getCachedCountryName());
		
		// antenna cable
		isDVBTorDVBC = getSelectedDVBTOrDVBCFromTVS();
				
		// analog digital
		analogOrDigital = getDigitalAnalogFromSharedPref();
		
		// operator
		operatorIndex = getOperatorIndexFromMW();
				
	}

	/**
	 * Gets the selected country from Global Settings & sets the selected
	 * country in MW
	 * 
	 * @param
	 * @return int country ID
	 */
	public int getSelectedCountyID() {
		if (STUB_MODE) {
			selectedCountryID = 27; // Russia
		} else {
			// get the country id from Global Settings
			/**
			 * Type Integer Austria=0; Belgium=1; Croatia=2; Czechrep=3;
			 * Denmark=4; Finland=5; France=6; Germany=7; Greece=8; Hungary=9;
			 * Ireland=10; Italy=11; Luxembourg=12; Netherlands=13; Norway=14;
			 * Poand=15; Portugal=16; Romania=17; Russia=18; Serbia=19;
			 * Slovakia=20; Slovenia=21; Spain=22; Sweden=23; Switzerland=24;
			 * Turkey=25; UK=26; Other=27; Australia=28; Estonia=29;
			 * Lithuania=30; Latvia=31; Kazakhstan=32; Bulgaria=33; China=34,
			 * Ukraine=35; Brazil=36, Arge,to,a=37, Albania=38, Armenia=39,
			 * Azerbaijan=40, Belarus=41, Bosnia and Herzegovina=42, Georgia=43,
			 * Montenegro=44, Israel=45, MacedoniaFyrom=46, Paraguay=47,
			 * Uruguay=48, Thai=49
			 */
			mTVSCselectedCountryID = mTvSettingsManager.getInt(
					TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
			Log.d(TAG,
					"getSelectedCountyID() from TVSettings mTVSCselectedCountryID "
							+ mTVSCselectedCountryID);
			// map the country id to local country list

			int localCountryID = 0;
			String[] localCountryArray = getSortedCountyList();
			String[] tvscCountryArray = getCountyListMappedToTVSettings();
			String tvscCountry = tvscCountryArray[mTVSCselectedCountryID];

			// reset selected CountryID to 0
			selectedCountryID = 0;

			for (localCountryID = 0; localCountryID < localCountryArray.length; localCountryID++) {
				if (tvscCountry == localCountryArray[localCountryID]) {
					// populate local country ID
					selectedCountryID = localCountryID;
					break;
				}
			}
		}

		Log.d(TAG, "getSelectedCountyID() " + selectedCountryID);
		// return the country ID
		return selectedCountryID;
	}

	/**
	 * Sets the selected country to TVS
	 * 
	 * @param int country ID is the local country ID from the sorted countrylist
	 */
	public void setSelectedCountyID(int countryID) {
		// store the country ID as class variable for later use
		selectedCountryID = countryID;
		if (STUB_MODE) {
			selectedCountryID = countryID;
		} else {
			int tvscCountryID = 0;
			String[] localCountryArray = getSortedCountyList();
			String[] tvscCountryArray = getCountyListMappedToTVSettings();
			String localCountry = localCountryArray[selectedCountryID];

            Log.d(TAG, "setSelectedCountyID() in selectedCountryID " + selectedCountryID + " localCountry: " + localCountry );

			// update the country ID in TVSettings
            for (tvscCountryID = 0; tvscCountryID < tvscCountryArray.length; tvscCountryID++) {
                if (localCountry.equalsIgnoreCase(tvscCountryArray[tvscCountryID])) {
                    mTVSCselectedCountryID = tvscCountryID;
                    mTvSettingsManager.putInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, mTVSCselectedCountryID);
					/*begin:min.jiang add 2015-08-27 */
					mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_TIME_ZONE_COUNTRY, 0, mTVSCselectedCountryID);	
		            mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_OFF_COUNTRY, 0, mTVSCselectedCountryID);	
					/*end:min.jiang add*/
                    euInst.SetInstallCountry(tvscCountryID);
                    Log.d(TAG, "setSelectedCountyID() in TVSettings " + mTVSCselectedCountryID);
                    break;
				}
			}
		}
	}

	/**
	 * Sets the RF Setting to TVS
	 * 
	 * @param int RF Setting is turn on/off DVBC/DVBT/Analog for auto scan
	 */
	public void setRfSetting(int value) {
		// store the country ID as class variable for later use
		selectedRfSetting = value;
		if (STUB_MODE) {
			selectedRfSetting = value;
		} else {
            Log.d(TAG, "setRfSetting() in selectedRfSetting " + selectedRfSetting );
            euInst.SetRfSetting(value);
		}
	}

	/**
	 * Sets the LCN Sorting Control to TVS
	 *
	 * @param int lcnMode is the LCN sorting control on/off from the user
	 */
	public void setLCNSortingControl(int mode) {
		Log.d(TAG, "setLCNSortingControl: mode " + mode);
		euInst.SetLCNSortingControl(mode);
	}

	/**
	 * Sets the PbsMode
	 * 
	 * @param int PbsMode
	 */
	public void setPbsMode(int value) {
		if (STUB_MODE) {
		} else {
            Log.d(TAG, "setPbsMode() : " + value );
            euInst.SetPbsMode(value);
		}
	}

	private String[] getCountyListMappedToTVSettings() {
		/**
		 * Type Integer Austria=0; Belgium=1; Croatia=2; Czechrep=3; Denmark=4;
		 * Finland=5; France=6; Germany=7; Greece=8; Hungary=9; Ireland=10;
		 * Italy=11; Luxembourg=12; Netherlands=13; Norway=14; Poand=15;
		 * Portugal=16; Romania=17; Russia=18; Serbia=19; Slovakia=20;
		 * Slovenia=21; Spain=22; Sweden=23; Switzerland=24; Turkey=25; UK=26;
		 * Other=27; Australia=28; Estonia=29; Lithuania=30; Latvia=31;
		 * Kazakhstan=32; Bulgaria=33; China=34, Ukraine=35; Brazil=36,
		 * Arge,to,a=37, Albania=38, Armenia=39, Azerbaijan=40, Belarus=41,
		 * Bosnia and Herzegovina=42, Georgia=43, Montenegro=44, Israel=45,
		 * MacedoniaFyrom=46, Paraguay=47, Uruguay=48, Thailand=49,NEWZEALAND = 50,
		 * SINGAPORE = 51,MALAYSIA = 52,TAIWAN = 53,INDONESIA = 54,NAMBIA = 55,
		 * PERU  = 56,SOUTHAFRICA= 57,UNITEDARABEMIRATES= 58,VIETNAM= 59,
		 * ANDORRA= 60,BOTSWANA= 61,FAROEISLANDS= 62,GHANA= 63,GREENLAND= 64,HOLLAND= 65,
		 * ICELAND= 66,LIECHTENSTEIN= 68,MONACO= 69,OMAN= 70,SAUDIARABIA= 71,BHARAIN= 72,CHILE= 73,
		 * EGYPT= 74,INDIA= 75,KUWAIT= 76,MOROCCO= 77,UZBEKISTAN= 78,CANADA= 79,DOMAINREPUBLIC= 80,
		 * MEXICO= 81,PHILIPPINES= 82,USA= 83,VIRGINISLANDS= 84,JAPAN= 85,KOREA= 86,HONGKONG= 87,
		 */
		String countriesList[] = { ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CROATIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CZECH_REP),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GREECE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LUXEMBOURG),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SERBIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVAKIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TURKEY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UK),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER), 
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA), 
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ESTONIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LITHUANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LATVIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKHSTAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CHINA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UKRAINE), 
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BRAZIL), 
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ARGENTINA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ALBANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ARMENIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AZERBAIJAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELARUS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOSNIA_HERZEGOVINA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GEORGIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MONTENEGRO),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ISRAEL),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MACEDONIA_FYROM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PARAGUAY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_URUGUAY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TAIWAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NAMIBIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PERU),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SOUTH_AFRICA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UNITED_ARAB_EMIRATES),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ANDORRA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOTSWANA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FAROE_ISLANDS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GHANA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GREENLAND),
				"Holland",
				"Iceland",
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LEBANON),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LIECHTENSTEIN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MONACO),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OMAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SAUDI_ARABIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BAHRAIN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CHILE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_EGYPT),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KUWAIT),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MOROCCO),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UZBEKISTAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CANADA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DOMINICAN_REPUBLIC),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MEXICO),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PHILIPPINES),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_USA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIRGIN_ISLANDS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_JAPAN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KOREA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HONG_KONG)
				

				 };

		return countriesList;
	}

	/**
	 * Predefined country list with the supported languages. This list shall be
	 * alphabetically ordered, according the selected menu language.
	 * 
	 * @return array country list
	 */
	public String[] getSortedCountyList() {
		/* List of country's specified in requirement for EU*/
		int regionBit = 0;
		ArrayList<String> countriesList = new ArrayList<String>();
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ALBANIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ARMENIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AZERBAIJAN));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELARUS));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOSNIA_HERZEGOVINA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CROATIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CZECH_REP));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ESTONIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GEORGIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GREECE));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND)); 
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ISRAEL));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKHSTAN));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LATVIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LITHUANIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LUXEMBOURG));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MACEDONIA_FYROM));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MONTENEGRO));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SERBIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVAKIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TURKEY));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UK));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UKRAINE));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UNITED_ARAB_EMIRATES));
		
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA));
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND));

		/*APMEA and EU List */		
		regionBit = mTvSettingsManager.getInt(TvSettingsConstants.OPREGION, 0,0);
		//Log.d(TAG,"regionBit="+regionBit);
		
		/* isBnoProduct check is added inaccordance with PR: LF6015PHIEUAPMTK01-403 */
		if((regionBit==1) || (isBnoProduct()))
		{
			/*TvSettingsDefinitions.OpRegionDisplayConstants.APMEA*/
			//countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA)); 
			//countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA));
			//countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND));
			//countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE));
			countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TAIWAN));

			/* These countries are not added because they are not in the BNO country List :  LF6015PHIEUAPMTK01-403 */
			if(isBnoProduct()== false)
			{
				//countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA));
				//countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND));
				countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM));
			}	
		}
		
		//sort country list list
		Collections.sort(countriesList);
		
		// append other at end
		countriesList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER));
		
		// convert arraylist to string list and return
		String[] countryArray = new String[countriesList.size()];
		countryArray = countriesList.toArray(countryArray);
		
		return countryArray;
	}

	/**
	 * Returns if the passed country supports timezone
	 * 
	 * @param int country ID
	 * @return boolean true is the country supports timezone
	 */
	public boolean ifTimezoneCountry(String argCountryName) {
		Boolean returnValue = false;
			
		if(argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN)) ||
		        argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL)) ||
		        argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKHSTAN)) || 
		        argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA)) ||
		        argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND)) ||
		        argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA))){
		    returnValue = true;
        } else {
            returnValue = false;
        }

		Log.d(TAG, "getCachedCountryName() ifTimezoneCountry() "
				+ getCachedCountryName() + " "+ returnValue);
		return returnValue;
	}

	/**
	 * Returns true if the passed country is among analog switched off countries
	 * 
	 * @param int country ID
	 * @return boolean true is the country is ASO country
	 */
	public boolean ifASOCountry(String argCountry,
			NativeAPIEnums.DVBTOrDVBC selectedMedium) {
		boolean returnStatus = false;

		String[] asoCountryListDVBT = { ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CZECH_REP),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ESTONIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LUXEMBOURG),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UK),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MACEDONIA_FYROM),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CROATIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LATVIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LITHUANIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVAKIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UNITED_ARAB_EMIRATES)
				};
		
		/* New ASO countries added AN-16981 & AN-16988 */

		String[] asoCountryListDVBC = { ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND),
										ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK)};

		int localIndex = 0;

		if (selectedMedium == NativeAPIEnums.DVBTOrDVBC.DVBC) {
			for (localIndex = 0; localIndex < asoCountryListDVBC.length; localIndex++) {
				if (argCountry.equalsIgnoreCase(asoCountryListDVBC[localIndex])) {
					returnStatus = true;
					break;
				}
			}
		} else if (selectedMedium == NativeAPIEnums.DVBTOrDVBC.DVBT) {
			for (localIndex = 0; localIndex < asoCountryListDVBT.length; localIndex++) {
				if (argCountry.equalsIgnoreCase(asoCountryListDVBT[localIndex])) {
					returnStatus = true;
					break;
				}
			}
		}

		Log.d(TAG, "ifASOCountry() " + argCountry + ": " + selectedMedium
				+ ": " + returnStatus);
		return returnStatus;
	}

	/**
	 * Returns current installation mode
	 * 
	 * @return NativeAPIEnums.InstallationMode current installation mode enum
	 */
	public NativeAPIEnums.InstallationMode getCurrentInstalltionMode() {
		NativeAPIEnums.InstallationMode instMode = NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION;
		if (STUB_MODE) {
			instMode = NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION;
		} else {
			// instMode

		}
		return instMode;
	}

	/**
	 * Returns if the current mode is VirginInstallation from MW or Global
	 * Settings
	 * 
	 * @return boolean
	 */
	public Boolean ifVirginInstallation() {
		Boolean virginStatus = false;
		if (STUB_MODE) {
			virginStatus = false;
		} else {
			int virginBit = mTvSettingsManager.getInt(TvSettingsConstants.VIRGINBIT, 0,
					0);
			if (virginBit == 0) {
				virginStatus = false;
			} else {
				virginStatus = true;
			}
		}

		Log.d(TAG, "ifVirginInstallation() " + virginStatus);
		return virginStatus;
	}

	/**
	 * Returns current country timezone list
	 * 
	 * @return array country list
	 */
	@SuppressLint("NewApi")
	public String[] getCurrentTimeZoneList() {
		String selectedCountryName = getCachedCountryName();
		ArrayList<String> timeZoneList = new ArrayList<String>();

		if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN))) {
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN_BALEARES));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CANARY_ISLANDS));
		} else if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL))) {
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL_MADEIRA));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AZORES));
		} else if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKHSTAN))) {
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKH_WESTERN));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKH_EASTERN));
		} else if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA))) {
			// 0=Kalingrad, 1=Moscow,2=Samara, 3=Yekaterinburg, 4=Omsk, 5=Krasnoyarsk, 6=Irkutsk, 7Yakutsk, 8==Vladivostok, 9=Srednekolymsk, 10=Kamchatka
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KALINGRAD));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MOSCOW));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SAMARA));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YEKATERINBURG));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OMSK));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KRASNOYARSK));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRKUTSK));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YAKUTSK));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VLADIVOSTOK));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SREDNEKOLYMSK));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAMCHATKA));
		}
		else if(selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND))) 
		{
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND));
			//build error timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CHATHAM_ISLANDS));
		}
		else if(selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA))) 
		{    /* build error
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA_WESTERN_TIME_ZONE));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA_CENTRAL_TIME_ZONE));
			timeZoneList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA_EASTERN_TIME_ZONE));*/
		}

		Object[] ObjectList = timeZoneList.toArray();
		String[] timeZoneArray = Arrays.copyOf(ObjectList, ObjectList.length,
				String[].class);

		return timeZoneArray;
	}

	public void setCachedTimeZoneIndex(int argTimeZoneID) {
		timeZoneIndex = argTimeZoneID;
		
		// update cached timezone name
		String[] timeZoneList = getCurrentTimeZoneList();
		timeZoneName = timeZoneList[argTimeZoneID];
		Log.d(TAG, "setCachedTimeZoneIndex " + argTimeZoneID + ", " + timeZoneName);
	}
	
	public String getCachedTimeZoneName(){
	    Log.d(TAG, "getCachedTimeZoneName " + timeZoneName);
	    return timeZoneName;
	}
	
	public int getCachedTimeZoneIndex() {
		Log.d(TAG, "getCachedTimeZoneIndex " + timeZoneIndex);
		if(timeZoneIndex >= getCurrentTimeZoneList().length){
		    // reset timezone index to void array out of bound error
		    timeZoneIndex = 0;
		}
		return timeZoneIndex;
	}
	
	/**
	 * Sets the current timezone param sets the current timezone in TVSettings
	 * and MW
	 */
	private void setCurrentTimeZoneToTVS(String argTimeZoneName) {
		Log.d(TAG,"setCurrentTimeZoneToTVS argTimeZoneName " + argTimeZoneName);
		if (STUB_MODE) {

		} else {
			String selectedCountryName = getCachedCountryName();
			
			String[] timeZoneArray = getCurrentTimeZoneList();
			Log.d(TAG,"length of timeZoneArray = " + String.valueOf(timeZoneArray.length));
			
			String selectedTimeZone = timeZoneName;
			AlarmManager alarmMangInst = (AlarmManager) (ctx).getSystemService(Context.ALARM_SERVICE);

			Log.d(TAG,"selectedTimeZone " + selectedTimeZone);
			// reset all the other timezones
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONESPAIN,0, 0);
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEPORTUGAL,0, 0);
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEKAZAKHSTAN,0, 0);
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, 0);
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONENEWZEALAND,0, 0);
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEINDONESIA,0, 0);
			
			if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN))) {
				// 0: spain_baleares, 1: canary_islands
				if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN_BALEARES))) {
					alarmMangInst.setTimeZone("Europe/Madrid");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONESPAIN,0, TvSettingsDefinitions.InstSettingsTimeZoneSpainConstants.CONTINENTALSPAINANDBALEARES);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CANARY_ISLANDS))) {
					alarmMangInst.setTimeZone("Atlantic/Canary");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONESPAIN,0, TvSettingsDefinitions.InstSettingsTimeZoneSpainConstants.CANARYISLANDS);
				}				
			} else if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL))) {
				//  0: portugal_madeira, 1: azores
				if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL_MADEIRA))) {
					alarmMangInst.setTimeZone("Atlantic/Madeira");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEPORTUGAL,0, TvSettingsDefinitions.InstSettingsTimeZonePortugalConstants.CONTINENTALPORTUGALANDMADEIRA);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AZORES))) {
					alarmMangInst.setTimeZone("Atlantic/Azores");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEPORTUGAL,0, TvSettingsDefinitions.InstSettingsTimeZonePortugalConstants.AZORES);
				}
			} else if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKHSTAN))) {
				// 0: kazakh_western, 1: kazakh_eastern
				if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKH_WESTERN))) {
					alarmMangInst.setTimeZone("Asia/Oral");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEKAZAKHSTAN,0, TvSettingsDefinitions.InstSettingsTimeZoneKazakhstanConstants.KAZAKH_WESTERN);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKH_EASTERN))) {
					alarmMangInst.setTimeZone("Asia/Almaty");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEKAZAKHSTAN,0, TvSettingsDefinitions.InstSettingsTimeZoneKazakhstanConstants.KAZAKH_EASTERN);
				}
			} else if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA))) {
				// 0=Kalingrad, 1=Moscow,2=Samara, 3=Yekaterinburg, 4=Omsk, 5=Krasnoyarsk, 6=Irkutsk, 7Yakutsk, 8==Vladivostok, 9=Srednekolymsk, 10=Kamchatka
				if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KALINGRAD))) {
					alarmMangInst.setTimeZone("Europe/Kaliningrad");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.KALINGRAD);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MOSCOW))) {
					alarmMangInst.setTimeZone("Europe/Moscow");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.MOSCOW);
				}  else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SAMARA))) {
					alarmMangInst.setTimeZone("Europe/Samara");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.SAMARA);
				}else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YEKATERINBURG))) {
					alarmMangInst.setTimeZone("Asia/Yekaterinburg");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.YEKATERINBURG);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OMSK))) {
					alarmMangInst.setTimeZone("Asia/Omsk");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.OMSK);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KRASNOYARSK))) {
					alarmMangInst.setTimeZone("Asia/Krasnoyarsk");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.KRASNOYARSK);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRKUTSK))) {
					alarmMangInst.setTimeZone("Asia/Irkutsk");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.IRKUTSK);
				}else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YAKUTSK))) {
					alarmMangInst.setTimeZone("Asia/Yakutsk");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.YAKUTSK);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VLADIVOSTOK))) {
					alarmMangInst.setTimeZone("Asia/Vladivostok");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.VLADIVOSTOK);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SREDNEKOLYMSK))) {
					alarmMangInst.setTimeZone("Asia/Srednekolymsk");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.SREDNEKOLYMSK);
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAMCHATKA))) {
					alarmMangInst.setTimeZone("Asia/Kamchatka");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA,0, TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.KAMCHATKA);
				}
			}
			else if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND))) 
			{
				// 0: CHATHAMISLANDS, 1: OTHERISLANDS
				if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND))) 
				{
					alarmMangInst.setTimeZone("Pacific/Auckland");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONENEWZEALAND,0, TvSettingsDefinitions.InstSettingsTimeZoneNewZealandConstants.OTHERISLANDS);
					
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CHATHAM_ISLANDS))) 
				{
					alarmMangInst.setTimeZone("Pacific/Chatham");
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONENEWZEALAND,0, TvSettingsDefinitions.InstSettingsTimeZoneNewZealandConstants.CHATHAMISLANDS);
				}
				
			} else if (selectedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA))) 
			{
				//  0: WESTERNZONE, 1: CENTRALZONE, 2:EASTERNZONE
				if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA_WESTERN_TIME_ZONE))) 
				{					
					alarmMangInst.setTimeZone("Asia/Jakarta");//+7Hrs
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEINDONESIA,0, TvSettingsDefinitions.InstSettingsTimeZoneIndonesiaConstants.WESTERNZONE);
					
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA_CENTRAL_TIME_ZONE))) 
				{
					alarmMangInst.setTimeZone("Asia/Makassar");//+8Hrs
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEINDONESIA,0, TvSettingsDefinitions.InstSettingsTimeZoneIndonesiaConstants.CENTRALZONE);
					
				} else if (selectedTimeZone.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA_EASTERN_TIME_ZONE))) 
				{
					alarmMangInst.setTimeZone("Asia/Jayapura");//+9Hrs
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTIMEZONEINDONESIA,0, TvSettingsDefinitions.InstSettingsTimeZoneIndonesiaConstants.EASTERNZONE);
				}
			}
		}
		Log.d(TAG,"setCurrentTimeZoneToTVS exit ");
	}
	
	private int getTimeZoneIndexFromTVS(String argCountryName){
	    int returnIndex = 0;
	    int timeZoneval = 0;
	    
	    if (argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN))) {
	        timeZoneval = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTIMEZONESPAIN, 0, 0);
            // 0: spain_baleares, 1: canary_islands
	        if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneSpainConstants.CONTINENTALSPAINANDBALEARES) {
                returnIndex = 0;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneSpainConstants.CANARYISLANDS) {
                returnIndex = 1;
            }               
        } else if (argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL))) {
            timeZoneval = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTIMEZONEPORTUGAL, 0, 0);
            //  0: portugal_madeira, 1: azores
            if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZonePortugalConstants.CONTINENTALPORTUGALANDMADEIRA) {
                returnIndex = 0;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZonePortugalConstants.AZORES) {
                returnIndex = 1;
            }        
        } else if (argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_KAZAKHSTAN))) {
            timeZoneval = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTIMEZONEKAZAKHSTAN, 0, 0);
            // 0: kazakh_western, 1: kazakh_eastern
            if (timeZoneval ==  TvSettingsDefinitions.InstSettingsTimeZoneKazakhstanConstants.KAZAKH_WESTERN) {
                returnIndex = 0;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneKazakhstanConstants.KAZAKH_EASTERN) {
                returnIndex = 1;
            }      
        } else if (argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA))) {
            timeZoneval = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTIMEZONERUSSIA, 0, 0);
            // 0=Kalingrad, 1=Moscow,2=Samara, 3=Yekaterinburg, 4=Omsk, 5=Krasnoyarsk, 6=Irkutsk, 7Yakutsk, 8==Vladivostok, 9=Srednekolymsk, 10=Kamchatka
            if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.KALINGRAD) {
                returnIndex = 0;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.MOSCOW) {
                returnIndex = 1;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.SAMARA) {
            	returnIndex = 2;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.YEKATERINBURG) {
                returnIndex = 3;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.OMSK) {
                returnIndex = 4;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.KRASNOYARSK) {
                returnIndex = 5;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.IRKUTSK) {
                returnIndex = 6;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.YAKUTSK) {
                returnIndex = 7;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.VLADIVOSTOK) {
                returnIndex = 8;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.SREDNEKOLYMSK) {
                returnIndex = 9;
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneRussiaConstants.KAMCHATKA) {
                returnIndex = 10;
            }
        }
		else if(argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND)))
		{
				timeZoneval = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTIMEZONENEWZEALAND, 0, 0);
				
				if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneNewZealandConstants.OTHERISLANDS) 
				{
                	returnIndex = 0;
				}
				else if(timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneNewZealandConstants.CHATHAMISLANDS) 
            	{
                	returnIndex = 1;
				}
		}
		else if(argCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA)))
		{
			timeZoneval = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTIMEZONEINDONESIA, 0, 0);
			
			if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneIndonesiaConstants.WESTERNZONE) 	
			{
                returnIndex = 0;
				
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneIndonesiaConstants.CENTRALZONE) 
           	{
                returnIndex = 1;
				
            } else if (timeZoneval == TvSettingsDefinitions.InstSettingsTimeZoneIndonesiaConstants.EASTERNZONE) 
            {
            	returnIndex = 2;
            }
		}
		
	    Log.d(TAG,"getTimeZoneIndexFromTVS argCountryName:" + argCountryName + 
	    		" timeZoneval:" +  timeZoneval + 
	    		" returnIndex:" + returnIndex );
	    return returnIndex;
	}

	/*
	 * Gets the antenna/cable list
	 * 
	 * @return array antenna/cable list
	 */
	public String[] getDVBTOrDVBCList() {
		String[] antennaList = { ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ANTENNA_DVBT),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CABLE_DVBC) };
		return antennaList;
	}

	/**
	 * Gets the cached DVBT OR DVBC value
	 * 
	 * @param
	 * @return enum DVBTOrDVBC Id
	 */
	public NativeAPIEnums.DVBTOrDVBC getCachedDVBTOrDVBC() {
		Log.d(TAG, "getCachedDVBTOrDVBC() " + isDVBTorDVBC);
		return isDVBTorDVBC;
	}

	/**
	 * Gets the selected DVBT OR DVBC from TVSettings
	 * 
	 * @param
	 * @return enum DVBTOrDVBC Id
	 */
	public NativeAPIEnums.DVBTOrDVBC getSelectedDVBTOrDVBCFromTVS() {
		NativeAPIEnums.DVBTOrDVBC returnStatus = NativeAPIEnums.DVBTOrDVBC.DVBC;
		if (STUB_MODE) {
			returnStatus = NativeAPIEnums.DVBTOrDVBC.DVBC;
		} else {
			
			// Initially MW will not be aware of TVSettings so we have to query
			// from TVSettings
			/* 0 = antenna,1=cable */
			int dvbMediumID = mTvSettingsManager.getInt(
					TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);

			if (dvbMediumID == TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA) {
				returnStatus = NativeAPIEnums.DVBTOrDVBC.DVBT;
			} else {
				returnStatus = NativeAPIEnums.DVBTOrDVBC.DVBC;
			}
		}
		
		Log.d(TAG, "getSelectedDVBTOrDVBCFromTVS() " + returnStatus);
		return returnStatus;
	}

	/**
	 * Sets the antenna/cable param sets the antenna or cable in TVSettings and
	 * MW
	 */
	public void setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC dvbtc) {
		Log.d(TAG, "setDVBTOrDVBC " + dvbtc);
		isDVBTorDVBC = dvbtc; // cache value for later use
		if (STUB_MODE) {

		} else {
			/* 0 = antenna,1=cable */
			if (dvbtc == NativeAPIEnums.DVBTOrDVBC.DVBC) {
				// set in MW
				// euInst.SetMedium(euInstConst.IHsvInstallation2_Cable); //
				// donot call directly as media player init has to be done
				euInst.setSessionTuneWithMedium(SESSION_MEDIUM.CABLE);
			} else if (dvbtc == NativeAPIEnums.DVBTOrDVBC.DVBT) {
				// set in MW
				// euInst.SetMedium(euInstConst.IHsvInstallation2_Terrestrial);
				// // donot call directly as media player init has to be done
				euInst.setSessionTuneWithMedium(SESSION_MEDIUM.ANTENNA);
			}
			/*
			if(ifVirginInstallation()){
			    // in virgin mode commit the medium to TVSettings
			    // set Antenna/Cable
		        if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
		            mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 1);
					// medium is set in the MW. 
					// Reason: medium was set after onprepare async callback to mw, before that operator screen was requesting operator on a antenna medium
					// TF515PHIALLMTK01-13476
					//euInst.SetMedium(euInstConst.IHsvInstallation2_Cable);
		        } else if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBT) {
		            mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
					// euInst.SetMedium(euInstConst.IHsvInstallation2_Terrestrial);
		        } 
			}*/
		}
	}

	/*
	 * Gets the Digital/Analog list
	 * 
	 * @return array digital/analog list
	 */
	public String[] getAnalogueDigitalList() {
		
		String[] analogueList; 
		
		if((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC)&&(DVBTOrDVBCMacro.DVBC_Light ==  countrySupportsDVBCFullorLite(getCachedCountryName())))
		{
				
				analogueList = new String[]{ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DIGITAL_PLUS_ANALOGUE),
										ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DIGITAL_ONLY),
										ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ANALOGUE_ONLY)} ;
		}
		else
		{
				analogueList = new String[]{ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DIGITAL_PLUS_ANALOGUE),
				ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DIGITAL_ONLY)};
		}
		return analogueList;
	}
	
	/**
	 * Gets the selected Digital,Analogue
	 * 
	 * @param
	 * @return int digital/analogue id
	 */
	public NativeAPIEnums.AnalogueOrDigital getDigitalAnalogFromSharedPref() {
		NativeAPIEnums.AnalogueOrDigital returnVal = NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE;
		
		// current cached country is same as stored country restore previous selected option
		// else new country point to 0th location
		
		String storedCountryName = getCountryNameFromTVS();		
		if(storedCountryName.equalsIgnoreCase(getCachedCountryName())){
			// restore the store operator index
		    String readString = NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE.toString();
			
            readString = mStoredSharedPreferences.getString("analog_digital", "");
			
			if(readString.equalsIgnoreCase(NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE.toString())){
			    // Digital + Analogue
                returnVal = NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE;
			}else if(readString.equalsIgnoreCase(NativeAPIEnums.AnalogueOrDigital.DIGITAL.toString())){
				// Digital Only
				returnVal = NativeAPIEnums.AnalogueOrDigital.DIGITAL;
			}else if(readString.equalsIgnoreCase(NativeAPIEnums.AnalogueOrDigital.ANALOGUE.toString())){
				// Analogue only
				returnVal = NativeAPIEnums.AnalogueOrDigital.ANALOGUE;
			}
		}
		
		Log.d(TAG, "getDigitalAnalogFromSharedPref " + analogOrDigital);
		return returnVal;
		
	}
	
	public void setAnalogSystemFromSharedPref(AnalogSystemCountry argSystemCountry){
		Log.d(TAG, "setAnalogSystemFromSharedPref " + argSystemCountry);
		edit.putString("analog_system", argSystemCountry.toString());
		edit.commit();
	}
	
	public AnalogSystemCountry getAnalogSystemFromSharedPref(){

		AnalogSystemCountry returnVal = AnalogSystemCountry.EAST_EUROPE;
		
		String readString = mStoredSharedPreferences.getString("analog_system", "");
		Log.d(TAG, "getAnalogSystemFromSharedPref " + readString);
		
		if(readString.equalsIgnoreCase(AnalogSystemCountry.WEST_EUROPE.toString())){
			returnVal = AnalogSystemCountry.WEST_EUROPE;
		}else if(readString.equalsIgnoreCase(AnalogSystemCountry.EAST_EUROPE.toString())){
			returnVal = AnalogSystemCountry.EAST_EUROPE;
		}else if(readString.equalsIgnoreCase(AnalogSystemCountry.UK.toString())){
			returnVal = AnalogSystemCountry.UK;
		}else if(readString.equalsIgnoreCase(AnalogSystemCountry.FRANCE.toString())){
			returnVal = AnalogSystemCountry.FRANCE;
		}else{
			// default case 
			returnVal = AnalogSystemCountry.EAST_EUROPE;
		}
		
		Log.d(TAG, "getAnalogSystemFromSharedPref " + returnVal);
		return returnVal;
	}

	public boolean getBGInstallFromSharedPref(){
		boolean status = true;
		if (mStoredSharedPreferences != null) {
			status = mStoredSharedPreferences.getBoolean("bg_install", status);
			Log.d(TAG, "bg_install in Shared Pref  " + status);
		} else {
			Log.d(TAG, "getBGInstallFromSharedPref: mStoredSharedPreferences is NULL !!!");
		}
		return status;
	}

	public void setBGInstalltoSharedPref(boolean bgInstallEnabled){
		if (edit != null) {
	 		edit.putBoolean("bg_install", bgInstallEnabled);
	 		edit.commit();
			Log.d(TAG, "set bg_install in Shared Pref to " + bgInstallEnabled);
		}
		else{
			Log.d(TAG, "setBGInstalltoSharedPref: edit is NULL !!!");
		}
	}
	
	/**
	 * Sets the Digital/Analog param sets the Digital or Analog or Digital in
	 * TVSettings and MW plus Analog
	 */
	public void setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital ad) {
		analogOrDigital = ad;
		if (STUB_MODE) {

		} else {
			// Set in TVSettings
			// set in MW
			/* 0 Digital 1 Analogue 2 Digital + Analog */
			if (ad == NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE) {
			    setDigitalOption(true);
				euInst.setDigitalOrAnalaog(2);
			} else if (ad == NativeAPIEnums.AnalogueOrDigital.ANALOGUE) {
			    setDigitalOption(false);
				euInst.setDigitalOrAnalaog(1);
			} else {
			    setDigitalOption(true);
				euInst.setDigitalOrAnalaog(0);
			}
		}
	}

	public NativeAPIEnums.AnalogueOrDigital getCachedAnalogueDigital() {
		Log.d(TAG, "getCachedAnalogueDigital() " + analogOrDigital);
		return analogOrDigital;
	}

	private void setAnalogueDigitalToSharedPref(NativeAPIEnums.AnalogueOrDigital argAnalogOrDigital) {
	    Log.d(TAG, "setAnalogueDigitalToSharedPref() " + analogOrDigital);
		edit.putString("analog_digital", argAnalogOrDigital.toString());
		edit.commit();
	}
	
	public Boolean ifCountrySupportsOperator(int argCountryID) {
		Boolean returnStatus = false;
		if (argCountryID == TvSettingsDefinitions.InstallationCountryConstants.NETHERLANDS ||
				argCountryID == TvSettingsDefinitions.InstallationCountryConstants.GERMANY ||
				argCountryID == TvSettingsDefinitions.InstallationCountryConstants.BELGIUM ||
				argCountryID == TvSettingsDefinitions.InstallationCountryConstants.AUSTRIA ||
				argCountryID == TvSettingsDefinitions.InstallationCountryConstants.SWITZERLAND||
				argCountryID == TvSettingsDefinitions.InstallationCountryConstants.HUNGARY ||
				argCountryID == TvSettingsDefinitions.InstallationCountryConstants.POLAND ||
				argCountryID == TvSettingsDefinitions.InstallationCountryConstants.ROMANIA ||
				argCountryID == TvSettingsDefinitions.InstallationCountryConstants.IRELAND) {
			returnStatus = true;
		}
		Log.d(TAG, "ifCountrySupportsOperator() Country: " + getCachedCountryName() + " returnStatus " + returnStatus);
		return returnStatus;
	}
	/*
	 * Function returns tru of the country has operator
	 * 
	 * @Return true is the county supports operator
	 */

	public Boolean ifCountryHasOperator(int argCountryID) {
		/*
		 * check if the Country is one among Netherlands, Germany,
		 * Belgium,Austria, Switzerland, Hungary,Poland, Romania or Ireland.
		 * (i.e. Operators UPC/Ziggo/Telenet)
		 */
		Boolean returnStatus = false;

		String[] countryList = getSortedCountyList();

		if (countryList[getCachedCountryID()].equalsIgnoreCase(ctx
				.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA))	
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN))
				|| countryList[getCachedCountryID()].equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA))
		){

			returnStatus = true;
			Log.d(TAG, "ifCountryHasOperator() Country: " + getCachedCountryName() + " returnStatus " + returnStatus);
		} else {
			Log.d(TAG, "ifCountryHasOperator() Country: " + getCachedCountryName() + " returnStatus " + returnStatus);
		}

		Log.d(TAG, "ifCountryHasOperator() Country: " + getCachedCountryName() + " returnStatus " + returnStatus);
		return returnStatus;
	}
	
	private int stringIndexInStrArray(String[] strArray, String matchString){
	    int returnIndex = 0;
	    int loopIndex = 0;
	    
	    for (loopIndex = 0; loopIndex < strArray.length; loopIndex++) {
            if (strArray[loopIndex].equalsIgnoreCase(matchString)){
                // set to index & break
                returnIndex = loopIndex;
                break;
            }
        }
	    return returnIndex;
	}
	
	public NativeAPIEnums.Operators getOperatorFromMW() {
		NativeAPIEnums.Operators returnOp = NativeAPIEnums.Operators.Other;

		if (STUB_MODE) {

		} else {
			int operatorID = euInst.GetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkOperator);
			Log.d(TAG, "getOperatorFromMW operatorID " + operatorID);

			switch (operatorID) {
			case 0:
				// other
				returnOp = NativeAPIEnums.Operators.Other;
				break;
			case 1:
				// Ziggo
				returnOp = NativeAPIEnums.Operators.Ziggo;
				break;
			case 2:
				// UPC
				returnOp = NativeAPIEnums.Operators.UPC;
				break;
			case 3:
				// UNITYMEDIA
				returnOp = NativeAPIEnums.Operators.Unitymedia;
				break;
			case 4:
				// KDG_SD
				returnOp = NativeAPIEnums.Operators.KDG_SD;
				break;
			case 5:
				// TELENET
				returnOp = NativeAPIEnums.Operators.Telenet;
				break;
			case 6:
				returnOp = NativeAPIEnums.Operators.CamOperator;
				break;
			case 7:
				// RCSRDS
				returnOp = NativeAPIEnums.Operators.RCSRDS;
				break;
			case 8:
				// Blizoo
				returnOp = NativeAPIEnums.Operators.Blizoo;
				break;	
			case 9:
				// Canal Digital
				returnOp = NativeAPIEnums.Operators.CanalDigital;	
				break;
			case 10:
				// Yousee
				returnOp = NativeAPIEnums.Operators.YouSee;
				break;	
			case 11:
				// Telemach
				returnOp = NativeAPIEnums.Operators.Telemach;
				break;	
			case 12:
				// ComHem
				returnOp = NativeAPIEnums.Operators.ComHem;
				break;	
				
              case 13:
					// KDG_HD
					returnOp = NativeAPIEnums.Operators.KDG_HD;
					break;
			}
		}
		Log.d(TAG, "getOperatorFromMW returnOp " + returnOp);
		return returnOp;
	}

    public int getOperatorIndexFromMW() {
        int returnIndex = 0;
		String countryName = getCachedCountryName();
        if(STUB_MODE){
        	
        }else{
	        String[] operatorList = getOperatorList();
	
	        // restore the store operator index
	        int operatorID = euInst.GetAttribute( euInstConst.IHsvInstallation2_InstallationModeAutomatic,
	                euInstConst.IHsvInstallation2_AttributeNetworkOperator);
			operatorID = getHTVOperatorToMW(operatorID);/*161031GaryYe cable operator[TF415PHIEUMTK01-184] Ensure all the Wizards settings are cloned*/
	        Log.d(TAG, "getOperatorIndexFromMW operatorID.. " + operatorID);
	        
	        switch (operatorID) {
	            case 0:
	                // other
	                returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER));
	                break;
	            case 1:
	                // Ziggo
	                returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ZIGGO));
	                break;
	            case 2:
	                // UPC
	                if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS)))
	                {
	                	returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UPC));
	                }
					else
					{
						returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC));
					}
	                break;
	            case 3:
	            	// UNITYMEDIA
	                returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MISC_UNITYMEDIA));
	                break;
	            case 4:
	            	// KDG_SD
	                returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VF_STANDARD_SORTING));
	                break;
	            case 5:
	                // TELENET
	                returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET));
	                break;
	            case 6:
	            	if(euInst.isOperatorProfileSupported())
	            	{
	            		returnIndex = stringIndexInStrArray(operatorList, euInst.getOperatorName());
	            	}
					break;
				case 7:
					// RCSRDS
					returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MISC_RCS_RDS));
					break;
				case 8:
				   //Blizoo
				   	returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BLIZOO));
					break;
				case 9:
				   //Canal Digital
				   returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.tunerservice.R.string.MAIN_CANALDIGITAL));   
				   break;   
				case 10:
				   //YouSee
				   returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YOUSEE));   
				   break;
				case 11:
				   //Telemach
				   returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.tunerservice.R.string.MAIN_TELEMACH));   
				   break; 
				case 12:
				   //ComHem
				   returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.tunerservice.R.string.MAIN_COMHEM));   
				   break; 		   
				case 13:
					// KDG_HD
					returnIndex = stringIndexInStrArray(operatorList, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VF_HD_SORTING));
					break;
					
			}
        }
        Log.d(TAG, "getOperatorIndexFromMW " + returnIndex);
        return returnIndex;
    }
    
    public String getCamBasedOpName()
    {
    	return euInst.getOperatorName();
    }
    
	public boolean isOperatorProfileSupported() {
		Boolean l_ret = euInst.isOperatorProfileSupported();
		Log.d(TAG, "isOperatorProfileSupported l_ret = " + l_ret);
		return l_ret;
	}
	
	/*
	 * Gets the list of operators
	 * 
	 * @Return array operator list
	 */
	@SuppressLint("NewApi")
	public String[] getOperatorList() {
		ArrayList<String> operatorList = new ArrayList<String>();

		String countryName = getCachedCountryName();

		if (countryName.equalsIgnoreCase(ctx
				.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))) {
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ZIGGO));
		}

		if (countryName.equalsIgnoreCase(ctx
				.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))) {
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UPC));
		}

		if (countryName.equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND))
				|| countryName.equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA))
				|| countryName.equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))
				|| countryName.equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND))
				|| countryName.equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA))
				|| countryName.equalsIgnoreCase(ctx
						.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND))) {
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC));
		}

		if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY)))
		{
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VF_STANDARD_SORTING));
		    operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VF_HD_SORTING));
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MISC_UNITYMEDIA));
		}

		if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))) {
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET));
		}

		if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA))) {
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MISC_RCS_RDS));
		}
		if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA))) {
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BLIZOO));
		}
		if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))) {
			operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YOUSEE));
		}
		if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) {
			operatorList.add(ctx.getString(org.droidtv.tunerservice.R.string.MAIN_CANALDIGITAL));
		}
		if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN))) {
			operatorList.add(ctx.getString(org.droidtv.tunerservice.R.string.MAIN_CANALDIGITAL));
			operatorList.add(ctx.getString(org.droidtv.tunerservice.R.string.MAIN_COMHEM));
		}
		
		if (countryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA))) {
			operatorList.add(ctx.getString(org.droidtv.tunerservice.R.string.MAIN_TELEMACH));
		}
		operatorList.add(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER));
		if(euInst.isOperatorProfileSupported() && (analogOrDigital != NativeAPIEnums.AnalogueOrDigital.ANALOGUE) )
		{
			operatorList.add(euInst.getOperatorName());
		}

		Object[] ObjectList = operatorList.toArray();
		String[] operatorArray = Arrays.copyOf(ObjectList, ObjectList.length,
				String[].class);

		return operatorArray;
	}

	/**
	 * Gets the operator name from GlobalSettings
	 */
	public NativeAPIEnums.Operators getOperatorFromTVS() {

		NativeAPIEnums.Operators opEnum = NativeAPIEnums.Operators.Other;
		if (STUB_MODE) {
			opEnum = NativeAPIEnums.Operators.Other;
		} else {

			int operatorId = mTvSettingsManager.getInt(TvSettingsConstants.OPERATORCABLE, 0, 0);
			
			switch (operatorId) {
			case TvSettingsDefinitions.OperatorCableConstants.NONE:
				opEnum = NativeAPIEnums.Operators.Other;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.Ziggo:
				opEnum = NativeAPIEnums.Operators.Ziggo;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.UPC:
				opEnum = NativeAPIEnums.Operators.UPC;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.KDG:
				opEnum = NativeAPIEnums.Operators.KDG_SD;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.UNITYMEDIA:
				opEnum = NativeAPIEnums.Operators.Unitymedia;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.TELENET:
                opEnum = NativeAPIEnums.Operators.Telenet;
                break;
			case TvSettingsDefinitions.OperatorCableConstants.RCS_RDS:
				opEnum = NativeAPIEnums.Operators.RCSRDS;
	            break;
			case TvSettingsDefinitions.OperatorCableConstants.BLIZOO:
				opEnum = NativeAPIEnums.Operators.Blizoo;
	            break;				
			case TvSettingsDefinitions.OperatorCableConstants.CANALDIGITAL:
				opEnum = NativeAPIEnums.Operators.CanalDigital;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.YOUSEE:
				opEnum = NativeAPIEnums.Operators.YouSee;
	            break;	
			case TvSettingsDefinitions.OperatorCableConstants.TELEMACH:
				opEnum = NativeAPIEnums.Operators.Telemach;
	            break;	
			case TvSettingsDefinitions.OperatorCableConstants.COMHEM:
				opEnum = NativeAPIEnums.Operators.ComHem;
				break;
		    case TvSettingsDefinitions.OperatorCableConstants.KDGHD:
					opEnum = NativeAPIEnums.Operators.KDG_HD;
					break;
			default:
				opEnum = NativeAPIEnums.Operators.Other;
				break;
			}
		}
		return opEnum;
	}

	public String getCachedOperatorName() {
		return selectedOperatorStr;
	}
	
	public void selectCamBasedInstallation()
	{
		Log.d(TAG, "Select Cam based installation entry new");
		 operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.CAM;
         euInst.SetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeCam,
					euInstConst.IHsvInstallation2_AttributeNetworkOperator,
					operatorIdTVS);
         
	}

	/**
	 * Sets the operator id in TVSettings and MW
	 */
	public void setCachedOperatorID(int argOpID) {
		//operatorIndex = argOpID;
		int operatorIdMW = 0;
		int l_installationMode = euInstConst.IHsvInstallation2_InstallationModeAutomatic;

		String selectedOperator = getOperatorList()[argOpID];
		selectedOperatorStr = selectedOperator;

		if (STUB_MODE) {
		} else {
			/* TVSettings None = 0, Ziggo = 1, UPC = 2, KDG = 3, KBW = 4 */
			/* MW ziggo 0, upc 1, other 2, kdg 16, unitymedia 17 */
			if (selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.NONE;
				operatorIdMW = 0;
			} else if (selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ZIGGO))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.Ziggo;
				operatorIdMW = 1;
			} else if (selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.UPC;
				operatorIdMW = 2;
			}else if (selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UPC))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.UPC;
				operatorIdMW = 2;
			}else if (selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VF_STANDARD_SORTING))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.KDG;
				operatorIdMW = 4;
			} else if (selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_UNITYMEDIA))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.UNITYMEDIA;
				operatorIdMW = 3;
			}else if (selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET))) {
                operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.TELENET;
				operatorIdMW = 5;
			}//RCS-RDS
			else if(selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_RCS_RDS))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.RCS_RDS;
				operatorIdMW =  7;
			}
			else if(selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BLIZOO))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.BLIZOO;
				operatorIdMW =  8;
			}	
			else if(selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.tunerservice.R.string.MAIN_CANALDIGITAL))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.CANALDIGITAL;
				operatorIdMW =  9;
			}
			else if(selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YOUSEE))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.YOUSEE;
				operatorIdMW =  10;
			}			
			else if(selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.tunerservice.R.string.MAIN_TELEMACH))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.TELEMACH;
				operatorIdMW =  11;
			}
			else if(selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.tunerservice.R.string.MAIN_COMHEM))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.COMHEM;
				operatorIdMW =  12;
			}else if (selectedOperator.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VF_HD_SORTING))) {
				operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.KDGHD;
				operatorIdMW = 13;
			}
			else
			{
				if(euInst.isOperatorProfileSupported()&& (analogOrDigital != NativeAPIEnums.AnalogueOrDigital.ANALOGUE) )
				{
					if (selectedOperator.equalsIgnoreCase(euInst.getOperatorName())) {
		                operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.CAM;
		                operatorIdMW = 6;
		                l_installationMode = euInstConst.IHsvInstallation2_InstallationModeCam;
					}
				}
			}
		

			// set the operator in MW
			euInst.SetAttribute(
					l_installationMode,
					euInstConst.IHsvInstallation2_AttributeNetworkOperator,
					operatorIdMW);
			
            if (ifVirginInstallation()) {
                // set the operator in TVSettings
                mTvSettingsManager.putInt(TvSettingsConstants.OPERATORCABLE, 0,
                        operatorIdTVS);
            }
			Log.d(TAG, "setCachedOperatorID() " + selectedOperator + " set to mw " + operatorIdMW );
		}
	}

	/**
	 * Gets the selected menu language from TV
	 * 
	 * @return NativeAPIEnums.TVMenuLanguage returns selected tv lanugage
	 */
	public NativeAPIEnums.TVMenuLanguage getTVMenuLanguage() {
		return NativeAPIEnums.TVMenuLanguage.ENGLISH;
	}

	/**
	 * Get the current cached installation mode
	 * 
	 * @return current installation mode
	 */
	public NativeAPIEnums.InstallationMode getCurrentInstallationMode() {
		Log.d(TAG, "getCurrentInstallationMode: " + currentInstallationMode);
		return currentInstallationMode;
	}

	public void OpsemistandbyInstallationstarted(){
		Log.d(TAG, "Entered into OpsemistandbyInstallationstarted");
		opsemistandbyins = true;
        Intent intent = new Intent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
        intent.putExtra("InstallMode", "Auto");
        if (NativeAPIEnums.DVBTOrDVBC.DVBC == getCachedDVBTOrDVBC()) {
            intent.putExtra("InstallMedium", "Cable");
        } else {
            intent.putExtra("InstallMedium", "Terrestrial");
        }
        ctx.sendStickyBroadcast(intent);

	}

	public boolean isOpsemistandbyInstallationtriggered() {
		Log.d(TAG, "isOpsemistandbyInstallationtriggered returning " + opsemistandbyins);
		return opsemistandbyins;
	}
	
	public void OpsemistandbyInstallationcomplete(){
		Log.d(TAG, "Entered into OpsemistandbyInstallationcomplete");
		if(opsemistandbyins == true)
		{
		Intent intent = new Intent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");		
		intent.putExtra("InstallMode", "Auto");
		if (NativeAPIEnums.DVBTOrDVBC.DVBC == getCachedDVBTOrDVBC()) {
			intent.putExtra("InstallMedium", "Cable");
		} else {
			intent.putExtra("InstallMedium", "Terrestrial");
		}		
		 ctx.sendStickyBroadcast(intent);	
		 opsemistandbyins = false;
		}
	}

	/**
	 * Set the current cached installation mode
	 * 
	 */
	public void setCurrentInstallationMode (NativeAPIEnums.InstallationMode Mode) {
		Log.d(TAG, "setCurrentInstallationMode cur: " + currentInstallationMode + "New:" + Mode);
		currentInstallationMode = Mode;
	}
	
	public NativeAPIEnums.InstallationMode getMWInstallationMode() {
		NativeAPIEnums.InstallationMode returnInstallationMode = null; 
		if(euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModePreScan){
			returnInstallationMode = NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN;
		}else if(euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModeAutomatic){
			returnInstallationMode = NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION;
		}
		Log.d(TAG, "getMWInstallationMode() " + returnInstallationMode);
		return returnInstallationMode;
	}
	
	public void startAutoInstallation(){
		Log.d(TAG, "startAutoInstallation ");
		if (STUB_MODE) {
			//ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_ID, "");
			//ntf.notifyAllObservers(EventIDs.EVENT_FAV_NETWORK, "");
			//ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
			
			//ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_FREQ, "");
			
			ntf.notifyAllObservers(EventIDs.EVENT_LCN_CONFLICT, "");
		}else{
			if (countrySupportsDVBCFullorLite(getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light) {
				euInst.SetAttributeMode(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeNetworkFreq,
						euInstConst.IHsvInstallation2_ManualValue);
			}
			
			if(ifPrescanFirst()){
				stopAndRestartInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN);
			}else{
				stopAndRestartInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
			}
		}
	}
	
	public void stopAndRestartInstallation(NativeAPIEnums.InstallationMode mode){
		Log.d(TAG, "stopAndRestartInstallation: " + mode);
		if (euInst.GetInstallationStatus() == euInstConst.IHsvInstallation2_StIdle) {
			Log.d(TAG, "MW in idle mode");
			// already idle state start the installation
			ifStopAndRestartInstallation = false;
			startInstallation(mode);
		}else{
			Log.d(TAG, "MW not idle, trigger stop installation");
			ifStopAndRestartInstallation = true;
			currentInstallationMode = mode; // update current installation mode
			euInst.StopInstallation();
		}
	}
	
	/**
	 * This function triggers installation
	 * 
	 * @param NativeAPIEnums
	 *            .InstallationMode pass installation mode enum accordingly
	 */
	public void startInstallation(NativeAPIEnums.InstallationMode mode) {
		Log.d(TAG, "startInstallation Installation Mode: " + mode);
		
		ifStopAndRestartInstallation = false; // reset flag so it dosen't hear to installation stop
		IsMajorVersionChange = false;
		Log.d(TAG, "operatorIdTVS: " + operatorIdTVS);
		// update local cached variable to update the current intallation mode
		currentInstallationMode = mode;
		int l_installationMode = euInstConst.IHsvInstallation2_InstallationModeAutomatic;
		if(isOperatorProfileSupported() && (operatorIdTVS == TvSettingsDefinitions.OperatorCableConstants.CAM))
		{
			Log.d(TAG, "setting to IHsvInstallation2_InstallationModeCam " );
			l_installationMode = euInstConst.IHsvInstallation2_InstallationModeCam;
			currentInstallationMode = NativeAPIEnums.InstallationMode.CAM_INSTALLATION;
		}
		if (STUB_MODE) {
			if (mode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION
					|| mode == NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION) {
				// start progress thread to inject events and increase
				// progressbar
				// startInstThreadAndInjectEvents();
				// ntf.notifyAllObservers(EventIDs.EVENT_FAV_NETWORK, "");
				// ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
				// ntf.notifyAllObservers(EventIDs.EVENT_LCN_CONFLICT, "");
			} else if (mode == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN) {
				// ntf.notifyAllObservers(EventIDs.EVENT_TUNING_STATION_NOT_FOUND,"");
				// ntf.notifyAllObservers(EventIDs.EVENT_INST_COMPLETED, "");
			}
			// ntf.notifyAllObservers(EventIDs.EVENT_LCN_CONFLICT, "");
			// ntf.notifyAllObservers(EventIDs.EVENT_INST_COMPLETED, "");
			ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_ID, "");
			
		} else {
		    resetCachedBeforeInstallation();
			//euInst.bindChannelVersionManagerService();
			if (mode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION) {

				// start Reinstall in MW
				euInst.StartInstallation(euInstConst.IHsvAppApiMainTuner, 0,
						l_installationMode);
				euInst.SetHostControlStatus (false);
			} else if ((mode == NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION)|| (mode == NativeAPIEnums.InstallationMode.NETWORK_UPDATE) ) {
				// start Update in MW
				euInst.StartInstallation(euInstConst.IHsvAppApiMainTuner, 0,
						euInstConst.IHsvInstallation2_InstallationModeUpdate);
				euInst.SetHostControlStatus (false);

			} else if (mode == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN) {

				// start prescan in MW
				euInst.StartInstallation(euInstConst.IHsvAppApiMainTuner, 0,
						euInstConst.IHsvInstallation2_InstallationModePreScan);
			} else if (mode == NativeAPIEnums.InstallationMode.BACKGROUND_INSTALLATION) {
				// start BackGround Install
				int vst_enable = mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_VSECURE_OVER_RF_ENABLE, 0, 0);
				int vst_freq;
				String s_freq;
				if( vst_enable == TvSettingsDefinitions.PbsVsercureOverRfEnable.PBSMGR_VSECURE_OVER_RF_ENABLE_ON )
				{	
					s_freq = mTvSettingsManager.getString(TvSettingsConstants.PBSMGR_PROPERTY_VSECURE_PROGRAM_INFO_FREQUENCY, 0, "");
					vst_freq = ((Integer.parseInt(s_freq))*10 * 16 ) / 1000 ;
					Log.d(TAG, "Vesecure Freq, Before change " + (Integer.parseInt(s_freq)) + "After Convert" + vst_freq);	
            
					euInst.StartInstallation(
						euInstConst.IHsvAppApiMainTuner,
						vst_freq,
						euInstConst.IHsvInstallation2_InstallationModeBackground);
				}
				else {
					euInst.StartInstallation(
						euInstConst.IHsvAppApiMainTuner,
						0,
						euInstConst.IHsvInstallation2_InstallationModeBackground);
				}
			} else if (mode == NativeAPIEnums.InstallationMode.BACKGROUND_UPDATE) {		
				euInst.StartInstallation(euInstConst.IHsvAppApiMainTuner, 0,
										euInstConst.IHsvInstallation2_InstallationModeUpdate);
				euInst.SetHostControlStatus (false);
			} else if (mode == NativeAPIEnums.InstallationMode.CAM_INSTALLATION) {
				// start Cam based Installation Update from Service
			
				euInst.StartInstallation(
						euInstConst.IHsvAppApiMainTuner,
						0,
						euInstConst.IHsvInstallation2_InstallationModeCam);
				euInst.SetHostControlStatus (false);
			} else if (mode == InstallationMode.MANUAL_INSTALLATION) {
				// start ManualINstallation
				euInst.StartInstallation(euInstConst.IHsvAppApiMainTuner, 0,
						euInstConst.IHsvInstallation2_InstallationModeManual);
				euInst.SetHostControlStatus (false);
			}
		}
	}

	public int getFirstChannel(NativeAPIEnums.ChannelType chType) {
		int channelID = 0;

		if (STUB_MODE) {
			if (chType == NativeAPIEnums.ChannelType.ANALOG) {
			} else if (chType == NativeAPIEnums.ChannelType.DIGITAL) {
			} else if (chType == NativeAPIEnums.ChannelType.RADIO) {
				channelID = 500;
			}
		} else {
			if (chType == NativeAPIEnums.ChannelType.ANALOG) {
			    channelID = euInst.GetFirstIntalledAnalogueChannel();
			} else if (chType == NativeAPIEnums.ChannelType.DIGITAL) {
				channelID = euInst.GetFirstIntalledDigitalChannel();
			} else if (chType == NativeAPIEnums.ChannelType.RADIO) {
			    channelID = euInst.GetFirstIntalledRadioChannel();
			}
		}
		return channelID;
	}

	/**
	 * This function triggers stop installation
	 * 
	 * @param void
	 */
	public void stopBckInstallation() {
		if (STUB_MODE) {

		} else {
			euInst.StopMWInstIfInstExists();
			//euInst.StopInstallation();
		}
	}
	
	public void UnregisterTuningInstance () {
		euInst.UnregisterTuningInstance();
	}
	
	public void stopDTRInstallation() {
		if (STUB_MODE) {
			//ntf.notifyAllObservers(EventIDs.EVENT_PLPIDS_DETECTED, "");
			ntf.notifyAllObservers(EventIDs.EVENT_LCN_CONFLICT, "");
		} else {
			euInst.StopInstallation();
		}
	}

	/**
	 * This function triggers stop installation
	 * 
	 * @param void
	 */
	public void stopInstallation(boolean ifExitWizard) {
		if (STUB_MODE) {

		} else {
			euInst.StopInstallation();
		}

		// broadcast message to all the modules that auto installation started
		Intent intent = new Intent(
				"org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
		if (currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION) {
			intent.putExtra("InstallMode", "Auto");
		} else if (currentInstallationMode == NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION) {
			intent.putExtra("InstallMode", "Update");
		} else if (currentInstallationMode == NativeAPIEnums.InstallationMode.CAM_INSTALLATION) {
			intent.putExtra("InstallMode", "Auto");
		}

		if (NativeAPIEnums.DVBTOrDVBC.DVBC == getCachedDVBTOrDVBC()) {
			intent.putExtra("InstallMedium", "Cable");
		} else {
			intent.putExtra("InstallMedium", "Terrestrial");
		}
		ctx.sendStickyBroadcast(intent);
		
		Log.d(TAG,"send intent broadcast org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
		
		// finish wizard activity
		if (ifExitWizard) {
		    
		    // restore system country in mw
		    euInst.SetSystemCountry(mTVSCselectedCountryID);
		    
		    // reset all settings 
		    resetToPersistent();
		    
		    exitNonInteruptableMode();
		    
		    if(wizardActivityCtx != null){
		    	((InstallerWizardActivity)wizardActivityCtx).exitInstallationWizard();
		    }
			//closeActivity(wizardActivityCtx);
		}
	}
	
/*	private void closeActivity(Context argCtx){
		Log.d(TAG, "closeActivity " + argCtx);
		if(argCtx != null){
			((Activity)argCtx).finish();
		}
	}*/
	
	public void registerTimerTask(Timer argTimerTask){
		allTimerTasks.add(argTimerTask);
	}
	
	public void stopAllTimerTasks(){
		Log.d(TAG, "stopAllTimerTasks ");
		Iterator<Timer> timerIter = allTimerTasks.iterator();
		Timer timerTask;
		while(timerIter.hasNext()){
			timerTask = timerIter.next();
			try{
				timerTask.cancel();
				timerTask.purge();
			}catch(Exception ex){
			}			
		}
		
		// reset timertesk array
		allTimerTasks = new ArrayList<Timer>();
	}

	/**
	 * This function checks if Settings Mode should be available during
	 * autoinstall
	 * 
	 * @return boolean true if DVB installation is supported and a (full) DVB
	 *         country is selected
	 */
	public boolean ifSettingsAvaliable() {
		Boolean returnStatus = false;
		/*
		 * Only available if DVB installation is supported and a (full) DVB
		 * country is selected.
		 */
		if ((NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light == countrySupportsDVBTFullorLite(getCachedCountryName()) && (getCachedDVBTOrDVBC() == DVBTOrDVBC.DVBT )) || (analogOrDigital == NativeAPIEnums.AnalogueOrDigital.ANALOGUE)){
		}else{
		    returnStatus = true;
		}
		return returnStatus;
	}

	/**
	 * This function installation progress percentage
	 * 
	 * @return int installation percentage
	 */
	public int getInstallationProgress() {
		if (STUB_MODE) {
			return instProgressPercentage;
		} else {

			instProgressPercentage = euInst.getPogressStatus();
			return instProgressPercentage;
		}
	}

	/**
	 * This function gets cached value of digital channel count during
	 * installation
	 * 
	 * @return int digital channel count
	 */
	public int getCachedDigitalChannelCount() {
		return digitalChannelCount;
	}

	/**
	 * This function gets cached value of digital channels removed during
	 * installation
	 * 
	 * @return int digital channel count
	 */
	public int getCachedDigitalChannelRemoved() {
		return digitalChannelsRemoved;
	}

	/**
	 * This function gets cached value of analog channel count during
	 * installation
	 * 
	 * @return int analogue channel count
	 */
	public int getCachedAnalogueChannelCount() {
		return analogueChannelCount;
	}

	/**
	 * This function returns digital channels added
	 * 
	 * @return int digital channel count
	 */
	public int getDigitalChannelCount() {
		int channelCount = 0;
		if (STUB_MODE) {
			channelCount = digitalChannelCount;
		} else {
			channelCount = euInst.GetNumberOfDigitalChannelsFound();
			digitalChannelCount = channelCount; // update for local cache to be
			// read from finish page
		}
		return channelCount;
	}

	public boolean mLcnConflictCountry () {
		boolean	retVal = false;
		/* In live testing Sweden is having LCN conflict in DVBT. So every update installation in standby
			Channels in non-honored are getting invalidated and added again to same position. 
			Hence MajorVersion notifications are generated from MW. This needs to be ignored. Putting this under this diversity method */
		String selectedCountryInTVS = getCountryNameFromTVS();
		int dvbMediumID = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
		if ((dvbMediumID == TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA) && 
				(selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN)))) {
					Log.d(TAG, "Sweden DVBT ");
					retVal = true;
		}
				
		return retVal;
	}
	
	
	
	/**
	 * This function returns digital channels removed
	 * 
	 * @return int digital channel count
	 */
	public int getDigitalChannelsRemoved() {
		int channelCount = 0;
		if (STUB_MODE) {
			channelCount = digitalChannelsRemoved;
		} else {
			channelCount = euInst.GetNumberOfDigitalChannelsRemoved();
			digitalChannelsRemoved = channelCount; // update for local cache to
			// be read from finish page
		}
		return channelCount;
	}

	/**
	 * This function gives analogue channel count
	 * 
	 * @return int analogue channel count
	 */
	public int getAnalogueChannelCount() {
		int channelCount = 0;
		if (STUB_MODE) {
			channelCount = analogueChannelCount;
		} else {
			channelCount = euInst.GetNumberOfAnalogChannelsFound();
			analogueChannelCount = channelCount; // update for local cache to be
			// read from finish page
		}
		return channelCount;
	}

	/**
	 * This function returns the netowrk id char count
	 * 
	 * @return int 4 or 5
	 */
	public int getNetworkIDCharCount() {
		int returnCharCount = 5;
		return returnCharCount;
	}
	
	public int getNetworkID() {
        int returnNetwkID = 0;
        if (STUB_MODE) {
            returnNetwkID = 12345;
        } else {
            //returnNetwkID = euInst.getDefaultNetworkID();
            returnNetwkID = euInst.GetAttribute(
                    euInstConst.IHsvInstallation2_InstallationModeAutomatic,
                    euInstConst.IHsvInstallation2_AttributeNetworkId);
            
            if (getCachedCountryName().equalsIgnoreCase(
                    ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))
                    && getCachedOperatorName().equalsIgnoreCase(
                            ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ZIGGO))
                    && ifVirginInstallation()) {
                // ziggo specific modifications
                returnNetwkID = 5555;
            } else if (getCachedCountryName().equalsIgnoreCase(
                    ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))
                    && getCachedOperatorName().equalsIgnoreCase(
                            ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET))
                    && ifVirginInstallation()) {
                // telenet specific modifications
                returnNetwkID = 22;
            } else if (getCachedCountryName().equalsIgnoreCase(
                    ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))
                    && getCachedOperatorName().equalsIgnoreCase(
                            ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YOUSEE))
                    && ifVirginInstallation()) {
                // telenet specific modifications
                returnNetwkID = 100;
            }
        }

        Log.d(TAG, "getNetworkID() " + returnNetwkID);
        
        return returnNetwkID;
    }
	
	public int getNetworkFrequency() {
        int returnNetwkFreq = 0;
        int netwkFreq = 0;
        if (STUB_MODE) {
            returnNetwkFreq = 48400;
        } else {
            netwkFreq = euInst.GetAttribute(
                    euInstConst.IHsvInstallation2_InstallationModeAutomatic,
                    euInstConst.IHsvInstallation2_AttributeNetworkFreq);

            Log.d(TAG, "getNetworkFrequency() netwkFreq1 " + netwkFreq);
            netwkFreq = (netwkFreq * 1000)/16;
            
            if (getCachedCountryName().equalsIgnoreCase(
                    ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))
                    && getCachedOperatorName().equalsIgnoreCase(
                            ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ZIGGO))
                    && ifVirginInstallation()) {
                // ziggo specific modifications
                netwkFreq = 474000;
            } else if (getCachedCountryName().equalsIgnoreCase(
                    ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))
                    && getCachedOperatorName().equalsIgnoreCase(
                            ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET))
                    && ifVirginInstallation()) {
                // telenet specific modifications
                netwkFreq = 322000;
            }
            
           /* int minFreq = 0;
            int maxFreq = 863000;
            
            if(getWSFreqStepSize() == 1){
                // 8Mhz
                if((getWSFreqScanMode() == 1) || (getWSNetworkFrequencyMode() == 0 ) || (countrySupportsDVBCFullorLite(getCachedCountryName()) == DVBTOrDVBCMacro.DVBC_Light)){
                    // (fullscan || automatic freq || clite){
                    minFreq = 114000;
                }else{
                    minFreq = 108000;
                }
            }else{
                // 1Mhz
                minFreq = 108000;
            }
            
            Log.d(TAG, "getNetworkFrequency() minFreq " + minFreq);
            Log.d(TAG, "getNetworkFrequency() maxFreq " + maxFreq);
            
            if ((netwkFreq >= minFreq) && (netwkFreq <= maxFreq)) {
                // network frequncty in range
            } else if (netwkFreq < minFreq) {
                netwkFreq = minFreq;
            } else if (netwkFreq > maxFreq) {
                netwkFreq = maxFreq;
            }*/
            
            Log.d(TAG, "getNetworkFrequency() netwkFreq2 " + netwkFreq);
            
            // extra check added to make digit
            netwkFreq = netwkFreq/10;
            
            returnNetwkFreq = netwkFreq;
        }
        
        Log.d(TAG, "getNetworkFrequency() " + returnNetwkFreq);
        return returnNetwkFreq;
    }

	/*
	 * validates the entered network ID
	 * 
	 * @Params network ID is correct
	 */
	public Boolean ifValidNetworkID(int argNetwkID) {
		Boolean returnStatus = false;

		if (STUB_MODE) {
			returnStatus = true;
		} else {
			// TODO MW call
			returnStatus = euInst.ifValidNetworkIDEntered(argNetwkID);
		}
		Log.d(TAG, "ifValidNetworkID() " + returnStatus);
		return returnStatus;
	}

	/*
	 * validates the entered network network frequency
	 * 
	 * @Params networkfrequency
	 */
	public Boolean ifValidNetworkFrequency(int argNetwkFreq) {
	    Log.d(TAG, "ifValidNetworkFrequency() argNetwkFreq " + argNetwkFreq);
        Boolean returnStatus = false;

        if (STUB_MODE) {
            returnStatus = true;
        } else {
            int khzFreq = argNetwkFreq * 10;
            int minFreq = 0;
            int maxFreq = 863000;
                       
            if(getWSFreqStepSize() == 1){
                // 8Mhz
                if((getWSFreqScanMode() == 1) || (getWSNetworkFrequencyMode() == 0 ) || (countrySupportsDVBCFullorLite(getCachedCountryName()) == DVBTOrDVBCMacro.DVBC_Light)){
                    // (fullscan || automatic freq || clite){
                    minFreq = 114000;
                }else{
                    minFreq = 108000;
                }
            }else{
                // 1Mhz
                minFreq = 108000;
            }
            
            if ((khzFreq >= minFreq) && (khzFreq <= maxFreq)) {
                // network frequency in range
                returnStatus = true;
            } 
        }
		Log.d(TAG, "ifValidNetworkFrequency() " + returnStatus);
		return returnStatus;
	}

	public void setNetworkFrequency(int argNetwkFreq) {
	    int khzFreq = argNetwkFreq * 10;
	    int convertedFreq = 0;
        // network frequncy set start the prescan
        
        Log.d(TAG, "setNetworkFrequency() khzFreq " +  khzFreq);
        if (STUB_MODE) {            
        } else {
            
            int minFreq = 0;
            int maxFreq = 863000;
            
            if(getWSFreqStepSize() == 1){
                // 8Mhz
                if((getWSFreqScanMode() == 1) || (getWSNetworkFrequencyMode() == 0 ) || (countrySupportsDVBCFullorLite(getCachedCountryName()) == DVBTOrDVBCMacro.DVBC_Light)){
                    // (fullscan || automatic freq || clite){
                    minFreq = 114000;
                }else{
                    minFreq = 108000;
                }
            }else{
                // 1Mhz
                minFreq = 108000;
            }
            
            Log.d(TAG, "setNetworkFrequency() minFreq " + minFreq);
            Log.d(TAG, "setNetworkFrequency() maxFreq " + maxFreq);
            
            if ((khzFreq >= minFreq) && (khzFreq <= maxFreq)) {
                // network frequency in range
            } else if (khzFreq < minFreq) {
                khzFreq = minFreq;
            } else if (khzFreq > maxFreq) {
                khzFreq = maxFreq;
            }
            
            convertedFreq = (int)((khzFreq * 16) / 1000);
            Log.d(TAG, "setNetworkFrequency() convertedFreq " +  convertedFreq);
            
            euInst.SetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic, euInstConst.IHsvInstallation2_AttributeNetworkFreq, convertedFreq);
            
            Log.d(TAG, "setNetworkFrequency() khzFreq convertedFreq " +  convertedFreq);
        }
    }

	/*
	 * getting the network name
	 * 
	 * @Return String network name
	 */
	public String getNetworkName(Integer networkID) {
		String netwkName = "";
		if (STUB_MODE) {
			netwkName = "Network Name";
		} else {
			// TODO MW api required
			netwkName = euInst.getNetworkName(networkID);
		}
		Log.d(TAG, "getNetworkName() " + networkID + " : " + netwkName);
		return netwkName;
	}
	
	public void setNetworkID(int argNetworkID) {
        if (STUB_MODE) {

        } else {
            // TODO MW api required
            euInst.SetAttributeMode(
                    euInstConst.IHsvInstallation2_InstallationModeAutomatic,
                    euInstConst.IHsvInstallation2_AttributeNetworkId,
                    euInstConst.IHsvInstallation2_ManualValue);
            euInst.SetAttribute(
                    euInstConst.IHsvInstallation2_InstallationModeAutomatic,
                    euInstConst.IHsvInstallation2_AttributeNetworkId,
                    argNetworkID);
        }
        
        Log.d(TAG, "setNetworkID() " + argNetworkID);
    }

	/*
	 * getting the favourite network list
	 * 
	 * @Return String[] favourite networks
	 */
	public String[] getFavouriteNwkList() {
		String[] returnNetworkList = null;
		int favNetworkCount = 0;
		if (STUB_MODE) {
			returnNetworkList = new String[] { "Network 0", "Network 1",
					"Network 2", "Network 3" };
		} else {
			// TODO MW API call
			favNetworkCount = euInst.GetNetworkIDList();
			Log.d(TAG, "getFavouriteNwkList() favNetworkCount " + favNetworkCount);
			returnNetworkList = new String[favNetworkCount];
			for (int nidIndex = 0; nidIndex < favNetworkCount; nidIndex++) {
				returnNetworkList[nidIndex] = euInst.GetNetworkIDName(nidIndex);
				Log.d(TAG, "getFavouriteNwkList() favNetworkName " + returnNetworkList[nidIndex]);
			}
		}

		Log.d(TAG, "getFavouriteNwkList() " + returnNetworkList.length);
		return returnNetworkList;
	}
	public String[] getFavouritechannelList() {
		String[] returnChannelList = null;
		int favChannelListCount = 0;
		if (STUB_MODE) {
			returnChannelList = new String[] { "ChannelList 0", "ChannelList 1",
					"ChannelList 2", "ChannelList 3" };
		} else {
			favChannelListCount = euInst.GetNumberOfChannelListIds();
			Log.d(TAG, "getFavouritechannelList() favChannelListCount " + favChannelListCount);
			returnChannelList = new String[favChannelListCount];
			for (int nidIndex = 0; nidIndex < favChannelListCount; nidIndex++) {
				returnChannelList[nidIndex] = euInst.GetChannelListIDName(nidIndex);
				Log.d(TAG, "getFavouritechannelList() " + returnChannelList[nidIndex]);
			}
		}
		Log.d(TAG, "getFavouritechannelList() " + returnChannelList.length);
		return returnChannelList;
		
	}
	/*
	 * setting the favourite channelList
	 * 
	 * @Params favourite channelList
	 */

	public void setFavouritechannelList(int favChannelListIDindex) {
		if (STUB_MODE) {

		} else {
			// TODO MW api
			euInst.SetFavouriteChannelListId(euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkId,favChannelListIDindex);
			euInst.UserSelectionDone(true);
		}

		Log.d(TAG, "setFavouritechannelList() " + favChannelListIDindex);
	}

	/*
	 * setting the favourite network
	 * 
	 * @Params favourite networkId
	 */

	public void setFavouriteNetwork(int favNetwkIDindex) {
		if (STUB_MODE) {

		} else {
			// TODO MW api
			euInst.SetFavouriteNetworkID(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkId,
					favNetwkIDindex);

			euInst.UserSelectionDone(true);
		}

		Log.d(TAG, "setFavouriteNetwork() " + favNetwkIDindex);
	}

	/*
	 * Get the current reqion mode
	 * 
	 * @Return Primary, Secondary, Tertiary
	 */
	public NativeAPIEnums.Regions getCurrentRegionMode() {
		Log.d (TAG, "CurrentRegionMode " + currentRegionMode);
		return currentRegionMode;
	}

	public void setCurrentRegionMode(NativeAPIEnums.Regions argRegion) {
		Log.d (TAG, "setCurrentRegionMode " + argRegion);
		 currentRegionMode = argRegion;
	}
	
	public void setIfUserSelectionDone(boolean ifUserSelectionDone){
		Log.d (TAG, "setIfUserSelectionDone " + ifUserSelectionDone);
		euInst.UserSelectionDone(ifUserSelectionDone);
	}
	/*
	 * This function gives primary regions
	 * 
	 * @Return String[] primary regions
	 */
	public String[] getPrimaryRegions() {
		if (STUB_MODE) {
			primaryRegions = new String[] { "Primary Region1",
					"Primary Region2", "Primary Region3" };
		} else {
			String []mwStringArray = euInst.getRegionList(PRIMARY_REGION_CASE, 0, 0);
			if(mwStringArray == null){
				primaryRegions =  new String[] {};
			}else{
				primaryRegions = new String[mwStringArray.length + 1];
				for (int index=0; index < mwStringArray.length; index++){
					primaryRegions[index] = mwStringArray[index];
				}
				primaryRegions[mwStringArray.length] = ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER);
			}
		}
		for (int index=0; index < primaryRegions.length; index++){
			Log.d(TAG, "getPrimaryRegions() " + primaryRegions[index]);
		}
		return primaryRegions;

	}

	/*
	 * setting the primary regions
	 * 
	 * @Params primary region id
	 */
	public void setPrimaryRegion(int primaryRegion) {
		primaryRegionIndex = primaryRegion;

		if (STUB_MODE) {
			currentRegionMode = NativeAPIEnums.Regions.SECONDARY;
			ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
		} else {
			
			// last string is other check if user pressed on other
			if(primaryRegion == (primaryRegions.length -1) ){
				euInst.UserSelectionDone(true);
			}else{
				euInst.setRegionList(PRIMARY_REGION_CASE, primaryRegion);
				
				String[] secondaryRegions = getSecondayRegions();
				
				Log.d(TAG, "setPrimaryRegion secondaryRegions " + secondaryRegions.length);
				
				if ((secondaryRegions.length == 0) || (secondaryRegions.length == 1)){
					// no secondary region commit to current selected region				
					euInst.UserSelectionDone(true);
				} /*else if (secondaryRegions.length == 1) {
					// only one secondary region no need to ask user set
					// the region directly
					setSecondayRegion(0);
	
					// check if current secondary region contains further tertiary
					// regions
					String[] tertiaryRegions = getTeritaryRegions();
					Log.d(TAG, "setPrimaryRegion tertiaryRegions " + tertiaryRegions.length);
					if (tertiaryRegions.length == 0) {
						// no tertiary region commit to current selected region
						euInst.UserSelectionDone(true);
					} else if (tertiaryRegions.length == 1) {
						// only one tertiary region no need to ask user set
						// the region directly
						setTeritoryRegion(0);
	
						euInst.UserSelectionDone(true);
					} else {
						Log.d (TAG, "RegionMode Teriary" );
						// multiple tertiary regions popup dialog
						currentRegionMode = NativeAPIEnums.Regions.TERTIARY;
						ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
					}
				}*/ else {
					Log.d (TAG, "RegionMode Secondary" );
					// multiple secondary regions popup dialog
					currentRegionMode = NativeAPIEnums.Regions.SECONDARY;
					ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
				}
			}
		}

	}

	/*
	 * This function gives secondary regions
	 * 
	 * @Return String[] secondary regions
	 */
	public String[] getSecondayRegions() {

		// for the specific primary region get the sub secondary regions
		if (STUB_MODE) {
			secondaryRegions = new String[] { "Secondary Region1",
					"Secondary Region2", "Secondary Region3" };
		} else {
			String []mwStringArray = euInst.getRegionList(SECONDARY_REGION_CASE, primaryRegionIndex, 0);
			
			if(mwStringArray == null){
				secondaryRegions =  new String[] {};
			}else{
				secondaryRegions = new String[mwStringArray.length + 1];
				for (int index=0; index < mwStringArray.length; index++){
					secondaryRegions[index] = mwStringArray[index];
				}
				secondaryRegions[mwStringArray.length] = ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER);
			}
		}
		
		for (int index=0; index < secondaryRegions.length; index++){
			Log.d(TAG, "getSecondayRegions() " + secondaryRegions[index]);
		}
		return secondaryRegions;
	}

	/*
	 * setting the secondary region
	 * 
	 * @Params secondary region id
	 */
	public void setSecondayRegion(int secondaryRegion) {
		secondaryRegionIndex = secondaryRegion;

		if (STUB_MODE) {
			currentRegionMode = NativeAPIEnums.Regions.TERTIARY;
			ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
		} else {
			
			if(secondaryRegion == (secondaryRegions.length -1) ){
				euInst.UserSelectionDone(true);
			}else{
				euInst.setRegionList(SECONDARY_REGION_CASE, secondaryRegion);
				
				// check if current secondary region contains further tertiary
				// regions
				String[] tertiaryRegions = getTeritaryRegions();
	
				if ((tertiaryRegions.length == 0) || (tertiaryRegions.length == 1)) {
					// no tertiary region commit to current selected region
					euInst.UserSelectionDone(true);
				} /*else if (tertiaryRegions.length == 1) {
					// only one tertiary region no need to ask user set
					// the region directly
					setTeritoryRegion(0);
					euInst.UserSelectionDone(true);
				}*/ else {
					Log.d (TAG, "RegionMode Tertiary" );
					// multiple tertiary regions popup dialog
					currentRegionMode = NativeAPIEnums.Regions.TERTIARY;
					ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
				}
			}
		}
		
		Log.d(TAG, "setSecondayRegion " + secondaryRegion);

	}

	/*
	 * This function gives teritory regions
	 * 
	 * @Return String[] teritory regions
	 */
	public String[] getTeritaryRegions() {
		if (STUB_MODE) {
			teritaryRegions = new String[] { "Tertiary Region1",
					"Tertiary Region2", "Tertiary Region3" };
		} else {
			String [] mwStringArray = euInst.getRegionList(TERTIARY_REGION_CASE, primaryRegionIndex, secondaryRegionIndex);
			
			if(mwStringArray == null){
				teritaryRegions =  new String[] {};
			}else{
				teritaryRegions = new String[mwStringArray.length + 1];
				for (int index=0; index < mwStringArray.length; index++){
					teritaryRegions[index] = mwStringArray[index];
				}
				teritaryRegions[mwStringArray.length] = ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER);
			}
		}
		for (int index=0; index < teritaryRegions.length; index++){
			Log.d(TAG, "getTeritaryRegions() " + teritaryRegions[index]);
		}
		return teritaryRegions;
	}

	/*
	 * setting the teritory regions
	 * 
	 * @Params teritory region
	 */
	public void setTeritoryRegion(int teritoryRegion) {
		if (STUB_MODE) {

		} else {
			if(teritoryRegion == (teritaryRegions.length -1) ){
				euInst.UserSelectionDone(true);
			}else{
				euInst.setRegionList(TERTIARY_REGION_CASE, teritoryRegion);
				euInst.UserSelectionDone(true);
			}
		}
	}
	
	public Boolean ifPrescanFirst() {
		Boolean returnStatus = false;
		if (STUB_MODE) {
			returnStatus = true;
		} else {
			if ((euInstConst.IHsvInstallation2_QuickScan == euInst.GetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic,euInstConst.IHsvInstallation2_AttributeScanMode))
					&& (getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
					&& (true == ifDigitalOptionOn())) {
				if (	getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY)) 		|| 
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))	||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY)) 		|| 
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA)) 		|| 
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND)) 	||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA))   	||						
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UKRAINE)) 		||
						getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA))){
					returnStatus = true;
				}else if(countrySupportsDVBCFullorLite(getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light){
					returnStatus = true;
				}else{
					returnStatus = false;
				}
			}
			
			if(NativeAPIEnums.AnalogueOrDigital.ANALOGUE == getCachedAnalogueDigital()){
				// in case of analog dont trigger prescan
				returnStatus = false;
			}
		}
		Log.d(TAG, "ifPrescanFirst() " + returnStatus + " for country " + getCachedCountryName());		
		return returnStatus;
	}
	
    public Boolean ifShowNetworkName() {
        Boolean returnStatus = false;
        if (STUB_MODE) {
            returnStatus = true;
        } else {

            if ((euInstConst.IHsvInstallation2_FullScan == euInst.GetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic, euInstConst.IHsvInstallation2_AttributeScanMode))
                    && (getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)) {
                returnStatus = true;
            }
        }

        Log.d(TAG,"ifShowNetworkName " + returnStatus);
        return returnStatus;
    }

    public boolean ifNetworkFreqMode(){
        boolean returnStatus = false;
        if (STUB_MODE) {
            returnStatus = true;
        } else {
            
            if(getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC){
                if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND))) {
                    returnStatus = false;
                }else if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA))){
                        if(getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC))){
                            returnStatus = true;
                        }
                    }
                }
            }
        Log.d(TAG, "ifNetworkFreqMode() " + returnStatus);
        return returnStatus;
    }
	/*
	 * if Network frequency dialog
	 * 
	 * @Return if netowrk freq dialog should be launched
	 */
    public Boolean ifNetworkFreqDialog() {
        Boolean returnStatus = false;
        if (STUB_MODE) {
            returnStatus = false;
        } else {
            // if(mw scanning mode is quickscan){
            // if (country = netherland, belgium, austria, swiss, hungary,
            // poland, ireland or (romania && upc) or (DVB-CLite && Digital on)
            if ((euInstConst.IHsvInstallation2_QuickScan == euInst.GetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic, euInstConst.IHsvInstallation2_AttributeScanMode))
                    && (getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)) {
                Log.d(TAG, "ifNetworkFreqDialog 0");
                if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND))
                        || getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND))) {
                    Log.d(TAG, "ifNetworkFreqDialog 1");
                    returnStatus = true;
                }else if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA)) &&
                        getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC))){
                    Log.d(TAG, "ifNetworkFreqDialog 2");
                    returnStatus = true;
                }else if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA)) &&
                        getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BLIZOO))){
                    Log.d(TAG, "ifNetworkFreqDialog 3");
                    returnStatus = true;
                }else if((countrySupportsDVBCFullorLite(getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light) && 
                            ifDigitalOptionOn()){
                    returnStatus = true;
                    Log.d(TAG, "ifNetworkFreqDialog 4");
                }
            }

            if (NativeAPIEnums.AnalogueOrDigital.ANALOGUE == getCachedAnalogueDigital()) {
                // in case of analog dont show networkfreq
                returnStatus = false;
            }
        }
        Log.d(TAG, "ifNetworkFreqDialog() " + returnStatus);
        return returnStatus;
    }

	public void setPinEntryInTVS(int pinID){
	    Log.d(TAG, "setPinEntryInTVS() " + pinID);
	    mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSPINCODE,0,pinID);
	    Log.d(TAG, "setPinEntryInTVS() " + mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSPINCODE, 0, 0));
	}
	
	public boolean ifShowPinEntryScreen(){
	    boolean returnStatus = false;
	    int currentPin = -1;
       
        // if country is france or italy & pin entry is not already set
        currentPin = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSPINCODE, 0, 0);
        Log.d(TAG, "ifShowPinEntryScreen() " + currentPin);
		//== Kalo added 0909_15, Fix  [TF415PHIEUMTK03-604] ==
		/*
		if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE))||
            getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY)) ||
            getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))) && 
            (currentPin == -1)){
            returnStatus = true;
        } */
        Log.d(TAG, "ifShowPinEntryScreen() " + returnStatus);
        return returnStatus;
    }
	/*
	 * skip Netork ID dialog
	 */
	public int skipNetworkID(int attempt) {
		int nID = 0;
		if (STUB_MODE) {
			nID = 0;
		} else {
			nID = skipNetworkFrequency(attempt);
		}

		Log.d(TAG, "skipNetworkID " + attempt + " : " + nID);
		return nID;
	}

	/*
	 * skip LCN resolve dialog
	 * 
	 * @Param true: selection done ... false; selection skipped
	 */
	public void lcnSelectionDone(Boolean ifDone) {
		if (STUB_MODE) {
			ntf.notifyAllObservers(EventIDs.EVENT_INST_COMPLETED, "");			
		} else {
			// TODO MW API
			euInst.ConflictsSelectionDone(ifDone);
		}
	}

	/*
	 * get lcn conflict first column channel numbers
	 */

    public String[] getConflictingChannelNumbers() {
        String[] returnArray = null;
        int[] conflictNumArray = null;
        Log.d(TAG, "getConflictingChannelNumbers enter");

        if (STUB_MODE) {
            returnArray = new String[10];
            for (int localIndex = 0; localIndex < 10; localIndex++) {
                returnArray[localIndex] = "" + localIndex;
            }
        } else {
            conflictNumArray = euInst.getConflictingChannelNumbers();

            if (conflictNumArray == null) {
                conflictNumArray = new int[] {};
            }

            returnArray = new String[conflictNumArray.length];
            for (int index = 0; index < conflictNumArray.length; index++) {
                returnArray[index] = Integer.toString(conflictNumArray[index]);
            }

        }
        Log.d(TAG, "getConflictingChannelNumbers exit");

        return returnArray;
    }

	/*
	 * get lcn conflict second column channel names
	 */

    public String[] getConflictingChannelNames(int argChannelNumber) {
        Log.d(TAG, "getConflictingChannelNames channelNumber " + argChannelNumber);
        lcnConflictChannelNumber = argChannelNumber;
        if (STUB_MODE) {
            lcnServiceNames = new String[10];
            for (int localIndex = 0; localIndex < 10; localIndex++) {
                lcnServiceNames[localIndex] = "ChannelName " + lcnConflictChannelNumber + "_" + localIndex;
            }
        } else {
            Log.d(TAG, "getConflictingChannelNames 1");
            lcnServiceNames = euInst.getConflictingChannelNames(lcnConflictChannelNumber);
            Log.d(TAG, "getConflictingChannelNames 2");
            if (lcnServiceNames == null) {
                lcnServiceNames = new String[] {};
            }
        }
        
        for (int index = 0; index < lcnServiceNames.length; index++){
            Log.d(TAG, "getConflictingChannelNames() " + lcnServiceNames[index]);
        }
        Log.d(TAG, "getConflictingChannelNames exit");
        return lcnServiceNames;
    }

	/*
	 * set conflicting channel number
	 */
	public void setConflictingChannelNumbers(int chNo) {
		Log.d(TAG, "setConflictingChannelNumbers " + chNo);

		lcnConflictChannelNumber = chNo;
		if (STUB_MODE) {

		} else {
		}
	}

	/*
	 * set conflicting channel Name
	 */
	public void setConflictingChannelNames(int serviceIndex) {
		Log.d(TAG, "setConflictingChannelNumbers " + serviceIndex);
		if (STUB_MODE) {

		} else {
			// TODO MW API
			euInst.SetUserSelectConflictService(lcnConflictChannelNumber,serviceIndex);
		}
	}

	/*
	 * skip Netork Frequncy dialog
	 */
	public int skipNetworkFrequency(int attempt) {
		Log.d(TAG, "skipNetworkFrequency attempt: " + attempt);
		int lowestNID = 0xFFFF;
		if (STUB_MODE) {
		} else {
			
			lowestNID = 0xFFFF;
			
			euInst.SkipInstallationScans(euInstConst.IHsvInstallation2_ScanDVBT | euInstConst.IHsvInstallation2_ScanDVBC | euInstConst.IHsvInstallation2_ScanDVBS);
			
			if ((getMWInstallationMode() == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN) && 
					(countrySupportsDVBCFullorLite(getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)){
				Log.d(TAG, "skipNetworkFrequency 1" );
				// get the least NID value
				
				int[] nIDList = getNIDsFound();
				if (nIDList.length != 0) {
					 for(int nidIndex = 0; nidIndex < nIDList.length; nidIndex++){
						 if(nIDList[nidIndex] < lowestNID){
							 lowestNID = nIDList[nidIndex];
						 }
					 }
				}
				
				// set manual nid value
				euInst.SetAttributeMode(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeNetworkId,
						euInstConst.IHsvInstallation2_ManualValue);
				
				euInst.SetAttribute(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeNetworkId,
						lowestNID);
				Log.d(TAG, "skipNetworkFrequency lowestNID:" + lowestNID);
				
				// start auto installation
				stopAndRestartInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
			} else {
				if (countrySupportsDVBCFullorLite(getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light) {
					Log.d(TAG, "skipNetworkFrequency 2");
					stopAndRestartInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN);
				} else {
					Log.d(TAG, "skipNetworkFrequency 3");
					stopAndRestartInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
				}
			}
		}
		
		Log.d(TAG, "skipNetworkFrequency lowestNID " + lowestNID);
		return lowestNID;
	}

	/*
	 * if check Network ID's
	 * 
	 * @Return if network ID should be checked
	 */
	public int[] getNIDsFound() {
		int[] returnArray = null;
		if (STUB_MODE) {
			returnArray = new int[] { 00000, 11111, 22222 };
		} else {
			// TODO MW api required
			returnArray = euInst.getNIDsFound();

			if(returnArray == null){
			    Log.d(TAG, "getNIDsFound() returnArray is null");
				returnArray =  new int[] {};
			}

			for (int index =0 ; index < returnArray.length; index++){
				Log.d(TAG, "getNIDsFound() " + index + " : " + returnArray[index]);
			}
		}
		return returnArray;
	}

	/*
	 * if check Network ID's
	 * 
	 * @Return if network ID should be checked
	 */
	public Boolean ifCheckNIDs() {
		Boolean returnStatus = false;
		if (STUB_MODE) {
			returnStatus = false;
		} else {
			if (((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
					&& getCachedCountryName().equalsIgnoreCase(
							ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS)) && (getCachedOperatorName()
					.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ZIGGO)) || getCachedOperatorName()
					.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER))))
					|| ((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
							&& getCachedCountryName().equalsIgnoreCase(
									ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM)) && getCachedOperatorName()
							.equalsIgnoreCase(
									ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET)))

			) {
				returnStatus = false;
			}else{
				returnStatus = true;
			}
		}
		Log.d(TAG, "ifCheckNIDs " + returnStatus);
		return returnStatus;
	}

	public boolean ifYouseeOperator()
	{
		boolean returnStatus = false;
		if((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
							&& getCachedCountryName().equalsIgnoreCase(
									ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK)) 
							&& getCachedOperatorName().equalsIgnoreCase(
									ctx.getString(org.droidtv.ui.strings.R.string.MAIN_YOUSEE)))
		{
			returnStatus = true;
		}
		Log.d(TAG, "ifYouseeOperator " + returnStatus);
		return returnStatus;
	}
	public boolean ifHandleInvalidNID(){
		boolean returnStatus = true;
		if ((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
				&& getCachedCountryName().equalsIgnoreCase(
						ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND))){
			returnStatus = false;			
		}
		return returnStatus;
	}

	public Boolean setDigitalOption(boolean ifOn) {
		ifDigitalOn = ifOn;
		if (STUB_MODE) {

		} else {
			// TODO MW api required
			int setValue = 0;
			setValue = ifOn ? 1 : 0;

			euInst.SetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDigitalOption,
					setValue);
		}
		return ifDigitalOn;
	}

	/*
	 * if Network frequency dialog
	 * 
	 * @Return if digital option is on in advanced menu settings
	 */
	public Boolean ifDigitalOptionOn() {
		if (STUB_MODE) {
			ifDigitalOn = true;
		} else {
			// TODO MW api required
			int returnType = euInst.GetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDigitalOption);
			ifDigitalOn = (returnType == 0) ? false : true;

		}
		Log.d(TAG, "ifDigitalOptionOn " + ifDigitalOn);
		return ifDigitalOn;
	}

	public int getDTTScanStatus() {
		int returnStatus = 0;
		if (STUB_MODE) {
		} else {
			returnStatus = euInst.GetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDTTScanOnAnalog);
			// 1: Default On
			// 0: Default Off
		}
		Log.d(TAG, "getDTTScanStatus " + returnStatus);
		return returnStatus;
	}

	public void setDTTScanStatus(int DTTScanStatus) {
		if (STUB_MODE) {

		} else {
			// 1: Scan On
			// 0: Scan Off
			euInst.SetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDTTScanOnAnalog,
					DTTScanStatus);
		}
	}
	
	public int getLCNOptionStatus()
	{
	int returnStatus = 0;
		if (STUB_MODE) {
		} else {
			returnStatus = euInst.GetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeLCNOption);
			// 1: Default On
			// 0: Default Off
		}
		Log.d(TAG, "getLCNOptionStatus " + returnStatus);
		return returnStatus;
	}
	
		public void setLCNOptionStatus(int Status) {
		if (STUB_MODE) {

		} else {
			// 1: Scan On
			 //0: Scan Off
			euInst.SetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeLCNOption,
					Status);
		}
		Log.d(TAG, "setLCNOptionStatus " + Status);			
	}
	
	public int getDualAnalogPassStatus() {
		int returnStatus = 0;
		if (STUB_MODE) {
		} else {
			returnStatus = euInst.GetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDualAnalogPass);
			// 1: Default On
			// 0: Default Off
		}
		Log.d(TAG, "getDualAnalogPassStatus " + returnStatus);
		return returnStatus;
	}

	public void setDualAnalogPassStatus(int Status) {
		if (STUB_MODE) {

		} else {
			// 1: Scan On
			// 0: Scan Off
			euInst.SetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDualAnalogPass,
					Status);
		}
		Log.d(TAG, "setDualAnalogPassStatus " + Status);			
	}
	
	public void setWSSetFreeCAChannels(int isArgSCRorFTA) {
	    isFreeOrFreeScrambled = isArgSCRorFTA;
		if (STUB_MODE) {

		} else {
			// 1: SCR + FTA
			// 0: FTA only
			euInst.SetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeScrOrFTA,
					isArgSCRorFTA);
		}
		Log.d(TAG, "setWSSetFreeCAChannels " + isArgSCRorFTA);
	}

	public int getWSSetFreeCAChannels() {
		int ifSrcAndFTA = 0;
		if (STUB_MODE) {
		} else {
			// TODO MW API
			ifSrcAndFTA = euInst.GetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeScrOrFTA);
			
			// 1: SCR + FTA
			// 0: FTA only
			isFreeOrFreeScrambled = ifSrcAndFTA;
		}
		Log.d(TAG, "getWSSetFreeCAChannels " + ifSrcAndFTA);
		return ifSrcAndFTA;
	}

	public int getWSNetworkFrequencyMode() {
		if (STUB_MODE) {

		} else {
			// TODO MW API Calls
			if (euInstConst.IHsvInstallation2_AutomaticValue == euInst
					.GetAttributeMode(
							euInstConst.IHsvInstallation2_InstallationModeAutomatic,
							euInstConst.IHsvInstallation2_AttributeNetworkFreq)) {
				// Automatic
				networkFreqMode = 0;
			} else {
				// Manual
				networkFreqMode = 1;
			}
		}
		Log.d(TAG, "getWSNetworkFrequencyMode " + networkFreqMode);
		return networkFreqMode;
	}

	public void setWSNetworkFrequencyMode(int argNetworkFreqMode) {
		networkFreqMode = argNetworkFreqMode;

		if (STUB_MODE) {

		} else {
			// TODO MW API Calls
			if (networkFreqMode == 0) {
				// Automatic
				euInst.SetAttributeMode(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeNetworkFreq,
						euInstConst.IHsvInstallation2_AutomaticValue);
			} else {
				// Manual
				euInst.SetAttributeMode(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeNetworkFreq,
						euInstConst.IHsvInstallation2_ManualValue);
			}
		}
		Log.d(TAG, "setWSNetworkFrequencyMode " + argNetworkFreqMode);
	}

	public int getWSNetworkIdMode() {
		if (STUB_MODE) {

		} else {
			// TODO MW API Calls
			if (euInstConst.IHsvInstallation2_AutomaticValue == euInst
					.GetAttributeMode(
							euInstConst.IHsvInstallation2_InstallationModeAutomatic,
							euInstConst.IHsvInstallation2_AttributeNetworkId)) {
				// Automatic
				networkIDMode = 0;
			} else {
				// Manual
				networkIDMode = 1;
			}
		}
		return networkIDMode;
	}

	public void setWSNetworkIdMode(int argNetworkID) {
		networkIDMode = argNetworkID;

		if (STUB_MODE) {

		} else {
			// TODO MW API Calls
			if (networkIDMode == 0) {
				// Automatic
				euInst.SetAttributeMode(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeNetworkId,
						euInstConst.IHsvInstallation2_AutomaticValue);
			} else {
				// Manual
				euInst.SetAttributeMode(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeNetworkId,
						euInstConst.IHsvInstallation2_ManualValue);
			}
		}
	}

	public int getWSFreqStepSize() {
		if (STUB_MODE) {

		} else {
			// TODO MW API Calls
			if (euInstConst.IHsvInstallation2_DVBCStepSize1 == euInst
					.GetAttribute(
							euInstConst.IHsvInstallation2_InstallationModeAutomatic,
							euInstConst.IHsvInstallation2_AttributeFreqStepSize)) {
				// 1mhz
				frequencyStepSize = 0;
			} else {
				// 8mhz
				frequencyStepSize = 1;
			}
			Log.d(TAG, "getWSFreqStepSize " + frequencyStepSize);
		}
		return frequencyStepSize;
	}

	public void setWSFreqStepSize(int argFreqStepsize) {

		frequencyStepSize = argFreqStepsize;
		if (STUB_MODE) {

		} else {
			// TODO MW API Calls

			if (frequencyStepSize == 0) {
				// 1mhz
				euInst.SetAttribute(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeFreqStepSize,
						euInstConst.IHsvInstallation2_DVBCStepSize1);
				
			} else {
				// 8mhz
				euInst.SetAttribute(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeFreqStepSize,
						euInstConst.IHsvInstallation2_DVBCStepSize8);
			}
			
			Log.d(TAG,
					"setWSFreqStepSize "
							+ frequencyStepSize
							+ " : "
							+ euInst.GetAttribute(
									euInstConst.IHsvInstallation2_InstallationModeAutomatic,
									euInstConst.IHsvInstallation2_AttributeFreqStepSize));
		}
	}

	public int getWSFreqScanMode() {
		if (STUB_MODE) {

		} else {
			if (euInstConst.IHsvInstallation2_QuickScan == euInst.GetAttribute(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeScanMode)) {
				// quickscan
				frequencyScanMode = 0;
			} else {
				// fullscan
				frequencyScanMode = 1;
			}

		}
		return frequencyScanMode;
	}

	public void setWSFreqScanMode(int argFreqScanMode) {
		frequencyScanMode = argFreqScanMode;
		if (STUB_MODE) {

		} else {
			if (frequencyScanMode == 0) {
				// quickscan
				euInst.SetAttribute(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeScanMode,
						euInstConst.IHsvInstallation2_QuickScan);
			} else {
				// fullscan
				euInst.SetAttribute(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeScanMode,
						euInstConst.IHsvInstallation2_FullScan);
			}
		}
	}

	public void resetToPersistent() {
		Log.d(TAG, "resetToPersistent Enter");
		if (STUB_MODE) {
		} else {
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeSymbolRate);
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeScanMode);
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkId);
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkFreq);
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeModulation);
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeFreqStepSize);
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeScrOrFTA);
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkOperator);
			euInst.ResetAttributeToPersistent(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDTTScanOnAnalog);

			if (NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light == countrySupportsDVBCFullorLite(getCachedCountryName())) {
				euInst.ResetAttributeToPersistent(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeDigitalOption);
			}
		}
		
		Log.d(TAG, "resetToPersistent Exit");
	}
	
	/*
	 * function called to reset wizard settings
	 */

	public void resetWSToDefault() {
	    Log.d(TAG,"resetWSToDefault ");
		/*
			As per paul's mail the following attributes should not be reset
			Digital / Analog selection
			Network Operator
			Dual Analog Pass
		*/
		
		if (STUB_MODE) {
		    ifDigitalOn = true;
		} else {
			euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeSymbolRate);
			euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeScanMode);
			euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkId);
			euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkFreq);
			euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeModulation);
			euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeFreqStepSize);
			euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeScrOrFTA);
			/*[TF515PHIALLMTK01-14946]
			euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeNetworkOperator);
			*/
			/*
				DTT Scan on analog is re-enabled as per Paul's Mail.
			*/
			 euInst.ResetAttributeToDefault(
					euInstConst.IHsvInstallation2_InstallationModeAutomatic,
					euInstConst.IHsvInstallation2_AttributeDTTScanOnAnalog);

			if (NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light == countrySupportsDVBCFullorLite(getCachedCountryName())) {
				euInst.ResetAttributeToDefault(
						euInstConst.IHsvInstallation2_InstallationModeAutomatic,
						euInstConst.IHsvInstallation2_AttributeDigitalOption);
			}

			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSDVBTINSTALLATION, 0, 0);
			
	        // analog digital
	        /*[TF515PHIALLMTK01-14946]
	        analogOrDigital = getDigitalAnalogSelection(getCachedCountryName(),getCachedDVBTOrDVBC());*/
	        
	        // operator
	        operatorIndex = getOperatorIndexFromMW();
		}
	}
	
	/*** TVPROVIDER IMPLEMENTATION START ***/
	private String MapDecoderType (int DecoderType) {
		String 	Result;
		/* 	#define IHsvFrontEndApi_ChanDecDvbT		((Nat32)0x1 )
	#define IHsvFrontEndApi_ChanDecDvbC		((Nat32)0x2 )
	#define IHsvFrontEndApi_ChanDecDvbS		((Nat32)0x4 )
	#define IHsvFrontEndApi_ChanDecISDBT		((Nat32)0x8 )
	#define IHsvFrontEndApi_ChanDecDvbT2		((Nat32)0x10 )
*/
		switch (DecoderType) {
			case	0x01:
				Result = Channels.TYPE_DVB_T;
				break;
			case	0x02:
				Result = Channels.TYPE_DVB_C;
				break;
			case	0x10:
				Result = Channels.TYPE_DVB_T2;
				break;
			default:
				Result = Channels.TYPE_PAL;
				break;
		}
		
		return Result;
	}

	private int GetDecoderType (String DecoderType) {
		int	Result = 0;

		if(DecoderType.equalsIgnoreCase(Channels.TYPE_DVB_T)){
			Result = 0x01;
		}
		if(DecoderType.equalsIgnoreCase(Channels.TYPE_DVB_C)){
			Result = 0x02;
		}
		if(DecoderType.equalsIgnoreCase(Channels.TYPE_DVB_T2)){
			Result = 0x10;
		}
		if(DecoderType.equalsIgnoreCase(Channels.TYPE_PAL)){
			Result = 0x00;
		}

		//Log.d(TAG, "Decodertype " + Result);
		
		return Result;
	}

	
	private String MapServiceType (int DecoderType, int ServiceType) {
		String	MappedServiceType = Channels.SERVICE_TYPE_AUDIO_VIDEO;

		/* 	#define IHsvFrontEndApi_ChanDecDvbT		((Nat32)0x1 )
		#define IHsvFrontEndApi_ChanDecDvbC		((Nat32)0x2 )
		#define IHsvFrontEndApi_ChanDecDvbS		((Nat32)0x4 )
		#define IHsvFrontEndApi_ChanDecISDBT		((Nat32)0x8 )
		#define IHsvFrontEndApi_ChanDecDvbT2		((Nat32)0x10 )
		*/


		/* Service Type applies to only Digital channels. For analog make it default as audio_video */
		if ((DecoderType == 1) || (DecoderType == 0x02) || (DecoderType == 0x10))
		{
			switch(ServiceType) {
				case	IChannelContract.SERVICE_TYPE_TELEVISION:
				case	IChannelContract.SERVICE_TYPE_TELETEXT:
				case	IChannelContract.SERVICE_TYPE_MPEG2HD:
				case	IChannelContract.SERVICE_TYPE_ADVCODECHDTELEVISION:
				case	IChannelContract.SERVICE_TYPE_ADVCODECSDTELEVISION:
				case	IChannelContract.SERVICE_TYPE_3DHDDIGITAL:
				case	SERVICE_TYPE_HEVC:
					MappedServiceType = Channels.SERVICE_TYPE_AUDIO_VIDEO;
					break;
				case	IChannelContract.SERVICE_TYPE_RADIO:
				case	IChannelContract.SERVICE_TYPE_ADVCODEC_RADIO:
					MappedServiceType = Channels.SERVICE_TYPE_AUDIO;
					break;
				default:
					MappedServiceType = Channels.SERVICE_TYPE_OTHER;
			}
		}

		return MappedServiceType;
	}
		
	public void mUpdateDatabaseVersion(boolean ForceVersionUpdate) {
		/* Updating the cachedMajorVesrion here. Because for Semistandby & Background, InstallationExit method won't be called */
		int	CurrentVersion = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, 0); 
		if (ForceVersionUpdate) {
			CurrentVersion++;
			Log.d(TAG, "Forced major version update. New Version updated to DB is " + CurrentVersion);
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, CurrentVersion); 
			cachedMajorVesrion = CurrentVersion;
		}
		else {
			if (IsMajorVersionChange) {
				CurrentVersion++;
				Log.d(TAG, "Major version update. New Version updated to DB is " + CurrentVersion);
				mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, CurrentVersion); 
				cachedMajorVesrion = CurrentVersion;
			}
		}
	}

	public int setThemeDataToDB(int dispNum, int themeNum, int data) {

		Cursor cursor = null;
		String[] mProjection = {
					HtvContract.HtvChannelSetting._ID,
					HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER
				};

		try {
			cursor = ctx.getContentResolver().query(
				HtvContract.HtvChannelSetting.CONTENT_URI, mProjection, null, null, null, null);
			int rows_num = cursor.getCount();
			Log.d(TAG, "\nDispNum " + dispNum + ", RowNum " + rows_num + "\n");

			if (dispNum > rows_num) {
				Log.e(TAG, "\nError! Disp#" + dispNum  + ", DBRow#" + rows_num + "\n");
			} else {
				ContentValues tVal = new ContentValues();
				String themeUri = null;
				switch (themeNum) {
					case 1:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER;
						break;
					case 2:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER;
						break;
					case 3:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER;
						break;
					case 4:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER;
						break;
					case 5:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER;
						break;
					case 6:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER;
						break;
					case 7:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER;
						break;
					case 8:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER;
						break;
					case 9:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER;
						break;
					case 10:
						themeUri = HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER;
						break;
					default:
						Log.e(TAG, "\nError!, Theme# " + themeNum);
						break;
				}

				if (themeUri != null) {
					tVal.put(themeUri, data);
					ctx.getContentResolver().update(HtvContract.HtvChannelSetting.CONTENT_URI, tVal,
						new StringBuilder(HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER).append("=").append(dispNum).toString(), null);
				}
			}
		} catch (Exception e) {
			Log.d(TAG, "\nsetThemeData2DB: " + HtvContract.HtvChannelSetting.CONTENT_URI + "\n");
			Log.e(TAG, "\nsetThemeData2DB: (" + dispNum + "," + themeNum + "," + data + ")\n");
			e.printStackTrace();
		} finally {
			if (cursor != null)
				cursor.close();
			cursor = null;
		}

		return 0;
	}

	public class divideTask implements Runnable {
	
		divideTask(int a, int b, int c, int d) {
			RecordsInserted = a;
			NoOfRecords = b;
			InsertStep = c;
			index = d;
		}
		
		int RecordsInserted;
		int NoOfRecords;
		int InsertStep;
		int index;
		int bigestDisplayNumber=0;
		TcInstallerTvProviderData          TvpData;
		int 		ANTENNA_MEDIUM =0, CABLE_MEDIUM = 1;
		String[] mProjection ={ TvContract.Channels._ID,
   					TvContract.Channels.COLUMN_DISPLAY_NUMBER,
					TvContract.Channels.COLUMN_VERSION_NUMBER,
					TvContract.Channels.COLUMN_BROWSABLE,
					TvContract.Channels.COLUMN_DISPLAY_NAME					
					};
		public void run() {
			if( RecordsInserted < NoOfRecords) {
				int 	Version = 0; /*Version 0 for auto installation*/

				if((NoOfRecords-RecordsInserted) < InsertStep) {
					InsertStep = (NoOfRecords-RecordsInserted);
				}

				ContentValues []val=new ContentValues[InsertStep];                                                   
				for (int Loop = 0; Loop < InsertStep; Loop++) {
					val[Loop] = new ContentValues();
						
					TvpData = euInst.GetTvProviderBlobDataByIndex (index, DATA_ALL_TABLE);
					index++;
					//Log.d(TAG, "ONID" + TvpData.OriginalNetworkId + " TSID" + TvpData.Tsid + " ServiceID" + TvpData.ServiceId + " PresetNbr" + TvpData.PresetNumber + "DisplayName" + TvpData.ChannelName);
					//val[Loop].put (Channels.COLUMN_PACKAGE_NAME,"org.droidtv.euinstallertc"); /* TvProvider will fill this up */
					val[Loop].put (Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService"); /* Check with Mounesh/Pavan what to fill here */
					val[Loop].put (Channels.COLUMN_TYPE,MapDecoderType(TvpData.DecoderType));
					val[Loop].put (Channels.COLUMN_SERVICE_TYPE,MapServiceType(TvpData.DecoderType, TvpData.ServiceType));
					val[Loop].put (Channels.COLUMN_NETWORK_AFFILIATION , (TvpData.NewPreset == 1) ? "New" : "");
					val[Loop].put (Channels.COLUMN_ORIGINAL_NETWORK_ID,Integer.toString(TvpData.OriginalNetworkId));
					val[Loop].put (Channels.COLUMN_TRANSPORT_STREAM_ID,Integer.toString(TvpData.Tsid));
					val[Loop].put (Channels.COLUMN_SERVICE_ID,Integer.toString(TvpData.ServiceId));
					val[Loop].put (Channels.COLUMN_DISPLAY_NUMBER,Integer.toString(TvpData.PresetNumber));
					val[Loop].put (Channels.COLUMN_DISPLAY_NAME,TvpData.ChannelName);
					val[Loop].put (Channels.COLUMN_DESCRIPTION,((TvpData.ScrambledStatus== 1) ? "Scrambled" :"")); /* See if we can put medium information here */
					//val[Loop].put (Channels.COLUMN_BROWSABLE,Integer.toString(TvpData.VisibleService));
					val[Loop].put (Channels.COLUMN_BROWSABLE, ((TvpData.SystemHidden != 0) ? 0 : 1));
					val[Loop].put (Channels.COLUMN_SEARCHABLE,Integer.toString(TvpData.NumericSelect));
					val[Loop].put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,FormBlobData(TvpData,Version,false));
					val[Loop].put (Channels.COLUMN_LOCKED,0); /* Channel Lock is not to be set for Auto installation */
					if(PlayTvUtils.isPbsMode())
					{
						val[Loop].put (Channels.COLUMN_VERSION_NUMBER,((MapDecoderType(TvpData.DecoderType) == Channels.TYPE_DVB_C) ? CABLE_MEDIUM:ANTENNA_MEDIUM));
					} else {
						val[Loop].put (Channels.COLUMN_VERSION_NUMBER,((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) ? CABLE_MEDIUM:ANTENNA_MEDIUM));
					}
			
				}
				

				Log.d (TAG, "Going to do bulk insert ");
				Log.d (TAG, "Going to do bulk insert tunerservice");
				ctx.getContentResolver().bulkInsert(TvContract.Channels.CONTENT_URI ,val);
				Log.d (TAG, "finish bulk insert tunerservice");

				
				Log.d (TAG, "Insertion done for records " + InsertStep);

				RecordsInserted = (RecordsInserted + InsertStep);
				looperThread.mHandler.postDelayed(new divideTask(RecordsInserted,NoOfRecords,InsertStep,index),200);
			}
			else {
				int number = addExtSourceToTvProvider(getBiggestDisplayNumber());
				addMediaChannelToTvProvider(number);
				
				SyncHTvProvider();
				PopulateTvContentProvider();
				mUpdateDatabaseVersion(true);
				registerTvProviderContentObservers();
                sync_IDToMW ();
				ntf.notifyAllObservers(EventIDs.EVENT_COMMIT_FINISHED,"");
			}
		}
	}
	
	private byte[] FormBlobData (TcInstallerTvProviderData TvpData, int Version, boolean Update) {

		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		byte[]	BlobData = null;

		
		if(Update == true){
			
			/*Get Data from Tvprovider*/
			String[] projection = new String[] {Channels.COLUMN_INTERNAL_PROVIDER_DATA};
			String	mselection=Channels._ID +"= ?";
			String[]	mselectionargs=new String[]{String.valueOf(TvpData.UniqueId)};
			
			Cursor TCCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
			if((TCCursor != null) && (TCCursor.moveToNext())){
				BlobData = TCCursor.getBlob(0);
				
				try{
					keyvalues.setBlob(BlobData);
					
					keyvalues.put (ITvContractExtras.C_PRESETPTC,TvpData.Ptc);
					keyvalues.put (ITvContractExtras.C_PLPID,TvpData.StreamPriority);
					keyvalues.put (ITvContractExtras.C_FREQUENCY,TvpData.Frequency);
					keyvalues.put (ITvContractExtras.C_BANDWIDTH,TvpData.Bandwidth);
					keyvalues.put (ITvContractExtras.C_SYMBOLRATE,TvpData.SymbolRate);
					keyvalues.put (ITvContractExtras.C_MODULATION,TvpData.ModulationType);
					keyvalues.put (ITvContractExtras.C_STREAMPRIORITY,TvpData.StreamPriority);
					keyvalues.put (ITvContractExtras.C_NUMERICSELECT,TvpData.NumericSelect);
					keyvalues.put (ITvContractExtras.C_SCRAMBLED,TvpData.ScrambledStatus);
					keyvalues.put (ITvContractExtras.C_USERHIDDEN,TvpData.UserHidden);
					keyvalues.put (ITvContractExtras.C_NEWPRESET,TvpData.NewPreset);
					keyvalues.put (ITvContractExtras.C_CNINETWORK_ID,TvpData.CniNi);
					keyvalues.put (ITvContractExtras.C_SERVICEIDENTIFIER,TvpData.ServiceId);
					keyvalues.put (ITvContractExtras.C_NetworkId,TvpData.NetworkId);
					//keyvalues.put (ITvContractExtras.C_SAP,TvpData.SAP);
					keyvalues.put (ITvContractExtras.C_PreferredStereo,TvpData.PreferredStereo);
					keyvalues.put (ITvContractExtras.C_LCN,TvpData.LCN);
					
					keyvalues.put (ITvContractExtras.C_FREECIMODE,TvpData.FreeCiMode);
					keyvalues.put (ITvContractExtras.C_LOGOID,TvpData.LogoURL);
					
					keyvalues.put (ITvContractExtras.C_INSTALLER_BLOB,FormPrivateBlobData (TvpData, Version));
					
					/* Newly added for CR AN-81115. Putting try catch to ensure no exception seen while upgrading */
					keyvalues.put (ITvContractExtras.C_HDLCN,TvpData.LowPrioLCN);

					keyvalues.put (ITvContractExtras.C_USEROVERRULEDCHANNELNAME,TvpData.UserModifiedName);
					
					
					BlobData = keyvalues.getBlob();
				}
				catch (Exception e) {
					Log.d(TAG, "Exception in FormBlobData() " + e);
				}
				finally {
					TCCursor.close ();
					TCCursor = null;
				}			
			}
			else{
				Update = false;
			}
			
			if(TCCursor != null) {
				TCCursor.close();
				TCCursor = null;
			}
		}
			
		if(Update == false)
		{
			keyvalues.put (ITvContractExtras.C_PRESETPTC,TvpData.Ptc);
			keyvalues.put (ITvContractExtras.C_PLPID,TvpData.StreamPriority);
			keyvalues.put (ITvContractExtras.C_FREQUENCY,TvpData.Frequency);
			keyvalues.put (ITvContractExtras.C_BANDWIDTH,TvpData.Bandwidth);
			keyvalues.put (ITvContractExtras.C_SYMBOLRATE,TvpData.SymbolRate);
			keyvalues.put (ITvContractExtras.C_MODULATION,TvpData.ModulationType);
			keyvalues.put (ITvContractExtras.C_STREAMPRIORITY,TvpData.StreamPriority);
			keyvalues.put (ITvContractExtras.C_NUMERICSELECT,TvpData.NumericSelect);
			keyvalues.put (ITvContractExtras.C_SCRAMBLED,TvpData.ScrambledStatus);
			keyvalues.put (ITvContractExtras.C_HBBTVON,TvpData.IntHbbTvOption);
			keyvalues.put (ITvContractExtras.C_USERHIDDEN,TvpData.UserHidden);
			keyvalues.put (ITvContractExtras.C_NEWPRESET,TvpData.NewPreset);
			keyvalues.put (ITvContractExtras.C_CNINETWORK_ID,TvpData.CniNi);
			keyvalues.put (ITvContractExtras.C_AUDIOPID,TvpData.AudioPid);
			keyvalues.put (ITvContractExtras.C_VIDEOPID,TvpData.VideoPid);
			keyvalues.put (ITvContractExtras.C_PCRPID,TvpData.PcrPid);
			keyvalues.put (ITvContractExtras.C_VIDEOSTREAMTYPE,TvpData.VideoStreamType);
			keyvalues.put (ITvContractExtras.C_AUDIOSTREAMTYPE,TvpData.AudioStreamType);
			keyvalues.put (ITvContractExtras.C_TXTPAGES,TvpData.TxtPages);
			keyvalues.put (ITvContractExtras.C_SERVICEIDENTIFIER,TvpData.ServiceId);
			keyvalues.put (ITvContractExtras.C_NetworkId,TvpData.NetworkId);
			keyvalues.put (ITvContractExtras.C_TXTSUBPAGE,TvpData.TextSubTitlePage);
			keyvalues.put (ITvContractExtras.C_SAP,TvpData.SAP);
			keyvalues.put (ITvContractExtras.C_PreferredStereo,TvpData.PreferredStereo);
			keyvalues.put (ITvContractExtras.C_LCN,TvpData.LCN);
			keyvalues.put (ITvContractExtras.C_USEROVERRULEDLOGOURI,TvpData.UserModifiedLogo);

			keyvalues.put (ITvContractExtras.C_PMTPID,TvpData.PmtPid);
			keyvalues.put (ITvContractExtras.C_SECONDARY_AUDIOPID,TvpData.SecAudioPid);
			keyvalues.put (ITvContractExtras.C_SECONDARY_AUDIOSTREAMTYPE,TvpData.SecAudioStreamType);
			keyvalues.put (ITvContractExtras.C_DATETIMESTAMP,TvpData.DateStamp);
			keyvalues.put (ITvContractExtras.C_FREECIMODE,TvpData.FreeCiMode);
			keyvalues.put (ITvContractExtras.C_MATCH_BRANDID,TvpData.MatchBrandFlag);
			keyvalues.put (ITvContractExtras.C_BRANDIDS,TvpData.BrandIds);
			keyvalues.put (ITvContractExtras.C_LOGOID,TvpData.LogoURL);

			

			keyvalues.put (ITvContractExtras.C_INSTALLER_BLOB,FormPrivateBlobData (TvpData, Version));

			try {
				/* Newly added for CR AN-81115. Putting try catch to ensure no exception seen while upgrading */
				keyvalues.put (ITvContractExtras.C_HDLCN,TvpData.LowPrioLCN);
			} catch (Exception e) {
				Log.e(TAG, "Error blobput	" + e);
			}
			
			
			try {
				BlobData = keyvalues.getBlob();
			} catch (Exception e) {
				Log.e(TAG, "Error FormBlobData	" + e);
			}
		}
		return BlobData;


	}

	private byte[] FormPrivateBlobData (TcInstallerTvProviderData TvpData, int Version) {

		byte[]	BlobData = null;
		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();
		
		privatekeyvalues.put (TvContractPrivate.C_SIGNAL_STRENGTH,TvpData.SignalStrength);
		privatekeyvalues.put (TvContractPrivate.C_SIGNAL_QUALITY,TvpData.SignalQuality);
		privatekeyvalues.put (TvContractPrivate.C_SDT_VERSION,TvpData.SDTVersion);
		privatekeyvalues.put (TvContractPrivate.C_NIT_VERSION,TvpData.NITVersion);

		privatekeyvalues.put (TvContractPrivate.C_DELTAVOLUME,TvpData.DeltaVolume);
		privatekeyvalues.put (TvContractPrivate.C_LOWPRIO_LCN,TvpData.LowPrioLCN);
		privatekeyvalues.put (TvContractPrivate.C_LOWPRIO_VISIBLESERVICE,TvpData.LowPrioVisibleService);
		privatekeyvalues.put (TvContractPrivate.C_VIDEODESCPRESENT,TvpData.VideoDescPresent);
		privatekeyvalues.put (TvContractPrivate.C_VISIBLESERVICE,TvpData.VisibleService);
		privatekeyvalues.put (TvContractPrivate.C_OUI,TvpData.OUI);
		privatekeyvalues.put (TvContractPrivate.C_SERVICELIST_VERSION,TvpData.ServiceListVersion);
		privatekeyvalues.put (TvContractPrivate.C_USER_INSTALLED,TvpData.UserInstalled);
		privatekeyvalues.put (TvContractPrivate.C_PREFERRED_NICAM,TvpData.PreferredNicam);
		privatekeyvalues.put (TvContractPrivate.C_NUM_BRAND_IDS,TvpData.NumBrandIds);
		privatekeyvalues.put (TvContractPrivate.C_SCRAMBLED_STATUS,TvpData.ScrambledStatus);
		privatekeyvalues.put (TvContractPrivate.C_REGION_DEPTH,TvpData.RegionDepth);
		privatekeyvalues.put (TvContractPrivate.C_PRIMARY_REGION,TvpData.PrimaryRegion);
		privatekeyvalues.put (TvContractPrivate.C_SECONDARY_REGION,TvpData.SecondaryRegion);
		privatekeyvalues.put (TvContractPrivate.C_TERTIARY_REGION,TvpData.TertiaryRegion);
		privatekeyvalues.put (TvContractPrivate.C_COUNTRY_CODE,TvpData.CountryCode);
		privatekeyvalues.put (TvContractPrivate.C_HDSIMULCASTREP_ONID,TvpData.HDSimulcastRepOnId);
		privatekeyvalues.put (TvContractPrivate.C_HDSIMULCASTREP_TSID,TvpData.HDSimulcastRepTsId);
		privatekeyvalues.put (TvContractPrivate.C_HDSIMULCASTREP_SVCID,TvpData.HDSimulcastRepSvcId);
		privatekeyvalues.put (TvContractPrivate.C_FAVOURITENUMBER,TvpData.FavoriteNumber);
		privatekeyvalues.put (TvContractPrivate.C_MULTIPLE_LCN,TvpData.MultipleLCN);
		privatekeyvalues.put (TvContractPrivate.C_MULTIPLE_PRESET,TvpData.MultiplePreset);
		privatekeyvalues.put (TvContractPrivate.C_MULTIPLE_FAVOURITE_ID,TvpData.MultipleFavorite);
		
		privatekeyvalues.put (TvContractPrivate.C_FUNETUNE_FREQUENCY,TvpData.FineTuneFrequency);
		privatekeyvalues.put (TvContractPrivate.C_FINETUNE_OFFSET,TvpData.FineTuneOffset);
		privatekeyvalues.put (TvContractPrivate.C_COLOUR_SYSTEM,TvpData.ColourSystem);
		privatekeyvalues.put (TvContractPrivate.C_DATA_INDICATOR,TvpData.DataIndicator);
		privatekeyvalues.put (TvContractPrivate.C_ATTENUATOR,TvpData.Attenuator);
		privatekeyvalues.put (TvContractPrivate.C_TUNED,TvpData.Tuned);
		privatekeyvalues.put (TvContractPrivate.C_DETUNED,TvpData.DeTuned);
		privatekeyvalues.put (TvContractPrivate.C_AGC_INSTALLAED,TvpData.AgcInstalled);
		privatekeyvalues.put (TvContractPrivate.C_PREFERRED_FAVORITE,TvpData.PreferredFavorite);

		
		privatekeyvalues.put (TvContractPrivate.C_A_SIGNAL_STRENGTH,TvpData.ASignalStrength);
		privatekeyvalues.put (TvContractPrivate.C_V_SIGNAL_STRENGTH,TvpData.VSignalStrength);
		privatekeyvalues.put (TvContractPrivate.C_Q_SIGNAL_STRENGTH,TvpData.QSignalStrength);
		privatekeyvalues.put (TvContractPrivate.C_CDSD_FREQUENCY,TvpData.CDSDFrequency);
		privatekeyvalues.put (TvContractPrivate.C_CODERATE,TvpData.CodeRate);
		privatekeyvalues.put (TvContractPrivate.C_HIERARCHYMODE,TvpData.HierarchyMode);
		privatekeyvalues.put (TvContractPrivate.C_GUARDINTERVAL,TvpData.GuardInterval);
		privatekeyvalues.put (TvContractPrivate.C_PTC_LIST_VERSION,TvpData.PtcListVersion);
		privatekeyvalues.put (TvContractPrivate.C_TS_VERSION,TvpData.TSVersion);
		privatekeyvalues.put (TvContractPrivate.C_BARKER_MUX,TvpData.BarkerMux);
		Log.d(TAG, "FormPrivateBlobData() ANALOG_TABLE_PRESET: " + TvpData.AnalogTablePreset);
		privatekeyvalues.put (TvContractPrivate.C_ANALOG_TABLE_PRESET,TvpData.AnalogTablePreset);
		privatekeyvalues.put (TvContractPrivate.C_TYPE,TvpData.Type);
		privatekeyvalues.put (TvContractPrivate.C_SERVICETYPE,TvpData.ServiceType); 	
		
		privatekeyvalues.put (TvContractPrivate.C_VERSION,Version);
		privatekeyvalues.put (TvContractPrivate.C_LANG_CODE,TvpData.LanguageCode);

		try {
			BlobData = privatekeyvalues.getBlob();
		} catch (Exception e) {
			Log.e(TAG, "Error FormPrivateBlobData  " + e);
		}
		return BlobData;
	}

	public void PopulateTvContentProvider(){

		Log.d(TAG, "PopulateTvContentProvider");

		int           NoOfRecords = 0, Loop = 0, RecordsInserted = 0, InsertStep = 100, index = 0;
		TcInstallerTvProviderData TvpData;

		/* Clear existing database */
		String	mselection = null;
		String[]	mselectionargs = null;
		int RowsDeleted = ctx.getContentResolver().delete(IFrequencyListContract.ITCFrequencyMap.CONTENT_URI,mselection,mselectionargs);

		Log.d(TAG,"PopulateTvContentProvider: RowsDeleted "+RowsDeleted);
		
		NoOfRecords = euInst.GetNumberOfDatabaseRecords(DATA_TS_TABLE);
		

		for(RecordsInserted = 0; RecordsInserted < NoOfRecords; RecordsInserted = (RecordsInserted + InsertStep)){

			if((NoOfRecords-RecordsInserted) < InsertStep) {
				InsertStep = (NoOfRecords-RecordsInserted);
			}
			
			ContentValues []val=new ContentValues[InsertStep];													 
			
			for (Loop = 0; Loop < InsertStep; Loop++) {
				TvpData = euInst.GetTvProviderBlobDataByIndex (index,DATA_TS_TABLE);
				index++;
				
				val[Loop] = new ContentValues();
			
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_FREQUENCY,TvpData.Frequency); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_SYMBOLRATE,TvpData.SymbolRate); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_ORIGINALNETWORKID,TvpData.OriginalNetworkId); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_TSID,TvpData.Tsid); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_MODULATIONTYPE,TvpData.ModulationType); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_BANDWIDTH,TvpData.Bandwidth); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_BARKERMUX,TvpData.BarkerMux); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_PACKAGE_MUX,0); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_GUARDINTERVAL,TvpData.GuardInterval); 
				val[Loop].put (IFrequencyListContract.ITCFrequencyMap.COLUMN_DECODERTYPE,TvpData.DecoderType); 
			
			}
			Log.d (TAG, "Going to do bulk insert of TCFrequencyMap ");
			ctx.getContentResolver().bulkInsert(IFrequencyListContract.ITCFrequencyMap.CONTENT_URI ,val);
			Log.d (TAG, "Insertion done for records " + InsertStep);
		}
		
	}    

	public void LoadTvProviderData(){

		Log.d(TAG, "LoadTvProviderData");
		TcInstallerTvProviderData TvpData = new TcInstallerTvProviderData();
		TcInstallerTvProviderData Temp = new TcInstallerTvProviderData();	
		String NewPreset;
		byte[]	BlobData = null;
		int			ANTENNA_MEDIUM =0, CABLE_MEDIUM = 1, count = 0;
		int CurrentMedium = ((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) ? CABLE_MEDIUM:ANTENNA_MEDIUM);

		/*Get Dat from Tvprovider*/
		String[] projection = new String[] {Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_TYPE, Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_DISPLAY_NUMBER, Channels.COLUMN_DISPLAY_NAME, Channels.COLUMN_SEARCHABLE, Channels.COLUMN_INTERNAL_PROVIDER_DATA, Channels.COLUMN_VERSION_NUMBER, Channels._ID, Channels.COLUMN_NETWORK_AFFILIATION};
		String	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?";
		String[]	mselectionargs=new String[]{String.valueOf(CurrentMedium)};
		boolean fbIsPbsMode = PlayTvUtils.isPbsMode();

		if (fbIsPbsMode)
		{
			mselection=Channels.COLUMN_VERSION_NUMBER+"<= ?";
			mselectionargs=new String[]{String.valueOf(CABLE_MEDIUM)}; // HTV quecy ANTENNA_MEDIUM and CABLE_MEDIUM at the same time.
			clearHTVChNameUpdateWaitList();
		}
		
		Cursor TCCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		if(TCCursor != null){
			count = TCCursor.getCount();
		}
		Log.d(TAG, "LoadTvProviderData: Number of channles in db" + count);	

		/*Clear the RAM copy in MW*/
		euInst.PopulateMW(Temp,1);
		if(TCCursor != null){
			try{
			while(TCCursor.moveToNext()) { 
				//Log.d(TAG, "Adding Data to MW");
				TvpData.DecoderType = GetDecoderType(TCCursor.getString(0));
				TvpData.OriginalNetworkId= TCCursor.getInt(2);
				TvpData.Tsid= TCCursor.getInt(3);
				TvpData.ServiceId= TCCursor.getInt(4);
				TvpData.PresetNumber= TCCursor.getInt(5);
				TvpData.ChannelName= TCCursor.getString(6);
				TvpData.NumericSelect = TCCursor.getInt(7);
				BlobData = TCCursor.getBlob(8);
				TvpData.UniqueId = TCCursor.getInt(10);
				NewPreset = TCCursor.getString(11);
				try {
					
					if (fbIsPbsMode && (HTV_DI_CHANNEL_UPDATE_FLAG.equals(NewPreset) || HTV_DT_CHANNEL_UPDATE_FLAG.equals(NewPreset)))
						addHTVChNameUpdateRequest((long)TvpData.UniqueId);
					
					TvpData.NewPreset = (NewPreset.equalsIgnoreCase("New") ? 1 : 0);					
				}
				catch (Exception e)
				{
				}
				AddMWRecord(TvpData,BlobData);
			}
			}finally{
			   TCCursor.close();
			   TCCursor=null;
			}
		}
		Log.d(TAG, "LoadTvProviderData: DB Population completed");	
	}

	public void LoadFreqMapDataData(){

		TcInstallerTvProviderData TvpData = new TcInstallerTvProviderData();
		int count = 0;
		
		String[] projection = new String[] {IFrequencyListContract.ITCFrequencyMap.COLUMN_FREQUENCY,IFrequencyListContract.ITCFrequencyMap.COLUMN_SYMBOLRATE,
			IFrequencyListContract.ITCFrequencyMap.COLUMN_ORIGINALNETWORKID,IFrequencyListContract.ITCFrequencyMap.COLUMN_TSID,
			IFrequencyListContract.ITCFrequencyMap.COLUMN_MODULATIONTYPE,IFrequencyListContract.ITCFrequencyMap.COLUMN_BANDWIDTH,
			IFrequencyListContract.ITCFrequencyMap.COLUMN_BARKERMUX,IFrequencyListContract.ITCFrequencyMap.COLUMN_PACKAGE_MUX,
			IFrequencyListContract.ITCFrequencyMap.COLUMN_GUARDINTERVAL,IFrequencyListContract.ITCFrequencyMap.COLUMN_DECODERTYPE};
		String	mselection= null;
		String[]	mselectionargs= null;
		
		Cursor TCCursor = ctx.getContentResolver().query(IFrequencyListContract.ITCFrequencyMap.CONTENT_URI, projection, mselection, mselectionargs, null);
		if(TCCursor != null){
			count = TCCursor.getCount();
		}
		Log.d(TAG, "LoadFreqMapDataData: Number of FreqMapTables in db" + count);	

		if(TCCursor != null){
			try{
			while(TCCursor.moveToNext()) { 
				//Log.d(TAG, "Adding FreqMap Data to MW");
				TvpData.Frequency = TCCursor.getInt(0);
				TvpData.SymbolRate= TCCursor.getInt(1);
				TvpData.OriginalNetworkId= TCCursor.getInt(2);
				TvpData.Tsid= TCCursor.getInt(3);
				TvpData.ModulationType= TCCursor.getInt(4);
				TvpData.Bandwidth= TCCursor.getInt(5);
				TvpData.BarkerMux= TCCursor.getInt(7);
				TvpData.GuardInterval= TCCursor.getInt(8);
				TvpData.DecoderType= TCCursor.getInt(9);
				/*TvpData.ServiceId (filled with 0 for Freq. Map Table) is used to identigy the FreqMaptable in MW*/
				TvpData.ServiceId	= 0;
				TvpData.Type = 3; /* This is needed to filter analog population and Freq Map population */
				euInst.PopulateMW(TvpData,0);
			}	
			}finally{
			  TCCursor.close();
			  TCCursor=null;
			}
		}
		Log.d(TAG, "LoadFreqMapDataData: Complete ");	
		
	}


	public void AddMWRecord(TcInstallerTvProviderData TvpData,byte[] BlobData)
	{
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();
		byte[]	privateBlobData = null;
		
		try{
			keyvalues.setBlob(BlobData);
		}
		catch (Exception e) {
			Log.d(TAG, "Exception in setBlob() in AddMWRecord" + e);
		}			


		TvpData.Ptc = keyvalues.getInt (ITvContractExtras.C_PRESETPTC);
		TvpData.Frequency = keyvalues.getInt (ITvContractExtras.C_FREQUENCY);
		TvpData.Bandwidth = keyvalues.getInt (ITvContractExtras.C_BANDWIDTH);
		TvpData.SymbolRate = keyvalues.getInt (ITvContractExtras.C_SYMBOLRATE);
		TvpData.ModulationType = keyvalues.getInt (ITvContractExtras.C_MODULATION);
		TvpData.StreamPriority = keyvalues.getInt (ITvContractExtras.C_STREAMPRIORITY);
		TvpData.NumericSelect = keyvalues.getInt (ITvContractExtras.C_NUMERICSELECT);
		TvpData.ScrambledStatus = keyvalues.getInt (ITvContractExtras.C_SCRAMBLED);
		TvpData.IntHbbTvOption = keyvalues.getInt (ITvContractExtras.C_HBBTVON);
		TvpData.UserHidden = keyvalues.getInt (ITvContractExtras.C_USERHIDDEN);
		//TvpData.NewPreset = keyvalues.getInt (ITvContractExtras.C_NEWPRESET);
		TvpData.CniNi = keyvalues.getInt (ITvContractExtras.C_CNINETWORK_ID);
		TvpData.AudioPid = keyvalues.getInt (ITvContractExtras.C_AUDIOPID);
		TvpData.VideoPid = keyvalues.getInt (ITvContractExtras.C_VIDEOPID);
		TvpData.PcrPid = keyvalues.getInt (ITvContractExtras.C_PCRPID);
		TvpData.VideoStreamType = keyvalues.getInt (ITvContractExtras.C_VIDEOSTREAMTYPE);
		TvpData.AudioStreamType = keyvalues.getInt (ITvContractExtras.C_AUDIOSTREAMTYPE);
		TvpData.TxtPages = keyvalues.getString (ITvContractExtras.C_TXTPAGES);
		TvpData.ServiceId = keyvalues.getInt (ITvContractExtras.C_SERVICEIDENTIFIER);
		TvpData.NetworkId = keyvalues.getInt (ITvContractExtras.C_NetworkId);
		TvpData.TextSubTitlePage = keyvalues.getInt (ITvContractExtras.C_TXTSUBPAGE);
		TvpData.SAP = keyvalues.getInt (ITvContractExtras.C_SAP);
		TvpData.PreferredStereo = keyvalues.getInt (ITvContractExtras.C_PreferredStereo);
		TvpData.LCN = keyvalues.getInt (ITvContractExtras.C_LCN);
		TvpData.UserModifiedLogo= keyvalues.getInt (ITvContractExtras.C_USEROVERRULEDLOGOURI);

		TvpData.PmtPid = keyvalues.getInt (ITvContractExtras.C_PMTPID);
		TvpData.SecAudioPid = keyvalues.getInt (ITvContractExtras.C_SECONDARY_AUDIOPID);
		TvpData.SecAudioStreamType = keyvalues.getInt (ITvContractExtras.C_SECONDARY_AUDIOSTREAMTYPE);
		TvpData.DateStamp = keyvalues.getInt (ITvContractExtras.C_DATETIMESTAMP);
		TvpData.FreeCiMode = keyvalues.getInt (ITvContractExtras.C_FREECIMODE); 	
		TvpData.MatchBrandFlag = keyvalues.getInt (ITvContractExtras.C_MATCH_BRANDID);
		TvpData.BrandIds = keyvalues.getIntArray (ITvContractExtras.C_BRANDIDS);
		TvpData.LogoURL = keyvalues.getInt(ITvContractExtras.C_LOGOID);

		TvpData.UserModifiedName = keyvalues.getInt (ITvContractExtras.C_USEROVERRULEDCHANNELNAME);


		/*Get Private data*/

		privateBlobData = keyvalues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);

		try{
			privatekeyvalues.setBlob(privateBlobData);
		}
		catch (Exception e) {
			Log.d(TAG, "Exception in setBlob() in AddMWRecord for Private Data" + e);
		}			

		TvpData.SignalStrength = privatekeyvalues.getInt(TvContractPrivate.C_SIGNAL_STRENGTH);
		TvpData.SignalQuality = privatekeyvalues.getInt (TvContractPrivate.C_SIGNAL_QUALITY);
		TvpData.SDTVersion = privatekeyvalues.getInt (TvContractPrivate.C_SDT_VERSION);
		TvpData.NITVersion = privatekeyvalues.getInt (TvContractPrivate.C_NIT_VERSION);
		TvpData.DeltaVolume = privatekeyvalues.getInt (TvContractPrivate.C_DELTAVOLUME);
		TvpData.LowPrioLCN = privatekeyvalues.getInt (TvContractPrivate.C_LOWPRIO_LCN);
		TvpData.LowPrioVisibleService = privatekeyvalues.getInt (TvContractPrivate.C_LOWPRIO_VISIBLESERVICE);
		TvpData.VideoDescPresent = privatekeyvalues.getInt (TvContractPrivate.C_VIDEODESCPRESENT);
		TvpData.VisibleService = privatekeyvalues.getInt (TvContractPrivate.C_VISIBLESERVICE);
		TvpData.OUI = privatekeyvalues.getInt (TvContractPrivate.C_OUI);
		TvpData.ServiceListVersion = privatekeyvalues.getInt (TvContractPrivate.C_SERVICELIST_VERSION);
		TvpData.UserInstalled = privatekeyvalues.getInt (TvContractPrivate.C_USER_INSTALLED);
		
		TvpData.PreferredNicam = privatekeyvalues.getInt (TvContractPrivate.C_PREFERRED_NICAM);

		TvpData.NumBrandIds = privatekeyvalues.getInt (TvContractPrivate.C_NUM_BRAND_IDS);

		TvpData.ScrambledStatus = privatekeyvalues.getInt (TvContractPrivate.C_SCRAMBLED_STATUS);
		TvpData.RegionDepth = privatekeyvalues.getInt (TvContractPrivate.C_REGION_DEPTH);
		TvpData.PrimaryRegion = privatekeyvalues.getInt (TvContractPrivate.C_PRIMARY_REGION);
		TvpData.SecondaryRegion = privatekeyvalues.getInt (TvContractPrivate.C_SECONDARY_REGION);
		TvpData.TertiaryRegion = privatekeyvalues.getInt (TvContractPrivate.C_TERTIARY_REGION);
		TvpData.CountryCode = privatekeyvalues.getInt (TvContractPrivate.C_COUNTRY_CODE);
		TvpData.HDSimulcastRepOnId = privatekeyvalues.getInt (TvContractPrivate.C_HDSIMULCASTREP_ONID);
		TvpData.HDSimulcastRepTsId = privatekeyvalues.getInt (TvContractPrivate.C_HDSIMULCASTREP_TSID);
		TvpData.HDSimulcastRepSvcId = privatekeyvalues.getInt (TvContractPrivate.C_HDSIMULCASTREP_SVCID);
		TvpData.FavoriteNumber = privatekeyvalues.getInt (TvContractPrivate.C_FAVOURITENUMBER);
		
		TvpData.MultipleLCN = privatekeyvalues.getIntArray (TvContractPrivate.C_MULTIPLE_LCN);
		TvpData.MultiplePreset = privatekeyvalues.getIntArray (TvContractPrivate.C_MULTIPLE_PRESET);
		TvpData.MultipleFavorite = privatekeyvalues.getIntArray (TvContractPrivate.C_MULTIPLE_FAVOURITE_ID);
		
		TvpData.FineTuneFrequency = privatekeyvalues.getInt (TvContractPrivate.C_FUNETUNE_FREQUENCY);
		TvpData.FineTuneOffset = privatekeyvalues.getInt (TvContractPrivate.C_FINETUNE_OFFSET);
		TvpData.ColourSystem = privatekeyvalues.getInt (TvContractPrivate.C_COLOUR_SYSTEM);
		TvpData.DataIndicator = privatekeyvalues.getInt (TvContractPrivate.C_DATA_INDICATOR);
		TvpData.Attenuator = privatekeyvalues.getInt (TvContractPrivate.C_ATTENUATOR);
		TvpData.Tuned = privatekeyvalues.getInt (TvContractPrivate.C_TUNED);
		TvpData.DeTuned = privatekeyvalues.getInt (TvContractPrivate.C_DETUNED);
		TvpData.AgcInstalled = privatekeyvalues.getInt (TvContractPrivate.C_AGC_INSTALLAED);
		TvpData.PreferredFavorite = privatekeyvalues.getInt (TvContractPrivate.C_PREFERRED_FAVORITE);

		
		TvpData.ASignalStrength = privatekeyvalues.getInt (TvContractPrivate.C_A_SIGNAL_STRENGTH);
		TvpData.VSignalStrength = privatekeyvalues.getInt (TvContractPrivate.C_V_SIGNAL_STRENGTH);
		TvpData.QSignalStrength = privatekeyvalues.getInt (TvContractPrivate.C_Q_SIGNAL_STRENGTH);
		TvpData.CDSDFrequency = privatekeyvalues.getInt (TvContractPrivate.C_CDSD_FREQUENCY);
		TvpData.CodeRate = privatekeyvalues.getInt (TvContractPrivate.C_CODERATE);
		TvpData.HierarchyMode = privatekeyvalues.getInt (TvContractPrivate.C_HIERARCHYMODE);
		TvpData.GuardInterval = privatekeyvalues.getInt (TvContractPrivate.C_GUARDINTERVAL);
		TvpData.PtcListVersion = privatekeyvalues.getInt (TvContractPrivate.C_PTC_LIST_VERSION);
		TvpData.TSVersion = privatekeyvalues.getInt (TvContractPrivate.C_TS_VERSION);
		TvpData.BarkerMux = privatekeyvalues.getInt (TvContractPrivate.C_BARKER_MUX);
		
		TvpData.AnalogTablePreset = privatekeyvalues.getInt (TvContractPrivate.C_ANALOG_TABLE_PRESET);
		TvpData.Type = privatekeyvalues.getInt (TvContractPrivate.C_TYPE);

		TvpData.ServiceType= privatekeyvalues.getInt (TvContractPrivate.C_SERVICETYPE);
		TvpData.LanguageCode = privatekeyvalues.getInt (TvContractPrivate.C_LANG_CODE);

		euInst.PopulateMW(TvpData,0);
	}

	
	public void mPopulateTvProvider() {

		Log.d(TAG, "PopulateTVProvider ");
		int           NoOfRecords = 0, RecordsInserted = 0, InsertStep = 200, index = 0;
	
		NoOfRecords = euInst.GetNumberOfDatabaseRecords (DATA_ALL_TABLE);
		if (NoOfRecords != 0 || PlayTvUtils.isPbsMode())
		{
			looperThread.mHandler.post(new divideTask(RecordsInserted,NoOfRecords,InsertStep,index));
		}
		else 
			{
				registerTvProviderContentObservers();
				ntf.notifyAllObservers(EventIDs.EVENT_COMMIT_FINISHED,"");	
			}

		Log.d (TAG, "Number of entries "+NoOfRecords);
	}

	private void resetChannelList(){
		
		if ( mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE ,0,0) == TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON ){
			ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI , null, null);
			Log.d(TAG,"HTV mode - Reset tv.db all channels");
		}else{
			Log.d(TAG,"EU  mode - Don't need to reset tv.db all channels");
		}
	}
	
	private class LooperThread extends Thread {
		public Handler mHandler;
		boolean handlerCreated = false;
		public void run() {
			Log.d(TAG,"Looper thread creation");
			synchronized (this)
			{
				Looper.prepare();
				mHandler = new Handler() ;
				handlerCreated = true;
				Log.d(TAG,"notifying... after handler creation");
				notify();

			}
			Looper.loop();
		}

		public boolean getLooperThreadHandlerStatus()
		{
			return handlerCreated;
		}
	};	
	
	public void commitDatabaseToTvProvider(boolean isAutoInstall) {
		int 	RowsDeleted = 0;
		int		ANTENNA_MEDIUM=0, CABLE_MEDIUM=1, EXTERNAL_SOURCE=10, IP_CHANNEL=11, MEDIA_CHANNEL=12;
		int channelCount = 0;
		channelCount = euInst.GetNumberOfDigitalChannelsFound();
		/*Enable Background installation*/ 
		IsBGInstallEnabled = true;
		setBGInstalltoSharedPref(IsBGInstallEnabled);
		/* In Auto Installation use case clear existing database and add everything fresh */
		if (isAutoInstall) {
			unregisterTvProviderContentObservers();
			/* Perform clearing of existing database */
			if((getCurrentInstallationMode() != NativeAPIEnums.InstallationMode.CAM_INSTALLATION) || ((getCurrentInstallationMode() == NativeAPIEnums.InstallationMode.CAM_INSTALLATION) && (channelCount != 0))) {
				String	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?";
				String[]	mselectionargs=new String[]{String.valueOf(ANTENNA_MEDIUM)};
				RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection,mselectionargs);
				Log.d(TAG,"ANTENNA: RowsDeleted "+RowsDeleted);
			}

			String mselection=Channels.COLUMN_VERSION_NUMBER+"= ?";
			String[] mselectionargs=new String[]{String.valueOf(CABLE_MEDIUM)};
			RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection,mselectionargs);
			Log.d(TAG,"CABLE: RowsDeleted "+RowsDeleted);
			
			String mselection2=Channels.COLUMN_VERSION_NUMBER+"= ?";
			String[] mselectionargs2=new String[]{String.valueOf(EXTERNAL_SOURCE)};
			RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection2,mselectionargs2);
			Log.d(TAG,"EXTERNAL_SOURCE: RowsDeleted "+RowsDeleted);			
			
			String mselection3=Channels.COLUMN_VERSION_NUMBER+"= ?";
			String[] mselectionargs3=new String[]{String.valueOf(MEDIA_CHANNEL)};
			RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection3,mselectionargs3);
			Log.d(TAG,"MEDIA_CHANNEL: RowsDeleted "+RowsDeleted);
			
			String mselection4=Channels.COLUMN_VERSION_NUMBER+"= ?";
			String[] mselectionargs4=new String[]{String.valueOf(IP_CHANNEL)};
			RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection4,mselectionargs4);
			Log.d(TAG,"IP_CHANNEL: RowsDeleted "+RowsDeleted);
			
			clearHTVChNameUpdateWaitList();
			
			/* Populate to TVProvider */
			mPopulateTvProvider();
		}
		else
		{
			
			AsyncTaskCommon asyncTaskCommon = new AsyncTaskCommon();
			asyncTaskCommon.execute(DB_UPDATE_BACKGROUND);
		}
	}
	
	public void SyncSingleChannelToDatabase (int Medium , int presetNum) {
		TcInstallerTvProviderData	TvpData;
		
		ArrayList<ContentProviderOperation> operations=new ArrayList<ContentProviderOperation>();
		int NoOfRecords = euInst.GetNumberOfDatabaseRecords (DATA_ALL_TABLE);
		int count =0;
		
		for (count = 0; count < NoOfRecords; count++)
		{
			
			TvpData = euInst.GetTvProviderBlobDataByIndex (count, DATA_ALL_TABLE);
			if (TvpData.PresetNumber == presetNum)
			{
				Log.d(TAG, "ONID" + TvpData.OriginalNetworkId + " TSID" + TvpData.Tsid + " ServiceID" + TvpData.ServiceId + " PresetNbr" + TvpData.PresetNumber + " UniqueID " + TvpData.UniqueId + "logoURL" + 
				TvpData.LogoURL + "TvpData.ChannelName" + TvpData.ChannelName);

				ContentProviderOperation.Builder builder=ContentProviderOperation.newUpdate(TvContract.buildChannelUri(TvpData.UniqueId));

				Log.d(TAG,"Tvcontract" + TvContract.buildChannelUri(TvpData.UniqueId));

				builder.withValue(Channels.COLUMN_DISPLAY_NAME,TvpData.ChannelName);
				builder.withValue(Channels.COLUMN_INTERNAL_PROVIDER_DATA,FormBlobData(TvpData,0,true));	
				
				//builder.withSelection(Channels._ID +"= ?" + " AND " + Channels.COLUMN_VERSION_NUMBER+"= ?", new String[]{String.valueOf(TvpData.UniqueId),String.valueOf(Medium)});	
				operations.add(builder.build());
				try {
					ContentProviderResult[] results = ctx.getContentResolver().applyBatch(Channels.CONTENT_URI.getAuthority(), operations);
					if(results != null) {
						Log.d(TAG,"SyncSingleChannelToDatabase():Operation finished");	
						operations.clear();
					}
				} catch (RemoteException e) {
					Log.d(TAG,"SyncSingleChannelToDatabase():Exception "+e);	
				} catch (OperationApplicationException e) {	
					Log.d(TAG,"SyncSingleChannelToDatabase():Exception "+e);	    		
				} catch(Exception e) {
					Log.d(TAG,"SyncSingleChannelToDatabase():Exception "+e);	    		
				}
				try	{
					Thread.sleep(100);	    		
				} catch (InterruptedException e) {
					Log.d(TAG,"SyncSingleChannelToDatabase():Exception "+e);	    		
				}			
				break;
			}
		}
	}
	
	class AsyncTaskCommon extends AsyncTask<String, Void, String> {

		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			Log.d(TAG, "onPostExecute enter result " + result);
			Log.d(TAG, "onPostExecute exit");
		}

		@Override
		protected String doInBackground(String... params) {
			String resultString = "";
			Log.d(TAG, "doInBackground params: " + params[0]);
			if ((params[0]).equalsIgnoreCase(DB_UPDATE_BACKGROUND)) {
				unregisterTvProviderContentObservers();
				// Add forTF415PHIEUMTK03-1614 by star ----add-----
				if (!mbUseHtvDTRTuneType) {
					DeleteExternalSourceFromTvProvider();
				}
				//-------------------------------------------------------end------
				SyncTvProvider();
				// Add forTF415PHIEUMTK03-1614 by star ----add-----
				if (!mbUseHtvDTRTuneType) {
					int number = getBiggestDisplayNumber();
					AddExternalSourceToTvProvider(number);
					SyncHTvProvider();
				}
				//-------------------------------------------------------end------
				registerTvProviderContentObservers();
				PopulateTvContentProvider();
				mUpdateDatabaseVersion(false);
			}
			return resultString;
		}
	}

	public  void UpdateLangCodeForCurrentMux(int presetNumber)
	{
		Log.d(TAG, "UpdateLangCodeForCurrentMux preset: " + presetNumber);
		int onid = 0, tsid = 0, uniqueId = 0, rowsUpdated = 0;
		int	ANTENNA_MEDIUM =0, CABLE_MEDIUM = 1;
		byte[]	BlobData = null;
		byte[]	PrivateBlobData = null;
		int CurrentMedium = ((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) ? CABLE_MEDIUM:ANTENNA_MEDIUM);
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();
        int menulanguage = mTvSettingsManager.getInt(TvSettingsConstants.MENULANGUAGE, 0, 0);

		String[] projection = new String[] {Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID};
		String	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?" +" AND "+Channels.COLUMN_DISPLAY_NUMBER+"= ?";
		String[] mselectionargs=new String[]{String.valueOf(CurrentMedium),String.valueOf(presetNumber)};

		Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

		/*Get ONID and TSID of preset*/
		if(cursor != null){
			try{
			while(cursor.moveToNext()) { 
				onid = cursor.getInt(0);
				tsid = cursor.getInt(1);
				break;
			}
			}finally{			
			   cursor.close();
			   cursor=null;
			}
		}

		unregisterTvProviderContentObservers();

		projection = new String[] {Channels.COLUMN_INTERNAL_PROVIDER_DATA,Channels._ID};
		mselection = Channels.COLUMN_VERSION_NUMBER+"= ?" + " AND "+ Channels.COLUMN_ORIGINAL_NETWORK_ID +"= ?" +" AND "+ Channels.COLUMN_TRANSPORT_STREAM_ID +"= ?";
		mselectionargs = new String[]{String.valueOf(CurrentMedium),String.valueOf(onid),String.valueOf(tsid)};

		cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

		if(cursor != null) {
			try {
				while(cursor.moveToNext()) { 
					BlobData = cursor.getBlob(0);
					uniqueId = cursor.getInt(1);

					try{
						keyvalues.setBlob(BlobData);
						PrivateBlobData = keyvalues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);
						privatekeyvalues.setBlob(PrivateBlobData);
						privatekeyvalues.put(TvContractPrivate.C_LANG_CODE,menulanguage);
						PrivateBlobData = privatekeyvalues.getBlob();
						keyvalues.put(ITvContractExtras.C_INSTALLER_BLOB,PrivateBlobData);
						BlobData = keyvalues.getBlob();

						ContentValues val = new ContentValues();
						
						val.put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,BlobData);
						
						mselection = Channels._ID +"= ?";
						mselectionargs = new String[]{String.valueOf(uniqueId)};
						
						rowsUpdated = 0;
						rowsUpdated = ctx.getContentResolver().update(TvContract.Channels.CONTENT_URI, val, mselection, mselectionargs);
						
						if(rowsUpdated == 0){
							Log.e(TAG, "Preset does not exist, cannot update menu language !!! ");
						}
						else{
							Log.d(TAG, "Updated menu language for _ID: " + uniqueId);
						}
					} catch (Exception e) {
						Log.d(TAG, "Exception in setBlob() while UpdateLangCodeForCurrentMux" + e);
					}
				}
			} finally {
			   cursor.close();
			   cursor = null;
			}
		}

		registerTvProviderContentObservers();
	}
	
	public void SyncTvProvider() {
		Log.d(TAG, "SyncTvProvider");
		int NoOfRecords = 0, Loop = 0;
		int[] newChannelnum;
		int[] new_index;
		TcInstallerTvProviderData	TvpData;
		int ANTENNA_MEDIUM = 0, CABLE_MEDIUM = 1;
		int	DBVersion = 0, CurrentVersion = 0, RowsDeleted = 0;
		byte[]  BlobData = null;
		byte[]  PrivateBlobData = null;
		boolean fbIsPbsMode = PlayTvUtils.isPbsMode();
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();
		int CurrentMedium = ((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) ? CABLE_MEDIUM : ANTENNA_MEDIUM);

		/*Get Version*/
    	String[] projection = new String[]{Channels.COLUMN_INTERNAL_PROVIDER_DATA};
		String   mselection = Channels.COLUMN_VERSION_NUMBER + " = ?";
		String[] mselectionargs = new String[]{String.valueOf(CurrentMedium)};

		if(fbIsPbsMode)
		{
			mselection = Channels.COLUMN_VERSION_NUMBER + " <= ? AND " + Channels.COLUMN_NETWORK_AFFILIATION + " NOT IN (?,?,?,?,?)";
			mselectionargs = new String[]{String.valueOf(CABLE_MEDIUM), HTV_DI_CHANNEL_FLAG, HTV_DI_CHANNEL_CHECK_FLAG, HTV_DI_CHANNEL_UPDATE_FLAG, HTV_DT_CHANNEL_FLAG, HTV_DT_CHANNEL_UPDATE_FLAG};
		}

		Cursor TCCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		if(TCCursor != null) {
			try {
				while(TCCursor.moveToNext()) { 
					BlobData = TCCursor.getBlob(0);
					break;
				}
			} finally {
			   TCCursor.close();
			   TCCursor = null;
			}
		}

		if(BlobData != null) {
			try {
				keyvalues.setBlob(BlobData);
			} catch (Exception e) {
				Log.d(TAG, "Exception in setBlob() while reading version" + e);
			}
			PrivateBlobData = keyvalues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);
			privatekeyvalues.setBlob(PrivateBlobData);
			DBVersion = privatekeyvalues.getInt(TvContractPrivate.C_VERSION);
			CurrentVersion = DBVersion + 1;
			Log.d(TAG, "Current version " + CurrentVersion);
		} else {
			Log.d(TAG, "No Records with Medium " + isDVBTorDVBC);
			DBVersion = 0;
			CurrentVersion = 0;
		}

		/* Read entries one by one and update/add to TVProvider */
		NoOfRecords = euInst.GetNumberOfDatabaseRecords(DATA_ALL_TABLE);
		Log.d (TAG, "Number of entries " + NoOfRecords);

        ContentValues val = new ContentValues();
		int count = 0;
		int size = NoOfRecords;
		int newRecordCount = 0;
		Boolean isMediachannelExist = false;
		ArrayList<ContentProviderOperation> operations = new ArrayList<ContentProviderOperation>();
		ArrayList<ContentValues> fvHtvNewRecords = null;
		SparseIntArray fvHtvSpecificChList = null;
		
		if(fbIsPbsMode) {
			fvHtvSpecificChList = new SparseIntArray();
			fvHtvNewRecords = new ArrayList<ContentValues>();
			
			projection = new String[]{Channels._ID, Channels.COLUMN_DISPLAY_NUMBER};
			mselection = Channels.COLUMN_NETWORK_AFFILIATION + " IN (?, ?, ?, ?, ?)";
			mselectionargs = new String[]{HTV_DI_CHANNEL_FLAG, HTV_DI_CHANNEL_CHECK_FLAG, HTV_DI_CHANNEL_UPDATE_FLAG, HTV_DT_CHANNEL_FLAG, HTV_DT_CHANNEL_UPDATE_FLAG};
			
			TCCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
			
			if(TCCursor != null && TCCursor.getCount() > 0) {
				int fiDispNum;
				TCCursor.moveToFirst();
				
				do {
					try {
						fiDispNum = Integer.parseInt(TCCursor.getString(1));
						fvHtvSpecificChList.append(TCCursor.getInt(0), fiDispNum);
					} catch(Exception e) {
					}
				} while(TCCursor.moveToNext());
			}
			
			if(TCCursor != null) {
				TCCursor.close();
				TCCursor = null;
			}
		}
		newChannelnum = new int[NoOfRecords+1];
		for (Loop = 0; Loop < NoOfRecords; Loop++) {
			//Log.d (TAG, " Query For index  "+ Loop);
			count++;
			ContentProviderOperation.Builder builder = ContentProviderOperation.newUpdate(Channels.CONTENT_URI);

			TvpData = euInst.GetTvProviderBlobDataByIndex(Loop, DATA_ALL_TABLE);
			Log.d(TAG, "ONID" + TvpData.OriginalNetworkId + " TSID" + TvpData.Tsid + " ServiceID" + TvpData.ServiceId + " PresetNbr" + TvpData.PresetNumber + " UniqueID " + TvpData.UniqueId + "DisplayName" + TvpData.ChannelName);

			Log.d(TAG,"tv.db TvpData.PresetNumber" +TvpData.PresetNumber);
			builder.withValue(Channels.COLUMN_INPUT_ID, "org.droidtv.tunerservice/.TunerService");
			if (fvHtvSpecificChList != null && TvpData.UniqueId > 0 && fvHtvSpecificChList.get(TvpData.UniqueId) == TvpData.PresetNumber) {
				
			} else {
				builder.withValue(Channels.COLUMN_TYPE, MapDecoderType(TvpData.DecoderType));
				builder.withValue(Channels.COLUMN_SERVICE_TYPE, MapServiceType(TvpData.DecoderType, TvpData.ServiceType));
				builder.withValue(Channels.COLUMN_ORIGINAL_NETWORK_ID, TvpData.OriginalNetworkId);
				builder.withValue(Channels.COLUMN_TRANSPORT_STREAM_ID, TvpData.Tsid);
				builder.withValue(Channels.COLUMN_SERVICE_ID, TvpData.ServiceId);
				builder.withValue(Channels.COLUMN_DISPLAY_NUMBER, TvpData.PresetNumber);
				builder.withValue(Channels.COLUMN_DISPLAY_NAME, TvpData.ChannelName);
				builder.withValue(Channels.COLUMN_DESCRIPTION, ((TvpData.ScrambledStatus == 1) ? "Scrambled" : ""));
				//builder.withValue(Channels.COLUMN_BROWSABLE, TvpData.VisibleService);
				builder.withValue(Channels.COLUMN_BROWSABLE, ((TvpData.SystemHidden != 0) ? 0 : 1));
				builder.withValue(Channels.COLUMN_SEARCHABLE, TvpData.NumericSelect);
				builder.withValue(Channels.COLUMN_INTERNAL_PROVIDER_DATA, FormBlobData(TvpData, CurrentVersion, true));
			}
			
			if (fbIsPbsMode) {
				Log.d(TAG, "SyncTvProvider()  TvpData.UniqueId=" + TvpData.UniqueId);
				int fiActualMedium = (MapDecoderType(TvpData.DecoderType) == Channels.TYPE_DVB_C) ? CABLE_MEDIUM : ANTENNA_MEDIUM;

				builder.withValue(Channels.COLUMN_VERSION_NUMBER, fiActualMedium);
				builder.withSelection(Channels._ID + " = ? AND " + Channels.COLUMN_VERSION_NUMBER + " = ?",
										new String[]{String.valueOf(TvpData.UniqueId), String.valueOf(fiActualMedium)});
			} else {
				builder.withValue(Channels.COLUMN_VERSION_NUMBER, CurrentMedium);
				builder.withSelection(Channels._ID + " = ? AND " + Channels.COLUMN_VERSION_NUMBER + " = ?",
										new String[]{String.valueOf(TvpData.UniqueId), String.valueOf(CurrentMedium)});
			}
			
			operations.add(builder.build());
			int display_tmp_mum = 0;
			if ((count == 100) || (Loop == size - 1)) {	
				try	{
					ContentProviderResult[] results = ctx.getContentResolver().applyBatch(Channels.CONTENT_URI.getAuthority(), operations);

                    Log.d(TAG, "Operation operations.size: " + operations.size() + ", Loop: " + Loop + ", newRecordCount: " + newRecordCount + ", results.length: " + results.length);
					
					if (results != null) {
						for (int j = 0; j < results.length; j++) {
							if ((results[j] != null) && (results[j].count == 0)) {
								TvpData = euInst.GetTvProviderBlobDataByIndex((newRecordCount + j), DATA_ALL_TABLE);

								val.put(Channels.COLUMN_INPUT_ID, "org.droidtv.tunerservice/.TunerService");
								val.put(Channels.COLUMN_TYPE, MapDecoderType(TvpData.DecoderType));
								val.put(Channels.COLUMN_SERVICE_TYPE, MapServiceType(TvpData.DecoderType, TvpData.ServiceType));
								if (mbUseHtvDTRTuneType) {
									val.put(Channels.COLUMN_NETWORK_AFFILIATION,
											(Channels.TYPE_PAL.equals(MapDecoderType(TvpData.DecoderType))) ? HTV_DT_CHANNEL_FLAG : ((TvpData.NewPreset == 1) ? HTV_DT_CHANNEL_FLAG : ""));
									TvpData.PresetNumber = 0;
								} else {
                                    val.put(Channels.COLUMN_NETWORK_AFFILIATION, (TvpData.NewPreset == 1) ? "New" : "");
								}
								val.put(Channels.COLUMN_ORIGINAL_NETWORK_ID, Integer.toString(TvpData.OriginalNetworkId));
								val.put(Channels.COLUMN_TRANSPORT_STREAM_ID, Integer.toString(TvpData.Tsid));
								val.put(Channels.COLUMN_SERVICE_ID, Integer.toString(TvpData.ServiceId));
								newChannelnum[display_tmp_mum] = TvpData.PresetNumber;
								Log.d(TAG,"htv put TvpData.PresetNumber " +newChannelnum[display_tmp_mum] + "display_tmp_mum " + display_tmp_mum);
								display_tmp_mum++;
								val.put(Channels.COLUMN_DISPLAY_NUMBER, Integer.toString(TvpData.PresetNumber));
								val.put(Channels.COLUMN_DISPLAY_NAME, TvpData.ChannelName);
								val.put(Channels.COLUMN_DESCRIPTION, ((TvpData.ScrambledStatus == 1) ? "Scrambled" : ""));
								//val.put(Channels.COLUMN_BROWSABLE, Integer.toString(TvpData.VisibleService));
								//val.put(Channels.COLUMN_BROWSABLE, ((TvpData.SystemHidden != 0) ? 0 : ((TvpData.NewPreset == 1 && mbUseHtvDTRTuneType) ? 0 : 1)));
								val.put(Channels.COLUMN_BROWSABLE, ((TvpData.SystemHidden != 0) ? 0 : 1));
								val.put(Channels.COLUMN_SEARCHABLE, Integer.toString(TvpData.NumericSelect));
								val.put(Channels.COLUMN_INTERNAL_PROVIDER_DATA, FormBlobData(TvpData, CurrentVersion, false));
								val.put(Channels.COLUMN_LOCKED, 0);
								if (fbIsPbsMode) {
									val.put(Channels.COLUMN_VERSION_NUMBER,
											((MapDecoderType(TvpData.DecoderType) == Channels.TYPE_DVB_C) ? CABLE_MEDIUM : ANTENNA_MEDIUM));
								} else {
									val.put(Channels.COLUMN_VERSION_NUMBER,
											((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) ? CABLE_MEDIUM : ANTENNA_MEDIUM));
								}

								Uri fCPResult = ctx.getContentResolver().insert(TvContract.Channels.CONTENT_URI, val);
								
								if (fbIsPbsMode) {
									int fiMappedChId = Integer.parseInt(fCPResult.getLastPathSegment());
									ContentValues val3 = new ContentValues();

									val3.put(HtvContract.HtvChannelSetting._ID, fiMappedChId);
									val3.put(HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE, "TYPE_TUNER");
									val3.put(HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID, fiMappedChId);

									if (val.getAsString(Channels.COLUMN_NETWORK_AFFILIATION).startsWith(HTV_DT_CHANNEL_FLAG)) {
										val3.put(HtvContract.HtvChannelSetting.COLUMN_SKIP1, "1");
										val3.put(HtvContract.HtvChannelSetting.COLUMN_SKIP2, "1");
									}
									
									fvHtvNewRecords.add(val3);
								}
							}
						}
						Log.d(TAG, "Operation finished");
						operations.clear();
					}
				} catch (RemoteException e) {
						Log.d(TAG, "SyncTvProvider():RemoteException " + e);
					} catch (OperationApplicationException e) {
						Log.d(TAG, "SyncTvProvider():OperationApplicationException " + e);
					} catch(Exception e) {
						Log.d(TAG, "SyncTvProvider():Exception " + e);
					}
					try	{
						Thread.sleep(100);
					} catch (InterruptedException e) {
						Log.d(TAG, "SyncTvProvider():InterruptedException " + e);
					}
					count = 0;
					newRecordCount = Loop + 1;
			}
		}

		/*Delete old records*/
		projection = new String[] {Channels._ID, Channels.COLUMN_INTERNAL_PROVIDER_DATA};
		if (fbIsPbsMode) {
			mselection = Channels.COLUMN_VERSION_NUMBER + " <= ? AND " + Channels.COLUMN_NETWORK_AFFILIATION + " NOT IN (?, ?, ?, ?, ?)";
			mselectionargs = new String[]{String.valueOf(CABLE_MEDIUM), HTV_DI_CHANNEL_FLAG, HTV_DI_CHANNEL_CHECK_FLAG, HTV_DI_CHANNEL_UPDATE_FLAG, HTV_DT_CHANNEL_FLAG, HTV_DT_CHANNEL_UPDATE_FLAG};
		} else {
			mselection = Channels.COLUMN_VERSION_NUMBER + " = ?";
			mselectionargs = new String[]{String.valueOf(CurrentMedium)};
		}

		TCCursor = null;
		TCCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		if(TCCursor != null) {
			try {
			while(TCCursor.moveToNext()) { 
				BlobData = TCCursor.getBlob(1);
				if(BlobData != null) {
					try {
						keyvalues.setBlob(BlobData);
					} catch (Exception e) {
						Log.d(TAG, "Exception in setBlob() while deleting old records" + e);
					}			
					
					PrivateBlobData = keyvalues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);
					privatekeyvalues.setBlob(PrivateBlobData);

					int Version = privatekeyvalues.getInt(TvContractPrivate.C_VERSION);

					/*Delete if version is not matching*/
					if(Version != CurrentVersion) {
						/*Delete the record*/
						if (fbIsPbsMode) {
							mselection = Channels._ID + " = ? AND " + Channels.COLUMN_VERSION_NUMBER + " <= ?";
							mselectionargs = new String[]{String.valueOf(TCCursor.getInt(0)), String.valueOf(CABLE_MEDIUM) };
						} else {
							mselection = Channels._ID + " = ? AND " + Channels.COLUMN_VERSION_NUMBER + " = ?";
							mselectionargs = new String[]{String.valueOf(TCCursor.getInt(0)), String.valueOf(CurrentMedium) };
						}
						RowsDeleted = 0;
						RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI, mselection, mselectionargs);
						if(RowsDeleted != 0) {
							Log.d(TAG, "Deleted Preset " + TCCursor.getInt(0));
							if (fbIsPbsMode) {
								String mselection2 = HtvContract.HtvChannelSetting._ID + " = ?";
								String[] mselectionargs2 = new String[]{String.valueOf(TCCursor.getInt(0))};
							
								ctx.getContentResolver().delete(HtvContract.HtvChannelSetting.CONTENT_URI, mselection2, mselectionargs2);
							}
						}
					}
				}
			}
			} finally {
			 TCCursor.close();
			 TCCursor = null;
			}
		}

		sync_IDToMW();
		
		if (fvHtvNewRecords != null && !fvHtvNewRecords.isEmpty()) {
			int fiLastHtvDispNumber = getHTVBiggestDisplayNumber();
			int loop = 0;
			int[] loopnum;
			//newChannelnum = getHTVEmptyDisplayNumber(newChannelnum,fiLastHtvDispNumber);
			//loop = newChannelnum.length;
			for (ContentValues fValSet : fvHtvNewRecords) {
				fValSet.put(HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, newChannelnum[loop]);
				loop++;
				//fValSet.put(HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, ++fiLastHtvDispNumber);
			}

			
			ctx.getContentResolver().bulkInsert(HtvContract.HtvChannelSetting.CONTENT_URI, fvHtvNewRecords.toArray(new ContentValues[]{}));
		}

		ntf.notifyAllObservers(EventIDs.EVENT_COMMIT_FINISHED, "");
	}
	
	public void sync_IDToMW () {
		Log.d(TAG, "sync_IDToMW");
		TcInstallerTvProviderData tvpData = new TcInstallerTvProviderData();
		byte[] blobData = null;
		int ANTENNA_MEDIUM = 0, CABLE_MEDIUM = 1;
		int numOfRecords = 0;
		//int CurrentMedium = ((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) ? CABLE_MEDIUM : ANTENNA_MEDIUM);

		// Get Data from Tvprovider
		String[] projection = new String[] {Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_TYPE, Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_DISPLAY_NUMBER, Channels.COLUMN_INTERNAL_PROVIDER_DATA, Channels._ID};
		String mselection;
		String[] mselectionargs;

		if(PlayTvUtils.isPbsMode()) {
			mselection = Channels.COLUMN_VERSION_NUMBER + " <= ?";
			mselectionargs = new String[] {String.valueOf(CABLE_MEDIUM)};
		} else {
			int CurrentMedium = ((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) ? CABLE_MEDIUM : ANTENNA_MEDIUM);
			mselection = Channels.COLUMN_VERSION_NUMBER + " = ?";
			mselectionargs = new String[] {String.valueOf(CurrentMedium)};
		}

		Cursor TCCursor = ctx.getContentResolver().query (TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		if (TCCursor != null) {
			numOfRecords = TCCursor.getCount();
		}
		Log.d(TAG, "sync_IDToMW: Number of channles in db " + numOfRecords);	

		if (TCCursor != null) {
			try {
				while(TCCursor.moveToNext()) {
					tvpData.DecoderType = GetDecoderType(TCCursor.getString(0));
					tvpData.OriginalNetworkId = TCCursor.getInt(2);
					tvpData.Tsid = TCCursor.getInt(3);
					tvpData.ServiceId = TCCursor.getInt(4);
					tvpData.PresetNumber = TCCursor.getInt(5);
					blobData = TCCursor.getBlob(6);
					tvpData.UniqueId = TCCursor.getInt(7);
					//Log.d (TAG," UniqueID for Preset " + tvpData.PresetNumber + " tvpData.UniqueId" +tvpData.UniqueId);
					populate_IDSyncKeysFromBlobData(tvpData, blobData);
					euInst.syncUniqueIdToMW(tvpData);
				}	
			} finally {
				TCCursor.close();
				TCCursor = null;
			}
		}
	}

	public void populate_IDSyncKeysFromBlobData (TcInstallerTvProviderData tvpData, byte[] blobData)
	{
		IIntKeyValueables keyValues = IIntKeyValueables.Instance.getInterface();
		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();
		byte[] privateBlobData = null;
		
		try {
			keyValues.setBlob(blobData);
		}
		catch (Exception e) {
			Log.d(TAG, "Exception in setBlob() in populateServiceTableKeysFromBlobData ()" + e);
		}
		
		tvpData.Frequency = keyValues.getInt (ITvContractExtras.C_FREQUENCY);
		tvpData.StreamPriority = keyValues.getInt (ITvContractExtras.C_STREAMPRIORITY);

		privateBlobData = keyValues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);
		try{
			privatekeyvalues.setBlob(privateBlobData);
		}
		catch (Exception e) {
			Log.d(TAG, "Exception in setBlob() in AddMWRecord for Private Data" + e);
		}
		
		tvpData.MultiplePreset = privatekeyvalues.getIntArray (TvContractPrivate.C_MULTIPLE_PRESET);

        tvpData.AnalogTablePreset = privatekeyvalues.getInt (TvContractPrivate.C_ANALOG_TABLE_PRESET);
		tvpData.Type = privatekeyvalues.getInt (TvContractPrivate.C_TYPE);
	}

	private void setPbsTimeZoneIndex(int country, int index) {
		Log.d(TAG, "setPbsTimeZoneIndex: country " + country + ", timezone " + index);
		switch(country) {
			case TvSettingsDefinitions.InstallationCountryConstants.SPAIN:
				Log.d(TAG, "update spain timezone (" + index + ") during install channle.");
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_TIMEZONESPAIN, 0, index);
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_OFF_TIMEZONESPAIN, 0, index);				
				break;
			case TvSettingsDefinitions.InstallationCountryConstants.PORTUGAL:
				Log.d(TAG, "update portugal timezone (" + index + ") during install channle.");
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_TIMEZONEPORTUGAL, 0, index);
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_OFF_TIMEZONEPORTUGAL, 0, index);				
				break;
			case TvSettingsDefinitions.InstallationCountryConstants.KAZAKHSTAN :
				Log.d(TAG, "update kazakhstan timezone (" + index + ") during install channle.");
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_TIMEZONEKAZAKHSTAN, 0, index);
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_OFF_TIMEZONEKAZAKHSTAN, 0, index);				
				break;
			case TvSettingsDefinitions.InstallationCountryConstants.RUSSIA:
				Log.d(TAG, "update russia timezone (" + index + ") during install channle.");
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_TIMEZONERUSSIA, 0, index);
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_OFF_TIMEZONERUSSIA, 0, index);				
				break;
			case TvSettingsDefinitions.InstallationCountryConstants.AUSTRALIA:
				Log.d(TAG, "update australia timezone (" + index + ") during install channle.");
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_TIMEZONEAUSTRALIA, 0, index);
				mTvSettingsManager.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_OFF_TIMEZONEAUSTRALIA, 0, index);				
				break;
		}
	}
	/*** TVPROVIDER IMPLEMENTATION END ***/
	
    public void commitToTVSettings() {
        Log.d(TAG, "commitToTVSettings() started");

        boolean resetParentalRating  = false;

        //Check whether installed country changed and reset the parental rating setting
        if (getCountryNameFromTVS().equalsIgnoreCase (getCachedCountryName ())) {
            resetParentalRating = false;
        } else {
            resetParentalRating = true;
        }
        
        if(false == ifVirginInstallation()){
            // EuinstallerTC should not set the below bits in NVM
            
            // set country
            setSelectedCountyID(getCachedCountryID());

            // update timezone in TVSettings
            if (ifTimezoneCountry(getCachedCountryName())) {
                setCurrentTimeZoneToTVS(getCachedTimeZoneName());
				
				setPbsTimeZoneIndex(mTVSCselectedCountryID, timeZoneIndex);//min.jiang add 2015-08-27
            }
        }

        // set the operator in TVSettings
        if (ifCountryHasOperator(getCachedCountryID())) {
            mTvSettingsManager.putInt(TvSettingsConstants.OPERATORCABLE, 0, operatorIdTVS);
        }
		else
		{
			mTvSettingsManager.putInt(TvSettingsConstants.OPERATORCABLE, 0, TvSettingsDefinitions.OperatorCableConstants.NONE);
		}

        // update last selected tuner in TVSettings
        mTvSettingsManager.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC);

        // update digital/analog in TVSettings
        setAnalogueDigitalToSharedPref(analogOrDigital);

		
		if ((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) ||
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND))) ||
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))) ||
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN)))) {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSCHANNELLOGOS, 0, 0);
		}
		else {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSCHANNELLOGOS, 0, 1);
		}
		
        // for NORDIG countries set subtitles on /*legacy FRS :10660 and dCRS*/
		if ((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) ||
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND))) ||
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))) ||
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN)))) {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 1);
		}

		/* For DVBC Belgium Telenet, Subtitle value shoud be ON. */
		if ((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) &&
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))) &&
			(getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET)))) {
			Log.d (TAG, "Telenet Instalation. Subtitle Set to ON");
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 1);
		}

		if ((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) &&
				(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA)) &&
				 (operatorIdTVS == TvSettingsDefinitions.OperatorCableConstants.RCS_RDS))) {
			Log.d (TAG, "ROMANIA Instalation. Subtitle Set to ON ");
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 1);
		}

		if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE))) {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 2);
		}
		if ((isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBT)){
			if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA))) ||
				(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM)))) {
				mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 0);
			}else if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE))) {
				mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 1);
			}
		}
		
        // If the country is Italy or France, parental rating shall be set to Age 18.
		if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY))){
			setParentalRating( TvSettingsDefinitions.InstallationCountryConstants.ITALY,"18");
			 mTvSettingsManager.putInt(TvSettingsConstants.DVBPARENTALRATING, 0, TvSettingsDefinitions.ParentalRatingConstants.AGE18);
		}else if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE))){
			setParentalRating(TvSettingsDefinitions.InstallationCountryConstants.FRANCE,"18");
			 mTvSettingsManager.putInt(TvSettingsConstants.DVBPARENTALRATING, 0, TvSettingsDefinitions.ParentalRatingConstants.AGE18);
		}else if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA))){
			setParentalRating(TvSettingsDefinitions.InstallationCountryConstants.ROMANIA,"18");
			mTvSettingsManager.putInt(TvSettingsConstants.DVBPARENTALRATING, 0, TvSettingsDefinitions.ParentalRatingConstants.AGE18);
		}else if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM)) && 
			(operatorIdTVS == TvSettingsDefinitions.OperatorCableConstants.TELENET)){
			setParentalRating(TvSettingsDefinitions.InstallationCountryConstants.BELGIUM,"17");
			mTvSettingsManager.putInt(TvSettingsConstants.DVBPARENTALRATING, 0, TvSettingsDefinitions.ParentalRatingConstants.AGE17);
		}else{
			// If installation country is changed from prev installation, reset the Parental Rating Settings
	        if (resetParentalRating == true) {
	            setParentalRating (mTVSCselectedCountryID, "none");
	            mTvSettingsManager.putInt (TvSettingsConstants.DVBPARENTALRATING, 0, TvSettingsDefinitions.ParentalRatingConstants.NONE);
	        }
		}
		
        // set channel filter
        if ( (currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION) 
             || (currentInstallationMode == NativeAPIEnums.InstallationMode.CAM_INSTALLATION) )
		{
            mTvSettingsManager.putInt(TvSettingsConstants.CHANNELFILTER, 0, TvSettingsDefinitions.ChannelFilterConstants.ALL);
			mTvSettingsManager.putInt(TvSettingsConstants.CHANNELFILTERTC, 0, TvSettingsDefinitions.ChannelFilterConstants.ALL);
			mTvSettingsManager.putInt(TvSettingsConstants.TCCHANNELSUBLIST, 0, TvSettingsDefinitions.ChannelFilterConstants.ALL);
        }
        
        // set free + scrambled (all) or free
        isFreeOrFreeScrambled = getWSSetFreeCAChannels();
        if(isFreeOrFreeScrambled == 0){
            mTvSettingsManager.putInt(TvSettingsConstants.ACCESSTYPE, 0, TvSettingsDefinitions.AccessTypeConstants.FREE);
        }else {
            mTvSettingsManager.putInt(TvSettingsConstants.ACCESSTYPE, 0, TvSettingsDefinitions.AccessTypeConstants.ALL);
        }
		

        // ziggo fix AN-29679, AN-33714
        if ((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))
                && getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ZIGGO))) ||
                (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA))
                && getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_RCS_RDS))) 
                ) {
            mTvSettingsManager.putInt(TvSettingsConstants.ACCESSTYPE, 0,TvSettingsDefinitions.AccessTypeConstants.ACCESSTYPE_IGNORE);
        }
        
        // set Antenna/Cable
        Log.d(TAG, "isDVBTorDVBC: " + isDVBTorDVBC);
		if (PlayTvUtils.isPbsMode()) { // HTV - always set medium type to antenna.
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA);
		} else {
	        if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
    	        mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.CABLE);
        	} else if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBT) {
            	mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA);
	        } else {
    	        // default case if any should come here
        	}
		}

        // set the clock mode
        if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
            mTvSettingsManager.putInt(TvSettingsConstants.AUTOCLOCKMODE, 0, TvSettingsDefinitions.InstallationClockModeConstants.AUTOMATICCLOCKMODE);
        } else if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBT) {
            int clockMode = mTvSettingsManager.getInt(TvSettingsConstants.AUTOCLOCKMODE, 0, 0);
            Log.d(TAG, "commitToTVSettings() clockMode: " + clockMode);
            if (clockMode == TvSettingsDefinitions.InstallationClockModeConstants.MANUALCLOCKMODE) {
                mTvSettingsManager.putInt(TvSettingsConstants.AUTOCLOCKMODE, 0, TvSettingsDefinitions.InstallationClockModeConstants.AUTOMATICCLOCKMODE);
            }else{
                // remains same as user selected
            }
        }

		if (getCurrentInstallationMode() == NativeAPIEnums.InstallationMode.CAM_INSTALLATION) {
			int channelCount = 0;
			int l_terrestrialCamOpId = 1;
			channelCount = euInst.GetNumberOfDigitalChannelsFound();
			if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
				mTvSettingsManager.putInt(TvSettingsConstants.OPERATORCABLE, 0, operatorIdTVS);
			} else {
				if(channelCount == 0) {
					l_terrestrialCamOpId = 0;
				}
				Log.d(TAG, "Updating OPERATORTERRESTRIAL with " + l_terrestrialCamOpId);
				mTvSettingsManager.putInt(TvSettingsConstants.OPERATORTERRESTRIAL, 0, l_terrestrialCamOpId);
			}
		}
		//As per discussion with prasthanth and smitha nordig CR will take care of advance output no need to set any value//
		if(ifVirginInstallation()){
			mTvAudioMgr = ITvAudioManager.Instance.getInterface();
			if(((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))) && (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBT))
				|| ((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN))) && (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC))
				||((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND))) && (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBT)))
			{
				mTvSettingsManager.putInt(TvSettingsConstants.DIGITALOUTPUTFORMAT, 0, TvSettingsDefinitions.DigitalOutputFormatConstants.MULTICHANNEL);
				mTvAudioMgr.setProperty(ITvAudioManager.AUDMGR_PROPERTY_SPDIF_MODE, ITvAudioManager.AUDMGR_SPDIF_OUTPUT_MODE_BITSTREAM);
			} else {
				mTvSettingsManager.putInt(TvSettingsConstants.DIGITALOUTPUTFORMAT, 0, TvSettingsDefinitions.DigitalOutputFormatConstants.STEREO);
				mTvAudioMgr.setProperty(ITvAudioManager.AUDMGR_PROPERTY_SPDIF_MODE, ITvAudioManager.AUDMGR_SPDIF_OUTPUT_MODE_PCM);
			}
		}

		//Default setting to BroadCast EPG with CR AN-81715 for Slovenia & RMCR-3597 M7 Countries
		if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA)))    ||
		   (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))) ||
		   (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM)))     ||
		   (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LUXEMBOURG)))  ||
		   (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA)))     ||
		   (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CZECH_REP)))   ||
		   (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVAKIA)))    ||
		   (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY)))     
		)
		{
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSDVBEPGCHOICE, 0, TvSettingsDefinitions.InstSettingsDvbEpgConstants.DVBEPG);
		}
		else
		{
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSDVBEPGCHOICE, 0, TvSettingsDefinitions.InstSettingsDvbEpgConstants.AUTO);
		}

		/*The below changes are brought in accordance with RMCR:3578*/	
		mSettingOnOffDiversityOfHBBTVStatus(mTVSCselectedCountryID);

		commitToCTVServerSettings();
        Log.d(TAG, "commitToTVSettings() completed");
    }

    public void commitToCTVServerSettings(){
	try {
		tvMpl = TvMediaPlayer.getTvTunerMediaPlayer();
		iTvMplCtx = tvMpl.getTvMediaPlayerContext();
		iTvSrvConfig = iTvMplCtx.getTvServerConfig();
		String l_selectedCountry = getCountryNameFromTVS();
		NativeAPIEnums.DVBTOrDVBC selectedMediumInTVS = getSelectedDVBTOrDVBCFromTVS();

				
	//DVB-TLite Country
		if ((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBT)
			&& (countrySupportsDVBTFullorLite(getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light)){
			iTvSrvConfig.setValue(ITvServerConfig.DVBT_LITE_COUNTRY, 1);
		}else{
			iTvSrvConfig.setValue(ITvServerConfig.DVBT_LITE_COUNTRY, 0);
		}
		
	//Hearing Impaired
		iTvSrvConfig.setValue(ITvServerConfig.HEARING_IMPAIRED_ON, 1);
	//Subtitle On
		iTvSrvConfig.setValue(ITvServerConfig.SUBTITLE_ON, 1);
	//Multi-feed Support
		if ((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
			&& getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY))){
			iTvSrvConfig.setValue(ITvServerConfig.MULTIFEED_SUPPORTED, 1);	
		}else{
		  	iTvSrvConfig.setValue(ITvServerConfig.MULTIFEED_SUPPORTED, 0);
		}
	//Subtitle PID FallBack to First PMT
		if ((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBT)
				&& getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UK))){
		iTvSrvConfig.setValue(ITvServerConfig.SUBTITLE_PID_FALLBACK_FIRST_PMT, 1);
		}else{
		  iTvSrvConfig.setValue(ITvServerConfig.SUBTITLE_PID_FALLBACK_FIRST_PMT, 0);
		}

	//Premixed VI Support
		if ((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBT)
				&& ((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE)))||
						(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY)))||
						(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND))))){
		  iTvSrvConfig.setValue(ITvServerConfig.IS_PREMIXED_VI_SUPPORTED, 1);
		}else{
		  iTvSrvConfig.setValue(ITvServerConfig.IS_PREMIXED_VI_SUPPORTED, 0);
		}

	//QA Support
		if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE))){
		  iTvSrvConfig.setValue(ITvServerConfig.IS_QA_SUPPORTED, 1);
		}else{
		  iTvSrvConfig.setValue(ITvServerConfig.IS_QA_SUPPORTED, 0);
		}
		  
	//AVC Descriptor Support
		if (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND))){
		  iTvSrvConfig.setValue(ITvServerConfig.IS_AVC_DESCRIPTOR_SUPPORTED, 1);
		}else{
		  iTvSrvConfig.setValue(ITvServerConfig.IS_AVC_DESCRIPTOR_SUPPORTED, 0);
		}	
		  
	//value = eurdiv_IsAc3AudioSupported();
		  iTvSrvConfig.setValue(ITvServerConfig.IS_AC3_AUDIO_SUPPORETED, 0);
		  iTvSrvConfig.setValue(ITvServerConfig.CAM1_MEDIUM, 1);//CAM1 Medium
		  iTvSrvConfig.setValue(ITvServerConfig.CAM2_MEDIUM, 1);//CAM2 Medium
		  iTvSrvConfig.setValue(ITvServerConfig.OVV_ENABLE, 1);//OVV Enable Status
		  iTvSrvConfig.setValue(ITvServerConfig.SAD_ENABLE, 1);//SAD Enable Status
		  iTvSrvConfig.setValue(ITvServerConfig.DUAL_STATUS, 1);//Dual Status

	//Default Advanced Audio Format
		if( (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY)) ) 
			&& getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBT) {
			  	iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_ADVANCED_AUDIOFORMAT, 1);
		}else{
				iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_ADVANCED_AUDIOFORMAT, 0);
		}
	//QAA MulLang Identification Support
		
		if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))) || (IsAPMEACountry())) {
		  
		  iTvSrvConfig.setValue(ITvServerConfig.QAA_MUL_LANG_IDENTIFICATION_SUPPORTED, 1);
		  
		}else{
		  iTvSrvConfig.setValue(ITvServerConfig.QAA_MUL_LANG_IDENTIFICATION_SUPPORTED, 0);
		}
		// MONITOR_SDT_RUNNING_STATUS
		
			if (ifCountryHasOperator(getCachedCountryID())
					&& (getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
					&& (currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION)
					&& ((getOperatorFromMW() == NativeAPIEnums.Operators.UPC)|| 
							(getOperatorFromMW() == NativeAPIEnums.Operators.Telenet) || 
							(getOperatorFromMW() == NativeAPIEnums.Operators.Unitymedia))) {
				
				iTvSrvConfig.setValue(ITvServerConfig.MONITOR_SDT_RUNNING_STATUS, 0);
			} else {
				iTvSrvConfig.setValue(ITvServerConfig.MONITOR_SDT_RUNNING_STATUS, 1);
			}
			// CR RMCR-3063
			if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TURKEY))) {
		  
		  		iTvSrvConfig.setValue(ITvServerConfig.MONITOR_SDT_RUNNING_STATUS, 0);
		  
			}
	
	//Default Character Table
		iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);/*If nothing we are taking this as default*/
		  if (countrySupportsDVBTFullorLite(l_selectedCountry) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Full)
		  {
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GREECE)))
					  {
				  	iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,3);// ISO/IEC 8859-7
					  }
			  if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK)))
				  ||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE)))
					 || (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_GERMANY)))
						 || (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY)))
							 || (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SPAIN)))
								  ||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN)))
									|| (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ESTONIA))))
			  {
					iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,5);// ISO/IEC 8859-9
			  }
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))) /* Implementation of IPM-47442 */
			  {
				 if(selectedMediumInTVS==NativeAPIEnums.DVBTOrDVBC.DVBC)
				 {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
				 }else{
					 iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,5);// ISO/IEC 8859-9
				 }	
			  }
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY)))
			  {
				 if((selectedMediumInTVS==NativeAPIEnums.DVBTOrDVBC.DVBC)&&
						 (getOperatorFromMW() == NativeAPIEnums.Operators.UPC)&&
						 (currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION))
				 {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
				 }else{
					 iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,6);// ISO/IEC 8859-2
				 }	
			  }
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND)))
			  {
				 if(selectedMediumInTVS==NativeAPIEnums.DVBTOrDVBC.DVBC)
				 {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
				 }else{
					 iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,5);// ISO/IEC 8859-9
				 }	
			  }
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVENIA)))/*   brg36mgr#68735  */ 
			  {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,6);// ISO/IEC 8859-2
			  }
			  if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND))) /* CR-brg36mgr#85649 */ 
				 || (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))))
			  {
				  if(selectedMediumInTVS==NativeAPIEnums.DVBTOrDVBC.DVBC)
					 {
					  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,5);// ISO/IEC 8859-9
					 }else{
						 iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
					 }	
			  }
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_PORTUGAL)))/*   brg36mgr#68735  */ 
			  {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,7);// ISO/IEC 8859-15 
			  }
			  if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELARUS)))/* CR brg36mgr#137992 */ 
				  ||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_RUSSIA)))
					  ||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UKRAINE))))
			  {
				  if(selectedMediumInTVS==NativeAPIEnums.DVBTOrDVBC.DVBC)
					 {
					  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
					 }else{
						 iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,1); // ISO/IEC 8859-5
					 }
			  }
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND)))
			  {
				 if((selectedMediumInTVS==NativeAPIEnums.DVBTOrDVBC.DVBC)&&
						 (getOperatorFromMW() == NativeAPIEnums.Operators.UPC)&&
						 (currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION))
				 {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
				 }else{
					 iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,6);// ISO/IEC 8859-2
				 }	
			  }
			  if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AZERBAIJAN)))// ISO/IEC 8859-5 CR AN-24687
				  ||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SERBIA))))/*AN-45722*/
				  {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,1);// ISO/IEC 8859-2
				  }
			  if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA)))
					  ||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM)))
						 || (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_CZECH_REP)))
							 || (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UK)))
								 || (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_LATVIA)))
									  ||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SLOVAKIA)))
										|| (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND)))
										|| (getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MACEDONIA_FYROM))))
			  {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
				  
				  
			  }
			  
			  
		  }
		  else{
		  
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_UKRAINE)))
			  {
				 if(selectedMediumInTVS==NativeAPIEnums.DVBTOrDVBC.DVBC)
				 {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,1);// ISO/IEC 8859-5
				 }else{
					 iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
				 }	
			  }
			  
			  if(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA)))
			  {
				 if((selectedMediumInTVS==NativeAPIEnums.DVBTOrDVBC.DVBC)&&
						((currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION)&&
							(getOperatorFromMW() == NativeAPIEnums.Operators.Other)))
				 {
				  iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,5);// ISO/IEC 8859-5
				 }else{
					 iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE,0);// ISO/IEC 6937
				 }	
			  }
			  
			  
		  }
		//SDT original
		  if((ifCountryHasOperator(getCachedCountryID()))&&((getOperatorFromMW() == NativeAPIEnums.Operators.KDG_HD) || (getOperatorFromMW() == NativeAPIEnums.Operators.KDG_SD))){
			  iTvSrvConfig.setValue(ITvServerConfig.DUMP_ALLPIDS_TC,1);
		  }
		  else{
			  iTvSrvConfig.setValue(ITvServerConfig.DUMP_ALLPIDS_TC,0);
		  }
		iTvSrvConfig.setValue(ITvServerConfig.MONITOR_SDT_ORIGINAL_STATUS,1);
		iTvSrvConfig.setValue(ITvServerConfig.VISUALLY_IMPAIRED_ON, 1);
		iTvSrvConfig.setValue(ITvServerConfig.OAD_SUPPORTED,1);
		iTvSrvConfig.setValue(ITvServerConfig.QAD_SUPPORTED,1);
		if((ifCountryHasOperator(getCachedCountryID()))&&(getOperatorFromMW() == NativeAPIEnums.Operators.Ziggo)){
			iTvSrvConfig.setValue(ITvServerConfig.VOD_SUPPORTED,1);
			}
		else{
			iTvSrvConfig.setValue(ITvServerConfig.VOD_SUPPORTED,0);
			}


		iTvSrvConfig.sync();
		Log.d(TAG, "commitToCTVServerSettings() completed");

	} catch (Exception e) {
		Log.d(TAG, "Exception in commitToCTVServerSettings()caught");
		}		  	
    }
    public void setPLPID(int plpID){
        if(STUB_MODE){
            
        }else{
            euInst.SetStreamPriority(plpID);
        }
        Log.d(TAG, "setPLPID() " + plpID);
    }
    
    public int[] getPLPIDs(){
        
        if(STUB_MODE){
            plpIDs = new int[10];
            for(int localIndex=0; localIndex<10;localIndex++){
                plpIDs[localIndex] = localIndex;
            }
        }else{
            plpIDs = euInst.GetDetectedPlpIds_Tvplayer();;
        }
        Log.d(TAG, "getPLPIDs() " + plpIDs.length);
        return plpIDs;
    }

    
    public boolean ifNetwkFreqDialogDuringPrescan(){
        Boolean returnStatus = false;
        if (STUB_MODE) {
            returnStatus = false;
        } else {
            if (((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
                    && getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS)) 
                    && (getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ZIGGO)) 
                            || getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_OTHER))))
                    || ((getCachedDVBTOrDVBC() == NativeAPIEnums.DVBTOrDVBC.DVBC)
                            && getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM)) &&
                            getCachedOperatorName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET)))

            ) {
                returnStatus = true;
            }
        }
        Log.d(TAG, "ifNetwkFreqDialogDuringPrescan " + returnStatus);
        return returnStatus;
    }
    
    public void aciSetSurface(final Surface txtsurface){
        Log.d(TAG, "aciSetSurface enter " + txtsurface);
        Thread t = new Thread() {
            public void run() {   
                euInst.SetAciSurface(txtsurface);
            }
        };
        t.start();
        Log.d(TAG, "aciSetSurface exit ");
    }
    
    public void aciNavigate(NativeAPIEnums.ACINavigate directionEnum){
        Log.d(TAG, "aciNavigate " + directionEnum);
		switch(directionEnum)
		{
		case	UP:
			Log.d(TAG, "UP Key from ACI Page");
			euInst.MoveToPreviousAciItem ();
			break;
		case	DOWN:
			Log.d(TAG, "DOWN Key from ACI Page");
			euInst.MoveToNextAciItem();
			break;
		case	ENTER:
			Log.d(TAG, "ENTER Key from ACI Page");
			euInst.SelectAciItem ();
			break;
		default:
			break;
		}
    }
    
    public void setDTRScreenMode(DTRScreenMode argMode){
    	Log.d(TAG, "setDTRScreenMode " + argMode);
		currentDTRScreenMode = argMode;
	}
    
    public DTRScreenMode getDTRScreenMode(){
    	Log.d(TAG, "getDTRScreenMode " + currentDTRScreenMode);
		return currentDTRScreenMode;
	}
    
    public boolean ifTLiteCountry(){
    	boolean returnStatus = false;
    	
        if (countrySupportsDVBTFullorLite(getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light) {
        	returnStatus = true;
        }
    	Log.d(TAG, "ifTLiteCountry " + returnStatus);
		return returnStatus;
    }
    
    public void handleFactoryReset(){
    	Log.d(TAG, "handleFactoryReset");
    	FactoryResetHandler fr = new FactoryResetHandler();
    	fr.execute(FACTORY_RESET_DETECTED);
    }
    
    class FactoryResetHandler extends AsyncTask<String, Void, String> {

    	@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			Log.d(TAG, "onPostExecute enter result " + result);
		}

		@Override
		protected String doInBackground(String... params) {
			String resultString = "";
			Log.d(TAG, "doInBackground params: " + params[0]);
			if ((params[0]).equalsIgnoreCase(FACTORY_RESET_DETECTED)) {
				ITvAudioManager mTvAudioMgr = ITvAudioManager.Instance.getInterface();// new TvVideoManager();
				
				int mSystemCountry = mTvSettingsManager.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		    	int mMedium = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
		    	
		    	Log.d(TAG,"mSystemCountry:" + mSystemCountry + " mMedium:" + mMedium);
		    	
		    	if(	((mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.SWEDEN) && 
		    			(mMedium == TvSettingsDefinitions.InstSettingsInstallMode.CABLE)) ||
		    		((mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.HUNGARY) && 
		    				(mMedium == TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA))||
		    				((mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.NEWZEALAND) && 
		    			(mMedium == TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA))){
		    		Log.d(TAG,"reset audio to multichannel");
		    		mTvSettingsManager.putInt(TvSettingsConstants.DIGITALOUTPUTFORMAT, 0, TvSettingsDefinitions.DigitalOutputFormatConstants.MULTICHANNEL);
					mTvAudioMgr.setProperty(ITvAudioManager.AUDMGR_PROPERTY_SPDIF_MODE, ITvAudioManager.AUDMGR_SPDIF_OUTPUT_MODE_BITSTREAM);
		    	}else{
		    		Log.d(TAG,"reset audio to stereo");
		    		mTvSettingsManager.putInt(TvSettingsConstants.DIGITALOUTPUTFORMAT, 0, TvSettingsDefinitions.DigitalOutputFormatConstants.STEREO);
					mTvAudioMgr.setProperty(ITvAudioManager.AUDMGR_PROPERTY_SPDIF_MODE, ITvAudioManager.AUDMGR_SPDIF_OUTPUT_MODE_PCM);
		    	}
		    	
		    	
				resultString = "FACTORY_RESET_DETECTED";
			}
			return resultString;
		}
    	
    }

	public PowerStates getFromPowerState(){

		Log.d(TAG, "getFromPowerState " + fromPowerStates);
		return fromPowerStates;
	}

	public PowerStates getToPowerState(){

		Log.d(TAG, "getToPowerState " + toPowerStates);
		return toPowerStates;
	}

    
    public void handlePowerStateChange(PowerStates argFromPowerState, PowerStates argToPowerState){
    	PoweStateChangeHandler psh = new PoweStateChangeHandler();
		Log.d(TAG, "handlePowerStateChange ");
    	fromPowerStates = argFromPowerState;
    	toPowerStates = argToPowerState;
		if(ctx != null){
    		psh.execute(POWER_CHANGE_DETECTED);
		}
    }
    
    public void showTVNofification(final Context context, final String notifMessage ){
		Log.d(TAG,"showTVNofification  context: " + context + ", notifMessage: " + notifMessage);
		   
		messenger = TvToastMessenger.getInstance(context);
		mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
		mTimeOutTvToast.setMessage(notifMessage);
		messenger.showTvToastMessage(mTimeOutTvToast);
	}
    
    public  void showTVNofificationTillKey(final Context context, final String notifMessage ){
    	Log.d(TAG,"showTVNofificationTillKey  context: " + context + ", notifMessage: " + notifMessage);
		   
		messenger = TvToastMessenger.getInstance(context);
		mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_PERMANENT | TvToastMessenger.TYPE_KEY_PRESS, "", -1);
		mTimeOutTvToast.setMessage(notifMessage);
		messenger.showTvToastMessage(mTimeOutTvToast);
    }

	class PoweStateChangeHandler extends AsyncTask<String, Void, String> {

		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			Log.d(TAG, "onPostExecute enter result " + result);

			if (result.equalsIgnoreCase(CHANNEL_LIST_NOTIFICATION)) {
				Log.d(TAG, "onPostExecute enter case I");
				
				showTVNofification(ctx, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CHANNELLIST_UPDATED));
				
				// reset flags
                channelsUpdated(false);
                networkChangeDetected(false);
			} else if (result.equalsIgnoreCase(LCN_CONFLICT_NOTIFICATION)) {
				
				Log.d(TAG, "onPostExecute enter case II");
				
				Intent l_intent = new Intent(ctx, NetworkUpdateDialogActivity.class);
				l_intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				ctx.startActivity(l_intent);
				
				// reset flags
                channelsUpdated(false);
                networkChangeDetected(false);
			}else if (result.equalsIgnoreCase(UDATE_NEEDED_NOTIFICATION)) {
				Log.d(TAG, "onPostExecute enter case III");
			
				showTVNofification(ctx, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CHANNEL_UPDATE_NEEDED));
								
				// reset flags
                channelsUpdated(false);
              
                // donot reset back the flag as the behaviour should persist across reboots until installation is done
                // networkChangeDetected(false);
			} else if (result.equalsIgnoreCase(DEFAULT_POWER_ON_CASE)) {
				Log.d(TAG, "onPostExecute enter case IV");
				// reset flags
				// networkChangeDetected(false);
			} else if(result.equalsIgnoreCase(EXIT_INSTALLATION)){
				Log.d(TAG, "EXIT_INSTALLATION");
				
				boolean fbIsBypassStep = false;
				
				if(mSemForHTVDT != null) {
					if(mSemForHTVDT.tryAcquire())
						mSemForHTVDT.release();
					else {
						fbIsBypassStep = true;
						ntf.notifyAllObservers(EventIDs.EVENT_HTV_DT_CANCEL, "");
					}
				}
				
				if(!fbIsBypassStep) {
					(InstallerActivityManager.getInstance()).exitInstallation(EXIT_INSTALLER_REASON.POWER_STATE_TO_SEMISTANDY);
				}
			}
			
			Log.d(TAG, "onPostExecute exit");
		}

		@Override
		protected String doInBackground(String... params) {
			String resultString = "";
			Log.d(TAG, "doInBackground params: " + params[0]);
			if ((params[0]).equalsIgnoreCase(POWER_CHANGE_DETECTED)) {

				if (toPowerStates == PowerStates.POWER_STATE_FULL_SYSTEM_START) {
					String selectedCountryInTVS = getCountryNameFromTVS();
					DVBTOrDVBC selectedMediumInTVS = getSelectedDVBTOrDVBCFromTVS();
					if (ifChannelUpdateON()) { /* Channel channel update On */
						if ((selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ITALY)))
								&& ifNetworkChangeDetected()
								&& (selectedMediumInTVS == DVBTOrDVBC.DVBT)) {
							// if country is italy & network change detected flag is set (LCN conflict)
							resultString = LCN_CONFLICT_NOTIFICATION;
						} else if((GetStandbyUpdate() == 1)/* Automatic channel update On */
								&&  ifNetworkChangeDetected() /* No update installation has been done in standby upon a network update detection in operational mode */
								&&  ((selectedMediumInTVS == DVBTOrDVBC.DVBT && selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) || 
									(selectedMediumInTVS == DVBTOrDVBC.DVBT && IsAPMEAbackgroundNWupdate())	||
									((selectedMediumInTVS == DVBTOrDVBC.DVBC) && !(selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS)))))	
								){
							/*
							DVB-T Norway OR DVB-C except for the Netherlands - Operator Ziggo/Other
							AND
							No update installation has been done in standby upon a network update detection in operational mode
							AND
							Automatic channel update On and Channel update message On
							*/
							resultString = UDATE_NEEDED_NOTIFICATION;
						} else if (ifChannelsUpdated()) {
							resultString = CHANNEL_LIST_NOTIFICATION;
						} else{
							resultString = DEFAULT_POWER_ON_CASE;
						}
					}else{
						resultString = DEFAULT_POWER_ON_CASE;
					}
				}else if (toPowerStates == PowerStates.POWER_STATE_SEMI_STANDBY) {
					if((getApplicationState() == ApplicationState.IDLE) || 
							(getApplicationState() == ApplicationState.INST_SERVICE) ){
					}else{
						// case where wizard installation is continuing and power button is pressed
						resultString = EXIT_INSTALLATION;
					}
				}
			}
			return resultString;
		}
	}
	
	public void enterNonInteruptableMode() {
		if(ifVirginInstallation()){
		}else{
			Log.d(TAG, "NON_INTERRUPTIBLE intent enter dispatched");
			ifPendingNonInteruptableRequest = true;
			Intent intent = new Intent("org.droidtv.NON_INTERRUPTIBLE");
			intent.putExtra("Enter", true);
			ctx.sendStickyBroadcast(intent);
		}
	}
    
	public void exitNonInteruptableMode() {
		if(ifVirginInstallation()){
		}else{
			Log.d(TAG, "NON_INTERRUPTIBLE intent exit dispatched " + ifPendingNonInteruptableRequest);
			Intent intent = new Intent("org.droidtv.NON_INTERRUPTIBLE");
			intent.putExtra("Enter", false);
			ctx.sendStickyBroadcast(intent);
			ifPendingNonInteruptableRequest = false;
		}
	}

	
	
    public void muteAudio(boolean argValue){
		Log.d(TAG, "muteAudio Mute Audio & Video also for MTK =" + argValue);
	
		if(mSessionInstanceMain != null) {
			ITVTunerSession tvmc = mSessionInstanceMain.getTunerSession();
			if(tvmc != null) {	
				tvmc.setTrackMuteStatus(TvTrackInfo.TYPE_AUDIO ,argValue);
				tvmc.setTrackMuteStatus(TvTrackInfo.TYPE_VIDEO ,argValue);
			} else {
				Log.d(TAG, "muteAudio iITVTunerSession is null");
			}
		}
	}
    
    public boolean ifRecordingIsInProgress(){
    	boolean returnStatus = false;
    	
    	String[] projection = {IRecordingsContract.C_RECORDING_ID};
    	String selection = IRecordingsContract.C_RECORDING_TYPE + " == ?";
        String[] selectionArgs = {""+IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal()};

        Cursor cur = ctx.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, selection, selectionArgs, null);
        if (cur != null) {
			if(cur.getCount() > 0){
				returnStatus = true;
			}
			cur.close();
			cur=null;
		}

    	Log.d(TAG, "ifRecordingIsInProgress " + returnStatus);
    	return returnStatus;
    }
    
    public void showRecordingMessage(){
    	// display tvtoast
    	if(ctx !=null){
			messenger = TvToastMessenger.getInstance(ctx);
			mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
			mTimeOutTvToast.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_PVR_STOP_RECORDING));
			messenger.showTvToastMessage(mTimeOutTvToast);
    	}
    }
    
    /*
     * Function return True for APMEA LCNV2 supported countries
     * Singapore,Thailand,Taiwan,Malaysia
     * 
     * @Params 
     */
	
	public boolean ifEnteredSortingPhase(){
    	return ifEnteredSorting;
    }
	
	public void setSortingPhase(boolean argSortingPhase){
    	Log.d(TAG, "setSortingPhase " + argSortingPhase);
    	ifEnteredSorting = argSortingPhase;
    }
	
	public boolean ifLCNV2Supported(){
		boolean retval = false;
		if((getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE)))||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND)))||
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TAIWAN)))||(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA))) ||
			(getCachedCountryName().equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM)))){
		retval=true;
		}
		return retval;
	}
    /*
     * Function return True for APMEA Background Network Update i.e APMEAn country supports this
     * 
     * @Params 
     */
	public boolean IsAPMEAbackgroundNWupdate(){
		boolean retval = false;
    	String storedCountryName = getCountryNameFromTVS();
		if((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE)))||(storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND)))||
			(storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TAIWAN)))||(storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA)))||
			(storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA)))||(storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA)))||
			(storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND)))||(storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM)))){
		retval=true;
		}
		Log.d(TAG, "IsAPMEAbackgroundNWupdate return"+retval);
		return retval;
	}
    
	public boolean IsAPMEACountry(){
		boolean retval = false;
		String InstalledCountryName = getCachedCountryName();
		if((InstalledCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE)))||(InstalledCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND)))||
			(InstalledCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TAIWAN)))||(InstalledCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA)))||
			(InstalledCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA)))||(InstalledCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA)))||
			(InstalledCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND)))||(InstalledCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM)))){
		retval=true;
		}
		Log.d(TAG, "IsAPMEACountry return"+retval);
		return retval;
	}
    public void exitWithoutInstallation(){
		Log.d(TAG, "exitWithoutInstallation");
		
		if(euInst.ifValidSession()){
			euInst.StopInstallation();
			euInst.StopOngoingScan();
			//euInst.registerCIListener();
			euInst.ExitEuInstallerTC();
			muteAudio(false);
		}
		
		stopAllTimerTasks();
		
		setApplicationState(NativeAPIEnums.ApplicationState.IDLE);
		UnregisterTuningInstance();
		closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
		
		if(ifPendingNonInteruptableRequest){
			exitNonInteruptableMode();
		}

		 if (currentInstallationMode != NativeAPIEnums.InstallationMode.CAM_INSTALLATION) {
		// clear notification handler and add nativeapiwrapper
			ntf.removeAllObservers();
			ntf.addObserver(NativeAPIWrapper.getInstance());
		}
	}
	
    public void exitOnInstallationComplete(){
    	Log.d(TAG, "exitOnInstallationComplete currentInstallationMode = " + currentInstallationMode);

		/*Re-Enable Background installation*/		
		cachedMajorVesrion = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, 0);
		IsBGInstallEnabled = true;
		setBGInstalltoSharedPref(IsBGInstallEnabled);

		if (STUB_MODE) {
			exitNonInteruptableMode();
		} else {
		
			if(euInst.ifValidSession()){
				//euInst.StopInstallation();
				//euInst.StopOngoingScan();
				//euInst.registerCIListener();
				euInst.ExitEuInstallerTC();
				muteAudio(false);
				euInst.SetHostControlStatus(true);
			}
			
			stopAllTimerTasks();
			if(ifPendingNonInteruptableRequest){
				exitNonInteruptableMode();
			}
			setApplicationState(NativeAPIEnums.ApplicationState.IDLE);
			UnregisterTuningInstance();
			closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
			
			// clear notification handler and add nativeapiwrapper
			ntf.removeAllObservers();
			ntf.addObserver(NativeAPIWrapper.getInstance());
			
			// broadcast message to all the modules that auto installation completed
            Intent intent = new Intent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
            if ((currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION) 
            		|| (currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN)){
                intent.putExtra("InstallMode", "Auto");
                tvclkManager = ITvClockManager.Instance.getInterface();// new TvClockManager();
                tvclkManager.SetClockUnDefined();
                
            } else if ((currentInstallationMode == NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION)|| (currentInstallationMode == NativeAPIEnums.InstallationMode.NETWORK_UPDATE)) {
                intent.putExtra("InstallMode", "Update");
            } else if (currentInstallationMode == NativeAPIEnums.InstallationMode.CAM_INSTALLATION) {
                intent.putExtra("InstallMode", "Auto");
            } else if(currentInstallationMode == NativeAPIEnums.InstallationMode.BACKGROUND_INSTALLATION){
            	intent.putExtra("InstallMode", "Background");
            } 
            
            if (NativeAPIEnums.DVBTOrDVBC.DVBC == getCachedDVBTOrDVBC()) {
                intent.putExtra("InstallMedium", "Cable");
            } else {
                intent.putExtra("InstallMedium", "Terrestrial");
            }
            if(currentInstallationMode == InstallationMode.DTR_INSTALLATION || currentInstallationMode == InstallationMode.HTV_DTR_INSTALLATION){
            	// in case of DTR code will come here on search > done without store button i.e failed case. CHANNEL_INSTALL_STOPPED is already dispatched from DTRMenuItem screen
            } else {
				if(intent.getExtra("InstallMode") != null){
					ctx.sendStickyBroadcast(intent);
				}
            }
            Log.d(TAG, "send intent broadcast org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");

			/* CIPLUS: Enabled Host control here */
			euInst.SetHostControlStatus(true);
            // dispatch intent to playtv to play first channel
            if (ifVirginInstallation()) {
                // donot do channel switching
            	InstallerActivityManager.getInstance().finishActivityStack();
            }else{
                if ( (currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION)
                     || (currentInstallationMode == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN) 
				     || (currentInstallationMode == NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION)
				     || (currentInstallationMode == NativeAPIEnums.InstallationMode.NETWORK_UPDATE)
					 || (currentInstallationMode == NativeAPIEnums.InstallationMode.CAM_INSTALLATION) 
					 || (currentInstallationMode == NativeAPIEnums.InstallationMode.DTR_INSTALLATION) ){
                    // it should not come here for prescan as prescan is the
                    // failed
                    // case here
                    switchToFirstAvailableChannel(currentInstallationMode);
                }               
            }           
		}
    }
    
	public void SetHostControlStatus(boolean OnOff)
	{
		if (euInst != null) {
			euInst.SetHostControlStatus(OnOff);
		}	
	}
	
    public NativeAPIEnums.ApplicationState getApplicationState(){
    	Log.d(TAG, "getApplicationState() " + currentAppState);
    	return currentAppState;
    }

    public void setApplicationState(NativeAPIEnums.ApplicationState argState){
    	currentAppState = argState;
    	
    	// if wizard of channel settings comes up stop MW in case its active
    	if((currentAppState == NativeAPIEnums.ApplicationState.INST_SETTINGS) ||
    			(currentAppState == NativeAPIEnums.ApplicationState.INST_WIZARD) ||
    			(currentAppState == NativeAPIEnums.ApplicationState.INST_SETTINGS_WIZARD)||
    			(currentAppState == NativeAPIEnums.ApplicationState.INST_NETWORK_UPDATE)){
    		    euInst.StopMWInstIfInstExists();

    		// unregister service if already registered
    		ntf.notifyAllObservers(EventIDs.EVENT_UNREGISTER_SERVICE, "");	
    	}
    	
    	Log.d(TAG, "setApplicationState " + currentAppState);
    }
    
    public int findDigitalChannel(int aiChFreq, int aiTuneType, int aiServID, Integer aiNID, Integer aiONID, Integer aiTSID, Integer aiMod, Integer aiSymRt, Integer aiPLPID) {
    	
    	int fiFoundChId = -1;
		int[] checkplp = new int[10];
		int cur_indexl;
		int findplp = 0;
    	String[] fsvProjection = new String[] { Channels._ID , Channels.COLUMN_INTERNAL_PROVIDER_DATA };
    	String fsSelection = Channels.COLUMN_VERSION_NUMBER+"=" + (aiTuneType==1?1:0) + " AND " + Channels.COLUMN_SERVICE_ID + "=" + aiServID + " ";
    	
    	Log.d(TAG, "findDigitalChannel() is called. Freq:" + aiChFreq + "  TuneType:" + aiTuneType + "  ONID:" + aiONID + "  NID:" + aiNID + "  TSID:" + aiTSID + "  ServID:" + aiServID + "  Mod:" + aiMod + "  SymRt:" + aiSymRt + "  PLP:" + aiPLPID);
    	
    	if(aiONID != null)
    		fsSelection += " AND " + Channels.COLUMN_ORIGINAL_NETWORK_ID + "=" + aiONID + " ";
    	
    	if(aiTSID != null)
    		fsSelection += " AND " + Channels.COLUMN_TRANSPORT_STREAM_ID + "=" + aiTSID + " ";
        	
    	Cursor cur = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, fsvProjection, fsSelection, new String[]{}, null);
		cur_indexl = cur.getCount();
    	if(cur != null && cur.getCount()>0) {
    		
    		IIntKeyValueables fKeyvalues = IIntKeyValueables.Instance.getInterface();
    		
    		cur.moveToFirst();

    		try{
    			do{
        			byte[] fvBlobData = cur.getBlob(1);
					cur_indexl--;
        			fKeyvalues.setBlob(fvBlobData);
        			
        			int fiFreq = fKeyvalues.getInt(ITvContractExtras.C_FREQUENCY);
        			int fiFreqDiff = aiChFreq - fiFreq;
        			
        			if((fiFreqDiff < -2500) || (fiFreqDiff > 2500)) {
        				
        				Log.d(TAG, "Info: Frequency different: " + aiChFreq + "   " + fiFreq);
        				
        				continue;
        			}
        			
        			if(aiNID != null 
        					&& fKeyvalues.getInt(ITvContractExtras.C_NetworkId) != 0
    						&& aiNID != fKeyvalues.getInt(ITvContractExtras.C_NetworkId)) {
        				
        				Log.d(TAG, "Info: Network ID different: " + fKeyvalues.getInt(ITvContractExtras.C_NetworkId) + "  " + aiNID);

    					continue;
        			}
        			/*
        			if(aiMod != null) {
        				
        				// 0 - QAM16
        				// 1 - QAM32
        				// 2 - QAM64
        				// 3 - QAM128
        				// 4 - QAM256
        				int fiMod = -1;
        				
        				if(aiTuneType == 0) {
        					
        					switch(aiMod) {
        					case 1:
        						fiMod = 2;
        						break;
        					case 3:
        						fiMod = 3;
        						break;
        					case 5:
        						fiMod = 4;        							
        					}        					
        				}
        				else {        					
        					fiMod = aiMod;        					
        				}
        				
        				if(fiMod != fKeyvalues.getInt(ITvContractExtras.C_MODULATION)) {
        					
        					Log.d(TAG, "Info: Modulation different: " + fKeyvalues.getInt(ITvContractExtras.C_MODULATION) + "  " + fiMod);
        					continue;        				
        				}
        			}*/
        					
        			/*
        			if(aiTuneType == 1 && aiSymRt != null) {
        				int fiSymRt = fKeyvalues.getInt(ITvContractExtras.C_SYMBOLRATE);
        				int fiSymRtDiff = aiSymRt - fiSymRt;
        				
        				if(fiSymRtDiff < -10000 || fiSymRtDiff > 10000) {
        					Log.d(TAG, "Info: Symbol rate different: " + aiSymRt + "  " + fiSymRt);
        					continue;
        				}        				
        			}*/

        			fiFoundChId = cur.getInt(0);
					Log.d(TAG, "Info: findDigitalChannel fiFoundChId: " + fiFoundChId);
					if((aiPLPID != -1) ) {
						checkplp[cur_indexl] = fKeyvalues.getInt(ITvContractExtras.C_PLPID);
						if (fKeyvalues.getInt(ITvContractExtras.C_PLPID) == aiPLPID) {
							findplp = 1;
							break;
						} else if ((aiPLPID != null ) && fKeyvalues.getInt(ITvContractExtras.C_PLPID) != aiPLPID && findplp != 1) {
							findplp = -1;
						}
					}
    				//break;
        			
        		}while(cur.moveToNext());
				if(findplp == -1)
					fiFoundChId = -1;
    		}
    		catch(Exception e) { }    		    		    		    	
    	}
    	
    	if(cur != null) {    		
    		cur.close();
    		cur = null;
    	}

    	return fiFoundChId;
    }
    
    public void switchToSpecificChannel(int aiChId) {
    	switchToSpecificChannelEx(aiChId, false);
    }
    
    public void switchToSpecificChannelEx(int aiChId, boolean abAddForceTuneFlag) {
    	Log.d(TAG, "switchToSpecificChannel will switch channel to ChId:" + aiChId);
		
		Uri fUri = TvContract.buildChannelUri(aiChId);
		
		Log.d(TAG, "raise intent to playtv: " + fUri.toString());
		/* YanFu 2016/08/15 fix [TF415PHIEUMTK03-1429] [Phase3][WIXP] Request IP Channel selection fail (background tune)*/
		Log.d(TAG, "Change tune!");
		Intent fPlayTVIntent = new Intent();
		fPlayTVIntent.setAction("org.droidtv.intent.action.ChannelChange");
		fPlayTVIntent.setPackage("org.droidtv.playtv");
		fPlayTVIntent.putExtra("uriString", fUri.toString());
//			serviceCtx.startService(playTVIntent);	
//			Intent fPlayTVIntent = new Intent("android.intent.action.VIEW", fUri);
//			fPlayTVIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TOP);
//			if(abAddForceTuneFlag)
//				fPlayTVIntent.putExtra(KEYNAME_FORCE_CHANNEL_TUNING, 1);

		try {
			ctx.startService(fPlayTVIntent);
//				ctx.startActivity(fPlayTVIntent);
		} catch (Exception ex) {
			Log.e(TAG, "raise intent exception caught: " + ex.getMessage());
		}
    }

    public int findAnalogChannel(int aiChFreq, int aiTuneType, Integer aiTvSys) {
    	
    	int fiFoundChId = -1;
    	int fiFoundChFreqDiff = 4000; //4Mhz
    	String[] fsvProjection = new String[] { Channels._ID , Channels.COLUMN_INTERNAL_PROVIDER_DATA };
    	String fsSelection = Channels.COLUMN_VERSION_NUMBER+"=" + aiTuneType + " AND " + Channels.COLUMN_TYPE + "='" + Channels.TYPE_PAL + "' ";
    	
    	Log.d(TAG, "findAnalogChannel() is called. Freq:" + aiChFreq + "  TuneType:" + aiTuneType + "  TvSys:" + aiTvSys);
        	
    	Cursor cur = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, fsvProjection, fsSelection, new String[]{}, null);
    	
    	if(cur != null && cur.getCount()>0) {
    		
    		IIntKeyValueables fKeyvalues = IIntKeyValueables.Instance.getInterface();
    		/*
    		Integer fiTvSysCond = null;
    		
    		if(aiTvSys != null)											
				switch(aiTvSys) {		
				case 1:
					fiTvSysCond = ITuningAna.TUNING_ANA_TVSYS_DK | ITuningAna.TUNING_ANA_TVSYS_DK_A2;//0x4;//AnalogSystemCountry.EAST_EUROPE;
					break;
				case 2:
					fiTvSysCond = ITuningAna.TUNING_ANA_TVSYS_I;//0x2;//AnalogSystemCountry.UK;
					break;
				case 3:
					fiTvSysCond = ITuningAna.TUNING_ANA_TVSYS_L;//0x8;//AnalogSystemCountry.FRANCE;
					break;
				case 0:
				default:
					fiTvSysCond = ITuningAna.TUNING_ANA_TVSYS_BG | ITuningAna.TUNING_ANA_TVSYS_BG_A2; //0x1;//AnalogSystemCountry.WEST_EUROPE;		
				}*/
    		
    		cur.moveToFirst();
    		
    		try{
    			do{
        			byte[] fvBlobData = cur.getBlob(1);
        			    		
        			fKeyvalues.setBlob(fvBlobData);
        			
        			int fiFreq = fKeyvalues.getInt(ITvContractExtras.C_FREQUENCY);
        			int fiFreqDiff = (aiChFreq>fiFreq)?(aiChFreq-fiFreq):(fiFreq-aiChFreq);
        			
        			//Frequency difference must be less than 3.5Mhz.
        			if(fiFreqDiff > 3500) { 
        				Log.d(TAG, "Info: frequency different: " + fiFreq + "   " + aiChFreq);
        				
        				continue;
        			}

        			/*
        			if(fiTvSysCond != null) {
        				
        				int fiTvSys = fKeyvalues.getInt(ITvContractExtras.C_MODULATION);        			        				        	
            			
        				if((fiTvSys & fiTvSysCond.intValue()) == 0) {
        					
        					Log.d(TAG, "Info: Mod different: " + fiTvSys + "   " + fiTvSysCond);
        					
        					continue;            	
        				}
        			}*/
        			
        			if(fiFreqDiff < fiFoundChFreqDiff){
        				
        				fiFoundChId = cur.getInt(0);
        				
        				if(fiFreqDiff == 0)
        					break;
        				else
        					fiFoundChFreqDiff = fiFreqDiff;
        			}        			
        		}while(cur.moveToNext());
    		}
    		catch(Exception e) { }    		    		    		    	
    	}
    	
    	if(cur != null) {   		
    		cur.close();  
    		cur = null;
    	}
    	    	
    	return fiFoundChId;
    }

	/*
	 * invokes the intent to playtv to switch on first available installed
	 * channel
	 */
	public void switchToFirstAvailableChannel(NativeAPIEnums.InstallationMode instMode) {
		int channelId = -1;
		int mChannelNum = 0;
		int ANTENNA_MEDIUM = 0, CABLE_MEDIUM = 1;
		int fiActualMedium = ANTENNA_MEDIUM;
		// update last selected tuner in TVSettings
		mTvSettingsManager.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);

		if (STUB_MODE) {

		} else {
			if ((instMode == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION) || (instMode == NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION)
					|| (instMode == NativeAPIEnums.InstallationMode.CAM_INSTALLATION) || (instMode == NativeAPIEnums.InstallationMode.DTR_INSTALLATION)) {
				channelId = euInst.GetFirstInstalledChannel();
			}
		}

		if((channelId == -1) || (channelId == 0XFFFF)) 
		{
			mChannelNum =  mTvSettingsManager.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC, 0, 0);
			Log.d(TAG, "switchToFirstAvailableChannel() LastSelectedPreset:  " + mChannelNum );
		} else {
			String[] mProjection = new String[] { Channels._ID };		
			String mSelecion = Channels.COLUMN_DISPLAY_NUMBER + "=?"+" AND "+Channels.COLUMN_VERSION_NUMBER+"= ?";	
			String[] mSelectionArgs;
			if(PlayTvUtils.isPbsMode())
			{
				mSelectionArgs = new String[]{Integer.toString(channelId),Integer.toString(fiActualMedium)};
			} else {
				if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
					mSelectionArgs = new String[]{Integer.toString(channelId),Integer.toString(1)};
				} else {
					mSelectionArgs = new String[]{Integer.toString(channelId),Integer.toString(0)};
				}
			}

			Log.d(TAG, "switchToFirstAvailableChannel channelId " + channelId + "mSelectionArgs[1] " + mSelectionArgs[1]);
			Cursor cur = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, mProjection, mSelecion, mSelectionArgs, null);
			if(cur != null && cur.getCount() == 0) {
				Log.d(TAG, "switchToFirstAvailableChannel c.getCount()" + cur.getCount());
				fiActualMedium = CABLE_MEDIUM;
				Log.d(TAG, "switchToFirstAvailableChannel() fiActualMedium2:  " + fiActualMedium );
				mSelectionArgs = new String[]{Integer.toString(channelId),Integer.toString(fiActualMedium)};
				cur = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, mProjection, mSelecion, mSelectionArgs, null);

			}


			if ((cur != null) && (cur.getCount() > 0)) {
				cur.moveToFirst();
				try {
					mChannelNum = Integer.parseInt(cur.getString(0));
				} catch (Exception ex) {
				}
			}
			if(cur != null) {
				cur.close();
				cur=null;
			}
		}

		// Reset MediaPlayer
		if(euInst.ifValidSession()){
			euInst.StopInstallation();
			euInst.StopOngoingScan();
			//Log.d(TAG, "Register CI listner back before releasing session");
			//euInst.registerCIListener();
			euInst.ExitEuInstallerTC();
		}
		UnregisterTuningInstance();
		closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);

		Log.d(TAG, "switchToFirstAvailableChannel() mChannelNum: " + mChannelNum);

		if(mChannelNum != 0) 
		{
			String[] mProjection = new String[] { Channels.COLUMN_DISPLAY_NUMBER };		
			String mSelecion = Channels._ID + "=?"+" AND "+Channels.COLUMN_VERSION_NUMBER+"= ?";	
			String[] mSelectionArgs;
			if(PlayTvUtils.isPbsMode())
			{
				//int fiActualMedium = ((MapDecoderType(0) == Channels.TYPE_DVB_C) ? CABLE_MEDIUM:ANTENNA_MEDIUM);
				Log.d(TAG, "switchToFirstAvailableChannel() fiActualMedium3:  " + fiActualMedium );
				mSelectionArgs = new String[]{Integer.toString(mChannelNum),Integer.toString(fiActualMedium)};
			} else {
				if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
					mSelectionArgs = new String[]{Integer.toString(mChannelNum),Integer.toString(1)};
				} else {
					mSelectionArgs = new String[]{Integer.toString(mChannelNum),Integer.toString(0)};
				}
			}

			Cursor curs = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, mProjection, mSelecion, mSelectionArgs, null);
			if((curs != null) && curs.getCount() > 0) 
			{
				//Log.d(TAG, "UniqueID checking for in DB" + c.getCount());
			}else {
					Log.d(TAG, "switchToFirstAvailableChannel() UniqId Not Exist in tv.db " + mChannelNum);
					mChannelNum = 0;
			}
			if(curs != null){
				curs.close();
				curs=null;
			}
				
		}

				
		Intent playTVIntent = null;
		Uri playUri = null;
		if(mChannelNum != 0)
		{
			playUri = TvContract.buildChannelUri(mChannelNum);
			if ((instMode == NativeAPIEnums.InstallationMode.INCOMPLETE_INSTALLATION) || (instMode == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN)) {
				// invalid channelID
				Log.d(TAG, "Tuning to default");
				// playUri = tvuri.formURI(TvURIEnum.DEFAULT);
			} else {
				if (getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC) {
					if (((instMode == NativeAPIEnums.InstallationMode.DTR_INSTALLATION) && (isDTRStoreOptionAvailable() == false))) {
						// playUri = tvuri.formURI(TvURIEnum.DEFAULT);
					} else {
						// playUri = tvuri.formURI(Medium.MEDIUM_CABLE, channelId,
						// SelectionType.SELECTION_NORMAL);
						playUri = TvContract.buildChannelUri(mChannelNum);
					}
				} else {
					// playUri = tvuri.formURI(Medium.MEDIUM_TERRESTRIAL, channelId,
					// SelectionType.SELECTION_NORMAL);
					playUri = TvContract.buildChannelUri(mChannelNum);
				}
			}
			Log.d(TAG, "raise intent to playtv: " + playUri.toString());
			playTVIntent = new Intent("android.intent.action.VIEW",playUri);	
		}else {
			Log.d(TAG, "raise intent to WATCH_TV:"); 
			playTVIntent = new Intent("org.droidtv.playtv.WATCH_TV");
		}

		//Intent playTVIntent = new Intent("org.droidtv.playtv.SELECTURI", playUri);

//		playTVIntent.putExtra("uri", playUri);
		
		playTVIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TOP);


		if (instMode == NativeAPIEnums.InstallationMode.NETWORK_UPDATE) {
			playTVIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		}

		try {
			ctx.startActivity(playTVIntent);
		} catch (Exception ex) {
			Log.e(TAG, "raise intent exception caught: " + ex.getMessage());
		}
	}

    public int getTestReceptionFrequency() {

        int l_retFrequency = 0;

        if (STUB_MODE) {
        } else {
            l_retFrequency = euInst.GetTunerFrequency();
            if (l_retFrequency < 0) {
                l_retFrequency = 0;
            }
        }
        return l_retFrequency / 10;
    }
    
    public void setTestReceptionFrequency(int p_frequency) {
    	setTestReceptionFrequencyEx(p_frequency, false);
    }

    public void setTestReceptionFrequencyEx(int p_frequency,boolean abIsForHtv) {

        if (STUB_MODE) {
            ntf.notifyAllObservers(EventIDs.EVENT_PLPIDS_DETECTED, "");
        } else {
            int l_setFreq = p_frequency * 10;
            l_setFreq = (l_setFreq * 16) / 1000;
            // disable mheg if required
            m_isHierarchicalMuxFound = false;
            Log.d(TAG, "starting installation with frequency " + String.valueOf(l_setFreq));
			IsMajorVersionChange = false;
			currentInstallationMode = abIsForHtv?InstallationMode.HTV_DTR_INSTALLATION:InstallationMode.DTR_INSTALLATION;
            euInst.StartInstallation(1, l_setFreq, euInstConst.IHsvInstallation2_InstallationModeWeakSignal);
        }
    }

	public boolean isDTRStoreOptionAvailable() {
		boolean returnStatus = true;
		Log.d(TAG, "isDTRStoreOptionAvailable entry");

		String selectedCountryInTVS = getCountryNameFromTVS();
        NativeAPIEnums.DVBTOrDVBC selectedMediumInTVS = getSelectedDVBTOrDVBCFromTVS();
        
        if ((selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBC)
                && (countrySupportsDVBCFullorLite(selectedCountryInTVS) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Full)) {
        	
        	Log.d(TAG, "isDTRStoreOptionAvailable 1");
            if(selectedCountryInTVS.equalsIgnoreCase(ctx
                        .getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))){
            	Log.d(TAG, "isDTRStoreOptionAvailable 2");
                returnStatus = false;
            }else if(selectedCountryInTVS.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM)) && 
                    (getOperatorFromMW() == NativeAPIEnums.Operators.Telenet )){
            	Log.d(TAG, "isDTRStoreOptionAvailable 3");
                returnStatus = false;
            }else if(getOperatorFromMW() == NativeAPIEnums.Operators.UPC){
            	Log.d(TAG, "isDTRStoreOptionAvailable 4");
                returnStatus = false;
            } else if (getOperatorFromMW() == NativeAPIEnums.Operators.RCSRDS) {
				returnStatus = false;
			} else if(getOperatorFromMW() == NativeAPIEnums.Operators.CanalDigital){
				if(getWSFreqScanMode() == 0)
					returnStatus = false;
			}else if(getOperatorFromMW() == NativeAPIEnums.Operators.YouSee){
				if(getWSFreqScanMode() == 0)
					returnStatus = false;
			} else{
            	Log.d(TAG, "isDTRStoreOptionAvailable 5");
            }
        }
        Log.d(TAG, "isDTRStoreOptionAvailable " + returnStatus);
        return returnStatus;
	}

	public boolean IsHierarchialMuxFound() {
		Log.d(TAG,
				"IsHierarchialMuxFound returning "
						+ String.valueOf(m_isHierarchicalMuxFound));
		return m_isHierarchicalMuxFound;
	}

	public int toggleHierarchialMuxNetworkNumber() {
		int streamPriority = euInst.getSigStreamPriority();
		int newNetworkNumber = 0;
		
		Log.d(TAG, "toggleHierarchialMuxNetworkNumber streamPriority before "
				+ streamPriority);

		if (streamPriority == ITuningDvbT.TUNING_DVBT_STREAMPRIO_HIGH) {
			euInst.SetStreamPriority(ITuningDvbT.TUNING_DVBT_STREAMPRIO_LOW);
			newNetworkNumber = 2;
			Log.d(TAG, "toggleHierarchialMuxNetworkNumber streamPriority hight to low ");
		} else {
			euInst.SetStreamPriority(ITuningDvbT.TUNING_DVBT_STREAMPRIO_HIGH);
			newNetworkNumber = 1;
			Log.d(TAG, "toggleHierarchialMuxNetworkNumber streamPriority low to high ");
		}
		Log.d(TAG, "toggleHierarchialMuxNetworkNumber newNetworkNumber " + newNetworkNumber);
		return newNetworkNumber;
	}
	
	public int GetHierarchialMuxNetworkNumber() {
		int l_networkNumber = 0;
		int l_streamPriority = euInst.getSigStreamPriority();

		if (l_streamPriority == ITuningDvbT.TUNING_DVBT_STREAMPRIO_HIGH) {
			l_networkNumber = 1;
		} else if (l_streamPriority == ITuningDvbT.TUNING_DVBT_STREAMPRIO_LOW) {
			l_networkNumber = 2;
		}

		Log.d(TAG, "GetHierarchialMuxNetworkNumber returning "
				+ String.valueOf(l_networkNumber));
		return l_networkNumber;
	}

    public boolean AvailableCableMedium() {
        Log.d(TAG, "AvailableCableMedium entry");
        boolean l_ret = false;
        if (STUB_MODE) {

        } else {
            if (getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC) {
                l_ret = euInst.IsAvailable(euInstConst.IHsvInstallation2_InstallationModeWeakSignal, euInstConst.IHsvInstallation2_AttributeSymbolRate);
            }
            Log.d(TAG, "AvailableCableMedium returning " + String.valueOf(l_ret));
        }
        return l_ret;// TODO :
    }

	public long GetSymbolRateDisplay()
	{
		Log.d(TAG, "GetSymbolRateDisplay entry");
		long l_symbolRate = euInst.getSigSymbolRate();
		long l_ret = 0;
		l_ret = (l_symbolRate / 1000);
		Log.d(TAG,"GetSymbolRateDisplay returning " + String.valueOf(l_ret));
		return l_ret;
	}

	public String GetTestReceptionModulation() {
		Log.d(TAG, "GetTestReceptionModulation entry");
		int l_constellation = euInst.getSigConstellation();
		Log.d(TAG, "GetTestReceptionModulation 1");
		Log.d(TAG,
				"Constellation = " + String.valueOf(l_constellation));
		String l_retString = "";
		if( getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC) {
			Log.d(TAG, "GetTestReceptionModulation Cable");
			switch (l_constellation) {
			case ITuningDvbC.TUNING_DVBC_QAM16:
				Log.d(TAG, "TUNING_DVBC_QAM16");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.SERVICE_16_QAM);
				break;

			case ITuningDvbC.TUNING_DVBC_QAM32:
				Log.d(TAG, "TUNING_DVBC_QAM32");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.SERVICE_32_QAM);
				break;

			case ITuningDvbC.TUNING_DVBC_QAM64:
				Log.d(TAG, "TUNING_DVBC_QAM64");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.SERVICE_64_QAM);
				break;

			case ITuningDvbC.TUNING_DVBC_QAM128:
				Log.d(TAG, "TUNING_DVBC_QAM128");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.SERVICE_128_QAM);
				break;

			case ITuningDvbC.TUNING_DVBC_QAM256:
				Log.d(TAG, "TUNING_DVBC_QAM256");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.SERVICE_256_QAM);
				break;
			/*
			 * case ITuningDvbC.AutoModulation: l_retString =
			 * strSTR_MAIN_AUTOMATICID; break;
			 */

			default:
				break;
			}
		} else {
			Log.d(TAG, "GetTestReceptionModulation Anteena");
			switch (l_constellation) {
			case ITuningDvbT.TUNING_DVBT_CONSTELLATION_QAM16:
				Log.d(TAG, "TUNING_DVBT_CONSTELLATION_QAM16");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.SERVICE_16_QAM);
				break;

			case ITuningDvbT.TUNING_DVBT_CONSTELLATION_QAM64:
				Log.d(TAG, "TUNING_DVBT_CONSTELLATION_QAM64");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.SERVICE_64_QAM);
				break;

			case ITuningDvbT.TUNING_DVBT_CONSTELLATION_QAM256:
				Log.d(TAG, "TUNING_DVBT_CONSTELLATION_QAM256");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.SERVICE_256_QAM);
				break;
			/*
			 * case ITuningDvbT.AutoModulation: l_retString =
			 * strSTR_MAIN_AUTOMATICID; break;
			 */

			case ITuningDvbT.TUNING_DVBT_CONSTELLATION_QPSK:
				Log.d(TAG, "TUNING_DVBT_CONSTELLATION_QPSK");
				l_retString = ctx.getString(org.droidtv.ui.strings.R.string.MISC_QPSK);
				break;

			default:
				break;
			}
		}
		Log.d(TAG, "returning " + l_retString);
		return l_retString;
	}

	public int GetTestReceptionNoOfChannelsStored() {
		Log.d(TAG, "GetTestReceptionNoOfChannelsStored");
		return euInst.GetNumberOfDigitalChannelsFound();
	}

	public String GetTestReceptionNetworkName() {
		Log.d(TAG, "GetTestReceptionNetworkName entry");
		String l_ret = euInst.getNetworkName(0);
		// Mahesh to add an api
		/*
		 * 
		 * if(strapi_GetByKey(HsvMain, HSVSPID(NetworkName, dvb, nit),
		 * HSVINVALIDKEY, HSVINVALIDKEY, HSVINVALIDKEY, (void *)(NetworkName)))
		 * { //Valid Network name found } else { // GetByKey() failed. We will
		 * probably need to wait for notifications from SDMNetworkName = '\0'; }
		 */
		Log.d(TAG, "GetTestReceptionNetworkName returning "
				+ l_ret);
		return l_ret;
	}

	public void CancelTestReceptionInstallation() {
		Log.d(TAG, "CancelTestReceptionInstallation");
		m_isHierarchicalMuxFound = false;
		if (euInst.GetInstallationStatus() != euInstConst.IHsvInstallation2_StIdle) {

			euInst.StopInstallation();
		}
		euInst.ResetAttributeToDefault(
				euInstConst.IHsvInstallation2_InstallationModeWeakSignal,
				euInstConst.IHsvInstallation2_AttributeSymbolRate);
	}

	public void StoreTestReceptionInstallation() {
		Log.d(TAG, "StoreTestReceptionInstallation");
		if(STUB_MODE){
		    
		}else{
		    euInst.StoreWeakSignalInstallationChannel();
		}
	}

	public long GetTestReceptionSignalQuality() {
		long l_ret;
		// l_ret =
		// euInst.GetSignalstrength(euInstConst.IHsvInstallation2_InsQssm);
		//l_ret = euInst.getSignalStrenght(euInstConst.IHsvInstallation2_InsQssm);
		l_ret = euInst.getSignalQuality();
		Log.d(TAG, "GetTestReceptionSignalQuality returning "
				+ String.valueOf(l_ret));
		return l_ret;
	}

	public int GetSignalQualityBer() {
		Log.d(TAG, "GetSignalQualityBer entry");
		int l_ret = euInst.getSignalBer();
		Log.d(TAG,
				"GetSignalQualityBer returning " + String.valueOf(l_ret));
		return l_ret;

	}

	public int GetSignalStrength() {
		int l_ret;
		Log.d(TAG, "GetSignalStrength entry");
		// l_ret =
		// (int)euInst.GetSignalstrength(euInstConst.IHsvInstallation2_InsVssm);
		l_ret = (int) euInst
				.getSignalStrenght(euInstConst.IHsvInstallation2_InsVssm);
		Log.d(TAG,
				"GetSignalStrength returning " + String.valueOf(l_ret));
		return l_ret;
	}

	public boolean AvailableStandbyChannelUpdate() {
		Log.d(TAG, "AvailableStandbyChannelUpdate entry ");
		//boolean l_ret = false;
		/*
		 * if((value == MiscEnumStandbyUpdateOff)&&(FALSE ==
		 * ceapmnuctrl_IsMenuControllable
		 * (ceapmnuctrl_StandbyUpdateChannelsMenu))) { return FALSE;
		 * 
		 * }
		 * 
		 * return
		 * ceapmnuctrl_IsMenuAvailable(ceapmnuctrl_StandbyUpdateChannelsMenu);
		 */
		//String[] l_countryList = getSortedCountyList();
		/*boolean l_isCountryNetherlands = l_countryList[getSelectedCountyID()]
				.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS));*/
		/*
		 * (Netherlands - cable and operator Ziggo/Other)
		 */
		Log.d(TAG, "AvailableStandbyChannelUpdate exit ");
		return true;
	}

	public boolean AvailableStartUpMsg() {
		boolean l_ret = true;
		// return
		// ceapmnuctrl_IsMenuAvailable(ceapmnuctrl_UpdateInstallStartUpMessageMenu);
		return l_ret;
	}

    public boolean IsDvbInstallationAvailable() {
        Log.d(TAG, "IsDvbInstallationAvailable entry ");
        boolean l_ret = true;
        if (STUB_MODE) {
            l_ret = true;
        } else {
            String l_selectedCountry = getCountryNameFromTVS();
            NativeAPIEnums.DVBTOrDVBCMacro l_dvbtSupport = countrySupportsDVBTFullorLite(l_selectedCountry);
            NativeAPIEnums.DVBTOrDVBCMacro l_dvbcSupport = countrySupportsDVBCFullorLite(l_selectedCountry);
            if ((l_dvbtSupport == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_NotSupported) && (l_dvbcSupport == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_NotSupported)) {
                l_ret = false;
            }
        }
        Log.d(TAG, "IsDvbInstallationAvailable returning " + String.valueOf(l_ret));
        return l_ret;
    }

	public boolean IsSymbolRateModeAvailable() {
        Log.d(TAG, "IsSymbolRateModeAvailable entry ");
        boolean l_ret = false;
        if (STUB_MODE) {
            l_ret = true;
        } else {
            String l_selectedCountry = getCountryNameFromTVS();
            NativeAPIEnums.DVBTOrDVBCMacro l_dvbcSupport = countrySupportsDVBCFullorLite(l_selectedCountry);
            if (getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC) {
                Log.d(TAG, "medium is cable ");
                if ((l_dvbcSupport == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Full) || (l_dvbcSupport == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)) {
                    Log.d(TAG, "support for full/light available ");
                    l_ret = true;
                }
            }
        }
        Log.d(TAG, "IsSymbolRateModeAvailable returning " + String.valueOf(l_ret));
        return l_ret;
    }

	public boolean IsPredefinedSymbolRateAvailable() {
		boolean l_ret = true;
		if (getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC) {
			// l_ret = (macrodiv_MacroGetDVBBitVector(macrodiv_MacroDVBCFull |
			// macrodiv_MacroDVBCLight));
		}
		return l_ret;
	}

	public boolean IsAPMEARegionAvailable() // CR :RMCR-3078
	{
		boolean l_ret = false;
		int regionBit = 0;

		regionBit = mTvSettingsManager.getInt(TvSettingsConstants.OPREGION, 0,0);
    	
		Log.d(TAG,"regionBit ="+regionBit);
		if(regionBit == TvSettingsDefinitions.OpRegionDisplayConstants.APMEA){ // APPMEA Region
			l_ret = true;
		}
		Log.d(TAG,"IsAPMEARegionAvailable returning " + String.valueOf(l_ret));
		return l_ret;
	}

	public boolean AvailableInstallationMode() {
		return euInst
				.IsMediumSupported(euInstConst.IHsvInstallation2_Terrestrial);
	}

	public boolean ControllableStandbyChannelUpdate() {
		boolean l_ret = true;
		String[] l_countryList = getSortedCountyList();
		boolean l_isCountryNetherlands = l_countryList[getSelectedCountyID()]
				.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS));
		if(( getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC)
				&& l_isCountryNetherlands) {
			l_ret = false;
		}
		// return
		// ceapmnuctrl_IsMenuControllable(ceapmnuctrl_StandbyUpdateChannelsMenu);
		// in ceapps\prod\ceapjagconfig\mmacro_m.c
		return l_ret;
	}

    public boolean isSymbolRateModeControllable() {
        Log.d(TAG, "isSymbolRateModeControllable entry ");
        boolean l_ret = false;
        if (STUB_MODE) {
            l_ret = true;
        } else {
            int l_attr = euInst.GetAttribute(euInstConst.IHsvInstallation2_InstallationModeAutomatic, euInstConst.IHsvInstallation2_AttributeDigitalOption);
            {
                if (l_attr > 0) {
                    l_ret = true;
                }
            }
        }
        Log.d(TAG, "isSymbolRateModeControllable returning " + String.valueOf(l_ret));
        return l_ret;
    }

    public boolean isSymbolRateControllable() {
        Log.d(TAG, "isSymbolRateControllable entry ");
        boolean l_ret = false;
        if (STUB_MODE) {
            l_ret = true;
        } else {
            if (isSymbolRateModeControllable()) {
                int l_attr = euInst.GetAttributeMode(euInstConst.IHsvInstallation2_InstallationModeWeakSignal, euInstConst.IHsvInstallation2_AttributeSymbolRate);
                if (l_attr == euInstConst.IHsvInstallation2_ManualValue) {
                    l_ret = true;
                }
            }
        }
        Log.d(TAG, "isSymbolRateControllable returning " + String.valueOf(l_ret));
        return l_ret;
    }
    public boolean isDTRMenuControllable()
    {
    	Log.d(TAG,"isDTRMenuControllable entry");
    	boolean l_ret = true;
    	if (getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC)
    	{
    		if(!ifDigitalOptionOn())
    		{
    			l_ret = false;
    		}
    	}
    	Log.d(TAG,"isDTRMenuControllable returning " + l_ret);
    	return l_ret;
    }
    
	public boolean ifQuickInstallation() {
		boolean returnStatus = false;

		if (euInstConst.IHsvInstallation2_QuickScan == euInst.GetAttribute(
				euInstConst.IHsvInstallation2_InstallationModeAutomatic,
				euInstConst.IHsvInstallation2_AttributeScanMode)) {
			returnStatus = true;
		}
		Log.d(TAG, "ifQuickInstallation returnStatus " + returnStatus);
		return returnStatus;
	}
    
    public boolean ifChannelFrequncyNumberAvail(){
    	boolean returnStatus = false;
    	
    	/* CR:AN-21406
    	 * 	- NorDig countries (Sweden/Norway/Denmark/Finland)
			- Terrestrial installation based on quick frequency scan (grid scan) and full frequency scan (tuner band scan)
			- DVB-T/T2 channels (analog excluded)
		*/
    	
    	String storedCountryName = getCountryNameFromTVS();
    	DVBTOrDVBC storedMedium = getSelectedDVBTOrDVBCFromTVS();
    	Log.d(TAG, "storedCountryName: " + storedCountryName + " ,storedMedium: " + storedMedium);
    	
    	if (((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN))) ||
				  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) ||
				  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))) ||
				  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND))) ||
				  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))/*TF515PHIALLMTK02-53(301521)*/) || 
				  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ESTONIA)))/*TF515PHIALLMTK02-52(301520)*/) &&
				  (storedMedium == DVBTOrDVBC.DVBT)
				  ) {
    		returnStatus = true;
    	}

    	Log.d(TAG, "ifChannelFrequncyNumberAvail returnStatus " + returnStatus);
		return returnStatus;
    }

	public boolean ifAutomaticUpOptNChannelUpAvail() {
		boolean returnStatus = true;
		Log.d(TAG, "ifAutomaticUpOptNChannelUpAvail entry ");
		if (STUB_MODE) {
			returnStatus = true;
		} else {
			String selectedCountryInTVS = getCountryNameFromTVS();
			NativeAPIEnums.DVBTOrDVBC selectedMediumInTVS = getSelectedDVBTOrDVBCFromTVS();
			// for DVB-T light countries function should return false
			if ((selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBT)
					&& (countrySupportsDVBTFullorLite(selectedCountryInTVS) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light)) {
				returnStatus = false;
			}
		}
		Log.d(TAG, "ifAutomaticUpOptNChannelUpAvail returning " + returnStatus);
		return returnStatus;
	}

    public boolean isNotNetherlandsAndCable() {
        Log.d(TAG, "isNotNetherlandsAndCable entry ");
        boolean l_ret = true;
        if (STUB_MODE) {
            l_ret = true;
        } else {
            String[] l_countryList = getSortedCountyList();
            boolean l_isCountryNetherlands = l_countryList[getSelectedCountyID()].equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS));
            if ((getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC) && l_isCountryNetherlands) {
                l_ret = false;
            }
            
            
        }
        Log.d(TAG, "isNotNetherlandsAndCable returning " + String.valueOf(l_ret));
        // return
        // ceapmnuctrl_IsMenuControllable(ceapmnuctrl_StandbyUpdateChannelsMenu);
        // in ceapps\prod\ceapjagconfig\mmacro_m.c
        return l_ret;
    }

	public void SetStandbyUpdate(boolean p_setStandbyUpdateOn) {
		Log.d(TAG, "SetStandbyUpdate entry ");
		if (p_setStandbyUpdateOn) {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSTANDBYCHANNELUPDATE, 0, 1);
		} else {
			networkChangeDetected(false);
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSTANDBYCHANNELUPDATE, 0, 0);
		}

		Log.d(TAG, "SetStandbyUpdate exit ");
	}
	
	public void channelsUpdated(boolean ifChannelsUpdated){
		if (ifChannelsUpdated) {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSNETWORKCHANGEDDETECTED, 0, 1);
		} else {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSNETWORKCHANGEDDETECTED, 0, 0);
		}
		Log.d(TAG, "channelsUpdated " + ifChannelsUpdated);
	}
	
	public boolean ifChannelsUpdated(){
		boolean returnStatus = false;

		if (mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSNETWORKCHANGEDDETECTED, 0, 0) == 1) {
			returnStatus = true;
		} else {
			returnStatus = false;
		}

		Log.d(TAG, "ifChannelsUpdated " + returnStatus);
		return returnStatus;
		
	}
	
	public void networkChangeDetected(boolean ifChangeDetected) {
		// set if network change is detected during background installation
		if (ifChangeDetected) {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSNETWORKCHANGEDDETECTEDCABLE, 0, 1);
		} else {
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSNETWORKCHANGEDDETECTEDCABLE, 0, 0);
		}
		Log.d(TAG, "networkChangeDetected " + ifChangeDetected);
	}

	public boolean ifChannelUpdateON() {
		boolean returnStatus = false;

		if (mTvSettingsManager.getInt(TvSettingsConstants.STARTUPMESSAGE, 0, 0) == 1) {
			returnStatus = true;
		} else {
			returnStatus = false;
		}

		Log.d(TAG, "ifChannelUpdateON " + returnStatus);
		return returnStatus;
	}
	
	public boolean ifNetworkChangeDetected() {
		boolean returnStatus = false;

		if (mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSNETWORKCHANGEDDETECTEDCABLE, 0, 0) == 1) {
			returnStatus = true;
		} else {
			returnStatus = false;
		}

		Log.d(TAG, "ifNetworkChangeDetected " + returnStatus);
		return returnStatus;
	}

	public int GetStandbyUpdate() {
		Log.d(TAG, "SetStandbyUpdate entry ");
		int l_ret = mTvSettingsManager.getInt(
				TvSettingsConstants.INSTSETTINGSSTANDBYCHANNELUPDATE, 0, 0);
		Log.d(TAG,
				"GetStandbyUpdate exit " + String.valueOf(l_ret));
		return l_ret;
	}

	public void SetStartUpMsg(boolean p_setStartUpMsgeOn) {
		Log.d(TAG, "SetStartUpMsg entry ");
		if (p_setStartUpMsgeOn) {
			mTvSettingsManager.putInt(TvSettingsConstants.STARTUPMESSAGE, 0, 1);
		} else {
			mTvSettingsManager.putInt(TvSettingsConstants.STARTUPMESSAGE, 0, 0);
		}
		
		Log.d(TAG, "SetStartUpMsg exit ");
	}

	public int GetStartUpMsg() {
		Log.d(TAG, "GetStartUpMsg entry ");

		int l_ret = mTvSettingsManager.getInt(TvSettingsConstants.STARTUPMESSAGE, 0, 0);

		Log.d(TAG, "GetStartUpMsg exit " + String.valueOf(l_ret));
		return l_ret;
	}
	
	public boolean ifStoreAsNewChannelEnabled(){
		Log.d(TAG, "ifStoreAsNewChannelEnabled: " + mStoreAsNewChannelEnabled);
		return mStoreAsNewChannelEnabled;
	}

	public void setStoreAsNewChannelStatus(boolean argIfEnabled){
		mStoreAsNewChannelEnabled = argIfEnabled;
		Log.d(TAG, "setStoreAsNewChannelStatus: " + mStoreAsNewChannelEnabled);
	}
	
	public void loadCurrentAnalogValues()
	{

		int currentChannelID = mTvSettingsManager.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC, 0, 0);

		String[] projection = new String[] {Channels.COLUMN_DISPLAY_NUMBER, Channels.COLUMN_TYPE };
		String mselection = Channels._ID + "= ?" + " AND " + Channels.COLUMN_TYPE + "=?";
		String[] mselectionargs = new String[] { String.valueOf(currentChannelID), Channels.TYPE_PAL };

		Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

		if (cursor != null) 
		{
			if (cursor.getCount() > 0) {
				cursor.moveToFirst();
				m_lastSelectedPresetTC = cursor.getInt(0);
				Log.d(TAG, "IsAnalogPresetExists m_lastSelectedPresetTC " + m_lastSelectedPresetTC);
			}
			cursor.close();
			cursor=null;
		} else {
			Log.d(TAG, "cursor NULL, no channel in tv.db with _ID ");
		}

		analogSystemCountry = getAnalogSystemFromSharedPref();
	}
	
	public boolean IsCurrentChannelAnalog() 
	{
		Log.d(TAG, "IsCurrentChannelAnalog entry");
		boolean returnStatus = false;

		int currentChannelID = mTvSettingsManager.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC, 0, 0);

		String[] projection = new String[] {Channels.COLUMN_DISPLAY_NUMBER, Channels.COLUMN_TYPE };
		String mselection = Channels._ID + "= ?" + " AND " + Channels.COLUMN_TYPE + "=?";
		String[] mselectionargs = new String[] { String.valueOf(currentChannelID), Channels.TYPE_PAL };

		Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

		if (cursor != null) 
		{
			if (cursor.getCount() > 0) 
			{
				returnStatus = true;
			}
			cursor.close();
			cursor=null;
		}
		else 
		{
			Log.d(TAG, "cursor NULL, no channel in tv.db with _ID ");
		}

		
		Log.d(TAG, "IsCurrentChannelAnalog exit with returnStatus" + returnStatus);
		return returnStatus;
	}
	
	public int GetManualSearchFrequency(){
		Log.d(TAG,"GetManualSearchFrequency entry");
		int lastSelectedPreset = 0;			
		int mFrequency = 0;
		Uri tableName;
		String selection;
		String selectionArgs[];
		String projection[];
		
		NativeAPIEnums.DVBTOrDVBC selectedMedium = getSelectedDVBTOrDVBCFromTVS();
		int lastSelectedTuner = mTvSettingsManager.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		Log.d(TAG,"lastSelectedTuner = " + lastSelectedTuner);
		
		if(lastSelectedTuner == TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC){
			lastSelectedPreset = mTvSettingsManager.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC, 0, 0);
			Cursor cursor;
			
			if (selectedMedium == DVBTOrDVBC.DVBT) {
				tableName = IChannelContract.CONTENT_URI_TerChannelMap;
			} else {
				tableName = IChannelContract.CONTENT_URI_CabChannelMap;
			}
			
			Log.d(TAG,"GetManualSearchFrequency lastSelectedPreset: " + lastSelectedPreset);
			
			projection = new String[] { IChannelContract.C_FREQUENCY};
			selection = IChannelContract.C_PRESETTYPE + "=?" + " AND " + IChannelContract.C_PRESET_ID + "=?";
			selectionArgs = new String[] { "" + IChannelContract.PresetType.PRESET_TYPE_ANALOG.ordinal(), Integer.toString(lastSelectedPreset) };
			
			cursor = ctx.getContentResolver().query(tableName, projection, selection, selectionArgs, null);

			if (cursor != null) {
				try
				{
				Log.d(TAG,"GetManualSearchFrequency cursor length:" + cursor.getCount());
				while(cursor.moveToNext()) { 
					mFrequency=cursor.getInt(0);
					break;
				}
				}finally{
				   cursor.close();
				   cursor=null;
				}
			}
		}
		
		Log.d(TAG,"GetManualSearchFrequency mFrequncy:" + mFrequency);
		
		int minFreq[] = new int[2];
		int maxFreq[] = new int[2];
		euInst.getFreqRange_JavInst(minFreq, maxFreq);
		if (mFrequency < minFreq[0]) {
			mFrequency = minFreq[0];
			Log.d(TAG, "GetManualSearchFrequency min =   " + minFreq[0]);
		} else if (mFrequency > maxFreq[0]) {
			mFrequency = maxFreq[0];
			Log.d(TAG, "GetManualSearchFrequency Max =   " + maxFreq[0]);
		}
        
		
		Log.d(TAG,"GetManualSearchFrequency returning " + mFrequency);
		return mFrequency ;
	}
	
	public void getFrequencyRange(int freqValue[])
	{
		Log.d(TAG,"getFrequency_Range entry");
		int l_minFreq[] = new int[2];
		int l_maxFreq[] = new int[2];
		euInst.getFreqRange_JavInst(l_minFreq, l_maxFreq);
		freqValue[0] = l_minFreq[0];
		freqValue[1] = l_maxFreq[0];
		Log.d(TAG,"getFrequency_Range exit");
	}
	public int GetSearchFrequency()
	{
		Log.d(TAG,"GetSearchFrequency entry");
		int m_lastSelectedPreset = 0;			
		int mFrequncy = 0;
		int l_lastSelectedTuner = mTvSettingsManager.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		Log.d(TAG,"l_lastSelectedTuner = " + l_lastSelectedTuner);
		if (l_lastSelectedTuner == 0)
		{
			m_lastSelectedPreset = mTvSettingsManager.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC, 0, 0);
			Log.d(TAG,"m_lastSelectedPreset = " + m_lastSelectedPreset);
			
			String[] mProjection = new String[] {TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA };			
			String mSelecion  = TvContract.Channels._ID+" = ?"+" AND "+Channels.COLUMN_VERSION_NUMBER+"= ?";	
			String[] mSelectionArgs;
			
			if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
			  	mSelectionArgs = new String[]{Integer.toString(m_lastSelectedPreset),Integer.toString(1)};
			} else {
				mSelectionArgs = new String[]{Integer.toString(m_lastSelectedPreset),Integer.toString(0)};
			}
				
			Cursor cursor   = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI,mProjection,mSelecion,mSelectionArgs, null);
			if(cursor != null) {
				try{
				while(cursor.moveToNext()) { 
					byte[] BlobData		 = cursor.getBlob(0);
					if(BlobData != null)  {
						IIntKeyValueables keyvals	 = IIntKeyValueables.Instance.getInterface();
						try{
							keyvals.setBlob(BlobData);
						}catch(Exception e){
							Log.d(TAG, "parseBlobData - CAUGHT EXCEPTION keyvals=null");
							keyvals = null;
						}

						if(keyvals != null){
							mFrequncy = keyvals.getInt(ITvContractExtras.C_FREQUENCY);
						}
					}
				}
				}finally{
				   cursor.close();
				   cursor=null;
				}
			}
		}
			
		Log.d(TAG,"GetSearchFrequency returning " + mFrequncy);
		return mFrequncy ;
	}
		
	public void updateUserEnteredManualFreq(int argFreq) {
		Log.d(TAG, "updateUserEnteredManualFreq entered with: " + argFreq);

		int minFreq[] = new int[2];
		int maxFreq[] = new int[2];
		euInst.getFreqRange_JavInst(minFreq, maxFreq);
		if (argFreq < minFreq[0]) {
			argFreq = minFreq[0];
			Log.d(TAG, "updateUserEnteredManualFreq min =   " + minFreq[0]);
		} else if (argFreq > maxFreq[0]) {
			argFreq = maxFreq[0];
			Log.d(TAG, "updateUserEnteredManualFreq Max =   " + maxFreq[0]);
		}
		argFreq = (argFreq / 1000) << 4;
		mSearchingFrequency = argFreq;
		euInst.SetManualFrequency( mSearchingFrequency, 0, true ); 
		
		Log.d(TAG, "updateUserEnteredManualFreq mSearchingFrequency: " + mSearchingFrequency);
	}
	
	public void startFreqSearch(){
		Log.d(TAG,"startFreqSearch start");
		Thread l_initThread = new Thread(new Runnable()
		{
			public void run()
			{
				euInst.StartFrequencySearch();
			}
		});
		l_initThread.setPriority(Process.THREAD_PRIORITY_BACKGROUND);
		l_initThread.start();

		//euInst.StartFrequencySearch();
		Log.d(TAG,"startFreqSearch end");
	}
	/*public void StartManualInstall(){
		Log.d(TAG, "StartManualInstall mSearchingFrequency: " + mSearchingFrequency);
		//StartHyInstallation(euInstConst.IHsvInstallation2_InstallationModeManual);
		if (((euInst.GetInstallationStatus() == euInstConst.IHsvInstallation2_InstallationStateInProgress) || (euInst
				.GetInstallationStatus() == euInstConst.IHsvInstallation2_InstallationStateScrambledSearch))
				&& (euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModeManual)
				&& (euInst.getIfManInstStart())) {
			euInst.StartFrequencySearch();
			Log.d(TAG, "StartFrequencySearch called");
		} else {
			//euInst.setIfManInstStart(true);
			StartHyInstallation(euInstConst.IHsvInstallation2_InstallationModeManual);
		}
		Log.d(TAG, "SetFrequency Exit");
	}*/
	/*
	public void SetFrequency(int p_freq)
	{
		Log.d(TAG,"SetFrequency entered with  "+ p_freq);
	//	ManualFreqSet = true;
	        if ( euInst.GetManualInstallationMode( ) == euInstConst.IHsvInstallation2_ManualInstallationModeFrequency )
	        {
				Log.d(TAG,"SetFrequency p_freq =  "+ p_freq );
				int minFreq[] = new int[2];
				int maxFreq[] = new int[2];
				euInst.getFreqRange_JavInst(minFreq, maxFreq);
	            if(p_freq < minFreq[0])
	            {
	            	p_freq = minFreq[0];
					Log.d(TAG,"SetFrequency min =   "+ minFreq[0]);
	            }
	            else if(p_freq > maxFreq[0])
	            {
	            	p_freq = maxFreq[0];
	                Log.d(TAG,"SetFrequency Max =   "+ maxFreq[0] );
	            }
				p_freq = (p_freq/1000) << 4;
				Log.d(TAG,"SetFrequency p_freq =  "+ p_freq );
	            mSearchingFrequency = p_freq;
	            Log.d(TAG,"SetFrequency mSearchingFrequency =  "+ mSearchingFrequency );
		        Log.d(TAG,"SetFrequency euInst.getIfManInstStart() returned =  "+ euInst.getIfManInstStart() );
			
				if (euInst.getIfManInstStart() == false)
				{
					 Log.d(TAG,"SetManualFrequency called with  "+ mSearchingFrequency );
	                euInst.SetManualFrequency( p_freq, 0, true ); 
				}					
				Log.d(TAG,"SetFrequency Status =   "+ euInst.GetInstallationStatus() );
                Log.d(TAG,"SetFrequency Mode =   "+ euInst.GetInstallationMode() );

	            if(((euInst.GetInstallationStatus() == euInstConst.IHsvInstallation2_InstallationStateInProgress) ||
	                (euInst.GetInstallationStatus() == euInstConst.IHsvInstallation2_InstallationStateScrambledSearch)) &&
	                (euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModeManual) && (euInst.getIfManInstStart()))
	            {
	                euInst.StartFrequencySearch();
	                Log.d(TAG,"StartFrequencySearch called");
	            }
	            else
	            {
					euInst.setIfManInstStart(true);
	                StartHyInstallation(euInstConst.IHsvInstallation2_InstallationModeManual);
	            }
	        }
	        Log.d(TAG,"SetFrequency exit");
	   
	}
	*/
	public int GetFrequency()
	{
		Log.d(TAG,"GetFrequency entry");
		int lReturn = 0;
		//int mSearchingFrequency=0;
		int freqArray[] = new int[2];
         euInst.getFreq_JavInst(freqArray);
         lReturn = freqArray[0];
		/*if((mSearchingFrequency >= euInst.GetMinFrequency()) && (mSearchingFrequency <= euInst.GetMaxFrequency()))
		{
			lReturn = (int)(mSearchingFrequency >> 4);
		}
		else*/
		{
			//lReturn = (int)(euInst.GetTunerFrequency() >> 4 ); // Right shift by 4 is same as divide by 16
		}
		Log.d(TAG,"GetFrequency returning " + lReturn);
		return lReturn ;
	}
	
	public void StopManualSearch()
	{
		Log.d(TAG,"StopManualSearch entry ");
		//int l_installationStatus = euInst.GetInstallationStatus();

		/*if (((l_installationStatus == euInstConst.IHsvInstallation2_InstallationStateInProgress) || (l_installationStatus == euInstConst.IHsvInstallation2_InstallationStateScrambledSearch
))
				&& (euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModeManual))
		{
			Log.d(TAG,"StopManualSearch stop triggered ");
			euInst.StopInstallation();
		}*/
		
		euInst.StopInstallation();
		Log.d(TAG,"StopManualSearch exit ");

	}
	
	public void StopInstallationIfNotIdle(){
		if (euInst.GetInstallationStatus() != euInstConst.IHsvInstallation2_StIdle) {
			euInst.StopInstallation();
		}
	}
	
	public void StartManualSearch()
	{
		Log.d(TAG,"StartManualSearch entry ");
		int l_installationStatus = euInst.GetInstallationStatus();  
		if(euInst.IsManualInstallationModeSupported(euInstConst.IHsvInstallation2_ManualInstallationModeFrequency))
		{
			if(((l_installationStatus == euInstConst.IHsvInstallation2_InstallationStateInProgress) || 
				(l_installationStatus == euInstConst.IHsvInstallation2_InstallationStateScrambledSearch)) && 
				(euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModeManual))
			{
				euInst.StartFrequencySearch();
			}
			else
			{
				this.StartHyInstallation(euInstConst.IHsvInstallation2_InstallationModeManual);
			}           
		}
		Log.d(TAG,"StartManualSearch exit ");
	}
	
	public void AbortManualInstall()
	{
		Log.d(TAG,"AbortManualInstall entry ");
		int l_installationStatus = euInst.GetInstallationStatus();

		if (((l_installationStatus == euInstConst.IHsvInstallation2_InstallationStateInProgress) || (l_installationStatus == euInstConst.IHsvInstallation2_InstallationStateScrambledSearch
))
			&& (euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModeManual))
		{
			euInst.StopInstallation();
		}
		Log.d(TAG,"AbortManualInstall exit ");
		// event_OnEvent(evids_HyInsShowSearchBeforeString);

	}

	public void IncrementFineTune()
	{
		Log.d(TAG,"IncrementFineTune entry ");
		if (euInst.GetManualInstallationMode() == euInstConst.IHsvInstallation2_ManualInstallationModeFrequency)
		{
			SetFineTuneFrequency(1);
		}
		Log.d(TAG,"IncrementFineTune exit ");
	}
	

	public void DecrementFineTune()
	{
		Log.d(TAG,"DecrementFineTune entry ");
		if (euInst.GetManualInstallationMode() == euInstConst.IHsvInstallation2_ManualInstallationModeFrequency)
		{
			SetFineTuneFrequency(-1);
		}
		Log.d(TAG,"DecrementFineTune exit ");
	}
	
	public void SetFineTuneFrequency(int  p_value)
	{
		Log.d(TAG,"SetFineTuneFrequency entry " + p_value);
		int TunerFreq = 0;
		int NewTunerFreq = 0;

		TunerFreq = euInst.GetTunerFrequency(); 
		NewTunerFreq = TunerFreq + p_value;

		if ( (NewTunerFreq >= (euInst.GetMinFrequency())) && (NewTunerFreq <= (euInst.GetMaxFrequency())) )
		{
			euInst.SetManualFrequency( NewTunerFreq,0, false);
			euInst.SetManualInstallationMode( euInstConst.IHsvInstallation2_InstallationModeManual );

			if(((euInst.GetInstallationStatus() == euInstConst.IHsvInstallation2_InstallationStateInProgress) || 
				(euInst.GetInstallationStatus() == euInstConst.IHsvInstallation2_InstallationStateScrambledSearch)) && 
				(euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModeManual))
			{
				euInst.StartFrequencySearch();
			}
			else
			{
				this.StartHyInstallation(euInstConst.IHsvInstallation2_InvalidFrequency);
			}
		}
		Log.d(TAG,"SetFineTuneFrequency exit ");
	}

	public int GetFineTuneFrequency(int prop, int index)
	{  
		Log.d(TAG,"GetFineTuneFrequency entry ");
		return (euInst.GetTunerFrequency());
	}

	public void StartHyInstallation(int mode)
	{
		Log.d(TAG,"StartHyInstallation entry ");
		if(euInst.GetInstallationStatus() == euInstConst.IHsvInstallation2_InstallationStateIdle)
		{
			//euInst.bindChannelVersionManagerService();
			IsMajorVersionChange = false;
			euInst.StartInstallation(euInstConst.IHsvAppApiMainTuner, 0,mode);
		    Log.d(TAG,"StartInstallation called ");
		}
		else
		{
			euInst.StopInstallation();
			Log.d(TAG,"StopInstallation called ");
		}
		Log.d(TAG,"StartHyInstallation exit ");
	}


	public void ExitManualInstall() {
		Log.d(TAG, "ExitManualInstall entry ");
		// RestartInstallRequested = FALSE;
		int l_installationStatus = euInst.GetInstallationStatus();

		if (((l_installationStatus == euInstConst.IHsvInstallation2_InstallationStateInProgress) || 
				(l_installationStatus == euInstConst.IHsvInstallation2_InstallationStateScrambledSearch))
				&& (euInst.GetInstallationMode() == euInstConst.IHsvInstallation2_InstallationModeManual)) {
			euInst.StopInstallation();
		}

		Log.d(TAG, "ExitManualInstall exit ");
	}

	public void SwitchToAnalogUsecase() // //MW : support not available yet
	{
		Log.d(TAG, "SwitchToAnalogUsecase entry ");
		euInst.setSessionTuneWithMedium(SESSION_MEDIUM.ANALOG);
		Log.d(TAG, "SwitchToAnalogUsecase exit ");
	}
	
	public boolean isAnalogSwitchComplete()
	{
		Log.d(TAG, "isAnalogSwitchComplete returning  " + analogSourceSetupDone);
		return analogSourceSetupDone;
	}

	public void DetectTvSystem(int p_tvSystem) {
		Log.d(TAG, "SetTvSystem entry " + p_tvSystem);

		{
			euInst.DetectTvSystemIdID(p_tvSystem);
		}
		Log.d(TAG, "SetTvSystem exit ");
	}
	
	public void updateCachedAnalogSytemCountry(){
		int tvSystemId = euInst.getTVSystemID();
		if(tvSystemId == euInstConst.IHsvInstallation2_InsTvSystemBg){
			analogSystemCountry = AnalogSystemCountry.WEST_EUROPE;
		}else if(tvSystemId == euInstConst.IHsvInstallation2_InsTvSystemDk){
			analogSystemCountry = AnalogSystemCountry.EAST_EUROPE;
		}else if(tvSystemId == euInstConst.IHsvInstallation2_InsTvSystemI){
			analogSystemCountry = AnalogSystemCountry.UK;
		}else if(tvSystemId == euInstConst.IHsvInstallation2_InsTvSystemL){
			analogSystemCountry = AnalogSystemCountry.FRANCE;
		}else{
			// default case 
			analogSystemCountry = AnalogSystemCountry.EAST_EUROPE;
		}
		
		setAnalogSystemFromSharedPref(analogSystemCountry);
		Log.d(TAG, "updateCachedAnalogSytemCountry " + analogSystemCountry);
	}

   	public AnalogSystemCountry getCachedAnalogSytemCountry(){
   		Log.d(TAG, "getCachedAnalogSytemCountry " + analogSystemCountry);
   		return analogSystemCountry;
   	}
   	
   	public void setCachedAnalogSytemCountry(AnalogSystemCountry argCountry){
   		Log.d(TAG, "setCachedAnalogSytemCountry " + argCountry);
   		analogSystemCountry = argCountry;
   		
   		switch(analogSystemCountry){
   		case WEST_EUROPE:
   			euInst.setTVSystemID(euInstConst.IHsvInstallation2_InsTvSystemBg);
			break;
		case EAST_EUROPE:
			euInst.setTVSystemID(euInstConst.IHsvInstallation2_InsTvSystemDk);
			break;
		case UK:
			euInst.setTVSystemID(euInstConst.IHsvInstallation2_InsTvSystemI);
			break;
		case FRANCE:
			euInst.setTVSystemID(euInstConst.IHsvInstallation2_InsTvSystemL);
			break;
		default:
			break;
   		}
   		
   		setAnalogSystemFromSharedPref(analogSystemCountry);
   	}
	
	public void StoreManualInstallOnCurrentChannel() /* StoreManualInstallValues */
	{
		Log.d(TAG, "StoreManualInstallOnCurrentChannel entered " + m_lastSelectedPresetTC);
		euInst.StoreManualInstallationValues(m_lastSelectedPresetTC);
		Log.d(TAG, "StoreManualInstallOnCurrentChannel exit");
	}

	public void StoreManualInstallAsNewChannel() {
		Log.d(TAG, "AutoStoreManualInstallationValues entered ");

		euInst.AutoStoreManualInstallationValues();
		// mManualInstallTuneToPrevPreset = FALSE;
		// StoreAsNewPreset = TRUE;

	}

	public void SetFavoriteReorder() {
		Log.d(TAG, "SetFavoriteReorder entry ");

		// amsvc_RequestActivity( amLib_ACT_ReorderChannels, amLib_ACT_Start, 0
		// );
		Log.d(TAG, "SetFavoriteReorder exit ");

	}
	/*
	public void SetInstalledMedium(NativeAPIEnums.DVBTOrDVBC argInstallMode) {
		Log.d(TAG, "SetInstalledMedium entry ");
		
		Log.d(TAG, "SetInstalledMedium " + argInstallMode);
		if(argInstallMode == DVBTOrDVBC.DVBC){
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 1);
			setDVBTOrDVBC(argInstallMode);
		}else if(argInstallMode == DVBTOrDVBC.DVBT){
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
			setDVBTOrDVBC(argInstallMode);
		}
	}*/

	public boolean isDVBTLightSupported() {
		boolean l_ret = false;
		String l_selectedCountry = getCountryNameFromTVS();
		if (countrySupportsDVBTFullorLite(l_selectedCountry) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light) {
			l_ret = true;
		}
		return l_ret;
	}

	public boolean isDVBT2Supported() {
		boolean l_ret = false;
		String l_selectedCountry = getCountryNameFromTVS();
		NativeAPIEnums.DVBTOrDVBCMacro l_fullOrLight = countrySupportsDVBTFullorLite(l_selectedCountry);
		if ((l_fullOrLight == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light)
				|| (l_fullOrLight == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Full)) {
			l_ret = true;
		}
		return l_ret;
	}
	public void setCamUpdateModeFlag(boolean p_isCamUpdateMode)
	{
		Log.d(TAG,"setCamUpdateModeFlag entry with " + p_isCamUpdateMode);
		m_isCamUpdateMode = p_isCamUpdateMode;
	}
	public boolean isCamUpdateMode()
	{
		Log.d(TAG, "isCamUpdateMode returning  " + m_isCamUpdateMode);
		return m_isCamUpdateMode;
	}

	@Override
	public void update(Observable observable, Object data) {
		/*Log.d(TAG, "update: action " + ((NotificationInfoObject) data).actionID
				+ ", message " + ((NotificationInfoObject) data).message);*/
		final int l_eventID = ((NotificationInfoObject) data).actionID;
		int mChannelID = 0, presetNumber = 0;
		
		switch (l_eventID) {
		//Mark these lines for channel install behavior unnormal.
		//case EventIDs.EVENT_INST_STARTED:
		//	resetChannelList();
		//	break;
		case EventIDs.EVENT_HIERARCHICAL_MUX_FOUND:
			m_isHierarchicalMuxFound = true;
			break;
		case EventIDs.EVENT_SHOW_MANUAL_STORE_MESSAGE:
			String l_msg = (String) ((NotificationInfoObject) data).message; 
			m_lastSelectedPresetTC = Integer.parseInt(l_msg);
			ifAnalogDBSyncTriggered = true;
			commitDatabaseToTvProvider(false);
			break;
		case EventIDs.EVENT_COMMIT_FINISHED:
			// code will come here whenever db sync happens but only analog cases need to be handled here
			// other cases can be handled in respective wizard/dtr screens
			Log.d(TAG, "EVENT_COMMIT_FINISHED ifAnalogDBSyncTriggered: " + ifAnalogDBSyncTriggered);
			if(ifAnalogDBSyncTriggered){
				ifAnalogDBSyncTriggered = false; // reset flag
				
				Log.d(TAG, "EVENT_COMMIT_FINISHED last selected channel " + m_lastSelectedPresetTC);
				
				String[] mProjection = new String[] { Channels._ID };		
				String mSelecion = Channels.COLUMN_DISPLAY_NUMBER + " = ?" + " AND " + Channels.COLUMN_VERSION_NUMBER + " = ?";	
				String[] mSelectionArgs;
				if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
				  	mSelectionArgs = new String[]{Integer.toString(m_lastSelectedPresetTC),Integer.toString(1)};
				} else {
					mSelectionArgs = new String[]{Integer.toString(m_lastSelectedPresetTC),Integer.toString(0)};
				}
				
				Cursor c = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, mProjection, mSelecion, mSelectionArgs, null);
				if(c != null){
					Log.d(TAG, "c.getCount() " + c.getCount());
				}

				if ((c != null) && (c.getCount() > 0)) {
					c.moveToFirst();
					Log.d(TAG, "c " + c);
					try {
						mChannelID = Integer.parseInt(c.getString(0));
						Log.d(TAG, "mChannelID " + mChannelID);
					} catch (Exception ex) {
					} finally {
						c.close();
						c = null;
					}
				}
				
				if(c != null) {
					c.close();
					c = null;
				}
							
				if (!mbUseHtvDTRTuneType) {
					mTvSettingsManager.putInt(TvSettingsConstants.LASTSELECTEDDEVICE, 0,TvSettingsDefinitions.LastSelectedDeviceConstants.DVBTC);
					mTvSettingsManager.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC);
					// medium already set in nvm
				
					// set the channel number
					mTvSettingsManager.putInt(TvSettingsConstants.LASTSELECTEDPRESETTC, 0, mChannelID);
					
					// display tvtoast
					messenger = TvToastMessenger.getInstance(ctx);
					mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
					int storedChannelNum = m_lastSelectedPresetTC;
//					if (PlayTvUtils.isPbsMode())
//						storedChannelNum = mChannelID;
					mTimeOutTvToast.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CHANNEL_STORED) + storedChannelNum);
					messenger.showTvToastMessage(mTimeOutTvToast);
				}
			}
			break;
		case EventIDs.EVENT_ANALOG_SWITCH_DONE:
			Log.d(TAG,"EVENT_ANALOG_SWITCH_DONE");
			analogSourceSetupDone = true;
			break;
		case EventIDs.EVENT_SWITCH_TC:
			Log.d(TAG,"EVENT_SWITCH_TC");
			analogSourceSetupDone = false;
			break;
		case EventIDs.EVENT_CAM_INSTALL_REQUEST_NORMAL:
			Log.d(TAG,"EVENT_CAM_INSTALL_REQUEST_NORMAL");
			launchCamBasedInstallation(false);
			break;
		case EventIDs.EVENT_CAM_INSTALL_REQUEST_URGENT:
			Log.d(TAG,"EVENT_CAM_INSTALL_REQUEST_URGENT");
			launchCamBasedInstallation(true);
			break;
		case EventIDs.EVENT_CAM_SCHEDULE_UPDATE_INSTALL_DONE:
			onAlarmFiredFlag = false;
			clearCamData();
			setCamUpdateModeFlag(false);
			break;
		 case EventIDs.EVENT_INST_STOPPED:
         	Log.d(TAG, "EventIDs.EVENT_INST_STOPPED");
         	if(ifStopAndRestartInstallation){
         		startInstallation(getCurrentInstallationMode());
         	}
         	break;
		 case EventIDs.EVENT_MAJORVERSION_UPDATE:
			IsMajorVersionChange = true;
			break;
		case EventIDs.RESET_REGION_SELECTION:
			currentRegionMode = NativeAPIEnums.Regions.PRIMARY;
			Log.d(TAG, "ResetRegion Selection to "+currentRegionMode);
			break;
		case EventIDs.EVENT_CAM_SCHEDULE_UPDATE_TIME:	
			if(ssbyInstallInst != null)
				ssbyInstallInst.camSchedulUpdateTime(Integer.parseInt((String) ((NotificationInfoObject) data).message));
		break;
		case EventIDs.EVENT_CAM_SCHEDULE_UPDATE_DATE:
			if(ssbyInstallInst != null)
				ssbyInstallInst.camscheduleUpdateDate(Integer.parseInt((String) ((NotificationInfoObject) data).message));
		break;
		case EventIDs.EVENT_LANGUAGE_UPDATED:
			String l_msg1 = (String) ((NotificationInfoObject) data).message; 
			presetNumber = Integer.parseInt(l_msg1);
			UpdateLangCodeForCurrentMux(presetNumber);
		break;
		case EventIDs.EVENT_CHANNEL_NAME_UPDATED:			
			{
				String fsChID = (String) ((NotificationInfoObject) data).message;
				String fsUpdatedChName = euInst.GetUpdatedChannelName();
				int fiUpdatedONID = euInst.GetUpdatedONID();
				int fiUpdatedTsID = euInst.GetUpdatedTsID();
				String mSelecion = "_id=? AND " + Channels.COLUMN_NETWORK_AFFILIATION + "=?";
				String[] mSelectionArgs = new String[] {fsChID, HTV_DI_CHANNEL_UPDATE_FLAG};
				ContentValues fvValues = new ContentValues();
						
				//Log.d(TAG, "Update channel name. _id:" + fsChID + "  Name:" + fsUpdatedChName);
																
				fvValues.put(Channels.COLUMN_DISPLAY_NAME, fsUpdatedChName);

				Log.d(TAG, "Update channel name. _id:" + fsChID + "  Name:" + fsUpdatedChName + "  ONID:" + fiUpdatedONID + "  TsID:" + fiUpdatedTsID);
				//
				fvValues.put(Channels.COLUMN_ORIGINAL_NETWORK_ID, fiUpdatedONID);
				fvValues.put(Channels.COLUMN_TRANSPORT_STREAM_ID, fiUpdatedTsID);
				//fvValues.put(Channels.COLUMN_DISPLAY_NAME, fsUpdatedChName);
				fvValues.put(Channels.COLUMN_NETWORK_AFFILIATION, HTV_DI_CHANNEL_FLAG);
					
				if(ctx.getContentResolver().update(TvContract.Channels.CONTENT_URI, fvValues, mSelecion, mSelectionArgs) > 0) 
				{
					Log.d(TAG, "Update channel name: success.");
					
					synchronized(mviHtvChNameUpdateList) {
						try{
							mviHtvChNameUpdateList.remove(Long.decode(fsChID));
						}
						catch(Exception e) { }
					}
										
					Intent fIntent = new Intent("org.droidtv.euinstallertc.CHANNEL_NAME_UPDATE");
					ctx.sendBroadcast(fIntent);
				} else {
					
					mSelectionArgs = new String[] {fsChID, HTV_DT_CHANNEL_UPDATE_FLAG};
					
					fvValues.put(Channels.COLUMN_NETWORK_AFFILIATION, HTV_DT_CHANNEL_FLAG);
					
					if(ctx.getContentResolver().update(TvContract.Channels.CONTENT_URI, fvValues, mSelecion, mSelectionArgs) > 0) 
					{
						Log.d(TAG, "Update channel name 1: success.");
						
						synchronized(mviHtvChNameUpdateList) {
							try{
								mviHtvChNameUpdateList.remove(Long.decode(fsChID));
							}
							catch(Exception e) { }
						}
											
						Intent fIntent = new Intent("org.droidtv.euinstallertc.CHANNEL_NAME_UPDATE");
						ctx.sendBroadcast(fIntent);
					} else {
					
						mSelecion = "_id=?";
						mSelectionArgs = new String[] {fsChID};
					
						fvValues.put(Channels.COLUMN_NETWORK_AFFILIATION, "");
					
						if(ctx.getContentResolver().update(TvContract.Channels.CONTENT_URI, fvValues, mSelecion, mSelectionArgs) > 0) 
						{
							Log.d(TAG, "Update channel name 2: success.");
											
							Intent fIntent = new Intent("org.droidtv.euinstallertc.CHANNEL_NAME_UPDATE");
							ctx.sendBroadcast(fIntent);
						}
					}
				}								
			}
			break;		
		}
	}

	public void setMajorVersion()
	{
		Log.d(TAG, "setManjorVersion to True");
		IsMajorVersionChange = true;
	}
		
	public void HandleTuneToLowestPreset(int presetNum)
	{
		Log.d(TAG, "HandleTuneToLowestPreset with Preset "+presetNum);
		String[] mprojection = new String[] { Channels._ID };		 
		String mselecion = Channels.COLUMN_DISPLAY_NUMBER + "=?"+" AND "+Channels.COLUMN_VERSION_NUMBER+"= ?";  
		String[] mselectionArgs;
		if (isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC) {
			mselectionArgs = new String[]{Integer.toString(presetNum),Integer.toString(1)};
		} else {
			mselectionArgs = new String[]{Integer.toString(presetNum),Integer.toString(0)};
		}

		int mChannelNum = 0;
		boolean ifValidPreset = false;
		Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, mprojection, mselecion, mselectionArgs, null);
		if(cursor!= null){
			Log.d(TAG, "cursor.getCount()" + cursor.getCount());
		}
		if ((cursor != null) && (cursor.getCount() > 0)) {
			cursor.moveToFirst();
			Log.d(TAG, "cursor "+ cursor);
			try {
				mChannelNum = Integer.parseInt(cursor.getString(0));
				ifValidPreset = true;
			} catch (Exception ex) {
			}
		}else{
		}
			
		if(cursor != null){
			cursor.close();
			cursor=null;
		}
		if(ifValidPreset){
			Uri playUri = null;

			if ((getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBC) || 
				((getSelectedDVBTOrDVBCFromTVS() == NativeAPIEnums.DVBTOrDVBC.DVBT))){
				playUri = TvContract.buildChannelUri(mChannelNum);
				Intent playTVIntent = new Intent("android.intent.action.VIEW",playUri);
				playTVIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);

				try {
					Log.d(TAG, "raise intent to playtv: " + playUri.toString());
					serviceCtx.startActivity(playTVIntent);
				} catch (Exception ex) {
				Log.e(TAG, "raise intent exception caught: " + ex.getMessage());
				}
			}
		}

	}

	
	public void launchCamBasedInstallation(boolean isUrgent)
	{
		Log.d(TAG,"Entered launchCamBasedInstallation with Value " + isUrgent);
		if(isUrgent == true)
		{
			setCamUpdateModeFlag(true);
			Intent l_intentUrgent = new Intent(ctx, CamUpdateDialogActivity.class);
			l_intentUrgent.putExtra("NotificationType", "Notification");
			l_intentUrgent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			ctx.startActivity(l_intentUrgent);
		}
		else
		{
			setCamUpdateModeFlag(true);
			Intent l_intent = new Intent(ctx, CamUpdateDialogActivity.class);
			l_intent.putExtra("NotificationType", "Dialog");
			l_intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			ctx.startActivity(l_intent);
		}
	}

	public TCSurface getTCSurface()
	{
		Log.d(TAG,"getTCSurface entry " );
		return m_surface;
	}

	public TCSurface createTCSurface(Context p_context)
	{
		Log.d(TAG,"createTCSurface entry " );
		m_surface = new TCSurface(p_context);
		Log.d(TAG,"createTCSurface exit " );
		return m_surface;
	}
	public void setTVMplSurface(Surface p_surface)
	{
		Log.d(TAG,"setTVMplSurface entry " );
		euInst.setSurface(p_surface);
		Log.d(TAG,"setTVMplSurface exit " );
	}
	public boolean isBackgroundUpdateRequired()
	{
		boolean backgroundInstallReq = false;
		int medium,operator;
		NativeAPIEnums.Operators opEnum = NativeAPIEnums.Operators.Other;
		
		medium = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
		String storedCountryName = getCountryNameFromTVS();
		operator = mTvSettingsManager.getInt(TvSettingsConstants.OPERATORCABLE,0,0);

		switch (operator) {
		case TvSettingsDefinitions.OperatorCableConstants.NONE:
			opEnum = NativeAPIEnums.Operators.Other;
			break;

		case TvSettingsDefinitions.OperatorCableConstants.TELENET:
			opEnum = NativeAPIEnums.Operators.Telenet;
		default:
			break;
		}
		if((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))) && (medium == 1) 
			&& ((opEnum == NativeAPIEnums.Operators.Telenet) | (opEnum == NativeAPIEnums.Operators.Other)))
		{
			backgroundInstallReq = true;
		}	
		return backgroundInstallReq;
	}

	class CheckScheduleUpdate implements Runnable {
		
			@Override
			public void run() {
				synchronized (installerservicescheduleTime) {
					Log.d(TAG, "Entered Runnable Synchronized for CheckScheduleUpdate\n");
					if(ssbyInstallInst != null) {
						ssbyInstallInst.checkStartScheduleUpdate();
					}
					else
						Log.d(TAG, "ssbyInstallInst is null");
				}
			}
	};	
	public boolean isSemiStandbyUpdateRequiredOnShutdown () {
		boolean semiSbyNeeded = false;
		int medium;
		String storedCountryName = getCountryNameFromTVS();
		Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown entry " );

		if(IsBGInstallEnabled == false){
			semiSbyNeeded = false;
		}
		else{
			medium = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
			int operator = mTvSettingsManager.getInt(TvSettingsConstants.OPERATORCABLE,0,0);
			NativeAPIEnums.Operators opEnum = NativeAPIEnums.Operators.Other;
				
			Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 1 " );
			Log.d(TAG, "Medium" + medium + "NetworkUpdateNeeded" +  (euInst.IsNetworkUpdateDetected()));
			/* If DVBC / Clite && (NetworkUpdate Required || NetworkUpdate needed from settings) && (Medium == cable) */
			if (( (countrySupportsDVBCFullorLite(storedCountryName) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Full) ||
				  (countrySupportsDVBCFullorLite(storedCountryName) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light) ) && 
				(medium == 1) && (euInst.IsNetworkUpdateDetected() == true )) {
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 11" );
				semiSbyNeeded = true;
			}
			Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 2 " );

			/* If( Medium == T) && (Country == Finland/ Norway/ Sweden/ Ireland/ Hungary ) */
			if ((medium == 0) && ((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_FINLAND))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SINGAPORE)))||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_THAILAND)))||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TAIWAN)))||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MALAYSIA)))||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRALIA)))||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_INDONESIA)))||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NEWZEALAND))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_VIETNAM))))) {
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 22 " );
				semiSbyNeeded = true;
			}
			Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 3 " );
			/* If (Medium == C) && (Country == Norway/Sweden/Denmark */
			if ((medium == 1) && ((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))) ||
								  (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA))))) {
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 33 " );
				

				switch(operator)
				{
					case TvSettingsDefinitions.OperatorCableConstants.CANALDIGITAL:
						opEnum = NativeAPIEnums.Operators.CanalDigital;
						break;
					case TvSettingsDefinitions.OperatorCableConstants.YOUSEE:
						opEnum = NativeAPIEnums.Operators.YouSee;
						break;
				}
				if((getWSFreqScanMode() == 0) && ((opEnum == NativeAPIEnums.Operators.CanalDigital) || (opEnum == NativeAPIEnums.Operators.YouSee)))
				{
					semiSbyNeeded = false;
				} else {
					semiSbyNeeded = true;
				}
			}
			
			/* chack if automatic update is on */
			Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 4 " );
			if((GetStandbyUpdate() == 0) && (semiSbyNeeded == true)){
				semiSbyNeeded = false;
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 44 " );
			}

			/*Check if Update installation is available*/
			Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 5 " );
			if((semiSbyNeeded == true) && (euInst.IsAvailable(euInstConst.IHsvInstallation2_InstallationModeAutomatic, euInstConst.IHsvInstallation2_AttributeUpdateInstall) == false))
			{
				semiSbyNeeded = false;
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown 55 " );
			}
		}
		
		
		Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown exit " + semiSbyNeeded);
		return semiSbyNeeded;
	}
	public void onAlarmFired()
	{
	     Log.d(TAG,"Launching Schedule Update wizard\n");
		onAlarmFiredFlag = true;
		RunScheduleUpdate r = new RunScheduleUpdate();
		mCipHandler.post(r);
	}
	public void checkStartScheduleUpdate()
	{
		Log.d(TAG,"checkStartScheduleUpdate\n");
		CheckScheduleUpdate r = new CheckScheduleUpdate();
		mCipHandler.post(r);
	}

	public void storeCamData(long time)
	{
		boolean IsCamSchedPerfomred = true;
		//mCamScheduleShrdPref = ctx.getApplicationContext().getSharedPreferences("mCamScheduleShrdPref", Context.MODE_PRIVATE);
		//editor  = mCamScheduleShrdPref.edit();
		editor.putLong("CamSchdTime", time);
		editor.putBoolean("IsCamSchedPerfomred", IsCamSchedPerfomred);
		editor.commit();		
	}

	public void clearCamData()
	{
		boolean IsCamSchedPerfomred = false;
		//mCamScheduleShrdPref = ctx.getApplicationContext().getSharedPreferences("mCamScheduleShrdPref", Context.MODE_PRIVATE);
		//editor  = mCamScheduleShrdPref.edit();
		editor.putLong("CamSchdTime", 0);
		editor.putBoolean("IsCamSchedPerfomred", IsCamSchedPerfomred);
		editor.commit();		
	}
	public long getStoredScheduleUpdateTime()
	{
		Log.d(TAG,"getStoredScheduleUpdateTime \n");
		long time = 0;
		time				  = mCamScheduleShrdPref.getLong("CamSchdTime", time);
		Log.d(TAG,"alarm time is " + time);
		return time;
	}

	public boolean IsCamSchedPerformed()
	{
		Log.d(TAG,"IsCamSchedPerformed \n");
		boolean IsCamSchedPerfomred = false;
		IsCamSchedPerfomred = mCamScheduleShrdPref.getBoolean("IsCamSchedPerfomred", IsCamSchedPerfomred);
		return IsCamSchedPerfomred;
	}

	public boolean isScheduleUpdateNeeded(long currentTimeinMilliSec)
	{
		Log.d(TAG,"Entered isScheduleUpdateNeeded \n");
		boolean IsCamSchedPerfomred = false, retValue = false;
		long time = 0;
		time 			      = mCamScheduleShrdPref.getLong("CamSchdTime", time);
		IsCamSchedPerfomred = mCamScheduleShrdPref.getBoolean("IsCamSchedPerfomred", IsCamSchedPerfomred);
		Log.d(TAG," IsCamSchedPerfomred is " + IsCamSchedPerfomred);
		Log.d(TAG," time is " + time);
		Log.d(TAG,"Alarm Fired?? now not used" + onAlarmFiredFlag);
		if(IsCamSchedPerfomred && (currentTimeinMilliSec > time) /*&& onAlarmFiredFlag*/)
		{
			retValue = true;
		}
		return retValue;
	}

	class RunScheduleUpdate implements Runnable {

		@Override
		public void run() {
			synchronized (installerserviceschedulelock) {
				Log.d(TAG, "Entered Runnable Synchronized\n");
				mTvPowerManager = ITvPowerManager.Instance.getInterface();
				currentPowerState = mTvPowerManager.GetPowerState();
				if (currentPowerState == PowerStates.POWER_STATE_FULL_SYSTEM_START) {
					Log.d(TAG, "Powered on scenario. Will launch UI\n");
					operatorIdTVS = TvSettingsDefinitions.OperatorCableConstants.CAM;
					euInst.SetAttribute(euInstConst.IHsvInstallation2_InstallationModeCam, euInstConst.IHsvInstallation2_AttributeNetworkOperator, operatorIdTVS);
					launchCamBasedInstallation(false);
				}
			}
		}
	};

	public boolean isSemiStandbyUpdateRequiredOnAlarmWakeup () {
		boolean semiSbyNeeded = true;
		int medium, operator;
		NativeAPIEnums.Operators opEnum = NativeAPIEnums.Operators.Other;
		String storedCountryName = getCountryNameFromTVS();

		if(IsBGInstallEnabled == false){
			semiSbyNeeded = false;
		}
		else{
			operator = mTvSettingsManager.getInt(TvSettingsConstants.OPERATORCABLE,0,0);
			medium = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
			
			switch (operator) {
			case TvSettingsDefinitions.OperatorCableConstants.NONE:
				opEnum = NativeAPIEnums.Operators.Other;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.Ziggo:
				opEnum = NativeAPIEnums.Operators.Ziggo;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.UPC:
				opEnum = NativeAPIEnums.Operators.UPC;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.KDG:
				opEnum = NativeAPIEnums.Operators.KDG_SD;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.UNITYMEDIA:
				opEnum = NativeAPIEnums.Operators.Unitymedia;
				break;
			 case TvSettingsDefinitions.OperatorCableConstants.RCS_RDS:
				 opEnum = NativeAPIEnums.Operators.RCSRDS;
				 break;
			case TvSettingsDefinitions.OperatorCableConstants.TELENET:
			    opEnum = NativeAPIEnums.Operators.Telenet;	
				 break;			
			case TvSettingsDefinitions.OperatorCableConstants.BLIZOO:
			    opEnum = NativeAPIEnums.Operators.Blizoo;
	             break;
			case TvSettingsDefinitions.OperatorCableConstants.CANALDIGITAL:
				opEnum = NativeAPIEnums.Operators.CanalDigital;
				break;
			case TvSettingsDefinitions.OperatorCableConstants.YOUSEE:
				opEnum = NativeAPIEnums.Operators.YouSee;
	             break;
           case TvSettingsDefinitions.OperatorCableConstants.KDGHD:
					opEnum = NativeAPIEnums.Operators.KDG_HD;
					break;
			default:
				break;
			}

			/* Clite && Cable && DigitalOption = FALSE  --> false */
			if ((countrySupportsDVBCFullorLite(storedCountryName) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light) &&
				(medium == 1) && (ifDigitalOptionOn() == false)) {
				semiSbyNeeded = false;
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnAlarmWakeup 1" );
			}
			
			/* Netherlands  && Cable && UPC ==> false */
			/* Belgium && Cable && Telenet ==> false */
			if ( ((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))) && (medium == 1) && (opEnum == NativeAPIEnums.Operators.UPC)) ||
				 ((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))) && (medium == 1) && (opEnum == NativeAPIEnums.Operators.Telenet)) ||
				 ((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS))) && (medium == 1) && (opEnum == NativeAPIEnums.Operators.Ziggo)) ){
				semiSbyNeeded = false;
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnAlarmWakeup 2" );
			}
			
			if (((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NORWAY)))||
				    (storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWEDEN)))) && 
					(medium == 1) && (opEnum == NativeAPIEnums.Operators.CanalDigital)) 
			{
				if(getWSFreqScanMode() == 0)
					semiSbyNeeded = false;
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnAlarmWakeup 3" );

			}
			/* Denmark && Cable && YouSee ==> false */
			if((storedCountryName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DENMARK))) && (medium == 1) && (opEnum == NativeAPIEnums.Operators.YouSee))
			{
				if(getWSFreqScanMode() == 0)
					semiSbyNeeded = false;
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnAlarmWakeup 4" );
			}
			/* chack if automatic update is on */
			if((GetStandbyUpdate() == 0) && (semiSbyNeeded == true)){
				semiSbyNeeded = false;
				Log.d(TAG,"isSemiStandbyUpdateRequiredOnShutdown   5" );
			}
		}
		
		Log.d(TAG,"isSemiStandbyUpdateRequiredOnAlarmWakeup semiSbyNeeded:" + semiSbyNeeded );
		return semiSbyNeeded;
	}
	
	
	public void UnregisterTuningListener()
	{
		euInst.UnregisterTuningNotification();
	}
	
	public class TCSurface extends SurfaceView implements SurfaceHolder.Callback
	{
		Surface m_surface = null;
		public TCSurface(Context context)
		{
			super(context);
			Log.d(TAG,"TCSurface : constructor" );
			getHolder().addCallback(this);
		}
		@Override
		public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
		{
			Log.d(TAG,"TCSurface : surfaceChanged " );
		}
		@Override
		public void surfaceCreated(SurfaceHolder holder)
		{
			Log.d(TAG,"TCSurface : surfaceCreated " );
			m_surface = holder.getSurface();
		}
		@Override
		public void surfaceDestroyed(SurfaceHolder holder)
		{
			Log.d(TAG,"TCSurface : surfaceDestroyed " );
		}
		public Surface getSurface()
		{
			Log.d(TAG,"TCSurface : getSurface " );
			return m_surface;
		}
	}
	
	public NativeAPIEnums.DVBTOrDVBC GetMediumDVBTorDVBC()
	{
		Log.d(TAG,"GetMediumDVBTorDVBC entry");
		NativeAPIEnums.DVBTOrDVBC l_ret;
		
		// 0 - DVB T or 1 - DVB C
		if(euInst.GetMedium() == 0)
		{
			l_ret = NativeAPIEnums.DVBTOrDVBC.DVBT;
		}
		else
		{
			l_ret = NativeAPIEnums.DVBTOrDVBC.DVBC;
		}
		
		Log.d(TAG,"GetMediumDVBTorDVBC exit"+ l_ret);
		
		return l_ret;
	}

	public void setMedium(NativeAPIEnums.DVBTOrDVBC dvbMedium)
	{
		Log.d(TAG,"setMedium entry, ");

		euInst.createMWInstance();

		// 0 - DVB T or 1 - DVB C
		if(dvbMedium == NativeAPIEnums.DVBTOrDVBC.DVBC){
			isDVBTorDVBC = NativeAPIEnums.DVBTOrDVBC.DVBC;
			euInst.SetMedium(euInstConst.IHsvInstallation2_Cable);
		} else {
			isDVBTorDVBC = NativeAPIEnums.DVBTOrDVBC.DVBT;
			euInst.SetMedium(euInstConst.IHsvInstallation2_Terrestrial);
		}

		Log.d(TAG,"setMedium exit");
	}

	public NativeAPIEnums.DVBTOrDVBC getCurrentMedium()
	{
		Log.d(TAG,"getCurrentMedium " + isDVBTorDVBC);
		return isDVBTorDVBC;
	}

	public NativeAPIEnums.AnalogueOrDigital getDigitalAnalogSelection(String selectedCountry,NativeAPIEnums.DVBTOrDVBC selectedMedium)
	{
		Log.d(TAG, "getDigitalAnalogIndex entry ");
		
		String storedCountry = getCountryNameFromTVS();
		NativeAPIEnums.DVBTOrDVBC storedMedium = getSelectedDVBTOrDVBCFromTVS();
		
		Log.d(TAG, "Stored_Medium: " + storedMedium + "Stored_Country: " + storedCountry);
		
		if(storedCountry.equalsIgnoreCase(selectedCountry) && (storedMedium == selectedMedium))
		{
			Log.d(TAG, "Get the Previous Selection");
			analogOrDigital = getPreviousDigitalAnalogSelection(selectedCountry,selectedMedium);
		}
        else
        {
        	Log.d(TAG, "Get the Default Selection");
        	analogOrDigital = getDefaultDigitalAnalogSelection(selectedCountry,selectedMedium);
        }
        
		
        Log.d(TAG, "getDigitalAnalogIndex exit:" + analogOrDigital);
		
        return analogOrDigital;
	}
	
	public NativeAPIEnums.AnalogueOrDigital getDefaultDigitalAnalogSelection(String selCountry,NativeAPIEnums.DVBTOrDVBC selMedium)
	{
		Log.d(TAG, "getDefaultDigitalAnalogIndex entry ");
		
		// is DVBT
		if(selMedium == NativeAPIEnums.DVBTOrDVBC.DVBT)
		{
			Log.d(TAG, "is a DVBT full");
			if(DVBTOrDVBCMacro.DVBT_Full == countrySupportsDVBTFullorLite(selCountry))
			{
				//if analog default off country
				if(ifASOCountry(selCountry,selMedium))
				{
				    Log.d(TAG, "T is a analog switched off");
					analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL;
				}
				else
				{
					Log.d(TAG, "T is a analog switched on");
					analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE;
					
				}
			}
		}
		else //is DVBC
		{
			if(DVBTOrDVBCMacro.DVBC_Full ==  countrySupportsDVBCFullorLite(selCountry))
			{
				//if analog default off country
				Log.d(TAG, "is a DVBC full");
				if(ifASOCountry(selCountry,selMedium))
				{
					Log.d(TAG, "is a analog switched off");
					analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL;
				}
				else
				{
					Log.d(TAG, "is a analog switched On");
					if(getOperatorFromMW() == NativeAPIEnums.Operators.Telemach)
					{
						analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL;
					} else {
					analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE;
					}
				}
			}
			else
			{
				Log.d(TAG, "is a DVBC lite");
				//analog is always default on for dvbc_lite country
				analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE;
			}
		}
		
		Log.d(TAG, "getDefaultDigitalAnalogIndex exit: " + analogOrDigital);
		
		return analogOrDigital;
	}
	
	public NativeAPIEnums.AnalogueOrDigital getPreviousDigitalAnalogSelection(String selCountry,NativeAPIEnums.DVBTOrDVBC selMedium)
	{
		Log.d(TAG, "getPreviousDigitalAnalogSelection entry ");
		
		String readString = mStoredSharedPreferences.getString("analog_digital", "");
	
		Log.d(TAG, "readstring:  " + readString);
	
		if(readString.equalsIgnoreCase(NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE.toString()))
        {
        	// Digital + Analogue
        	Log.d(TAG, "Index is analog + digital");
        	analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE;
        }else if(readString.equalsIgnoreCase(NativeAPIEnums.AnalogueOrDigital.DIGITAL.toString()))
        {
        	// Digital Only
        	Log.d(TAG, "Index is digital"); 
        	analogOrDigital = NativeAPIEnums.AnalogueOrDigital.DIGITAL;
        }else if(readString.equalsIgnoreCase(NativeAPIEnums.AnalogueOrDigital.ANALOGUE.toString()))
        {
        	// Analogue only
        	Log.d(TAG, "Index is analog ");  
        	analogOrDigital = NativeAPIEnums.AnalogueOrDigital.ANALOGUE;
        }
        else
        {
        	// Case where stored country & medium matches with the selected, but readstring == null
			// Happens @ virgin installation
			Log.d(TAG, "Get the Default Index @ virgin installation");
        	analogOrDigital = getDefaultDigitalAnalogSelection(selCountry,selMedium);
        }
		
		Log.d(TAG, "getPreviousDigitalAnalogSelection exit: " + analogOrDigital);
		
		return analogOrDigital;
	}
	
	public int getMappedDigitalAnalogIndex()
	{
		Log.d(TAG, "getMappedDigitalAnalogIndex entry");
		int l_digangIdx = 0;
		
		switch(analogOrDigital)
		{
			case DIGITAL_AND_ANALOGUE: l_digangIdx = 0;
										break;
			case DIGITAL:l_digangIdx = 1;
							break;
			case ANALOGUE:l_digangIdx = 2;
							break;
		}
		
		if(l_digangIdx > (getAnalogueDigitalList().length -1))
		{
			// case where returned index is greater than the lenght of radio list, safety check
			Log.d(TAG, "returned index greater than radio list lenght: index reset to zero: index "+ l_digangIdx + " radiolist_len " +(getAnalogueDigitalList().length -1));
			l_digangIdx = 0;
		}
		
		Log.d(TAG, "getMappedDigitalAnalogIndex exit: " + l_digangIdx);
		
		return l_digangIdx;
	
	}

	public int getChannelfromID(int id)
	{
		int ret = 0;
		
		String[] projection = new String[] {Channels.COLUMN_DISPLAY_NUMBER};
		String	mselection = Channels._ID+"= ?";
		String[]	mselectionargs=new String[]{String.valueOf(id)};
		
		Cursor TCCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		
		if(TCCursor != null){
			try{
			if(TCCursor.moveToNext()) { 
				ret = TCCursor.getInt(0);
			}
			}finally{
			    TCCursor.close();
				TCCursor=null;
			}
		}
		else{
			Log.d(TAG, "TCCursor NULL, no channel in tv.db with _ID " + id);	
		}

		Log.d(TAG, "getChannelfromID ret " + ret);	
		return ret;		
	
	}
	
	public boolean isDTRSearchInifinitely(){
		boolean returnStatus = false;

		/*String selectedCountryInTVS = getCountryNameFromTVS();*/
        NativeAPIEnums.DVBTOrDVBC selectedMediumInTVS = getSelectedDVBTOrDVBCFromTVS();
		if(selectedMediumInTVS == NativeAPIEnums.DVBTOrDVBC.DVBT)
		{
			returnStatus = true;
		}
 
        Log.d(TAG, "isDTRSearchInifinitely " + returnStatus);
        return returnStatus;
	}
	
	//------------------------------ TIF Changes ------------------------------ //

	public SessionHandlerTIF mSessionInstanceMain = null;
	public SessionHandlerTIF mSessionService = null;
	
	public void createTIFSession(SessionHandlerTIF.SESSION_PURPOSE argSessionPurpose) {
		Log.d(TAG, "createTIFSession " + argSessionPurpose);
		if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER) {
			mSessionInstanceMain = new SessionHandlerTIF(ctx, SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
			mSessionInstanceMain.registerToSessionHandler(mMainCallbackSessionHandler);
			mSessionInstanceMain.createNewSession();
		} else if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_OBSERVER) {
			mSessionService = new SessionHandlerTIF(ctx, SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_OBSERVER);
			mSessionService.registerToSessionHandler(mObserverCallbackSessionHandler);
			mSessionService.createNewSession();
		}
	}
	
	private SessionHandlerTIF.ISessionHandlerTIF mObserverCallbackSessionHandler = new SessionHandlerTIF.ISessionHandlerTIF() {

		@Override
		public void sessionReleased() {
			// TODO Auto-generated method stub
		}
		
		@Override
		public void sessionOnChannelChangeStarted () {
			Log.d (TAG, "Channel Change started. Hence stopping background");
			try {
				backInstallInst.stopBackgroundInstallation();
			}
			catch  (Exception e) {
			}
		}

		@Override
		public void sessionOnChannelChangeCompleted (Uri channelUri) {
			Log.d (TAG, "sessionOnChannelChangeCompleted channelUri: " + channelUri + "IsBGInstallEnabled: " + IsBGInstallEnabled);
			// background installation wil be triggered from here
			boolean fbIsHtvChNameUpdate = false;
			boolean fbIsPbsMode = PlayTvUtils.isPbsMode();
			
			if(fbIsPbsMode && !IsBGInstallEnabled && channelUri != null)
				fbIsHtvChNameUpdate = getIsAnyRequestforHTVChNameUpdate();
			
			if((IsBGInstallEnabled == true || fbIsHtvChNameUpdate) && ((getApplicationState() == NativeAPIEnums.ApplicationState.IDLE) ||
				(getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE))){
				//Log.d(TAG, "sessionOnChannelChangeCompleted in Observer mode channelUri: " + channelUri);
				try {
					if( channelUri == null){
						backInstallInst.stopBackgroundInstallation();
					}else{
						long channel_id = ContentUris.parseId(channelUri);
						
						if(fbIsHtvChNameUpdate) 
							fbIsHtvChNameUpdate = getIsHTVChNeedForNameUpdate(channel_id);
						
						if(IsBGInstallEnabled || fbIsHtvChNameUpdate) {
							
//							Log.d(TAG, "sessionOnChannelChangeCompleted with _ID " + channel_id);
							String[] projection = new String[] { Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_NETWORK_AFFILIATION};
							String mselection = Channels._ID + "= ?";
							String[] mselectionargs = new String[] { String.valueOf(channel_id)};
							euInst.setSessionHandler(mSessionService);
							euInst.setCIInterfacesOnSessionCreated();
							Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
						
						    try{
							if((cursor != null) && (cursor.moveToFirst() != false)){
								String Type = cursor.getString(0);
								int fiServID = cursor.getInt(1);
								String fsNetAffi = cursor.getString(2);
								
								if(fbIsHtvChNameUpdate && !HTV_DI_CHANNEL_UPDATE_FLAG.equals(fsNetAffi) && !HTV_DT_CHANNEL_UPDATE_FLAG.equals(fsNetAffi)) {														
									removeHTVChNameUpdateRequest(channel_id);									
									backInstallInst.stopBackgroundInstallation();
								}
								else if(((Type.equalsIgnoreCase(Channels.TYPE_DVB_T)) ||(Type.equalsIgnoreCase(Channels.TYPE_DVB_C)) || (Type.equalsIgnoreCase(Channels.TYPE_DVB_T2)))
										&& !HTV_DT_CHANNEL_FLAG.equals(fsNetAffi) 
										&& !HTV_DI_CHANNEL_FLAG.equals(fsNetAffi)
										&& !HTV_DI_CHANNEL_CHECK_FLAG.equals(fsNetAffi)
										) {
									//Log.d(TAG, "DVBTC Channel " + Type);
									euInst.setSessionHandler(mSessionService);
									euInst.sessionOnChannelRetuned();
									if (fbIsPbsMode) {
										setPbsMode(1);
									}
									if (Type.equalsIgnoreCase(Channels.TYPE_DVB_T) || HTV_DI_CHANNEL_UPDATE_FLAG.equals(fsNetAffi) || HTV_DT_CHANNEL_UPDATE_FLAG.equals(fsNetAffi)) {
										//Log.d(TAG, "sessionOnChannelChangeCompleted TYPE_DVB_T");
										euInst.SetMedium(euInstConst.IHsvInstallation2_Terrestrial);
									} else {
										//Log.d(TAG, "sessionOnChannelChangeCompleted TYPE_DVB_C");
										euInst.SetMedium(euInstConst.IHsvInstallation2_Cable);
									}

									if (fbIsPbsMode) {
										if (HTV_DI_CHANNEL_UPDATE_FLAG.equals(fsNetAffi) || HTV_DT_CHANNEL_UPDATE_FLAG.equals(fsNetAffi))
											euInst.PrepareChNameUpdate((int) channel_id, fiServID);
										else {
											removeHTVChNameUpdateRequest(channel_id);
											euInst.PrepareChNameUpdate(0, 0);
										}
									}

									if (GetStandbyUpdate() == 1 || HTV_DI_CHANNEL_UPDATE_FLAG.equals(fsNetAffi)){
										backInstallInst.startBackgroundInstallation();
									}
								}
								else{
									//Log.d(TAG, "Non DVBTC Channel " + Type);
									backInstallInst.stopBackgroundInstallation();
								}
							}
							else{
								Log.d(TAG, "Null cursor " + cursor);
								backInstallInst.stopBackgroundInstallation();
							}
							}finally{
							   if(cursor != null)
							   {
								  cursor.close();
								  cursor=null;
							   }
							}
							
						}
						
					
					}
				}
				catch (Exception e)
				{
					Log.d (TAG, "Exception in " + e);
				}
			}
		}

		@Override
		public void sessionOnChannelRetuned(Uri channelUri) {

			if( channelUri == null){
				try {
					backInstallInst.stopBackgroundInstallation();
				}
				catch  (Exception e) {
				}
			}
		}

		@Override
		public void sessionCreationSuccessfull() {
			// set session handler so euinstallerTC can use session handler
			NativeAPIEnums.DVBTOrDVBC returnMode = getSelectedDVBTOrDVBCFromTVS();
			isDVBTorDVBC = returnMode;
			
			euInst.createMWInstance();

			if(isDVBTorDVBC == NativeAPIEnums.DVBTOrDVBC.DVBC){
				euInst.SetMedium(euInstConst.IHsvInstallation2_Cable);
			}
			else{
				euInst.SetMedium(euInstConst.IHsvInstallation2_Terrestrial);
			}
			
			Log.d(TAG, "sessionCreationSuccessfull and MW instance created, Loading the TVProvidr Data: current Medium: " + isDVBTorDVBC);
			//RemoveHtvDTChannel();
			LoadTvProviderData();
			LoadFreqMapDataData();
			
			// create instace for background installation
			backInstallInst = new BackgroundInstallation(serviceCtx);
			ssbyInstallInst	= new SemistandbyUpdate(serviceCtx);
			registerTvProviderContentObservers();
			Uri selectedURI = mSessionService.getTunerSession().getSelectedURI();
			if(selectedURI != null){
				Log.d(TAG, "There is already a URI selected so send sessionOnChannelChangeCompleted which is missed");				
				sessionOnChannelChangeCompleted(selectedURI);
			}
		}

		@Override
		public void sessionCreationFailed() {
			// TODO Auto-generated method stub
			// exit giving notification to the user
		}
		
		@Override
		public void sessionOnChannelRetunedFailed () {
			
		}

	};
	
	private SessionHandlerTIF.ISessionHandlerTIF mMainCallbackSessionHandler = new SessionHandlerTIF.ISessionHandlerTIF() {
		
		@Override
		public void sessionReleased() {
			// TODO Auto-generated method stub
		}
		
		@Override
		public void sessionOnChannelRetuned( Uri channelUri) {
			ntf.notifyAllObservers(EventIDs.EVENT_INSTALLER_ONCHANNELRETUNED, "");
			// respond only for Installer main installations
			if( channelUri == null){
				
			}else if(getApplicationState() != NativeAPIEnums.ApplicationState.IDLE){
				euInst.sessionOnChannelRetuned();
			//	euInst.setCIInterfacesOnSessionCreated();
			}
		}
		
		@Override
		public void sessionCreationSuccessfull() {
			
			// set session handler so euinstallerTC can use session handler
			// call mw instance creation if not already created
			euInst.createMWInstance(); // optional can be removed as MW instance by this time is already created by service
			Log.d(TAG, "mMainCallbackSessionHandler: sessionCreationSuccessfull");
			
			euInst.setSessionHandler(mSessionInstanceMain);
			
			// this flow will come when session is first created by Activity
			NativeAPIEnums.DVBTOrDVBC returnMode = mbUseHtvDTRTuneType?meHtvDTRTuneType:getSelectedDVBTOrDVBCFromTVS();
			isDVBTorDVBC = returnMode;

		
			int tvscCountryID = 0;
			String[] localCountryArray = getSortedCountyList();
			String[] tvscCountryArray = getCountyListMappedToTVSettings();
			
			tvscCountryID = mTvSettingsManager.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
			String localCountry = tvscCountryArray[tvscCountryID];
  

			// update the country ID in TVSettings
            for (tvscCountryID = 0; tvscCountryID < localCountryArray.length; tvscCountryID++) {
                if (localCountry.equalsIgnoreCase(localCountryArray[tvscCountryID])) {
                    
                  	selectedCountryID = tvscCountryID;
                    Log.d(TAG, "sessionCreationSuccessfull setSelectedCountyID()  " + selectedCountryID);
                    break;
				}
			}

			if (returnMode == NativeAPIEnums.DVBTOrDVBC.DVBC) {
				setSessionTuneWithMedium(SessionHandlerTIF.SESSION_MEDIUM.CABLE);
			} else {
				setSessionTuneWithMedium(SessionHandlerTIF.SESSION_MEDIUM.ANTENNA);
			}
		}
		
		@Override
		public void sessionCreationFailed() {
			Log.d(TAG, "sessionCreationFailed"); 
			// exit giving notification to the user
			(InstallerActivityManager.getInstance()).exitInstallation(EXIT_INSTALLER_REASON.SESSION_CREATION_FAILED);
			
		}
		
		@Override
		public void sessionOnChannelRetunedFailed () {
			ntf.notifyAllObservers(EventIDs.EVENT_SESSION_TUNE_FAILED, "");
		}
		
		@Override
		public void sessionOnChannelChangeStarted () {
			
		}

		
		@Override
		public void sessionOnChannelChangeCompleted (Uri channelUri) {
			
		}
	};
	
	public void setSessionTuneWithMedium(SessionHandlerTIF.SESSION_MEDIUM argMedium){
		Log.d(TAG, "setSessionTuneWithMedium " + argMedium);
		euInst.setSessionTuneWithMedium(argMedium);
	}
	
	public void closeTIFSession(SessionHandlerTIF.SESSION_PURPOSE argSessionPurpose) {
		Log.d(TAG, "closeTIFSession " + argSessionPurpose);
		if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER) {
			if(mSessionInstanceMain != null){
				mSessionInstanceMain.closeSession();
				mSessionInstanceMain = null;
			}
		} else if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_OBSERVER) {
			if(mSessionService != null){
				mSessionService.closeSession();
			}
		}
	}

	/**
	  * method to register tv uri to get onchange
	  */
	 public void registerTvProviderContentObservers()
	 {
		  Log.d(TAG,"registerTvProviderContentObservers()");
		  try{
			  if((ctx!=null) && (isChannelInstall(ctx)))
			  {
				  ContentResolver cr = ctx.getContentResolver();
				  mObserver = new TvProviderListener(TVPHandler);
				  cr.registerContentObserver(TvContract.Channels.CONTENT_URI, true,mObserver );
			  }
		  }
		 catch(Exception e)	
		 {
			 Log.d(TAG,"Exception:"+e);
		 }
		  
	 }
	 
	 /**
	  * method to unregister the tv uri
	  */
	 public void unregisterTvProviderContentObservers() 
	 {
		  if(ctx!=null && mObserver != null)
		  {
			  ContentResolver cr = ctx.getContentResolver();
			  cr.unregisterContentObserver( mObserver );
			  mObserver = null;
			  Log.d(TAG,"unregisterTvProviderContentObservers");
		  }
	  }
	  
	private class TvProviderListener extends ContentObserver
	{

		public TvProviderListener(Handler handler) 
		{
			super(handler);
		}

		public void onChange(boolean selfChange,Uri uri) 
		{
		//	Log.d(TAG,"TvProviderNotificationReceiver:onChange() called uri: "+uri + " selfChange: " + selfChange);
			if(!selfChange){
				long channelid = 0;

				TcInstallerTvProviderData TvpData = new TcInstallerTvProviderData();
				byte[]  BlobData = null;
				String NewPreset;

				// execute block if uri is tv uri
				if(TvContract.isChannelUriForTunerInput(uri))
				{
					try
					{
						channelid = Long.parseLong(uri.getLastPathSegment());

					//	Log.d(TAG, "TvProviderNotificationReceiver with _ID " + channelid);

						/*Get Data from Tvprovider*/
						String[] projection = new String[] {Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_TYPE, Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_DISPLAY_NUMBER, Channels.COLUMN_DISPLAY_NAME, Channels.COLUMN_SEARCHABLE, Channels.COLUMN_INTERNAL_PROVIDER_DATA, Channels.COLUMN_VERSION_NUMBER, Channels._ID, Channels.COLUMN_NETWORK_AFFILIATION};
						String mselection = Channels._ID + "= ?" ;
						String[] mselectionargs = new String[] { String.valueOf(channelid)};

						Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

						if((cursor != null) && (cursor.moveToFirst() != false)) {
							String ChannelType = cursor.getString(0);
							if((ChannelType.equalsIgnoreCase(Channels.TYPE_DVB_T)) ||(ChannelType.equalsIgnoreCase(Channels.TYPE_DVB_C)) || (ChannelType.equalsIgnoreCase(Channels.TYPE_DVB_T2)) || (ChannelType.equalsIgnoreCase(Channels.TYPE_PAL))){
							//	Log.d(TAG, "DVBTC Channel " + ChannelType);
								IsChanneRenameInProgress = true;
								/*Update channel in MW*/
								Log.d(TAG, "Adding Data to MW");
								TvpData.DecoderType = GetDecoderType(cursor.getString(0));
								TvpData.OriginalNetworkId= cursor.getInt(2);
								TvpData.Tsid= cursor.getInt(3);
								TvpData.ServiceId= cursor.getInt(4);
								TvpData.PresetNumber= cursor.getInt(5);
								TvpData.ChannelName= cursor.getString(6);
								TvpData.NumericSelect = cursor.getInt(7);
								BlobData = cursor.getBlob(8);
								TvpData.UniqueId = cursor.getInt(10);
								NewPreset = cursor.getString(11);
								try {
									TvpData.NewPreset = (NewPreset.equalsIgnoreCase("New") ? 1 : 0);
								}
								catch (Exception e)
								{
								}
								AddMWRecord(TvpData,BlobData);
							}
							else{
								//Log.d(TAG, "Non DVBTC Channel " + ChannelType);
							}
						}
						else{
						Log.d(TAG, "Null cursor " + cursor);
	 
						}
						if(cursor != null){ 
							cursor.close();
							cursor = null;
						}

					}
					catch(Exception e)
					{
						Log.d(TAG,"onChange():Exception:"+e);
					}
				}
			}
		}
	};

	
	 /**
	  * this method is used to check whether tv channels are installed or not
	  * @param:cxt-application context
	  * @return:true if channels are installed otherwise false
	  */
	 public boolean isChannelInstall(Context cxt) throws Exception
	 {
		 String []projection=new String[]{Channels.COLUMN_DISPLAY_NUMBER};
		 String  packageSelection=Channels.COLUMN_PACKAGE_NAME+"=?";
		 String[] packageSelectionArgs=new String[]{PACKAGE_NAME_TUNERSERVICE};
		 
		 Cursor cursor=cxt.getContentResolver().query(Channels.CONTENT_URI, projection,
						   packageSelection,packageSelectionArgs, null);
		 int count=0;
		 
		 if(cursor!=null)
		 {
			 count = cursor.getCount();
			 cursor.close();
			 cursor = null;
			 Log.d(TAG,"isInstallChannels() called: count:"+count);
			 
			 if(count>0)
				 return true;
		 }
		 
		 return false;
 	}
	
	public void setParentalRating(int argCountryIDinTVS, String argAgeRating) {
		Log.d(TAG, "setParentalRating ");
		TvInputManager mTvInputManager = (TvInputManager) ctx.getSystemService(Context.TV_INPUT_SERVICE);
		Log.d(TAG, "mTvInputManager: " + mTvInputManager);
		if(mTvInputManager != null){
			List<TvContentRating> contentRatingStringList = mTvInputManager.getBlockedRatings();
			Log.d(TAG, "contentRatingString " + contentRatingStringList);

			TvContentRating contentRatingStr = null;
			String mainRating = "";
			String ratingSystem = "";
			String domain = "";
			List<String> subRatingList = null;

			if (contentRatingStringList != null) {
				
				if (contentRatingStringList.size() > 0) {
					for (int contentRatingIndex = 0; contentRatingIndex < contentRatingStringList.size(); contentRatingIndex++) {
						// print existing content ratings
						contentRatingStr = contentRatingStringList.get(contentRatingIndex);
						Log.d(TAG, "ratingStr [" + contentRatingIndex + "]:" + contentRatingStr);
						mainRating = contentRatingStr.getMainRating();
						Log.d(TAG, "mainRating:" + mainRating);
						ratingSystem = contentRatingStr.getRatingSystem();
						Log.d(TAG, "ratingSys:" + ratingSystem);
						domain = contentRatingStr.getDomain();
						Log.d(TAG, "domain:" + domain);
						subRatingList = contentRatingStr.getSubRatings();
						if(subRatingList != null){
							for (int subRatingIndex = 0; subRatingIndex < subRatingList.size(); subRatingIndex++) {
								Log.d(TAG, "subratingList [" + subRatingIndex + "]:" + subRatingList.get(subRatingIndex));
							}
						}
					}
				}
				
				domain = new String("org.droidtv.tunerservice");
				Log.d(TAG, "set domain:"+domain);
				//ratingSystem = new String("FR_DVB_18");
				
				switch (argCountryIDinTVS) {
				case TvSettingsDefinitions.InstallationCountryConstants.SPAIN:
					ratingSystem = "ES_DVB";
					break;
				case TvSettingsDefinitions.InstallationCountryConstants.FRANCE:
					ratingSystem = "FR_DVB";
					break;
				case TvSettingsDefinitions.InstallationCountryConstants.SINGAPORE:
					ratingSystem = "SG_TV";
					break;
				case TvSettingsDefinitions.InstallationCountryConstants.NEWZEALAND:
					ratingSystem = "NZ_TV";
					break;
				case TvSettingsDefinitions.InstallationCountryConstants.AUSTRALIA:
					ratingSystem = "AU_TV";
					break;
				default:
					ratingSystem = "DVB";
					break;
				}
				
				Log.d(TAG, "set ratingSystem:"+ratingSystem);
				
				mainRating = new String("DVB_NONE"); // initialize with default
				if(ratingSystem == "DVB"){
					if(argAgeRating == "none"){
						mainRating = new String("DVB_NONE");
					}else if(argAgeRating == "17"){
						mainRating = new String("DVB_17");
					}else if(argAgeRating == "18"){
						mainRating = new String("DVB_18");
					}
				}else if(ratingSystem == "ES_DVB"){
				    if(argAgeRating == "none"){
						mainRating = new String("ES_DVB_NONE");
					}else if(argAgeRating == "17"){
						mainRating = new String("ES_DVB_17");
					}else if(argAgeRating == "18"){
						mainRating = new String("ES_DVB_18");
					}
				}else if(ratingSystem == "FR_DVB"){
					if(argAgeRating == "none"){
						mainRating = new String("FR_DVB_NONE");
					}else if(argAgeRating == "17"){
						mainRating = new String("FR_DVB_17");
					}else if(argAgeRating == "18"){
						mainRating = new String("FR_DVB_18");
					}
				}else if(ratingSystem == "SG_TV"){
				       if(argAgeRating == "none")
				              mainRating = new String("SG_TV_NONE");
				}else if(ratingSystem == "AU_TV"){
				       if(argAgeRating == "none")
				              mainRating = new String("AU_TV_NONE");
				}else if(ratingSystem == "NZ_TV"){
				       if(argAgeRating == "none")
				              mainRating = new String("NZ_TV_NONE");
				}
				Log.d(TAG, "set mainRating:"+mainRating);
				
				contentRatingStr = TvContentRating.createRating(domain, ratingSystem, mainRating, (String[]) null);
				
				if (contentRatingStr != null) {
					if (contentRatingStringList.size() > 0) {
						// already content rating is there, set the content rating on the 0th item, clear full list
						int length = contentRatingStringList.size();
						
						for (int contentRatingIndex = 0; contentRatingIndex < length; contentRatingIndex++) {
							mTvInputManager.removeBlockedRating(contentRatingStringList.get(contentRatingIndex));
						}
					}
					
					// content rating not there add new content rating in 0th position
					mTvInputManager.setParentalControlsEnabled(true);
					mTvInputManager.addBlockedRating(contentRatingStr);
				}
			}
		}
	}

	public EuInstallerTC getEuinstallerTCInstance(){
		return euInst;
	}

	// logo association, NativeAPIWrapper is always registered to logoassociationhandler
	// argListner null then 
	public void startLogoAssociation(DVBTOrDVBC argMedium, ILogoAssociationListner argListner){
		Log.d(TAG,"startLogoAssociation ");
		IsLogoAssociationOngoing = true;
		logoAssoListner = argListner;
		logoAssoHandler.startLogoAssociation(argMedium, this);
	}
		
	@Override
	public void notifyLogoAssociationComplete() {
		/*Cache Majorversion here to ignore the version change notification triggered by logo association, in case notification is delayed */
		cachedMajorVesrion = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, 0);
		IsLogoAssociationOngoing = false;
		if(logoAssoListner != null){
			logoAssoListner.notifyLogoAssociationComplete();
		}
	}

	@Override
	public void notifyLogoAssociationAborted() {
		cachedMajorVesrion = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, 0);
		IsLogoAssociationOngoing = false;
		if(logoAssoListner != null){
			logoAssoListner.notifyLogoAssociationAborted();
		}
	}
	
	public boolean ifWaitForLogoAssociation(){
		boolean returnStatus = true;
		if(getOperatorFromMW() == NativeAPIEnums.Operators.CanalDigital){
			returnStatus = false;
		}
		Log.d(TAG,"ifWaitForLogoAssociation " + returnStatus);
		return returnStatus;
	}

	/* This Function if return TRUE - HBBTV On Off Screen will be shown to user*/
	public boolean ifCountrySupportsHBBTV(){
		boolean returnStatus = false;
		int tvscCountryID = mTvSettingsManager.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		switch (tvscCountryID) {
			case TvSettingsDefinitions.InstallationCountryConstants.AUSTRIA:
			case TvSettingsDefinitions.InstallationCountryConstants.CROATIA:
			case TvSettingsDefinitions.InstallationCountryConstants.BELGIUM:
			case TvSettingsDefinitions.InstallationCountryConstants.CZECHREP:
			case TvSettingsDefinitions.InstallationCountryConstants.FINLAND:
			case TvSettingsDefinitions.InstallationCountryConstants.FRANCE:
			case TvSettingsDefinitions.InstallationCountryConstants.GERMANY:
			case TvSettingsDefinitions.InstallationCountryConstants.GREECE:
			case TvSettingsDefinitions.InstallationCountryConstants.HUNGARY:
			case TvSettingsDefinitions.InstallationCountryConstants.LUXEMBOURG:
			case TvSettingsDefinitions.InstallationCountryConstants.NETHERLANDS:
			case TvSettingsDefinitions.InstallationCountryConstants.NORWAY:
			case TvSettingsDefinitions.InstallationCountryConstants.POLAND:
			case TvSettingsDefinitions.InstallationCountryConstants.PORTUGAL:
			case TvSettingsDefinitions.InstallationCountryConstants.ROMANIA:
			case TvSettingsDefinitions.InstallationCountryConstants.RUSSIA:
			case TvSettingsDefinitions.InstallationCountryConstants.SERBIA:
			case TvSettingsDefinitions.InstallationCountryConstants.SLOVAKIA:
			case TvSettingsDefinitions.InstallationCountryConstants.SLOVENIA:
			case TvSettingsDefinitions.InstallationCountryConstants.SPAIN:
			case TvSettingsDefinitions.InstallationCountryConstants.SWEDEN:
			case TvSettingsDefinitions.InstallationCountryConstants.SWITZERLAND:
			case TvSettingsDefinitions.InstallationCountryConstants.TURKEY:
			case TvSettingsDefinitions.InstallationCountryConstants.OTHER:
			case TvSettingsDefinitions.InstallationCountryConstants.ESTONIA:
			case TvSettingsDefinitions.InstallationCountryConstants.LITHUANIA:
			case TvSettingsDefinitions.InstallationCountryConstants.LATVIA:
			case TvSettingsDefinitions.InstallationCountryConstants.KAZAKHSTAN:
			case TvSettingsDefinitions.InstallationCountryConstants.BULGARIA:
			case TvSettingsDefinitions.InstallationCountryConstants.CHINA:
			case TvSettingsDefinitions.InstallationCountryConstants.UKRAINE:
			case TvSettingsDefinitions.InstallationCountryConstants.ALBANIA:
			case TvSettingsDefinitions.InstallationCountryConstants.ARMENIA:
			case TvSettingsDefinitions.InstallationCountryConstants.AZERBAIJAN:
			case TvSettingsDefinitions.InstallationCountryConstants.BELARUS:
			case TvSettingsDefinitions.InstallationCountryConstants.BOSNIAANDHERZEGOVINA:
			case TvSettingsDefinitions.InstallationCountryConstants.GEORGIA:
			case TvSettingsDefinitions.InstallationCountryConstants.MONTENEGRO:
			case TvSettingsDefinitions.InstallationCountryConstants.ISRAEL:
			case TvSettingsDefinitions.InstallationCountryConstants.MACEDONIAFYROM:
			case TvSettingsDefinitions.InstallationCountryConstants.PARAGUAY:
			case TvSettingsDefinitions.InstallationCountryConstants.URUGUAY:	
				returnStatus = true;
				break;	
			case TvSettingsDefinitions.InstallationCountryConstants.SINGAPORE:
			case TvSettingsDefinitions.InstallationCountryConstants.MALAYSIA:	
			case TvSettingsDefinitions.InstallationCountryConstants.TAIWAN:
			case TvSettingsDefinitions.InstallationCountryConstants.NEWZEALAND:
			case TvSettingsDefinitions.InstallationCountryConstants.AUSTRALIA:
			case TvSettingsDefinitions.InstallationCountryConstants.THAILAND:
			case TvSettingsDefinitions.InstallationCountryConstants.VIETNAM:	
			case TvSettingsDefinitions.InstallationCountryConstants.UNITEDARABEMIRATES:	
			case TvSettingsDefinitions.InstallationCountryConstants.SOUTHAFRICA:
			case TvSettingsDefinitions.InstallationCountryConstants.UK:
				returnStatus = false;
				/*The above changes are brought in accordance with RMCR:3578*/
				break;	
			default:
				returnStatus = false;
				break;
		}
		Log.d(TAG,"ifCountrySupportsHBBTV " + returnStatus);
		return returnStatus;
	}
	
	public void setHBBTVStatus(boolean ifOn)
	{
		Log.d(TAG,"setHBBTVStatus " + ifOn);
		if(ifOn){
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSHBBTV, 0, 1);
		}else{
			mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSHBBTV, 0, 0);
		}
	}

    public void clearPersistent() {
		if (STUB_MODE) {
			
		} else {
            Log.d(TAG, "clearPersistent()");
            euInst.ClearPersistent();		
		}
	}

	public int addExtSource() {
		int number = 0;
		Log.d(TAG, "addExtSource");
		if (!CheckExternalSourceExist()) {
			number = AddExternalSourceToTvProvider(getBiggestDisplayNumber());
			//number = addMediaBroswerToTvProvider(number);
			SyncHTvProvider();

		}
		return number;
	}
	
	public void refreshSpecialChannelsForMyChoice() {
		Log.d(TAG, "refreshSpecialChannelsForMyChoice() is called.");
		
		String fsSelection = HtvContract.HtvChannelSetting._ID + "<?";
		String[] fsvSelectionArgs = new String[]{String.valueOf(0)};
		
		ctx.getContentResolver().delete(HtvContract.HtvChannelSetting.CONTENT_URI, fsSelection, fsvSelectionArgs);
		
		addSpecialChannelsForMyChoice();
	}
	
	private void addSpecialChannelsForMyChoice() {
				
		ContentValues []val=new ContentValues[5];
		val[0] = new ContentValues();
		val[1] = new ContentValues();
		val[2] = new ContentValues();
		val[3] = new ContentValues();
		val[4] = new ContentValues();
		val[0].put (HtvContract.HtvChannelSetting._ID, "-1");
		val[0].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,HtvContract.HtvChannelSetting.TYPE_MEDIABROSWER);
		val[0].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, "10001");
		val[0].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID ,"10001");
		val[1].put (HtvContract.HtvChannelSetting._ID, "-2");
		val[1].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,HtvContract.HtvChannelSetting.TYPE_PTA);
		val[1].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, "10002");
		val[1].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID ,"10002");
		val[2].put (HtvContract.HtvChannelSetting._ID, "-3");
		val[2].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,HtvContract.HtvChannelSetting.TYPE_MIRACAST);
		val[2].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, "10003");
		val[2].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID ,"10003");
		val[3].put (HtvContract.HtvChannelSetting._ID, "-4");
		val[3].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,HtvContract.HtvChannelSetting.TYPE_APPS);
		val[3].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, "10004");
		val[3].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID ,"10004");
		val[4].put (HtvContract.HtvChannelSetting._ID, "-5");
		val[4].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,HtvContract.HtvChannelSetting.TYPE_INTERNETBROSWER);
		val[4].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, "10005");
		val[4].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID ,"10005");
		ctx.getContentResolver().bulkInsert(HtvContract.HtvChannelSetting.CONTENT_URI ,val);
	}

	public int addExtSourceToTvProvider(int biggestnumber) {
		Log.d(TAG, "addExtSource");
		int number = 0;
		if (!CheckExternalSourceExist()) {
			number = AddExternalSourceToTvProvider(biggestnumber);
			//number = addMediaBroswerToTvProvider(number);
			// SyncHTvProvider();

		}
		return number;
	}

	public void addMediaChannelToTvProvider(int number) {
		Log.d(TAG, "addMediaChannel");

		AddMediaChannelToTvProvider(number);
	}
// for TF415PHIEUMTK66-2528 the number of source is wrong in channel list after change option code (disable/ enable SCART/YPbPr source) .
	public void OptionCoder_ExternalSource() {
		Log.d(TAG, "OptionCoder_ExternalSource");
			DeleteExternalSourceFromTvProvider();
			int number = getBiggestDisplayNumber();
			AddExternalSourceToTvProvider(number);
			SyncHTvProvider();
	}

	public void SyncHTvProvider() {		
		String[] mProjection ={ TvContract.Channels._ID,
   					TvContract.Channels.COLUMN_DISPLAY_NUMBER,
					TvContract.Channels.COLUMN_VERSION_NUMBER,
					TvContract.Channels.COLUMN_BROWSABLE,
					TvContract.Channels.COLUMN_DISPLAY_NAME,
					TvContract.Channels.COLUMN_NETWORK_AFFILIATION
					};
		String mselection = null;
		String[]	mselectionargs = null;
		int RowsDeleted = ctx.getContentResolver().delete(HtvContract.HtvChannelSetting.CONTENT_URI,mselection,mselectionargs);
		Log.d(TAG,"PopulateTvContentProvider HtvContract.HtvChannelSetting: RowsDeleted "+RowsDeleted);
		int RowsDeleted2 = ctx.getContentResolver().delete(HtvContract.HtvThemeTvSetting.CONTENT_URI,mselection,mselectionargs);
		Log.d(TAG,"PopulateTvContentProvider HtvContract.HtvThemeTvSetting: RowsDeleted "+RowsDeleted2);
		Cursor cursor  = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI,mProjection,null,null,null,null);
		Log.d (TAG, "query tv.db");
		
		if(cursor != null) {
			
			int rows_num = cursor.getCount();
			Log.d (TAG, "cursor.getCount"+rows_num);			
			
			if(rows_num != 0) {
				
				ContentValues []val3=new ContentValues[rows_num];
				
				Log.d (TAG, "rows_num != 0");
				cursor.moveToFirst();
				for(int i=0; i<rows_num; i++){
					val3[i] = new ContentValues();
					val3[i].put (HtvContract.HtvChannelSetting._ID ,cursor.getInt(0)); /* Check with Mounesh/Pavan what to fill here */
					val3[i].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER,cursor.getString(1));
					if(cursor.getInt(2)==0){
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,"TYPE_TUNER");
						if(mbUseHtvDTRTuneType) {
							String fsStr = cursor.getString(5);
							if(fsStr != null && fsStr.startsWith(HTV_DT_CHANNEL_FLAG)) {
								val3[i].put(HtvContract.HtvChannelSetting.COLUMN_SKIP1, "1");
								val3[i].put(HtvContract.HtvChannelSetting.COLUMN_SKIP2, "1");
							}							
						}
					}else if(cursor.getInt(2)==1){
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,"TYPE_TUNER");
						if(mbUseHtvDTRTuneType) {
							String fsStr = cursor.getString(5);
							if(fsStr != null && fsStr.startsWith(HTV_DT_CHANNEL_FLAG)) {
								val3[i].put(HtvContract.HtvChannelSetting.COLUMN_SKIP1, "1");
								val3[i].put(HtvContract.HtvChannelSetting.COLUMN_SKIP2, "1");
							}							
						}
					}else if(cursor.getInt(2)==2){
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,"TYPE_TUNER");
					} else if (cursor.getInt(2) == 10) {
						Log.d (TAG, "cursor.getString(4) ="+cursor.getString(4));
						if (cursor.getInt(3)==0) {
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE, "TYPE_SOURCE");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_SKIP1, "1");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_FREEPKG, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_PAYPKG1, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_PAYPKG2, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER, "0");
							val3[i].put(HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER, "0");
						} else {
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,"TYPE_SOURCE");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_FREEPKG,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG1,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG2,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER,"0");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER,"0");
							}
					} else if (cursor.getInt(2) == 12) {
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,"TYPE_FILE");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_FREEPKG,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG1,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG2,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER,"1");
							val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER,"1");
					}else if(cursor.getInt(2) == 11){
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE,"TYPE_OTHER");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_FREEPKG,"1");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG1,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG2,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER,"0");
						val3[i].put (HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER,"0");
					}
					val3[i].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID ,cursor.getInt(0));
					cursor.moveToNext();

				} 
				
				ctx.getContentResolver().bulkInsert(HtvContract.HtvChannelSetting.CONTENT_URI ,val3);
			}
			
			cursor.close();
			cursor = null;
		}
		
		addSpecialChannelsForMyChoice();		
	}
	public Boolean CheckExternalSourceExist () {
		String[] projection = new String[] {Channels._ID,};
		String 	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?";
		String[]	mselectionargs=new String[]{"10"};
		boolean fbIsExistent = false;
		Cursor ExternalSourceCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		
		if(ExternalSourceCursor != null) {
			
			if(ExternalSourceCursor.getCount() != 0)
				fbIsExistent = true;
			
			ExternalSourceCursor.close();
			ExternalSourceCursor = null;
		}
		
		return fbIsExistent;
	}

	public void DeleteExternalSourceFromTvProvider() {
		String[] args = { "10" };
		ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,
				new StringBuilder(TvContract.Channels.COLUMN_VERSION_NUMBER).append("=?").toString(), args);
	}

	public Boolean CheckMediaChannelExist() {
		String[] projection = new String[] { Channels._ID, };
		String mselection = Channels.COLUMN_VERSION_NUMBER + "= ?";
		String[] mselectionargs = new String[] { "12" };
		boolean fbIsExistent = false;
		Cursor ExternalSourceCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection,
				mselection, mselectionargs, null);
		
		if(ExternalSourceCursor != null) {
			
			if(ExternalSourceCursor.getCount() != 0)
				fbIsExistent = true;
			
			ExternalSourceCursor.close();
			ExternalSourceCursor = null;
		}

		return fbIsExistent;
	}

	public void DeleteMediaChannelFromTvProvider() {
		String[] args = { "12" };
		ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,
				new StringBuilder(TvContract.Channels.COLUMN_VERSION_NUMBER).append("=?").toString(), args);
	}

	public int AddExternalSourceToTvProvider(int bigestDisplayNumber) {
		Log.d(TAG, "AddExternalSourceToTvProvider " + bigestDisplayNumber);
		mTvInputManager = (TvInputManager) ctx.getSystemService(Context.TV_INPUT_SERVICE);
		List<TvInputInfo> tvInputList = mTvInputManager.getTvInputList();
		Log.d(TAG, "tvInputList size:" + tvInputList.size());
		TvInputInfo []temp=new TvInputInfo[8];
			
		int length=0;
		ITvSettingsManager mITvMgr;
		mITvMgr = ITvSettingsManager.Instance.getInterface();
		int t=0;
		if (!tvInputList.isEmpty()) {
			Log.d(TAG, "AddExternalSourceToTvProvider if");
			for (int i = 0; i < tvInputList.size(); i++) {
				Log.d(TAG, "tvInputList ID: " + tvInputList.get(i).getId());
				Log.d(TAG, "tvInputList i: " + i);
				String tvInputId = tvInputList.get(i).getId();
				
				if (tvInputId.contains("HW9") || tvInputId.contains("HW10") || tvInputId.contains("HW11")|| (tvInputId.contains("HW12")&&mITvMgr.getInt(TvSettingsConstants.OPMHL, 0, 0)==1)
				|| tvInputId.contains("ComponentService")|| tvInputId.contains("ScartService")) {
					if (tvInputId.contains("HW9"))
						temp[0]=tvInputList.get(i);
					else if (tvInputId.contains("HW10"))
						temp[1]=tvInputList.get(i);
					else if (tvInputId.contains("HW11"))
						temp[2]=tvInputList.get(i);
					else if (tvInputId.contains("HW12"))
						temp[3]=tvInputList.get(i);
					else if (tvInputId.contains("ComponentService"))
						temp[4]=tvInputList.get(i);								
					else if (tvInputId.contains("ScartService"))
						temp[5]=tvInputList.get(i);

					++length;
				}
			}
		}

		Log.d(TAG, "tvInputList length: " + length);				
		ContentValues []val2=new ContentValues[length];
		int tmp = 0;
		int count=0;
				
		for (int i = 0; i < 8;i++ ) {	
			IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
			if(count<length)
			{
				val2[count] = new ContentValues();
			}
			if(temp[i]!=null){
				Log.d(TAG, "temp ID: " + temp[i].getId());
				Log.d(TAG, "tvInputList i: " + i);
				if (temp[i].getId().contains("TunerService")) {


				} else {						
					String tvInputId = temp[i].getId();
					String display_name = null;
					String source_uri = null;

					if (tvInputId.contains("HW9")) {
						display_name = "HDMI1";
						source_uri = "org.droidtv.hdmiService/.HdmiService/HW9";

					} else if (tvInputId.contains("HW10")) {
						display_name = "HDMI2";
						source_uri = "org.droidtv.hdmiService/.HdmiService/HW10";
							

					} else if (tvInputId.contains("HW11")) {
						display_name = "HDMI3";
						source_uri = "org.droidtv.hdmiService/.HdmiService/HW11";
					} else if (tvInputId.contains("HW12")) {
						display_name = "HDMI4";
						source_uri = "org.droidtv.hdmiService/.HdmiService/HW12";

					} else if (tvInputId.contains("ComponentService")) {
						display_name = "YPBPR";
						source_uri = "org.droidtv.componentService/.ComponentService/HW4";

					} else if (tvInputId.contains("ScartService")) {
						display_name = "SCART";
						source_uri = "org.droidtv.scartService/.ScartService/HW7";
							
					} else {
						Log.d(TAG, "Other type [" + tvInputId + "]");
						continue;
					}

					val2[count].put (Channels.COLUMN_INPUT_ID,"2"); /* Check with Mounesh/Pavan what to fill here */
					val2[count].put (Channels.COLUMN_TYPE,TvContract.Channels.TYPE_OTHER);
					val2[count].put (Channels.COLUMN_SERVICE_TYPE,TvContract.Channels.SERVICE_TYPE_AUDIO_VIDEO);
					val2[count].put (Channels.COLUMN_ORIGINAL_NETWORK_ID,"0");
					val2[count].put (Channels.COLUMN_TRANSPORT_STREAM_ID,"0");
					val2[count].put (Channels.COLUMN_SERVICE_ID,"65535");
					val2[count].put (Channels.COLUMN_DISPLAY_NAME,display_name);
					val2[count].put (Channels.COLUMN_NETWORK_AFFILIATION , "");
					val2[count].put (Channels.COLUMN_DESCRIPTION, "");
					int checkstatus =  mITvMgr.getInt(TvSettingsConstants.PBSMGR_PROPERTY_SELECTABLE_AV, 0, 0);
					if ((checkstatus & TvSettingsDefinitions.PbsSelectableAvFlag.PBSMGR_SELECTABLE_AV_HDMI_4_FLAG)==0&&display_name.equals("HDMI4")) {
						val2[count].put(Channels.COLUMN_BROWSABLE, "0");
					} else if((checkstatus & TvSettingsDefinitions.PbsSelectableAvFlag.PBSMGR_SELECTABLE_AV_HDMI_1_FLAG)==0&&display_name.equals("HDMI1")){
						val2[count].put(Channels.COLUMN_BROWSABLE, "0");
					}else if((checkstatus & TvSettingsDefinitions.PbsSelectableAvFlag.PBSMGR_SELECTABLE_AV_HDMI_2_FLAG)==0&&display_name.equals("HDMI2")){
						val2[count].put(Channels.COLUMN_BROWSABLE, "0");
					}else if((checkstatus & TvSettingsDefinitions.PbsSelectableAvFlag.PBSMGR_SELECTABLE_AV_HDMI_3_FLAG)==0&&display_name.equals("HDMI3")){
						val2[count].put(Channels.COLUMN_BROWSABLE, "0");
					}else if((checkstatus & TvSettingsDefinitions.PbsSelectableAvFlag.PBSMGR_SELECTABLE_AV_SCART_FLAG)==0&&display_name.equals("SCART")){
						val2[count].put(Channels.COLUMN_BROWSABLE, "0");
					}else if((checkstatus & TvSettingsDefinitions.PbsSelectableAvFlag.PBSMGR_SELECTABLE_AV_YPBPR_FLAG)==0&&display_name.equals("YPBPR")){
						val2[count].put(Channels.COLUMN_BROWSABLE, "0");
					}
					else{
						val2[count].put(Channels.COLUMN_BROWSABLE, "1");
					}

					tmp = bigestDisplayNumber + count+1;
					Log.d(TAG, "AddExternalSourceToTvProvider add display num " +tmp );
					val2[count].put(Channels.COLUMN_DISPLAY_NUMBER, Integer.toString(bigestDisplayNumber + count+1));
					keyvalues.put(ITvContractExtras.C_URI_BLOB, source_uri);
					try {
						val2[count].put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,keyvalues.getBlob());
					} catch (Exception e) {
						Log.e(TAG, "Error FormBlobData  " + e);
						e.printStackTrace();
					}

					val2[count].put (Channels.COLUMN_VERSION_NUMBER,"10");
					Log.d (TAG, "val["+count+"] "+ val2[count].toString());
					count++;
				}
			}
		} 

		Log.d (TAG, "Going to do bulk insert external source");
		ctx.getContentResolver().bulkInsert(TvContract.Channels.CONTENT_URI ,val2);
		Log.d (TAG, "finish bulk insert external source");
		return bigestDisplayNumber + count;
	}
	public int addMediaBroswerToTvProvider(int display_number) {
	IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
	ContentValues val3 =new ContentValues();
	String display_name = "MediaBrowser";
	String source_uri = "usb";
						val3.put (Channels.COLUMN_INPUT_ID,"2"); /* Check with Mounesh/Pavan what to fill here */
					val3.put (Channels.COLUMN_TYPE,TvContract.Channels.TYPE_OTHER);
					val3.put (Channels.COLUMN_SERVICE_TYPE,TvContract.Channels.SERVICE_TYPE_AUDIO_VIDEO);
					val3.put (Channels.COLUMN_ORIGINAL_NETWORK_ID,"0");
					val3.put (Channels.COLUMN_TRANSPORT_STREAM_ID,"0");
					val3.put (Channels.COLUMN_SERVICE_ID,"65535");
					val3.put (Channels.COLUMN_DISPLAY_NAME,display_name);
					val3.put (Channels.COLUMN_NETWORK_AFFILIATION , "");
					val3.put (Channels.COLUMN_DESCRIPTION, "");
					val3.put(Channels.COLUMN_BROWSABLE, "1");
					val3.put(Channels.COLUMN_DISPLAY_NUMBER, Integer.toString(display_number+1));
					keyvalues.put(ITvContractExtras.C_URI_BLOB, source_uri);
					try {
						val3.put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,keyvalues.getBlob());
					} catch (Exception e) {
						Log.e(TAG, "Error FormBlobData  " + e);
						e.printStackTrace();
					}

					val3.put (Channels.COLUMN_VERSION_NUMBER,"10");
					Log.d (TAG, "Going to do bulk insert external source");
					ctx.getContentResolver().insert(TvContract.Channels.CONTENT_URI ,val3);
					Log.d (TAG, "finish bulk insert external source");
		return display_number + 1;
					}
	public void AddMediaChannelToTvProvider(int mediaChannelNumber) {
				int errCount = 0;
				String mediaChannelPath = "/data/data/HTV/Clone/Clone_data/MediaChannels/";

				try {
					File file = new File(mediaChannelPath);
					if (file.exists()) {
						String[] fileList = file.list();

						Log.d(TAG, "Local media size " + fileList.length);

						if (fileList.length > 0) {
							int lastIndexOfString = 0;
							ContentValues[] valMedia = new ContentValues[fileList.length];

							for (int Loop = 0; Loop < fileList.length; ++Loop) {
								IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
								valMedia[Loop] = new ContentValues();

								Log.i(TAG, "[" + Loop + "] " + fileList[Loop]);
								valMedia[Loop].put (Channels.COLUMN_INPUT_ID, "2");
								valMedia[Loop].put (Channels.COLUMN_TYPE, TvContract.Channels.TYPE_OTHER);
								valMedia[Loop].put (Channels.COLUMN_SERVICE_TYPE, TvContract.Channels.SERVICE_TYPE_OTHER);
								valMedia[Loop].put (Channels.COLUMN_ORIGINAL_NETWORK_ID, "0");
								valMedia[Loop].put (Channels.COLUMN_TRANSPORT_STREAM_ID, "0");
								valMedia[Loop].put (Channels.COLUMN_SERVICE_ID, "65535");
								++errCount;
								lastIndexOfString = fileList[Loop].lastIndexOf('.');
								if (lastIndexOfString > 0) {
									valMedia[Loop].put (Channels.COLUMN_DISPLAY_NAME, fileList[Loop].substring(0, lastIndexOfString));
								} else {
									valMedia[Loop].put (Channels.COLUMN_DISPLAY_NAME, fileList[Loop]);
								}
								valMedia[Loop].put (Channels.COLUMN_BROWSABLE, "1");
								valMedia[Loop].put (Channels.COLUMN_DISPLAY_NUMBER, Integer.toString(++mediaChannelNumber));
								valMedia[Loop].put (Channels.COLUMN_VERSION_NUMBER, "12");
								++errCount;
								keyvalues.put (ITvContractExtras.C_URI_BLOB, new StringBuilder(mediaChannelPath).append(fileList[Loop]).toString());
								++errCount;
								valMedia[Loop].put (Channels.COLUMN_INTERNAL_PROVIDER_DATA, keyvalues.getBlob());
								errCount = 0;
							}

							Log.d (TAG, "Going to do bulk insert local media");
							ctx.getContentResolver().bulkInsert(TvContract.Channels.CONTENT_URI, valMedia);
							Log.d (TAG, "finish bulk insert local media");
						} else {
							Log.d (TAG, "No local media file");
						}
					} else {
						Log.d (TAG, "No local media folder");
					}
				} catch (Exception e) {
					Log.e(TAG, "Local Media errCount " + errCount);
					e.printStackTrace();
				}
			}
	public void mSettingOnOffDiversityOfHBBTVStatus(int country)
	{
		Log.d(TAG,"mSettingOnOffDiversityOfHBBTVStatus Installed Country" +country);

		switch(country)
		{
			case TvSettingsDefinitions.InstallationCountryConstants.SINGAPORE:
			case TvSettingsDefinitions.InstallationCountryConstants.MALAYSIA:	
			case TvSettingsDefinitions.InstallationCountryConstants.TAIWAN:
			case TvSettingsDefinitions.InstallationCountryConstants.THAILAND:
		  /*case TvSettingsDefinitions.InstallationCountryConstants.AUSTRALIA:*/
		  /*removed due to RMCR:3578*/
			case TvSettingsDefinitions.InstallationCountryConstants.VIETNAM:	
			case TvSettingsDefinitions.InstallationCountryConstants.UNITEDARABEMIRATES:	
			case TvSettingsDefinitions.InstallationCountryConstants.SOUTHAFRICA:
				setHBBTVStatus(false);
				break;
			default:
				setHBBTVStatus(true);
				break;
		}
	}
	
	public void setUseHtvDTRTuneType(boolean abIsUse, boolean abIsDVBT) {
		Log.d(TAG, "setUseHtvDTRTuneType() is called. IsUse:" + abIsUse);
		if(abIsUse) {
			mbUseHtvDTRTuneType = true;
			meHtvDTRTuneType = abIsDVBT?NativeAPIEnums.DVBTOrDVBC.DVBT:NativeAPIEnums.DVBTOrDVBC.DVBC;
		}
		else
			mbUseHtvDTRTuneType = false;
	}
	
	public boolean isHtvDTChannelExistent() {
		
		boolean fiResult = false;
		String[] fsvProjection = new String[] {"_id"};
		String fsSelection = Channels.COLUMN_NETWORK_AFFILIATION + " = ? ";
		String[] fsvSelectionArgs = new String[] {HTV_DT_CHANNEL_FLAG};
		
		Cursor fCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, fsvProjection, fsSelection, fsvSelectionArgs, null);
		
		if(fCursor != null && fCursor.getCount() > 0)
			fiResult = true;
		
		if(fCursor != null) {
			fCursor.close();
			fCursor = null;
		}
		
		return fiResult;
	}
	
	public void RemoveHtvDTChannel() {
		
		Log.d(TAG, "RemoveHtvDTChannel() is called.");

		String fsSelection = Channels.COLUMN_NETWORK_AFFILIATION + " = ? ";
		String[] fsvSelectionArgs = new String[] {HTV_DT_CHANNEL_FLAG};
		ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI, fsSelection, fsvSelectionArgs);

		fsSelection = HtvContract.HtvChannelSettingBaseColumns.COLUMN_SKIP2 + " = ? ";
		fsvSelectionArgs = new String[] {String.valueOf(1)};
		
		ctx.getContentResolver().delete(HtvContract.HtvChannelSetting.CONTENT_URI, fsSelection, fsvSelectionArgs);
	}
	
	public void setIsDVBT2Scan(boolean abEnable){
		euInst.SetIsDVBT2Scan(abEnable?1:0);
	}
	
	public void setFocusedDVBT2PlpID(int aiPlpID){
		euInst.SetFocusedPlpId(aiPlpID);
	}
	
	public void setDTRMonitorServID(int fiServID) {
		euInst.PrepareChNameUpdate(0,fiServID);
	}
	
	public String getDTRMonitorServName() {
		return euInst.GetUpdatedChannelName();
	}
	
	public int getDTRMonitorServONID() {
		return euInst.GetUpdatedONID();
	}
	
	public int getDTRMonitorServTsID() {
		return euInst.GetUpdatedTsID();
	}
	
	public int getDTRMonitorSymbolRate() {
		return euInst.GetUpdatedSymbolRate();
	}
	
	public int getDTRMonitorBandwidth() {
		
		int[] fviBWs = new int[]{0};
		
		euInst.getActualChanBandwidth_JavaInst(fviBWs);
		
		return fviBWs[0];
	}
	
	public void setExtractScanResult(boolean abIsTrue) {
		euInst.SetExtractScanResult(abIsTrue?1:0);
	}

	public int getBiggestDisplayNumber() {
		int biggestnumber = 0;
		int number = 0;
		String[] mProjection = { TvContract.Channels.COLUMN_DISPLAY_NUMBER };
		Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, mProjection, null, null, null, null);
		
		if(cursor != null && cursor.getCount() > 0) {
			cursor.moveToFirst();
			
			do{
				try{
					number = Integer.parseInt(cursor.getString(0));
					
					if (number > biggestnumber)
						biggestnumber = number;
				}
				catch(Exception e) {
				}
			}
			while (cursor.moveToNext());			
		}
		
		if(cursor != null) {
			cursor.close();
			cursor = null;
		}
		
		return biggestnumber;
    }

	public int[] getHTVEmptyDisplayNumber(int[] TVdisplaynum,int biggestnumber) {
		int number = 0;
		int[] compare;
		int EmptyNum = 0;
		Arrays.sort(TVdisplaynum);
		String[] mProjection = { HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER };
		Cursor cursor = ctx.getContentResolver().query(HtvContract.HtvChannelSetting.CONTENT_URI, mProjection,  null, null, null);
        if(TVdisplaynum[TVdisplaynum.length-1]>biggestnumber) {
			biggestnumber = TVdisplaynum[TVdisplaynum.length - 1];
			compare = new int[TVdisplaynum[TVdisplaynum.length - 1]];
		}else {
			compare = new int[biggestnumber];
		}
		Log.d(TAG, "DisplayNumber biggestnumber " +biggestnumber);
		if(cursor != null && cursor.getCount() > 0){
			cursor.moveToFirst();
			Log.d(TAG, "htv cursor.getCount() " +cursor.getCount());
			do{
				try{
					number = Integer.parseInt(cursor.getString(0));
					Log.d(TAG, "htv number " +number);
					compare[number] = 999;
				} catch(Exception e) {

				}
			}while (cursor.moveToNext());
		}

		if(cursor != null) {
			cursor.close();
			cursor = null;
		}
        /*
		for(int Loop =0; Loop<TVdisplaynum.length;Loop++) {
			Log.d(TAG, "TVdisplaynum.length " + TVdisplaynum.length);
			if (compare[TVdisplaynum[Loop]] != 999 || (TVdisplaynum[Loop]>biggestnumber)) {
				compare[TVdisplaynum[Loop]] = 999;
				Log.d(TAG, "if [Loop] " + Loop + " TVdisplaynum[Loop] " + TVdisplaynum[Loop] + " compare[TVdisplaynum[Loop]] " +compare[TVdisplaynum[Loop]]);
			}else
			{
				for (int i = 1; i < compare.length; i++) {
					Log.d(TAG, "else [i] " + i + " TVdisplaynum[Loop] " + TVdisplaynum[Loop] + " compare[i] " + compare[i]);
					if(compare[i] != 999)
					{
						compare[i] = 999;
						TVdisplaynum[Loop] = i;
						Log.d(TAG, "else [Loop] " + Loop + " TVdisplaynum[Loop] " + TVdisplaynum[Loop] + " i  " + i + " compare[i] " + compare[i]);
						break;
					}
				}
			}
		}
		*/
		return TVdisplaynum;
	}
	public int getHTVBiggestDisplayNumber() {
		int biggestnumber = 0;
		int number = 0;
		
		String[] mProjection = { HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER };
		Cursor cursor = ctx.getContentResolver().query(HtvContract.HtvChannelSetting.CONTENT_URI, mProjection,  null, null, null);
		
		if(cursor != null && cursor.getCount() > 0){			
			cursor.moveToFirst();
			
			do{
				try{
					number = Integer.parseInt(cursor.getString(0));
					if (number > biggestnumber && number < 10000)
						biggestnumber = number;
				} catch(Exception e) {
					
				}
			}while (cursor.moveToNext());
		}
		
		if(cursor != null) {
			cursor.close();
			cursor = null;
		}
		
		return biggestnumber;
	}
	
	public boolean isBnoProduct() 
	{		
		boolean isBno = false;		
		int productType = -1;		
		try{			
			if(mTvSettingsManager != null){				
				productType =  mTvSettingsManager.getInt(TvSettingsConstants.OPPRODUCTTYPE, 0, 0);
				switch(productType){				
					case TvSettingsDefinitions.OpProductTypeConstants.BNO:						
						isBno = true;					
						break;				
					case TvSettingsDefinitions.OpProductTypeConstants.MARVELL:				
					case TvSettingsDefinitions.OpProductTypeConstants.MTK5593U:				
					case TvSettingsDefinitions.OpProductTypeConstants.MTK5593T:				
					case TvSettingsDefinitions.OpProductTypeConstants.MTK5593H:			
					case TvSettingsDefinitions.OpProductTypeConstants.MTK5593F:				
					case TvSettingsDefinitions.OpProductTypeConstants.HEVCBOX:				
					case TvSettingsDefinitions.OpProductTypeConstants.HOTELTV:						
						isBno = false;					
						break;				
					}			
				}		
		}catch(Exception e)
		{			
			Log.d(TAG, "caught exception " + e.getLocalizedMessage());		
		}		
		Log.d(TAG, "isBnoProduct returns " + isBno + " productType " + productType);		
		return isBno;	
	}
	
	public boolean acquireHTVDTSemaphore() {
		
		if(mSemForHTVDT != null){
			mSemForHTVDT.acquireUninterruptibly();
			return true;
		}
		
		return false;
	}
	
	public boolean releaseHTVDTSemaphore() {
		
		if(mSemForHTVDT != null){
			mSemForHTVDT.release();
			return true;
		}
		
		return false;
	}
	
	public void notifyNewHTVDTRequestArrival(){
		
		Log.d(TAG, "notifyNewHTVDTRequestArrival() is called.");
    
    	ntf.notifyAllObservers(EventIDs.EVENT_NEW_HTV_DT_REQUEST_ARRIVAL, "");	    	
    }
	
	public int GetLastAnalogPresetNumber(){
		
		int fiPreset = euInst.GetLastAnalogPresetNumber();
		
		return (fiPreset>=0?fiPreset:0);
	}
	
	public boolean getIsAnyRequestforHTVChNameUpdate(){
		
		boolean fbResult;
		
		synchronized(mviHtvChNameUpdateList) {
			fbResult = !mviHtvChNameUpdateList.isEmpty();
		}
		
		return fbResult;
	}
	
	public boolean getIsHTVChNeedForNameUpdate(Long alChID){
		
		boolean fbResult;
		
		synchronized(mviHtvChNameUpdateList) {
			fbResult = mviHtvChNameUpdateList.contains(alChID);
		}
		
		return fbResult;
	}
	
	public void removeHTVChNameUpdateRequest(Long alChID){
		synchronized(mviHtvChNameUpdateList) {
			mviHtvChNameUpdateList.remove(alChID);
		}
	}
	
	public void addHTVChNameUpdateRequest(Long alChID){
		synchronized(mviHtvChNameUpdateList) {
			
			if(!mviHtvChNameUpdateList.contains(alChID))			
				mviHtvChNameUpdateList.add(alChID);
		}
	}
	
	public void clearHTVChNameUpdateWaitList() {
		synchronized(mviHtvChNameUpdateList) {			
			mviHtvChNameUpdateList.clear();
		}
	}
    /*161031GaryYe cable operator[TF415PHIEUMTK01-184] Ensure all the Wizards settings are cloned*/
	/**
	 * HTV clone feature needs access settings of cable operator in MW and UI display
	 */
	public int getHTVOperatorToMW(int operatorIdMW) {
	    int def = -1;
        boolean isHtvOperatorID = ctx.getSharedPreferences("CableOperatorHTV",Context.MODE_MULTI_PROCESS).getBoolean("isHtvID",true);
        int operatorIdHTV = SystemProperties.getInt("persist.htv.CableOperator",def);
        
        if(isHtvOperatorID && (operatorIdHTV != def) && (Thread.currentThread().getStackTrace()[4].getMethodName().equals("setfocusOnTheRadioList"))){   
           
           ctx.getSharedPreferences("CableOperatorHTV",Context.MODE_MULTI_PROCESS).edit().putBoolean("isHtvID",false).commit();
           return operatorIdHTV;
       }
        return operatorIdMW;
	}
	
	public void initInstallSettings() {
		
		boolean fbIsPbsMode = PlayTvUtils.isPbsMode();
		
		setPbsMode(fbIsPbsMode?1:0);
		
		if(fbIsPbsMode) {
			int RfSetting = 0;
			if(0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_C_C2, 0, 0)) {
				RfSetting |= 0x01;
			}
			if(0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_T_T2, 0, 0)) {
				RfSetting |= 0x02;
			}
			if(0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_ANALOG, 0, 0)) {
				RfSetting |= 0x04;
			}
			setRfSetting(RfSetting);
		}		
	}


	/* YanFu 2017/09/25 fix [GZ-CET][V5.249.5.075] Can't change channels by ch+/ch- and key numbers, can only select witch channel list */
	/*
	*   Update PlayTv Channel Database, Then TV can Zap New Install Channel.
	*/

	public void notifyPlayTvUpdateChannelDB() {
		Log.d(TAG, "notifyPlayTvUpdateChannelDB() is called.");
		Intent intent = new Intent(SOURCE_SELECT_CHANGE);
		ctx.sendBroadcast(intent);
	}
}
