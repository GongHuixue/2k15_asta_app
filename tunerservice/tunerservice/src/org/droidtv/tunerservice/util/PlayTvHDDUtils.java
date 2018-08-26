package org.droidtv.tunerservice.util;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.droidtv.tunerservice.interfaces.IHDDListener;
import org.droidtv.tv.os.storage.IUsbVolumeLister;
import org.droidtv.tv.provider.IHDDContract;

import android.content.Context;
import android.database.ContentObserver;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.os.StatFs;
import android.util.Log;


public class PlayTvHDDUtils {
	public static final String Tag ="PlayTvHDDUtils";
	private String mMountPath;
	private long mTotalHDDSize = 0;
	private long mDeviceID = 0;
	private static final String TIME_SHIFT_PATH = "/TimeShift";
	private static final long QUOTA_SIZE = 34359738368L;// 32 GB (32*1024*1024*1024)
	private Context mContext;
	private static PlayTvHDDUtils _instance = null;
	private HDDContentObserver HddObserver = null;
	private List<IHDDListener> registeredListeners = new ArrayList<IHDDListener>();

	public PlayTvHDDUtils(Context context) {
		mContext = context;
		HddObserver = new HDDContentObserver(null);
		mContext.getContentResolver().registerContentObserver(
				IHDDContract.PAIRED_DEVICES_URI, true, HddObserver);
		Log.d(Tag, "Registered IHDDContract Observer");
		queryIHDDContract(mContext);
	}

	public String getMountPath() {
		synchronized(this) {
			return mMountPath; //it is ok to return within a synchronized block..java
		}
	}

	public static synchronized PlayTvHDDUtils getInstance(Context context) {
		if (_instance == null) {
			_instance = new PlayTvHDDUtils(context);
		}
		return _instance;
	}

	public long getTotalSize() {

		if(mTotalHDDSize > 0)
			return mTotalHDDSize;

		if (mMountPath != null) {
			StatFs mediaFS;
			try {

				mediaFS = new StatFs(mMountPath);

			}catch(Exception e) {
				Log.d(Tag,"getTotal size exception "+e.toString());
				return -1;
			}

			long blockSize = mediaFS.getBlockSizeLong();
			long availableBlocks = mediaFS.getBlockCountLong() ;

      Log.d(Tag, "avilable blocks  MediaFS.getBlockSizeLong() "	+ blockSize);
			Log.d(Tag, " MediaFS.getBlockCountLong() " + availableBlocks);

			mTotalHDDSize = availableBlocks * blockSize;
			Log.d(Tag, " AvailableSize is " + mTotalHDDSize);
			mTotalHDDSize = mTotalHDDSize - (long) (0.05 * mTotalHDDSize);

			Log.d(Tag, " AvailableSize after deduction " + mTotalHDDSize);

		} else {

			Log.e(Tag, "provide mountpath which is null");
		}

		return mTotalHDDSize;
	}

	public long getFreeSize() {

		if (mMountPath != null) {

		    String pvrPath = mMountPath + "/pvr";
		    StatFs pvrmediaFS;
		    Log.d(Tag, "  PVR path " + pvrPath);
		    try {
          pvrmediaFS = new StatFs(pvrPath);
        }catch(Exception e) {
          Log.d(Tag,"getFree size exception "+ e.toString());
          return -1;
        }

        long freeBlock = pvrmediaFS.getFreeBlocksLong();
        long blockSize =  pvrmediaFS.getBlockSizeLong();
        
        Log.d(Tag, "getBlockSizeLong" + blockSize);
        Log.d(Tag, "getFreeBlocksLong" + freeBlock);
        return (freeBlock * blockSize);

		} else {
			Log.e(Tag, " getFreeSize mountpath is null");
		}
		return -1;
	}

	public long getTSFolderSize(File directory) {

		long length = 0;
		if(directory.isDirectory()) {
			for (File file : directory.listFiles()) {
				if (file != null && file.isFile())
					length += file.length();
				else if(file != null)
					length += getTSFolderSize(file);
			}
		} else {
			length = directory.length();
		}
		return length;
	}

	public long getDeviceId() {

		if (mMountPath == null) {
			Log.e(Tag, "provider mountpath and serial number");
			return -1;
		} else if (mDeviceID > 0) {
			return mDeviceID;
		}

		IUsbVolumeLister volumeLister = IUsbVolumeLister.Instance
				.getInterface();
		List<IUsbVolumeLister.UsbVolume> volumes = volumeLister
				.getMountedVolumes();

		String produtId = null;
		String vendorId = null;
		String serialNumber = null;

		for (IUsbVolumeLister.UsbVolume vol : volumes) {
			if (vol.mMountPath.equalsIgnoreCase(mMountPath) == true) {

				serialNumber = vol.mSerialNum == null? "":vol.mSerialNum;
				vendorId = vol.mVendorID == null?"":vol.mVendorID;
				produtId = vol.mProductID == null?"":vol.mProductID;

				Log.d(Tag, " QueryIHDDContract : vol.mSerialNum; ->  "+ serialNumber);
				Log.d(Tag, " QueryIHDDContract : VENDOR_ID ->  " + vendorId);
				Log.d(Tag, " QueryIHDDContract : produtId ->  " + produtId);
				break;
			}
		}

		String deviceId = vendorId + serialNumber + produtId;

		Log.d(Tag,"device Id is "+deviceId);

		if (deviceId != null) {

			long hashCode = 1125899906842597L;
			int len = deviceId.length();
			for (int i = 0; i < len; i++) {
				hashCode = (31 * hashCode) + deviceId.charAt(i);
			}
			Log.d(Tag, "Device Id hash code " + hashCode);
			mDeviceID = hashCode;
		}
		return mDeviceID;
	}

	private void resetValues() {

		mDeviceID = 0;
		mTotalHDDSize = 0;
	}
	private void queryIHDDContract(Context context) {
		synchronized (this) {
			Log.d(Tag, "QueryIHDDContract ");
			String[] HDD_PROJ = new String[] { IHDDContract.C_MOUNTPATH};
			String HDD_SELECT = IHDDContract.C_MOUNTPATH + "!=";
			String[] HDD_SELECT_ARGS = { null };
			Cursor hddcursor = context.getContentResolver().query(
					IHDDContract.PAIRED_DEVICES_URI, HDD_PROJ, HDD_SELECT,
					HDD_SELECT_ARGS, null);

			if ((hddcursor != null) && (hddcursor.getCount() > 0)
					&& (hddcursor.moveToFirst())) {
				mMountPath = hddcursor.getString(0);
			} else {
				Log.d(Tag, "QueryIHDDContract : Cursor is NULL ");
			}
			if (hddcursor != null) {
				hddcursor.close();
			}

			Log.d(Tag, " QueryIHDDContract : mMountPath ->  " + mMountPath);
		}
	}

	class HDDContentObserver extends ContentObserver {

		public HDDContentObserver(Handler handler) {
			super(handler);
			Log.d(Tag, "HDDContentObserver construct");
		}

		@Override
		public boolean deliverSelfNotifications() {
            return false;
		}

		@Override
		public void onChange(boolean selfChange, Uri uri) {
		    Log.d(Tag, "onChange ");
		    String oldPath = getMountPath();
		    queryIHDDContract(mContext);
		    String newPath = getMountPath();
			resetValues();
			getTotalSize();
			getDeviceId();
		    if(newPath == null) {
		    	onHDDRemoved();
		    } else if(oldPath == null) {
		    	onHDDConnected();
		    } else if(oldPath.equals(newPath) == false) {
		    	onHDDRemoved();
		    	onHDDConnected();
		    } else {
		    	Log.d(Tag, "no path change " + uri);
		    }
		}
    }

	private void onHDDConnected() {
		synchronized (registeredListeners) {
			for(IHDDListener HDDListener:registeredListeners) {
				HDDListener.onHDDConnected();
			}
		}
	}

	private void onHDDRemoved() {
		synchronized (registeredListeners) {
			Log.d(Tag, "size in removed " + registeredListeners.size());
			for(IHDDListener HDDListener:registeredListeners) {
				Log.d(Tag, "telling client removed ");
				HDDListener.onHDDRemoved();
			}
		}
	}

	public boolean addHDDListener(IHDDListener handler, String cTag)
	{
		Log.d(Tag,"addHDDListener called from " + cTag);
		synchronized(registeredListeners) {
			if(registeredListeners.contains(handler)==false)
			{
				registeredListeners.add(handler);
				return true;
			}
		}
		return false;
	}

	public boolean removeHDDListener(IHDDListener handler, String cTag)
	{
		Log.d(Tag,"removeHDDListener called from " + cTag);
		synchronized(registeredListeners) {
			if(registeredListeners.contains(handler)==true)
			{
				registeredListeners.remove(handler);
			}
		}
		return true;
	}
	
	 public String queryMountPath() {
			queryIHDDContract(mContext);
			return mMountPath;
	 }
		
}