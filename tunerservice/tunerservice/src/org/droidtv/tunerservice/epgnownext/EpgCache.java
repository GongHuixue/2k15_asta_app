package org.droidtv.tunerservice.epgnownext;

import java.util.ArrayList;
import java.util.List;

import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;

import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import org.droidtv.tv.smarttv.INetTvService;
//import org.droidtv.playtv.PlayTvApplication;

public class EpgCache implements IEpgProviderNotify {

	private EpgNowNextData mCurrentNowNextData = null;
	private EpgNowNextData mUserSpecificNowNextData = null;
	private List<IEpgProviderNotify> mClients = new ArrayList<IEpgProviderNotify>();

	private boolean mIsEpgBCEpg = true;
	private boolean mIsInitialized = false;
	private static final String TAG = "EpgCache";

	private ServiceConnector mServiceConnector = new ServiceConnector();
	private INetTvService mNettvService = null;
	private ITvSettingsManager settingsManager = ITvSettingsManager.Instance.getInterface();
	
	private Context mContext = null;
	private ITVSettingsManagerCallBack mStorageBinder=null;
	private int registeredConstants[] = {
			TvSettingsConstants.INSTSETTINGSDVBEPGCHOICE,
			TvSettingsConstants.INSTALLATIONCOUNTRY };
	
	private int currentChannel = -1, userChannel = -1;

	
	public EpgCache(Context context) {
	
		mContext = context;
		connectService();
		mStorageBinder = new ITVSettingsManagerCallBack();
		ITvSettingsManager.Instance.getInterface().SetCallBacks(mStorageBinder, registeredConstants);
	}

	public void connectService() {
		Thread connectorThread = new Thread() {
			public void run() {
				Intent intent = new Intent("org.droidtv.tv.intent.action.NETTVSERVICES");
				mContext.bindService(intent, mServiceConnector, Service.START_STICKY);
			}
		};connectorThread.start();
	}
	
	/* we provider an un-register method
		It will be called by the PlayTvApplication 
		when plytvApplication itself gets died.
	*/
	
	public void release() {
	
		Log.d(TAG," start releasing epg cache instance");
		synchronized (this) {
			if (mCurrentNowNextData != null) {
				mCurrentNowNextData.releaseContext();
			}
			
			if (mUserSpecificNowNextData != null) {
				mUserSpecificNowNextData.releaseContext();
			}
			mCurrentNowNextData = null;
			mUserSpecificNowNextData = null;
		}
		
		if (mServiceConnector != null) {
			mContext.unbindService(mServiceConnector);
		}
				
		
		mNettvService = null;
		mContext = null;
		Log.d(TAG," done releasing of epg cache instance");
	}
	
	public boolean isBCEpgMode() {
		
		return mIsEpgBCEpg;
	}

	public void onEpgDataChanged(int presetID) {
		
		synchronized (this) {
		
			for (IEpgProviderNotify listener : mClients) {
				Log.d(TAG, "Sending notification for the client"+listener);
				try {
					if(listener != null) {
						listener.onEpgDataChanged(presetID);
					} else {
						Log.d(TAG, "listener is null for to notify");
					}
				}catch(Exception e){
					Log.d(TAG,"exception while notifying clients"+e);
				}
			}
		}
	}
	
	public void onEpgDataProviderChanged() {
		
		for (IEpgProviderNotify listener : mClients) {
		
			if(listener != null) {
				listener.onEpgModeChanged();
			}
		}
	}

	public void onEpgModeChanged() {
	
	}
	
	class ServiceConnector implements ServiceConnection {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {

			mNettvService = INetTvService.Instance.asInterface(service);
			try {
				service.linkToDeath(new ServiceDeathHandler(), 0);
			} catch (RemoteException e) {
				Log.d(TAG, "onServiceConnected : RemoteException"); 
			}
			Log.d(TAG, "Bind response received from INetTvService"	+ mNettvService);
			setInitialized(true);
			evaluateEPG();
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d(TAG, "Service disconnect call");
			mNettvService = null;
			//mIsInitialized = false; even if the service dies we dont want Zap bat to get blocked.
		}
	}
	
	class ServiceDeathHandler implements IBinder.DeathRecipient {

		@Override
		public void binderDied() {
			Log.d(TAG, "org.droidtv.tv.intent.action.NETTVSERVICES has died. Re-connecting...");
			mIsEpgBCEpg = true;
			connectService();
		}
	}

	private void evaluateEPG() {

		int settingEpgChoice = settingsManager.getInt(
				TvSettingsConstants.INSTSETTINGSDVBEPGCHOICE, 0, 0);

		boolean currentEpgProvider = mIsEpgBCEpg;
		
		if (settingEpgChoice == TvSettingsDefinitions.InstSettingsDvbEpgConstants.DVBEPG) {
			Log.d(TAG, "DVBEPG mode");
			
			mIsEpgBCEpg = true;
		} else {
			if (mNettvService != null) {
				if (mNettvService.isIpEpgAvailable()) {
					Log.d(TAG, "IP EPG mode");
					mIsEpgBCEpg = false;
				} else {
					Log.d(TAG, "IP EPG not avl");
					mIsEpgBCEpg = true;
				}
			} else {
				Log.w(TAG, "service not connected to evalute epg");
			}
		}
		
		synchronized (this) {
			if(currentChannel!=-1){
				onPlayCompleted(currentChannel);
			}
		}
		synchronized (this) {
			if(userChannel!=-1){
				queryNowNextData(userChannel);
			}
		}
		
		if (currentEpgProvider != mIsEpgBCEpg) {
			onEpgDataProviderChanged();
		}
	}

	public void setInitialized(boolean status) {
		// TODO Auto-generated method stub
		synchronized (this) {
			mIsInitialized = status;
		}
	}

	public void onPlayCompleted(int uniqueChannelId) {

		
		if(uniqueChannelId == 0 || uniqueChannelId == -1) return;
		
		synchronized (this) {
			Log.d(TAG,"onPlayCompleted received from the playtvService mIsInitialized"+mIsInitialized + "Channel id "+uniqueChannelId);

			if (!mIsInitialized) {
				Log.d(TAG,"return from cache onPlayCompleted bcz "+mIsInitialized);
				currentChannel = uniqueChannelId;
				return;
			}
			currentChannel = -1;
			Log.d(TAG,"onPlayCompleted mUserSpecificNowNextData mCurrentNowNextData="+mCurrentNowNextData);
			
			if(mCurrentNowNextData != null) {
				mCurrentNowNextData.releaseContext();
				mCurrentNowNextData = null;
			}
				
			if ((mUserSpecificNowNextData != null)
					&& (mUserSpecificNowNextData.getNowNextDataChannelId() == uniqueChannelId)) {
							//! indicates ---now we can use mCurrentNowNext as a ref.	
				mCurrentNowNextData = mUserSpecificNowNextData;
				mUserSpecificNowNextData = null;
				Log.d(TAG,"return already we have data  with same channel id "+uniqueChannelId);
				
			} else {//!indicates we cannot use mCurrent as a ref any more..we need a separate instance.both wants to exist independently.
			
				Log.d(TAG,"onPlayCompleted sep instance for mCurrent="+mCurrentNowNextData);
											
				mCurrentNowNextData = new EpgNowNextData(mContext);
				mCurrentNowNextData.startLooperThread();
				mCurrentNowNextData.register(this);
				mCurrentNowNextData.queryNowNextData(uniqueChannelId, mIsEpgBCEpg);
			}
		}
	}

	public void  queryNowNextData(int uniqueChannelId) {
	
		if(uniqueChannelId == 0 || uniqueChannelId == -1) return;
		
		synchronized (this) {
			Log.d(TAG,"queryNowNextData  request has come for ch:id "+uniqueChannelId  +" mIsInitialized "+mIsInitialized );
			if (!mIsInitialized) {
				userChannel = uniqueChannelId;
				Log.d(TAG,"return bcz the mIsInitialized "+mIsInitialized);
				return ;
			}
			userChannel = -1;
			if (mUserSpecificNowNextData == null) {
				mUserSpecificNowNextData = new EpgNowNextData(mContext);
				mUserSpecificNowNextData.startLooperThread();
				mUserSpecificNowNextData.register(this);
			}
			
			mUserSpecificNowNextData.queryNowNextData(uniqueChannelId, mIsEpgBCEpg);
		}
	}
	
	public int getChannelEpgDataStatus(int id) {
	
		synchronized (this) {
			if(id == (-1) || (mCurrentNowNextData != null && mCurrentNowNextData.getNowNextDataChannelId() == id)) {
				return mCurrentNowNextData.getNowNextDataStatus();
			} else if( mUserSpecificNowNextData !=  null && (mUserSpecificNowNextData.getNowNextDataChannelId() == id)){
				return mUserSpecificNowNextData.getNowNextDataStatus();
			} else {
				return EpgNowNextData.NO_DATA;
			}
		}
	}
	

	public String getNowEventName(int id) {
	
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowEventName();  
																
			} else if (mUserSpecificNowNextData != null &&  
								(mUserSpecificNowNextData.getNowNextDataChannelId() == id)) {
				return mUserSpecificNowNextData.getNowEventName(); 
																	
			}
		}
		return null;
	}

	public void registerListener(IEpgProviderNotify listener) {
	
		synchronized(this) {
			if(listener !=  null && !(mClients.contains(listener))) {
				mClients.add(listener);
				Log.d(TAG,"total no of epg cache listeners now after adding client"+mClients.size());
			}
		}
	}

	public void unregisterListener(IEpgProviderNotify listener) {
		synchronized(this) {
			if(listener !=  null && (mClients.contains(listener))) {
				mClients.remove(listener);
				Log.d(TAG,"total no of epg cache listeners now after removing client"+mClients.size());
			}
		}
	}
	
	public String getNextEventName(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextEventName();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextEventName(); // it is ok
																	
			}
		}
		return null;
	}

	public int getNowEventId(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowEventId();  
															
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowEventId();  
																	
			}
		}
		return -1;
	}

	public int getNextEventId(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextEventId();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextEventId();  
																	
			}
		}
		return -1;
	}

	public int getNowPresetId(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowPresetId();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowPresetId();  
																	
			}
		}
		return -1;
	}

	public int getNextPresetId(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextPresetId();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextPresetId(); // it is ok
																	
			}
		}
		return -1;
	}

	public int getNowVersion(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowVersion();  
															
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowVersion();  
																	
			}
		}
		return -1;
	}

	public int getNextVersion(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextVersion();  
																
			} else if (mUserSpecificNowNextData != null &&
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextVersion();  
																	
			}
		}
		return -1;
	}

	public int getNowStartTime(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowStartTime();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowStartTime(); // it is ok
																	
			}
		}
		return -1;
	}

	public int getNextStartTime(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextStartTime();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextStartTime(); 
																	
			}
		}
		return -1;
	}

	public int getNowEndTime(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowEndTime();  
															
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowEndTime();  
																	
			}
		}
		return -1;
	}

	public int getNextEndTime(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextEndTime();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextEndTime();  
																	
			}
		}
		return -1;
	}

	public String getNowShortInfo(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowShortInfo();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowShortInfo(); 
																	
			}
		}
		return null;
	}

	public String getNextShortInfo(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextShortInfo();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextShortInfo(); // it is ok
																	
			}
		}
		return null;
	}

	public String getNowExtendedInfo(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowExtendedInfo();  
																	
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowExtendedInfo(); // it is
																		
			}
		}
		return null;
	}

	public String getNextExtendedInfo(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextExtendedInfo();  
																	
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextExtendedInfo(); // it is
																		
			}
		}
		return null;
	}

	public String getNowLanguageid(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowLanguageid();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowLanguageid(); // it is ok
																	
			}
		}
		return null;
	}

	public String getNextLanguageid(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextLanguageid();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextLanguageid(); // it is ok
																		
			}
		}
		return null;
	}

	public int getNowTargetIndex(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowTargetIndex();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowTargetIndex(); // it is ok
																		
			}
		}
		return -1;
	}

	public int getNextTargetIndex(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextTargetIndex();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextTargetIndex(); 
																		
			}
		}
		return -1;
	}

	public int getNowGenre(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowGenre();  
															
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowGenre();  
																
			}
		}
		return -1;
	}

	public int getNextGenre(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextGenre(); 
														
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextGenre();  
																
			}
		}
		return -1;
	}

	public boolean getNowScrambledStatus(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowScrambledStatus(); 
																	
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowScrambledStatus(); 
																			
			}
		}
		return false;
	}

	public boolean getNextScrambledStatus(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextScrambledStatus();
																		
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextScrambledStatus(); 
																			
			}
		}
		return false;
	}

	public int getNowRating(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowRating();
															
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowRating();  
																
			}
		}
		return -1;
	}

	public int getNextRating(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextRating();  
															
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextRating();  
																	
			}
		}
		return -1;
	}

	public String getNowGuidanceinfo(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowGuidanceinfo();  
																	
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowGuidanceinfo(); 
																		
			}
		}
		return null;
	}

	public String getNextGuidanceinfo(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextGuidanceinfo();  
																	
			} else if (mUserSpecificNowNextData != null &&
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextGuidanceinfo(); 
																		
			}
		}
		return null;
	}

	public int getNowLinkType(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNowLinkType();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNowLinkType();  
																	
			}
		}
		return -1;
	}

	public int getNextLinkType(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getNextLinkType();  
																
			} else if (mUserSpecificNowNextData != null && 
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getNextLinkType();
																	
			}
		}
		return -1;
	}

	public int getHeatMap(int id) {
		synchronized (this) {
			if ((id == -1)
					|| ((mCurrentNowNextData != null) && (mCurrentNowNextData
							.getNowNextDataChannelId() == id))) {
				return mCurrentNowNextData.getHeatMap();  
															
			} else if (mUserSpecificNowNextData != null &&
								mUserSpecificNowNextData.getNowNextDataChannelId() == id) {
				return mUserSpecificNowNextData.getHeatMap();  
																
			}
		}
		return -1;
	}

	public int getCurrentChannelId(int id) {
	
		synchronized (this) {
		
			if (mCurrentNowNextData != null) {
				return mCurrentNowNextData.getNowNextDataChannelId(); 
																		
			} else if (mUserSpecificNowNextData != null ) {
				return mUserSpecificNowNextData.getNowNextDataChannelId();  
			}
		}
		return -1;
	}
	
	class ITVSettingsManagerCallBack extends ITvSettingsManager.ITvSettingsManagerNotify {
		public void OnUpdate(int property){
			// TODO Auto-generated method stub
			int value=ITvSettingsManager.Instance.getInterface().getInt(property, 0, 0);
			Log.d(TAG, "Update in the IP/BC epg status property - " + property
					+ "; Value - " + value +" mNettvService "+mNettvService);
			//AG:GT:TVJAR Porting 
			//GtvManager.getInstance(mContext).onEpgSourceChanged();
			if(mNettvService == null ) {
				connectService();
			} else {
				evaluateEPG();
			}
		}
	}
}



