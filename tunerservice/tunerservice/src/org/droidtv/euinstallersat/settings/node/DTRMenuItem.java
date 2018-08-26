package org.droidtv.euinstallersat.settings.node;

import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.settings.ISettingsNotificationListener;
import org.droidtv.euinstallersat.settings.SatelliteSettingsActivity;
import org.droidtv.euinstallersat.settings.SettingsColourKeyManager;
import org.droidtv.euinstallersat.settings.node.view.DTRView;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.util.SignalIndicatorView;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.tvinput.ILogoAssociationControl.ILogoAssociationListener;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueChangeListener;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueConfirmation;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker.IInputPickerValueEntered;
import android.view.ViewGroup.LayoutParams;

import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.helpers.ResourceHelper;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IMenuNodeControl;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.graphics.drawable.BitmapDrawable;
import android.os.IBinder;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class DTRMenuItem extends MenuItem implements OnClickListener, IViewListener, ISettingsNotificationListener, IInputPickerValueChangeListener, IInputPickerValueEntered,
		IInputPickerValueConfirmation, IMenuNodeControl
{
	public boolean m_isCollapsed = false;

	private boolean m_isSearchInProgress = false;
	private boolean m_isStoreInProgress = false;
	private boolean m_isSigCheckInProgress = false;

	private int m_idxManualInsLNB;
	private ITvSettingsManager msettings =ITvSettingsManager.Instance.getInterface();

	private TextView m_satName_txtVw;
	private TextView m_sigQuality_txtVw;
	private TextView m_sigStrength_txtVw;
	private TextView m_sigQualityTitle_txtVw;
	private TextView m_sigStrengthTitle_txtVw;
	private TextView m_channels_txtVw;
	private TextView m_channelsTitleTxtVw;
	private TextView m_satNameTitle_txtVw;
	private InputPicker leftPicker;
	private PopupWindow m_progressWindow;

	private Button m_buttonSearch;
	private Button m_buttonDone;
	private SettingsColourKeyManager m_colourKeyManager;
	private FrameLayout mFrameLayoutContainer;

	private SignalIndicatorView m_sigStrengthView;
	private SignalIndicatorView m_sigQualityView;
	
	private Timer m_timer;

	private int TOGGLE_BUTTON_SEARCH = 0;
	private int TOGGLE_BUTTON_STORE = 1;
	private int m_toggleButton = 0;
	private int m_minFreq;
	private int m_maxFreq;

	private Context m_context;

	private NativeAPIWrapper m_wrapper;

	private LinearLayout m_resultLayout;
	private RelativeLayout m_retView;
	private LayoutInflater mInflater;
	private int NUM_PICKER = 5;

	private ILogoAssociationControl m_logoAssoInt = null;
	private ListenerImpl m_listener = new ListenerImpl();
	

	private static final String TAG = DTRMenuItem.class.getName();
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	public DTRMenuItem(Context context, AttributeSet attrs, ResourceHelper reshelp)
	{
		super(context, attrs, reshelp);
		m_context = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		mInflater = LayoutInflater.from(context);

		mFrameLayoutContainer = (FrameLayout) mInflater.inflate(R.layout.empty_framelayout_container, null);
	}

	public RelativeLayout loadCustomView()
	{
		return loadView();
	}

	@Override
	public View getView(Context ctx)
	{
		Log.d(TAG, "getView: " + mFrameLayoutContainer);

		if (mFrameLayoutContainer != null)
		{
			return mFrameLayoutContainer;
		} else
		{
			return super.getView(ctx);
		}
	}

	@Override
	public void setFocus(Boolean focus){
		Log.d(TAG, "setFocus " + focus);
		// super.setFocus(focus);
		mFrameLayoutContainer.removeAllViews();
		if (focus){
			if(m_wrapper.getSettingsActivity() instanceof SatelliteSettingsActivity){
				((SatelliteSettingsActivity) m_wrapper.getSettingsActivity()).showHideColorKey(false);
			}
			mFrameLayoutContainer.addView(loadView(), 0);
		}
	}

	@Override
	public boolean isNodeFocusable()
	{
		return mApplicationClassInstance.isControllable(mContext, mCookie, IApplication.IGNORE_VALUE);
	}

	protected RelativeLayout loadView()
	{
		Log.d(TAG, "loadView entry");
		m_wrapper.enterNonInteruptableMode();
		//m_colourKeyManager.disableBlueKey();
		//LayoutInflater l_inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		RelativeLayout retView = (RelativeLayout) mInflater.inflate(R.layout.satellite_dtr_holder_layout, null);

		DTRView l_dtrView = (DTRView) retView.findViewById(R.id.dTRView1);
		l_dtrView.addListener(this);
		m_toggleButton = TOGGLE_BUTTON_SEARCH;
		m_retView = retView;

		m_isStoreInProgress = false;

		m_resultLayout = (LinearLayout) l_dtrView.findViewById(R.id.dtr_result_layout);
		m_satName_txtVw = (TextView) l_dtrView.findViewById(R.id.textView_dtr_satName);
		m_satNameTitle_txtVw = (TextView) l_dtrView.findViewById(R.id.static_dtr_name);
		initProgressBar();
		initFrequencyPicker(retView);
		initButtons(retView);
		initTextViews(m_resultLayout);
		initSigIndicator(m_resultLayout);
		m_isSearchInProgress = false;
		m_isSigCheckInProgress = false;
		m_idxManualInsLNB = m_wrapper.GetLNBforManualIns();
		m_satName_txtVw.setText(getSatelliteName());
		setDisplayedFrequency(m_wrapper.GetFreq());
		int l_freqArray[] = new int[2];
		m_wrapper.getFrequencyRange(l_freqArray);
		m_minFreq = l_freqArray[0] / 1000;
		m_maxFreq = l_freqArray[1] / 1000;
		retView.requestFocus();
		NotificationHandler.getInstance().registerForNotification(this);

		Log.d(TAG, "loadView exit with layout");
		return retView;

	}

	public void setColourKeyManager(SettingsColourKeyManager p_colourKeyManager)
	{
		m_colourKeyManager = p_colourKeyManager;
	}

	private void initSigIndicator(LinearLayout retView)
	{
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
	}

	private void initProgressBar()
	{
		Log.d(TAG, "initProgressBar entry");
		ProgressBar l_progressBar = new ProgressBar(m_context);
		LayoutParams l_layoutParams = new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		l_progressBar.setLayoutParams(l_layoutParams);
		int l_width = (int) m_context.getResources().getDimension(R.dimen.dtr_search_npanel_waiting_anim_width);
		int l_height = (int) m_context.getResources().getDimension(R.dimen.dtr_search_npanel_waiting_anim_height);
		m_progressWindow = new PopupWindow(l_progressBar, l_width, l_height, true);
		Log.d(TAG, "initProgressBar exit");
	}

	private void initFrequencyPicker(RelativeLayout retView)
	{
		int l_idx;
		Log.d(TAG, "initialising views for frequency entry");
		leftPicker = (InputPicker) retView.findViewById(R.id.left_picker);

		leftPicker.setMaxValue(99999);
		leftPicker.setMinValue(0);
		leftPicker.setEnabled(true);
		leftPicker.setInputPickerValueChangeListener(this);
		leftPicker.setValueConfirmListener(this);
		leftPicker.setValueEnteredListener(this);
	}

	private void initButtons(RelativeLayout retView)
	{
		Log.d(TAG, "initialising buttons");
		m_buttonSearch = (Button) retView.findViewById(R.id.button_dtr_search);
		m_buttonDone = (Button) retView.findViewById(R.id.button_dtr_done);

		m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
		m_buttonSearch.setOnClickListener(this);
		m_buttonDone.setOnClickListener(this);
	}

	private void initTextViews(LinearLayout retView)
	{
		Log.d(TAG, "initialising textviews");

		m_channels_txtVw = (TextView) retView.findViewById(R.id.textView_dtr_channels_found);
		m_sigQuality_txtVw = (TextView) retView.findViewById(R.id.textView_dtr_quality);
		m_sigQualityTitle_txtVw = (TextView) retView.findViewById(R.id.static_dtr_quality);
		m_sigStrength_txtVw = (TextView) retView.findViewById(R.id.textView_dtr_sigStrength);
		m_sigStrengthTitle_txtVw = (TextView) retView.findViewById(R.id.static_dtr_sigStrength);
		m_channelsTitleTxtVw = (TextView) retView.findViewById(R.id.static_dtrTxt_channelsFound);

		Log.d(TAG, "initialising visibiity of textviews");

		m_channels_txtVw.setVisibility(View.GONE);
		m_channelsTitleTxtVw.setVisibility(View.GONE);
		m_sigStrength_txtVw.setVisibility(View.GONE);
		m_sigStrengthTitle_txtVw.setVisibility(View.GONE);
		m_sigQuality_txtVw.setVisibility(View.GONE);
		m_sigQualityTitle_txtVw.setVisibility(View.GONE);

	}

	private void hideResults()
	{
		m_channels_txtVw.setVisibility(View.GONE);
		m_channelsTitleTxtVw.setVisibility(View.GONE);
		m_sigStrength_txtVw.setVisibility(View.GONE);
		m_sigStrengthTitle_txtVw.setVisibility(View.GONE);
		m_sigQuality_txtVw.setVisibility(View.GONE);
		m_sigQualityTitle_txtVw.setVisibility(View.GONE);
		m_sigStrengthView.setVisibility(View.GONE);
		m_sigQualityView.setVisibility(View.GONE);
	}

	private String getSatelliteName()
	{
		Log.d(TAG, "getSatelliteName");
		String l_satName = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_NONE);
		if (!m_wrapper.IsLNBFree(m_idxManualInsLNB))
		{
			boolean l_isDuplicate = m_wrapper.IsSatelliteDuplicate(m_idxManualInsLNB);
			if (m_wrapper.GetIsRecognisedSatellite(m_idxManualInsLNB))
			{
				l_satName = m_wrapper.GetSatelliteName(m_idxManualInsLNB);
			} else
			{
				int l_displayIdx = m_idxManualInsLNB + 1;
				l_satName = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_SATELLITE) + l_displayIdx;
			}
			if (l_isDuplicate)
			{
				l_satName = l_satName + m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_DUPLICATE);
			}

		}
		Log.d(TAG, "getSatelliteName returning" + l_satName);
		return l_satName;
	}

	private int getDisplayedFrequency()
	{
		Log.d(TAG, "getDisplayedFrequency");
		int l_symbolRate = 0;
		int l_idx;
		
		l_symbolRate = leftPicker.getCurrValue();
		Log.d(TAG, String.valueOf(l_symbolRate));
		return l_symbolRate;
	}

	private void setDisplayedFrequency(int p_freq)
	{
		Log.d(TAG, "setDisplayedFrequency " + p_freq);
		int l_idx;
		String l_string = Integer.toString(p_freq) + "00000";
		if (p_freq <= 0)
		{
			l_string = "0000000000";
		}

		String l_displayString = l_string.substring(0, NUM_PICKER);
		Log.d(TAG, "l_displayString = " + l_displayString);
		
		int l_displayedFreq = 0;
		try{
			l_displayedFreq = Integer.parseInt(l_displayString);
		}catch(Exception ex){
		}
		
		leftPicker.setCurrValue(l_displayedFreq);
		
	}

	private void showProgressBar(boolean p_isCancelable)
	{
		Log.d(TAG, "showProgressBar entry" + p_isCancelable);
		if (p_isCancelable)
		{
			m_progressWindow.setBackgroundDrawable(new BitmapDrawable(m_context.getResources()));
			m_progressWindow.setOnDismissListener(new PopupWindow.OnDismissListener()
			{

				@Override
				public void onDismiss()
				{
					sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_STOPPED");
				}
			});
			m_progressWindow.setFocusable(true);

		} else
		{
			m_progressWindow.setFocusable(false);
		}
		
		int xOffset = 1125;
		int yOffset = 325;
		m_progressWindow.showAtLocation(m_retView, Gravity.NO_GRAVITY, xOffset, yOffset);
		m_progressWindow.getContentView().setFocusableInTouchMode(true);

		m_progressWindow.getContentView().setOnKeyListener(new View.OnKeyListener()
		{
			@Override
			public boolean onKey(View v, int keyCode, KeyEvent event)
			{
				Log.d(TAG, "In key listener for popup window");
				return true;
			}
		});
	}

	private boolean onKeyRight()
	{
		boolean l_ret = true;
		Activity l_activity = (Activity) m_context;
		View l_focusView = l_activity.getCurrentFocus();
		Log.d(TAG, "focus item id " + String.valueOf(l_focusView.getId()));

		switch (l_focusView.getId())
		{
			case R.id.left_picker:
				m_buttonSearch.requestFocus();
				break;
			case R.id.button_dtr_search:
				m_buttonDone.requestFocus();
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

	private boolean onKeyLeft()
	{
		boolean l_ret = true;
		Activity l_activity = (Activity) m_context;
		Log.d(TAG, "Before getting focus view");
		View l_focusView = l_activity.getCurrentFocus();
		Log.d(TAG, "focus item id " + String.valueOf(l_focusView.getId()));

		switch (l_focusView.getId())
		{
			case R.id.left_picker:
				onScreenExit(true);
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

	@Override
	public boolean handleKeyEvent(KeyEvent event)
	{
		Log.d(TAG, "dispatchKeyEvent for the DTR screen " + String.valueOf(event.getKeyCode()));
		Boolean l_ret = false;
		int l_keyCode = event.getKeyCode();
		Activity l_activity = (Activity) m_context;
		View l_focusView = l_activity.getCurrentFocus();
		if (m_isStoreInProgress)
		{
			Log.d(TAG, "Keys blocked, returning");
			l_ret = true;
			return l_ret;
		}

		switch (l_keyCode)
		{
			case KeyEvent.KEYCODE_DPAD_LEFT:
			case KeyEvent.KEYCODE_SOFT_LEFT:
				if (event.getAction() == KeyEvent.ACTION_DOWN)
				{
					l_ret = onKeyLeft();
				} else
				{
					l_ret = true;
				}
				break;
			case KeyEvent.KEYCODE_DPAD_RIGHT:
			case KeyEvent.KEYCODE_SOFT_RIGHT:
				if (event.getAction() == KeyEvent.ACTION_DOWN)
				{
					l_ret = onKeyRight();
				} else
				{
					l_ret = true;
				}
				break;
			case KeyEvent.KEYCODE_DPAD_UP:
				int l_focusViewId = l_focusView.getId();
				if (event.getAction() == KeyEvent.ACTION_DOWN)
				{
					switch (l_focusViewId)
					{
						case R.id.left_picker:
							l_ret = true;
							break;
						case R.id.button_dtr_search:
						case R.id.button_dtr_done:
							leftPicker.requestFocus();
							l_ret = true;
							break;
					}
				} else
				{
					l_ret = true;
				}
				break;
			case KeyEvent.KEYCODE_DPAD_DOWN:
				if (event.getAction() == KeyEvent.ACTION_DOWN)
				{
					switch (l_focusView.getId())
					{
						case R.id.left_picker:
							m_buttonSearch.requestFocus();
							l_ret = true;
							break;
						case R.id.button_dtr_search:
						case R.id.button_dtr_done:
							l_ret = true;
							break;
					}
				} else
				{
					l_ret = true;
				}
				break;
			case KeyEvent.KEYCODE_BACK:
			case KeyEvent.KEYCODE_DEL:
			case KeyEvent.KEYCODE_ESCAPE:
				Log.d(TAG, "KEYCODE_BACK / KEYCODE_DEL / KEYCODE_ESCAPE");
				if (m_isSearchInProgress)
				{
					m_progressWindow.dismiss();
				}
				onScreenExit(true);
				l_ret = true;
				break;
			case KeyEvent.KEYCODE_VOLUME_DOWN:
			case KeyEvent.KEYCODE_VOLUME_UP:
			case KeyEvent.KEYCODE_VOLUME_MUTE:
				l_ret = false;
				break;
			default:
				Log.d(TAG, "passing key to base class");
				l_ret = true;
				break;
		}
		return l_ret;
	}

	private void onSearchFail() // did not find channels
	{
		Log.d(TAG, "onSearchFail entry");
		m_resultLayout.setVisibility(View.VISIBLE);
		m_isSearchInProgress = false;
		m_satName_txtVw.setText(org.droidtv.ui.strings.R.string.MAIN_NONE);
		m_buttonDone.requestFocus();
		m_channels_txtVw.setVisibility(View.VISIBLE);
		m_channelsTitleTxtVw.setVisibility(View.VISIBLE);
		m_satNameTitle_txtVw.setText(org.droidtv.ui.strings.R.string.MAIN_SATELLITE_COLON);
		m_channels_txtVw.setText("0");
		m_progressWindow.setOnDismissListener(null);
		m_progressWindow.dismiss();
	}

	private void onChannelFound()
	{
		Log.d(TAG, "onChannelFound entry");
		m_satName_txtVw.setText(getSatelliteName());
		startSignalStrengthCheck();
		m_progressWindow.setOnDismissListener(null);
		m_progressWindow.dismiss();
		m_satNameTitle_txtVw.setText(org.droidtv.ui.strings.R.string.MAIN_SATELLITE_COLON);
		m_channels_txtVw.setVisibility(View.INVISIBLE);
		m_channelsTitleTxtVw.setVisibility(View.INVISIBLE);
		m_resultLayout.setVisibility(View.VISIBLE);
		m_sigStrengthView.setVisibility(View.VISIBLE);
		m_sigQualityView.setVisibility(View.VISIBLE);
		if (m_wrapper.isDTRStoreOptionAvailable() == true) {
			m_buttonSearch.requestFocus();
			m_toggleButton = TOGGLE_BUTTON_STORE;
			m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_STORE);

		} else {
			m_buttonSearch.requestFocus();
			m_toggleButton = TOGGLE_BUTTON_SEARCH;
			m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
		}
	Log.d(TAG, "onChannelFound entry m_toggleButton " + m_toggleButton);

	}

	private void onStore()
	{
		Log.d(TAG, "onStore entry");
		m_isStoreInProgress = false;
		m_satNameTitle_txtVw.setText(org.droidtv.ui.strings.R.string.MAIN_SATELLITE_COLON);
		m_satName_txtVw.setText(getSatelliteName());
		m_channels_txtVw.setVisibility(View.VISIBLE);
		m_channelsTitleTxtVw.setVisibility(View.VISIBLE);
		int l_tvChannelsFound = m_wrapper.GetTvServices(true, m_idxManualInsLNB);
		int l_radioChannelsFound = m_wrapper.GetRadioServices(true, m_idxManualInsLNB);
		m_channels_txtVw.setText(String.valueOf(l_tvChannelsFound + l_radioChannelsFound));
		m_toggleButton = TOGGLE_BUTTON_SEARCH;
		m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
		m_buttonDone.requestFocus();
		Log.d(TAG, "onStore exit");
	}

	private void startSignalStrengthCheck()
	{
		Log.d(TAG, "startSignalStrengthCheck entry");
		if (!m_isSigCheckInProgress)
		{
			m_sigStrength_txtVw.setVisibility(View.VISIBLE);
			m_sigStrengthTitle_txtVw.setVisibility(View.VISIBLE);
			m_sigQuality_txtVw.setVisibility(View.VISIBLE);
			m_sigQualityTitle_txtVw.setVisibility(View.VISIBLE);
			m_sigStrengthView.setVisibility(View.VISIBLE);
			m_timer = new Timer();
			m_wrapper.StartStopSigStrMeas(true, m_idxManualInsLNB);
			m_timer.schedule(new UpdateSignalQuality(), 0, 5000);
			m_isSigCheckInProgress = true;
		}
		Log.d(TAG, "startSignalStrengthCheck exit");
	}

	private void stopSignalStrengthCheck()
	{
		Log.d(TAG, "stopSignalStrengthCheck entry");
		if (m_isSigCheckInProgress)
		{
			m_timer.cancel();
			m_timer.purge();
			m_wrapper.StartStopSigStrMeas(false, m_idxManualInsLNB);
			m_isSigCheckInProgress = false;

		}
		Log.d(TAG, "stopSignalStrengthCheck exit");
	}

	@Override
	public void update(Observable observable, Object data)
	{
		Log.d(TAG, "update: action " + ((NotificationInfoObject) data).actionID + ", message " + ((NotificationInfoObject) data).message);
		final int l_eventID = ((NotificationInfoObject) data).actionID;
		final Activity l_activity = (Activity) m_context;
		switch (l_eventID)
		{
			case EventIDs.SERVICE_SCAN_UPDATE: // channels found
				Log.d(TAG, "SERVICE_SCAN_UPDATE");
				l_activity.runOnUiThread(new Runnable()
				{
					@Override
					public void run()
					{
						onChannelFound();
						m_wrapper.setTVMplSurface(m_wrapper.getEuinstallerSatSurface().getSurface());// search
						// is
						// complete
					}
				});
				break;
			case EventIDs.SERVICE_SCAN_COMPLETE:// sorting done
				Log.d(TAG, "SERVICE_SCAN_COMPLETE");
				m_wrapper.commitDatabaseToTvProvider(m_wrapper.INSTALL_TYPE_SRT);
				break;
			case EventIDs.MANUAL_INSTALL_FAILED:
				Log.d(TAG, "MANUAL_INSTALL_FAILED");
				l_activity.runOnUiThread(new Runnable()
				{
					@Override
					public void run()
					{
						onSearchFail();
					}
				});

				break;
			case EventIDs.COMMIT_TVPROVIDER_FINISHED:
				Log.d(TAG, "COMMIT_TVPROVIDER_FINISHED");
				startLogoAssociation();
				Log.d(TAG, "Logo association triggered");
				break;
		}

	}

	@Override
	public void onClick(View v)
	{
		switch (v.getId())
		{
			case R.id.button_dtr_search:
				if (m_toggleButton == TOGGLE_BUTTON_SEARCH)
				{
					m_wrapper.SetFreq(getValidFrequency());
					hideResults();
					m_resultLayout.setVisibility(View.INVISIBLE);
					stopSignalStrengthCheck();
					showProgressBar(true);
					m_wrapper.SetScanStarts(MwDataTypes.IHsvSatelliteInstallation_InstallationManual, m_idxManualInsLNB);
					sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
				} else
				{
					m_isStoreInProgress = true;
					if (m_wrapper.isDTRStoreOptionAvailable() == true)
					{
						showProgressBar(false);
						m_wrapper.SetServiceStore();
					}
				}
				break;

			case R.id.button_dtr_done:
				Log.d(TAG, "ok on done/cancel");
				boolean l_isInstallComplete = true;
				if (m_toggleButton == TOGGLE_BUTTON_STORE)
				{
					Log.d(TAG, "Ok on search without selecting store");
					m_wrapper.SetScanStops();
					sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_STOPPED");
					l_isInstallComplete = false;
				}
				if (m_wrapper.isTuner2Active())
				{
					Log.d(TAG, "Tuner2 active");
					l_isInstallComplete = false;
				}
				if (m_wrapper.isDTRStoreOptionAvailable() == false)
				{
					Log.d(TAG,"Tune to Default channel");
					l_isInstallComplete = false;
				}
				onScreenExit(false);
				//m_wrapper.switchToFirstAvailableChannel(l_isInstallComplete);
				//((Activity)m_context).finish();
				instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
				
				break;

			/*case R.id.button_dtr_previous:
				Log.d(TAG, "ok on previous button");
				if (m_toggleButton == TOGGLE_BUTTON_STORE)
				{
					m_wrapper.SetScanStops();
					sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_STOPPED");
				}
				onScreenExit(true);
				break;*/

			default:
				break;

		}

	}

	private int getValidFrequency()
	{
		int l_freq = getDisplayedFrequency();
		if (l_freq < m_minFreq)
		{
			l_freq = m_minFreq;
		}
		if (l_freq > m_maxFreq)
		{
			l_freq = m_maxFreq;
		}
		setDisplayedFrequency(l_freq);
		Log.d(TAG, "getValidFrequency returning " + l_freq);
		return l_freq;
	}

	private void sendIntent(String p_action)
	{
		Log.d(TAG, "sendIntent " + p_action);
		Intent l_intent = new Intent(p_action);
		l_intent.putExtra("InstallMode", "DTR");
		m_context.sendBroadcast(l_intent);
	}

	private void startLogoAssociation()
	{
		Log.d(TAG, "startLogoAssiciation");
		Intent i = new Intent("org.droidtv.tvcontentprovider.LogoService");
		(m_context).bindService(i, mConnection, Context.BIND_AUTO_CREATE);
	}

	private ServiceConnection mConnection = new ServiceConnection()
	{
		@Override
		public void onServiceConnected(ComponentName name, IBinder service)
		{
			Log.d(TAG, "ILogoAssociationControl called");
			m_logoAssoInt = ILogoAssociationControl.Instance.asInterface(service);
			if (m_logoAssoInt != null)
			{
				Log.d(TAG, "logoAssoInt is not null");
				m_logoAssoInt.registerListenerCallback(m_listener);
				m_logoAssoInt.StartLogoAssociation(ILogoAssociationControl.MEDIUM_SATELLITE);

			} else
			{
				Log.d(TAG, "NULL logoAssoInt found");
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name)
		{
			// TODO Auto-generated method
			// stub

		}
	};

	public class ListenerImpl extends ILogoAssociationListener
	{

		@Override
		public void onLogoAssociationStateChanged(int state)
		{
			Log.d(TAG, "onLogoAssociationStateChanged called with State:" + state);
			if (state == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_COMPLETE)
			{
				Log.d(TAG, "Logo Association complete received");
				try
				{
					(m_context).unbindService(mConnection);
				} catch (Exception ex)
				{
					Log.d(TAG, "Exception caught while unbinding service org.droidtv.tvcontentprovider.LogoService");
				}

				onLogoAssociationComplete();
			}
		}

	}

	private void onLogoAssociationComplete()
	{
		Activity l_activity = (Activity) m_context;
		l_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				onStore();
				sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_COMPLETE");
				m_progressWindow.setOnDismissListener(null);
				m_progressWindow.dismiss();
			}
		});

		msettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 1);

	}

	class UpdateSignalQuality extends TimerTask
	{

		@Override
		public void run()
		{
			Log.d(TAG, "in timer task to UpdateSignalQuality");
			int l_signalQuality = m_wrapper.GetSignalQuality(m_idxManualInsLNB);
			int l_signalStrength = m_wrapper.GetSignalStrength(m_idxManualInsLNB);

			final int ui_signalQuality = l_signalQuality;
			final int ui_signalStrength = l_signalStrength;
			Activity l_activity = (Activity) m_context;
			l_activity.runOnUiThread(new Runnable()
			{

				@Override
				public void run()
				{
					m_sigStrengthView.setValue(ui_signalStrength);
					m_sigQualityView.setValue((int) ui_signalQuality);
					String l_qualityString = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_GOOD);

					if (ui_signalQuality <= 33)
					{
						l_qualityString = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_POOR);
					} else if (ui_signalQuality <= 66)
					{
						l_qualityString = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_FAIR);
					}

					m_sigQuality_txtVw.setText(l_qualityString);
					m_sigStrength_txtVw.setText(" " + String.valueOf(ui_signalStrength));
				}
			});

		}
	};

	private void onScreenExit(boolean pMoveToPrev)
	{
		Log.d(TAG, "onScreenExit entry");
		stopSignalStrengthCheck();
		m_wrapper.setTVMplSurface(null);
		m_wrapper.exitNonInteruptableMode();
        m_wrapper.SetScanStops();
		//getSettingsManager().scrollToPrevPage();
		NotificationHandler.getInstance().unRegisterForNotification(this);
		m_isCollapsed = false;
		m_progressWindow.setOnDismissListener(null);
		m_progressWindow.dismiss();
		//m_colourKeyManager.enableBlueKey();
		//getSettingsManager().updatePanel_2(loadCustomView());
		if (pMoveToPrev){
			if(m_wrapper.getSettingsActivity() instanceof SatelliteSettingsActivity){
				((SatelliteSettingsActivity) m_wrapper.getSettingsActivity()).showHideColorKey(true);
			}
			getMenuBuilder().removeFocus();
		}
		Log.d(TAG, "onScreenExit exit");
	}

	@Override
	public void onInputPickerValueChanged(int arg0)
	{
		Log.d(TAG, "onInputPickerValueChanged");
		if (m_toggleButton != TOGGLE_BUTTON_SEARCH)
		{
			m_toggleButton = TOGGLE_BUTTON_SEARCH;
			m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
			m_wrapper.SetScanStops();
		}

	}

	@Override
	public void onInputPickerValueConfirm(int p_currValue)
	{
		Log.d(TAG, "onInputPickerValueConfirm");
		onKeyRight();

	}

	@Override
	public void onInputPickerValueEntered(int p_currValue)
	{
		Log.d(TAG, "onInputPickerValueEntered");
		if (m_toggleButton != TOGGLE_BUTTON_SEARCH)
		{
			m_toggleButton = TOGGLE_BUTTON_SEARCH;
			m_buttonSearch.setText(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH);
			m_wrapper.SetScanStops();
		}
		onKeyRight();

	}

}
