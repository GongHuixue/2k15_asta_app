package org.droidtv.tunerservice.interfaces;

import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import java.util.Map;
import android.net.Uri;

public interface IPlayTvStateChangeListener {
	public static final int TUNE_FAILED_REASON_NONE					 	= 0;
	public static final int TUNE_FAILED_REASON_RECORDING_IN_PROGRESS 	= 1;
	public static final int TUNE_FAILED_REASON_TAD_IN_PROGRESS 			= 2;
	public static final int TUNE_FAILED_REASON_3D_IN_PROGRESS 			= 3;
	public static final int TUNE_FAILED_REASON_UHD_IN_PROGRESS 			= 4;
	public static final int TUNE_FAILED_REASON_INSTALLATION_IN_PROGRESS = 5;
	public static final int TUNE_FAILED_REASON_CAM_VOD_IN_PROGRESS 		= 6; 
	
	abstract void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber);
	abstract void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium, int presetNumber);
	abstract void onPlayFinished(Uri mediaPlayerUri, Medium medium, int presetNumber);
	abstract void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason);
	abstract void onInfo(boolean cicamAvailable);
	abstract void onError(PlayTvMediaPlayer mpl, int what , int extra);
	abstract void onLockStatusChanged(int type, int status);
	abstract void onPurposeChanged(int purpose);
	void onUriChanged(Uri mediaPlayerUri);
	void onCamUpgradeStarted(boolean status);
}
