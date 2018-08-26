/*
 *  Copyright(C) 2012 TP Vision Holding B.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of TP Vision Holding B.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of TP Vision Holding B.V.
 *
 */
package org.droidtv.tv.tvpower;

import org.droidtv.tv.tvpower.ITvSemiStandbyControl.ITvSemiStandbyCallback;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import org.droidtv.tv.context.ITvInterface;

/** @hide */
public interface TvSemiStandbyControlImpl {

	public class Stub extends TvSemiStandbyControl.Stub {
	
		ITvSemiStandbyControl intf = null;

		public Stub(ITvInterface service) {
			intf = (ITvSemiStandbyControl) service;
		}
    			
		@Override
		public void registerSemiStandbyAction(int actionid, IBinder listener) throws RemoteException {
			intf.registerSemiStandbyAction(actionid,(ITvSemiStandbyCallback)new TvSemiStandbyControlImpl.TvSemiStandbyNotify.Proxy(listener));
		}
		
		@Override
		public void unregisterSemiStandbyAction(int actionid) throws RemoteException {
			intf.unregisterSemiStandbyAction(actionid);
		}
		
        @Override
		public void setActionCompleted(int actionid) throws RemoteException {
			intf.setActionCompleted(actionid);
		}

        @Override
		public void setAlarmForSemiStandbyAction(int actionid, long nextAlarmTimeMSecs ) throws RemoteException {
			intf.setAlarmForSemiStandbyAction(actionid,nextAlarmTimeMSecs);
		}
	}

	public class Proxy implements ITvSemiStandbyControl {
		TvSemiStandbyControl remote = null;

		public Proxy(IBinder service) {
			remote = TvSemiStandbyControl.Stub.asInterface(service);
		}
		
		@Override
		public void registerSemiStandbyAction(int actionid,ITvSemiStandbyCallback listener) {
			try {
				remote.registerSemiStandbyAction(actionid,new TvSemiStandbyControlImpl.TvSemiStandbyNotify.Stub(listener).asBinder());
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
				
		@Override
		public void unregisterSemiStandbyAction(int actionid) {
			try {
				remote.unregisterSemiStandbyAction(actionid);
			}catch(Exception e) {
				e.printStackTrace();
			}
		}
		
        @Override
		public void setActionCompleted(int actionid) {
			try {
				remote.setActionCompleted(actionid);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}

        @Override
		public void setAlarmForSemiStandbyAction(int actionid, long nextAlarmTimeMSecs ) {
			try {
				remote.setAlarmForSemiStandbyAction(actionid,nextAlarmTimeMSecs);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
	}

	public interface TvSemiStandbyNotify {

		public class Stub extends TvSemiStandbyCallback.Stub {
			ITvSemiStandbyCallback intf = null;

			public Stub(ITvSemiStandbyCallback service) {
				intf = (ITvSemiStandbyCallback) service;
			}
			
			@Override
			public void onStartAction () throws RemoteException {
				intf.onStartAction();
			}
			
			@Override
			public void onStopAction () throws RemoteException {
				intf.onStopAction();
			}
			
			@Override
			public long onGetNextAlarm() throws RemoteException {
				return intf.onGetNextAlarm();
			}
			
			@Override
			public void onAlarmFired() throws RemoteException {
				intf.onAlarmFired();
			}
		}

		public class Proxy extends ITvSemiStandbyCallback {
			TvSemiStandbyCallback remote = null;

			public Proxy(IBinder service) {
				remote = TvSemiStandbyCallback.Stub.asInterface(service);
			}
						
			@Override
			public void onStartAction() {
				try {
					remote.onStartAction();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public void onStopAction() {
				try {
					remote.onStopAction();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public long onGetNextAlarm() {
				try {
					return remote.onGetNextAlarm();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
				return 0;
			}
			
			@Override
			public void onAlarmFired() {
				try {
					remote.onAlarmFired();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
		}
	}
}
