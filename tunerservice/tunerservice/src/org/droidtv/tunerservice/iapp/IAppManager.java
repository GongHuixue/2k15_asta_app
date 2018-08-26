package org.droidtv.tunerservice.iapp;

import org.droidtv.tunerservice.iapp.interfaces.IAppListener;
import org.droidtv.tunerservice.interfaces.IAppManagerTunerCallBacks;
import org.droidtv.tunerservice.interfaces.ITextureViewCallBackListener;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tunerservice.overlay.TunerServiceTextureView;
import android.content.Context;
import android.graphics.Matrix;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.SurfaceTexture;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Surface;
import android.view.TextureView;
import android.view.TextureView.SurfaceTextureListener;
import android.view.View;
import android.view.View.OnKeyListener;

public class IAppManager implements OnKeyListener,SurfaceTextureListener, ITextureViewCallBackListener, android.os.Handler.Callback{
	
	public static final int ID_MHEG 	= 0;
	public static final int ID_MHP 		= 1;
	public static final int ID_HBBTV 	= 2;

	public String TAG = null;
	
	Context mContext = null;
	static IAppManager iappmgr = null;
	private InteractiveApp iapp = null;
	
	Surface mSurface = null;
	private TextureView iappView = null; 
	private Handler mHandler = null ;	
	private static final int SET_MODE 		= 1;
	private static final int ADD_VIEW 		= 2;
	private static final int REMOVE_VIEW 	= 3;
	private static final int SETGFX_SIZE	= 4;
	private static final int REMOVE_SUBTITLE_VIEW	= 5;
	private static final int ADD_SUBTITLE_VIEW		= 6;
	private static final int ADD_BG_VIEW		=7;
	private static final int REMOVE_BG_VIEW		=8;
	
	private TunerServiceTextureView mSubtitleTextureView = null;
	private TunerServiceTextureView mBGTextureView = null;
	private OverlayManager mOverlayManager = null;
	private IAppManagerTunerCallBacks mIAppManagerTunerCallBacksListener = null;
	private String mAction = null;
	private IAppListener mMainIappMangerListener = null;
	private int mId;
	private boolean isInteractiveAppPaused = false;
	private boolean isEnabled = false;
		
	public IAppManager(int Id,Context mcontext,String action) {
		if(Id == ID_HBBTV){
			TAG = "IAppManager:HbbTv";
		}else{
			TAG = "IAppManager:Mheg";
		}	
		Log.d(TAG,"Init");
		this.mContext = mcontext;
		mId = Id;
		mHandler = new Handler(this);
		iapp = createInteractiveApp();
		mAction = action;
	}
	
	private InteractiveApp createInteractiveApp() {
		Log.d(TAG,"createInteractiveApp");
		InteractiveApp liapp = new InteractiveApp(mContext, this,mId);
		liapp.startLooperThread();
		if(mIAppManagerTunerCallBacksListener!=null) {
			liapp.setIAppManagerTunerCallBacksListener(mIAppManagerTunerCallBacksListener);
		}
		return liapp;
	}
	
	public void setMainIAppListener(IAppListener listener){
		Log.d(TAG,"setMainIAppListener");
		mMainIappMangerListener = listener;
	}
		
	public void setIAppManagerTunerCallBacksListener(IAppManagerTunerCallBacks listener) {
		Log.d(TAG,"[Hardy]setIAppManagerTunerCallBacksListener");
		mIAppManagerTunerCallBacksListener = listener;
		iapp.setIAppManagerTunerCallBacksListener(listener);
		connect(mId,mAction);
	}	

	public boolean onKeyDown(int keyCode) throws RemoteException {
		boolean retval = false;
		Log.d(TAG,"onKeyDown");
		return retval;
	}
	
	public boolean onKeyUp(int keyCode) {
		boolean retval = false;
		Log.d(TAG,"onKeyUp");
		return retval;
	}
	
	public boolean onKeyEvent(int keyCode, KeyEvent event) {
		boolean retval = false;
		Log.d(TAG,"onKeyEvent");
		if(iapp.isConnected()) {
			retval = iapp.onKeyEvent(keyCode, event);
		}
		return retval;
	}
	
	private void addView(boolean enable) {

		Log.d(TAG,"add/RemoveView " + enable +mId);
		if(enable) {		
			Log.d(TAG,"sendMessage ADD_VIEW"+mId);
			mHandler.sendMessage(Message.obtain(mHandler,ADD_VIEW));
		}
		else {
			Log.d(TAG,"sendMessage REMOVE_VIEW"+mId);
			mHandler.sendMessage(Message.obtain(mHandler,REMOVE_VIEW));
		}
	}
	
	
	private synchronized void sendStopStart(boolean ena) {
		Log.d(TAG,"sendStopStart" + ena);
		if(ena==true) {
			if(!iapp.isStarted()){
				Log.d(TAG,"calling start");
				//addView(true);
				if(mId==ID_MHEG) {
					mHandler.sendEmptyMessage(ADD_BG_VIEW);
				}
				iapp.start();
			}
			if(iappView!=null) {
				if(iappView.getTag().equals("")){
					Log.d(TAG,"Adding IAPP TAG not set");
					addView(true);
				}
			}else {
				addView(true);
			}
		}
		else {
			if(iapp.isStarted()){
				Log.d(TAG,"calling stop");
				addView(false);
				if(mId==ID_MHEG) {
					mHandler.sendEmptyMessage(REMOVE_BG_VIEW);
				}
				iapp.stop();
			}
		}
	}
	
	public void setInteractiveSurfaceView(Surface view) {
		Log.d(TAG,"setInteractiveSurfaceView " + view);
		iapp.setInteractiveSurfaceView(view);
	}
	
	public void setInteractiveVideoSurfaceView(Surface surface){
		Log.i(TAG,"setInteractiveVideoSurfaceView called : ");
		if(iapp.isConnected()) {
			iapp.setInteractiveVideoSurfaceView(surface);
		}
	}
	
	public void setInteractiveListener(){
		Log.i(TAG,"setInteractiveListener called : ");
		if(iapp.isConnected()) {
			iapp.setInteractiveListener();
		}
	}
		
	private void connect(int id, String action) {
		Log.d(TAG,"Connecting " + id);
		if(!iapp.isConnected()) {
			iapp.startConnection(id,action);
		}
	}
	
	private void disConnect(int id) {
		Log.d(TAG,"DisConnecting " + id);
		if(iapp.getID()==id) {
			iapp.release();
			iapp = null;
			iapp = createInteractiveApp();
		}
	}	

	@Override
	public void onSurfaceTextureAvailable(SurfaceTexture surfacetxt, int width,
			int height) {
		Log.d(TAG,"onSurfaceTextureAvailable width " + width + " height " + height);
		
		if(mSurface==null) {
			mSurface = new Surface(surfacetxt);
			setInteractiveSurfaceView(mSurface);
		}
	}

	@Override
	public boolean onSurfaceTextureDestroyed(SurfaceTexture surfacetxt) {
		Log.d(TAG,"onSurfaceTextureDestroyed");
		if(mSurface!=null)	{
			Log.d(TAG,"Releasing the surface");
			mSurface.release();
			Runnable r = new Runnable() {
				@Override
				public void run() {
					setInteractiveSurfaceView(null);
				}
			};
			mHandler.post(r);			
			//TODO : Check this part
			//sendStopStart(false);
			mSurface = null;
			iappView = null;
		}
		mSurface = null;
		return false;
	}

	@Override
	public void onSurfaceTextureSizeChanged(SurfaceTexture surfacetxt, int width,
			int height) {
		Log.d(TAG,"onSurfaceTextureSizeChanged width " + width + " height " + height);
	}

	@Override
	public void onSurfaceTextureUpdated(SurfaceTexture surfacetxt) {
		
	}
	
	public void removeViews() {
		Log.d(TAG,"removeViews called");
		if(iappView != null){
			addView(false);
		}
		//remove subtitle/background 
	}

	public void release() {
		Log.d(TAG,"release !!!!!");
		if(iappView != null){
			addView(false);
		}
		iapp.release();
	}


	private TextureView createTextureView() {		
		iappView = new TextureView(mContext);
		iappView.setTag("");
		iappView.setOpaque(false);
		iappView.setVisibility(TextureView.VISIBLE);
		iappView.setSurfaceTextureListener(this);
		return iappView;
	}

	public TextureView getInteractiveAppView() {
		if(iappView==null) {
			Log.e(TAG,"createTextureView" +mId);
			iappView=createTextureView();
		}
		return iappView;
	}

	public void onAppStarted() {
	    Log.e(TAG,"onAppStarted called sending notification");
		iapp.setAppState(true);
		if((mMainIappMangerListener != null)){
			mMainIappMangerListener.onAppStarted();
		}
	}
	
	public void onAppExited() {
	    Log.e(TAG,"onAppExited called");
	  	iapp.setAppState(false);
		if((mMainIappMangerListener != null)){
			if(!(isInteractiveAppPaused())){    //Sol For PR TF515PHIALLMTK01-3706
				mMainIappMangerListener.onAppExited();
			}
		}
    }
	
	public void requestSubtitleView() {
		Log.d(TAG,"creating subtitle surface for IAPP playback ->" +mId);
		mHandler.sendMessage(Message.obtain(mHandler,ADD_SUBTITLE_VIEW));		
	}

	public void enableIAppVideo(boolean ena) {
		Log.d(TAG,"enableIAppVideo called " + ena );
		if(ena) {
			Log.d(TAG,"enableIAppVideo called for IAPP playback");		
			mHandler.sendMessage(Message.obtain(mHandler,REMOVE_SUBTITLE_VIEW));
			requestSubtitleView();
		} else {
			iapp.setInteractiveVideoSurfaceView(null);
			iapp.setInteractiveSubtitleSurfaceView(null);
		}
		Log.d(TAG,"enableIAppVideo done");
	}
	
	@Override
	public void onSurfaceTextureAvailable(TunerServiceTextureView ptxtv) {
		if(mSubtitleTextureView==ptxtv) {
			Log.d(TAG,"IAPP Subtitle onSurfaceTextureAvailable arrived ");
			Surface subSurface = ptxtv.getSurface();		
			iapp.setInteractiveSubtitleSurfaceView(subSurface);
		} else if(mBGTextureView==ptxtv) {
			Log.d(TAG,"IAPP BG onSurfaceTextureAvailable arrived ");
			Surface subSurface = ptxtv.getSurface();		
			iapp.setInteractiveBGView(subSurface);
		}
	}

	@Override
	public boolean onSurfaceTextureDestroyed(TunerServiceTextureView ptxtv) {
		if(mSubtitleTextureView==ptxtv) {
			Log.d(TAG,"IAPP Subtitle onSurfaceTextureDestroyed arrived ");
			mSubtitleTextureView = null;
			iapp.setInteractiveSubtitleSurfaceView(null);
		}else if(mBGTextureView==ptxtv) {
			Log.d(TAG,"IAPP BG onSurfaceTextureDestroyed arrived ");
			mBGTextureView = null;
			iapp.setInteractiveBGView(null);
		}
		else{
			Log.d(TAG,"onSurfaceTextureDestroyed arrived for unknown ptxtv");			
		}
		ptxtv.release();
		ptxtv = null;
		return false;
	}
	
	public void setInteractiveSubtitleSize(int width, int height) {
		Log.d(TAG,"setInteractiveSubtitleSize arrived");
		Message msg = mHandler.obtainMessage(SET_MODE,width,height);
		mHandler.sendMessage(msg);
	}
	
	public boolean getIappStatus() {
		return iapp.isConnected();
	}		
	
	@Override
	public boolean handleMessage(Message msg) {

		Log.d(TAG,"HANDLE MESSAGE = "+ msg.what);	
		switch(msg.what){

		case REMOVE_VIEW:
			Log.d(TAG,"REMOVE_VIEW"+mId);
			if(iappView != null){
				if(mOverlayManager!=null){
					mOverlayManager.removeIAPPView();
				}else{
					Log.d(TAG,"Not able to REMOVE_VIEW mOverlayManager is null!!!!");
				}
				iappView=null;
			}
			break;
		
		case ADD_VIEW:
			Log.d(TAG,"ADD_VIEW "+mId);
			if(mOverlayManager!=null){
				getInteractiveAppView();
				iappView.setOnKeyListener(this);
				mOverlayManager.addIAPPView(iappView);
			}else{
				Log.d(TAG,"Not able to ADD_VIEW mOverlayManager is null!!!!");
			}
			break;
			
		case ADD_SUBTITLE_VIEW:
			if(mOverlayManager!=null) {
				mSubtitleTextureView = new TunerServiceTextureView(mContext,
					TunerServiceTextureView.TXTVIEWTYPE_SUBTTILE, 
					TunerServiceTextureView.SUBVIEWTYPE_SUBTTILE_DVB,
					TunerServiceTextureView.EXSUBTTILE_EXTMPLAYER,this);
				mOverlayManager.addSubtitleView(mSubtitleTextureView);
				Log.d(TAG,"creating subtitle view for IAPP playback done");
			}
			break;
		
		case REMOVE_SUBTITLE_VIEW:
			if(mOverlayManager!=null){
				mOverlayManager.removeSubtitleView();
			}
			break;
			
		case SET_MODE:
			Log.d(TAG,"handlerMessage -> size" + msg.arg1);
			try {
				mSubtitleTextureView.setLayoutTransformParams(msg.arg1, msg.arg2);
			}catch(Exception e) {
				Log.d(TAG,"Exception in calling setMode");
			}
			break;
			
		case SETGFX_SIZE:
			Log.d(TAG,"handlerMessage -> SETGFX_SIZE " + msg.arg1 + "x" + msg.arg2);
			if(iappView!=null) {
				int SurfaceWidth  = iappView.getWidth();
				int SurfaceHeight = iappView.getHeight();
				Log.d(TAG,"iappView " + iappView.getWidth() + "x" + iappView.getHeight());
				try {
					float xScale = ((float)(SurfaceWidth)/(float)(msg.arg1));
					float yScale = ((float)(SurfaceHeight)/(float)(msg.arg2));
				
					Log.d(TAG,"Transform " + xScale + " x " + yScale);
					
					Matrix mtx = iappView.getTransform(null);
					mtx.setScale (xScale,yScale);
					iappView.setTransform(mtx);
					Log.d(TAG,"Transform call done");
				}catch(Exception e) {
					Log.d(TAG, "SETGFX_SIZE - exception :"+e.toString());
				}
			}
			break;
		case ADD_BG_VIEW:
			if(mOverlayManager!=null) {
				mBGTextureView = new TunerServiceTextureView(mContext,
					TunerServiceTextureView.TXTVIEWTYPE_IAPP_BG,0,0,this);
				mOverlayManager.addIAPPBGView(mBGTextureView);
				Log.d(TAG,"ADD_BG_VIEW: creating bg view for IAPP done");
			}
			break;
		case REMOVE_BG_VIEW:
			Log.d(TAG,"REMOVE_BG_VIEW");
			if(mOverlayManager!=null){
				Log.d(TAG,"REMOVE_BG_VIEW: removing BG View");
				mOverlayManager.removeIAPPBGView();
                iapp.setInteractiveBGView(null);
			}
			break;	
		}
		return false;
	}

	public void setOverlayManager(final OverlayManager overlaymgr) {
		boolean value = (overlaymgr!=null);
		Log.d(TAG,"setOverlayManager " + value);		
		mOverlayManager = overlaymgr;
		if(iappView!=null){
			iappView=null;
		}
	}
	
	public boolean onKey(View v, int keyCode, KeyEvent event) {
		if(iappView == v) {
			return onKeyEvent(keyCode,event);
		}
		return false;
	}
		
   /*
	*  IAppManager will be asked to start and stop the interactiveapp from MainIAppManager
	*/
	public void start(){
		Log.d(TAG,"Start");
		synchronized (this) {
			if(isInteractiveAppPaused) {
				setInteractiveAppPauseState(false);
			}
		}
		sendStopStart(true);
	}
		
	public void stop(){
		Log.d(TAG,"Stop");	
		sendStopStart(false);
	}	

	public void startApp(String appRef){
		Log.d(TAG,"Start");	
		iapp.startApp(appRef);
		addView(true);
	}
	
	public void invokeInteractiveApp(String url){
		Log.d(TAG,"InvokeInteractiveApp in IAppMAnager");
		if((mMainIappMangerListener != null)){
			mMainIappMangerListener.invokeInteractiveApp(url);
		}
	}
	
	public void onSetSize(int width, int height) {
		Log.d(TAG,"onSetSize called " + width + "x" + height);
		Message msg = mHandler.obtainMessage(SETGFX_SIZE, width, height);
		mHandler.sendMessage(msg);
	}
		
	public void relayoutToDestinationRectangle(final Rect rect) {
		Log.d(TAG,"relayoutToDestinationRectangle called " + rect.toString());
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(iappView!=null) {
					int SurfaceWidth  = iappView.getWidth();
					int SurfaceHeight = iappView.getHeight();
					RectF src = new RectF(0,0,SurfaceWidth,SurfaceHeight);
					RectF dst = new RectF(rect.left,rect.top,rect.right,rect.bottom);
					try {
						Matrix mtx = new Matrix();
						mtx.reset();						
						mtx.setRectToRect(src,dst,Matrix.ScaleToFit.FILL);
						iappView.setTransform(mtx);
						iappView.invalidate();
						Log.d(TAG,"Transform call done");
					}catch(Exception e){
						Log.d(TAG,"Exception caught" + e.getLocalizedMessage());
					}
				}
			}
		};
		mHandler.post(r);
	}
		
	public boolean onSessionRelease(){
		Log.d(TAG,"onSessionRelease......");
		boolean lRet = false;
		setInteractiveAppPauseState(true);
		if(iapp.isStarted()) {
			sendStopStart(false);
			lRet = true;
		}else{
			Log.d(TAG,"InteractiveApp Not started");
		}
		//Call Stop when the session gets released		
		iapp.stop();
		return lRet;
	}
	
	private synchronized boolean isInteractiveAppPaused(){
		return isInteractiveAppPaused;
	}
	
	private synchronized void setInteractiveAppPauseState(boolean state){
		isInteractiveAppPaused = state;
	}

	public void setAVSurface(Surface surface) {
		iapp.setInteractiveVideoSurfaceView(surface);
	}

	public boolean isEnabled() {
		return isEnabled;
	}

	public void setEnabled(boolean isEnabled) {
		this.isEnabled = isEnabled;
	}

	public void requestBackgroundSurface() {
		//Log.d(TAG,"requestBackgroundSurface called ");
		//mHandler.sendEmptyMessage(ADD_BG_VIEW);
	}	
	
	public boolean isStarted(){		
		boolean lRet = false;
		if(iapp.isStarted() || iapp.isStartRequested()){
			lRet = true;
		}
		return lRet;
	}	
}
