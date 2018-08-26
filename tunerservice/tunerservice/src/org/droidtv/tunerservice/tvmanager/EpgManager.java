package org.droidtv.tunerservice.tvmanager;

import org.droidtv.tunerservice.playback.TvAbstractPlayback;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tv.tvinput.ITVSessionContext;
import android.media.tv.TvInputService.Session;
import android.os.Bundle;
import android.os.Handler;
import android.view.Surface;
import android.util.Log;
import android.net.Uri;
import android.content.Context;
import java.util.Map;
import java.lang.Integer;
import org.droidtv.tunerservice.TunerService;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.media.TvMediaPlayerContext;
import org.droidtv.tv.tvinput.CamInfoImpl;
import org.droidtv.tv.video.ITvVideoManager;

public class EpgManager extends AbstractManager{
	private String LOG_TAG  			= "EpgManager";
	private PlayTVFacMediaPlayer cplaytvmediaplayer = null;
	private TvAbstractPlayback mainPlayback 	= null;	
	private PlayTVMediaPlayerFactory factory 	= null;
	private boolean isMainSession 				= true;
	private int mrequestType	  				= -1;
	private Session mCurrentActiveSession		= null;
	private Handler	mHandler					= null;
	private Medium facmedium=  TvURIHelper.Medium.MEDIUM_INVALID;
	private Uri mCurrentUri = null;
	
	public EpgManager(Context pContext, boolean fg){
		if(fg) {
			LOG_TAG += "fg";
		} else {
			LOG_TAG += "bg";
		}
		mContext	= pContext;
		factory		= PlayTVMediaPlayerFactory.getInstance();
		mHandler	= new Handler();
	}
	
	@Override
	public void setSessionType(String sessionType) {
		if(sessionType.equals(ITVSessionContext.SESSION_TYPE_EPG_ACQUISITION)){
			Log.i(LOG_TAG,"setSessionType... session type = SESSION_TYPE_EPG_ACQUISITION ");
			mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_DATA_ACQUISITION;
		}else if(sessionType.equals(ITVSessionContext.SESSION_TYPE_EPG_FOREGROUND_ACQUISITION)){
			Log.i(LOG_TAG,"setSessionType... session type = SESSION_TYPE_EPG_FOREGROUND_ACQUISITION ");
			mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_DATA_ACQUISITION;
		}else {
			//not interested for EpgManager
		}
	}
	
	@Override
	public void setSession(final Session session, final Surface surface) {
		if(mHandler != null) {
			Runnable r = new Runnable() {
				@Override
				public void run() {					
					mCurrentActiveSession 	= session;
				}
			};
			mHandler.post(r);
		}	
	}
	
	@Override
	public Session getCurrentActiveSession() {
		return mCurrentActiveSession;
	}
	
	@Override
	public void tune(final Uri pChannelUri,final Bundle params) {
		Log.i(LOG_TAG,"tune called with Bundle: ");		
		if(mHandler!=null){
			mHandler.post(new Runnable() {				
				@Override
				public void run() {
					mCurrentUri = pChannelUri;
					Map<String, String> headers = null;
					String tuneType =  ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT;
					if(params != null) {
						tuneType = params.getString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE);
					}
					if((tuneType != null) && (tuneType.equals(ITVSessionContext.TUNE_REQUEST_TYPE_CUSTOM))){
						headers = TvURIHelper.getHeadersFromBundle(mContext,params);
						if( (pChannelUri != null) && (headers != null) ) {
							headers.put(TvHeaders.COMPLETE_URI,pChannelUri.toString());
						}
					} else if((tuneType != null) && (tuneType.equals(ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT))) {
						if(pChannelUri != null) {
							headers = TvURIHelper.getUriHeaders(mContext, pChannelUri);
						}
					}
					if((headers == null) || (headers.size() == 0)) {
						onPlayFailed(pChannelUri,Medium.MEDIUM_INVALID, 0, ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
						return;
					}
					if(headers.get(TvHeaders.MEDIUM) != null){
						facmedium =	TvURIHelper.Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
					}
					headers.put(TvHeaders.SELECTION_TYPE,Integer.toString(TvURIHelper.SelectionType.SELECTION_NORMAL.value));
					headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_NONE));
					cplaytvmediaplayer = factory
								.getMPLInstance(
									mContext,
									mrequestType,
									facmedium, 
									-1);
					if(cplaytvmediaplayer != null) {				
						if(mainPlayback != cplaytvmediaplayer.getPlaybackObject()){
							if(mainPlayback != null) {
								mainPlayback.unRegisterListener(EpgManager.this);
							}
							mainPlayback = cplaytvmediaplayer.getPlaybackObject();
							mainPlayback.registerListener(EpgManager.this);
							Log.i(LOG_TAG,"mainPlayback : registerListener : "+mainPlayback);				
						}
						if(mainPlayback != null) {
							mainPlayback.play(pChannelUri , headers); 
						}
					}else {
						//do additional call to know the reason for failure					
						int status = factory.IsMediaPlayerAvailable(
									mContext,
									mrequestType,
									facmedium,
									-1);
						onPlayFailed(pChannelUri,facmedium, -1, getTuneFailureReason(status));
					}
				}
			});
		}		
	}
	
	@Override
	public TvMediaPlayerContext getTvMediaPlayerContext(){
		if(cplaytvmediaplayer != null) {
			return ((TvMediaPlayerContext)cplaytvmediaplayer.getMediaPlayerInstance().getTvMediaPlayerContext());
		}
		return null;
	}

	private void resetRequest() {
		Log.d(LOG_TAG, "resetRequest");
		if(cplaytvmediaplayer != null) {
			if(mainPlayback != null) {
				mainPlayback.unRegisterListener(EpgManager.this);
				mainPlayback = null;
			}
			factory.releaseMPLInstance(mrequestType,cplaytvmediaplayer);			
			cplaytvmediaplayer	= null;
			mrequestType		= -1;
		}
	}
	
	@Override
	public void release(final TunerService.TunerSession pSession){
		Log.i(LOG_TAG,"release : ");
		if(mHandler != null) {
			Runnable r = new Runnable() {
				@Override
				public void run() {
					if(mCurrentActiveSession == pSession) {
						resetRequest();
						mCurrentActiveSession	= null;
					}
				}
			};
			mHandler.post(r);
		}		
	}

	/* ITvAbstractPlaybackListener */
	public void onPlayError(int error, int what , int extra, int mode){
		if(cplaytvmediaplayer != null) {
			if(error == ITvAbstractPlaybackListener.PLAYERROR_FACTORY) {
				int status = factory.IsMediaPlayerAvailable(mContext, mrequestType, facmedium, -1);	
				resetRequest();
				notifyonTuneFailed(mCurrentUri, getTuneFailureReason(status));
			}
		}
		super.onPlayError(error,what,extra,mode);
	}
	
	public CamInfoImpl getCamInfo(int slotId) {
		if(cplaytvmediaplayer != null) {
			return cplaytvmediaplayer.getCamInfo(slotId);
		}
		return null;
	}
}
