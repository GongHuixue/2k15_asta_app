package org.droidtv.tunerservice;

import org.droidtv.tv.tvinput.Clonechannel;
import org.droidtv.tv.tvinput.ClonechannelParam;
import org.droidtv.tv.tvinput.CloneTagStrings;
import org.droidtv.tv.tvinput.ClonechannelCallBack;

import org.droidtv.htv.provider.HtvContract.HtvChannelList;
import org.droidtv.htv.provider.HtvContract;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.euinstallertc.model.mwapi.IntKeyValueablesPrivate;
import org.droidtv.euinstallertc.model.mwapi.TvContractPrivate;

import android.database.Cursor;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.AsyncTask;
import android.content.ContentProviderOperation;
import android.content.OperationApplicationException;
import android.os.RemoteException;
import android.content.ContentProviderResult;
import android.util.Log;
import android.content.ContentValues;
import android.content.ContentUris;
import android.net.Uri;
import android.content.UriMatcher;

import java.util.ArrayList;
import java.util.List;

public class ClonechannelService extends Service{

	public static final String ACTION_BIND = "org.droidtv.action.ACTION_CLONE_INSTALL";
	private static final String TAG        = "ClonechannelService";
	private Context mContext;
	private ClonechannelCallBack  mainClonechannelCallBack			= null; 
    private ArrayList<CloneChannelData> mCloneDataList = new ArrayList<CloneChannelData>(); 
    private CloneChannelData mCloneData = null; 
    private CloneChannelTask mCloneTask = null;

    private long mCursorId = 0;
    private boolean bCopyFromUSB = false;
 
	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		Log.d(TAG, "onCreate");
		mContext = this;
	}

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		if (intent.getAction().equals(ACTION_BIND)) {
			Log.d(TAG, "onBind");
			return new ClonechannelServiceImpl();
		}
		return null;
	}

	@Override  
	public void onDestroy() { 
		super.onDestroy();  
	}  


	private class ClonechannelServiceImpl extends  Clonechannel.Stub
	{ 
		@Override
		public void installCloneChannelApi(String type, ClonechannelParam param, boolean islast)
		{
	        if(islast != true) {
                mCloneData = new CloneChannelData(type, param);
                mCloneDataList.add(mCloneData);
            }else {
                /*store the last channel data*/
                mCloneData = new CloneChannelData(type, param);
                mCloneDataList.add(mCloneData);
                Log.d(TAG, "All data has stored to array-list, channel size = " + mCloneDataList.size());
                mCloneTask = new CloneChannelTask();
                mCloneTask.execute();
            }
		}

		@Override
		public void registerCallback(ClonechannelCallBack callback) throws RemoteException
		{
			mainClonechannelCallBack = callback;
		}
        
        @Override  /*This API is useless*/
	    public void setCursorId(boolean copyFromUSB, long cursorId) {
            bCopyFromUSB = copyFromUSB;
            mCursorId = cursorId;
        }
        
        @Override  
	    public void installJapitCh() {
            int addChNum = mCloneDataList.size();
	        Log.d(TAG, "Japit add channel num " + addChNum);
            if(addChNum > 0) {
                mCloneTask = new CloneChannelTask();
                mCloneTask.execute();
            }else {
				Log.d(TAG, "There is no channel in the list");
            }
        }
	}

	private byte[] FormBlobData (ClonechannelParam TvpData) {
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		byte[]	BlobData = null;
		String sMediumDVBT = "TYPE_DVB_T", sMediumDVBT2 = "TYPE_DVB_T2", sMediumDVBC = "TYPE_DVB_C";
		keyvalues.put (ITvContractExtras.C_PRESETPTC                 , 0);
		keyvalues.put (ITvContractExtras.C_DPTSID                    , 0);
		keyvalues.put (ITvContractExtras.C_DPSID                     , 0);
		keyvalues.put (ITvContractExtras.C_TPID                      , 0);
		keyvalues.put (ITvContractExtras.C_PLPID                     , 0);
		keyvalues.put (ITvContractExtras.C_FREQUENCY                 , TvpData.getFrequency());
		keyvalues.put (ITvContractExtras.C_BANDWIDTH                 , TvpData.getBandwidth());
		keyvalues.put (ITvContractExtras.C_SYMBOLRATE                , TvpData.getSymbolRate());
		keyvalues.put (ITvContractExtras.C_MODULATION                , TvpData.getModulationType());
		keyvalues.put (ITvContractExtras.C_STREAMPRIORITY            , 0);
		keyvalues.put (ITvContractExtras.C_NUMERICSELECT             , 1);
		keyvalues.put (ITvContractExtras.C_SCRAMBLED                 , 0);
		keyvalues.put (ITvContractExtras.C_USEROVERRULEDLOGOURI      , 0);
		keyvalues.put (ITvContractExtras.C_USEROVERRULEDCHANNELNAME  , 0);
		keyvalues.put (ITvContractExtras.C_HBBTVON                   , 1);
		keyvalues.put (ITvContractExtras.C_USERHIDDEN                , 0);
		keyvalues.put (ITvContractExtras.C_NEWPRESET                 , 1);
		keyvalues.put (ITvContractExtras.C_CNINETWORK_ID             , 0);
		keyvalues.put (ITvContractExtras.C_AUDIOPID                  , 8191);
		keyvalues.put (ITvContractExtras.C_VIDEOPID                  , 8191);
		keyvalues.put (ITvContractExtras.C_PCRPID                    , 8191);
		keyvalues.put (ITvContractExtras.C_VIDEOSTREAMTYPE           , 0);
		keyvalues.put (ITvContractExtras.C_AUDIOSTREAMTYPE           , 0);
		keyvalues.put (ITvContractExtras.C_TXTPAGES                  , 2047);
		keyvalues.put (ITvContractExtras.C_SERVICEIDENTIFIER         , Integer.parseInt(TvpData.getServiceId())); // interger or string?
		keyvalues.put (ITvContractExtras.C_PACKAGEGROUP              , 0);
		keyvalues.put (ITvContractExtras.C_DATASLICEID               , 0);
		keyvalues.put (ITvContractExtras.C_PARENTAL_RATING           , 0);
		keyvalues.put (ITvContractExtras.C_NetworkId                 , 0);
		keyvalues.put (ITvContractExtras.C_TXTSUBPAGE                , 0);
		keyvalues.put (ITvContractExtras.C_SAP                       , 0);
		keyvalues.put (ITvContractExtras.C_PreferredStereo           , 1);
		keyvalues.put (ITvContractExtras.C_LNBNUMBER                 , 0);
		keyvalues.put (ITvContractExtras.C_LCN                       , 0);
		keyvalues.put (ITvContractExtras.C_PMTPID                    , 8191);
		keyvalues.put (ITvContractExtras.C_SECONDARY_AUDIOPID        , 0);
		keyvalues.put (ITvContractExtras.C_SECONDARY_AUDIOSTREAMTYPE , 0);
		keyvalues.put (ITvContractExtras.C_DATETIMESTAMP             , 0);
		keyvalues.put (ITvContractExtras.C_FREECIMODE                , 0);
		keyvalues.put (ITvContractExtras.C_MATCH_BRANDID             , 0);
		keyvalues.put (ITvContractExtras.C_BRANDIDS                  , 0);
		keyvalues.put (ITvContractExtras.C_FECINNER                  , 0);
		keyvalues.put (ITvContractExtras.C_ROLLOFF                   , 0);
		keyvalues.put (ITvContractExtras.C_LOGOID                    , 0);

		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();

		privatekeyvalues.put (TvContractPrivate.C_TS_VERSION, -1);
		if (TvpData.getMediumType().equalsIgnoreCase(sMediumDVBT) ||
				TvpData.getMediumType().equalsIgnoreCase(sMediumDVBT2) ||
				TvpData.getMediumType().equalsIgnoreCase(sMediumDVBC)) {
			Log.d(TAG, "[fenghsu] Set Type to 3!!");
			privatekeyvalues.put(TvContractPrivate.C_TYPE, 3); //Must set to onepart channel
		}
		privatekeyvalues.put(TvContractPrivate.C_ANALOG_TABLE_PRESET, TvpData.getPresetNumber());

		keyvalues.put(ITvContractExtras.C_INSTALLER_BLOB, privatekeyvalues.getBlob());

		try {
			BlobData = keyvalues.getBlob();
		} catch (Exception e) {
			Log.e(TAG, "Error FormBlobData  " + e);
		}
		return BlobData;
	}

	private class CloneChannelData {
		private ClonechannelParam mChParam;
		private String mChType;
		public CloneChannelData(String type,ClonechannelParam param)
		{
			this.mChType = type;
			this.mChParam = param;
		}
    }

	private class CloneChannelTask extends AsyncTask<Void, Void, Void> 
	{
        private CloneChannelData mChData;
        private int mCopyNum = 0; 
		private ClonechannelParam mChParam;
		private String mChType;
		private ContentValues[] bulkToInsert = null;
        private long id = 0; 
        private int htvInserted = 0;
 
        private int mChNum = mCloneDataList.size(); 
        private int ChIndex = 0, mChInserted = 0, mChInsertStep = 100;
 
		@Override
		protected Void doInBackground(Void... arg0)
	    {
            try {
                /* CopyFromUSB = true, get cursor id from cloneservice, handle copyfromusb case
	             * CopyFromUSB = false, get cursor id from GetTvDbCursorId, handle japit/sxp case  */
                if(bCopyFromUSB) {
                    Log.d(TAG, "Clone Channel From Clone Service");
                    id = mCursorId;
                }else {
                    Log.d(TAG, "Clone Channel From Japit/Sxp");
                    id = mCursorId;
	                //id = GetTvDbCursorId();
                }
                Log.d(TAG, "Cursor id = " + id);
                 
				for(mChInserted = 0; mChInserted < mChNum; mChInserted = (mChInserted + mChInsertStep)) {
					if((mChNum - mChInserted) < mChInsertStep) {
						mChInsertStep = mChNum - mChInserted;
					}

					ContentValues[] val = new ContentValues[mChInsertStep];   
					ContentValues[] htvVal = new ContentValues[mChInsertStep];   

					for(ChIndex = 0; ChIndex < mChInsertStep; ChIndex++) {                    
						mChData = mCloneDataList.get(ChIndex + mChInserted);
						mChType = mChData.mChType;
						mChParam = mChData.mChParam;
						CopyDataToTvProvider(val, htvVal);
					}

					mCopyNum = mContext.getContentResolver().bulkInsert(TvContract.Channels.CONTENT_URI, val);
					Log.d(TAG, "Copy Channel, [TV]mChInserted " + mChInserted + ", step " + mChInsertStep + ", copyed " + mCopyNum);

					SyncHtvListDb(htvVal, mChInsertStep);
				}
            }catch(Exception e) {
                Log.e(TAG, "CopyDataToTvProvider failed " + e);
				e.printStackTrace();
            }

			if (mainClonechannelCallBack !=null)
			{
				try 
				{					
					mainClonechannelCallBack.onCompelete();
				} catch (RemoteException e) 
				{
					e.printStackTrace();
				}
			}
			mCloneDataList.clear();
            return null;
        }

        private void SyncHtvListDb(ContentValues[] htv, int step) {
            int rowNum = 0;
            int index = 0;
            int preCursorId = 0;
			Cursor cursor = null;
			String[] mProjection = { TvContract.Channels._ID };
			String mSortOrder = "CAST( " + Channels._ID+ " AS INTEGER ) ASC";
			try { 
				cursor = mContext.getContentResolver().query(TvContract.Channels.CONTENT_URI, mProjection, null, null, mSortOrder);
                cursor.moveToFirst();
				if(cursor != null) {
					rowNum = cursor.getCount();
                    /*before insert db, there is channel data in tv.db*/
                    if(rowNum > step) { 
                        if(htvInserted > 0)
                            preCursorId = rowNum - (rowNum - htvInserted);
                        else 
                            preCursorId = (rowNum - step);
                    }else if (rowNum == step){  /*before insert db, tv.db had cleared*/
                        preCursorId = htvInserted;
                    }
					Log.d(TAG, "Row num=" + rowNum + ", previous cursor=" + preCursorId +", insert step=" + step + ",htv insert=" + htvInserted);

                    cursor.moveToPosition(preCursorId);

                    do {
						if(index < step) {
							//rewrite previous cursorId
							htv[index].put (HtvContract.HtvChannelSetting._ID, cursor.getInt(0));
							htv[index].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID, cursor.getInt(0));
                            Log.d(TAG, "index = "  + index + "cursorID = " + cursor.getInt(0));
						}
                        index++;
					}while(cursor.moveToNext() == true);
                    
                    mCopyNum = mContext.getContentResolver().bulkInsert(HtvContract.HtvChannelSetting.CONTENT_URI, htv);
					Log.d(TAG, "Copy Channel, [HTV]htv inserted " + htvInserted + ", copyed " + mCopyNum);
				    htvInserted = htvInserted + step; 
                }
 
			}finally {
				if(cursor != null) {
					cursor.close();
					cursor = null;
				}
			}
        }

	    private void CopyDataToTvProvider(ContentValues[] val, ContentValues[] valHtv)
		{	
			Log.d(TAG, "CopyDataToTvProvider run, channel type = " + mChType + ", id = " + id);
            val[ChIndex] = new ContentValues();  
            valHtv[ChIndex] = new ContentValues();  
			if (mChType.equals(CloneTagStrings.TAG_BROADCAST))
			{
				val[ChIndex].put (TvContract.Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService"); /* Check with Mounesh/Pavan what to fill here */
				val[ChIndex].put (TvContract.Channels.COLUMN_TYPE,mChParam.getMediumType());
				val[ChIndex].put (TvContract.Channels.COLUMN_SERVICE_TYPE,mChParam.getServiceType());
				Log.d(TAG, "TAG_BROADCAST"+"getMediumType"+mChParam.getMediumType()+ "COLUMN_SERVICE_TYPE"+mChParam.getServiceType()); 
				val[ChIndex].put (TvContract.Channels.COLUMN_NETWORK_AFFILIATION , "");
				val[ChIndex].put (TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID,mChParam.getONID());
				val[ChIndex].put (TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID,mChParam.getTSID());
				val[ChIndex].put (TvContract.Channels.COLUMN_SERVICE_ID,mChParam.getServiceId());
				val[ChIndex].put (TvContract.Channels.COLUMN_DISPLAY_NUMBER,mChParam.getPresetNumber());
				val[ChIndex].put (TvContract.Channels.COLUMN_DISPLAY_NAME,mChParam.getName());
				val[ChIndex].put (TvContract.Channels.COLUMN_DESCRIPTION,""); /* See if we can put medium information here */
				val[ChIndex].put (TvContract.Channels.COLUMN_BROWSABLE, 1);
				val[ChIndex].put (TvContract.Channels.COLUMN_SEARCHABLE,1);
				val[ChIndex].put (TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA,FormBlobData(mChParam));
				if (mChParam.getPayPKG1().equals("1") || mChParam.getPayPKG2().equals("1") ) {//pay1/pay2
					val[ChIndex].put(TvContract.Channels.COLUMN_LOCKED, 1);
					Log.d(TAG, "COLUMN_LOCKED 1"); 

				} else { //free
					val[ChIndex].put(TvContract.Channels.COLUMN_LOCKED, 0);
					Log.d(TAG, "COLUMN_LOCKED 0"); 
				}
				if (mChParam.getMediumType().equals(TvContract.Channels.TYPE_DVB_T) || mChParam.getMediumType().equals(TvContract.Channels.TYPE_DVB_T2) )
				{
					val[ChIndex].put (TvContract.Channels.COLUMN_VERSION_NUMBER,0);
				}
				else if (mChParam.getMediumType().equals(TvContract.Channels.TYPE_DVB_C))
				{
					val[ChIndex].put (TvContract.Channels.COLUMN_VERSION_NUMBER,1);
				}
				else if (mChParam.getMediumType().equals(TvContract.Channels.TYPE_DVB_S))
				{
					val[ChIndex].put (TvContract.Channels.COLUMN_VERSION_NUMBER,2);
				}
				else if (mChParam.getMediumType().equals(TvContract.Channels.TYPE_PAL))//analog
				{
					val[ChIndex].put (TvContract.Channels.COLUMN_VERSION_NUMBER,0);
				}


				valHtv[ChIndex].put (HtvContract.HtvChannelSetting._ID                   , id);
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER , mChParam.getPresetNumber());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE     , "TYPE_TUNER");
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_BLANK          , mChParam.getBlank());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_SKIP1          , mChParam.getSkip());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_FREEPKG        , mChParam.getFreePKG());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG1        , mChParam.getPayPKG1());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG2        , mChParam.getPayPKG2());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER     , mChParam.getTTV1order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER     , mChParam.getTTV2order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER     , mChParam.getTTV3order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER     , mChParam.getTTV4order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER     , mChParam.getTTV5order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER     , mChParam.getTTV6order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER     , mChParam.getTTV7order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER     , mChParam.getTTV8order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER     , mChParam.getTTV9order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER    , mChParam.getTTV10order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_LOGO_URL    , mChParam.getLogoURL());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID      , id);
			}
			else if (mChType.equals(CloneTagStrings.TAG_SOURCE))
			{
				String source_type = mChParam.getSoureType();
				String source_uri = "";
				IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();

				if (source_type.equals("HDMI1")) {
					source_uri = "org.droidtv.hdmiService/.HdmiService/HW9";
				} else if (source_type.equals("HDMI2")) {
					source_uri = "org.droidtv.hdmiService/.HdmiService/HW10";
				} else if (source_type.equals("HDMI3")) {
					source_uri = "org.droidtv.hdmiService/.HdmiService/HW11";
				} else if (source_type.equals("HDMI4")) {
					source_uri = "org.droidtv.hdmiService/.HdmiService/HW12";
				} else if (source_type.equals("YPBPR")) {
					source_uri = "org.droidtv.componentService/.ComponentService/HW4";
				} else if (source_type.equals("SCART")) {
					source_uri = "org.droidtv.scartService/.ScartService/HW7";
				} 

				val[ChIndex].put (TvContract.Channels.COLUMN_INPUT_ID,"2"); /* Check with Mounesh/Pavan what to fill here */
				val[ChIndex].put (TvContract.Channels.COLUMN_TYPE,TvContract.Channels.TYPE_OTHER);
				val[ChIndex].put (TvContract.Channels.COLUMN_SERVICE_TYPE,TvContract.Channels.SERVICE_TYPE_AUDIO_VIDEO);
				val[ChIndex].put (TvContract.Channels.COLUMN_NETWORK_AFFILIATION , "");
				val[ChIndex].put (TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID,"0");
				val[ChIndex].put (TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID,"0");
				val[ChIndex].put (TvContract.Channels.COLUMN_SERVICE_ID,"65535");
				val[ChIndex].put (TvContract.Channels.COLUMN_DISPLAY_NUMBER,mChParam.getPresetNumber());
				val[ChIndex].put (TvContract.Channels.COLUMN_DISPLAY_NAME,mChParam.getName());
				val[ChIndex].put (TvContract.Channels.COLUMN_DESCRIPTION,""); /* See if we can put medium information here */
				val[ChIndex].put (TvContract.Channels.COLUMN_BROWSABLE, 1);
				val[ChIndex].put (TvContract.Channels.COLUMN_SEARCHABLE,1);

				keyvalues.put(ITvContractExtras.C_URI_BLOB, source_uri);
				Log.d(TAG, "Going to form blob ");
				try {
					val[ChIndex].put (TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA,keyvalues.getBlob());
				} catch (Exception e) {
					Log.e(TAG, "Error FormBlobData  " + e);
					e.printStackTrace();
				}
				val[ChIndex].put (TvContract.Channels.COLUMN_VERSION_NUMBER,"10");


				valHtv[ChIndex].put (HtvContract.HtvChannelSetting._ID                   , id);
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER , mChParam.getPresetNumber());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE     , "TYPE_SOURCE");

				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_BLANK          , mChParam.getBlank());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_SKIP1          , mChParam.getSkip());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_FREEPKG        , mChParam.getFreePKG());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG1        , mChParam.getPayPKG1());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG2        , mChParam.getPayPKG2());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER     , mChParam.getTTV1order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER     , mChParam.getTTV2order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER     , mChParam.getTTV3order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER     , mChParam.getTTV4order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER     , mChParam.getTTV5order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER     , mChParam.getTTV6order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER     , mChParam.getTTV7order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER     , mChParam.getTTV8order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER     , mChParam.getTTV9order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER    , mChParam.getTTV10order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_LOGO_URL    , mChParam.getLogoURL());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID      , id);
			}
			else if (mChType.equals(CloneTagStrings.TAG_MULTICAST) )
			{
				IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
				val[ChIndex].put (TvContract.Channels.COLUMN_INPUT_ID,"2"); /* Check with Mounesh/Pavan what to fill here */
				val[ChIndex].put (TvContract.Channels.COLUMN_TYPE,TvContract.Channels.TYPE_OTHER);
				val[ChIndex].put (TvContract.Channels.COLUMN_SERVICE_TYPE,TvContract.Channels.SERVICE_TYPE_AUDIO_VIDEO);
				val[ChIndex].put (TvContract.Channels.COLUMN_NETWORK_AFFILIATION , "");

				//val[ChIndex][ChIndex].put (TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID,"0");
				//val[ChIndex][ChIndex].put (TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID,"0");
				val[ChIndex].put (TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID,mChParam.getONID());
				val[ChIndex].put (TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID,mChParam.getTSID());
				val[ChIndex].put (TvContract.Channels.COLUMN_SERVICE_ID,mChParam.getServiceId());
				val[ChIndex].put (TvContract.Channels.COLUMN_BROWSABLE,"1");
				//val[ChIndex][ChIndex].put (TvContract.Channels.COLUMN_SERVICE_ID,"65535");
				val[ChIndex].put (TvContract.Channels.COLUMN_DISPLAY_NUMBER,mChParam.getPresetNumber());
				val[ChIndex].put (TvContract.Channels.COLUMN_DISPLAY_NAME,mChParam.getName());
				keyvalues.put(ITvContractExtras.C_URI_BLOB, mChParam.geturl());
				keyvalues.put (ITvContractExtras.C_HBBTVON, 1);
				try {
					val[ChIndex].put (TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA,keyvalues.getBlob());
				} catch (Exception e) {
					Log.e(TAG, "Error FormBlobData  " + e);
					e.printStackTrace();
				}
				val[ChIndex].put (TvContract.Channels.COLUMN_VERSION_NUMBER,"11");

				valHtv[ChIndex].put (HtvContract.HtvChannelSetting._ID                   , id);
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER , mChParam.getPresetNumber());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE     , mChParam.getSoureType());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_BLANK          , mChParam.getBlank());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_SKIP1          , mChParam.getSkip());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_FREEPKG        , mChParam.getFreePKG());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG1        , mChParam.getPayPKG1());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG2        , mChParam.getPayPKG2());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER     , mChParam.getTTV1order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER     , mChParam.getTTV2order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER     , mChParam.getTTV3order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER     , mChParam.getTTV4order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER     , mChParam.getTTV5order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER     , mChParam.getTTV6order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER     , mChParam.getTTV7order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER     , mChParam.getTTV8order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER     , mChParam.getTTV9order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER    , mChParam.getTTV10order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_LOGO_URL    , mChParam.getLogoURL());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID      , id);
			}
			else if ( mChType.equals(CloneTagStrings.TAG_MEDIA))
			{
				IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
				val[ChIndex].put (TvContract.Channels.COLUMN_INPUT_ID,"2"); /* Check with Mounesh/Pavan what to fill here */
				val[ChIndex].put (TvContract.Channels.COLUMN_TYPE,TvContract.Channels.TYPE_OTHER);
				val[ChIndex].put (TvContract.Channels.COLUMN_SERVICE_TYPE,TvContract.Channels.SERVICE_TYPE_OTHER);
				val[ChIndex].put (TvContract.Channels.COLUMN_NETWORK_AFFILIATION , "");
				val[ChIndex].put (TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID,"0");
				val[ChIndex].put (TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID,"0");
				val[ChIndex].put (TvContract.Channels.COLUMN_SERVICE_ID,"65535");
				val[ChIndex].put (TvContract.Channels.COLUMN_DISPLAY_NUMBER,mChParam.getPresetNumber());
				val[ChIndex].put (TvContract.Channels.COLUMN_DISPLAY_NAME,mChParam.getName());
				keyvalues.put(ITvContractExtras.C_URI_BLOB, mChParam.geturl());
				try {
					val[ChIndex].put (TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA,keyvalues.getBlob());
				} catch (Exception e) {
					Log.e(TAG, "Error FormBlobData  " + e);
					e.printStackTrace();
				}
				val[ChIndex].put (TvContract.Channels.COLUMN_VERSION_NUMBER,"12");
				val[ChIndex].put (TvContract.Channels.COLUMN_BROWSABLE, "1");

				
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting._ID                   , id);
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER , mChParam.getPresetNumber());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE     , "TYPE_FILE");
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_BLANK          , mChParam.getBlank());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_SKIP1          , mChParam.getSkip());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_FREEPKG        , mChParam.getFreePKG());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG1        , mChParam.getPayPKG1());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_PAYPKG2        , mChParam.getPayPKG2());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV1_ORDER     , mChParam.getTTV1order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV2_ORDER     , mChParam.getTTV2order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV3_ORDER     , mChParam.getTTV3order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV4_ORDER     , mChParam.getTTV4order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV5_ORDER     , mChParam.getTTV5order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV6_ORDER     , mChParam.getTTV6order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV7_ORDER     , mChParam.getTTV7order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV8_ORDER     , mChParam.getTTV8order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV9_ORDER     , mChParam.getTTV9order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_TTV10_ORDER    , mChParam.getTTV10order());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_LOGO_URL    , mChParam.getLogoURL());
				valHtv[ChIndex].put (HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID      , id);
			}
            id++;
		}        
	}

}

