package org.droidtv.tunerservice.interfaces;

import android.net.Uri;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import java.util.Map;

public interface ITvAbstractPlaybackListener {
	public static final int TUNE_FAILED_REASON_NONE					 	= 0;
	public static final int TUNE_FAILED_REASON_RECORDING_IN_PROGRESS 	= 1;
	public static final int TUNE_FAILED_REASON_TAD_IN_PROGRESS 			= 2;
	public static final int TUNE_FAILED_REASON_3D_IN_PROGRESS 			= 3;
	public static final int TUNE_FAILED_REASON_UHD_IN_PROGRESS 			= 4;
	public static final int TUNE_FAILED_REASON_INSTALLATION_IN_PROGRESS = 5;
	public static final int TUNE_FAILED_REASON_CAM_VOD_IN_PROGRESS 		= 6; 

	public static final int PLAYBACK_STATE_STOPPED = 0;
	public static final int PLAYBACK_STATE_PLAYING = 1;
	public static final int PLAYBACK_STATE_PAUSED = 2;
	public static final int PLAYBACK_STATE_TRICKPLAY = 3;
	
	public static final int MODE_TIMESHIFT = 0;
	public static final int MODE_PVR = 1;	

	abstract void onPlayStarted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber);
	abstract void onPlayCompleted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber);
	abstract void onPlayFailed(Uri uri, Medium medium, int presetNumber, int reason);
	abstract void onPlayFinished(Uri uri, Medium medium, int presetNumber);

	abstract void onLicenseExchangeHappening(boolean status);
	abstract void onSeekComplete(int mode);
	
	// Error codes for play error
	public static final int PLAYERROR_HDD 		= 1;
	public static final int PLAYERROR_SYSTEM 	= 2;
	public static final int PLAYERROR_FACTORY 	= 3;
	
	abstract void onPlayError(int error, int what , int extra, int mode);

	// Channel type values
	public static final int CHANNELTYPE_TV = 1;
	public static final int CHANNELTYPE_RADIO = 2;
	
	abstract void onServiceTypeDetected(int type);

	abstract void onTrickModeEnabled(boolean status, int mode);
	abstract void onPlayStateChanged(int state, int mode);
	abstract void onLockStatusChanged(int type, int status);
	abstract void onInfo(boolean cicamAvailable);
	abstract void onMPLPurposeChanged(int purpose);
	abstract void onTimeshiftInfoChanged();
	
	// Constants TO BE REMOVED when TvView is replaced by session
/*	public static final int ONSHOWSPINNER = 5;
	public static final int ONREMOVESPINNER = 6;
	public static final int ONRESETSPEED = 7;
	public static final int ONSEEKCOMPLETENOTIFY = 8;
	public static final int ONDISABLETRICKMODES = 9;
	public static final int ONENABLETRICKMODES = 10;
	public static final int ONPLAYSTATECHANGED = 11;
	public static final int ONMAXCIRCULARBUFFERREACHED = 12;
	public static final int ONCATCHUPLIVE = 13;
	public static final int ONLISTENERCHANGED = 14;
	public static final int ONPLAYFROMSTART = 15;
	public static final int ONPLAYERROR_HDD = 16;
	public static final int ONPLAYERROR_SYSTEM = 17;
	public static final int ONCHANNELTYPE_TV = 18;
	public static final int ONCHANNELTYPE_RADIO = 19;*/
}