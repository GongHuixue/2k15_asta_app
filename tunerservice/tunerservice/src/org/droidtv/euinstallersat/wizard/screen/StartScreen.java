package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.LnbSettingsEntry;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.settings.WizardSettingsActivity;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.content.Context;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

public class StartScreen extends WizardStep implements SatelliteScreen
{

	private static final String TAG = StartScreen.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper m_wrapper;
	private TextView m_startInfoTxtVw;

	public StartScreen(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		layout(context);
	}

	public StartScreen(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public StartScreen(Context context)
	{
		this(context, null, 0);
	}

	private void layout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(R.layout.reinstallstart, null);
		m_startInfoTxtVw = (TextView)view.findViewById(R.id.startBody);
		addView(view);

		// OnClick Listener for Search button
		OnClickListener buttonSearch_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Log.i(TAG, "getScreenName:" + getScreenName());
				unregisterForNotification();
				if(m_wrapper.getConnectionType() == LnbSettingsEntry.LnbConnectionSatIP){
					mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.SATIP_HUBSCREEN, getScreenName());
				}else{
					mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.PRESCAN, getScreenName());
				}
			}
		};

		// OnClick Listener for SETTINGS button
		OnClickListener buttonSettings_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Intent l_intent;
				l_intent = new Intent(mContext, WizardSettingsActivity.class);
				mContext.startActivity(l_intent);
			}
		};

		// OnClick Listener for NEXT button
		OnClickListener buttonSkip_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Log.d(TAG,"Ok on skip");
				m_wrapper.resetInstallation();
				m_wrapper.resetLnbSettings();
				((SatelliteInstallationActivity)mContext).exitInstallationWizard();
			}
		};
		
		String l_btnSearch_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
		String l_btnSkip_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SKIP);
		String l_btnSettings_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SETTINGS);
		
		setButton3(l_btnSearch_txt, buttonSearch_Listener, View.VISIBLE);
		setButton2(l_btnSettings_txt, buttonSettings_Listener, View.VISIBLE);
		setButton1(l_btnSkip_txt, buttonSkip_Listener, View.VISIBLE);
		hideHint();

	}
	
	private void setHelpText()
	{
		int helpTextId = 0;
		int lnbCount = 0;
		Boolean[] scanForLNBs;
		int l_currentConnType = m_wrapper.getConnectionType();
		switch(l_currentConnType)
		{
			case LnbSettingsEntry.LnbConnectionSingle:
				helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_1_LNB;
				m_startInfoTxtVw.setText(helpTextId);
				break;
			case LnbSettingsEntry.LnbConnectionDiSeqcMini:
				scanForLNBs =  m_wrapper.getPrescanForLNBs();
				lnbCount = 0;
				for (int index=0;index<2;index++){
					if(scanForLNBs[index] == true){
						lnbCount++;
					}
				}
				if(lnbCount == 1){
					helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_SKIP_1_LNB;
				} else {
					// all LNB's are selected
					helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_2_LNB;
				}
				
				m_startInfoTxtVw.setText(helpTextId);
				break;
			case LnbSettingsEntry.LnbConnectionDiSeqc1_0:
				scanForLNBs =  m_wrapper.getPrescanForLNBs();
				lnbCount = 0;
				for (int index=0;index<scanForLNBs.length;index++){
					if(scanForLNBs[index] == true){
						lnbCount++;
					}
				}
				if(lnbCount == 1){
					helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_SKIP_1_LNB;
				}else if(lnbCount == 2){
					helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_SKIP_2_LNB;
				}else{
					helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_4_LNB;
				}
				
				m_startInfoTxtVw.setText(helpTextId);
				break;
			case LnbSettingsEntry.LnbConnectionUnicableLnb:
				helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_UNICABLE_1;
				m_startInfoTxtVw.setText(helpTextId);
				break;
			case LnbSettingsEntry.LnbConnectionUnicableSwitch:
				helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_UNICABLE_2;
				m_startInfoTxtVw.setText(helpTextId);
				break;
			case LnbSettingsEntry.LnbConnectionSatIP:
				m_startInfoTxtVw.setText("");
				break;
						
			
				
		}
		
		
	}
	
	private void unregisterForNotification()
	{
		NotificationHandler.getInstance().unRegisterForNotification(this);
	}

	@Override
	public void update(Observable observable, Object data)
	{
		final int eventID = ((NotificationInfoObject) data).actionID;
		switch (eventID)
		{
			case EventIDs.WIZARD_SETTINGS_EXIT:
				Log.d(TAG,"WIZARD_SETTINGS_EXIT");
				setHelpText();
				setButton3focussed();
				break;
		}
	}

	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.STARTSCREEN;
	}

	@Override
	public void screenIntialization()
	{
		Log.d(TAG,"screenIntialization");
		(NotificationHandler.getInstance()).registerForNotification(this);
		setHelpText();
		setButton3focussed();
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{

		boolean ret = super.dispatchKeyEvent(event);
		int keyCode = event.getKeyCode();
		switch (keyCode)
		{
			case KeyEvent.KEYCODE_DPAD_RIGHT:
				ret = true;
				break;
			case KeyEvent.KEYCODE_DPAD_LEFT:
				ret = true;
				break;
		}
		return ret;

	}

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		
	}
}
