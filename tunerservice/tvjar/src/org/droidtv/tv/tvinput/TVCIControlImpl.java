package org.droidtv.tv.tvinput;

import java.util.List;
import java.util.ArrayList;
import android.os.IBinder;
import android.net.Uri;
import android.os.RemoteException;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Surface;
import org.droidtv.tv.context.ITvInterface;
import org.droidtv.tv.tvinput.ITVCIControl;
import org.droidtv.tv.tvinput.TVCIControlCallback;

/** @hide */
public interface TVCIControlImpl {

	public class Proxy implements ITVCIControl{	
		private static final String LOG_TAG = "TVCIControlImpl";
		TVCIControl mTVCIControl 	= null;
		ArrayList<ITVCIControlCallback> ciControlCallback = null;
		
		public Proxy(IBinder svc){
			//Log.i(LOG_TAG,"constructor of TVCIControlImpl proxy");
			if(svc != null){
				mTVCIControl 		= TVCIControl.Stub.asInterface(svc);
				ciControlCallback 	= new ArrayList<ITVCIControl.ITVCIControlCallback>();
			}
		}	
		
		@Override
		public void enableMMI(boolean enable) {
			Log.i(LOG_TAG,"enableMMI called");
			try {
				mTVCIControl.enableMMI(enable);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
		}

		@Override
		public void updateMMIStatus(boolean status) {
			Log.i(LOG_TAG,"updateMMIStatus called");
			try {
				mTVCIControl.updateMMIStatus(status);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
		}	
		
		@Override
		public void selectMMIItem(int menuType,int selectedItem) {
				Log.i(LOG_TAG,"selectMMIItem called");
				try {
					mTVCIControl.selectMMIItem(menuType,selectedItem);
				} catch (RemoteException e) {				
					throw new RuntimeException(e);
				}
				
		}
		
		@Override
		public String[] getMMIItems(int menuType) {
			Log.i(LOG_TAG,"getMMIItems called");
			try {
				return mTVCIControl.getMMIItems(menuType);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
		}
		
		@Override
		public int getLastSelectedMenuIndex() {
			Log.i(LOG_TAG,"getLastSelectedMenuIndex called");
			try {
				return mTVCIControl.getLastSelectedMenuIndex();
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
			
		}
		
		@Override
		public void setEnquiryMMIResponse(String answer) {
			Log.i(LOG_TAG,"setEnquiryMMIResponse called");
			try {
				mTVCIControl.setEnquiryMMIResponse(answer);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
		}

		@Override
		public CIMmiEnq getEnquiryMMIInfo() {
			Log.i(LOG_TAG,"getEnquiryMMIInfo called");
			try {
				return mTVCIControl.getEnquiryMMIInfo();
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
		}		
		
		@Override
		public void cancelMMI(int menutype){
			Log.i(LOG_TAG,"cancelMMI called");
			try {
				mTVCIControl.cancelMMI(menutype);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
			
		}
		
		@Override
		public void enableCamUpgrade(boolean enable){
			Log.i(LOG_TAG,"enableCamUpgrade called");
			try {
				mTVCIControl.enableCamUpgrade(enable);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
			
		}	
		
		@Override
		public int getCAMUpgradeStatus() {
			Log.i(LOG_TAG,"getCAMUpgradeStatus called");
			try {
				return mTVCIControl.getCAMUpgradeStatus();
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
		}		
		
		@Override
		public void updateCamInfo(CamInfo caminfo) {
			Log.i(LOG_TAG,"updateCamInfo called");
			CamInfoImpl obj = new CamInfoImpl(caminfo);
			try {
				mTVCIControl.updateCamInfo(obj);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
			
		}	
		@Override
		public void enableCAMUI(boolean enable) {
			Log.i(LOG_TAG,"enableCAMUI called");
			try {
				mTVCIControl.enableCAMUI(enable);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
		}
		
		
		@Override
		public CamInfo getCamInfo(int slotId) {
			Log.i(LOG_TAG,"getCamInfo called");
			try {
				return mTVCIControl.getCamInfo(slotId);
			} catch (RemoteException e) {				
				throw new RuntimeException(e);
			}
		}
		
		@Override
		public void registerCIControlListener(ITVCIControlCallback eventsCallback) {			
			//Log.i(LOG_TAG,"registerCIControlListener called");			
			boolean register = false;
			synchronized (ciControlCallback) {
				if(eventsCallback != null){
					if(ciControlCallback.size() == 0) {
						register = true;
					}
					if (ciControlCallback.contains(eventsCallback) == false) {
						ciControlCallback.add(eventsCallback);
						//Log.d(LOG_TAG,"Added into list");
					}
				}
				else{
					Log.d(LOG_TAG,"eventsCallback is null");
				}
			}
			if(register){
				try {
					//Log.d(LOG_TAG,"Added listener");
					mTVCIControl.registerCIControlListener(mCallStub);
				} catch (RemoteException e) {
					// TODO Auto-generated catch block
					throw new RuntimeException(e);
				}
			}
		}
			
		@Override
		public void unRegisterCIControlListener(ITVCIControlCallback eventsCallback) {
			Log.i(LOG_TAG,"unRegisterCIControlListener called");			
			boolean unregister = false;
			synchronized (ciControlCallback) {
				if (ciControlCallback.contains(eventsCallback) == true) {
					ciControlCallback.remove(eventsCallback);
				}
				if(ciControlCallback.size()==0){
				   unregister = true;
				}
			}

			if(unregister) {
				try {
					mTVCIControl.unRegisterCIControlListener(mCallStub);
				} catch (RemoteException e) {
					// TODO Auto-generated catch block
					throw new RuntimeException(e);
				}
			}			
		}
			
		TVCIControlCallback.Stub mCallStub = new TVCIControlCallback.Stub() {
			@Override
			public void onEvent(int slotID,int eventID,int value) {
				try {
					synchronized (ciControlCallback) {
						for (ITVCIControlCallback listener : ciControlCallback) {
							listener.onEvent(slotID,eventID,value);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw (e);
				}
				
			}
		};
	}
}
