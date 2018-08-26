package org.droidtv.tunerservice.recording;

import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tunerservice.util.TvURIHelper.UriData;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.provider.IRecordingsContract.RecordingType;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.media.tv.TvContract.BaseTvColumns;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;

public class RecordData {
	public int recordId;
	public int channelId;
	public long est;
	public long eet;
	public int version;
	public int presetid;
	public int programNumber;
	public RecordingType recordingType;
	public int eventId;
	public int endUserMargin;
	public int startUserMargin;
	public int isIPEPG;
	public String recordingName;
	public Medium medium;
	private String TAG=RecordData.class.getSimpleName();
	public static IRecordingsContract.RecordingType[] rec_type = IRecordingsContract.RecordingType.values();
	public int isRadio;
	public int isZiggo;
	
	public RecordData(int in_recordId, int in_channelId, long in_est, long in_eet, int in_version,RecordingType rec_type2, int in_eventId, int in_endUserMargin, 
										int in_startUserMargin, int in_isIPEPG, String in_recordingName, Context mContext) {
		// data to be filled in by the client..
		recordId = in_recordId;
		channelId = in_channelId;
		est = in_est;
		eet = in_eet;
		version = in_version;
		recordingType = rec_type2;
		presetid = 0;
		programNumber = 0;
		isZiggo=0;
		medium = Medium.MEDIUM_INVALID;
		fillPresetInfo(channelId,mContext);
		eventId = in_eventId;
		endUserMargin = in_endUserMargin;
		startUserMargin = in_startUserMargin;
		isIPEPG = in_isIPEPG;
		recordingName = in_recordingName;
	}

	public void fillPresetInfo(int channelId,Context mContext) {
		Log.d(TAG, "fillPresetInfo channelId : " + channelId);
		Uri tvContentProviderUri = null;
		tvContentProviderUri = TvContract.buildChannelUri(channelId);
//		tvContentProviderUri = ITvURI.Instance.getInterface().getUriFromUniqueId(channelId);
		if (tvContentProviderUri != null) {
			String[] projection = new String[] {Channels.COLUMN_DISPLAY_NUMBER,Channels.COLUMN_SERVICE_ID,Channels.COLUMN_SERVICE_TYPE};
			String selection = BaseTvColumns._ID + "== ?";
			String[] selectionArgs = { String.valueOf(channelId) };
			Cursor c=null;
			try
			{
			c = mContext.getContentResolver().query(tvContentProviderUri, projection, selection, selectionArgs, null);
			if ((c != null) && (c.getCount() > 0) && (c.moveToFirst())) {
				presetid = c.getInt(0);//0
				programNumber = c.getInt(1);//1
				String service_type=c.getString(2);//2
				if((service_type!=null) && (service_type.equalsIgnoreCase(Channels.SERVICE_TYPE_AUDIO))){
					isRadio=1;
				}
				else{
					isRadio=0;
				}
				Log.d(TAG,"fillPresetInfo presetid"+presetid+"programNumber"+programNumber);
				UriData mdata = TvURIHelper.parseUri(mContext, tvContentProviderUri);
				medium= TvURIHelper.Medium.fromInteger(mdata.medium);
				int op_package=ITvSettingsManager.Instance.getInterface().getInt(TvSettingsConstants.OPERATORCABLE, 0, 0);
				if((medium == TvURIHelper.Medium.MEDIUM_CABLE) &&  op_package==TvSettingsDefinitions.OperatorCableConstants.Ziggo){
					isZiggo=1;
				}
			}
			
			}
			finally
			{
				if (c != null)
				{
				   c.close();
				   c=null;
				}
			}
		} else {
			Log.d(TAG, "Returning from fillPresetInfo as URI is null");
			return;
		}
	}

	public RecordData(int rec_id,Context mContext) {
		String[] projection = { IRecordingsContract.C_CHANNELID /* 0*/, IRecordingsContract.C_EFFECTIVE_START_TIME /*1*/, IRecordingsContract.C_EFFECTIVE_END_TIME/*2*/, 
							IRecordingsContract.C_RECORDING_TYPE/*3*/, IRecordingsContract.C_VERSION/*4*/, IRecordingsContract.C_EVENT_ID/*5*/, IRecordingsContract.C_MARGIN_END/*6*/, 
							IRecordingsContract.C_MARGIN_START/*7*/, IRecordingsContract.C_ISIPEPG_RECORDING/*8*/, IRecordingsContract.C_RECORDING_NAME/*9*/ };
		String selection = IRecordingsContract.C_RECORDING_ID + " == ?";
		String[] selectionArgs = { String.valueOf(rec_id) };
		recordId = rec_id;
		Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, selection, selectionArgs, null);
		if ((c != null) && (c.getCount() > 0) && (c.moveToFirst())) {
			channelId = c.getInt(0);
			est = c.getLong(1);
			eet = c.getLong(2);
			recordingType = rec_type[c.getInt(3)];
			version = c.getInt(4);
			presetid = 0;
			programNumber = 0;
			medium = Medium.MEDIUM_INVALID;
			isRadio=0;
			isZiggo=0;
			fillPresetInfo(channelId,mContext);
			Log.e(TAG, " RecordData : channel id " + channelId);
			eventId = c.getInt(5);
			endUserMargin = c.getInt(6);
			startUserMargin = c.getInt(7);
			isIPEPG = c.getInt(8);
			recordingName = c.getString(9);
			Log.d(TAG, "Mukta RecordData : eventId : " + eventId + " , endUserMargin : " + endUserMargin + ", isIPEPG : " + isIPEPG);
		} else {
			Log.e(TAG, "cursor not ok in RecordData");
			channelId = 0;
			est = 0;
			eet = 0;
			version = 0;
			recordingType = RecordingType.RECORDING_FAILED;
			presetid = 0;
			eventId = -1;
			endUserMargin = 0;
			startUserMargin = 0;
			isIPEPG = 0;
			recordingName = null;
			medium = Medium.MEDIUM_INVALID;
			isRadio=0;
			isZiggo=0;
		}
		if (c != null)
		{
			c.close();
		    c=null;     
		}
	}
}
