package org.droidtv.tunerservice.provider.recordremind;

import android.database.Cursor;
import android.database.MatrixCursor;
import android.content.Context;
import android.util.Log;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tunerservice.recording.RecordData;

/**
 * @author shreesha.vailaya
 *
 */
public class RecordingsAllocation_Single implements IRecordingsAllocation {
	private static final String TAG = "RecordingAllocation_S";
	private static boolean DEBUG_ALLOCATION = true;
	private static RecordingsAllocation_Single _instance = null;
	Context mContext = null;
	private RecordData head = null;
	private IRecordingAllocationNotify listener = null;

	private RecordingsAllocation_Single(Context mContext) {
		Log.d(TAG, "recording allocation - Single, singleton class");
		this.mContext = mContext;
	}

	/**
	 * @return RecordingsAllocation
	 * 
	 * This is a singleton class for managing the recording allocations to tuners. Used in recording content provider
	 */
	public static synchronized RecordingsAllocation_Single getInstance(Context mContext) {
		if(_instance == null) {
			_instance = new RecordingsAllocation_Single(mContext);
		}
		return _instance;
	}
		
	public  int getTunerCapability(int tunerNumber) {
		return 0;
	}

	public void setTunerCapability(int tunerNumber, int capability) {
	}

	//synchronized method is a syntactical sugar for synchronized(this) for the contents of the method
	//refer : http://stackoverflow.com/questions/3047564/java-synchronized-method-lock-on-object-or-method
	public synchronized void addRecording(Recordings value) {
		//we dont maintain any list for single recording
	}

	public synchronized boolean deleteRecording(RecordingKeys key )
	{
		//we dont maintain any list for single recording
		return false;
	}

	public synchronized void updateRecording(Recordings value)
  	{
		//we dont maintain any list for single recording
  	}

	public synchronized Cursor getScheduleRecordings(int tunerNumber, boolean limitOne)
	{
		if( (limitOne) && (head != null) ) {
			MatrixCursor result = new MatrixCursor(IRecordingsContract.GET_RECORDINGS_DEFAULT_PROJECTIONS);
			result.addRow(new Object[] {head.recordId, head.channelId, head.est, head.eet});
			return result;
		}
		return null; //not supported as of now..
	}

	public synchronized Cursor getConflictingRecordings(Recordings value) {
		Log.d(TAG,"getNumberOfConflictingRecords " + value.recId);
		
		String[] selectionArgs = null;//{String.valueOf(endtime), String.valueOf(starttime)} ;
		String sortorder=IRecordingsContract.C_EFFECTIVE_START_TIME; // default is Ascending
		String selectionClause = "( ( (" + IRecordingsContract.C_EFFECTIVE_START_TIME + "<" +value.endTime+")"  + "AND ("
				+IRecordingsContract.C_EFFECTIVE_END_TIME+")"+">"+ value.startTime+")"+" AND (("+
				IRecordingsContract.C_RECORDING_TYPE+"=="+IRecordingsContract.RecordingType.RECORDING_SCHEDULED.ordinal()+")"+
				" OR ("+ IRecordingsContract.C_RECORDING_TYPE+"=="+IRecordingsContract.RecordingType.RECORDING_OTR.ordinal()+")"+
				" OR ("+ IRecordingsContract.C_RECORDING_TYPE+"=="+IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal()+")"+				
				" OR ("+ IRecordingsContract.C_RECORDING_TYPE+"=="+IRecordingsContract.RecordingType.RECORDING_MANUAL.ordinal()+")))";
		String projection[] = {IRecordingsContract.C_RECORDING_ID, IRecordingsContract.C_EFFECTIVE_START_TIME, IRecordingsContract.C_EFFECTIVE_END_TIME, 
								IRecordingsContract.C_RECORDING_NAME};

		Log.d(TAG, "selection clause " + selectionClause);
		
		Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, 
						selectionClause, selectionArgs, sortorder);
		MatrixCursor result = new MatrixCursor(IRecordingsContract.GET_CONFLICTS_PROJECTIONS);
		long start = 0, end = 0;
		long firstHalf = 0, tempHalf;
		long option1Start = 0, option1End = 0;
		long recordStartTime = 0;
		long tempStartTime;
		if(c != null) {
			try
			{
			if(c.getCount() == 0) {
				return result;
			}
			Log.d(TAG, "not zero cursor for conflict detection " + value.startTime + "," + value.endTime);
			c.moveToFirst();
			tempStartTime = c.getLong(1);
			if(value.startTime < tempStartTime) {
				firstHalf = tempStartTime - value.startTime;
				option1Start = value.startTime;
				option1End = tempStartTime;
			}		
			Log.d(TAG, "1 : " + firstHalf + "," + option1Start + "," + option1End);
			recordStartTime = c.getLong(2);
			//copy this as a delete option..
			result.addRow(new Object[] {c.getInt(0), c.getLong(1), c.getLong(2), c.getString(3), 1, IRecordingsContract.RESOLVE_ACTION_DELETE});
			c.moveToNext();
			while(!c.isAfterLast()) {
				tempStartTime = c.getLong(1);
				if(recordStartTime < tempStartTime) {
					tempHalf = tempStartTime - recordStartTime;
					if(tempHalf > firstHalf) {
						firstHalf = tempHalf;
						option1Start = recordStartTime;
						option1End = tempStartTime;
					}
				}
				if(recordStartTime < c.getLong(2) ) {
					recordStartTime = c.getLong(2);
				}
				Log.d(TAG, "2 : " + firstHalf + "," + option1Start + "," + option1End + "," + recordStartTime);
				//copy this as a delete option..
				result.addRow(new Object[] {c.getInt(0), c.getLong(1), c.getLong(2), c.getString(3), 1, IRecordingsContract.RESOLVE_ACTION_DELETE});
				c.moveToNext();
			}
			if(recordStartTime < value.endTime) {
				tempHalf = value.endTime - recordStartTime;
				if(tempHalf > firstHalf) {
					firstHalf = tempHalf;
					option1Start = recordStartTime;
					option1End = value.endTime;
				}
			}
			Log.d(TAG, "3 : " + firstHalf + "," + option1Start + "," + option1End);
			if(option1Start != 0) {
				result.addRow(new Object[] {value.recId, option1Start, option1End, value.recordingEventName, 2, IRecordingsContract.RESOLVE_ACTION_PARTIAL_RECORDING});
			}
		}
		finally
		{
			c.close();
			c=null;
		}
		}
		return result;
	}

	public synchronized void clearAllRecordings()
	{
		//we dont maintain any list for single recording
	}

	public  synchronized void lockRecordingHead(int recordingId, int tunerNumber)
	{
		//we dont maintain any list for single recording
	}

	public synchronized void registerForNotification(IRecordingAllocationNotify ref) {
		listener = ref;
	}

	public synchronized void setNextRecording(RecordData record) {
		boolean notify = false;
		if( (head == null) && (record != null) ) {
			notify = true;
		} else if( (head != null) && (record == null) ) {
			notify = true;
		} else if( (head != null) && (record != null) ) {
			if( (head.recordId != record.recordId) || (head.est != record.est) ) {
				notify = true;
			}
		}
		head = record;
		Log.d(TAG, "head change " + notify);
		if( (notify) && (listener != null) ) {
			listener.onRecordingHeadChanged(2, head);
		}
	}
}

