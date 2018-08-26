package org.droidtv.euinstallersat.wizard.screen;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.CONNECTION_TYPE;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.util.SignalIndicatorView;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.InstallationCancelDialog;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

public class PreScan extends WizardStep implements SatelliteScreen
{

	private static final String TAG = PreScan.class.getName();
	private Context m_context;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper m_wrapper;
	private SatelliteScreen mSatelliteScreen;
	private View m_view;
	
	
	private int m_lnbCount = 0;
	private int m_idxCurScannedLNB = -1;
	
	private SignalIndicatorView[] m_sigQualityImageArray;
	private SignalIndicatorView[] m_sigStrengthImageArray;
	
	private TextView[] m_sigQualityValueArray;
	private TextView[] m_sigQualityArray;
	
	private TextView[] m_sigStrengthValueArray;
	private TextView[] m_sigStrengthArray;
	
	private TextView[] m_lnbTextArray;
	
	private String[] m_satNameArray;
	private ArrayList<Integer> m_validLNBIdxArray;
	private Timer m_timer;
	
	
	private ProgressBar[] m_progBarArray;
	
	private int MAX_LNB_COUNT = 4;
	private int m_idxSigStrengthCheckLNB;
	private boolean m_isRecognisedSatFound;
	private boolean m_isSigStrengthInProgress;
	
	private OnClickListener m_cancelButtonListener;
	private OnClickListener m_installButtonListener;
	private OnClickListener mSearchAgainButtonistener;

	public PreScan(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		m_context = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		mSatelliteScreen = this;
		loadLayout(context);
	}

	public PreScan(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public PreScan(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		m_view = inflater.inflate(R.layout.prescan, null);
		initSigQualityArray();
		initSigStrengthArray();
		initLnbInfoArray();
		initButtonListeners();
		initSatNameArray();
		m_validLNBIdxArray = new ArrayList<Integer>();
		addView(m_view);
		
		String l_btnNext_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);
		
		setButton1(l_btnCancel_txt, m_cancelButtonListener, View.VISIBLE);
		setButton2(l_btnPrev_txt, null, View.INVISIBLE);
		setButton3(l_btnNext_txt, null, View.INVISIBLE);
		String l_hint_txt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_PRESCAN);
		setHintText(l_hint_txt);
		
	}
	
	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.droidtv.satelliteinstallation.util.SatelliteScreen#screenIntialization
	 * () Called when the screen is visible
	 */
	@Override
	public void screenIntialization()
	{
		Log.i(TAG, "<< PreScan screenIntialization called >>");
		(NotificationHandler.getInstance()).registerForNotification(mSatelliteScreen);
		m_timer = new Timer();
		m_lnbCount = m_wrapper.getLNBCount();
		m_wrapper.setInstallMode(NativeAPIWrapper.INSTALL_MODE_AUTO);
		m_wrapper.sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
		
		intialiseUI();
		initPrescan();
		scanNextLNB();
		enableWaitingAnimation(true);
	}
	
	private void intialiseUI() {
		Log.d(TAG, "intialiseUI");
		int l_idx;
		for (l_idx = 0; l_idx < MAX_LNB_COUNT; l_idx++) {
			m_progBarArray[l_idx].setVisibility(GONE);
			m_progBarArray[l_idx].setProgress(0);
			m_lnbTextArray[l_idx].setText(m_satNameArray[l_idx]);
			m_sigQualityValueArray[l_idx].setText("0");
			m_sigQualityImageArray[l_idx].setValue(0);
			m_sigStrengthValueArray[l_idx].setText("0");
			m_sigStrengthImageArray[l_idx].setValue(0);
			m_lnbTextArray[l_idx].setVisibility(INVISIBLE);
			showHideSigStrengthIndicator(l_idx, false);
		}

		setHintText(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_PRESCAN));
		setButton2(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), null, View.INVISIBLE);
		setButton3(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT), null, View.INVISIBLE);
	}
	
	private void initSigQualityArray()
	{
		Log.d(TAG, "initSigQualityArray entry");
		
		m_sigQualityImageArray = new SignalIndicatorView[MAX_LNB_COUNT];
		m_sigQualityValueArray = new TextView[MAX_LNB_COUNT];
		m_sigQualityArray = new TextView[MAX_LNB_COUNT];
		
		m_sigQualityImageArray[0] = (SignalIndicatorView) m_view.findViewById(R.id.sat1signalquality);
		m_sigQualityImageArray[1] = (SignalIndicatorView) m_view.findViewById(R.id.sat2signalquality);
		m_sigQualityImageArray[2] = (SignalIndicatorView) m_view.findViewById(R.id.sat3signalquality);
		m_sigQualityImageArray[3] = (SignalIndicatorView) m_view.findViewById(R.id.sat4signalquality);
		
		m_sigQualityValueArray[0] = (TextView) m_view.findViewById(R.id.sat1qualityval);
		m_sigQualityValueArray[1] = (TextView) m_view.findViewById(R.id.sat2qualityval);
		m_sigQualityValueArray[2] = (TextView) m_view.findViewById(R.id.sat3qualityval);
		m_sigQualityValueArray[3] = (TextView) m_view.findViewById(R.id.sat4qualityval);
		
		m_sigQualityArray[0] = (TextView) m_view.findViewById(R.id.sat1quality);
		m_sigQualityArray[1] = (TextView) m_view.findViewById(R.id.sat2quality);
		m_sigQualityArray[2] = (TextView) m_view.findViewById(R.id.sat3quality);
		m_sigQualityArray[3] = (TextView) m_view.findViewById(R.id.sat4quality);
		
		int[] l_qualityIdArray = {org.droidtv.ui.tvwidget2k15.R.drawable.signal_quality_01,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_quality_02,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_quality_03,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_quality_04};
		int[] l_qualityValueArray = {25, 50, 75, 100};
		
		
		for(int l_idx = 0; l_idx < MAX_LNB_COUNT; l_idx ++)
		{
			m_sigQualityImageArray[l_idx].init(l_qualityIdArray, l_qualityValueArray);
			m_sigQualityValueArray[l_idx].setText("0");
			//m_sigQualityImageArray[l_idx].setDefaultImage(R.drawable.stat_sys_signal1_4);
		}
		
		Log.d(TAG, "initSigQualityArray exit");
		
	}
	
	private void initSigStrengthArray()
	{
		Log.d(TAG, "initSigStrengthArray entry");
		
		m_sigStrengthImageArray = new SignalIndicatorView[MAX_LNB_COUNT];
		m_sigStrengthValueArray = new TextView[MAX_LNB_COUNT];
		m_sigStrengthArray = new TextView[MAX_LNB_COUNT];
		
		m_sigStrengthImageArray[0] = (SignalIndicatorView) m_view.findViewById(R.id.sat1signalstrength);
		m_sigStrengthImageArray[1] = (SignalIndicatorView) m_view.findViewById(R.id.sat2signalstrength);
		m_sigStrengthImageArray[2] = (SignalIndicatorView) m_view.findViewById(R.id.sat3signalstrength);
		m_sigStrengthImageArray[3] = (SignalIndicatorView) m_view.findViewById(R.id.sat4signalstrength);
		
		m_sigStrengthValueArray[0] = (TextView) m_view.findViewById(R.id.sat1signalstrengthval);
		m_sigStrengthValueArray[1] = (TextView) m_view.findViewById(R.id.sat2signalstrengthval);
		m_sigStrengthValueArray[2] = (TextView) m_view.findViewById(R.id.sat3signalstrengthval);
		m_sigStrengthValueArray[3] = (TextView) m_view.findViewById(R.id.sat4signalstrengthval);
		
		m_sigStrengthArray[0] = (TextView) m_view.findViewById(R.id.sat1signalstrengthText);
		m_sigStrengthArray[1] = (TextView) m_view.findViewById(R.id.sat2signalstrengthText);
		m_sigStrengthArray[2] = (TextView) m_view.findViewById(R.id.sat3signalstrengthText);
		m_sigStrengthArray[3] = (TextView) m_view.findViewById(R.id.sat4signalstrengthText);
		
		int[] l_idArray = {org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_01,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_02,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_03,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_04,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_05,
				org.droidtv.ui.tvwidget2k15.R.drawable.signal_strength_06};
		int[] l_valueArray = {17, 34, 51, 68, 85, 100};
		
		for(int l_idx = 0; l_idx < MAX_LNB_COUNT; l_idx ++)
		{
			m_sigStrengthImageArray[l_idx].init(l_idArray, l_valueArray);
			m_sigStrengthImageArray[l_idx].setValue(0);
			m_sigQualityValueArray[l_idx].setText("0");
			m_sigStrengthValueArray[l_idx].setText("0");
		}
		
		Log.d(TAG, "initSigStrengthArray exit");
	}
	
	private void initLnbInfoArray()
	{
		Log.d(TAG, "initLnbInfoArray entry");
		
		m_lnbTextArray = new TextView[MAX_LNB_COUNT];
		m_progBarArray = new ProgressBar[MAX_LNB_COUNT];
		
		m_lnbTextArray[0] = (TextView) m_view.findViewById(R.id.satellitelnb1text);
		m_lnbTextArray[1] = (TextView) m_view.findViewById(R.id.satellitelnb2text);
		m_lnbTextArray[2] = (TextView) m_view.findViewById(R.id.satellitelnb3text);
		m_lnbTextArray[3] = (TextView) m_view.findViewById(R.id.satellitelnb4text);
		
		m_progBarArray[0] = (ProgressBar) m_view.findViewById(R.id.lnb1progressbar);
		m_progBarArray[1] = (ProgressBar) m_view.findViewById(R.id.lnb2progressbar);
		m_progBarArray[2] = (ProgressBar) m_view.findViewById(R.id.lnb3progressbar);
		m_progBarArray[3] = (ProgressBar) m_view.findViewById(R.id.lnb4progressbar);
		
		Log.d(TAG, "initLnbInfoArray exit");
		
	}
	
	private void initSatNameArray()
	{
		Log.d(TAG, "initSatNameArray entry");
		
		m_satNameArray = new String[MAX_LNB_COUNT];
		m_satNameArray[0] = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB1);
		m_satNameArray[1] = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB2);
		m_satNameArray[2] = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB3);
		m_satNameArray[3] = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB4);
		
		Log.d(TAG, "initSatNameArray exit");
	}
	
	private void initButtonListeners()
	{
		Log.d(TAG, "initButtonListeners entry");
		m_cancelButtonListener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				if(m_isSigStrengthInProgress)
				{
					m_wrapper.resetInstallation();
				}
				else
				{
					m_wrapper.SetScanStops();
				}
				//sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_STOPPED");
				mSatelliteWizard.launchPreviousScren();
			}
		};
		
		m_installButtonListener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				
				boolean l_isMduDetected = m_wrapper.GetIsMDUDetected();
				
				//m_wrapper.SetBouquetIndex(0);
				if(m_isRecognisedSatFound && !l_isMduDetected)
				{
					if (m_validLNBIdxArray.size() == 1)
					{
						int l_lnbIdx = m_validLNBIdxArray.get(0);
						int l_satId = m_wrapper.GetSatDetectedID(l_lnbIdx);
						
						if (l_satId == MwDataTypes.EUTELSAT_5_W)
						{
							Log.d(TAG,"EUTELSAT_5_W");
							/*CR:RMCR:2884
							    :Remove Legagcy Fransat Installation
							*/
							m_wrapper.SetBouquetIndex(0);
							mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.INSTALLSCREEN, getScreenName());
							
						}
						else if(m_wrapper.getTotalPackagesFound() == 1)
						{
							Log.d(TAG,"No Packages Found:Only unsorted available:Direct unsorted installation");
							m_wrapper.SetBouquetIndex(0);
							mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.INSTALLSCREEN, getScreenName());
							
						}else
						{
							Log.d(TAG,"Package Selection 1");
							mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.PACKAGE_SELECTION, getScreenName());
						}
					}
					else
					{	
						Log.d(TAG,"Package Selection 2");
						mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.PACKAGE_SELECTION, getScreenName());
					}
				} else if(m_wrapper.isOperatorProfileSupported()) {
					// cam based installation 
					// populate cam packages & move to package selection screen
					
					Log.d(TAG,"Package Selection 3");
					mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.PACKAGE_SELECTION, getScreenName());
				} else {
					Log.d(TAG,"Install Screen ");
					/* Package identification needed. Otherwise previous selection will be retained */
					m_wrapper.IdentifyPackagesAvailable();
					m_wrapper.SetBouquetIndex(0);
					mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.INSTALLSCREEN, getScreenName());
				}
				
				
			}
		};
		
		mSearchAgainButtonistener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				stopSignalStrengthCheck();
				intialiseUI();
				initPrescan();
				scanNextLNB();
				enableWaitingAnimation(true);
				
			}
		};
		
		Log.d(TAG, "initButtonListeners exit");
		
	}
	
	private void initPrescan() {
		Log.d(TAG, "initPrescan entry");
		m_idxCurScannedLNB = -1;
		m_isRecognisedSatFound = false;
		m_idxSigStrengthCheckLNB = 0;
		m_validLNBIdxArray.clear();
		m_isSigStrengthInProgress = false;
		Log.d(TAG, "initPrescan exit");
	}
	
	private void scanNextLNB() {
		Log.d(TAG, "scanNextLNB entry");
		Activity activity = (Activity) m_context;
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				m_idxCurScannedLNB++;
				if (m_idxCurScannedLNB == m_lnbCount) {
					onScanComplete();
				} else {
					// trigger prescan for LNB
					m_lnbTextArray[m_idxCurScannedLNB].setVisibility(VISIBLE);
					m_progBarArray[m_idxCurScannedLNB].setVisibility(VISIBLE);
					m_wrapper.SetScanStarts((MwDataTypes.IHsvSatelliteInstallation_InstallationPreScan | MwDataTypes.IHsvSatelliteInstallation_InstallationServiceScan), m_idxCurScannedLNB);
				}
			}
		});

		Log.d(TAG, "scanNextLNB exit");
	}
	
	private void onScanComplete()
	{
		Log.d(TAG, "onScanComplete entry");
		enableWaitingAnimation(false);
		if(m_validLNBIdxArray.size() > 0)
		{
			setHintText(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_PRESCAN_RESULT));
			setButton3(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_INSTALL), m_installButtonListener, View.VISIBLE);
			setButton3focussed();
			startSignalStrengthCheck();
		}
		else
		{
			setHintText(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_PRESCAN_NO_SATELLITES_FOUND));
		}
		
		String l_btnSearchAgainTxt = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SEARCH_AGAIN);
		setButton2(l_btnSearchAgainTxt, mSearchAgainButtonistener, View.VISIBLE);
		Log.d(TAG, "onScanComplete exit");
	}
	
	private void startSignalStrengthCheck()
	{
		Log.d(TAG, "startSignalStrengthCheck entry");
		int l_idx;
		int l_numLNBs  = m_validLNBIdxArray.size();
		int l_lnbIdx;
		m_isSigStrengthInProgress = true;
		m_timer = new Timer();
			
		for ( l_idx = 0; l_idx < l_numLNBs; l_idx ++ )
		{
			l_lnbIdx  = m_validLNBIdxArray.get(l_idx);
			showHideSigStrengthIndicator(l_lnbIdx, true);
			m_sigQualityImageArray[l_lnbIdx].setValue(0);
			m_sigStrengthImageArray[l_lnbIdx].setValue(0);
		}
		
		m_idxSigStrengthCheckLNB = 0;	
		m_wrapper.StartStopSigStrMeas(true, m_validLNBIdxArray.get(m_idxSigStrengthCheckLNB));
		m_timer.schedule(new UpdateSignalStrength(), 5000, 5000);
		Log.d(TAG, "startSignalStrengthCheck exit");
	}
	
	private void stopSignalStrengthCheck()
	{
		Log.d(TAG, "stopSignalStrengthCheck entry");
		if (m_isSigStrengthInProgress)
		{
			m_isSigStrengthInProgress = false;
			m_timer.cancel();
			m_timer.purge();
			m_wrapper.StartStopSigStrMeas(false, m_validLNBIdxArray.get(m_idxSigStrengthCheckLNB));
			m_idxSigStrengthCheckLNB = 0;
		}
		Log.d(TAG, "stopSignalStrengthCheck exit");
	}
	
	
	private void showHideSigStrengthIndicator( int p_lnbIdx, boolean p_isVisible )
	{
		Log.d(TAG, "showHideSigStrengthIndicator entry");
		final int l_idx = p_lnbIdx;
		final boolean l_isVisible = p_isVisible;
		Activity l_activity = (Activity) m_context;
		l_activity.runOnUiThread(new Runnable()
		{
			
			@Override
			public void run()
			{
				if(l_isVisible)
				{
					m_sigQualityImageArray[l_idx].setVisibility(VISIBLE);
					m_sigQualityValueArray[l_idx].setVisibility(VISIBLE);
					m_sigStrengthImageArray[l_idx].setVisibility(VISIBLE);
					m_sigStrengthValueArray[l_idx].setVisibility(VISIBLE);
					m_sigStrengthArray[l_idx].setVisibility(VISIBLE);
					m_sigQualityArray[l_idx].setVisibility(VISIBLE);
				}
				else
				{
					m_sigQualityImageArray[l_idx].setVisibility(INVISIBLE);
					m_sigQualityValueArray[l_idx].setVisibility(INVISIBLE);
					m_sigStrengthImageArray[l_idx].setVisibility(INVISIBLE);
					m_sigStrengthValueArray[l_idx].setVisibility(INVISIBLE);
					m_sigStrengthArray[l_idx].setVisibility(INVISIBLE);
					m_sigQualityArray[l_idx].setVisibility(INVISIBLE);
				}

			}

		});
		Log.d(TAG, "showHideSigStrengthIndicator exit");
	}



	/*
	 * (non-Javadoc)
	 * 
	 * @see java.util.Observer#update(java.util.Observable, java.lang.Object)
	 * Call back method from the nativeapiwrapper Update the UI based on the
	 * events triggered from the wrapper
	 * 
	 * @Params Observable,Object
	 */
	@Override
	public void update(Observable observable, Object data)
	{
		final int eventID = ((NotificationInfoObject) data).actionID;
		Log.i(TAG, "eventID:" + eventID);
		switch (eventID)
		{
			case EventIDs.PRESCAN_SUCCESS:
				Log.d(TAG,"PRESCAN_SUCCESS");
				updateLNBInfo(m_idxCurScannedLNB, true);
				scanNextLNB();
				break;
			case EventIDs.PRESCAN_FAIL:
				Log.d(TAG,"PRESCAN_FAIL");
				updateLNBInfo(m_idxCurScannedLNB, false);
				scanNextLNB();
				break;
			case EventIDs.PRESCAN_UPDATE:
				Log.d(TAG,"PRESCAN_UPDATE");
				updateProgressBar(m_idxCurScannedLNB, m_wrapper.GetPreScanStatus(m_idxCurScannedLNB));
				break;
			
		}
	}

	
	/*
	 * Updating the Lnb1 text based on mw output
	 */
	private void updateLNBInfo(final int p_lnbIdx, final boolean p_isScanSuccesful)
	{
		Log.i(TAG, "updateLNBInfo called p_lnbIdx " + String.valueOf(p_lnbIdx));
		Activity l_activity = (Activity) m_context;
		boolean l_isDuplicate = false;
		String l_satName = "";
		boolean l_isRecognisedSatellite = false;
		if(p_isScanSuccesful)
		{
			Log.d(TAG,"Scan succesfull");
			l_satName = m_wrapper.GetSatelliteName(p_lnbIdx);
			l_isDuplicate = m_wrapper.IsSatelliteDuplicate(p_lnbIdx);
			l_isRecognisedSatellite = (m_wrapper.GetIsRecognisedSatellite(p_lnbIdx));
		}
		
		final boolean ui_isDuplicate = l_isDuplicate;
		final String ui_satName = l_satName;
		final boolean ui_isRecognisedSatellite = l_isRecognisedSatellite;
		
		l_activity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{
				if(p_isScanSuccesful)
				{
					if(ui_isDuplicate)
					{
						String l_duplicateStr = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_DUPLICATE);
						m_lnbTextArray[p_lnbIdx].setText(m_satNameArray[p_lnbIdx] + "- " + l_duplicateStr);
						//TODO : show satellite name in the next line
					}
					else if(ui_isRecognisedSatellite)
					{
						m_isRecognisedSatFound = true;
						m_lnbTextArray[p_lnbIdx].setText(m_satNameArray[p_lnbIdx] + "- " + ui_satName);
					}
					if(!ui_isDuplicate)
					{
						m_validLNBIdxArray.add(p_lnbIdx);
					}
				}
				else
				{
					String noneStr = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_SATELLITE_NONE);
					String skipStr = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_SKIPPED);
					if((m_wrapper.getConnectionTypeFromMW() == CONNECTION_TYPE.DISEQC_1_0) || (m_wrapper.getConnectionTypeFromMW() == CONNECTION_TYPE.DISEQC_MINI)){
						if(m_wrapper.getPrescanForLNBs()[p_lnbIdx] == false){
			    			Log.d(TAG,"Skip LNB");
			    			m_lnbTextArray[p_lnbIdx].setText(m_satNameArray[p_lnbIdx] + " - "+ skipStr);
						}else{
							m_lnbTextArray[p_lnbIdx].setText(m_satNameArray[p_lnbIdx] + " - "+ noneStr);
						}
					}else{
						// existing default case for single/Universal/Unicable LNb's
						m_lnbTextArray[p_lnbIdx].setText(m_satNameArray[p_lnbIdx] + "- "+ noneStr);
					}
				}
				m_progBarArray[p_lnbIdx].setVisibility(INVISIBLE);
				if( p_lnbIdx < (m_lnbCount-1))
				{
					Log.d(TAG,"showing next item");
					m_lnbTextArray[p_lnbIdx+1].setVisibility(VISIBLE);
					m_progBarArray[p_lnbIdx+1].setVisibility(VISIBLE);
				}
			}

		});
	}

	
	
	/*
	 * Updating the progress bar percentage
	 * 
	 * @Param int searchingPercentage
	 */
	private void updateProgressBar(final int p_lnbIdx, final int p_progress)
	{
		Activity l_activity = (Activity) m_context;
		l_activity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{
				m_progBarArray[p_lnbIdx].setProgress(p_progress);
			}
		});
	}
	
	

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.droidtv.satelliteinstallation.util.SatelliteScreen#setInstance(org
	 * .droidtv.satelliteinstallation.SatelliteWizard)
	 */
	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.droidtv.satelliteinstallation.util.SatelliteScreen#getScreenName()
	 */
	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.PRESCAN;
	}

	
	
	 @Override
    public boolean onKey(View view, int keyCode, KeyEvent event)
    {
		 boolean l_ret = false;
		 if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
		 {
			super.onKey(view, keyCode, event); 
			l_ret = true;
		 }
		 else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
		 {
			 super.onKey(view, keyCode, event); 
			 l_ret = true; 
		 }
		 else if (((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) && event.getAction() == KeyEvent.ACTION_UP)
         {
			InstallationCancelDialog l_dialog = new InstallationCancelDialog(m_context,mSatelliteWizard);
    		l_dialog.setNextScreen(ScreenRequest.PRESCAN, ScreenRequest.STARTSCREEN);
    		l_dialog.showDialog();
    		l_ret = true;
         }
		 
		 return l_ret;
    }

	class UpdateSignalStrength extends TimerTask
	{

		@Override
		public void run()
		{
			Log.d(TAG, "in timer task to UpdateSignalQuality");
			Activity l_activity = (Activity) m_context;
			int l_curLNB = m_validLNBIdxArray.get(m_idxSigStrengthCheckLNB);
			final int l_signalStrength = m_wrapper.GetSignalStrength(l_curLNB );
			final int l_signalQuality = m_wrapper.GetSignalQuality(l_curLNB );
			final int l_idx = l_curLNB;
			l_activity.runOnUiThread(new Runnable()
			{
				@Override
				public void run()
				{
					m_sigQualityValueArray[l_idx ].setText(String.valueOf(l_signalQuality ));
					m_sigQualityImageArray[l_idx].setValue(l_signalQuality);
					m_sigStrengthValueArray[l_idx ].setText(String.valueOf(l_signalStrength ));
					m_sigStrengthImageArray[l_idx].setValue(l_signalStrength);					
				}
			});
			m_wrapper.StartStopSigStrMeas(false, l_curLNB);
			m_idxSigStrengthCheckLNB++;
			if (m_idxSigStrengthCheckLNB == m_validLNBIdxArray.size())
			{
				m_idxSigStrengthCheckLNB = 0;
			}
			l_curLNB = m_validLNBIdxArray.get(m_idxSigStrengthCheckLNB);
			m_wrapper.StartStopSigStrMeas(true, l_curLNB);

		}
	};

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		stopSignalStrengthCheck();
		NotificationHandler.getInstance().unRegisterForNotification(this);
	}



}
