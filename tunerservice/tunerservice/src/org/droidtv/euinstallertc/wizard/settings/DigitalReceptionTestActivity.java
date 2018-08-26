/*
 *  Copyright(C) 2015 TP Vision Holding B.V.,
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
import java.util.Observable;
import java.util.Observer;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.settings.EasyPqView;
import org.droidtv.euinstallertc.util.ContextHelper;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.ui.tvwidget2k15.NPanelBrowser;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.CustomMenuInflater;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuBuilder;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.ICompanionWidgetControl;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.LayoutInflater;
import android.widget.FrameLayout;
//[TF415PHIEUMTK66-1720] Some menu items in professional menu are changed in the Guest language. start
import android.content.pm.PackageManager;
import android.content.res.Resources;
import java.util.Locale;
import android.content.res.Configuration;
import android.content.Intent;
//[TF415PHIEUMTK66-1720] Some menu items in professional menu are changed in the Guest language. end
public class DigitalReceptionTestActivity extends Activity implements Observer {
    private static final String TAG = DigitalReceptionTestActivity.class.getName();
    private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();
    private DigitalReceptionTestActivity m_context;
    private FrameLayout m_frameLayout;
    private MenuBuilder mBuilder;
    private EasyPqView mEasyPQView;
	private ITvSettingsManager mTvSettingsManager = ITvSettingsManager.Instance.getInterface();
	private NotificationHandler mNtf = NotificationHandler.getInstance();
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
    	Log.d(TAG, "onCreate Enter");
        super.onCreate(savedInstanceState);
	//[TF415PHIEUMTK66-1720] Some menu items in professional menu are changed in the Guest language. start
	Intent callIntent=  getIntent();
	if (callIntent != null){
		String PBSCall = callIntent.getStringExtra("PBSCall");
		if (PBSCall != null){
			if (PBSCall.equals("true")){
				Resources res = getApplicationContext().getResources();
				Locale locale = new Locale("en");
				Locale.setDefault(locale);

				Configuration config = new Configuration();
				config.locale = locale;

				res.updateConfiguration(config, res.getDisplayMetrics());
			}
		}
	}
	//[TF415PHIEUMTK66-1720] Some menu items in professional menu are changed in the Guest language.end
        m_context = this;
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        m_wrapper.setApplicationContext(this);

		if(m_wrapper.ifRecordingIsInProgress()){
			m_wrapper.showRecordingMessage();
			finish();
		}else{
			m_wrapper.setApplicationState(NativeAPIEnums.ApplicationState.INST_WIZARD);
			m_wrapper.enterNonInteruptableMode();
			instActManager.addActivityToStack(this);

			m_frameLayout = new FrameLayout(this);
			LayoutInflater l_inflater = (LayoutInflater) this.getSystemService(LAYOUT_INFLATER_SERVICE);
			View l_settingsView = l_inflater.inflate(R.layout.digital_reception_test_layout, null);
			
        	m_frameLayout.addView(m_wrapper.createTCSurface(m_context));
	        m_frameLayout.addView(l_settingsView);

    	    setContentView(m_frameLayout);
			mNtf.registerForNotification(m_context);

        	NPanelBrowser npb = (NPanelBrowser) findViewById(R.id.euChannelSettingsBrowser);
	        npb.setVisibility(View.VISIBLE);

    	    MenuItem mi = new CustomMenuInflater(m_context).inflateMenu(R.menu.digital_reception_test_menu, getResources());
	        HashMap<String, ICompanionWidgetControl> companionView = new HashMap<String, ICompanionWidgetControl>();
    	    mEasyPQView = (EasyPqView)findViewById(R.id.easyPQView);
        	companionView.put("easyPQ", mEasyPQView);

	        mBuilder = new MenuBuilder(m_context);
    	    mBuilder.setCompanionViews(companionView);
        	mBuilder.setMenuData(npb, mi);
	        npb.requestFocus();
			if (PlayTvUtils.isPbsMode()) {
				m_wrapper.setLCNSortingControl(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_LCN, 0, 0));
			} else {
				m_wrapper.setLCNSortingControl(1);
			}
			m_wrapper.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
		}
		
        Log.d(TAG, "OnCreate Exit");
    }

	@Override
	protected void onStart() {
		Log.d(TAG, "onStart");
		super.onStart();
	}

	@Override
	protected void onResume(){
		Log.d(TAG, "onResume");
		super.onResume();
	}

	@Override
    protected void onPause() {
    	Log.d(TAG, "onPause");
      
    	if (isFinishing()) {
			Log.d(TAG, "onPause & the reason is activity is finishing");
		} else {
			boolean isVisible = requestVisibleBehind(true);
			
	        Log.d(TAG, "requestVisibleBehind returns: " + isVisible);
	        if (isVisible == false) {
	        	instActManager.exitInstallation(EXIT_INSTALLER_REASON.VISIBLE_BEHIND_NOT_ALLOWED);
	        }
		}
    	
        super.onPause();
    }

	@Override
    protected void onStop() {
    	Log.d(TAG, "onStop");
        super.onStop();
    }

	@Override
	protected void onDestroy() {
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		ContextHelper.getInstance().unBindEumService(m_context);
		super.onDestroy();
	}

	@Override
	public void finish() {
		Log.d(TAG, "finish");
		super.finish();
		overridePendingTransition(0, 0);
	}

	@Override
	public void update(Observable observable, Object data) {
		
	}
}
