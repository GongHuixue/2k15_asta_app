package org.droidtv.tunerservice.recording;

import java.util.ArrayList;
import java.util.ConcurrentModificationException;
import java.util.List;
import org.droidtv.tunerservice.recording.Reminder;
import org.droidtv.tunerservice.util.RecLogger;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.database.ContentObserver;
import android.database.DatabaseUtils;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import java.util.Map;
import android.media.tv.TvInputInfo;
import android.media.tv.TvInputManager;
import android.media.tv.TvInputManager.SessionCallback;
import android.media.tv.TvInputManager.TvInputCallback;
import android.media.tv.TvInputManager.Session;
import android.media.tv.TvTrackInfo;
import android.media.tv.TvContentRating;
import org.droidtv.tv.tvinput.ITVTunerSession.ITunerSessionCallbacks;
import org.droidtv.tv.tvinput.ITVSessionContext.ISessionContextCallbacks;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tunerservice.PlayTvDiversity;
import org.droidtv.tunerservice.recording.TimeshiftRecording;
import org.droidtv.tunerservice.util.PlayTvHDDUtils;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.UriData;
import org.droidtv.tunerservice.bcstreceiver.AlarmReceiver;
import org.droidtv.tunerservice.interfaces.IHDDListener;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.interfaces.IPowerEvents;
import org.droidtv.tunerservice.interfaces.IRecStateChangeListener;
import org.droidtv.tunerservice.recording.AutoPVR;
import android.media.tv.TvContract;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.db.CAMDetails;
import org.droidtv.tunerservice.db.CamInfoDB;
import org.droidtv.tunerservice.epgnownext.EpgCache;
import org.droidtv.tunerservice.epgnownext.IEpgProviderNotify;
import org.droidtv.tunerservice.epgnownext.EpgNowNextData;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.media.BcstConstants;
import org.droidtv.tv.media.ITvMediaRecordControl;
import org.droidtv.tv.media.ITvMediaControl;
import org.droidtv.tv.media.ISubtitles;
import org.droidtv.tv.media.ITvMediaRecordControl.IonTvRecordControlCallback;
import org.droidtv.tv.media.ITvMediaRecordControl.RecordingInfo;
//import org.droidtv.tv.media.ITvURI;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.provider.IRecordingsContract.RecordingError;
import org.droidtv.tv.provider.IRecordingsContract.RecordingType;
import org.droidtv.tv.provider.IRecordingsContract.EITSource;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerShutdownLocks;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.media.ITvMediaStream.TvMediaAudioInfo;
import org.droidtv.tunerservice.recording.RecordData;
import org.droidtv.tv.media.ITvMediaStream;
import org.droidtv.tv.media.ITvMediaStream.IOnMediaStreamChangeListener;
import org.droidtv.tv.media.ITvMediaStream.TvMediaEitPFinfo;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl.ITvSemiStandbyCallback;
import org.droidtv.tunerservice.playback.TvChannelPlayback;
import org.droidtv.tunerservice.provider.recordremind.RecordingsAllocation_Single;
import org.droidtv.tv.logger.ILogger;
import org.droidtv.tv.logger.ILogger.ChannelZapSource;
import org.droidtv.tv.logger.ILogger.ChannelZapSource.*;

public class RecService implements ITvAbstractPlaybackListener , IHDDListener{

	private final static String Tag 							= "RecService";

	private static final int FIVE_SECONDS 						= 5;
	private static final int ONE_MIN 							= 60;
	private static final int TWO_MINS							= 120;
	private static final int TEN_MINS							= 600;
	private static final int TWENTY_MINS 						= 1200;
	private static final int MILLIS_IN_SECOND 						= 1000;

	private static final long MIN_SIZE_FOR_PVR = 21474836480L;// 20GB (20*1024*1024*1024)
	private static final long MIN_SPACE_FOR_PVR = 536870912L;// 512 MB (512*1024*1024)

	public final static int POWER_STATE_IDLE 					= 0x0000;
	public final static int POWER_STATE_ONGOING					= 0x0001;
	public final static int POWER_STATE_CLEANUP 				= 0x0002;

	// states
	public final static int STATE_IDLE 							                                = 0;
	public final static int STATE_TUNING 							                                = 1;
	public final static int STATE_WAITING_FOR_EVENT	                                              = 2;
	public final static int STATE_RECORDING_STARTING 			                                = 3;
	public final static int STATE_RECORDING_STARTING_NORDIG_NO_EVENT		    = 4;
	public final static int STATE_RECORDING_EVENT 				                                = 5;
	public final static int STATE_RECORDING_NORDIG_NO_EVENT			                  = 6;
	public final static int STATE_RECORDING_MANUAL 				                         = 7;
	public final static int STATE_RECORDING_AUTO_MARGIN 		                         = 8;
	public final static int STATE_RECORDING_STOPPING 			                                = 9;


	public final static int MEDIA_AUDIO_CHANGE  				= 0x01;
	public final static int MEDIA_SUBTITLE_CHANGE    			= 0x02;
	public final static int MEDIA_CHECK_AND_APPLY_CHANGE		= 0x03;
	public final static int MEDIA_FLUSH_CHANGE    				= 0x04;


	private RecContentObserver recObserver 						= null;
	private PlayTVFacMediaPlayer playtvmplayer						= null;

	private ITvMediaRecordControl recordinstance				= null;
	private List<IRecStateChangeListener> registeredListeners 	= null;
	boolean foreground_rec										= false;
	private Handler handler										= null;
	private Runnable runnable									= null;
	private Handler finishRecHandler							= null;
	private Handler lockHandler									= null;
	private Runnable finishRecRunnable							= null;
	private PvrRecordListenerClass PvrRecordListener			= null;
	private MediaStreamChangeListenerClass mMediaStreamChangeListener = null;
	private String mountPath									= null;
  	private long mAlarmTime=Long.MAX_VALUE;
  	private int PreparePostPonedRecordId=-1;
	private RecordData ongoingRecData 							= null;
	private PlayTVMediaPlayerFactory factory 					= null;
	private ITvPowerManager pm									= null;
	private ITvPowerManager.ShutdownLock  lock					= null;
  private ITvPowerManager.ShutdownLock  mShutDownInProgresslock;
	private ITvPowerManager mTvPowerManager						= null;
	private PendingIntent pendingIntent 						= null;
	//private PlayTVKeyHandler mEventHandler						= null;	TODO:TIF MOVEMENT
	private TVContentObserver tvObserver 						= null;
	private static Context mContext								= null;
	private EpgCache mEpgCache 									= null;

	private static RecService mRecService 						= null;

	static IRecordingsContract.RecordingType[] rec_type 			= null;
	static IRecordingsContract.RecordingError[] rec_error_type 	= null;

	public RecValidityCheck recValidityCheck 					= null;

	private boolean isRecordingPending 							= false;
	private boolean dualTunerSupported 							= false;
	private boolean isVersionNull 								= true;
	private boolean isPartial 									= false;
	private boolean isObserverRegistered 						= false;
	private boolean isTimeShiftCopyDone 						= true;


	private int mUserChannelCid 									= -1;
	private int mRecChannelCid = -1;
	private int mUserSubtitleIndex 							= -2;
	private int mUserAudioIndex 							= -1;
	private int mNextRecordingId 								= -1;
	private int currentVersion 									= -1;

	private int powerOnSyncState								= POWER_STATE_IDLE;
	private int currentState 									= STATE_IDLE ;
	private long mNextRecordingEST 								= Long.MAX_VALUE;
	private Medium mUserMedium 									= Medium.MEDIUM_INVALID;
	private RecordingError recError 							= RecordingError.REC_ERROR_NONE;
	private PowerStates mCurrentPowerState 						= PowerStates.POWER_STATE_UNKNOWN;

	private ITvMediaStream mMediaStream = null;
	private RecEitRunnable eitRunnable = new RecEitRunnable();
	private final static int EIT_NOT_ARRIVED =0;
	private final static int EVENT_IN_PRESENT =1;
	private final static int EVENT_IN_FOLLOWING =2;
	private final static int EVENT_IS_NOT_PRESENT =3;
	private final static boolean  EIT_PRESENT_EVENT = false;
	private final static boolean  EIT_FOLLOWING_EVENT =true;
	private TvToast mTimeOutTvToast		= null;
	private TvToastMessenger messenger	= null;

	private TvInputCallbackClass mTvInputCallback =  null;
	private TvInputManager mTvInputManager = null;
	private TunerSessionCallback mSessionCallback = null;
	private Handler mSessionHandler = null;
	String TunerServiceID = null;
	private static IPowerEvents mPowerEventListener = null;
	private ITvSemiStandbyControl mCallback=null;
	private RecordingsAllocation_Single rec_allocator = null;
	private Handler sbyHandler = null;
	private final int id = ITvSemiStandbyControl.ACTION_RECORDING;
	private SbyCallback msbyCallbackclass = null;
	private int mUserChannelLock=-1;
	private RecLogger recLog = null;
	private RecService(){
		//Log.i(Tag, "constructor called");

	}

	private void initRecService(){
		//Log.d(Tag,"initRecService called");
		registeredListeners 			= new ArrayList<IRecStateChangeListener>();
		rec_type						= IRecordingsContract.RecordingType.values();
		rec_error_type 					= IRecordingsContract.RecordingError.values();
		mPowerEventListener = new PowerEventsReceiver();

		mTvPowerManager = ITvPowerManager.Instance.getInterface();
		if(mTvPowerManager!=null)
    mCurrentPowerState = mTvPowerManager.GetPowerState();
	recLog = RecLogger.getInstance();
	recLog.bindToLoggingService(mContext);

    try {
      handler = new Handler();
	lockHandler = new Handler();
      runnable = new Runnable() {
        @Override
        public void run() {
					//Log.d(Tag, "endRecording called");
          endRecording(false);
        }
      };
			rec_allocator = RecordingsAllocation_Single.getInstance(mContext);
      recObserver = new RecContentObserver(null);
      mContext.getContentResolver().registerContentObserver(IRecordingsContract.CONTENT_URI_Recordings, true, recObserver);
      //Log.d(Tag, "Registered Observer");
    } catch (Exception ex) {
      Log.e(Tag, ex.toString());
    }
    try {
      finishRecHandler = new Handler();
      finishRecRunnable = new Runnable() {
        @Override
        public void run() {
					if (ongoingRecData != null) {
            HandleRecordingFinished(ongoingRecData);
					} else {
            Log.d(Tag, "ongoingRecData is null");
          }
        }
      };
    } catch (Exception ex) {
      Log.e(Tag, ex.toString());
    }
		getVersion();
    factory = PlayTVMediaPlayerFactory.getInstance();
    pm = ITvPowerManager.Instance.getInterface();
    lock = pm.CreateShutdownLock(PowerShutdownLocks.DONT_SHUTDOWN_LOCK, Tag);
    mShutDownInProgresslock=pm.CreateShutdownLock(PowerShutdownLocks.SHUTDOWN_IN_PROGRESS_LOCK, Tag);
	messenger 		= TvToastMessenger.getInstance(mContext);
	mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
    PvrRecordListener = new PvrRecordListenerClass();
		mMediaStreamChangeListener = new MediaStreamChangeListenerClass();
	    createObserverSession();
		// mEventHandler = PlayTVKeyHandler.getInstance();//TODO: TIF MOVEMENT
		// query HDD
		PlayTvHDDUtils.getInstance(mContext).addHDDListener(this, Tag);
		mountPath = PlayTvHDDUtils.getInstance(mContext).getMountPath();
		doPowerOnSync();
		//Log.d(Tag, " powerOnSyncState in onCreate: " + powerOnSyncState);
		powerOnSyncState |= POWER_STATE_CLEANUP;
		RegisterBroadcastReceiver();
		recValidityCheck = new RecValidityCheck(mContext);
		recValidityCheck.startLooperthread();
		mEpgCache = new EpgCache(mContext);
		msbyCallbackclass = new SbyCallback();
		bindtoSSBYService();
	}
	private void createObserverSession() {
		mSessionHandler = new Handler();
		mTvInputCallback = new TvInputCallbackClass();
		mSessionCallback = new TunerSessionCallback();
		mTvInputManager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
		if (mTvInputManager != null) {
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
				//Log.d(Tag,"Creating session");
				mTvInputManager.createSession(TunerServiceID, mSessionCallback, mSessionHandler);
			}else {
				Log.d(Tag,"TunerService input not added yet");
			}
		} else {
			Log.d(Tag, "TvInputManager is null");
		}
	}

	public static RecService getInstance(){
		//Log.i(Tag,"getInstance called ");
			return mRecService;
	}

	public int getPowerOnSyncState() {
		return powerOnSyncState;
	}

	public void doPowerOnSync()
	{
		//Log.d(Tag, " acquiring lock in recService for doPowerOnSync");
		getLock();
		try {
			TvMediaPlayer mMediaPlayer = null;
			mMediaPlayer = TvMediaPlayer.getTvTunerMediaPlayer();
			recordinstance = mMediaPlayer.getTvMediaPlayerContext().getTvMediaRecordControl();
		}catch(Exception e) {
			Log.e(Tag, "caught exception to get root tv media player instance for poweronSync"+ e.toString());
		}
		if(mountPath != null) {
			PowerOnSyncOngoingRecording();
			PowerOnSyncUserActions();
			powerOnSyncState |= POWER_STATE_ONGOING;
			Log.d(Tag, " powerOnSyncState after ongoing things done: "+powerOnSyncState);
		}
		PowerOnSyncCleanUp();
         //Auto PVR not supported
		//AutoPVR.getInstance().doPowerOnSync(mContext);
		Reminder.getInstance(mContext).registerReminderEvent();
	}


	void PowerOnSyncOngoingRecording()
	{
		//query for ongoing recording
		//Log.d(Tag, " PowerOnSyncOngoingRecording ");
		String[] projection = {IRecordingsContract.C_RECORDING_ID,IRecordingsContract.C_CHANNELID};
		String selection = IRecordingsContract.C_RECORDING_TYPE + " == ?";
		String[] selectionArgs = {""+IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal()};
		Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, selection,
										selectionArgs, null);

		if( (c != null) && (c.getCount() > 0) && (c.moveToFirst() ) ) {
			if(mountPath != null)
			{
			try {
			  TvMediaPlayer mMediaPlayer = null;
			  mMediaPlayer = TvMediaPlayer.getTvTunerMediaPlayer();
			  recordinstance = mMediaPlayer.getTvMediaPlayerContext().getTvMediaRecordControl();
			  if(recordinstance!=null) {
				Log.d(Tag, " PowerOnSyncOngoingRecording : update rec type to new, mountpath is :"+mountPath);
				long deviceIdentifier = PlayTvHDDUtils.getInstance(mContext).getDeviceId();
				String deviceId = Long.toString(deviceIdentifier);
				recordinstance.recoverOngoingRecording(mountPath, c.getInt(0),deviceId);
				isPartial = true;
				recError = RecordingError.REC_ERROR_POWERINTERRUPTION;
				updateRecordDetails(c.getInt(0), true, null);
				Uri tvContentProviderUri = TvContract.buildChannelUri(c.getInt(1));
				int medium=-1;
				if (tvContentProviderUri != null) {
					UriData mdata=TvURIHelper.parseUri(mContext, tvContentProviderUri);
					if(mdata!=null){
						medium=mdata.medium;
					}
				}
				dualTunerSupported=factory.IsDualTunerFactoryConfigEnabled(TvURIHelper.Medium.fromInteger(medium));
			      if(dualTunerSupported){
			    	  foreground_rec=false;
					} else{
			    	  foreground_rec=true;
			      }
			    Log.d(Tag,"poweronsync ongoing- recid"+c.getInt(0)+"cid"+c.getInt(1)+"medium-"+medium);
				Intent i = new Intent("org.droidtv.playtv.REC_END_NOTIFY");
			    i.putExtra("recordId", c.getInt(0));
				i.putExtra(IRecordingsContract.C_CHANNELID, c.getInt(1));
				i.putExtra("foreground",foreground_rec);
			    mContext.sendBroadcast(i);
			  }
			}
			catch(Exception e) {
			  Log.e(Tag, "exception in deleteRecording"+ e.toString());
			}
		  }
		  else {
			updateRecordForError(c.getInt(0), RecordingError.REC_ERROR_NODISK, false, false);
		  }
		}
		else
		{
		  Log.d(Tag, "No result for cursor for PowerOnSyncOngoingRecording");
		}
		if(c != null)
			c.close();
	}


  void PowerOnSyncUserActions()
  {
   // Log.d(Tag, " PowerOnSyncUserActions ");
    String[] projection = {IRecordingsContract.C_RECORDING_ID, IRecordingsContract.C_RECORDING_TYPE};
    String selection = IRecordingsContract.C_RECORDING_TYPE + " = ? OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = ? ";
    String[] selectionArgs = {""+IRecordingsContract.RecordingType.RECORDING_USER_STOPPED.ordinal(),
      ""+IRecordingsContract.RecordingType.RECORDING_USER_DELETED.ordinal()};
    Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, selection,
    selectionArgs, null);
    if( (c != null) && (c.getCount() > 0) && (c.moveToFirst() ) ) {
      do {
        String where = IRecordingsContract.C_RECORDING_ID + " = ? ";
        String[] whereArgs = { Integer.toString(c.getInt(0))};
        RecordingType recType = rec_type[c.getInt(1)];
        Log.d(Tag, "PowerOnSyncUserActions recType " +recType);
        switch(recType) {
        case RECORDING_USER_STOPPED :
        	if((mountPath != null) && (recordinstance!=null))
			{
				Log.d(Tag, " PowerOnSyncUserActions : update rec type to new, mountpath is :"+mountPath);
				long deviceIdentifier = PlayTvHDDUtils.getInstance(mContext).getDeviceId();
				String deviceId = Long.toString(deviceIdentifier);
				recordinstance.recoverOngoingRecording(mountPath, c.getInt(0), deviceId);
				isPartial = false;
				recError = RecordingError.REC_ERROR_NONE;
			}
        	updateRecordDetails(c.getInt(0), true, null);
          break;

        case RECORDING_USER_DELETED :
          //if HDD connected
          if(mountPath != null)
          {
            Log.d(Tag, "PowerOnSyncUserActions RECORDING_USER_DELETED mountPath:" +mountPath);
            try {
              TvMediaPlayer mMediaPlayer = null;
              mMediaPlayer = TvMediaPlayer.getTvTunerMediaPlayer();
              recordinstance = mMediaPlayer.getTvMediaPlayerContext().getTvMediaRecordControl();
              if(recordinstance!=null)
              {
                recordinstance.deleteRecording(c.getInt(0), mountPath);
                int del_res = mContext.getContentResolver().delete(IRecordingsContract.CONTENT_URI_Recordings, where, whereArgs);
                Log.d(Tag, "PowerOnSyncUserActions deleted "+del_res+" Recordings.");
              }
            }
            catch(Exception e){
              Log.e(Tag, "exception in deleteRecording"+ e.toString());
            }

          }
          break;

        default:
          Log.d(Tag, "this rec_type"+ recType+ " not expected");
        }
      }while (c.moveToNext());
    }
    else
    {
      Log.d(Tag, "No result for cursor for PowerOnSyncUserActions");
    }
    if(c != null)
      c.close();
  }

  void PowerOnSyncCleanUp() {
    long timenow = System.currentTimeMillis()/1000;
    //Log.d(Tag, " PowerOnSyncCleanUp timenow: "+timenow );
    String where = "(" + IRecordingsContract.C_RECORDING_TYPE + " = "
    +IRecordingsContract.RecordingType.RECORDING_SCHEDULED.ordinal()+" OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = "
    +IRecordingsContract.RecordingType.RECORDING_MANUAL.ordinal() +" OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = "
    +IRecordingsContract.RecordingType.RECORDING_OTR.ordinal()+") AND ( (" +
    IRecordingsContract.C_EFFECTIVE_END_TIME + ") <= "+timenow+")";

    ContentValues updateValues = new ContentValues();
    updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_FAILED.ordinal());
    updateValues.put(IRecordingsContract.C_IS_PARTIAL, false);
    updateValues.put(IRecordingsContract.C_RECORDING_ERROR, RecordingError.REC_ERROR_NOPOWER.ordinal());
    updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
    int update_result = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, updateValues, where, null);
    Log.d(Tag, "updated "+update_result+" records to failed in PowerOnSyncCleanUp, now prepare for next record.");
    //update version with max version as nodes handled already
    String[] ver_proj = new String[]{"MAX(" + IRecordingsContract.C_VERSION +")"};
    //String ver_sel = "MAX(" + IRecordingsContract.C_VERSION +")";
    Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, ver_proj, null, null, null) ;
    if((c != null) && (c.getCount() > 0) && (c.moveToFirst() ))
    {
      //Log.d(Tag, "setting version value as "+ c.getInt(0)+ " after PowerOnSync");
      setVersion(c.getInt(0));
    }
    if(c != null)
    	c.close();
    String[] proj = {IRecordingsContract.C_CHANNELID, IRecordingsContract.C_EFFECTIVE_START_TIME,
      IRecordingsContract.C_EFFECTIVE_END_TIME, IRecordingsContract.C_RECORDING_TYPE,
      IRecordingsContract.C_VERSION, IRecordingsContract.C_RECORDING_ID,
      IRecordingsContract.C_EVENT_ID /*6*/, IRecordingsContract.C_MARGIN_END /*7*/,IRecordingsContract.C_MARGIN_START /*8*/,
      IRecordingsContract.C_ISIPEPG_RECORDING /*9*/, IRecordingsContract.C_RECORDING_NAME /*10*/};
    String sel = IRecordingsContract.C_RECORDING_TYPE + " = ? OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = ? OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = ? ";
    String[] sel_args = {String.valueOf(RecordingType.RECORDING_OTR.ordinal()),
      String.valueOf(RecordingType.RECORDING_SCHEDULED.ordinal()),
      String.valueOf(RecordingType.RECORDING_MANUAL.ordinal())};
    String orderby = IRecordingsContract.C_EFFECTIVE_START_TIME + " ASC LIMIT 1";
    Cursor c1 = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, proj, sel,
    sel_args, orderby);

    if( (c1 != null) && (c1.getCount() > 0) && (c1.moveToFirst() ) ) {
      RecordData record =  new RecordData(c1.getInt(5), c1.getInt(0), c1.getLong(1), c1.getLong(2), c1.getInt(4),
      								rec_type[c1.getInt(3)], c1.getInt(6), c1.getInt(7), c1.getInt(8), c1.getInt(9), c1.getString(10), mContext);
      if(record.recordId !=0)
      {
        Log.d(Tag, "PowerOnSyncCleanUp: PrepareForRecording ");
		recLog.logFailedRecording(record.recordId, RecordingError.REC_ERROR_NOPOWER );
        //PrepareForRecording(record);
        handler.post(new PrepareRecRunnable(record, true));
        if(timenow < record.est-TWENTY_MINS)
        {
          Log.d(Tag, "PowerOnSyncCleanUp: releasing lock as recording is after long time.");
          releaseLock();
        }
        else {
          Log.d(Tag, "PowerOnSyncCleanUp: holding lock as recording is scheduled.");
        }
      }
      else {
        Log.d(Tag, "PowerOnSyncCleanUp: releasing lock as recording id is zero.");
        releaseLock();
      }
    }else
    {
      Log.d(Tag, "cursor empty: no recordings to prepare. Release lock.");
      releaseLock();
    }
    if(c1 != null)
      c1.close();
  }

  class RecContentObserver extends ContentObserver {

    public RecContentObserver(Handler handler) {
      super(handler);
      //Log.d(Tag, "RecContentObserver construct");
    }

    @Override
    public boolean deliverSelfNotifications() {
      return false;
    }

    @Override
    public synchronized void onChange(boolean selfChange, Uri uri) {
      //Log.d(Tag, "onChange ");
      String ChangeId = uri.getQueryParameter(IRecordingsContract.C_CHANGE_ID);
      String OperationType = uri.getQueryParameter(IRecordingsContract.C_OPERATIONTYPE);
      if((OperationType.equals(IRecordingsContract.C_OPERATIONTYPE_INSERT)) ||
          ((OperationType.equals(IRecordingsContract.C_OPERATIONTYPE_UPDATE)) &&
            (!(Tag.equals(ChangeId))) && (!((AutoPVR.TAG).equals(ChangeId)))))
      {
        if(!selfChange) {
          Log.d(Tag, "onChange Called : URI" + uri);
          Runnable nodeChangeRunnable = new Runnable() {
            @Override
            public void run() {
              NodeChanged();
            }
          };
          handler.post(nodeChangeRunnable);
        }
      }
      else
      {
        String version = uri.getQueryParameter(IRecordingsContract.C_VERSION);
        Log.d(Tag, "onChange version: "+ version);
        if(!(version.equals("-1"))){
          //setVersion(Integer.parseInt(version));
          SetVersionRunnable setVersionRunnable = new SetVersionRunnable(Integer.parseInt(version));
          handler.post(setVersionRunnable);
        }
        Log.d(Tag, "operation type is :"+ OperationType);
        Log.d(Tag, "Change Id is :"+ ChangeId);
        Log.d(Tag, "operation type is delete or update from recService/AutoPVR");
      }
    }
  }


  private void RegisterBroadcastReceiver() {
    //Log.d(Tag,"RegisterBroadcastReceiver ");
    IntentFilter HDDFormatFilter = new IntentFilter();
    HDDFormatFilter.addAction("org.droidtv.intent.action.FORMATTINGDONE");
    mContext.registerReceiver(HDDFormatReceiver, HDDFormatFilter);	//TODO:TIF: to be handled
    //Log.d(Tag,"RegisterBroadcastReceiver Done");
  }

  private boolean NordigPVRSupported(RecordData recData)
  {
	  boolean retval = false;
	  int country = 0;

	  ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
	  country = globalSettings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
        Log.d(Tag,"recData.isIPEPG " + recData.isIPEPG +  " recData.medium " + recData.medium + " recData.endUserMargin " +  recData.endUserMargin + " country " + country);
	  if( ( recData.isIPEPG == 0) &&
	  	(recData.eventId != -1) &&
	  	( (recData.medium == Medium.MEDIUM_CABLE) || (recData.medium == Medium.MEDIUM_TERRESTRIAL) ) &&
	  	(0 ==  recData.endUserMargin) &&
	  	(0 == recData.startUserMargin) &&
	  	( 	(country ==TvSettingsDefinitions.InstallationCountryConstants.NORWAY)||
				  (country ==TvSettingsDefinitions.InstallationCountryConstants.FINLAND)||
				  (country ==TvSettingsDefinitions.InstallationCountryConstants.DENMARK)||
				  (country == TvSettingsDefinitions.InstallationCountryConstants.SWEDEN)) ) {
	  	retval = true;
	  	Log.d(Tag,"Nordig PVR supported");
	  }
	  return retval;
  }

  private class EitInfoPair {
  	int eitStatus;
	TvMediaEitPFinfo info;
  }

  private EitInfoPair CheckEitPFData(RecordData recdata)
  {
	  boolean found = false;
	  EitInfoPair retval = new EitInfoPair();

         if(null != playtvmplayer){
        	  ITvMediaStream mediaStream = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaStream();
        	  if(mediaStream!=null) {
        	  	TvMediaEitPFinfo eitPresentData;
        	  	TvMediaEitPFinfo eitFollowingData;
        		eitPresentData = mediaStream.getEitPFData(EIT_PRESENT_EVENT);
        		eitFollowingData = mediaStream.getEitPFData(EIT_FOLLOWING_EVENT);
        		Log.d(Tag,"CheckEitPFData() Presnt Event Id "+ eitPresentData.eventid + " Following Event Id " + eitFollowingData.eventid);
        		retval.info = eitPresentData; //default is present info..
        		if(eitPresentData.eventid == recdata.eventId) {
        			//start rec,update end time
        			found = true;
        			retval.eitStatus = EVENT_IN_PRESENT;
        		}
        		if(!found) {
        			if(eitFollowingData.eventid == recdata.eventId) {
        				//start rec after event comes to present &  start record
        				found = true;
        				retval.eitStatus = EVENT_IN_FOLLOWING;
        				retval.info = eitFollowingData;
        			}
        		}
        		if((eitPresentData.eventid == -1)&&(eitFollowingData.eventid == -1)) {
        			//eit is not present
        			retval.eitStatus = EIT_NOT_ARRIVED;
        		} else if(!found) {
        			//start rec as scheduled
        			retval.eitStatus = EVENT_IS_NOT_PRESENT;
        		}
        	  }
	  }
	  Log.d(Tag," CheckEitPFData() - EIT status " + retval.eitStatus);
	  return retval;
  }

  boolean isNextRecordingReady() {
  	return isNextRecordingReady(System.currentTimeMillis()/1000);
  }

  boolean isNextRecordingReady(long atTime) {
    boolean retval = false;

    String[] projection = { IRecordingsContract.C_EFFECTIVE_START_TIME};
    String selection = IRecordingsContract.C_RECORDING_TYPE + " = ? OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = ? OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = ?";
    String[] selectionArgs = {String.valueOf(RecordingType.RECORDING_OTR.ordinal()),
      String.valueOf(RecordingType.RECORDING_SCHEDULED.ordinal()),
      String.valueOf(RecordingType.RECORDING_MANUAL.ordinal())};
    String orderBy = IRecordingsContract.C_EFFECTIVE_START_TIME + " ASC  LIMIT 1";
    Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection,
    selection, selectionArgs, orderBy);
     if( (c != null) && (c.getCount() > 0) && (c.moveToFirst() ) ) {
	if(atTime >= c.getLong(0)) {
		retval = true;
	}
    }
    if(c != null)
    	c.close();
    return retval;
  }

  class RecEitRunnable implements Runnable {
	  @Override
	  public void run() {
		if(null == ongoingRecData) {
			Log.e(Tag, "ongoing rec data null in RecEitRunnable");
			return;
		}
		if(!NordigPVRSupported(ongoingRecData)) {
			Log.d(Tag, "no eit based nordig pvr ");
			return;
		}
		long timenow = System.currentTimeMillis()/1000;
		EitInfoPair status = CheckEitPFData(ongoingRecData);
		Log.d(Tag," run: RecEitRunnable " + currentState + ", " + status.eitStatus);
		switch(currentState) {
		case STATE_WAITING_FOR_EVENT:
			 switch(status.eitStatus) {
			 case EVENT_IN_FOLLOWING:
			 	if(status.info.dt != ongoingRecData.est) { //no margins present for nordig pvr
			 		Log.d(Tag, "updating time for recording ");
					//update recordings contract provider
					String where =  IRecordingsContract.C_RECORDING_ID + "=?";
					String[] whereArgs = {Integer.toString(ongoingRecData.recordId)};
					ContentValues updateValues = new ContentValues();
					updateValues.put(IRecordingsContract.C_STARTTIME, status.info.dt);
					updateValues.put(IRecordingsContract.C_DURATION, status.info.Duration);
					updateValues.put(IRecordingsContract.C_EIT_SOURCE, EITSource.EIT_SOURCE_PF.ordinal());
					updateValues.put(IRecordingsContract.C_EIT_VERSION, -1);	//let other fields get updated..
					updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
					int retval = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings,
					updateValues, where, whereArgs);
					if(retval != 1) {
					  Log.e(Tag, "error in updating start time !!--we will wait till the start time.. ?");
					}else{
					    ongoingRecData = new RecordData(ongoingRecData.recordId,mContext);
					}
			 	}
				if(timenow < (status.info.dt - 5)) {		//threshold of 5 seconds to avoid switching..
					Log.d(Tag, "start time is later..lets go back" + ongoingRecData.recordId);
					currentState = STATE_IDLE;
					finishRecHandler.post(finishRecRunnable);
				} else {
				 	if(ongoingRecData.eet > timenow) {
						handler.removeCallbacks(eitRunnable);
						handler.postDelayed(eitRunnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
						Log.d(Tag,"eitRunnable: Recording will be checked in seconds 1 ->" +  (ongoingRecData.eet - timenow));
					} else {
						Log.e(Tag, "event in following event till end time ");
						updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_EVENT_NOT_TRANSMITTED, true, false);
					}
				}
				break;
			case EVENT_IN_PRESENT:
				//update recordings contract provider
				String where =  IRecordingsContract.C_RECORDING_ID + "=?";
				String[] whereArgs = {Integer.toString(ongoingRecData.recordId)};
				ContentValues updateValues = new ContentValues();
				updateValues.put(IRecordingsContract.C_STARTTIME, status.info.dt);
				updateValues.put(IRecordingsContract.C_DURATION, status.info.Duration);
				updateValues.put(IRecordingsContract.C_EIT_SOURCE, EITSource.EIT_SOURCE_PF.ordinal());
				updateValues.put(IRecordingsContract.C_EIT_VERSION, -1);	//let other fields get updated..
				updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
				ongoingRecData.eet = status.info.dt + status.info.Duration; //no margins for nordig PVR..
				int retval = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings,
				updateValues, where, whereArgs);
				if(retval != 1) {
					Log.e(Tag, "error in updating start time !!--we will wait till the start time.. 4?");
				}
				currentState = STATE_RECORDING_STARTING;
				startRecording();
				handler.removeCallbacks(eitRunnable);
				handler.postDelayed(eitRunnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
				Log.d(Tag,"eitRunnable: Recording will be checked in seconds 2 ->" +  (ongoingRecData.eet - timenow));
				break;
			 default:
			        currentState = STATE_RECORDING_STARTING_NORDIG_NO_EVENT;
				startRecording();
				handler.removeCallbacks(eitRunnable);
				handler.postDelayed(eitRunnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
				Log.d(Tag,"eitRunnable: Recording will be checked in seconds 2 ->" +  (ongoingRecData.eet - timenow));
				break;
			 }
		  	 break;
		 case STATE_RECORDING_EVENT:
			ITvMediaStream mediaStream = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaStream();
			if(mediaStream !=null) {
				switch(status.eitStatus) {
				case EVENT_IN_PRESENT:
					long eet = status.info.dt + status.info.Duration;
					if(eet != ongoingRecData.eet) { //no margins present for nordig pvr
						Log.d(Tag, "updating duration for recording ");
						//update recordings contract provider
						String where =  IRecordingsContract.C_RECORDING_ID + "=?";
						String[] whereArgs = {Integer.toString(ongoingRecData.recordId)};
						ContentValues updateValues = new ContentValues();
						updateValues.put(IRecordingsContract.C_DURATION, status.info.Duration);
						updateValues.put(IRecordingsContract.C_EIT_SOURCE, EITSource.EIT_SOURCE_PF.ordinal());
						//updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag); -- we want ChangeOngoingRecParams to happen..
						int retval = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings,
						updateValues, where, whereArgs);
						if(retval != 1) {
						  Log.e(Tag, "error in updating duration !!--we will wait till the original duration.. ?");
						}
			 		} else {
						if(ongoingRecData.eet > timenow ) {
							handler.removeCallbacks(eitRunnable);
							handler.postDelayed(eitRunnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
							Log.d(Tag,"eitRunnable: Recording will be checked in seconds 3 ->" +  (ongoingRecData.eet - timenow));
						} else {
						   	if(isNextRecordingReady() ) {
								Log.d(Tag, "eitRunnable : Next Recording is ready ");
								endRecording(true);
						   	} else {
							   	if((ongoingRecData.eet + (4 * 60 * 60 * MILLIS_IN_SECOND)) > timenow) {
							   		handler.removeCallbacks(eitRunnable);
									handler.postDelayed(eitRunnable,10*MILLIS_IN_SECOND);
							   	} else {
							   		endRecording(false);
							   	}
						   	}
						}
			 		}
					break;
				case EIT_NOT_ARRIVED:
					if(isNextRecordingReady() ) {
						Log.d(Tag, "eitRunnable : Next Recording is ready ");
						endRecording(true);
					} else {
						if((ongoingRecData.eet + (4 * 60 * 60 * MILLIS_IN_SECOND)) > timenow) {
							handler.removeCallbacks(eitRunnable);
							handler.postDelayed(eitRunnable,10*MILLIS_IN_SECOND);
						} else {
							endRecording(false);
						}
					}
					break;
				default:
					endRecording(false);
					break;
				}
			}
			break;
		    case STATE_RECORDING_NORDIG_NO_EVENT:
		        switch(status.eitStatus) {
		            case EIT_NOT_ARRIVED:
		                if(isNextRecordingReady() ) {
		                    Log.d(Tag, "eitRunnable :state STATE_RECORDING_NORDIG_NO_EVENT: Next Recording is ready ");
		                    endRecording(true);
		                 } else {
					if((ongoingRecData.eet + (4 * 60 * 60 * MILLIS_IN_SECOND)) > timenow) {
						handler.removeCallbacks(eitRunnable);
						handler.postDelayed(eitRunnable,10*MILLIS_IN_SECOND);
					} else {
						endRecording(false);
					}
				  }
		                break;
		            case EVENT_IN_PRESENT:
		            case EVENT_IN_FOLLOWING:
		            case EVENT_IS_NOT_PRESENT:
		                if(ongoingRecData.eet <= timenow) {
		                    endRecording(false);
		                }
		                else{
		                    handler.removeCallbacks(eitRunnable);
		                    handler.postDelayed(eitRunnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
		                    Log.d(Tag, "eitRunnable :state STATE_RECORDING_NORDIG_NO_EVENT: Recording will stop in " + (ongoingRecData.eet - timenow) );
		                }
		                break;
		            default:
		                break;
		        }
		        break;
		    case STATE_RECORDING_STARTING:
		    case STATE_RECORDING_STARTING_NORDIG_NO_EVENT:
		        if(ongoingRecData.eet <= timenow) {
		              endRecording(false);
		         }
		        break;
		  }
	  }
  };

  private void RegisterOnMediaStreamChangeListener()
  {
	  if(NordigPVRSupported(ongoingRecData)==true) {
		 // Log.d(Tag, "RegisterOnMediaStreamChangeListener called");
		  try {
			  ITvMediaStream tvms = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaStream();
			  tvms.registerCallbackListener((IOnMediaStreamChangeListener) mMediaStreamChangeListener);
		  } catch(Exception e) {
			  Log.d(Tag,"Caught exception in RegisterOnMediaStreamChangeListener "+e.toString());
		  }
	  }
  }

  class MediaStreamChangeListenerClass extends IOnMediaStreamChangeListener {
	@Override
	public void onMediaStreamChanged(int property_changed) {
	  Log.d(Tag,"onMediaStreamChanged " + property_changed);
	  if(property_changed == EIT_CHANGED) {
		  handler.removeCallbacks(eitRunnable);
		  handler.post(eitRunnable);
	  }
	}
  }

  public class PvrRecordListenerClass extends IonTvRecordControlCallback {

   @Override
    public void onTimeshiftStatus(int arg0)  {
      Log.d(Tag," onTimeshiftStatus : Status " + arg0);
      handler.post(new HandleTimeshiftNotifications(arg0));
    }

    @Override
    public void onTsbCopyDone()
    {
      //Log.d(Tag," onTsbCopyDone" );
      isTimeShiftCopyDone = true;
    }

    @Override
    public void onTimeshiftPlaybackStatus(int arg0)  {
      // TODO Auto-generated method stub

    }

    @Override
    public void onTadStatus(int arg0)  {
      // TODO Auto-generated method stub

    }

	@Override
	public void onRecordingStatus(int status)  {
	      Log.d(Tag," onRecordingStatus : Status " + status);
	      handler.post(new HandleRecordingNotifications(status));
	}

    @Override
    public void onRecordPlaybackStatus(int arg0)  {
      // TODO Auto-generated method stub
    }

    @Override
    public void licenseCheckStatus(boolean arg0)  {
      // TODO Auto-generated method stub
    }

    @Override
    public void onMinimumDataAvailable(){
      // TODO Auto-generated method stub
     // Log.d(Tag, "onMinimumDataAvailable");
      handler.post(new MinDataAvailableRunnable());
    }
    /*
      @Override
      public void onMaxCircularBufferReached() throws RemoteException {
        // TODO Auto-generated method stub
      } */

  }

  class MinDataAvailableRunnable implements Runnable {
	public void run() {
	      if(ongoingRecData != null)
	      {
	        String where = IRecordingsContract.C_RECORDING_ID + " = ? ";
	        String[] whereArgs = { Integer.toString(ongoingRecData.recordId) };
	        ContentValues updateValues = new ContentValues();

	        updateValues.put(IRecordingsContract.C_IS_PARTIAL, true);
	        updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
	        int updateResult = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, updateValues,
	        where, whereArgs);
	        if(0 >= updateResult)
	        {
	          Log.e(Tag, "record update failed in onMinimumDataAvailable");
	        }
	      } else {
	        Log.d(Tag, "onMinimumDataAvailable ongoingRecData is null");
	      }
	}
};

  class HandleTimeshiftNotifications implements Runnable {
    private int notification;

    public HandleTimeshiftNotifications(int notif) {
      notification = notif;
    }

    @Override
    public void run() {
      Log.d(Tag," run: HandleTimeshiftNotifications " + notification);
      switch(notification) {
      case BcstConstants.TIMESHIFT_STOPPED:
        if(isRecordingPending)
        {
          Log.d(Tag,"Start the pending recording");
          checkForStartRecording();
          isRecordingPending = false;
        }
        break;
      default:
        break;
      }
    }
  };

  class HandleRecordingNotifications implements Runnable {
    private int notification;

    public HandleRecordingNotifications(int notif) {
      notification = notif;
    }

  @Override
    public void run() {
    Log.d(Tag," run: HandleRecordingNotifications " + notification);
      switch(notification) {
      case BcstConstants.RECORDING_STARTED:
        if(null != ongoingRecData)
        {
            if (ongoingRecData.isIPEPG == 0) {
                Log.d(Tag," REcording is from bcepg with eventId : " +ongoingRecData.eventId);
                if(ongoingRecData.eventId == -1) {
                currentState = STATE_RECORDING_MANUAL;
                mEpgCache.registerListener(mRecordingInfo);
                // Query EPG data
                mEpgCache.queryNowNextData(ongoingRecData.channelId);
                } else {
                    if(STATE_RECORDING_STARTING_NORDIG_NO_EVENT == currentState){
                        /*Incase of Nordig, if event is not availabe in EIT P/F duing start of the recording, then recording should
                        **happen for last updated duration for that event
                        */
                        currentState = STATE_RECORDING_NORDIG_NO_EVENT;
                    }
                    else{
                        currentState = STATE_RECORDING_EVENT;
                    }
                }
            } else {
            Log.d(Tag," REcording is from IPepg"+ongoingRecData.eventId);
                if(PlayTvDiversity.isIPEpgAutoMarginSupported()){
                    if(ongoingRecData.eventId == -1) {
                        currentState = STATE_RECORDING_MANUAL;
                    }
                    else{
                        currentState = STATE_RECORDING_EVENT;
                    }
                }
                else{
                    currentState = STATE_RECORDING_MANUAL;
                }
            }
          /*To apply subtitle PID, PMT should be received, so reapply the subtitle index again here*/
            handler.post(new MediaChangeRunnable(MEDIA_CHECK_AND_APPLY_CHANGE));
        }
        else
        {
          Log.d(Tag, "Skipping RECORDING_STARTED");
        }
        break;
      case BcstConstants.RECORDING_FINISHED:
        isTimeShiftCopyDone= true;
        if(isRecordingPending)
        {
          Log.d(Tag,"Start the pending recording");
          checkForStartRecording();
          isRecordingPending = false;
        }
        else if((null != ongoingRecData)/*&&(currentState == STATE_RECORDING_STOPPING)*/)
        {
		  currentState = STATE_IDLE;
          onRecFinished();

        }
        else
        {
        	currentState = STATE_IDLE;
          	Log.d(Tag, "Skipping RECORDING_FINISHED");
        }
        break;
      case BcstConstants.RECORDING_ERROR_HDDFULL:
        Log.d(Tag, "RECORDING_ERROR_HDDFULL");
        if(ongoingRecData != null)
        	updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_DISKFULL, false, false);
        else
        	Log.d(Tag, "ongoing rec data is null for recordingStatus RECORDING_ERROR_HDDFULL");
        break;

		case BcstConstants.RECORDING_ERROR_HDDNOTCONNECTED:
        Log.d(Tag, "RECORDING_ERROR_HDDNOTCONNECTED");
        if(ongoingRecData != null)
        	updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_NODISK, false, false);
        else
        	Log.d(Tag, "ongoing rec data is null for recordingStatus RECORDING_ERROR_HDDNOTCONNECTED");
        break;
      case BcstConstants.RECORDING_ERROR_SYSTEM:
        Log.d(Tag, "RECORDING_ERROR_SYSTEM");
        if(ongoingRecData != null)
        	updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_SYSTEM, false, false);
        else
        	Log.d(Tag, "ongoing rec data is null for recordingStatus RECORDING_ERROR_SYSTEM");
        break;
      case BcstConstants.RECORDING_ERROR_CICAM:
        Log.d(Tag, "RECORDING_ERROR_CICAM");
        if(ongoingRecData != null)
        	updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_NO_CAM, false, false);
        else
        	Log.d(Tag, "ongoing rec data is null for recordingStatus RECORDING_ERROR_CICAM");
        break;
      }
    }
  };

  // get dual tuner support values fron TvSettings
  /*final PersistentStorageCallBacks.Stub mSettingsBinder = new PersistentStorageCallBacks.Stub()
  {
      @Override
      public void OnUpdateListener(int property, int value)
          throws RemoteException {
        Log.d(Tag, "Update : Database Updated for Property - " + property + "; Value - " + value );
        if((property == TvSettingsConstants.OPTWOTUNERS) || (property == TvSettingsConstants.LASTSELECTEDTUNER))
        {
          //handleTvsettingsParams();
        }
      }
  };*/



 /* public void onDestroy() {
    if (recObserver != null) {
      mContext.getContentResolver().unregisterContentObserver(recObserver);
      Log.d(Tag, "UnRegistered recObserver");
    }
    PlayTvHDDUtils.getInstance(this).removeHDDListener(this, Tag);
    if(recordinstance != null)
    {
    	recordinstance.unregisterListenerCallback(PvrRecordListener);
    	recordinstance = null;
    }

	UnRegisterTVContentObserver();
    //PlayTvApplication.getInstance().recService = null; //TODO:TIF:: not required
  }*/  //TODO:TIF:is this required


  private int getVersion() {
    if(currentVersion == -1) {
      String[] projection = {"Version"};
      String selection = "_id == ?"; //key is integer..
      String[] selectionArgs = {String.valueOf(1)};
      Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Version, projection, selection,
      selectionArgs, null);
      if( (c != null) && (c.getCount() > 0) && (c.moveToFirst() )) {
        isVersionNull = false;
        //Log.d(Tag, "getVersion : " + c.getInt(0));
        currentVersion =  c.getInt(0);
      }
      else
      {
        Log.d(Tag, "getVersion null");
      }
      if(c != null)
        c.close();
    }
    //Log.d(Tag, "currentVersion is :"+currentVersion);
    return currentVersion;
  }

  private void setVersion(int version) {
    //Log.d(Tag, "setVersion " + version);
    ContentValues values = new ContentValues();
    values.put("_id", 1);
    values.put("Version", version);
    values.put(IRecordingsContract.C_CHANGE_ID, Tag);

    if(isVersionNull) {
      mContext.getContentResolver().insert(IRecordingsContract.CONTENT_URI_Version, values);
      isVersionNull = false;
    } else {
      String where = "_id == ?";
      String[] selectionArgs = {String.valueOf(1)};
      mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Version, values, where, selectionArgs);
    }
    currentVersion = version;
  }
  public void NodeChanged()
  {
    int CurrentVer = getVersion();// from version table
    // get all changed/updated rec from recordings db.
    // query rec db where version > CurrentVer
    Log.d(Tag, "Node Changed " + CurrentVer);
    String[] RECORD_PROJ = new String[] {
      IRecordingsContract.C_RECORDING_ID /*0*/, IRecordingsContract.C_RECORDING_TYPE /*1*/,
      IRecordingsContract.C_EFFECTIVE_START_TIME /*2*/, IRecordingsContract.C_EFFECTIVE_END_TIME /*3*/,
      IRecordingsContract.C_VERSION /*4*/, IRecordingsContract.C_CHANNELID /*5*/,
      IRecordingsContract.C_EVENT_ID /*6*/, IRecordingsContract.C_MARGIN_END /*7*/, IRecordingsContract.C_MARGIN_START /*8*/,
      IRecordingsContract.C_ISIPEPG_RECORDING /*9*/, IRecordingsContract.C_RECORDING_NAME /*10*/};
    String RECORD_SELECT = IRecordingsContract.C_VERSION + " > ?";
    String[] RECORD_SELECT_ARGS = { Integer.toString(CurrentVer) };
    String RECORD_ORDERBY = IRecordingsContract.C_VERSION + " ASC";

    Cursor rec_iter = mContext.getContentResolver().query(
    IRecordingsContract.CONTENT_URI_Recordings, RECORD_PROJ,
    RECORD_SELECT, RECORD_SELECT_ARGS, RECORD_ORDERBY);
    if ((rec_iter != null) && (rec_iter.getCount() > 0) && (rec_iter.moveToFirst()))
    {
      int version = 0;
      Log.d(Tag, "Node Changed count " + rec_iter.getCount());
      if(mountPath==null){
    	  mountPath=PlayTvHDDUtils.getInstance(mContext).queryMountPath();
      }
      do
      {
        RecordData record = new RecordData(rec_iter.getInt(0), rec_iter.getInt(5),rec_iter.getLong(2),rec_iter.getLong(3),
        									rec_iter.getInt(4), rec_type[rec_iter.getInt(1)], rec_iter.getInt(6), rec_iter.getInt(7), rec_iter.getInt(8), rec_iter.getInt(9),
									      rec_iter.getString(10),mContext);
        Log.d(Tag, "record " + record.recordId + "," + record.recordingType.toString());
        Log.d(Tag, "Mukta eventId : " + record.eventId + " , endUserMargin : "+record.endUserMargin+ ", isIPEPG : "+record.isIPEPG);
        if( (ongoingRecData != null) && (record.recordId == ongoingRecData.recordId) )
        {
          ChangeOngoingRecParams(record);
        }
        else
        {
          switch (record.recordingType)
          {
          case RECORDING_OTR:
            if(ongoingRecData == null) {
              if(mountPath != null)
              {
                Log.d(Tag, " mountPath :" + mountPath);
                getLock();
                PrepareForRecording(record, false);
              }
              else
              {
                Log.d(Tag, " HDD is not paired: Raise intent to format HDD");
                //FormatHdd();
              }
            }

            break;

          case AUTO_PVR_SCHEDULED:
            //Auto PVR not supported
            //AutoPVR.getInstance().registerAutoPVREvent(record, mContext);
            break;

          case RECORDING_SCHEDULED:
          case RECORDING_MANUAL:
        	  Log.d(Tag, "mNextRecordingId : "+mNextRecordingId+ ", mNextRecordingEST : "+mNextRecordingEST);
        	  Log.d(Tag, "record.recordId : "+record.recordId+ ", record.est : "+record.est);
        	  if(((mNextRecordingId == record.recordId)||(mNextRecordingId == -1)||(record.est < mNextRecordingEST))&&(ongoingRecData==null))
        		  PrepareForRecording(record, false);
        	  else
        		  Log.d(Tag,"Re-shuffling of first alarm is not needed");
            break;
          case RECORDING_USER_STOPPED:
            Log.d(Tag, " RECORDING_USER_STOPPED ");
            if(record.recordId == mNextRecordingId)
            	isRecordingPending = false;
            endRecording(true);
            break;
          case RECORDING_USER_DELETED:
            Log.d(Tag, " RECORDING_USER_DELETED ");
            if(record.recordId == mNextRecordingId)
            {
              isRecordingPending = false;
          	  HandleRecordingFinished(record);
            } else if(mountPath != null)
            {
              String where = IRecordingsContract.C_RECORDING_ID + " = ? ";
              String[] whereArgs = { Integer.toString(record.recordId)};
              try{
                TvMediaPlayer mMediaPlayer = null;
                mMediaPlayer = TvMediaPlayer.getTvTunerMediaPlayer();
		    ITvMediaRecordControl lRecordInstance = mMediaPlayer.getTvMediaPlayerContext().getTvMediaRecordControl();
                if(lRecordInstance!=null)
                {
                  lRecordInstance.deleteRecording(record.recordId, mountPath);
                  int del_res = mContext.getContentResolver().delete(IRecordingsContract.CONTENT_URI_Recordings, where, whereArgs);
                  Log.d(Tag, "deletion of "+del_res+" record from node changed");
                }
              } catch(Exception e){
                Log.e(Tag, "exception in deleteRecording"+ e.toString());
              }
            }
            else
            {
            	Log.d(Tag, "mountpath is null for deleting record: "+ record.recordId);
            }
            break;
          default:
            Log.w(Tag, "rec type need not be handled " + record.recordingType.toString());
            break;
          }
        }
        version = record.version;
        rec_iter.moveToNext();
      } while (!rec_iter.isAfterLast());
      setVersion(version);
    }
    else
    {
      Log.e(Tag, "cursor empty ");
    }
    if(rec_iter != null)
      rec_iter.close();
  }

  /* for ongoing recording end margin can be stopped and it can be stopped,deleted..*/
  void ChangeOngoingRecParams(RecordData record)
  {
	//Log.d(Tag, "ChangeOngoingRecParams ");
	ongoingRecData = record;
    if((record.recordingType == RecordingType.RECORDING_USER_STOPPED) ||
        (record.recordingType == RecordingType.RECORDING_USER_DELETED))
    {
      Log.d(Tag, "ChangeOngoingRecParams : endRecording called");
      endRecording(true);
    } else if(record.recordingType == RecordingType.RECORDING_ONGOING) {
      long timenow = System.currentTimeMillis()/1000;
	if(false == NordigPVRSupported(ongoingRecData)) {
	      if(record.eet > timenow)
	      {
	        //remove runnable and post again
	        handler.removeCallbacks(runnable);
	        handler.postDelayed(runnable, (record.eet - timenow) *  MILLIS_IN_SECOND );
	        Log.d(Tag,"Update recording  end time,  recording will stop in seconds -> " + (record.eet - timenow));
	      }
	      else
	      {
	        Log.d(Tag,"Stop the recording immediately");
		  handler.removeCallbacks(runnable);
	        endRecording(false);
	      }
	} else {
		switch(currentState) {
		case STATE_IDLE:
		case STATE_RECORDING_STOPPING:
			Log.d(Tag, "ignoring ongoing rec change" + currentState);
			break;
		case STATE_WAITING_FOR_EVENT:
			if(timenow < (ongoingRecData.est - 5)) {		//threshold of 5 seconds to avoid switching..
				Log.d(Tag, "start time is later..lets go back" + ongoingRecData.recordId);
				currentState = STATE_IDLE;
				finishRecHandler.post(finishRecRunnable);
			} else {
			 	if(ongoingRecData.eet > timenow) {
					handler.removeCallbacks(eitRunnable);
					handler.postDelayed(eitRunnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
					Log.d(Tag,"eitRunnable: Recording will be checked in seconds 1 ->" +  (ongoingRecData.eet - timenow));
				} else {
					Log.e(Tag, "event in waiting till it is changed.. ");
					updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_EVENT_NOT_TRANSMITTED, true, false);
				}
			}
			break;
		case STATE_RECORDING_AUTO_MARGIN:
		      if(record.eet > timenow)
            	      {
            	        //remove runnable and post again
            	        handler.removeCallbacks(runnable);
            	        handler.postDelayed(runnable, (record.eet - timenow) *  MILLIS_IN_SECOND );
            	        Log.d(Tag,"Update recording  end time, state STATE_RECORDING_AUTO_MARGIN,  recording will stop in seconds -> " + (record.eet - timenow));
            	      }
            	      else
            	      {
            	        Log.d(Tag,"Stop the recording immediately");
            		  handler.removeCallbacks(runnable);
            	        endRecording(false);
            	      }
		        break;
		case STATE_RECORDING_EVENT:
		case STATE_RECORDING_MANUAL:
		case STATE_RECORDING_STARTING:
		case STATE_RECORDING_STARTING_NORDIG_NO_EVENT:
		case STATE_RECORDING_NORDIG_NO_EVENT:
			if(record.eet > timenow)
		      {
		        //remove eitrunnable and post again
		        handler.removeCallbacks(eitRunnable);
		        handler.postDelayed(eitRunnable, (record.eet - timenow) *  MILLIS_IN_SECOND );
		        Log.d(Tag,"Nordig - Update recording  end time,  recording will stop in seconds -> " + (record.eet - timenow));
		      }
		      else
		      {
		          handler.removeCallbacks(eitRunnable);
		          Log.d(Tag,"Nordig - Stop the recording immediately");
		          endRecording(false);
		      }
			break;
		}
	}
    }else {
      Log.d(Tag, "not ongoing recording for changing " + record.recordingType);
    }
  }

  private void getLock()

  {
    if(!lock.isHeld())
    {
      Log.d(Tag, "acquiring lock from RecService");
      lock.acquire();
    }
  }
  private void releaseLock()
  {
    if(lock.isHeld())
    {
      Log.d(Tag, "Releasing lock from RecService");
      lock.release();
    }
  }
  private void getShutDownInProgressLock()
  {
    if(!mShutDownInProgresslock.isHeld())
    {
      Log.d(Tag, "acquiring ShutDownInProgressLock from RecService");
      mShutDownInProgresslock.acquire();
    }
  }
  private void releaseShutDownInProgressLock()
  {
    if(mShutDownInProgresslock.isHeld())
    {
      Log.d(Tag, "Releasing ShutDownInProgressLock from RecService");
      mShutDownInProgresslock.release();
    }
  }
  /**
    * @param record
    */
  public void PrepareForRecording(RecordData record, boolean isPowerOnSync)
  {
    long timenow = System.currentTimeMillis() / 1000;
    Log.d(Tag, "prepare for rec id:"+record.recordId+", record.est : " + record.est + ", timenow : " + timenow);
	long mNextAlarmTime = Long.MAX_VALUE;
    if (timenow >= record.eet)// don't write eet - two_mins as eet can be less than 2 mins
    {
      Log.d(Tag, "too late to record in prepare");
      /*((-1 == mNextRecordingId) && (null == ongoingRecData)) - Added to schedule next recording if current one is expired*/
      if((record.recordId == mNextRecordingId) ||((-1 == mNextRecordingId) && (null == ongoingRecData))){
    	  Log.d(Tag, "too late, clearing next data info.");
    	  mNextRecordingId = -1;
    	  mNextRecordingEST = Long.MAX_VALUE;
    	  ongoingRecData=record;
      }
      updateRecordForError(record.recordId, RecordingError.REC_ERROR_NOPOWER, true,false);
      return;
    }
    if((currentState != STATE_IDLE)&&(ongoingRecData!=null)&&(ongoingRecData.recordId != record.recordId))
    {
      Log.d(Tag,"recording ongoing..cannot prepare " + ongoingRecData.recordId); //may this recording fail..
      return;
    }
    if(mCurrentPowerState!=PowerStates.POWER_STATE_FULL_SYSTEM_START && mCurrentPowerState!=PowerStates.POWER_STATE_SEMI_STANDBY){
	Log.d(Tag,"Holdinglock as prepare is postponed"+record.recordId);
	getLock();
	PreparePostPonedRecordId=record.recordId;
      return;
    }
	recError = RecordingError.REC_ERROR_NONE;
    mNextRecordingId = record.recordId;
    mNextRecordingEST = record.est;
    rec_allocator.setNextRecording(record);
    Log.d(Tag, "currentState in PrepareForRecording: "+currentState);
    if(timenow >= record.est) {
      Log.d(Tag,"Starting Recording");
      getLock();
  	ongoingRecData = record;
      if( (mountPath != null) )
      {
    	//if (true /*!PlayTvApplication.getInstance().getNonInterruptableStatus()*/) // TODO:TIF:: changes to be made so that PlayTvApplication is not used
    	//{
    	  initRecording(record);
	      if((System.currentTimeMillis()/1000) > (ongoingRecData.est+5)) {
	       	isPartial = true;
	       	if(isPowerOnSync)
	       		recError = RecordingError.REC_ERROR_POWERINTERRUPTION;
	       	else
	       		recError = RecordingError.REC_ERROR_CONFLICT;
	      }
    	//}
    	/*else
    	{
    		Log.e(Tag, "Show RecordingError.REC_ERROR_TV_BUSY");
			recError = RecordingError.REC_ERROR_TV_BUSY;
    		updateRecordForError(record.recordId,RecordingError.REC_ERROR_TV_BUSY, true, true);
    	}*/
      } else {
			Log.d(Tag, " HDD is not connected, mountPath is null");
			recError = RecordingError.REC_ERROR_NODISK;
			updateRecordForError(record.recordId, RecordingError.REC_ERROR_NODISK, true, true);
      }
    }
    else {
	    if( (timenow + ONE_MIN) >= record.est) //don't write est-1min as est can be less than 1 min
	    {
			//less than 1 min remaining
			getLock();
			mNextAlarmTime = record.est;
			Log.d(Tag,"Adding zero minute before recording alarm");
	    }
	    else if( (timenow + TWO_MINS) >= record.est) //dont write est - 2mins
	    {
	    	getLock();
	        mNextAlarmTime = record.est - ONE_MIN;
	        Log.d(Tag,"Adding one minute before recording alarm");
		//TODO:TIF:PlayTvApplication not to be used
	      if(/*(!PlayTvApplication.getInstance().getNonInterruptableStatus())*/true && (PowerStates.POWER_STATE_FULL_SYSTEM_START == mCurrentPowerState))
	      {
	        Boolean isSameChannel;
	        int currChannel = PlayTvUtils.getCurrentChannel();
	        if(record.channelId == currChannel)
	        isSameChannel = true;
	        else
	        isSameChannel = false;
	        Intent twoMinToRec = new Intent("org.droidtv.action.RECORD_DIALOG");
	        twoMinToRec.putExtra("isSameChannel", isSameChannel);
	        twoMinToRec.putExtra("recId", record.recordId);
	        twoMinToRec.putExtra("channelId", record.channelId);
	        twoMinToRec.putExtra("est", record.est);
	        twoMinToRec.putExtra("eet", record.eet);
	        switch(record.recordingType)
	        {
	             case RECORDING_SCHEDULED:
	                  twoMinToRec.putExtra("recordingType", record.recordingType.RECORDING_SCHEDULED.ordinal());
	             break;
	             case  RECORDING_MANUAL:
	                  twoMinToRec.putExtra("recordingType", record.recordingType.RECORDING_MANUAL.ordinal());
	             break;
	             default:
	                   Log.d(Tag,"Entered the default case");
	             break;
	        }
	        twoMinToRec.putExtra("recordingName", record.recordingName);
	        twoMinToRec.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
	        mContext.startActivity(twoMinToRec);//TODO:TIF: needs to be handled
	      } else {
	    	  Log.d(Tag, "Not showing 2 mins before recording pop up as in non-interruptible state or set is not in full-on state.");
	      }
	    }
	    else if( (timenow + TEN_MINS) >= record.est)
	    {
			// Format HDD
			if((mountPath == null) && (PowerStates.POWER_STATE_FULL_SYSTEM_START == mCurrentPowerState)) {
				Log.d(Tag, " 10mins to recording -: Check HDD status ");
				FormatHdd();
			}
			getLock();
	        mNextAlarmTime = record.est - TWO_MINS;
	        Log.d(Tag,"Adding two minute before recording alarm");
	    }
	    else if( (timenow + TWENTY_MINS) >= record.est)
	    {
	    	getLock();
	        mNextAlarmTime = record.est - TEN_MINS;
	        Log.d(Tag,"Adding ten minute before recording alarm");
	    }
	    else
	    {
	        mNextAlarmTime = record.est - TWENTY_MINS;
	        Log.d(Tag,"Adding twenty minute before recording alarm");
	        releaseLock();
	    }
	    AddAlarm(record.recordId, mNextAlarmTime);
    }
  }

  void HandleRecordingFinished(RecordData record)
  {
    //make ongoing recording as new
    Log.d(Tag, "HandleRecordingFinished");
	mNextRecordingId = -1;
	mNextRecordingEST = Long.MAX_VALUE;
	isRecordingPending = false;
    String where = IRecordingsContract.C_RECORDING_ID + " = ?";
    String[] whereArgs = { Integer.toString(record.recordId) };
    if(record.recordingType == RecordingType.RECORDING_USER_DELETED) {
      if(mountPath != null)
      {
        Log.d(Tag, "mukta RECORDING_USER_DELETED mountPath:" +mountPath);
        try {
          TvMediaPlayer mMediaPlayer = null;
          mMediaPlayer = TvMediaPlayer.getTvTunerMediaPlayer();
	    ITvMediaRecordControl lRecordInstance = mMediaPlayer.getTvMediaPlayerContext().getTvMediaRecordControl();
          if(lRecordInstance!=null)
          {
            lRecordInstance.deleteRecording(record.recordId, mountPath);
            int del_res = mContext.getContentResolver().delete(IRecordingsContract.CONTENT_URI_Recordings, where, whereArgs);
            Log.d(Tag, "HandleRecordingFinished deleted "+del_res+" Recordings.");
          }
        }
        catch(Exception e){
          Log.e(Tag, "exception in deleteRecording"+ e.toString());
        }
      }
      //cancel alarm set for this recording.
		if(pendingIntent != null){
		    AlarmManager alarmMgr = (AlarmManager)mContext.getSystemService(Context.ALARM_SERVICE);
			alarmMgr.cancel(pendingIntent);
		}
    }

	if ((record.recordingType == RecordingType.RECORDING_ONGOING) && (NordigPVRSupported(record))) {
		// update recording to scheduled, so it will be processed later
		ContentValues values = new ContentValues();
		values.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_SCHEDULED.ordinal());
		values.put(IRecordingsContract.C_CHANGE_ID, Tag);
		String selc = IRecordingsContract.C_RECORDING_ID + " = " + record.recordId;
		int updateResult = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, values, selc, null);
		if (updateResult <= 0) {
			Log.d(Tag, "Error while updating recording type to scheduled for nordigPVR");
		}
	}
	
    //add to validity check record array.
    if(record.recordingType == RecordingType.RECORDING_NEW) {
    	AddRecordForValidityCheck(record);
    }
    //make recordings as failed for recording conflict
    long timenow = System.currentTimeMillis()/1000;
    String where1 = "(" + IRecordingsContract.C_RECORDING_TYPE + " = "
    +IRecordingsContract.RecordingType.RECORDING_SCHEDULED.ordinal()+" OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = "
    +IRecordingsContract.RecordingType.RECORDING_MANUAL.ordinal() +" OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = "
    +IRecordingsContract.RecordingType.RECORDING_OTR.ordinal()+") AND ( (" +
    IRecordingsContract.C_EFFECTIVE_END_TIME + ") <= "+timenow+")";
    ContentValues failRecValues = new ContentValues();
    failRecValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_FAILED.ordinal());
    failRecValues.put(IRecordingsContract.C_IS_PARTIAL, false);
    failRecValues.put(IRecordingsContract.C_RECORDING_ERROR, RecordingError.REC_ERROR_CONFLICT.ordinal());
    failRecValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
    int updateResult = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, failRecValues, where1, null);
    Log.d(Tag, "updated "+updateResult+" records to failed in HandleRecordingFinished");
	if(updateResult>0){
		recLog.logFailedRecording(record.recordId, RecordingError.REC_ERROR_CONFLICT );
	}

    //prepare for next recording
    ongoingRecData = null;

    String[] projection = {	IRecordingsContract.C_CHANNELID,					// 0
						IRecordingsContract.C_EFFECTIVE_START_TIME,		// 1
      						IRecordingsContract.C_EFFECTIVE_END_TIME,			// 2
      						IRecordingsContract.C_RECORDING_TYPE,				// 3
      						IRecordingsContract.C_VERSION, 					// 4
      						IRecordingsContract.C_RECORDING_ID,				// 5
      						IRecordingsContract.C_EVENT_ID,					// 6
      						IRecordingsContract.C_ISIPEPG_RECORDING,			// 7
      						IRecordingsContract.C_RECORDING_NAME,				// 8
      						IRecordingsContract.C_MARGIN_START,				// 9
      						IRecordingsContract.C_MARGIN_END					// 10
      					  };
    String selection = IRecordingsContract.C_RECORDING_TYPE + " = ? OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = ? OR " +
    IRecordingsContract.C_RECORDING_TYPE + " = ?";
    String[] selectionArgs = {String.valueOf(RecordingType.RECORDING_OTR.ordinal()),
      String.valueOf(RecordingType.RECORDING_SCHEDULED.ordinal()),
      String.valueOf(RecordingType.RECORDING_MANUAL.ordinal())};
    String orderBy = IRecordingsContract.C_EFFECTIVE_START_TIME + " ASC  LIMIT 1";
    Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection,
    selection, selectionArgs, orderBy);

    RecordData nextRecord = null;
    if( (c != null) && (c.getCount() > 0) && (c.moveToFirst() ) ) {
	nextRecord = new RecordData(c.getInt(5), c.getInt(0), c.getLong(1), c.getLong(2), c.getInt(4), rec_type[c.getInt(3)],
								c.getInt(6), c.getInt(10), c.getInt(9), c.getInt(7), c.getString(8), mContext);
    } else {
       ; //nothing - get optimized away
    }
    if(c != null)
    	c.close();
    UnRegisterTVContentObserver();
    if(nextRecord != null) {
      rec_allocator.setNextRecording(nextRecord);
      handler.post(new PrepareRecRunnable(nextRecord));
      //release MPL always as factory needs to be aware of we change channel..
      if(playtvmplayer != null) {
        playtvmplayer.getPlaybackObject().unRegisterListener(this);
        if(recordinstance != null)
        {
       	  recordinstance.unregisterListenerCallback(PvrRecordListener);
       	  recordinstance = null;
        }
	  try {
	    	ITvMediaStream tvms = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaStream();
	    	tvms.unregisterCallbackListener((IOnMediaStreamChangeListener) mMediaStreamChangeListener);
	  } catch (Exception e) {
	    	Log.d(Tag, "unregister in finished exceptional " + e.toString());
	  }
        if(foreground_rec){
       	  factory.releaseMPLInstance(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING, playtvmplayer);
        } else{
       	  factory.releaseMPLInstance(PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING, playtvmplayer);
        }
        playtvmplayer = null;
      }
      if(timenow < nextRecord.est-TWENTY_MINS)
      {
        Log.d(Tag, "HandleRecordingFinished: releasing lock too long for next recording.");
        if(PowerStates.POWER_STATE_SEMI_STANDBY == mCurrentPowerState)
        {
          Log.d(Tag, "HandleRecordingFinished:put device to standby");
          pm.SetState(PowerStates.POWER_STATE_STANDBY);
        }
        releaseLock();
      }
      else {
        Log.d(Tag, "HandleRecordingFinished : holding lock for next recording.");
      }
    }
    else
    {
      rec_allocator.setNextRecording(null);
      Log.d(Tag,"no next recording scheduled : releasing lock.");
      if(playtvmplayer != null) {
	playtvmplayer.getPlaybackObject().unRegisterListener(this);
       if(recordinstance != null)
       {
      		recordinstance.unregisterListenerCallback(PvrRecordListener);
      		recordinstance = null;
       }
	try {
	    	ITvMediaStream tvms = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaStream();
	    	tvms.unregisterCallbackListener((IOnMediaStreamChangeListener) mMediaStreamChangeListener);
	  } catch (Exception e) {
	    	Log.d(Tag, "unregister in finished exceptional2 " + e.toString());
	  }
    	if(foreground_rec){
    	  	factory.releaseMPLInstance(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING, playtvmplayer);
    	} else {
    	  	factory.releaseMPLInstance(PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING, playtvmplayer);
    	}
      }
      playtvmplayer = null;
      if(PowerStates.POWER_STATE_SEMI_STANDBY == mCurrentPowerState)
      {
        Log.d(Tag, "HandleRecordingFinished:put device to standby1");
        pm.SetState(PowerStates.POWER_STATE_STANDBY);
      }
      releaseLock();
    }
  }

	public void initRecording(RecordData record) {
		Log.d(Tag,"initRecording : recording in channel id  " + record.channelId);
		Medium medium, mcurrentmedium;
		Uri uri = TvContract.buildChannelUri(record.channelId);
		UriData mdata=TvURIHelper.parseUri(getContext(), uri);
		medium = TvURIHelper.Medium.fromInteger(mdata.medium);
		int mChannelNumber;
		int mCurrentPurpose = 0;
		dualTunerSupported = factory.IsDualTunerFactoryConfigEnabled(record.medium);
		if(dualTunerSupported){
			foreground_rec=false;
		} else{
			foreground_rec=true;
		}
		if(foreground_rec){
			playtvmplayer = factory.getMPLInstance(mContext, PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING,record.medium, record.presetid);
		}
		else{
			playtvmplayer = factory.getMPLInstance(mContext, PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING,record.medium, record.presetid);
		}

		//playtvmplayer cannot be null as recording is highest priority..
		if(playtvmplayer != null) {
			recordinstance = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaRecordControl();
			if(recordinstance != null)
			{
				recordinstance.registerListenerCallback(PvrRecordListener);
			} else {
				Log.d(Tag,"Recording instance is null..");
			}
			//update recordings contract provider
			long timenw = System.currentTimeMillis()/1000;
			String where =  IRecordingsContract.C_RECORDING_ID + "=?";
			String[] whereArgs = {Integer.toString(ongoingRecData.recordId)};
			ContentValues updateValues = new ContentValues();
			ongoingRecData.recordingType = RecordingType.RECORDING_ONGOING;
			updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_ONGOING.ordinal());
			updateValues.put(IRecordingsContract.C_PROGRAM_NUMBER, ongoingRecData.programNumber);
			updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
			updateValues.put(IRecordingsContract.C_ISRADIO,ongoingRecData.isRadio);
			updateValues.put(IRecordingsContract.C_ACTUAL_START_TIME,timenw);
			int retval = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings,
			updateValues, where, whereArgs);
			if(retval != 1) {
				Log.e(Tag, "error in making recording as ongoing !!--why to make fatal ?");
			}
			mChannelNumber = playtvmplayer.getCurrentChannel() ;
			mcurrentmedium	= playtvmplayer.getCurrentMedium();
			mCurrentPurpose = playtvmplayer.getCurrentPurpose();
			playtvmplayer.getPlaybackObject().registerListener(this);

			Log.d(Tag, " given medium " + medium + " current medium :" + mcurrentmedium + "mChannelNumber "  + mChannelNumber + "record.presetid " + record.presetid + " mCurrentPurpose " + mCurrentPurpose);
			if(dualTunerSupported) {
				Log.d(Tag,"dualTunerSupported  ");
				try {
					currentState = STATE_TUNING;
					playtvmplayer.getPlaybackObject().play(uri);
				} catch(Exception e) {
					Log.d(Tag, "exception while tuning " + e.toString());
				}
				/*Need to do setdatasource again so as to update usetype - BroadcastPlayer will avoid tuning again*/
			}
			else {
				Log.d(Tag,"dualTuner not Supported  ");
				if((medium == mcurrentmedium) && (mChannelNumber == record.presetid) && (0 < (mCurrentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH))) {
					Log.d(Tag,"Single Tuner: Already tuned to same channel :no need to tune again " + mChannelNumber);
					PrepareForStartRecording();
				} else {
					try {
						currentState = STATE_TUNING;
						recLog.logZapSource(record.channelId, ILogger.ChannelZapSource.ZapMethod.RECORDING);
						playtvmplayer.getPlaybackObject().play(uri);
					} catch(Exception e) {
						Log.e(Tag, "exception while tuning " + e.toString());
					}
				}
			}
		}
		else {
			Log.e(Tag, "playtvmplayer should not be null !!!");
			recError = RecordingError.REC_ERROR_TV_BUSY;
			updateRecordForError(record.recordId,RecordingError.REC_ERROR_TV_BUSY, true, true);
		}
	}


	private int getChannelLockStatus(Uri uri) {
		int lChannelLock = -1;
		Cursor lCursor = null;
		try {
			if (uri != null && mContext != null) {
				String[] PROJECTION = { TvContract.Channels.COLUMN_LOCKED };
				lCursor = mContext.getContentResolver().query(uri, PROJECTION,null, null, null);
				if ((lCursor != null) && (lCursor.getCount() > 0)&& (lCursor.moveToFirst())) {
					lChannelLock = lCursor.getInt(lCursor.getColumnIndex(TvContract.Channels.COLUMN_LOCKED));
				} else {
					Log.d(Tag, "getChannelLockStatus lCursor is null");
				}
			} else {
				Log.d(Tag, "getChannelLockStatus uri or mContext is null");
			}
		} catch (Exception e) {
			Log.d(Tag, "Exception in CheckChannelLockStatus");
		} finally {
			if (lCursor != null) {
				lCursor.close();
				lCursor = null;
			}
		}
		return lChannelLock;
	}
 	
  private void PrepareForStartRecording()
  {
    //	String path =  mountPath + "/pvr_" + ongoingRecData.recordId + ".tsl";
    recordinstance = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaRecordControl();
    if(recordinstance != null)
    {
      recordinstance.registerListenerCallback(PvrRecordListener);
      if(true == recordinstance.isRecordingAllowed())
      {
        if(mountPath != null)
        {
          checkForStartRecording();
        }
        else
        {
          Log.d(Tag, "hard disk is not connected to start recording");
        }
      }
      else
      {
        isRecordingPending = true;
        Log.d(Tag,"Already recording in progress, wait untill previous recording stops");
      }
    }
    else
    {
      Log.d(Tag,"Record instance is NULL");
    }
  }

  private void startRecording() {
  	TimeshiftRecording tsRecording  = null; //= TimeshiftRecording.getInstance(); TODO:TIF:to be handled
	if(ongoingRecData != null) {
		Log.d(Tag,"startRecording: mount path : " + mountPath + " Recording id " + ongoingRecData.recordId );

		if((mountPath != null) && (PlayTvHDDUtils.getInstance(mContext).getTotalSize() >= MIN_SIZE_FOR_PVR) &&
				(PlayTvHDDUtils.getInstance(mContext).getFreeSize() >= MIN_SPACE_FOR_PVR)) {
		  if(recordinstance != null) {
			  int mnewmode=BcstConstants.RECORDING_MODE_UNATTENDED;
			  int copyDuration = 0;
			if(playtvmplayer!=null){
				if((playtvmplayer.getPlaybackObject()!=null)){
					tsRecording=((TvChannelPlayback)playtvmplayer.getPlaybackObject()).getTimeshiftRecordingObject();
				}
				if((ongoingRecData.recordingType == RecordingType.RECORDING_OTR) && (null != tsRecording)) {
					  copyDuration = tsRecording.getCopyDuration();
					  Log.d(Tag,"copyDuration " + copyDuration);
				}
				if(0 < copyDuration) {
					isTimeShiftCopyDone = false;
			   		Log.d(Tag,"isTimeShiftCopyDone" + isTimeShiftCopyDone);
				}
				mnewmode= DeduceCamOperatingmode(playtvmplayer.getCurrentPurpose());
			}
			 long deviceIdentifier = PlayTvHDDUtils.getInstance(mContext).getDeviceId();
			 String deviceId = Long.toString(deviceIdentifier);
			 recordinstance.startRecording(mnewmode, mountPath, ongoingRecData.recordId, copyDuration, deviceId);
				// register for content observer
				RegisterTVContentObserver();

			 Runnable onRecStartRunnable = new Runnable() {
		            @Override
		            public void run() {
		              onRecStarted();
		            }
		          };
		     handler.post(onRecStartRunnable);
			 Intent i = new Intent("org.droidtv.playtv.REC_START_NOTIFY");
			 if (ongoingRecData != null){
				mRecChannelCid=ongoingRecData.channelId;
			    i.putExtra("recordId", ongoingRecData.recordId);
			    i.putExtra(IRecordingsContract.C_CHANNELID, ongoingRecData.channelId);
			    i.putExtra("PresetId", ongoingRecData.presetid);
			    Log.d(Tag,"startRecording ongoingRecData.recordId"+ongoingRecData.recordId+"ongoingRecData.channelId)"+ongoingRecData.channelId);

			 } else{
			    Log.d(Tag,"ongoingRecData is null");
			 }
			 i.putExtra("foreground",foreground_rec);
			 mContext.sendBroadcast(i);
		  }else {
		  	Log.d(Tag,"RecordInstance is NULL: recording wont start, updating recording as failed.");
		  	recError = RecordingError.REC_ERROR_IOERROR;
		  	updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_IOERROR, true, true);
		  }
	  	} else {

		  if(mountPath == null){
			  Log.d(Tag,"mountpath null, updating recording as failed for REC_ERROR_NODISK.");
			 recError = RecordingError.REC_ERROR_NODISK	;
			  updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_NODISK, true, true);
		  }
		  else{
			  Log.e(Tag,"HDD full, updating recording as failed for REC_ERROR_DISKFULL.");
			  Log.e(Tag,"getTotalSize: " + PlayTvHDDUtils.getInstance(mContext).getTotalSize());
			  Log.e(Tag,"getFreeSize: " + PlayTvHDDUtils.getInstance(mContext).getFreeSize());
			  recError = RecordingError.REC_ERROR_DISKFULL	;
			  updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_DISKFULL, true, true);
		  }
	  	}
	} else {
	  Log.d(Tag, "ongoingRecData is null while start recording.");
	}
  }

  public void checkForStartRecording() {
	recordinstance = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaRecordControl();
	if(recordinstance != null) {
		  recordinstance.registerListenerCallback(PvrRecordListener); //tvmediarecordcontrol blocks same listener object to be registered more than once..
		  long timenow = System.currentTimeMillis()/1000;
		  Log.d(Tag," checkForStartRecording() - Event Id " + ongoingRecData.eventId );
		  if(true == NordigPVRSupported(ongoingRecData)) {
		  	RegisterOnMediaStreamChangeListener(); //tvmediastream blocks same listener object to be registered more than once..
		  	EitInfoPair status = CheckEitPFData(ongoingRecData);
			String where =  IRecordingsContract.C_RECORDING_ID + "=?";
			String[] whereArgs = {Integer.toString(ongoingRecData.recordId)};
			ContentValues updateValues = new ContentValues();
			int retval;
			switch(status.eitStatus) {
			case EVENT_IN_PRESENT:
				//update recordings contract provider
				updateValues.put(IRecordingsContract.C_STARTTIME, status.info.dt);
				updateValues.put(IRecordingsContract.C_DURATION, status.info.Duration);
				updateValues.put(IRecordingsContract.C_EIT_SOURCE, EITSource.EIT_SOURCE_PF.ordinal());
				updateValues.put(IRecordingsContract.C_EIT_VERSION, -1);	//let other fields also get changed..
				updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
				ongoingRecData.eet = status.info.dt + status.info.Duration; //no margins for nordig PVR..
				retval = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings,
						updateValues, where, whereArgs);
				if(retval != 1) {
					Log.e(Tag, "error in updating start time !!--we will wait till the start time.. 2?");
				}
				currentState = STATE_RECORDING_STARTING;
				startRecording();
				handler.removeCallbacks(eitRunnable);
				handler.postDelayed(eitRunnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
				Log.d(Tag,"Nordig PVR -  Recording will be stopped in seconds ->" +  (ongoingRecData.eet - timenow));
				break;
			default:
				currentState = STATE_WAITING_FOR_EVENT;
				handler.removeCallbacks(eitRunnable);
				handler.postDelayed(eitRunnable, 10 *  MILLIS_IN_SECOND );
				Log.d(Tag,"Nordig PVR -  EIT will be checked in next 10 seconds");
				break;
			case EVENT_IN_FOLLOWING:
				//update recordings contract provider
				updateValues.put(IRecordingsContract.C_STARTTIME, status.info.dt);
				updateValues.put(IRecordingsContract.C_DURATION, status.info.Duration);
				updateValues.put(IRecordingsContract.C_EIT_SOURCE, EITSource.EIT_SOURCE_PF.ordinal());
				updateValues.put(IRecordingsContract.C_EIT_VERSION, -1);	//let other fields also get changed..
				updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
				ongoingRecData.eet = status.info.dt + status.info.Duration; //no margins for nordig PVR..
				retval = mContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings,
									updateValues, where, whereArgs);
				if(retval != 1) {
					Log.e(Tag, "error in updating start time !!--we will wait till the start time.. 3?");
				}
				currentState = STATE_WAITING_FOR_EVENT;
				handler.removeCallbacks(eitRunnable);
				handler.postDelayed(eitRunnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
				Log.d(Tag,"Event in following check after - seconds ->" +  (ongoingRecData.eet - timenow));
				break;
			}
		  } else {
		       currentState = STATE_RECORDING_STARTING;
		  	startRecording();
			handler.removeCallbacks(runnable);
			handler.postDelayed(runnable, (ongoingRecData.eet - timenow) *  MILLIS_IN_SECOND );
			Log.d(Tag," Recording will be stopped in seconds ->" +  (ongoingRecData.eet - timenow));
		  }
	}
	}

  class RecChangemodeRunnable implements Runnable {

    public RecChangemodeRunnable(PowerStates mPowerState) {
     // Log.d(Tag,"RecChangemodeRunnable");
      mCurrentPowerState = mPowerState;
    }
    @Override
    public void run() {
      Log.d(Tag," run: Prepare for rec power state change mode fired ");
      if(ongoingRecData!=null)
      {
        try {
          recordinstance = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaRecordControl();
          int mnewmode = DeduceCamOperatingmode(playtvmplayer.getCurrentPurpose());
          if(recordinstance != null )
          recordinstance.changeRecordingMode(mnewmode);
        }catch(Exception e){
          Log.e(Tag, "exception in RecordControl"+ e.toString());
        }
      }
      else
      Log.d(Tag,"No Recording is in currently in progress");
    }
  };


  public void  SetCurrentPowerState(PowerStates mPowerState)
  {
      Log.d(Tag,"SetCurrentPowerState:"+mPowerState);
	if ((PreparePostPonedRecordId != -1) && (mPowerState == PowerStates.POWER_STATE_FULL_SYSTEM_START || mPowerState == PowerStates.POWER_STATE_SEMI_STANDBY)) {
	    Log.d(Tag, "SetCurrentPowerState prepare for recording" + mCurrentPowerState + PreparePostPonedRecordId);
	    mCurrentPowerState=mPowerState;
	    handler.post(new PrepareRecRunnable(new RecordData(PreparePostPonedRecordId,mContext)));
	    PreparePostPonedRecordId = -1;
	}else if(mPowerState==PowerStates.POWER_STATE_DDR_STANDBY){
	    mCurrentPowerState=PowerStates.POWER_STATE_DDR_STANDBY;
	    getShutDownInProgressLock();
		handler.post(new PrepareDDRRunnable());
	}
	else {
    handler.post(new RecChangemodeRunnable(mPowerState));
	}
  }
  class PrepareDDRRunnable implements Runnable{
	  public PrepareDDRRunnable(){
		  //Log.d(Tag,"PrepareDDRRunnable");
	  }
	  @Override
		  public void run(){
		  	long timenow = System.currentTimeMillis()/1000;
			if((mNextRecordingId!=-1) && (mAlarmTime<=(timenow+TWO_MINS))){
				Log.d(Tag,"PrepareDDRRunnable"+timenow);
				AddAlarm(mNextRecordingId, (timenow+TWO_MINS));
			}
			releaseShutDownInProgressLock();
		  }
  };

  public int DeduceCamOperatingmode(int currentPurpose)
  {
    Log.d(Tag, "Deduce cam mode " + mCurrentPowerState + currentPurpose);
    if( (mCurrentPowerState == PowerStates.POWER_STATE_FULL_SYSTEM_START ) &&
        ( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)
          == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH))
    {
      return BcstConstants.RECORDING_MODE_WATCH_AND_BUFFER;
    }

    return BcstConstants.RECORDING_MODE_UNATTENDED;

  }
  public void onRecStarted()
  {
    Log.d(Tag,"onRecStarted ");
    try {
      for(IRecStateChangeListener RecActionsListener:registeredListeners) {
        RecActionsListener.onRecStarted();
      }
    } catch (ConcurrentModificationException e) {
      Log.d(Tag,"Error sending Notifications to all modules ");
    }
		if (ongoingRecData.isZiggo == 1) {
			CAMDetails camDetails = new CAMDetails();
			camDetails.setMedium(CAMDetails.UNKNOWNMEDIUM);
			CamInfoDB camInfo = CamInfoDB.getInstace(mContext);
			int noOfCAMS = camInfo.getNoOfCAMS(camDetails);
			Log.i(Tag, "NoOFCAMS:" + noOfCAMS);
			if (noOfCAMS == 1) {
				mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_ZIGGO_RECORDING_STARTED));
				messenger.showTvToastMessage(mTimeOutTvToast);
			} else {
				mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORDING_STARTED));
				messenger.showTvToastMessage(mTimeOutTvToast);
			}
		} else {
	  mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORDING_STARTED));
	  messenger.showTvToastMessage(mTimeOutTvToast);
		}
  }

  public void endRecording(boolean userStop)
  {
    Log.d(Tag,"endRecording with userStop is " + userStop);
    if((ongoingRecData!=null) && (recordinstance != null)) {
    	isRecordingPending = false;
	    if (!userStop) {
	      if ((currentState == STATE_RECORDING_EVENT) || (currentState == STATE_RECORDING_NORDIG_NO_EVENT)){
	        int UserMargin = 0;
	        UserMargin = ongoingRecData.endUserMargin;
	        Log.d(Tag,"UserMargin is " +UserMargin);
	        if(UserMargin != 0) {
	          //stop recording
	          Log.d(Tag,"End UserMargin"+UserMargin+ " stopping recording.");
	          handler.removeCallbacks(runnable);
	          recordinstance.stopRecording();
	          currentState = STATE_RECORDING_STOPPING;
	        }
	        else {
	          int autoMarginend = 600; // Read from the NVM
			  ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
	          autoMarginend = globalSettings.getInt(TvSettingsConstants.PVRAUTOENDMARGIN, 0, 600);
	          Log.d(Tag,"autoMarginend : "+autoMarginend);
	          if(autoMarginend != 0)
	          {
	            	if(!isNextRecordingReady(ongoingRecData.eet+autoMarginend) ) {
	              Log.d(Tag,"Posting autoMarginend");
	              // Post delayed with autoMarginend
	              handler.removeCallbacks(runnable);
	              handler.postDelayed(runnable, (autoMarginend*MILLIS_IN_SECOND) );

	              // Update the AUTO MARGIN END in the Recording
	              String where = IRecordingsContract.C_RECORDING_ID + "=?";
	              String[] whereArgs = { Integer.toString(ongoingRecData.recordId) };
	              ContentValues updateValues = new ContentValues();
	              updateValues.put(IRecordingsContract.C_AUTO_MARGIN_END,autoMarginend);
	              updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
	              mContext.getContentResolver().update(
	              IRecordingsContract.CONTENT_URI_Recordings, updateValues,
	              where, whereArgs);

	              currentState = STATE_RECORDING_AUTO_MARGIN;
	            }
	            else
	            {
	              handler.removeCallbacks(runnable);
	              recordinstance.stopRecording();
	              currentState = STATE_RECORDING_STOPPING;
	            }
	          }
	          else
	          {
	            Log.d(Tag,"End AutoMargin"+autoMarginend+ " stopping recording.");
	            handler.removeCallbacks(runnable);
	            recordinstance.stopRecording();
	            currentState = STATE_RECORDING_STOPPING;
	          }
	        }

	      } else {
	        //stop recording
	        Log.d(Tag,"stopping recording as currentstate is not STATE_RECORDING_EVENT.");
	        handler.removeCallbacks(runnable);
	        recordinstance.stopRecording();
	        currentState = STATE_RECORDING_STOPPING;
	      }
	    } else {
	      //stop recording
	      Log.d(Tag,"stopping recording as stopped by user.");
	      handler.removeCallbacks(runnable);
	      recordinstance.stopRecording();
	      currentState = STATE_RECORDING_STOPPING;
	    }
    } else {
        Log.d(Tag,"ongoingrecdata null or recordInstance null" /*or wrong recording state caught for endRecording currentState is:"+currentState*/);
    }
  }

  public int getRecordingSize(int recordingId) {
    RecordingInfo RecInfo;
    int size = 0;
    if (recordinstance != null) {
      RecInfo = recordinstance.getCurrentRecordingInfo(recordingId);
      size = RecInfo.sizeInMB;
    }
    return size;
  }

  private RecordingInfo getRecordingInfo(int recordingId) {
    RecordingInfo RecInfo = null;
    if (recordinstance != null) {
      RecInfo = recordinstance.getCurrentRecordingInfo(recordingId);
    }
    return RecInfo;
  }

  public void onRecFinished() {
    Log.d(Tag,"onRecFinished ");
    mNextRecordingId = -1;
    mNextRecordingEST = Long.MAX_VALUE;
    if ((ongoingRecData != null) && (ongoingRecData.recordingType != RecordingType.RECORDING_USER_DELETED)) {
       	updateRecordDetails(ongoingRecData.recordId, false, ongoingRecData);
    } else {
      Log.d(Tag, " either ongoingRecData is null or recording type is user DEleted");
    }

    try {
      for(IRecStateChangeListener RecActionsListener:registeredListeners) {
        RecActionsListener.onRecFinished();
      }
    } catch (ConcurrentModificationException e) {
      Log.d(Tag,"Error sending Notifications to all modules ");
    }
    Intent i = new Intent("org.droidtv.playtv.REC_END_NOTIFY");
	if (ongoingRecData != null){
	    i.putExtra("recordId", ongoingRecData.recordId);
	    i.putExtra(IRecordingsContract.C_CHANNELID, ongoingRecData.channelId);
	    i.putExtra("PresetId", ongoingRecData.presetid);
	}
	i.putExtra("foreground",foreground_rec);
    mContext.sendBroadcast(i);
    mRecChannelCid=-1;
    finishRecHandler.post(finishRecRunnable);

    currentState = STATE_IDLE;
  }

  public void updateRecordForError(int recordId, RecordingError recError, boolean handleRecFinished, boolean showOnlyOSD) {
	Log.d(Tag,"updateRecordForError with error "+recError + " showOnlyOSD: " +  showOnlyOSD + "currentState:" + currentState);
	this.recError = recError;

	recLog.logFailedRecording(recordId, recError);

	if(showOnlyOSD) {
		// SHOW OSD: this should only be executed if recording didn't start due to some failure.
		ShowErrorOSD(recError);
	}
    if((recordinstance != null) &&
    		(ongoingRecData != null) &&
    		(ongoingRecData.recordId == recordId) &&
    		(currentState != STATE_IDLE))
    {
    	handler.removeCallbacks(runnable);
    	isRecordingPending = false;
    	recordinstance.stopRecording();
    	currentState = STATE_RECORDING_STOPPING;
    } else if(handleRecFinished) {
	    String where = IRecordingsContract.C_RECORDING_ID + "=?";
	    String[] whereArgs = { Integer.toString(recordId) };
	    ContentValues updateValues = new ContentValues();
	    updateValues.put(IRecordingsContract.C_IS_PARTIAL, false);
	    updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_FAILED.ordinal());
	    updateValues.put(IRecordingsContract.C_RECORDING_ERROR, recError.ordinal());
	    updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
	    mContext.getContentResolver().update(
	      IRecordingsContract.CONTENT_URI_Recordings, updateValues,
	      where, whereArgs);
	    if( (ongoingRecData != null) && (ongoingRecData.recordId == recordId) ) {
		ongoingRecData.recordingType = RecordingType.RECORDING_FAILED;
	    }
    	finishRecHandler.post(finishRecRunnable);
    }
  }

  private void ShowErrorOSD(RecordingError error)
  {
	Log.d(Tag,"ShowErrorOSD "+error);
	if(error == RecordingError.REC_ERROR_NONE)
	    {
		 	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORDING_FINISHED));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(((error == RecordingError.REC_ERROR_CONFLICT) || (error == RecordingError.REC_ERROR_POWERINTERRUPTION))&&(isPartial))
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORDING_FINISHED));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_CONFLICT)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_OTHER_RECORDING));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_POWERINTERRUPTION)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_POWER_FAILURE));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_DISKFULL)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_HDD_FULL));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_EPG_NOTACTIVE)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_NO_EPG_DATA));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_EVENT_NOT_TRANSMITTED)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_CHANGED_SCHEDULE));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_IOERROR)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_WRITE_ERROR));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_NO_CAM)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_NO_CAM));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_NO_SIGNAL)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_NO_SIGNAL));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_NO_TRUSTED_CLOCK)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_NO_AUTOMATIC_CLOCK));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_NODISK)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_NO_HDD));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_NOPOWER)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_POWER_FAILURE));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_SYSTEM)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_SYSTEM_ERROR));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
	    else if(error == RecordingError.REC_ERROR_TV_BUSY)
	    {
	    	mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_RECORD_FAILED_TV_BUSY));
		 	messenger.showTvToastMessage(mTimeOutTvToast);
	    }
  }

  public boolean registerRecStateChangeListener(IRecStateChangeListener handler, String cTag)
  {
    //Log.d(Tag,"registerRecStateChangeListener called from " + cTag);
    if(registeredListeners.contains(handler)==false)
    {
      registeredListeners.add(handler);
      return true;
    }
    return false;
  }

  public boolean unregisterRecStateChangeListener(IRecStateChangeListener handler, String cTag)
  {
    Log.d(Tag,"unregisterRecStateChangeListener called from " + cTag);
    registeredListeners.remove(handler);
    return true;
  }

  void AddAlarm(int rec_id, long abstime)
  {
	mAlarmTime=abstime;
    Log.d(Tag," AddAlarm : abstime is "+abstime+ " rec_id "+ rec_id);
    AlarmManager alarmMgr = (AlarmManager)mContext.getSystemService(Context.ALARM_SERVICE);
    Intent intent = new Intent(mContext, AlarmReceiver.class);

    Uri RecUri = Uri.parse("rec://");
    intent.setData(RecUri);

    intent.putExtra("recordId", rec_id);
    intent.putExtra("alarmTime", abstime);

    pendingIntent = PendingIntent.getBroadcast(mContext, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
    alarmMgr.setExact(AlarmManager.RTC_WAKEUP, (abstime * MILLIS_IN_SECOND), pendingIntent);
  }

  class RecAlarmRunnable implements Runnable {
    private RecordData alarmRecord;

    public RecAlarmRunnable(int rec_id) {
      //Log.d(Tag," RecAlarmRunnable ");
      alarmRecord = new RecordData(rec_id,mContext);
    }

    @Override
    public void run() {
      Log.d(Tag," run: Prepar for rec after alarm fired ");
	if( (ongoingRecData != null) && (ongoingRecData.recordId == alarmRecord.recordId) ) {
		Log.d(Tag, "recording already started..ignoring alarm");
	} else if((alarmRecord.recordId == mNextRecordingId) || (mNextRecordingId == -1)) {
    	  handler.post(new PrepareRecRunnable(alarmRecord));
	} else {
    	  Log.d(Tag, "alarmRecord.recordId : "+alarmRecord.recordId + "mNextRecordingId : "+mNextRecordingId);
	}
    }
  };

  public void onAlarm(int rec_id,int reqId) {
    Log.d(Tag," Alarm Fired for rec_id "+rec_id);
    handler.post(new RecAlarmRunnable(rec_id));
  }

  @Override
  public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
  int presetNumber) {
    Log.d(Tag, "PlayStarted - Recservice");
  }

  @Override
  public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
  int presetNumber) {
	  Log.d(Tag,"Recservice onPlayCompleted"+mediaPlayerUri.toString());
    if((ongoingRecData != null) && (ongoingRecData.presetid == presetNumber) && (ongoingRecData.medium == medium) && (currentState == STATE_TUNING) ) {
      Log.d(Tag,"PlayCompleted - RecServer ");
      PrepareForStartRecording();
    }
  }

  @Override
  public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
    if((ongoingRecData != null) && (ongoingRecData.presetid == presetNumber) && (ongoingRecData.medium == medium) && (currentState == STATE_TUNING)) {
      endRecording(true);
      Log.e(Tag, "play failed for recording -- not expected !!");
	  recError = RecordingError.REC_ERROR_TV_BUSY	;
      updateRecordForError(ongoingRecData.recordId, RecordingError.REC_ERROR_TV_BUSY, false, true);
      Log.d(Tag, "updated records to failed for failing to get mpl instance ");
    }
    else{
         Log.d(Tag, "Ignoring on onPlayFailed currentState " + currentState + "presetNumber " + presetNumber);
    }
  }

  @Override
  public void onInfo(boolean cicamAvailable) {
  }


  @Override
  public void onPlayFinished(Uri mediaPlayerUri, Medium medium,
  int presetNumber) {
    //should not come for channels and hence not of interest..
  }

  @Override
  public void onLockStatusChanged(int type, int status) {
    // TODO Auto-generated method stub
	}

  @Override
  public void onPlayError(int error, int what , int extra, int mode){
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
}

@Override
public void onSeekComplete(int mode){
}

@Override
public void onTimeshiftInfoChanged(){
}

  @Override
  public void onMPLPurposeChanged(int currentPurpose) {
    // TODO Auto-generated method stub
    if(ongoingRecData != null) {
      int newMode = DeduceCamOperatingmode(currentPurpose);
      try {
        recordinstance = playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaRecordControl();
        if(recordinstance!=null)
        {
          recordinstance.changeRecordingMode(newMode);
          Log.d(Tag, "onMPLPurposeChanged sucessfully changed the recording mode");
        }
      } catch(Exception e){
        Log.e(Tag, "exception in onMPLPurposeChanged "+ e.toString());
      }
    }
  }

  private void FormatHdd(){
    Intent intent = new Intent("org.droidtv.settings.LAUNCH_HDD_WIZARD");
    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
    intent.putExtra("WIZARD_ORIGIN", 2/*TS*/);
    mContext.startActivity(intent);
  }

  private final BroadcastReceiver HDDFormatReceiver = new BroadcastReceiver() {
    @Override
    public void onReceive(Context context, Intent intent) {
      String sAction = intent.getAction();
      if(sAction.equals("org.droidtv.intent.action.FORMATTINGDONE")) {
        Log.d(Tag, "Remove new, failed, expired, partially viewed, viewed recordings.");
        String where = IRecordingsContract.C_RECORDING_TYPE + "= ? OR "
        + IRecordingsContract.C_RECORDING_TYPE + "= ? OR "
        + IRecordingsContract.C_RECORDING_TYPE + "= ? OR "
        + IRecordingsContract.C_RECORDING_TYPE + "= ? OR "
        + IRecordingsContract.C_RECORDING_TYPE + "= ? OR "
        + IRecordingsContract.C_RECORDING_TYPE + "= ?";
        String whereArgs[] = {""+IRecordingsContract.RecordingType.RECORDING_NEW.ordinal(),
          ""+IRecordingsContract.RecordingType.RECORDING_FAILED.ordinal(),
          ""+IRecordingsContract.RecordingType.RECORDING_EXPIRED.ordinal(),
          ""+IRecordingsContract.RecordingType.RECORDING_VIEWED.ordinal(),
          ""+IRecordingsContract.RecordingType.RECORDING_PARTIALLY_VIEWED.ordinal(),
          ""+IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal()};
        int del_result = context.getContentResolver().delete(
        IRecordingsContract.CONTENT_URI_Recordings, where, whereArgs);
        if(del_result >0)
        {
          Log.d(Tag, "formatting HDD, deleted "+del_result+" recordings.");
        } else {
          Log.d(Tag, "no recordings deleted on format HDD.");
        }
      }
    }
  };

  class PrepareRecRunnable implements Runnable {
    private RecordData prepareRecord;
    private boolean IsPowerOnSync;

    public PrepareRecRunnable(RecordData record) {
      Log.d(Tag," prepareRecRunnable ");
      prepareRecord = record;
      IsPowerOnSync = false;
    }

    public PrepareRecRunnable(RecordData record, boolean isPowerOnSync) {
        Log.d(Tag," prepareRecRunnable ");
        prepareRecord = record;
        IsPowerOnSync = isPowerOnSync;
    }
    @Override
    public void run() {
      Log.d(Tag," run: Prepar for rec ");
      PrepareForRecording(prepareRecord, IsPowerOnSync);
    }
  };

  class SetVersionRunnable implements Runnable {
    private int version;

    public SetVersionRunnable(int version) {
      Log.d(Tag," SetVersionRunnable ");
      this.version = version;
    }

    @Override
    public void run() {
      Log.d(Tag," run: setVersion ");
      setVersion(version);
    }
  };

    class MediaChangeRunnable implements Runnable {
        private String subtitleIndex;
        private String audioIndex;
        private int mode;

         public MediaChangeRunnable(int lmode){
            this.mode = lmode;
        }

         public MediaChangeRunnable(int lmode,String lsubtitleindex,String laudioIndex){
             this.mode = lmode;
             if(lsubtitleindex!=null){
            	 this.subtitleIndex=lsubtitleindex;
             }
             if(laudioIndex!=null){
            	 this.audioIndex=laudioIndex;
             }
        }


        @Override
        public void run() {

            switch(this.mode)
            {
            case MEDIA_AUDIO_CHANGE:
            	//Log.d(Tag," MediaChangeRunnable - mode MEDIA_AUDIO_CHANGE");
                if(null != audioIndex){

//                    if((mRecChannelCid != mUserChannelCid)){
//                        mUserSubtitleIndex = -2;
//                    }
                    int ltrackId=-1;
                    String[] parts = audioIndex.split(":");
                    String trackId = parts[1];
                    if(trackId!=null) {
                    	 ltrackId=Integer.parseInt(trackId) ;
                    }
                    mUserAudioIndex=ltrackId;
                    if((null != ongoingRecData) && (null != playtvmplayer) && (ongoingRecData.channelId == mUserChannelCid) && ((playtvmplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)==0)){
                    	ITvMediaControl tvmc 	= playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaControl();
	                    ITvMediaStream tvms 	= playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaStream();
	                    if(tvmc != null && tvms != null){
		                   	 int noAudio = tvms.getCurrentNoOfAudio();
		                   	 if(noAudio > Integer.parseInt(trackId)) {
		                   		 TvMediaAudioInfo currentAudInfo = tvmc.getTVAudio();
		                   		 //TvMediaAudioInfo mAudioInfo =  new TvMediaAudioInfo();
		                   		TvMediaAudioInfo mAudioInfo= tvms.getCurrentAudioInfo(mUserAudioIndex);
			                 	if((null != mAudioInfo) && (null != currentAudInfo) && ((currentAudInfo.pid != mAudioInfo.pid) || (currentAudInfo.langCode != mAudioInfo.langCode)|| (currentAudInfo.type != mAudioInfo.type))) {
		                   			 tvmc.stopTVMedia(ITvMediaControl.MEDIA_AUDIO);
		                   		   	 tvmc.playTVAudio(mAudioInfo);
		                   		 }
		                   	 }
                       
	                    	}
                    	}
	                    else{
	                            Log.d(Tag,"Audio change not called");
	                     }
                    }
                    else{
                        Log.d(Tag,"Audio change not called");
                    }
                
            break;

            case MEDIA_SUBTITLE_CHANGE:
            	//Log.d(Tag," MediaChangeRunnable - mode MEDIA_SUBTITLE_CHANGE");
                if(null != this.subtitleIndex){
//                       if(mRecChannelCid != mUserChannelCid){
//                            mUserAudioIndex=-1;
//                       }
                       int ltrackId=-2;
                       String[] parts = subtitleIndex.split(":");
                       String trackId = parts[1];
                       if(trackId!=null) {
                       	 ltrackId=Integer.parseInt(trackId) ;
                       }
                       mUserSubtitleIndex = ltrackId;
                       if((null != ongoingRecData) && (null != playtvmplayer) && (ongoingRecData.channelId == mUserChannelCid) && ((playtvmplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)==0)){
                            ISubtitles subtitle =  playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getSubtitles();
                            if(null != subtitle){
                            	int lCurSubtitle=subtitle.getCurrentSubtitle();
                            	if(lCurSubtitle!=mUserSubtitleIndex){
                            		Log.d(Tag,"Current Subtitle"+lCurSubtitle+"subtitle to be selected"+mUserSubtitleIndex);
	                                subtitle.setUserPreferredSubtitle(mUserSubtitleIndex);
	                                subtitle = null;
									ITvMediaControl tvMediaControl =  playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaControl();
									if(null != tvMediaControl){
									   tvMediaControl.playTVMedia(BcstConstants.MEDIA_SUBTITLE, 8191);
									   tvMediaControl = null;
									    Log.d(Tag,"Subtitle enabled, index " + mUserSubtitleIndex);
									}
									else{
										Log.d(Tag,"Subtitle enabled, index " + mUserSubtitleIndex  + "Failed");
									}
                            	}
                            }
                            else{
                            	Log.d(Tag,"ISubtitle is null");
                            }
                       }
                       else{
                            Log.d(Tag,"Subtitle change not called");
                       }
                }else{
                	Log.d(Tag,"subtitleIndex is null");
                }
            break;
            case MEDIA_CHECK_AND_APPLY_CHANGE:
            	if((null != ongoingRecData) && (null != playtvmplayer) && (ongoingRecData.channelId==mUserChannelCid) && ((playtvmplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)==0)){
                	Log.d(Tag," MediaChangeRunnable - mode MEDIA_CHECK_AND_APPLY_CHANGE"+mUserChannelCid+"ongoing"+ongoingRecData+"cid="+ongoingRecData.channelId);
                	ITvMediaControl tvMediaControl =  playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaControl();
                	ITvMediaStream tvms 	= playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaStream();
                    if(null != tvMediaControl && tvms !=null){
                    	TvMediaAudioInfo currentAudInfo = tvMediaControl.getTVAudio();
                    	TvMediaAudioInfo mAudioInfo =  new TvMediaAudioInfo();
	                   	mAudioInfo= tvms.getCurrentAudioInfo(mUserAudioIndex);
	                   	if((null != mAudioInfo) && (null != currentAudInfo) && ((currentAudInfo.pid != mAudioInfo.pid) || (currentAudInfo.langCode != mAudioInfo.langCode)|| (currentAudInfo.type != mAudioInfo.type))) {
	                   			tvMediaControl.stopTVMedia(ITvMediaControl.MEDIA_AUDIO);
	                   			tvMediaControl.playTVAudio(mAudioInfo);
	                   			Log.d(Tag,"Audio enabled, pid " + mAudioInfo.pid);
	                   		 }
                        tvMediaControl = null;
                        tvms=null;
                    }
                    else{
                       Log.d(Tag,"ITvMediaControl or ITvMediaStream is null");
                    }

                    ISubtitles subtitle =  playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getSubtitles();
                    if(null != subtitle){
                    	int lCurSubtitle=subtitle.getCurrentSubtitle();
                    	if(lCurSubtitle!=mUserSubtitleIndex){
                    		Log.d(Tag,"Current Subtitle"+lCurSubtitle+"subtitle to be selected"+mUserSubtitleIndex);
	                        subtitle.setUserPreferredSubtitle(mUserSubtitleIndex);
	                        subtitle = null;
							ITvMediaControl tvMediaControl1 =  playtvmplayer.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaControl();
							if(null != tvMediaControl1){
							   tvMediaControl1.playTVMedia(BcstConstants.MEDIA_SUBTITLE, 8191);
							   tvMediaControl1 = null;
							   Log.d(Tag,"Subtitle enabled, index " + mUserSubtitleIndex);
							}
							else{
								Log.d(Tag,"Subtitle enabled, index " + mUserSubtitleIndex + "Failed");
							}
                    	}
                    }
                    else{
                       Log.d(Tag,"ISubtitle is null");
                    }
                }
                else{
  	              mUserAudioIndex=-1;
  	              mUserSubtitleIndex = -2;
                }
            break;
            default: 
            	break;
        }
    };
    
    }
    
  public RecordData OngoingRecData()
  {
    return ongoingRecData;
  }

  /*------------HDD Notifications starts here-------------*/
  @Override
  public void onHDDConnected() {
    Log.d(Tag,"onHDDConnected");
    mountPath = PlayTvHDDUtils.getInstance(mContext).getMountPath();
    Runnable powerOnSyncRunnable = new Runnable() {
		@Override
		public void run() {
		    Log.d(Tag, "onHDDConnected powerOnSyncState:"+powerOnSyncState);
		    if(powerOnSyncState == POWER_STATE_CLEANUP){
		    	Log.d(Tag, "poweronsync on HDD connected");
		        PowerOnSyncOngoingRecording();
		        PowerOnSyncUserActions();
		        powerOnSyncState |= POWER_STATE_ONGOING;
		    }
    	}
    };
    handler.post(powerOnSyncRunnable);
  }

  @Override
  public void onHDDRemoved() {
    Log.d(Tag,"onHDDRemoved");
    mountPath = null;
    Runnable nodeChangeRunnable = new Runnable() {
      @Override
      public void run() {
        if((ongoingRecData != null)&&((currentState != STATE_IDLE)))

        {
          Log.d(Tag, "HDD onChange mountpath is null..so stop recording");
          isPartial = true;
          recError = RecordingError.REC_ERROR_NODISK;
          endRecording(true);
        }
      }
    };
    handler.post(nodeChangeRunnable);
  }
  /*------------HDD Notifications ends here-------------*/

  public void updateRecordDetails(int recId, boolean isPowerOnSync, RecordData record) {
    String where = IRecordingsContract.C_RECORDING_ID + "=?";
    String[] whereArgs = { Integer.toString(recId) };
    ContentValues updateValues = new ContentValues();
    RecordingInfo RecInfo = getRecordingInfo(recId);
    Log.d(Tag, "RECID: "+recId+" , C_RECORDING_TYPE:new/failed , C_SIZE_IN_MB: "+RecInfo.sizeInMB+
    " , C_HAS_LICENSE_FILE: "+ RecInfo.hasLicenseFile +
    " , C_RETENTION_INFO : "+ RecInfo.retentionInfo+
    " , C_DURATION : "+RecInfo.duration+
    " , C_CICAMID : " +RecInfo.cicamId+
    " , C_FTASTATUS:" +RecInfo.isFTAService+
    " , C_recordingError:" +RecInfo.recordingError+
    " , C_DOTSTATUS:"+RecInfo.isDOTSet + " , recError: " + recError+", C_HAS_CICAM_PIN"+RecInfo.hasPinEvent);
    if(recError == RecordingError.REC_ERROR_NONE) {
    	recError = rec_error_type[RecInfo.recordingError];
    }
    Log.d(Tag,"updateRecordDetails recError : "+recError);

	recLog.logFailedRecording(recId, recError);

    if(!isPowerOnSync) {
	    ShowErrorOSD(recError);
    }
    else {
    	Log.d(Tag, "updateRecordDetails called from poweronSync");
    }

    if(RecInfo.duration > 0) {
	if(null != record) {
		record.recordingType = RecordingType.RECORDING_NEW;
	}
    	updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_NEW.ordinal());
    }
    else {
	if(null != record) {
		record.recordingType = RecordingType.RECORDING_FAILED;
	}
    	updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_FAILED.ordinal());
    }
    updateValues.put(IRecordingsContract.C_SIZE_IN_MB, RecInfo.sizeInMB);
    updateValues.put(IRecordingsContract.C_HAS_LICENSE_FILE, RecInfo.hasLicenseFile);
    updateValues.put(IRecordingsContract.C_RETENTION_INFO, RecInfo.retentionInfo);
    updateValues.put(IRecordingsContract.C_DURATION, RecInfo.duration);
    updateValues.put(IRecordingsContract.C_CICAMID, RecInfo.cicamId);
    updateValues.put(IRecordingsContract.C_ISFTARECORDING, RecInfo.isFTAService);
    updateValues.put(IRecordingsContract.C_HASDOT, RecInfo.isDOTSet);
    updateValues.put(IRecordingsContract.C_HAS_CICAM_PIN, RecInfo.hasPinEvent);
	updateValues.put(IRecordingsContract.C_IS_PARTIAL, isPartial);
	updateValues.put(IRecordingsContract.C_RECORDING_ERROR, recError.ordinal());
    updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
    mContext.getContentResolver().update(
    IRecordingsContract.CONTENT_URI_Recordings, updateValues,
    where, whereArgs);

    //reset ispartial and error
    isPartial = false;
    recError = RecordingError.REC_ERROR_NONE;
  }

  public boolean isRecordingOnGoing(Uri mediaPlayerUri)
  {
	  boolean mRecordingInProgress = false;
          UriData data ;
	  if((ongoingRecData!=null) && (currentState != STATE_IDLE)) {
		  try {
			  data = TvURIHelper.parseUri(mContext,mediaPlayerUri);
		  }catch(Exception e) {
			  Log.e(Tag, "caught exception in isRecordingOnGoing"+ e.toString());
			  return mRecordingInProgress;
		  }
		  Medium currentMedium = Medium.fromInteger(data.medium);
		  int currentChannel = data.channel;
		  //todo:tif
		  Medium medium = ongoingRecData.medium;
		  Log.d(Tag,"currentChannel" +currentChannel +"Current medium" +currentMedium);
		  Log.d(Tag,"RecordingChannel" +ongoingRecData.presetid +"RecordingMedium" +medium);
		  if((currentMedium == medium) &&
				  (currentChannel == ongoingRecData.presetid))
		  {
			  mRecordingInProgress = true;

		  }
	  }
	  return mRecordingInProgress;

  }

  public int getOngoingRecordId(Uri mediaPlayerUri)
  {
    Log.d(Tag,"getOngoingRecordId");
	if(ongoingRecData != null)
   return ongoingRecData.recordId;
   else return 0;
  }
  
  public boolean getIsZiggoRecordingOnGoing()
  {
    Log.d(Tag,"getIsZiggoRecording");
	if(ongoingRecData != null && ongoingRecData.isZiggo==1){
		return true;
	}
	else
	   return false;
  }

  /**
	 * To be called to register the content observer on TvContentProvider to know
	 * if the lock status of the channel being watched is getting changed.
	 * On change of medium the observer has to be set again.
	 */
	public void RegisterTVContentObserver()
	{
		Log.d(Tag,"RegisterTVContentObserver ");
		if(playtvmplayer!=null && ((playtvmplayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)==0)){
			if((tvObserver!=null) && (isObserverRegistered)) {
				mContext.getContentResolver().unregisterContentObserver(tvObserver);
			}
			else {
				tvObserver = new TVContentObserver(null);
			}
			mContext.getContentResolver().registerContentObserver(TvContract.Channels.CONTENT_URI, true, tvObserver);
			isObserverRegistered = true;
			if(ongoingRecData!=null){
				mUserChannelLock=getChannelLockStatus(TvContract.buildChannelUri(ongoingRecData.channelId));
			}
		}
		else{
			if((tvObserver!=null) && (isObserverRegistered)) {
				mContext.getContentResolver().unregisterContentObserver(tvObserver);
			}
		}
	}

	// unregister
	public void UnRegisterTVContentObserver()
	{
		Log.d(Tag,"UnRegisterTVContentObserver ");
		if(tvObserver!=null) {
			mUserChannelLock=-1;
			mContext.getContentResolver().unregisterContentObserver(tvObserver);
		}
	}

	public void CheckChannelLockStatus(Uri uri) {
		Cursor cursor = null;
		try {
			if ((mContext != null) && (uri != null)	&& TvContract.isChannelUriForTunerInput(uri)) {
				Log.d(Tag, "CheckChannelLockStatus " + uri.toString());
				int lockedChanneldId = -1;
				lockedChanneldId = (int) ContentUris.parseId(uri);
				if(lockedChanneldId == ongoingRecData.channelId){
					int lChannellock = getChannelLockStatus(uri);
					Log.d(Tag, "channel lock:" + lChannellock);
					if ((lChannellock != -1) && (mUserChannelLock != -1)&& (lChannellock != mUserChannelLock)) {
						mUserChannelLock = lChannellock;
						if ((ongoingRecData != null) && (lockedChanneldId != -1)) {
							Log.d(Tag, "calling ReInsertLockStatus");
							recordinstance.ReInsertLockStatus();
						}
					}
				}
			}
		} catch (Exception e) {
			Log.d(Tag, "Exception in CheckChannelLockStatus!!!");
		}
	}

  class TVContentObserver extends ContentObserver {

    	public String Tag = "TVContentObserver";
		private Uri lockChangeUri = null;

    	public TVContentObserver(Handler handler) {
    		super(handler);
    		Log.d(Tag, "TVContentObserver constructor called");
    	}

        @Override
        public boolean deliverSelfNotifications() {
            return false;
        }

    	@Override
    	public synchronized void onChange(boolean selfChange, Uri uri) {
    		super.onChange(selfChange, uri);
    		if(!selfChange) {
    			Log.d(Tag, "onChange Called : URI" + uri);
    			lockChangeUri = uri;
    			Runnable LockChangeRunnable = new Runnable() {
    				@Override
    				public void run() {
    					CheckChannelLockStatus(lockChangeUri);
    				}
    			};
    			lockHandler.post(LockChangeRunnable);
    		}
    	}
    }

  public void evaluateAlarms() {
	  Log.d(Tag, "evaluateAlarms before going to standby again");
	  getLock();
	  if((System.currentTimeMillis()/1000 + TWENTY_MINS) >= mNextRecordingEST) {
		  Log.d(Tag, "holding lock for futher action..");
	  }
	  else {
		  Log.d(Tag, "no action, hence releaseing lock..");
		  releaseLock();
	  }

  }

  public boolean getTimeShiftCopyStatus()
  {
        Log.d(Tag, "getTimeShiftCopyStatus" +isTimeShiftCopyDone);
        return isTimeShiftCopyDone;
   }
	public void AddRecordForValidityCheck(RecordData record)
	{
		Log.d(Tag, "AddRecordForValidityCheck");
		NoLicenseButRetention(record);
		HasLicense(record);
	}

	private void NoLicenseButRetention(RecordData record) {
		Log.d(Tag, "ifNoLicenseButRetention");
		String[] proj = new String[] {IRecordingsContract.C_RECORDING_ID, IRecordingsContract.C_RETENTION_INFO};
		String sel = "(" + IRecordingsContract.C_RECORDING_TYPE + " = ? OR "
				+ IRecordingsContract.C_RECORDING_TYPE + " = ? OR "
				+ IRecordingsContract.C_RECORDING_TYPE + " = ? ) AND ("
				+ IRecordingsContract.C_HAS_LICENSE_FILE + " = ? ) AND ("
				+ IRecordingsContract.C_RETENTION_INFO + " != ? )";
		String[] sel_args = { ""+RecordingType.RECORDING_NEW.ordinal(),
				""+RecordingType.RECORDING_VIEWED.ordinal(),
				""+RecordingType.RECORDING_PARTIALLY_VIEWED.ordinal(),
				String.valueOf(0),
				String.valueOf(-1)};
		String orderby = IRecordingsContract.C_RETENTION_INFO + " ASC LIMIT 1";

		Cursor c = mContext.getContentResolver().query(
				IRecordingsContract.CONTENT_URI_Recordings, proj,
				sel, sel_args, orderby);
		if((c != null) && (c.getCount() > 0) && (c.moveToFirst())) {
			if(c.getInt(0) == record.recordId) {
				//arm timer for this cancel previous
				recValidityCheck.validityTimer.cancel();
				long retention = c.getInt(1);
				int recId = c.getInt(0);
				//int sendDelay = (int)(retention-(System.currentTimeMillis()/MILLIS_IN_SECOND))*MILLIS_IN_SECOND;
				recValidityCheck.AddAlarmForValidityCheck(recId, retention);
			}
		}
		if(c != null)
			c.close();
	}

	private void HasLicense(RecordData record){
		Log.d(Tag, "ifLicense");
		String[] proj = new String[] {IRecordingsContract.C_HAS_LICENSE_FILE};
		String sel ="(" +IRecordingsContract.C_RECORDING_ID + " = ? ) AND ("
				+IRecordingsContract.C_HAS_LICENSE_FILE+ " = ? )";
		String[] sel_args = { String.valueOf(record.recordId),
				String.valueOf(1)};
		Cursor c = mContext.getContentResolver().query(
				IRecordingsContract.CONTENT_URI_Recordings, proj,
				sel, sel_args, null);
		if((c != null) && (c.getCount() > 0) && (c.moveToFirst())) {
			Log.d(Tag, "AddRecordForValidityCheck add recordId "+record.recordId+" to arraylist.");
			recValidityCheck.recordIdArray.add(record.recordId);
		}
		if(c!=null)
			c.close();
	}

	private Context getContext() {
		return mContext;
	}

	public static synchronized void createInstance(Context mContext) {
		setContext(mContext);
		if(mRecService==null){
			//Log.d(Tag,"creating REcservice");
			mRecService=new RecService();
			mRecService.initRecService();
		}
	}
	private static void setContext(Context lContext) {
		//Log.d(Tag,"setcontext called");
		mContext=lContext;
	}

	private IEpgProviderNotify mRecordingInfo = new IEpgProviderNotify() {
		@Override
		public void onEpgDataChanged(int channelId) {
			try {
				Log.d(Tag, "onEpgDataChanged "+channelId+" "+mEpgCache.isBCEpgMode());
				final int id = channelId;
				if(mEpgCache.isBCEpgMode()) {
					Runnable RecordingInfoRun = new Runnable() {
						@Override
						public void run() {
							if (id == ongoingRecData.channelId) {
								updateRecordingInfo(ongoingRecData);
							}
						}
					};
					handler.post(RecordingInfoRun);
					mEpgCache.unregisterListener(mRecordingInfo);
				}
			} catch (Exception e) {
				Log.d(Tag, "Exception in onEpgDataChanged !!!"+e.toString());
			}
		}

		@Override
		public void onEpgModeChanged() {
			Log.d(Tag, "onEpgModeChanged");
		}
	};

	private void updateRecordingInfo(RecordData data) {
		if (data != null) {
			Log.d(Tag, "updateRecordingInfo recId:"+data.recordId+" chId:"+data.channelId+"recType:"+data.recordingType);
			if (data.recordingType == IRecordingsContract.RecordingType.RECORDING_MANUAL) {
				String eventName = null;
				String shortInfo = null;
				String extendedInfo = null;
				String guidanceInfo = null;
				int genre = 0;
				int rating = 0;
				String shortInfoWithEventName = null;

				if (mEpgCache.getChannelEpgDataStatus(data.channelId) != EpgNowNextData.NO_DATA) {
					Log.d(Tag, "EPG data found for UniqueID "+data.channelId);
					eventName = mEpgCache.getNowEventName(data.channelId);
					shortInfo = mEpgCache.getNowShortInfo(data.channelId);
					extendedInfo = mEpgCache.getNowExtendedInfo(data.channelId);
					guidanceInfo = mEpgCache.getNowGuidanceinfo(data.channelId);
					genre = mEpgCache.getNowGenre(data.channelId);
					rating = mEpgCache.getNowRating(data.channelId);
					// This is done for EPG moreInfoActivity, since it expects event name and short info in a single string
					shortInfoWithEventName = eventName + "\n" + shortInfo;
					Log.d(Tag, "eventName:"+eventName+" shortInfo:"+shortInfo+" extendedInfo:"+extendedInfo+
							" guidanceInfo:"+guidanceInfo+" genre:"+genre+" rating:"+rating+" shortInfoWithEventName:"+
							shortInfoWithEventName);

					String selection = IRecordingsContract.C_RECORDING_ID+" = ?";
					String[] selArgs = {Integer.toString(data.recordId)};
					ContentValues v = new ContentValues();
					v.put(IRecordingsContract.C_EVENT_NAME, eventName);
					v.put(IRecordingsContract.C_EVENT_SHORT_INFO, shortInfoWithEventName);
					v.put(IRecordingsContract.C_EVENT_EXTENDED_INFO, extendedInfo);
					v.put(IRecordingsContract.C_EVENT_GUIDANCE_INFO, guidanceInfo);
					v.put(IRecordingsContract.C_EVENT_GENRE, genre);
					v.put(IRecordingsContract.C_EVENT_RATING, rating);
					int count = mContext.getContentResolver().update(
								IRecordingsContract.CONTENT_URI_Recordings, v, selection, selArgs);
					Log.d(Tag, "EPG info update result "+count);
				} else {
					Log.d(Tag, "No EPG data for uniqueID "+data.channelId);
				}
			}
		} else {
			Log.d(Tag, "updateRecordingInfo: RecData is null");
		}
	}

	 private class PowerEventsReceiver implements IPowerEvents {

 		@Override
 		public void onPowerChangeStart(PowerStates from, PowerStates to, Bundle extras) {
 			Log.d(Tag,"onPowerChangeStart : from - "+from+"to - "+to);
 			SetCurrentPowerState(to);
 		}

 		@Override
 		public void onPowerChangeEnd(PowerStates from, PowerStates to, Bundle extras) {
			Log.d(Tag,"onPowerChangeEnd : from - "+from+"to - "+to);
 			SetCurrentPowerState(to);
 		}
 	}

     public static IPowerEvents getPowerEventsListener() {
 		return mPowerEventListener;
 	}
     private void Setcid(Uri uri) {
 		if(uri != null) {
 			try {
 				mUserChannelCid= (int) ContentUris.parseId(uri);
 			}catch(Exception e) {
 				Log.d("Exception while doing parseID!!!","Uri is " + e.toString());
 				mUserChannelCid= -1;
 			}
 			Log.d(Tag,"set cid"+uri.toString()+"cid"+mUserChannelCid);
 		}else {
 			mUserChannelCid= -1;
 			Log.d(Tag,"set cid uri is null,"+"cid"+mUserChannelCid);
 		}
 	}
	public void processNextRecordingId() {
		Log.d(Tag, "processNextRecordingId mNextRecordingId" + mNextRecordingId	+ "mNextRecordingEST" + mNextRecordingEST);

		if (STATE_IDLE == currentState) {
			try {
				if (mNextRecordingEST != Long.MAX_VALUE	&& mNextRecordingId != -1) {
					RecordData lRecord = new RecordData(mNextRecordingId,mContext);
					PrepareForRecording(lRecord,false);
				}
			} catch (Exception e) {
				Log.d(Tag, "Exception in processNextRecordingId");
			}
		} else {
			Log.d(Tag,"current state is not idle, so request ignored, currentState "+ currentState);
		}
	}

	public boolean isRecordingforeground() {
		return foreground_rec;
	}

     private void bindtoSSBYService() {
    	 //Log.d(Tag,"bindService");
 		svcConnect svcobj = new svcConnect();
 		Intent intent = new Intent(TvIntent.ACTION_SERVICE_SBYSERVICE);
 		mContext.getApplicationContext().bindService(intent,svcobj, Context.BIND_AUTO_CREATE);
 	}
     
 	/****************************** Session starts here *****************************/

 	public class TvInputCallbackClass extends TvInputCallback {
 		
 		public void onInputStateChanged(String inputId, int state) {
 		}
 		
 		public void onInputAdded(String inputId) {
 			if (inputId.equals(TunerServiceID)) {
				if (mTvInputManager.getInputState(TunerServiceID) == TvInputManager.INPUT_STATE_CONNECTED) {
					Log.d(Tag, "creating the session,waiting for call back");
					mTvInputManager.createSession(TunerServiceID,mSessionCallback, mSessionHandler);
				}
			} else {
				//Log.d(Tag, "OnInputAdded for non tuner id");
			}
 		}

 		public void onInputRemoved(String inputId) {
 		}
 	}
 	
 	public class TunerSessionCallback extends SessionCallback {
         
 		Session mSession  = null;
 		ITVSessionContext mSessionContext = null;
 		ITVTunerSession mTunerSession 	= null;
 		
         public void onSessionCreated(Session session) {
 			//Log.d(Tag,"onSessionCreated "+session);
 			if(session!=null){
				mSession = session;
				String action = ITVSessionContext.APP_PRIVATE_COMMAND_SESSION_TYPE;
				Bundle bundle = new Bundle();
				bundle.putString(ITVSessionContext.KEY_SESSION_TYPE, ITVSessionContext.SESSION_TYPE_MAIN_OBSERVER);
				mSession.sendAppPrivateCommand(action, bundle);
 			}
         }
         
         public void onSessionReleased(Session session) {
 			Log.i(Tag,"onSessionReleased");
 			mSession  = null;
 	 		mSessionContext = null;
 	 		mTunerSession 	= null;
         }
         
         public void onChannelRetuned(Session session, Uri channelUri) {
 			//Log.d(Tag,"onChannelRetuned uri:"+channelUri);
 			if(session!=null && channelUri!=null){
 				Setcid(channelUri);
 				handler.post(new MediaChangeRunnable(MEDIA_CHECK_AND_APPLY_CHANGE));
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
         
         public void onTrackSelected(Session session, int type, String trackId) {
        	 if(session!=null){
        		 //Log.d(Tag,"onTrackSelected"+type);
        		 if(type==TvTrackInfo.TYPE_AUDIO){
        			 if(trackId!=null){
        				 handler.post(new MediaChangeRunnable(MEDIA_AUDIO_CHANGE,null,trackId));
        			 }
        		 }
        		 else if(type==TvTrackInfo.TYPE_SUBTITLE){
        			 if(trackId!=null){
        				 handler.post(new MediaChangeRunnable(MEDIA_SUBTITLE_CHANGE,trackId,null));
        			 }
        		 }
        	 }
         }

         
         public void onSessionEvent(Session session, String eventType, Bundle eventArgs) {	
 			//Log.i(Tag,"onSessionEvent " + this);
 			if(eventType.equals(ITVSessionContext.EVENT_SESSION_CONTEXT_CREATED)){
 				IBinder binder = eventArgs.getBinder(ITVSessionContext.SESSION_CONTEXT);
 				mSessionContext = ITVSessionContext.instance.asInterface(binder);
 				mTunerSession	= mSessionContext.getITvTunerSession();
 				
 				class TunerSessionObserver extends ITunerSessionCallbacks {
 					@Override
 					public void onTuneFailed(String inputid, Uri channelUri, int reason) {
 					}
 					
 					@Override
 					public void OnDualStatusChanged(int channel, int controllable) {
 					}
 				}

 				TunerSessionObserver tunerSessionCallbacks = new TunerSessionObserver();					
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
 	
 	/****************************** Session ends here *****************************/
 	
 	private class svcConnect implements ServiceConnection {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			mCallback = ITvSemiStandbyControl.Instance.asInterface(service);
			//Log.d(Tag,"onServiceConnected ");
			mCallback.registerSemiStandbyAction(id,msbyCallbackclass);
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			//Log.d(Tag,"onServiceDisconnected ");
		}
	}

 	private class SbyCallback extends ITvSemiStandbyCallback {

 		public void onStartAction() {
			Log.d(Tag,"onStartAction called");
			handler.post(new Runnable() {
				@Override
				public void run() {
					processNextRecordingId();
					mCallback.setActionCompleted(id);
				}
			});
		}

		public void onStopAction() {
			Log.d(Tag,"StopAction called");
			handler.post(new Runnable() {
				@Override
				public void run() {
					mCallback.setActionCompleted(id);
				}
			});
		}

		public long onGetNextAlarm() {
			Log.d(Tag,"onGetNextAlarm called");
			return 0;
		}
 	}
}
