package org.droidtv.tunerservice.overlay;


import org.droidtv.tunerservice.interfaces.ITextureViewCallBackListener;

import android.content.Context;
import android.graphics.Matrix;
import android.graphics.SurfaceTexture;
import android.util.Log;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;

public class TunerServiceTextureView extends TextureView implements TextureView.SurfaceTextureListener{
	
	public static final int TXTVIEWTYPE_INVALID 		= -1;
	public static final int TXTVIEWTYPE_SUBTTILE 		= 0;
	public static final int TXTVIEWTYPE_IAPP 			= 1;
	public static final int TXTVIEWTYPE_IAPP_BG 		= 2;
	
	public static final int SUBVIEWTYPE_INVALID 		= -1;
	public static final int SUBVIEWTYPE_SUBTTILE_DVB 	= 0;
	public static final int SUBVIEWTYPE_SUBTTILE_TXT 	= 1;
	public static final int SUBVIEWTYPE_SUBTTILE_DEF	= 2;

	public static final int EXSUBTTILE_LIVE				= 0;
    public static final int EXSUBTTILE_TIMESHIFTED		= 1;
    public static final int EXSUBTTILE_EXTMPLAYER		= 2;
    public static final int EXSUBTTILE_OLYMPICS 		= 3;
    
	public static final int SUBVIEWTYPE_IAPP_MHEG 		= 0;
	public static final int SUBVIEWTYPE_IAPP_MHP 		= 1;
	public static final int SUBVIEWTYPE_IAPP_HBBTV 		= 2;
	
	private static final String TAG = "TunerServiceTextureView";	
		
	int mtype = TXTVIEWTYPE_SUBTTILE;
	int msubtype = SUBVIEWTYPE_INVALID;
	int mexsubtype = EXSUBTTILE_LIVE;
	
	private ITextureViewCallBackListener mlistener=null;
	private Surface mSurface = null;
	
	private boolean inUse = false;
	private boolean isAvailable = false;
	
	public Surface getSurface() {
		return mSurface;
	}

	public int getType() {
		return mtype;
	}

	public void setType(int type) {
		mtype = type;
	}
	
	public int getSubtype() {
		return msubtype;
	}

	public void setSubtype(int subtype) {
		msubtype = subtype;
	}

	public TunerServiceTextureView(Context context, int type, int subtype,
			int extype,ITextureViewCallBackListener listener) {
		super(context);
		mtype = type;
		msubtype = subtype;
		mexsubtype = extype;
		mlistener = listener;
		this.setOpaque(false);
		this.setVisibility(View.VISIBLE);
		this.setSurfaceTextureListener(this);
	}

	@Override
	public void onSurfaceTextureAvailable(SurfaceTexture surfacetxt, int width,
			int height) {
		Log.d(TAG,"onSurfaceTextureAvailable " + msubtype);
		mSurface = new Surface(surfacetxt);
		this.isAvailable = true;
		if(mlistener!=null) {
			mlistener.onSurfaceTextureAvailable(this);
		}
		
	}

	@Override
	public boolean onSurfaceTextureDestroyed(SurfaceTexture surfacetxt) {
		Log.d(TAG,"onSurfaceTextureDestroyed " + msubtype);
		this.isAvailable = false;
		if(mlistener!=null) {
			mlistener.onSurfaceTextureDestroyed(this);
		}
		return false;
	}

	@Override
	public void onSurfaceTextureSizeChanged(SurfaceTexture surfacetxt, int width,
			int height) {
		Log.d(TAG,"onSurfaceTextureSizeChanged " + msubtype);
	}

	@Override
	public void onSurfaceTextureUpdated(SurfaceTexture surfacetxt) {
		Log.d(TAG,"onSurfaceTextureUpdated " + msubtype);
	}

	public void release() {
		Log.d(TAG,"release " + msubtype);
		if(mSurface!=null) {
			mSurface.release();
			mSurface=null;
		}
	}

	public boolean isInUse() {
		return inUse;
	}

	public void setInUse(boolean inUse) {
		this.inUse = inUse;
		if(inUse) {
			this.setVisibility(View.VISIBLE);
		} else {
			this.setVisibility(View.INVISIBLE);
		}
	}

	public boolean isAvailable() {
		return isAvailable;
	}
	
	public boolean equals(int type,int extype) {
		if((this.msubtype == type) && (this.mexsubtype == extype)) {
			return true;
		}
		else {
			return false;
		}	
	}
	
	public void setLayoutTransformParams(int width, int height){
		Log.d(TAG,"setLayoutParams " + width + "x" + height);
		float scaleX = 1.0f;
		float scaleY = 1.0f;
		int surfaceWidth  = this.getWidth();
		int surfaceHeight = this.getHeight();
		scaleX = (float)((surfaceWidth)/(float)width);
		scaleY = (float)((surfaceHeight)/(float)height);
		Log.d(TAG,"scaleX " + scaleX);
		Log.d(TAG,"scaleY " + scaleY);
		try {
			Matrix mtx = this.getTransform(null);
			mtx.setScale (scaleX, scaleY);
			this.setTransform (mtx);
			Log.d(TAG,"setscale done");
		} catch(Exception e) {
			Log.d(TAG,"Exception changing mode " + e.getLocalizedMessage());
		}
		Log.d(TAG,"setLayoutParams done ");
	}
}
