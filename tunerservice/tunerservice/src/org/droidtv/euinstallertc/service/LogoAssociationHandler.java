package org.droidtv.euinstallertc.service;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DVBTOrDVBC;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.tvinput.ILogoAssociationControl.ILogoAssociationListener;

import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.util.Log;

// class for handling logo association, class handles one listener at a time
public class LogoAssociationHandler {

	private String TAG = LogoAssociationHandler.class.getName();
	private ILogoAssociationListner logoAssoRegisteredInst = null;
	private ILogoAssociationControl logoAssoInt = null;
	private ListenerImpl listener = new ListenerImpl();
	private DVBTOrDVBC currentMedium = DVBTOrDVBC.DVBT;

	public interface ILogoAssociationListner {
		// once logo association is complete callback is given to registeed
		// object
		public void notifyLogoAssociationComplete();
		public void notifyLogoAssociationAborted();
	}

	public void unRegisterLogoAssociationHandler() {
		logoAssoRegisteredInst = null;
	}

	public void startLogoAssociation(NativeAPIEnums.DVBTOrDVBC argMedium, ILogoAssociationListner argLogoAsso) {
		Log.d(TAG, "startLogoAssociation " + argMedium + " " + argLogoAsso);
		logoAssoRegisteredInst = argLogoAsso;
		currentMedium = argMedium;
		Intent intent = new Intent("org.droidtv.tvcontentprovider.LogoService");
		if (NativeAPIWrapper.getInstance().getApplicationServiceContext() != null) {
			((Service) NativeAPIWrapper.getInstance().getApplicationServiceContext()).bindService(intent, mConnection, Context.BIND_AUTO_CREATE);
		}else{
			// service not running 
			if (logoAssoRegisteredInst != null) {
				try {
					logoAssoRegisteredInst.notifyLogoAssociationAborted();
				} catch (Exception ex) {
					Log.d(TAG, "Caught exception");
				}
			}
		}
	}

	private ServiceConnection mConnection = new ServiceConnection() {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG, "ILogoAssociationControl called");

			logoAssoInt = ILogoAssociationControl.Instance.asInterface(service);
			if (logoAssoInt != null) {
				Log.d(TAG, "logoAssoInt is not null");
				logoAssoInt.registerListenerCallback(listener);
				if (DVBTOrDVBC.DVBC == currentMedium) {
					logoAssoInt.StartLogoAssociation(ILogoAssociationControl.MEDIUM_CABLE);
				} else {
					logoAssoInt.StartLogoAssociation(ILogoAssociationControl.MEDIUM_TERRESTRIAL);
				}

			} else {
				Log.d(TAG, "NULL logoAssoInt found");
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			// TODO Auto-generated method
			// stub

		}
	};

	public class ListenerImpl extends ILogoAssociationListener {

		@Override
		public void onLogoAssociationStateChanged(int state) {
			Log.d(TAG, "onLogoAssociationStateChanged called with State:" + state);

			if (state == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_COMPLETE) {
				Log.d(TAG, "Logo Association complete received");
				// unbind listner
				logoAssoInt.unregisterListenerCallback(listener);

				// unbind from logo service
				try {
					if (NativeAPIWrapper.getInstance().getApplicationServiceContext() != null) {
						((Service) NativeAPIWrapper.getInstance().getApplicationServiceContext()).unbindService(mConnection);
					}
				} catch (Exception ex) {
					Log.d(TAG, "Exception caught while unbinding service org.droidtv.tvcontentprovider.LogoService");
				}

				// give callback
				if (logoAssoRegisteredInst != null) {
					try {
						logoAssoRegisteredInst.notifyLogoAssociationComplete();
					} catch (Exception ex) {
						Log.d(TAG, "Caught exception");
					}
				}
			} else if (state == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_ABORTED) {
				// give callback

				// unbind listner
				logoAssoInt.unregisterListenerCallback(listener);

				// unbind from logo service
				try {
					if (NativeAPIWrapper.getInstance().getApplicationServiceContext() != null) {
						((Service) NativeAPIWrapper.getInstance().getApplicationServiceContext()).unbindService(mConnection);
					}
				} catch (Exception ex) {
					Log.d(TAG, "Exception caught while unbinding service org.droidtv.tvcontentprovider.LogoService");
				}

				if (logoAssoRegisteredInst != null) {
					try {
						logoAssoRegisteredInst.notifyLogoAssociationAborted();
					} catch (Exception ex) {
						Log.d(TAG, "Caught exception");
					}
				}
			} else if (state == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_STARTED) {
				// nothing to be done
			}
		}
	}

}
