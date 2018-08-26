/*
*  Copyright(C) 2012 TP Vision Holding B.V.,
*  All Rights Reserved.
*  This  source code and any compilation or derivative thereof is the
*  proprietary information of TP Vision Holding B.V.
*  and is confidential in nature.
*  Under no circumstances is this software to be exposed to or placed
*  under an Open Source License of any type without the expressed
*  written permission of TP Vision Holding B.V.
*
*/
package org.droidtv.euinstallersat.ci;



import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.SatInstaller;
import android.content.Context;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

public class TextWidget extends CIDialog {
	
	private SatInstaller mSatInstaller;
	private Context mContext;
	private CIInitializeInterface mCiInitializeInterface = null;
	private static final String TAG = TextWidget.class.getName();

	public TextWidget(Context context,
			SatInstaller satInstaller,CIInitializeInterface ciInitializeInterface) {
		super(context);
		mContext = context;
		mCiInitializeInterface = ciInitializeInterface;
		mSatInstaller = satInstaller;
		Log.i(TAG, "TextWidget constructor calling:"+mSatInstaller+"mContext:"+mContext);
	}

	public void closeWidget(){
						mCiInitializeInterface.setCurrentEvent();
						//set to MW
						setMWExit();
						hideDialog();
	}
	/*
	 * Set call to MW when the dialog is opened
	 */
	private void setMWInitial(){
	Log.i(TAG, "setMWInitial calling:"+mSatInstaller);
	 		mSatInstaller.setMmiEnable();  
	}
	
	/*
	 * Set call to MW when the dialog is closed
	 */
	private void setMWExit(){
			Log.i(TAG, "TextWidget playTvCIPlusHandler"+mSatInstaller);
			mSatInstaller.setExitResponse();
			mSatInstaller.setExitToOSD();
		
	}

	/*
	 * Closes the dialog
	 */
	public void hideDialog() {
		Log.i(TAG, " hideDialog PlayTvActivity:" + mContext);
		hide(mContext);
	}
	 
	/*
	 * Text Dialog called when the event triggered from the MW
	 */
	public void displaytextWidget() {
		Log.i(TAG,
				"displaytextWidget called");
		// set call to MW
		setMWInitial();

		final LayoutInflater inflater = (LayoutInflater) mContext
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View textScreen = inflater.inflate(R.layout.textdialog, null);

				
				
				// Set the body
				TextView body = (TextView) textScreen
						.findViewById(R.id.bodytext);

		body.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CI_MODULE_INACTIVE));

		// Set the title
		setTitleText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_COMMON_INTERFACE));

		setTitleVisibility(View.VISIBLE);
		setSubtitleVisibility(View.INVISIBLE);
		setBottomTextVisibility(View.INVISIBLE);

		setButton1Visibility(View.INVISIBLE);
		setButton2Visibility(View.INVISIBLE);
		setButton3Visibility(View.INVISIBLE);
		setButton4Text(mContext
				.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_EXIT));
		setButton4Visibility(View.VISIBLE);
		setButton4focussed();

		setMessageDialogListener(new MessageDialogListener() {
					@Override
					public void onButton4Clicked() {
						Log.i(TAG,"TextWidget onButton4Clicked Activity:"+mContext);
						closeWidget();
					}
					@Override
					public void onButton3Clicked() {
					}
					@Override
					public void onButton2Clicked() {
					}
					@Override
					public void onButton1Clicked() {
					}
				});
				// Add the view
				addView(textScreen);
				show();
			//}
		//});
	}
	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		boolean handled = false;
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		switch (keyCode) {
		case KeyEvent.KEYCODE_BACK:
			if (keyAction == KeyEvent.ACTION_DOWN) {
				Log.d(TAG,"BackKey pressed");
				closeWidget();
				handled = true;
			}
			break;
		case KeyEvent.KEYCODE_ESCAPE:
			if (keyAction == KeyEvent.ACTION_DOWN) {
				Log.d(TAG,"Exitkey pressed");
				closeWidget();
				handled = true;
			}
			break;
		/*case KeyEvent.KEYCODE_DPAD_DOWN:
			Log.i(TAG, "keyAction Focus:" + keyAction);
			if (keyAction == KeyEvent.ACTION_DOWN) {
				Log.i(TAG, "current Focus:" + alphanumeric.isFocused());
				if (alphanumeric.isFocused()) {
					Log.d(TAG, "setting focus for the button");
					setButton4focussed();
				}
			}
			break;*/
		}
		return handled | super.dispatchKeyEvent(event);
	}
	
}
