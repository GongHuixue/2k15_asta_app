package org.droidtv.tunerservice.provider.recordremind;

import org.droidtv.tunerservice.recording.RecordData;

public interface IRecordingAllocationNotify {
	
	/**
	 * @param tuner 
	 * @param value: null, if no further recording to be scheduled
	 */
	void onRecordingHeadChanged(int tuner, RecordData value);

}
