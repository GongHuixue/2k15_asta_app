package org.droidtv.euinstallersat.service;

import java.util.ArrayList;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.euinstallersat.model.mwapi.SemistandbyUpdate;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.tv.media.IInstallerService;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.Handler;
import android.os.Handler.Callback;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;

public class SatInstallerService extends Service implements IInstallerService {

    private static final String TAG     = SatInstallerService.class.getName();
	
    private InstallerTVSettings instTVS = null;
    private NativeAPIWrapper    nwrap   = NativeAPIWrapper.getInstance();
    private NotificationHandler ntf     = NotificationHandler.getInstance();
    private Context             mContext;
    private ArrayList<IInstallerServiceListener> listenerList = new ArrayList<IInstallerServiceListener>();
    private SemistandbyUpdate 	semisbyInst = null;
    private Callback mMessageHandler = null;
    private Handler mHandler=null;
    
    private static final int MSG_STARTBACKGROUND = 0;
    private static final int MSG_STOPBACKGROUND  = 1;
    
    private static final int MSG_STARTUPDATE = 2;
    private static final int MSG_STOPUPDATE  = 3;   
    
    public class InstallerBinder extends Binder {
        InstallerBinder getService() {
            return InstallerBinder.this;
        }
    }

    public void installationComplete(int status){
    	IInstallerServiceListener registeredListner;
		Log.d(TAG, "installationComplete " + status);

		nwrap.SetHostControlStatus(TunerName.TUNER1, true);
		nwrap.SetHostControlStatus(TunerName.TUNER2, true);
		
    	for(int index=0;index<listenerList.size();index++){
    		registeredListner = listenerList.get(index);
    		registeredListner.onInstallationCompleted(status);
    	}
    }
    
    @Override
    public boolean onUnbind(Intent intent) {
        Log.d(TAG, "onUnbind " + intent);
       // nwrap.unBind_Service();
        return super.onUnbind(intent);
    }

    @Override
    public IBinder onBind(Intent argIntent) {
        Log.d(TAG, "onBind " + argIntent);
        return IInstallerService.Instance.asBinder((IInstallerService) this);
    }
    
    @Override
    public void onCreate() {
        Log.d(TAG, "onCreate Enter");
        super.onCreate();
       
        mContext = this;
//        semisbyInst = new SemistandbyUpdate(mContext);
//        semisbyInst.registerServerInstance(this);
        listenerList = new ArrayList<IInstallerServiceListener>();
        
    	// register for NVM bit changes
		instTVS = new InstallerTVSettings();
		instTVS.registerTvSettingsManager();
		
		nwrap = NativeAPIWrapper.getInstance();
		nwrap.setApplicationContext(mContext);
		
		nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_OBSERVER);
		
        mMessageHandler = new Callback() {

			@Override
			public boolean handleMessage(Message msg) {
				switch(msg.arg1) {
					case MSG_STARTBACKGROUND:
						Log.d(TAG,"MSG_STARTBACKGROUND: ");
						/*semisbyInst.StartInstallation 
							(IInstallerService.BACKGROUND_INSTALLATION, msg.arg2);*/
						break;
					case MSG_STOPBACKGROUND:
						Log.d(TAG,"MSG_STOPBACKGROUND: ");
						/*semisbyInst.StopInstallation(IInstallerService.BACKGROUND_INSTALLATION);*/
						break;
					case MSG_STARTUPDATE:
						Log.d(TAG,"MSG_STARTUPDATE: ");

						//nwrap.setApplicationContext(mContext);
						/*if(semisbyInst.StartInstallation (IInstallerService.UPDATE_INSTALLATION, msg.arg2) == true)
						{
							//nwrap.initTVMediaPlayer(NativeAPIWrapper.TunerName.TUNER1);
							//nwrap.setBackgroundFlag();
						}
						else
						{
							Log.d(TAG,"UPDATE INSTALLATION NOT REQUIRED");							
						}*/
						break;
					case MSG_STOPUPDATE:
						Log.d(TAG,"MSG_STOPUPDATE: ");
						//semisbyInst.StopInstallation(IInstallerService.UPDATE_INSTALLATION);
                
						break;
				}
				return true;
			}
        };
        //mHandler = new Handler(mMessageHandler);
        mHandler = new Handler();
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "onDestroy");
        super.onDestroy();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        super.onStartCommand(intent, flags, startId);
        Log.d(TAG, "onStartCommand intent:" + intent + " flags:" + flags + " startId:" + startId);

        // continue running service until explicitly stopped, so return sticky.
        return START_STICKY;
    }

    @Override
    public boolean StartInstallation(int mode, int param) {
    	boolean 	retval = true;
        Log.d(TAG, "### StartInstallation " + mode + " : " + param);
        Message msg = mHandler.obtainMessage();
        int l_appState = nwrap.getApplicationState();
        if( (l_appState ==NativeAPIWrapper.STATE_IDLE) || (l_appState ==NativeAPIWrapper.STATE_SERVICE))
        {
        	nwrap.setApplicationState(NativeAPIWrapper.STATE_SERVICE);
			//nwrap.createMWInstance(mContext);
			
	        switch (mode) {
	            case IInstallerService.BACKGROUND_INSTALLATION:
	                Log.d(TAG, "### StartInstallation BACKGROUND_INSTALLATION from EuinstallerSatService");
	                msg.arg1=MSG_STARTBACKGROUND;
	                msg.arg2=param;
	                mHandler.sendMessage(msg);
	                     
	                break;
	            case IInstallerService.UPDATE_INSTALLATION:
	                Log.d(TAG, "#### StartInstallation UPDATE_INSTALLATION from EuinstallerSatService");
			
					msg.arg1=MSG_STARTUPDATE;
	                msg.arg2=param;
	                mHandler.sendMessage(msg);
					
					break;
	        }
        }
        else
        {
        	Log.d(TAG,"ignore start installation");
        }
        Log.d( TAG, "### SatinstallerService returned " + retval);
        return retval;
    }

    @Override
    public boolean StopInstallation(int mode) {
    	boolean 	retval = true;
        Log.d(TAG, "StopInstallation " + mode);
         Message msg = mHandler.obtainMessage();
         int l_appState = nwrap.getApplicationState();
         if( (l_appState ==NativeAPIWrapper.STATE_IDLE) || (l_appState ==NativeAPIWrapper.STATE_SERVICE))
         {
         	nwrap.setApplicationState(NativeAPIWrapper.STATE_SERVICE);
	        switch (mode) {
	            case IInstallerService.BACKGROUND_INSTALLATION:
	                Log.d(TAG, "StopInstallation BACKGROUND_INSTALLATION from EuinstallerTcService");              
	                //retval = semisbyInst.StopInstallation (mode);
	               
	                msg.arg1=MSG_STOPBACKGROUND;
	                msg.arg2=0;
	                mHandler.sendMessage(msg);
	                break;
	            case IInstallerService.UPDATE_INSTALLATION:
	                Log.d(TAG, "StopInstallation UPDATE_INSTALLATION from EuinstallerTcService");
					msg.arg1=MSG_STOPUPDATE;
	                msg.arg2=0;
	                mHandler.sendMessage(msg);
	                
	                break;
	        }
         }
         else
         {
         	Log.d(TAG,"ignore stop installation");
         }
        Log.d( TAG, "StopInstallation returned " + retval);
        return retval;
    }

    @Override
    public void registerInstallerListener(IInstallerServiceListener listener) {
        Log.d(TAG, "registerInstallerListener " + listener);
        listenerList.add(listener);
    }

    @Override
    public void unRegisterInstallerListener(IInstallerServiceListener listener) {
        Log.d(TAG, "unRegisterInstallerListener " + listener);
        listenerList.remove(listener);
    }

	
	
}
