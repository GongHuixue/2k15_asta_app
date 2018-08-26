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

import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
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
import android.widget.Button;

public class TerrestrialOperatorScreen extends WizardStep implements IInstallationScreen
{
	private static final String TAG = TerrestrialOperatorScreen.class.getName();
	private InstallationWizard mInstallationWizard;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private RadioSelector radioSelector;
	private Context mContext;

	public TerrestrialOperatorScreen(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		mContext = context;
		loadLayout(context, attrs, defStyle);
	}

	public TerrestrialOperatorScreen(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);
	}

	public TerrestrialOperatorScreen(Context context)
	{
		this(context, null, 0);
	}

	/*
	 * This method is responsible for setting the view to wizard step and it will change button names,make it visible or invisible.
	 * setting hint text.
	 * Displays list of Operators.
	 * On selection of the operator it will navigate to channel search screen
	 *
	 * 
	 * @params context,attribute set,default style
	 */
	private void loadLayout(Context context, AttributeSet attrs, int defStyle)
	{

		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		
		addView(view);
		
		//OnClick Listener for NEXT button 
		OnClickListener buttonNext_Listener = new OnClickListener(){
			@Override
			public void onClick(View v) {
				int selectedItem = radioSelector.getCheckedItemPosition();
				if(selectedItem == 0){
					// cam based installation
					nwrap.selectCamBasedInstallation();
					mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN,getScreenName());
				}else if(selectedItem == 1){
					// Full Selected resume normal code same as antenna/cable selection screen
					if ( NativeAPIEnums.DVBTOrDVBC.DVBT== nwrap.getCachedDVBTOrDVBC()) {
						// antenna
						mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
					}else{
						//cable
						if (PlayTvUtils.isPbsMode()) {
							nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE);
							mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
						} else {
							mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.DIGITAL_SCREEN, getScreenName());
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
		
		radioSelector.setOnItemClickListener(new OnItemClickListener()
		{
			@Override
			public void onItemClick(AdapterView<?> arg0, View selectedView,int selectedItem, long arg3)
			{
			    Log.d(TAG, "selected Item:" + selectedItem);
			    if(selectedItem == 0)
				{
			    	nwrap.selectCamBasedInstallation();
				}
				setButton3focussed();
			}
		});

		setHintText("Choose your operator");

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
		return InstallationWizard.ScreenRequest.TERRIESTRIAL_OPERATOR_SCREEN;
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
		int setOperatorIndex = 0;			
		radioSelector.setItemChecked(setOperatorIndex, true);
		radioSelector.setSelection(setOperatorIndex);
		radioSelector.requestFocusFromTouch();
		radioSelector.requestFocus();	
	}

	@Override
	public void screenIntialization() {
		String[] l_OpList = new String[]{nwrap.getCamBasedOpName(),
										"Full"};
		radioSelector.setArray(l_OpList);

		setfocusOnTheRadioList();
		
	}

}
