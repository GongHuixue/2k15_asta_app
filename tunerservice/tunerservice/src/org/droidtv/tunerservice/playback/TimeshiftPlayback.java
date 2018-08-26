package org.droidtv.tunerservice.playback;
 
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.interfaces.ITSRecording;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.media.ITvMediaRecordControl;
import org.droidtv.tv.media.BcstConstants;
import android.content.Context;
import android.util.Log;
import java.util.Map;
import android.os.Handler;
import android.os.Looper;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnSeekCompleteListener;
import android.net.Uri;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tv.media.ITvMediaRecordControl.IonTvRecordControlCallback;
import org.droidtv.tunerservice.playback.TvChannelPlayback;
import org.droidtv.tunerservice.recording.TimeshiftRecording;
import org.droidtv.tv.media.ITvMediaStream.TvMediaAudioInfo;
import org.droidtv.tv.media.ITvMediaRecordControl.PlaybackEitInfo;
import org.droidtv.tv.audio.ITvAudioManager;

public class TimeshiftPlayback extends TvAbstractPlayback implements OnSeekCompleteListener, ITSRecording {

	private static final String TAG = "TimeshiftPlayback";
	private PlayTVFacMediaPlayer playtvmpl;
	private static final int ONE_SECOND = 1000;
	private static final int ACTION_NONE = 0x00;
	private static final int ACTION_PAUSE = 0x01;
	private static final int ACTION_RESUME = 0x02;
	private static final int ACTION_STOP = 0x03;
	private static final int ACTION_SEEKTO = 0x04;
	private static final int ACTION_SETSPEED = 0x05;
	private static final int ACTION_RELEASE = 0x06;
	private static final int ACTION_PLAYFROMSTART = 0x07;

	private Handler mPlayHandler = null;
	private int mPendingUserAction = ACTION_NONE;
	private int mCurrentSpeed = 1;
	private int mCurrentDirection;
	private int mPendingUserSeekTime ;
	private boolean mSeekPending = false;

	private UserActionRunnable mUserActionRunnable;
	private SeekDoneRunnable mSeekCompletedRunnable;
	private NextSeekRunnable mNextSeekRunnable = new NextSeekRunnable();

	private TsPlaybackListenerClass Tslistener = null ;
	private ITvMediaRecordControl recCtrlInstance;
//	private PlayTvSubtitleHandler mSubtitleHandler = null;
	private enum TSServerPlayStateDef {
		STATE_IDLE(0),
		STATE_STARTING(1),
		STATE_RUNNING(2),
		STATE_STOPPING(3);
		private int state;
		private TSServerPlayStateDef(int newstate) {
			state = newstate;
		}
  	}
	private TSServerPlayStateDef tsServerPlayState = TSServerPlayStateDef.STATE_IDLE;
	// This variable is set to true when stop is triggered
	// to avoid having pending actions when onSeekComplete for seekTo(1) arrives.
	// This will block all calls once stop is triggered.
	private boolean tsPlaybackStopTriggered = false;
	private TvChannelPlayback mParent;
	private TimeshiftRecording tsRecording;

	private long mTrickStartTime;
	private int mTrickStartPos;
	private int mTrickNextPos; 

	private Handler mTimeUpdateHandler;
	private int currentTime = 0;
	private int recordedTime = 0;
	private  TvMediaAudioInfo audioInfo;
	private int PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED;
	private PlaybackEitInfo mTSInfo = null;
	private ITvAbstractPlaybackListener mPlaybackListener = null;
	private boolean trickmodeStatus = true;
	private Runnable mTimeUpdate = new Runnable() {
		@Override
		public void run() {
			synchronized(this) {
				try
				{
					currentTime = playtvmpl.getMediaPlayerInstance().getCurrentPosition() / ONE_SECOND;
					recordedTime = (int) (tsRecording.getRecordedDuration()/ONE_SECOND);
					Log.d(TAG, "current time - "+currentTime + ", " + recordedTime);
					mTimeUpdateHandler.postDelayed(mTimeUpdate, ONE_SECOND);
				} catch(Exception e) {
					Log.e(TAG, "Exceptional update of current time " + e.toString());
				}
			}
		}
	};

	public class TsPlaybackListenerClass extends IonTvRecordControlCallback {
		@Override
		public void onMaxCircularBufferReached() {
			Log.d(TAG, "onMaxCircularBufferReached");
			mPlayHandler.post(new HandleMaxBufferReached());
		}

		@Override
		public void onTimeshiftPlaybackStatus(int status) {
			Log.d(TAG, "onTimeshiftPlaybackStatus - "+status);
			mPlayHandler.post(new HandleTSNotifications(status));
		}

		@Override
		public void onServiceType(int type) {
			Log.d(TAG, "onServiceType: type -> " + type);
			if (mParent != null) {
				if(type == BcstConstants.RADIO_SERVICE_TYPE) {
					onServiceTypeDetected(ITvAbstractPlaybackListener.CHANNELTYPE_RADIO);
				}
				else {
					onServiceTypeDetected(ITvAbstractPlaybackListener.CHANNELTYPE_TV);
				}
			}
		}
		
		@Override
		public void onEITDataChanged(PlaybackEitInfo eitData) {
			 Log.d(TAG, "onEITDataChanged");
			 mPlayHandler.post(new HandleEITDataChanged(eitData));
		}
	}

	private class HandleEITDataChanged implements Runnable {
		PlaybackEitInfo data = null;
		
		public HandleEITDataChanged(PlaybackEitInfo EITdata) {
			data = EITdata;
		}
		
		 public void run() {
			if (data != null) {
				mTSInfo = data;
				onTimeshiftInfoChanged();
			}
		 }
	}
	
	private class HandleMaxBufferReached implements Runnable {
		public void run() {
			resume();
		}
	}

	private class HandleTSNotifications implements Runnable {
		int status;

		public HandleTSNotifications(int playstatus) {
			status = playstatus;
		}

		public void run() {
			switch (status) {
				case BcstConstants.TIMESHIFT_PLAY_STARTED:
					Log.d(TAG, "TS Play Started : time - "+currentTime);
					try {
						tsServerPlayState = TSServerPlayStateDef.STATE_RUNNING;
						if (PlaybackState != ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY) {
						   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
						   onPlayStateChanged(PlaybackState);
						}
						ITvAudioManager audioMgr = ITvAudioManager.Instance.getInterface();
						if (audioMgr != null) {
							audioMgr.setProperty(ITvAudioManager.AUDMGR_PROPERTY_SPDIF_COPYRIGHT, ITvAudioManager.AUDMGR_SPDIF_COPYRIGHT_PROTECTED);
						}
					} catch (Exception e) {
						Log.d(TAG, "Exception in TIMESHIFT_PLAY_STARTED "+ e.toString());
					}
				break;
				case BcstConstants.TIMESHIFT_PLAY_STOPPED:
					Log.d(TAG, "TS Play Stoped");
					if (tsRecording != null) {
						tsRecording.registerClient(null);
					}
					if(mParent != null) {
						mParent.closeTimeshiftPlay();
					}
					if(recCtrlInstance != null) {
						try {
							recCtrlInstance.unregisterListenerCallback(Tslistener);
						} catch (Exception e) {
						}
						recCtrlInstance = null;
					}
					mParent = null;
					tsPlaybackStopTriggered = false;
				break;
				case BcstConstants.TIMESHIFT_PLAY_SYSTEM_ERROR:
					Log.d(TAG, "TS Play Error, stop timeshift playback");
					onPlayFinished();
				break;
				default:
				break;
			}
		}
	};

	public TimeshiftPlayback(Context context, TvChannelPlayback parent, PlayTVFacMediaPlayer mpl, ITvAbstractPlaybackListener listener) {
		playtvmpl = mpl;
		tsRecording = parent.getTimeshiftRecordingObject();
		mPlayHandler = new Handler(Looper.getMainLooper());
		mTimeUpdateHandler = new Handler(Looper.getMainLooper());
		mPlaybackListener = listener;
		if(null != tsRecording) {
			tsRecording.registerClient((ITSRecording)this);
			currentTime = (int)(tsRecording.getRecordedDuration()/ONE_SECOND); 
			recordedTime = currentTime;
		}
		// Start current time calculation
		if (mTimeUpdateHandler != null) {
			mTimeUpdateHandler.postDelayed(mTimeUpdate, ONE_SECOND);
		}
		playtvmpl.getMediaPlayerInstance().setOnSeekCompleteListener(this);
		Tslistener = new TsPlaybackListenerClass();
		mParent = parent;
		recCtrlInstance = playtvmpl.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaRecordControl();
		recCtrlInstance.registerListenerCallback(Tslistener);
		trickmodeStatus = true;
        	// generate Onpause to subtitle handler class
		/*mSubtitleHandler = PlayTvSubtitleHandler.getInstance(true);
		 if(mSubtitleHandler!=null) {
			mSubtitleHandler.OnPause();
		 }*/
		mSeekPending = false;
		    Log.d(TAG, "Changing recording mode to timeshift ");
		    recCtrlInstance.changeRecordingMode(BcstConstants.RECORDING_MODE_TIMESHIFT);
//		PlayTvLogger.sendPVRInfo(Activity.PAUSE_TV);
		playtvmpl.startTimeshiftPause();
/* TODO - to be anabled for PPR2
               ITvMediaControl mediaCtrl = playtvmpl.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaControl();
               if(null != mediaCtrl){
                    audioInfo = mediaCtrl.getTVAudio();
               }
               else{
                    Log.d(TAG, "Get media control instance failed");
                    audioInfo.langCode = 0;
                    audioInfo.type = 0;
                    audioInfo.pid = 8191;
                    audioInfo.langId = 0;
               }
*/
	}

	@Override
	public void setPlayer(PlayTVFacMediaPlayer mpl) {
		synchronized (playtvmpl) {
			playtvmpl = mpl;
		}
	}

	@Override
	public void onSeekComplete(MediaPlayer mp) {
		Log.e(TAG, "onSeekCompleted  playback");
		try {
			synchronized(this) {
				currentTime = playtvmpl.getMediaPlayerInstance().getCurrentPosition() / ONE_SECOND;
			}
		}catch (Exception e) {
			Log.e(TAG, "error on onSeekComplete " + e.toString());
		}
		mSeekCompletedRunnable = new SeekDoneRunnable();
		mPlayHandler.post(mSeekCompletedRunnable);
	}

	@Override
	public void stop() {
		Log.d(TAG, "stop ");
		tsServerPlayState = TSServerPlayStateDef.STATE_STOPPING;
                 /*mSubtitleHandler = PlayTvSubtitleHandler.getInstance(true);
                 if(mSubtitleHandler!=null) {
                        mSubtitleHandler.OnStop();
                 }*/
		if(mTimeUpdateHandler != null) {
			mTimeUpdateHandler.removeCallbacks(mTimeUpdate);
		}
		//mParent.sendonStateChanged(TV_CHANNEL_DETECTED); // remove radio channel Background if any is there : Todo when timeshift across zaps is supported
		mUserActionRunnable = new UserActionRunnable(ACTION_STOP);
	    mPlayHandler.post(mUserActionRunnable);
	}

	@Override
	public boolean pause() {
		Log.d(TAG, "pause ");
		boolean status = false;
		if (!tsPlaybackStopTriggered) {
			mUserActionRunnable = new UserActionRunnable(ACTION_PAUSE);
			mPlayHandler.post(mUserActionRunnable);
			status = true;
		} else {
			Log.d(TAG, "pause dropped - stop in progress !!!");
		}
		return status;
	}

	@Override
	public void resume() {
		Log.d(TAG, "resume ");
		if (!tsPlaybackStopTriggered) {

			mUserActionRunnable = new UserActionRunnable(ACTION_RESUME);
			mPlayHandler.post(mUserActionRunnable);
		} else {
			Log.d(TAG, "resume dropped - stop in progress !!!");
		}
	}

	@Override
	public void seekTo(int msecs) {
		Log.d(TAG, "seek to ");
		if (!tsPlaybackStopTriggered) {
			mUserActionRunnable = new UserActionRunnable(ACTION_SEEKTO);
			mUserActionRunnable.setPendingSeekTime(msecs / ONE_SECOND);
			mPlayHandler.post(mUserActionRunnable);

		} else {
			Log.d(TAG, "seekTo dropped - stop in progress !!!");
		}
	}

	@Override
	public void setSpeed(int speed, boolean forward) {
		Log.d(TAG, "setSpeed ");
		if (!tsPlaybackStopTriggered) {

			mUserActionRunnable = new UserActionRunnable(speed, forward ? BcstConstants.DIRECTION_FORWARD : BcstConstants.DIRECTION_BACKWARD);
			Log.d(TAG, "created an Action for setspeed in UserAction Runnable ************");
			mPlayHandler.post(mUserActionRunnable);
		} else {
			Log.d(TAG, "setSpeed dropped - stop in progress !!!");
		}
	}
	
	@Override
	public boolean getTrickmodeStatus() {
		return trickmodeStatus;
	}

	private class UserActionRunnable implements Runnable {
	  int userActionRequested;
	  int userSpeed, userPendingSeekTime;
	  int userDirection;

	  UserActionRunnable(int action) {
	    userActionRequested = action;
	  }

	  void setPendingSeekTime(int pendingSeekTime) {
		  userPendingSeekTime = pendingSeekTime;
	  }

	  UserActionRunnable(int speed, int direction) {
		   userActionRequested = ACTION_SETSPEED;
		   userSpeed = speed;
		   userDirection = direction;
	  }

	  public void  run() {
		    Log.d(TAG, "running the UserActionRunnable speed is "+ mCurrentSpeed);
		    mPlayHandler.removeCallbacks(mNextSeekRunnable);
			if( !mSeekPending ) {
				switch(userActionRequested) {
					case ACTION_PAUSE:
						Log.d(TAG, "running the UserActionRunnable ACTION_PAUSE");
						try {
						   playtvmpl.getMediaPlayerInstance().pause();
						   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED;
						   onPlayStateChanged(PlaybackState);
						} catch (Exception e) {
						   Log.e(TAG, "error while pause " + e.toString());
						}
					break;
					case ACTION_STOP:
					   Log.d(TAG, "running the UserActionRunnable ACTION_STOP");
					   try {
							tsPlaybackStopTriggered = true;
					   		playtvmpl.getMediaPlayerInstance().seekTo(1);
							mSeekPending = true;
							tsServerPlayState = TSServerPlayStateDef.STATE_STOPPING;
					   } catch (Exception e) {
						   Log.e(TAG, "error while stop " + e.toString());
					   }
					break;
					case ACTION_SEEKTO:
						Log.d(TAG, "running the UserActionRunnable ACTION_SEEK_TO ");
						mCurrentSpeed = 1;
						// check on minimum data available for forward direction
						if((userPendingSeekTime > currentTime) && (tsRecording.isMinimumDataAvailable() == false) &&
						(tsServerPlayState == TSServerPlayStateDef.STATE_IDLE))
						{
							Log.d(TAG, "ACTION_SEEKTO: Minimum data not available so jumping to live ");
							onPlayFinished();
						}
						else
						{
							try {
								if(userPendingSeekTime > recordedTime) {
									onPlayFinished();
								} else {
									playtvmpl.getMediaPlayerInstance().seekTo(userPendingSeekTime * ONE_SECOND);
									mSeekPending = true;
									if(tsServerPlayState == TSServerPlayStateDef.STATE_IDLE) {
										tsServerPlayState = TSServerPlayStateDef.STATE_STARTING;
										//recCtrlInstance.startTimeshiftPlayback1(audioInfo);
										recCtrlInstance.startTimeshiftPlayback();
										playtvmpl.startTimeshiftPlayback();
									}
								}
							} catch (Exception e) {
							   Log.e(TAG, "error while seekto " + e.toString());
							}
						}

					break;
					case ACTION_RESUME:
						Log.d(TAG, "running the UserActionRunnable ACTION_RESUME " + tsServerPlayState.ordinal());
						if(tsRecording.isMinimumDataAvailable())
						{
							try {
								playtvmpl.getMediaPlayerInstance().start();
								if(tsServerPlayState == TSServerPlayStateDef.STATE_IDLE) {
									tsServerPlayState = TSServerPlayStateDef.STATE_STARTING;
									//recCtrlInstance.startTimeshiftPlayback1(audioInfo);
									recCtrlInstance.startTimeshiftPlayback();
									playtvmpl.startTimeshiftPlayback();
								} else {
									PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
									onPlayStateChanged(PlaybackState);
								}
							} catch(Exception e) {
								Log.d(TAG, "start playback exception " + e.toString());
							}
						}
						else
						{
							Log.d(TAG, "ACTION_RESUME: Minimum data not available so jumping to live ");
							onPlayFinished();
						}
					break;
					case  ACTION_SETSPEED:
						Log.d(TAG, "running the UserActionRunnable ACTION_SET_SPEED ****");
						// for rewind, no need to check minimum data available. Only for fast forward, check minimum data available
						if((userDirection == BcstConstants.DIRECTION_FORWARD) && (tsRecording.isMinimumDataAvailable() == false) &&
						(tsServerPlayState == TSServerPlayStateDef.STATE_IDLE))
						{
							Log.d(TAG, "ACTION_SETSPEED: Minimum data not available so jumping to live ");
							onPlayFinished();
						}
						else
						{
							mCurrentSpeed = userSpeed;
							mCurrentDirection = userDirection;
							try {
								if(mCurrentSpeed == 1) {
									try {
										playtvmpl.getMediaPlayerInstance().start();
									   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
									   onPlayStateChanged(PlaybackState);
									} catch (Exception e) {
										Log.e(TAG, "error while resume for speed1 " + e.toString());
									}
								} else {
									playtvmpl.getMediaPlayerInstance().pause();
								   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY;
								   onPlayStateChanged(PlaybackState);
									int val = calcNextJump(mCurrentSpeed, mCurrentDirection);
									Log.d(TAG, "calcNextJump "+val);
									if(val >= 0) {
										if(val > recordedTime) {
											onPlayFinished();
										} else {
											mTrickStartTime = System.currentTimeMillis();
											mTrickStartPos = currentTime;
											Log.d(TAG, "start trick " + mTrickStartTime + ", " + mTrickStartPos);
											playtvmpl.getMediaPlayerInstance().seekTo(val * ONE_SECOND);
											mSeekPending = true;
										}
									} else {
										if (mUserActionRunnable != null) {
											mPlayHandler.removeCallbacks((Runnable)mUserActionRunnable);
										}
										mUserActionRunnable = new UserActionRunnable(ACTION_PLAYFROMSTART);
										mPlayHandler.post(mUserActionRunnable);
									}
									Log.d(TAG, "done setSpeed request");
								}
								if(tsServerPlayState == TSServerPlayStateDef.STATE_IDLE) {
									tsServerPlayState = TSServerPlayStateDef.STATE_STARTING;
									//recCtrlInstance.startTimeshiftPlayback1(audioInfo);
									recCtrlInstance.startTimeshiftPlayback();
									playtvmpl.startTimeshiftPlayback();
								}
							} catch (Exception e) {
							   Log.e(TAG, "error while set speed" + e.toString());
							}
						}
					break;
					case ACTION_PLAYFROMSTART:
						Log.d(TAG, "running the UserActionRunnable ACTION_PLAYFROMSTART ");
						playtvmpl.getMediaPlayerInstance().start();
						PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
						onPlayStateChanged(PlaybackState);
						playtvmpl.getMediaPlayerInstance().seekTo(0);
						mSeekPending = true;
				}
			} else {
				Log.d(TAG, "running the UserActionRunnable ACTION_PENDING *******");
				mPendingUserAction = userActionRequested;
				mCurrentSpeed = userSpeed;
				mCurrentDirection = userDirection;
				mPendingUserSeekTime = userPendingSeekTime;
			}
	    }
    }

    private class NextSeekRunnable implements Runnable {
		public void run() {
			Log.d(TAG, "next seek " + mTrickNextPos);
			playtvmpl.getMediaPlayerInstance().seekTo(mTrickNextPos * ONE_SECOND);
			mSeekPending = true;
		}
    }

    private void continueTrickJump() {
		int val = calcNextJump(mCurrentSpeed, mCurrentDirection);
		Log.d(TAG, "continueTrickJump "+ val);
		if(val >= 0) {
			if(val > recordedTime) {
				onPlayFinished();
			} else {
				long expectedTime = (long)( (currentTime - mTrickStartPos) / (mCurrentSpeed * mCurrentDirection) );
				expectedTime = (expectedTime * ONE_SECOND) + mTrickStartTime;
				long clockTime = System.currentTimeMillis();
				Log.d(TAG, "for wait " + expectedTime + ", " + clockTime);
				if(clockTime < expectedTime) {
					mTrickNextPos = val;
					mPlayHandler.postDelayed(mNextSeekRunnable, (expectedTime - clockTime));
				} else {
					val = calcNextJump(mCurrentSpeed, mCurrentDirection, currentTime);
					if(val >= 0) {
						currentTime = val;
					} else {
						currentTime = 0;
					}
					continueTrickJump();
				}
			}
		} else {
			if (mUserActionRunnable != null) {
				mPlayHandler.removeCallbacks((Runnable)mUserActionRunnable);
			}
			mCurrentSpeed = 1;
			mCurrentDirection = BcstConstants.DIRECTION_FORWARD;
			mUserActionRunnable = new UserActionRunnable(ACTION_PLAYFROMSTART);
			mPlayHandler.post(mUserActionRunnable);
		}
    }

    private class SeekDoneRunnable implements Runnable {

	    public void run() {

		Log.d(TAG, "running SeekDoneRunnable ");
		mPlayHandler.removeCallbacks(mNextSeekRunnable);
		mSeekPending = false;

	    switch(mPendingUserAction) {

	       case ACTION_NONE:
				Log.d(TAG, "running SeekDoneRunnable ACTION_NONE");
	            		mPendingUserAction = ACTION_NONE;
				if(tsServerPlayState == TSServerPlayStateDef.STATE_STOPPING) {
					release(true);
					// Sending onTimedhiftPlaystatechanged from timeshift to live (playing)
					onPlayStateChanged(ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED);
				} else if(mCurrentSpeed != 1) {
					continueTrickJump();
				} else {
					if (mParent != null) {
						onSeekCompleteNotify();
					}
					if(!isPlaying()) {
						playtvmpl.getMediaPlayerInstance().start();
					}
				   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
				   onPlayStateChanged(PlaybackState);
					Log.d(TAG, "Not in TrickMode skipping ACTION_NONE SeekDoneRunnable ACTION_NONE ****");
				}
				break;
	       case ACTION_PAUSE:
				Log.d(TAG, "running SeekDoneRunnable ACTION_PAUSE");
		            	mPendingUserAction = ACTION_NONE;
		            	mCurrentSpeed = 1;
		            	try {
					playtvmpl.getMediaPlayerInstance().pause();
				   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED;
				   onPlayStateChanged(PlaybackState);
		    	    	} catch (Exception e) {
					Log.e(TAG, "error while pause SeekDoneRunnable " + e.toString());
		    	    	}
			    	break;
	        case ACTION_STOP:
				Log.d(TAG, "running SeekDoneRunnable ACTION_STOP");
	    	    		mPendingUserAction = ACTION_NONE;
	    	    		mCurrentSpeed = 1;
	    	    		Log.d(TAG, "STOP playback Called!!!");
				try {
					playtvmpl.getMediaPlayerInstance().seekTo(1);
					mSeekPending = true;
					tsServerPlayState = TSServerPlayStateDef.STATE_STOPPING;
				} catch (Exception e) {
				   	Log.e(TAG, "error while stop in seekdone " + e.toString());
				}
				break;
	        case ACTION_RESUME:
	    	   		Log.d(TAG, "running SeekDoneRunnable ACTION_RESUME");
	    	   		mCurrentSpeed = 1;
	    	   		mPendingUserAction = ACTION_NONE;
			   	try {
					playtvmpl.getMediaPlayerInstance().start();
				   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
				   onPlayStateChanged(PlaybackState);
				} catch(Exception e) {
					Log.d(TAG, "start playback in seekdone exception " + e.toString());
				}
	    			break;
	        case ACTION_SEEKTO:
				Log.d(TAG, "running SeekDoneRunnable ACTION_SEEKTO");
	            		mPendingUserAction = ACTION_NONE;
	            		mCurrentSpeed = 1;
				try {
					if(mPendingUserSeekTime > recordedTime) {
						onPlayFinished();
					} else {
	            		playtvmpl.getMediaPlayerInstance().seekTo(mPendingUserSeekTime * ONE_SECOND);
						mSeekPending = true;
						PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY;
					    onPlayStateChanged(PlaybackState);
					}
				} catch(Exception e) {
					Log.d(TAG, "seek in seekdone exception " + e.toString());
				}
				break;
	       case ACTION_SETSPEED:
				Log.e(TAG, "running SeekDoneRunnable ACTION_SETSPEED");
				mPendingUserAction = ACTION_NONE;
				Log.e(TAG, "seek to has called......to media player  SeekDone ACTION_SETSPEED");
				try {
					if(mCurrentSpeed == 1) {
						playtvmpl.getMediaPlayerInstance().start();
					   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
					   onPlayStateChanged(PlaybackState);
					} else {
						int val = calcNextJump(mCurrentSpeed, mCurrentDirection);
						if(val >= 0) {
							if(val > recordedTime) {
								onPlayFinished();
							} else {
								mTrickStartTime = System.currentTimeMillis();
								mTrickStartPos = currentTime;
								Log.d(TAG, "change trick " + mTrickStartTime + ", " + mTrickStartPos);
								playtvmpl.getMediaPlayerInstance().seekTo(val * ONE_SECOND);
								mSeekPending = true;
							   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY;
							   onPlayStateChanged(PlaybackState);
							}
						} else {
							if (mUserActionRunnable != null) {
								mPlayHandler.removeCallbacks((Runnable)mUserActionRunnable);
							}
							mCurrentSpeed = 1;
							mCurrentDirection = BcstConstants.DIRECTION_FORWARD;
							mUserActionRunnable = new UserActionRunnable(ACTION_PLAYFROMSTART);
							mPlayHandler.post(mUserActionRunnable);
						}
					}
				} catch (Exception e) {
			    		Log.e(TAG, "error while set speed in seekdone " + e.toString());
				}
				break;
	    }
	  }
    }

	private int calcNextJump(int speed, int direction, int startTime) {
		int jumpTo = (direction == BcstConstants.DIRECTION_FORWARD) ?  (currentTime + speed) :
												(currentTime - speed);

		Log.d(TAG,"jumpTo "+jumpTo);
		return jumpTo;
	}

   	private int calcNextJump(int speed, int direction) {
	    	Log.d(TAG,"calcNextJump speed "+speed +" direction "+direction+ " current duration " + currentTime);

		return calcNextJump(speed, direction, currentTime);
   	}

	public void onPlayFinished() {
		Log.d(TAG, "onPlayFinished");
		try {
			/*
			playtvmpl.getMediaPlayerInstance().seekTo(1);
			mSeekPending = true;
			tsServerPlayState = TSServerPlayStateDef.STATE_STOPPING;
			*/
			if(tsServerPlayState != TSServerPlayStateDef.STATE_STOPPING)
			{
				Log.d(TAG, "onPlayFinished : Stop call");
				stop();
			}
		} catch (Exception e) {
		   	Log.e(TAG, "error while stop in playfinished " + e.toString());
		}
	}

	public boolean onError(PlayTvMediaPlayer mpl, int what , int extra) {
		Log.d(TAG, "onError");
		release();
		return true;
	}

	public void release(boolean restoreStartedState) {
		try {
			playtvmpl.getMediaPlayerInstance().start();
		 } catch(Exception e) {
			Log.e(TAG, "exception in restore playback "+ e.toString());
		}
		release();
	}

	@Override
	public void release() {
		try {
			tsPlaybackStopTriggered = true;
			tsServerPlayState = TSServerPlayStateDef.STATE_STOPPING;
			playtvmpl.getMediaPlayerInstance().setOnSeekCompleteListener(null);
			playtvmpl.getMediaPlayerInstance().GetTvMediaRecordControlInstance().stopTimeshiftPlayback();
			playtvmpl.stopTimeshiftPlayback();
			if(mTimeUpdateHandler != null) {
				mTimeUpdateHandler.removeCallbacks(mTimeUpdate);
			}
		} catch(Exception e) {
			Log.e(TAG, "exception in release playback "+ e.toString());
		}
	}

	@Override
	public int getCurrentDuration() {
		return currentTime * ONE_SECOND;
	}

	@Override
	public int getTotalDuration() {
		Log.e(TAG, "gettotal duration not expected");
		return 0;
	}

	@Override
	public boolean isPlaying() {
		return playtvmpl.getMediaPlayerInstance().isPlaying();
	}

	@Override
	public void play(Uri uri, Medium medium,  Map<String,String> headers) {
		Log.e(TAG,"play not expected ");
	}

	@Override
	public Medium getMedium() {
		if(playtvmpl != null) {
			//return playtvmpl.getCurrentMedium();
			return Medium.MEDIUM_TSFILE;
		}
		return Medium.MEDIUM_INVALID;
	}

	@Override
	public int getServiceType() {
		/*if(playtvmpl != null) {
			return playtvmpl.getServiceType();
		}*/
		return playtvmpl.SERVICE_TYPE_INVALID;
	}

	@Override
	public void enableTrickModes(boolean status) {
		Log.d(TAG, "enableTrickModes "+status);
		onTrickModeEnabled(status);
		trickmodeStatus = status;
	}

	@Override
	public void registerListener(ITvAbstractPlaybackListener listener) {
	
	}
	
	@Override
	public void unRegisterListener(ITvAbstractPlaybackListener listener) {

	}
	
	// -------- TSRecording Interface notifications -----------

	@Override
	public void onTSRecordingStarted() {
	}

	@Override
	public void onTSRecordingStopped() {
		Log.d(TAG, "TS Recording stopped");
		onPlayFinished();
	}

	@Override
	public void onTSRecordingStopped(Boolean isHDDReadError) {
		Log.d(TAG, "TS Recording stopped with HDDReadError");
		onPlayError(ITvAbstractPlaybackListener.PLAYERROR_HDD, 0, 0);
		onPlayFinished();
	}

	public boolean isTSPlayBackActive() {
		if(tsServerPlayState!=TSServerPlayStateDef.STATE_STOPPING) {
			return true;
		}
		else {
			return false;
		}
	}
	
/*	private PlayTvSubtitleHandler getSubtitleHandlerForTS() {
		return PlayTvSubtitleHandler.getInstance(true);
	}*/

	@Override
	public int getPlaybackState() {
		return PlaybackState;
	}

	public void onSeekCompleteNotify() {
		if (mPlaybackListener != null) {
			mPlaybackListener.onSeekComplete(ITvAbstractPlaybackListener.MODE_TIMESHIFT);
		}
	}

	public void onPlayError(int error, int what, int extra) {
		if (mPlaybackListener != null) {
			mPlaybackListener.onPlayError(error, what, extra, ITvAbstractPlaybackListener.MODE_TIMESHIFT);
		}
	}

	public void onServiceTypeDetected(int type) {
		if (mPlaybackListener != null) {
			mPlaybackListener.onServiceTypeDetected(type);
		}
	}
	
	public void onTrickModeEnabled(boolean status) {
		if (mPlaybackListener != null) {
			mPlaybackListener.onTrickModeEnabled(status, ITvAbstractPlaybackListener.MODE_TIMESHIFT);
		}
	}

	public void onPlayStateChanged(int state) {
		if (mPlaybackListener != null) {
			mPlaybackListener.onPlayStateChanged(state, ITvAbstractPlaybackListener.MODE_TIMESHIFT);
		}
	}
	
	public void onTimeshiftInfoChanged() {
		if (mPlaybackListener != null) {
			mPlaybackListener.onTimeshiftInfoChanged();
		}
	}
	
	public PlaybackEitInfo getTimeshiftInfo() {
		return mTSInfo;
	}
	
	public void setTimeShiftInfo(PlaybackEitInfo info) {
		mTSInfo = info;
	}
	
	public void playCatchUpChannel(Uri uri,Medium medium, Map<String,String> headers) {
		Log.d(TAG, "playCatchUpChannel");
		if(isPlaying()) {
			onPlayStateChanged(ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING);
		} else {
			onPlayStateChanged(ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED);
		}
	}
}
