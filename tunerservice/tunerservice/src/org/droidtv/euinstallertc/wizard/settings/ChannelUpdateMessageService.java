package org.droidtv.euinstallertc.wizard.settings;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.settings.SettingsConstants;
import android.app.IntentService;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class ChannelUpdateMessageService extends IntentService {
	private final String TAG = ChannelUpdateMessageService.class.getName();
	private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();

	public ChannelUpdateMessageService() {
		super("ChannelUpdateMessageService");
	}

	@Override
	protected void onHandleIntent(Intent intent) {
		int enumVal = 0;

		if (intent != null) {
			enumVal = intent.getIntExtra("value", -1);

			if (enumVal == SettingsConstants.enumON) {
				m_wrapper.SetStartUpMsg(true);
			} else if (enumVal == SettingsConstants.enumOFF) {
				m_wrapper.SetStartUpMsg(false);
			}
		}

		Log.d(TAG, "\nGet " + enumVal + " from " + (intent!=null));
	}
}
