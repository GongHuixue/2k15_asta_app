package org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard;
import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeWizard.ConnTypeScreenReq;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardScreen;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;

public class ConnTypeActivity extends Activity
{

	private final String TAG = ConnTypeActivity.class.getName();
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	private ConnTypeScreenReq firstScreen = ConnTypeScreenReq.SETTINGS;
	
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		Log.d(TAG,"onCreate");
		
		super.onCreate(savedInstanceState);
		
		Bundle bundle = getIntent().getExtras();
				
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		instActManager.addActivityToStack(this);
		setContentView(R.layout.main);
		
		firstScreen = ConnTypeScreenReq.SETTINGS;
		if (bundle != null) {
			String launchScreen = (String) bundle.get("LaunchScreen");
			if((launchScreen!=null) && (launchScreen.equalsIgnoreCase("LNBSelection"))){
				firstScreen = ConnTypeScreenReq.LNBSELECTION;
			}
		}
		
		ConnTypeWizard connTypeWizard;
		connTypeWizard = (ConnTypeWizard) View.inflate(this, R.layout.connection_type_wizard, null);
		WizardScreen l_wizardScreen = (WizardScreen) findViewById(R.id.wizardScreen);
		connTypeWizard.setWizardScreen(l_wizardScreen);
		connTypeWizard.initWizardScreen();
	}
	
	public ConnTypeScreenReq firstScreen(){
		return firstScreen;
	}
	
	@Override
	protected void onDestroy(){
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
	}
	
	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		int l_keyCode = event.getKeyCode();
		boolean l_ret = true;
		switch(l_keyCode)
		{
			case KeyEvent.KEYCODE_DPAD_LEFT:
			case KeyEvent.KEYCODE_DPAD_RIGHT:
			case KeyEvent.KEYCODE_DPAD_UP:
			case KeyEvent.KEYCODE_DPAD_DOWN:
				l_ret = super.dispatchKeyEvent(event);
				break;
			case KeyEvent.KEYCODE_VOLUME_DOWN:
			case KeyEvent.KEYCODE_VOLUME_UP:
			case KeyEvent.KEYCODE_VOLUME_MUTE:
				l_ret = false;
				break;
			default:
				super.dispatchKeyEvent(event);
				l_ret = true;
				break;
		}
		return l_ret;
	}
}
