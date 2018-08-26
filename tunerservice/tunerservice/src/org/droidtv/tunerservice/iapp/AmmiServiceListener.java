package org.droidtv.tunerservice.iapp;

import org.droidtv.tv.tvinput.IInteractiveService.IInteractiveServiceCallBack;
import android.util.Log;
import android.view.Surface;
import org.droidtv.tunerservice.overlay.AmmiSurfaceView;
import org.droidtv.tunerservice.tvmpl.PlayTvCIPlusHandler;
import org.droidtv.tunerservice.interfaces.IAppManagerTunerCallBacks;
import org.droidtv.tunerservice.tvmanager.MainTVManager;

public class AmmiServiceListener extends IInteractiveServiceCallBack{
	
	private static final String TAG = AmmiServiceListener.class.getSimpleName();
	
	private PlayTvCIPlusHandler mPlayTvCIPlusHandler = null;
	
	
	public AmmiServiceListener(PlayTvCIPlusHandler playTvCIPlusHandler) {
		mPlayTvCIPlusHandler = playTvCIPlusHandler;
	}
	
	@Override
	public void requestVideoBackgroundSurface() {
	}

	@Override
	public void relayoutMediaPlaybackSurface(int surfaceindex, int width,
			int height) {
	}

	@Override
	public void relayoutSurface(int width, int height) {
	}

	@Override
	public void relayoutVideoBackgroundSurface(int width, int height) {
	}

	@Override
	public void requestMediaPlaybackSurfaces(int video_manager_cacheid) {
	}

	@Override
	public void releaseMediaPlaybackSurfaces() {
	}

	@Override
	public void releaseVideoBackgroundSurface() {
	}

	@Override
	public void onAppExited() {
	    Log.e(TAG,"onAppExited called");
	    mPlayTvCIPlusHandler.onAppExited();
	}

	@Override
	public void onAppStarted() {
	    Log.e(TAG,"onAppStarted called");
	    mPlayTvCIPlusHandler.onAppStarted();
	}
		
	@Override
	public void setVideoPosition(int x, int y, int width, int height) {
		Log.v(TAG,"setVideoPosition called x=" + x + " y =" + y + " width=" + width + " height=" + height);
		IAppManagerTunerCallBacks iAppMgrIntf = MainTVManager.getIAppManagerTunerCallbackInstance();
		if(iAppMgrIntf != null) {
			iAppMgrIntf.setVideoPosition(x, y, width, height);
		}
	}
	
	//@Override
	public void enableAV(boolean ena) {
	}
	
	//@Override
	public Surface getSubtitleSurface() {
		return null;
	}
	
	//mIAppManager.setInteractiveSubtitleMode(mode);
	
	
}
