package org.droidtv.euinstallersat.wizard.satip;

import java.util.ArrayList;
import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.tvnotification.TvNotificationManager;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.euinstallersat.common.InstallerActivityManager;
import android.content.Context;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ListView;


public class SatIPHubScreen extends WizardStep implements SatelliteScreen {

	private static final String TAG = SatIPHubScreen.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper nwrap;
	private SatIPWrapper swrap;
	private ListView hubListView;
	private SatIPHubAdapter satIPHubAdapter;
	private NotificationHandler ntf;
	private SatIPHubScreen thisClassInst;
	
	private ArrayList<ModalDialog>  mModalDialogList;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	enum HUBITEMS {
		CONNECT_TO_NETWORK, CONNECT_TO_SATIP_SERVER, SEARCH_FOR_SATELLITE, INSTALL_SATELLITE
	}

	public SatIPHubScreen(Context context, AttributeSet attrSet, int defStyle) {
		super(context, attrSet, defStyle);
		mContext = context;
		thisClassInst = this;
		nwrap = NativeAPIWrapper.getInstance();
		swrap = SatIPWrapper.getInstance();
		ntf = NotificationHandler.getInstance();
		layout(context);
	}

	public SatIPHubScreen(Context context, AttributeSet attrSet) {
		this(context, attrSet, 0);
	}

	public SatIPHubScreen(Context context) {
		this(context, null, 0);
	}

	private void layout(Context context) {
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

		View view = inflater.inflate(R.layout.satiphub, null);
		addView(view);

		hubListView = (ListView) view.findViewById(R.id.satIPHubListID);
		hubListView.setSelector(org.droidtv.ui.tvwidget2k15.R.drawable.listviewselector);

		OnClickListener buttonPrevious_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				Log.d(TAG, "ok on previous");
				mSatelliteWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonFinish_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				Log.d(TAG, "ok on finish");
				unregisterForNotification();
				
				instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
				/*nwrap.tuneOnFinish();
				((Activity)mContext).setResult(SatelliteConstants.RESULT_CODE_CLOSE_SETTINGS_ACTIVITY);
				((Activity)mContext).finish();*/
				
			}
		};

		OnClickListener buttonCancel_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				Log.d(TAG, "ok on cancel");
				unregisterForNotification();
			}
		};

		hubListView.setOnItemSelectedListener(new OnItemSelectedListener() {

			@Override
			public void onItemSelected(AdapterView<?> arg0, View arg1, int selectedIndex, long arg3) {
				setHintText(satIPHubAdapter.getItemList().get(selectedIndex).hintText);
			}

			@Override
			public void onNothingSelected(AdapterView<?> arg0) {
				// TODO Auto-generated method stub
			}
		});

		hubListView.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int selectedIndex, long arg3) {
				Log.d(TAG, "onItemClick " + selectedIndex);
				if (selectedIndex == HUBITEMS.CONNECT_TO_NETWORK.ordinal()) {
					Intent intent = new Intent("android.settings.WIRELESS_SETTINGS");
					mContext.sendBroadcast(intent);
				} else if (selectedIndex == HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal()) {
					// check if network is connected
					if (satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).isCompleted == true) {
						// launch SatIP server list screen
						ntf.unRegisterForNotification(thisClassInst);
						mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.SATIP_SERVERLIST, getScreenName());
					}else{
						
					}
				} else if (selectedIndex == HUBITEMS.SEARCH_FOR_SATELLITE.ordinal()) {
					// check if network is connected and satIP server detected
					if (satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).isCompleted == true
							&& satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal()).isCompleted == true) {
						// launch prescan screen
						ntf.unRegisterForNotification(thisClassInst);
						mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.SATIP_PRESCAN, getScreenName());
					}else{
						TvNotificationManager.postTvNotification(mContext,TvNotificationManager.FLAG_NO_IMAGE,
								mContext.getString(org.droidtv.tunerservice.R.string.MAIN_MSG_SAT_IP_PRESCAN_NOT_POSSIBLE), 
								TvNotificationManager.FLAG_TIMED_NOTIFICATION);
					}
				} else if (selectedIndex == HUBITEMS.INSTALL_SATELLITE.ordinal()) {
					
					if (satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).isCompleted == true
							&& satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal()).isCompleted == true
							&& satIPHubAdapter.getItemList().get(HUBITEMS.SEARCH_FOR_SATELLITE.ordinal()).isCompleted == true) {
						// launch package selection screen
						ntf.unRegisterForNotification(thisClassInst);
						mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.PACKAGE_SELECTION, getScreenName());
					}else{
						TvNotificationManager.postTvNotification(mContext,TvNotificationManager.FLAG_NO_IMAGE, 
								mContext.getString(org.droidtv.tunerservice.R.string.MAIN_MSG_SAT_IP_INSTALLATION_NOT_POSSIBLE), 
								TvNotificationManager.FLAG_TIMED_NOTIFICATION);
					}
				}
			}
		});

		setButton1(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), buttonCancel_Listener, View.VISIBLE);
		setButton2(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener, View.VISIBLE);
		setButton3(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE), buttonFinish_Listener, View.VISIBLE);
	}

	private void unregisterForNotification() {
		NotificationHandler.getInstance().unRegisterForNotification(this);
	}

	@Override
	public void update(Observable observable, Object data) {
		final int eventID = ((NotificationInfoObject) data).actionID;
		switch (eventID) {
		case EventIDs.WIZARD_SETTINGS_EXIT:
			Log.d(TAG, "WIZARD_SETTINGS_EXIT");
			// setButton3focussed();
			break;
		case EventIDs.SATIP_NETWK_CONN_CHANGE:
			Log.d(TAG, "SATIP_NEWTWK_CONN_UNAVAILABLE");
			refreshHubItemList();
			break;
		}
	}

	public void refreshHubItemList() {
		((SatelliteInstallationActivity) mContext).runOnUiThread(new Runnable() {
			@Override
			public void run() {

				boolean ifNetworkAvail = nwrap.ifNetworkAvailable();
				boolean ifSatIPServerAvail = false;
				boolean ifSatelliteAfterPrescan = false;
				boolean ifSatIPInstallationDone = false;
				// refresh network connectivity
				if(ifNetworkAvail){
					satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).isCompleted = true;
					satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).displaySubText = nwrap.getNetworkName();
				}else{
					satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).isCompleted = false;
					satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).displaySubText = "";
				}

				// refresh satip server list
				if (ifNetworkAvail && swrap.getSatIPServerList().size() > 0) {
					satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal()).isCompleted = true;
					satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal()).displaySubText = swrap.getSatIPServerNameList()[swrap.getUserSelectedServer()];
					ifSatIPServerAvail = true;
				} else {
					satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal()).isCompleted = false;
					satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal()).displaySubText = "";
					ifSatIPServerAvail = false;
				}

				// search for satellite
				ifSatelliteAfterPrescan = swrap.ifSatIPSatelliteAfterPrescan();
				if (ifNetworkAvail && ifSatIPServerAvail && ifSatelliteAfterPrescan) {
					satIPHubAdapter.getItemList().get(HUBITEMS.SEARCH_FOR_SATELLITE.ordinal()).isCompleted = true;
					// display satellite name
					satIPHubAdapter.getItemList().get(HUBITEMS.SEARCH_FOR_SATELLITE.ordinal()).displaySubText = swrap.getSatIPSatelliteName();
				} else {
					satIPHubAdapter.getItemList().get(HUBITEMS.SEARCH_FOR_SATELLITE.ordinal()).isCompleted = false;
					satIPHubAdapter.getItemList().get(HUBITEMS.SEARCH_FOR_SATELLITE.ordinal()).displaySubText = "";
				}

				// install satellite
				ifSatIPInstallationDone = swrap.ifSatIPInstallationDone();
				if (ifNetworkAvail && ifSatIPServerAvail && ifSatelliteAfterPrescan && ifSatIPInstallationDone) {
					satIPHubAdapter.getItemList().get(HUBITEMS.INSTALL_SATELLITE.ordinal()).isCompleted = true;
					// display channel number 
				}else {
					satIPHubAdapter.getItemList().get(HUBITEMS.INSTALL_SATELLITE.ordinal()).isCompleted = false;
					satIPHubAdapter.getItemList().get(HUBITEMS.INSTALL_SATELLITE.ordinal()).displaySubText = "";
				}
				
				// trigger list refresh
				satIPHubAdapter.notifyDataSetChanged();

				// finish button
				if (satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).isCompleted && 
						satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal()).isCompleted
						&& satIPHubAdapter.getItemList().get(HUBITEMS.INSTALL_SATELLITE.ordinal()).isCompleted
						&& satIPHubAdapter.getItemList().get(HUBITEMS.SEARCH_FOR_SATELLITE.ordinal()).isCompleted) {
					Log.d(TAG, "all steps complete");
					setButton3Enabled(true);
				} else {
					setButton3Enabled(false);
				}
			}
		});

	}

	public void launchNetworkDialog() {
		Log.d(TAG, "launchNetworkDialog");
		
		mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_SAT_IP_NETWORK_CABLE), "");
    	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_SAT_IP_NETWORK_CABLE));
    	
    	ModalDialogFooterButtonProp mCloseButton = mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CLOSE),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_NOW clicked ");
    					mModalDialog.hide();
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialogList.add(mModalDialog);
    	mModalDialog.setCancelable(false);
    	mModalDialog.show();
    	mCloseButton.requestFocus();
	}

	@Override
	public void setInstance(SatelliteWizard wizard) {
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName() {
		return ScreenRequest.SATIP_HUBSCREEN;
	}

	@Override
	public void screenIntialization() {
		Log.d(TAG, "screenIntialization");
		ntf.registerForNotification(this);

		mModalDialogList = new ArrayList<ModalDialog>();
		mModalDialogList.clear();
		populateRadioList();
		refreshHubItemList();

		// after list is populated check the status of the list items and take
		// action
		/*if ((satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).isExecutedOnce == false)
				&& (satIPHubAdapter.getItemList().get(HUBITEMS.CONNECT_TO_NETWORK.ordinal()).isCompleted == false)) {

			ntf.notifyAllObservers(EventIDs.SATIP_NETWK_CONN_CHANGE, "");
			launchNetworkDialog();
		}*/
	}

	private void setFocusOnItem() {
		int index = 0;

		for (index = 0; index < 4; index++) {
			if (satIPHubAdapter.getItemList().get(index).isCompleted == false) {
				break;
			}
		}
		switch (index) {
		case 0:
		case 1:
		case 2:
		case 3:
			hubListView.requestFocus();
			hubListView.setSelection(index);
			break;
		default:
			setButton3focussed();
			break;
		}
	}

	private void populateRadioList() {
		satIPHubAdapter = new SatIPHubAdapter(mContext);
		ArrayList<SatIPHubItemInfo> listData = new ArrayList<SatIPHubItemInfo>();

		listData.add(new SatIPHubItemInfo(HUBITEMS.CONNECT_TO_NETWORK.ordinal(), getContext().getString(org.droidtv.ui.strings.R.string.MAIN_SAT_IP_AUTOSTORE_CONNECT_TO_NETWORK), getContext().getString(
				R.string.MAIN_WI_SAT_IP_AUTOSTORE_CONNECT_TO_NETWORK),"" ,nwrap.ifNetworkAvailable(), false));

		listData.add(new SatIPHubItemInfo(HUBITEMS.CONNECT_TO_SATIP_SERVER.ordinal(), getContext().getString(org.droidtv.tunerservice.R.string.MAIN_SAT_IP_AUTOSTORE_CONNECT_TO_SERVER), getContext().getString(
				R.string.MAIN_WI_SAT_IP_AUTOSTORE_CONNECT_TO_SERVER),"", false, false));

		listData.add(new SatIPHubItemInfo(HUBITEMS.SEARCH_FOR_SATELLITE.ordinal(), getContext().getString(org.droidtv.ui.strings.R.string.MAIN_SAT_IP_AUTOSTORE_SEARCH_FOR_SATELLITE), getContext().getString(
				R.string.MAIN_WI_SAT_IP_AUTOSTORE_SEARCH_FOR_SATELLITE),"", false, false));

		listData.add(new SatIPHubItemInfo(HUBITEMS.INSTALL_SATELLITE.ordinal(), getContext().getString(org.droidtv.ui.strings.R.string.MAIN_SAT_IP_AUTOSTORE_INSTALL), getContext().getString(
				R.string.MAIN_WI_SAT_IP_AUTOSTORE_INSTALL),"", false, false));

		satIPHubAdapter.setItemList(listData);
		hubListView.setAdapter(satIPHubAdapter);

		setFocusOnItem();

		setHintText(satIPHubAdapter.getItemList().get(0).hintText);
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {

		boolean ret = super.dispatchKeyEvent(event);
		int keyCode = event.getKeyCode();
		switch (keyCode) {
		case KeyEvent.KEYCODE_DPAD_RIGHT:
			ret = true;
			break;
		case KeyEvent.KEYCODE_DPAD_LEFT:
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
