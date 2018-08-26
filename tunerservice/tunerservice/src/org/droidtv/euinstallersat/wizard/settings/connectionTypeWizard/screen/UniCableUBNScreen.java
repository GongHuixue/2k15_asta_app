package org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.screen;

import java.util.Observable;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.settings.WizardSettingsActivity;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeScreen;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeWizard;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeWizard.ConnTypeScreenReq;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class UniCableUBNScreen extends WizardStep implements ConnTypeScreen
{

	private final String TAG = UniCableUBNScreen.class.getName();
	private Context m_context;
	private ConnTypeWizard m_connTypeWizard;
	private NativeAPIWrapper m_wrapper;
	private RadioSelector m_radioSelector;

	public UniCableUBNScreen(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		m_context = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		loadLayout(context);
	}

	public UniCableUBNScreen(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public UniCableUBNScreen(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View l_view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		addView(l_view);

		m_radioSelector = (RadioSelector) l_view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		m_radioSelector.setOnKeyListener(this);

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
				int ubnId = m_radioSelector.getCheckedItemPosition();
				m_wrapper.SetUnicableUBNumber(ubnId);
				m_connTypeWizard.launchScreen(ConnTypeScreenReq.UNICABLEUBF, getScreenName());
			}
		};
		
		m_radioSelector.setOnItemClickListener(new OnItemClickListener()
		{

			@Override
			public void onItemClick(AdapterView<?> arg0, View view, int selectedItem, long arg3)
			{
				Log.d(TAG, "selectedItem:" + selectedItem);
				setButton3focussed();
			}

		});
		
		String l_btnNext_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);
		
		setButton1(l_btnCancel_txt, buttonCancel_Listener, VISIBLE);
		setButton2(l_btnPrev_txt, buttonPrevious_Listener, VISIBLE);
		setButton3(l_btnNext_txt, buttonNext_Listener, VISIBLE);
		setHintText(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_UB_NUMBER));
	}
	
	private void launchWizardSettings()
	{
		Intent l_intent;
		l_intent = new Intent(m_context, WizardSettingsActivity.class);
		((Activity) m_context).finish();
		m_context.startActivity(l_intent);
	}


	@Override
	public void update(Observable observable, Object data)
	{
	}

	@Override
	public void setInstance(ConnTypeWizard wizard)
	{
		m_connTypeWizard = wizard;
	}

	@Override
	public ConnTypeScreenReq getScreenName()
	{
		return ConnTypeScreenReq.UNICABLEUBN;
	}

	@Override
	public void screenIntialization()
	{
		
		
		if(m_wrapper.GetIsNordicCountry())
		{
			String[] l_ubnStrNordic = { m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB1), 
										m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB2),
										m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB3), 
										m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB4), 
										m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB5),
										m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB6), 
										m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB7), 
										m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB8) };
			m_radioSelector.setArray(l_ubnStrNordic);
		}
		else
		{
			String[] l_ubnStr = { m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB0), 
					  m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB1),
					  m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB2), 
					  m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB3), 
					  m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB4),
					  m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB5), 
					  m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB6), 
					  m_context.getString(org.droidtv.ui.strings.R.string.MISC_UB7) };
			m_radioSelector.setArray(l_ubnStr);
		}
		int ubnId = m_wrapper.GetUnicableUBNumber();
		m_radioSelector.setItemChecked(ubnId, true);
		m_radioSelector.setSelection(ubnId);
		m_radioSelector.requestFocus();
	}
	
	@Override
    public boolean onKey(View view, int keyCode, KeyEvent event)
    {

           Log.d(TAG,"OnKey");
           boolean l_isKeyHandled = false;
           if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
           {
                  Log.d(TAG,"KEYCODE_DPAD_RIGHT");
                  if(m_radioSelector == view)
                  {
                        setButton3focussed();
                  }
				  else
				  {
					super.onKey(view, keyCode, event);
				  }
                  l_isKeyHandled = true;
           }
           else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
           {
                  Log.d(TAG,"KEYCODE_DPAD_LEFT");
                  if(m_radioSelector == view)
                  {
                        setButton1focussed();
                  }
				  else
				  {
					super.onKey(view, keyCode, event);
				  }
                  l_isKeyHandled = true;
           }
           else if (keyCode == KeyEvent.KEYCODE_DPAD_UP && event.getAction() == KeyEvent.ACTION_DOWN)
           {
        	   Log.d(TAG,"KEYCODE_DPAD_UP");
               if(m_radioSelector != view)
               {
            	   int l_selIdx = m_radioSelector.getCheckedItemPosition();
            	   m_radioSelector.setSelection(l_selIdx);
            	   m_radioSelector.smoothScrollToPosition(l_selIdx);
            	   m_radioSelector.requestFocus();
               }
           }
           Log.d(TAG,"OnKey returning " + l_isKeyHandled);
           return l_isKeyHandled;

    }
	
	@Override
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
				NotificationHandler.getInstance().notifyAllObservers(EventIDs.WIZARD_SETTINGS_EXIT,"");
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
			NotificationHandler.getInstance().notifyAllObservers(EventIDs.WIZARD_SETTINGS_EXIT,"");
		}
	}

}
