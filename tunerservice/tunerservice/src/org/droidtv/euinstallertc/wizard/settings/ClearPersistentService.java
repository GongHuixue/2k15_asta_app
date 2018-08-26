package org.droidtv.euinstallertc.wizard.settings;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import android.app.IntentService;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class ClearPersistentService extends IntentService {
	private final String TAG = ClearPersistentService.class.getName();
	private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();

	public ClearPersistentService() {
		super("AutomaticChannelUpdateService");
	}

	@Override
	protected void onHandleIntent(Intent intent) {
		int enumVal = 0;

		if (intent != null) {
			m_wrapper.clearPersistent();
		}

		Log.d(TAG, "ClearPersistentService");
	}
}
