package org.droidtv.tunerservice.overlay;

import java.util.Map;

import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.InstallationCountryConstants;
import org.droidtv.tv.video.IVideoProperties;
import org.droidtv.tv.video.IVideoProperties.IVideoPropertiesChangedListener;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tunerservice.interfaces.IOverlayListener;

import android.media.tv.TvContract;
import android.os.Handler;
import android.util.Log;

public class RadioBGHandler implements IOverlayListener {

	private static final String TAG = RadioBGHandler.class.getSimpleName();
	private final static int HYS_TIME = 6000;
	public static final String SERVICE_TYPE = "serviceType";
		
	private Handler mHandler = null;
	private OverlayManager mOverlayMgr = null;
	private String mServiceType = null;
	private IVideoProperties mVidProp = null;
	private VideoPropertiesListener mlistener = null;
	private radioRunnable mRunnable = null;
	private boolean timerexpired = false;
	private int mLockStatus = 0;
	private ITvSettingsManager globalSetting;
	private int mCurrentCountry = -1;
	private boolean mIsRadioBGDisabled = false;
	// Reno 20150420 HTV show on screen clock on radio channel
	private static boolean isPbsMode = false;
	private static boolean isDisplayOsc = false;
	private IPbsSettingsEventCallbacks mPbsSettingCallbacks = null;
	private static final int[] pbsSettingsEvent = new int[] {TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE, TvSettingsConstants.PBSMGR_PROPERTY_CLOCK_DISPLAY_CLOCK_ON_RADIO};
	// Reno
	
	public RadioBGHandler() {
		Log.d(TAG, "RadioBackground cunstructor");
		mHandler = new Handler();
		globalSetting = ITvSettingsManager.Instance.getInterface();
		mCurrentCountry = globalSetting.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		
	}
		
	public void onLockStatusChanged(int type, int status){
		Log.d(RadioBGHandler.class.getSimpleName(), "onLockStatusChanged " + status + " timerExpired " +timerexpired);
		mLockStatus = status;
		if(timerexpired){
			evaluateRadioBG();
		}
	}
	
	public void onPlayStarted() {		
		reset();
	}
	
	public void onPlayCompleted(Map<String, String> headers, IVideoProperties lVidPropties) {
		if(headers!=null && (!isMhegEnabledCountry())){
			mServiceType = headers.get(TvHeaders.SERVICE_TYPE);
			mVidProp = lVidPropties;
			if((mServiceType != null) && 
				(mServiceType.equalsIgnoreCase(TvContract.Channels.SERVICE_TYPE_AUDIO))) {
				mlistener = new VideoPropertiesListener();
				mVidProp.registerIVideoPropertiesChangeListener(mlistener);
				mRunnable = new radioRunnable();
				mHandler.postDelayed(mRunnable, HYS_TIME);
				// Reno 20150420 HTV show on screen clock on radio channel
				isPbsMode = (globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE, 0, 0)
						== TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON);
				isDisplayOsc = (globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CLOCK_DISPLAY_CLOCK_ON_RADIO, 0, 0)
						== TvSettingsDefinitions.PbsDisplayClockRadioChannelConstants.PBSMGR_RADIO_CHANNEL_YES);
				mPbsSettingCallbacks = new IPbsSettingsEventCallbacks();
				globalSetting.SetCallBacks(mPbsSettingCallbacks, pbsSettingsEvent);
				// Reno
			}
		}
	}
	
	private boolean isMhegEnabledCountry(){
		boolean mhegEnabled = false;

		//Always show if PBS mode on & OSC on
		//---- [TF415PHIEUMTK03-1294] Display clock on radio channel does not work after AC off/on.
		if ((globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE, 0, 0)
						== TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON)) {

			if ((globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CLOCK_DISPLAY_CLOCK_ON_RADIO, 0, 0)
						== TvSettingsDefinitions.PbsDisplayClockRadioChannelConstants.PBSMGR_RADIO_CHANNEL_YES)) {
				Log.d(TAG,"pbs mode on & OSC on, always show OSC even UK/IRELAND");
				return false;
			}
		}
		//----

		if(mCurrentCountry == InstallationCountryConstants.UK || mCurrentCountry == InstallationCountryConstants.IRELAND){
			mhegEnabled = true;
		}
		Log.d(TAG, "isMhegEnabledCountry " +mhegEnabled);
		return mhegEnabled;
	}
	
	private class radioRunnable implements Runnable{
		boolean ena = true;
		public void disable() {
			ena = false;
		}
		@Override
		public void run() {
			if(ena) {
				timerexpired = true;
				if(isRadioBGRequired() && !mIsRadioBGDisabled) {
					if(mOverlayMgr!=null) {
						//mOverlayMgr.addRadioView();
						// Reno 20150420 HTV show on screen clock on radio channel
						if (isPbsMode && isDisplayOsc) {
							mOverlayMgr.addRadioChOscView();
						} else {
							mOverlayMgr.addRadioView();
						}
						// Reno
					}
				}
			}
		}
	};
	
	private boolean isRadioBGRequired() {
		boolean retVal = false;
		try{
			if(timerexpired && mVidProp != null) {
				if((mVidProp.getSignalPresent()==IVideoProperties.SIGNALPRESENCE_DETECTED) 
						&& (mVidProp.getVideoPresent() ==IVideoProperties.VIDEOPRESENCE_NOTDETECTED)
						&& (mLockStatus == 0)) {
					retVal = true;
				}
			}
		}
		catch(Exception e){
			Log.e(TAG,"getSignalPresent/getVideoPresent() exception caught!!!" +e.toString());
		}
		return retVal;
	}
	
	protected class VideoPropertiesListener extends IVideoPropertiesChangedListener{
		@Override
		public void onSignalPresentChanged(int isSignalPresent) {
			Log.d(TAG, "onSignalPresentChanged isSignalPresent "+isSignalPresent);
			evaluateRadioBG();
		}
		
		@Override
		public void onVideoPresentChanged(int isVideoPresent) {
			Log.d(TAG, "onVideoPresentChanged isVideoPresent "+isVideoPresent);
			evaluateRadioBG();
		}
	}
	
	private void evaluateRadioBG(){
		if(mOverlayMgr!=null) {
			if(isRadioBGRequired() && ! mIsRadioBGDisabled){
				//mOverlayMgr.addRadioView();
				// Reno 20150420 HTV show on screen clock on radio channel
				if (isPbsMode && isDisplayOsc) {
					mOverlayMgr.addRadioChOscView();
				} else {
					mOverlayMgr.addRadioView();
				}
				// Reno
			}else {
				//mOverlayMgr.removeRadioView();
				// Reno 20150420 HTV show on screen clock on radio channel
				if (isPbsMode && isDisplayOsc) {
					mOverlayMgr.removeRadioChOscView();
				} else {
					mOverlayMgr.removeRadioView();
				}
				// Reno
			}
		}
	}

	public void setOverlayManager(OverlayManager overlayManager) {
		if(overlayManager == null) {
			reset();
		}
		if(mOverlayMgr == null && overlayManager != null && globalSetting != null){
			mCurrentCountry = globalSetting.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		}
		mOverlayMgr = overlayManager;
		if(mOverlayMgr != null){
			mOverlayMgr.registerForOverlayCallback(this);
		}
	}
	
	private void reset() {
		if(mOverlayMgr!=null){
			//mOverlayMgr.removeRadioView();
			// Reno 20150420 HTV show on screen clock on radio channel
			if (isPbsMode && isDisplayOsc) {
				mOverlayMgr.removeRadioChOscView();
			} else {
				mOverlayMgr.removeRadioView();
			}
			// Reno
		}
		if(mRunnable!=null) {
			mHandler.removeCallbacks(mRunnable,null);
			mRunnable.disable();
		}
		timerexpired = false;
		mLockStatus = 0;
		if(mlistener != null){
			if(mVidProp!=null) {
				mVidProp.unregisterIVideoPropertiesChangeListener(mlistener);
			}
			mlistener = null;
		}		
		// Reno 20150420 HTV show on screen clock on radio channel
		if(mPbsSettingCallbacks != null){
			if(globalSetting != null) {
				globalSetting.UnSetCallBacks(mPbsSettingCallbacks, pbsSettingsEvent);
			}
			mPbsSettingCallbacks = null;
		}
		// Reno
	}
	
	@Override
	public void releaseOverlayManager() {
	}
	
	@Override
	public void setOverLayViewStatus(int viewStatus){
		if(mIsRadioBGDisabled && ((viewStatus&ITVSessionContext.OVERLAY_VIEW_RADIOBACKGROUND) > 0)) {
			mIsRadioBGDisabled = false;
			if((mServiceType != null) && (mServiceType.equalsIgnoreCase(TvContract.Channels.SERVICE_TYPE_AUDIO))) {
				if(mOverlayMgr!=null) {
					if(isRadioBGRequired()){
						//mOverlayMgr.addRadioView();
						// Reno 20150420 HTV show on screen clock on radio channel
						if (isPbsMode && isDisplayOsc) {
							mOverlayMgr.addRadioChOscView();
						} else {
							mOverlayMgr.addRadioView();
						}
						// Reno
					}
				}
			}
			
		}else if ((viewStatus&ITVSessionContext.OVERLAY_VIEW_RADIOBACKGROUND) == 0) {
			mIsRadioBGDisabled = true;
			if((mServiceType != null) && (mServiceType.equalsIgnoreCase(TvContract.Channels.SERVICE_TYPE_AUDIO))) {
				if(mOverlayMgr!=null) {
					//mOverlayMgr.removeRadioView();
					// Reno 20150420 HTV show on screen clock on radio channel
					if (isPbsMode && isDisplayOsc) {
						mOverlayMgr.removeRadioChOscView();
					} else {
						mOverlayMgr.removeRadioView();
					}
					// Reno
				}
			}
		}
	}

	// Reno 20150420 HTV show on screen clock on radio channel
	class IPbsSettingsEventCallbacks extends ITvSettingsManager.ITvSettingsManagerNotify {
		public void OnUpdate(int property) {
			Log.d(TAG, "IPbsSettingsEventCallbacks - OnUpdate - property == " + property);

			switch (property) {
				case TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE:
				case TvSettingsConstants.PBSMGR_PROPERTY_CLOCK_DISPLAY_CLOCK_ON_RADIO:
					switchRadioChBG();
					break;

				default:
					Log.w(TAG, "unexpected event");
					break;
			}
		}
	}

	private void switchRadioChBG() {
		if (mOverlayMgr != null) {
			if (isRadioBGRequired()) {
				int settingPbsMode = globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE, 0, 0);
				int settingOscOnRadioCh = globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CLOCK_DISPLAY_CLOCK_ON_RADIO, 0, 0);
				Log.d(TAG, "pbs mode value == " + settingPbsMode);
				Log.d(TAG, "isPbsMode == " + isPbsMode);
				Log.d(TAG, "show osc on radio channel value == " + settingOscOnRadioCh);
				Log.d(TAG, "isDisplayOsc == " + isDisplayOsc);

				if (!isPbsMode && settingPbsMode == TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON) {
					isPbsMode = true;
					if (isDisplayOsc) {
						mOverlayMgr.removeRadioView();
						mOverlayMgr.addRadioChOscView();
					}
				} else if (isPbsMode && settingPbsMode == TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_OFF) {
					isPbsMode = false;
					if (isDisplayOsc) {
						mOverlayMgr.removeRadioChOscView();
						mOverlayMgr.addRadioView();
					}
				}

				if (isDisplayOsc && settingOscOnRadioCh == TvSettingsDefinitions.PbsDisplayClockRadioChannelConstants.PBSMGR_RADIO_CHANNEL_NO) {
					isDisplayOsc = false;
					if (isPbsMode) {
						mOverlayMgr.removeRadioChOscView();
						mOverlayMgr.addRadioView();
					}
				} else if (!isDisplayOsc && settingOscOnRadioCh == TvSettingsDefinitions.PbsDisplayClockRadioChannelConstants.PBSMGR_RADIO_CHANNEL_YES) {
					isDisplayOsc = true;
					if (isPbsMode) {
						mOverlayMgr.removeRadioView();
						mOverlayMgr.addRadioChOscView();
					}
				}

			}
		}
	}

}
