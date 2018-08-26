package org.droidtv.tunerservice.provider.recordremind.tables;


import org.droidtv.tunerservice.provider.recordremind.DataStore;
import org.droidtv.tunerservice.provider.recordremind.ItblHandler;
import org.droidtv.tunerservice.provider.recordremind.RecordRemindProvider;
import org.droidtv.tv.provider.IRecordingsContract;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.SQLException;
import android.util.Log;

public class RecordingTbl implements ItblHandler {

	private final String TAG = "RecordingTable";

	public long insertRecord(DataStore db, ContentValues insertData,
			int versionInfo) {
		
		Log.d(TAG,"Inserting Recording table with verion Id"+versionInfo);

		insertData.put(IRecordingsContract.C_VERSION, versionInfo);
		return (db.getWritableDatabase().insert(IRecordingsContract.RECORDINGS_TABLE,
				null, insertData));
	}

	public int updateRecord(DataStore db, ContentValues updateValues,
			String whereStatement, String[] whereSelectionArgs, int versionInfo) {

		Log.d(TAG,"Updating Recording table with verion Id"+versionInfo);

		updateValues.put(IRecordingsContract.C_VERSION, versionInfo);

		return ((db.getWritableDatabase()).update(
				IRecordingsContract.RECORDINGS_TABLE, updateValues, whereStatement,
				whereSelectionArgs));
	}

	public String deleteRecord(DataStore db, String where,
			String[] whereSelectArgs, int versionInfo) {

		String recordString = null;
		
		Log.d(TAG,"Deleting Recording table with version Id");

		Cursor cursor = db.getReadableDatabase().query(
				IRecordingsContract.RECORDINGS_TABLE,
				new String[] { IRecordingsContract.C_RECORDING_ID, IRecordingsContract.C_SERVER_RECORDING_ID}, where,
				whereSelectArgs, null, null, null);
				
		Log.d(TAG, "cursor for record id and server recording id "+ cursor);
		
		if(cursor != null)
		{
		    try
			{
			    if (cursor.getCount() == 1 && cursor.moveToFirst()) {
		
			         int recordingId = cursor.getInt(cursor.getColumnIndex(IRecordingsContract.C_RECORDING_ID));
					
			         int serverRecordingId = cursor.getInt(cursor.getColumnIndex(IRecordingsContract.C_SERVER_RECORDING_ID));
					
			         Log.d(TAG, "recordingId="+ recordingId +"serverRecordingId="+serverRecordingId );
			
			         recordString = IRecordingsContract.C_RECORDING_ID +"="+recordingId+"&"+IRecordingsContract.C_SERVER_RECORDING_ID+"="+serverRecordingId;
			
		        } else if(cursor.getCount() > 1){
		
			       Log.d(TAG,"multiple records deletion");
			       recordString=IRecordingsContract.C_RECORDING_ID +"=*.*"+"&"+IRecordingsContract.C_SERVER_RECORDING_ID+"=*.*";
		        }
			}
			finally
			{
				cursor.close();
			    cursor	=null;
			}
			 
		}

		String sqlStatement = "INSERT OR REPLACE INTO "
					+ IRecordingsContract.ParentVersion + " values(" + "1,"
					+ versionInfo + ")";// only 1 record will be added
		try {

			Log.d(TAG, "Delete recording version:"+ versionInfo +" RecordRemindProvider.parentVersion:"+ RecordRemindProvider.parentVersion);
				
			if (versionInfo > RecordRemindProvider.parentVersion) {
					Log.d(TAG, "To Update the ParentVersion with id "+versionInfo);
					RecordRemindProvider.setParentVersion(versionInfo);
					db.getWritableDatabase().execSQL(sqlStatement);
				}
		} catch (SQLException e) {

			Log.d(TAG, "Deleting Statement throws Error" + e);
		}
		
		int id = (db.getWritableDatabase().delete(IRecordingsContract.RECORDINGS_TABLE, where, whereSelectArgs));
		
		if (id > 0) {
			return recordString;
		} else {
			return null;
		}
	}
}
