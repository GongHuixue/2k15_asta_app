package org.droidtv.euinstallertc.settings;

import java.util.ArrayList;
import java.util.HashMap;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.AnalogSystemCountry;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DTRScreenMode;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.wizard.InstallerWizardActivity;
import org.droidtv.euinstallertc.settings.SettingsConstants;
import org.droidtv.euinstallertc.util.ContextHelper;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_MEDIUM;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuBuilder;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IChangeNotification;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.ICompanionWidgetControl;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.View;

public class SettingsHandler implements IApplication {

	private final String TAG = SettingsHandler.class.getName();
	// single instance holder
	private static SettingsHandler singletonInstance = null;
	private Context mContext;
	private MenuBuilder mMenuBuilderInst;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;
	private ITvSettingsManager mTvSettingsManager =ITvSettingsManager.Instance.getInterface();
	private boolean enablePBS = PlayTvUtils.isPbsMode(); 

	private SettingsHandler() {
	}

	// get single instance of NotificationHandler class
	public static SettingsHandler getInstance() {
		if (singletonInstance == null) {
			singletonInstance = new SettingsHandler();
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
		boolean returnStatus = true;

		Log.d(TAG, "isAvailable enter cookieID:" + cookieID + " enumVal:" + enumVal);

		switch (cookieID) {
		case SettingsConstants.MAIN_FREQUENCY_NUMBER:
			returnStatus = nwrap.ifChannelFrequncyNumberAvail();
			break;
		case SettingsConstants.MAIN_AUTOMATIC_CHANNEL_UPDATE:
		case SettingsConstants.MAIN_CHANNEL_UPDATE_MESSAGE:
			returnStatus = nwrap.ifAutomaticUpOptNChannelUpAvail();
			break;
		case SettingsConstants.MAIN_DIGITAL_TEST_RECEPTION:
			returnStatus = nwrap.IsDvbInstallationAvailable();
			break;
		// HTV - Jemy.	
		case SettingsConstants.MAIN_SEARCH:
			if (enablePBS) {
				returnStatus = false;
			} else {
				returnStatus = nwrap.IsDvbInstallationAvailable();
			}
			break;
		// HTV - Jemy.
		case SettingsConstants.MAIN_DVBT_SEARCH:			
		case SettingsConstants.MAIN_DVBC_SEARCH:
			if (enablePBS) {
				returnStatus = nwrap.IsDvbInstallationAvailable();
			} else {
				returnStatus = false;
			}
			break;
		case SettingsConstants.MAIN_SYSTEM:
			returnStatus = (nwrap.IsAPMEARegionAvailable() == true)?false:true;	// CR :RMCR-3078
			break;
		case SettingsConstants.MAIN_REORDER: 
			returnStatus = false;
		break;
		default:
			returnStatus = true;
		}

		Log.d(TAG, "isAvailable exit cookieID:" + cookieID + " enumVal:" + enumVal + " returnBool:" + returnStatus);
		return returnStatus;
	}

	@Override
	public boolean isControllable(Context ctx, int cookieID, int enumVal) {
		boolean returnStatus = true;
		Log.d(TAG, "isControllable enter cookieID:" + cookieID + " enumVal:" + enumVal);

		switch (cookieID) {
		case SettingsConstants.MAIN_REORDER:
			if (nwrap.getNoOfInstalledChannels() == 0) {
				returnStatus = false;
			}
			break;
		case SettingsConstants.MAIN_STORE_AS_NEW_CHANNEL:
			returnStatus = nwrap.ifStoreAsNewChannelEnabled();
			break;
		case SettingsConstants.MAIN_STORE_CURRENT_CHANNEL:

			Log.d(TAG,"MAIN_STORE_CURRENT_CHANNEL notified");
			//TF515PHIALLMTK01-20025 below func call added
			
			returnStatus = nwrap.ifStoreAsNewChannelEnabled() && nwrap.IsCurrentChannelAnalog();
			break;
		case SettingsConstants.MAIN_DIGITAL_TEST_RECEPTION:
			if (!enablePBS)
			{
				returnStatus = nwrap.isDTRMenuControllable();
			} else {
				returnStatus = true;
			}
			break;
		case SettingsConstants.MAIN_ANALOGUE_MANUAL_INSTALLATION:
			nwrap.setStoreAsNewChannelStatus(false);
			returnStatus = true;
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
		case SettingsConstants.MAIN_ANALOGUE_MANUAL_INSTALLATION:
			if (nwrap.isAnalogSwitchComplete() == false) {
				nwrap.SwitchToAnalogUsecase();
			}
			
			nwrap.loadCurrentAnalogValues();
			break;
		case SettingsConstants.MAIN_DIGITAL_TEST_RECEPTION:
			nwrap.autoSetSystemCountryToMW(true);
			if (!enablePBS) {
			// HTV - Jemy. Need set medium type on MAIN_SEARCH/MAIN_DVBC_SEARCH
			nwrap.setDVBTOrDVBC(nwrap.getSelectedDVBTOrDVBCFromTVS());
			}
			// reset the successful analog search done flag
			nwrap.setStoreAsNewChannelStatus(false);
			break;
		case SettingsConstants.MAIN_DVBT_SEARCH:
			Log.d(TAG, "Launching the DVB-T DTR");
			// HTV -Jemy
			//mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA);
			nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBT);
			nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBT);
			//nwrap.closeTIFSession();
			//nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
			break;
		case SettingsConstants.MAIN_DVBC_SEARCH:
			Log.d(TAG, "Launching the DVB-C DTR");
			// HTV -Jemy
			//mTvSettingsManager.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.CABLE);
			nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);			
			nwrap.setDVBTOrDVBC(NativeAPIEnums.DVBTOrDVBC.DVBC);
			//nwrap.closeTIFSession();
			//nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER); 
			break;				
		case SettingsConstants.MAIN_FIND_CHANNEL:
			//nothing done
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
		case SettingsConstants.MAIN_AUTOMATIC_CHANNEL_UPDATE:
			if (nwrap.GetStandbyUpdate() == 0) {
				returnVal = SettingsConstants.enumOFF;
			} else {
				returnVal = SettingsConstants.enumON;
			}
			break;

		case SettingsConstants.MAIN_FREQUENCY_NUMBER:
			if (nwrap.getDTRScreenMode() == DTRScreenMode.LOAD_CHANNEL_NUMBER) {
				returnVal = SettingsConstants.index_1;
			} else {
				returnVal = SettingsConstants.index_0;
			}
			break;

		case SettingsConstants.MAIN_CHANNEL_UPDATE_MESSAGE:
			if (nwrap.GetStartUpMsg() == 0) {
				returnVal = SettingsConstants.enumOFF;
			} else {

				returnVal = SettingsConstants.enumON;
			}
			break;
		case SettingsConstants.MAIN_SYSTEM:
			AnalogSystemCountry systemCountry = nwrap.getCachedAnalogSytemCountry();

			switch (systemCountry) {
			case EAST_EUROPE:
				returnVal = SettingsConstants.index_1;
				break;
			case UK:
				returnVal = SettingsConstants.index_2;
				break;
			case FRANCE:
				returnVal = SettingsConstants.index_3;
				break;
			default: // WEST_EUROPE
				returnVal = SettingsConstants.index_0;
				break;
			}
			break;
		}

		Log.d(TAG, "getInt exit cookieID:" + cookieID + " returnVal:" + returnVal);
		return returnVal;
	}

	@Override
	public void setInt(Context ctx, int cookieID, int enumVal) {
		Log.d(TAG, "setInt cookieID:" + cookieID + " enumVal:" + enumVal);
		Intent intent;
		switch (cookieID) {
		case SettingsConstants.MAIN_SEARCH_FOR_CHANNELS:
			intent = new Intent(mContext, InstallerWizardActivity.class);
			
			// intent = new Intent(mContext, WizardSettingsActivity.class);
			intent.putExtra("IntentParent", "ChannelSettings");

			mContext.startActivity(intent);
			break;
		case SettingsConstants.MAIN_SEARCH:
			Log.d(TAG, "Launching the DTR");

			break;
		case SettingsConstants.MAIN_AUTOMATIC_CHANNEL_UPDATE:
			if (enumVal == SettingsConstants.enumON) {
				nwrap.SetStandbyUpdate(true);
			} else if (enumVal == SettingsConstants.enumOFF) {
				nwrap.SetStandbyUpdate(false);
				
				// display tvtoast
				messenger = TvToastMessenger.getInstance(ctx);
				mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
				mTimeOutTvToast.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_AUTOMATIC_UPDATE_OFF));
				messenger.showTvToastMessage(mTimeOutTvToast);
				
			}
			break;
		case SettingsConstants.MAIN_CHANNEL_UPDATE_MESSAGE:
			if (enumVal == SettingsConstants.enumON) {
				nwrap.SetStartUpMsg(true);
			} else if (enumVal == SettingsConstants.enumOFF) {
				nwrap.SetStartUpMsg(false);
			}
			break;
		case SettingsConstants.MAIN_FREQUENCY_NUMBER:
			Log.d(TAG, "selection for MAIN_FREQUENCY_NUMBER");
			if (enumVal == SettingsConstants.index_0) {
				nwrap.setDTRScreenMode(DTRScreenMode.LOAD_CHANNEL_FREQ);
			} else {
				nwrap.setDTRScreenMode(DTRScreenMode.LOAD_CHANNEL_NUMBER);
			}

			break;
		case SettingsConstants.MAIN_FIND_CHANNEL:
			Log.d(TAG, "Launching the Analog");
			break;
		case SettingsConstants.MAIN_REORDER:
			Log.d(TAG, "Sending intent to reorder");
			intent = new Intent(TvIntent.ACTION_REORDER_CHANNELS);
			intent.putExtra(TvIntent.CHANNELS_REORDER_TUNER_TYPE, TvIntent.CHANNELS_REORDER_TERRESTRIAL);
			((Activity) mContext).startActivity(intent);
			((Activity) mContext).finish();
			break;
		case SettingsConstants.MAIN_STORE_CURRENT_CHANNEL:
			nwrap.StoreManualInstallOnCurrentChannel();
			break;
		case SettingsConstants.MAIN_STORE_AS_NEW_CHANNEL:
			nwrap.StoreManualInstallAsNewChannel();
			break;

		case SettingsConstants.MAIN_SYSTEM:
			switch (enumVal) {
			case SettingsConstants.index_0:
				nwrap.setCachedAnalogSytemCountry(AnalogSystemCountry.WEST_EUROPE);
				break;
			case SettingsConstants.index_1:
				nwrap.setCachedAnalogSytemCountry(AnalogSystemCountry.EAST_EUROPE);
				break;
			case SettingsConstants.index_2:
				nwrap.setCachedAnalogSytemCountry(AnalogSystemCountry.UK);
				break;
			case SettingsConstants.index_3:
				nwrap.setCachedAnalogSytemCountry(AnalogSystemCountry.FRANCE);
				break;
			default:
				break;
			}
			break;

		}
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
			ContextHelper.getInstance().setAppContext(mContext);
			ContextHelper.getInstance().setContext(contextLevel, context);
		}
	}

	public void setLabel(int cookie, String lable) {
	}

	public void setIcons(int cookie, int value, String[] iconsarray) {
	}

}
