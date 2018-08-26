package org.droidtv.euinstallertc.service;

import org.droidtv.tv.audio.ITvAudioManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.ITvSettingsManager.ITvSettingsManagerNotify;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import android.util.Log;

public class InstallerTVSettings {
	private ITvSettingsManager mTvSettingsManager =ITvSettingsManager.Instance.getInterface(); 
    private static final String TAG       = InstallerTVSettings.class.getName();
    private int [] property;
    private int [] property_cache;
    private static final int PROPMAX = 1;
    private ITvAudioManager mTvAudioMgr =null;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();

    public InstallerTVSettings() {
        Log.d(TAG, "InstallerTVSettings Constuctor");
       
        // register to global settings for the NVM bit changes
        // registerTvSettingsManager();
    }

	class SettingsListener extends ITvSettingsManagerNotify{

		//@Override
		public void OnUpdate(int prop){
		    boolean valchanged = false;
			int value;
		    Log.d(TAG, "Notification From Global Setting Received  " + prop );
		    switch(prop) {
		        case TvSettingsConstants.INSTALLATIONCOUNTRY:
					value = mTvSettingsManager.getInt(prop,0,0);
		            if(property_cache[0]!=value) {
		                Log.d(TAG, "Country changed in TVSettings");
		                property_cache[0] = value;
		                valchanged=true;
		                commitDefaulsInVirginMode();
		            }
		        break;
		    }
		    if(valchanged) {
		      
		    } else {
		        Log.d(TAG,"Notification Recevied but value not changed " + prop);
		    }
		}
	};
	
    public void registerTvSettingsManager(){
        Log.d(TAG, "registerTvSettingsManager Enter");
        
        property = new int [PROPMAX];
        property_cache = new int [PROPMAX];
		SettingsListener SettingsListener = new SettingsListener();

        property[0] = TvSettingsConstants.INSTALLATIONCOUNTRY;
        property_cache[0] = -1; // change due to TF515PHIALLMTK01-23776 commented out:mTvSettingsManager.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0,0);
               
        mTvSettingsManager.SetCallBacks(SettingsListener, property);
        
        Log.d(TAG, "registerTvSettingsManager Exit");
        
    }
    public synchronized void commitDefaulsInVirginMode() {

        int ifVirginMode = mTvSettingsManager.getInt(TvSettingsConstants.VIRGINBIT, 0, 0);
		int mMedium 	 = mTvSettingsManager.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
        Log.d(TAG, "commitDefaultsInVirginMode ifVirginMode " + ifVirginMode);
        if (ifVirginMode == 1) {
		
			mTvAudioMgr = ITvAudioManager.Instance.getInterface(); //new TvVideoManager();
            Log.d(TAG, "commitDefaultsInVirginMode started");
            int mSystemCountry = mTvSettingsManager.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);

            if ((mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.SWEDEN) || (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.NORWAY)
                    || (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.DENMARK) || (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.FINLAND)
                    || (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.UKRAINE) || (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.IRELAND)
                    || (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.FRANCE)) {
                // set subtitle to on
                mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 1);
            }
			else if( (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.MALAYSIA) ||
				(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.VIETNAM) ){
                mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 0);
			}	

			
			if((mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.SWEDEN) || (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.NORWAY)
				|| (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.DENMARK) || (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.FINLAND)) 
			{
					// set Logos to off
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSCHANNELLOGOS, 0, 0);
			}
			else
			{
				// set Logos to on
					mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSCHANNELLOGOS, 0, 1);
			}

            int mMenuLanguage = mTvSettingsManager.getInt(TvSettingsConstants.MENULANGUAGE, 0, 0);
            if ((mMenuLanguage == TvSettingsDefinitions.InstallationLanguageConstants.THAI) || (mMenuLanguage == TvSettingsDefinitions.InstallationLanguageConstants.ARABIC)
                    || (mMenuLanguage == TvSettingsDefinitions.InstallationLanguageConstants.HEBREW) || (mMenuLanguage == TvSettingsDefinitions.InstallationLanguageConstants.HUNGAL)
                    || (mMenuLanguage == TvSettingsDefinitions.InstallationLanguageConstants.MALAY) || (mMenuLanguage == TvSettingsDefinitions.InstallationLanguageConstants.PERSIAN)
                    || (mMenuLanguage == TvSettingsDefinitions.InstallationLanguageConstants.TAIWANESE)) {

                mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE, 0, TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH);
                mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE, 0, TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH);
                mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDPRIMARYTXTLANGUAGE, 0, TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH);
            } else {
                mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE, 0, mMenuLanguage);
                mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE, 0, mMenuLanguage);
                mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDPRIMARYTXTLANGUAGE, 0, mMenuLanguage);
            }

            mTvSettingsManager.putInt(TvSettingsConstants.PREFERREDSECONDARYAUDIOLANGUAGE, 0, TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH);
            mTvSettingsManager.putInt(TvSettingsConstants.PREFERREDSECONDARYSUBTITLELANGUAGE, 0, TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH);
            mTvSettingsManager.putInt(TvSettingsConstants.PREFERREDSECONDARYTXTLANGUAGE, 0, TvSettingsDefinitions.InstallationLanguageConstants.ENGLISH);


			
			if(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.IRELAND)
			{
				mTvSettingsManager.putInt(TvSettingsConstants.PREFERREDSECONDARYAUDIOLANGUAGE, 0, TvSettingsDefinitions.InstallationLanguageConstants.IRISH);
				mTvSettingsManager.putInt(TvSettingsConstants.PREFERREDSECONDARYSUBTITLELANGUAGE, 0, TvSettingsDefinitions.InstallationLanguageConstants.IRISH);
			} 
			if ((mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.SWEDEN)&&(mMedium == TvSettingsDefinitions.InstSettingsInstallMode.CABLE)
				|| (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.HUNGARY)&&(mMedium == TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA)
				||((mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.NEWZEALAND) && (mMedium == TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA)))
			{
					mTvSettingsManager.putInt(TvSettingsConstants.DIGITALOUTPUTFORMAT, 0, TvSettingsDefinitions.DigitalOutputFormatConstants.MULTICHANNEL);
					mTvAudioMgr.setProperty(ITvAudioManager.AUDMGR_PROPERTY_SPDIF_MODE, ITvAudioManager.AUDMGR_SPDIF_OUTPUT_MODE_BITSTREAM);
			}
			else
			{
				mTvSettingsManager.putInt(TvSettingsConstants.DIGITALOUTPUTFORMAT, 0, TvSettingsDefinitions.DigitalOutputFormatConstants.STEREO);
				mTvAudioMgr.setProperty(ITvAudioManager.AUDMGR_PROPERTY_SPDIF_MODE, ITvAudioManager.AUDMGR_SPDIF_OUTPUT_MODE_PCM);
			}
			
            // Preferred Audio format
            mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOFORMAT, 0, 0);

            // Original language false
            mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSORIGINALLANGUAGE, 0, 0);

            // visually impaired status
            mTvSettingsManager.putInt(TvSettingsConstants.VISUALLYIMPAIREDSTATUS, 0, 0);

            // hearing impaired status
            mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSHEARINGIMPAIRED, 0, 0);

            // SetChannelUpdateDialogueSetting
            mTvSettingsManager.putInt(TvSettingsConstants.CHANNELUPDATEDIALOGUE, 0, 0);

            // visually impaired speech preference descriptive
            mTvSettingsManager.putInt(TvSettingsConstants.VISUALLYIMPAIREDSPEECHPREFERENCE, 0, TvSettingsDefinitions.VisuallyImPairedConstants.OFF);

            // visually impaired seamless mixing
            mTvSettingsManager.putInt(TvSettingsConstants.VISUALLYIMPAIREDSEAMLESSMIXING, 0, 1);

            // set the clock mode to automatic
            // if (mSystemCountry !=
            // TvSettingsDefinitions.InstallationCountryConstants.NETHERLANDS) {
            mTvSettingsManager.putInt(TvSettingsConstants.AUTOCLOCKMODE, 0, TvSettingsDefinitions.InstallationClockModeConstants.AUTOMATICCLOCKMODE);
            // }

            // set the parental rating
            // If the country is Italy or France, parental rating shall be set to Age 18.
            if ( (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.ITALY) || 
            		(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.FRANCE) ||
            		(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.ROMANIA)){
				nwrap.setParentalRating(mSystemCountry, "18");
                mTvSettingsManager.putInt(TvSettingsConstants.DVBPARENTALRATING, 0, TvSettingsDefinitions.ParentalRatingConstants.AGE18);
            }else{
            	nwrap.setParentalRating(mSystemCountry, "none");
            	mTvSettingsManager.putInt (TvSettingsConstants.DVBPARENTALRATING, 0, TvSettingsDefinitions.ParentalRatingConstants.NONE);
            }

			if ((mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.AUSTRALIA)
					|| (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.NEWZEALAND)
					|| (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.SINGAPORE))
			{
				nwrap.setParentalRating(mSystemCountry, "none");
				mTvSettingsManager.putInt(TvSettingsConstants.DVBPARENTALRATING, 0, TvSettingsDefinitions.ParentalRatingConstants.NONE);
			}         
            
            // AN-34339
            if (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.FRANCE) {
				 mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE , 0, 2);
			 }
            if (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.FINLAND) {
				 mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE , 0, 1);
			 }

			//making default EPG as Braodcast EPG with CR,AN-81715 for Slovenia & RMCR-3597 M7 Countries
            /* remove for default is always DVBEPG
			if( (mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.SLOVENIA   ) ||
				(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.NETHERLANDS) ||
				(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.BELGIUM    ) ||
				(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.LUXEMBOURG ) ||
				(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.AUSTRIA    ) ||
				(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.CZECHREP   ) ||
				(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.SLOVAKIA   ) ||
				(mSystemCountry == TvSettingsDefinitions.InstallationCountryConstants.HUNGARY    ) 
			  )
			{
				
				mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSDVBEPGCHOICE , 0, TvSettingsDefinitions.InstSettingsDvbEpgConstants.DVBEPG);
			}
			else
			{
				mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSDVBEPGCHOICE , 0,TvSettingsDefinitions.InstSettingsDvbEpgConstants.AUTO);
			}*/

				/*The below changes are brought in accordance with RMCR:3578*/	
			nwrap.mSettingOnOffDiversityOfHBBTVStatus(mSystemCountry);
			
            Log.d(TAG, "commitDefaultsInVirginMode completed");
        }
    }
}
