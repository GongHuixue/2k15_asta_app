package org.droidtv.tunerservice;

import org.droidtv.tv.contextualhelp.IHelpContext;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;

import android.content.ActivityNotFoundException;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.IBinder;
import android.util.Log;

public final class TunerServiceHelpContext {

	//Constants:
	/* Level 1 */
	public final static String NA = "NA";
	public final String WatchTv = "WatchTv";
	public final String WatchSatellite = "WatchSatellite";

		/* Level 2 */
	public  final String Playstate = "Playstate";
	public  final String Options = "Options";
	public  final String universal_access = "universal_access";
	public  final String key_beep = "key_beep";
	public  final String voice_guidance = "voice_guidance";
	public  final String hearing_impaired = "hearing_impaired";
	public  final String audio_description_menu = "audio_description_menu";
	public  final String audio_description = "audio_description";
	public  final String mixed_volume = "mixed_volume";
	public  final String video_selection = "video_selection";
	public  final String subtitles = "subtitles";
	public  final String subtitle_language = "subtitle_language";
	public  final String audio_language = "audio_language";
	public  final String dual_i_ii = "dual_i_ii";
	public  final String common_interface = "common_interface";
	public  final String hbb_tv_on_this_channel = "hbb_tv_on_this_channel";
	public  final String channel_info = "channel_info";
	public  final String mhp_applications = "mhp_applications";
	public  final String mono_stereo = "mono_stereo";
	public  final String controls = "controls";
	public  final String device_info = "device_info";
	public  final String recording_foreground ="recording_foreground";
	public  final String recording_background ="recording_background";
	public  final String PVR="PVR";
	//End Constants
	private  final String TAG = "TunerServiceHelpContext";
	private ServiceConnector mConnection = null;

	@SuppressWarnings("unused")
	private String [] mContextArray=null;

	private static String HELPCONTEXTPARAM1 = NA;
	private static String HELPCONTEXTPARAM2 = NA;
	private static String HELPCONTEXTPARAM3 = NA;
	private static String HELPCONTEXTPARAM4 = NA;

	private IHelpContext intHelpContext = null;
	private Context mContext;
	private static TunerServiceHelpContext mTunerServiceHelpContext;

	private TunerServiceHelpContext() {
	}

	/* Static 'instance' method */
	public static TunerServiceHelpContext getInstance() {
		if(mTunerServiceHelpContext == null){
			mTunerServiceHelpContext = new TunerServiceHelpContext();
		}
		return mTunerServiceHelpContext;
	}
	
	public void setTunerServiceContext(Context ctx){
		mContext = ctx;
	}

	class ServiceConnector implements ServiceConnection {
		@Override
		public void onServiceDisconnected(ComponentName name) {
			// TODO Auto-generated method stub
			intHelpContext = null;
		}

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			// TODO Auto-generated method stub
			Log.d("OnService connected", "HelpContext");
			intHelpContext = IHelpContext.Instance.asInterface(service);
			String [] lArray={HELPCONTEXTPARAM1, HELPCONTEXTPARAM2,
					HELPCONTEXTPARAM3, HELPCONTEXTPARAM4};
			try {
				intHelpContext.setHelpContext(lArray);			
				mContextArray=intHelpContext.getHelpContext();
			}catch(NullPointerException e) {
				
			}
		}
	}

	public void setHelpContextData(String param1, String param2, String param3,
			String param4) {
		Log.d(TAG, "setHelpContextData" + param1 + " " + param2
				+ " " + param3 + " " + param4);
		setHelpData(param1, param2, param3, param4);
		if (intHelpContext != null) {
			String [] lArray={HELPCONTEXTPARAM1, HELPCONTEXTPARAM2,	HELPCONTEXTPARAM3, HELPCONTEXTPARAM4};
			try {
				intHelpContext.setHelpContext(lArray);
				mContextArray=intHelpContext.getHelpContext();
			}catch(NullPointerException e) {
				
			}
		} else {
			startHelpService();
		}
	}

	public String[] getHelpContextData() {
		String[] retVal = null;
		if (intHelpContext != null) {
			try {
				retVal = intHelpContext.getHelpContext();
			}catch(NullPointerException e) {
				
			}
		} else {
			startHelpService();
		}
		return retVal;
	}

	public void startHelpService() {

		try {
			Intent mIntent = new Intent();
			mIntent.setAction("org.droidtv.intent.action.eUMService");
			
			if(mContext!=null) {
				PackageManager mPackageManager = mContext.getPackageManager();
				ResolveInfo mResolveInfo = mPackageManager.resolveService(mIntent, 0);
				if(mConnection == null) {
					mConnection = new ServiceConnector();
				}
				if((mResolveInfo != null) && (mConnection != null)) {
					mIntent.setClassName(mResolveInfo.serviceInfo.packageName, mResolveInfo.serviceInfo.name);
					mContext.bindService(mIntent, mConnection, Context.BIND_AUTO_CREATE);
					Log.d(TAG, "Binding help activity");
				}else {
					Log.d(TAG, "org.droidtv.intent.action.eUMService: not able to resolve ");
				}
			}
		} catch (ActivityNotFoundException e) {
			Log.d(TAG, "EumActivity not found"+e);
		}
	}

	private static void setHelpData(String param1,String param2,String param3,String param4) {
		HELPCONTEXTPARAM1 = param1;
		HELPCONTEXTPARAM2 = param2;
		HELPCONTEXTPARAM3 = param3;
		HELPCONTEXTPARAM4 = param4;
	}
	
	public void clearHelpData(){
		if (intHelpContext != null) {
			Log.d(TAG, "ClearHelpData");
			intHelpContext.clearContext();
		}
	}
	
	public void Release(){
		try{
			if(mConnection != null) {
				mContext.unbindService(mConnection);				
			}
		}
		catch(Exception e){
			e.printStackTrace();
		}
		mContext = null;
	}
}
