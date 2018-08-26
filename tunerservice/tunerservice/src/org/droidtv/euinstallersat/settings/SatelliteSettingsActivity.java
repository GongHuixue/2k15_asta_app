package org.droidtv.euinstallersat.settings;

import java.util.HashMap;
import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallersat.model.notification.INotificationListener;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.settings.EasyPqView;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.ICompanionWidgetControl;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.util.ContextHelper;
import org.droidtv.ui.tvwidget2k15.ColorKeys;
import org.droidtv.ui.tvwidget2k15.NPanelBrowser;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuBuilder;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.CustomMenuInflater;
import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.widget.FrameLayout;

public class SatelliteSettingsActivity extends Activity implements INotificationListener
{
	private ColorKeys mColourKeyBar;
	private static final String TAG = SatelliteSettingsActivity.class.getName();
	private Activity m_context;
	private NativeAPIWrapper nwrap = null;
	private FrameLayout m_frameLayout;
	private NPanelBrowser m_browser;
	private View m_settingsView;
	private View m_loaderView;
	private EasyPqView mEasyPQView;
	private boolean m_isUIInitDone = false;
	private SettingsHandler mSettingsHandler;
	private MenuBuilder mBuilder;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		m_context = this;		
		Log.d(TAG, "OnCreate");
		// Initialize NativeAPIWrapper and pass application context
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		nwrap  = NativeAPIWrapper.getInstance();
		nwrap.setApplicationContext(this);
		
		if(nwrap.ifRecordingIsInProgress()){
			nwrap.showRecordingMessage();
			finish();
		}else{
			instActManager.addActivityToStack(this);
			nwrap.setApplicationState(NativeAPIWrapper.STATE_SETTINGS);
			nwrap.initializeCache();
			
			m_frameLayout = new FrameLayout(this);
			LayoutInflater l_inflater = (LayoutInflater)this.getSystemService(LAYOUT_INFLATER_SERVICE);
	
			m_settingsView = l_inflater.inflate(R.layout.satellite_settings_activity_layout,null);
			m_loaderView = l_inflater.inflate(R.layout.application_loader,null);
			m_frameLayout.addView(nwrap.createEuinstallerSatSurface(m_context));
	        m_frameLayout.addView(m_settingsView);
	        m_frameLayout.addView(m_loaderView);
			setContentView(m_frameLayout);
			NotificationHandler.getInstance().registerForNotification(this);
			m_isUIInitDone = false;
			
			// setdatasource for TUNER1, don't do for TUNER2 as recording might be continuing on it
			// nwrap.initTVMediaPlayer(NativeAPIWrapper.TunerName.TUNER1);
			nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
		}
	}
	
	public void showHideColorKey(boolean ifShow){
		Log.d(TAG, "showHideColorKey " + ifShow);
		
		if(ifShow){
			mColourKeyBar.setVisibility(View.VISIBLE);
		}else{
			mColourKeyBar.setVisibility(View.INVISIBLE);
		}
	}
	
	@Override
	public void finish() {
		Log.d(TAG, "finish");
		super.finish();
		overridePendingTransition(0, 0);
	}
	
	@Override
	protected void onStart()
	{
		// The activity is about to become visible.
		Log.d(TAG, "onStart");
		super.onStart();
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
    	Log.d(TAG, "onPause");
    	
    	if (isFinishing()) {
			Log.d(TAG, "onPause & the reason is activity is finishing");
		}else{
			boolean isVisible = requestVisibleBehind(true);
	        Log.d(TAG, "requestVisibleBehind returns: "+ isVisible);
	        
	        if(isVisible == false){
	        	instActManager.exitInstallation(EXIT_INSTALLER_REASON.VISIBLE_BEHIND_NOT_ALLOWED);
	        }
		}
    	/*
        if (mEasyPQView != null) {
        	mEasyPQView.onPause();
        }
        if (m_settingsListener != null) {
            m_settingsListener.clearEumContext();
        }
        */     
        super.onPause();
    }


	@Override
	protected void onStop()
	{
		Log.d(TAG, "onStop");
		super.onStop();
		/*
		if (m_settingsListener != null) {
			m_settingsListener.clearEumContext();
		}*/
		// The activity is no longer visible (it is now "stopped")
	}

	@Override
	protected void onDestroy(){

		try
		{	
			ContextHelper.getInstance().unBindEumService(m_context);
		}
		catch(Exception ex)
		{
			//Log.d(TAG,"Exception: "+ex.getMessage());
		}
			
		instActManager.removeActivityFromStack(this);
		Log.d(TAG, "onDestroy");
		super.onDestroy();
		// The activity is about to be destroyed.
	}
	
	@Override
	protected void onRestart(){
		Log.d(TAG, "onRestart");
		super.onRestart();
	}
	
	@Override
	public void onVisibleBehindCanceled() {
		Log.d(TAG, "onVisibleBehindCanceled");
		// should return within 500ms, release the resources after it otherwise android kill the activity 
		super.onVisibleBehindCanceled();
		if(instActManager != null){
			instActManager.exitInstallation(EXIT_INSTALLER_REASON.ON_VISIBLILITY_CANCELLED);
		}
	}
	
	@Override
	public boolean dispatchKeyEvent(KeyEvent event){
		int keyCode = event.getKeyCode();
        int keyAction = event.getAction();
        boolean handled = false;

        Log.d(TAG,"Keycode: " + keyCode);
        if ((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) {
            if (keyAction == KeyEvent.ACTION_DOWN) {
                instActManager.exitInstallation(EXIT_INSTALLER_REASON.USER_TRIGGERED_EXIT);                
            }
			handled = true;
        } else if((keyCode == KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE) ||
        		(keyCode == KeyEvent.KEYCODE_MEDIA_STOP ) ||
        		(keyCode == KeyEvent.KEYCODE_MEDIA_NEXT) ||
        		(keyCode == KeyEvent.KEYCODE_MEDIA_PREVIOUS ) ||
        		(keyCode == KeyEvent.KEYCODE_MEDIA_REWIND ) ||
        		(keyCode == KeyEvent.KEYCODE_MEDIA_FAST_FORWARD ) ||
        		(keyCode == KeyEvent.KEYCODE_MEDIA_PLAY ) ||
        		(keyCode == KeyEvent.KEYCODE_MEDIA_PAUSE ) ||
        		(keyCode == KeyEvent.KEYCODE_MEDIA_RECORD ) ||
        		(keyCode == KeyEvent.KEYCODE_TV_TELETEXT )  ||
        		(keyCode == KeyEvent.KEYCODE_TV_NUMBER_ENTRY  ) ||
        		(keyCode == KeyEvent.KEYCODE_CHANNEL_UP  ) ||
        		(keyCode == KeyEvent.KEYCODE_CHANNEL_DOWN  ) ||
        		(keyCode == KeyEvent.KEYCODE_INFO  ) ||
        		(keyCode == KeyEvent.KEYCODE_PICTURE_FORMAT) ||
        		(keyCode == KeyEvent.KEYCODE_TELETEXT) ||
        		(keyCode == KeyEvent.KEYCODE_GUIDE) /*||
        		(keyCode == KeyEvent.KEYCODE_TV ) */){
            	Log.d(TAG, "Consume key keyCode:" + keyCode);
        	// consume keys
        	handled = true;
        }

        return handled | super.dispatchKeyEvent(event);
        
	}
	
	private void onInitDone()
	{
		Log.d(TAG,"onInitDone entry");
		m_isUIInitDone = true;
		m_frameLayout.removeView(m_loaderView);
		m_browser = (NPanelBrowser) findViewById(R.id.SatelliteSettingsBrowser);
		//m_settingsManager = new SettingsManager(m_context);
		
		mSettingsHandler = SettingsHandler.getInstance();
		mBuilder = new MenuBuilder(m_context);
		mSettingsHandler.setContext(m_context,mBuilder);
		
		MenuItem mi = new CustomMenuInflater(m_context).inflateMenu(R.menu.satellite_settings_menu, getResources());
				
		
		HashMap<String, ICompanionWidgetControl> companionViews = new HashMap<String, ICompanionWidgetControl>();
        mEasyPQView = (EasyPqView) findViewById(R.id.easyPQView);
        companionViews.put("easyPQ", mEasyPQView);
        
        mBuilder.setCompanionViews(companionViews);
		mBuilder.setMenuData(m_browser, mi);
		
       // m_settingsManager.setCompanionViews(companionViews);
				
		// customize color keybar
		mColourKeyBar = (ColorKeys) findViewById(R.id.colorKeys);
		mColourKeyBar.setRedLabel(null);
		mColourKeyBar.setGreenLabel(null);
		mColourKeyBar.setYellowLabel(null);
		mColourKeyBar.setBlueLabel(getString(org.droidtv.ui.strings.R.string.MAIN_COLOUR_HELP));
		
		//m_settingsListener = new SatelliteSettingsListener(m_context, m_settingsManager, m_colourKeyManager);
		//m_settingsListener.init();
		//m_settingsManager.setSettingsEumListener(m_settingsListener);
		m_browser.requestFocus();
		NativeAPIWrapper.getInstance().setDefaultSettingsToMW();
		Log.d(TAG,"onInitDone exit");
	}

	@Override
	public void update(Observable arg0, Object data)
	{
		
		int l_eventID = ((NotificationInfoObject) data).actionID;
		switch (l_eventID)
		{
			case EventIDs.NATIVELAYER_INIT_DONE:
				Log.d(TAG,"NATIVELAYER_INIT_DONE");
				runOnUiThread(new Runnable()
				{
					@Override
					public void run()
					{
						if(!m_isUIInitDone)
						{
							onInitDone();
						}
					}
				});
				
				break;	
		}
		
	}
}
