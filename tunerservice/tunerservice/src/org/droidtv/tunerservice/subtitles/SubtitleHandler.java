package org.droidtv.tunerservice.subtitles;


import java.io.IOException;
import java.util.Map;

import org.droidtv.tunerservice.interfaces.ITextureViewCallBackListener;
import org.droidtv.tunerservice.interfaces.ITvAbstractPlaybackListener;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tunerservice.overlay.TunerServiceTextureView;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.audio.ITvAudioManager;
import org.droidtv.tv.audio.ITvAudioManager.OnTvAudioPropertyChangeListener;
import org.droidtv.tv.media.BcstConstants;
import org.droidtv.tv.media.ISubtitles;
import org.droidtv.tv.media.ITvMediaControl;
import org.droidtv.tv.media.ITvMediaControl.IonMediaChangeListener;
import org.droidtv.tv.media.ITvMediaStream;
import org.droidtv.tv.media.ITvMediaStream.TvMediaAudioInfo;
import org.droidtv.tv.media.ITvMediaStream.TvMediaSubtitleInfo;
import org.droidtv.tv.media.ITvMediaStream.TvMediaTypeInfo;
import org.droidtv.tv.media.ITxtSubtitles;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.ITvSettingsManager.ITvSettingsManagerNotify;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.util.IIntKeyValueables;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.database.ContentObserver;
import android.database.Cursor;
import android.media.tv.TvContract;
import android.net.Uri;
import android.os.Handler;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.Surface;
import android.view.View;

public class SubtitleHandler implements ITextureViewCallBackListener { 

	private static String ctag = "SubtitleHandler";

	public final static int SubtitleType_INVALID  = -1;
	public final static int SubtitleType_DVB 	  = 0;
	public final static int SubtitleType_TXT 	  = 1;
	public final static int SubtitleType_DEFAULT  = 2;
         
	public final static int STATE_INACTIVE		= 0;
	public final static int STATE_ACTIVE		= 1;

	private static final int  SubtitleMode_OFF 			= 0;
	private static final int  SubtitleMode_ON 			= 1;
	private static final int  SubtitleMode_AUTOMATIC 		= 2;

	private static final int MEDIAPLAYER_INVALIDSTATE = -1;
	private static final int MEDIAPLAYER_PLAYSTARTED = 0;
	private static final int MEDIAPLAYER_PLAYCOMPLETED = 1;
	
	private static final int PMT_NOTARRIVED = 0;
	private static final int PMT_ARRIVED = 1;
	
	private static final int INVALID_PID = 8191;
	private static final int DEFAULT_INDEX = -1;
	private static final int DEFAULT_LANGCODE = -1;

	private static final int INVALID_TOKEN = -1;
	private static final int ACTIVITY_INVALIDSTATE = -1;

	private static final int ANALOG_CHANNEL =0;
	private static final int DIGITAL_CHANNEL =1;

	private static final int PAUSE_STATE = 0;
	private static final int STARTED_STATE = 1;
	private static final int TRICKPLAY_STATE = 2;
	
	// Constants for different resolutions of subtitles
	private static final int DVBSUBTITLE_SD  = 1002; //720x576
	private static final int DVBSUBTITLE_HD = 1001; //1920x1080
	private static final int DVBSUBTITLE_NORMAL = 1003; //1280x720
	
	public static final int WIDTH_MODE_SD = 720;
	public static final int HEIGHT_MODE_SD = 576;
	public static final int WIDTH_MODE_HD = 960;
	public static final int HEIGHT_MODE_HD = 540;
	public static final int WIDTH_MODE_NORMAL = 640;
	public static final int HEIGHT_MODE_NORMAL = 720;

	private int mMplState = STARTED_STATE;
	private int mSubindex = -1;

	private int [] property;
	private int [] property_cache;
	private static final int PROPMAX = 4;

	private ISubtitles mDVBSubInterface = null;
	private ITxtSubtitles mTxtSubInterface = null;
	private PlayingSubtitles currentps = null;
	private StateMachineParams subStateMachine = null;
	private ITvSettingsManager globalSetting;
	private TvMediaPlayer tvmpl = null;
	private Context mContext= null;
	private Handler mhandler = null;
	private MediaChangeListenerClass mMediaChangeListener=null;
	private ITvSettingsManagerNotify PStorageBinder;
    private OnTvAudioPropertyChangeListenerClass mAudioPropertyChangeListener = null;
    private boolean istuner=true;
    private svcClass mTxtConn=null;
    private boolean isTimeShifted = false;	
    private boolean isDigitalChannel = true;
    private boolean mTeleTextEnabled =false;
	private boolean isOlympics = true;
	private OverlayManager mOverlayManager = null;
	private boolean mCaptionsEnabled = true;
    private boolean isMediaListenerRegistered=true;
	
	class PlayingSubtitles {
		int pid;
		int type;
		int index;
		int langcode;
		
		public PlayingSubtitles() {
			resetToDefaults();
		}
		
		public void resetToDefaults() {
			type = SubtitleType_INVALID; //create constants and use them
			pid = INVALID_PID;
			index = DEFAULT_INDEX;
			langcode = DEFAULT_LANGCODE;
		}

		public void resetToDefaultSelection() {
			type = SubtitleType_DVB; //create constants and use them
			pid = INVALID_PID;
			index = DEFAULT_INDEX;
			langcode = DEFAULT_LANGCODE;
		}
		
		public void resetToTxtSelection() {
			type = SubtitleType_TXT; //create constants and use them
			pid = INVALID_PID;
			index = DEFAULT_INDEX;
			langcode = DEFAULT_LANGCODE;
		}
	};

	class StateMachineParams {
		int token;
		int Subtitlestate; 
		int activitystate; //define activity states that a public 
		int mediaplayerstate;
		int pmtState;  // defines whether we have got Pmt or not
		Uri uri;
		
		public void resetToDefaults() {
			token = INVALID_TOKEN; //create constants and use them
			Subtitlestate = STATE_INACTIVE;
			activitystate =  STATE_ACTIVE;
			// TODO : check on this part for TIFF
			mediaplayerstate = MEDIAPLAYER_INVALIDSTATE;
		    pmtState = PMT_NOTARRIVED ;
		}
	}
	
	Surface mCurrentSubtitleSurface = null;
	TunerServiceTextureView mCurrentSubtitleTextureView = null;
	int mSubtitleOSDVisibility = View.VISIBLE;
	int mSubtitleValidationVisibility = View.VISIBLE;

	public SubtitleHandler(Context context) {
		mContext = context;
		currentps = new PlayingSubtitles();
		subStateMachine = new StateMachineParams();
		subStateMachine.resetToDefaults();
		globalSetting = ITvSettingsManager.Instance.getInterface();
		bindToTxt(false);
		mhandler = new Handler();
		RegisterTvSettingsManager();
		RegisterAudioPropertyListener();
	}
	
	public void release(boolean istuner) {
		unbindToTxt();
		unRegisterTvSettingsManager();
		unRegisterCallBacks();
	}
	
    public void releaseSurface() {
    	if(mOverlayManager!=null) {
    		mOverlayManager.removeSubtitleView();
    	}
    }

	public void onAudioFocusChanged(boolean state) {
		if (!state) {
			if (tvmpl != null) {
				disableSubtitles();
				UnRegisterOnMediaChangeListener(tvmpl);
				tvmpl = null;
				subStateMachine.token = -1;
			}
		}
	}
	
	private boolean isSubtitleSupported(Medium medium) {
		switch(medium) {
		case MEDIUM_CABLE:
			return true;
		case MEDIUM_SATELLITE:
			return true;
		case MEDIUM_TERRESTRIAL:
			return true;
		case MEDIUM_PVRFILE:
			return true;
		case MEDIUM_LOCALFILE:
			return true;
		default:
			return false;
		}
	}
	
	public void setTvMediaPlayer(PlayTvMediaPlayer playTvMediaPlayer,
			Medium medium) {
		int token = playTvMediaPlayer.getMediaPlayerInstance().getToken();
                
		if (token != subStateMachine.token) {
			subStateMachine.token = token;
			if (isSubtitleSupported(medium)) {
				onTvMediaPlayerChanged(playTvMediaPlayer);
			} else {
				unRegisterCallBacks();
			}
		}
	}

	private void onTvMediaPlayerChanged(PlayTvMediaPlayer playTvMediaPlayer) {
		//boolean isOlympicuseCasechanged = false;
		//carefully unregister -> see if we can keep this
		try {
			unRegisterCallBacks();
			tvmpl=playTvMediaPlayer.getMediaPlayerInstance();
			currentps.resetToDefaults();
			isMediaListenerRegistered = RegisterOnMediaChangeListener(tvmpl);
            RegisterAudioPropertyListener();
            
		}catch(Exception e) {
			Log.e(ctag,"onTvMediaPlayerChanged Exception"+e.toString());
		}
		
		if((playTvMediaPlayer.getCurrentPurpose() & PlayTVMediaPlayerFactory.REQUEST_TYPE_RECORDING)>0) {
			if(!isOlympics){
				Log.i(ctag,"onTvMediaPlayerChanged Enter olympics");
				isOlympics = true;
			}
        } else {
        	isOlympics = false;
        }
		/*
		if(isOlympicuseCasechanged){
			Log.e(ctag,"onTvMediaPlayerChanged isOlympicuseCasechanged" + isOlympicuseCasechanged);
			if(mCurrentSubtitleTextureView!=null) {
				//mCurrentSubtitleTextureView.setInUse(false);
				//mCurrentSubtitleTextureView.release();
			}
		}
		Log.e(ctag,"onTvMediaPlayerChanged isOlympics" + isOlympics);
		*/
	}

	private void unRegisterCallBacks() {
		if (tvmpl != null) {
			disableSubtitles();
			UnRegisterOnMediaChangeListener(tvmpl);
			UnRegisterAudioPropertyListener();
			tvmpl = null;
		}
	}
	
	public void onIAppSubtitleIndexSelected(final boolean enable,final int index)
	{
		Log.i(ctag, "onIAppSubtitleIndexSelected" +"enable" +enable +"index" +index );	

		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(enable){
					onSubtitleIndexSelected(index);
				}
				else
				{
					disableSubtitles();
				}
			}
		};
		mhandler.post(r);
	}	
	
	private void disableTextSubtitles() { 
		try {
			if (mTxtSubInterface != null) {
				mTxtSubInterface.disableSubtitles();
			}
		}catch(Exception e) {
			Log.e(ctag,"Exception while disabling TextSubtitles" + e.getLocalizedMessage());
		}
	
	}
		
	public void onSubtitleIndexSelected(final int index) {
		
		Runnable r = new Runnable() {

			@Override
			public void run() {
				try {
					TvMediaSubtitleInfo subinfo;
					ITvMediaStream itvms = tvmpl.getTvMediaPlayerContext().getTvMediaStream();
					int cur_subtype = -1;
					currentps.index = index;
					if (index != -2) {
						subinfo = itvms.getCurrentSubtitleInfo(index);
						currentps.pid = subinfo.pid;

						if (TvMediaTypeInfo.isTXTSubtitle(subinfo.type))
							cur_subtype = SubtitleType_TXT;
						else
							cur_subtype = SubtitleType_DVB;

						if (cur_subtype != currentps.type) {
							if (currentps.type == SubtitleType_TXT) {
								disableTextSubtitles();
							} else if (currentps.type == SubtitleType_DVB) {
								if (mDVBSubInterface != null) {
									mDVBSubInterface.disableSubtitles();
								}
							}
						}
						currentps.type = cur_subtype;
						currentps.langcode = subinfo.langCode;
					} else {
						if (currentps.type == SubtitleType_TXT) {
							disableTextSubtitles();
						}
						currentps.type = SubtitleType_DVB;
					}

				} catch (Exception e) {
					Log.e(ctag, "Exception in onSubtitleIndexSelected ");
				}
				
				if(mDVBSubInterface!=null) {
					mDVBSubInterface.setUserPreferredSubtitle(index);
				}
				//Selecting index explicitly so it is not a default
				//enable subtitles the current ps is updated and
				//the middleware is updated with the wish of the
				//user so that if validate becomes true after sometime
				//user gets to see what he had selected earlier
				EnableSubtitles(currentps,true);
		        if (index == -2) {
		             // Re-set the currentps.type to invalid to eliminate 
		             // calling disable subtitles accidentally.
		             currentps.type = SubtitleType_INVALID; 
		        }
			}
		};
		mhandler.post(r);
	}

	public void onModeChanged(int mode) {
		try {
			switch (mode) {
			case SubtitleMode_OFF:
				disableSubtitles();
				break;
			case SubtitleMode_ON:
				if (isDVBSubtitleAvailable()) {
					currentps.resetToDefaultSelection();
				} else {
					// Reset the user selected and select the correct 
					if((tvmpl != null) && (tvmpl.getTvMediaPlayerContext() != null)) {
						if(mDVBSubInterface!=null) {
							mDVBSubInterface.setUserPreferredSubtitle(-1);
						}
						TvMediaSubtitleInfo subinfo;
						int noSubtitles = 0;
						int index = 0;
						ITvMediaStream itvms = tvmpl.getTvMediaPlayerContext()
								.getTvMediaStream();
						/*ITvMediaControl itvmc = tvmpl.getTvMediaPlayerContext()
								.getTvMediaControl();
						int pid = itvmc.getTVMedia(BcstConstants.MEDIA_SUBTITLE);
						Log.d(ctag, "SubtitleInfo Pid =" + pid); */
						noSubtitles = itvms.getCurrentNoOfSubtitle();
						/*for (int i = 0; i < noSubtitles; i++) {
							subinfo = itvms.getCurrentSubtitleInfo(i);
							if (subinfo.pid == pid) {
								currentps.index = i;
								currentps.langcode = subinfo.langCode;
								currentps.type = SubtitleType_TXT;
							}
						} */
						if(mDVBSubInterface!=null) {
						index =  mDVBSubInterface.getCurrentSubtitle();
						}
						if(index>=0) {
							//Should we check txt subtitles here???
							subinfo = itvms.getCurrentSubtitleInfo(index);
							currentps.pid  = subinfo.pid;
							currentps.langcode = subinfo.langCode;
							currentps.index = index;
							currentps.type = SubtitleType_TXT;
						}
						if((noSubtitles==0) && (isTeletextPageStored())) {
							currentps.resetToTxtSelection();
						}
					}
				}
				EnableSubtitles(currentps, true);
				break;
			case SubtitleMode_AUTOMATIC:
				if(mDVBSubInterface!=null) {
					mDVBSubInterface.setUserPreferredSubtitle(-1);
				}
				EnableSubtitles(currentps, true);
				break;
			}
		}
		catch(Exception e) {
			Log.e(ctag,"Exception taking action onModeChanged" + e.getLocalizedMessage());
		}
	}

	public int getSubtitleMode() {
		int mode = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSUBTITLE,0,0);
		return mode;
	}

	private void updateCurrentPs(int mode,int channeltype) {
		ITvMediaStream  itvms;
		TvMediaSubtitleInfo subinfo;
		int subtype = -1;
		
		switch (mode) {
			case SubtitleMode_ON:
				try {
					itvms = tvmpl.getTvMediaPlayerContext().getTvMediaStream();
					int index =  mDVBSubInterface.getCurrentSubtitle();
					if(index>=0) {
						subinfo = itvms.getCurrentSubtitleInfo(index);
						currentps.pid  = subinfo .pid;
						if(TvMediaTypeInfo.isTXTSubtitle(subinfo.type))
							currentps.type = SubtitleType_TXT;
						else
							currentps.type = SubtitleType_DVB;
						currentps.langcode = subinfo.langCode;
						currentps.index = index;
					}
				} catch(Exception e) {
					Log.e(ctag,"Exception updateCurrentPs");
				}
				break;
			case SubtitleMode_AUTOMATIC:
				try {
					itvms = tvmpl.getTvMediaPlayerContext().getTvMediaStream();
					if(channeltype == ANALOG_CHANNEL){
						currentps.index = -1;
						currentps.type = SubtitleType_DVB;
					}
					else if(channeltype == DIGITAL_CHANNEL ) {
						if(mSubindex!=-1) { 
							subinfo = itvms.getCurrentSubtitleInfo(mSubindex);
							if (TvMediaTypeInfo.isTXTSubtitle(subinfo.type)) {
								subtype = SubtitleType_TXT;
							}
							else if (TvMediaTypeInfo.isDVBSubtitle(subinfo.type)) {
								subtype = SubtitleType_DVB;
							}
							if(subtype!=currentps.type) {
								disableSubtitles();
							}
                    	currentps.index = mSubindex;
                    	currentps.langcode = subinfo.langCode;
                    	currentps.pid = subinfo.pid;
                    	currentps.type = subtype;
                    	
                    	if(mDVBSubInterface!=null) {
                			mDVBSubInterface.setUserPreferredSubtitle(mSubindex);
                		}
                   }
				}
			}catch(Exception e) {
				Log.e(ctag,"Exception updateCurrentPs");
			}
			break;
		}
	}

	public void setsurface(int type)
	{
		int extype = TunerServiceTextureView.EXSUBTTILE_LIVE;
		if(isTimeShifted) {
			extype = TunerServiceTextureView.EXSUBTTILE_TIMESHIFTED;
		}
		if(isOlympics) {
			extype = TunerServiceTextureView.EXSUBTTILE_OLYMPICS;
		}
		if(mCurrentSubtitleTextureView!=null) {
			if(mCurrentSubtitleTextureView.isAvailable()==true)
			{
				if(mCurrentSubtitleTextureView.equals(type, extype)){
					if(type==SubtitleType_DVB) {
						if(!mCurrentSubtitleTextureView.isInUse()) {
							try {
								if(mDVBSubInterface!=null) {
									mDVBSubInterface.setSurface(mCurrentSubtitleTextureView.getSurface());
									mCurrentSubtitleTextureView.setInUse(true);
								}
							} catch(Exception e) {
								Log.e(ctag, "Exception caught while setSurface text subtitle"+e.getLocalizedMessage());
							}
						}
					}
					else if(type==SubtitleType_TXT) {
						if(!mCurrentSubtitleTextureView.isInUse()) {
							if(mTxtSubInterface!=null) {
								mTxtSubInterface.setSurface(mCurrentSubtitleTextureView.getSurface());
								mCurrentSubtitleTextureView.setInUse(true);
							}
						}
					}
				} else {
					mCurrentSubtitleTextureView.setInUse(false);
					requestSubitleView(type,extype);
				}
			}
		}
		else
		{
			Log.v(ctag,"isSurfaceAvailable has become false.");
			requestSubitleView(type,extype);
		}
	} 

	private boolean validateSubtitleEnable() {
		int currentMode = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSUBTITLE,0, 0);

		if ((globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE,0, 0) == 1) && (globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_OSD_IDSPLAY,0, 0) == 0)) {
			currentMode = 0;
		}

		// add false conditions on top and true conditions below them
		try {
			
			if(mSubtitleOSDVisibility==View.INVISIBLE) {
				Log.v(ctag, "mSubtitleOSDVisibility is set to INVISIBLE");
				return false;
			}
			
			if(!mCaptionsEnabled) {
				Log.v(ctag, "mCaptionsEnabled is set to off Don't Enable");
				return false;
			}
			
			if(mMplState != STARTED_STATE){
				Log.v(ctag,"mMplState not fine " + mMplState);
				return false;
			}
			
			if(currentMode==0) {
				Log.v(ctag, "Subtitles state is Off Don't Enable");
				return false;
			}
			
			ITvMediaControl itvmc = tvmpl.getTvMediaPlayerContext().getTvMediaControl();
			if(itvmc.getLockStatus() == true) {
				Log.v(ctag, "getLockStatus returns Locked Don't Enable");
				return false;
			}
			if(itvmc.getCurrentScramblingStatus() == ITvMediaControl.SCRAMBLING_STATUS_SCRAMBLED) {
				Log.v(ctag,"getCurrentScramblingStatus returns scrambled Don't Enable");
				return false;
			}
			if(currentMode==1) {
				Log.v(ctag, "Subtitles state is ON Enable");
				return true;
			}
			if(currentMode==2) {
				Log.v(ctag, "Subtitles state is Automatic");
				if (isTeletextPageStored()) {
					currentps.resetToTxtSelection();
					if (IsAudiomuted())
						return true;
					else
						return false;
				} else {
					if ((!isDigitalChannel) && IsAudiomuted()) {
						updateCurrentPs(2, ANALOG_CHANNEL);
						return true;
					} else if ((isDigitalChannel) && enableAutomaticsubtitle()) {
						updateCurrentPs(2, DIGITAL_CHANNEL);
						return true;
					} else
						return false;
				}
			}
		} catch (Exception e) {
			Log.e(ctag,	"validateSubtitleEnable::Caught Exception : "
							+ e.getLocalizedMessage());
			return false;
		}
		return false;
	}

	public void onSubtitleChanged() {

		if ((subStateMachine.mediaplayerstate == MEDIAPLAYER_PLAYCOMPLETED) && 
				(subStateMachine.activitystate == STATE_ACTIVE)) {

			try {
				mDVBSubInterface = tvmpl.getTvMediaPlayerContext().getSubtitles();
			} catch (Exception e) {
				Log.e(ctag,	"getSubtitles::Caught Exception : "	+ e.getLocalizedMessage());
				return;
			}
			synchronized (currentps) {
				PlayingSubtitles ps = GetPlayingSubtitleInfo();
				int mode = getSubtitleMode();

				Log.d(ctag, "onSubtitleChanged: ps pid -:  " + ps.pid + "current pid " + currentps.pid + "type " + currentps.type 
                                             + "current Langcode" + currentps.langcode);
				if (ps.pid == INVALID_PID) {
					if (currentps.type == SubtitleType_DVB) {
						if (mDVBSubInterface != null) {
							mDVBSubInterface.disableSubtitles();
						}
					} else if (currentps.type == SubtitleType_TXT) {
						disableTextSubtitles();
					}
					
					if (mode > 0) {
						if(isTeletextPageStored()) {
							currentps.resetToTxtSelection();
							EnableSubtitles(currentps,true);
							unregisterContentObserver();
							return;
						}
					}
					if (!isSubtitleNotAvailable()) {
						if (mode==2) {
							EnableSubtitles(currentps,true);
							return;
						}
					}
				}
				if (((subStateMachine.Subtitlestate==STATE_ACTIVE)&&(ps.pid==currentps.pid)&&(ps.type==currentps.type)&&(ps.langcode==currentps.langcode))|| 
						(ps.index == -2)) {
					Log.v(ctag, "onSubtitleChanged :exiting .... ");
					// This to hide the subtitle which is already playing when
					// we dynamically change the primary subtitle language and none
					// gets selected and we sill reset the currentps to default
					if((ps.index == -2)){
						if (currentps.type == SubtitleType_DVB) {
							// No need to call explicitly disable 
							// as tvserver would have already done stop media
							// calling disable will reset the None index.
                            currentps.resetToDefaults();
						}
						else if (currentps.type == SubtitleType_TXT) {
							disableTextSubtitles();
							currentps.resetToDefaults();	
						}
					}			
					return;
				}

				// If user selects a different type of subtitles
				// then onMediaStateChanged notification comes and
				// then the disable calls will go from here

				if (ps.type != currentps.type) {
					if (currentps.type == SubtitleType_DVB) {
						if (mDVBSubInterface != null) {
							mDVBSubInterface.disableSubtitles();
						}
					} else if (currentps.type == SubtitleType_TXT) {
						disableTextSubtitles();
					}
				}

				currentps.pid = ps.pid;
				currentps.type = ps.type;
				currentps.index = ps.index;
				currentps.langcode = ps.langcode;
				
				EnableSubtitles(currentps,true);
			}
		} else {
			Log.v(ctag, "subStateMachine mediaplayerstate is:"
					+ subStateMachine.mediaplayerstate);
		}
	}

	private PlayingSubtitles GetPlayingSubtitleInfo() {
		int noSubtitles=0;
		PlayingSubtitles ps = new PlayingSubtitles();

		TvMediaSubtitleInfo subinfo;

		ITvMediaControl itvmc = tvmpl.getTvMediaPlayerContext().getTvMediaControl();
		ITvMediaStream  itvms = tvmpl.getTvMediaPlayerContext().getTvMediaStream();

		ISubtitles isub = tvmpl.getTvMediaPlayerContext().getSubtitles();
                
		if(isub!=null) {
			ps.index = isub.getCurrentSubtitle();
			Log.v(ctag,"GetPlayingSubtitleInfo: getCurrentSubtitle returns " + ps.index);

			if(ps.index==-2){
				Log.d(ctag,"GetPlayingSubtitleInfo: Subtitle None Selected");
			}
			else {
				if(ps.index >=0) 
				{
					subinfo = itvms.getCurrentSubtitleInfo(ps.index);
					ps.langcode = subinfo.langCode;
                    ps.pid = subinfo.pid;
					if (TvMediaTypeInfo.isTXTSubtitle(subinfo.type)) {
						ps.type = SubtitleType_TXT;
					}
					else if (TvMediaTypeInfo.isDVBSubtitle(subinfo.type)) {
						ps.type = SubtitleType_DVB;
						ps.index = -1;
					}
					else {
						Log.d(ctag,"GetPlayingSubtitleInfo Unknown type");
					}

				}
				else if (ps.index == -1) {
					ps.pid = itvmc.getTVMedia(BcstConstants.MEDIA_SUBTITLE);
					Log.i(ctag,"GetPlayingSubtitleInfo Pid =" + ps.pid);
					noSubtitles = itvms.getCurrentNoOfSubtitle();
					for(int i=0;i<noSubtitles;i++) {
						subinfo = itvms.getCurrentSubtitleInfo(i);
						Log.i(ctag,"subinfo pid" +subinfo.pid + "subinfo.langCode" +subinfo.langCode);
						if(subinfo.pid==ps.pid)	{
							ps.index = i;
							ps.langcode = subinfo.langCode;
							if (TvMediaTypeInfo.isTXTSubtitle(subinfo.type)) {
								Log.v(ctag,"GetPlayingSubtitleInfo TXT lang code " + ps.langcode);
								ps.type = SubtitleType_TXT;
							}
							else if (TvMediaTypeInfo.isDVBSubtitle(subinfo.type)) {
								Log.v(ctag,"GetPlayingSubtitleInfo DVB");
								ps.type = SubtitleType_DVB;
								ps.index = -1;
							}
							else {
								Log.d(ctag,"GetPlayingSubtitleInfo Unknown type");
							}
							break;
						}
					}	
				}
			}
		}
		return ps;
	}

	private synchronized void EnableSubtitles(PlayingSubtitles ps, boolean defaultsel) {
		// Check TvSettings for the current subtitles setting and enable
		boolean validatepassed = false;
		validatepassed = validateSubtitleEnable();
		
		if ((validatepassed) || (!defaultsel)) {
			mSubtitleValidationVisibility = View.VISIBLE;
			if(!defaultsel) {
				if ((globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSUBTITLE,0,0) == 2)) {
					ps = currentps;
				}
			}
			
			if (ps.type == SubtitleType_TXT) {
				try {
					if (mTxtSubInterface != null) {
						setsurface(SubtitleType_TXT);
						if(mCurrentSubtitleTextureView!=null) {
							if (mCurrentSubtitleTextureView.isInUse()) {
								mCurrentSubtitleTextureView.setVisibility(View.VISIBLE);
								Log.d(ctag, "Calling Enable subtitles for TXT");
								mTxtSubInterface.enableSubtitles(ps.index);
								subStateMachine.Subtitlestate = STATE_ACTIVE;
							}
						}
					}
				} catch(Exception e) {
					Log.e(ctag, "Exception caught while enabling text subtitle"+e.getLocalizedMessage());
				}
			} else if (ps.type == SubtitleType_DVB) {
				if (mDVBSubInterface != null) {
					setsurface(SubtitleType_DVB);
					if(mCurrentSubtitleTextureView!=null) {
						if (mCurrentSubtitleTextureView.isInUse()) {
							mCurrentSubtitleTextureView.setVisibility(View.VISIBLE);
							Log.d(ctag, "Calling Enable subtitles for DVB");
							mDVBSubInterface.enableSubtitles(ps.index);
							subStateMachine.Subtitlestate = STATE_ACTIVE;
						}
					}
				}
			}
		} else {
			// setVisibility to INVISIBLE only if the mCurrentSubtitleTextureView is available
			// otherwise it may lead to problem
			mSubtitleValidationVisibility = View.INVISIBLE;
			if( (mCurrentSubtitleTextureView!=null) && (mCurrentSubtitleTextureView.isAvailable())) {
				mCurrentSubtitleTextureView.setVisibility(View.INVISIBLE);
			}
		}
	}
	
	private void unbindToTxt() {
		if( (mTxtConn!=null) && (mTxtSubInterface!=null) ) {
			mContext.getApplicationContext().unbindService(mTxtConn);
			mTxtConn = null;
			mTxtSubInterface = null;
		}
	}
	
	private void bindToTxt(boolean retry) {
		mTxtConn = new svcClass(retry);
		Intent intent = new Intent("org.droidtv.teletext.SUBTITLE");
		intent.putExtra("CrashRecovery", true);
		mContext.getApplicationContext().bindService(intent,mTxtConn,Context.BIND_AUTO_CREATE);
	}

	class svcClass implements ServiceConnection {
		boolean lRetry = false;
		
		svcClass(){
			lRetry = false;
		}
		
		svcClass(boolean retry){
			lRetry = retry;
		}
		
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			try {
				service.linkToDeath(new ServiceDeathHandler(), 0);
			} catch (RemoteException e) {
				Log.e(ctag,"onServiceConnected :RemoteException");
			}
			mTxtSubInterface = ITxtSubtitles.Instance.asInterface(service);
			
			if(lRetry) {
				lRetry = false;
				EnableSubtitles(currentps,true);
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			mTxtSubInterface = null;
		}
	}

	class ServiceDeathHandler implements IBinder.DeathRecipient {

		@Override
		public void binderDied() {
			Log.e(ctag, "org.droidtv.teletext.SUBTITLE has died. Re-connecting...");
			mTxtSubInterface = null;
			mTxtConn = null;
			releaseSurface();
			bindToTxt(true);
		}
	}
	
	public void onPlayStarted(Uri mediaPlayerUri) {
		// Reset the type as we could have selected none explicitly
		if (currentps.type == SubtitleType_INVALID) {
			currentps.type = SubtitleType_DVB;	
		}
		disableSubtitles();
		/*if((mCurrentSubtitleTextureView!=null) && 
			(mCurrentSubtitleTextureView.isAvailable())) {
			Log.d(ctag,"onPlayStarted made Visibility INVISIBLE");
			mCurrentSubtitleTextureView.setVisibility(View.INVISIBLE);
		}
		*/
		if(mDVBSubInterface!=null) {
			mDVBSubInterface.setUserPreferredSubtitle(-1);
		}
		subStateMachine.mediaplayerstate 	= MEDIAPLAYER_PLAYSTARTED;
		subStateMachine.pmtState 			= PMT_NOTARRIVED;
		mhandler.removeCallbacksAndMessages(null);
	}

	public void onPlayCompleted(Uri uri, Map<String, String> headers) {
		subStateMachine.uri = uri;
		subStateMachine.mediaplayerstate = MEDIAPLAYER_PLAYCOMPLETED;
		mMplState = STARTED_STATE;
		try {
			if((isMediaListenerRegistered == false) && (tvmpl != null)){
				isMediaListenerRegistered = RegisterOnMediaChangeListener(tvmpl);
			}
			if(uri!=null) { 
				if(TvContract.isChannelUriForTunerInput(uri)) {
					registerContentObserver();
					istuner = true;
					if(headers!=null) {
						if(headers.containsKey(TvHeaders.MODE)){
							if(TvHeaders.MODE_ANALOG==
								Integer.parseInt(headers.get(TvHeaders.MODE))) {
								isDigitalChannel = false;
								if(isTeletextPageStored()) {
									currentps.resetToTxtSelection();
									EnableSubtitles(currentps, true);
								}
								return;
							}else {
								isDigitalChannel = true;
							}
						}
					}
				} else {
					unregisterContentObserver();
					istuner = false;
					isDigitalChannel = true;
				}
			}
	        onSubtitleChanged();
		}catch(Exception e) {
			Log.e(ctag,"Exception "+ e.getLocalizedMessage());
		}
	}

	public void onUriChanged(final Uri mediaPlayerUri) {
		
		if(istuner) {
			if(mediaPlayerUri!=null) {
				try{
					String c = mediaPlayerUri.getQueryParameter("playback");
					if((c.equalsIgnoreCase("LIVE_PAUSE"))){
						OnPause();
					}
					else if(c.equalsIgnoreCase("URL_PLAY")){
						mMplState = STARTED_STATE;
				    }		
				}catch(Exception e){
					Log.e(ctag,"exception");
					OnStop();
				}
			}
		}
	}
	
	private void OnPause() {
		mMplState = PAUSE_STATE;
        isTimeShifted = true;
		disableSubtitles();
		subStateMachine.pmtState = PMT_NOTARRIVED;
	}
	
    private void OnStop() {
		if(isTimeShifted == true)
		{
    	    isTimeShifted = false;
    	    disableSubtitles();
            //Re-set mMplState to STARTED_STATE as we may jump from pause
            //to Live directly
    	    mMplState = STARTED_STATE;
    	    subStateMachine.pmtState = PMT_NOTARRIVED;
		}
    }
	
	public void onPlayStateChanged(int state, int mode) {
		switch(state) {
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_PLAYING:
				// resume subtitles if not playing
				if(mode == ITvAbstractPlaybackListener.MODE_PVR) {
					mMplState = STARTED_STATE;
					onSubtitleChanged(); 
				} else {
					isTimeShifted = true;
					// Setting state to starting, so onMediaStateChanged notification 
					// will be processed.
					mMplState = STARTED_STATE;
					// onSubtitleChanged() is done to trigger PMT arrived again, since last
					// disable would have reset currentps to default and wont start until PMT has
					// arrived.
					onSubtitleChanged();
				}
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_PAUSED:
				if(mode == ITvAbstractPlaybackListener.MODE_PVR) {
					mMplState = PAUSE_STATE;
					disableSubtitles();
				} else {
					OnPause();
				}
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_TRICKPLAY:
				// Stop subtitles
				mMplState = TRICKPLAY_STATE;
				disableSubtitles();
			break;
			case ITvAbstractPlaybackListener.PLAYBACK_STATE_STOPPED:
				// No Action
				if(mode != ITvAbstractPlaybackListener.MODE_PVR) {
					OnStop();
					// onSubtitleChanged() is done to trigger PMT arrived again, since last
					// disable would have reset currentps to default and wont start until PMT has
					// arrived.
					onSubtitleChanged();
				}
				else{
					//PVR playback stopped. reset the mplstate to default STARTED_STATE
					mMplState = STARTED_STATE;
				}
			break;
			default:
			break;
		}
	}

	private void disableSubtitles() {
		synchronized(currentps) {
			subStateMachine.Subtitlestate = STATE_INACTIVE;
			Log.v(ctag,"disableSubtitles SubtitleType is :" +currentps.type);
			if(currentps.type==SubtitleType_TXT) {
				disableTextSubtitles();
			}
			else if (currentps.type==SubtitleType_DVB) {
				if(mDVBSubInterface!=null) {
					mDVBSubInterface.disableSubtitles();
				}
			}
			currentps.resetToDefaults();
		}
	}

	private boolean RegisterOnMediaChangeListener(TvMediaPlayer tvmp) {	
		try {
			ITvMediaControl tvmc = tvmp.getTvMediaPlayerContext().getTvMediaControl();
            if(tvmc != null)
			{
			    mMediaChangeListener = new MediaChangeListenerClass();
			    tvmc.registerListenerCallback((IonMediaChangeListener) mMediaChangeListener);
			}
			else
			{
				return false;
			}
		}catch(Exception e) {
			Log.e(ctag,"Caught exception in RegisterOnMediaChangeListener ");
			return false;
		}
		return true;
	}

	private void UnRegisterOnMediaChangeListener(TvMediaPlayer tvmp) {
		try {
			ITvMediaControl tvmc = tvmp.getTvMediaPlayerContext().getTvMediaControl();	
			tvmc.unRegisterListenerCallback((IonMediaChangeListener) mMediaChangeListener);
		} catch(Exception e) {
			Log.e(ctag,"Caught exception in UnRegisterOnMediaChangeListener ");
		}
	}
	
	private void onScramblingStatusChanged(int media, int status) {
		synchronized(currentps) {
			switch(status)
			{
			case ITvMediaControl.SCRAMBLING_STATUS_SCRAMBLED:
				Log.d(ctag,"onScramblingStatusChanged disable subtitles with type" +currentps.type);
				if((currentps.type == SubtitleType_DVB) && (mDVBSubInterface!=null))
				{
					mDVBSubInterface.disableSubtitles();
				}
				else if((currentps.type ==SubtitleType_TXT) && (mTxtSubInterface!=null))
				{	
					disableTextSubtitles();
				}
				break;
			case ITvMediaControl.SCRAMBLING_STATUS_UNSCRAMBLED:
				Log.d(ctag,"onScramblingStatusChanged enable subtitles");
				if(currentps.type!=SubtitleType_INVALID) {
					EnableSubtitles(currentps,true);
				}
				break;
			default:
				Log.d(ctag,"onScramblingStatusChanged in default with type" +currentps.type);
				break;
			}
		}
	}		
	
	public void RegisterTvSettingsManager()
	{
		property = new int [PROPMAX];
		property_cache = new int [PROPMAX];
/*============ START TPV HTV CHANGE # When PBS mode enable Subtitle on startup feature ============== */
		if (globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE, 0, 0) == TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON)
		{
			int value = 0;
			if (globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_ENABLE_SUBTITLE, 0, 0) == TvSettingsDefinitions.PbsEnableSubtitle.PBSMGR_ENABLE_SUBTITLE_ON)
				value = globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_SUBTITLE_ON_STARTUP, 0, 0);
			globalSetting.putInt(TvSettingsConstants.INSTSETTINGSSUBTITLE,0,value);
		}
/*============ END TPV HTV CHANGE # When PBS mode enable Subtitle on startup feature ============== */
		property[0] = TvSettingsConstants.INSTSETTINGSSUBTITLE;
		property_cache[0] = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSUBTITLE,0,0);

		property[1] = TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE;
		property_cache[1] =  globalSetting.getInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,0);

		property[2] = TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE;
		property_cache[2] =  globalSetting.getInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,0);

		property[3] = TvSettingsConstants.PBSMGR_PROPERTY_OSD_IDSPLAY;
		property_cache[3] =  globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_OSD_IDSPLAY,0,0);

		PStorageBinder = new ITvSettingsManagerNotify() {
			
		 public	void OnUpdate(int prop) {
				int value ;
				int value3 ;
				switch (prop) {
				case TvSettingsConstants.PBSMGR_PROPERTY_OSD_IDSPLAY:
				case TvSettingsConstants.INSTSETTINGSSUBTITLE:
					value = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSUBTITLE,0,0);
					value3 = globalSetting.getInt(TvSettingsConstants.PBSMGR_PROPERTY_OSD_IDSPLAY,0,0);	

					if ((property_cache[0] != value) || (property_cache[3] != value3)) {
						property_cache[0] = value;
						property_cache[3] = value3;
						if (subStateMachine.activitystate == STATE_ACTIVE) {
							if (value3 == 0) {
								value = 0;
							}
							final int val = value;
							Runnable r = new Runnable() {
							@Override
							public void run() {
								onModeChanged(val);
							}
						};
						mhandler.post(r);
                                          }
					}
					break;
				case TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE:
					value = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE,0,0);
                    if (property_cache[1] != value) {
					property_cache[1] = value;
						if (subStateMachine.activitystate == STATE_ACTIVE) {
							if ((globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 0) == 2)) {
								Runnable r = new Runnable() {
									@Override
									public void run() {
										EnableSubtitles(currentps,true);
									}
								};
								mhandler.post(r);

							}
						}
					}
					break;
				case TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE:
					value = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE,0,0);;
					if (property_cache[2] != value) {
						property_cache[2] = value;
					}
					break;
				}
			}							
		};
		globalSetting.SetCallBacks(PStorageBinder, property);
	}
	
	private void unRegisterTvSettingsManager(){
		globalSetting.UnSetCallBacks(PStorageBinder, property);
	}
	

	private void requestSize(final int width, final int height) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(mCurrentSubtitleTextureView!=null) {
					mCurrentSubtitleTextureView.setLayoutTransformParams(width,height);
				}
			}
		};
		mhandler.post(r);
	}

	class MediaChangeListenerClass extends IonMediaChangeListener {			
		@Override
		public void onLockStatusChanged(final int type, final int status)
		{
			Runnable r = new Runnable() {
				@Override
				public void run() {
					synchronized(currentps) {
						if(currentps.type==SubtitleType_DVB) {
							if(mDVBSubInterface!=null) {
								if(status==1) {
									mDVBSubInterface.disableSubtitles();	
								}
								else {
									if((subStateMachine.pmtState == PMT_ARRIVED ) && (subStateMachine.mediaplayerstate == MEDIAPLAYER_PLAYCOMPLETED)){
										EnableSubtitles(currentps,true);
									}
								}
							}
						}
						else if(currentps.type==SubtitleType_TXT) {
							if(mTxtSubInterface!=null) {
								if(status==1) {
									disableTextSubtitles();
								}
								else {
									if((subStateMachine.pmtState == PMT_ARRIVED) && (subStateMachine.mediaplayerstate == MEDIAPLAYER_PLAYCOMPLETED)){
										EnableSubtitles(currentps,true);
									}
								}
							}
						}
					}
				}
			};
			mhandler.post(r);
		}
								
		@Override
		public void onMediaStateChanged(int media) {
			Log.v(ctag,"onMediaStateChanged " + media + " mMplState " + mMplState);
			
			if(subStateMachine.activitystate == STATE_ACTIVE) {
				switch(media) {
				case DVBSUBTITLE_SD:
					requestSize(WIDTH_MODE_SD,HEIGHT_MODE_SD);
					break;
				case DVBSUBTITLE_HD:
					requestSize(WIDTH_MODE_HD,HEIGHT_MODE_HD);
					break;
				case DVBSUBTITLE_NORMAL:
					requestSize(WIDTH_MODE_NORMAL,HEIGHT_MODE_NORMAL);
					break;
				case ITvMediaControl.MEDIA_SUBTITLE:
					subStateMachine.pmtState = PMT_ARRIVED;
					if(mMplState == STARTED_STATE) {
						if(subStateMachine.mediaplayerstate != MEDIAPLAYER_PLAYCOMPLETED) {
							Log.v(ctag,"returning as onMediaEvent has come before PLAYCOMPLETED");
							return ;
						}
						Runnable r = new Runnable() {
						@Override
						public void run() {
							onSubtitleChanged();
							}
						};
						mhandler.post(r);
					}
					break;
				case ITvMediaControl.MEDIA_AUDIO:
					Runnable r = new Runnable() {
						@Override
						public void run() {
							if((subStateMachine.pmtState == PMT_ARRIVED)  && (subStateMachine.mediaplayerstate == MEDIAPLAYER_PLAYCOMPLETED)){
								onAudioChanged();
							}
							else {
								Log.d(ctag,"onAudioChanged not posted as PMT has not arrived: " + subStateMachine.pmtState);
							}
						}
					};
					mhandler.post(r);
				default:
					break;
				}
			}
		}

		@Override
		public void onScramblingStatusChanged(final int media, final int status) {
			Log.v(ctag,"onScramblingStatusChanged status " + status + "pmtState" +subStateMachine.pmtState);
			Runnable r = new Runnable() {
				@Override
				public void run() {
					if((subStateMachine.activitystate == STATE_ACTIVE) && (subStateMachine.pmtState == PMT_ARRIVED) && (subStateMachine.mediaplayerstate == MEDIAPLAYER_PLAYCOMPLETED)){
						SubtitleHandler.this.onScramblingStatusChanged(media,status);
					}
				}
			};
			mhandler.post(r);
		}	
	}	

		

	public boolean enableAutomaticsubtitle()
	{
		// TODO : Revisit this code 
		

		boolean result =false;
		int mAudioLang =0;
		int mSubtitlelang =0;
		
		mAudioLang = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSPREFERREDAUDIOLANGUAGE, 0, 0);
		if(!isInstalledCountryFrance()) // Other than France
		{
			mSubtitlelang = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSPREFERREDSUBTITLELANGUAGE, 0, 0);
		}
		else  // France 
		{
			mSubtitlelang =TvSettingsDefinitions.InstSettingsPreferredPrimaryTxtLanguageConstants.FRENCH; // French
		}
		// Check whether the subtitle list contains the user seleted Primary 
		// subtitle language then check whether the Audio is muted or whether the
		// currently playing audio is different than the user selected primary language.
		// In case of France check for whether the list of subtitles are having French
		// and whether the currenly playing audio language is other than French.
		if(CompareSubtitleLang(mSubtitlelang))
		{
			if(IsAudiomuted() || !CompareAudioLang(mAudioLang))
				return true;
		}
		return result;
	}

	public boolean CompareAudioLang(int mAudioLang)
	{
		// TODO : Revisit this code and cleanup use of tvmpl safe??? 
		
		Log.v(ctag,"CompareAudioLang and user prefered Lang is:" +mAudioLang);

		boolean result =false;

		TvMediaAudioInfo mCurrentAudioInfo = null;
		try {
			ITvMediaControl itvmc = tvmpl.getTvMediaPlayerContext().getTvMediaControl();
			mCurrentAudioInfo = itvmc.getTVAudio();
          
			if((mCurrentAudioInfo == null)|| (mCurrentAudioInfo.pid == INVALID_PID)) {
				Log.d(ctag,"No Audio is getting Played currently Received Pid is 8191");
				return false;
			}
            if(mCurrentAudioInfo.langCode == mAudioLang) {
            	Log.v(ctag,"mCurrentAudioInfo.langCode:" +mCurrentAudioInfo.langCode +"mAudioLang" +mAudioLang);
            	result = true;
            }
		} catch(Exception e) {
			Log.e(ctag,"Exception in CompareAudioLang");
		}
		return result;
	}
	
	public boolean CompareSubtitleLang(int mSubtitlelang) {		
		// TODO : Revisit this code and cleanup
		boolean result = false;
		mSubindex = -1;
		TvMediaSubtitleInfo mCurrentSubInfo = null;

		try {
			ITvMediaStream itvms = tvmpl.getTvMediaPlayerContext().getTvMediaStream();
			int hearingImparedStatus = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSHEARINGIMPAIRED, 0, 0);
			int noSubtitle = itvms.getCurrentNoOfSubtitle();
			if(hearingImparedStatus == 1)
			{
				for (int i = 0; i < noSubtitle; i++) {
					mCurrentSubInfo = itvms.getCurrentSubtitleInfo(i);
					if (mCurrentSubInfo.langCode == mSubtitlelang)  {
						if(TvMediaTypeInfo.isHearingImpaired(mCurrentSubInfo.type)){
							result = true;
							mSubindex = i;
							break;
						}
						mSubindex = i;
					}
				}
			}
			else {
				for (int i = 0; i < noSubtitle; i++) {
					mCurrentSubInfo = itvms.getCurrentSubtitleInfo(i);
					if ((mCurrentSubInfo.langCode == mSubtitlelang)) { 
						if((!TvMediaTypeInfo.isHearingImpaired(mCurrentSubInfo.type))){
							result = true;
							mSubindex = i;
							break;
						}
						mSubindex = i;
					}
				}
			}
		} catch (Exception e) {
			Log.e(ctag, "Exception in CompareSubtitleLang");
		}

		if(mSubindex!=-1){
			Log.d(ctag,"user set mSubtitlelang is matched with index :"+ mSubindex);
			result = true;
		}
		return result;
	}

	/*
	 * This is used to check if Audio is muted or not
	 * for Automatic Mode 
	 */
	public boolean IsAudiomuted() {
		boolean mresult = false;	
		if(ITvAudioManager.Instance.getInterface().getProperty(ITvAudioManager.AUDMGR_PROPERTY_SPEAKER_MUTE) 
				== ITvAudioManager.AUDMGR_TRUE) {
			mresult = true;
		}
        return mresult;
	}

	/**
	 * On Country France and mode Automatic 
	 * we take more actions 
	 * @return
	 */
	public boolean isInstalledCountryFrance() {
		boolean result = false;
		if( globalSetting.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0) == 
				TvSettingsDefinitions.InstallationCountryConstants.FRANCE) {
			result = true;
		} 
		return result;
	}

	/*
	 * Local class used to register for AudioProperty callbacks
	 */
	public class OnTvAudioPropertyChangeListenerClass extends
	OnTvAudioPropertyChangeListener {

		@Override
		public void onAudioPropertyChanged(int mPropertyName, int mPropertyValue) {
		super.onAudioPropertyChanged( mPropertyName, mPropertyValue);
			if ((mPropertyName == ITvAudioManager.AUDMGR_PROPERTY_SPEAKER_MUTE)) {
				Runnable r = new Runnable() {
					@Override
					public void run() {
						int mode  = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 0);
						if ((!isDigitalChannel) && (mode ==2)) {
							EnableSubtitles(currentps,true);
						}
						else if((mode ==2) && (isDigitalChannel) && (subStateMachine.pmtState == PMT_ARRIVED) && (subStateMachine.mediaplayerstate == MEDIAPLAYER_PLAYCOMPLETED)){
							EnableSubtitles(currentps,true);
						}
						Log.v(ctag,"mode" +mode +"isDigitalChannel" +isDigitalChannel 
								+"pmtState" +subStateMachine.pmtState);
					}
				};
				mhandler.post(r);

			}
		} 
	}

	/*
	 * This is required for enabling callbacks for mute/unmute.
	 * This is required when the subtitle mode is Automatic 
	 * @param mAudioManager
	 */
	private void RegisterAudioPropertyListener() {
		mAudioPropertyChangeListener = new OnTvAudioPropertyChangeListenerClass();
		ITvAudioManager.Instance.getInterface().registerAudioPropertyListener(mAudioPropertyChangeListener);
	}
	
	/*
	 * This is required for stopping callbacks for mute/unmute
	 * This is called once we change the subtitle mode to 
	 * ON/OFF from Automatic 
	 */ 
	public void UnRegisterAudioPropertyListener() {

		if ((mAudioPropertyChangeListener != null)) {
			ITvAudioManager.Instance.getInterface().unregisterAudioPropertyListener(mAudioPropertyChangeListener);
			mAudioPropertyChangeListener = null;
		}
	}

	/**
	 * This is used for checking if there are no subtitles available
	 * for selection. When there are no subtitles then we are defaulting
	 * to Teletext Subtitles. 
	 * This is working/applicable to Analog channels also
	 * @return
	 */
	private boolean isSubtitleNotAvailable() {
		try {
			int noSubtitles = 0;
			ITvMediaStream itvms = tvmpl.getTvMediaPlayerContext()
					.getTvMediaStream();
			noSubtitles = itvms.getCurrentNoOfSubtitle();
			if (noSubtitles == 0)
				return true;
			else
				return false;
		} catch (Exception e) {
			Log.e(ctag, "Exception in isSubtitleNotAvailable");
		}
		return false;
	}

	/**
	 * onAudioChanged is called when there is a change in PMT for
	 * Audio. We need to take action when the Subtitle Mode is 
	 * set to Automatic
	 */
	private void onAudioChanged() {
		if(subStateMachine.activitystate == STATE_ACTIVE){
		if ((globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSUBTITLE, 0, 0) == 2)) {
			EnableSubtitles(currentps,true);
		}
		}
	}

	private boolean isDVBSubtitleAvailable() {
         TvMediaSubtitleInfo subinfo;
         int noSubtitles = 0;

         boolean result = false;
         try {
        	 ITvMediaStream  itvms = tvmpl.getTvMediaPlayerContext().getTvMediaStream();

        	 noSubtitles = itvms.getCurrentNoOfSubtitle();
             
        	 for(int i=0;i<noSubtitles;i++) {
        		 subinfo = itvms.getCurrentSubtitleInfo(i);
        		 if (TvMediaTypeInfo.isTXTSubtitle(subinfo.type)) {
                 }
        		 else if (TvMediaTypeInfo.isDVBSubtitle(subinfo.type)) {
                    result = true;
                    break;
        		 }
        	 }
         }catch(Exception e) {
               Log.e(ctag,"Exception in isDVBSubtitleAvailable");
         }
         Log.v(ctag,"isDVBSubtitleAvailable returned:" +result);
         return result;
    }
	
    private TunerServiceTextureView createTextureView(int subtitletype,int extype) {
    	Log.v(ctag, "createTextureView " + subtitletype);
    	TunerServiceTextureView txtView = new TunerServiceTextureView(mContext,
    			TunerServiceTextureView.TXTVIEWTYPE_SUBTTILE,subtitletype,extype,this);
  		return txtView;
  	}
    
	 /*
     * type should be correct
     * 
     */
  	public void requestSubitleView(final int subtitletype,final int extype) {
  		Log.v(ctag, "requestSubitleView called" + subtitletype);
  		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(mCurrentSubtitleTextureView==null) {
					if(mOverlayManager!=null) {
						mCurrentSubtitleTextureView = createTextureView(subtitletype,extype);
						mOverlayManager.addSubtitleView(mCurrentSubtitleTextureView);
					}
				} else {
					if(!mCurrentSubtitleTextureView.equals(subtitletype, extype)){
						if(mOverlayManager!=null) {
							mCurrentSubtitleTextureView = createTextureView(subtitletype,extype);
							mOverlayManager.addSubtitleView(mCurrentSubtitleTextureView);
						}
					}
				}
			}
  		};
  		mhandler.post(r);
  	}
  	  	
	/**
	 * onHideSubtitle to be called by SubtitleDummy OSD on a rule
	 * that says subtitle should not be displayed
	 */
	public void onHideSubtitle() {
		if(mCurrentSubtitleTextureView!=null){
			//we have to check if the surface is already created
			if(mCurrentSubtitleTextureView.isAvailable()) {
				mCurrentSubtitleTextureView.setVisibility(View.INVISIBLE);
			}
		}
		mSubtitleOSDVisibility = View.INVISIBLE;
	}

	/**
	 * onShowSubtitle to be called by SubtitleDummy OSD on a rule
	 * that says subtitle should be displayed
	 */
	public void onShowSubtitle() {
		if(mCurrentSubtitleTextureView!=null) {
			//we have to check if the surface is already created
			if(mCurrentSubtitleTextureView.isAvailable()) {
				mCurrentSubtitleTextureView.setVisibility(View.VISIBLE);
			}
		}
		mSubtitleOSDVisibility = View.VISIBLE;
	}
		
	@Override
	public void onSurfaceTextureAvailable(TunerServiceTextureView ptxtv) {
		Log.v(ctag,"onSurfaceTextureAvailable called " + ptxtv);
		if(ptxtv==mCurrentSubtitleTextureView) {
			mCurrentSubtitleTextureView.setVisibility(mSubtitleOSDVisibility);
			if(mSubtitleOSDVisibility==View.VISIBLE) {
				Runnable r = new Runnable() {
					@Override
					public void run() {
						if (tvmpl != null){
							EnableSubtitles(currentps,true);
						}
					}
				};
				mhandler.post(r);
			}
		} else {
			Log.v(ctag,"onSurfaceTextureAvailable arrived for a different TextureView");
			//are we doing something wrong here???
		}
	}

	@Override
	public boolean onSurfaceTextureDestroyed(final TunerServiceTextureView ptxtv) {
		Log.v(ctag,"onSurfaceTextureDestroyed called " + ptxtv);
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(ptxtv==mCurrentSubtitleTextureView) {
					//current view destroyed
					if(ptxtv.getSubtype()==TunerServiceTextureView.SUBVIEWTYPE_SUBTTILE_TXT) {					
						disableTextSubtitles();
					}else if (ptxtv.getSubtype()==TunerServiceTextureView.SUBVIEWTYPE_SUBTTILE_DVB) {
						if(mDVBSubInterface!=null) {
							mDVBSubInterface.disableSubtitles();
						}
					}
					mCurrentSubtitleTextureView = null;
				}			
				//surface destroyed release surface
				ptxtv.release();
			}
		};
		mhandler.post(r);
		return false;
	}

	public void onTeletextExited() {
		if(mTeleTextEnabled)
		{
			mTeleTextEnabled = false;		
			EnableSubtitles(currentps,true); 
		}
	}

	public void onTeletextEntered() {
		mTeleTextEnabled = true;
		if(currentps.type==SubtitleType_TXT) {
			disableTextSubtitles();
		}
		else if (currentps.type==SubtitleType_DVB) {
			if(mDVBSubInterface!=null) {
				mDVBSubInterface.disableSubtitles();
			}
		}
	}
	
	public void onTrickModeStatusChanged(boolean ena){
        if(ena) {
        	Log.v(ctag,"onTrickModeStatusChanged disable subtitles");
        	if (currentps.type == SubtitleType_TXT) {
        		disableTextSubtitles();
            } else if (currentps.type == SubtitleType_DVB) {
                if (mDVBSubInterface != null) {
                    mDVBSubInterface.disableSubtitles();
                }
            }
        }
        else {
        	Log.v(ctag,"onTrickModeStatusChanged enable subtitles");
        	EnableSubtitles(currentps, true);  
        }
	}

	public void setOverlayManager(OverlayManager mOverlayMgr) {
		if((mOverlayMgr==null) || (mOverlayMgr != mOverlayManager)) {
			if(mCurrentSubtitleTextureView!=null) {
				if(!mCurrentSubtitleTextureView.isAvailable())
				{
					mCurrentSubtitleTextureView = null;
				}
				releaseSurface();
			}
		}
		mOverlayManager = mOverlayMgr;
		if(mOverlayMgr==null){
			Runnable r = new Runnable() {
				@Override
				public void run() {
					subStateMachine.uri = null;
					unregisterContentObserver();
				}
			};
			mhandler.post(r);
		}
	}

	public void setCaptionEnabled(final boolean enable) {
		//This is global disable subtitles coming in from TIF
		Log.v(ctag,"setCaptionEnabled " + enable);
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(mCaptionsEnabled!=enable) {
					mCaptionsEnabled=enable;
					if(enable){
						onSubtitleChanged();
					}else {
						if(mCurrentSubtitleTextureView!=null) {
							mCurrentSubtitleTextureView=null;
							disableSubtitles();
							releaseSurface();
						}
					}
				}
			}
		};
		mhandler.post(r);
	}
	
	private boolean isTeletextPageStored() {
		boolean stored = false;
		Log.v(ctag, "isTeletextPageStored :  uri - " + subStateMachine.uri);
		if(TvContract.isChannelUriForTunerInput(subStateMachine.uri)) {
			Cursor cursor=null;
			String[] PROJECTION =  {
				TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA
			};
			try{
				cursor= mContext.getContentResolver().query(subStateMachine.uri,PROJECTION,null,null,null);
				if(cursor!=null){
					if(cursor.moveToFirst()){
						byte[] lInternalData  		= cursor.getBlob(cursor.getColumnIndex(TvContract.Channels.COLUMN_INTERNAL_PROVIDER_DATA));
						IIntKeyValueables keyvals	= IIntKeyValueables.Instance.getInterface();				
						try{
							keyvals.setBlob(lInternalData);	
							Log.v(ctag,"Txt page number=" + keyvals.getInt(ITvContractExtras.C_TXTSUBPAGE));
							if(keyvals.getInt(ITvContractExtras.C_TXTSUBPAGE)>0) {
								stored = true;
							}
						}catch(IOException e){
							Log.e(ctag, "isTeletextPageStored - CAUGHT EXCEPTION");
						}catch(ClassNotFoundException e){
							Log.e(ctag, "isTeletextPageStored - CAUGHT EXCEPTION");
						}
					}
					cursor.close();
				}
			}catch(Exception e) {
				Log.e(ctag,"Exception isTeletextPageStored");
			}
		}
		return stored;
	}
	
	private SubtitleContentObserver mChannelObserver=null;
	private boolean isObserverRegistered = false;
	
	public class SubtitleContentObserver extends ContentObserver {
    	public SubtitleContentObserver( Handler hldr ) {
		    super( hldr );			
		}

		public void onChange(boolean selfChange,Uri uri) {			
			if(uri != null)	{
				if((subStateMachine.uri!=null) && 
					(subStateMachine.uri.equals(uri)) && 
					(currentps.type==SubtitleType_INVALID)) {
					Runnable r = new Runnable(){
						@Override
						public void run() {
							onSubtitleChanged();
						}
					};
					mhandler.post(r);
				}
			}				 
		}
    }
	
	protected void registerContentObserver() {
		if(mChannelObserver == null ) {
			mChannelObserver = new SubtitleContentObserver(new Handler());
		}
		if((!isObserverRegistered)) {
			mContext.getContentResolver().registerContentObserver(TvContract.Channels.CONTENT_URI,true,mChannelObserver);
			isObserverRegistered = true;
		}
    }

	protected void unregisterContentObserver() {
		if((mChannelObserver != null) && (isObserverRegistered)) {
			mContext.getContentResolver().unregisterContentObserver(mChannelObserver);
			isObserverRegistered = false;
		}
	}
}
