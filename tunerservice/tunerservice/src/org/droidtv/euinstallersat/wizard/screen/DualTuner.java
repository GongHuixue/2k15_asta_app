package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.SelectedMode;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class DualTuner extends WizardStep implements SatelliteScreen
{

	private static final String TAG = DualTuner.class.getName();
	private Context mContext;
	private RadioSelector mRadioSelector;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper m_wrapper;
	public static int mSelectedItem = 1;
	private int IDX_ONE_TUNER = 0;
	private int IDX_TWO_TUNERS = 1;

	public DualTuner(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		loadLayout(context);
	}

	public DualTuner(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public DualTuner(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		addView(view);
		mRadioSelector = (RadioSelector) view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		mRadioSelector.setOnKeyListener(this);
		OnClickListener buttonCancel_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				mSatelliteWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonPrevious_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				mSatelliteWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonNext_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				int selectedPosition = mRadioSelector.getCheckedItemPosition();
				if (selectedPosition == IDX_ONE_TUNER) {
					m_wrapper.setDualTunerToTVS(false);
				} else {
					m_wrapper.setDualTunerToTVS(true);
				}
				if(m_wrapper.getUserSelectedMode() == SelectedMode.FROM_THE_CAM){
					mSatelliteWizard.launchScreen(ScreenRequest.CAM_INSTALLATION, getScreenName());
				}else{
					mSatelliteWizard.launchScreen(ScreenRequest.STARTSCREEN, getScreenName());
				}
			}
		};

		mRadioSelector.setOnItemClickListener(new OnItemClickListener()
		{

			@Override
			public void onItemClick(AdapterView<?> arg0, View view, int selectedItem, long arg3)
			{
				Log.d(TAG, "selectedItem:" + selectedItem);
				setButton3focussed();
			}

		});
		
		String l_btnNext_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);

		setButton1(l_btnCancel_txt, buttonCancel_Listener, VISIBLE);
		setButton2(l_btnPrev_txt, buttonPrevious_Listener, VISIBLE);
		setButton3(l_btnNext_txt, buttonNext_Listener, VISIBLE);
		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_DUAL_TUNER));
	}
	
	    @Override
    public boolean onKey(View view, int keyCode, KeyEvent event)
    {

           Log.d(TAG,"OnKey");
           boolean l_isKeyHandled = false;
           if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
           {
                  Log.d(TAG,"KEYCODE_DPAD_RIGHT");
                  if(mRadioSelector == view)
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
                  if(mRadioSelector == view)
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
               if(mRadioSelector != view)
               {
            	   int l_selIdx = mRadioSelector.getCheckedItemPosition();
            	   mRadioSelector.setSelection(l_selIdx);
            	   mRadioSelector.requestFocus();
               }
           }
           Log.d(TAG,"OnKey returning " + l_isKeyHandled);
           return l_isKeyHandled;

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
		return ScreenRequest.DUAL_TUNER;
	}

	@Override
	public void screenIntialization()
	{
		String[] l_dualTunerArray = {
				 mContext.getString(org.droidtv.ui.strings.R.string.MAIN_ONE_TUNER),
				 mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TWO_TUNERS) };
		mRadioSelector.setArray(l_dualTunerArray);
		if(m_wrapper.IsDualTunerOn())
		{
			mRadioSelector.setItemChecked(IDX_TWO_TUNERS, true);
			mRadioSelector.setSelection(IDX_TWO_TUNERS);
		}
		else
		{
			mRadioSelector.setItemChecked(IDX_ONE_TUNER, true);
			mRadioSelector.setSelection(IDX_ONE_TUNER);
		}
		
		
		mRadioSelector.requestFocus();
	}

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		
	}
}
