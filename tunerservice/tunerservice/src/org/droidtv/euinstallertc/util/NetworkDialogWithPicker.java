package org.droidtv.euinstallertc.util;

import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueConfirmation;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueEntered;

import android.app.Dialog;
import android.content.Context;
import android.util.Log;
import android.view.FocusFinder;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.Button;

public class NetworkDialogWithPicker extends Dialog implements IInputPickerValueConfirmation, IInputPickerValueEntered {
	private static final String TAG = NetworkDialogWithPicker.class.getName();
	private Button skipButton;
	private Button doneButton;

	public void registerButtonInstance(Button skip, Button done) {
		skipButton = skip;
		doneButton = done;
	}

	public NetworkDialogWithPicker(Context context) {
		super(context);
		Log.d(TAG, "DialogWithDigit");
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setCancelable(false);
	}

	private boolean onKeyRight() {
		Log.d(TAG, "onKeyRight entry");
		boolean handled = false;
		View currentFocus;
		View rightFocus = null;

		currentFocus = getCurrentFocus();
		if (currentFocus != null) {
			rightFocus = FocusFinder.getInstance().findNextFocus((ViewGroup) currentFocus.getParent(), currentFocus, View.FOCUS_RIGHT);
		}

		if (currentFocus instanceof Button) {
			if (rightFocus == null) {
				handled = true;
			} else {
				rightFocus.requestFocus();
				handled = true;
			}
		} else if (currentFocus instanceof InputPicker) {
			if (rightFocus != null && rightFocus.getVisibility() == View.VISIBLE && (rightFocus instanceof InputPicker)) {
				rightFocus.requestFocus();
				handled = true;
			} else {
				if(doneButton != null){
					doneButton.requestFocus();
					handled = true;
				}
			}
		}

		Log.d(TAG, "onKeyRight returning " + handled);
		return handled;
	}

	@Override
	public void onInputPickerValueEntered(int val) {
		Log.d(TAG, "onInputPickerValueEntered " + val);
		onKeyRight();
	}

	@Override
	public void onInputPickerValueConfirm(int val) {
		Log.d(TAG, "onInputPickerValueConfirm " + val);
		onKeyRight();
	}

	public boolean handleKeyEvent(KeyEvent event) {
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		Boolean handled = false;

		View currentFocus;
		View upFocus = null;

		currentFocus = getCurrentFocus();
		if (currentFocus != null) {
			upFocus = FocusFinder.getInstance().findNextFocus((ViewGroup) currentFocus.getParent(), currentFocus, View.FOCUS_UP);
		}

		switch (keyCode) {
		case KeyEvent.KEYCODE_DPAD_LEFT:
		case KeyEvent.KEYCODE_SOFT_LEFT:
		case KeyEvent.KEYCODE_DPAD_CENTER:
		case KeyEvent.KEYCODE_DPAD_DOWN:
			handled = false;
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
			if (keyAction == KeyEvent.ACTION_UP) {
				if (currentFocus instanceof Button) {
					upFocus.requestFocus();
					handled = true;
				} else {
					handled = true;
				}
			} else {
				handled = true;
			}
			break;
		default:
			handled = true;
			break;
		}
		return handled;
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		Log.d(TAG, "dispatchKeyEvent for RalativeLayoutView");
		Log.d(TAG, String.valueOf(event.getAction()));
		Boolean handle = false;
		
		handle = super.dispatchKeyEvent(event);
		if (handle == false) {
			handle = handleKeyEvent(event);
		}
		return handle;
	}
}
