package org.droidtv.tunerservice.overlay;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.util.Log;
import android.view.TextureView;
import android.view.View.OnKeyListener;
import android.view.KeyEvent;
import android.view.View;
import android.view.Surface;
import android.os.Handler;
import org.droidtv.tv.tvinput.IInteractiveService;
import org.droidtv.tunerservice.tvmpl.PlayTvCIPlusHandler;

public class AmmiSurfaceView implements TextureView.SurfaceTextureListener{

	private TextureView mTextureView;
	private boolean mSurfaceAvailable = false;
	public  TextureView.SurfaceTextureListener cModule;
	private SurfaceTexture mSurfaceTexture;
	private IInteractiveService mInteractiveService;
	private String TAG = AmmiSurfaceView.class.getSimpleName();
	private int mwidth, mheight;
	private Surface mSurface;
	private Handler mHandler = null;
	private PlayTvCIPlusHandler mPlayTvCIPlusHandler;
	public AmmiSurfaceView(Context context,IInteractiveService interactiveService,PlayTvCIPlusHandler playTvCIPlusHandler){
		Log.i(TAG,"AmmiSurfaceView called:"+context);
		mInteractiveService = interactiveService;
		mPlayTvCIPlusHandler = playTvCIPlusHandler;
		mHandler	 = new Handler();
		mTextureView = new TextureView(context);
		mTextureView.setSurfaceTextureListener(this);
		mTextureView.setOpaque(false);
	}

	
	public void setTextureViewVisibility(boolean visibility)
	{
		Log.i(TAG,"EnableSurface called:"+visibility);
		if(visibility){
			mTextureView.setVisibility(TextureView.VISIBLE);
		} else {
			mTextureView.setVisibility(TextureView.INVISIBLE);
		}
	}
	public TextureView getTextureView(){
		return mTextureView;
	}
	
	public boolean isSurfaceTextureAvailable()
	{
		return mSurfaceAvailable;
	}
	
	public SurfaceTexture getSurfaceTexture()
	{
		return mSurfaceTexture;
	}
	
	@Override
	public void onSurfaceTextureAvailable(SurfaceTexture surfacetexture, int width,int height){
		Log.d(TAG ,"onSurfaceTextureAvailable:");
		mSurfaceAvailable = true;
		mwidth = width;
		mheight = height;
		mSurfaceTexture = surfacetexture;
		if (mSurface == null && mInteractiveService != null) {
			mSurface = new Surface(surfacetexture);
			mInteractiveService.setSurface(mSurface);
		}else {
			Log.i(TAG,"onSurfaceTextureAvailable mSurface is null:"+mSurface);
		}
	}

	@Override
	public boolean onSurfaceTextureDestroyed(SurfaceTexture surfacetexture) {
		Log.d(TAG,"onSurfaceTextureDestroyed ");
		mSurfaceAvailable = false;
		if(mSurface!=null && mInteractiveService != null){			
			mSurface.release();
			mSurface = null;
			mPlayTvCIPlusHandler.resetAmmiSurfaceView();
			Runnable r = new Runnable() {
				@Override
				public void run() {
					mInteractiveService.setSurface(null);
				}
			};
			mHandler.post(r);
		}else {
			Log.i(TAG,"onSurfaceTextureDestroyed mSurface is null:"+mSurface);
		}
		return false;
	}
	
	@Override
	public void onSurfaceTextureSizeChanged(SurfaceTexture surfacetexture, int width,int height) {
		mwidth = width;
		mheight = height;
		Log.d(TAG,"onSurfaceTextureSizeChanged called:mwidth->"+mwidth+"mheight:"+mheight);
	}

	@Override
	public void onSurfaceTextureUpdated(SurfaceTexture surfacetexture) {
		Log.d(TAG,"onSurfaceTextureUpdated called:"+surfacetexture.toString());
	}
	
}
