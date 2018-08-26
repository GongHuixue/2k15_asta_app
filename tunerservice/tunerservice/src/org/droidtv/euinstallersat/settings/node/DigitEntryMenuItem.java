package org.droidtv.euinstallersat.settings.node;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.settings.node.view.DigitEntryView;
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
import android.widget.RelativeLayout;


public class DigitEntryMenuItem extends MenuItem implements IViewListener, OnClickListener, IInputPickerValueEntered, IInputPickerValueConfirmation,IMenuNodeControl
{
	private static final String TAG = DigitEntryMenuItem.class.getName();
	private Context m_context;
	
	private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();
	private RelativeLayout retView;
	private Button m_buttonDone;
	private Button m_buttonCancel;

	private InputPicker pickerLeft;

	public DigitEntryMenuItem(Context context, AttributeSet attrs, ResourceHelper reshelp)
	{
		super(context, attrs, reshelp);
		m_context = context;
		
		//retView.addListener(this);
		LayoutInflater inflater = (LayoutInflater) m_context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		
		retView = (RelativeLayout) inflater.inflate(R.layout.ws_digitentry_holder_layout, null);
		
		DigitEntryView l_digitEntryView = (DigitEntryView) retView.findViewById(R.id.digitEntryView1);
		l_digitEntryView.addListener(this);
		
		
		m_buttonCancel = (Button) retView.findViewById(R.id.ws_button_cancel);
		m_buttonDone = (Button) retView.findViewById(R.id.ws_button_done);
		
		m_buttonCancel.setOnClickListener(this);
		m_buttonDone.setOnClickListener(this);
				
		initPickerArray();

	}
	
	private void initPickerArray()
	{
	
		pickerLeft = (InputPicker) retView.findViewById(R.id.settings_picker_left);
		pickerLeft.setMaxValue(99999);
		pickerLeft.setMinValue(0);
		pickerLeft.enableLeandingZero(true);

		pickerLeft.setValueConfirmListener(this);
		pickerLeft.setValueEnteredListener(this);

	}
	

	private int getValueFromPickerUI()
	{
		int l_retVal = pickerLeft.getCurrValue();
		Log.d(TAG, "getValueFromPickerUI() " + l_retVal + " " + getId());
		return l_retVal;
	}

	private void setValueInPickerUI(int p_value)
	{
		pickerLeft.setCurrValue(p_value);
			
		Log.d(TAG, "DigitEntryNode.setValueInPickerUI(): " + p_value);
	}
	
	@Override
	public boolean isNodeFocusable()
	{
		return mApplicationClassInstance.isControllable(mContext, mCookie, IApplication.IGNORE_VALUE);
	}
	
	@Override
	public void setFocus(Boolean focus)
	{
		Log.d(TAG, "setFocus " + focus);
		// super.setFocus(focus);
		if (focus)
		{
			
			if(m_buttonCancel != null){
				m_buttonCancel.setVisibility(View.VISIBLE);
			}
			
			if( m_buttonDone != null){
				m_buttonDone.setVisibility(View.VISIBLE);
			}
			retView.requestFocus();
		} 
		else
		{
			// hide buttons
			if(m_buttonCancel != null){
				m_buttonCancel.setVisibility(View.INVISIBLE);
			}
			
			if( m_buttonDone != null){
				m_buttonDone.setVisibility(View.INVISIBLE);
			}

		}
		reloadValues();
	}

	@Override
	public void setVisible(boolean visible)
	{
		// TODO Auto-generated method stub
		Log.d(TAG, "setVisible");
		super.setVisible(visible);
	}

	@Override
	public boolean isAvailable()
	{
		// TODO Auto-generated method stub
		Log.d(TAG, "isAvailable");
		return true;
	}

	@Override
	public boolean isControllable()
	{
		Log.d(TAG, "isControllable");
		boolean controllable = super.isControllable();

		/*if (pickerLeft != null) {
			pickerLeft.setEnabled(controllable);
			pickerRight.setEnabled(controllable);
			cancelButton.setEnabled(controllable);
			doneButton.setEnabled(controllable);
		}*/

		return controllable;
	}

	@Override
	public View getView(Context pContext) {
		Log.d(TAG, "getView " + retView);
		reloadValues();
		return encapsulateWithEasyPQ(retView);
	}

	@Override
	public View getNodeView()
	{
		// TODO Auto-generated method stub
		Log.d(TAG, "getNodeView");
		return super.getNodeView();
	}

	@Override
	public void refreshView()
	{
		// TODO Auto-generated method stub
		Log.d(TAG, "refreshView");
		super.refreshView();
	}

	public void reloadValues()
	{
		int l_pickerValue = 0;
		switch(getId())
		{
			case R.id.MAIN_SYMBOL_RATE:
				l_pickerValue = m_wrapper.GetSymbolRate();
				break;
			case R.id.CD_HOMING_SYMBOL_RATE:
				l_pickerValue = m_wrapper.GetSymbolRateForCDHomingTransponder();
				break;
			case R.id.MAIN_HOMING_TRANSPONDER:
			case R.id.MAIN_CH_SAT_HOMING_FREQUENCY:
				Log.d(TAG,"calling GetFreqForCDHomingTransponder");
				l_pickerValue = m_wrapper.GetFreqForCDHomingTransponder();
				break;
			case R.id.CD_LNB_ONE_LOW_FREQ:
				Log.d(TAG,"reloadvalues GetLnbLowLoFrequency(0)");
				l_pickerValue = m_wrapper.getLnbLowLoFrequency(0,false);
			break;
			case R.id.CD_LNB_TWO_LOW_FREQ:
				Log.d(TAG,"reloadvalues GetLnbLowLoFrequency(1)");
				l_pickerValue = m_wrapper.getLnbLowLoFrequency(1,false);
			break;
			case R.id.CD_LNB_THREE_LOW_FREQ:
				Log.d(TAG,"reloadvalues GetLnbLowLoFrequency(2)");
				l_pickerValue = m_wrapper.getLnbLowLoFrequency(2,false);
			break;
			case R.id.CD_LNB_FOUR_LOW_FREQ:
				Log.d(TAG,"reloadvalues GetLnbLowLoFrequency(3)");
				l_pickerValue = m_wrapper.getLnbLowLoFrequency(3,false);
			break;
			case R.id.CD_LNB_ONE_HIGH_FREQ:
				Log.d(TAG,"reloadvalues GetLnbHighLoFrequency(0)");
				l_pickerValue = m_wrapper.getLnbHighLoFrequency(0,false);
			break;
			case R.id.CD_LNB_TWO_HIGH_FREQ:
				Log.d(TAG,"reloadvalues GetLnbHighLoFrequency(1)");
				l_pickerValue = m_wrapper.getLnbHighLoFrequency(1,false);
			break;
			case R.id.CD_LNB_THREE_HIGH_FREQ:
				Log.d(TAG,"reloadvalues GetLnbHighLoFrequency(2)");
				l_pickerValue = m_wrapper.getLnbHighLoFrequency(2,false);
			break;
			case R.id.CD_LNB_FOUR_HIGH_FREQ:
				Log.d(TAG,"reloadvalues GetLnbHighLoFrequency(3)");
				l_pickerValue = m_wrapper.getLnbHighLoFrequency(3,false);
			break;
			case R.id.CD_LNB_ONE_LOW_FREQ_MAIN_MENU:
				Log.d(TAG,"reloadvalues GetLnbLowLoFrequency(0)");
				l_pickerValue = m_wrapper.getLnbLowLoFrequency(0,true);
			break;
			case R.id.CD_LNB_TWO_LOW_FREQ_MAIN_MENU:
				Log.d(TAG,"reloadvalues GetLnbLowLoFrequency(1)");
				l_pickerValue = m_wrapper.getLnbLowLoFrequency(1,true);
			break;
			case R.id.CD_LNB_THREE_LOW_FREQ_MAIN_MENU:
				Log.d(TAG,"reloadvalues GetLnbLowLoFrequency(2)");
				l_pickerValue = m_wrapper.getLnbLowLoFrequency(2,true);
			break;
			case R.id.CD_LNB_FOUR_LOW_FREQ_MAIN_MENU:
				Log.d(TAG,"reloadvalues GetLnbLowLoFrequency(3)");
				l_pickerValue = m_wrapper.getLnbLowLoFrequency(3,true);
			break;
			case R.id.CD_LNB_ONE_HIGH_FREQ_MAIN_MENU:
				Log.d(TAG,"reloadvalues GetLnbHighLoFrequency(0)");
				l_pickerValue = m_wrapper.getLnbHighLoFrequency(0,true);
			break;
			case R.id.CD_LNB_TWO_HIGH_FREQ_MAIN_MENU:
				Log.d(TAG,"reloadvalues GetLnbHighLoFrequency(1)");
				l_pickerValue = m_wrapper.getLnbHighLoFrequency(1,true);
			break;
			case R.id.CD_LNB_THREE_HIGH_FREQ_MAIN_MENU:
				Log.d(TAG,"reloadvalues GetLnbHighLoFrequency(2)");
				l_pickerValue = m_wrapper.getLnbHighLoFrequency(2,true);
			break;
			case R.id.CD_LNB_FOUR_HIGH_FREQ_MAIN_MENU:
				Log.d(TAG,"reloadvalues GetLnbHighLoFrequency(3)");
				l_pickerValue = m_wrapper.getLnbHighLoFrequency(3,true);
			break;
		}
		setValueInPickerUI(l_pickerValue);		
		Log.d(TAG, "DigitEntryNode.ReloadValues() : " + l_pickerValue);
	}

	private boolean onKeyLeft()
	{
		Log.d(TAG,"onKeyLeft");
		boolean l_ret = true;
		Activity l_activity = (Activity) m_context;
		View l_focusView = l_activity.getCurrentFocus();
		switch (l_focusView.getId())
		{
			case R.id.ws_button_cancel:
				Log.d(TAG,"Left on cancel button");
				pickerLeft.requestFocus();
				break;
			case R.id.ws_button_done:
				m_buttonCancel.requestFocus();
				break;
			case R.id.settings_picker_left:
				Log.d(TAG,"Left on settings_picker_left");
				getMenuBuilder().removeFocus();
				//l_ret = false;
				break;
		}
		
		return l_ret;
		
	}
	
	
	private boolean onKeyRight()
	{
		Log.d(TAG,"onKeyRight");
		boolean l_ret = true;
		Activity l_activity = (Activity) m_context;
		View l_focusView = l_activity.getCurrentFocus();
		switch (l_focusView.getId())
		{
			case R.id.ws_button_cancel:
				m_buttonDone.requestFocus();
				l_ret = true;
				break;
			case R.id.settings_picker_left:
				m_buttonDone.requestFocus();
				break;
		}
		return l_ret;
	}

	@Override
	public boolean handleKeyEvent(KeyEvent event)
	{
		Log.d(TAG,"handleKeyEvent");
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		Boolean l_isHandled = false;

		View l_currentFocus;
		

		l_currentFocus = ((Activity) m_context).getCurrentFocus();
		

		switch (keyCode)
		{
			case KeyEvent.KEYCODE_DPAD_LEFT:
			case KeyEvent.KEYCODE_SOFT_LEFT:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					l_isHandled = onKeyLeft();
				} else
				{
					l_isHandled = true;
				}
				break;
			case KeyEvent.KEYCODE_DPAD_RIGHT:
			case KeyEvent.KEYCODE_SOFT_RIGHT:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					l_isHandled = onKeyRight();
				} else
				{
					l_isHandled = true;
				}

				break;
			case KeyEvent.KEYCODE_DPAD_UP:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					if (l_currentFocus instanceof Button)
					{
						pickerLeft.requestFocus();
						l_isHandled = true;
					} else
					{
						l_isHandled = true;
					}
				} else
				{
					l_isHandled = true;
				}
				break;
			case KeyEvent.KEYCODE_DPAD_DOWN:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					if (l_currentFocus instanceof InputPicker)
					{
						m_buttonDone.requestFocus();
						l_isHandled = true;
					}
				} else
				{
					l_isHandled = true;
				}
				break;
		}
		return l_isHandled;
	}
	
	
	@Override
	public void onClick(View v)
	{
		Log.d(TAG, " onClick ");
		switch (v.getId())
		{
			case R.id.ws_button_cancel:
				reloadValues();
				getMenuBuilder().removeFocus();
				break;
			case R.id.ws_button_done:
				int l_pickerValue = 0;
				l_pickerValue = getValueFromPickerUI();
				switch(getId())
				{
					case R.id.MAIN_SYMBOL_RATE:
						m_wrapper.SetSymbolRate(l_pickerValue);
						l_pickerValue = m_wrapper.GetSymbolRate();
						break;
					case R.id.CD_HOMING_SYMBOL_RATE:
						m_wrapper.SetSymbolRateForCDHomingTransponder(l_pickerValue);
						l_pickerValue = m_wrapper.GetSymbolRateForCDHomingTransponder();
						break;
					case R.id.MAIN_HOMING_TRANSPONDER:
					case R.id.MAIN_CH_SAT_HOMING_FREQUENCY:
						    m_wrapper.SetFreqForCDHomingTransponder(l_pickerValue);
						    l_pickerValue = m_wrapper.GetFreqForCDHomingTransponder();
						break;
					case R.id.CD_LNB_ONE_LOW_FREQ:
							m_wrapper.setLnbLowLoFrequency(0,l_pickerValue,false);
							l_pickerValue = m_wrapper.getLnbLowLoFrequency(0,false);
						break;
					case R.id.CD_LNB_TWO_LOW_FREQ:
							m_wrapper.setLnbLowLoFrequency(1,l_pickerValue,false);
							l_pickerValue = m_wrapper.getLnbLowLoFrequency(1,false);
						break;
					case R.id.CD_LNB_THREE_LOW_FREQ:
							m_wrapper.setLnbLowLoFrequency(2,l_pickerValue,false);
							l_pickerValue = m_wrapper.getLnbLowLoFrequency(2,false);
						break;
					case R.id.CD_LNB_FOUR_LOW_FREQ:
							m_wrapper.setLnbLowLoFrequency(3,l_pickerValue,false);
							l_pickerValue = m_wrapper.getLnbLowLoFrequency(3,false);
						break;
					case R.id.CD_LNB_ONE_HIGH_FREQ:
							m_wrapper.setLnbHighLoFrequency(0,l_pickerValue,false);
							l_pickerValue = m_wrapper.getLnbHighLoFrequency(0,false);
						break;
					case R.id.CD_LNB_TWO_HIGH_FREQ:
							m_wrapper.setLnbHighLoFrequency(1,l_pickerValue,false);
							l_pickerValue = m_wrapper.getLnbHighLoFrequency(1,false);
						break;
					case R.id.CD_LNB_THREE_HIGH_FREQ:
							m_wrapper.setLnbHighLoFrequency(2,l_pickerValue,false);
							l_pickerValue = m_wrapper.getLnbHighLoFrequency(2,false);
						break;
					case R.id.CD_LNB_FOUR_HIGH_FREQ:
							m_wrapper.setLnbHighLoFrequency(3,l_pickerValue,false);
							l_pickerValue = m_wrapper.getLnbHighLoFrequency(3,false);
						break;
					case R.id.CD_LNB_ONE_LOW_FREQ_MAIN_MENU:
						m_wrapper.setLnbLowLoFrequency(0,l_pickerValue,true);
						l_pickerValue = m_wrapper.getLnbLowLoFrequency(0,true);
					break;
					case R.id.CD_LNB_TWO_LOW_FREQ_MAIN_MENU:
							m_wrapper.setLnbLowLoFrequency(1,l_pickerValue,true);
							l_pickerValue = m_wrapper.getLnbLowLoFrequency(1,true);
						break;
					case R.id.CD_LNB_THREE_LOW_FREQ_MAIN_MENU:
							m_wrapper.setLnbLowLoFrequency(2,l_pickerValue,true);
							l_pickerValue = m_wrapper.getLnbLowLoFrequency(2,true);
						break;
					case R.id.CD_LNB_FOUR_LOW_FREQ_MAIN_MENU:
							m_wrapper.setLnbLowLoFrequency(3,l_pickerValue,true);
							l_pickerValue = m_wrapper.getLnbLowLoFrequency(3,true);
						break;
					case R.id.CD_LNB_ONE_HIGH_FREQ_MAIN_MENU:
							m_wrapper.setLnbHighLoFrequency(0,l_pickerValue,true);
							l_pickerValue = m_wrapper.getLnbHighLoFrequency(0,true);
						break;
					case R.id.CD_LNB_TWO_HIGH_FREQ_MAIN_MENU:
							m_wrapper.setLnbHighLoFrequency(1,l_pickerValue,true);
							l_pickerValue = m_wrapper.getLnbHighLoFrequency(1,true);
						break;
					case R.id.CD_LNB_THREE_HIGH_FREQ_MAIN_MENU:
							m_wrapper.setLnbHighLoFrequency(2,l_pickerValue,true);
							l_pickerValue = m_wrapper.getLnbHighLoFrequency(2,true);
						break;
					case R.id.CD_LNB_FOUR_HIGH_FREQ_MAIN_MENU:
							m_wrapper.setLnbHighLoFrequency(3,l_pickerValue,true);
							l_pickerValue = m_wrapper.getLnbHighLoFrequency(3,true);
						break;
				}
				setValueInPickerUI(l_pickerValue);
				getMenuBuilder().removeFocus();
				break;
		}
	}
	
	@Override
	public void onInputPickerValueConfirm(int p_currValue)
	{
		Log.d(TAG,"onInputPickerValueConfirm");
		onKeyRight();
		
	}
	
	@Override
	public void onInputPickerValueEntered(int p_currValue)
	{
		Log.d(TAG,"onInputPickerValueEntered");
		onKeyRight();
		
	}


}
