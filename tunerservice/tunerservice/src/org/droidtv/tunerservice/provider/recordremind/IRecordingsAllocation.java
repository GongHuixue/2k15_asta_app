package org.droidtv.tunerservice.provider.recordremind;

import android.database.Cursor;

public interface IRecordingsAllocation {
	final int TUNER_ONE = 1, TUNER_TWO = 2;
	final int TUNER_CAPABILITY_EQUAL = 0;
	final int TUNER_CAPABILITY_LESS = -1;
	final int TUNER_CAPABILITY_HIGHER = 1;
	final int TUNER_CAPABILITY_CABLE_TERRESTRIAL = 0x01;
	final int TUNER_CAPABILITY_SATELLITE = 0x02;
	final int MEDIUM_ANTENNA = 0;
	final int MEDIUM_CABLE = 1;
	final int MEDIUM_SATELLITE = 2;
	public  int getTunerCapability(int tunerNumber);
	public void setTunerCapability(int tunerNumber, int capability);
	public void addRecording(Recordings value);
	public boolean deleteRecording(RecordingKeys key);
	public void updateRecording(Recordings value);
	public Cursor getScheduleRecordings(int tunerNumber, boolean limitOne);
	public Cursor getConflictingRecordings(Recordings value);
	public void clearAllRecordings();
	public void lockRecordingHead(int recordingId, int tunerNumber);
	public void registerForNotification(IRecordingAllocationNotify ref);
}

