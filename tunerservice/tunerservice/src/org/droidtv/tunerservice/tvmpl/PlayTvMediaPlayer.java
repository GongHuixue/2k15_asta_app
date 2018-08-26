package org.droidtv.tunerservice.tvmpl;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.util.TvURIHelper;
import org.droidtv.tunerservice.interfaces.IPlayTvStateChangeListener;
import org.droidtv.tv.media.ITvMediaControl;
import org.droidtv.tv.media.ITvMediaControl.IonMediaChangeListener;
import org.droidtv.tv.media.TvMediaPlayer;
import org.droidtv.tv.media.TvMediaPlayer.OnPreparedListenerTv;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tunerservice.util.TvHeaders;
import org.droidtv.tunerservice.db.CAMDetails;
import org.droidtv.tunerservice.db.CamInfoDB;

import android.content.Context;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnInfoListener;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;
import android.view.Surface;
import android.os.Looper;
import org.droidtv.tv.tvinput.CamInfoImpl;
import org.droidtv.tunerservice.PlayTvDiversity;
import org.droidtv.tv.provider.IRecordingsContract.RecordingUri;
import android.media.MediaPlayer.OnCompletionListener;
import android.content.res.AssetFileDescriptor;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileDescriptor;
import 	java.io.FileNotFoundException;
import android.widget.ImageView;
import android.view.WindowManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.widget.RelativeLayout;
import android.view.View;
import android.view.LayoutInflater;
import android.view.ViewGroup.LayoutParams;
import android.util.DisplayMetrics;
import android.widget.FrameLayout;
import org.droidtv.tunerservice.R;
import android.graphics.drawable.Drawable;
import org.droidtv.tunerservice.tvmanager.MainTVManager;



public class PlayTvMediaPlayer implements OnPreparedListenerTv, OnCompletionListener, OnErrorListener, OnInfoListener {
	static final int STOPPED = 0;
	static final int STARTED = 1;
	public static final int SERVICE_TYPE_INVALID = -1;	
	private String tag = null;	
	private TvMediaPlayer tvmplayer;
	private Context mContext;
	private Uri local_uri;
	Map<String, String> local_headers;
	private List<IPlayTvStateChangeListener> listeners = null;	
	private Uri mCurrentUri = null;
	private Map<String,String> mCurrentHeaders	= null;
	private Medium currentMedium = Medium.MEDIUM_INVALID;
	private int serviceType = SERVICE_TYPE_INVALID;
	private boolean hasCicam = false;
	private int currentPurpose = 0;
	private int currentPresetNumber = 0;
	private ClockHandler clkHandler = null;
	Handler mhandler = null;
	private int mtvmpstatus = STOPPED;
	private TvURIHelper.SelectionType mSelectionType;
	IPlayTvStateChangeListener playbackListener=null;
	MediaChangeListenerClass mMediaChangeListener=null;	
	private Object mSyncObj = new Object(); 
	
	public static final int PLAYER_INVALID 				= 0x00;
	public static final int PLAYER_TUNER 				= 0x01;
	public static final int PLAYER_EXTENSION 			= 0x02;
	public static final int PLAYER_TSPLAYER 			= 0x04;
	public static final int PLAYER_FILEPLAYER			= 0x08;
		
	private static final int PLAYER_TUNER_INVALID		= 0x00;
	private static final int PLAYER_TUNER_ANALOG			= 0x01;
	private static final int PLAYER_TUNER_DIGITAL		= 0x02;
	
	private int mUnderlyingPlayer 						= PLAYER_INVALID;
	private int mAnalogDigitalPlayer 					= PLAYER_TUNER_INVALID;
	private boolean isSetSurfaceRequired 				= true;
	private int mCurrentUserType        				= TvMediaPlayer.USERTYPE_WATCHTV_HIGH;
	private mediaPlayerStateControl mplayerStateControl = null;
	private localMediaPlayerStateControl lmplayerStateControl = null;
	private Uri mOrginalUri 							= null;	
	private PlayTvCIPlusHandler mPlayTvCIPlusHandler	= null;
	protected boolean isCamUpgradeStarted				= false;
	private boolean isMediaListenerRegistered           = true;
	private boolean repeat 							= true;
	private Uri mUri									= null;
	private Map<String, String> mheaders			= null;
	/*-------------------------------------------------------------------------------------*/
	private static final int DEFAULT_WIDTH 	= 1920;
	private static final int DEFAULT_HEIGHT = 1080;
	private int mMetricsWidth = DEFAULT_WIDTH;
	private int mMetricsHeight = DEFAULT_HEIGHT;


	private Context mViewContext 	= null;
	private View channelView 	= null;
	private FrameLayout frameLayout = null;
	private Handler mViewHandler 	= null;
	private static LayoutParams mMatchParentLP = null;
	
	public static final int VIEW_CHANNEL_BG 		= 100;
	
	private static final String CHANNELVIEW	= "imageView";
	private String [] mZorderPlay 	= {CHANNELVIEW};
	public String LocalFilePath = "";
	public Context mLayoutContext = null;

	/*-------------------------------------------------------------------------------------*/
	private boolean imagefile = false;
	private class localMediaPlayerStateControl {		
		final int MAXSTACKSIZE=20;
		
		public static final int MPLAYERSTATE_IDLE 			= 1;
		public static final int MPLAYERSTATE_PREPARING 		= 2;
		public static final int MPLAYERSTATE_PREPARED	 	= 3;
		
		int mediaPlayerState = MPLAYERSTATE_IDLE;
		Stack <Map<String,String>> headerstack = null;
		Stack <Uri> uriStack = null;
		
		public localMediaPlayerStateControl() {
			mediaPlayerState = MPLAYERSTATE_IDLE;
			headerstack = new Stack <Map<String, String>>();
			uriStack = new Stack <Uri>();
		}
		
		public void setPrepareState(int state) {
			Log.v(tag,"setPrepareState called " + state);
			this.mediaPlayerState = state;
		}
		
		public int getPrepareState() {
			return this.mediaPlayerState;
		}
		
		public void pushToStack(Map<String, String> headers) {
			if(!headerstack.isEmpty()) {
				if(headerstack.size()>=MAXSTACKSIZE) {
					headerstack.clear();
				}
			}
			headerstack.push(headers);
			Log.d(tag,"pushToStack done size=" + headerstack.size());			
		}

		public void pushToUriStack(Uri mUri) {
			if(!uriStack.isEmpty()) {
				if(uriStack.size()>=MAXSTACKSIZE) {
					uriStack.clear();
				}
			}
			uriStack.push(mUri);
			Log.d(tag,"pushToStack done size=" + uriStack.size());			
		}
		
		public Map<String, String> popFromStack() {
			Map <String, String> headers = null;
			if(!headerstack.isEmpty()) {
				Log.d(tag,"popFromStack called " + headerstack.size()+"isempty=>"+headerstack.isEmpty());
				headers = headerstack.pop();
				if(!headerstack.isEmpty()) {
					headerstack.clear();
				}
				return headers;
			} else {
				return null;
			}
		}

		public Uri popFromUriStack() {
			Uri rUri = null;
			if(!uriStack.isEmpty()) {
				Log.d(tag,"popFromStack called " + uriStack.size()+"isempty=>"+uriStack.isEmpty());
				rUri = uriStack.pop();
				if(!uriStack.isEmpty()) {
					uriStack.clear();
				}
				return rUri;
			} else {
				return null;
			}
		}

		public boolean isStackEmpty() {
			return headerstack.isEmpty();
		}
	}

	
	private class mediaPlayerStateControl {		
		final int MAXSTACKSIZE=5;
		
		public static final int MPLAYERSTATE_IDLE 			= 1;
		public static final int MPLAYERSTATE_PREPARING 		= 2;
		public static final int MPLAYERSTATE_PREPARED	 	= 3;
		
		int mediaPlayerState = MPLAYERSTATE_IDLE;
		Stack <Map<String,String>> headerstack = null;
		public mediaPlayerStateControl() {
			mediaPlayerState = MPLAYERSTATE_IDLE;
			headerstack = new Stack <Map<String, String>>();
		}
		
		public void setPrepareState(int state) {
			Log.v(tag,"setPrepareState called " + state);
			this.mediaPlayerState = state;
		}
		
		public int getPrepareState() {
			return this.mediaPlayerState;
		}
		
		public void pushToStack(Map<String, String> headers) {
			if(!headerstack.isEmpty()) {
				if(headerstack.size()>=MAXSTACKSIZE) {
					headerstack.clear();
				}
			}
			headerstack.push(headers);
			Log.d(tag,"pushToStack done size=" + headerstack.size());			
		}
		
		public Map<String, String> popFromStack() {
			Map <String, String> headers = null;
			if(!headerstack.isEmpty()) {
				Log.d(tag,"popFromStack called " + headerstack.size()+"isempty=>"+headerstack.isEmpty());
				headers = headerstack.pop();
				if(!headerstack.isEmpty()) {
					headerstack.clear();
				}
				return headers;
			} else {
				return null;
			}
		}

		public boolean isStackEmpty() {
			return headerstack.isEmpty();
		}
	}
	/*--------------------------------------------*/
	public void setLayoutContext(Context mContext)
	{
		if(mContext != null)
			this.mLayoutContext = mContext;
	}

	/*--------------------------------------------*/
	public int getTvMediaPlayerToken()
	{
		return tvmplayer.getToken();
	}

	public void setCiPlusHandlerInstance(PlayTvCIPlusHandler obj){
		mPlayTvCIPlusHandler = obj;
	}
	
	public PlayTvMediaPlayer(Context mContext, int purpose, TvMediaPlayer tvmpl, Medium medium, int slotId) {
		tag = "PlayTvMediaPlayer-" + tvmpl.getToken() + "-" + purpose;
		this.mContext = mContext;
		currentMedium = medium;

		Looper looper;
		looper = Looper.myLooper();
		if (looper != Looper.getMainLooper())
			Log.d(tag, "PlayTvMediaPlayer instantiated from NON-UI Thread");

		mplayerStateControl = new mediaPlayerStateControl(); 
		lmplayerStateControl = new localMediaPlayerStateControl();
		
		if(slotId > 0) {
			hasCicam = true;
		}
		currentPurpose = purpose;
		
		listeners = new ArrayList<IPlayTvStateChangeListener>(2);
		tvmplayer = tvmpl;
		tvmplayer.setOnPreparedListenerTv(this);
		
		if((currentPurpose & (PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH | 
				 PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY))>0) {
			clkHandler = new ClockHandler(this);
		}
		
		if((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)> 0) {
			isMediaListenerRegistered = RegisterOnMediaChangeListener(tvmpl);
		}
		
		mhandler = new Handler();
		
		isSetSurfaceRequired = true;
		setUnderlyingPlayer(PLAYER_INVALID);
	}
	
	public void addPurpose(int purpose) {
		int previousPurpose = currentPurpose;
		currentPurpose |= purpose;
		Log.d(tag, "Add Purpose: From:"+previousPurpose+"TO:"+currentPurpose );
		tag = "PlayTvMediaPlayer-" + tvmplayer.getToken() + "-" + currentPurpose;
		if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) > 0) {
			if(clkHandler == null) {
				clkHandler = new ClockHandler(this);
			}			
			isMediaListenerRegistered = RegisterOnMediaChangeListener(tvmplayer);			       
		}
		if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) > 0) {
			isMediaListenerRegistered = RegisterOnMediaChangeListener(tvmplayer);            
        }
		
		if(mPlayTvCIPlusHandler != null)
		{
			mPlayTvCIPlusHandler.addPurpose(purpose);
		}
		
		if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY) > 0) {
			if(clkHandler == null) {
				clkHandler = new ClockHandler(this);
			}			
		}
		
		if(previousPurpose != currentPurpose) {
			onPurposeChanged(currentPurpose);
		}
	}
	

	public void removePurpose(int purpose) {
		boolean mainwatch = false;
		boolean auxWatch = false;
		int previousPurpose = currentPurpose;
		if((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)> 0) {
			mainwatch = true;
		}
		currentPurpose &= ~purpose;
		Log.d(tag, "removePurpose: From:"+previousPurpose+"To:"+currentPurpose );
        if( (currentPurpose & (PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH | PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)) == 0) {
            UnRegisterOnMediaChangeListener(tvmplayer);
        }
        if(tvmplayer!=null){
        	tag = "PlayTvMediaPlayer-" + tvmplayer.getToken() + "-" + currentPurpose;
        }
		if(mPlayTvCIPlusHandler != null)
		{
			mPlayTvCIPlusHandler.removePurpose(purpose);
		}
	
		if(((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)== 0) 
			&& (mainwatch)) {
			setAVSurface(null);
		}
		
		if(currentPurpose == 0) {
			if(tvmplayer != null) {
				Log.i(tag, " reset : tvmplayer-: " + tvmplayer.hashCode());
				tvmplayer.reset();
				synchronized(mplayerStateControl) {
					mplayerStateControl.setPrepareState(mediaPlayerStateControl.MPLAYERSTATE_IDLE);
				}
				synchronized(lmplayerStateControl) {
					lmplayerStateControl.setPrepareState(localMediaPlayerStateControl.MPLAYERSTATE_IDLE);
				}
			}
			clearCurrentUri();
		}
		
		if(previousPurpose != currentPurpose) {
			onPurposeChanged(currentPurpose);
		}
	}

	public int getCurrentPurpose()
	{
		return currentPurpose;
	}
	
	//till resource arbitrator is available..
	public void notifyError() {
		Log.d(tag,"notifyError called ...sending to clients");
		synchronized (listeners) {
			if (playbackListener != null) {
				playbackListener.onError(PlayTvMediaPlayer.this, -1, -1);
			}
			for (IPlayTvStateChangeListener listener : listeners) {
				listener.onError(PlayTvMediaPlayer.this, -1 , -1);
			}
		}
	}
	
	public Medium getCurrentMedium() {
		return currentMedium;
	}
	
	public int getServiceType() {
		return serviceType;
	}
	
	public boolean registerPlayBackListener(IPlayTvStateChangeListener handler, String ctag)
	{
		playbackListener = handler;
		return true;
	}
	
	public boolean registerListener(IPlayTvStateChangeListener handler, String ctag)
	{
		synchronized (listeners) {
			if(listeners.contains(handler)==false)
			{
				listeners.add(handler);
				return true;
			}
		}
		return false;
	}
	
	public boolean unregisterListener(IPlayTvStateChangeListener handler, String ctag)
	{
		synchronized (listeners) {
			listeners.remove(handler);
		}
		return true;
	}
	/*-------------------------------------------------------------------------------------*/
	public void playImageChannel(String filePath , Map<String, String> headers){
		ViewInit(this.mLayoutContext, filePath);

		if(filePath.isEmpty()){
			Log.d(tag, "System couldn't found any local media file!!");
		}else{
			addChannelImage();
		}
	}
	
	public void ViewInit(Context mContext, String filePath) {
		
		this.mViewContext = mContext;
		mViewHandler  = new Handler(Looper.getMainLooper());
		
		LayoutInflater inflater = (LayoutInflater) mViewContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		setMatchParentLP(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT));
		try {
			DisplayMetrics outMetrics = new DisplayMetrics();
			WindowManager mWindowManager = (WindowManager) mViewContext.getSystemService(Context.WINDOW_SERVICE);
			mWindowManager.getDefaultDisplay().getMetrics(outMetrics);			
			mMetricsWidth = outMetrics.widthPixels;
			mMetricsHeight = outMetrics.heightPixels;
			Log.d(tag,"mMetricsWidth : "+mMetricsWidth+"mMetricsHeight : "+mMetricsHeight);
			
		} catch(Exception e) {
			Log.d(tag,"Exception getting metrics");
		}
		
		Log.d(tag,"width=" + mMetricsWidth + " height=" + mMetricsHeight);
		frameLayout = new FrameLayout(mViewContext);
		FrameLayout.LayoutParams params = getDefaultLayoutParams();
		frameLayout.setLayoutParams(params);
		channelView = inflater.inflate(R.layout.channel_img, null);
		channelView.setId(VIEW_CHANNEL_BG);
		LocalFilePath = filePath;
		//updateViewZOrder();
		//printZorder();
	}
	
	/* 
	 *	
	*/
	private int setImageView(String filePath){
		int ret_value = 0;
		LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		channelView = inflater.inflate(R.layout.channel_img, null);
		channelView.setId(VIEW_CHANNEL_BG);
		File imgFile = new File(filePath);
		
		if(imgFile.exists()){
			Drawable image1 = Drawable.createFromPath(filePath);
			channelView.setBackground(image1);
			channelView.setBackgroundDrawable(image1); 
			//channelView.setForeground(image1);
			channelView.setVisibility(View.VISIBLE);
			ret_value = 1;
		}else{
			Log.d(tag,"Exception getting metrics");
		}
		
		return ret_value;
	}
	
	private static void setMatchParentLP(LayoutParams layoutParams) {
		// TODO Auto-generated method stub
		mMatchParentLP=layoutParams;
	}
	
	public void addChannelImage() {
		Runnable r = new Runnable() {
			@Override
			public void run() {
			 	//View v = frameLayout.findViewWithTag(CHANNELVIEW);				
					int width = mMetricsWidth;
					int height = mMetricsHeight;
					FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(width, height);
					channelView.setX(0);
					channelView.setY(0);
					params.setMargins(0, 0, 0, 0);
					//params.setMargins(0, 0, 1280, 720);
					setImageView(LocalFilePath);
					addView(mMatchParentLP,CHANNELVIEW,channelView);
					updateViewZOrder();	
					//printZorder();
			}
		};
		mViewHandler.post(r);
	}
	
	public void removeChannelImage(final View recView) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
			   View v = frameLayout.findViewWithTag(CHANNELVIEW); 
				if(v!=null) {
					removeView(recView);
					updateViewZOrder();
					printZorder();
				}
			}
		};
		mViewHandler.post(r);
	}
	
	private void addView(LayoutParams params, String tag, View nView) {
		nView.setLayoutParams(params);
		nView.setTag(tag);
		frameLayout.addView(nView);
	}
	
	private void removeView(View v) {
		frameLayout.removeView(v);
	}
	
	private void printZorder() {
		int count =frameLayout.getChildCount();
		
		for(int i=0;i<count;i++) {
			frameLayout.getChildAt(i).bringToFront ();
			frameLayout.getChildAt(i).refreshDrawableState();
		}
	}
	
	private void updateViewZOrder() {
			for(int i=0;i<mZorderPlay.length;i++) {
				View v = frameLayout.findViewWithTag(mZorderPlay[i]);
				if(v!=null) {
					v.bringToFront();
				}
			}
	}
	
	public FrameLayout.LayoutParams getDefaultLayoutParams() {
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(mMetricsWidth,mMetricsHeight);
		params.setMargins(0, 0, 0, 0);
		return params;
	}
	
	public void PlayLocalFile(Uri uri, Map<String, String> headers, boolean isImageFile){ 
		currentMedium = Medium.MEDIUM_LOCALFILE;
		serviceType = SERVICE_TYPE_INVALID;
		ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
		String file_uri = "file:/" + uri.toString();
		Uri pathUri = Uri.parse(file_uri);
		imagefile = isImageFile;
		if((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) 
				== PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) {
			Log.d(tag,"purpose TAD : USERTYPE_TAD added");
			headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_TAD));					
		}else {
			headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_WATCHTV_HIGH));
		}

		headers.put(TvHeaders.COMPLETE_URI,pathUri.toString());
		headers.put("IDURI",uri.toString());
		
		

		if(lmplayerStateControl.getPrepareState()!=localMediaPlayerStateControl.MPLAYERSTATE_PREPARING){
			synchronized(lmplayerStateControl) {
				selectLocalChannel(headers);
			}
		}else{
			lmplayerStateControl.pushToStack(headers);
			//lmplayerStateControl.pushToUriStack(pathUri);
		}
	}

	private void selectLocalChannel(Map<String, String> headers) {
		Uri mediaplayerUri = null;
		if(headers==null) {
			if(!lmplayerStateControl.isStackEmpty()) {
				headers = lmplayerStateControl.popFromStack();
			}
		}
		if(headers==null) {
			return;
		}

		lmplayerStateControl.setPrepareState(localMediaPlayerStateControl.MPLAYERSTATE_PREPARING);
		mCurrentUri = Uri.parse(headers.get("IDURI"));
		mediaplayerUri  = Uri.parse(headers.get(TvHeaders.COMPLETE_URI));
		mCurrentHeaders	=	headers;
		
		if(headers.containsKey(TvHeaders.PRESET_ID)) {
			currentPresetNumber = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
			Log.d(tag,"PlayChannel "+ currentPresetNumber);
		}else {
			currentPresetNumber = 0;
			Log.d(tag,"PlayChannel no preset number");
		}

		onPlayStarted(mCurrentUri, mCurrentHeaders, currentMedium, currentPresetNumber);

		if(imagefile) return;
		int status = selectLocalchannelRetry(mediaplayerUri, headers);

		if (status == 0) {
			//tvmplayer.start();
			Log.d(tag, "prepareAsync() : returned");
		}


		if (status != 0) {
			Log.e(tag, "selectChannel failed");
			lmplayerStateControl.setPrepareState(localMediaPlayerStateControl.MPLAYERSTATE_IDLE);
			onPlayFailed(mCurrentUri, currentMedium, currentPresetNumber, IPlayTvStateChangeListener.TUNE_FAILED_REASON_NONE);
		}

	}
	
	private int selectLocalchannelRetry(Uri mediaplayerUri ,Map<String, String> headers) {
		int status = 0;
		try {
//			tvmplayer.stop();
			tvmplayer.setOnCompletionListener(this);
			tvmplayer.setOnErrorListener(this);
			tvmplayer.setOnInfoListener(this);
			tvmplayer.setDataSource(mContext,mediaplayerUri ,headers);
			Log.d(tag,"Calling prepareAsync");
			//tvmplayer.prepare();
			tvmplayer.prepareAsync();
			tvmplayer.setOnCompletionListener(new OnCompletionListener() {
				@Override
				public void onCompletion(MediaPlayer mp) {
					try{
						tvmplayer.seekTo(0);
						tvmplayer.start();
						//lmplayerStateControl.setPrepareState(localMediaPlayerStateControl.MPLAYERSTATE_IDLE);
					}catch (Exception e){
						e.printStackTrace();
					}
				}
			});
		} catch (IOException e) {
			Log.e(tag,"setDataSource fails with IOException");
			status=1;
		} catch (IllegalStateException e) {
			Log.e(tag,"setDataSource fails with IllegalStateException");
			status=1;
		} catch (NullPointerException e) {
			Log.e(tag,"setDataSource fails with NullPointerException");
			status=1;
		}
		return status;
	}
	
	public void PlayCatchUpRecording(Uri uri, int recordingId, Map<String, String> headers) {
		Log.i(tag, "PlayCatchUpRecording "+recordingId);
		Uri mediaPlayerUri = Uri.parse("tv://file");
		currentMedium = Medium.MEDIUM_PVRFILE;
		serviceType = SERVICE_TYPE_INVALID;
		currentPresetNumber = recordingId;
		mCurrentUri = uri;
		Uri.Builder uriBuilder = mCurrentUri.buildUpon();
		uriBuilder.appendQueryParameter("playback", "URL_PLAY");
		mCurrentUri = uriBuilder.build();
		onPlayStarted(mCurrentUri, headers, currentMedium, currentPresetNumber);
		mCurrentHeaders		= 	headers;
		mCurrentUserType	=	TvMediaPlayer.USERTYPE_WATCHTV_HIGH;
		try {
			tvmplayer.setOnCompletionListener(this);
			tvmplayer.setOnErrorListener(this);
			tvmplayer.setOnInfoListener(this);
			onPlayCompleted(mCurrentUri, mCurrentHeaders, currentMedium, currentPresetNumber);
		} catch (Exception e) {
			Log.d(tag,"PlayCatchUpRecording fails "+e.toString());
			onPlayFailed(mediaPlayerUri, currentMedium, currentPresetNumber, IPlayTvStateChangeListener.TUNE_FAILED_REASON_NONE);
		} 		
	}

	public void PlayRecording(int recordingId, Map<String, String> headers) {
		Uri mediaPlayerUri = Uri.parse("tv://file");
		currentMedium = Medium.MEDIUM_PVRFILE;
		serviceType = SERVICE_TYPE_INVALID;
		currentPresetNumber = recordingId;
		mCurrentUri = RecordingUri.buildRecordingUri(recordingId);
		//mCurrentUri = TvURI.formURI(recordingId);//todo:recording movement required
		Uri.Builder uriBuilder = mCurrentUri.buildUpon();
		uriBuilder.appendQueryParameter("playback", "URL_PLAY");
		mCurrentUri = uriBuilder.build();
		if(tvmplayer !=null)
		{
			mtvmpstatus = STOPPED;
			Log.d(tag,"Resetting ");
			tvmplayer.reset();
			Log.d(tag,"Resetting done");
		}		
		if((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) 
				== PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) {
			Log.i(tag,"purpose TAD : USERTYPE_TAD added");
			headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_TAD));					
		}else {
			headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_WATCHTV_HIGH));
		}
		onPlayStarted(mCurrentUri, headers, currentMedium, currentPresetNumber);
		mCurrentHeaders		= 	headers;
		mCurrentUserType	=	TvMediaPlayer.USERTYPE_WATCHTV_HIGH;
		try {
			tvmplayer.setOnCompletionListener(this);
			tvmplayer.setOnErrorListener(this);
			tvmplayer.setOnInfoListener(this);
			tvmplayer.setDataSource(mContext, mediaPlayerUri ,headers);
			Log.d(tag,"Calling prepare");
			tvmplayer.prepareAsync();
			Log.d(tag,"prepareAsync() : returned");
		} catch (IOException e) {
				Log.e(tag,"setDataSource fails with IOException ");
				onPlayFailed(mediaPlayerUri, currentMedium, currentPresetNumber, IPlayTvStateChangeListener.TUNE_FAILED_REASON_NONE);
		} catch (IllegalStateException e) {
			Log.e(tag,"setDataSource fails with IllegalStateException ");
			onPlayFailed(mediaPlayerUri, currentMedium, currentPresetNumber, IPlayTvStateChangeListener.TUNE_FAILED_REASON_NONE);
		} catch (NullPointerException e) {
			Log.e(tag,"setDataSource fails with NullPointerException ");
			onPlayFailed(mediaPlayerUri, currentMedium, currentPresetNumber, IPlayTvStateChangeListener.TUNE_FAILED_REASON_NONE);
		}
	}
	
	public void PlayOlympicChannel(Uri uri,Map<String,String> headers) {
		Log.i(tag,"PlayOlympicChannel ");
		if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) 
				== PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) {
			headers.put(TvHeaders.OLYMPIC_USECASE,Integer.toString(1));
			mCurrentUri 		= uri;
			mCurrentHeaders		= headers;
			if(headers.get(TvHeaders.MEDIUM) != null) {				
				currentMedium 	= Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
			}
			if(headers.get(TvHeaders.PRESET_ID) != null) {				
				currentPresetNumber = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
			}
			
			//olympic usecase
			onPlayStarted(mCurrentUri, mCurrentHeaders, currentMedium, currentPresetNumber);
			tvmplayer.setOnCompletionListener(this);
			tvmplayer.setOnErrorListener(this);
			tvmplayer.setOnInfoListener(this);
			mtvmpstatus = STARTED;
			onPlayCompleted(mCurrentUri, mCurrentHeaders, currentMedium, currentPresetNumber);
		}
		else {
			Log.e(tag,"PlayOlympicChannel : Wrong call - check ");
		}
	}
			
	public void PlayCatchUpChannel (Uri uri,Map<String,String> headers) {
		Log.i(tag,"PlayCatchUpChannel ");
		mCurrentUri 		= uri;
		mCurrentHeaders		= headers;
		if(headers.get(TvHeaders.MEDIUM) != null) {				
			currentMedium 	= Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
		}
		if(headers.get(TvHeaders.PRESET_ID) != null) {				
			currentPresetNumber = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
		}
		
		//olympic usecase
		onPlayStarted(mCurrentUri, mCurrentHeaders, currentMedium, currentPresetNumber);
		tvmplayer.setOnCompletionListener(this);
		tvmplayer.setOnErrorListener(this);
		tvmplayer.setOnInfoListener(this);
		mtvmpstatus = STARTED;
		onPlayCompleted(mCurrentUri, mCurrentHeaders, currentMedium, currentPresetNumber);
	}

	private boolean isDualTunerEnabled(){
		PlayTVMediaPlayerFactory playTvMPFactory = PlayTVMediaPlayerFactory.getInstance();
		if(playTvMPFactory != null){
				boolean dualTunerStatus = playTvMPFactory.isDualTunerFactoryConfigEnabled();
				Log.i(tag,"isDualTunerEnabled:"+dualTunerStatus);
				return dualTunerStatus;
		}
		return false;
	}
	
	
	public int getCurrentChannel()
	{
		Log.i(tag,"get current channe : currentPresetNumber " + currentPresetNumber);
	   return currentPresetNumber;
	}
	
	public void PlayChannel(Uri currentUri, Map<String, String> headers)
	{
		
		if(!headers.containsKey(TvHeaders.SELECTION_TYPE)) {
			headers.put(TvHeaders.SELECTION_TYPE,"0");
		}
		Log.i(tag,"setDataSource SelectionType = " + mSelectionType);
		if((mSelectionType == TvURIHelper.SelectionType.SELECTION_HOSTCONTROL) && (Integer.parseInt(headers.get(TvHeaders.SELECTION_TYPE)) != TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value && Integer.parseInt(headers.get(TvHeaders.SELECTION_TYPE)) != TvURIHelper.SelectionType.SELECTION_CAMPMT.value))
		{
			//currentMedium and currentPresetNumber are not be used only uri says the correct values 
			onPlayFailed(currentUri, currentMedium, currentPresetNumber, IPlayTvStateChangeListener.TUNE_FAILED_REASON_CAM_VOD_IN_PROGRESS);
			mPlayTvCIPlusHandler.releaseHC(currentUri,headers);
		}else {
			if(Integer.parseInt(headers.get(TvHeaders.SELECTION_TYPE)) == TvURIHelper.SelectionType.SELECTION_HOSTCONTROL.value || Integer.parseInt(headers.get(TvHeaders.SELECTION_TYPE)) == TvURIHelper.SelectionType.SELECTION_CAMPMT.value){
				mSelectionType = TvURIHelper.SelectionType.SELECTION_HOSTCONTROL;
				if((headers.containsKey(TvHeaders.SERVICE_ID)) && (Integer.parseInt(headers.get(TvHeaders.SERVICE_ID))) == 0){
					headers.put(TvHeaders.SELECTION_TYPE,Integer.toString(TvURIHelper.SelectionType.SELECTION_INSTALL.value)); //Host control tune will be silent!
				} else if(Integer.parseInt(headers.get(TvHeaders.SELECTION_TYPE)) != TvURIHelper.SelectionType.SELECTION_CAMPMT.value) {
					headers.put(TvHeaders.SELECTION_TYPE,Integer.toString(TvURIHelper.SelectionType.SELECTION_SILENT.value)); //Host control tune will be silent!
				}
			}	
			Log.i(tag,"setDataSource SelectionType = " + headers.get("seltype"));
			
			if((headers.containsKey(TvHeaders.MEDIUM)) && (headers.get(TvHeaders.MEDIUM) == Integer.toString(Medium.MEDIUM_SATELLITE.value))) {
				ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
				if(globalSettings != null) {
					if(tvmplayer.getToken()	==	TvMediaPlayer.ROOT_TUNER) {	
						headers.put(TvHeaders.USER_BAND_TUNER,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER,0,0)));
						headers.put(TvHeaders.USER_BAND_FREQUENCY_TUNER,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTSETTINGSUNICABLEFREQUENCYPRIMARYTUNER,0,0)));	
					}else {
						headers.put(TvHeaders.USER_BAND_TUNER,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDSECONDARYTUNER,0,0)));	
						headers.put(TvHeaders.USER_BAND_FREQUENCY_TUNER,Integer.toString(globalSettings.getInt(TvSettingsConstants.INSTSETTINGSUNICABLEFREQUENCYSECONDARYTUNER,0,0)));	
					}
				}
			}
			headers.put(TvHeaders.CI_CAM, hasCicam == true ? "true" : "false");		
			if( ((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) ||
					((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING)) {					
					int noOfCurrentMediumCam 	= 0;
					try {
						CAMDetails camDetails = new CAMDetails();
						CamInfoDB Camdb = CamInfoDB.getInstace(mContext);				
						Medium medium 	= Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));	
						camDetails.setMedium(medium);
						noOfCurrentMediumCam 	= Camdb.getNoOfCAMS(camDetails);
					} catch(Exception e) {
						Log.e(tag,"Exception getting CAM details" + e.getLocalizedMessage());
					}				
					if((isDualTunerEnabled() == true) && ((noOfCurrentMediumCam == 0) || (PlayTvDiversity.isCAMAllocationPrioritySupported() == false))) {
						Log.i(tag,"purpose recording : USERTYPE_RECORDING_LOW added");			
						headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_RECORDING_LOW));
						headers.put(TvHeaders.CI_CAM, "false");
					}
					else {
						Log.i(tag,"purpose recording : USERTYPE_RECORDING_HIGH added");			
						headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_RECORDING_HIGH));
						headers.put(TvHeaders.CI_CAM, "true");
					}	
			}
			else if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) {
				headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_WATCHTV_HIGH));
			}
			else if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_WATCH) {
					headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_WATCHTV_LOW));
			}
			else if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_MONITOR_PIP) {
					if(PlayTvDiversity.isMonitorPIPSupported()){
						//headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_MONITOR_PIP));
					}else {
						headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_WATCHTV_LOW));
					}
			}
			else if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_FOLLOW_MAIN) {
					headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_BACKGROUND));
			}
			else if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_INSTALLER) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_INSTALLER) {
					headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_BACKGROUND));
			}
			else if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_SEMISTDBY) {
				headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_WATCHTV_HIGH));
			}
			else if((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_DATA_ACQUISITION) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_DATA_ACQUISITION) {
				headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_WATCHTV_HIGH));
			}
			else if((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_DATA_ACQUISITION) 
							== PlayTVMediaPlayerFactory.REQUEST_TYPE_DATA_ACQUISITION) {
				headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_BACKGROUND));							
			}
			else if((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_INDEPENDENT_TAD) {
				headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_TAD));					
			}
			else if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_INSTALLER) {
				headers.put(TvHeaders.USER_TYPE, Integer.toString(TvMediaPlayer.USERTYPE_WATCHTV_HIGH));
			}
			headers.put(TvHeaders.COMPLETE_URI,currentUri.toString());		
			if(mplayerStateControl.getPrepareState()!=mediaPlayerStateControl.MPLAYERSTATE_PREPARING){
				synchronized(mplayerStateControl) {
					selectChannel(headers);
				}
			}else {
				mplayerStateControl.pushToStack(headers);
			}
		}
	}
	
	/**
	 * selectChannel has to be called only when there is no previous
	 * selection happening.
	 * @param headers
	 */
	private void selectChannel(Map<String, String> headers) {
		boolean failed=false;
		boolean bootupSelection= false;
		Uri mediaplayerUri = Uri.parse("tv://tuner");
				
		if(headers==null) {
			if(!mplayerStateControl.isStackEmpty()) {
				headers = mplayerStateControl.popFromStack();
			}
		}
		if(headers==null) {
			return;
		}		
		if(headers.containsKey(TvHeaders.USER_TYPE)) {
			mCurrentUserType = Integer.parseInt(headers.get(TvHeaders.USER_TYPE));
		}
		if(headers.get(TvHeaders.MEDIUM) != null) {				
			currentMedium 	= Medium.fromInteger(Integer.parseInt(headers.get(TvHeaders.MEDIUM)));
		}
		if((((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) 
			  == PlayTVMediaPlayerFactory.REQUEST_TYPE_BACKGROUND_RECORDING) || 
			((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING) 
			  == PlayTVMediaPlayerFactory.REQUEST_TYPE_FOREGROUND_RECORDING)) && 
		   ((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)
			  == PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)){
			headers.put(TvHeaders.OLYMPIC_USECASE,Integer.toString(1));
		}
			
		mplayerStateControl.setPrepareState(mediaPlayerStateControl.MPLAYERSTATE_PREPARING);
		
		mCurrentUri = Uri.parse(headers.get(TvHeaders.COMPLETE_URI));
		if(headers.get(TvHeaders.WAKEUP_SELECTION) != null) {				
			bootupSelection = ((Integer.parseInt(headers.get(TvHeaders.WAKEUP_SELECTION))) == 1) ? true : false;
		}					
		if(headers.containsKey(TvHeaders.PRESET_ID)) {
			currentPresetNumber = Integer.parseInt(headers.get(TvHeaders.PRESET_ID));
			Log.d(tag,"PlayChannel "+ currentPresetNumber);
		}else {
			currentPresetNumber = 0;
			Log.d(tag,"PlayChannel no preset number");
		}				
				
		if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) 
				== PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) {
			if(mAnalogDigitalPlayer!=PLAYER_TUNER_INVALID) {
				//Already playing something
				if(headers.containsKey(TvHeaders.MODE)) {
					if(Integer.parseInt(headers.get(TvHeaders.MODE))==TvHeaders.MODE_ANALOG) {
						Log.d(tag,"Going to do Analog Selection");
						if(mAnalogDigitalPlayer!=PLAYER_TUNER_ANALOG) {
							//if previously playing digital and the new selection is analog
							Log.d(tag,"digital->analog player");
							setAVSurface(null);
						}
						mAnalogDigitalPlayer = PLAYER_TUNER_ANALOG; 
						serviceType			 = IChannelContract.SERVICE_TYPE_ANALOG;
					}else {
						Log.d(tag,"Going to do digital Selection");
						if(mAnalogDigitalPlayer!=PLAYER_TUNER_DIGITAL) {
							Log.d(tag,"analog->digital");
							//if previously playing analog and the new selection is digital
							setAVSurface(null);
						}
						mAnalogDigitalPlayer = PLAYER_TUNER_DIGITAL;
						if(currentMedium == Medium.MEDIUM_TERRESTRIAL) {
							serviceType	 = IChannelContract.SERVICE_TYPE_TERRESTRIAL;
						}
						else if(currentMedium == Medium.MEDIUM_CABLE) {
							serviceType	 = IChannelContract.SERVICE_TYPE_CABLE;
						}
						else if(currentMedium == Medium.MEDIUM_SATELLITE) {
							serviceType	 = IChannelContract.SERVICE_TYPE_SATELLITE;
						}
					}
				}
			} else {
				if(headers.containsKey(TvHeaders.MODE)) {
					if(Integer.parseInt(headers.get(TvHeaders.MODE))==TvHeaders.MODE_ANALOG) {
						Log.d(tag,"Going to do Analog Selection");
						mAnalogDigitalPlayer = PLAYER_TUNER_ANALOG;	
						serviceType			 = IChannelContract.SERVICE_TYPE_ANALOG;
					} else {
						Log.d(tag,"Going to do digital Selection");
						mAnalogDigitalPlayer = PLAYER_TUNER_DIGITAL;
						if(currentMedium == Medium.MEDIUM_TERRESTRIAL) {
							serviceType	 = IChannelContract.SERVICE_TYPE_TERRESTRIAL;
						}
						else if(currentMedium == Medium.MEDIUM_CABLE) {
							serviceType	 = IChannelContract.SERVICE_TYPE_CABLE;
						}
						else if(currentMedium == Medium.MEDIUM_SATELLITE) {
							serviceType	 = IChannelContract.SERVICE_TYPE_SATELLITE;
						}
					}
				}
			}
		}
			
		synchronized(mSyncObj) {							
			if(tvmplayer !=null) {
				if(!bootupSelection) {
					if(mAnalogDigitalPlayer==PLAYER_TUNER_ANALOG) {
						if((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)==
							PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) {
							try {
								Log.d(tag,"calling mute");
								tvmplayer.getTvMediaPlayerContext().getTvMediaControl().setMediaMute(ITvMediaControl.MEDIA_AUDIO,true);
								tvmplayer.getTvMediaPlayerContext().getTvMediaControl().setMediaMute(ITvMediaControl.MEDIA_VIDEO,true);
								Log.d(tag,"calling mute done");
							} catch(Exception e) {
								Log.e(tag,"Exception setting setMediaMute " + e.getLocalizedMessage());
							}
						}
					}
				}	
				mtvmpstatus = STOPPED;
				Log.d(tag,"Resetting "+ tvmplayer.hashCode());
				if(headers.get(TvHeaders.DISABLE_AUTO_MUTE) != null) {				
					boolean autoMute = (Integer.parseInt(headers.get(TvHeaders.DISABLE_AUTO_MUTE)) == 1) ? true :false;
					ITvMediaControl tvmc = tvmplayer.getTvMediaPlayerContext().getTvMediaControl();
					if(tvmc != null){
						if(autoMute) {
							Log.i(tag,"Entering NDT Selection : setAutoMute - false");
							tvmc.setAutoMute(false);
						}else {
							Log.i(tag,"Exiting NDT Selection : setAutoMute - true");
							tvmc.setAutoMute(true);
						}	
					}
				}
				if(bootupSelection || ((headers.get(TvHeaders.RESTORE_CHANNEL_STATE) != null) && 
				  (Integer.parseInt(headers.get(TvHeaders.RESTORE_CHANNEL_STATE)) == 1))) {
					tvmplayer.resetOnWakeup();
				} else {
					tvmplayer.reset();
				}
				Log.d(tag,"Resetting done "+ tvmplayer.hashCode());
				/*try {
					Thread.sleep(100);
				} catch(Exception e){
					
				}*/
			}
			mCurrentHeaders	=	headers;
			onPlayStarted(mCurrentUri, mCurrentHeaders, currentMedium, currentPresetNumber);
			
			Log.d(tag,"headers string " + headers.toString());
								
			Log.d(tag,"setDataSource vpid:apid:pcrpid  = " + headers.get("vpid") + ":" + headers.get("apid") + ":" +  headers.get("pcrpid"));
			Log.d(tag,"setDataSource freq = " + headers.get("freq") + "serviceid " + headers.get("sid") + "seltype " + headers.get("seltype"));
			int status = selectchannelRetry(mediaplayerUri,headers);
			if(status==2) {
				tvmplayer.resetOnWakeup();
				status = selectchannelRetry(mediaplayerUri,headers);
			}
			
			if(status!=0) {
				Log.e(tag,"selectChannel failed");
				mplayerStateControl.setPrepareState(mediaPlayerStateControl.MPLAYERSTATE_IDLE);
				onPlayFailed(mCurrentUri, currentMedium, currentPresetNumber, IPlayTvStateChangeListener.TUNE_FAILED_REASON_NONE);
			}
		}
	}
	
	private int selectchannelRetry(Uri mediaplayerUri ,Map<String, String> headers) {
		int status = 0;
		try {
			
			Log.d(tag,"setDataSource##"+tvmplayer.getToken()+"HasCode##"+ tvmplayer.hashCode());
			tvmplayer.setOnCompletionListener(this);
			tvmplayer.setOnErrorListener(this);
			tvmplayer.setOnInfoListener(this);
			tvmplayer.setDataSource(mContext,mediaplayerUri ,headers);
			Log.d(tag,"Calling prepareAsync");
			tvmplayer.prepareAsync();
		} catch (IOException e) {
			Log.e(tag,"setDataSource fails with IOException");
			status=1;
		} catch (IllegalStateException e) {
			Log.e(tag,"setDataSource fails with IllegalStateException");
			status=1;
		} catch (NullPointerException e) {
			Log.e(tag,"setDataSource fails with NullPointerException");
			status=1;
		} catch (SecurityException e) {
			Log.e(tag,"selection fails with SecurityException");
			status=2;
		}
		return status;
	}
	
	public TvMediaPlayer getMediaPlayerInstance()
	{
		return tvmplayer;
	}

	public void setDdrResumeSurface(int enable)
	{
		if (tvmplayer != null)
			tvmplayer.setDdrResumeSurface(enable);
	}

	public void onError(final int what , final int extra) {
		Log.e(tag, "onError received sending to clients");
		Runnable r = new Runnable() {
			@Override
			public void run() {				
				synchronized (listeners) {
					if (playbackListener != null) {
						playbackListener.onError(PlayTvMediaPlayer.this, what , extra);
					}
					for (IPlayTvStateChangeListener listener : listeners) {
						listener.onError(PlayTvMediaPlayer.this, what , extra);
					}
				}
			}
		};
		mhandler.post(r);
		synchronized(mplayerStateControl) {
			mplayerStateControl.setPrepareState(mediaPlayerStateControl.MPLAYERSTATE_IDLE);
		}
		synchronized(lmplayerStateControl) {
			lmplayerStateControl.setPrepareState(localMediaPlayerStateControl.MPLAYERSTATE_IDLE);
		}
	}

	private void onPlayStarted(Uri mediaPlayerUri, Map<String, String> headers, Medium medium, int presetNumber) {
		synchronized (listeners) {
			if(playbackListener!=null) {
				playbackListener.onPlayStarted(mediaPlayerUri, headers, medium, presetNumber);
			}
			for(IPlayTvStateChangeListener listener:listeners) {
				listener.onPlayStarted(mediaPlayerUri, headers, medium, presetNumber);
			}
		}
	}

	private void onPlayCompleted(Uri mediaPlayerUri, Map<String, String> headers, Medium medium, int presetNumber) {
		synchronized (listeners) {
			if((isMediaListenerRegistered == false) && (tvmplayer!= null )){
				isMediaListenerRegistered = RegisterOnMediaChangeListener(tvmplayer);
			}				
            if(mediaPlayerUri != null){
			    Log.d(tag, "onPlayCompleted-"+mediaPlayerUri.toString());
            }
			if(playbackListener!=null) {
				playbackListener.onPlayCompleted(mediaPlayerUri, headers, medium, presetNumber);
			}
			for(IPlayTvStateChangeListener listener:listeners) {
				listener.onPlayCompleted(mediaPlayerUri, headers, medium, presetNumber);
			}
		}
	}

	private void onPlayFailed(Uri mediaPlayerUri, Medium medium, int presetNumber, int reason) {
		synchronized (listeners) {
			Log.e(tag, "onPlayFailed-"+mediaPlayerUri.toString());
			if(playbackListener!=null) {
				playbackListener.onPlayFailed(mediaPlayerUri, medium, presetNumber, reason);
			}
			for(IPlayTvStateChangeListener listener:listeners) {
				listener.onPlayFailed(mediaPlayerUri, medium, presetNumber, reason);
			}
		}
	}
	
	private void onPlayFinished(Uri mediaPlayerUri, Medium medium, int presetNumber) {
		synchronized (listeners) {
			if(playbackListener!=null) {
				playbackListener.onPlayFinished(mediaPlayerUri, medium, presetNumber);
			}
			for(IPlayTvStateChangeListener listener:listeners) {
				listener.onPlayFinished(mediaPlayerUri, medium, presetNumber);
			}
		}
	}
	
	public void onCamUpgradeStarted(final boolean status){
		Runnable r = new Runnable() {
				@Override
				public void run() {
					isCamUpgradeStarted = status;
					if(playbackListener!=null) {
						playbackListener.onCamUpgradeStarted(status);
					}
				}
			};
			mhandler.post(r);
		
    }
	
	public void onHCTuneBack(final Uri channelURI , final Map<String, String> header){
		Runnable r = new Runnable() {
			@Override
			public void run() {
				PlayChannel(channelURI,header); //TO DO - replace with new API of playtvmpl
			}
		};
		mhandler.post(r);
	}
	
	private void onLockStatusChanged(int type, int status) {
		synchronized (listeners) {
			if(playbackListener!=null) {
				playbackListener.onLockStatusChanged(type, status);
			}
			for(IPlayTvStateChangeListener listener:listeners) {
				listener.onLockStatusChanged(type, status);
			}
		}
	}
  
	private void onPurposeChanged(int CurrentPurpose)
	{
		synchronized (listeners) {
			if(playbackListener!=null) {
				playbackListener.onPurposeChanged(CurrentPurpose);
			}
			for(IPlayTvStateChangeListener listener:listeners) {
				listener.onPurposeChanged(CurrentPurpose);
			}
		}
	}

	@Override
	public void onPreparedTv(MediaPlayer mp, Uri CurrentUri, Map<String, String> headers) {
		int currentId = 0;
		Uri currentUri = null;
		Log.d(tag,"onPreparedTv from TvMediaPlayer recieved CurrentUri is " + CurrentUri);
		
		if(headers.containsKey(TvHeaders.COMPLETE_URI)) {
			currentUri = Uri.parse(headers.get(TvHeaders.COMPLETE_URI));
		} else {
			currentUri = mCurrentUri;
		}
		
		if(mAnalogDigitalPlayer==PLAYER_TUNER_ANALOG) {
			if( ((currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH)== 
				PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) && 
				(currentMedium!=Medium.MEDIUM_PVRFILE)) {
					try {
						Log.d(tag,"calling unmute");
						tvmplayer.getTvMediaPlayerContext().getTvMediaControl().setMediaMute(ITvMediaControl.MEDIA_AUDIO,false);
						tvmplayer.getTvMediaPlayerContext().getTvMediaControl().setMediaMute(ITvMediaControl.MEDIA_VIDEO,false);
						Log.d(tag,"calling unmute done");
					} catch(Exception e) {
					Log.e(tag,"Exception setting setMediaMute " + e.getLocalizedMessage());
				}
			}
		}
		
		if(currentUri!=null){
			String flags = currentUri.getQueryParameter("flags");
			if(flags!=null) {
				if((Integer.parseInt(flags) & PlayTvUtils.FLAGS_AUDIOMUTED)>0){
					Log.d(tag,"calling mute");
					tvmplayer.getTvMediaPlayerContext().getTvMediaControl().setMediaMute(ITvMediaControl.MEDIA_AUDIO,true);
					Log.d(tag,"calling mute done");
				}
			}
		}
		
		tvmplayer.start();
		mtvmpstatus = STARTED;
		Log.d(tag,"tvmplayer.start done ");
		if(currentMedium == Medium.MEDIUM_LOCALFILE){
			ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
			if (!lmplayerStateControl.isStackEmpty()) {
				Runnable r = new Runnable() {
					@Override
					public void run() {
						synchronized (lmplayerStateControl) {
							selectLocalChannel(null);
						}
					}
				};
				mhandler.post(r);
			} else {
				onPlayCompleted(currentUri, headers, currentMedium, currentPresetNumber);
			}
			synchronized (lmplayerStateControl) {
				lmplayerStateControl.setPrepareState(localMediaPlayerStateControl.MPLAYERSTATE_PREPARED);
			}
		}else {
			if (!mplayerStateControl.isStackEmpty()) {
				Runnable r = new Runnable() {
					@Override
					public void run() {
						synchronized (mplayerStateControl) {
							selectChannel(null);
						}
					}
				};
				mhandler.post(r);
			} else {
				onPlayCompleted(currentUri, headers, currentMedium, currentPresetNumber);
			}
			synchronized (mplayerStateControl) {
				mplayerStateControl.setPrepareState(mediaPlayerStateControl.MPLAYERSTATE_PREPARED);
			}
		}
	}
		
	public Uri getCurrentUri() {
	
		return mCurrentUri;
		
	}
	
	class MediaChangeListenerClass extends IonMediaChangeListener{			
		@Override
		public void onLockStatusChanged(final int type, final int status)
		{
			Runnable r = new Runnable() {
				@Override
				public void run() {
					PlayTvMediaPlayer.this.onLockStatusChanged(type, status);
				}
			};
			mhandler.post(r);
		}

		@Override
		public void onMediaStateChanged(int media) {
		}

		@Override
		public void onScramblingStatusChanged(int media, int status) {
		}
		
		@Override
		public void OnReplacementSvcTuneRequested(final int onid, final int tsid,final int sid) {
			if( (currentPurpose & PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) 
					== PlayTVMediaPlayerFactory.REQUEST_TYPE_MAIN_WATCH) {
				//thread safe???
				Runnable r = new Runnable() {
					@Override
					public void run() {
						Map<String, String> headers = TvURIHelper.getHeadersForTriplet(mContext,onid,tsid,sid,true);
						if((headers != null) && (headers.size() > 0)) {
							PlayChannel(mCurrentUri, headers); //check mCurrentUri can be used or not
						}
					}
				};
				mhandler.post(r);
			}
		}
	}
	
	private boolean RegisterOnMediaChangeListener(TvMediaPlayer tvmp)
	{	
		try {
			ITvMediaControl tvmc = tvmp.getTvMediaPlayerContext().getTvMediaControl();
			if(mMediaChangeListener==null) {
				mMediaChangeListener = new MediaChangeListenerClass();
			}
			if(tvmc != null){
			    tvmc.registerListenerCallback((IonMediaChangeListener) mMediaChangeListener);
			}
			else {
				Log.e(tag,"tvmc is null medialistener not registered");
				return false;
			}
		}catch(Exception e) {
			Log.e(tag,"Caught exception in RegisterOnMediaChangeListener ");
			return false;
		}
		return true;
	}
	
	private void UnRegisterOnMediaChangeListener(TvMediaPlayer tvmp) {
		try {
			ITvMediaControl tvmc = tvmp.getTvMediaPlayerContext().getTvMediaControl();	
			tvmc.unRegisterListenerCallback((IonMediaChangeListener) mMediaChangeListener);
			mMediaChangeListener = null;
		} catch(Exception e) {
			Log.e(tag,"Caught exception in UnRegisterOnMediaChangeListener ");
		}
	}
	
	public void setLockStatus(int type, int status)
	{
		try {
			ITvMediaControl tvmc = tvmplayer.getTvMediaPlayerContext().getTvMediaControl();
			tvmc.setLockStatus(type, status);
			Log.i(tag,"setLockStatus done");
		} catch(Exception e ) {
			Log.e(tag,"Caught exception calling setLockstatus");
		}
	}

	public void enableLocking(boolean enable)
	{
		try {
			ITvMediaControl tvmc = tvmplayer.getTvMediaPlayerContext().getTvMediaControl();
			tvmc.enableLocking(enable);
			Log.i(tag,"enableLocking done");
		} catch(Exception e ) {
			Log.e(tag,"Caught exception calling enableLocking");
		}
	}
	
	@Override
	public void onCompletion(MediaPlayer mp) {
		onPlayFinished(mCurrentUri, currentMedium, currentPresetNumber);
	}
	
	public void setAVSurface(Surface s) {
		boolean isValid = true;
		synchronized (mSyncObj) {
			if(s==null) {
				isValid = false;
			}
			if((mCurrentUserType == TvMediaPlayer.USERTYPE_WATCHTV_HIGH) ||
			   (mCurrentUserType == TvMediaPlayer.USERTYPE_WATCHTV_LOW)  || 
			   (mCurrentUserType == TvMediaPlayer.USERTYPE_RECORDING_HIGH) ||
			   (mCurrentUserType == TvMediaPlayer.USERTYPE_RECORDING_LOW) ||
			   (mCurrentUserType == TvMediaPlayer.USERTYPE_TAD)) {
				try{
					Log.d(tag,"setAVSurface Started " + isValid);
						tvmplayer.setSurface(s);
						if(isValid) {
							isSetSurfaceRequired = false;
						} else {
							isSetSurfaceRequired = true;
						}
					}catch(Exception e) {
					Log.e(tag,"Exception in setSurface "+ e.getLocalizedMessage());
				}
				Log.d(tag,"setAVSurface End " + isValid);
			}
			else
			{
				Log.d(tag,"playtvmediaplayer : setAvSurface on incorrect usecase - usertpe : "+mCurrentUserType);
			}
		}
	}
    

	
	public void hcReleased(){
		Log.d(tag,"hcRelease HC status to idle");
		mSelectionType = null;
	}

	public ClockHandler getClockHandler() {
		return clkHandler;
	}
		
	@Override
	public boolean onInfo(MediaPlayer mp, int what, int extra) {
		Log.d(tag, "OnInfo: mp " + mp + " what " + what + " extra " + extra);
		if((what == TvMediaPlayer.MEDIA_RESOURCE_NOT_AVAILABLE) && (((extra & TvMediaPlayer.RESID_CAM0) == TvMediaPlayer.RESID_CAM0) 
			|| ((extra & TvMediaPlayer.RESID_CAM1) == TvMediaPlayer.RESID_CAM1))) {
			synchronized (listeners) {
				if(playbackListener!=null) {
					playbackListener.onInfo(false);
				}
				for(IPlayTvStateChangeListener listener:listeners) {
					listener.onInfo(false);
				}
			}
		}
		else if((what == TvMediaPlayer.MEDIA_RESOURCE_AVAILABLE) && (((extra & TvMediaPlayer.RESID_CAM0) ==  TvMediaPlayer.RESID_CAM0)
			|| ((extra & TvMediaPlayer.RESID_CAM1) == TvMediaPlayer.RESID_CAM1))) {
			synchronized (listeners) {
				if(playbackListener!=null) {
					playbackListener.onInfo(true);
				}
				for(IPlayTvStateChangeListener listener:listeners) {
					listener.onInfo(true);
				}
			}
		}
		return true;
	}

	@Override
	public boolean onError(MediaPlayer mp, int what, int extra) {
		onError(what, extra);
		return true;
	}
	
	public int getUnderlyingPlayer() {
		Log.v(tag,"getUnderlyingPlayer returns value " + mUnderlyingPlayer);
		return mUnderlyingPlayer;
	}

	public void setUnderlyingPlayer(int mUnderlyingPlayer) {
		Log.v(tag,"setUnderlyingPlayer called value " + mUnderlyingPlayer);
		this.mUnderlyingPlayer = mUnderlyingPlayer;
	}

	public boolean isSetSurfaceRequired() {
		return this.isSetSurfaceRequired;
	}
	
	private void onUriChanged() {
		if(listeners != null && mCurrentUri != null) {
			for(IPlayTvStateChangeListener listener : listeners) {
				listener.onUriChanged(mCurrentUri);
			}
		}
		if(playbackListener!= null ) {
			playbackListener.onUriChanged(mCurrentUri);
		}		
	}
	
	public void startTimeshiftPause() {
		Log.v(tag,"startTimeshiftPause:mCurrentUri="+mCurrentUri);
		if (mCurrentUri != null && mCurrentUri.getQueryParameter("playback") == null) {
			mOrginalUri = Uri.parse(mCurrentUri.toString());
			Uri.Builder uriBuilder = mCurrentUri.buildUpon();
			uriBuilder.appendQueryParameter("playback", "LIVE_PAUSE");
			mCurrentUri = uriBuilder.build();
			onUriChanged();
		} 
	}

	public void startTimeshiftPlayback() {
		Log.v(tag,"startTimeshiftPlayback:mCurrentUri="+mCurrentUri);
		if (mCurrentUri != null) {
			mCurrentUri = mOrginalUri;
			Uri.Builder uriBuilder = mCurrentUri.buildUpon();
			uriBuilder.appendQueryParameter("playback", "URL_PLAY");
			mCurrentUri = uriBuilder.build();
			onUriChanged();
		} 
	}
	
	public void stopTimeshiftPlayback() {	
		if(mOrginalUri != null && mCurrentUri != null) {
			mCurrentUri = mOrginalUri;
			mOrginalUri = null;
		}
		Log.v(tag, "mCurrentUri="+mCurrentUri +" mOrginalUri="+mOrginalUri);
		onUriChanged();
	}
	
	public void suppressMute(){	
		Log.v(tag,"suppressMute called");
		try{
			tvmplayer.getTvMediaPlayerContext().getTvMediaControl().setMediaMute(ITvMediaControl.RESET_ALL_MEDIA,false);	
		}
		catch(Exception e){
			Log.e(tag,"exception caught ");
		}
	}
	
	public void restoreMute(){
		Log.v(tag,"restoreMute called");
		try{
			tvmplayer.getTvMediaPlayerContext().getTvMediaControl().setMediaMute(ITvMediaControl.RESET_ALL_MEDIA,true);		
		}
		catch(Exception e){
			Log.e(tag,"exception caught ");
		}
	}
	
	public void clearCurrentUri() {
		mCurrentUri 		= null;
		currentPresetNumber = 0;
		currentMedium 		= Medium.MEDIUM_INVALID;
	}
	public void enableCAMUI(boolean enable) {
			Log.v(tag,"enableCAMUI called");
			if(mPlayTvCIPlusHandler != null)
			mPlayTvCIPlusHandler.enableCAMUI(enable);
	}
	
	public CamInfoImpl getCamInfo(int slotId){
			if(mPlayTvCIPlusHandler != null){
				return mPlayTvCIPlusHandler.getCamInfo(slotId);
			}
			return null;
    }
}
