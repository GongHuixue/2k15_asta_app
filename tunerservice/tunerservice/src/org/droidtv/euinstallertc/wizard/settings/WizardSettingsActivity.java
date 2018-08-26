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
package org.droidtv.euinstallertc.wizard.settings;

import java.util.HashMap;

import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.settings.EasyPqView;
import org.droidtv.tunerservice.R;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.ui.tvwidget2k15.ColorKeys;
import org.droidtv.ui.tvwidget2k15.NPanelBrowser;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.CustomMenuInflater;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuBuilder;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.ICompanionWidgetControl;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;

public class WizardSettingsActivity extends Activity {
	private static final String TAG = WizardSettingsActivity.class.getName();
	private ColorKeys mColourKeyBar;
	private MenuBuilder mBuilder;
	private WizardSettingsActivity mContext;
	private EasyPqView mEasyPQView;
	private WizardSettingsHandler mWizardSettingsHandler;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mContext = this;
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		MenuItem mi;

		setContentView(R.layout.wizard_settings_layout);
		NPanelBrowser npb = (NPanelBrowser) findViewById(R.id.wizard_settings_nPanelBrowser);
		npb.setVisibility(View.VISIBLE);

		mWizardSettingsHandler = WizardSettingsHandler.getInstance();

		mBuilder = new MenuBuilder(mContext);
		mWizardSettingsHandler.setContext(mContext, mBuilder);

		if (PlayTvUtils.isPbsMode()) {
			mi = new CustomMenuInflater(mContext).inflateMenu(R.menu.htv_settings_wizard_menu, getResources());
		} else {
			mi = new CustomMenuInflater(mContext).inflateMenu(R.menu.settings_wizard_menu, getResources());
		}

		HashMap<String, ICompanionWidgetControl> companionView = new HashMap<String, ICompanionWidgetControl>();
		mEasyPQView = (EasyPqView)findViewById(R.id.easyPQView);
		companionView.put("easyPQ", mEasyPQView);
		mBuilder.setCompanionViews(companionView);
		mBuilder.setMenuData(npb, mi);
		npb.requestFocus();

		// customize color keybar
		mColourKeyBar = (ColorKeys) findViewById(R.id.colorKeys);
		mColourKeyBar.setRedLabel(getString(org.droidtv.ui.strings.R.string.MAIN_COLOUR_RESET));
		mColourKeyBar.setGreenLabel(getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE));
		mColourKeyBar.setYellowLabel(null);
		mColourKeyBar.setBlueLabel(null);
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		boolean handled = false;

		Log.d(TAG, " TCWizardSettingsActivity.dispatchKeyEvent keyCode " + keyCode);

		if (keyCode == KeyEvent.KEYCODE_PROG_RED) { // Red Key
			if (keyAction == KeyEvent.ACTION_DOWN) {
				// reset
				nwrap.resetWSToDefault();

				// reset ui entries
				NetworkFreqMenuItem ntwkFreqItem = (NetworkFreqMenuItem) mBuilder.findSettingsNodeById(R.id.MAIN_NETWORK_FREQUENCY);
				ntwkFreqItem.ReloadValues();

				// refresh all the nodes
				mBuilder.refreshUI();

				handled = true;
			} else if (keyAction == KeyEvent.ACTION_UP) {
				handled = true;
			}
		} else if (keyCode == KeyEvent.KEYCODE_PROG_GREEN) { // Green Key
			if (keyAction == KeyEvent.ACTION_DOWN) {

				// commit changes if pending
				NetworkFreqMenuItem ntwkFreqItem = (NetworkFreqMenuItem) mBuilder.findSettingsNodeById(R.id.MAIN_NETWORK_FREQUENCY);
				ntwkFreqItem.CommitValues();

				// done
				finish();
				handled = true;
			} else if (keyAction == KeyEvent.ACTION_UP) {
				handled = true;
			}
        }else if((keyCode == KeyEvent.KEYCODE_VOLUME_DOWN) ||
        		(keyCode == KeyEvent.KEYCODE_VOLUME_UP) ||
        		(keyCode == KeyEvent.KEYCODE_VOLUME_MUTE)){
        	handled = super.dispatchKeyEvent(event);
        }else{
        	// for other keys let it call super to retain default bheaviour from wizard framework
        	// but return true to avoid android from handling by default for activity switching
        	super.dispatchKeyEvent(event);
        	handled = true;
        }
        return handled;

    }
	
	@Override
	protected void onResume() {
		super.onResume();
		Log.d(TAG, "onResume");
		if (mEasyPQView != null) {
			// mEasyPQView.onResume();
		}
	}

	@Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG, "onStop");
    }
	

    @Override
    protected void onPause() {
        Log.d(TAG, "onPause");
        if (mEasyPQView != null) {
            //mEasyPQView.onPause();
        }
        
        if(isFinishing()){
 		   Log.d(TAG, "onPause & the reason is activity is finishing");
 		}
        
        super.onPause();
    }

    @Override
    protected void onDestroy() {
    	Log.d(TAG, "onDestroy");
    	instActManager.removeActivityFromStack(this);
        super.onDestroy();
    }
	
}
