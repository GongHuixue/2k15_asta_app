package org.droidtv.tunerservice.provider.recordremind;

/**
 * @author shreesha.vailaya
 * 
 *
 */
public class Recordings {
	
	long startTime;
	long endTime;
	String recordingEventName;
	int medium;
	int recId;
	boolean isLocked;
	
	
	public Recordings(long start,long end,int id,int medium,String evName)
	{
		startTime = start;
		endTime = end;
		this.medium = medium;
		recId = id;
		isLocked = false;
		recordingEventName = evName;
	}
	
	public synchronized boolean isRecordingLocked()
	{
		return isLocked;
	}
	
	public synchronized void setLocked()
	{
		isLocked = true;
	}
	
	public int getrecordingId()
	{
		return recId;
	}
}
