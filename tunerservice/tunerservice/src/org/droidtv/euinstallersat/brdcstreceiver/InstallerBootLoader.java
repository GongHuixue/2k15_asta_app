package org.droidtv.euinstallersat.brdcstreceiver;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.service.SatInstallerService;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.logger.ILogger;
import org.droidtv.tv.logger.ILogger.TypeOfTunersInstalled;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.database.Cursor;
import android.net.ConnectivityManager;
import android.os.AsyncTask;
import android.os.IBinder;
import android.util.Log;

public class InstallerBootLoader extends BroadcastReceiver
{
    private static final String TAG = InstallerBootLoader.class.getName();
    private Context ctx;
    protected static ILogger m_binder = null;
    private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
    private HandleBroadcastIntent asyncHandlerTask;
    
    private ServiceConnection m_servConnection = new ServiceConnection()
	{

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
		}
	};

    
    @Override
    public void onReceive(Context context, Intent intent)
    {
        Log.d(TAG, "onReceive intent " + intent);

        ctx = context;
        if (null == intent)
        {
            Log.d(TAG, "Error: Intent is null!");
            return;
        }
        
        final String action = intent.getAction();
        if (null == action){
            Log.d(TAG, "Error: Intent Action is null!" );
            return;
        }else if (action.equals(TvIntent.ACTION_POWER_BOOT_COMPLETED)){
            Log.d(TAG, "ACTION_BOOT_COMPLETED Recieved" );
            // startPowerUpSequence(context);
           
            Log.d(TAG, "Start EuinstallerService" );
            // start EuinstallerTC service
            Intent serviceIntent = new Intent(context, SatInstallerService.class);
            ctx.startService(serviceIntent); 
			// Logging is done in TC bootloader in single query
			//asyncInitTask = new InitLoggingTask();
			//asyncInitTask.execute("");
            return;
        } else if (action.equalsIgnoreCase(TvIntent.ACTION_TV_POWER_STATE_CHANGE_BEGIN)) {
			Log.d(TAG, "ACTION_TV_POWER_STATE_CHANGE_BEGIN");
			PowerStates fromPowerStates = (PowerStates) intent.getSerializableExtra(TvIntent.SOURCE_TV_POWER_MODE);
			PowerStates toPowerStates = (PowerStates) intent.getSerializableExtra(TvIntent.TARGET_TV_POWER_MODE);
			Log.i(TAG, "Received Powerstatechange Start from " + fromPowerStates + " to " + toPowerStates);
		} else if (action.equalsIgnoreCase(TvIntent.ACTION_TV_POWER_STATE_CHANGED)) {
			Log.d(TAG, "ACTION_TV_POWER_STATE_CHANGED");
			PowerStates fromPowerStates = (PowerStates) intent.getSerializableExtra(TvIntent.SOURCE_TV_POWER_MODE);
			PowerStates toPowerStates = (PowerStates) intent.getSerializableExtra(TvIntent.TARGET_TV_POWER_MODE);
			Log.i(TAG, "Received Powerstatechange End from " + fromPowerStates + " to " + toPowerStates);
			nwrap.handlePowerStateChange(fromPowerStates, toPowerStates);
		} /* SAT-IP is not part of MTK 2k15. Hence below removing the CONNECTIVITY_ACTION receiver */
    }
    
    class HandleBroadcastIntent extends AsyncTask<String, Void, String> {

		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			// leave empty as no changes in UI required
			Log.d(TAG, "onPostExecute exit");
		}

		@Override
		protected String doInBackground(String... params) {
		//	Log.d(TAG, "doInBackground params: " + params[0]);
			if ((params[0]).equalsIgnoreCase(ConnectivityManager.CONNECTIVITY_ACTION)) {
				nwrap.networkChangeDetected();
			}
			return params[0];
		}
	}
	class InitLoggingTask extends AsyncTask<String, Void, String> {

		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			// leave empty as no changes in UI required
		//	Log.d(TAG, "onPostExecute exit");
		}

		@Override
		protected String doInBackground(String... params) {
		//	Log.d(TAG, "doInBackground params: " + params[0]);
			bindToLoggingService();
			return params[0];
		}
	}

	public void bindToLoggingService() {
		Intent l_intent = new Intent();
		l_intent.setAction("org.droidtv.tv.intent.action.START_LOGGER");
		try {
			boolean serviceBound = ctx.getApplicationContext().bindService(l_intent, m_servConnection, Context.BIND_AUTO_CREATE);
			Log.d(TAG, " bindToLoggingService, servicebound=" + serviceBound);
		} catch (SecurityException e) {
			Log.d(TAG, "bindToLoggingService caught Security Exception : " + "" + e.getLocalizedMessage());
		} catch (Exception e) {
			Log.d(TAG, "bindToLoggingService caught exception :: Could bind to service : " + "" + e.getLocalizedMessage());
		}
	}

	private class CulLogTask extends AsyncTask<Void, Void, Void> {

		@Override
		protected Void doInBackground(Void... arg0) {
			int l_numChannels = getNoOfInstalledChannels();
			if (m_binder != null) {
				Log.d(TAG, "Logging " + l_numChannels + " for satellite");
				TypeOfTunersInstalled l_tunerType = new ILogger.TypeOfTunersInstalled();
				l_tunerType.amt_channels = l_numChannels;
				l_tunerType.delivery_system = ILogger.TypeOfTunersInstalled.DeliverySystem.DVBS;
				m_binder.Log(l_tunerType);
			}
			return null;
		}
		
		private int getNoOfInstalledChannels() {
			int l_presetCount = 0;

			try {
				// query Satellite Preset Table
				String[] CHANNEL_COLUMNS = { IChannelContract.C_PRESET_ID };

				Cursor satCursor = ctx.getContentResolver().query(IChannelContract.CONTENT_URI_SatChannelMap, CHANNEL_COLUMNS, null, null, null);
				Log.i(TAG, "satCursor:" + satCursor);
				if (satCursor != null) {
					l_presetCount = satCursor.getCount();
					satCursor.close();
				}

			} catch (Exception e) {
				Log.e(TAG, "Error TVContentProvider  " + e);
			}

			Log.d(TAG, "getNoOfInstalledChannels() " + l_presetCount);
			return l_presetCount;
		}

	}
}
