package org.droidtv.euinstallertc.wizard.settings;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.settings.SettingsConstants;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;
import android.app.IntentService;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class AutomaticChannelUpdateService extends IntentService {
	private final String TAG = AutomaticChannelUpdateService.class.getName();
	private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;

	public AutomaticChannelUpdateService() {
		super("AutomaticChannelUpdateService");
	}

	@Override
	protected void onHandleIntent(Intent intent) {
		int enumVal = 0;

		if (intent != null) {
			enumVal = intent.getIntExtra("value", -1);

			if (enumVal == SettingsConstants.enumON) {
				m_wrapper.SetStandbyUpdate(true);
			} else if (enumVal == SettingsConstants.enumOFF) {
				m_wrapper.SetStandbyUpdate(false);
				messenger = TvToastMessenger.getInstance(this);
				mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
				mTimeOutTvToast.setMessage(this.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_AUTOMATIC_UPDATE_OFF));
				messenger.showTvToastMessage(mTimeOutTvToast);
			}
		}

		Log.d(TAG, "\nGet " + enumVal + " from " + (intent!=null));
	}
}
