
package org.droidtv.tunerservice.tvmanager;

import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import java.util.Map;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import android.util.Log;
import android.net.Uri;
import android.content.Context;
import org.droidtv.tv.media.TvMediaPlayerContext;
import org.droidtv.tunerservice.TunerService;
import org.droidtv.tv.tvinput.TVCIControlCallback;
import org.droidtv.tunerservice.tvmanager.MainTVManager;
import org.droidtv.tunerservice.tvmpl.PlayTvCIPlusHandler;
import org.droidtv.tunerservice.interfaces.ICINotifyEvents;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.playback.TvAbstractPlayback;
import org.droidtv.tv.tvinput.ITVTunerSession;
import android.os.Handler;
import android.os.Looper;
import android.view.KeyEvent;
public class MainCIManager extends AbstractManager implements ICINotifyEvents{
	private static final String LOG_TAG  = "MainCIManager";
	//private Context mContext 						= null;
	private PlayTVFacMediaPlayer cplaytvmediaplayer 	= null;
	private PlayTVFacMediaPlayer tunerPlaytvmediaplayer = null;
	private PlayTVFacMediaPlayer pvrPlaytvmediaplayer 	= null;
	private PlayTVMediaPlayerFactory factory 			= null;
	private MainTVManager mMainTvManager 				= null;
	private PlayTvCIPlusHandler mCiPlusHandler			= null;
	private Handler mHandler						    = null;
	private static MainCIManager mMainCIManager;
	private	TvAbstractPlayback mTvAbstractPlayback = null;
	public MainCIManager(Context pContext){
		mContext			= pContext;
		setMainCIManager(this);
		mHandler			= new Handler(Looper.getMainLooper());
		factory				= PlayTVMediaPlayerFactory.getInstance();
		tunerPlaytvmediaplayer 	= factory.getDirectMPLInstance(mContext,PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_CI);
		cplaytvmediaplayer		= tunerPlaytvmediaplayer;//by default
		mCiPlusHandler			= new PlayTvCIPlusHandler(mContext,PlayTvUtils.MAIN_ACTION,cplaytvmediaplayer);
		tunerPlaytvmediaplayer.setCiPlusHandlerInstance(mCiPlusHandler);
		
		pvrPlaytvmediaplayer= factory.getDirectMPLInstance(mContext,PlayTVMediaPlayerFactory.REQUEST_TYPE_PVR_CI);
		pvrPlaytvmediaplayer.setCiPlusHandlerInstance(mCiPlusHandler);

		tunerPlaytvmediaplayer.registerListener(new PlaytvStateChangeCallbacks(tunerPlaytvmediaplayer),LOG_TAG);
		pvrPlaytvmediaplayer.registerListener(new PlaytvStateChangeCallbacks(pvrPlaytvmediaplayer),LOG_TAG);
		
		mTvAbstractPlayback = tunerPlaytvmediaplayer.getPlaybackObject();
		mTvAbstractPlayback.registerListener(new PlaybackListener(mCiPlusHandler));
	}
	
	private static void setMainCIManager(MainCIManager mainCIManager) {
		// TODO Auto-generated method stub
		mMainCIManager=mainCIManager;
	}

	public static MainCIManager getMainCIManagerInstance(){
		return mMainCIManager;
	}
	@Override
	public void setMainTvManager(MainTVManager maintvManager) {
		mMainTvManager = maintvManager;
	}
	
	@Override
	public void setOverlayManager(OverlayManager overlayManager){
		if(mCiPlusHandler != null){
			mCiPlusHandler.setOverlayManager(overlayManager);
		}
	}
	
	@Override	
	public Uri getSelectedURI(){
		Log.i(LOG_TAG,"getSelectedURI called");
		if(mMainTvManager != null) {
			return mMainTvManager.getSelectedURI();
		}	
		return null;
	}
	
	@Override	
	public Uri getNextURI(Uri uri){
		Log.i(LOG_TAG,"getNextURI called .... current uri passed = "+uri);
		if(mMainTvManager != null) {
			return mMainTvManager.getNextURI(uri);
		}
		return null;
	}

	@Override	
	public Uri getPreviousURI(Uri uri){
		Log.i(LOG_TAG,"getPreviousURI called .... current uri passed = "+uri);
		if(mMainTvManager != null) {
			return mMainTvManager.getPreviousURI(uri);
		}
		return null;
	}
	
	@Override
	public TvMediaPlayerContext getTvMediaPlayerContext(){
		TvMediaPlayerContext itmpc = null;
		if(cplaytvmediaplayer!=null) {
			itmpc = (TvMediaPlayerContext)cplaytvmediaplayer.getMediaPlayerInstance().getTvMediaPlayerContext();
		}
		return (TvMediaPlayerContext)itmpc;
	}
	
	@Override
	public void release(TunerService.TunerSession pSession){
		Log.i(LOG_TAG,"release called");
		cplaytvmediaplayer.setCiPlusHandlerInstance(null);
		cplaytvmediaplayer = null;
		mCiPlusHandler	   = null;
	}
	
	public void enableMMI(boolean enable) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.enableMMI(enable);
		}
	}
	
	public void updateMMIStatus(boolean status) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.updateMMIStatus(status);
		}
	}
	
	public void selectMMIItem(int menuType,int selectedItem) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.selectMMIItem(menuType,selectedItem);
		}
	}
	
	public String[] getMMIItems(int menuType) {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getMMIItems(menuType);
		}
		return null;
	}
	
	public int getLastSelectedMenuIndex() {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getLastSelectedMenuIndex();
		}
		return 0;
	}
	
	public void setEnquiryMMIResponse(String answer) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.setEnquiryMMIResponse(answer);
		}
	}
	
	public CIMmiEnq getEnquiryMMIInfo() {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getEnquiryMMIInfo();
		}
		return null;
	}
	
	public void cancelMMI(int menutype){
		if(mCiPlusHandler != null) {
			mCiPlusHandler.cancelMMI(menutype);
		}
	}

	public void enableCamUpgrade(boolean enable){
		if(mCiPlusHandler != null) {
			mCiPlusHandler.enableCamUpgrade(enable);
		}
	}
	
	public int getCAMUpgradeStatus() {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getCAMUpgradeStatus();
		}
		return 0;
	}
	
	public void updateCamInfo(CamInfo caminfo) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.updateCamInfo(caminfo);
		}
	}
	
	public void enableCAMUI(boolean enable) {
		//dummy
	}
	
	public CamInfo getCamInfo(int slotId) {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getCamInfo(slotId);
		}
		return null;
	}
	
	public void registerCIControlListener(TVCIControlCallback callback){
		if(mCiPlusHandler != null) {
			mCiPlusHandler.registerCIControlListener(callback);
		}	
	}

	public void unRegisterCIControlListener(TVCIControlCallback callback){
		if(mCiPlusHandler != null) {
			mCiPlusHandler.unRegisterCIControlListener(callback);
		}
	}
	@Override
	public void notifyChannelInstallStatus(boolean status,Medium medium){
		Log.i(LOG_TAG,"Channel Installtion Completed notifyChannelInstallComplete called:"+status+"medium:"+medium);
		if(mCiPlusHandler != null){
			if(status){
				mCiPlusHandler.dropCamInfoDB();
			}
			mCiPlusHandler.notifyChannelInstallStatus(status,medium);
		}else {
			Log.d(LOG_TAG,"not shown camwizard as PlayTvCIPlusHandler object is null");
		}
			
	}
	
	public boolean	onKeyDown(int keyCode, KeyEvent event){
		return mCiPlusHandler.onKeyDown(keyCode);
	}
	
	public boolean	onKeyUp(int keyCode, KeyEvent event){
		return mCiPlusHandler.onKeyUp(keyCode);
	}
	
	public class PlaytvStateChangeCallbacks implements IPlayTvStateChangeListener {
		private PlayTVFacMediaPlayer mPlaytvmpl = null;
		
		PlaytvStateChangeCallbacks(PlayTVFacMediaPlayer mpl) {
			mPlaytvmpl	= mpl;
		}
		
		@Override
		public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber) {
		}
		
		@Override
		public void onPlayCompleted(Uri mediaPlayerUri,  Map<String,String> headers, Medium medium, int presetNumber) {
		
				mHandler.post(new Runnable() {
					@Override
					public void run() {
						if((mPlaytvmpl.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) {
							cplaytvmediaplayer = mPlaytvmpl;
							mCiPlusHandler.setPlayer(cplaytvmediaplayer);
						} else {
							Log.i(LOG_TAG,"purpose is not WATCH_MAiN");
						}
					}
				});
		
			
		}
		
		@Override
		public void onPlayFinished(Uri mediaPlayerUri, Medium medium, int presetNumber) {
		}
		
		@Override
		public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
		}
		
		@Override
		public void onInfo(boolean cicamAvailable) {
		}
		
		@Override
		public void onError(PlayTvMediaPlayer mpl, int what , int extra) {
		}
		
		@Override
		public void onLockStatusChanged(int type, int status) {
		}
		
		@Override
		public void onPurposeChanged(int purpose) {
			//This will avoid to send onInfo on PVR token(Big Token)
			if((purpose == 0) && (mPlaytvmpl == pvrPlaytvmediaplayer)){
				mCiPlusHandler.setPlayer(tunerPlaytvmediaplayer);
			}
		}
		
		@Override
		public void onUriChanged(Uri mediaPlayerUri) {
		}
		
		@Override
		public void onCamUpgradeStarted(boolean status) {
		}
	}
	
	public class PlaybackListener implements ITvAbstractPlaybackListener {
		private PlayTvCIPlusHandler lCIPlusHandler = null;
		
		PlaybackListener(PlayTvCIPlusHandler pCIPlusHandler) {
			lCIPlusHandler	= pCIPlusHandler;
		}
		
		@Override
		public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber) {
		}
		
		@Override
		public void onPlayCompleted(Uri mediaPlayerUri,  Map<String,String> headers, Medium medium, int presetNumber) {
		}
		
		@Override
		public void onPlayFinished(Uri mediaPlayerUri, Medium medium, int presetNumber) {
		}
		
		@Override
		public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
		}
		
		@Override
		public void onInfo(boolean cicamAvailable) {
		}
		
		@Override
		public void onLicenseExchangeHappening(boolean status){
		}
		
		@Override
		public void onServiceTypeDetected(int type){
		}

		@Override
		public void onTrickModeEnabled(boolean status, int mode){
		}

		@Override
		public void onPlayStateChanged(int state, int mode){
			if(state !=  ITVTunerSession.TIMESHIFT_PLAYBACK_STATE_LIVE){
				lCIPlusHandler.setPlaybackStatus(true); //setting true when we are in time shift mode
			}else {
				lCIPlusHandler.setPlaybackStatus(false); //setting false when we are not in time shift mode
			}
		}

		@Override
		public void onSeekComplete(int mode){
		}

		@Override
		public void onTimeshiftInfoChanged(){
		}
		
		@Override
		public void onMPLPurposeChanged(int currentPurpose) {
		}
		
		@Override
		public void onLockStatusChanged(int type, int status) {
		}

		@Override
		public void onPlayError(int error, int what , int extra, int mode){
		}
		
	}
}
