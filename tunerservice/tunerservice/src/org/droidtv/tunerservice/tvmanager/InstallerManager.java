package org.droidtv.tunerservice.tvmanager;

import org.droidtv.tunerservice.playback.TvAbstractPlayback;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;

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

public class InstallerManager extends AbstractManager{
	private static final String LOG_TAG  = "InstallerManager";
	//private Context mContext 	= null;
	private PlayTVFacMediaPlayer cplaytvmediaplayer = null;
	private	TvAbstractPlayback mainPlayback 	= null;	
	private PlayTVMediaPlayerFactory factory 	= null;
	private Surface mSurface 				 	= null;
	private Session mCurrentActiveSession		= null;
	private Handler mHandler					= null;
	private int mrequestType      				= PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER;
	
	public InstallerManager(Context pContext){
		mContext	= pContext;
		factory		= PlayTVMediaPlayerFactory.getInstance();
		mHandler 	= new Handler();
	}
	
	public void setSessionType(String sessionType) {
		if(sessionType.equals(ITVSessionContext.SESSION_TYPE_INSTALLER)){
			Log.i(LOG_TAG,"setSessionType = SESSION_TYPE_INSTALLER_MAIN ");
			mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER;
			try {
				Log.i(LOG_TAG,"PowerState " + ITvPowerManager.Instance.getInterface().GetPowerState() );
				if(ITvPowerManager.Instance.getInterface().GetPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY) {
					mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY;
				}
			}catch(Exception e) {
				Log.e(LOG_TAG,"Exception accessing ITvPowerManager");
			}
		}else if(sessionType.equals(ITVSessionContext.SESSION_TYPE_INSTALLER_AUX)){
			Log.i(LOG_TAG,"setSessionType = SESSION_TYPE_INSTALLER_AUX ");
			mrequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_INSTALLER;
		}
	}
	
	public void tune(final Uri pChannelUri,final Bundle params) {
		Log.i(LOG_TAG,"tune called with Bundle: ");		
		if(mHandler!=null){
			mHandler.post(new Runnable() {				
				@Override
				public void run() {
					Medium facmedium=  	TvURIHelper.Medium.MEDIUM_INVALID;
					String tuneType = 	params.getString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE);
					if((tuneType != null) && (tuneType.equals(ITVSessionContext.TUNE_REQUEST_TYPE_CUSTOM))){
						Map<String, String> headers = TvURIHelper.getHeadersFromBundle(mContext,params);	
						if((headers == null) || (headers.size() == 0)) {
							onPlayFailed(pChannelUri,Medium.MEDIUM_INVALID, 0, ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
							return;
						}
						if(pChannelUri != null) {
							headers.put(TvHeaders.COMPLETE_URI,pChannelUri.toString());
						}
						headers.put(TvHeaders.SELECTION_TYPE,Integer.toString(TvURIHelper.SelectionType.SELECTION_INSTALL.value));
						if(headers.get(TvHeaders.MEDIUM) != null){
							facmedium =	TvURIHelper.Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
						}
						cplaytvmediaplayer = factory
								.getMPLInstance(
										mContext,
										mrequestType,
										facmedium, 
										-1);
						if(cplaytvmediaplayer != null) {
							cplaytvmediaplayer.setAVSurface(null);
							if(mainPlayback != cplaytvmediaplayer.getPlaybackObject()){
								if(mainPlayback != null) {
									mainPlayback.unRegisterListener(InstallerManager.this);
								}
								mainPlayback = cplaytvmediaplayer.getPlaybackObject();
								mainPlayback.registerListener(InstallerManager.this);
								Log.i(LOG_TAG,"mainPlayback : registerListener : "+mainPlayback);				
							}
							if(mainPlayback != null) {
								mainPlayback.play(pChannelUri , headers); 
							}
						}else {
							int status = factory.IsMediaPlayerAvailable(
								mContext,
								mrequestType,
								facmedium,
								-1);
					
							onPlayFailed(pChannelUri,facmedium, -1, getTuneFailureReason(status));
						}
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
	
	@Override
	public void setSession(final Session session, final Surface surface) {		
		if(mHandler != null) {
			Runnable r = new Runnable() {
				@Override
				public void run() {
					mCurrentActiveSession 	= session;
					mSurface 				= surface;
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
    public void setSurface(Surface pSurface){
		Log.d(LOG_TAG, "InstallerManager pSurface:" + pSurface);
		mSurface = pSurface;
		if(cplaytvmediaplayer != null) {
			Log.v(LOG_TAG,"mSurface!!! ");
			cplaytvmediaplayer.setAVSurface(mSurface);
		}
	}
	
	@Override
	public void release(final TunerService.TunerSession pSession){
		Log.i(LOG_TAG,"release : ");
		if(mHandler != null) {
			Runnable r = new Runnable() {
				@Override
				public void run() {
					if(pSession == mCurrentActiveSession) {
						if(cplaytvmediaplayer != null) {
							setSurface(null);
							if(mainPlayback != null) {
								mainPlayback.unRegisterListener(InstallerManager.this);
								mainPlayback = null;
							}
							factory.releaseMPLInstance(mrequestType,cplaytvmediaplayer);
							cplaytvmediaplayer		= null;			
						}
						mCurrentActiveSession	= null;
					}
				}
			};
			mHandler.post(r);
		}
	}
	
	public void enableCAMUI(boolean enable) {
			Log.d(LOG_TAG,"enableCAMUI called with enable = " + enable);
			if(cplaytvmediaplayer != null){
				cplaytvmediaplayer.enableCAMUI(enable);
			}
			else{
				Log.d(LOG_TAG,"cplaytvmediaplayer is null");
			}
				
	}
	
	
	public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber) {
		if(mSurface != null) {
			Log.v(LOG_TAG,"mSurface!!! ");
			cplaytvmediaplayer.setAVSurface(mSurface);
		}
		super.onPlayCompleted(mediaPlayerUri,headers,medium,presetNumber);
	}
	
	public CamInfoImpl getCamInfo(int slotId) {
		if(cplaytvmediaplayer != null) {
			return cplaytvmediaplayer.getCamInfo(slotId);
		}
		return null;
	}
}
