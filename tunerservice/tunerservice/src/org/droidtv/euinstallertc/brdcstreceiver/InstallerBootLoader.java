package org.droidtv.euinstallertc.brdcstreceiver;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.service.EuInstallerService;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.logger.ILogger;
import org.droidtv.tv.logger.ILogger.TypeOfTunersInstalled;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.util.IIntKeyValueables;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.database.Cursor;
import android.os.AsyncTask;
import android.os.IBinder;
import android.util.Log;
import android.os.Handler;

import android.media.tv.TvContract.Channels;
import android.media.tv.TvContract;

public class InstallerBootLoader extends BroadcastReceiver {
	private static final String TAG = InstallerBootLoader.class.getName();
	private Context ctx;

	protected static ILogger m_binder = null;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private InitLoggingTask asyncInitTask;
	private Handler mhandler = null;

	private ServiceConnection m_servConnection = new ServiceConnection() {
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG, " onServiceConnected callback received");
			m_binder = ILogger.Instance.asInterface(service);
			CulLogTask l_culLog = new CulLogTask();
			l_culLog.execute();
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d(TAG, "received onServicedisconnected for LoggingHelper, shut this service");
			m_binder = null;
			reBind();
		}
		
		private void reBind() {
			Log.d(TAG,"reBind called");
			Runnable r = new Runnable() {
				@Override
				public void run() {
					Log.d(TAG,"Reconnecting to UsageLogger");
					bindToLoggingService();					
				}
			};
			mhandler.post(r);
		}

	};

	@Override
	public void onReceive(Context context, Intent intent) {
		Log.d(TAG, "onReceive intent " + intent);

		ctx = context;
		if (null == intent) {
			Log.d(TAG, "Error: Intent is null!");
			return;
		}

		final String action = intent.getAction();
		if (null == action) {
			Log.d(TAG, "Error: Intent Action is null!");
			return;
		} else if (action.equals(TvIntent.ACTION_POWER_BOOT_COMPLETED)) {
			Log.d(TAG, "ACTION_BOOT_COMPLETED Recieved");
			// startPowerUpSequence(context);
						
//			Log.d(TAG, "Start EuinstallerService");
			// start EuinstallerTC service
			Intent serviceIntent = new Intent(context, EuInstallerService.class);
			ctx.startService(serviceIntent);
			mhandler = new Handler();
			asyncInitTask = new InitLoggingTask();
			asyncInitTask.execute("");
			return;
		} else if (action.equalsIgnoreCase(TvIntent.ACTION_TV_POWER_STATE_CHANGE_BEGIN)) {
			Log.d(TAG, "ACTION_TV_POWER_STATE_CHANGE_BEGIN");
			PowerStates fromPowerStates = (PowerStates) intent.getSerializableExtra(TvIntent.SOURCE_TV_POWER_MODE);
			PowerStates toPowerStates = (PowerStates) intent.getSerializableExtra(TvIntent.TARGET_TV_POWER_MODE);
			Log.i(TAG, "Received Powerstatechange Start from "
					+ fromPowerStates + " to " + toPowerStates);
		} else if (action.equalsIgnoreCase(TvIntent.ACTION_TV_POWER_STATE_CHANGED)) {
			Log.d(TAG, "ACTION_TV_POWER_STATE_CHANGED");
			PowerStates fromPowerStates = (PowerStates) intent.getSerializableExtra(TvIntent.SOURCE_TV_POWER_MODE);
			PowerStates toPowerStates = (PowerStates) intent.getSerializableExtra(TvIntent.TARGET_TV_POWER_MODE);
			Log.i(TAG, "Received Powerstatechange End from " + fromPowerStates
					+ " to " + toPowerStates);
			
			nwrap.handlePowerStateChange(fromPowerStates, toPowerStates);
		} else if(action.equalsIgnoreCase("org.droidtv.settings.FACTORY_RESET")){
			Log.d(TAG, "org.droidtv.settings.FACTORY_RESET");
			nwrap.handleFactoryReset();
		}
		/*For clear data*/
		Log.d(TAG, "star check intent " + intent);
		if(action.equalsIgnoreCase("org.droidtv.intent.action.settings.ClearData")){
			Log.d(TAG, "org.droidtv.intent.action.settings.ClearData");
			Log.d(TAG, "LoadTvProviderData ClearData");
			nwrap.LoadTvProviderData();
		}
		/*For OPtion code*/
		Log.d(TAG, "star check intent " + intent);
		if(action.equalsIgnoreCase("org.droidtv.intent.action.settings.OptionCode")){
			Log.d(TAG, "org.droidtv.intent.action.settings.OptionCode");
			nwrap.OptionCoder_ExternalSource();
		}
	}

	class InitLoggingTask extends AsyncTask<String, Void, String> {

		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			// leave empty as no changes in UI required
//			Log.d(TAG, "onPostExecute exit");
		}

		@Override
		protected String doInBackground(String... params) {
			//Log.d(TAG, "doInBackground params: " + params[0]);
			bindToLoggingService();
			return params[0];
		}
	}
	
	public void bindToLoggingService() {
			
		Intent intent = new Intent();
		intent.setAction("org.droidtv.tv.intent.action.START_LOGGER");
		try{
			PackageManager mPackageManager = ctx.getPackageManager();
			ResolveInfo mResolveInfo = mPackageManager.resolveService(intent, 0);			
			if(mResolveInfo != null) {
				intent.setClassName(mResolveInfo.serviceInfo.packageName, mResolveInfo.serviceInfo.name);
				boolean serviceBound = ctx.getApplicationContext().bindService(intent, m_servConnection, Context.BIND_AUTO_CREATE);
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

	private class CulLogTask extends AsyncTask<Void, Void, Void> {

		@Override
		protected Void doInBackground(Void... arg0) {
			if (m_binder != null) {
				logNoOfInstalledChannels();
			}
			return null;
		}
		
		public void logNoOfInstalledChannels(){
//			Log.d(TAG,"logNoOfInstalledChannels2 ");
			int versionNumber = 0;
			byte[]  temp;
			int channelCount = 0;
			String source_uri;
			IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
			// SELECT version_number, COUNT(version_number) AS CHANNEL_COUNT FROM channels GROUP BY (version_number);
			
			String[] mProjection = { 
					TvContract.Channels.COLUMN_VERSION_NUMBER, //version_number
					Channels.COLUMN_INTERNAL_PROVIDER_DATA,}; 
			
			Cursor lRetCursor = ctx.getContentResolver().query(
					Channels.CONTENT_URI, // Content URI
					mProjection, // select 
					null, 
					null,
					null);
			
			TypeOfTunersInstalled typeOfTuner;
			boolean ifDVBT = false; int channelCountDVBT = 0;
			boolean ifDVBC = false; int channelCountDVBC = 0;
			boolean ifDVBS = false; int channelCountDVBS = 0;
			boolean ifNone=false; int channelCountNone = 0;
			boolean ifIPTVMulticast=false; int channelCountIPTVMulticast = 0;
			boolean ifIPTVUnicast=false; int channelCountIPTVUnicast = 0;
			boolean ifVODRTSP=false; int channelCountVODRTSP = 0;
			boolean ifOthers=false; int channelCountOthers = 0;
			
			if( null!= lRetCursor){
				try{
					// retrive data
					while(lRetCursor.moveToNext()){
						// get t/c/sat
						versionNumber = lRetCursor.getInt(0);
						keyvalues.setBlob(lRetCursor.getBlob(1));
					
				/*		Log.d(TAG, "versionNumber: " + versionNumber +
								" channelCount: " + channelCount);*/
						
						if(versionNumber == 0){ // antenna
							ifDVBT = true;
							channelCountDVBT++;
						}else if(versionNumber == 1){ // cable
							ifDVBC = true;
							channelCountDVBC++;
						}else if((versionNumber == 2) || (versionNumber == 3) || (versionNumber == 4) || (versionNumber == 5)){ // satellite lnb's
							ifDVBS = true;
							channelCountDVBS++;
						}else if(versionNumber == 11){ //IP channel
							source_uri = keyvalues.getString(ITvContractExtras.C_URI_BLOB);
							if( source_uri.contains("unicast") )
							{
								ifIPTVUnicast = true;
								channelCountIPTVUnicast++;
							}else if( source_uri.contains("multicast") )
							{
								ifIPTVMulticast = true;
								channelCountIPTVMulticast++;
							} else if( source_uri.contains("rtsp") )
							{
								ifVODRTSP = true;
								channelCountVODRTSP++;
							}  
						}
						else{
							ifOthers = true;
							channelCountOthers++;
						}
					}
				}catch(Exception ex){
					Log.d(TAG, "Caught exception: " + ex.getMessage());
				}
				finally
				{
					lRetCursor.close();
  				    lRetCursor=null;
				}
				// write to event logger
				if(ifDVBT){
					Log.d(TAG, "dvbt " + channelCountDVBT);
					typeOfTuner = new ILogger.TypeOfTunersInstalled();
					typeOfTuner.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.DVBT;
					typeOfTuner.amt_channels = channelCountDVBT;
					if(m_binder != null){
						m_binder.Log(typeOfTuner);
					}
				}
				
				if(ifDVBC){
					Log.d(TAG, "dvbc " + channelCountDVBC);
					typeOfTuner = new ILogger.TypeOfTunersInstalled();
					typeOfTuner.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.DVBC;
					typeOfTuner.amt_channels = channelCountDVBC;
					if(m_binder != null){
						m_binder.Log(typeOfTuner);
					}
				}
				
				if(ifDVBS){
					Log.d(TAG, "dvbs " + channelCountDVBS);
					typeOfTuner = new ILogger.TypeOfTunersInstalled();
					typeOfTuner.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.DVBS;
					typeOfTuner.amt_channels = channelCountDVBS;
					if(m_binder != null){
						m_binder.Log(typeOfTuner);
					}
				}
				if(ifNone){
					Log.d(TAG, "none " + channelCountNone);
					typeOfTuner = new ILogger.TypeOfTunersInstalled();
					typeOfTuner.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.NONE;
					typeOfTuner.amt_channels = channelCountNone;
					if(m_binder != null){
						m_binder.Log(typeOfTuner);
					}
				}
				
				if(ifIPTVMulticast){
					Log.d(TAG, "IPTV multicast " + channelCountIPTVMulticast);
					typeOfTuner = new ILogger.TypeOfTunersInstalled();
					typeOfTuner.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.IPTV_MULTICAST;
					typeOfTuner.amt_channels = channelCountIPTVMulticast;
					if(m_binder != null){
						m_binder.Log(typeOfTuner);
					}
				}
				
				if(ifIPTVUnicast){
					Log.d(TAG, "IPTV unicast " + channelCountIPTVUnicast);
					typeOfTuner = new ILogger.TypeOfTunersInstalled();
					typeOfTuner.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.IPTV_UNICAST;
					typeOfTuner.amt_channels = channelCountIPTVUnicast;
					if(m_binder != null){
						m_binder.Log(typeOfTuner);
					}
				}
				if(ifVODRTSP){
					Log.d(TAG, "	VOD " + channelCountVODRTSP);
					typeOfTuner = new ILogger.TypeOfTunersInstalled();
					typeOfTuner.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.VOD_RTSP;
					typeOfTuner.amt_channels =channelCountVODRTSP;
					if(m_binder != null){
						m_binder.Log(typeOfTuner);
					}
				}
				
				if(ifOthers){
					Log.d(TAG, "other " + channelCountOthers);
					typeOfTuner = new ILogger.TypeOfTunersInstalled();
					typeOfTuner.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.OTHERS;
					typeOfTuner.amt_channels = channelCountOthers;
					if(m_binder != null){
						m_binder.Log(typeOfTuner);
					}
				}					
			}	
		}

	}

}
