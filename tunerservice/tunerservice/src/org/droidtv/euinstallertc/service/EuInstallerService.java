package org.droidtv.euinstallertc.service;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Calendar;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.ApplicationState;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.InstallationMode;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.mwapi.SemistandbyUpdate;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallertc.service.DirectTuneUtility.ChannelData;
import org.droidtv.htv.provider.HtvContract;
import org.droidtv.tv.media.IInstallerService;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.tv.tvinput.ITvContractExtras;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Binder;
import android.os.Bundle;
import android.os.Handler;
import android.os.Handler.Callback;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.content.ContentProviderOperation;
import android.content.ContentValues;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;

public class EuInstallerService extends Service implements IInstallerService {

	private static final String TAG = EuInstallerService.class.getName();

	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private Context mContext;
	private ArrayList<IInstallerServiceListener> listenerList = new ArrayList<IInstallerServiceListener>();
	private SemistandbyUpdate semisbyInst = null;
	private Callback mMessageHandler = null;
	private Handler mHandler = null;
	private Handler mLoadProviderDataHandler = null;
	private Handler mSwitchFirstChannelHandler = null;
	private Handler mPalDbBuildHandler = null;
	private Handler mAddExtSourceHandler = null;
	private int year, month, day;
	private int hour, minute;
	private long camscheduletimeinmsecs;
	private InstallerTVSettings instTVS = null;
	private Integer miHTVDTMutex1 = 1;
	private Integer miHTVDTMutex2 = 1;
	private Bundle mHTVDTCachedRequest = null;

	private static final int MSG_STARTBACKGROUND = 0;
	private static final int MSG_STOPBACKGROUND = 1;
	private static final int MSG_STARTUPDATE = 2;
	private static final int MSG_STOPUPDATE = 3;
	
	private final static int TCALARM_HOUR = 6;

	public final static String scheduleUpdateScheme = "scheduleUpdateAlarm";
	public final static String scheduleUpdateIntent = "org.droidtv.installer.SchedulUpdateAlm";
	public final static String scheduleUpdateIntentBroadcast = "org.droidtv.euinstallertc.service.EuInstallerService";
	
	public static final String KEYNAME_DT_FREQ = "DT_FREQ";
	public static final String KEYNAME_DT_TUNETYPE = "DT_TUNETYPE";
	public static final String KEYNAME_DT_SERVID = "DT_SERVID";
	public static final String KEYNAME_DT_NID = "DT_NID";
	public static final String KEYNAME_DT_ONID = "DT_ONID";
	public static final String KEYNAME_DT_TSID = "DT_TSID";
	public static final String KEYNAME_DT_TVSYS = "DT_TVSYS";
	public static final String KEYNAME_DT_MOD = "DT_MOD";
	public static final String KEYNAME_DT_SYMRT = "DT_SYMRT";
	public static final String KEYNAME_DT_BLANK = "DT_BLANK";
	public static final String KEYNAME_DT_SKIP = "DT_SKIP";
	public static final String KEYNAME_DT_CHNO = "DT_CHNO";
	public static final String KEYNAME_DT_PLPID = "DT_PLPID";
	public static final String KEYNAME_DT_CHID = "DT_CHID";
	public static final String KEYNAME_DT_CHNAME = "DT_CHNAME";
	public static final String KEYNAME_DT_BW = "DT_BW";
	public static final String KEYNAME_DT_WIXP = "DT_WIXP";
	public static final String KEYNAME_DTR_RESULT = "Result";
	public static final String KEYNAME_DTR_CHID = "channelId";
	public static final String KEYNAME_VALUE = "value";
	public static final String KEYVALUE_DIRECT_TUNE = "DIRECT_TUNE";
	public static final String KEYVALUE_DIRECT_INST = "DIRECT_INST";
	public static final String KEYVALUE_ADD_MCCH = "ADD_MCCH";
	
	public static final String ACTNAME_DIRECT_TUNE_RESULT = "org.droidtv.euinstallertc.DIRECT_TUNE_RESULT";
	public static final String ACTNAME_DIRECT_TUNE_WIXP = "org.droidtv.intent.action.WIXP_CHANNEL_INSTALL_COMPLETE";

	public class InstallerBinder extends Binder {
		InstallerBinder getService() {
			return InstallerBinder.this;
		}
	}

	public void installationComplete(int status) {
		IInstallerServiceListener registeredListner;
		Log.d(TAG, "installationComplete " + status);
		for (int index = 0; index < listenerList.size(); index++) {
			registeredListner = listenerList.get(index);
			registeredListner.onInstallationCompleted(status);
		}
	}

	public void camscheduleUpdateDate(int Date) {
		Log.d(TAG, "Started parsing Date from CAM OP - Scheduled Update");
		int tempyear = 0, tempmonth = 0;
		int K = 0;
		tempyear = (int) ((Date - 15078.2) / 365.25);
		tempmonth = (int) (((int) ((Date - 14956.1) - ((int) (tempyear * 365.25))) / 30.6001));
		day = Date - 14956 - ((int) (tempyear * 365.25))
				- ((int) (tempmonth * 30.6001));
		if ((tempmonth == 14) || (tempmonth == 15)) {
			K = 1;
		} else {
			K = 0;
		}
		year = tempyear + K + 1900;// To make sync with current year
		month = tempmonth - 1 - K * 12;
		Log.d(TAG, "Year obtained is  " + year + "Month obtained is  " + month
				+ "Day obtained is  " + day);
	}

	public void camSchedulUpdateTime(int Time) {
		minute = (Time % 10) * 6;
		hour = (Time / 10);
		Log.d(TAG, "Minute obtained is  " + minute + "Hour obtained is  "
				+ hour);
		long clientTime = Long.MAX_VALUE;
		camscheduletimeinmsecs = Long.MAX_VALUE;
		Calendar alarmTime = Calendar.getInstance();
		String mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		clientTime = alarmTime.getTimeInMillis();
		Log.d(TAG, "current time is " + mydate + "And time in milli secs is "
				+ clientTime);
		alarmTime.set(Calendar.YEAR, year);
		alarmTime.set(Calendar.MONTH, (month - 1)); // One month ahead issue
		alarmTime.set(Calendar.DAY_OF_MONTH, day);
		alarmTime.set(Calendar.HOUR_OF_DAY, (hour + 1)); // Due to current issue in clock - 1 hr ahead
		alarmTime.set(Calendar.MINUTE, minute);
		alarmTime.set(Calendar.SECOND, 0);
		mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		Log.d(TAG, "Alarm time is " + mydate);
		camscheduletimeinmsecs = alarmTime.getTimeInMillis();
		Log.d(TAG, "Alarm time is " + mydate + " timeinmsecs"
				+ camscheduletimeinmsecs);
		nwrap.storeCamData(camscheduletimeinmsecs);
		AlarmManager alarmMgr = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
		Intent intent = new Intent(scheduleUpdateIntent);
		Uri camscheduleupdateuri = Uri.parse(scheduleUpdateScheme + "://alarm?");
		intent.setData(camscheduleupdateuri);
		PendingIntent pendingIntent = PendingIntent.getBroadcast(this, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
		alarmMgr.set(AlarmManager.RTC_WAKEUP, camscheduletimeinmsecs, pendingIntent);
		// Set Aalrm & wait for Notify & trigger Update Installation from there like we do in camUpdateinstallation in urgent mode
	}

	@Override
	public boolean onUnbind(Intent intent) {
		Log.d(TAG, "onUnbind " + intent);
		//nwrap.unBindService();
		return super.onUnbind(intent);
	}

	@Override
	public IBinder onBind(Intent argIntent) {
		Log.d(TAG, "onBind " + argIntent);
		return IInstallerService.Instance.asBinder((IInstallerService) this);
	}

	@Override
	public void onCreate() {
		Log.d(TAG, "onCreate Enter");
		super.onCreate();
		final Calendar alarmTime = Calendar.getInstance();
		final int MIN_TOL = 10;
		mContext = this;
		//semisbyInst = new SemistandbyUpdate(mContext);
		//semisbyInst.registerServiceInstance(this);
		listenerList = new ArrayList<IInstallerServiceListener>();

		nwrap.setApplicationContext(mContext);
		
		// register for NVM bit changes
		instTVS = new InstallerTVSettings();
		instTVS.registerTvSettingsManager();

		
		
		nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_OBSERVER);

		mMessageHandler = new Callback() {

			@Override
			public boolean handleMessage(Message msg) {
				switch (msg.arg1) {
				case MSG_STARTBACKGROUND:
					Log.d(TAG, "MSG_STARTBACKGROUND: ");
					// This is Temporary fix for PR AN-36402
					/*
					if(nwrap.isBackgroundUpdateRequired()) {
						Log.d(TAG, "StartInstallation BACKGROUND_INSTALLATION Not Called callback");
					} else {*/
						//nwrap.setEuinstallerTokenId(0);
/*						semisbyInst
							.StartInstallation(
									IInstallerService.BACKGROUND_INSTALLATION,
									msg.arg2);*/
				//	}
					break;
				case MSG_STOPBACKGROUND:
					Log.d(TAG, "MSG_STOPBACKGROUND: ");
//					semisbyInst.StopInstallation(IInstallerService.BACKGROUND_INSTALLATION);
					nwrap.UnregisterTuningListener();
					break;
				case MSG_STARTUPDATE:
					Log.d(TAG, "MSG_STARTUPDATE: ");
					/* Going to check for 6 AM or schedule Update Installation */

					/* If 6AM Installation */
					int currenthour = alarmTime.get(Calendar.HOUR_OF_DAY);
					int currentmin = alarmTime.get(Calendar.MINUTE);
					
					long currentTimeinMilliSec = alarmTime.getTimeInMillis();
					Log.d(TAG, "Current Time is " + currentTimeinMilliSec);
					if ((currenthour == TCALARM_HOUR) && (currentmin < MIN_TOL)) {
						Log.d(TAG, "6 AM update\n");
//						if (semisbyInst.StartInstallation(IInstallerService.UPDATE_INSTALLATION, msg.arg2)) {
							//nwrap.initTVMediaPlayer();
//						}
					} else if (nwrap.isScheduleUpdateNeeded(currentTimeinMilliSec)) {
						Log.d(TAG, "Schedule Update\n");
						//nwrap.initTVMediaPlayer();
						//semisbyInst.StartInstallation(IInstallerService.UPDATE_INSTALLATION, 2);
					} else {
						/*
						 * Log.d(TAG,"Both 6 AM & Schedule update failed... so reply installation complete\n"); installationComplete(1);
						 */
						Log.d(TAG, "Semistandby update installation ");
//						if (semisbyInst.StartInstallation(IInstallerService.UPDATE_INSTALLATION, msg.arg2)) {
							//nwrap.initTVMediaPlayer();
//						}
					}
					break;
				case MSG_STOPUPDATE:
					Log.d(TAG, "MSG_STOPUPDATE: ");
					//semisbyInst.StopInstallation(IInstallerService.UPDATE_INSTALLATION);

					break;
				}
				return true;
			}
		};
		//mHandler = new Handler(mMessageHandler);
		mHandler = new Handler(new Callback() {
			
			@Override
			public boolean handleMessage(Message msg) {
				// TODO Auto-generated method stub
				return false;
			}
		});

		Log.d(TAG, "onCreate Exit");
	}

	@Override
	public void onDestroy() {
		Log.d(TAG, "onDestroy");
		super.onDestroy();
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		super.onStartCommand(intent, flags, startId);
		Log.d(TAG, "onStartCommand intent:" + intent + " flags:" + flags
				+ " startId:" + startId);

		if(intent == null){
			return START_STICKY;
		}
		String ExtraStr = intent.getStringExtra(KEYNAME_VALUE);
				
		//Log.d(TAG, "ExtraStr= " + ExtraStr);
		if(ExtraStr != null)
		{
			if (ExtraStr.equals("LOAD_PROVIDER_DATA")) {
		        mLoadProviderDataHandler = new Handler();
		        mLoadProviderDataHandler.post(loadProviderDataRunnable);
			} else if (ExtraStr.equals("SWITCH_FIRST_CHANNEL")) {
				mSwitchFirstChannelHandler = new Handler();
		        mSwitchFirstChannelHandler.post(switchToFirstChannel);
			} else if (ExtraStr.equals("PAL_DB_BUILD")) {
				mPalDbBuildHandler = new Handler();
				mPalDbBuildHandler.post(buildPALDB);
			} else if (ExtraStr.equals("ADD_EXT_SOURCE")) {
				mAddExtSourceHandler = new Handler();
				mAddExtSourceHandler.post(addExtSource);
			} else if (ExtraStr.equals(KEYVALUE_DIRECT_TUNE)) {
				DirectTuneHandler fDTHandler= new DirectTuneHandler(mContext);
				fDTHandler.execute(intent.getExtras());
			} else if (ExtraStr.equals(KEYVALUE_DIRECT_INST)) {
				DirectInstallHandler fInstallHandler= new DirectInstallHandler(mContext);
				fInstallHandler.execute(intent.getExtras());
			} else if(ExtraStr.equals(KEYVALUE_ADD_MCCH)) {
				mHandler.post(addSpecialChannels);
			} else {
				Log.d(TAG, "unknow ExtraStr=" + ExtraStr);
			}			
		}
		
		
		// continue running service until explicitly stopped, so return sticky.
		return START_STICKY;
	}
	
	class FreqInstallHandler extends AsyncTask<Bundle,Void,Void> {
		
		private final String TAG_SUB = FreqInstallHandler.class.getSimpleName();
		
		public FreqInstallHandler() {
		
		}

		@Override
		protected Void doInBackground(Bundle... avBundles) {
			Bundle fBundle = avBundles[0];
			
			Log.d(TAG_SUB, "doInBackground() is called.");
			
			if(fBundle.containsKey(KEYNAME_DT_FREQ) 
					&& fBundle.containsKey(KEYNAME_DT_TUNETYPE)) {				
				
				NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
				
				if(nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.IDLE 
						|| nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE) {
					
					if(nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE)
						nwrap.stopBckInstallation();
					
					Log.d(TAG_SUB, "Do DTR install...");
					
					
				}
				else
					Log.d(TAG_SUB, "Error: Some installing-related task is still running.");								
			}
			else
				Log.d(TAG_SUB, "Error: Some required parameters are missing.");
			
			return null;
		}
		
	}
	
	class DirectTuneHandler extends AsyncTask<Bundle,Void,Void> {
		
		private final String TAG_SUB = DirectTuneHandler.class.getSimpleName();
		private Context mContext;
						
		private void sendIntent(String p_action, int aiTuneType) {
			Log.d(TAG, "sendIntent " + p_action);
			Intent l_intent = new Intent(p_action);
			l_intent.putExtra("InstallMode", "DTR");
			if (aiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_C) {
				l_intent.putExtra("InstallMedium", "Cable");
			} else {
				l_intent.putExtra("InstallMedium", "Terrestrial");
			}
			mContext.sendStickyBroadcast(l_intent);
		}
		
		private int installChannel(ChannelData aChData, DirectTuneUtility.DirectTuneResultInterface aResultHandler) {
			
			Log.d(TAG, "installChannel() is called.");
			
			NativeAPIWrapper mWrapper = NativeAPIWrapper.getInstance();
			int fiMappedChId = -1;
			
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START", aChData.miTuneType);
			
			String[] fsvProjection = new String[] {HtvContract.HtvChannelSetting._ID};
			String fsSelection = HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER +"=? ";
			String[] fsvSelectionArgs = new String[]{Integer.toString(aChData.miChNo)};
			ArrayList<ContentProviderOperation> fvOperations=new ArrayList<ContentProviderOperation>();
			int fiDupChIdx = -1;
						
			/*
			if( aChData.miTuneType == INDEX_TUNETYPE_ANALOG)
				fiDupChIdx = mWrapper.findAnalogChannel(aChData.miFreq, INDEX_TUNETYPE_DVB_T, null);
			else
				fiDupChIdx = mWrapper.findDigitalChannel(aChData.miFreq, aChData.miTuneType, aChData.miServID, null, aChData.miONID, aChData.miTSID, null, null);
			*/
			if(fiDupChIdx != -1) {			
				Log.d(TAG, "Info: Duplicated channel found.");			
				fsSelection += " OR " + HtvContract.HtvChannelSetting._ID + "=" + fiDupChIdx;
			}

			Cursor fCursor = mContext.getContentResolver().query(HtvContract.HtvChannelSetting.CONTENT_URI, fsvProjection, fsSelection, fsvSelectionArgs, null);
			
			if(fCursor != null && fCursor.getCount() > 0) {
										
				String[] fsvSelectionForDelete = new String[]{"0"};
				
				fCursor.moveToFirst();
				
				do{			
					ContentProviderOperation.Builder builder=ContentProviderOperation.newDelete(Channels.CONTENT_URI);
					fsvSelectionForDelete[0] = String.valueOf(fCursor.getInt(0));
					builder.withSelection(Channels._ID +"= ?", fsvSelectionForDelete);
					
					fvOperations.add(builder.build());
									
								    	
				}while(fCursor.moveToNext());
			}
			
			if(fCursor != null) {
				fCursor.close();
				fCursor = null;
			}
			
			if(fvOperations.size() > 0) {
				Log.d(TAG, "Info: Remove channel with display number '" + aChData.miChNo + "' and duplicated channel from Htv content provider.");
				mContext.getContentResolver().delete(HtvContract.HtvChannelSetting.CONTENT_URI, fsSelection, fsvSelectionArgs);
				
				Log.d(TAG, "Info: Remove channel with display number '" + aChData.miChNo + "' and duplicated channel from TvProvider.");
				try {
					mContext.getContentResolver().applyBatch(Channels.CONTENT_URI.getAuthority(), fvOperations);
				}
				catch(Exception e) {
					Log.d(TAG, "Error: Remove channel from TvProvider fails. " + e.getMessage());
					
					aResultHandler.sendDTResultIntent(3);				
					sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED", aChData.miTuneType);
					return fiMappedChId;
				}
				
			}
			
			Log.d(TAG, "Info: Create the display number of the new channel in TvProvider.");
			
			int fiDispNum = 1;
			
			fsvProjection = new String[] {"max(cast(display_number as integer))"};
			fsSelection = Channels.COLUMN_VERSION_NUMBER + " in (?,?)";
			fsvSelectionArgs = new String[]{"0", "1"};
			
			fCursor = mContext.getContentResolver().query(Channels.CONTENT_URI, fsvProjection, fsSelection, fsvSelectionArgs, null);
			
			if(fCursor != null && fCursor.getCount() > 0) {
				fCursor.moveToFirst();
				
				if(!fCursor.isNull(0)) {
					fiDispNum = fCursor.getInt(0);
				    
					if(fiDispNum <= 0)
						fiDispNum = 1;
					else
						fiDispNum += 1;
				}
			}
			
			if(fCursor != null) {
				fCursor.close();
				fCursor = null;
			}
			
			Log.d(TAG, "Info: Display number-> " + fiDispNum);
			
			aChData.miPresetNum = mWrapper.GetLastAnalogPresetNumber()+1;
			
			mWrapper.unregisterTvProviderContentObservers();
					
			try {
				
				ContentValues val=new ContentValues();
				
				val.put (Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService");
				val.put (Channels.COLUMN_TYPE,DirectTuneUtility.mapTuneTypeString(aChData.miTuneType));				
				val.put (Channels.COLUMN_SERVICE_TYPE, Channels.SERVICE_TYPE_AUDIO_VIDEO);								
				val.put (Channels.COLUMN_NETWORK_AFFILIATION , NativeAPIWrapper.HTV_DT_CHANNEL_UPDATE_FLAG);
				
				if(aChData.miONID != null)
					val.put (Channels.COLUMN_ORIGINAL_NETWORK_ID, aChData.miONID);
				
				if(aChData.miTSID != null)
					val.put (Channels.COLUMN_TRANSPORT_STREAM_ID, aChData.miTSID);
				
				if(aChData.miServID != null)
					val.put (Channels.COLUMN_SERVICE_ID, aChData.miServID);
				
				val.put (Channels.COLUMN_DISPLAY_NUMBER,Integer.toString(fiDispNum));	
				val.put (Channels.COLUMN_DISPLAY_NAME, "");		
				val.put (Channels.COLUMN_DESCRIPTION, ""); 	
				val.put (Channels.COLUMN_BROWSABLE, 1);
				val.put (Channels.COLUMN_SEARCHABLE, 1);
				val.put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,DirectTuneUtility.formBlobData(aChData));		
				val.put (Channels.COLUMN_LOCKED,0);
				val.put (Channels.COLUMN_VERSION_NUMBER, DirectTuneUtility.mapVersion(aChData.miTuneType));
				
				Log.d(TAG, "Info: Insert channel data into TvProvider");
				
				Uri fCPResult = mContext.getContentResolver().insert(TvContract.Channels.CONTENT_URI ,val);
				
				Log.d(TAG, "Info: insert result- " + fCPResult);
				
				Log.d(TAG, "Info: Insert channel data into Htv Content Provider");
				
				fiMappedChId = Integer.parseInt(fCPResult.getLastPathSegment());
				
				val=new ContentValues();
				
				val.put(HtvContract.HtvChannelSetting._ID, fiMappedChId);
				val.put(HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE, HtvContract.HtvBaseDefs.TYPE_TUNER);
				val.put(HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, Integer.toString(aChData.miChNo));
				val.put(HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID, fiMappedChId);
				
				val.put(HtvContract.HtvChannelSetting.COLUMN_SKIP1, 1);
				val.put(HtvContract.HtvChannelSetting.COLUMN_SKIP2, 1);
				val.put(HtvContract.HtvChannelSetting.COLUMN_FREEPKG, 1);
				
				mContext.getContentResolver().insert(HtvContract.HtvChannelSetting.CONTENT_URI, val);			
				
				Log.d(TAG, "Info: Sync TvProvider to Installer.");
				mWrapper.LoadTvProviderData();
				mWrapper.LoadFreqMapDataData();				
				
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE", aChData.miTuneType);
				
				//sendDTResultIntent(0);			
			}
			catch(IOException e) { 
				Log.d(TAG, "Error: " + e.getMessage());
				fiMappedChId = -1;
				aResultHandler.sendDTResultIntent(3);
				
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED", aChData.miTuneType);
			}
			catch(NumberFormatException e) {
				Log.d(TAG, "Error: Channel ID can't be extracted from insertion. " + e.getMessage());
				fiMappedChId = -1;
				aResultHandler.sendDTResultIntent(3);
				
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED", aChData.miTuneType);
			}
			
			mWrapper.registerTvProviderContentObservers();
			
			return fiMappedChId;			
		}

		public DirectTuneHandler(Context context) {
			mContext = context;
		}
		
		private boolean getChannelInfo(Bundle aBundle) {
			
			Log.d(TAG, "getChannelInfo() is called.");
			
			boolean fbResult = false;
			
			String[] fsvProjection = new String[]{Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_INTERNAL_PROVIDER_DATA};
			String fsSelection = Channels._ID + "=? ";
			String[] fsvSelectionArgs = new String[]{String.valueOf(aBundle.getInt(KEYNAME_DT_CHID))};
			
			Cursor fCursor = mContext.getContentResolver().query(TvContract.Channels.CONTENT_URI, fsvProjection, fsSelection, fsvSelectionArgs, null);
			
			if(fCursor != null) {
				
				if(fCursor.getCount() > 0) {
					fCursor.moveToFirst();
									
					String fsTuneType = fCursor.getString(0);				
					int fiTuneType = -1;
					
					if(Channels.TYPE_DVB_T.equals(fsTuneType)) {
						fiTuneType = 0;
					}
					else if(Channels.TYPE_DVB_T2.equals(fsTuneType)) {
						fiTuneType = 2;
					}
					else if(Channels.TYPE_DVB_C.equals(fsTuneType)) {
						fiTuneType = 1;
					}
					
					if(fiTuneType == 0 || fiTuneType == 1 || fiTuneType == 2) {
						
						IIntKeyValueables fKeyvalues = IIntKeyValueables.Instance.getInterface();
						
						aBundle.putInt(KEYNAME_DT_TUNETYPE, fiTuneType);
						aBundle.putInt(KEYNAME_DT_SERVID, fCursor.getInt(1));
						
						try
						{
							fKeyvalues.setBlob(fCursor.getBlob(2));
							aBundle.putInt(KEYNAME_DT_FREQ, fKeyvalues.getInt(ITvContractExtras.C_FREQUENCY));
						
							fbResult = true;
						}
						catch(Exception e) {
							Log.d(TAG, "Error: during processing Blob data. Msg:" + e.getMessage());
						}
							
					}
				}
				
				fCursor.close();
				fCursor = null;
			}
			
			return fbResult;
		}
		
		private void handleRequest(Bundle fBundle) {			
			
			Log.d(TAG_SUB, "Info: Start to handle HTV DT request.");
			
			DirectTuneUtility.DirectTuneResultInterface fResultHandler = DirectTuneUtility.getDirectTuneResultHandler(fBundle.containsKey(KEYNAME_DT_WIXP), mContext);
			
			if(fBundle.containsKey(KEYNAME_DT_CHID)) {
				
				Log.d(TAG_SUB, "Info: Prepare to update channel info.");
				
				if(getChannelInfo(fBundle)) {
					
					if(nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.IDLE 
							|| nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE) {
						
						if(nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE)
							nwrap.stopBckInstallation();
						
						Intent fIntent = new Intent();
						fIntent.setClass(mContext, DirectTuneHandleActivity.class);
						fIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
						fIntent.putExtras(fBundle);
						mContext.startActivity(fIntent);						
					}
					else {
						Log.d(TAG_SUB, "Error: Some installing-related task is still running.");					
						//sendDTResultIntent(2);
					}
				}
				else {
					Log.d(TAG_SUB, "Error: Some required parameters are missing.");
					//sendDTResultIntent(1);
				}
				
			} else if(fBundle.containsKey(KEYNAME_DT_FREQ) && fBundle.containsKey(KEYNAME_DT_TUNETYPE)) {
				
				int fiTuneType = fBundle.getInt(KEYNAME_DT_TUNETYPE);
				
				if(((fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T
						|| fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_C
						|| fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T2) && fBundle.containsKey(KEYNAME_DT_SERVID))
					|| (fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_ANALOG && fBundle.containsKey(KEYNAME_DT_TVSYS)) ) {
					
					if(nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.IDLE 
							|| nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE) {			
						
						if(nwrap.getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE)
							nwrap.stopBckInstallation();
						
						if(fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T
								|| fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_C
								|| fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T2) {
							
							Log.d(TAG_SUB, "Info: Handle digital channel.");
							
							Integer fiNID = null;
							Integer fiONID = null;
							Integer fiTSID = null;
							Integer fiMod = null;
							Integer fiSymRt = null;
							int fiTuneFreq = fBundle.getInt(KEYNAME_DT_FREQ);						
							int fiServID = fBundle.getInt(KEYNAME_DT_SERVID);
							Integer fiPLPID = null;

							if(fBundle.containsKey(KEYNAME_DT_NID))
								fiNID = fBundle.getInt(KEYNAME_DT_NID);
							
							if(fBundle.containsKey(KEYNAME_DT_ONID))
								fiONID = fBundle.getInt(KEYNAME_DT_ONID);
							
							if(fBundle.containsKey(KEYNAME_DT_TSID))
								fiTSID = fBundle.getInt(KEYNAME_DT_TSID);
							
							if(fBundle.containsKey(KEYNAME_DT_MOD))
								fiMod = fBundle.getInt(KEYNAME_DT_MOD);
							
							if(fBundle.containsKey(KEYNAME_DT_SYMRT))
								fiSymRt = fBundle.getInt(KEYNAME_DT_SYMRT);

							if(fBundle.containsKey(KEYNAME_DT_PLPID))
								fiPLPID = fBundle.getInt(KEYNAME_DT_PLPID);
							
							int fiFoundChId = nwrap.findDigitalChannel(fiTuneFreq, 
																			fiTuneType, 
																			fiServID, 
																			fiNID, 
																			fiONID, 
																			fiTSID,
																			fiMod,
																			fiSymRt,
																			fiPLPID);
							
							if(fiFoundChId != -1 ) {
								
								Log.d(TAG_SUB, "The required channel is already installed.");
								Log.d(TAG_SUB, "The required channel is already installed. fiFoundChId" + fiFoundChId);
								fResultHandler.sendDTResultIntent(0);
								fResultHandler.switchToSpecificChannel(fiFoundChId);
							}
							else {
								
								Log.d(TAG_SUB, "The required channel isn't found.");
                                Log.d(TAG_SUB, "The required channel fiPLPID is " + fiPLPID);
								//Integer fiPLPID = null;
								Integer fiBW = null;
								
								//if(fBundle.containsKey(KEYNAME_DT_PLPID))
								//	fiPLPID = fBundle.getInt(KEYNAME_DT_PLPID);
								
								if(fBundle.containsKey(KEYNAME_DT_BW)) {								
									fiBW = fBundle.getInt(KEYNAME_DT_BW);
									
									if(fiBW != 0 && fiBW != 1 && fiBW != 2 && fiBW != 4)
										fiBW = 0;
								}
                                Log.d(TAG_SUB, "The required channel fiBW is " + fiBW);
								if(fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_C
										|| (fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T && fiBW != null)
										|| (fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T2 && fiPLPID != null && fiBW != null)) {
									
									Log.d(TAG_SUB, "Do Direct Install then tune...");
									
									ChannelData fChData = new ChannelData(fiTuneType, fiTuneFreq, fiONID, fiTSID, fiServID, fiSymRt);
									
									if(fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T)
										fChData.miBW = fiBW;
									
									if(fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T2){
										fChData.miBW = fiBW;
										fChData.miPLPID = fiPLPID;
									}
									
									fChData.miChNo = nwrap.getHTVBiggestDisplayNumber() + 1;
									
									fiFoundChId = installChannel(fChData,fResultHandler);
									
									if(fiFoundChId != -1){
										fResultHandler.switchToSpecificChannel(fiFoundChId);
									}
								}
								else {
									Log.d(TAG_SUB, "Do DTR install...");
									
									Intent fIntent = new Intent();
									fIntent.setClass(mContext, fBundle.containsKey(KEYNAME_DT_WIXP)?WixpDirectTuneHandleActivity.class:DirectTuneHandleActivity.class);
									fIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
									fIntent.putExtras(fBundle);
									mContext.startActivity(fIntent);
								}							
							}										
													
						}
						else {
							
							Log.d(TAG_SUB, "Info: Handle analog channel.");
							
							int fiFoundChId = nwrap.findAnalogChannel(fBundle.getInt(KEYNAME_DT_FREQ), 
																	0, 
																	fBundle.getInt(KEYNAME_DT_TVSYS));
							
							if(fiFoundChId != -1) {
								Log.d(TAG_SUB, "The required channel is already installed.");
								
								fResultHandler.sendDTResultIntent(0);
								fResultHandler.switchToSpecificChannel(fiFoundChId);
							} else {
								Log.d(TAG_SUB, "The required analog channel isn't found. Do DTR install...");
								
								Intent fIntent = new Intent();
								fIntent.setClass(mContext, fBundle.containsKey(KEYNAME_DT_WIXP)?WixpAnalogDirectTuneHandleActivity.class:AnalogDirectTuneHandleActivity.class);
								fIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
								fIntent.putExtras(fBundle);
								mContext.startActivity(fIntent);
							}
						}
					}
					else {
						Log.d(TAG_SUB, "Error: Some installing-related task is still running.");					
						fResultHandler.sendDTResultIntent(2);
					}					
				}
				else {
					Log.d(TAG_SUB, "Error: Some required parameters are missing.");
					fResultHandler.sendDTResultIntent(1);
				}																
			}
			else {
				Log.d(TAG_SUB, "Error: Some required parameters are missing.");
				fResultHandler.sendDTResultIntent(1);
			}	
		}
		
		@Override
		protected Void doInBackground(Bundle... avBundles) {
			
			Log.d(TAG_SUB, "doInBackground() is called.");
			Bundle fRequest = null;
			
			synchronized(miHTVDTMutex2) {
				mHTVDTCachedRequest = avBundles[0];
			}
			
			nwrap.notifyNewHTVDTRequestArrival();
			
			synchronized(miHTVDTMutex1) {
				
				nwrap.acquireHTVDTSemaphore();
				nwrap.releaseHTVDTSemaphore();
				
				synchronized(miHTVDTMutex2) {
					fRequest = mHTVDTCachedRequest;
					mHTVDTCachedRequest = null;
				}
				
				if(fRequest != null)
					handleRequest(fRequest);
			}
									
			return null;
		}
				
	}
	
	

	final Runnable loadProviderDataRunnable = new Runnable() {
        public void run() {
			Log.d(TAG, "loadProviderDataRunnable: ");
			nwrap.stopBckInstallation();
			nwrap.LoadTvProviderData();
			nwrap.LoadFreqMapDataData();
			// broadcast message to all the modules that auto installation completed
            Intent complete_intent = new Intent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
           	complete_intent.putExtra("InstallMode", "Background");

            //complete_intent.putExtra("InstallMedium", "Cable");
            complete_intent.putExtra("InstallMedium", "Terrestrial");
           	mContext.sendStickyBroadcast(complete_intent);
            Log.d(TAG, "send intent broadcast org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");

			//nwrap.switchToFirstAvailableChannel(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
        }
    };

	final Runnable switchToFirstChannel = new Runnable() {
        public void run() {
			Log.d(TAG, "switchToFirstChannel: ");
			nwrap.switchToFirstAvailableChannel(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);			
        }
    };

	final Runnable buildPALDB = new Runnable() {

        public void run() {
			Log.d(TAG, "PRESET_DB_BUILD: ");

			ContentValues[] val = new ContentValues[41];

			for(int Loop = 0; Loop < 41; Loop++) {

				val[Loop] = new ContentValues();

				//val[Loop].put (Channels.COLUMN_PACKAGE_NAME,1); /* TvProvider will fill this up */
				val[Loop].put (Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService"); /* Check with Mounesh/Pavan what to fill here */
				val[Loop].put (Channels.COLUMN_TYPE,"TYPE_PAL");
				val[Loop].put (Channels.COLUMN_SERVICE_TYPE,"SERVICE_TYPE_AUDIO_VIDEO");
				//val[Loop].put (Channels.COLUMN_NETWORK_AFFILIATION , (TvpData.NewPreset == 1) ? "New" : "");
				val[Loop].put (Channels.COLUMN_ORIGINAL_NETWORK_ID, 0);
				val[Loop].put (Channels.COLUMN_TRANSPORT_STREAM_ID, 0);
				val[Loop].put (Channels.COLUMN_SERVICE_ID, 0);
				//channel 925 doesn't exist
				if(Loop >= 24)
					val[Loop].put (Channels.COLUMN_DISPLAY_NUMBER, (902 + Loop));
				else
					val[Loop].put (Channels.COLUMN_DISPLAY_NUMBER, (901 + Loop));
				val[Loop].put (Channels.COLUMN_DISPLAY_NAME, "------");
				//val[Loop].put (Channels.COLUMN_DESCRIPTION,((TvpData.ScramblingStatus== 1) ? "Scrambled" :"")); /* See if we can put medium information here */
				val[Loop].put (Channels.COLUMN_BROWSABLE, 1);
				val[Loop].put (Channels.COLUMN_SEARCHABLE, 1);
				val[Loop].put (Channels.COLUMN_LOCKED, 0);
				val[Loop].put (Channels.COLUMN_INTERNAL_PROVIDER_DATA, getATVBlobData(Loop));
				val[Loop].put (Channels.COLUMN_VERSION_NUMBER, 1);
			}
			Log.d (TAG, "Going to do bulk insert of preset channel table ");
			mContext.getContentResolver().bulkInsert(TvContract.Channels.CONTENT_URI ,val);
			nwrap.SyncHTvProvider();
        }
    };

	final Runnable addExtSource = new Runnable() {
        public void run() {
			Log.d(TAG, "addExtrenSource: ");
			nwrap.addExtSource();
        }
    };
    
    final Runnable addSpecialChannels = new Runnable() {
		
		@Override
		public void run() {
			Log.d(TAG, "add special channels for MyChoice...");
			nwrap.refreshSpecialChannelsForMyChoice();
		}
	};
	
	private byte[] getATVBlobData (int index) {
		Log.d(TAG, "getATVBlobData(), index: " + index);
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		byte[] BlobData = null;
		int PAL_BG = 1, SECAM_BG = 1, PAL_I = 2, PAL_DK = 4, SECAM_DK = 4, SECAM_L = 8;
		int[] atvFreqList = { 	49750, 119250, 184000, 217250, 224250, 280250, 304250, 335250, 360250, 448250,
							   503250, 527250, 783250,  55750,  64250, 209250, 223250, 343250, 548250, 176250,
							   590250,  62250, 231250, 615250, 231250, 455250,  48250,  63750,  69250, 182250,
							   196250, 319250, 471250, 487250, 519250, 515250, 631250, 695250, 743250, 831250,
							   663250
							};
		int[] atvModulationList = { PAL_DK, PAL_BG, SECAM_L, PAL_BG, PAL_BG, SECAM_DK, PAL_DK, PAL_BG, SECAM_DK, PAL_DK,
									PAL_I, PAL_I, PAL_DK, SECAM_L, PAL_BG, PAL_BG, SECAM_DK, PAL_I, SECAM_BG, SECAM_DK,
									PAL_BG, PAL_BG, PAL_BG, PAL_I, PAL_BG, PAL_BG, PAL_BG, SECAM_L, PAL_BG, PAL_BG,
									PAL_I, PAL_BG, PAL_BG, PAL_I, PAL_BG, SECAM_DK, SECAM_DK, PAL_BG, PAL_BG, PAL_I,
									SECAM_L
									};

		keyvalues.put (ITvContractExtras.C_PRESETPTC, 0);
		keyvalues.put (ITvContractExtras.C_PLPID, 0);
		keyvalues.put (ITvContractExtras.C_FREQUENCY, atvFreqList[index]);
		keyvalues.put (ITvContractExtras.C_BANDWIDTH, 0);
		keyvalues.put (ITvContractExtras.C_SYMBOLRATE, 0);
		keyvalues.put (ITvContractExtras.C_MODULATION, atvModulationList[index]);
		keyvalues.put (ITvContractExtras.C_STREAMPRIORITY, 0);
		keyvalues.put (ITvContractExtras.C_NUMERICSELECT, 1);
		keyvalues.put (ITvContractExtras.C_SCRAMBLED, 0);
		keyvalues.put (ITvContractExtras.C_HBBTVON, 0);
		keyvalues.put (ITvContractExtras.C_USERHIDDEN, 0);
		keyvalues.put (ITvContractExtras.C_NEWPRESET, 0);
		keyvalues.put (ITvContractExtras.C_CNINETWORK_ID, 0);
		keyvalues.put (ITvContractExtras.C_AUDIOPID, 8191);
		keyvalues.put (ITvContractExtras.C_VIDEOPID, 8191);
		keyvalues.put (ITvContractExtras.C_PCRPID, 0);
		keyvalues.put (ITvContractExtras.C_VIDEOSTREAMTYPE, 0);
		keyvalues.put (ITvContractExtras.C_AUDIOSTREAMTYPE, 0);
		keyvalues.put (ITvContractExtras.C_TXTPAGES, 0);
		keyvalues.put (ITvContractExtras.C_SERVICEIDENTIFIER, 0);
		keyvalues.put (ITvContractExtras.C_NetworkId, 0);
		keyvalues.put (ITvContractExtras.C_TXTSUBPAGE, 0);
		keyvalues.put (ITvContractExtras.C_SAP, 0);
		keyvalues.put (ITvContractExtras.C_PreferredStereo, 0);
		keyvalues.put (ITvContractExtras.C_LCN, 0);
		keyvalues.put (ITvContractExtras.C_USEROVERRULEDLOGOURI, 0);

		keyvalues.put (ITvContractExtras.C_PMTPID, 8191);
		keyvalues.put (ITvContractExtras.C_SECONDARY_AUDIOPID, 8191);
		keyvalues.put (ITvContractExtras.C_SECONDARY_AUDIOSTREAMTYPE, 0);
		keyvalues.put (ITvContractExtras.C_DATETIMESTAMP, 0);
		keyvalues.put (ITvContractExtras.C_FREECIMODE, 0);
		keyvalues.put (ITvContractExtras.C_MATCH_BRANDID, 0);
		keyvalues.put (ITvContractExtras.C_BRANDIDS, 0);
		keyvalues.put (ITvContractExtras.C_LOGOID, 0);

		keyvalues.put (ITvContractExtras.C_INSTALLER_BLOB, 0);

		try {
			/* Newly added for CR AN-81115. Putting try catch to ensure no exception seen while upgrading */
			keyvalues.put (ITvContractExtras.C_HDLCN, 49152);
		} catch (Exception e) {
			Log.e(TAG, "Error blobput	" + e);
		}


		try {
			BlobData = keyvalues.getBlob();
		} catch (Exception e) {
			Log.e(TAG, "Error FormBlobData	" + e);
		}

		return BlobData;
	}

	@Override
	public boolean StartInstallation(int mode, int param) {
		boolean retval = true;
		if ((nwrap.getApplicationState() == ApplicationState.IDLE)
				|| (nwrap.getApplicationState() == ApplicationState.INST_SERVICE)) {
			Log.d(TAG, "StartInstallation " + mode + " : " + param);
			// set the current state to service
			nwrap.setApplicationState(ApplicationState.INST_SERVICE);
			nwrap.setApplicationContext(mContext);
			nwrap.background_SetSystemCountry();
			nwrap.createMWInstance();

			Message msg = mHandler.obtainMessage();
			switch (mode) {
			case IInstallerService.BACKGROUND_INSTALLATION:
				Log.d(TAG, "StartInstallation BACKGROUND_INSTALLATION from EuinstallerTcService");
				msg.arg1 = MSG_STARTBACKGROUND;
				msg.arg2 = param;
				mHandler.sendMessage(msg);

				break;
			case IInstallerService.UPDATE_INSTALLATION:
				Log.d(TAG, "StartInstallation UPDATE_INSTALLATION from EuinstallerTcService");

				msg.arg1 = MSG_STARTUPDATE;
				msg.arg2 = param;
				mHandler.sendMessage(msg);

				// nwrap.setApplicationContext(mContext);
				// nwrap.initTVMediaPlayer();
				// retval = semisbyInst.StartInstallation
				// (IInstallertcService.UPDATE_INSTALLATION, msg.arg2);

				break;
			}
		} else {
			// if wizard or settings is active service calls should be ignored
			retval = false;
			Log.d(TAG, "StartInstallation call ignored as Activity is up");
		}

		Log.d(TAG, "### EuinstallerTcService returned " + retval);
		return retval;
	}

	@Override
	public boolean StopInstallation(int mode) {
		boolean retval = true;
		Log.d(TAG, "StopInstallation " + mode);

		if ((nwrap.getApplicationState() == ApplicationState.IDLE)
				|| (nwrap.getApplicationState() == ApplicationState.INST_SERVICE)) {
			// set the current state to service
			nwrap.setApplicationState(ApplicationState.INST_SERVICE);

			Message msg = mHandler.obtainMessage();
			switch (mode) {
			case IInstallerService.BACKGROUND_INSTALLATION:
				Log.d(TAG, "StopInstallation BACKGROUND_INSTALLATION from EuinstallerTcService");
				// retval = semisbyInst.StopInstallation (mode);

				msg.arg1 = MSG_STOPBACKGROUND;
				msg.arg2 = 0;
				mHandler.sendMessage(msg);
				break;
			case IInstallerService.UPDATE_INSTALLATION:
				Log.d(TAG, "StopInstallation UPDATE_INSTALLATION from EuinstallerTcService");
				msg.arg1 = MSG_STOPUPDATE;
				msg.arg2 = 0;
				mHandler.sendMessage(msg);

				break;
			}
		} else {
			// if wizard or settings is active service calls should be ignored
			retval = false;
			Log.d(TAG, "StopInstallation call ignored as Activity is up");
		}

		Log.d(TAG, "StopInstallation returned " + retval);
		return retval;
	}

	@Override
	public void registerInstallerListener(IInstallerServiceListener listener) {
		Log.d(TAG, "registerInstallerListener " + listener);
		listenerList.add(listener);
	}

	@Override
	public void unRegisterInstallerListener(IInstallerServiceListener listener) {
		Log.d(TAG, "unRegisterInstallerListener " + listener);
		listenerList.remove(listener);
	}

}
