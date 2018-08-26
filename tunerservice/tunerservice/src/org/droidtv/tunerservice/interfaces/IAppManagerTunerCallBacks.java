package org.droidtv.tunerservice.interfaces;

public interface IAppManagerTunerCallBacks {
	
	public abstract void setVideoPosition(int x, int y, int width, int height);
	public abstract void enableBroadcastAV(boolean ena);	
}
