package org.droidtv.tunerservice.services.sbyservice;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.SystemProperties;
import android.util.Log;

import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl.ITvSemiStandbyCallback;

public class HtvSSBYClientDelay implements Handler.Callback {

    public static final String TAG = "SSBYServiceHtvSsbyDelay";

    private Context mContext = null;
    private ITvSemiStandbyControl ssbyIntf = null;
    private Handler mHandler = null;
    private SbyCallback mSbyCallback = null;

    private static final int CLIENT_ID = ITvSemiStandbyControl.ACTION_HTV_SSBY_DELAY;
    private static final int DELAY_TIMER = 5;
    private int delayCounter = 0;

    private static final int EVENT_INIT = 1;
    private static final int EVENT_CONNECTED = 2;
    private static final int EVENT_START_DELAY = 3;
    private static final int EVENT_IGNORE_DELAY = 4;

    public HtvSSBYClientDelay(Context context) {
        mContext = context;
        mHandler = new Handler(this);
        mHandler.sendEmptyMessage(EVENT_INIT);
        mSbyCallback = new SbyCallback();
    }

    @Override
    public boolean handleMessage(Message msg) {
        switch(msg.what) {
            case EVENT_INIT:
                bindToSsbyService();
                break;

            case EVENT_CONNECTED:
                ssbyIntf.registerSemiStandbyAction(CLIENT_ID, mSbyCallback);
                break;

            case EVENT_START_DELAY:
                delayCounter = 0;
                mHandler.post(mDelayRunnable);
                break;

            case EVENT_IGNORE_DELAY:
                ssbyIntf.setActionCompleted(CLIENT_ID);
                break;

            default:
                break;
        }
        return false;
    }

    private void bindToSsbyService() {
        ServiceConnectionImpl svcConn = new ServiceConnectionImpl();
        Intent intent = new Intent(TvIntent.ACTION_SERVICE_SBYSERVICE);
        mContext.bindService(intent, svcConn, Context.BIND_AUTO_CREATE);
    }

    private class ServiceConnectionImpl implements ServiceConnection {

        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Log.d(TAG, "onServiceConnected");
            ssbyIntf = ITvSemiStandbyControl.Instance.asInterface(service);
            mHandler.sendEmptyMessage(EVENT_CONNECTED);
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.d(TAG, "onServiceDisconnected");
        }

    }

    private class SbyCallback extends ITvSemiStandbyCallback {

        public void onStartAction() {
            Log.d(TAG, "onStartAction");

            if (SystemProperties.get("persist.htv.ssby_delay").equals("disable")) {
                Log.d(TAG, "persist.htv.ssby_delay - disable, ignore standby delay");
                mHandler.sendEmptyMessage(EVENT_IGNORE_DELAY);
            } else {
                Log.d(TAG, "Stay in semi standby for another 5 mins");
                mHandler.sendEmptyMessage(EVENT_START_DELAY);
            }
        }

        public void onStopAction() {
            Log.d(TAG, "onStopAction");
            mHandler.removeCallbacks(mDelayRunnable);
            ssbyIntf.setActionCompleted(CLIENT_ID);
        }
    }

    private Runnable mDelayRunnable = new Runnable() {
        public void run() {
            Log.d(TAG, "delay counter - " + delayCounter + " minute(s)");
            if (delayCounter == DELAY_TIMER) {
                ssbyIntf.setActionCompleted(CLIENT_ID);
            } else {
                delayCounter++;
                mHandler.postDelayed(this, 60000);
            }
        }
    };

}