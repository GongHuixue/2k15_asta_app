package org.droidtv.tunerservice.recording;

import org.droidtv.tunerservice.interfaces.IHDDListener;
import org.droidtv.tunerservice.interfaces.ITSRecording;
import org.droidtv.tunerservice.interfaces.IPlayTvMPLFactoryCallback;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;

import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.PlayTvHDDUtils;
import org.droidtv.tunerservice.epgnownext.EpgCache;
import org.droidtv.tunerservice.epgnownext.IEpgProviderNotify;
import org.droidtv.tunerservice.epgnownext.EpgNowNextData;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tv.media.BcstConstants;
import org.droidtv.tv.media.ITvMediaRecordControl;
import org.droidtv.tv.media.ITvMediaRecordControl.IonTvRecordControlCallback;
import org.droidtv.tv.media.ITvMediaRecordControl.RecordingInfo;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.media.ITvMediaRecordControl.PlaybackEitInfo;
import org.droidtv.tv.tvinput.ITVSessionContext;

import org.droidtv.tunerservice.playback.TvChannelPlayback;
import org.droidtv.tunerservice.recording.RecService;

import android.content.Context;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;
import 	java.lang.Math;
import java.util.Map;

/**
* @author mukta.singhal
*
*/
public class TimeshiftRecording implements ITvAbstractPlaybackListener, IPlayTvMPLFactoryCallback, IHDDListener {
  public static final String TAG ="TSRecording";


private TvChannelPlayback tvChannelPlayback;
private TvMediaPlayer tvmplayer = null;
  private ITvMediaRecordControl recordinstance =  null;
  Context mContext;
  private PlayTVMediaPlayerFactory factory = null;
  private PlayTVFacMediaPlayer playtvmplayerforTS = null;
  private TSRecordingListenerClass TSRecordingListener = null;
  private Handler mHandler;
  private long mDuration;
  private long  zappedTime = 0;
  private int  mpresetNumber = 0;
  private int lastQueriedPreset = 0;
  private boolean lastPresetAnalog = false;
  private ITSRecording listener = null;
  private static final long TIME_SHIFT_REC_FORMAT_MIN_SIZE = 34359738368L;//32 GB (32*1024*1024*1024)
  private int mTimeshiftError = 0;
  private PowerOnSyncRunnable powerOnSyncRunnable;
  private EpgNowNextData mCurrentNowNextData = null;
  private int mServiceType = -1;
  private EpgCache mEpgCache = null;
  private int mUniqueId = -1;
  private int mEpgNowDataVersion = -2;
  public PlaybackEitInfo mEitInfo = null;
  private boolean selectionComplete = false;
  private static final int ONE_SECOND = 1000;
  
  private enum TSStateDef {
		STATE_IDLE(0),
		STATE_STARTING(1),
		STATE_RUNNING(2),
		STATE_RELEASING(3);
		private int state;
		private TSStateDef(int newstate) {
			state = newstate;
		}
  }

  public TSStateDef tsState = TSStateDef.STATE_IDLE;
  private String mountedPath = null;
  public boolean mMinimumDataAvailable = false;
  private long mRecordedDuration = 0;
  private Medium mMedium = Medium.MEDIUM_INVALID;

  public static final int PAUSE_ALLOWED   = 0;
  public static final int IN_TRANSIENT = 5;
  public static final int HDD_NOT_CONNECTED = 1;
  //public static final int NO_PAIRED_HDD	= 3;
  public static final int ANALOG_CHANNEL = 3;
  public static final int X_RATED_CONTENT = 4;

  //class constructor
  public TimeshiftRecording(Context context, TvChannelPlayback playback) {

	mContext = context;
	Log.d(TAG," TimeshiftRecording class created ");
	this.tvChannelPlayback = playback;
	factory = PlayTVMediaPlayerFactory.getInstance();
	factory.registerListener(PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT, this);
	PlayTvHDDUtils.getInstance(mContext).addHDDListener(this, TAG);
	mountedPath = PlayTvHDDUtils.getInstance(mContext).getMountPath();
	getMediaPlayer();
	TSRecordingListener =  new TSRecordingListenerClass();
	playback.registerListener(this);	
	mHandler = new Handler();
	mDuration = getTSDuration();
	powerOnSyncRunnable = new PowerOnSyncRunnable();
	mEpgCache = new EpgCache(mContext);
	mEitInfo = new PlaybackEitInfo();
  }
  public void acquire() {
  	Log.d(TAG, "Timeshift Recording acquire");
  	getMediaPlayer();
  }

  public void registerClient(ITSRecording callback) {
  	listener = callback;
  }

  private void getMediaPlayer() {
	  Log.d(TAG," In getMediaPlayer");
	  if(factory.IsMediaPlayerAvailable(mContext, PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT, mMedium, mpresetNumber)
			  == PlayTVMediaPlayerFactory.STATUS_AVAILABLE) {
		  playtvmplayerforTS = factory.getMPLInstance(mContext, PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT,mMedium, mpresetNumber);
		  try {
			  tvmplayer = playtvmplayerforTS.getMediaPlayerInstance();
			  //factory.registerListener(PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT, this);
		  } catch (Exception e){
			  Log.e(TAG, "exception while get media player " + e.getLocalizedMessage() );
			  Log.e(TAG, "playtvmpl " + playtvmplayerforTS + " ,tvmplayer " + tvmplayer + " ,record " + recordinstance);
			  releaseMediaPlayer();
		  }
	  } else {
		  if(playtvmplayerforTS!=null){
			  releaseMediaPlayer();
		  }
	  }
  }

  private void releaseMediaPlayer() {
    Log.d(TAG," In releaseMediaPlayer");
    if(recordinstance != null) {
      try {
		recordinstance.unregisterListenerCallback(TSRecordingListener);
	  } catch (Exception e) {
	  }
      recordinstance = null;
    }
    if(playtvmplayerforTS != null) {
      factory.releaseMPLInstance(PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT, playtvmplayerforTS);
    }
    playtvmplayerforTS = null;
    tvmplayer = null;
  }

  public void startTimeShiftRecording(int presetNumber)
  {
    Log.d(TAG,"startTimeShiftRecording for preset ->" + presetNumber);

    if(null == mountedPath) {
      Log.d(TAG, "HDD is not connected..hence no TS");
      return;
    }
    if(mServiceType == TvHeaders.MODE_ANALOG) {
      Log.d(TAG, "channel not digital..hence no TS");
	  return;
    }

    if(tsState == TSStateDef.STATE_IDLE)
    {
      String path = mountedPath + "/timeshift/timeshift.tsc";
      if(tvmplayer!=null){
      		recordinstance = tvmplayer.getTvMediaPlayerContext().getTvMediaRecordControl();
		Log.d(TAG," recordinstance: "+recordinstance +" path: ->  " + path);

      		if(recordinstance != null)
      		{
	    		if(true == recordinstance.isRecordingAllowed())
			{
			     	/*Reset timeshift error*/
    			    	mTimeshiftError = 0;
				recordinstance.registerListenerCallback(TSRecordingListener);
				Log.d(TAG," Going to start the Time Shift ** mDuration:"+mDuration);
				zappedTime = System.currentTimeMillis()/1000;
				if (RecService.getInstance() != null) {
					int recPowerState = RecService.getInstance().getPowerOnSyncState();
					Log.d(TAG, "PowerOnSyncTask recPowerState:"+recPowerState);
					if(recPowerState == (RecService.POWER_STATE_ONGOING|RecService.POWER_STATE_CLEANUP)) {
						Log.d(TAG, "starting timeshift recording after rec powerOnSync");
						recordinstance.startTimeshift(path, (int) mDuration);
						tsState = TSStateDef.STATE_STARTING;
					}
					else {
						mHandler.removeCallbacks(powerOnSyncRunnable);
						mHandler.postDelayed(powerOnSyncRunnable, 1000);
					}
				} else {
					Log.d(TAG, "starting timeshift recording since recservice in null");
					recordinstance.startTimeshift(path, (int) mDuration);
					tsState = TSStateDef.STATE_STARTING;
				}
			}
			else
			{
				 mpresetNumber = presetNumber;
				Log.d(TAG,"Already timeshift in progress, wait untill previous recording stops");
			}
	      } else {
	        Log.d(TAG," record instance  is null  ");
	      }
	     } else {
	       Log.d(TAG," tvmplayer instance is null  ");
	    }
       } else {
          Log.e(TAG, "time shift recording already happening " + tsState.ordinal());
       }
  }

  public void stopTimeShiftRecording(Boolean isHDDReadError) {
	  Log.d(TAG," stopTimeShiftRecording ");
	  if(tsState != TSStateDef.STATE_IDLE){
		  tsState = TSStateDef.STATE_IDLE;
		  if(recordinstance!=null) {
			  recordinstance.stopTimeshift();
		  }
		  if(listener != null) {
			  if(isHDDReadError)
				  listener.onTSRecordingStopped(isHDDReadError);
			  else
				  listener.onTSRecordingStopped();
		  }
		  mRecordedDuration = 0;
	  }
	  else {
		  Log.d(TAG," time shift recording not happening " + tsState.ordinal());
	  }
  }

  @Override
  public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
  int presetNumber) {
	  Log.d(TAG," onPlayStarted : medium " +medium+ " presetNumber " +presetNumber);
	  boolean isCatchUpSelection = false;
	  mpresetNumber = 0;
	  mMedium = medium;
	  selectionComplete = false;
	  
	  if (headers != null) {
		String privData = headers.get(ITVSessionContext.KEY_PRIVATE_DATA_COOKIE);
		if ((privData != null) && (privData.equals(TvHeaders.PRIV_DATA_CATCHUP_TUNE))) {
			isCatchUpSelection = true;
		} else {
			isCatchUpSelection = false;
		}
	  }
	  
	  if((isTSRecordingApplicable()) && (!isCatchUpSelection)) {
		  stopTimeShiftRecording(false);
	  }
  }

  @Override
  public void onMPLPurposeChanged(int purpose) {
	// TODO Auto-generated method stub
	
  }
 
  @Override
  public void onTimeshiftInfoChanged() {
	// TODO Auto-generated method stub
	
  }

  @Override
  public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
  int presetNumber) {	   
		selectionComplete = true;
		prepareTSRecording(mediaPlayerUri, headers, medium, presetNumber);
  }

  @Override
  public void onPlayFinished(Uri mediaPlayerUri, Medium medium,
  int presetNumber) {
    // TODO Auto-generated method stub

  }

  @Override
  public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
    // TODO Auto-generated method stub

  }

  @Override
  public void onInfo(boolean cicamAvailable) {
    // TODO Auto-generated method stub

  }


  public class TSRecordingListenerClass extends IonTvRecordControlCallback {

    @Override
    public void onMinimumDataAvailable() {
      Log.d(TAG, "onMinimumDataAvailable");
      mMinimumDataAvailable = true;
    }

    @Override
    public void licenseCheckStatus(boolean arg0)  {
      // TODO Auto-generated method stub

    }

    @Override
    public void onRecordPlaybackStatus(int arg0) {
      // TODO Auto-generated method stub
    }

    @Override
    public void onRecordingStatus(int arg0)  {
      Log.d(TAG," onRecordingStatus : Status " + arg0);
      mHandler.post(new HandleRecNotifications(arg0));
	 }

    @Override
    public void onTadStatus(int arg0) {
      // TODO Auto-generated method stub

    }

    @Override
    public void onTimeshiftPlaybackStatus(int arg0)  {
      // TODO Auto-generated method stub

    }

    @Override
    public void onTimeshiftStatus(int arg0)  {
      Log.d(TAG," onTimeshiftStatus : Status " + arg0);
      mHandler.post(new HandleTSNotifications(arg0));
    }
  }

  class HandleTSNotifications implements Runnable {
		private int notification;

		public HandleTSNotifications(int notif) {
			notification = notif;
		}

		@Override
		public void run() {
			Log.d(TAG," run: HandleNotifications " + notification);
			switch(notification) {
				case BcstConstants.TIMESHIFT_STARTED:
					if(listener != null) {
						listener.onTSRecordingStarted();
					}
					onTimeShiftRecordingStarted();
					break;
				case BcstConstants.TIMESHIFT_STOPPED:
					onTimeShiftRecordingStopped();
					break;
				case BcstConstants.TIMESHIFT_ERROR_HDDNOTCONNECTED:
					Log.d(TAG," !!! onTimeshiftStatus - HDDError !!!! ");
					mTimeshiftError = notification;
					stopTimeShiftRecording(true);
					break;
				default:
					Log.d(TAG," !!! onTimeshiftStatus - Error !!!! ");
					mTimeshiftError = notification;
					stopTimeShiftRecording(false);
					break;
				}
			}
  };
    class HandleRecNotifications implements Runnable {
		private int notification;

		public HandleRecNotifications(int notif) {
			notification = notif;
		}
		@Override
		public void run() {
			Log.d(TAG," run: HandleRecNotifications " + notification);
			switch(notification) {
				 case BcstConstants.RECORDING_FINISHED:
					Log.d(TAG," REcording Finished: Start the timeshift on preset -: " +  mpresetNumber + " TS status : "  + tsState.ordinal());
					startTimeShiftRecording(mpresetNumber);
					break;
				default:
					break;
				}
			}
  };
  public void onTimeShiftRecordingStarted()
  {
    Log.d(TAG," !!! onTimeShiftStarted !!!! ");
    tsState = TSStateDef.STATE_RUNNING;
	mEpgCache.registerListener(mTSInfo);
	mEpgCache.queryNowNextData(mUniqueId);
    zappedTime = (System.currentTimeMillis()/1000);
    mHandler.postDelayed(mTimerTask, 1000);
  }

  public void onTimeShiftRecordingStopped()
  {
    Log.d(TAG," !!!!!! onTimeShiftStopped !!!! " + tsState);
    mEpgCache.unregisterListener(mTSInfo);
	mEpgNowDataVersion = -2;
	if(tsState==TSStateDef.STATE_RELEASING) {
    	tsState = TSStateDef.STATE_IDLE;
    	releaseMediaPlayer();
    } else {
	    tsState = TSStateDef.STATE_IDLE;
	    if(((0 == mTimeshiftError ) || (BcstConstants.TIMESHIFT_ERROR_SYSTEM  == mTimeshiftError)) && (playtvmplayerforTS!=null) )
	    {
	      /*Recording is stopped only due to time change, then restart recording. otherwise don't start*/
	      Log.d(TAG,"Triggering timeshift recording again");
	      prepareTSRecording(null, null, mMedium, mpresetNumber);
	    }
    }
    mTimeshiftError = 0;
  }

  private void prepareTSRecording(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
	int presetNumber) {
	   if(playtvmplayerforTS==null) {
			getMediaPlayer();
	   }
		try {
			if((headers != null) && (headers.get(TvHeaders.MODE) != null)) {
				mServiceType = Integer.parseInt(headers.get(TvHeaders.MODE));
			}
			if(isTSRecordingApplicable()) {
				mpresetNumber = presetNumber;
				mMedium = medium;
				if((headers != null) && (headers.get(TvHeaders.UNIQUE_ID) != null)) {
					mUniqueId = Integer.parseInt(headers.get(TvHeaders.UNIQUE_ID));
				}
				if (selectionComplete) {
					// check HDD status
					if(mountedPath != null) {
					  //start timeshift recording
					  Log.d(TAG," prepareTSRecording : TS Status-: " + tsState.ordinal());
					  zappedTime = (System.currentTimeMillis()/1000);
					  if(tsState == TSStateDef.STATE_IDLE) {
						switch(medium) {
						case MEDIUM_TERRESTRIAL:
						case MEDIUM_CABLE:
						case MEDIUM_SATELLITE:
						  if(mServiceType != TvHeaders.MODE_ANALOG) {
							Log.d(TAG, "prepareTSRecording DVB-T/C -- starting TS");
							if (RecService.getInstance() != null) {
								if (RecService.getInstance().getTimeShiftCopyStatus()){
									Log.d(TAG, "startTimeShiftRecording");
									startTimeShiftRecording(presetNumber);
								 }
								 else{
									mHandler.postDelayed(mStartTimeShift, 1000);
									Log.d(TAG,"Posting on to the handler");
								}
							}
						   }
						  break;
						default:
						  break;
						}
					  } else {
						  Log.e(TAG, "TS not started as state not idle " + tsState.ordinal());
					  }
					}
					else {
					  Log.d(TAG," prepareTSRecording : Timeshift recording wont start as HDD is not connected/formatted ");
					}
				} else {
					Log.d(TAG, "prepareTSRecording: TS not started since selection is not yet complete !!!");
				}
			}
		} catch (Exception e) {
			Log.d(TAG, "Exception in prepareTSRecording !!"+e.toString());
		}  
  }
  
  public boolean isMinimumDataAvailable() {
    Log.d(TAG, "isMinimumDataAvailable "+mMinimumDataAvailable);
    return mMinimumDataAvailable;
  }

  public void resetMinimumDataAvailable()
  {
	Log.d(TAG, "resetMinimumDataAvailable ");
	mMinimumDataAvailable = false;
  }
  
  public void release()
  {
    Log.d(TAG," release tsstate " + tsState.ordinal() + " playtvmplayerforTS " + playtvmplayerforTS);
    
	if (tsState != TSStateDef.STATE_IDLE) {
		stopTimeShiftRecording(false);
		tsState = TSStateDef.STATE_RELEASING;
    } else {
		releaseMediaPlayer(); //it is ok to miss the notification about timeshift recording stopped..
	}
  }

  public int getCurrentTimeShiftStatus()
  {
  	Log.d(TAG, "get ts status " + mountedPath + ", " + mServiceType + ", " + tsState.ordinal());
  	if(mountedPath == null) {
		return HDD_NOT_CONNECTED;
  	} else if(mServiceType == TvHeaders.MODE_ANALOG) {
  		return ANALOG_CHANNEL;
  	} else if(tsState != TSStateDef.STATE_RUNNING) {
  		return IN_TRANSIENT;
  	} //xrated content not clear whether ts will be stopped..
    	return PAUSE_ALLOWED;
  }

  public long getTotalDuration() {
    Log.d(TAG," !!!!!! getMaxDuration : duration -> "+mDuration+" !!!! " );
    return mDuration;
  }

  public long getTSDuration() {
	long totalSize = PlayTvHDDUtils.getInstance(mContext).getTotalSize();
	// The calculations are based on following :
	// max bit-rate = 25mbps or 3276800 bytes per second.
	// 90 minutes recording at speed of 3276800 bytes per second = (3276800 * 90 *60)/1024/1024 = 16875 MByte or ~16.5 GByte
	float availableDuration = (totalSize * 1000)/(float)3276800;
	long totalDuration = 0;

	if (availableDuration > (90 * 60 * 1000)) {
		totalDuration = (90 * 60 * 1000);
	} else {
		totalDuration = (long)availableDuration;
	}
	Log.d (TAG, "getTSDuration - totalSize:"+totalSize+", availableDuration:"+availableDuration+", totalDuration:"+totalDuration);

	return totalDuration;
  }

  public long getRecordedDuration(){
       return (mRecordedDuration*ONE_SECOND);
  }

  public int getCopyDuration() {
/*
       if(mountedPath != null) {
      int copyDuration = 0;
      long timenow = System.currentTimeMillis()/1000;
      copyDuration = (int)(timenow - zappedTime);
      int totalDuration = (int)(getTotalDuration()/1000);
      if(copyDuration > totalDuration)
        copyDuration = totalDuration;
      return copyDuration;
    }
    else
    return 0;
*/
    /*AN-67996 - timeshift copy is removed in 2k14*/
    return 0;
  }

  @Override
  public void onLockStatusChanged(int type, int status) {
    // TODO Auto-generated method stub

  }
  @Override
  public boolean onAvailable(int clientType) {
    // start timeshift recording
    Log.d(TAG,"  onAvailable");
    mHandler.post(mStart);
    return false;
  }

  @Override
  public boolean onNotAvailable(int clientType) {
    // stop timeshift recording
    Log.d(TAG,"  onNotAvailable timeshiftrecordingstarted :  " + tsState.ordinal());
    stopTimeShiftRecording(false);
    releaseMediaPlayer(); //it is ok to miss the notification about timeshift recording stopped..
    return false;
  }


  @Override
  public void onOlympicUsecaseUpdate(boolean enable, boolean isOTR) {
    // TODO Auto-generated method stub

  }


  /*------------HDD Notifications starts here-------------*/
  @Override
  public void onHDDConnected() {
    Log.d(TAG,"onHDDConnected");
    Runnable nodeChangeRunnable = new Runnable() {
      @Override
      public void run() {
        mountedPath = PlayTvHDDUtils.getInstance(mContext).getMountPath();
        mDuration = getTSDuration();

        if(tsState == TSStateDef.STATE_IDLE) {
          	Log.d(TAG," onAvailable : Start timeshift on channel :" + mpresetNumber);
			if(mountedPath != null) {
				if(mServiceType != TvHeaders.MODE_ANALOG) {
					getMediaPlayer();
					startTimeShiftRecording(mpresetNumber);
				}
			}
  		} else {
  			Log.e(TAG, "no hdd on connected");
  		}
      }
    };
    mHandler.post(nodeChangeRunnable);
  }

  @Override
  public void onHDDRemoved() {
    Log.d(TAG,"onHDDRemoved");
    Runnable nodeChangeRunnable = new Runnable() {
      @Override
      public void run() {
        mountedPath = null;
        if(tsState != TSStateDef.STATE_IDLE) {
          stopTimeShiftRecording(true);
        }
      }
    };
    mHandler.post(nodeChangeRunnable);
  }


/*------------HDD Notifications ends here-------------*/
  private Runnable mStart = new Runnable() {
    @Override
    public void run() {
      Log.d(TAG, "processing start recording");
      if(playtvmplayerforTS == null) {
        getMediaPlayer();
      }
      startTimeShiftRecording(mpresetNumber);
    }
  };

  private Runnable mTimerTask = new Runnable() {
    @Override
    public void run() {
      if((tsState == TSStateDef.STATE_RUNNING) && (null != recordinstance))
      {
        RecordingInfo info;
        info  = recordinstance.getCurrentRecordingInfo(0);
        mRecordedDuration = info.duration;
        Log.d(TAG,"RecordedDuration : duration -> " + mRecordedDuration );
        mHandler.postDelayed(mTimerTask, 1000);
      }
    }
  };


	@Override
	public void onPlayStateChanged(int state, int mode) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onLicenseExchangeHappening(boolean status) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onSeekComplete(int mode) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onPlayError(int error, int what, int extra, int mode) {
		// TODO Auto-generated method stub
		release();
	}
	@Override
	public void onServiceTypeDetected(int type) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onTrickModeEnabled(boolean status, int mode) {
		// TODO Auto-generated method stub
		
	}

	class PowerOnSyncRunnable implements Runnable {
		@Override
		public void run() {
			Log.d(TAG," run: PowerOnSyncRunnable ");
			startTimeShiftRecording(mpresetNumber);
		}
	}

    private Runnable mStartTimeShift = new Runnable() {

        @Override
        public void run() {

            if (RecService.getInstance() != null) {
                if (RecService.getInstance().getTimeShiftCopyStatus()){
                    Log.d(TAG," startTimeShiftRecording");
                    startTimeShiftRecording(mpresetNumber);
                }
                else
                {
                    mHandler.postDelayed(mStartTimeShift, 1000);
                }
            }
       }
    };
    
    private boolean isTSRecordingApplicable() {
    	if(playtvmplayerforTS!=null) {
    		if(((playtvmplayerforTS.getCurrentPurpose()) & Math.abs((PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH | PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD | PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD)))>0) {
  			 return true; 
  		  }
  	   }
    	return false;
    }
	
	private IEpgProviderNotify mTSInfo = new IEpgProviderNotify() {
		@Override
		public void onEpgDataChanged(int channelId) {
			try {
				Log.d(TAG, "onEpgDataChanged "+channelId+" "+mEpgCache.isBCEpgMode());
				final int chId = channelId;
				if(mEpgCache.isBCEpgMode()) {
					Runnable TSInfoRun = new Runnable() {
						@Override
						public void run() {
							updateTSInfo(chId);
						}
					};
					mHandler.post(TSInfoRun);
				}
			} catch (Exception e) {
				Log.d(TAG, "Exception in onEpgDataChanged !!!"+e.toString());
			}
		}
		
		@Override
		public void onEpgModeChanged() {
			Log.d(TAG, "onEpgModeChanged");
		}
	};
		
	private void updateTSInfo(int channelId) {
		if (tsState != TSStateDef.STATE_IDLE) {
			int currentVersion = mEpgCache.getNowVersion(channelId);
			String eventName = null;
			String shortInfo = null;
			String extendedInfo = null;
			String guidanceInfo = null;
			int genre = 0;
			int rating = 0;
			try {
				Log.d(TAG, "Inserting EIT infor for TS curVer:"+currentVersion+" prevVer:"+mEpgNowDataVersion);
				if (currentVersion != mEpgNowDataVersion) {
					mEpgNowDataVersion = currentVersion;
					mEitInfo.eventName = mEpgCache.getNowEventName(channelId);
					mEitInfo.shortInfo = mEpgCache.getNowShortInfo(channelId);
					mEitInfo.extendedInfo = mEpgCache.getNowExtendedInfo(channelId);
					mEitInfo.guidanceInfo = mEpgCache.getNowGuidanceinfo(channelId);
					mEitInfo.genre = mEpgCache.getNowGenre(channelId);
					mEitInfo.rating = mEpgCache.getNowRating(channelId);
					mEitInfo.uniqueId = mUniqueId;
					recordinstance.StoreEITData(mEitInfo.eventName, mEitInfo.shortInfo, mEitInfo.extendedInfo, 
												mEitInfo.guidanceInfo, mEitInfo.uniqueId, mEitInfo.genre, mEitInfo.rating);
				}
			} catch (Exception e) {
				Log.d(TAG, "Exception in updateTSInfo !!"+e.toString());
			}
		}
	}
	
	public PlaybackEitInfo getEitInfo() {
		return mEitInfo;
	}
}
