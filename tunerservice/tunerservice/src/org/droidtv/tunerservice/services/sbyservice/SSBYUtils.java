package org.droidtv.tunerservice.services.sbyservice;

import java.util.ArrayList;
import java.util.List;

import org.droidtv.tunerservice.util.TvURIHelper.Medium;

import android.content.Context;
import android.database.Cursor;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.util.Log;

public class SSBYUtils {
	
	private static final String TAG = "SSBYUtils";
	
	public static int getFirstChannel(Context context, Medium m) {
		Log.d(TAG, "getFirstChannel called ");
		
		int _id = -1;
		String[] projection = new String[] { TvContract.Channels._ID,
				 TvContract.Channels.COLUMN_TYPE};
		String typeselection = null;
		List<String> typelist = new ArrayList<String>(); 
		switch(m) {
			case MEDIUM_SATELLITE:
				typeselection = Channels.COLUMN_TYPE + "=? OR " +
						Channels.COLUMN_TYPE + "=?";
				typelist.add(Channels.TYPE_DVB_S);
				typelist.add(Channels.TYPE_DVB_S2);
			break;
			case MEDIUM_CABLE:
				typeselection = Channels.COLUMN_TYPE + "=? OR " +
						Channels.COLUMN_TYPE + "=?";
				typelist.add(Channels.TYPE_DVB_C);
				typelist.add(Channels.TYPE_DVB_C2);
			break;
			default:
				typeselection = Channels.COLUMN_TYPE + "=? OR " +
						Channels.COLUMN_TYPE + "=? OR " +
						Channels.COLUMN_TYPE + "=? OR " +
						Channels.COLUMN_TYPE + "=? OR " +
						Channels.COLUMN_TYPE + "=?";
						
				typelist.add(Channels.TYPE_DVB_T);
				typelist.add(Channels.TYPE_DVB_T2);
				typelist.add(Channels.TYPE_DVB_C);
				typelist.add(Channels.TYPE_DVB_C2);
				typelist.add(Channels.TYPE_PAL);
			break;
		}
		
		String selection = typeselection;
		String [] selectionArgs = typelist.toArray(new String[typelist.size()]);
		String sortorder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
		
		
		Cursor cursor = null;
		
		cursor=context.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, selection, selectionArgs, sortorder);
		
		if(cursor!=null) {
			try
			{
			   if(cursor.getCount()>0) {
				  cursor.moveToFirst();
				  _id = cursor.getInt(0);
			   }
			}
			finally
			{
				cursor.close();
				cursor=null;
			}			
		}
		
		Log.d(TAG,"getFirstChannel returns cid " + _id);
		return _id;
	}
	
	public static boolean isChannelInstalled(Context context, int cid ){
		boolean found = false;
		String[] Projection = new String[] {
				TvContract.Channels._ID,
				TvContract.Channels.COLUMN_DISPLAY_NUMBER,
		};
		
		String selection = TvContract.Channels._ID + "=? ";
		String [] selectionArgs = { Integer.toString(cid) };
		
		Cursor c = context.getContentResolver().query(TvContract.Channels.CONTENT_URI, Projection, selection, selectionArgs, null);
		if(c != null ) {
			if(c.getCount()>0) {
				found = true;
			}
			c.close();
			c=null;
		}
		Log.d(TAG,"for id " + cid + " isChannelInstalled returns " + found);
		return found;
	}
	/*begin:min.jiang add 2016-03-15, for sync time of clock channel*/
	public static int getFirstClockChannel(Context context){
		int _id = -1;
		int _displaynum = 0;
		String[] projection = new String[] { TvContract.Channels._ID,
			                                 TvContract.Channels.COLUMN_DISPLAY_NUMBER};		
		String sortOrder=" CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";		
		String selection = TvContract.Channels.COLUMN_VERSION_NUMBER + " = ? OR " + TvContract.Channels.COLUMN_VERSION_NUMBER + "=? OR " + 
		             TvContract.Channels.COLUMN_VERSION_NUMBER + " = ? OR " + TvContract.Channels.COLUMN_VERSION_NUMBER + "=?";
		String[] selectionArgs = new String[]{"0", "1", "2", "11"};			
		Cursor cursor = context.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, selection, selectionArgs, sortOrder);
		if(cursor != null) {
			try
			{
			   if(cursor.getCount()>0) {
				  cursor.moveToFirst();
				  _id = cursor.getInt(0);
				  _displaynum = cursor.getInt(1);				  
			   }
			}
			finally
			{
				cursor.close();
				cursor=null;
			}	

		}
		Log.d(TAG,"getFirstClockChannel returns cid: " + _id + ", dispalynum: " + _displaynum);

		return _id;
	}	
	/*end:min.jiang add*/
}
