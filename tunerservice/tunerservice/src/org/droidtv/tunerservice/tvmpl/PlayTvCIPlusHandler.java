package org.droidtv.tunerservice.tvmpl;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.HashSet;
import org.droidtv.tunerservice.db.CAMDetails;
import org.droidtv.tunerservice.iapp.AmmiServiceListener;
import org.droidtv.tunerservice.overlay.AmmiSurfaceView;
import org.droidtv.tunerservice.db.CamInfoDB;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;
import org.droidtv.tunerservice.interfaces.IOverlayListener;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.media.ITvMediaCI.CICamIdInfo;
import org.droidtv.tv.media.ITvMediaCI.CIHcC2DSD;
import org.droidtv.tv.media.ITvMediaCI.CIHcCDSD;
import org.droidtv.tv.media.ITvMediaCI.CIHcS2DSD;
import org.droidtv.tv.media.ITvMediaCI.CIHcSDSD;
import org.droidtv.tv.media.ITvMediaCI.CIHcT2DSD;
import org.droidtv.tv.media.ITvMediaCI.CIHcTDSD;
import org.droidtv.tv.media.ITvMediaCI.CIMmiEnq;
import org.droidtv.tv.media.ITvMediaCI.CIMmiMenuList;
import org.droidtv.tv.media.ITvMediaCI.CIMmiResponse;
import org.droidtv.tv.media.ITvMediaCI.IOnCIChangeListener;
import org.droidtv.tv.media.ITvMediaControl;
import org.droidtv.tv.media.ITvMediaControl.IonMediaChangeListener;
import org.droidtv.tv.media.ITvMediaPlayerContext;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.video.ITvVideoManager;
import org.droidtv.tv.video.IVideoProperties;
import org.droidtv.tv.tvinput.IInteractiveService;
import org.droidtv.tv.tvinput.TVCIControlCallback;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tv.tvinput.ITVCIControl;
import org.droidtv.tv.tvinput.CIMmiEnqImpl;
import org.droidtv.tv.tvinput.CamInfoImpl;
import org.droidtv.tv.tvinput.ITVCIControl.CamInfo;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;	
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tunerservice.util.CamLogger;
import android.view.View.OnKeyListener;
import android.view.KeyEvent;
import android.view.View;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;
import android.media.tv.TvContract;
import android.os.TransactionTooLargeException;
import android.os.DeadObjectException;

public class PlayTvCIPlusHandler implements OnKeyListener,IPlayTvStateChangeListener,IChannelContract,IOverlayListener{

	public enum MmiType {
		MmiTypeEnquiry(0), MmiTypeMenu(1), MmiTypeList(2);
		private final int value;

		private MmiType(int val) {
			this.value = val;
		}
	}

	public enum ScramblingStatus {
		Invalid(1), UnScrambled(2), Scrambled(3), ProgramToBePurchased(4), ProgramNotEntitled(5);
		private final int value;

		private ScramblingStatus(int val) {
			this.value = val;
		}
	}

	public enum CiPlusStatus {
		StatusInactive(0), StatusInitialising(1), StatusInitialsed(2), StatusAuthorised(
				3), StatusNOTauthorised(4), StatusV1(5);
		private final int value;
		private CiPlusStatus(int val) {
			this.value = val;
		}
	}
	private String TAG = PlayTvCIPlusHandler.class.getSimpleName();
	private static final int MAINTYPE = 0;
	private static final int AUXTYPE = 2;
	private static final String DefaultStr = "a";
	public static final int INVALID_STATUS = -1;
	private	static final int TIME_DELAY= 2000;
	private PlayTVFacMediaPlayer mPlayTvmpl;
	private TvMediaPlayer mTvmpl;
	private ITvMediaPlayerContext mITvMediaPlayerContext; 
	private ITvMediaCI mITvMediaCI;
	private ITvMediaControl mITvMediaControl;
	private CIMmiEnq mCIEnqMmi;
	private CIMmiMenuList mCIMenuMmi;
	private CIMmiMenuList mCIListMmi;
	private Context mContext;
	private int mHCSvcId;
	private boolean mMMIInProgress;
	private boolean mAMMIInProgress;
	private int mCurrentMmiID;
	private boolean mListChoiceExists;
	private boolean mCAMUpgrInProgress;
	private boolean mIsHCforCAMupgrade;
	private boolean mIsHCinProgress;
	private boolean mIsHCAskReleased;
	private boolean mPlayCompletedRecvd;
	private boolean mLockStatus;
	private int[] mLastSelectedMenuItem;
	private int mMenuItenCount;
	private int mCurrentPurpose;
	private Handler mHandler;
	public int mCamStatus;
	private CamInfoDB mCamInfo;
	private CAMDetails mCamDetails;
	private CIChangeListener mCIChangeListener;
	private Handler mHandlerTimer;
	private CamHelper mCamHelper;
	private int mSlotID;
	private AmmiSurfaceView mAmmiSurfaceView;
	private IInteractiveService mInteractiveService;
	private AmmiServiceListener mIServiceListener;
	private Uri mPreviousChannelUri;
	private boolean mIsCAMUIRegistered;
	private Map<String, String> mPreviousChannelHeader;
	private Uri mUserSelectedURI;
	private Map<String, String> mUserSelectedHeader;
	private OverlayManager mOverlayManager;
	private static final int MAIN_AMMI = 1;
	private static final int AUX_AMMI = 2;
	private int mAmmiType;
	private String mActionType;
	private boolean mIsAmmiStarted;
	private boolean mIsOnAppStarted;
	private static final int AMMI_OPEN = 1;
	private static final int AMMI_CLOSE = 2;
	private boolean mIsCamWizardToShow;
	private boolean mIsChannelsInstalled;
	private Set<TVCIControlCallback> mEventsCallback	= new HashSet(2);
	private static final int CI_CLEAN = -1;
	private static final int CAM_UPGRADE_COMPLETED = 0;
	private static final int INVALID_CAM_UPGRADE = -1;
	private CamLogger mCamLogger;
	private boolean mIsHCTuneToSameSvc;
	private int mPresetNumber = 0;
	private boolean mIsMMIEnableRequired = false;
	private boolean mIsSelectionInProgress;
	private boolean lastHCTuneFailed = false;
	private boolean mTimeShiftMode = false;
	private boolean mIsAmmiStopped = false;
	public PlayTvCIPlusHandler(final Context pContext,final String pAction,final PlayTVFacMediaPlayer mpl) {
		mPlayTvmpl = mpl;
		mContext = pContext;
		if(pAction.equals(PlayTvUtils.MAIN_ACTION)){
			TAG = TAG+"-"+MAINTYPE;
		}else if(pAction.equals(PlayTvUtils.AUX_ACTION)){
			TAG = TAG+"-"+AUXTYPE;
		}
		mHandler = new Handler(Looper.getMainLooper());
		mCurrentPurpose = mpl.getCurrentPurpose();
		mCamHelper = new CamHelper(this, mContext);
		mActionType = pAction;
		Log.d(TAG,"PlayTvCIPlusHandler constructor called:"+this+"Ammi Action:"+pAction);
		bindAmmiService(pAction,false);
		mPlayTvmpl.registerListener(this, TAG);
		mHandlerTimer=new Handler(Looper.getMainLooper());
		registerCamLogger();
	}
	
	private void registerCamLogger(){
		mCamLogger = CamLogger.getInstance();
		if(mActionType.equals(PlayTvUtils.MAIN_ACTION)){
			mCamLogger.bindToLoggingService(mContext);
		}
	}
	
	public void setPlayer(final PlayTVFacMediaPlayer mpl){
		mHandler.post(new Runnable() {
			@Override
			public void run() {
				if(mpl != mPlayTvmpl){
					Log.i(TAG,"setPlayer has called mpl is not equal:"+mpl.getCurrentPurpose());
					mPlayTvmpl.unregisterListener(PlayTvCIPlusHandler.this,TAG);
					mPlayTvmpl = mpl;
					mPlayTvmpl.registerListener(PlayTvCIPlusHandler.this, TAG);
					enableCINotification(false);
					initHandler();
					if(mPlayTvmpl.getCurrentPurpose() != 0){
						enableCINotification(true);
					}
				}
			}
		});
	}

	public void setOverlayManager(OverlayManager overlayManager){
		Log.v(TAG,"setOverlayManager called overlayManager:"+overlayManager+"mOverlayManager:"+mOverlayManager);
		if(overlayManager == null || mOverlayManager != overlayManager){
			removeAmmiView(mAmmiType);
		}
		mOverlayManager = overlayManager;
		if(overlayManager != null){
			createAmmiSurfaceView();
			overlayManager.registerForOverlayCallback(this);
		}
	}
	
	@Override
	public void releaseOverlayManager() {
		setOverlayManager(null);
	}
	
	@Override
	public void setOverLayViewStatus(int viewStatus) {
	}
	
	public void createAmmiSurfaceView(){
		mHandler.post(new Runnable() {
			@Override
			public void run() {
				if(mOverlayManager != null && mInteractiveService != null && mAmmiSurfaceView == null){
					mAmmiSurfaceView = new AmmiSurfaceView(mContext,mInteractiveService,PlayTvCIPlusHandler.this);
				} else{
					Log.v(TAG,"createAmmiSurfaceView called mOverlayManager manager is :"+mOverlayManager +"mInteractiveService:"+mInteractiveService);
				}
			}
		});
	}
	
	public void setPlaybackStatus(boolean pTimeShiftMode){
		mTimeShiftMode = pTimeShiftMode;
		if(pTimeShiftMode && isAMMIShowing(AMMI_OPEN)){
			notifyAMMiClose();
			mIsAmmiStopped = true;
		} else if(!pTimeShiftMode && mIsAmmiStopped){
			setAmmiActivate();
			mIsAmmiStopped = false;
		}
		
	}
	private void bindAmmiService(final String pAction,boolean retry){
		Intent intent = new Intent(pAction);
		if(retry){
			intent.putExtra("CrashRecovery", true);
		}
		mContext.bindService(intent, ammIConnection,Context.BIND_AUTO_CREATE);
	}

	class ServiceDeathHandler implements IBinder.DeathRecipient {
		@Override
		public void binderDied() {
			resetAMMI();
		}
	}

	private AmmiServiceListener getAmmiServiceListener(){
		AmmiServiceListener lAmmiListener = new AmmiServiceListener(this);
		return lAmmiListener;
	}

	private void resetAMMI(){
		mIsAmmiStarted = mIsOnAppStarted = false;
		mInteractiveService = null;
		mAmmiSurfaceView = null;
		setAmmiClose();
		setAMMIInProgress(false);
		removeAmmiView(mAmmiType);
		bindAmmiService(mActionType,true);
	}

	private ServiceConnection ammIConnection = new ServiceConnection() {
		@Override
		public void onServiceDisconnected(ComponentName name) {
		}

		@Override
		public void onServiceConnected(ComponentName pName, IBinder pService) {
			try {
				mInteractiveService = IInteractiveService.Instance.asInterface(pService);
				/*
				 * Registering for the interactive service listener call backs
				 */
				pService.linkToDeath(new ServiceDeathHandler(), 0);
				mIServiceListener = getAmmiServiceListener();
				createAmmiSurfaceView();
				if(mIServiceListener != null){
					mInteractiveService.setInteractiveServiceCallbackListener(mIServiceListener);
					setAmmiActivate();
				}else {
					Log.d(TAG,"mIServiceListener is null");
				}
			} catch (Exception e) {
				Log.e(TAG,"Exception in service connection:"+e.toString());
			}
		}
	};

	/*
	 * Will be called when cam removed
	 * 
	 */
	private void closeAMMI(){
		Log.i(TAG,"closeAMMI called:mIsAmmiStarted:"+mIsAmmiStarted+"mIsOnAppStarted"+mIsOnAppStarted);
		stopAMMI();
	}

	private boolean isAMMIShowing(final int eventID){
		boolean isAMMIDisplayed = false;
		if(eventID == AMMI_OPEN) {
			if(mIsAmmiStarted == true){	
				isAMMIDisplayed =  true;
			}else {
				if(mIsOnAppStarted == true){
					isAMMIDisplayed = true;
				}
				else {
					isAMMIDisplayed = false;
				}
			}
		}else if(eventID == AMMI_CLOSE){
			if(mIsAmmiStarted == true && mIsOnAppStarted == true){	
				isAMMIDisplayed = true;
			}else {
				isAMMIDisplayed = false;
			}
		}
		Log.i(TAG,"isAMMIShowing called EventID:"+eventID+"mIsAmmiStarted:"+mIsAmmiStarted +"mIsOnAppStarted:"+mIsOnAppStarted+"isAMMIDisplayed:"+isAMMIDisplayed);
		return isAMMIDisplayed;
	}

	private void addAmmiView(final String actionType){
		if(mAmmiSurfaceView != null && mOverlayManager != null){
			if(actionType.equals(PlayTvUtils.MAIN_ACTION)){
				mAmmiType = MAIN_AMMI;
			}else if(actionType.equals(PlayTvUtils.AUX_ACTION)){
				mAmmiType = AUX_AMMI;
			} 
			mOverlayManager.addAMMIView(mAmmiSurfaceView.getTextureView(),mAmmiType);
		}else {
			Log.v(TAG,"Not added the ammiView surfaceView:"+mAmmiSurfaceView);
		}
	}
	
	private void removeAmmiView(final int ammiType){
		if(mOverlayManager != null){
			mOverlayManager.removeAMMIView(ammiType);
		}else{
			Log.d(TAG,"remvoveammiview not done as overlaymanager is null");
		}
	}
	
	public void resetAmmiSurfaceView(){
		mAmmiSurfaceView = null;
	}
	
	private void startAMMI(){
		if(mAmmiSurfaceView != null && mInteractiveService != null && mOverlayManager != null){
			 if(isAMMIShowing(AMMI_OPEN) == false && !mTimeShiftMode){
				if(isAuxZiggo() == false){
					Log.d(TAG,"start Call");
					enableCamUpgrade(false);
					setAMMIInProgress(true);
					mAmmiSurfaceView.getTextureView().setOnKeyListener(this);
					mAmmiSurfaceView.setTextureViewVisibility(true);
					addAmmiView(mActionType);
					mInteractiveService.start();
					mIsAmmiStarted = true;
				}
			} else {
				setAmmiDisable();
			}
		} else{
			Log.i(TAG,"mAmmiSurfaceView is null or mInteractiveService is null:"+mInteractiveService+"mAmmiSurfaceView:"+mAmmiSurfaceView+"mOverlayManager:"+mOverlayManager);
		}
	}

	private void stopAMMI(){
		if(mInteractiveService != null && isAMMIShowing(AMMI_CLOSE) == true){
			mInteractiveService.stop();
			mIsAmmiStarted = false;
		} 
	}

	public void onAppStarted(){
		mIsOnAppStarted = true;
		setAmmiEnable();
	}

	public void onAppExited(){
		mHandler.post(new Runnable() {
			@Override
			public void run() {
				mIsAmmiStarted = mIsOnAppStarted = false;
				setAmmiClose();
				setAMMIInProgress(false);
				if(mAmmiSurfaceView != null){
					mAmmiSurfaceView.setTextureViewVisibility(false);
				}
			}
		});
	}
	
	/**
	 * Enables the MMI's and will be called before showing the MMI
	 *
	 * @param pEnableStatus mmi status , true means enable the mmi ,false means disable the mmi
	 */
	public void enableMMI(final boolean pEnableStatus){
		Log.d(TAG, "Entered mmiEnable:"+pEnableStatus);
		try { 
			if(mITvMediaCI != null){
				if(pEnableStatus){
					mITvMediaCI.mmiEnable();
				} else {
					mITvMediaCI.mmiDisable();
				}
			} else {
				Log.d(TAG,"enableMMI() has not called TvMediaCI is null");
			}
		}
		catch (Exception e){
			Log.e(TAG,"NullPointerException !!"+e.toString());
		}
	}

	/**
	 *  updateMMIStatus will be called before showing the MMI and closing the MMI
	 *
	 *  @param status State of the MMI true means displaying mmi and false means mmi exited
	 *  @throws RuntimeException
	 */
	public void updateMMIStatus(final boolean pMmiProgress){
		mMMIInProgress = pMmiProgress;
		if(!(pMmiProgress) && mITvMediaCI != null){
			mITvMediaCI.mmiClose(mCurrentMmiID);
		}
	}

	/**
	 * Selected item in the menu or list mmi
	 *
	 * @param menuType  Can be {@link MENU_MMI} or {@link LIST_MMI}
	 * @param selectedItem  User selcted item in the corresponding menu
	 */
	public void selectMMIItem(final int pMenuType,final int pSelectedItem) {
		Log.d(TAG, "selectMMIItem: choice = " + pSelectedItem+"currentMMIID:"+mCurrentMmiID+"menuType:"+pMenuType);
		switch(pMenuType){
		case ITVCIControl.MENU_MMI:
			CIMmiResponse lMenuResponse = new CIMmiResponse();
			lMenuResponse.SelectIndex = pSelectedItem;
			if(mMenuItenCount >= 0) {
				mLastSelectedMenuItem[mMenuItenCount++] = pSelectedItem;
			}
			lMenuResponse.ResponseString = DefaultStr;
			//if (mCIMenuMmi.NumberOfChoices > 0) {
				mITvMediaCI.mmiCmdResponse(mCurrentMmiID, MmiType.MmiTypeMenu.value,lMenuResponse);
			//}
			break;
		case ITVCIControl.LIST_MMI:
			CIMmiResponse lListResponse = new CIMmiResponse();
			lListResponse.SelectIndex = pSelectedItem;
			lListResponse.ResponseString = DefaultStr;
			//if (mCIListMmi.NumberOfChoices > 0) {
				mITvMediaCI.mmiCmdResponse(mCurrentMmiID, MmiType.MmiTypeList.value,lListResponse);
			//}
			break;
		default:
			break;
		}
	}

	/**
	 * Will return list of option items for the mmi based on the menutype
	 *
	 * @param menuType Can be {@link MENU_MMI} or {@link LIST_MMI}
	 * @return String[] {@link ITvMediaCI.CIMmiMenuList.MenuStrings}  based on menuType
	 *
	 */
	public String[] getMMIItems(final int pMenuType) {
		switch(pMenuType){
		case ITVCIControl.MENU_MMI:
			return mCIMenuMmi.MenuStrings;
		case ITVCIControl.LIST_MMI:
			return mCIListMmi.MenuStrings;
		default:
			return new String[0];
		}
	}
	
	/**
	 * Will return last selected menu item in the menu mmi
	 *
	 * @return int last selected item in the menu mmi
	 * 
	 */
	public int getLastSelectedMenuIndex(){
		return mLastSelectedMenuItem[mMenuItenCount];
	}


	/**
	 * To send the answer from enquiry MMI and will be called when the ok button has clicked in enquiry MMI
	 *
	 * @param answer User entered alpha numeric entry in enquiry mmi
	 * 
	 */
	public void setEnquiryMMIResponse(String pAnswer) {
		CIMmiResponse lCIMmiResponse = new CIMmiResponse();
		lCIMmiResponse.SelectIndex = 1; // Answer ID
		lCIMmiResponse.ResponseString = pAnswer;
		mITvMediaCI.mmiCmdResponse(mCurrentMmiID, MmiType.MmiTypeEnquiry.value,lCIMmiResponse);
	}
	
	/**
	 * Will return info for the Enquiry mmi
	 *
	 * @return String {@link ITvMediaCI.CIMmiEnq}
	 * @throws RuntimeException
	 */
	public CIMmiEnqImpl getEnquiryMMIInfo(){
		if(mCIEnqMmi != null){
			CIMmiEnqImpl ciMmiEnqImpl = new CIMmiEnqImpl();
			ciMmiEnqImpl.isVisible = mCIEnqMmi.Blind;
			ciMmiEnqImpl.answerLength= mCIEnqMmi.LengthOfAnswer;
			ciMmiEnqImpl.promptText = mCIEnqMmi.PromptText;
			return ciMmiEnqImpl;
		} else {
			Log.d(TAG,"getEnqMMIText MMI object is null");
			return null;
		}
	}


	/**
	 * Cancelling MMI base on the menutype and will be called when the cancel button was clicked in the Menu MMI
	 *
	 * @param menuType Can be {@link MENU_MMI} or {@link LIST_MMI} or {@link ENQUIRY_MMI}
	 *  @throws RuntimeException
	 */
	public void cancelMMI(int pMenuType) {
		switch(pMenuType){
		case ITVCIControl.MENU_MMI:
			CIMmiResponse lMenuResponse = new CIMmiResponse();
			lMenuResponse.SelectIndex = 0;
			lMenuResponse.ResponseString = DefaultStr;
			if(mMenuItenCount > 0) {
				--mMenuItenCount;
			}
			mITvMediaCI.mmiCmdResponse(mCurrentMmiID, MmiType.MmiTypeMenu.value,lMenuResponse);
			break;
		case ITVCIControl.LIST_MMI:
			CIMmiResponse lListResponse = new CIMmiResponse();
			lListResponse.SelectIndex = 0;
			lListResponse.ResponseString = DefaultStr;
			mITvMediaCI.mmiCmdResponse(mCurrentMmiID, MmiType.MmiTypeList.value,lListResponse);
			break;
		case ITVCIControl.ENQUIRY_MMI:
			CIMmiResponse lEnquiryResponse = new CIMmiResponse();
			lEnquiryResponse.SelectIndex = 0; // Answer ID
			lEnquiryResponse.ResponseString = DefaultStr;
			mITvMediaCI.mmiCmdResponse(mCurrentMmiID, MmiType.MmiTypeEnquiry.value,lEnquiryResponse);
			break;
		default:
			break;
		}
	}

	public void enableCamUpgrade(boolean enable){
	}

	public int getCAMUpgradeStatus(){
		int status = 0;
		return status;
	}

	public void updateCamInfo(CamInfo pCaminfo){
		if(mCamHelper != null){
			mCamHelper.updateCamMedium(pCaminfo.slotId,pCaminfo.medium);
		} else {
			Log.d(TAG,"updateMedium called mCamHelper is null");
		}
	}

	public void enableCAMUI(boolean pEnableStatus){
		Log.d(TAG,"enableCAMUI called:"+pEnableStatus+":"+mIsCAMUIRegistered);
		if(! pEnableStatus && mIsCAMUIRegistered){
			enableMMI(false);
			unRegisterCIListener();
		}else if(pEnableStatus && !mIsCAMUIRegistered) {
			registerCIChangeListener();
			enableMMI(true);
		}
	}

	public CamInfoImpl getCamInfo(int slotId){
		if(mCamHelper != null){
			return mCamHelper.getCamInfo(slotId);
		} else {
			Log.d(TAG,"getCamInfo called mCamHelper is null");
			return null;
		}
	}

	private void enableCINotification(boolean pEnableStatus){
		 Log.d(TAG,"enableCINotification called:"+pEnableStatus+":"+mIsCAMUIRegistered+"isHcInProgress:"+mIsHCinProgress+" mCAMUpgrInProgress:"+mCAMUpgrInProgress);
		if(! pEnableStatus && mIsCAMUIRegistered){
			//Exit from HC only if CAM upgrade is NOT in progress
			if(mIsHCinProgress == true)
			{
				Log.d(TAG,"HC in progress.. so exit HC");
				releaseHC(mPreviousChannelUri,mPreviousChannelHeader);
				mPlayTvmpl.hcReleased();
				mIsHCinProgress  = false;
			}
			notifyAMMiClose();
			enableMMI(false);
			unRegisterCIListener();
		}else if(pEnableStatus && !mIsCAMUIRegistered) {
			registerCIChangeListener();
			enableMMI(true);
			setAmmiActivate();
		}
	}
	
	private void registerForCamNotifications(){
		 if(!mIsCAMUIRegistered) {
			//Caching the current cam status
			int lCamStatus = mCamStatus;
			registerCIChangeListener();
			mIsMMIEnableRequired = true;
			//Comparing the previous camstatus and current camstatus
			if(lCamStatus != mCamStatus){
				showCamWizard(mCamStatus);
			}
		}
	}

	/**
	 * To register callback for cam events.
	 * 
	 * @param eventsCallback Object of type class ITVCIControlCallback      
	 * @throws RuntimeException
	 */
	public void registerCIControlListener(TVCIControlCallback pEventsCallback){
		synchronized(mEventsCallback) {
			Log.i(TAG,"registerCIControlListener called:"+pEventsCallback+"this:"+this);
			mEventsCallback.add(pEventsCallback);
		}
	}

	/**
	 * To un-register callback for cam events.
	 * 
	 * @param eventsCallback Object of type class ITVCIControlCallback      
	 * @throws RuntimeException
	 */
	public void unRegisterCIControlListener(TVCIControlCallback pEventsCallback){
		synchronized(mEventsCallback) {
			Log.i(TAG,"unRegisterCIControlListener called:"+pEventsCallback+"this:"+this);
			mEventsCallback.remove(pEventsCallback);
		}
	}


	private void registerCIChangeListener(){
		if(mITvMediaCI!= null && mIsCAMUIRegistered == false){
			Log.d(TAG, "registerCIChangeListener called");
			mCIChangeListener = new CIChangeListener();
			mITvMediaCI.registerCIChangeListener((IOnCIChangeListener)mCIChangeListener);
			mIsCAMUIRegistered = true;
			mCamStatus =  mITvMediaCI.getCipStatus();
		} else {
			Log.v(TAG, "registerCIChangeListener called mITvMediaCI is null:"+mIsCAMUIRegistered);
		}
	}

	
	private void initHandler() {
		mLastSelectedMenuItem = new int[100];
		mCamStatus =  CiPlusStatus.StatusInactive.value;
		try{
			if (mPlayTvmpl != null) {
				mTvmpl = mPlayTvmpl.getMediaPlayerInstance();
				if (mTvmpl != null) {
					mITvMediaPlayerContext = mTvmpl.getTvMediaPlayerContext();
					mITvMediaCI = mITvMediaPlayerContext.getTvMediaCI();
					Log.i(TAG, "Got TV Media CI Instance:"+mITvMediaCI);
					if (mITvMediaControl == null) {
						mITvMediaPlayerContext = mTvmpl.getTvMediaPlayerContext();
						mITvMediaControl = mITvMediaPlayerContext.getTvMediaControl();
						if (mITvMediaControl != null) {
							MediaChangeListener medialistener = new MediaChangeListener();
							mITvMediaControl.registerListenerCallback((IonMediaChangeListener) medialistener);
							Log.d(TAG, "Got TV Media Control Instance");
						} else {
							Log.d(TAG, "TV Media Control Instance is NULL");
						}
					}
				} else {
					Log.d(TAG, "Media Player Instance is NULL");
				}
			} else {
				Log.d(TAG, " mPlayTvmpl : null object");
			}
		}catch(Exception e){
			Log.e(TAG,"Exception in initHandler:"+e.toString());
		}
	}

	private boolean setAmmiClose() {
		Log.d(TAG, "setAmmiClose called");
		try{
			mITvMediaCI.ammiClose(0);
		}catch(NullPointerException e){
			Log.d(TAG,"NullPointerException : TvMediaCI");
		}
		return true;
	}

	private boolean setAmmiActivate() {
		mHandler.post(new Runnable() {
			@Override
			public void run() {
				Log.d(TAG, "setAmmiActivate called:");
				if (mITvMediaCI != null && mITvMediaCI.isAMMIRequestOpen()) {
					startAMMI();
				}
			}
		});
		return true;
	}

	private void setAmmiEnable() {
		Log.d(TAG, "setAmmiEnable called mMMIInProgress:"+mMMIInProgress);
		if (mITvMediaCI!= null) {
			mITvMediaCI.ammiEnable();
			mAMMIInProgress = true;
		}
		else{
			if(mTvmpl == null){
				mTvmpl = mPlayTvmpl.getMediaPlayerInstance();
			}
			try{
				mITvMediaPlayerContext = mTvmpl.getTvMediaPlayerContext();
				mITvMediaCI = mITvMediaPlayerContext.getTvMediaCI();
				if (mITvMediaCI!= null) {
					mITvMediaCI.ammiEnable();
					mAMMIInProgress = true;
				}
				else
				{
					Log.d(TAG, "Tvmci is Null :-(");
				}
			}catch(Exception e){
				Log.e(TAG,"exception !!");
			}
		}
	}

	private void setAmmiDisable() {
		if (mITvMediaCI!= null && mAMMIInProgress == true) {
			mITvMediaCI.ammiDisable();
		}
		else{
			Log.v(TAG, "setAmmiDisable Tvmci is Null :-mAMMIInProgress"+mAMMIInProgress);
		}
	}

	private void setAMMIInProgress(boolean ammiProgress){
		mAMMIInProgress = ammiProgress;
	}

	public boolean isHcInProgress(){
		return mIsHCinProgress;
	}

	public void onHCTuneFailed() {
		mIsHCinProgress = false;
		lastHCTuneFailed = true;
		mPlayTvmpl.onHCTuneBack(mPreviousChannelUri,mPreviousChannelHeader);
	}

	public boolean isSignalPresent() {
		boolean lRetval = false;
		int lStatus = 1;
		IVideoProperties lVideoProperties = mTvmpl.getTvMediaPlayerContext().getVideoPropertiesImpl(); //did as done in Live settings assistance wizard
		lStatus=lVideoProperties.getSignalPresent();
		Log.v(TAG, "signalPresent = " + lStatus);
		if(lStatus == 1){
			lRetval = true;
		}
		return lRetval;
	}

	public CICamIdInfo  getCamIDInfo(final int pValue){
		if(mITvMediaCI != null){
			return mITvMediaCI.GetCICamIdInfo(pValue);
		}
		return null;
	}

	private int getSlotID(){
		mSlotID = getCamIDInfo(ITvMediaCI.SLOT_UNKNOWN).SlotID;	
		return mSlotID;
	}

	public void dropCamInfoDB(){
		CamInfoDB camInfoDB = CamInfoDB.getInstace(mContext);
		camInfoDB.open();
		camInfoDB.dropCamDetails();
	}
	
	/*
	 *	It is calling from PlaytvService and AUX service
	 */
	public void notifyChannelInstallStatus(boolean channelInstallStatus,Medium medium){
		if(channelInstallStatus == false){
			mIsCamWizardToShow = false;
		} else {
			mIsChannelsInstalled = true;
			if(mActionType == PlayTvUtils.AUX_ACTION){
				if(PlayTVMediaPlayerFactory.getInstance().IsDualTunerFactoryConfigEnabled(medium) == false){
					mIsCamWizardToShow = true;
				}
			}
			checkToShowCamWizard();
		}
	}

	private void  checkToShowCamWizard(){
		Log.i(TAG, "checkToShowCamWizard is called:mIsChannelsInstalled->"+mIsChannelsInstalled+"mIsCamWizardToShow:"+mIsCamWizardToShow);
		if(mIsChannelsInstalled && mIsCamWizardToShow && mITvMediaCI != null){
			mIsChannelsInstalled = false;
			mIsCamWizardToShow = false;
			int lCamStatus = mITvMediaCI.getCipStatus();
			showCamWizard(lCamStatus);
		}
	}

	private void showCamWizard(int lCamStatus){
		if(lCamStatus == CiPlusStatus.StatusV1.value){
			if(mITvMediaCI != null && mITvMediaCI.isCIPlusCompatible(ITvMediaCI.SLOT_UNKNOWN) == false){
				if(mCamHelper != null && mCamHelper.isCamWizardCanShow()){
					try{
						getSlotID();
						synchronized (mEventsCallback) {
							for (TVCIControlCallback listener : mEventsCallback) {
								listener.onEvent(mSlotID,ITVCIControl.CI_LAUNCHWIZARD,mCamHelper.getNoOfCAMS());
							}
						}
					}catch(TransactionTooLargeException e) {
						Log.e(TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(TAG,"DeadObjectException !!!");
					}catch(Exception e){
						Log.e(TAG,"Exception:"+e.toString());	
					}
				} 
			}
		} else 
			if(lCamStatus == CiPlusStatus.StatusAuthorised.value){
				if(mCamHelper != null && mCamHelper.isCamWizardCanShow()){
					try{
						synchronized (mEventsCallback) {
							for (TVCIControlCallback listener : mEventsCallback) {
								listener.onEvent(mSlotID,ITVCIControl.CI_LAUNCHWIZARD,mCamHelper.getNoOfCAMS());
							}
						}
					}catch(TransactionTooLargeException e) {
						Log.e(TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(TAG,"DeadObjectException !!!");
					}catch(Exception e){
						Log.e(TAG,"Exception:"+e.toString());	
					}
				}
			}
	}

	private void unRegisterCIListener(){
		Log.d(TAG, "unRegisterCIListenr is called:"+mITvMediaCI+":"+mCIChangeListener);
		if(mITvMediaCI != null && mCIChangeListener != null && mIsCAMUIRegistered == true){
			mITvMediaCI.unregisterCIChangeListener((IOnCIChangeListener)mCIChangeListener);
			mIsCAMUIRegistered = false;
		}
	}

	private void camUpgrAbortedCompleted(){
		if(mCAMUpgrInProgress)
		{
			mCAMUpgrInProgress = false;
			try{
				synchronized (mEventsCallback) {
					for (TVCIControlCallback listener : mEventsCallback) {
						listener.onEvent(mSlotID,ITVCIControl.CI_CAMUPGRADE_COMPLETED,0);
					}
				}
			}catch(TransactionTooLargeException e) {
				Log.e(TAG,"TransactionTooLargeException !!!");
			}catch(DeadObjectException e) {
				Log.e(TAG,"DeadObjectException !!!");
			}catch(Exception e){
				Log.e(TAG,"Exception:"+e.toString());	
			}
			mPlayTvmpl.onCamUpgradeStarted(false);
		}
	}

	public void notifyAMMiCloseMW(){
			if((mITvMediaCI != null) && (mITvMediaCI.getCipStatus() > CiPlusStatus.StatusInactive.value) && (mAMMIInProgress)){
				setAmmiClose();
			}else {
				Log.i(TAG,"notifyAMMiCloseMw called mITvMediaCI:"+mITvMediaCI+"mAMMIInProgress:"+mAMMIInProgress);
			}
	}
	
	private void notifyAMMiClose()
	{
		if((mITvMediaCI != null) && (mITvMediaCI.getCipStatus() > CiPlusStatus.StatusInactive.value) && (mAMMIInProgress)){
			mAMMIInProgress = false;
			stopAMMI();
		}else {
			Log.i(TAG,"notifyAMMiClose:stopAmmi not called:"+mAMMIInProgress+"mITvMediaCI:"+mITvMediaCI);
		}
	}
	
	private boolean isInZiggo(){
		ITvSettingsManager globalSettings =  ITvSettingsManager.Instance.getInterface();
		Medium medium = PlayTvUtils.getCurrentMedium();
		Log.i(TAG,"isZiggo called medium:"+medium+"operator:"+globalSettings.getInt(TvSettingsConstants.OPERATORCABLE, 0, 0));
		if((medium == Medium.MEDIUM_CABLE) && ((globalSettings.getInt(TvSettingsConstants.OPERATORCABLE, 0, 0) == TvSettingsDefinitions.OperatorCableConstants.Ziggo))){
			return true;
		}
		return false;
	}

	private boolean isAuxZiggo(){
		if(mActionType == PlayTvUtils.AUX_ACTION)
		{
			if(isInZiggo()){
				setAmmiDisable();
				return true;
			}
		}
		return false;
	}
	
	class CIChangeListener extends IOnCIChangeListener{
		@Override
		public void onAMMIClosed() {
			if(mITvMediaCI.getCipStatus() > CiPlusStatus.StatusInactive.value){
				stopAMMI();
			}
		}

		@Override
		public void onAMMIOpened() {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					if(!mIsSelectionInProgress){
						startAMMI();
					}
				}
			});
			
		}

		@Override
		public void onAppInfoReceived() {
		}

		@Override
		public void onCAMError(int pType) {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					try {
						synchronized (mEventsCallback) {
							for (TVCIControlCallback listener : mEventsCallback) {
								listener.onEvent(mSlotID,ITVCIControl.CI_PLUS_ERRORMESSAGE,0);
							}
						}
					}catch(TransactionTooLargeException e) {
						Log.e(TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(TAG,"DeadObjectException !!!");
					}catch (Exception e) {
						Log.e(TAG,"Exception in onCAMError");
					}
				}
			});
		}

		@Override
		public void onCAMStatusChanged(final int pCurrentCamStatus) {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					Log.v(TAG, "onCAMStatusChanged called currentStatus:" + pCurrentCamStatus + "mCamStatus = " + mCamStatus+"CurrentPurpose:"+mCurrentPurpose);
					if((pCurrentCamStatus ==  CiPlusStatus.StatusInactive.value)  && (mCamStatus != CiPlusStatus.StatusInactive.value)){
						mAMMIInProgress = mMMIInProgress = false;
						try {
								if(mCamLogger != null){
									mCamLogger.logCamUsage(mSlotID,false);
								}
								if(mCamHelper.getCamStatus(mSlotID) == true){
									try{
										closeAMMI();
										synchronized (mEventsCallback) {
											for (TVCIControlCallback listener : mEventsCallback) {
												listener.onEvent(ITvMediaCI.SLOT_UNKNOWN,ITVCIControl.CI_REMOVED,0);
											}
										}
									}catch(TransactionTooLargeException e) {
									Log.e(TAG,"TransactionTooLargeException !!!");
								}catch(DeadObjectException e) {
									Log.e(TAG,"DeadObjectException !!!");
								}catch(Exception e){
									Log.e(TAG,"Exception:"+e.toString());	
								}
							} else {
								try{
									closeAMMI();
									synchronized (mEventsCallback) {
										for (TVCIControlCallback listener : mEventsCallback) {
											listener.onEvent(ITvMediaCI.SLOT0,ITVCIControl.CI_REMOVED,0);	
										}
									}
								}catch(TransactionTooLargeException e) {
									Log.e(TAG,"TransactionTooLargeException !!!");
								}catch(DeadObjectException e) {
									Log.e(TAG,"DeadObjectException !!!");
								}catch(Exception e){
									Log.e(TAG,"Exception:"+e.toString());	
								}
							}
						}catch (Exception e) {
							Log.e(TAG,"Exception in onCAMStatusChanged:"+e.toString());	
						}
						if(mCAMUpgrInProgress == true)
						{
							mCAMUpgrInProgress = false;
						}
						if(mIsHCinProgress == true)
						{
							onHCStateChanged(true);
						}
					}	
					else if((mCamStatus == CiPlusStatus.StatusInactive.value) && (pCurrentCamStatus != CiPlusStatus.StatusInactive.value)){
						try{
							if(mCamLogger != null){
								getSlotID();
								mCamLogger.logCamUsage(mSlotID,true);
							}
							synchronized (mEventsCallback) {
								for (TVCIControlCallback listener : mEventsCallback) {
									listener.onEvent(mSlotID,ITVCIControl.CI_INSERTED,CI_CLEAN);
								}
							}
						}catch(TransactionTooLargeException e) {
							Log.e(TAG,"TransactionTooLargeException !!!");
						}catch(DeadObjectException e) {
							Log.e(TAG,"DeadObjectException !!!");
						}catch(Exception e){
							Log.e(TAG,"Exception:"+e.toString());	
						}
					}
					if((pCurrentCamStatus == CiPlusStatus.StatusV1.value) && (mCamStatus != CiPlusStatus.StatusV1.value)){
						getSlotID();
						if(mITvMediaCI.isCIPlusCompatible(ITvMediaCI.SLOT_UNKNOWN) == false){
							try{
								if(mCamHelper != null && mCamHelper.isNewCamInserted()){
									synchronized (mEventsCallback) {
										for (TVCIControlCallback listener : mEventsCallback) {
											listener.onEvent(mSlotID,ITVCIControl.CI_INSERTED,0);
										}
									}
								}
								if(mCamHelper != null && mCamHelper.isCamWizardCanShow()){
									synchronized (mEventsCallback) {
										for (TVCIControlCallback listener : mEventsCallback) {
											listener.onEvent(mSlotID,ITVCIControl.CI_LAUNCHWIZARD,mCamHelper.getNoOfCAMS());
										}
									}
								}
							}catch(TransactionTooLargeException e) {
								Log.e(TAG,"TransactionTooLargeException !!!");
							}catch(DeadObjectException e) {
								Log.e(TAG,"DeadObjectException !!!");
							}catch(Exception e){
								Log.e(TAG,"Exception:"+e.toString());	
							}
						}
					}
					else if((pCurrentCamStatus == CiPlusStatus.StatusAuthorised.value) && (mCamStatus != CiPlusStatus.StatusAuthorised.value)) {

						if(mCamHelper != null && mCamHelper.isCamWizardCanShow()){
							try{
								synchronized (mEventsCallback) {
									for (TVCIControlCallback listener : mEventsCallback) {
										listener.onEvent(mSlotID,ITVCIControl.CI_LAUNCHWIZARD,mCamHelper.getNoOfCAMS());
									}
								}
							}catch(TransactionTooLargeException e) {
								Log.e(TAG,"TransactionTooLargeException !!!");
							}catch(DeadObjectException e) {
								Log.e(TAG,"DeadObjectException !!!");
							}catch(Exception e){
								Log.e(TAG,"Exception:"+e.toString());	
							}
						} 
					}
					mCamStatus = pCurrentCamStatus;
				}
			});
		}

		@Override
		public void onCAMUpgradeAborted() {
			camUpgrAbortedCompleted();
		}

		@Override
		public void onCAMUpgradeCompleted() {
			camUpgrAbortedCompleted();
		}

		@Override
		public void onCAMUpgradeInProgress(int pStatus) {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					int lCamUpgradeStatus = INVALID_STATUS; 
					if(mITvMediaCI != null)
					lCamUpgradeStatus = mITvMediaCI.getCAMUpgradeStatus();
					Log.v(TAG, "onCAMUpgradeInProgress called mCAMUpgrInProgress:"+mCAMUpgrInProgress+"lCamUpgradeStatus:"+lCamUpgradeStatus);
					if( (lCamUpgradeStatus != INVALID_STATUS) && (mCAMUpgrInProgress != true) )
					{
						mCAMUpgrInProgress = true;
						try{
							synchronized (mEventsCallback) {
								for (TVCIControlCallback listener : mEventsCallback) {
									listener.onEvent(mSlotID,ITVCIControl.CI_CAMUPGRADE_STARTED,0);
								}
							}
						}catch(TransactionTooLargeException e) {
							Log.e(TAG,"TransactionTooLargeException !!!");
						}catch(DeadObjectException e) {
							Log.e(TAG,"DeadObjectException !!!");
						}catch(Exception e){
							Log.e(TAG,"Exception:"+e.toString());	
						}
						mPlayTvmpl.onCamUpgradeStarted(true);
					}
				}
			});
		}

		@Override
		public void onCAMUpgradeInitiated() {
		}

		@Override
		public void onCAMUpgradeRequested() {
		}

		@Override
		public void onHCStateChanged(final boolean pIscamremoved) {
			if((mIsHCinProgress == true))
			{
				mPlayTvmpl.hcReleased();
				mIsHCinProgress = false;
				if((pIscamremoved == true) || (mIsHCforCAMupgrade == true))
				{
					Log.d(TAG,"HC state changed is called, so tuning to previous channel. Calling onHCTuneBack");
					mPlayTvmpl.onHCTuneBack(mPreviousChannelUri,mPreviousChannelHeader);
					mIsHCforCAMupgrade = false;
				}
				else if(mIsHCAskReleased == true)
				{
					Log.d(TAG,"HC state changed is called, so tuning to user selected channel. Calling onHCTuneBack");
					mPlayTvmpl.onHCTuneBack(mPreviousChannelUri,mPreviousChannelHeader);
					mIsHCAskReleased = false;
				}
			}			
		}

		@Override
		public void onMmiClosed(final int pStatus) {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					if(mITvMediaCI.getCipStatus() > CiPlusStatus.StatusInactive.value){
						try{
							synchronized (mEventsCallback) {
								for (TVCIControlCallback listener : mEventsCallback) {
									listener.onEvent(mSlotID,ITVCIControl.CI_CLOSEMMI_WIDGET,0);
								}
							}
						}catch(TransactionTooLargeException e) {
							Log.e(TAG,"TransactionTooLargeException !!!");
						}catch(DeadObjectException e) {
							Log.e(TAG,"DeadObjectException !!!");
						}catch(Exception e){
							Log.e(TAG,"Exception:"+e.toString());	
						}
					}
				}
			});
		}

		@Override
		public void onMmiCmdEnq(final int pMmiId,final CIMmiEnq pMmiCmd) {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					mCIEnqMmi = pMmiCmd;
					mCurrentMmiID = pMmiId;
					Log.v(TAG, "Ans len = " + mCIEnqMmi.LengthOfAnswer+"PromptText = " + mCIEnqMmi.PromptText);
					try {
						synchronized (mEventsCallback) {
							for (TVCIControlCallback listener : mEventsCallback) {
								listener.onEvent(mSlotID,ITVCIControl.CI_OPENENQUIRY_WIDGET,0);
							}
						}
					}catch(TransactionTooLargeException e) {
						Log.e(TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(TAG,"DeadObjectException !!!");
					}catch (Exception e) {
						Log.e(TAG,"Exception in onMmiCmdEnq:"+e.toString());	
					}
				}
			});
		}

		@Override
		public void onMmiCmdList(final int pMmiId,final CIMmiMenuList pMmiCmd) {
			Log.d(TAG, "OnMmiCmdList is called");
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					mCurrentMmiID = pMmiId;
					mCIListMmi = pMmiCmd;
					if(mCIListMmi.NumberOfChoices > 0){
						mListChoiceExists = true;
					}
					else{
						mListChoiceExists = false;
					}
					try {
						synchronized (mEventsCallback) {
							for (TVCIControlCallback listener : mEventsCallback) {
								listener.onEvent(mSlotID,ITVCIControl.CI_OPENLIST_WIDGET,0);
							}
						}
					}catch(TransactionTooLargeException e) {
						Log.e(TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(TAG,"DeadObjectException !!!");
					}catch (Exception e) {
						Log.e(TAG,"Exception in onMmiCmdList:"+e.toString());	
					}
				}
			});
		}

		@Override
		public void onMmiCmdMenu(final int pMmiId,final CIMmiMenuList pMmiCmd) {
			Log.d(TAG, "OnMmiCmdMenu is called:");
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					mCIMenuMmi = pMmiCmd;
					mCurrentMmiID = pMmiId;
					try {
						synchronized (mEventsCallback) {
							for (TVCIControlCallback listener : mEventsCallback) {
								listener.onEvent(mSlotID,ITVCIControl.CI_OPENMENU_WIDGET,0);
							}
						}
					}catch(TransactionTooLargeException e) {
						Log.e(TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(TAG,"DeadObjectException !!!");
					}catch (Exception e) {
						Log.e(TAG,"Exception in onMmiCmdMenu:"+e.toString());	
					}
				}
			});
		}

		@Override
		public void onMmiOpenRequest(final int pMmiId) {
			Log.d(TAG, "OnMmiOpenRequest is called");
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					mCurrentMmiID = pMmiId;
					try{
						synchronized (mEventsCallback) {
							for (TVCIControlCallback listener : mEventsCallback) {
								listener.onEvent(mSlotID,ITVCIControl.CI_OPENMMI_WIDGET,0);
							}
						}
					}catch(TransactionTooLargeException e) {
						Log.e(TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(TAG,"DeadObjectException !!!");
					}catch(Exception e){
						Log.e(TAG,"Exception:"+e.toString());	
					}
				}
			});
		}

		@Override
		public void onHCReleaseReply(int pReleaseReply) {
			Log.d(TAG,"Calling OnHCReleaseReply to PlayTVFacMediaPlayer!!:"+pReleaseReply);
			if(pReleaseReply == 0)
			{
				mIsHCAskReleased = true;
			}
		}

		@Override
		public void onHCTuneRequested(final int pNetworkID,final int pOrgNetWorkId,final int pTsID,final int pSeriveId) {
			Log.v(TAG, "onHCTuneRequested <ONID, TSID, SID> = <" + pOrgNetWorkId + ", " + pTsID + ", " + pSeriveId + ">"+"mCAMUpgrInProgress:"+mCAMUpgrInProgress);
			Runnable runnable = new Runnable(){
				public void run(){
					mHCSvcId = pSeriveId;
					boolean isFallbackQueryReqd = false;
					if((mHCSvcId == 0) || (mCAMUpgrInProgress == true))
						isFallbackQueryReqd = true;
					Map<String, String>  mHCTuneHeaders = TvURIHelper.getHeadersForTriplet(mContext,pOrgNetWorkId,pTsID,pSeriveId,isFallbackQueryReqd);
					if(mHCTuneHeaders != null && mHCTuneHeaders.size() > 0){
						//mHCTuneHeaders.put(TvHeaders.PRESET_ID,Integer.toString(0));
						mHCTuneHeaders.put(TvHeaders.SELECTION_TYPE,Integer.toString(TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value));
						//Log.d(TAG,"freq= " + mHCTuneHeaders.get(TvHeaders.FREQUENCY) + "Preset= " + mHCTuneHeaders.get(TvHeaders.PRESET_ID) + " vpid:apid:pcrpid "+ mHCTuneHeaders.get(TvHeaders.VIDEO_PID) + ":" + mHCTuneHeaders.get(TvHeaders.AUDIO_PID) + ":" + mHCTuneHeaders.get(TvHeaders.PCR_PID));
						mIsHCinProgress = true;
						mIsHCAskReleased = false;
						if(mCAMUpgrInProgress == true){
							mIsHCforCAMupgrade = true;
						}
						else{
							mIsHCforCAMupgrade = false;
						}

						if(Integer.parseInt(mHCTuneHeaders.get(TvHeaders.PRESET_ID)) == mPresetNumber){
							mIsHCTuneToSameSvc = true;	
						}
						mPreviousChannelHeader = TvURIHelper.getUriHeaders(mContext , mPreviousChannelUri);
						
						String completeUri = mHCTuneHeaders.get(TvHeaders.COMPLETE_URI);
						if(completeUri != null) {
							mHCTuneHeaders.put(TvHeaders.REQUEST_TYPE,ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT);
							mPlayTvmpl.PlayChannel(Uri.parse(completeUri),mHCTuneHeaders);							
						}else {
							mPlayTvmpl.PlayChannel(mPlayTvmpl.getCurrentUri(),mHCTuneHeaders);
						}
					} else {
						if(mITvMediaCI != null){
							mITvMediaCI.hCTuneReply(ITvMediaCI.HC_TUNE_FAILED);
						} else {
							Log.d(TAG,"ITvMediaCI is null not sending failure to TvServer ");
						}
					}
				}
			};
			mHandler.post(runnable);
		}

		@Override
		public void onHCTuneRequestedDVBC(final int serviceId,final CIHcCDSD cDesc,final boolean isCAMPMTAvailable) {
			Log.v(TAG, "OnHCTuneRequestedDVBC is called mCAMUpgrInProgress:"+mCAMUpgrInProgress);
			Runnable runnable = new Runnable(){
				public void run(){
                    if(mHCSvcId == serviceId)
                        mIsHCTuneToSameSvc = true;
					mHCSvcId = serviceId;
					Map<String, String> headers = new HashMap<String, String>();;
					if(mCAMUpgrInProgress == true){
						mIsHCforCAMupgrade = true;
					}
					else{
						mIsHCforCAMupgrade = false;
					}
					headers.put(TvHeaders.MODE, Integer.toString(TvHeaders.MODE_DVBC));
					headers.put(TvHeaders.FREQUENCY, Integer.toString(cDesc.frequency));
					headers.put(TvHeaders.SYMBOL_RATE, Integer.toString(cDesc.symbolRate));
					headers.put(TvHeaders.SERVICE_ID, Integer.toString(serviceId));
					headers.put(TvHeaders.SELECTION_TYPE,Integer.toString(TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value));
					headers.put(TvHeaders.VIDEO_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.AUDIO_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.PCR_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.VIDEO_STREAM_TYPE,Integer.toString(0));
					headers.put(TvHeaders.AUDIO_STREAM_TYPE,Integer.toString(0));
					headers.put(TvHeaders.CACHE_ID, Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_DIGITAL));
					headers.put(TvHeaders.PRESET_ID,Integer.toString(0));
					mIsHCinProgress = true;
					mIsHCAskReleased = false;
					mPreviousChannelHeader = TvURIHelper.getUriHeaders(mContext , mPreviousChannelUri);
					mPlayTvmpl.PlayChannel(mPlayTvmpl.getCurrentUri(),headers);
				}
			};
			mHandler.post(runnable);
		}

		@Override
		public void onHCTuneRequestedDVBC2(int arg0, CIHcC2DSD arg1, boolean isCAMPMTAvailable) {
		}

		@Override
		public void onHCTuneRequestedDVBS(final int serviceId,final CIHcSDSD sDesc,final boolean isCAMPMTAvailable) {
			Log.v(TAG, "OnHCTuneRequestedDVBS is called mCAMUpgrInProgress:"+mCAMUpgrInProgress);
			Runnable runnable = new Runnable(){
				public void run(){
					mHCSvcId = serviceId;
					Map<String, String> headers = new HashMap<String, String>();
					if(mCAMUpgrInProgress == true){
						mIsHCforCAMupgrade = true;
					}
					else{
						mIsHCforCAMupgrade = false;
					}
					String[] PROJECTION = {
							TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA
					};
					int _id = Integer.parseInt(mPlayTvmpl.getCurrentUri().getLastPathSegment());	
					String [] selectionArgs = {Integer.toString(_id)};
					String selection  = TvContract.Channels._ID + " = ?";
					Cursor cursor = mContext.getContentResolver().query(TvContract.Channels.CONTENT_URI,PROJECTION,selection, selectionArgs, null);
					if(cursor!=null){
						try{
							if((cursor.getCount()>0) && (cursor.moveToFirst())){
								byte[] lInternalData		 = cursor.getBlob(cursor.getColumnIndex(TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA));
								IIntKeyValueables keyvals	 = IIntKeyValueables.Instance.getInterface();				
								try{
									keyvals.setBlob(lInternalData);	
									int lnbNumber = keyvals.getInt(ITvContractExtras.C_LNBNUMBER);	
									ITvSettingsManager globalSettings 	= ITvSettingsManager.Instance.getInterface();
									int lnbType = globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE,lnbNumber,0);
									if (-1 == lnbNumber || -1 == lnbType) {
										Log.e(TAG,"Error getting LNB Details from the SatInfoTable : lnbNumber "+ lnbNumber + ", LnbType " + lnbType);
									}
									headers.put(TvHeaders.MODE, Integer.toString(TvHeaders.MODE_DVBS));
									headers.put(TvHeaders.SYMBOL_RATE, Integer.toString(sDesc.symbolRate));
									headers.put(TvHeaders.FREQUENCY, Integer.toString(sDesc.frequency));
									headers.put(TvHeaders.POLARIZATION, Integer.toString(sDesc.polarization));
									headers.put(TvHeaders.LNB_NUMBER, Integer.toString(lnbNumber));
									headers.put(TvHeaders.LNB_TYPE, Integer.toString(lnbType));
									headers.put(TvHeaders.SERVICE_ID, Integer.toString(serviceId));
									headers.put(TvHeaders.SELECTION_TYPE, Integer.toString(TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value));
									headers.put(TvHeaders.VIDEO_PID,Integer.toString(0x1FFF));
									headers.put(TvHeaders.AUDIO_PID,Integer.toString(0x1FFF));
									headers.put(TvHeaders.PCR_PID,Integer.toString(0x1FFF));
									headers.put(TvHeaders.VIDEO_STREAM_TYPE,Integer.toString(0));
									headers.put(TvHeaders.AUDIO_STREAM_TYPE,Integer.toString(0));
									headers.put(TvHeaders.CACHE_ID, Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCH_SATELLITE));
									mIsHCinProgress = true;
									mIsHCAskReleased = false;
								}
								catch(Exception e){
									Log.e(TAG,"Exception caught onHCTuneRequestedDVBS:"+e.toString());
								}
								mPreviousChannelHeader = TvURIHelper.getUriHeaders(mContext , mPreviousChannelUri);
								mPlayTvmpl.PlayChannel(mPlayTvmpl.getCurrentUri(),headers);
							}
						}finally
						{
							if(cursor != null){
								cursor.close();
								cursor = null;
							}
						}	
					}
				}
			};
			mHandler.post(runnable);
		}

		@Override
		public void onHCTuneRequestedDVBS2(int arg0, CIHcS2DSD arg1) {
		}

		@Override
		public void onHCTuneRequestedDVBT(final int serviceId,final CIHcTDSD tDesc,final boolean isCAMPMTAvailable) {
			Log.v(TAG, "OnHCTuneRequestedDVBT is called freq:"+tDesc.centreFrequency+"BW:"+tDesc.centreFrequency+"streamprio = "+tDesc.priority+"serviceId = "+serviceId+"isCAMPMTAvailable="+isCAMPMTAvailable+"mCAMUpgrInProgress:"+mCAMUpgrInProgress);
			Runnable runnable = new Runnable(){
				public void run(){
					mHCSvcId = serviceId;
					Map<String, String> headers = new HashMap<String, String>();
					if(mCAMUpgrInProgress == true){
						mIsHCforCAMupgrade = true;
					}
					else{
						mIsHCforCAMupgrade = false;
					}
					headers.put(TvHeaders.MODE, Integer.toString(TvHeaders.MODE_DVBT));
					headers.put(TvHeaders.FREQUENCY, Integer.toString(tDesc.centreFrequency));
					headers.put(TvHeaders.BANDWIDTH, Integer.toString(tDesc.bandwidth));
					headers.put(TvHeaders.STREAM_PRIORITY, Integer.toString(tDesc.priority));
					headers.put(TvHeaders.SERVICE_ID, Integer.toString(serviceId));

					if(isCAMPMTAvailable == true){
						headers.put(TvHeaders.SELECTION_TYPE, Integer.toString(TvURIHelper.SelectionType.SELECTION_CAMPMT.value));
					}else {
						headers.put(TvHeaders.SELECTION_TYPE, Integer.toString(TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value));
					}
					headers.put(TvHeaders.VIDEO_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.AUDIO_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.PCR_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.VIDEO_STREAM_TYPE,Integer.toString(0));
					headers.put(TvHeaders.AUDIO_STREAM_TYPE,Integer.toString(0));
					headers.put(TvHeaders.CACHE_ID, Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_DIGITAL));
					mIsHCinProgress = true;
					mIsHCAskReleased = false;
					mPreviousChannelHeader = TvURIHelper.getUriHeaders(mContext , mPreviousChannelUri);
					mPlayTvmpl.PlayChannel(mPlayTvmpl.getCurrentUri(),headers);
				}
			};
			mHandler.post(runnable);
		}

		@Override
		public void onHCTuneRequestedDVBT2(final int serviceId,final CIHcT2DSD t2Desc,final boolean isCAMPMTAvailable) {
			Runnable runnable = new Runnable(){
				public void run(){
					mHCSvcId = serviceId;
					Map<String, String> headers = new HashMap<String, String>();;
					Log.v(TAG, "OnHCTuneRequestedDVBT2 is called:"+mCAMUpgrInProgress);
					if(mCAMUpgrInProgress == true){
						mIsHCforCAMupgrade = true;
					}
					else{
						mIsHCforCAMupgrade = false;
					}
					headers.put(TvHeaders.MODE, Integer.toString(TvHeaders.MODE_DVBT2));
					headers.put(TvHeaders.FREQUENCY, Integer.toString(t2Desc.centreFreq));
					headers.put(TvHeaders.BANDWIDTH, Integer.toString(t2Desc.bandWidth));
					headers.put(TvHeaders.PLP_ID, Integer.toString(t2Desc.plpId));
					headers.put(TvHeaders.SERVICE_ID, Integer.toString(serviceId));
					headers.put(TvHeaders.SELECTION_TYPE, Integer.toString(TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value));
					headers.put(TvHeaders.VIDEO_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.AUDIO_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.PCR_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.VIDEO_STREAM_TYPE,Integer.toString(0));
					headers.put(TvHeaders.AUDIO_STREAM_TYPE,Integer.toString(0));
					headers.put(TvHeaders.CACHE_ID, Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_DIGITAL));
					mIsHCinProgress = true;
					mIsHCAskReleased = false;
					mPreviousChannelHeader = TvURIHelper.getUriHeaders(mContext , mPreviousChannelUri);
					mPlayTvmpl.PlayChannel(mPlayTvmpl.getCurrentUri(),headers);
				}
			};
			mHandler.post(runnable);
		}
	}

	class MediaChangeListener extends IonMediaChangeListener{
		@Override
		public void onMediaStateChanged(int arg0) {
		}

		@Override
		public void onLockStatusChanged(int type, int status) {
			if(isTvPinHasPriority()){
				boolean tempStatus = (status != 0);
				try {
					if((tempStatus == false) && (tempStatus != mLockStatus)){
						enableMMI(true);
					}
					if((tempStatus == true)){
						enableMMI(false);
					}
					mLockStatus = tempStatus;
				} catch (Exception e) {
					Log.e(TAG,"Exception in onLockStatusChanged:"+e.toString());
				}
			}
		}

		@Override
		public void onScramblingStatusChanged(int arg0, int arg1) {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					int lScramblingStatus = 0;
					lScramblingStatus = mITvMediaControl.getCurrentScramblingStatus();
					if(lScramblingStatus == ScramblingStatus.ProgramToBePurchased.value)
					{
						try {
							synchronized (mEventsCallback) {
								for (TVCIControlCallback listener : mEventsCallback) {
									listener.onEvent(mSlotID,ITVCIControl.CI_PROGRAMTOBEPURCHASED,0);
								}
							}

						}catch(TransactionTooLargeException e) {
							Log.e(TAG,"TransactionTooLargeException !!!");
						}catch(DeadObjectException e) {
							Log.e(TAG,"DeadObjectException !!!");
						}catch (Exception e) {
							Log.e(TAG,"Exception in onScramblingStatusChanged:"+e.toString());
						}

					}
					else if(lScramblingStatus == ScramblingStatus.ProgramNotEntitled.value)
					{
						try {
							synchronized (mEventsCallback) {
								for (TVCIControlCallback listener : mEventsCallback) {
									listener.onEvent(mSlotID,ITVCIControl.CI_PROGRAMNOTENTITLED,0);
								}
							}

						}catch(TransactionTooLargeException e) {
							Log.e(TAG,"TransactionTooLargeException !!!");
						}catch(DeadObjectException e) {
							Log.e(TAG,"DeadObjectException !!!");
						}catch (Exception e) {
							Log.e(TAG,"Exception in onScramblingStatusChanged:"+e.toString());
						}
					}
				}
			});
		}
	}

	public void addPurpose(int purpose) {
		mCurrentPurpose |= purpose;
		if( ((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_RECORDING)){
			Log.d(TAG,"Add Purpose is for recording.. so disabling Host control");
		}
	}

	public void removePurpose(int purpose) {
		if( ((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_RECORDING)){
			Log.d(TAG,"remove Purpose is for recording.. so enabling Host control");
		}
		mCurrentPurpose &= ~purpose;
		Log.i(TAG, "removePurpose : purpose changed to " + mCurrentPurpose );
	}

	public void HCEnable(boolean enable){
		Log.i(TAG,"Calling HCEnable to TvMediaCi with Value  = " + enable);
	}

	public void releaseHC(final Uri pCurrentUri,final  Map<String, String> pHeaders){
		Log.d(TAG,"Calling ReleaseHC to TvMediaCi");
		mUserSelectedURI = pCurrentUri;
		mUserSelectedHeader = pHeaders;
		mITvMediaCI.releaseHC();
	}
	
	public boolean onKey(View v, int keyCode, KeyEvent event) {
		Log.i(TAG,"onKey Called keyCode:"+keyCode);
		boolean retval = false;
		if(mAmmiSurfaceView != null && mAmmiSurfaceView.getTextureView() == v && mInteractiveService != null && mOverlayManager != null) {
			retval = mInteractiveService.onKeyEvent(event);
		} else {
			Log.i(TAG,"not send key to mheg:"+mAmmiSurfaceView+"service:"+mInteractiveService+"mOverlayManager:"+mOverlayManager);
		}
		return retval;
	}
	
	
	public boolean	onKeyDown(int keyCode){
		return isKeyConsumed(keyCode);
	}
	
	public boolean	onKeyUp(int keyCode){
		return isKeyConsumed(keyCode);
	}

	private boolean isKeyConsumed(int keyCode){
		boolean isConsumeed = false;
		if(mIsHCinProgress == true && isInZiggo()){
			isConsumeed = true;
		}
		else{
			isConsumeed = false;
		}
		Log.i(TAG,"isKeyConsumed called with keyCode = "+ keyCode+"isKeyConsumeed:"+isConsumeed);		
		return isConsumeed;
	}
	
	@Override
	public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,int presetNumber) {
		mIsSelectionInProgress = true;
		//stop() call towards MHEG on onPlayStarted
		if((mIsHCinProgress == false) && (mIsHCTuneToSameSvc == false)){
			notifyAMMiClose();
		}
			
		if(isTvPinHasPriority()){
			mLockStatus = false;
			if(mHandlerTimer != null){
				mHandlerTimer.removeCallbacks(mEnableMMI);
			}
			try {
				enableMMI(false);
			} catch (Exception e) {
				Log.e(TAG,"Exception in onPlayStarted:"+e.toString());
			}
		}
		if(headers!=null) {
			if(headers.containsKey(TvHeaders.MODE)){
				if(TvHeaders.MODE_ANALOG==
					Integer.parseInt(headers.get(TvHeaders.MODE))) {
						notifyAMMiCloseMW();
						enableCAMUI(false);
					}
				else {
					if(isWatchMain() || isFollowMain()){
						enableCAMUI(true);
					}
				}
			}
		}
	}

	private void resetMMITimer() {
		if(mHandlerTimer!=null){
			mHandlerTimer.removeCallbacks(mEnableMMI);
			mHandlerTimer.postDelayed(mEnableMMI, TIME_DELAY);
		}
		else{
			Log.d(TAG,"Inside resetMMITimer mLooperTimer is null or Timer is already started");
		}
	}

	Runnable mEnableMMI=new Runnable() {
		@Override
		public void run() {
			if(mLockStatus == false){
				try {
					enableMMI(true);
				} catch (Exception e) {
					Log.e(TAG,"Exception in enableMMI:"+e.toString());
				}
			} else {
				Log.d(TAG,"Channel is locked no need to enable MMI");
			}
		}
	};

	@Override
	public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,int presetNumber) {
			mIsSelectionInProgress = false;
			mPresetNumber = presetNumber;
			Log.v(TAG, "onPlayCompleted : presetNumber = " + mPresetNumber+"CurrentPurpose:"+mCurrentPurpose);
		if(mIsHCinProgress == false){
			mPreviousChannelUri = mediaPlayerUri;
		}
		if(mPlayCompletedRecvd == false){
			initHandler();
			if(isWatchMain() || isFollowMain()){
				registerCIChangeListener();
				enableMMI(true);
			}
			if((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY)==0) {
				if(PlayTvUtils.getLockStatus(mediaPlayerUri) == 0){
					updateCamStatus();
					statusCheckToShowCamWizard();
					mPlayCompletedRecvd = true;
				} else {
					Log.d(TAG, "onPlayCompleted: lockstatus updated to true = ");
				}
			}
		}

		if(mIsMMIEnableRequired){
			mIsMMIEnableRequired = false;
			enableMMI(true);
		}
		
		if(mIsHCinProgress == false){
		    mIsHCTuneToSameSvc = false;
		}
		
		if(mIsHCinProgress == true){
			if(isSignalPresent()){
				sendHCTuneReplyStaus(mHCSvcId);
                mIsHCTuneToSameSvc = false;
				lastHCTuneFailed = false;
			}
			else{
				mPlayTvmpl.hcReleased();
				mITvMediaCI.hCTuneReply(ITvMediaCI.HC_TUNE_FAILED);
				onHCTuneFailed();
			}
		}
		
		if(!mIsCamWizardToShow && (isWatchMain() || isFollowMain())){
			mIsCamWizardToShow = true;
			checkToShowCamWizard();
		}
	
		if(isTvPinHasPriority()){
			resetMMITimer();
		}
		if(isWatchMain() || isFollowMain()){
			createAmmiSurfaceView();
			setAmmiActivate();
		} 
		mHCSvcId = -1;
	}

	@Override
	public void onPlayFinished(Uri mediaPlayerUri, Medium medium,
			int presetNumber) {
	}
	
	private boolean isWatchMain(){
		boolean isWatchMain = false;
		if(mActionType == PlayTvUtils.MAIN_ACTION){
			if((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH){
				isWatchMain = true;
			}
		}
		return isWatchMain;
	}
	
	private boolean isFollowMain(){
		boolean isFollowMain = false;
		if(mActionType == PlayTvUtils.AUX_ACTION){
			if(((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) || 
				((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) == PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) ||
				((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) ||
				((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) ||
				((mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) == PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP)){
					isFollowMain = true;
			}					
		}
		return isFollowMain;
	}

	public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
		if((mIsHCinProgress == true) && (reason != IPlayTvStateChangeListener.TUNE_FAILED_REASON_CAM_VOD_IN_PROGRESS)){
			mITvMediaCI.hCTuneReply(ITvMediaCI.HC_TUNE_FAILED);
			mPlayTvmpl.hcReleased();
			mPlayTvmpl.onHCTuneBack(mPreviousChannelUri,mPreviousChannelHeader);
		}
	}

	@Override
	public void onInfo(boolean cicamAvailable) {
		final boolean camAvailable = cicamAvailable;
		Runnable r = new Runnable() {
			@Override
			public void run() {
				Log.v(TAG, "CI+_OnInfo camAvailable:"+camAvailable);
				if(camAvailable) {
					if (mITvMediaCI != null) {
						getSlotID();
						try{
							synchronized (mEventsCallback) {
								for (TVCIControlCallback listener : mEventsCallback) {
									listener.onEvent(mSlotID,ITVCIControl.CI_ACQUIRE,0);
								}
							}
						}catch(TransactionTooLargeException e) {
							Log.e(TAG,"TransactionTooLargeException !!!");
						}catch(DeadObjectException e) {
							Log.e(TAG,"DeadObjectException !!!");
						}catch(Exception e){
							Log.e(TAG,"Exception:"+e.toString());	
						}
						mITvMediaCI.AcquireCAM();
						mCamStatus =  mITvMediaCI.getCipStatus();					
					}
				}
				else {
					if((mMMIInProgress == true) || (mAMMIInProgress == true)){
						notifyAMMiClose();
						try{
							synchronized (mEventsCallback) {
								for (TVCIControlCallback listener : mEventsCallback) {
									listener.onEvent(mSlotID,ITVCIControl.CI_RELEASE,0);
								}
							}
						}catch(TransactionTooLargeException e) {
							Log.e(TAG,"TransactionTooLargeException !!!");
						}catch(DeadObjectException e) {
							Log.e(TAG,"DeadObjectException !!!");
						}catch(Exception e){
							Log.e(TAG,"Exception:"+e.toString());	
						}	
					}	
					if (mITvMediaCI != null) {
						try {
							mITvMediaCI.ReleaseCAM();
						} catch (Exception e) {
							Log.e(TAG,"Exception in onInfo ReleaseCAM:"+e.toString());
						}

					}
				}
			}
		};
		mHandler.post(r); 
	}

	@Override
	public void onError(PlayTvMediaPlayer mpl, int what , int extra) {
	}

	@Override
	public void onLockStatusChanged(int type, int status) {
	}
	@Override
	public void onPurposeChanged(int purpose) {
		Log.i(TAG,"onPurposeChanged:purpose->"+purpose+"mActionType:"+mActionType);
		if(mActionType == PlayTvUtils.MAIN_ACTION){
			if((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH){
				registerForCamNotifications();
				if(mCAMUpgrInProgress && isCamUpgradeCompleted()) {
					camUpgrAbortedCompleted();
				}
			}else {
				if((purpose == 0) && (mCAMUpgrInProgress)){
					camUpgrAbortedCompleted();
				}
				enableCINotification(false);
			}
		} else if(mActionType == PlayTvUtils.AUX_ACTION){
				if(((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) || 
					((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) == PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) ||
				   ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) ||
				   ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) ||
				   ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) == PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP)){
				   registerForCamNotifications();
				   if(mCAMUpgrInProgress && isCamUpgradeCompleted()) {
						camUpgrAbortedCompleted();
				   }
				} else {
					enableCINotification(false);
				}				
		}
	}

	@Override
	public void onCamUpgradeStarted(boolean status) {
	}

	@Override
	public void onUriChanged(Uri mediaPlayerUri) {

	}

	private boolean isCamUpgradeCompleted(){
		if(mITvMediaCI != null){
			int lCamUpgradeStatus = mITvMediaCI.getCAMUpgradeStatus();
			Log.i(TAG,"isCamUpgradeCompleted"+lCamUpgradeStatus);
			if(lCamUpgradeStatus == CAM_UPGRADE_COMPLETED || lCamUpgradeStatus == INVALID_CAM_UPGRADE){
				return true;
			}
		} else {
			Log.d(TAG,"isCamUpgradeCompleted called TVMediaCI is null");
		}
		return false;
	}
	
	private void sendHCTuneReplyStaus(final int pHCSvcId){
		if(pHCSvcId == 0){
			Log.d(TAG,"Calling HCTuneReply for svcId 0 with Value  = " + ITvMediaCI.HC_TUNE_SUCCESS_WITH_SVCID_0);
			mITvMediaCI.hCTuneReply(ITvMediaCI.HC_TUNE_SUCCESS_WITH_SVCID_0);
		}
		else{
			Log.d(TAG,"Calling HCTuneReply to TvMediaCi with Value  = " + ITvMediaCI.HC_TUNE_SUCCESS);
			mITvMediaCI.hCTuneReply(ITvMediaCI.HC_TUNE_SUCCESS);
		}
		if((mIsHCTuneToSameSvc == false) || ((mIsHCTuneToSameSvc == true) && (lastHCTuneFailed == false))){
			notifyAMMiClose();
		}
		else{
			Log.d(TAG, "Not calling notifyAMMiClose :"+" mIsHCTuneToSameSvc = " + mIsHCTuneToSameSvc + " lastHCTuneFailed = " + lastHCTuneFailed);
		}
	}
	
	public void setLockStatusChanged(int type, int status){
		boolean tempStatus = (status != 0);
		Log.d(TAG, "Lock status: " + status + ", boolean converted: " + tempStatus+"mLockStatus:"+mLockStatus);
		try {
			if((tempStatus == false) && (tempStatus != mLockStatus)){
				enableMMI(true);
			}
			if((tempStatus == true)){
				enableMMI(false);
			}
			mLockStatus = tempStatus;
		} catch (Exception e) {
			Log.e(TAG,"Excetpion in setLockStatusChanged:"+e.toString());
		}
	}

	private void updateCamStatus(){
		CICamIdInfo slot0CamIDINFO = getCamIDInfo(ITvMediaCI.SLOT0);
		if (slot0CamIDINFO != null) {
			if (slot0CamIDINFO.CamIDLen == 0 && slot0CamIDINFO.CamCisDataLen == 0) {
				if (mCamHelper.getCamStatusInDB(ITvMediaCI.SLOT0)) {
					mCamHelper.updateCamStatus(ITvMediaCI.SLOT0,false);
				}
			}
		} else {
			Log.d(TAG, "slot0CamIDINFO is null ");
		}
		CICamIdInfo slot1CamIDINFO = getCamIDInfo(ITvMediaCI.SLOT1);
		if (slot1CamIDINFO != null) {
			if (slot1CamIDINFO.CamIDLen == 0 && slot1CamIDINFO.CamCisDataLen == 0) {
				if (mCamHelper.getCamStatusInDB(ITvMediaCI.SLOT1)) {
					mCamHelper.updateCamStatus(ITvMediaCI.SLOT1,false);
				}
			}
		} else {
			Log.d(TAG, "slot1CamIDINFO is null ");
		}
	}

	private void statusCheckToShowCamWizard(){
		if(mITvMediaCI != null){
			mCamStatus = mITvMediaCI.getCipStatus();
			showCamWizard(mCamStatus);
		}
	}

	//CR: RMCR-2833  --> TV PIN entry to be shown first for Italy
	private boolean isTvPinHasPriority(){
		boolean retval = false;
		ITvSettingsManager mglobalSetting =  ITvSettingsManager.Instance.getInterface();
		int installedCountry = mglobalSetting.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		switch(installedCountry)
		{
		case TvSettingsDefinitions.InstallationCountryConstants.ITALY:
			retval = true;
			break;
		default:
			break;
		}
		Log.i(TAG, "isTvPinHasPriority retval : " + retval);
		return retval;
	}
	
	public void onCAMTuneRequested(boolean ena) {
	}

	@Override
	public Uri getLogoUri(Uri arg0, int arg1) {
		return null;
	}

	@Override
	public int getMediumFromUniqueId(int arg0) {
		return 0;
	}

	@Override
	public Uri getMuxesUri(Uri uri, String tableName) {
		Uri muxesUri=null;
		muxesUri=Uri.parse(uri.toString()+"/"+tableName);
		return muxesUri;
	}

	@Override
	public Uri getUriFromUniqueId(int arg0) {
		return null;
	}
}
