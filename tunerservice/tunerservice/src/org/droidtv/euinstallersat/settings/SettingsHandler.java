package org.droidtv.euinstallersat.settings;

import java.util.ArrayList;

import org.droidtv.euinstallersat.util.ContextHelper;
import org.droidtv.euinstallersat.util.SatelliteConstants;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeActivity;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuBuilder;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IChangeNotification;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class SettingsHandler implements IApplication, IDataChangeListener
{

	private final String TAG = SettingsHandler.class.getName();
	// single instance holder
	private volatile static SettingsHandler mHandlerInstance = null;
	private Context mContext;
	private MenuBuilder mMenuBuilderInst;
	private SatelliteSettingsModel mSettingsModel;

	private SettingsHandler()
	{
	}

	// get single instance of NotificationHandler class
	public static synchronized SettingsHandler getInstance() {
		if (mHandlerInstance == null) {
			mHandlerInstance = new SettingsHandler();
		}
		return mHandlerInstance;
	}

	public void setContext(Context argCtx, MenuBuilder argMenuBuilderInst)
	{
		Log.d(TAG,"setContext " + argCtx);
		mContext = argCtx;
		mMenuBuilderInst = argMenuBuilderInst;
		initSettingsHandler(argCtx);
	}
	
	private void initSettingsHandler(Context argCtx){
		
		if(null == mContext){
			mContext = argCtx;
		}
		if(null == mSettingsModel){
			Log.d(TAG,"initSettingsHandler " + argCtx);
			mSettingsModel = new SatelliteSettingsModel(argCtx);
			mSettingsModel.addDataChangeListener(this);
		}
	}

	@Override
	public void dump(String arg0, String arg1, String arg2)
	{

	}

	@Override
	public String[] getIcons(Context arg0, int arg1, int arg2)
	{
		return null;
	}

	@Override
	public String getLabel(Context arg0, int arg1, int arg2)
	{
		Log.d(TAG,"getLabel entry for cookie " + arg1 + "and arg2 : " + arg2);
		return null;
	}

	@Override
	public ArrayList<ListData> getListData(Context arg0, int pId)
	{
		Log.d(TAG,"getListData entry for cookie " + pId);
		ArrayList<ListData> lListData = null;
		
		switch (pId)
		{
			case SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION:
				lListData = mSettingsModel.getAUOListData();
			break;
			case SettingsConstants.MISC_LNB:
			case SettingsConstants.MAIN_POLARISATION:
				String[] l_data;
				int lIdx = 0;
				l_data = mSettingsModel.getDataForNode(pId);
				
				if(l_data!=null)
				{
					lListData = new ArrayList<ListData>();
					for(lIdx = 0; lIdx < l_data.length; lIdx ++)
					{
						ListData lData = new ListData();
						lData.cookie = lIdx;
						lData.label = l_data[lIdx];
						Log.d(TAG,"setting label to : " + lData.label);
						lListData.add(lData);
						
					}
				}
				break;
		}
		
		return lListData;
	}

	@Override
	public Object getObj(Context context, int cookie) {
		Log.d(TAG,"getObj cookie:" +  cookie);
		
		int[] lSelectedItems = new int[]{};
		if(cookie == SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION){
			lSelectedItems = mSettingsModel.getAUOCheckedLNBs();
		}
		
		return lSelectedItems;
	}

	@Override
	public boolean isAvailable(Context ctx, int cookieID, int enumVal)
	{
		Log.d(TAG, "isAvailable enter cookieID:" + cookieID + " enumVal:" + enumVal);
		initSettingsHandler(ctx);
		return mSettingsModel.getAvailabilityOfNode(cookieID);
	}

	@Override
	public boolean isControllable(Context ctx, int cookieID, int enumVal)
	{
		Log.d(TAG, "isControllable enter cookieID:" + cookieID + " enumVal:" + enumVal);
		initSettingsHandler(ctx);
		return mSettingsModel.getControllablityOfNode(cookieID);
	}

	@Override
	public boolean isNodeLocked(Context ctx, int cookieID)
	{

		return false;
	}

	@Override
	public void onNodeEntered(Context ctx, int cookieID)
	{
		Log.d(TAG, "onNodeEntered cookieID: " + cookieID);


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
		Log.d(TAG, "getInt enter cookieID:" + cookieID);
		initSettingsHandler(ctx);
		return mSettingsModel.getSelectedItem(cookieID);
	}

	@Override
	public void setInt(Context ctx, int cookieID, int enumVal)
	{
		Log.d(TAG, "setInt cookieID:" + cookieID + " enumVal:" + enumVal);
		Intent intent;
		switch (cookieID)
		{
			case SettingsConstants.MAIN_SEARCH_FOR_SATELLITE:
				Log.d(TAG, "Launching wizard");
				intent = new Intent(mContext, SatelliteInstallationActivity.class);
				intent.putExtra("LaunchMode", "LaunchFromSettings");
				((Activity)mContext).startActivityForResult(intent, SatelliteConstants.REQUEST_CODE_LAUNCH_WIZARD_FROM_SETTINGS);
				break;
			case SettingsConstants.MAIN_SEARCH:
				Log.d(TAG, "Launching DTR");
				//m_settingsManager.collapseNPanel();
				//DTRScreen dtr = (DTRScreen) m_settingsManager.findSettingsNodeById(R.id.MAIN_SEARCH);
				//dtr.m_isCollapsed = true;
				//dtr.setColourKeyManager(m_colourKeyManager);
				//m_settingsManager.updatePanel_2(dtr.loadCustomView());
				break;
			case SettingsConstants.MAIN_REORDER:
				intent = new Intent(TvIntent.ACTION_REORDER_CHANNELS);
				intent.putExtra(TvIntent.CHANNELS_REORDER_TUNER_TYPE, TvIntent.CHANNELS_REORDER_SATELLITE);
				((Activity)mContext).startActivity(intent);
				((Activity)mContext).finish();
				break;
			case SettingsConstants.LNB_SELECTION:
				Log.d(TAG, "Launching LNB Selection Wizard Screen");
				((Activity) mContext).finish(); 
				intent = new Intent(mContext, ConnTypeActivity.class);
				intent.putExtra("LaunchScreen", "LNBSelection");
				mContext.startActivity(intent);
				break;
			default:
				mSettingsModel.selectDynamicItem(cookieID, enumVal);
				mSettingsModel.selectItem(cookieID);
				break;
		}
		
		mMenuBuilderInst.refreshUI();
	}

	@Override
	public void setObj(Context context, int cookie, Object value) {
		Log.d(TAG, "setObj cookie: " + cookie + " value:" + value);
		
		if(cookie == SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION){
			int[] data = (int[])value;
			if(data != null){
				for(int lnbIndex = 0;lnbIndex<data.length;lnbIndex++){
					Log.d(TAG,"setObj lnbIndex: " +  data[lnbIndex] );
				}
				mSettingsModel.setAUOCheckedLNBs(data);
				/*for(int index = 0 ; index < data.length ; index++){
					Log.d(TAG,"setObj index: " + index + " ,val: "+ data[index]);
					mSettingsModel.selectDynamicItem(cookie, data[index]);
				}*/
			}
		}
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
			ContextHelper.getInstance().setAppContext(mContext);
			ContextHelper.getInstance().setContext(contextLevel, context);
		}
	}
	
	public void setLabel(int cookie, String lable)
	{
	}

	public void setIcons(int cookie, int value, String[] iconsarray)
	{
	}
	
	public void onControllabilityChanged(int p_nodeId, boolean p_isControllable)
	{
		Log.d(TAG, "onControllabilityChanged " + p_nodeId + "p_isControllable = "+ p_isControllable);
		mMenuBuilderInst.onChanged(IChangeNotification.CONTROLLABLITY_CHANGE, p_nodeId, p_isControllable);
	}

	@Override
	public void showNotification(int p_notificationStringId)
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showDialog(int p_msgStringId)
	{
		// TODO Auto-generated method stub
		
	}

}
