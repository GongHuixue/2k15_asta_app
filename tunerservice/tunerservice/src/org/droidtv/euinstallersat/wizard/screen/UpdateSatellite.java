package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.LnbSettingsEntry;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
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
import android.widget.Button;
import android.widget.TextView;


public class UpdateSatellite extends WizardStep implements SatelliteScreen
{

	private static final String TAG = UpdateSatellite.class.getName();
	private SatelliteWizard mSatelliteWizard;
	//private Context mContext;
	private NativeAPIWrapper mWrapper;

	public UpdateSatellite(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		//mContext = context;
		loadLayout(context, attrSet, defStyle);
		mWrapper = NativeAPIWrapper.getInstance();
	}

	public UpdateSatellite(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public UpdateSatellite(Context context)
	{
		super(context, null, 0);
	}

	private void loadLayout(final Context context, AttributeSet attrs, int defStyle)
	{
		//SimpleText view = new SimpleText(mContext);
		//view.setText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_UPDATE_CHANNELS));

		//addView(view);
		
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(R.layout.reinstallstart, null);
		TextView l_infoTxtVw = (TextView)view.findViewById(R.id.startBody);
		addView(view);
		l_infoTxtVw.setText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_UPDATE_CHANNELS));
		OnClickListener buttonCancel_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				mSatelliteWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonSettings_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Log.i(TAG, "buttonSettings:onClick called");
				mSatelliteWizard.launchScreen(ScreenRequest.SATELLITESELECTION, getScreenName());
			}
		};

		OnClickListener buttonUpdate_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Log.i(TAG, "buttonUpdate:onClick called");
				mSatelliteWizard.launchScreen(ScreenRequest.UPDATESCAN, getScreenName());
			}
		};

		setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), buttonCancel_Listener, View.VISIBLE);
		setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SETTINGS), buttonSettings_Listener, View.VISIBLE);
		setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_UPDATE), buttonUpdate_Listener, View.VISIBLE);
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
		return ScreenRequest.UPDATESATELLITE;
	}

	@Override
	public void screenIntialization()
	{
		int l_currentConnType = mWrapper.getConnectionType();
		boolean l_isSettingsEnabled = false;
		if(l_currentConnType == LnbSettingsEntry.LnbConnectionDiSeqc1_0)
		{
			if(mWrapper.isAutoUpListAvailable())
			{
				l_isSettingsEnabled = true;
			}
		}
		
	    setButton2Enabled(l_isSettingsEnabled);
	    setButton3focussed();
	}
	  


           @Override
       public boolean dispatchKeyEvent(KeyEvent event)
       {
              if(event.getAction() == KeyEvent.ACTION_DOWN && event.getKeyCode() == KeyEvent.KEYCODE_DPAD_RIGHT) {                  
                     Log.d(TAG,"right pressed: focusedView" + findFocus());
              }
              
        Log.d(TAG,"OnKey");
        boolean l_isKeyHandled = super.dispatchKeyEvent(event);
        if (!l_isKeyHandled && event.getKeyCode() == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
        {
               Log.d(TAG,"KEYCODE_DPAD_RIGHT, returning true");
               Button b2 = (Button)findViewById(org.droidtv.ui.tvwidget2k15.R.id.button2);
               if(b2.hasFocus()) {
                 setButton3focussed();
               }               
               l_isKeyHandled = true;
        }
        if (!l_isKeyHandled && event.getKeyCode() == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
        {
               Log.d(TAG,"KEYCODE_DPAD_RIGHT, returning true");
               Button b2 = (Button)findViewById(org.droidtv.ui.tvwidget2k15.R.id.button2);
               if(b2.hasFocus()) {
                 setButton1focussed();
               }               
               l_isKeyHandled = true;
        }
        return l_isKeyHandled;

       }

		@Override
		public void screenExit()
		{
			Log.d(TAG,"screenExit");
			
		}


}
