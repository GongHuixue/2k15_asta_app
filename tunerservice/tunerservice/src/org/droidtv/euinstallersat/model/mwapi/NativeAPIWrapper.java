package org.droidtv.euinstallersat.model.mwapi;

import java.util.Observable;

import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_MEDIUM;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallersat.model.notification.INotificationListener;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.notification.CamOpProfDialogActivity;
import org.droidtv.euinstallersat.notification.CamOpProfInstallActivity;
import org.droidtv.euinstallersat.service.SatInstallerService;
import org.droidtv.euinstallersat.settings.SatelliteSettingsActivity;
import org.droidtv.euinstallersat.util.BouquetIdMapping;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.tv.media.ITvMediaPlayerContext;
import org.droidtv.tv.media.ITvServerConfig;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.InstallationCountryConstants;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.provider.IFrequencyListContract;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.tvclock.ITvClockManager;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;

import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.database.ContentObserver;
import android.database.Cursor;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.media.tv.TvTrackInfo;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.util.SparseBooleanArray;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;


public final class NativeAPIWrapper implements INotificationListener
{

	public static final String TAG = NativeAPIWrapper.class.getName();
	
	/*********************************************/
    private static boolean STUB_MODE = false;
    /*********************************************/
	
	protected Context ctx;
	private Context wizardActivityCtx = null;
	private Context settingsActivityCtx = null;
	private Context serviceCtx = null;
	private static volatile NativeAPIWrapper mNativeAPIWrapper = null;
	
	// native api instance holder
	private SatInstaller satInst = new SatInstaller(SatInstaller.TunerID.TUNER1);
	private SatInstaller satInst2 = new SatInstaller(SatInstaller.TunerID.TUNER2);
	
	private Boolean isTuner2Active = false;
	private boolean m_isCamUpdateMode = false;
	private ITvSettingsManager m_settings =ITvSettingsManager.Instance.getInterface();
	private int userSelectedPkg = MwDataTypes.PKG_ID_GENERIC;
	private int mLNBSelectedForManualIns = 0;
	private int m_currentLNBIdx = 0;
	private int m_oredLNBValue = 0x00; //used for add satellite
	
	private EuinstallerSatSurface m_surface;
	
	public static final int STATE_SETTINGS = 0;
	public static final int STATE_WIZARD = 1;
	public static final int STATE_SERVICE = 2;
	public static final int STATE_IDLE = 3;
	public static final int STATE_BACKGROUND_UPDATE = 4;
	
	private int m_applicationState = STATE_IDLE;
	
	public static final int INSTALL_MODE_NONE = 0;
	public static final int INSTALL_MODE_AUTO = 1;
	public static final int INSTALL_MODE_UPDATE = 2;
	public static final int INSTALL_MODE_DTR = 3;

    public static final int TVPROVIDER_SATELLITE_MEDIUM_BASE = 2;
    public static final int MAX_LNB_NUMBER = 4;
       
	private TvMediaPlayer tvMpl = null;
	private ITvMediaPlayerContext iTvMplCtx = null; 
	private ITvServerConfig iTvSrvConfig = null;
	
	private int m_installMode = INSTALL_MODE_NONE;
	private  int mCachedDualTunerSetting = 0;
	public static boolean isInNoninterruptablemode = false;
	
	private boolean ifSatIPMwAPI = true;
	private boolean ifCurrentlyInNonInterruptibe = false;
	
	private PowerStates currentPowerState;
	private PowerStates fromPowerStates;
	private PowerStates toPowerStates;
	private String POWER_CHANGE_DETECTED = "POWER_CHANGE_DETECTED";
	private String FACTORY_RESET_DETECTED = "FACTORY_RESET_DETECTED";
	private String DEFAULT_POWER_ON_CASE = "DEFAULT_POWER_ON_CASE";
	private String EXIT_INSTALLATION = "EXIT_INSTALLATION";
	private boolean IsMajorVersionChange = false;
	private BackgroundInstallation backInstallInst = null;
	private SemistandbyUpdate	ssbyInstallInst = null;
	private SharedPreferences mCamOp = null;
	private Editor editor = null;
	private boolean m_SemistandbyUpdateInstalTriggered = false;
	private LooperThread looperThread;
	public static final String PACKAGE_NAME_TUNERSERVICE="org.droidtv.tunerservice";
	public enum TunerName{
		TUNER1,
		TUNER2
	}
	
	private SelectedMode userSelectedMode = SelectedMode.ADVANCED;
	
	public enum SelectedMode{
		FROM_THE_CAM,
		ADVANCED
	}	

	public static final int INSTALL_TYPE_AUTO = 0;
	public static final int INSTALL_TYPE_UPDATE = 1;
	public static final int INSTALL_TYPE_BACKGROUND = 2;
	public static final int INSTALL_TYPE_SRT = 3;
	
	private boolean isOPRegistered = false;
	private boolean CamNitUpdateInstallPerformed = false;
	private boolean CamNitUpdateInstallTriggered = false;	
	public static final int DATA_ALL_TABLE = 0;
	public static final int DATA_TS_TABLE = 1;
	
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;

	// notification instance handler holder
	protected NotificationHandler ntf = NotificationHandler.getInstance();
	private TvProviderListener mObserver;
    private Handler mHandler= new Handler();
    private final int SERVICE_TYPE_HEVC = 0x1F;
    public enum CONNECTION_TYPE{
    	SINGLE_LNB,
    	DISEQC_1_0,
    	DISEQC_MINI,
    	UNICABLE_LNB,
    	UNICABLE_SWITCH,
    	SAT_IP
    }

    private Boolean [] ifPrescanLNB = new Boolean[]{true,true,true,true};
    private SharedPreferences mStoredSharedPreferences = null;
    private Editor edit = null;
    
	protected NativeAPIWrapper()
	{
		looperThread = new LooperThread(); //Every slot will have one looper thread
		looperThread.start();
		ntf.registerForNotification(this);

		
		synchronized(looperThread) {
				while(!looperThread.getLooperThreadHandlerStatus()) {
					try {
						//Log.d(TAG,"Runnable waiting..");
						looperThread.wait();
						//Log.d(TAG,"Runnable wait finish");
					} catch (InterruptedException e) {
						//e.printStackTrace();
					}
				}
			}
	}

	public void setMMIEnabled(boolean status){
		/*if(status == true){
			satInst.setMmiEnable();
		} else {
			satInst.setMmiDisable();
		}*/
	}
	
	
	public synchronized static NativeAPIWrapper getInstance() {
		//Log.d(TAG, "mNativeAPIWrapper " + mNativeAPIWrapper);
		if (mNativeAPIWrapper == null) {
		
				mNativeAPIWrapper = new NativeAPIWrapper();
			
		}
		//Log.d(TAG, "mNativeAPIWrapper return " + mNativeAPIWrapper);
		return mNativeAPIWrapper;
	}

	public SatInstaller getSatInstaller(final TunerName argTunerName){
		SatInstaller returnInst = null;
		if (argTunerName == TunerName.TUNER1) {
			returnInst = satInst;
		} else if (argTunerName == TunerName.TUNER2) {
			returnInst = satInst2;
		}
		return returnInst;
	}
		
	public void setApplicationContext(Context appContext) {
		//Log.d(TAG, "setApplicationContext appContext:" + appContext);
		ctx = appContext;
		satInst.initMainActivityInstance(appContext);
		satInst2.initMainActivityInstance(appContext);
		
		mStoredSharedPreferences = ctx.getApplicationContext().getSharedPreferences("euinstallersat", Context.MODE_PRIVATE);
		edit = mStoredSharedPreferences.edit();
		
		mCamOp = ctx.getApplicationContext().getSharedPreferences("mCamOp", Context.MODE_PRIVATE);
		editor  = mCamOp.edit();		
		if(appContext instanceof SatelliteInstallationActivity){
			wizardActivityCtx = appContext;
		}else if(appContext instanceof SatelliteSettingsActivity){
			settingsActivityCtx = appContext;
		}else if(appContext instanceof SatInstallerService){
			serviceCtx = appContext;
		}
	}
	
	public Context getSettingsActivity(){
		Log.d(TAG, "getSettingsActivity() " + settingsActivityCtx);
		return settingsActivityCtx;
	}
	
	public Context getApplicationServiceContext(){
		Log.d(TAG, "getApplicationServiceContext() " + serviceCtx);
		return serviceCtx;
	}

	public void setopcache()
	{	
		boolean iscached = false;
		Log.d(TAG, "setopchace");
		iscached = false;
		editor.putBoolean("iscached", iscached);
		editor.commit();
	}
	public void setTunerToIdleMode(TunerName argTunerName, boolean ifIdleMode){
		Log.d(TAG,"setTunerToIdleMode "+ argTunerName + " " + ifIdleMode);
		if(argTunerName == TunerName.TUNER1){
			satInst.setTunerModeToIdle(ifIdleMode);
		}else if(argTunerName == TunerName.TUNER2){
			satInst2.setTunerModeToIdle(ifIdleMode);
		}
	}
	
	public void setApplicationState(int p_state)
	{
		//Log.d(TAG,"setApplicationState"+ p_state);
		m_applicationState = p_state;
	}
	
	public int getApplicationState()
	{
		//Log.d(TAG,"getApplicationState"+ m_applicationState);
		return m_applicationState;
	}
	
	public void exitOnInstallationComplete(){
		Log.d(TAG, "onInstallationComplete m_installMode:" + m_installMode);
		
		if (satInst.ifValidSession()) {
			satInst.StopInstallation();
			satInst.ExitSatInstaller();
			setMMIEnabled(false); //Disable the mmi
			satInst2.ExitSatInstaller();

			muteAudio(false);
			
			// enable back camUI when installer is exiting
			satInst.registerCIListener();
			if(isTwoTunerSupported()){
				satInst2.registerCIListener();
			}
		}
		
		SetHostControlStatus(TunerName.TUNER1, true);
		SetHostControlStatus(TunerName.TUNER2, true);
		
		//set Tuner2 to active mode
		setTunerToIdleMode(TunerName.TUNER2, false);
		
		exitNonInteruptableMode();
		
		closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
		if(isTwoTunerSupported()){
			closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_AUX);
		}
		
		// reset all variables
		mCachedDualTunerSetting = m_settings.getInt(TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, 0 );
		isTuner2Active = false;
		m_applicationState = STATE_IDLE;
		
		// clear notification handler and add nativeapiwrapper
		ntf.removeAllObservers();
		ntf.addObserver(NativeAPIWrapper.getInstance());
		
		m_settings.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 1);
		m_settings.putInt(TvSettingsConstants.CHANNELFILTER, 0, TvSettingsDefinitions.ChannelFilterConstants.ALL);
		m_settings.putInt(TvSettingsConstants.CHANNELFILTERSATELLITE, 0, TvSettingsDefinitions.ChannelFilterConstants.ALL);
		m_settings.putInt(TvSettingsConstants.SATELLITECHANNELSUBLIST, 0, 0);
		
		if(m_installMode != INSTALL_MODE_NONE)
		{
			// dont sent the intent again for DTR intents will be taken care inside DTR screen
			sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_COMPLETE");
		}
		setInstallMode(INSTALL_MODE_NONE);
				
		if (!isVirginInstallMode()) {
			switchToFirstAvailableChannel(true);
		} else {
			Log.d(TAG, "Virgin installation, not tuning");
			InstallerActivityManager.getInstance().finishActivityStack();
		}
		Log.d(TAG,"onInstallationComplete exit");
	}
	
	public void exitWithoutInstallation(){
		Log.d(TAG, "exitWithoutInstallation");
		
		if (satInst.ifValidSession()) {
			satInst.StopInstallation();
			satInst.ExitSatInstaller();
			setMMIEnabled(false); //Disable the mmi
			satInst2.ExitSatInstaller();
			
			// enable back camUI when installer is exiting
			satInst.registerCIListener();
			if(isTwoTunerSupported()){
				satInst2.registerCIListener();
			}
			
			muteAudio(false);
		}
		
		SetHostControlStatus(TunerName.TUNER1, true);
		SetHostControlStatus(TunerName.TUNER2, true);
		
		//set Tuner2 to active mode
		setTunerToIdleMode(TunerName.TUNER2, false);
		
		exitNonInteruptableMode();
		
		closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
		if(isTwoTunerSupported()){
			closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_AUX);
		}
		
		// reset all variables
		mCachedDualTunerSetting = m_settings.getInt(TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, 0 );
		isTuner2Active = false;
		m_applicationState = STATE_IDLE;
		
		// clear notification handler and add nativeapiwrapper
		ntf.removeAllObservers();
		ntf.addObserver(NativeAPIWrapper.getInstance());
	}

	public Context getCurrentContext(){
		Log.d(TAG, "getCurrentContext " + ctx);
		return ctx;
	}
	
	 public void showTVNofification(final Context context, final String notifMessage ){
			Log.d(TAG,"showTVNofification  context: " + context + ", notifMessage: " + notifMessage);
		messenger = TvToastMessenger.getInstance(context);
		mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
		mTimeOutTvToast.setMessage(notifMessage);
		messenger.showTvToastMessage(mTimeOutTvToast);
	}

	/*
	 * Set number satellites to install
	 * 
	 * @Param int number of satellites to install
	 */
	public void setSatInstallationCount(int satInstallationCount)
	{
	}
	
	public void setDefaultSettingsToMW()
	{
		int symbolrate = 0;
		Log.d(TAG,"setDefaultSettingsToMW entry");
	
		
		if (GetPolarisationFromTVDB() == MwDataTypes.PolarisationVertical) {
			SetPolarisation(true);
		} else {
			SetPolarisation(false);
		}
		
		SetManualInstallLNB(satInst.GetCurrentLNB());
		symbolrate = GetSymbolRateFromParams();
		SetSymbolRate(symbolrate);

		if(isTwoTunerSupported() == false){
			// dual tuner is disabled in option code, set the nvm to single tuner
			setDualTunerToTVS(false);
		}

		
		Log.d(TAG,"setDefaultSettingsToMW exit");
	}

	

	public boolean isAutoChUpdateAvailable()
	{
		Log.d(TAG,"isAutoChUpdateAvailable entry");
		boolean l_ret = true;
	//	l_ret = !satInst.GetUserPackageIndex().IsPackage;
		l_ret = satInst.GetUserPackageIndex();
		l_ret = !l_ret;
		Log.d(TAG,"isAutoChUpdateAvailable returning" + l_ret);
		return l_ret;
	}

	public int GetAutoChanUpdate()
	{
		Log.d(TAG,"GetAutoChanUpdate entry");
		int l_isStandbyUpdate = m_settings.getInt(
				TvSettingsConstants.INSTSETTINGSSTANDBYCHANNELUPDATE, 0, 0);
		Log.d(TAG,"l_isStandbyUpdate = " + l_isStandbyUpdate);
		return l_isStandbyUpdate;
	}

	public void SetAutoChanUpdate(boolean p_isAutoUpdateOn)
	{
		Log.d(TAG, "SetAutoChanUpdate entry " + p_isAutoUpdateOn);
		if (p_isAutoUpdateOn) {
			m_settings.putInt(
					TvSettingsConstants.INSTSETTINGSSTANDBYCHANNELUPDATE, 0, 1);
		} else {
			m_settings.putInt(
					TvSettingsConstants.INSTSETTINGSSTANDBYCHANNELUPDATE, 0, 0);
		}
		Log.d(TAG, "SetAutoChanUpdate exit");
	}

	public boolean isAutoChanUpdateControllable()
	{
		Log.d(TAG, "isAutoChanUpdateControllable entry");
		boolean l_ret = isAnyLNBInstalled();
		Log.d(TAG, "isAutoChanUpdateControllable exit");
		return l_ret;
	}
	
	private boolean isAnyLNBInstalled()
	{
		Log.d(TAG, "isAnyLNBInstalled entry");
		boolean l_ret = false;
		int l_idx;
		int l_numInstalledLNB = 0;
		int l_maxLNBCount = getLNBCount();
		for(l_idx = 0; l_idx < l_maxLNBCount; l_idx ++)
		{
			if(IsLNBInstalled(l_idx))
			{
				l_numInstalledLNB++;
			}
			
		}
		if(l_numInstalledLNB>0)
		{
			l_ret = true;
		}
		Log.d(TAG, "isAnyLNBInstalled returning " + l_ret);
		return l_ret;
	}

	public boolean isAutoUpListAvailable()
	{
		Log.d(TAG, "isAutoUpListAvailable entry");
		boolean l_ret = true;
		//l_ret = !satInst.GetUserPackageIndex().IsPackage;
		l_ret = satInst.GetUserPackageIndex();
		l_ret = !l_ret;
		
		if(ifSatIPConnectionType()){
			l_ret = false;
		}
		Log.d(TAG, "isAutoUpListAvailable exit");
		return l_ret;
	}

	public boolean isAutoUpListControllable()
	{
		Log.d(TAG, "isAutoUpListControllable entry");
		boolean l_ret = false;
		int l_isStandbyUpdate = m_settings.getInt(
				TvSettingsConstants.INSTSETTINGSSTANDBYCHANNELUPDATE, 0, 0);
		Log.d(TAG,"l_isStandbyUpdate = " + l_isStandbyUpdate);
		if((l_isStandbyUpdate != 0) && isAnyLNBInstalled())
		{
			l_ret = true;
		}
		Log.d(TAG, "isAutoUpListControllable exit");
		return l_ret;
	}


	public void SetInsAutUpOptionList(int selectedLnbIdx,boolean ifChecked)
	{
		Log.d(TAG, "SetInsAutUpOptionList lnb " + selectedLnbIdx + ",ifChecked " + ifChecked );
		boolean isUpdateEnabled = satInst.GetUpdateInstallEnabled(selectedLnbIdx);
		Log.d(TAG, "SetInsAutUpOptionList Before: " + isUpdateEnabled);
		satInst.SelectLNBForUpdate(selectedLnbIdx, ifChecked);
		isUpdateEnabled = satInst.GetUpdateInstallEnabled(selectedLnbIdx);
		Log.d(TAG, "SetInsAutUpOptionList After: " + isUpdateEnabled);
	}

	public void SetManualInstMenu()
	{
		Log.d(TAG, "SetManualInstMenu entry");
		satInst.LoadManualInstallationDefaultValues();
		Log.d(TAG, "SetManualInstMenu exit");
	}

	public int GetManualInstallLNB()
	{
		Log.d(TAG, "GetManualInstallLNB entry");
		int l_ret = 0;
		if(isTuner2Active()){
			l_ret = satInst2.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallLnb);
		}else{
			l_ret = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallLnb);
		}
		Log.d(TAG, "GetManualInstallLNB exit");
		return l_ret;
	}

	public void SetManualInstallLNB(int p_selectedLnb)
	{
		Log.d(TAG, "SetManualInstallLNB entry " + p_selectedLnb);
		mLNBSelectedForManualIns = p_selectedLnb;
		if(isTuner2Active()){
			satInst2.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual,MwDataTypes.IHsvSatelliteInstallation_ManualInstallLnb, mLNBSelectedForManualIns);
		}else{
			satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual,MwDataTypes.IHsvSatelliteInstallation_ManualInstallLnb, mLNBSelectedForManualIns);
		}
		
		Log.d(TAG, "SetManualInstallLNB exit");
	}

	public boolean isPolarisationAvailable()
	{
		Log.d(TAG, "isPolarisationAvailable entry");
		boolean l_ret = true;
		Log.d(TAG, "isPolarisationAvailable exit");
		return l_ret;
	}

	public int GetPolarisationFromParams()
	{
		Log.d(TAG, "GetPolarisationFromParams entry");
		int l_retIdx = 0;
		if(isTuner2Active()){
			l_retIdx = satInst2.GetPolarization();
		}else{
			l_retIdx = satInst.GetPolarization();
		}
		Log.d(TAG, "GetPolarisationFromParams returning" + l_retIdx);
		return l_retIdx;
	}
	
	public int GetPolarisation()
	{
		Log.d(TAG, "GetPolarisation entry");
		int l_retIdx = 0;

		if(isTuner2Active())
		{
			l_retIdx = satInst2.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallPolaraization);
		}
		else
		{
			l_retIdx = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallPolaraization);
		}
		Log.d(TAG, "GetPolarisation returning" + l_retIdx);
		return l_retIdx;
	}
	
	public int GetPolarisationFromTVDB()
	{
		int l_retPol = 1;

		Log.d(TAG,"GetPolarisationFromTVDB entry");
		int m_lastSelectedPreset = 0;			
		
	
		m_lastSelectedPreset = m_settings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2, 0, 0);
		Log.d(TAG,"m_lastSelectedPreset = " + m_lastSelectedPreset);
		int  SATELLITE_MEDIUM_BASE = 2;
		
		String[] mProjection = new String[] {TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA };			
		String	mselection=TvContract.Channels._ID+" = ?"+" AND "+Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?";
		String[]	mselectionargs=new String[]{Integer.toString(m_lastSelectedPreset),String.valueOf(SATELLITE_MEDIUM_BASE+0),String.valueOf(SATELLITE_MEDIUM_BASE+1),String.valueOf(SATELLITE_MEDIUM_BASE+2),String.valueOf(SATELLITE_MEDIUM_BASE+3)};
			
		Cursor cursor   = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI,mProjection,mselection,mselectionargs, null);
		if(cursor != null) {
			try
			{
			
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
						l_retPol = keyvals.getInt(ITvContractExtras.C_POLARIZATION);
					}
				}
			 }
			}
			finally{
			  cursor.close();
			  cursor=null;
			}
		}
		Log.d(TAG, "GetPolarisationFromTVDB returning"  + l_retPol);
		
		return l_retPol;
	}

	public void SetPolarisation(boolean p_isVertical)
	{
		Log.d(TAG, "SetPolarisation entry");
		if(p_isVertical)
		{
			if(isTuner2Active()){
				satInst2.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallPolaraization,MwDataTypes.PolarisationVertical);
			}else{
				satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallPolaraization,MwDataTypes.PolarisationVertical);
			}
			
		}
		else
		{
			if(isTuner2Active()){
				satInst2.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallPolaraization, MwDataTypes.PolarisationHorizontal);
			}else{
				satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallPolaraization, MwDataTypes.PolarisationHorizontal);
			}
		}
		Log.d(TAG, "SetPolarisation exit");
	}

	public int GetSymRateMode()
	{
		Log.d(TAG, "GetSymRateMode entry");
		int l_ret = 0;
		if(isTuner2Active()){
			l_ret = satInst2.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRateMode);
		}else{
			l_ret = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRateMode);
		}
		Log.d(TAG, "GetSymRateMode exit " + l_ret);
		return l_ret;
	}

	public void SetSymRateMode(boolean p_isAutomatic)
	{
		Log.d(TAG, "SetSymRateMode entry " + p_isAutomatic);
		if(p_isAutomatic) {
			if(isTuner2Active()){
				satInst2.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual,MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRateMode,MwDataTypes.SymbolRateModeAuto);
			}else{
				satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual,MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRateMode,MwDataTypes.SymbolRateModeAuto);
			}
		} else {
			if(isTuner2Active()){
				satInst2.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual,MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRateMode,MwDataTypes.SymbolRateModeManual);
			}else{
				satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual,MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRateMode,MwDataTypes.SymbolRateModeManual);
			}
		}
		Log.d(TAG, "SetSymRateMode exit");
	}

	public boolean isSymbolRateControllable()
	{
		Log.d(TAG, "isSymbolRateControllable entry");
		boolean l_ret = true;
		int l_symbolRateMode = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRateMode);
		Log.d(TAG, "isSymbolRateControllable SymbolRateMode" + l_symbolRateMode);
		if(l_symbolRateMode == MwDataTypes.SymbolRateModeAuto)
		{
			l_ret = false;
		}
		
		Log.d(TAG, "isSymbolRateControllable exit" + l_ret);
		return l_ret;
	}
	
	public boolean isCDHomingSymbolRateControllable()
	{
		Log.d(TAG, "isCDHomingSymbolRateControllable entry");
		boolean l_ret = true;
		int l_symbolRateMode = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan, MwDataTypes.IHsvSatelliteInstallation_AttributeSymbolRateMode);
		Log.d(TAG, "isCDHomingSymbolRateControllable SymbolRateMode" + l_symbolRateMode);
		if(l_symbolRateMode == MwDataTypes.SymbolRateModeAuto)
		{
			l_ret = false;
		}
		
		Log.d(TAG, "isCDHomingSymbolRateControllable exit" + l_ret);
		return l_ret;
	}
	
	public boolean isReorderControllable()
	{
		Log.d(TAG, "isReorderControllable entry");
		boolean l_ret = false;
		if(getNoOfInstalledChannels() > 0)
		{
			l_ret = true;
		}
		Log.d(TAG, "isReorderControllable exit");
		return l_ret;
	}
	
	
	public int getNoOfInstalledChannels()
	{
		int presetCount = 0;
		try {
			String[] projection = new String[] { Channels._ID };
			String mselection = Channels.COLUMN_TYPE + "= ?" + " OR " + Channels.COLUMN_TYPE + "=?";
			String[] mselectionargs = new String[] { Channels.TYPE_DVB_S, Channels.TYPE_DVB_S2};

			Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

			if (cursor != null) {
				presetCount = cursor.getCount();
				cursor.close();
				cursor=null;
			} else {
				Log.d(TAG, "getNoOfInstalledChannels: cursor NULL");
			}

		} catch (Exception e) {
			Log.e(TAG, "Error TVProvider  " + e);
		}

		Log.d(TAG, "getNoOfInstalledChannels() " + presetCount);
		return presetCount;
	}

	public int GetSymbolRate()
	{
		Log.d(TAG, "GetSymbolRate entry");
		int l_ret = 0;
		if(isTuner2Active()){
			l_ret = satInst2.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual,MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRate);
		}else{
			l_ret = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual,MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRate);
		}
		Log.d(TAG, "GetSymbolRate l_ret" + l_ret);
		l_ret /= 1000;
		Log.d(TAG, "GetSymbolRate exit");
		return l_ret;
	}

	public int GetSymbolRateFromParams()
	{
		Log.d(TAG, "GetSymbolRate entry");
		int l_ret = 0;
		if(isTuner2Active()){
			l_ret = satInst2.GetSymbolRate();
			Log.d(TAG, "GetSymbolRate returning"	+ l_ret);
		}else{	
			l_ret = satInst.GetSymbolRate();
		}
		l_ret /= 1000; 
		Log.d(TAG, "GetSymbolRate returning"	+ String.valueOf(l_ret));
		return l_ret;
	}
	
	public int GetSymRateModeForCDHomingTransponder()
	{
		Log.d(TAG, "GetSymRateModeForCDHomingTransponder entry");
		int l_ret = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan, MwDataTypes.IHsvSatelliteInstallation_AttributeSymbolRateMode);
		Log.d(TAG, "GetSymRateModeForCDHomingTransponder exit");
		return l_ret;
	}
	
	public int GetPolarisationForCDHomingTransponder()
	{
		Log.d(TAG, "GetPolarisationForCDHomingTransponder entry");
		int l_retIdx = 0;
		l_retIdx = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan, MwDataTypes.IHsvSatelliteInstallation_AttributePolarisation);
		Log.d(TAG, "GetPolarisationForCDHomingTransponder returning" + l_retIdx);
		return l_retIdx;
	}
	
	public void SetSymbolRateForCDHomingTransponder(int p_symbolRate)
	{
		Log.d(TAG, "SetSymbolRateForCDHomingTransponder entry");
		satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan,MwDataTypes.IHsvSatelliteInstallation_AttributeSymbolRate, p_symbolRate * 1000);
		Log.d(TAG, "SetSymbolRateForCDHomingTransponder exit");
	}
	
	public int GetFreqForCDHomingTransponder()
	{
		Log.d(TAG, "GetFreqForCDHomingTransponder entry");
		int l_ret = 0;
		l_ret = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan, MwDataTypes.IHsvSatelliteInstallation_AttributeFrequency);
		Log.d(TAG, "GetFreqForCDHomingTransponder returning"  + String.valueOf(l_ret));
		l_ret/=1000;
		return l_ret;
	}
	
	public void SetSymRateModeForCDHomingTransponder(boolean p_isAutomatic)
	{
		Log.d(TAG, "SetSymRateModeForCDHomingTransponder entry");
		if(p_isAutomatic) {
			satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan,MwDataTypes.IHsvSatelliteInstallation_AttributeSymbolRateMode,MwDataTypes.SymbolRateModeAuto);
		} else {
			satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan,MwDataTypes.IHsvSatelliteInstallation_AttributeSymbolRateMode,MwDataTypes.SymbolRateModeManual);
		}
		Log.d(TAG, "SetSymRateModeForCDHomingTransponder exit");
	}
	
	public int GetSymbolRateForCDHomingTransponder()
	{
		Log.d(TAG, "GetSymbolRateForCDHomingTransponder entry");
		int l_ret = 0;
		l_ret = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan,MwDataTypes.IHsvSatelliteInstallation_AttributeSymbolRate);
		Log.d(TAG, "GetSymbolRate l_ret" + l_ret);
		l_ret /= 1000;
		Log.d(TAG, "GetSymbolRateForCDHomingTransponder exit");
		return l_ret;
	}
	
	public void SetPolarisationForCDHomingTransponder(boolean p_isVertical)
	{
		Log.d(TAG, "SetPolarisationForCDHomingTransponder entry");
		if(p_isVertical)
		{
			satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan, MwDataTypes.IHsvSatelliteInstallation_AttributePolarisation,MwDataTypes.PolarisationVertical);
		}
		else
		{
			satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan, MwDataTypes.IHsvSatelliteInstallation_AttributePolarisation, MwDataTypes.PolarisationHorizontal);
		}
		Log.d(TAG, "SetPolarisationForCDHomingTransponder exit");
	}


	public void SetSymbolRate(int p_symbolRate) {
		Log.d(TAG, "SetSymbolRate entry");
		int[] l_symbolRateRange_arr = satInst.getSymbolRateRange();
		int l_symbolRate = p_symbolRate * 1000;
		if (l_symbolRate != 0) {
			if (l_symbolRate < l_symbolRateRange_arr[0]) {
				l_symbolRate = l_symbolRateRange_arr[0];
			} else if (l_symbolRate > l_symbolRateRange_arr[1]) {
				l_symbolRate = l_symbolRateRange_arr[1];
			}
		}
		if (isTuner2Active()) {
			satInst2.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRate, l_symbolRate);
		} else {
			satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallSymRate, l_symbolRate);
		}
		Log.d(TAG, "SetSymbolRate exit");
	}

	public int GetFreq()
	{
		Log.d(TAG,"GetFreq entry");
		int m_lastSelectedPreset = 0;			
		int mFrequncy = 10700;
	
		m_lastSelectedPreset = m_settings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2, 0, 0);
		Log.d(TAG,"m_lastSelectedPreset = " + m_lastSelectedPreset);
		int  SATELLITE_MEDIUM_BASE = 2;
		
		String[] mProjection = new String[] {TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA };			
		String	mselection=TvContract.Channels._ID+" = ?"; 
		String[]	mselectionargs=new String[]{Integer.toString(m_lastSelectedPreset)};
		
			
		Cursor cursor   = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI,mProjection,mselection,mselectionargs, null);
		if(cursor != null)
		{
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
			}
			finally
			{
			   cursor.close();
			   cursor=null;
			}
		}
	
		

		/*
		if(isTuner2Active()){
			int freqArray[] = new int[1];
			satInst2.getFreq_SatInst(freqArray);
			l_ret = freqArray[0];
			Log.d(TAG, "GetFreq returning"  + l_ret);
			if(l_ret == 0) {
				l_ret = 10700;
			}

		}else{
			
			int freqArray[] = new int[1];
			satInst.getFreq_SatInst(freqArray);
			l_ret = freqArray[0];
			if(l_ret == 0) {
				l_ret = 10700;
			}
			//l_ret = satInst.GetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallFreq);
		}*/
		
		Log.d(TAG, "GetFreq returning"  + mFrequncy);
		
		return mFrequncy;
	}
	
	public void getFrequencyRange(int freqValue[])
	{
		Log.d(TAG,"getFrequency_Range entry");
		satInst.getFrequency_Range(freqValue);
		Log.d(TAG,"getFrequency_Range exit");
	}

	public void SetFreq(int p_freq)
	{
		Log.d(TAG, "SetFreq entry " + String.valueOf(p_freq));
		p_freq*=1000;
		if(isTuner2Active()){
			satInst2.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallFreq, p_freq);
		}else{
			satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, MwDataTypes.IHsvSatelliteInstallation_ManualInstallFreq, p_freq);
		}
		Log.d(TAG, "SetFreq exit");
	}
	
		public void SetFreqForCDHomingTransponder(int p_freq)
	{
		Log.d(TAG, "SetFreqForCDHomingTransponder entry " + String.valueOf(p_freq));
		p_freq*=1000;
		satInst.SetAttribute(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan, MwDataTypes.IHsvSatelliteInstallation_AttributeFrequency, p_freq);
		Log.d(TAG, "SetFreqForCDHomingTransponder exit");

	}
	
	public boolean isPackageFreesat()
	{
		Log.d(TAG, "isPackageFreesat entry");
		boolean l_ret = false;//TODO : check call
		Log.d(TAG, "isPackageFreesat exit");
		return l_ret;
	}
	

	public void resetInstallation()
	{
		Log.d(TAG, "resetInstallation entry");
		satInst.ResetInstallation();
		muteAudio(false);
		if(m_installMode != INSTALL_MODE_NONE)
		{
			sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_STOPPED");
			setInstallMode(INSTALL_MODE_NONE);
		}
		Log.d(TAG, "resetInstallation exit");
	}
	
	public int getConnectionType()
	{
		Log.d(TAG, "getConnectionType entry");
		int l_connectionType = satInst.GetLNBType();
		Log.d(TAG, "getConnectionType returning" + l_connectionType);
		return l_connectionType;
	}
	public int getLNBCount()
	{
		Log.d(TAG, "###getLNBCount entry");
		int l_count = 0;
		//LnbSettings lnbSettings = satInst.GetLnbSettings();
		int lnbType = LnbSettingsEntry.LnbConnectionSingle;
		if(isTuner2Active()){
			lnbType = satInst2.GetLNBType();
		}else{
			lnbType = satInst.GetLNBType();
		}
		
		Log.d(TAG, "getLNBCount returning" +  lnbType);
		switch(lnbType)
		{
		case LnbSettingsEntry.LnbConnectionSingle:
			l_count = 1;
			break;
		case LnbSettingsEntry.LnbConnectionDiSeqc1_0:
			l_count = 4;
			break;
		case LnbSettingsEntry.LnbConnectionDiSeqcMini:
			l_count = 2;
			break;
		case LnbSettingsEntry.LnbConnectionUnicableLnb:
			l_count = 1;
			break;
		case LnbSettingsEntry.LnbConnectionUnicableSwitch:
			l_count = 2;
			break;
		case LnbSettingsEntry.LnbConnectionSatIP:
			l_count = 4;
			break;
		}
		
		Log.d(TAG, "getLNBCount returning" + String.valueOf(l_count));
		return l_count;
	}
	
	public void SetHostControlStatus (final TunerName argTunerName,boolean OnOff) {
		if(argTunerName == TunerName.TUNER1){
			satInst.SetHostControlStatus(OnOff);
		}else{
			satInst2.SetHostControlStatus(OnOff);
		}
	}

	
	public void SetScanStarts(final int p_mode, final int p_lnbIdx)
	{
		Log.d(TAG, "SetScanStarts entry");
		Log.d(TAG,"thread id : " + android.os.Process.myTid());
		Thread l_scanThread = new Thread(new Runnable()
		 {
			    public void run()
			    {
			    	
			    	Log.d(TAG, "starting scan in new thread and mode:" + p_mode);
			    	Log.d(TAG,"thread id in new thread: " + android.os.Process.myTid());
			    //	satInst.bindChannelVersionManagerService();
			    	
			    	if( p_mode == (MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan | MwDataTypes.IHsvSatelliteInstallation_InstallationServiceScan))
					{
						setInstallMode(INSTALL_MODE_AUTO);
						SetHostControlStatus(TunerName.TUNER1, false);
						SetHostControlStatus(TunerName.TUNER2, false);
						
						if((getConnectionTypeFromMW() == CONNECTION_TYPE.DISEQC_1_0) || (getConnectionTypeFromMW() == CONNECTION_TYPE.DISEQC_MINI)){
				    		if(getPrescanForLNBs()[p_lnbIdx] == false){
				    			Log.d(TAG,"Skip LNB");
				    			satInst.StartInstallation(MwDataTypes.IHsvAppApiNoSource, p_lnbIdx, 3);
				    		}else{
				    			satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, 3 /*p_mode*/);
				    		}
						}else{
							// existing default case for single/Universal/Unicable LNb's
							satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, 3 /*p_mode*/);
						}
					}
					else if(p_mode == MwDataTypes.IHsvSatelliteInstallation_InstallationServiceScan)
					{
						setInstallMode(INSTALL_MODE_AUTO);
						IsMajorVersionChange = false;
						satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, p_mode);
					}
					else if(p_mode == MwDataTypes.IHsvSatelliteInstallation_InstallationManual)
					{
						setInstallMode(INSTALL_MODE_DTR);
						IsMajorVersionChange = false;
						if(isTuner2Active()){
							satInst2.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, p_mode);
						}else{
							satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, p_mode);
						}
					}
					else if(p_mode == MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan)
					{
						satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, p_mode);
					}
					else if(p_mode == MwDataTypes.IHsvSatelliteInstallation_InstallationMiniPrecan)
					{
						setInstallMode(INSTALL_MODE_UPDATE);
						satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, p_mode);
						
						sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
					}
					else if (p_mode == MwDataTypes.IHsvSatelliteInstallation_InstallationBackground)
					{
						IsMajorVersionChange = false;
						Log.d(TAG,"In Mode Installation Background"+ p_mode);
						satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, p_mode);
					}
					else if (p_mode == MwDataTypes.IHsvSatelliteInstallation_InstallationCamNit)
					{
						Log.d(TAG,"In Mode Installation Cam NIT"+ p_mode);
						satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, p_lnbIdx, p_mode);
						sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
					}
	
					else					
					{
						Log.d(TAG,"entered mode is not correct");
					}
			    }
			  });
		l_scanThread.setPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
		l_scanThread.start();
		
		Log.d(TAG, "SetScanStarts exit");
	}
	
	/* 
	 * @ param p_updateMode - 	distiguishes between normal update installation and 
	 * 							Fransat background update installation						
	 */
	public void SetUpdateInstallStart(final int p_updateMode)
	{
		Log.d(TAG, "SetUpdateInstallStart entry : mode - " + p_updateMode);
		if(m_installMode == INSTALL_MODE_NONE)
		{
			setInstallMode(INSTALL_MODE_UPDATE);
			sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
		}
		
		 new Thread(new Runnable()
		 {
		    public void run()
		    {
		    	Log.d(TAG, "starting update scan in new thread");
		    	//satInst.bindChannelVersionManagerService();
				IsMajorVersionChange = false;
		    	satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner,0, p_updateMode);
		    }
		  }).start();
	    Log.d(TAG, "SetUpdateInstallStart exit"); 
	}

	public void updateInstllation() {
		Log.d(TAG, "updateInstllation entry");
//		satInst.bindChannelVersionManagerService();
		if((getFromPowerState() == PowerStates.POWER_STATE_FULL_SYSTEM_START) && (getToPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY)){
			SetHostControlStatus(TunerName.TUNER1, false);
			SetHostControlStatus(TunerName.TUNER2, false);
			IsMajorVersionChange = false;
			satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner,0,MwDataTypes.IHsvSatelliteInstallation_InstallationSSbyUpdate);
		}
		else{
			SetHostControlStatus(TunerName.TUNER1, false);
			SetHostControlStatus(TunerName.TUNER2, false);
			IsMajorVersionChange = false;
			satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner,0,MwDataTypes.IHsvSatelliteInstallation_InstallationAutomaticUpdate);
		}
	    Log.d(TAG, "updateInstllation exit");
	}
	
	public void SetMajorVersion (boolean ValueToSet) {
		Log.d(TAG,"MajorUpdate Set" + ValueToSet);
		IsMajorVersionChange = ValueToSet;
	}
	
	public void UpdateLnbTypeOnSemistandbyUpdate() {
		/* For Semistandby update installation, if mini-prescan is done, then LNB Type can get changed. 
			Update of LNB Type is needed for this use case */
		int l_installState = satInst.GetCurrentInstallationMode();
		int l_packageId = satInst.GetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageId);
		int LnbType;
		int	LnbIndex;
		int mRowsUpdated = 0;

		Log.d (TAG,"CurrentInstallationState " + l_installState + "package id " + l_packageId);
		/* ANEESH: Extend this logic for Foreground update installation too */
		switch(l_packageId) {
			case	MwDataTypes.DIGITURK_TURKSAT_PACKAGE_ID:
			case	MwDataTypes.DIGITURK_EUTELSAT_PACKAGE_ID:
				Log.d (TAG, "Digiturk Turksat/EutelSat package for semistandby update ");
				commitSatelliteSettingsToGlobalSettings();
				break;
			default:
				Log.d(TAG,"LnbType Update not needed in semistandby ");
				break;
		}
	}	
	
	public boolean isSemiStandbyUpdateRequiredOnAlarmWakeup () {
		boolean semiSbyNeeded = true;
		int retVal = GetAutoChanUpdate();
		if(retVal == 0) {
			semiSbyNeeded = false;
		} else if(ifOperatorProfilePackage() == true) {
			semiSbyNeeded = false;
		}
		Log.d(TAG," semiSbyNeeded check " + semiSbyNeeded);
		return semiSbyNeeded;
	}
	public boolean isSemiStandbyUpdateRequiredOnShutdown () {
		boolean semiSbyNeeded = false;
		
		/* Check package id Fransat & BatTriggered update installation is ongoing */
		int l_installState = satInst.GetCurrentInstallationMode();
		int l_packageId = satInst.GetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageGroup);
		Log.d (TAG, "InstallState" +  l_installState + "PackageID %d " + l_packageId);
		if ((l_packageId == MwDataTypes.PKG_ID_FRANSAT) && (l_installState == MwDataTypes.IHsvSatelliteInstallation_InstallationBackgroundUpdate)) {
			semiSbyNeeded = true;
		}
		else if ((l_packageId == MwDataTypes.PKG_ID_TURK) && (GetIsMDUDetectedInAnyLnbPos() == true)) {
			semiSbyNeeded = true;
		}
		
		m_SemistandbyUpdateInstalTriggered = semiSbyNeeded;
		return semiSbyNeeded;
	}

	public boolean isSemiStandbyUpdateOnShutdown () {
		boolean retVal = false;
		int l_installState = satInst.GetCurrentInstallationMode();
		int l_packageId = satInst.GetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageGroup);
		
		if((getFromPowerState() == PowerStates.POWER_STATE_FULL_SYSTEM_START) && (getToPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY)){
			if ((l_packageId == MwDataTypes.PKG_ID_TURK) && (GetIsMDUDetectedInAnyLnbPos() == true)) {
				retVal = true;
			}
			
		}
		Log.d(TAG," isSemiStandbyUpdateOnShutdown retVal " + retVal);
		return retVal;
	}
	
	public void ResetSemistandbyFlag () {
		m_SemistandbyUpdateInstalTriggered = false;
	}
	
	public boolean GetSemistandbyFlag () {
		return m_SemistandbyUpdateInstalTriggered;
	}
	
	public int GetPreScanStatus(int p_lnbIdx)
	{
		Log.d(TAG, "GetPreScanStatus entry");
		int l_ret = satInst.GetScanProgressStatus(MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan);
		Log.d(TAG, "GetPreScanStatus returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	public void StartStopSigStrMeas(final boolean p_isStartCheck,
			final int p_lnbIdx) {
		Log.d(TAG, "StartStopSigStrMeas entry isStartCheck: " + p_isStartCheck + ", lnbIdx" + p_lnbIdx);
		new Thread(new Runnable() {
			public void run() {
				if (p_isStartCheck) {
					if (isTuner2Active()) {
						satInst2.StartSignalStrengthMeas(p_lnbIdx);
					} else {
						satInst.StartSignalStrengthMeas(p_lnbIdx);
					}

				} else {
					if (isTuner2Active()) {
						satInst2.StopSignalStrengthMeas(p_lnbIdx);
					} else {
						satInst.StopSignalStrengthMeas(p_lnbIdx);
					}
				}
			}
		}).start();

		Log.d(TAG, "StartStopSigStrMeas exit");
	}

	public int GetSignalStrength(int p_lnbIdx)
	{
		Log.d(TAG, "GetSignalStrength entry");
		//int l_sigStrength = satInst.GetSignalStrength(p_lnbIdx);
		
		int l_sigStrength = 0;
		if(isTuner2Active()){
			l_sigStrength = satInst2.getSigStrength_SatInst(p_lnbIdx,0);
		}else{
			l_sigStrength = satInst.getSigStrength_SatInst(p_lnbIdx,0);
		}
		Log.d(TAG, "GetSignalStrength returning" + String.valueOf(l_sigStrength));
		return l_sigStrength;
	}
	
	public int GetSignalQuality(int p_lnbIdx)
	{
		Log.d(TAG, "GetSignalQuality entry");
	//	int l_sigQuality = satInst.GetSignalQuality(p_lnbIdx);
		int l_sigQuality = 0;
		if(isTuner2Active()){
			l_sigQuality = satInst2.getSigQuality_SatInst(p_lnbIdx,0);
		}else{
			l_sigQuality = satInst.getSigQuality_SatInst(p_lnbIdx,0);
		}
		
		Log.d(TAG, "getSigQuality_SatInst" + String.valueOf(l_sigQuality));
		return l_sigQuality;
	}
	
	public boolean GetIsMDUDetected()
	{
		Log.d(TAG, "GetIsMDUDetected entry");
		boolean l_ret = false;
		
		int lnbType = satInst.GetLNBType();
		int satelliteId = 0, satStatus = 0;
		int lnbIndex = 0,  count = 0;
		boolean  mduOnly = false, nonMdu = false;		
		
		if (lnbType == LnbSettingsEntry.LnbConnectionSingle) {
			count = 1;
		}
		else if (lnbType == LnbSettingsEntry.LnbConnectionDiSeqcMini) {
			count = 2;
		}
		else if (lnbType == LnbSettingsEntry.LnbConnectionDiSeqc1_0) {
			count = 4;
		}
		
		for (lnbIndex = 0; lnbIndex < count; lnbIndex++) {
			satelliteId = satInst.GetSatId(lnbIndex);
			satStatus = satInst.getLnbStatus(lnbIndex);
		
			if ((satStatus == MwDataTypes.LnbInstalled) || (satStatus == MwDataTypes.LnbDuplicate)) {
				switch(satelliteId) {
					case MwDataTypes.EUTELSAT_W3A_7E_MDU4:
					case MwDataTypes.EUTELSAT_W3A_7A_MDU5:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU3:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU2:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU1:
						mduOnly = true;
						break;
					default:
						nonMdu = true;
						break;
				}
			}
		}
		
		if ((mduOnly == true) && (nonMdu == false)) {
			l_ret = true;
			/* Set the package selection type to Quick */
			satInst.SetAttribute( MwDataTypes.IHsvSatelliteInstallation_InstallationServiceScan, 1, 1); // PackageOnly
			satInst.IdentifyPackagesAvailable();			
		}
		
		Log.d(TAG, "GetIsMDUDetected returning" + String.valueOf(l_ret));
		return l_ret;
	}

	public void IdentifyPackagesAvailable() {
		satInst.IdentifyPackagesAvailable();			
	}
	
	public boolean GetIsMDUDetectedInAnyLnbPos()
	{
		Log.d(TAG, "GetIsMDUDetectedInAnyLnbPos entry");
		boolean l_ret = false;
		
		int lnbType = satInst.GetLNBType();
		int satelliteId = 0, satStatus = 0;
		int lnbIndex = 0,  count = 0;;		
		
		if (lnbType == LnbSettingsEntry.LnbConnectionSingle) {
			count = 1;
		}
		else if (lnbType == LnbSettingsEntry.LnbConnectionDiSeqcMini) {
			count = 2;
		}
		else if (lnbType == LnbSettingsEntry.LnbConnectionDiSeqc1_0) {
			count = 4;
		}
		
		for (lnbIndex = 0; lnbIndex < count; lnbIndex++) {
			satelliteId = satInst.GetSatId(lnbIndex);
			satStatus = satInst.getLnbStatus(lnbIndex);
		
			if ((satStatus == MwDataTypes.LnbInstalled) || (satStatus == MwDataTypes.LnbDuplicate)) {
				switch(satelliteId) {
					case MwDataTypes.EUTELSAT_W3A_7E_MDU4:
					case MwDataTypes.EUTELSAT_W3A_7A_MDU5:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU3:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU2:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU1:
						l_ret = true;
						break;
					default:
						break;
				}
			}
		}
		
		Log.d(TAG, "GetIsMDUDetectedInAnyLnbPos returning" + String.valueOf(l_ret));
		return l_ret;
	}


	public int  GetMduSlotForMiniPrescan()
	{
		Log.d(TAG, "GetMduSlotForMiniPrescan entry");
		int LnbPos = 0;
		
		int lnbType = satInst.GetLNBType();
		int satelliteId = 0, satStatus = 0;
		int lnbIndex = 0,  count = 0;;		
		
		if (lnbType == LnbSettingsEntry.LnbConnectionSingle) {
			count = 1;
		}
		else if (lnbType == LnbSettingsEntry.LnbConnectionDiSeqcMini) {
			count = 2;
		}
		else if (lnbType == LnbSettingsEntry.LnbConnectionDiSeqc1_0) {
			count = 4;
		}
		
		for (lnbIndex = 0; lnbIndex < count; lnbIndex++) {
			satelliteId = satInst.GetSatId(lnbIndex);
			satStatus = satInst.getLnbStatus(lnbIndex);
		
			if ((satStatus == MwDataTypes.LnbInstalled) || (satStatus == MwDataTypes.LnbDuplicate)) {
				switch(satelliteId) {
					case MwDataTypes.EUTELSAT_W3A_7E_MDU4:
					case MwDataTypes.EUTELSAT_W3A_7A_MDU5:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU3:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU2:
					case MwDataTypes.EUTELSAT_W3A_7E_MDU1:
						LnbPos = lnbIndex;
						break;
					default:
						break;
				}
			}
		}
		
		Log.d(TAG, "GetMduSlotForMiniPrescan returning" + String.valueOf(LnbPos));
		return LnbPos;
	}

	
	public int GetSatDetectedID(int p_lnbIdx)
	{
		Log.d(TAG, "GetSatDetectedID entry");
		int l_id = 0; 
		//LnbSettingsEntry lnbSettings = satInst.GetLnbSettings(p_lnbIdx); // This API Need to Check
		if(isTuner2Active()){
			l_id = satInst2.GetSatId(p_lnbIdx);
		}else{
			l_id = satInst.GetSatId(p_lnbIdx);
		}
		
		
		Log.d(TAG, "GetSatDetectedID returning " + String.valueOf(l_id));
		return l_id;
	}
	
	public int GetCountry()
	{
		Log.d(TAG, "GetCountry entry");
		int l_countryId = 0; 
		
		l_countryId = m_settings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		
		Log.d(TAG, "GetCountry returning" + String.valueOf(l_countryId));
		return l_countryId;
	}
	
	public boolean GetIsNordicCountry()
	{
		Log.d(TAG, "GetIsNordicCountry entry");
		boolean l_ret = false;
		int l_countryId = m_settings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		switch(l_countryId)
		{
			case InstallationCountryConstants.DENMARK:
			case InstallationCountryConstants.FINLAND:
			case InstallationCountryConstants.NORWAY:
			case InstallationCountryConstants.SWEDEN:
				l_ret = true;
				break;
			default:
				l_ret = false;
				break;
		}
		Log.d(TAG, "GetIsNordicCountry returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	
	public void SetBouquetIndex(int p_index)
	{
		Log.d(TAG, "SetBouquetIndex entry" + p_index);
		HsvPackageStructure l_pkgStructure;
		l_pkgStructure = satInst.GetPackageByIndex(p_index);
		satInst.SetBouquetIndex(l_pkgStructure.PackageId);
		Log.d(TAG, "SetBouquetIndex exit  ");
	}
	
	public void SetPackageIDDirectly(int pkgID){
		Log.d(TAG, "SetPackageIDDirectly " + pkgID);
		satInst.SetBouquetIndex(pkgID);
	}
	
	public void SetScanStops()
	{
		Log.d(TAG, "SetScanStops entry");
		new Thread(new Runnable()
		 {
			    public void run()
			    {
			    	Log.d(TAG, "stopping scan in new thread");
			    	if(isTuner2Active()){
						satInst2.StopInstallation();
					}else{
						satInst.StopInstallation();
					}
			    }
			  }).start();
		if(m_installMode != INSTALL_MODE_NONE)
		{
			sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_STOPPED");
			setInstallMode(INSTALL_MODE_NONE);
		}
		Log.d(TAG, "SetScanStops exit");
	}
	
	public boolean IsSatelliteDuplicate(int p_lnbIdx)
	{
		Log.d(TAG, "IsSatelliteDuplicate entry");
		boolean l_ret = false;
		int LnbStatus; 
		if(isTuner2Active()){
			LnbStatus = satInst2.getLnbStatus(p_lnbIdx);
		}else{
			LnbStatus = satInst.getLnbStatus(p_lnbIdx);
		}
		if(MwDataTypes.LnbDuplicate ==  LnbStatus) {
			l_ret = true;
		} 
		Log.d(TAG, "IsSatelliteDuplicate returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	public String GetSatelliteName(int p_lnbIdx)
	{
		Log.d(TAG, "GetSatelliteName entry");
		String l_retString = "";
		if(isTuner2Active()){
			l_retString = satInst2.GetSatelliteName(p_lnbIdx);
		}else{
			l_retString = satInst.GetSatelliteName(p_lnbIdx);
		}
		Log.d(TAG, "GetSatelliteName returning" + l_retString);
		return l_retString;
	}
	
	public boolean GetIsRecognisedSatellite(int p_lnbIdx)
	{
		Log.d(TAG, "GetIsRecognisedSatellite entry");
		int SatelliteId;
		if(isTuner2Active()){
			SatelliteId = satInst2.GetSatId(p_lnbIdx);
		}else{
			SatelliteId = satInst.GetSatId(p_lnbIdx);
		}
		boolean l_ret = false;
		if(SatelliteId != MwDataTypes.UNKNOWN_SATELLITE) {
			l_ret = true;
		}
		Log.d(TAG, "GetIsRecognisedSatellite returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	public void StartPackageParsing()
	{
		Log.d(TAG, "StartPackageParsing entry");
		//satInst.bindChannelVersionManagerService();
		satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, 0, MwDataTypes.IHsvSatelliteInstallation_InstallationPackageParsing);
		//satInst.IdentifyPackagesAvailable();
		Log.d(TAG, "StartPackageParsing exit");
	}
	
	
	public String[] GetBouquetNames()
	{
		Log.d(TAG, "GetBouquetNames entry");
		int l_idx;
		int l_numPackages;
		int l_stringId;
		BouquetIdMapping l_bouquetMapping = BouquetIdMapping.getInstance();
		HsvPackageStructure l_pkgStructure;
		String[] l_ret; //= SatelliteConstants.PACKAGE_ITEMS;
		l_numPackages = satInst.GetTotalNumberOfPackagesFound();
		l_ret = new String[l_numPackages];
		Log.d(TAG,"Number of packages = " + String.valueOf(l_numPackages));
		
		// for fransat: if country is FRANCE & satellite is Eutilsat
		int countryID = GetCountry();
		int satID = GetSatDetectedID(0); // TODO:to be updated wih valid LNB ID
		Log.d(TAG, "INSTALLATIONCOUNTRY " + countryID + "satID" +satID);
		boolean l_isCamBasedInstallation = satInst.isOperatorProfileSupported();
		
		for(l_idx = 0; l_idx < l_numPackages; l_idx ++)
		{
			l_pkgStructure = satInst.GetPackageByIndex(l_idx);
			if ((((l_pkgStructure.PackageId & 0xFFFF) == MwDataTypes.FRANSAT_PACKAGE_ID) && 
					(countryID == InstallationCountryConstants.FRANCE) )||(l_isCamBasedInstallation && ((l_pkgStructure.PackageId & 0xFFFF) == MwDataTypes.OPERATOR_PROFILE_PACKAGE_ID)))
				
			{
				Log.d(TAG,"Installation PackageListName " + l_pkgStructure.PackageListName);
				Log.d(TAG,"Installation PackageName " + l_pkgStructure.PackageName);
				l_ret[l_idx] = l_pkgStructure.PackageListName;
			}else{
				l_stringId = l_bouquetMapping.getPackageStringId(l_pkgStructure.PackageId);
				l_ret[l_idx] = ctx.getString(l_stringId);
			}
			Log.d(TAG, "GetBouquetNames l_idx  " + l_idx  + "pkgid"+ l_pkgStructure.PackageId + "l_ret" +l_ret[l_idx] );
		}
		//l_ret = SatelliteConstants.PACKAGE_ITEMS; // TODO: REMOVE this	
		return l_ret;
	}
	
	public String GetSelectedPackageName() 
	{
		Log.d(TAG, "GetSelectedPackage entry");
		int l_stringId;
		String l_retString;
		int l_installState = satInst.GetCurrentInstallationState();
		int l_packageId = satInst.GetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageId);

		l_stringId = BouquetIdMapping.getInstance().getPackageStringId(l_packageId);
		l_retString = ctx.getString(l_stringId);
		
		Log.d(TAG, "GetSelectedPackageName returning" + l_retString);
		return l_retString;
	}
	
	public boolean ifOperatorProfilePackage() {
		boolean retStatus = false;
		int installState = satInst.GetCurrentInstallationState();
		int packageId = satInst.GetAttribute(installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageId);
		Log.d(TAG, "packageId: " + packageId);

		if (packageId == MwDataTypes.OPERATOR_PROFILE_PACKAGE_ID) {
			retStatus = true;
		}

		Log.d(TAG, "ifOperatorProfilePackage: " + retStatus);
		return retStatus;
	}

	
	public boolean isM7Package() {
		boolean retVal = false;
		int pakageGroupID = satInst.GetAttribute(0, MwDataTypes.IHsvSatelliteInstallation_AttributePackageGroup);
		if(pakageGroupID == MwDataTypes.PKG_ID_M7){
			retVal = true;
		}
		Log.d(TAG, "pakageGroupID: " + pakageGroupID + " ifM7Package: " + retVal);
		return retVal;
	}

	public boolean isPredefinedRankingList() {
		Log.d(TAG, "isPredefinedRankingList entry");
		boolean retStatus = false;
		retStatus = satInst.GetUserPackageIndex();
		Log.d(TAG, "if package: " + retStatus);
		retStatus = !retStatus;

		Log.d(TAG, "isPredefinedRankingList returning: " + String.valueOf(retStatus));
		return retStatus;
	}
	
	public void SetSelectedPackage(boolean p_isPackageOnly)//sets package only or all
	{
		Log.d(TAG, "SetSelectedPackage entry");
		int  l_installState = satInst.GetCurrentInstallationState();
		if(p_isPackageOnly)
		{
			satInst.SetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageOnly, MwDataTypes.InsEnumPackageonly);
		}
		else
		{
			satInst.SetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageOnly, MwDataTypes.InsEnumAllchannels);
		}
		Log.d(TAG, "SetSelectedPackage entry");
	}
	
	public int GetScannedLNB()
	{
		Log.d(TAG, "GetScannedLNB entry");
		int l_ret = m_currentLNBIdx;
		Log.d(TAG, "GetScannedLNB returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	//TODO : use enums for parameters
	//p_isPackage : indicates LNB/package
	//p_isAdded : added/removed
	public int GetTvServices(Boolean p_isAdded, int p_lnbIdx)
	{
		Log.d(TAG, "GetTvServices entry");
		int l_ret = 0;
		if(p_isAdded)
		{
			if(isTuner2Active()){
				l_ret = satInst2.GetNumberOfTvChannelsFound(p_lnbIdx);
			}else{
				l_ret = satInst.GetNumberOfTvChannelsFound(p_lnbIdx);
			}
		}
		else
		{
			if(isTuner2Active()){
				l_ret = satInst2.GetNumberOfTvChannelsRemoved(p_lnbIdx);
			}else{
				l_ret = satInst.GetNumberOfTvChannelsRemoved(p_lnbIdx);
			}
		}
		
		Log.d(TAG, "GetTvServices returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	public int GetRadioServices(Boolean p_isAdded,
			int p_lnbIdx) {
		Log.d(TAG, "GetRadioServices entry");
		int l_ret = 0;

		if (p_isAdded) {
			if (isTuner2Active()) {
				l_ret = satInst2.GetNumberofRadioChannelsFound(p_lnbIdx);
			} else {
				l_ret = satInst.GetNumberofRadioChannelsFound(p_lnbIdx);
			}

		} else {
			if (isTuner2Active()) {
				l_ret = satInst2.GetNumberofRadioChannelsRemoved(p_lnbIdx);
			}
			{
				l_ret = satInst.GetNumberofRadioChannelsRemoved(p_lnbIdx);
			}
		}

		Log.d(TAG, "GetRadioServices returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	public String GetPackageName()
	{
		Log.d(TAG, "GetPackageName entry");
		String l_ret = "";
		int l_stringId;
		int l_packageId;
		
		int countryID = GetCountry();


		BouquetIdMapping l_bouquetMapping = BouquetIdMapping.getInstance();
		int l_installState = satInst.GetCurrentInstallationState();
		l_packageId = satInst.GetAttribute(l_installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageId);
		Log.d(TAG, "l_installState: " + l_installState + " l_packageId:" + l_packageId);
		if(((l_packageId& 0xFFFF) == MwDataTypes.FRANSAT_PACKAGE_ID) && 
							(countryID == InstallationCountryConstants.FRANCE))
		{
			Log.d(TAG, "get pkg name for Fransat"); 
			l_ret = satInst.GetPackageName(l_packageId);
		} else if ( l_packageId == MwDataTypes.OPERATOR_PROFILE_PACKAGE_ID) {
			Log.d(TAG, "Get operator profile name");
			l_ret = satInst.GetPackageName(l_packageId);
        } else {
			l_stringId = l_bouquetMapping.getPackageStringId(l_packageId);
			l_ret = ctx.getString(l_stringId);
		}
		
		Log.d(TAG, "GetPackageName exit" + l_ret);
		return l_ret;
	}
	
	public int GetServiceScanStatus()
	{
		Log.d(TAG, "GetServiceScanStatus entry");
		int l_ret = 0;
		l_ret = satInst.GetScanProgressStatus(MwDataTypes.IHsvSatelliteInstallation_InstallationServiceScan);
		Log.d(TAG, "GetServiceScanStatus returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	public int GetLNBforManualIns()
	{
		Log.d(TAG, "GetLNBforManualIns entry");
		int l_ret = mLNBSelectedForManualIns;
		Log.d(TAG, "GetLNBforManualIns returning" + String.valueOf(l_ret));
		return l_ret;
	}
	
	public Boolean IsLNBFree(int p_lnbIdx)
	{
		Log.d(TAG, "IsLNBFree entry for " + String.valueOf(p_lnbIdx));
		Boolean l_ret = false;
		int LnbStatus;
		if(isTuner2Active()){
			LnbStatus = satInst2.getLnbStatus(p_lnbIdx);
		}else{
			LnbStatus = satInst.getLnbStatus(p_lnbIdx);
		}
		if(LnbStatus == MwDataTypes.LnbFree)
		{
			l_ret = true;
		} 
		Log.d(TAG, "IsLNBFree returning" + String.valueOf(l_ret));
		return l_ret;

	}
	
	public Boolean IsLNBInstalled(int p_lnbIdx)
	{
		Log.d(TAG, "IsLNBInstalled entry for " + String.valueOf(p_lnbIdx));
		Boolean l_ret = false;
		int LnbStatus = satInst.getLnbStatus(p_lnbIdx);
		if(LnbStatus == MwDataTypes.LnbInstalled)
		{
			l_ret = true;
		} 
		Log.d(TAG, "IsLNBInstalled returning" + String.valueOf(l_ret));
		return l_ret;

	}
	
	public Boolean IsDualTunerOn()
	{
		Log.d(TAG, "IsDualTunerOn entry");
		Boolean l_ret = (mCachedDualTunerSetting != 0) ? true: false /*true*/;
		Log.d(TAG, "IsDualTunerOn returning" + String.valueOf(l_ret));
		return l_ret;

	}
	
	//called from the dual tuner screen on selecting the list
	public void setDualTunerToTVS(boolean p_isDualTunerOn) {
		Log.d(TAG, "setDualTunerOn entry " + p_isDualTunerOn);
		mCachedDualTunerSetting = (p_isDualTunerOn == true) ? 1 : 0;
		Log.d(TAG, "setDualTunerOn exit ");
	}
	
	public void initializeCache () {
		userSelectedMode = SelectedMode.ADVANCED;
		if(isTwoTunerSupported()){
			mCachedDualTunerSetting = m_settings.getInt(TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, 0 );
		}else{
			mCachedDualTunerSetting = 0;
		}
		reloadSelectedLNBs();
		Log.d(TAG, "DualTunerInitialized with " + mCachedDualTunerSetting);
	}
	
	
	public boolean isUpdateControllable()
	{
		Log.d(TAG, "isUpdateControllable entry");
		boolean l_ret = false;
		int l_idx;
		int l_installedLNBCount = 0;
		int l_maxLNBCount = 4;
		for(l_idx = 0; l_idx < l_maxLNBCount; l_idx ++)
		{
			if(mNativeAPIWrapper.IsLNBInstalled(l_idx))
			{
				l_installedLNBCount++;
			}
		}
		if(l_installedLNBCount > 0)
		{
			l_ret = true;
		}
		Log.d(TAG, "isUpdateControllable returning " + l_ret);
		return l_ret;
	}
	
	public boolean isAddSatelliteControllable()
	{
		Log.d(TAG, "isAddSatelliteControllable entry");
		boolean l_ret = false;
		boolean isPackage = false;
		int l_numInstalledLNB = 0;
		int l_numFreeLNB = 0;
		int l_maxLNBCount = 4;
		int l_idx;
		isPackage = satInst.GetUserPackageIndex();
	
	
		if(!isPackage)
		{	
				
			if(satInst.GetLNBType() == LnbSettingsEntry.LnbConnectionDiSeqc1_0)
			{
				if(isUpdateControllable())//atleast one LNB is installed
				{
					for(l_idx = 0; l_idx < l_maxLNBCount; l_idx ++)
					{
						if(IsLNBInstalled(l_idx))
						{
							l_numInstalledLNB++;
						}
						if(IsLNBFree(l_idx))
						{
							l_numFreeLNB++;
						}
					}
					if( (l_numFreeLNB>0) && (l_numInstalledLNB>0))
					{
						l_ret = true;
					}
				}
				
			}
		}
		
		Log.d(TAG, "isAddSatelliteControllable returning " + l_ret);
		return l_ret;
	}
	
	public boolean isRemoveSatelliteControllable()
	{
		Log.d(TAG,"isRemoveSatelliteControllable entry");
		boolean l_ret = false;
		boolean isPackage = false;
		int l_numInstalledLNB = 0;
		int l_maxLNBCount = 4;
		int l_idx;
		int LnbStatus = MwDataTypes.LnbFree;
		isPackage = satInst.GetUserPackageIndex();
		
		if(!isPackage)
		{
			if(satInst.GetLNBType() == LnbSettingsEntry.LnbConnectionDiSeqc1_0)
			{
				for(l_idx = 0; l_idx < l_maxLNBCount; l_idx ++)
				{
					LnbStatus = satInst.getLnbStatus(l_idx);
					Log.d(TAG, "getLnbStatus returning " + LnbStatus + " for index " + l_idx);
					if((LnbStatus == MwDataTypes.LnbInstalled) || (LnbStatus == MwDataTypes.LnbManualInstalled))
					{
						l_numInstalledLNB++;
					} 
				}
				if(l_numInstalledLNB>0)
				{
					l_ret = true;
				}
			}
		}
		Log.d(TAG, "isRemoveSatelliteControllable returning " + l_ret);
		return l_ret;
	}
	
	public void SetServiceStore()
	{
		Log.d(TAG, "SetServiceStore entry");
		satInst.StoreManualInstallationValues();
		Log.d(TAG, "SetServiceStore exit");
	}
	
	public void SetManualInstallFinished()
	{
		Log.d(TAG, "SetManualInstallFinished entry");
		//Tune
		Log.d(TAG, "SetManualInstallFinished exit");
	}
	
	public int getFirstInstalledChannel()
	{
		Log.d(TAG, "getFirstInstalledChannel entry");
		int l_ret = 0;
		
		l_ret = satInst.GetFirstInstalledChannel();

		Log.d(TAG, "getFirstInstalledChannel exit " + String.valueOf(l_ret));
		return l_ret;
	}
	
	
	public void SetTypeOfLNB(int p_connectionType)
	{
		Log.d(TAG,"SetTypeOfLNB entry " + String.valueOf(p_connectionType)); //TODO : get enums from jni

		// set connection type to MW
		satInst.SetConnectionType(p_connectionType);
		
		// setdatasource to tvplayer
		if(p_connectionType == LnbSettingsEntry.LnbConnectionSatIP){
			setSessionTuneWithMedium(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER,  SESSION_MEDIUM.SATIP);
		}else{
			setSessionTuneWithMedium(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER, SESSION_MEDIUM.DVBS2);
		}
		
		Log.d(TAG,"SetTypeOfLNB exit");
	}
	
	public int GetUnicableUBNumber()
	{
		Log.d(TAG,"GetUnicableUBNumber entry");
		int l_ret = 0;
		int l_ubn;
		byte l_ubnByte;
		int l_idx;
		LnbSettingsEntry l_lnbSettings; 
		byte UserBand;
		UserBand = satInst.GetUserBand(0);
		l_ubnByte = UserBand;
		l_ubn = Integer.parseInt(Byte.toString(l_ubnByte));
		if((l_ubn >= 0) && (l_ubn <= 7) )
		{
			l_ret = l_ubn;
		}
		else
		{
			Log.d(TAG,"UnicableUBNumber is not valid ");
		}
		Log.d(TAG,"GetUnicableUBNumber returning " + String.valueOf(l_ret));
		return l_ret;
	}
	
	public int GetUnicableUBNumberTuner2()
	{
		Log.d(TAG,"GetUnicableUBNumberTuner2 entry");
		int l_ret = 0;
		int l_ubn;
		byte l_ubnByte;
		byte UserBand;
		UserBand = satInst.GetUserBand(2);
		l_ubnByte = UserBand;
		l_ubn = Integer.parseInt(Byte.toString(l_ubnByte));
		if((l_ubn >= 0) && (l_ubn <= 7) )
		{
			l_ret = l_ubn;
		}
		else
		{
			Log.d(TAG,"UnicableUBNumber is not valid ");
		}
		Log.d(TAG,"GetUnicableUBNumberTuner2 returning " + String.valueOf(l_ret));
		return l_ret;
	}
	
	public void SetUnicableUBNumber(int p_ubn)
	{
		Log.d(TAG,"SetUnicableUBNumber entry");
		satInst.SetUnicableUBNumber(p_ubn);
		//satInst.EnableUnicable(0, true);
		Log.d(TAG,"SetUnicableUBNumber exit");
	}
	
	public void SetUnicableUBNumberTuner2(int p_ubn)
	{
		Log.d(TAG,"SetUnicableUBNumberTuner2 entry");
		//TODO : dual tuner jni integ
		satInst.SetUnicableUBNumberTuner2(p_ubn);
		//satInst.EnableUnicable(0, true);
		Log.d(TAG,"SetUnicableUBNumberTuner2 exit");
	}
	
	public int GetUnicableUBFreq()
	{
		Log.d(TAG,"GetUnicableUBFreq entry");
		int l_ret = 0;
		int UserBandFrequency = satInst.GetUserFrequency(0);
		l_ret = UserBandFrequency;
		Log.d(TAG,"GetUnicableUBFreq returning " + String.valueOf(l_ret));
		return l_ret;
	}
	
	public int GetUnicableUBFreqTuner2()
	{
		Log.d(TAG,"GetUnicableUBFreqTuner2 entry");
		int l_ret = 0;
		//TODO : dual tuner jni integ
		l_ret = satInst.GetUnicableUBFreqTuner();
		Log.d(TAG,"GetUnicableUBFreqTuner2 returning " + String.valueOf(l_ret));
		return l_ret;
	}
	
	public void SetUnicableUBFreq(int p_freq)
	{
		Log.d(TAG,"SetUnicableUBFreq entry");
	/*	LnbSettingsEntry l_lnbSettings;
		l_lnbSettings = satInst.GetLnbSettings(0);
		l_lnbSettings.UserBandFrequency = p_freq;
		//TODO : set call needed from jni
		l_lnbSettings = satInst.GetLnbSettings(1);
		l_lnbSettings.UserBandFrequency = p_freq;
		//TODO : set call needed from jni
*/
		satInst.SetUnicableUBFreq(p_freq);
		//satInst.EnableUnicable(0, true);

		Log.d(TAG,"SetUnicableUBFreq exit");
	}
	
	public void SetUnicableUBFreqTuner2(int p_freq)
	{
		Log.d(TAG,"SetUnicableUBFreq entry");
		//TODO : dual tuner jni integ
		Log.d(TAG,"SetUnicableUBFreq exit");
		satInst.SetUnicableUBFreqTuner(p_freq);
		//0,1 //Primary Valure
		//2,3 //Secondar Value
	}
	
	public boolean isDTRStoreOptionAvailable()
	{
		Log.d(TAG,"isDTRStoreOptionAvailable entry");
		boolean returnStatus = true;
		
		if(isTuner2Active()){
			returnStatus = false;
		}else{
			// check if digiturk disable dtr
			/* TF515PHIALLMVL01-8129(340473) */
			int pakageGroupID = satInst.GetAttribute(0, MwDataTypes.IHsvSatelliteInstallation_AttributePackageGroup);
			Log.d(TAG, "pakageGroupID: " + pakageGroupID);
			if((pakageGroupID == MwDataTypes.PKG_ID_TURK) || (pakageGroupID == MwDataTypes.PKG_ID_M7)){
				returnStatus = false;
			}
		}

		Log.d(TAG,"isDTRStoreOptionAvailable package" + m_settings.getInt(TvSettingsConstants.OPERATORSATELLITE, 0, 0 ) );
		if( m_settings.getInt(TvSettingsConstants.OPERATORSATELLITE, 0, 0 ) == TvSettingsDefinitions.OperatorSatelliteConstants.TRICOLOR )
		{
			returnStatus = false;
		}

		Log.d(TAG,"isDTRStoreOptionAvailable returning " + returnStatus);
		return returnStatus;
	}
	
	public boolean isSatelliteAdded(int p_lnbIdx)
	{
		Log.d(TAG,"isSatelliteAdded entry for " + String.valueOf(p_lnbIdx));
		boolean l_ret = false;
		int LnbStatus = satInst.getLnbStatus(p_lnbIdx);
		if(LnbStatus != MwDataTypes.LnbFree)
		{
			l_ret = true;
		}
		Log.d(TAG,"isSatelliteAdded returning " + String.valueOf(l_ret));
		return l_ret;
	}
	/*
	 * 
	 */
	public void updateAddedLNBIndex(int p_lnbIndex)
	{
		Log.d(TAG,"updateAddedLNBIndex " + p_lnbIndex);
		int[] lnbConst = new int[]{	MwDataTypes.IHsvSatelliteInstallation_SatLnb1,
				MwDataTypes.IHsvSatelliteInstallation_SatLnb2,
				MwDataTypes.IHsvSatelliteInstallation_SatLnb3,
				MwDataTypes.IHsvSatelliteInstallation_SatLnb4};
		
		int LnbStatus = satInst.getLnbStatus(p_lnbIndex);
		if(LnbStatus != MwDataTypes.LnbDuplicate)
		{
			Log.d(TAG,"adding lnb to list");
			m_oredLNBValue|=lnbConst[p_lnbIndex];
		}
		
		
	}
	
	/*
	 * m_oredLNBValue keeps track of the list of newly added LNB indices
	 */
	public void clearCachedAddedLNBIndex()
	{
		Log.d(TAG,"clearCachedAddedLNBIndex");
		m_oredLNBValue = 0x00;
		
	}
	
	public void SetAddInstallStart()
	{
		Log.d(TAG,"SetAddInstallStart entry");
		new Thread(new Runnable()
		 {
			    public void run()
			    {
			     //   satInst.bindChannelVersionManagerService();
					IsMajorVersionChange = false;
					satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, m_oredLNBValue, MwDataTypes.IHsvSatelliteInstallation_InstallationAddSatellite);
			    }
			  }).start();
		
		Log.d(TAG,"SetAddInstallStart exit");
	}

	
	public void SetAddInstallPrescanStart()
	{
		Log.d(TAG,"SetAddInstallPrescanStart entry");
		new Thread(new Runnable()
		 {
			    public void run()
			    {
					satInst.StartInstallation(MwDataTypes.IHsvAppApiMainTuner, m_oredLNBValue, MwDataTypes.IHsvSatelliteInstallation_InstallationAddSatellite | MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan);
			    }
			  }).start();
		
		Log.d(TAG,"SetAddInstallPrescanStart exit");
	}
	
	public boolean GetInsUpdateSatelliteChecked(int p_lnbIdx)
	{
		boolean l_ret = false;
		Log.d(TAG,"GetInsUpdateSatelliteChecked entry " + p_lnbIdx);
		l_ret = satInst.GetUpdateInstallEnabled(p_lnbIdx);
		Log.d(TAG,"GetInsUpdateSatelliteChecked returning " + String.valueOf(l_ret));
		return l_ret;
	}
	
	public void SelectLNBForUpdate(SparseBooleanArray p_array)
	{
		Log.d(TAG,"SelectLNBForUpdate entry");
		int l_count = p_array.size();
		int l_idx;
		//LnbSettingsEntry l_lnbSettings;
		Log.d(TAG,"number of items:" + l_count);
		for(l_idx = 0; l_idx < l_count; l_idx ++)
		{
			//l_lnbSettings = satInst.GetLnbSettings(l_idx);
			if(p_array.get(l_idx) == true)
			{
				//l_lnbSettings.UpdateInstallEnabled = true;
				satInst.SelectLNBForUpdate(l_idx, true);
			}
			else
			{
				satInst.SelectLNBForUpdate(l_idx, false);
				//l_lnbSettings.UpdateInstallEnabled = false;
			}
			
			//satInst.SetLnbSettings(l_idx,l_lnbSettings);
		}
		Log.d(TAG,"SelectLNBForUpdate exit");
	}
	

	
	
	public boolean isRemoveControllable(int p_lnbIdx)
	{
		Log.d(TAG,"isRemoveControllable entry for" + p_lnbIdx);
		boolean l_ret = false;
		int LnbStatus = satInst.getLnbStatus(p_lnbIdx);
		if(LnbStatus == MwDataTypes.LnbInstalled || LnbStatus == MwDataTypes.LnbDuplicate || LnbStatus == MwDataTypes.LnbManualInstalled)
		{
			l_ret = true;
		}
		Log.d(TAG,"isRemoveControllable returning" + l_ret);
		return l_ret;
	}
	
	public void SetRemoveSatellite(final int p_lnbIdx)
	{
		Log.d(TAG,"SetRemoveSatellite entry for" + p_lnbIdx);
		
		 new Thread(new Runnable()
		 {
			    public void run()
			    {
			    	 Log.d(TAG,"Removing satellite in new thread");
			    	satInst.RemoveSatelliteEntry(p_lnbIdx);
			    }
			  }).start();
		Log.d(TAG,"SetRemoveSatellite exit");
	}
	
	public void SetUpdateSorting()
	{
		Log.d(TAG,"SetUpdateSorting entry");
		satInst.StartPredefinedListCopy();
		Log.d(TAG,"SetUpdateSorting exit");
	}
	

	@Override
	public void update(Observable arg0, Object data) {
		Log.d(TAG, "update: action " + ((NotificationInfoObject) data).actionID + ", message " + ((NotificationInfoObject) data).message);
		final int l_eventID = ((NotificationInfoObject) data).actionID;
		switch (l_eventID) {

		case EventIDs.LNB_INSTALL_STARTED:
			String l_msg = (String) ((NotificationInfoObject) data).message;
			m_currentLNBIdx = Integer.parseInt(l_msg);
			Log.d(TAG, "m_currentLNBIdx set to : " + m_currentLNBIdx);
			break;
		case EventIDs.OP_PROFILE_INSTALL_REQUEST_IMMEDIATE:
			Log.d(TAG, "OP_PROFILE_INSTALL_REQUEST_IMMEDIATE");
			if ( ((getApplicationState() == STATE_IDLE) || (getApplicationState() == STATE_SERVICE) || (getApplicationState() == STATE_BACKGROUND_UPDATE)) 
					&& (satInst.ifOPProfLaterPressed() == false) 
				&& (ifCurrentlyInNonInterruptibe == false)){
				launchCamBasedInstallation();
			}
			break;
		case EventIDs.OP_PROFILE_INSTALL_REQUEST_URGENT:
			Log.d(TAG, "OP_PROFILE_INSTALL_REQUEST_URGENT");
			if(CamNitUpdateInstallTriggered == false)
			{
				CamNitUpdateInstallPerformed = true;
				launchCamInstallUrgent();
				CamNitUpdateInstallTriggered = true;
			}
			break;
		case EventIDs.CAM_NIT_INSTALLATION:
			Log.d(TAG, "CAM_NIT_INSTALLATION");
			if(CamNitUpdateInstallTriggered == false)
			{
				CamNitUpdateInstallPerformed = true;
				launchCamInstallUrgent();
				CamNitUpdateInstallTriggered = true;
			}
			break;
		case EventIDs.MAJORVERSION_UPDATE:
			IsMajorVersionChange = true;
			break;
		case EventIDs.STORE_OP_CICAMID:
			Log.d(TAG, "STORE_OP_CICAMID");
			StoreCiCamforOp((long)satInst.getOpProfileCiCamId());
			break;
		case EventIDs.CHECK_START_NEW_CAM_OP:
			Log.d(TAG, "CHECK_START_NEW_CAM_OP");
			if ((getApplicationState() == STATE_IDLE) || (getApplicationState() == STATE_SERVICE) || (getApplicationState() == STATE_BACKGROUND_UPDATE)){
				if(checkForCiCamId((long)satInst.getOpProfileCiCamId()) == true){
					Log.d(TAG, "CiCamid is different!!");
					launchCamBasedInstallation();
				}else if(checkForCiCamNitRequest() == true){
					Log.d(TAG, "Check for nit request is succeeded so trigger launchCamInstallUrgent!!");
					if(CamNitUpdateInstallTriggered == false)
					{
						CamNitUpdateInstallPerformed = true;
						launchCamInstallUrgent();
						CamNitUpdateInstallTriggered = true;
					}
				}else{
					Log.d(TAG, "CiCamid is same!! Info version is not modified with profile containers");
				}
			}
			break;
		}
	}

	public boolean iscamnitbasedinstallation()
	{
		Log.d(TAG, "iscamnitbasedinstallation returns : " + CamNitUpdateInstallPerformed);
		return CamNitUpdateInstallPerformed;
	}

	public void camprofileInstallationCompleted()
	{
		Log.d(TAG, "EVENT_INST_COMPLETED");	
		if(CamNitUpdateInstallTriggered == true)
		{
			Log.d(TAG, "Installation completed in cam nit based installation");
			CamNitUpdateInstallPerformed = false;
			CamNitUpdateInstallTriggered = false;
		}
	}
	public void launchCamBasedInstallation() {
		Log.d(TAG,"launchCamBasedInstallation ctx " + ctx);
		if(ctx != null){
			Intent intent = new Intent(ctx, CamOpProfDialogActivity.class);
			intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			ctx.startActivity(intent);
		}
	}
	public void launchCamInstallUrgent() {
		Log.d(TAG,"launchCamInstallUrgent");
		Intent intent;
		//satInst.registerCIListener();
		intent = new Intent(ctx,CamOpProfInstallActivity.class);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
		ctx.startActivity(intent);
		
	}
	/*
	public void tuneOnFinish()
	{
		SetHostControlStatus(TunerName.TUNER1, true);
		SetHostControlStatus(TunerName.TUNER2, true);
		Log.d(TAG,"tuneOnFinish entry");
		m_settings.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 1);
		m_settings.putInt(TvSettingsConstants.CHANNELFILTER, 0, TvSettingsDefinitions.ChannelFilterConstants.ALL);
		m_settings.putInt(TvSettingsConstants.CHANNELFILTERSATELLITE, 0, TvSettingsDefinitions.ChannelFilterConstants.ALL);
		m_settings.putInt(TvSettingsConstants.SATELLITECHANNELSUBLIST, 0, 0);
		sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_COMPLETE");
		setInstallMode(INSTALL_MODE_NONE);
		

		muteAudio(false);
		if(!isVirginInstallMode())
		{
			switchToFirstAvailableChannel(true);
		}
		else
		{
			Log.d(TAG,"Virgin installation, not tuning");
			//reset();
		}
		Log.d(TAG,"tuneOnFinish exit");
	}
	*/
        private void mDeleteSatelliteEntryForVersion (int Version)
        {
                int     RowsDeleted = 0;
                
                String  mselection=Channels.COLUMN_VERSION_NUMBER+"= ?";
                String[]        mselectionargs=new String[]{String.valueOf(Version)};
                RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection,mselectionargs);
                Log.d(TAG,"RemoveSatelite: RowsDeleted "+RowsDeleted+"For VersionNumber" + Version);
        }
        
        public void RemoveFromSatelliteDb(int oredLnbIdx)
        {
                int             SATELLITE_MEDIUM_BASE   =2;
                if ((oredLnbIdx & MwDataTypes.IHsvSatelliteInstallation_SatLnb1) == MwDataTypes.IHsvSatelliteInstallation_SatLnb1)
                {
                        mDeleteSatelliteEntryForVersion(SATELLITE_MEDIUM_BASE);
                }
                if ((oredLnbIdx & MwDataTypes.IHsvSatelliteInstallation_SatLnb2) == MwDataTypes.IHsvSatelliteInstallation_SatLnb2)
                {
                        mDeleteSatelliteEntryForVersion(SATELLITE_MEDIUM_BASE+1);
                }
                if ((oredLnbIdx & MwDataTypes.IHsvSatelliteInstallation_SatLnb3) == MwDataTypes.IHsvSatelliteInstallation_SatLnb3)
                {
                        mDeleteSatelliteEntryForVersion(SATELLITE_MEDIUM_BASE+2);
                }
                if ((oredLnbIdx & MwDataTypes.IHsvSatelliteInstallation_SatLnb4) == MwDataTypes.IHsvSatelliteInstallation_SatLnb4)
                {
                        mDeleteSatelliteEntryForVersion(SATELLITE_MEDIUM_BASE+3);
                }
				mUpdateDatabaseVersion(true);
        }	
	
	private void switchToFirstAvailableChannel(boolean p_isInstallationComplete) {
		Log.d(TAG, "switchToFirstAvailableChannel entry: " + p_isInstallationComplete);

		int channelId = -1;
		Uri playUri;
		

		int mChannelNum = 0;
		Cursor cursor;

		/* For SRT if Store option is not available, need to do default tuning alone */
		if ((satInst.GetCurrentInstallationMode() == MwDataTypes.IHsvSatelliteInstallation_InstallationManual) && isDTRStoreOptionAvailable())
			{
				Log.d(TAG,"For DTR Store not available, doing default tuning ");
				p_isInstallationComplete = false;
			}

		if (p_isInstallationComplete) {
			channelId = satInst.GetFirstInstalledChannel();

			if((channelId == -1) || (channelId == 0XFFFF)){
				mChannelNum = m_settings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2, 0, 0);
				Log.d(TAG,"switchToFirstAvailableChannel LASTSELECTEDPRESETS2 " + mChannelNum);
			} else {
				String[] mProjection = new String[] { Channels._ID,Channels.COLUMN_TYPE };
				String mSelecion = "(" + TvContract.Channels.COLUMN_TYPE + "=? OR " + TvContract.Channels.COLUMN_TYPE + "=? ) " + "AND " +  Channels.COLUMN_DISPLAY_NUMBER + " =?";
							
				String[] mSelectionArgs = new String[]{Channels.TYPE_DVB_S,Channels.TYPE_DVB_S2,Integer.toString(channelId)};
				cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, mProjection, mSelecion, mSelectionArgs, null);

				if ((cursor != null) && (cursor.getCount() > 0)) {
					Log.d(TAG, "cursor.getCount()" + cursor.getCount());
					if (cursor.moveToFirst()) {
						try {
							mChannelNum = Integer.parseInt(cursor.getString(0));
						} catch (Exception ex) {
						}
					}
				} else {
					if (cursor != null){
						Log.d(TAG, "cursor.getCount()" + cursor.getCount());
					}
				}
				if(cursor != null){
					cursor.close();
					cursor=null;
				}
				Log.d(TAG, "mChannelNum: " + mChannelNum);
			}
		} else {
			Log.d(TAG, "Tuning to default");
			//playUri = tvuri.formURI(TvURIEnum.DEFAULT);
		}
		
		// enable back camUI before closing the session
		/*satInst.registerCIListener();
		if(isTwoTunerSupported()){
			satInst2.registerCIListener();
		}

		//reset();
		
		closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
		closeTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_AUX);
		*/
		if(mChannelNum != 0) 
		{
			String[] mProjection = new String[] { Channels._ID,Channels.COLUMN_TYPE };
			String mSelecion = "(" + TvContract.Channels.COLUMN_TYPE + "=? OR " + TvContract.Channels.COLUMN_TYPE + "=? ) " + "AND " +  Channels._ID + " =?";
							
			String[] mSelectionArgs = new String[]{Channels.TYPE_DVB_S,Channels.TYPE_DVB_S2,Integer.toString(mChannelNum)};
				
				
			cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, mProjection, mSelecion, mSelectionArgs, null);

			if ((cursor != null) && (cursor.getCount() > 0)) {
				//Log.d(TAG, "UniqueID checking for in DB" + c.getCount());
			} else {
				mChannelNum = 0;	
			}
			if(cursor != null){
				cursor.close();
				cursor=null;
			}
		}
		Intent playTVIntent = null;
		if(mChannelNum != 0)
		{
			playUri = TvContract.buildChannelUri(mChannelNum);
			Log.d(TAG, "raise intent to playtv: " + playUri.toString());
			
			//Intent playTVIntent = new Intent("org.droidtv.playtv.SELECTURI", playUri);
			playTVIntent = new Intent("android.intent.action.VIEW",playUri);
			//playTVIntent.putExtra("uri", playUri);
		} else {
			Log.d(TAG, "raise intent to WATCH_TV:"); 
			playTVIntent = new Intent("org.droidtv.playtv.WATCH_TV");
		}
		
		if (ctx instanceof SatInstallerService) {
			// intent raised from nervice context
			playTVIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		}
		try {
			ctx.startActivity(playTVIntent);
		} catch (Exception ex) {
			Log.e(TAG, "raise intent exception caught: " + ex.getMessage());
		}
		Log.d(TAG, "switchToFirstAvailableChannel exit");
	}

	
	public int getChannelfromID(int id)
	{
		int ret = 0;
		
		String[] projection = new String[] {Channels.COLUMN_DISPLAY_NUMBER};
		String	mselection = Channels._ID+"= ?";
		String[]	mselectionargs=new String[]{String.valueOf(id)};
		
		Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		
		if(cursor != null){
			if(cursor.moveToNext()) { 
				ret = cursor.getInt(0);
			}
			cursor.close();
			cursor=null;
		}
		else{
			Log.d(TAG, "cursor NULL, no channel in tv.db with _ID " + id);	
		}

		Log.d(TAG, "getChannelfromID ret " + ret);	
		return ret;			
	}
	
	/*** TVPROVIDER IMPLEMENTATION START ***/
	private String MapDecoderType(int DecoderType) {
		String Result;
		if(DecoderType == MwDataTypes.DVBS){
			Result = Channels.TYPE_DVB_S;
		}
		else{
			Result = Channels.TYPE_DVB_S2;
		}
		return Result;
	}

	
	private int ConvertDecoderType(String DecoderType) {
		int Result;
		if(DecoderType.equalsIgnoreCase(Channels.TYPE_DVB_S)){
			Result = MwDataTypes.DVBS;
		}
		else{
			Result = MwDataTypes.DVBS2;
		}
		return Result;
	}
	
	private String MapServiceType (int ServiceType) {
		String	MappedServiceType;

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

		return MappedServiceType;
	}


	public byte[] FormBlobPrivateData(SatInstallerTvProviderData TvpData,int Version)
	{

		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();
		byte[]	BlobPrivateData = null;
		
		privatekeyvalues.put (TvContractPrivate.C_FAVOURITENUMBER,TvpData.FavoriteNumber);
		privatekeyvalues.put (TvContractPrivate.C_VISIBLESERVICE,TvpData.VisibleService);
		privatekeyvalues.put (TvContractPrivate.C_LNBTYPE,TvpData.LnbType);
		privatekeyvalues.put (TvContractPrivate.C_SATID,TvpData.SatelliteId);
		privatekeyvalues.put (TvContractPrivate.C_ORBITALPOSITION,TvpData.OrbitalPosition);
		privatekeyvalues.put (TvContractPrivate.C_SIGNALSTRENGTH,TvpData.SignalStrength);
		privatekeyvalues.put (TvContractPrivate.C_SIGNALQUALITY,TvpData.SignalQuality);
		privatekeyvalues.put (TvContractPrivate.C_APPSCOOCKIE,TvpData.AppsCookie);
		privatekeyvalues.put (TvContractPrivate.C_SDTVERSION,TvpData.SDTVersion);
		privatekeyvalues.put (TvContractPrivate.C_NITVERSION,TvpData.NITVersion);
		privatekeyvalues.put (TvContractPrivate.C_LOWPRIOLCN,TvpData.LowPrioLCN);
		privatekeyvalues.put (TvContractPrivate.C_LOWPRIOVISIBLESERVICE,TvpData.LowPrioVisibleService);
		privatekeyvalues.put (TvContractPrivate.C_VIDEODESCPRESENT,TvpData.VideoDescPresent);
		privatekeyvalues.put (TvContractPrivate.C_DUPLICATESERVICE,TvpData.DuplicateSvc);
		privatekeyvalues.put (TvContractPrivate.C_SERVICELISTVERSION,TvpData.ServiceListVersion);
		privatekeyvalues.put (TvContractPrivate.C_USERINSTALLED,TvpData.UserInstalled);
		privatekeyvalues.put (TvContractPrivate.C_DVBTYPE,TvpData.DvbType);
		privatekeyvalues.put (TvContractPrivate.C_INSTALLEDSATNUMBER,TvpData.InstalledSatelliteNumber);
		privatekeyvalues.put (TvContractPrivate.C_NEWCHANNEL,TvpData.NewChannel);		
		privatekeyvalues.put (TvContractPrivate.C_SDSDFREQUENCY,TvpData.SDSDFrequency);
		privatekeyvalues.put (TvContractPrivate.C_COUNTRYCODE,TvpData.CountryCode);
		privatekeyvalues.put (TvContractPrivate.C_HDSIMULCASTREPONID,TvpData.HDSimulcastRepOnId);
		privatekeyvalues.put (TvContractPrivate.C_HDSIMULCASTREPTSID,TvpData.HDSimulcastRepTsId);
		privatekeyvalues.put (TvContractPrivate.C_HDSIMULCASTREPSVCID,TvpData.HDSimulcastRepSvcId);
		privatekeyvalues.put (TvContractPrivate.C_ASIGNALSTRENGTH,TvpData.ASignalStrength);
		privatekeyvalues.put (TvContractPrivate.C_VSIGNALSTRENGTH,TvpData.VSignalStrength);
		privatekeyvalues.put (TvContractPrivate.C_QSIGNALSTRENGTH,TvpData.QSignalStrength);
		privatekeyvalues.put (TvContractPrivate.C_CHANNELINFORMATION,TvpData.ChannelInformation);
		privatekeyvalues.put (TvContractPrivate.C_CODERATE,TvpData.CodeRate);
		privatekeyvalues.put (TvContractPrivate.C_PTCLISTVERSION,TvpData.PtcListVersion);
		privatekeyvalues.put (TvContractPrivate.C_TSVERSION,TvpData.TSVersion);
		privatekeyvalues.put (TvContractPrivate.C_PLPID,TvpData.PlpId);
		privatekeyvalues.put (TvContractPrivate.C_BARKERMUX,TvpData.BarkerMux);
		privatekeyvalues.put (TvContractPrivate.C_NUMBRANDIDS,TvpData.NumBrandIds);		
		privatekeyvalues.put (TvContractPrivate.C_FECINNER,TvpData.FECInner);		
		privatekeyvalues.put (TvContractPrivate.C_ROLLOFF,TvpData.RollOff);		

		privatekeyvalues.put (TvContractPrivate.C_SATELLITENAME,TvpData.SatelliteName);		
		privatekeyvalues.put (TvContractPrivate.C_MULTIPLELCN,TvpData.MultipleLCN);		
		privatekeyvalues.put (TvContractPrivate.C_MULTIPLEPRESET,TvpData.MultiplePreset);		
		privatekeyvalues.put (TvContractPrivate.C_MULTIPLEFAVORITE,TvpData.MultipleFavorite);		
		privatekeyvalues.put (TvContractPrivate.C_SERVICETYPE,TvpData.ServiceType);		
		

		privatekeyvalues.put (TvContractPrivate.C_VERSION,Version);		

		try {
			BlobPrivateData = privatekeyvalues.getBlob();
		} catch (Exception e) {
			Log.e(TAG, "Error in FormBlobPrivateData  " + e);
		}
		return BlobPrivateData;
	}

	private byte[] FormBlobData (SatInstallerTvProviderData TvpData, int CurrentVersion) {
		
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		byte[]	BlobData = null;

		keyvalues.put (ITvContractExtras.C_PRESETPTC,TvpData.Ptc);
		keyvalues.put (ITvContractExtras.C_FREQUENCY,TvpData.Frequency);
		keyvalues.put (ITvContractExtras.C_BANDWIDTH,TvpData.Bandwidth);
		keyvalues.put (ITvContractExtras.C_SYMBOLRATE,TvpData.SymbolRate);
		keyvalues.put (ITvContractExtras.C_MODULATION,TvpData.ModulationType);
		keyvalues.put (ITvContractExtras.C_NUMERICSELECT,TvpData.NumericSelect);
//		keyvalues.put (ITvContractExtras.C_SCRAMBLED,TvpData.ScrambledStatus);
//		keyvalues.put (ITvContractExtras.C_HBBTVON,TvpData.IntHbbTvOption);
		keyvalues.put (ITvContractExtras.C_USERHIDDEN,TvpData.UserHidden);
		keyvalues.put (ITvContractExtras.C_NEWPRESET,TvpData.NewPreset);
		keyvalues.put (ITvContractExtras.C_AUDIOPID,TvpData.AudioPid);
		keyvalues.put (ITvContractExtras.C_VIDEOPID,TvpData.VideoPid);
		keyvalues.put (ITvContractExtras.C_PCRPID,TvpData.PcrPid);
		keyvalues.put (ITvContractExtras.C_VIDEOSTREAMTYPE,TvpData.VideoStreamType);
		keyvalues.put (ITvContractExtras.C_AUDIOSTREAMTYPE,TvpData.AudioStreamType);
		keyvalues.put (ITvContractExtras.C_NetworkId,TvpData.NetworkId);
		keyvalues.put (ITvContractExtras.C_TXTSUBPAGE,TvpData.TextSubTitlePage);
		keyvalues.put (ITvContractExtras.C_SAP,TvpData.SAP);
		keyvalues.put (ITvContractExtras.C_PreferredStereo,TvpData.PreferredStereo);
		keyvalues.put (ITvContractExtras.C_LCN,TvpData.LCN);
		keyvalues.put (ITvContractExtras.C_USEROVERRULEDLOGOURI,TvpData.UserModifiedLogo);
		keyvalues.put (ITvContractExtras.C_DPTSID,TvpData.DpTsid);
		keyvalues.put (ITvContractExtras.C_DPSID,TvpData.DpServiceId);
		keyvalues.put (ITvContractExtras.C_TPID,TvpData.Tpid);
		keyvalues.put (ITvContractExtras.C_POLARIZATION,TvpData.Polarization);
		keyvalues.put (ITvContractExtras.C_PACKAGEGROUP,TvpData.PackageGroup);
		keyvalues.put (ITvContractExtras.C_LNBNUMBER,TvpData.LnbNumber);

		
		keyvalues.put (ITvContractExtras.C_DATETIMESTAMP,TvpData.DateStamp);
		keyvalues.put (ITvContractExtras.C_PMTPID,TvpData.PmtPid);
		keyvalues.put (ITvContractExtras.C_SECONDARY_AUDIOPID,TvpData.SecAudioPid);
		keyvalues.put (ITvContractExtras.C_FREECIMODE,TvpData.FreeCiMode);
		keyvalues.put (ITvContractExtras.C_SCRAMBLED,TvpData.ScramblingStatus);
		keyvalues.put (ITvContractExtras.C_SECONDARY_AUDIOSTREAMTYPE,TvpData.SecAudioStreamType);
		keyvalues.put (ITvContractExtras.C_USEROVERRULEDCHANNELNAME,TvpData.UserModifiedName);
		keyvalues.put (ITvContractExtras.C_MATCH_BRANDID,TvpData.MatchBrandFlag);
		keyvalues.put (ITvContractExtras.C_BRANDIDS,TvpData.BrandIds); // int array
		keyvalues.put (ITvContractExtras.C_HBBTVON,TvpData.HbbTvOption);
		keyvalues.put (ITvContractExtras.C_PARENTAL_RATING,TvpData.ParentalRating);
		keyvalues.put (ITvContractExtras.C_SERVICEIDENTIFIER,TvpData.ServiceIdentifier);
		keyvalues.put (ITvContractExtras.C_LOGOID,TvpData.LogoURL);

		keyvalues.put (ITvContractExtras.C_INSTALLER_BLOB,FormBlobPrivateData(TvpData,CurrentVersion));
	

		try {
			BlobData = keyvalues.getBlob();
		} catch (Exception e) {
			Log.e(TAG, "Error in FormBlobData  " + e);
		}
		return BlobData;
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
		SatInstallerTvProviderData          TvpData;
		int  SATELLITE_MEDIUM_BASE = 2;
		int index, CurrentVersion = 0; /*reset version for auto installation*/
		
		public void run() {
			if( RecordsInserted < NoOfRecords) { 
				
				if((NoOfRecords-RecordsInserted) < InsertStep) {
					InsertStep = (NoOfRecords-RecordsInserted);
				}

				ContentValues []val=new ContentValues[InsertStep];                                                   

				for (int Loop = 0; Loop < InsertStep; Loop++) {
					TvpData = satInst.GetTvProviderBlobDataByIndex (index,DATA_ALL_TABLE);
					index++;

					val[Loop] = new ContentValues();

					//val[Loop].put (Channels.COLUMN_PACKAGE_NAME,1); /* TvProvider will fill this up */
					val[Loop].put (Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService"); /* Check with Mounesh/Pavan what to fill here */
					val[Loop].put (Channels.COLUMN_TYPE,MapDecoderType(TvpData.DecoderType));
					val[Loop].put (Channels.COLUMN_SERVICE_TYPE,MapServiceType(TvpData.ServiceType));
					val[Loop].put (Channels.COLUMN_NETWORK_AFFILIATION , (TvpData.NewPreset == 1) ? "New" : "");
					val[Loop].put (Channels.COLUMN_ORIGINAL_NETWORK_ID,TvpData.OriginalNetworkId);
					val[Loop].put (Channels.COLUMN_TRANSPORT_STREAM_ID,TvpData.Tsid);
					val[Loop].put (Channels.COLUMN_SERVICE_ID,TvpData.ServiceId);
					val[Loop].put (Channels.COLUMN_DISPLAY_NUMBER,TvpData.PresetNumber);
					val[Loop].put (Channels.COLUMN_DISPLAY_NAME,TvpData.ChannelName);
					val[Loop].put (Channels.COLUMN_DESCRIPTION,((TvpData.ScramblingStatus== 1) ? "Scrambled" :"")); /* See if we can put medium information here */
					val[Loop].put (Channels.COLUMN_BROWSABLE,((TvpData.SystemHidden != 0)?0:1));
					val[Loop].put (Channels.COLUMN_SEARCHABLE,TvpData.NumericSelect);
					val[Loop].put (Channels.COLUMN_LOCKED,TvpData.ChannelLock);
					val[Loop].put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,FormBlobData(TvpData,CurrentVersion));
					val[Loop].put (Channels.COLUMN_VERSION_NUMBER,(SATELLITE_MEDIUM_BASE+TvpData.LnbNumber));

				}
				Log.d (TAG, "Going to do bulk insert of Satellite table ");
				ctx.getContentResolver().bulkInsert(TvContract.Channels.CONTENT_URI ,val);
				Log.d (TAG, "Insertion done for records " + InsertStep);
				RecordsInserted = (RecordsInserted + InsertStep);
				looperThread.mHandler.postDelayed(new divideTask(RecordsInserted,NoOfRecords,InsertStep,index),200);
			}
			else {
				PopulateTvContentProvider();
				mUpdateDatabaseVersion(true);
                sync_IDToMW ();
				ntf.notifyAllObservers(EventIDs.COMMIT_TVPROVIDER_FINISHED,"");
			}
		}
	}
	
	
	public void mPopulateTvProvider () {

		int           NoOfRecords = 0, Loop = 0, RecordsInserted = 0, InsertStep = 400, index = 0;
		SatInstallerTvProviderData          TvpData;
		int                           SATELLITE_MEDIUM_BASE          =2;
		/* Read entries one by one and populate to TVProvider */
		//Uri InsertUri= Uri.parse("content://" + TvContract.AUTHORITY + "/"+Channels.CONTENT_TYPE);

		NoOfRecords = satInst.GetNumberOfDatabaseRecords (DATA_ALL_TABLE);
		Log.d(TAG, "NoOfRecords" + NoOfRecords);
		//InsertStep = NoOfRecords;
		if (NoOfRecords != 0)
		{
			looperThread.mHandler.post(new divideTask(RecordsInserted,NoOfRecords,InsertStep,0));
		} else {
			registerTvProviderContentObservers();
			ntf.notifyAllObservers(EventIDs.COMMIT_TVPROVIDER_FINISHED,"");
		}

	}

	private void mUpdateDatabaseVersion(boolean ForceVersionUpdate) {
		int	CurrentVersion = m_settings.getInt(TvSettingsConstants.INSTSETTINGSSATCHANNELTABLEVERSION, 0, 0); 
		if (ForceVersionUpdate) {
			CurrentVersion++;
			Log.d(TAG, "Auto Installation. New Version updated to DB is " + CurrentVersion);
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSSATCHANNELTABLEVERSION, 0, CurrentVersion); 
		}
		else {
			if (IsMajorVersionChange) {
				CurrentVersion++;
				Log.d(TAG, "Major version update. New Version updated to DB is " + CurrentVersion);
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSSATCHANNELTABLEVERSION, 0, CurrentVersion); 
			}
		}
	}



	private class LooperThread extends Thread {
		public Handler mHandler;
		boolean handlerCreated = false;
		public void run() {
			//Log.d(TAG,"Looper thread creation");
			synchronized (this)
			{
				Looper.prepare();
				mHandler = new Handler() ;
				handlerCreated = true;
				//Log.d(TAG,"notifying... after handler creation");
				notify();

			}
			Looper.loop();
		}

		public boolean getLooperThreadHandlerStatus()
		{
			return handlerCreated;
		}
	};	


	
		
	public void commitDatabaseToTvProvider(int insType) {
		final int innerinsType = insType;
			looperThread.mHandler.post(new Runnable(){
		    public void run()
		    {
				int 	NoOfRecords = 0, Loop = 0, RowsDeleted = 0;
				SatInstallerTvProviderData	TvpData;
				int		SATELLITE_MEDIUM_BASE	=2;
				
				/* In Auto Installation use case clear existing database and add everything fresh */
				if (INSTALL_TYPE_AUTO == innerinsType) {

					unregisterTvProviderContentObservers();
					
					/* Perform clearing of existing database */
					for (Loop =0; Loop < 4; Loop++) {
						String	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?";
						String[]	mselectionargs=new String[]{String.valueOf((SATELLITE_MEDIUM_BASE+Loop))};
						RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection,mselectionargs);
						Log.d(TAG,"Satelite: RowsDeleted "+RowsDeleted+"For LnbNumber" + Loop);
					}
					
					/* Read entries one by one and populate to TVProvider */
					mPopulateTvProvider ();

				}
				else if(INSTALL_TYPE_UPDATE == innerinsType) {
					unregisterTvProviderContentObservers();
					mSyncTvProvider();
					PopulateTvContentProvider();
					mUpdateDatabaseVersion(false);
                    sync_IDToMW ();
					registerTvProviderContentObservers();
					ntf.notifyAllObservers(EventIDs.COMMIT_TVPROVIDER_FINISHED,"");
				}else if(INSTALL_TYPE_SRT == innerinsType)				
				{	
					Log.d(TAG, "commitDatabaseToTvProvider for SRT");	
					unregisterTvProviderContentObservers();
					mSyncTvProviderforSrtInstall();				
					PopulateTvContentProvider();				
					mUpdateDatabaseVersion(false);           
					sync_IDToMW ();
					registerTvProviderContentObservers();
					ntf.notifyAllObservers(EventIDs.COMMIT_TVPROVIDER_FINISHED,"");			
				}
				else{
					unregisterTvProviderContentObservers();
					mSyncTvProviderforBckInstall();
					mUpdateDatabaseVersion(false);
                    sync_IDToMW ();
					registerTvProviderContentObservers();
					ntf.notifyAllObservers(EventIDs.COMMIT_TVPROVIDER_FINISHED,"");
				}
				
				Log.d(TAG, "commitDatabaseToTvProvider is Done");
				
			}
		});

		
	}

	
	public void mSyncTvProvider() {

		Log.d(TAG, "SyncTvProvider");
		
		int 	NoOfRecords = 0, Loop = 0, Index = 0;
		SatInstallerTvProviderData	TvpData;
		int	DBVersion = 0, CurrentVersion = 0, RowsUpdated = 0, RowsDeleted = 0;
		byte[]	BlobData = null;
		byte[]	PrivateBlobData = null;
		int  SATELLITE_MEDIUM_BASE = 2;
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();

		/*Get Version*/
    	String[] projection = new String[]{Channels.COLUMN_INTERNAL_PROVIDER_DATA};
		String	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?";
		String[]	mselectionargs=new String[]{String.valueOf(SATELLITE_MEDIUM_BASE+0),String.valueOf(SATELLITE_MEDIUM_BASE+1),String.valueOf(SATELLITE_MEDIUM_BASE+2),String.valueOf(SATELLITE_MEDIUM_BASE+3)};

		Cursor SatCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		if(SatCursor != null){
			try{
			while(SatCursor.moveToNext()) { 
				BlobData=SatCursor.getBlob(0);
				break;
			}
			}
            finally{			
			   SatCursor.close();
			   SatCursor=null;
			}
		}

		if(BlobData != null){
			try{
				keyvalues.setBlob(BlobData);
			}
			catch (Exception e) {
				Log.d(TAG, "Exception in setBlob() while reading version" + e);
			}
			PrivateBlobData = keyvalues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);
			privatekeyvalues.setBlob(PrivateBlobData);
			DBVersion = privatekeyvalues.getInt(TvContractPrivate.C_VERSION);
			CurrentVersion = DBVersion + 1;
			Log.d (TAG, "Current version "+CurrentVersion);
			
		}
		else
		{
			Log.d (TAG, "No Records with Satellite Medium ");
			DBVersion = 0;
			CurrentVersion = 0;
		}



		/* Read entries one by one and update/add to TVProvider */
		NoOfRecords = satInst.GetNumberOfDatabaseRecords (DATA_ALL_TABLE);
		Log.d (TAG, "Number of entries "+NoOfRecords);
		ContentValues val=new ContentValues();
		
		for (Loop = 0; Loop < NoOfRecords; Loop++) {
			//Log.d (TAG, " Query For index  "+ Loop);

				
			TvpData = satInst.GetTvProviderBlobDataByIndex (Loop,DATA_ALL_TABLE);
			Log.d(TAG, "ONID" + TvpData.OriginalNetworkId + " TSID" + TvpData.Tsid + " ServiceID" + TvpData.ServiceId + " PresetNbr" + TvpData.PresetNumber+ "Name" + TvpData.ChannelName );
		
			val.put (Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService"); /* Check with Mounesh/Pavan what to fill here */
			val.put (Channels.COLUMN_TYPE,MapDecoderType(TvpData.DecoderType));
			val.put (Channels.COLUMN_SERVICE_TYPE,MapServiceType(TvpData.ServiceType));
			val.put (Channels.COLUMN_NETWORK_AFFILIATION , (TvpData.NewPreset == 1) ? "New" : "");
			val.put (Channels.COLUMN_ORIGINAL_NETWORK_ID,TvpData.OriginalNetworkId);
			val.put (Channels.COLUMN_TRANSPORT_STREAM_ID,TvpData.Tsid);
			val.put (Channels.COLUMN_SERVICE_ID,TvpData.ServiceId);
			val.put (Channels.COLUMN_DISPLAY_NUMBER,TvpData.PresetNumber);
			val.put (Channels.COLUMN_DISPLAY_NAME,TvpData.ChannelName);
			val.put (Channels.COLUMN_DESCRIPTION,((TvpData.ScramblingStatus== 1) ? "Scrambled" :"")); /* See if we can put medium information here */
			val.put (Channels.COLUMN_BROWSABLE, ((TvpData.SystemHidden != 0) ? 0 : 1));
			val.put (Channels.COLUMN_SEARCHABLE,TvpData.NumericSelect);
//			val.put (Channels.COLUMN_LOCKED,TvpData.ChannelLock); /*TODO: update of this column need permission*/
			//Log.d(TAG, "Going to form blob ");
			val.put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,FormBlobData(TvpData,CurrentVersion));
			//Log.d(TAG, "After Blob operations ");
			val.put (Channels.COLUMN_VERSION_NUMBER,(SATELLITE_MEDIUM_BASE+TvpData.LnbNumber));
			


			mselection = Channels._ID +"= ?" + " AND " + Channels.COLUMN_VERSION_NUMBER+"= ?";
			mselectionargs=new String[]{String.valueOf(TvpData.UniqueId),String.valueOf(SATELLITE_MEDIUM_BASE+TvpData.LnbNumber) };

			RowsUpdated = 0;
			RowsUpdated = ctx.getContentResolver().update(TvContract.Channels.CONTENT_URI,val,mselection,mselectionargs);

			if(RowsUpdated == 0){
				//Log.d(TAG, "Preset does not exist, hence inserting new record ");
				ctx.getContentResolver().insert(TvContract.Channels.CONTENT_URI ,val);
			}
			else{
				//Log.d(TAG, "Updated the record ");
			}

		}

		/*Delete old records*/
		projection = new String[] {Channels._ID,Channels.COLUMN_INTERNAL_PROVIDER_DATA,Channels.COLUMN_VERSION_NUMBER};
		mselection=Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?"+" OR "+Channels.COLUMN_VERSION_NUMBER+"= ?";
		mselectionargs=new String[]{String.valueOf(SATELLITE_MEDIUM_BASE+0),String.valueOf(SATELLITE_MEDIUM_BASE+1),String.valueOf(SATELLITE_MEDIUM_BASE+2),String.valueOf(SATELLITE_MEDIUM_BASE+3)};

		SatCursor = null;
		SatCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		if(SatCursor != null){
		   try
		   {
			while(SatCursor.moveToNext()) { 
				BlobData=SatCursor.getBlob(1);
				
				if(BlobData != null){
					try{
						keyvalues.setBlob(BlobData);
					}
					catch (Exception e) {
						Log.d(TAG, "Exception in setBlob() while deleting old records" + e);
					}			
					
					PrivateBlobData = keyvalues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);
					privatekeyvalues.setBlob(PrivateBlobData);

					int Version = privatekeyvalues.getInt(TvContractPrivate.C_VERSION);
					int ColumnVersion = SatCursor.getInt(2);

					/*Delete if version is not matching*/
					if(Version != CurrentVersion){
						/*Delete the record*/
						mselection = Channels._ID+"= ?" + "AND " + Channels.COLUMN_VERSION_NUMBER+"= ?";
						mselectionargs=new String[]{String.valueOf(SatCursor.getInt(0)),String.valueOf(ColumnVersion) };
						RowsDeleted = 0;
						RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection,mselectionargs);
						if(RowsDeleted !=0){
							Log.d(TAG,"Deleted Preset "+ SatCursor.getInt(0));
						}
					}
				}
			}
		   }catch (Exception e) {
				Log.d(TAG, " mSyncTvProvider() while Cusor Move" + e);
		   }	
			
		   
		   finally
		   {
			  SatCursor.close();
			  SatCursor=null;
		   }
		}
	}

	public void mSyncTvProviderforSrtInstall(){
		
		int  NoOfRecords = 0, count = 0, Loop = 0, DBVersion = 0, onid = 0, tsid = 0, lnbNumber = 0,mTpId = 0;
		byte[]	BlobData = null;
		int uniqueId;
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		int  SATELLITE_MEDIUM_BASE = 2;
		int	CurrentVersion = 0, RowsDeleted = 0,index = 0,cachedTPID = 0;
		SatInstallerTvProviderData TvpData;
		
		int LnbNumber = GetManualInstallLNB();
		int presetNumber = satInst.getDeletedPresetNumber();
	
		
		String[] projection = new String[] {Channels.COLUMN_ORIGINAL_NETWORK_ID,Channels.COLUMN_TRANSPORT_STREAM_ID,Channels.COLUMN_INTERNAL_PROVIDER_DATA};
		String mselection = Channels.COLUMN_DISPLAY_NUMBER + "= ?" + " AND " + Channels.COLUMN_VERSION_NUMBER+"= ?";
		String[] mselectionargs=new String[]{String.valueOf(presetNumber),String.valueOf(SATELLITE_MEDIUM_BASE+LnbNumber)};
		
		Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
        try
		{
		    if(cursor != null && cursor.getCount() > 0){
			   cursor.moveToFirst();
			   onid = cursor.getInt(0);
			   tsid = cursor.getInt(1);
			   BlobData = cursor.getBlob(2);
			
			   if(BlobData != null){
					try{
						keyvalues.setBlob(BlobData);
					}
					catch (Exception e) {
						Log.d(TAG, "Exception in setBlob() while reading version" + e);
					}			
					cachedTPID = keyvalues.getInt(ITvContractExtras.C_TPID);
			   }
			  //Log.d(TAG, "mSyncTvProviderforSrtInstall" + "Onid= "  + onid + "TsId = " +  tsid + "TPID = " + cachedTPID);
		    } else {
			   Log.d(TAG, "mSyncTvProviderforSrtInstall Cursor Count is NULL");
		    }
		}
        finally
		{
		    if(cursor != null) {
			   cursor.close();
			}
		}


		cursor = null;
		projection = new String[] {Channels._ID, Channels.COLUMN_INTERNAL_PROVIDER_DATA};
		mselection = Channels.COLUMN_ORIGINAL_NETWORK_ID + "= ?" + " AND " + Channels.COLUMN_TRANSPORT_STREAM_ID + "= ?" + " AND " + Channels.COLUMN_VERSION_NUMBER+"= ?";
		mselectionargs=new String[]{String.valueOf(onid),String.valueOf(tsid),String.valueOf(SATELLITE_MEDIUM_BASE+LnbNumber)};
		
		cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

		if(cursor != null)
			Log.d(TAG, " mSyncTvProviderforSrtInstall GETCOUNT " + cursor.getCount());
		
		try{
		if(cursor != null)
		{
			while(cursor.moveToNext())
			{
				uniqueId = cursor.getInt(0);
				BlobData = cursor.getBlob(1);
				if(BlobData != null){
					try{
						keyvalues.setBlob(BlobData);
					}
					catch (Exception e) {
						Log.d(TAG, "Exception in setBlob() while reading version" + e);
					}			
					mTpId = keyvalues.getInt(ITvContractExtras.C_TPID);
					//Log.d(TAG, "  TPID of TV.db " + mTpId);

					if(mTpId == cachedTPID)
					{						
						/*Delete the record*/
						
						mselection = Channels._ID +"= ?";
						mselectionargs=new String[]{String.valueOf(uniqueId)};
						RowsDeleted = 0;
						RowsDeleted = ctx.getContentResolver().delete(TvContract.Channels.CONTENT_URI,mselection,mselectionargs);
						if(RowsDeleted !=0){
							Log.d(TAG,"Deleted Preset "+ cursor.getInt(0));
						}			
					}
				}
		
			}
			
		}
		}
		finally{
		   if(cursor != null) {
			  cursor.close();
			  cursor=null;
		   }
		}
		NoOfRecords = satInst.GetNumberOfDatabaseRecords (DATA_ALL_TABLE);
		//Log.d(TAG," mSyncTvProviderforSrtInstall NoOfRecords " + NoOfRecords);
		ContentValues val = new ContentValues();
		for (Loop = 0; Loop < NoOfRecords; Loop++) {
			TvpData = satInst.GetTvProviderBlobDataByIndex (Loop,DATA_ALL_TABLE);
		
			val.put (Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService"); 
			val.put (Channels.COLUMN_TYPE,MapDecoderType(TvpData.DecoderType));
			val.put (Channels.COLUMN_SERVICE_TYPE,MapServiceType(TvpData.ServiceType));
			val.put (Channels.COLUMN_NETWORK_AFFILIATION , (TvpData.NewPreset == 1) ? "New" : "");
			val.put (Channels.COLUMN_ORIGINAL_NETWORK_ID,TvpData.OriginalNetworkId);
			val.put (Channels.COLUMN_TRANSPORT_STREAM_ID,TvpData.Tsid);
			val.put (Channels.COLUMN_SERVICE_ID,TvpData.ServiceId);
			val.put (Channels.COLUMN_DISPLAY_NUMBER,TvpData.PresetNumber);
			val.put (Channels.COLUMN_DISPLAY_NAME,TvpData.ChannelName);
			Log.d (TAG,"OriginalNetworkId" + TvpData.OriginalNetworkId + " TSID " + TvpData.Tsid + "DISPLAYNAME " + TvpData.ChannelName);
			val.put (Channels.COLUMN_DESCRIPTION,((TvpData.ScramblingStatus== 1) ? "Scrambled" :"")); 
			val.put (Channels.COLUMN_BROWSABLE,((TvpData.SystemHidden != 0)?0:1));
			val.put (Channels.COLUMN_SEARCHABLE,TvpData.NumericSelect);
			val.put (Channels.COLUMN_LOCKED,TvpData.ChannelLock);
			val.put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,FormBlobData(TvpData,CurrentVersion));
			val.put (Channels.COLUMN_VERSION_NUMBER,(SATELLITE_MEDIUM_BASE+TvpData.LnbNumber));	

			ctx.getContentResolver().insert(TvContract.Channels.CONTENT_URI ,val);
		}
			
	}
	

	public void mSyncTvProviderforBckInstall(){

		Log.d(TAG, "mSyncTvProviderforBckInstall");
		int RowsUpdated = 0, NoOfRecords = 0, count = 0, loop = 0, DBVersion = 0, onid = 0, tsid = 0, lnbNumber = 0;
		byte[]	BlobData = null;
		int  SATELLITE_MEDIUM_BASE = 2;
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		SatInstallerTvProviderData TvpData;

		
		/*Get Data from TVProvider*/
		
		int channel = m_settings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2, 0, 0);
		
		String[] projection = new String[] {Channels.COLUMN_ORIGINAL_NETWORK_ID,Channels.COLUMN_TRANSPORT_STREAM_ID,Channels.COLUMN_VERSION_NUMBER,Channels.COLUMN_INTERNAL_PROVIDER_DATA};
		String mselection = Channels._ID+"= ?";
		String[] mselectionargs=new String[]{String.valueOf(channel)};
		
		
		Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
			
		if(cursor != null){
			try
			{
			   cursor.moveToFirst();
			   onid = cursor.getInt(0);
			   tsid = cursor.getInt(1);
			   lnbNumber = cursor.getInt(2);
			   BlobData = cursor.getBlob(3);
			}
			finally
			{	
			    cursor.close();
			    cursor=null;  
			}
			if(BlobData != null){
				try{
					keyvalues.setBlob(BlobData);
				}
				catch (Exception e) {
					Log.d(TAG, "Exception in setBlob() while reading version" + e);
				}			
				DBVersion = keyvalues.getInt(TvContractPrivate.C_VERSION);
				
			}
			else
			{
				Log.d (TAG, "No Records with Satellite Medium ");
				DBVersion = 0;
			}

			Log.d (TAG, "updating TS with ONID: " + onid + " TSID: " + tsid + " LNB: " + lnbNumber);

			/* Read entries one by one and update/add to TVProvider */
			NoOfRecords = satInst.GetNumberOfDatabaseRecords (DATA_ALL_TABLE);
			Log.d (TAG, "Number of entries "+NoOfRecords);
			
			ContentValues val=new ContentValues();
			for (loop = 0; loop < NoOfRecords; loop++) {
				Log.d (TAG, " Query For index  "+ loop);

								
				TvpData = satInst.GetTvProviderBlobDataByIndex (loop,DATA_ALL_TABLE);

				if((onid == TvpData.OriginalNetworkId) && (tsid == TvpData.Tsid) && (lnbNumber == (SATELLITE_MEDIUM_BASE+TvpData.LnbNumber))){

					Log.d(TAG, "ONID" + TvpData.OriginalNetworkId + " TSID" + TvpData.Tsid + " ServiceID" + TvpData.ServiceId + " PresetNbr" + TvpData.PresetNumber + " UniqueID: " + TvpData.UniqueId);
				
					val.put (Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService"); /* Check with Mounesh/Pavan what to fill here */
					val.put (Channels.COLUMN_TYPE,MapDecoderType(TvpData.DecoderType));
					val.put (Channels.COLUMN_SERVICE_TYPE,MapServiceType(TvpData.ServiceType));
					val.put (Channels.COLUMN_NETWORK_AFFILIATION , (TvpData.NewPreset == 1) ? "New" : "");
					val.put (Channels.COLUMN_ORIGINAL_NETWORK_ID,TvpData.OriginalNetworkId);
					val.put (Channels.COLUMN_TRANSPORT_STREAM_ID,TvpData.Tsid);
					val.put (Channels.COLUMN_SERVICE_ID,TvpData.ServiceId);
					val.put (Channels.COLUMN_DISPLAY_NUMBER,TvpData.PresetNumber);
					val.put (Channels.COLUMN_DISPLAY_NAME,TvpData.ChannelName);
					val.put (Channels.COLUMN_DESCRIPTION,((TvpData.ScramblingStatus== 1) ? "Scrambled" :"")); /* See if we can put medium information here */
					val.put (Channels.COLUMN_BROWSABLE,((TvpData.SystemHidden != 0)?0:1));
					val.put (Channels.COLUMN_SEARCHABLE,TvpData.NumericSelect);
					//val.put (Channels.COLUMN_LOCKED,TvpData.ChannelLock); /*TODO: update of this column need permission*/
					val.put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,FormBlobData(TvpData,DBVersion));
					val.put (Channels.COLUMN_VERSION_NUMBER,(SATELLITE_MEDIUM_BASE+TvpData.LnbNumber));

					mselection = Channels._ID +"= ?" + " AND " + Channels.COLUMN_VERSION_NUMBER+"= ?";
					mselectionargs=new String[]{String.valueOf(TvpData.UniqueId),String.valueOf(SATELLITE_MEDIUM_BASE+TvpData.LnbNumber)};

					RowsUpdated = 0;
					RowsUpdated = ctx.getContentResolver().update(TvContract.Channels.CONTENT_URI,val,mselection,mselectionargs);

					if(RowsUpdated == 0){
						Log.d(TAG, "Preset does not exist, Preset added in background installation !!! ");
					}
					else{
						Log.d(TAG, "Updated the record ");
					}
				}

			}
			
		}
		
	}

	
	public void PopulateTvContentProvider(){

		Log.d(TAG, "PopulateTvContentProvider");

		int           NoOfRecords = 0, Loop = 0, RecordsInserted = 0, InsertStep = 100, index = 0;
		int	packageMux = 0;
		SatInstallerTvProviderData TvpData;

		/* Perform clearing of existing database */
		String	mselection = null;
		String[]	mselectionargs = null;
		int RowsDeleted = ctx.getContentResolver().delete(IFrequencyListContract.ISATFrequencyMap.CONTENT_URI,mselection,mselectionargs);

		Log.d(TAG,"PopulateTvContentProvider: RowsDeleted "+RowsDeleted);
		
		NoOfRecords = satInst.GetNumberOfDatabaseRecords(DATA_TS_TABLE);
		

		for(RecordsInserted = 0; RecordsInserted < NoOfRecords; RecordsInserted = (RecordsInserted + InsertStep)){

			if((NoOfRecords-RecordsInserted) < InsertStep) {
				InsertStep = (NoOfRecords-RecordsInserted);
			}
			
			ContentValues []val=new ContentValues[InsertStep];													 
			
			for (Loop = 0; Loop < InsertStep; Loop++) {
				TvpData = satInst.GetTvProviderBlobDataByIndex (index,DATA_TS_TABLE);
				index++;
				
				val[Loop] = new ContentValues();
			
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_FREQUENCY,TvpData.Frequency); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_SYMBOLRATE,TvpData.SymbolRate); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_ORIGINALNETWORKID,TvpData.OriginalNetworkId); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_TSID,TvpData.Tsid); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_MODULATIONTYPE,TvpData.ModulationType); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_BANDWIDTH,TvpData.Bandwidth); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_BARKERMUX,TvpData.BarkerMux); 
				if(TvpData.SDSDFrequency == 0){
					packageMux = (int)IFrequencyListContract.PackageMux.NON_PACKAGE_MUX.ordinal();
				}
				else{
					packageMux = (int)IFrequencyListContract.PackageMux.PACKAGE_ONLY_MUX.ordinal();
				}
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_PACKAGE_MUX,packageMux); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_LNBNUMBER,TvpData.LnbNumber); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_POLARIZATION,TvpData.Polarization); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_CODERATE,0); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_MODULATIONSYSTEM,TvpData.DecoderType); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_ROLLOFFFACTOR,TvpData.RollOff); 
				val[Loop].put (IFrequencyListContract.ISATFrequencyMap.COLUMN_FECINNER,TvpData.FECInner); 
			
			}
			//Log.d (TAG, "Going to do bulk insert of SATFrequencyMap ");
			ctx.getContentResolver().bulkInsert(IFrequencyListContract.ISATFrequencyMap.CONTENT_URI ,val);
			//Log.d (TAG, "Insertion done for records " + InsertStep);
		}
		
	}


	public void LoadTvProviderData(){

		//Log.d(TAG, "LoadTvProviderData");

		SatInstallerTvProviderData TvpData = new SatInstallerTvProviderData();
		SatInstallerTvProviderData Temp = new SatInstallerTvProviderData();		
		byte[]	BlobData = null;
		int  count = 0, i = 0;
		String NewPreset;
		
		/*Clear the RAM copy in MW*/
		satInst.PopulateMW(Temp,1);

		for (i = 0; i < MAX_LNB_NUMBER; i++)
		{
			/*Get Data from TVProvider*/
			String[] projection = new String[] {Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_TYPE, Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_DISPLAY_NUMBER, Channels.COLUMN_DISPLAY_NAME, Channels.COLUMN_BROWSABLE, Channels.COLUMN_INTERNAL_PROVIDER_DATA, Channels.COLUMN_VERSION_NUMBER, Channels.COLUMN_LOCKED, Channels._ID, Channels.COLUMN_NETWORK_AFFILIATION};
			String	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?";
			String[]	mselectionargs=new String[]{String.valueOf(TVPROVIDER_SATELLITE_MEDIUM_BASE+i)};
			
			Cursor SatCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
			if(SatCursor != null){
				count = SatCursor.getCount();
			}
			Log.d(TAG, "LoadTvProviderData: Number of channles in db " + count + " with LNB " + i); 

			if(SatCursor != null){
				try{
				while(SatCursor.moveToNext()) { 
					//Log.d(TAG, "Adding Data to MW");
					TvpData.DecoderType = ConvertDecoderType(SatCursor.getString(0)); // TODO: use this once this value is filled in MW
					TvpData.ServiceType= SatCursor.getInt(1);
					TvpData.OriginalNetworkId= SatCursor.getInt(2);
					TvpData.Tsid= SatCursor.getInt(3);
					TvpData.ServiceId= SatCursor.getInt(4);
					TvpData.PresetNumber= SatCursor.getInt(5);
					TvpData.ChannelName= SatCursor.getString(6);
					TvpData.NumericSelect = SatCursor.getInt(7);
					TvpData.ChannelLock= SatCursor.getInt(10);
					TvpData.UniqueId = SatCursor.getInt(11);
					NewPreset = SatCursor.getString(12);
					try {
						TvpData.NewPreset = (NewPreset.equalsIgnoreCase("New") ? 1 : 0);
					}
					catch (Exception e)
					{
					}
					BlobData = SatCursor.getBlob(8);
					
					AddMWRecord(TvpData,BlobData);
				}
				}
                finally{				
				   SatCursor.close();
				   SatCursor=null;
				}
			}
		}
		Log.d(TAG, "LoadTvProviderData Completed");
	}


	public void AddMWRecord(SatInstallerTvProviderData TvpData,byte[] BlobData)
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
		TvpData.NumericSelect = keyvalues.getInt (ITvContractExtras.C_NUMERICSELECT);
		TvpData.ScrambledStatus = keyvalues.getInt (ITvContractExtras.C_SCRAMBLED);
		TvpData.IntHbbTvOption = keyvalues.getInt (ITvContractExtras.C_HBBTVON);
		TvpData.UserHidden = keyvalues.getInt (ITvContractExtras.C_USERHIDDEN);
		//TvpData.NewPreset = keyvalues.getInt (ITvContractExtras.C_NEWPRESET);
		TvpData.AudioPid = keyvalues.getInt (ITvContractExtras.C_AUDIOPID);
		TvpData.VideoPid = keyvalues.getInt (ITvContractExtras.C_VIDEOPID);
		TvpData.PcrPid = keyvalues.getInt (ITvContractExtras.C_PCRPID);
		TvpData.VideoStreamType = keyvalues.getInt (ITvContractExtras.C_VIDEOSTREAMTYPE);
		TvpData.AudioStreamType = keyvalues.getInt (ITvContractExtras.C_AUDIOSTREAMTYPE);
		TvpData.NetworkId = keyvalues.getInt (ITvContractExtras.C_NetworkId);
		TvpData.TextSubTitlePage = keyvalues.getInt (ITvContractExtras.C_TXTSUBPAGE);
		TvpData.SAP = keyvalues.getInt (ITvContractExtras.C_SAP);
		TvpData.PreferredStereo = keyvalues.getInt (ITvContractExtras.C_PreferredStereo);
		TvpData.LCN = keyvalues.getInt (ITvContractExtras.C_LCN);
		TvpData.DpTsid = keyvalues.getInt (ITvContractExtras.C_DPTSID);
		TvpData.DpServiceId = keyvalues.getInt (ITvContractExtras.C_DPSID);
		TvpData.Tpid = keyvalues.getInt (ITvContractExtras.C_TPID);
		TvpData.Polarization = keyvalues.getInt (ITvContractExtras.C_POLARIZATION);
		TvpData.PackageGroup = keyvalues.getInt (ITvContractExtras.C_PACKAGEGROUP);
		TvpData.LnbNumber = keyvalues.getInt (ITvContractExtras.C_LNBNUMBER);

		
		TvpData.DateStamp = keyvalues.getInt (ITvContractExtras.C_DATETIMESTAMP);
		TvpData.PmtPid = keyvalues.getInt (ITvContractExtras.C_PMTPID);
		TvpData.SecAudioPid = keyvalues.getInt (ITvContractExtras.C_SECONDARY_AUDIOPID);
		TvpData.FreeCiMode = keyvalues.getInt (ITvContractExtras.C_FREECIMODE);
		TvpData.ScramblingStatus = keyvalues.getInt (ITvContractExtras.C_SCRAMBLED);
		TvpData.SecAudioStreamType = keyvalues.getInt (ITvContractExtras.C_SECONDARY_AUDIOSTREAMTYPE);
		TvpData.UserModifiedName = keyvalues.getInt (ITvContractExtras.C_USEROVERRULEDCHANNELNAME);
		TvpData.MatchBrandFlag = keyvalues.getInt (ITvContractExtras.C_MATCH_BRANDID);
		TvpData.BrandIds = keyvalues.getIntArray (ITvContractExtras.C_BRANDIDS);		
		TvpData.HbbTvOption = keyvalues.getInt (ITvContractExtras.C_HBBTVON);
		TvpData.ParentalRating = keyvalues.getInt (ITvContractExtras.C_PARENTAL_RATING);
		TvpData.ServiceIdentifier = keyvalues.getInt (ITvContractExtras.C_SERVICEIDENTIFIER);
		TvpData.LogoURL= keyvalues.getInt (ITvContractExtras.C_LOGOID);

		
		/*Get Private data*/

		privateBlobData = keyvalues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);

		try{
			privatekeyvalues.setBlob(privateBlobData);
		}
		catch (Exception e) {
			Log.d(TAG, "Exception in setBlob() in AddMWRecord for Private Data" + e);
		}			


		/*Private data*/
		TvpData.FavoriteNumber = privatekeyvalues.getInt (TvContractPrivate.C_FAVOURITENUMBER);
		TvpData.VisibleService = privatekeyvalues.getInt (TvContractPrivate.C_VISIBLESERVICE);
		TvpData.LnbType = privatekeyvalues.getInt (TvContractPrivate.C_LNBTYPE);
		TvpData.SatelliteId = privatekeyvalues.getInt (TvContractPrivate.C_SATID);
		TvpData.OrbitalPosition = privatekeyvalues.getInt (TvContractPrivate.C_ORBITALPOSITION);
		TvpData.SignalStrength = privatekeyvalues.getInt (TvContractPrivate.C_SIGNALSTRENGTH);
		TvpData.SignalQuality = privatekeyvalues.getInt (TvContractPrivate.C_SIGNALQUALITY);
		TvpData.AppsCookie = privatekeyvalues.getInt (TvContractPrivate.C_APPSCOOCKIE);
		TvpData.SDTVersion = privatekeyvalues.getInt (TvContractPrivate.C_SDTVERSION);
		TvpData.NITVersion = privatekeyvalues.getInt (TvContractPrivate.C_NITVERSION);
		TvpData.LowPrioLCN = privatekeyvalues.getInt (TvContractPrivate.C_LOWPRIOLCN);
		TvpData.LowPrioVisibleService = privatekeyvalues.getInt (TvContractPrivate.C_LOWPRIOVISIBLESERVICE);
		TvpData.VideoDescPresent = privatekeyvalues.getInt (TvContractPrivate.C_VIDEODESCPRESENT);
		TvpData.DuplicateSvc = privatekeyvalues.getInt (TvContractPrivate.C_DUPLICATESERVICE);
		TvpData.ServiceListVersion = privatekeyvalues.getInt (TvContractPrivate.C_SERVICELISTVERSION);
		TvpData.UserInstalled = privatekeyvalues.getInt (TvContractPrivate.C_USERINSTALLED);
		TvpData.DvbType = privatekeyvalues.getInt (TvContractPrivate.C_DVBTYPE);
		TvpData.InstalledSatelliteNumber = privatekeyvalues.getInt (TvContractPrivate.C_INSTALLEDSATNUMBER);
		TvpData.NewChannel = privatekeyvalues.getInt (TvContractPrivate.C_NEWCHANNEL); 	
		TvpData.SDSDFrequency = privatekeyvalues.getInt (TvContractPrivate.C_SDSDFREQUENCY);
		TvpData.CountryCode = privatekeyvalues.getInt (TvContractPrivate.C_COUNTRYCODE);
		TvpData.HDSimulcastRepOnId = privatekeyvalues.getInt (TvContractPrivate.C_HDSIMULCASTREPONID);
		TvpData.HDSimulcastRepTsId = privatekeyvalues.getInt (TvContractPrivate.C_HDSIMULCASTREPTSID);
		TvpData.HDSimulcastRepSvcId = privatekeyvalues.getInt (TvContractPrivate.C_HDSIMULCASTREPSVCID);
	
		TvpData.ASignalStrength = privatekeyvalues.getInt (TvContractPrivate.C_ASIGNALSTRENGTH);
		TvpData.VSignalStrength = privatekeyvalues.getInt (TvContractPrivate.C_VSIGNALSTRENGTH);
		TvpData.QSignalStrength = privatekeyvalues.getInt (TvContractPrivate.C_QSIGNALSTRENGTH);
		TvpData.ChannelInformation = privatekeyvalues.getInt (TvContractPrivate.C_CHANNELINFORMATION);
		TvpData.CodeRate = privatekeyvalues.getInt (TvContractPrivate.C_CODERATE);
		TvpData.PtcListVersion = privatekeyvalues.getInt (TvContractPrivate.C_PTCLISTVERSION);
		TvpData.TSVersion = privatekeyvalues.getInt (TvContractPrivate.C_TSVERSION);
		TvpData.PlpId = privatekeyvalues.getInt (TvContractPrivate.C_PLPID);
		TvpData.BarkerMux = privatekeyvalues.getInt (TvContractPrivate.C_BARKERMUX);
		TvpData.NumBrandIds = privatekeyvalues.getInt (TvContractPrivate.C_NUMBRANDIDS);		
		TvpData.FECInner = privatekeyvalues.getInt (TvContractPrivate.C_FECINNER); 	
		TvpData.RollOff = privatekeyvalues.getInt (TvContractPrivate.C_ROLLOFF);		

		TvpData.SatelliteName = privatekeyvalues.getString (TvContractPrivate.C_SATELLITENAME);		
		TvpData.MultipleVisibleService = privatekeyvalues.getIntArray (TvContractPrivate.C_MULTIPLEVISIBLESERVICE);		
		TvpData.MultipleLCN = privatekeyvalues.getIntArray (TvContractPrivate.C_MULTIPLELCN);		
		TvpData.MultiplePreset = privatekeyvalues.getIntArray (TvContractPrivate.C_MULTIPLEPRESET);		
		TvpData.MultipleFavorite = privatekeyvalues.getIntArray (TvContractPrivate.C_MULTIPLEFAVORITE);		
		TvpData.ServiceType= privatekeyvalues.getInt (TvContractPrivate.C_SERVICETYPE);

		satInst.PopulateMW (TvpData, 0);
	}
	

	public void sync_IDToMW () {

		Log.d(TAG, "sync_IDToMW");

		SatInstallerTvProviderData tvpData = new SatInstallerTvProviderData ();		
		byte[] blobData = null;
		int  numOfRecords = 0, loopCount = 0;
		
		for (loopCount = 0; loopCount < MAX_LNB_NUMBER; ++loopCount)
		{
			// Get Data from TVProvider
			String[] projection = new String[] {Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_TYPE, Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_DISPLAY_NUMBER, Channels.COLUMN_INTERNAL_PROVIDER_DATA, Channels._ID};
			String mselection = Channels.COLUMN_VERSION_NUMBER+"= ?";
			String[] mselectionargs = new String[] {String.valueOf (TVPROVIDER_SATELLITE_MEDIUM_BASE + loopCount) };
			
			Cursor SatCursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
			if(SatCursor != null){
				numOfRecords = SatCursor.getCount();
			}
			Log.d(TAG, "sync_IDToMW: Number of channles in db " + numOfRecords + " with LNB " + loopCount); 

			if(SatCursor != null){
				try
				{
				while (SatCursor.moveToNext()) { 					
					tvpData.DecoderType = 0;
					tvpData.OriginalNetworkId= SatCursor.getInt(2);
					tvpData.Tsid= SatCursor.getInt(3);
					tvpData.ServiceId= SatCursor.getInt(4);
					tvpData.PresetNumber= SatCursor.getInt(5);
					tvpData.UniqueId = SatCursor.getInt(7);
					blobData = SatCursor.getBlob(6);
					populate_IDSyncKeysFromBlobData (tvpData, blobData);
                    satInst.syncUniqueIdToMW(tvpData);
				}
				}
                finally
				{				
				   SatCursor.close();
				   SatCursor=null;
				}
			}
		}
       }

    public void populate_IDSyncKeysFromBlobData (SatInstallerTvProviderData tvpData, byte[] blobData)
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
		
		tvpData.Tpid = keyValues.getInt (ITvContractExtras.C_TPID);
		
		privateBlobData = keyValues.getByteArray(ITvContractExtras.C_INSTALLER_BLOB);

		try{
			privatekeyvalues.setBlob(privateBlobData);
		}
		catch (Exception e) {
			Log.d(TAG, "Exception in setBlob() in AddMWRecord for Private Data" + e);
		}

		tvpData.MultiplePreset = privatekeyvalues.getIntArray(TvContractPrivate.C_MULTIPLEPRESET);
	}

	
	/*** TVPROVIDER IMPLEMENTATION END ***/
	
	
	public void commitToCTVSettings(){
		
		int countryID = GetCountry();
		tvMpl = TvMediaPlayer.getTvTunerMediaPlayer();
		iTvMplCtx = tvMpl.getTvMediaPlayerContext();
		iTvSrvConfig = iTvMplCtx.getTvServerConfig();
		int installState = satInst.GetCurrentInstallationState();
		iTvSrvConfig.setValue(ITvServerConfig.MONITOR_SDT_ORIGINAL_STATUS,1);
		userSelectedPkg = satInst.GetAttribute(installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageGroup);
		if(userSelectedPkg==MwDataTypes.PKG_ID_FRANSAT){
			iTvSrvConfig.setValue(ITvServerConfig.MONITOR_SDT_ORIGINAL_STATUS,0);
		}
		else{
			iTvSrvConfig.setValue(ITvServerConfig.MONITOR_SDT_ORIGINAL_STATUS,1);
		}

		//Multi-feed Support
		if (countryID==InstallationCountryConstants.GERMANY){
			iTvSrvConfig.setValue(ITvServerConfig.MULTIFEED_SUPPORTED, 1);	
		}else{
		  	iTvSrvConfig.setValue(ITvServerConfig.MULTIFEED_SUPPORTED, 0);/*ID 5379*/
		}

		//Default Character table satellite
		switch(countryID)
		{
		case InstallationCountryConstants.TURKEY:
			iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE_SAT, 5);	//ISO/IEC 8859-9
			break;
		case InstallationCountryConstants.POLAND:	
			iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE_SAT, 6);//ISO/IEC 8859-2
			break;
		case InstallationCountryConstants.AUSTRIA:
		case InstallationCountryConstants.BELGIUM:
		case InstallationCountryConstants.GERMANY:
		case InstallationCountryConstants.LUXEMBOURG:
		case InstallationCountryConstants.NETHERLANDS:	
			iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE_SAT, 0x81);// ISO/IEC 8859-1
			break;
		default:
			iTvSrvConfig.setValue(ITvServerConfig.DEFAULT_CHARACTER_TABLE_SAT, 0);//ISO/IEC 6937 default value
			break;

		}
		int pkgid1 = satInst.GetAttribute(installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageId);
		if((userSelectedPkg==MwDataTypes.PKG_ID_TURK) && ((pkgid1 == MwDataTypes.DIGITURK_TURKSAT_PACKAGE_ID) || (pkgid1 == MwDataTypes.DIGITURK_EUTELSAT_PACKAGE_ID))){
			iTvSrvConfig.setValue(ITvServerConfig.DUMP_ALLPIDS_SAT,1); //enabling all pid dump in capmt for digiturk package
		}
		else{
			iTvSrvConfig.setValue(ITvServerConfig.DUMP_ALLPIDS_SAT,0);
		}	
		// CR RMCR-3063	
		if(countryID == InstallationCountryConstants.TURKEY)
		{
			iTvSrvConfig.setValue(ITvServerConfig.MONITOR_SDT_RUNNING_STATUS, 0);
		}
		iTvSrvConfig.sync();
		
		Log.d(TAG, "commitToCTVSettings exit ");
	}

	private void commitSatelliteSettingsToGlobalSettings() {
		int count = getLNBCount();
		
		int i, k=0;
		int LnbNumber;                         
		int LnbType;                                
		int LowLoFreq;                           
		int HighLoFreq;
		int ToneControl;
		int LnbPower;
		int ConnectionType;
		int UserBandPrimaryTuner;
		int UserBandFrequencyPrimaryTuner;
		int UserBandSecondaryTuner;
		int UserBandFrequencySecondaryTuner;
		int SatId=0;
	
		String l_digiturk_eutelsat_w4_36e;	
		String l_packageName;
		String l_SatelliteName;
	
		/* Vector items */
			for(i=0;i<count;i++) 
			{
				Log.d(TAG,"Satellite id " + satInst.GetSatId(i));
				if(satInst.GetSatId(i) == MwDataTypes.EUTELSAT_W4_36E)
				{
					Log.d(TAG,"Satellite is EUTELSAT_W4_36E");
					LnbType = 3;
				}else 
				{
				LnbType = satInst.GetLnbType(i);
			}
			Log.d(TAG,"  SatelliteSettingsTable LnbType" + LnbType);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE, i, LnbType);
			LnbPower = satInst.GetLnbPower(i);
			Log.d(TAG,"  SatelliteSettingsTable LnbPower" + LnbPower);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLNBPOWER, i, LnbPower);
			LowLoFreq = satInst.GetLowLoFreq(i);
			Log.d(TAG,"  SatelliteSettingsTable LowLoFreq" + LowLoFreq);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ, i, LowLoFreq);
			HighLoFreq = satInst.GetHighLoFreq(i);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ, i, HighLoFreq);
			ToneControl = satInst.GetToneControl(i);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGTONECONTROL, i, ToneControl);

			SatId = satInst.GetSatId(i);
			Log.d(TAG, "SatelliteSettingsTable SatID " + SatId);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGSATELLITEID, i, SatId);
			
			l_SatelliteName = satInst.GetSatelliteName(i);
			m_settings.putString(TvSettingsConstants.INSTALLATIONSETTINGSATELLITENAME, i, l_SatelliteName);
		}

		for (i = count; i < 4; i++) {
			/* Reset all details to 0 for non-occupied LNBs */
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE, i, 0);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLNBPOWER, i, 0);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ, i, 0);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ, i, 0);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGTONECONTROL, i, 0);
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGSATELLITEID, i, 0xFFFF);
		}

		/* Scalar Items */
		ConnectionType = getConnectionType();
		m_settings.putInt(TvSettingsConstants.INSTSETTINGSCONNECTIONTYPE, 0,ConnectionType);

		UserBandPrimaryTuner = GetUnicableUBNumber();
		m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, UserBandPrimaryTuner);
		Log.d(TAG, "UserBandPrimaryTuner " + UserBandPrimaryTuner);
		UserBandFrequencyPrimaryTuner = satInst.GetUnicableUBFreqTuner2(0);
		m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEFREQUENCYPRIMARYTUNER, 0, UserBandFrequencyPrimaryTuner);
		Log.d(TAG, "UserBandFrequencyPrimaryTuner " + UserBandFrequencyPrimaryTuner);

		if(IsDualTunerOn()) {
			UserBandSecondaryTuner = GetUnicableUBNumberTuner2();
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDSECONDARYTUNER, 0, UserBandSecondaryTuner);
			Log.d(TAG, "UserBandSecondaryTuner " + UserBandPrimaryTuner);
			UserBandFrequencySecondaryTuner = satInst.GetUnicableUBFreqTuner2(1);
			Log.d(TAG, "UserBandFrequencySecondaryTuner " + UserBandFrequencySecondaryTuner);
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEFREQUENCYSECONDARYTUNER, 0, UserBandFrequencySecondaryTuner);
		} else {
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDSECONDARYTUNER, 0, 0);
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEFREQUENCYSECONDARYTUNER, 0, 0);
		}
	
	}
	
	public void writeTunerSelectionToTVS(){
		Log.d(TAG, "writeTunerSelectionToTVS mCachedDualTunerSetting: " + mCachedDualTunerSetting);
		/* Setting Dual Tuner value */	
		if(isTwoTunerSupported()){
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, mCachedDualTunerSetting);
		}else{
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, 0);
			}
		}
	
	public void commitToTVSettings(){
		Log.d(TAG, "commitToTVSettings entry: ");
		
		// commit operator to TVSettings
		int installState = satInst.GetCurrentInstallationState();
		userSelectedPkg = satInst.GetAttribute(installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageGroup);
		
		int subtitleStatus = 0;
		switch (userSelectedPkg) {
		case MwDataTypes.PKG_ID_GENERIC:
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.NONE);
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		case MwDataTypes.PKG_ID_CANAL:
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.CANALDIGITAL);
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			subtitleStatus = 1;
			break;
		case MwDataTypes.PKG_ID_M7:
			Log.d(TAG, "commit M7 spcfc changes enter");
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.M7);
			
			Log.d(TAG, "commit M7 spcfc ACCESSTYPE_IGNORE");
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ACCESSTYPE_IGNORE);
			
			// commit M7 specific changes
			String subPkgName = GetSelectedPackageName();
			
			if(subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_THE_NETHERLANDS_CANAL_DIGITAL_SD)) || 
			   subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_THE_NETHERLANDS_CANAL_DIGITAL_HD)) ||
			   subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TV_VLAANDEREN_SD))				 || 
			   subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TV_VLAANDEREN_HD))				 	
			  )
			{
				Log.d(TAG, " commit M7 specific changes case I");
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.DUTCH); // primary audio
				m_settings.putInt(TvSettingsConstants.PREFERREDSECONDARYAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH); // secondary audio
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.DUTCH); // primary subtitle
				subtitleStatus = 1; // set subtitle on  /*AN-74989*/
			}else if(subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TELESAT_BELGIUM)) || 
					subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_TELESAT_LUXEMBOURG))){
				Log.d(TAG, " commit M7 specific changes case II");
				subtitleStatus = 0; // set subtitle off  /*AN-74989*/
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.FRENCH); // primary audio
				m_settings.putInt(TvSettingsConstants.PREFERREDSECONDARYAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH); // secondary audio
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.FRENCH); // primary subtitle
			}else if(subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_AUSTRIASAT))){
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.GERMAN); // primary audio
				m_settings.putInt(TvSettingsConstants.PREFERREDSECONDARYAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH); // secondary audio
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.GERMAN); // primary subtitle
				subtitleStatus = 0; // set subtitle off  /*AN-74989*/
				Log.d(TAG, " commit M7 specific changes case III");
			}else if(subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_SKYLINK_CS_LINK_CESKO))){
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.CZECH); // primary audio
				m_settings.putInt(TvSettingsConstants.PREFERREDSECONDARYAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.SLOVAK); // secondary audio
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.CZECH); // primary subtitle
				subtitleStatus = 0; // set subtitle off  /*AN-74989*/
				Log.d(TAG, " commit M7 specific changes case IV");
			}else if(subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_SKYLINK_CS_LINK_SLOVENSKO))){
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.SLOVAK); // primary audio
				m_settings.putInt(TvSettingsConstants.PREFERREDSECONDARYAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.CZECH); // secondary audio
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.SLOVAK); // primary subtitle
				subtitleStatus = 0; // set subtitle off  /*AN-74989*/
				Log.d(TAG, " commit M7 specific changes case V");
			}else if(subPkgName.equalsIgnoreCase(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_HELLO_HUNGARY))){
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.HUNGARIAN); // primary audio
				m_settings.putInt(TvSettingsConstants.PREFERREDSECONDARYAUDIOLANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH); // secondary audio
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE,0,0); // make subtitle OFF
				m_settings.putInt(TvSettingsConstants.PREFERREDSECONDARYSUBTITLELANGUAGE,0,TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH); // secondary subtitle
				int mMenuLanguage = m_settings.getInt(TvSettingsConstants.MENULANGUAGE, 0, 0);
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,mMenuLanguage);
				subtitleStatus = 0;
				Log.d(TAG, " commit M7 specific changes case VI");
			}
			
			
			Log.d(TAG, " commit M7 specific changes exit");
			break;
		case MwDataTypes.PKG_ID_POL:
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			int pkgid = satInst.GetAttribute(installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageId);
			if(pkgid == MwDataTypes.CYFROWY_POLSAT_PACKAGE_ID) {
				m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.CYFROWYPOLSAT);
			} else if(pkgid == MwDataTypes.CYFRAPLUS_POLSAT_PACKAGE_ID) {
				m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.CYFROWY);
			}
			break;	
		case MwDataTypes.PKG_ID_N:
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.POLANDN);
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		case MwDataTypes.PKG_ID_RUSSIA:
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.RUSSIANTV);
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		case MwDataTypes.PKG_ID_TURK:
			int pkgid1 = satInst.GetAttribute(installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageId);
			if(pkgid1 == MwDataTypes.DIGITURK_TURKSAT_PACKAGE_ID) {
				m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.DigiturkTurksat);
			} else if(pkgid1 == MwDataTypes.DIGITURK_EUTELSAT_PACKAGE_ID) {
				m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.DigiturkEutelsat);
			}
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		case MwDataTypes.PKG_ID_FRANSAT:
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.FRANSAT);
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,4);
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,4);
			subtitleStatus = 2;
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		case MwDataTypes.PKG_ID_OPERATOR_PROFILE:
			//m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.OP_PROFILE);
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		case MwDataTypes.PKG_ID_FREESAT:
			Log.d(TAG, " Selected Package is FREESAT");
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0, TvSettingsDefinitions.OperatorSatelliteConstants.FREESAT);
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		case MwDataTypes.PKG_ID_TRICOLOR:
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0,TvSettingsDefinitions.OperatorSatelliteConstants.TRICOLOR); 
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		case MwDataTypes.PKG_ID_ASTRA_LCN:
			m_settings.putInt(TvSettingsConstants.OPERATORSATELLITE, 0,TvSettingsDefinitions.OperatorSatelliteConstants.ASTRALCN); 
			m_settings.putInt(TvSettingsConstants.ACCESSTYPESAT, 0,TvSettingsDefinitions.AccessTypeConstants.ALL);
			break;
		default:
			break;
		}
		
		/* Setting Dual Tuner value */
		if(isTwoTunerSupported()){
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, mCachedDualTunerSetting);
		}else{
			m_settings.putInt(TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, 0);
		}
		
		if((getConnectionTypeFromMW() == CONNECTION_TYPE.DISEQC_1_0) || (getConnectionTypeFromMW() == CONNECTION_TYPE.DISEQC_MINI)){
			commitSelectedLNBs();
		}
		
		// set the default subtitle
		m_settings.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0,subtitleStatus);

		commitSatelliteSettingsToGlobalSettings();
	
		// as per pavan
		ITvClockManager tvclkManager = ITvClockManager.Instance.getInterface();//new TvClockManager();
        tvclkManager.SetClockUnDefined();
			
		Log.d(TAG, "### commitToTVSettings userSelectedPkg " + userSelectedPkg + "   mode  " +  installState +  " in TVSettings " + m_settings.getInt(TvSettingsConstants.OPERATORSATELLITE, 0, 0 ));
		commitToCTVSettings();
		Log.d(TAG, "commitToTVSettings exit ");
	}
	
	public void saveSatelliteSettingsToPersistent()
	{
		Log.d(TAG, "SaveSatelliteSettingsToPersistent entry: ");
		
		satInst.SaveSatelliteSettingsToPersistent();
		Log.d(TAG, "SaveSatelliteSettingsToPersistent exit: ");
	}
	public void commitSatelliteSettingsToPersistent()
	{
		Log.d(TAG, "CommitSatelliteSettingsToPersistent entry: ");
		
		satInst.CommitSatelliteSettingsToPersistent();
		Log.d(TAG, "CommitSatelliteSettingsToPersistent exit: ");
		
	}
	public void ExitSatInstaller()
	{
		Log.d(TAG, "ExitSatInstaller entry: ");
		satInst.ExitSatInstaller();
		Log.d(TAG, "ExitSatInstaller exit: ");
	}
	
	public boolean isVirginInstallMode()
	{
		Log.d(TAG, "isVirginInstallMode entry");
		boolean l_ret = false;
		if(m_settings.getInt(TvSettingsConstants.VIRGINBIT, 0, 0) == 1)
		{
			l_ret = true;
		}
		Log.d(TAG, "isVirginInstallMode returning" + l_ret);
		return l_ret;
	}
	
	public void setTuner2Active(boolean isTunerAct){
		Log.d(TAG, "setTuner2Active " + isTunerAct);
		isTuner2Active = isTunerAct;
		
		if((isTunerAct == true) && (ifRecordingIsInProgress() == false)) {
			if(((mSessionInstanceAux != null) && (mSessionInstanceAux.getSessionState() != SessionHandlerTIF.SESSION_STATE.SESSION_CREATED)) ||
				(mSessionInstanceAux == null)){
				Log.d(TAG, "setTuner2Active mSessionInstanceAux creating ");
				createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_AUX);
			}
		}
	}
	
	public boolean isTuner2Active(){
		return isTuner2Active;
	}
	public boolean IsLnbSettingsAvailable()
	{
		Log.d(TAG, "isLnbsettingsAvailabe entry");
		boolean l_ret = false;
		
		/*if(GetIsNordicCountry() || (getConnectionType() == LnbSettingsEntry.LnbConnectionUnicableLnb) || (getConnectionType() == LnbSettingsEntry.LnbConnectionUnicableSwitch) )
		{
			l_ret = true;
		}*/
		// AN-76760
			l_ret = true;
		
		// disable if satip
		if(ifSatIPConnectionType()){
			l_ret = false;
		}
		Log.d(TAG, "isLnbsettingsAvailabe returning " + l_ret);
		return l_ret;
		
	}
	
	public boolean IsLnbPowerAvailable()
	{
		Log.d(TAG, "IsLnbPowerAvailable entry");
		boolean l_ret = true;
		
		if((getConnectionType() == LnbSettingsEntry.LnbConnectionUnicableLnb) || (getConnectionType() == LnbSettingsEntry.LnbConnectionUnicableSwitch) )
		{
			l_ret = false;
		}
		Log.d(TAG, "IsLnbPowerAvailable returning " + l_ret);
		return l_ret;
		
	}
			
	public void setLnbPower(int lnbIndex, byte powerStateOnOff )
	{
		Log.d(TAG, "setLnbPower entry");
		// powerStateOnOff on=1 off=0
	//	LnbSettingsEntry l_lnbSettings = satInst.GetLnbSettings(lnbIndex);
	//	l_lnbSettings.LnbPower = powerStateOnOff;
		satInst.setLnbpower(lnbIndex,powerStateOnOff);
	//	satInst.SetLnbSettingsviaIndex(lnbIndex,l_lnbSettings);
		Log.d(TAG, "setLnbPower exit");

	}
	
	public byte GetLnbPower(int lnbIndex)
	{
		Log.d(TAG, "GetLnbPower entry");
		//LnbSettingsEntry l_lnbSettings = satInst.GetLnbSettings(lnbIndex);
		byte LnbPower = satInst.GetLnbPower(lnbIndex);
		Log.d(TAG, "GetLnbPower exit RETURNING "+ LnbPower);
		return LnbPower;
		
	}
	
	public void set22khztone(int lnbIndex, byte toneControl)
	{
		Log.d(TAG, "set22khztone entry");
		//tone control can be : on = 1 off = 0 automatic = 2
		//LnbSettingsEntry l_lnbsettings = satInst.GetLnbSettings(lnbIndex);
		//l_lnbsettings.ToneControl = toneControl;
		satInst.settotone(lnbIndex,toneControl);
		//satInst.SetLnbSettingsviaIndex(lnbIndex, l_lnbsettings);
		Log.d(TAG, "set22khztone exit");
	}
	
	public int Get22khztone(int lnbIndex)
	{
		Log.d(TAG, "Get22khztone entry");
		//LnbSettingsEntry l_lnbSettings = satInst.GetLnbSettings(lnbIndex);
		int ToneControl = satInst.GetToneControl(lnbIndex);
		Log.d(TAG, "Get22khztone exit RETURNING "+ ToneControl);
		return ToneControl;
	}
	
	public void setLnbLowLoFrequency(int lnbIndex, int lnbLowLoFreq, boolean isSetToNVM) {
		Log.d(TAG, "SetLnbLowLoFrequency entry " + lnbIndex + ", " + lnbLowLoFreq + ", " + isSetToNVM);

		lnbLowLoFreq = lnbLowLoFreq * 1000;		

		// write to MW
		satInst.setlnbLowLoFrequency(lnbIndex, lnbLowLoFreq);

		// if required read from MW and set to NVM

		if (isSetToNVM) {
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ, lnbIndex, lnbLowLoFreq);
		}
	}
	
	public int getLnbLowLoFrequency(int lnbIndex, boolean readFromNVM) {
		Log.d(TAG, "GetLnbLowLoFrequency entry");
		int LowLoFreq = 9750000;
		
		LowLoFreq = satInst.GetLowLoFreq(lnbIndex);
		
		if (readFromNVM) {
			LowLoFreq = m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ, lnbIndex, 0);
		} 
		
		Log.d(TAG, "getLnbLowLoFrequency exit RETURNING " + LowLoFreq);

		return LowLoFreq / 1000;
	}
	

	public void setLnbHighLoFrequency(int lnbIndex, int lnbHighLoFreq, boolean isSetToNVM) {
		Log.d(TAG, "setLnbHighLoFrequency entry " + lnbIndex + ", " + lnbHighLoFreq + ", " + isSetToNVM);
		lnbHighLoFreq = lnbHighLoFreq * 1000;

		// write to MW
		satInst.setlnbHighLoFrequency(lnbIndex, lnbHighLoFreq);

		// if requested set to NVM
		if (isSetToNVM) {
			m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ, lnbIndex, lnbHighLoFreq);
		}
	}
	
	public int getLnbHighLoFrequency(int lnbIndex, boolean readFromNVM) {
		Log.d(TAG, "getLnbHighLoFrequency entry");
		int HighLoFreq = 10600000;

		HighLoFreq = satInst.GetHighLoFreq(lnbIndex);

		if (readFromNVM){
			HighLoFreq =m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ, lnbIndex, 0);
		}
		
		Log.d(TAG, "getLnbHighLoFrequency exit RETURNING " + HighLoFreq);
		return HighLoFreq / 1000;
	}
	
	public void resetLnbSettings()
	{
		Log.d(TAG, "resetLnbSettings entry");
		satInst.ResetLnbSettings();
		reloadSelectedLNBs();
		Log.d(TAG, "resetLnbSettings exit");
	}
	
	public void cancelInstallation()
	{
		Log.d(TAG, "cancelInstallation entry");
		int l_installState = satInst.GetCurrentInstallationState();
		
		if(l_installState == MwDataTypes.IHsvInstallation2_InstallationStateIdle)
		{
			resetInstallation();
			resetLnbSettings();
		}
		else
		{
			SetScanStops();
		}
		Log.d(TAG, "cancelInstallation exit ");
	}
	
	public void setInstallMode(int p_installMode)
	{
		Log.d(TAG,"setInstallMode " + p_installMode);
		m_installMode = p_installMode;
	}
	
	public boolean isTwoTunerSupported()
	{
		boolean l_ret = false;
		if(m_settings.getInt(TvSettingsConstants.OPTWOTUNERS, 0, 0)== 1)
		{
			l_ret = true;
		}
		Log.d(TAG,"isTwoTunerSupported returning " + l_ret);
		return l_ret;
	}
	
	public boolean dualTunerSelectedInNVM ()
	{
		boolean l_ret = false;
		
		l_ret = (m_settings.getInt(TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, 0 ) == 1)?true:false;
		
		Log.d(TAG,"dualTunerSelectedInNVM returning " + l_ret);
		return l_ret;
	}
	
	public void sendIntent(String p_intent)
	{
		Log.d(TAG,"sendIntent p_intent = " + p_intent);
		String l_mode = "Auto";
		Intent l_intent = new Intent(p_intent);
		if(m_installMode == INSTALL_MODE_UPDATE){
			l_mode = "Update";
		}else if(m_installMode == INSTALL_MODE_DTR){
			l_mode = "DTR";
		}
		Log.d(TAG,"l_mode = " + l_mode);
		l_intent.putExtra("InstallMode", l_mode);
		ctx.sendBroadcast(l_intent);
	}
	
	public void enterNonInteruptableMode()
	{
		if(isVirginInstallMode()){
			Log.d(TAG, "NON_INTERRUPTIBLE intent not-dispatched as sytem is in virgin mode");
		}else{
			Log.d(TAG, "NON_INTERRUPTIBLE intent enter dispatched");
	        Intent intent = new Intent("org.droidtv.NON_INTERRUPTIBLE");
	        intent.putExtra("Enter", true);
	        ctx.sendStickyBroadcast(intent);
		}
    }
    
	public void exitNonInteruptableMode(){
		if(isVirginInstallMode()){
			Log.d(TAG, "NON_INTERRUPTIBLE intent not-dispatched as sytem is in virgin mode");
		}else{
			Log.d(TAG, "NON_INTERRUPTIBLE intent exit dispatched");
	        Intent intent = new Intent("org.droidtv.NON_INTERRUPTIBLE");
	        intent.putExtra("Enter", false);
	        ctx.sendStickyBroadcast(intent);
		}
    }
    
	public void setCamUpdateModeFlag(boolean p_isCamUpdateMode)
	{
		Log.d(TAG,"setCamUpdateModeFlag entry with " + p_isCamUpdateMode);
		m_isCamUpdateMode = p_isCamUpdateMode;
	}
	
	public boolean isCamUpdateMode()
	{
		Log.d("NativeAPIHandler", "isCamUpdateMode returning  " + m_isCamUpdateMode);
		return m_isCamUpdateMode;
	}

	public boolean isOperatorProfileSupported()
	{
		Log.d(TAG,"isOperatorProfileSupported");
		return satInst.isOperatorProfileSupported();
	}
	
	public EuinstallerSatSurface getEuinstallerSatSurface()
	{
		Log.d(TAG,"getTCSurface entry " );
		return m_surface;
	}

	public EuinstallerSatSurface createEuinstallerSatSurface(Context p_context)
	{
		Log.d(TAG,"createTCSurface entry " );
		m_surface = new EuinstallerSatSurface(p_context);
		Log.d(TAG,"createTCSurface exit " );
		return m_surface;
	}
	public void setTVMplSurface(Surface p_surface)
	{
		Log.d(TAG,"setTVMplSurface entry " );
		satInst.setSurface(p_surface);
		Log.d(TAG,"setTVMplSurface exit " );
	}

	/*
	public void unBind_Service()
	{
		Log.d(TAG,"unBind_Service entry " );
		satInst.unbindChannelVersionManagerService();
		Log.d(TAG,"unBind_Service exit " );
	}
	*/
	
	public class EuinstallerSatSurface extends SurfaceView implements SurfaceHolder.Callback
	{
		Surface m_surface = null;
		
		public EuinstallerSatSurface(Context context)
		{
			super(context);
			Log.d(TAG,"EuinstallerSatSurface : constructor" );
			getHolder().addCallback(this);
		}
		@Override
		public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
		{
			Log.d(TAG,"EuinstallerSatSurface : surfaceChanged " );
		}
		@Override
		public void surfaceCreated(SurfaceHolder holder)
		{
			Log.d(TAG,"EuinstallerSatSurface : surfaceCreated " );
			m_surface = holder.getSurface();
		}
		@Override
		public void surfaceDestroyed(SurfaceHolder holder)
		{
			Log.d(TAG,"EuinstallerSatSurface : surfaceDestroyed " );
		}
		public Surface getSurface()
		{
			Log.d(TAG,"EuinstallerSatSurface : getSurface " );
			return m_surface;
		}
	}
	
	 public boolean ifRecordingIsInProgress(){
    	boolean returnStatus = false;
    	
    	String[] projection = {IRecordingsContract.C_RECORDING_ID};
    	String selection = IRecordingsContract.C_RECORDING_TYPE + " == ?";
        String[] selectionArgs = {""+IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal()};

        try{
	        Cursor cur = ctx.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, selection, selectionArgs, null);
	        if (cur != null) {
				if(cur.getCount() > 0){
					returnStatus = true;
				}
				cur.close();
				cur=null;
			}
        }catch(Exception ex){
        	Log.d(TAG, "ifRecordingIsInProgress ex caught:" + ex.getMessage());
        }
    	
    	Log.d(TAG, "ifRecordingIsInProgress: " + returnStatus);
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

	public void setPinEntryInTVS(int pinID) {
		Log.d(TAG, "setPinEntryInTVS() " + pinID);
		m_settings.putInt(TvSettingsConstants.INSTSETTINGSPINCODE, 0, pinID);
		Log.d(TAG, "setPinEntryInTVS() " + m_settings.getInt(TvSettingsConstants.INSTSETTINGSPINCODE, 0, 0));
	}
		
	public boolean ifShowPinEntryScreen() {
		boolean returnStatus = false;
		int currentPin = -1;

		// if country is france or italy & pin entry is not already set
		currentPin = m_settings.getInt(TvSettingsConstants.INSTSETTINGSPINCODE, 0, 0);
		Log.d(TAG, "ifShowPinEntryScreen() " + currentPin);
		int installState = satInst.GetCurrentInstallationMode();
		int pkgGroup = satInst.GetAttribute(installState, MwDataTypes.IHsvSatelliteInstallation_AttributePackageGroup);
		Log.d(TAG, "installState:" + installState + " pkgGroup" + pkgGroup);
		if ((pkgGroup == MwDataTypes.PKG_ID_M7) && (currentPin == -1)) {
			returnStatus = true;
		}
		Log.d(TAG, "ifShowPinEntryScreen() " + returnStatus);
		return returnStatus;
	}
	public void StoreCiCamforOp(long ciCamId){
		Log.d(TAG, "cicamid to be stored is " + ciCamId);
		long CiCamId = ciCamId;
		boolean iscached = true;
		int cachedinfoversion = satInst.getOpProfileinfoversion();
		String cachedProfileName = new String(satInst.getOperatorProfilePackageName());
		editor.putLong("CiCamId", CiCamId);
		editor.putString("cachedProfileName",cachedProfileName);
		editor.putInt("cachedinfoversion",cachedinfoversion);
		editor.putBoolean("iscached", iscached);
		editor.commit();	
	}
	public void clearCiCamforOp(){
		Log.d(TAG, "Clearing cicamid stored for Op");
		long CiCamId = 0;
		editor.putLong("CiCamId", CiCamId);
		editor.commit();
	}
	public boolean checkForCiCamId(long newCiCamid){
		Log.d(TAG, "Entered into checkForCiCamId with cicamid " + newCiCamid);
		boolean isCicamIdDiffers = false;
		long CacheCiCamId = 0;
		boolean iscached = false;
		iscached = mCamOp.getBoolean("iscached", iscached);
		Log.d(TAG, "iscached is " + iscached);
		CacheCiCamId = mCamOp.getLong("CiCamId", CacheCiCamId);
		Log.d(TAG, "Cached Cicamid is " + CacheCiCamId);
		if(/*(iscached == true) && */(newCiCamid != CacheCiCamId)){
			isCicamIdDiffers = true;	
		}
		return isCicamIdDiffers;
	}

	public void TriggerOperatorStatusReq() {
			Log.d(TAG, "Request for Operator status Info from MW");
			satInst.requestStatusInfoOnInsCompletion();
	}
	
	public boolean checkForCiCamNitRequest(){
		Log.d(TAG, "Entered into checkForCiCamNitRequest");
		boolean isCicamNitRequestNeeded = false;
		boolean iscached = false;
		String cachedProfileName = null;
		iscached = mCamOp.getBoolean("iscached", iscached);
		try{
		cachedProfileName = new String(mCamOp.getString("cachedProfileName",cachedProfileName));
		}
		catch(Exception e){
			Log.d(TAG, "Exception in cachedprofile name:"+e.toString());
	
		}
		int cachedinfoversion = 0;
		cachedinfoversion = mCamOp.getInt("cachedinfoversion", cachedinfoversion);
		Log.d(TAG, "iscached is " + iscached);
		if(cachedProfileName == null)
		{
			iscached = false;
			editor.putBoolean("iscached", iscached);
			editor.commit();
			Log.d(TAG, "Modified iscached to false");
		}
		else {
		Log.d(TAG, "Cached opname is " + cachedProfileName);
		Log.d(TAG, "cachedinfoversion  is " + cachedinfoversion);
		if((iscached == true) && (cachedinfoversion != satInst.getOpProfileinfoversion()))///* && (cachedProfileName.equals(satInst.getOperatorProfilePackageName()) == false)*/)
			isCicamNitRequestNeeded = true;
		}
		return isCicamNitRequestNeeded;
	}
	public void setNonInterruptibleState(boolean argState){
		Log.d(TAG, "listening to org.droidtv.NON_INTERRUPTIBLE change: " + argState);
		ifCurrentlyInNonInterruptibe = argState;
	}

	public PowerStates getFromPowerState(){

		Log.d(TAG, "getFromPowerState " + fromPowerStates);
		return fromPowerStates;
	}

	public PowerStates getToPowerState(){

		Log.d(TAG, "getToPowerState " + toPowerStates);
		return toPowerStates;
	}

	public void handlePowerStateChange(PowerStates argFromPowerState, PowerStates argToPowerState) {
		PoweStateChangeHandler psh = new PoweStateChangeHandler();

		fromPowerStates = argFromPowerState;
		toPowerStates = argToPowerState;
		psh.execute(POWER_CHANGE_DETECTED);
	}

	class PoweStateChangeHandler extends AsyncTask<String, Void, String> {

		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			Log.d(TAG, "onPostExecute enter result " + result);

			if (result.equalsIgnoreCase(DEFAULT_POWER_ON_CASE)) {
				Log.d(TAG, "onPostExecute enter");
				// reset flags
				satInst.setOPProfLaterPressed(false);
			}else if(result.equalsIgnoreCase(EXIT_INSTALLATION)){
				Log.d(TAG, "EXIT_INSTALLATION");
				(InstallerActivityManager.getInstance()).exitInstallation(EXIT_INSTALLER_REASON.POWER_STATE_TO_SEMISTANDY);
			}

			Log.d(TAG, "onPostExecute exit");
		}

		@Override
		protected String doInBackground(String... params) {
			String resultString = "";
			Log.d(TAG, "doInBackground params: " + params[0]);
			if ((params[0]).equalsIgnoreCase(POWER_CHANGE_DETECTED)) {

				if (toPowerStates == PowerStates.POWER_STATE_FULL_SYSTEM_START) {
					resultString = DEFAULT_POWER_ON_CASE;
				}else if (toPowerStates == PowerStates.POWER_STATE_SEMI_STANDBY) {
					if((getApplicationState() == STATE_IDLE) ||
							(getApplicationState() == STATE_SERVICE)){
					}else{
						// case where wizard installation is continuing and power button is pressed
						resultString = EXIT_INSTALLATION;
					}
				}
			}
			return resultString;
		}
	}
	
	
	public boolean isFreesatPackage(int p_radioIndex)
	{
		Log.d(TAG,"IsFreesatPackage Entry, radioIndex:" + p_radioIndex );
		
		boolean l_retVal = false;
		HsvPackageStructure l_pkgStructure;
		int l_countryID = GetCountry();
		l_pkgStructure = satInst.GetPackageByIndex(p_radioIndex);


		Log.d(TAG,"Country id" + l_countryID + "packageid" + l_pkgStructure.PackageId);
		
		//Checking package == Freesat and Country == UK: country check put in once req cleared.
		if (l_pkgStructure.PackageId == MwDataTypes.FREESAT_PACKAGE_ID)/* && 
				(l_countryID == InstallationCountryConstants.UK) )*/
		{
			l_retVal = true;
		}
		Log.d(TAG,"IsFreesatPackage Exit, return:" + l_retVal);
		
		return l_retVal;
	}

	
	public boolean isAstraLCNPackage(int p_radioIndex)
	{
		Log.d(TAG,"isAstraLCnPackage Entry, radioIndex:" + p_radioIndex );
		
		boolean l_retVal = false;
		HsvPackageStructure l_pkgStructure;
		int l_countryID = GetCountry();
		l_pkgStructure = satInst.GetPackageByIndex(p_radioIndex);

		Log.d(TAG,"Country id" + l_countryID + "packageid" + l_pkgStructure.PackageId);
		

		if (l_pkgStructure.PackageId == MwDataTypes.ASTRALCN_PACKAGE_ID)
		{
			l_retVal = true;
		}
		
		Log.d(TAG,"isAstraLCnPackage Exit, return:" + l_retVal);
		
		return l_retVal;
	}

	public int getInstalledLnbCount()
	{
		Log.d(TAG,"getInstalledLnbCount Entry");
		int l_idx;
		int l_installedLNBCount = 0;
		int l_maxLNBCount = 4;
		for(l_idx = 0; l_idx < l_maxLNBCount; l_idx ++)
		{
			if(mNativeAPIWrapper.IsLNBInstalled(l_idx))
			{
				l_installedLNBCount++;
			}
		}
		
		Log.d(TAG,"getInstalledLnbCount Exit, return:" + l_installedLNBCount);
		return l_installedLNBCount;
	}

	public boolean isPostCodeValid(String p_postcode)
	{
		Log.d(TAG,"isPostCodeValid Entry");
		boolean l_retVal = false;
		
		// regular expression for postcode pattern Axxx nAA or Axx nAA or Ax nAA
		String l_regexPattern = "([A-Z])(((\\d|[A-Z]){1})|((\\d|[A-Z]){2})|((\\d|[A-Z]){3}))( {1})(\\d)([A-z]{2})";
		if(p_postcode.matches(l_regexPattern))
		{
			l_retVal = true;
		}
		
		Log.d(TAG,"isPostCodeValid Exit, return:" + l_retVal);
		return l_retVal;
	}

	public void setPostCode(String p_postcode)
	{
		Log.d(TAG,"setEnteredPostCode Entry" + p_postcode);
		int l_postCodeLen = p_postcode.length();
		
		satInst.setPostCode(l_postCodeLen,p_postcode);
		
		Log.d(TAG,"setEnteredPostCode Exit");
	}

	public void stopBckInstallation() 
	{		
			//Log.d(TAG,"stopBckInstallation Entry");
			satInst.StopMWInstIfInstExists();
			//Log.d(TAG,"stopBckInstallation Exit");
	}
	
	public void setUserSelectedMode(SelectedMode argMode){
		userSelectedMode = argMode;
		Log.d(TAG, "setUserSelectedMode: " + userSelectedMode);
	}
	
	public SelectedMode getUserSelectedMode(){
		Log.d(TAG, "getUserSelectedModes: " + userSelectedMode);
		return userSelectedMode;
	}
	
	public boolean ifSatIPConnectionType(){
		
		boolean returnStatus;
		/*Shiva: change to ebable satip*/
		returnStatus = (satInst.GetLNBType() == LnbSettingsEntry.LnbConnectionSatIP);
		
		Log.d(TAG, "ifSatIPConnectionType " + returnStatus);
	    return returnStatus;
	}
	
	public boolean ifNetworkAvailable() {
		boolean returnStatus = false;
		Log.d(TAG, "ifNetworkAvailable Enter");
	    ConnectivityManager connectivityManager = (ConnectivityManager)ctx.getSystemService(Context.CONNECTIVITY_SERVICE);
	    NetworkInfo activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
	    
	    if((activeNetworkInfo != null) && (activeNetworkInfo.isConnected())){
	    	if((activeNetworkInfo.getType() == ConnectivityManager.TYPE_ETHERNET) ||
	    			(activeNetworkInfo.getType() == ConnectivityManager.TYPE_WIFI)){
	    		returnStatus = true;
	    	}
	    }
	    Log.d(TAG, "ifNetworkAvailable " + returnStatus);
	    return returnStatus;
	}
	
	public String getNetworkName(){
		String returnString = "";
		
		ConnectivityManager connectivityManager = (ConnectivityManager)ctx.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
		
		if((activeNetworkInfo != null) && (activeNetworkInfo.isConnected())){
			
			
			if(activeNetworkInfo.getType() == ConnectivityManager.TYPE_WIFI){
				Log.d(TAG, "getNetworkName wifi");
				WifiManager wifiManager = (WifiManager) ctx.getSystemService(Context.WIFI_SERVICE);
				WifiInfo wifiInfo = wifiManager.getConnectionInfo();
				if (WifiInfo.getDetailedStateOf(wifiInfo.getSupplicantState()) == NetworkInfo.DetailedState.CONNECTED) {	
					returnString = wifiInfo.getSSID();
				}
			}else if(activeNetworkInfo.getType() == ConnectivityManager.TYPE_ETHERNET){
				Log.d(TAG, "getNetworkName lan");
				returnString = activeNetworkInfo.getTypeName();
			}else{
				Log.d(TAG, "else getNetworkName: " +  activeNetworkInfo.getTypeName());
			}
		}
		 
		Log.d(TAG, "getNetworkName " + returnString);
		return returnString;
	}
	
	public void networkChangeDetected(){
		Log.d(TAG, "networkChangeDetected");
		ntf.notifyAllObservers(EventIDs.SATIP_NETWK_CONN_CHANGE,"");
	}
	
	public void resetSessionMediumAsNVM(){
		Log.d(TAG, "resetSessionMediumAsNVM");
		int connectionType = m_settings.getInt(TvSettingsConstants.INSTSETTINGSCONNECTIONTYPE, 0,0);
		if(connectionType == 5){ // SATIP
			setSessionTuneWithMedium(SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER,SessionHandlerTIF.SESSION_MEDIUM.SATIP);
		}else{
			setSessionTuneWithMedium(SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER,SessionHandlerTIF.SESSION_MEDIUM.DVBS2);
		}
	}
	
	public int getNVMConnectionType(){
		int connectionType = m_settings.getInt(TvSettingsConstants.INSTSETTINGSCONNECTIONTYPE, 0,0);
		Log.d(TAG,"getNVMConnectionType " + connectionType);
		return connectionType;
	}
	
	//------------------------------ TIF Changes ------------------------------ //

	public SessionHandlerTIF mSessionInstanceMain = null;
	public SessionHandlerTIF mSessionInstanceAux = null;
	public SessionHandlerTIF mSessionService = null;
	
	public void createTIFSession(SessionHandlerTIF.SESSION_PURPOSE argSessionPurpose) {
		//Log.d(TAG, "createTIFSession " + argSessionPurpose);
		if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER) {
			mSessionInstanceMain = new SessionHandlerTIF(ctx, SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
			mSessionInstanceMain.registerToSessionHandler(mMainCallbackSessionHandler);
			mSessionInstanceMain.createNewSession();
		}else if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_AUX) {
			mSessionInstanceAux = new SessionHandlerTIF(ctx, SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_AUX);
			mSessionInstanceAux.registerToSessionHandler(mAuxCallbackSessionHandler);
			mSessionInstanceAux.createNewSession();
			//ntf.notifyAllObservers(EventIDs.NATIVELAYER_INIT_DONE_TUNER2,"");
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
		public void sessionOnChannelRetuned(Uri channelUri) {
			// background installation wil be triggered from here
			if((getApplicationState() == STATE_IDLE) ||
				(getApplicationState() == STATE_SERVICE)){
				//Log.d(TAG, "sessionOnChannelRetuned in Observer mode channelUri: " + channelUri);
				try {
					if( channelUri == null){
						backInstallInst.stopBackgroundInstallation();
					}else{
						long channel_id = ContentUris.parseId(channelUri);
						//Log.d(TAG, "sessionOnChannelRetuned with _ID " + channel_id);
						String[] projection = new String[] { Channels.COLUMN_TYPE };
						String mselection = Channels._ID + "= ?" ;
						String[] mselectionargs = new String[] { String.valueOf(channel_id)};
						satInst.setSessionHandler(mSessionService);
						satInst.registerAndReqForOpProf();
						Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
						try
						{						
							if((cursor != null) && (cursor.moveToFirst() != false)) {
								String ChannelType = cursor.getString(0);
								if((ChannelType.equalsIgnoreCase(Channels.TYPE_DVB_S2)) ||(ChannelType.equalsIgnoreCase(Channels.TYPE_DVB_S))){
									Log.d(TAG, "DVBS Channel " + ChannelType);
									satInst.setSessionHandler(mSessionService);
									satInst.sessionOnChannelRetuned();
									satInst.setDemuxIntf();
									backInstallInst.startBackgroundInstallation();
									if(isOPRegistered == false){
										//									satInst.registerAndReqForOpProf();
										//satInst.registerCIListener();
										isOPRegistered = true;
										setopcache();
									}
								}
								else{
									Log.d(TAG, "Non DVBS Channel " + ChannelType);
									backInstallInst.stopBackgroundInstallation();
								}
							}
							else{
								Log.d(TAG, "Null cursor " + cursor);
								backInstallInst.stopBackgroundInstallation();
							}
						}
						finally{
							if(cursor != null) {						  
								cursor.close();
								cursor=null;
							}
						}

					}
				}
				catch (Exception e)
				{
				}
			}
		}

		@Override
		public void sessionCreationSuccessfull() {
			satInst.createMWInstance(); 
			//Log.d(TAG, "sessionCreationSuccessfull and MW instance created, Loading the TVProvider Data");
			try{
				LoadTvProviderData();
			}catch(Exception ex){
				Log.d(TAG,ex.getMessage());
			}
//			satInst.registerAndReqForOpProf();
			// create instace for background installation
			backInstallInst = new BackgroundInstallation(ctx);
			ssbyInstallInst	= new SemistandbyUpdate(ctx);
			registerTvProviderContentObservers();
			//PR:TF515PHIALLMTK01-24702 
			/* 
				Scenario: satinstallerservice died (lowmemorykiller) > oncreate create new session >
				sessionCreationSuccessfull pause > suddenly tuneerservice died > sessionReleased callback >
				sessionCreationSuccessfull resume > calls made on invalid session

			*/
			if(mSessionService.getSessionState() != SessionHandlerTIF.SESSION_STATE.INVALID){
				Uri selectedURI = mSessionService.getTunerSession().getSelectedURI();
				if(selectedURI != null){
					//Log.d(TAG, "There is already a URI selected so send OnchannelRetuned which is missed");
					sessionOnChannelRetuned(selectedURI);			
				}
			}
		}

		@Override
		public void sessionCreationFailed() {
			// TODO Auto-generated method stub
			// exit giving notification to the user
		}
	};
	
	private SessionHandlerTIF.ISessionHandlerTIF mMainCallbackSessionHandler = new SessionHandlerTIF.ISessionHandlerTIF() {
		
		@Override
		public void sessionReleased() {
			// TODO Auto-generated method stub
		}
		
		@Override
		public void sessionOnChannelRetuned(Uri channelUri) {
			// respond only for Installer main installations
			if( channelUri == null){
				
			}else if(getApplicationState() != STATE_IDLE){
				satInst.sessionOnChannelRetuned();
//				satInst.unRegisterCIListener();
				satInst.setDemuxIntf();
			}
		}
		
		@Override
		public void sessionCreationSuccessfull() {
			
			// set session handler so euinstallerTC can use session handler
			// call mw instance creation if not already created
			satInst.createMWInstance(); // optional can be removed as MW instance by this time is already created by service
			satInst.setSessionHandler(mSessionInstanceMain);
			
			setSessionTuneWithMedium(SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER,SessionHandlerTIF.SESSION_MEDIUM.DVBS2);
		}
		
		@Override
		public void sessionCreationFailed() {
			// exit giving notification to the user
		}
	};
	private SessionHandlerTIF.ISessionHandlerTIF mAuxCallbackSessionHandler = new SessionHandlerTIF.ISessionHandlerTIF() {
		
		@Override
		public void sessionReleased() {
			// TODO Auto-generated method stub
		}
		
		@Override
		public void sessionOnChannelRetuned(Uri channelUri) {
			// respond only for Installer main installations
			if( channelUri == null){
				
			}else if(getApplicationState() != STATE_IDLE){
				satInst2.sessionOnChannelRetuned();
//				satInst2.unRegisterCIListener();
			}
		}
		
		@Override
		public void sessionCreationSuccessfull() {
			
			// set session handler so euinstallerTC can use session handler
			// call mw instance creation if not already created
			//satInst.createMWInstance(); // optional can be removed as MW instance by this time is already created by service
			satInst2.setSessionHandler(mSessionInstanceAux);
			
			setSessionTuneWithMedium(SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_AUX,SessionHandlerTIF.SESSION_MEDIUM.DVBS2);
		}
		
		@Override
		public void sessionCreationFailed() {
			// exit giving notification to the user
		}
	};
	
	public void setSessionTuneWithMedium(SessionHandlerTIF.SESSION_PURPOSE argSessionPurpose, SessionHandlerTIF.SESSION_MEDIUM argMedium){
		Log.d(TAG, "setSessionTuneWithMedium " + argMedium);
		
		if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER) {
			satInst.setSessionTuneWithMedium(argMedium);
		}else if(argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_AUX) {
			satInst2.setSessionTuneWithMedium(argMedium);
		}
	}
	public void muteAudio(boolean argValue){
		Log.d(TAG, "muteAudio with argValue=" + argValue);
		
		if(mSessionInstanceMain != null) {
			ITVTunerSession tvmc = mSessionInstanceMain.getTunerSession();
			if(tvmc != null) {	
				tvmc.setTrackMuteStatus(TvTrackInfo.TYPE_AUDIO ,argValue);
			} else {
				Log.d(TAG, "muteAudio iITVTunerSession is null");
			}
		}
	}
		
	public void closeTIFSession(SessionHandlerTIF.SESSION_PURPOSE argSessionPurpose) {
		Log.d(TAG, "closeTIFSession " + argSessionPurpose);
		if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER) {
			if(mSessionInstanceMain != null){
				mSessionInstanceMain.closeSession();
				mSessionInstanceMain = null;
			}
		} else if (argSessionPurpose == SessionHandlerTIF.SESSION_PURPOSE.SESSION_PURPOSE_AUX) {
			if(mSessionInstanceAux != null){
				mSessionInstanceAux.closeSession();
				mSessionInstanceAux = null;
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
		  //Log.d(TAG,"registerTvProviderContentObservers()");
		  try{
			  if((ctx!=null) && (isChannelInstall(ctx)))
			  {
				  ContentResolver cr = ctx.getContentResolver();
				  mObserver = new TvProviderListener(mHandler);
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

				SatInstallerTvProviderData TvpData = new SatInstallerTvProviderData();
				byte[]  BlobData = null;
				String NewPreset;

				// execute block if uri is tv uri
				if(TvContract.isChannelUriForTunerInput(uri))
				{
					try
					{
						channelid = Long.parseLong(uri.getLastPathSegment());

					//	Log.d(TAG, "TvProviderNotificationReceiver with _ID " + channelid);

						/*Get Data from TVProvider*/
						String[] projection = new String[] {Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_TYPE, Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_DISPLAY_NUMBER, Channels.COLUMN_DISPLAY_NAME, Channels.COLUMN_BROWSABLE, Channels.COLUMN_INTERNAL_PROVIDER_DATA, Channels.COLUMN_VERSION_NUMBER, Channels.COLUMN_LOCKED, Channels._ID, Channels.COLUMN_NETWORK_AFFILIATION};
						String mselection = Channels._ID + "= ?" ;
						String[] mselectionargs = new String[] { String.valueOf(channelid)};

						Cursor cursor = ctx.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);

						if((cursor != null) && (cursor.moveToFirst() != false)) {
							String ChannelType = cursor.getString(0);
							if((ChannelType.equalsIgnoreCase(Channels.TYPE_DVB_S2)) ||(ChannelType.equalsIgnoreCase(Channels.TYPE_DVB_S))){
								//Log.d(TAG, "DVBS Channel " + ChannelType);
								/*Update channel in MW*/
								Log.d(TAG, "Adding Data to MW");
								TvpData.DecoderType = ConvertDecoderType(ChannelType); // TODO: use this once this value is filled in MW
								TvpData.ServiceType= cursor.getInt(1);
								TvpData.OriginalNetworkId= cursor.getInt(2);
								TvpData.Tsid= cursor.getInt(3);
								TvpData.ServiceId= cursor.getInt(4);
								TvpData.PresetNumber= cursor.getInt(5);
								TvpData.ChannelName= cursor.getString(6);
								TvpData.NumericSelect = cursor.getInt(7);
								TvpData.ChannelLock= cursor.getInt(10);
								TvpData.UniqueId = cursor.getInt(11);
								NewPreset = cursor.getString(12);
								try {
									TvpData.NewPreset = (NewPreset.equalsIgnoreCase("New") ? 1 : 0);
								}
								catch (Exception e)
								{
								}
								BlobData = cursor.getBlob(8);

								AddMWRecord(TvpData,BlobData);
							}
							else{
								//Log.d(TAG, "Non DVBS Channel " + ChannelType);
							}
						}
						else{
						Log.d(TAG, "Null cursor " + cursor);
	 
						}
						if(cursor != null) 
						cursor.close();

					}
					catch(Exception e)
					{
						Log.d(TAG,"onChange():Exception:"+e);
					}
				}
			}
		}
	}
	
	
	public void startTricolorRegionParsing() 
	{
		
		satInst.startTricolorRegionParsing();
	}


	/**
	 * @param selectedRegionIndex
	 */
	public void setRegionIndex(int selectedRegionIndex) 
	{
		
		satInst.setTricolorRegionIndex (selectedRegionIndex);
		
	}


	/**
	 * @param selectedPosition
	 * @return
	 */
	public boolean isRussiaTricolor(int selectedPosition) {
		
		Log.d(TAG,"isRussiaTricolor Entry, selectedPosition:" + selectedPosition );
		
		boolean isTricolor = false;
		HsvPackageStructure pkgStructure;
		
		pkgStructure = satInst.GetPackageByIndex(selectedPosition);


		Log.d(TAG,"packageid" + pkgStructure.PackageId);
		
		if (((pkgStructure.PackageId == MwDataTypes.TRICOLOR_HD_PACKAGE_ID) || 
			  (pkgStructure.PackageId == MwDataTypes.TRICOLOR_SD_PACKAGE_ID))) 
			 
		{
			isTricolor = true;
		}
		Log.d(TAG,"IsRussiaTricolor Exit, return:" + isTricolor);
		
		return isTricolor;
	}


	/**
	 * @return
	 */
	public String[] getTricolorRegionNames() 
	{
		String regionnames[] = satInst.getTricolorRegionNames();
		
		//TODO:SUTENDRA:check the req when LRN descriptor is not present and behave here accordingly.
		return regionnames;
		
	}

	public int getTotalPackagesFound()
	{
		Log.d(TAG,"getTotalPackagesFound Entry");
		int retVal = 0;

		satInst.IdentifyPackagesAvailable();
		retVal = satInst.GetTotalNumberOfPackagesFound();

		Log.d(TAG,"getTotalPackagesFound Exit" + retVal);
		return retVal;
	}
	
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
			 //Log.d(TAG,"isInstallChannels() called: count:"+count);
			 
			 if(count>0)
				 return true;
		 }
		 
		 return false;
 	}
	 
	public boolean ifLNBSelectionControllable() {
		boolean returnStatus = false;
		CONNECTION_TYPE contype =  getConnectionTypeFromMW();

		if ((CONNECTION_TYPE.DISEQC_1_0 == contype) || (CONNECTION_TYPE.DISEQC_MINI == contype)) {
			returnStatus = true;
		}
		
		return returnStatus;
	}
	
	public CONNECTION_TYPE getConnectionTypeFromMW(){
		CONNECTION_TYPE returnType = CONNECTION_TYPE.SINGLE_LNB;
		int lnbType = LnbSettingsEntry.LnbConnectionSingle;
		if(isTuner2Active()){
			lnbType = satInst2.GetLNBType();
		}else{
			lnbType = satInst.GetLNBType();
		}
		
		switch (lnbType) {
		case LnbSettingsEntry.LnbConnectionSingle:
			returnType = CONNECTION_TYPE.SINGLE_LNB;
			break;
		case LnbSettingsEntry.LnbConnectionDiSeqc1_0:
			returnType = CONNECTION_TYPE.DISEQC_1_0;
			break;
		case LnbSettingsEntry.LnbConnectionDiSeqcMini:
			returnType = CONNECTION_TYPE.DISEQC_MINI;
			break;
		case LnbSettingsEntry.LnbConnectionUnicableLnb:
			returnType = CONNECTION_TYPE.UNICABLE_LNB;
			break;
		case LnbSettingsEntry.LnbConnectionUnicableSwitch:
			returnType = CONNECTION_TYPE.UNICABLE_SWITCH;
			break;
		case LnbSettingsEntry.LnbConnectionSatIP:
			returnType = CONNECTION_TYPE.SAT_IP;
			break;
		}

		Log.d(TAG,"getConnectionTypeFromMW " + returnType);
		return returnType;
	}
	
	public Boolean[] getPrescanForLNBs(){
		Log.d(TAG,"ifPrescanLNB: "+ ifPrescanLNB[0] + "," + ifPrescanLNB[1] + "," + ifPrescanLNB[2] + "," + ifPrescanLNB[3]);
		return ifPrescanLNB;
	}
	
	public void setPrescanLNBs(int lnbIndex, boolean ifSelected){
		Log.d(TAG,"setPrescanLNBs: "+ lnbIndex + " " + ifSelected);
		ifPrescanLNB[lnbIndex] = ifSelected;
	}
	
	public void reloadSelectedLNBs(){
		Log.d(TAG,"reloadSelectedLNBs");
		if (mStoredSharedPreferences != null) {
			ifPrescanLNB[0] = mStoredSharedPreferences.getBoolean("selected_lnb_1", true);
			ifPrescanLNB[1] = mStoredSharedPreferences.getBoolean("selected_lnb_2", true);
			ifPrescanLNB[2] = mStoredSharedPreferences.getBoolean("selected_lnb_3", true);
			ifPrescanLNB[3] = mStoredSharedPreferences.getBoolean("selected_lnb_4", true);
		}
	}
	
	private void commitSelectedLNBs(){
		Log.d(TAG,"commitSelectedLNBs");
			if (edit != null) {
		 		edit.putBoolean("selected_lnb_1", ifPrescanLNB[0]);
		 		edit.putBoolean("selected_lnb_2", ifPrescanLNB[1]);
		 		edit.putBoolean("selected_lnb_3", ifPrescanLNB[2]);
		 		edit.putBoolean("selected_lnb_4", ifPrescanLNB[3]);
		 		edit.commit();
			}
	}
	
	public boolean ifCountrySupportsHBBTV(){
			boolean returnStatus = false;
			int tvscCountryID = m_settings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
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
				case TvSettingsDefinitions.InstallationCountryConstants.UK:
				case TvSettingsDefinitions.InstallationCountryConstants.OTHER:
				case TvSettingsDefinitions.InstallationCountryConstants.AUSTRALIA:
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
				case TvSettingsDefinitions.InstallationCountryConstants.NEWZEALAND:
				case TvSettingsDefinitions.InstallationCountryConstants.MALAYSIA:
					returnStatus = true;
					break;
				default:
					returnStatus = false;
					break;
			}
			Log.d(TAG,"ifCountrySupportsHBBTV " + returnStatus);
			return returnStatus;
		}
		
		public void setHBBTVStatus(boolean ifOn){
			Log.d(TAG,"setHBBTVStatus " + ifOn);
			if(ifOn){
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSHBBTV, 0, 1);
			}else{
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSHBBTV, 0, 0);
			}
		}

}
