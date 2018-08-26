package org.droidtv.tunerservice.epgnownext;

import org.droidtv.tunerservice.channelfilter.ChannelConstants;
import org.droidtv.tv.provider.IEpgContract;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import android.content.Context;
import android.database.ContentObserver;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;
import android.database.DatabaseUtils;
import android.os.Looper;
import org.droidtv.tunerservice.epgnownext.ScheduleData;
import org.droidtv.tv.smarttv.provider.IIpEpgContract;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;

public class EpgNowNextData implements IEpgNowNextData {

	private static final String TAG = "EpgNowNextData";
	public static final int NO_DATA = 0;
	public static final int DATA_PRESENT = 0x100;
	public static final int EXTRA_DATA_PRESENT = 0x200;

	private Context mClientContext = null;
	private IEpgProviderNotify mProviderListener = null;
	private boolean mBCEPGMode = true;

	private NowNextDataStatus mDataStatus = new NowNextDataStatus();
	private ITvSettingsManager globalSetting = ITvSettingsManager.Instance.getInterface();
	private BCEPGDataObserver mBCEpgDataObserver = null;
	private IPEPGDataObserver mIPEpgDataObserver = null;
	private static LooperThread looperThread = null;

	private String[] ipProjection = null;
	//private static final int IP_COLINDEX_NOW_HEATMAP = 0;
	private static final int IP_COLINDEX_NOW_STARTTIME = 0;
	private static final int IP_COLINDEX_NOW_ENDTIME = 1;
	private static final int IP_COLINDEX_NOW_TITLE = 2;
	private static final int IP_COLINDEX_NOW_TEXT = 3;
	private static final int IP_COLINDEX_NOW_EVENTID = 4;

	//private static final int IP_COLINDEX_NEXT_HEATMAP = 100;
	private static final int IP_COLINDEX_NEXT_STARTTIME = 100;
	private static final int IP_COLINDEX_NEXT_ENDTIME = 101;
	private static final int IP_COLINDEX_NEXT_TITLE = 102;
	private static final int IP_COLINDEX_NEXT_TEXT = 103;
	private static final int IP_COLINDEX_NEXT_EVENTID = 104;

	private Uri mCurrentUri = null;
	private static Object SYNC = new Object();

	public EpgNowNextData(Context clientActivity) {

		mClientContext = clientActivity;
		ipProjection = new String[] {IIpEpgContract.C_UTC_START_TIME,
					IIpEpgContract.C_UTC_END_TIME, IIpEpgContract.C_TITLE, IIpEpgContract.C_TEXT, IIpEpgContract.C_PROGRAM_ID};

		synchronized(SYNC) {
			if(looperThread == null) {
				looperThread = new LooperThread();
			}
		}
	}
		
	public void startLooperThread(){
			synchronized(looperThread) {
				while(!looperThread.getLooperThreadHandlerStatus()) {
					try {
						looperThread.start();
						looperThread.wait();
					} catch (InterruptedException e) {
						Log.d(TAG,"EpgNowNextData:InterruptedException");
					}
				}
			}
	}

	private void registerUriNotification(int uniqueChannelId , Uri clientUri) {

		if( mBCEpgDataObserver == null) {
				mBCEpgDataObserver = new BCEPGDataObserver(new Handler());
		}

		if(mIPEpgDataObserver == null ) {
			mIPEpgDataObserver = new IPEPGDataObserver(new Handler());
		}

		((Context)mClientContext).getContentResolver().unregisterContentObserver(mBCEpgDataObserver);
		((Context)mClientContext).getContentResolver().unregisterContentObserver(mIPEpgDataObserver);

		//Log.d(TAG,"registering for notification uri "+clientUri +" channel id "+uniqueChannelId +
		//		" mBCEpgDataObserver "+mBCEpgDataObserver + " mIPEpgDataObserver="+mIPEpgDataObserver);

		if(mBCEPGMode) {
			((Context)mClientContext).getContentResolver().registerContentObserver(clientUri, false, mBCEpgDataObserver);
		} else {
			((Context)mClientContext).getContentResolver().registerContentObserver(IIpEpgContract.CONTENT_URI_PROGRAM_DATA,
				false, mIPEpgDataObserver);
		}
	}

	private Uri getBCEpgUri(int uniqueChannelId, boolean nownext) {

		Uri uri;
		Medium medium = getMedium(uniqueChannelId);

		switch(medium) {

		case MEDIUM_TERRESTRIAL:
			if(nownext) {
				uri = IEpgContract.CONTENT_URI_AntennaNowNextEventData;
			} else {
				uri = IEpgContract.CONTENT_URI_AntennaScheduleData;
			}
			break;
		case MEDIUM_CABLE:
			if(nownext) {
				uri = IEpgContract.CONTENT_URI_CableNowNextEventData;
			} else {
				uri = IEpgContract.CONTENT_URI_CableScheduleData;
			}
			break;
		case MEDIUM_SATELLITE:
			if(nownext) {
				uri = IEpgContract.CONTENT_URI_SatelliteNowNextEventData;
			} else {
				uri = IEpgContract.CONTENT_URI_SatelliteScheduleData;
			}
			break;
		default:
			uri = null;
			break;
		}
		return uri;
	}

	private Medium getMedium(int uniqueChannelId) {
		String[] projection = new String[] {Channels.COLUMN_VERSION_NUMBER};
		Medium  currentMedium = Medium.MEDIUM_INVALID;
		Cursor c=null;
		try{
			Uri uri = TvContract.Channels.CONTENT_URI;
			String selection = Channels._ID + "=?";
			String [] selectionArgs = new String [] { Integer.toString(uniqueChannelId)};
			c = mClientContext.getContentResolver().query(uri, projection, selection, selectionArgs, null);
			if((c != null) && (c.getCount()>0)){
				c.moveToFirst();
				int version = c.getInt(c.getColumnIndex(Channels.COLUMN_VERSION_NUMBER));
				if(version == ChannelConstants.VERSION_DVBT){
					currentMedium = Medium.MEDIUM_TERRESTRIAL;
				}else if(version == ChannelConstants.VERSION_DVBC){
					currentMedium = Medium.MEDIUM_CABLE;
				}else if((version == ChannelConstants.VERSION_DVBS1) || (version == ChannelConstants.VERSION_DVBS2) 
						|| (version == ChannelConstants.VERSION_DVBS3) || (version == ChannelConstants.VERSION_DVBS4)){
					currentMedium = Medium.MEDIUM_SATELLITE;
				}
				
			}
		}catch(Exception e){
			Log.d(TAG,"Exception in getMedium():"+e);
		}
		finally
		{
			if(c!=null)
			{
				c.close();
				c = null;
			}
		}
	//	Log.d(TAG, "getMedium medium " + currentMedium);
		return currentMedium;
	}
	
	public void queryNowNextData(int uniqueChannelID,  boolean isbcEpg) {

		if( uniqueChannelID == 0)
		   return;

		Uri epgUri = getBCEpgUri(uniqueChannelID, true);
		if(epgUri != null) {
			if(isbcEpg != mBCEPGMode ||
						mCurrentUri == null ||
						epgUri.toString().equalsIgnoreCase(mCurrentUri.toString()) == false) {
	
				mCurrentUri = epgUri;
				//Log.d(TAG," call register for notification uniqueChannelID="+uniqueChannelID +" isbcEpg = "+isbcEpg +
						//" mBCEPGMode="+mBCEPGMode + " mCurrentUri="+mCurrentUri);
				mBCEPGMode = isbcEpg;
				mCurrentUri = epgUri;
				registerUriNotification(uniqueChannelID, mCurrentUri);
			}
			mCurrentUri = epgUri;
			query(uniqueChannelID);
		}
	}

	public ScheduleData queryCurrentScheduleData(int uniqueChannelID) {

		ScheduleData retval = null;

		String[] projection = {IEpgContract.C_SCHEDULE_EVENTID, IEpgContract.C_SCHEDULE_EVENTNAME, IEpgContract.C_SCHEDULE_VERSION,
								IEpgContract.C_SCHEDULE_STARTTIME, IEpgContract.C_SCHEDULE_ENDTIME, IEpgContract.C_SCHEDULE_SHORTINFO};

		String selection = IEpgContract.C_SCHEDULE_PRESETID + " = ? AND " + IEpgContract.C_SCHEDULE_ENDTIME + " > ? AND " + IEpgContract.C_SCHEDULE_STARTTIME + " <= ?";

		String[] selectionArgs = {String.valueOf(uniqueChannelID), String.valueOf(System.currentTimeMillis()), String.valueOf(System.currentTimeMillis())};

		String orderBy = IEpgContract.C_SCHEDULE_STARTTIME + " LIMIT 1";

		Uri uri = getBCEpgUri(uniqueChannelID, false);
		if(uri != null) {
			Cursor c =null;
			try
			{
			   c= ((Context)mClientContext).getContentResolver().query(uri, projection, selection, selectionArgs, null);
	
			   if( (c != null) && (c.getCount() > 0) && (c.moveToFirst() ) ) {
				  retval = new ScheduleData();
	
				  retval.eventid = c.getInt(0);
				  retval.name = c.getString(1);
				  retval.eitversion = c.getInt(2);
				  retval.starttime = c.getLong(3);
				  retval.duration = c.getLong(4) - retval.starttime;
				  retval.shortinfo = c.getString(5);
			    }
			}
			finally
			{
			   if(c != null) {
				  c.close();
				c=null;  
			   }
			}
		}
		return retval;
	}

	private void query(final int uniqueChannelID) {

		if (mBCEPGMode) {
			looperThread.getLooperHandler().removeCallbacks(mBcEpgRunnable);

			if(uniqueChannelID != mDataStatus.getChannelId()) {
				mDataStatus.setChannelId(uniqueChannelID);
			}

			looperThread.getLooperHandler().post(mBcEpgRunnable);

		} else {

			//Log.d(TAG, "Starting the Loader Manager Query for IP-EPG uniqueChannelID "+uniqueChannelID +" mDataStatus.getChannelId() "+mDataStatus.getChannelId() );
			looperThread.getLooperHandler().removeCallbacks(mIpEpgRunnable);

			if(uniqueChannelID != mDataStatus.getChannelId()) {
				mDataStatus.setChannelId(uniqueChannelID);
			}

			looperThread.getLooperHandler().post(mIpEpgRunnable);
		}
	}

	@Override
	public String getNowEventName() {

		if(mBCEPGMode) {
			return mDataStatus.getStringData(IEpgContract.NOWNEXTDATA_NOW_EVENTNAMEID);
		} else {
			return mDataStatus.getStringData(IP_COLINDEX_NOW_TITLE);
		}
	}

	@Override
	public String getNextEventName() {

		if(mBCEPGMode) {
			return mDataStatus.getStringData(IEpgContract.NOWNEXTDATA_NEXT_EVENTNAMEID);
		} else {
			return mDataStatus.getStringData(IP_COLINDEX_NEXT_TITLE);
		}
	}

	@Override
	public int getNowEventId() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_EVENTID);
		} else {
			return mDataStatus.getIntData(IP_COLINDEX_NOW_EVENTID);
		}
	}

	@Override
	public int getNextEventId() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_EVENTID);
		} else {
			return mDataStatus.getIntData(IP_COLINDEX_NEXT_EVENTID);
		}
	}

	@Override
	public int getNowPresetId() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_PRESETID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNextPresetId() {

		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_PRESETID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNowVersion() {

		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_VERSIONID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNextVersion() {

		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_VERSIONID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNowStartTime() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_STARTTIMEID);
		} else {
			return mDataStatus.getIntData( IP_COLINDEX_NOW_STARTTIME);
		}
	}

	@Override
	public int getNextStartTime() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_STARTTIMEID);
		} else {
			return mDataStatus.getIntData( IP_COLINDEX_NEXT_STARTTIME);
		}
	}

	@Override
	public int getNowEndTime() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_ENDTIMEID);
		} else {
			return mDataStatus.getIntData(IP_COLINDEX_NOW_ENDTIME);
		}
	}

	@Override
	public int getNextEndTime() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_ENDTIMEID);
		} else {
			return mDataStatus.getIntData(IP_COLINDEX_NEXT_ENDTIME);
		}
	}

	@Override
	public String getNowShortInfo() {
		if(mBCEPGMode) {
			return mDataStatus.getStringData(IEpgContract.NOWNEXTDATA_NOW_SHORTINFOID);
		} else {
			return mDataStatus.getStringData(IP_COLINDEX_NOW_TEXT);
		}
	}

	@Override
	public String getNextShortInfo() {
		if(mBCEPGMode) {
			return mDataStatus.getStringData(IEpgContract.NOWNEXTDATA_NEXT_SHORTINFOID);
		} else {
			return mDataStatus.getStringData(IP_COLINDEX_NEXT_TEXT);
		}
	}

	@Override
	public String getNowExtendedInfo() {
		if(mBCEPGMode) {
			return mDataStatus.getStringData(IEpgContract.NOWNEXTDATA_NOW_EXTENDEDINFOID);
		} else {
			return null;
		}
	}

	@Override
	public String getNextExtendedInfo() {

		if(mBCEPGMode) {
			return mDataStatus.getStringData(IEpgContract.NOWNEXTDATA_NEXT_EXTENDEDINFOID);
		} else {
			return null;
		}
	}

	@Override
	public String getNowLanguageid() {
		return null;
	}

	@Override
	public String getNextLanguageid() {

		return null;
	}

	@Override
	public int getNowTargetIndex() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_TARGETINDEXID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNextTargetIndex() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_TARGETINDEXID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNowGenre() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_GENREID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNextGenre() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_GENREID);
		} else {
			return -1;
		}
	}

	@Override
	public boolean getNowScrambledStatus() {
		if(mBCEPGMode) {
			return mDataStatus.getBooleanData(IEpgContract.NOWNEXTDATA_NOW_SCRAMBLEDID);
		} else {
			return false;
		}
	}

	@Override
	public boolean getNextScrambledStatus() {
		if(mBCEPGMode) {
			return mDataStatus.getBooleanData(IEpgContract.NOWNEXTDATA_NEXT_SCRAMBLEDID);
		} else {
			return false;
		}
	}

	@Override
	public int getNowRating() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_RATINGID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNextRating() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_RATINGID);
		} else {
			return -1;
		}
	}

	@Override
	public String getNowGuidanceinfo() {
		if(mBCEPGMode) {
			return mDataStatus.getStringData(IEpgContract.NOWNEXTDATA_NOW_GUIDANCEINFOID);
		} else {
			return null;
		}
	}

	@Override
	public String getNextGuidanceinfo() {
		if(mBCEPGMode) {
			return mDataStatus.getStringData(IEpgContract.NOWNEXTDATA_NEXT_GUIDANCEINFOID);
		} else {
			return null;
		}
	}

	@Override
	public int getNowLinkType() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NOW_LINKTYPEID);
		} else {
			return -1;
		}
	}

	@Override
	public int getNextLinkType() {
		if(mBCEPGMode) {
			return mDataStatus.getIntData(IEpgContract.NOWNEXTDATA_NEXT_LINKTYPEID);
		} else {
			return -1;
		}

	}

	@Override
	public int getHeatMap() {
		return mDataStatus.getHeatMapData();
	}

	public int getNowNextDataChannelId() {
		return mDataStatus.getChannelId();
	}

	public int getNowNextDataStatus() {
		return mDataStatus.getStatus();
	}

	private void onEpgDataChanged(int presetid) {

		//Log.d(TAG, "onEpgDataChanged Epg mBCEPG "+mBCEPGMode);

		if( (mDataStatus.getChannelId() == presetid) && (mProviderListener != null) ) {
			mProviderListener.onEpgDataChanged(presetid);
		} else {
			//Log.d(TAG, "block notification since " + mDataStatus.getChannelId() + " presetid " + presetid);
		}
	}

	public void register(IEpgProviderNotify listener) {
		mProviderListener = listener;
	}

	public void releaseContext() {

		//Log.d(TAG,"releasing the context");

		if(mBCEpgDataObserver != null) {
			((Context)mClientContext).getContentResolver().unregisterContentObserver(mBCEpgDataObserver);
		}

		if(mIPEpgDataObserver != null) {
			((Context)mClientContext).getContentResolver().unregisterContentObserver(mIPEpgDataObserver);
		}

		mProviderListener = null;
		looperThread.release();

		//Log.d(TAG,"released");
		//mClientContext = null;
	}

	private class LooperThread extends Thread {

		private Handler mHandler;
		private boolean handlerCreated = false;

		public void run() {

			synchronized (this)
			{
				Looper.prepare();
				mHandler = new Handler();
				handlerCreated = true;
				//Log.d(TAG,"Looper thread handler created..");
				notify();
			}
			Looper.loop();
		};

		public boolean getLooperThreadHandlerStatus(){
			return handlerCreated;
		}

		public Handler getLooperHandler() {

			return mHandler;
		}

		public void release() {
			mHandler.removeCallbacks(mBcEpgRunnable);
			mHandler.removeCallbacks(mIpEpgRunnable);
			//Log.d(TAG,"released threadLooper");
		}
	}

	private Runnable mIpEpgRunnable =  new Runnable() {

		@Override
		public void run() {
			final int channel = mDataStatus.getChannelId();
			int currentTime = (int)(System.currentTimeMillis() / 1000);
			//Log.d(TAG,"runnable for ipEpg channel id is "+channel +" current time is"+currentTime);
			//String selection = IIpEpgContract.C_CCID + " = " +  channel +  " AND " + IIpEpgContract.C_UTC_END_TIME + ">= " +currentTime;
			String selection = IIpEpgContract.C_CCID + " =? " +  " AND " + IIpEpgContract.C_UTC_END_TIME + ">=? ";
			String[] selectionArgs = {String.valueOf(channel),String.valueOf(currentTime)};
			String orderBy = IIpEpgContract.C_UTC_END_TIME + " LIMIT 2";
			//synchronized(this) {
				Cursor c = ((Context)mClientContext).getContentResolver().query(IIpEpgContract.CONTENT_URI_PROGRAM_DATA,
					ipProjection, selection, selectionArgs, orderBy);
				if((c != null) && (c.getCount() > 0)){
				    c.moveToFirst();
   					long now_start = (long) (c.getInt( IP_COLINDEX_NOW_STARTTIME));
   					long now_end = (long) (c.getInt( IP_COLINDEX_NOW_ENDTIME));
   					long current_time = (System.currentTimeMillis() /1000);
                    if((now_start <= current_time) && (current_time < now_end )){
                    	c.moveToFirst();
                    	mDataStatus.ipDataReady(channel, c);
                    } else{
                    	//Log.d(TAG, "dropping cursor for IP EPG as it is not now");
                    	mDataStatus.ipDataReady(channel, null); //DataStatus closes the cursor..
                		if(mCurrentUri!= null) {
                    		c = ((Context)mClientContext).getContentResolver().query(mCurrentUri, null,
                    				IEpgContract.GET_NOWNEXTDATA, new String[] { String.valueOf(channel) },null);
                			registerUriNotification(channel, mCurrentUri);
                			mDataStatus.bcDataReady(channel, c);
                    	}
            			mBCEPGMode = true;
                    }
				} else {
					//Log.d(TAG, "ip epg cursor null ");
					c = ((Context)mClientContext).getContentResolver().query(mCurrentUri, null,
                        					IEpgContract.GET_NOWNEXTDATA, new String[] { String.valueOf(channel) },null);
					mBCEPGMode = true;
					registerUriNotification(channel, mCurrentUri);
					mDataStatus.bcDataReady(channel, c);
				}
			//}
			onEpgDataChanged(channel);
		}
	};

	private Runnable mBcEpgRunnable =  new Runnable() {

		@Override
		public void run() {

			final int channel = mDataStatus.getChannelId();
			//synchronized(this) {
				Cursor c = ((Context)mClientContext).getContentResolver().query(mCurrentUri, null,
					IEpgContract.GET_NOWNEXTDATA, new String[] { String.valueOf(channel) },null);
				mDataStatus.bcDataReady(channel, c);
			//}
			onEpgDataChanged(channel);
		}
	};

	public class BCEPGDataObserver extends ContentObserver {

		public BCEPGDataObserver(Handler handler) {
			super(handler);
		}

		public void onChange(boolean selfChange, Uri uri) {
			super.onChange(selfChange, uri);
			//Log.d(TAG, "onChange BCEPGDataObserver got triggered this="+this);
			mDataStatus.bcDataChange();
		}
	}

	public class IPEPGDataObserver extends ContentObserver {

		public IPEPGDataObserver(Handler handler) {
			super(handler);
		}

		public void onChange(boolean selfChange, Uri uri) {
			super.onChange(selfChange, uri);
			//Log.d(TAG, "onChange IPEPGDataObserver got triggered this="+this);
			mDataStatus.ipDataChange();
		}
	}

	class NowNextDataStatus {

		private int status;
		private int uniqueChannelId = 0;
		private Cursor mBCEPGCursor = null;
		private Cursor mIPEPGCursor = null;
		private boolean inNowForIP = true;

		public NowNextDataStatus() {
			status = EpgNowNextData.NO_DATA;
		}

		public void setChannelId(int id) {
			synchronized(this) {
				uniqueChannelId = id;
				status = EpgNowNextData.NO_DATA;
				if(mBCEPGCursor != null) {
					mBCEPGCursor.close();
				}
			}
		}

		public int 	getChannelId() {
			return uniqueChannelId;
		}

		public int getStatus() {
			return status;
		}

		public void bcDataReady(int presetid, Cursor c) {
			synchronized(this) {
				if(uniqueChannelId == presetid) {
					if(null != mBCEPGCursor) {
						mBCEPGCursor.close();
					}
					if( (c != null) && (c.getCount() > 0) ) {
						status |= EpgNowNextData.DATA_PRESENT;
						c.moveToFirst();
						//Log.d(TAG, "bc data ready " + c.getCount());
						mBCEPGCursor = c;
					} else {
						//Log.d(TAG, "bc No data ");
						status = EpgNowNextData.NO_DATA;
						mBCEPGCursor = null;
						if(c != null) {
							c.close();
							c=null;
						}
					}
				} else {
					//Log.w(TAG, "not matching presetid " + uniqueChannelId + presetid);
					if(c != null)
					   c.close();
				       c=null;
				}
			}
		}

		public void ipDataReady(int presetid, Cursor c) {
			synchronized(this) {
				if(uniqueChannelId == presetid) {
					if(null != mIPEPGCursor) {
						mIPEPGCursor.close();
					}
					if(mBCEPGMode) {
						if( (c != null) && (c.getCount() > 1) ) {
							status |= EpgNowNextData.EXTRA_DATA_PRESENT;
							c.moveToFirst();
							inNowForIP = true;
							//Log.d(TAG, "ip extra data ready " + c.getCount());
							mIPEPGCursor = c;
						} else {
							//Log.w(TAG, "count unexpected for ip ");
							status &= (~EpgNowNextData.EXTRA_DATA_PRESENT);
							mIPEPGCursor = null;
							if(c != null) {
								c.close();
								c=null;
							}
						}
					} else {
						if( (c != null) && (c.getCount() > 1) ) {
							status = EpgNowNextData.DATA_PRESENT;
							c.moveToFirst();
							inNowForIP = true;
							//Log.d(TAG, "ip data ready " + c.getCount());
							mIPEPGCursor = c;
						} else {
							//Log.w(TAG, "count unexpected for ip " );
							status = EpgNowNextData.NO_DATA;
							mIPEPGCursor = null;
							if(c != null) {
								c.close();
								c=null;
							}
						}
					}
				} else {
					//Log.w(TAG, "not matching presetid for ip data " + uniqueChannelId + presetid);
					if(c != null)
						c.close();
				}
			}
		}

		public void bcDataChange() {
			synchronized (this) {
				queryNowNextData(uniqueChannelId, mBCEPGMode);
			}
		}

		public void ipDataChange() {
			synchronized (this) {
				queryNowNextData(uniqueChannelId, mBCEPGMode);
			}
		}

		private void moveIpToNow() {
			if(!inNowForIP) {
				mIPEPGCursor.moveToFirst();
				inNowForIP = true;
			}
		}

		private void moveIpToNext() {
			if(inNowForIP) {
				mIPEPGCursor.moveToNext();
				inNowForIP = false;
			}
		}

		public int getIntData(int colIndex) {
			synchronized(this) {
				if(mBCEPGMode) {
					if( (status & EpgNowNextData.DATA_PRESENT) > 0) {
						try {
							return mBCEPGCursor.getInt(colIndex) ;
						}catch(Exception e) {
							//Log.e(TAG, "exception to get bc int " + e.getLocalizedMessage());
						}
					} else {
						//Log.d(TAG, "data not present yet " + status);
					}
				} else {
					if( (status & EpgNowNextData.DATA_PRESENT) > 0) {
						try {
							switch(colIndex) {
							case IP_COLINDEX_NOW_STARTTIME:
								moveIpToNow();
								return mIPEPGCursor.getInt(IP_COLINDEX_NOW_STARTTIME);
							case IP_COLINDEX_NOW_ENDTIME:
								moveIpToNow();
								return mIPEPGCursor.getInt(IP_COLINDEX_NOW_ENDTIME);
							case IP_COLINDEX_NOW_EVENTID:
								moveIpToNow();
								return mIPEPGCursor.getInt(IP_COLINDEX_NOW_EVENTID);
							case IP_COLINDEX_NEXT_STARTTIME:
								moveIpToNext();
								return mIPEPGCursor.getInt(IP_COLINDEX_NOW_STARTTIME); //yes it's not colindex_next_xxx
							case IP_COLINDEX_NEXT_ENDTIME:
								moveIpToNext();
								return mIPEPGCursor.getInt(IP_COLINDEX_NOW_ENDTIME); //yes it's not colindex_next_xxx
							case IP_COLINDEX_NEXT_EVENTID:
								moveIpToNext();
								return mIPEPGCursor.getInt(IP_COLINDEX_NOW_EVENTID); //yes it's not colindex_next_xxx
							default:
								Log.e(TAG, "unknown int for column " + colIndex);
								return -1;
							}
						} catch(Exception e) {
							Log.e(TAG, "exception to get ip int " + e.getLocalizedMessage());
						}
					} else {
					//	Log.d(TAG, "data not present yet for ip " + status);
					}
				}
			}
			return -1;
		}

		private boolean getBooleanData(int colIndex) {
			synchronized(this) {
				if(mBCEPGMode) {
					if( (status & EpgNowNextData.DATA_PRESENT) > 0) {
						try {
							return (mBCEPGCursor.getInt(colIndex) != 0) ;
						}catch(Exception e) {
							Log.e(TAG, "exception to get bool " + e.getLocalizedMessage());
						}
					} else {
						Log.d(TAG, "data not present yet " + status);
					}
				} else {
					Log.e(TAG, "no boolean data for ip");
				}
			}
			return false;
		}

		private String getStringData(int colIndex) {
			synchronized(this) {
				if(mBCEPGMode) {
					if( (status & EpgNowNextData.DATA_PRESENT) > 0) {
						try {
							return (mBCEPGCursor.getString(colIndex)) ;
						}catch(Exception e) {
							Log.e(TAG, "exception to get bc string " + e.getLocalizedMessage());
						}
					} else {
						//Log.d(TAG, "data not present yet " + status);
					}
				} else {
					if( (status & EpgNowNextData.DATA_PRESENT) > 0) {
						try {
							switch(colIndex) {
							case IP_COLINDEX_NOW_TEXT:
								moveIpToNow();
								return mIPEPGCursor.getString(IP_COLINDEX_NOW_TEXT);
							case IP_COLINDEX_NOW_TITLE:
								moveIpToNow();
								return mIPEPGCursor.getString(IP_COLINDEX_NOW_TITLE);
							case IP_COLINDEX_NEXT_TEXT:
								moveIpToNext();
								return mIPEPGCursor.getString(IP_COLINDEX_NOW_TEXT); //yes it's not colindex_next_xxx
							case IP_COLINDEX_NEXT_TITLE:
								moveIpToNext();
								return mIPEPGCursor.getString(IP_COLINDEX_NOW_TITLE);	//yes it's not colindex_next_xxx
							default:
								Log.e(TAG, "unknown int for column " + colIndex);
								return null;
							}
						} catch(Exception e) {
							//Log.e(TAG, "exception to get ip int " + e.getLocalizedMessage());
						}
					} else {
						//Log.d(TAG, "data not present yet for ip " + status);
					}
				}
			}
			return null;
		}

		public int getHeatMapData() {
			synchronized(this) {
				try {
					return 0;//mIPEPGCursor.getInt(IP_COLINDEX_NOW_HEATMAP);
				} catch(Exception e) {
					Log.e(TAG, "exception to get heat map " + e.getLocalizedMessage());
				}
			}
			return -1;
		}
	}
}

