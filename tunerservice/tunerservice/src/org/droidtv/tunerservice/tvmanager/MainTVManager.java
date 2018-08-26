package org.droidtv.tunerservice.tvmanager;

import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.lang.String;
import java.lang.Exception;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.preference.PreferenceActivity.Header;
import android.util.Log;
import android.net.Uri;
import android.view.Surface;
import android.view.View;
import android.media.tv.*;
import android.media.tv.TvInputService.Session;
import android.media.tv.TvTrackInfo;
import org.droidtv.tv.media.ITvMediaMultiFeed;
import org.droidtv.tv.media.ITvMediaMultiFeed.TvMediaMultiFeedInfo;
import org.droidtv.tv.media.ITvMediaRecordControl.PlaybackEitInfo;
import org.droidtv.tv.audio.IInputSound;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.media.TvMediaPlayerContext;
import org.droidtv.tv.media.BcstConstants;
import org.droidtv.tv.media.ITvMediaControl;
import org.droidtv.tv.media.ITvMediaControl.LockData;
import org.droidtv.tv.media.ITvMediaStream;
import org.droidtv.tv.media.ITvMediaStream.TvMediaAudioInfo;
import org.droidtv.tv.media.ITvMediaStream.TvMediaVideoInfo;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tunerservice.util.TvURIHelper.SelectionType;
import org.droidtv.tunerservice.TunerService;
import org.droidtv.tunerservice.subtitles.SubtitleHandler;
import org.droidtv.tunerservice.channelfilter.ChannelFilter;
import org.droidtv.tunerservice.iapp.MainIAppManager;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tunerservice.overlay.RadioBGHandler;
import org.droidtv.tunerservice.overlay.RecordingIcon;
import org.droidtv.tunerservice.overlay.ImageChView;
import org.droidtv.tunerservice.playback.TvAbstractPlayback;
import org.droidtv.tunerservice.playback.TvChannelPlayback;
import org.droidtv.tunerservice.playback.PvrPlayback;
import org.droidtv.tunerservice.interfaces.IPlayTvMPLFactoryCallback;
import org.droidtv.tunerservice.interfaces.IPowerEvents;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.interfaces.IAppManagerTunerCallBacks;
import org.droidtv.tunerservice.interfaces.ITunerRating;
import android.content.ContentValues;
import android.content.Intent;
import android.media.tv.TvContract.Channels;
import org.droidtv.tv.tvinput.CamInfoImpl;
import org.droidtv.tunerservice.interfaces.IClockHandlerCallBacks;//min.jiang add
import 	android.content.Context;
import org.droidtv.tv.tvpower.ITvPowerManager;

public class MainTVManager extends AbstractManager implements ITvAbstractPlaybackListener,IPlayTvMPLFactoryCallback,
                                                                     IClockHandlerCallBacks{
	private static final String LOG_TAG 				= "MainTVManager";
	//private Context mContext							= null;
	private Handler mHandler 							= null;
	private PlayTVFacMediaPlayer cplaytvmediaplayer       = null;  
	private PlayTVMediaPlayerFactory factory			= null;
	private Surface mSurface 							= null;
	private SubtitleHandler mSubtitleHandler 			= null;
	private	TvAbstractPlayback mainPlayback 			= null;
	private String msessionType							= ITVSessionContext.SESSION_TYPE_MAIN_WATCH;
	private static  RatingInterfaceManager mMainRatingInterfaceInstance = null;
	private MainIAppManager mIappManager = null;
	private boolean mBroadcastAVEnabled 				= true;
	private Session	mCurrentActiveSession				= null;
	private int mRequestType							= -1;
	private int mLastSelectedMode						= -1;
	private static IAppManagerTunerCallBacksImpl  mTunerCallBackListener 	= null;
	private TunerService.TunerSession mainSessionListener 			= null; 
	private String mSelectedMultifeedTrack 							= null;
	private static IPowerEvents mPowerEventListener = null;
	private RadioBGHandler mRadioBG = null;
	private RecordingIcon  mRecIcon = null;
	private ImageChView    mChView    = null;
	private boolean wakeupSelection = true;
	private boolean wakeupFromDDR	= false;
	private String mTuneSubType		= null;
	private Looper mTvLooper = null;
	private HandlerThread thread = null;
	private boolean mLockDisabled		= false;
	private boolean mCloneLockData		= false;
	private LockData mCachedLockData	= null;
	private boolean mCachedLockStatus	= false;
	private static final int DEFAULT_PID= 0x1FFF;
	private boolean isMediaListenerRegistered	= true;
	private OverlayManager mOverlayManager = null;

	private static final String InstallFlag = "value";	
	private static final String Dt_Chid = "DT_CHID";

	public MainTVManager(Context pContext){
		Log.i(LOG_TAG,"creating MainTVManager");		
		mContext		= pContext;	
		mCachedLockData	= new LockData();	
		mHandler 		= new Handler();
		factory			= PlayTVMediaPlayerFactory.getInstance();
		factory.registerListener(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH, this);
		initModules();		
		createMainRatingInterface(this);
		mMainRatingInterfaceInstance.setContext(pContext);
	}
	
	public void MainTvManagerInit(){
		if ( thread == null)
		{
			thread = new HandlerThread("MainTvManagerThread");
			thread.start();
			mTvLooper = thread.getLooper();
			mTvHandler = new TvManagerHandler(mTvLooper);
		}
		createPowerEventListener(this);
	}
	
	private static void createMainRatingInterface(MainTVManager mMainTVManager){
		mMainRatingInterfaceInstance= mMainTVManager.new RatingInterfaceManager();
	}
	
	private static void createPowerEventListener(MainTVManager mMainTVManager){
		mPowerEventListener = mMainTVManager.new PowerEventsReceiver();
	}
	
	private void initModules() {		
		mSubtitleHandler		 	= new SubtitleHandler(mContext);		
		mIappManager 				= new MainIAppManager(mContext);
		mRadioBG 					= new RadioBGHandler();
		mRecIcon					= new RecordingIcon(mContext);
		mChView						= new ImageChView(mContext);
		mTunerCallBackListener 		= new IAppManagerTunerCallBacksImpl(); 		
		mIappManager.setIAppManagerTunerCallBacksListener(mTunerCallBackListener);	
	}
	public void	setOverLayViewStatus(final int overlayViewStatus){
		if(mOverlayManager  != null){
			mOverlayManager.setOverLayViewStatus(overlayViewStatus);
		}
	}	
	@Override
	public void setOverlayManager(OverlayManager overlayManager){
		Log.i(LOG_TAG,"registerOverlayManager called");
		if(mOverlayManager != null && overlayManager == null){
			mOverlayManager.release();
		}
		mOverlayManager = overlayManager;
		mSubtitleHandler.setOverlayManager(overlayManager);
		mIappManager.setOverlayManager(overlayManager);
		mRadioBG.setOverlayManager(overlayManager);
		mRecIcon.setOverlayManager(overlayManager);
		mChView.setOverlayManager(overlayManager);
	}
	
	@Override
	protected void notifyLockStatusChanged(int type, int status) {
		super.notifyLockStatusChanged(type, status);
		if(mRadioBG != null){
			mRadioBG.onLockStatusChanged(type, status);
		}
	}

	@Override
	public void release(final TunerService.TunerSession pSession){
		Log.i(LOG_TAG,"release called ");
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(pSession == mCurrentActiveSession) {
					if(cplaytvmediaplayer != null) {
						setSurface(null);
						unRegisterOnMediaChangeListener();
						unRegisterOnMediaStreamChangeListener();
						unRegisterOnMediaStreamLinkageInfoListener();
						unregisterforContentObserver();
						unregisterforHTVContentObserver();
						if(mainPlayback != null) {
							mainPlayback.unRegisterListener(MainTVManager.this);
							mainPlayback = null;
						}
						if(mIappManager != null){
							mIappManager.onSessionRelease();
						}
						setOverlayManager(null);
						cplaytvmediaplayer.suppressMute();
						factory.releaseMPLInstance(mRequestType,cplaytvmediaplayer);
						mSelectedMultifeedTrack = null;
						cplaytvmediaplayer 		= null;
						mRequestType			= -1;
						msessionType			= ITVSessionContext.SESSION_TYPE_MAIN_WATCH;
						notifyChannelRetuned(null);
						notifyReAcquireInterfaces(); //towards observer sessions
						mTriggerReAcquireInterfaces = true;
						mBroadcastAVEnabled = true;
					}else {
						//release overlay mediaplayer cleaned in onError case
						setOverlayManager(null);
					}
					mCurrentActiveSession	= null;	
				}	
			}
		};
		mHandler.post(r);	
	}

	@Override
	public void setSession(final Session session, final Surface surface) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
				mCurrentActiveSession 	= session;
				mSurface 				= surface;
			}
		};
		mHandler.post(r);			
	}
	
	@Override
	public void onPlayError(int error, int what, int extra, int mode) {
		super.onPlayError(error, what, extra, mode);
		//should not release overlay/session here because the session from 
		//main_watch is not released
		if(error==ITvAbstractPlaybackListener.PLAYERROR_FACTORY) {
			if(cplaytvmediaplayer!=null){
				cplaytvmediaplayer.setAVSurface(null);
				unRegisterOnMediaChangeListener();
				unRegisterOnMediaStreamChangeListener();
				unRegisterOnMediaStreamLinkageInfoListener();
				unregisterforContentObserver();
				unregisterforHTVContentObserver();
				Runnable r = new Runnable() {
					@Override
					public void run() {
						if(mainPlayback != null) {
							mainPlayback.unRegisterListener(MainTVManager.this);
							mainPlayback = null;
						}
					}
				};
				mHandler.post(r);
				
				if(mIappManager != null){
					mIappManager.onSessionRelease();
				}
				cplaytvmediaplayer.suppressMute();
				factory.releaseMPLInstance(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH,cplaytvmediaplayer);
				mSelectedMultifeedTrack = null;
				cplaytvmediaplayer 		= null;
				mRequestType			= -1;
				msessionType			= ITVSessionContext.SESSION_TYPE_MAIN_WATCH;
				notifyChannelRetuned(null);
				notifyReAcquireInterfaces(); //towards observer sessions
				mTriggerReAcquireInterfaces = true;
				mBroadcastAVEnabled = true;
			}
		}
	}

	@Override
	public Session getCurrentActiveSession() {
		return mCurrentActiveSession;
	}
   
    @Override
    public void setSurface(Surface pSurface){
		if(cplaytvmediaplayer != null) {
			Log.v(LOG_TAG,"setSurface!!! ");
			if(mBroadcastAVEnabled){
				cplaytvmediaplayer.setAVSurface(pSurface);
			}else {
				mIappManager.setAVSurface(pSurface);
			}
		}		
		mSurface = pSurface;
	}
	
	@Override
	public void dispatchSurfaceChanged(int pFormat, int pWidth, int pHeight, Surface pSurface) {
		if(cplaytvmediaplayer != null) {
			Log.v(LOG_TAG,"dispatchSurfaceChanged " + pWidth + "x" + pHeight);
			mSurface = pSurface;
			if(mBroadcastAVEnabled){
				cplaytvmediaplayer.setAVSurface(mSurface);
			}else {
				mIappManager.setAVSurface(mSurface);
			}
		}
	}
	@Override
	public void selectTrack(int type, String trackId){
		Log.i(LOG_TAG,"selectTrack called with type = "+type+" and trackId = "+trackId);
		
		try{
			ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
			ITvMediaStream tvms 	= getTvMediaPlayerContext().getTvMediaStream();
			
			if(trackId != null) {
				String[] parts = trackId.split(":");
				trackId = parts[1];
				if(type == TvTrackInfo.TYPE_AUDIO) {
					int noAudio = tvms.getCurrentNoOfAudio();
					if(noAudio > Integer.parseInt(trackId)) {
//						TvMediaAudioInfo mAudioInfo =  new TvMediaAudioInfo();
						TvMediaAudioInfo mAudioInfo= tvms.getCurrentAudioInfo(Integer.parseInt(trackId));
						TvMediaAudioInfo currentAudInfo = tvmc.getTVAudio();
						if((currentAudInfo.pid != mAudioInfo.pid) || (currentAudInfo.langCode != mAudioInfo.langCode) 
						   || (currentAudInfo.type != mAudioInfo.type)) {
							tvmc.stopTVMedia(ITvMediaControl.MEDIA_AUDIO);
							tvmc.playTVAudio(mAudioInfo);
						} else {
							Runnable r = new Runnable() {
								@Override
								public void run() {
									notifyMediaStateChanged(ITvMediaControl.MEDIA_AUDIO);
								}
							};
							mHandler.post(r);
						}
					}
				}else if(type == TvTrackInfo.TYPE_VIDEO) {
					int noVideo = tvms.getCurrentNoOfVideo();
					if(noVideo > Integer.parseInt(trackId)) {
						TvMediaVideoInfo mVideoInfo 	= tvms.getCurrentVideoInfo(Integer.parseInt(trackId));
						int pid = tvmc.getTVMedia(ITvMediaControl.MEDIA_VIDEO);
						if(pid != mVideoInfo.pid) {
							tvmc.stopTVMedia(ITvMediaControl.MEDIA_VIDEO);
							tvmc.playTVMedia(ITvMediaControl.MEDIA_VIDEO,mVideoInfo.pid);
						}else {
							Runnable r = new Runnable() {
								@Override
								public void run() {
									notifyMediaStateChanged(ITvMediaControl.MEDIA_VIDEO);
								}
							};
							mHandler.post(r);
						}
					}
				}else if(type == TvTrackInfo.TYPE_SUBTITLE) {
					if(mSubtitleHandler!=null) {
						mSubtitleHandler.onSubtitleIndexSelected(Integer.parseInt(trackId));
					}
				}else {
					Log.i(LOG_TAG,"selectTrack called with invalid type = "+type);
				}
			}else {
				if(type == TvTrackInfo.TYPE_AUDIO) {					
					tvmc.stopTVMedia(ITvMediaControl.MEDIA_AUDIO);
				}else if(type == TvTrackInfo.TYPE_VIDEO) {					
					tvmc.stopTVMedia(ITvMediaControl.MEDIA_VIDEO);
				}else if(type == TvTrackInfo.TYPE_SUBTITLE) {
					if(mSubtitleHandler!=null) {
						//to disable?
						mSubtitleHandler.onSubtitleIndexSelected(-2);
						Runnable r = new Runnable() {
							@Override
							public void run() {
								notifyMediaStateChanged(ITvMediaControl.MEDIA_SUBTITLE);
							}
						};
						mHandler.post(r);
					}
				}else {
					Log.i(LOG_TAG,"selectTrack called with invalid type = "+type);
				}
			}
			
		}
		catch(Exception e){
			Log.d(LOG_TAG,"selectTrack : Exception: "+e.toString());
		}		
	}
	
	@Override
	public void unselectTrack(int type){
		Log.i(LOG_TAG,"unselectTrack called with type = "+type);		
		try{
			ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
			if(type == TvTrackInfo.TYPE_AUDIO) {					
				tvmc.stopTVMedia(ITvMediaControl.MEDIA_AUDIO);
			}else if(type == TvTrackInfo.TYPE_VIDEO) {					
				tvmc.stopTVMedia(ITvMediaControl.MEDIA_VIDEO);
			}else if(type == TvTrackInfo.TYPE_SUBTITLE) {
				if(mSubtitleHandler!=null) {
					mSubtitleHandler.onSubtitleIndexSelected(-2);					
					Runnable r = new Runnable() {
						@Override
						public void run() {
							notifyMediaStateChanged(ITvMediaControl.MEDIA_SUBTITLE);
						}
					};
					mHandler.post(r);
				}
			}else {
				Log.i(LOG_TAG,"unselectTrack called with invalid type = "+type);
			}
		}		
		catch(Exception e){
			Log.d(LOG_TAG,"unselectTrack : Exception : "+e.toString());
		}			
	}
    
	@Override
    public void tune(Uri pChannelUri){
		Log.i(LOG_TAG,"tune called : " +pChannelUri);
		selectUri(pChannelUri,ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT,null,null,null);
	}
	
	@Override
	public void tune(Uri pChannelUri,Bundle params) {
		Log.i(LOG_TAG,"tune called with Bundle :");
		String tuneType 			= ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT;
		String tuneSubType			= null;
		String privDataCookie		= null;
		boolean restoreChannelState	= false;
		Map<String, String> headers = new HashMap<String, String>();
		boolean pidSelOnly 			= false;
		
		if(params != null) {			
			if(params.getString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE) != null) {
				tuneType 	= params.getString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE);
				tuneSubType = params.getString(ITVSessionContext.KEY_TUNE_REQUEST_SUB_TYPE);
				if(tuneType.equals(ITVSessionContext.TUNE_REQUEST_TYPE_CUSTOM)){					
					headers = TvURIHelper.getHeadersFromBundle(mContext,params);
				}
				if((tuneSubType != null) && (tuneSubType.equals(ITVSessionContext.TUNE_REQUEST_SUB_TYPE_PID_SELECTION))){
					pidSelOnly = true;
				}
			}
			if(params.getString(ITVSessionContext.KEY_PRIVATE_DATA_COOKIE) != null) {
				privDataCookie 	= params.getString(ITVSessionContext.KEY_PRIVATE_DATA_COOKIE);
			}
			if(params.containsKey(ITVSessionContext.KEY_RESTORE_CHANNEL_STATE)) {
				restoreChannelState	= params.getBoolean(ITVSessionContext.KEY_RESTORE_CHANNEL_STATE);
				headers.put(TvHeaders.RESTORE_CHANNEL_STATE,Integer.toString(restoreChannelState ? 1 : 0));
			}
			if(params.containsKey(TvHeaders.FORCE_CHANNEL_TUNING)) {
				headers.put(TvHeaders.FORCE_CHANNEL_TUNING, "1");
			}
		}
		if(pidSelOnly) {
			selectPid(pChannelUri,headers);
		}else {
			selectUri(pChannelUri,tuneType,tuneSubType,privDataCookie,headers);
		}
	}
	
	@Override
	public List<MultiFeedServiceInfo> getMultiFeedTracks(){
		Log.i(LOG_TAG,"getMultiFeedTracks called");		 
		ITvMediaMultiFeed tvMediaMultifeed 		=	getTvMediaPlayerContext().getTvMediaMultiFeed();
		int num		=	tvMediaMultifeed.getSubFeedsAvailable();
		List<MultiFeedServiceInfo> ret	= new ArrayList<MultiFeedServiceInfo>();
		
		for(int i = 0; i < num; i++){
			TvMediaMultiFeedInfo multifeed	= tvMediaMultifeed.getSubFeedData(i);
			MultiFeedServiceInfo serviceInfo = new MultiFeedServiceInfo();
			serviceInfo.mID = Integer.toString(i);//TODO: to be discussed
			Bundle bundle 	= new Bundle();
			bundle.putInt("onid",multifeed.onId);
			bundle.putInt("tsid",multifeed.tsId);
			bundle.putInt("sid",multifeed.serviceId);
			bundle.putString("name", multifeed.name);
			serviceInfo.mExtra	= bundle;
			ret.add(serviceInfo);
		}
		return ret;
	}	
	
	@Override
	public TimeshiftInfo getTimeshiftInfo(){
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				PlaybackEitInfo info = mainPlayback.getTimeshiftInfo();
				TimeshiftInfo TSInfo = new TimeshiftInfo();
				if (info != null) {
					TSInfo.eventName	= info.eventName;	
					TSInfo.shortInfo 	= info.shortInfo;	
					TSInfo.extendedInfo	= info.extendedInfo;	
					TSInfo.guidanceInfo	= info.guidanceInfo;	
					TSInfo.channelId	= info.uniqueId;	
					TSInfo.genre		= info.genre;		
					TSInfo.rating		= info.rating;		
				}			
				return TSInfo;
			} else {
				Log.d(LOG_TAG, "getTimeshiftInfo: ERROR, called on wrong object");
			}
		}
		return null;
	}

	@Override
	public String getSelectedMultiFeedTrack(){
		return mSelectedMultifeedTrack;
	}
	
	@Override
	public void enableAudio(boolean status){	
		if(cplaytvmediaplayer != null) {
			cplaytvmediaplayer.getMediaPlayerInstance().enableAudio(status);
		}
	}
	
	@Override
	public boolean getAudioStatus(){
		if(cplaytvmediaplayer != null) {
			return cplaytvmediaplayer.getMediaPlayerInstance().getAudioStatus();
		}
		return true;
	}
	
	@Override
	public int getCurrentMediaMode(){
		return (mBroadcastAVEnabled ? ITVTunerSession.MODE_BROADCAST : ITVTunerSession.MODE_BROADBAND);
	}
	
	@Override
	public void selectMultiFeedTrack(String multifeed){
		mSelectedMultifeedTrack		=	multifeed;
		final String trackId=multifeed;
		class RunSelectMultifeeduri implements Runnable {
			
			@Override
			public void run() {
				ITvMediaMultiFeed tvMediaMultifeed 		=	getTvMediaPlayerContext().getTvMediaMultiFeed();
				int num		=	tvMediaMultifeed.getSubFeedsAvailable();
				if(Integer.parseInt(trackId)<=num){
					for(int i = 0; i < num; i++){
						TvMediaMultiFeedInfo multifeedInfo	= tvMediaMultifeed.getSubFeedData(i);
						if(Integer.parseInt(trackId)==i){
							Map<String,String> headers=TvURIHelper.getHeadersForTriplet(mContext, multifeedInfo.onId, multifeedInfo.tsId, multifeedInfo.serviceId, true);
							if(headers!=null && headers.size()>0){
								headers.put(TvHeaders.SELECTION_TYPE,Integer.toString(SelectionType.SELECTION_MULTIFEED.value));
								if(mainPlayback!=null){
									Uri uri=getSelectedURI();
									int presetId=TvURIHelper.getPresetId(mContext,uri);
									headers.put(TvHeaders.SERVICE_ID,Integer.toString(multifeedInfo.serviceId));
									headers.put("Presetid", Integer.toString(presetId));
									mainPlayback.play(uri, headers);
								}
							}
						}

					}
				}
				
			}
		}
		RunSelectMultifeeduri runMultifeeduri = new RunSelectMultifeeduri();
		mHandler.post(runMultifeeduri);
		
	}
	
	@Override	
	public Uri getSelectedURI(){
		Uri selectedUri = null;
		
		if(cplaytvmediaplayer != null) {
			selectedUri = cplaytvmediaplayer.getCurrentUri();
		}
		
		if(null != selectedUri)
		Log.i(LOG_TAG, "getSelectedURI##"+selectedUri.toString());
		else
		Log.i(LOG_TAG, "getSelectedURI##NULL");
		
		return selectedUri;
	}
	
	@Override
	public byte[]  getOipfSiDescriptor(){
		if(getTvMediaPlayerContext() != null) {
			ITvMediaStream tvms 	= getTvMediaPlayerContext().getTvMediaStream();
			return tvms.getOipfSiDescriptor(false);
		}
		return null;
	}
	
	@Override
	public void pause(){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				mainPlayback.pause();
			} else {
				Log.d(LOG_TAG, "pause: ERROR, called on wrong object");
			}
		}
	}
	
	@Override
	public void stop(){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				mainPlayback.stop();
			} else {
				Log.d(LOG_TAG, "stop: ERROR, called on wrong object");
			}
		}
	}
	
	@Override
	public void resume(){          
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				mainPlayback.resume();
			} else {
				Log.d(LOG_TAG, "resume: ERROR, called on wrong object");
			}
		}
	}
	
	@Override
	public void seekTo(int pMsecs){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				mainPlayback.seekTo(pMsecs);
			} else {
				Log.d(LOG_TAG, "seekTo: ERROR, called on wrong object");
			}
		}
	}
	
	@Override
	public void setSpeed(int pSpeed, boolean pForward){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				mainPlayback.setSpeed(pSpeed, pForward);
			} else {
				Log.d(LOG_TAG, "setSpeed: ERROR, called on wrong object");
			}
		}
	}
	
	@Override
	public int getCurrentDuration(){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				return mainPlayback.getCurrentDuration();
			} else {
				Log.d(LOG_TAG, "getCurrentDuration: ERROR, called on wrong object");
			}
		}
		return 0;
	}
	
	@Override
	public int getTotalDuration(){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				return mainPlayback.getTotalDuration();
			} else {
				Log.d(LOG_TAG, "getTotalDuration: ERROR, called on wrong object");
			}
		}
		return 0;
	}
	
	@Override
	public int getBufferedDuration(){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				return (int)mainPlayback.getRecordedDuration();
			} else {
				Log.d(LOG_TAG, "getBufferedDuration: ERROR, called on wrong object");
			}
		}
		return 0;		
	}
	
	@Override
	public int getPlaybackState(){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				return mainPlayback.getPlaybackState();
			} else {
				Log.d(LOG_TAG, "getPlaybackState: ERROR, called on wrong object");
			}
		}
		return 0;				
	}
	
	@Override
	public void enableTrickModes(boolean pEnable){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				mainPlayback.enableTrickModes(pEnable);
			} else {
				Log.d(LOG_TAG, "enableTrickModes: ERROR, called on wrong object");
			}
		}				
	}
	
	@Override
	public boolean getTrickModeStatus(){
		if(mainPlayback != null) {
			if (mainPlayback instanceof PvrPlayback) {
				return mainPlayback.getTrickmodeStatus();
			} else {
				Log.d(LOG_TAG, "getTrickModeStatus: ERROR, called on wrong object");
			}
		}
		return true;
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
	public View getOverlayView() {
		return null;
	}
	
	@Override
	public void setSessionType(String sessionType) {
		msessionType = sessionType;
	}
    
    /*begin:min.jiang add 2015-07-09*/
    @Override
    public void OnClockSetResult(Uri uri, int result) {
        if(uri != null) {
            boolean clockcalibration = uri.getBooleanQueryParameter("clock_calibration", false);    
            Log.d(LOG_TAG, "OnClockSetResult uri: " + uri + ", clockcalibration " + clockcalibration + ", result: " + result);
            if(clockcalibration) {
                uri = PlayTvUtils.appendQueryParameter(uri, "clock_result", "" + result);  
                notifyonTuneCompleted("org.droidtv.tunerservice/.TunerService",uri,null);
                if(cplaytvmediaplayer != null) {
                     cplaytvmediaplayer.getClockHandler().RegisterCallBack(null);
                }
            }            
        }
    }
    
    /*end:min.jiang add*/
    
	private PlayTVFacMediaPlayer getPlaytvFacMediaPlayer() {
		return cplaytvmediaplayer;
	}
	
	private int getPlayerType(Medium medium) {
		switch(medium) {
			case MEDIUM_CABLE:
				return PlayTvMediaPlayer.PLAYER_TUNER;
			case MEDIUM_TERRESTRIAL:
				return PlayTvMediaPlayer.PLAYER_TUNER;
			case MEDIUM_SATELLITE:
				return PlayTvMediaPlayer.PLAYER_TUNER;
			case MEDIUM_EXTN:
				return PlayTvMediaPlayer.PLAYER_EXTENSION;
			case MEDIUM_PVRFILE:
				return PlayTvMediaPlayer.PLAYER_TSPLAYER;
			case MEDIUM_TSFILE:
				return PlayTvMediaPlayer.PLAYER_TSPLAYER;
			case MEDIUM_LOCALFILE:
				return PlayTvMediaPlayer.PLAYER_FILEPLAYER;
			default:
				return PlayTvMediaPlayer.PLAYER_INVALID;
		}
	}
	
	private boolean selectUri(Uri selectURI,String tuneType,String tuneSubType,String privDataCookie, Map<String, String> headers) {		
		boolean retval = false;
		if (selectURI != null) {
			RunSelecturi r = new RunSelecturi(selectURI,tuneType,tuneSubType,privDataCookie,headers);
			mHandler.post(r);
			retval = true;
		}
		return retval;
	}
	
	class RunSelecturi implements Runnable {		
		Uri selectURI				= null;
		String tuneType				= null;
		String tuneSubType			= null;
		String privDataCookie		= null;
		Map<String, String> headers	= null;
		public RunSelecturi(Uri selectURI,String tuneType,String tuneSubType,String privDataCookie,Map<String, String> headers) {
			this.selectURI 		= selectURI;
			this.tuneType		= tuneType;
			this.headers		= headers;
			this.tuneSubType	= tuneSubType;
			this.privDataCookie	= privDataCookie;
		}
		
		@Override
		public void run() {
			Log.d(LOG_TAG,"RunselectUri ");
			PlayTVFacMediaPlayer pPlaytvMediaPlayer = null;
			int pPlayerType				= PlayTvMediaPlayer.PLAYER_INVALID;						
			int cPlayerType				= PlayTvMediaPlayer.PLAYER_INVALID;
			int pPlayerPurpose 			= 0; 
			int cPlayerPurpose 			= 0; 
			int channel					= -1;
			int mode					= -1;
			int plpid					= -1;
			int bandWidth               = -1;
			int sym_rate				= 0;
			boolean isOlympicUsecase 	= false;
			Medium medium				= Medium.MEDIUM_INVALID;
			boolean restoreChannelState = false;
			boolean isCatchUpChannel	= false;
			boolean isForceTune = false;
			Uri pPlayerUri = null;
			try {
				if((headers != null) && (headers.get(TvHeaders.RESTORE_CHANNEL_STATE) != null)) {
					restoreChannelState = (Integer.parseInt(headers.get(TvHeaders.RESTORE_CHANNEL_STATE)) == 1) ? true : false;
				}
				if(headers != null && headers.containsKey(TvHeaders.FORCE_CHANNEL_TUNING))
					isForceTune = true;
				mRequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH;
				Log.i(LOG_TAG,"PowerState " + ITvPowerManager.Instance.getInterface().GetPowerState() );
				if(selectURI != null && selectURI.getBooleanQueryParameter("clock_calibration", false)) {
					mRequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY;
				}
				Log.i(LOG_TAG,"RunSelecturi run()  mRequestType = " + mRequestType );
				if(!(tuneType.contentEquals(ITVSessionContext.TUNE_REQUEST_TYPE_CUSTOM))) {					
					headers  = TvURIHelper.getUriHeaders(mContext, this.selectURI);
					Log.d(LOG_TAG,"[!!!]1: headers string = " + ((headers == null) ? "null" : headers.toString()));
					if((wakeupSelection) || (wakeupFromDDR)) {
						headers.put(TvHeaders.WAKEUP_SELECTION,Integer.toString(1));					
					}
				}
				
				if((headers == null) || (headers.size() == 0)) {
					onPlayFailed(this.selectURI,Medium.MEDIUM_INVALID, 0, ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
					return;
				}
				
				if(headers.get(TvHeaders.FILE_URI) != null){
					mRequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_MEDIA_FILE;
				}
								
				if((mTuneSubType != null) && mTuneSubType.equals(ITVSessionContext.TUNE_REQUEST_SUB_TYPE_NON_DESTRUCTIVE_SELECTION)) {
					headers.put(TvHeaders.DISABLE_AUTO_MUTE,Integer.toString(0));
				}
				if((tuneSubType != null) && tuneSubType.equals(ITVSessionContext.TUNE_REQUEST_SUB_TYPE_NON_DESTRUCTIVE_SELECTION)) {
					headers.put(TvHeaders.DISABLE_AUTO_MUTE,Integer.toString(1));						
				}
				mTuneSubType = tuneSubType;
				if(mTuneSubType != null) {
					headers.put(TvHeaders.REQUEST_SUB_TYPE,mTuneSubType);
				}
				if(!headers.containsKey(TvHeaders.SELECTION_TYPE)) {
					if(tuneType.contentEquals(ITVSessionContext.TUNE_REQUEST_TYPE_SILENT)){
						headers.put(TvHeaders.SELECTION_TYPE,Integer.toString(TvURIHelper.SelectionType.SELECTION_SILENT.value));
					}else {
						headers.put(TvHeaders.SELECTION_TYPE,Integer.toString(TvURIHelper.SelectionType.SELECTION_NORMAL.value));
					}
				}
				if(headers.get(TvHeaders.MEDIUM) != null) {				
					medium 	= Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
				}
				if(headers.get(TvHeaders.PRESET_ID) != null) {				
					channel = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
				}				
				if(msessionType.equals(ITVSessionContext.SESSION_TYPE_MAIN_WATCH_IN_PIP)) {
					headers.put(TvHeaders.RESOURCE_PQ_TYPE,Integer.toString(TvHeaders.PQ_TYPE_SUB)); 
					headers.put(TvHeaders.OUTPUT_TYPE,Integer.toString(TvHeaders.PATH_VIDEO));
				}
				if(privDataCookie != null) {
					headers.put(TvHeaders.PRIV_DATA_COOKIE,privDataCookie); 
				}
				if(headers.containsKey(TvHeaders.MODE)) {
					mode = Integer.parseInt(headers.get(TvHeaders.MODE));
					if((mode ==	TvHeaders.MODE_ANALOG) && (mLastSelectedMode != TvHeaders.MODE_ANALOG)) {
						mTriggerReAcquireInterfaces = true;
					}else if((mode != TvHeaders.MODE_ANALOG) && (mLastSelectedMode == TvHeaders.MODE_ANALOG)) {
						mTriggerReAcquireInterfaces = true;
					}
					mLastSelectedMode = mode;
				}
				if(!isForceTune && headers.containsKey(TvHeaders.NEW_PRESET)) {
					
					if(TvHeaders.HTV_DI_CHANNEL_CHECK_FLAG.equals(headers.get(TvHeaders.NEW_PRESET))
							&& headers.containsKey(TvHeaders.MODE) 
							&& (headers.containsKey(TvHeaders.BANDWIDTH) || headers.containsKey(TvHeaders.PLP_ID) || headers.containsKey(TvHeaders.SYMBOL_RATE))) {
						
						mode = Integer.parseInt(headers.get(TvHeaders.MODE));
						if(headers.containsKey(TvHeaders.BANDWIDTH))
							bandWidth = Integer.parseInt(headers.get(TvHeaders.BANDWIDTH));
						if(headers.containsKey(TvHeaders.PLP_ID))
							plpid = Integer.parseInt(headers.get(TvHeaders.PLP_ID));
						if(headers.containsKey(TvHeaders.SYMBOL_RATE))
							sym_rate = Integer.parseInt(headers.get(TvHeaders.SYMBOL_RATE));
						Log.v(LOG_TAG, "DT: channel id = " +  this.selectURI.getLastPathSegment() );
						Log.v(LOG_TAG, "DT: mode type = " + mode + "  bandwidth = " + bandWidth +  "  plp id = " + plpid + "  sym_rate = " +  sym_rate );
						if( (mode == TvHeaders.MODE_DVBT) && (bandWidth == 0) ||
							(mode == TvHeaders.MODE_DVBT2) && (plpid == -1) ||
						    (mode == TvHeaders.MODE_DVBC) && (sym_rate == 0) ) {
							Intent intent = new Intent("org.droidtv.euinstallertc.INSTALLER");
							intent.putExtra(InstallFlag,"DIRECT_TUNE");
							intent.putExtra(Dt_Chid, Integer.parseInt(this.selectURI.getLastPathSegment()));
							mContext.startService(intent);
							
							return;
						}
					}					
				}

				pPlaytvMediaPlayer = MainTVManager.this.getPlaytvFacMediaPlayer();
				if(pPlaytvMediaPlayer!=null) {
					pPlayerType 	= pPlaytvMediaPlayer.getUnderlyingPlayer();
					pPlayerPurpose 	= pPlaytvMediaPlayer.getCurrentPurpose();
					pPlayerUri      = pPlaytvMediaPlayer.getCurrentUri();
					Log.v(LOG_TAG, "pPlaytvMediaPlayer PlayerType: "+pPlayerType + ", pPlayerUri: " + pPlayerUri);
	                if(pPlayerUri != null && pPlayerUri.getBooleanQueryParameter("clock_calibration", false)) {
	                	Log.i(LOG_TAG, "release clock mediaplayer");
	                	factory.releaseMPLInstance(PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY,cplaytvmediaplayer);	
	                }
					unRegisterOnMediaChangeListener();
					unRegisterOnMediaStreamChangeListener();
					unRegisterOnMediaStreamLinkageInfoListener();
					unregisterforContentObserver();
					unregisterforHTVContentObserver();
					ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
					if(tvmc != null) {
						mCachedLockData 	= tvmc.getLockData();
						mCachedLockStatus	= tvmc.getLockStatus();	
					}
				}
														
				cplaytvmediaplayer = factory
					.getMPLInstance(
							MainTVManager.this.mContext,
							mRequestType,
							medium,
							channel);
									
				if (cplaytvmediaplayer != null) {
                    /*begin:min.jiang add 2015-07-09*/
                    if(cplaytvmediaplayer.getClockHandler() != null) {
                        cplaytvmediaplayer.getClockHandler().RegisterCallBack(MainTVManager.this);
                    }
                    /*end:min.jiang add*/
					isMediaListenerRegistered = registerOnMediaChangeListener();
					if(isMediaListenerRegistered == true)
					{
						registerOnMediaStreamChangeListener();
						registerOnMediaStreamLinkageInfoListener();
					}
					registerforContentObserver();

					cPlayerType 	= getPlayerType(medium);
					cPlayerPurpose 	= cplaytvmediaplayer.getCurrentPurpose();
					Log.v(LOG_TAG,"cplaytvmediaplayer PlayerType "+ cPlayerType);
					
					if(restoreChannelState) {
						headers.put(TvHeaders.RESTORE_CHANNEL_STATE,Integer.toString(1));
						ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
						if(tvmc != null) {
							mCachedLockData 	= tvmc.getLockData();
							mCachedLockStatus	= tvmc.getLockStatus();	
						}
					}

					Log.d(LOG_TAG,"[!!!]2: headers string = " + headers.toString());

					try {
						if ((privDataCookie != null) && (privDataCookie.equals(TvHeaders.PRIV_DATA_CATCHUP_TUNE))) {
							isCatchUpChannel = true;
						} else {
							isCatchUpChannel = false;
						}
					} catch (Exception e) {
						Log.e(LOG_TAG, "playCatchUp check failed, fall-back to default !!!");
						isCatchUpChannel = false;
					}
										
					if((cPlayerPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == 
						PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING){
						//dual tuner usecase & hence check for olympic usecase
						if(factory.IsDualTunerFactoryConfigEnabled(medium)) {
							/*set previous mediaplayer surface to null*/
							Log.d(LOG_TAG,"Entering in to olympic usecase");
							if(pPlaytvMediaPlayer != null) {
								pPlaytvMediaPlayer.setAVSurface(null);
							}
							isOlympicUsecase   			= true;
							mTriggerReAcquireInterfaces	= true;
							mNotifyMediaEvents			= true;
							
							/*Reset pin entered status to false so that re-evaluation of lock should show pin entry again*/
							mCachedLockData.dvbpinstatus = false;
							mCachedLockData.lockpinstatus= false;
							
							mCloneLockData				 = true;							
						}
					}
					if(mCloneLockData || restoreChannelState) {
						ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
						if(tvmc != null) {
							tvmc.setLockData(mCachedLockData);
							if((mCachedLockData.isLockEnabled) && (!mCachedLockStatus) && (mCachedLockData.dvbpinstatus|mCachedLockData.lockpinstatus)) {
								tvmc.enableLocking(false);
								mLockDisabled = true;
							}
						}
						mCloneLockData = false;
					}
					if(pPlayerType	!= PlayTvMediaPlayer.PLAYER_INVALID) {
						if(pPlayerType !=	cPlayerType) {
							Log.d(LOG_TAG, "SetSurface to null, since player changed");
							pPlaytvMediaPlayer.setAVSurface(null);
						}else {
							if(factory.IsDualTunerFactoryConfigEnabled(medium)) {
								//dual tuner usecase & hence check for olympic usecase
								if((pPlayerPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == 
										PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) {
									/*set previous mediaplayer surface to null*/
									Log.d(LOG_TAG,"Exiting out from olympic usecase");
									mTriggerReAcquireInterfaces = true;
									pPlaytvMediaPlayer.setAVSurface(null);									
									/*Need to remove watch main purpose while exiting from olympic usecase*/
									factory.releaseMPLInstance(mRequestType,pPlaytvMediaPlayer);									
								}
							}
						}
					}
					if((mBroadcastAVEnabled) && (pPlayerType != cPlayerType) && (mSurface != null)){												
						if((wakeupSelection) || (wakeupFromDDR)) {
							if(((mMainRatingInterfaceInstance!= null) && (mMainRatingInterfaceInstance.getParentalRating() == ITvMediaControl.PARENTAL_RATING_DVB_NONE)) ||
							   ((headers.get(TvHeaders.LOCK) != null) && (Integer.parseInt(headers.get(TvHeaders.LOCK)) == 0))){					
								cplaytvmediaplayer.setAVSurface(mSurface);
							}
						}else {
							cplaytvmediaplayer.setAVSurface(mSurface);
						}						
					}
					if(mRequestType == PlayTVMediaPlayerFactory.REQUEST_TYPE_MEDIA_FILE)
					   mChView.onPlayStarted(headers.get(TvHeaders.FILE_URI));
					
					//setOverlayViewEnabled(true);
					if((wakeupSelection) || (wakeupFromDDR)) {
						wakeupSelection = false;
						wakeupFromDDR	= false;
					}
					cplaytvmediaplayer.setUnderlyingPlayer(cPlayerType);					
					if(mSubtitleHandler!=null) {
						mSubtitleHandler.setTvMediaPlayer(cplaytvmediaplayer,medium);
					}										
					if(mainPlayback != cplaytvmediaplayer.getPlaybackObject()){
						if(mainPlayback != null) {
							mainPlayback.unRegisterListener(MainTVManager.this);
						}
						mainPlayback = cplaytvmediaplayer.getPlaybackObject();
						mainPlayback.registerListener(MainTVManager.this);
					}							
					if(medium == Medium.MEDIUM_LOCALFILE){
						mainPlayback = cplaytvmediaplayer.getPlaybackObject();
					}
					if(mainPlayback != null) {
						if(isOlympicUsecase) {
							mainPlayback.playOlympicChannel(this.selectURI,medium,headers);
						} else if (isCatchUpChannel) {
							Log.d(LOG_TAG, "CatchUp tune detected playCatchUpChannel");
							mainPlayback.playCatchUpChannel(this.selectURI,medium,headers);
						} else {
							mainPlayback.play(this.selectURI,medium,headers);
						}
					}				
				}else {
					cplaytvmediaplayer = pPlaytvMediaPlayer; //assign previous valid mpl
					//do additional call to know the reason for failure					
					int status = factory.IsMediaPlayerAvailable(
								mContext,
								PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH,
								medium,
								channel);
					
					if(status  != PlayTVMediaPlayerFactory.STATUS_AVAILABLE) {
					if(((status & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) || ((status & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING)) {
							mRecIcon.showStopRecordingToast();
						}
					}
					
					RunOnPlayFailed r = new RunOnPlayFailed(selectURI, medium, channel, getTuneFailureReason(status));
					mHandler.post(r);
				}					
			}catch(Exception e) {
				Log.e(LOG_TAG, "RunSelecturi::Caught Exception : " + e.getLocalizedMessage() );
			}
		}	
	};

	class RunOnPlayFailed implements Runnable {
		Uri selectURI;
		Medium medium;
		int channel;
		int status;
		RunOnPlayFailed(Uri selectURI, Medium medium, int channel, int status) {
			this.selectURI = selectURI;
			this.medium = medium;
			this.channel = channel;
			this.status = status;
		}
		
		@Override
		public void run() {
			onPlayFailed(selectURI, medium, channel, status);
		}
	};
					
	private void selectOlympicChannelUri(Uri selectURI) {
		PlayTVFacMediaPlayer pPlaytvMediaPlayer = null;
		int cPlayerType				= PlayTvMediaPlayer.PLAYER_INVALID;
		int cPlayerPurpose 			= 0; 
		int channel 				= -1;
		Map<String, String> headers	= null;		
		Medium medium 				= Medium.MEDIUM_INVALID;
		
		headers  = TvURIHelper.getUriHeaders(mContext,selectURI);	
		if((headers == null) || (headers.size() == 0)) {
			onPlayFailed(selectURI,Medium.MEDIUM_INVALID, 0, ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
			return;
		}
		if(headers.get(TvHeaders.MEDIUM) != null) {				
			medium 	= Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
		}
		if(headers.get(TvHeaders.PRESET_ID) != null) {				
			channel = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
		}
		if(factory.IsDualTunerFactoryConfigEnabled(medium)) {			
			pPlaytvMediaPlayer = MainTVManager.this.getPlaytvFacMediaPlayer();
			if(pPlaytvMediaPlayer!=null) {
				ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
				if(tvmc != null) {
					mCachedLockData 	= tvmc.getLockData();
					mCachedLockStatus	= tvmc.getLockStatus();
				}			
				unRegisterOnMediaChangeListener();
				unRegisterOnMediaStreamChangeListener();
				unRegisterOnMediaStreamLinkageInfoListener();
			
			}		
			cplaytvmediaplayer = factory
					.getMPLInstance(
							mContext,
							PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH,
							medium,
							channel);
			if (cplaytvmediaplayer != null) {
				cPlayerType 	= getPlayerType(medium);
				cPlayerPurpose 	= cplaytvmediaplayer.getCurrentPurpose();
				//dual tuner usecase & hence check for olympic usecase
				if((cPlayerPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING)	== 
						PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) {
					/*set previous mediaplayer surface to null*/
					Log.d(LOG_TAG,"Entering in to olympic usecase");
					pPlaytvMediaPlayer.setAVSurface(null);					
					cplaytvmediaplayer.setUnderlyingPlayer(cPlayerType);
					mTriggerReAcquireInterfaces =  true;
					isMediaListenerRegistered = registerOnMediaChangeListener();
					if(isMediaListenerRegistered == true)
					{
						registerOnMediaStreamChangeListener();
						registerOnMediaStreamLinkageInfoListener();
					}
					ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
					if((tvmc != null) && (mCachedLockData != null)) {
						tvmc.setLockData(mCachedLockData);
						if((mCachedLockData.isLockEnabled) && (!mCachedLockStatus) && (mCachedLockData.dvbpinstatus|mCachedLockData.lockpinstatus)) {
							tvmc.enableLocking(false);
							mLockDisabled = true;
						}
					}					
					
					if(mainPlayback != cplaytvmediaplayer.getPlaybackObject()){
						if(mainPlayback != null) {
							mainPlayback.unRegisterListener(MainTVManager.this);
						}
						mainPlayback = cplaytvmediaplayer.getPlaybackObject();
						mainPlayback.registerListener(MainTVManager.this);
					}				
					if(mSubtitleHandler!=null) {
						mSubtitleHandler.setTvMediaPlayer(cplaytvmediaplayer,medium);
					}
				}
			}else {
				//do additional call to know the reason for failure
				int status = factory.IsMediaPlayerAvailable(
							mContext,
							PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH,
							medium,
							channel);				
				onPlayFailed(selectURI,medium, channel, getTuneFailureReason(status));
			}
		}
		
	}
	
	private int convertToTvServerConstant (int streamType) {
		int		type;
		switch (streamType) {
		case 0x0F:
			type = (ITvMediaStream.TvMediaTypeInfo.AAC_TYPE >> 24);
			break;
		case 0x11:
			type = (ITvMediaStream.TvMediaTypeInfo.HEAAC_TYPE >> 24);
			break;
		case 0x81:
			type = (ITvMediaStream.TvMediaTypeInfo.AC3_TYPE >> 24);
			break;
		case 0x06:
			type = (ITvMediaStream.TvMediaTypeInfo.AC3PLUS_TYPE >> 24);
			break;
		default:
			type = (ITvMediaStream.TvMediaTypeInfo.MPEG_AUDIO_TYPE >> 24);
			break;
		}
		return type;
	}

	private void selectPid(final Uri pChannelUri,final Map<String, String> headers) {		
		Runnable r = new Runnable() {
			@Override
			public void run() {				
				if((headers != null) && (cplaytvmediaplayer!=null)){
					try{
						ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
						
						if(headers.get(TvHeaders.VIDEO_PID) != null) {
							TvMediaVideoInfo mVideoInfo =  new TvMediaVideoInfo();
							mVideoInfo.pid 	= Integer.parseInt(headers.get(TvHeaders.VIDEO_PID));
							if(headers.get(TvHeaders.VIDEO_STREAM_TYPE) != null) {
								mVideoInfo.type	= Integer.parseInt(headers.get(TvHeaders.VIDEO_STREAM_TYPE));
							}							
							if(mVideoInfo.pid == DEFAULT_PID) {
								tvmc.playTVVideo(mVideoInfo);	
							}else {
								if(tvmc.getTVMedia(ITvMediaControl.MEDIA_VIDEO) != mVideoInfo.pid) {
									tvmc.stopTVMedia(ITvMediaControl.MEDIA_VIDEO);
									tvmc.playTVVideo(mVideoInfo);	
									Log.i(LOG_TAG,"selectPid : Video Pid - "+mVideoInfo.pid);
								}else {
									Log.i(LOG_TAG,"selectPid : Video Pid already playing - "+mVideoInfo.pid);
								}
							}
						}
						if(headers.get(TvHeaders.AUDIO_PID) != null) {
							TvMediaAudioInfo mAudioInfo =  new TvMediaAudioInfo();
							mAudioInfo.pid = Integer.parseInt(headers.get(TvHeaders.AUDIO_PID));
							if(headers.get(TvHeaders.AUDIO_STREAM_TYPE) != null) {
								int type 		= Integer.parseInt(headers.get(TvHeaders.AUDIO_STREAM_TYPE));
								type = convertToTvServerConstant (type);
								if(ITvMediaStream.TvMediaTypeInfo.isMpegAudio(type << 24)) {
									mAudioInfo.type = ITvMediaStream.TvMediaTypeInfo.MPEG_AUDIO_TYPE;
								}else if(ITvMediaStream.TvMediaTypeInfo.isAC3Audio(type << 24)) {
									mAudioInfo.type = ITvMediaStream.TvMediaTypeInfo.AC3_TYPE;
								}else if(ITvMediaStream.TvMediaTypeInfo.isAACAudio(type << 24)) {
									mAudioInfo.type = ITvMediaStream.TvMediaTypeInfo.AAC_TYPE;
								}else if(ITvMediaStream.TvMediaTypeInfo.isAC3PLUSAudio(type << 24)) {
									mAudioInfo.type = ITvMediaStream.TvMediaTypeInfo.AC3PLUS_TYPE;
								}else if(ITvMediaStream.TvMediaTypeInfo.isHEAACAudio(type << 24)) {
									mAudioInfo.type = ITvMediaStream.TvMediaTypeInfo.HEAAC_TYPE;
								}else {
									//default case
									mAudioInfo.type = ITvMediaStream.TvMediaTypeInfo.MPEG_AUDIO_TYPE;
								}
							}
							if(mAudioInfo.pid == DEFAULT_PID) {
								mAudioInfo.langCode = 0xFFFF;
								tvmc.playTVAudio(mAudioInfo);
							}else {
								//only pid check is done, if needed, we can also check streamtype mis match
								//but not sure MHEG will always send valid streamtype, so do change on need basis.
								if(tvmc.getTVMedia(ITvMediaControl.MEDIA_AUDIO) != mAudioInfo.pid) {
									if(mAudioInfo.pid != DEFAULT_PID) {
										tvmc.stopTVMedia(ITvMediaControl.MEDIA_AUDIO);
									}
									tvmc.playTVAudio(mAudioInfo);	
									Log.i(LOG_TAG,"selectPid : Audio Pid - "+mAudioInfo.pid);
									Log.i(LOG_TAG,"selectPid : Audio Type - "+mAudioInfo.type);
								}else {
									Log.i(LOG_TAG,"selectPid : Audio Pid already playing - "+mAudioInfo.pid);
								}
							}
							
						}						
						if(headers.get(TvHeaders.PCR_PID) != null) {
							int pcrPid = Integer.parseInt(headers.get(TvHeaders.PCR_PID));
							if(tvmc.getTVMedia(ITvMediaControl.MEDIA_PCR) != pcrPid) {
								if(pcrPid != DEFAULT_PID) {
									tvmc.stopTVMedia(ITvMediaControl.MEDIA_PCR);
								}
								tvmc.playTVMedia(ITvMediaControl.MEDIA_PCR,pcrPid);	
								Log.i(LOG_TAG,"selectPid : PCR Pid - "+pcrPid);
							}else {
								Log.i(LOG_TAG,"selectPid : PCR Pid already playing - "+pcrPid);
							}
						}
						//subtitle not possible?
					}
					catch(Exception e){
						Log.e(LOG_TAG,"selectPid Exception : "+e.toString());
					}
				}else {
					Log.e(LOG_TAG,"selectPid failed!!!");
				}
			}
		};
		mHandler.post(r);
	}
	
	@Override
	public boolean onAvailable(int clientType) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean onNotAvailable(int clientType) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
    public void onOlympicUsecaseUpdate(boolean enable, boolean isOTR) 
	{
		if(cplaytvmediaplayer!=null) {
			if(enable) {
				if(isOTR) {
					selectOlympicChannelUri(cplaytvmediaplayer.getCurrentUri());
				}
			}
			else {
				Log.d(LOG_TAG,"Exiting from olympic usecase");				
				ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
				if(tvmc != null) {
					mCachedLockData 	= tvmc.getLockData();
					mCachedLockStatus	= tvmc.getLockStatus();
					mCloneLockData 		= true;
				}				
				unRegisterOnMediaChangeListener();
				unRegisterOnMediaStreamChangeListener();
				unRegisterOnMediaStreamLinkageInfoListener();
				if(mainPlayback != null) {
					mainPlayback.unRegisterListener(MainTVManager.this);
					mainPlayback =  null;
				}
				mTriggerReAcquireInterfaces = true;
				selectUri(cplaytvmediaplayer.getCurrentUri(),ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT,null,null,null);
				cplaytvmediaplayer = null;
			}
		}else {
			Log.v(LOG_TAG,"onOlympicUsecaseUpdate -> not required to take any action");
		}
    }
		
	public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber){

		queryUserLockStatus();
		
		if(mSubtitleHandler!=null) {
			mSubtitleHandler.onPlayStarted(mediaPlayerUri);
		}
		if(mIappManager!=null) {
			mIappManager.onZapStatusChanged(BcstConstants.STATE_PREPARE_START,headers, mediaPlayerUri);
		}
		if(mRecIcon != null) {
			mRecIcon.onPlayStarted(mediaPlayerUri);
		}
		if(mRadioBG != null){
			mRadioBG.onPlayStarted();
		}
		super.onPlayStarted(mediaPlayerUri,headers, medium,presetNumber);
	}
	
	public void onPlayCompleted(final Uri mediaPlayerUri, final Map<String,String> headers, final Medium medium, final int presetNumber) {
		if(cplaytvmediaplayer==null) {
			return;
		}
		if(isMediaListenerRegistered == false){
			isMediaListenerRegistered = registerOnMediaChangeListener();
			registerOnMediaStreamChangeListener();
			registerOnMediaStreamLinkageInfoListener();
		}
		if(mMainRatingInterfaceInstance!= null) {					
			mMainRatingInterfaceInstance.setParentalRating();		
		}
		
        Log.d(LOG_TAG, "onPlayCompleted: mBroadcastAVEnabled " + mBroadcastAVEnabled + ", mSurface " + mSurface + ", cplaytvmediaplayer" + cplaytvmediaplayer);
		if((mBroadcastAVEnabled) && (mSurface != null) && (cplaytvmediaplayer != null)) {
			Log.v(LOG_TAG,"mSurface!!! ");
			cplaytvmediaplayer.setAVSurface(mSurface);		
		}		
		if(mediaPlayerUri!=null) {
			String tuneType = ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT;
			if(headers.containsKey(TvHeaders.REQUEST_TYPE)) {
				tuneType = headers.get(TvHeaders.REQUEST_TYPE);	
			}
            /*begin:min.jiang modify 2015-07-09*/
            boolean clockCalibration = mediaPlayerUri.getBooleanQueryParameter("clock_calibration", false);
            Log.d(LOG_TAG, "onPlayCompleted: clockCalibration " + clockCalibration);
			if(!tuneType.equals(ITVSessionContext.TUNE_REQUEST_TYPE_CUSTOM) && !clockCalibration) {
            /*end:min.jiang modify*/    
				if(medium != TvURIHelper.Medium.MEDIUM_PVRFILE) {
					PlayTvUtils.storeCurrentChannel(mediaPlayerUri, medium, presetNumber);
				}
				PlayTvUtils.storeLastSelectedUri(mediaPlayerUri.toString());
			}
		}		
		if(mSubtitleHandler!=null) {
			mSubtitleHandler.onPlayCompleted(mediaPlayerUri,headers);
		}
		if(mIappManager!=null) {
			mIappManager.onZapStatusChanged(BcstConstants.STATE_PREPARE_COMPLETE,headers, mediaPlayerUri);
		}
		if(ChannelFilter.getChannelFilterInstance() != null){
			ChannelFilter.getChannelFilterInstance().onPlayCompleted(mediaPlayerUri, presetNumber);
		}
		if(mRecIcon != null){
			mRecIcon.onPlayCompleted(mediaPlayerUri);
		}
		if(mRadioBG != null) {
			try {
				mRadioBG.onPlayCompleted(headers,getTvMediaPlayerContext().getVideoPropertiesImpl());
			}catch(Exception e) {
				Log.e(LOG_TAG,"Exception in getvideoprop");
			}
		}
				
		if((mediaPlayerUri != null) && (TvContract.isChannelUriForTunerInput(mediaPlayerUri))) {
			Handler handler	=	new Handler();
			if(handler!=null){
				handler.post(new Runnable() {					
					@Override
					public void run() {
						int prefStereo 		= -1;
						int sap				= -1;
						String newPreset	= null;
						int mRowsUpdated		= 0;
						try{
							if(headers.containsKey(TvHeaders.PREFERRED_STEREO)) {
								prefStereo = Integer.parseInt(headers.get(TvHeaders.PREFERRED_STEREO));
								if(prefStereo == 1) {
									//stereo
									getTvMediaPlayerContext().getInputSoundImpl().setChannel(IInputSound.CHANNEL2);
								}else {
									//mono
									getTvMediaPlayerContext().getInputSoundImpl().setChannel(IInputSound.CHANNEL1);
								}
							}
							if(headers.containsKey(TvHeaders.SAP)) {
								sap	= Integer.parseInt(headers.get(TvHeaders.SAP));
								if(sap == IInputSound.CHANNEL2) {
									getTvMediaPlayerContext().getInputSoundImpl().setChannel(IInputSound.CHANNEL2);							
								}else if(sap == IInputSound.CHANNEL3) {
									getTvMediaPlayerContext().getInputSoundImpl().setChannel(IInputSound.CHANNEL3);
								}
							}
							if((headers.containsKey(TvHeaders.NEW_PRESET)) && (headers.containsKey(TvHeaders.UNIQUE_ID))){
								newPreset = headers.get(TvHeaders.NEW_PRESET);
									if(newPreset.equalsIgnoreCase("New")){
										//Reset the Newflag
										ContentValues value = new ContentValues();
										String	mselection = Channels._ID+"= ?";
										String[]	mselectionargs = new String[]{headers.get(TvHeaders.UNIQUE_ID)};
										value.put(Channels.COLUMN_NETWORK_AFFILIATION,"");
										mRowsUpdated = mContext.getContentResolver().update(TvContract.Channels.CONTENT_URI,value,mselection,mselectionargs);
									}								
							}
						}
						catch(Exception e){
							Log.e(LOG_TAG,"Exception: "+e.toString());
						}	
					}
				});
			}
		}
		super.onPlayCompleted(mediaPlayerUri,headers, medium,presetNumber);
		
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if((cplaytvmediaplayer!=null) && mLockDisabled) {
					ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
					if(tvmc != null) {
						tvmc.enableLocking(true);
						mLockDisabled = false;
					}
				}
			}
		};
		
		mHandler.post(r);
	}
	
	
	public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
		if(mIappManager!=null) {
			mIappManager.onZapStatusChanged(BcstConstants.STATE_PLAY_FAILED,null, mediaPlayerUri);
		}
		super.onPlayFailed(mediaPlayerUri,medium,presetNumber,reason);
	}
	
	public void onPlayStateChanged(int state, int mode) {
		Log.i(LOG_TAG,"onPlayStateChanged called with status:"+state+" mode:"+mode);	
		if (mSubtitleHandler != null) {
			mSubtitleHandler.onPlayStateChanged(state, mode);
		}
		super.onPlayStateChanged(state, mode);
	}
	
	public Uri getNextURI(Uri uri){
		Log.i(LOG_TAG,"getNextURI called .... current uri passed = "+uri);
		Uri nextUri		=	ChannelFilter.getChannelFilterInstance().getNextUri(uri);		
		Log.i(LOG_TAG,"getNextURI returns -> "+nextUri);
		return nextUri;
	}
	
	public Uri getPreviousURI(Uri uri){
		Log.i(LOG_TAG,"getPreviousURI called .... current uri passed = "+uri);
		Uri previousUri		=	ChannelFilter.getChannelFilterInstance().getPrevUri(uri);		
		Log.i(LOG_TAG,"getPrevURI returns -> "+previousUri);
		return previousUri;
	}

	private class IAppManagerTunerCallBacksImpl implements IAppManagerTunerCallBacks {

		@Override
		public void setVideoPosition(int x, int y, int width, int height) {
			Log.i(LOG_TAG,"setVideoPosition x=" + x + " y=" + y + " width=" + width + " + height="+height);
			MainTVManager.this.notifyLayoutChanged(x,y,(width+x),(height+y));
		}

		@Override
		public void enableBroadcastAV(boolean ena) {
			Log.i(LOG_TAG,"enableBroadcastAV called : " + ena);
			mBroadcastAVEnabled = ena;
			if((cplaytvmediaplayer!=null) && (mSurface!=null)) {
				if(!ena) {				
					cplaytvmediaplayer.setAVSurface(null);
					mIappManager.setAVSurface(mSurface);
					Log.i(LOG_TAG,"mIappManager setsurface called");
				} else {
					cplaytvmediaplayer.setAVSurface(mSurface);
					Log.i(LOG_TAG,"surface back to broadcast");
				}
			}
			MainTVManager.this.notifyMediaModeChanged(mBroadcastAVEnabled ? ITVTunerSession.MODE_BROADCAST : ITVTunerSession.MODE_BROADBAND);
		}
	}	

    public static ITunerRating getMainRatingInterfaceInstance(){
            return (ITunerRating)mMainRatingInterfaceInstance;
    }
	
	public static IAppManagerTunerCallBacks getIAppManagerTunerCallbackInstance() {
		return mTunerCallBackListener;
	}
        
    private class PowerEventsReceiver implements IPowerEvents {
		
		@Override
		public void onPowerChangeStart(PowerStates from, PowerStates to,Bundle extras) {
			if(to==PowerStates.POWER_STATE_DDR_STANDBY) {
				Log.d(LOG_TAG,"going to DDR!!!");
				wakeupFromDDR = true;
			}
		}
		
		@Override
		public void onPowerChangeEnd(PowerStates from, PowerStates to,Bundle extras) {
			Log.d(LOG_TAG,"onPowerChangeEnd : from - "+from+"to - "+to);
			if((from==PowerStates.POWER_STATE_FULL_SYSTEM_START) && 
				(to==PowerStates.POWER_STATE_SEMI_STANDBY)) {
			}else if(from==PowerStates.POWER_STATE_SEMI_STANDBY){
				if(to==PowerStates.POWER_STATE_FULL_SYSTEM_START) {
					Log.d(LOG_TAG,"wakeup from DDR!!!");
					wakeupFromDDR = true;
				}
			}
		}
	}
    
    public static IPowerEvents getPowerEventsListener() {
		return mPowerEventListener;
	}

	// Implementation for new methods added in TVTunerSession for Timeshift/PVR separation.
	
	@Override
	public void timeshiftPause() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				mainPlayback.pause();
			} else {
				Log.e(LOG_TAG, "timeshiftPause: ERROR, called on wrong object");
			}
		}
	}
	
	@Override
	public void timeshiftStop() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				mainPlayback.stop();
			} else {
				Log.e(LOG_TAG, "timeshiftStop: ERROR, called on wrong object");
			}
		}
	}
	
	@Override	
	public void timeshiftResume() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				mainPlayback.resume();
			} else {
				Log.e(LOG_TAG, "timeshiftResume: ERROR, called on wrong object");
			}
		}	
	}
	
	@Override	
	public void timeshiftSeekTo(int pMsecs) {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				mainPlayback.seekTo(pMsecs);
			} else {
				Log.e(LOG_TAG, "timeshiftSeekTo: ERROR, called on wrong object");
			}
		}
	}
	
	@Override	
	public void timeshiftSetSpeed(int pSpeed, boolean pForward) {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				mainPlayback.setSpeed(pSpeed, pForward);
			} else {
				Log.e(LOG_TAG, "timeshiftSetSpeed: ERROR, called on wrong object");
			}
		}
	}
	
	@Override	
	public int getTimeshiftCurrentDuration() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				return mainPlayback.getCurrentDuration();
			} else {
				Log.e(LOG_TAG, "getTimeshiftCurrentDuration: ERROR, called on wrong object");
			}
		}
		return 0;
	}
	
	@Override	
	public int getTimeshiftTotalDuration() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				return mainPlayback.getTotalDuration();
			} else {
				Log.e(LOG_TAG, "getTimeshiftTotalDuration: ERROR, called on wrong object");
			}
		}
		return 0;
	}
	
	@Override	
	public int getTimeshiftBufferedDuration() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				return (int)mainPlayback.getRecordedDuration();
			} else {
				Log.e(LOG_TAG, "getTimeshiftBufferedDuration: ERROR, called on wrong object");
			}
		}
		return 0;		
	}
	
	@Override	
	public int getTimeshiftPlaybackState() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				return mainPlayback.getPlaybackState();
			} else {
				Log.e(LOG_TAG, "getTimeshiftPlaybackState: ERROR, called on wrong object");
			}
		}
		return 0;				
	}
	
	@Override	
	public int getTimeshiftRecordingStatus() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				return mainPlayback.getCurrentTimeShiftStatus();
			} else {
				Log.e(LOG_TAG, "getTimeshiftRecordingStatus: ERROR, called on wrong object");
			}
		}
		return 0;		
	}
	
	@Override	
	public void enableTimeshiftTrickModes(boolean pEnable) {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				mainPlayback.enableTrickModes(pEnable);
			} else {
				Log.e(LOG_TAG, "enableTimeshiftTrickModes: ERROR, called on wrong object");
			}
		}			
	}
	
	@Override
	public boolean getTimeshiftTrickModeStatus() {
		if(mainPlayback != null) {
			if (mainPlayback instanceof TvChannelPlayback) {
				return mainPlayback.getTrickmodeStatus();
			} else {
				Log.e(LOG_TAG, "enableTimeshiftTrickModes: ERROR, called on wrong object");
			}
		}
		return true;
	}
	
	public void setCaptionEnabled(boolean pEnabled){
		if(mSubtitleHandler!=null){
			mSubtitleHandler.setCaptionEnabled(pEnabled);
		}
	}

	public CamInfoImpl getCamInfo(int slotId) {
		if(cplaytvmediaplayer != null) {
			return cplaytvmediaplayer.getCamInfo(slotId);
		}
		return null;
	}
}
