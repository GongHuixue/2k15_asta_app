package org.droidtv.euinstallertc.notification;


import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class NetworkUpdateDialogActivity extends Activity {

	private Context mContext;
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;
	private static final String TAG = NetworkUpdateDialogActivity.class.getName();
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private NotificationHandler ntf = NotificationHandler.getInstance();
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		Log.d(TAG, "OnCreate");
		mContext = this;
		
		instActManager.addActivityToStack(this);
		showDialog();
	}
	
	private void showDialog()
	{
		Log.d(TAG, "showDialog");
		
		mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_CHANNEL_UPDATE_MESSAGE), "");
    	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_NETWORK_UPDATE_DETECTED));
    	
    	ModalDialogFooterButtonProp mLaterButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_LATER),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
       					Log.d(TAG, "MAIN_BUTTON_LATER clicked ");
    					mModalDialog.hide();
						//TvNotificationManager.postTvNotification(mContext, TvNotificationManager.FLAG_NO_IMAGE,mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_NETWORK_UPDATE_LATER), TvNotificationManager.FLAG_TIMED_NOTIFICATION, 0);
						// display tvtoast
						messenger = TvToastMessenger.getInstance(mContext);
						mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
						mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_NETWORK_UPDATE_LATER));
						messenger.showTvToastMessage(mTimeOutTvToast);
    					nwrap.networkChangeDetected(true);
    					finish();
    				}
    			});
    	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NOW),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					nwrap.setApplicationContext(mContext);
    					if(nwrap.ifRecordingIsInProgress()){
    						nwrap.showRecordingMessage();
    					}else{
    						launchUpdateWizard();
    					}
    					
    					mModalDialog.hide();
    					finish();
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setCancelable(false);
    	mModalDialog.show();
    	mLaterButton.requestFocus();
	}
	
	private void launchUpdateWizard()
	{
		Log.d(TAG, "launchUpdateWizard");
		Intent l_intent;
		l_intent = new Intent(mContext,NetworkUpdateInstallActivity.class);
		l_intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		mContext.startActivity(l_intent);
	}

	@Override
	protected void onStart() {
		super.onStart();
		Log.d(TAG, "onStart");
	}

	@Override
	protected void onResume() {
		super.onResume();
		Log.d(TAG, "onResume");
	}

	@Override
	protected void onPause() {
		super.onPause();
		Log.d(TAG, "onPause");
		if (isFinishing()) {
			Log.d(TAG, "onPause & the reason is activity is finishing");
		}
	}

	@Override
	protected void onStop() {
		super.onStop();
		if (!isFinishing()) {
			finish();
		}
		Log.d(TAG, "onStop");
	}

	@Override
	protected void onDestroy() {
		instActManager.removeActivityFromStack(this);
		Log.d(TAG, "onDestroy");
		super.onDestroy();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Log.d(TAG, "onRestart");
	}

}
