package org.droidtv.euinstallersat.wizard.satip;

import java.util.ArrayList;
import java.util.Observable;
import java.util.List;

import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.INotificationListener;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;


import org.droidtv.tv.frontend.ISatIpServer;


import android.content.Context;
import android.util.Log;

public class SatIPWrapper implements INotificationListener{
	public static final String TAG = SatIPWrapper.class.getName();

	protected Context ctx;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	protected NotificationHandler ntf = NotificationHandler.getInstance();
	private static SatIPWrapper singletonInstance = null;
	private ArrayList<ISatIpServer.SatIpServer> satIPServerList = null;
	private int selectedServerIndex = 0;
	private ISatIpServer.SatIpServer selectedServer = null;
	private int lnbIndex;
	private int satID;
	private boolean ifInstallationCompleted = false;
	private ISatIpServer m_satip = null; 
	private boolean enableSatIPSupport = false;

	private ISatIpServer.ISatIpServerStatusChangedListener satIpListener  = new ISatIpServer.ISatIpServerStatusChangedListener() {

	public void onSatIpServerStatusChanged(ISatIpServer.SatIpServer server,final int IsFound, final int isSelectedServer){

 			Log.d(TAG, "onSatIpServerStatusChanged for " + server.friendlyName + " is found: " + IsFound + " isSelectedServer: " + isSelectedServer);

			/*Add the server if it does not exist in the list*/
			if((IsFound == 1) && !(satIPServerList.contains(server))){
					Log.d(TAG, "Added server: " + server.friendlyName);
					satIPServerList.add(server);
			}/*Remove the server */
			else if((IsFound == 0) && satIPServerList.contains(server)){
					Log.d(TAG, "Removed server: " + server.friendlyName);
					satIPServerList.remove(server);
					if(isSelectedServer == 1){
						Log.d(TAG, "ERROR: Selected Server disconnected");
			}
			
			}
 		}	
	};
	
	private SatIPWrapper() {
		if(enableSatIPSupport){
			m_satip = ISatIpServer.Instance.getInterface();
			ntf.registerForNotification(this);
			satIPServerList = new ArrayList<ISatIpServer.SatIpServer>();
			selectedServerIndex = 0;
			m_satip.registerSatIpServerStatusChangeListener(satIpListener);
		}
	}
	
	private void reset(){
		lnbIndex = 0;
		
		ifInstallationCompleted = false;
	}
	
	// updated from prescan screens
	public void setSatIPSatelliteInfo(int lnbIndex, int satID){
		Log.d(TAG, "setSatIPSatelliteInfo " + lnbIndex + ", " + satID);
		this.lnbIndex = lnbIndex;
		this.satID = satID;
	}
	
	public String getSatIPSatelliteName(){
		String returnString = "";
		returnString = "Astra 19.2";
		Log.d(TAG, "getSatIPSatelliteName " + returnString);
		return returnString;
	}
	public boolean ifSatIPSatelliteAfterPrescan(){
		boolean returnStatus = (satID == MwDataTypes.ASTRA_19_2_E)?true:false;
		Log.d(TAG, "ifSatIPSatelliteAfterPrescan " + returnStatus);
		return returnStatus;
	}

	public boolean ifSatIPServerDetectedOnBoot() {
		boolean returnStatus = true;
		if(enableSatIPSupport){
			/*Sometimes getserverlist is crashing in tvplayer, */
			List<ISatIpServer.SatIpServer> serverList = m_satip.getServerList();
			returnStatus = serverList.isEmpty();
			Log.d(TAG, "ifSatIPDetectedDuringBootUp() " + (!returnStatus));
		}

		return (!returnStatus);
	}

	public static SatIPWrapper getInstance() {
		Log.d(TAG, "getInstance " + singletonInstance);
		if (singletonInstance == null) {
			singletonInstance = new SatIPWrapper();
		}
		return singletonInstance;
	}
	
	
	public ArrayList<ISatIpServer.SatIpServer> getSatIPServerList(){
		Log.d(TAG,"getSatIPServerList " + satIPServerList.size() );
		return satIPServerList;
	}
	
	public String[] getSatIPServerNameList(){
		String[] serverNameArray;
		if(enableSatIPSupport){
			int serverCount = satIPServerList.size();
			serverNameArray = new String[serverCount];
			
			for(int index=0; index<serverCount; index++){
				serverNameArray[index] = satIPServerList.get(index).friendlyName;
			}		
		}else{
			serverNameArray = new String[]{};
		}
		return serverNameArray;
	}
	
	public int getUserSelectedServer(){
		if(enableSatIPSupport){
			ISatIpServer.SatIpServer server = m_satip.getSelectedServerDetails();
			selectedServerIndex  = 0;
			String selectedUDN = server.UDN;
			Log.d(TAG,"getUserSelectedServer selected UDN " +  selectedUDN);
			for(int index=0;index< satIPServerList.size();index++){
				if(server.UDN.equalsIgnoreCase(selectedUDN)){
					selectedServerIndex = index;
					Log.d(TAG,"getUserSelectedServer server found at index " +  index);
					break;
				}
			}
			selectedServer = server;
			Log.d(TAG,"getUserSelectedServer index: " + selectedServerIndex + "name: " +  server.friendlyName);
		}
		
		return selectedServerIndex;
	}
	
	public void setUserSelectedServer(int serverIndex){
		Log.d(TAG,"setUserSelectedServer " + serverIndex );
		selectedServerIndex = serverIndex;
		if(enableSatIPSupport){
			ISatIpServer.SatIpServer server = satIPServerList.get(serverIndex);
			m_satip.selectServer(server);	
		}
		
	}

	public void storeUserSelectedServer(){
		Log.d(TAG,"storeUserSelectedServer " );
		if(enableSatIPSupport){
			m_satip.storeServer(selectedServer);		
		}
	}

	public void restoreUserSelectedServer(){
		Log.d(TAG,"restoreUserSelectedServer ");
		/*restore persistant server*/	
		if(enableSatIPSupport){
			m_satip.storeServer(null);	
		}
	}

	
	public void startSatIPSearch(){
		final int TimeOut = 2;
		Log.d(TAG,"startSatIPSearch() ");
		satIPServerList.clear();
		if(enableSatIPSupport){
			m_satip.searchServers(TimeOut);
		}
	}
	
	public void setSatIPInstallationDone(boolean ifInstDone){
		Log.d(TAG,"setSatIPInstallationDone() " + ifInstDone);
		ifInstallationCompleted = ifInstDone;
	}
	
	public boolean ifSatIPInstallationDone(){
		Log.d(TAG,"ifSatIPInstallationDone() " + ifInstallationCompleted);
		return ifInstallationCompleted;
	}
	
	@Override
	public void update(Observable arg0, Object data) {
		Log.d(TAG, "update: action " + ((NotificationInfoObject) data).actionID
				+ ", message " + ((NotificationInfoObject) data).message);
		final int l_eventID = ((NotificationInfoObject) data).actionID;
		switch (l_eventID) {
		case EventIDs.SERVICE_SCAN_COMPLETE:
			Log.d(TAG,"SERVICE_SCAN_COMPLETE");
			break;
		case EventIDs.INSTALLATION_FAILED:
			Log.d(TAG, "INSTALLATION_FAILED");
			break;
		}

		
	}
}
