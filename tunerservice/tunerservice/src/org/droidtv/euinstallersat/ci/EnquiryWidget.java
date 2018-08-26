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

import java.util.Observable;
import java.util.Observer;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.SatInstaller;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.media.ITvMediaCI.CICamIdInfo;
import android.content.Context;
import android.text.InputFilter;
import android.text.InputType;
import android.text.method.PasswordTransformationMethod;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class EnquiryWidget extends CIDialog implements Observer {

	private Context mContext;
	private SatInstaller mSatInstaller;
	private EditText alphanumeric;
	private CIInitializeInterface mCiInitializeInterface;
	private NotificationHandler mNotificationHandler;
	private static final int mCheckAnswerLength = 255;
	private static final String TAG = EnquiryWidget.class.getName();

	public EnquiryWidget(Context context,
			SatInstaller satInstaller,CIInitializeInterface ciInitializeInterface) {
		super(context);
		mContext = context;
		mSatInstaller = satInstaller;
		mCiInitializeInterface = ciInitializeInterface;
		// Registering for notification
			registerForNotification();

		Log.i(TAG, "EventID: EnquiryWidget constructor calling:"+mSatInstaller+"mContext:"+mContext);
	}
	
	/*
	 * Registering for notifications
	 */
	public void registerForNotification() {
		mNotificationHandler = NotificationHandler.getInstance();
		mNotificationHandler.registerForNotification(this);
	}
	
	/*
	 * Unregistering notifications
	 */
	public void unRegisterFromNotifications() {
		Log.d(TAG,"unRegisterFromNotifications called:"+mNotificationHandler);
		if(mNotificationHandler != null){
			mNotificationHandler.unRegisterForNotification(this);
		}
	}
	
	/*
	 * Set call to MW when the dialog is opened
	 */
	private void setMWInitial(){
			Log.i(TAG, "setMWInitial called:"+mSatInstaller);
	if(mSatInstaller != null){
		mSatInstaller.setMmiEnable();
		mSatInstaller.setMMIInProgress(true);
	}
	}
	
	public void closeWidget(){
	Log.i(TAG, "closeWidget called:"+mCiInitializeInterface);
		if(mCiInitializeInterface != null) {
						mCiInitializeInterface.setCurrentEvent();
						//set to MW
						setMWExit();
						hideDialog();
		}
	}
	/*
	 * Set call to MW when the user pressed EXIT button
	 */
	private void setMWExit(){
	Log.i(TAG, "setMWExit called:"+mSatInstaller);
	if(mSatInstaller != null){
			mSatInstaller.setExitResponse();
			mSatInstaller.setExitToOSD();
			mSatInstaller.setMMIInProgress(false);
	}
	}
	
	/*
	 * Set call to MW when the user pressed OK button
	 */
	private void setMWOK(){
		Log.i(TAG, "setMWOK called:");
		String answer = alphanumeric.getText().toString();
		Log.i(TAG, "setMWOK called: answer:->"+answer+"mPlayTvCIPlusHandler:"+mSatInstaller);
		if(answer != null && mSatInstaller != null){
		mSatInstaller.setMmiOKEnqCmdResponse(answer);
		}
	}
	
	
	/*
	 * Set call to MW when the user pressed Cancel button
	 */
	private void setMWCancel(){
	Log.i(TAG, "setMWCancel called:"+mSatInstaller);
	if(mSatInstaller != null){
		mSatInstaller.setMmiCancelEnqCmdResponse();
		}
	}
	
	/*
	 * Set To MW
	 */
	
	private void setMWEVENT(){
			//mPlayTvCIPlusHandler.setMmiOpenSupported(false);
	}
	
	/*
	 * Reset the edit text value when the user pressed Cancel button 
	 */
	private void resetText(){
		Log.i(TAG, "resetText called:"+alphanumeric);
		if(alphanumeric != null){
			alphanumeric.setText("");
		}
	}
	
	
	/*
	 *  Displays the dialog
	 */
	public void displayEnquiryWidget() {
		Log.i(TAG, "displayEnquiryWidget() called:"+mSatInstaller+"mContext:"+mContext+"mNotificationHandler"+mNotificationHandler);
		try {
			
			// Set to MW
			setMWInitial();
			
			final LayoutInflater inflater = (LayoutInflater) mContext
					.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			View enquiryScreen = inflater.inflate(R.layout.enquirydialog, null);
			
				Log.i(TAG ,
						"Length of the Answer:"
								+ mSatInstaller.getMmiCmdEnq()
								+ "ProptText:"
								+ mSatInstaller.getMmiCmdEnq().PromptText
								+ + mSatInstaller.getMmiCmdEnq().LengthOfAnswer);

				// Accessing PlayTvCIPLUSHandler
				String text = mSatInstaller.getMmiCmdEnq().PromptText;
				int numericLength = mSatInstaller.getMmiCmdEnq().LengthOfAnswer;
				boolean isNumericVisible = mSatInstaller
						.getMmiCmdEnq().Blind;

				// Set the body
				TextView body = (TextView) enquiryScreen
						.findViewById(R.id.bodytext);
				if (text != null && !text.equals("")){
					body.setText(text);
				}

					// set alpha numeric entry size

			// Pin Entry and setting max length
			alphanumeric = (EditText) enquiryScreen
					.findViewById(R.id.numericentry);

			alphanumeric.setFocusableInTouchMode(true);
			alphanumeric.requestFocus();
			if(numericLength != mCheckAnswerLength){
			alphanumeric
					.setFilters(new InputFilter[] { new InputFilter.LengthFilter(
							numericLength) });
			}
			if (isNumericVisible) {
				alphanumeric.setInputType(InputType.TYPE_CLASS_NUMBER
						| InputType.TYPE_NUMBER_VARIATION_PASSWORD);
				alphanumeric
						.setTransformationMethod(PasswordTransformationMethod
								.getInstance());
			}
			CICamIdInfo cICamIdInfo = mSatInstaller.getCamIDInfo(ITvMediaCI.SLOT_UNKNOWN);
			int slotID = -1;
			if(cICamIdInfo != null && cICamIdInfo.SlotID <= 1 && cICamIdInfo.SlotID >= 0){
				slotID = cICamIdInfo.SlotID;
			}
			Log.i(TAG,"MenuWidget slotID:"+slotID+"cICamIdInfo:"+cICamIdInfo);
			String slotName = null;
			if(slotID == 0){
				slotName = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_COMMON_INTERFACE_SLOT_2);
			} else {
				slotName = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_COMMON_INTERFACE_SLOT_1);
			}
			// Set the title
			setTitleText(slotName+" "+mContext.getString(org.droidtv.ui.strings.R.string.MAIN_COMMON_INTERFACE));
			setTitleVisibility(View.VISIBLE);
			setSubtitleVisibility(View.INVISIBLE);
			setBottomTextVisibility(View.INVISIBLE);

			setButton2Text(mContext
					.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_EXIT));
			setButton2Visibility(View.VISIBLE);
			setButton4Text(mContext
					.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_OK));
			setButton4Visibility(View.VISIBLE);
			setButton3Text(mContext
					.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL));
			setButton3Visibility(View.VISIBLE);
			setButton1Visibility(View.INVISIBLE);
			setMessageDialogListener(new MessageDialogListener() {
						@Override
						public void onButton4Clicked() {
							//set to MW
							setMWOK();
						} 
						@Override
						public void onButton3Clicked() {
							//set to MW
							setMWCancel();
							//Reset the edit text value
							resetText();
							
						}
						@Override
						public void onButton2Clicked() {
							closeWidget();
						}
						@Override
						public void onButton1Clicked() {
						} 
					});
					addView(enquiryScreen); 
					show();
				//}
		//	});
		} 
		catch(Exception e){  
			Log.e(TAG,e.getMessage());
		} 
  
	}

	/*
	 * Hide the dialog and unregister from notifications
	 */
	public void hideDialog(){
	Log.i(TAG,"hideDialog called");
		unRegisterFromNotifications();
		hide();
	}

	@Override
	public void update(Observable observable, Object data) {
		final int eventID = ((NotificationInfoObject) data).actionID;
		Log.i(TAG, " update called EventID:" + eventID);
		switch (eventID) {
		case EventIDs.CI_OPENMMI_WIDGET:
			// set call to MW
			setMWEVENT();
			break;
		case EventIDs.CI_CLOSEMMI_WIDGET:
			closeWidget();
			break;
		default:
			break;
		}
	}

	
	
	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		boolean handled = false;
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		Log.i(TAG, "dispatchKeyEvent pressed:" + keyCode);
		switch (keyCode) {
		case KeyEvent.KEYCODE_DPAD_CENTER:
		case KeyEvent.KEYCODE_ENTER:
			if (keyAction == KeyEvent.ACTION_UP) {
		
				Log.i(TAG, "current Focus:" + alphanumeric.isFocused());
				if (alphanumeric.isFocused()) {
					Log.d(TAG, "setting focus for the button");
					setButton4focussed();
					handled = true;
				}
			}
			break;
		case KeyEvent.KEYCODE_BACK:
			if (keyAction == KeyEvent.ACTION_DOWN) {
				Log.d(TAG,"BackKey pressed");
				closeWidget();
				handled = true;
			}
			break;
		case KeyEvent.KEYCODE_TV:
		case KeyEvent.KEYCODE_CHANNEL_UP:
		case KeyEvent.KEYCODE_CHANNEL_DOWN:
		case KeyEvent.KEYCODE_GUIDE:
		case KeyEvent.KEYCODE_INFO:
		case KeyEvent.KEYCODE_WINDOW:
		case KeyEvent.KEYCODE_TELETEXT:
		case KeyEvent.KEYCODE_MEDIA_RECORD:
				Log.i(TAG," GUIDE OR INFO OR WINDOW key pressed");
				handled = true;
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
		Log.i(TAG,"Enquiry Widget dispatchKeyEvent pressed handle:"+handled);
	
	Log.i(TAG,"Enquiry Widget dispatchKeyEvent pressed return value:"+handled);
	return handled || super.dispatchKeyEvent(event);
	}
	
	
}
