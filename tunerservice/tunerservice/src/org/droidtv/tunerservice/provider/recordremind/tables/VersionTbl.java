package org.droidtv.tunerservice.provider.recordremind.tables;


import org.droidtv.tunerservice.provider.recordremind.DataStore;
import org.droidtv.tv.provider.IRecordingsContract;

import android.content.ContentValues;


public class VersionTbl implements org.droidtv.tunerservice.provider.recordremind.ItblHandler {

	private static final String TAG = "VersionTblRcd";

	public long insertRecord(DataStore db, ContentValues insertData,
			int versionInfo) {

		return (db.getWritableDatabase().insert(IRecordingsContract.Version, null,
				insertData));
	}

	public String deleteRecord(DataStore db, String where,
			String[] whereSelectArgs, int versionInfo) {

		return String.valueOf((db.getWritableDatabase().delete(IRecordingsContract.Version, where,
				whereSelectArgs)));

	}

	public int updateRecord(DataStore db, ContentValues updateValues,
			String whereStatement, String[] whereSelectionArgs, int versionInfo) {


		return ((db.getWritableDatabase()).update(IRecordingsContract.Version,
			updateValues, whereStatement, whereSelectionArgs));

	/*
		Log.d(TAG, "updated the Version tbl received "+versionInfo);
		if (whereSelectionArgs == null || whereSelectionArgs.length == 0) {
			Log.d("VersionTable record reminder",
					"no version update arg is given to update the version info Number  ");
			return -1;
		}

		String sqlStatement = "INSERT OR REPLACE INTO "
				+ RecordingsContract.Version + " values(" + "1,"
				+ whereSelectionArgs[0] + ")";

		db.getWritableDatabase().execSQL(sqlStatement);
		Log.d(TAG, "updated the Version tbl with version "+whereSelectionArgs[0] );
		return 1;*/
	}
}
