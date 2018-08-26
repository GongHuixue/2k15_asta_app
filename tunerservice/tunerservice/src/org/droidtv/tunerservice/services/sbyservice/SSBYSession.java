package org.droidtv.tunerservice.services.sbyservice;

import java.util.List;

import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.SSBYSessionHelperCallbacks;
import org.droidtv.tunerservice.util.PlayTvMsgHandler;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.video.IVideoSource;

import android.content.Context;
import android.media.tv.TvContract;
import android.media.tv.TvInputInfo;
import android.media.tv.TvInputManager;
import android.media.tv.TvInputManager.Session;
import android.media.tv.TvInputManager.SessionCallback;
import android.media.tv.TvInputManager.TvInputCallback;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Handler.Callback;
import android.os.Message;
import android.util.Log;

public class SSBYSession implements Callback{
	
	private Context mContext = null;
	
	private TvInputManager tvinputmanager = null;
	private TvInputCallbackClass mCallbackobject = null;
	
	private Handler mSessionHandler = null;
	private SessionCallbackClass mSessionCallbackobject = null;
	
	private Handler mExtnSessionHandler = null;
	private SessionCallbackClass mExtnSessionCallbackobject = null;
	
	private PlayTvMsgHandler mHandler = null;
	private SSBYSessionHelperCallbacks listener = null;
	
	private static String TAG = "SSBYSession";
	
	private static final int EVENT_INIT 					= 1;
	private static final int EVENT_CREATE_OBSERVER_SESSION 	= 2;
	private static final int EVENT_OBSERVER_SESSION_CREATED	= 3;
	private static final int EVENT_OBSERVER_SESSION_CLOSED	= 4;
	
	private static final int EVENT_CREATE_EXTN_SESSION		= 5;
	private static final int EVENT_EXTN_SESSION_CREATED		= 6;
	private static final int EVENT_EXTN_SESSION_CLOSED		= 7;
	private static final int EVENT_EXTN_SESSION_ONTUNED		= 8;
	
	private static final int SESSION_OBSERVER	= 1;
	private static final int SESSION_EXTN	= 2;
		
	private static final int TIME_OUT = 5000;
		
	public SSBYSession(Context context, SSBYSessionHelperCallbacks listener) {
		mContext = context;
		this.listener = listener;
		mHandler = new PlayTvMsgHandler(PlayTvMsgHandler.getLooper("SSBYSession"), this);
		mSessionHandler = new Handler();
		mCallbackobject = new TvInputCallbackClass();
		mSessionCallbackobject = new SessionCallbackClass();
		
		mExtnSessionHandler = new Handler();
		mExtnSessionCallbackobject = new SessionCallbackClass();
		mExtnSessionCallbackobject.setSessionType(SESSION_EXTN);
		
		mHandler.sendEmptyMessage(EVENT_INIT);		
	}
	
	public void startSession(){
		//mHandler.sendEmptyMessage(EVENT_CREATE_OBSERVER_SESSION);
	}
		
	private class TvInputCallbackClass extends TvInputCallback {

		@Override
		public void onInputStateChanged(String inputId, int state) {
			Log.d(TAG,"onInputStateChanged " + inputId + "state " + state);
			tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(tvinputmanager!=null){
				try{
					TvInputInfo tv = tvinputmanager.getTvInputInfo(inputId);
					if(tv != null && (tv.getType()== TvInputInfo.TYPE_TUNER)&&
							(tv.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))){
						if(state==TvInputManager.INPUT_STATE_CONNECTED) {
							mHandler.sendEmptyMessage(EVENT_CREATE_OBSERVER_SESSION);
						}
					}
				}catch(Exception ee){
					Log.e(TAG,"onInputStateChanged exception"+ee.getMessage());
				}
			}
		}
	}
	
	public class SessionCallbackClass extends SessionCallback {
        
		private Session mSession  = null;
		private int sessiontype = SESSION_OBSERVER;
		private String tvinputId = null;
		private boolean active = false;
		
		public void setSessionType(int type) {
			sessiontype = type;
		}
		
        public void onSessionCreated(Session session) {
			Log.d(TAG,"onSessionCreated " + session);
			mSession = session;
			if(sessiontype==SESSION_OBSERVER) {
				String action = ITVSessionContext.APP_PRIVATE_COMMAND_SESSION_TYPE;
				Bundle bundle = new Bundle();
				bundle.putString(ITVSessionContext.KEY_SESSION_TYPE, ITVSessionContext.SESSION_TYPE_MAIN_OBSERVER);
				mSession.sendAppPrivateCommand(action, bundle);
				mHandler.sendEmptyMessage(EVENT_OBSERVER_SESSION_CREATED);
			}else {
				mHandler.sendEmptyMessage(EVENT_EXTN_SESSION_CREATED);
			}
        }
        
        public void onSessionReleased(Session session) {
			Log.d(TAG,"onSessionReleased called");
			if(sessiontype==SESSION_OBSERVER) {
				mHandler.sendEmptyMessage(EVENT_OBSERVER_SESSION_CLOSED);
			}else {
				mHandler.sendEmptyMessage(EVENT_EXTN_SESSION_CLOSED);
			}
			mSession = null;
        }
        
        public void onChannelRetuned(Session session, Uri channelUri) {
        	if((sessiontype==SESSION_EXTN)&&(active)) {
        		mHandler.sendEmptyMessage(EVENT_EXTN_SESSION_ONTUNED);
        	}
        }         

		public void tune() {
			Uri uri = TvContract.buildChannelUriForPassthroughInput(tvinputId);
			Log.d(TAG,"uri is " + uri.toString());
			mSession.tune(uri);
		}

		public void createSession(TvInputInfo tinfo) {
			active = true;
			if(mSession!=null) {
				if(!tinfo.getId().equals(tvinputId)) {
					mSession.release();
					mSession=null;
				}
			}
			tvinputId = tinfo.getId();
			if(mSession==null) {
				tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
				if(tvinputmanager!=null){
					tvinputmanager.createSession(tinfo.getId(),this, mExtnSessionHandler);
				}
			}else {
				tune();
			}
		}

		public void releaseSession() {
			active=false;
			//if we release the session the DDR Resume does not happen -> tvplayer 
		}
    }

	@Override
	public boolean handleMessage(Message msg) {
		boolean found = false;
		switch(msg.what){
		case EVENT_INIT:
			tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(tvinputmanager != null) {
				Log.d(TAG,"tvinputmanager found ");
				tvinputmanager.registerCallback(mCallbackobject,mSessionHandler);
			} else {
				Log.d(TAG,"tvinputmanager not found ");
				mHandler.sendEmptyMessageDelayed(EVENT_INIT,TIME_OUT);
			}
			break;
		case EVENT_CREATE_OBSERVER_SESSION:
			Log.d(TAG,"EVENT_CREATE_OBSERVER_SESSION ");
			try {
				tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
				List<TvInputInfo> inputlist = tvinputmanager.getTvInputList();
				TvInputInfo tinfo = null;
				Log.d(TAG,"inputlist size="+ inputlist.size());
				for(int i=0;i<inputlist.size();i++) {
					tinfo = (TvInputInfo) inputlist.get(i);
					if((tinfo.getType()==TvInputInfo.TYPE_TUNER) &&
						(tinfo.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))){
						if(tvinputmanager.getInputState(tinfo.getId())==TvInputManager.INPUT_STATE_CONNECTED) {
							Log.d(TAG,"calling createsession");
							tvinputmanager.createSession(tinfo.getId(),mSessionCallbackobject,mSessionHandler);
						}
						break;
					}
				}
			}catch(Exception e){
				Log.d(TAG,"Exception " + e.getLocalizedMessage());
			}
			break;
		case EVENT_OBSERVER_SESSION_CREATED:	
			listener.onObserverSessionCreated();
			break;
		case EVENT_OBSERVER_SESSION_CLOSED:
			listener.onObserverSessionClosed();
			break;
		case EVENT_CREATE_EXTN_SESSION:
			Log.d(TAG,"EVENT_CREATE_EXTN_SESSION ");
			try {
				tvinputmanager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
				List<TvInputInfo> inputlist = tvinputmanager.getTvInputList();
				TvInputInfo tinfo = null;
				Log.d(TAG,"inputlist size="+ inputlist.size());
				for(int i=0;i<inputlist.size();i++) {
					tinfo = inputlist.get(i);
					String tinfoString = tinfo.getId();
					Log.d(TAG,"id=" + tinfoString + " type =" + inputlist.get(i).getType());
					if(tinfoString.endsWith("HW"+msg.arg1)){
						mExtnSessionCallbackobject.createSession(tinfo);
						found = true;
						break;
					}
				}
			}catch(Exception e){
				Log.d(TAG,"Exception " + e.getLocalizedMessage());
			}
			if(!found) {
				Log.d(TAG,"extension source not found");
				listener.onExtensionSessionTuned();
			}
			break;
		case EVENT_EXTN_SESSION_CREATED:
			Log.d(TAG,"EVENT_EXTN_SESSION_CREATED ");
			mExtnSessionCallbackobject.tune();
			break;
		case EVENT_EXTN_SESSION_ONTUNED:
			Log.d(TAG,"EVENT_EXTN_SESSION_ONTUNED ");
			listener.onExtensionSessionTuned();
			break;
		}
		return false;
	}
	
	public void selectExtension(int sourceid) {
		Log.d(TAG,"selectExtension called "+ sourceid);
		Message msg = mHandler.obtainMessage(EVENT_CREATE_EXTN_SESSION,getHardwareId(sourceid), 0);
		mHandler.sendMessage(msg);
	}
		
	private static int getHardwareId(int sourceid) {
		switch (sourceid) {
			case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI1:
				return IVideoSource.VIDEOSOURCE_HDMI1;
			case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI2:	
				return IVideoSource.VIDEOSOURCE_HDMI2;
			case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI3:
				return IVideoSource.VIDEOSOURCE_HDMI3;
			case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI4:
				return IVideoSource.VIDEOSOURCE_HDMI4;
			case TvSettingsDefinitions.LastSelectedDeviceConstants.SCART:	
				return IVideoSource.VIDEOSOURCE_SCART1;
			case TvSettingsDefinitions.LastSelectedDeviceConstants.YPBPR:
				return IVideoSource.VIDEOSOURCE_YPBPR1;
			default:
				Log.e(TAG,"Invalid sourceid" + sourceid);
				return 0;
		}
	}
	
	public void releaseExtension() {
		mExtnSessionCallbackobject.releaseSession();
	}
}
