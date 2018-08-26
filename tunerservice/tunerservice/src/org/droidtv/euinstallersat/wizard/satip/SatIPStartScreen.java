package org.droidtv.euinstallersat.wizard.satip;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.LnbSettingsEntry;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.settings.WizardSettingsActivity;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

public class SatIPStartScreen extends WizardStep implements SatelliteScreen
{

	private static final String TAG = SatIPStartScreen.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper nwrap;
	private TextView startInfoTxtVw;
	private int currentConnType;

	public SatIPStartScreen(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		nwrap = NativeAPIWrapper.getInstance();
		layout(context);
	}

	public SatIPStartScreen(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public SatIPStartScreen(Context context)
	{
		this(context, null, 0);
	}

	private void layout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(R.layout.satipstart, null);
		startInfoTxtVw = (TextView)view.findViewById(R.id.startBody);
		
		startInfoTxtVw.setText(org.droidtv.tunerservice.R.string.MAIN_WI_SAT_IP_AUTOSTORE_START);
		addView(view);

		// OnClick Listener for Search button
		OnClickListener buttonSearch_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Log.i(TAG, "getScreenName:" + getScreenName());
				unregisterForNotification();
				
				if(currentConnType == LnbSettingsEntry.LnbConnectionSatIP){
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
				nwrap.resetInstallation();
				nwrap.resetLnbSettings();
				((Activity)mContext).finish();
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
		int l_helpTextId = 0;
		
		// update text and connection type variable
		currentConnType = nwrap.getConnectionType();
		switch(currentConnType)
		{
			case LnbSettingsEntry.LnbConnectionSingle:
				l_helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_1_LNB;
				break;
			case LnbSettingsEntry.LnbConnectionDiSeqcMini:
				l_helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_2_LNB;
				break;
			case LnbSettingsEntry.LnbConnectionDiSeqc1_0:
				l_helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_4_LNB;
				break;
			case LnbSettingsEntry.LnbConnectionUnicableLnb:
				l_helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_UNICABLE_1;
				break;
			case LnbSettingsEntry.LnbConnectionUnicableSwitch:
				l_helpTextId = org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_START_UNICABLE_2;
				break;
			case LnbSettingsEntry.LnbConnectionSatIP:
				l_helpTextId = org.droidtv.tunerservice.R.string.MAIN_WI_SAT_IP_AUTOSTORE_START;
				break;
		}
		
		startInfoTxtVw.setText(l_helpTextId);
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
				setButton3focussed();
				setHelpText();
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
		return ScreenRequest.SATIP_STARTSCREEN;
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
