package org.droidtv.tunerservice.iapp;

import org.droidtv.tunerservice.interfaces.IAppManagerTunerCallBacks;
import org.droidtv.tv.tvinput.IInteractiveService.IInteractiveServiceCallBack;

import android.graphics.Rect;
import android.util.Log;

public class IServiceListener extends IInteractiveServiceCallBack{
	
	private static final String TAG = "IServiceListener";
	private IAppManager mIAppManager = null;
	private IAppManagerTunerCallBacks mTunerCallBackListener = null;
	private static final int SUBTITLE_SURFACE_INDEX = 1;
		
	public IServiceListener(IAppManager iappmanager) {
		mIAppManager = iappmanager;
	}
	
	@Override
	public void requestVideoBackgroundSurface() {
		mIAppManager.requestBackgroundSurface();
	}

	@Override
	public void relayoutMediaPlaybackSurface(int surfaceindex, int width,
			int height) {
		Log.d(TAG,"relayoutMediaPlaybackSurface called ");
		if(surfaceindex==SUBTITLE_SURFACE_INDEX) {
			mIAppManager.setInteractiveSubtitleSize(width,height);
		}
	}

	@Override
	public void relayoutSurface(int width, int height) {
		Log.e(TAG,"relayoutSurface called");
		mIAppManager.onSetSize(width,height);
	}

	@Override
	public void relayoutVideoBackgroundSurface(int width, int height) {
		// TODO Auto-generated method stub
	}

	@Override
	public void requestMediaPlaybackSurfaces(int video_manager_cacheid) {
		if(mTunerCallBackListener!=null) {
			mIAppManager.enableIAppVideo(true);
			mTunerCallBackListener.enableBroadcastAV(false);
		}
	}

	@Override
	public void releaseMediaPlaybackSurfaces() {
		if(mTunerCallBackListener!=null) {
			mIAppManager.enableIAppVideo(false);
			mTunerCallBackListener.enableBroadcastAV(true);
		}
	}

	@Override
	public void releaseVideoBackgroundSurface() {
		// TODO Auto-generated method stub
	}

	@Override
	public void onAppExited() {
	    Log.e(TAG,"onAppExited called");
	    mIAppManager.onAppExited();
	}

	@Override
	public void onAppStarted() {
	    Log.e(TAG,"onAppStarted called");
	    mIAppManager.onAppStarted();
	}
		
	@Override
	public void setVideoPosition(int x, int y, int width, int height) {
		Log.v(TAG,"setVideoPosition called x=" + x + " y =" + y + " width=" + width + " height=" + height);
		if(mTunerCallBackListener!=null) {
			mTunerCallBackListener.setVideoPosition(x, y, width, height);
		}
	}
		
	public void setIAppManagerTunerCallBacksListener(IAppManagerTunerCallBacks listener) {
		mTunerCallBackListener = listener;
	}
	
	public void invokeInteractiveApp(String url){
		Log.e(TAG,"invokeInteractiveApp called" +url);
		mIAppManager.invokeInteractiveApp(url);
	}
	
	public void relayoutToDestinationRectangle(Rect r) {
		mIAppManager.relayoutToDestinationRectangle(r);
	}
}
