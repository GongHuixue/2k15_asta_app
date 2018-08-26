package org.droidtv.tunerservice.services.sbyservice;

import java.io.FileDescriptor;
import java.io.PrintWriter;
import java.util.ArrayDeque;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import org.droidtv.tunerservice.PlayTvDiversity;
import org.droidtv.tunerservice.interfaces.IPlayTvMPLFactoryCallback;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;
import org.droidtv.tunerservice.interfaces.IPowerEvents;
import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.ClientStates;
import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.ControlStates;
import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.Events;
import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.PStates;
import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.PowerStateEventHandler;
import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.SSBYClientDeathListener;
import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.SSBYSessionHelperCallbacks;
import org.droidtv.tunerservice.tvmpl.PlayTvMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.PlayTvMsgHandler;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.util.PowerLogger;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.tvpower.ITvPowerManager;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerBootState;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerShutdownLocks;
import org.droidtv.tv.tvpower.ITvPowerManager.PowerStates;
import org.droidtv.tv.tvpower.ITvPowerManager.ShutdownLock;
import org.droidtv.tv.tvpower.ITvPowerManager.StandByType;
import org.droidtv.tv.tvpower.ITvPowerManager.WakeUpReason;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl;
import org.droidtv.tv.tvpower.TvSemiStandbyControl;
import org.droidtv.tv.tvpower.TvSemiStandbyControlImpl;
import org.droidtv.tv.upgrade.ITvOADControl;
import org.droidtv.tv.logger.ILogger;
import org.droidtv.tv.logger.ILogger.PowerStateTransition;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler.Callback;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.os.SystemProperties;

import android.content.ComponentName;
import android.content.pm.PackageManager;

public class SemiStandbyService extends Service implements 
	Callback, IPlayTvMPLFactoryCallback, IPlayTvStateChangeListener, SSBYSessionHelperCallbacks {
	
	private static final int MAX_CLIENTS = 9;
	
	private PlayTvMsgHandler mSbyHandler 	= 	null;
	private ITvPowerManager mTvPowerManager	=	null;
	
	private HashMap <String, SSBYClient> mClientList = null;
	private ArrayDeque<SSBYClient> mClientQue;	
		
	public static final String TAG="SSBYService";
	
	private ShutdownLock mShutdownLock = null;
	
	SSBYDefinitions.PStates mSysPowerstate = SSBYDefinitions.PStates.PSTATE_INIT;
	SSBYDefinitions.ClientStates mClientState = SSBYDefinitions.ClientStates.CSTATE_INIT;
	SSBYDefinitions.ControlStates mMediaControlState = SSBYDefinitions.ControlStates.MSTATE_INIT;
		
	private PlayTVMediaPlayerFactory mplfactory = null;
	private PlayTVFacMediaPlayer mplaytvmpl = null;
	private SSBYSession mSbysession = null;
			
	private PowerStateEventHandler handlers[] = null;
	
	private SSBYClientEMM sbyEMM = null;
	private SSBYClientClockCalib sbyclock = null;
	private HtvSSBYClientDelay sbyDelay = null; // Reno 20160217 extends 5 minutes for staying in semi standby
	private static IPowerEvents mPowerEventListener = null;
	private PowerLogger mPowerLogger;
    
    private ITvSettingsManager mTvSettingMgr = null;
	
	@Override
	public IBinder onBind(Intent intent) {
		return (IBinder) new SSbyServiceImpl();
	}

	@Override
	public void onCreate() {
		Log.v(TAG,"onCreate called");
		
		createPowerEventListener(this);
		startCIService(this);
		registerPowerLogger(this);
		mSysPowerstate = SSBYDefinitions.PStates.PSTATE_INIT;
		mClientQue = new ArrayDeque <SSBYClient> (MAX_CLIENTS);
		mClientList = new HashMap<String, SSBYClient>(MAX_CLIENTS);
		handlers = new PowerStateEventHandler [] {
			new init(),
			new full_to_semi(),
			new booting_to_semi_alarm(),
			new booting_to_semi_cold(),
			new semi_to_full(),
			new ddr_to_full_on(),
		};
		
		mSbyHandler = new PlayTvMsgHandler(PlayTvMsgHandler.getLooper("SSBYService"), this);
		mSbyHandler.sendEmptyMessage(Events.EVENT_INIT.value);
	}
	
	private static void createPowerEventListener(SemiStandbyService mSvc){
		mPowerEventListener = mSvc.new PowerEventsReceiver();
	}

	private void registerPowerLogger(Context context){
		mPowerLogger = PowerLogger.getInstance();
		mPowerLogger.bindToLoggingService(context);
	}

	
	private void startCIService(Context context) {
		Log.v(TAG, "Starting CIService");
		Intent ciService = new Intent("org.droidtv.ci.CIStartService");
		context.startService(ciService);
	}
	private void registerforFacEvents() {
		mplfactory = PlayTVMediaPlayerFactory.getInstance();
		if(mplfactory!=null) {
			mplfactory.registerListener(PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY, SemiStandbyService.this);
		}
	}
	
	private void unregisterFacEvents(){
		mplfactory = null;
	}
	
	@Override
	public boolean handleMessage(Message msg) {
		SSBYDefinitions.Events event = SSBYDefinitions.Events.getEvent(msg.what);
		Log.v(TAG,"handleMessage ->" + event);
		boolean handled = false;
		switch(event){
		case EVENT_ALARM_FIRED:
			handled = true;
			mTvPowerManager = ITvPowerManager.Instance.getInterface();
			PowerStates cPowerState = mTvPowerManager.GetPowerState();
			if(cPowerState!=PowerStates.POWER_STATE_FULL_SYSTEM_START) {
				if((mSysPowerstate==PStates.PSTATE_FULLON_TO_SEMI)||
					(mSysPowerstate==PStates.PSTATE_BOOTING_TO_SEMI_ALARM)||
					(mSysPowerstate==PStates.PSTATE_BOOTING_TO_SEMI_COLD)) {
						if(cPowerState==PowerStates.POWER_STATE_SEMI_STANDBY) {
							if(mShutdownLock==null) {
								//some one else is holding DSL
								if(mClientQue.size()==0) {
									int almclients = getSSBYAlarmClient(); 
									if(almclients>0) {
										if(acquireDSL()) {
											reportAlarmFired(almclients,true);
											addClientToQue(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION);
											handled = false;
										}
									}
								}
							}
							//skip because SSBY is already in action and already 
							//actions have been triggered
						}
						else if(cPowerState==PowerStates.POWER_STATE_DDR_STANDBY) {
						//Wait for power notification to take action
						acquireDSL();
					}
				}
				if(handled) {
					return false;
				}
			}else {
				if(msg.arg1>0){
					reportAlarmFired(msg.arg1,false);
				}
				return false;
			}
			break;
		case EVENT_POWERCHANGE_END:
			mSysPowerstate = getPowerTransition(msg);
			break;
		case EVENT_FAC_AVAILABLE:
			registerforFacEvents();
			if(mMediaControlState == ControlStates.MSTATE_WAITING) {
				requestMediaplayer();
			}else {
				return false;
			}
			break;
		case EVENT_FAC_UNAVAILABLE:
			//not expecting this
			if(mMediaControlState == ControlStates.MSTATE_AVAILABLE) {
				mMediaControlState = ControlStates.MSTATE_WAITING;
				msg.what = Events.EVENT_MP_UNAVAILABLE.value;
			} else {
				return false;
			}
			break;
		case EVENT_MP_AVAILABLITY_CHANGED:
			if(mMediaControlState==ControlStates.MSTATE_WAITING) {
				requestMediaplayer();
			}
			return false;
		case EVENT_MP_AVAILABLE:
			if(mMediaControlState == ControlStates.MSTATE_WAITING) {
				mMediaControlState = ControlStates.MSTATE_AVAILABLE;
			}else {
				return false;
			}
			Log.d(TAG,"mMediaControlState now " + mMediaControlState);
			break;
		case EVENT_MP_UNAVAILABLE:
			if(mMediaControlState == ControlStates.MSTATE_AVAILABLE) {
				mMediaControlState = ControlStates.MSTATE_WAITING;
			} else {
				return false;
			}
			break;
		case EVENT_CLIENT_CONNECTED:
			SSBYClient ssbyclient = (SSBYClient)msg.obj;
			//check if it already present and return
			mClientList.put(Integer.toString(msg.arg1), ssbyclient);
			break;
		case EVENT_REQUEST_MPLAYER:
			if(mMediaControlState == ControlStates.MSTATE_INIT) {
				mMediaControlState = ControlStates.MSTATE_WAITING;
				registerforFacEvents();
				requestMediaplayer();
				return false;
			}
			break;
		case EVENT_RELEASE_MPLAYER:
			if(mMediaControlState == ControlStates.MSTATE_AVAILABLE) {
				mMediaControlState = ControlStates.MSTATE_INIT;
				//releaseMediaplayer();
				return false;
			}
			mMediaControlState = ControlStates.MSTATE_INIT;
			break;
		case EVENT_START_APP:
			startPlayTvApp();
			return false;
		case EVENT_RELEASE_DSL:
			releaseDSL();
			return false;
		case EVENT_REGISTER_ALARM:
			registerAlarms();
			return false;
		case EVENT_REQUEST_SBY:
			requestPowerStateSby();
			return false;
		case EVENT_POWERCHANGE_START:
			if(msg.arg2==PowerStates.POWER_STATE_DDR_STANDBY.ordinal()) {
				PlayTVFacMediaPlayer facdmpl = null;
				try {
					ShutdownLock mShutDownInProgresslock  = mTvPowerManager.CreateShutdownLock(PowerShutdownLocks.SHUTDOWN_IN_PROGRESS_LOCK,"SSBYInprogress");
					mShutDownInProgresslock.acquire();
					facdmpl = PlayTVMediaPlayerFactory.getInstance().getDirectMPLInstance(this, PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY);
					facdmpl.getMediaPlayerInstance().getTvMediaPlayerContext().getTvMediaCI().ForceDescrambling();
					mShutDownInProgresslock.release();
				}catch(Exception e) {
					Log.e(TAG,"Exception ForceDescrambling");
				}
			}
			return false;
		case EVENT_ALARM_REQUEST:
			if(msg.getData()!=null){
				addAlarm(msg.arg1,(0x01<<msg.arg1),msg.getData().getLong("almtime"));
			}
			return false;
        /*begin:min.jiang add 2015-07-15*/    
        case EVENT_CLIENT_COMPLETED:
            handleClientComplete(msg.arg1);
            break;
        /*end:min.jiang add*/    
		default:
			break;
		}
        
        if(mTvSettingMgr == null) {
            mTvSettingMgr = ITvSettingsManager.Instance.getInterface();
        }
        
        /* ericws_20171115 [TF415PHIEUMTK66-2535] TV does not send the an IPCloneService with ReadyForUpgrade */
        if(mTvSettingMgr != null) {
            if((mSysPowerstate == PStates.PSTATE_INIT)
                || (mSysPowerstate == PStates.PSTATE_SEMI_TO_FULLON)
                || (mSysPowerstate == PStates.PSTATE_DDR_TO_FULLON)) {
                int virginbit = mTvSettingMgr.getInt(TvSettingsConstants.VIRGINBIT, 0, 0);
                //Log.d(TAG, "virginbit = " + virginbit);

                ComponentName compIicName = new ComponentName("org.droidtv.devicesetup", "org.droidtv.devicesetup.IICActivity");
                PackageManager pm = getApplicationContext().getPackageManager();
                int nPmIicState = pm.getComponentEnabledSetting(compIicName);
                //Log.d(TAG, "IICActivity Enabled State: " + nPmIicState);

                // Because sometimes virginbit is set unreasonable, follow package manager status to reset virginbit at specific moment.
                if(nPmIicState == PackageManager.COMPONENT_ENABLED_STATE_DISABLED) {
                    if(virginbit == 1) {
                        Log.d(TAG, "IICActivity is disabled, reset virgin bit.");
                        mTvSettingMgr.putInt(TvSettingsConstants.VIRGINBIT, 0, 0);
                        virginbit = 0;
                    }
                } else if(nPmIicState == PackageManager.COMPONENT_ENABLED_STATE_DEFAULT) {
                    if(virginbit == 0) {
                        Log.d(TAG, "IICActivity is default, set virgin bit.");
                        mTvSettingMgr.putInt(TvSettingsConstants.VIRGINBIT, 0, 1);
                        virginbit = 1;
                    }
                }
            }
        }
        
		Log.i(TAG,"PowerTransition State =" + mSysPowerstate);
		if(	mSysPowerstate.value < SSBYDefinitions.PStates.PSTATE_SBY.value) {
			handlers[mSysPowerstate.value].doAction(event, msg);
		}
		else {
			switch(event) {
			case EVENT_CLIENT_COMPLETED:
				Log.v(TAG,"EVENT_CLIENT_COMPLETED " + msg.arg1);
				SSBYClient client = mClientList.get(Integer.toString(msg.arg1));
				if(client!=null) {
					client.onActioncompleted();
				}
				break;
			case EVENT_CLIENT_DISCONNECTED:
				removeClient(msg.arg1);
				break;
			default:
				break;
			}
		}
		return false;
	}
	
	private PStates getPowerTransitiononAlarmFired() {
		PStates pstate=mSysPowerstate;
		PowerBootState cTargetBootState = mTvPowerManager.GetTargetBootState();
		WakeUpReason cWakeUpReason  	= GetWakeUpReason();
		PowerStates CurrentPowerState   = mTvPowerManager.GetPowerState();
		
		Log.i(TAG, "getPowerTransitiononAlarmFired TargetBootState: " + cTargetBootState);
		Log.i(TAG, "getPowerTransitiononAlarmFired WakeUpREason: " + cWakeUpReason);
		Log.i(TAG, "getPowerTransitiononAlarmFired PowerState: " + CurrentPowerState);
		
		
		if(cTargetBootState==PowerBootState.TARGET_BOOT_STATE_SEMI_STANDBY){
			if(cWakeUpReason==WakeUpReason.WAKE_UP_REASON_ALARM) {
				pstate = SSBYDefinitions.PStates.PSTATE_BOOTING_TO_SEMI_ALARM;
			}
		}		
		Log.i(TAG, "getPowerTransitiononAlarmFired returns "+ mSysPowerstate + "->" + pstate );
		return pstate;
	}
	
	private PStates getPowerTransition(Message msg) {
		PStates pstate=mSysPowerstate;
		PowerBootState cTargetBootState = mTvPowerManager.GetTargetBootState();
		WakeUpReason cWakeUpReason  	= GetWakeUpReason();
		PowerStates CurrentPowerState   = mTvPowerManager.GetPowerState();
		
		int from = msg.arg1;
		int to   = msg.arg2;
			
		Log.d(TAG, "getPowerTransition TargetBootState=" + cTargetBootState + 
				" wakeupreason=" +  cWakeUpReason + " cpowerstate=" + CurrentPowerState);
					
		if( (from==PowerStates.POWER_STATE_FULL_SYSTEM_START.ordinal()) && 
			(to==PowerStates.POWER_STATE_SEMI_STANDBY.ordinal())) {
			pstate = SSBYDefinitions.PStates.PSTATE_FULLON_TO_SEMI;
		}
		else if( from==PowerStates.POWER_STATE_BOOTING.ordinal() && 
			(to==PowerStates.POWER_STATE_SEMI_STANDBY.ordinal())) {
			if(cWakeUpReason==WakeUpReason.WAKE_UP_REASON_ALARM) {
				pstate = SSBYDefinitions.PStates.PSTATE_BOOTING_TO_SEMI_ALARM;
			} else {
				pstate = SSBYDefinitions.PStates.PSTATE_BOOTING_TO_SEMI_COLD;
			}
		}
		else if(from==PowerStates.POWER_STATE_SEMI_STANDBY.ordinal() && 
			(to==PowerStates.POWER_STATE_FULL_SYSTEM_START.ordinal())) {
			pstate = SSBYDefinitions.PStates.PSTATE_SEMI_TO_FULLON;
		}
		else if((from==PowerStates.POWER_STATE_BOOTING.ordinal()) && 
			(to==PowerStates.POWER_STATE_FULL_SYSTEM_START.ordinal()) && 
			((cWakeUpReason==WakeUpReason.WAKE_UP_REASON_COLD_BOOT)||
			 (cWakeUpReason==WakeUpReason.WAKE_UP_REASON_RC_KEY)   ||
			 (cWakeUpReason==WakeUpReason.WAKE_UP_REASON_UNKNOWN))) { 
			pstate = SSBYDefinitions.PStates.PSTATE_FULLON;
		} else if(from==PowerStates.POWER_STATE_DDR_STANDBY.ordinal()) {
			if(to==PowerStates.POWER_STATE_FULL_SYSTEM_START.ordinal()) {
				pstate = SSBYDefinitions.PStates.PSTATE_DDR_TO_FULLON;	
			} else if(to==PowerStates.POWER_STATE_SEMI_STANDBY.ordinal()) {
				if(cWakeUpReason==WakeUpReason.WAKE_UP_REASON_ALARM) {
					pstate = SSBYDefinitions.PStates.PSTATE_BOOTING_TO_SEMI_ALARM;
				} else {
					pstate = SSBYDefinitions.PStates.PSTATE_BOOTING_TO_SEMI_COLD;
				}
			}
		} else if(CurrentPowerState==PowerStates.POWER_STATE_FULL_SYSTEM_START){
			pstate = SSBYDefinitions.PStates.PSTATE_FULLON;
		} else if((from==PowerStates.POWER_STATE_SEMI_STANDBY.ordinal()) &&
				(to==PowerStates.POWER_STATE_STANDBY.ordinal())){
			pstate = SSBYDefinitions.PStates.PSTATE_SBY;
		}			
		Log.i(TAG, "getPowerTransition returns "+ mSysPowerstate + "->" + pstate );
		return pstate;
	}

	//No implementation in the methods should be written in the handlemessage itself
	private void onQuickShutdown() {
		//ReleaseShutDownLock();
	}
	
	private void requestMediaplayer() {
		if(mplfactory!=null) {
			mplaytvmpl = mplfactory.getMPLInstance(this,PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY,
					PlayTvUtils.getCurrentMedium(), PlayTvUtils.getCurrentChannel());
			if(mplaytvmpl!=null) {
				Log.v(TAG,"Mediaplayer available");
				mplaytvmpl.registerListener(this, TAG);
				mSbyHandler.sendEmptyMessage(Events.EVENT_MP_AVAILABLE.value);
			}else {
				Log.d(TAG,"Mediaplayer denied");
				mSbyHandler.sendEmptyMessage(Events.EVENT_MP_UNAVAILABLE.value);
			}
		}
	}
	
	private void releaseMediaplayer(){
		if(mplaytvmpl!=null) {
			mplfactory.releaseMPLInstance(PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY, mplaytvmpl);
			mSbyHandler.sendEmptyMessage(Events.EVENT_MP_UNAVAILABLE.value);
			Log.v(TAG,"releaseMediaplayer done");
		}
	}
	
	private long getTimeRoundedoff(long ctime) {
		Calendar calarmTime = Calendar.getInstance();
		calarmTime.setTimeInMillis(ctime);
		calarmTime.set(Calendar.MILLISECOND, 0);
		return calarmTime.getTimeInMillis();
	}
	
	private void registerAlarms() {
		long alarmTime = Long.MAX_VALUE;
		long clientTime = 0;
		int lowclientid = 0;
		int multiclient = 0;
		
		try {
			Iterator<String> lIterator = mClientList.keySet().iterator();	
			while(lIterator.hasNext()){
				String key =  lIterator.next();
				SSBYClient client = mClientList.get(key);
				clientTime = getTimeRoundedoff(client.onGetNextAlarm());
				if(clientTime!=0) {
					if( alarmTime > clientTime) {
						alarmTime = clientTime;
						lowclientid = client.getId();
						multiclient = (0x01 << lowclientid);
					}else if(alarmTime==clientTime) {
						multiclient = (multiclient | (0x01 << client.getId()));
					}
				}
			}
			Log.v(TAG,"clients " + multiclient);
			if(alarmTime!=Long.MAX_VALUE) {
				addAlarm(lowclientid, multiclient, alarmTime);
			}
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	
	private void requestPowerStateSby() {
		Log.v(TAG,"requestPowerStateSby called");
		mTvPowerManager.SetState(PowerStates.POWER_STATE_STANDBY);
	}
	
	private void SbyInit() {
		Log.v(TAG,"SbyInit called");
		mTvPowerManager = ITvPowerManager.Instance.getInterface();
        if(mTvSettingMgr == null) {
            mTvSettingMgr = ITvSettingsManager.Instance.getInterface();
        }

		Calendar alarmTime = Calendar.getInstance();
		String mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		Log.i(TAG,"current time is " + mydate);
		
		mSbysession = new SSBYSession(this,this);
				
		startClients();
		//sendPowerStartupChanges();
		registerBroadcastReceivers();
		acquireDSL();
		mSbysession.startSession();
	}

	private boolean acquireDSL() {
		Log.v(TAG,"acquireDSL called");
		if(mShutdownLock==null) {
			mShutdownLock = mTvPowerManager.CreateShutdownLock(PowerShutdownLocks.DONT_SHUTDOWN_LOCK, TAG);
		}
		try {
			if(!mShutdownLock.isHeld()) {
				mShutdownLock.acquire();
			}
			return true;
		}catch(IllegalStateException e) {
			Log.e(TAG,"Wrong state");
		}
		return false;
	}

	private void releaseDSL() {
		try {
			if (mShutdownLock.isHeld() == true) {
				mShutdownLock.release();
				Log.v(TAG, "Released ShutDownLock");
				mShutdownLock = null;
			}
		} catch (NullPointerException ne) {
			Log.e(TAG, "ShutDownLock is null");
		}
	}

	@Override
	public void onDestroy() {
		Log.v(TAG,"onDestroy called");
		super.onDestroy();
	}

	@Override
	public void onLowMemory() {
		Log.v(TAG,"onLowMemory called");
		super.onLowMemory();
	}

	@Override
	public void onTrimMemory(int level) {
		Log.v(TAG,"onTrimMemory called");
		super.onTrimMemory(level);
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.v(TAG,"onStartCommand called");
		super.onStartCommand(intent, flags, startId);
		return START_STICKY;
	}
		
	private void startClients() {
		sbyEMM = new SSBYClientEMM(this);
		sbyclock = new SSBYClientClockCalib(this);
		sbyDelay = new HtvSSBYClientDelay(this); // Reno 20160217 extends 5 minutes for staying in semi standby
	}
    
	/*begin:min.jiang add 2015-07-15, for clock calibration*/
    private void handleClientComplete(int id) {        
        boolean notifyComplete = (mSysPowerstate == SSBYDefinitions.PStates.PSTATE_BOOTING_TO_SEMI_ALARM ||
                                  mSysPowerstate == SSBYDefinitions.PStates.PSTATE_BOOTING_TO_SEMI_COLD ||
                                  mSysPowerstate == SSBYDefinitions.PStates.PSTATE_SEMI_TO_FULLON) && 
                                  (id == ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION);
        if(PlayTvUtils.isPbsMode()) {
            if(notifyComplete) {   
                Log.d(TAG, "notifyClientComplete id: " + id + ", power: " + mSysPowerstate);
                sendBroadcast(new Intent("org.droidtv.tv.semistandby.clock.complete"));
            }            
        }
    }


    private void addClientToQueOnPbs(int id, boolean on) {
		if(PlayTvUtils.isPbsMode() == on) {
            addClientToQue(id);
        }
    }
    /*end:min.jiang add*/

	private void registerBroadcastReceivers() {
		Log.v(TAG,"RegisterBroadcastReceivers ");
		IntentFilter alarmfilter = new IntentFilter();
		alarmfilter.addAction(SSBYDefinitions.AlarmPendingIntent);
		alarmfilter.addDataScheme(SSBYDefinitions.strAlmScheme);
		registerReceiver(mAlarmReceiver, alarmfilter);
	}
		
	private void sendPowerStartupChanges() {
		Log.v(TAG,"sendPowerStartupChanges ");
		PowerBootState TargetBootState;
		WakeUpReason wakeUpReason;
		PowerStates CurrentPowerState;
		
    	if(mTvPowerManager != null) {
    		
    		TargetBootState 	= mTvPowerManager.GetTargetBootState();
    		wakeUpReason 		= GetWakeUpReason();
    		CurrentPowerState   = mTvPowerManager.GetPowerState();
    		
    		Log.i(TAG, "sendPowerStartupChanges TargetBootState: " + TargetBootState);
    		Log.i(TAG, "sendPowerStartupChanges WakeUpREason: " + wakeUpReason);
    		Log.i(TAG, "sendPowerStartupChanges PowerState: " + CurrentPowerState);
    		
    		if(TargetBootState == PowerBootState.TARGET_BOOT_STATE_SEMI_STANDBY) {
				switch(wakeUpReason) {
				case WAKE_UP_REASON_ALARM:
					/*Calendar c = Calendar.getInstance();
					
					
						Message msg = mSbyHandler.obtainMessage(MSG_ALARM_FIRED);
						
						Bundle b = msg.getData();
						b.putInt(SSBYDefinitions.strClientid, ALARM_ALL);
						b.putInt(SSBYDefinitions.strAlarmid, 0);
						b.putLong(SSBYDefinitions.strTimeinms,c.getTimeInMillis());
				
						mSbyHandler.sendMessage(msg);
					*/
					
					
					break;
				default:
					break;
				}
			}
    	    		    		
    		PowerStates from = PowerStates.POWER_STATE_BOOTING;
    		PowerStates to = PowerStates.POWER_STATE_BOOTING;
    		    		
			if(TargetBootState == PowerBootState.TARGET_BOOT_STATE_FULL_SYSTEM_START) {
				if(CurrentPowerState==PowerStates.POWER_STATE_FULL_SYSTEM_START) {
					to = PowerStates.POWER_STATE_FULL_SYSTEM_START;
					synchronized(mSbyHandler) {
						Message msg = mSbyHandler.obtainMessage(Events.EVENT_POWERCHANGE_START.value,
								from.ordinal(),to.ordinal());
						mSbyHandler.sendMessage(msg);
					}
					synchronized(mSbyHandler) {
						Message msg = mSbyHandler.obtainMessage(Events.EVENT_POWERCHANGE_END.value,
								from.ordinal(),to.ordinal());
						mSbyHandler.sendMessage(msg);
					}
				}
				else {
					to = PowerStates.POWER_STATE_FULL_SYSTEM_START;
					synchronized(mSbyHandler) {
						Message msg = mSbyHandler.obtainMessage(Events.EVENT_POWERCHANGE_START.value,
								from.ordinal(),to.ordinal());
						mSbyHandler.sendMessage(msg);
					}
				}
			}
			else if (TargetBootState == PowerBootState.TARGET_BOOT_STATE_SEMI_STANDBY) {
				if(CurrentPowerState==PowerStates.POWER_STATE_SEMI_STANDBY) {
					to = PowerStates.POWER_STATE_SEMI_STANDBY;
					synchronized(mSbyHandler) {
						Message msg = mSbyHandler.obtainMessage(Events.EVENT_POWERCHANGE_START.value,
								from.ordinal(),to.ordinal());
						mSbyHandler.sendMessage(msg);
					}
					synchronized(mSbyHandler) {
						Message msg = mSbyHandler.obtainMessage(Events.EVENT_POWERCHANGE_END.value,
								from.ordinal(),to.ordinal());
						mSbyHandler.sendMessage(msg);
					}
				}else {
					to = PowerStates.POWER_STATE_SEMI_STANDBY;
					synchronized(mSbyHandler) {
						Message msg = mSbyHandler.obtainMessage(Events.EVENT_POWERCHANGE_START.value,
								from.ordinal(),to.ordinal());
						mSbyHandler.sendMessage(msg);
					}
				}
			}
    	}
    }
	
	private final BroadcastReceiver mAlarmReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String sAction = intent.getAction();
			if((sAction).equals(SSBYDefinitions.AlarmPendingIntent)) {
				try {
					Uri data = intent.getData();
					String scheme = data.getScheme();
					if(scheme.equals(SSBYDefinitions.strAlmScheme)) {
						SemiStandbyService.this.onAlarmFired(data); 
					}
				}catch(Exception e){
					Log.e(TAG,"Exception in parsing the intent");
				}
			}
		}
	};
	
	private void startPlayTvApp() {
		
		if( PlayTvUtils.getVirginBit() == 1) {
			Log.d(TAG, "Virgin Mode Detected.. not Starting PlayTvActivity");
		} else {
			PlayTVMediaPlayerFactory playTvMPFactory = PlayTVMediaPlayerFactory.getInstance();
			PlayTVFacMediaPlayer TADMpl = null;
			if(playTvMPFactory != null){
				 TADMpl = playTvMPFactory.getDirectMPLInstance(this,PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD);
				// if independent TAD is not available, check if dependent tad is going on
				if (TADMpl == null) {											
					TADMpl = playTvMPFactory.getDirectMPLInstance(this,PlayTVMediaPlayerFactory.REQUEST_TYPE_DEPENDENT_TAD);
				}
			}
			
			if (TADMpl != null) {
				Intent onStartActionIntent = null;
				if (TADMpl.getCurrentMedium() == Medium.MEDIUM_PVRFILE) {
					Log.d(TAG, "Independent TAD Detected: PVR USE-CASE: Starting RecPlayActivity");
					onStartActionIntent = new Intent("org.droidtv.action.PLAYRECORDING");
				} else {
					Log.d(TAG, "Independent TAD Detected: TUNER USE-CASE: Starting PlayTvActivity");
					onStartActionIntent = new Intent("org.droidtv.playtv.BOOTCOMPLETED");
				}
				onStartActionIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				//check for WakeupReason
				if(mSysPowerstate==SSBYDefinitions.PStates.PSTATE_DDR_TO_FULLON) {
					onStartActionIntent.putExtra("FromSby",PlayTvUtils.FLAGS_BOOTUPFROMDDRSBY);
					//onStartActionIntent.putExtra("WakeUpKey", mWakeUpkey);
				} else {
					onStartActionIntent.putExtra("FromSby",PlayTvUtils.FLAGS_BOOTUPFROMSBY);
					//onStartActionIntent.putExtra("WakeUpKey", mWakeUpkey);
				}
				onStartActionIntent.putExtra("FromTAD", 1);
				onStartActionIntent.putExtra("TADUri",TADMpl.getCurrentUri().toString());
				startActivity(onStartActionIntent);
			} else {
				Log.d(TAG, "Starting PlayTvActivity");
				Intent onStartActionIntent = new Intent("org.droidtv.playtv.BOOTCOMPLETED");
				onStartActionIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				//check for WakeupReason
				if(mSysPowerstate==SSBYDefinitions.PStates.PSTATE_DDR_TO_FULLON) {
					onStartActionIntent.putExtra("FromSby",PlayTvUtils.FLAGS_BOOTUPFROMDDRSBY);
					//onStartActionIntent.putExtra("WakeUpKey", mWakeUpkey);
				} else {
					onStartActionIntent.putExtra("FromSby",PlayTvUtils.FLAGS_BOOTUPFROMSBY);
					//onStartActionIntent.putExtra("WakeUpKey", mWakeUpkey);
				}
				startActivity(onStartActionIntent);
				//mWakeUpkey=-1;
			}
		}
	}

	//mediaplayer callbacks to be implemented in different class
	@Override
	public boolean onAvailable(int clientType) {
		Log.v(TAG, "PlayTVMediaPlayerFactory returns onAvailable clientType " + clientType);
		mSbyHandler.sendEmptyMessage(Events.EVENT_MP_AVAILABLITY_CHANGED.value);
		return false;
	}

	@Override
	public boolean onNotAvailable(int clientType) {
		Log.v(TAG, "PlayTVMediaPlayerFactory returns onNotAvailable");
		mSbyHandler.sendEmptyMessage(Events.EVENT_MP_UNAVAILABLE.value);
		return false;
	}

	@Override
	public void onPlayStarted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
			int presetNumber) {
	}

	@Override
	public void onPlayCompleted(Uri mediaPlayerUri, Map<String,String> headers, Medium medium,
			int presetNumber) {
	}

	@Override
	public void onPlayFinished(Uri mediaPlayerUri, Medium medium,
			int presetNumber) {
	}

	@Override
	public void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
	}

	@Override
	public void onInfo(boolean cicamAvailable) {
	}

	@Override
	public void onError(PlayTvMediaPlayer mpl, int what , int extra) {
		Log.d(TAG, "onError on PlayTvMediaPlayer should release mpl now ");
		releaseMediaplayer();
	}

	@Override
	public void onLockStatusChanged(int type, int status) {
		// TODO Auto-generated method stub
		
	}
        
        @Override
	public void onPurposeChanged(int purpose) {
		// TODO Auto-generated method stub
		
	}
	
	private WakeUpReason GetWakeUpReason() {
		Map<WakeUpReason, Integer> WakeupReasonMap = null; 
		WakeUpReason reason=WakeUpReason.WAKE_UP_REASON_UNKNOWN;
		try {
			WakeupReasonMap = mTvPowerManager.GetWakeUpReason();
			reason = WakeupReasonMap.keySet().iterator().next();
			//if(reason==WakeUpReason.WAKE_UP_REASON_RC_KEY) {
				//mWakeUpkey = WakeupReasonMap.get(reason);
				//Log.d(TAG,"mWakeUpkey is"+mWakeUpkey);
			//}
		} catch(Exception e) {
			Log.e(TAG,"GetWakeUpReason - exception caught!!!");
		}
		return reason;
	}
		
	public void addAlarm(int ClientId, int clients, long schtimeinmsecs) {
		Log.i(TAG, "AddAlarm called: startTime: " + schtimeinmsecs + 
				" ClientId " + ClientId + " clients " + clients);
		
		AlarmManager alarmMgr = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
		Intent intent = new Intent("org.droidtv.playtv.SbyServiceAlm");
		Uri sbyuri = Uri.parse(SSBYDefinitions.strAlmScheme + "://alarm?" + SSBYDefinitions.strClientid + "=" + ClientId + "&" +
				SSBYDefinitions.strAlarmid + "=" + clients);
		intent.setData(sbyuri);
		PendingIntent pendingIntent = PendingIntent.getBroadcast(this, 0,
				intent, PendingIntent.FLAG_UPDATE_CURRENT);
		
		Calendar alarmTime = Calendar.getInstance();
		alarmTime.setTimeInMillis(schtimeinmsecs);
		String mydate = java.text.DateFormat.getDateTimeInstance().format(alarmTime.getTime());
		Log.d(TAG,"Alarm set at time" + mydate);
		
		saveAlarm(clients,schtimeinmsecs);
		alarmMgr.setExact(AlarmManager.RTC_WAKEUP, schtimeinmsecs,pendingIntent);
	}

	public void RemoveAlarm(int ClientId, int AlarmId, long schtimeinmsecs) {
		Log.d(TAG, "RemoveAlarm called: startTime: " + schtimeinmsecs + 
				" ClientId " + ClientId + " AlarmId " + AlarmId);
		
		AlarmManager alarmMgr = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
		Intent intent = new Intent("org.droidtv.playtv.SbyServiceAlm");
		Uri sbyuri = Uri.parse(SSBYDefinitions.strAlmScheme + "://alarm?" + SSBYDefinitions.strClientid + "=" + ClientId + "&" +
				SSBYDefinitions.strAlarmid + "=" + AlarmId);
		intent.setData(sbyuri);
		PendingIntent pendingIntent = PendingIntent.getBroadcast(this, 0,
				intent, PendingIntent.FLAG_UPDATE_CURRENT);
		alarmMgr.cancel(pendingIntent);
	}

	public void onAlarmFired(Uri data) {
		if(data!=null) {
			try {
				mTvPowerManager = ITvPowerManager.Instance.getInterface();
				final PowerStates cPowerState = mTvPowerManager.GetPowerState();
				int clients  = Integer.parseInt(data.getQueryParameter(SSBYDefinitions.strAlarmid));
				Log.i(TAG,"onAlarmFired cPowerState = " + cPowerState + " transition " + mSysPowerstate + " clients: " + clients);
				if(cPowerState!=PowerStates.POWER_STATE_FULL_SYSTEM_START) {
					mSbyHandler.sendEmptyMessage(Events.EVENT_ALARM_FIRED.value);
				}else {
					//int client   = Integer.parseInt(data.getQueryParameter(SSBYDefinitions.strClientid));
					Message msg = mSbyHandler.obtainMessage(Events.EVENT_ALARM_FIRED.value, clients, 0);
					mSbyHandler.sendMessage(msg);
				}

				final int TCBit = (0x1 << ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
				final int SATBit =  (0x1 << ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
				boolean isTCInstallation = ((clients & TCBit) == TCBit);
				boolean isSATInstallation = ((clients & SATBit) == SATBit);
				//Log.d(TAG,"isTCInstallation: "+isTCInstallation+" isSATInstallation: "+isSATInstallation);
				if( isTCInstallation || isSATInstallation){
					Runnable r = new Runnable() {
						@Override
						public void run() {
							//Log to CUL Logger about BroadcastUpdate
							//Log.d(TAG,"Logging Installation PowerState to PowerLogger with PowerState: "+cPowerState);
							mPowerLogger.logPowerState(cPowerState, ILogger.PowerStateTransition.Reason.BROADCAST_UPDATE);
						}
					};
					mSbyHandler.post(r);
				}
			} catch(Exception e) {
				Log.e(TAG,"onAlarmFired Exception "+ e.getLocalizedMessage());
			}
		}
	}
	
	@Override
	public void onOlympicUsecaseUpdate(boolean enable, boolean isOTR) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onUriChanged(Uri mediaPlayerUri) {
			
	}
	
	@Override
	public void onCamUpgradeStarted(boolean status) {
	}
	
		
	public class init implements PowerStateEventHandler {

		@Override
		public void doAction(Events event, Message msg) {
			switch(event){
				case EVENT_INIT:
					SbyInit();
				break;
				default:
					break;
			}
			
		}

		@Override
		public void onAllActionsCompleted() {
			
		}
		
	}
	
	private void addClientToQue(int id) {
		String key = Integer.toString(id);
		if(mClientList.containsKey(key)) {
			SSBYClient client =mClientList.get(key);
			if(!mClientQue.contains(client)) {
				mClientQue.add(client);
				Log.d(TAG,"client added " + id);
			}
		}
	}
	
	private void removeClient(int id) {
		String key = Integer.toString(id);
		if(mClientList.containsKey(key)) {
			SSBYClient client = mClientList.get(key);
			mClientQue.remove(client);
			mClientList.remove(key);
			Log.d(TAG,"client removed " + id);
		}
	}
	
	private void reportAlarmFired(int clients, boolean add) {
		for(int i=1;i<MAX_CLIENTS+1;i++) {
			if((clients&(0x01<<i))>0) {
				SSBYClient client = mClientList.get(Integer.toString(i));
				if(client!=null){
					client.onAlarmFired();
					if(add){
						addClientToQue(i);
					}
				}
			}
		}
	}

	private boolean isVirginMode() {
		int virginbit = mTvSettingMgr.getInt(TvSettingsConstants.VIRGINBIT, 0, 0);
		int opvirgin  = mTvSettingMgr.getInt(TvSettingsConstants.OPVIRGIN, 0, 0);
		Log.d(TAG,"isVirginMode virginbit="+virginbit+" opvirgin="+opvirgin);
		return (virginbit == 1 || opvirgin == 1);
	}

	private boolean isNormalShutdown(Message msg) {
		try {
			Bundle b = (Bundle) msg.obj;
			if((StandByType)b.getSerializable("StandByType")==ITvPowerManager.StandByType.STANDBY_QUICK){
				Log.d(TAG,"STANDBY_QUICK");
				return false;
			}
		}catch(Exception e) {
			Log.e(TAG,"Exception reading extras" + e.getLocalizedMessage());
		}
		return true;
	}
		
	private class full_to_semi implements PowerStateEventHandler {
		SSBYClient clientinlist = null;
		@Override
		public void doAction(Events event, Message msg) {
			switch(event) {
				case EVENT_CLIENT_COMPLETED:
				if(mMediaControlState==ControlStates.MSTATE_AVAILABLE) {	
					clientinlist = mClientQue.peekFirst();
					if(clientinlist!=null) {
						if(clientinlist.getId()==msg.arg1) {
							if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS) {
								clientinlist.onActioncompleted();
								mClientQue.remove(clientinlist);
								clientinlist = mClientQue.peekFirst();
								if(clientinlist!=null) {
									if(clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED){
										clientinlist.onStartAction();
									}else {
										Log.d(TAG,"client current state " + clientinlist.getcurrentState() + " id" + clientinlist.getId());
									}
								}else {
									onAllActionsCompleted();
								}
							}
							else if(clientinlist.getcurrentState()==ClientStates.CSTATE_STOPPING) {
								Log.d(TAG,"Restarting the client " + clientinlist.getId());
								clientinlist.onActioncompleted();
								clientinlist.onStartAction();
							}
						}
						else {
							Log.e(TAG,"unexpected here");
						}
					}
				} else if(mMediaControlState==ControlStates.MSTATE_WAITING) {
					clientinlist = mClientQue.peekFirst();
					if((clientinlist!=null)&&(clientinlist.getId()==msg.arg1)) {
						if(clientinlist.getcurrentState()==ClientStates.CSTATE_STOPPING) {
							clientinlist.onActionReset();
						}
					}
				}
				break;
			case EVENT_CLIENT_CONNECTED:
				//start activity if conditions are met
				clientinlist = mClientQue.peekFirst();
				if((clientinlist!=null) && (clientinlist.getId()==msg.arg1)) {
					if(mMediaControlState==ControlStates.MSTATE_AVAILABLE){
						clientinlist.onStartAction();
					}
				}
				break;
			case EVENT_CLIENT_DISCONNECTED:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					removeClient(msg.arg1);
					if(clientinlist.getId()==msg.arg1) {
						Log.d(TAG,"Current client died ");
						clientinlist = mClientQue.peekFirst();
						if(clientinlist!=null) {
							if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED) && 
								(mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
									clientinlist.onStartAction();
							}
						}else {
							if(mMediaControlState==ControlStates.MSTATE_AVAILABLE) {
								onAllActionsCompleted();
							}
						}
					}else {
						Log.d(TAG,"client died");
					}
				}
				break;
			case EVENT_MP_AVAILABLE:
				//start activity if conditions are met
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED){
						//KT add. enter standby case.
						sendBroadcast(new Intent("org.droidtv.pbsserver.IS_SEMI_CLIENT_RUNNING_TRUE"));
						clientinlist.onStartAction();
					}
				}
				break;
			case EVENT_MP_UNAVAILABLE:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS){
						clientinlist.onStopAction();
					}
				}
				break;
			case EVENT_POWERCHANGE_END:
				//check virgin mode, [TF416PHIEUMTK00-707] DUT will auto start after RC power off about 10min at instant initial cloning(IIC) wizard
				if (isVirginMode()) {
					mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_DSL.value);
					break;
				}
				//add clients here
				if(isNormalShutdown(msg)) {
					clientinlist = mClientQue.peekFirst();
					if ((clientinlist!=null) && ((clientinlist.getId() == ITvSemiStandbyControl.ACTION_OAD_ACQUISITION) 
							|| (clientinlist.getId() == ITvSemiStandbyControl.ACTION_VSECURE_ACQUISITION))
							&& (clientinlist.getcurrentState() == ClientStates.CSTATE_INPROGRESS)) {
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_HTV_SSBY_DELAY, true); // Reno 20160217 extends 5 minutes for staying in semi standby
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION, true);//min.jiang add 2015-07-16
						addClientToQue(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
						addClientToQue(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION, false);//min.jiang modify 2015-07-16
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_HTV_AUTOUPGRADE, true);
					} else {
						mClientQue.clear();
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_HTV_SSBY_DELAY, true); // Reno 20160217 extends 5 minutes for staying in semi standby
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION, true);//min.jiang add 2015-07-16
						addClientToQue(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
						addClientToQue(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
						addClientToQue(ITvSemiStandbyControl.ACTION_VSECURE_ACQUISITION);
						addClientToQue(ITvSemiStandbyControl.ACTION_OAD_ACQUISITION);
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION, false);//min.jiang modify 2015-07-16
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_HTV_AUTOUPGRADE, true);
					}
					clientinlist = mClientQue.peekFirst();
					if(clientinlist!=null){
						if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED)
								&& (mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
							clientinlist.onStartAction();
							//KT add. enter standby case.
							sendBroadcast(new Intent("org.droidtv.pbsserver.IS_SEMI_CLIENT_RUNNING_TRUE"));
						} else {
							if(mMediaControlState!=ControlStates.MSTATE_AVAILABLE) {
								mSbyHandler.sendEmptyMessage(Events.EVENT_REQUEST_MPLAYER.value);
							}
						}
					}else {
						onAllActionsCompleted();
					}
				}else {
					mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_DSL.value);
				}
				break;
			case EVENT_LAST_SELECTION_DONE:
				mSbyHandler.sendEmptyMessage(Events.EVENT_REGISTER_ALARM.value);
				mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_DSL.value);
				break;
			case EVENT_ALARM_FIRED:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null){
					if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED)
						&& (mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
						clientinlist.onStartAction();
						//KT add. alarm case.
						sendBroadcast(new Intent("org.droidtv.pbsserver.IS_SEMI_CLIENT_RUNNING_TRUE"));
					} else {
						if(mMediaControlState!=ControlStates.MSTATE_AVAILABLE) {
							mSbyHandler.sendEmptyMessage(Events.EVENT_REQUEST_MPLAYER.value);
						}
					}
				}else {
					onAllActionsCompleted();
				}
				break;
			default:
				Log.e(TAG,"unexpected event " + event);
				break;
			}
		}
		@Override
		public void onAllActionsCompleted() {
			Log.d(TAG,"onAllActionsCompleted " + mSysPowerstate);
			//KT add. complete clean.
			sendBroadcast(new Intent("org.droidtv.pbsserver.IS_SEMI_CLIENT_RUNNING_FALSE"));
			int device = PlayTvUtils.getLastSelectedDevice(); 
			if((device==TvSettingsDefinitions.LastSelectedDeviceConstants.DVBTC) || 
				(device==TvSettingsDefinitions.LastSelectedDeviceConstants.DVBS)) {
				mSbyHandler.sendEmptyMessage(Events.EVENT_REGISTER_ALARM.value);
				mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_DSL.value);
			} else {
				mSbysession.selectExtension(device);
			}
		}
	}
	
	private class booting_to_semi_alarm implements PowerStateEventHandler {

		@Override
		public void doAction(Events event, Message msg) {
			SSBYClient clientinlist = null;
			switch(event){
			case EVENT_ALARM_FIRED:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null){
					if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED)
						&& (mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
						clientinlist.onStartAction();
					} else {
						if(mMediaControlState!=ControlStates.MSTATE_AVAILABLE) {
							mSbyHandler.sendEmptyMessage(Events.EVENT_REQUEST_MPLAYER.value);
						}
					}
				}else {
					onAllActionsCompleted();
				}
			break;	
			case EVENT_POWERCHANGE_END:
				reportAlarmFired(getSSBYAlarmClient(),true);
				addClientToQue(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION);
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null){
					if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED)&&
						(mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
						clientinlist.onStartAction();
					} else {
						if(mMediaControlState!=ControlStates.MSTATE_AVAILABLE) {
							mSbyHandler.sendEmptyMessage(Events.EVENT_REQUEST_MPLAYER.value);
						}
					}
				}else {
					onAllActionsCompleted();
				}
				break;
			case EVENT_CLIENT_COMPLETED:
				if(mMediaControlState==ControlStates.MSTATE_AVAILABLE) {	
					clientinlist = mClientQue.peekFirst();
					if(clientinlist!=null) {
						if(clientinlist.getId()==msg.arg1) {
							if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS) {
								clientinlist.onActioncompleted();
								mClientQue.remove(clientinlist);
								clientinlist = mClientQue.peekFirst();
								if(clientinlist!=null) {
									if(clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED){
										clientinlist.onStartAction();
									}else {
										Log.d(TAG,"client current state " + clientinlist.getcurrentState() + " id" + clientinlist.getId());
									}
								}else {
									onAllActionsCompleted();
								}
							}
							else if(clientinlist.getcurrentState()==ClientStates.CSTATE_STOPPING) {
								Log.d(TAG,"Restarting the client " + clientinlist.getId());
								clientinlist.onActionReset();
								clientinlist.onStartAction();
							}
						}
						else {
							Log.d(TAG,"unexpected here");
						}
					}
				} else if(mMediaControlState==ControlStates.MSTATE_WAITING) {
					clientinlist = mClientQue.peekFirst();
					if(clientinlist!=null) {
						if(clientinlist.getId()==msg.arg1) {
							if(clientinlist.getcurrentState()==ClientStates.CSTATE_STOPPING) {
								clientinlist.onActionReset();
							}
						}
					}
				}
				break;
			case EVENT_CLIENT_DISCONNECTED:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					removeClient(msg.arg1);
					if(clientinlist.getId()==msg.arg1) {
						Log.d(TAG,"Current client died ");
						clientinlist = mClientQue.peekFirst();
						if(clientinlist!=null) {
							if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED) && 
								(mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
									clientinlist.onStartAction();
							}
						}else {
							if(mMediaControlState==ControlStates.MSTATE_AVAILABLE) {
								onAllActionsCompleted();
							}
						}
					}else {
						Log.d(TAG,"client died");
					}
				}else {
					removeClient(msg.arg1);
				}
				break;
			case EVENT_MP_AVAILABLE:
				//start activity if conditions are met
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED){
						clientinlist.onStartAction();
					}
				}
				break;
			case EVENT_MP_UNAVAILABLE:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS){
						clientinlist.onStopAction();
					}
				}
				break;
			case EVENT_CLIENT_CONNECTED:
				//start activity if conditions are met
				clientinlist = mClientQue.peekFirst();
				if((clientinlist!=null)&&(clientinlist.getId()==msg.arg1)) {
					if(mMediaControlState==ControlStates.MSTATE_AVAILABLE){
						clientinlist.onStartAction();
					}
				}
				break;
			case EVENT_LAST_SELECTION_DONE:
				mSbyHandler.sendEmptyMessage(Events.EVENT_REGISTER_ALARM.value);
				mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_DSL.value);
				mSbyHandler.sendEmptyMessage(Events.EVENT_REQUEST_SBY.value);
				break;
			default:
				break;
			}
		}

		@Override
		public void onAllActionsCompleted() {
			Log.d(TAG,"onAllActionsCompleted " + mSysPowerstate);
			int device = PlayTvUtils.getLastSelectedDevice(); 
			if((device==TvSettingsDefinitions.LastSelectedDeviceConstants.DVBTC) || 
				(device==TvSettingsDefinitions.LastSelectedDeviceConstants.DVBS)) {
				mSbyHandler.sendEmptyMessage(Events.EVENT_REGISTER_ALARM.value);
				mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_DSL.value);
				mSbyHandler.sendEmptyMessage(Events.EVENT_REQUEST_SBY.value);
			} else {
				mSbysession.selectExtension(device);
			}
		}
		
	}
	
	private class booting_to_semi_cold implements PowerStateEventHandler {

		@Override
		public void doAction(Events event, Message msg) {
			SSBYClient clientinlist = null;
			switch(event){
			case EVENT_ALARM_FIRED:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null){
					if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED)
						&& (mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
						clientinlist.onStartAction();
					} else {
						if(mMediaControlState!=ControlStates.MSTATE_AVAILABLE) {
							mSbyHandler.sendEmptyMessage(Events.EVENT_REQUEST_MPLAYER.value);
						}
					}
				}else {
					onAllActionsCompleted();
				}
			break;	
			case EVENT_POWERCHANGE_END:
				//add clients here clock calib only
				mClientQue.clear();
                /* [CR][TF415PHIEUMTK01-208] When TV is in standby, always search for the RF FW and Clone Data ericws_20161116 */
                String bootreason_kernel = SystemProperties.get("sys.droidtv.bootreason_kernel");
                boolean isAbnormalReboot = false;
                Log.d(TAG, "sys.droidtv.bootreason_kernel - " + bootreason_kernel);

                if (bootreason_kernel != null) {
                    if (bootreason_kernel.equals("kernel_panic")) {
                        isAbnormalReboot = true;
                    }
                }

				if ((SystemProperties.get("htv.force_reboot").equals("true")) || (true == isAbnormalReboot)) {
                    int autoUpgrade = mTvSettingMgr.getInt(TvSettingsConstants.PBSMGR_PROPERTY_AUTO_UPGRADE, 0, 0);
                    int scanMode = mTvSettingMgr.getInt(TvSettingsConstants.PBSMGR_PROPERTY_SCAN_MODE,0,0);
                    int lowPowerStandbyMode =  mTvSettingMgr.getInt(TvSettingsConstants.PBSMGR_PROPERTY_LOW_POWER_STANDBY, 0, 0);
                    Log.i(TAG, "booting_to_semi_cold: add the clock sync to que");
                    addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION, true);
                    Log.i(TAG,"booting_to_semi_cold: scanMode = " + scanMode + ", autoUpgrade = " + autoUpgrade + ", lowPowerStandbyMode = " + lowPowerStandbyMode);
                    if ((scanMode == TvSettingsDefinitions.PbsRFUpgradeScanModeConstants.PBSMGR_RF_UPGRADE_MODE_CONTINUOUS)
                        && (autoUpgrade == TvSettingsDefinitions.PbsAutoUpgrade.PBSMGR_AUTO_UPGRADE_ON)
                        && (lowPowerStandbyMode == TvSettingsDefinitions.PbsLowPowerStandby.PBSMGR_LOW_POWER_STANDBY_FAST)) {
                        Log.i(TAG,"[ericws][" + Thread.currentThread().getStackTrace()[2].getLineNumber() + "]");
                        //onAllActionsCompleted();
                        addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_HTV_AUTOUPGRADE, true);
                    } else {
                        /* Request by Vincent for [TF415PHIEUMTK66-2317] TV does not send IPCloneServices anymore */
                        sendBroadcast(new Intent("org.droidtv.intent.action.semi.standby.IP_TO_TV"));
                    }
                } else { // Reno 20160523 full on to standby reboot

                    /* [START] ericws_20161206 [TF415PHIEUMTK66-1831] Some background activities do not execute when code boot. */
                    mClientQue.clear();
                    addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION, true);//min.jiang add 2015-07-16
                    addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_HTV_SSBY_DELAY, true); // Reno 20160217 extends 5 minutes for staying in semi standby
                    addClientToQue(ITvSemiStandbyControl.ACTION_TC_INSTALLATION);
                    addClientToQue(ITvSemiStandbyControl.ACTION_SAT_INSTALLATION);
                    addClientToQue(ITvSemiStandbyControl.ACTION_VSECURE_ACQUISITION);
                    addClientToQue(ITvSemiStandbyControl.ACTION_OAD_ACQUISITION);
                    addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION, false);//min.jiang modify 2015-07-16
                    addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_HTV_AUTOUPGRADE, true);
                    /* [END] ericws_20161206 [TF415PHIEUMTK66-1831] Some background activities do not execute when code boot. */

					// Reno 20160919
					if (!SystemProperties.get("persist.sys.pbs_standby_clock").equals("ALWAYS_DISPLAY")) {
						addClientToQueOnPbs(ITvSemiStandbyControl.ACTION_HTV_SSBY_DELAY, true);
					}
				}
				// Reno
				//addClientToQue(ITvSemiStandbyControl.ACTION_RECORDING);
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED)&&
						(mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
						clientinlist.onStartAction();
					} else {
						if(mMediaControlState!=ControlStates.MSTATE_AVAILABLE) {
							mSbyHandler.sendEmptyMessage(Events.EVENT_REQUEST_MPLAYER.value);
						}
					}
				}else {
					onAllActionsCompleted();
				}
				break;
			case EVENT_CLIENT_COMPLETED:				
				if(mMediaControlState==ControlStates.MSTATE_AVAILABLE) {	
					clientinlist = mClientQue.peekFirst();
					if(clientinlist!=null) {
						if(clientinlist.getId()==msg.arg1) {
							if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS) {
								clientinlist.onActioncompleted();
								mClientQue.remove(clientinlist);
								clientinlist = mClientQue.peekFirst();
								if(clientinlist!=null) {
									if(clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED){
										clientinlist.onStartAction();
									}else {
										Log.d(TAG,"client current state " + clientinlist.getcurrentState() + " id" + clientinlist.getId());
										Log.d(TAG,"mMediaControlState state " + mMediaControlState);
									}
								}else {
									onAllActionsCompleted();
								}
							}
							else if(clientinlist.getcurrentState()==ClientStates.CSTATE_STOPPING) {
								Log.d(TAG,"Restarting the client " + clientinlist.getId());
								clientinlist.onActionReset();
								clientinlist.onStartAction();
							}
						}
						else {
							Log.d(TAG,"unexpected here");
						}
					}
				} else if(mMediaControlState==ControlStates.MSTATE_WAITING) {
					clientinlist = mClientQue.peekFirst();
					if((clientinlist!=null) && (clientinlist.getId()==msg.arg1)) {
						if(clientinlist.getcurrentState()==ClientStates.CSTATE_STOPPING) {
							clientinlist.onActionReset();
						}
					}
				}
				break;
			case EVENT_CLIENT_DISCONNECTED:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					removeClient(msg.arg1);
					if(clientinlist.getId()==msg.arg1) {
						Log.d(TAG,"Current client died ");
						clientinlist = mClientQue.peekFirst();
						if(clientinlist!=null) {
							if((clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED) && 
								(mMediaControlState==ControlStates.MSTATE_AVAILABLE)){
									clientinlist.onStartAction();
							}
						}else {
							if(mMediaControlState==ControlStates.MSTATE_AVAILABLE) {
								onAllActionsCompleted();
							}
						}
					}else {
						Log.d(TAG,"client died");
					}
				}else {
					removeClient(msg.arg1);
				}
				break;
			case EVENT_MP_AVAILABLE:
				//start activity if conditions are met
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_CONNECTED){
						clientinlist.onStartAction();
					}
				}
				break;
			case EVENT_MP_UNAVAILABLE:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS){
						clientinlist.onStopAction();
					}
				}
				break;
			case EVENT_LAST_SELECTION_DONE:
				mSbyHandler.sendEmptyMessage(Events.EVENT_REGISTER_ALARM.value);
				mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_DSL.value);	
				break;
			default:
				break;
			}
		}

		@Override
		public void onAllActionsCompleted() {
			Log.d(TAG,"onAllActionsCompleted " + mSysPowerstate);
			int device = PlayTvUtils.getLastSelectedDevice(); 
			if((device==TvSettingsDefinitions.LastSelectedDeviceConstants.DVBTC) || 
				(device==TvSettingsDefinitions.LastSelectedDeviceConstants.DVBS)) {
				mSbyHandler.sendEmptyMessage(Events.EVENT_REGISTER_ALARM.value);
				mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_DSL.value);
			} else {
				mSbysession.selectExtension(device);
			}
		}
		
	}
	
	private class semi_to_full implements PowerStateEventHandler {
		SSBYClient clientinlist = null;		
		@Override
		public void doAction(Events event, Message msg) {
			switch(event){
			case EVENT_CLIENT_COMPLETED:
				clientinlist = mClientQue.peekFirst();
				if((clientinlist!=null) &&(clientinlist.getId()==msg.arg1)) {
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_STOPPING) {
						clientinlist.onActioncompleted();
						mClientQue.clear();
						onAllActionsCompleted();
					}
					else if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS) {
						clientinlist.onActioncompleted();
						mClientQue.clear();                        
						}
					else {
						Log.d(TAG,"unexpected client state here");
					}
				}
				else {
					Log.d(TAG,"unexpected here");
					break;
				}
				break;
			case EVENT_CLIENT_DISCONNECTED:
				clientinlist = mClientQue.peekFirst();
				if((clientinlist!=null) && (clientinlist.getId()==msg.arg1)) {
					Log.d(TAG,"Current client died generate completed");
					removeClient(msg.arg1);
					mSbyHandler.sendEmptyMessage(Events.EVENT_CLIENT_COMPLETED.value);
				} else {
					removeClient(msg.arg1);
				}
				break;
			case EVENT_MP_UNAVAILABLE:
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null) {
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS){
						clientinlist.onStopAction();
					}
				}
				break;
			case EVENT_POWERCHANGE_END:
				acquireDSL();
				boolean isOadInProgress = false;
				boolean isClockInProgress = false;
				clientinlist = mClientQue.peekFirst();
				if(clientinlist!=null){
					if(clientinlist.getcurrentState()==ClientStates.CSTATE_INPROGRESS) {
						// if OAD and download is in progress dont call stop and
						// launch OAD activity
						if (clientinlist.getId() == ITvSemiStandbyControl.ACTION_OAD_ACQUISITION) {
							isOadInProgress = showOadDownloadProgress();
						}
						if (clientinlist.getId() == ITvSemiStandbyControl.ACTION_CLOCK_CALIBRATION) {
							isClockInProgress = true;
						}
						if (!isOadInProgress)
							clientinlist.onStopAction();
					}else if(clientinlist.getcurrentState()==ClientStates.CSTATE_STOPPING){
						Log.d(TAG,"Wait for the client to finish");
					}else {
						Log.d(TAG,"clearing the que");
						mClientQue.clear();
						onAllActionsCompleted();
					}
				} else {
					onAllActionsCompleted();
				}
				break;
			default:
				break;
			}
		}	

		@Override
		public void onAllActionsCompleted() {
			mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_MPLAYER.value);
			String sStartApp = null;
			try {
				sStartApp = SystemProperties.get("sys.boot.StartAppLaunch");
			}catch(Exception e) {
				Log.e(TAG,"Error reading system prop" + e.getLocalizedMessage());
			}
			boolean startAppLaunched = false;
			if(sStartApp != null && !sStartApp.equals("")){
				if(sStartApp.equalsIgnoreCase("True")) {
					startAppLaunched = true;
					Log.d(TAG,"StartAppLaunch:"+sStartApp);
				}
			}
			if(!startAppLaunched){
				Log.d(TAG,"StartAppLaunch:"+startAppLaunched);
				//mSbyHandler.sendEmptyMessage(Events.EVENT_START_APP.value);
				if (SystemProperties.get("persist.sys.pbs_mode").equals("OFF")) {
					mSbyHandler.sendEmptyMessage(Events.EVENT_START_APP.value);
				}
			}
		}

		private boolean showOadDownloadProgress() {
			ITvOADControl tvOad = null;
			boolean isOadInProgress = false;
			if (mplaytvmpl != null) {
				tvOad = mplaytvmpl.getMediaPlayerInstance()
						.getTvMediaPlayerContext().getTvOADControl();
				if (tvOad != null) {
					if (tvOad.getDownloadProgress() > 0) {
						isOadInProgress = true;
						Intent oadMessageIntent = new Intent();
						oadMessageIntent
								.setAction("org.droidtv.oad.SHOWOADMESSAGE");
						oadMessageIntent.putExtra("MessageType", 8);
						oadMessageIntent
								.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
						startActivity(oadMessageIntent);
					}
				}
			}
			return isOadInProgress;
		}
		
	}
		
	private class ddr_to_full_on implements PowerStateEventHandler {

		@Override
		public void doAction(Events event, Message msg) {
			switch(event){
			case EVENT_CLIENT_DISCONNECTED:
				removeClient(msg.arg1);
				break;
			case EVENT_POWERCHANGE_END:
				Bundle b = (Bundle) msg.obj;
				acquireDSL();
				mSbyHandler.sendEmptyMessage(Events.EVENT_RELEASE_MPLAYER.value);
				if((b!=null)&&(!b.getBoolean("WakeUpAppLaunched",false))){
					mSbyHandler.sendEmptyMessage(Events.EVENT_START_APP.value);
				}
				break;
			default:
				break;
			}
		}

		@Override
		public void onAllActionsCompleted() {
			
		}
		
	}
	
		
	private class SSbyServiceImpl extends TvSemiStandbyControl.Stub implements SSBYClientDeathListener{
		
		public void registerSemiStandbyAction(int id, IBinder binder) {
			Log.d(TAG,"registerSemiStandbyAction called " + id);
			try {
				if(isClientSupported(id)) {
					SSBYClient ssbyclient = new SSBYClient(id,new TvSemiStandbyControlImpl.TvSemiStandbyNotify.Proxy(binder),binder,this);
					Message msg = mSbyHandler.obtainMessage(Events.EVENT_CLIENT_CONNECTED.value,id,0,ssbyclient);
					mSbyHandler.sendMessage(msg);
				}else {
					Log.d(TAG,"id not supported " + id);
				}
			}catch(Exception e) {
				e.printStackTrace();
			}
		}
		
		public void unregisterSemiStandbyAction(int id) {
			Log.d(TAG,"unregisterSemiStandbyAction called " + id);
			try {
				SSBYClient client = mClientList.get(Integer.toString(id));
				if(client!=null){
					client.unregister();
					Message msg = mSbyHandler.obtainMessage(Events.EVENT_CLIENT_DISCONNECTED.value,id,0);
					mSbyHandler.sendMessage(msg);
				}
			}catch(Exception e) {
				Log.e(TAG,"Unregister exception " + e.getLocalizedMessage());
			}
		}
		
		public void setActionCompleted(int id) {
			Log.d(TAG,"setActionCompleted called " + id);
			Message msg = mSbyHandler.obtainMessage(Events.EVENT_CLIENT_COMPLETED.value,id,0);
			mSbyHandler.sendMessage(msg);
		}
		
		public void setAlarmForSemiStandbyAction(int id, long nextAlarmTimeMSecs) {
			Log.v(TAG,"setAlarmForSemiStandbyAction called " + id);
			if(isClientSupported(id)) {
				Message msg = mSbyHandler.obtainMessage(Events.EVENT_ALARM_REQUEST.value,id,0);
				Bundle b = msg.getData();
				b.putLong("almtime",nextAlarmTimeMSecs);
				mSbyHandler.sendMessage(msg);
			}
		}

		@Override
		public void onSSBYClientDied(SSBYClient deadclient) {
			Log.d(TAG,"binderDied " + deadclient.getId());
			String key = Integer.toString(deadclient.getId());
			SSBYClient client = mClientList.get(key);
			if((client!=null) && (client==deadclient)) {
				Message msg = mSbyHandler.obtainMessage(Events.EVENT_CLIENT_DISCONNECTED.value,deadclient.getId(),0);
				mSbyHandler.sendMessage(msg);
			}else {
				Log.d(TAG,"client already removed");
			}
		}
	}
	
	private class PowerEventsReceiver implements IPowerEvents {
		
		@Override
		public void onPowerChangeStart(PowerStates from, PowerStates to, Bundle extras) {
			if(mSbyHandler!=null) {
				synchronized(mSbyHandler) {
					Message msg = mSbyHandler.obtainMessage(Events.EVENT_POWERCHANGE_START.value,from.ordinal(),to.ordinal(),extras);
					mSbyHandler.sendMessage(msg);
				}
			}
		}
		
		@Override
		public void onPowerChangeEnd(PowerStates from, PowerStates to, Bundle extras) {
			if(mSbyHandler!=null) { 
				synchronized(mSbyHandler) {
					Message msg = mSbyHandler.obtainMessage(Events.EVENT_POWERCHANGE_END.value,from.ordinal(),to.ordinal(),extras);
					mSbyHandler.sendMessage(msg);
				}
			}
		}
	}

	public static IPowerEvents getPowerEventsListener() {
		return mPowerEventListener;
	}

	@Override
	public void onObserverSessionCreated() {
		mSbyHandler.sendEmptyMessage(Events.EVENT_FAC_AVAILABLE.value);
	}

	@Override
	public void onObserverSessionClosed() {
		mSbyHandler.sendEmptyMessage(Events.EVENT_FAC_UNAVAILABLE.value);
	}

	@Override
	public void onExtensionSessionTuned() {
		mSbyHandler.sendEmptyMessage(Events.EVENT_LAST_SELECTION_DONE.value);
		mSbysession.releaseExtension();
	}
	
	private boolean saveAlarm(int client, long atime) {
		try {
			SharedPreferences ssbyStore = getApplicationContext().
					getSharedPreferences(SSBYDefinitions.strSSBYStore,Context.MODE_PRIVATE);
			if(ssbyStore!=null) {
				Editor editor = ssbyStore.edit();
				editor.putLong(SSBYDefinitions.strSSBYLastAlarm, atime);
				editor.putInt(SSBYDefinitions.strSSBYLastClient, client);
				editor.commit();
				return true;
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
		return false;
	}
	
	private int getSSBYAlarmClient() {
		int ssbyclient = 0;
		try {
			SharedPreferences ssbyStore = getApplicationContext().
					getSharedPreferences(SSBYDefinitions.strSSBYStore,Context.MODE_PRIVATE);
			if(ssbyStore!=null) {
				Long value = ssbyStore.getLong(SSBYDefinitions.strSSBYLastAlarm,0);				
				Calendar currentime = Calendar.getInstance();
				Calendar alarmtime = Calendar.getInstance();
				alarmtime.setTimeInMillis(value);
				Log.d(TAG,"Time now=" + java.text.DateFormat.getDateTimeInstance().format(currentime.getTime()) + 
						" Alarm time=" + java.text.DateFormat.getDateTimeInstance().format(alarmtime.getTime()));
				if( (currentime.getTimeInMillis()>=value) && ( (currentime.getTimeInMillis()-value)<50000)) {
					ssbyclient = ssbyStore.getInt(SSBYDefinitions.strSSBYLastClient,0);
				}
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
		return ssbyclient;
	}
	
	private boolean isClientSupported(int id) {
		boolean retval=false;
		switch(id){
			case ITvSemiStandbyControl.ACTION_OAD_ACQUISITION:
				//retval=PlayTvDiversity.isOADSupported();

				//KT, HTV using ITvSemiStandbyControl.ACTION_HTV_AUTOUPGRADE
				retval=false;
				break;
			default:
				retval=true;
		}
		return retval;
	}

	@Override
	protected void dump(FileDescriptor fd, PrintWriter writer, String[] args) {
		writer.println("Current Transition " + mSysPowerstate );
		writer.println("Clients " + mClientList.size() + " in que=" + mClientQue.size());
		if(mClientQue.size()>0){
			try {
				writer.println("current client = " + mClientQue.peekFirst().getId());
			} catch(Exception e) {
				
			}
		}
		if(mShutdownLock!=null) {
			writer.println("Dont ShutdownLock " + mShutdownLock.isHeld());
		}
	}
}
