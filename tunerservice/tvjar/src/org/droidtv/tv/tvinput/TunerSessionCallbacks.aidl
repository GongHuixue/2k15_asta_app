package org.droidtv.tv.tvinput;

import android.net.Uri;
import java.lang.String;
import android.os.Bundle;

interface TunerSessionCallbacks
{		
	void onScramblingStatusChanged(int tracktype, boolean status);
	
	void OnDualStatusChanged(int channel, int controllable);
	
	void OnBroadcastPreMixedVIPlayed(boolean status);
	
	void OnReplacementSvcTuneRequested(int origNetworkId, int tsId,int serviceId);
	
	void onMultifeedFeedDetected();
	
	void onLinkageTypeDetected(int spid,int onID,int tsID,int linkageType);
	
	void onTuneFailed(String inputid, in Uri channelUri, int reason);
	
	void onTuneStarted(String inputid, in Uri channelUri, in Bundle bundle);	
	
	void onTuneCompleted(String inputid, in Uri channelUri, in Bundle bundle);
	
	void onMediaModeChanged(int mode);
	
	void onTimeshiftSeekCompleted();
	
	void onTimeshiftTrickModeEnabled(boolean enable);
	
	void onTimeshiftPlayStateChanged(int state);
	
	void onTimeshiftRecordingStatusChanged(int status);
	
	void onTimeshiftPlayError(int reason);
	
	void onTimeshiftInfoChanged();

	void onPrivatePidInfoChanged();
}
