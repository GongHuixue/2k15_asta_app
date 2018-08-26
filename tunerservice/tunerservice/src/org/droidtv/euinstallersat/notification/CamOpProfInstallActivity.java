package org.droidtv.euinstallersat.notification;

import java.util.Observable;
import java.util.Observer;

import org.droidtv.euinstallersat.ci.CIPlusUI;
import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.util.InstalledLNBCache;
import org.droidtv.euinstallersat.wizard.util.LNBInfo;
import org.droidtv.tunerservice.R;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.tvinput.ILogoAssociationControl.ILogoAssociationListener;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

public class CamOpProfInstallActivity extends Activity implements Observer {

	private static final String TAG = CamOpProfInstallActivity.class.getName();
	private NativeAPIWrapper nwrap;
	private Context mContext;

	private TextView mTvChannelAdded;
	private TextView mRadioChannelAdded;
	private TextView mPackageName;
	private TextView mVerticalText;
	private TextView mInfoTxtVw;
	private TextView mStatusText;
	private TextView mTvTitle;
	private TextView mRadioTitle;
	private View mVerticalDivider;
	private ProgressBar mScreenHeaderProgessBar;
	private ProgressBar mWaitingAnimation;

	private Button mButton;
	private OnClickListener buttonFinish_Listener;

	private LNBInfo lnbInfo;
	private CIPlusUI mCIPlusUI;
	private RadioSelector mTunerSelector;

	private ILogoAssociationControl logoAssoInt = null;
	private ListenerImpl listener = new ListenerImpl();
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	private enum ScreenMode{
		CAM_INSTALLATION,
		TUNER_SELECTION,
		FINISH
	}
	private ScreenMode currentScreenMode = ScreenMode.CAM_INSTALLATION;

	protected void onCreate(Bundle savedInstanceState) {
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		mContext = this;
		Log.d(TAG, "onCreate ");
		super.onCreate(savedInstanceState);
		nwrap = NativeAPIWrapper.getInstance();
		instActManager.addActivityToStack(this);
		nwrap.setApplicationContext(this);
		nwrap.setApplicationState(NativeAPIWrapper.STATE_WIZARD);
		currentScreenMode = ScreenMode.CAM_INSTALLATION;
		loadLayout();

	}

	private void loadLayout() {
		setContentView(R.layout.cam_operator_prof_install);
		mPackageName = (TextView) findViewById(R.id.satelnb1text);
		mTvChannelAdded = (TextView) findViewById(R.id.tvvalue);
		mRadioChannelAdded = (TextView) findViewById(R.id.radiovalue);
		mButton = (Button) findViewById(R.id.bg_finishbtn);
		mScreenHeaderProgessBar = (ProgressBar) findViewById(R.id.bgupdateInstall_Header_Progress);
		mInfoTxtVw = (TextView) findViewById(R.id.satelnb1text);
		mStatusText = (TextView) findViewById(R.id.bg_belowspinnertext);
		mVerticalDivider = (View) findViewById(R.id.bg_verticaldivider_right);
		mWaitingAnimation = (ProgressBar) findViewById(R.id.waiting_anmimation);
		mTvTitle = (TextView) findViewById(R.id.tv);
		mRadioTitle = (TextView) findViewById(R.id.radio);
		mTunerSelector = (RadioSelector) findViewById(R.id.tunerSelectionID);

		mVerticalText = (TextView) findViewById(R.id.bgupdateInstall_verticalText);
		screenIntialization();

		buttonFinish_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				switch (currentScreenMode) {
				case CAM_INSTALLATION:
					// this case will not come as from this screen as auto navigation happens
					break;
				case TUNER_SELECTION:
					int selectedPosition = mTunerSelector.getCheckedItemPosition();
					if (selectedPosition == 0) {
						nwrap.setDualTunerToTVS(false);
					} else {
						nwrap.setDualTunerToTVS(true);
					}
					nwrap.writeTunerSelectionToTVS();
					navigateToFinishScreen();
					break;
				case FINISH:
					instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
					break;
				default:
					break;
				}
				

			}
		};
		mButton.setOnClickListener(buttonFinish_Listener);
		
		/*
		navigateToTunerSelectionScreen();
		lnbInfo = new LNBInfo();
		lnbInfo.m_name = "Fransat Package";
		lnbInfo.m_tvChannelsAdded = nwrap.GetTvServices(true, 0);
		lnbInfo.m_radioChannelsAdded = nwrap.GetRadioServices(true, 0);
		navigateToFinishScreen();
		*/

	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		Log.d(TAG, "dispatchKeyEvent for background update install activity");
		int keyCode = event.getKeyCode();
	
		boolean l_ret = true;
		switch (keyCode) {
		case KeyEvent.KEYCODE_BACK:
			l_ret = true;
			break;
		default:
			l_ret = super.dispatchKeyEvent(event);
			break;
		}
		Log.d(TAG, "dispatchKeyEvent for background update install activity returning " + l_ret);
		return l_ret;

	}

	private void screenIntialization() {

		mTvChannelAdded.setText("0");
		mTvChannelAdded.setVisibility(View.GONE);
		mRadioChannelAdded.setText("0");
		mRadioChannelAdded.setVisibility(View.GONE);
		mPackageName.setVisibility(View.GONE);
		mButton.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL));
		mButton.setEnabled(false);
		mVerticalDivider.setVisibility(View.GONE);
		mTunerSelector.setVisibility(View.GONE);
		
		mWaitingAnimation.setVisibility(View.VISIBLE);
		mInfoTxtVw.setVisibility(View.VISIBLE);
		mInfoTxtVw.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTALLING_PACKAGE));		
		mVerticalText.setTextColor(getResources().getColor(org.droidtv.ui.tvwidget2k15.R.color.npanelbrowser_textcolor_activated));
		mVerticalText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_SAT_INSTALLING));
		(NotificationHandler.getInstance()).registerForNotification(this);
		Log.d(TAG, "starting cam");
		
		lnbInfo = new LNBInfo();
		
		//nwrap.initTVMediaPlayer(NativeAPIWrapper.TunerName.TUNER1);
		nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
		
		// cache used for finish screen
		(InstalledLNBCache.getInstance()).emptyCache();

		Log.d(TAG, "screenIntialization Exit");
	}

	private void navigateToTunerSelectionScreen(){
		Log.d(TAG, "navigateToTunerSelectionScreen");
		currentScreenMode = ScreenMode.TUNER_SELECTION;
		
		((Activity) mContext).runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mTvChannelAdded.setVisibility(View.GONE);
				mRadioChannelAdded.setVisibility(View.GONE);
				mPackageName.setVisibility(View.GONE);
				mWaitingAnimation.setVisibility(View.GONE);
				mInfoTxtVw.setVisibility(View.GONE);
				
				mScreenHeaderProgessBar.setProgress(50);
				mStatusText.setVisibility(View.VISIBLE);
				mStatusText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_DUAL_TUNER));	
				mVerticalText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_SAT_AUTOSTORE_DUAL_TUNER));
				mButton.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT));
				mButton.setEnabled(true);
				mVerticalDivider.setVisibility(View.VISIBLE);
				
				
				String[] dualTunerArray = {
						 mContext.getString(org.droidtv.ui.strings.R.string.MAIN_ONE_TUNER),
						 mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TWO_TUNERS) };
				mTunerSelector.setArray(dualTunerArray);
				
				// default selection should always be on tuner 1
				mTunerSelector.setItemChecked(0, true);
				mTunerSelector.setVisibility(View.VISIBLE);
				
				mTunerSelector.setOnItemClickListener(new OnItemClickListener() {
		
					@Override
					public void onItemClick(AdapterView<?> arg0, View view,
							int selectedItem, long arg3) {
						Log.d(TAG, "selectedItem:" + selectedItem);
						mButton.setEnabled(true);
						mButton.requestFocus();
					}
		
				});
				mTunerSelector.requestFocus();
			}
		});
	}
	
	private void navigateToFinishScreen() {
		Log.d(TAG, "Launching finish screen");
		currentScreenMode = ScreenMode.FINISH;
		((Activity) mContext).runOnUiThread(new Runnable() {
			@Override
			public void run() {
				unRegisterFromNotifications();
				mTunerSelector.setVisibility(View.GONE);
				mScreenHeaderProgessBar.setProgress(100);
				mInfoTxtVw.setVisibility(View.GONE);
				mWaitingAnimation.setVisibility(View.GONE);
				mVerticalDivider.setVisibility(View.VISIBLE);
				mTvTitle.setVisibility(View.VISIBLE);
				mRadioTitle.setVisibility(View.VISIBLE);
				
				mTvChannelAdded.setText(Integer.toString(lnbInfo.m_tvChannelsAdded));
				mTvChannelAdded.setVisibility(View.VISIBLE);
				mRadioChannelAdded.setText(Integer.toString(lnbInfo.m_radioChannelsAdded));
				mRadioChannelAdded.setVisibility(View.VISIBLE);
				mPackageName.setText(lnbInfo.m_name);
				mPackageName.setVisibility(View.VISIBLE);
				
				mButton.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE));
				mVerticalText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_UPDATE_FINISHED));
				mStatusText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_SAT_AUTOSTORE_FINISHED));
				mStatusText.setVisibility(View.VISIBLE);
				mButton.setEnabled(true);
				
			}
		});
	}

	@Override
	public void update(Observable observable, Object data) {
		Log.d(TAG, "update entry");
		final int eventID = ((NotificationInfoObject) data).actionID;

		switch (eventID) {
		case EventIDs.PACKAGE_INSTALL_STARTED:
			Log.d(TAG, "PACKAGE_INSTALL_STARTED");
			// control is with the cam disable cancel as cancel has to be
			// triggered via mmi
			((Activity) mContext).runOnUiThread(new Runnable() {
				@Override
				public void run() {
					mButton.setEnabled(false);
				}
			});
			break;

		case EventIDs.PACKAGE_INSTALL_FINISHED:
			Log.d(TAG, "PACKAGE_INSTALL_FINISHED");
			lnbInfo.m_tvChannelsAdded = nwrap.GetTvServices(true, 0);
			lnbInfo.m_radioChannelsAdded = nwrap.GetRadioServices(true, 0);
			(InstalledLNBCache.getInstance()).addItem(lnbInfo);
			break;

		case EventIDs.SERVICE_SCAN_COMPLETE:
			Log.d(TAG, "SERVICE_SCAN_COMPLETE");
					
			nwrap.commitToTVSettings(); // To set package
			nwrap.setMMIEnabled(false); // Disable the mmi
			nwrap.saveSatelliteSettingsToPersistent();
			nwrap.commitSatelliteSettingsToPersistent();
			nwrap.commitDatabaseToTvProvider(NativeAPIWrapper.INSTALL_TYPE_AUTO);	
			nwrap.getSatInstaller(TunerName.TUNER1).storecicamdata();
			nwrap.camprofileInstallationCompleted();
			break;

		case EventIDs.NATIVELAYER_INIT_DONE:
			Log.d(TAG, "NATIVELAYER_INIT_DONE ");

			nwrap.getSatInstaller(TunerName.TUNER1).registerCIListener();
			
			mCIPlusUI = new CIPlusUI(mContext);

			// set the package ID to
			nwrap.SetPackageIDDirectly(MwDataTypes.OPERATOR_PROFILE_PACKAGE_ID);

			// set package only installation
			nwrap.SetSelectedPackage(true);

			// start installation
			if(nwrap.iscamnitbasedinstallation())
			{
				nwrap.SetScanStarts(MwDataTypes.IHsvSatelliteInstallation_InstallationCamNit, MwDataTypes.InsEnumServiceScan);
			}
			else
			{
				nwrap.SetScanStarts(MwDataTypes.IHsvSatelliteInstallation_InstallationServiceScan, MwDataTypes.InsEnumServiceScan);
			}
			break;
		case EventIDs.COMMIT_TVPROVIDER_FINISHED:
			Log.d(TAG, "COMMIT_TVPROVIDER_FINISHED");
			nwrap.TriggerOperatorStatusReq();
			break;

		case EventIDs.EVENT_INST_COMPLETED:
			Log.d(TAG, "EVENT_INST_COMPLETED");
			nwrap.camprofileInstallationCompleted();
			break;
			
		case EventIDs.TRIGGER_OP_INSTALL_COMPLETE:
			Log.d(TAG, "TRIGGER_OP_INSTALL_COMPLETE");
			lnbInfo.m_name = nwrap.getSatInstaller(TunerName.TUNER1).getOperatorProfilePackageName();
			startLogoAssociation();
			Log.d(TAG, "Logo association triggered");
			unregisterForNotification();
			if(nwrap.isTwoTunerSupported()){
				navigateToTunerSelectionScreen();
			}else{
				navigateToFinishScreen();
			}
			
			break;

		case EventIDs.EVENT_INS_STOPPED:
			Log.d(TAG, "EVENT_INS_STOPPED");
			lnbInfo.m_tvChannelsAdded = nwrap.GetTvServices(true, 0);
			lnbInfo.m_radioChannelsAdded = nwrap.GetRadioServices(true, 0);
			lnbInfo.m_name = nwrap.getSatInstaller(TunerName.TUNER1).getOperatorProfilePackageName();
			navigateToFinishScreen();
			break;


		}
	}

	private void unregisterForNotification() {
		NotificationHandler.getInstance().unRegisterForNotification(this);
	}

	private void startLogoAssociation() {
		Log.d(TAG, "startLogoAssociation");
		Intent i = new Intent("org.droidtv.tvcontentprovider.LogoService");
		((Activity) mContext).bindService(i, mConnection, Context.BIND_AUTO_CREATE);
	}

	private ServiceConnection mConnection = new ServiceConnection() {
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG, "ILogoAssociationControl called");

			logoAssoInt = ILogoAssociationControl.Instance.asInterface(service);
			if (logoAssoInt != null) {
				Log.d(TAG, "logoAssoInt is not null");
				logoAssoInt.registerListenerCallback(listener);
				logoAssoInt.StartLogoAssociation(ILogoAssociationControl.MEDIUM_SATELLITE);
			} else {
				Log.d(TAG, "NULL logoAssoInt found");
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			// TODO Auto-generated method
			// stub
		}
	};

	public class ListenerImpl extends ILogoAssociationListener {

		@Override
		public void onLogoAssociationStateChanged(int state) {
			Log.d(TAG, "onLogoAssociationStateChanged called with State:" + state);

			if (state == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_COMPLETE) {
				Log.d(TAG, "Logo Association complete received");

				// Navigating to next screen
				try {
					((Activity) mContext).unbindService(mConnection);
				} catch (Exception ex) {
					Log.d(TAG, "Exception caught while unbinding service org.droidtv.tvcontentprovider.LogoService");
				}
			}
		}
	}

	private void unRegisterFromNotifications() {
		Log.i(TAG, "unRegisterFromNotifications called");
		// register this class for notifications
		(NotificationHandler.getInstance()).unRegisterForNotification(this);
	}

	@Override
	protected void onDestroy() {
		Log.d(TAG,"onDestroy");
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
		/*nwrap.setApplicationState(NativeAPIWrapper.STATE_IDLE);
		nwrap.getSatInstaller(TunerName.TUNER1).unRegisterCIListener();
		sendIntentOnExit();*/
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		Log.d(TAG, "onStart");
		sendIntentOnEntry();
	}
	
	private void sendIntentOnEntry() {
		Log.d(TAG, "Wizard entry : sending intents on separate thread");
		nwrap.enterNonInteruptableMode();
	}

}
