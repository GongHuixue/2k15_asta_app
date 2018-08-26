package org.droidtv.tunerservice.tvmanager;

import java.lang.String;
import android.os.Bundle;

import org.droidtv.tv.tvinput.ITVSessionContext.ISessionContextCallbacks;
import org.droidtv.tv.tvinput.ITVTunerSession;
import org.droidtv.tv.media.TvMediaPlayerContext;

import android.os.IBinder;
import android.net.Uri;
import java.util.List;
import android.media.tv.TvContentRating;
import android.media.tv.TvInputManager;
import android.os.RemoteException;
import android.os.DeadObjectException;
import android.os.TransactionTooLargeException;

import android.media.tv.TvInputService.Session;
import org.droidtv.tv.media.*;
import org.droidtv.tv.audio.*;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;

import android.view.Surface;
import android.graphics.Rect;
import android.media.tv.TvTrackInfo;
import android.media.tv.TvTrackInfo.Builder;
import java.util.Set;
import java.util.HashSet;
import java.util.Iterator;
import android.content.Context;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.os.Message;
import java.util.ArrayList;
import java.util.Map;
import org.droidtv.tv.tvinput.*;
import org.droidtv.tunerservice.TunerService;
import org.droidtv.tunerservice.TunerService.TunerSession;
import org.droidtv.tv.tvinput.SessionContextCallbacks;
import org.droidtv.tv.media.ITvMediaControl;
import org.droidtv.tv.media.ITvMediaStream.TvMediaAudioInfo;
import org.droidtv.tv.media.ITvMediaStream.TvMediaTypeInfo;
import org.droidtv.tv.media.ITvMediaStream.TvMediaExtendedAudioInfo;
import org.droidtv.tv.media.ITvMediaStream.TvMediaVideoInfo;
import org.droidtv.tv.media.ITvMediaStream.TvMediaSubtitleInfo;
import org.droidtv.tv.media.ITvMediaControl.IonMediaChangeListener;
import org.droidtv.tv.media.ITvMediaStream.IOnMediaStreamChangeListener;
import org.droidtv.tv.media.ITvMediaStream.IOnMediaStreamLinkageInfoListener;
import org.droidtv.tv.tvinput.RecordCallbacks;
import org.droidtv.tv.tvinput.TunerSessionCallbacks;
import org.droidtv.tunerservice.interfaces.ITVInputSession;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tv.video.ITvVideoManager;
import org.droidtv.tv.audio.ITvAudioManager;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.tvmanager.AuxTVManager;
import org.droidtv.tunerservice.tvmanager.MainTVManager;
import org.droidtv.tunerservice.interfaces.ITunerRating;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import android.database.ContentObserver;
import android.os.Looper;
import android.database.Cursor;
import android.media.tv.TvContract;
import org.droidtv.htv.provider.HtvContract;

public abstract class AbstractManager implements ITvAbstractPlaybackListener,ITVTunerSession,ITVInputSession,ITVRecordPlayback,ITVCIControl{
	
	private static final String LOG_TAG 								= "TVTunerManager";
	private static final int INVALID_PID 								=  8191;	
	protected Set<TunerService.TunerSession> mSessionListeners	 		= new HashSet<TunerSession>(3);
	protected Set<SessionContextCallbacks> mSessionContextCallback		= new HashSet<SessionContextCallbacks>(3);
	protected Set<TunerSessionCallbacks> mTunerSessionCallback	 		= new HashSet<TunerSessionCallbacks>(3);	
	protected Set<RecordCallbacks> mRecordCallback		 				= new HashSet<RecordCallbacks>(3);	
	private Handler mHandler 											= new Handler();
	private MediaChangeListenerClass mMediaChangeListener						= null;
	private MediaStreamChangeListenerClass mMediaStreamChangeListener			= null;
	private MediaStreamLinkageInfoListenerClass mMediaStreamLinkageInfoListener	= null;
	protected boolean mNotifyMediaEvents					= true;
	protected String userRatingValue						= null;
	protected boolean mTriggerReAcquireInterfaces			= false;
    private TvInputManager mTvInputManager                  = null;
    protected Context mContext 								= null;		
	protected TvManagerHandler mTvHandler 					= null;		
	protected TvManagerUserLockObserver mUserLockObserver 	= null;	
	protected TvManagerHTVObserver mHTVObserver 	= null;
	protected boolean isHTVObserverRegistered 		= false;


	private static final String[] PROJECTION =  {
													TvContract.Channels.COLUMN_LOCKED,
													TvContract.Channels.COLUMN_SERVICE_ID,
													TvContract.Channels.COLUMN_TYPE,
													
												};												
	static final int ACTION_ONCHANGE_CONTENT_OBSERVER 	= 1;	
	static final int ACTION_ONCHANGE_HTV_CONTENT_OBSERVER 	= 2;
	protected int mUserLockStatus						= 0; // Default: UserLockStatus as false		
	protected boolean isObserverRegistered 				= false; 
    private String[][] MapToDvbRating = new String[][]{
                                                        {"DVB_NONE","1"},
                                                        {"DVB_4","2"},
                                                        {"DVB_5","4"},
                                                        {"DVB_6","8"},
                                                        {"DVB_7","16"},
                                                        {"DVB_8","32"},
                                                        {"DVB_9","64"},
                                                        {"DVB_10","128"},
                                                        {"DVB_11","256"},
                                                        {"DVB_12","512"},
                                                        {"DVB_13","1024"},
                                                        {"DVB_14","2048"},
                                                        {"DVB_15","4096"},
                                                        {"DVB_16","8192"},
                                                        {"DVB_17","16384"},
                                                        {"DVB_18","32768"},
                                                        {"ES_DVB_NONE","1"},
                                                        {"ES_DVB_4","2"},
                                                        {"ES_DVB_5","4"},
                                                        {"ES_DVB_6","8"},
                                                        {"ES_DVB_7","16"},
                                                        {"ES_DVB_8","32"},
                                                        {"ES_DVB_9","64"},
                                                        {"ES_DVB_10","128"},
                                                        {"ES_DVB_11","256"},
                                                        {"ES_DVB_12","512"},
                                                        {"ES_DVB_13","1024"},
                                                        {"ES_DVB_14","2048"},
                                                        {"ES_DVB_15","4096"},
                                                        {"ES_DVB_16","8192"},
                                                        {"ES_DVB_17","16384"},
                                                        {"ES_DVB_18","32768"},
                                                        {"ES_DVB_X","262144"},
                                                        {"FR_DVB_NONE","1"},
                                                        {"FR_DVB_4","2"},
                                                        {"FR_DVB_5","4"},
                                                        {"FR_DVB_6","8"},
                                                        {"FR_DVB_7","16"},
                                                        {"FR_DVB_8","32"},
                                                        {"FR_DVB_9","64"},
                                                        {"FR_DVB_10","128"},
                                                        {"FR_DVB_11","256"},
                                                        {"FR_DVB_12","512"},
                                                        {"FR_DVB_13","1024"},
                                                        {"FR_DVB_14","2048"},
                                                        {"FR_DVB_15","4096"},
                                                        {"FR_DVB_16","8192"},
                                                        {"FR_DVB_17","16384"},
                                                        {"FR_DVB_18","32768"},
														{"SG_TV_NONE","1"},
														{"SG_TV_G","2"},
														{"SG_TV_PG","16"},
														{"SG_TV_PG13","1024"},
														{"SG_TV_NC16","8192"},
														{"SG_TV_M18","32768"},
														{"SG_TV_R21","262144"},
														{"AU_TV_NONE","1"},
														{"AU_TV_G", "64"},
														{"AU_TV_PG", "256"},
														{"AU_TV_M", "1024"},
														{"AU_TV_MA", "4096"},
														{"AU_TV_AV", "16384"},
														{"AU_TV_R", "32768"},
														{"AU_TV_ALL", "524288"},
														{"NZ_TV_NONE", "1"},
														{"NZ_TV_G", "64"},
														{"NZ_TV_PGR", "256"},
														{"NZ_TV_AO", "4096"} };

	public int MapRatings ( String rating ) {
		String MappedStr = MapToDvbRating[0][1];
		int MappedRating = 0;
		for(int i_temp =0; i_temp < MapToDvbRating.length; i_temp ++) {
			if( rating.equals(MapToDvbRating[i_temp][0]) ) {
				MappedStr = MapToDvbRating[i_temp][1];
				break;
			}
		}
		MappedRating = Integer.parseInt(MappedStr);
		return MappedRating;
	}

	public void onUnblockContent(TvContentRating AbsUnblockedRating) {
		Log.i(LOG_TAG,"onUnblockContent called : ");
		mTvInputManager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
		if ( (mTvInputManager != null ) && (getTvMediaPlayerContext() != null) ) {
			ITvMediaControl tvmc = getTvMediaPlayerContext().getTvMediaControl();
			if(tvmc != null) {
				try {
					if(mTvInputManager.isParentalControlsEnabled()) {						
						tvmc.setLockStatus(ITvMediaControl.LOCKTYPE_DVB, 0);
						tvmc.setLockStatus(ITvMediaControl.LOCKTYPE_CHANNEL, 0);
					} else {
						tvmc.setLockStatus(ITvMediaControl.LOCKTYPE_CHANNEL, 0);
					}
				}catch(Exception e){
					Log.d(LOG_TAG,"exception " + e.getLocalizedMessage());
				} 
			}
		} 
	}


	public class RatingInterfaceManager implements ITunerRating {		
		public RatingInterfaceManager() {
			
		}
		
		public void setContext(Context context){
			mTvInputManager = (TvInputManager)context.getSystemService(Context.TV_INPUT_SERVICE);
		}
		
		public void enableRating ( ) {
			Log.i(LOG_TAG," PARENTAL_CONTROLS_ENABLED_CHANGED intent is recieved");	
			mHandler.post(new Runnable(){
				public void run(){
					if ( (mTvInputManager != null ) && (getTvMediaPlayerContext() != null) ) {
						ITvMediaControl tvmc = getTvMediaPlayerContext().getTvMediaControl();
						try {
							if(mTvInputManager.isParentalControlsEnabled())	{
								tvmc.enableLocking(true);
							} else {						
								tvmc.enableLocking(false);
							}
						}catch(Exception e){
							Log.e(LOG_TAG,"exception " + e.getLocalizedMessage());
						}
					} else {
						Log.i(LOG_TAG," Illegal Arguements recieved in enableRating ");
					}
				}
			});
			
		}
		
		public  void setParentalRating( ) {
			Log.i(LOG_TAG,"BLOCKED_RATINGS_CHANGED intent is recieved");
			mHandler.post(new Runnable(){
				public void run(){
					if ( (mTvInputManager != null ) && (getTvMediaPlayerContext() != null) )
					{
						ITvMediaControl tvmc = getTvMediaPlayerContext().getTvMediaControl();
						List<TvContentRating> ContentRatingString = mTvInputManager.getBlockedRatings();				
						try {
							if((tvmc!= null) && (ContentRatingString != null) && (ContentRatingString.size()> 0)) {
								TvContentRating RatingStr	= ContentRatingString.get(0);
								String SelectedRating	 	= RatingStr.getMainRating();				
								String RatingSys 			= RatingStr.getRatingSystem();
								Log.i(LOG_TAG," SelectedRating: " + SelectedRating + "Rating System:"+ RatingSys);
								if ( userRatingValue == null) {					
									userRatingValue = new String(SelectedRating);					
									tvmc.setUserRatingValue( ( MapRatings(SelectedRating) ) );					
									Log.i(LOG_TAG,"Initial rating set after bootup " );				
								}				
								if (!(SelectedRating.equals(userRatingValue))) {					
									userRatingValue = new String(SelectedRating);					
									tvmc.setUserRatingValue( ( MapRatings(SelectedRating) ) );					
									Log.i(LOG_TAG,"Rating changed inbetween" );				
								}	
							} else {
								Log.i(LOG_TAG,"No Parental is Set .. Not Setting Rating to MW");
							}
						}catch(Exception e){
							Log.e(LOG_TAG,"exception " + e.getLocalizedMessage());
						}
					} else {
						Log.i(LOG_TAG," MediaPlayer is not Ready!!!");
					}
				}
			});
			
			
		}
		
		public  int getParentalRating( ) {
			String SelectedRating = "DVB_NONE";
			if(mTvInputManager != null ) 
			{
                List<TvContentRating> ContentRatingString = mTvInputManager.getBlockedRatings();
				if((ContentRatingString != null) && (ContentRatingString.size()> 0))
				{
					TvContentRating RatingStr 	= ContentRatingString.get(0);
					SelectedRating 		= RatingStr.getMainRating();
				}
			}
			return MapRatings(SelectedRating);					
		}
		
		public void setDefaultRating() {
			Log.i(LOG_TAG,"setDefaultRating() is called");	
			mHandler.post(new Runnable(){
				public void run(){
					if (mTvInputManager != null) {
						List<TvContentRating> ContentRatingString = mTvInputManager.getBlockedRatings();
						if(ContentRatingString != null) {
							if ( ContentRatingString.size()> 0 ) {				
								TvContentRating RatingStr = ContentRatingString.get(0);
								String SelectedRating = RatingStr.getMainRating();				
								String RatingSys = RatingStr.getRatingSystem();
								Log.i(LOG_TAG," SelectedRating: " + SelectedRating +"RatingSys: "+RatingSys);
							} else {						
								int country 						= 0;
								String[] mSubRatings				= null;
								TvContentRating ContentRatingValue 	= null ;
								ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();						
								country = globalSettings.getInt( TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0 );						
								String Rating = new String("DVB_NONE");
								String Domain = new String("org.droidtv.tunerservice");
								String RatingSys;
								switch(country)	{
									case TvSettingsDefinitions.InstallationCountryConstants.SPAIN:
										RatingSys = "ES_DVB";
										break;
									case TvSettingsDefinitions.InstallationCountryConstants.FRANCE:
										RatingSys = "FR_DVB";
										break;
									case TvSettingsDefinitions.InstallationCountryConstants.SINGAPORE:
										RatingSys = "SG_TV";
										Rating = new String("SG_TV_NONE");
										break;
									case TvSettingsDefinitions.InstallationCountryConstants.AUSTRALIA:
										RatingSys = "AU_TV";
										Rating = new String("AU_TV_NONE");
										break;
									case TvSettingsDefinitions.InstallationCountryConstants.NEWZEALAND:
										RatingSys = "NZ_TV";
										Rating = new String("NZ_TV_NONE");
										break;
									default:
										RatingSys = "DVB";
										break;
								}
								Log.i(LOG_TAG,"setDefaultRating: Rating: " +Rating +"Domain: "+Domain+"RatingSys: "+RatingSys);
								ContentRatingValue = TvContentRating.createRating ( Domain, RatingSys, Rating, mSubRatings );
								if ( ContentRatingValue != null ) {
									mTvInputManager.addBlockedRating(ContentRatingValue);
								} else {
									Log.i(LOG_TAG,"setDefaultRating: createRating is returning null ");
								}						
							}	
						} else {
							Log.i(LOG_TAG,"setDefaultRating: ContentRatingString is null ");
						}
					} else {
						Log.i(LOG_TAG,"setDefaultRating: mTvInputManager is null");
					}
				}
			});
			
		}
	}

	
	public class TvManagerHandler extends Handler {
	
		public TvManagerHandler(Looper looper) {
			super(looper);
		}
		
		@Override
		public synchronized void handleMessage(Message msg) {		
			int Channellock = 0;
			Uri uri			= null;
			switch (msg.arg1) {
				case ACTION_ONCHANGE_CONTENT_OBSERVER:
					uri = getSelectedURI();					
					if((mContext!= null) && (uri != null) && TvContract.isChannelUriForTunerInput(uri)){
						Cursor cursor   = mContext.getContentResolver().query(uri,PROJECTION,null,null, null);
						if(cursor != null) {
							if((cursor.getCount() > 0) && (cursor.moveToFirst()) ) {
								Channellock = cursor.getInt(cursor.getColumnIndex(TvContract.Channels.COLUMN_LOCKED));								
								if ( mUserLockStatus != Channellock ) {
									Log.d(LOG_TAG,"User Lock Status Channellock "+ Channellock);
									mUserLockStatus 		= Channellock;
									try {
										ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
										if(tvmc != null) {
											tvmc.setLockStatus(ITvMediaControl.LOCKTYPE_CHANNEL, Channellock);
										}
									}catch(Exception e){
										Log.e(LOG_TAG,"exception " + e.getLocalizedMessage());
									}
								}									
							}
							cursor.close();
						}
					}
				break;				

				case ACTION_ONCHANGE_HTV_CONTENT_OBSERVER:
					try {
						ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();

						if (tvmc != null) {
							tvmc.setMediaMute(1, false);
						}
					}catch(Exception e){
						Log.d(LOG_TAG,"exception " + e.getLocalizedMessage());
					}
				break;	
			}		
		}	
	}

	public class TvManagerUserLockObserver extends ContentObserver {
    	public TvManagerUserLockObserver( Handler hldr ) {
		    super( hldr );			
		}

		public void onChange(boolean selfChange,Uri uri) {			
			if(uri != null)	{
				Message msgObj 	= new Message();
				msgObj.arg1 	= ACTION_ONCHANGE_CONTENT_OBSERVER;
				mTvHandler.sendMessage(msgObj);							
			}				 
		}
    }
	
	protected void registerforContentObserver() {
		if(mUserLockObserver == null ) {
			mUserLockObserver = new TvManagerUserLockObserver(new Handler());
		}
		             
        if((mUserLockObserver != null) && (isObserverRegistered == false)) {
			mContext.getContentResolver().registerContentObserver(TvContract.Channels.CONTENT_URI, true,mUserLockObserver );
			isObserverRegistered = true;
		} else {
			Log.d(LOG_TAG,"NOT Registering for ContentObserver mUserLockObserver is NULL | It is already Registered ");
		}              
    }

	protected void unregisterforContentObserver() {
		if((mUserLockObserver != null) && (isObserverRegistered == true)) {
			mContext.getContentResolver().unregisterContentObserver(mUserLockObserver);
			isObserverRegistered = false;
		} else {
			Log.d(LOG_TAG,"NOT UnRegistering for ContentObserver mUserLockObserver is NULL | It is already unregistered ");
		}
	}

	public void queryUserLockStatus ( ) {
		Uri uri = getSelectedURI();
		if((mContext!= null) && (uri != null) && TvContract.isChannelUriForTunerInput(uri) ) {
			Cursor cursor   = mContext.getContentResolver().query(uri,PROJECTION,null,null, null);
			if(cursor != null) {
				if((cursor.getCount() > 0) && (cursor.moveToFirst()) ) {	
					mUserLockStatus = cursor.getInt(cursor.getColumnIndex(TvContract.Channels.COLUMN_LOCKED));
					Log.i(LOG_TAG,"mUserLockStatus set to :" +mUserLockStatus );
				}
				cursor.close();
			}
		}
	}
	
	public class TvManagerHTVObserver extends ContentObserver {
    	public TvManagerHTVObserver( Handler hldr ) {
		    super( hldr );			
		}

		public void onChange(boolean selfChange,Uri uri) {			
			if(uri != null)	{
				Message msgObj 	= new Message();
				msgObj.arg1 	= ACTION_ONCHANGE_HTV_CONTENT_OBSERVER;
				mTvHandler.sendMessage(msgObj);							
			}				 
		}
    }
	
	protected void registerforHTVContentObserver() {
		if(mHTVObserver == null ) {
			mHTVObserver = new TvManagerHTVObserver(new Handler());
		}
		             
        if((mHTVObserver != null) && (isHTVObserverRegistered == false)) {
			mContext.getContentResolver().registerContentObserver(HtvContract.HtvChannelSetting.CONTENT_URI, true, mHTVObserver);
			isHTVObserverRegistered = true;
		} else {
			Log.d(LOG_TAG,"NOT Registering for ContentObserver mHTVObserver is NULL | It is already Registered ");
		}              
    }

	protected void unregisterforHTVContentObserver() {
		if((mHTVObserver != null) && (isHTVObserverRegistered == true)) {
			mContext.getContentResolver().unregisterContentObserver(mHTVObserver);
			isHTVObserverRegistered = false;
		} else {
			Log.d(LOG_TAG,"NOT UnRegistering for ContentObserver mHTVObserver is NULL | It is already unregistered ");
		}
	}

	public void registerListener(TunerService.TunerSession pListener){
		synchronized(mSessionListeners) {
			mSessionListeners.add(pListener);
		}
	}
	
	public void unRegisterListener(TunerService.TunerSession pListener){
		synchronized(mSessionListeners) {
			mSessionListeners.remove(pListener);
		}
	}
		
	protected void notifyEvent(final String pEvent, Bundle pData){
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator = mSessionListeners.iterator();
			while(lIterator.hasNext()){
				TunerService.TunerSession lListener = (TunerService.TunerSession)lIterator.next();
				lListener.notifySessionEvent(pEvent, pData);
			}
		}
	}
	
	protected void notifyChannelRetuned(final Uri pChannelUri){
		Log.i(LOG_TAG,"notifyChannelRetuned called... uri = "+pChannelUri);
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator		=	mSessionListeners.iterator();
			while(lIterator.hasNext()){
				TunerService.TunerSession lListener 	= (TunerService.TunerSession)lIterator.next();
				lListener.notifyChannelRetuned(pChannelUri);
			}
		}
	}
	
	protected void notifyVideoAvailable(){
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator		=	mSessionListeners.iterator();
			while(lIterator.hasNext()){
				TunerService.TunerSession lListener 	= (TunerService.TunerSession)lIterator.next();
				lListener.notifyVideoAvailable();
			}
		}
	}
	
	protected void notifyVideoUnavailable(final int reason){
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator		=	mSessionListeners.iterator();
			while(lIterator.hasNext()){
				TunerService.TunerSession lListener 	= (TunerService.TunerSession)lIterator.next();
				lListener.notifyVideoUnavailable(reason);
			}
		}
	}
	
	protected void notifyContentBlocked(final TvContentRating rating) {
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator		=	mSessionListeners.iterator();
			while(lIterator.hasNext()){
				TunerService.TunerSession lListener 	= (TunerService.TunerSession)lIterator.next();
				lListener.notifyContentBlocked(rating);
			}
		}
	}
	
	protected void notifyContentAllowed() {
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator		=	mSessionListeners.iterator();
			while(lIterator.hasNext()){
				TunerService.TunerSession lListener 	= (TunerService.TunerSession)lIterator.next();
				lListener.notifyContentAllowed();
			}
		}
	}
	
	protected void notifyTrackSelected(final int type, final String trackId) {
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator		=	mSessionListeners.iterator();
			while(lIterator.hasNext()){
				TunerService.TunerSession lListener 	= (TunerService.TunerSession)lIterator.next();
				lListener.notifyTrackSelected(type,trackId);
			}
		}
	}
	
	protected void notifyTracksChanged(final List<TvTrackInfo> tracks) {
		for (TvTrackInfo track : tracks) {
			if (track.getType() == TvTrackInfo.TYPE_AUDIO) {
				Log.i(LOG_TAG,"audio pid = " + track.getId());
			}else if (track.getType() == TvTrackInfo.TYPE_VIDEO) {
				Log.i(LOG_TAG,"video pid = " + track.getId());
			}else if (track.getType() == TvTrackInfo.TYPE_SUBTITLE) {
				Log.i(LOG_TAG,"subtitle pid = " + track.getId());
			}
		}
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator		=	mSessionListeners.iterator();
			while(lIterator.hasNext()){
				TunerService.TunerSession lListener = (TunerService.TunerSession)lIterator.next();
				lListener.notifyTracksChanged(tracks);
			}	
		}
	}
	
	protected void notifyLayoutChanged(int left, int top, int right, int bottom){
		Log.i(LOG_TAG,"notifyLayoutChanged called with left = "+ left +
												" top = "+ top +
												" right = "+ right+
												" +bottom ="+bottom);
		synchronized(mSessionListeners) {
			Iterator<TunerSession> lIterator		=	mSessionListeners.iterator();
			while(lIterator.hasNext()){			
				TunerService.TunerSession lListener 	= (TunerService.TunerSession)lIterator.next();
				lListener.layoutSurface(left,top,right,bottom);			
			}
		}
	}
	
	protected void notifyonTuneFailed(Uri channelUri, int inReason) {
		int reason = 0;
		switch (inReason) {
			case ITvAbstractPlaybackListener.TUNE_FAILED_REASON_RECORDING_IN_PROGRESS:
				reason = ITVTunerSession.TUNE_FAILED_REASON_RECORDING_IN_PROGRESS;
				break;
			case ITvAbstractPlaybackListener.TUNE_FAILED_REASON_TAD_IN_PROGRESS:
				reason = ITVTunerSession.TUNE_FAILED_REASON_TAD_IN_PROGRESS;
				break;
			case ITvAbstractPlaybackListener.TUNE_FAILED_REASON_3D_IN_PROGRESS:
				reason = ITVTunerSession.TUNE_FAILED_REASON_3D_IN_PROGRESS;
				break;
			case ITvAbstractPlaybackListener.TUNE_FAILED_REASON_UHD_IN_PROGRESS:
				reason = ITVTunerSession.TUNE_FAILED_REASON_UHD_IN_PROGRESS;
				break;
			case ITvAbstractPlaybackListener.TUNE_FAILED_REASON_INSTALLATION_IN_PROGRESS:
				reason = ITVTunerSession.TUNE_FAILED_REASON_INSTALLATION_IN_PROGRESS;
				break;
			case ITvAbstractPlaybackListener.TUNE_FAILED_REASON_CAM_VOD_IN_PROGRESS:
				reason = ITVTunerSession.TUNE_FAILED_REASON_CAM_VOD_IN_PROGRESS;
				break;
			default:
				reason = ITVTunerSession.TUNE_FAILED_REASON_NONE;
				break;
		}
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onTuneFailed("org.droidtv.tunerservice/.TunerService",channelUri,reason);
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void notifyonTuneStarted(String inputid, Uri channelUri, Bundle bundle) {
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try {
					TunerSessionCallbacks lListener = (TunerSessionCallbacks)lIterator.next();
					lListener.onTuneStarted("org.droidtv.tunerservice/.TunerService",channelUri,bundle);
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void notifyonTuneCompleted(String inputid, Uri channelUri, Bundle bundle) {
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onTuneCompleted("org.droidtv.tunerservice/.TunerService",channelUri,bundle);
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void notifyReAcquireInterfaces() {
		synchronized(mSessionContextCallback) {
			Iterator<SessionContextCallbacks> lIterator		=	mSessionContextCallback.iterator();
			while(lIterator.hasNext()){
				try {
					SessionContextCallbacks lListener 	= (SessionContextCallbacks)lIterator.next();
					lListener.onReAcquireInterfaces(); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void notifySeekComplete(){
		synchronized(mRecordCallback) {
			Iterator<RecordCallbacks> lIterator		=	mRecordCallback.iterator();
			while(lIterator.hasNext()){
				try{
					RecordCallbacks lListener 	= (RecordCallbacks)lIterator.next();
					lListener.onSeekCompleted(); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void notifyTimeshiftSeekComplete(){
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try{
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onTimeshiftSeekCompleted(); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}

	protected void notifyTrickModeEnabled(boolean enabled){
		synchronized(mRecordCallback) {
			Iterator<RecordCallbacks> lIterator		=	mRecordCallback.iterator();
			while(lIterator.hasNext()){
				try{
					RecordCallbacks lListener 	= (RecordCallbacks)lIterator.next();
					lListener.onTrickModeEnabled(enabled); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}

	protected void notifyTimeshiftTrickModeEnabled(boolean enabled){
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try{
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onTimeshiftTrickModeEnabled(enabled); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void notifyPlayError(int reason){
		Log.i(LOG_TAG,"notifyPlayError called with reason "+reason);
		synchronized(mRecordCallback) {
			Iterator<RecordCallbacks> lIterator		=	mRecordCallback.iterator();
			while(lIterator.hasNext()){
				try{
					RecordCallbacks lListener 	= (RecordCallbacks)lIterator.next();
					lListener.onPlayError(reason); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void notifyTimeshiftPlayError(int reason){
		Log.i(LOG_TAG,"notifyTimeshiftPlayError called with reason "+reason);
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try{
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onTimeshiftPlayError(reason); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}

	protected void notifyPVRStateChanged(int state){
		synchronized(mRecordCallback) {
			Iterator<RecordCallbacks> lIterator		=	mRecordCallback.iterator();
			while(lIterator.hasNext()){
				try{
					RecordCallbacks lListener 	= (RecordCallbacks)lIterator.next();
					lListener.onPlayStateChanged(state); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void notifyTimeshiftStateChanged(int state){
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onTimeshiftPlayStateChanged(state);
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
			if(state == ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED){
				notifyMediaStreamChanged();
			}
		}
	}

	protected void notifyTimeshiftInfoChanged() {
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onTimeshiftInfoChanged();
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}

	protected void notifyonPrivatePidInfoChanged() {
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try {
					TunerSessionCallbacks lListener = (TunerSessionCallbacks)lIterator.next();
					lListener.onPrivatePidInfoChanged();
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}


	public TvMediaPlayerContext getTvMediaPlayerContext(){
		return null;
	}

	public void release(TunerService.TunerSession pSession){
	
	}
	
    public void setMainSession(boolean pIsMainSession){
	
	}
	
    public void setSurface(Surface pSurface){
	
	}
	
    public void dispatchSurfaceChanged(int pFormat, int pWidth, int pHeight, Surface pSurface){
	
	}

	public void setVolume(float pVolume){
	
	}
	
    public void tune(Uri pChannelUri){
	
	}
	
	public void SetMain(boolean isMainSession) {
	
	}
	
	public void setSessionType(String sessionType) {
		
	}
	
    public void setCaptionEnabled(boolean pEnabled){
	
	}
	
    public void selectTrack(int type, String trackId){
			
	}
	
	public void selectTrack(TvTrackInfo trackInfo){
	
	}
	
    public void unselectTrack(TvTrackInfo pTrack){
	
	}

    public void appPrivateCommand(String pAction, Bundle pData){
	
	}

    public void createOverlayView(IBinder pWindowToken, Rect pFrame){
	
	}
	
    public void relayoutOverlayView(Rect pFrame){
	
	}
	
    public void removeOverlayView(){
	
	}

    public void requestUnblockContent(String pUnblockedRating){
	
	}	
	
	public void notifySessionEvent(final String pEventType, final Bundle pEventArgs){
	
	}
		
	public void timeshiftPause() {
	}
	
	public void timeshiftStop() {
	}
	
	public void timeshiftResume() {
	}
	
	public void timeshiftSeekTo(int msecs) {
	}
	
	public void timeshiftSetSpeed(int speed, boolean forward) {
	}
	
	public int getTimeshiftCurrentDuration() {
		return 0;
	}

	public int getTimeshiftTotalDuration() {
		return 0;
	}

	public int getTimeshiftBufferedDuration() {
		return 0;
	}

	public int getTimeshiftPlaybackState() {
		return 0;
	}

	public int getTimeshiftRecordingStatus() {
		return 0;
	}

	public void enableTimeshiftTrickModes(boolean enable) {
	}

	public boolean getTimeshiftTrickModeStatus() {
		return true;
	}

	public Uri getSelectedURI(){
		return null;
	}
	
	public Uri getNextURI(Uri uri){
		Uri nextUri		=	PlayTvUtils.getNextURI(uri);	
		return nextUri;
	}
	
	public Uri getPreviousURI(Uri uri){
		Uri previousUri		=	PlayTvUtils.getPreviousURI(uri);
		return previousUri;
	}
	
	public boolean getLockStatus(){
		boolean lockStatus		=	false;
		try{
			ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
			lockStatus				= tvmc.getLockStatus();
		}
		catch(Exception e){
			Log.e(LOG_TAG,"getLockStatus : Exception : "+e.toString());
		}
		return lockStatus;
	}

	public TvContentRating  getParentalRating(){
		String[] mSubRatings = null;
		
		TvContentRating ContentRatingValue = null ;
		mTvInputManager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);
		
		if ( (mTvInputManager != null ) && (getTvMediaPlayerContext() != null) )
		{
			ITvMediaStream tvms 	= getTvMediaPlayerContext().getTvMediaStream();
			int rating = tvms.getParentalRatingValue();

			List<TvContentRating> ContentRatingString = mTvInputManager.getBlockedRatings();

			if((ContentRatingString != null) && (ContentRatingString.size()> 0))
			{
				TvContentRating RatingStr = ContentRatingString.get(0);

				String SelectedRating = Integer.toString(rating);
				String RatingDomain = RatingStr.getDomain();				
				String RatingSys = RatingStr.getRatingSystem();
				
				if ( ( RatingDomain != null ) && ( RatingSys != null ) && ( SelectedRating != null ) )
				{
					Log.i(LOG_TAG," SelectedRating : " + SelectedRating );
					Log.i(LOG_TAG," Rating System : " + RatingSys );
					Log.i(LOG_TAG," Rating Domain : " + RatingDomain  );
					
					//ContentRatingValue = new TvContentRating();
					ContentRatingValue = RatingStr.createRating ( RatingDomain, RatingSys, SelectedRating, mSubRatings );
				}
				else
				{
					Log.i(LOG_TAG," Rating Arguements are returning null from TvContentRating ");
				}

			}
			else
			{
				Log.i(LOG_TAG," Blocked Ratings list are not valid");
			}
		}
		else
		{
			Log.i(LOG_TAG," mTVInputManager or getTvMediaPlayerContext is returning null");
		}
		
		return ContentRatingValue;
	}

	public int[] getPrivatePIDInfo(){
	    int[] mPidInfo = null;
	    if(null != getTvMediaPlayerContext()){
	        try{
    			ITvMediaStream tvms 	= getTvMediaPlayerContext().getTvMediaStream();
    			mPidInfo = tvms.getPrivatePIDInfo();
    		}
    		catch(Exception e){
    			Log.e(LOG_TAG,"Exception in getPrivatePIDInfo " + e.getMessage());
    		}
	    }
	    else{
	        Log.i(LOG_TAG,"getTvMediaPlayerContext is returning null");
	    }
	    return mPidInfo;
	}

	public byte[]  getOipfSiDescriptor(){
		return null;
	}

	public boolean getRunningStatus(){
		boolean runningState		=	false;
		try{
			ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
			runningState		= tvmc.getRunningStatus();
		}
		catch(Exception e){
			Log.e(LOG_TAG,"getRunningStatus : Exception : "+e.toString());
		}
		return runningState;
	}
	
	public boolean hasTeletext(){
		int result 		= getTvMediaPlayerContext().getTvMediaStream().getTeletextInfo();
		if((result == -1)||(result == INVALID_PID)){
			return false;
		}		
		return true;
	}
	
	private int convertToMediaControlTypes(int tifType) {	
		if(tifType == TvTrackInfo.TYPE_AUDIO) {
			return ITvMediaControl.MEDIA_AUDIO;
		}else if(tifType == TvTrackInfo.TYPE_VIDEO) {
			return ITvMediaControl.MEDIA_VIDEO;
		}else if(tifType == TvTrackInfo.TYPE_SUBTITLE) {
			return ITvMediaControl.MEDIA_SUBTITLE;
		}
		throw new IllegalArgumentException("invalid type: " + tifType);
	}
	
	private int convertToTIFTypes(int mcType) {
		if(mcType == ITvMediaControl.MEDIA_AUDIO) {
			return TvTrackInfo.TYPE_AUDIO;
		}else if(mcType == ITvMediaControl.MEDIA_VIDEO) {
			return TvTrackInfo.TYPE_VIDEO;
		}else if(mcType == ITvMediaControl.MEDIA_SUBTITLE) {
			return TvTrackInfo.TYPE_SUBTITLE;
		}
		return -1;
	}
	
	public void unselectTrack(int type){
			
	}
	
	public void setTrackMuteStatus(int type, boolean mute){
		try{
			ITvMediaControl tvmc 	= getTvMediaPlayerContext().getTvMediaControl();
			tvmc.setMediaMute(convertToMediaControlTypes(type),mute);
		}
		catch(Exception e){
			Log.e(LOG_TAG,"setTrackMuteStatus : Exception : "+e.toString());
		}
	}
	
	public boolean  getTrackMuteStatus(int type){
		boolean trackMuteStatus		= false;
		try{
			ITvMediaControl tvmc 	= 	getTvMediaPlayerContext().getTvMediaControl();
			trackMuteStatus			=	tvmc.getMediaMute(convertToMediaControlTypes(type));
		}
		catch(Exception e){
			Log.e(LOG_TAG,"getTrackMuteStatus : Exception : "+e.toString());
		}
		return trackMuteStatus;
	}
	
	public boolean getTrackScramblingStatus(int type){
		boolean trackSramblingStatus		= false;
		try{
			ITvMediaControl tvmc 	= 	getTvMediaPlayerContext().getTvMediaControl();
			trackSramblingStatus	=	(tvmc.getScramblingStatusByMediaType(convertToMediaControlTypes(type)) == ITvMediaControl.SCRAMBLING_STATUS_SCRAMBLED)? true:false;
		}
		catch(Exception e){
			Log.e(LOG_TAG,"getTrackScramblingStatus : Exception : "+e.toString());
		}
		return trackSramblingStatus;
	}
	
	public List<MultiFeedServiceInfo> getMultiFeedTracks(){		 
		return null;
	}	
	
	public TimeshiftInfo getTimeshiftInfo(){		 
		return null;
	}	

	public String getSelectedMultiFeedTrack(){
		return null;
	}
	
	public void selectMultiFeedTrack(String multifeed){		
	}
	
	public void loadVideoManagerCache(int cacheid){
		ITvVideoManager.Instance.getInterface().loadCache(cacheid);
		ITvAudioManager.Instance.getInterface().loadCache(cacheid);
	}
	
	public void relayoutVideo(int left, int top, int width, int height){
		notifyLayoutChanged(left,top,(width+left),(height+top));
	}
	
	public void enableAudio(boolean status) {
	
	}
	
	public boolean getAudioStatus(){
		return false;
	}
	
	public int getCurrentMediaMode(){
		return ITVTunerSession.MODE_BROADCAST;
	}
	
	public View getOverlayView() {
		return null;
	}
	
	public void setMainTvManager(MainTVManager maintvManager) {
	
	}
	
	public void setAuxTvManager(AuxTVManager auxtvManager) {
	
	}
	
	public void setSession(Session session, Surface surface) {
	
	}
	
	public Session getCurrentActiveSession() {
		return null;
	}
	
	public void pause(){
		
	}
	
	public void stop(){
		
	}
	
	public void resume(){
		
	}
	
	public void seekTo(int msecs){
		
	}
	
	public void setSpeed(int speed, boolean forward){
		
	}
	
	public int getCurrentDuration(){
		return 0;
	}
	
	public int getTotalDuration(){
		return 0;
	}
	
	public int getBufferedDuration(){
		return 0;
	}
	
	public int getPlaybackState(){
		return 0;
	}
	
	public void enableTrickModes(boolean enable){
		
	}
	
	public boolean getTrickModeStatus(){
		return true;
	}
	
	public PlayTVFacMediaPlayer getPlaytvMediaPlayer(){
		return null;
	}	
	
	public void enableMMI(boolean enable) {
		
	}
	
	public void updateMMIStatus(boolean status) {
	
	}
	
	public void selectMMIItem(int menuType,int selectedItem) {
	
	}
	
	public String[] getMMIItems(int menuType) {
		return null;
	}
	
	public int getLastSelectedMenuIndex() {
		return 0;
	}
	
	public void setEnquiryMMIResponse(String answer) {
		
	}
	
	public CIMmiEnq getEnquiryMMIInfo() {		
		return null;
	}
	
	public void cancelMMI(int menutype){
		
	}

	public void enableCamUpgrade(boolean enable){
	
	}
	
	public int getCAMUpgradeStatus() {
		return 0;
	}
	
	public void updateCamInfo(CamInfo caminfo) {

	}
	
	public void enableCAMUI(boolean enable) {
			
	}	
	
	public CamInfo getCamInfo(int slotId) {
		return null;
	}
	
	public void registerCIControlListener(ITVCIControlCallback callback){
		//dummy	
	}

	public void unRegisterCIControlListener(ITVCIControlCallback callback){
		//dummy
	}
	
	public void registerCIControlListener(TVCIControlCallback callback){
			
	}

	public void unRegisterCIControlListener(TVCIControlCallback callback){
		
	}
			
        protected void notifyLockStatusChanged(final int type, final int status){
                //int mParentalRatingValue = -1,
                int rating = 0;
                mTvInputManager = (TvInputManager)mContext.getSystemService(Context.TV_INPUT_SERVICE);


                if ( (mTvInputManager != null ) && (getTvMediaPlayerContext() != null) )
                {

                        //ITvMediaStream mMediaStream = getTvMediaPlayerContext().getTvMediaStream();

                        TvContentRating ContRatingStr ;

			String RatingStr = null;
			
			//mParentalRatingValue = mMediaStream.getParentalRatingValue();
		
			if(status == 0)
			{
				notifyContentAllowed();
			}
			else
			{
			
				if(type == 2) //user lock 
				{
					int size = 0;
					String[] mSubRatings = null;
					List<TvContentRating> ContentRatingString = mTvInputManager.getBlockedRatings();
					
					size = ContentRatingString.size();
					if((ContentRatingString.size()> 0))
					{
						TvContentRating RatingString = ContentRatingString.get(0);
						TvContentRating ContentRatingValue;

						if(mTvInputManager.isParentalControlsEnabled())
						{
							String SelectedRating = new String("DVB_NONE");
							String RatingDomain = RatingString.getDomain();
							String RatingSys = RatingString.getRatingSystem();

							if ( ( RatingDomain != null ) && ( RatingSys != null ) && ( SelectedRating != null ) )
							{
								Log.i(LOG_TAG," notifyLockStatusChanged: SelectedRating : " + SelectedRating );
								Log.i(LOG_TAG," notifyLockStatusChanged: Rating System : " + RatingSys );
								Log.i(LOG_TAG," notifyLockStatusChanged: Rating Domain : " + RatingDomain );

								ContentRatingValue = RatingString.createRating ( RatingDomain, RatingSys, SelectedRating, mSubRatings );
								if ( ContentRatingValue == null )
								{
									Log.i(LOG_TAG," notifyLockStatusChanged: ContentRatingValue is returned as null "  );
								}
								else{
									notifyContentBlocked(ContentRatingValue);
								}
							}
							else
							{
								Log.i(LOG_TAG," notifyLockStatusChanged: Rating Arguements are returning null from TvContentRating ");
							}
						}
						else
						{

							notifyContentBlocked(RatingString);
						}
						
					}
					else
					{
						Log.i(LOG_TAG," notifyLockStatusChanged: ContentRatingString size is null  ");
					}
					
				}
				else  // parental rating
				{
			
					List<TvContentRating> ContentRatingString = mTvInputManager.getBlockedRatings();

					if((ContentRatingString != null) && (ContentRatingString.size()> 0))
					{
						TvContentRating RatingString = ContentRatingString.get(0);
					
						notifyContentBlocked(RatingString);
					}
				}
			}
		}
		else
		{
			Log.i(LOG_TAG," Illegal Arguements recieved in notifyLockStatusChanged ");
		}
		
	}
	
	protected void notifyMediaStateChanged(final int media) {
		int tifMedia 		= convertToTIFTypes(media);
		boolean pidFound 	= false;
		if((tifMedia != -1) && (getTvMediaPlayerContext() != null)){  //dont sent for PCR as it is not part of TIF TvTrackInfo	
			ITvMediaControl tvmc = getTvMediaPlayerContext().getTvMediaControl();
			ITvMediaStream tvms = getTvMediaPlayerContext().getTvMediaStream();
			
			if(tifMedia == TvTrackInfo.TYPE_AUDIO)
			{
				TvMediaAudioInfo mCurrentAudioInfo =  tvmc.getTVAudio();				
				int noAudio = tvms.getCurrentNoOfAudio();		
				for(int i=0;i<noAudio;i++)
				{
					TvMediaExtendedAudioInfo mAudioInfo = tvms.getCurrentExtendedAudioInfo(i);
					if((mAudioInfo.pid == mCurrentAudioInfo.pid) && (mAudioInfo.langCode == mCurrentAudioInfo.langCode) 
					   && (mAudioInfo.type == mCurrentAudioInfo.type)) {
						notifyTrackSelected(tifMedia, "audio:" + Integer.toString(i));
						pidFound = true;
						break;
					}
				}
				if(!pidFound) {
					notifyTrackSelected(tifMedia, null);					
				}
				
			}else if(tifMedia == TvTrackInfo.TYPE_VIDEO)
			{
				int mCurrentVideoPid =  tvmc.getTVMedia(media);				
				int noVideo = tvms.getCurrentNoOfVideo();		
				for(int i=0;i<noVideo;i++)
				{
					TvMediaVideoInfo mVideoInfo = tvms.getCurrentVideoInfo(i);
					if(mVideoInfo.pid == mCurrentVideoPid) {
						notifyTrackSelected(tifMedia, "video:" + Integer.toString(i));
						pidFound = true;
						break;
					}
				}
				if(!pidFound) {
					notifyTrackSelected(tifMedia, null);					
				}
			
			}else if(tifMedia == TvTrackInfo.TYPE_SUBTITLE)
			{
				ISubtitles subtitleIntf = getTvMediaPlayerContext().getSubtitles();
			
				if(subtitleIntf != null) {
					int index = subtitleIntf.getCurrentSubtitle();
					Log.d(LOG_TAG,"subtitleIntf.getCurrentSubtitle() : index"+index);
					if(index == -2) {
						notifyTrackSelected(tifMedia, null);
					}else if(index >= 0) {
						notifyTrackSelected(tifMedia, "subtitle:" + Integer.toString(index));
					}
				}
			}
		}
	}
	
	private List<TvTrackInfo> buildMediaTrackList() {
		List<TvTrackInfo> mMediaTracks 	= null;			
		try{
			if(getTvMediaPlayerContext() != null) {
				mMediaTracks = new ArrayList<TvTrackInfo>();
				ITvMediaStream tvms = getTvMediaPlayerContext().getTvMediaStream();		
				int noAudio = tvms.getCurrentNoOfAudio();		
				for(int i=0;i<noAudio;i++)
				{
					TvMediaExtendedAudioInfo mAudioInfo = tvms.getCurrentExtendedAudioInfo(i);
					Builder abuilder = new Builder(TvTrackInfo.TYPE_AUDIO,"audio:"+Integer.toString(i));
					abuilder.setLanguage(Integer.toString(mAudioInfo.langCode));
					Bundle bundle=new Bundle();
					bundle.putInt(KEY_MEDIA_LANGID, mAudioInfo.langId);
					bundle.putInt(KEY_MEDIA_PID,mAudioInfo.pid);
					bundle.putInt(KEY_MEDIA_TYPE, mAudioInfo.type);
					bundle.putInt(KEY_MEDIA_LANGCODE,mAudioInfo.langCode);
					bundle.putBoolean(KEY_MEDIA_AUDIO_ISVI, TvMediaTypeInfo.isVisuallyImpairedCommentary(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_AUDIO_HAS_VI_ASSOCIATION,mAudioInfo.mixedAudio);
					bundle.putBoolean(KEY_MEDIA_AUDIO_HAS_PRIMARY_VI_ASSOCIATION, mAudioInfo.viAudio);
					bundle.putBoolean(KEY_MEDIA_AUDIO_ISPREMIXED,TvMediaTypeInfo.isPremixedVIAudio(mAudioInfo.type));				
					bundle.putBoolean(KEY_MEDIA_AUDIO_ISMPEG, TvMediaTypeInfo.isMpegAudio(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_AUDIO_ISAC3, TvMediaTypeInfo.isAC3Audio(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_AUDIO_ISAAC, TvMediaTypeInfo.isAACAudio(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_AUDIO_ISAC3PLUS, TvMediaTypeInfo.isAC3PLUSAudio(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_AUDIO_ISHEAAC, TvMediaTypeInfo.isHEAACAudio(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_AUDIO_IS_MULTICHANNEL_AC3, TvMediaTypeInfo.isMultichannelAC3Type(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_AUDIO_IS_NON_MULTICHANNEL_AC3, TvMediaTypeInfo.isNonMultichannelAC3Type(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_AUDIO_ISSPOKEN, TvMediaTypeInfo.isSpokenSubtitles(mAudioInfo.type));
					bundle.putBoolean(KEY_MEDIA_ISHEARINGIMPAIRED, TvMediaTypeInfo.isHearingImpaired(mAudioInfo.type));
					abuilder.setExtra(bundle);
					mMediaTracks.add(abuilder.build());
				}		
				int noSubtitle = tvms.getCurrentNoOfSubtitle();		
				for(int i=0;i<noSubtitle;i++)
				{
					TvMediaSubtitleInfo mSubtitleInfo = tvms.getCurrentSubtitleInfo(i);
					Builder sbuilder = new Builder(TvTrackInfo.TYPE_SUBTITLE,"subtitle:"+Integer.toString(i));
					sbuilder.setLanguage(Integer.toString(mSubtitleInfo.langCode));
					Bundle bundle=new Bundle();
					bundle.putInt(KEY_MEDIA_LANGID, mSubtitleInfo.language);
					bundle.putInt(KEY_MEDIA_PID,mSubtitleInfo.pid);
					bundle.putInt(KEY_MEDIA_TYPE, mSubtitleInfo.type);
					bundle.putInt(KEY_MEDIA_LANGCODE,mSubtitleInfo.langCode);
					bundle.putBoolean(KEY_MEDIA_SUBTITLE_ISDVB, TvMediaTypeInfo.isDVBSubtitle(mSubtitleInfo.type));
					bundle.putBoolean(KEY_MEDIA_SUBTITLE_ISText, TvMediaTypeInfo.isTXTSubtitle(mSubtitleInfo.type));
					bundle.putBoolean(KEY_MEDIA_ISHEARINGIMPAIRED, TvMediaTypeInfo.isHearingImpaired(mSubtitleInfo.type));
					sbuilder.setExtra(bundle);
					mMediaTracks.add(sbuilder.build());
				}
				
				int noVideo = tvms.getCurrentNoOfVideo();		
				for(int i=0;i<noVideo;i++)
				{
					TvMediaVideoInfo mVideoInfo = tvms.getCurrentVideoInfo(i);
					Builder vbuilder = new Builder(TvTrackInfo.TYPE_VIDEO,"video:"+Integer.toString(i));
					Bundle bundle=new Bundle();
					bundle.putInt(KEY_MEDIA_PID,mVideoInfo.pid);
					bundle.putInt(KEY_MEDIA_TYPE, mVideoInfo.type);
					vbuilder.setExtra(bundle);
					mMediaTracks.add(vbuilder.build());
				}							
			}
		}catch(Exception e){
			Log.e(LOG_TAG,"exception " + e.getLocalizedMessage());
		}			
		return mMediaTracks;
	}
	
	public void notifyMediaStreamChanged(){	
		Log.d(LOG_TAG,"notifyMediaStreamChanged");
		List<TvTrackInfo> mMediaTracks = buildMediaTrackList();
		if(mMediaTracks != null) {
			notifyTracksChanged(mMediaTracks);
		}
	}
	
	public void notifyMediaEvents(TunerService.TunerSession pListener) {
		try{
			if(pListener != null) {
				if(getTvMediaPlayerContext() != null){						
					ITvMediaControl tvmc 			= getTvMediaPlayerContext().getTvMediaControl();
					ITvMediaStream tvms 			= getTvMediaPlayerContext().getTvMediaStream();
					List<TvTrackInfo> mMediaTracks 	= buildMediaTrackList();
					/*no need to notify null cases as this is fresh trigger, google cache should already 
					  been initialized with null*/
					if(mMediaTracks != null) {
						pListener.notifyTracksChanged(mMediaTracks);
					}				
					TvMediaAudioInfo mCurrentAudioInfo =  tvmc.getTVAudio();				
					int noAudio = tvms.getCurrentNoOfAudio();		
					for(int i=0;i<noAudio;i++)
					{
						TvMediaExtendedAudioInfo mAudioInfo = tvms.getCurrentExtendedAudioInfo(i);
						if((mAudioInfo.pid == mCurrentAudioInfo.pid) && (mAudioInfo.langCode == mCurrentAudioInfo.langCode) 
						   && (mAudioInfo.type == mCurrentAudioInfo.type)) {
							pListener.notifyTrackSelected(TvTrackInfo.TYPE_AUDIO, "audio:" + Integer.toString(i));
							break;
						}
					}
					int mCurrentVideoPid =  tvmc.getTVMedia(ITvMediaControl.MEDIA_VIDEO);				
					int noVideo = tvms.getCurrentNoOfVideo();		
					for(int i=0;i<noVideo;i++)
					{
						TvMediaVideoInfo mVideoInfo = tvms.getCurrentVideoInfo(i);
						if(mVideoInfo.pid == mCurrentVideoPid) {
							pListener.notifyTrackSelected(TvTrackInfo.TYPE_VIDEO, "video:" + Integer.toString(i));
							break;
						}
					}
					ISubtitles subtitleIntf = getTvMediaPlayerContext().getSubtitles();			
					if(subtitleIntf != null) {
						int index = subtitleIntf.getCurrentSubtitle();
						if(index >= 0) {
							pListener.notifyTrackSelected(TvTrackInfo.TYPE_SUBTITLE, "subtitle:" + Integer.toString(index));
						}
					}
				}
			}
		}catch(Exception e){
			/*could be dead object exception/transaction too large due to client dies immediately
			  after creation of session or any other exception in media control operations*/
			Log.e(LOG_TAG,"exception " + e.getLocalizedMessage());
		}
	}
	
	private void notifyScramblingStatusChanged(final int media, final int status){
		int tifMedia = convertToTIFTypes(media);
		boolean tifScrambleStatus = (status == ITvMediaControl.SCRAMBLING_STATUS_SCRAMBLED)? true:false;
		
		if(tifMedia != -1) {
			synchronized(mTunerSessionCallback) {
				Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
				while(lIterator.hasNext()){
					try {
						TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
						lListener.onScramblingStatusChanged(tifMedia,tifScrambleStatus); // TODO: INTERFQACE CHANGE REQUIRED
					}catch(TransactionTooLargeException e) {
						Log.e(LOG_TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(LOG_TAG,"DeadObjectException !!!");
					}catch (RemoteException e) {
						throw new RuntimeException(e);
					}				
				}
			}
		}
	}
	
	private void notifyReplacementSvcTuneRequested(final int arg1,final int arg2,final int arg3) {
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.OnReplacementSvcTuneRequested(arg1,arg2,arg3);
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}			
			}
		}
	}
	
	private void notifyOnDualStatusChanged(final int channel,final int controllable) {
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){			
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.OnDualStatusChanged(channel,controllable);
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	private void  notifyOnBroadcastPreMixedVIPlayed(final boolean status){
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){			
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.OnBroadcastPreMixedVIPlayed(status);
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected boolean registerOnMediaChangeListener()
	{	
		try {
			ITvMediaControl tvmc = getTvMediaPlayerContext().getTvMediaControl();
			if(mMediaChangeListener	==	null) {
				mMediaChangeListener = new MediaChangeListenerClass();
			}
			if(tvmc != null) {				
			    tvmc.registerListenerCallback((IonMediaChangeListener) mMediaChangeListener);
			}
			else {
				Log.d(LOG_TAG,"tvmc null medialistener not registered");
				return false;
			}
		}catch(Exception e) {
			Log.e(LOG_TAG,"Caught exception in RegisterOnMediaChangeListener ");
			return false;
		}
		return true;
	}
	
	protected void unRegisterOnMediaChangeListener() {
		try {
			ITvMediaControl tvmc = getTvMediaPlayerContext().getTvMediaControl();	
			tvmc.unRegisterListenerCallback((IonMediaChangeListener) mMediaChangeListener);
			mMediaChangeListener = null;
		} catch(Exception e) {
			Log.e(LOG_TAG,"Caught exception in UnRegisterOnMediaChangeListener ");
		}
	}
	
	class MediaChangeListenerClass extends IonMediaChangeListener{
		
		@Override
		public void onLockStatusChanged(final int type, final int status)
		{
			Log.d(LOG_TAG,"onLockStatusChanged type = " + type + " status " + status);
			
			Runnable r = new Runnable() {
				public void run() {
					notifyLockStatusChanged(type, status);
				}
			};
			mHandler.post(r);
			
		}

		@Override
		public void onMediaStateChanged(final int media) {
			Log.d(LOG_TAG,"onMediaStateChanged " + media);
			mHandler.post(new Runnable(){
				public void run(){
					notifyMediaStateChanged(media);
				}
			});
		}

		@Override
		public void onScramblingStatusChanged(final int media,final int status) {
			Log.d(LOG_TAG,"onScramblingStatusChanged media" + media + " status " + status);
			mHandler.post(new Runnable(){
				public void run(){
					notifyScramblingStatusChanged(media, status);
				}
			});
		}
		
		@Override
		public void OnReplacementSvcTuneRequested(final int arg1, final int arg2,final int arg3) {	
				Log.d(LOG_TAG,"OnReplacementSvcTuneRequested arg1" + arg1 + " arg2 " + arg2 + " arg3 " +arg3);
				mHandler.post(new Runnable(){
				public void run(){
					notifyReplacementSvcTuneRequested(arg1,arg2,arg3);
				}
			});
		}
		
		@Override
		public void OnDualStatusChanged(final int channel, final int controllable) {
				Log.d(LOG_TAG,"OnDualStatusChanged channel" + channel + " controllable " + controllable);
				mHandler.post(new Runnable(){
				public void run(){					
					notifyOnDualStatusChanged(channel,controllable);
					if((getTvMediaPlayerContext() != null) && (controllable == 0)){
						/*controllable = 0 means ISODescriptor detected two language and hence dual1/2 menu 
						  not controllable as we display two language under audiolang menu*/
						if(channel == ITvMediaControl.LANGUAGE_ONE) {
							getTvMediaPlayerContext().getInputSoundImpl().setChannel(IInputSound.CHANNEL2);	
						}else if(channel == ITvMediaControl.LANGUAGE_TWO) {
							getTvMediaPlayerContext().getInputSoundImpl().setChannel(IInputSound.CHANNEL3);	
						}
					}
				}
			});
		}
		
		public void OnBroadcastPreMixedVIPlayed(final boolean status){
				Log.d(LOG_TAG,"OnBroadcastPreMixedVIPlayed status " + status);
				mHandler.post(new Runnable(){
				public void run(){
					notifyOnBroadcastPreMixedVIPlayed(status);
				}
			});
		}
	}		
	
	private void notifyonMultifeedFeedDetected() {
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){			
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onMultifeedFeedDetected();
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void registerOnMediaStreamChangeListener()
	{	
		try {
			ITvMediaStream tvms = getTvMediaPlayerContext().getTvMediaStream();
			if(mMediaStreamChangeListener	==	null) {
				mMediaStreamChangeListener = new MediaStreamChangeListenerClass();
			}
			tvms.registerCallbackListener((IOnMediaStreamChangeListener) mMediaStreamChangeListener);
		}catch(Exception e) {
			Log.e(LOG_TAG,"Caught exception in registerOnMediaStreamChangeListener ");
		}
	}
	
	protected void unRegisterOnMediaStreamChangeListener() {
		try {
			ITvMediaStream tvms = getTvMediaPlayerContext().getTvMediaStream();	
			tvms.unregisterCallbackListener((IOnMediaStreamChangeListener) mMediaStreamChangeListener);
			mMediaStreamChangeListener = null;
		} catch(Exception e) {
			Log.e(LOG_TAG,"Caught exception in unRegisterOnMediaStreamChangeListener ");
		}
	}
	
	class MediaStreamChangeListenerClass extends IOnMediaStreamChangeListener {
		@Override
		public void onMediaStreamChanged(final int property_changed) {
			mHandler.post(new Runnable(){
				public void run(){
					if(property_changed == IOnMediaStreamChangeListener.PMT_CHANGED) {
						notifyMediaStreamChanged();
						/*Notify private PID info changed*/
						notifyonPrivatePidInfoChanged();
					}
				}
			});
		}
		
		@Override
		 public void onMultifeedFeedDetected() {
			mHandler.post(new Runnable(){
				public void run(){
					notifyonMultifeedFeedDetected();
				}
			});
		 }	
	}
	
	private void notifyonLinkageTypeDetected(final int dest,final int spid,final int onID,final int tsID,final int linkageType) {
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator		=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){			
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onLinkageTypeDetected(spid,onID,tsID,linkageType);
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}
			}
		}
	}
	
	protected void registerOnMediaStreamLinkageInfoListener()
	{	
		try {
			ITvMediaStream tvms = getTvMediaPlayerContext().getTvMediaStream();
			if(mMediaStreamLinkageInfoListener	==	null) {
				mMediaStreamLinkageInfoListener = new MediaStreamLinkageInfoListenerClass();
			}
			tvms.registerLinkageInfoListener((IOnMediaStreamLinkageInfoListener) mMediaStreamLinkageInfoListener);
		}catch(Exception e) {
			Log.e(LOG_TAG,"Caught exception in registerOnMediaStreamLinkageInfoListener ");
		}
	}
	
	protected void unRegisterOnMediaStreamLinkageInfoListener() {
		try {
			ITvMediaStream tvms = getTvMediaPlayerContext().getTvMediaStream();	
			tvms.unregisterLinkageInfoListener((IOnMediaStreamLinkageInfoListener) mMediaStreamLinkageInfoListener);
			mMediaStreamLinkageInfoListener = null;
		} catch(Exception e) {
			Log.e(LOG_TAG,"Caught exception in unRegisterOnMediaStreamLinkageInfoListener ");
		}
	}
	
	class MediaStreamLinkageInfoListenerClass extends IOnMediaStreamLinkageInfoListener {		
		@Override
		public void onLinkageTypeDetected(final int dest,final int spid,final int onID,final int tsID,final int linkageType)
		{
			mHandler.post(new Runnable(){
				public void run(){
					notifyonLinkageTypeDetected(dest,spid,onID,tsID,linkageType);
				}
			});
		}	
	}
	
	protected void notifyMediaModeChanged(int mode){	
		Log.i(LOG_TAG,"notifyMediaModeChanged :  mode - "+mode);
		synchronized(mTunerSessionCallback) {
			Iterator<TunerSessionCallbacks> lIterator	=	mTunerSessionCallback.iterator();
			while(lIterator.hasNext()){
				try {
					TunerSessionCallbacks lListener 	= (TunerSessionCallbacks)lIterator.next();
					lListener.onMediaModeChanged(mode); 
				}catch(TransactionTooLargeException e) {
					Log.e(LOG_TAG,"TransactionTooLargeException !!!");
				}catch(DeadObjectException e) {
					Log.e(LOG_TAG,"DeadObjectException !!!");
				}catch (RemoteException e) {
					throw new RuntimeException(e);
				}				
			}
		}
	}
	
	public void setOverlayManager(OverlayManager overlayManager){
	
	}
	
	public void registerSessionContextCallbacks(ISessionContextCallbacks callback){
		//dummy function as class needs to implement ITvSessionContext
	}
			
	public void unregisterSessionContextCallbacks(ISessionContextCallbacks callback){
		//dummy function as class needs to implement ITvSessionContext
	}
	
	public void registerTunerSessionCallbacks(ITunerSessionCallbacks callback){
		//dummy function as class needs to implement ITvTunerSession
	}	
		
	public void unregisterTunerSessionCallbacks(ITunerSessionCallbacks callback){
		//dummy function as class needs to implement ITvTunerSession	
	}
		
	public void registerRecordCallback(IRecordCallbacks callback){
		//dummy function as class needs to implement ITvRecordPlayback
	}
	
	public void unregisterRecordCallbacks(IRecordCallbacks callback){
		//dummy function as class needs to implement ITvRecordPlayback
	}
	
	/*Actual implementation of register-unregister starts here*/	
	public void registerSessionContextCallbacks(final SessionContextCallbacks callback){
		synchronized(mSessionContextCallback) {
			mSessionContextCallback.add(callback);
		}
		mHandler.post(new Runnable(){
			public void run(){
				if(getTvMediaPlayerContext() != null) {					
					try {
						callback.onReAcquireInterfaces();
					}catch(TransactionTooLargeException e) {
						Log.e(LOG_TAG,"TransactionTooLargeException !!!");
					}catch(DeadObjectException e) {
						Log.e(LOG_TAG,"DeadObjectException !!!");
					}catch (RemoteException e) {
						throw new RuntimeException(e);
					}					
				}else {
					mTriggerReAcquireInterfaces =  true;
				}
			}
		});
	}
			
	public void unregisterSessionContextCallbacks(SessionContextCallbacks callback){
		synchronized(mSessionContextCallback) {
			mSessionContextCallback.remove(callback);
		}
	}
	
	public void registerTunerSessionCallbacks(TunerSessionCallbacks callback){
		synchronized(mTunerSessionCallback) {
			mTunerSessionCallback.add(callback);
		}
	}
		
	public void unregisterTunerSessionCallbacks(TunerSessionCallbacks callback){
		synchronized(mTunerSessionCallback) {
			mTunerSessionCallback.remove(callback);
		}
	}
		
	public void registerRecordCallback(RecordCallbacks callback){
		synchronized(mRecordCallback) {
			mRecordCallback.add(callback);
		}
	}
	
	public void unregisterRecordCallbacks(RecordCallbacks callback){
		synchronized(mRecordCallback) {
			mRecordCallback.remove(callback);
		}
	}
	
	public void tune(Uri pChannelUri,Bundle params) {
	
	}
	
	protected int getTuneFailureReason(int mplfacStatus) {
		int reason = ITvAbstractPlaybackListener.TUNE_FAILED_REASON_NONE;
		
		if((mplfacStatus) != PlayTVMediaPlayerFactory.STATUS_AVAILABLE) {
			if(((mplfacStatus & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) ||
			   ((mplfacStatus & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING)){
				reason	= ITvAbstractPlaybackListener.TUNE_FAILED_REASON_RECORDING_IN_PROGRESS;
			}else if(((mplfacStatus & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) == PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) ||
					 ((mplfacStatus & PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) == PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD)){
				reason	= ITvAbstractPlaybackListener.TUNE_FAILED_REASON_TAD_IN_PROGRESS;
			}else if((mplfacStatus & PlayTVMediaPlayerFactory.STATUS_3D_IN_PROGRESS) == PlayTVMediaPlayerFactory.STATUS_3D_IN_PROGRESS) {
				reason	= ITvAbstractPlaybackListener.TUNE_FAILED_REASON_3D_IN_PROGRESS;
			}else if((mplfacStatus & PlayTVMediaPlayerFactory.STATUS_NOTAVAILABLE_CAMVOD_IN_PROGRESS) == PlayTVMediaPlayerFactory.STATUS_NOTAVAILABLE_CAMVOD_IN_PROGRESS) {
				reason	= ITvAbstractPlaybackListener.TUNE_FAILED_REASON_CAM_VOD_IN_PROGRESS;
			}else if((mplfacStatus & PlayTVMediaPlayerFactory.STATUS_UHD_IN_PROGRESS) == PlayTVMediaPlayerFactory.STATUS_UHD_IN_PROGRESS) {
				reason	= ITvAbstractPlaybackListener.TUNE_FAILED_REASON_UHD_IN_PROGRESS;
			}else if((mplfacStatus & PlayTVMediaPlayerFactory.STATUS_INSTALLATION_IN_PROGRESS) == PlayTVMediaPlayerFactory.STATUS_INSTALLATION_IN_PROGRESS) {
				reason	= ITvAbstractPlaybackListener.TUNE_FAILED_REASON_INSTALLATION_IN_PROGRESS;
			}
		}
		return reason;
	}
	
	@Override
	public void onPlayStarted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber){
		Log.i(LOG_TAG,"onPlayStarted : "+uri);
		int selType = TvURIHelper.SelectionType.SELECTION_NORMAL.value;
		if((headers != null) && (headers.get(TvHeaders.SELECTION_TYPE) != null)) {
			selType	= Integer.parseInt(headers.get(TvHeaders.SELECTION_TYPE));
		}
		if((selType != TvURIHelper.SelectionType.SELECTION_MULTIFEED.value) &&
		   (selType != TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value)) {
			notifyonTuneStarted("org.droidtv.tunerservice/.TunerService",uri,TvURIHelper.getBundleFromHeaders(headers));
			notifyVideoUnavailable(TvInputManager.VIDEO_UNAVAILABLE_REASON_TUNING);
		}
	}
	
	@Override
	public void onPlayCompleted(Uri uri, Map<String,String> headers, Medium medium, int presetNumber){
		Log.i(LOG_TAG,"onPlayCompleted : "+uri);
		int selType = TvURIHelper.SelectionType.SELECTION_NORMAL.value;
		
		if(mNotifyMediaEvents) {
			mNotifyMediaEvents = false;
			notifyMediaStreamChanged();
			notifyMediaStateChanged(ITvMediaControl.MEDIA_VIDEO);
			notifyMediaStateChanged(ITvMediaControl.MEDIA_AUDIO);
			notifyMediaStateChanged(ITvMediaControl.MEDIA_SUBTITLE);
		}
		
		if(mTriggerReAcquireInterfaces) {			
			notifyReAcquireInterfaces();
			mTriggerReAcquireInterfaces = false;
		}		
		if((headers != null) && (headers.get(TvHeaders.SELECTION_TYPE) != null)) {
			selType = Integer.parseInt(headers.get(TvHeaders.SELECTION_TYPE));
		}
		if((selType != TvURIHelper.SelectionType.SELECTION_MULTIFEED.value) &&
		   (selType != TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value)) {
			notifyonTuneCompleted("org.droidtv.tunerservice/.TunerService",uri,TvURIHelper.getBundleFromHeaders(headers));
			notifyChannelRetuned(uri);
			notifyVideoAvailable();	
		}
	}
	
	@Override
	public void onPlayFailed(Uri uri, Medium medium, int presetNumber, int reason){
		notifyonTuneFailed(uri, reason);
	}	
	
	@Override
	public void onPlayFinished(Uri uri, Medium medium, int presetNumber){
			
	}
	
	@Override
	public void onLicenseExchangeHappening(boolean status){
		
	}
	
	@Override
	public void onSeekComplete(int mode){
		Log.i(LOG_TAG,"onSeekComplete mode:"+mode);
		if(mode == ITvAbstractPlaybackListener.MODE_PVR) {
			notifySeekComplete();
		} else {
			notifyTimeshiftSeekComplete();
		}
	}	
	
	@Override
	public void onPlayError(int error, int what , int extra, int mode){
		Log.i(LOG_TAG,"onPlayError called with error:"+error+" mode:"+mode);
		if(mode == ITvAbstractPlaybackListener.MODE_PVR) {
			notifyPlayError(error);
		} else {
			notifyTimeshiftPlayError(error);
		}
		notifyVideoUnavailable(TvInputManager.VIDEO_UNAVAILABLE_REASON_TUNING);
	}

	@Override
	public void onServiceTypeDetected(int type){
	
	}

	@Override
	public void onTrickModeEnabled(boolean status, int mode){
		Log.i(LOG_TAG,"onTrickModeEnabled called with status:"+status+" mode:"+mode);
		if(mode == ITvAbstractPlaybackListener.MODE_PVR) {
			notifyTrickModeEnabled(status);
		} else {
			notifyTimeshiftTrickModeEnabled(status);
		}
	}
	
	@Override
	public void onPlayStateChanged(int state, int mode) {
		Log.i(LOG_TAG,"onPlayStateChanged called with status:"+state+" mode:"+mode);	
		if(mode == ITvAbstractPlaybackListener.MODE_PVR) {
			notifyPVRStateChanged(state);
		} else {
			notifyTimeshiftStateChanged(state);
		}
	}
	
	@Override
	public void onTimeshiftInfoChanged() {
		Log.i(LOG_TAG,"onTimeshiftInfoChanged ");	
		notifyTimeshiftInfoChanged();
	}

	@Override
	public void onLockStatusChanged(int type, int status){
	
	}

	@Override
	public void onInfo(boolean cicamAvailable) {
	}

	@Override
	public void onMPLPurposeChanged(int purpose) {
	}
}