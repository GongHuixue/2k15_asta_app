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
import android.view.KeyEvent;

public class CamUpdateDialogActivity extends Activity
{

	private static final String TAG = CamUpdateDialogActivity.class.getName();
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	private Context ctx;
	private NotificationHandler ntf = NotificationHandler.getInstance();
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		Log.d(TAG, "OnCreate");
		ctx = this;
		instActManager.addActivityToStack(this);
		Bundle l_bundle = getIntent().getExtras();
		String l_notificationType = (String) l_bundle.get("NotificationType");
		// getIntent().getStringExtra("NotificationType");
		Log.d(TAG, "l_notificationType " + l_notificationType);
		if (l_notificationType.equalsIgnoreCase("Dialog")) {
			showDialog();
		} else {
			showNotification();
		}
	}

	private void showDialog()
	{
		Log.d(TAG, "showDialog");
		
		mBuilder = new ModalDialog.Builder(ctx,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TI_CAM_PROFILE_UPDATE_REQUEST), "");
    	mBuilder.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DI_CAM_PROFILE_UPDATE_REQUEST));
    	
    	ModalDialogFooterButtonProp mLaterButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_LATER),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "Stop cancelled Resume");
    					mModalDialog.hide();
    					finish();
    				}
    			});
    	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NOW),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					launchUpdateWizard();
    					mModalDialog.hide();
                        finish();
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setCancelable(false);
    	mModalDialog.show();
    	mLaterButton.requestFocus();
	}

	private void showNotification()
	{
		Log.d(TAG, "showNotification");
		//TvNotificationManager.postTvNotification(this, TvNotificationManager.FLAG_NO_IMAGE, getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CAM_PROFILE_UPDATE_IMMEDIATE),TvNotificationManager.FLAG_TIMED_NOTIFICATION, 0);
		messenger = TvToastMessenger.getInstance(ctx);
		mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
		mTimeOutTvToast.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CAM_PROFILE_UPDATE_IMMEDIATE));
		messenger.showTvToastMessage(mTimeOutTvToast);
		
		launchUpdateWizard();
	}

	private void launchUpdateWizard()
	{
		Log.d(TAG, "launchUpdateWizard");
		NativeAPIWrapper.getInstance().setCamUpdateModeFlag(true);
		Intent l_intent;
		l_intent = new Intent("org.droidtv.euinstallertc.LAUNCH_CHANNEL_INSTALL_WIZARD");
		startActivity(l_intent);
		finish();
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		return super.dispatchKeyEvent(event);
	}

	@Override
	protected void onDestroy()
	{
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
	}
	
	@Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG, "onStop");
    }

	@Override
	protected void onPause()
	{
		Log.d(TAG, "onPause");
		if(isFinishing()){
		   Log.d(TAG, "onPause & the reason is activity is finishing");
		}
		super.onPause();
	}

}
