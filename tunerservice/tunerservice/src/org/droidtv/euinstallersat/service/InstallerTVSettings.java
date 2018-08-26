package org.droidtv.euinstallersat.service;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.ITvSettingsManager.ITvSettingsManagerNotify;

import android.util.Log;

public class InstallerTVSettings {
	private static final String TAG = InstallerTVSettings.class.getName();
	private ITvSettingsManager msettings=ITvSettingsManager.Instance.getInterface();
	private int[] property;
	private int[] property_cache;
	private static final int PROPMAX = 1;
	private NativeAPIWrapper nwrap = null;

	public InstallerTVSettings() {
		Log.d(TAG, "InstallerTVSettings Constuctor");
	}
	
	class SettingsListener extends ITvSettingsManagerNotify{
			//@Override
		public void OnUpdate(int prop){
				boolean valchanged = false;
		   Log.d(TAG, "Notification From Global Setting Received  " + prop);
				switch (prop) {
				case TvSettingsConstants.VIRGINBIT:
				int value=msettings.getInt(TvSettingsConstants.VIRGINBIT, 0, 0);
					if (property_cache[0] != value) {
						Log.d(TAG, "Virgin bit changed in TVSettings");
						property_cache[0] = value;
						valchanged = true;
						ifVirginMode();
					}
					break;
				}
				if (valchanged) {

				} else {
					Log.d(TAG, "Notification Recevied but value not changed " + prop);
				}
			}
		};
	public void registerTvSettingsManager() {
		Log.d(TAG, "registerTvSettingsManager Enter");
		property = new int[PROPMAX];
		property_cache = new int[PROPMAX];
		SettingsListener SettingsListener = new SettingsListener();
		property[0] = TvSettingsConstants.VIRGINBIT;
		property_cache[0] = msettings.getInt(TvSettingsConstants.VIRGINBIT, 0, 0);
		msettings.SetCallBacks(SettingsListener, property);
		Log.d(TAG, "registerTvSettingsManager Exit");

	}

	public synchronized void ifVirginMode() {
		int ifVirginMode = msettings.getInt(TvSettingsConstants.VIRGINBIT, 0, 0);
		int country = msettings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
		Log.d(TAG, "ifVirginMode " + ifVirginMode);
		if ((ifVirginMode == 0) && (country == TvSettingsDefinitions.InstallationCountryConstants.FRANCE)) {
			// just came out of virgin mode
			
			// AN-70406
			// create a wrapper instance
			nwrap = NativeAPIWrapper.getInstance();
			// register for CAM notifications
			nwrap.getSatInstaller(TunerName.TUNER1).registerAndReqForOpProf();
		}
	}
}
