package org.droidtv.tunerservice.tvmanager;

import java.util.Set;
import java.util.HashSet;
import java.util.Map;
import android.util.Log;
import java.lang.String;
import java.lang.Exception;
import android.content.Context;
import android.os.Handler;
import android.os.Handler.Callback;
import android.os.Bundle;
import android.os.Message;
import android.os.HandlerThread;
import android.os.Looper;
import android.view.View;
import android.view.Surface;
import android.net.Uri;
import android.media.tv.TvInputService.Session;
import org.droidtv.tv.tvinput.*;
import org.droidtv.tv.media.TvMediaPlayerContext;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tunerservice.TunerService;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.interfaces.IPlayTvMPLFactoryCallback;
import org.droidtv.tunerservice.tvmanager.AbstractManager.RatingInterfaceManager;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tunerservice.util.PlayTvMsgHandler;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.playback.TvAbstractPlayback;
import org.droidtv.tunerservice.interfaces.ITunerRating;
import org.droidtv.tunerservice.interfaces.IPowerEvents;
import org.droidtv.tunerservice.PlayTvDiversity;
import org.droidtv.tv.tvinput.CamInfoImpl;
import org.droidtv.tv.video.ITvVideoManager;

public class AuxTVManager extends AbstractManager implements ITvAbstractPlaybackListener, IPlayTvMPLFactoryCallback {
	private Set<TunerService.TunerSession> mListeners	= null;
	private static final String LOG_TAG 				= "PlayTVAuxManager";
	private static final int ACTION_REQUEST				= 1;
	private static final int ACTION_RESET				= 2;
	//private Context mContext							= null;
	private Handler mHandler 							= null;
	private PlayTVFacMediaPlayer cplaytvmediaplayer 	= null;	
	private PlayTVMediaPlayerFactory factory 			= null;
	private Surface mSurface 							= null;
	private Handler mAuxHandler 						= null;
	private Uri auxSelectedUri 							= null;
	private	TvAbstractPlayback mainPlayback 			= null;
	private Session mCurrentActiveSession				= null;
	private int mrequestType							= -1;
	private int mCurrentChannel							= -1;
	private Medium mCurrentMedium						= Medium.MEDIUM_INVALID;
	private static int downgradeMask = PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.STATUS_NOTAVAILABLE_MAINWATCH_NOT_IN_PROGRESS;
	private static  RatingInterfaceManager mAuxRatingInterfaceInstance = null;	
	private Looper mTvLooper;	
	private HandlerThread thread 					= null;	
	private static IPowerEvents mPowerEventListener = null;
	private boolean releaseFollowMain				= false;
	private boolean isMediaListenerRegistered	= true;
	
	public AuxTVManager(Context pContext){
		Log.v(LOG_TAG,"creating PlayTVAuxManager");		
		mContext		= pContext;
		mListeners		= new HashSet(2);
		mHandler 		= new Handler();
		factory			= PlayTVMediaPlayerFactory.getInstance();		
		createMainRatingInterface(this);
		mAuxRatingInterfaceInstance.setContext(pContext);
		
		factory.registerListener(PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH, this);
		factory.registerListener(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN, this);
		factory.registerListener(PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP, this);
		createPowerEventListener(this);
		Callback AuxCallback = new Callback() {			
			public boolean handleMessage(Message msg) {
				Bundle b		= null;
				boolean proceed = false;	
				if(msg.arg2 == ACTION_REQUEST) {
					switch(msg.arg1) {
						case PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH:
						case PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN:
						case PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP:
							proceed = true;
						break;
						default:
							Log.i(LOG_TAG,"AuxCallback :  Request Type not supported by AuxManager!!!");
						break;
					}
					
					if(proceed) {
						b = msg.getData();
						Medium medium		= Medium.MEDIUM_INVALID;
						int channel			= -1;
						Uri channelUri 		= Uri.parse(b.getString("uri"));
						boolean camUpgrade 	= b.getBoolean(TvHeaders.CAM_UPGRADE);
						
						Map<String, String> headers	= TvURIHelper.getUriHeaders(mContext, channelUri);	
						if((headers == null) || (headers.size() == 0)) {
							onPlayFailed(channelUri,Medium.MEDIUM_INVALID, 0, ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
							return false;
						}
						if(headers.get(TvHeaders.MEDIUM) != null) {				
							medium 	= Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
						}
						if(headers.get(TvHeaders.PRESET_ID) != null) {				
							channel = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
						}			
						auxSelectedUri  = channelUri;
						mCurrentChannel	= channel;
						mCurrentMedium	= medium;
						
						cplaytvmediaplayer = factory.getMPLInstance(mContext, msg.arg1,	medium, channel);
						if(cplaytvmediaplayer != null) {
							mrequestType = msg.arg1;
							cplaytvmediaplayer.setAVSurface(null);
							
							if ( (mrequestType == PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH ) || 
										(mrequestType == PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) ) {

								if ( thread == null )
								{
									thread = new HandlerThread("AuxTvManagerThread");			
									thread.start();
									mTvLooper = thread.getLooper();		
									mTvHandler = new TvManagerHandler(mTvLooper);
								}
								registerforContentObserver();
								isMediaListenerRegistered = registerOnMediaChangeListener();
							}else if(mrequestType == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) {
								if(camUpgrade) {
									headers.put(TvHeaders.CAM_UPGRADE,Integer.toString(1));
								}
							}
							headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_NONE));
							if(mainPlayback != cplaytvmediaplayer.getPlaybackObject()){
								if(mainPlayback != null) {
									mainPlayback.unRegisterListener(AuxTVManager.this);
								}
								mainPlayback = cplaytvmediaplayer.getPlaybackObject();
								mainPlayback.registerListener(AuxTVManager.this);
							}							
							if(mainPlayback != null) {
								try {
									mainPlayback.play(channelUri,medium,headers);
								}catch(Exception e) {
									Log.d(LOG_TAG,"Exception in select " + e.getLocalizedMessage());
								}
							}								
						}else {
							//do additional call to know the reason for failure					
							int status = factory.IsMediaPlayerAvailable(
										mContext,
										msg.arg1,
										medium,
										channel);
							
							onPlayFailed(channelUri,medium, channel, getTuneFailureReason(status));
						}
					}
				}else if(msg.arg2 == ACTION_RESET) {
					if(msg.obj == mCurrentActiveSession) {
						if(cplaytvmediaplayer != null) {
							resetRequest();
						}
						if ( ( msg.arg1 == PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH ) || 
								( msg.arg1 == PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP ) ) {
							if ( thread != null )
							{
								thread.stop();
								thread = null;
							}
							unRegisterOnMediaChangeListener();
							unregisterforContentObserver();
						}
						auxSelectedUri				= null;	
						mCurrentChannel				= -1;
						mCurrentMedium				= Medium.MEDIUM_INVALID;
						mCurrentActiveSession 		= null;
						mTriggerReAcquireInterfaces	= true;
						notifyReAcquireInterfaces();//towards observer sessions
					}
				}
				return false;
			}
		};				
		mAuxHandler = new Handler(AuxCallback);
	}
	
	private static void createMainRatingInterface(AuxTVManager mAuxTVManager){
		mAuxRatingInterfaceInstance= mAuxTVManager.new RatingInterfaceManager();
	}
	
	public static void createPowerEventListener(AuxTVManager mAuxTVManager){
		mPowerEventListener = mAuxTVManager.new PowerEventsReceiver();
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
	public Session getCurrentActiveSession() {
		return mCurrentActiveSession;
	}

	@Override
    public void setSurface(Surface pSurface){
		mSurface = pSurface;
		Log.v(LOG_TAG,"setSurface !!! "+ ((pSurface == null)?"surface null":"valid surface"));
		if(cplaytvmediaplayer != null) {
			Log.v(LOG_TAG,"mSurface!!! ");
			cplaytvmediaplayer.setAVSurface(mSurface);
		}
	}
	
	@Override
	public void dispatchSurfaceChanged(int pFormat, int pWidth, int pHeight, Surface pSurface) {
		if(cplaytvmediaplayer != null) {
			mSurface = pSurface;
			Log.v(LOG_TAG,"dispatchSurfaceChanged " + pWidth + "x" + pHeight);
			cplaytvmediaplayer.setAVSurface(mSurface);
		}
	}
	
	@Override
    public void tune(Uri pChannelUri){
		Log.v(LOG_TAG,"tune called : " +pChannelUri);
		if(pChannelUri != null) {
			processRequest(mrequestType,pChannelUri,false);
		}else {
			Log.i(LOG_TAG,"Not possible to tune as URI is NULL !!!");
		}
	}
	
	@Override
	public void tune(Uri pChannelUri,Bundle params) {
		Log.v(LOG_TAG,"tune called : " +pChannelUri);
		if(params == null) {
			processRequest(mrequestType,pChannelUri,false);
		}else {
			Log.i(LOG_TAG,"tune with Bundle as of now not supported for AuxManager!!!");
		}
	}
	
	public void tuneCamUpgradeChannel(Uri pChannelUri) {
		if(pChannelUri != null) {
			processRequest(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN,pChannelUri,true);
		}else {
			Log.i(LOG_TAG,"tune with null pChannelUri is not supported!!!");
		}
	}
	
	@Override
	public TvMediaPlayerContext getTvMediaPlayerContext(){		
		Log.v(LOG_TAG,"getTvMediaPlayerContext called : ");
		if(cplaytvmediaplayer!=null){
			 return (TvMediaPlayerContext)cplaytvmediaplayer.getMediaPlayerInstance().getTvMediaPlayerContext();
		}
		return null;
	}
	
	@Override
	public View getOverlayView() {
		Log.i(LOG_TAG,"getOverlayView called : not supported for aux");
		return null;
	}

	@Override	
	public Uri getSelectedURI(){
		if(null != auxSelectedUri)
		Log.i(LOG_TAG, "getSelectedURI##"+auxSelectedUri.toString());
		else
		Log.i(LOG_TAG, "getSelectedURI##NULL");		
		return auxSelectedUri;
	}	
	
	@Override
	public void release(TunerService.TunerSession pSession){
		Log.v(LOG_TAG,"release : ");
		synchronized(mAuxHandler) {
			Message msg = mAuxHandler.obtainMessage();
			msg.arg1 = 0;
			msg.arg2 = ACTION_RESET;
			msg.obj	 = pSession;
			mAuxHandler.sendMessage(msg);
		}		
	}
	
	@Override
	public void setSessionType(String sessionType) {
		if(sessionType.equals(ITVSessionContext.SESSION_TYPE_PIP_WATCH)) {
			Log.v(LOG_TAG,"setSessionType... session type = SESSION_TYPE_PIP_WATCH ");
			if(PlayTvDiversity.isMonitorPIPSupported()) {
				mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP;
			}else {
				mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH;
			}
		}
		else if(sessionType.equals(ITVSessionContext.SESSION_TYPE_PIP_PREVIEW)){
			Log.v(LOG_TAG,"setSessionType... session type = SESSION_TYPE_PIP_PREVIEW ");
			mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH;
		}
		else if(sessionType.equals(ITVSessionContext.SESSION_TYPE_AUX_OBSERVER)){
			Log.v(LOG_TAG,"setSessionType... session type = SESSION_TYPE_AUX_OBSERVER ");
			//do not override main type which can be PIP_WATCH or PIP_PREVIEW
		}else {
			//not interested for AuxManager
		}
	}
	
	private void processRequest(int reason, Uri channelUri,boolean camUpgrade) {
		Log.d(LOG_TAG, "PlayTVAuxManager : processRequest  :reason "+reason);
		synchronized(mAuxHandler) {
			Message msg = mAuxHandler.obtainMessage();
			msg.arg1 = reason;
			msg.arg2 = ACTION_REQUEST;
			Bundle b = msg.getData();				
			b.putString("uri", channelUri.toString() );
			b.putBoolean(TvHeaders.CAM_UPGRADE,camUpgrade);
			mAuxHandler.sendMessage(msg);
		}				
	}
	
	private void resetRequest() {
		Log.v(LOG_TAG, "PlayTVAuxManager : resetRequest");
		int reqType = -1;
		if (cplaytvmediaplayer != null) {
			if((cplaytvmediaplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN)  
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) {
				reqType = PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN;
			}
			else if((cplaytvmediaplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH)  
				== PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) {
				setSurface(null);
				reqType = PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH;
			}
			else if((cplaytvmediaplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP)  
				== PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) {
				setSurface(null);
				reqType = PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP;
			} 
			if(reqType > 0) {				
				factory.releaseMPLInstance(reqType, cplaytvmediaplayer);
			}
			
			if((cplaytvmediaplayer.getCurrentPurpose() & (PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH | 
			    PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN | PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP)) == 0) {
				if(mainPlayback != null) {
					mainPlayback.unRegisterListener(AuxTVManager.this);
					mainPlayback = null;
				}
				cplaytvmediaplayer = null;
			}
		}			
	}
	
	/* ITvAbstractPlaybackListener */
	public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber){
		queryUserLockStatus();
		super.onPlayStarted(mediaPlayerUri,headers, medium,presetNumber);
	}
	
	/* ITvAbstractPlaybackListener */
	public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber) {
		if(isMediaListenerRegistered == false) {
			isMediaListenerRegistered = registerOnMediaChangeListener();
		}
		if(mAuxRatingInterfaceInstance != null)	{
			mAuxRatingInterfaceInstance.setParentalRating();			
		}		
		if((mSurface != null) && (cplaytvmediaplayer != null)) {
			/*Need to set valid surface to avoid blank on startup for smoother 
			  surface handover from Nativemediaplayer of TVServer*/
			Log.v(LOG_TAG,"mSurface!!! ");
			cplaytvmediaplayer.setAVSurface(mSurface);
		}
		super.onPlayCompleted(mediaPlayerUri,headers, medium,presetNumber);
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(releaseFollowMain && (cplaytvmediaplayer != null) && 
				  ((cplaytvmediaplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN)  
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN)){
					resetRequest();
				}
			}
		};
		mHandler.post(r);		
	}
	
	/* ITvAbstractPlaybackListener */
	public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
		super.onPlayFailed(mediaPlayerUri,medium,presetNumber,reason);
	}
	
	/* ITvAbstractPlaybackListener */
	public void onPlayError(int error, int what , int extra, int mode){
		if(cplaytvmediaplayer != null) {
			if(error == ITvAbstractPlaybackListener.PLAYERROR_FACTORY) {
				if((cplaytvmediaplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN)  
					!= PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) {
					resetRequest();
					int status = factory.IsMediaPlayerAvailable(mContext, mrequestType,mCurrentMedium, mCurrentChannel);	
					notifyonTuneFailed(auxSelectedUri, getTuneFailureReason(status));
				}else {
					resetRequest();
				}				
			}
		}
		super.onPlayError(error,what,extra,mode);
	}
	
	/* IPlayTvMPLFactoryCallback */
	@Override
	public boolean onAvailable(int clientType) {
		Log.v(LOG_TAG, "PlayTVMediaPlayerFactory returns onAvailable due to " + clientType);
		if((clientType == PlayTVMediaPlayerFactory.REQUEST_TYPE_RECORDING) || (clientType == PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) ||
		   (clientType == PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) || (clientType == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN)) {
			synchronized(mAuxHandler) {
				Medium medium		= PlayTvUtils.getCurrentMedium();
				Uri mainWatchuri 	= PlayTvUtils.getFirstDigitalChannel(mContext,medium);
				if(medium == Medium.MEDIUM_SATELLITE) {
					/*In DVBS single tuner mode,try to enable follow main on DVBT/C for downgrade purpose*/
					if(!factory.IsDualTunerFactoryConfigEnabled(medium)) {
						mainWatchuri 	= PlayTvUtils.getFirstDigitalChannel(mContext,Medium.MEDIUM_TERRESTRIAL);
						if(mainWatchuri == null) {
							mainWatchuri 	= PlayTvUtils.getFirstDigitalChannel(mContext,Medium.MEDIUM_CABLE);
						}
					}
				}
				if(mainWatchuri!=null) {
					Map<String, String> headers = TvURIHelper.getUriHeaders(mContext, mainWatchuri);				
					int channel					= -1;
					
					if((headers != null) && (headers.size() > 0)) {
						if(headers.get(TvHeaders.MEDIUM) != null) {				
							medium 	= Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
						}
						if(headers.get(TvHeaders.PRESET_ID) != null) {				
							channel = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
						}						
						int mplavail = factory.IsMediaPlayerAvailable(mContext, 
								PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN, medium, channel);						
						if(mplavail == PlayTVMediaPlayerFactory.STATUS_AVAILABLE) {
							if(clientType == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) {
								releaseFollowMain = false;
								processRequest(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN,mainWatchuri,false);								
							}else {							
								//process immediately without handler post as downgrade should happen before main watch selection
								cplaytvmediaplayer = factory.getMPLInstance(mContext,PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN,	medium, channel);
								if(cplaytvmediaplayer != null) {
									mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN;
									cplaytvmediaplayer.setAVSurface(null);									
									if(mainPlayback != cplaytvmediaplayer.getPlaybackObject()){
										if(mainPlayback != null) {
											mainPlayback.unRegisterListener(AuxTVManager.this);
										}
										mainPlayback = cplaytvmediaplayer.getPlaybackObject();
										mainPlayback.registerListener(AuxTVManager.this);
									}							
									if(mainPlayback != null) {
										try {
											mainPlayback.play(mainWatchuri,medium,headers);
										}catch(Exception e) {
											Log.d(LOG_TAG,"Exception in select " + e.getLocalizedMessage());
										}
									}
								}
							}
							return true;
						}else {
							Log.d(LOG_TAG, "Mediaplayer not available from factory!!!");
						}
					}
				}else {
					Log.d(LOG_TAG, "getLastSelectedTunerUri returned NULL!!!");
				}
			}
		}
		return false;
	}
	
	/* IPlayTvMPLFactoryCallback */
	@Override
	public boolean onNotAvailable(int clientType) {
		Log.v(LOG_TAG, "PlayTVMediaPlayerFactory returns onNotAvailable");
		if (cplaytvmediaplayer != null) {
			if((cplaytvmediaplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN)  
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) {
					resetRequest();
			}
		}
		return false;
	}
	
	/* IPlayTvMPLFactoryCallback */
	@Override
	public void onOlympicUsecaseUpdate(boolean enable, boolean isOTR) {
		
	}
	
	public static ITunerRating getAuxRatingInterfaceInstance(){
		return (ITunerRating)mAuxRatingInterfaceInstance;
	}
	
	private class PowerEventsReceiver implements IPowerEvents {
		
		@Override
		public void onPowerChangeStart(PowerStates from, PowerStates to, Bundle extras) {
			
		}
		
		@Override
		public void onPowerChangeEnd(PowerStates from, PowerStates to, Bundle extras) {
			Log.d(LOG_TAG,"onPowerChangeEnd : from "+from+"to "+to);
			if(to==PowerStates.POWER_STATE_SEMI_STANDBY) {
				releaseFollowMain = true;
			}else if(to==PowerStates.POWER_STATE_FULL_SYSTEM_START) {
				releaseFollowMain = false;				
			}
		}
	}
    
    public static IPowerEvents getPowerEventsListener() {
		return mPowerEventListener;
	}	
	
	public CamInfoImpl getCamInfo(int slotId) {
		if(cplaytvmediaplayer != null) {
			return cplaytvmediaplayer.getCamInfo(slotId);
		}
		return null;
	}
}
