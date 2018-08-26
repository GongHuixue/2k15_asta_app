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
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.settings.EasyPqView;
import org.droidtv.euinstallertc.settings.SettingsHandler;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.CustomMenuInflater;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuBuilder;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.ICompanionWidgetControl;

import org.droidtv.euinstallertc.util.ContextHelper;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.ui.tvwidget2k15.ColorKeys;
import org.droidtv.ui.tvwidget2k15.NPanelBrowser;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.widget.FrameLayout;
//[TF415PHIEUMTK66-1720] Some menu items in professional menu are changed in the Guest language. start
import android.content.pm.PackageManager;
import android.content.res.Resources;
import java.util.Locale;
import android.content.res.Configuration;
import android.content.Intent;
//[TF415PHIEUMTK66-1720] Some menu items in professional menu are changed in the Guest language. end
public class AnalogueManualInstallationActivity extends Activity implements Observer
{
	private static final String TAG = AnalogueManualInstallationActivity.class.getName();
	private SettingsHandler mSettingsHandler;
	private EasyPqView mEasyPQView;
	private AnalogueManualInstallationActivity m_context;
	private FrameLayout m_frameLayout;
	private MenuBuilder mBuilder;
	private ColorKeys mColourKeyBar;
	private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();
	private NotificationHandler m_ntf = NotificationHandler.getInstance();
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	private InitAsyncTask m_initAsyncTask;
	private static final String INIT_MW = "INIT_MW";
	private static final String INIT_UI = "INIT_UI";
	
	private boolean ifDTRScreenActive = false;
	
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		Log.d(TAG, "OnCreate Enter");
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
			ifDTRScreenActive = false;
			m_wrapper.setApplicationState(NativeAPIEnums.ApplicationState.INST_SETTINGS);
			instActManager.addActivityToStack(this);
			
			m_frameLayout = new FrameLayout(this);
			LayoutInflater l_inflater = (LayoutInflater) this.getSystemService(LAYOUT_INFLATER_SERVICE);
			View l_settingsView = l_inflater.inflate(R.layout.analogue_manual_installation_layout, null);
			
			m_frameLayout.addView(m_wrapper.createTCSurface(m_context));
			m_frameLayout.addView(l_settingsView);
	
			// setContentView(m_frameLayout);
			setContentView(R.layout.application_loader);
			m_ntf.registerForNotification(m_context);
	
			m_initAsyncTask = new InitAsyncTask();
			m_initAsyncTask.execute(INIT_MW);
			
			// initialize for session creation. Callback sends EVENT_INST_ONPREPAREDTV
			m_wrapper.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
		}

		Log.d(TAG, "OnCreate Exit");
	}
	
	public void ifDtrScreenActive(boolean ifActive){
		Log.d(TAG, "ifDtrScreenActive " + ifActive);
		ifDTRScreenActive = ifActive;
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
	public void onVisibleBehindCanceled() {
		Log.d(TAG, "onVisibleBehindCanceled");
		// should return within 500ms, release the resources after it otherwise android kill the activity 
		super.onVisibleBehindCanceled();
		if(instActManager != null){
			instActManager.exitInstallation(EXIT_INSTALLER_REASON.ON_VISIBLILITY_CANCELLED);
		}
	}
	
	@Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        int keyCode = event.getKeyCode();
        int keyAction = event.getAction();
        boolean handled = false;

        Log.d(TAG,"Keycode: " + keyCode);
        if ((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) {
            if (keyAction == KeyEvent.ACTION_DOWN) {
            	if(ifDTRScreenActive){
            		//let dtr screen handle back key
            	}else{
            		instActManager.exitInstallation(EXIT_INSTALLER_REASON.USER_TRIGGERED_EXIT);       
            	}
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
        } else if (keyCode == KeyEvent.KEYCODE_PROG_BLUE) {
        	handled = true;
        }

        return handled | super.dispatchKeyEvent(event);
    }
	@Override
	protected void onStart() {
		Log.d(TAG, "onStart");
		super.onStart();
	}

	@Override
	protected void onSaveInstanceState(Bundle savedInstanceState) {
		Log.d(TAG, "onSaveInstanceState");
		super.onSaveInstanceState(savedInstanceState);
	}

	@Override
	protected void onRestoreInstanceState(Bundle savedInstanceState) {
		Log.d(TAG, "onRestoreInstanceState");
		super.onRestoreInstanceState(savedInstanceState);
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
		}else{
			boolean isVisible = requestVisibleBehind(true);
	        Log.d(TAG, "requestVisibleBehind returns: "+ isVisible);
	        
	        if(isVisible == false){
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
	protected void onDestroy()
	{
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		ContextHelper.getInstance().unBindEumService(m_context);
		ifDTRScreenActive = false;

		super.onDestroy();
	}

	@Override
	protected void onRestart(){
		Log.d(TAG, "onRestart");
		super.onRestart();
	}
	
	@Override
	public void finish() {
		Log.d(TAG, "finish");
		super.finish();
		overridePendingTransition(0, 0);
	}

	class InitAsyncTask extends AsyncTask<String, Void, String>{

		@Override
		protected void onPostExecute(String result)
		{
			super.onPostExecute(result);
			Log.d(TAG, "onPostExecute enter result " + result);

			if (result.equals(INIT_MW))
			{

			} else if (result.equals(INIT_UI))
			{
				m_ntf.unregisterForNotification(m_context);
				setContentView(m_frameLayout);

				NPanelBrowser npb = (NPanelBrowser) findViewById(R.id.euChannelSettingsBrowser);
				npb.setVisibility(View.VISIBLE);
				
				mSettingsHandler = SettingsHandler.getInstance();
				mBuilder = new MenuBuilder(m_context);
				mSettingsHandler.setContext(m_context,mBuilder);
				
				MenuItem mi = new CustomMenuInflater(m_context).inflateMenu(R.menu.analogue_manual_installation_menu, getResources());
				
				HashMap<String, ICompanionWidgetControl> companionView = new HashMap<String, ICompanionWidgetControl>();
				mEasyPQView = (EasyPqView)findViewById(R.id.easyPQView);
				companionView.put("easyPQ", mEasyPQView);
				mBuilder.setCompanionViews(companionView);
				mBuilder.setMenuData(npb, mi);
				npb.requestFocus();
				
				// customize color keybar
				mColourKeyBar = (ColorKeys) findViewById(R.id.colorKeys);
				mColourKeyBar.setRedLabel(null);
				mColourKeyBar.setGreenLabel(null);
				mColourKeyBar.setYellowLabel(null);
				//mColourKeyBar.setBlueLabel(getString(org.droidtv.ui.strings.R.string.MAIN_COLOUR_HELP));
				mColourKeyBar.setBlueLabel(null);

				// customize color keybar
			}

			Log.d(TAG, "onPostExecute exit");
		}

		@Override
		protected String doInBackground(String... params)
		{
			Log.d(TAG, "doInBackground params: " + params[0]);
			if ((params[0]).equalsIgnoreCase(INIT_MW))
			{
				//m_wrapper.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); // initialize for set data source. Callback sends EVENT_INST_ONPREPAREDTV 
				// now call will come in update function with event EVENT_INST_ONPREPAREDTV
			}
			return params[0];
		}
	}

	@Override
	public void update(Observable observable, Object data)
	{
		final int eventID = ((NotificationInfoObject) data).actionID;
		switch (eventID)
		{
		case EventIDs.EVENT_INST_ONPREPAREDTV:
			Log.d(TAG, "EVENT_INST_ONPREPAREDTV ");
			// async task instance must be created in UI thread
				m_initAsyncTask = new InitAsyncTask();
				m_initAsyncTask.execute(INIT_UI);
			break;

		}
	}

}