package org.droidtv.tunerservice;

import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.Application;
import android.content.Context;
import android.content.pm.PackageManager;
import android.util.Log;
import android.os.Binder;


public class TunerApplication extends Application {

	private static final String TAG="TunerApplication";
	private ITvSettingsManager mGlobalSetting;
	private PackageManager pm;
	private String mCurrentProcName;
	private static final String TUNER_PACKAGE="org.droidtv.tunerservice";
	private static final String CHANNELAPP_PACKAGE="org.droidtv.channels";
	private static final String TXT_PACKAGE="org.droidtv.teletext";
	private static final String MHEG_PACKAGE="org.droidtv.mheg";
	private static final String CIAPP_PACKAGE="org.droidtv.ci";
	private static final String OAD_PACKAGE="org.droidtv.oad";
	
	@Override
	public void onCreate() 
	{
		  super.onCreate();
		  
		  try
		  {  
		      ActivityManager manager = (ActivityManager) this.getSystemService(Context.ACTIVITY_SERVICE);   
		      
              // iterate all tuner service process until get org.droidtv.tuner process			  
		      for (RunningAppProcessInfo processInfo : manager.getRunningAppProcesses())
		      {	              
				  mCurrentProcName = processInfo.processName;
				
				  // check process whether it is tuner or not
				  if(mCurrentProcName.equalsIgnoreCase(TUNER_PACKAGE))
				  {	  
					  // get global setting
					  mGlobalSetting=ITvSettingsManager.Instance.getInterface();
					  
					  // get tuner option  value, it will be either 0 or 1. 1 for tuner less , 0 for tuner
					  int isTunerLess=mGlobalSetting.getInt(TvSettingsConstants.OPTUNERLESS,0,0);
					  pm =getApplicationContext().getPackageManager();
					  Log.d(TAG,"Get package manager call"+pm+" isTunerLess:"+isTunerLess);
					  
					  //  execute block to tuner less  tv
					  if(isTunerLess==1)
					  {// disable tuner  
						  
						  pm.setApplicationEnabledSetting(CHANNELAPP_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_DISABLED, 0);
						  pm.setApplicationEnabledSetting(MHEG_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_DISABLED, 0);
						  pm.setApplicationEnabledSetting(TXT_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_DISABLED, 0);
						  pm.setApplicationEnabledSetting(CIAPP_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_DISABLED, 0);
						  pm.setApplicationEnabledSetting(OAD_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_DISABLED, 0);
						  pm.setApplicationEnabledSetting(TUNER_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_DISABLED, 0);						  
					  }
					  else
					  { //enable tuner
						  pm.setApplicationEnabledSetting(TUNER_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_ENABLED, 0);
						  pm.setApplicationEnabledSetting(CHANNELAPP_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_ENABLED, 0);
						  pm.setApplicationEnabledSetting(MHEG_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_ENABLED, 0);
						  pm.setApplicationEnabledSetting(TXT_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_ENABLED, 0);
						  pm.setApplicationEnabledSetting(CIAPP_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_ENABLED, 0);
						  pm.setApplicationEnabledSetting(OAD_PACKAGE, PackageManager.COMPONENT_ENABLED_STATE_ENABLED, 0);
					  }
					  break;
				 }  
		      }
			  
		  }
		  catch(Exception e)
		  {
			  Log.d(TAG,"onCreate():Exception:to get tuner less property:"+e);
		  }	 
	}
}
