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
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DVBTOrDVBCMacro;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
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
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;

/*
 * This class will display list of radio buttons in the wizard step and it allows the user to select the intstallation medium.
 */
public class AntennaCableScreen extends WizardStep implements
IInstallationScreen {

	private static final String TAG = AntennaCableScreen.class.getName();
	private InstallationWizard mInstallationWizard;
	private IInstallationScreen mInstallationScreen;
	private Context mContext;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private RadioSelector radioSelector;
	private NotificationHandler  ntf  = NotificationHandler.getInstance();
	private int userSelectedIndex = 0;
	
	public AntennaCableScreen(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		mContext = context;
		mInstallationScreen = this;
		loadLayout(context, attrs, defStyle);
	}

	public AntennaCableScreen(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public AntennaCableScreen(Context context) {
		this(context, null, 0);
	}

	private void navigateToNextScreen(){
		Log.d(TAG, "onchannelretuned done now navigateToNextScreen");
		String selectedCountry = nwrap.getCachedCountryName();
		enableWaitingAnimation(false);
		(NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
		switch (userSelectedIndex) {
			case 0:
				// set antenna / terrestrial
				if (DVBTOrDVBCMacro.DVBT_Light == nwrap.countrySupportsDVBTFullorLite(nwrap.getCachedCountryName())) {
					// analog and digital channels always installed (not
					// user controllable)
					nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE);
					
					if (nwrap.isOperatorProfileSupported()) {
						mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.TERRIESTRIAL_OPERATOR_SCREEN, getScreenName());
					}else{
						mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
					}
				} else {
					nwrap.setCachedAnalogueDigital(nwrap.getDigitalAnalogSelection(selectedCountry, NativeAPIEnums.DVBTOrDVBC.DVBT));
					if (nwrap.isOperatorProfileSupported()) {
						mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.TERRIESTRIAL_OPERATOR_SCREEN, getScreenName());
					}else{
						mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.DIGITAL_SCREEN, getScreenName());
					}
				}
			break;
			case 1:
				// set cable
				nwrap.setCachedAnalogueDigital(nwrap.getDigitalAnalogSelection(selectedCountry,NativeAPIEnums.DVBTOrDVBC.DVBC));
				
				if (nwrap.ifCountryHasOperator(nwrap.getCachedCountryID())) {
					mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.OPERATOR_SCREEN, getScreenName());
				} else {
					if (nwrap.isOperatorProfileSupported()) {
						mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.TERRIESTRIAL_OPERATOR_SCREEN, getScreenName());
					} else {
						mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.DIGITAL_SCREEN, getScreenName());
					}
				}
			break;	
		}
		
	}
	private void loadLayout(Context context, AttributeSet attrs, int defStyle) {

		LayoutInflater inflater = (LayoutInflater) context
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(
				org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);

		addView(view);

		// OnClick Listener for NEXT button
		OnClickListener buttonNext_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				// disable next button
				setButton1Enabled(false);
				enableWaitingAnimation(true);
				userSelectedIndex = radioSelector.getCheckedItemPosition();
				Log.d(TAG, "User clicked on Next button:" + userSelectedIndex);
				
				switch (userSelectedIndex) {
					case 0:
						// set antenna / terrestrial
						nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBT);
						// tune to selected medium and wait for the onchannelretuned callback
						break;
					case 1:
						// set cable
						nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBC);
						// tune to selected medium and wait for the onchannelretuned callback
						break;				
				}
			}
		};

		// OnClick Listener for PREVIOUS button
		OnClickListener buttonPrevious_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				(NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
				mInstallationWizard.launchPreviousScreen();
			}
		};
		
		OnClickListener buttonCancel_Listener = new OnClickListener() {

            @Override
            public void onClick(View v) {
                nwrap.stopInstallation(true);
            }
        };

        setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), buttonCancel_Listener, View.VISIBLE);
        
		setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener,
				View.VISIBLE);
		setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT),
				buttonNext_Listener, View.VISIBLE);
		radioSelector = (RadioSelector) view
				.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);

		// Changing the hint text based on the selected item
		radioSelector.setOnItemSelectedListener(new OnItemSelectedListener() {

			@Override
			public void onItemSelected(AdapterView<?> arg0, View view,
					int selectedItem, long arg3) {
				switch (selectedItem) {
				case 0:
					setHintText(mContext
							.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_ANTENNA_EUROPE));
					break;
				case 1:
					setHintText(mContext
							.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_CABLE_EUROPE));
					break;
				default:
					break;
				}

			}

			@Override
			public void onNothingSelected(AdapterView<?> arg0) {
			}

		});
		
		radioSelector.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View selectedView,
					int selectedItem, long arg3) {
				switch (selectedItem) {

				case 0:
					// set antenna / terrestrial
					//nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBT);
					setButton3focussed();
					setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_ANTENNA_EUROPE));
					break;
				case 1:
					// set cable
					//nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBC);
					setButton3focussed();
					setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_CABLE_EUROPE));
					break;
				}
			}
		});
	}

	/*
	 * Get the instance of Installation wizard(non-Javadoc)
	 * 
	 * @see
	 * org.droidtv.broadcasttv.InstallationScreen#setIntance(org.droidtv.broadcasttv
	 * .InstallationWizard)
	 */
	@Override
	public void setInstance(InstallationWizard wizard) {
		mInstallationWizard = wizard;
	}

	/*
	 * @see org.droidtv.broadcasttv.InstallationScreen#getScreenName() setting
	 * the currenct screen name for backward screen navigation.
	 * 
	 * @Param
	 * 
	 * @Return ScreenRequest
	 */
	@Override
	public ScreenRequest getScreenName() {
		return InstallationWizard.ScreenRequest.ANTENNA_SCREEN;
	}

	/*
	 * @see java.util.Observer#update(java.util.Observable, java.lang.Object)
	 * Call back method from InstallationScreen
	 * 
	 * @params observable,data
	 * 
	 * @return
	 */
	@Override
	public void update(Observable observable, Object data) {
		final int eventID = ((NotificationInfoObject) data).actionID;
		switch (eventID) {
			case EventIDs.EVENT_INSTALLER_ONCHANNELRETUNED:
				Log.d(TAG, "EVENT_INSTALLER_ONCHANNELRETUNED");
				 ((Activity)mContext).runOnUiThread(new Runnable() {
						
						@Override
						public void run() {
							navigateToNextScreen();
						}
				 });
			break;
		}
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
		// initially cable is selected
		NativeAPIEnums.DVBTOrDVBC dvbtOrdvbCSelected = nwrap.getCachedDVBTOrDVBC();
		
		if(dvbtOrdvbCSelected == NativeAPIEnums.DVBTOrDVBC.DVBT){
			radioSelector.setItemChecked(0, true);
			radioSelector.setSelection(0);
			setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_ANTENNA_EUROPE));
			
		}else{
			radioSelector.setItemChecked(1, true);
			radioSelector.setSelection(1);
			setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_CABLE_EUROPE));
		}
		
		radioSelector.requestFocusFromTouch();
		radioSelector.requestFocus();	
	}

	@Override
	public void screenIntialization() {
		setButton1Enabled(true);
		radioSelector.setArray(nwrap.getDVBTOrDVBCList());
		setfocusOnTheRadioList();
		// register this class for notifications
        (NotificationHandler.getInstance()).registerForNotification(mInstallationScreen);
	}
}
