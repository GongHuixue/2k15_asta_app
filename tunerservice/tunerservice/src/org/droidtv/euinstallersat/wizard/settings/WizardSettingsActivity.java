package org.droidtv.euinstallersat.wizard.settings;

import java.util.HashMap;

import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.settings.EasyPqView;
import org.droidtv.euinstallersat.settings.SettingsHandler;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.tunerservice.R;
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

public class WizardSettingsActivity extends Activity
{
    
    private final String TAG = WizardSettingsActivity.class.getName();
	private WizardColourKeyManager m_colourKeyManager;
	private ColorKeys m_colourKeyBar;
	private Activity m_context;
	private NotificationHandler m_ntfHandler;
	private EasyPqView mEasyPQView;
	private WizardSettingsHandler mWizardSettingsHandler;
	private SettingsHandler mSettingsHandler;
	private MenuBuilder mBuilder;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		Log.d(TAG, "OnCreate");
		//this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		m_context = this;	
		instActManager.addActivityToStack(this);
		setContentView(R.layout.wizard_settings_activity_layout);
		NPanelBrowser npb = (NPanelBrowser) findViewById(R.id.SatelliteWizardSettingsBrowser);
		
		mBuilder = new MenuBuilder(m_context);
		mWizardSettingsHandler = WizardSettingsHandler.getInstance();
		mWizardSettingsHandler.setContext(m_context, mBuilder);
		
		mSettingsHandler = SettingsHandler.getInstance();
		mSettingsHandler.setContext(m_context,mBuilder);

		MenuItem mi = new CustomMenuInflater(m_context).inflateMenu(R.menu.satellite_settings_wizard_menu, getResources());
		
		//m_settingsManager = new SettingsManager(m_context);
		
		HashMap<String, ICompanionWidgetControl> companionViews = new HashMap<String, ICompanionWidgetControl>();
        mEasyPQView = (EasyPqView) findViewById(R.id.easyPQView);
        companionViews.put("easyPQ", mEasyPQView);
       // m_settingsManager.setCompanionViews(companionViews);
		
		m_colourKeyBar = (ColorKeys) findViewById(R.id.widget_colorKeys);
		m_colourKeyManager = new WizardColourKeyManager(m_colourKeyBar,m_context);
		
		mBuilder.setCompanionViews(companionViews);
		mBuilder.setMenuData(npb, mi);
		
		m_ntfHandler = NotificationHandler.getInstance();
		npb.requestFocus();		
	}
	
	
	
	@Override
	protected void onStart()
	{
		super.onStart();
		Log.d(TAG, "onStart");
		// The activity is about to become visible.
	}

	@Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "onResume");
        /*if (mEasyPQView != null) {
            mEasyPQView.onResume();
        }*/
    }

    @Override
    protected void onPause() {
        // m_settingsListener.clearEumContext();
        super.onPause();
        Log.d(TAG, "onPause");
       /* if (mEasyPQView != null) {
            mEasyPQView.onPause();
        }*/
    }

	@Override
	protected void onStop()
	{
		super.onStop();
		Log.d(TAG, "onStop");
		// The activity is no longer visible (it is now "stopped")
	}

	@Override
	protected void onDestroy()
	{
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		super.onDestroy();		
	}
	
	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		Log.d(TAG, "dispatchKeyEvent");
		m_colourKeyBar.handleKeyDown(event.getKeyCode());
		if((event.getKeyCode() == KeyEvent.KEYCODE_BACK) || (event.getKeyCode() == KeyEvent.KEYCODE_ESCAPE))
		{
			m_ntfHandler.notifyAllObservers(EventIDs.WIZARD_SETTINGS_EXIT,"");
		}
		return super.dispatchKeyEvent(event);
	}
	
	@Override
	public void finish() {
		super.finish();
		overridePendingTransition(0, 0);
	}

}
