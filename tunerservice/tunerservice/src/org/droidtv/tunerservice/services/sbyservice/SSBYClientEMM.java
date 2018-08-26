package org.droidtv.tunerservice.services.sbyservice;

import java.util.Calendar;
import java.util.Map;

import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.PlayTvMsgHandler;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl.ITvSemiStandbyCallback;

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

public class SSBYClientEMM implements Callback{
	
	private final static int MSG_DONE		= 1;
	private final static int MSG_ABORTED 	= 2;
	private final static int MSG_INIT		= 3;
	private final static int MSG_CONNECTED	= 4;
	
	private final static int INIT 			= 0;
	private final static int INPROGRESS 	= 1;
	private final static int STOPPING 		= 2;
		
	public static final String TAG = "SSBYEMM";
	
	private static final int CABLE_TIMEOUT = 30*60*1000; //30 minutes
		
	private Medium cMedium = Medium.MEDIUM_CABLE;
	private PlayTvMsgHandler emmHandler = null;
	private int emmState = INIT; 
	private PlayTvMediaPlayer playtvmpl = null;
	private ITvSemiStandbyControl mCallback=null;
	private Context mContext = null;
	private final int id = ITvSemiStandbyControl.ACTION_EMM_AQUISITION;
	private SbyCallback msbyCallbackclass = null;
	private static final int ACTIONHOUR = 6;
	private Handler mainHandler = null;
	
	public SSBYClientEMM(Context context) {
		mContext = context;
		emmHandler = new PlayTvMsgHandler(PlayTvMsgHandler.getLooper("SSBYEMM"), this);
		emmState = INIT;
		msbyCallbackclass = new SbyCallback();
		emmHandler.sendEmptyMessage(MSG_INIT);
		mainHandler = new Handler(context.getMainLooper());
	}
		
	public void onActionCompleted(int id, int result) {
		if((emmState==INPROGRESS) || (emmState==STOPPING)) {
			emmState = INIT;
			if(mCallback!=null) {
				mCallback.setActionCompleted(this.id);
			}
		}
	}
	
	private void doAction() {
		Log.d(TAG,"doAction: called");
		Runnable r = new Runnable() {
			@Override
			public void run() {
				int cid = SSBYUtils.getFirstChannel(mContext,Medium.MEDIUM_CABLE);
				if(cid!=-1) {
					int presetnumber =-1;
					Log.d(TAG,"requestMediaplayer called");
					Uri uri = TvContract.buildChannelUri(cid);
					Map<String, String> headers	= TvURIHelper.getUriHeaders(mContext,uri);
					if((headers != null) && (headers.get(TvHeaders.MEDIUM) != null)) {				
						presetnumber = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
						PlayTVMediaPlayerFactory mplfactory =  PlayTVMediaPlayerFactory.getInstance();
						if(mplfactory!=null) {
							playtvmpl = mplfactory.getMPLInstance(mContext,
							PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY,
							cMedium, presetnumber);
							if(playtvmpl!=null) {
								playtvmpl.PlayChannel(uri, headers);	
								emmHandler.sendEmptyMessageDelayed(MSG_DONE, CABLE_TIMEOUT);
								Log.d(TAG,"Waiting for EMM for " + (CABLE_TIMEOUT/1000) + " seconds");
								return;
							}
						}
					}
				}
				emmHandler.sendEmptyMessage(MSG_DONE);
			}
		};
		mainHandler.post(r);
		Log.d(TAG,"doAction: done");
	}

	@Override
	public boolean handleMessage(Message msg) {
		switch(msg.what) {
			case MSG_INIT:
				bindtoSSBYService();	
				break;
			case MSG_CONNECTED:
				mCallback.registerSemiStandbyAction(id,msbyCallbackclass);
				break;
			case MSG_DONE:
				onActionCompleted(id,0);
				break;
			case MSG_ABORTED:
				onActionCompleted(id,1);
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

	private boolean isEMMUpdateRequired() {
		boolean emmRequired = false;
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		if(globalSettings.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0) == 1) {
			if(globalSettings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0,0)
					==TvSettingsDefinitions.InstallationCountryConstants.SWEDEN) {
				emmRequired= true;
			}
			else if(globalSettings.getInt(TvSettingsConstants.OPERATORCABLE, 0, 0)==
					TvSettingsDefinitions.OperatorCableConstants.UPC) {
				emmRequired= true;
			}
		}
		if(emmRequired){
			Log.d(TAG,"EMMUpdate is required");
		}
		return emmRequired;
	}
			
	private class svcConnect implements ServiceConnection {
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			mCallback = ITvSemiStandbyControl.Instance.asInterface(service);
			emmHandler.sendEmptyMessage(MSG_CONNECTED);
		}
		@Override
		public void onServiceDisconnected(ComponentName name) {
			
		}
	}
	
	private class SbyCallback extends ITvSemiStandbyCallback {
		
		public void onStartAction() {
			Log.d(TAG,"onStartAction called");
			if(emmState==INIT) {
				emmState = INPROGRESS;
				doAction();
			}
		}
		
		public void onStopAction() {
			Log.d(TAG,"onStopAction called");
			if(emmState==INPROGRESS) {
				emmState = STOPPING;
				if(emmHandler.hasMessages(MSG_DONE)) {
					emmHandler.removeMessages(MSG_DONE);
				}
				emmHandler.sendEmptyMessage(MSG_ABORTED);
			}
		}
		
		public long onGetNextAlarm(){ 
			long timeinmsecs = 0;
			if(isEMMUpdateRequired()){
				Calendar alarmTime = Calendar.getInstance();
				int currenthour = alarmTime.get(Calendar.HOUR_OF_DAY);
				if(currenthour>=ACTIONHOUR) {
					alarmTime.add(Calendar.DAY_OF_MONTH, 1);
				}
				alarmTime.set(Calendar.HOUR_OF_DAY, ACTIONHOUR);
				alarmTime.set(Calendar.MINUTE, 0);
				alarmTime.set(Calendar.SECOND, 0);
				alarmTime.set(Calendar.MILLISECOND, 0);
				timeinmsecs = alarmTime.getTimeInMillis();
			}
			return timeinmsecs;
		}
	}
}
