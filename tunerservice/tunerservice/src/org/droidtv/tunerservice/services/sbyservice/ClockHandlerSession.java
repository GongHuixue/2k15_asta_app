package org.droidtv.tunerservice.services.sbyservice;

import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.ISessionHandlerTIF;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.ImplITunerSessionCallbacks;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_STATE;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tv.tvinput.ITVTunerSession.ITunerSessionCallbacks;
//import org.droidtv.euinstallertc.model.mwapi.ITVTunerSession;
//import org.droidtv.euinstallertc.model.mwapi.ITunerSessionCallbacks;
//import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.ImplITunerSessionCallbacks;
import org.droidtv.tunerservice.interfaces.IClockHandlerCallBacks;
import org.droidtv.tv.tvinput.ITVSessionContext;
import android.media.tv.TvInputManager.SessionCallback;
import android.media.tv.TvInputManager.Session;
import android.os.Handler;
import android.media.tv.TvInputManager;
import android.media.tv.TvInputManager.TvInputCallback;
import android.util.Log;
import android.content.Context;
import android.content.Intent;
import android.os.Message;
import android.media.tv.TvTrackInfo;
import android.os.IBinder;
import android.media.tv.TvContentRating;
import android.media.tv.TvInputInfo;
import android.os.Bundle;
import android.net.Uri;
import java.util.List;
import android.os.Handler.Callback;


public class ClockHandlerSession implements Callback{
	private static final String TAG = "ClockHandlerSession";
	private Context mContext = null;
	private Handler mSessionHandler = null;
	private Handler mHandler = null;
	private TvInputManager tvinputmanager = null;
	private TvInputCallbackClass mCallbackobject = null;
	private SessionCallbackClass mSessionCallbackobject = null;
	private static final int EVENT_CREATESESSION 		= 1;
	private static final int EVENT_INIT 				= 2;
	private static final int EVENT_TUNE                 = 3;
	private static final int TIME_OUT = 5000;
	private Session mSession  = null;
	private ITVSessionContext mSessionContext = null;
	private ITVTunerSession mTunerSession = null;
	private ITunerSessionCallbacks tunerSessionCallbackInst;
	private IClockHandlerCallBacks mClockCallback = null;
//	private ISessionHandlerTIF mClientCallbackInst = null;
	private boolean mSessionrequest = false;
	private boolean mPendingtune = false;
	private boolean PendingSessionClose = false;
	private Uri mPendingUri;
	private Bundle mPendingHeaders;
	public ClockHandlerSession(Context context, IClockHandlerCallBacks callback){
		mContext = context;
		mClockCallback = callback;
		mHandler = new Handler(this);
		mSessionHandler = new Handler();
		mCallbackobject = new TvInputCallbackClass();
		mSessionCallbackobject = new SessionCallbackClass();
		tunerSessionCallbackInst = new ImplITunerSessionCallbacks();
		//mHandler.sendEmptyMessage(EVENT_INIT);
	}

	private class TvInputCallbackClass extends TvInputCallback {

		@Override
		public void onInputAdded(String inputId) {
			tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(tvinputmanager!=null){
				try{
					TvInputInfo tv = tvinputmanager.getTvInputInfo(inputId);
					if(tv != null && (tv.getType()== TvInputInfo.TYPE_TUNER) &&
							(tv.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))) {
						mHandler.sendEmptyMessage(EVENT_CREATESESSION);
					}
				}catch(Exception ee){
					Log.e(TAG,"onInputAdded exception"+ee.getMessage());
				}
			}
		}

		@Override
		public void onInputRemoved(String inputId) {
			tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(tvinputmanager!=null){
				try{
					TvInputInfo tv = tvinputmanager.getTvInputInfo(inputId);
					if(tv != null && (tv.getType()== TvInputInfo.TYPE_TUNER) &&
						(tv.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))) {
						Log.d(TAG,"onInputRemoved inputId "+inputId);
						mSession = null;
						mSessionrequest = false;
						mPendingtune = false;
					}
				}catch(Exception ee){
					Log.e(TAG,"onInputRemoved exception"+ee.getMessage());
				}
			}
		}

		@Override
		public void onInputStateChanged(String inputId, int state) {
			Log.d(TAG,"onInputStateChanged " + inputId + "state " + state);
			tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(tvinputmanager!=null){
				try{
					TvInputInfo tv = tvinputmanager.getTvInputInfo(inputId);
					if(tv != null && (tv.getType()== TvInputInfo.TYPE_TUNER) &&
							(tv.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))) {
						if(state==TvInputManager.INPUT_STATE_CONNECTED) {
							mHandler.sendEmptyMessage(EVENT_CREATESESSION);
						}else if(state==TvInputManager.INPUT_STATE_DISCONNECTED){
							mSession = null;
							mSessionrequest = false;
							mPendingtune = false;
						}
					}
				}catch(Exception ee){
					Log.e(TAG,"onInputStateChanged exception"+ee.getMessage());
				}
			}
		}
	}
		public class SessionCallbackClass extends SessionCallback {
        
        public void onSessionCreated(Session session) {
			Log.d(TAG,"onSessionCreated");
			if(session != null) {
				mSession = session;
				String action = ITVSessionContext.APP_PRIVATE_COMMAND_SESSION_TYPE;
				Bundle bundle = new Bundle();
				bundle.putString(ITVSessionContext.KEY_SESSION_TYPE, /*ITVSessionContext.SESSION_TYPE_INSTALLER*/
						                                              ITVSessionContext.SESSION_TYPE_MAIN_WATCH);
				mSession.sendAppPrivateCommand(action, bundle);
				String action1 = ITVSessionContext.APP_PRIVATE_COMMAND_OVERLAY_CONTROL;
				Bundle bundle1 = new Bundle();
				bundle.putString(ITVSessionContext.KEY_ENABLE_OVERLAY, "1");
				mSession.sendAppPrivateCommand(action1, bundle1);
				if(mPendingtune) {
					mHandler.obtainMessage(EVENT_TUNE).sendToTarget();
				}else if (PendingSessionClose == true) {
					/* No need to proceed further. CloseRequest already came */
					try{
						Log.d (TAG, "Session Release request honored");
						if(mSession != null) {
						mSession.release();
							mSession = null;
						}
						PendingSessionClose = false;
					}catch(Exception ex){
						Log.d(TAG,"Caught Exception: " + ex.getMessage());
					}
				}
			}
        }
        
        public void onSessionReleased(Session session) {
			Log.d(TAG,"onSessionReleased called");
			mSession = null;
        }
        
        public void onChannelRetuned(Session session, Uri channelUri) {}
       
        public void onTrackInfoChanged(Session session, List<TvTrackInfo> tracks) {}

        public void onVideoAvailable(Session session) {}

        public void onVideoUnavailable(Session session, int reason) {}
        
        public void onContentAllowed(Session session) {}
       
        public void onContentBlocked(Session session, TvContentRating rating) {}
        
        public void onSessionEvent(Session session, String eventType, Bundle eventArgs) {
			Log.d(TAG,"onSessionEvent "+ eventType);
			if((session != null) && (eventType != null)) {
				if (PendingSessionClose == true) {
					/* No need to proceed further. CloseRequest already came */
					try{
						Log.d (TAG, "Session Release request honored");
						mSession.release();
						mSession = null;
						PendingSessionClose = false;
					}catch(Exception ex){
						Log.d(TAG,"Caught Exception: " + ex.getMessage());
					}
				} else if(eventType.equals(ITVSessionContext.EVENT_SESSION_CONTEXT_CREATED)){
					IBinder binder = eventArgs.getBinder(ITVSessionContext.SESSION_CONTEXT);
					ITVSessionContext sessionContext = ITVSessionContext.instance.asInterface(binder);
					mSessionContext = ITVSessionContext.instance.asInterface(binder);
					mTunerSession = mSessionContext.getITvTunerSession();
					mTunerSession.registerTunerSessionCallbacks(tunerSessionCallbackInst);
				}
			}
        }
    }

	@Override
	public boolean handleMessage(Message msg) {
		Log.d(TAG, "handleMessage: " + msg.what);
		switch(msg.what){
		case EVENT_INIT:
			tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(tvinputmanager != null) {
				tvinputmanager.registerCallback(mCallbackobject,mSessionHandler);
				mHandler.sendEmptyMessage(EVENT_CREATESESSION);
			} else {
				mHandler.sendEmptyMessageDelayed(EVENT_INIT,TIME_OUT);
			}
			break;
		case EVENT_CREATESESSION:
			try {
				if((mSession==null) && (!mSessionrequest)) {
					tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
					List<TvInputInfo> inputlist = tvinputmanager.getTvInputList();
					TvInputInfo tinfo = null;
					for(int i=0;i<inputlist.size();i++){
						tinfo = inputlist.get(i);
						if((inputlist.get(i).getType() ==TvInputInfo.TYPE_TUNER) &&
							(tinfo.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))){
							if(tvinputmanager.getInputState(tinfo.getId())==TvInputManager.INPUT_STATE_CONNECTED) {
								Log.d(TAG,"calling createsession");
								tvinputmanager.createSession(tinfo.getId(),mSessionCallbackobject,mSessionHandler);
								mSessionrequest = true;
							}
							break;
						}
					}
				}
			}catch(Exception e){
				e.getLocalizedMessage();
			}
			break;
		case EVENT_TUNE:
			if(mSession != null && mPendingtune && mPendingUri != null){
				tune(mPendingUri, mPendingHeaders);
			}
			break;
		}
		return false;
	}

	public class ImplITunerSessionCallbacks extends ITunerSessionCallbacks{

		@Override
		public void onTuneFailed(String inputid, Uri channelUri, int reason) {
			//super.onTuneFailed(inputid, channelUri, reason);
			handleTuneFailed(channelUri);
		}

		@Override
		public void onTuneStarted(String inputid, Uri channelUri, Bundle bundle) {
		}

		@Override
		public void onTuneCompleted(String inputid, final Uri channelUri, Bundle bundle) {
			Log.d(TAG, "onTuneCompleted() is called." );
			handleTuneCompleted(channelUri);
		}
	}

	public void createNewSession(){

		try {
			String createSessionURI = null;
			PendingSessionClose = false;
			tvinputmanager = (TvInputManager) (mContext.getApplicationContext()).getSystemService(Context.TV_INPUT_SERVICE);
			if (tvinputmanager != null) {
				List<TvInputInfo> inputlist = tvinputmanager.getTvInputList();
				for(int index=0;index<inputlist.size();index++){
					TvInputInfo tinfo = (TvInputInfo) inputlist.get(index);
					Log.d(TAG, "tinfo ["+ index + "]:" + tinfo);
					if((tinfo != null) && (tinfo.getType() == TvInputInfo.TYPE_TUNER) &&
						(tinfo.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))){
						createSessionURI = tinfo.getId();
						mHandler.sendEmptyMessage(EVENT_CREATESESSION);
						break;
					}
				}
			}
			if(createSessionURI == null) {
				mHandler.sendEmptyMessage(EVENT_INIT);
			}
		} catch (Exception ex) {
			Log.d(TAG, "caught exception: " + ex.getMessage());
		}
	}

	public void tune(Uri uri, Bundle headers) {
		if(mSession != null){
			mSession.tune(uri, headers);
			mPendingtune = false;
			mPendingUri = null;
			mPendingHeaders = null;
		}else {
			mPendingtune = true;
			mPendingUri = uri;
			mPendingHeaders = headers;
		}
	}

	public void closeSession() {
		Log.d(TAG, "closeSession");
		mPendingtune = false;
		mPendingUri = null;
		mPendingHeaders = null;
		mSessionrequest = false;
		if (mTunerSession != null) {
			mTunerSession.unregisterTunerSessionCallbacks(tunerSessionCallbackInst);
		}
		if (mSession != null) {
			try{
				mSession.release();
				mSession = null;
			}catch(Exception ex){
				Log.d(TAG,"Caught Exception: " + ex.getMessage());
			}
		}else {
			PendingSessionClose = true;
		}
	}

    private void handleTuneCompleted(Uri channelUri) {
        if(channelUri != null) {
            boolean isClockCalibration = channelUri.getBooleanQueryParameter("clock_calibration", false);
            if(isClockCalibration) {
                String result = channelUri.getQueryParameter("clock_result");
                Log.d(TAG, "clock calibration complete result: " + result);
                if(result != null && mClockCallback != null) {
					int source = Integer.valueOf(result);
					mClockCallback.OnClockSetResult(channelUri, source);
                }
            }
        }
    }
    
    private void handleTuneFailed(Uri channelUri) {
        if(channelUri != null) {
            boolean isClockCalibration = channelUri.getBooleanQueryParameter("clock_calibration", false);
            if(isClockCalibration) {
                Log.d(TAG, "send broadcast for TuneFailed");
                mClockCallback.OnClockSetResult(channelUri, IClockHandlerCallBacks.RESULT_FAILED);
            }
        }
    }
}
