package org.droidtv.tunerservice.util;

import org.droidtv.tv.media.ITvURI;
import org.droidtv.tv.media.ITvURI.Medium;
import org.droidtv.tv.media.ITvURI.SelectionType;
import org.droidtv.tv.media.ITvURI.UriData;
//import org.droidtv.tv.provider.ChannelContract;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.video.ITvVideoManager;
import org.droidtv.tv.tvinput.ITVSessionContext;

import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.ChannelFilterConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.LastSelectedDeviceConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.LastSelectedTunerConstants;

import org.droidtv.tv.provider.IFavoriteContract;
import org.droidtv.tv.provider.IFavoriteContract.IBaseFavoriteColumns;

import org.droidtv.tv.util.IIntKeyValueables;

import android.content.ContentProviderClient;
import android.database.Cursor;
import android.net.Uri;
import android.os.RemoteException;
import android.util.Log;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.content.ContentUris;
import android.media.tv.TvContract;
import android.os.Bundle;
import android.database.DatabaseUtils;
import android.content.Context;

import java.io.IOException;

public class TvMediumHelper {
	public static final String TAG = "MhegService-TvMediumHelper";
	private static ITvSettingsManager mGlobalSetting = null;	
	private static IIntKeyValueables keyvalues;
	
	private static String[] DVBTCS_PROJ = {	
			Channels.COLUMN_DISPLAY_NUMBER,
			Channels._ID,			
			Channels.COLUMN_VERSION_NUMBER,
			Channels.COLUMN_DISPLAY_NAME,			
			Channels.COLUMN_LOCKED,					
			Channels.COLUMN_NETWORK_AFFILIATION,
			Channels.COLUMN_SERVICE_TYPE, 			
			Channels.COLUMN_TYPE,					
			Channels.COLUMN_INTERNAL_PROVIDER_DATA
	};
	
	private static String[] DVBTCS_FAV_PROJ = {	
			Channels.COLUMN_DISPLAY_NUMBER, 
			Channels._ID,
			Channels.COLUMN_VERSION_NUMBER,
			Channels.COLUMN_DISPLAY_NAME,			
			Channels.COLUMN_LOCKED,					
			Channels.COLUMN_NETWORK_AFFILIATION,
			Channels.COLUMN_SERVICE_TYPE, 			
			Channels.COLUMN_TYPE,					
			Channels.COLUMN_INTERNAL_PROVIDER_DATA,	
			IBaseFavoriteColumns.COLUMN_RANK,
			IBaseFavoriteColumns.COLUMN_CHANNEL_ID
	};

	private static final int FAV_LIST_1 = 1;
	private static final int FAV_LIST_2 = 2;
	private static final int FAV_LIST_3 = 3;
	private static final int FAV_LIST_4 = 4;
	private static final int MEDIUM_ANTENNA = 1;
	private static final int MEDIUM_CABLE = 2;
	private static final int MEDIUM_SATELLITE = 3;

	private static Bundle mTCInfo = null;
	private static Context mCtx = null;

	
	private TvMediumHelper(){

		Log.d(TAG,"Constructor");
	}

	public static int getCurrentChannelMediumType(Context ctx)
	{
		mCtx = ctx;
		int cid = getLastSelectedTunercid(0);
		String strCid = Integer.toString(cid);
		Log.d(TAG,"getLastSelectedTunercid="+cid);

		mTCInfo = QueryAllInfo(strCid);
		if(mTCInfo!=null) {
			String mChannelType = mTCInfo.getString("ChannelType");
			Log.d(TAG,"getCurrentChannelMediumType="+mChannelType);
			if(mChannelType.equalsIgnoreCase(Channels.TYPE_DVB_T)) 
            {
				return 0;
			}
			else {
				return 1;
			}
		}
		return -1;
	}

    public static int getLastSelectedTunercid(int device) throws IllegalArgumentException{
        ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
        //switch (device) {
        //    case TvSettingsDefinitions.LastSelectedDeviceConstants.DVBTC:
                return globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC,0,0);
        //    case TvSettingsDefinitions.LastSelectedDeviceConstants.DVBS:
        //        return globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2,0,0);
        //    default:
        //        throw new IllegalArgumentException();
        //}
    }

	private static Uri getContentUri(int medium) {
		Uri uri = TvContract.Channels.CONTENT_URI;
		int lChannelFilter = getChannelFilter();
/*		switch(medium){
		case MEDIUM_ANTENNA:
			
			switch(lChannelFilter){
			case ChannelFilterConstants.FAV_LIST_1:
				uri = IFavoriteContract.ITFavoriteList1.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_2:
				uri = IFavoriteContract.ITFavoriteList2.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_3:
				uri = IFavoriteContract.ITFavoriteList3.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_4:
				uri = IFavoriteContract.ITFavoriteList4.CONTENT_URI;
				break;	
			}
			break;
			
		case MEDIUM_CABLE:
			
			switch(lChannelFilter){
			case ChannelFilterConstants.FAV_LIST_1:
				uri = IFavoriteContract.ICFavoriteList1.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_2:
				uri = IFavoriteContract.ICFavoriteList2.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_3:
				uri = IFavoriteContract.ICFavoriteList3.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_4:
				uri = IFavoriteContract.ICFavoriteList4.CONTENT_URI;
				break;	
			}
			break;
			
		case MEDIUM_SATELLITE:
			
			switch(lChannelFilter){
			case ChannelFilterConstants.FAV_LIST_1:
				uri = IFavoriteContract.ISATFavoriteList1.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_2:
				uri = IFavoriteContract.ISATFavoriteList2.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_3:
				uri = IFavoriteContract.ISATFavoriteList3.CONTENT_URI;
				break;
			case ChannelFilterConstants.FAV_LIST_4:
				uri = IFavoriteContract.ISATFavoriteList4.CONTENT_URI;
				break;	
			}
			break;	
		}*/
		Log.d(TAG, "getContentUri returned uri " + uri);
		return uri;
	}

	private static void fetchBlobDataTC(Bundle mTCInfo, byte[] blobData)
	{
		Log.d(TAG, "fetchBlobDataTC Bundle: "+mTCInfo);
		keyvalues = IIntKeyValueables.Instance.getInterface();
		try{
			keyvalues.setBlob(blobData);
		}catch(IOException e){
			Log.d(TAG, "parseBlobData - CAUGHT EXCEPTION keyvalues=null");
			keyvalues = null;
		}catch(ClassNotFoundException e){
			Log.d(TAG, "parseBlobData - CAUGHT EXCEPTION keyvalues = null");
			keyvalues = null;
		}
		if(keyvalues != null){
			int freq = keyvalues.getInt(ITvContractExtras.C_FREQUENCY);
			int isScrambled = keyvalues.getInt(ITvContractExtras.C_SCRAMBLED);
			Log.d(TAG, "freq " + freq );
			/*TODO - PresetType for analog channel has to be handled properly*/
			mTCInfo.putInt("PresetType", 0);
			mTCInfo.putInt("Frequency", freq);
			mTCInfo.putInt("Scrambled", isScrambled);
		}else{
			Log.d(TAG, "parseBlobData - keyvalues is null");
		}
		
	}

	private static Bundle ParseTCInfo(Cursor mCursor) {
		Log.d(TAG, "ParseTCInfo Called ..");
		if ((mCursor != null) && (mCursor.getCount() > 0)) {
			mCursor.moveToFirst();
			mTCInfo = new Bundle();
			
			/*if(getChannelFilter() == TvSettingsDefinitions.ChannelFilterConstants.ALL){
				mTCInfo.putInt("ChannelNumber", mCursor.getInt(mCursor.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
				mTCInfo.putInt("UniqueId", mCursor.getInt(mCursor.getColumnIndex(Channels._ID)));
			}else{
				int cid = mCursor.getInt(mCursor.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID));
				//mTCInfo.putInt("ChannelNumber", ChannelFilter.getChannelFilterInstance().getFavNumber(cid));
				mTCInfo.putInt("UniqueId",cid);
			// Needs to be check for favourite number	
			}*/
			mTCInfo.putInt(Channels.COLUMN_VERSION_NUMBER, mCursor.getInt(mCursor.getColumnIndex(Channels.COLUMN_VERSION_NUMBER)));
			mTCInfo.putString("ChannelName", mCursor.getString(mCursor.getColumnIndex(Channels.COLUMN_DISPLAY_NAME)));
			mTCInfo.putInt("Locked",		 mCursor.getInt(mCursor.getColumnIndex(Channels.COLUMN_LOCKED)));
			mTCInfo.putString(Channels.COLUMN_NETWORK_AFFILIATION,		 mCursor.getString(mCursor.getColumnIndex(Channels.COLUMN_NETWORK_AFFILIATION)));
			mTCInfo.putString("ServiceType",mCursor.getString(mCursor.getColumnIndex(Channels.COLUMN_SERVICE_TYPE)));
			mTCInfo.putString("ChannelType",mCursor.getString(mCursor.getColumnIndex(Channels.COLUMN_TYPE)));
			
			byte[] mInternalData = mCursor.getBlob(mCursor.getColumnIndex(Channels.COLUMN_INTERNAL_PROVIDER_DATA));
			fetchBlobDataTC(mTCInfo, mInternalData);
			
		}
		return mTCInfo;
	}


	public static int getChannelFilter(){

		/*if(mGlobalSetting != null){
            int cLastSelectedTuner = mGlobalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
            int cChannelFilterTC  = mGlobalSetting.getInt(TvSettingsConstants.CHANNELFILTERTC, 0, 0);
            int cChannelFilterSat = mGlobalSetting.getInt(TvSettingsConstants.CHANNELFILTERSATELLITE, 0, 0);
            switch(cLastSelectedTuner){
                case TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC:
                    Log.d(TAG , "getChannelFilter DVB-T or DVB-C returns cChannelFilterTC " + cChannelFilterTC);
                    return cChannelFilterTC;
                case TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER:
                    Log.d(TAG , "getChannelFilter DVB-S, returns cChannelFilterSat " + cChannelFilterSat);
                    return cChannelFilterSat;
                default:
                    Log.d(TAG, "Error - Unknown tuner - cLastSelectedTuner" + cLastSelectedTuner);
                    return cChannelFilterTC;
            }
        }
        return -1;*/
        return 0;
    }

	private static String[] getProjection(int filter) {
		String[] cProjection = DVBTCS_PROJ;
		/*switch(filter){
		case ChannelFilterConstants.FAV_LIST_1:
		case ChannelFilterConstants.FAV_LIST_2:
		case ChannelFilterConstants.FAV_LIST_3:
		case ChannelFilterConstants.FAV_LIST_4:
			cProjection = DVBTCS_FAV_PROJ;
			break;
		}*/
		return cProjection;
	}

	private static String getColumnIdString(int filter) {
		String COLUMN_ID = Channels._ID;
		/*switch(filter){
		case ChannelFilterConstants.FAV_LIST_1:
		case ChannelFilterConstants.FAV_LIST_2:
		case ChannelFilterConstants.FAV_LIST_3:
		case ChannelFilterConstants.FAV_LIST_4:
			COLUMN_ID = IBaseFavoriteColumns.COLUMN_CHANNEL_ID;
			break;
		}*/
		Log.d(TAG, "getColumnIdString returns " + COLUMN_ID);
		return COLUMN_ID;
	}
	
	private static Bundle QueryAllInfo(String cid ) {
		Uri mContentURI = getContentUri(MEDIUM_CABLE);
		//int filter = getChannelFilter();
		int filter = 0;
		Context cxt;
		String[] cProjection = getProjection(filter);
		String COLUMN_ID = getColumnIdString(filter);
		
		String cSelection = "( " + TvContract.Channels.COLUMN_TYPE + " = ? OR " 
							+ TvContract.Channels.COLUMN_TYPE + " = ? OR " 
							+ TvContract.Channels.COLUMN_TYPE + " = ? OR " 
							+ TvContract.Channels.COLUMN_TYPE + " = ? OR " 
							+ TvContract.Channels.COLUMN_TYPE + " = ? OR " 
							+ TvContract.Channels.COLUMN_TYPE + " = ? OR " 
							+ TvContract.Channels.COLUMN_TYPE + " = ? ) AND " 
							+ COLUMN_ID + " = ?";
		String [] cSelectionArgs = { TvContract.Channels.TYPE_DVB_T, 
									 TvContract.Channels.TYPE_DVB_T2, 
									 TvContract.Channels.TYPE_DVB_C, 
									 TvContract.Channels.TYPE_DVB_C2, 
									 TvContract.Channels.TYPE_NTSC, 
									 TvContract.Channels.TYPE_SECAM, 
									 TvContract.Channels.TYPE_PAL, 
									 cid};
		Cursor mCursor = null;

		//getting application context
		
		ContentProviderClient mContentProviderClient = null;

		//if(mContentURI.getAuthority().equalsIgnoreCase(TvContract.AUTHORITY))
		//{
               //mContentProviderClient=PlayTvUtils.getChannelContentProviderClient();
               if (mCtx != null)
               {    try {
	                	//mContentProviderClient = mCtx.getCurrentContext().getMhegService().getContentProviderClient();
	                	mContentProviderClient = mCtx.getContentResolver().acquireContentProviderClient(TvContract.AUTHORITY);
               		} catch (Exception e) {
	               		Log.d(TAG, "getContentProviderClient : Exception : "+e.toString());
               		}
               }
		//}
		//else{
				//mContentProviderClient=PlayTvUtils.getFavoriteContentProviderClient();
		//}
		
		if (mContentProviderClient != null) {
			try {
				mCursor = mContentProviderClient.query(mContentURI, cProjection, cSelection, cSelectionArgs,null);
			} catch (Exception e) {
				Log.d(TAG, "QueryCableInfo : Exception : "+e.toString());
			}
		}
		Log.d(TAG, DatabaseUtils.dumpCursorToString(mCursor));
		try
		{
		   mTCInfo = ParseTCInfo(mCursor);
		}
		finally
		{
			if(mCursor!=null)
				mCursor.close();
			mCursor=null;
		}
		return mTCInfo;
	}	

		
}
