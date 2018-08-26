package org.droidtv.tunerservice.channelfilter;

import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.ChannelFilterConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.InstSettingsInstallMode;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.tv.provider.IFavoriteContract.IBaseFavoriteColumns;
import org.droidtv.tv.provider.IFavoriteContract;
import android.content.ContentUris;
import android.content.Context;
import android.database.Cursor;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

public class ChannelFilter implements IChannelFilter{
	
	private static final String TAG = "ChannelFilterTuner";
	private static ChannelFilter mChannelFilter = null;
	private ITvSettingsManager globalSetting;
	private Context mContext=null;
	private boolean mIsExecutedOnce = false;
	private boolean mIsCursorLoading = false;
	private DatabaseObserver mDBObserver = null;
	public Handler mDBObserverHandler = null;
	private CursorLoaderTask mCursorLoaderTask = null;
	private int mLastSelectedTuner = -1;
	private IIntKeyValueables keyvals;
	private int mLastSelectedCid = -1;
	
	private static final int TC_ALLFILTER 			= 0;
    private static final int TC_DIGITALFILTER 		= 1;
    private static final int TC_RADIOFILTER 		= 2;
    private static final int TC_ANALOGFILTER 		= 3;
    private static final int TC_FREE 				= 4;
    private static final int TC_SCRAMBLED 			= 5;
    
    private static final int SAT_ALL_CHANNELS		= 0;
    private static final int SAT_ALL_TV_CHANNELS 		= 1;
    private static final int SAT_ALL_RADIO_CHANNELS 	= 2;
    private static final int SAT_ALL_FREE_CHANNELS 		= 3;
    private static final int SAT_ALL_SCRAMBLED_CHANNELS = 4;
    private static final int SAT_ALL_SAT1_CHANNELS 		= 5;
    private static final int SAT_ALL_SAT2_CHANNELS 		= 6;
    private static final int SAT_ALL_SAT3_CHANNELS 		= 7;
    private static final int SAT_ALL_SAT4_CHANNELS 		= 8;
    
    private static final int SAT_FAV_CHANNELS 			= 0;
    private static final int SAT_FAV_TV_CHANNELS 		= 1;
    private static final int SAT_FAV_RADIO_CHANNELS 	= 2;
    private static final int SAT_FAV_FREE_CHANNELS 		= 3;
    private static final int SAT_FAV_SCRAMBLED_CHANNELS = 4;
    private static final int SAT_FAV_SAT1_CHANNELS 		= 5;
    private static final int SAT_FAV_SAT2_CHANNELS 		= 6;
    private static final int SAT_FAV_SAT3_CHANNELS 		= 7;
    private static final int SAT_FAV_SAT4_CHANNELS 		= 8;

	/**
	 * Global Variables for Zapbar Filtering
	 */
	private static Cursor mCursor = null;
	private Uri contentUri = Channels.CONTENT_URI;
	private String selection=null;
	private String[] selectionArgs=null;
	private String sortOrder=null;
	
	private final String[] CHANNEL_INFO_PROJ = new String[] {
												Channels.COLUMN_DISPLAY_NUMBER,
												Channels._ID,
												Channels.COLUMN_BROWSABLE
												};
	
	private final String[] CHANNEL_INFO_FAV_PROJ = new String[] {
												IBaseFavoriteColumns.COLUMN_RANK,
												Channels.COLUMN_DISPLAY_NUMBER,
												Channels._ID,
												IBaseFavoriteColumns.COLUMN_CHANNEL_ID
												};
												
	private final String[] CHANNEL_INFO_DVBS_PROJ = new String[] {
												Channels.COLUMN_DISPLAY_NUMBER,
												Channels._ID,
												Channels.COLUMN_BROWSABLE
												};	
												
	private final String[] CHANNEL_INFO_DVBS_FAV_PROJ = new String[] {
												IBaseFavoriteColumns.COLUMN_RANK,
												Channels.COLUMN_DISPLAY_NUMBER,
												Channels._ID,
												IBaseFavoriteColumns.COLUMN_CHANNEL_ID
												};
	private String[] CHANNEL_PROJ=null;
	/* Global Setting Register Variables */
	private int [] property;
	private static final int PROPMAX = 9;
	private ITVSettingsManagerCallBack PStorageBinder=null;
	
	private ChannelFilter(Context mContext)
	{
		Log.d(TAG, "ChannelFilter Cunstructor Called ");
		this.mContext = mContext;
		globalSetting = ITvSettingsManager.Instance.getInterface();
		RegisterTvSettingsManager();
		mDBObserverHandler = new Handler();
		mDBObserver =  new DatabaseObserver(mContext, mDBObserverHandler);
		int filter = ChannelUtils.getChannelFilter();
		RegisterFavDbObserver(filter);
		UpdateCursor();
	}
		public int getLastSelectedCid(){
			return mLastSelectedCid;
	}
	
	private void RegisterFavDbObserver(int filter) {
		switch(filter){
		case ChannelFilterConstants.ALL:
			if(mDBObserver != null){
				mDBObserver.UnRegisterDbObserver();
			}
			break;
		case ChannelFilterConstants.FAV_LIST_1:
		case ChannelFilterConstants.FAV_LIST_2:
		case ChannelFilterConstants.FAV_LIST_3:
		case ChannelFilterConstants.FAV_LIST_4:
			if(mDBObserver != null){
				mDBObserver.UnRegisterDbObserver();
				mDBObserver.RegisterDbObserver();
			}
			break;
		default:
			Log.d(TAG, "RegisterFavDbObserver unknown filter " + filter);
			break;
		}
	}
	
	public Bundle getNextChannelInfo(Uri uri){
		Bundle bundle = null;
		int chId = getChannelId(uri);
		if(chId >= 0){
			bundle = getNextChannelData(chId);
		}
		return bundle;
	}
	
	public Bundle getPrevChannelInfo(Uri uri){
		Bundle bundle = null;
		int chId = getChannelId(uri);
		if(chId >= 0){
			bundle = getPrevChannelData(chId);
		}
		return bundle;
	}
	
	public Bundle getChannelInfo(Uri uri){
		Bundle bundle = null;
		int chId = getChannelId(uri);
		if(chId >= 0){
			bundle = getChannelData(chId);
		}
		return bundle;
	}
	
	public void onPlayCompleted(Uri uri, int presetNumber)
	{
		//Log.d(TAG, "onPlayCompleted  uri " + uri + " presetNumber " + presetNumber);
		mLastSelectedCid = getChannelId(uri);
	}
	
	private int getChannelId(Uri uri){
		int lChNum = -1; 
		if(uri != null){
			String ChNum = uri.getLastPathSegment();
			if(ChNum != null){
				try{
					lChNum = Integer.parseInt(ChNum);
				}catch(NumberFormatException e){
					Log.d(TAG, "getChannelNumber - Caught exception for Uri : " + uri);
					lChNum = -1;
				}
			}
		}
		Log.d(TAG, "getChannelNumber - returning ChannelNum = " + lChNum);
		return lChNum;
	}
	
	public Uri getNextUri(Uri uri){
		int cid =-1;
		try {
			if(uri != null){
				cid = getcid(uri);
			}else{
				cid = mLastSelectedCid;
			}
			Bundle bundle = getNextChannelData(cid);
			int ncid = bundle.getInt("UniqueChannelId");
			return TvContract.buildChannelUri(ncid);
		}catch(Exception e) {
			Log.d(TAG, "getNextUri - exception :"+e.toString());
		}
		return null;
	}
	
	public Uri getPrevUri(Uri uri){
		int cid =-1;
		try {
			if(uri != null){
				cid = getcid(uri);
			}else{
				cid = mLastSelectedCid;
			}
			Bundle bundle = getPrevChannelData(cid);
			int ncid = bundle.getInt("UniqueChannelId");
			return TvContract.buildChannelUri(ncid);
		}catch(Exception e) {
			Log.d(TAG, "getPrevUri - exception :"+e.toString());
		}
		return null;
	}
	
	public int getNextChannelId(int mChannelNumber)
	{
		Log.d(TAG, "getNextChannelId - Channel Number : " + mChannelNumber);
		Cursor c = mCursor;
		int lNextChannelID = 0;
		boolean IFound = false;
		if((c != null) && (c.getCount() > 0)){
			c.moveToFirst();
			do{
				int mChannelNum = Integer.parseInt(c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
				if( mChannelNum > mChannelNumber){
					IFound = true;
					if(ChannelUtils.getChannelFilter() == ChannelFilterConstants.ALL){
						lNextChannelID = Integer.parseInt(c.getString(c.getColumnIndex(Channels._ID)));
					}else{
						lNextChannelID = Integer.parseInt(c.getString(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID)));
					}
					break;
				}
				
			}while(c.moveToNext() == true);
			if(IFound == false){
				Log.d(TAG, "getNextChannelId - not Present For Channel Number : " + mChannelNumber);
			}
		}else{
			Log.d(TAG, "getNextChannelId - Data is available in Cursor for Channel Number : " + mChannelNumber);
		}
		return lNextChannelID;
	}
	
	public int getPrevChannelId(int mChannelNumber)
	{
		Log.d(TAG, "getPrevChannelId - Channel Number : " + mChannelNumber);
		Cursor c = mCursor;
		int lPrevChannelID = 0;
		boolean IFound = false;
		if((c != null) && (c.getCount() > 0)){
			c.moveToLast();
			do{
				int mChannelNum = Integer.parseInt(c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
				if( mChannelNum < mChannelNumber){
					IFound = true;
					if(ChannelUtils.getChannelFilter() == ChannelFilterConstants.ALL){
						lPrevChannelID = Integer.parseInt(c.getString(c.getColumnIndex(Channels._ID)));
					}else{
						lPrevChannelID = Integer.parseInt(c.getString(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID)));
					}
					break;
				}
				
			}while(c.moveToPrevious());
			if(IFound == false){
				Log.d(TAG, "getPrevChannelId - not Present For Channel Number : " + mChannelNumber);
			}
		}else{
			Log.d(TAG, "getPrevChannelId - Data is available in Cursor for Channel Number : " + mChannelNumber);
		}
		return lPrevChannelID;
	}
	
	
	public void onStop(){
	}
	
	
	public void UpdateCursor() {
		//Log.d(TAG, "UpdateCursor");
		//PlayTvApplication.getInstance().setUpdateNeeded(false);
		mIsExecutedOnce = true;
		this.getChannelType();	
	}
	public static ChannelFilter getChannelFilterInstance(Context mContext){
		//Log.d(TAG, "getChannelFilterInstance Called");
		if(null == mChannelFilter){
			mChannelFilter = new ChannelFilter(mContext);
		}
		
		return mChannelFilter;
		
	}
	public static ChannelFilter getChannelFilterInstance(){
		//Log.d(TAG, "getChannelFilterInstance Called");
		return mChannelFilter;
	}
	
	public void RegisterTvSettingsManager()
     {
		 //Log.d(TAG, "RegisterTvSettingsManager Called");
             property = new int [PROPMAX];

             property[0] = TvSettingsConstants.CHANNELTYPE;
             property[1] = TvSettingsConstants.LASTSELECTEDTUNER;
             property[2] = TvSettingsConstants.INSTSETTINGSINSTALLMODE;
             property[3] = TvSettingsConstants.ACCESSTYPE;
             property[4] = TvSettingsConstants.CHANNELFILTER;
             property[5] = TvSettingsConstants.CHANNELFILTERSATELLITE;
             property[6] = TvSettingsConstants.CHANNELFILTERTC;
             property[7] = TvSettingsConstants.TCCHANNELSUBLIST;
             property[8] = TvSettingsConstants.SATELLITECHANNELSUBLIST;
             
             PStorageBinder = this.new ITVSettingsManagerCallBack(); 
             globalSetting.SetCallBacks(PStorageBinder, property);
     }
	
	protected void UpdateLastSelectedTuner(int prop) {
		if((prop == TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC) 
				||(prop == TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER)){
			Log.d(TAG, "Updating mLastSelectedTuner = " + prop);
			mLastSelectedTuner = prop;
		}
		
	}
	
	/*
	 * Function : Determine the type of the currently tuned channel based on 
	 * 1- Tuner Type 		(0- DVB-TC, 1- DVB-S) 
	 * 2- Installation Mode (0- DVB-T, 1- DVB-C)
	 * 3- Channel Filter 	(0- All, 1- Favourite)
	 * 4- TCChannelSublist  (0- All 1-Digital, 2-Radio, 3-Analog, 4-Free, 5-Scrambled)
	 * 5- SatelliteChannelSublist	(0- All, 1- Digital-1, 2- TV, 3- Radio, 4- Analog)
	 */

	public void getChannelType(){
		//Log.d(TAG, "getChannelType Called ");
		/** Finding the tuner type from Global Setting */
		int mSourceTuner = globalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		int mInstallMode = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
		//Log.d(TAG, "getChannelType:Tuner Type - " +mSourceTuner);
		switch(mSourceTuner){
		
		case TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC:
			
			/** Finding the Channel Filter from Global Setting */
			int mChannelFilter =  ChannelUtils.getChannelFilter();
			Log.d(TAG, "getChannelType:Channel Filter - "+mChannelFilter);
			switch(mChannelFilter){
			case TvSettingsDefinitions.ChannelFilterConstants.ALL:
					/** Finding the Channel Type from Global Setting 0- All 1-Digital, 2-Radio, 3-Analog, 4-Free, 5-Scrambled*/
					int mActiveZapList =  ChannelUtils.getActiveZapList(mSourceTuner);
						Log.d(TAG, "getChannelType : Active Zap list - " + mActiveZapList);
						switch(mActiveZapList){
						case TC_ALLFILTER:
							//Log.d(TAG, "DVB-TC -> ALL -> All Channels");
							getSelection(ChannelConstants.DVBTC_ALL_CHANNELS);
							break;
						case TC_DIGITALFILTER:
							//Log.d(TAG, "DVB-TC -> ALL -> DIGITAL Channels");
							getSelection(ChannelConstants.DVBTC_ALL_DIGITAL_CHANNELS);
							break;
						case TC_FREE:
							//Log.d(TAG, "DVB-TC -> ALL -> FREE Channels");
							getSelection(ChannelConstants.DVBTC_ALL_FREE_CHANNELS);
							break;
						case TC_SCRAMBLED:
							//Log.d(TAG, "DVB-TC -> ALL -> SCRAMBLED Channels");
							getSelection(ChannelConstants.DVBTC_ALL_SCRAMBLED_CHANNELS);
							break;
						case TC_ANALOGFILTER:
							//Log.d(TAG, "DVB-TC -> ALL -> ANALOG Channels");
							getSelection(ChannelConstants.DVBTC_ALL_ANANLOG_CHANNELS);
							break;
						case TC_RADIOFILTER:
							//Log.d(TAG, "DVB-TC -> ALL -> RADIO Channels");
							getSelection(ChannelConstants.DVBTC_ALL_RADIO_CHANNELS);
							break;
						default:
							//Log.d(TAG, "DVB-T -> ALL -> Unknown Channels");
							getSelection(ChannelConstants.DVBTC_ALL_CHANNELS);
							break;
						}
					break;
					
			case TvSettingsDefinitions.ChannelFilterConstants.FAV:
				Log.d(TAG, "DVBTC_FAVORITE_LIST_1");
				int fSelectionType = (mInstallMode == InstSettingsInstallMode.ANTENNA) ? 
																			ChannelConstants.DVBT_FAV_LIST_1:
																			ChannelConstants.DVBC_FAV_LIST_1;
					getSelection(fSelectionType);
					break;
				
			case ChannelConstants.FAV_LIST_2:
				Log.d(TAG, "DVBTC_FAVORITE_LIST_2");
				int tSelectionType = (mInstallMode == InstSettingsInstallMode.ANTENNA) ? 
																			ChannelConstants.DVBT_FAV_LIST_2:
																			ChannelConstants.DVBC_FAV_LIST_2;
				getSelection(tSelectionType);
				break;
				
			case ChannelConstants.FAV_LIST_3:
				Log.d(TAG, "DVBTC_FAVORITE_LIST_3");
				int cSelectionType = (mInstallMode == InstSettingsInstallMode.ANTENNA) ? 
																			ChannelConstants.DVBT_FAV_LIST_3:
																			ChannelConstants.DVBC_FAV_LIST_3;
				getSelection(cSelectionType);
				break;
				
			case ChannelConstants.FAV_LIST_4:
				Log.d(TAG, "DVBTC_FAVORITE_LIST_4");
				int pSelectionType = (mInstallMode == InstSettingsInstallMode.ANTENNA) ? 
																			ChannelConstants.DVBT_FAV_LIST_4:
																			ChannelConstants.DVBC_FAV_LIST_4;
				getSelection(pSelectionType);
				break;
			}
			break;
		case TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER:
			/** Finding the Channel Filter from Global Setting */
			int mChannelFilterSat =  ChannelUtils.getChannelFilter();
			switch(mChannelFilterSat){
				case TvSettingsDefinitions.ChannelFilterConstants.ALL:
					/** Finding the Channel Type from Global Setting */
					int mActiveZapListSat =  ChannelUtils.getActiveZapList(mSourceTuner);
					switch(mActiveZapListSat){
						case SAT_ALL_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL Channels");
							getSelection(ChannelConstants.DVBS_ALL_CHANNELS);
							break;
						case SAT_ALL_FREE_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL --> FREE Channels");
							getSelection(ChannelConstants.DVBS_ALL_FREE_CHANNELS);
							break;
						case SAT_ALL_SCRAMBLED_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL --> SCRAMBLED Channels");
							getSelection(ChannelConstants.DVBS_ALL_SCRAMBLED_CHANNELS);
							break;	
						case SAT_ALL_TV_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL --> TV Channels");
							getSelection(ChannelConstants.DVBS_ALL_TV_CHANNELS);
							break;
						case SAT_ALL_RADIO_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL --> RADIO Channels");
							getSelection(ChannelConstants.DVBS_ALL_RADIO_CHANNELS);
							break;
						case SAT_ALL_SAT1_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL --> SAT1 Channels");
							getSelection(ChannelConstants.DVBS_ALL_SAT1_CHANNELS);
							break;
						case SAT_ALL_SAT2_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL --> SAT2 Channels");
							getSelection(ChannelConstants.DVBS_ALL_SAT2_CHANNELS);
							break;
						case SAT_ALL_SAT3_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL --> SAT3 Channels");
							getSelection(ChannelConstants.DVBS_ALL_SAT3_CHANNELS);
							break;
						case SAT_ALL_SAT4_CHANNELS:
							Log.d(TAG, "DVB-S -> ALL --> SAT4 Channels");
							getSelection(ChannelConstants.DVBS_ALL_SAT4_CHANNELS);
							break;
						}
					break;
				case ChannelConstants.FAV_LIST_1:
					Log.d(TAG, "DVBS_FAV_LIST_1");
					getSelection(ChannelConstants.DVBS_FAV_LIST_1);
					break;
					
				case ChannelConstants.FAV_LIST_2:
					Log.d(TAG, "DVBS_FAV_LIST_2");
					getSelection(ChannelConstants.DVBS_FAV_LIST_2);
					break;
					
				case ChannelConstants.FAV_LIST_3:
					Log.d(TAG, "DVBS_FAV_LIST_3");
					getSelection(ChannelConstants.DVBS_FAV_LIST_3);
					break;
					
				case ChannelConstants.FAV_LIST_4:
					Log.d(TAG, "DVBS_FAV_LIST_4");
					getSelection(ChannelConstants.DVBS_FAV_LIST_4);
					break;
				}
				break;
		}
		
	}	
	
	/*
	 * Function : This Function will determine the selection and selectionArgs based on Tuner Type and 
	 *            Channel Filter
	 */
	void getChannelTypeAll(){
		Log.d(TAG, "getChannelTypeAll Called");
		/** Finding the Tuner type from Global Setting */
		int mSourceTuner = globalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		int mInstallMode = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
		Log.d(TAG, "getChannelTypeAll:Tuner Type - " +mSourceTuner);
		switch(mSourceTuner){
		
		case TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC://For Tuner Type T/C
			/** Finding the Installation mode (0-Antenna, 1- Cable)*/
			int mChannelFilter = ChannelUtils.getChannelFilter();//globalSetting.getInt(TvSettingsConstants.CHANNELFILTER, 0, 0);
			Log.d(TAG, "getChannelTypeAll:Channel filter - " +mChannelFilter);
			switch(mChannelFilter){
			case TvSettingsDefinitions.ChannelFilterConstants.ALL://For Terrestrial Mode
					getSelection(ChannelConstants.DVBTC_ALL_CHANNELS);
				break;
			case ChannelConstants.FAV_LIST_1:
					int f1SelectionType = (mInstallMode == InstSettingsInstallMode.ANTENNA) ? 
														ChannelConstants.DVBT_FAV_LIST_1:
														ChannelConstants.DVBC_FAV_LIST_1;
					getSelection(f1SelectionType);
				break;	
			case ChannelConstants.FAV_LIST_2:
					int f2SelectionType = (mInstallMode == InstSettingsInstallMode.ANTENNA) ? 
														ChannelConstants.DVBT_FAV_LIST_2:
														ChannelConstants.DVBC_FAV_LIST_2;
					getSelection(f2SelectionType);
				break;	
			case ChannelConstants.FAV_LIST_3:
					int f3SelectionType = (mInstallMode == InstSettingsInstallMode.ANTENNA) ? 
														ChannelConstants.DVBT_FAV_LIST_3:
														ChannelConstants.DVBC_FAV_LIST_3;
					getSelection(f3SelectionType);
				break;	
			case ChannelConstants.FAV_LIST_4:
					int f4SelectionType = (mInstallMode == InstSettingsInstallMode.ANTENNA) ? 
														ChannelConstants.DVBT_FAV_LIST_4:
														ChannelConstants.DVBC_FAV_LIST_4;
					getSelection(f4SelectionType);
				break;	
			}		
		break;
		case TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER://For Satellite Tuner Type
			/** Finding the Channel Filter from Global Setting */
			int mChannelFilterSat =  ChannelUtils.getChannelFilter();//globalSetting.getInt(TvSettingsConstants.CHANNELFILTER, 0, 0);
			
			switch(mChannelFilterSat){
		
				case TvSettingsDefinitions.ChannelFilterConstants.ALL:
						getSelection(ChannelConstants.DVBS_ALL_CHANNELS);
					break;
				case ChannelConstants.FAV_LIST_1:
						getSelection(ChannelConstants.DVBS_FAV_LIST_1);
					break;
				case ChannelConstants.FAV_LIST_2:
						getSelection(ChannelConstants.DVBS_FAV_LIST_2);
					break;
				case ChannelConstants.FAV_LIST_3:
						getSelection(ChannelConstants.DVBS_FAV_LIST_3);
					break;
				case ChannelConstants.FAV_LIST_4:
						getSelection(ChannelConstants.DVBS_FAV_LIST_4);
					break;
			}
			break;
		}
	}
	
	
	/*
	 * Function : Set the Selection and SelectionArgs for querying the database based on Current Channel Source type, 
	 * Installation Mode, Channel Filter and Access Type
	 */
	
	public void getSelection(int channelType){
		
		switch(channelType){
		case ChannelConstants.DVBTC_ALL_CHANNELS:
			Log.d(TAG, "DVBTC_ALL_CHANNELS");
			selection = Channels.COLUMN_VERSION_NUMBER + "=? OR " 
							 + Channels.COLUMN_VERSION_NUMBER + "=?";
			selectionArgs = new String[2];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBT);
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBC);
			contentUri =  getContentUri(ChannelConstants.DVBTC_ALL_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBTC_ALL_FREE_CHANNELS:
			Log.d(TAG, "DVBTC_ALL_FREE_CHANNELS");
			selection = "( " + Channels.COLUMN_VERSION_NUMBER + "=? OR " 
					 		 + Channels.COLUMN_VERSION_NUMBER + "=? ) AND "
					 		 + Channels.COLUMN_DESCRIPTION + "!=?";
			selectionArgs = new String[3];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBT);
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBC);	
			selectionArgs[2] = ChannelConstants.VALUE_SCRAMBLED;
			contentUri =  getContentUri(ChannelConstants.DVBTC_ALL_FREE_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBTC_ALL_SCRAMBLED_CHANNELS:
			Log.d(TAG, "DVBTC_ALL_SCRAMBLED_CHANNELS");
			/*TODO : need to move to TvContract*/
			selection = "( " +TvContract.Channels.COLUMN_VERSION_NUMBER + "=? OR " 
							 + TvContract.Channels.COLUMN_VERSION_NUMBER + "=? ) AND "  
							 + TvContract.Channels.COLUMN_DESCRIPTION + "=?";
			selectionArgs = new String[3];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBT);
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBC);
			selectionArgs[2] = ChannelConstants.VALUE_SCRAMBLED;
			contentUri =  getContentUri(ChannelConstants.DVBTC_ALL_SCRAMBLED_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBTC_ALL_DIGITAL_CHANNELS:
			Log.d(TAG, "DVBTC_ALL_DIGITAL_CHANNELS");
			selection = Channels.COLUMN_TYPE + "=? OR " 
						+ Channels.COLUMN_TYPE + "=? OR "
						+ Channels.COLUMN_TYPE + "=? OR "
						+ Channels.COLUMN_TYPE + "=?";
			selectionArgs = new String[4];
			selectionArgs[0] = Channels.TYPE_DVB_T;
			selectionArgs[1] = Channels.TYPE_DVB_C;
			selectionArgs[2] = Channels.TYPE_DVB_T2;
			selectionArgs[3] = Channels.TYPE_DVB_C2;
			contentUri =  getContentUri(ChannelConstants.DVBTC_ALL_DIGITAL_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBTC_ALL_ANANLOG_CHANNELS:
			Log.d(TAG, "DVBTC_ALL_ANANLOG_CHANNELS");
			selection = "( " + Channels.COLUMN_VERSION_NUMBER + "=? OR "
							 + Channels.COLUMN_VERSION_NUMBER + "=? ) AND ( " 
							 + Channels.COLUMN_TYPE + "=? OR " 
							 + Channels.COLUMN_TYPE + "=? )";
			selectionArgs = new String[4];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBT);
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBC);
			selectionArgs[2] = Channels.TYPE_PAL;
			selectionArgs[3] = Channels.TYPE_SECAM;
			contentUri =  getContentUri(ChannelConstants.DVBTC_ALL_ANANLOG_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBTC_ALL_RADIO_CHANNELS:
			Log.d(TAG, "DVBTC_ALL_RADIO_CHANNELS");
			selection = Channels.COLUMN_SERVICE_TYPE + "=? AND ( " 
						+ Channels.COLUMN_VERSION_NUMBER + "=? OR " 
						+ Channels.COLUMN_VERSION_NUMBER + "=? )"; 
			selectionArgs = new String[3];
			selectionArgs[0] = Channels.SERVICE_TYPE_AUDIO;
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBT);
			selectionArgs[2] = Integer.toString(ChannelConstants.VERSION_DVBC);	
			contentUri =  getContentUri(ChannelConstants.DVBTC_ALL_RADIO_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBT_FAV_LIST_1:
			Log.d(TAG, "DVBT_FAV_LIST_1");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBT_FAV_LIST_1);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBT_FAV_LIST_2:
			Log.d(TAG, "DVBT_FAV_LIST_2");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBT_FAV_LIST_2);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBT_FAV_LIST_3:
			Log.d(TAG, "DVBT_FAV_LIST_3");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBT_FAV_LIST_3);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBT_FAV_LIST_4:
			Log.d(TAG, "DVBT_FAV_LIST_4");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBT_FAV_LIST_4);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBC_FAV_LIST_1:
			Log.d(TAG, "DVBC_FAV_LIST_1");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBC_FAV_LIST_1);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBC_FAV_LIST_2:
			Log.d(TAG, "DVBC_FAV_LIST_2");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBC_FAV_LIST_2);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
			initCursorLoader();
			break;
		
		case ChannelConstants.DVBC_FAV_LIST_3:
			Log.d(TAG, "DVBC_FAV_LIST_3");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBC_FAV_LIST_3);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
			initCursorLoader();
			break;
		
		case ChannelConstants.DVBC_FAV_LIST_4:
			Log.d(TAG, "DVBC_FAV_LIST_4");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBC_FAV_LIST_4);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
			initCursorLoader();
			break;
					
		case ChannelConstants.DVBS_ALL_CHANNELS:
			Log.d(TAG, "DVBS_ALL_CHANNELS");
			selection = Channels.COLUMN_VERSION_NUMBER + "=? OR " 
						+ Channels.COLUMN_VERSION_NUMBER + "=?  OR "
						+ Channels.COLUMN_VERSION_NUMBER + "=?  OR "
						+ Channels.COLUMN_VERSION_NUMBER + "=?";
			selectionArgs = new String[4];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBS1);
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBS2);
			selectionArgs[2] = Integer.toString(ChannelConstants.VERSION_DVBS3);
			selectionArgs[3] = Integer.toString(ChannelConstants.VERSION_DVBS4);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_FREE_CHANNELS:
			Log.d(TAG, "DVBS_ALL_FREE_CHANNELS");
			selection = Channels.COLUMN_DESCRIPTION + "!=? AND ( " 
					  + Channels.COLUMN_VERSION_NUMBER + "=? OR "
					  + Channels.COLUMN_VERSION_NUMBER + "=? OR "
					  + Channels.COLUMN_VERSION_NUMBER + "=? OR "
					  + Channels.COLUMN_VERSION_NUMBER + "=? )";
			selectionArgs = new String[5];
			selectionArgs[0] = ChannelConstants.VALUE_SCRAMBLED;
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBS1);
			selectionArgs[2] = Integer.toString(ChannelConstants.VERSION_DVBS2);
			selectionArgs[3] = Integer.toString(ChannelConstants.VERSION_DVBS3);
			selectionArgs[4] = Integer.toString(ChannelConstants.VERSION_DVBS4);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_FREE_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_SCRAMBLED_CHANNELS:
			Log.d(TAG, "DVBS_ALL_SCRAMBLED_CHANNELS");
			selection = Channels.COLUMN_DESCRIPTION + "=? AND ( " 
					  + Channels.COLUMN_VERSION_NUMBER + "=? OR "
					  + Channels.COLUMN_VERSION_NUMBER + "=? OR "
					  + Channels.COLUMN_VERSION_NUMBER + "=? OR "
					  + Channels.COLUMN_VERSION_NUMBER + "=? )";
			selectionArgs = new String[5];
			selectionArgs[0] = ChannelConstants.VALUE_SCRAMBLED;
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBS1);
			selectionArgs[2] = Integer.toString(ChannelConstants.VERSION_DVBS2);
			selectionArgs[3] = Integer.toString(ChannelConstants.VERSION_DVBS3);
			selectionArgs[4] = Integer.toString(ChannelConstants.VERSION_DVBS4);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_SCRAMBLED_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_RADIO_CHANNELS:
			Log.d(TAG, "DVBS_ALL_RADIO_CHANNELS");
			selection = Channels.COLUMN_SERVICE_TYPE + "=? AND ( " 
						+ Channels.COLUMN_VERSION_NUMBER + "=? OR "
						+ Channels.COLUMN_VERSION_NUMBER + "=? OR "
						+ Channels.COLUMN_VERSION_NUMBER + "=? OR "
						+ Channels.COLUMN_VERSION_NUMBER + "=? )";
			selectionArgs = new String[5];
			selectionArgs[0] = Channels.SERVICE_TYPE_AUDIO;
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBS1);
			selectionArgs[2] = Integer.toString(ChannelConstants.VERSION_DVBS2);
			selectionArgs[3] = Integer.toString(ChannelConstants.VERSION_DVBS3);
			selectionArgs[4] = Integer.toString(ChannelConstants.VERSION_DVBS4);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_RADIO_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_TV_CHANNELS:
			Log.d(TAG, "DVBS_ALL_TV_CHANNELS");
			selection = Channels.COLUMN_SERVICE_TYPE + "=? AND ( " 
					+ Channels.COLUMN_VERSION_NUMBER + "=? OR "
					+ Channels.COLUMN_VERSION_NUMBER + "=? OR "
					+ Channels.COLUMN_VERSION_NUMBER + "=? OR "
					+ Channels.COLUMN_VERSION_NUMBER + "=? )";
			selectionArgs = new String[5];
			selectionArgs[0] = Channels.SERVICE_TYPE_AUDIO_VIDEO;
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBS1);
			selectionArgs[2] = Integer.toString(ChannelConstants.VERSION_DVBS2);
			selectionArgs[3] = Integer.toString(ChannelConstants.VERSION_DVBS3);
			selectionArgs[4] = Integer.toString(ChannelConstants.VERSION_DVBS4);	
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_TV_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_SAT_CHANNELS:
			Log.d(TAG, "DVBS_ALL_SAT_CHANNELS");
			selection = Channels.COLUMN_VERSION_NUMBER + "=? OR "
						+ Channels.COLUMN_VERSION_NUMBER + "=? OR "
						+ Channels.COLUMN_VERSION_NUMBER + "=? OR "
						+ Channels.COLUMN_VERSION_NUMBER + "=?";
			selectionArgs = new String[4];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBS1);
			selectionArgs[1] = Integer.toString(ChannelConstants.VERSION_DVBS2);
			selectionArgs[2] = Integer.toString(ChannelConstants.VERSION_DVBS3);
			selectionArgs[3] = Integer.toString(ChannelConstants.VERSION_DVBS4);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_SAT_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_SAT1_CHANNELS:
			Log.d(TAG, "DVBS_ALL_SAT1_CHANNELS");
			selection =  Channels.COLUMN_VERSION_NUMBER + "=?";
			selectionArgs = new String[1];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBS1);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_SAT1_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_SAT2_CHANNELS:
			Log.d(TAG, "DVBS_ALL_SAT2_CHANNELS");
			selection = Channels.COLUMN_VERSION_NUMBER + "=?";
			selectionArgs = new String[1];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBS2);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_SAT2_CHANNELS);
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_PROJ;
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_SAT3_CHANNELS:
			Log.d(TAG, "DVBS_ALL_SAT3_CHANNELS");
			selection = Channels.COLUMN_VERSION_NUMBER + "=?";
			selectionArgs = new String[1];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBS3);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_SAT3_CHANNELS);
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_PROJ;
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_ALL_SAT4_CHANNELS:
			Log.d(TAG, "DVBS_ALL_SAT4_CHANNELS");
			selection = Channels.COLUMN_VERSION_NUMBER + "=?";
			selectionArgs = new String[1];
			selectionArgs[0] = Integer.toString(ChannelConstants.VERSION_DVBS4);
			contentUri =  getContentUri(ChannelConstants.DVBS_ALL_SAT4_CHANNELS);
			sortOrder = " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_FAV_LIST_1:
			Log.d(TAG, "DVBS_FAV_LIST_1");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBS_FAV_LIST_1);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_FAV_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_FAV_LIST_2:
			Log.d(TAG, "DVBS_FAV_LIST_2");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBS_FAV_LIST_2);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_FAV_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_FAV_LIST_3:
			Log.d(TAG, "DVBS_FAV_LIST_3");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBS_FAV_LIST_3);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_FAV_PROJ;
			initCursorLoader();
			break;
			
		case ChannelConstants.DVBS_FAV_LIST_4:
			Log.d(TAG, "DVBS_FAV_LIST_4");
			selection =  null;
			selectionArgs = null;
			contentUri =  getContentUri(ChannelConstants.DVBS_FAV_LIST_4);
			sortOrder = "CAST( " + IBaseFavoriteColumns.COLUMN_RANK+" AS FLOAT) ASC";
			CHANNEL_PROJ = CHANNEL_INFO_DVBS_FAV_PROJ;
			initCursorLoader();
			break;
			
		}	
	}
	
	private Uri getContentUri(int lZapListType){
		Uri contentUri = TvContract.Channels.CONTENT_URI;
			
		switch (lZapListType){
		case ChannelConstants.DVBT_FAV_LIST_1:
			contentUri = IFavoriteContract.ITFavoriteList1.CONTENT_URI;
			break;
		case ChannelConstants.DVBT_FAV_LIST_2:
			contentUri = IFavoriteContract.ITFavoriteList2.CONTENT_URI;
			break;
		case ChannelConstants.DVBT_FAV_LIST_3:
			contentUri = IFavoriteContract.ITFavoriteList3.CONTENT_URI;
			break;
		case ChannelConstants.DVBT_FAV_LIST_4:
			contentUri = IFavoriteContract.ITFavoriteList4.CONTENT_URI;
			break;
		case ChannelConstants.DVBC_FAV_LIST_1:
			contentUri = IFavoriteContract.ICFavoriteList1.CONTENT_URI;
			break;
		case ChannelConstants.DVBC_FAV_LIST_2:
			contentUri = IFavoriteContract.ICFavoriteList2.CONTENT_URI;
			break;
		case ChannelConstants.DVBC_FAV_LIST_3:
			contentUri = IFavoriteContract.ICFavoriteList3.CONTENT_URI;
			break;
		case ChannelConstants.DVBC_FAV_LIST_4:
			contentUri = IFavoriteContract.ICFavoriteList4.CONTENT_URI;
			break;
		case ChannelConstants.DVBS_FAV_LIST_1:
			contentUri = IFavoriteContract.ISATFavoriteList1.CONTENT_URI;
			break;
		case ChannelConstants.DVBS_FAV_LIST_2:
			contentUri = IFavoriteContract.ISATFavoriteList2.CONTENT_URI;
			break;
		case ChannelConstants.DVBS_FAV_LIST_3:
			contentUri = IFavoriteContract.ISATFavoriteList3.CONTENT_URI;
			break;
		case ChannelConstants.DVBS_FAV_LIST_4:
			contentUri = IFavoriteContract.ISATFavoriteList4.CONTENT_URI;
			break;
		}
		Log.d(TAG, "getContentUri uri " + contentUri);
		return contentUri;
	}
	
	//Unused
	/*private Uri getContentUri(){
		Uri contentUri = TvContract.Channels.CONTENT_URI;	
		return contentUri;
	}*/
	
	
	private void initCursorLoader() {
		//Log.d(TAG, "initCursorLoader Called");
		mLastSelectedTuner = globalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		if(mCursorLoaderTask != null){
			Log.d(TAG, "mCursorLoaderTask cancelled and re-initalizing the CursorUpdate.. ");
			mCursorLoaderTask.cancel(true);
		}
		mCursorLoaderTask = new CursorLoaderTask();
		mCursorLoaderTask.execute("ChannelFilter");
	}

	private class CursorLoaderTask extends AsyncTask<String,Void, Cursor>{

		@Override
		protected void onCancelled(Cursor result) {
			// TODO Auto-generated method stub
			super.onCancelled(result);
			if(result!=null){
				Log.d(TAG,"onCancelled");
				result.close();
			}
		}

		@Override
		protected Cursor doInBackground(String... args) {
			Cursor cursor = null;
			//Log.d(TAG, "doInBackground -  querying content provider ...");
			cursor = mContext.getContentResolver().query(contentUri, CHANNEL_PROJ, selection, selectionArgs, sortOrder);
			mIsCursorLoading = true;
			return cursor;
		}

		@Override
		protected void onPostExecute(Cursor tmpCursor) {
			super.onPostExecute(mCursor);
			resetCursor();
			mCursor = tmpCursor;
			//Log.d(TAG, "onPostExecute - success - mIsExecutedOnce - " + mIsExecutedOnce);
			if(null != mCursor){
			   Log.d(TAG, "onPostExecute - mCursor.getCount() = " + mCursor.getCount());
			}else{
			   Log.d(TAG, "onPostExecute - Cursor is null");
			}
			if( (null == mCursor) || (mCursor.getCount() == 0)){
				if(mIsExecutedOnce == true ){
					mIsExecutedOnce = false;
					ChannelFilter.this.getChannelTypeAll();	
					//** Switch back to All Channel List if Current Channel Filter list is Favourite and There us no channel available in favourite list*//*
					Log.d(TAG, "Before Switching to All Channel List value of - mIsExecutedOnce : " + mIsExecutedOnce);
					if((mCursor == null) || (mCursor.getCount() == 0)){
						ChannelFilter.this.switchToAllChannelsList();
					}
				}
			}else{
				mIsCursorLoading = false;
			}	
		}
	}
	
	private void resetCursor() {
		if(mCursor != null){
			mCursor.close();
			mCursor = null;
		}	
	}
	
	/**
	 * This Function will re-trigger the Query to Update Global Cursor IF there is no channel available in favourite list
	 */
	public void switchToAllChannelsList() {
		Log.d(TAG, "switchToAllChannelsList -");
		int mChannelFilter = ChannelUtils.getChannelFilter();
		Log.d(TAG, "switchToAllChannelsList - mChhanelFilter " + mChannelFilter);
		if ((mChannelFilter == TvSettingsDefinitions.ChannelFilterConstants.FAV) && (null != mContext)){
				Log.d(TAG, "No Channel Available in Favourite List .. Switching to all channel list");
				ChannelUtils.storeChannelFilter(TvSettingsDefinitions.ChannelFilterConstants.ALL);
				globalSetting.putInt(TvSettingsConstants.CHANNELFILTER, 0, 0);
			}
		}
			
	/**
	 * This Function will query the Global Cursor and will find the current channel number data
	 * @param channelNumber
	 * @return channelData (ContentValue)
	 */
	public Bundle getChannelData(int channelId){
		Log.d(TAG, "getChannelData channel id " + channelId);
		Bundle channelData = null;
		int  mChannelType = ChannelUtils.getChannelFilter();//globalSetting.getInt(TvSettingsConstants.CHANNELFILTER, 0, 0);
		switch(mChannelType){
		case ChannelFilterConstants.ALL:
			channelData = parseChannelData(channelId);
			break;
		case ChannelFilterConstants.FAV_LIST_1:
		case ChannelFilterConstants.FAV_LIST_2:
		case ChannelFilterConstants.FAV_LIST_3:
		case ChannelFilterConstants.FAV_LIST_4:
			Log.d(TAG, "getChannelData  FavouritList " + mChannelType );
			channelData = parseFavChannelData(channelId);
			break;
		default:
			Log.d(TAG, "getChannelData - NVM corrupted " + mChannelType);
			channelData = parseChannelData(channelId);
			break;
		}
		
		return channelData;
	}
	/**
	 * This function will loop through the Global Cursor If the Current Zaplist is Favourite Channel List and fill the Content Values to Channel Number and Channel Name
	 * @param channelNumber
	 * @return channelData (ContentValue)
	 */
	
	private Bundle parseFavChannelData(int lChannelId) {
		Log.d(TAG, "parsFavChannelData : Channel ID - " + lChannelId);
		Bundle mChannelData = null;
		boolean iFound = false;
		Cursor c = mCursor;
		int favIndex = 0;
		if ((c != null) && (c.getCount() > 0)) {
			c.moveToFirst();
			do{
				int cid = Integer.parseInt(c.getString(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID)));
				favIndex++;
				if(cid == lChannelId){
					Log.d(TAG, "Channel id found in the cursor : " + lChannelId);
					iFound = true;
					mChannelData = parseFavData(c, favIndex);
					Log.d(TAG, "Channel name  " + c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NAME)));
					Log.d(TAG, "Favorite number " + c.getInt(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_RANK)));
					break;
				}
			}while(c.moveToNext());
			if(iFound == false){
				Log.d(TAG," parsFavChannelData - data is not available for channel id " + lChannelId);
				return null;
			}
		}else{
			Log.d(TAG, "There is No Channel Data in Global Cursor ..!!");
		}
		return mChannelData;
	}
	/**
	 * This function will loop through the Global Cursor If the Current Zaplist is All Channel List and fill the Content Values to Channel Number and Channel Name
	 * @param channelNumber
	 * @return mChannelData (ContentValue)
	 */
	private Bundle parseChannelData(int channelId) {
		Log.d(TAG, "parseChannelData : Channel id - " + channelId);
		Bundle mChannelData = null;
		boolean iFound = false;
				
		if(!mIsCursorLoading) {
			Cursor c = mCursor;
			if ((c != null) && (c.getCount() > 0)) {
				c.moveToFirst();
				do{
					int cid = Integer.parseInt(c.getString(c.getColumnIndex(Channels._ID)));
					if(cid == channelId){
						iFound = true;
						mChannelData = parseData(c);
						Log.d(TAG, "ChannelName : " + c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NAME)));
						Log.d(TAG, "ChannelNumber : " + c.getInt(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
						break;
					}
				}while(c.moveToNext() == true);
			}else{
				Log.d(TAG, "No data available in global Cursor ...!!! Again querying TVCP for all channel list");
			}
		}
		
		if(iFound == false){
			Log.d(TAG, "parseChannelData - Not Found in global Cusrsor - Channel ID : " + channelId);
			mChannelData = getDataFromTVContentProvider(channelId);
		}
		return mChannelData;
	}
	
	/**
	 * Function will query the Content Provider If Global Cursor Does Not have any Data
	 * @param channelNumber
	 * @return mChannelData(Bundle)
	 */
	private Bundle getDataFromTVContentProvider(int channelId) {
		Log.d(TAG, "getDataFromTVContentProvider channel id " + channelId);
		Bundle mChannelData = null;
		int filter = ChannelUtils.getChannelFilter();
		int mLastSelectedTuner = globalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		int lActiveListType = getActiveListType(filter);
		Uri mUri = getContentUri(lActiveListType );
		String[] CHANNEL_PROJ = CHANNEL_INFO_PROJ;
		String mSelecion = Channels._ID + "=?";
		if((filter >= ChannelFilterConstants.FAV_LIST_1) && (filter <= ChannelFilterConstants.FAV_LIST_4)){
			mSelecion = IBaseFavoriteColumns.COLUMN_CHANNEL_ID + "=?";
			CHANNEL_PROJ = CHANNEL_INFO_FAV_PROJ;
		}
		String[] mSelectionArgs = {
				Integer.toString(channelId)
		};
	
		Cursor c = mContext.getContentResolver().query(mUri, CHANNEL_PROJ, mSelecion, mSelectionArgs, null);
		if(( c != null) && (c.getCount() > 0) ){
			c.moveToFirst();
			 mChannelData = new Bundle();
			 if((filter >= ChannelFilterConstants.FAV_LIST_1) && (filter <= ChannelFilterConstants.FAV_LIST_4)){
				 mChannelData.putInt("ChannelNumber", c.getInt(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_RANK))+1);
			 }else{
				 mChannelData.putInt("ChannelNumber", c.getInt(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
			 }
			mChannelData.putInt("ChannelNumber",c.getInt(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
			mChannelData.putInt("UniqueChannelId", c.getInt(c.getColumnIndex(Channels._ID)));
			mChannelData.putInt("SystemHidden", c.getInt(c.getColumnIndex(Channels.COLUMN_BROWSABLE)));
			Log.d(TAG, "ChannelNumber : " + c.getInt(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
			c.close();
		}else{
			if(c!= null){
				c.close();
			}
		}
		return mChannelData;
	}
	private int getActiveListType(int filter) {
		Medium m = ChannelUtils.getCurrentMedium();
		int type = ChannelConstants.ALL_CHANNELS;
		switch(m){
		case MEDIUM_CABLE:
			switch(filter){
			case ChannelFilterConstants.FAV_LIST_1:
				type = ChannelConstants.DVBC_FAV_LIST_1;
				break;
			case ChannelFilterConstants.FAV_LIST_2:
				type = ChannelConstants.DVBC_FAV_LIST_2;
				break;
			case ChannelFilterConstants.FAV_LIST_3:
				type = ChannelConstants.DVBC_FAV_LIST_3;
				break;
			case ChannelFilterConstants.FAV_LIST_4:
				type = ChannelConstants.DVBC_FAV_LIST_4;
				break;			
			}
			break;
		case MEDIUM_TERRESTRIAL:
			switch(filter){
			case ChannelFilterConstants.FAV_LIST_1:
				type = ChannelConstants.DVBT_FAV_LIST_1;
				break;
			case ChannelFilterConstants.FAV_LIST_2:
				type = ChannelConstants.DVBT_FAV_LIST_2;
				break;
			case ChannelFilterConstants.FAV_LIST_3:
				type = ChannelConstants.DVBT_FAV_LIST_3;
				break;
			case ChannelFilterConstants.FAV_LIST_4:
				type = ChannelConstants.DVBT_FAV_LIST_4;
				break;			
			}
			break;
		case MEDIUM_SATELLITE:
			switch(filter){
			case ChannelFilterConstants.FAV_LIST_1:
				type = ChannelConstants.DVBS_FAV_LIST_1;
				break;
			case ChannelFilterConstants.FAV_LIST_2:
				type = ChannelConstants.DVBS_FAV_LIST_2;
				break;
			case ChannelFilterConstants.FAV_LIST_3:
				type = ChannelConstants.DVBS_FAV_LIST_3;
				break;
			case ChannelFilterConstants.FAV_LIST_4:
				type = ChannelConstants.DVBS_FAV_LIST_4;
				break;			
			}
			break;
		}
		Log.d(TAG, "getActiveListType returns " + type);
		return type;
	}

	/**
	 * Extract the Next Channel Data from the Cursor based on given channel number and and returns in Content Value 
	 * @param channelNumber
	 * @return channelData (Bundle)
	 */
	public Bundle getNextChannelData(int channelId){
		Log.d(TAG, "getNextChannelData channel id - " + channelId);
		Bundle channelData = null;
		int  mChannelType = ChannelUtils.getChannelFilter();//globalSetting.getInt(TvSettingsConstants.CHANNELFILTER, 0, 0);
		switch(mChannelType){
		case ChannelFilterConstants.ALL:
			channelData = parseNextChannelData(channelId);
			break;
		case ChannelFilterConstants.FAV_LIST_1:
		case ChannelFilterConstants.FAV_LIST_2:
		case ChannelFilterConstants.FAV_LIST_3:
		case ChannelFilterConstants.FAV_LIST_4:
			Log.d(TAG, "getNextChannelData FavouriteList " + mChannelType);
			channelData = parseNextFavChannelData(channelId);
			break;
		default:
			Log.d(TAG, "NVM corrupted ChannelFilter " + mChannelType);
			channelData = parseNextChannelData(channelId);
			break;
		}
		
		return channelData;
	}
	
	/**
	 * Function will find the next favourite of the given favourite number and Fill the Favourite Number and Channel Name into Content Values and return it
	 * It returns null if next favourite number not found.
	 * @param channel
	 * @return channelData(Bundle)
	 */
	
	private Bundle parseNextFavChannelData(int mCurrentFavCid) {
		Log.d(TAG, "parseNextFavChannelData  mCurrentCid " + mCurrentFavCid);
		int favouriteNumber = 0;
		Bundle mChannelData = null;
		boolean IFound = false;
		int favIndex = 0;
		Cursor c = mCursor;
		if ((c != null) && (c.getCount() > 0)){
			c.moveToFirst();
			do{
				favIndex++;
				int lNextFavCid = c.getInt(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID));
				if(lNextFavCid == mCurrentFavCid){
					IFound = true;
					if(!c.isLast()){
						c.moveToNext();
					}else{
						c.moveToFirst();
					}
					Log.d(TAG, "parseNextFavChannelData CurrentFavCid " + mCurrentFavCid + " NextFavCid " + c.getInt(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID)));
					mChannelData = parseFavData(c, favIndex);
					break;
				}
					
			}while(c.moveToNext());
		}else{
			Log.d(TAG, "parseNextFavChannelData  - global cursor is empty");
		}
		return mChannelData;
	}
	/**
	 * This Function will extract the data of next channel number from Global Cursor and fill into the Content Value and will return the same
	 * @param channel
	 * @return channelData (ContentValues)
	 */

	private Bundle parseNextChannelData(int channelId){
		Log.d(TAG, "parseNextChannelData - Channel ID : " + channelId);
		Bundle channelData = null;
		Cursor c =  mCursor;
		boolean IFound = false;
		if ((c != null) && (c.getCount() >0)){
			c.moveToFirst();
			do{
				int nextChannelId = c.getInt(c.getColumnIndex(Channels._ID));
				if(nextChannelId == channelId)
				{
					IFound = true;
					if(!c.isLast()){
						c.moveToNext();
					}else{
						c.moveToFirst();
					}
					Log.d(TAG, " parseNextChannelData - Found Next Channel ID - " + c.getInt(c.getColumnIndex(Channels._ID)));
					channelData = parseData(c);
					while(ChannelUtils.checkSystemHiddenValue(channelData)) {
                        if(c.isLast()){
                               c.moveToFirst();
                        }else{
                               c.moveToNext();
                        }
                        channelData = parseData(c);
					};
                 break;
				}
			}while(c.moveToNext() == true );
			if(IFound == false){
				Log.d(TAG, " parseNextChannelData - Data is Not available for Channel ID : " + channelId);
			}
		}
		return channelData;
	}
	/**
	 * Extract the Previous Channel Data from the Cursor based on current active zaplist (ALL/Favourite) and returns in Content Value 
	 * @param channelNumber
	 * @return channelData (Bundle)
	 */
	public Bundle getPrevChannelData(int channelId){
		Bundle channelData = null;
		int  mChannelType = ChannelUtils.getChannelFilter();
		switch(mChannelType){
		case ChannelFilterConstants.ALL: 
			channelData = parsePrevChannelData(channelId);
			break;
		case ChannelFilterConstants.FAV_LIST_1:
		case ChannelFilterConstants.FAV_LIST_2:
		case ChannelFilterConstants.FAV_LIST_3:
		case ChannelFilterConstants.FAV_LIST_4:
			channelData = parsePrevFavChannelData(channelId);
			break;
		default:
			Log.d(TAG, "Global setting got corrupted - ChannelFilter " + mChannelType);
			channelData = parsePrevChannelData(channelId);
			break;
		}
		return channelData;
	}
	
	private Bundle parseData(Cursor c){
		Bundle channelData = new Bundle();
		channelData.putInt("ChannelNumber",c.getInt(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
		channelData.putInt("UniqueChannelId", c.getInt(c.getColumnIndex(Channels._ID)));
		channelData.putInt("SystemHidden", c.getInt(c.getColumnIndex(Channels.COLUMN_BROWSABLE)));
		
		return channelData;
	}
	
	private Bundle parseFavData(Cursor c, int favIndex){
		Bundle channelData = new Bundle();
		channelData.putInt("ChannelNumber",favIndex);
		channelData.putInt("UniqueChannelId", c.getInt(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID)));
		return channelData;
	}
	
	/**
	 * Parses the channel data from the cursor based on current channel favourite number
	 * @param channel
	 * @return channelData(Bundle)
	 */
	
	private Bundle parsePrevFavChannelData(int mCurrentFavCid) {
		Log.d(TAG, "parsePrevFavChannelData CurrentFavCid " + mCurrentFavCid );
		int favouriteNumber = 0;
		boolean IFound = false;
		Bundle channelData = null;
		Cursor c =  mCursor;
		int favIndex = 0;
		if ((c != null) && (c.getCount()> 0 )){
			c.moveToFirst();
			do{
				int lPrevFavCid = c.getInt(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID));
				favIndex ++;
				Log.d(TAG, " lPrevFavCid " + lPrevFavCid + " c.getPosition() " + c.getPosition());
				if(lPrevFavCid == mCurrentFavCid)
				{
					IFound = true;
					if(!c.isFirst()){
						c.moveToPrevious();
					}else{
						c.moveToLast();
					}
					Log.d(TAG, "parsePrevFavChannelData CurrentFavCid " + mCurrentFavCid + " lPrevFavCid " + lPrevFavCid);
					channelData = parseFavData(c, favIndex);
					break;
				}
			}while(c.moveToNext());
		}else{
			Log.d(TAG, "parsePrevFavChannelData Global cursor is empty .. returning null");
		}
		return channelData;
	}
	/**
	 * Fetch the previous channel data from global cursor and parse into the Content Value
	 * @param channel
	 * @return channelData (Bundle)
	 */

	private Bundle parsePrevChannelData(int channelID){
		Log.d(TAG, "parsePrevChannelData - channelID : " + channelID );
		Bundle channelData = null;
		Cursor c =  mCursor;
		boolean IFound = false;
		if ((c != null) && (c.getCount() > 0)){
			c.moveToLast();
			do{
				int prevChannelId = c.getInt(c.getColumnIndex(Channels._ID));
				if(prevChannelId ==channelID)
				{
					IFound = true;
					if(c.isFirst()) {
						c.moveToLast();
					} else {
						c.moveToPrevious();
					}
					Log.d(TAG, " parsePrevChannelData - Found prev Channel ID " + c.getInt(c.getColumnIndex(Channels._ID)));
					channelData = parseData(c);
					while(ChannelUtils.checkSystemHiddenValue(channelData)) {
                        if(c.isFirst()){
                               c.moveToLast();
                        }else{
                               c.moveToPrevious();
                        }
                        channelData = parseData(c);
					};
					break;
				}
			}while(c.moveToPrevious());
			if(IFound == false){
				Log.d(TAG, "parsePrevChannelData - not found for Channel ID :  " + channelID);
			}
		}
		return channelData;
	}
	/**
	 * This Function will take Channel Number as input and Loop Through in Cursor To Find Out the it's favourite number
	 * @param mChannelNumber
	 * @return mFavouriteNumber
	 */
	public int getFavouriteNumber(int mChannelNumber){
		Log.d(TAG, "getFavouriteNumber Called For Channel Number : " + mChannelNumber);
		Cursor c = mCursor;
		int mFavouriteNumber = 0;
		if((c != null) && (c.getCount() > 0)){
			c.moveToFirst();
			do{
				int mChannelNum = Integer.parseInt(c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
				if( mChannelNum == mChannelNumber){
					/*TODO - Channels.COLUMN_DISPLAY_NUMBER needs to be change to Channels.COULMN_RANK*/
					mFavouriteNumber = Integer.parseInt(c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));//ChannelContract.C_FAVORITENUMBER)));
					break;
				}
			}while(c.moveToNext() == true);
			if(mFavouriteNumber == 0){
				Log.d(TAG, "getFavouriteNumber - Data is not Present For Channel Number : " + mChannelNumber);
			}
			
		}else{
			Log.d(TAG, "getFavouriteNumber - No Channel Data is available in Global Cursor : Channel Number : " + mChannelNumber);
		}
		
		return mFavouriteNumber;
	}
	/**
	 * This Function will take Favourite Number as input and Loop Through in Cursor To Find Out the it's Channel number
	 * @param mFavouiteNumber
	 * @return mChannelNumber
	 */
	public int getChannelNumber(int mFavouiteNumber){
		Cursor c = mCursor;
		int mChannelNumber = 0;
		boolean IFound = false;
		if((c != null) && (c.getCount() > 0)){
			c.moveToFirst();
			do{
				/*TODO - Channels.COLUMN_DISPLAY_NUMBER needs to be change to Channels.COULMN_RANK*/
				int mFavouriteNum = Integer.parseInt(c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));//ChannelContract.C_FAVORITENUMBER)));
				if( mFavouriteNum == mFavouiteNumber){
					IFound = true;
					mChannelNumber = Integer.parseInt(c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));//.C_PRESET_ID)));
					break;
				}
				
			}while(c.moveToNext() == true);
			if(IFound == false){
				Log.d(TAG, "getChannelNumber - Data is not Present For Channel Number : " + mChannelNumber);
			}
		}else{
			Log.d(TAG, "getChannelNumber - No data is available in cursor : Channel Number : " + mFavouiteNumber);
		}
		Log.d(TAG, "getChannelNumber - FavoriteNum : " + mFavouiteNumber + " Channel Num = " + mChannelNumber);
		return mChannelNumber;
	}
	
	/**
	 * This Function will loop through in global cursor and find out the Unique Channel ID
	 * @param mChannelNumber
	 * @return mUniqueChannelID
	 */
	public int getUnqueChannelId(int mChannelNumber)
	{
		Cursor c = mCursor;
		int mUniqueChannelID = 0;
		boolean IFound = false;
		if((c != null) && (c.getCount() > 0)){
			c.moveToFirst();
			do{
				int mChannelNum = Integer.parseInt(c.getString(c.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));//ChannelContract.C_PRESET_ID)));
				if( mChannelNum == mChannelNumber){
					IFound = true;
					if(ChannelUtils.getChannelFilter() == ChannelFilterConstants.ALL){
						mUniqueChannelID = Integer.parseInt(c.getString(c.getColumnIndex(Channels._ID)));
					}else{
						mUniqueChannelID = Integer.parseInt(c.getString(c.getColumnIndex(IBaseFavoriteColumns.COLUMN_CHANNEL_ID)));
					}
					break;
				}
				
			}while(c.moveToNext() == true);
			if(IFound == false){
				Log.d(TAG, "getUnqueChannelId - UniqueChannelId is not Present For Channel Number : " + mChannelNumber);
			}
		}else{
			Log.d(TAG, "getUnqueChannelId - No Channel Data is available in Global Cursor : Channel Number : " + mChannelNumber);
		}
		Log.d(TAG, "getUnqueChannelId returns channel number " + mChannelNumber + " uniqueid " + mUniqueChannelID);
		return mUniqueChannelID;
	}
		
	
	class ITVSettingsManagerCallBack extends ITvSettingsManager.ITvSettingsManagerNotify {
		public void OnUpdate(int property) {
			int value=ITvSettingsManager.Instance.getInterface().getInt(property, 0, 0);
			Log.d(TAG, "Notification From Global Setting Received  " + property + " Value = " + value);
			if((property == TvSettingsConstants.CHANNELFILTERTC) || (property == TvSettingsConstants.CHANNELFILTERSATELLITE)){
				RegisterFavDbObserver(value);
			}
        	UpdateLastSelectedTuner(property);
        	UpdateCursor();
		}
	}
	
	private int getcid(Uri uri) throws IllegalArgumentException{
		int cid = -1;
		try {
			cid = (int)ContentUris.parseId(uri);
		}catch(Exception e){
			throw new IllegalArgumentException();
		}
		return cid;
	}
	/*begin:min.jiang add 2016-03-16, for clock channel*/
	public int getSourceType(int channelID){
	    int sourceType = -1;
	    Uri contentUri = Channels.CONTENT_URI;
		String sortOrder=" CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC";
		String[] ChannelProjection = new String[] {
												Channels.COLUMN_VERSION_NUMBER
											};
		String selection = Channels._ID + "=?";
		String str = "" + channelID;
		String[] selectionArgs = new String[]{str};	
		
		Cursor cursor =  mContext.getContentResolver().query(contentUri, ChannelProjection, selection, selectionArgs, sortOrder);
		
		if ((cursor != null) && (cursor.getCount() > 0)){
			cursor.moveToFirst();
			sourceType = cursor.getInt(cursor.getColumnIndex(Channels.COLUMN_VERSION_NUMBER));
			cursor.close();
		}
		
		return sourceType;
	}	
	/*end:min.jiang add*/
}
