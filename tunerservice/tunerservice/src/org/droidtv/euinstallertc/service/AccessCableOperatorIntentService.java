package org.droidtv.euinstallertc.service;

import android.util.Log;
import android.content.Context;
import android.app.IntentService;
import android.content.Intent;


/*161031GaryYe cable operator[TF415PHIEUMTK01-184] Ensure all the Wizards settings are cloned*/
public class AccessCableOperatorIntentService extends IntentService {
    private static final String TAG = "AccessCableOperatorIntentService";
    private static Context mContext;
    public final static String ACTION_CHANGE_CABLE_OPERATOR   = "org.droidtv.installer.ChangeMwCableOperator";

    public AccessCableOperatorIntentService() {
        super(TAG);
        mContext = this;
    }
    @Override  
    public void onCreate() {  
        super.onCreate();
    }  

    @Override
    protected void onHandleIntent(Intent intent) {
        int operatorID = 0;
        
        final String action = intent.getAction();       
        if (null == action) {
            Log.d(TAG, "Error: Intent Action is null!");
            return;
        }

        if(action.equals(ACTION_CHANGE_CABLE_OPERATOR)) {
            mContext.getSharedPreferences("CableOperatorHTV",Context.MODE_MULTI_PROCESS).edit().putBoolean("isHtvID",true).commit();
        }
    }
}