package org.droidtv.tunerservice.playback;

import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tv.media.ITvMediaRecordControl.PlaybackEitInfo;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import android.net.Uri;
import java.util.Map;

import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;

public abstract class TvAbstractPlayback {
	private static final String TAG = "TvAbstractPlayback";
	public abstract void setPlayer(PlayTVFacMediaPlayer mpl);
	public abstract void play(Uri uri,Medium medium, Map<String,String> headers);
	public abstract void stop();
	public abstract void release();
	public abstract void registerListener(ITvAbstractPlaybackListener listener);
	public abstract void unRegisterListener(ITvAbstractPlaybackListener listener);
	
	public void playCatchUpChannel(Uri uri,Medium medium, Map<String,String> headers) {
		
	}

	public void playOlympicChannel(Uri uri,Medium medium, Map<String,String> headers) {
		
	}
	
	public void play(Uri CurrentUri,Map<String,String> headers) {
		
	}
	
	public void play(Uri uri){
	}
	public boolean pause() {
		return false;
	}
	public void resume() {
		
	}
	public void seekTo(int msecs) {
		
	}
	public void setSpeed(int speed, boolean forward) {
		
	}
	public int  getCurrentDuration() {
		return 0;
	}
	public int  getTotalDuration() {
		return 0;
	}
	public boolean isPlaying() {
		return false;
	}
	public void enableTrickModes(boolean status) {
		
	}
	
	public abstract Medium getMedium();
	public abstract int getServiceType();
	
	public boolean isTimeshiftActive() {
		return false;
	}
		
	public int getPlaybackState() {
		return 0;
	}
	
	public int getCurrentTimeShiftStatus() {
		return 1; //TimeshiftRecordingobject.IN_TRANSIENT 
	}
	
	public long getRecordedDuration() {
		return 0;
	}
	
	public PlaybackEitInfo getTimeshiftInfo() {
		return null;
	}
	
	public boolean getTrickmodeStatus() {
		return true;
	}
}
