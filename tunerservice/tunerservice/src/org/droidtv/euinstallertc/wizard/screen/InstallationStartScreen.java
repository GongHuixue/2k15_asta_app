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

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

/*
 * This is the initial step in the wizard installation * 
 */
public class InstallationStartScreen extends WizardStep implements
		IInstallationScreen {

	private static final String TAG = InstallationStartScreen.class.getName();
	private InstallationWizard mInstallationWizard;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private Context mContext;
	private View installationStartScreen;
	private TextView informationLine;

	public InstallationStartScreen(Context context) {
		this(context, null, 0);
	}

	public InstallationStartScreen(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public InstallationStartScreen(Context context, AttributeSet attrs,
			int defStyle) {
		super(context, attrs, defStyle);
		loadLayout(context, attrs, defStyle);
	}

	private void loadLayout(Context context, AttributeSet attrs, int defStyle) {

		mContext = context;
		
		final LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        installationStartScreen = inflater.inflate(R.layout.information_layout, null);
        addView(installationStartScreen);
        
        informationLine = (TextView) installationStartScreen.findViewById(R.id.line1String);
		
		hideHint();
		
        OnClickListener buttonStart_Listener = new OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d(TAG, "You clicked on Start button");
                if (nwrap.ifVirginInstallation()) {
                    mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.ANTENNA_SCREEN, getScreenName());
                } else {
                    if (nwrap.ifUpdateInsatallationAvailable()) {
                        mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.REINSTALL_SCREEN, getScreenName());
                    } else {
                        mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.COUNTRY_SCREEN, getScreenName());
                    }
                }
            }
        };

		OnClickListener buttonCancel_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				nwrap.stopInstallation(true);
			}
		};

        setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), buttonCancel_Listener, View.VISIBLE);
        setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), null, View.INVISIBLE);
        setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_START), buttonStart_Listener, View.VISIBLE);

		// set the focus on start button
		setButton3focussed();
	}

	@Override
	public void setInstance(InstallationWizard wizard) {
		mInstallationWizard = wizard;
		Log.d(TAG, "InstallationWizard:" + wizard);
	}

	@Override
	public ScreenRequest getScreenName() {
		return InstallationWizard.ScreenRequest.WIZARD_INSTALLATION;
	}

	@Override
	public void update(Observable observable, Object data) {
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		boolean ret = super.dispatchKeyEvent(event);
		int keyCode = event.getKeyCode();
		switch (keyCode) {
		case KeyEvent.KEYCODE_DPAD_RIGHT:
			ret = true;
			break;
		case KeyEvent.KEYCODE_DPAD_LEFT:
			ret = false;
			break;
		}
		Log.v(TAG, "dispatch key event:" + ret);
		return ret;
	}

	@Override
	public void screenIntialization() {
		
		nwrap.reInitializeCachedSelections();
		if(nwrap.ifVirginInstallation()){
		    informationLine.setText(mContext
                    .getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_START));
		}else{
    		if (nwrap.ifUpdateInsatallationAvailable()) {
    		    informationLine.setText(mContext
    					.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_START));
    		} else {
    		    informationLine.setText(mContext
    					.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_START_REINSTALL));
    		}
		}
		
		setButton3focussed();
	}
}
