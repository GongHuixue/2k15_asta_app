package org.droidtv.euinstallertc.service;

import java.io.IOException;
import java.util.ArrayList;

import org.droidtv.euinstallertc.model.mwapi.IntKeyValueablesPrivate;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.mwapi.TvContractPrivate;
import org.droidtv.euinstallertc.service.DirectTuneUtility.ChannelData;
import org.droidtv.htv.provider.HtvContract;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.util.IIntKeyValueables;

import android.content.ContentProviderOperation;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.OperationApplicationException;
import android.database.Cursor;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.RemoteException;
import android.util.Log;
import android.util.SparseIntArray;

class DirectInstallHandler extends AsyncTask<Bundle,Void,Void> {
	
	private final String TAG = DirectInstallHandler.class.getSimpleName();
	private Context mContext;
	private NativeAPIWrapper mWrapper = NativeAPIWrapper.getInstance();
	
	
	private static final int INDEX_FIRST_TUNETYPE = DirectTuneUtility.INDEX_TUNETYPE_DVB_T;
	private static final int INDEX_LAST_TUNETYPE = DirectTuneUtility.INDEX_TUNETYPE_ANALOG;
	
	public DirectInstallHandler(Context context) {
		mContext = context;
	}

	@Override
	protected Void doInBackground(Bundle... avBundles) {
		Bundle fBundle = avBundles[0];
		
		Log.d(TAG, "doInBackground() is called.");
		
		if(!fBundle.containsKey(EuInstallerService.KEYNAME_DT_CHNO)) {
			
			Log.d(TAG, "Error: Parameter 'DT_CHNO' is missing.");
			
			sendDTResultIntent(1);
			return null;
		}
		
		if(!fBundle.containsKey(EuInstallerService.KEYNAME_DT_TUNETYPE) ) {
			
			Log.d(TAG, "Error: Parameter 'DT_TUNETYPE' is missing.");
			
			sendDTResultIntent(1);
			return null;
		}
				
		mWrapper.acquireHTVDTSemaphore();
		
		Log.d(TAG, "Prepare to do direct channel install.");
		
		if(mWrapper.getApplicationState() == NativeAPIEnums.ApplicationState.IDLE 
				|| mWrapper.getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE) {			
			
			if(mWrapper.getApplicationState() == NativeAPIEnums.ApplicationState.INST_SERVICE)
				mWrapper.stopBckInstallation();
			
			int fiTuneType = fBundle.getInt(EuInstallerService.KEYNAME_DT_TUNETYPE);
			
			if(fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T 
					|| fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T2
					|| fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_C) {
				
				if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_FREQ)
						&& fBundle.containsKey(EuInstallerService.KEYNAME_DT_SERVID)) {
					
					Log.d(TAG, "Prepare to install digital channel.");
			
					ChannelData fChData = new ChannelData();
					
					fChData.miTuneType = fiTuneType;
					fChData.miChNo = fBundle.getInt(EuInstallerService.KEYNAME_DT_CHNO);
					fChData.miFreq = fBundle.getInt(EuInstallerService.KEYNAME_DT_FREQ);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_ONID))
						fChData.miONID = fBundle.getInt(EuInstallerService.KEYNAME_DT_ONID);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_TSID))
						fChData.miTSID = fBundle.getInt(EuInstallerService.KEYNAME_DT_TSID);

					fChData.miServID = fBundle.getInt(EuInstallerService.KEYNAME_DT_SERVID);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_MOD))
						fChData.miMod = fBundle.getInt(EuInstallerService.KEYNAME_DT_MOD);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_SYMRT))
						fChData.miSymRt = fBundle.getInt(EuInstallerService.KEYNAME_DT_SYMRT);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_BLANK))
						fChData.miBlank = fBundle.getInt(EuInstallerService.KEYNAME_DT_BLANK);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_SKIP))
						fChData.miSkip = fBundle.getInt(EuInstallerService.KEYNAME_DT_SKIP);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_CHNAME))
						fChData.msChName = fBundle.getString(EuInstallerService.KEYNAME_DT_CHNAME);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_BW))
						fChData.miBW = fBundle.getInt(EuInstallerService.KEYNAME_DT_BW);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_PLPID))
						fChData.miPLPID = fBundle.getInt(EuInstallerService.KEYNAME_DT_PLPID);
					
					installChannel(fChData);				
				}
				else {
					Log.d(TAG, "Error: Some parameters are missing.");
					sendDTResultIntent(1);
				}									
			} else if(fiTuneType == DirectTuneUtility.INDEX_TUNETYPE_ANALOG) {
				
				if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_FREQ)
						&& fBundle.containsKey(EuInstallerService.KEYNAME_DT_TVSYS)) {
					
					Log.d(TAG, "Prepare to install analog channel.");
					
					ChannelData fChData = new ChannelData();
					
					fChData.miTuneType = fiTuneType;
					fChData.miChNo = fBundle.getInt(EuInstallerService.KEYNAME_DT_CHNO);
					fChData.miFreq = fBundle.getInt(EuInstallerService.KEYNAME_DT_FREQ);
					fChData.miTvSys = fBundle.getInt(EuInstallerService.KEYNAME_DT_TVSYS);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_BLANK))
						fChData.miBlank = fBundle.getInt(EuInstallerService.KEYNAME_DT_BLANK);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_SKIP))
						fChData.miSkip = fBundle.getInt(EuInstallerService.KEYNAME_DT_SKIP);
					
					if(fBundle.containsKey(EuInstallerService.KEYNAME_DT_CHNAME))
						fChData.msChName = fBundle.getString(EuInstallerService.KEYNAME_DT_CHNAME);
					
					installChannel(fChData);				
				}			
			}
			else {
				Log.d(TAG, "Error: The value of 'DT_TUNETYPE' is invalid.");
				sendDTResultIntent(1);
			}
		}
		else {
			Log.d(TAG, "Error: Some installing-related task is still running.");					
			sendDTResultIntent(2);
		}
		
		mWrapper.releaseHTVDTSemaphore();
		
		return null;
	}
	
	private void shiftSpecialChannelNo(ChannelData aChData){
		int fiChNoMax = aChData.miChNo;
		
		Log.d(TAG, "shiftSpecialChannelNo() is called.");
		
		ArrayList<ContentProviderOperation> fvOperations=new ArrayList<ContentProviderOperation>();
		String[] fsvProjection = new String[] {"max(cast(" + HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER + " as integer))"};
		String fsSelection = HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE + " in (?,?,?,?)";
		String[] fsvSelectionArgs = new String[]{HtvContract.HtvBaseDefs.TYPE_TUNER, HtvContract.HtvBaseDefs.TYPE_IP_UNICAST, HtvContract.HtvBaseDefs.TYPE_IP_MULTICAST, HtvContract.HtvBaseDefs.TYPE_IP_RTSP_RTP};
		
		Cursor fCursor = mContext.getContentResolver().query(HtvContract.HtvChannelSetting.CONTENT_URI, fsvProjection, fsSelection, fsvSelectionArgs, null);
		
		if(fCursor != null) {
			
			try{
				if(fCursor.getCount() > 0)
				{
				
					fCursor.moveToFirst();
				
					if(fCursor.getInt(0) > fiChNoMax)
						fiChNoMax = fCursor.getInt(0);				
				}
			}
			catch(Exception e){
				Log.d(TAG, "Error: Query the maximum channel No. of BCST/IP channel fails.");
			}
			finally{
				fCursor.close();
				fCursor = null;
			}			
		}
		
		Log.d(TAG, "shiftSpecialChannelNo(): The maximum channel No. of BCST/IP channel is: " + fiChNoMax);
		
		fsvProjection = new String[] {HtvContract.HtvChannelSetting._ID, HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER};
		fsSelection = HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE +" IN (?,?) ";
		fsvSelectionArgs = new String[]{HtvContract.HtvBaseDefs.TYPE_SOURCE, HtvContract.HtvBaseDefs.TYPE_FILE};
		
		
		fCursor = mContext.getContentResolver().query(HtvContract.HtvChannelSetting.CONTENT_URI, fsvProjection, fsSelection, fsvSelectionArgs, null);
		SparseIntArray fviSpecialChs = new SparseIntArray();		
				
		if(fCursor != null) {
			
			try{
				if(fCursor.getCount()>0){
					
					Log.d(TAG, "shiftSpecialChannelNo(): channel count of source/local media files: " + fCursor.getCount());
				
					fCursor.moveToFirst();
				
					do{
						try{
							int fiChNo = Integer.valueOf(fCursor.getString(1));
							fviSpecialChs.put(fiChNo, fCursor.getInt(0));
						}
						catch(NumberFormatException e){						
						}					
					}while(fCursor.moveToNext());
				}
			}
			catch(Exception e)
			{
				Log.d(TAG, "Error: Read sources/local media files fails. " + e.getMessage());				
			}
			finally {
				fCursor.close();
				fCursor = null;
			}			
		}
		
		if(fviSpecialChs.size()>0) {
			if(fviSpecialChs.keyAt(0)<=fiChNoMax){
				
				fsSelection = HtvContract.HtvChannelSetting._ID + "=? ";
				fsvSelectionArgs = new String[]{"0"};
				int fiNewSpecialChNo = fiChNoMax;
				
				for(int fiIdx=0; fiIdx<fviSpecialChs.size(); fiIdx++){
					ContentProviderOperation.Builder builder = ContentProviderOperation.newUpdate(HtvContract.HtvChannelSetting.CONTENT_URI);
					builder.withValue(HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, String.valueOf(++fiNewSpecialChNo));
					fsvSelectionArgs[0] = String.valueOf(fviSpecialChs.valueAt(fiIdx));
					builder.withSelection(fsSelection, fsvSelectionArgs);
					
					fvOperations.add(builder.build());
				}
				
				try{
					mContext.getContentResolver().applyBatch(HtvContract.AUTHORITY, fvOperations);
				}
				catch(Exception e){
					Log.d(TAG, "Error: Shift channel No. of source/local media files fail." + e.getMessage());
				}
				
				fvOperations.clear();
			}
			
			fviSpecialChs.clear();
		}
		
		Log.d(TAG, "shiftSpecialChannelNo() is done.");
	}
	
	private void installChannel(ChannelData aChData) {
		
		Log.d(TAG, "installChannel() is called.");
		
		sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START", aChData.miTuneType);
		
		String[] fsvProjection = new String[] {HtvContract.HtvChannelSetting._ID};
		String fsSelection = HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER +"=? ";
		String[] fsvSelectionArgs = new String[]{Integer.toString(aChData.miChNo)};
		ArrayList<ContentProviderOperation> fvOperations=new ArrayList<ContentProviderOperation>();
		int fiDupChIdx = -1;
		/*
		if( aChData.miTuneType == INDEX_TUNETYPE_ANALOG)
			fiDupChIdx = mWrapper.findAnalogChannel(aChData.miFreq, INDEX_TUNETYPE_DVB_T, null);
		else
			fiDupChIdx = mWrapper.findDigitalChannel(aChData.miFreq, aChData.miTuneType, aChData.miServID, null, aChData.miONID, aChData.miTSID, null, null);
		*/
		if(fiDupChIdx != -1) {			
			Log.d(TAG, "Info: Duplicated channel found.");			
			fsSelection += " OR " + HtvContract.HtvChannelSetting._ID + "=" + fiDupChIdx;
		}
		
		shiftSpecialChannelNo(aChData);

		Cursor fCursor = mContext.getContentResolver().query(HtvContract.HtvChannelSetting.CONTENT_URI, fsvProjection, fsSelection, fsvSelectionArgs, null);
		
		if(fCursor != null && fCursor.getCount() > 0) {
									
			String[] fsvSelectionForDelete = new String[]{"0"};
			
			fCursor.moveToFirst();
			
			do{			
				ContentProviderOperation.Builder builder=ContentProviderOperation.newDelete(Channels.CONTENT_URI);
				fsvSelectionForDelete[0] = String.valueOf(fCursor.getInt(0));
				builder.withSelection(Channels._ID +"= ?", fsvSelectionForDelete);
				
				fvOperations.add(builder.build());
								
							    	
			}while(fCursor.moveToNext());
		}
		
		if(fCursor != null) {
			fCursor.close();
			fCursor = null;
		}
		
		mWrapper.unregisterTvProviderContentObservers();
		
		if(fvOperations.size() > 0) {
			Log.d(TAG, "Info: Remove channel with display number '" + aChData.miChNo + "' and duplicated channel from Htv content provider.");
			mContext.getContentResolver().delete(HtvContract.HtvChannelSetting.CONTENT_URI, fsSelection, fsvSelectionArgs);
			
			Log.d(TAG, "Info: Remove channel with display number '" + aChData.miChNo + "' and duplicated channel from TvProvider.");
			try {
				mContext.getContentResolver().applyBatch(Channels.CONTENT_URI.getAuthority(), fvOperations);
			}
			catch(Exception e) {
				Log.d(TAG, "Error: Remove channel from TvProvider fails. " + e.getMessage());
				
				mWrapper.registerTvProviderContentObservers();
				
				sendDTResultIntent(3);				
				sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED", aChData.miTuneType);
				return;
			}
			
		}
		
		Log.d(TAG, "Info: Create the display number of the new channel in TvProvider.");
		
		int fiDispNum = 1;
		
		fsvProjection = new String[] {"max(cast(display_number as integer))"};
		fsSelection = Channels.COLUMN_VERSION_NUMBER + " in (?,?)";
		fsvSelectionArgs = new String[]{"0", "1"};
		
		fCursor = mContext.getContentResolver().query(Channels.CONTENT_URI, fsvProjection, fsSelection, fsvSelectionArgs, null);
		
		if(fCursor != null && fCursor.getCount() > 0) {
			fCursor.moveToFirst();
			
			if(!fCursor.isNull(0)) {
				fiDispNum = fCursor.getInt(0);
			    
				if(fiDispNum <= 0)
					fiDispNum = 1;
				else
					fiDispNum += 1;
			}
		}
		
		if(fCursor != null) {
			fCursor.close();
			fCursor = null;
		}
		
		Log.d(TAG, "Info: Display number-> " + fiDispNum);
		
		aChData.miPresetNum = mWrapper.GetLastAnalogPresetNumber()+1;
				
		try {
			
			ContentValues val=new ContentValues();
			
			val.put (Channels.COLUMN_INPUT_ID,"org.droidtv.tunerservice/.TunerService");
			val.put (Channels.COLUMN_TYPE,DirectTuneUtility.mapTuneTypeString(aChData.miTuneType));				
			val.put (Channels.COLUMN_SERVICE_TYPE, Channels.SERVICE_TYPE_AUDIO_VIDEO);
			
			if(aChData.miTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T || aChData.miTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_T2)
				val.put (Channels.COLUMN_NETWORK_AFFILIATION , NativeAPIWrapper.HTV_DI_CHANNEL_CHECK_FLAG);
			else if(aChData.miTuneType == DirectTuneUtility.INDEX_TUNETYPE_ANALOG || aChData.msChName != null)
				val.put (Channels.COLUMN_NETWORK_AFFILIATION , NativeAPIWrapper.HTV_DI_CHANNEL_FLAG);
			else
				val.put (Channels.COLUMN_NETWORK_AFFILIATION , NativeAPIWrapper.HTV_DI_CHANNEL_UPDATE_FLAG);
			
			if(aChData.miONID != null)
				val.put (Channels.COLUMN_ORIGINAL_NETWORK_ID, aChData.miONID);
			
			if(aChData.miTSID != null)
				val.put (Channels.COLUMN_TRANSPORT_STREAM_ID, aChData.miTSID);
			
			if(aChData.miServID != null)
				val.put (Channels.COLUMN_SERVICE_ID, aChData.miServID);
			
			val.put (Channels.COLUMN_DISPLAY_NUMBER,Integer.toString(fiDispNum));			
			val.put (Channels.COLUMN_DISPLAY_NAME, (aChData.msChName != null)?aChData.msChName:"");			
			val.put (Channels.COLUMN_DESCRIPTION, ""); 	
			val.put (Channels.COLUMN_BROWSABLE, 1);
			val.put (Channels.COLUMN_SEARCHABLE, 1);
			val.put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,DirectTuneUtility.formBlobData(aChData));		
			val.put (Channels.COLUMN_LOCKED,0);
			val.put (Channels.COLUMN_VERSION_NUMBER, DirectTuneUtility.mapVersion(aChData.miTuneType));
			
			Log.d(TAG, "Info: Insert channel data into TvProvider");
			
			Uri fCPResult = mContext.getContentResolver().insert(TvContract.Channels.CONTENT_URI ,val);
			
			Log.d(TAG, "Info: insert result- " + fCPResult);
			
			Log.d(TAG, "Info: Insert channel data into Htv Content Provider");
			
			int fiMappedChId = Integer.parseInt(fCPResult.getLastPathSegment());
			
			val=new ContentValues();
			
			val.put(HtvContract.HtvChannelSetting._ID, fiMappedChId);
			val.put(HtvContract.HtvChannelSetting.COLUMN_MEDIA_TYPE, HtvContract.HtvBaseDefs.TYPE_TUNER);
			val.put(HtvContract.HtvChannelSetting.COLUMN_DISPLAY_NUMBER, Integer.toString(aChData.miChNo));
			val.put(HtvContract.HtvChannelSetting.COLUMN_MAPPED_ID, fiMappedChId);
			
			if(aChData.miBlank != null && aChData.miBlank != 0)
				val.put(HtvContract.HtvChannelSetting.COLUMN_BLANK, 1);
			
			if(aChData.miSkip != null && aChData.miSkip != 0)
				val.put(HtvContract.HtvChannelSetting.COLUMN_SKIP1, 1);
			
			val.put(HtvContract.HtvChannelSetting.COLUMN_FREEPKG, 1);
			
			mContext.getContentResolver().insert(HtvContract.HtvChannelSetting.CONTENT_URI, val);			
			
			Log.d(TAG, "Info: Sync TvProvider to Installer.");
			mWrapper.LoadTvProviderData();
			mWrapper.LoadFreqMapDataData();
			
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_COMPLETE", aChData.miTuneType);
			
			sendDTResultIntent(0);
		}
		catch(IOException e) { 
			Log.d(TAG, "Error: " + e.getMessage());
			sendDTResultIntent(3);
			
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED", aChData.miTuneType);
		}
		catch(NumberFormatException e) {
			Log.d(TAG, "Error: Channel ID can't be extracted from insertion. " + e.getMessage());
			sendDTResultIntent(3);
			
			sendIntent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED", aChData.miTuneType);
		}
		finally {
			mWrapper.registerTvProviderContentObservers();
		}
				
	}
	
	private void sendIntent(String p_action, int aiTuneType) {
		Log.d(TAG, "sendIntent " + p_action);
		Intent l_intent = new Intent(p_action);
		l_intent.putExtra("InstallMode", "DTR");
		if (aiTuneType == DirectTuneUtility.INDEX_TUNETYPE_DVB_C) {
			l_intent.putExtra("InstallMedium", "Cable");
		} else {
			l_intent.putExtra("InstallMedium", "Terrestrial");
		}
		mContext.sendStickyBroadcast(l_intent);
	}
	
	private void sendDTResultIntent(int aiErrCode) {
		final String fsActionName = EuInstallerService.ACTNAME_DIRECT_TUNE_RESULT;
		Log.d(TAG, "sendDTResultIntent " + fsActionName);
		Intent l_intent = new Intent(fsActionName);
		l_intent.putExtra("Result", aiErrCode);
		
		mContext.sendBroadcast(l_intent);
	}
}