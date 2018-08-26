package org.droidtv.euinstallersat.ci;

import java.util.Observable;
import java.util.Observer;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.euinstallersat.model.mwapi.SatInstaller;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import android.app.Activity;
import android.content.Context;
import android.util.Log;

public class CIPlusUI implements Observer {

	private Context mContext;
	private int mPurpose;
	private NotificationHandler mNotificationHandler;
	private CIInitializeInterface ciInitializeInterface;
	private int event;
	private static final String TAG = CIPlusUI.class.getSimpleName();
	private SatInstaller satInstaller;
	public CIPlusUI(Context context) {
		mContext = context;
		
		mNotificationHandler = NotificationHandler.getInstance();
		
		mNotificationHandler.registerForNotification(this);
		Log.i(TAG, "CIFactory:mPlayTvCIPlusHandler-:"+context);
		
		ciInitializeInterface = getWidgetInstance();
		NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
		//Enabiling the mmi
		nwrap.setMMIEnabled(true);
		satInstaller = nwrap.getSatInstaller(TunerName.TUNER1);
		ciInitializeInterface.setContext(mContext);
		ciInitializeInterface.setSatInstaller(satInstaller);
		
	}
 	@Override
	public void update(Observable observable, Object data) {
		event = ((NotificationInfoObject) data).actionID;
		Log.i(TAG, "CIFactory:mPlayTvCIPlusHandler->event:"+event);
		
		if(!(ciInitializeInterface.getNonInterruptStatus())){
		ciInitializeInterface.setSatInstaller(satInstaller);
		switch(event){
			case EventIDs.CI_OPENENQUIRY_WIDGET:
			case EventIDs.CI_OPENLIST_WIDGET:
			case EventIDs.CI_OPENMENU_WIDGET:
			case EventIDs.CI_OPENTEXT_WIDGET:
			case EventIDs.CI_OPENMMI_WIDGET:
			case EventIDs.CI_CLOSEMMI_WIDGET:
			case EventIDs.CI_INACTIVE_STATE:
				((Activity)mContext).runOnUiThread(new Runnable() {
					
					@Override
					public void run() {
						ciInitializeInterface.update(event);
						
					}
				});
				
			break;
			default:
			break;
		}
	}
	}
	
		
	
	private CIInitializeInterface getWidgetInstance(){
		ciInitializeInterface = CIMainWidget.getInstance();
		return ciInitializeInterface;
	}
		
}
