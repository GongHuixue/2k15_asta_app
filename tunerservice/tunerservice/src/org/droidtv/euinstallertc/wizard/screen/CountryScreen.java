/*
 *  Copyright(C) 2012 TP Vision Holding B.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of TP Vision Holding B.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of TP Vision Holding B.V.
 *
 */
package org.droidtv.euinstallertc.wizard.screen;

import java.util.Observable;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tunerservice.util.PlayTvUtils;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;

/*
 * This class will display list of radio buttons in the wizard step and it allows the user to select the country.
 */

public class CountryScreen extends WizardStep implements IInstallationScreen
{

	private static final String TAG = CountryScreen.class.getName();
	private InstallationWizard mInstallationWizard;
	private Context mContext;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private ITvSettingsManager mTvSettingsManager = ITvSettingsManager.Instance.getInterface();
	private RadioSelector radioSelector;

	private boolean EnableDVBC = true;
	private boolean EnableDVBT = true;
	private boolean EnableAnalog = true;
	private int RfSetting = 0;
	private int PbsMode = 0;

	public CountryScreen(Context context)
	{
		this(context, null, 0);
	}

	public CountryScreen(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);
	}

	public CountryScreen(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		mContext = context;
		Log.d(TAG, "CountrySelector() called");
		loadLayout(context, attrs, defStyle);

	}

	/*
	 * This method is responsible for setting the view to wizard step and it will change button names,make it visible or invisible.
	 * setting hint text .
	 * Displays list of countries.
	 *
	 * 
	 * @params context,attribute set,default style
	 */
	private void loadLayout(final Context context, AttributeSet attrs,
			int defStyle)
	{
		Log.d(TAG, "loadLayoutCalled() called");

		final LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		addView(view);
		
		
		//OnClick Listener for NEXT button 
		OnClickListener buttonNext_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				
				int selectedItem = radioSelector.getCheckedItemPosition();
				Log.i(TAG, "Country Selection:" + selectedItem);
				Log.d(TAG, "You clicked on Next button: "+ selectedItem);
				nwrap.setCachedCountryID(selectedItem);

				EnableDVBC = (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_C_C2, 0, 0));
				EnableDVBT = (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_T_T2, 0, 0));
				EnableAnalog = (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_ANALOG, 0, 0));

				/* 
				 * Requirement: Timezone country and Virgin installation:
				 * <Screen: Timezone> Not Timezone country or not Virgin
				 * installation: DVB-C installation is supported: <Screen:
				 * Antenna/Cable> DVB-C installation is not supported: Search
				 * subwizard, first applicable
				 */
				
				if(nwrap.ifShowPinEntryScreen()){
				    mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.PINENTRY_SCREEN,getScreenName());
				}else{
					RfSetting = 0;
					if(EnableDVBC) {
						RfSetting |= 0x01;
					}
					if(EnableDVBT) {
						RfSetting |= 0x02;
					}
					if(EnableAnalog) {
						RfSetting |= 0x04;
					}
					nwrap.setRfSetting(RfSetting);
					if (PlayTvUtils.isPbsMode()) {
						PbsMode = 1;
					}
					else {
						PbsMode = 0;
					}
					nwrap.setPbsMode(PbsMode);
					
    				if (nwrap.ifTimezoneCountry(nwrap.getCachedCountryName())){
    				    if( nwrap.ifVirginInstallation()){
							if (PbsMode == 1) {
								HtvTimezoneCountry();
							} else {
    				        	if (nwrap.ifDVBCSupportedCountry(nwrap.getCachedCountryName()))
    	                    	{
    	                    	    mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.ANTENNA_SCREEN,getScreenName());
    	                    	}else{
    	                    	    mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN,getScreenName());
    	                    	}
							}
    				    }else{
    				        mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.TIMEZONE_SCREEN,getScreenName());
    				    }
    				}else{
	    				if (PbsMode == 1) {
							HtvTimezoneCountry();
	    				} else {
    						if (nwrap.ifDVBCSupportedCountry(nwrap.getCachedCountryName()))
    						{
    							mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.ANTENNA_SCREEN,getScreenName());
    						}else{
    							mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN,getScreenName());
    						}
	    					}
    				}
				}
			}
		};

		//OnClick Listener for PREVIOUS button
		OnClickListener buttonPrevious_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				mInstallationWizard.launchPreviousScreen();
			}
		};
		
		setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), null,
				View.INVISIBLE);
		setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener,
				View.VISIBLE);
		setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT),
				buttonNext_Listener, View.VISIBLE);
	
		radioSelector = (RadioSelector) view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		//radioSelector.setSmoothScrollbarEnabled(true);
		radioSelector.setOnItemClickListener(new OnItemClickListener()
		{
			@Override
			public void onItemClick(AdapterView<?> arg0, View selectedView,int selectedItem, long arg3)
			{

				/*String mSelectedCountry = (String) ((TextView) selectedView).getText().toString();*/
				Log.i(TAG, "Country Selection:" + selectedItem );
				
				// move the focus on next button
				setButton3focussed();
				
			}
		});
		setHintText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_COUNTRY));
		
		// un-registering this class for notifications
		(NotificationHandler.getInstance()).unregisterForNotification(this);
	}

	/*
	 * @see org.droidtv.broadcasttv.InstallationScreen#setIntance(org.droidtv.broadcasttv.InstallationWizard)
	 * Getting the InstallationWizard instance and keeping it for screen navigation.
	 * 
	 * @params InstallationWizard wizard
	 * @return 
	 */
	@Override
	public void setInstance(InstallationWizard wizard)
	{
		mInstallationWizard = wizard;
	}

	/*
	 * @see org.droidtv.broadcasttv.InstallationScreen#getScreenName()
	 * setting the currenct screen name for backward screen navigation. 
	 * 
	 * @Param
	 * @Return ScreenRequest
	 */
	@Override
	public ScreenRequest getScreenName()
	{
		return InstallationWizard.ScreenRequest.COUNTRY_SCREEN;
	}

	/*
	 * @see java.util.Observer#update(java.util.Observable, java.lang.Object)
	 * Call back method from InstallationScreen
	 * 
	 * @params observable,data
	 * @return
	 */
	@Override
	public void update(Observable observable, Object data)
	{
	}
	
	@Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        boolean handled = false;
        int keyCode = event.getKeyCode();
        int keyAction = event.getAction();
        View currentFocus = ((Activity) mContext).getCurrentFocus();
        
        switch (keyCode) {
            case KeyEvent.KEYCODE_DPAD_UP:

                if (currentFocus instanceof Button) {
                    if (keyAction == KeyEvent.ACTION_UP) {
                        int selectedItemPos = radioSelector.getCheckedItemPosition();
                        radioSelector.smoothScrollToPosition(selectedItemPos);
                        radioSelector.requestFocusFromTouch();
                        radioSelector.requestFocus();
                        radioSelector.setSelection(selectedItemPos);
                        radioSelector.setItemChecked(selectedItemPos, true);
                    }
                    handled = true;
                }
                
                break;
        }

        return handled | super.dispatchKeyEvent(event);
    }

    private void setfocusOnTheRadioList(){
	    Log.d(TAG, "setfocusOnTheRadioList " + radioSelector.getCount());
		if(radioSelector.getCount() > 0){
			// code will come here when revisiting the screen
		}else{
			radioSelector.setArray( nwrap.getSortedCountyList());					
		}		
        int setLocalCountryID = nwrap.getCachedCountryID();
        Log.d(TAG, "setfocusOnTheRadioList setLocalCountryID " + setLocalCountryID);
        
        radioSelector.smoothScrollToPosition(setLocalCountryID);
        radioSelector.requestFocusFromTouch();
        radioSelector.requestFocus();
        radioSelector.setSelection(setLocalCountryID);
        radioSelector.setItemChecked(setLocalCountryID, true);
	}
	
	@Override
	public void screenIntialization() {
		
		// country adapter already populated needn't to change anything
		Log.d(TAG, "radioSelector.getCount() " + radioSelector.getCount() );
		setfocusOnTheRadioList();
		
	}

	private void HtvTimezoneCountry() {
		nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE);
		if (EnableDVBC)
	    {
			nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBC);

			if (nwrap.ifCountryHasOperator(nwrap.getCachedCountryID())) {
				mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.OPERATOR_SCREEN, getScreenName());
	    }else{
	        mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN,getScreenName());
	    }
		}
		else if (EnableDVBT)
		{
			nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBT);
			
			if (nwrap.isOperatorProfileSupported()) {
				mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.TERRIESTRIAL_OPERATOR_SCREEN, getScreenName());
	    }else{
	        mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN,getScreenName());
	    }
		} else
		{
			nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBT);
			
			mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN,getScreenName());
		}
	}
}
