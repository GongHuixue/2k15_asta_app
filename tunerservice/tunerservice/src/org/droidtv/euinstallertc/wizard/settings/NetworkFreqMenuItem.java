package org.droidtv.euinstallertc.wizard.settings;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.util.IViewListener;
import org.droidtv.euinstallertc.util.RalativeLayoutView;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueConfirmation;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueEntered;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.helpers.ResourceHelper;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IMenuNodeControl;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class NetworkFreqMenuItem extends MenuItem implements IMenuNodeControl, IViewListener, IInputPickerValueConfirmation, IInputPickerValueEntered {
	private static final String TAG = NetworkFreqMenuItem.class.getName();
	protected Context mContext;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private RalativeLayoutView retView;
	private Button doneButton;
	private Button cancelButton;
	private InputPicker pickerLeft;
	private InputPicker pickerRight;
	private Boolean ifEditedByUser;

	public NetworkFreqMenuItem(Context context, AttributeSet attrs, ResourceHelper reshelp) {
		super(context, attrs, reshelp);
		Log.d(TAG, "NetworkFreqMenuItem()");
		mContext = context;
		ifEditedByUser = false;

		LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		retView = (RalativeLayoutView) inflater.inflate(R.layout.settings_symbol_rate_layout, null);
		pickerLeft = (InputPicker) retView.findViewById(R.id.settings_picker_left);
		pickerRight = (InputPicker) retView.findViewById(R.id.settings_picker_right);
		cancelButton = (Button) retView.findViewById(R.id.settings_button_cancel);
		doneButton = (Button) retView.findViewById(R.id.settings_button_done);

		retView.addListener(this);

		pickerLeft.setMinValue(0);
		pickerLeft.enableLeandingZero(true);
		pickerLeft.setValueConfirmListener(this);
		pickerLeft.setValueEnteredListener(this);

		pickerRight.setMinValue(0);
		pickerRight.enableLeandingZero(true);
		pickerRight.setValueConfirmListener(this);
		pickerRight.setValueEnteredListener(this);

		pickerLeft.setMaxValue(999);
		pickerRight.setMaxValue(99);

		cancelButton.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				ReloadValues();
				getMenuBuilder().removeFocus();
			}
		});

		doneButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				int pickerValue = 0;
				ifEditedByUser = true;
				CommitValues();
				ReloadValues();

				getMenuBuilder().removeFocus();
				Log.d(TAG, " doneButton.setOnClickListener " + pickerValue);
			}
		});
		
		ReloadValues();
	}

	private int getValueFromPickerUI() {
		int returnValue = 0;

		returnValue = pickerLeft.getCurrValue() * 100;
		returnValue = returnValue + ((pickerRight.getCurrValue() * 100) / 100);

		Log.d(TAG, "getValueFromPickerUI() " + returnValue);
		return returnValue;
	}

	@Override
	public boolean isNodeFocusable() {
		return mApplicationClassInstance.isControllable(mContext, mCookie, IApplication.IGNORE_VALUE);
	}

	private void setValueInPickerUI(int value) {
		int firstDigit = 0;
		int decimalDigits = 0;

		Log.d(TAG, "setValueInPickerUI(): " + value);

		firstDigit = value / 100;
		decimalDigits = value - (firstDigit * 100);

		/*pickerLeft.setCurrValue(normalizeString(firstDigit, 3));
		pickerRight.setCurrValue(normalizeString(decimalDigits, 2));*/
		pickerLeft.setCurrValue(firstDigit);
		pickerRight.setCurrValue(decimalDigits);

	}

	private String normalizeString(int value, int charCount) {
		String returnString = "";
		returnString = String.valueOf(value);

		for (int index = 0; index < charCount; index++) {
			if (returnString.length() < charCount) {
				returnString = "0" + returnString;
			} else {
				break;
			}
		}
		return returnString;
	}

	public void ReloadValues() {
		String caseString = "";
		int pickerValue = 0;

		pickerValue = nwrap.getNetworkFrequency();
		setValueInPickerUI(pickerValue);

		Log.d(TAG, "ReloadValues(): " + caseString + " : " + pickerValue);
	}

	public void CommitValues() {
		String caseString = "";
		int pickerValue = 0;

			if(ifEditedByUser){
				pickerValue = getValueFromPickerUI();
				nwrap.setNetworkFrequency(pickerValue);
				ifEditedByUser = false;
			}
		Log.d(TAG, "CommitValues " + caseString + " " + pickerValue);
	}

	private boolean onKeyRight() {
		Log.d(TAG, "onKeyRight entry");
		boolean l_ret = false;
		View currentFocus;

		currentFocus = ((Activity) mContext).getCurrentFocus();

		switch (currentFocus.getId()) {
		case R.id.settings_button_cancel:
			doneButton.requestFocus();
			l_ret = true;
			break;
		case R.id.settings_button_done:
			l_ret = true;
			break;
		case R.id.settings_picker_left:
			pickerRight.requestFocus();
			l_ret = true;
			break;
		case R.id.settings_picker_right:
			doneButton.requestFocus();
			l_ret = true;
			break;
		}

		Log.d(TAG, "onKeyRight returning " + l_ret);
		return l_ret;
	}

	@Override
	public void onInputPickerValueEntered(int mCurrValue) {
		Log.d(TAG, "onInputPickerValueConfirm");
		onKeyRight();
	}

	@Override
	public void onInputPickerValueConfirm(int mCurrValue) {
		Log.d(TAG, "onInputPickerValueEntered");
		onKeyRight();
	}

	@Override
	public void setFocus(Boolean focus) {
		Log.d(TAG, "setFocus " + focus);
		// super.setFocus(focus);
		if (focus) {
			if(cancelButton != null){
				cancelButton.setVisibility(View.VISIBLE);
			}
			
			if( doneButton != null){
				doneButton.setVisibility(View.VISIBLE);
			}
			
			// show buttons
			retView.requestFocus();
			
		}else{
			// hide buttons
			if(cancelButton != null){
				cancelButton.setVisibility(View.INVISIBLE);
			}
			
			if( doneButton != null){
				doneButton.setVisibility(View.INVISIBLE);
			}
			
		}
		ReloadValues();
	}

	@Override
	public void setVisible(boolean visible) {
		Log.d(TAG, "setVisible");
		super.setVisible(visible);
	}

	@Override
	public boolean isControllable() {
		Log.d(TAG, "isControllable");
		boolean controllable = super.isControllable();

		if (pickerLeft != null) {
			pickerLeft.setEnabled(controllable);
			pickerRight.setEnabled(controllable);
			cancelButton.setEnabled(controllable);
			doneButton.setEnabled(controllable);
		}

		return controllable;
	}

	@Override
	public View getView(Context ctx) {
		Log.d(TAG, "getView " + retView);
		return retView;
	}

	@Override
	public View getNodeView() {
		// TODO Auto-generated method stub
		Log.d(TAG, "getNodeView");
		return super.getNodeView();
	}

	@Override
	public void refreshView() {
		// TODO Auto-generated method stub
		Log.d(TAG, "refreshView");
		super.refreshView();
	}

	@Override
	public boolean handleKeyEvent(KeyEvent event) {
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		Boolean handled = false;

		View currentFocus;
		currentFocus = ((Activity) mContext).getCurrentFocus();

		Log.d(TAG, "handleKeyEvent keyCode:" + keyCode + " ,keyAction:" + keyAction);
		switch (keyCode) {
		case KeyEvent.KEYCODE_DPAD_LEFT:
		case KeyEvent.KEYCODE_SOFT_LEFT:
			if (keyAction == KeyEvent.ACTION_DOWN) {
				switch (currentFocus.getId()) {
				case R.id.settings_button_cancel:
					pickerLeft.requestFocus();
					handled = true;
					break;
				case R.id.settings_button_done:
					cancelButton.requestFocus();
					handled = true;
					break;
				case R.id.settings_picker_left:
					// handle
					getMenuBuilder().removeFocus();
					handled = true;
					break;
				case R.id.settings_picker_right:
					pickerLeft.requestFocus();
					handled = true;
					break;
				}
			} else {
				handled = true;
			}
			break;
		case KeyEvent.KEYCODE_DPAD_RIGHT:
		case KeyEvent.KEYCODE_SOFT_RIGHT:
			if (keyAction == KeyEvent.ACTION_DOWN) {

				handled = onKeyRight();
			} else {
				handled = true;
			}

			break;
		case KeyEvent.KEYCODE_DPAD_UP:
			if (keyAction == KeyEvent.ACTION_DOWN) {
				if (currentFocus instanceof Button) {
					pickerLeft.requestFocus();
					handled = true;
				} else {
					handled = true;
				}
			} else {
				handled = true;
			}
			break;
		case KeyEvent.KEYCODE_DPAD_DOWN:
			if (keyAction == KeyEvent.ACTION_DOWN) {
				if (currentFocus instanceof InputPicker) {
					doneButton.requestFocus();
					handled = true;
				}
			} else {
				handled = true;
			}
			break;
		}
		return handled;
	}

}
