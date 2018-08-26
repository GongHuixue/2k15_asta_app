package org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.settings.WizardSettingsActivity;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeScreen;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeWizard;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeWizard.ConnTypeScreenReq;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnFocusChangeListener;
import android.widget.TextView;

public class UniCableUBFScreen extends WizardStep implements ConnTypeScreen, OnFocusChangeListener
{

	private static final String TAG = UniCableUBFScreen.class.getName();
	
	private int FOCUS_PICKER = 0;
	private int FOCUS_BUTTON = 1;
	private int m_focusWidget = FOCUS_PICKER;
	private int NUM_PICKER = 7;
	private int m_focusPicker = 0;
	
	private Context m_context;
	

	
	private TextView[] m_digit_array = new TextView[7];
		
	
	private TextView m_min_txtVw;
	private TextView m_max_txtVw;
	
	private View m_textBg;
	private View m_textBgFocus;
	
	private NativeAPIWrapper m_wrapper;
	private NotificationHandler m_ntfHandler;
	private ConnTypeWizard m_connTypeWizard;

	public UniCableUBFScreen(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		m_context = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		m_ntfHandler = NotificationHandler.getInstance();
	//	m_wrapper.setDualTuner(0);
		loadLayout(context);
	}

	public UniCableUBFScreen(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public UniCableUBFScreen(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{

		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View l_view = inflater.inflate(R.layout.unicableubfscreen, null);
		m_min_txtVw = (TextView) l_view.findViewById(R.id.minimum);
		m_max_txtVw = (TextView) l_view.findViewById(R.id.maximum);
		m_textBg = (View)l_view.findViewById(R.id.bg);
		m_textBgFocus = (View)l_view.findViewById(R.id.bg_focused);
		String l_mhzText = context.getString(org.droidtv.ui.strings.R.string.MISC_MHZ);
		String l_minText = context.getString(org.droidtv.ui.strings.R.string.MAIN_MINIMUM_SHORT);
		String l_maxText = context.getString(org.droidtv.ui.strings.R.string.MAIN_MAXIMUM_SHORT);
		m_min_txtVw.setText(l_minText + ": 0950.000 " + l_mhzText);
		m_max_txtVw.setText(l_maxText + ": 2150.000 " + l_mhzText);
		initFrequencyPicker(l_view);
		l_view.requestFocus();
		m_digit_array[0].requestFocus();
		m_focusWidget = FOCUS_PICKER;
		addView(l_view);

		OnClickListener buttonCancel_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				exitOnFinish(true);
			}
		};

		OnClickListener buttonPrevious_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				m_connTypeWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonNext_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				m_wrapper.SetUnicableUBFreq(getDisplayedFrequency());
				if(m_wrapper.IsDualTunerOn())
				{
					m_connTypeWizard.launchScreen(ConnTypeScreenReq.UNICABLEUBN2, getScreenName());
				}
				else
				{
					exitOnFinish(false);
					
				}
			}
		};
		
		String l_btnNext_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);
		
		setButton1(l_btnCancel_txt, buttonCancel_Listener, VISIBLE);
		setButton2(l_btnPrev_txt, buttonPrevious_Listener, VISIBLE);
		setButton3(l_btnNext_txt, buttonNext_Listener, VISIBLE);
		setHintText(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_UB_FREQUENCY));
	}
	
	private void launchWizardSettings()
	{
		Intent l_intent;
		l_intent = new Intent(m_context, WizardSettingsActivity.class);
		((Activity) m_context).finish();
		m_context.startActivity(l_intent);
	}


	private void initFrequencyPicker(View view)
	{
		Log.d(TAG, "initialising views for frequency entry");
		int l_idx;
		m_digit_array[0] = (TextView) view.findViewById(R.id.digit1);
		m_digit_array[1] = (TextView) view.findViewById(R.id.digit2);
		m_digit_array[2] = (TextView) view.findViewById(R.id.digit3);
		m_digit_array[3] = (TextView) view.findViewById(R.id.digit4);
		m_digit_array[4] = (TextView) view.findViewById(R.id.digit5);
		m_digit_array[5] = (TextView) view.findViewById(R.id.digit6);
		m_digit_array[6] = (TextView) view.findViewById(R.id.digit7);
		
		for(l_idx = 0;l_idx < NUM_PICKER; l_idx++)
		{
			m_digit_array[l_idx].setOnKeyListener(this);
			m_digit_array[l_idx].setFocusable(true);
			m_digit_array[l_idx].setOnFocusChangeListener(this);
		}
	}
	
	private int getDisplayedFrequency()
	{
		Log.d(TAG, "getDisplayedFrequency");
		int l_freq = 0;
		int l_idx;
		for (l_idx = 0; l_idx < NUM_PICKER; l_idx++)
		{
			l_freq = l_freq * 10 + Integer.valueOf(m_digit_array[l_idx].getText().toString());
		}
		Log.d(TAG, String.valueOf(l_freq));
		return l_freq;

	}

	private void setDisplayedFrequency(int p_freq)
	{

		int l_idx;
		Log.d(TAG, "setDisplayedFrequency " + p_freq);
		for (l_idx = NUM_PICKER - 1; l_idx >= 0; l_idx--)
		{

			m_digit_array[l_idx].setText(String.valueOf(p_freq % 10));
			p_freq = p_freq - p_freq % 10;
			p_freq = p_freq / 10;
			Log.d(TAG, String.valueOf(p_freq));
		}
	}


	@Override
	public void update(Observable observable, Object data)
	{

	}

	@Override
	public void setInstance(ConnTypeWizard p_wizard)
	{
		m_connTypeWizard = p_wizard;
	}

	@Override
	public ConnTypeScreenReq getScreenName()
	{
		return ConnTypeScreenReq.UNICABLEUBF;
	}
	
	private void setInputTextFocus(Boolean p_isFocused)
	{
		if(p_isFocused)
		{
			m_textBg.setVisibility(View.INVISIBLE);
			m_textBgFocus.setVisibility(View.VISIBLE);
		}
		else
		{
			m_textBg.setVisibility(View.VISIBLE);
			m_textBgFocus.setVisibility(View.INVISIBLE);
		}
	}

	@Override
	public void screenIntialization()
	{
		setDisplayedFrequency(m_wrapper.GetUnicableUBFreq());
		m_digit_array[0].requestFocus();
		setInputTextFocus(true);
		m_focusWidget = FOCUS_PICKER;
	}

	
	@Override
    public boolean onKey(View view, int keyCode, KeyEvent event)
    {
		Log.d(TAG,"onKey");
		boolean l_ret = false;
		int keyAction = event.getAction();
		switch (event.getKeyCode())
		{
			case KeyEvent.KEYCODE_DPAD_LEFT:
			case KeyEvent.KEYCODE_SOFT_LEFT:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					if (m_focusWidget == FOCUS_PICKER)
					{
						if (m_focusPicker != 0)
						{		
							m_focusPicker--;
							m_digit_array[m_focusPicker].requestFocus();
							Log.d(TAG, "new focus picker in left");
							Log.d(TAG, String.valueOf(m_focusPicker));		
							l_ret = true;
						}
					}	
					else
					{
						super.onKey(view, keyCode, event);
					}					
				}
				l_ret = true;
				break;
			case KeyEvent.KEYCODE_DPAD_RIGHT:
			case KeyEvent.KEYCODE_SOFT_RIGHT:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					if (m_focusWidget == FOCUS_PICKER)
					{
						if (m_focusPicker < (NUM_PICKER - 1))
						{
							m_focusPicker++;
							m_digit_array[m_focusPicker].requestFocus();
							Log.d(TAG, "new focus picker in right");
						}
						else
						{
							m_focusWidget = FOCUS_BUTTON;
							setInputTextFocus(false);
							setButton3focussed();
						}

					}
					else
					{
						super.onKey(view, keyCode, event);
					}
					Log.d(TAG, "new focus picker in right");
				}
				l_ret = true;
				break;
			case KeyEvent.KEYCODE_DPAD_DOWN:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					if (m_focusWidget == FOCUS_PICKER)
					{
						m_focusWidget = FOCUS_BUTTON;
						setInputTextFocus(false);
						setButton1focussed();
					}
				}
				l_ret = false;
				break;
			case KeyEvent.KEYCODE_DPAD_UP:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					if (m_focusWidget == FOCUS_BUTTON)
					{
						m_focusWidget = FOCUS_PICKER;
						m_focusPicker = 0;
						m_digit_array[0].requestFocus();
						setInputTextFocus(true);
						l_ret = true;
					}
					else
					{
						l_ret = false;
					}
					
				}
				break;
			
			case KeyEvent.KEYCODE_0:
			case KeyEvent.KEYCODE_1:
			case KeyEvent.KEYCODE_2:
			case KeyEvent.KEYCODE_3:
			case KeyEvent.KEYCODE_4:
			case KeyEvent.KEYCODE_5:
			case KeyEvent.KEYCODE_6:
			case KeyEvent.KEYCODE_7:
			case KeyEvent.KEYCODE_8:
			case KeyEvent.KEYCODE_9:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					String l_inputText;
					if (m_focusWidget == FOCUS_PICKER)
					{
						l_inputText = Character.toString(event.getNumber());
						Log.d(TAG,"l_inputText = " + l_inputText);
						m_digit_array[m_focusPicker].setText(l_inputText);
						if(m_focusPicker< (NUM_PICKER -1))
						{
							m_focusPicker++;
							m_digit_array[m_focusPicker].requestFocus();
						}
					}
				}
				break;
			
			default:
				Log.d(TAG, "passing key to base class");
				l_ret = false;
				break;

		}

		return l_ret;
	}
	
	
	
	

	
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		if((event.getKeyCode() == KeyEvent.KEYCODE_BACK) || (event.getKeyCode() == KeyEvent.KEYCODE_ESCAPE))
        {
     	   if(m_wrapper.GetIsNordicCountry())
			{
				launchWizardSettings();
			}
			else
			{
				m_wrapper.resetInstallation();
				m_ntfHandler.notifyAllObservers(EventIDs.WIZARD_SETTINGS_EXIT,"");
			}
     	   
        }
		
		return super.dispatchKeyEvent(event);
	}
	
	private void exitOnFinish(boolean p_isResetNeeded)
	{
		if(m_wrapper.GetIsNordicCountry())
		{
			launchWizardSettings();
		}
		else
		{
			if(p_isResetNeeded)
			{
				m_wrapper.resetInstallation();
			}
			((Activity) m_context).finish();
			m_ntfHandler.notifyAllObservers(EventIDs.WIZARD_SETTINGS_EXIT,"");
		}
	}

	@Override
	public void onFocusChange(View p_view, boolean p_isFocused)
	{
		if(p_view instanceof TextView)
		{
			if(p_isFocused == true)
			{
				((TextView)p_view).setTextColor(m_context.getResources().getColor(org.droidtv.ui.tvwidget2k15.R.color.highlight));
			}
			else
			{
				
				((TextView)p_view).setTextColor(m_context.getResources().getColor(org.droidtv.ui.tvwidget2k15.R.color.filter_disabled_focussed));
			}
		}
		
	}
}
