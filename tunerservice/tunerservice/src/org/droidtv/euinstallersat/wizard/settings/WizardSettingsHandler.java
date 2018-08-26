package org.droidtv.euinstallersat.wizard.settings;

import java.util.ArrayList;

import org.droidtv.euinstallersat.model.mwapi.LnbSettingsEntry;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.settings.SettingsConstants;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeActivity;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuBuilder;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IChangeNotification;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class WizardSettingsHandler implements IApplication
{

	private static final String TAG = WizardSettingsHandler.class.getName();
	// single instance holder
	private static WizardSettingsHandler mHandlerInstance = null;
	private Context mContext;
	private MenuBuilder mMenuBuilderInst;
	private NativeAPIWrapper m_wrapper = NativeAPIWrapper.getInstance();

	private WizardSettingsHandler()
	{
	}

	// get single instance of NotificationHandler class
	public static WizardSettingsHandler getInstance()
	{
		if (mHandlerInstance == null)
		{
			mHandlerInstance = new WizardSettingsHandler();
		}
		return mHandlerInstance;
	}

	public void setContext(Context argCtx, MenuBuilder argMenuBuilderInst)
	{
		Log.d(TAG,"setContext " + argCtx);
		mContext = argCtx;
		mMenuBuilderInst = argMenuBuilderInst;
	}

	@Override
	public void dump(String arg0, String arg1, String arg2)
	{
		// TODO Auto-generated method stub

	}

	@Override
	public String[] getIcons(Context arg0, int arg1, int arg2)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getLabel(Context arg0, int arg1, int arg2)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<ListData> getListData(Context arg0, int arg1)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Object getObj(Context arg0, int arg1)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean isAvailable(Context ctx, int cookieID, int enumVal)
	{
		
		Log.d(TAG, "isAvailable");
		Boolean l_ret = true;
		switch (cookieID)
		{
			case SettingsConstants.MAIN_HOMING_TRANSPONDER:
				l_ret = m_wrapper.GetIsNordicCountry();
				break;
			case SettingsConstants.CD_LNB_SETTINGS:
				 //l_ret = m_wrapper.IsLnbSettingsAvailable();
				l_ret = true;	// AN-76771
				break;	
			case SettingsConstants.CD_LNB_TWO_SETTINGS:
				if((LnbSettingsEntry.LnbConnectionDiSeqcMini != m_wrapper.getConnectionType())&&
				   (LnbSettingsEntry.LnbConnectionDiSeqc1_0 != m_wrapper.getConnectionType())&&
				   (LnbSettingsEntry.LnbConnectionUnicableSwitch != m_wrapper.getConnectionType()) 
				  ) 
				{
						l_ret = false;
				}
				break;
			
			case SettingsConstants.CD_LNB_THREE_SETTINGS:
			case SettingsConstants.CD_LNB_FOUR_SETTINGS:
				if(LnbSettingsEntry.LnbConnectionDiSeqc1_0 != m_wrapper.getConnectionType())
				{
						l_ret = false;
				}
				break;
			case SettingsConstants.CD_LNB_ONE_LNBPOWER:
			case SettingsConstants.CD_LNB_TWO_LNBPOWER:
				l_ret =m_wrapper.IsLnbPowerAvailable();
				break;
		}
		return l_ret;
		}

	@Override
	public boolean isControllable(Context ctx, int cookieID, int enumVal)
	{
		Log.d(TAG, "getControllablityOfNode");
		Boolean l_ret = true;
		switch(cookieID)
		{
	
			case SettingsConstants.CD_HOMING_SYMBOL_RATE:
				l_ret = m_wrapper.isCDHomingSymbolRateControllable();
				break;
			default: l_ret = true;
			
		}
		return l_ret;	}

	@Override
	public boolean isNodeLocked(Context ctx, int cookieID)
	{
		return false;
	}

	@Override
	public void onNodeEntered(Context ctx, int cookieID)
	{
		Log.d(TAG, "onNodeItemClicked");
		
		

	}

	@Override
	public void onNodeExited(Context ctx, int cookieID)
	{
		Log.d(TAG, "onNodeExited cookieID: " + cookieID);
	}

	@Override
	public void onNodeFocusGained(Context ctx, int cookieID)
	{
		Log.d(TAG, "onNodeFocusGained cookieID: " + cookieID);

	}

	@Override
	public void onNodeFocusLost(Context ctx, int cookieID)
	{
		Log.d(TAG, "onNodeFocusLost cookieID: " + cookieID);

	}

	@Override
	public void registerNodeChanges(IChangeNotification MenuNodeChangeImpl, int cookie)
	{
	}

	@Override
	public int getInt(Context ctx, int cookieID)
	{
		int l_ret = 0;
		switch (cookieID)
		{
			case SettingsConstants.MAIN_CH_SAT_HOMING_POLARISATION:
				if(m_wrapper.GetPolarisationForCDHomingTransponder() == MwDataTypes.PolarisationVertical)
				{
					l_ret = 0;
				} else {
					l_ret = 1;
				}
				break;
			case SettingsConstants.CD_HOMING_SYMBOL_RATE_MODE:
				l_ret = m_wrapper.GetSymRateModeForCDHomingTransponder();
				break;
			case SettingsConstants.CD_LNB_ONE_LNBPOWER:
				l_ret =m_wrapper.GetLnbPower(0);
				break;
			case SettingsConstants.CD_LNB_TWO_LNBPOWER:
				l_ret =m_wrapper.GetLnbPower(1);
				break;
			case SettingsConstants.CD_LNB_THREE_LNBPOWER:
				l_ret =m_wrapper.GetLnbPower(2);
				break;
			case SettingsConstants.CD_LNB_FOUR_LNBPOWER:
				l_ret =m_wrapper.GetLnbPower(3);
				break;
		}
		return l_ret;	}

	@Override
	public void setInt(Context ctx, int cookieID, int enumVal)
	{
		Log.d(TAG, "setInt cookieID:" + cookieID + " enumVal:" + enumVal);
		switch(cookieID)
		{
			case SettingsConstants.CONNECTION_TYPE:
					Log.d(TAG, "Launching settings");
					((Activity) mContext).finish(); 
					Intent l_intent;
					l_intent = new Intent(mContext, ConnTypeActivity.class);
					mContext.startActivity(l_intent);
					break;
			case SettingsConstants.MAIN_CH_SAT_HOMING_POLARISATION:
				if(enumVal == 0)
				{
					m_wrapper.SetPolarisationForCDHomingTransponder(true);
				}
				else
				{
					m_wrapper.SetPolarisationForCDHomingTransponder(false);
				}
				break;
			case SettingsConstants.CD_HOMING_SYMBOL_RATE_MODE:
				if(enumVal == 0)
				{
					m_wrapper.SetSymRateModeForCDHomingTransponder(true);
					revalidateControlabilityOfList(SettingsConstants.CD_HOMING_SYMBOL_RATE, false);
				}
				else
				{
					m_wrapper.SetSymRateModeForCDHomingTransponder(false);
					revalidateControlabilityOfList(SettingsConstants.CD_HOMING_SYMBOL_RATE, true);
				}
				break;
			case SettingsConstants.CD_LNB_ONE_LNBPOWER:
				m_wrapper.setLnbPower(0, (byte) enumVal);
				break;
			case SettingsConstants.CD_LNB_TWO_LNBPOWER:
				m_wrapper.setLnbPower(1, (byte) enumVal);
				break;
			case SettingsConstants.CD_LNB_THREE_LNBPOWER:
				m_wrapper.setLnbPower(2, (byte) enumVal);
				break;
			case SettingsConstants.CD_LNB_FOUR_LNBPOWER:
				m_wrapper.setLnbPower(3, (byte) enumVal);
				break;
		}
		mMenuBuilderInst.refreshUI();
	}

	public void revalidateControlabilityOfList(int pCookieId, boolean pIsControllable)
	{
		mMenuBuilderInst.onChanged(IChangeNotification.CONTROLLABLITY_CHANGE, pCookieId, pIsControllable);
	}

	@Override
	public void setObj(Context arg0, int arg1, Object arg2)
	{
		// TODO Auto-generated method stub
	}

	@Override
	public void unRegisterNodeChanges(IChangeNotification arg0)
	{
		// TODO Auto-generated method stub
	}

	@Override
	public void unRegisterNodeChanges(IChangeNotification MenuNodeChangeImpl, int cookie)
	{

	}

	@Override
	public void updateHelpContext(int contextLevel, String context) {
		Log.d(TAG,"updateHelpContext "+contextLevel+", "+context);
		if(mContext!=null && context!=null && !context.equals("")){
			//ContextHelper.getInstance().setContext(contextLevel, context);
		}
	}
	
	public void setLabel(int cookie, String lable)
	{
	}

	public void setIcons(int cookie, int value, String[] iconsarray)
	{
	}

}
