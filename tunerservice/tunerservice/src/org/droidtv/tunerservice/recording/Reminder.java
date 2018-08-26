package org.droidtv.tunerservice.recording;

import java.util.ArrayList;

import org.droidtv.tunerservice.bcstreceiver.AlarmReceiver;
import org.droidtv.tunerservice.interfaces.IPowerEvents;
import org.droidtv.tunerservice.util.PowerLogger;
import org.droidtv.tv.provider.IRemindersContract;
import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerShutdownLocks;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.logger.ILogger;
import org.droidtv.tv.logger.ILogger.PowerStateTransition;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.database.ContentObserver;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;


public class Reminder {

	private static final String TAG = "Reminder";
	private static Reminder _instance = null;
	private static Context mClientContext = null;
	private long mAlarmRegisteredTime;
	private RemContentObserver remObserver = null;
	private int  MILLI_SECS = 1000;
	private PowerStates mCurrentPowerState = PowerStates.POWER_STATE_UNKNOWN;
	private ArrayList <PendingReminder> pendingReminder = null;
	private ITvPowerManager.ShutdownLock  lock;
	private PendingIntent pendingIntent = null;
	private Handler mTimerHandler=null;
	private static IPowerEvents mPowerEventListener = null;
	private static PowerLogger mPowerLogger;
	
    class RemContentObserver extends ContentObserver {
    	
    	private Handler handler = new Handler();
    	
    	public RemContentObserver(Handler handler) {
    		super(handler);
    		Log.d(TAG, "RemContentObserver construct");
    	}

        @Override
        public boolean deliverSelfNotifications() {
            return false;
        }
    	
    	@Override
    	public void onChange(boolean selfChange, Uri uri) {
       		if(!selfChange) {
    			Log.d(TAG, "onChange Called : URI" + uri);
    			Runnable nodeChangeRunnable = new Runnable() {
    				@Override
    				public void run() {
    					NodeChanged();
    				}
    			};
    			handler.post(nodeChangeRunnable);
    		}
    	}
    }
 
	public synchronized static Reminder getInstance(Context clientContext) {
		mClientContext = clientContext;
		if (_instance == null) {
			_instance = new Reminder();
			mPowerEventListener =_instance.new PowerEventsReceiver();
			registerPowerLogger();
		}
		return _instance;
	}
	
	public void registerReminderEvent() {
		mAlarmRegisteredTime = Long.MAX_VALUE;
		remObserver = new RemContentObserver(null);
	    lock = ITvPowerManager.Instance.getInterface().CreateShutdownLock(PowerShutdownLocks.DONT_SHUTDOWN_LOCK, TAG);
	    getLock();
		powerOnSyncReminder();
		releaseLock();
		mClientContext.getContentResolver().registerContentObserver(IRemindersContract.CONTENT_URI_RemindsList, true, remObserver);
	}

	private static void registerPowerLogger(){
		mPowerLogger = PowerLogger.getInstance();

		mPowerLogger.bindToLoggingService(mClientContext);
	}
	
	private void powerOnSyncReminder() {
		Log.d(TAG, "powerOnSyncReminder");
		removeStaleReminder();
		NodeChanged();
	}
	
	private void getLock() {
		if(!lock.isHeld())
		{
			Log.d(TAG, "acquiring lock from Reminder");
			lock.acquire();
		}
	}
	
	private void releaseLock() {
		if(lock.isHeld())
		{
			Log.d(TAG, "Releasing lock from Reminder");
			lock.release();
		}
	}
	
	private void removeStaleReminder() {
		long timenow = System.currentTimeMillis()/1000;
		Log.d(TAG, "removeStaleReminder reminder");
		String where = IRemindersContract.C_REM_ENDTIME + " <= ?";
		String whereArgs[] = {String.valueOf(timenow)};
		int del_result = mClientContext.getContentResolver().delete(
				IRemindersContract.CONTENT_URI_RemindsList, where, whereArgs);
		if(del_result >0)
		{
			Log.d(TAG, "deleted "+del_result+" reminders. timenow is "+String.valueOf(timenow));
		} else {
			Log.d(TAG, "no stale reminders to be deleted");
		}
	}

    public void NodeChanged() {
    	Log.d(TAG, "Node Changed ");
    	long timenow = System.currentTimeMillis()/1000;

		String[] REMIND_PROJ = new String[] {
				IRemindersContract.C_REM_STARTTIME,
				IRemindersContract.C_REM_MEDIUM,
				IRemindersContract.C_REM_CHANNELID,
				IRemindersContract.C_REM_EVENTID,
				IRemindersContract.C_REM_EVENTNAME,
				IRemindersContract.C_REM_ENDTIME};
		String REMIND_ORDERBY = IRemindersContract.C_REM_STARTTIME + " ASC LIMIT 1";
		
		Cursor rem_cursor = mClientContext.getContentResolver().query(
				IRemindersContract.CONTENT_URI_RemindsList, REMIND_PROJ,
				null, null, REMIND_ORDERBY);
                //boolean mNonInterruptableMode = PlayTvApplication.getInstance().getNonInterruptableStatus();
		if ((rem_cursor != null) && (rem_cursor.getCount() > 0) && (rem_cursor.moveToFirst()) && (mAlarmRegisteredTime >= rem_cursor.getInt(0))) 
		{
			if(rem_cursor.getInt(5)<timenow){
				deleteReminder(rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_CHANNELID)),rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_EVENTID)));
			}
			else if(rem_cursor.getInt(0)<timenow) {
				Log.d(TAG, "got event to be fired now");
               // if(!mNonInterruptableMode){
           	    	mCurrentPowerState = ITvPowerManager.Instance.getInterface().GetPowerState();
					Intent i = new Intent("org.droidtv.playtv.REMINDER");
					i.putExtra("medium", rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_MEDIUM)));
					i.putExtra("cid", rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_CHANNELID)));
					i.putExtra("eventId", rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_EVENTID)));
					i.putExtra("eventName", rem_cursor.getString(rem_cursor.getColumnIndex(IRemindersContract.C_REM_EVENTNAME)));
					i.putExtra("startTime", rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_STARTTIME)));
					i.putExtra("endTime", rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_ENDTIME)));
					Log.d(TAG,"Reminder Cid="+rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_CHANNELID)));
	                Log.d(TAG,"startTime" + rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_STARTTIME)));
	                Log.d(TAG,"endTime"+rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_ENDTIME)));
				    i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
	           	    Log.d(TAG, "mCurrentPowerState: "+mCurrentPowerState);
            		if(mCurrentPowerState != PowerStates.POWER_STATE_FULL_SYSTEM_START) {
            			Log.d(TAG, "Reminder fired in standby/semi-standby state. setting power state to FULL_SYSTEM_START");
            			ITvPowerManager.Instance.getInterface().SetState(PowerStates.POWER_STATE_FULL_SYSTEM_START);
            			if(pendingReminder == null)
            				pendingReminder = new ArrayList<PendingReminder>();
            			pendingReminder.add(new PendingReminder(true, i));
            			rem_cursor.close();
            			return;
            		}
				    mClientContext.startActivity(i);
//                }
//                else
//                {
//                  Log.d(TAG,"System is in NonInterruptableState");
//                }
//                
				    deleteReminder(rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_CHANNELID)),rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_EVENTID)));
			}
			else if(mAlarmRegisteredTime != rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_STARTTIME))) {
				mAlarmRegisteredTime = rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_STARTTIME));
				AddAlarm(mAlarmRegisteredTime);
			} else {
				Log.d(TAG, "reminder scheduled at same time");
			}
		} else
		{
			if(pendingIntent != null){
				AlarmManager alarmMgr = (AlarmManager)mClientContext.getSystemService(Context.ALARM_SERVICE);
				alarmMgr.cancel(pendingIntent);
				mAlarmRegisteredTime = Long.MAX_VALUE;
				Log.d(TAG, "clearing alarm as no reminders in the list.");
			}
		}
		if(rem_cursor != null)
			rem_cursor.close();
    }
    
	private void deleteReminder()
	{
		String where = IRemindersContract.C_REM_STARTTIME+ " = ? " ;
		String where_args[] = {String.valueOf(mAlarmRegisteredTime)}; 
		int result = mClientContext.getContentResolver().delete(IRemindersContract.CONTENT_URI_RemindsList, where, where_args);
		Log.d(TAG, "The Result Received for the Delete Operation:" + result);
	}
	
	private void deleteReminder(int cid, int eventId)
	{
		//delete reminder from DB as already expired.
		String mScheduleselectionclause=IRemindersContract.C_REM_CHANNELID +  " = '"+ (String.valueOf(cid)) + "' AND "+IRemindersContract.C_REM_EVENTID+" = '"+ (String.valueOf(eventId)) + "'";
		int result = (mClientContext.getContentResolver().delete(IRemindersContract.CONTENT_URI_RemindsList, mScheduleselectionclause+" AND " + IRemindersContract.C_REM_EVENTID+ "="+String.valueOf(eventId), null));
		Log.d(TAG, "The Result Received for the Delete Operation:" + result);
	}
	
	void AddAlarm(long abstime)
	{
		Log.d(TAG," AddAlarm at : "+abstime);
        AlarmManager alarmMgr = (AlarmManager)mClientContext.getSystemService(Context.ALARM_SERVICE);
        Intent intent = new Intent(mClientContext, AlarmReceiver.class);

    	Uri RemUri = Uri.parse("rem://");
        intent.setData(RemUri);
        
        pendingIntent = PendingIntent.getBroadcast(mClientContext, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
        alarmMgr.setExact(AlarmManager.RTC_WAKEUP, (abstime * MILLI_SECS), pendingIntent);        
        Log.d(TAG,"scheduleNextReminder has Done Wait for the OnReceive to COME");
	}
	
	public void onAlarm() {

		Log.d(TAG, "on Alarm Has been Called *** Alarm has fired mAlarmRegisteredTime"+ mAlarmRegisteredTime);
	    mCurrentPowerState = ITvPowerManager.Instance.getInterface().GetPowerState();
	    Log.d(TAG, "mCurrentPowerState onAlarm: "+mCurrentPowerState);
		long timenow = System.currentTimeMillis()/1000;
		//query for reminders at the same time.
		String[] REMIND_PROJ = new String[] {
				IRemindersContract.C_REM_STARTTIME,
				IRemindersContract.C_REM_MEDIUM,
				IRemindersContract.C_REM_CHANNELID,
				IRemindersContract.C_REM_EVENTID,
				IRemindersContract.C_REM_EVENTNAME,
				IRemindersContract.C_REM_ENDTIME};
		String REMIND_SELECT = IRemindersContract.C_REM_STARTTIME + " = ?";
		String[] REMIND_SELECT_ARGS = { Long.toString(mAlarmRegisteredTime) };
		
		Cursor rem_cursor = mClientContext.getContentResolver().query(
				IRemindersContract.CONTENT_URI_RemindsList, REMIND_PROJ,
				REMIND_SELECT, REMIND_SELECT_ARGS, null);
                //boolean mNonInterruptableMode = PlayTvApplication.getInstance().getNonInterruptableStatus();

		if ((rem_cursor != null) && (rem_cursor.getCount() > 0) && (rem_cursor.moveToFirst())) 
		{
			Log.d(TAG,"cursor returned "+rem_cursor.getCount() +" events at this time");
			getLock();
			if(mCurrentPowerState != PowerStates.POWER_STATE_FULL_SYSTEM_START) {
				mPowerLogger.logPowerState(mCurrentPowerState,ILogger.PowerStateTransition.Reason.REMINDER);
		    	Log.d(TAG, "Reminder Alarm fired in standby/semi-standby state. setting power state to FULL_SYSTEM_START");
		    	ITvPowerManager.Instance.getInterface().SetState(PowerStates.POWER_STATE_FULL_SYSTEM_START);
			}
			while(rem_cursor.isAfterLast() == false){
               // if(!mNonInterruptableMode) {
                	if(rem_cursor.getLong(5) < timenow)
                	{
                		Log.d(TAG, "reminder time already elapsed continue..");
                		rem_cursor.moveToNext();
                		continue;
                	}
					Intent i = new Intent("org.droidtv.playtv.REMINDER");
					i.putExtra("medium", rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_MEDIUM)));
					i.putExtra("cid", rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_CHANNELID)));
					i.putExtra("eventId", rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_EVENTID)));
					i.putExtra("eventName", rem_cursor.getString(rem_cursor.getColumnIndex(IRemindersContract.C_REM_EVENTNAME)));
					i.putExtra("startTime", rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_STARTTIME)));
					i.putExtra("endTime", rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_ENDTIME)));
					Log.d(TAG,"Reminder Cid="+rem_cursor.getInt(rem_cursor.getColumnIndex(IRemindersContract.C_REM_CHANNELID)));
	                Log.d(TAG,"startTime" + rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_STARTTIME)));
	                Log.d(TAG,"endTime"+rem_cursor.getLong(rem_cursor.getColumnIndex(IRemindersContract.C_REM_ENDTIME)));
		            i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		    		if(mCurrentPowerState != PowerStates.POWER_STATE_FULL_SYSTEM_START) {
		    			Log.d(TAG, "Adding intents to the pendingreminder list");
            			if(pendingReminder == null)
            				pendingReminder = new ArrayList<PendingReminder>();
		    			pendingReminder.add(new PendingReminder(true, i));
		    		} else {
			            mClientContext.startActivity(i);
				        Log.d(TAG,"intent sent to start ReminderActivity");
					}
//                }
//                else
//                {
//                	Log.d(TAG,"system is in NonInterruptableState");
//                }
				rem_cursor.moveToNext();
			}
	        deleteReminder();
	        releaseLock();
		}
		else {
			Log.d(TAG,"cursor returned null");
		}

		mAlarmRegisteredTime = Long.MAX_VALUE;
		if(rem_cursor != null)
			rem_cursor.close();
		//NodeChanged will be called on deletion of the reminder and setting next alarm will be taken care.
	}

	private void startActivityTimer() {
		// TODO Auto-generated method stub
		mTimerHandler=new Handler();
		if(mTimerHandler!=null && pendingIntent !=null){
			mTimerHandler.postDelayed(new Runnable() {
				
				@Override
				public void run() {
					// TODO Auto-generated method stub
					showReminderAfterWakeup();
				}
			},10000);
		}
	}

	public void showReminderAfterWakeup() 
	{
		if(pendingReminder != null){
			Log.d(TAG,"going to start reminderActivity");
			for(int i=0; i<pendingReminder.size(); i++) {
				mClientContext.startActivity(pendingReminder.get(i).getPendingReminderIntent());
				deleteReminder(pendingReminder.get(i).getPendingReminderIntent().getIntExtra("cid", 0), 
						pendingReminder.get(i).getPendingReminderIntent().getIntExtra("eventId", 0));
			}
			pendingReminder.clear();
			pendingReminder = null;
			mTimerHandler=null;
		} else {
			Log.d(TAG,"no pending reminders for wake up");
		}
	}
	
	class PendingReminder {
		private boolean isReminderPending;
		private Intent intent;
		public PendingReminder(boolean status, Intent remIntent) {
			Log.d(TAG, "constructor called for PendingReminder");
			isReminderPending = status;
			intent = remIntent;
		}
		public Intent getPendingReminderIntent() {
			return intent;
		}
		public boolean getPendingReminderStatus() {
			return isReminderPending;
		}
	}
	
	 private class PowerEventsReceiver implements IPowerEvents {

	 		@Override
	 		public void onPowerChangeStart(PowerStates from, PowerStates to,Bundle extras) {
	 			Log.d(TAG,"onPowerChangeStart : from - "+from+"to - "+to);
	 		}

	 		@Override
	 		public void onPowerChangeEnd(PowerStates from, PowerStates to,Bundle extras) {
				Log.d(TAG,"onPowerChangeEnd : from - "+from+"to - "+to);
				if(from==PowerStates.POWER_STATE_DDR_STANDBY || from==PowerStates.POWER_STATE_SEMI_STANDBY || from == PowerStates.POWER_STATE_STANDBY){
					if(to==PowerStates.POWER_STATE_FULL_SYSTEM_START && pendingIntent!=null){
					startActivityTimer();
					}
				}
	 		}
	 	}

	     public static IPowerEvents getPowerEventsListener() {
	 		return mPowerEventListener;
	 	}
}
