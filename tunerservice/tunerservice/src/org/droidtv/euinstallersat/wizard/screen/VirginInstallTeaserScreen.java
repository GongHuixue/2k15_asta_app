package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

public class VirginInstallTeaserScreen extends WizardStep implements SatelliteScreen
{

	private static final String TAG = VirginInstallTeaserScreen.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private TextView m_startInfoTxtVw;

	public VirginInstallTeaserScreen(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		layout(context);
	}

	public VirginInstallTeaserScreen(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public VirginInstallTeaserScreen(Context context)
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
				NativeAPIWrapper l_wrapper = NativeAPIWrapper.getInstance();
				if(l_wrapper.isTwoTunerSupported())
				{
					mSatelliteWizard.launchScreen(ScreenRequest.DUAL_TUNER, getScreenName());
				}
				else
				{
					mSatelliteWizard.launchScreen(ScreenRequest.STARTSCREEN, getScreenName());
				}

			}
		};

		

		// OnClick Listener for NEXT button
		OnClickListener buttonSkip_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				((SatelliteInstallationActivity) mContext).exitInstallationWizard();
			}
		};
		
		String l_btnStart_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_START);
		String l_btnCancel_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);
		
		setButton3(l_btnStart_txt, buttonSearch_Listener, View.VISIBLE);
		setButton2("", null, View.INVISIBLE);
		setButton1(l_btnCancel_txt, buttonSkip_Listener, View.VISIBLE);
		m_startInfoTxtVw.setText(org.droidtv.ui.strings.R.string.MAIN_DI_SAT_ASSISTANT_START);
		hideHint();
	}
	

	@Override
	public void update(Observable observable, Object data)
	{
	}

	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.VIRGIN_INSTALL_TEASER;
	}

	@Override
	public void screenIntialization()
	{
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
			default:
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
