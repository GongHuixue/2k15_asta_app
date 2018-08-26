package org.droidtv.euinstallersat.wizard.screen;

import java.util.HashMap;
import java.util.Observable;

import org.droidtv.euinstallersat.model.mwapi.LnbSettingsEntry;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;

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
import android.widget.AdapterView.OnItemSelectedListener;

public class InstallModes extends WizardStep implements SatelliteScreen
{

	private static final String TAG = InstallModes.class.getName();
	private Context m_context;
	private SatelliteWizard m_satelliteWizard;
	private RadioSelector m_radioSelector;
	private NativeAPIWrapper m_wrapper;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	
	private final int IDX_UPDATE_CHANNELS = 0;
	private final int IDX_REINSTALL = 1;
	private final int IDX_ADD_SATELLITE = 2;
	private final int IDX_REMOVE_SATELLITE = 3;
	
	private String[] m_hintText;

	public InstallModes(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		m_context = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		m_hintText = new String[] { m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTR_UPDATE_CHANNELS),
									m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTR_REINSTALL_CHANNELS), 
									m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTR_ADD_SATELLITE),
									m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTR_REMOVE_SATELLITE) };
		loadLayout(context, attrSet, defStyle);
	}

	public InstallModes(Context context, AttributeSet arg1)
	{
		this(context, null, 0);
	}

	public InstallModes(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(final Context context, AttributeSet attrs, int defStyle)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		addView(view);

		m_radioSelector = (RadioSelector) view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		m_radioSelector.setOnKeyListener(this);
		// OnClick Listener for NEXT button
		OnClickListener buttonNext_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Log.i(TAG, "text:" + m_radioSelector.getItemAtPosition(m_radioSelector.getCheckedItemPosition()));
				int selectedItem = m_radioSelector.getCheckedItemPosition();
				switch (selectedItem)
				{
					case IDX_UPDATE_CHANNELS:
						if(isDigiturkSingleLNB())
						{
							m_satelliteWizard.launchScreen(ScreenRequest.MINI_PRESCAN, getScreenName());
						}
						else
						{
							m_satelliteWizard.launchScreen(ScreenRequest.UPDATESATELLITE, getScreenName());
						}
						break;
					case IDX_REINSTALL:
						showReinstallDialog();
						break;
					case IDX_ADD_SATELLITE:
						m_satelliteWizard.launchScreen(ScreenRequest.ADDSATPRESCAN, getScreenName());
						break;
					case IDX_REMOVE_SATELLITE:
						m_satelliteWizard.launchScreen(ScreenRequest.REMOVESATSELECTION, getScreenName());
						break;
					default:
						break;
				}
			}
		};

		// ONClick Listener for CANCEL Button
		OnClickListener buttonCancel_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				Log.d(TAG,"Ok on cancel button");

				((SatelliteInstallationActivity)m_context).exitInstallationWizard();
			}
		};
		
		String l_btnNext_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);
		
		setButton3(l_btnNext_txt, buttonNext_Listener, View.VISIBLE);
		setButton2(l_btnPrev_txt, null, View.INVISIBLE);
		setButton1(l_btnCancel_txt, buttonCancel_Listener, View.VISIBLE);

		// Changing the hint text based on the selected item
		m_radioSelector.setOnItemSelectedListener(new OnItemSelectedListener()
		{

			@Override
			public void onItemSelected(AdapterView<?> arg0, View view, int selectedItem, long arg3)
			{
				setHintText(m_hintText[selectedItem]);
			}

			@Override
			public void onNothingSelected(AdapterView<?> arg0)
			{
				// TODO Auto-generated method stub

			}
		});

		m_radioSelector.setOnItemClickListener(new OnItemClickListener()
		{

			@Override
			public void onItemClick(AdapterView<?> arg0, View view, int selectedItem, long arg3)
			{
				Log.i(TAG, "selectedItem:" + selectedItem);
				setHintText(m_hintText[selectedItem]);
				setButton3focussed();
			}

		});
		
	}
	
	private boolean isDigiturkSingleLNB()
	{
		Log.d(TAG,"isDigiturkSingleLNB entry");
		boolean l_ret = false;
		String l_packageName;
		String l_digiturk_eutelsat_w3a_7e;
		/*
		String l_digiturk_turksat_42e;
		if(m_wrapper.getConnectionType( ) == LnbSettingsEntry.LnbConnectionSingle)
		{
			l_digiturk_eutelsat_w3a_7e = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_DIGITURK_EUTELSAT_W3A_7E);
			l_digiturk_turksat_42e = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_DIGITURK_TURKSAT_42E);
			l_packageName = m_wrapper.GetSelectedPackageName();
			if((l_packageName.equalsIgnoreCase(l_digiturk_eutelsat_w3a_7e)) || (l_packageName.equalsIgnoreCase(l_digiturk_turksat_42e)))
			{
				l_ret = true;
			}
		}
		*/
		l_digiturk_eutelsat_w3a_7e = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BOUQUET_DIGITURK_EUTELSAT_W3A_7E);
		l_packageName = m_wrapper.GetSelectedPackageName();
		/* Mini prescan should be limited to only Digiturk Eutelsat & when at least one MDU detected 
			Assumption: No combination of MDUs  OR Eutelsat Universl + MDUs is expected */
		if (l_packageName.equalsIgnoreCase(l_digiturk_eutelsat_w3a_7e))
		{
			Log.d(TAG, "Package selected is Eutelsat ");
			if (m_wrapper.GetIsMDUDetectedInAnyLnbPos() == true)
			{
				l_ret = true;
			}
		}
		Log.d(TAG,"isDigiturkSingleLNB returning " + l_ret);
		return l_ret;
	}

	@Override
	public void update(Observable observable, Object data)
	{

	}

	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		m_satelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.INSTALLMODES;
	}

	@Override
	public void screenIntialization()
	{
		Boolean l_isUpdateControllable = m_wrapper.isUpdateControllable();
		String[] l_radioListText = {m_context.getString(org.droidtv.ui.strings.R.string.MAIN_UPDATE_CHANNELS), 
									m_context.getString(org.droidtv.ui.strings.R.string.MAIN_REINSTALL_CHANNELS),
									m_context.getString(org.droidtv.ui.strings.R.string.MAIN_ADD_SATELLITE), 
									m_context.getString(org.droidtv.ui.strings.R.string.MAIN_REMOVE_SATELLITE) };
		m_radioSelector.setArray(l_radioListText);
		if (l_isUpdateControllable)
		{
			m_radioSelector.setItemChecked(IDX_UPDATE_CHANNELS, true);
			m_radioSelector.setSelection(IDX_UPDATE_CHANNELS);
			setHintText(m_hintText[IDX_UPDATE_CHANNELS]);
		}
		else
		{
			m_radioSelector.setItemChecked(IDX_REINSTALL, true);
			m_radioSelector.setSelection(IDX_REINSTALL);
			setHintText(m_hintText[IDX_REINSTALL]);
		}
		HashMap<Integer,Boolean> l_controllabilityMap = new HashMap<Integer,Boolean>();
		l_controllabilityMap.put(IDX_UPDATE_CHANNELS, l_isUpdateControllable);
		l_controllabilityMap.put(IDX_REINSTALL,true);
		l_controllabilityMap.put(IDX_ADD_SATELLITE, m_wrapper.isAddSatelliteControllable());
		l_controllabilityMap.put(IDX_REMOVE_SATELLITE,m_wrapper.isRemoveSatelliteControllable());
		m_radioSelector.setControllable(l_controllabilityMap);
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
            	   m_radioSelector.requestFocus();
               }
           }
           Log.d(TAG,"OnKey returning " + l_isKeyHandled);
           return l_isKeyHandled;

    }
	
	private void showReinstallDialog()
	{
		mBuilder = new ModalDialog.Builder(m_context,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_TI_SAT_CONFIRM_REINSTALL), "");
    	mBuilder.setMessage(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_DI_SAT_CONFIRM_REINSTALL));
    	
    	ModalDialogFooterButtonProp mCancelButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_CANCEL clicked ");
    					mModalDialog.hide();
    				}
    			});
    	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_REINSTALL),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_REINSTALL clicked ");
    					if(m_wrapper.getNVMConnectionType() == LnbSettingsEntry.LnbConnectionSatIP){
    						m_satelliteWizard.launchScreen(ScreenRequest.SATIP_STARTSCREEN, getScreenName());
    					}else if (m_wrapper.isTwoTunerSupported()) {
    						m_satelliteWizard.launchScreen(ScreenRequest.DUAL_TUNER, getScreenName());
    					} else {
    						m_satelliteWizard.launchScreen(ScreenRequest.STARTSCREEN, getScreenName());
    					}
    					mModalDialog.hide();
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setCancelable(false);
    	mModalDialog.show();
    	mCancelButton.requestFocus();
	}

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		
	}




	

}
