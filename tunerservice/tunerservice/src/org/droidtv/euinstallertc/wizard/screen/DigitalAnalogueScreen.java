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
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class DigitalAnalogueScreen extends WizardStep implements
IInstallationScreen
{

	private static final String TAG = DigitalAnalogueScreen.class.getName();
	private InstallationWizard mInstallationWizard;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private RadioSelector radioSelector;
	private Context mContext;

	public DigitalAnalogueScreen(Context context, AttributeSet attrs,
			int defStyle)
	{
		super(context, attrs, defStyle);
		mContext = context;
		loadLayout(context, attrs, defStyle);
	}

	public DigitalAnalogueScreen(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);
	}

	public DigitalAnalogueScreen(Context context)
	{
		this(context, null, 0);
	}

	/*
	 * This method is responsible for setting the view to wizard step and it
	 * will change button names,make it visible or invisible. setting hint text.
	 * Displays list of Digital and Analogue options. On selection of the list
	 * it will navigate to Operator screen
	 * 
	 * 
	 * @params context,attribute set,default style
	 */

	private void loadLayout(Context context, AttributeSet attrs, int defStyle) {

		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		addView(view);
		
		//OnClick Listener for NEXT button 
		OnClickListener buttonNext_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				
				int selectedItem = radioSelector.getCheckedItemPosition();
				Log.d(TAG, "Next button:"+selectedItem);

				switch (selectedItem) {
				case 0:
					// set Digital And Analog in mw
					nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE);
					mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
					break;
				case 1:
					// set Digital in mw
					nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.DIGITAL);
					mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
					break;
				case 2:
					// set Analog in mw
					nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.ANALOGUE);
					mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
					break;
				default:
					break;
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
		
		OnClickListener buttonSkip_Listener = new OnClickListener() {

            @Override
            public void onClick(View v) {
                nwrap.stopInstallation(true);
            }
        };
		
		if(nwrap.ifVirginInstallation()){
            setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SKIP), buttonSkip_Listener, View.VISIBLE);
        }else{
            setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SKIP), null, View.INVISIBLE);
        }
		
		setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener,
				View.VISIBLE);
		setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT),
				buttonNext_Listener, View.VISIBLE);
		

		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_ANALOGUE_DIGITAL));

		radioSelector = (RadioSelector) view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		
		radioSelector.setOnItemClickListener(new OnItemClickListener()
		{
			@Override
			public void onItemClick(AdapterView<?> arg0, View selectedView,
					int selectedItem, long arg3)
			{
				
				Log.d(TAG, "DigitalAnalogueScreen.onItemClick:"+selectedItem);
				switch (selectedItem)
				{
				case 0:
					// set Digital and Analog in mw
					nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE);
					setButton3focussed();
					break;
				case 1:
					// set Digital in mw
					nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.DIGITAL);
					setButton3focussed();
					break;
				case 2:
					// set Analog in mw
					nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.ANALOGUE);
					setButton3focussed();
					break;
				default:
					break;
				}
			}
		});
	}

	/*
	 * @see
	 * org.droidtv.broadcasttv.InstallationScreen#setIntance(org.droidtv.broadcasttv
	 * .InstallationWizard) Getting the InstallationWizard instance and keeping
	 * it for screen navigation.
	 * 
	 * @params InstallationWizard wizard
	 * 
	 * @return
	 */
	@Override
	public void setInstance(InstallationWizard wizard)
	{
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
	public ScreenRequest getScreenName()
	{
		return InstallationWizard.ScreenRequest.DIGITAL_SCREEN;
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
	public void update(Observable observable, Object data)
	{
	}
	
	private void setfocusOnTheRadioList(){
		// Selected based on country/medium selection
		/*NativeAPIEnums.AnalogueOrDigital getAD = nwrap.getCachedAnalogueDigital();		
		int setDigitalAnalogIndex = 0;
		if(getAD == NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE){
			setDigitalAnalogIndex = 0;
		}else if(getAD == NativeAPIEnums.AnalogueOrDigital.DIGITAL){
			setDigitalAnalogIndex = 1;
		}else if(getAD == NativeAPIEnums.AnalogueOrDigital.ANALOGUE){
			setDigitalAnalogIndex = 2;
		}*/
		
		int DigitalAnalogIndex = nwrap.getMappedDigitalAnalogIndex();
		radioSelector.setItemChecked(DigitalAnalogIndex, true);
		radioSelector.setSelection(DigitalAnalogIndex);
		radioSelector.requestFocusFromTouch();
		radioSelector.requestFocus();		
	}

	@Override
	public void screenIntialization() {
		radioSelector.setArray(nwrap.getAnalogueDigitalList());
		// set the focus on the radio list
		setfocusOnTheRadioList();
		
	}
	
}
