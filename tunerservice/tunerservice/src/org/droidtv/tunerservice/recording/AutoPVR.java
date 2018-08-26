package org.droidtv.tunerservice.recording;

import java.util.Calendar;

//import org.droidtv.playtv.PlayTvApplication; TODO:TIF:commented... to be removed
import org.droidtv.tunerservice.util.PlayTvHDDUtils;
import org.droidtv.tunerservice.bcstreceiver.AlarmReceiver;
import org.droidtv.tunerservice.interfaces.IHDDListener;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;
import org.droidtv.tunerservice.recording.RecordData;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tv.media.BcstConstants;
import org.droidtv.tv.media.ITvMediaRecordControl;
import org.droidtv.tv.media.ITvMediaRecordControl.IonTvRecordControlCallback;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.provider.IRecordingsContract.RecordingError;
import org.droidtv.tv.provider.IRecordingsContract.RecordingType;
import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvPowerManager.ShutdownLock;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;
import java.util.Map;

public class AutoPVR implements IHDDListener{

	public static final String TAG = "AutoPVR";
	private PlayTVFacMediaPlayer mPlaytvmplayer = null;
	private Context mClientContext = null;
	private RecordData mAutoPVRData = null;
	private static ITvMediaRecordControl recordinstance = null;
	private static Object syncLock = null;
	private static final int MILLI_SECS = 1000;
	private long mAlarmRegisteredTime = 0;
	private static AutoPVR _instance = null;
	private static AutoPvrRecordListener mAutoPVRRecordListner;
	private static PlayTVStateMonitor mPlayStateMonitor = null;
	private Handler mRecodingTimeHandler = new Handler();
	private Runnable mRunnable = null;
	private static final int LOCK_CHECK_IN_MIN = 20 * 60;
	private ShutdownLock mPowerManagerImpl = null;

	private static IRecordingsContract.RecordingType[] rec_type = IRecordingsContract.RecordingType
			.values();
	public static enum AutoPVRStatus {
		IDLE, STARTED
	};

	static {
		syncLock = new Object();
	}


	private static int mCurrentRecordingStatus = AutoPVRStatus.IDLE.ordinal();

	private AutoPVR() {
		ITvPowerManager mTVPowerManager = ITvPowerManager.Instance.getInterface();
		mPowerManagerImpl = mTVPowerManager.CreateShutdownLock(
				ITvPowerManager.PowerShutdownLocks.DONT_SHUTDOWN_LOCK, TAG);
	}

	private void initialiseRecordingLifeTime() {

		mRunnable = new Runnable() {
			@Override
			public void run() {
				Log.d(TAG, "postDelayed has come out from the Recording");
				if (recordinstance != null) {
					recordinstance.stopRecording();
				}
			}
		};
	}

	public static AutoPVR getInstance() {

		synchronized (syncLock) {

			if (_instance == null) {
				_instance = new AutoPVR();
				mAutoPVRRecordListner = _instance.new AutoPvrRecordListener();
				mPlayStateMonitor = _instance.new PlayTVStateMonitor();
				_instance.initialiseRecordingLifeTime();
			}
			return _instance;
		}
	}

	public void doPowerOnSync(Context context)
	{
		mClientContext = context;
		if(mPowerManagerImpl.isHeld()==false)
			mPowerManagerImpl.acquire();
		PowerOnSyncOngoingRecord();
		cleanUpStale(true);
		findNextRecordForScheduling();
	}

	void PowerOnSyncOngoingRecord()
	{
		Log.d(TAG, "PowerOnSyncOngoingRecord");
		//query for ongoing recording
		String[] projection = {IRecordingsContract.C_RECORDING_ID};
		String selection = IRecordingsContract.C_RECORDING_TYPE + " == ?";
		String[] selectionArgs = {IRecordingsContract.RecordingType.AUTO_PVR_ONGOING.toString()};
		Cursor c = mClientContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, selection,
			selectionArgs, null);
		if( (c != null) && (c.getCount() > 0) && (c.moveToFirst() ) ) {
			String where = IRecordingsContract.C_RECORDING_ID + " = ? ";
			String[] whereArgs = { Integer.toString(c.getInt(0))};
			ContentValues updateValues = new ContentValues();
			updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.AUTO_PVR_FAILED.ordinal());
			updateValues.put(IRecordingsContract.C_RECORDING_ERROR, RecordingError.REC_ERROR_POWERINTERRUPTION.ordinal());
			updateValues.put(IRecordingsContract.C_CHANGE_ID, TAG);
			int updateResult = mClientContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, updateValues, where, whereArgs);
			if(0 >= updateResult)
			{
				Log.e(TAG, "failed to update recording in PowerOnSyncOngoingRecord");
			}
		}
		if(c != null)
			c.close();
	}

	void cleanUpStale(Boolean isPowerOnsync) {
		long timenow = System.currentTimeMillis()/1000;
		String[] projection = {IRecordingsContract.C_RECORDING_ID};
		String selection = IRecordingsContract.C_RECORDING_TYPE + " = ? AND " +
				IRecordingsContract.C_EFFECTIVE_START_TIME + "<= ?";
		String[] selectionArgs = {IRecordingsContract.RecordingType.AUTO_PVR_SCHEDULED.toString(),
				String.valueOf(timenow)};
		Cursor c = mClientContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, selection,
				selectionArgs, null);
		if( (c != null) && (c.getCount() > 0) && (c.moveToFirst() ) ) {
			String where = IRecordingsContract.C_RECORDING_ID + " = ? ";
			String[] whereArgs = { Integer.toString(c.getInt(0))};
			do {
				ContentValues updateValues = new ContentValues();
				updateValues.put(IRecordingsContract.C_RECORDING_TYPE, RecordingType.AUTO_PVR_FAILED.ordinal());
				updateValues.put(IRecordingsContract.C_IS_PARTIAL, false);
				if(isPowerOnsync)
					updateValues.put(IRecordingsContract.C_RECORDING_ERROR, RecordingError.REC_ERROR_NOPOWER.ordinal());
				else
					updateValues.put(IRecordingsContract.C_RECORDING_ERROR, RecordingError.REC_ERROR_CONFLICT.ordinal());
				updateValues.put(IRecordingsContract.C_CHANGE_ID, TAG);
				int update_result = mClientContext.getContentResolver().update(IRecordingsContract.CONTENT_URI_Recordings, updateValues, where, whereArgs);
				if(update_result<=0)
					Log.e(TAG, "update failed cleanUpStale");
			} while (c.moveToNext());
		}
		if(c != null)
			c.close();
		Log.d(TAG, "no more stale recording. Can Prepare for next recording");
	}
	public void registerAutoPVREvent(RecordData autoPVRData,
			Context clientContext) {

		Log.d(TAG, "registering Auto PVR");

		synchronized (syncLock) {
			this.mClientContext = clientContext;
			if (autoPVRData != null) {
				Log.d(TAG, "The Recording Details are");
				Log.d(TAG, "autoPVRData.channelId " + autoPVRData.channelId
						+ "autoPVRData.eet " + autoPVRData.eet
						+ "autoPVRData.est " + autoPVRData.est
						+ "autoPVRData.presetid  " + autoPVRData.presetid
						+ "autoPVRData.programNumber "
						+ autoPVRData.programNumber + "autoPVRData.recordId "
						+ autoPVRData.recordId + "autoPVRData.recordingType "
						+ autoPVRData.recordingType + "autoPVRData.version "
						+ autoPVRData.version);
			}

			if (autoPVRData != null
					&& (autoPVRData.recordingType == IRecordingsContract.RecordingType.AUTO_PVR_SCHEDULED)
					&& (mCurrentRecordingStatus == AutoPVRStatus.IDLE.ordinal())
					&& ((mAlarmRegisteredTime == 0 || mAlarmRegisteredTime > (autoPVRData.est)))) {

				mAlarmRegisteredTime = autoPVRData.est;
				mAutoPVRData = autoPVRData;
				scheduleRecording();
				holdLock(mAutoPVRData);

			} else {
				Log.d(TAG,
						"The request for AutoPVR will not be granted already service is running ");
				return;
			}
		}
	}

	class AutoPVRAlarm implements Runnable {

		RecordData recordData = null;

		public AutoPVRAlarm(RecordData record) {
			recordData = record;
		}

		public void run() {
			Log.d(TAG, " Alarm has Fired ***** Initialise the Recording ");
			initRecording(recordData);
		}
	};

	private void scheduleRecording() {

		AlarmManager alarmMgr = (AlarmManager) mClientContext
				.getSystemService(Context.ALARM_SERVICE);

		Intent intent = new Intent(mClientContext, AlarmReceiver.class);

		Uri RecUri = Uri.parse("auto_pvr://");
		intent.setData(RecUri);

		intent.putExtra("est", mAutoPVRData.est * MILLI_SECS);
		intent.putExtra("recordId", mAutoPVRData.recordId);

		PendingIntent pendingIntent = PendingIntent.getBroadcast(
				mClientContext, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);

		alarmMgr.setExact(AlarmManager.RTC_WAKEUP, (mAutoPVRData.est * MILLI_SECS),
				pendingIntent);

		Log.d(TAG,
				"scheduleNextRecording has Done Wait for the OnReceive to COME");
	}

	private void holdLock(RecordData record) {

		if (record != null
				&& ((record.est
						- (Calendar.getInstance().getTimeInMillis() / 1000) <= (LOCK_CHECK_IN_MIN)))) {

			if (mPowerManagerImpl.isHeld() == false) {
				mPowerManagerImpl.acquire();
				Log.d(TAG, "Acquiring lock from AUTOPVR");
			}

		} else {

			if (mPowerManagerImpl.isHeld() == true) {
				mPowerManagerImpl.release();
				Log.d(TAG, "Releasing lock from AUTOPVR");
			}
		}
	}

	private void startRecording(RecordData record) {

		PlayTvHDDUtils.getInstance(mClientContext).addHDDListener(this, TAG);
		Log.d(TAG, "startRecording  ****" + " recording id " + mAutoPVRData.recordId);

		recordinstance = mPlaytvmplayer.getMediaPlayerInstance()
				.getTvMediaPlayerContext().getTvMediaRecordControl();

		if ((recordinstance != null)&&(PlayTvHDDUtils.getInstance(mClientContext).getMountPath() != null)) {
			recordinstance.registerListenerCallback(mAutoPVRRecordListner);
			long deviceIdentifier = PlayTvHDDUtils.getInstance(mClientContext).getDeviceId();
			String deviceId = Long.toString(deviceIdentifier);
			recordinstance.startRecording(0, PlayTvHDDUtils.getInstance(mClientContext).getMountPath(), mAutoPVRData.recordId, 0, deviceId);
			Log.d(TAG, "started Recording ");

		} else {
			Log.d(TAG, "RecordInstance is NULL:  recording wont start");
		}
	}

	private void updateRecordingStatusInDB(int status) {

		String where = IRecordingsContract.C_RECORDING_ID + "=?";

		String[] whereArgs = { Integer.toString(mAutoPVRData.recordId) };
		ContentValues updateValues = new ContentValues();

		updateValues.put(IRecordingsContract.C_RECORDING_TYPE, status);

		updateValues.put(IRecordingsContract.C_PROGRAM_NUMBER,
				mAutoPVRData.programNumber);
		updateValues.put(IRecordingsContract.C_CHANGE_ID, TAG);

		int retval = mClientContext.getContentResolver().update(
				IRecordingsContract.CONTENT_URI_Recordings, updateValues, where,
				whereArgs);

		Log.d(TAG, "The retr value from the status update change is " + retval);

	}

	private void updateRecordingStatusInDB(int status, int errorType) {

		String where = IRecordingsContract.C_RECORDING_ID + "=?";

		String[] whereArgs = { Integer.toString(mAutoPVRData.recordId) };
		ContentValues updateValues = new ContentValues();

		updateValues.put(IRecordingsContract.C_RECORDING_TYPE, status);
		updateValues.put(IRecordingsContract.C_RECORDING_ERROR, errorType);
		updateValues.put(IRecordingsContract.C_PROGRAM_NUMBER,
				mAutoPVRData.programNumber);
		updateValues.put(IRecordingsContract.C_CHANGE_ID, TAG);

		int retval = mClientContext.getContentResolver().update(
				IRecordingsContract.CONTENT_URI_Recordings, updateValues, where,
				whereArgs);

		Log.d(TAG, "The retr value from the status update change is " + retval);

	}
	public RecordData getNextData() {

		String[] RECORD_PROJ = new String[] {
				IRecordingsContract.C_RECORDING_ID, // 0
				IRecordingsContract.C_RECORDING_TYPE, // 1
				IRecordingsContract.C_EFFECTIVE_START_TIME + " As EFF_START", // 2
				IRecordingsContract.C_EFFECTIVE_END_TIME, // 3
				IRecordingsContract.C_VERSION,  // 4
				IRecordingsContract.C_CHANNELID, // 5
				IRecordingsContract.C_EVENT_ID,  // 6
				IRecordingsContract.C_MARGIN_END, // 7
				IRecordingsContract.C_MARGIN_START, // 8
				IRecordingsContract.C_ISIPEPG_RECORDING, // 9
				IRecordingsContract.C_RECORDING_NAME // 10
		};

		String selection = IRecordingsContract.C_RECORDING_TYPE
				+ " = "
				+ String.valueOf(IRecordingsContract.RecordingType.AUTO_PVR_SCHEDULED
						.ordinal())
				+ " AND  EFF_START  >= "
				+ String.valueOf((Calendar.getInstance().getTimeInMillis() / 1000));

		Cursor nextRecordCursor = mClientContext.getContentResolver().query(
				IRecordingsContract.CONTENT_URI_Recordings, RECORD_PROJ,
				selection, null, "  EFF_START ASC LIMIT 1");

		Log.d(TAG, "Cursor received for the next record " + nextRecordCursor);

		if (nextRecordCursor != null && nextRecordCursor.getCount() > 0) {
			Log.d(TAG, "record details " + nextRecordCursor.getCount());
		} else {
			Log.d(TAG, "There is no record for the next Data");
		}

		if ((nextRecordCursor != null) && (nextRecordCursor.getCount() > 0)
				&& (nextRecordCursor.moveToFirst())) {

			RecordData nextRecordData = new RecordData(nextRecordCursor.getInt(0),
							nextRecordCursor.getInt(5),
							nextRecordCursor.getLong(2),
							nextRecordCursor.getLong(3),
							nextRecordCursor.getInt(4),
							rec_type[nextRecordCursor.getInt(1)],
							nextRecordCursor.getInt(6),
							nextRecordCursor.getInt(7),
							nextRecordCursor.getInt(8),
							nextRecordCursor.getInt(9),
							nextRecordCursor.getString(10),
							mClientContext);

			Log.d(TAG, "the parameters for the next record is channelId "
					+ nextRecordData.channelId + " est " + nextRecordData.est
					+ " eet " + nextRecordData.eet + " Preset Id "
					+ nextRecordData.presetid );

			holdLock(nextRecordData);
			nextRecordCursor.close();
			return nextRecordData;

		} else {

			holdLock(null);
			Log.d(TAG, "There is no record for the next Data, releasing lock autoPvr");
			if(nextRecordCursor != null)
				nextRecordCursor.close();
			return null;
		}
	}

	private void initRecording(RecordData record) {

		Medium medium = Medium.MEDIUM_TERRESTRIAL;
		//todo:tif
//		medium = Medium.fromInteger(ITvURI.Instance.getInterface().getMediumFromUniqueId(record.channelId));

		Log.d(TAG, "Tuned to channel ID " + record.channelId + " Medium "
				+ medium);
		Log.d(TAG, "mClientContext " + mClientContext + " medium " + medium
				+ " mAutoPVRData " + record);
		Log.d(TAG, "Channel ID " + record.channelId + "  record.presetid "
				+ record.presetid);

		mPlaytvmplayer = PlayTVMediaPlayerFactory.getInstance().getMPLInstance(
				mClientContext, PlayTVMediaPlayerFactory.REQUEST_TYPE_AUTO_PVR,
				medium, record.presetid);

		Log.d(TAG, "mPlaytvmplayer instance received is**** " + mPlaytvmplayer);

		if (mPlaytvmplayer != null) {
			mPlaytvmplayer.registerListener(mPlayStateMonitor, TAG);
			//mPlaytvmplayer.PlayChannel(medium, record.presetid);  //TO DO - replace with new API of playtvmpl
		} else {
			Log.w(TAG, "factory returned null for auto pvr");
			updateRecordingStatusInDB(IRecordingsContract.RecordingType.AUTO_PVR_FAILED
					.ordinal());
		}
	}

	/*public int getPresetId(MediumType medium, int channelId) {

		Uri tvContentProviderUri;
		int presetid = 0;

		switch (medium) {
		case MEDIUM_CABLE:
			tvContentProviderUri = IChannelContract.CONTENT_URI_CabChannelMap;
			break;
		case MEDIUM_SATELLITE:
			tvContentProviderUri = IChannelContract.CONTENT_URI_SatChannelMap;
			break;
		default:
		case MEDIUM_TERRESTRIAL:
			tvContentProviderUri = IChannelContract.CONTENT_URI_TerChannelMap;
			break;
		}

		String[] projection = { IChannelContract.C_PRESET_ID,
				IChannelContract.C_SID };

		String selection = IChannelContract.C_UNIQUE_ID + "== ?";
		String[] selectionArgs = { String.valueOf(channelId) };

		Cursor c = mClientContext.getContentResolver().query(
				tvContentProviderUri, projection, selection, selectionArgs,
				null);

		if ((c != null) && (c.getCount() > 0) && (c.moveToFirst())) {
			presetid = c.getInt(0);
			mAutoPVRData.programNumber = c.getInt(1);
		}
		if(c != null)
			c.close();
		return presetid;
	}
*/
	private void findNextRecordForScheduling() {
		cleanUpStale(false);
		RecordData nextData = getNextData();
		mCurrentRecordingStatus = AutoPVRStatus.IDLE.ordinal();
		mAlarmRegisteredTime = 0;

		if (nextData != null) {
			AutoPVR.getInstance()
					.registerAutoPVREvent(nextData, mClientContext);
		}
	}

	/****************** Handles all the PlayTvStateChangeListener CallBacks ************/

	class PlayTVStateMonitor implements IPlayTvStateChangeListener {

		@Override
		public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
				int presetNumber) {

		}

		@Override
		public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
				int presetNumber) {
			Log.d(TAG, "on play completed for auto pvr");
			startRecording(mAutoPVRData);
		}

		@Override
		public void onPlayFinished(Uri mediaPlayerUri, Medium medium,
				int presetNumber) {
			Log.e(TAG, "not expected on play finished");
		}

		@Override
		public void onPlayFailed(Uri mediaPlayerUri, Medium medium,
				int presetNumber, int reason) {

			Log.e(TAG, "on play failed");
			if (recordinstance != null) {
				recordinstance.stopRecording();
			} else {
				findNextRecordForScheduling();
			}
		}

		@Override
		public void onInfo(boolean cicamAvailable) {

		}

		@Override
		public void onError(PlayTvMediaPlayer mpl, int what , int extra) {

			Log.e(TAG, "on play Error");
			if (recordinstance != null) {
				recordinstance.stopRecording();
			}
		}

		@Override
		public void onLockStatusChanged(int type, int status) {

		}

		@Override
		public void onPurposeChanged(int purpose) {
			// TODO Auto-generated method stub

		}
		@Override
		public void onUriChanged(Uri mediaPlayerUri) {

		}

		@Override
		public void onCamUpgradeStarted(boolean status) {
		}
	}

	/****************** Handles all the Recoding Notifications CallBack ************/

	class AutoPvrRecordListener extends IonTvRecordControlCallback {

		public AutoPvrRecordListener() {
			super();
		}

		@Override
		public void onTimeshiftStatus(int arg0) {
		}

		@Override
		public void onTimeshiftPlaybackStatus(int arg0) {
		}

		@Override
		public void onTadStatus(int arg0) {
		}

		@Override
		public void onRecordingStatus(int status) {

			Log.d(TAG, "onRecordingStatus : Status " + status);

			switch (status) {

			case BcstConstants.RECORDING_STARTED:

				Log.d(TAG, "Recoding started call back has received: End time "
						+ mAutoPVRData.eet + " Start Time " + mAutoPVRData.est);

				mCurrentRecordingStatus = AutoPVRStatus.STARTED.ordinal();

				boolean messageAddedtoQueue = mRecodingTimeHandler.postDelayed(
						mRunnable, (mAutoPVRData.eet - mAutoPVRData.est)
								* MILLI_SECS);
				Log.d(TAG,
						"Recording started Notification has received Recoding will Run for "
								+ ((mAutoPVRData.eet - mAutoPVRData.est))
								+ " SECONDS "
								+ "Status of the Message added to Q: "
								+ messageAddedtoQueue);
				break;

			case BcstConstants.RECORDING_FINISHED:

				Log.d(TAG, "Recoding FINISHED call back has received "
						+ recordinstance);

				if (recordinstance != null) {

					synchronized (syncLock) {
						PlayTVMediaPlayerFactory
								.getInstance()
								.releaseMPLInstance(
										PlayTVMediaPlayerFactory.REQUEST_TYPE_AUTO_PVR,
										mPlaytvmplayer);
						mRecodingTimeHandler.removeCallbacks(mRunnable);
						mPlaytvmplayer = null;
						updateRecordingStatusInDB(IRecordingsContract.RecordingType.AUTO_PVR_NEW.ordinal());
						recordinstance.unregisterListenerCallback(mAutoPVRRecordListner);
						recordinstance = null;
					}
					findNextRecordForScheduling();
				}
				break;

			case BcstConstants.RECORDING_ERROR_SYSTEM:
			case BcstConstants.RECORDING_ERROR_HDDNOTCONNECTED:
			case BcstConstants.RECORDING_ERROR_CICAM:
			case BcstConstants.RECORDING_ERROR_HDDFULL:

				Log.d(TAG, "Recording has encountered an Error "
						+ recordinstance);

				if (recordinstance != null) {
					synchronized (syncLock) {
						PlayTVMediaPlayerFactory
								.getInstance()
								.releaseMPLInstance(
										PlayTVMediaPlayerFactory.REQUEST_TYPE_AUTO_PVR,
										mPlaytvmplayer);
						mRecodingTimeHandler.removeCallbacks(mRunnable);
						mPlaytvmplayer = null;

						updateRecordingStatusInDB(IRecordingsContract.RecordingType.RECORDING_FAILED
					.ordinal());
						recordinstance = null;
					}
					findNextRecordForScheduling();
				}
				break;
			}
		}

		@Override
		public void onRecordPlaybackStatus(int arg0) {
		}

		@Override
		public void licenseCheckStatus(boolean arg0) {
		}
	}

	public void onAlarm(int recId) {

		Log.d(TAG, "on Alarm Has been Called *** Alarm has fired");
		RecordData record = new RecordData(recId,mClientContext);
		if (mCurrentRecordingStatus == AutoPVRStatus.IDLE.ordinal())
			mRecodingTimeHandler.post(new AutoPVRAlarm(record));
	}

	@Override
	public void onHDDConnected() {
		Log.d(TAG, "onHDDConnected");
	}

	@Override
	public void onHDDRemoved() {
		Log.d(TAG, "onHDDRemoved");
		if (recordinstance != null) {
			//PlayTVKeyHandler.getInstance().onKeyDown(SystemEvents.HDD_NOT_CONNECTED, null);//TODO:TIF:commented..to be handled
			updateRecordingStatusInDB(IRecordingsContract.RecordingType.AUTO_PVR_FAILED.ordinal(),
					IRecordingsContract.RecordingError.REC_ERROR_NODISK.ordinal());
			recordinstance.stopRecording();
		}
	}
}
