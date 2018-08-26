/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.droidtv.tunerservice.services.sbyservice;

import android.content.ContentResolver;
import android.content.Context;
import android.content.res.Resources;
import android.os.SystemClock;
import android.provider.Settings;
import android.util.Log;
/*begin:min.jiang add 2015-06-29, for pbs date and time settings*/
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager.ITvSettingsManagerNotify;
/*end:min.jiang add*/
/**
 * {@link TrustedTime} that connects with a remote NTP server as its trusted
 * time source.
 *
 * @hide
 */
public class NtpTrustedTime implements TrustedTime {
    private static final String TAG = "NtpTrustedTime";
    private static final boolean LOGD = false;

    private static NtpTrustedTime sSingleton;

    private /*final*/ String mServer;
    private final long mTimeout;

    private boolean mHasCache;
    private long mCachedNtpTime;
    private long mCachedNtpElapsedRealtime;
    private long mCachedNtpCertainty;
	/*begin:min.jiang add 2015-06-29, for pbs date and time settings*/
	private static ITvSettingsManager globalSetting;
	private static int NTPSourceType = 0;
	private static String NTPUserUri = "";
	private static ITvSettingsManager mTvSettingsManager = ITvSettingsManager.Instance.getInterface();
    
	class ICPNtpSettingsNotify extends ITvSettingsManagerNotify{
		public void OnUpdate(int property) {
			String defaultServer = "2.android.pool.ntp.org";
			if(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE ,0,0) == 
				TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON) {
	            if(property == TvSettingsConstants.PBSMGR_PROPERTY_DNT_NTP_SOURCE ||
	               property == TvSettingsConstants.PBSMGR_PROPERTY_DNT_CUSTOM_NTP_SERVER) {
	                
	    			NTPSourceType = mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_NTP_SOURCE, 0, 0);
	    			NTPUserUri = mTvSettingsManager.getString(TvSettingsConstants.PBSMGR_PROPERTY_DNT_CUSTOM_NTP_SERVER, 0, "");
	    			if(NTPSourceType != 0){
	    				defaultServer = NTPUserUri;
	    			}     
	                mServer = defaultServer;	                
	            }
			}else {
				mServer = defaultServer;
			}
			Log.d(TAG, "OnUpdate NtpTrustedTime using " + mServer);
        }   
    }
    /*end:min.jiang add*/

    private NtpTrustedTime(String server, long timeout) {
        if (LOGD) Log.d(TAG, "creating NtpTrustedTime using " + server);
        mServer = server;
        mTimeout = timeout;
        /*begin:min.jiang add 2015-06-29, for pbs date and time settings*/
        mTvSettingsManager.SetCallBacks(new ICPNtpSettingsNotify(), new int[]{
            TvSettingsConstants.PBSMGR_PROPERTY_DNT_NTP_SOURCE,
            TvSettingsConstants.PBSMGR_PROPERTY_DNT_CUSTOM_NTP_SERVER   ,
            TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE
        });
        /*end:min.jiang add*/
    }

    public static synchronized NtpTrustedTime getInstance(Context context) {
        if (sSingleton == null) {
            //final Resources res = context.getResources();
            //final ContentResolver resolver = context.getContentResolver();
            /*begin:min.jiang add 2015-06-29, for pbs date and time settings*/
            String defaultServer = /*res.getString(R.string.config_ntpServer);*/"2.android.pool.ntp.org";
            final long defaultTimeout = 30000;
			if ( mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE ,0,0) == TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON ){
				//[HTV][NTP] store ntp server to system. 
				globalSetting = ITvSettingsManager.Instance.getInterface();
				NTPSourceType = globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_NTP_SOURCE, 0, 0);
				NTPUserUri = globalSetting.getString(TvSettingsConstants.PBSMGR_PROPERTY_DNT_CUSTOM_NTP_SERVER, 0, "");

				if(NTPSourceType != 0){
					defaultServer = NTPUserUri;
				}
				Log.d(TAG, "defaultServer: "+ defaultServer + "PBSMGR_PROPERTY_DNT_NTP_SOURCE: " + NTPSourceType);
			}
			/*end:min.jiang add*/
            //final String secureServer = Settings.Global.getString(resolver, Settings.Global.NTP_SERVER);
            //final long timeout = Settings.Global.getLong(resolver, Settings.Global.NTP_TIMEOUT, defaultTimeout);

            //final String server = secureServer != null ? secureServer : defaultServer;
            sSingleton = new NtpTrustedTime(defaultServer, defaultTimeout);
        }

        return sSingleton;
    }

    @Override
    public boolean forceRefresh() {
        if (mServer == null) {
            // missing server, so no trusted time available
        	Log.d(TAG, "forceRefresh() Server Null");
            return false;
        }

        if (LOGD) Log.d(TAG, "forceRefresh() from cache miss");
        final SntpClient client = new SntpClient();
        if (client.requestTime(mServer, (int) mTimeout)) {
        	mHasCache = true;
            mCachedNtpTime = client.getNtpTime();
            mCachedNtpElapsedRealtime = client.getNtpTimeReference();
            mCachedNtpCertainty = client.getRoundTripTime() / 2;
            return true;
        } else {
        	Log.d(TAG, "forceRefresh() Server request Null");
        	return false;
        }
    }

    @Override
    public boolean hasCache() {
        return mHasCache;
    }

    @Override
    public long getCacheAge() {
        if (mHasCache) {
            return SystemClock.elapsedRealtime() - mCachedNtpElapsedRealtime;
        } else {
            return Long.MAX_VALUE;
        }
    }

    @Override
    public long getCacheCertainty() {
        if (mHasCache) {
            return mCachedNtpCertainty;
        } else {
            return Long.MAX_VALUE;
        }
    }

    @Override
    public long currentTimeMillis() {
        if (!mHasCache) {
            throw new IllegalStateException("Missing authoritative time source");
        }
        if (LOGD) Log.d(TAG, "currentTimeMillis() cache hit");

        // current time is age after the last ntp cache; callers who
        // want fresh values will hit makeAuthoritative() first.
        return mCachedNtpTime + getCacheAge();
    }

    public long getCachedNtpTime() {
        if (LOGD) Log.d(TAG, "getCachedNtpTime() cache hit");
        return mCachedNtpTime;
    }

    public long getCachedNtpTimeReference() {
        return mCachedNtpElapsedRealtime;
    }
}
