package org.droidtv.tv.tvinput;

import android.net.Uri;
import android.os.Parcelable;
import android.os.Parcel;
import android.os.IBinder;
import android.os.Bundle;
import android.util.Log;
import java.util.List;
import java.util.ArrayList;
import java.lang.Exception;
import java.lang.String;
import org.droidtv.tv.*;
import org.droidtv.tv.tvinput.ITVSessionContext;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tv.tvinput.MultiFeedServiceInfoImpl;
import org.droidtv.tv.tvinput.TimeshiftInfoImpl;
import android.media.tv.TvContentRating;
import android.os.RemoteException;

/** @hide */
public interface TVTunerSessionImpl{
	public class Proxy implements ITVTunerSession{	
		private static final String LOG_TAG = "TVTunerSessionImpl";
		TVTunerSession mSession 	= null;
		ArrayList<ITunerSessionCallbacks> tunerSessionListner = null;
		
		public Proxy(IBinder svc){
			//Log.i(LOG_TAG,"constructor of tunersessionimpl proxy");
			if(svc != null){
				mSession = TVTunerSession.Stub.asInterface(svc);
				tunerSessionListner = new ArrayList<ITVTunerSession.ITunerSessionCallbacks>();
			}
		}
				
		public Uri getSelectedURI(){
			//Log.i(LOG_TAG,"getSelectedURI called");
			try {
				return mSession.getSelectedURI();
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
	
		public Uri getNextURI(Uri uri){
			//Log.i(LOG_TAG,"getNextURI called");
			try {
				return mSession.getNextURI(uri);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public Uri getPreviousURI(Uri uri){
			//Log.i(LOG_TAG,"getPreviousURI called");
			try {
				return mSession.getPreviousURI(uri);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public boolean getLockStatus(){
			//Log.i(LOG_TAG,"getLockStatus called");
			try {
				return mSession.getLockStatus();
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public boolean getRunningStatus(){
			//Log.i(LOG_TAG,"getRunningStatus called");
			try {
				return mSession.getRunningStatus();
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}

		public TvContentRating  getParentalRating(){
			//Log.i(LOG_TAG,"getParentalRating called");
			try {
				if(mSession.getParentalRating() != null) {
					return TvContentRating.unflattenFromString(mSession.getParentalRating());
				}else {
					return null;
				}
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public byte[] getOipfSiDescriptor(){
			//Log.i(LOG_TAG,"getOipfSiDescriptor called");
			try {
				return mSession.getOipfSiDescriptor();
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}

		public int[] getPrivatePIDInfo(){
		       //Log.i(LOG_TAG,"getPrivatePIDInfo called");
			try {
				return mSession.getPrivatePIDInfo();
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		}

		public boolean hasTeletext(){
			//Log.i(LOG_TAG,"hasTeletext called");
			try {
				return mSession.hasTeletext();
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public void unselectTrack(int type){
			//Log.i(LOG_TAG,"unselectTrack called");
			try {
				mSession.unselectTrack(type);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public void setTrackMuteStatus(int type, boolean mute){
			//Log.i(LOG_TAG,"setTrackMuteStatus called");
			try {
				mSession.setTrackMuteStatus(type,mute);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public boolean  getTrackMuteStatus(int type){
			//Log.i(LOG_TAG,"getTrackMuteStatus called");
			try {
				return mSession.getTrackMuteStatus(type);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public boolean getTrackScramblingStatus(int type){
			//Log.i(LOG_TAG,"getTrackScramblingStatus called");
			try {
				return mSession.getTrackScramblingStatus(type);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public List<MultiFeedServiceInfo> getMultiFeedTracks(){
			//Log.i(LOG_TAG,"getMultiFeedTracks called");
			try {
				List<MultiFeedServiceInfoImpl> multifeedserviceInfoImpl;
				List<MultiFeedServiceInfo> multifeedserviceInfo = new ArrayList<MultiFeedServiceInfo>();
				multifeedserviceInfoImpl = mSession.getMultiFeedTracks();
				if(multifeedserviceInfoImpl!=null){
					for(int i=0;i<multifeedserviceInfoImpl.size();i++)
					{
						MultiFeedServiceInfo serviceInfo = new MultiFeedServiceInfo();
						serviceInfo.mID = multifeedserviceInfoImpl.get(i).mID;
						serviceInfo.mExtra = multifeedserviceInfoImpl.get(i).mExtra;
						multifeedserviceInfo.add(serviceInfo);
					}
				}
				else{
					multifeedserviceInfo = null ;
				}
				return multifeedserviceInfo;
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public String getSelectedMultiFeedTrack() {
			//Log.i(LOG_TAG,"getMultiFeedTracks called");	
			try {
				return mSession.getSelectedMultiFeedTrack();
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}			
		}
		
		public void selectMultiFeedTrack(String trackId){
			//Log.i(LOG_TAG,"selectMultiFeedTrack called");
			try {
				mSession.selectMultiFeedTrack(trackId);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public void loadVideoManagerCache(int cacheid){
			//Log.i(LOG_TAG,"loadVideoManagerChache called");
			try {
				mSession.loadVideoManagerCache(cacheid);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}
		}
		
		public void relayoutVideo(int left, int top, int width, int height){
			//Log.i(LOG_TAG,"relayoutVideo called");
			try {
				mSession.relayoutVideo(left,top,width,height);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}	
		}

		public void enableAudio(boolean status){
			try {
				mSession.enableAudio(status);
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}	
		}
		
		public boolean getAudioStatus() {
			try {
				return mSession.getAudioStatus();
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}		
		}
		
		public int getCurrentMediaMode() {
			try {
				return mSession.getCurrentMediaMode();
			} catch (Exception e) {				
				throw new RuntimeException(e);
			}			
		}
		
		public void timeshiftPause(){
			//Log.i(LOG_TAG,"pauseTimeshift called ");
			try{
				mSession.timeshiftPause();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}	
		}
		
		public void timeshiftStop(){
			//Log.i(LOG_TAG,"timeshiftStop called");

			try{
				mSession.timeshiftStop();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}			
		}
	
		public void timeshiftResume(){
			//Log.i(LOG_TAG,"resumeTimeshift called");

			try{
				mSession.timeshiftResume();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public void timeshiftSeekTo(int msecs){
			//Log.i(LOG_TAG,"timeshiftSeekTo called");

			try{
				mSession.timeshiftSeekTo(msecs);
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public void timeshiftSetSpeed(int speed, boolean forward){
			//Log.i(LOG_TAG,"timeshiftSetSpeed called");
			try{
				mSession.timeshiftSetSpeed(speed , forward);
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public void enableTimeshiftTrickModes(boolean enable){
			//Log.i(LOG_TAG,"enableTimeshiftTrickModes called");
			try{
				mSession.enableTimeshiftTrickModes(enable);
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}

		public boolean getTimeshiftTrickModeStatus(){
			//Log.i(LOG_TAG,"getTimeshiftTrickModeStatus called");
			try{
				return mSession.getTimeshiftTrickModeStatus();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}

		public int getTimeshiftCurrentDuration(){
			//Log.i(LOG_TAG,"getTimeshiftCurrentDuration called");
			try{
				return mSession.getTimeshiftCurrentDuration();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public int getTimeshiftTotalDuration(){
			//Log.i(LOG_TAG,"getTimeshiftTotalDuration called");
			try{
				return mSession.getTimeshiftTotalDuration();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public int getTimeshiftBufferedDuration(){
			//Log.i(LOG_TAG,"getTimeshiftBufferedDuration called");
			try{
				return mSession.getTimeshiftBufferedDuration();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public int getTimeshiftPlaybackState(){
			//Log.i(LOG_TAG,"getTimeShiftPlaybackState called");
			try{
				return mSession.getTimeshiftPlaybackState();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public int getTimeshiftRecordingStatus(){
			//Log.i(LOG_TAG,"getTimeshiftRecordingStatus called");
			try{
				return mSession.getTimeshiftRecordingStatus();
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}
		
		public TimeshiftInfo getTimeshiftInfo() {
			//Log.i(LOG_TAG,"getTimeshiftInfo called");
			try{
				TimeshiftInfoImpl TSInfoImpl;
				TimeshiftInfo TSInfo = new TimeshiftInfo();
				TSInfoImpl =  mSession.getTimeshiftInfo();
				
				if(TSInfoImpl != null) {
					TSInfo.eventName	= TSInfoImpl.eventName;
					TSInfo.shortInfo 	= TSInfoImpl.shortInfo; 	
					TSInfo.extendedInfo	= TSInfoImpl.extendedInfo;
					TSInfo.guidanceInfo	= TSInfoImpl.guidanceInfo;	
					TSInfo.channelId	= TSInfoImpl.channelId;	
					TSInfo.genre		= TSInfoImpl.genre;		
					TSInfo.rating		= TSInfoImpl.rating;		
				}
				return TSInfo;
			}
			catch(Exception e){
				throw new RuntimeException(e);
			}
		}

		TunerSessionCallbacks.Stub mCallStub = new TunerSessionCallbacks.Stub() {
			@Override
			public void onScramblingStatusChanged(int tracktype, boolean status) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onScramblingStatusChanged(tracktype,status);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}
			@Override
			public void OnDualStatusChanged(int channel, int controllable) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.OnDualStatusChanged(channel, controllable);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
			
			}
			@Override
			public void OnBroadcastPreMixedVIPlayed(boolean status) {
				try {
						synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.OnBroadcastPreMixedVIPlayed(status);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
				
			}

			@Override
			public void OnReplacementSvcTuneRequested(int origNetworkId, int tsId,int serviceId) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.OnReplacementSvcTuneRequested(origNetworkId,tsId,serviceId);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
			}

			@Override
			public void onMultifeedFeedDetected() {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onMultifeedFeedDetected();
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
			}

			@Override
			public void onLinkageTypeDetected(int spid,int onID,int tsID,int linkageType) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onLinkageTypeDetected(spid,onID,tsID, linkageType);
						}

					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}

			}
			
			@Override
			public void onTuneFailed(String inputid, Uri channelUri, int reason) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTuneFailed(inputid,channelUri,reason);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
			}
			
			@Override
			public void onTuneStarted(String inputid, Uri channelUri, Bundle bundle) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTuneStarted(inputid,channelUri,bundle);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
			}
			
			@Override
			public void onTuneCompleted(String inputid, Uri channelUri, Bundle bundle) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTuneCompleted(inputid,channelUri,bundle);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
			}
			
			@Override
			public void onMediaModeChanged(int mode) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onMediaModeChanged(mode);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
			}
			
			@Override
			public void onTimeshiftSeekCompleted() {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTimeshiftSeekCompleted();
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}
			
			@Override
			public void onTimeshiftTrickModeEnabled(boolean enable) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTimeshiftTrickModeEnabled(enable);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}
			
			@Override
			public void onTimeshiftPlayStateChanged(int state) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTimeshiftPlayStateChanged(state);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}
			
			@Override
			public void onTimeshiftRecordingStatusChanged(int status) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTimeshiftRecordingStatusChanged(status);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}

			@Override
			public void onTimeshiftPlayError(int reason) {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTimeshiftPlayError(reason);
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}

			@Override
			public void onTimeshiftInfoChanged() {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onTimeshiftInfoChanged();
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}
				
			}

			@Override
			public void onPrivatePidInfoChanged() {
				try {
					synchronized (tunerSessionListner) {
						for (ITunerSessionCallbacks listener : tunerSessionListner) {
							listener.onPrivatePidInfoChanged();
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					throw new RuntimeException(e);
				}

			}
		};
	
		public void registerTunerSessionCallbacks(ITunerSessionCallbacks callback){
			//Log.i(LOG_TAG,"registerTunerSessionCallbacks called");			
			boolean register = false;
			synchronized (tunerSessionListner) {
				if(callback != null){
					if(tunerSessionListner.size() == 0) {
						register = true;
					}
					if (tunerSessionListner.contains(callback) == false) {
						tunerSessionListner.add(callback);
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
					mSession.registerTunerSessionCallbacks(mCallStub);
				} catch (RemoteException e) {
					// TODO Auto-generated catch block
					throw new RuntimeException(e);
				}
			}
		}
		
		public void unregisterTunerSessionCallbacks(ITunerSessionCallbacks callback){
			//Log.i(LOG_TAG,"unregisterTunerSessionCallbacks called");			
			boolean unregister = false;
			synchronized (tunerSessionListner) {
				if (tunerSessionListner.contains(callback) == true) {
					tunerSessionListner.remove(callback);
				}
				if(tunerSessionListner.size()==0){
				   unregister = true;
				}
			}

            if(unregister) {
				try {
					mSession.unregisterTunerSessionCallbacks(mCallStub);
				} catch (RemoteException e) {
					// TODO Auto-generated catch block
					throw new RuntimeException(e);
				}
            }
		}		
	}	
}
