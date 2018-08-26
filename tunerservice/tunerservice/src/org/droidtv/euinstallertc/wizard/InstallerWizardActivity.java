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
package org.droidtv.euinstallertc.wizard;

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
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.FocusFinder;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.Button;
//[TF415PHIEUMTK66-1720] Some menu items in professional menu are changed in the Guest language. start
import android.content.pm.PackageManager;
import android.content.res.Resources;
import java.util.Locale;
import android.content.res.Configuration;
import android.content.Intent;
//[TF415PHIEUMTK66-1720] Some menu items in professional menu are changed in the Guest language. end

public class InstallerWizardActivity extends Activity implements Observer{
	public InstallerWizardActivity ctx;
	private InstallationWizard wizardInstallation;
	private static final String TAG = InstallerWizardActivity.class.getName();
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private String ChannelSettings = "ChannelSettings";
	private boolean LaunchedByChannelSettings = false;
	private InitFramwkInteractWithUI asyncInitTask;
	private static final String INIT_MW = "INIT_MW";
	private static final String INIT_UI = "INIT_UI";
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	// notification instance handler holder
	private NotificationHandler ntf = NotificationHandler.getInstance();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d(TAG, "OnCreate Enter");
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
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);

		ctx = this;
		nwrap.setApplicationContext(ctx);
		
		if(nwrap.ifRecordingIsInProgress()){
			nwrap.showRecordingMessage();
			finish();
		}else{
			nwrap.setApplicationState(NativeAPIEnums.ApplicationState.INST_WIZARD);
			instActManager.addActivityToStack(this);
			nwrap.enterNonInteruptableMode();
			
			Bundle extras = getIntent().getExtras();
			if (extras != null) {
				if (ChannelSettings.equalsIgnoreCase(extras
						.getString("IntentParent"))) {
					Log.d(TAG, "Wizard launched from Channel Settings");
					LaunchedByChannelSettings = true;
				}
			}
			
			//setContentView(R.layout.activity_main);

			setContentView(R.layout.application_loader);
			ntf.registerForNotification(ctx);
			nwrap.muteAudio(true);
			
			if (LaunchedByChannelSettings) {
				nwrap.setApplicationState(NativeAPIEnums.ApplicationState.INST_SETTINGS_WIZARD);
				// launched from channels settings MW instance creation &
				// init tv media player already taken care
				asyncInitTask = new InitFramwkInteractWithUI();
				asyncInitTask.execute(INIT_UI);
				
			} else {
				super.setTheme( org.droidtv.tunerservice.R.style.transparent_theme);
				nwrap.setApplicationState(NativeAPIEnums.ApplicationState.INST_WIZARD);
				asyncInitTask = new InitFramwkInteractWithUI();
				asyncInitTask.execute(INIT_MW);
				
				// initialize for session creation. Callback sends EVENT_INST_ONPREPAREDTV
				nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
			}
		}
		Log.d(TAG, "OnCreate Exit");
	}
	
	@Override
	public void onVisibleBehindCanceled() {
		Log.d(TAG, "onVisibleBehindCanceled");
		// should return within 500ms, release the resources after it otherwise android kill the activity 
		super.onVisibleBehindCanceled();
		
		if(false == LaunchedByChannelSettings){
			if(instActManager != null){
				instActManager.exitInstallation(EXIT_INSTALLER_REASON.ON_VISIBLILITY_CANCELLED);
			}
		}
	}

	class InitFramwkInteractWithUI extends AsyncTask<String, Void, String> {

		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			Log.d(TAG, "onPostExecute enter result " + result);

			if (result.equals(INIT_MW)) {

			} else if (result.equals(INIT_UI)) {
				ntf.unregisterForNotification(ctx);
				setContentView(R.layout.activity_main);
				wizardInstallation = (InstallationWizard) View.inflate(ctx,
						R.layout.installation, null);
				Log.d(TAG, "wizardInstallation " + wizardInstallation);
				WizardScreen wizardScreen = (WizardScreen) findViewById(R.id.wizardScreen);
				Log.d(TAG, " wizardScreen " + wizardScreen);
				wizardInstallation.setWizardScreen(wizardScreen);
				wizardInstallation.initWizardScreen();
				
			}

			Log.d(TAG, "onPostExecute exit");
		}

		@Override
		protected String doInBackground(String... params) {
			Log.d(TAG, "doInBackground params: " + params[0]);
			if ((params[0]).equalsIgnoreCase(INIT_MW)) {
				//nwrap.createMWInstance(ctx); // create MW instance
				//nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
				// now call will come in update function with event
				// EVENT_INST_ONPREPAREDTV
			}
			return params[0];
		}
	}

	public void exitInstallationWizard(){
		if(true == LaunchedByChannelSettings){
			// just finish the activity don't release any resource
			finish();
		}else{
			// release all resources 
			instActManager.exitInstallation(EXIT_INSTALLER_REASON.USER_TRIGGERED_EXIT);
		}
	}
	
	@Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        int keyCode = event.getKeyCode();
        int keyAction = event.getAction();
        boolean handled = false;

        View currentFocus;
        View leftFocus = null;
        View rightFocus = null;

        currentFocus = getCurrentFocus();
        if (currentFocus != null) {
            leftFocus = FocusFinder.getInstance().findNextFocus((ViewGroup) currentFocus.getParent(), currentFocus, View.FOCUS_LEFT);
            rightFocus = FocusFinder.getInstance().findNextFocus((ViewGroup) currentFocus.getParent(), currentFocus, View.FOCUS_RIGHT);
        }

        if ((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) {
            if (keyAction == KeyEvent.ACTION_DOWN) {
                if ((wizardInstallation != null ) &&((wizardInstallation.getCurrentScreen() == InstallationWizard.ScreenRequest.FINISH_SCREEN)
                        || (wizardInstallation.getCurrentScreen() == InstallationWizard.ScreenRequest.UPDATEFINISHED_SCREEN) 
                        || (wizardInstallation.getCurrentScreen() == InstallationWizard.ScreenRequest.HBBTV_PRIVACY_STATEMENT))) {
                    // ignore back key
                    handled = true;
                } else {
                	if(nwrap.ifEnteredSortingPhase() == false){
	                	mBuilder = new ModalDialog.Builder(ctx,ModalDialog.HEADING_TYPE_DEFAULT);
	                    mBuilder.setHeading(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_TI_AUTOSTORE_STOP), "");
	                	mBuilder.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_STOP));
                	
	                	ModalDialogFooterButtonProp mNoButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
	                			ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NO),
	                			true,
	                			new ModalDialogInterface.OnClickListener(){
	                				@Override
	                				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
	                					Log.d(TAG, "Stop cancelled Resume");
	                					mModalDialog.hide();
	                				}
	                			});
	                	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
	                			ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_YES),
	                			true,
	                			new ModalDialogInterface.OnClickListener(){
	                				@Override
	                				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
	                					 Log.d(TAG, "Stop installation");
	                					 Log.d(TAG, "Stop Dialog: Yes button pressed for screen: "
	                                             + wizardInstallation.getCurrentScreen());

	                                     if (wizardInstallation.getCurrentScreen() == InstallationWizard.ScreenRequest.SEARCHING_SCREEN) {
	                                         ntf.notifyAllObservers(EventIDs.EVENT_USER_INITIATED_STOP, "");
	                                     } else {
	                                         nwrap.stopInstallation(true);
	                                     }
	                                     mModalDialog.hide();
	                				}
	                			});
	                	mModalDialog = mBuilder.build();
	                	mModalDialog.setCancelable(false);
	                	mModalDialog.show();
	                	mNoButton.requestFocus();
					}
                }
                handled = true;
            } else if (keyAction == KeyEvent.ACTION_UP) {
                handled = true;
            }
        } else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT) {
            if (keyAction == KeyEvent.ACTION_DOWN) {

                if (currentFocus instanceof Button) {
                    // left key pressed over wizard buttons
                    if (leftFocus == null) {
                        // nothing on the left side go to previous screen
                        switch (wizardInstallation.getCurrentScreen()) {
                            case REINSTALL_SCREEN:
                            case COUNTRY_SCREEN:
                            case PINENTRY_SCREEN:
                            case TIMEZONE_SCREEN:
                            case ANTENNA_SCREEN:
                            case DIGITAL_SCREEN:
                            case OPERATOR_SCREEN:
                            case SEARCH_SCREEN:
                            case STARTUPDATE_SCREEN:
                                wizardInstallation.launchPreviousScreen();
                                break;
                            default:
                                break;
                        }
                        handled = true;
                    }
                    // else let android handled the default case
                } else if (currentFocus instanceof RadioSelector) {
                    // left key pressed over radio list
                    wizardInstallation.launchPreviousScreen();
                    handled = true;
                } else {
                    // block other default cases
                    handled = true;
                }
            } else if (keyAction == KeyEvent.ACTION_UP) {
                handled = true;
            }
        } else if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
            if (keyAction == KeyEvent.ACTION_DOWN) {

				if (currentFocus instanceof Button) {
					// right key pressed over wizard buttons
					if (rightFocus == null) {
						// nothing on the right side consume the key
						handled = true;
					}// else let android handled the default case
				} else if (currentFocus instanceof RadioSelector) {
					// right key pressed over radio list

					IInstallationScreen screenInst = wizardInstallation
							.getScreenInstance(wizardInstallation
									.getCurrentScreen());
					((WizardStep) screenInst).setButton3focussed();
                    handled = true;
                }else {
                    // block other default cases
                    handled = true;
                }
            } else if (keyAction == KeyEvent.ACTION_UP) {
                handled = true;
            }
        } else if (keyCode == KeyEvent.KEYCODE_DPAD_UP) {
            handled = super.dispatchKeyEvent(event);
        } else if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
            handled = super.dispatchKeyEvent(event);
        } else if((keyCode == KeyEvent.KEYCODE_VOLUME_DOWN) ||
        		(keyCode == KeyEvent.KEYCODE_VOLUME_UP) ||
        		(keyCode == KeyEvent.KEYCODE_VOLUME_MUTE)){
        	handled = super.dispatchKeyEvent(event);
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
        		(keyCode == KeyEvent.KEYCODE_GUIDE) ||
        		(keyCode == KeyEvent.KEYCODE_TV )
        		 ){
        	Log.d(TAG, "Consume key keyCode:" + keyCode);
        	// keys to consume
        	
        	 handled = true;
        }else {
            // for other keys let it call super to retain default behavior from wizard framework
            super.dispatchKeyEvent(event);
            handled = false;
        }

        return handled;
    }

	@Override
	protected void onRestoreInstanceState(Bundle savedInstanceState) {
		Log.d(TAG, "onRestoreInstanceState");
		super.onRestoreInstanceState(savedInstanceState);
	}

	@Override
	protected void onStart() {
		super.onStart();
		Log.d(TAG, "onStart");
	}

	@Override
	protected void onResume() {
		super.onResume();
		Log.d(TAG, "onResume");
	}

	@Override
	protected void onPause() {
		Log.d(TAG, "onPause");
		super.onPause();
		
		if(isFinishing()){
	        Log.d(TAG, "onPause & the reason is activity is finishing");
	    }else if(false == LaunchedByChannelSettings){
	    	boolean isVisible = requestVisibleBehind(true);
	        Log.d(TAG, "requestVisibleBehind returns: "+ isVisible);
	        
	        if(isVisible == false){
	        	instActManager.exitInstallation(EXIT_INSTALLER_REASON.VISIBLE_BEHIND_NOT_ALLOWED);
	        }
	    }
		
	}

	@Override
	protected void onStop() {
		super.onStop();
		Log.d(TAG, "onStop");
	}

	@Override
	protected void onDestroy() {
		Log.d(TAG, "onDestroy LaunchedByChannelSettings " + LaunchedByChannelSettings);
		instActManager.removeActivityFromStack(this);
		if(LaunchedByChannelSettings){
			// do nothing as onDestroy of CS will reset
		}else{
			//nwrap.resetNativeAPIWrapper();
		}
		super.onDestroy();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Log.d(TAG, "onRestart");
	}

	@Override
	public void update(Observable observable, Object data) {
		final int eventID = ((NotificationInfoObject) data).actionID;
		switch (eventID) {
		case EventIDs.EVENT_INST_ONPREPAREDTV:
			Log.d(TAG, "EVENT_INST_ONPREPAREDTV ");
			// async task instance must be created in UI thread
			asyncInitTask = new InitFramwkInteractWithUI();
			asyncInitTask.execute(INIT_UI);
			break;
		}		
	}
	
	@Override
	public void finish() {
		super.finish();
		overridePendingTransition(0, 0);
	}

}
