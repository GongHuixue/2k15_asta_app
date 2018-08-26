package org.droidtv.euinstallersat.notification;

import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
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

	private final String TAG = CamUpdateDialogActivity.class.getName();
	private Context mContext;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		mContext = this;
		Log.d(TAG, "OnCreate");
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
		
		mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_CAM_PROFILE_UPDATE_REQUEST), "");
    	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_CAM_PROFILE_UPDATE_REQUEST));
    	
    	ModalDialogFooterButtonProp mLaterButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_LATER),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_LATER clicked ");
    					mModalDialog.hide();
    					finish();
    				}
    			});
    	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NOW),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_NOW clicked ");
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
				
		// display tvtoast
		messenger = TvToastMessenger.getInstance(mContext);
		mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
		mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CAM_PROFILE_UPDATE_IMMEDIATE));
		messenger.showTvToastMessage(mTimeOutTvToast);
					
		launchUpdateWizard();
	}

	private void launchUpdateWizard()
	{
		Log.d(TAG, "launchUpdateWizard");
		NativeAPIWrapper.getInstance().setCamUpdateModeFlag(true);
		Intent l_intent;
		l_intent = new Intent("org.droidtv.euinstallersat.LAUNCH_SATELLITE_INSTALL_WIZARD");
		startActivity(l_intent);

	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		// TODO Auto-generated method stub
		return super.dispatchKeyEvent(event);
	}

	@Override
	protected void onDestroy()
	{
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
	}

	@Override
	protected void onPause()
	{
		// TODO Auto-generated method stub
		super.onPause();
	}

}
