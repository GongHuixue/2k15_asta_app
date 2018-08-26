package org.droidtv.euinstallersat.wizard;

import java.util.Observable;

import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallersat.model.notification.INotificationListener;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.util.InstallationCancelDialog;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardScreen;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.StrictMode;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.widget.FrameLayout;

public class SatelliteInstallationActivity extends Activity implements INotificationListener {

	private static final String TAG = SatelliteInstallationActivity.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper mWrapper;
	private NotificationHandler ntf;
	private View m_view;
	private View m_loaderView;

	private enum LAUNCHMODE{
		SATELLITE_SETTINGS,
		DIRECT_FROM_DASHBOARD
	}
	private LAUNCHMODE launchMode = LAUNCHMODE.DIRECT_FROM_DASHBOARD;
			
	private InstallationCancelDialog m_displayDialog;
	private FrameLayout m_frameLayout;

	private boolean tuner1InitDone = false;
	private boolean tuner2InitDone = false;
	
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mContext = this;
		Log.d(TAG, "OnCreate");
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		mWrapper = NativeAPIWrapper.getInstance();
		mWrapper.setApplicationContext(this);
		
		if(mWrapper.ifRecordingIsInProgress()){
			mWrapper.showRecordingMessage();
			finish();
			
		}else{
		
			StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder().detectAll().penaltyLog().build());
	
			ntf = NotificationHandler.getInstance();
			ntf.registerForNotification(this);
	
			String l_launchType = null;
			Bundle l_bundle = getIntent().getExtras();
			if (l_bundle != null) {
				l_launchType = (String) l_bundle.get("LaunchMode");
			}
			Log.d(TAG, "LaunchMode " + l_launchType);
			
			mWrapper.muteAudio(true);
			
			mWrapper.setApplicationState(NativeAPIWrapper.STATE_WIZARD);
			instActManager.addActivityToStack(this);
	
			m_frameLayout = new FrameLayout(this);
			LayoutInflater l_inflater = (LayoutInflater) this
					.getSystemService(LAYOUT_INFLATER_SERVICE);
	
			m_view = l_inflater.inflate(R.layout.main, null);
			m_loaderView = l_inflater.inflate(R.layout.application_loader, null);
			m_frameLayout.addView(m_view);
			m_frameLayout.addView(m_loaderView);
	
			Log.d(TAG, "ui thread id : " + android.os.Process.myTid());
			setContentView(m_frameLayout);
	
			// reset to Tuner1 selection
			mWrapper.setTuner2Active(false);
			if (l_launchType == null) {
			
				tuner1InitDone = false;
				tuner2InitDone = false;
	
				launchMode = LAUNCHMODE.DIRECT_FROM_DASHBOARD;
				Log.d(TAG, "launchMode " + launchMode);
				
				// setdatasource for TUNER1 & TUNER2
				//mWrapper.initTVMediaPlayer(NativeAPIWrapper.TunerName.TUNER1);
				//mWrapper.initTVMediaPlayer(NativeAPIWrapper.TunerName.TUNER2);
				
				if(mWrapper.isTwoTunerSupported()) {
					mWrapper.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
					// do setdatasource for aux only if tuner2 NVM is set
					// aneesh
					if(mWrapper.dualTunerSelectedInNVM()){
						mWrapper.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_AUX);
					}else{
						tuner2InitDone = true;
						onInitDone();
					}
				}else{
					tuner2InitDone = true;
					mWrapper.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
				}
			} else {
				launchMode = LAUNCHMODE.SATELLITE_SETTINGS;
				Log.d(TAG, "launchMode " + launchMode);
				
				tuner1InitDone = true;
				tuner2InitDone = false;
	
				// tigger setdatasource for TUNER2 only as for TUNER1 setdatasource is already done
				//mWrapper.initTVMediaPlayer(NativeAPIWrapper.TunerName.TUNER2);
				if(mWrapper.isTwoTunerSupported()) {
					if(mWrapper.dualTunerSelectedInNVM()){
						mWrapper.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_AUX);
					}else{
						tuner2InitDone = true;
						onInitDone();
					}
				}else{
					tuner2InitDone = true;
					onInitDone();
				}
			}
		}
	}

	@Override
	public void finish() {
		super.finish();
		overridePendingTransition(0, 0);
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		Log.d(TAG, "dispatchKeyEvent for satellite wizard activity");
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		boolean l_ret = true;
		switch (keyCode) {
		case KeyEvent.KEYCODE_BACK:
		case KeyEvent.KEYCODE_ESCAPE:
			if (keyAction == KeyEvent.ACTION_UP) {
				if (super.dispatchKeyEvent(event) == false) {
					if(mSatelliteWizard == null){
						// system still stuck in loading animation & back key pressed
						exitInstallationWizard();
					}else{
						m_displayDialog = new InstallationCancelDialog(this,
								mSatelliteWizard);
						m_displayDialog.showDialog();
					}
				}
			}
			l_ret = true;
			break;
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

		Log.d(TAG, "dispatchKeyEvent for satellite wizard activity returning "
				+ l_ret);
		return l_ret;

	}

	@Override
	protected void onStart() {
		Log.d(TAG, "onStart");
		super.onStart();
		mWrapper.enterNonInteruptableMode();
	}

	@Override
	protected void onResume() {
		Log.d(TAG, "onResume");
		super.onResume();
	}

	@Override
	protected void onPause() {
		Log.d(TAG, "onPause");
		super.onPause();
	}

	@Override
	protected void onStop() {
		Log.d(TAG, "onStop");
		super.onStop();
	}

	@Override
	protected void onDestroy() {
		Log.d(TAG, "onDestroy launchMode:" + launchMode);
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
		
	}
	
	public void exitInstallationWizard(){
		switch(launchMode){
		case DIRECT_FROM_DASHBOARD:
			instActManager.exitInstallation(EXIT_INSTALLER_REASON.USER_TRIGGERED_EXIT);
			break;
		case SATELLITE_SETTINGS:
			mWrapper.exitNonInteruptableMode();
			finish();
			break;
		default:
			break;
		}
	}

	private void onInitDone() {
		Log.d(TAG, "onInitDone tuner1InitDone:" + tuner1InitDone + " tuner2InitDone:" + tuner2InitDone);
		if (tuner1InitDone && tuner2InitDone) {
			tuner1InitDone = true;
			tuner2InitDone = true;
			Log.d(TAG, "onInitDone entry1");
			//set Tuner2 to idle mode
			if(mWrapper.dualTunerSelectedInNVM()){
				mWrapper.setTunerToIdleMode(TunerName.TUNER2, true);
			}
			
			ntf.unRegisterForNotification(this);

			((Activity)mContext).runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Log.d(TAG, "run in UI thread");
					m_frameLayout.removeView(m_loaderView);
					mSatelliteWizard = (SatelliteWizard) View.inflate(mContext, R.layout.satelliteinstallation, null);
					WizardScreen wizardScreen = (WizardScreen) findViewById(R.id.wizardScreen);
					mSatelliteWizard.setWizardScreen(wizardScreen);
					mSatelliteWizard.initWizardScreen();
				}
			});
		}
		Log.d(TAG, "onInitDone exit " + (tuner1InitDone && tuner2InitDone));
	}

	@Override
	public void update(Observable arg0, Object data) {

		int l_eventID = ((NotificationInfoObject) data).actionID;
		switch (l_eventID) {
		case EventIDs.NATIVELAYER_INIT_DONE:
			Log.d(TAG, "NATIVELAYER_INIT_DONE");
			tuner1InitDone = true;
			onInitDone();
			break;
		case EventIDs.NATIVELAYER_INIT_DONE_TUNER2:
			Log.d(TAG, "NATIVELAYER_INIT_DONE_TUNER2");
			tuner2InitDone = true;
			onInitDone();
			break;
		}

	}

}
