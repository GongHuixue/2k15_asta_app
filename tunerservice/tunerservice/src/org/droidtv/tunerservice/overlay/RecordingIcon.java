package org.droidtv.tunerservice.overlay;

import android.media.tv.TvContract;
import android.content.Intent;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnKeyListener;
import android.view.LayoutInflater;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tunerservice.R;
import org.droidtv.tunerservice.db.CAMDetails;
import org.droidtv.tunerservice.db.CamInfoDB;
import org.droidtv.tunerservice.interfaces.IRecStateChangeListener;
import org.droidtv.tunerservice.recording.RecService;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.TunerServiceHelpContext;


public class RecordingIcon  implements OnKeyListener,IRecStateChangeListener {
	
	private static final String TAG 							= RecordingIcon.class.getSimpleName();
	private Handler mHandler 									= null;
	private Uri	mCurrentUri 									= null;
	private Context mContext									= null;	
	private View recIconView									= null;
	private OverlayManager mOverlayMgr 							= null;
	private TvToast mTimeOutTvToast								= null;
	private TvToastMessenger messenger							= null;
	private TunerServiceHelpContext mTunerServiceHelpContext	= null;
	
	public RecordingIcon(Context context) {
		Log.d(TAG, "RecordingIcon :  constructor");
		mContext 					= context;
		mHandler 					= new Handler();
		messenger 					= TvToastMessenger.getInstance(mContext);
		mTimeOutTvToast 			= TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
		mTunerServiceHelpContext	= TunerServiceHelpContext.getInstance();
				
		LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		recIconView = inflater.inflate(R.layout.record_icon, null);
		recIconView.setId(OverlayManager.VIEW_REC_ICON);
		recIconView.setOnKeyListener(this);
		
		Runnable r = new Runnable() {
			@Override
			public void run() {
				RecService.getInstance().registerRecStateChangeListener(RecordingIcon.this,"RecordingIcon");
			}
		};
		mHandler.post(r);	
	}

	public void setOverlayManager(OverlayManager overlayManager) {
		Log.d(TAG, "RecordingIcon :  setOverlayManager - "+overlayManager);
		if(overlayManager == null) {
			if(mOverlayMgr!=null){
				Log.d(TAG, "RecordingIcon :removeRecordingIcon!!!");
				mOverlayMgr.removeRecordingIcon(recIconView);
			}
			mCurrentUri	= null;
		}
		mOverlayMgr = overlayManager;
	}
	
	public void onPlayStarted(Uri mediaPlayerUri) {
		Log.d(TAG, "RecordingIcon :onPlayStarted : "+mediaPlayerUri);
		mCurrentUri = mediaPlayerUri;
		mCheckRecordingIcon();
	}
	
	public void onPlayCompleted(final Uri mediaPlayerUri) {
		//do nothing
	}
	
	@Override
	public void onRecStarted(){
		Log.d(TAG, "RecordingIcon :onRecStarted");
		mCheckRecordingIcon();			
	}
	
	@Override
	public void onRecFinished(){
		Log.d(TAG, "RecordingIcon :onRecFinished");
		mCheckRecordingIcon();		
	}
		
	@Override
	public boolean onKey(View v, int keyCode, KeyEvent event) {
		Log.d(TAG, "onKey " + keyCode + ", " + KeyEvent.KEYCODE_EXPLORER+ ", " + KeyEvent.KEYCODE_TV_INPUT);
		boolean retval = false;
		if(keyCode == KeyEvent.KEYCODE_PROG_RED && event.getAction() == KeyEvent.ACTION_UP){
			retval=true;
		}
		if(event.getAction() == KeyEvent.ACTION_DOWN) {
			if(keyCode == KeyEvent.KEYCODE_MEDIA_RECORD) {
				retval = mOnKeyDown(keyCode);
			}
			else if(keyCode == KeyEvent.KEYCODE_MEDIA_STOP) {
				retval = mOnKeyDown(keyCode);
			}
			else if(keyCode == KeyEvent.KEYCODE_PROG_RED){
				if(isRecordingOngoinginZiggo()){
					mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_ZIGGO_RECORDING_ONGOING));
					messenger.showTvToastMessage(mTimeOutTvToast);
					retval=true;
				}
				else if(!IsDualTunerFactoryConfigEnabled()){
					showStopRecordingToast();
					retval=true;
				}else{
					retval=false;
				}
			}
			else if(((keyCode == KeyEvent.KEYCODE_CHANNEL_UP) ||
					(keyCode == KeyEvent.KEYCODE_CHANNEL_DOWN) ||
					(keyCode == KeyEvent.KEYCODE_0) || 
					(keyCode == KeyEvent.KEYCODE_1)	||
					(keyCode == KeyEvent.KEYCODE_2)	||
					(keyCode == KeyEvent.KEYCODE_3)	||
					(keyCode == KeyEvent.KEYCODE_4)	||
					(keyCode == KeyEvent.KEYCODE_5) ||
					(keyCode == KeyEvent.KEYCODE_6)	||
					(keyCode == KeyEvent.KEYCODE_7)	||
					(keyCode == KeyEvent.KEYCODE_8) ||
					(keyCode == KeyEvent.KEYCODE_9) ||//Digits
					(keyCode == KeyEvent.KEYCODE_BACK) ||// back
					//(keyCode == KeyEvent.KEYCODE_TV_INPUT) ||// Exit, watch TV
					(keyCode == KeyEvent.KEYCODE_NUMPAD_5) ||// Dealer smart-tv
					(keyCode == KeyEvent.KEYCODE_MEDIA_PLAY) ||//Play
					(keyCode == KeyEvent.KEYCODE_MEDIA_PAUSE) ||//Pause
					(keyCode == KeyEvent.KEYCODE_MEDIA_FAST_FORWARD) ||//Forward
					(keyCode == KeyEvent.KEYCODE_MEDIA_REWIND) ||//Rewind
					(keyCode == KeyEvent.KEYCODE_MEDIA_NEXT) ||//Next
					(keyCode == KeyEvent.KEYCODE_MEDIA_PREVIOUS) ||//previous
					//(keyCode == KeyEvent.KEYCODE_EXPLORER) ||//source
					(keyCode == KeyEvent.KEYCODE_SEARCH))) {/*&&//browse*/
				if(!IsDualTunerFactoryConfigEnabled()){
					Log.d(TAG, "Key is blocked by recording in single tuner use case");
					showStopRecordingToast();
					retval = true;
				}
				else {
					Log.d(TAG, "Key is not blocked by recording icon");
					retval = false;
				}
			}
		}
		return retval;
	}

	private void mCheckRecordingIcon() {
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(RecService.getInstance().isRecordingOnGoing(mCurrentUri)) {
					if(mOverlayMgr!=null){
						Log.d(TAG, "RecordingIcon :addRecordingIcon!!!");
						mOverlayMgr.addRecordingIcon(recIconView);
						mSetHelpContext(true);
					}
				}else {
					if(mOverlayMgr!=null){
						Log.d(TAG, "RecordingIcon :removeRecordingIcon!!!");
						mOverlayMgr.removeRecordingIcon(recIconView);
						mSetHelpContext(false);
					}
				}				
			}
		};
		mHandler.post(r);	
	}
	
	private boolean IsDualTunerFactoryConfigEnabled() {
		boolean retVal 						= false;
		PlayTVMediaPlayerFactory factory 	= PlayTVMediaPlayerFactory.getInstance();
		
		retVal	= factory.IsDualTunerFactoryConfigEnabled(PlayTvUtils.getCurrentMedium());
		return retVal;
	}

	private void ShowUpdateDialogue()
	{		
		int recid = RecService.getInstance().getOngoingRecordId(mCurrentUri) ;				
		Log.d(TAG," Ongoing recording id ::" + recid);
		
		String[] projection 	= {	IRecordingsContract.C_RECORDING_ID,IRecordingsContract.C_EFFECTIVE_START_TIME,  
									IRecordingsContract.C_EFFECTIVE_END_TIME, IRecordingsContract.C_RECORDING_NAME,
									IRecordingsContract.C_CHANNELID};
		String selection 		= IRecordingsContract.C_RECORDING_ID + " == ?";
		String[] selectionArgs 	= {String.valueOf(recid)};
		
		Cursor c = mContext.getContentResolver().query(IRecordingsContract.CONTENT_URI_Recordings, projection, selection,
					selectionArgs, null);
		
		if(c != null) {
			try
			{
			if((c.getCount() > 0) && (c.moveToFirst())) {
				int recordingId 	= c.getInt(0);
				long starttime 		= c.getLong(1);
				long recEndtime 	= c.getLong(2);
				long recduration 	= (recEndtime - starttime);
				String recordingname= c.getString(3);
				int channel 		= c.getInt(4);			
				Log.d(TAG,"RECORDING_ONGOING : Show update recording dialogue if we are on same channel where recording is ongoing ");
				Log.d(TAG,"RECORDING_ONGOING : recording id: "+recordingId +" channel on which OTR is going on:"+channel+ "Current channel:"+mCurrentUri);  
						
				// get channel name	
				String chanelName 		= null;
				String [] selArgs 		= {Integer.toString(channel)};
				String seln		  		= TvContract.Channels._ID + " = ?";
				String projn[] 			= { TvContract.Channels.COLUMN_DISPLAY_NAME };
				Cursor cursor 			= mContext.getContentResolver().query(TvContract.Channels.CONTENT_URI,
										  projn,seln, selArgs, null);
				if(cursor!=null){
					if((cursor.getCount()>0) && (cursor.moveToFirst())){
						chanelName = cursor.getString(0);				
					} else {
						Log.d(TAG, " !!! no channel info");
					}
					cursor.close();
					cursor=null;
				}
			 
				//Raise an intent to epg to show update record timing dialogue
				Intent intent = new Intent(TvIntent.ACTION_UPDATE_RECORDING_ACTIVITY);
				intent.putExtra("RECORDING_TYPE", IRecordingsContract.RecordingType.RECORDING_ONGOING.ordinal());
				intent.putExtra("RECORDING_ID", recordingId);
				intent.putExtra("REC_STARTTIME", starttime);
				intent.putExtra("REC_DURATION", recduration);
				intent.putExtra("REC_PROGRAMNAME", recordingname);
				intent.putExtra("REC_CHANNELNAME", chanelName);
				intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				mContext.startActivity(intent);				
			}
			}
			finally
			{
  			   c.close();
			   c=null;
			}
		}
	}
	
	private boolean mOnKeyDown(int keyCode) {
		boolean bRetval = false;
		Log.d(TAG, "mOnKeyDown");
		if (keyCode == KeyEvent.KEYCODE_MEDIA_RECORD) {		
			Log.d(TAG, "mOnKeyDown : RECORD ");			
			ShowUpdateDialogue();
			bRetval=true;
		}
		else if (keyCode == KeyEvent.KEYCODE_MEDIA_STOP) {
			//raise an intent
			Intent intent = new Intent(TvIntent.ACTION_STOP_RECORDING_DIALOG);
			int recid = RecService.getInstance().getOngoingRecordId(mCurrentUri);
			intent.putExtra("recId", recid);
			intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			mContext.startActivity(intent);

			bRetval=true;
		}		
		return bRetval;
	}

	public void showStopRecordingToast() {
		// TODO Auto-generated method stub
		if(messenger!=null && mTimeOutTvToast!=null){
			mTimeOutTvToast.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_PVR_STOP_RECORDING));
			messenger.showTvToastMessage(mTimeOutTvToast);
		}
	}

	public boolean isRecordingOngoinginZiggo(){
		boolean isRecordingOngoinginZiggo=false;
		try{
				CAMDetails camDetails = new CAMDetails();
				camDetails.setMedium(CAMDetails.UNKNOWNMEDIUM);
				CamInfoDB camInfo = CamInfoDB.getInstace(mContext);
				int noOfCAMS = camInfo.getNoOfCAMS(camDetails);
				Log.i(TAG, "NoOFCAMS:" + noOfCAMS);
				if (noOfCAMS == 1 && RecService.getInstance().getIsZiggoRecordingOnGoing()) {
					isRecordingOngoinginZiggo = true;
				}
		} catch (Exception e) {
			Log.d(TAG, "Exception in checkRecordingInOlympic");
		}
		return isRecordingOngoinginZiggo;
	}
		
	private void mSetHelpContext(boolean set) {
		String secondaryHelpContext = null;
		String[] currentHelpContext = null;
		Log.d(TAG, "mSetHelpContext "+set);
		try {
			if (mTunerServiceHelpContext != null) {
				currentHelpContext = mTunerServiceHelpContext.getHelpContextData();
				if (currentHelpContext != null) {
					Log.d(TAG, "currentHelpContext "+currentHelpContext[0]+" "+currentHelpContext[1]+" "+currentHelpContext[2]);
					if (set) {
						if(RecService.getInstance().isRecordingforeground()) {
							Log.d(TAG, "foreground rec "+set);
							secondaryHelpContext = mTunerServiceHelpContext.recording_foreground;
						} else {
							Log.d(TAG, "background rec "+set);
							secondaryHelpContext = mTunerServiceHelpContext.recording_background;
						}
						mTunerServiceHelpContext.setHelpContextData(currentHelpContext[0],
																		secondaryHelpContext, 
																		mTunerServiceHelpContext.NA, 
																		mTunerServiceHelpContext.NA);
					} else {
						if ((currentHelpContext[1].equalsIgnoreCase(mTunerServiceHelpContext.recording_foreground)) || 
							(currentHelpContext[1].equalsIgnoreCase(mTunerServiceHelpContext.recording_background))) {
							mTunerServiceHelpContext.setHelpContextData(currentHelpContext[0],
																			mTunerServiceHelpContext.Playstate, 
																			mTunerServiceHelpContext.NA, 
																			mTunerServiceHelpContext.NA);
						}
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
