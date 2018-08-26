package org.droidtv.tunerservice.db;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;

import android.util.Log;

public class CamInfoDB {

	private static CamInfoDB mCamInfoDB;
	private CAMSQLiteHelper mCamsqLiteHelper;
	private static Context mContext;
	private SQLiteDatabase database;
	/*
	 * cam status 1 means true , 0 means false
	 */
	private static final int CAMSTATUS = 1;
	private String TAG = CamInfoDB.class.getSimpleName();

	private CamInfoDB() {
		if(mCamsqLiteHelper == null){
			mCamsqLiteHelper = new CAMSQLiteHelper(mContext);			
		}
	}

	public static CamInfoDB getInstace(Context context) {
		mContext = context;
		synchronized (CamInfoDB.class) {
			if (mCamInfoDB == null) {
				mCamInfoDB = new CamInfoDB();
			}
			
		}
		return mCamInfoDB;
	}

	public void open() throws SQLException {
		synchronized (this) {
			Log.i(TAG,"open called:"+mCamsqLiteHelper);

			database = mCamsqLiteHelper.getWritableDatabase();
		}
	}

	public void close() {
		//mCamsqLiteHelper.close();
	}
	
	/*
	 * Insert CAM Details 
	 * @Params CAMDetails camDetails
	 * @Returns int insertid 
	 */
	public long addCam(CAMDetails camDetails){
	
	try{
			synchronized (this) {
		database = mCamsqLiteHelper.getWritableDatabase();
		
			ContentValues contentValues = new ContentValues();
			contentValues.put(CAMSQLiteHelper.COLUMN_SLOTID,camDetails.getSlotID());
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMID,camDetails.getCamID());
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMIDBLOB,camDetails.getCamIDBlob());
			contentValues.put(CAMSQLiteHelper.COLUMN_MEDIUAM,camDetails.getMedium());
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMSTATUS,camDetails.isCamStatus());
			long insertID = database.insert(CAMSQLiteHelper.TABLE_CAMDETAILS, null, contentValues);
			Log.i(TAG,"addCam :"+insertID);
			return insertID;
			}
		}
		catch(SQLiteException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return 0;
	}
	
	
	public boolean getCamStatus(CAMDetails camDetails){
		
		try{
			synchronized (this) {
			database = mCamsqLiteHelper.getWritableDatabase(); 
			String selectQuery = null;
			
				selectQuery = "SELECT  count(*) FROM "+ CAMSQLiteHelper.TABLE_CAMDETAILS +" where "+CAMSQLiteHelper.COLUMN_SLOTID+" = "+ camDetails.getSlotID()  +" and "+ CAMSQLiteHelper.COLUMN_CAMSTATUS +"="+"'"+CAMSTATUS+"'";
				if(selectQuery != null){
					Log.i(TAG, "getCamStatus() compiled statement:"+database.compileStatement(selectQuery));
					Cursor cursor = database.rawQuery(selectQuery,null);
					if(cursor != null ){
						if(cursor.moveToFirst()){
							int camCount = cursor.getInt(0);
							cursor.close();
							Log.i(TAG, "getCamStatus() camcount :"+camCount); 
							if(camCount == 0){
								return false;
							}
							else{
								return true;
							}
						} 
						cursor.close();
					 }
				}
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return false;
		
	}
	
	/*
	 * Updating CAM Details 
	 * @Params CAMDetails camDetails
	 * @Returns int updateID 
	 */
	public int updateCam(CAMDetails camDetails){
	try{
			synchronized (this) {
		database = mCamsqLiteHelper.getWritableDatabase();
		
			Log.i(TAG,"updateCam:camstatus->"+camDetails.isCamStatus()+"medium:"+camDetails.getMedium()+"getCamID:"+camDetails.getCamID()+"slotID:"+camDetails.getSlotID());
			ContentValues contentValues = new ContentValues();
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMID, camDetails.getCamID());
			contentValues.put(CAMSQLiteHelper.COLUMN_MEDIUAM, camDetails.getMedium());
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMSTATUS, camDetails.isCamStatus());
			int updateID = database.update(CAMSQLiteHelper.TABLE_CAMDETAILS, contentValues,CAMSQLiteHelper.COLUMN_SLOTID +"="+camDetails.getSlotID(), null);
			Log.i(TAG,"updateCam updateID:"+updateID);
			return updateID;
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return 0;
		}

	
	/*
	 * Updating camstatus while removing the cam
	 * @Params CAMDetails camDetails
	 * @Returns int 
	 */
	public int updateCamStatus(CAMDetails camDetails){
	try{
			synchronized (this) {
		database = mCamsqLiteHelper.getWritableDatabase();
		
			/*
			 * Columns to update
			 */
			Log.i(TAG,"updateCamStatus:camstatus->"+camDetails.isCamStatus());
			ContentValues contentValues = new ContentValues();
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMSTATUS, camDetails.isCamStatus());
			int updateID = database.update(CAMSQLiteHelper.TABLE_CAMDETAILS, contentValues,CAMSQLiteHelper.COLUMN_SLOTID +"="+camDetails.getSlotID(), null);
			Log.i(TAG,"updateCamStatus updateID:"+updateID);
			return updateID;
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return 0;
	}
	
	/*
	 * Updating camstatus while removing the cam
	 * @Params CAMDetails camDetails
	 * @Returns int 
	 */
	public int updateBothCamSStatus(CAMDetails camDetails){
	try{
			synchronized (this) {
		database = mCamsqLiteHelper.getWritableDatabase();
		
			/*
			 * Columns to update
			 */
			Log.i(TAG,"updateBothCamSStatus:camstatus->"+camDetails.isCamStatus());
			ContentValues contentValues = new ContentValues();
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMSTATUS, camDetails.isCamStatus());
			int updateID = database.update(CAMSQLiteHelper.TABLE_CAMDETAILS, contentValues,null, null);
			Log.i(TAG,"updateBothCamSStatus updateID:"+updateID);
			return updateID;
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return 0;
	}
	
	
	/*
	 * Retrieve the CAM Medium corresponding to slotID
	 * @Params CAMDetails camDetails
	 * @Returns String medium
	 */
	public String getMedium(CAMDetails camDetails){
	try{
			synchronized (this) {
				database = mCamsqLiteHelper.getWritableDatabase();
			
				/*
				 * Columns to retrieve
				 */
				String columns[] = {CAMSQLiteHelper.COLUMN_MEDIUAM};
				Cursor cursor = database.query(CAMSQLiteHelper.TABLE_CAMDETAILS,columns , CAMSQLiteHelper.COLUMN_SLOTID +" = "+camDetails.getSlotID(), null, null, null, null);
				if(cursor != null){
					if(cursor.moveToFirst()){
						/*
						 * Getting CAM Medium
						 */
						String medium = cursor.getString(cursor.getColumnIndex(CAMSQLiteHelper.COLUMN_MEDIUAM));
						Log.i(TAG,"getMedium cursor length:"+cursor.getCount());
						cursor.close();
						Log.i(TAG,"getMedium() medium:"+medium);
						return medium;
					}
					cursor.close();
				}  	
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return null; 
	}

	
	/*
	 * Updating CAM Medium corresponding to the slotID
	 * @Params CAMDetails camDetails
	 * @Returns int updatedcount 
	 */
	public int updateMedium(CAMDetails camDetails){
	try{
			synchronized (this) {
		database = mCamsqLiteHelper.getWritableDatabase();
		
			Log.i(TAG,"updateMedium:medium->"+camDetails.getMedium());
			ContentValues contentValues = new ContentValues();
			contentValues.put(CAMSQLiteHelper.COLUMN_MEDIUAM, camDetails.getMedium());
			CAMDetails CAMDetails1 = new CAMDetails();
			CAMDetails1.setMedium(CAMDetails.UNKNOWNMEDIUM);//TODO:TIF
			int noOfCams = getNoOfCAMS(CAMDetails1);
			Log.i(TAG,"updateMedium:noOfCams->"+noOfCams);
			if(noOfCams == 1){
				int updateID = database.update(CAMSQLiteHelper.TABLE_CAMDETAILS, contentValues,CAMSQLiteHelper.COLUMN_SLOTID +"="+camDetails.getSlotID(), null);
				Log.i(TAG,"updated Medium for single CAM:"+updateID);
				return updateID;
			} else if(noOfCams == 2){
				int updateID = database.update(CAMSQLiteHelper.TABLE_CAMDETAILS, contentValues,null, null);
				Log.i(TAG,"updated Medium for Both the CAMs:"+updateID);
				return updateID;
			}
		 }
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return 0;
	}
	
	
	
	
	/*
	 * Retrieve CAMID based on the SLOTID
	 * @Params CAMDetails camDetails
	 * @Returns long camID
	 */
	public String getCamId(CAMDetails camDetails){
	try{
			synchronized (this) {
			database = mCamsqLiteHelper.getWritableDatabase();
			
				/*
				 * Columns to retrieve
				 */
				String columns[] = {CAMSQLiteHelper.COLUMN_CAMID};
				Cursor cursor = database.query(CAMSQLiteHelper.TABLE_CAMDETAILS,columns , CAMSQLiteHelper.COLUMN_SLOTID +" = "+camDetails.getSlotID(), null, null, null, null);
				if(cursor != null){
					if(cursor.moveToFirst()){
						/*
						 * Getting CAMID
						 */
						String camID = cursor.getString(cursor.getColumnIndex(CAMSQLiteHelper.COLUMN_CAMID));
						Log.i(TAG,"cursor length:"+cursor.getCount());
						cursor.close();
						Log.i(TAG,"getCamId():"+camID);
						return camID;
					}
					cursor.close();
				}	
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return null; 
	}
	
	/*
	 * Updating camid for the corresponding slotID
	 * @Params CAMDetails camDetails
	 * @Returns int updateID
	 */
	public int updateCamID(CAMDetails camDetails){
	try{
			synchronized (this) {
		database = mCamsqLiteHelper.getWritableDatabase();
			/*
			 * Columns to update
			 */
			Log.i(TAG,"updateCamID:camID"+camDetails.getCamID()+"camsTatus:"+camDetails.isCamStatus());
			ContentValues contentValues = new ContentValues();
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMID, camDetails.getCamID());
			contentValues.put(CAMSQLiteHelper.COLUMN_CAMSTATUS, camDetails.isCamStatus());
			int updateID = database.update(CAMSQLiteHelper.TABLE_CAMDETAILS, contentValues,CAMSQLiteHelper.COLUMN_SLOTID +"="+camDetails.getSlotID(), null);
			Log.i(TAG,"updateCamID updateID:"+updateID);
			return updateID;
		 }
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return 0;
	}
	
	public byte[] getCamIdBlob(CAMDetails camDetails){
	try{
			synchronized (this) {
				database = mCamsqLiteHelper.getWritableDatabase();
				/*
				 * Columns to retrieve
				 */
				String columns[] = {CAMSQLiteHelper.COLUMN_CAMIDBLOB};
				Cursor cursor = database.query(CAMSQLiteHelper.TABLE_CAMDETAILS,columns , CAMSQLiteHelper.COLUMN_SLOTID +" = "+camDetails.getSlotID(), null, null, null, null);
				if(cursor != null){
					if(cursor.moveToFirst()){
						/*
						 * Getting CAMID
						 */
						byte[] camID = cursor.getBlob(cursor.getColumnIndex(CAMSQLiteHelper.COLUMN_CAMIDBLOB));
						Log.i(TAG,"cursor length:"+cursor.getCount() +"byte array:"+camID.length);
						cursor.close();
						return camID;
					}
					cursor.close();
				}
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return null; 
	}
	
	
	/*
	 * Retrieve the number of presented currently
	 * @Params CAMDetails camDetails
	 * @Returns int numberOfCams
	 */
	public int getNoOfCAMS(CAMDetails camDetails){
	try{
			synchronized (this) {
			database = mCamsqLiteHelper.getWritableDatabase();
			String selectQuery = null;
			
				if(camDetails.getMedium() .equalsIgnoreCase(CAMDetails.UNKNOWNMEDIUM)){
					selectQuery = "SELECT  count(*) FROM "+ CAMSQLiteHelper.TABLE_CAMDETAILS +" where "+CAMSQLiteHelper.COLUMN_CAMSTATUS+" = "+ CAMSTATUS +" and ("+CAMSQLiteHelper.COLUMN_MEDIUAM +"="+"'"+CAMDetails.UNKNOWNMEDIUM+"'"+" or "+ CAMSQLiteHelper.COLUMN_MEDIUAM +"="+"'"+CAMDetails.TCINSTALLMEDIUM+"'"+" or "+ CAMSQLiteHelper.COLUMN_MEDIUAM +"="+"'"+CAMDetails.SATINSTALLMEDIUM +"')";
				}else if(camDetails.getMedium() .equalsIgnoreCase(CAMDetails.TCINSTALLMEDIUM)){
				selectQuery = "SELECT  count(*) FROM "+ CAMSQLiteHelper.TABLE_CAMDETAILS +" where "+CAMSQLiteHelper.COLUMN_CAMSTATUS+" = "+ CAMSTATUS +" and "+ CAMSQLiteHelper.COLUMN_MEDIUAM +"="+"'"+CAMDetails.TCINSTALLMEDIUM+"'";
				} else if(camDetails.getMedium() .equalsIgnoreCase(CAMDetails.SATINSTALLMEDIUM)){
					selectQuery = "SELECT  count(*) FROM "+ CAMSQLiteHelper.TABLE_CAMDETAILS +" where "+CAMSQLiteHelper.COLUMN_CAMSTATUS+" = "+ CAMSTATUS +" and "+ CAMSQLiteHelper.COLUMN_MEDIUAM +"="+"'"+CAMDetails.SATINSTALLMEDIUM+"'";
				}
				if(selectQuery != null){
					Log.i(TAG, "getNoOfCAMS compiled statement:"+database.compileStatement(selectQuery));
					Cursor cursor = database.rawQuery(selectQuery,null);
					if(cursor != null){
						if(cursor.moveToFirst()){
						int camCount = cursor.getInt(0);
						cursor.close();
						Log.i(TAG, "getNoOfCAMS camcount :"+camCount); 
						return camCount;
						}
						cursor.close();
					}
				}
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return 0;
	}
	
	/*
	 * Checking the slotid is existed or not
	 */
	public boolean isSlotIDExisted(CAMDetails camDetails){
	
	try{
			synchronized (this) {
				database = mCamsqLiteHelper.getWritableDatabase();
				String selectQuery = null;
					selectQuery = "SELECT  count(*) FROM "+ CAMSQLiteHelper.TABLE_CAMDETAILS +" where "+CAMSQLiteHelper.COLUMN_SLOTID+" = "+ camDetails.getSlotID();
					if(selectQuery != null){
						Log.i(TAG, " isSlotIDExisted compiled statement:"+database.compileStatement(selectQuery));
						Cursor cursor = database.rawQuery(selectQuery,null);
						if(cursor != null){
							if(cursor.moveToFirst()){
								int camCount = cursor.getInt(0);
								cursor.close();
								Log.i(TAG, "isSlotIDExisted camcount :"+camCount); 
								if(camCount == 0){
									return false;
								}
								else{
									return true;
								}
							}
							cursor.close();
						 }
					}
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return false;
	}
	
		public void dropCamDetails(){
		try{
		synchronized (this) {
		database = mCamsqLiteHelper.getWritableDatabase();
		Log.d(TAG,"dropCamDetails called:"+database);
	
				 int deletecount = database.delete(CAMSQLiteHelper.TABLE_CAMDETAILS, null, null);
				 Log.i(TAG, "dropCamDetails statement:"+deletecount);
			}
		
		}
		catch(SQLException  sqlException)
		{
				Log.e(TAG ,sqlException.getMessage());
		}
	}
	
	public CAMDetails getCamInfo(CAMDetails camDetails){
		
			try{
			synchronized (this) {
				database = mCamsqLiteHelper.getWritableDatabase();
			
				/*
				 * Columns to retrieve
				 */
				String columns[] = {CAMSQLiteHelper.COLUMN_CAMID,CAMSQLiteHelper.COLUMN_CAMSTATUS,CAMSQLiteHelper.COLUMN_MEDIUAM};
				Cursor cursor = database.query(CAMSQLiteHelper.TABLE_CAMDETAILS,columns , CAMSQLiteHelper.COLUMN_SLOTID +" = "+camDetails.getSlotID(), null, null, null, null);
				if(cursor != null){
					if(cursor.moveToFirst()){
						CAMDetails camInfo = new CAMDetails();
						camInfo.setCamID(cursor.getString(cursor.getColumnIndex(CAMSQLiteHelper.COLUMN_CAMID)));
						camInfo.setCamStatus(((cursor.getInt(cursor.getColumnIndex(CAMSQLiteHelper.COLUMN_CAMSTATUS))) == CAMSTATUS) ? true:false);
						camInfo.setMedium(cursor.getString(cursor.getColumnIndex(CAMSQLiteHelper.COLUMN_MEDIUAM)));
						cursor.close();
						return camInfo;
					} else {
						cursor.close();
					}
				}  	
			}
		}catch(SQLException sqlException){
			Log.e(TAG ,sqlException.getMessage());
		}
		return null;
	}
	
}
