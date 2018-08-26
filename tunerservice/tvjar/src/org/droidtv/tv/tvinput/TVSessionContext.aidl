package org.droidtv.tv.tvinput;

import android.os.IBinder;
import android.os.Parcelable;
import java.lang.String;

import org.droidtv.tv.media.TvMediaPlayerContext;

interface TVSessionContext
{		
	IBinder getITvTunerSession();
	IBinder getITVExtensionSession();
	IBinder getITvRecordPlayback();
	IBinder getITVCIControl();
	TvMediaPlayerContext getTvMediaPlayerContext();
	void registerSessionContextCallbacks(IBinder callback);	
	void unregisterSessionContextCallbacks(IBinder callback);
}
