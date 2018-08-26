package org.droidtv.tunerservice.bcstreceiver;



import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tunerservice.tvmanager.MainCIManager;
import org.droidtv.tunerservice.tvmanager.AuxCIManager;

public class InstallationReceiver extends BroadcastReceiver {

	private static final String TAG = "InstallationReceivers";
	public static boolean isUpdateRequired = false;
	
	@Override
	public void onReceive(Context context, Intent intent) {
	
		Bundle extras = intent.getExtras();
		if (extras != null) {
			if (intent.getAction().equalsIgnoreCase("org.droidtv.euinstallertc.CHANNEL_INSTALL_START")) {
				String installMode = extras.getString("InstallMode");
				Log.d(TAG,"start installation->" + installMode);
				if(installMode!=null){
					Log.d(TAG,"TC Installation start send:");
					if(installMode.equalsIgnoreCase("Auto")){
						MainCIManager mainCIManager = MainCIManager.getMainCIManagerInstance();
						if(mainCIManager != null){
							mainCIManager.notifyChannelInstallStatus(false,Medium.MEDIUM_TERRESTRIAL);
							Log.d(TAG,"TC Installation start send:");
						} else {
							Log.d(TAG,"TC Installation Complete received: MainCIManager is null not called showcamwizard");
						}
						
						AuxCIManager auxCIManager = AuxCIManager.getAuxCIManagerInstance();
						if(auxCIManager != null){
							auxCIManager.notifyChannelInstallStatus(false,Medium.MEDIUM_TERRESTRIAL);
						}else {
						Log.d(TAG,"TC Installation Complete received: auxCIManager is null not called showcamwizard");
						}
					}
				}
			} else if (intent.getAction().equalsIgnoreCase("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE")) {
				String installMode = extras.getString("InstallMode");
				Log.d(TAG,"TC Installation Complete received: CHANNEL_INSTALL_COMPLETE : " + installMode);
				if(installMode!=null){
					if(installMode.equalsIgnoreCase("Auto")){
						MainCIManager mainCIManager = MainCIManager.getMainCIManagerInstance();
						if(mainCIManager != null){
							mainCIManager.notifyChannelInstallStatus(true,Medium.MEDIUM_TERRESTRIAL);
						} else {
							Log.d(TAG,"TC Installation Complete received: MainCIManager is null not called showcamwizard");
						}
						
						AuxCIManager auxCIManager = AuxCIManager.getAuxCIManagerInstance();
						if(auxCIManager != null){
							auxCIManager.notifyChannelInstallStatus(true,Medium.MEDIUM_TERRESTRIAL);
						}else {
						Log.d(TAG,"TC Installation Complete received: auxCIManager is null not called showcamwizard");
						}
					}
				}
				
			} else if (intent.getAction().equalsIgnoreCase("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED")) {
				Log.d(TAG,"Stop Installation : " + intent.getStringExtra("InstallMode"));
			}else if (intent.getAction().equalsIgnoreCase("org.droidtv.euinstallersat.SATELLITE_INSTALL_START")) {
					String installMode = extras.getString("InstallMode");
					Log.i(TAG,"start sat installation:" + installMode);
					if(installMode!=null){
						if(installMode.equalsIgnoreCase("Auto")){
							MainCIManager mainCIManager = MainCIManager.getMainCIManagerInstance();
							if(mainCIManager != null){
								mainCIManager.notifyChannelInstallStatus(false,Medium.MEDIUM_SATELLITE);
								Log.d(TAG,"SAT Installation start send:");
							} else {
								Log.d(TAG,"SAT Installation Complete received: MainCIManager is null not called showcamwizard");
							}
							AuxCIManager auxCIManager = AuxCIManager.getAuxCIManagerInstance();
							if(auxCIManager != null){
								auxCIManager.notifyChannelInstallStatus(false,Medium.MEDIUM_SATELLITE);
							}else {
							Log.d(TAG,"SAT Installation Complete received: auxCIManager is null not called showcamwizard");
							}
						}
					}
			}
			else if (intent.getAction().equalsIgnoreCase("org.droidtv.euinstallersat.SATELLITE_INSTALL_COMPLETE")) {
					String installMode = extras.getString("InstallMode");
					Log.i(TAG,"SAT Installation complete received:" + installMode);
					if(installMode!=null){
						if(installMode.equalsIgnoreCase("Auto")){
							MainCIManager mainCIManager = MainCIManager.getMainCIManagerInstance();
							if(mainCIManager != null){
								mainCIManager.notifyChannelInstallStatus(true,Medium.MEDIUM_SATELLITE);
							} else {
								Log.d(TAG,"SAT Installation Complete received: MainCIManager is null not called showcamwizard");
							}
							AuxCIManager auxCIManager = AuxCIManager.getAuxCIManagerInstance();
							if(auxCIManager != null){
								auxCIManager.notifyChannelInstallStatus(true,Medium.MEDIUM_SATELLITE);
							}else {
							Log.d(TAG,"SAT Installation Complete received: auxCIManager is null not called showcamwizard");
							}
						}
					}
				
			}  else if (intent.getAction().equalsIgnoreCase("org.droidtv.euinstallersat.SATELLITE_INSTALL_STOPPED")) {
				Log.i(TAG,"Sat installation Stopped:" + intent.getStringExtra("InstallMode"));
			}
		}

	}

}
