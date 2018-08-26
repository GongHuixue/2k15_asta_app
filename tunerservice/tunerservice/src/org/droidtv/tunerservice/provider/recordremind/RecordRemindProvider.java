package org.droidtv.tunerservice.provider.recordremind;

import org.droidtv.tunerservice.util.PlayTvHDDUtils;
import android.database.sqlite.SQLiteQueryBuilder;
import android.os.ParcelFileDescriptor;
import java.io.File;
import java.io.FileNotFoundException;
import org.droidtv.tv.provider.IRecordingsContract.RecordingUri;
import android.media.tv.TvContract;
import android.app.SearchManager;
import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.Context;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.MatrixCursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.os.Binder;
import android.util.Log;
import java.util.Arrays;
import java.util.Set;
import org.droidtv.tv.media.TvURI;
import org.droidtv.tunerservice.provider.recordremind.tables.MajorMinorTbl;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.UriData;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.provider.IRemindersContract;
import org.droidtv.tv.provider.IRecordingReminderContract;
import org.droidtv.tunerservice.recording.RecordData;
public class RecordRemindProvider extends ContentProvider implements IRecordingAllocationNotify {

	private static String TAG = "RecordingProvider";
	private static SQLiteDatabase mReadRecordingsRemindersDBHandle = null;
	private static SQLiteDatabase recordingsremindersDBHandle = null;
	//Function Handlers
	private static int PREVIOUS_RECORD = 1;
	private static int NEXT_RECORD = 2;
	private static int MAX_VERSION_RECORD = 3;
	private static int currentVersion = 0;
	public static int parentVersion = 0;
	// Table Handlers
	private static final int RECORDING = 1;
	private static final int VERSION = 2;
	private static final int PARENT_VERSION = 3;
	private static final int SEARCH_SUGGESTION = 4;
	private static final int REMINDERS = 5;
	private static final int CONFLICTING_RECORDINGS = 6;
	private static final int TUNER_ONE_RECORDINGS = 7;
	private static final int TUNER_TWO_RECORDINGS = 8;
	private static final int MAJOR_MINOR_VERSION=9;
    private static final int RECORDING_REMINDER_VIEW=10;
	private static final int MATCH_RECORDING_ID_PROGRAM_IMAGE=11;
	private int mRecordingMajorVersion = 0;
	private int mRecordingMinorVersion = 0;
	public static final String Mjr_Mnr_Ver_Tbl = "majorminorTbl";
	public static final String[] SearchCursorSchema = {
		SearchManager.SUGGEST_COLUMN_TEXT_1,
		SearchManager.SUGGEST_COLUMN_TEXT_2,
		SearchManager.SUGGEST_COLUMN_ICON_1,
		SearchManager.SUGGEST_COLUMN_DURATION,
		SearchManager.SUGGEST_COLUMN_RATING_SCORE,
		SearchManager.SUGGEST_COLUMN_INTENT_DATA 
		};
	public static String RecordingsSearchProj = IRecordingsContract.C_CHANNELID+","+
		IRecordingsContract.C_RECORDING_ID+","+
		IRecordingsContract.C_RECORDING_NAME + ","+
	    "date("+IRecordingsContract.C_EFFECTIVE_START_TIME+",'unixepoch') AS 'StartTime',"+
	    IRecordingsContract.C_DURATION + ","+
	    IRecordingsContract.C_EVENT_RATING;
	    //strftime('%H:%M:%S',"+
		//IRecordingsContract.C_DURATION+",'unixepoch') AS 'Duration'";
	private IRecordingsAllocation recAllocation;
	
	private static UriMatcher uris = new UriMatcher(UriMatcher.NO_MATCH);
	
	static {
		uris.addURI(IRecordingsContract.AUTHORITY,
				IRecordingsContract.Recordings+"/"+IRecordingsContract.RECORDINGS_TABLE, RECORDING);
		uris.addURI(IRecordingsContract.AUTHORITY, IRecordingsContract.Recordings+"/"+IRecordingsContract.Version,
				VERSION);
		uris.addURI(IRecordingsContract.AUTHORITY,
				IRecordingsContract.Recordings+"/"+IRecordingsContract.ParentVersion, PARENT_VERSION);
		uris.addURI(IRecordingsContract.AUTHORITY, SearchManager.SUGGEST_URI_PATH_QUERY, SEARCH_SUGGESTION);
		uris.addURI(IRecordingsContract.AUTHORITY, IRecordingsContract.CONFLICTING_RECORDINGS, CONFLICTING_RECORDINGS);
		uris.addURI(IRecordingsContract.AUTHORITY, IRecordingsContract.TUNER_ONE_RECORDINGS, TUNER_ONE_RECORDINGS);
		uris.addURI(IRecordingsContract.AUTHORITY, IRecordingsContract.TUNER_TWO_RECORDINGS, TUNER_TWO_RECORDINGS);
        uris.addURI(IRecordingsContract.AUTHORITY, IRecordingsContract.Recordings+"/"+IRecordingsContract.MAJOR_MINOR_VERSION_TABLE,
				MAJOR_MINOR_VERSION);
		uris.addURI(IRemindersContract.AUTHORITY, IRemindersContract.REMINDS_LIST+"/"+IRemindersContract.REMINDERS_TABLE, REMINDERS);
        uris.addURI(IRecordingReminderContract.AUTHORITY, IRecordingReminderContract.DATABASE_RECORDING_REMIND+"/"+IRecordingReminderContract.VIEW_RECORDINGS_REMINDERS, RECORDING_REMINDER_VIEW);
		uris.addURI(IRecordingsContract.AUTHORITY, IRecordingsContract.Recordings+"/"+IRecordingsContract.RECORDINGS_TABLE+"/#", 
				MATCH_RECORDING_ID_PROGRAM_IMAGE);
		
	}

	private String extractTbleName(Uri clientUri) {

		if (uris.match(clientUri) == RECORDING) {

			return clientUri.getLastPathSegment();

		} else if (uris.match(clientUri) == VERSION) {

			return clientUri.getLastPathSegment();

		} else if (uris.match(clientUri) == PARENT_VERSION) {

			return clientUri.getLastPathSegment();
		}
		return null;
	}

	private ItblHandler getTableInstance(Uri clientUri) {

		return (TableFactory.getTableInstance(extractTbleName(clientUri)));
	}

	public int delete(Uri uri, String selection, String[] selectionArgs) {

		String tableName = null;
		int numRows = -1;
		Uri notificationUri = null;
		int pid = Binder.getCallingPid();
		String deletedRecordStringUri = null;
        //Log.d(TAG,"Delete Query with epg record/reminder provider");
		try
		{
		if (uri != null)
		{
			tableName = uri.getLastPathSegment();
			if (tableName.equalsIgnoreCase(IRecordingsContract.RECORDINGS_TABLE))
			{
				synchronized (this)
				{
				    ItblHandler ItableHandlerInstance = getTableInstance(uri);

					if (ItableHandlerInstance != null) {

				    	deletedRecordStringUri = (ItableHandlerInstance.deleteRecord(
						 	DataStore.getInstance(getContext()), selection,
							 selectionArgs,(++currentVersion)));
						Log.d(TAG,"deleted recording string generated"+deletedRecordStringUri);
				    	mRecordingMajorVersion++;
						if (deletedRecordStringUri != null) {
							numRows = 1;
						} 
					}	
				}
			}
			else if (tableName.equalsIgnoreCase(IRecordingsContract.Version))
			{
				synchronized (this)
				{
				    ItblHandler ItableHandlerInstance = getTableInstance(uri);

				     if (ItableHandlerInstance != null) {
						 
						 try {
							numRows = Integer.parseInt((ItableHandlerInstance.deleteRecord(
								DataStore.getInstance(getContext()), selection,
								selectionArgs, -1)));
							Log.d(TAG,"delete Query for Version Table");
						 }catch(NumberFormatException e) {
							Log.d(TAG,"number formant exception in parsing the table tran for version delete");
						 }
						 return numRows;
				      }
				 }
        
			}
			else if (tableName.equalsIgnoreCase(IRecordingsContract.ParentVersion))
			{
				synchronized (this)
				{
				    ItblHandler ItableHandlerInstance = getTableInstance(uri);

				     if (ItableHandlerInstance != null) {

						try {
							numRows= Integer.parseInt((ItableHandlerInstance.deleteRecord(
								DataStore.getInstance(getContext()), selection,
								selectionArgs, -1)));
							Log.d(TAG,"delete Query for Parent Version Table");
						 } catch(NumberFormatException e) {
							Log.d(TAG,"number format exception in the parent version delete");
						 }
						 return numRows;
				      }
				 }
			}

			else if (tableName.equalsIgnoreCase(IRemindersContract.REMINDERS_TABLE))
		    {
				synchronized (this)
				{
					if (recordingsremindersDBHandle == null)
					{
						recordingsremindersDBHandle=DataStore.getInstance(getContext()).getWritableDatabase();
					}
                    numRows = recordingsremindersDBHandle.delete(tableName, selection, selectionArgs);
                    //Log.d(TAG,"delete Query for Reminders Table");
	  			}								
		    }
		}
		if (numRows > 0)
		{
			notificationUri = Uri.parse(uri+"/*");
			Uri.Builder builder = notificationUri.buildUpon();
			builder.appendQueryParameter(IRemindersContract.C_CALLING_PROCESS_ID, ""+pid);
			builder.appendQueryParameter(IRecordingsContract.C_OPERATIONTYPE,IRecordingsContract.C_OPERATIONTYPE_DELETE);
			builder.appendQueryParameter(IRecordingsContract.C_VERSION,  String.valueOf(-1));
			synchronized (this)
			{
				builder.appendQueryParameter(IChannelContract.C_MAJOR_VERSION, String.valueOf(mRecordingMajorVersion));
				builder.appendQueryParameter(IChannelContract.C_MINOR_VERSION, String.valueOf(mRecordingMinorVersion));
			}
			notificationUri = builder.build();
			if (deletedRecordStringUri != null) {
				notificationUri = Uri.parse(notificationUri+"&"+deletedRecordStringUri);
			}
			Log.d(TAG,"updated Uri after the delete opt"+notificationUri.toString());
			updateMajorMinorRecordingVersions();
			deletedRecordStringUri = null;
			getContext().getContentResolver().notifyChange(notificationUri, null);
		}
	}
		catch(Exception e)
		{
			Log.d(TAG,"Exception in deletion="+e);
		}
		return numRows;
	}

	public String getType(Uri uri) {

		return null;
	}

	@Override
	public ParcelFileDescriptor openFile(Uri uri, String mode)
			throws FileNotFoundException {
		Log.d(TAG,"openFile():called");
        switch (uris.match(uri)) {
            case MATCH_RECORDING_ID_PROGRAM_IMAGE:
                return openImageFile(uri, mode);
            default:
                throw new FileNotFoundException(uri.toString());
        }
	}
	
	private ParcelFileDescriptor openImageFile(Uri uri, String mode) throws FileNotFoundException {
        
        Log.d(TAG,"openImageFile():called");
        ParcelFileDescriptor pfd=null;
        long recordingId=-1;
        String table=null;
        try
        {
        	recordingId= Long.parseLong(uri.getLastPathSegment());
        	table=uri.getPathSegments().get(1);
        	Log.d(TAG,"Recordings Table Name:"+table);
        }
        catch(NumberFormatException e)
        {
            Log.d(TAG,"openImageFile():"+e);
            throw new NumberFormatException(e.toString());
        }
        Cursor mRecordingCursor=null;
        try
        {
        	SQLiteDatabase db = DataStore.getInstance(getContext()).getReadableDatabase();
            SQLiteQueryBuilder queryBuilder = new SQLiteQueryBuilder();
            queryBuilder.setTables(table);
            mRecordingCursor = queryBuilder.query(db, new String[] { IRecordingsContract.C_RECORDING_ID },
        			IRecordingsContract.C_RECORDING_ID+"=?", new String[]{String.valueOf(recordingId)}, null, null, null);
            if (mRecordingCursor !=null && mRecordingCursor.getCount() < 1) 
        	{
        		// Fails early if corresponding recording's id does not exist.
        		throw new FileNotFoundException(uri.toString());
            }
            if (mode.equals("r")) 
            {
            	String mountPath = PlayTvHDDUtils.getInstance(getContext()).getMountPath();
            	StringBuilder imagePath;
				
    			if(mountPath!=null && (!mountPath.isEmpty()))
    			{
    				imagePath=new StringBuilder(mountPath).append("/pvr/pvr_").append(recordingId+".tsl/").append(recordingId+".jpeg");
    				Log.d(TAG,"Image Path:"+imagePath);
    				File imageFile=new File(imagePath.toString());
					Log.d(TAG,"Image File:"+imageFile);
    				if(imageFile.exists())
    				{
						Log.d(TAG,"Image File exist");
    					pfd=ParcelFileDescriptor.open(imageFile, ParcelFileDescriptor.MODE_READ_ONLY);
    				}
    			}
            } 
        }
        catch(Exception e)
        {
        	Log.d(TAG,"openImageFile():"+e);
        }
		finally
		{
			if(mRecordingCursor!=null)
				mRecordingCursor.close();
			mRecordingCursor=null;
		}
		Log.d(TAG,"openImageFile(): parcel file descriptor"+pfd);
        return pfd;
    }

	private Cursor getScheduledNextRecord(long effectiveEndTime, Uri clientUri) {

		Log.d(TAG, "getScheduledNextRecord EffectiveEndTime is:"
				+ effectiveEndTime);

		String sqlStatement = "SELECT " + "("
				+ (IRecordingsContract.C_STARTTIME) + "+"
				+ (IRecordingsContract.C_MARGIN_START) + "+"
				+ (IRecordingsContract.C_AUTO_MARGIN_START) + ")	"
				+ " AS  ActualStart FROM  " + extractTbleName(clientUri)
				+ " where ActualStart >= " + effectiveEndTime
				+ " ORDER BY  ActualStart ASC  LIMIT  1";

		Log.d(TAG, "Statemetn to EXEC:" + sqlStatement);
		Cursor cursor=mReadRecordingsRemindersDBHandle.rawQuery(sqlStatement, null);
		return cursor;
	}

	private Cursor getScheduledPreviousRecord(long effectiveStartTime,
			Uri clientUri) {

		Log.d(TAG, "getScheduledPreviousRecord effectiveStartTime is:"
				+ effectiveStartTime);

		String sqlStatement = "SELECT " + "("
				+ (IRecordingsContract.C_STARTTIME) + "+"
				+ (IRecordingsContract.C_DURATION) + "+"
				+ (IRecordingsContract.C_MARGIN_END) + "+"
				+ (IRecordingsContract.C_AUTO_MARGIN_END) + ")"
				+ " AS  ActualEnd  FROM  " + extractTbleName(clientUri)
				+ " where  ActualEnd <= " + effectiveStartTime
				+ " ORDER BY  ActualEnd DESC  LIMIT 1";

		Log.d(TAG, "Statemetn to EXEC:" + sqlStatement);

		//Cursor cursor = DataStrore.getInstance(getContext())
			//	.getWritableDatabase().rawQuery(sqlStatement, null);
		Cursor cursor = mReadRecordingsRemindersDBHandle.rawQuery(sqlStatement, null);

		return cursor;
	}

	public Uri insert(Uri uri, ContentValues values) {
		String tableName = null;
		long insert_count = -1L;
		Uri uriInUri=null;
		Uri notificationUri = null;
		String changeId = null;
		int pid = Binder.getCallingPid();
		
		Log.d(TAG, "Insert Query with epg record/reminder provider");
		
		try {
	
			if (uri != null) {
				
				tableName = uri.getLastPathSegment();
			
				// Check if Change ID is present and remove it
				if ((values != null) && (values.containsKey(IRecordingsContract.C_CHANGE_ID))) {
					changeId = values.getAsString(IRecordingsContract.C_CHANGE_ID);
				  
					values.remove(IRecordingsContract.C_CHANGE_ID);
				}

				if (tableName.equalsIgnoreCase(IRecordingsContract.RECORDINGS_TABLE)) {
					
					synchronized (this)	{
					
						Log.d(TAG, "Inserting the Recording Records");
						ItblHandler ItableHandlerInstance = getTableInstance(uri);
       		  			if (ItableHandlerInstance != null) {					
       		  				insert_count = ItableHandlerInstance.insertRecord(
       		  						DataStore.getInstance(getContext()), values,
       		  						(++currentVersion));
       		  				mRecordingMajorVersion++;
       		  				Log.d(TAG, "Result Received after the Table insertion in the CP:"
       		  						+ insert_count + " mRecordingMajorVersion "+mRecordingMajorVersion);

       		  				uriInUri = Uri.parse("" + insert_count);
       		  			}
					}
				} else if (tableName.equalsIgnoreCase(IRecordingsContract.Version))  {
					Log.d(TAG, "Inserting the Version Records");
            	
					synchronized (this)   	{
						ItblHandler ItableHandlerInstance = getTableInstance(uri);

						if (ItableHandlerInstance != null) {
							insert_count = ItableHandlerInstance.insertRecord(
									DataStore.getInstance(getContext()), values,
									(currentVersion));
							Log.d(TAG, "Result Received after the Table insertion in the CP:"
									+ insert_count);

							uriInUri = Uri.parse("" + insert_count);
							return uriInUri;
						}
					}
				} else if (tableName.equalsIgnoreCase(IRecordingsContract.ParentVersion))  {
					Log.d(TAG, "Inserting the ParentVersion Records");
            	
					synchronized (this)  	{
            		
						ItblHandler ItableHandlerInstance = getTableInstance(uri);

						if (ItableHandlerInstance != null) {
            						insert_count = ItableHandlerInstance.insertRecord(
            							DataStore.getInstance(getContext()), values,
            							currentVersion);

            				Log.d(TAG, "Result Received after the Table insertion in the CP:"
            				+ insert_count);

            				uriInUri = Uri.parse("" + insert_count);
							return uriInUri;
						}
					}
				} else if(tableName.equalsIgnoreCase(IRemindersContract.REMINDERS_TABLE)) {
            	
					Log.d(TAG, "Inserting the Reminders Records");
            	
					synchronized (this) {
				
						if (recordingsremindersDBHandle == null) {
							recordingsremindersDBHandle=DataStore.getInstance(getContext()).getWritableDatabase();
						}
						insert_count = recordingsremindersDBHandle.insert(tableName, null, values);
						uriInUri = Uri.parse("" + insert_count);
					}								
				}
			}
			synchronized (this) {
				if (insert_count > 0) {
					notificationUri = Uri.parse(uri+"/*");
					Uri.Builder builder = notificationUri.buildUpon();
					builder.appendQueryParameter(IRemindersContract.C_CALLING_PROCESS_ID, ""+pid);
					builder.appendQueryParameter(IRecordingsContract.C_OPERATIONTYPE,IRecordingsContract.C_OPERATIONTYPE_INSERT);
					// Add change id to notification
					if (changeId != null) {
						builder.appendQueryParameter(IRemindersContract.C_CHANGE_ID, changeId);
					}
					
					builder.appendQueryParameter(IRecordingsContract.C_VERSION,  String.valueOf(currentVersion));
					builder.appendQueryParameter(IChannelContract.C_MAJOR_VERSION,  String.valueOf(mRecordingMajorVersion));
					builder.appendQueryParameter(IChannelContract.C_MINOR_VERSION, String.valueOf(mRecordingMinorVersion));
					notificationUri = builder.build();
					updateMajorMinorRecordingVersions();
					getContext().getContentResolver().notifyChange(notificationUri, null);
				}
			}
		}
		catch(Exception e){
			 Log.d("SQLite Exception in insertion",""+e);
		}
		return uriInUri;
	}

	public boolean onCreate() {

		DataStore.getInstance(getContext());
		setDBHandle(DataStore.getInstance(getContext()).getWritableDatabase()); //added
		setReadDBHandle(DataStore.getInstance(getContext()).getReadableDatabase()); //added
		Uri uriInstance=Uri.parse("content://"+IRecordingsContract.AUTHORITY +"/"+IRecordingsContract.Recordings+"/"+IRecordingsContract.RECORDINGS_TABLE);
		Cursor currentVersionCursor=null;
		
		try
		{
			currentVersionCursor = getMaxVersionRecord(uriInstance);
		
		   if (currentVersionCursor != null && currentVersionCursor.moveToFirst()
				&& currentVersionCursor.getCount() >= 1
				&& currentVersionCursor.getColumnCount() >= 1) {
			setCurrentVersion(currentVersionCursor.getInt(0));
			Log.d(TAG, "The CurrentVersion Read from the DB Recording"
					+ currentVersion);
		   
		   }
		}
		catch(Exception e)
		{
			Log.d(TAG,"Exception in onCreate():getMaxVersionRecord()");
		}
		finally
		{
			if(currentVersionCursor!=null)
			{
				currentVersionCursor.close();
			    currentVersionCursor=null;
			}
		}

		
		setParentVersion(getParentVersion());

		setCurrentVersion((currentVersion > parentVersion) ? currentVersion
				: parentVersion);

		Log.d(TAG, "onCreate called finished *****" + currentVersion
				+ " parent version " + parentVersion);
		readMajorMinorVersion();
		recAllocation = RecordingsAllocation_Single.getInstance(getContext());
		recAllocation.registerForNotification(this);
		return true;
	}
	
	private int getParentVersion() {

		String sqlStatement = "SELECT " + IRecordingsContract.C_VERSION
				+ " from  parentversion";

		Cursor cursor=null;
		try
		{
		   cursor= DataStore.getInstance(getContext())
				.getReadableDatabase().rawQuery(sqlStatement, null);
		   if (cursor != null && cursor.getCount() >= 1) {
			   cursor.moveToFirst();
			 return cursor.getInt(0);
		   }
		}
		finally
		{
			if(cursor!=null)
			{
				cursor.close();
			    cursor=null;
			}
		}
		return -1;
	}

	public Cursor query(Uri uri, String[] projection, String selection,
			String[] selectionArgs, String sortOrder) {

	     	//Log.d(TAG, "Query with record/reminder provider");
			Cursor resultSet = null;
			int match = uris.match(uri);
			try {
				String tableName = uri.getLastPathSegment();
				Log.d(" The DB Name Received for the Operation is:", tableName);
				
				
				if(mReadRecordingsRemindersDBHandle==null)
				{
					createReadRecordingsRemindersDBHandle(getContext());
				}
				
			     switch (match) {
				   case RECORDING:
				    {
						//Log.d(TAG, "Recordings Table query !!!");
						//synchronized (this)
						//{
						  if (projection != null && projection.length >= 1
								&& (projection[0].toString()).equalsIgnoreCase(""+PREVIOUS_RECORD)) {
							    
							    return (getScheduledPreviousRecord(
								Long.parseLong(projection[1]), uri));
	
   						} else if (projection != null && projection.length >= 1
								&& (projection[0].toString()).equalsIgnoreCase(""+ NEXT_RECORD)) {
							 
							    return (getScheduledNextRecord(Long.parseLong(projection[1]),
									uri));
							 
	
						} else if (projection != null && projection.length >= 1
								&& (projection[0].toString()).equalsIgnoreCase(""+MAX_VERSION_RECORD)) {
							 
							   return (getMaxVersionRecord(uri));
						}
						else
						{
							//if (mReadRecordingsRemindersDBHandle == null)
							//{
						
								//mReadRecordingsRemindersDBHandle=	DataStrore.getInstance(getContext()).getReadableDatabase();
							//}
							
					 		//Log.d(TAG,"before query");
							resultSet = mReadRecordingsRemindersDBHandle.query(tableName, projection, 
									selection, selectionArgs, null, null, sortOrder);
							//Log.d(TAG,"after query");
		                       return resultSet;
						}
						//}
					}
				    case VERSION:
					{
						//Log.d(TAG, " query for Version !!!");
							//synchronized (this)
							//{
							//	if (mReadRecordingsRemindersDBHandle == null)
								//{
							
									//mReadRecordingsRemindersDBHandle=	DataStrore.getInstance(getContext()).getReadableDatabase();
							///	}
								
								resultSet = mReadRecordingsRemindersDBHandle.query(tableName, projection, 
										selection, selectionArgs, null, null, sortOrder);
			                       return resultSet;
							//} 
						
					}
				    case PARENT_VERSION:
					{
						//Log.d(TAG, " query for ParentVersion !!!");
							//synchronized (this)
							//{
								//if (mReadRecordingsRemindersDBHandle == null)
								//{
							
									//mReadRecordingsRemindersDBHandle=DataStrore.getInstance(getContext()).getReadableDatabase();
							//	}
								
								resultSet = mReadRecordingsRemindersDBHandle.query(tableName, projection, 
										selection, selectionArgs, null, null, sortOrder);
			                       return resultSet;
							//} 
						
					}
					case MAJOR_MINOR_VERSION:
				    {
				    	Log.d(TAG, "Query for major/minor Version !!!"+tableName);
				    	resultSet = mReadRecordingsRemindersDBHandle.query(tableName, projection, 
								selection, selectionArgs, null, null, sortOrder);
	                       return resultSet;
				    			
				    }
					case RECORDING_REMINDER_VIEW:
					    try
				        {
				        	//Log.d(TAG,"view called");
				    	    resultSet = mReadRecordingsRemindersDBHandle.query(DataStore.REC_REM_VIEW, projection, 
								selection, selectionArgs, null, null, sortOrder);
				        }
				        catch(Exception e)
				        {
				        	Log.d(TAG,"query():Excepton "+e);
				        }				    	
				    	return resultSet;
				    case REMINDERS:
					{
						//Log.d(TAG, " query for Reminders Table !!!");
						//synchronized (this)
						//{
							//if (mReadRecordingsRemindersDBHandle == null)
							//{
								//mReadRecordingsRemindersDBHandle=DataStrore.getInstance(getContext()).getReadableDatabase();
							//}
							
							resultSet = mReadRecordingsRemindersDBHandle.query(tableName, projection, 
									selection, selectionArgs, null, null, sortOrder);
		                       return resultSet;
						//}				
					}
					case SEARCH_SUGGESTION:
					{
						Log.d(TAG, "SEARCH_SUGGESTION query !!!->"+selectionArgs[0]);
						return getSuggestions(selectionArgs[0]);
					}
					case TUNER_ONE_RECORDINGS:
						//Log.d(TAG, "TUNER_ONE query !!!");
						if(selection != null ) {
							Log.e(TAG, "unsupported selection for tuner_one rec" + selection);
							return null;
						}
						if(!Arrays.equals(projection, IRecordingsContract.GET_RECORDINGS_DEFAULT_PROJECTIONS)) {
							Log.e(TAG, "unsupported projection for tuner_one rec ");
							return null;
						}
						if(recAllocation != null) {
							boolean limitone = false;
							if( (sortOrder != null) && (sortOrder.contains("LIMIT 1")) ) {
								limitone = true;
							}
							return recAllocation.getScheduleRecordings(IRecordingsAllocation.TUNER_ONE, limitone);
						}
						break;
					case TUNER_TWO_RECORDINGS:
						//Log.d(TAG, "TUNER_TWO query !!!");
						if(selection != null ) {
							Log.e(TAG, "unsupported selection for tuner_two rec" + selection);
							return null;
						}
						if(!Arrays.equals(projection, IRecordingsContract.GET_RECORDINGS_DEFAULT_PROJECTIONS)) {
							Log.e(TAG, "unsupported projection for tuner_two rec ");
							return null;
						}
						if(recAllocation != null) {
							boolean limitone = false;
							if( (sortOrder != null) && (sortOrder.contains("LIMIT 1")) ) {
								limitone = true;
							}
							return recAllocation.getScheduleRecordings(IRecordingsAllocation.TUNER_TWO, limitone);
						}
						break;
					case CONFLICTING_RECORDINGS:
						Log.d(TAG, "CONFLICTING_RECORDINGS query !!!");
						int recordingID;
						long est;
						long eet;
						int channelid;
						if(!selection.equals(IRecordingsContract.CONFLICTING_RECORDINGS_SELECTION)) {
							Log.e(TAG, "unsupported selection for conflicts " + selection);
							return null;
						}
						if(sortOrder != null) {
							Log.e(TAG, "unsupported sort order for conflicts " + sortOrder);
							return null;
						}
						if(!Arrays.equals(projection, IRecordingsContract.GET_CONFLICTS_PROJECTIONS)) {
							Log.e(TAG, "unsupported projection for conflicts ");
							return null;
						}
						try {
							recordingID = Integer.parseInt(selectionArgs[0]);
							est = Long.parseLong(selectionArgs[1]);
							eet = Long.parseLong(selectionArgs[2]);
							channelid	 = Integer.parseInt(selectionArgs[3]);
						} catch (Exception e) {
							Log.e(TAG, "selection arguments not proper " + e.toString());
							return null;
						}
						//TODO : Add from Helper
						Uri mUri = TvContract.buildChannelUri(channelid);
						UriData mdata=TvURIHelper.parseUri(getContext(), mUri);
//						String medium = TvURIHelper.getChannelNumber(getContext(), channelid, resBundle);
						if(mdata.medium == TvURI.Medium.MEDIUM_SATELLITE.value) {
							mdata.medium = IRecordingsAllocation.MEDIUM_SATELLITE;
						} else if(mdata.medium == TvURI.Medium.MEDIUM_TERRESTRIAL.value) {
							mdata.medium = IRecordingsAllocation.MEDIUM_ANTENNA;
						} else if(mdata.medium == TvURI.Medium.MEDIUM_CABLE.value) {
							mdata.medium = IRecordingsAllocation.MEDIUM_CABLE;
						} else {
							Log.e(TAG, "channel id not corresponding to known medium ");
							return null;
						}
						Recordings value = new Recordings(est, eet, recordingID, mdata.medium, null);
						if(recAllocation != null) {
							return recAllocation.getConflictingRecordings(value);
						}
						break;
					default:
					{
						Log.d(TAG, "No Match found for Query !!!");
					}
		
				} 
			  }
			     	  catch (Exception e) {
			     	  Log.d(TAG,""+e);
		     	  }
			return null;
	}
	
	private static void createReadRecordingsRemindersDBHandle(Context mContext){
		mReadRecordingsRemindersDBHandle =	DataStore.getInstance(mContext).getReadableDatabase();
	}

	private Cursor getMaxVersionRecord(Uri uri) {

		String tbl = extractTbleName(uri);// select max(Version) from recording

		String sqlStatement = "Select MAX(" + IRecordingsContract.C_VERSION
				+ ") from " + tbl;

		Log.d(TAG, "Statemetn to find Max version Number:" + sqlStatement);

		//Cursor cursor = DataStrore.getInstance(getContext())
			//	.getReadableDatabase().rawQuery(sqlStatement, null);
		if(mReadRecordingsRemindersDBHandle==null)
		{
			mReadRecordingsRemindersDBHandle=DataStore.getInstance(getContext()).getReadableDatabase();
		}
		Cursor cursor =mReadRecordingsRemindersDBHandle.rawQuery(sqlStatement, null);
		
		return cursor;
	}

	public int update(Uri uri, ContentValues values, String selection,String[] selectionArgs) {
		int effectedRecords = -1;
		Uri notificationUri = null;
		String changeId = null;
		int pid = Binder.getCallingPid();
		
		try
		{
			//Log.d(TAG, "Update Query with epg record/reminder provider !!!");
		if(uri!=null)
		{
			String tableName = uri.getLastPathSegment();
			Log.d(" Table Name Received for the Operation is:", tableName);

		   // Check if Change ID is present and remove it
		   if ((values != null) && (values.containsKey(IRemindersContract.C_CHANGE_ID))) {
			   changeId = values.getAsString(IRemindersContract.C_CHANGE_ID);
				  
			   values.remove(IRemindersContract.C_CHANGE_ID);
		   }
			
			if (tableName.equalsIgnoreCase(IRecordingsContract.RECORDINGS_TABLE))
			{
				synchronized (this)
				{
				   ItblHandler ItableHandlerInstance = getTableInstance(uri);

				   if (ItableHandlerInstance != null) 
				   {
					    Log.d(TAG, "Update Query for Recording Table selection statement="+selection );
						
					    if(selectionArgs != null)
							Log.d(TAG, "selection args "+Arrays.toString(selectionArgs));
												
						effectedRecords = (ItableHandlerInstance.updateRecord(
							DataStore.getInstance(getContext()), values, selection,
							selectionArgs, (++currentVersion)));
						
						
						
					/*	if ((values != null) && (values.containsKey(IRecordingsContract.C_RECORDING_TYPE)))
						{
							int recordingType = values.getAsInteger(IRecordingsContract.C_RECORDING_TYPE);
							int recordingId = Integer.parseInt(selectionArgs[0]);
							if(IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal() == recordingType)
							{
								Log.d(TAG,"Recording started, locking the node "+recordingId);
								recManagerRef.lockRecordingHead(recordingId);
							}
							else if( (IRecordingsContract.RecordingType.RECORDING_SCHEDULED.ordinal() != recordingType ) &&
									 (IRecordingsContract.RecordingType.RECORDING_MANUAL.ordinal() != recordingType ) &&
									 (IRecordingsContract.RecordingType.RECORDING_OTR.ordinal() != recordingType ) &&
									 (IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal() != recordingType)
									)
									{
										recManagerRef.deleteRecordinghead(recordingId);
									}


								
						}*/
									
						

					    if ((effectedRecords>0) && (values.containsKey(IRecordingsContract.C_RECORDING_NAME) || 
					    		values.containsKey(IRecordingsContract.C_RECORDING_TYPE) ||
					    		values.containsKey(IRecordingsContract.C_STARTTIME) || 
					    		values.containsKey(IRecordingsContract.C_DURATION) ||
					    		values.containsKey(IRecordingsContract.C_MARGIN_START) ||
					    		values.containsKey(IRecordingsContract.C_MARGIN_END) ||
					    		values.containsKey(IRecordingsContract.C_AUTO_MARGIN_START) ||
					    		values.containsKey(IRecordingsContract.C_AUTO_MARGIN_END))) {
 							mRecordingMajorVersion++;
 					    } else {
 							mRecordingMinorVersion++;
 					    }
					    Log.d(TAG, "Update Query for Recording Table major minor now is mRecordingMajorVersion :"+mRecordingMajorVersion +" mRecordingMinorVersion:" + mRecordingMinorVersion);
				   }
				}
			}
			else if (tableName.equalsIgnoreCase(IRecordingsContract.ParentVersion))
			{
				synchronized (this)
				{
				   ItblHandler ItableHandlerInstance = getTableInstance(uri);

				   if (ItableHandlerInstance != null) {
					   Log.d(TAG, "Update Query for ParentVersion Table");

					    effectedRecords = (ItableHandlerInstance.updateRecord(
							DataStore.getInstance(getContext()), values, selection,
							selectionArgs, (currentVersion)));
							
						return effectedRecords;
				   }
				}
			}
			else if (tableName.equalsIgnoreCase(IRecordingsContract.Version))
			{
				synchronized (this)	{
					
				   ItblHandler ItableHandlerInstance = getTableInstance(uri);

				   if (ItableHandlerInstance != null) {
					   //Log.d(TAG, "Update Query for Version Table");

					   effectedRecords = (ItableHandlerInstance.updateRecord(
							DataStore.getInstance(getContext()), values, selection,
							selectionArgs, (currentVersion)));
							
						return effectedRecords;
				   }
				}
			} else if(tableName.equalsIgnoreCase(IRemindersContract.REMINDERS_TABLE)) {
				
				synchronized (this)	{
				   if (recordingsremindersDBHandle == null) {
					   recordingsremindersDBHandle = DataStore.getInstance(getContext()).getWritableDatabase();
				   }
				   Log.d(TAG, "Update Query for Reminders Table");
				   effectedRecords = recordingsremindersDBHandle.update(tableName, values, selection, selectionArgs);
				}
			}
		
			//  Notify if records updated
 			if (effectedRecords > 0) {
 				
 				String projStr = contentValuesToProjString(values);
 				notificationUri = Uri.parse(uri+"/"+projStr);
 				Uri.Builder builder = notificationUri.buildUpon();
 				builder.appendQueryParameter(IRemindersContract.C_CALLING_PROCESS_ID, ""+pid);
 				builder.appendQueryParameter(IRecordingsContract.C_OPERATIONTYPE,IRecordingsContract.C_OPERATIONTYPE_UPDATE);

 				// Add change id to notification
 				if (changeId != null) {
 					builder.appendQueryParameter(IRemindersContract.C_CHANGE_ID, changeId);
 				}
 				
				builder.appendQueryParameter(IRecordingsContract.C_VERSION,  String.valueOf(currentVersion));
				synchronized (this)	{
 				builder.appendQueryParameter(IChannelContract.C_MAJOR_VERSION,String.valueOf(mRecordingMajorVersion));
 				builder.appendQueryParameter(IChannelContract.C_MINOR_VERSION,String.valueOf(mRecordingMinorVersion));
				}
 				notificationUri = builder.build();
 				updateMajorMinorRecordingVersions();
 				getContext().getContentResolver().notifyChange(notificationUri, null);
 			}
		}
		
	}
		catch(Exception e)
		{
		Log.d(TAG,"Exception in updating="+e);
		}
		return effectedRecords;
		}
	
	private MatrixCursor getSuggestions(String selection) 
	{
		
		MatrixCursor matrix = new MatrixCursor(SearchCursorSchema);
		Log.d(TAG,"getSuggestions(): called");
		String selectArg = selection + "%";
		
		String mQuery = "SELECT "+RecordingsSearchProj + " FROM " + IRecordingsContract.RECORDINGS_TABLE + " WHERE " 
				+ IRecordingsContract.C_RECORDING_NAME + " LIKE '" + selectArg + "' ORDER BY "+IRecordingsContract.C_RECORDING_ID+" ASC LIMIT 5";

		Cursor mCursor=null;
		try 
		{
			Log.d(TAG, "Search query is : " + mQuery);
			
			mCursor = mReadRecordingsRemindersDBHandle.rawQuery(mQuery, null);
			
			if(mCursor!=null && mCursor.moveToNext())
			{
			   
				   do
				   {
					   long mChannelId=Integer.parseInt( mCursor.getString(0));
					   Uri mLogoUri=TvContract.buildChannelLogoUri(mChannelId);
					   long mRecordingId=mCursor.getLong(1);
					   Uri mRecUri=RecordingUri.buildRecordingUri(mRecordingId);
					   Log.d(TAG,"logo uri "+mLogoUri+" and mRecUri:"+mRecUri);
					   long duration=(mCursor.getLong(4))*1000;
					   Log.d(TAG,"duration:"+duration);
					   matrix.addRow(new Object[] {mCursor.getString(mCursor.getColumnIndex(IRecordingsContract.C_RECORDING_NAME)),
					   mCursor.getString(3),mLogoUri.toString(),duration,mCursor.getString(5),mRecUri});		
				      }while(mCursor.moveToNext());
			
				
			}
			
		} catch (Exception e) {
			
			Log.d(TAG,"Exception in Search Suggestion"+e);
		}
		finally
	    {
		          if(mCursor!=null)
				  {
					  mCursor.close();
					  mCursor=null;
				  }
		}
		
		return matrix;
	}
	
	private static void setDBHandle(SQLiteDatabase dbHandle) {
		recordingsremindersDBHandle=dbHandle;
	}
	private static void setReadDBHandle(SQLiteDatabase dbHandle) {
		mReadRecordingsRemindersDBHandle=dbHandle;
	}
	private static void setCurrentVersion(int version) {
		currentVersion=version;
	}

	public static void setParentVersion(int version) {
		parentVersion = version;
	}
	
	private void updateMajorMinorRecordingVersions() {
		
		synchronized (this) {
			
			ItblHandler ItableHandlerInstance =  (ItblHandler) new MajorMinorTbl();
			ContentValues updateValues = new ContentValues();
			Log.d(TAG,"Upadting the major minor version major is "+mRecordingMajorVersion +" minor is "+mRecordingMinorVersion);
			updateValues.put(IChannelContract.C_MAJOR_VERSION, mRecordingMajorVersion);
			updateValues.put(IChannelContract.C_MINOR_VERSION, mRecordingMinorVersion);

			int result = ItableHandlerInstance.updateRecord(DataStore.getInstance(getContext()), 
					updateValues, null,	null, -1);
			Log.d(TAG, "major version update result "+result);

			ItableHandlerInstance = null;
			updateValues = null;
		}
	}
	
	private void readMajorMinorVersion() {
		synchronized (this) {

			IQueryHandler ItableHandlerInstance = (IQueryHandler) new MajorMinorTbl();

			Cursor c = ItableHandlerInstance.query(DataStore.getInstance(getContext()), 
					Mjr_Mnr_Ver_Tbl, null, null, null);

			try
			{
			    if(c!= null && c.getCount() >= 1) {
              
			        c.moveToFirst();
			        mRecordingMajorVersion = c.getInt(c.getColumnIndex(IChannelContract.C_MAJOR_VERSION));
			        mRecordingMinorVersion = c.getInt(c.getColumnIndex(IChannelContract.C_MINOR_VERSION));
			        Log.d(TAG, "after updation the major and minor versions are "+mRecordingMajorVersion + "," +mRecordingMinorVersion);

			    } else {

			       Log.d(TAG, mRecordingMajorVersion + "::" +mRecordingMinorVersion);
			     }
			}
			finally
			{
				if(c!=null)
				{
					c.close();
					c=null;
				}
				
			}
		}
	}

	private String contentValuesToProjString (ContentValues val) {
	    	String projStr = "";
	    	StringBuffer projStrToBuffer=new StringBuffer();//added
	    	Set<String> strSet = null;
	    	
	    	if (val == null) {
	    		return projStr;
	    	}
	    	strSet = val.keySet();
	    	// Convert to comma separated string 
	    	for (String Item : strSet) {
	    		projStrToBuffer.append(Item.toString()).append(",");//added
	    		//projStr += Item.toString()+",";
	    	}
	    	projStr=projStrToBuffer.toString();
	    	// Remove the last comma
	    	int len = projStr.length();
	    	if (len > 0) {
	    		projStr = projStr.substring(0, len - 1);
	    	}
	    	return projStr;
    }

    @Override
    public void onRecordingHeadChanged(int tuner,RecordData value) {
		getContext().getContentResolver().notifyChange(IRecordingsContract.CONTENT_URI_TunerTwo, null);
    }
}

