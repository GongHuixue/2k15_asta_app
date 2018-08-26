package org.droidtv.tunerservice.provider.recordremind.tables;


import org.droidtv.tunerservice.provider.recordremind.DataStore;
import org.droidtv.tv.provider.IRecordingsContract;

import android.content.ContentValues;


public class ParentVersionTbl implements org.droidtv.tunerservice.provider.recordremind.ItblHandler {

	public long insertRecord(DataStore db, ContentValues insertData,
			int versionInfo) {

		return (db.getWritableDatabase().insert(IRecordingsContract.ParentVersion,
				null, insertData));
	}

	public String deleteRecord(DataStore db, String where,
			String[] whereSelectArgs, int versionInfo) {

		return String.valueOf((db.getWritableDatabase().delete(IRecordingsContract.ParentVersion,
				where, whereSelectArgs)));
	}

	public int updateRecord(DataStore db, ContentValues updateValues,
			String whereStatement, String[] whereSelectionArgs, int versionInfo) {

		return (db.getWritableDatabase().delete(IRecordingsContract.ParentVersion,
				whereStatement, whereSelectionArgs));
	}

}
