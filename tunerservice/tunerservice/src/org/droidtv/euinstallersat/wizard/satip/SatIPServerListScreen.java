package org.droidtv.euinstallersat.wizard.satip;

import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.TextView;

public class SatIPServerListScreen extends WizardStep implements
		SatelliteScreen {

	private static final String TAG = SatIPServerListScreen.class.getName();
	private Context mContext;
	private RadioSelector mRadioSelector;
	private TextView mTextContent;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper nwrap;
	private SatIPWrapper swrap;
	private NotificationHandler ntf;
	private SatIPServerListScreen thisClassInst;
	private TimerTask localProgTimerTask = null;
	private Timer localProgTimer = null;

	public SatIPServerListScreen(Context context, AttributeSet attrSet,
			int defStyle) {
		super(context, attrSet, defStyle);
		mContext = context;
		thisClassInst = this;
		nwrap = NativeAPIWrapper.getInstance();
		swrap = SatIPWrapper.getInstance();
		ntf = NotificationHandler.getInstance();
		loadLayout(context);
	}

	public SatIPServerListScreen(Context context, AttributeSet attrSet) {
		this(context, attrSet, 0);
	}

	public SatIPServerListScreen(Context context) {
		this(context, null, 0);
	}

	private void loadLayout(Context context) {
		LayoutInflater inflater = (LayoutInflater) context
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(R.layout.satipserverlist, null);
		addView(view);
		mRadioSelector = (RadioSelector) view.findViewById(R.id.radioList);
		mTextContent = (TextView) view.findViewById(R.id.bodyText);
		mTextContent.setText(org.droidtv.tunerservice.R.string.MAIN_WI_SAT_IP_NO_SERVERS_FOUND);
		mRadioSelector.setOnKeyListener(this);

		OnClickListener buttonCancel_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				ntf.unRegisterForNotification(thisClassInst);
				stopSearch();
				mSatelliteWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonRetry_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				startSearch();
			}
		};

		OnClickListener buttonDone_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				swrap.setUserSelectedServer(mRadioSelector
						.getCheckedItemPosition());
				ntf.unRegisterForNotification(thisClassInst);
				stopSearch();
				mSatelliteWizard.launchPreviousScren();
			}
		};

		mRadioSelector.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View view,
					int selectedItem, long arg3) {
				Log.d(TAG, "selectedItem:" + selectedItem);
				setButton3focussed();
			}

		});

		setButton1(
				mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL),
				buttonCancel_Listener, VISIBLE);
		setButton2(
				mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH_AGAIN),
				buttonRetry_Listener, VISIBLE);
		setButton3(
				mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE),
				buttonDone_Listener, VISIBLE);

		// setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_SAT));
	}

	@Override
	public boolean onKey(View view, int keyCode, KeyEvent event) {

		Log.d(TAG, "OnKey");
		boolean handleKey = false;
		if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT
				&& event.getAction() == KeyEvent.ACTION_DOWN) {
			Log.d(TAG, "KEYCODE_DPAD_RIGHT");
			if (mRadioSelector == view) {
				setButton3focussed();
			} else {
				super.onKey(view, keyCode, event);
			}
			handleKey = true;
		} else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT
				&& event.getAction() == KeyEvent.ACTION_DOWN) {
			Log.d(TAG, "KEYCODE_DPAD_LEFT");
			if (mRadioSelector == view) {
				setButton1focussed();
			} else {
				super.onKey(view, keyCode, event);
			}
			handleKey = true;
		} else if (keyCode == KeyEvent.KEYCODE_DPAD_UP
				&& event.getAction() == KeyEvent.ACTION_DOWN) {
			Log.d(TAG, "KEYCODE_DPAD_UP");
			if (mRadioSelector != view) {
				int l_selIdx = mRadioSelector.getCheckedItemPosition();
				mRadioSelector.setSelection(l_selIdx);
				mRadioSelector.requestFocus();
			}
		}
		Log.d(TAG, "OnKey returning " + handleKey);
		return handleKey;

	}

	@Override
	public void update(Observable observable, Object data) {
		final int eventID = ((NotificationInfoObject) data).actionID;
		switch (eventID) {
		case EventIDs.SATIP_SERV_SEARCH_COMPLETE:
			Log.d(TAG, "SATIP_SERV_SEARCH_COMPLETE");
			final int serverItemCount = swrap.getSatIPServerList().size();
			((SatelliteInstallationActivity) mContext)
					.runOnUiThread(new Runnable() {
						@Override
						public void run() {
							enableWaitingAnimation(false);
							setButton2Enabled(true);

							if (serverItemCount > 0) {
								mTextContent.setVisibility(INVISIBLE);
								mRadioSelector.setVisibility(VISIBLE);
								setButton3Enabled(true);
								setfocusOnTheRadioList();
							} else {
								mRadioSelector.setVisibility(INVISIBLE);
								mTextContent.setVisibility(VISIBLE);
							}
						}
					});

			break;
		}
	}

	@Override
	public void setInstance(SatelliteWizard wizard) {
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName() {
		return ScreenRequest.SATIP_SERVERLIST;
	}

	private void startSearch() {
		Log.d(TAG, "startSearch ");
		swrap.startSatIPSearch();

		if (localProgTimerTask != null) {
			localProgTimerTask.cancel();
			localProgTimerTask = null;
		}

		if (localProgTimer != null) {
			localProgTimer.cancel();
			localProgTimer = null;
		}

		((SatelliteInstallationActivity) mContext)
				.runOnUiThread(new Runnable() {
					@Override
					public void run() {
						enableWaitingAnimation(true);
						setButton2Enabled(false);
						setButton3Enabled(false);
					}
				});

		localProgTimerTask = new TimerTask() {
			@Override
			public void run() {
				 ntf.notifyAllObservers(EventIDs.SATIP_SERV_SEARCH_COMPLETE, "");
			}
		};

		localProgTimer = new Timer();
		localProgTimer.schedule(localProgTimerTask, 5000);
	}

	private void stopSearch() {
		Log.d(TAG, "stopSearch ");
		if (localProgTimerTask != null) {
			localProgTimerTask.cancel();
		}

		if (localProgTimer != null) {
			localProgTimer.cancel();
		}
	}

	private void setfocusOnTheRadioList() {
		Log.d(TAG, "setfocusOnTheRadioList " + mRadioSelector.getCount());

		mRadioSelector.setArray(swrap.getSatIPServerNameList());
		int setLocalServerID = swrap.getUserSelectedServer();
		mRadioSelector.smoothScrollToPosition(setLocalServerID);
		mRadioSelector.requestFocusFromTouch();
		mRadioSelector.requestFocus();
		mRadioSelector.setSelection(setLocalServerID);
		mRadioSelector.setItemChecked(setLocalServerID, true);
	}

	@Override
	public void screenIntialization() {
		Log.d(TAG, "screenIntialization");
		
		ntf.registerForNotification(thisClassInst);
		if (swrap.getSatIPServerList().size() > 0) {
			enableWaitingAnimation(false);
			mTextContent.setVisibility(INVISIBLE); 
			mRadioSelector.setVisibility(VISIBLE);
			setfocusOnTheRadioList();
		} else {
			mRadioSelector.setVisibility(INVISIBLE);
			mTextContent.setVisibility(INVISIBLE);
			startSearch();
		}
	}

	@Override
	public void screenExit() {
		Log.d(TAG, "screenExit");

	}
}
