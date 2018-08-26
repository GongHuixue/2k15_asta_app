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
package org.droidtv.tv.tvinput;

import org.droidtv.tv.tvinput.IInteractiveService.IInteractiveServiceCallBack;
import org.droidtv.tv.tvinput.InteractiveServiceCallBack;
import java.util.List;
import android.net.Uri;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.Surface;
import android.view.KeyEvent;
import org.droidtv.tv.context.ITvInterface;
import android.os.IBinder;
import android.graphics.Rect;

/** @hide */
public interface InteractiveServiceImpl {

	public class Stub extends InteractiveService.Stub implements IBinder.DeathRecipient{

		IInteractiveService intf = null;

		public Stub(ITvInterface service) {
			intf = (IInteractiveService) service;
		}
    
		@Override
		public void binderDied() {
			intf.setInteractiveServiceCallbackListener(null);
		}
		
		@Override
		public boolean onKeyEvent(KeyEvent event) throws RemoteException {
			boolean b = false;
			b = intf.onKeyEvent(event);
			return b;
		}
		
		@Override
		public void setSurface(Surface view)
				throws RemoteException {
			intf.setSurface(view);
		}
		
		@Override
		public void setVideoBackgroundSurface(Surface view)
				throws RemoteException {
			intf.setVideoBackgroundSurface(view);
		}
		
		@Override
		public void setInteractiveServiceCallbackListener(IBinder listener) throws RemoteException {
			intf.setInteractiveServiceCallbackListener((IInteractiveServiceCallBack)new InteractiveServiceImpl.InteractiveServiceNotify.Proxy(listener));
			//register for link to Death            
			listener.linkToDeath(this, 0);
		}

        @Override
		public void start() throws RemoteException {
			intf.start();
		}

        @Override
		public void stop() throws RemoteException {
			intf.stop();
		}
		
		@Override
		public void setMediaPlaybackSurfaces(List<Surface> surfacelist) throws RemoteException {
			intf.setMediaPlaybackSurfaces(surfacelist);
		}		
		public void startApp(String url)throws RemoteException {
			intf.startApp(url);
		}
	}

	public class Proxy implements IInteractiveService {

		InteractiveService remote = null;

		public Proxy(IBinder service) {
			remote = InteractiveService.Stub.asInterface(service);
			
		}

		@Override
		public void setSurface(Surface view) {
			try {
				remote.setSurface(view);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
		
		@Override
		public void setVideoBackgroundSurface(Surface view) {
			try {
				remote.setVideoBackgroundSurface(view);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}	
		
		@Override
		public boolean onKeyEvent(KeyEvent event) {
			boolean b = false;
			try {
				b = remote.onKeyEvent(event);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
			return b;
		}

		@Override
		public void setInteractiveServiceCallbackListener(IInteractiveServiceCallBack listener) {
			try {
				remote.setInteractiveServiceCallbackListener(new InteractiveServiceImpl.InteractiveServiceNotify.Stub(listener).asBinder());
			} catch (RemoteException e) {
				e.printStackTrace();
			}

		}

        @Override
		public void start() {
			try {
				remote.start();
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}

        @Override
		public void stop() {
			try {
				remote.stop();
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
		
		@Override
		public void setMediaPlaybackSurfaces(List<Surface> surfacelist) {
			try {
				remote.setMediaPlaybackSurfaces(surfacelist);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
		
		public void startApp(String url){
			try {
				remote.startApp(url);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}		
	}

	public interface InteractiveServiceNotify {

		public class Stub extends InteractiveServiceCallBack.Stub {
			IInteractiveServiceCallBack intf = null;

			public Stub(IInteractiveServiceCallBack service) {
				intf = (IInteractiveServiceCallBack) service;
			}
			
			@Override
			public void setVideoPosition(int TL, int TR, int BL, int BR)
					throws RemoteException {
				intf.setVideoPosition(TL, TR, BL, BR);

			}

			@Override
			public void onAppStarted () throws RemoteException {
				intf.onAppStarted();
			}
			
			@Override
			public void onAppExited () throws RemoteException{
				intf.onAppExited();
			}
			
			@Override
			public void requestVideoBackgroundSurface() {
				intf.requestVideoBackgroundSurface();
			}
			
			@Override
			public void releaseVideoBackgroundSurface() {
				intf.releaseVideoBackgroundSurface();
			}
			
			@Override
			public void requestMediaPlaybackSurfaces(int video_manager_cacheid) {
				intf.requestMediaPlaybackSurfaces(video_manager_cacheid);
			}
	
			@Override
			public void releaseMediaPlaybackSurfaces() {
				intf.releaseMediaPlaybackSurfaces();
			}
			
			@Override
			public void relayoutMediaPlaybackSurface(int surfaceindex, int width, int height){
				intf.relayoutMediaPlaybackSurface(surfaceindex,width,height);
			}
			
			@Override
			public void relayoutSurface(int width, int height) {
				intf.relayoutSurface(width,height);
			}
	
			@Override
			public void relayoutVideoBackgroundSurface(int width, int height) {
				intf.relayoutVideoBackgroundSurface(width,height);
			}

			public void invokeInteractiveApp(String url){
				intf.invokeInteractiveApp(url);			
			}			
			
            public void relayoutToDestinationRectangle(Rect r){
				intf.relayoutToDestinationRectangle(r);
			}			
			
		}

		public class Proxy extends IInteractiveServiceCallBack {
			InteractiveServiceCallBack remote = null;

			public Proxy(IBinder service) {
				remote = InteractiveServiceCallBack.Stub.asInterface(service);
			}
			
			@Override
			public void setVideoPosition(int TL, int TR, int BL, int BR) {
				try {
					remote.setVideoPosition(TL, TR, BL, BR);
				} catch (RemoteException e) {
					e.printStackTrace();
				}

			}
			
			@Override
			public void onAppStarted() {
				try {
					remote.onAppStarted();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public void onAppExited() {
				try {
					remote.onAppExited();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public void requestVideoBackgroundSurface() {
				try {
					remote.requestVideoBackgroundSurface();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public void releaseVideoBackgroundSurface() {
				try {
					remote.releaseVideoBackgroundSurface();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public void requestMediaPlaybackSurfaces(int video_manager_cacheid) {
				try {
					remote.requestMediaPlaybackSurfaces(video_manager_cacheid);
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void releaseMediaPlaybackSurfaces() {
				try {
					remote.releaseMediaPlaybackSurfaces();
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void relayoutMediaPlaybackSurface(int surfaceindex, int width, int height) {
				try {
					remote.relayoutMediaPlaybackSurface(surfaceindex,width,height);
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void relayoutSurface(int width, int height) {
				try {
					remote.relayoutSurface(width,height);
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			
			@Override
			public void relayoutVideoBackgroundSurface(int width, int height) {
				try {
					remote.relayoutVideoBackgroundSurface(width,height);
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			
			public void invokeInteractiveApp(String url){
				try {
					remote.invokeInteractiveApp(url);
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}						
            
            public void relayoutToDestinationRectangle(Rect r){
                try {    
    				remote.relayoutToDestinationRectangle(r);
                } catch(RemoteException e){
					e.printStackTrace();
                }           
            }			
		}
	}
}
