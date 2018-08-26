package org.droidtv.tunerservice.provider.recordremind;

import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.provider.IRemindersContract;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class DataStore extends SQLiteOpenHelper 
{
	
	// path for recording/reminder database
	private static final String DBPATH="/user_setting/rw/tvserver/databases/recordings/"+IRecordingsContract.Recordings;
	public static final String REC_REM_VIEW="RecRemView";
	
	// schema for recording table 
	public static String RecordingsTableColumns = "(" +
			IRecordingsContract.C_RECORDING_ID + " INTEGER PRIMARY KEY  AUTOINCREMENT NOT NULL, " +
			IRecordingsContract.C_RECORDING_TYPE + " INTEGER, " +
			IRecordingsContract.C_RECORDING_ERROR + " INTEGER, " +
			IRecordingsContract.C_ISIPEPG_RECORDING + " BOOL, " +
			IRecordingsContract.C_EVENT_ID + " INTEGER, " +
			IRecordingsContract.C_CHANNELID + " INTEGER, " +
			IRecordingsContract.C_STARTTIME + " BIGINT  DEFAULT 0, " +
			IRecordingsContract.C_DURATION + " BIGINT  DEFAULT 0, " +
			IRecordingsContract.C_MARGIN_START + " INTEGER  DEFAULT 0, " +
			IRecordingsContract.C_MARGIN_END + " INTEGER  DEFAULT 0, " +
			IRecordingsContract.C_EIT_VERSION + " INTEGER, " +
			IRecordingsContract.C_AUTO_MARGIN_START + " INTEGER  DEFAULT 0, " +
			IRecordingsContract.C_AUTO_MARGIN_END + " INTEGER  DEFAULT 0, " +
			IRecordingsContract.C_EVENT_SHORT_INFO + " VARCHAR, " +
			IRecordingsContract.C_IS_PARTIAL + " BOOL, " +
			IRecordingsContract.C_RETENTION_INFO + " NUMERIC, " +
			IRecordingsContract.C_RESUME_INFO + " INTEGER, " +
			IRecordingsContract.C_RECORDING_NAME + " VARCHAR, " +
			IRecordingsContract.C_SIZE_IN_MB + " INTEGER, " +
			IRecordingsContract.C_HAS_LICENSE_FILE + " BOOL, " +
			IRecordingsContract.C_PROGRAM_NUMBER + " INTEGER, " +
			IRecordingsContract.C_CICAMID + " INTEGER, " +
			IRecordingsContract.C_LAST_PIN_CHANGE_TIME + " NUMERIC, " +
	        IRecordingsContract.C_ISFTARECORDING + " BOOL, "+
			IRecordingsContract.C_HASDOT+ " BOOL, "+
			IRecordingsContract.C_SERVER_RECORDING_ID+ " INTEGER, "+
			IRecordingsContract.C_EVENT_NAME + " VARCHAR, " +
			IRecordingsContract.C_EVENT_EXTENDED_INFO + " VARCHAR, " +
			IRecordingsContract.C_EVENT_GUIDANCE_INFO + " VARCHAR, " +
			IRecordingsContract.C_EVENT_GENRE+ " INTEGER, "+
			IRecordingsContract.C_EVENT_RATING+ " INTEGER, "+
			IRecordingsContract.C_HAS_CICAM_PIN+ " BOOL, "+
			IRecordingsContract.C_EPISODE_ID+" VARCHAR,"+
			IRecordingsContract.C_SERIES_ID+" VARCHAR,"+
			IRecordingsContract.C_SEASON_NO+" INTEGER,"+
			IRecordingsContract.C_EPISODE_NO+" INTEGER,"+
			IRecordingsContract.C_EPISODE_COUNT+" INTEGER,"+
	        IRecordingsContract.C_ACTUAL_START_TIME	+" BIGINT DEFAULT 0,"+
	        IRecordingsContract.C_EIT_SOURCE+" INTEGER,"+
	        IRecordingsContract.C_ISRADIO+" BOOL,"+
			IRecordingsContract.C_PROGRAM_IMAGE_TYPE+" INTEGER,"+
			IRecordingsContract.C_ABSOLUTE_TIME+" BIGINT,"+
			IRecordingsContract.C_PROGRAM_DURATION+" BIGINT,"+
	        IRecordingsContract.C_VERSION + " INTEGER NOT NULL)";

	// schema for reminder table
	public static final String  RemindersTableColumns="("+
	        IRemindersContract.C_REMINDER_ID+" INTEGER PRIMARY KEY AUTOINCREMENT,"+
			IRemindersContract.C_REM_CHANNELID +" integer,"+
			IRemindersContract.C_REM_EVENTID +" integer,"+
			IRemindersContract.C_REM_EVENTNAME +" text,"+
			IRemindersContract.C_REM_SHORTINFO +" text,"+
			IRemindersContract.C_REM_STARTTIME+ " integer,"+
			IRemindersContract.C_REM_ENDTIME+ " integer,"+
			IRemindersContract.C_EIT_SOURCE+ " integer,"+
			IRemindersContract.C_REM_MEDIUM+" integer)";
	
	
	@Override
	public void onDowngrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		
		Log.d(TAG, "onDowngrade called with old version->"+oldVersion+" new version->"+newVersion);
	}

	private static final String TAG = "RecordingsProviderDataStrore";
	private static DataStore DataStroreInstance = null;
		
	public DataStore(Context context, String name, CursorFactory factory,
			int version) {

		super(context, name, factory, version);
	}
	
	@Override
	public void onCreate(SQLiteDatabase db) {
		

		String sqlStatement = "CREATE TABLE "+IRecordingsContract.RECORDINGS_TABLE+RecordingsTableColumns;
	
		db.execSQL(sqlStatement);
	
		sqlStatement = "CREATE TABLE version (_id INTEGER PRIMARY KEY  NOT NULL,"
				+ "Version INTEGER NOT NULL)";
	
		db.execSQL(sqlStatement);
	

		sqlStatement = "CREATE TABLE parentversion (_id INTEGER PRIMARY KEY  NOT NULL,"
				+ "Version INTEGER NOT NULL)";

		db.execSQL(sqlStatement);
	
	    db.execSQL("CREATE TABLE IF NOT EXISTS " +  IRemindersContract.REMINDERS_TABLE + 
	    		RemindersTableColumns);
	    
	    sqlStatement = "CREATE TABLE IF NOT EXISTS " + RecordRemindProvider.Mjr_Mnr_Ver_Tbl +"(_id INTEGER PRIMARY KEY  NOT NULL," +
	    		IChannelContract.C_MAJOR_VERSION +" INTEGER NOT NULL," +
				IChannelContract.C_MINOR_VERSION + " INTEGER NOT NULL)";
	    
	    db.execSQL(sqlStatement);
	    
     	    Log.d("recordReminder", "Created Tables Reminders, Version, Parent Version, Recording");
     	    
     	 try
		 {
     		 // creating a recording+reminder view
     		 String sql=getRecRemView();
     		 Log.d(TAG,"View Creaton for Recording Reminders: "+sql);
     		 db.execSQL(sql);
		 }
		 catch(Exception e)
		 {
			 Log.d(TAG,"onCreate():Exception:"+e);
		 }
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		Log.d(TAG, "version change - old:"+oldVersion+" new:"+newVersion);
	}

	public static DataStore getInstance(Context clientContext) {

		if (DataStroreInstance == null) {
			DataStroreInstance = new DataStore(clientContext, DBPATH,
					null, 1);
		}
		return DataStroreInstance;
	}
	 private String getRecRemView()
	   {
		   String sql="CREATE VIEW IF NOT EXISTS "+REC_REM_VIEW+" AS SELECT "+IRecordingsContract.C_RECORDING_ID+","+
	               IRecordingsContract.C_RECORDING_TYPE+","+IRecordingsContract.C_RECORDING_ERROR + "," +
				   IRecordingsContract.C_ISIPEPG_RECORDING + "," +IRecordingsContract.C_SERVER_RECORDING_ID+","+
				   IRecordingsContract.C_EVENT_ID + ","+IRecordingsContract.C_CHANNELID + "," +
				   IRecordingsContract.C_STARTTIME + "," +IRecordingsContract.C_DURATION + "," +
				   IRecordingsContract.C_MARGIN_START + "," +IRecordingsContract.C_MARGIN_END + "," +
				   IRecordingsContract.C_EIT_VERSION + "," +IRecordingsContract.C_AUTO_MARGIN_START + "," +
				   IRecordingsContract.C_AUTO_MARGIN_END + "," +IRecordingsContract.C_EVENT_SHORT_INFO + "," +
				   IRecordingsContract.C_IS_PARTIAL + "," +IRecordingsContract.C_RETENTION_INFO + "," +
				   IRecordingsContract.C_RESUME_INFO + "," +IRecordingsContract.C_RECORDING_NAME + "," +
				   IRecordingsContract.C_SIZE_IN_MB + "," +IRecordingsContract.C_HAS_LICENSE_FILE + "," +
				   IRecordingsContract.C_PROGRAM_NUMBER + "," +	IRecordingsContract.C_CICAMID + "," +
				   IRecordingsContract.C_LAST_PIN_CHANGE_TIME + "," +IRecordingsContract.C_HAS_CICAM_PIN+","+
				   "'-1' AS '"+IRemindersContract.C_REM_MEDIUM + "',"+
				   IRecordingsContract.C_ISFTARECORDING + ","+
				   IRecordingsContract.C_HASDOT+ ","+IRecordingsContract.C_EVENT_NAME + "," +
				   IRecordingsContract.C_EVENT_EXTENDED_INFO + "," +IRecordingsContract.C_EVENT_GUIDANCE_INFO +","+
				   IRecordingsContract.C_EVENT_GENRE+ ","+IRecordingsContract.C_EVENT_RATING+ ","+
				   IRecordingsContract.C_VERSION+","+
				   IRecordingsContract.C_EPISODE_ID+","+IRecordingsContract.C_SERIES_ID+","+
				   IRecordingsContract.C_SEASON_NO+","+IRecordingsContract.C_EPISODE_NO+","+
				   IRecordingsContract.C_EPISODE_COUNT+","+IRecordingsContract.C_ACTUAL_START_TIME+","+
				   IRecordingsContract.C_EIT_SOURCE+","+IRecordingsContract.C_ISRADIO+","+
				   "'-1' AS '"+IRemindersContract.C_REM_ENDTIME+"',"+
				   IRecordingsContract.C_PROGRAM_IMAGE_TYPE+","+
				   IRecordingsContract.C_ABSOLUTE_TIME+","+
				   IRecordingsContract.C_PROGRAM_DURATION+
				   " FROM "+IRecordingsContract.RECORDINGS_TABLE+" UNION ALL "+
				   " SELECT "+IRemindersContract.C_REMINDER_ID+"," +
				   "'-1' AS '"+IRecordingsContract.C_RECORDING_TYPE+"',"+"'-1' AS '"+IRecordingsContract.C_RECORDING_ERROR+"'," +
				   "'0' AS '" +IRecordingsContract.C_ISIPEPG_RECORDING + "'," +"'-1' AS '"+IRecordingsContract.C_SERVER_RECORDING_ID+"',"+
				   IRemindersContract.C_REM_EVENTID +","+IRemindersContract.C_REM_CHANNELID +","+
				   IRemindersContract.C_REM_STARTTIME+ "," +"'-1' AS '"+IRecordingsContract.C_DURATION +"',"+ 
				   "'-1' AS '" +IRecordingsContract.C_MARGIN_START + "','-1' AS '" +IRecordingsContract.C_MARGIN_END + "'," +
				   "'-1' AS '"+IRecordingsContract.C_EIT_VERSION + "','-1' AS '" +IRecordingsContract.C_AUTO_MARGIN_START + "'," +
				   "'-1' AS '" +IRecordingsContract.C_AUTO_MARGIN_END + "'," +IRemindersContract.C_REM_SHORTINFO + "," +
				   "'0' AS '" +IRecordingsContract.C_IS_PARTIAL + "','-1' AS '" +IRecordingsContract.C_RETENTION_INFO + "'," +
				   "'-1' AS '"+IRecordingsContract.C_RESUME_INFO + "'," +IRemindersContract.C_REM_EVENTNAME + "," +
				   "'-1' AS '" +IRecordingsContract.C_SIZE_IN_MB + "'," +"'0' AS '"+IRecordingsContract.C_HAS_LICENSE_FILE +"',"+
				   "'-1' AS '" +IRecordingsContract.C_PROGRAM_NUMBER + "','-1' AS '" +IRecordingsContract.C_CICAMID + "'," +
				   "'-1' AS '"+IRecordingsContract.C_LAST_PIN_CHANGE_TIME+"','0' AS '"+IRecordingsContract.C_HAS_CICAM_PIN+"'," +
				   IRemindersContract.C_REM_MEDIUM +","+
				   "'0' AS '"+IRecordingsContract.C_ISFTARECORDING + "'," +
				   "'0' AS '"+IRecordingsContract.C_HASDOT+"'," +"'null' AS '"+IRecordingsContract.C_EVENT_NAME + "'," +
				   "'null' AS '" +IRecordingsContract.C_EVENT_EXTENDED_INFO + "',"+"'null' AS '" +IRecordingsContract.C_EVENT_GUIDANCE_INFO + "'," +
				   "'-1' AS '"+IRecordingsContract.C_EVENT_GENRE+ "',"+"'-1' AS '"+IRecordingsContract.C_EVENT_RATING+ "'," +
				   "'-1' AS '"+IRecordingsContract.C_VERSION +"',"+
				   "'null' AS '"+IRecordingsContract.C_EPISODE_ID+"',"+"'null' AS '"+IRecordingsContract.C_SERIES_ID+"',"+
				   "'-1' AS '"+IRecordingsContract.C_SEASON_NO+"',"+"'-1' AS '"+IRecordingsContract.C_EPISODE_NO+"'," +
				   "'-1' AS '"+IRecordingsContract.C_EPISODE_COUNT+"',"+"'-1' AS '"+IRecordingsContract.C_ACTUAL_START_TIME+"'," +
				   IRemindersContract.C_EIT_SOURCE+","+"'0' AS '"+IRecordingsContract.C_ISRADIO+"',"+
				   IRemindersContract.C_REM_ENDTIME+","+
				   "'-1' AS '"+IRecordingsContract.C_PROGRAM_IMAGE_TYPE+"',"+
				   "'-1' AS '"+IRecordingsContract.C_ABSOLUTE_TIME+"',"+
				   "'-1' AS '"+IRecordingsContract.C_PROGRAM_DURATION+"'"+
				   " FROM "+IRemindersContract.REMINDERS_TABLE;
		   return sql;
	   }

}
