package org.droidtv.tv.tvinput;

import android.os.IBinder;
import android.os.RemoteException;
import java.lang.RuntimeException;
import java.lang.Exception;
import java.util.ArrayList;
import org.droidtv.tv.tvinput.ITVRecordPlayback;
import android.util.Log;
import android.net.Uri;

public interface TVRecordPlaybackImpl {

	public class Proxy implements ITVRecordPlayback {
		
		private static final String LOG_TAG			= "TVRecordPlaybackImpl";
		private TVRecordPlayback mRecordPlayback	= null;
		ArrayList<IRecordCallbacks> recordListner = null;
		
		public Proxy(IBinder pBinder){
			if(pBinder != null){
				mRecordPlayback		= TVRecordPlayback.Stub.asInterface(pBinder);
				recordListner		= new ArrayList<ITVRecordPlayback.IRecordCallbacks>();
			}			
		}
		
		public void pause(){
			Log.i(LOG_TAG,"pause called ");
			try{
				mRecordPlayback.pause();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}	
		}
		
		public void stop(){
			Log.i(LOG_TAG,"stop called");

			try{
				mRecordPlayback.stop();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}			
		}
	
		public void resume(){
			Log.i(LOG_TAG,"resume called");

			try{
				mRecordPlayback.resume();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public void seekTo(int msecs){
			Log.i(LOG_TAG,"seekTo called");

			try{
				mRecordPlayback.seekTo(msecs);
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public void setSpeed(int speed, boolean forward){
			Log.i(LOG_TAG,"setSpeed called");
			try{
				mRecordPlayback.setSpeed(speed , forward);
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public int getCurrentDuration(){
			Log.i(LOG_TAG,"getCurrentDuration called");
			try{
				return mRecordPlayback.getCurrentDuration();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public int getTotalDuration(){
			Log.i(LOG_TAG,"getTotalDuration called");
			try{
				return mRecordPlayback.getTotalDuration();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public int getBufferedDuration(){
			Log.i(LOG_TAG,"getBufferedDuration called");
			try{
				return mRecordPlayback.getBufferedDuration();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public int getPlaybackState(){
			Log.i(LOG_TAG,"getPlaybackState called");
			try{
				return mRecordPlayback.getPlaybackState();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public void enableTrickModes(boolean enable){
			Log.i(LOG_TAG,"enableTrickModes called");
			try{
				mRecordPlayback.enableTrickModes(enable);
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
	
		public boolean getTrickModeStatus(){
			Log.i(LOG_TAG,"getTrickModeStatus called");
			try{
				return mRecordPlayback.getTrickModeStatus();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}

		RecordCallbacks.Stub mCallStub = new RecordCallbacks.Stub() {
			@Override
			public void onSeekCompleted() {
				try {
					synchronized (recordListner) {
						for (IRecordCallbacks listener : recordListner) {
							listener.onSeekCompleted();
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}
			
			@Override
			public void onPlayError(int reason) {
				try {
					synchronized (recordListner) {
						for (IRecordCallbacks listener : recordListner) {
							listener.onPlayError(reason);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}
			
			@Override
			public void onTrickModeEnabled(boolean enable) {
				try {
					synchronized (recordListner) {
						for (IRecordCallbacks listener : recordListner) {
							listener.onTrickModeEnabled(enable);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}
			
			@Override
			public void onPlayStateChanged(int state) {
				try {
					synchronized (recordListner) {
						for (IRecordCallbacks listener : recordListner) {
							listener.onPlayStateChanged(state);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}
		};
		
		public void registerRecordCallback(IRecordCallbacks callback){
			Log.i(LOG_TAG,"registerRecordCallback called");			
			boolean register = false;
			synchronized (recordListner) {
				if(callback != null){
					if(recordListner.size() == 0) {
						register = true;
					}
					if (recordListner.contains(callback) == false) {
						recordListner.add(callback);
						Log.d(LOG_TAG,"Added into list");
					}
				}
				else{
					Log.d(LOG_TAG,"callback is null");
				}
			}
			if(register){
				try {
					Log.d(LOG_TAG,"Added listener");
					mRecordPlayback.registerRecordCallback(mCallStub);
				} catch (RemoteException e) {
					// TODO Auto-generated catch block
					throw new RuntimeException(e);
				}
			}
		}
	
		public void unregisterRecordCallbacks(IRecordCallbacks callback){
			Log.i(LOG_TAG,"unregisterRecordCallbacks called");
			boolean unregister = false;
			synchronized (recordListner) {
				if (recordListner.contains(callback) == true) {
					recordListner.remove(callback);
				}
				if(recordListner.size()==0){
				   unregister = true;
				}
			}
            if(unregister) {
				try {
					mRecordPlayback.unregisterRecordCallbacks(mCallStub);
				} catch (RemoteException e) {
					// TODO Auto-generated catch block
					throw new RuntimeException(e);
				}
            }			
		}
	}
}