package org.droidtv.tunerservice;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;

import android.content.ComponentName;
import android.content.Context;
import android.content.pm.ResolveInfo;
import android.media.tv.TvContentRating;
import android.media.tv.TvInputService;
import android.media.tv.TvTrackInfo;
import android.media.tv.TvInputInfo;
import android.media.tv.TvInputHardwareInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Surface;
import android.view.View;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import org.droidtv.tv.tvinput.*;
import org.droidtv.tunerservice.channelfilter.ChannelFilter;
import org.droidtv.tunerservice.recording.RecService;
import org.droidtv.tunerservice.tvmanager.AbstractManager;
import org.droidtv.tunerservice.tvmanager.AuxTVManager;
import org.droidtv.tunerservice.tvmanager.MainTVManager;
import org.droidtv.tunerservice.tvmanager.InstallerManager;
import org.droidtv.tunerservice.tvmanager.EpgManager;
import org.droidtv.tunerservice.tvmanager.MainCIManager;
import org.droidtv.tunerservice.tvmanager.AuxCIManager;
import org.droidtv.tunerservice.tvmanager.OadManager;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.TunerServiceHelpContext;
import org.droidtv.tv.media.IInstallerService;
import org.droidtv.tv.media.TvMediaPlayerContext;
import org.droidtv.tv.tvinput.TVSessionContext;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.SessionContextCallbacks;
import org.droidtv.tv.tvinput.RecordCallbacks;
import org.droidtv.tv.tvinput.TunerSessionCallbacks;
import org.droidtv.tv.tvinput.TVCIControlCallback;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tv.tvinput.ITVTunerSession.MultiFeedServiceInfo;
import org.droidtv.tv.tvinput.ITVTunerSession.TimeshiftInfo;
import org.droidtv.tv.tvinput.ITVExtensionSession;

public class TunerService extends TvInputService{
	private static final String TV_INPUT_ID     			=	"TPVISION_CHANNEL_INPUT"; //TODO: Assign a non-null input id . The same must be used in the database
	private static final String LOG_TAG						=	"TunerService";
	private MainTVManager mMainTvManager					=	null;
	private AuxTVManager mAuxManager						=	null;
	private EpgManager mForegroundEpgManager				= 	null;
	private EpgManager mBackgroundEpgManager				= 	null;
	private InstallerManager mInstallerManager				=	null;
	private InstallerManager mAuxInstallerManager			=	null;
	private MainCIManager mMainCIManager					=	null;
	private AuxCIManager  mAuxCIManager						=	null;
	private OadManager	  mOadManager						=   null;
	private PlayTVMediaPlayerFactory factory				=   null; 
    private ChannelFilter mChannelFilter    				= 	null;
	private TunerServiceHelpContext mTunerServiceHelpContext= 	null;
    
	
	@Override
	public void onCreate(){
		Handler mTunerServiceHandler		=	null;		
		Log.v(LOG_TAG,"onCreate called for TunerService");
		mTunerServiceHandler	= new Handler();
		factory 				= new PlayTVMediaPlayerFactory(this);
			
		Handler mhandler=new Handler();
		if(mhandler!=null){
			mhandler.post(new Runnable() {
				
				@Override
				public void run() {
					RecService.createInstance(TunerService.this);
				}
			});
		}
		if(mTunerServiceHandler != null){
			mTunerServiceHandler.post(new Runnable(){
				@Override
				public void run(){					
					mMainTvManager 					=	new MainTVManager(TunerService.this);
					mMainTvManager.MainTvManagerInit();
					mAuxManager						=	new AuxTVManager(TunerService.this);
					mInstallerManager				=	new InstallerManager(TunerService.this);
					mAuxInstallerManager			=	new InstallerManager(TunerService.this);
					mForegroundEpgManager			=	new EpgManager(TunerService.this, true);
					mBackgroundEpgManager			=	new EpgManager(TunerService.this, false);
					mMainCIManager					=	new MainCIManager(TunerService.this);					
					mAuxCIManager					=	new AuxCIManager(TunerService.this);
					mOadManager						=	new OadManager(TunerService.this);
					mChannelFilter 					=	ChannelFilter.getChannelFilterInstance(TunerService.this);					
					mTunerServiceHelpContext		=	TunerServiceHelpContext.getInstance();
					
					try {
						mMainCIManager.setMainTvManager(mMainTvManager);
						mAuxCIManager.setAuxTvManager(mAuxManager);	
						mTunerServiceHelpContext.setTunerServiceContext(TunerService.this);
						mTunerServiceHelpContext.startHelpService();
					} catch (Exception e) {
						e.printStackTrace();
					}
					
					Intent intent = new Intent("org.droidtv.euinstallertc.INSTALLER");
					TunerService.this.bindService(intent, mInstallServConnection, Context.BIND_IMPORTANT | Context.BIND_AUTO_CREATE);
				}
			});
		}			
	}
	
	private IInstallerService mInstallerServBinder = null;
	private ServiceConnection mInstallServConnection = new ServiceConnection() {
		
		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d(LOG_TAG,"Installer service is disConnected.");			
		}
		
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(LOG_TAG,"Installer service is connected.");
			
			mInstallerServBinder = IInstallerService.Instance.asInterface(service);			
		}
	};
	
	
	public Session onCreateSession(String pInputId){
		TunerSession mSession	=	null;		
		mSession = new TunerSession(this);			
		return mSession;
	}
	
	public TvInputInfo onHardwareAdded(TvInputHardwareInfo hardwareInfo) {
		TvInputInfo tvInputInfo 			= null;
		
		if(hardwareInfo.getType() == TvInputHardwareInfo.TV_INPUT_TYPE_TUNER){			
			ResolveInfo resolveInfo 			= getPackageManager().resolveService(
						new Intent(SERVICE_INTERFACE).setClass(this, getClass()),	
							PackageManager.GET_SERVICES | PackageManager.GET_META_DATA);
			
			String label 						= getString(org.droidtv.ui.strings.R.string.MAIN_ANTENNA_TV_SELECTED);
			Uri iconUri							= Uri.parse(org.droidtv.ui.tvwidget2k15.R.drawable.watch_tv_48x36_38+"");

			try{
				tvInputInfo = TvInputInfo.createTvInputInfo(this, resolveInfo, hardwareInfo,label, iconUri);
			}
			catch(Exception e){
				Log.e(LOG_TAG,"exception caught : "+e.toString());
			}
		}
		return tvInputInfo;
    }
	

	public class TunerSession extends Session {
		Handler mSessionHandler								= null;
		private TVSessionContextStub	mTVSessionContext	= null;
		private TVTunerSessionStub mTVTunerSession 			= null;
		private TVRecordPlaybackStub mTVRecordPlayback		= null;
		private TVCIControlStub mTVCIControl				= null;
		private AbstractManager mTunerManager				= null;
		private Context mContext							= null;
		private boolean mIsControllerSession				= true;
		private	boolean isMainSession						= false;		
		private OverlayManager mOverlayManager				= null; 
		private Surface mSurface							= null;
		private String mSessionType							= ITVSessionContext.SESSION_TYPE_MAIN_WATCH;
		private String LOG_TAG								= "TunerSession";
		
		public TunerSession(Context pContext) {			
            super(pContext);	
			mContext				= pContext;			
			mTVSessionContext		= new TVSessionContextStub();
			mTVTunerSession			= new TVTunerSessionStub();
			mTVRecordPlayback		= new TVRecordPlaybackStub();
			mTVCIControl			= new TVCIControlStub();	
			mSessionHandler			= new Handler();
			if(mSessionHandler != null){
				mSessionHandler.post(new Runnable(){
					public void run(){
					  String lSessionEvent               = ITVSessionContext.EVENT_SESSION_CONTEXT_CREATED;
					  Bundle lContextData                = new Bundle();
					  IBinder lSessionContext            = getSessionContext();
					  lContextData.putBinder(ITVSessionContext.SESSION_CONTEXT, lSessionContext);
					  notifySessionEvent(lSessionEvent, lContextData);
					}
				});
			}
			/*Assign default manager to a session*/
			mTunerManager = mMainTvManager;
			mTunerManager.registerListener(this);
        }	
		
		public IBinder getSessionContext(){
			return mTVSessionContext.asBinder();
		}	
		
		public void setOverlayViewEnabled(final boolean pEnable){
			Log.v(LOG_TAG,"setOverlayViewEnabled called "+ pEnable);
			super.setOverlayViewEnabled(pEnable);
		}
		
		public void notifySessionEvent(final String pEventType, final Bundle pEventArgs) {
			super.notifySessionEvent(pEventType,pEventArgs);
		}
		
		public void notifyChannelRetuned(final Uri pChannelUri) {
			Log.v(LOG_TAG,"notifyChannelRetuned called with Uri "+pChannelUri);
			super.notifyChannelRetuned(pChannelUri);
		}
		
		public void notifyTracksChanged(final List<TvTrackInfo> tracks){
			super.notifyTracksChanged(tracks);
		}
		
		public void notifyVideoAvailable(){
			super.notifyVideoAvailable();
		}
		
		public void notifyVideoUnavailable(final int reason){
			super.notifyVideoUnavailable(reason);
		}
		
		public void notifyContentAllowed(){
			super.notifyContentAllowed();
		}
		
		public void notifyContentBlocked(final TvContentRating rating){
			super.notifyContentBlocked(rating);
		}
		
		public void onRelease(){
			Log.v(LOG_TAG,"onRelease called");
			mTunerManager.unRegisterListener(this);
			mTVTunerSession.clearListeners();
			mTVSessionContext.clearListeners();
			mTVRecordPlayback.clearListeners();
			mTVCIControl.clearListeners();
			if(mIsControllerSession){
				//release manager only if this session is it's active session
				onSetSurface(null);
				mTunerManager.release(this);				
			}
			mOverlayManager = null; //cleanup on overlaymanager to be handled.
			mSurface 		= null;
		}
		
		public void onSetMain(boolean isMainSession) {
			isMainSession	=	isMainSession;
        }
		
		public boolean onSetSurface(Surface surface){
			Log.i(LOG_TAG,"onSetSurface called " + ((surface == null)?"surface null":"valid surface"));
			if(mTunerManager.getCurrentActiveSession() == this) {
				mTunerManager.setSurface(surface);
			}else {
				Log.i(LOG_TAG,"onSetSurface called on NON_ACTIVE session, so ignore!!!");
			}			
			mSurface = surface;
			return false;
		}
		
		public void onSurfaceChanged(int format, int width, int height) {
			Log.i(LOG_TAG,"onSurfaceChanged with format = " + format +" width = "+ width + " height = "+height);
			mTunerManager.dispatchSurfaceChanged(format, width, height, mSurface);
        }
		
		public void onSetStreamVolume(float volume){
		}
		
		public boolean onTune(Uri channelUri){
			Log.i(LOG_TAG,"onTune called with Uri "+ channelUri);
			if(mIsControllerSession) {
				mTunerManager.setSession(this,mSurface);
			}
			mTunerManager.tune(channelUri);
			return true ;
		}
		
		public boolean onTune(Uri channelUri,Bundle params){
			Log.i(LOG_TAG,"onTune called with Bundle " + channelUri);
			if(mIsControllerSession) {
				mTunerManager.setSession(this,mSurface);
			}
			mTunerManager.tune(channelUri,params);
			return true ;
		}
		
		public void onSetCaptionEnabled(boolean enabled){
			Log.i(LOG_TAG,"onSetCaptionEnabled called " + enabled);
			mTunerManager.setCaptionEnabled(enabled);
		}
		
		public void onUnblockContent(TvContentRating pUnblockedRating){
			mTunerManager.onUnblockContent(pUnblockedRating);
        }
		
		public boolean onSelectTrack(int type, String trackId){
			Log.i(LOG_TAG,"onSelectTrack called");
			mTunerManager.selectTrack(type, trackId);
            return false;
        }
		
		public boolean onUnselectTrack(TvTrackInfo track) {
			Log.i(LOG_TAG,"onUnselectTrack called");
            return false;
        }			
		
		public void onAppPrivateCommand(String action, Bundle data) {
			if((action != null) && action.equals(ITVSessionContext.APP_PRIVATE_COMMAND_SESSION_TYPE) && (data != null)){				
				String lSessionType = data.getString(ITVSessionContext.KEY_SESSION_TYPE);
				LOG_TAG				= "TunerSession : "+lSessionType;
				if(lSessionType != null){
					initializeSession(lSessionType);
					Handler lhandler = new Handler();
					if(lhandler != null){
						lhandler.post(new Runnable() {							
							@Override
							public void run() {
								mTunerManager.notifyMediaEvents(TunerSession.this);
							}
						});
					}					
				}				
			}else if((action != null) && action.equals(ITVSessionContext.APP_PRIVATE_COMMAND_OVERLAY_CONTROL) && (data != null)) {
				String lOverlay = data.getString(ITVSessionContext.KEY_ENABLE_OVERLAY);
				if(lOverlay != null){
					boolean enableOverlay = (Integer.parseInt(lOverlay) == 1) ? true : false;
					if(enableOverlay) {
						Log.i(LOG_TAG,"enabling overlay!!!");
						setOverlayViewEnabled(true);	
					}
				}
				int overlayViewStatus = data.getInt(ITVSessionContext.KEY_ENABLE_OVERLAY_VIEW,-1);
				if(overlayViewStatus != -1) {
					if(mOverlayManager != null) {
						mOverlayManager.setOverLayViewStatus(overlayViewStatus);
					} else if(mMainTvManager != null){
						mMainTvManager.setOverLayViewStatus(overlayViewStatus);
					}
				}
			}
        }
		
		@Override
		public View onCreateOverlayView() {			
			Log.i(LOG_TAG,"onCreateOverlayView");
			if(mSessionType.equals(ITVSessionContext.SESSION_TYPE_MAIN_WATCH)){
				if(mOverlayManager == null) {
					mOverlayManager	= new OverlayManager(mContext);
				}else {
					Log.i(LOG_TAG,"overlay already created for this session!!!");
				}
				mTunerManager.setOverlayManager(mOverlayManager);
				mMainCIManager.setOverlayManager(mOverlayManager);
				mAuxCIManager.setOverlayManager(mOverlayManager);
				return mOverlayManager.getOverlayView();
			}else {
				Log.i(LOG_TAG,"overlay not created as this is non-mainwatch session!!!");
			}
			return null;
        }
		
		public boolean onKeyDown(int keyCode, KeyEvent event) {
			Log.i(LOG_TAG,"onKeyDown called with keycode = "+keyCode);
			boolean isKeyConsumed = false;
			if(mOverlayManager!=null) {
				isKeyConsumed =  mOverlayManager.onKeyDown(keyCode,event);
				if(isKeyConsumed == false){
					isKeyConsumed = mMainCIManager.onKeyDown(keyCode,event);
				}
			}
			return isKeyConsumed;
        }
		
		public boolean onKeyLongPress(int keyCode, KeyEvent event) {
			Log.v(LOG_TAG,"onKeyLongPress called with keycode = "+keyCode);
            return false;
        }
		
		public boolean onKeyMultiple(int keyCode, int count, KeyEvent event) {
			Log.v(LOG_TAG,"onKeyMultiple called with keycode = "+keyCode);
            return false;
        }
		
		public boolean onKeyUp(int keyCode, KeyEvent event) {
			Log.i(LOG_TAG,"onKeyUp called with keycode = "+keyCode);
			boolean isKeyConsumed = false;
			if(mOverlayManager!=null) {
				isKeyConsumed = mOverlayManager.onKeyUp(keyCode,event);
				if(isKeyConsumed == false){
					isKeyConsumed = mMainCIManager.onKeyUp(keyCode,event);
				}
			}
            return isKeyConsumed;
        }	
		
		private void initializeSession(String pSessionType){
			AbstractManager prevTunerManager = mTunerManager;
			if(mTunerManager != null) {
				//by default, session would be mapped to mainTvManager
				//Hence unregister as soon as session type gets assigned to attach respective managers.
				mTunerManager.unRegisterListener(this);
			}
			if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_MAIN_WATCH)){			
				mTunerManager 	= mMainTvManager;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_MAIN_WATCH_IN_PIP)){
				mTunerManager 	= mMainTvManager;		
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_INTERACTIVE_ENGINE)){			
				mTunerManager 		= mMainTvManager;
				mIsControllerSession= false;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_INSTALLER)){			
				mTunerManager = mInstallerManager;
			}else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_INSTALLER_AUX)){
				mTunerManager = mAuxInstallerManager;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_EPG_ACQUISITION)){
				mTunerManager = mBackgroundEpgManager;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_EPG_FOREGROUND_ACQUISITION)){
				mTunerManager = mForegroundEpgManager;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_PIP_WATCH)) {
				mTunerManager	= mAuxManager;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_PIP_PREVIEW)){
				mTunerManager	= mAuxManager;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_MAIN_OBSERVER)){
				mTunerManager 		= mMainTvManager;
				mIsControllerSession= false;			
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_AUX_OBSERVER)){
				mTunerManager		= mAuxManager;
				mIsControllerSession= false;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_MAIN_CI)){
				mTunerManager		= mMainCIManager;
				mIsControllerSession= false;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_AUX_CI)){
				mTunerManager		= mAuxCIManager;
				mIsControllerSession= false;
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_OAD)) {
				mTunerManager		= mOadManager;				
			}
			else if(pSessionType.equals(ITVSessionContext.SESSION_TYPE_CHANNEL_APP)) {
				mTunerManager		= mMainTvManager;
				mIsControllerSession= false;
			}
			else {
				Log.i(LOG_TAG,"initializeSession called... session type = unknown ");
				mIsControllerSession= false;
				mTunerManager 		= mMainTvManager;				
			}
			if(prevTunerManager != mTunerManager) {
				//change of manager due to non-main watch session types
				mTVTunerSession.reRouteListeners(prevTunerManager);
				mTVSessionContext.reRouteListeners(prevTunerManager);
				mTVRecordPlayback.reRouteListeners(prevTunerManager);
				mTVCIControl.reRouteListeners(prevTunerManager);
			}
			mTunerManager.registerListener(this);			
			mTunerManager.setSessionType(pSessionType);
			mSessionType =	pSessionType;
		}		
		
		public class TVSessionContextStub extends TVSessionContext.Stub{
			private Context mContext	= null;
			private Map<IBinder, Client> mListeners	= new HashMap<IBinder, Client>();
			
			public IBinder getITvTunerSession(){
				return mTVTunerSession.asBinder();				
			}
				
			public IBinder getITvRecordPlayback(){
				return mTVRecordPlayback.asBinder();
			}
			
			public IBinder getITVCIControl() {
				return mTVCIControl.asBinder();
			}
			
			public IBinder getITVExtensionSession(){
		            return null;	
	                }
			
			public TvMediaPlayerContext getTvMediaPlayerContext(){
				try{
					return (mTunerManager.getTvMediaPlayerContext());		
				}catch(Exception e){
					return null;
				}				
			}
			public void registerSessionContextCallbacks(IBinder binder){
				synchronized(mListeners) {
					if(!mListeners.containsKey(binder)) {
						try {
							SessionContextCallbacks callback = SessionContextCallbacks.Stub.asInterface(binder);
							Client mClient = new Client(binder,callback);						
							binder.linkToDeath(mClient,0);
							mListeners.put(binder,mClient);
							mTunerManager.registerSessionContextCallbacks(callback);
							}catch (RemoteException e) {
							Log.d(LOG_TAG,"registerSessionContextCallbacks:RemoteException");
						}
					}
				}
			}
			
			public void unregisterSessionContextCallbacks(IBinder binder){	
				synchronized(mListeners) {
					if(mListeners.containsKey(binder)) {		
						mTunerManager.unregisterSessionContextCallbacks(mListeners.get(binder).getCallback());
						binder.unlinkToDeath(mListeners.get(binder),0);
						mListeners.remove(binder);
					}
				}
			}
			
			private class Client implements IBinder.DeathRecipient {
				private final IBinder mBinder;
				private SessionContextCallbacks mCallback = null;
				
				public Client(IBinder binder,SessionContextCallbacks callback) {
					mBinder 	= 	binder;
					mCallback	=	callback;
				}
				
				public SessionContextCallbacks getCallback() {
					return mCallback;
				}
				
				@Override
				public void binderDied() {
					Log.d(LOG_TAG, "binderDied() binder=" + mBinder);
					synchronized(mListeners) {
						if(mListeners.containsKey(mBinder)) {
							mTunerManager.unregisterSessionContextCallbacks(mCallback);
							mListeners.remove(mBinder);
						}
					}
				}
			}
			
			public void clearListeners() {
				synchronized(mListeners) {
					Iterator lIterator = mListeners.keySet().iterator();
					while(lIterator.hasNext()){
						IBinder binder = (IBinder)lIterator.next();
						mTunerManager.unregisterSessionContextCallbacks(mListeners.get(binder).getCallback());
						binder.unlinkToDeath(mListeners.get(binder),0);
					}
					mListeners.clear();
				}
			}
			
			public void reRouteListeners(AbstractManager prevTunerManager) {
				synchronized(mListeners) {
					Iterator lIterator = mListeners.keySet().iterator();
					while(lIterator.hasNext()){
						IBinder binder = (IBinder)lIterator.next();
						prevTunerManager.unregisterSessionContextCallbacks(mListeners.get(binder).getCallback());
						mTunerManager.registerSessionContextCallbacks(mListeners.get(binder).getCallback());
					}
				}			
			}
		}
		
		public class TVRecordPlaybackStub extends TVRecordPlayback.Stub{
			private Map<IBinder, Client> mListeners	= new HashMap<IBinder, Client>();
			
			public void pause(){
				Log.v(LOG_TAG,"pause called");
				mTunerManager.pause();
			}
			
			public void stop(){
				Log.v(LOG_TAG,"stop called");
				mTunerManager.stop();
			}
	
			public void resume(){
				Log.v(LOG_TAG,"resume called");
				mTunerManager.resume();
			}
			
			public void seekTo(int msecs){
				Log.v(LOG_TAG,"seekTo called:msecs-"+msecs);
				mTunerManager.seekTo(msecs);
			}
			
			public void setSpeed(int speed, boolean forward){
				Log.v(LOG_TAG,"setSpeed called :speed-"+speed+"forward-"+forward);
				mTunerManager.setSpeed(speed,forward);
			}
			
			public int getCurrentDuration(){
				return mTunerManager.getCurrentDuration();
			}
			
			public int getTotalDuration(){
				return mTunerManager.getTotalDuration();
			}
			
			public int getBufferedDuration(){
				return mTunerManager.getBufferedDuration();
			}
			
			public int getPlaybackState(){
				return mTunerManager.getPlaybackState();
			}
			
			public void enableTrickModes(boolean enable){
				Log.v(LOG_TAG,"enableTrickModes called : "+enable);
				mTunerManager.enableTrickModes(enable);
			}
			
			public boolean getTrickModeStatus(){
				return mTunerManager.getTrickModeStatus();
			}

			public void registerRecordCallback(IBinder binder){
				synchronized(mListeners) {
					if(!mListeners.containsKey(binder)) {
						try {
							RecordCallbacks callback = RecordCallbacks.Stub.asInterface(binder);
							Client mClient = new Client(binder,callback);
							binder.linkToDeath(mClient,0);
							mListeners.put(binder,mClient);
							mTunerManager.registerRecordCallback(callback);
						}catch (RemoteException e) {
							Log.d(LOG_TAG,"registerRecordCallback : RemoteException");
						}
					}	
				}
			}
	
			public void unregisterRecordCallbacks(IBinder binder){
				synchronized(mListeners) {
					if(mListeners.containsKey(binder)) {		
						mTunerManager.unregisterRecordCallbacks(mListeners.get(binder).getCallback());
						binder.unlinkToDeath(mListeners.get(binder),0);
						mListeners.remove(binder);
					}
				}
			}
						
			private class Client implements IBinder.DeathRecipient {
				private final IBinder mBinder;
				private RecordCallbacks mCallback = null;
				
				public Client(IBinder binder, RecordCallbacks callback) {
					mBinder 	= 	binder;
					mCallback	=	callback;
				}

				public RecordCallbacks getCallback() {
					return mCallback;
				}
				
				@Override
				public void binderDied() {
					Log.d(LOG_TAG, "binderDied() binder=" + mBinder);
					synchronized(mListeners) {
						if(mListeners.containsKey(mBinder)) {
							mTunerManager.unregisterRecordCallbacks(mCallback);
							mListeners.remove(mBinder);
						}
					}
				}
			}
			
			public void clearListeners() {
				synchronized(mListeners) {
					Iterator lIterator = mListeners.keySet().iterator();
					while(lIterator.hasNext()){
						IBinder binder = (IBinder)lIterator.next();
						mTunerManager.unregisterRecordCallbacks(mListeners.get(binder).getCallback());
						binder.unlinkToDeath(mListeners.get(binder),0);					
					}
					mListeners.clear();
				}
			}
			
			public void reRouteListeners(AbstractManager prevTunerManager) {
				synchronized(mListeners) {
					Iterator lIterator = mListeners.keySet().iterator();
					while(lIterator.hasNext()){
						IBinder binder = (IBinder)lIterator.next();
						prevTunerManager.unregisterRecordCallbacks(mListeners.get(binder).getCallback());
						mTunerManager.registerRecordCallback(mListeners.get(binder).getCallback());
					}
				}			
			}
		}
		
		
		public class TVTunerSessionStub extends TVTunerSession.Stub{
			private Map<IBinder, Client> mListeners	= new HashMap<IBinder, Client>();
			
			public void timeshiftPause(){
				Log.v(LOG_TAG,"pauseTimeshift called");
				mTunerManager.timeshiftPause();
			}

			public void timeshiftStop(){
				Log.v(LOG_TAG,"timeshiftStop called");
				mTunerManager.timeshiftStop();
			}

			public void timeshiftResume(){
				Log.v(LOG_TAG,"resumeTimeshift called");
				mTunerManager.timeshiftResume();
			}

			public void timeshiftSeekTo(int msecs){
				Log.v(LOG_TAG,"timeshiftSeekTo called:msecs-"+msecs);
				mTunerManager.timeshiftSeekTo(msecs);
			}

			public void timeshiftSetSpeed(int speed, boolean forward){
				Log.v(LOG_TAG,"timeshiftSetSpeed called:speed-"+speed+"forward-"+forward);
				mTunerManager.timeshiftSetSpeed(speed, forward);
			}

			public int getTimeshiftCurrentDuration(){
				return mTunerManager.getTimeshiftCurrentDuration();
			}

			public int getTimeshiftTotalDuration(){
				return mTunerManager.getTimeshiftTotalDuration();
			}

			public int getTimeshiftBufferedDuration(){
				return mTunerManager.getTimeshiftBufferedDuration();
			}

			public int getTimeshiftPlaybackState(){
				return mTunerManager.getTimeshiftPlaybackState();
			}

			public int getTimeshiftRecordingStatus(){
				return mTunerManager.getTimeshiftRecordingStatus();
			}

			public TimeshiftInfoImpl getTimeshiftInfo(){
				TimeshiftInfo timeshiftInfo;
				timeshiftInfo = mTunerManager.getTimeshiftInfo();
				TimeshiftInfoImpl timeshiftInfoImpl = new TimeshiftInfoImpl(timeshiftInfo);
				return timeshiftInfoImpl;
			}

			public void enableTimeshiftTrickModes(boolean enable){
				Log.v(LOG_TAG,"enableTimeshiftTrickModes called:enable-"+enable);
				mTunerManager.enableTimeshiftTrickModes(enable);
			}

			public boolean getTimeshiftTrickModeStatus(){
				return mTunerManager.getTimeshiftTrickModeStatus();
			}

			public Uri getSelectedURI(){
				return mTunerManager.getSelectedURI();
			}
	
			public Uri getNextURI(Uri uri){
				return mTunerManager.getNextURI(uri);
			}
			
			public Uri getPreviousURI(Uri uri){
				return mTunerManager.getPreviousURI(uri);
			}
			
			public boolean getLockStatus(){
				return mTunerManager.getLockStatus();
			}
			
			public boolean getRunningStatus(){
				return mTunerManager.getRunningStatus();
			}
			public String  getParentalRating(){
				TvContentRating mTransmissionRating  = null;
				mTransmissionRating = mTunerManager.getParentalRating() ;
				if ( mTransmissionRating != null )
				{
					return mTransmissionRating.flattenToString();
				}
				else
				{
					Log.d(LOG_TAG,"mTransmissionRating is recieved as null");
					return null;
				}
			}

			public int[]  getPrivatePIDInfo(){
				return mTunerManager.getPrivatePIDInfo();
			}

			public byte[]  getOipfSiDescriptor(){
				return mTunerManager.getOipfSiDescriptor();
			}
			
			public boolean hasTeletext(){
				return mTunerManager.hasTeletext();
			}
			
			public void unselectTrack(int type){
				Log.v(LOG_TAG,"unselectTrack called");
				mTunerManager.unselectTrack(type);
			}
			
			public void setTrackMuteStatus(int type, boolean mute){
				Log.v(LOG_TAG,"setTrackMuteStatus called :mute-"+mute+"type-"+type);
				mTunerManager.setTrackMuteStatus(type , mute);
			}
			
			public boolean  getTrackMuteStatus(int type){
				return mTunerManager.getTrackMuteStatus(type);
			}
			
			public boolean getTrackScramblingStatus(int type){
				return mTunerManager.getTrackScramblingStatus(type);
			}
			
			public List<MultiFeedServiceInfoImpl> getMultiFeedTracks(){
				List<MultiFeedServiceInfo> multifeedserviceInfo;
				List<MultiFeedServiceInfoImpl> multifeedserviceInfoImpl = new ArrayList<MultiFeedServiceInfoImpl>();
				multifeedserviceInfo = mTunerManager.getMultiFeedTracks();
				for(int i=0;i<multifeedserviceInfo.size();i++)
				{
					MultiFeedServiceInfoImpl serviceInfoImpl = new MultiFeedServiceInfoImpl(multifeedserviceInfo.get(i).mID,multifeedserviceInfo.get(i).mExtra);
					multifeedserviceInfoImpl.add(serviceInfoImpl);
				}
				return multifeedserviceInfoImpl;
			}
			
			public String getSelectedMultiFeedTrack() {
				return mTunerManager.getSelectedMultiFeedTrack();
			}
			
			public void selectMultiFeedTrack(String trackId){
				Log.v(LOG_TAG,"selectMultiFeedTrack called:trackId-"+trackId);
				mTunerManager.selectMultiFeedTrack(trackId);
			}
			
			public void loadVideoManagerCache(int cacheid){
				Log.v(LOG_TAG,"loadVideoManagerChache called");
				mTunerManager.loadVideoManagerCache(cacheid);
			}
			
			public void relayoutVideo(int left, int top, int width, int height){
				Log.v(LOG_TAG,"relayoutVideo called");
				mTunerManager.relayoutVideo(left,top,width,height);
			}
			
			public void enableAudio(boolean status){
				mTunerManager.enableAudio(status);
			}
			
			public boolean getAudioStatus(){
				return mTunerManager.getAudioStatus();
			}
			
			public int getCurrentMediaMode(){
				return mTunerManager.getCurrentMediaMode();
			}
			
			public void registerTunerSessionCallbacks(IBinder binder){
				synchronized(mListeners) {
					if(!mListeners.containsKey(binder)) {
						try {
							TunerSessionCallbacks callback = TunerSessionCallbacks.Stub.asInterface(binder);
							Client mClient = new Client(binder,callback);
							binder.linkToDeath(mClient,0);
							mListeners.put(binder,mClient);
							mTunerManager.registerTunerSessionCallbacks(callback);
						}catch (RemoteException e) {
							Log.d(LOG_TAG,"registerTunerSessionCallbacks : RemoteException");
						}
					}
				}
			}
			
			public void unregisterTunerSessionCallbacks(IBinder binder){
				synchronized(mListeners) {
					if(mListeners.containsKey(binder)) {
						mTunerManager.unregisterTunerSessionCallbacks(mListeners.get(binder).getCallback());
						binder.unlinkToDeath(mListeners.get(binder),0);
						mListeners.remove(binder);
					}
				}
			}		
			
			private class Client implements IBinder.DeathRecipient {
				private final IBinder mBinder;
				private TunerSessionCallbacks mCallback = null;
				
				public Client(IBinder binder,TunerSessionCallbacks callback) {
					mBinder 	= 	binder;
					mCallback	=	callback;
				}
				
				public TunerSessionCallbacks getCallback() {
					return mCallback;
				}

				@Override
				public void binderDied() {
					Log.d(LOG_TAG, "binderDied() binder=" + mBinder);
					synchronized(mListeners) {
						if(mListeners.containsKey(mBinder)) {
							mTunerManager.unregisterTunerSessionCallbacks(mCallback);
							mListeners.remove(mBinder);
						}
					}
				}
			}
			
			public void clearListeners() {
				synchronized(mListeners) {
					Iterator lIterator = mListeners.keySet().iterator();
					while(lIterator.hasNext()){
						IBinder binder = (IBinder)lIterator.next();
						mTunerManager.unregisterTunerSessionCallbacks(mListeners.get(binder).getCallback());
						binder.unlinkToDeath(mListeners.get(binder),0);
					}
					mListeners.clear();
				}
			}
			
			public void reRouteListeners(AbstractManager prevTunerManager) {
				synchronized(mListeners) {
					Iterator lIterator = mListeners.keySet().iterator();
					while(lIterator.hasNext()){
						IBinder binder = (IBinder)lIterator.next();
						prevTunerManager.unregisterTunerSessionCallbacks(mListeners.get(binder).getCallback());
						mTunerManager.registerTunerSessionCallbacks(mListeners.get(binder).getCallback());
					}
				}			
			}
		}
		
		public class TVCIControlStub extends TVCIControl.Stub{
			private Map<IBinder, Client> mListeners	= new HashMap<IBinder, Client>();
			
			public void enableMMI(boolean enable) {
				Log.v(LOG_TAG,"enableMMI called with enable = "+ enable);
				mTunerManager.enableMMI(enable);
			}
			
			public void updateMMIStatus(boolean status) {
				Log.v(LOG_TAG,"updateMMIStatus called with status = "+ status);
				mTunerManager.updateMMIStatus(status);
			}
			
			public void selectMMIItem(int menuType,int selectedItem) {
				Log.v(LOG_TAG,"selectMMIItem called with menuType ="+menuType + "selectedItem = "+selectedItem);
				mTunerManager.selectMMIItem(menuType,selectedItem);
			}
			
			public String[] getMMIItems(int menuType) {
				return mTunerManager.getMMIItems(menuType);
			}
			
			public int getLastSelectedMenuIndex() {
				return mTunerManager.getLastSelectedMenuIndex();
			}
			
			public void setEnquiryMMIResponse(String answer) {
				Log.v(LOG_TAG,"setEnquiryMMIResponse called : answer - "+answer);
				mTunerManager.setEnquiryMMIResponse(answer);
			}
			
			public CIMmiEnqImpl getEnquiryMMIInfo() {
				return (CIMmiEnqImpl)mTunerManager.getEnquiryMMIInfo();
			}
			
			public void cancelMMI(int menutype){
				Log.v(LOG_TAG,"cancelMMI called : menutype = "+menutype);
				mTunerManager.cancelMMI(menutype);
			}
		
			public void enableCamUpgrade(boolean enable){
				Log.v(LOG_TAG,"enableCamUpgrade called :  enable - "+enable);
				mTunerManager.enableCamUpgrade(enable);
			}
			
			public int getCAMUpgradeStatus() {
				return mTunerManager.getCAMUpgradeStatus();
			}
			
			public void updateCamInfo(CamInfoImpl caminfo) {
				Log.v(LOG_TAG,"updateCamInfo called");
				mTunerManager.updateCamInfo(caminfo);
			}
			
			public void enableCAMUI(boolean enable) {
				Log.v(LOG_TAG,"enableCAMUI called:enable-"+enable);
				mTunerManager.enableCAMUI(enable);
			}
			
			public CamInfoImpl getCamInfo(int slotId) {
				return (CamInfoImpl)mTunerManager.getCamInfo(slotId);
			}
			
			public void registerCIControlListener(IBinder binder){
				synchronized(mListeners) {
					if(!mListeners.containsKey(binder)) {
						try {
							TVCIControlCallback callback = TVCIControlCallback.Stub.asInterface(binder);
							Client mClient = new Client(binder,callback);
							binder.linkToDeath(mClient,0);
							mListeners.put(binder,mClient);
							mTunerManager.registerCIControlListener(callback);
						}catch (RemoteException e) {
							Log.d(LOG_TAG,"registerCIControlListener : RemoteException");
						}
					}
				}
			}
	
			public void unRegisterCIControlListener(IBinder binder){
				synchronized(mListeners) {
					if(mListeners.containsKey(binder)) {		
						mTunerManager.unRegisterCIControlListener(mListeners.get(binder).getCallback());
						binder.unlinkToDeath(mListeners.get(binder),0);
						mListeners.remove(binder);
					}
				}
			}
						
			private class Client implements IBinder.DeathRecipient {
				private final IBinder mBinder;
				private TVCIControlCallback mCallback = null;
				
				public Client(IBinder binder, TVCIControlCallback callback) {
					mBinder 	= 	binder;
					mCallback	=	callback;
				}

				public TVCIControlCallback getCallback() {
					return mCallback;
				}
				
				@Override
				public void binderDied() {
					Log.d(LOG_TAG, "binderDied() binder=" + mBinder);
					synchronized(mListeners) {
						if(mListeners.containsKey(mBinder)) {
							mTunerManager.unRegisterCIControlListener(mCallback);
							mListeners.remove(mBinder);
						}
					}
				}
			}
			
			public void clearListeners() {
				synchronized(mListeners) {
					Iterator lIterator = mListeners.keySet().iterator();
					while(lIterator.hasNext()){
						IBinder binder = (IBinder)lIterator.next();
						mTunerManager.unRegisterCIControlListener(mListeners.get(binder).getCallback());
						binder.unlinkToDeath(mListeners.get(binder),0);
					}
					mListeners.clear();
				}
			}
			
			public void reRouteListeners(AbstractManager prevTunerManager) {
				synchronized(mListeners) {
					Iterator lIterator = mListeners.keySet().iterator();
					while(lIterator.hasNext()){
						IBinder binder = (IBinder)lIterator.next();
						prevTunerManager.unRegisterCIControlListener(mListeners.get(binder).getCallback());
						mTunerManager.registerCIControlListener(mListeners.get(binder).getCallback());
					}
				}			
			}
		}
				
	}
	
	
}
