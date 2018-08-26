package org.droidtv.euinstallertc.brdcstreceiver;

import android.content.BroadcastReceiver;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

public class TimeChangeReceiver extends BroadcastReceiver{
	private static final String TAG ="TimeChangeReceiver";
	
	@Override
	public void onReceive(Context context, Intent intent) {
		
		try {

				Log.d(TAG,"Entered TimeChangeReceiver\n");
				NativeAPIWrapper.getInstance().checkStartScheduleUpdate();
		}catch(Exception e){
			Log.d(TAG,"Exception in parsing the intent");
		}
	}
}
