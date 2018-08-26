package org.droidtv.euinstallersat.model.mwapi;

import java.util.List;

import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tv.tvinput.ITvContractExtras;
import android.media.tv.TvInputManager.TvInputCallback;

import android.annotation.SystemApi;
import android.content.Context;
import android.media.tv.TvContentRating;
import android.media.tv.TvInputInfo;
import android.media.tv.TvInputManager;
import android.media.tv.TvInputManager.Session;
import android.media.tv.TvInputManager.SessionCallback;
import android.media.tv.TvTrackInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.util.Log;
import android.view.Surface;

/*
 *
 * Class for handling sessions in TV input framework (TIF) architecture
 * */

public final class SessionHandlerTIF {
	private String TAG = SessionHandlerTIF.class.getName();
	private TvInputManager mTvInputManager = null;
	private Handler mSessionHandler = null;
	private Context mContext = null;
	private InstallerSessionCallback mSessionCallback = null;
	private Session mSession = null;
	private ITVSessionContext mSessionContext = null;
	private ITVTunerSession mTunerSession = null;
	private String mPurpose = null;
	private ISessionHandlerTIF mClientCallbackInst = null;
	private SESSION_STATE sessionState = SESSION_STATE.INVALID;
	private Handler mHandler = null;
	private SessionContextCallbacks sessionContextCallbacks = null;
	private TvInputCallbackClass mCallbackobject = null;
	
	public String createSessionURI = "org.droidtv.tunerservice/.TunerService"; // initialized to default

	/*
	 * private static final int MSG_ = 0; private static final int
	 * MSG_STOPBACKGROUND = 1; private static final int MSG_STARTUPDATE = 2;
	 * private static final int MSG_STOPUPDATE = 3;
	 */

	public static enum SESSION_PURPOSE {
		SESSION_PURPOSE_INSTALLER, SESSION_PURPOSE_AUX, SESSION_PURPOSE_OBSERVER
	}

	public static enum SESSION_STATE {
		INVALID, SESSION_CREATED,
	}

	public static enum SESSION_MEDIUM {
		DVBS2,
		SATIP
	}

	public interface ISessionHandlerTIF {
		public void sessionCreationFailed();

		public void sessionCreationSuccessfull();

		public void sessionReleased();

		public void sessionOnChannelRetuned(Uri channelUri);
	}
	
	private class SessionContextCallbacks extends ITVSessionContext.ISessionContextCallbacks {
		
		@Override
		public void onReAcquireInterfaces() {
			if (mClientCallbackInst != null) {
				
			}
		}
	}

	public class InstallerSessionCallback extends SessionCallback {

		public void onSessionCreated(Session session) {
			Log.d(TAG, "onSessionCreated session:" + session + " mPurpose " + mPurpose);
			mSession = session;
			try {
				if (mSession == null) {
					if (mClientCallbackInst != null) {
						mHandler.post(new Runnable() {
							@Override
							public void run() {
								mClientCallbackInst.sessionCreationFailed();
							}
						});
					}
				} else {
					mHandler.post(new Runnable() {
						@Override
						public void run() {
							String action = ITVSessionContext.APP_PRIVATE_COMMAND_SESSION_TYPE;
							Bundle bundle = new Bundle();
							bundle.putString(ITVSessionContext.KEY_SESSION_TYPE, mPurpose);
							mSession.sendAppPrivateCommand(action, bundle);
						}
					});
				}

			} catch (Exception ex) {
				Log.d(TAG, "caught exception: " + ex.getMessage());
			}

		}

		public void onSessionReleased(Session session) {
			Log.d(TAG, "onSessionReleased called");
			sessionState = SESSION_STATE.INVALID;
			if (mClientCallbackInst != null) {
				mHandler.post(new Runnable() {
					@Override
					public void run() {
						mClientCallbackInst.sessionReleased();
					}
				});
			}
		}

		public void onChannelRetuned(Session session, final Uri channelUri) {
			Log.d(TAG, "onChannelRetuned " + session + " : " + channelUri);
			if (mClientCallbackInst != null) {
				mHandler.post(new Runnable() {
					@Override
					public void run() {
						mClientCallbackInst.sessionOnChannelRetuned(channelUri);
					}
				});

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

		@SystemApi
		public void onSessionEvent(Session session, String eventType, Bundle eventArgs) {
			Log.d(TAG, "onSessionEvent " + session + " eventType:" + eventType);
			try {
				if (eventType.equals(ITVSessionContext.EVENT_SESSION_CONTEXT_CREATED)) {
					IBinder binder = eventArgs.getBinder(ITVSessionContext.SESSION_CONTEXT);
					mSessionContext = ITVSessionContext.instance.asInterface(binder);
					
					mSessionContext.registerSessionContextCallbacks(sessionContextCallbacks);
					
					mTunerSession = mSessionContext.getITvTunerSession();
					sessionState = SESSION_STATE.SESSION_CREATED;
					if (mClientCallbackInst != null) {
						mHandler.post(new Runnable() {
							@Override
							public void run() {
								Log.d(TAG, "onSessionEvent sessionCreationSuccessfull");
								mClientCallbackInst.sessionCreationSuccessfull();
							}
						});
					}
				}
			} catch (Exception ex) {
				Log.d(TAG, "caught exception: " + ex.getMessage());
			}
		}
	}

	public SessionHandlerTIF(Context argContext, SESSION_PURPOSE argPurpose) {
		Log.d(TAG, "SessionHandlerTIF " + argPurpose);
		// constructor
		
		WorkerThread mEmptyThread = new WorkerThread("empty thread"); 
		if(mEmptyThread.isAlive() == false){
			mEmptyThread.start();
		}
		WorkerThread mWorkerThread = new WorkerThread("callback thread"); 
		if(mWorkerThread.isAlive() == false){
			mWorkerThread.start();
		}
		mSessionHandler = new Handler(mEmptyThread.getLooper());
		mContext = argContext;
		if (argPurpose == SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER) {
			mPurpose = ITVSessionContext.SESSION_TYPE_INSTALLER;
			TAG = SessionHandlerTIF.class.getName() + " " + mPurpose + ":";
		} else if (argPurpose == SESSION_PURPOSE.SESSION_PURPOSE_OBSERVER) {
			mPurpose = ITVSessionContext.SESSION_TYPE_MAIN_OBSERVER;
			TAG = SessionHandlerTIF.class.getName() + " " + mPurpose + ":";
		}else if (argPurpose == SESSION_PURPOSE.SESSION_PURPOSE_AUX) {
			mPurpose = ITVSessionContext.SESSION_TYPE_INSTALLER_AUX;
			TAG = SessionHandlerTIF.class.getName() + " " + mPurpose + ":";
		}
		mSessionCallback = new InstallerSessionCallback();
		sessionContextCallbacks = new SessionContextCallbacks();

		Log.d(TAG, "new handler");
		mHandler = new Handler(mWorkerThread.getLooper());

		mCallbackobject = new TvInputCallbackClass();

	}
	
	/**
	 * class WorkerThread: extends HandlerThread
	 * WorkerThread creates a thread with a looper. This looper is used by Handler to perform parallel tasks.
	 */
	class WorkerThread extends HandlerThread{

		public WorkerThread(String name) {
			super(name);
		}
	}
	
	public void setSurface(Surface surface) {
	Log.d(TAG, "setSurface " + surface);
		try {
		  mSession.setSurface(surface);
		} catch (Exception ex) {
		  Log.d(TAG, "Exception caught while closing session " + ex.getMessage());
		}
	}


	public void registerToSessionHandler(ISessionHandlerTIF argClientCallBackInst) {
		Log.d(TAG, "registerToSessionHandler " + argClientCallBackInst);
		mClientCallbackInst = argClientCallBackInst;
	}

	public void createNewSession() {
		Log.d(TAG, "createNewSession " + mContext);

		if (mContext == null) {
			return;
		}

		try {
			// get TIF service instance
			mTvInputManager = (TvInputManager) (mContext.getApplicationContext()).getSystemService(Context.TV_INPUT_SERVICE);

			if (mTvInputManager != null) {
				
				List<TvInputInfo> inputlist = mTvInputManager.getTvInputList();
				for(int index=0;index<inputlist.size();index++){
					TvInputInfo tinfo = (TvInputInfo) inputlist.get(index);
					Log.d(TAG, "tinfo ["+ index + "]:" + tinfo);
					if((tinfo != null) && (tinfo.getType() == TvInputInfo.TYPE_TUNER) &&
						(tinfo.getComponent().getPackageName().equals(ITVSessionContext.TUNERSERVICE_PKG_ID))){
						Log.d(TAG, "tuner id");
						createSessionURI = tinfo.getId();
						break;
					}
				}

				mHandler.post(new Runnable() {
					@Override
					public void run() {
						mTvInputManager.createSession(createSessionURI, mSessionCallback, mSessionHandler);
					}
				});

				mTvInputManager.registerCallback(mCallbackobject,mSessionHandler);
			}
		} catch (Exception ex) {
			Log.d(TAG, "caught exception: " + ex.getMessage());
		}
	}

	public void closeSession() {
		Log.d(TAG, "closeSession");
		if (mSession != null) {
			mSession.release();
		}
	}

	public ITVTunerSession getTunerSession() {
		Log.d(TAG, "getTunerSession " + mTunerSession);
		return mTunerSession;
	}

	public ITVSessionContext getSessionContext() {
		Log.d(TAG, "getTunerSession " + mSessionContext);
		return mSessionContext;
	}

	public void tuneWithBundle(final Bundle argBundle) {
		Log.d(TAG, "tuneWithBundle createSessionURI:" + createSessionURI + " argBundle:" + argBundle + " mSession:" + mSession);
		if ((mSession != null) && (argBundle != null)) {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					mSession.tune(ITvContractExtras.Channels.buildDefaultChannelUri(), argBundle);
				}
			});
		}
	}

	public SESSION_STATE getSessionState() {
		Log.d(TAG, "getSessionState " + sessionState);
		return sessionState;
	}
	
	private class TvInputCallbackClass extends TvInputCallback {

		@Override
		public void onInputAdded(String inputId) {
			Log.d(TAG,"onInputAdded " + inputId);
			mTvInputManager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(mTvInputManager!=null)
			{
				try{
					TvInputInfo tv = mTvInputManager.getTvInputInfo(inputId);
					
				}catch(Exception ee){
					Log.e(TAG,"onInputAdded exception"+ee.getMessage());
				}
			}
		}

		@Override
		public void onInputRemoved(String inputId) {
			Log.d(TAG,"onInputRemoved " + inputId);
			mTvInputManager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(mTvInputManager!=null){
				try{
					TvInputInfo tv = mTvInputManager.getTvInputInfo(inputId);
					
				}catch(Exception ee){
					Log.e(TAG,"onInputRemoved exception"+ee.getMessage());
				}
			}
		}

		@Override
		public void onInputStateChanged(String inputId, int state) {
			Log.d(TAG,"onInputStateChanged " + inputId + "state " + state);
			mTvInputManager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
			if(mTvInputManager!=null){
				
			}
		}
	}
}
