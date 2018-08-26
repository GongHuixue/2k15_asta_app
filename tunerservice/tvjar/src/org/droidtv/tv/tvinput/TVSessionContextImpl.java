package org.droidtv.tv.tvinput;

import android.os.IBinder;
import android.os.Parcelable;
import android.os.Parcel;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import java.lang.String;
import java.lang.Exception;
import java.util.ArrayList;
import org.droidtv.tv.context.*;
import org.droidtv.tv.broadcast.*;
import org.droidtv.tv.media.*;
import org.droidtv.tv.frontend.*;
import org.droidtv.tv.audio.*;
import org.droidtv.tv.video.*;
import org.droidtv.tv.upgrade.*;
import org.droidtv.tv.tvinput.ITVRecordPlayback;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tv.tvinput.ITVCIControl;
import org.droidtv.tv.media.TvMediaPlayerContext;

public class TVSessionContextImpl implements ITVSessionContext {

	//IBinder mRemote = null;
	TVSessionContext mRemote = null;
	ArrayList<ISessionContextCallbacks> sessionContextListner = null;
	private final static String LOG_TAG = "TVSessionContextImpl";
	TvMediaPlayerContext mTvmplContext 			= null;
	private ITVTunerSession	mTvTunerSession	    = null;
	private ITVRecordPlayback mTvRecordPlayback	= null;
	private ITVCIControl mTvCIControl			= null;
	private ITVExtensionSession mTvExtensionSession = null;
	
	public TVSessionContextImpl (IBinder service){
		mRemote 				= TVSessionContext.Stub.asInterface(service);
		sessionContextListner 	= new ArrayList<ITVSessionContext.ISessionContextCallbacks>();
		try{
			mTvmplContext = mRemote.getTvMediaPlayerContext();
		}
		catch(Exception e){
			mTvmplContext = null;			
			Log.i(LOG_TAG,"TVSessionContextImpl constructor : exception "+e.toString());
			//No need of throwing error as mTvmplContext will become avaialble @ onReacquireInterface()
		}
		try{
			mTvTunerSession 	= ITVTunerSession.instance.asInterface(mRemote.getITvTunerSession());
			mTvRecordPlayback 	= ITVRecordPlayback.instance.asInterface(mRemote.getITvRecordPlayback());
			mTvCIControl		= ITVCIControl.instance.asInterface(mRemote.getITVCIControl());
			mTvExtensionSession = ITVExtensionSession.instance.asInterface(mRemote.getITVExtensionSession());
		}
		catch(Exception e){
			throw new RuntimeException(e);
		}
		
	}
	public ITVTunerSession getITvTunerSession(){
		return mTvTunerSession;	
	}
	
	public ITVExtensionSession getITVExtensionSession(){
		return mTvExtensionSession;	
	}
	
	public ITVRecordPlayback getITvRecordPlayback(){
		return mTvRecordPlayback;
	}
	
	public ITVCIControl getITVCIControl() {
		return mTvCIControl;	
	}

	public ITvMediaAmmi getITvMediaAmmi(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTvMediaAmmi();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}

	public ITvMediaCI getITvMediaCI(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTvMediaCI();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}

	public ITvMediaOp getITvMediaOp(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTvMediaOp();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}

	public ITvMediaRecordControl getITvMediaRecordControl(){
		Log.i(LOG_TAG,"getITvMediaRecordControl called");
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTvMediaRecordControl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}

	public ITvStreamingService getITvStreamingService(){ // TODO: to be removed 
		//return mRemote.getTvMediaPlayerContext().getTvStreamingService();
		return null;
	}

	public IAudioClip getIAudioClip(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getAudioClipImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}

	public IStc getIStc(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getStcImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public ITad getITad(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTadImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public IVideoClip getIVideoClip(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getVideoClipImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public IVideoDrip getIVideoDrip(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getVideoDripImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public IVideoMute getIVideoMute(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getVideoMute();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public ITuning getITuning(){
		try{			
			if(mTvmplContext != null) {
				return mTvmplContext.getTuning();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public ITuningAna getITuningAna(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTuningAna();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public ITuningDvbC getITuningDvbC(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTuningDvbC();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}	
	
	public ITuningDvbS getITuningDvbS(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTuningDvbS();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public ITuningDvbT getITuningDvbT(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTuningDvbT();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}	
	
	public IAudioDescription getIAudioDescription(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getAudioDescriptionImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public IInputSound getIInputSound(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getInputSoundImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public IAnalogColorDecode getIAnalogColorDecode(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getAnalogColorDecodeImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public IVideoProperties getIVideoProperties(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getVideoPropertiesImpl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public long getDemux(){ 
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getDemux();
			}else {
				return 0;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}	
	
	public long getURLDemux(){ 
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getURLDemux();
			}else {
				return 0;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}
	
	public long getVbi(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getVBI();
			}else {
				return 0;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}	
	public ITvOADControl getTvOADControl(){
		try{
			if(mTvmplContext != null) {
				return mTvmplContext.getTvOADControl();
			}else {
				return null;
			}
		}catch(Exception e){
			throw new RuntimeException(e);
		}
	}

	SessionContextCallbacks.Stub mCallStub = new SessionContextCallbacks.Stub() {
		@Override
		public void onReAcquireInterfaces() {
			try {
				mTvmplContext = mRemote.getTvMediaPlayerContext();
				synchronized (sessionContextListner) {
					for (ISessionContextCallbacks listener : sessionContextListner) {
						listener.onReAcquireInterfaces();
					}
				}
			} catch (Exception e) {
				// TODO: handle exception
				throw new RuntimeException(e);
			}			
		}
	};
	
	public void registerSessionContextCallbacks(ISessionContextCallbacks callback){		
		boolean register = false;
		
		synchronized (sessionContextListner) {
			if(callback != null){
				if(sessionContextListner.size() == 0) {
					register = true;
				}
				if (sessionContextListner.contains(callback) == false) {
					sessionContextListner.add(callback);
					//Log.d(LOG_TAG,"Added into list");
				}
			}
			else{
				Log.d(LOG_TAG,"callback is null");
			}
		}
		if(register){
			try {
				//Log.d(LOG_TAG,"Added listener");
				mRemote.registerSessionContextCallbacks(mCallStub);
			} catch (RemoteException e) {
				// TODO Auto-generated catch block
				throw new RuntimeException(e);
			}
		}			
	}
	
	public void unregisterSessionContextCallbacks(ISessionContextCallbacks callback){		
		boolean unregister = false;
		synchronized (sessionContextListner) {
			if (sessionContextListner.contains(callback) == true) {
				sessionContextListner.remove(callback);
			}
			if(sessionContextListner.size()==0){
			   unregister = true;
			}
		}

		if(unregister) {
			try {
				mRemote.unregisterSessionContextCallbacks(mCallStub);
			} catch (RemoteException e) {
				// TODO Auto-generated catch block
				throw new RuntimeException(e);
			}
		}
	}
}
