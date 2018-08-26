package org.droidtv.tunerservice.playback;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;

//import org.droidtv.playtv.PlayTvApplication;
//import org.droidtv.playtv.osds.RecPlayKeyHandler;
//import org.droidtv.playtv.osds.SystemEvents;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tv.media.BcstConstants;
import org.droidtv.tv.media.ITvMediaRecordControl;
import org.droidtv.tv.media.ITvMediaRecordControl.IonTvRecordControlCallback;
import org.droidtv.tv.media.ITvMediaRecordControl.PlayableData;
import org.droidtv.tv.media.ITvMediaControl;
import org.droidtv.tv.media.ITvMediaControl.IonMediaChangeListener;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tunerservice.util.PlayTvHDDUtils;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tv.media.ITvMediaRecordControl.RecordingInfo;
import org.droidtv.tv.audio.ITvAudioManager;

import android.content.ContentProviderClient;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnSeekCompleteListener;
import android.os.Handler;
import android.util.Log;
import android.net.Uri;

public class PvrPlayback extends TvAbstractPlayback implements OnSeekCompleteListener{
    private static final String TAG = "PvrPlayback";
	private PlayTVFacMediaPlayer playtvmpl;
	private ITvMediaRecordControl recordinstance;
	private ITvMediaControl controlinstance;
	private String filePath;
	private String cicamId;
	private int programNumber;
	private int playrecordingId;
	private int resumeInfo, seekAfterPlayable = -1;
	private boolean tvserverPlayTriggered;
	private PvrPlaybackListenerClass Pvrlistener = null ;
	private PvrMediaControlListenerClass mediacontrollistener = null;
	Context mContext;
	private Handler mTimeUpdateHandler;
	private boolean isSpinnerSet= false;
	private boolean isFirstTimeCheck = true;
	private int mCachedRecId = -1;
	private Uri mCachedUri = null;
	private Medium mCachedMedium;
	private Map<String,String> mCachedHeaders	= null;
	public static final int PLAYBACK_SHOWSPINNER = 40;
	public static final int PLAYBACK_REMOVESPINNER = 41;
	public static final int PLAYBACK_RESETSPEED = 42;
	public static final int PLAYBACK_SEEKCOMPLETE = 43;
	public static final int PLAYBACK_PLAYERROR_HDD = 44;
	public static final int PLAYBACK_RADIO = 45;
	public static final int PLAYBACK_TV = 46;
	public static final int PLAYBACK_PLAYERROR_SYSTEM = 47;
	public static final int PLAYBACK_DISABLETRICKMODES = 48;
	public static final int PLAYBACK_ENABLETRICKMODES = 49;
	public static final int PLAYBACK_PLAYSTATECHANGED = 50;
	private Handler mPlayHandler = null;
	private static final int ONE_SECOND = 1000;

	private static final int ACTION_NONE = 0x00;
	private static final int ACTION_PAUSE = 0x01;
	private static final int ACTION_RESUME = 0x02;
	private static final int ACTION_STOP = 0x03;
	private static final int ACTION_SEEKTO = 0x04;
	private static final int ACTION_SETSPEED = 0x05;
	private static final int ACTION_PLAYFROMSTART = 0x06;
	private static final int ACTION_NOTPLAYABLE = 0x07;

	private int mPendingUserAction = ACTION_NONE;
	private int mCurrentSpeed = 1;
	private int mCurrentDirection = BcstConstants.DIRECTION_FORWARD;
	private int mPendingUserSeekTime ;
	private boolean mSeekPending = false;

	private long mTrickStartTime;
	private int mTrickStartPos;
	private int mTrickNextPos;
	
	// Criteria, based on which released of playback is done
	private int releaseCriterion = PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH |
									PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD |
									PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD;

	private Uri mUri = null;
	private Map<String,String> mHeaders =  null;

	private UserActionRunnable mUserActionRunnable;
	private SeekDoneRunnable mSeekCompletedRunnable;
	private NextSeekRunnable mNextSeekRunnable = new NextSeekRunnable();
	private List<ITvAbstractPlaybackListener> mPlaybackListener = null;
	private PlaytvStateChangeCallbacks mPlayTvStateChangeListener = null;
	private enum stopReasonDef {
		REASON_NONE(0),
		REASON_STOP(1),
		REASON_FINISHED(2),
		REASON_ERROR(3);
		private int reason;
		private stopReasonDef(int stopreason) {
			reason = stopreason;
			Log.d(TAG, "stopreason " + reason);
		}
	}
	private stopReasonDef stopReason = stopReasonDef.REASON_NONE;
	private int currentTime = 0;
	private int totalTime = 0;
	private boolean trickmodeStatus = true;
	private int PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
	private RecordingInfo mRecordingInfo;
	private Runnable mTimeUpdate = new Runnable() {
		@Override
		public void run() {
			try {
				synchronized(this) {
					if(stopReason == stopReasonDef.REASON_NONE) {
						currentTime = playtvmpl.getMediaPlayerInstance().getCurrentPosition() / ONE_SECOND;
						totalTime = playtvmpl.getMediaPlayerInstance().getDuration() / ONE_SECOND;
					}
					mTimeUpdateHandler.postDelayed(mTimeUpdate, ONE_SECOND);
				}
			} catch (Exception e) {
				Log.e(TAG, "Exceptionally not updating time " + e.toString() );
			}
		}
	};

	public class PvrMediaControlListenerClass extends IonMediaChangeListener {
		@Override
		public void onMediaStateChanged(int media) {

		}
	};

	public class PvrPlaybackListenerClass extends IonTvRecordControlCallback {
		@Override
		public void onRecordPlaybackStatus(int status) {
			Log.d(TAG, "onRecordPlaybackStatus "+status);
			 mPlayHandler.post(new RecordPlayResponse(status));
		}

		@Override
		public void licenseCheckStatus(boolean status)  {
            Log.d(TAG, "licenseCheckStatus status " + status + ", " + isSpinnerSet);
			if(status) {
			  if(isSpinnerSet) {
   			    isSpinnerSet = false;
			    onLicenseExchangeHappening(false);
			   }
				if(seekAfterPlayable != -1) {
					jumpTo(seekAfterPlayable);
					seekAfterPlayable = -1;
				}
			}
			else
			{
				mUserActionRunnable = new UserActionRunnable(ACTION_NOTPLAYABLE, seekAfterPlayable, mCurrentDirection);
				mPlayHandler.post(mUserActionRunnable);
			}
		}

        @Override
		public void onPlayNotPossible(int reason, int playTime) {
		     Log.d(TAG, "OnPlayNotPossible reason " + reason + " play time" + playTime);
		     if( (reason ==1) || (reason == 0) ) { // BAD_RETENTION // // BAD_LICENCSE
				mUserActionRunnable = new UserActionRunnable(ACTION_NOTPLAYABLE, playTime, mCurrentDirection);
				mPlayHandler.post(mUserActionRunnable);
		    } else {
		       /*CHECKING_WITH_CICAM*/
    			if(!isSpinnerSet) {
      	          		isSpinnerSet = true;
    				onLicenseExchangeHappening(true);
    			}
		    }
		}

		@Override
		public void onServiceType(int type) {
			Log.d(TAG, "onServiceType: type -> " + type);
			if(type == BcstConstants.RADIO_SERVICE_TYPE)
				onServiceTypeDetected(ITvAbstractPlaybackListener.CHANNELTYPE_RADIO);
			else
				onServiceTypeDetected(ITvAbstractPlaybackListener.CHANNELTYPE_TV);
		}
	 };

	 private class RecordPlayResponse implements Runnable {
	 	int status;

	 	RecordPlayResponse(int newstatus) {
			status = newstatus;
	 	}

	 	public void  run() {
			switch (status) {
			case BcstConstants.RECORD_PLAY_STARTED:
				Log.d(TAG, "resume info " + resumeInfo);
				try {
					PlaybackState=ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
					onPlayStateChanged(PlaybackState);
					mTimeUpdateHandler.postDelayed(mTimeUpdate,ONE_SECOND);
					ITvAudioManager audioMgr = ITvAudioManager.Instance.getInterface();
					if (audioMgr != null) {
						audioMgr.setProperty(ITvAudioManager.AUDMGR_PROPERTY_SPDIF_COPYRIGHT, ITvAudioManager.AUDMGR_SPDIF_COPYRIGHT_PROTECTED);
					}
				} catch(Exception e) {
					Log.d(TAG, "onrecord status " + e.toString());
				}
				isFirstTimeCheck = true;

				totalTime = playtvmpl.getMediaPlayerInstance().getDuration() / ONE_SECOND;
            			CheckForPlayable(resumeInfo,BcstConstants.DIRECTION_FORWARD);
            			break;
			case BcstConstants.RECORD_PLAY_STOPPED:
				setMute(false);
				String[] proj = { IRecordingsContract.C_RECORDING_TYPE };
				String where = IRecordingsContract.C_RECORDING_ID + "=?";
				String[] whereArgs = { Integer.toString(playrecordingId) };
				Cursor c;
				c = mContext.getContentResolver().query(
						IRecordingsContract.CONTENT_URI_Recordings, proj, where,
						whereArgs, null);
				ContentValues values = new ContentValues();
				PlaybackState=ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
				Log.d(TAG, "stopReason "+stopReason);
				switch(stopReason) {
				case REASON_ERROR:
				case REASON_NONE:
					if ((c != null) && (c.getCount() == 1) && (c.moveToFirst())) {
						int cRecordingType = c.getInt(0);
						if (cRecordingType == IRecordingsContract.RecordingType.RECORDING_NEW.ordinal()){
								cRecordingType = IRecordingsContract.RecordingType.RECORDING_PARTIALLY_VIEWED.ordinal();
								values.put(IRecordingsContract.C_RECORDING_TYPE, cRecordingType);
						}
						values.put(IRecordingsContract.C_RESUME_INFO, 0);
						if(0 == mRecordingInfo.recordingError){
						    /*update retention only if there is no error*/
						    values.put(IRecordingsContract.C_RETENTION_INFO, mRecordingInfo.retentionInfo);
						}
						mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, values, where, whereArgs);
						c.close();
					}
					// Send state changed only if there are no playbacks cached
					if (mCachedRecId == -1) {
						synchronized (mPlaybackListener) {
							for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
								listener.onPlayFailed(mUri, Medium.MEDIUM_PVRFILE, -1, ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
							}
						}
					}
					break;
				case REASON_FINISHED:
					if ((c != null) && (c.getCount() == 1) && (c.moveToFirst())) {
						int cRecordingType = c.getInt(0);
						if ( (cRecordingType == IRecordingsContract.RecordingType.RECORDING_NEW.ordinal()) ||
							 (cRecordingType == IRecordingsContract.RecordingType.RECORDING_PARTIALLY_VIEWED.ordinal()) ){
								cRecordingType = IRecordingsContract.RecordingType.RECORDING_VIEWED.ordinal();
								values.put(IRecordingsContract.C_RECORDING_TYPE, cRecordingType);
						}
						values.put(IRecordingsContract.C_RESUME_INFO, 0);
						if(0 == mRecordingInfo.recordingError){
						    /*update retention only if there is no error*/
						    values.put(IRecordingsContract.C_RETENTION_INFO, mRecordingInfo.retentionInfo);
						}
						mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, values, where, whereArgs);
						c.close();
					}
					currentTime = 0;
					// Send state changed only if there are no playbacks cached
					if (mCachedRecId == -1) {
						onPlayStateChanged(PlaybackState);
					}
					break;
				case REASON_STOP:
					if ((c != null) && (c.getCount() == 1) && (c.moveToFirst())) {
						int cRecordingType = c.getInt(0);
						if (cRecordingType == IRecordingsContract.RecordingType.RECORDING_NEW.ordinal()){
								cRecordingType = IRecordingsContract.RecordingType.RECORDING_PARTIALLY_VIEWED.ordinal();
								values.put(IRecordingsContract.C_RECORDING_TYPE, cRecordingType);
						}
						Log.d(TAG, "updating resume info to " + currentTime);
						values.put(IRecordingsContract.C_RESUME_INFO, currentTime);
					        if(0 == mRecordingInfo.recordingError){
					            /*update retention only if there is no error*/
					            values.put(IRecordingsContract.C_RETENTION_INFO, mRecordingInfo.retentionInfo);
						}
						mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, values, where, whereArgs);
						c.close();
					}
					// Send state changed only if there are no playbacks cached
					if (mCachedRecId == -1) {
						onPlayStateChanged(PlaybackState);
					}
					break;
				}

				// Start next recording if pending
				if (mCachedRecId != -1) {
					play(mCachedUri, mCachedMedium, mCachedHeaders);
					mCachedRecId = -1;
				} else {
					if(recordinstance != null) {
						try {
							recordinstance.unregisterListenerCallback(Pvrlistener);
						} catch (Exception e) {
						}
						recordinstance = null;
					}
					if (controlinstance != null) {
						try {
							controlinstance.unRegisterListenerCallback(mediacontrollistener);
						} catch (Exception e) {
						}
						controlinstance = null;
					}
					// This is commented out to handle the TAD case.
					// Dynamic usecase switch on TV due to playback finished.
					// In this case if we unregister here, mainwatch removed will not be
					// notified to StreamingService. Thus causing release of TAD resources not being done.
					//playtvmpl.registerPlayBackListener(null, TAG);
				}
				break;
			case BcstConstants.RECORD_PLAY_SYSTEM_ERROR:
			    Log.e(TAG, "Playback error stoping playback" + status);
				onPlayError(ITvAbstractPlaybackListener.PLAYERROR_SYSTEM, 0, 0);
			    stop();
			    break;
			case BcstConstants.RECORD_PLAY_ERROR_HDDNOTCONNECTED:
				onPlayError(ITvAbstractPlaybackListener.PLAYERROR_HDD,0,0);
				stop();
				break;				
			default:
				Log.e(TAG, "tvserver status unexpected " + status);
				break;
			}
		}
	  }

	public PvrPlayback(Context context, PlayTVFacMediaPlayer mpl) {
		Log.d(TAG, "constructor " + mpl);
		synchronized(this) {
			playtvmpl = mpl;
		}
		mContext = context;
		mTimeUpdateHandler = new Handler();
		mPlayHandler = new Handler();
		Pvrlistener = new PvrPlaybackListenerClass();
		mediacontrollistener = new PvrMediaControlListenerClass();
		mCachedRecId = -1;
		mPlaybackListener = new ArrayList<ITvAbstractPlaybackListener>();
		mPlayTvStateChangeListener = new PlaytvStateChangeCallbacks();
	}

	@Override
	public void setPlayer(PlayTVFacMediaPlayer mpl) {
		Log.d(TAG, "set Player " + mpl);
		playtvmpl = mpl;
	}

	@Override
	public void playCatchUpChannel(Uri uri,Medium medium, Map<String,String> headers) {
		Log.d(TAG, "playCatchUpChannel "+uri);
		int recId	  = Integer.parseInt(uri.getLastPathSegment());	
		try {
			headers.put(TvHeaders.CI_CAM, cicamId);
			playtvmpl.PlayCatchUpRecording(uri, recId, headers);
		} catch (Exception e) {
			Log.d(TAG, "playCatchUpChannel failed "+e.toString());
			onPlayFailed(uri, Medium.MEDIUM_PVRFILE, -1, ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
		}
	}

	@Override
	public void play(Uri uri, Medium medium, Map<String,String> headers) {
		boolean minimumDataAvailble = true;
		int isPartial = 0;
		int recId	  = Integer.parseInt(uri.getLastPathSegment());
		//RecordingError recError = RecordingError.REC_ERROR_NONE;
		Log.d(TAG, "play called");
		if (!tvserverPlayTriggered) {
			mSeekPending 		= false;
			mCurrentDirection 	= BcstConstants.DIRECTION_FORWARD;
			seekAfterPlayable	= -1;
			isSpinnerSet 		= false;
			mCurrentSpeed 		= 1;
			mPendingUserAction 	= ACTION_NONE;
			stopReason 			= stopReasonDef.REASON_NONE;
			playrecordingId 	= recId;
			trickmodeStatus		= true;
			String[] proj = { IRecordingsContract.C_PROGRAM_NUMBER,
					IRecordingsContract.C_CICAMID,
					IRecordingsContract.C_RESUME_INFO,
					IRecordingsContract.C_RECORDING_TYPE,
					IRecordingsContract.C_IS_PARTIAL,
					IRecordingsContract.C_RECORDING_ERROR};

			String where = IRecordingsContract.C_RECORDING_ID + "=?";
			String[] whereArgs = { Integer.toString(recId) };

			Cursor c = mContext.getContentResolver().query(
					IRecordingsContract.CONTENT_URI_Recordings, proj, where,
					whereArgs, null);

			if ((c != null) && (c.getCount() > 0) && (c.moveToFirst())) {
				cicamId = String.valueOf(c.getInt(1));
				resumeInfo = c.getInt(2);
				Log.d(TAG,"id: " + playrecordingId +" Pgm number -> : " + programNumber + " cam id : " + cicamId
						+ " ResumeInfo " +resumeInfo);
				isPartial = c.getInt(4);
				//recError = RecordingError.valueOf(Integer.toString(c.getInt(5)));
				// Check if minimum data is available for ongoing recordings
				if ((c.getInt(3) == IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal()) &&
						(c.getInt(4) == 0)) {
					minimumDataAvailble = false;
				}
				c.close();

				if (minimumDataAvailble) {
					if(isPartial == 1) {
	/*					if(recError == RecordingError.REC_ERROR_DISKFULL){

						}*/
						/*********** TODO: TIF: Need to notify PlaytvApp about this event ***************/
						//RecPlayKeyHandler.getInstance().onKeyDown(SystemEvents.PARTIAL_RECORDING, null);
					}
					try {
						playtvmpl.getMediaPlayerInstance().setOnSeekCompleteListener(this);
						//recordinstance = playtvmpl.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaRecordControl();
						//recordinstance.registerListenerCallback(Pvrlistener);
						//controlinstance = playtvmpl.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaControl();
						//controlinstance.registerListenerCallback(mediacontrollistener);
						playtvmpl.registerPlayBackListener(mPlayTvStateChangeListener, TAG);
						headers.put(TvHeaders.CI_CAM, cicamId);
						playtvmpl.PlayRecording(playrecordingId, headers);
					} catch (Exception e) {
						Log.e(TAG, "error in using tvmpl " + e.toString());
					}
				} else {
					onPlayFailed(mUri, Medium.MEDIUM_PVRFILE, -1, ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE);
					Log.d(TAG, "Plaback Failed: Minimum data not available");
				}
			} else {
				Log.e(TAG, "cursor not ok for pvr playback");
			}
		} else {
			Log.d(TAG, "Playback already in progress hence caching and stopping playback");
			mCachedUri 		= uri;
			mCachedMedium 	= medium;
			mCachedHeaders 	= headers;
			mCachedRecId 	= recId;
			stop();
		}
	}

	@Override
	public void stop() {
		 Log.d(TAG, "stop  playback");
		 mUserActionRunnable = new UserActionRunnable(ACTION_STOP);
	     	 mPlayHandler.post(mUserActionRunnable);
	}

	@Override
	public boolean pause() {
		Log.d(TAG, "pause  playback");

		mUserActionRunnable = new UserActionRunnable(ACTION_PAUSE);
         	mPlayHandler.post(mUserActionRunnable);
		return true;
	}
	@Override
	public void resume() {
		Log.d(TAG, "resume  playback");
		mUserActionRunnable = new UserActionRunnable(ACTION_RESUME);
	    	mPlayHandler.post(mUserActionRunnable);

	}

	@Override
	public void seekTo(int msecs) {
		Log.d(TAG, "seekto  playback " + msecs/ONE_SECOND);
		mUserActionRunnable = new UserActionRunnable(ACTION_SEEKTO, msecs/ONE_SECOND);
	    	mPlayHandler.post(mUserActionRunnable);
	}

	@Override
	public void setSpeed(int speed, boolean forward) {
		Log.d(TAG, "setspeed playback speed request from the UI with "+speed +" forward "+forward);
		mUserActionRunnable = new UserActionRunnable(ACTION_SETSPEED, speed, forward ? BcstConstants.DIRECTION_FORWARD : BcstConstants.DIRECTION_BACKWARD);
		mPlayHandler.post(mUserActionRunnable);
	}

	public void onLockStatusChanged(int type, int status) {
		Log.i(TAG,"onLockStatusChanged ");
		onLockStatusChangedNotify(type, status);
	}
	private class UserActionRunnable implements Runnable {

	  int userActionRequested;
	  int userSpeed, userSeekTime;
	  int userDirection =  BcstConstants.DIRECTION_FORWARD;

	  UserActionRunnable(int action) {
	    	userActionRequested = action;
	  }

	  UserActionRunnable(int action, int seekTime) {
		userActionRequested = ACTION_SEEKTO;
		userSeekTime = seekTime;
		userDirection = (seekTime > currentTime) ? BcstConstants.DIRECTION_FORWARD : BcstConstants.DIRECTION_BACKWARD;
	  }

	  UserActionRunnable(int action, int param1, int direction) {
	  	userActionRequested = action;
	  	if(action == ACTION_SETSPEED) {
			userSpeed = param1;
	  	} else if(action == ACTION_NOTPLAYABLE) {
	  		userSeekTime = param1;
	  	}
		   userDirection = direction;
	  }

	  public void  run() {
		    Log.d(TAG, "running the UserActionRunnable with seek pending status as "+ mSeekPending);
		    mPlayHandler.removeCallbacks(mNextSeekRunnable);
		    /* Condition (userActionRequested == ACTION_STOP) is added below
			   to honor stop request even if there is a pending seek */
			if(!mSeekPending || (userActionRequested == ACTION_STOP)) {
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
				   if ( (stopReason == stopReasonDef.REASON_ERROR) || (stopReason == stopReasonDef.REASON_NONE) ) {
				    	   try {
						   mTimeUpdateHandler.removeCallbacks(mTimeUpdate);
				    		   playtvmpl.getMediaPlayerInstance().stop();
				    	   } catch (Exception e) {
				    		   Log.e(TAG, "error while stopping mediaplayer " + e.toString());
				    	   }
				    	   try {
				    		   stopReason = stopReasonDef.REASON_STOP;
				    		   /*Note: getRecordingInfo should be called always before calling stopRecordPlayback */
				    		   getRecordingInfo();
				    		   recordinstance.stopRecordPlayback();
				    		   tvserverPlayTriggered = false;
				    	   } catch (Exception e) {
				    		   Log.e(TAG, "error while stop to middleware " + e.toString());
				    	   }
				   }
			    	   break;
			       case ACTION_SEEKTO:
				   	Log.d(TAG, "running the UserActionRunnable ACTION_SEEK_TO ");
				   	mCurrentSpeed = 1;
					if(userSeekTime < totalTime) {
				   		CheckForPlayable(userSeekTime, userDirection);
					} else {
						onPlayFinished(Medium.MEDIUM_PVRFILE, -1);
					}
		    	    break;
			       case ACTION_RESUME:
					Log.d(TAG, "running the UserActionRunnable ACTION_RESUME");
					try {
						playtvmpl.getMediaPlayerInstance().start();
					   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
					   onPlayStateChanged(PlaybackState);
					} catch (Exception e) {
			    		   Log.e(TAG, "error while resume " + e.toString());
			    	   	}
			    	   	break;
			       case  ACTION_SETSPEED:
					Log.d(TAG, "running the UserActionRunnable ACTION_SET_SPEED");
					mCurrentSpeed = userSpeed;
					mCurrentDirection = userDirection;
					if(mCurrentSpeed == 1) {
						try {
							playtvmpl.getMediaPlayerInstance().start();
						   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
						   onPlayStateChanged(PlaybackState);
						} catch (Exception e) {
			    		   		Log.e(TAG, "error while resume for speed 1 : " + e.toString());
			    	   	}
					} else {
						try {
			    		   		playtvmpl.getMediaPlayerInstance().pause();
							   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY;
							   onPlayStateChanged(PlaybackState);
				    	   	} catch (Exception e) {
				    		   Log.e(TAG, "error while pause for set speed" + e.toString());
				    	   	}
					  	int val = calcNextJump(mCurrentSpeed, mCurrentDirection);
						Log.d(TAG, "calcNextJump "+val);
						if( (val >= 0) && (val < totalTime) ) {
							mTrickStartTime = System.currentTimeMillis();
							mTrickStartPos = currentTime;
							Log.d(TAG, "start trick " + mTrickStartTime + ", " + mTrickStartPos);
					   		CheckForPlayable(val, mCurrentDirection);
						} else if(val > totalTime) {
							onPlayFinished(Medium.MEDIUM_PVRFILE, -1);
						} else {
							mUserActionRunnable = new UserActionRunnable(ACTION_PLAYFROMSTART);
							mPlayHandler.post(mUserActionRunnable);
						}
					}
					break;
				case ACTION_PLAYFROMSTART:
					Log.d(TAG, "running the UserActionRunnable ACTION_PLAYFROMSTART ");
					mCurrentSpeed = 1;
					mCurrentDirection = BcstConstants.DIRECTION_FORWARD;
					PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
					onPlayStateChanged(PlaybackState);
					CheckForPlayable(0, mCurrentDirection);
					mPendingUserAction = ACTION_RESUME;
					break;
				case ACTION_NOTPLAYABLE:
					HandleNotPlayable(userSeekTime, userDirection);
					break;
				}
				} else {
		    		if(userActionRequested == ACTION_NOTPLAYABLE) {
					Log.d(TAG, "ignoring not playable while we are seeking..");
		    		} else {
			  		Log.d(TAG, "storing as pending.. " + userActionRequested + " userDirection " + userDirection + " userSpeed " + userSpeed + " userSeekTime " + userSeekTime);
	    	  			mPendingUserAction = userActionRequested;
              			mCurrentSpeed = userSpeed;
              			mCurrentDirection = userDirection;
              			mPendingUserSeekTime = userSeekTime;
				}
		    }
	    }
    }

    private class NextSeekRunnable implements Runnable {
		public void run() {
			Log.d(TAG, "next seek " + mTrickNextPos);
			CheckForPlayable(mTrickNextPos, mCurrentDirection);
		}
    }

    private void continueTrickJump() {
		int val = calcNextJump(mCurrentSpeed, mCurrentDirection);
		Log.d(TAG, "continueTrickJump "+ val);
		if( (val >= 0) && (val <= totalTime) ) {
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
		} else if(val > totalTime) {
			onPlayFinished(Medium.MEDIUM_PVRFILE, -1);
		} else {
			mUserActionRunnable = new UserActionRunnable(ACTION_PLAYFROMSTART);
			mPlayHandler.post(mUserActionRunnable);
		}
    }

   private class SeekDoneRunnable implements Runnable {
	  public void run() {
		Log.d(TAG, "running SeekDoneRunnable");
		mPlayHandler.removeCallbacks(mNextSeekRunnable);
		mSeekPending = false;
	    	switch(mPendingUserAction) {
	       case ACTION_NONE:
			Log.d(TAG, "running SeekDoneRunnable ACTION_NONE");
	            	mPendingUserAction = ACTION_NONE;
			if(isFirstTimeCheck) {
				// Initialise URI before the first playtime change
				// and send contentstatus change notification.
				// This is necessary for MRC streaming to work properly
				if (recordinstance != null) {
					recordinstance.initContentStatus();
				}
				synchronized (mPlaybackListener) {
					for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
						listener.onPlayCompleted(mUri, mHeaders, Medium.MEDIUM_PVRFILE, -1);
					}
				}
				setMute(false);
				isFirstTimeCheck = false;
			} else if(mCurrentSpeed != 1) {
				continueTrickJump();
			}else {
				onSeekCompleteNotify();
				if(!isPlaying()) {
					playtvmpl.getMediaPlayerInstance().start();
				}
			   // We are notifying playing here, to handle case where 
			   // seek is done in pause state.
			   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
			   onPlayStateChanged(PlaybackState);
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

	       case  ACTION_STOP:
		   Log.d(TAG, "running SeekDoneRunnable ACTION_STOP");
	    	   mPendingUserAction = ACTION_NONE;
	    	   mCurrentSpeed = 1;
	    	   Log.d(TAG, "STOP playback Called!!!");
		   if ( (stopReason == stopReasonDef.REASON_ERROR) || (stopReason == stopReasonDef.REASON_NONE) ) {
				try {
					mTimeUpdateHandler.removeCallbacks(mTimeUpdate);
					playtvmpl.getMediaPlayerInstance().stop();

					stopReason = stopReasonDef.REASON_STOP;
					/*Note: getRecordingInfo should be called always before calling stopRecordPlayback */
					getRecordingInfo();
					recordinstance.stopRecordPlayback();
					tvserverPlayTriggered = false;
				} catch (Exception e) {
					Log.e(TAG, "error while stop SeekDoneRunnable" + e.toString());
				}
		   }
		   break;

	       case  ACTION_RESUME:

	    	   Log.d(TAG, "running SeekDoneRunnable ACTION_RESUME");
	    	   mCurrentSpeed = 1;
	    	   mPendingUserAction = ACTION_NONE;
			try {
				playtvmpl.getMediaPlayerInstance().start();
			   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
			   onPlayStateChanged(PlaybackState);
			} catch (Exception e) {
				Log.e(TAG, "error while resume-1" + e.toString());
			}
	    		break;
	       case ACTION_SEEKTO:
			Log.d(TAG, "running SeekDoneRunnable ACTION_SEEKTO");
			mPendingUserAction = ACTION_NONE;
	         	mCurrentSpeed = 1;
			if(mPendingUserSeekTime < totalTime) {
				CheckForPlayable(mPendingUserSeekTime, mCurrentDirection);
			} else {
				onPlayFinished(Medium.MEDIUM_PVRFILE, -1);
			}
			break;
	       case ACTION_SETSPEED:
			Log.d(TAG, "running SeekDoneRunnable ACTION_SETSPEED");
			mPendingUserAction = ACTION_NONE;
			Log.d(TAG, "seek to has called......to media player  SeekDone ACTION_SETSPEED");
			if(mCurrentSpeed == 1) {
				try {
					playtvmpl.getMediaPlayerInstance().start();
				   PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
				   onPlayStateChanged(PlaybackState);
				} catch (Exception e) {
			    		Log.e(TAG, "error while resume for speed1 " + e.toString());
			    	}
			} else {
				int val = calcNextJump(mCurrentSpeed, mCurrentDirection);
				if( (val >= 0) && (val < totalTime) ) {
					mTrickStartTime = System.currentTimeMillis();
					mTrickStartPos = currentTime;
					Log.d(TAG, "change trick " + mTrickStartTime + ", " + mTrickStartPos);
					CheckForPlayable(val, mCurrentDirection);
				} else if(val > totalTime) {
					onPlayFinished(Medium.MEDIUM_PVRFILE, -1);
				} else {
					mUserActionRunnable = new UserActionRunnable(ACTION_PLAYFROMSTART);
					mPlayHandler.post(mUserActionRunnable);
				}
			}
			break;
		case ACTION_NOTPLAYABLE:
			Log.d(TAG, "running SeekDoneRunnable ACTION_NOTPLAYABLE");
			mPendingUserAction = ACTION_NONE;
			HandleNotPlayable(mPendingUserSeekTime, mCurrentDirection);
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

	public void onPlayStarted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber) {
		Log.d(TAG, "onPlayStarted " );
		mUri 		= uri;
		mHeaders	= headers;
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onPlayStarted(uri, headers, medium, presetNumber);
			}
		}
	}

	public void onPlayCompleted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber) {
		Log.d(TAG, "onPlayCompleted " + resumeInfo);
		mUri 		= uri;
		mHeaders 	= headers;
		boolean catchUpTune = false;
		
		if (headers != null) {
			String privData = headers.get(ITVSessionContext.KEY_PRIVATE_DATA_COOKIE);
			if ((privData != null) && (privData.equals(TvHeaders.PRIV_DATA_CATCHUP_TUNE))) {
				catchUpTune = true;
			}
		}
		
		if (catchUpTune) {
			synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayCompleted(mUri, mHeaders, Medium.MEDIUM_PVRFILE, -1);
				}
			}
			onPlayStateChanged(PlaybackState);
		} else {
			try{
				recordinstance = playtvmpl.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaRecordControl();
				recordinstance.registerListenerCallback(Pvrlistener);
				controlinstance = playtvmpl.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaControl();
				controlinstance.registerListenerCallback(mediacontrollistener);
				PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING;
			}catch(Exception e){
				Log.d(TAG, "onPlayCompleted " + e.getMessage());
			}
			/*synchronized (mPlaybackListener) {
				for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
					listener.onPlayCompleted(uri, Medium.MEDIUM_PVRFILE, -1);
				}
			}*/
			try {
				if(PlayTvHDDUtils.getInstance(mContext).getMountPath() != null) {
					setMute(true);
					long deviceIdentifier = PlayTvHDDUtils.getInstance(mContext).getDeviceId();
					String deviceId = Long.toString(deviceIdentifier);
					/*recordinstance.startRecordPlayback(programNumber, cicamId,
							PlayTvHDDUtils.getInstance(mContext).getMountPath(), playrecordingId);*/
					recordinstance.startRecordPlayback(programNumber, cicamId,
							PlayTvHDDUtils.getInstance(mContext).getMountPath(), playrecordingId, deviceId);
					tvserverPlayTriggered = true;
				}
			} catch(Exception e) {
				Log.e(TAG, "error on play completed " + e.toString());
			}
		}
	}

	public void onPlayFinished(Medium medium, int presetNumber) {
	Log.d(TAG, "onPlayFinished " );
		PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onPlayFinished(mUri, Medium.MEDIUM_PVRFILE, -1);
			}
		}
		try {
			mTimeUpdateHandler.removeCallbacks(mTimeUpdate);
			stopReason = stopReasonDef.REASON_FINISHED;
			/*Note: getRecordingInfo should be called always before calling stopRecordPlayback */
			getRecordingInfo();
			recordinstance.stopRecordPlayback();
			tvserverPlayTriggered = false;
		} catch(Exception e) {
			Log.e(TAG, "error on play finished " + e.toString());
		}
	}

	public void onPlayFailed(Uri uri, Medium medium, int presetNumber, int reason) {
	Log.e(TAG, "onPlayFailed ");
		PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
		onPlayStateChanged(PlaybackState);
		try {
			if(tvserverPlayTriggered) {
				mTimeUpdateHandler.removeCallbacks(mTimeUpdate);
				stopReason = stopReasonDef.REASON_ERROR;
				/*Note: getRecordingInfo should be called always before calling stopRecordPlayback */
				getRecordingInfo();
				recordinstance.stopRecordPlayback();
				tvserverPlayTriggered = false;
			}
		} catch(Exception e) {
			Log.e(TAG, "error on release " + e.toString());
		}
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onPlayFailed(uri, Medium.MEDIUM_PVRFILE, -1, reason);
			}
		}
	}

	public boolean onError(PlayTvMediaPlayer mpl, int what , int extra) {
		PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
		onPlayStateChanged(PlaybackState);
		if((what == MediaPlayer.MEDIA_ERROR_UNKNOWN) && ( extra == MediaPlayer.MEDIA_ERROR_IO))
		{
			Log.e(TAG, " Onerror due to read/write error ");
			onPlayError(ITvAbstractPlaybackListener.PLAYERROR_HDD, what, extra);
		}
		else
		{
			Log.e(TAG, " Onerror due to system error ");
			if((what == -1) && (extra == -1)) {
				onPlayError(ITvAbstractPlaybackListener.PLAYERROR_FACTORY, what, extra);
			}else {
				onPlayError(ITvAbstractPlaybackListener.PLAYERROR_SYSTEM, what, extra);
			}
		}
		release();
		return false;
	}

	@Override
	public void release() {
		Log.d(TAG, "release called");
		PlaybackState = ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED;
		onPlayStateChanged(PlaybackState);
		try {
			if(tvserverPlayTriggered) {
				setMute(false);
				mTimeUpdateHandler.removeCallbacks(mTimeUpdate);
				stopReason = stopReasonDef.REASON_STOP;
				/*Note: getRecordingInfo should be called always before calling stopRecordPlayback */
				getRecordingInfo();
				recordinstance.stopRecordPlayback();
				tvserverPlayTriggered = false;
			}
		} catch(Exception e) {
			Log.e(TAG, "error on release " + e.toString());
		}
	}

	@Override
	public void onSeekComplete(MediaPlayer mp) {
		Log.d(TAG,"onSeekComplete sending STATE_PREPARE_COMPLETE state changed on seek completion");
		synchronized(this) {
			if(stopReason == stopReasonDef.REASON_NONE) {
				currentTime = (playtvmpl.getMediaPlayerInstance().getCurrentPosition() / ONE_SECOND);
			}
		}
		mSeekCompletedRunnable = new SeekDoneRunnable();
		mPlayHandler.post(mSeekCompletedRunnable);
	}

	@Override
	public int getCurrentDuration() {
		return currentTime * ONE_SECOND;
	}

	@Override
	public int getTotalDuration() {
		return totalTime * ONE_SECOND;
	}

	@Override
	public boolean isPlaying() {
		if(stopReason == stopReasonDef.REASON_NONE) {
			if((playtvmpl != null) && (tvserverPlayTriggered)) {
				return playtvmpl.getMediaPlayerInstance().isPlaying();
			}
		}
		return false;
	}


	@Override
	public Medium getMedium() {
		if(playtvmpl != null) {
			return playtvmpl.getCurrentMedium();
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
	public boolean getTrickmodeStatus() {
		return trickmodeStatus;
	}

	private void jumpTo(int seekTime) {
		try {
			mSeekPending = true;
			playtvmpl.getMediaPlayerInstance().seekTo(seekTime * ONE_SECOND);
	    } catch (Exception e) {
	    	Log.e(TAG, "error while seek in jump play " + e.toString());
   	    }
	}

	public void CheckForPlayable(int starttime,int direction) {
		Log.d(TAG,"CheckForPlayable starttime " + starttime + " direction " + direction);

              if(tvserverPlayTriggered){
            		if(starttime < 0)
              			starttime = 0;
        		int status = -1;
        		status = recordinstance.checkIfPlayable(starttime);

        		if(status == BcstConstants.PLAYABLE)
        		{
        			  Log.d(TAG,"status BcstConstants.PLAYABLE");
        			  jumpTo(starttime);
        		}
        		else if(status == BcstConstants.NOT_PLAYABLE)
        		{
        			Log.d(TAG,"status BcstConstants.NOT_PLAYABLE");
        			mUserActionRunnable = new UserActionRunnable(ACTION_NOTPLAYABLE, starttime, mCurrentDirection);
        			mPlayHandler.post(mUserActionRunnable);
        		}
        		else if(status == BcstConstants.CHECKING_CICAM)
        		{
        			Log.d(TAG,"status BcstConstants.CHECKING_CICAM");
        			if(!isSpinnerSet) {
                     	isSpinnerSet = true;
        				onLicenseExchangeHappening(true);
        			}
        			seekAfterPlayable = starttime;
        		}
		}
		else{
		    Log.d(TAG,"Playback not triggred, so skiping check for playable");
		}
	}

public void HandleNotPlayable(int starttime,int direction) {
    Log.d(TAG,"HandleNotPlayable starttime " + starttime + " direction " + direction +
    " isSpinnerSet " + isSpinnerSet);

    if(tvserverPlayTriggered){
        if(starttime < 0)
            starttime = 0;

        PlayableData  mData = recordinstance.getNextPlayableChunk(starttime,direction);
        Log.d(TAG,"Playable data received - "+mData.status + ", " + mData.startTime + ", " + mData.endTime);
        if(mData.status == BcstConstants.PLAYABLE) {
            if(isSpinnerSet) {
                isSpinnerSet = false;
                onLicenseExchangeHappening(false);
            }
            if(mData.startTime < totalTime) {
                 jumpTo(mData.startTime);
            } else {
                stop();
            }
        }
        else if(mData.status == BcstConstants.NOT_PLAYABLE)
        {
            if(isSpinnerSet)
            {
                isSpinnerSet = false;
                onLicenseExchangeHappening(false);   //Need to add this constant in Bcst constants
            }
            if(direction == BcstConstants.DIRECTION_FORWARD) {
                Log.d(TAG, "finishing playback as nothing to play");
                onPlayFinished(Medium.MEDIUM_PVRFILE, -1);
                // Mark the recording as expired, if no playable block is available
                if (starttime == 0) {
                    try {
                        InvalidateRecording(playrecordingId);
                    } catch (Exception e) {
                        Log.d(TAG, "Exception in inValidateRecording(): " + e.toString());
                    }
                }
            } else {
                mUserActionRunnable = new UserActionRunnable(ACTION_PLAYFROMSTART);
                mPlayHandler.post(mUserActionRunnable);
            }
        }
        else if (mData.status == BcstConstants.CHECKING_CICAM)
        {
            seekAfterPlayable = mData.startTime;
            if(!isSpinnerSet)
            {
                isSpinnerSet = true;
                onLicenseExchangeHappening(true);      //Need to add this in bcst constants
            }
        }
    }	else{
    Log.d(TAG,"Playbck not triggered, skip get next playable chunk");
    }
}

	private void InvalidateRecording (int recId)
	{
		ContentProviderClient cp = mContext.getContentResolver().acquireContentProviderClient(IRecordingsContract.CONTENT_URI_Recordings);
		String selection = IRecordingsContract.C_RECORDING_TYPE+" != ? AND "+IRecordingsContract.C_RECORDING_ID+" = ?";
		String[] selectionArgs = new String[] {	""+IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal(),
												""+recId};
		ContentValues values = new ContentValues();
		int count = 0;

		try {
			values.put(IRecordingsContract.C_RECORDING_TYPE, IRecordingsContract.RecordingType.RECORDING_EXPIRED.ordinal());
			count = cp.update(IRecordingsContract.CONTENT_URI_Recordings, values, selection, selectionArgs);
		} catch (Exception e) {
			Log.d(TAG, "inValidateRecording: Exception in update: "+e.toString());
		}

		if (count > 0) {
			Log.d(TAG, "Successfully invalidated Recording with RecordingId "+recId);
		} else {
			Log.d(TAG, "Recording invalidation failed for RecordingId "+recId);
		}
	}

	 private void getRecordingInfo() {
   		long deviceIdentifier = PlayTvHDDUtils.getInstance(mContext).getDeviceId();
    		String deviceId = Long.toString(deviceIdentifier);
    		if (recordinstance != null) {
    		    mRecordingInfo = recordinstance.getRecordingInfo(playrecordingId, PlayTvHDDUtils.getInstance(mContext).getMountPath(), deviceId);
    		 }
	 }

	public void setMute (boolean state) {
		if (controlinstance != null) {
			controlinstance.setMediaMute( ITvMediaControl.MEDIA_VIDEO, state);
			controlinstance.setMediaMute( ITvMediaControl.MEDIA_AUDIO, state);
		} else {
			Log.d(TAG, "setMute FAILED !!!");
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

	@Override
	public int getPlaybackState() {
		return PlaybackState;
	}

	public void onLicenseExchangeHappening(boolean status) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onLicenseExchangeHappening(status);
			}
		}
	}

	public void onSeekCompleteNotify() {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onSeekComplete(ITvAbstractPlaybackListener.MODE_PVR);
			}
		}
	}

	public void onPlayError(int error, int what, int extra) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onPlayError(error, what, extra, ITvAbstractPlaybackListener.MODE_PVR);
			}
		}
	}

	public void onServiceTypeDetected(int type) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onServiceTypeDetected(type);
			}
		}
	}

	public void onTrickModeEnabled(boolean status) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onTrickModeEnabled(status, ITvAbstractPlaybackListener.MODE_PVR);
			}
		}
	}

	public void onPlayStateChanged(int state) {
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onPlayStateChanged(state, ITvAbstractPlaybackListener.MODE_PVR);
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
		if ((playtvmpl != null) && ((playtvmpl.getCurrentPurpose() & releaseCriterion) == 0)) {
			release();
		}
	
		synchronized (mPlaybackListener) {
			for(ITvAbstractPlaybackListener listener:mPlaybackListener) {
				listener.onMPLPurposeChanged(purpose);
			}
		}
	}

	public class PlaytvStateChangeCallbacks implements IPlayTvStateChangeListener {
		@Override
		public void onPlayStarted(Uri mediaPlayerUri,  Map<String,String> headers, Medium medium, int presetNumber) {
			PvrPlayback.this.onPlayStarted(mediaPlayerUri, headers, medium, presetNumber);
		}

		@Override
		public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber) {
			PvrPlayback.this.onPlayCompleted(mediaPlayerUri, headers, medium, presetNumber);
		}

		@Override
		public void onPlayFinished(Uri mediaPlayerUri, Medium medium, int presetNumber) {
			PvrPlayback.this.onPlayFinished(medium, presetNumber);
		}

		@Override
		public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
			PvrPlayback.this.onPlayFailed(mediaPlayerUri, medium, presetNumber, reason);
		}

		@Override
		public void onInfo(boolean cicamAvailable) {
			PvrPlayback.this.onInfo(cicamAvailable);
		}

		@Override
		public void onError(PlayTvMediaPlayer mpl, int what , int extra) {
			PvrPlayback.this.onError(mpl, what, extra);
		}

		@Override
		public void onLockStatusChanged(int type, int status) {
			PvrPlayback.this.onLockStatusChanged(type, status);
		}

		@Override
		public void onPurposeChanged(int purpose) {
			PvrPlayback.this.onMPLPurposeChanged(purpose);
		}

		@Override
		public void onUriChanged(Uri mediaPlayerUri) {
			// Deprecated method
		}

		@Override
		public void onCamUpgradeStarted(boolean status) {
		}
	}
}
