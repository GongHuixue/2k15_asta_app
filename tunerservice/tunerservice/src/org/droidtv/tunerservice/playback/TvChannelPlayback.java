package org.droidtv.tunerservice.playback;

import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tv.media.IPlayTVControl.IPlayTVControlListener;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tunerservice.util.TvURIHelper.UriData;
import org.droidtv.tv.media.ITvMediaRecordControl.PlaybackEitInfo;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.tvinput.ITVTunerSession;
import java.util.Map;

import android.content.ContentValues;
import android.content.Context;
import android.net.Uri;
import android.util.Log;
import java.util.List;
import java.util.ArrayList;
import android.os.Handler;
import org.droidtv.tunerservice.recording.TimeshiftRecording;
//import org.droidtv.playtv.osds.ChannelFilter;

import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;

public class TvChannelPlayback extends TvAbstractPlayback{
	PlayTVFacMediaPlayer playtvmpl;
	IPlayTVControlListener tvViewListener = null;
	TimeshiftPlayback timeshiftPlay = null;
	private String TAG;
	private Context mContext;
	private boolean playing = true;
	private Handler mHandler= null;
	//PlayTvHelpContext mPlayTvHelpContext;
	Object syncObj=null;
	private TimeshiftRecording tsRecording;
	private List<ITvAbstractPlaybackListener> mPlaybackListener = null;
	private int PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
	private TimeshiftRecording TimeshiftRecordingobject = null;
	private TvAbstractPlaybackListener TSPlaybackListener = null;
	private PlaytvStateChangeCallbacks mPlayTvStateChangeListener = null;
	private boolean trickmodeStatus = true;
	// Criteria, based on which released of playback is done
	private int releaseCriterion = PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH |
									PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD |
									PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD;

	
	public TvChannelPlayback(Context context, PlayTVFacMediaPlayer mpl) {
		mContext = context;
		playtvmpl = mpl;
		TAG = "TvChannelPlayback-" + mpl.getMediaPlayerInstance().getToken();
		Log.d(TAG,"TvChannelPlayback created ");
		syncObj = new Object();
		mHandler= new Handler();
		mPlaybackListener = new ArrayList<ITvAbstractPlaybackListener>();
		// Timeshift will be associated with each playback 	
		// Quick fix - TO BE REMOVED
		if (playtvmpl.getMediaPlayerInstance().getToken() == 0) {
			TimeshiftRecordingobject = new TimeshiftRecording(mContext, this);
		}
		TSPlaybackListener = new TvAbstractPlaybackListener();
		mPlayTvStateChangeListener = new PlaytvStateChangeCallbacks();
	}
	
	@Override
	public void setPlayer(PlayTVFacMediaPlayer mpl) {
		Log.d(TAG,"TvChannelPlayback setPlayer called ");
		synchronized (syncObj) {
			playtvmpl = mpl;
		}
	}
	
	@Override
	public void play(Uri CurrentUri,Map<String,String> headers) {
		Log.d(TAG, "play :: Uri = " + CurrentUri);
		releaseTimeshiftPlay();
		playtvmpl.registerPlayBackListener(mPlayTvStateChangeListener, TAG);
		playtvmpl.PlayChannel(CurrentUri , headers); 
		trickmodeStatus = true;
	}
	
	@Override
	public void play(Uri CurrentUri,Medium medium, Map<String,String> headers) {
		releaseTimeshiftPlay();
		playtvmpl.registerPlayBackListener(mPlayTvStateChangeListener, TAG);
		playtvmpl.PlayChannel(CurrentUri,headers);
		trickmodeStatus = true;
	}
	
	@Override
	public void playOlympicChannel(Uri uri,Medium medium, Map<String,String> headers) {
		releaseTimeshiftPlay();
		playtvmpl.registerPlayBackListener(mPlayTvStateChangeListener, TAG);
		playtvmpl.PlayOlympicChannel(uri,headers);
		trickmodeStatus = true;
	}

	@Override
	public void playCatchUpChannel(Uri uri,Medium medium, Map<String,String> headers) {
		Log.d(TAG, "playCatchUpChannel "+uri);
		playtvmpl.registerPlayBackListener(mPlayTvStateChangeListener, TAG);
		playtvmpl.PlayCatchUpChannel(uri,headers);
		if (timeshiftPlay != null) {
			timeshiftPlay.playCatchUpChannel(uri, medium, headers);
		}
	}
	
	@Override
	public void stop() {
		if(timeshiftPlay != null) {
			timeshiftPlay.stop();
		} else {
			Log.e(TAG, "stop not supported for channels");
		}
	}

	/* Recording is currently using this to start recording*/
	@Override
	public void play(final Uri uri) {
		try {
			releaseTimeshiftPlay();
			Map<String, String> headers = TvURIHelper.getUriHeaders(mContext, uri);
			if(headers !=null ) {
				play(uri,headers);
			}else {
				Log.d(TAG,"no such channel and hence play failed!!!");
				Runnable r = new Runnable() {
					@Override
					public void run() {
						onPlayFailed(uri, Medium.MEDIUM_INVALID,-1,ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
					}
				};
				mHandler.post(r);
			}
			trickmodeStatus = true;
		} catch(Exception e) {
			Log.d(TAG,"Exception " + e.getLocalizedMessage());
		}
	}

	// This will be called from main thread only..
	public void closeTimeshiftPlay() {
		Log.d(TAG, "closeTimeshiftPlay");
		if(timeshiftPlay != null) {
			// notify state change, since we are switching from timeshift to channel
		   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
		   onPlayStateChanged(PlaybackState);
			timeshiftPlay = null;
		} else {
			Log.d(TAG, "timeshiftPlay is already null");
		}
	}

	@Override
	public int getTotalDuration(){
		if (TimeshiftRecordingobject != null) {
			return (int)TimeshiftRecordingobject.getTotalDuration();
		} else {
			return 0;
		}
	}

	@Override
	public boolean pause() {
		boolean status = false;
		if(timeshiftPlay != null ) {
			timeshiftPlay.pause();
		} else {
			Log.d(TAG, "pause on live");
			playtvmpl.getMediaPlayerInstance().pause();
			//reset minimum data available on entering timeshift pause.
			if(TimeshiftRecordingobject != null)
			{
				TimeshiftRecordingobject.resetMinimumDataAvailable();
			}
			timeshiftPlay = new TimeshiftPlayback(mContext, this, playtvmpl, TSPlaybackListener);
			if (TimeshiftRecordingobject != null) {
				timeshiftPlay.setTimeShiftInfo(TimeshiftRecordingobject.getEitInfo());
			}
			playtvmpl.startTimeshiftPause();
			
			PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED;
			onPlayStateChanged(PlaybackState);
			status = true;
		}
		return status;
	}

	@Override
	public void resume() {
		if(timeshiftPlay != null) {
			timeshiftPlay.resume();
		} else {
			Log.e(TAG, "resume not supported");
		}
	}

	@Override
	public void seekTo(int msecs) {
		if(timeshiftPlay != null) {
			timeshiftPlay.seekTo(msecs);
		} else {
			Log.d(TAG, "seekto on live " + msecs);
			timeshiftPlay = new TimeshiftPlayback(mContext, this, playtvmpl, TSPlaybackListener);
			if (TimeshiftRecordingobject != null) {
				timeshiftPlay.setTimeShiftInfo(TimeshiftRecordingobject.getEitInfo());
			}
			timeshiftPlay.seekTo(msecs);
		}
	}
	
	@Override
	public void enableTrickModes(boolean status) {
		if (timeshiftPlay != null) {
			timeshiftPlay.enableTrickModes(status);
		}
		trickmodeStatus = status;
	}
	
	@Override
	public boolean getTrickmodeStatus() {
		if (timeshiftPlay != null) {
			return timeshiftPlay.getTrickmodeStatus();
		}
		return trickmodeStatus;
	}

	public void setSpeed(int speed, boolean forward) {
		if(timeshiftPlay != null) {
			timeshiftPlay.setSpeed(speed,forward);
		} else {
			Log.d(TAG, "set speed on live " + speed + " , " + forward);
			playtvmpl.getMediaPlayerInstance().pause();
			timeshiftPlay = new TimeshiftPlayback(mContext, this, playtvmpl, TSPlaybackListener);
			if (TimeshiftRecordingobject != null) {
				timeshiftPlay.setTimeShiftInfo(TimeshiftRecordingobject.getEitInfo());
			}
			timeshiftPlay.setSpeed(speed, forward);
		}
	}

	public void onPlayStarted(Uri CurrentUri,Map<String,String> headers, Medium medium, int presetNumber) {
		Log.d(TAG, "onPlayStarted - Uri = "+ CurrentUri);
		synchronized (syncObj) {
			Log.d(TAG, "onPlayStarted ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayStarted(CurrentUri, headers, medium, presetNumber);
				}
			}
			PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
			onPlayStateChanged(PlaybackState);
		}
	}

	public void onPlayCompleted(Uri CurrentUri, Map<String,String> headers, Medium medium, int presetNumber) {
		Log.d(TAG, "onPlayCompleted");
		//PlayTvUtils.storeCurrentChannel(CurrentUri, medium, presetNumber);	
		//PlayTvUtils.storeLastSelectedDevice(medium);
		//if(isNewPreset(CurrentUri)){
			//resetNewFlag(CurrentUri);
		//}
		synchronized (syncObj) {
			Log.d(TAG, "onPlayCompleted ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayCompleted(CurrentUri, headers, medium, presetNumber);
				}
			}
		}
	}

	public void onPlayFailed(Uri CurrentUri, Medium medium, int presetNumber, int reason) {
		Log.e(TAG, "play failed for channel");
		synchronized (syncObj) {
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayFailed(CurrentUri, medium, presetNumber, reason);
				}
			}
			PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
			onPlayStateChanged(PlaybackState);
		}
	}

	public void onPlayFinished(Uri CurrentUri, Medium medium, int presetNumber) {
		Log.e(TAG, "onPlayFinished not expected");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayFinished(CurrentUri, medium, presetNumber);
				}
			}
		PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
		onPlayStateChanged(PlaybackState);
	}

	public boolean onError(PlayTvMediaPlayer mpl, int what , int extra) {
		//similar to release code..
		Log.d(TAG, "onError");
		if(timeshiftPlay != null) {
			timeshiftPlay.onError(mpl,what,extra); //order is important..notify tvview last..
			timeshiftPlay = null;			
		} else {
			PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
			onPlayStateChanged(PlaybackState);
		}
		if((what == -1) && (extra == -1)) {
			onPlayError(ITvAbstractPlaybackListener.PLAYERROR_FACTORY, what, extra);
		}else {
			onPlayError(ITvAbstractPlaybackListener.PLAYERROR_SYSTEM, what, extra);
		}
		return true;
	}
	
	@Override
	public void release() {
		if (TimeshiftRecordingobject != null) {
			TimeshiftRecordingobject.release();
		}
		if(timeshiftPlay != null) {
			timeshiftPlay.release();
			timeshiftPlay = null;
		}	
	}

	@Override
	public int getCurrentDuration() {
		try {
			if(timeshiftPlay != null) {
				return timeshiftPlay.getCurrentDuration();
			} else if (TimeshiftRecordingobject != null) {
				Log.d(TAG, "Rohit: call landed getRecordedDuration");
				return (int)TimeshiftRecordingobject.getRecordedDuration();
			}
		} catch (Exception e) {
			Log.e(TAG, "Exception in getCurrentDuration - "+e.toString());
		}
		return 0;
	}
	
	@Override
	public int getCurrentTimeShiftStatus() {
		if (TimeshiftRecordingobject != null) {
			return TimeshiftRecordingobject.getCurrentTimeShiftStatus();
		}
		// Fix added to handle Olympic usecase.
		// In Olympic use-case main-watch will be on tuner-2, 
		// where timeshift is not currently created.
		// Will be removed once acquire-release changes for independent-tad and
		// changes to add timeshift as a sub-purpose along with main-watch/independent-tad
		// is done.
		else {
			return ITVTunerSession.TIMESHIFT_RECORDING_NOTACTIVE_RECORDING_IN_PROGRESS;
		}
	}
	
	@Override
	public long getRecordedDuration() {
		 if (TimeshiftRecordingobject != null) {
			return TimeshiftRecordingobject.getRecordedDuration();
		 }
		 return 0;
	}	

	@Override
	public PlaybackEitInfo getTimeshiftInfo() {
		 if (timeshiftPlay != null) {
			return timeshiftPlay.getTimeshiftInfo();
		 } else if (TimeshiftRecordingobject != null) {
			// if playback is not started yet, return live info
			return TimeshiftRecordingobject.getEitInfo();
		 }
		 return null;
	}

	@Override
	public boolean isPlaying() {
		return playtvmpl.getMediaPlayerInstance().isPlaying();
	}
	
	public void onLockStatusChanged(int type, int status) {
		Log.i(TAG,"onLockStatusChanged ");
		synchronized (syncObj) {
			onLockStatusChangedNotify(type, status);
		}
	}

	@Override
	public Medium getMedium() {
		if(timeshiftPlay != null) {
			return timeshiftPlay.getMedium();
		} else if(playtvmpl != null) {
			return playtvmpl.getCurrentMedium();
		}
		return Medium.MEDIUM_INVALID;
	}

	@Override
	public int getServiceType() {
		if(playtvmpl != null) {
			return playtvmpl.getServiceType();
		}
		return PlayTvMediaPlayer.SERVICE_TYPE_INVALID;
	}
	
	@Override
	public boolean isTimeshiftActive() {
		if(timeshiftPlay != null) {
			if(timeshiftPlay.isTSPlayBackActive()) {
				Log.i(TAG,"isTimeshiftActive return true");
				return true;	
			}
		}
		Log.i(TAG,"isTimeshiftActive return false");
		return false;
	}

	private boolean isNewPreset(Uri uri){
		boolean isNewChannel = false;
		if(uri != null){
			String isNewPreset = uri.getQueryParameter(IChannelContract.C_NEWPRESET);
			if(isNewPreset != null){
				int isNew = Integer.parseInt(isNewPreset);
				if(isNew == 1){
					isNewChannel = true;
				}
			}
		}
		Log.d(TAG, "isNewPreset - Returning isNewPreset = " + isNewChannel + " , Uri = " + uri);
		return isNewChannel;
	}
	
	private void resetNewFlag(Uri currentUri) {
		Uri dbUri = PlayTvUtils.getCurrentTvContentProviderUri();
		ContentValues values = new ContentValues();
		values.put(IChannelContract.C_NEWPRESET, 0);
		UriData data = TvURIHelper.parseUri(mContext, currentUri);
		String  channel = null;
		if(data != null){
			channel  = Integer.toString(data.channel);
			mContext.getContentResolver().update(dbUri, values, IChannelContract.C_PRESET_ID+"=?", new String []{channel});
			Log.d(TAG, "Succesfully updated with C_NEWPRESET = 0 for ChannelNumber = " + channel);
			/*if(ChannelFilter.getChannelFilterInstance(mContext) != null){
				ChannelFilter.getChannelFilterInstance(mContext).UpdateCursor();
			}else{
				Log.d(TAG, "Channel filter instance is NULL, Can't update cursor ");
			}*/
		}
	}	
	
	private void releaseTimeshiftPlay() {
		if(timeshiftPlay != null) {
			timeshiftPlay.release();
			timeshiftPlay = null;
		}
	}

	@Override
	public void registerListener(ITvAbstractPlaybackListener listener) {
		synchronized (mPlaybackListener) {
			if(!mPlaybackListener.contains(listener)) {
				mPlaybackListener.add(listener);
			}
		}
	}
	
	@Override
	public void unRegisterListener(ITvAbstractPlaybackListener listener) {
		synchronized (mPlaybackListener) {
			if(mPlaybackListener.contains(listener)) {
				mPlaybackListener.remove(listener);
			}
		}
	}

	public void onPlayStateChanged(int state) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onPlayStateChanged(state, ITvAbstractPlaybackListener.MODE_TIMESHIFT);
			}
		}
	}

	public TimeshiftRecording getTimeshiftRecordingObject() {
		return TimeshiftRecordingobject;
	}

	public void onPlayError(int error, int what, int extra) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onPlayError(error, what, extra, ITvAbstractPlaybackListener.MODE_TIMESHIFT);
			}
		}
	}

	public void onLockStatusChangedNotify(int type, int status) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onLockStatusChanged(type, status);
			}
		}
	}

	public void onInfo(boolean cicamAvailable) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onInfo(cicamAvailable);
			}
		}
	}

	public void onMPLPurposeChanged(int purpose) {
		Log.d(TAG, "onMPLPurposeChanged purpose:"+purpose);
		if ((playtvmpl != null) && ((playtvmpl.getCurrentPurpose() & releaseCriterion) == 0)) {
			release();
		}
			
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onMPLPurposeChanged(purpose);
			}
		}
	}
	
	@Override
	public int getPlaybackState() {
		if (timeshiftPlay != null) {
			return timeshiftPlay.getPlaybackState();
		}
		return PlaybackState;
	}
	
	public class TvAbstractPlaybackListener implements ITvAbstractPlaybackListener {
		
		@Override
		public void onPlayStarted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber) {
			Log.d(TAG, "onPlayStarted ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayStarted(uri, headers, medium, presetNumber);
				}
			}
		}
		
		@Override
		public void onPlayCompleted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber) {
			Log.d(TAG, "onPlayCompleted ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayCompleted(uri, headers, medium, presetNumber);
				}
			}
		}

		@Override
		public void onPlayFailed(Uri uri, Medium medium, int presetNumber, int reason) {
			Log.d(TAG, "onPlayFailed ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayFailed(uri, medium, presetNumber, reason);
				}
			}
		}

		@Override
		public void onPlayFinished(Uri uri, Medium medium, int presetNumber) {
			Log.d(TAG, "onPlayFinished ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayFinished(uri, medium, presetNumber);
				}
			}
		}

		@Override
		public void onLicenseExchangeHappening(boolean status) {
			Log.d(TAG, "onLicenseExchangeHappening "+status);
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onLicenseExchangeHappening(status);
				}
			}
		}
		
		@Override
		public void onSeekComplete(int mode) {
			Log.d(TAG, "onSeekComplete");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onSeekComplete(mode);
				}
			}
		}

		@Override
		public void onPlayError(int error, int what, int extra, int mode) {
			Log.d(TAG, "onPlayError "+error+" what:"+what+" extra:"+extra);
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayError(error, what, extra, mode);
				}
			}
		}

		@Override
		public void onServiceTypeDetected(int type) {
			Log.d(TAG, "onServiceTypeDetected "+type);
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onServiceTypeDetected(type);
				}
			}
		}

		@Override
		public void onTrickModeEnabled(boolean status, int mode) {
			Log.d(TAG, "onTrickModeEnabled "+status);
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onTrickModeEnabled(status, mode);
				}
			}
		}

		@Override
		public void onPlayStateChanged(int state, int mode) {
			Log.d(TAG, "onPlayStateChanged ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayStateChanged(state, mode);
				}
			}
		}

		@Override
		public void onLockStatusChanged(int type, int status) {
			Log.d(TAG, "onLockStatusChanged ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onLockStatusChanged(type, status);
				}
			}
		}

		@Override
		public void onInfo(boolean cicamAvailable) {
			Log.d(TAG, "onInfo ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onInfo(cicamAvailable);
				}
			}
		}

		@Override
		public void onMPLPurposeChanged(int purpose) {
			Log.d(TAG, "onMPLPurposeChanged ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onMPLPurposeChanged(purpose);
				}
			}
		}

		@Override
		public void onTimeshiftInfoChanged() {
			Log.d(TAG, "onTimeshiftInfoChanged ");
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onTimeshiftInfoChanged();
				}
			}
		}
	}

	public class PlaytvStateChangeCallbacks implements IPlayTvStateChangeListener {
		@Override
		public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber) {
			TvChannelPlayback.this.onPlayStarted(mediaPlayerUri, headers, medium, presetNumber);
		}
		
		@Override
		public void onPlayCompleted(Uri mediaPlayerUri,  Map<String,String> headers, Medium medium, int presetNumber) {
			TvChannelPlayback.this.onPlayCompleted(mediaPlayerUri, headers, medium, presetNumber);
		}
		
		@Override
		public void onPlayFinished(Uri mediaPlayerUri, Medium medium, int presetNumber) {
			TvChannelPlayback.this.onPlayFinished(mediaPlayerUri, medium, presetNumber);
		}
		
		@Override
		public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
			TvChannelPlayback.this.onPlayFailed(mediaPlayerUri, medium, presetNumber, reason);
		}
		
		@Override
		public void onInfo(boolean cicamAvailable) {
			TvChannelPlayback.this.onInfo(cicamAvailable);
		}
		
		@Override
		public void onError(PlayTvMediaPlayer mpl, int what , int extra) {
			TvChannelPlayback.this.onError(mpl, what, extra);
		}
		
		@Override
		public void onLockStatusChanged(int type, int status) {
			TvChannelPlayback.this.onLockStatusChanged(type, status);
		}
		
		@Override
		public void onPurposeChanged(int purpose) {
			TvChannelPlayback.this.onMPLPurposeChanged(purpose);
		}
		
		@Override
		public void onUriChanged(Uri mediaPlayerUri) {
		}
		
		@Override
		public void onCamUpgradeStarted(boolean status) {
		}
	}	
}
