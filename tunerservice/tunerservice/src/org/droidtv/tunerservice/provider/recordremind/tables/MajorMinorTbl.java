package org.droidtv.tunerservice.provider.recordremind.tables;

import org.droidtv.tunerservice.provider.recordremind.DataStore;
import org.droidtv.tunerservice.provider.recordremind.IQueryHandler;
import org.droidtv.tunerservice.provider.recordremind.RecordRemindProvider;
import org.droidtv.tv.provider.IChannelContract;

import android.content.ContentValues;
import android.database.Cursor;
import android.util.Log;

public class MajorMinorTbl implements IQueryHandler {

	@Override
	public long insertRecord(DataStore db, ContentValues insertData,
			int versionInfo) {
		return -1;
	}

	@Override
	public int updateRecord(DataStore db, ContentValues updateValues,
			String whereStatement, String[] whereSelectionArgs, int versionInfo) {
		
		if(updateValues != null ) {

			String sqlStatement = "INSERT OR REPLACE INTO "
				+ RecordRemindProvider.Mjr_Mnr_Ver_Tbl + " values(" + "1,"
				+ updateValues.getAsString(IChannelContract.C_MAJOR_VERSION) + ","
				+ updateValues.getAsString(IChannelContract.C_MINOR_VERSION) + ")";

			Log.d("MajorMinorTbl","constructed string to update major version tble "+sqlStatement);

			db.getWritableDatabase().execSQL(sqlStatement);
			return 1;

		} else {
		      return -1;	
		}
	}

	@Override
	public String deleteRecord(DataStore db, String where,
			String[] whereSelectArgs,int versionInfo) {
		return String.valueOf(0);
	}

	@Override
	public Cursor query(DataStore db, String tableName, String[] projection,
			String selection, String sortOrder) {
		
		String SqlQuery = "SELECT " + IChannelContract.C_MAJOR_VERSION + "," 
				+ IChannelContract.C_MINOR_VERSION + " FROM " + tableName;
		
		//return db.getWritableDatabase().rawQuery(SqlQuery, null);
		return db.getReadableDatabase().rawQuery(SqlQuery, null);
	}
}
