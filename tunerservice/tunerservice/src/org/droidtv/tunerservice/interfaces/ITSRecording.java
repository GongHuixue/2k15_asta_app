package org.droidtv.tunerservice.interfaces;


public interface ITSRecording {
	abstract void onTSRecordingStarted();
	abstract void onTSRecordingStopped();
	abstract void onTSRecordingStopped(Boolean isHDDReadError);
}