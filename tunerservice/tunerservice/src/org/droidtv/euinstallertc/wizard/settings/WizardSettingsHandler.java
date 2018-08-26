package org.droidtv.euinstallertc.wizard.settings;

import java.util.ArrayList;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.AnalogueOrDigital;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DVBTOrDVBC;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.settings.SettingsConstants;
import org.droidtv.euinstallertc.util.ContextHelper;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuBuilder;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IChangeNotification;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tunerservice.util.PlayTvUtils;

import android.content.Context;
import android.util.Log;

public class WizardSettingsHandler implements IApplication {

	private static final String TAG = WizardSettingsHandler.class.getName();
	// single instance holder
	private static WizardSettingsHandler singletonInstance = null;
	private Context mContext;
	private MenuBuilder mMenuBuilderInst;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private ITvSettingsManager mTvSettingsManager = ITvSettingsManager.Instance.getInterface();

	private boolean EnableDVBC = true;
	private boolean EnableDVBT = true;
	private boolean EnableAnalog = true;
	private WizardSettingsHandler() {
	}

	// get single instance of NotificationHandler class
	public static WizardSettingsHandler getInstance() {
		if (singletonInstance == null) {
			singletonInstance = new WizardSettingsHandler();
		}
		return singletonInstance;
	}

	public void setContext(Context argCtx, MenuBuilder argMenuBuilderInst) {
		mContext = argCtx;
		mMenuBuilderInst = argMenuBuilderInst;
	}

	@Override
	public void dump(String arg0, String arg1, String arg2) {
		// TODO Auto-generated method stub

	}

	@Override
	public String[] getIcons(Context arg0, int arg1, int arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getLabel(Context arg0, int arg1, int arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<ListData> getListData(Context arg0, int arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Object getObj(Context arg0, int arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean isAvailable(Context ctx, int cookieID, int enumVal) {
		boolean returnDvbtStatus = false;
		boolean returnDvbcStatus = false;
		boolean returnStatus = true;

		Log.d(TAG, "isAvailable enter cookieID:" + cookieID + " enumVal:" + enumVal);

        EnableDVBC = (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_C_C2, 0, 0));
        EnableDVBT = (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_T_T2, 0, 0));
        EnableAnalog = (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_ANALOG, 0, 0));

		switch (cookieID) {
		case SettingsConstants.MAIN_FREQUENCY_SCAN:
			if (PlayTvUtils.isPbsMode()) {
				if (EnableDVBT) {
					// Terrestrial
					if (nwrap.countrySupportsDVBTFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Full) {
						returnDvbtStatus = true;
					} else {
						returnDvbtStatus = false;
					}
				}
				returnStatus = returnDvbtStatus;
			} else {
				if (NativeAPIEnums.DVBTOrDVBC.DVBT == nwrap.getCachedDVBTOrDVBC()) {
					// Terrestrial
					if (nwrap.countrySupportsDVBTFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Full) {
						returnStatus = true;
					} else {
						returnStatus = false;
					}
				} else {
					// Cable

					if (((nwrap.getCachedCountryName() != ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS)) && (nwrap.getCachedOperatorName() != ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC))
							&& (nwrap.getCachedOperatorName() != ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET))
							&& (nwrap.getCachedOperatorName() != ctx.getString(org.droidtv.ui.strings.R.string.MISC_RCS_RDS)) && nwrap.ifDVBCSupportedCountry(nwrap.getCachedCountryName()))) {
						returnStatus = true;
					} else {
						returnStatus = false;
					}
				}
				
			}
			break;
		case SettingsConstants.MAIN_DVBC_FREQUENCY_SCAN:
			if (EnableDVBC) {
				// Cable
				if (((nwrap.getCachedCountryName() != ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS)) && (nwrap.getCachedOperatorName() != ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC))
						&& (nwrap.getCachedOperatorName() != ctx.getString(org.droidtv.ui.strings.R.string.MISC_TELENET))
						&& (nwrap.getCachedOperatorName() != ctx.getString(org.droidtv.ui.strings.R.string.MISC_RCS_RDS)) && nwrap.ifDVBCSupportedCountry(nwrap.getCachedCountryName()))) {
					returnDvbcStatus = true;
				} else {
					returnDvbcStatus = false;
				}
			}
			returnStatus = returnDvbcStatus;
			break;
		case SettingsConstants.MAIN_FREQUENCY_STEP_SIZE:
			if (PlayTvUtils.isPbsMode()) {
				if (EnableDVBC && nwrap.ifDVBCSupportedCountry(nwrap.getCachedCountryName())) {
					returnStatus = true;
				} else {
					returnStatus = false;
				}
			} else {
				if ((NativeAPIEnums.DVBTOrDVBC.DVBC == nwrap.getCachedDVBTOrDVBC()) && nwrap.ifDVBCSupportedCountry(nwrap.getCachedCountryName())) {
					returnStatus = true;
				} else {
					returnStatus = false;
				}
			}
			break;
		case SettingsConstants.MAIN_NETWORK_FREQUENCY_MODE:
		case SettingsConstants.MAIN_NETWORK_FREQUENCY:
			returnStatus = false;
			if (PlayTvUtils.isPbsMode()) {
				if (EnableDVBC) {			
					if ((nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS)) || (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))
							|| (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)) {

						returnStatus = false;
					} else if (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA)) {
						if (nwrap.getCachedOperatorName() != ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC)) {
							returnStatus = true;
						}
					} else if ((nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA)) &&
							(nwrap.getCachedOperatorName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BLIZOO))) {
							returnStatus = false;
					} else if (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Full) {
						returnStatus = true;
					}
				} else {
					returnStatus = false;
				}
			
			} else {
				if ((NativeAPIEnums.DVBTOrDVBC.DVBC == nwrap.getCachedDVBTOrDVBC())) {
					if ((nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_NETHERLANDS)) || (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_AUSTRIA))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_HUNGARY))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_POLAND))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_IRELAND))
							|| (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))
							|| (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)) {

						returnStatus = false;
					} else if (nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_ROMANIA)) {
						if (nwrap.getCachedOperatorName() != ctx.getString(org.droidtv.ui.strings.R.string.MISC_UPC)) {
							returnStatus = true;
						}
					} else if ((nwrap.getCachedCountryName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BULGARIA)) &&
							(nwrap.getCachedOperatorName() == ctx.getString(org.droidtv.ui.strings.R.string.MAIN_BLIZOO))) {
							returnStatus = false;
					} else if (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Full) {
						returnStatus = true;
					}
				} else {
					returnStatus = false;
				}
			}
			break;
			
		case SettingsConstants.MAIN_DTT_SCAN:
			if (PlayTvUtils.isPbsMode()) {
				if ((nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)
					&& EnableDVBC) {
					returnStatus = true;
				} else {
					returnStatus = false;
				}
			} else {
				if ((nwrap.countrySupportsDVBCFullorLite(nwrap
						.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)
						&& (NativeAPIEnums.DVBTOrDVBC.DVBC == nwrap
								.getCachedDVBTOrDVBC())) {
					returnStatus = true;
				} else {
					returnStatus = false;
				}
			}
			break;
		case SettingsConstants.MAIN_DUAL_ANALOG_PASS:
			if (((nwrap.getCachedCountryName() == ctx
					.getString(org.droidtv.ui.strings.R.string.MAIN_SWITZERLAND))
					|| (nwrap.getCachedCountryName() == ctx
							.getString(org.droidtv.ui.strings.R.string.MAIN_FRANCE))
					|| (nwrap.getCachedCountryName() == ctx
							.getString(org.droidtv.ui.strings.R.string.MAIN_BELGIUM))
					|| (nwrap.getCachedCountryName() == ctx
							.getString(org.droidtv.ui.strings.R.string.MAIN_LUXEMBOURG))) 
							
					&& (nwrap.getCachedAnalogueDigital()!= NativeAPIEnums.AnalogueOrDigital.DIGITAL)
					&& (EnableDVBC && (PlayTvUtils.isPbsMode() == false))) {
				returnStatus = true;
			} else {
				returnStatus = false;
			}
			break;
		default:
			returnStatus = true;
			break;
		}
		
		Log.d(TAG, "isAvailable exit cookieID:" + cookieID + " enumVal:" + enumVal + " returnBool:" + returnStatus);
		return returnStatus;
	}

	@Override
	public boolean isControllable(Context ctx, int cookieID, int enumVal) {
		boolean returnStatus = true;
		ITvSettingsManager  mTvSettingMgr = ITvSettingsManager.Instance.getInterface();
		Log.d(TAG, "isControllable enter cookieID:" + cookieID + " enumVal:" + enumVal);

		switch (cookieID) {
		case SettingsConstants.MAIN_FREQUENCY_SCAN:
			if (PlayTvUtils.isPbsMode()) {
				if(EnableDVBT){
					returnStatus = true;
				} else {
					returnStatus = false;
				}
				break;
			} 
		case SettingsConstants.MAIN_DVBC_FREQUENCY_SCAN:
		case SettingsConstants.MAIN_FREQUENCY_STEP_SIZE:
			if (PlayTvUtils.isPbsMode()) {
				if(EnableDVBC){
					returnStatus = true;
				} else {
					returnStatus = false;
				}
			} else {
				if (((nwrap.getCachedDVBTOrDVBC() == DVBTOrDVBC.DVBT) && (nwrap.countrySupportsDVBTFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Full))
						|| ((nwrap.getCachedDVBTOrDVBC() == DVBTOrDVBC.DVBC) && (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Full))) {
					returnStatus = true;
				} else {
					returnStatus = nwrap.ifDigitalOptionOn();
				}			
			}
			break;
		case SettingsConstants.MAIN_NETWORK_FREQUENCY_MODE:
			if (PlayTvUtils.isPbsMode()) {
				nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);
				if (nwrap.getWSFreqScanMode() == 0) {
					returnStatus = true;
				} else {
					returnStatus = false;
				}
				break;
			}
			if (nwrap.ifDigitalOptionOn()) {
				if (nwrap.getWSFreqScanMode() == 0) {
					returnStatus = true;
				} else {
					returnStatus = false;
				}
			} else {
				returnStatus = false;
			}
			break;
		case SettingsConstants.MAIN_NETWORK_FREQUENCY:
			if (PlayTvUtils.isPbsMode()) {
				nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);
				if ((nwrap.getWSFreqScanMode() == 0) && (nwrap.getWSNetworkFrequencyMode() == 1)) {
					returnStatus = true;
				} else {
					returnStatus = false;
				}
				break;
			}
			if (nwrap.ifDigitalOptionOn()) {
				if ((nwrap.getWSFreqScanMode() == 0) && (nwrap.getWSNetworkFrequencyMode() == 1)) {
					returnStatus = true;
				} else {
					returnStatus = false;
				}
			} else {
				returnStatus = false;
			}
			break;
		case SettingsConstants.MAIN_FREE_SCRAMBLED:
			returnStatus = true;
			if ((nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light) && (NativeAPIEnums.DVBTOrDVBC.DVBC == nwrap.getCachedDVBTOrDVBC())) {
				returnStatus = nwrap.ifDigitalOptionOn();
			}
			break;
		case SettingsConstants.MAIN_DTT_SCAN:
			returnStatus = true; 
			break;
		case SettingsConstants.MAIN_DUAL_ANALOG_PASS:
			returnStatus = true;				 
			break;	
		case SettingsConstants.MAIN_DVBT_SETTINGS:
			if(EnableDVBT){
				//nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBT);
				returnStatus = true;
			} else {
				returnStatus = false;
			}
			break;
		case SettingsConstants.MAIN_DVBC_SETTINGS:
			if(EnableDVBC){
				//nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);
				returnStatus = true;
			} else {
				returnStatus = false;
			}
			break;
		default:
			returnStatus = true;
			break;
		}

		Log.d(TAG, "isControllable exit cookieID:" + cookieID + " enumVal:" + enumVal + " returnBool:" + returnStatus);

		return returnStatus;
	}

	@Override
	public boolean isNodeLocked(Context ctx, int cookieID) {
		return false;
	}

	@Override
	public void onNodeEntered(Context ctx, int cookieID) {
		Log.d(TAG, "onNodeEntered cookieID: " + cookieID);

		switch (cookieID) {
		default:
			break;
		}

	}

	@Override
	public void onNodeExited(Context ctx, int cookieID) {
		Log.d(TAG, "onNodeExited cookieID: " + cookieID);
	}

	@Override
	public void onNodeFocusGained(Context ctx, int cookieID) {
		Log.d(TAG, "onNodeFocusGained cookieID: " + cookieID);

	}

	@Override
	public void onNodeFocusLost(Context ctx, int cookieID) {
		Log.d(TAG, "onNodeFocusLost cookieID: " + cookieID);

	}

	@Override
	public void registerNodeChanges(IChangeNotification MenuNodeChangeImpl, int cookie) {
	}

	@Override
	public int getInt(Context ctx, int cookieID) {
		int returnVal = 0;
		Log.d(TAG, "getInt enter cookieID:" + cookieID);

		switch (cookieID) {
		case SettingsConstants.MAIN_FREQUENCY_SCAN:
			if (PlayTvUtils.isPbsMode()) {
				nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBT);
				returnVal = nwrap.getWSFreqScanMode();
				if (EnableDVBC)	{
					nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);
				}
			} else {
				returnVal = nwrap.getWSFreqScanMode();
			}
			break;
		case SettingsConstants.MAIN_DVBC_FREQUENCY_SCAN:
			nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);
			returnVal = nwrap.getWSFreqScanMode();
			if (!EnableDVBC) {
				nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBT);
			}
			break;
		case SettingsConstants.MAIN_FREQUENCY_STEP_SIZE:
			returnVal = nwrap.getWSFreqStepSize();
			break;
		case SettingsConstants.MAIN_NETWORK_FREQUENCY_MODE:
			returnVal = nwrap.getWSNetworkFrequencyMode();
			break;
		case SettingsConstants.MAIN_NETWORK_FREQUENCY:
			break;
		case SettingsConstants.MAIN_FREE_SCRAMBLED:
			// 1: SCR + FTA
			// 0: FTA only
			int returnFTA = nwrap.getWSSetFreeCAChannels();
			returnVal = (returnFTA == 1) ? 0 : 1;
			break;
		case SettingsConstants.MAIN_DTT_SCAN:
			returnVal = (nwrap.getDTTScanStatus() == 0) ? 0 : 1;
			break;
		case SettingsConstants.MAIN_DUAL_ANALOG_PASS:
			returnVal = (nwrap.getDualAnalogPassStatus() == 0) ? 0 : 1;
			break;
		default:
			returnVal = 0;
			break;
		}

		Log.d(TAG, "getInt exit cookieID:" + cookieID + " returnVal:" + returnVal);
		return returnVal;
	}

	@Override
	public void setInt(Context ctx, int cookieID, int enumVal) {
		Log.d(TAG, "setInt cookieID:" + cookieID + " enumVal:" + enumVal);
		switch (cookieID) {
		case SettingsConstants.MAIN_FREQUENCY_SCAN:
			if (PlayTvUtils.isPbsMode()) {
				nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBT);
				nwrap.setWSFreqScanMode(enumVal);
				if (EnableDVBC)	{
					nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);
				}
			} else {
				nwrap.setWSFreqScanMode(enumVal);
			}
			break;
		case SettingsConstants.MAIN_DVBC_FREQUENCY_SCAN:
			nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);
			nwrap.setWSFreqScanMode(enumVal);
			if (!EnableDVBC) {
				nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBT);
			}
			break;
		case SettingsConstants.MAIN_FREQUENCY_STEP_SIZE:
			nwrap.setWSFreqStepSize(enumVal);
			break;
		case SettingsConstants.MAIN_NETWORK_FREQUENCY_MODE:
			nwrap.setWSNetworkFrequencyMode(enumVal);
			break;
		case SettingsConstants.MAIN_FREE_SCRAMBLED:
			enumVal = (enumVal == 1) ? 0 : 1;
			nwrap.setWSSetFreeCAChannels(enumVal);
			break;
		case SettingsConstants.MAIN_DTT_SCAN:
			enumVal = (enumVal == 1) ? 1 : 0;
			nwrap.setDTTScanStatus(enumVal);
			break;
		case SettingsConstants.MAIN_DUAL_ANALOG_PASS:
			enumVal = (enumVal == 1) ? 1 : 0;
			nwrap.setDualAnalogPassStatus(enumVal);
			break;
		default:
			break;
		}
		
		revalidateControlabilityOfList();
		mMenuBuilderInst.refreshUI();
	}
	
	public void revalidateControlabilityOfList(){
		mMenuBuilderInst.onChanged(IChangeNotification.CONTROLLABLITY_CHANGE, SettingsConstants.MAIN_FREQUENCY_SCAN, true);
		mMenuBuilderInst.onChanged(IChangeNotification.CONTROLLABLITY_CHANGE, SettingsConstants.MAIN_FREQUENCY_STEP_SIZE, true);
		mMenuBuilderInst.onChanged(IChangeNotification.CONTROLLABLITY_CHANGE, SettingsConstants.MAIN_NETWORK_FREQUENCY_MODE, true);
		mMenuBuilderInst.onChanged(IChangeNotification.CONTROLLABLITY_CHANGE, SettingsConstants.MAIN_NETWORK_FREQUENCY, true);
		mMenuBuilderInst.onChanged(IChangeNotification.CONTROLLABLITY_CHANGE, SettingsConstants.MAIN_FREE_SCRAMBLED, true);
	}

	@Override
	public void setObj(Context arg0, int arg1, Object arg2) {
		// TODO Auto-generated method stub
	}

	@Override
	public void unRegisterNodeChanges(IChangeNotification arg0) {
		// TODO Auto-generated method stub
	}

	@Override
	public void unRegisterNodeChanges(IChangeNotification MenuNodeChangeImpl, int cookie) {

	}

	@Override
	public void updateHelpContext(int contextLevel, String context) {
		Log.d(TAG,"updateHelpContext "+contextLevel+", "+context);
		if(mContext!=null && context!=null && !context.equals("")){
			//ContextHelper.getInstance().setContext(contextLevel, context);
		}
	}

	public void setLabel(int cookie, String lable) {
	}

	public void setIcons(int cookie, int value, String[] iconsarray) {
	}

}
