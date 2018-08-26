package org.droidtv.tv.tvinput;

import android.os.IBinder;
import android.os.Parcelable;
import java.lang.String;
import android.net.Uri;
import java.util.List;
import android.net.Uri;
import org.droidtv.tv.tvinput.MultiFeedServiceInfoImpl;
import org.droidtv.tv.tvinput.TimeshiftInfoImpl;

interface TVTunerSession
{		
	Uri getSelectedURI();
	Uri getNextURI(in Uri uri);
	Uri getPreviousURI(in Uri uri);
	boolean getLockStatus();
	boolean getRunningStatus();
	boolean hasTeletext();
	void unselectTrack(int type);
	void setTrackMuteStatus(int type, boolean mute);
	boolean  getTrackMuteStatus(int type);
	boolean getTrackScramblingStatus(int type);	
	List<MultiFeedServiceInfoImpl> getMultiFeedTracks();	
	String getSelectedMultiFeedTrack();	
	void selectMultiFeedTrack(String trackId);
	void loadVideoManagerCache(int cacheid);
	void relayoutVideo(int left, int top, int width, int height);
	void enableAudio(boolean status);
	boolean getAudioStatus();
	int getCurrentMediaMode();
	void registerTunerSessionCallbacks(IBinder callback);	
	void unregisterTunerSessionCallbacks(IBinder callback);
	String getParentalRating();
	byte[] getOipfSiDescriptor();
	void timeshiftPause();
	void timeshiftStop();
	void timeshiftResume();
	void timeshiftSeekTo(int msecs);
	void timeshiftSetSpeed(int speed, boolean forward);
	void enableTimeshiftTrickModes(boolean enable);
	boolean getTimeshiftTrickModeStatus();
	int getTimeshiftCurrentDuration();
	int getTimeshiftTotalDuration();
	int getTimeshiftBufferedDuration();
	int getTimeshiftPlaybackState();
	int getTimeshiftRecordingStatus();
	TimeshiftInfoImpl getTimeshiftInfo();
	int[] getPrivatePIDInfo();
}
