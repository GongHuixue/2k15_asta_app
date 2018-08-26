package org.droidtv.tunerservice.overlay;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.TextureView;
import android.view.View;
import android.view.WindowManager;
import android.view.ViewGroup.LayoutParams;
import android.widget.FrameLayout;
import android.view.KeyEvent;
import java.util.HashSet;
import org.droidtv.tunerservice.interfaces.IOverlayListener;
import org.droidtv.tunerservice.R;

// Reno 20150420 HTV show on screen clock on radio channel
import android.content.Intent;
import android.content.IntentFilter;
import org.droidtv.tunerservice.overlay.HtvRadioChOscView;
// Reno
/*======== haishan.lin@xmic 2015.11.21 #  Logging OSC on Radio Channel start ========= */
import org.droidtv.tv.logger.ILogger;
import android.content.ServiceConnection;
import android.content.ComponentName;
import android.os.IBinder;
/*======== haishan.lin@xmic 2015.11.21 #  Logging OSC on Radio Channel end ========= */

public class OverlayManager {
	
	public static final int VIEW_RADIO_BG 		= 1;
	public static final int VIEW_SUBTITLES 		= 2;
	public static final int VIEW_INTERACTIVEAPP = 3;
	public static final int VIEW_AMMI_1 		= 4;
	public static final int VIEW_AMMI_2 		= 5;
	public static final int VIEW_IAPP_BG		= 6;
	public static final int VIEW_REC_ICON		= 7;
	public static final int VIEW_OSC			= 8; // Reno 20150420 HTV show on screen clock on radio channel
	public static final int VIEW_IMG_CH		= 9;
	
	private static final String TAG_RADIO		= "Radio";
	private static final String TAG_SUBTITLES	= "Subtitles";
	private static final String TAG_IAPP		= "IApp";
	private static final String TAG_AMMI_1		= "Ammi1";
	private static final String TAG_AMMI_2		= "Ammi2";
	private static final String TAG_REC_ICON	= "RecIcon";
	private static final String TAG_IAPPBG		= "IAppBG";
	private static final String TAG_OSC 		= "OnScreenClock"; // Reno 20150420 show on screen clock on radio channel
	private static final String TAG_IMCH		= "ImageCH";
	
	private static final int DEFAULT_WIDTH 	= 1920;
	private static final int DEFAULT_HEIGHT = 1080;

	private Context mContext 		= null;
	private View radioView 			= null;
	private View oscView			= null; // Reno 20150420 HTV show on screen clock on radio channel
	private FrameLayout frameLayout = null;
	private Handler mhandler 		= null;
	private boolean isChannel		= true;
	private String TAG 				= "OverlayManager";
	private static LayoutParams mMatchParentLP = null;
		
	// Reno 20150420 show on screen clock on radio channel (modifies)
	private String [] mZorderPlay 	= {TAG_IAPPBG,TAG_RADIO,TAG_SUBTITLES,TAG_IAPP,TAG_AMMI_1,TAG_AMMI_2,TAG_REC_ICON, TAG_OSC};
	private String [] mZorderRPlay 	= {TAG_RADIO,TAG_SUBTITLES, TAG_OSC};
	
	private int ammiPurpose[] = {-1,-1};
	private int mMetricsWidth = DEFAULT_WIDTH;
	private int mMetricsHeight = DEFAULT_HEIGHT;
	private HashSet<IOverlayListener> mOverlayListenerList;
	private boolean mOverlayEnabled = false;
    /*======== haishan.lin@xmic 2015.11.21 #  Logging PowerStateTransition:Quick Clock start ========= */
    protected static ILogger mBinder = null;
    ILogger.OSCEventTrigger mOSCTrigger = null;
    /*======== haishan.lin@xmic 2015.11.21 #  Logging PowerStateTransition:Quick Clock end ========= */

	public OverlayManager(Context mContext) {
		
		this.mContext = mContext;
        mOSCTrigger = new ILogger.OSCEventTrigger();
		mhandler = new Handler(Looper.getMainLooper());
		mOverlayListenerList = new HashSet<IOverlayListener>();
		LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		setMatchParentLP(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT));
		try {
			DisplayMetrics outMetrics = new DisplayMetrics();
			WindowManager mWindowManager = (WindowManager) mContext.getSystemService(Context.WINDOW_SERVICE);
			mWindowManager.getDefaultDisplay().getMetrics(outMetrics);
			mMetricsWidth = outMetrics.widthPixels;
			mMetricsHeight = outMetrics.heightPixels;
			Log.d(TAG,"mMetricsWidth : "+mMetricsWidth+"mMetricsHeight : "+mMetricsHeight);
			
		} catch(Exception e) {
			Log.d(TAG,"Exception getting metrics");
		}
		
		Log.d(TAG,"width=" + mMetricsWidth + " height=" + mMetricsHeight);
		
		frameLayout = new FrameLayout(mContext);
		FrameLayout.LayoutParams params = getDefaultLayoutParams();
		frameLayout.setLayoutParams(params);

		radioView = inflater.inflate(R.layout.radio_bg, null);
		radioView.setId(VIEW_RADIO_BG);
		// RENO TODO invalid date and time condition
		// Reno 20150420 show on screen clock on radio channel
		oscView = new HtvRadioChOscView(mContext);
		oscView.setId(VIEW_OSC);
		// Reno
			
		updateViewZOrder();
		printZorder();
	}
			
	private static void setMatchParentLP(LayoutParams layoutParams) {
		// TODO Auto-generated method stub
		mMatchParentLP=layoutParams;
	}

	public View getOverlayView() {		
		return frameLayout;
	}
	
	public void release() {
		synchronized (mOverlayListenerList) {
			for(IOverlayListener listener:mOverlayListenerList) {
					listener.releaseOverlayManager();
			}
			mOverlayListenerList = null;
		}
	}
	
	public void registerForOverlayCallback(IOverlayListener listener){
		mOverlayListenerList.add(listener);
	}
	
	public void removeSubtitleView() {
		Log.d(TAG,"removeSubtitleView called");
		Runnable r = new Runnable() {
			@Override
			public void run() {
				Log.d(TAG,"removeSubtitleView runnable");
				View cview = null;
				cview = frameLayout.findViewWithTag(TAG_SUBTITLES);
				if(cview!=null) {
					removeView(cview);
					updateViewZOrder();
				}
			}
		};
		mhandler.post(r);
		Log.d(TAG,"removeSubtitleView posted");
	}

	public void addSubtitleView(final TextureView nSurfaceView) {
		Log.d(TAG,"addSubtitleView called");
		Runnable r = new Runnable() {
			@Override
			public void run() {
				Log.d(TAG,"addSubtitleView runnable");
				try {
					View cview = null;
					cview = frameLayout.findViewWithTag(TAG_SUBTITLES);
					nSurfaceView.setId(VIEW_SUBTITLES);
					if(cview!=null) {
						removeView(cview);
					}
					addView(mMatchParentLP,TAG_SUBTITLES,nSurfaceView);
					updateViewZOrder();
				} catch(Exception e) {
					Log.d(TAG,"Exception  " + e.getLocalizedMessage());
				}
				Log.d(TAG,"addSubtitleView done");
				printZorder();
			}
		};
		mhandler.post(r);
		Log.d(TAG,"addSubtitleView posted");
	}
	
	public void addRadioView() {
		Runnable r = new Runnable() {
			@Override
			public void run() {
			 View v = frameLayout.findViewWithTag(TAG_RADIO); 
				if(v==null) {
					addView(mMatchParentLP,TAG_RADIO,radioView);
					updateViewZOrder();
				}
			}
		};
		mhandler.post(r);
	}
	
	public void removeRadioView() {
		Runnable r = new Runnable() {
			@Override
			public void run() {
			   View v = frameLayout.findViewWithTag(TAG_RADIO); 
				if(v!=null) {
					removeView(radioView);
					updateViewZOrder();
				}
			}
		};
		mhandler.post(r);
	}

	// Reno 20150420 HTV show on screen clock on radio channel
	public void addRadioChOscView() {
		Runnable r = new Runnable() {
			@Override
			public void run() {
				//Log.d(TAG, "HTV - show on screen clock on radio channel");
				View v = frameLayout.findViewWithTag(TAG_OSC);
				if (v == null) {
					addView(mMatchParentLP,TAG_OSC, oscView);
					mContext.registerReceiver(HtvRadioChOscView.HtvRadioChOscReceiver, HtvRadioChOscView.oscIntentFilter);
					updateViewZOrder();
                    logOSCEventTrigger();   //haishan.lin@xmic 2015.11.21 #  Logging OSC on Radio Channel start
				}
			}
		};
		mhandler.post(r);
	}

	public void removeRadioChOscView() {
		Runnable r = new Runnable() {
			@Override
			public void run() {
				//Log.d(TAG, "HTV - remove on screen clock on radio channel");
				View v = frameLayout.findViewWithTag(TAG_OSC);
				if (v != null) {
					removeView(oscView);
					mContext.unregisterReceiver(HtvRadioChOscView.HtvRadioChOscReceiver);
					updateViewZOrder();
				}
			}
		};
		mhandler.post(r);
	}
	// Reno

	public void addRecordingIcon(final View recView) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
			 View v = frameLayout.findViewWithTag(TAG_REC_ICON);				
				if(v==null) {
					int width = mContext.getResources().getDimensionPixelOffset(R.dimen.rec_icon_width);
					int height= mContext.getResources().getDimensionPixelOffset(R.dimen.rec_icon_height);
					FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(width, height);
					recView.setX(mMetricsWidth-width);
					recView.setY(0);
					params.setMargins(0, 0, 0, 0);
					addView(params,TAG_REC_ICON,recView);
					updateViewZOrder();	
					printZorder();
				}
			}
		};
		mhandler.post(r);
	}
	
	public void removeRecordingIcon(final View recView) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
			   View v = frameLayout.findViewWithTag(TAG_REC_ICON); 
				if(v!=null) {
					removeView(recView);
					updateViewZOrder();
					printZorder();
				}
			}
		};
		mhandler.post(r);
	}

	public void addImageChView(final View chView) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
			 View v = frameLayout.findViewWithTag(TAG_IMCH);				
				if(v==null) {
					int width = 1280;
					int height= 768;
					FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(mMetricsWidth, mMetricsHeight);
					chView.setX(0);
					chView.setY(0);
					params.setMargins(0, 0, 0, 0);
					addView(params,TAG_IMCH,chView);
					updateViewZOrder();	
					printZorder();
				}
			}
		};
		mhandler.post(r);
	}
	
	public void removeImageChView(final View chView) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
			   View v = frameLayout.findViewWithTag(TAG_IMCH); 
				if(v!=null) {
					removeView(chView);
					updateViewZOrder();
					printZorder();
				}
			}
		};
		mhandler.post(r);
	}

	
	private void removeView(View v) {
		frameLayout.removeView(v);
	}
	
	private void addView(LayoutParams params, String tag, View nView) {
		nView.setLayoutParams(params);
		nView.setTag(tag);
		frameLayout.addView(nView);
	}
			
	private void printZorder() {
		int count =frameLayout.getChildCount();
		for(int i=0;i<count;i++) {
			Log.d(TAG,"View at " + i + "->" + frameLayout.getChildAt(i).getTag());
		}
	}
	
	private void updateViewZOrder() {
		if(isChannel) {
			for(int i=0;i<mZorderPlay.length;i++) {
				View v = frameLayout.findViewWithTag(mZorderPlay[i]);
				if(v!=null) {
					v.bringToFront();
				}
			}
		} else {
			for(int i=0;i<mZorderRPlay.length;i++) {
				View v = frameLayout.findViewWithTag(mZorderRPlay[i]);
				if(v!=null) {
					v.bringToFront();
				}
			}
		}
	}
	
	public FrameLayout.LayoutParams getDefaultLayoutParams() {
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(mMetricsWidth,mMetricsHeight);
		params.setMargins(0, 0, 0, 0);
		return params;
	}
	
	public void addAMMIView(final TextureView nSurfaceView, final int type) {
		Log.d(TAG,"addAMMIView called:"+nSurfaceView.toString());
		
		Runnable r = new Runnable() {
			@Override
			public void run() {
				Log.d(TAG,"addAMMIView runnable:type->"+type);
				try {
					String mytag=null;
					int id = -1;
					if(ammiPurpose[0] == type){
						Log.d(TAG,"addAMMIView ammiPurpose[0] is already added");
					} else  if(ammiPurpose[1] == type){
						Log.d(TAG,"addAMMIView ammiPurpose[1] is already added");
						}
					else {
						if(ammiPurpose[0]==-1) {
							ammiPurpose[0]=type;
							mytag =  TAG_AMMI_1;
							id = VIEW_AMMI_1;
						}
						else if(ammiPurpose[1]==-1){
							ammiPurpose[1]=type;
							mytag =  TAG_AMMI_2;
							id = VIEW_AMMI_2;
						}
						if(frameLayout.findViewWithTag(mytag)==null) {
							nSurfaceView.setId(id);
							addView(mMatchParentLP,mytag,nSurfaceView);
							updateViewZOrder();
						}
					}
				} catch(Exception e) {
					Log.d(TAG,"Exception  " + e.getLocalizedMessage());
				}
				Log.d(TAG,"addAMMIView done");
				printZorder();
			}
		};
		mhandler.post(r);
		Log.d(TAG,"addAMMIView posted");
	}
	
	public void removeAMMIView(final int type) {
		Log.d(TAG,"removeAMMIView called");
		Runnable r = new Runnable() {
			@Override
			public void run() {
				Log.d(TAG,"removeAMMIView runnable");
				View cview = null;
				String mytag=null;
				if(ammiPurpose[0]==type) {
					mytag =  TAG_AMMI_1;
					ammiPurpose[0] = -1;
					cview = frameLayout.findViewWithTag(mytag);
					removeView(cview);
					if(ammiPurpose[1]!=-1){
						ammiPurpose[0] = ammiPurpose[1];
						ammiPurpose[1] = -1;
						mytag = TAG_AMMI_2;
						cview = frameLayout.findViewWithTag(mytag);
						cview.setTag(TAG_AMMI_1);
					}
				} else if(ammiPurpose[1]==type) {
					mytag =  TAG_AMMI_2;
					ammiPurpose[1] = -1;
					cview = frameLayout.findViewWithTag(mytag);
					removeView(cview);
				}
				Log.d(TAG,"removeAMMIView runnable done");
				updateViewZOrder();
				printZorder();
			}
		};
		mhandler.post(r);
	}
	
	public void removeIAPPView(){
		Runnable r = new Runnable() {
			@Override
			public void run() {
				View cview = frameLayout.findViewWithTag(TAG_IAPP);
				if(cview!=null){
					cview.setTag("");
					removeView(cview);
					updateViewZOrder();
					printZorder();
				}
			}
		};
		mhandler.post(r);
	}
	
	public void addIAPPView(final TextureView view){
		Log.d(TAG,"addIAPPView");
		Runnable r = new Runnable() {
			@Override
			public void run() {
				View cview = frameLayout.findViewWithTag(TAG_IAPP);
				if(cview==null){
					addView(mMatchParentLP,TAG_IAPP,view);
					updateViewZOrder();
					printZorder();
				}
			}
		};
		mhandler.post(r);
	}
	
	public void addIAPPBGView(final View view) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
				View cview = frameLayout.findViewWithTag(TAG_IAPPBG);
				if(cview==null){
					addView(mMatchParentLP,TAG_IAPPBG,view);
					updateViewZOrder();
					printZorder();
				}
			}
		};
		mhandler.post(r);
	}
	
	public void removeIAPPBGView(){
		Runnable r = new Runnable() {
			@Override
			public void run() {
				View cview = frameLayout.findViewWithTag(TAG_IAPPBG);
				if(cview!=null){
					removeView(cview);
					updateViewZOrder();
					printZorder();
				}
			}
		};
		mhandler.post(r);
	}
	
	public void setOverlayViewEnabled(boolean enable) {
		mOverlayEnabled = enable;
	}
	
	public boolean isOverLayEnabled() {
		return mOverlayEnabled;
	}

	private boolean dispatchKeyEvent(KeyEvent event){
		if(isChannel) {
			for(int i=mZorderPlay.length-1;i>=0;i--) {
				View v = frameLayout.findViewWithTag(mZorderPlay[i]);
				if(v!=null) {
					if(v.dispatchKeyEvent(event)){
						return true;
					}
				}
			}
		} else {
			for(int i=mZorderRPlay.length-1;i>=0;i--) {
				View v = frameLayout.findViewWithTag(mZorderRPlay[i]);
				if(v!=null) {
					if(v.dispatchKeyEvent(event)){
						return true;
					}
				}
			}
		}
		return false;
	}

	private boolean dispatchKeyEventForSxp(KeyEvent event){
		if(isChannel) {
				View v = frameLayout.findViewWithTag(TAG_IAPP);
				if(v!=null) {
					if(v.dispatchKeyEvent(event)){
						return true;
					}
				}
			
		}
		return false;
	}
	
	public boolean	onKeyDown(int keyCode, KeyEvent event){
		Log.i(TAG,"onKeyDown called with keyCode = "+ keyCode);	
		
		if ( keyCode == KeyEvent.KEYCODE_HTV_SXP_MHEG_DISPLAY_ON || keyCode == KeyEvent.KEYCODE_HTV_SXP_MHEG_DISPLAY_OFF )
		{
			//this added for SXP to display on/off MHEG
			KeyEvent new_event;
			if ( keyCode == KeyEvent.KEYCODE_HTV_SXP_MHEG_DISPLAY_ON) {
				keyCode = KeyEvent.KEYCODE_PROG_RED;
				new_event =  new KeyEvent(event.getAction(), keyCode);//0--action down
			} else {
				keyCode = KeyEvent.KEYCODE_BACK;
				new_event = new KeyEvent(event.getAction(), keyCode);//0--action down
			}

			Log.i(TAG,"onKeyDown called after changed with keyCode = "+ keyCode );		
			return dispatchKeyEventForSxp( new_event );
		}
		return dispatchKeyEvent(event);
	}
	
	public boolean	onKeyUp(int keyCode, KeyEvent event){
		Log.i(TAG,"onKeyUp called with keyCode = "+ keyCode);
		
		if ( keyCode == KeyEvent.KEYCODE_HTV_SXP_MHEG_DISPLAY_ON || keyCode == KeyEvent.KEYCODE_HTV_SXP_MHEG_DISPLAY_OFF )
		{
			//this added for SXP to display on/off MHEG
			KeyEvent new_event;
			if ( keyCode == KeyEvent.KEYCODE_HTV_SXP_MHEG_DISPLAY_ON) {
				keyCode = KeyEvent.KEYCODE_PROG_RED;
				new_event = new KeyEvent(event.getAction(), keyCode);//1--action up
			} else {
				keyCode = KeyEvent.KEYCODE_BACK;
				new_event = new KeyEvent(event.getAction(), keyCode);//1--action up
			}

			Log.i(TAG,"onKeyUp called after changed with keyCode = "+ keyCode );	
			return dispatchKeyEventForSxp( new_event );
		}
		return dispatchKeyEvent(event);
	}

	@Override
	protected void finalize() throws Throwable {
		Log.d(TAG,"finalize called " + this);
		super.finalize();
	}
	
	public void	setOverLayViewStatus(int overlayViewStatus){
		if(mOverlayListenerList != null){
			synchronized (mOverlayListenerList) {
				for(IOverlayListener listener:mOverlayListenerList) {
						listener.setOverLayViewStatus(overlayViewStatus);
				}
			}
		}
	}
    /*======== haishan.lin@xmic 2015.11.21 #  Logging OSC on Radio Channel start ========= */
    private ServiceConnection conn = new ServiceConnection()
	{

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG, " onServiceConnected callback received");
			mBinder = ILogger.Instance.asInterface(service);
            mBinder.Log(mOSCTrigger);

		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d(TAG, "received onServicedisconnected for LoggingHelper, shut this service");
			mBinder = null;
		}
	};

	private void bindToLoggingService() {
		Intent intent = new Intent();
		intent.setAction("org.droidtv.tv.intent.action.START_LOGGER");
		try {
			boolean serviceBound = mContext.getApplicationContext().bindService(intent, conn, Context.BIND_AUTO_CREATE);
			Log.d(TAG, " bindToLoggingService, servicebound=" + serviceBound);
		} catch (SecurityException e) {
			Log.d(TAG, "bindToLoggingService caught Security Exception : " + "" + e.getLocalizedMessage());
		} catch (Exception e) {
			Log.d(TAG, "bindToLoggingService caught exception :: Could bind to service : " + "" + e.getLocalizedMessage());
		}
	}

    private void logOSCEventTrigger(){
        mOSCTrigger.clock_event_type = ILogger.OSCEventTrigger.ClockEventType.ON_RADIO_CHANNELS;
        mOSCTrigger.power_state_at_trigger = ILogger.OSCEventTrigger.PowerStateTrigger.ON;
        if(mBinder == null){
            bindToLoggingService();
        }else{
            mBinder.Log(mOSCTrigger);
        }
    }
    /*======== haishan.lin@xmic 2015.11.21 #  Logging OSC on Radio Channel end ========= */
}
