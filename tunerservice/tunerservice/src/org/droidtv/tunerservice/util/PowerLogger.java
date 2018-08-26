package org.droidtv.tunerservice.util;

import org.droidtv.tv.logger.ILogger;
import org.droidtv.tv.logger.ILogger.PowerStateTransition;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.IBinder;
import android.util.Log;


public class PowerLogger {

	private static final String TAG = PowerLogger.class.getSimpleName();
	private static PowerLogger mPowerLogger;
	private ILogger mBinder;
	private ILogger.PowerStateTransition mPowerLog;
	private PowerLogger(){
	}

	public static PowerLogger getInstance(){
						Log.d(TAG," in getInstance" );
		if(mPowerLogger == null){
			mPowerLogger = new PowerLogger();
		}
		return mPowerLogger;
	}

	public void bindToLoggingService(Context pContext) {

		Intent logIntent = new Intent();
		logIntent.setAction("org.droidtv.tv.intent.action.START_LOGGER");
		try{
			PackageManager mPackageManager = pContext.getPackageManager();
			ResolveInfo mResolveInfo = mPackageManager.resolveService(logIntent, 0);		
			if(mResolveInfo != null) {
				logIntent.setClassName(mResolveInfo.serviceInfo.packageName, mResolveInfo.serviceInfo.name);
				boolean serviceBound =pContext.getApplicationContext().bindService(logIntent, conn, Context.BIND_AUTO_CREATE);
				Log.d(TAG," in bindToNetvLoggerService  after binding call, servicebound="+serviceBound);
			}else {
				Log.e(TAG, "org.droidtv.tv.intent.action.START_LOGGER: not able to resolve ");
			}
		}catch(SecurityException e){
			Log.e(TAG, "Caught Security Exception : " + ""+e.getLocalizedMessage());
						Log.e(TAG, "Failed to bind to CUL service "+e.toString() );
		}catch(Exception e){
			Log.e(TAG , "Caught exception :: Could bind to service : " +""+e.getLocalizedMessage());
		}
	}

	public ServiceConnection conn = new ServiceConnection(){

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG," onServiceConnected callback received");
			mBinder = ILogger.Instance.asInterface(service);
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d(TAG,"received onServicedisconnected for LoggingHelper, shut this service");
			mBinder = null;
		}
	};

	private ILogger.PowerStateTransition.PowerState translatePowerState(PowerStates tvPowerState){
		ILogger.PowerStateTransition.PowerState loggerPowerState;

		/*TVPower.PowerStates: POWER_STATE_UNKNOWN, POWER_STATE_BOOTING, POWER_STATE_BOOT_COMPLETED, POWER_STATE_FULL_SYSTEM_START, 
					POWER_STATE_SEMI_STANDBY, POWER_STATE_DDR_STANDBY, POWER_STATE_STANDBY, POWER_STATE_VIRTUAL_POWER_OFF*/
		/*PowerStateTranstition.PowerState: OFF, STANDBY, SEMI_STANDBY, ON*/

		//Log.d(TAG,"translatePowerState:tvPowerState"+tvPowerState);
		switch(tvPowerState){
			case POWER_STATE_BOOTING:
			case POWER_STATE_BOOT_COMPLETED:
			case POWER_STATE_FULL_SYSTEM_START:
				loggerPowerState = ILogger.PowerStateTransition.PowerState.ON;
				break;
			case POWER_STATE_SEMI_STANDBY:
				loggerPowerState = ILogger.PowerStateTransition.PowerState.SEMI_STANDBY;
				break;
			case POWER_STATE_DDR_STANDBY:
			case POWER_STATE_STANDBY:
				loggerPowerState = ILogger.PowerStateTransition.PowerState.STANDBY;
				break;
			case POWER_STATE_VIRTUAL_POWER_OFF:
				loggerPowerState = ILogger.PowerStateTransition.PowerState.OFF;
				break;
			case POWER_STATE_UNKNOWN:
			default:
				loggerPowerState = ILogger.PowerStateTransition.PowerState.OFF;
			}
		//Log.d(TAG,"translatePowerState:loggerPowerState"+loggerPowerState);
		return loggerPowerState;
		}

	public void logPowerState(PowerStates powerState, ILogger.PowerStateTransition.Reason powerReason ){

		//Log.d(TAG,"logPowerState: PowerState:"+powerState+", Reason: "+powerReason);
		mPowerLog = new ILogger.PowerStateTransition();
		
		mPowerLog.power_state = translatePowerState(powerState);
		mPowerLog.reason = powerReason;

		//Log.d(TAG,"logPowerState:powerLog.powerState"+mPowerLog.power_state+"powerLog.reason"+mPowerLog.reason);
		if(mBinder != null){
			//Log.d(TAG,"mBinder available, PowerState Logged");
			mBinder.Log(mPowerLog);
			}
		else{
			Log.e(TAG,"Binder NOT available, can't log PowerState");
			}
		}
}

