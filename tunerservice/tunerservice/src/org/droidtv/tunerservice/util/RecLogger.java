package org.droidtv.tunerservice.util;

import org.droidtv.tv.logger.ILogger;
import org.droidtv.tv.logger.ILogger.FailedPVRRecording.*;
import org.droidtv.tv.provider.IRecordingsContract.RecordingError;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.IBinder;
import android.util.Log;
import android.os.Handler;
import android.os.HandlerThread;


public class RecLogger {

	private static final String TAG = RecLogger.class.getSimpleName();
	private static RecLogger mRecLogger;
	private ILogger mBinder;
	private ILogger.FailedPVRRecording mRecLog;
	private ILogger.ChannelZapAdvanced mZapInfo = null;
	private ILogger.ChannelZapSource mChannelZapLog = null;
	private static Handler mLogHandler = null;
	HandlerThread thread = new HandlerThread(TAG);

	private RecLogger(){
		thread.start();
		mLogHandler = new Handler(thread.getLooper());
		mRecLog = new ILogger.FailedPVRRecording();
		mZapInfo = new ILogger.ChannelZapAdvanced();
	}
	/*
	Bill Pugh Singleton Implementation as suggested in review comments
	*/
	private static class SingletonHelper{
        private static final RecLogger INSTANCE = new RecLogger();
    }

	public static RecLogger getInstance(){
		return SingletonHelper.INSTANCE;
	}

	public void bindToLoggingService(Context pContext) {

		Intent logIntent = new Intent();
		logIntent.setAction("org.droidtv.tv.intent.action.START_LOGGER");
		try{
			PackageManager mPackageManager = pContext.getPackageManager();
			ResolveInfo mResolveInfo = mPackageManager.resolveService(logIntent, 0);
			if(mResolveInfo != null) {
				logIntent.setClassName(mResolveInfo.serviceInfo.packageName, mResolveInfo.serviceInfo.name);
				boolean serviceBound =pContext.getApplicationContext().bindService(logIntent, conn, Context.BIND_AUTO_CREATE);
				Log.d(TAG," in bindToNetvLoggerService  after binding call, servicebound="+serviceBound);
			}else {
				Log.e(TAG, "org.droidtv.tv.intent.action.START_LOGGER: not able to resolve ");
			}
		}catch(SecurityException e){
			Log.e(TAG, "Caught Security Exception : " + ""+e.getLocalizedMessage());
						Log.e(TAG, "Failed to bind to CUL service "+e.toString() );
		}catch(Exception e){
			Log.e(TAG , "Caught exception :: Couldn't bind to service : " +""+e.getLocalizedMessage());
		}
	}

	public ServiceConnection conn = new ServiceConnection(){

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			//Log.d(TAG," onServiceConnected callback received");
			mBinder = ILogger.Instance.asInterface(service);
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			//Log.d(TAG,"received onServicedisconnected for LoggingHelper, shut this service");
			mBinder = null;
		}
	};

	private FailureReason translateErrorToReason(RecordingError recError){

		FailureReason reason = FailureReason.NONE;

		switch(recError){
			case REC_ERROR_NONE:
				reason = FailureReason.NONE;
				break;
			case REC_ERROR_DISKFULL:
				reason = FailureReason.DISKFULL;
				break;
			case REC_ERROR_CONFLICT:
				reason = FailureReason.CONFLICT;
				break;
			case REC_ERROR_NOPOWER:
				reason = FailureReason.NOPOWER;
				break;
			case REC_ERROR_POWERINTERRUPTION:
				reason = FailureReason.POWERINTERRUPTION;
				break;
			case REC_ERROR_NODISK:
				reason = FailureReason.NODISK;
				break;
			case REC_ERROR_IOERROR:
				reason = FailureReason.IOERROR;
				break;
			case REC_ERROR_EVENT_NOT_TRANSMITTED:
				reason = FailureReason.EVENT_NOT_TRANSMITTED;
				break;
			case REC_ERROR_NO_TRUSTED_CLOCK:
				reason = FailureReason.NO_TRUSTED_CLOCK;
				break;
			case REC_ERROR_TV_BUSY:
				reason = FailureReason.TV_BUSY;
				break;
			case REC_ERROR_NO_SIGNAL:
				reason = FailureReason.NO_SIGNAL;
				break;
			case REC_ERROR_NO_CAM:
				reason = FailureReason.NO_CAM;
				break;
			case REC_ERROR_EPG_NOTACTIVE:
				reason = FailureReason.EPG_NOTACTIVE;
				break;
			case REC_ERROR_SYSTEM:
				reason = FailureReason.SYSTEM;
				break;
			default:
				reason = FailureReason.NONE;
		}
		return reason;
	}

	public void logFailedRecording(int recID, RecordingError recError ){

		Log.d(TAG,"logFailedRecording: recID: "+recID+", recError:"+recError);
		mRecLog.failureReason = translateErrorToReason(recError);
		mRecLog.recID = recID;

		if(mLogHandler != null){
			mLogHandler.postDelayed(mlogRunnable, 0);
		}
	}


	private Runnable mlogRunnable = new Runnable() {

		@Override
		public void run() {
			try{				
				if(mBinder != null){
					//Log.d(TAG,"mBinder available, FailedRecording Logged");
					mBinder.Log(mRecLog);
					}
				else{
					Log.e(TAG,"Binder NOT available, can't log PowerState");
					}
			}catch(Exception e){
				Log.e(TAG, "Failed to log FailedPVRRecording to CUL due to :"+e.toString());
			}
		}
	};

	public void logZapSource(long channelId, ILogger.ChannelZapSource.ZapMethod zapSource){

		mChannelZapLog = new ILogger.ChannelZapSource();
		mChannelZapLog.channel_id = channelId;
		mChannelZapLog.zap_method = zapSource;

		if(mLogHandler != null){
			mLogHandler.postDelayed(mZapSourceRunnable, 0);
		}else{
			Log.e(TAG,"Handler NOT available, can't log ChannelZapSource"+zapSource);
		}
	}

	private Runnable mZapSourceRunnable = new Runnable() {

		@Override
		public void run() {
			try{
				if(mBinder != null){
					mBinder.Log(mChannelZapLog);
					mChannelZapLog = null;
				}
			}catch(Exception e){
				Log.e(TAG, "Failed to log zap Source to CUL due to :"+e.toString());
			}
		}
	};
}

