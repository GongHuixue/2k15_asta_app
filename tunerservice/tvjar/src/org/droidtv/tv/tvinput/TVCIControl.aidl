package org.droidtv.tv.tvinput;

import android.os.IBinder;
import android.os.RemoteException;
import org.droidtv.tv.tvinput.CIMmiEnqImpl;
import org.droidtv.tv.tvinput.CamInfoImpl;

/**
 * All the CI Application functionality is exposed via this interface. This is implemented by
 */
/** @hide */
interface TVCIControl{  	  
	void enableMMI(boolean enableStatus);   
	void updateMMIStatus (boolean status);	
	void selectMMIItem(int menuType,int selectedItem);	
	String[] getMMIItems(int menuType);	
	int getLastSelectedMenuIndex();	
	void setEnquiryMMIResponse(String answer);	
	CIMmiEnqImpl getEnquiryMMIInfo();	
	void cancelMMI(int menuType);	
	void enableCamUpgrade(boolean enable); 
	int getCAMUpgradeStatus();
	void updateCamInfo(in CamInfoImpl caminfo);	
	void enableCAMUI(boolean enable);
	CamInfoImpl getCamInfo(int slotId);
	void registerCIControlListener(IBinder eventsCallback);	
	void unRegisterCIControlListener(IBinder eventsCallback);	
}

