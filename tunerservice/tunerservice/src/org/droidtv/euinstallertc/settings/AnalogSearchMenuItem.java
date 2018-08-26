package org.droidtv.euinstallertc.settings;

import java.util.Observable;
import java.util.Observer;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.InstallationMode;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.euinstallertc.util.IViewListener;
import org.droidtv.euinstallertc.util.RalativeLayoutView;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueChangeListener;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueConfirmation;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueEntered;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.helpers.ResourceHelper;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.drawable.BitmapDrawable;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.PopupWindow;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;

public class AnalogSearchMenuItem extends MenuItem implements OnClickListener, IViewListener, IInputPickerValueChangeListener, IInputPickerValueEntered,
		IInputPickerValueConfirmation, Observer {

	private static final String TAG = AnalogSearchMenuItem.class.getName();
	protected Context mContext;
	private RalativeLayoutView analogSearchView;
	private LayoutInflater mInflater;
	private FrameLayout mFrameLayoutContainer;
	public boolean m_isCollapsed = false;
	private Button m_buttonSearch;
	private Button m_buttonDone;
	private Timer m_timer;
	private int m_minFreq;
	private int m_maxFreq;
	boolean m_isSearchInProgress = false;
	private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();;
	private PopupWindow m_progressWindow;
	private ManualInstallState currentState = ManualInstallState.START_INSTALLATION;
	private SearchButtonState searchButtonState = SearchButtonState.SEARCH;
	private InputPicker leftPicker;
	private int NUM_PICKER = 3;

	private enum ManualInstallState {
		START_INSTALLATION, INSTALLATION_IN_PROGRESS
	}

	private enum SearchButtonState {
		SEARCH, CANCEL
	}

	@Override
	public View getView(Context ctx) {
		Log.d(TAG, "getView: " + mFrameLayoutContainer);

		if (mFrameLayoutContainer != null) {
			return mFrameLayoutContainer;
		} else {
			return super.getView(ctx);
		}
	}

	@Override
	public void setFocus(Boolean focus) {
		Log.d(TAG, "setFocus " + focus);
		// super.setFocus(focus);
		mFrameLayoutContainer.removeAllViews();
		if (focus) {
			if(m_wrapper.getSettingsActivity() instanceof ChannelSettingsActivity){
				((ChannelSettingsActivity) m_wrapper.getSettingsActivity()).showHideColorKey(false);
			}
			mFrameLayoutContainer.addView(loadView(), 0);
			screenInitialization();
		}
	}

	@Override
	public boolean isNodeFocusable() {
		return mApplicationClassInstance.isControllable(mContext, mCookie, IApplication.IGNORE_VALUE);
	}

	public AnalogSearchMenuItem(Context context, AttributeSet attrs, ResourceHelper reshelp) {
		super(context, attrs, reshelp);

		mContext = context;
		mInflater = LayoutInflater.from(context);

		mFrameLayoutContainer = (FrameLayout) mInflater.inflate(R.layout.empty_framelayout_container, null);
		//mFrameLayoutContainer.addView(loadView(), 0);
		
	}

	protected RelativeLayout loadView() {
		Log.d(TAG, "m_isCollapsed is true");
		m_wrapper.enterNonInteruptableMode();

		analogSearchView = (RalativeLayoutView) mInflater.inflate(R.layout.manual_install_layout, null);
		analogSearchView.addListener(this);
		
		initFrequencyPicker(analogSearchView);
		initButtons(analogSearchView);
		
		return analogSearchView;
	}
	
	private void screenInitialization(){
		Log.d(TAG, "screenInitialization");
		
		initProgressBar();
		NotificationHandler.getInstance().registerForNotification(this);
		Log.d(TAG, "checking for wrapper flag");
		if (m_wrapper.isAnalogSwitchComplete() == false) 
		{
			Log.d(TAG, "IsAnalogPresetExists is false, showing wait animation");
			showProgressBar();
			m_buttonSearch.setEnabled(false);
		}
		m_isSearchInProgress = false;
		currentState = ManualInstallState.START_INSTALLATION;
		int l_freqArray[] = new int[2];
		m_wrapper.getFrequencyRange(l_freqArray);
		m_minFreq = l_freqArray[0];
		m_maxFreq = l_freqArray[1];
		setDisplayedFrequency(m_wrapper.GetManualSearchFrequency());
		analogSearchView.requestFocus();
		m_timer = new Timer();
	}

	private void initFrequencyPicker(RelativeLayout retView) {
		Log.d(TAG, "initialising views for frequency entry");
		leftPicker = (InputPicker) retView.findViewById(R.id.left_picker);

		leftPicker.setMaxValue(999);
		leftPicker.setEnabled(true);
		
		leftPicker.setOnClickListener(this);
		leftPicker.setInputPickerValueChangeListener(this);
		leftPicker.setValueConfirmListener(this);
		leftPicker.setValueEnteredListener(this);
		
	}

	private void initButtons(RelativeLayout retView) {
		Log.d(TAG, "initialising buttons");
		m_buttonSearch = (Button) retView.findViewById(R.id.button_dtr_search);
		m_buttonDone = (Button) retView.findViewById(R.id.button_dtr_done);
		m_buttonSearch.setOnClickListener(this);
		m_buttonDone.setOnClickListener(this);

		m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
		searchButtonState = SearchButtonState.SEARCH;
	}

	private void initProgressBar() {
		Log.d(TAG, "initProgressBar entry");
		ProgressBar l_progressBar = new ProgressBar(mContext);
		LayoutParams l_layoutParams = new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		l_progressBar.setLayoutParams(l_layoutParams);
		int l_width = (int) mContext.getResources().getDimension(R.dimen.dtr_search_npanel_waiting_anim_width);
		int l_height = (int) mContext.getResources().getDimension(R.dimen.dtr_search_npanel_waiting_anim_height);
		if(m_progressWindow == null){
			m_progressWindow = new PopupWindow(l_progressBar, l_width, l_height, true);
		}
		Log.d(TAG, "initProgressBar exit");
	}

	private int getDisplayedFrequency() {
		Log.d(TAG, "getDisplayedFrequency");
		int l_symbolRate = 0;
		
		l_symbolRate = leftPicker.getCurrValue();
		l_symbolRate *= 1000;
		Log.d(TAG, String.valueOf(l_symbolRate));
		return l_symbolRate;

	}

	private int getValidFrequency() {
		int l_freq = getDisplayedFrequency();
		if (l_freq < m_minFreq) {
			l_freq = m_minFreq;
		}
		if (l_freq > m_maxFreq) {
			l_freq = m_maxFreq;
		}
		setDisplayedFrequency(l_freq);
		Log.d(TAG, "getValidFrequency returning " + l_freq);
		return l_freq;
	}

	private void setDisplayedFrequency(int p_freq) {
		Log.d(TAG, "setDisplayedFrequency " + p_freq);

		p_freq /= 1000;
		String l_string = "000" + Integer.toString(p_freq);
		if (p_freq <= 0) {
			Log.d(TAG, "resetting string to 0");
			l_string = "000";
		}
		Log.d(TAG, "l_string = " + l_string);
		String l_displayString = l_string.substring(l_string.length() - NUM_PICKER, l_string.length());

		int l_displayedFreq = 0;
		try{
			l_displayedFreq = Integer.parseInt(l_displayString);
		}catch(Exception ex){
		}
		
		leftPicker.setCurrValue(l_displayedFreq);
		
	}

	private boolean onKeyLeft() {
		boolean l_ret = true;
		Activity l_activity = (Activity) mContext;
		Log.d(TAG, "Before getting focus view");
		View l_focusView = l_activity.getCurrentFocus();
		Log.d(TAG, "After getting focus view");
		Log.d(TAG, "focus item id " + String.valueOf(l_focusView.getId()));

		switch (l_focusView.getId()) {
		case R.id.left_picker:
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
			onScreenExit();
			l_ret = true;
			break;
		case R.id.button_dtr_done:
			m_buttonSearch.requestFocus();
			Log.d(TAG, "Focus on button");
			l_ret = true;
			break;
		case R.id.button_dtr_search:
			leftPicker.requestFocus();
			l_ret = true;
			break;

		}

		return l_ret;
	}

	private boolean onKeyRight() {
		boolean l_ret = true;
		Activity l_activity = (Activity) mContext;
		View l_focusView = l_activity.getCurrentFocus();
		Log.d(TAG, "focus item id " + String.valueOf(l_focusView.getId()));
		switch (l_focusView.getId()) {
		case R.id.left_picker:
			m_buttonSearch.requestFocus();
			break;
		case R.id.button_dtr_search:
			if (searchButtonState == SearchButtonState.SEARCH) {
				m_buttonDone.requestFocus();
			} else if (searchButtonState == SearchButtonState.CANCEL) {
				// ignore right focus
			}
			break;
		case R.id.button_dtr_done:
			Log.d(TAG, "Focus on done button");
			break;
		default:
			l_ret = false;
			break;
		}
		return l_ret;
	}

	@Override
	public boolean handleKeyEvent(KeyEvent event) {
		Log.d(TAG, "dispatchKeyEvent for the DTR screen " + String.valueOf(event.getKeyCode()));
		Boolean l_ret = false;
		Activity l_activity = (Activity) mContext;
		View l_focusView = l_activity.getCurrentFocus();
		int focusViewId;
		switch (event.getKeyCode()) {
		case KeyEvent.KEYCODE_DPAD_LEFT:
		case KeyEvent.KEYCODE_SOFT_LEFT:
			if (event.getAction() == KeyEvent.ACTION_DOWN) {
				l_ret = onKeyLeft();
			} else {
				l_ret = true;
			}
			break;
		case KeyEvent.KEYCODE_DPAD_RIGHT:
		case KeyEvent.KEYCODE_SOFT_RIGHT:
			if (event.getAction() == KeyEvent.ACTION_DOWN) {
				l_ret = onKeyRight();
			} else {
				l_ret = true;
			}
			break;
		case KeyEvent.KEYCODE_BACK:
		case KeyEvent.KEYCODE_DEL:
			Log.d(TAG, "KEYCODE_BACK / KEYCODE_DEL");
			if (m_isSearchInProgress) {
				m_progressWindow.dismiss();
				m_wrapper.StopManualSearch();
				if (m_timer != null) {
					m_timer.cancel();
					m_timer.purge();
				}
			} else {
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
				onScreenExit();
			}
			l_ret = true;
			break;
		case KeyEvent.KEYCODE_DPAD_DOWN:
			focusViewId = l_focusView.getId();
			if (event.getAction() == KeyEvent.ACTION_DOWN) {
				switch (focusViewId) {
				case R.id.button_dtr_search:
					if (searchButtonState == SearchButtonState.SEARCH) {
						m_buttonDone.requestFocus();
					} else if (searchButtonState == SearchButtonState.CANCEL) {
						// ignore down focus
					}
					break;
				case R.id.button_dtr_done:
					l_ret = true;
					break;
				default:
					break;
				}
			}
			break;
		case KeyEvent.KEYCODE_DPAD_UP:
			focusViewId = l_focusView.getId();
			if (event.getAction() == KeyEvent.ACTION_DOWN) {
				switch (focusViewId) {
				case R.id.button_dtr_search:
					leftPicker.requestFocus();
					l_ret = true;
					break;
				case R.id.button_dtr_done:
					m_buttonSearch.requestFocus();
					l_ret = true;
					break;
				default:
					break;
				}
			}
			break;
		case KeyEvent.KEYCODE_PROG_BLUE:
			l_ret = true;
			break;

		}
		return l_ret;
	}

	private void onSearchComplete() {
		Log.d(TAG, "onSearchComplete entry");
		m_isSearchInProgress = false;
		m_buttonDone.requestFocus();
		m_progressWindow.setOnDismissListener(null);
		m_progressWindow.dismiss();
		m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
		m_buttonSearch.setEnabled(true);
		searchButtonState = SearchButtonState.SEARCH;
		if (m_timer != null) {
			m_timer.cancel();
			m_timer.purge();
		}
		Log.d(TAG, "onSearchComplete exit");
	}

	@Override
	public void update(Observable observable, Object data) {
		Log.d(TAG, "update: action " + ((NotificationInfoObject) data).actionID + ", message " + ((NotificationInfoObject) data).message);
		final int l_eventID = ((NotificationInfoObject) data).actionID;
		Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				switch (l_eventID) {
				case EventIDs.EVENT_INST_TUNING_STATION_NOT_FOUND:
						Log.d(TAG, "search failed EVENT_INST_TUNING_STATION_NOT_FOUND");
					currentState = ManualInstallState.INSTALLATION_IN_PROGRESS;
					onSearchComplete();
					break;
				case EventIDs.EVENT_SHOW_SEARCH_AFTER_STRING: // search is
																// complete
					Log.d(TAG, "search success EVENT_SHOW_SEARCH_AFTER_STRING");
					currentState = ManualInstallState.INSTALLATION_IN_PROGRESS;
					m_wrapper.setTVMplSurface(m_wrapper.getTCSurface().getSurface());// search
																						// is
																						// complete
					m_wrapper.updateCachedAnalogSytemCountry();
					m_wrapper.setStoreAsNewChannelStatus(true);
					onSearchComplete();
					break;
				case EventIDs.EVENT_ANALOG_SWITCH_DONE:
					Log.d(TAG, "EVENT_ANALOG_SWITCH_DONE");
					m_progressWindow.setOnDismissListener(null);
					m_progressWindow.dismiss();
					m_buttonSearch.setEnabled(true);
					break;
				case EventIDs.EVENT_ANALOG_CH_FOUND:
					Log.d(TAG, "EVENT_ANALOG_CH_FOUND ");
					currentState = ManualInstallState.INSTALLATION_IN_PROGRESS;
					break;
				case EventIDs.EVENT_INST_STARTED:
					Log.d(TAG, "EVENT_INST_STARTED");
					currentState = ManualInstallState.INSTALLATION_IN_PROGRESS;
					break;
				case EventIDs.EVENT_INST_STOPPED:
					Log.d(TAG, "EVENT_INST_STARTED");
					currentState = ManualInstallState.START_INSTALLATION;
					m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
					searchButtonState = SearchButtonState.SEARCH;
					break;
				case EventIDs.EVENT_INST_COMPLETED:
					Log.d(TAG, "EVENT_INST_COMPLETED");
					currentState = ManualInstallState.START_INSTALLATION;
					m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
					searchButtonState = SearchButtonState.SEARCH;
					sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
					break;
				}
			}
		});

	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.button_dtr_search:
			Log.d(TAG, "Starting search: " + currentState + ": " + searchButtonState);
			showProgressBar();

			switch (searchButtonState) {
			case SEARCH:
				// m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);
				if (currentState == ManualInstallState.START_INSTALLATION) {
					m_wrapper.StopManualSearch();
					m_wrapper.updateUserEnteredManualFreq(getValidFrequency());
					m_wrapper.startInstallation(InstallationMode.MANUAL_INSTALLATION);
					currentState = ManualInstallState.INSTALLATION_IN_PROGRESS;
				} else if (currentState == ManualInstallState.INSTALLATION_IN_PROGRESS) {
					m_timer = new Timer();
					m_timer.schedule(new UpdateDisplayedFrequency(), 0, 100);
					m_wrapper.startFreqSearch();
				}

				searchButtonState = SearchButtonState.CANCEL;
				m_buttonSearch.requestFocus();
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
				break;
			case CANCEL:
				m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
				searchButtonState = SearchButtonState.SEARCH;
				m_wrapper.StopManualSearch();
				m_progressWindow.dismiss();
				break;
			}

			break;
		case R.id.button_dtr_done:
			Log.d(TAG, "ok on done/cancel");
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
			onScreenExit();
			break;
		}
	}

	class UpdateDisplayedFrequency extends TimerTask {
		@Override
		public void run() {
			Activity l_activity = (Activity) mContext;
			final int l_freq = m_wrapper.GetFrequency();
			l_activity.runOnUiThread(new Runnable() {

				@Override
				public void run() {
					setDisplayedFrequency(l_freq);
				}
			});
		}
	};

	private void showProgressBar() {
		Log.d(TAG, "showProgressBar entry");
		m_progressWindow.setBackgroundDrawable(new BitmapDrawable(mContext.getResources()));
		m_isSearchInProgress = true;
		m_buttonSearch.setEnabled(false);
		m_progressWindow.setOnDismissListener(new PopupWindow.OnDismissListener() {
			@Override
			public void onDismiss() {
				m_isSearchInProgress = false;
				m_buttonSearch.requestFocus();
				m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
				searchButtonState = SearchButtonState.SEARCH;
				m_buttonSearch.setEnabled(true);
				if (m_timer != null) {
					m_timer.cancel();
					m_timer.purge();
				}
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
			}
		});
		m_progressWindow.setFocusable(true);
		m_buttonSearch.requestFocus();

		int xOffset = 800;
		int yOffset = 325;
		m_progressWindow.showAtLocation(analogSearchView, Gravity.NO_GRAVITY, xOffset, yOffset);
		m_progressWindow.getContentView().setFocusableInTouchMode(true);

		m_progressWindow.getContentView().setOnKeyListener(new View.OnKeyListener() {

			@Override
			public boolean onKey(View v, int keyCode, KeyEvent event) {
				Log.d(TAG, "In key listener for popup window");
				return true;
			}
		});
	}

	private void onScreenExit() {
		Log.d(TAG, "onScreenExit");
		m_wrapper.StopManualSearch();
		m_wrapper.setTVMplSurface(null);
		NotificationHandler.getInstance().unregisterForNotification(this);
		m_isCollapsed = false;
		if (m_progressWindow != null) {
			m_progressWindow.dismiss();
		}
		m_wrapper.exitNonInteruptableMode();
		if(m_wrapper.getSettingsActivity() instanceof ChannelSettingsActivity){
			if(m_wrapper.getSettingsActivity() instanceof ChannelSettingsActivity){
				((ChannelSettingsActivity) m_wrapper.getSettingsActivity()).showHideColorKey(true);
			}
		}

		getMenuBuilder().refreshUI();
		getMenuBuilder().removeFocus();
		
	}

	@Override
	public void onInputPickerValueChanged(int arg0) {
		Log.d(TAG, "onInputPickerValueChanged: ");
		currentState = ManualInstallState.START_INSTALLATION;
	}

	@Override
	public void onInputPickerValueConfirm(int p_currValue) {
		Log.d(TAG, "onInputPickerValueConfirm");
		onKeyRight();
	}

	@Override
	public void onInputPickerValueEntered(int p_currValue) {
		Log.d(TAG, "onInputPickerValueEntered");
		currentState = ManualInstallState.START_INSTALLATION;
		onKeyRight();

	}

	private void sendIntent(String p_action) {
		Log.d(TAG, "sendIntent " + p_action);
		Intent l_intent = new Intent(p_action);
		l_intent.putExtra("InstallMode", "AnalogueManual");
		if (m_wrapper.AvailableCableMedium()) {
			l_intent.putExtra("InstallMedium", "Cable");
		} else {
			l_intent.putExtra("InstallMedium", "Terrestrial");
		}
		mContext.sendStickyBroadcast(l_intent);
	}

}
