package org.droidtv.euinstallersat.wizard.satip;

import android.util.Log;

public class SatIPHubItemInfo {
	private static final String TAG = SatIPHubItemInfo.class.getName();
	public String displayText;
	public String hintText;
	public boolean isCompleted;
	public boolean isExecutedOnce;
	public int itemPos;
	public String displaySubText;

	public SatIPHubItemInfo(int argItemPos, String argDisplayText,
			String argHintText, String argDisplaySubText,  boolean argIsCompleted,
			boolean argIsExecutedOnce) {
		Log.d(TAG, "ItemInfo Constructor: " + ", " + argDisplayText + ", "
				+ argIsCompleted);
		displayText = argDisplayText;
		hintText = argHintText;
		displaySubText = argDisplaySubText;
		isCompleted = argIsCompleted;
		itemPos = argItemPos;
		isExecutedOnce = argIsExecutedOnce;
	}
}
