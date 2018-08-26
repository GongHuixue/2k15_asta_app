package org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.screen;

import java.util.ArrayList;
import java.util.List;
import java.util.Observable;

import org.droidtv.euinstallersat.model.mwapi.LnbSettingsEntry;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.satip.SatIPWrapper;
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

public class SettingsScreen extends WizardStep implements ConnTypeScreen
{

	private final String TAG = SettingsScreen.class.getName();
	private Context m_context;
	private ConnTypeWizard m_connTypeWizard;
	private NativeAPIWrapper m_wrapper;
	private SatIPWrapper m_satipwrapper;
	private RadioSelector m_radioSelector;
	private NotificationHandler m_ntfHandler;
	
	private final int MAIN_1_SATELLITE = 0;
	private final int MAIN_2_SATELLITES = 1;
	private final int MAIN_4_SATELLITE = 2;
	private final int MAIN_UNICABLE_1_SATELLITE = 3;
	private final int MAIN_UNICABLE_2_SATELLITE = 4;
	private final int MAIN_SAT_IP = 5;

	public SettingsScreen(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		m_context = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		m_ntfHandler = NotificationHandler.getInstance();
		m_satipwrapper = SatIPWrapper.getInstance();
		loadLayout(context);
	}

	public SettingsScreen(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public SettingsScreen(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		
		View l_view;
		l_view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		addView(l_view);

		m_radioSelector = (RadioSelector) l_view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		m_radioSelector.setOnKeyListener(this);

		OnClickListener buttonCancel_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				launchPreviousScreen(true);
			}
		};

		OnClickListener buttonPrevious_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				launchPreviousScreen(true);
			}
		};

		OnClickListener buttonNext_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				int selectedItem = m_radioSelector.getCheckedItemPosition();
				int index = 0;
				m_wrapper.setSatInstallationCount(selectedItem);
				switch (selectedItem)
				{
					case MAIN_1_SATELLITE:
						m_wrapper.SetTypeOfLNB(LnbSettingsEntry.LnbConnectionSingle);
						launchPreviousScreen(false);
						break;
					case MAIN_2_SATELLITES:
						m_wrapper.SetTypeOfLNB(LnbSettingsEntry.LnbConnectionDiSeqcMini);
						// default all selected
						for(index = 0;index<4;index++){
							m_wrapper.setPrescanLNBs(index,true);
						}
						launchWizardSettings();
						break;
					case MAIN_4_SATELLITE:
						m_wrapper.SetTypeOfLNB(LnbSettingsEntry.LnbConnectionDiSeqc1_0);
						// default all selected
						for(index = 0;index<4;index++){
							m_wrapper.setPrescanLNBs(index,true);
						}
						launchWizardSettings();
						break;
					case MAIN_UNICABLE_1_SATELLITE:
						m_wrapper.SetTypeOfLNB(LnbSettingsEntry.LnbConnectionUnicableLnb);
						m_connTypeWizard.launchScreen(ConnTypeScreenReq.UNICABLEUBN, getScreenName());
						break;
					case MAIN_UNICABLE_2_SATELLITE:
						m_wrapper.SetTypeOfLNB(LnbSettingsEntry.LnbConnectionUnicableSwitch);
						m_connTypeWizard.launchScreen(ConnTypeScreenReq.UNICABLEUBN, getScreenName());
						break;
					case MAIN_SAT_IP:
						m_wrapper.SetTypeOfLNB(LnbSettingsEntry.LnbConnectionSatIP);
						launchPreviousScreen(false);
						break;

				}
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
		setHintText(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_CONNECTION_TYPE));
	}
	
	private void launchWizardSettings()
	{
		Intent l_intent;
		l_intent = new Intent(m_context, WizardSettingsActivity.class);
		((Activity) m_context).finish(); 
		m_context.startActivity(l_intent);
	}
	
	private void launchPreviousScreen(boolean p_isResetNeeded)
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
		return ConnTypeScreenReq.SETTINGS;
	}

	@Override
	public void screenIntialization()
	{
		List<String> connectionTypeList =new ArrayList<String>();
		
		connectionTypeList.add(	m_context.getString(org.droidtv.ui.strings.R.string.MAIN_1_SATELLITE));
		connectionTypeList.add(	m_context.getString(org.droidtv.ui.strings.R.string.MAIN_2_SATELLITES));
		connectionTypeList.add(	m_context.getString(org.droidtv.ui.strings.R.string.MAIN_4_SATELLITES));
		connectionTypeList.add(	m_context.getString(org.droidtv.ui.strings.R.string.MAIN_UNICABLE_1_SATELLITE));
		connectionTypeList.add(	m_context.getString(org.droidtv.ui.strings.R.string.MAIN_UNICABLE_2_SATELLITES));
		
		if(m_satipwrapper.ifSatIPServerDetectedOnBoot()){
			connectionTypeList.add(	m_context.getString(org.droidtv.tunerservice.R.string.MAIN_SAT_IP));
		}
		
		m_radioSelector.setArray(connectionTypeList.toArray(new String[connectionTypeList.size()]));
		int l_focusIdx = getCurrentFocusIdx();
		m_radioSelector.setItemChecked(l_focusIdx, true);
		m_radioSelector.setSelection(l_focusIdx);
		m_radioSelector.requestFocus();
	}
	
	private int getCurrentFocusIdx()
	{
		int l_idx = 0;
		int l_currentConnType = m_wrapper.getConnectionType();
		switch(l_currentConnType)
		{
			case LnbSettingsEntry.LnbConnectionSingle:
				l_idx = MAIN_1_SATELLITE;
				break;
			case LnbSettingsEntry.LnbConnectionDiSeqcMini:
				l_idx = MAIN_2_SATELLITES;
				break;
			case LnbSettingsEntry.LnbConnectionDiSeqc1_0:
				l_idx = MAIN_4_SATELLITE;
				break;
			case LnbSettingsEntry.LnbConnectionUnicableLnb:
				l_idx = MAIN_UNICABLE_1_SATELLITE;
				break;
			case LnbSettingsEntry.LnbConnectionUnicableSwitch:
				l_idx = MAIN_UNICABLE_2_SATELLITE;
				break;
			
				
		}
		Log.d(TAG," getCurrentFocusIdx returning" + l_idx);
		return l_idx;
		
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
				m_ntfHandler.notifyAllObservers(EventIDs.WIZARD_SETTINGS_EXIT,"");
			}
     	   
        }
		
		return super.dispatchKeyEvent(event);
	}




}
