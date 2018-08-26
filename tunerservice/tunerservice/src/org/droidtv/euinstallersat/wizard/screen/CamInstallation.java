package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.ci.CIPlusUI;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.InstalledLNBCache;
import org.droidtv.euinstallersat.wizard.util.LNBInfo;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.tvinput.ILogoAssociationControl.ILogoAssociationListener;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

public class CamInstallation extends WizardStep implements SatelliteScreen {

	private static final String TAG = CamInstallation.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper nwrap;
	private TextView m_startInfoTxtVw;
	private CIPlusUI mCIPlusUI;
	private LNBInfo lnbInfo;
	private ILogoAssociationControl logoAssoInt = null;
	private ListenerImpl listener = new ListenerImpl();

	public CamInstallation(Context context, AttributeSet attrSet, int defStyle) {
		super(context, attrSet, defStyle);
		mContext = context;
		nwrap = NativeAPIWrapper.getInstance();
		layout(context);
	}

	public CamInstallation(Context context, AttributeSet attrSet) {
		this(context, attrSet, 0);
	}

	public CamInstallation(Context context) {
		this(context, null, 0);
	}

	private void layout(Context context) {
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(R.layout.caminstallation, null);
		m_startInfoTxtVw = (TextView) view.findViewById(R.id.textBody);
		m_startInfoTxtVw.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTALLING_PACKAGE));
		addView(view);

		OnClickListener buttonCancel_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				Log.i(TAG, "pressed on cancel");
				unregisterForNotification();
				
				nwrap.getSatInstaller(TunerName.TUNER1).unRegisterCIListener();
				nwrap.setMMIEnabled(false); //Disable the mmi
				nwrap.cancelInstallation();
				mSatelliteWizard.launchPreviousScren();
			}
		};

		setButton1(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), buttonCancel_Listener, View.VISIBLE);
		setButton2(null, null, View.INVISIBLE);
		setButton3(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT), null, View.VISIBLE);

		setButton3Enabled(false);

		hideHint();
	}

	private void unregisterForNotification() {
		NotificationHandler.getInstance().unRegisterForNotification(this);
	}

	@Override
	public void update(Observable observable, Object data) {
		Log.d(TAG, "update entry");

		final int eventID = ((NotificationInfoObject) data).actionID;

		switch (eventID) {
		
		case EventIDs.PACKAGE_INSTALL_STARTED:
			Log.d(TAG, "PACKAGE_INSTALL_STARTED");
			lnbInfo = new LNBInfo();
			// control is with the cam disable cancel as cancel has to be triggered via mmi
			break;

		case EventIDs.PACKAGE_INSTALL_FINISHED:
			Log.d(TAG, "PACKAGE_INSTALL_FINISHED");
			lnbInfo.m_tvChannelsAdded = nwrap.GetTvServices(true, 0);
			lnbInfo.m_radioChannelsAdded = nwrap.GetRadioServices(true, 0);
			lnbInfo.m_name = nwrap.getSatInstaller(TunerName.TUNER1).getOperatorProfilePackageName();
			InstalledLNBCache.getInstance().addItem(lnbInfo);
			
			((Activity) mContext).runOnUiThread(new Runnable() {
				@Override
				public void run() {
					setButton1Enabled(false);
				}
			});
			
			break;

		case EventIDs.SERVICE_SCAN_COMPLETE:
			Log.d(TAG, "SERVICE_SCAN_COMPLETE");
						
			nwrap.commitToTVSettings(); // To set package
			nwrap.setMMIEnabled(false); //Disable the mmi
			nwrap.saveSatelliteSettingsToPersistent();
			nwrap.commitSatelliteSettingsToPersistent();
			nwrap.commitDatabaseToTvProvider(NativeAPIWrapper.INSTALL_TYPE_AUTO);
			break;
			
		case EventIDs.COMMIT_TVPROVIDER_FINISHED:
			Log.d(TAG, "COMMIT_TVPROVIDER_FINISHED");
			nwrap.TriggerOperatorStatusReq();
			break;
		case EventIDs.EVENT_INS_STOPPED:
			Log.d(TAG, "EVENT_INS_STOPPED");
			unregisterForNotification();
			nwrap.getSatInstaller(TunerName.TUNER1).unRegisterCIListener();
			nwrap.setMMIEnabled(false); //Disable the mmi
			nwrap.cancelInstallation();
			//mSatelliteWizard.launchPreviousScren();
			lnbInfo.m_tvChannelsAdded = nwrap.GetTvServices(true, 0);
			lnbInfo.m_radioChannelsAdded = nwrap.GetRadioServices(true, 0);
			lnbInfo.m_name = nwrap.getSatInstaller(TunerName.TUNER1).getOperatorProfilePackageName();
			unregisterForNotification();
			navigateToFinishScreen();

			break;
		case EventIDs.TRIGGER_OP_INSTALL_COMPLETE:
			Log.d(TAG, "TRIGGER_OP_INSTALL_COMPLETE");
			startLogoAssociation();
			Log.d(TAG, "Logo association triggered");
			unregisterForNotification();
			navigateToFinishScreen();
			break;
		}
	}

	private void navigateToFinishScreen() {
//		nwrap.getSatInstaller(TunerName.TUNER1).unRegisterCIListener();
		Log.d(TAG, "Launching finish screen");
		((Activity) mContext).runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mSatelliteWizard.launchScreen(ScreenRequest.FINISHSCREEN, getScreenName());
			}
		});
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
				logoAssoInt.StartLogoAssociation(ILogoAssociationControl.MEDIUM_SATELLITE);
			} else {
				Log.d(TAG, "NULL logoAssoInt found");
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
		}
	};

	public class ListenerImpl extends ILogoAssociationListener {

		@Override
		public void onLogoAssociationStateChanged(int state) {
			Log.d(TAG, "onLogoAssociationStateChanged called with State:" + state);

			if (state == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_COMPLETE) {
				Log.d(TAG, "Logo Association complete received");

				try {
					((Activity) mContext).unbindService(mConnection);
				} catch (Exception ex) {
					Log.d(TAG, "Exception caught while unbinding service org.droidtv.tvcontentprovider.LogoService");
				}
			}
		}
	}

	@Override
	public void setInstance(SatelliteWizard wizard) {
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName() {
		return ScreenRequest.CAM_INSTALLATION;
	}

	@Override
	public void screenIntialization() {
		Log.d(TAG, "screenIntialization");
		(NotificationHandler.getInstance()).registerForNotification(this);
		nwrap.getSatInstaller(TunerName.TUNER1).registerCIListener();
		
		setButton3focussed();
		
		// cache used for finish screen
		(InstalledLNBCache.getInstance()).emptyCache();

		mCIPlusUI = new CIPlusUI(mContext);
 
		// set the package ID to
		nwrap.SetPackageIDDirectly(MwDataTypes.OPERATOR_PROFILE_PACKAGE_ID);
		
		// set package only installation
		nwrap.SetSelectedPackage(true);

		// start installation
		nwrap.SetScanStarts(MwDataTypes.IHsvSatelliteInstallation_InstallationServiceScan, MwDataTypes.InsEnumServiceScan);
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {

		boolean ret = super.dispatchKeyEvent(event);
		int keyCode = event.getKeyCode();
		switch (keyCode) {
		case KeyEvent.KEYCODE_DPAD_RIGHT:
		case KeyEvent.KEYCODE_DPAD_LEFT:
		case KeyEvent.KEYCODE_BACK:
		case KeyEvent.KEYCODE_ESCAPE:
			// consume
			ret = true;
			break;
		}
		return ret;
	}

	@Override
	public void screenExit() {
		Log.d(TAG, "screenExit");

	}
}
