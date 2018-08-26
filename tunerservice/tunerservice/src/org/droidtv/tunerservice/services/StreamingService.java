package org.droidtv.tunerservice.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.playback.TvAbstractPlayback;
import org.droidtv.tunerservice.playback.PvrPlayback;
import org.droidtv.tunerservice.interfaces.IPlayTvMPLFactoryCallback;
import org.droidtv.tv.media.BcstConstants;
import org.droidtv.tv.media.ITvMediaRecordControl.IonTvRecordControlCallback;
import org.droidtv.tv.tvinput.ITvStreamingControl;
import org.droidtv.tv.media.ITvStreamingPlayControl;
import org.droidtv.tv.media.TvMediaPlayerContext;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tunerservice.util.TvURIHelper.UriData;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.tvinput.ITVTunerSession.ITunerSessionCallbacks;
import org.droidtv.tv.tvinput.ITVSessionContext.ISessionContextCallbacks;
import android.app.Service;
import android.content.Intent;
import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;
import android.media.tv.TvInputInfo;
import android.media.tv.TvInputManager;
import android.media.tv.TvInputManager.SessionCallback;
import android.media.tv.TvInputManager.TvInputCallback;
import android.media.tv.TvInputManager.Session;
import android.media.tv.TvTrackInfo;
import android.media.tv.TvContentRating;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tunerservice.PlayTvDiversity;

public class StreamingService extends Service implements ITvStreamingControl, ITvStreamingPlayControl {

	// TAG for streaming service
	private static final String TAG = "StreamingService";
	// Runnable variables
	private RunPrepareStreaming mPrepareStreamingRunnable = null;
	private RunStreaming mStreamingRunnable = null;
	private RunStreamingNotification mStreamingNRunnable = null;
	private RunTvAbstractPlaybackListener mTVAbsPlayListenerRunnable = null;
	private RunTunerSessionCallbacks mTunerSessionCallbacksRunnable = null;
	private Handler mHandler = null;
	private Thread mStreamingThread = null;
	// Runnable Action definition
	// Action constants for streaming state machine
	private static final int ACTION_RUNSTREAMING_START_STREAMING = 1;
	private static final int ACTION_RUNSTREAMING_STREAMING_STARTED = 2;
	private static final int ACTION_RUNSTREAMING_STOP_STREAMING = 3;
	private static final int ACTION_RUNSTREAMING_STREAMING_STOPPED = 4;
	private static final int ACTION_RUNSTREAMING_STREAMING_ERROR = 5;
	private static final int ACTION_RUNSTREAMING_FINALIZE_STREAMING = 6;
	private static final int ACTION_RUNSTREAMING_STREAMING_CLOSED = 7;
	private static final int ACTION_RUNSTREAMING_STREAMING_MODE_CHANGED = 8;
	private static final int ACTION_RUNSTREAMING_RELEASE_STREAMING = 9;
	// Action constants for AbstractPlayback listener
	private static final int ACTION_RUNTVABSPLAYLISTENER_PLAYSTARTED = 1;
	private static final int ACTION_RUNTVABSPLAYLISTENER_PLAYCOMPLETED = 2;
	private static final int ACTION_RUNTVABSPLAYLISTENER_PLAYFAILED = 3;
	private static final int ACTION_RUNTVABSPLAYLISTENER_PLAYFINISHED = 4;
	private static final int ACTION_RUNTVABSPLAYLISTENER_SEEKCOMPLETE = 5;
	private static final int ACTION_RUNTVABSPLAYLISTENER_PLAYERROR = 6;
	private static final int ACTION_RUNTVABSPLAYLISTENER_TRICKMODECHANGE = 7;
	private static final int ACTION_RUNTVABSPLAYLISTENER_PLAYSTATECHANGE = 8;
	private static final int ACTION_RUNTVABSPLAYLISTENER_ONMPLPURPOSECHANGED = 9;
	private static final int ACTION_RUNTVABSPLAYLISTENER_TIMESHIFTPLAYSTATECHANGE = 10;
	// Action constants for SessionCallbacks
	private static final int ACTION_RUNTUNERSESSIONCALLBACKS_ONCHANNELRETUNED = 1;
	// Streaming state machine
	private StreamingStateDef StreamingState = StreamingStateDef.STATE_IDLE;
	private enum StreamingStateDef {
		STATE_IDLE(0),
		STATE_SELECTION_STARTED(1),
		STATE_SELECTION_COMPLETED(2),
		STATE_TRIGGERED(3),
		STATE_STREAMING(4),
		STATE_STOPPING(5),
		STATE_RELEASING(6);
		private int state;
		private StreamingStateDef(int newstate) {
			state = newstate;
		}
  	}
	// Factory variables
	private PlayTVFacMediaPlayer cplaytvfacmediaplayer = null;
	private PlayTVMediaPlayerFactory factory = null;
	private int mCurrentPurpose = -1;
	// Notifications
	private List<ITvStreamingControlListener> mStreamingControlListener = null;
	private List<ITvStreamingPlayControlListener> mStreamingPlayControlListener = null;
	private TADStatusListenerClass mTADStatusListener = null;
	//private PlaytvStateChangeCallbacks mPlayTvStateChangeListener = null;
	private ITvAbstractPlaybackListener mPlaybackListener = null;
	private IPlayTvMPLFactoryCallback mPlayTvMPLFactoryListener = null;
	// Session variables :( - had to add this since client was not ready to startActivity
	private TvInputCallbackClass mTvInputCallback =  null;
	private TvInputManager mTvInputManager = null;
	private TunerSessionCallback mSessionCallback = null;
	private Handler mSessionHandler = null;
	private Session mSession = null;
	private ITVTunerSession mTunerSession = null;
	private TunerSessionObserver tunerSessionCallbacks = null;
	// Global Variable
	// To store previous tvmpl purpose, used to identify
	// if main_watch was added.
	private int mPreviousPurpose = 0;
	// Cache the last selected streaming mode. To be used on mpl purpose change
	private int mLastSelectedStreamingMode = ITvStreamingControl.STREAMING_NOT_POSSIBLE_RESOURCES_NOT_AVAILABLE;
	// Last requested type for MPL
	private int mLastMPLRequestType = 0;
	// Current usecase Medium (This is added to support release streaming during usecase switch in ssby)
	private Medium mCurrentMedium = Medium.MEDIUM_INVALID; 

	/****************************** ITvStreamingControl Methods Starts here ***********************/

	@Override
	public int getStreamingPossibility(Uri uri) {
		Log.d(TAG, "getStreamingPossibility "+uri);
		uriInfo info = getUriInfo(uri);
		int chId = (info.medium == Medium.MEDIUM_PVRFILE) ? info.recId : info.channelId;
		factory = PlayTVMediaPlayerFactory.getInstance();
		int retVal = ITvStreamingControl.STREAMING_NOT_POSSIBLE_RESOURCES_NOT_AVAILABLE;
		int reason = PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE;
		ITvPowerManager lTvPowerManager = ITvPowerManager.Instance.getInterface();

		if((lTvPowerManager.GetPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY) &&
			((factory.IsMediaPlayerAvailable(StreamingService.this,
										PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD,
										info.medium, chId) & PlayTVMediaPlayerFactory.STATUS_AVAILABLE) != 0)) {
			retVal = ITvStreamingControl.STREAMING_POSSIBLE_INDEPENDENT;
		} else {
			// Independent TAD not possible, so check if dependent TAD is possible
			Log.d(TAG, "Independent TAD not possible, so check if dependent TAD is possible");
			reason = factory.IsMediaPlayerAvailable(StreamingService.this,
									PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD,
									info.medium, chId);
			if ((reason & PlayTVMediaPlayerFactory.STATUS_AVAILABLE) != 0) {
				Log.d(TAG, "STATUS_AVAILABLE");
				PlayTVFacMediaPlayer tmpPlaytvfacmediaplayer = factory.getMPLInstance(
												StreamingService.this,
												PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD,
												info.medium, chId);
				if (tmpPlaytvfacmediaplayer != null) {
					int purpose = tmpPlaytvfacmediaplayer.getCurrentPurpose();
					Log.d(TAG, "Current purpose "+purpose);
					if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) != 0) {
						retVal = ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH;
					} else {
						if (((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) > 0) ||
							((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) > 0)) {
							retVal = ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_RECORDING;
						} else {
							retVal = ITvStreamingControl.STREAMING_NOT_POSSIBLE_RESOURCES_NOT_AVAILABLE;
						}
					}
				} else {
					retVal = ITvStreamingControl.STREAMING_NOT_POSSIBLE_RESOURCES_NOT_AVAILABLE;
				}
			} else {
				Log.d(TAG, "STATUS_NOT_AVAILABLE");
				// dependent TAD not possible, so check if Main-watch is possible
				reason = factory.IsMediaPlayerAvailable(StreamingService.this,
										PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH,
										info.medium, chId);
				if ((reason & PlayTVMediaPlayerFactory.STATUS_AVAILABLE) != 0) {
					Log.d(TAG, "STATUS_AVAILABLE");
					retVal = ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH;
				} else {
					Log.d(TAG, "STATUS_NOT_AVAILABLE");
					// main watch not possible, so check reason and return
					// There is no check for background recording here since this condition will never be hit when
					// background recording is happening. It will either be dependent tad with background or independent tad.
					if ((reason & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) != 0) {
						retVal = ITvStreamingControl.STREAMING_NOT_POSSIBLE_RECORDINGS_IN_PROGRESS;
					} else {
						retVal = ITvStreamingControl.STREAMING_NOT_POSSIBLE_RESOURCES_NOT_AVAILABLE;
					}
				}
			}
		}
		Log.d(TAG, "getStreamingPossibility - uri:"+uri+" medium:"+info.medium+" channelId:"+info.channelId+" retVal:"+retVal);
		return retVal;
	}

	@Override
	public void startStreaming(String ipAddress, boolean bEncrypt, int mode) {
		Log.d(TAG, "startStreaming called !!");
		if(StreamingState == StreamingStateDef.STATE_SELECTION_COMPLETED) {
			mStreamingRunnable = new RunStreaming(ACTION_RUNSTREAMING_START_STREAMING,
										ipAddress, bEncrypt, mode);
			mHandler.post(mStreamingRunnable);
		} else {
			Log.d(TAG, "startStreaming called in illegal state - "+StreamingState);
			throw new IllegalStateException();
		}
	}

	@Override
	public void stopStreaming() {
		Log.d(TAG, "stopStreaming ");
		mStreamingRunnable = new RunStreaming(ACTION_RUNSTREAMING_STOP_STREAMING);
		mHandler.post(mStreamingRunnable);
	}

	@Override
	public void finalizeStreaming() {
		Log.d(TAG, "finalizeStreaming ");
		mStreamingRunnable = new RunStreaming(ACTION_RUNSTREAMING_FINALIZE_STREAMING);
		mHandler.post(mStreamingRunnable);
	}

	@Override
	public void registerTvStreamingControlListener(
		ITvStreamingControlListener handler) {
		Log.d(TAG,"registerTvStreamingControlListener - "+handler);
		synchronized (mStreamingControlListener) {
			if(mStreamingControlListener.contains(handler)==false)
			{
				mStreamingControlListener.add(handler);
				Log.d(TAG,"clients now " + mStreamingControlListener.size());
			}
		}
	}

	@Override
	public void unRegisterTvStreamingControlListener(
		ITvStreamingControlListener handler) {
		Log.d(TAG,"unRegisterTvStreamingControlListener - "+handler);
		synchronized (mStreamingControlListener) {
			if(mStreamingControlListener.contains(handler)==false)
			{
				mStreamingControlListener.remove(handler);
				Log.d(TAG,"clients now " + mStreamingControlListener.size());
			}
		}
	}

	/****************************** ITvStreamingControl Methods Ends here ***********************/

	/****************************** ITvStreamingPlayControl Methods Starts here ***********************/

	@Override
	public TvMediaPlayerContext getTvMediaPlayerContext() {
		TvMediaPlayerContext context = null;
		if (cplaytvfacmediaplayer != null) {
			context = (TvMediaPlayerContext)cplaytvfacmediaplayer.
								getMediaPlayerInstance().getTvMediaPlayerContext();
		}
		Log.d(TAG, "getTvMediaPlayerContext: "+context);
		return context;
	}

	@Override
	public void prepareStreaming(int mode, Uri uri) {
		Log.d(TAG, "prepareStreaming - mode:"+mode+" uri:"+uri);
		//uriInfo info = getUriInfo(uri);
		factory = PlayTVMediaPlayerFactory.getInstance();
		mPrepareStreamingRunnable = new RunPrepareStreaming(mode, uri);
		mHandler.post(mPrepareStreamingRunnable);
	}

	@Override
	public int getTimeshiftStatus() {
		int status = 1;
		int retVal = 1;
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				status = playback.getCurrentTimeShiftStatus();
				switch (status) {
					case ITVTunerSession.TIMESHIFT_RECORDING_ACTIVE:
						retVal = ITvStreamingPlayControl.TIMESHIFT_ACTIVE;
						break;
					case ITVTunerSession.TIMESHIFT_RECORDING_NOTACTIVE_RECORDING_IN_PROGRESS:
						retVal = ITvStreamingPlayControl.TIMESHIFT_NOTACTIVE_RECORDING_IN_PROGRESS;
						break;
					case ITVTunerSession.TIMESHIFT_RECORDING_NOTACTIVE_HDD_NOT_CONNECTED:
						retVal = ITvStreamingPlayControl.TIMESHIFT_NOTACTIVE_HDD_NOT_CONNECTED;
						break;
					case ITVTunerSession.TIMESHIFT_RECORDING_NOTACTIVE_NO_DIGITAL_CHANNEL:
						retVal = ITvStreamingPlayControl.TIMESHIFT_NOTACTIVE_NO_DIGITAL_CHANNEL;
						break;
					case ITVTunerSession.TIMESHIFT_RECORDING_NOTACTIVE_XRATED_CONTENT:
						retVal = ITvStreamingPlayControl.TIMESHIFT_NOTACTIVE_X_RATED_CONTENT;
						break;
					case ITVTunerSession.TIMESHIFT_RECORDING_NOTACTIVE_IN_TRANSIENT:
						retVal = ITvStreamingPlayControl.TIMESHIFT_NOTACTIVE_IN_TRANSIENT;
						break;
					default:
						retVal = ITvStreamingPlayControl.TIMESHIFT_NOTACTIVE_GENERIC_ERROR;
						break;
				}
			} else {
				Log.d(TAG, "getTimeshiftStatus: playback is null");
			}
		} else {
			Log.d(TAG, "getTimeshiftStatus: cplaytvfacmediaplayer is null");
		}
		Log.d(TAG, "getTimeshiftStatus: status "+status+" retVal "+retVal);
		return retVal;
	}

	@Override
	public void pause() {
		Log.d(TAG, "pause: ");
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				playback.pause();
			} else {
				Log.d(TAG, "pause: playback is null");
			}
		} else {
			Log.d(TAG, "pause: cplaytvfacmediaplayer is null");
		}
	}

	@Override
	public void resume() {
		Log.d(TAG, "resume: ");
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				playback.resume();
			} else {
				Log.d(TAG, "resume: playback is null");
			}
		} else {
			Log.d(TAG, "resume: cplaytvfacmediaplayer is null");
		}
	}

	@Override
	public void seekTo(int timePos) {
		Log.d(TAG, "seekTo: "+timePos);
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				playback.seekTo(timePos);
			} else {
				Log.d(TAG, "seekTo: playback is null");
			}
		} else {
			Log.d(TAG, "seekTo: cplaytvfacmediaplayer is null");
		}
	}
 
	@Override
	public void stop() {
		Log.d(TAG, "stop: ");
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				playback.stop();
			} else {
				Log.d(TAG, "stop: playback is null");
			}
		} else {
			Log.d(TAG, "stop: cplaytvfacmediaplayer is null");
		}
	}

	@Override
	public int getCurrentDuration() {
		int duration = 0;
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				duration = playback.getCurrentDuration();
			} else {
				Log.d(TAG, "getCurrentDuration: playback is null");
			}
		} else {
			Log.d(TAG, "getCurrentDuration: cplaytvfacmediaplayer is null");
		}
		Log.d(TAG, "getCurrentDuration: duration "+duration);
		return duration;
	}

	@Override
	public int getTotalDuration() {
		int duration = 0;
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				duration = playback.getTotalDuration();
			} else {
				Log.d(TAG, "getTotalDuration: playback is null");
			}
		} else {
			Log.d(TAG, "getTotalDuration: cplaytvfacmediaplayer is null");
		}
		Log.d(TAG, "getTotalDuration: duration "+duration);
		return duration;
	}

	@Override
	public int getBufferedDuration() {
		int duration = 0;
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				duration = (int)playback.getRecordedDuration();
			} else {
				Log.d(TAG, "getBufferedDuration: playback is null");
			}
		} else {
			Log.d(TAG, "getBufferedDuration: cplaytvfacmediaplayer is null");
		}
		Log.d(TAG, "getBufferedDuration: duration "+duration);
		return duration;
	}

	@Override
	public void enableTrickModes(boolean enable) {
		Log.d(TAG, "enableTrickModes: "+enable);
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				playback.enableTrickModes(enable);
			} else {
				Log.d(TAG, "enableTrickModes: playback is null");
			}
		} else {
			Log.d(TAG, "enableTrickModes: cplaytvfacmediaplayer is null");
		}
	}

	@Override
	public int getPlaybackState() {
		int state = 0;
		if (cplaytvfacmediaplayer != null) {
			TvAbstractPlayback playback = null;
			playback = cplaytvfacmediaplayer.getPlaybackObject();
			if (playback != null) {
				int lstate = playback.getPlaybackState();
				if (playback instanceof PvrPlayback) {
					switch (lstate) {
						case ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING:
							state = ITvStreamingPlayControl.PLAYBACK_STATE_PLAYING;
						break;
						case ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED:
							state = ITvStreamingPlayControl.PLAYBACK_STATE_PAUSED;
						break;
						case ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY:
							state = ITvStreamingPlayControl.PLAYBACK_STATE_TRICKPLAY;
						break;
						case ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED:
							state = ITvStreamingPlayControl.PLAYBACK_STATE_STOPPED;
						break;
						default:
						break;
					}
				} else {
					switch(lstate) {
						case ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING:
							state = ITvStreamingPlayControl.PLAYBACK_STATE_TIMESHIFT;
						break;
						case ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED:
							state = ITvStreamingPlayControl.PLAYBACK_STATE_PAUSED;
						break;
						case ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY:
							state = ITvStreamingPlayControl.PLAYBACK_STATE_TRICKPLAY;
						break;
						case ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED:
							state = ITvStreamingPlayControl.PLAYBACK_STATE_PLAYING;
						break;
						default:
						break;
					}
				}
			} else {
				Log.d(TAG, "getPlaybackState: playback is null");
			}
		} else {
			Log.d(TAG, "getPlaybackState: cplaytvfacmediaplayer is null");
		}
		Log.d(TAG, "getPlaybackState: state "+state);
		return state;
	}

	@Override
	public void registerTvStreamingPlayControlListener(
		ITvStreamingPlayControlListener handler) {
		Log.d(TAG, "registerTvStreamingPlayControlListener - "+handler);
		synchronized (mStreamingPlayControlListener) {
			if(mStreamingPlayControlListener.contains(handler)==false)
			{
				mStreamingPlayControlListener.add(handler);
				Log.d(TAG,"clients now " + mStreamingPlayControlListener.size());
			}
		}
	}

	@Override
	public void unRegisterTvStreamingPlayControlListener(
		ITvStreamingPlayControlListener handler) {
		Log.d(TAG, "unRegisterTvStreamingPlayControlListener - "+handler);
		synchronized (mStreamingPlayControlListener) {
			if(mStreamingPlayControlListener.contains(handler)==false)
			{
				mStreamingPlayControlListener.remove(handler);
				Log.d(TAG,"clients now " + mStreamingPlayControlListener.size());
			}
		}
	}

	/****************************** ITvStreamingPLayControl Methods Starts here ***********************/


	/****************************** Private Methods Starts here ***********************/

	private uriInfo getUriInfo(Uri uri) {
		uriInfo info = new uriInfo();
		try {
			Map<String, String> headers	= TvURIHelper.getUriHeaders(this, uri);
			if(headers.get(TvHeaders.MEDIUM) != null) {
				info.medium = Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
			}
			if(headers.get(TvHeaders.PRESET_ID) != null) {
				info.channelId = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
			}
			if(headers.get(TvHeaders.RECORDING_ID) != null) {
				info.recId = Integer.parseInt(headers.get(TvHeaders.RECORDING_ID));
			}
		} catch (Exception e) {
			Log.d(TAG, "Exception in getUriInfo:"+e.toString());
		}
		Log.d(TAG, "getUriInfo uri:"+uri+" medium:"+info.medium+" channelId:"+info.channelId+" recId:"+info.recId);
		return info;
	}

	private void onPrepareStreamingFailed(int error) {
		Log.d(TAG, "onPrepareStreamingFailed "+error);
		synchronized (mStreamingPlayControlListener) {
			for(ITvStreamingPlayControlListener listener:mStreamingPlayControlListener) {
				listener.onPrepareStreamingFailed(error);
			}
		}
	}

	private void onMediaPlayerContextAvailable(TvMediaPlayerContext context) {
		Log.d(TAG, "onMediaPlayerContextAvailable "+context);
		synchronized (mStreamingPlayControlListener) {
			for(ITvStreamingPlayControlListener listener:mStreamingPlayControlListener) {
				listener.onMediaPlayerContextAvailable(context);
			}
		}
	}

	private void onStreamingStarted(boolean status) {
		Log.d(TAG, "onStreamingStarted "+status);
		mStreamingRunnable = new RunStreaming(ACTION_RUNSTREAMING_STREAMING_STARTED, status);
		mHandler.post(mStreamingRunnable);
	}

	private void onStreamingStopped() {
		Log.d(TAG, "onStreamingStopped ");
		mStreamingRunnable = new RunStreaming(ACTION_RUNSTREAMING_STREAMING_STOPPED);
		mHandler.post(mStreamingRunnable);
	}

	private void onStreamingClosed() {
		Log.d(TAG, "onStreamingClosed");
		mStreamingRunnable = new RunStreaming(ACTION_RUNSTREAMING_STREAMING_CLOSED);
		mHandler.post(mStreamingRunnable);
	}

	private void onStreamingModeChanged(int mode) {
		Log.d(TAG, "onStreamingModeChanged "+mode);
		mStreamingRunnable = new RunStreaming(ACTION_RUNSTREAMING_STREAMING_MODE_CHANGED, mode);
		mHandler.post(mStreamingRunnable);
	}

	private void onSeekComplete(boolean success) {
		Log.d(TAG, "onSeekComplete");
		synchronized (mStreamingPlayControlListener) {
			for(ITvStreamingPlayControlListener listener:mStreamingPlayControlListener) {
				listener.onSeekCompleted(success);
			}
		}
	}

	private void onPlayStateChanged(int state) {
		Log.d(TAG, "onPlayStateChanged");
		int lState = 0;
		switch(state) {
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING:
				lState = ITvStreamingPlayControl.PLAYBACK_STATE_PLAYING;
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED:
				lState = ITvStreamingPlayControl.PLAYBACK_STATE_PAUSED;
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY:
				lState = ITvStreamingPlayControl.PLAYBACK_STATE_TRICKPLAY;
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED:
				lState = ITvStreamingPlayControl.PLAYBACK_STATE_STOPPED;
			break;
			default:
			break;
		}
		synchronized (mStreamingPlayControlListener) {
			for(ITvStreamingPlayControlListener listener:mStreamingPlayControlListener) {
				listener.onPlayStateChanged(lState);
			}
		}
	}

	private void changeMPLMode(int fromPurpose, int toPurpose) {
		// release dependent mpl
		PlayTVFacMediaPlayer tmpMpl = null;
		TvAbstractPlayback playback = null;
		Medium medium = Medium.MEDIUM_INVALID;
		int chId = 0;
		if(cplaytvfacmediaplayer != null) {
			medium = cplaytvfacmediaplayer.getCurrentMedium();
			chId = cplaytvfacmediaplayer.getCurrentChannel();
		}
		// acquire independent mpl
		tmpMpl = factory.acquireMPLInstance(
							StreamingService.this, toPurpose,
							medium, chId);

		releaseMpl(cplaytvfacmediaplayer, fromPurpose);
		cplaytvfacmediaplayer = tmpMpl;
		if(tmpMpl != null) {
			mLastMPLRequestType = toPurpose;
			mPreviousPurpose = tmpMpl.getCurrentPurpose();
			playback = tmpMpl.getPlaybackObject();
			if(playback != null) {
				playback.registerListener(mPlaybackListener);
			} else {
				Log.d(TAG, "changeStreamingModeToIndependent: tmpMpl playback object is null");
			}
		} else {
			Log.d(TAG, "changeStreamingModeToIndependent: tmpMpl object is null");
		}
	}

	private void releaseMpl(PlayTVFacMediaPlayer mpl, int requestType) {
		mLastMPLRequestType = 0;
		if(mpl != null) {
			TvAbstractPlayback playback = mpl.getPlaybackObject();
			if(playback != null) {
				playback.unRegisterListener(mPlaybackListener);
			}
			factory.releaseMPLInstance(requestType,	mpl);
		}
	}

	private void acquireMpl (int requestType, Medium medium, int chId) {
		Log.d(TAG, "acquireMpl: requestType:"+requestType+" mLastMPLRequestType:"+mLastMPLRequestType+" medium:"+medium+" chId:"+chId);
		PlayTVFacMediaPlayer tmpMpl = null;
		if (cplaytvfacmediaplayer != null) {
			if(mLastMPLRequestType != requestType) {
				// acquire new mpl, since requestType changed
				tmpMpl = factory.acquireMPLInstance(
							StreamingService.this, requestType,
							medium, chId);

				// release old mpl
				releaseMpl(cplaytvfacmediaplayer, mLastMPLRequestType);
				cplaytvfacmediaplayer = tmpMpl;
			} else {
				// acquire again
				tmpMpl = factory.acquireMPLInstance(
							StreamingService.this, requestType,
							medium, chId);

				// check if old and new are same
				if (cplaytvfacmediaplayer != tmpMpl) {
					releaseMpl(cplaytvfacmediaplayer, requestType);
				}
				cplaytvfacmediaplayer = tmpMpl;
			}
		} else {
			//acquire since we don't have mpl
			tmpMpl = factory.acquireMPLInstance(
						StreamingService.this, requestType,
						medium, chId);
			cplaytvfacmediaplayer = tmpMpl;
		}
	}

	private void onTimeshiftPlayStateChanged(int state) {
		Log.d(TAG, "onTimeshiftPlayStateChanged");
		int lState = 0;
		switch(state) {
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING:
				lState = ITvStreamingPlayControl.PLAYBACK_STATE_TIMESHIFT;
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED:
				lState = ITvStreamingPlayControl.PLAYBACK_STATE_PAUSED;
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY:
				lState = ITvStreamingPlayControl.PLAYBACK_STATE_TRICKPLAY;
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED:
				lState = ITvStreamingPlayControl.PLAYBACK_STATE_PLAYING;
			break;
			default:
			break;
		}
		synchronized (mStreamingPlayControlListener) {
			for(ITvStreamingPlayControlListener listener:mStreamingPlayControlListener) {
				listener.onPlayStateChanged(lState);
			}
		}
	}

	private void releaseStreaming() {
		Log.d(TAG, "releaseStreaming ");
		mStreamingRunnable = new RunStreaming(ACTION_RUNSTREAMING_RELEASE_STREAMING);
		mHandler.post(mStreamingRunnable);
	}


	/****************************** Private Methods Ends here ***********************/

	/****************************** Runnables Starts here ***********************/

	class RunPrepareStreaming implements Runnable {
		Uri rUri;
		int rMode;

		public RunPrepareStreaming(int mode, Uri uri) {
			rUri = uri;
			rMode = mode;
		}

		@Override
		public void run() {
			uriInfo info = getUriInfo(rUri);
			TvAbstractPlayback playback = null;
			PlayTVFacMediaPlayer tmpMpl = null;
			//UriData uriData = TvURIHelper.parseUri(StreamingService.this,rUri);
			Map<String, String> headers = TvURIHelper.getUriHeaders(StreamingService.this, rUri);
			int requestType = 0;
			int chId = 0;
			Log.d(TAG, "Running prepareStreaming runnable - uri:"+rUri+" mode:"+rMode+" medium:"+info.medium+" channelId:"+info.channelId);

			switch (rMode) {
				case ITvStreamingControl.STREAMING_POSSIBLE_INDEPENDENT:
					Log.d(TAG, "STREAMING_POSSIBLE_INDEPENDENT");
					mLastSelectedStreamingMode = ITvStreamingControl.STREAMING_POSSIBLE_INDEPENDENT;
					requestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD;
					chId = (info.medium == Medium.MEDIUM_PVRFILE) ? info.recId : info.channelId;

					// Check if there is a usecase change and release streaming
					if (mCurrentMedium != info.medium) {
						releaseStreaming();
						mCurrentMedium = info.medium;
						break;
					}
					// Acquire mpl for selection
					acquireMpl(requestType, info.medium, chId);

					if(cplaytvfacmediaplayer != null) {
						mLastMPLRequestType = requestType;
						mPreviousPurpose = cplaytvfacmediaplayer.getCurrentPurpose();
						playback = cplaytvfacmediaplayer.getPlaybackObject();
						if(playback != null) {
							playback.registerListener(mPlaybackListener);
							playback.play(rUri, info.medium, headers);
							StreamingState = StreamingStateDef.STATE_SELECTION_STARTED;
						} else {
							StreamingState = StreamingStateDef.STATE_IDLE;
							onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_GENERIC_ERROR);
						}
					} else {
						StreamingState = StreamingStateDef.STATE_IDLE;
						onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_MODE_NOT_AVAILABLE);
					}
				break;
				case ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_RECORDING:
					Log.d(TAG, "STREAMING_POSSIBLE_DEPENDENT_RECORDING");
					mLastSelectedStreamingMode = ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_RECORDING;
					requestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD;
					chId = (info.medium == Medium.MEDIUM_PVRFILE) ? info.recId : info.channelId;

					// Acquire mpl for selection
					acquireMpl(requestType, info.medium, chId);

					if(cplaytvfacmediaplayer != null) {
						mCurrentMedium = info.medium;
						mLastMPLRequestType = requestType;
						mPreviousPurpose = cplaytvfacmediaplayer.getCurrentPurpose();
						playback = cplaytvfacmediaplayer.getPlaybackObject();
						if(playback != null) {
							playback.registerListener(mPlaybackListener);
							StreamingState = StreamingStateDef.STATE_SELECTION_COMPLETED;
							onMediaPlayerContextAvailable((TvMediaPlayerContext)cplaytvfacmediaplayer.
												getMediaPlayerInstance().getTvMediaPlayerContext());
						} else {
							StreamingState = StreamingStateDef.STATE_IDLE;
							onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_GENERIC_ERROR);
						}
					} else {
						StreamingState = StreamingStateDef.STATE_IDLE;
						onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_MODE_NOT_AVAILABLE);
					}
				break;
				case ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH:
					Log.d(TAG, "STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH");
					mLastSelectedStreamingMode = ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH;
					chId = (info.medium == Medium.MEDIUM_PVRFILE) ? info.recId : info.channelId;
					int reason = factory.IsMediaPlayerAvailable(StreamingService.this,
											PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD,
											info.medium, chId);
					if ((reason & PlayTVMediaPlayerFactory.STATUS_AVAILABLE) != 0) {
						Log.d(TAG, "STATUS_AVAILABLE for request");

						// Acquire mpl for selection
						acquireMpl(PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD, info.medium, chId);

						if(cplaytvfacmediaplayer != null) {
							mCurrentMedium = info.medium;
							mLastMPLRequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD;
							mPreviousPurpose = cplaytvfacmediaplayer.getCurrentPurpose();
							playback = cplaytvfacmediaplayer.getPlaybackObject();
							if(playback != null) {
								playback.registerListener(mPlaybackListener);
								StreamingState = StreamingStateDef.STATE_SELECTION_COMPLETED;
								onMediaPlayerContextAvailable((TvMediaPlayerContext)cplaytvfacmediaplayer.
													getMediaPlayerInstance().getTvMediaPlayerContext());
							} else {
								StreamingState = StreamingStateDef.STATE_IDLE;
								onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_GENERIC_ERROR);
							}
						} else {
							StreamingState = StreamingStateDef.STATE_IDLE;
							onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_MODE_NOT_AVAILABLE);
						}
					} else {
						Log.d(TAG, "STATUS_NOT_AVAILABLE since current channel is different, check for requested channel");
						reason = factory.IsMediaPlayerAvailable(StreamingService.this,
											PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH,
											info.medium, chId);
						if ((reason & PlayTVMediaPlayerFactory.STATUS_AVAILABLE) != 0) {
							Log.d(TAG, "STATUS_AVAILABLE for requested channel, perform selection");
							// Send intent to start activity
							Intent selectionIntent = null;
							switch(info.medium) {
								case MEDIUM_SATELLITE:
								case MEDIUM_CABLE:
								case MEDIUM_TERRESTRIAL:
									selectionIntent = new Intent("org.droidtv.playtv.SELECTURI");
									selectionIntent.putExtra("uri", rUri.toString());
								break;
								case MEDIUM_PVRFILE:
									selectionIntent = new Intent("org.droidtv.action.PLAYRECORDING");
									selectionIntent.putExtra("RecordingId", info.recId);
								break;
								default:
									onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_MODE_NOT_AVAILABLE);
								return;
							}

							Log.d(TAG, "Start Activity, for selection");
							selectionIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
							startActivity(selectionIntent);
							StreamingState = StreamingStateDef.STATE_SELECTION_STARTED;
							mCurrentMedium = info.medium;
						} else {
							onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_MODE_NOT_AVAILABLE);
						}
					}
				break;
				default:
					Log.e(TAG, "PrepareStreaming called with Invalid mode: "+rMode);
					onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_GENERIC_ERROR);
				return;
			}
		}
	}

	class RunStreaming implements Runnable {
		int rAction;
		String rIpAddress;
		boolean rBEncrypt;
		boolean rStatus;
		int rMode;

		public RunStreaming(int action, String ipAddress, boolean bEncrypt, int mode) {
			rAction = action;
			rIpAddress = ipAddress;
			rBEncrypt = bEncrypt;
			rMode = mode;
		}

		public RunStreaming(int action) {
			rAction = action;
		}

		public RunStreaming(int action, boolean status) {
			rAction = action;
			rStatus = status;
		}

		public RunStreaming(int action, int mode) {
			rAction = action;
			rMode = mode;
		}

		@Override
		public void run() {
			Log.d(TAG, "Running Streaming runnable - ipAddr:"+rIpAddress+" encrypt:"+rBEncrypt+" action:"+rAction);
			switch (rAction) {
				case ACTION_RUNSTREAMING_START_STREAMING:
					if (StreamingState == StreamingStateDef.STATE_SELECTION_COMPLETED) {
						int mode = BcstConstants.DIGITAL_BROADCAST;
						StreamingState = StreamingStateDef.STATE_TRIGGERED;
						if (cplaytvfacmediaplayer != null) {
							try {
								// get medium and change mode if it is TS/PVR
								Medium medium = cplaytvfacmediaplayer.getCurrentMedium();
								if ((medium == Medium.MEDIUM_PVRFILE)||(medium == Medium.MEDIUM_TSFILE)) {
									mode = BcstConstants.PVR_PLAYBACK;
								}
								// Send start streaming call to TvServer
								cplaytvfacmediaplayer.getMediaPlayerInstance().
										getTvMediaPlayerContext().getTvMediaRecordControl().
										registerListenerCallback(mTADStatusListener);
								cplaytvfacmediaplayer.getMediaPlayerInstance().
										getTvMediaPlayerContext().getTvMediaRecordControl().
										startTAD(mode, rIpAddress, rBEncrypt);
							} catch (Exception e) {
								Log.d(TAG, "StartStreaming: Exception in runnable : "+e.toString());
								onStreamingStarted(false);
							}
						} else {
							// sending streaming start failed
							Log.d(TAG, "StartStreaming: cplaytvfacmediaplayer is null");
							onStreamingStarted(false);
						}
					} else {
						// sending streaming start failed
						Log.d(TAG, "StartStreaming: Invalid StreamingState Invalid StreamingState "+StreamingState);
						onStreamingStarted(false);
					}
				break;
				case ACTION_RUNSTREAMING_STREAMING_STARTED:
					if (StreamingState == StreamingStateDef.STATE_TRIGGERED) {
						if (rStatus) {
							StreamingState = StreamingStateDef.STATE_STREAMING;
						} else {
							StreamingState = StreamingStateDef.STATE_SELECTION_COMPLETED;
						}
						synchronized (mStreamingControlListener) {
							for(ITvStreamingControlListener listener:mStreamingControlListener) {
								listener.onStreamingStarted(rStatus);
							}
						}
					} else {
						Log.d(TAG, "onStreamingStarted: Invalid StreamingState "+StreamingState);
					}
				break;
				case ACTION_RUNSTREAMING_STOP_STREAMING:
					if((StreamingState == StreamingStateDef.STATE_TRIGGERED) || (StreamingState == StreamingStateDef.STATE_STREAMING)) {
						StreamingState = StreamingStateDef.STATE_STOPPING;
						if(cplaytvfacmediaplayer != null) {
							try {
								cplaytvfacmediaplayer.getMediaPlayerInstance().
										getTvMediaPlayerContext().getTvMediaRecordControl().
										stopTAD();
							} catch(Exception e) {
								Log.e(TAG, "StopStreaming: Exception : "+e.toString());
							}
						} else {
							Log.e(TAG, "StopStreaming: cplaytvfacmediaplayer is null");
						}
					} else {
						Log.d(TAG, "StopStreaming: Invalid StreamingState "+StreamingState);
					}
				break;
				case ACTION_RUNSTREAMING_STREAMING_STOPPED:
					if (StreamingState != StreamingStateDef.STATE_IDLE) {
						StreamingState = StreamingStateDef.STATE_SELECTION_COMPLETED;
						synchronized (mStreamingControlListener) {
							for(ITvStreamingControlListener listener:mStreamingControlListener) {
								listener.onStreamingStopped();
							}
						}
					} else {
						Log.d(TAG, "onStreamingStopped: Invalid StreamingState "+StreamingState);
					}
				break;
				case ACTION_RUNSTREAMING_FINALIZE_STREAMING:
					StreamingState = StreamingStateDef.STATE_RELEASING;
					if (cplaytvfacmediaplayer != null) {

						// release mpl
						int purpose = cplaytvfacmediaplayer.getCurrentPurpose();
						if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) != 0) {
							releaseMpl(cplaytvfacmediaplayer, PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
						} else if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) != 0) {
							releaseMpl(cplaytvfacmediaplayer, PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
						}
						cplaytvfacmediaplayer = null;
					}
					onStreamingClosed();
				break;
				case ACTION_RUNSTREAMING_STREAMING_CLOSED:
					if (StreamingState != StreamingStateDef.STATE_IDLE) {
						StreamingState = StreamingStateDef.STATE_IDLE;
						synchronized (mStreamingControlListener) {
							for(ITvStreamingControlListener listener:mStreamingControlListener) {
								listener.onStreamingClosed();
							}
						}
					} else {
						Log.d(TAG, "Not sending onStreamingClosed, since state is idle");
					}
				break;
				case ACTION_RUNSTREAMING_STREAMING_MODE_CHANGED:
					if (StreamingState != StreamingStateDef.STATE_IDLE) {
						mLastSelectedStreamingMode = rMode;
						synchronized (mStreamingControlListener) {
							for(ITvStreamingControlListener listener:mStreamingControlListener) {
								listener.onStreamingModeChanged(rMode);
							}
						}
					} else {
						Log.d(TAG, "Not sending onStreamingModeCHanged, since state is idle");
					}
				break;
				case ACTION_RUNSTREAMING_RELEASE_STREAMING:
					StreamingState = StreamingStateDef.STATE_RELEASING;
					if (cplaytvfacmediaplayer != null) {
						try {
							cplaytvfacmediaplayer.getMediaPlayerInstance().
									getTvMediaPlayerContext().getTvMediaRecordControl().
									releaseTAD();
						} catch(Exception e) {
							Log.e(TAG, "releaseTAD: Exception : "+e.toString());
						}

						// release mpl
						int purpose = cplaytvfacmediaplayer.getCurrentPurpose();
						if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) != 0) {
							releaseMpl(cplaytvfacmediaplayer, PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
						} else if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) != 0) {
							releaseMpl(cplaytvfacmediaplayer, PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
						}
						cplaytvfacmediaplayer = null;
					}
				break;

				default:
				break;
			}
		}
	}

	class RunStreamingNotification implements Runnable {

		int rAction;
		public RunStreamingNotification(int action) {
			rAction = action;
		}

		@Override
		public void run() {
			Log.d(TAG, "Running streamingNotification runnable - action:"+rAction);
			switch(rAction) {
				case BcstConstants.TAD_PLAY_STARTED:
					onStreamingStarted(true);
				break;
				case BcstConstants.TAD_PLAY_STOPPED:
					onStreamingStopped();
				break;
				case BcstConstants.TAD_PLAY_ERROR:
					int purpose = -1;
					if (cplaytvfacmediaplayer != null) {
						purpose = cplaytvfacmediaplayer.getCurrentPurpose();
						if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) != 0) {
							releaseMpl(cplaytvfacmediaplayer, PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
						} else if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) != 0) {
							releaseMpl(cplaytvfacmediaplayer, PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
						}
						cplaytvfacmediaplayer = null;
					}
					Log.d(TAG, "TAD_PLAY_ERROR: Releasing mpl for "+purpose);
					onStreamingClosed();
				break;
				case BcstConstants.TAD_PLAY_RELEASED:
					Log.d(TAG, "TAD_PLAY_RELEASED");
					onStreamingClosed();
				break;
				default:
				break;
			}
		}
	}

	class RunTvAbstractPlaybackListener implements Runnable {

		int rAction;
		Uri rUri;
		int rWhat;
		int rExtra;
		int rDataInt;
		boolean rStatus;
		public RunTvAbstractPlaybackListener(int action, Uri uri) {
			rAction = action;
			rUri = uri;
		}

		public RunTvAbstractPlaybackListener(int action, int what, int extra) {
			rAction = action;
			rWhat = what;
			rExtra = extra;
		}

		public RunTvAbstractPlaybackListener(int action, int dataInt) {
			rAction = action;
			rDataInt = dataInt;
		}

		public RunTvAbstractPlaybackListener(int action, boolean status) {
			rAction = action;
			rStatus = status;
		}

		@Override
		public void run() {
			Log.d(TAG, "Runnings TvAbstractPlaybackListener runnable action:"+rAction);
			switch(rAction) {
				case ACTION_RUNTVABSPLAYLISTENER_PLAYSTARTED:
				break;
				case ACTION_RUNTVABSPLAYLISTENER_PLAYCOMPLETED:
					if ((cplaytvfacmediaplayer != null) &&
							(mLastSelectedStreamingMode != ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH)) {
						StreamingState = StreamingStateDef.STATE_SELECTION_COMPLETED;
						onMediaPlayerContextAvailable((TvMediaPlayerContext)cplaytvfacmediaplayer.
											getMediaPlayerInstance().getTvMediaPlayerContext());
					} else {
						Log.d(TAG, "cplaytvfacmediaplayer is null in ONPLAYCOMPLETED");
					}
				break;
				case ACTION_RUNTVABSPLAYLISTENER_PLAYFAILED:
				break;
				case ACTION_RUNTVABSPLAYLISTENER_PLAYFINISHED:
				break;
				case ACTION_RUNTVABSPLAYLISTENER_SEEKCOMPLETE:
					onSeekComplete(true);
				break;
				case ACTION_RUNTVABSPLAYLISTENER_PLAYERROR:
					// when mpl is lost due to higher priority purpose
					// onError is issued with 'what' & 'extra' as -1
					if ((rWhat == -1) && (rExtra == -1)) {
						if (cplaytvfacmediaplayer != null) {
							int purpose = cplaytvfacmediaplayer.getCurrentPurpose();
							if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) != 0) {
								factory.releaseMPLInstance(
										PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD,
										cplaytvfacmediaplayer);
							} else if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) != 0) {
								factory.releaseMPLInstance(
										PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD,
										cplaytvfacmediaplayer);
							}
							cplaytvfacmediaplayer = null;
						}
					}
					onStreamingClosed();
				break;
				case ACTION_RUNTVABSPLAYLISTENER_TRICKMODECHANGE:
				break;
				case ACTION_RUNTVABSPLAYLISTENER_PLAYSTATECHANGE:
					onPlayStateChanged(rDataInt);
				break;
				case ACTION_RUNTVABSPLAYLISTENER_TIMESHIFTPLAYSTATECHANGE:
					onTimeshiftPlayStateChanged(rDataInt);
				break;
				case ACTION_RUNTVABSPLAYLISTENER_ONMPLPURPOSECHANGED:
				break;
				default:
				break;
			}
		}
	}

	class RunTunerSessionCallbacks implements Runnable {

		int rAction;
		Uri rUri;

		public RunTunerSessionCallbacks(int action, Uri uri) {
			rAction = action;
			rUri = uri;
		}

		@Override
		public void run() {
			Log.d(TAG, "Running TunerSessionCallbacks runnable - action:"+rAction);
			switch (rAction) {
				case ACTION_RUNTUNERSESSIONCALLBACKS_ONCHANNELRETUNED:
					if (StreamingState == StreamingStateDef.STATE_SELECTION_STARTED) {
						uriInfo info = getUriInfo(rUri);
						//UriData uriData = TvURIHelper.parseUri(StreamingService.this, rUri);
						TvAbstractPlayback playback = null;
						PlayTVFacMediaPlayer tmpMpl = null;
						int chId = (info.medium == Medium.MEDIUM_PVRFILE) ? info.recId : info.channelId;

						// Acquire mpl for selection
						acquireMpl(PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD, info.medium, chId);

						if(cplaytvfacmediaplayer != null) {
							mLastMPLRequestType = PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD;
							mPreviousPurpose = cplaytvfacmediaplayer.getCurrentPurpose();
							playback = cplaytvfacmediaplayer.getPlaybackObject();
							if(playback != null) {
								playback.registerListener(mPlaybackListener);
								StreamingState = StreamingStateDef.STATE_SELECTION_COMPLETED;
								onMediaPlayerContextAvailable((TvMediaPlayerContext)cplaytvfacmediaplayer.
												getMediaPlayerInstance().getTvMediaPlayerContext());
							} else {
								Log.d(TAG, "ONCHANNELRETUNED: Playback is null for mpl");
							}
						} else {
							StreamingState = StreamingStateDef.STATE_IDLE;
							onPrepareStreamingFailed(ITvStreamingPlayControlListener.PREPARE_FAILED_MODE_NOT_AVAILABLE);
						}
					} else {
						Log.d(TAG, "ONCHANNELRETUNED, but state is "+StreamingState);
					}
				break;
				default:
				break;
			}
		}
	}

	/****************************** Runnables Ends here ***********************/

	/****************************** Sub classes Starts here ***********************/

	public class TADStatusListenerClass extends IonTvRecordControlCallback {
		@Override
		public void onTadStatus(int status)  {
			Log.d(TAG,"onTadStatus : Status " + status);
			mStreamingNRunnable = new RunStreamingNotification(status);
			mHandler.post(mStreamingNRunnable);
		}
	}

	private class uriInfo {
		Medium medium;
		int channelId;
		int recId;
	}

	public class PlayTvMPLFactoryListener implements IPlayTvMPLFactoryCallback {

		@Override
		public boolean onAvailable(int clientType) {
			Log.d(TAG, "onAvailable "+clientType);
			return false;
		}

		@Override
		public boolean onNotAvailable(int clientType) {
			Log.d(TAG, "onNotAvailable "+clientType);
			return false;
		}

		@Override
		public void onOlympicUsecaseUpdate(boolean enable,boolean isOTR) {
			Log.d(TAG, "onOlympicUsecaseUpdate enable:"+enable+" isOTR:"+isOTR);

		}
	}

	public class TvAbstractPlaybackListener implements ITvAbstractPlaybackListener {

		@Override
		public void onPlayStarted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber) {
			Log.d(TAG, "onPlayStarted uri:"+uri);
			mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_PLAYSTARTED, uri);
			mHandler.post(mTVAbsPlayListenerRunnable);
		}

		@Override
		public void onPlayCompleted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber) {
			Log.d(TAG, "onPlayCompleted uri:"+uri);
			mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_PLAYCOMPLETED, uri);
			mHandler.post(mTVAbsPlayListenerRunnable);
		}

		@Override
		public void onPlayFailed(Uri uri, Medium medium, int presetNumber, int reason) {
			Log.d(TAG, "onPlayFailed uri:"+uri);
			mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_PLAYFAILED, uri);
			mHandler.post(mTVAbsPlayListenerRunnable);
		}

		@Override
		public void onPlayFinished(Uri uri, Medium medium, int presetNumber) {
			Log.d(TAG, "onPlayFinished uri:"+uri);
			mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_PLAYFINISHED, uri);
			mHandler.post(mTVAbsPlayListenerRunnable);
		}

		@Override
		public void onLicenseExchangeHappening(boolean status) {
		}

		@Override
		public void onSeekComplete(int mode) {
			Log.d(TAG, "onSeekComplete ");
			mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_SEEKCOMPLETE, null);
			mHandler.post(mTVAbsPlayListenerRunnable);
		}

		@Override
		public void onPlayError(int error, int what, int extra, int mode) {
			mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_PLAYERROR, what, extra);
			mHandler.post(mTVAbsPlayListenerRunnable);
		}

		@Override
		public void onServiceTypeDetected(int type) {
		}

		@Override
		public void onTrickModeEnabled(boolean status, int mode) {
			mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_TRICKMODECHANGE, status);
			mHandler.post(mTVAbsPlayListenerRunnable);
		}

		@Override
		public void onPlayStateChanged(int state, int mode) {
			Log.d(TAG, "onPlayStateChanged state:"+state+" mode:"+mode);
			if(mode == ITvAbstractPlaybackListener.MODE_PVR) {
				mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_PLAYSTATECHANGE, state);
				mHandler.post(mTVAbsPlayListenerRunnable);
			} else {
				mTVAbsPlayListenerRunnable = new RunTvAbstractPlaybackListener(ACTION_RUNTVABSPLAYLISTENER_TIMESHIFTPLAYSTATECHANGE, state);
				mHandler.post(mTVAbsPlayListenerRunnable);
			}
		}

		@Override
		public void onLockStatusChanged(int type, int status) {
		}

		@Override
		public void onInfo(boolean cicamAvailable) {
		}

		@Override
		public void onMPLPurposeChanged(int purpose) {
			Log.d(TAG, "ONMPLPURPOSECHANGED state:"+StreamingState+" mode:"+mLastSelectedStreamingMode+" Cur_purpose:"+purpose+" Prv_purpose:"+mPreviousPurpose);
			if (StreamingState != StreamingStateDef.STATE_IDLE) {
				switch (mLastSelectedStreamingMode) {
					case ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH:
						// Check if old purpose has main_watch
						if ((mPreviousPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) > 0) {
							mPreviousPurpose = purpose;
							if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) > 0) {
								// Nothing to be done
							} else {
								Log.d(TAG, "Purpose changed MAIN_WATCH removed !!!");
								ITvPowerManager lTvPowerManager = ITvPowerManager.Instance.getInterface();
								if(lTvPowerManager.GetPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY) {
									if (((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) != 0) ||
										((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) != 0)) {
										Log.d(TAG, "Current Power state is SSBY: Change mode to Dependent-Recording");
										onStreamingModeChanged(ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_RECORDING);
									} else {
										Log.d(TAG, "Current Power state is SSBY: Change mode to Independent");
										changeMPLMode(PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD, PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
										onStreamingModeChanged(ITvStreamingControl.STREAMING_POSSIBLE_INDEPENDENT);
									}
								} else {
									Log.d(TAG, "Current Power state is FULL_ON: Release streaming resources if happening");
									releaseStreaming();
								}
							}
						}
					break;
					case ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_RECORDING:
						if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) > 0) {
							if ((mPreviousPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) > 0) {
								// Nothing to be done
								mPreviousPurpose = purpose;
							} else {
								mPreviousPurpose = purpose;
								Log.d(TAG, "MAIN_WATCH added in dependent_recording case");
								if (((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) > 0) ||
									((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) > 0)) {
									// Do nothing
								} else {
									// recording has finished during ssby, so change mode on waking up
									//onStreamingModeChanged(ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH);
									releaseStreaming();
								}
							}
						} else {
							if ((mPreviousPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) > 0) {
								mPreviousPurpose = purpose;
								Log.d(TAG, "MAIN_WATCH removed in dependent_recording case");
								// Check if recording is still present in notified purpose
								if (((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) > 0) ||
									((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) > 0)) {
									// Do nothing
								} else {
									// Recording has finished. Change mode as applicable
									// Check power state and switch to independent if in ssby OR StopStreaming in Full-On
									ITvPowerManager lTvPowerManager = ITvPowerManager.Instance.getInterface();
									if(lTvPowerManager.GetPowerState() == PowerStates.POWER_STATE_SEMI_STANDBY) {
										Log.d(TAG, "Current Power state is SSBY: Change mode to independent");
										changeMPLMode(PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD, PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
										onStreamingModeChanged(ITvStreamingControl.STREAMING_POSSIBLE_INDEPENDENT);
									} else {
										Log.d(TAG, "Current Power state is FULL_ON: Stop streaming if happening");
										releaseStreaming();
									}
								}
							}
						}
					break;
					case ITvStreamingControl.STREAMING_POSSIBLE_INDEPENDENT:
						if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) > 0) {
							if ((mPreviousPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) > 0) {
								// Do nothing
								mPreviousPurpose = purpose;
							} else {
								Log.d(TAG, "Purpose changed MAIN_WATCH added !!!");
								mPreviousPurpose = purpose;
								// TODO: Check if independent is possible, in case of mtk and then decide to continue
								// 		  in independent OR switch to dependent TAD
								changeMPLMode(PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD, PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
								onStreamingModeChanged(ITvStreamingControl.STREAMING_POSSIBLE_DEPENDENT_MAIN_WATCH);
							}
						}
					break;
					default:
						mPreviousPurpose = purpose;
					break;
				}
			}
		}

		@Override
		public void onTimeshiftInfoChanged() {

		}
	}

	/****************************** Sub classes Ends here ***********************/

	/****************************** Service methods Starts here ***********************/

	@Override
	public void onCreate() {
		Log.d(TAG, "onCreate");
		super.onCreate();

		mStreamingThread = new Thread(new Runnable() {
			public void run() {
				Looper.prepare();
				mHandler = new Handler();
				Looper.loop();
			}
		});
		mStreamingThread.start();
		mStreamingControlListener = new ArrayList<ITvStreamingControlListener>();
		mStreamingPlayControlListener = new ArrayList<ITvStreamingPlayControlListener>();
		mTADStatusListener = new TADStatusListenerClass();
//		factory = PlayTVMediaPlayerFactory.getInstance();
//		mPlayTvStateChangeListener = new PlaytvStateChangeCallbacks();
		mPlaybackListener = new TvAbstractPlaybackListener();
		mPlayTvMPLFactoryListener = new PlayTvMPLFactoryListener();
		mSessionHandler = new Handler();
		mTvInputCallback = new TvInputCallbackClass();
		mSessionCallback = new TunerSessionCallback();
		mTvInputManager = (TvInputManager)getSystemService(Context.TV_INPUT_SERVICE);

		if (mTvInputManager != null) {
			String TunerServiceID = null;
			mTvInputManager.registerCallback( mTvInputCallback, mSessionHandler);
			List inputlist = mTvInputManager.getTvInputList();
			for(int i=0;i<inputlist.size();i++){
				TvInputInfo tinfo = (TvInputInfo) inputlist.get(i);
				if((tinfo.getType() == TvInputInfo.TYPE_TUNER) && 
					(tinfo.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))){
					TunerServiceID = tinfo.getId();
					break;
				}
			}
			if((TunerServiceID != null) && (mTvInputManager.getInputState(TunerServiceID) == TvInputManager.INPUT_STATE_CONNECTED)) {
				Log.d(TAG,"Creating session");
				mTvInputManager.createSession(TunerServiceID, mSessionCallback, mSessionHandler);
			}else {
				Log.d(TAG,"TunerService input not added yet");
			}
		} else {
			Log.d(TAG, "TvInputManager is null");
		}
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		super.onStartCommand(intent, flags, startId);
		return Service.START_STICKY;
	}

	@Override
	public void onDestroy() {
		Log.d(TAG, "onDestroy");
		closeSession();
		if (mHandler != null) {
			mHandler.removeCallbacks(mPrepareStreamingRunnable);
			mHandler.removeCallbacks(mStreamingRunnable);
			mHandler.removeCallbacks(mStreamingNRunnable);
			mHandler.removeCallbacks(mTVAbsPlayListenerRunnable);
			mHandler.getLooper().quit();
		}
		mStreamingThread = null;
		super.onDestroy();
	}

	@Override
	public IBinder onBind(Intent intent) {
		Log.d(TAG, "ConnectionRequest received - intent:"+intent.getAction());
		IBinder binder = null;
		if (intent.getAction().equalsIgnoreCase("org.droidtv.tunerservice.services.streamingservice.TVSTREAMINGCONTROL")) {
			binder = ITvStreamingControl.Instance.asBinder((ITvStreamingControl) this);
		} else if (intent.getAction().equalsIgnoreCase("org.droidtv.tunerservice.services.streamingservice.TVSTREAMINGPLAYCONTROL")) {
			binder = ITvStreamingPlayControl.Instance.asBinder((ITvStreamingPlayControl) this);
		}
		return binder;
	}

	@Override
	public boolean onUnbind(Intent intent) {
		Log.d(TAG, "onUnbind");
		try {
			if(cplaytvfacmediaplayer != null) {
				int purpose = cplaytvfacmediaplayer.getCurrentPurpose();
				// First stop streaming
				cplaytvfacmediaplayer.getMediaPlayerInstance().
						getTvMediaPlayerContext().getTvMediaRecordControl().
						stopTAD();
				// Unregister listeners
				cplaytvfacmediaplayer.getMediaPlayerInstance().
						getTvMediaPlayerContext().getTvMediaRecordControl().
						unregisterListenerCallback(mTADStatusListener);
				StreamingState = StreamingStateDef.STATE_IDLE;
				// now release the mpl
				if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) != 0) {
					releaseMpl(cplaytvfacmediaplayer, PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
				} else if ((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) != 0) {
					releaseMpl(cplaytvfacmediaplayer, PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
				}
				cplaytvfacmediaplayer = null;
			}

			if (mTvInputManager != null) {
				mTvInputManager.unregisterCallback(mTvInputCallback);
			}
		} catch(Exception e) {
			Log.e(TAG, "Exception in onUnbind: "+e.toString());
		}
		return super.onUnbind(intent);
	}

	/****************************** Service methods Ends here ***********************/

	/****************************** Session starts here *****************************/

	public class TvInputCallbackClass extends TvInputCallback {

		public void onInputStateChanged(String inputId, int state) {
		}

		public void onInputAdded(String inputId) {
			if(inputId.equals("org.droidtv.tunerservice/.TunerService")) {
				Log.d(TAG,"creating the session,waiting for call back");
				mTvInputManager.createSession("org.droidtv.tunerservice/.TunerService", mSessionCallback, mSessionHandler);
			}
		}

		public void onInputRemoved(String inputId) {
		}
	}

	class TunerSessionObserver extends ITunerSessionCallbacks {
		@Override
		public void onTuneFailed(String inputid, Uri channelUri, int reason) {
		}

		@Override
		public void OnDualStatusChanged(int channel, int controllable) {
		}
	}

	public class TunerSessionCallback extends SessionCallback {

		ITVSessionContext mSessionContext = null;

        public void onSessionCreated(Session session) {
			Log.d(TAG,"onSessionCreated ");
			mSession = session;
			String action = ITVSessionContext.APP_PRIVATE_COMMAND_SESSION_TYPE;
			Bundle bundle = new Bundle();
			bundle.putString(ITVSessionContext.KEY_SESSION_TYPE, ITVSessionContext.SESSION_TYPE_MAIN_OBSERVER);
			mSession.sendAppPrivateCommand(action, bundle);
        }

        public void onSessionReleased(Session session) {
			Log.i(TAG,"onSessionReleased");
        }

        public void onChannelRetuned(Session session, Uri channelUri) {
			Log.d(TAG,"onChannelRetuned uri:"+channelUri);
			if(channelUri != null) {
				mTunerSessionCallbacksRunnable = new RunTunerSessionCallbacks(ACTION_RUNTUNERSESSIONCALLBACKS_ONCHANNELRETUNED, channelUri);
				mHandler.post(mTunerSessionCallbacksRunnable);
			}
		}

        public void onTrackInfoChanged(Session session, List<TvTrackInfo> tracks) {
        }

        public void onVideoAvailable(Session session) {
        }

        public void onVideoUnavailable(Session session, int reason) {
        }


        public void onContentAllowed(Session session) {
        }

        public void onContentBlocked(Session session, TvContentRating rating) {
        }


        public void onSessionEvent(Session session, String eventType, Bundle eventArgs) {
			Log.i(TAG,"onSessionEvent " + this);
			if(eventType.equals(ITVSessionContext.EVENT_SESSION_CONTEXT_CREATED)){
				IBinder binder = eventArgs.getBinder(ITVSessionContext.SESSION_CONTEXT);
				mSessionContext = ITVSessionContext.instance.asInterface(binder);
				mTunerSession	= mSessionContext.getITvTunerSession();

				tunerSessionCallbacks = new TunerSessionObserver();
				mTunerSession.registerTunerSessionCallbacks(tunerSessionCallbacks);

				class SessionContextObserver extends ISessionContextCallbacks {
					@Override
					public void onReAcquireInterfaces() {
					}
				}
				SessionContextObserver sessionContextCallbacks = new SessionContextObserver();
				mSessionContext.registerSessionContextCallbacks(sessionContextCallbacks);
			}
        }
	}
	
	public void closeSession() {
		Log.d(TAG, "closeSession");
		if (mTunerSession != null) {
			mTunerSession.unregisterTunerSessionCallbacks(tunerSessionCallbacks);
		}
		if (mSession != null) {
			try{
				mSession.release();
			}catch(Exception ex){
				Log.d(TAG,"Caught Exception: " + ex.getMessage());
			}
		}
	}

	/****************************** Session ends here *****************************/


/**************** TO BE REMOVED: ADDED FOR BUILD TO GO THROUGH **************************************/

	public boolean isStreaming() {
		return false;
	}
	public void pauseLocal() {

	}
	public void resumeLocal() {

	}
	public void setSpeedLocal() {

	}
	public void stopLocal() {

	}
	public void audioFocusChanged(int audioFocus) {

	}
	public void enableBroadcastAV(boolean ena) {

	}
	public void onUriChanged(Uri uri) {

	}
	public void onPlayStateChangedNotify() {

	}

	public void onStateChanged(Uri uri, int state) {

	}

}
