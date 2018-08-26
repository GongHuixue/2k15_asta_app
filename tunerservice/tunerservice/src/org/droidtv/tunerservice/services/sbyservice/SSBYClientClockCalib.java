package org.droidtv.tunerservice.services.sbyservice;

import java.util.Map;

import org.droidtv.tunerservice.interfaces.IClockHandlerCallBacks;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;
import org.droidtv.tunerservice.tvmpl.ClockHandler;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.PlayTvMsgHandler;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;

import org.droidtv.tv.context.TvIntent;

import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl.ITvSemiStandbyCallback;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.ISessionHandlerTIF;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.*;
/*begin:min.jiang add 2016-01-21, for ntp time*/
import android.content.IntentFilter;
import org.droidtv.tunerservice.channelfilter.ChannelFilter;

import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.tvpower.ITvPowerManager.ShutdownLock;
import org.droidtv.tv.tvclock.ITvClockManager;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.ITvSettingsManager.ITvSettingsManagerNotify;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.SystemProperties;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/*end:min.jiang add*/
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.media.tv.TvContract;
import android.net.Uri;
import android.os.Handler;
import android.os.Handler.Callback;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.os.Bundle;

public class SSBYClientClockCalib implements IClockHandlerCallBacks, Callback {
	
	public static final String TAG = "SSBYServiceClk";
	
	private final static int CLOCKCALIB_READY			=1;
	private final static int CLOCKCALIB_INPROGRESS		=2;
	private final static int CLOCKCALIB_STOPPING		=3;
	
	private final static int MAX_WAIT_TIME_SEC_CLOCK	=30;
		
	SemiStandbyService sbyServiceHandler = null;
	private int clockcalibstate = CLOCKCALIB_READY;
	private PlayTvMsgHandler sbyClockHandler = null;
	private Context mContext=null;
	private PlayTVFacMediaPlayer ClockPlayTvmpl = null;
	private Medium mActionMedium = Medium.MEDIUM_INVALID;
	private boolean mRestoreLastSelection = false;
	
	private static final int EVT_TIMEOUT 	= 1;
	private static final int EVT_CANCELLED 	= 2;
	private static final int EVT_SELECTEXTN = 3;
	private static final int EVT_CONNECT	= 4;
	private static final int EVT_CONNECTED	= 5;
	
	private ITvSemiStandbyControl mCallback=null;
	private final int id = ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION;
	private SbyCallback msbyCallbackclass = null;
	//private MediaplayerCallbackClass mMediaplayerCallback = null;
	private Handler mainHandler = null;
	/*begin:min.jiang add 2016-01-21, for ntp time*/
	private static final int EVT_NTP_TIMEOUT = 6;	
	private static String NTP_WAKEUP_ACTION = "org.droidtv.tv.semistandby.ntp.wakeup";	
	private int hour = 1;
	private Object mLock = new Object();
	private boolean mColdStart = false;	
	private boolean mSessionFlag = false;
	private boolean mClockFlag = false;
	private ShutdownLock mShutdownLock = null;
	private ITvClockManager mTvclockmanager = null;
	private ITvPowerManager mTvPowerManager =	null;
	private ClockHandlerSession mClockSession = null;
	private static ITvSettingsManager mTvSettingsManager = ITvSettingsManager.Instance.getInterface();
	class NtpSettingsNotify extends ITvSettingsManagerNotify{
		public void OnUpdate(int property) {
			Log.d(TAG, "OnUpdate : property is: " + property);
			if(property == TvSettingsConstants.PBSMGR_PROPERTY_DNT_SOURCE){
				if(mTvSettingsManager.getInt(property,0,0) == TvSettingsDefinitions.PbsDNTSourceConstants.PBSMGR_DNT_SOURCE_AUTOMATIC_NTP){
					Log.d(TAG, "OnUpdate : updateNtpTime()");
					updateNtpTime();
				}
			}
        }
    }
	private Runnable updateRunner = new Runnable(){
		
		@Override
		public void run() {
			// TODO Auto-generated method stub
			ConnectivityManager connMgr = (ConnectivityManager)mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
			NetworkInfo netInfo = connMgr.getActiveNetworkInfo();
			if(netInfo != null && netInfo.isConnectedOrConnecting() == true)
			{
				Log.i(TAG, "updateRunner : check network is available");
				synchronized (mLock) {
				NtpTrustedTime tpvisionTime = NtpTrustedTime.getInstance(mContext);			        
				Log.d(TAG, "start get ntp time");		
				if(tpvisionTime.forceRefresh()){
					long curTime = tpvisionTime.currentTimeMillis();
					Calendar cal = Calendar.getInstance();
					cal.setTimeInMillis(curTime);
					Date data = cal.getTime();
					SimpleDateFormat format = new SimpleDateFormat("dd/MMM/yyyy:HH:mm:ss");
					String localTimeStr = format.format(data) ;  
					Log.d(TAG, "get ntp time: " + localTimeStr);			
					
					mTvclockmanager.SetTime( curTime,0,ITvClockManager.eClockSources.ECD, mColdStart);
					mColdStart = false;	
					//releaseDSL();
				}	
				Log.d(TAG, "end get ntp time");
				}

			}

		}
	};	
	
    private BroadcastReceiver NtpSyncReceiver = new BroadcastReceiver() {

            @Override
            public void onReceive(Context context, Intent intent) {
                Log.d(TAG, "NtpSyncReceiver - onReceive");
                String action = intent.getAction();
                Log.d(TAG, "action = " + action);
				if(TvIntent.ACTION_TV_POWER_STATE_CHANGE_BEGIN.equals(action)){
					ITvPowerManager.PowerStates targetPowerStates = ITvPowerManager.PowerStates.POWER_STATE_UNKNOWN;
					targetPowerStates = (PowerStates)intent.getSerializableExtra(TvIntent.TARGET_TV_POWER_MODE);
				
					ITvPowerManager.PowerStates mPowerStatesSource = ITvPowerManager.PowerStates.POWER_STATE_UNKNOWN; 
					mPowerStatesSource = (PowerStates) intent.getSerializableExtra(TvIntent.SOURCE_TV_POWER_MODE);						
					OnChangePowerState(mPowerStatesSource, targetPowerStates);
				}else if(ConnectivityManager.CONNECTIVITY_ACTION.equals(action)){
					updateNtpTime();
				}else if(NTP_WAKEUP_ACTION.equals(action)){
					//SetAlarmforNtp(hour);
					// Reno 20160421 modifies time of sync cycle by ntp on different conditions
					String pbsStandbyMode = SystemProperties.get("persist.sys.pbs_standby_mode");
					Log.d(TAG, "PBS standby mode: " + pbsStandbyMode);
					if (pbsStandbyMode.equals("GREEN")) {
						//SetAlarmforNtp(24);
					} else if (pbsStandbyMode.equals("FAST")) {
						SetAlarmforNtp(hour);
					}
					// Reno
					//updateNtpTime();
				}
			}

    };		

    private BroadcastReceiver TxtSyncReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.d(TAG, "TxtSyncReceiver - onReceive");
            String action = intent.getAction();
            Log.d(TAG, "action = " + action);
			if("org.droidtv.tv.txt.clock.complete".equals(action)){
				if(clockcalibstate == CLOCKCALIB_INPROGRESS){
					onClockCalibrationCompleted(0);
				}
			}
		}
};

	private boolean updateNtpTime() {
		if(!PlayTvUtils.isPbsMode() || !PlayTvUtils.isNeedSyncNetTime())
			return false;		

		ConnectivityManager connMgr = (ConnectivityManager)mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo netInfo = connMgr.getActiveNetworkInfo();
		sbyClockHandler.removeMessages(EVT_NTP_TIMEOUT);
		sbyClockHandler.sendMessageDelayed(sbyClockHandler.obtainMessage(EVT_NTP_TIMEOUT),
			(MAX_WAIT_TIME_SEC_CLOCK*1000));		
		sbyClockHandler.removeCallbacks(updateRunner);
		if(netInfo != null && netInfo.isConnectedOrConnecting() == true){
			Log.d(TAG, "start update ntp time");			
			sbyClockHandler.post(updateRunner);
			return true;
		}

		return false;
		
	}

	private void updateClockForNtp(){
	
		ConnectivityManager connMgr = (ConnectivityManager)mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo netInfo = connMgr.getActiveNetworkInfo();
		if(netInfo != null && netInfo.isConnectedOrConnecting() == true)
		{
			Log.i(TAG, "updateClockForNtp : check network is available");
			synchronized (mLock) {
			NtpTrustedTime tpvisionTime = NtpTrustedTime.getInstance(mContext);			        
			Log.d(TAG, "updateClockForNtp : start get ntp time");		
			if(tpvisionTime.forceRefresh()){
				long curTime = tpvisionTime.currentTimeMillis();
				Calendar cal = Calendar.getInstance();
				cal.setTimeInMillis(curTime);
				Date data = cal.getTime();
				SimpleDateFormat format = new SimpleDateFormat("dd/MMM/yyyy:HH:mm:ss");
				String localTimeStr = format.format(data) ;  
				Log.d(TAG, "updateClockForNtp : get ntp time: " + localTimeStr);			
				
				mTvclockmanager.SetTime( curTime,0,ITvClockManager.eClockSources.ECD, mColdStart);
				mColdStart = false;	

				if(mCallback!= null) {
					onActionCompleted(0);						
				}
			}	
			Log.d(TAG, "updateClockForNtp : end get ntp time");
			}
		}

	}


	
	private void OnChangePowerState(ITvPowerManager.PowerStates mPowerStatesSource, ITvPowerManager.PowerStates targetPowerStates) {
		
		if(!PlayTvUtils.isPbsMode() || !PlayTvUtils.isNeedSyncNetTime())
			return;
		Log.i(TAG, "OnChangePowerState: mPowerStatesSource = " + mPowerStatesSource + ", targetPowerStates = " + targetPowerStates);

		hour = (targetPowerStates == PowerStates.POWER_STATE_DDR_STANDBY) ? 24 : 1;

		if(mPowerStatesSource == PowerStates.POWER_STATE_BOOTING && targetPowerStates == PowerStates.POWER_STATE_FULL_SYSTEM_START) {
			String reason = SystemProperties.get("sys.droidtv.wakeup_reason");
			mColdStart = reason.equals("Cold Boot") ? true : false;
			Log.i(TAG,"OnChangePowerState : start get ntp time");
			updateNtpTime();	
		}		
		if(targetPowerStates == ITvPowerManager.PowerStates.POWER_STATE_SEMI_STANDBY ||
			targetPowerStates == ITvPowerManager.PowerStates.POWER_STATE_DDR_STANDBY ||
			targetPowerStates == ITvPowerManager.PowerStates.POWER_STATE_FULL_SYSTEM_START) {
			//acquireDSL();
			CancelAlarmForNtp();
			//SetAlarmforNtp(hour);
			// Reno 20160421 modifies time of sync cycle by ntp on different conditions
			String pbsStandbyMode = SystemProperties.get("persist.sys.pbs_standby_mode");
			Log.d(TAG, "PBS standby mode: " + pbsStandbyMode);
			if (pbsStandbyMode.equals("GREEN")) {
				//SetAlarmforNtp(24);
			} else if (pbsStandbyMode.equals("FAST")) {
				SetAlarmforNtp(hour);
			}
			// Reno
		}




	}

	private boolean acquireDSL() {
		synchronized(mLock){
			if(mShutdownLock==null) {
				mShutdownLock = mTvPowerManager.CreateShutdownLock(ITvPowerManager.PowerShutdownLocks.DONT_SHUTDOWN_LOCK, TAG);
			}		
			try {
				if(!mShutdownLock.isHeld()) {				
					mShutdownLock.acquire();
					Log.v(TAG,"acquireDSL called");
				}
				return true;
			}catch(IllegalStateException e) {
				Log.e(TAG,"Wrong state");
			}
		}
		return false;
	}

	private void releaseDSL() {
		synchronized(mLock){
			if (mShutdownLock != null && mShutdownLock.isHeld() == true) {
				mShutdownLock.release();	
				mShutdownLock = null;
				Log.v(TAG, "Released ShutDownLock");			
			}
		}
	}	
	private void SetAlarmforNtp(int hours) {
		
		try {		
			AlarmManager am = (AlarmManager) mContext
					.getSystemService(Context.ALARM_SERVICE);
			Intent i = new Intent(NTP_WAKEUP_ACTION);
			PendingIntent pi = PendingIntent.getBroadcast(mContext, 1, i, 0);

			Log.i(TAG,"SetAlarmforNtp()"+ (System.currentTimeMillis() + hours * 60 * 60 * 1000));
			
			am.set(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + hours * 60 * 60 * 1000, pi);
			
		} catch (Exception e) {
			 e.printStackTrace();
		}

	}    

	private void CancelAlarmForNtp() {
		Log.d(TAG,"CancelAlarmForNtp()");
		Intent intent = new Intent(NTP_WAKEUP_ACTION);	
		PendingIntent sender = PendingIntent
				.getBroadcast(mContext, 1, intent, 0);
		AlarmManager alarmManager = (AlarmManager) mContext
				.getSystemService(Context.ALARM_SERVICE);
		alarmManager.cancel(sender);
	}  	
	/*end:min.jiang add*/				
	public SSBYClientClockCalib(Context context) {
		mContext = context;
		sbyServiceHandler = (SemiStandbyService )context;
		Log.d(TAG,"created "+ id);
		sbyClockHandler = new PlayTvMsgHandler(PlayTvMsgHandler.getLooper("SSBYCLOCKCALIB"), this);
		clockcalibstate = CLOCKCALIB_READY;
		msbyCallbackclass = new SbyCallback();
		//mMediaplayerCallback = new MediaplayerCallbackClass();
		mainHandler = new Handler(context.getMainLooper());
		sbyClockHandler.sendEmptyMessage(EVT_CONNECT);
		/*begin:min.jiang add 2016-01-21, for ntp time*/		
		mClockSession = new ClockHandlerSession(mContext, this);
		mTvclockmanager = ITvClockManager.Instance.getInterface();
		mTvPowerManager = ITvPowerManager.Instance.getInterface();
		IntentFilter clockIntentFilter = new IntentFilter();
        clockIntentFilter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
		clockIntentFilter.addAction(TvIntent.ACTION_TV_POWER_STATE_CHANGE_BEGIN);		
        clockIntentFilter.addAction(NTP_WAKEUP_ACTION);
		mContext.registerReceiver(NtpSyncReceiver, clockIntentFilter);
		IntentFilter txtIntentFilter = new IntentFilter();
		txtIntentFilter.addAction("org.droidtv.tv.txt.clock.complete");
		mContext.registerReceiver(TxtSyncReceiver, txtIntentFilter);
        mTvSettingsManager.SetCallBacks(new NtpSettingsNotify(), new int[]{
            TvSettingsConstants.PBSMGR_PROPERTY_DNT_SOURCE
        });
		/*end:min.jiang add*/		
	}
	
	public void onActionCompleted(final int result) {
		Log.d(TAG,"onActionCompleted result" + result);

		sbyClockHandler.sendMessage(sbyClockHandler.obtainMessage(EVT_CANCELLED));
		if( (clockcalibstate==CLOCKCALIB_STOPPING) || 
			(clockcalibstate==CLOCKCALIB_INPROGRESS)) {
			clockcalibstate=CLOCKCALIB_READY;
				Runnable r = new Runnable() {
				@Override
				public void run() {
					mCallback.setActionCompleted(id);
				}
			};
			sbyClockHandler.post(r);
		}
	}
	

	private void onClockCalibrationCompleted(final int result) {
		Log.d(TAG, "onClockCalibrationCompleted" + result );
		
		mClockSession.closeSession();
		onActionCompleted(result);
	}
		
	private boolean isLastSelectionRestoreRequired() {
		int device = PlayTvUtils.getLastSelectedDevice(); 
		if((device==TvSettingsDefinitions.LastSelectedDeviceConstants.DVBTC) || 
			(device==TvSettingsDefinitions.LastSelectedDeviceConstants.DVBS)) {
			return false;
		}else {
			return true;
		}
	}
	
	private void startClockCalibration() {
		Log.d(TAG,"StartClockCalibration called");

		sbyClockHandler.sendMessageDelayed(sbyClockHandler.obtainMessage(EVT_TIMEOUT),
				(MAX_WAIT_TIME_SEC_CLOCK*1000));
		mActionMedium = PlayTvUtils.getCurrentMedium();
		
		int cid = PlayTvUtils.getCurrentChannel(mActionMedium);
        /*begin:min.jiang add 2015-07-15, for clock calibration*/
		int sourceType = -1;
        if(PlayTvUtils.isPbsMode()){
			
            mActionMedium = Medium.MEDIUM_INVALID;
            if(PlayTvUtils.isLiveChannelMode()){
				sbyClockHandler.removeCallbacks(updateRunner);
                cid = PlayTvUtils.getClockCalibrationcid();//tune to clock program channel        
                sourceType = ChannelFilter.getChannelFilterInstance(mContext).getSourceType(cid);
                Log.d(TAG, "start tune to clock channel cid: " + cid + ", sourceType: " + sourceType);    
            }else if(PlayTvUtils.isNeedSyncNetTime()){
            	Log.d(TAG, "start get ntp time");    
				
            	sbyClockHandler.removeCallbacks(updateRunner);
				updateClockForNtp();
				return;
            }else {
                clockcalibstate=CLOCKCALIB_READY;
                if(mCallback != null) {
                    mCallback.setActionCompleted(id);
                }
                return;                   
            }
			if(!SSBYUtils.isChannelInstalled(mContext, cid)) {
				cid = SSBYUtils.getFirstClockChannel(mContext);
				sourceType = ChannelFilter.getChannelFilterInstance(mContext).getSourceType(cid);
				PlayTvUtils.storeClockCalibrationcid(cid);
			}
			
            //-1: Not found, 0:DVBT, 1:DVBC, 2:DVBS
			if(sourceType != 0 && sourceType != 1 && sourceType != 2) {
				Log.d(TAG, "sourceType: (" + sourceType + ") is not available");
                clockcalibstate=CLOCKCALIB_READY;
                if(mCallback != null) {
                    mCallback.setActionCompleted(id);
                }
                return;     
			}
			
        }        
		/*end:min.jiang modify*/
		if(!SSBYUtils.isChannelInstalled(mContext, cid)){
			Log.d(TAG,"Last cid is not available ");
			cid = SSBYUtils.getFirstChannel(mContext, mActionMedium);
			if(cid!=-1){
				PlayTvUtils.storeCurrentChannel(TvContract.buildChannelUri(cid),mActionMedium,cid);
			}
		}
		
		if(cid==-1) {
			Log.d(TAG,"No channels found. selecting extension");
			sbyClockHandler.sendEmptyMessage(EVT_SELECTEXTN);
		} else {
			selectChannelforClkExtraction(cid);
		}
	}	
	
	private void selectChannelforClkExtraction(final int cid) {
				Uri uri = TvContract.buildChannelUri(cid);
        uri = PlayTvUtils.appendQueryParameter(uri, "clock_calibration", "1");
        mClockSession.createNewSession();
		mClockSession.tune(uri, null);
	}

	private void Release() {
		Log.d(TAG,"Release Called Flagging ACTIONRESULT_COMPLETED ");
		//unregisterMediaplayerCallbacks();
		mClockSession.closeSession();
		onActionCompleted(1);
	}
		
	@Override
	public void OnClockSetResult(Uri uri, int result) {//min.jiang modify 2015-07-09	
		switch(result) {
			case IClockHandlerCallBacks.RESULT_FAILED:
			case IClockHandlerCallBacks.RESULT_TIMEOUT:
				onClockCalibrationCompleted(0);
				break;
			case IClockHandlerCallBacks.RESULT_SUCCESS_TDT:
				Log.d(TAG,"ClockCalib done. Flagging ACTIONRESULT_COMPLETED ");
				onClockCalibrationCompleted(0);
				break;
			case IClockHandlerCallBacks.RESULT_SUCCESS_TOT:
				Log.d(TAG,"ClockCalib done. Flagging ACTIONRESULT_COMPLETED ");
				onClockCalibrationCompleted(0);
				break;
		}
	}	
	
	@Override
	public boolean handleMessage(Message arg) {
		switch(arg.what) {
			case EVT_TIMEOUT:
				OnClockSetResult(null, IClockHandlerCallBacks.RESULT_TIMEOUT);//min.jiang modify 2015-07-09	
				break;
			case EVT_CANCELLED:
				if(sbyClockHandler.hasMessages(EVT_TIMEOUT)){
					sbyClockHandler.removeMessages(EVT_TIMEOUT);
					Log.d(TAG,"Message removed");
				}
				break;
			case EVT_SELECTEXTN:
				if(!mRestoreLastSelection) {
					Log.d(TAG,"Change to HDMI");
					PlayTvUtils.storeLastSelectedDevice(TvSettingsDefinitions.LastSelectedDeviceConstants.HDMI1);
				}
				onClockCalibrationCompleted(0);
				break;
			case EVT_CONNECT:
				bindtoSSBYService();
				break;
			case EVT_CONNECTED:
				mCallback.registerSemiStandbyAction(id,msbyCallbackclass);
				break;
			case EVT_NTP_TIMEOUT://min.jiang add 2016-01-22 for ntp time out.
				Log.d(TAG, "get ntp time out");
				//releaseDSL();
				break;
			default:
				break;
		}
		return false;
	}
	
	private void bindtoSSBYService() {
		svcConnect svcobj = new svcConnect();
		Intent intent = new Intent(TvIntent.ACTION_SERVICE_SBYSERVICE);
		mContext.getApplicationContext().bindService(intent,svcobj, Context.BIND_AUTO_CREATE);
	}
	
	private class svcConnect implements ServiceConnection {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			mCallback = ITvSemiStandbyControl.Instance.asInterface(service);
			Log.d(TAG,"onServiceConnected ");
			sbyClockHandler.sendEmptyMessage(EVT_CONNECTED);
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d(TAG,"onServiceDisconnected ");
		}
	}
	
	private class SbyCallback extends ITvSemiStandbyCallback {
		
		public void onStartAction() {
			Log.d(TAG,"onStartAction called");

			if(clockcalibstate==CLOCKCALIB_READY) {
				clockcalibstate=CLOCKCALIB_INPROGRESS;
				mRestoreLastSelection = isLastSelectionRestoreRequired();
				Runnable r = new Runnable() {
					@Override
					public void run() {
						startClockCalibration();
						Log.d(TAG,"startClockCalibration done");
					}
				};
				sbyClockHandler.post(r);
			}
		}
		
		public void onStopAction() {
			Log.d(TAG,"onStopAction called");
			if(clockcalibstate==CLOCKCALIB_INPROGRESS) {
				clockcalibstate=CLOCKCALIB_STOPPING;
				Runnable r = new Runnable() {
					@Override
					public void run() {
						Log.d(TAG,"Action is already ongoing on this calling Stop");
						Release();
						Log.d(TAG,"release done");
					}
				};
				sbyClockHandler.post(r);
			}	
		}
	}
	

			// TODO Auto-generated method stub
			

			// TODO Auto-generated method stub
			

			// TODO Auto-generated method stub
			


			// TODO Auto-generated method stub
			

			// TODO Auto-generated method stub
			

			// TODO Auto-generated method stub
			

			// TODO Auto-generated method stub
			

			// TODO Auto-generated method stub
			

			// TODO Auto-generated method stub
			
		
	
}
