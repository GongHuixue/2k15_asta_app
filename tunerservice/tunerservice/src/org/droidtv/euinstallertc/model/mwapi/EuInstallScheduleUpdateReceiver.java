package org.droidtv.euinstallertc.model.mwapi;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

public class EuInstallScheduleUpdateReceiver extends BroadcastReceiver{
	private static final String TAG ="SSBYServiceAlmReceiver";
	
	@Override
	public void onReceive(Context context, Intent intent) {
		Uri data = intent.getData();
		try {
		
			String scheme = data.getScheme();
			Log.d(TAG, "onReceive scheme-> "+ scheme);
			if(scheme.equals("scheduleUpdateAlarm")) {
				NativeAPIWrapper.getInstance().onAlarmFired();
			}
		}catch(Exception e){
			Log.d(TAG,"Exception in parsing the intent");
		}
	}
}