package org.droidtv.tunerservice.provider.recordremind;

import android.content.ContentValues;

public interface ItblHandler {

	public long insertRecord(DataStore db, ContentValues insertData,
			int versionInfo);

	public int updateRecord(DataStore db, ContentValues updateValues,
			String whereStatement, String[] whereSelectionArgs, int versionInfo);

	public String deleteRecord(DataStore db, String where,
			String[] whereSelectArgs, int versionInfo);

}
