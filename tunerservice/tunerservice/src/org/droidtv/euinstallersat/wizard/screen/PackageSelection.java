package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.FreesatOnlyInstallationDialog;
import org.droidtv.euinstallersat.wizard.util.InstallationCancelDialog;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class PackageSelection extends WizardStep implements SatelliteScreen
{

	private static final String TAG = PackageSelection.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private RadioSelector mRadioSelector;
	private NativeAPIWrapper m_wrapper;
	private SatelliteScreen mSatelliteScreen;

	public PackageSelection(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		mSatelliteScreen = this;
		loadLayout(context);
	}

	public PackageSelection(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public PackageSelection(Context context)
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
		mRadioSelector.requestFocus();

		mRadioSelector.setOnItemClickListener(new OnItemClickListener()
		{

			@Override
			public void onItemClick(AdapterView<?> arg0, View view, int selectedItem, long arg3)
			{
				Log.d(TAG, "selectedItem:" + selectedItem);
				setButton3focussed();
			}

		});

		
		// OnClick Listener for Cancel button
		OnClickListener buttonCancel_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				m_wrapper.SetScanStops();
				m_wrapper.resetInstallation();
				mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.STARTSCREEN, getScreenName());

			}
		};

		// OnClick Listener for NEXT button
		OnClickListener buttonNext_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				int selectedPosition = mRadioSelector.getCheckedItemPosition();
				m_wrapper.SetBouquetIndex(selectedPosition);
				if(m_wrapper.ifShowPinEntryScreen()){ // AN-75007
					Log.d(TAG, "Launching pin entry screen");
					mSatelliteWizard.launchScreen(ScreenRequest.PIN_ENTRY, getScreenName());
				}else if( m_wrapper.ifOperatorProfilePackage() || m_wrapper.isM7Package()){
					m_wrapper.SetSelectedPackage(true);
					Log.d(TAG, "Launching service installation screen");
					mSatelliteWizard.launchScreen(ScreenRequest.INSTALLSCREEN, getScreenName());
				}else if (m_wrapper.isPredefinedRankingList()) {
					Log.d(TAG, "Launching service installation screen");
					mSatelliteWizard.launchScreen(ScreenRequest.INSTALLSCREEN, getScreenName());
				} else if (m_wrapper.isAstraLCNPackage(selectedPosition)) {
					Log.d(TAG, "Launching service installation screen");
					m_wrapper.SetSelectedPackage(true);
					mSatelliteWizard.launchScreen(ScreenRequest.INSTALLSCREEN, getScreenName());
				} else if(m_wrapper.isFreesatPackage(selectedPosition))
				{
						Log.d(TAG,"Selected Package is Freesat");
						
					// if more than one satellites detected during prescan display 'Freesat Only Confirmation' Dialog.
					if((m_wrapper.getInstalledLnbCount()) > 1){
						Log.d(TAG,"Num of Satellite Detected, more than one: Display Dialogue");
						showFreesatOnlyDialog();
					}else{
						Log.d(TAG,"Launching Freesat Postcode Entry  screen");
						mSatelliteWizard.launchScreen(ScreenRequest.FREESAT_POSTCODE_ENTRY, getScreenName());
					}
				}
				else if (m_wrapper.isRussiaTricolor (selectedPosition)) 
				{
					
						Log.d(TAG, "Selected Package is Tricolor index "+selectedPosition);
						mSatelliteWizard.launchScreen(ScreenRequest.TRICOLOR_REGION_SELECTION, getScreenName());
						//showTricolorNoFullScanDialog ();
						/* Region Selection Screen will be triggered from the Dialog directly */
				}else {
					Log.d(TAG, "Launching quick/full screen");
					mSatelliteWizard.launchScreen(ScreenRequest.QUICK_FULL, getScreenName());
				}

			}
		};

		// OnClick Listener for Previous button
		OnClickListener buttonPrevious_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Log.d(TAG,"Launching previous screen");
				m_wrapper.SetScanStops();
				m_wrapper.resetInstallation();
				if(m_wrapper.ifSatIPConnectionType()){
					mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.SATIP_HUBSCREEN, getScreenName());
				}else{
					mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.STARTSCREEN, getScreenName());
				}
			}
		};
		
		String l_btnNext_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);

		setButton1(l_btnCancel_txt, buttonCancel_Listener, VISIBLE);
		setButton2(l_btnPrev_txt, buttonPrevious_Listener, VISIBLE);
		setButton3(l_btnNext_txt, buttonNext_Listener, VISIBLE);

		//setHintText(SatelliteConstants.PACKAGE_TITLE);

	}

	private void showFreesatOnlyDialog()
	{
		Log.d(TAG,"show FreesatOnly Dialog");
		FreesatOnlyInstallationDialog l_dialog = new FreesatOnlyInstallationDialog(mContext,mSatelliteWizard);
		l_dialog.setNextScreen(ScreenRequest.PACKAGE_SELECTION, ScreenRequest.FREESAT_POSTCODE_ENTRY);
		l_dialog.showDialog();
		mRadioSelector.requestFocus();
	}
	

	
	@Override
	public void update(Observable observable, Object data)
	{
		Log.d(TAG, "update: action " + ((NotificationInfoObject) data).actionID + ", message " + ((NotificationInfoObject) data).message);
		final int l_eventID = ((NotificationInfoObject) data).actionID;
		Activity l_activity = (Activity) mContext;
		
		switch (l_eventID)
		{
			case EventIDs.PACKAGE_LIST_CREATED: // channels found
				Log.d(TAG, "PACKAGE_LIST_UPDATE");
				unregisterForNotificaton();
				final String packageNames[] = m_wrapper.GetBouquetNames();
				
				l_activity.runOnUiThread(new Runnable()
				{
					@Override
					public void run()
					{
						switch (l_eventID)
						{
							case EventIDs.PACKAGE_LIST_CREATED: // channels found
								Log.d(TAG, "PACKAGE_LIST_UPDATE");
								unregisterForNotificaton();
								enableWaitingAnimation(false);
								setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_PACKAGE_SELECTION));
								mRadioSelector.setArray(packageNames);
								mRadioSelector.setVisibility(VISIBLE);
								mRadioSelector.setChoiceMode(RadioSelector.CHOICE_MODE_SINGLE);
								setButton3Enabled(true);
								mRadioSelector.requestFocus();
								break;
						}
					}
				});
				
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
		return ScreenRequest.PACKAGE_SELECTION;
	}

	@Override
	public void screenIntialization()
	{
		Log.d(TAG,"screenIntialization: Registering for events");
		(NotificationHandler.getInstance()).registerForNotification(mSatelliteScreen);
		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SEARCH_PACKAGES));
		mRadioSelector.setVisibility(INVISIBLE);
		m_wrapper.StartPackageParsing();
		enableWaitingAnimation(true);
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
            	   mRadioSelector.smoothScrollToPosition(l_selIdx);
            	   mRadioSelector.requestFocus();
               }
           }
           else if (((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) && event.getAction() == KeyEvent.ACTION_UP)
			{
				InstallationCancelDialog l_dialog = new InstallationCancelDialog(mContext, mSatelliteWizard);
				l_dialog.setNextScreen(ScreenRequest.PACKAGE_SELECTION, ScreenRequest.STARTSCREEN);
				l_dialog.showDialog();
				l_isKeyHandled = true;
			}           
           Log.d(TAG,"OnKey returning " + l_isKeyHandled);
           return l_isKeyHandled;

    }

	
	
	private void unregisterForNotificaton()
	{
		NotificationHandler.getInstance().unRegisterForNotification(this);
	}

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		unregisterForNotificaton();
		
	}
}
