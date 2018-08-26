package org.droidtv.euinstallertc.settings;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DTRScreenMode;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_MEDIUM;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallertc.service.LogoAssociationHandler.ILogoAssociationListner;
import org.droidtv.euinstallertc.settings.ChannelFreqNumberTable.ChanFreqNumEntry;
import org.droidtv.euinstallertc.util.CustomDialog;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.euinstallertc.util.IViewListener;
import org.droidtv.euinstallertc.util.RalativeLayoutView;
import org.droidtv.euinstallertc.util.SignalIndicatorView;
import org.droidtv.euinstallertc.wizard.screen.LCNConflictScreenActivity;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueChangeListener;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueConfirmation;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueEntered;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.helpers.ResourceHelper;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IMenuNodeControl;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;
import org.droidtv.tunerservice.util.PlayTvUtils;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.util.DisplayMetrics;

public class DTRMenuItem extends MenuItem implements IMenuNodeControl, Observer, IInputPickerValueChangeListener, IInputPickerValueConfirmation, OnClickListener, IViewListener,
		IInputPickerValueEntered {
	private final String TAG = DTRMenuItem.class.getName();
	protected Context mContext;
	private RalativeLayoutView dtrView;
	private LayoutInflater mInflater;
	private FrameLayout mFrameLayoutContainer;
	boolean isStoreInProgress = false;
	boolean ifSearchInProgress = false;
	boolean m_isSearchDone = false;
	private boolean m_ifDTRFreqEnabled = false;

	private TextView m_networkName_txtVw;
	private TextView m_sigQuality_txtVw;
	private TextView m_sigStrength_txtVw;
	private TextView m_sigQualityTitle_txtVw;
	private TextView m_sigStrengthTitle_txtVw;
	private TextView m_networkNumber_txtVw;
	private TextView m_channels_txtVw;
	private TextView m_symbolRateTxtVw;
	private TextView m_channelsTitleTxtVw;
	private TextView m_modulationTxtVw;
	private TextView m_networkNumberTitle_txtVw;
	private TextView m_modulationTitle_txtVw;
	private TextView m_networkNameTitle_txtVw;
	private TextView m_symbolRateTitle_txtVw;
	private RelativeLayout m_pickerLayoutView;
	private RelativeLayout m_radioLayoutView;
	private RadioSelector m_channelRadioList;
	private InputPicker leftPicker;
	private InputPicker rightPicker;

	private Timer m_timer;

	private LinearLayout m_resultLayout;

	private Button m_buttonSearch;
	private Button m_buttonDone;
	private Button m_buttonNetwork;
	//private Button m_buttonPrevious;

	private PopupWindow m_progressWindow;

	private SignalIndicatorView m_sigStrengthView;
	private SignalIndicatorView m_sigQualityView;

	private enum SEARCH_BUTTON_STATE{
		SEARCH_STATE,
		STORE_STATE,
		STOP_WHILE_SEARCHING
	}
	
	private SEARCH_BUTTON_STATE searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;

	private int m_plpIDs_array[];

	private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();;

	private Dialog m_plpIDDialog;
	
	private ArrayList<ModalDialog>  mModalDialogList;
    private ModalDialog mModalDialog;
    private ModalDialog.Builder mBuilder;;

	private ChannelFreqNumberTable m_chFNTableInst;
	private ArrayList<ChanFreqNumEntry> m_chFNTableList;
	private int m_selectedChannelNum = 0;
	
	private boolean ifSearchSuccessful = false;	

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
		
		if (true) {
		//HTV ++
		if (focus) {
			mFrameLayoutContainer.addView(loadView(), 0);
		}
		} else {
		//HTV --
		if (focus) {
			if(m_wrapper.getSettingsActivity() instanceof ChannelSettingsActivity){
				((ChannelSettingsActivity) m_wrapper.getSettingsActivity()).showHideColorKey(false);
			}
			mFrameLayoutContainer.addView(loadView(), 0);
			
		}

		((ChannelSettingsActivity) m_wrapper.getSettingsActivity()).ifDtrScreenActive(focus);
		}
	}

	@Override
	public boolean isNodeFocusable() {
		return mApplicationClassInstance.isControllable(mContext, mCookie, IApplication.IGNORE_VALUE);
	}

	public DTRMenuItem(Context context, AttributeSet attrs, ResourceHelper reshelp) {
		super(context, attrs, reshelp);
		Log.d(TAG, "DTRMenuItem()");
		mContext = context;
		mInflater = LayoutInflater.from(context);

		// RelativeLayout retView = (RelativeLayout)
		// mInflater.inflate(R.layout.dtr_holder_layout, null);
		mFrameLayoutContainer = (FrameLayout) mInflater.inflate(R.layout.empty_framelayout_container, null);
	}

	protected RelativeLayout loadView() {

		Log.d(TAG, "loading view");
		m_wrapper.enterNonInteruptableMode();
		m_ifDTRFreqEnabled = m_wrapper.isDTRStoreOptionAvailable();
		Log.d(TAG, "m_ifDTRFreqEnabled = " + m_ifDTRFreqEnabled);

		dtrView = (RalativeLayoutView) mInflater.inflate(R.layout.dtr_layout, null);
		dtrView.addListener(this);

		searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
				
		m_isSearchDone = false;
		isStoreInProgress = false;
		ifSearchInProgress = false;
		m_resultLayout = (LinearLayout) dtrView.findViewById(R.id.dtr_result_layout);
		mModalDialogList = new ArrayList<ModalDialog>();  
		ifSearchSuccessful = false;

		m_pickerLayoutView = (RelativeLayout) dtrView.findViewById(R.id.layout_dtr_pickerList);
		m_radioLayoutView = (RelativeLayout) dtrView.findViewById(R.id.layout_dtr_radioList);
		m_channelRadioList = (RadioSelector) dtrView.findViewById(R.id.dtr_radioList_channels);

		initProgressBar();
		initFrequencyPicker(dtrView);
		initButtons(dtrView);
		initTextViews(m_resultLayout);
		initSigIndicator(m_resultLayout);

		m_chFNTableInst = new ChannelFreqNumberTable(mContext);
		m_chFNTableList = m_chFNTableInst.getChannelFreqEntryList(m_wrapper.ifQuickInstallation(), m_wrapper.getCountryNameFromTVS());

		if (m_wrapper.getDTRScreenMode() == DTRScreenMode.LOAD_CHANNEL_FREQ) {
			m_pickerLayoutView.setVisibility(View.VISIBLE);
			m_channelRadioList.setVisibility(View.GONE);
			leftPicker.setFocusable(true);
			setDisplayedFrequency(m_wrapper.GetSearchFrequency());

			if (m_ifDTRFreqEnabled) {
				leftPicker.requestFocus();
			} else {
				m_buttonSearch.requestFocus();
			}
		} else if (m_wrapper.getDTRScreenMode() == DTRScreenMode.LOAD_CHANNEL_NUMBER) {
			m_pickerLayoutView.setVisibility(View.GONE);
			m_channelRadioList.setVisibility(View.VISIBLE);

			ChanFreqNumEntry freqEntry;
			Float freq;
			String[] ChannelFreqStrArray = new String[m_chFNTableList.size()];

			for (int index = 0; index < m_chFNTableList.size(); index++) {
				freqEntry = m_chFNTableList.get(index);
				freq = (float) ((float) (freqEntry.Frequency) / 1000.0f);
				ChannelFreqStrArray[index] = freqEntry.ChannelName + " - " + String.format("%.1f", freq) + " MHz";
			}
			m_channelRadioList.setArray(ChannelFreqStrArray);

			// get last tuned frequency
			String channelName = m_chFNTableInst.getChannelName(m_wrapper.GetSearchFrequency());
			if (channelName == null) {
				m_selectedChannelNum = 0;
			} else {
				for (int index = 0; index < m_chFNTableList.size(); index++) {
					if (channelName.equalsIgnoreCase(m_chFNTableList.get(index).ChannelName)) {
						m_selectedChannelNum = index;
						break;
					}
				}
			}

			// set the focus onlast tuned frequncy
			setFocusOnRadioItem(m_selectedChannelNum);

			m_channelRadioList.setOnItemClickListener(new OnItemClickListener() {
				@Override
				public void onItemClick(AdapterView<?> arg0, View selectedView, int selectedItem, long arg3) {
					Log.d(TAG, " selected radiolist item " + selectedItem);
					// set the frequency to mw
					m_selectedChannelNum = selectedItem;

					searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
					m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
					m_wrapper.StopInstallationIfNotIdle();

					// move the focus on search button
					m_buttonSearch.requestFocus();
				}
			});
		}

		m_resultLayout.setVisibility(View.INVISIBLE);
		// retView.requestFocus();

		m_timer = new Timer();
		NotificationHandler.getInstance().registerForNotification(this);

		Log.d(TAG, "load view done");
		return dtrView;

	}

	private void setFocusOnRadioItem(int position) {
		Log.d(TAG, "setFocusOnRadioItem: " + position);
		m_channelRadioList.smoothScrollToPosition(position);
		m_channelRadioList.requestFocusFromTouch();
		m_channelRadioList.requestFocus();
		m_channelRadioList.setSelection(position);
		m_channelRadioList.setItemChecked(position, true);
	}

	private void initProgressBar() {
		Log.d(TAG, "initProgressBar entry");
		ProgressBar l_progressBar = new ProgressBar(mContext);
		LayoutParams l_layoutParams = new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		l_progressBar.setLayoutParams(l_layoutParams);
		int l_width = (int) mContext.getResources().getDimension(R.dimen.dtr_search_npanel_waiting_anim_width);
		int l_height = (int) mContext.getResources().getDimension(R.dimen.dtr_search_npanel_waiting_anim_height);
		m_progressWindow = new PopupWindow(l_progressBar, l_width, l_height, true);
		Log.d(TAG, "initProgressBar exit");
	}

	private void initFrequencyPicker(RelativeLayout retView) {
		Log.d(TAG, "initialising views for frequency entry");
		leftPicker = (InputPicker) retView.findViewById(R.id.left_picker);
		rightPicker = (InputPicker) retView.findViewById(R.id.right_picker);

		leftPicker.setMaxValue(999);
		leftPicker.setEnabled(m_ifDTRFreqEnabled);
		if (m_ifDTRFreqEnabled) {
			leftPicker.setInputPickerValueChangeListener(this);
			leftPicker.setValueConfirmListener(this);
			leftPicker.setValueEnteredListener(this);
		}
		
		rightPicker.setMaxValue(99);
		rightPicker.setEnabled(m_ifDTRFreqEnabled);
		if (m_ifDTRFreqEnabled) {
			rightPicker.setInputPickerValueChangeListener(this);
			rightPicker.setValueConfirmListener(this);
			rightPicker.setValueEnteredListener(this);
		}
	}

	private void initButtons(RelativeLayout retView) {
		Log.d(TAG, "initialising buttons");
		m_buttonSearch = (Button) retView.findViewById(R.id.button_dtr_search);
		m_buttonDone = (Button) retView.findViewById(R.id.button_dtr_done);
		m_buttonNetwork = (Button) retView.findViewById(R.id.button_dtr_network);
		//m_buttonPrevious = (Button) retView.findViewById(R.id.button_dtr_previous);

		m_buttonSearch.setOnClickListener(this);
		m_buttonDone.setOnClickListener(this);
		m_buttonNetwork.setOnClickListener(this);
		//m_buttonPrevious.setOnClickListener(this);

		m_buttonNetwork.setVisibility(View.INVISIBLE);
	}

	private void enableDisableAllButtons(boolean ifEnabled) {
		m_buttonSearch.setEnabled(ifEnabled);
		m_buttonDone.setEnabled(ifEnabled);
		m_buttonNetwork.setEnabled(ifEnabled);
		//m_buttonPrevious.setEnabled(ifEnabled);
	}

	private void initTextViews(LinearLayout p_retView) {
		Log.d(TAG, "initialising textviews entry");
		m_networkName_txtVw = (TextView) p_retView.findViewById(R.id.textView_dtr_networkName);
		m_networkNumber_txtVw = (TextView) p_retView.findViewById(R.id.textView_dtr_networkNumber);
		m_channels_txtVw = (TextView) p_retView.findViewById(R.id.textView_dtr_channels_found);
		m_symbolRateTxtVw = (TextView) p_retView.findViewById(R.id.textView_dtr_rate);
		m_sigQuality_txtVw = (TextView) p_retView.findViewById(R.id.textView_dtr_quality);
		m_sigStrength_txtVw = (TextView) p_retView.findViewById(R.id.textView_dtr_sigStrength);
		m_channelsTitleTxtVw = (TextView) p_retView.findViewById(R.id.static_dtrTxt_channelsFound);
		m_modulationTxtVw = (TextView) p_retView.findViewById(R.id.textView_dtr_modulation);
		m_sigQualityTitle_txtVw = (TextView) p_retView.findViewById(R.id.static_dtr_quality);
		m_sigStrengthTitle_txtVw = (TextView) p_retView.findViewById(R.id.static_dtr_sigStrength);

		m_networkNumberTitle_txtVw = (TextView) p_retView.findViewById(R.id.title_textView_dtr_networkNumber);
		m_modulationTitle_txtVw = (TextView) p_retView.findViewById(R.id.static_dtrTxt_modulation);
		m_symbolRateTitle_txtVw = (TextView) p_retView.findViewById(R.id.static_textView_dtr_rate);
		m_networkNameTitle_txtVw = (TextView) p_retView.findViewById(R.id.static_dtr_name);

		Log.d(TAG, "initialising textviews exit");

	}

	private void initSigIndicator(LinearLayout retView) {
		m_sigStrengthView = (SignalIndicatorView) retView.findViewById(R.id.sigStrengthIndicator);
		int[] l_idArray = { org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_01, org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_02, org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_03,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_04, org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_05, org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_06 };
		int[] l_valueArray = { 17, 34, 51, 68, 85, 100 };
		m_sigStrengthView.init(l_idArray, l_valueArray);
		m_sigStrengthView.setValue(50);
		m_sigStrengthView.setVisibility(View.GONE);

		m_sigQualityView = (SignalIndicatorView) retView.findViewById(R.id.sigQualityIndicator);
		int[] l_qualityIdArray = { org.droidtv.ui.tvwidget2k15.R.drawable.signal_quality_01, org.droidtv.ui.tvwidget2k15.R.drawable.signal_quality_02, org.droidtv.ui.tvwidget2k15.R.drawable.signal_quality_03,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_quality_04 };
		int[] l_qualityValueArray = { 25, 50, 75, 100 };
		m_sigQualityView.init(l_qualityIdArray, l_qualityValueArray);
		m_sigQualityView.setValue(50);
		m_sigQualityView.setVisibility(View.GONE);

		hideResults();
	}

	private void hideResults() {
		m_networkNumber_txtVw.setVisibility(View.GONE);
		m_modulationTxtVw.setVisibility(View.GONE);
		m_symbolRateTxtVw.setVisibility(View.GONE);
		m_channels_txtVw.setVisibility(View.GONE);
		m_networkName_txtVw.setVisibility(View.GONE);

		m_networkNumberTitle_txtVw.setVisibility(View.GONE);
		m_modulationTitle_txtVw.setVisibility(View.GONE);
		m_networkNameTitle_txtVw.setVisibility(View.GONE);
		m_symbolRateTitle_txtVw.setVisibility(View.GONE);
		m_channelsTitleTxtVw.setVisibility(View.GONE);
		m_sigQualityTitle_txtVw.setVisibility(View.GONE);
		m_sigStrengthTitle_txtVw.setVisibility(View.GONE);
		m_sigQuality_txtVw.setVisibility(View.GONE);
		m_sigStrength_txtVw.setVisibility(View.GONE);
		m_sigStrengthView.setVisibility(View.GONE);
		m_sigQualityView.setVisibility(View.GONE);
	}

	private void showWaitingAnimation(boolean ifShow){
		Log.d(TAG, "showWaitingAnimation " + ifShow );
		
		if(ifShow){
			m_progressWindow.setOutsideTouchable(false);
			m_progressWindow.setFocusable(false);
			
			// as per UxD the waiting animation should come in between of video screen
		
		    /*int xOffset = 1050;
			int yOffset = 325;*/

			DisplayMetrics metrics = mContext.getResources().getDisplayMetrics();
			int widthScreen = metrics.widthPixels;
			int heightScreen = metrics.heightPixels;

			int xOffset= ((metrics.widthPixels - dtrView.getWidth())/2) + dtrView.getWidth() + (m_progressWindow.getWidth()/2);
			int yOffset =  (metrics.heightPixels/2) - (m_progressWindow.getHeight()/2);
			
			Log.d(TAG," " +  widthScreen +" " + heightScreen +" " + xOffset +" "+ yOffset);
			
			m_progressWindow.showAtLocation(dtrView, Gravity.NO_GRAVITY,xOffset,yOffset);
			m_progressWindow.getContentView().setFocusableInTouchMode(true);
		}else{
			if(m_progressWindow != null){
				m_progressWindow.dismiss();
			}
		}
	}
	
	/*
	private void showProgressBar(final boolean p_isCancelable) {
		Log.d(TAG, "showProgressBar entry" + p_isCancelable);
		if (p_isCancelable) {
			enableDisableAllButtons(false);
			m_progressWindow.setOnDismissListener(new PopupWindow.OnDismissListener() {
				@Override
				public void onDismiss() {
					Log.d(TAG, "cancelling installation");
					enableDisableAllButtons(true);
					m_wrapper.CancelTestReceptionInstallation();
					sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
				}
			});
			
		}
		m_progressWindow.setOutsideTouchable(true);
		m_progressWindow.setFocusable(true);
		
		// as per UxD the waiting animation should come in between of video screen
		//DisplayMetrics displayMetrics = mContext.getResources().getDisplayMetrics();
    	
	    int xOffset = 1050;
		int yOffset = 325;
		m_progressWindow.showAtLocation(dtrView, Gravity.NO_GRAVITY,xOffset,yOffset);
		m_progressWindow.getContentView().setFocusableInTouchMode(true);
		m_progressWindow.getContentView().setOnKeyListener(new OnKeyListener() {

			@Override
			public boolean onKey(View v, int keyCode, KeyEvent event) {
				Log.d(TAG, "In key listener for popup window");
				if(((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE))){
					if(p_isCancelable && (event.getAction() == KeyEvent.ACTION_UP)){
						m_progressWindow.dismiss();
					}
					return true;
				}else{
					// consume
					return true;
				}
					
			}
		});
	}*/

	private int getDisplayedFrequency() {
		Log.d(TAG, "getDisplayedFrequency");
		int l_symbolRate = 0;
		l_symbolRate = leftPicker.getCurrValue() * 100 + rightPicker.getCurrValue();
		Log.d(TAG, "getDisplayedFrequency " +  String.valueOf(l_symbolRate));
		return l_symbolRate;
	}

	private void setDisplayedFrequency(int p_freq) {
		Log.d(TAG, "setDisplayedFrequency " + p_freq);
		p_freq /= 10;
		String l_string = "00000" + Integer.toString(p_freq);
		if (p_freq <= 0) {
			l_string = "0000000000";
		}
		
		String l_displayString = l_string.substring(l_string.length() - 5, l_string.length());
		//int l_displayedFreq = Integer.parseInt(l_displayString);
		int freqInInt = 0;
		try{
			freqInInt = Integer.parseInt(l_displayString.substring(0,3));
		}catch(Exception ex){
		}
		leftPicker.setCurrValue(freqInInt);
		
		freqInInt = 0;
		try{
			freqInInt = Integer.parseInt(l_displayString.substring(3,5));
		}catch(Exception ex){
		}
		rightPicker.setCurrValue(freqInInt);
	}

	private boolean onKeyLeft() {
		boolean l_ret = false;
		Activity l_activity = (Activity) mContext;
		View l_focusView = l_activity.getCurrentFocus();
		Log.d(TAG, "focus item id " + String.valueOf(l_focusView.getId()));

		switch (l_focusView.getId()) {
		case R.id.left_picker:
			m_wrapper.CancelTestReceptionInstallation();
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
			onScreenExit(true);
			(InstallerActivityManager.getInstance()).exitInstallation(EXIT_INSTALLER_REASON.USER_TRIGGERED_EXIT);
			l_ret = true;
			break;
		case R.id.right_picker:
			leftPicker.requestFocus();
			l_ret = true;
			break;
		case R.id.button_dtr_search:
			if (m_buttonNetwork.getVisibility() == View.VISIBLE) {
				m_buttonNetwork.requestFocus();
			} else {
				leftPicker.requestFocus();
			}
			l_ret = true;
			break;
		case R.id.button_dtr_network:
			leftPicker.requestFocus();
			l_ret = true;
			break;
		case R.id.button_dtr_done:
			m_buttonSearch.requestFocus();
			Log.d(TAG, "Focus on button");
			l_ret = true;
			break;
		case R.id.dtr_radioList_channels:
			m_wrapper.CancelTestReceptionInstallation();
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
			onScreenExit(true);
			(InstallerActivityManager.getInstance()).exitInstallation(EXIT_INSTALLER_REASON.USER_TRIGGERED_EXIT);
			l_ret = true;
			break;
		}

		return l_ret;
	}

	private boolean onKeyRight() {
		boolean l_ret = false;
		Activity l_activity = (Activity) mContext;
		View l_focusView = l_activity.getCurrentFocus();
		Log.d(TAG, "focus item id " + String.valueOf(l_focusView.getId()));

		switch (l_focusView.getId()) {
		case R.id.left_picker:
			rightPicker.requestFocus();
			l_ret = true;
			break;
		case R.id.right_picker:
			if (m_buttonNetwork.getVisibility() == View.VISIBLE) {
				m_buttonNetwork.requestFocus();
			} else {
				m_buttonSearch.requestFocus();
			}
			l_ret = true;
			break;
		case R.id.button_dtr_search:
			m_buttonDone.requestFocus();
			l_ret = true;
			break;
		case R.id.button_dtr_network:
			m_buttonSearch.requestFocus();
			break;
		case R.id.button_dtr_done:
			Log.d(TAG, "Focus on done button");
			l_ret = true;
			break;
		case R.id.dtr_radioList_channels:
			if (m_buttonNetwork.getVisibility() == View.VISIBLE) {
				m_buttonNetwork.requestFocus();
			} else {
				m_buttonSearch.requestFocus();
			}
			l_ret = true;
			break;
		}

		return l_ret;
	}

	@Override
	public boolean handleKeyEvent(KeyEvent event) {
		Log.d(TAG, "dispatchKeyEvent for the DTR screen " + String.valueOf(event.getKeyCode()));
		Boolean l_ret = false;
		Activity activity = (Activity) mContext;
		View focusView = activity.getCurrentFocus();
		Log.d(TAG, "focusView " + activity.getCurrentFocus());

		if (isStoreInProgress) {
			if((event.getKeyCode() == KeyEvent.KEYCODE_BACK) ||(event.getKeyCode() == KeyEvent.KEYCODE_DEL) ){
				Log.d(TAG, "Keys blocked, returning");
				// back key pressed during store in progress
				return true;
			}
		}else if (ifSearchInProgress){
			if((event.getKeyCode() == KeyEvent.KEYCODE_BACK) ||(event.getKeyCode() == KeyEvent.KEYCODE_DEL) || (event.getKeyCode() == KeyEvent.KEYCODE_DPAD_CENTER  )){
				// continue i.e allow the keys ( back key and ok key on  stop button)
			}else{
				Log.d(TAG, "Keys blocked, returning");
				return true;
			}
		}
		
		
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
			case KeyEvent.KEYCODE_DPAD_UP:
				int l_focusViewId = focusView.getId();
				if (event.getAction() == KeyEvent.ACTION_DOWN) {
					switch (l_focusViewId) {
					case R.id.left_picker:
					case R.id.right_picker:
						l_ret = true;
						break;
					case R.id.button_dtr_search:
					case R.id.button_dtr_done:
					case R.id.button_dtr_network:
						if (m_ifDTRFreqEnabled == true) {
							if (m_wrapper.getDTRScreenMode() == DTRScreenMode.LOAD_CHANNEL_FREQ) {
								leftPicker.requestFocus();
							} else if (m_wrapper.getDTRScreenMode() == DTRScreenMode.LOAD_CHANNEL_NUMBER) {
								setFocusOnRadioItem(m_selectedChannelNum);
							}
						}
						l_ret = true;
						break;
					}
				} else {
					l_ret = true;
				}
				break;
			case KeyEvent.KEYCODE_DPAD_DOWN:
				if (event.getAction() == KeyEvent.ACTION_DOWN) {
					switch (focusView.getId()) {
						case R.id.left_picker:
						case R.id.right_picker:
							m_buttonSearch.requestFocus();
							l_ret = true;
							break;
						case R.id.button_dtr_search:
						case R.id.button_dtr_done:
						case R.id.button_dtr_network:
							/* case R.id.button_dtr_previous: */
							l_ret = true;
							break;
					}
				} else {
					l_ret = true;
				}
				break;
			case KeyEvent.KEYCODE_BACK:
			case KeyEvent.KEYCODE_DEL:
				if (event.getAction() != KeyEvent.ACTION_DOWN) {
					Log.d(TAG, "KEYCODE_BACK / KEYCODE_DEL searchButtonState: " + searchButtonState);
					switch (searchButtonState) {
					case SEARCH_STATE:
					case STORE_STATE:
						enableDisableAllButtons(true);
						showWaitingAnimation(false);
						m_wrapper.CancelTestReceptionInstallation();
						sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
						onScreenExit(true);
						(InstallerActivityManager.getInstance()).exitInstallation(EXIT_INSTALLER_REASON.USER_TRIGGERED_EXIT);
						break;
					case STOP_WHILE_SEARCHING:
					
						enableDisableAllButtons(true);
						showWaitingAnimation(false);
	
						m_wrapper.CancelTestReceptionInstallation();
						sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
	
						searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
						// retain search state
						m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
						
						ifSearchInProgress = false;
						break;
	
					default:
						break;
					}
				}
				l_ret = true;
				break;
			case KeyEvent.KEYCODE_PROG_BLUE:
				// consume blue key
				l_ret = true;
				break;
			default:
				l_ret = true;
				break;
		}
		return l_ret;
	}

	private void onSearchFail() // did not find channels
	{
		Log.d(TAG, "onSearchFail entry");
		m_buttonDone.requestFocus();

		ifSearchSuccessful = false;
		ifSearchInProgress = false;
		m_resultLayout.setVisibility(View.VISIBLE);
		
		m_networkNameTitle_txtVw.setVisibility(View.VISIBLE);
		m_networkNameTitle_txtVw.setText(org.droidtv.ui.strings.R.string.MAIN_CHANNELS_FOUND_COLON);
		
		m_networkName_txtVw.setVisibility(View.VISIBLE);
		m_networkName_txtVw.setText("0");
		
		searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
		// retain search state
		m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
		
	}

	private void onChannelFound() {
		Log.d(TAG, "onChannelFound entry");
		boolean l_isHierarchialMuxFound = m_wrapper.IsHierarchialMuxFound();
		boolean l_isAvailableCableMedium = false;
		int l_getHierarchialMuxNetworkNumber = 0;
		String l_modulation = m_wrapper.GetTestReceptionModulation();
		long l_symbolRate = 0;
		
		ifSearchSuccessful = true;

		m_isSearchDone = true;

		if (l_isHierarchialMuxFound) {
			Log.d(TAG, "l_isHierarchialMuxFound is true");
			l_getHierarchialMuxNetworkNumber = m_wrapper.GetHierarchialMuxNetworkNumber();
		} else {
			l_isAvailableCableMedium = m_wrapper.AvailableCableMedium();
			if (l_isAvailableCableMedium) {
				l_symbolRate = m_wrapper.GetSymbolRateDisplay();
				Log.d(TAG, "Symbol rate " + String.valueOf(l_symbolRate));
			}
		}

		m_resultLayout.setVisibility(View.VISIBLE);
		//m_channelsTitleTxtVw.setText(org.droidtv.ui.strings.R.string.MAIN_CHANNELS_FOUND_COLON);
		m_networkNameTitle_txtVw.setVisibility(View.VISIBLE);
		m_networkNameTitle_txtVw.setText(org.droidtv.ui.strings.R.string.MAIN_NETWORK_NAME_COLON);
		if (m_ifDTRFreqEnabled) {
			Log.d(TAG, "store option available");
			searchButtonState = SEARCH_BUTTON_STATE.STORE_STATE;
			// retain search state
			m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_STORE);
			m_buttonSearch.requestFocus();
		} else {
			Log.d(TAG, "store option unavailable");
			searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
			m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
			m_buttonDone.requestFocus();
		}
		if (l_isHierarchialMuxFound) 
		{
			Log.d(TAG, "uithread : isHierarchialMuxFound is true");
			m_networkNumber_txtVw.setVisibility(View.VISIBLE);
			m_buttonNetwork.setVisibility(View.VISIBLE);
			m_networkNumberTitle_txtVw.setVisibility(View.VISIBLE);
			m_networkNumber_txtVw.setText(String.valueOf(l_getHierarchialMuxNetworkNumber));

		} 
		else 
		{
			m_modulationTxtVw.setVisibility(View.VISIBLE);
			m_modulationTitle_txtVw.setVisibility(View.VISIBLE);
			m_modulationTxtVw.setText(l_modulation);
			if (l_isAvailableCableMedium) 
			{
				Log.d(TAG, "uithread : isAvailableCableMedium is true");
				m_symbolRateTitle_txtVw.setVisibility(View.VISIBLE);
				m_symbolRateTxtVw.setVisibility(View.VISIBLE);
				String l_rateStr = String.valueOf(l_symbolRate / 1000) + "." + String.valueOf(l_symbolRate % 1000);
				m_symbolRateTxtVw.setText(String.valueOf(l_rateStr));
			}
		}
		updateNetworkName();

		m_timer = new Timer();
		m_sigStrengthView.setVisibility(View.VISIBLE);
		m_sigQualityView.setVisibility(View.VISIBLE);
		m_sigStrength_txtVw.setVisibility(View.VISIBLE);
		m_sigQuality_txtVw.setVisibility(View.VISIBLE);
		m_sigStrengthTitle_txtVw.setVisibility(View.VISIBLE);
		m_sigQualityTitle_txtVw.setVisibility(View.VISIBLE);
		m_timer.schedule(new UpdateSignalQuality(), 0, 5000);
		Log.d(TAG, "OnChannelFound exit");

	}

	private void updateNetworkName() {
		boolean ifCountryIsDVBTLite = m_wrapper.isDVBTLightSupported();
		String netWrkName = "";
		if (ifCountryIsDVBTLite == false) {
			netWrkName = m_wrapper.GetTestReceptionNetworkName();
			m_networkNameTitle_txtVw.setVisibility(View.VISIBLE);
			m_networkName_txtVw.setVisibility(View.VISIBLE);
			m_networkName_txtVw.setText(netWrkName);
		}
	}

	private void onStore() {
		Log.d(TAG, "onStore");
		if(ifSearchSuccessful){
			int l_channelsStored = m_wrapper.GetTestReceptionNoOfChannelsStored();
			final int channelsStored = l_channelsStored;
			m_resultLayout.setVisibility(View.VISIBLE);
			m_channels_txtVw.setVisibility(View.VISIBLE);
			m_channelsTitleTxtVw.setVisibility(View.VISIBLE);
			m_channelsTitleTxtVw.setText(org.droidtv.ui.strings.R.string.MAIN_MSG_CHANNELS_STORED_COLON);
			m_channels_txtVw.setText(String.valueOf(channelsStored));
		}
		m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
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

				case EventIDs.EVENT_INST_CHANNEL_NOT_FOUND:
				case EventIDs.EVENT_INST_TUNING_STATION_NOT_FOUND:
					isStoreInProgress = false;
					ifSearchInProgress = false;
					enableDisableAllButtons(true);
					showWaitingAnimation(false);
					Log.d(TAG, "calling onSearchFail");
					onSearchFail();
					break;

				case EventIDs.EVENT_DIGIT_CH_FOUND:
					Log.d(TAG, "EVENT_DIGIT_CH_FOUND");
					if (!m_isSearchDone) {
						isStoreInProgress = false;
						ifSearchInProgress = false;
						enableDisableAllButtons(true);
						showWaitingAnimation(false);
						Log.d(TAG, "calling onChannelFound");
						onChannelFound();
						m_wrapper.muteAudio(false);
						m_wrapper.setTVMplSurface(m_wrapper.getTCSurface().getSurface());// search
																							// is
																							// complete
					} else if (m_wrapper.IsHierarchialMuxFound()) {
						// channel found event came on press of network 1/2
						// button
						updateNetworkName();
					}

					break;

				case EventIDs.EVENT_INST_COMPLETED:
					Log.d(TAG, "EVENT_INST_COMPLETED");
					if(ifSearchSuccessful){
						m_wrapper.commitDatabaseToTvProvider(false);
					}else{
						onInstallationComplete();
					}
					break;

				case EventIDs.EVENT_PLPIDS_DETECTED:
					Log.d(TAG, "EVENT_PLPIDS_DETECTED");
					m_plpIDs_array = m_wrapper.getPLPIDs();
					if (m_plpIDs_array.length > 1) {
						launchPLPIDDialog();
					}
					break;
				case EventIDs.EVENT_LCN_CONFLICT:
					Log.d(TAG, "EVENT_LCN_CONFLICT");
					// show dialog
					launchLCNConflictMessageDialog();
					break;
				case EventIDs.EVENT_COMMIT_FINISHED:
					Log.d(TAG, "EVENT_COMMIT_FINISHED");
					m_wrapper.startLogoAssociation(m_wrapper.getSelectedDVBTOrDVBCFromTVS(), new ILogoAssociationListner() {
						
						@Override
						public void notifyLogoAssociationComplete() {
							onInstallationComplete();
						}
						
						@Override
						public void notifyLogoAssociationAborted() {
							onInstallationComplete();
						}
					});
					break;
				}
			}
		});
	}

	private void launchLCNConflictMessageDialog() {
		Log.d(TAG, "launchLCNConflictMessageDialog ");
		if (mModalDialog != null) {
			mModalDialog.dismiss();
		}
		
		mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
		mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_GENERIC_MESSAGE), "");
    	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_LCN_CONFLICT));
    	
    	mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SKIP),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "LCN Dialog Skip clicked");
    					mModalDialog.hide();
    					m_wrapper.lcnSelectionDone(false);
    				}
    			});
    	ModalDialogFooterButtonProp mLaunchButton = mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_RESOLVE),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					 Log.d(TAG, "LCN Dialog Resolve clicked");
    					 mModalDialog.hide();
                         mContext.startActivity(new Intent(mContext, LCNConflictScreenActivity.class));
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setOnKeyListener(new Dialog.OnKeyListener() {

			@Override
			public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event) {
				if (keyCode == KeyEvent.KEYCODE_BACK) {
                    mModalDialog.dismiss();
                    m_wrapper.lcnSelectionDone(false);
                    return true;
                }else{
                	return false;
                }
				
			}
        });
    	mLaunchButton.requestFocus();
    	mModalDialog.show();
    	mModalDialogList.add(mModalDialog);
	}

	private void launchPLPIDDialog() {
		Log.d(TAG, "launchPLPIDDialog ");
		m_plpIDDialog = new CustomDialog(mContext);
		m_plpIDDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
		m_plpIDDialog.getWindow().setBackgroundDrawableResource(android.R.color.transparent);
		m_plpIDDialog.setContentView(R.layout.dialog_radiolist);
		m_plpIDDialog.setCancelable(false);

		TextView dialog_title = (TextView) m_plpIDDialog.findViewById(R.id.dialog_title);
		final RadioSelector radioSelector = (RadioSelector) m_plpIDDialog.findViewById(R.id.dialog_RadioList);
		final Button doneButton = (Button) m_plpIDDialog.findViewById(R.id.dialog_done);

		String[] plpIDNames = new String[m_plpIDs_array.length];
		for (int localIndex = 0; localIndex < m_plpIDs_array.length; localIndex++) {
			plpIDNames[localIndex] = "PLP" + m_plpIDs_array[localIndex];
		}
		dialog_title.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_GENERIC_MESSAGE));
		dialog_title.setVisibility(View.VISIBLE);

		radioSelector.setArray(plpIDNames);

		radioSelector.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View selectedView, int selectedItem, long arg3) {
				Log.i(TAG, "Selected item:" + selectedItem);
				doneButton.requestFocus();
			}
		});

		doneButton.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				int selectedItem = radioSelector.getCheckedItemPosition();
				m_wrapper.setPLPID(m_plpIDs_array[selectedItem]);
				m_plpIDDialog.dismiss();
			}
		});

		m_plpIDDialog.show();

	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.button_dtr_search:
			
			switch (searchButtonState) {
				case SEARCH_STATE:
					// press search button for new frequency (fresh search)
					
					m_wrapper.stopDTRInstallation();
					m_isSearchDone = false;
					ifSearchInProgress = true;

					Log.d(TAG, "ok on search");
					hideResults();
					int l_frequency = 0;

					if (m_wrapper.getDTRScreenMode() == DTRScreenMode.LOAD_CHANNEL_NUMBER) {
						l_frequency = m_chFNTableList.get(m_selectedChannelNum).Frequency;
					} else if (m_wrapper.getDTRScreenMode() == DTRScreenMode.LOAD_CHANNEL_FREQ) {
						l_frequency = (getDisplayedFrequency() * 10);
					}

					Log.d(TAG, "l_frequency= " + l_frequency);
					if (l_frequency < 44000 || l_frequency > 870000) {
						Log.d(TAG, "DTR with Invalid Frequency");
						onSearchFail();

					} else {
						l_frequency = l_frequency / 10;
						m_resultLayout.setVisibility(View.INVISIBLE);
						m_wrapper.setTestReceptionFrequency(l_frequency);
						showWaitingAnimation(true);
						sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
					}

					// reset timers
					m_timer.cancel();
					m_timer.purge();
					
					if(m_wrapper.isDTRSearchInifinitely()){
						// disable all buttons except search button
						enableDisableAllButtons(false);
						m_buttonSearch.setEnabled(true);
						
						searchButtonState = SEARCH_BUTTON_STATE.STOP_WHILE_SEARCHING;
						// update search button to stop
						m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_STOP);
					}else{
						searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
						// retain search state
						m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
					}
					break;
				case STOP_WHILE_SEARCHING:
					Log.d(TAG, "ok on stop cancelling installation");
					enableDisableAllButtons(true);
					showWaitingAnimation(false);
					
					m_wrapper.CancelTestReceptionInstallation();
					sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
					
					searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
					// retain search state
					m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);

					onSearchFail();
					break;
				case STORE_STATE:
					Log.d(TAG, "ok on store");
					isStoreInProgress = true;
				
					showWaitingAnimation(true);
					
					m_wrapper.StoreTestReceptionInstallation();
					
					searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
					m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
					m_buttonDone.setEnabled(false);
					break;
	
				default:
					break;
			}
			break;

		case R.id.button_dtr_done:
			Log.d(TAG, "ok on done/cancel " + searchButtonState + " " + isStoreInProgress);
			NativeAPIEnums.InstallationMode l_installMode = NativeAPIEnums.InstallationMode.DTR_INSTALLATION;
			if (searchButtonState == SEARCH_BUTTON_STATE.STORE_STATE) {
				// Search done, but not store
				m_wrapper.CancelTestReceptionInstallation();
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
				l_installMode = NativeAPIEnums.InstallationMode.INCOMPLETE_INSTALLATION; // tune to default
				Log.d(TAG,"done pressed without storing");
				onScreenExit(false);
				(InstallerActivityManager.getInstance()).exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
				
			}else{
				Log.d(TAG,"done pressed ater storing tune");
				onScreenExit(false);
				(InstallerActivityManager.getInstance()).exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
				/*m_wrapper.switchToFirstAvailableChannel(l_installMode);
				((Activity) mContext).finish();*/
			}
			
			break;
		case R.id.button_dtr_network:
			Log.d(TAG, "ok on network button");
			// showPickList();
			int netwkNum = m_wrapper.toggleHierarchialMuxNetworkNumber();
			m_networkNumber_txtVw.setText(String.valueOf(netwkNum));
			break;
		default:
			break;

		}

	}
	
	private void onInstallationComplete(){
		Log.d(TAG, "onInstallationComplete");
		Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				isStoreInProgress = false;
				ifSearchInProgress = false;
				enableDisableAllButtons(true);
				 m_buttonDone.requestFocus();
				showWaitingAnimation(false);
				onStore();
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE");
			}
		});
	}

	private void sendIntent(String p_action) {
		Log.d(TAG, "sendIntent " + p_action);
		Intent l_intent = new Intent(p_action);
		l_intent.putExtra("InstallMode", "DTR");
		if (m_wrapper.AvailableCableMedium()) {

			l_intent.putExtra("InstallMedium", "Cable");

		} else {

			l_intent.putExtra("InstallMedium", "Terrestrial");

		}
		mContext.sendStickyBroadcast(l_intent);
	}

	class UpdateSignalQuality extends TimerTask {

		@Override
		public void run() {
			Log.d(TAG, "in timer task to UpdateSignalQuality");
			final long l_signalQuality;
			int l_sigQualityBer;
			final int l_signalStrength = m_wrapper.GetSignalStrength();
			l_signalQuality = m_wrapper.GetTestReceptionSignalQuality();
			l_sigQualityBer = m_wrapper.GetSignalQualityBer();
			final int l_berInt = l_sigQualityBer / 100;
			final int l_berDec = l_sigQualityBer % 100;

			Activity l_activity = (Activity) mContext;
			l_activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					m_sigStrengthView.setValue(l_signalStrength);
					m_sigQualityView.setValue((int) l_signalQuality);
					String signalQuality = " " + String.valueOf(l_signalQuality) + " (BER:" + l_berInt + "." + l_berDec + " X 1E-6)";
					m_sigQuality_txtVw.setText(signalQuality);
					m_sigStrength_txtVw.setText(" " + String.valueOf(l_signalStrength));
				}
			});

		}
	};

	private void onScreenExit(boolean ifUIUpdate) {
		Log.d(TAG, "unregistering for notification " + ifUIUpdate);

		NotificationHandler.getInstance().unregisterForNotification(this);
		m_wrapper.StopManualSearch();

		m_wrapper.setTVMplSurface(null);
		if (m_timer != null) {
			m_timer.cancel();
			m_timer.purge();
		}
		m_wrapper.exitNonInteruptableMode();

		if (ifUIUpdate) {
			getMenuBuilder().removeFocus();
			if(m_wrapper.getSettingsActivity() instanceof ChannelSettingsActivity){
				((ChannelSettingsActivity) m_wrapper.getSettingsActivity()).showHideColorKey(true);
			}
		}
	}

	@Override
	public void onInputPickerValueChanged(int arg0) {
		if (searchButtonState != SEARCH_BUTTON_STATE.SEARCH_STATE) {
			searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
			m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
			m_wrapper.StopInstallationIfNotIdle();
		}
	}

	@Override
	public void onInputPickerValueConfirm(int p_currValue) {
		Log.d(TAG, "onInputPickerValueConfirm");
		onKeyRight();

	}

	@Override
	public void onInputPickerValueEntered(int p_currValue) {
		Log.d(TAG, "onInputPickerValueEntered");
		if (searchButtonState != SEARCH_BUTTON_STATE.SEARCH_STATE) {
			searchButtonState = SEARCH_BUTTON_STATE.SEARCH_STATE;
			m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
			m_wrapper.StopInstallationIfNotIdle();
		}
		onKeyRight();

	}
}
