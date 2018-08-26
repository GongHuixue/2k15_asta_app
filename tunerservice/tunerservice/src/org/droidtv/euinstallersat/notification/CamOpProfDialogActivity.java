package org.droidtv.euinstallersat.notification;

import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;

public class CamOpProfDialogActivity extends Activity {

	private static final String TAG = CamOpProfDialogActivity.class.getName();
	private Context mContext;
	private NativeAPIWrapper nwrap;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mContext = this;
		Log.d(TAG, "OnCreate");
		instActManager.addActivityToStack(this);
		nwrap = NativeAPIWrapper.getInstance();
		showDialog();
	}

	private void showDialog() {
		Log.d(TAG, "showDialog");

		mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_CAM_REINSTALL_NEW_PROFILE), "");
    	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_CAM_REINSTALL_NEW_PROFILE));
    	
    	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_LATER),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_LATER clicked ");
    					nwrap.getSatInstaller(TunerName.TUNER1).setOPProfLaterPressed(true);
    					mModalDialog.hide();
    					finish();
    				}
    			});
    	ModalDialogFooterButtonProp mNowButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NOW),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_NOW clicked ");
    					if(nwrap.ifRecordingIsInProgress()){
    						nwrap.showRecordingMessage();
    					}else{
    						launchFromCamWizard();
    					}
    					mModalDialog.hide();
                        finish();
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setCancelable(false);
    	mModalDialog.show();
    	mNowButton.requestFocus();
	}

	private void launchFromCamWizard() {
		Log.d(TAG, "launchFromCamWizard");
		Intent intent = new Intent(mContext,CamOpProfInstallActivity.class);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		nwrap.sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
		mContext.startActivity(intent);
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		return super.dispatchKeyEvent(event);
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
	}

	@Override
	protected void onStop() {
		super.onStop();
		Log.d(TAG, "onStop");
	}

	@Override
	protected void onDestroy() {
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Log.d(TAG, "onRestart");
	}

}
