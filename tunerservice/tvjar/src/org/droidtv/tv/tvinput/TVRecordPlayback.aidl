package org.droidtv.tv.tvinput;

import android.os.IBinder;
import android.net.Uri;

interface TVRecordPlayback{

	void pause();

	void stop();
	
	void resume();
	
	void seekTo(int msecs);
	
	void setSpeed(int speed, boolean forward);
	
	int getCurrentDuration();
	
	int getTotalDuration();
	
	int getBufferedDuration();
	
	int getPlaybackState();
	
	void enableTrickModes(boolean enable);
	
	boolean getTrickModeStatus();

	void registerRecordCallback(IBinder callback);
	
	void unregisterRecordCallbacks(IBinder callback);
}