package org.droidtv.tunerservice.tvmplfactory;

import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.PlayTvDiversity;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tunerservice.playback.TvAbstractPlayback;
import org.droidtv.tunerservice.playback.TvChannelPlayback;
import org.droidtv.tunerservice.playback.PvrPlayback;
import org.droidtv.tunerservice.playback.LocalMediaPlayback;

import android.content.Context;
import android.util.Log;

public class PlayTVFacMediaPlayer extends PlayTvMediaPlayer {
	private String TAG 							= "PlayTVFacMediaPlayer";
	private Context mContext 						= null;
	private TvMediaPlayer mtvmpl 					= null;
	private PlayTvFacMplCapability capabilityObj 	= null;
	private TvAbstractPlayback playbackObj	 		= null;
	private int mCurrentConstraint				= PlayTVMediaPlayerFactory.CONSTRAINT_NONE;
	private Medium mCurrentMedium 					= Medium.MEDIUM_INVALID;
	private int mCurrentChannelId 					= -1;
	private Object facmplLock 						= new Object();
	
	public PlayTVFacMediaPlayer(Context context, TvMediaPlayer tvmpl,int initialPurpose,Medium medium) {
		super(context,initialPurpose,tvmpl,Medium.MEDIUM_INVALID,0); //default values for medium & cam - check later
		mContext 			= context;
		mtvmpl				= tvmpl;
		mCurrentMedium      = Medium.MEDIUM_INVALID;
		mCurrentChannelId	= -1;
		capabilityObj		= new PlayTvFacMplCapability(initialPurpose);
		
		switch(medium) {
		case MEDIUM_CABLE:
		case MEDIUM_TERRESTRIAL:
		case MEDIUM_SATELLITE:			
			playbackObj = new TvChannelPlayback(context,this);
			break;
		case MEDIUM_PVRFILE:
			playbackObj = new PvrPlayback(context,this);
			break;
		case MEDIUM_EXTN:
			//playbackObj = new PlayTvExtensions(context);
			break;
		case MEDIUM_LOCALFILE:
			playbackObj = new LocalMediaPlayback(context,this);
			break;
		default:
			Log.e(TAG, "client not ok -- error");
			break;
		}
		TAG = "PlayTVFacMediaPlayer-" + mtvmpl.getToken();
//		Log.d(TAG,"FacMPL created !!!");			
	}	
	
	/*
	* This API is to dynamically control capabilities.
	* Factory main class will indicate supported request types based on 
	* configurations such as single/dual tuner/network connections.
	*/
	public void updateCabability(int requestTypes) {
		synchronized (facmplLock) {
			if(capabilityObj != null) {
				capabilityObj.setRequestTypeSupport(requestTypes);
			}
		}
	}
	
	/*
	* This API is to dynamically control capabilities.
	* Factory main class will indicate supported mediums based on 
	* configurations such as single/dual tuner/network connections.
	*/
	public void updateMediumSupport(Medium medium,boolean enable) {
		synchronized (facmplLock) {
			if(capabilityObj != null) {
				capabilityObj.setMediumSupport(medium,enable);
			}
		}
	}
	
	/*
	* The API returns true/false if facmpl is capable of handling clientRequest 
	* for given medium.
	*/
	public boolean IsRequestCapable(int clientRequest, Medium medium, int channelId) {		
	//	Log.d(TAG,"IsRequestCapable : clientRequest -" + clientRequest);
		synchronized (facmplLock) {
			if( (capabilityObj != null) && capabilityObj.IsMediumSupported(medium) && capabilityObj.IsRequestTypeSupported(clientRequest)) {
				return true;
			}
			Log.d(TAG,"Not capable of handling the request!!!");
			return false;
		}
	}	
	
	/*
	* The API returns if request made by client is possible after evaluating current purpose of the facmpl and 
	* priority & based on resource availability. In case if media player is not available, it will also append the reason.
	* Algorithm :
	*  - Check if facmpl is Capable of handling clientRequest for given medium
	*  - Check if facmpl is under any constraints.
	*  - Check if clientRequest comes under priority management
	*  - Check if clientRequest is greater than currentpurpose, if so allow.
	*  - Exception : dual watch (two recordings active, user zaps between recording channels via TAD/normal main watch)
	*  - For all clientRequests which doesnt comes under priority management, handle via explicit switch cases.
	*/
	public int IsRequestPossible(int clientRequest, Medium medium, int channelId) {	
		int retVal = PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE;	
		boolean proceed = true;
		int currPurpose = 0;		
		synchronized (facmplLock) {
			if(IsRequestCapable(clientRequest,medium,channelId)) {
				// check if under any constraints
				if(mCurrentConstraint == PlayTVMediaPlayerFactory.CONSTRAINT_INSTALLATION) {
					if((super.getCurrentMedium() == Medium.MEDIUM_PVRFILE) || (clientRequest == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER) ||
					   (clientRequest == PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_INSTALLER)) {
						retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;						
					} else {
						proceed = false;
						retVal = PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.STATUS_INSTALLATION_IN_PROGRESS;
					}					
				} else if(mCurrentConstraint == PlayTVMediaPlayerFactory.CONSTRAINT_UHD){
					if(((clientRequest & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) > 0) || 
					  ((clientRequest & PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) > 0) ||
					  ((clientRequest & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) > 0)) {
						retVal 	=  (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.STATUS_UHD_IN_PROGRESS) ;
						proceed = false;
					}
				} else if (mCurrentConstraint == PlayTVMediaPlayerFactory.CONSTRAINT_3D) { 
					if(((clientRequest & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) > 0) || 
					  ((clientRequest & PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) > 0) ||
					  ((clientRequest & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) > 0)) {
						retVal 	=  (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.STATUS_3D_IN_PROGRESS) ;
						proceed	= false;
					}				
				} else if (mCurrentConstraint == PlayTVMediaPlayerFactory.CONSTRAINT_CAM_VOD) { 				
					retVal = PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | PlayTVMediaPlayerFactory.STATUS_NOTAVAILABLE_CAMVOD_IN_PROGRESS;						
				} 
				
				if(proceed) {			
					if(!priorityIndependentRequests(clientRequest)) {
						currPurpose = (super.getCurrentPurpose() & PlayTVMediaPlayerFactory.PRIORITY_REQUESTS_MASK);
						if(currPurpose <= clientRequest) {
							retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
						}
						else if((medium == mCurrentMedium) && (channelId == mCurrentChannelId) && 
						((clientRequest & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)) {
							//olympic usecase or zap between dual watch
							retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
						}
						else{
							/*this logic will not work if mpl availability depends on status of other mpl
							  eg: follow main when watch main doesnt exist - should be handled in main factory class */
							retVal = (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | super.getCurrentPurpose());
						}
					} else {
						switch(clientRequest) {
							case PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD:
							if((medium == super.getCurrentMedium()) && (channelId == super.getCurrentChannel())) {
								retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
							}
							break;
							
							case (PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH | PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT):
							case (PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT): //backward compatibility
							if(((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) == 0) &&
							   ((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) == 0) && //olympic
							   ((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)) {
								retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
							}
							break;
							case PlayTVMediaPlayerFactory.REQUEST_TYPE_MEDIA_FILE:
								retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
								break;
							case (PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD | PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT):
							if((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) == PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) {
								retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
							}
							break;
							
							case PlayTVMediaPlayerFactory.REQUEST_TYPE_OAD:
							if((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) == 0) {
								retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
							}
							break;
							case PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_INSTALLER:
							if(!(((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING)>0) || 
								((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP)>0) ||
								((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_DATA_ACQUISITION)>0) ||
								((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD)>0) ||
								((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH)>0))){
								//if no activities on pip active, then allow background installation on second tuner
								//send onError to follow main exception
								retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
							}
							break;
							case PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER:						
							retVal = PlayTVMediaPlayerFactory.STATUS_AVAILABLE;
							break;		
						}
						if(retVal != PlayTVMediaPlayerFactory.STATUS_AVAILABLE) {
							retVal = (PlayTVMediaPlayerFactory.STATUS_NOT_AVAILABLE | super.getCurrentPurpose());
						}
					}
				}else {
					Log.d(TAG,"Request not allowed due to constraints!!!");
				}
			}else {
				Log.d(TAG,"IsRequestPossible : facmpl is not capable of handling clientRequest -" + clientRequest);		
			}
		}
//		Log.d(TAG,"IsRequestPossible : clientRequest -" + clientRequest +"retVal -" +retVal);
		return retVal;		
	}
	
	/*
	* The API adds the clientRequest indicated by factory super class. This will be used to evaluate further requests coming
	* to this facmpl.
	* Algorithm :
	*	- Add purpose to PlayTvMediaPlayer.
	*	- Send Error to all lower clients only if they are active currently.
	*	- Exception : If foreground recording started on main watch, trigger "OnNotAvailable()" to timeshift.
	*/
	public void addPurpose(int clientRequest,Medium medium, int channelId) {
	//	Log.d(TAG,"addPurpose : clientRequest -" + clientRequest);
		int i = 0;
		
		synchronized (facmplLock) {			
			if(!priorityIndependentRequests(clientRequest)) {
				//exceptions
				if(((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT) == PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT) &&
				   ((clientRequest   == PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) || 
					(clientRequest   == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING))){
					synchronized (PlayTVMediaPlayerFactory._callbacks) {
						if(PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT)!=null) {
							PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT).onNotAvailable(clientRequest);								
						}
					}
				}
				//exceptions
				if((((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) == 0) || (medium != super.getCurrentMedium()) )&&
				   (clientRequest   == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) && (medium != Medium.MEDIUM_PVRFILE)){
					synchronized (PlayTVMediaPlayerFactory._callbacks) {
						if(PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN)!=null) {
							//reusing the API for triggering follow main upon first watch tv tuner selection
							PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN).onAvailable(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN);								
						}
					}
				}
				mCurrentMedium      = medium;
				mCurrentChannelId	= channelId;
				super.addPurpose(clientRequest);
				//sending notify error
				int lowerclientType = (clientRequest >> 0x01);			
				for(;lowerclientType>0;) {
					if((clientRequest   == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) &&
					   ((lowerclientType&PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)>0)) {
						//exception - should not send on error as session shouldn't be released.
					}else if((super.getCurrentPurpose() & lowerclientType) == lowerclientType){
							Log.d(TAG,"Sending notifyError to client" + lowerclientType);
							super.notifyError(); 
							break;		//sending one notify error should be sufficient 				
					}
					lowerclientType = (lowerclientType >> 0x01);
				}
			} else {
				super.addPurpose(clientRequest);
				//priority independent requests will not send any notify errors
			}
		}
	}	
	
	/*
	* The API removes the clientRequest indicated by factory super class. This will be used to evaluate further requests coming
	* to this facmpl.
	* Algorithm :
	*	- Exception : If we are in olympic usecase & recording stopped, need to notify client about olympic usecase exit.
	*	- Send onAvailable to all lower clients sequentially only if current facmpl capable of handling it.	
	*	- Exception : If foreground recording stopped, send "OnAvailable()" to timeshift.
	*	- Remove purpose from PlayTvMediaPlayer.
	*	- If no activity running on current facmpl, reset channel & medium.
	*/
	public void removePurpose(int clientRequest) {
//		Log.d(TAG,"removePurpose : clientRequest -" + clientRequest);
		synchronized (facmplLock) {
			//exception to reset follow main when main watch gets removed.
			if(((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) &&
				(clientRequest == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)  && (mCurrentMedium != Medium.MEDIUM_PVRFILE) ){
				synchronized (PlayTVMediaPlayerFactory._callbacks) {
					if(PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN)!=null) {
						//reusing the API for triggering follow main upon first watch tv tuner selection
						PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN).onNotAvailable(PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN);								
					}
				}
			}
		
			if( PlayTvDiversity.isOlympicUsecaseSupported() && 
			   (clientRequest ==  PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING)) {
				if((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) ==
					PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) {
					//olympic usecase exit
					super.removePurpose(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH);
					synchronized (PlayTVMediaPlayerFactory._callbacks) {
						if(PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)!=null) {
							PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH).onOlympicUsecaseUpdate(false, false);								
						}
					}
				}
			}
			super.removePurpose(clientRequest);	
			
			if(!priorityIndependentRequests(clientRequest)) {
				synchronized (PlayTVMediaPlayerFactory._callbacks) {
					int lowerclientType = (clientRequest >> 0x01);
					for(;lowerclientType>0;) {				
						if(	capabilityObj.IsRequestTypeSupported(lowerclientType) && //send if only this facmpl capable of handling
							(PlayTVMediaPlayerFactory._callbacks.get(lowerclientType)!=null)) {
							Log.d(TAG, "sending onAvailable to " + lowerclientType );
							boolean stophere = PlayTVMediaPlayerFactory._callbacks.get(lowerclientType).onAvailable(clientRequest);
							if(stophere) {
								Log.d(TAG, "client needs mpl " + lowerclientType );
								break;
							}
						}
						lowerclientType = (lowerclientType >> 0x01);
					}
				}
			
				//handling exceptions
				if(clientRequest ==  PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) {	
					synchronized (PlayTVMediaPlayerFactory._callbacks) {
						if(PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT)!=null) {
							PlayTVMediaPlayerFactory._callbacks.get(PlayTVMediaPlayerFactory.REQUEST_TYPE_TIME_SHIFT).onAvailable(clientRequest);								
						}
					}
				}
			}
			if(super.getCurrentPurpose() == 0) {
				mCurrentMedium      = Medium.MEDIUM_INVALID;
				mCurrentChannelId	= -1;
			}
		}
	}
	
	/*
	* The API will add new constraint to facmpl. In result, facmpl will enter to
	* special mode where errors will be notified on existing active requests &
	* new requests will be dishonoured based on constraint type added.
	* Algorithm :
	*	- Installer : Send error to all active priority dependent requests.
	*   - UHD/3D    : Send error to TAD/monitor pip/pip preview.
	*/
	public void addConstraint(int constraintType) {
//		Log.d(TAG,"addConstraint : constraintType -" + constraintType);
		
		synchronized (facmplLock) {
			mCurrentConstraint = constraintType;
			if(super.getCurrentMedium() != Medium.MEDIUM_PVRFILE) {
				switch(constraintType) {
				case PlayTVMediaPlayerFactory.CONSTRAINT_INSTALLATION:
					/* send on Error for all active requests as installation is being started */
					//is that enough for dependent tad/timeshift to also reset if we send to main requests??
					int lowerclientType = PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING;			
					for(;lowerclientType>0;) {
						if((super.getCurrentPurpose() & lowerclientType) == lowerclientType){
							Log.d(TAG,"Sending notifyError to client due to installation" + lowerclientType);
							super.notifyError(); 
							break;		//sending one notify error should be sufficient 				
						}
						lowerclientType = (lowerclientType >> 0x01);
					}
					break;
				case PlayTVMediaPlayerFactory.CONSTRAINT_UHD:
				case PlayTVMediaPlayerFactory.CONSTRAINT_3D:
					if(((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) > 0) || 
					   ((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) > 0) ||
					   ((super.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) > 0)) {
							Log.d(TAG,"Sending notifyError to client due to UHD/3D detection");
							super.notifyError(); 
					   }
					break;
				default:
					break;
				}
			}
		}
	}
	
	/*
	* The API will remove the constrant added previously. 
	*/
	public void removeConstraint(int constraintType) {
//		Log.d(TAG,"removeConstraint : constraintType -" + constraintType);
		synchronized (facmplLock) {
			mCurrentConstraint	= PlayTVMediaPlayerFactory.CONSTRAINT_NONE;
		}
	}
	
	/*
	* The API will return playback object. 
	*/
	public TvAbstractPlayback getPlaybackObject() {		
		return playbackObj;
	}
	
	/*
	* The API will return currently requested Channel. This will be used by clients whenever
	* they want to query last requested channel which might not be selected yet.
	*/
	public int getCurrentRequestedChannel() {
//		Log.d(TAG,"getCurrentRequestedChannel -" + mCurrentChannelId);
		return mCurrentChannelId;
	}
	
	/*
	* The API will return currently requested Medium.  This will be used by clients whenever
	* they want to query last requested medium which might not be selected yet.
	*/
	public Medium getCurrentRequestedMedium() {
//		Log.d(TAG,"getCurrentRequestedMedium -" + mCurrentMedium);
		return mCurrentMedium;
	}
	
	class PlayTvFacMplCapability {
		private int supportedMedium 		= 0;
		private int currentCapability 		= 0x00;	
		
		PlayTvFacMplCapability(int intialCapability) {			
			currentCapability 	= intialCapability;
		}
		
		public void setMediumSupport(Medium medium,boolean enable) {
			if(medium != Medium.MEDIUM_INVALID) {
				if(enable) {
					supportedMedium = (supportedMedium | (1 << medium.value)) ;
				} else {
					supportedMedium = (supportedMedium & ~(1 << medium.value)) ;
				}
			} else {
				supportedMedium = 0;	
			}
		}
				
		public boolean IsMediumSupported(Medium medium) {
		     boolean retVal = false;
		     if(medium != Medium.MEDIUM_INVALID) {
		        if((supportedMedium & (1 << medium.value)) == (1 << medium.value)) { 
		          retVal = true;
		        }
		     } else {
		        retVal = true; //need for releasempl??
		     }

			 if(medium == Medium.MEDIUM_LOCALFILE)
				retVal = true;
			  
		     return retVal;
		}

		/*bitwise ORed requestTypes*/
		public void setRequestTypeSupport(int requestTypes) {
			currentCapability = requestTypes; //always reset
		}
		public boolean IsRequestTypeSupported(int requestType) {
			boolean retVal = false;
			if((currentCapability & requestType) == requestType) {
				retVal = true;
			}
			return retVal;
		}
	}
	
	private boolean priorityIndependentRequests(int clientRequest) {
		if(clientRequest > PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) {
			return true;
		}
		return false;
	}
}

