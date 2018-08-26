package org.droidtv.euinstallertc.model.mwapi;

import java.util.List;

import android.util.Log;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.Handler.Callback;
import android.content.Context;
import android.media.tv.TvInputManager.SessionCallback;
import android.media.tv.TvInputManager.Session;
import android.view.Surface;

import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tv.tvinput.ITVTunerSession.ITunerSessionCallbacks;
import org.droidtv.tv.tvinput.ITvContractExtras;
import android.media.tv.*;
import android.annotation.SystemApi;

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
	public String createSessionURI = "org.droidtv.tunerservice/.TunerService"; // initialized to default
	private ITunerSessionCallbacks tunerSessionCallbackInst;
	private boolean PendingSessionClose = false;
	private WorkerThread mEmptyThread, mWorkerThread;

	/*
	 * private static final int MSG_ = 0; private static final int
	 * MSG_STOPBACKGROUND = 1; private static final int MSG_STARTUPDATE = 2;
	 * private static final int MSG_STOPUPDATE = 3;
	 */

	public static enum SESSION_PURPOSE {
		SESSION_PURPOSE_INSTALLER, SESSION_PURPOSE_OBSERVER
	}

	public static enum SESSION_STATE {
		INVALID, SESSION_CREATED, SESSION_CREATION_INPRGRESS
	}

	public static enum SESSION_MEDIUM {
		ANALOG, CABLE, ANTENNA
	}

	public interface ISessionHandlerTIF {
		public void sessionCreationFailed();

		public void sessionCreationSuccessfull();

		public void sessionReleased();

		public void sessionOnChannelRetuned(Uri channelUri);
		
		public void sessionOnChannelRetunedFailed ();
		
		public void sessionOnChannelChangeStarted ();

		public void sessionOnChannelChangeCompleted (Uri channelUri);		
	}
	
	private class SessionContextCallbacks extends ITVSessionContext.ISessionContextCallbacks {
		
		@Override
		public void onReAcquireInterfaces() {
			if (mClientCallbackInst != null) {
				
			}
		}
	}
	
	public class ImplITunerSessionCallbacks extends ITunerSessionCallbacks{

		@Override
		public void onTuneFailed(String inputid, Uri channelUri, int reason) {
			//super.onTuneFailed(inputid, channelUri, reason);
			
			if (mClientCallbackInst != null) {
				mHandler.post(new Runnable() {
					@Override
					public void run() {
						mClientCallbackInst.sessionOnChannelRetunedFailed();
					}
				});
			}
			
		}
		
		@Override
		public void onTuneStarted(String inputid, Uri channelUri, Bundle bundle) {
			if (mClientCallbackInst != null) {
				mHandler.post(new Runnable() {
					@Override
					public void run() {
						mClientCallbackInst.sessionOnChannelChangeStarted();
					}
				});
			}
		}

		
		@Override
		public void onTuneCompleted(String inputid, final Uri channelUri, Bundle bundle) {
			//Log.d(TAG, "onTuneCompleted() is called. mClientCallbackInst:" + mClientCallbackInst + "  bundle:" + bundle + "  Request type:" + bundle.getString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE));
			if ((mClientCallbackInst != null) && (bundle != null) && (bundle.getString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE).equalsIgnoreCase(ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT))) {
				mHandler.post(new Runnable() {
					@Override
					public void run() {
						mClientCallbackInst.sessionOnChannelChangeCompleted(channelUri);
					}
				});
			}
			else{
				if(bundle != null){
					Log.d(TAG, "onTuneCompleted  RequestType: " + bundle.getString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE));			}
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
				} else if (PendingSessionClose == true) {
					/* No need to proceed further. CloseRequest already came */
					try{
						Log.d (TAG, "Session Release request honored");
						mSession.release();
						PendingSessionClose = false;
						sessionState = SESSION_STATE.INVALID;
					}catch(Exception ex){
						Log.d(TAG,"Caught Exception: " + ex.getMessage());
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
				if (PendingSessionClose == true) {
					/* No need to proceed further. CloseRequest already came */
					try{
						Log.d (TAG, "Session Release request honored");
						mSession.release();
						PendingSessionClose = false;
						sessionState = SESSION_STATE.INVALID;
					}catch(Exception ex){
						Log.d(TAG,"Caught Exception: " + ex.getMessage());
					}
				} else if (eventType.equals(ITVSessionContext.EVENT_SESSION_CONTEXT_CREATED)) {
					IBinder binder = eventArgs.getBinder(ITVSessionContext.SESSION_CONTEXT);
					mSessionContext = ITVSessionContext.instance.asInterface(binder);
					
					mSessionContext.registerSessionContextCallbacks(sessionContextCallbacks);
					
					mTunerSession = mSessionContext.getITvTunerSession();
					
					mTunerSession.registerTunerSessionCallbacks(tunerSessionCallbackInst);
					
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
		
		mEmptyThread = new WorkerThread("empty thread"); 
		if(mEmptyThread.isAlive() == false){
			mEmptyThread.start();
		}
		mWorkerThread = new WorkerThread("callback thread"); 
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
		}
		mSessionCallback = new InstallerSessionCallback();
		sessionContextCallbacks = new SessionContextCallbacks();

		Log.d(TAG, "new handler");
		mHandler = new Handler(mWorkerThread.getLooper());

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
			sessionState = SESSION_STATE.SESSION_CREATION_INPRGRESS;
			PendingSessionClose = false;
			// get TIF service instance
			mTvInputManager = (TvInputManager) (mContext.getApplicationContext()).getSystemService(Context.TV_INPUT_SERVICE);
			tunerSessionCallbackInst = new ImplITunerSessionCallbacks();
					
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
			}
		} catch (Exception ex) {
			Log.d(TAG, "caught exception: " + ex.getMessage());
		}
	}

	public void closeSession() {
		Log.d(TAG, "closeSession");
		if (mTunerSession != null) {
			mTunerSession.unregisterTunerSessionCallbacks(tunerSessionCallbackInst);
		}
		if (mSession != null) {
			try{
				mSession.release();
			}catch(Exception ex){
				Log.d(TAG,"Caught Exception: " + ex.getMessage());
			}
		}
		/* CloseSesion request came before the SessionCreated notification */
		if (sessionState == SESSION_STATE.SESSION_CREATION_INPRGRESS)
		{
			PendingSessionClose = true;
		}
		
		exitThreads();
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
	public void tune(final Uri uri, final Bundle argBundle) {
		Log.d(TAG, "tune URI:" + uri + " argBundle:" + argBundle + " mSession:" + mSession);
		if (mSession != null) {
			mHandler.post(new Runnable() {
				@Override
				public void run() {
					mSession.tune(uri, argBundle);
				}
			});
		}
	}

	public SESSION_STATE getSessionState() {
		Log.d(TAG, "getSessionState " + sessionState);
		return sessionState;
	}
	private void exitThreads(){
		try{
			if(mEmptyThread != null){
				mEmptyThread.quit();
			}
		}catch(Exception ex){}
		
		try{
			if(mWorkerThread != null){
				mWorkerThread.quit();
			}
		}catch(Exception ex){}
	}
}
