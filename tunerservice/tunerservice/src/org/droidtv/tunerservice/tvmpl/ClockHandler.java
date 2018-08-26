package org.droidtv.tunerservice.tvmpl;

import org.droidtv.tunerservice.interfaces.IClockHandlerCallBacks;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.LooperTimer;
import org.droidtv.tv.media.ITvMediaStream.TvMediaTimeInfo;
import org.droidtv.tv.media.ITvMediaStream.TvMediaTimeOffsetInfo;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tv.media.TvMediaStream;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.tvclock.ITvClockManager;
import android.net.Uri;
import android.os.RemoteException;
import android.util.Log;
import java.util.Map;
import android.os.Handler;
/*begin:min.jiang add 2015-06-02, for pbs date and time settings*/
import java.util.HashMap;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;
import android.content.Context;
import android.content.ContentUris;
import android.provider.Settings;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tunerservice.util.PlayTvUtils;

/*end:min.jiang add*/

public class ClockHandler implements IPlayTvStateChangeListener {
	private static final String tag = "ClockHandler";

	private static final int mRefreshIntervalLong = 20 * 1000; // in ms
	private static final int mRefreshIntervalShort = 3 * 1000; // in ms
	private static final int INVALID_VERSION_NUMBER = -1;

	private IClockHandlerCallBacks mlistener = null;
	private ClockTimer mClockTimer = null;

	private volatile int mTOTVersionNo;
	private volatile int mTDTVersionNo;
	
	/** To set time from tdt/tot, we require tv media player */
	PlayTvMediaPlayer playtvmpl = null;
	TvMediaPlayer tvmpl = null;

	/** Media stream through which playtv activity gets time from tdt/tot */
	TvMediaStream tvms = null;
	ITvClockManager mtvclockmanager = null;

    private Uri mUri = null;
	private boolean mColdStart = false;//min.jiang add 2015-10-08, implement clock calibration when cold start
	private Handler mHandler = null;

	public ClockHandler(PlayTvMediaPlayer mpl) {
		Log.d(tag, "ClockHandler");
		mtvclockmanager = ITvClockManager.Instance.getInterface();
		playtvmpl = mpl;
		playtvmpl.registerListener(this, tag);
		mTOTVersionNo = INVALID_VERSION_NUMBER;
		mTDTVersionNo = INVALID_VERSION_NUMBER;

	}

	public void release() {
		Log.d(tag, "release called");
		if (mClockTimer != null) {
			if(mHandler != null){
				mHandler.removeCallbacksAndMessages(null);
			}
			mClockTimer.stopTimer();
			mClockTimer = null;
		}
	}

	private class ClockTimer extends LooperTimer {
		public int mCurrentInterval;

		@Override
		public void timerHandler() {
			Log.d(tag, "Periodic Timer");
			// TODO : Currently calling set time on the same thread.
			// Need to move this onto a seperate thread for timer accuracy
			SetTimeEx();
		}

		public ClockTimer() {
			mCurrentInterval = mRefreshIntervalShort;
		}

		public void UpdateTimerInterval(int mInterval) {
			synchronized(ClockHandler.this){
				if (mCurrentInterval != mInterval) {
					Log.d(tag, "Updating timer to " + mInterval);
					if (mClockTimer != null)
						mClockTimer.resetTimer(mInterval, true, 0);
					mCurrentInterval = mInterval;
				}
			}
		}
	}

	private boolean SetTimeFromTOT() {
		TvMediaTimeInfo mTottimeInfo = null;
		TvMediaTimeOffsetInfo mTottimeOffsetInfo = null;
		boolean mTOTSet = false;

		try {
			mTottimeInfo = tvms.getCurrentTimeInfoFromTot();
			mTottimeOffsetInfo = tvms.getCurrentTimeOffsetInfo();
		} catch (RemoteException e) {
			Log.d(tag, " Caught RemoteException");
		}
		if(mTottimeOffsetInfo != null) {
			if(!PlayTvUtils.isLiveCountry(mTottimeOffsetInfo.countryId)){
				Log.d(tag, "ts countryId: " + mTottimeOffsetInfo.countryId + ", not menu country");
				return false;
			}
		}
		if (null != mTottimeInfo && null != mTottimeOffsetInfo) {
			/* Check if the retrieved information is valid */
			if ((mTottimeInfo.version == INVALID_VERSION_NUMBER)
					|| (mTottimeOffsetInfo.version == INVALID_VERSION_NUMBER)) {
				Log.d(tag, "TOT: Invalid version");
				if (mTOTVersionNo != INVALID_VERSION_NUMBER) {
					Log.d(tag, "TOT: Time already set with version "
							+ mTOTVersionNo);
					mTOTSet = true;
				}
			} else if ((mTOTVersionNo == mTottimeInfo.version)
					&& (mTOTVersionNo != INVALID_VERSION_NUMBER)) {
				Log.d(tag, "Version: Stream: " + mTottimeInfo.version
						+ "ClockHandler " + mTOTVersionNo);
				Log.d(tag, "TOT: Time already set with version "
						+ mTOTVersionNo);
				mTOTSet = true;
			} else {
				try {
					/*
					 * set next lto : so that if set time is called then clock
					 * service will check for next lto date is reached, if so
					 * then next time offset will be set by clock service
					 */
		            /*begin:min.jiang add 2015-06-02, for pbs date and time settings*/       
					/*
				    if(PlayTvUtils.isPbsMode()) {   
		                Log.d(tag, "tot countryId: " + mTottimeOffsetInfo.countryId + ", datetime: " + mTottimeInfo.datetime);
		                if(mTottimeInfo.datetime > 0 && !PlayTvUtils.isLiveCountry(mTottimeOffsetInfo.countryId)) {     
		                    Log.d(tag, "TOT: not live country");                    
		                    if (mlistener != null) {
								mlistener.OnClockSetResult(mUri, IClockHandlerCallBacks.RESULT_FAILED);
							}                    
		                    return false;
		                }                
		            }
		            */
		            /*end:min.jiang add*/					 
					String timesecs = String
							.valueOf(mTottimeOffsetInfo.changeDate);
					/* converting to milli seconds */
					long text = 1000 * Long.parseLong(String.valueOf(timesecs));
					Log.d(tag, "changeDate = " + text);
					if (text > 0) {
						mtvclockmanager
								.SetNextLtoChange(
										text,
										(int) (mTottimeOffsetInfo.nextTimeOffset * 1000),
										ITvClockManager.eClockSources.TOT);
						Log.d(tag, "NEXT LTO TIME[" + text + "ms]"
								+ "NEXT LTO OFFSET["
								+ mTottimeOffsetInfo.nextTimeOffset + "]");
					}

					/* set time from TOT */
					timesecs = String.valueOf(mTottimeInfo.datetime);
					/* converting to milli seconds */
					text = 1000 * Long.parseLong(String.valueOf(timesecs));
					Log.d(tag, "datetime = " + text);
					if (text > 0) {
						mtvclockmanager
								.SetTime(
										text,
										(mTottimeOffsetInfo.timeOffset * 1000),
										 ITvClockManager.eClockSources.TOT, mColdStart);//min.jiang 2015-10-08
						if (mlistener != null) {
							mlistener
									.OnClockSetResult(mUri, IClockHandlerCallBacks.RESULT_SUCCESS_TOT);
						}
						Log.d(tag, "TIME CHANGED TO:[" + text + " ms]"
								+ "TOT OFFSET[" + mTottimeOffsetInfo.timeOffset
								+ "]");
						mTOTVersionNo = mTottimeInfo.version;
						mTOTSet = true;
					}
				} catch (Exception e) {
					Log.d(tag, "Caught Exception : " + e.getLocalizedMessage());
				}
			}
		}
		return mTOTSet;
	}

	private boolean SetTimeFromTDT() {
		/* Set time using TDT */
		TvMediaTimeInfo mTdttimeInfo = null;

		try {
			mTdttimeInfo = tvms.getCurrentTimeInfoFromTdt();
		} catch (RemoteException e) {
			Log.d(tag, " Caught RemoteException");
		}

		if (null != mTdttimeInfo) {
			/* Check version numbers */
			if ((mTdttimeInfo.version == INVALID_VERSION_NUMBER)
					|| (mTDTVersionNo == mTdttimeInfo.version)) {
				Log.d(tag, "TDT: Invalid version or same version");
				Log.d(tag, "Version: Stream: " + mTdttimeInfo.version
						+ "ClockHandler " + mTDTVersionNo);
				return false;
			}
			Log.d(tag,
					"getCurrentTimeInfoFromTdt called Successfully with return value="
							+ mTdttimeInfo.datetime + " version="
							+ mTdttimeInfo.version);

			/* set time from TDT */
			try {
				String timesecs = String.valueOf(mTdttimeInfo.datetime);
				long text = 1000 * Long.parseLong(String.valueOf(timesecs));
				Log.d(tag, "datetime = " + text);
				if (text > 0) {
					mtvclockmanager
							.SetTime(
									text,
									0,
									ITvClockManager.eClockSources.TDT, mColdStart);//min.jiang modify 2015-10-08
					if (mlistener != null) {
						mlistener
								.OnClockSetResult(mUri, IClockHandlerCallBacks.RESULT_SUCCESS_TDT);
					}
					Log.d(tag, "TIME CHANGED TO : " + text + " ms");
					mTDTVersionNo = mTdttimeInfo.version;
					return true;
				}
			} catch (Exception e) {
				Log.d(tag, "Caught Exception : " + e.getLocalizedMessage());
			}
		} else {
			Log.d(tag, "TDT: null object");
		}
		return false;
	}
    /*begin:min.jiang add 2015-06-02, for pbs date and time settings*/
    private boolean isClockLiveChannel(PlayTvMediaPlayer playtvmpl) {
        boolean ret = false;
        int cid = -1;
		Uri mUri = null;
		if(playtvmpl != null)
		{
			mUri = playtvmpl.getCurrentUri();
		}
        if(mUri != null && PlayTvUtils.isLiveChannelMode()) {
            cid = (int)ContentUris.parseId(mUri);  
            
            if(cid == PlayTvUtils.getClockCalibrationcid()){
                Log.d(tag, "play channel equal clock channel");
                ret = true;
            }
        }
        return ret;
    }
   
    /*end:min.jiang add*/
	public void SetTimeEx() {
		Log.d(tag, "SetTime()");
		
		if (playtvmpl != null) {
			if (tvmpl == null) {
				tvmpl = playtvmpl.getMediaPlayerInstance();// tv media player
															// instance
			}
            /*begin:min.jiang add 2015-06-02, for pbs date and time settings*/            
		    if(PlayTvUtils.isPbsMode()) {
                Log.d(tag, "pbs mode is on");
                if(!isClockLiveChannel(playtvmpl)){
                    Log.d(tag, "not live channel or not clock down channel in SetTime()");
                    
                    if (mlistener != null) {
						mlistener.OnClockSetResult(mUri, IClockHandlerCallBacks.RESULT_FAILED);
					}             
                    return;
                }                
            }                  
            /*end:min.jiang add*/
			if (tvmpl != null) {
				if (tvms == null) {
					tvms = tvmpl.getTvMediaStreamInstance();
				}
				if (tvms != null) {
					/* Check from TOT */
					if (!SetTimeFromTOT()) {
						Log.d(tag, "SetTimeFromTOT failed. Trying TDT");
						if (!SetTimeFromTDT()) {
							Log.d(tag, "SetTimeFromTDT failed");
						} else {
							mHandler = new Handler();
							Runnable r = new Runnable() {
								@Override
								public void run() {
									if (mClockTimer != null) {
										mClockTimer.UpdateTimerInterval(mRefreshIntervalLong);
									}
								}
							};
							mHandler.post(r);	
							
						}
					} else {
						mHandler = new Handler();
						Runnable r = new Runnable() {
							@Override
							public void run() {
								if (mClockTimer != null) {
									mClockTimer.UpdateTimerInterval(mRefreshIntervalLong);
								}
							}
						};
						mHandler.post(r);	
					}
				} else {
					Log.d(tag, "null object : media stream instance failed");
				}
			} else {
				Log.d(tag, "null object : media player instance failed");
			}
		} else {
			Log.d(tag, "null object : playtv media player instance failed");
		}
	}

	@Override
	public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
			int presetNumber) {
	}

	@Override
	public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
			int presetNumber) {

		if ((medium == Medium.MEDIUM_INVALID)
				|| (medium == Medium.MEDIUM_TSFILE)
				|| (medium == Medium.MEDIUM_PVRFILE)
				|| (medium == Medium.MEDIUM_EXTN)) {
			return;
		}

		mTOTVersionNo = INVALID_VERSION_NUMBER;
		mTDTVersionNo = INVALID_VERSION_NUMBER;
        if(mediaPlayerUri != null){
		    Log.d(tag, "OnPlayCompleted " + mediaPlayerUri.toString());
        }
        mUri = mediaPlayerUri;
		mColdStart = mUri.getBooleanQueryParameter("clock_calibration", false); //min.jiang add 2015-10-08  
        if(((playtvmpl.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)>0) ||
    			((playtvmpl.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY)>0)) {
        	if (null == mClockTimer) {
        		Log.d(tag, "Starting ClockTimer");
        		mClockTimer = new ClockTimer();
        		mClockTimer.LooperTimerInit();
        		mClockTimer.startTimer(mRefreshIntervalShort, true, 0);
        	}
        }else {
        	Log.d(tag,"not ok purpose" + playtvmpl.getCurrentPurpose());
        }
	}

	@Override
	public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
	}

	@Override
	public void onInfo(boolean cicamAvailable) {
		
	}

	@Override
	public void onError(PlayTvMediaPlayer mpl, int what , int extra) {
		if((what==-1)&&(extra==-1)) {
			Log.d(tag,"local onError... ignore");
		}else {
			release();
		}
	}

	@Override
	public void onPlayFinished(Uri mediaPlayerUri, Medium medium,
			int presetNumber) {
	}

	@Override
	public void onLockStatusChanged(int type, int status) {
	}

	@Override
	public void onPurposeChanged(int purpose) {
		if(((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)==0) &&
			((purpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY)==0)){
			release();
		}
	}

	public void RegisterCallBack(IClockHandlerCallBacks listener) {
		mlistener = listener;
	}
	@Override
	public void onUriChanged(Uri mediaPlayerUri) {
	}
	
	@Override
	public void onCamUpgradeStarted(boolean status) {
	}
}
