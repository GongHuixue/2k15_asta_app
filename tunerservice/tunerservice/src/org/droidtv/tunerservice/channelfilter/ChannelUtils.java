package org.droidtv.tunerservice.channelfilter;

import android.os.Bundle;
import android.util.Log;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;



public class ChannelUtils {

	private static final String TAG = ChannelUtils.class.getSimpleName();
	private static ITvSettingsManager mGlobalSetting;
	
	static{
		mGlobalSetting = ITvSettingsManager.Instance.getInterface();
	}

	public static int getCurrentChannel()
	{
		int channel=0;
		Medium medium = getCurrentMedium();
		if(medium == Medium.MEDIUM_SATELLITE)	{
			channel  = mGlobalSetting.getInt(TvSettingsConstants.LASTSELECTEDPRESETS2,0,0);
		} else {
			channel = mGlobalSetting.getInt(TvSettingsConstants.LASTSELECTEDPRESETTC,0,0);
		}
		Log.d(TAG,"getCurrentChannel returns " + channel);
		return channel;
	}
	
	
	public static Medium getCurrentMedium()
	{
		Medium medium = Medium.MEDIUM_TERRESTRIAL;
		int tuner = mGlobalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0); 		
		if(tuner==0) {
			int tcmedium = mGlobalSetting.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
			if(tcmedium == 0) {
				Log.d(TAG,"Terrstrial");
				medium = Medium.MEDIUM_TERRESTRIAL; 
			} else if(tcmedium == 1) {
				Log.d(TAG,"Cable");
				medium = Medium.MEDIUM_CABLE;
			}
			else
			{
				Log.d(TAG,"Invalid MediumTC... Selecting DVBT");
				medium = Medium.MEDIUM_TERRESTRIAL;
			}
		} 
		else if(tuner==1){
			Log.d(TAG,"Satellite");
			medium = Medium.MEDIUM_SATELLITE;
		}
		
		Log.d(TAG,"getCurrentMedium medium = " + medium.ordinal());
		return medium;
	}
	
	public static int getChannelFilter(){
		 
		if(mGlobalSetting != null){
			int cLastSelectedTuner = mGlobalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
			int cChannelFilterTC  = mGlobalSetting.getInt(TvSettingsConstants.CHANNELFILTERTC, 0, 0);
			int cChannelFilterSat = mGlobalSetting.getInt(TvSettingsConstants.CHANNELFILTERSATELLITE, 0, 0);
			switch(cLastSelectedTuner){
				case TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC:
					Log.d(TAG , "getChannelFilter::TunerType - DVB-T or DVB-C, returning cChannelFilterTC = " + cChannelFilterTC);
					return cChannelFilterTC;
				case TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER:
					Log.d(TAG , "getChannelFilter::TunerType - DVB-S, returning cChannelFilterSat = " + cChannelFilterSat);
					return cChannelFilterSat;
				default:
					Log.d(TAG, "getChannelFilter::LastSelectedTuner value in NVM is Wrong :: LastSelectedTuner - " + cLastSelectedTuner);
					return cChannelFilterTC;
			}
		}
		return -1;
	}
	
	
	public static int getActiveZapList(int tunerType){
		switch(tunerType){
		case TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC:
			return mGlobalSetting.getInt(TvSettingsConstants.TCCHANNELSUBLIST, 0, 0);
		case TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER:
			return mGlobalSetting.getInt(TvSettingsConstants.SATELLITECHANNELSUBLIST, 0, 0);
		default:
			Log.e(TAG, "getActiveZapList - Error :: Unknow tuner type =  " + tunerType + " , returning -1");
			return -1;
		}
	}
	
	public static void storeChannelFilter(int channelFilter){
		int cTunerType = mGlobalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		switch(cTunerType){
		case TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC:
			Log.d(TAG, "storeChannelFilter :: Storing CHANNELFILTERTC = " + channelFilter);
			mGlobalSetting.putInt(TvSettingsConstants.CHANNELFILTERTC, 0, channelFilter);
			break;
		case TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER:
			Log.d(TAG, "storeChannelFilter :: Storing CHANNELFILTERSATELLITE = " + channelFilter);
			mGlobalSetting.putInt(TvSettingsConstants.CHANNELFILTERSATELLITE, 0, channelFilter);
			break;
		default:
			Log.d(TAG, "Cannot store channel filter valuer as Tuner Type is Unknown ..  cTunerType :: " + cTunerType);
		}
	}
	
	public static boolean checkSystemHiddenValue(Bundle channelData) {
		boolean isSystemHidden = false;
		try{
			if(channelData != null){
				isSystemHidden = (channelData.getInt("SystemHidden") == 0) ?  true : false;
			}
		}catch(Exception e){
			Log.d(TAG, "Exception raised .. returning false");
			isSystemHidden = false;
		}
		Log.d(TAG, "checkSystemHiddenValue returning isSystemHidden = " + isSystemHidden);
		return isSystemHidden;
	}
	
}
