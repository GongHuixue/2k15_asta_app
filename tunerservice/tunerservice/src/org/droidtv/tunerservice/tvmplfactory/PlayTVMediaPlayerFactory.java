package org.droidtv.tunerservice.tvmplfactory;

import org.droidtv.tunerservice.interfaces.IPlayTvMPLFactoryCallback;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.persistentstorage.ITvSettingsManager.ITvSettingsManagerNotify;
import org.droidtv.tv.persistentstorage.TvSettingsConstants; 
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tunerservice.db.CAMDetails;
import org.droidtv.tunerservice.db.CamInfoDB;
import org.droidtv.tunerservice.PlayTvDiversity;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;

import android.content.Context;
import android.util.Log;
import android.util.SparseArray;
import android.os.Handler;

public class PlayTVMediaPlayerFactory {

	private static String TAG =  "PlayTVMediaPlayerFactory";
	
	/* Client Request Types START -- ordered based on priority */
	public static final int REQUEST_TYPE_SEMISTDBY					= 0x1;
	public static final int REQUEST_TYPE_FOLLOW_MAIN 				= 0x2;
	public static final int REQUEST_TYPE_AUTO_PVR 					= 0x4;		
	public static final int REQUEST_TYPE_AUX_WATCH 					= 0x8;
	public static final int REQUEST_TYPE_DATA_ACQUISITION 			= 0x10;		
	public static final int REQUEST_TYPE_INDEPENDENT_TAD 			= 0x20; 
	public static final int REQUEST_TYPE_MAIN_WATCH 				= 0x80;
	public static final int REQUEST_TYPE_MONITOR_PIP 				= 0x100;
	public static final int REQUEST_TYPE_FOREGROUND_DATA_ACQUISITION= 0x200;	
	public static final int REQUEST_TYPE_FOREGROUND_RECORDING		= 0x400; 
	public static final int REQUEST_TYPE_BACKGROUND_RECORDING 		= 0x800; //priority ends here..
	
	protected static final int PRIORITY_REQUESTS_MASK			= 0xFFF;
	
	public static final int REQUEST_TYPE_OAD     				= 0x1000; //no seperate priority for this..
	public static final int REQUEST_TYPE_DEPENDENT_TAD			= 0x2000; //dependent on watch main or recording
	public static final int REQUEST_TYPE_TIME_SHIFT				= 0x4000; //dependent on watch main or independent tad
	public static final int REQUEST_TYPE_MAIN_INSTALLER			= 0x8000; 
	public static final int REQUEST_TYPE_AUX_INSTALLER			= 0x10000; 
	public static final int REQUEST_TYPE_MAIN_CI				= 0x20000; 
	public static final int REQUEST_TYPE_AUX_CI					= 0x40000;
    public static final int REQUEST_TYPE_PVR_CI	 				= 0x60000;	
	public static final int REQUEST_TYPE_MEDIA_FILE	 		= 0x80000;	
	
	/* backward compatibility */
	public static final int REQUEST_TYPE_RECORDING				= REQUEST_TYPE_BACKGROUND_RECORDING; //obsolete
	
	/* New addition to request types -
	REQUEST_TYPE_DATA_ACQUISITION - for epg background acquition
	REQUEST_TYPE_INDEPENDENT_TAD  - Without watch main - can happen on second tuner(if available) or first tuner[if recording
	ongoing in second tuner and tuner1 is free(recording + other app like you tube usecase) ]
	REQUEST_TYPE_FOREGROUND_RECORDING - two recordings possible, if background recording(2nd tuner) is in progress, then 
	recording will happen on 1st tuner.
	REQUEST_TYPE_BACKGROUND_RECORDING - background recording happens on 2nd tuner.
	REQUEST_TYPE_DEPENDENT_TAD - TAD streaming on watch main/recording
	*/	
	/* Client Requests Types END. */
	
	/* MediaPlayer request - IsMediaPlayerAvailable() return values  ==> To be updated after discussion with all clients*/
	public static final int STATUS_AVAILABLE 							= 0x100000;
	public static final int STATUS_NOT_AVAILABLE 						= 0x000000;
	public static final int STATUS_3D_IN_PROGRESS						= 0x200000;
	public static final int STATUS_NOTAVAILABLE_CAMVOD_IN_PROGRESS 		= 0x400000;
	public static final int STATUS_UHD_IN_PROGRESS						= 0x800000;
	public static final int STATUS_INSTALLATION_IN_PROGRESS				= 0x1000000;
	
	/*backward compatibility */
	public static final int STATUS_NOTAVAILABLE_RECORDING_IN_PROGRESS 	= STATUS_NOT_AVAILABLE | REQUEST_TYPE_BACKGROUND_RECORDING;
	public static final int STATUS_NOTAVAILABLE_MAINWATCH_NOT_IN_PROGRESS= STATUS_NOT_AVAILABLE; //really needed??
	
	/*Definition of available CAM slots*/
	public static final int CAM_NONE 		= 0;
	public static final int CAM_SLOT0 		= 1;
	public static final int CAM_SLOT1 		= 2;
	
	/*Definition of available resources managed by factory*/
	public static final int RESOURCE_NONE	=	0;
	public static final int RESOURCE_CAM 	=	1;
	public static final int RESOURCE_HDD	=	2;
	
	/*Definition of constraints managed by factory*/
	public static final int CONSTRAINT_NONE				=	0;
	public static final int CONSTRAINT_INSTALLATION 	=	1;
	public static final int CONSTRAINT_UHD				=	2;
	public static final int CONSTRAINT_3D				=	3;
	public static final int CONSTRAINT_CAM_VOD			=   4;
	
	private static final int  CAPABILITY_MAIN_TUNER_DUALMODE 	= ( REQUEST_TYPE_MAIN_WATCH | REQUEST_TYPE_SEMISTDBY | REQUEST_TYPE_FOREGROUND_RECORDING | 
														REQUEST_TYPE_DATA_ACQUISITION | REQUEST_TYPE_FOREGROUND_DATA_ACQUISITION |REQUEST_TYPE_DEPENDENT_TAD | 
														REQUEST_TYPE_INDEPENDENT_TAD | REQUEST_TYPE_TIME_SHIFT | REQUEST_TYPE_MAIN_INSTALLER | REQUEST_TYPE_OAD);
	private static final int  CAPABILITY_AUX_TUNER_DUALMODE  	= ( REQUEST_TYPE_MAIN_WATCH | REQUEST_TYPE_FOLLOW_MAIN | REQUEST_TYPE_AUTO_PVR | REQUEST_TYPE_INDEPENDENT_TAD | 
														REQUEST_TYPE_AUX_INSTALLER | REQUEST_TYPE_BACKGROUND_RECORDING | REQUEST_TYPE_DATA_ACQUISITION | 
														REQUEST_TYPE_MONITOR_PIP | REQUEST_TYPE_AUX_WATCH | REQUEST_TYPE_DEPENDENT_TAD | REQUEST_TYPE_SEMISTDBY | REQUEST_TYPE_OAD); 
														//REQUEST_TYPE_SEMISTDBY - capability added as once recording finishes in semisby, onavailable to be generated.
	private static final int  CAPABILITY_MAIN_TUNER_SINGLEMODE 	= ( REQUEST_TYPE_MAIN_WATCH | REQUEST_TYPE_SEMISTDBY | REQUEST_TYPE_FOREGROUND_RECORDING | 
														REQUEST_TYPE_DATA_ACQUISITION | REQUEST_TYPE_FOREGROUND_DATA_ACQUISITION | REQUEST_TYPE_DEPENDENT_TAD | 
														REQUEST_TYPE_AUTO_PVR | REQUEST_TYPE_TIME_SHIFT | REQUEST_TYPE_MAIN_INSTALLER | REQUEST_TYPE_INDEPENDENT_TAD | 
														REQUEST_TYPE_OAD);
	
	private static PlayTVMediaPlayerFactory	_mObj						= null;
	protected static SparseArray<PlayTVFacMediaPlayer> _instances		= new SparseArray<PlayTVFacMediaPlayer>(10); 
	protected static SparseArray<IPlayTvMPLFactoryCallback> _callbacks 	= new SparseArray<IPlayTvMPLFactoryCallback>(10);
	protected static int noOfCam 										= 2;	
	private static boolean isDualTunerDVBTC 							=	false;
	private static boolean isDualTunerDVBS								=	false;
	static private PlayTVFacMediaPlayer tuner1MPL,tuner2MPL,pvr1MPL,pvr2MPL,extnMPL,localMPL;
	//private static PlayTVFactoryCamEvaluator	camEvaluator = null;
	private Context mContext;
	Handler mhandler = null;
	
	// get dual tuner support values fron TvSettings
	final ITvSettingsManagerNotify mSettingsBinder = new ITvSettingsManagerNotify()
	{
		
		public void OnUpdate(int property) {
			if((property == TvSettingsConstants.OPTWOTUNERS) || (property == TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE))
			{
				Log.d(TAG,"PersistentStorageCallBacks : Change in Tuner Settings : property = " +property);
				readTunerInfo();
				Runnable r = new Runnable() {
					@Override
					public void run() {
						updateFacmplCapabilities();
					}
				};
				mhandler.post(r);
			}
		}
	};	
	
	private static synchronized void readTunerInfo() {
		int optiontuner = ITvSettingsManager.Instance.getInterface().getInt(
				TvSettingsConstants.OPTWOTUNERS, 0, 0);
		if(optiontuner == 1) {
			isDualTunerDVBTC = true;
			optiontuner = ITvSettingsManager.Instance.getInterface().getInt(
					TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE, 0, 0);
			if(optiontuner == 1) {				
				isDualTunerDVBS = 	true;
			} else {
				isDualTunerDVBS = 	false;
			}
			
		} else {
			isDualTunerDVBTC 	=	false;
			isDualTunerDVBS		=	false;
		}
		//Log.d(TAG,"readTunerInfo : isDualTunerDVBTC : "+isDualTunerDVBTC + "isDualTunerDVBS : " +isDualTunerDVBS);
	}
	
	private static void updateFacmplCapabilities() {
		if(tuner1MPL != null) {
			tuner1MPL.updateMediumSupport(Medium.MEDIUM_CABLE,true);
			tuner1MPL.updateMediumSupport(Medium.MEDIUM_TERRESTRIAL,true);	
			tuner1MPL.updateMediumSupport(Medium.MEDIUM_SATELLITE,true);
			if(isDualTunerDVBTC) {				
				tuner1MPL.updateCabability(CAPABILITY_MAIN_TUNER_DUALMODE);
			} else {
				tuner1MPL.updateCabability(CAPABILITY_MAIN_TUNER_SINGLEMODE);
			}
			
		}
		if(tuner2MPL != null) {			
			if(isDualTunerDVBTC) {
				tuner2MPL.updateMediumSupport(Medium.MEDIUM_CABLE,true);
				tuner2MPL.updateMediumSupport(Medium.MEDIUM_TERRESTRIAL,true);
				tuner2MPL.updateCabability(CAPABILITY_AUX_TUNER_DUALMODE);
				if(isDualTunerDVBS) {					
					tuner2MPL.updateMediumSupport(Medium.MEDIUM_SATELLITE,true);
				} else {
					tuner2MPL.updateMediumSupport(Medium.MEDIUM_SATELLITE,false);
				}
			} else {
				tuner2MPL.updateCabability(0);
			}
		}
		if(extnMPL != null) {
			extnMPL.updateMediumSupport(Medium.MEDIUM_EXTN,true);
			extnMPL.updateCabability(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH);
		}
		if(pvr1MPL != null) {
			pvr1MPL.updateMediumSupport(Medium.MEDIUM_PVRFILE,true);
			if(PlayTvDiversity.isIndependentTadSupported()) {
				pvr1MPL.updateCabability(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH | REQUEST_TYPE_DEPENDENT_TAD);
			}else {
				//if independent tad not supported, pvr playback via tad should happen in pvr1 mpl only
				pvr1MPL.updateCabability(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH | REQUEST_TYPE_DEPENDENT_TAD | REQUEST_TYPE_INDEPENDENT_TAD | REQUEST_TYPE_SEMISTDBY);
				//REQUEST_TYPE_SEMISTDBY - capability added as once independent PVR finishes in semisby, onavailable to be generated.
			}
		}
		if(pvr2MPL != null) {
			pvr2MPL.updateMediumSupport(Medium.MEDIUM_PVRFILE,true);
			pvr2MPL.updateCabability(PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD | REQUEST_TYPE_SEMISTDBY);
			//REQUEST_TYPE_SEMISTDBY - capability added as once independent PVR finishes in semisby, onavailable to be generated.
		}
		if(localMPL != null){
			localMPL.updateMediumSupport(Medium.MEDIUM_LOCALFILE,true);
			localMPL.updateCabability(PlayTVMediaPlayerFactory.REQUEST_TYPE_MEDIA_FILE);
		}
	}
	
	private void initializeFacMediaplayer() {
		TvMediaPlayer tvmpl = null;			
		//camEvaluator = new PlayTVFactoryCamEvaluator(mContext);	
		//Log.d(TAG, "MediaPlayerFactoryInstance camEvaluator -  "+ camEvaluator);
		tvmpl = TvMediaPlayer.getTvTunerMediaPlayer();		
		tuner1MPL = new PlayTVFacMediaPlayer(mContext,tvmpl,0,Medium.MEDIUM_TERRESTRIAL);
		Log.d(TAG, "MediaPlayerFactoryInstance tuner1MPL -  "+ tuner1MPL);	
		tvmpl = TvMediaPlayer.getTvAuxMediaPlayer();		
		tuner2MPL = new PlayTVFacMediaPlayer(mContext,tvmpl,0,Medium.MEDIUM_TERRESTRIAL);
		Log.d(TAG, "MediaPlayerFactoryInstance tuner2MPL -  "+ tuner2MPL);	
		/* - Not supported in TIF branch - 
		tvmpl = TvMediaPlayer.getTvExtensionMediaPlayer();
		extnMPL = new PlayTVFacMediaPlayer(mContext,tvmpl,PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH,Medium.MEDIUM_EXTN);*/
		tvmpl = TvMediaPlayer.createTvMediaPlayer();
		pvr1MPL = new PlayTVFacMediaPlayer(mContext,tvmpl,0,Medium.MEDIUM_PVRFILE);
		tvmpl = TvMediaPlayer.createTvMediaPlayer();
		pvr2MPL = new PlayTVFacMediaPlayer(mContext,tvmpl,0,Medium.MEDIUM_PVRFILE);		
		tvmpl = TvMediaPlayer.createTvMediaPlayer();
		localMPL = new PlayTVFacMediaPlayer(mContext,tvmpl,0,Medium.MEDIUM_LOCALFILE);
		updateFacmplCapabilities();
	}
	
	/*
	* The API gives dual tuner configuration based on medium & nvm/option code settings.
	* In case of DVBC/T - based on option code OPTWOTUNERS (TRUE if enabled)
	* In case of DVBS   - based on option code OPTWOTUNERS & nvm settings INSTSETTINGSDUALTUNERSATELLITE(TRUE if both enabled)
	*/
	public synchronized boolean IsDualTunerFactoryConfigEnabled(Medium medium) {
		if(medium == Medium.MEDIUM_SATELLITE) {
			if(_mObj.isDualTunerDVBS) {
				return true;
			}
			else {
				return false;
			}
		}
		else if((medium == Medium.MEDIUM_CABLE) || 
				(medium == Medium.MEDIUM_TERRESTRIAL)) {
			if(_mObj.isDualTunerDVBTC) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
	
	/* 
	* The API gives overall set dual tuner configuration based on option code OPTWOTUNERS. 
	*/
	public synchronized boolean isDualTunerFactoryConfigEnabled(){
		if(_mObj.isDualTunerDVBTC) {
			return true;
		}
		else {
			return false;
		}
	}	
	
	
	/*
	* The API gives instantiate PlayTVMediaPlayerFactory class.
	*/
	public PlayTVMediaPlayerFactory(Context context) {		  
		//Log.d(TAG,"PlayTVMediaPlayerFactory : Instantiated!!!");
		mContext=context;
		setPlayTVMediaPlayerFactoryObj(this);		
		mhandler = new Handler();
		//tvSettingsManagerInstance = ITvSettingsManager.Instance.getInterface();
		// register for tvsettings constants change for option code , tuner , user settings
		int[] properties = {TvSettingsConstants.OPTWOTUNERS, TvSettingsConstants.INSTSETTINGSDUALTUNERSATELLITE};//todo: get user settings
		//tvsettingsmanager = ITvSettingsManager.Instance.getInterface();
		ITvSettingsManager.Instance.getInterface().SetCallBacks(mSettingsBinder, properties);
		readTunerInfo();
		initializeFacMediaplayer();
	}

	private static void setPlayTVMediaPlayerFactoryObj(
			PlayTVMediaPlayerFactory playTVMediaPlayerFactory) {
		// TODO Auto-generated method stub
		_mObj=playTVMediaPlayerFactory;
	}
	
	/*
	* The API gives instance of current PlayTVMediaPlayerFactory class. (singleton)
	*/
	public static synchronized PlayTVMediaPlayerFactory getInstance() {
		//Log.d(TAG, "MediaPlayerFactoryInstance getInstance() "+ _mObj);		 
		return _mObj;
	}

	class FacMplObject {
		private PlayTVFacMediaPlayer mfacMpl = null;
		private int mStatus					 = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
	
		FacMplObject(PlayTVFacMediaPlayer facmpl, int inStatus) {
			mfacMpl = facmpl;
			mStatus	= inStatus;
		}
		
		PlayTVFacMediaPlayer getFacMplObject() {
			return mfacMpl;
		}
		
		int getStatus() {
			return mStatus;
		}
	}
			
	private FacMplObject getFacMplInstance(int clientRequestType, Medium medium, int channelId) {
		PlayTVFacMediaPlayer facmpl = null,tempfacmpl = null;
		int retVal	= PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE;
		switch(clientRequestType) {				
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING:
			/*in dual tuner - recording should always be available*/
			if(tuner2MPL.IsRequestCapable(clientRequestType,medium,channelId)) {
				facmpl 	= tuner2MPL;
			}
			break;
		
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING: //no need to add in instance??
			facmpl 	= tuner1MPL;
			break;
			
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP:
			if(!PlayTvDiversity.isTadPossibleWithPip()) {
				tempfacmpl 	= _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
			}
			if(tempfacmpl == null) {
				if(PlayTvDiversity.isMonitorPIPSupported()) {
					if(tuner2MPL.IsRequestCapable(clientRequestType,medium,channelId)) {
						facmpl 	= tuner2MPL;
					}
				}
			}else {
				retVal	= (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
			}
			break;
			
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH:
			/*in dual tuner - main watch should always be available*/
			Log.d(TAG,"getfacmpl : REQUEST_TYPE_MAIN_WATCH : tuner2 medium"+tuner2MPL.getCurrentRequestedMedium()+"tuner2 channelId"+tuner2MPL.getCurrentRequestedChannel());
			if(medium == Medium.MEDIUM_PVRFILE) {
				facmpl 	= pvr1MPL;				
			}else {
				Log.d(TAG,"getfacmpl : REQUEST_TYPE_MAIN_WATCH : medium"+medium+"channelId"+channelId);
				if(	( ((PlayTvDiversity.isOlympicUsecaseSupported()) && (noOfCam == 1)) ||
                      ((tuner1MPL.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) > 0) )	&& 
				   (((tuner2MPL.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) > 0) && 
				    ((tuner2MPL.getCurrentRequestedChannel() == channelId) && (tuner2MPL.getCurrentRequestedMedium() == medium)))) {
					/*	Two usecases where we need to check with tuner2MPL for watch main
						1.If olympic usecase supported and noofCam = 1
						2.On dual watch usecase when dual recording in progress and user zaps between two rec channels
						Above happens provided tuner2 already playing requested channels.
					*/
					facmpl = tuner2MPL;
					//no need to put in _instances?
				}
				else {
					facmpl = tuner1MPL;
				}
			}
			
			break;
		
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD:
			/* Algorithm : 
			1)Check if TAD request made with medium = PVR file, use pvr2MPL (streaming of recording playback).
			2)Check if TAD possible on second tuner - will work if no background recording.
			3)If noOfCAM = 1,check if TAD request made with medium = background recording medium &  
			  channel = background recording channel, allow streaming on tuner2MPL(termed as "winterOlympics").
			4)Check if TAD possible on first tuner - will work if no watch main, foreground recording. 
			  (user watching you tube/other application & background recording in progress)
			*/
			if(medium == Medium.MEDIUM_PVRFILE) {
				if(PlayTvDiversity.isIndependentTadSupported()) {
					facmpl = pvr2MPL;
				} else {
					facmpl = pvr1MPL;
				}
			}else {
				if((PlayTvDiversity.isIndependentTadSupported()) && 
					(PlayTVMediaPlayerFactory.STATUS_AVAILABLE == tuner2MPL.IsRequestPossible(clientRequestType,medium,channelId))) { 
					facmpl = tuner2MPL;
				} else if ((!PlayTvDiversity.isIndependentTadSupported()) &&
					(PlayTVMediaPlayerFactory.STATUS_AVAILABLE == tuner1MPL.IsRequestPossible(clientRequestType,medium,channelId))) {
					facmpl = tuner1MPL;
				} else if( ((PlayTvDiversity.isOlympicUsecaseSupported()) && (noOfCam == 1)) && 
				   (tuner2MPL.getCurrentChannel() == channelId) && (tuner2MPL.getCurrentMedium() == medium)) { 
					retVal	= PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING;
				} else if(PlayTVMediaPlayerFactory.STATUS_AVAILABLE == tuner1MPL.IsRequestPossible(clientRequestType,medium,channelId)) {
					facmpl = tuner1MPL;
				} else {
					retVal	= PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE;
				}
			}			
			break;
			
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH:
			if(!PlayTvDiversity.isTadPossibleWithPip()) {
				tempfacmpl 	= _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
			}
			if(tempfacmpl == null) {
				if(tuner2MPL.IsRequestCapable(clientRequestType,medium,channelId)) {
					facmpl 	= tuner2MPL;
				}
			}else {
				retVal	= (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
			}
			break;
		
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_DATA_ACQUISITION:
			if(tuner2MPL.IsRequestCapable(clientRequestType,medium,channelId)) {
				facmpl = tuner2MPL;
			} else {
				facmpl = tuner1MPL;
			}
			break;

		case PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_DATA_ACQUISITION:
			facmpl = tuner1MPL;
			break;
			
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN:			
			if(tuner2MPL.IsRequestCapable(clientRequestType,medium,channelId)) {
				facmpl = tuner2MPL;
			}
			break;	
			
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_AUTO_PVR:
			if(tuner2MPL.IsRequestCapable(clientRequestType,medium,channelId)) {
				facmpl = tuner2MPL;
			} else {
				facmpl = tuner1MPL;
			}
			break;
			
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY:
			if(_instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) != null) {
				retVal	= (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING);
				Log.d(TAG, "Recording Case");
			}
			if(_instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) != null) {
				retVal	= (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
				Log.d(TAG, "TAD Case");
			}			
			if(_instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_DATA_ACQUISITION) != null) {
				retVal	= (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.REQUEST_TYPE_DATA_ACQUISITION);
				Log.d(TAG, "DATA Case");
			}		
			// None of the above conditions have passed, so return mpl to ssby service
			facmpl 	= tuner1MPL;
			break;
			
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD: //no need to put in instance
			/* Algorithm : 
			1)Check if TAD request made with channel & medium equal to watch main.
			2)Check if TAD request made with channel & medium equal to recording.
			*/	
			if (((tempfacmpl = _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)) != null) &&
				(tempfacmpl.getCurrentChannel() == channelId) && 
				(tempfacmpl.getCurrentMedium() == medium)) {
				facmpl = tempfacmpl;
			} else if (((tempfacmpl = _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING)) != null) &&
				(noOfCam == 1)	&& 
				(tempfacmpl.getCurrentChannel() == channelId) &&
				(tempfacmpl.getCurrentMedium() == medium) &&
				(PlayTvDiversity.isOlympicUsecaseSupported())) {
				// if in ssby and recording of same channel is in progress, then dependent tad will be allowed.
				facmpl = tempfacmpl;
			} else if (((tempfacmpl = _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING)) != null) &&
				(tempfacmpl.getCurrentChannel() == channelId) &&
				(tempfacmpl.getCurrentMedium() == medium)) {
				// if in ssby and recording of same channel is in progress, then dependent tad will be allowed.
				facmpl = tempfacmpl;
			} else if (PlayTvDiversity.isIndependentTadSupported()) {
				tempfacmpl 	= _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING);
				if((tempfacmpl != null) && (tempfacmpl.getCurrentChannel() == channelId) && 
				   (tempfacmpl.getCurrentMedium() == medium)) {
					facmpl = tempfacmpl;
				}
			}
			break;
			
		case (PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH | PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT):
		case (PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT): //backward compatible
			facmpl 	= _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH);
			break;
		
		case (PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD | PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT):
			if(tuner2MPL.IsRequestCapable(clientRequestType,medium,channelId)) {
				facmpl 	= _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
			}
			//check with sankar - usecase of youtube + background rec + independent tad timeshift ??
			break;
			
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_OAD:
			if(STATUS_AVAILABLE == tuner1MPL.IsRequestPossible(clientRequestType,medium,channelId)) {
				facmpl = tuner1MPL;
				Log.d(TAG, "OAD using tuner1");
			} else if(STATUS_AVAILABLE == tuner2MPL.IsRequestPossible(clientRequestType,medium,channelId)) {
				facmpl = tuner2MPL;
				Log.d(TAG, "OAD using tuner2");
			} else {
				Log.d(TAG, "OAD: NO tuner is valid now");
				facmpl = null;
			}
			//facmpl 	= tuner1MPL;
			break;				
		
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER : 
			/* Need to generate onError for all other clients of factory upon AddPurpose of installer */
			facmpl 	= tuner1MPL;
			break;
		
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_INSTALLER : 
			/* Need to generate onError for all other clients of factory upon AddPurpose of installer */
			facmpl 	= tuner2MPL;
			break;
		case PlayTVMediaPlayerFactory.REQUEST_TYPE_MEDIA_FILE:
			Log.d(TAG, "Starting create REQUEST_TYPE_MEDIA_FILE ");		 
			facmpl 	= localMPL;
			break;
		default:
			break;
		}
		if(facmpl != null) {			
			retVal	= PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
		}
		return (new FacMplObject(facmpl,retVal));
	}
	
	/*
	* The API returns if media player is available or not for the request indicated by client after evaluating 
	* based on resource availability. In case if media player is not available, it will also append the reason.
	*/
	public synchronized int IsMediaPlayerAvailable(Context clientContext,
			int clientRequestType, Medium medium, int channelId) {		
		FacMplObject facmplObj 		= getFacMplInstance(clientRequestType,medium,channelId);
		int retVal 					= facmplObj.getStatus();
		if(retVal == STATUS_AVAILABLE) {
			PlayTVFacMediaPlayer facmpl = 	facmplObj.getFacMplObject();		
			if(facmpl != null) {
				retVal = facmpl.IsRequestPossible(clientRequestType,medium,channelId);
			}else {
				retVal = STATUS_NOT_AVAILABLE;
			}
		}
		Log.d(TAG,"IsMediaPlayerAvailable : clientRequestType -" + clientRequestType + "retVal - " +retVal);
		return retVal;	
	}

	/*
	* The API returns media player instance for the request indicated by client after evaluating 
	* based on resource availability. This will not add purpose.
	*/
	public synchronized PlayTVFacMediaPlayer getMPLInstance(Context clientContext,
			int clientRequestType, Medium medium, int channelId) {			
		mContext 					= clientContext;
		try {
			CAMDetails camDetails 		= new CAMDetails();
			camDetails.setMedium(medium);
			CamInfoDB Camdb 			= CamInfoDB.getInstace(clientContext);
			noOfCam 				= Camdb.getNoOfCAMS(camDetails);
		} catch(Exception e) {
			Log.d(TAG,"Exception getting CAM details" + e.getLocalizedMessage());
		}	
		Log.d(TAG,"getMPLInstance:ReqType-"+clientRequestType+"medium-"+medium+"channelId-"+channelId+"noOfCam-"+noOfCam);
		FacMplObject facmplObj 		= getFacMplInstance(clientRequestType,medium,channelId);
		int retVal 					= facmplObj.getStatus();
		PlayTVFacMediaPlayer facmpl = facmplObj.getFacMplObject();
		if((retVal == STATUS_AVAILABLE) && (facmpl != null)) {	
			retVal = facmpl.IsRequestPossible(clientRequestType,medium,channelId);			
			if(retVal == STATUS_AVAILABLE) {
				/*To keep this until all clients moves to new API*/
				if((clientRequestType & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER) ==  PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER) { 
					addConstraint(PlayTVMediaPlayerFactory.CONSTRAINT_INSTALLATION,facmpl);
				}
				_instances.put(clientRequestType, facmpl);	
				facmpl.addPurpose(clientRequestType,medium,channelId);							
				if(((clientRequestType & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) &&
				   (PlayTvDiversity.isOlympicUsecaseSupported()) && (noOfCam == 1) && 
				   (tuner1MPL.getCurrentChannel() == channelId) && (tuner1MPL.getCurrentMedium() == medium)) {
					//check for watch main only happening on tuner1
					synchronized (_callbacks) {
						if(_callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)!=null) {
							Log.d(TAG,"getMPLInstance : Triggering Olympic usecase : clientRequestType - " + clientRequestType);
							_callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH).onOlympicUsecaseUpdate(true,true);
						}
					}
				}
				
				PlayTVFacMediaPlayer sbyfacmpl = _instances.get(REQUEST_TYPE_SEMISTDBY);
				if((sbyfacmpl != null) && (sbyfacmpl != facmpl) && ((clientRequestType & PRIORITY_REQUESTS_MASK) > REQUEST_TYPE_SEMISTDBY)) {					
					sbyfacmpl.notifyError();
				}
				
				/* To handle specific usecase handling due to platform limitation - generating error on other facmpl */
				if((clientRequestType & PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) == PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) {
					if(!PlayTvDiversity.isTadPossibleWithPip()) {
						PlayTVFacMediaPlayer tempfacmpl = _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP);
						if(tempfacmpl == null) {
							tempfacmpl 	= _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH);
						}
						if(tempfacmpl != null) {
							tempfacmpl.notifyError();
						}
					}
				}
				Log.d(TAG,"getMPLInstance : returning valid facmpl :"+facmpl);
				return facmpl;
			}
		}
		Log.d(TAG,"getMPLInstance : returning NULL !!!");
		return null;
	}
	
	/*
	* The API returns media player instance for the request indicated by client after evaluating 
	* based on resource availability. This will add purpose to FacMPL as well.
	*/
	public synchronized PlayTVFacMediaPlayer acquireMPLInstance(Context clientContext,
			int clientRequestType, Medium medium, int channelId) {
		mContext = clientContext;		
		try {
			CAMDetails camDetails 		= new CAMDetails();
			camDetails.setMedium(medium);
			CamInfoDB Camdb 			= CamInfoDB.getInstace(clientContext);
			noOfCam 					= Camdb.getNoOfCAMS(camDetails);
		} catch(Exception e) {
			Log.d(TAG,"Exception getting CAM details" + e.getLocalizedMessage());
		}
		Log.d(TAG,"acquireMPLInstance:ReqType-"+clientRequestType+"medium-"+medium+"channelId-"+channelId+"noOfCam:"+noOfCam);
		FacMplObject facmplObj 		= getFacMplInstance(clientRequestType,medium,channelId);
		int retVal 					= facmplObj.getStatus();
		PlayTVFacMediaPlayer facmpl = facmplObj.getFacMplObject();
		
		if((retVal == STATUS_AVAILABLE) && (facmpl != null)) {	
			retVal = facmpl.IsRequestPossible(clientRequestType,medium,channelId);			
			if(retVal == STATUS_AVAILABLE) {
				if((clientRequestType & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER) != 0) { 
					addConstraint(PlayTVMediaPlayerFactory.CONSTRAINT_INSTALLATION,facmpl);
				}
				_instances.put(clientRequestType, facmpl);	
				facmpl.addPurpose(clientRequestType,medium,channelId);				
				if(((clientRequestType & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) &&
				   (PlayTvDiversity.isOlympicUsecaseSupported()) && (noOfCam == 1) && 
				   (tuner1MPL.getCurrentChannel() == channelId) && (tuner1MPL.getCurrentMedium() == medium)) {
					//check for watch main only happening on tuner1
					synchronized (_callbacks) {
						if(_callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)!=null) {
							Log.d(TAG,"getMPLInstance : Triggering Olympic usecase : clientRequestType - " + clientRequestType);
							_callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH).onOlympicUsecaseUpdate(true,true);
						}
					}
				}
				
				PlayTVFacMediaPlayer sbyfacmpl = _instances.get(REQUEST_TYPE_SEMISTDBY);
				if((sbyfacmpl != null) && (sbyfacmpl != facmpl) && ((clientRequestType & PRIORITY_REQUESTS_MASK) > REQUEST_TYPE_SEMISTDBY)) {					
					sbyfacmpl.notifyError();
				}
				
				/* To handle specific usecase handling due to platform limitation - generating error on other facmpl */
				if((clientRequestType & PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) == PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD) {
					if(!PlayTvDiversity.isTadPossibleWithPip()) {
						PlayTVFacMediaPlayer tempfacmpl = _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP);
						if(tempfacmpl == null) {
							tempfacmpl 	= _instances.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH);
						}
						if(tempfacmpl != null) {
							tempfacmpl.notifyError();
						}
					}
				}
				Log.d(TAG,"getMPLInstance : returning valid facmpl :"+facmpl);
				return facmpl;
			}			
		}
		Log.d(TAG,"getMPLInstance : returning NULL !!!");
		return null;
	}

	/*
	* The API will release the currently associated mediaplayer for the clientRequestType mentioned.
	* After releasing the mpl, it will also generate "OnAvailable()" for the other possible 
	* lower client requests.
	*/
	public synchronized void releaseMPLInstance(int clientRequestType, PlayTVFacMediaPlayer mpl) {
		Log.d(TAG,"releaseMPLInstance : clientRequestType -" + clientRequestType);
		_instances.remove(clientRequestType);
		if((clientRequestType & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER) != 0) { 
			removeConstraint(PlayTVMediaPlayerFactory.CONSTRAINT_INSTALLATION,mpl);
		}
		if(mpl != null) {
			mpl.removePurpose(clientRequestType);			
		}		
	}
		
	/*
	* The API will add new constraint to all facmpl. In result, facmpls will enter to
	* special mode where errors will be notified on existing active requests &
	* new requests will be dishonoured based on constraint type added.
	*/
	public synchronized void addConstraint(int constraintType,PlayTVFacMediaPlayer mpl) {
		Log.d(TAG,"addConstraint : constraintType -" + constraintType);
		if(tuner1MPL != null) tuner1MPL.addConstraint(constraintType);
		if(tuner2MPL != null) tuner2MPL.addConstraint(constraintType);
		if(pvr1MPL   != null) pvr1MPL.addConstraint(constraintType);
		if(pvr2MPL	 != null) pvr2MPL.addConstraint(constraintType);		
	}
	
	/*
	* The API will remove the constrant added previously. 
	*/
	public synchronized void removeConstraint(int constraintType,PlayTVFacMediaPlayer mpl) {
		Log.d(TAG,"removeConstraint : constraintType -" + constraintType);
		if(tuner1MPL != null) tuner1MPL.removeConstraint(constraintType);
		if(tuner2MPL != null) tuner2MPL.removeConstraint(constraintType);
		if(pvr1MPL   != null) pvr1MPL.removeConstraint(constraintType);
		if(pvr2MPL	 != null) pvr2MPL.removeConstraint(constraintType);	
	}
	
	/*
	* The API will register the call back function for requested client type.
	*/
	public synchronized void registerListener(int clientRequestType, IPlayTvMPLFactoryCallback listener) {
		//Log.d(TAG,"registerListener called from "+ clientRequestType);
		synchronized (_callbacks) {
			_callbacks.put(clientRequestType, listener);
		}
	}
		
	public synchronized void onCAMTuneRequested(boolean ena) {
		//tvTunerFactory.onCAMTuneRequested(ena);
	}
	
	/*
	* The API will unregister the call back function for requested client type.
	*/
	public synchronized void unregisterListener(int clientRequestType) {
		Log.d(TAG,"unregisterListener called from "+ clientRequestType);
		synchronized (_callbacks) {
			_callbacks.remove(clientRequestType);
		}
	}
	
	/*
	* The API returns direct media player instance for the request indicated by client.
	*/
	public synchronized PlayTVFacMediaPlayer getDirectMPLInstance(Context clientContext,int clientRequestType) {
		//Log.d(TAG,"getDirectMPLInstance called with "+ clientRequestType);
		switch(clientRequestType) {
			case REQUEST_TYPE_MAIN_CI : 
				return tuner1MPL;
			case REQUEST_TYPE_AUX_CI : 
				return tuner2MPL;
			case REQUEST_TYPE_PVR_CI:
				return pvr1MPL;
			case REQUEST_TYPE_SEMISTDBY:
				return tuner1MPL;
			case REQUEST_TYPE_INDEPENDENT_TAD:
				return _instances.get(clientRequestType);
			case REQUEST_TYPE_DEPENDENT_TAD:
				return _instances.get(clientRequestType);
			default:
				Log.d(TAG,"getDirectMPLInstance not supported for "+ clientRequestType);
			break;
		} 
		return null;
	}
}
