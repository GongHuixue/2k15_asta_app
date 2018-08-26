package org.droidtv.tunerservice.iapp;

import org.droidtv.tunerservice.PlayTvDiversity;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager.ITvSettingsManagerNotify;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.media.BcstConstants;
import org.droidtv.tunerservice.interfaces.IAppManagerTunerCallBacks;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tunerservice.iapp.interfaces.IAppListener;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.util.TvMediumHelper;
import android.content.Context;
import android.util.Log;
import android.view.Surface;
import android.net.Uri;
import android.os.Handler;
import android.os.Looper;
import android.media.tv.TvContract;

import java.util.Map;

public class MainIAppManager{

	public static final int ID_MHEG 	= 0;
	public static final int ID_MHP 		= 1;
	public static final int ID_HBBTV 	= 2;	

	public static final String ACTION_MHEG 	 = "org.droidtv.action.ACTION_MHEG";
	public static final String ACTION_MHP	 = "org.droidtv.action.ACTION_MHP";
	public static final String ACTION_HBBTV  = "org.droidtv.hbbtv.InteractiveService";
	
	private static final int INVALID_COUNTRY 	= 1000;
	private int InstalledCountryCode = INVALID_COUNTRY;
	private Context mContext = null;
	private IAppManager mIAppManager1 = null;
	private IAppManager mIAppManager2 = null;
	private static String TAG = "MainIAppManager";
	private String mAppReference = null;
	private int mUpdatedProperty = 0;
	private Handler mHandler = null;
	private OverlayManager moverlaymanager = null;
	private boolean startMHEG = false;
	
	public MainIAppManager(Context mcontext){
		Log.d(TAG,"MainIAppManager constructor");
		mContext = mcontext;
		mHandler = new Handler(Looper.getMainLooper());
		onInstalledCountryChanged(getCountry());
		registerCountryChangedNotifications();
		registerPbsMhegChangeNotifications();
		registerPbsModeNotifications();                  		
		
		// for creating IAppManager
		mIAppManager1  = new IAppManager(ID_HBBTV,mContext,ACTION_HBBTV);
		mIAppManager1.setEnabled(true);
		if(PlayTvDiversity.isMHEGSupported()) {
			mIAppManager2  = new IAppManager(ID_MHEG,mContext,ACTION_MHEG);
			mIAppManager2.setEnabled(false);
		}
		setMainIAppListener();
	}

	private void setMainIAppListener() {
		Log.d(TAG,"setMainIAppListener");
		if(mIAppManager1!=null) {
			mIAppManager1.setMainIAppListener(new HbbTvListener());
		}

		if(mIAppManager2!= null){
			switch(InstalledCountryCode) {
				case TvSettingsDefinitions.InstallationCountryConstants.IRELAND:
				case TvSettingsDefinitions.InstallationCountryConstants.UK:
					if (!((getPbsMode() == TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON) 
							&& (getEnableMheg() == TvSettingsDefinitions.PbsEnableMheg.PBSMGR_ENABLE_MHEG_OFF))) {
						mIAppManager2.setEnabled(true);
						mIAppManager2.setMainIAppListener(new MhegListener());
					} else {
						mIAppManager2.setEnabled(false);
					}
					break;
				default:
					mIAppManager2.setEnabled(false);
					break;
			}
		}
	}                   		

	private int getCountry() {
		Log.d(TAG,"getCountry");
		return getSettingsManager().getInt(TvSettingsConstants.INSTALLATIONCOUNTRY,0,0);
	}
	
	private int getEnableMheg() {
		Log.d(TAG,"getEnableMheg");
		return getSettingsManager().getInt(TvSettingsConstants.PBSMGR_PROPERTY_ENABLE_MHEG,0,0);
	}
	
	private int getPbsMode() {
		Log.d(TAG,"getPbsMode");
		return getSettingsManager().getInt(TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE,0,0);
	}                   		
	
	private boolean isTerrestrialMedium(){
		Log.d(TAG,"isTerrestrialMedium");
		boolean lRet = false;

		int lMedium = TvMediumHelper.getCurrentChannelMediumType(mContext);
		if (lMedium == 0)
		{
				lRet = true;	
			}else{
			lRet = false;
		}
		
		Log.d(TAG,"isTerrestrialMedium return "+lRet);
		
		return lRet;

	}
	
	private ITvSettingsManager getSettingsManager(){
		return ITvSettingsManager.Instance.getInterface();
	}

	public void registerCountryChangedNotifications()
	{
		Log.d(TAG, "RegisterTvSettingsManager Called");
		final int PROPMAX = 1;
		int property[] = new int [PROPMAX];

		property[0] = TvSettingsConstants.INSTALLATIONCOUNTRY;

		ITvSettingsManagerNotify PStorageBinder = new ITvSettingsManagerNotify() {
			
			public void OnUpdate(int prop){
				mUpdatedProperty = prop;
				Log.d(TAG, "Notification From Global Setting Received  " + prop );
				mHandler.post(new Runnable(){
					public void run() {
						if(mUpdatedProperty == TvSettingsConstants.INSTALLATIONCOUNTRY) {
							int value = getSettingsManager().getInt(TvSettingsConstants.INSTALLATIONCOUNTRY,0,0);
							onInstalledCountryChanged(value);
						}
					}
				});	
			}
		};                                                        
		getSettingsManager().SetCallBacks(PStorageBinder, property);
	}

	public void onInstalledCountryChanged(int SelectedCountryCode) {
		Log.d(TAG,"In TIF Country Code is............ " + SelectedCountryCode );
		if(InstalledCountryCode!=SelectedCountryCode) {
			InstalledCountryCode = SelectedCountryCode;
			Log.d(TAG,"Country Changed mActiveId= " );
			setMainIAppListener();
		}
	}
	
	public void checkStartMhegStatus() {
		if (((InstalledCountryCode == TvSettingsDefinitions.InstallationCountryConstants.IRELAND) 
				|| (InstalledCountryCode == TvSettingsDefinitions.InstallationCountryConstants.UK )) 
				&& startMHEG) {
			if (!((getPbsMode() == TvSettingsDefinitions.PbsProfessionalModeConstants.PBSMGR_PROFESSIONAL_MODE_ON) 
					&& (getEnableMheg() == TvSettingsDefinitions.PbsEnableMheg.PBSMGR_ENABLE_MHEG_OFF))) {
				mIAppManager1.removeViews();
				mHandler.post(new Runnable(){
					public void run() {
						if(mIAppManager2 != null) {
							mIAppManager2.start();
						}
					}
				});	
			} else {
				mIAppManager2.removeViews();
				mHandler.post(new Runnable(){
					public void run() {
						if(mIAppManager1 != null) {
							mIAppManager1.start();
						}
					}
				});	
			}
		}
	}
	
	public void registerPbsMhegChangeNotifications() {
		Log.d(TAG, "RegisterTvSettingsManager Called");
		
		final int PROPMAX = 1;
		int property[] = new int [PROPMAX];
		property[0] = TvSettingsConstants.PBSMGR_PROPERTY_ENABLE_MHEG;

		ITvSettingsManagerNotify PBSMhegStorageBinder = new ITvSettingsManagerNotify() {
			
			public void OnUpdate(int prop){
				mUpdatedProperty = prop;
				Log.d(TAG, "Notification PbsMhegChange From Global Setting Received  " + prop );
				
				mHandler.post(new Runnable(){
					public void run() {
						if(mUpdatedProperty == TvSettingsConstants.PBSMGR_PROPERTY_ENABLE_MHEG) {
							setMainIAppListener();
							checkStartMhegStatus();
						}
					}
				});
			}
		};
		getSettingsManager().SetCallBacks(PBSMhegStorageBinder, property);
	}
	
	public void registerPbsModeNotifications() {
		Log.d(TAG, "RegisterTvSettingsManager Called");
		
		final int PROPMAX = 1;
		int property[] = new int [PROPMAX];
		property[0] = TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE;

		ITvSettingsManagerNotify PBSModeStorageBinder = new ITvSettingsManagerNotify() {
			
			public void OnUpdate(int prop){
				mUpdatedProperty = prop;
				Log.d(TAG, "Notification onPbsModeChanged From Global Setting Received  " + prop );
				
				mHandler.post(new Runnable(){
					public void run() {
						if(mUpdatedProperty == TvSettingsConstants.PBSMGR_PROPERTY_PROFESSIONAL_MODE) {
							setMainIAppListener();
							checkStartMhegStatus();
						}
					}
				});
			}
		};
		getSettingsManager().SetCallBacks(PBSModeStorageBinder, property);
	}
	
	public void onZapStatusChanged(int state,Map<String, String> headers, Uri uri) {
		Log.d(TAG,"onZapStatusChanged uri " + uri + " state " + state);
		boolean isPrivSelection = false;
		
		if (headers != null) {
			String privData = headers.get(TvHeaders.PRIV_DATA_COOKIE);
			if ((privData!=null) && (!privData.equals(TvHeaders.PRIV_DATA_CATCHUP_TUNE))) {
				isPrivSelection = true;
			} 
		}

		if((uri!=null) && (TvContract.isChannelUriForTunerInput(uri))&&(moverlaymanager!=null)) {
			if (!isPrivSelection) {
				switch(state) {
					case BcstConstants.STATE_PREPARE_START:
						mHandler.post(new Runnable(){
							public void run() {
								if(mIAppManager2!=null) {
									startMHEG = false;
									mIAppManager2.stop();
								}
							}
						});
					break;
					case BcstConstants.STATE_PREPARE_COMPLETE:
						if(mIAppManager2 != null){
							mHandler.post(new Runnable(){
								public void run() {				
									if(mIAppManager2!=null) {
										if(mIAppManager2.isStarted()){
											Log.d(TAG,"stopping mheg as seen started");
											startMHEG = false;
											mIAppManager2.stop();
										}	
									}
								}
							});															
						}
						mHandler.post(new Runnable(){
							public void run() {				
								if(mIAppManager1!=null) {
									mIAppManager1.setInteractiveListener();
									mIAppManager1.start();
								}
							}
						});	
					break;
				}
				mAppReference = null;
			}
		}else {
			mHandler.post(new Runnable(){
				public void run() {				
					if(mIAppManager1!=null) {
						mIAppManager1.stop();
					}
					if(mIAppManager2!=null) {
						startMHEG = false;
						mIAppManager2.stop();
					}
				}
			});
		}
	}
	
	public void setIAppManagerTunerCallBacksListener(IAppManagerTunerCallBacks listener) {
		Log.d(TAG,"setIAppManagerTunerCallBacksListener ");
		if(mIAppManager1 != null){
			mIAppManager1.setIAppManagerTunerCallBacksListener(listener);
		}
		if(mIAppManager2 != null){		
			mIAppManager2.setIAppManagerTunerCallBacksListener(listener);
		}
	}

	public class MhegListener implements IAppListener{

		public void onAppStarted(){
			Log.d(TAG,"onAppStarted MHEG...");
		}
		
		public void onAppExited(){
			Log.d(TAG,"onAppExited MHEG...");
			mHandler.post(new Runnable(){
				public void run() {				
					mIAppManager2.removeViews();
					if(mAppReference != null){
						Log.d(TAG,"Calling startApp to Hbbtv with url" + mAppReference);
						if(mIAppManager1!=null) {
							mIAppManager1.startApp(mAppReference);
						}
					}
				}
			});
		}
		
		public void invokeInteractiveApp(String Appreference){
			mAppReference = Appreference;
			Log.d(TAG,"invokeInteractiveApp MHEG..."+Appreference);
			mHandler.post(new Runnable() {				
				public void run() {
					if(mIAppManager2!=null) {
						startMHEG = false;
						mIAppManager2.stop();
					}
				}
			});
		}
	}

	public class HbbTvListener implements IAppListener{

		public void onAppStarted(){
			Log.d(TAG,"onAppStarted HBBTV...");
			if(mIAppManager2!=null) {
				startMHEG = false;
				mIAppManager2.removeViews();
				mIAppManager2.stop();
				Log.d(TAG,"onAppStarted HBBTV...");
				mIAppManager1.start();
			}
		}
		
		public void onAppExited(){
			Log.d(TAG,"onAppExited HBBTV...");
			startMHEG = true;
			if((mIAppManager2!=null) && (mIAppManager2.isEnabled())) {
				mIAppManager1.removeViews();
				mHandler.post(new Runnable(){
					public void run() {
						Log.d(TAG,"Exiting Hbbtv checking whether to start Mheg...");
						if(isTerrestrialMedium() && ((InstalledCountryCode == TvSettingsDefinitions.InstallationCountryConstants.IRELAND)||(InstalledCountryCode == TvSettingsDefinitions.InstallationCountryConstants.UK )) ){
							mIAppManager2.start();
						}else{
							Log.d(TAG,"Either Medium or Country is different Not starting Mheg...");
						}
					}
				});		
			}
		}
		
		public void invokeInteractiveApp(String Appreference){
			//Nothing to be done this call will not come from hbbtv	
		}

	}
	
	public void setOverlayManager(final OverlayManager overlaymgr) {
		Log.d(TAG,"Setting the overLayManager");
		moverlaymanager = overlaymgr;
		mHandler.post(new Runnable(){
			public void run() {
				if(mIAppManager1 != null){
					mIAppManager1.setOverlayManager(overlaymgr);
				}
				if((mIAppManager2 != null)){
					mIAppManager2.setOverlayManager(overlaymgr);
				}
			}
		});
	}	
	
	public void onSessionRelease(){
		Log.d(TAG,"Session Destroyed");
		if(mIAppManager1!= null) {
			mIAppManager1.onSessionRelease();
		}
		if(mIAppManager2!=null){
			mIAppManager2.onSessionRelease();
		}					
	}

	public void setAVSurface(Surface mSurface) {
		if(mIAppManager1!= null) {
			mIAppManager1.setAVSurface(mSurface);
		}
		if((mIAppManager2!=null)&&(mIAppManager2.isEnabled())){
			mIAppManager2.setAVSurface(mSurface);
		}
	}
}

