package org.droidtv.tunerservice.util;

import android.media.tv.TvContract;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.tvinput.ITVSessionContext;
import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import java.lang.String;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.tv.video.ITvVideoManager;

import java.io.IOException;
import android.util.Log;
import java.lang.Integer;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

import android.database.Cursor;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;	
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.provider.IFrequencyListContract;


public class TvURIHelper{
	private static final String LOG_TAG = "TvURIHelper";	
													
	private static final String[] PROJECTION_RECORDING =  {
		IRecordingsContract.C_CHANNELID
	};										
	private static final String[] PROJECTION = {
		TvContract.Channels.COLUMN_DISPLAY_NUMBER,
		TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID ,
		TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID,
		TvContract.Channels.COLUMN_SERVICE_ID,
		TvContract.Channels.COLUMN_SERVICE_TYPE,
		TvContract.Channels.COLUMN_TYPE,
		TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA,
		TvContract.Channels.COLUMN_NETWORK_AFFILIATION
	};
	private static final String[] PROJECTION_TRIPLET =  {
		TvContract.Channels._ID,
		TvContract.Channels.COLUMN_DISPLAY_NUMBER,
		TvContract.Channels.COLUMN_SERVICE_ID,
		TvContract.Channels.COLUMN_SERVICE_TYPE,
		TvContract.Channels.COLUMN_TYPE,
		TvContract.Channels.COLUMN_BROWSABLE,
		TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA
	};		
	private static final String[] PROJECTION_FREQUENCY_MAP =  {	
		IFrequencyListContract.ITCFrequencyMap.COLUMN_FREQUENCY,
		IFrequencyListContract.ITCFrequencyMap.COLUMN_SYMBOLRATE,
		IFrequencyListContract.ITCFrequencyMap.COLUMN_MODULATIONTYPE,
		IFrequencyListContract.ITCFrequencyMap.COLUMN_BANDWIDTH
	};
	private static final String SELECTION  = TvContract.Channels._ID+" = ?";
	private static final String SELECTION_RECORDING  	= IRecordingsContract.C_RECORDING_ID+" = ?";
	private static final String SELECTION_MULTIFEED_1 	= TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID + " =?"+" AND " + TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID + " =?"+" AND " + TvContract.Channels.COLUMN_SERVICE_ID + " =?"; 
	private static final String SELECTION_MULTIFEED_2 	= TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID + " =?"+" AND " + TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID + " =?"; 
	private static final String SELECTION_FREQUENCY_MAP = IFrequencyListContract.ITCFrequencyMap.COLUMN_ORIGINALNETWORKID + " =?"+" AND " + IFrequencyListContract.ITCFrequencyMap.COLUMN_TSID + " =?";


	public final static Map<Integer, String> tvURIHeaders = new HashMap<Integer, String>() {{
		put(ITvContractExtras.C_FREQUENCY,TvHeaders.FREQUENCY);
		put(ITvContractExtras.C_SYMBOLRATE,TvHeaders.SYMBOL_RATE);
		put(ITvContractExtras.C_POLARIZATION,TvHeaders.POLARIZATION);
		put(ITvContractExtras.C_LNBNUMBER,TvHeaders.LNB_NUMBER);
		put(ITvContractExtras.C_PLPID,TvHeaders.PLP_ID);
		put(ITvContractExtras.C_BANDWIDTH,TvHeaders.BANDWIDTH);
		put(ITvContractExtras.C_STREAMPRIORITY,TvHeaders.STREAM_PRIORITY);
		put(ITvContractExtras.C_VIDEOPID,TvHeaders.VIDEO_PID);
		put(ITvContractExtras.C_AUDIOPID,TvHeaders.AUDIO_PID);
		put(ITvContractExtras.C_PCRPID,TvHeaders.PCR_PID);
		put(ITvContractExtras.C_VIDEOSTREAMTYPE,TvHeaders.VIDEO_STREAM_TYPE);
		put(ITvContractExtras.C_AUDIOSTREAMTYPE,TvHeaders.AUDIO_STREAM_TYPE);
		put(ITvContractExtras.C_MODULATION,TvHeaders.TV_SYSTEM);
		put(ITvContractExtras.C_PreferredStereo,TvHeaders.PREFERRED_STEREO);
		put(ITvContractExtras.C_SAP,TvHeaders.SAP);
		put(ITvContractExtras.C_FECINNER,TvHeaders.SATIP_FECINNER);
		put(ITvContractExtras.C_ROLLOFF,TvHeaders.SATIP_ROLLOFF); 
	}};	
	
	public static enum Medium {
		MEDIUM_INVALID (-1),
		MEDIUM_SATELLITE (0),
		MEDIUM_CABLE (1),
		MEDIUM_TERRESTRIAL (2),
		MEDIUM_TSFILE(3),
		MEDIUM_PVRFILE(4),
		MEDIUM_EXTN(5),
		MEDIUM_LOCALFILE(6);
		
		public int value;
		
		Medium(int value){
			this.value = value;
		}

		public static Medium fromInteger(int x) {
			switch(x) {
			case 0:
				return MEDIUM_SATELLITE;
			case 1:
				return MEDIUM_CABLE;
			case 2:
				return MEDIUM_TERRESTRIAL;
			case 3:
				return MEDIUM_TSFILE;
			case 4:
				return MEDIUM_PVRFILE;
			case 5:
				return MEDIUM_EXTN;
			case 6:
				return MEDIUM_LOCALFILE;
			default:
				return MEDIUM_INVALID;
			}
		}
	}

	public enum SelectionType {
		SELECTION_INVALID(-1),		
		SELECTION_NORMAL (0),
		SELECTION_DIRECT (1),
		SELECTION_SILENT (2),
		SELECTION_INSTALL (3),
		SELECTION_MULTIFEED (4),
		SELECTION_NDT (5),
		SELECTION_DEFAULT (6),
		SELECTION_BREAKIN (7),
		SELECTION_CAMPMT(8),
		SELECTION_HOSTCONTROL(9);
		
		public int value;
		
		SelectionType (int value) {
			this.value = value;
		}
		public static SelectionType fromInteger(int parseInt) {
			switch(parseInt)
			{
				case 0:  return SELECTION_NORMAL;
				case 1:  return SELECTION_DIRECT;
				case 2:  return SELECTION_SILENT;
				case 3:  return SELECTION_INSTALL;
				case 4:  return SELECTION_MULTIFEED;
				case 5:  return SELECTION_NDT;
				case 6:  return SELECTION_DEFAULT;
				case 7:  return SELECTION_BREAKIN;
				case 8:  return SELECTION_CAMPMT;
				case 9:  return SELECTION_HOSTCONTROL;
				default: return SELECTION_INVALID;
			}
		}
	}
	
	public enum TvUriTypeEnum
	{   INVALID(-1),
		SEL_DEFAULT(0),
		SEL_DEFAULT_MEDIUM_CHANNEL(1),
		SEL_MEDIUM_DEFAULT_CHANNEL(2),
		SEL_MEDIUM_CHANNEL(3),
		SEL_ONID_TSID_SID(4),
		SEL_MOD_FREQUENCY(5),
		SEL_ONID_TSID_SID_TPID(6),
		SEL_PVR_FILE(7),
		SEL_EXTN_DEFAULT(11), 
		SEL_EXTN_SOURCE(12), 
		SEL_EXTN_SOURCE_PHYADD(13),
		SEL_MOD_FREQUENCY_STREAMPRIORITY(21),
		SEL_USER_PARAMETERS(22);
	
		private int value;
		
		TvUriTypeEnum(int value)
		{
			this.value = value;
		}

		public static TvUriTypeEnum fromInteger(int parseInt) {
			switch(parseInt)
			{
				case 0:  return SEL_DEFAULT; 
				case 1:  return SEL_DEFAULT_MEDIUM_CHANNEL;
				case 2:  return SEL_MEDIUM_DEFAULT_CHANNEL;
				case 3:  return SEL_MEDIUM_CHANNEL;
				case 4:  return SEL_ONID_TSID_SID;
				case 5:  return SEL_MOD_FREQUENCY;
				case 6:  return SEL_ONID_TSID_SID_TPID;
				case 7:  return SEL_PVR_FILE;	
				case 11: return SEL_EXTN_DEFAULT;
				case 12: return SEL_EXTN_SOURCE;
				case 13: return SEL_EXTN_SOURCE_PHYADD;
				case 21: return SEL_MOD_FREQUENCY_STREAMPRIORITY;
				case 22: return SEL_USER_PARAMETERS;
				default: return INVALID;
			}
		}
	}

	public static class UriData {
		public Uri uri;		
		public int medium = -1;		
		public int seltype = -1;		
		public int modulation = -1;		
		public int channel = -1;
		public int onid = -1;
		public int tsid = -1;
		public int sid = -1;
		public int tpid = -1;
		public int frequency = -1;
		public int bandwidth = -1;
		public int symbolrate = -1;				
		public int streamPriority = -1;
		public int recId = -1;
		public int tvuritype =-1;
		public int polarization = -1; 
		public int lnbnumber = -1; 
		public int vpid = -1; 
		public int apid = -1; 
		public int pcrpid = -1; 
		public int videostreamtype = -1;
		public int audiostreamtype = -1;
		public int mode = -1;
		
		public void dump(){
			String TAG = "UriData";
			if(uri!=null) {
				Log.d(TAG,"uri" + uri.toString());
				Log.d(TAG,"medium" + medium);
				Log.d(TAG,"seltype" + seltype);
				Log.d(TAG,"modulation " + modulation);
				Log.d(TAG,"channel" + channel);
				Log.d(TAG,"onid" + onid);
				Log.d(TAG,"tsid" + tsid);
				Log.d(TAG,"sid" + sid);
				Log.d(TAG,"freq" + frequency);
				Log.d(TAG,"bandwidth" + bandwidth);
				Log.d(TAG,"symbolrate" + symbolrate);
				Log.d(TAG,"streamPriority" + streamPriority);
				Log.d(TAG,"bandwidth" + bandwidth);
				Log.d(TAG,"mode" + mode);
				Log.d(TAG,"vpid" + vpid);
				Log.d(TAG,"apid" + apid);
				Log.d(TAG,"pcrpid" + pcrpid);
				Log.d(TAG,"videostreamtype" + videostreamtype);
				Log.d(TAG,"audiostreamtype" + audiostreamtype);
				Log.d(TAG,"polarization" + polarization);
			}
		}
	}
			
	public static UriData parseUri(Context context, Uri uri){
		UriData uriData = new UriData();
		Log.d(LOG_TAG,"parseUri");
		if(!TvContract.isChannelUriForTunerInput(uri)){
			Log.d(LOG_TAG,"parse Uri for recording");
			uriData.recId = Integer.parseInt(uri.getLastPathSegment());
			Log.d(LOG_TAG,"Recording id is "+uriData.recId);
			String [] selectionArgs = {Integer.toString(uriData.recId)};
			Cursor cursor=null;
            try	{
			   cursor   = context.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings,PROJECTION_RECORDING,SELECTION_RECORDING,selectionArgs, null);
			   if((cursor != null) && (cursor.moveToFirst()) ) {
				  uriData.channel = Integer.parseInt(cursor.getString(cursor.getColumnIndex(IRecordingsContract.C_CHANNELID)));
				  uriData.medium = Medium.MEDIUM_PVRFILE.value;
			   }else{
				  Log.d(LOG_TAG,"Cursor not received for recording playback");
				  return null;
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
			return uriData;
		}		
		int uniqueId    = Integer.parseInt(uri.getLastPathSegment());	
		String [] selectionArgs = {Integer.toString(uniqueId)};//{(new Integer(uniqueId)).toString()};
		Cursor cursor=null;
		try{
		cursor   = context.getContentResolver().query(TvContract.Channels.CONTENT_URI,PROJECTION,SELECTION,selectionArgs, null);
		if(cursor != null) {
			if((cursor.getCount() > 0) && cursor.moveToFirst()) {
				uriData.channel = Integer.parseInt(cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_DISPLAY_NUMBER)));
				uriData.onid    = Integer.parseInt(cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_ORIGINAL_NETWORK_ID)));
				uriData.tsid    = Integer.parseInt(cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_TRANSPORT_STREAM_ID)));
				uriData.sid     = Integer.parseInt(cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_SERVICE_ID)));
				try {
					String typeval = cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_TYPE));
					Log.d(LOG_TAG,"typeval" + typeval);
				
					if(typeval.equals(TvContract.Channels.TYPE_DVB_T) ||
							typeval.equals(TvContract.Channels.TYPE_DVB_T2)){
						uriData.medium = Medium.MEDIUM_TERRESTRIAL.value;
					}
					else if(typeval.equals(TvContract.Channels.TYPE_DVB_S) ||
							typeval.equals(TvContract.Channels.TYPE_DVB_S2)){
						uriData.medium = Medium.MEDIUM_SATELLITE.value;
					}
					else if(typeval.equals(TvContract.Channels.TYPE_DVB_C) ||
							typeval.equals(TvContract.Channels.TYPE_DVB_C2)){
						uriData.medium = Medium.MEDIUM_CABLE.value;
					}
					else if(typeval.equals(TvContract.Channels.TYPE_PAL)){
						uriData.medium = PlayTvUtils.getCurrentMedium().value;
					}
				}catch(Exception e){
					Log.d(LOG_TAG,"parse URI : Exception : " +e.toString());
				}
				
				byte[] lInternalData		 = cursor.getBlob(cursor.getColumnIndex(TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA));
				IIntKeyValueables keyvals	 = IIntKeyValueables.Instance.getInterface();
				
				try{
					keyvals.setBlob(lInternalData);
				}catch(IOException e){
					Log.d(LOG_TAG, "parseBlobData - CAUGHT EXCEPTION keyvals=null");
					keyvals = null;
				}catch(ClassNotFoundException e){
					Log.d(LOG_TAG, "parseBlobData - CAUGHT EXCEPTION keyvals=null");
					keyvals = null;
				}											
					
				if(keyvals != null){
					uriData.frequency		= keyvals.getInt(ITvContractExtras.C_FREQUENCY);
					uriData.bandwidth		= keyvals.getInt(ITvContractExtras.C_BANDWIDTH);
					uriData.symbolrate  	= keyvals.getInt(ITvContractExtras.C_SYMBOLRATE);
				}
			}
		}else {
			Log.d(LOG_TAG, "curson null or getCount 0!!!");
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
		return uriData;
	}
	
	public static Map<String, String> getUriHeaders(Context context, Uri uri) {
		Map<String, String> headers	= null;
		Log.d(LOG_TAG, "getUriHeaders :  uri - "+uri);
		if(TvContract.isChannelUriForTunerInput(uri)) {
			int _id = Integer.parseInt(uri.getLastPathSegment());	
			String [] selectionArgs = {Integer.toString(_id)};
			String selection  = TvContract.Channels._ID + " = ?";
			Cursor cursor=null;
			try{
			Log.d(LOG_TAG,"[!!!]: getUriHeaders :  get cursor.");
			cursor= context.getContentResolver().query(TvContract.Channels.CONTENT_URI,PROJECTION,
					selection, selectionArgs, null);
			
			if(cursor!=null){
				Log.d(LOG_TAG,"[!!!]: getUriHeaders :  cursor != null . count: " + cursor.getCount());
				if((cursor.getCount()>0) && (cursor.moveToFirst())){
					headers = new HashMap<String, String>();
					headers.put(TvHeaders.UNIQUE_ID,Integer.toString(_id));
					headers.put(TvHeaders.COMPLETE_URI,uri.toString());					
					headers.put(TvHeaders.PRESET_ID,cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_DISPLAY_NUMBER)));
					headers.put(TvHeaders.SERVICE_ID,cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_SERVICE_ID)));
					headers.put(TvHeaders.SERVICE_TYPE,cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_SERVICE_TYPE)));
					headers.put(TvHeaders.CHANNEL_ID,Integer.toString(_id));
					if(cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_NETWORK_AFFILIATION)) != null){
						headers.put(TvHeaders.NEW_PRESET,cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_NETWORK_AFFILIATION)));
					}
					
					/*fill medium - conversion needed*/
					String cType 	= cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_TYPE));
					int medium 		= Medium.MEDIUM_TERRESTRIAL.value;
					int mode		= TvHeaders.MODE_DVBT;
					
					if(cType != null) {
						if((cType.equals(TvContract.Channels.TYPE_DVB_T))) {
							medium	=	Medium.MEDIUM_TERRESTRIAL.value;
							mode	=	TvHeaders.MODE_DVBT;
						}
						else if((cType.equals(TvContract.Channels.TYPE_DVB_T2))){
							medium	=	Medium.MEDIUM_TERRESTRIAL.value;
							mode	=	TvHeaders.MODE_DVBT2;
						}
						else if((cType.equals(TvContract.Channels.TYPE_DVB_C)) ||
								(cType.equals(TvContract.Channels.TYPE_DVB_C2)) ){
							medium	=	Medium.MEDIUM_CABLE.value;
							mode	=	TvHeaders.MODE_DVBC;
						}
						else if((cType.equals(TvContract.Channels.TYPE_DVB_S)) ||
								(cType.equals(TvContract.Channels.TYPE_DVB_S2))){
							medium	=	Medium.MEDIUM_SATELLITE.value;
							mode	=	TvHeaders.MODE_DVBS;
						}
						else if(cType.equals(TvContract.Channels.TYPE_PAL)){
							medium	=	Medium.MEDIUM_TERRESTRIAL.value;
							mode	=	TvHeaders.MODE_ANALOG;
						}
						else if(cType.equals(TvContract.Channels.TYPE_OTHER)){
							medium	=	Medium.MEDIUM_LOCALFILE.value;
							mode	=	TvHeaders.MODE_LOCAL_FILE;
						}
						
					}else {
						Log.d(LOG_TAG, "ColumnType=null !!!");
					}
					headers.put(TvHeaders.MEDIUM,Integer.toString(medium));
					headers.put(TvHeaders.MODE,Integer.toString(mode));
					
					/*fill TvProvider internal blob data*/
					byte[] lInternalData		 = cursor.getBlob(cursor.getColumnIndex(TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA));
					IIntKeyValueables keyvals	 = IIntKeyValueables.Instance.getInterface();				
					try{
						keyvals.setBlob(lInternalData);						
						headers.put(TvHeaders.FREQUENCY,Integer.toString(keyvals.getInt(ITvContractExtras.C_FREQUENCY)));
						headers.put(TvHeaders.SYMBOL_RATE,Integer.toString(keyvals.getInt(ITvContractExtras.C_SYMBOLRATE)));
						headers.put(TvHeaders.BANDWIDTH,Integer.toString(keyvals.getInt(ITvContractExtras.C_BANDWIDTH)));
						headers.put(TvHeaders.PREFERRED_STEREO,Integer.toString(keyvals.getInt(ITvContractExtras.C_PreferredStereo)));
						headers.put(TvHeaders.SAP,Integer.toString(keyvals.getInt(ITvContractExtras.C_SAP)));
						
		
						if(mode == TvHeaders.MODE_ANALOG) {
							headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_ANALOG));
							headers.put(TvHeaders.TV_SYSTEM,Integer.toString(keyvals.getInt(ITvContractExtras.C_MODULATION)));
						}else if(mode == TvHeaders.MODE_LOCAL_FILE){
							headers.put(TvHeaders.FILE_URI,keyvals.getString(ITvContractExtras.C_URI_BLOB));
						}else {
							Log.d(LOG_TAG,"[!!!]: getUriHeaders :  get video pid :");
							int tmp_vpid = keyvals.getInt(ITvContractExtras.C_VIDEOPID);
							int tmp_apid = keyvals.getInt(ITvContractExtras.C_AUDIOPID);
							int tmp_pcrpid = keyvals.getInt(ITvContractExtras.C_PCRPID);
							Log.d(LOG_TAG,"[!!!]: getUriHeaders :  first time get vpid:apid:pcrpid = " + tmp_vpid + ":" + tmp_apid + ":" + tmp_pcrpid);

							lInternalData = cursor.getBlob(cursor.getColumnIndex(TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA));
							keyvals.setBlob(lInternalData);	
							int tmp_vpid2 = keyvals.getInt(ITvContractExtras.C_VIDEOPID);
							int tmp_apid2 = keyvals.getInt(ITvContractExtras.C_AUDIOPID);
							int tmp_pcrpid2 = keyvals.getInt(ITvContractExtras.C_PCRPID);
							Log.d(LOG_TAG,"[!!!]: getUriHeaders :  second time get vpid:apid:pcrpid = " + tmp_vpid2 + ":" + tmp_apid2 + ":" + tmp_pcrpid2);

							if (tmp_vpid == tmp_vpid2) {
								Log.d(LOG_TAG,"[!!!]: getUriHeaders :  get video pid two times, the same. ");
								headers.put(TvHeaders.VIDEO_PID,Integer.toString(tmp_vpid));
							} else {
								Log.d(LOG_TAG,"[!!!]: getUriHeaders :  get video pid two times, not the same. ");
							}
							if (tmp_apid == tmp_apid2) {
								Log.d(LOG_TAG,"[!!!]: getUriHeaders :  get audio pid two times, the same. ");
								headers.put(TvHeaders.AUDIO_PID,Integer.toString(tmp_apid));
							} else {
								Log.d(LOG_TAG,"[!!!]: getUriHeaders :  get audio pid two times, not the same. ");
							}
							if (tmp_pcrpid == tmp_pcrpid2) {
								Log.d(LOG_TAG,"[!!!]: getUriHeaders :  get pcr pid two times, the same. ");
								headers.put(TvHeaders.PCR_PID,Integer.toString(tmp_pcrpid));
							} else {
								Log.d(LOG_TAG,"[!!!]: getUriHeaders :  get pcr pid two times, not the same. ");
							}
							
							//headers.put(TvHeaders.VIDEO_PID,Integer.toString(keyvals.getInt(ITvContractExtras.C_VIDEOPID)));
							//headers.put(TvHeaders.AUDIO_PID,Integer.toString(keyvals.getInt(ITvContractExtras.C_AUDIOPID)));
							//headers.put(TvHeaders.PCR_PID,Integer.toString(keyvals.getInt(ITvContractExtras.C_PCRPID)));
							headers.put(TvHeaders.VIDEO_STREAM_TYPE,Integer.toString(keyvals.getInt(ITvContractExtras.C_VIDEOSTREAMTYPE)));
							headers.put(TvHeaders.AUDIO_STREAM_TYPE,Integer.toString(keyvals.getInt(ITvContractExtras.C_AUDIOSTREAMTYPE)));
												
							if(medium == Medium.MEDIUM_SATELLITE.value) {
								headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCH_SATELLITE));
								headers.put(TvHeaders.POLARIZATION,Integer.toString(keyvals.getInt(ITvContractExtras.C_POLARIZATION)));
								
								int lnbNumber 						= keyvals.getInt(ITvContractExtras.C_LNBNUMBER);																
								ITvSettingsManager globalSettings 	= ITvSettingsManager.Instance.getInterface();
								headers.put(TvHeaders.LNB_NUMBER,Integer.toString(lnbNumber));					
								headers.put(TvHeaders.LNB_TYPE,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE,lnbNumber,0)));
								headers.put(TvHeaders.LO_LOW_FREQUENCY,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ,lnbNumber,0)));
								headers.put(TvHeaders.LO_HIGH_FREQUENCY,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ,lnbNumber,0)));
								headers.put(TvHeaders.TONE,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGTONECONTROL,lnbNumber,0)));
								headers.put(TvHeaders.LNB_POWER,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBPOWER,lnbNumber,0)));
								
								int connectionType = globalSettings.getInt(TvSettingsConstants.INSTSETTINGSCONNECTIONTYPE,lnbNumber,0);
								headers.put(TvHeaders.CONNECTION_TYPE,Integer.toString(connectionType));
								
								if(connectionType == 5)  { //magic num to be replaced
									headers.put(TvHeaders.MODE,Integer.toString(TvHeaders.MODE_SATIP)); //overwrite
									headers.put(TvHeaders.SATIP_MODSYS,Integer.toString(keyvals.getInt(ITvContractExtras.C_MODULATION)));
									headers.put(TvHeaders.SATIP_FECINNER,Integer.toString(keyvals.getInt(ITvContractExtras.C_FECINNER)));
									headers.put(TvHeaders.SATIP_ROLLOFF,Integer.toString(keyvals.getInt(ITvContractExtras.C_ROLLOFF)));
									headers.put(TvHeaders.SATIP_PILOTS,Integer.toString(1)); //if always constant, why do we need this part of header?
								}								
							}else {
								headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_DIGITAL));
								if(mode==TvHeaders.MODE_DVBC) {
									//added because the auto selection in DVBC was taking time 
									headers.put(TvHeaders.MODULATION,Integer.toString(keyvals.getInt(ITvContractExtras.C_MODULATION)));
								}
								if(mode == TvHeaders.MODE_DVBT2) {
									headers.put(TvHeaders.PLP_ID,Integer.toString(keyvals.getInt(ITvContractExtras.C_PLPID)));
								} else {
									headers.put(TvHeaders.STREAM_PRIORITY,Integer.toString(keyvals.getInt(ITvContractExtras.C_STREAMPRIORITY)));
								}
							}
						}
					}catch(IOException e){
						Log.d(LOG_TAG, "parseBlobData - CAUGHT EXCEPTION keyvals=null");
					}catch(ClassNotFoundException e){
						Log.d(LOG_TAG, "parseBlobData - CAUGHT EXCEPTION keyvals=null");
					}
				}
				
			}
			}
			finally
			{
				if(cursor!=null)
					cursor.close();
				cursor=null;
			}
		}else {
			int recId = Integer.parseInt(uri.getLastPathSegment());
			Log.d(LOG_TAG,"Recording id is "+recId);			
			String[] proj = { IRecordingsContract.C_PROGRAM_NUMBER,
							};
			String where 		= IRecordingsContract.C_RECORDING_ID + "=?";
			String[] whereArgs 	= { Integer.toString(recId) };

			Cursor c=null;
			try{
			c = context.getContentResolver().query(
					IRecordingsContract.CONTENT_URI_Recordings, proj, where,
					whereArgs, null);

			if (c != null) {
				if((c.getCount() > 0) && (c.moveToFirst())) {
					headers = new HashMap<String, String>();
					headers.put(TvHeaders.COMPLETE_URI,uri.toString());	
					headers.put(TvHeaders.RECORDING_ID, Integer.toString(recId));
					String filePath =  PlayTvHDDUtils.getInstance(context).getMountPath() + "/pvr/pvr_" +recId + ".tsl";
					headers.put(TvHeaders.FILE_LOCATION, filePath);
					int programNumber = c.getInt(0);
					headers.put(TvHeaders.SERVICE_ID, Integer.toString(programNumber));
					headers.put(TvHeaders.CACHE_ID, Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_PVR));
					headers.put(TvHeaders.MEDIUM, Integer.toString(Medium.MEDIUM_PVRFILE.value));
				}
			}
			}
            finally
			{
				if(c!=null)
					c.close();
				c=null;
			}
		}		
		return headers;
	}

	public static Map<String,String> getHeadersForTriplet(Context context,int onId,int tsId,int serviceId, boolean fallbackQueryReqd){
		Log.d(LOG_TAG,"parseUri onId is "+onId+ " tsID"+tsId+" serviceID"+serviceId);
		Map<String, String> headers =  new HashMap<String, String>();
		Cursor cursor 				=  null;
		boolean proceed				=  false;
		Uri mUri					=  TvContract.Channels.CONTENT_URI;
		String[] selectionArgs		=  null;
		int freqMapTableMedium 		= Medium.MEDIUM_TERRESTRIAL.value;
		int freqMapTableMode		= TvHeaders.MODE_DVBT;
		
		/* algorithm - get item for matching onid,tsid&sid */
		selectionArgs	=	new String[]{Integer.toString(onId),Integer.toString(tsId),Integer.toString(serviceId)};
		try{
		cursor   		= 	context.getContentResolver().query(mUri,PROJECTION_TRIPLET,SELECTION_MULTIFEED_1,selectionArgs, null);
		if(cursor != null) {
			if(cursor.getCount() > 0) {
				proceed = true;
			}else{
				//cursor.close();
			}
		}
		if((proceed == false) && (fallbackQueryReqd == true)) {
			/* algorithm - get item for matching onid & tsid */
			selectionArgs	=	new String[]{Integer.toString(onId),Integer.toString(tsId)};		
			cursor   		= 	context.getContentResolver().query(mUri,PROJECTION_TRIPLET,SELECTION_MULTIFEED_2,selectionArgs, null);
			if((cursor != null) && (cursor.getCount() > 0)) {
				proceed = true;
			}
			if(proceed == false){
				selectionArgs	=	new String[]{Integer.toString(onId),Integer.toString(tsId)};
				ITvSettingsManager globalSettings 	= ITvSettingsManager.Instance.getInterface();
				int tuner 							= globalSettings.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
				if(tuner == 0){
					mUri = IFrequencyListContract.ITCFrequencyMap.CONTENT_URI;
					int tcmedium = globalSettings.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
					if(tcmedium == 0) {
						freqMapTableMedium 	= Medium.MEDIUM_TERRESTRIAL.value;
						freqMapTableMode	=	TvHeaders.MODE_DVBT;
					} else if(tcmedium == 1) {
						freqMapTableMedium 	= Medium.MEDIUM_CABLE.value;
						freqMapTableMode	= TvHeaders.MODE_DVBC;
					}
				}
				else if(tuner == 1){
					mUri = IFrequencyListContract.ISATFrequencyMap.CONTENT_URI;
					freqMapTableMedium 	= Medium.MEDIUM_SATELLITE.value;
					freqMapTableMode	=	TvHeaders.MODE_DVBS;
				}
				cursor		= context.getContentResolver().query(mUri,PROJECTION_FREQUENCY_MAP,SELECTION_FREQUENCY_MAP,selectionArgs, null);
				Log.d(LOG_TAG,"Frequency map query returned cursor " + cursor);
			}
		}
		if(cursor != null) {
			if((cursor.getCount() > 0) && (cursor.moveToFirst()) ) {			
				if(mUri.equals(TvContract.Channels.CONTENT_URI)){
				headers.put(TvHeaders.PRESET_ID,cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_DISPLAY_NUMBER)));
				if(cursor.getString(cursor.getColumnIndex(TvContract.Channels._ID)) != null) {
					int uniqueId 	= Integer.parseInt(cursor.getString(cursor.getColumnIndex(TvContract.Channels._ID)));
					int userhidden	= 0;
					headers.put(TvHeaders.CHANNEL_ID,Integer.toString(uniqueId));
					if(cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_BROWSABLE)) != null) {
						userhidden 	= Integer.parseInt(cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_BROWSABLE)));
						
						if((userhidden == 1) && (uniqueId > 0)) {
							Uri uri = TvContract.buildChannelUri(uniqueId);
							headers.put(TvHeaders.COMPLETE_URI,uri.toString());
						}
					}					
				}
				headers.put(TvHeaders.SERVICE_ID,cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_SERVICE_ID)));
				headers.put(TvHeaders.SERVICE_TYPE,cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_SERVICE_TYPE)));
				/*fill medium - conversion needed*/
				String cType 	= cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_TYPE));
				int medium 		= Medium.MEDIUM_TERRESTRIAL.value;
				int mode		= TvHeaders.MODE_DVBT;
				if((cType.equals(TvContract.Channels.TYPE_DVB_T))) {
					medium	=	Medium.MEDIUM_TERRESTRIAL.value;
					mode	=	TvHeaders.MODE_DVBT;
				}
				else if((cType.equals(TvContract.Channels.TYPE_DVB_T2))){
					medium	=	Medium.MEDIUM_TERRESTRIAL.value;
					mode	=	TvHeaders.MODE_DVBT2;
				}
				else if((cType.equals(TvContract.Channels.TYPE_DVB_C)) ||
						(cType.equals(TvContract.Channels.TYPE_DVB_C2)) ){
					medium	=	Medium.MEDIUM_CABLE.value;
					mode	=	TvHeaders.MODE_DVBC;
				}
				else if((cType.equals(TvContract.Channels.TYPE_DVB_S)) ||
						(cType.equals(TvContract.Channels.TYPE_DVB_S2))){
					medium	=	Medium.MEDIUM_SATELLITE.value;
					mode	=	TvHeaders.MODE_DVBS;
				}
				else if(cType.equals(TvContract.Channels.TYPE_PAL)){
					medium	=	Medium.MEDIUM_TERRESTRIAL.value;
					mode	=	TvHeaders.MODE_ANALOG;
				}					
				headers.put(TvHeaders.MEDIUM,Integer.toString(medium));
				headers.put(TvHeaders.MODE,Integer.toString(mode));
				
				/*fill TvProvider internal blob data*/
				byte[] lInternalData		 = cursor.getBlob(cursor.getColumnIndex(TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA));
				IIntKeyValueables keyvals	 = IIntKeyValueables.Instance.getInterface();				
				try{
					keyvals.setBlob(lInternalData);						
					headers.put(TvHeaders.FREQUENCY,Integer.toString(keyvals.getInt(ITvContractExtras.C_FREQUENCY)));
					headers.put(TvHeaders.SYMBOL_RATE,Integer.toString(keyvals.getInt(ITvContractExtras.C_SYMBOLRATE)));
					headers.put(TvHeaders.BANDWIDTH,Integer.toString(keyvals.getInt(ITvContractExtras.C_BANDWIDTH)));
					headers.put(TvHeaders.PREFERRED_STEREO,Integer.toString(keyvals.getInt(ITvContractExtras.C_PreferredStereo)));
					headers.put(TvHeaders.SAP,Integer.toString(keyvals.getInt(ITvContractExtras.C_SAP)));
					
					if(mode == TvHeaders.MODE_ANALOG) {
						headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_ANALOG));
						headers.put(TvHeaders.TV_SYSTEM,Integer.toString(keyvals.getInt(ITvContractExtras.C_MODULATION)));
					}else {
						headers.put(TvHeaders.VIDEO_PID,Integer.toString(0x1FFF));
						headers.put(TvHeaders.AUDIO_PID,Integer.toString(0x1FFF));
						headers.put(TvHeaders.PCR_PID,Integer.toString(0x1FFF));
						headers.put(TvHeaders.VIDEO_STREAM_TYPE,Integer.toString(0));
						headers.put(TvHeaders.AUDIO_STREAM_TYPE,Integer.toString(0));
											
						if(medium == Medium.MEDIUM_SATELLITE.value) {
							headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCH_SATELLITE));
							headers.put(TvHeaders.POLARIZATION,Integer.toString(keyvals.getInt(ITvContractExtras.C_POLARIZATION)));
							
							int lnbNumber 						= keyvals.getInt(ITvContractExtras.C_LNBNUMBER);																
							ITvSettingsManager globalSettings 	= ITvSettingsManager.Instance.getInterface();
							headers.put(TvHeaders.LNB_NUMBER,Integer.toString(lnbNumber));					
							headers.put(TvHeaders.LNB_TYPE,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE,lnbNumber,0)));
							headers.put(TvHeaders.LO_LOW_FREQUENCY,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ,lnbNumber,0)));
							headers.put(TvHeaders.LO_HIGH_FREQUENCY,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ,lnbNumber,0)));
							headers.put(TvHeaders.TONE,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGTONECONTROL,lnbNumber,0)));
							headers.put(TvHeaders.LNB_POWER,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBPOWER,lnbNumber,0)));
							
							int connectionType = globalSettings.getInt(TvSettingsConstants.INSTSETTINGSCONNECTIONTYPE,lnbNumber,0);
							headers.put(TvHeaders.CONNECTION_TYPE,Integer.toString(connectionType));
							
							if(connectionType == 5)  { //magic num to be replaced
								headers.put(TvHeaders.MODE,Integer.toString(TvHeaders.MODE_SATIP)); //overwrite
								headers.put(TvHeaders.SATIP_MODSYS,Integer.toString(keyvals.getInt(ITvContractExtras.C_MODULATION)));
								headers.put(TvHeaders.SATIP_FECINNER,Integer.toString(keyvals.getInt(ITvContractExtras.C_FECINNER)));
								headers.put(TvHeaders.SATIP_ROLLOFF,Integer.toString(keyvals.getInt(ITvContractExtras.C_ROLLOFF)));
								headers.put(TvHeaders.SATIP_PILOTS,Integer.toString(1)); //if always constant, why do we need this part of header?
							}								
						}else {
							headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_DIGITAL));
							if(mode == TvHeaders.MODE_DVBT2) {
								headers.put(TvHeaders.PLP_ID,Integer.toString(keyvals.getInt(ITvContractExtras.C_PLPID)));
							} else {
								headers.put(TvHeaders.STREAM_PRIORITY,Integer.toString(keyvals.getInt(ITvContractExtras.C_STREAMPRIORITY)));
							}
						}
					}
				}catch(IOException e){
					Log.d(LOG_TAG, "parseBlobData - CAUGHT EXCEPTION keyvals=null");
				}catch(ClassNotFoundException e){
					Log.d(LOG_TAG, "parseBlobData - CAUGHT EXCEPTION keyvals=null");
				}	
				}
				else if(mUri.equals(IFrequencyListContract.ITCFrequencyMap.CONTENT_URI) || mUri.equals(IFrequencyListContract.ISATFrequencyMap.CONTENT_URI)){
					headers.put(TvHeaders.MEDIUM,Integer.toString(freqMapTableMedium));
					headers.put(TvHeaders.MODE,Integer.toString(freqMapTableMode));	
					headers.put(TvHeaders.VIDEO_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.AUDIO_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.PCR_PID,Integer.toString(0x1FFF));
					headers.put(TvHeaders.VIDEO_STREAM_TYPE,Integer.toString(0));
					headers.put(TvHeaders.AUDIO_STREAM_TYPE,Integer.toString(0));
					headers.put(TvHeaders.PRESET_ID,Integer.toString(0));
					if(freqMapTableMedium == Medium.MEDIUM_SATELLITE.value){
						headers.put(TvHeaders.FREQUENCY,Integer.toString(cursor.getInt((cursor.getColumnIndex(IFrequencyListContract.ISATFrequencyMap.COLUMN_FREQUENCY)))));
						headers.put(TvHeaders.SYMBOL_RATE,Integer.toString(cursor.getInt((cursor.getColumnIndex(IFrequencyListContract.ISATFrequencyMap.COLUMN_SYMBOLRATE)))));
						headers.put(TvHeaders.BANDWIDTH,Integer.toString(cursor.getInt((cursor.getColumnIndex(IFrequencyListContract.ISATFrequencyMap.COLUMN_BANDWIDTH)))));
						headers.put(TvHeaders.LNB_NUMBER,Integer.toString(cursor.getInt((cursor.getColumnIndex(IFrequencyListContract.ISATFrequencyMap.COLUMN_LNBNUMBER)))));
						headers.put(TvHeaders.POLARIZATION,Integer.toString(cursor.getInt((cursor.getColumnIndex(IFrequencyListContract.ISATFrequencyMap.COLUMN_POLARIZATION)))));
						headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCH_SATELLITE));
					}
					else{
						headers.put(TvHeaders.FREQUENCY,Integer.toString(cursor.getInt((cursor.getColumnIndex(IFrequencyListContract.ITCFrequencyMap.COLUMN_FREQUENCY)))));
						headers.put(TvHeaders.SYMBOL_RATE,Integer.toString(cursor.getInt((cursor.getColumnIndex(IFrequencyListContract.ITCFrequencyMap.COLUMN_SYMBOLRATE)))));
						headers.put(TvHeaders.BANDWIDTH,Integer.toString(cursor.getInt((cursor.getColumnIndex(IFrequencyListContract.ITCFrequencyMap.COLUMN_BANDWIDTH)))));
						headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_DIGITAL));
					}
				}
			}else {
				Log.d(LOG_TAG, "getCount 0!!!");
				headers=null;
			}
			
		}else{
			Log.d(LOG_TAG, "curson null !!!");
			headers=null;
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
		return headers;
	}
	
	public static int getPresetId(Context context,Uri uri){
		int channel = -1;
		if(TvContract.isChannelUriForTunerInput(uri)) {
			int _id = Integer.parseInt(uri.getLastPathSegment());
			String [] projection = {TvContract.Channels.COLUMN_DISPLAY_NUMBER};
			String [] selectionArgs = {Integer.toString(_id)};
			String selection  = TvContract.Channels._ID + " = ?";
			Cursor cursor =null;
			
			try
			{
			cursor= context.getContentResolver().query(TvContract.Channels.CONTENT_URI,projection,
					selection, selectionArgs, null);
			if(cursor!=null){
				if(cursor.getCount()>0){
					cursor.moveToFirst();
					channel = Integer.parseInt(cursor.getString(cursor.getColumnIndex(TvContract.Channels.COLUMN_DISPLAY_NUMBER)));
				}
			}else{
				Log.d(LOG_TAG,"cursor is null"); 
			}
			}
			finally{
				if(cursor!=null)
					cursor.close();
				cursor=null;
			}
		}
		return channel;
	}
	
	public static Map<String, String> getHeadersFromBundle(Context context,Bundle params) {
		Map<String, String> headers	= new HashMap<String, String>();		
		if(params != null) {
			int mode 				=  TvHeaders.MODE_DVBT;
			int medium				=  Medium.MEDIUM_INVALID.value;
			String[] keys	 		=  params.getStringArray(ITVSessionContext.TUNING_PARAMETERS);
			String tuneType			=  params.getString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE);
			String tuneSubType		=  params.getString(ITVSessionContext.KEY_TUNE_REQUEST_SUB_TYPE);
			String privDataCookie 	=  params.getString(ITVSessionContext.KEY_PRIVATE_DATA_COOKIE);
			
			if(tuneType != null) {
				headers.put(TvHeaders.REQUEST_TYPE,tuneType);
			}
			if(tuneSubType != null) {
				headers.put(TvHeaders.REQUEST_SUB_TYPE,tuneSubType);
			}
			if(privDataCookie != null) {
				headers.put(TvHeaders.PRIV_DATA_COOKIE,privDataCookie); 
			}
			for(int i = 0; i < keys.length ; i++){								
				String input = params.getString(keys[i]);
				if(keys[i].equals(TvContract.Channels.COLUMN_TYPE) ) {
					keys[i] = TvHeaders.MODE;
					if(input.equals(TvContract.Channels.TYPE_DVB_T)) {  
						mode 	= TvHeaders.MODE_DVBT;
						medium	= Medium.MEDIUM_TERRESTRIAL.value;
					}else if (input.equals(TvContract.Channels.TYPE_DVB_T2)) {
						if(privDataCookie != null){
							mode    = TvHeaders.MODE_DVBT2;
						}else{
							mode 	= TvHeaders.MODE_DVBT | TvHeaders.MODE_DVBT2;
						}
						medium	= Medium.MEDIUM_TERRESTRIAL.value;
					}else if(input.equals(TvContract.Channels.TYPE_DVB_S) || input.equals(TvContract.Channels.TYPE_DVB_S2)) {
						mode 	= TvHeaders.MODE_DVBS;
						medium	= Medium.MEDIUM_SATELLITE.value;
					}else if(input.equals(TvContract.Channels.TYPE_DVB_C ) || input.equals(TvContract.Channels.TYPE_DVB_C2)) {
						mode 	= TvHeaders.MODE_DVBC;
						medium	= Medium.MEDIUM_CABLE.value;
					}else if(input.equals(TvContract.Channels.TYPE_PAL ) || input.equals(TvContract.Channels.TYPE_SECAM)) {
						mode 	= TvHeaders.MODE_ANALOG;
						medium	= Medium.MEDIUM_TERRESTRIAL.value;
					}else if(input.equals(ITvContractExtras.TYPE_DVB_SATIP)) { 
						mode 	= TvHeaders.MODE_SATIP;
						medium	= Medium.MEDIUM_SATELLITE.value;
					}else {
						Log.d(LOG_TAG,"InValid medium passed !!!"+input);
					}
					headers.put(keys[i],Integer.toString(mode));
					headers.put(TvHeaders.MEDIUM,Integer.toString(medium));
					Log.i(LOG_TAG, "Bundle Parameters: " + keys[i] + " " + mode);
				} else if (keys[i].equals(TvContract.Channels.COLUMN_LOCKED)) {
					keys[i] = TvHeaders.LOCK;
					headers.put(keys[i], input);
					Log.i(LOG_TAG, "Bundle Parameters: " + keys[i] + " "
							+ input);
				} else if (keys[i].equals(TvContract.Channels.COLUMN_SERVICE_ID)) {
					keys[i] = TvHeaders.SERVICE_ID;
					headers.put(keys[i], input);
					Log.i(LOG_TAG, "Bundle Parameters: " + keys[i] + " "
							+ input);
				}else {
					String keystr = keys[i];
					try {
						Integer keyInt = new Integer(keys[i]);
						if (TvURIHelper.tvURIHeaders.containsKey(keyInt)) {
							keystr = TvURIHelper.tvURIHeaders.get(keyInt);
							Log.i(LOG_TAG, "Bundle Parameters: caontains key "
									+ keystr + " " + input);
						}
					} catch (NumberFormatException e) {
						Log.d(LOG_TAG, "Key is not of integer type");
					}
					headers.put(keystr, input);
					Log.i(LOG_TAG, "Bundle Parameters: = " + keystr + " "
							+ input);
				}
			}
			if(mode == TvHeaders.MODE_ANALOG) {
				if(!headers.containsKey(TvHeaders.CACHE_ID)) {
					headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_ANALOG));
				}
			}else {
				if(medium == Medium.MEDIUM_SATELLITE.value) {
					if(!headers.containsKey(TvHeaders.CACHE_ID)) {
						headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCH_SATELLITE));
					}
					if(headers.containsKey(TvHeaders.LNB_NUMBER)) {
						int lnbNumber 						= Integer.parseInt(headers.get(TvHeaders.LNB_NUMBER));																
						ITvSettingsManager globalSettings 	= ITvSettingsManager.Instance.getInterface();
						headers.put(TvHeaders.LNB_NUMBER,Integer.toString(lnbNumber));					
						headers.put(TvHeaders.LNB_TYPE,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE,lnbNumber,0)));
						headers.put(TvHeaders.LO_LOW_FREQUENCY,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ,lnbNumber,0)));
						headers.put(TvHeaders.LO_HIGH_FREQUENCY,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ,lnbNumber,0)));
						headers.put(TvHeaders.TONE,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGTONECONTROL,lnbNumber,0)));
						headers.put(TvHeaders.LNB_POWER,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBPOWER,lnbNumber,0)));
						
						int connectionType = globalSettings.getInt(TvSettingsConstants.INSTSETTINGSCONNECTIONTYPE,lnbNumber,0);
						headers.put(TvHeaders.CONNECTION_TYPE,Integer.toString(connectionType));
						if(connectionType == 5)  { //magic num to be replaced
							headers.put(TvHeaders.MODE,Integer.toString(TvHeaders.MODE_SATIP)); //overwrite
							if(headers.containsKey(TvHeaders.TV_SYSTEM)) {
								//incase of satip, modulation to be sent on different header string
								headers.put(TvHeaders.SATIP_MODSYS,headers.get(TvHeaders.TV_SYSTEM));
							}
							headers.put(TvHeaders.SATIP_PILOTS,Integer.toString(1)); //if always constant, why do we need this part of header?
						}
					}
													
				}else {
					if(!headers.containsKey(TvHeaders.CACHE_ID)) {
						headers.put(TvHeaders.CACHE_ID,Integer.toString(ITvVideoManager.VIDMGR_ACTIVITY_WATCHTV_DIGITAL));							
					}
				}
			}
		}
		return headers;
	}
	
	public static Bundle getBundleFromHeaders(Map<String, String> headers) {
		Bundle bundle 			= new Bundle();	
		String tuneType 		= ITVSessionContext.TUNE_REQUEST_TYPE_DEFAULT;
		
		if(headers != null) {			
			List<String> typelist 	= new ArrayList<String>(); 
			int mode 				= TvHeaders.MODE_DVBT;
			String columnType		= TvContract.Channels.TYPE_DVB_T;			
			Iterator lIterator 		= TvURIHelper.tvURIHeaders.keySet().iterator();
			while(lIterator.hasNext()){
				 int key = (int)lIterator.next();
				 if(headers.containsKey(tvURIHeaders.get(key))) {
					typelist.add(Integer.toString(key));
					bundle.putString(Integer.toString(key), headers.get(tvURIHeaders.get(key)));					
				 }
			}
			if(headers.containsKey(TvHeaders.SERVICE_TYPE)){
				bundle.putString(TvContract.Channels.COLUMN_SERVICE_TYPE,headers.get(TvHeaders.SERVICE_TYPE));
			}
			if(headers.get(TvHeaders.MODE) != null) {	
				mode = Integer.parseInt(headers.get(TvHeaders.MODE));
				if(mode == TvHeaders.MODE_DVBT) {
					columnType = TvContract.Channels.TYPE_DVB_T;
				}else if((mode&TvHeaders.MODE_DVBT2) == TvHeaders.MODE_DVBT2) {
					columnType = TvContract.Channels.TYPE_DVB_T2;
				}else if(mode == TvHeaders.MODE_DVBS) {
					columnType = TvContract.Channels.TYPE_DVB_S;
				}else if(mode == TvHeaders.MODE_DVBC) {
					columnType = TvContract.Channels.TYPE_DVB_C;
				}else if(mode == TvHeaders.MODE_ANALOG) {
					columnType = TvContract.Channels.TYPE_PAL;
				}else if(mode == TvHeaders.MODE_SATIP) {
					columnType = ITvContractExtras.TYPE_DVB_SATIP;
				}
				typelist.add(TvContract.Channels.COLUMN_TYPE);
				bundle.putString(TvContract.Channels.COLUMN_TYPE, columnType);	
			}
			if(headers.get(TvHeaders.REQUEST_TYPE) != null) {
				tuneType = headers.get(TvHeaders.REQUEST_TYPE);						
			}else {
				if(headers.get(TvHeaders.SELECTION_TYPE) != null) {
					int selType 	= Integer.parseInt(headers.get(TvHeaders.SELECTION_TYPE));					
					if( (selType == TvURIHelper.SelectionType.SELECTION_SILENT.value) || 
						(selType == TvURIHelper.SelectionType.SELECTION_MULTIFEED.value) ||
						(selType == TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value)){
						tuneType = ITVSessionContext.TUNE_REQUEST_TYPE_SILENT;
					}else if(selType == TvURIHelper.SelectionType.SELECTION_INSTALL.value) {
						tuneType = ITVSessionContext.TUNE_REQUEST_TYPE_CUSTOM;
					}					
				}
			}
			typelist.add(ITVSessionContext.KEY_TUNE_REQUEST_TYPE);
			bundle.putString(ITVSessionContext.KEY_TUNE_REQUEST_TYPE, tuneType);
			if(headers.get(TvHeaders.REQUEST_SUB_TYPE) != null) {
				typelist.add(ITVSessionContext.KEY_TUNE_REQUEST_SUB_TYPE);
				bundle.putString(ITVSessionContext.KEY_TUNE_REQUEST_SUB_TYPE,headers.get(TvHeaders.REQUEST_SUB_TYPE));
			}
			if(headers.get(TvHeaders.PRIV_DATA_COOKIE) != null) {
				typelist.add(ITVSessionContext.KEY_PRIVATE_DATA_COOKIE);
				bundle.putString(ITVSessionContext.KEY_PRIVATE_DATA_COOKIE,headers.get(TvHeaders.PRIV_DATA_COOKIE));
			}
			String[] params = typelist.toArray(new String[typelist.size()]);
			bundle.putStringArray(ITVSessionContext.TUNING_PARAMETERS,params);			
		}
		return bundle;
	}
}
