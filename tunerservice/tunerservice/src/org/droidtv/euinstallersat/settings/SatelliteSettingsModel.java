package org.droidtv.euinstallersat.settings;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.Observable;

import org.droidtv.euinstallersat.model.mwapi.LnbSettingsEntry;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.IApplication.ListData;

import android.content.Context;
import android.util.Log;

public class SatelliteSettingsModel implements ISettingsNotificationListener
{
	private static final String TAG = SatelliteSettingsModel.class.getName();
	Context m_context;
	NativeAPIWrapper m_wrapper;
	IDataChangeListener m_dataChangeListener;
	ArrayList<Integer> m_autoUpdateLNBIdx;
	int[] m_automaticUpdateIdArray;
	int[] m_startUpMessageIdArray;
	int[] m_predefinedSymbolRateArray;

	int INDEX_OFF = 0;
	int INDEX_ON = 1;

	int INDEX_AUTOMATIC = 0;
	int INDEX_MANUAL = 1;

	int INDEX_WEST_EUROPE = 0;
	int INDEX_EAST_EUROPE = 1;
	int INDEX_UK = 2;
	int INDEX_FRANCE = 3;

	int INDEX_ANTENNA = 0;
	int INDEX_CABLE = 1;

	public SatelliteSettingsModel(Context p_context)
	{
		Log.d(TAG,"SatelliteSettingsModel constructor");
		m_context = p_context;
		m_wrapper = NativeAPIWrapper.getInstance();
		NotificationHandler.getInstance().registerForNotification(this);
		m_automaticUpdateIdArray = m_context.getResources().getIntArray(R.array.automaticUpdateOptions);
		m_startUpMessageIdArray = m_context.getResources().getIntArray(R.array.startupMessageOptions);
		m_predefinedSymbolRateArray = m_context.getResources().getIntArray(R.array.predefinedSymbolRateArray);
		m_autoUpdateLNBIdx = new ArrayList<Integer>();
	}

	public boolean getControllablityOfNode(int p_nodeId)
	{
		Log.d(TAG, "getControllablityOfNode");
		Boolean l_ret = true;
		switch (p_nodeId)
		{
			case SettingsConstants.MAIN_AUTOMATIC_CHANNEL_UPDATE:
				l_ret = m_wrapper.isAutoChanUpdateControllable();
				break;
			case SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION:
				l_ret = m_wrapper.isAutoUpListControllable();
				break;
			case SettingsConstants.MAIN_SYMBOL_RATE:
				l_ret = m_wrapper.isSymbolRateControllable();
				break;
			case SettingsConstants.CD_HOMING_SYMBOL_RATE:
				l_ret = m_wrapper.isCDHomingSymbolRateControllable();
				break;
			case SettingsConstants.MAIN_REORDER:
				//l_ret = m_wrapper.isReorderControllable();
				l_ret = false;
				break;
			case SettingsConstants.LNB_SELECTION:
				l_ret = m_wrapper.ifLNBSelectionControllable();
				break;
			default:
				l_ret = true;
		}
		return l_ret;
	}
	
	public boolean getControllabilityOfLeafNode(int nodeResId, int dataId)
	{
		Log.d(TAG, "getControllabilityOfLeafNode for dataId" + dataId);
		boolean l_ret = true;
		switch(nodeResId)
		{
			case SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION:
				Log.d(TAG,"MAIN_AUTOMATIC_UPDATE_OPTION");
				if(!m_wrapper.IsLNBInstalled(m_autoUpdateLNBIdx.get(dataId)))
				{
					l_ret = false;
				}
				break;
		}
		Log.d(TAG, "getControllabilityOfLeafNode returning" + l_ret);
		return l_ret;
	}

	public boolean getAvailabilityOfNode(int p_nodeId)
	{
		Log.d(TAG, "getAvailabilityOfNode");
		Boolean l_ret = true;
		switch (p_nodeId)
		{
			/*case SettingsConstants.MISC_TUNER:
				l_ret = m_wrapper.IsDualTunerOn();
				break;*/
			case SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION:
				l_ret = m_wrapper.isAutoUpListAvailable();
				break;
			case SettingsConstants.MAIN_MANUAL_INSTALLATION:
				if(m_wrapper.isPackageFreesat() == true)
				{
					l_ret = false;
				}
				break;
			case SettingsConstants.MAIN_DIGITAL_TEST_RECEPTION:
				if(!m_wrapper.isPackageFreesat())
				{
					l_ret = false;
				}
				break;
			case SettingsConstants.MISC_TUNER:
			if ((!m_wrapper.isPackageFreesat()) && 
					m_wrapper.IsDualTunerOn() &&
					(m_wrapper.ifSatIPConnectionType() == false)) {
				l_ret = true;
			} else {
				l_ret = false;
			}
			break;
		case SettingsConstants.MAIN_HOMING_TRANSPONDER:
			 if((m_wrapper.GetIsNordicCountry() == true) &&
					 (m_wrapper.ifSatIPConnectionType() == false)){
				 l_ret = true;
			 }else{
				 l_ret = false;
			 }
			
			break;
		case SettingsConstants.CD_LNB_SETTINGS:
			Log.d(TAG, "CD_LNB_TWO_SETTINGS");
		    l_ret = m_wrapper.IsLnbSettingsAvailable();
			Log.d(TAG, "CD_LNB_TWO_SETTINGS" + l_ret);
			break;	
		case SettingsConstants.CD_LNB_TWO_SETTINGS:
			Log.d(TAG, "CD_LNB_TWO_SETTINGS");
			int l_connType = m_wrapper.getConnectionType();
			if((LnbSettingsEntry.LnbConnectionDiSeqcMini != l_connType)&&
			   (LnbSettingsEntry.LnbConnectionDiSeqc1_0 != l_connType)&&
			   (LnbSettingsEntry.LnbConnectionUnicableSwitch != l_connType) 
			  ) 
			{
					l_ret = false;
			}
			
			if(m_wrapper.ifSatIPConnectionType()){
				l_ret = false;
			}
			Log.d(TAG, "CD_LNB_TWO_SETTINGS" + l_ret);
			break;
		case SettingsConstants.CD_LNB_THREE_SETTINGS:
		case SettingsConstants.CD_LNB_FOUR_SETTINGS:
			if(LnbSettingsEntry.LnbConnectionDiSeqc1_0 != m_wrapper.getConnectionType())
			{
					l_ret = false;
			}
			
			if(m_wrapper.ifSatIPConnectionType()){
				l_ret = false;
			}
			break;
		case SettingsConstants.CD_LNB_ONE_LNBPOWER:
		case SettingsConstants.CD_LNB_TWO_LNBPOWER: 
			l_ret = m_wrapper.IsLnbPowerAvailable();
		break;
		case SettingsConstants.MAIN_SAT_IP_FEC: 
		case SettingsConstants.MAIN_SAT_IP_MODULATION_SYSTEM: 
		case SettingsConstants.MAIN_SAT_IP_MODULATION_TYPE:
		case SettingsConstants.MAIN_SAT_IP_ROLL_OFF:
		case SettingsConstants.MAIN_SAT_IP_PILOTS:
			l_ret = m_wrapper.ifSatIPConnectionType();
		break;
		case SettingsConstants.MAIN_REORDER: 
			l_ret = false;
		break;
		default:
			l_ret = true;
			break;
		}
		return l_ret;
	}
	
	public boolean getAvailabilityOfLeafNode(int p_nodeId, int p_dataId)
	{
		Log.d(TAG, "getAvailabilityOfLeafNode entry" + p_dataId);
		boolean l_ret = true;
		switch(p_nodeId)
		{
			case SettingsConstants.MAIN_POLARISATION:
				Log.d(TAG,"MAIN_POLARISATION");
				break;
			case SettingsConstants.MAIN_REORDER: 
				l_ret = false;
			break;
		}
		Log.d(TAG, "getAvailabilityOfLeafNode returning" + l_ret);
		return l_ret;
	}

	public void selectDynamicItem(int p_nodeId, int p_dataId)
	{
		Log.d(TAG, "selectDynamicItem cookie: " + p_nodeId +  ",val: " + p_dataId);
		boolean l_controllability = true;
		switch (p_nodeId)
		{
			case SettingsConstants.MAIN_AUTOMATIC_CHANNEL_UPDATE:
				Log.d(TAG, "selection for MAIN_AUTOMATIC_UPDATE_OPTION");
				if (p_dataId == 0)
				{
					m_wrapper.SetAutoChanUpdate(false);
				}
				else
				{
					m_wrapper.SetAutoChanUpdate(true);
				}
				l_controllability = m_wrapper.isAutoUpListControllable();
				m_dataChangeListener.onControllabilityChanged(SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION, l_controllability);
				break;
			case SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION:
				// p_dataId is the enum value passed directly
				// m_wrapper.SetInsAutUpOptionList(p_dataId);
				break;
			case SettingsConstants.MISC_LNB:
				m_wrapper.SetManualInstallLNB(p_dataId);
				break;
			case SettingsConstants.MAIN_CH_SAT_HOMING_POLARISATION:
				if(p_dataId == 0)
				{
					m_wrapper.SetPolarisationForCDHomingTransponder(true);
				}
				else
				{
					m_wrapper.SetPolarisationForCDHomingTransponder(false);
				}
				break;
			case SettingsConstants.MAIN_POLARISATION:
				if(p_dataId == 0)
				{
					m_wrapper.SetPolarisation(true);
				}
				else
				{
					m_wrapper.SetPolarisation(false);
				}
				break;
			case SettingsConstants.MAIN_SYMBOL_RATE_MODE:
				if(p_dataId == 0)
				{
					m_wrapper.SetSymRateMode(true);
					m_dataChangeListener.onControllabilityChanged(SettingsConstants.MAIN_SYMBOL_RATE, false);
				}
				else
				{
					m_wrapper.SetSymRateMode(false);
					m_dataChangeListener.onControllabilityChanged(SettingsConstants.MAIN_SYMBOL_RATE, true);
				}
				break;
			case SettingsConstants.MISC_TUNER:
				if(p_dataId == 0){
					m_wrapper.setTuner2Active(false);
				}else
				{
					m_wrapper.setTuner2Active(true);
				}
				break;
			case SettingsConstants.CD_HOMING_SYMBOL_RATE_MODE:
				if(p_dataId == 0)
				{
					m_wrapper.SetSymRateModeForCDHomingTransponder(true);
					m_dataChangeListener.onControllabilityChanged(SettingsConstants.CD_HOMING_SYMBOL_RATE, false);
				}
				else
				{
					m_wrapper.SetSymRateModeForCDHomingTransponder(false);
					m_dataChangeListener.onControllabilityChanged(SettingsConstants.CD_HOMING_SYMBOL_RATE, true);
				}
				break;
			case SettingsConstants.CD_LNB_ONE_LNBPOWER:
				m_wrapper.setLnbPower(0, (byte) p_dataId);
				break;
			case SettingsConstants.CD_LNB_TWO_LNBPOWER:
				m_wrapper.setLnbPower(1, (byte) p_dataId);
				break;
			case SettingsConstants.CD_LNB_THREE_LNBPOWER:
				m_wrapper.setLnbPower(2, (byte) p_dataId);
				break;
			case SettingsConstants.CD_LNB_FOUR_LNBPOWER:
				m_wrapper.setLnbPower(3, (byte) p_dataId);
				break;
		}
	}

	public int getSelectedItem(int p_nodeId)
	{
		Log.d(TAG, "getSelectedItem");
		Log.d(TAG, String.valueOf(p_nodeId));
		int l_ret = 0;
		switch (p_nodeId)
		{
			case SettingsConstants.MAIN_AUTOMATIC_CHANNEL_UPDATE:
				l_ret = m_wrapper.GetAutoChanUpdate();
				break;
			case SettingsConstants.MISC_LNB:
				l_ret = m_wrapper.GetManualInstallLNB();
				break;
			case SettingsConstants.CD_HOMING_SYMBOL_RATE_MODE:
				l_ret = m_wrapper.GetSymRateModeForCDHomingTransponder();
				break;
			case SettingsConstants.MAIN_SYMBOL_RATE_MODE:
				l_ret = m_wrapper.GetSymRateMode();
				break;
			case SettingsConstants.MAIN_CH_SAT_HOMING_POLARISATION:
				if(m_wrapper.GetPolarisationForCDHomingTransponder() == MwDataTypes.PolarisationVertical)
				{
					l_ret = 0;
				} else {
					l_ret = 1;
				}
				break;
			case SettingsConstants.MAIN_POLARISATION:
				if(m_wrapper.GetPolarisation() == MwDataTypes.PolarisationVertical)
				{
					l_ret = 0;
				} else {
					l_ret = 1;
				}
				break;
				
			case SettingsConstants.MISC_TUNER:
				if(m_wrapper.isTuner2Active()){
					l_ret = 1;
				}else
				{
					l_ret = 0;
				}
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
		Log.d(TAG, "getSelectedItem exit " + l_ret);
		return l_ret;
	}

	public void selectItem(int p_nodeId)
	{
		Log.d(TAG, "selectItem");
		Log.d(TAG, String.valueOf(p_nodeId));
		switch (p_nodeId)
		{
			case SettingsConstants.MAIN_MANUAL_INSTALLATION:
				m_wrapper.SetManualInstMenu();
				break;
			
		}
	}

	// equivalent of onFocusGained
	public void onNodeItemSelected(int p_nodeId)
	{
		Log.d(TAG, "onNodeItemSelected");
		switch (p_nodeId)
		{

		}
	}

	// TODO : check when this is called??
	public void onMovingBackwardFromNode(int p_nodeId)
	{
		Log.d(TAG, "onMovingBackwardFromNode");
		switch (p_nodeId)
		{

		}
	}

	public ArrayList<ListData> getAUOListData(){
		ArrayList<ListData> returnListData = new ArrayList<ListData>();
		int maxLNBCount =  m_wrapper.getLNBCount();
		Log.d(TAG,"getAUOListData maxLNBCount: " + maxLNBCount );
		
		m_autoUpdateLNBIdx.clear();
		
		if (m_wrapper.isAutoUpListAvailable()){
			for(int lnbIndex = 0; lnbIndex < maxLNBCount; lnbIndex++){
				if(false == m_wrapper.IsLNBFree(lnbIndex)){
					ListData lData = new ListData();
					lData.cookie = lnbIndex;
					lData.label = m_wrapper.GetSatelliteName(lnbIndex);
					returnListData.add(lData);
					Log.d(TAG,"getAUOListData label: " + lData.label + ", cookie: " + lData.cookie);
					
					// used global variable
					m_autoUpdateLNBIdx.add(lnbIndex);
				}
			}
		}
		
		if(returnListData.isEmpty()){
			Log.d(TAG,"Automatic update list is empty, setting controllability to false");
			m_dataChangeListener.onControllabilityChanged(SettingsConstants.MAIN_AUTOMATIC_UPDATE_OPTION, false);
		}
		
		return returnListData;
	}
	
	public void setAUOCheckedLNBs(int[] checkedArray){
		int maxAUOLNBCount =  m_autoUpdateLNBIdx.size();
		Log.d(TAG,"setAUOCheckedLNBs maxAUOLNBCount: " + maxAUOLNBCount );
		
		for(int lnbIndex = 0;lnbIndex<checkedArray.length;lnbIndex++){
			Log.d(TAG,"setAUOCheckedLNBs lnbIndex: " +  checkedArray[lnbIndex] );
		}
		
		Iterator<Integer> lnbListIter = m_autoUpdateLNBIdx.iterator();
		int currentLNBIndex = 0;
		boolean ifPresentInCheckedItems = false;
		while(lnbListIter.hasNext()){
			currentLNBIndex = lnbListIter.next();
			ifPresentInCheckedItems = false;
			for(int lnbIndex = 0;lnbIndex<checkedArray.length;lnbIndex++){
				if(currentLNBIndex == checkedArray[lnbIndex]){
					ifPresentInCheckedItems = true;
					break;
				}
			}
			if(ifPresentInCheckedItems){
				m_wrapper.SetInsAutUpOptionList(currentLNBIndex,true);
			}else{
				m_wrapper.SetInsAutUpOptionList(currentLNBIndex,false);
			}
		}
	}
	
	public int[] getAUOCheckedLNBs(){
		int[] returnLNBArray = new int[]{};
		ArrayList<Integer> lnbList = new ArrayList<Integer>();
		
		int maxAUOLNBCount =  m_autoUpdateLNBIdx.size();
		Log.d(TAG,"getAUOCheckedLNBs maxAUOLNBCount: " + maxAUOLNBCount );
		
		Iterator<Integer> lnbListIter = m_autoUpdateLNBIdx.iterator();
		int currentLNBIndex = 0;
		while(lnbListIter.hasNext()){
			currentLNBIndex = lnbListIter.next();
			if(true == m_wrapper.GetInsUpdateSatelliteChecked(currentLNBIndex)){
				lnbList.add(currentLNBIndex);
				Log.d(TAG,"getAUOCheckedLNBs currentLNBIndex: " + currentLNBIndex );
			}
		}
		
		if(lnbList.size() > 0){
			returnLNBArray = new int[lnbList.size()];
			
			// convert Arraylist to int[]
			
			for(int checkedLnbIndex = 0;checkedLnbIndex < lnbList.size();checkedLnbIndex++){
				returnLNBArray[checkedLnbIndex] = lnbList.get(checkedLnbIndex);
			}
		}
		Log.d(TAG,"getAUOCheckedLNBs returnLNBArray: " + Arrays.toString(returnLNBArray));
		return returnLNBArray;
	}

	public String[] getDataForNode(int p_nodeResId)
	{
		Log.d(TAG, "getDataForNode");
		String[] l_retArray = new String[20];
		switch (p_nodeResId)
		{
			case SettingsConstants.MAIN_POLARISATION:
				int l_satId = m_wrapper.GetSatDetectedID(m_wrapper.GetManualInstallLNB());
				if (l_satId == MwDataTypes.EUTELSAT_W4_36E)
				{
					l_retArray = new String[]{m_context.getString(org.droidtv.ui.strings.R.string.MAIN_RIGHT_HAND_CIRCULAR),
						m_context.getString(org.droidtv.ui.strings.R.string.MAIN_LEFT_HAND_CIRCULAR)
					};
				}
				else
				{
					l_retArray = new String[]{m_context.getString(org.droidtv.ui.strings.R.string.MAIN_VERTICAL),
						m_context.getString(org.droidtv.ui.strings.R.string.MAIN_HORIZONTAL)
					};
				}
				break;
			case SettingsConstants.MISC_LNB:
			{
				l_retArray = getLNBList();
			}
			break;
		}
		return l_retArray;
	}

	private String[] getLNBList()
	{
		Log.d(TAG,"getLNBList entry");
		int l_lnbCount = m_wrapper.getLNBCount();
		int l_idx;
		String l_name;
		String l_retArr[] = new String[l_lnbCount];
		for(l_idx = 0; l_idx < l_lnbCount; l_idx++)
		{
			if(m_wrapper.IsLNBFree(l_idx))
			{
				l_name = m_context.getString(org.droidtv.ui.strings.R.string.MAIN_NONE);
			}
			else
			{
				l_name = m_wrapper.GetSatelliteName(l_idx);
			}
			Log.d(TAG,"l_name = " + l_name);
			l_retArr[l_idx] = l_name;
		}
		Log.d(TAG,"getLNBList exit");
		return l_retArr;
	}

	public void addDataChangeListener(IDataChangeListener p_listener)
	{
		m_dataChangeListener = p_listener;
	}

	public void removeDataChangeListener()
	{
		m_dataChangeListener = null;
	}
	

	@Override
	public void update(Observable observable, Object data)
	{
		Log.d(TAG, "update: action " + ((NotificationInfoObject) data).actionID + ", message " + ((NotificationInfoObject) data).message);
		final int l_eventID = ((NotificationInfoObject) data).actionID;
		switch (l_eventID)
		{

			case EventIDs.USB_UPDATE_FAIL_CHECK_USB:
				m_dataChangeListener.showNotification(org.droidtv.ui.strings.R.string.MAIN_MSG_SORTING_LIST_UPDATE_GENERIC_ERROR);
				break;
			case EventIDs.USB_UPDATE_FAIL_OLD_VERSION:
				m_dataChangeListener.showNotification(org.droidtv.ui.strings.R.string.MAIN_MSG_SORTING_LIST_UPDATE_OLDER_VERSION);
				break;
			case EventIDs.USB_UPDATE_SUCCESS:
				m_dataChangeListener.showDialog(org.droidtv.ui.strings.R.string.MAIN_DI_SORTING_LIST_UPDATE_SUCCESSFUL);
				break;

		}

	}

}
