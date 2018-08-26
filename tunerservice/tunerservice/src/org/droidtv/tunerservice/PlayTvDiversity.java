package org.droidtv.tunerservice;

import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import android.util.Log;
import android.os.SystemProperties;

public class PlayTvDiversity {
	
	public static final String TAG = "PlayTvDiversity"; 
		
	public static boolean isCAMAllocationPrioritySupported()
	{
		ITvSettingsManager mglobalSetting  = ITvSettingsManager.Instance.getInterface(); 
		int InstalledCountry = mglobalSetting.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		boolean retval = true;

		switch(InstalledCountry)
		{
		case TvSettingsDefinitions.InstallationCountryConstants.ITALY:
			if(PlayTvUtils.getCurrentMedium() == Medium.MEDIUM_TERRESTRIAL)
				retval = false;
			break;
		default:
			break;
		}
		Log.d(TAG,"isCAMAllocationPrioritySupported retval:" +retval);
		return retval;

	}
	
	public static boolean isOlympicUsecaseSupported()
	{
		ITvSettingsManager mglobalSetting  = ITvSettingsManager.Instance.getInterface(); 
		int InstalledCountry = mglobalSetting.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		boolean retval = true; // enabled for PPR1.5

		switch(InstalledCountry)
		{
		case TvSettingsDefinitions.InstallationCountryConstants.ITALY:
			if(PlayTvUtils.getCurrentMedium() == Medium.MEDIUM_TERRESTRIAL)
				retval = false;
			break;
		default:
			break;
		}
		Log.d(TAG,"isOlympicUsecaseSupported retval:" +retval);
		return retval;	
	}
	
	public static boolean isQaaMulTranslationSupported()
	{
		ITvSettingsManager mglobalSetting  = ITvSettingsManager.Instance.getInterface(); 
		int InstalledCountry = mglobalSetting.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		boolean retval = false; 

		switch(InstalledCountry)
		{
		case TvSettingsDefinitions.InstallationCountryConstants.HUNGARY:
				retval = true;
			break;
		default:
			break;
		}
		Log.d(TAG,"isCountryHungary retval:" +retval);
		return retval;	
	}

	public static boolean isOADSupported()
	{
		ITvSettingsManager mglobalSetting  = ITvSettingsManager.Instance.getInterface();
		int EnableOAD  = mglobalSetting.getInt(TvSettingsConstants.OPOAD,0,0);

		boolean retval = false; 

		if(EnableOAD!= 0)
		{
			retval = true;
		}

		Log.d(TAG,"isOADenabled:" +retval +"EnableOAD" +EnableOAD);
		return retval;

	}

	public static boolean isMonitorPIPSupported() {
		/*String sytemval = SystemProperties.get("ro.tpvision.product.ppr2");
		if(sytemval != null && !sytemval.trim().equals("")
				&& (sytemval.trim().equals("1"))) {
			return true;
		}
		else {
			return false;
		}*/
		return false;
	}
	
	public static boolean isTadPossibleWithPip()
	{
		/*	Platform has only two decoders and no encoders. Hence for TAD streaming, we will use
			one of decoder as encoder. As other available decoder is busy with main watch, TAD + PIP
			usecase is not possible */
		return false;
	}
	
	public static boolean isIndependentTadSupported() {
		return false;
	}

	public static boolean isMHEGSupported() {
		//marvel return false
		//mtk return true 
		return true;
	}	
	public static boolean isIPEpgAutoMarginSupported(){
		return true;
	}
}
