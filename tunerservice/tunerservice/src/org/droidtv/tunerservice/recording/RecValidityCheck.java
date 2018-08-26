package org.droidtv.tunerservice.recording;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.tv.media.ITvMediaRecordControl;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.provider.IRecordingsContract.RecordingType;
import org.droidtv.tunerservice.util.PlayTvHDDUtils;
import org.droidtv.tunerservice.bcstreceiver.AlarmReceiver;
import org.droidtv.tunerservice.interfaces.IHDDListener;

import org.droidtv.tv.media.ITvMediaRecordControl.IonTvRecordControlCallback;

import android.content.ContentValues;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.database.Cursor;
import android.util.Log;
import android.os.Handler;
import android.os.Looper;

import android.app.PendingIntent;
import android.content.Intent;
import android.net.Uri;
import android.app.AlarmManager;




public class RecValidityCheck {

	private final static String Tag = "RecValidityCheck";
	private Context mClientContext = null;
	private int  MILLI_SECS = 1000;
	//private RecValiditytimer recValidityTimer, dailyValiditytimer;
	public Timer validityTimer;
	private Timer dailyTimer;
	private SharedPreferences mRecValidityCheckPrefs = null;
	private Editor editor = null;
	private ITvMediaRecordControl recordinstance;
	private final static int TWENTY_FOUR_HOURS = 1000*60*60*24;
	private PvrRecordListenerClass PvrRecordListener = null;
	public static int count = 0;
	public List<Integer> recordIdArray = new ArrayList<Integer>();
	public static int validityCheckRecId = 0;
	private LooperThread looperThread;
	private Handler handler;
	private HddListener mHddListener = null;
	
	private class LooperThread extends Thread {
		public Handler mHandler;
		boolean handlerCreated = false;
		public void run() {
	//		Log.d(Tag,"Looper thread creation");
			synchronized (this)
			{
				Looper.prepare();
				mHandler = new Handler() ;
				handlerCreated = true;
	//			Log.d(Tag,"RecValidity: notifying... after handler creation");
				notify();
			}
			Looper.loop();
		};
	
		public boolean getLooperThreadHandlerStatus()
		{
			return handlerCreated;
		}
    };

	public RecValidityCheck(Context clientContext) {
	//	Log.d(Tag, "RecValidityCheckService constructor");
		this.mClientContext = clientContext;
		validityTimer = new Timer();
		dailyTimer = new Timer();
		handler = new Handler();
		//recValidityTimer = new RecValiditytimer(true);
		//dailyValiditytimer = new RecValiditytimer(false);
		PvrRecordListener = new PvrRecordListenerClass();
		mHddListener = new HddListener();
		PlayTvHDDUtils.getInstance(clientContext).addHDDListener(mHddListener, Tag);
	}

	public void startLooperthread() {
		// TODO Auto-generated method stub
		looperThread = new LooperThread(); //Every slot will have one looper thread
		looperThread.start();
		synchronized(looperThread) {
			while(!looperThread.getLooperThreadHandlerStatus()) {
				try {
					Log.d(Tag,"Runnable waiting..");
					looperThread.wait();
					Log.d(Tag,"Runnable wait finish");
				} catch (InterruptedException e) {
					Log.d(Tag,"InterruptedException");
				}
			}
		}
		if (PlayTvHDDUtils.getInstance(mClientContext).getMountPath() != null) { 
			UpdateRecToExpired();
			ArmTimerForNextRecord();
		}
		RecValidityCheckViaPrefs();
	}

	class RecValidityAlarmRunnable implements Runnable {
		private int ValidityCheckRecord;

		public RecValidityAlarmRunnable(int rec_id) {
			Log.d(Tag," RecValidityAlarmRunnable "+rec_id);
			ValidityCheckRecord = rec_id;
		}

		@Override
		public void run() {
			Log.d(Tag," run: Prepar for recvalidity after alarm fired ");
				onTimerExpired();
			}
	};
	
	private void UpdateRecToExpired() {
		String mountPath = PlayTvHDDUtils.getInstance(mClientContext).getMountPath();
		if (mountPath != null) {
			long timenow = System.currentTimeMillis()/MILLI_SECS;
			Log.d(Tag, "UpdateRecToExpired timenow " +timenow);
			String where = "(" + IRecordingsContract.C_RECORDING_TYPE + " = ? OR "
					+ IRecordingsContract.C_RECORDING_TYPE + " = ? OR "
					+ IRecordingsContract.C_RECORDING_TYPE + " = ? ) AND ("
					//+ IRecordingsContract.C_ISIPEPG_RECORDING + " = ? ) AND ("
					+ IRecordingsContract.C_RETENTION_INFO + " <= ?) AND ("
					+ IRecordingsContract.C_HAS_LICENSE_FILE + " = ? ) AND ("
					+ IRecordingsContract.C_RETENTION_INFO + " != ? )";
			String[] whereArgs = { ""+ RecordingType.RECORDING_NEW.ordinal(),
					""+RecordingType.RECORDING_VIEWED.ordinal(),
					""+RecordingType.RECORDING_PARTIALLY_VIEWED.ordinal(),
					//String.valueOf(isCurrentEpgIPEpg()),
					//Long.toString(timenow),
					""+timenow,
					String.valueOf(0),
					String.valueOf(-1)};
			String[] proj = { ""+ IRecordingsContract.C_RECORDING_ID};

			TvMediaPlayer mMediaPlayer = null;
			try {
				mMediaPlayer = TvMediaPlayer.getTvTunerMediaPlayer();
				recordinstance = mMediaPlayer.getTvMediaPlayerContext().getTvMediaRecordControl();
			} catch(Exception e) {
				Log.e(Tag, "exception in deleteRecordingsFromHDD : "+e.toString());
			}
			
			// get the list of recording to be marked as expired
			Cursor c = mClientContext.getContentResolver().query(
				IRecordingsContract.CONTENT_URI_Recordings, proj,
				where, whereArgs, null);
			if(c != null) {
				if ((c.getCount() > 0) && (c.moveToFirst())) {
					do {
						try {
							if (recordinstance != null) {
								recordinstance.deleteRecording(c.getInt(0), mountPath);
								
								// recheck mount path, this is done to avoid scenario where mountpath 
								// has become null between delete and marking as expired.
								mountPath = PlayTvHDDUtils.getInstance(mClientContext).getMountPath();
								if (mountPath != null) {
									String sel = "(" + IRecordingsContract.C_RECORDING_ID + " = ? )";
									String[] selArgs = { ""+ c.getInt(0)};
									ContentValues updateValues = new ContentValues();
									updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_EXPIRED.ordinal());
									updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
									int updateResult = mClientContext.getContentResolver().update(
											IRecordingsContract.CONTENT_URI_Recordings, updateValues, 
											sel, selArgs);
									if (updateResult > 0) {
										Log.d(Tag, "UpdateRecToExpired: Rec "+c.getInt(0)+" marked as expired");
									} else {
										Log.d(Tag, "UpdateRecToExpired: Marking Rec "+c.getInt(0)+" to expired, FAILED !!!");
									}											
								} else {
									break;
								}
							}
						} catch (Exception e) {
							Log.d(Tag, "UpdateRecToExpired: Exception"+e.toString());
						}
					} while (c.moveToNext());
				}
				c.close();
			}
		}
	}
		
	private void ArmTimerForNextRecord() {
		Log.d(Tag, "ArmTimerForNextRecord");
		long timenow = System.currentTimeMillis()/MILLI_SECS;
		String[] proj = new String[] {IRecordingsContract.C_RECORDING_ID, IRecordingsContract.C_RETENTION_INFO};
		String sel = "(" + IRecordingsContract.C_RECORDING_TYPE + " = ? OR "
				+ IRecordingsContract.C_RECORDING_TYPE + " = ? OR "
				+ IRecordingsContract.C_RECORDING_TYPE + " = ? ) AND ("
				//+ IRecordingsContract.C_ISIPEPG_RECORDING + " = ? ) AND ("
				+ IRecordingsContract.C_HAS_LICENSE_FILE + " = ? ) AND ("
				+ IRecordingsContract.C_RETENTION_INFO + " != ? )";
		String[] sel_args = { ""+RecordingType.RECORDING_NEW.ordinal(),
				""+RecordingType.RECORDING_VIEWED.ordinal(),
				""+RecordingType.RECORDING_PARTIALLY_VIEWED.ordinal(),
				//String.valueOf(isCurrentEpgIPEpg()),
				String.valueOf(0),
				String.valueOf(-1)};
		String orderby = IRecordingsContract.C_RETENTION_INFO + " ASC LIMIT 1";
		
		Cursor c = mClientContext.getContentResolver().query(
				IRecordingsContract.CONTENT_URI_Recordings, proj,
				sel, sel_args, orderby);
		if((c != null) && (c.getCount() > 0) && (c.moveToFirst())) {
			long retention = c.getInt(1);
			int recId = c.getInt(0);
			long sendDelay = (retention-timenow)*MILLI_SECS;
			Log.d(Tag, "setting timer for time  retention: "+ retention +" sendDelay: "+ sendDelay);
			AddAlarmForValidityCheck(recId, retention);
		}
		else {
			Log.d(Tag, "no records found to be set for expiry");
		}
		if(c != null)
			c.close();
	}

	public void AddAlarmForValidityCheck(int rec_id, long abstime) {
		Log.d(Tag," AddAlarm for RecValidity : abstime is "+abstime+ " rec_id "+ rec_id);
		AlarmManager alarmMgr = (AlarmManager)mClientContext.getSystemService(Context.ALARM_SERVICE);
		Intent intent = new Intent(mClientContext, AlarmReceiver.class);

		Uri RecUri = Uri.parse("recvalidity://");
		intent.setData(RecUri);

		intent.putExtra("recordId", rec_id);
		intent.putExtra("alarmTime", abstime);

		PendingIntent pendingIntent = PendingIntent.getBroadcast(mClientContext, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
		alarmMgr.setExact(AlarmManager.RTC, (abstime * MILLI_SECS), pendingIntent);       
	}

	public void onAlarm(int rec_id) {
		Log.d(Tag," Alarm Fired for rec_id "+rec_id);
		handler.post(new RecValidityAlarmRunnable(rec_id));
	}

	public void onTimerExpired() {
		Log.d(Tag, "onTimerExpired");
		UpdateRecToExpired();
		ArmTimerForNextRecord();
	}
	
	public String getCurrentdate() {
        try{
        	String format = "yyyy/MM/dd";
        	DateFormat dateFormat = new SimpleDateFormat(format);
        	Date date = new Date();
        	String sDate = dateFormat.format(date);
        	return sDate;
        }catch (Exception e) {
        	Log.e(Tag, e.toString());
        }
        return "";
    }

	public void RecValidityCheckViaPrefs() {
//		Log.d(Tag, "RecValidityCheckViaPrefs");
		mRecValidityCheckPrefs = mClientContext.getApplicationContext().getSharedPreferences("RecValidityCheckPrefs", Context.MODE_PRIVATE);
		String mRecordValidityCheckTime = mRecValidityCheckPrefs.getString("RecordValidityCheckDate", "");
//		Log.d(Tag, "RecValidityCheckViaPrefs mRecordValidityCheckTime: "+mRecordValidityCheckTime + " getCurrentdate "+ getCurrentdate());
		//immediately start
		DailyValidityCheck();
	}
	
	private void updateRecValidityPrefs() {
		String currDateString = getCurrentdate();
		Log.d(Tag, "updateRecValidityPrefs - Resetting the Shared Preference currDateString :" +currDateString);
		editor  = mRecValidityCheckPrefs.edit();
		editor.putString("RecordValidityCheckDate", currDateString);
		editor.commit();
	}
	
	private long getMidnightTime(){
    	Calendar mCalendar = Calendar.getInstance();
    	Log.d(Tag, "timenow" +mCalendar.getTimeInMillis());
		String mydate = java.text.DateFormat.getDateTimeInstance().format(mCalendar.getTime());
		Log.i(Tag,"current time is " + mydate);
    	mCalendar.add(Calendar.DATE, 1);
    	mCalendar.set(Calendar.HOUR, 0);
    	mCalendar.set(Calendar.MINUTE, 0);
    	mCalendar.set(Calendar.SECOND, 0);
    	mCalendar.set(Calendar.MILLISECOND, 0);
    	mCalendar.set(Calendar.AM_PM, Calendar.AM);

    	String nightdate = java.text.DateFormat.getDateTimeInstance().format(mCalendar.getTime());
		Log.i(Tag,"midnighttime in millis : "+ +mCalendar.getTimeInMillis()+ " date time is " + nightdate);
    	return mCalendar.getTimeInMillis();
    }
    /*
    @SuppressWarnings("deprecation")
	private Date getMidnightTime(){
        Date midnight = new java.util.Date(); 
        midnight.setHours(ZERO); 
        midnight.setMinutes(ZERO); 
        Log.d(Tag, "getMidnightTime" +midnight);
        return midnight;
    }
    */
  
    private void setMidnightTimer() {
    	Calendar mCal = Calendar.getInstance();
    	long timenow = mCal.getTimeInMillis();//from calender to use local time so that the timer fires at midnight 12
		String mydate = java.text.DateFormat.getDateTimeInstance().format(timenow);
		Log.i(Tag,"setMidnightTimer current time is " + mydate);
    	long sendDelay = (getMidnightTime()-timenow);
    	Log.d(Tag, "setMidnightTimer for time " +getMidnightTime() +" sendDelay: "+sendDelay);
    	dailyTimer.schedule(new TimerTask() {          
	        @Override
	        public void run() {
	        	Log.d(Tag, "timer fired DailyValidityCheck");
	        	DailyValidityCheck();
	        }

	    }, /*sendDelay*/60000, TWENTY_FOUR_HOURS);
    }
    
	public void DailyValidityCheck() {
//		Log.d(Tag, "DailyValidityCheck");
		Log.d(Tag, "mount path is "+PlayTvHDDUtils.getInstance(mClientContext).getMountPath());
		if (PlayTvHDDUtils.getInstance(mClientContext).getMountPath() != null)
		{
			Log.d(Tag, "DailyValidityCheck mountpath is not null proceed...");
			String[] proj = new String[] {IRecordingsContract.C_RECORDING_ID, IRecordingsContract.C_RETENTION_INFO};
			String sel = "(" + IRecordingsContract.C_RECORDING_TYPE + " = ? OR "
					+ IRecordingsContract.C_RECORDING_TYPE + " = ? OR "
					+ IRecordingsContract.C_RECORDING_TYPE + " = ? ) AND ("
					//+ IRecordingsContract.C_ISIPEPG_RECORDING + " = ? ) AND ("
					+ IRecordingsContract.C_HAS_LICENSE_FILE + " = ? )";
			String[] sel_args = { ""+ RecordingType.RECORDING_NEW.ordinal(),
					""+ RecordingType.RECORDING_VIEWED.ordinal(),
					""+ RecordingType.RECORDING_PARTIALLY_VIEWED.ordinal(),
					//String.valueOf(isCurrentEpgIPEpg()),
					String.valueOf(1)};
			String orderby = IRecordingsContract.C_RETENTION_INFO + " ASC";
			
			Cursor c = mClientContext.getContentResolver().query(
					IRecordingsContract.CONTENT_URI_Recordings, proj,
					sel, sel_args, orderby);
			if((c != null) && (c.getCount() > 0) && (c.moveToFirst())) {
				while(!c.isAfterLast()){
					Log.d(Tag, "adding record ID to arraylist recordId"+ c.getInt(0));
					recordIdArray.add(c.getInt(0));
					c.moveToNext();
				}
				
				TvMediaPlayer mMediaPlayer = null;
				try {
					mMediaPlayer = TvMediaPlayer.getTvTunerMediaPlayer();
					recordinstance = mMediaPlayer.getTvMediaPlayerContext().getTvMediaRecordControl();
				}
				catch(Exception e){                      
					Log.e(Tag, "exception in RecordingValidityCheck"+ e.toString());
				}
				
				if (recordinstance != null) {
					recordinstance.registerListenerCallback(PvrRecordListener);
				}
				
				triggerCheckForNextRecord();
			}
			else{
				Log.d(Tag, "DailyValidityCheck.. no record found");
				updateRecValidityPrefs();
			}
			if(c!=null)
				c.close();
		}
		else
		{
			Log.d(Tag, "mountpath is null");
			return;
		}
	}
	
	public void triggerCheckForNextRecord() {
		Log.d(Tag,"triggerCheckForNextRecord");
		if((recordinstance != null) && (count < recordIdArray.size()))
		{
			Log.d(Tag, "Count is "+count);
			setValidityCheckRecId(recordIdArray.get(count));
			Log.d(Tag,"triggerCheckForNextRecord MW CALL recordingValidityCheck recId - "+ validityCheckRecId);
			/* TODO: This is commented out since there is currently no test case available for testing this scenario
				Changes will be optimised and added at a later stage */
			//recordinstance.recordingValidityCheck(validityCheckRecId, PlayTvHDDUtils.getInstance(mClientContext).getMountPath());
			// **** To be removed, once validity check for license is enabled ***
			new PvrRecordListenerClass().onRecordValidityStatus(0);
			setCount(count+1);
			Log.d(Tag, "Incremented Count is "+count);
		}
		if(count > recordIdArray.size()) {
			Log.d(Tag,"updateRecValidityPrefs");
			updateRecValidityPrefs();
			setCount(0);
		}
	}
	
	public static void setValidityCheckRecId(int validityCheckrecid ) {
        RecValidityCheck.validityCheckRecId = validityCheckrecid ;
   }
	
	public static void setCount(int lcount) {
        RecValidityCheck.count=lcount ;
   }


	private Runnable validityCheckRunnable = new Runnable() {
		@Override
		public void run() {
			Log.d(Tag," run: validity check ");
			triggerCheckForNextRecord();
		}		
	};
	
/*	public class validityCheckRunnable implements Runnable {
		
		@Override
		public void run() {
			Log.d(Tag," run: validity check ");
			triggerCheckForNextRecord();
		}
	};*/
	
	 public class PvrRecordListenerClass extends IonTvRecordControlCallback {
			
			@Override
			public void onRecordValidityStatus(int status) {
				Log.d(Tag, "onRecordValidityStatus status - " + status);
				if(status == 1)
				{
					//make recording as expired
					String where = IRecordingsContract.C_RECORDING_ID + " = ? ";
					String[] whereArgs = { Integer.toString(validityCheckRecId)};
					ContentValues updateValues = new ContentValues();
					Log.d(Tag, "Update recType to expired for RecId - " + validityCheckRecId);
					updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.RECORDING_EXPIRED.ordinal());
					updateValues.put(IRecordingsContract.C_CHANGE_ID, Tag);
					int updateResult = mClientContext.getContentResolver().update(
							IRecordingsContract.CONTENT_URI_Recordings, updateValues, 
							where, whereArgs);
					if(0 >= updateResult)
					{
						Log.e(Tag, "Update Failed: Failed to update RecordingType to expired");
					}
				}
				
				looperThread.mHandler.post(validityCheckRunnable);
			}
	};

	private class HddListener implements IHDDListener {

		@Override
		public void onHDDConnected() {
			Log.d(Tag,"onHDDConnected");
			Runnable runValidityCheck = new Runnable() {
				@Override
				public void run() {
					Log.d(Tag, "Triggering onTimerExpired since onHDDConnected");
					onTimerExpired();
				}
			};
			handler.post(runValidityCheck);
		}

		
		@Override
		public void onHDDRemoved() {
			Log.d(Tag,"onHDDRemoved");
			
		}
	}

	/*
	private class RecValiditytimer extends LooperTimer {
		private Boolean isOnce;
		public RecValiditytimer(Boolean isOnce) {
			this.isOnce = isOnce ;
		}

		@Override
		public void timerHandler() {
			Log.d(Tag,"timerHandler");
			if(isOnce)
				onTimerExpired();
			else
				DailyValidityCheck();
		}
		
	}*/
}