package org.droidtv.tunerservice.provider.recordremind;

public class RecordingKeys {
	long startTime;
	int recId;
	public RecordingKeys(long start,int recId)
	{
		startTime = start;
		this.recId = recId;
	}
}
