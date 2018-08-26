package org.droidtv.tunerservice.db;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class CAMSQLiteHelper extends SQLiteOpenHelper {

	 private static final String DATABASE_NAME = "camdetails.db";
	 private static final int DATABASE_VERSION = 1;
	 public static final String TABLE_CAMDETAILS = "camdetails";
	  public static final String COLUMN_ID = "_id";
	  public static final String COLUMN_SLOTID = "slotid";
	  public static final String COLUMN_CAMID = "camid";
	  public static final String COLUMN_CAMIDBLOB = "camidblob";
	  public static final String COLUMN_MEDIUAM = "medium";
	  public static final String COLUMN_CAMSTATUS = "camstatus";
	 // Database creation sql statement
	  private static final String DATABASE_CREATE = "create table "+ TABLE_CAMDETAILS 
			  + "(" + COLUMN_SLOTID + " integer primary key , " 
			  + COLUMN_CAMID  + " text not null ,"
			  + COLUMN_CAMIDBLOB + " blob not null ,"			  
			  + COLUMN_MEDIUAM + " text not null ," 
			  + COLUMN_CAMSTATUS + " text not null);";

	  
	public CAMSQLiteHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

	@Override
	public void onCreate(SQLiteDatabase database) {
		database.execSQL(DATABASE_CREATE);
	}

	@Override
	public void onUpgrade(SQLiteDatabase datbase, int arg1, int arg2) {
		datbase.execSQL("DROP TABLE IF EXISTS " + TABLE_CAMDETAILS);
	    onCreate(datbase);
	}

	
}
