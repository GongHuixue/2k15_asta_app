package org.droidtv.tunerservice.util;

import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.provider.IEpgContract;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.video.ITvVideoManager;
import org.droidtv.tv.video.IVideoSource;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.content.ContentUris;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;
import java.util.ArrayList;
import java.util.List;

public final class PlayTvUtils {
	
	public static final String TAG ="PlayTvUtils";
	
	public static final int constTUNER = 0;
	
	public static final int FLAGS_BOOTUP = 1;
	public static final int FLAGS_BOOTUPFROMDDRSBY = 2;
	public static final int FLAGS_BOOTUPFROMSBY = 4;
	public static final int FLAGS_AUDIOMUTED = 8;
	public static final int FLAGS_DEFAULTURI = 0x10;
	public static final int FLAGS_BOOTUPFROMSBYOAD = 0x20;

	private static final int LOCKED = 1;
	
	public static final String MAIN_ACTION = "org.droidtv.action.ACTION_MAIN_AMMI";
	public static final String AUX_ACTION = "org.droidtv.action.ACTION_AUX_AMMI";
	
	public static int getCurrentChannel()
	{
		int channel=0;
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
				
		Medium medium = getCurrentMedium();
		
		if(medium == Medium.MEDIUM_SATELLITE)	{
			channel  = globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2,0,0);
		} 
		else {
			channel = globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC,0,0);
		}
		Log.d(TAG,"getCurrentChannel returns " + channel);
		
		return channel;
	}
	
	public static Uri getLastSelectedUri() {
		Medium medium = TvURIHelper.Medium.MEDIUM_INVALID;
		Uri uri = null;
		int lastDevice = getLastSelectedDevice();
	    int channel = -1;	
		switch (lastDevice) {
			case TvSettingsDefinitions.LastSelectedDeviceConstants.DVBTC:
				medium = getCurrentMedium();
				channel = getCurrentChannel();
				if( (medium!=TvURIHelper.Medium.MEDIUM_INVALID) && (channel>=0) ) {
					//todo:TIF
		//			uri = TvURIHelper.formURI(medium,channel,SelectionType.SELECTION_NORMAL);
				}
			break;
			case TvSettingsDefinitions.LastSelectedDeviceConstants.DVBS:
				medium = getCurrentMedium();
				channel = getCurrentChannel();
				if( (medium!=TvURIHelper.Medium.MEDIUM_INVALID) && (channel>=0) ) {
				//todo:TIF
//					uri = TvURIHelper.formURI(medium,channel,SelectionType.SELECTION_NORMAL);
				}
			break;
				case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI1:
				case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI2:
				case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI3:
				case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI4:
				case TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI5:
				case TvSettingsDefinitions.LastSelectedDeviceConstants.SCART:
				case TvSettingsDefinitions.LastSelectedDeviceConstants.YPBPR:
				case TvSettingsDefinitions.LastSelectedDeviceConstants.CVBS:
					String seluri;
					ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
					seluri = globalSettings.getString(TvSettingsConstants.LASTSELECTEDURI,0,null);
					uri = Uri.parse(seluri);
				break;
			default:				
			break;
		}
		if(uri!=null) {
			Log.d(TAG,"getLastSelectedUri returns  " + uri.toString());
		}
		else {
			Log.d(TAG,"No Previous Selection done");
			//todo:tif
			/*uri = TvURI.formURI(TvURIDeviceEnum.EXTENSION,
					TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI1);*/
		}
		return uri;
	}
	
	public static Uri getLastSelectedTunerUri() {
		ITvSettingsManager globalSettings 	= ITvSettingsManager.Instance.getInterface();
		int tuner 							= globalSettings.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		Uri uri 							= null;
		if(tuner==0) {
			uri  = TvContract.buildChannelUri(globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC,0,0));
		}
		else if(tuner==1){
			uri  = TvContract.buildChannelUri(globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2,0,0));					
		}
		if(uri!=null) {
			Log.d(TAG,"getLastSelectedUri returns  " + uri.toString());
		}
		else
		{
			Log.d(TAG,"No Previous Selection done");
		}
		
		return uri;
	}
	
	public static int getLastSelectedSource() {
		//ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		return constTUNER;
	}
		
	public static void storeLastSelectedDevice(int sourceid) {
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		globalSettings.putInt(TvSettingsConstants.LASTSELECTEDDEVICE,0,sourceid);
	}
	
	public static void storeLastSelectedDevice(Medium medium) {
		int sourceid = 0;
		if((medium == Medium.MEDIUM_TERRESTRIAL) || (medium == Medium.MEDIUM_CABLE)){
			sourceid = TvSettingsDefinitions.LastSelectedDeviceConstants.DVBTC;
		}
		if(medium == Medium.MEDIUM_SATELLITE){
			sourceid = TvSettingsDefinitions.LastSelectedDeviceConstants.DVBS;
		}
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		globalSettings.putInt(TvSettingsConstants.LASTSELECTEDDEVICE,0,sourceid);
	}
	
	public static int getLastSelectedDevice() {
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		return globalSettings.getInt(TvSettingsConstants.LASTSELECTEDDEVICE,0,0);
	}
		
	public static void storeCurrentChannel(Uri mediaPlayerUri, Medium medium, int presetNumber)
	{
		Log.d(TAG,"storeCurrentChannel _id called ");
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		int _id = 0;
		if(mediaPlayerUri!=null) {
			try {
				_id = (int) ContentUris.parseId(mediaPlayerUri);
				if(medium == Medium.MEDIUM_SATELLITE) {
					if(globalSettings.getInt(TvSettingsConstants.LASTSELECTEDTUNER,0,0)!=1) {
						globalSettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER,0,1);
					}
					globalSettings.putInt(TvSettingsConstants.LASTSELECTEDPRESETS2,0, _id);
				} else if( (medium == Medium.MEDIUM_CABLE) || (medium == Medium.MEDIUM_TERRESTRIAL) ){
					if(globalSettings.getInt(TvSettingsConstants.LASTSELECTEDTUNER,0,1)!=0) {
						globalSettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER,0,0);
					}
					globalSettings.putInt(TvSettingsConstants.LASTSELECTEDPRESETTC,0, _id);
				} else {
					return;
				}
			}catch(Exception e) {
				Log.d(TAG,"storeCurrentChannel:Exception : "+e.toString());
			}
		}
		Log.d(TAG,"storeCurrentChannel _id " + _id + "done");
	}
	
	public static void setCurrentMedium(Medium m)
	{
		Log.d(TAG,"setCurrentMedium to " + m);
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		switch(m) {
			case MEDIUM_CABLE:
				globalSettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);	
				globalSettings.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 1);
				break;
			case MEDIUM_SATELLITE:
				globalSettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 1);
				break;
			case MEDIUM_TERRESTRIAL:
				globalSettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
				globalSettings.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
				break;
			default:
				break;
		}
		Log.d(TAG,"setCurrentMedium done");
	}
	
	public static Medium getCurrentMedium()
	{
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		Medium medium = TvURIHelper.Medium.MEDIUM_TERRESTRIAL;
		int tuner = globalSettings.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0); 		
		if(tuner==0) {
			int tcmedium = globalSettings.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
			if(tcmedium == 0) {
				Log.d(TAG,"Terrstrial");
				medium = TvURIHelper.Medium.MEDIUM_TERRESTRIAL; 
			} else if(tcmedium == 1) {
				Log.d(TAG,"Cable");
				medium = TvURIHelper.Medium.MEDIUM_CABLE;
			}
			else
			{
				Log.d(TAG,"Invalid MediumTC... Selecting DVBT");
				medium = TvURIHelper.Medium.MEDIUM_TERRESTRIAL;
			}
		} 
		else if(tuner==1){
			Log.d(TAG,"Satellite");
			medium = TvURIHelper.Medium.MEDIUM_SATELLITE;
		}
		
		Log.d(TAG,"getCurrentMedium medium = " + medium.ordinal());
		return medium;
	}
	
	public static Uri getCurrentTvContentProviderUri()
	{
		Uri uri = null;
		
		Medium medium = getCurrentMedium();
		
		if(medium == TvURIHelper.Medium.MEDIUM_TERRESTRIAL) {
			uri = IChannelContract.CONTENT_URI_TerChannelMap;
		} else if (medium == TvURIHelper.Medium.MEDIUM_CABLE)	{
			uri = IChannelContract.CONTENT_URI_CabChannelMap;
		} else if (medium == TvURIHelper.Medium.MEDIUM_SATELLITE) {
			uri = IChannelContract.CONTENT_URI_SatChannelMap;
		}else{
			uri = IChannelContract.CONTENT_URI_TerChannelMap;
		}
		Log.d(TAG,"getCurrentTvContentProviderUri uri" + uri.toString());
		return uri;
	}
	
	public static Uri getCurrentEPGContentProviderUri()
	{
		Uri uri = null;
		
		Medium medium = getCurrentMedium();
		
		if(medium == TvURIHelper.Medium.MEDIUM_TERRESTRIAL) {
			uri = IEpgContract.CONTENT_URI_AntennaNowNextEventData;
		} else if (medium == TvURIHelper.Medium.MEDIUM_CABLE)	{
			uri = IEpgContract.CONTENT_URI_CableNowNextEventData;
		} else if (medium == TvURIHelper.Medium.MEDIUM_SATELLITE) {
			uri = IEpgContract.CONTENT_URI_SatelliteNowNextEventData;
		}else{
			uri = IEpgContract.CONTENT_URI_AntennaNowNextEventData;
		}
		Log.d(TAG,"getCurrentEPGContentProviderUri uri" + uri.toString());
		return uri;
	}
	
	public static int getChannelFilter(){
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		int mChannelFilter = globalSettings.getInt(TvSettingsConstants.CHANNELFILTER, 0, 0);
		if((mChannelFilter == 0 ) || ( mChannelFilter == 1)){
			return mChannelFilter;
		}else{
			return 0;
		}
	}
	
	public static int getMode(int DecoderType)
	{
		int mode = 2;
		switch(DecoderType)
		{
			case 0x00: mode = 1; //0 is being used for analog
				break;
			case 0x01: mode = 2; //IHsvFrontEndApi_ChanDecDvbT
				break;
			case 0x10: mode = 4; //IHsvFrontEndApi_ChanDecDvbT2
				break;
			case 0x02: mode = 8; //IHsvFrontEndApi_ChanDecDvbC
				break;
			case 0x04: mode = 0x10; //IHsvFrontEndApi_ChanDecDvbS
				break;
			default: 
				break;
		}
		Log.d(TAG,"getMode returns " + mode);
		return mode;
	}
	
	public static int getMode(Medium m) {
		int mode = 0;
		switch(m) {
			case MEDIUM_TERRESTRIAL:
				mode = 2 | 4;	
			break;
			case MEDIUM_CABLE:
				mode = 8;
			break;
			case MEDIUM_SATELLITE:
				mode = 0x10;
			break;
			default:
				break;
		}
		Log.d(TAG,"getMode for medium " + m + "returns " + mode);
		return mode;
	}
	
	public static int getCacheId(int sourceid) {
		switch(sourceid) {
			case IVideoSource.VIDEOSOURCE_HDMI1:
				return ITvVideoManager.VIDMGR_ACTIVITY_HDMI_1;
			case IVideoSource.VIDEOSOURCE_HDMI2:
				return ITvVideoManager.VIDMGR_ACTIVITY_HDMI_2;
			case IVideoSource.VIDEOSOURCE_HDMI3:
				return ITvVideoManager.VIDMGR_ACTIVITY_HDMI_3;
			case IVideoSource.VIDEOSOURCE_HDMI4:
				return ITvVideoManager.VIDMGR_ACTIVITY_HDMI_4;
				
			//using same id for VIDEOSOURCE_YPBPR1 and VIDEOSOURCE_YPBPR2	
			case IVideoSource.VIDEOSOURCE_YPBPR1:
				return ITvVideoManager.VIDMGR_ACTIVITY_YPBPR;
			case IVideoSource.VIDEOSOURCE_YPBPR2:
				return ITvVideoManager.VIDMGR_ACTIVITY_YPBPR;
				
			//using same id for VIDEOSOURCE_SCART1 and VIDEOSOURCE_SCART2	
			case IVideoSource.VIDEOSOURCE_SCART1:
				return ITvVideoManager.VIDMGR_ACTIVITY_SCART;
			case IVideoSource.VIDEOSOURCE_SCART2:
				return ITvVideoManager.VIDMGR_ACTIVITY_SCART;	
				
			//There is no direct mapping available once the ids are available the 
			//	following has to be set
				
			case IVideoSource.VIDEOSOURCE_HDMI5:
			case IVideoSource.VIDEOSOURCE_HDMI6:
			case IVideoSource.VIDEOSOURCE_SVIDEO:
			case IVideoSource.VIDEOSOURCE_VGA:
			case IVideoSource.VIDEOSOURCE_CVBS1:
			case IVideoSource.VIDEOSOURCE_CVBS2:
			default:
				Log.e(TAG,"No Cache id available for "+ sourceid);
				return 0;
		}
	}

	public static Uri getCurrentTvContentProviderUri(Medium m) {
		switch(m) {
			case MEDIUM_CABLE:
				return IChannelContract.CONTENT_URI_CabChannelMap;
			case MEDIUM_SATELLITE:
				return IChannelContract.CONTENT_URI_SatChannelMap;
			case MEDIUM_TERRESTRIAL:
				return IChannelContract.CONTENT_URI_TerChannelMap;
			default: 
				Log.d(TAG,"Invalid medium");
				return null;
		}
	}

	public static int getCurrentChannel(Medium medium) {
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		
		switch(medium) {
			case MEDIUM_SATELLITE:
				return globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2,0,0);
			case MEDIUM_CABLE:
				return globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC,0,0);
			case MEDIUM_TERRESTRIAL:
				return globalSettings.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC,0,0);
			default:	
				return 0;	
		}
	}
    /*begin:min.jiang add 2015-06-06, for pbs date and time settings*/
    public static boolean isLiveChannelMode() {
        boolean ret = false;
        ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
        int source = globalSettings.getInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_SOURCE, 0, 0);
        if(source == TvSettingsDefinitions.PbsDNTSourceConstants.PBSMGR_DNT_SOURCE_AUTOMATIC_LIVE_CH) {
            ret = true;
        }

        return ret;
    }
    public static boolean isNeedSyncNetTime(){
        boolean ret = false;
        ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
        int source = globalSettings.getInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_SOURCE, 0, 0);
        if(source == TvSettingsDefinitions.PbsDNTSourceConstants.PBSMGR_DNT_SOURCE_AUTOMATIC_NTP) {
            ret = true;
        }

        return ret;        
    }
    public static boolean isLiveCountry(int isocode) {
        ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
        int timeZoneCountry = globalSettings.getInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_TIME_ZONE_COUNTRY, 0, 0); 
        Log.d(TAG, "pbs timezone country: " + timeZoneCountry);
        return isocode == timeZoneCountry;    
    }
    
    public static int getClockCalibrationcid() {
        ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
        return globalSettings.getInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_LIVE_CH,0,0);
    }

    public static void storeClockCalibrationcid(int cid) {
        ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
        globalSettings.putInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_LIVE_CH,0,cid);

    }
    public static boolean isPbsMode() {
        ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
        return globalSettings.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE,0,0) == 
                TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON;
    }    
    
    /*end:min.jiang add*/
	public static void storeLastSelectedUri(String uri) {
		Log.d(TAG,"storeLastSelectedUri " + uri);
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		globalSettings.putString(TvSettingsConstants.LASTSELECTEDURI,0,uri);
	}
	
	public static int getVirginBit(){
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		Log.d(TAG, "Returning Virgin Bit Value = " + globalSettings.getInt(TvSettingsConstants.VIRGINBIT,0,0));
		return globalSettings.getInt(TvSettingsConstants.VIRGINBIT,0,0);
	}

	public static Boolean IsChannelDigital(Context context, int presetid)
	{
		Boolean isdigital 		= true;		
		String[] MPLAYER_PROJ 	= new String [] {	
				TvContract.Channels.COLUMN_TYPE
				};
		String selection 		=  TvContract.Channels.COLUMN_DISPLAY_NUMBER + "=?";
		String selectionArgs[] 	= {Integer.toString(presetid)};
		Cursor c1=null;
		try
		{
		    c1 = context.getContentResolver().query(TvContract.Channels.CONTENT_URI, 
							MPLAYER_PROJ , selection, selectionArgs, null);
		    if( (c1!=null)&& (c1.getCount()>0) && (c1.moveToFirst())) 
		    {
			   String cType 	= c1.getString(c1.getColumnIndex(TvContract.Channels.COLUMN_TYPE));
			   if((cType != null) && (cType.equals(TvContract.Channels.TYPE_PAL))) {
				  isdigital = false;
			    }
			    Log.d(TAG,"IsChannelDigital - channel "+presetid+"isdigital-"+isdigital);
		    }
		   else
		   {
			 Log.d(TAG," Cursor is NULL for service type ");			
		   }
		}
		finally
		{
			if(c1!=null)
			{
				c1.close();
			    c1=null;	   
			}
		}
		return isdigital;
	}
	
	public static Uri appendQueryParameter(Uri uri, String key, String value){
		if(uri != null){
			Uri.Builder builder = uri.buildUpon().appendQueryParameter(key, value);
			return builder.build();
		}
		return null;
	}

	public static Uri translateUri(Uri selectUri) {
		Medium medium = Medium.MEDIUM_INVALID;
		if( selectUri.toString().matches("tv://tuner/[TCS]/\\d{1,4}") ){
			String cString = selectUri.getLastPathSegment().toString();
			int presetNumber = Integer.parseInt(cString);
			Log.d(TAG,"presetNumber " + presetNumber);
			String mString = selectUri.getPathSegments().get(0);
			if(mString.matches("T")) {
	        	medium = Medium.MEDIUM_TERRESTRIAL;
	        }else if(mString.matches("C")) {
	           	medium = Medium.MEDIUM_CABLE;
	        }else if(mString.matches("S")) {
	        	medium = Medium.MEDIUM_SATELLITE;
	        }
	//		selectUri = TvURIHelper.formURI(presetNumber,medium);
			Log.d(TAG,"Translated uri : " + selectUri.toString());
		}
		return selectUri;
	}
	
	public static boolean isCableSelected()
	{
		boolean isCable = false;
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		int tcmedium = globalSettings.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
		if(tcmedium == 1) {
			isCable = true;
		}
		Log.d(TAG, "isCableSelected "+isCable);
		return isCable;
	}
	
	public static int getLockStatus(Uri uri) {
		int lockedStatus = 0;
		if((uri != null) /*&& WAR : (!ZapbarUtils.isIPEpg())*/){
			String m_lock = uri.getQueryParameter(IChannelContract.C_LOCK);
			if(m_lock != null){
				int lock = Integer.parseInt(m_lock);
				if(lock == LOCKED){
					lockedStatus = 1;
				}
			}
		}
		Log.d(TAG, "getLockStatus - returning lockedStatus = " + lockedStatus);
		return lockedStatus;
	}

	public static Uri getNextURI(Uri currentUri){
		Log.i(TAG,"getNextURI called with currentUri = "+currentUri);
		return null;
	}
	
	public static Uri getPreviousURI(Uri currentUri){
		Log.i(TAG,"getPreviousURI called with currentUri = "+currentUri);
		return null;
	}
	
	public static Uri getFirstDigitalChannel(Context context, Medium m) {
		Uri channelUri			= null;
		List<String> typelist 	= new ArrayList<String>(); 
		
		if(m == Medium.MEDIUM_TERRESTRIAL) {
			typelist.add(Channels.TYPE_DVB_T);
			typelist.add(Channels.TYPE_DVB_T2);
		}else if(m == Medium.MEDIUM_CABLE) {
			typelist.add(Channels.TYPE_DVB_C);
			typelist.add(Channels.TYPE_DVB_C2);
		}else if(m == Medium.MEDIUM_SATELLITE) {
			typelist.add(Channels.TYPE_DVB_S);
			typelist.add(Channels.TYPE_DVB_S2);
		}
		
		String [] projection= {TvContract.Channels._ID};
		String sortorder 	= " CAST( " + Channels.COLUMN_DISPLAY_NUMBER + " AS INTEGER ) ASC  LIMIT 1";
		Cursor cursor		= null;
		try
		{
		   cursor = context.getContentResolver().query(TvContract.Channels.CONTENT_URI,projection,
				TvContract.Channels.COLUMN_TYPE+" IN(?,?)", typelist.toArray(new String[typelist.size()]), sortorder);
		   if(cursor!=null){
			  if(cursor.getCount()>0){
				  cursor.moveToFirst();
				  int channel = Integer.parseInt(cursor.getString(cursor.getColumnIndex(TvContract.Channels._ID)));
				  if(channel > 0) {
					channelUri = TvContract.buildChannelUri(channel);
				  }
			   }
		   }else{
			  Log.d(TAG,"cursor is null"); 
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
		Log.d(TAG, "getFirstDigitalChannel: returns " +channelUri);
		return channelUri;
	}
}
