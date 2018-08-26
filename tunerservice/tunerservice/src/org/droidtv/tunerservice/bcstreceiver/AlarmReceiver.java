package org.droidtv.tunerservice.bcstreceiver;

import org.droidtv.tunerservice.recording.RecService;
import org.droidtv.tunerservice.recording.AutoPVR;
import org.droidtv.tunerservice.recording.Reminder;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

public class AlarmReceiver extends BroadcastReceiver{
	private static final String TAG = "AlarmReceiver";
	
	@Override
	public void onReceive(Context context, Intent intent) {

		Uri data = intent.getData();
		String scheme = data.getScheme();
		Log.d(TAG, "onReceive scheme-> "+ scheme);
		if(scheme.equals("rec"))
		{
			Bundle alarmBundle = intent.getExtras();
			int recId = (Integer) alarmBundle.get("recordId");
	        Log.d(TAG, "Alarm Fired for Recording " + recId);
	        int reqId=(Integer)alarmBundle.getInt("reqId");
	        if(RecService.getInstance() != null)
	        {
	        	RecService.getInstance().onAlarm(recId,reqId);
	        } else {
	        	Log.d(TAG, "recservice null, not able to handle recording alarm");
	        }
		}		
		if(scheme.equals("auto_pvr")) {
			Bundle alarmBundle = intent.getExtras();
			int recId = (Integer) alarmBundle.get("recordId");
	        Log.d(TAG, "Alarm Fired for Auto PVR " + recId);
            //Auto PVR not supported
	        //AutoPVR.getInstance().onAlarm(recId);
		}
		if(scheme.equals("recvalidity"))
		{
			Bundle alarmBundle = intent.getExtras();
			int recId = (Integer) alarmBundle.get("recordId");
	        Log.d(TAG, "Alarm Fired for Validity check: Recording ID " + recId);
	        if(RecService.getInstance() != null)
	        {
	        	RecService.getInstance().recValidityCheck.onAlarm(recId);
	        }
	        else {
	        	Log.d(TAG, "recservice null, not able to handle recValidityCheck alarm");
	        }
		}
		if(scheme.equals("rem")) {
			Log.d(TAG, "Alarm Fired for reminder");
            Reminder.getInstance(context.getApplicationContext()).onAlarm();
		}
	}
}
