package org.droidtv.tv.tvinput;

interface RecordCallbacks
{		
	void onSeekCompleted();

	void onPlayError(int reason);

	void onTrickModeEnabled(boolean enable);

	void onPlayStateChanged(int state);
}
