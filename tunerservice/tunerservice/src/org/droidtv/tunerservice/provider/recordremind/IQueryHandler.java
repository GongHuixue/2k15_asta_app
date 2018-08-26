package org.droidtv.tunerservice.provider.recordremind;

import android.database.Cursor;

public interface IQueryHandler extends ItblHandler {

	public Cursor query(DataStore db , String tableName, String[] projection, String selection, String sortOrder );
}
