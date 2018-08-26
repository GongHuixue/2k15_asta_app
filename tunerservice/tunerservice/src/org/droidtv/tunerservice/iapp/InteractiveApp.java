package org.droidtv.tunerservice.iapp;

import java.util.ArrayList;
import java.util.List;

import org.droidtv.tunerservice.interfaces.IAppManagerTunerCallBacks;
import org.droidtv.tv.tvinput.IInteractiveService;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Surface;
import android.content.pm.ResolveInfo;
import android.content.pm.PackageManager; 
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.os.RemoteException;

public class InteractiveApp implements ServiceConnection, IBinder.DeathRecipient {
	
	Context mContext;
	boolean mActive = false;
	boolean mConnected = false;
	int mID=-1;
	String mAction = null;
	String TAG= null;
	
	IServiceListener mIServiceListener = null;
	IInteractiveService iappBinder = null;
	Surface mIAppSurface = null;
	boolean started = false;
	private HandlerThread mIAppHandlerThread = null; 
	private Handler mIAppHandler = null;
	private Looper mLooper;
	private static final int ONSERVICE_CONNECTED = 100; 
	private static final int START_INTERACTIVEAPP = 101;
	private static final int SET_INTERACTIVELISTENER = 102;
	private boolean isSurfaceSet = false;
	private boolean isStartRequested = false;
	private Surface playbackSubtitleSurface = null;
	private Surface playbackVideoSurface = null;
	
	
	public InteractiveApp(Context context,IAppManager iappManager, int id) {
		mID = id;
		if(mID == 0){
			TAG = "InteractiveApp:MHEG";
		}else{
			TAG = "InteractiveApp:HBBTV";
		}
		mContext = context;
		mIServiceListener = new IServiceListener(iappManager);
	}
	
	public void startLooperThread(){
		mIAppHandlerThread = new HandlerThread("IAppHandlerTThread");
		mIAppHandlerThread.start();
		mLooper = mIAppHandlerThread.getLooper();
		mIAppHandler = new InteractiveAppHandler(mLooper);	
	}
	public int getID() {
		return mID;
	}
	
	public void startConnection(int id, String action) {
		startConnectionLocal(id, action, false);
	}
	
	private void startConnectionLocal(int id, String action, boolean retry) {
		Log.d(TAG,"StartConnection ");
		mID = id;
		mAction = action;
		PackageManager pm = mContext.getApplicationContext().getPackageManager();
		Intent launcherIntent = new Intent(action);
		ResolveInfo ri = pm.resolveService(launcherIntent, 0);
		if(ri!=null){
			launcherIntent.setClassName(ri.serviceInfo.packageName,ri.serviceInfo.name);
			if(retry){
				launcherIntent.putExtra("CrashRecovery", true);
			}
			mContext.getApplicationContext().bindService(launcherIntent,this,Context.BIND_AUTO_CREATE);
		}
	}

	public boolean isConnected() {
		Log.d(TAG,"isConnected() " +mConnected);
		return mConnected;
	}
		
	@Override
	public void onServiceConnected(ComponentName name, IBinder service) {
		Log.d(TAG,"onServiceConnected ");
		iappBinder = IInteractiveService.Instance.asInterface(service);
		mConnected = true;
		try {
			service.linkToDeath(this, 0);
		} catch (RemoteException e) {
			Log.d(TAG, "onServiceConnected - RemoteException");
		}
		if(iappBinder != null) {
			Message msg = mIAppHandler.obtainMessage();
			msg.what = ONSERVICE_CONNECTED;
			mIAppHandler.sendMessage(msg);		
		}
	}

	@Override
	public void onServiceDisconnected(ComponentName name) {
		mConnected = false;
	}
	
	@Override
	public void binderDied() {
		Log.d(TAG, mAction + " has died. Re-connecting...");
		
		mIServiceListener.releaseMediaPlaybackSurfaces();
		setAppState(false);
		startConnectionLocal(mID, mAction, true);
	}
		
	public boolean onKeyEvent(int keyCode, KeyEvent keyevent){
		boolean retVal = false;
		if(iappBinder!=null){
			retVal = iappBinder.onKeyEvent(keyevent);
		}
		Log.d(TAG,"onKeyEvent retVal"+retVal);
		return retVal;
	}

	public void setInteractiveSubtitleSurfaceView(Surface surface) {
		playbackSubtitleSurface = surface;
		if(iappBinder!=null) {
			if((playbackSubtitleSurface!=null)&&(playbackVideoSurface!=null)){
				List <Surface> surfacelist = null;
				surfacelist = new ArrayList <Surface>(2);
				surfacelist.add(playbackVideoSurface);
				surfacelist.add(playbackSubtitleSurface);
				iappBinder.setMediaPlaybackSurfaces(surfacelist);
			}
		}		
	}

	public void setInteractiveSurfaceView(Surface surface) {
		Log.i(TAG,"setInteractiveSurfaceView called");
		mIAppSurface = surface;
		if(iappBinder!=null){
			iappBinder.setSurface(mIAppSurface);
			isSurfaceSet = true;
			Message msg = mIAppHandler.obtainMessage();
			msg.what = START_INTERACTIVEAPP;
			mIAppHandler.sendMessage(msg);		
		}
	}

	public void setInteractiveVideoSurfaceView(Surface surface){
		playbackVideoSurface = surface;
		if((playbackSubtitleSurface!=null)&&(playbackVideoSurface!=null)){
			List <Surface> surfacelist = null;
			surfacelist = new ArrayList <Surface>(2);
			surfacelist.add(playbackVideoSurface);
			surfacelist.add(playbackSubtitleSurface);
			iappBinder.setMediaPlaybackSurfaces(surfacelist);
		}
	}

	public void start() {
		Log.i(TAG,"start called");
		isStartRequested = true;
		Message msg = mIAppHandler.obtainMessage();
		msg.what = START_INTERACTIVEAPP;
		mIAppHandler.sendMessage(msg);
	}

	public void stop() {
		Log.i(TAG,"stop called");
		isStartRequested = false;
		setAppState(false);
		if(iappBinder!=null){
			iappBinder.stop();
		}
	}

	public void release() {
		Log.i(TAG,"release called");
		if(iappBinder!=null) {
			Log.i(TAG,"setSurfaceNull called");
			iappBinder.setSurface(null);
		}
		if(mConnected) {
			Log.i(TAG,"UnbindingService.....");
			mContext.getApplicationContext().unbindService(this);
		}
	}
	
	public boolean isStarted(){
		return started;
	}

	public void setIAppManagerTunerCallBacksListener(IAppManagerTunerCallBacks listener) {
		mIServiceListener.setIAppManagerTunerCallBacksListener(listener);
	}

	public void setInteractiveListener() {
		if(iappBinder!=null){
			Message msg = mIAppHandler.obtainMessage();
			msg.what = SET_INTERACTIVELISTENER;
			mIAppHandler.sendMessage(msg);		
		}
	}
	
	public void startApp(String url){
		Log.i(TAG,"startApp called");
		setAppState(true);
		if(iappBinder!=null){
			iappBinder.startApp(url);
		}
	}
	
	public void setAppState(boolean val){
		Log.i(TAG,"setAppState called "+val);
		started = val;	
	}
	
	private class InteractiveAppHandler extends Handler{
		
		  private InteractiveAppHandler (Looper looper) {
			  super (looper);
		  }		
		  public void handleMessage(Message msg) {
			  switch(msg.what){
			  	case ONSERVICE_CONNECTED:
					Log.i(TAG,"Handler :ONSERVICE_CONNECTED");
					iappBinder.setInteractiveServiceCallbackListener(mIServiceListener);
					if(mIAppSurface != null){
						setInteractiveSurfaceView(mIAppSurface);
					}
					Log.d(TAG,"isStartRequested"+isStartRequested+"started="+started+"mIAppSurface="+mIAppSurface+" iappBinder"+iappBinder);
					if(isStartRequested && (!isStarted()) && (mIAppSurface != null) && ( iappBinder != null )){	
						Log.i(TAG,"Starting the app");
						setAppState(true);
						iappBinder.start();						
					}
				break;
				case START_INTERACTIVEAPP:
					Log.d(TAG,"isStartRequested"+isStartRequested+"started="+started+"mIAppSurface="+mIAppSurface+" iappBinder"+iappBinder);
					if(isStartRequested && (!isStarted()) && (mIAppSurface != null) && ( iappBinder != null )){	
						Log.i(TAG,"Starting the app");
						setAppState(true);
						iappBinder.start();						
					}
				break;	
				case SET_INTERACTIVELISTENER:
					Log.d(TAG,"SET_INTERACTIVELISTENER");
					iappBinder.setInteractiveServiceCallbackListener(mIServiceListener);
				break;	
			  	default:
				
				break;
			  
			  }
		  }
	}

	public void setInteractiveBGView(Surface bgSurface) {
		iappBinder.setVideoBackgroundSurface(bgSurface);
	}	
	public boolean isStartRequested(){
		return isStartRequested;
	}
			
	
}
