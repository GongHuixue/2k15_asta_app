package org.droidtv.tunerservice.channelfilter;

import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.provider.IFavoriteContract;

import android.content.Context;
import android.database.ContentObserver;
import android.media.tv.TvContract;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;

public class DatabaseObserver extends ContentObserver{

	private static final String TAG = DatabaseObserver.class.getSimpleName();
	private ITvSettingsManager mGlobalSetting=null;
	private Context mContext;
	private Uri CONTENT_URI = TvContract.Channels.CONTENT_URI;
	private Uri FAV_CONTENT_URI = IFavoriteContract.IFavoriteList.CONTENT_URI;
	private static int mTCVersion = 0;
	private static int mSatVersion = 0;
	public boolean isUpdateCursorNeeded = false;
	private int [] property;
	private final int PROPMAX = 2;
	
	private ITVSettingsManagerCallBack PStorageBinder=null;

	
	public DatabaseObserver(Context context, Handler handler) {
		super(handler);
		Log.d(TAG, "DatabaseObserver cunstructor");
		mContext = context;
		initDatabaseObserver();
		RegisterTvSettingsManager();
		RegisterDbObserver();
	}
	
	public void RegisterDbObserver() {
		if(mContext != null){
			mContext.getContentResolver().registerContentObserver(FAV_CONTENT_URI, true, this);
			Log.d(TAG, "RegisterDbObserver success " +FAV_CONTENT_URI);
		}	
	}
	
	public void UnRegisterDbObserver() {
		if(mContext != null){
			Log.d(TAG, "UnRegisterDbObserver success");
			mContext.getContentResolver().unregisterContentObserver(this);
		}	
	}
	
	private void initDatabaseObserver() 
	{
		mGlobalSetting = ITvSettingsManager.Instance.getInterface();
		mTCVersion = mGlobalSetting.getInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, 0);
		mSatVersion = mGlobalSetting.getInt(TvSettingsConstants.INSTSETTINGSSATCHANNELTABLEVERSION, 0, 0);
	}

	public void RegisterTvSettingsManager()
    {
            property = new int [PROPMAX];
            property[0] = TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION;
            property[1] = TvSettingsConstants.INSTSETTINGSSATCHANNELTABLEVERSION;
            
            PStorageBinder = this.new ITVSettingsManagerCallBack(); 
            mGlobalSetting.SetCallBacks(PStorageBinder, property);
    }
	
	@Override
	public void onChange(boolean selfChange, Uri uri) {
		super.onChange(selfChange, uri);
		Log.d(TAG, "onChange selfChange " + selfChange + " uri " + uri);
		if(ChannelFilter.getChannelFilterInstance() != null){
			ChannelFilter.getChannelFilterInstance().UpdateCursor();
		}
	}

	@Override
	public void onChange(boolean selfChange) {
		super.onChange(selfChange);
		Log.d(TAG, "onChange selfChange " + selfChange);
		if(ChannelFilter.getChannelFilterInstance() != null){
			ChannelFilter.getChannelFilterInstance().UpdateCursor();
		}
	}

	class ITVSettingsManagerCallBack extends ITvSettingsManager.ITvSettingsManagerNotify {
		public void OnUpdate(int property) {
			int value=ITvSettingsManager.Instance.getInterface().getInt(property, 0, 0);
			Log.d(TAG, "Notification from global setting received  " + property + " Value = " + value);
        	if(ChannelFilter.getChannelFilterInstance() != null){ 
        		if(isVersionChanged(property, value))
        		{
        			ChannelFilter.getChannelFilterInstance().UpdateCursor();
        		}
        	}else{
        		Log.d(TAG, "OnUpdate - ChannelFilter.getChannelFilterInstance() returned null");
        	}
		}

		private boolean isVersionChanged(int property, int value) {
			boolean changed = false;
			switch(property){
			case TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION:
				Log.d(TAG, "INSTSETTINGSTCCHANNELTABLEVERSION " + value + " mTCVersion " +mTCVersion);
				if(value  > mTCVersion ){
					changed = true;
					mTCVersion = value;
				}
				break;
			case TvSettingsConstants.INSTSETTINGSSATCHANNELTABLEVERSION:
				Log.d(TAG, "INSTSETTINGSSATCHANNELTABLEVERSION " + value + " mSatVersion " +mSatVersion);
				if(value  > mSatVersion ){
					changed = true;
					mSatVersion = value;
				}
				break;
			default:
				Log.d(TAG, "isVersionChanged unknown property " + property);
				break;
			}
			Log.d(TAG, "isVersionChanged returns isChanged " + changed);
			return changed;
		}
	}

}