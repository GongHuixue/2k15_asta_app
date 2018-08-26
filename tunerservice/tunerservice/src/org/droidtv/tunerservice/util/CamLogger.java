package org.droidtv.tunerservice.util;

import org.droidtv.tv.logger.ILogger;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.IBinder;
import android.util.Log;
import org.droidtv.tv.media.ITvMediaCI;

public class CamLogger {
	
	private static final String TAG = CamLogger.class.getSimpleName();
	private static CamLogger mCamLogger;
	private ILogger mBinder;
	private ILogger.PeriPheralUsage mPeriPheralUsage = null;
	private CamLogger(){
	}
	
	public static CamLogger getInstance(){
		if(mCamLogger == null){
			mCamLogger = new CamLogger();
		}
		return mCamLogger;
	}
	
	public void bindToLoggingService(Context pContext) {

		Intent i = new Intent();
		i.setAction("org.droidtv.tv.intent.action.START_LOGGER");
		try{
			PackageManager mPackageManager = pContext.getPackageManager();
			ResolveInfo mResolveInfo = mPackageManager.resolveService(i, 0);			
			if(mResolveInfo != null) {
				i.setClassName(mResolveInfo.serviceInfo.packageName, mResolveInfo.serviceInfo.name);				
				boolean serviceBound =pContext.getApplicationContext().bindService(i, conn, Context.BIND_AUTO_CREATE);
				Log.d(TAG," in bindToNetvLoggerService  after binding call, servicebound="+serviceBound);
			}else {
				Log.d(TAG, "org.droidtv.tv.intent.action.START_LOGGER: not able to resolve ");
			}
		}catch(SecurityException e){
			Log.d(TAG, "Caught Security Exception : " + ""+e.getLocalizedMessage());
		}catch(Exception e){
			Log.d(TAG , "Caught exception :: Could bind to service : " +""+e.getLocalizedMessage());
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
	
	public void logCamUsage(int peripheralId, boolean isConnected) {
		Log.d(TAG, "logCamUsage called with peripheralId: "+peripheralId +", isConnected: "+isConnected);
		mPeriPheralUsage = new ILogger.PeriPheralUsage();
		if(peripheralId == ITvMediaCI.SLOT0){
			mPeriPheralUsage.connector = ILogger.PeriPheralUsage.Connector.CAM_1;
		}
		else if(peripheralId == ITvMediaCI.SLOT1){
			mPeriPheralUsage.connector = ILogger.PeriPheralUsage.Connector.CAM_2;
		}
			
		if(isConnected) {
			mPeriPheralUsage.state = ILogger.PeriPheralUsage.State.CONNECTED;
		} else {
			mPeriPheralUsage.state = ILogger.PeriPheralUsage.State.DISCONNECTED;
		}
		
		if( mBinder != null ) {
			mBinder.Log(mPeriPheralUsage);
		}else{
			Log.d(TAG, "Logging binder is NULL ");
		}
	}
	
	private void logDefaultPeripheralData() {
		mPeriPheralUsage.product_type = ILogger.PeriPheralUsage.ProductType.OTHER_PERIPHERAL;
		mPeriPheralUsage.product_id = "";
		mPeriPheralUsage.product_name = "";
		mPeriPheralUsage.vendor_id = "";
		mPeriPheralUsage.vendor_name = "";
		mPeriPheralUsage.given_name = "";
	}
	
}
