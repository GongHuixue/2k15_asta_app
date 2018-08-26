package org.droidtv.tunerservice.interfaces;


import org.droidtv.tunerservice.overlay.TunerServiceTextureView;

public interface ITextureViewCallBackListener {
	
	public void onSurfaceTextureAvailable(TunerServiceTextureView ptxtv);
	
	public boolean onSurfaceTextureDestroyed(TunerServiceTextureView ptxtv);
}
