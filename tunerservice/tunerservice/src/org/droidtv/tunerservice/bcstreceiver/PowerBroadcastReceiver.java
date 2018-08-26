package org.droidtv.tunerservice.bcstreceiver;

import org.droidtv.tunerservice.recording.RecService;
import org.droidtv.tunerservice.recording.Reminder;
import org.droidtv.tunerservice.services.sbyservice.SemiStandbyService;
import org.droidtv.tunerservice.tvmanager.MainTVManager;
import org.droidtv.tunerservice.tvmanager.AuxTVManager;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class PowerBroadcastReceiver extends BroadcastReceiver{
	private static final String TAG = "SSBYTvPowerReceiver"; 
	@Override
	public void onReceive(Context context, Intent intent) {
		String sAction = intent.getAction();
		Bundle extras = intent.getExtras();		
		if(TvIntent.ACTION_TV_POWER_STATE_CHANGE_BEGIN.equals(sAction)) {
			PowerStates from = (PowerStates) intent.getSerializableExtra(TvIntent.SOURCE_TV_POWER_MODE);
			PowerStates to   = (PowerStates) intent.getSerializableExtra(TvIntent.TARGET_TV_POWER_MODE);
			Log.i(TAG, "Received Powerstatechange Start from " + from + " to " + to);
			if(SemiStandbyService.getPowerEventsListener()!=null){
				SemiStandbyService.getPowerEventsListener().onPowerChangeStart(from,to,extras);
			}
			if(RecService.getInstance()!=null  && RecService.getPowerEventsListener()!=null){
				RecService.getPowerEventsListener().onPowerChangeStart(from, to,extras);
			}
			if(MainTVManager.getPowerEventsListener()!=null){
				MainTVManager.getPowerEventsListener().onPowerChangeStart(from,to,extras);
			}
			if(AuxTVManager.getPowerEventsListener()!=null){
				AuxTVManager.getPowerEventsListener().onPowerChangeStart(from,to,extras);
			}
		}
		else if(TvIntent.ACTION_TV_POWER_STATE_CHANGED.equals(sAction)) {
			PowerStates from = (PowerStates) intent.getSerializableExtra(TvIntent.SOURCE_TV_POWER_MODE);
			PowerStates to   = (PowerStates) intent.getSerializableExtra(TvIntent.TARGET_TV_POWER_MODE);
			Log.i(TAG, "Received Powerstatechange End from " + from + " to " + to);
			if(SemiStandbyService.getPowerEventsListener()!=null){
				SemiStandbyService.getPowerEventsListener().onPowerChangeEnd(from,to,extras);
			}
			if(RecService.getInstance()!=null  && RecService.getPowerEventsListener()!=null){
				RecService.getPowerEventsListener().onPowerChangeEnd(from, to,extras);
			}
			if(MainTVManager.getPowerEventsListener()!=null){
				MainTVManager.getPowerEventsListener().onPowerChangeEnd(from,to,extras);
			}
			if(AuxTVManager.getPowerEventsListener()!=null){
				AuxTVManager.getPowerEventsListener().onPowerChangeEnd(from,to,extras);
			}
			if(Reminder.getPowerEventsListener() !=null ){
				Reminder.getPowerEventsListener().onPowerChangeEnd(from, to,extras);
			}
		}
	}
}
