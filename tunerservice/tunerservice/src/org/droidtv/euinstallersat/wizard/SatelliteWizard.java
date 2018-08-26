package org.droidtv.euinstallersat.wizard;

import java.util.Stack;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.LnbSettingsEntry;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.TunerName;
import org.droidtv.euinstallersat.wizard.satip.SatIPWrapper;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions.InstallationCountryConstants;
import org.droidtv.ui.tvwidget2k15.wizardframework.Wizard;
import org.droidtv.ui.tvwidget2k15.wizardframework.Wizard.IWizardMovementCallback;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class SatelliteWizard extends Wizard implements IWizardMovementCallback
{

	private static final String TAG = SatelliteWizard.class.getName();
	private Context mContext;
	private ScreenRequest mLaunchItem = ScreenRequest.INSTALLMODES;
	private Stack<ScreenRequest> mScreenRequestStack;

	private int progress;
	private NativeAPIWrapper m_wrapper;
	private SatelliteScreen m_selectedSatelliteScreen = null;
	private ScreenRequest m_firstScreen;
	
	private final int MAX_STEPS_REINSTALL = 8;
	private final int MAX_STEPS_UPDATE_SAT = 5;
	private final int MAX_STEPS_ADD_SAT = 5;
	private final int MAX_STEPS_REMOVE_SAT = 3;
	private final int MAX_STEPS_CAM_SAT = 5;
	private final int MAX_STEPS_SATIP = 7;
	
	private SatIPWrapper m_satipwrapper;
	
	private int[][] m_progressIndex = new int[][]{ 
													{2,MAX_STEPS_REINSTALL}, 	//INSTALLMODES
													{3,MAX_STEPS_REINSTALL},	//STARTSCREEN
													{4,MAX_STEPS_REINSTALL}, 	//PRESCAN
													{5,MAX_STEPS_REINSTALL}, 	//PACKAGE_SELECTION
													{6,MAX_STEPS_REINSTALL}, 	//QUICK_FULL
													{7,MAX_STEPS_REINSTALL},	//INSTALLSCREEN
													{8,MAX_STEPS_REINSTALL},	//FINISHSCREEN
													{3,MAX_STEPS_UPDATE_SAT},	//UPDATESATELLITE
													{4,MAX_STEPS_UPDATE_SAT},	//UPDATESCAN
													{3,MAX_STEPS_UPDATE_SAT},	//SATELLITESELECTION
													{5,MAX_STEPS_UPDATE_SAT},	//FINISHUPDATE
													{3,MAX_STEPS_ADD_SAT},		//ADDSATPRESCAN
													{4,MAX_STEPS_ADD_SAT},		//ADDSATINSTALL
													{5,MAX_STEPS_ADD_SAT},		//ADDSATFINISH
													{3,MAX_STEPS_REMOVE_SAT},	//REMOVESATSELECTION
													{3,MAX_STEPS_REINSTALL},	//DUAL_TUNER
													{1,MAX_STEPS_REINSTALL},	//VIRGIN_INSTALL_TEASER
													{3,MAX_STEPS_UPDATE_SAT},	//MINI_PRESCAN
													{2,MAX_STEPS_CAM_SAT},		//CAM_SELECTION
													{3,MAX_STEPS_CAM_SAT},		//CAM_INSTALLATION
													{5,MAX_STEPS_REINSTALL},	//PIN_ENTRY
													{4,MAX_STEPS_REINSTALL},	//FREESAT_POSTCODE_ENTRY
													{2,MAX_STEPS_SATIP},		//SATIP_STARTSCREEN
													{3,MAX_STEPS_SATIP},		//SATIP_HUBSCREEN
													{4,MAX_STEPS_SATIP},		//SATIP_SERVERLIST
													{5,MAX_STEPS_SATIP},		//SATIP_PRESCAN
													{6,MAX_STEPS_REINSTALL}, 	//TRICOLOR_REGION_SELECTION
													{6,MAX_STEPS_REINSTALL}		//HBBTV_PRIVACY_STATEMENT
													
	};
	

	public enum ScreenRequest
	{
		INSTALLMODES, STARTSCREEN, PRESCAN, PACKAGE_SELECTION, QUICK_FULL, INSTALLSCREEN, FINISHSCREEN, 
		UPDATESATELLITE, UPDATESCAN, SATELLITESELECTION, FINISHUPDATE, ADDSATPRESCAN, ADDSATINSTALL, ADDSATFINISH, REMOVESATSELECTION, DUAL_TUNER,
		VIRGIN_INSTALL_TEASER,MINI_PRESCAN,CAM_SELECTION,CAM_INSTALLATION,PIN_ENTRY,FREESAT_POSTCODE_ENTRY,SATIP_STARTSCREEN,SATIP_HUBSCREEN,
		SATIP_SERVERLIST, SATIP_PRESCAN,TRICOLOR_REGION_SELECTION, HBBTV_PRIVACY_STATEMENT
	}

	public SatelliteWizard(Context context, AttributeSet attrSet, int defStyle) {
		super(context, attrSet, defStyle);
		mContext = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		m_satipwrapper = SatIPWrapper.getInstance();
		m_wrapper.initializeCache ();
		
		mScreenRequestStack = new Stack<SatelliteWizard.ScreenRequest>();
		if (m_wrapper.GetCountry() == InstallationCountryConstants.FRANCE ) {
			// RMCR-1976
			// RMCR-3233 TF515PHIALLMTK01-18278

			// trigger opcam status check
			m_wrapper.getSatInstaller(TunerName.TUNER1).triggerCAMOPStatusCheck();
			mLaunchItem = ScreenRequest.CAM_SELECTION;
		} else if (m_wrapper.isVirginInstallMode()) {
			if(m_satipwrapper.ifSatIPServerDetectedOnBoot()){
				mLaunchItem = ScreenRequest.SATIP_STARTSCREEN;
				
				// set satip connection type to mw
				m_wrapper.SetTypeOfLNB(LnbSettingsEntry.LnbConnectionSatIP);
			}else{
				mLaunchItem = ScreenRequest.VIRGIN_INSTALL_TEASER;
			}
		} else if (m_wrapper.isCamUpdateMode()) {
			mLaunchItem = ScreenRequest.UPDATESCAN;
		} else if(m_wrapper.getNVMConnectionType() == LnbSettingsEntry.LnbConnectionSatIP){
			
			if (m_wrapper.getNoOfInstalledChannels() == 0){
				mLaunchItem = ScreenRequest.SATIP_STARTSCREEN;
			}else{
				mLaunchItem = ScreenRequest.INSTALLMODES;
			}
		} else if (m_wrapper.getNoOfInstalledChannels() == 0) {
			if (m_wrapper.isTwoTunerSupported()) {
				mLaunchItem = ScreenRequest.DUAL_TUNER;
			} else {
				mLaunchItem = ScreenRequest.STARTSCREEN;
			}
		} else{
			mLaunchItem = ScreenRequest.INSTALLMODES;
		}
		
		
		Log.d(TAG, "SatelliteWizard First Screen: " + mLaunchItem);
		m_firstScreen = mLaunchItem;
		mScreenRequestStack.push(mLaunchItem);
		// mSatelliteInstallation = new ArrayList<View>();
		loadLayout(context);

	}

	public SatelliteWizard(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public SatelliteWizard(Context context)
	{
		this(context, null, 0);
	}

	/*
	 * Load the list of wizard steps Params : Context
	 */
	private void loadLayout(Context context)
	{
		View.inflate(mContext, R.layout.satellitewizardsteps, null);
		//mNpb = (NPanelBrowser) ((SatelliteInstallationActivity) mContext).findViewById(org.droidtv.ui.tvwidget2k15.R.id.nPanelBrowser1);
		
	}

	public void initWizardScreen()
	{
		if(m_selectedSatelliteScreen !=null)
		{
			m_selectedSatelliteScreen.screenIntialization();
		}
	}
	
	@Override
	public void setWizardScreen(WizardScreen arg0)
	{
		Log.d(TAG,"setWizardScreen");
		int l_childCount = getChildCount();
		int l_idx;
		for(l_idx = 0; l_idx < l_childCount; l_idx ++)
		{
			View step = getChildAt(l_idx);
			((SatelliteScreen) step).setInstance(this);
			((WizardStep) step).setWizardListener(this);
		}
		setWizardMovementCallback(this);
		super.setWizardScreen(arg0);
		
		Log.d(TAG,"Step count : " + getStepCount());
		
	}

	public void launchPreviousScren()
	{
		if((mLaunchItem == m_firstScreen) || (mScreenRequestStack.isEmpty()))
		{
			Log.d(TAG,"back from first screen, calling activity finish");
			((SatelliteInstallationActivity)mContext).exitInstallationWizard();
			return;
		}
		mLaunchItem = mScreenRequestStack.pop();
		Log.d(TAG, "launchPreviousScreen currentscreen:" + mLaunchItem);
		if(m_selectedSatelliteScreen !=null)
		{
			m_selectedSatelliteScreen.screenExit();
		}
		
	
		gotoPrevStep();
		if(m_selectedSatelliteScreen !=null)
		{
			m_selectedSatelliteScreen.screenIntialization();
		}
		
	}

	public void launchScreen(ScreenRequest launchItem, ScreenRequest currentItem)
	{

		// populate in the stack with existing item
		mScreenRequestStack.push(mLaunchItem);
		// set the next screen to be launched
		mLaunchItem = launchItem;
		if(m_selectedSatelliteScreen !=null)
		{
			m_selectedSatelliteScreen.screenExit();
		}
		// trigger callback by framework to getPanelView(index) function
		gotoNextStep();
		if(m_selectedSatelliteScreen !=null)
		{
			m_selectedSatelliteScreen.screenIntialization();
		}
		

	}

	@Override
	public void gotoNextStep()
	{
		super.gotoNextStep();
	}

	public ScreenRequest getCurrentScreen()
	{
		Log.d(TAG, "getCurrentScreen() " + mLaunchItem);
		return mLaunchItem;
	}
	
	
	public boolean launchFirstScreen()
	{
		Log.d(TAG,"launchFirstScreen");
		boolean l_ret = true;
		ScreenRequest l_currentScreen = getCurrentScreen();
		Log.d(TAG,"l_currentScreen = " + l_currentScreen + ",m_firstScreen = " + m_firstScreen);
		if(l_currentScreen != m_firstScreen)
		{
			m_selectedSatelliteScreen.screenExit();
			launchScreen(m_firstScreen, l_currentScreen);
			l_ret = true;
		}
		else
		{
			l_ret = false;//already on the first screen of the wizard
		}
		return l_ret;
	}
	
	
	/*
	 * (non-Javadoc)
	 * 
	 * @see org.droidtv.ui.comps.wizardframework.Wizard#getPanelView(int)
	 */
	@Override
	public View getPanelView(int index)
	{
		View retView = null;
		setWizardLabel(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_SATELLITE_INSTALLATION));
		// update the wizard progress
		progress = index;
		
		retView = super.getPanelView(index);
		
		int l_stepCount = getStepCount();
		if (progress >= 0 && progress < l_stepCount - 1)
		{
			int l_stepIdx = mLaunchItem.ordinal();
			setWizardProgress(m_progressIndex[l_stepIdx][0], m_progressIndex[l_stepIdx][1]);
		}
		

		

		if (mLaunchItem == ((SatelliteScreen) retView).getScreenName())
		{
			Log.v(TAG, "getPanel View reView:" + retView);
			m_selectedSatelliteScreen = ((SatelliteScreen) retView);
			return retView;
		}
		
		return null;
	}



	@Override
	public int getNextStepIndex(int p_currentStepIndex)
	{
		Log.d(TAG,"getNextStepIndex");
		Log.d(TAG,"mLaunchItem " + mLaunchItem.toString());
		Log.d(TAG,"mLaunchItem.ordinal " + mLaunchItem.ordinal());
		return mLaunchItem.ordinal();
	}

	@Override
	public int getPrevStepIndex(int p_currentStepIndex)
	{
		Log.d(TAG,"getPrevStepIndex");
		Log.d(TAG,"mLaunchItem " + mLaunchItem.toString());
		Log.d(TAG,"mLaunchItem.ordinal " + mLaunchItem.ordinal());
		return mLaunchItem.ordinal();
	}

}
