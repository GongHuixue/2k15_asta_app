package org.droidtv.euinstallersat.wizard.screen;

import java.util.HashMap;
import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.SelectedMode;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.euinstallersat.model.mwapi.SatInstaller.OpPresentStatus;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class CamSelection extends WizardStep implements SatelliteScreen {

	private static final String TAG = CamSelection.class.getName();
	private Context mContext;
	private RadioSelector mRadioSelector;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper nwrap;
	public static int mSelectedItem = 1;
	private final int IDX_FROM_CAM = 0;
	private final int IDX_ADVANCED_INSTALLATION = 1;
	private TimerTask localOPProgTimerTask  = null;
    private Timer     localOPProgTimer      = null;

	public CamSelection(Context context, AttributeSet attrSet, int defStyle) {
		super(context, attrSet, defStyle);
		mContext = context;
		nwrap = NativeAPIWrapper.getInstance();
		loadLayout(context);
	}

	public CamSelection(Context context, AttributeSet attrSet) {
		this(context, attrSet, 0);
	}

	public CamSelection(Context context) {
		this(context, null, 0);
	}

	private void loadLayout(Context context) {
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		addView(view);
		mRadioSelector = (RadioSelector) view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		mRadioSelector.setOnKeyListener(this);
		OnClickListener buttonCancel_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				stopOPCAMDetection();
				mSatelliteWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonPrevious_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				stopOPCAMDetection();
				mSatelliteWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonNext_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				int selectedPosition = mRadioSelector.getCheckedItemPosition();
				stopOPCAMDetection();
				if (selectedPosition == 0) {
					// cam based installation
					nwrap.setUserSelectedMode(SelectedMode.FROM_THE_CAM);
					
					if (nwrap.isTwoTunerSupported()) {
						// AN-78512
						mSatelliteWizard.launchScreen(ScreenRequest.DUAL_TUNER, getScreenName());
					}else{
						// cam based installation
						mSatelliteWizard.launchScreen(ScreenRequest.CAM_INSTALLATION, getScreenName());
					}
				} else {
					// normal rf installation
					nwrap.setUserSelectedMode(SelectedMode.ADVANCED);
					if (nwrap.isTwoTunerSupported()) {
						mSatelliteWizard.launchScreen(ScreenRequest.DUAL_TUNER, getScreenName());
					} else {
						mSatelliteWizard.launchScreen(ScreenRequest.STARTSCREEN, getScreenName());
					}
				}
			}
		};

		mRadioSelector.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View view, int selectedItem, long arg3) {
				Log.d(TAG, "selectedItem:" + selectedItem);
				setButton3focussed();
			}

		});
		

		String l_btnNext_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);

		setButton1(l_btnCancel_txt, buttonCancel_Listener, VISIBLE);
		setButton2(l_btnPrev_txt, buttonPrevious_Listener, VISIBLE);
		setButton3(l_btnNext_txt, buttonNext_Listener, VISIBLE);
		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_FROM_THE_CAM));
	}

	@Override
	public boolean onKey(View view, int keyCode, KeyEvent event) {

		Log.d(TAG, "OnKey");
		boolean l_isKeyHandled = false;
		if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN) {
			Log.d(TAG, "KEYCODE_DPAD_RIGHT");
			if (mRadioSelector == view) {
				setButton3focussed();
			} else {
				super.onKey(view, keyCode, event);
			}
			l_isKeyHandled = true;
		} else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN) {
			Log.d(TAG, "KEYCODE_DPAD_LEFT");
			if (mRadioSelector == view) {
				setButton1focussed();
			} else {
				super.onKey(view, keyCode, event);
			}
			l_isKeyHandled = true;
		} else if (keyCode == KeyEvent.KEYCODE_DPAD_UP && event.getAction() == KeyEvent.ACTION_DOWN) {
			Log.d(TAG, "KEYCODE_DPAD_UP");
			if (mRadioSelector != view) {
				int l_selIdx = mRadioSelector.getCheckedItemPosition();
				mRadioSelector.setSelection(l_selIdx);
				mRadioSelector.requestFocus();
			}
		}
		Log.d(TAG, "OnKey returning " + l_isKeyHandled);
		return l_isKeyHandled;

	}
	
	private void triggerOPCAMDetectionIfRequired(){
		stopOPCAMDetection();
		Log.d(TAG,"triggerOPCAMDetectionIfRequired");
		if(OpPresentStatus.NOT_PRESENT == nwrap.getSatInstaller(TunerName.TUNER1).getOpPresenceStatus()){
			// no need to start timer
			checkAndUpdateControlability(OpPresentStatus.NOT_PRESENT);
		}else if(OpPresentStatus.PRESENT == nwrap.getSatInstaller(TunerName.TUNER1).getOpPresenceStatus()){
			// no need to start timer
			checkAndUpdateControlability(OpPresentStatus.PRESENT);
		}else if(OpPresentStatus.WAITING == nwrap.getSatInstaller(TunerName.TUNER1).getOpPresenceStatus()){
			checkAndUpdateControlability(OpPresentStatus.WAITING);
			// start timer detection
			// start the timer
			localOPProgTimerTask = new TimerTask() {
				int secCount = 0;
				@Override
				public void run() {
					secCount++;
					/*if(secCount == 5){
						checkAndUpdateControlability(OpPresentStatus.NOT_PRESENT);
						stopOPCAMDetection();
					}*/
					if(OpPresentStatus.WAITING != nwrap.getSatInstaller(TunerName.TUNER1).getOpPresenceStatus() ){
						stopOPCAMDetection();
						checkAndUpdateControlability(nwrap.getSatInstaller(TunerName.TUNER1).getOpPresenceStatus());
					}
				}
			};
			
			localOPProgTimer = new Timer();
			localOPProgTimer.schedule(localOPProgTimerTask, 0, 1000);
		}
			
	}
	
	public void stopOPCAMDetection(){
		Log.d(TAG,"stopOPCAMDetection");
		if (localOPProgTimerTask != null) { localOPProgTimerTask.cancel();}
		if (localOPProgTimer != null) { localOPProgTimer.cancel(); }
	}
	
	private void checkAndUpdateControlability(final OpPresentStatus argOpPresentStatus){
		
		((Activity)mContext).runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				HashMap<Integer,Boolean> controllabilityMap = new HashMap<Integer,Boolean>();
				// check for cam op status
				if(OpPresentStatus.NOT_PRESENT == argOpPresentStatus){
					
					// cam is not present at all
					enableWaitingAnimation(false);
					
					// downlight from cam and select advanced
					controllabilityMap.clear();
					controllabilityMap.put(IDX_FROM_CAM, false);
					controllabilityMap.put(IDX_ADVANCED_INSTALLATION,true);
					mRadioSelector.setControllable(controllabilityMap);
					
					//mRadioSelector.setItemChecked(IDX_ADVANCED_INSTALLATION, true);
					//mRadioSelector.setSelection(IDX_ADVANCED_INSTALLATION);
				}else if(OpPresentStatus.PRESENT == argOpPresentStatus){
					
					// cam detected and op profile supported
					enableWaitingAnimation(false);
					
					controllabilityMap.clear();
					controllabilityMap.put(IDX_FROM_CAM, true);
					controllabilityMap.put(IDX_ADVANCED_INSTALLATION,true);
					mRadioSelector.setControllable(controllabilityMap);
					
					//mRadioSelector.setItemChecked(IDX_FROM_CAM, true);
					//mRadioSelector.setSelection(IDX_FROM_CAM);
				}else if(OpPresentStatus.WAITING == argOpPresentStatus){
					// cam detection in progress
					enableWaitingAnimation(true);
					
					controllabilityMap.clear();
					controllabilityMap.put(IDX_FROM_CAM, false);
					controllabilityMap.put(IDX_ADVANCED_INSTALLATION,true);
					mRadioSelector.setControllable(controllabilityMap);
					
					//mRadioSelector.setItemChecked(IDX_ADVANCED_INSTALLATION, true);
					//mRadioSelector.setSelection(IDX_ADVANCED_INSTALLATION);
				}
			}
		});
		
	}

	@Override
	public void update(Observable observable, Object data) {

	}

	@Override
	public void setInstance(SatelliteWizard wizard) {
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName() {
		return ScreenRequest.CAM_SELECTION;
	}

	@Override
	public void screenIntialization() {
		Log.d(TAG, "screenIntialization");
		String[] radioListArray = { mContext.getString(org.droidtv.ui.strings.R.string.MAIN_FROM_THE_CAM), mContext.getString(org.droidtv.ui.strings.R.string.MAIN_ADVANCED_INSTALLATION) };
		mRadioSelector.setArray(radioListArray);
		triggerOPCAMDetectionIfRequired();
		mRadioSelector.setItemChecked(IDX_ADVANCED_INSTALLATION, true);
		mRadioSelector.setSelection(IDX_ADVANCED_INSTALLATION);
		mRadioSelector.requestFocus();
	}

	@Override
	public void screenExit() {
		Log.d(TAG, "screenExit");
	}
}
