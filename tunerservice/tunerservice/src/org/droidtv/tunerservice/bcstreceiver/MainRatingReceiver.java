package org.droidtv.tunerservice.bcstreceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import org.droidtv.tv.context.TvIntent;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;
import org.droidtv.tunerservice.tvmanager.MainTVManager;
import org.droidtv.tunerservice.tvmanager.AuxTVManager;
import android.os.HandlerThread;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;

public class MainRatingReceiver extends BroadcastReceiver{
	private static final String LOG_TAG = "MainRatingReceiver";
//	private MainRatingHandler mRatingHandler;
//	private Looper mRatingLooper;
	static final int BLOCKED_RATINGS_CHANGED = 1;
	static final int PARENTAL_CONTROLS_ENABLED_CHANGED = 2;
	static final int ACTION_POWER_BOOT_COMPLETED = 3;
	
	public MainRatingReceiver() {
	
//		HandlerThread thread = new HandlerThread("MainRatingReceiverThread");
//		thread.start();
//		// Get the HandlerThread's Looper and use it for our Handler
//		mRatingLooper = thread.getLooper();
//		mRatingHandler = new MainRatingHandler(mRatingLooper);
			
	}
	
//	private final class MainRatingHandler extends Handler {
//	
//		public MainRatingHandler(Looper looper) {
//			super(looper);
//		}
//		
//		
//		@Override
		public synchronized void handleMessage(int msg) {
		
			switch (msg)
			{
			
				case BLOCKED_RATINGS_CHANGED:
					
					if ( MainTVManager.getMainRatingInterfaceInstance() != null ) {
						MainTVManager.getMainRatingInterfaceInstance().setParentalRating();
					}
					if ( AuxTVManager.getAuxRatingInterfaceInstance() != null ) {
						AuxTVManager.getAuxRatingInterfaceInstance().setParentalRating();
					}
					break;
					
				case PARENTAL_CONTROLS_ENABLED_CHANGED:
					if ( MainTVManager.getMainRatingInterfaceInstance() != null ) {
						MainTVManager.getMainRatingInterfaceInstance().enableRating();
					}
					if ( AuxTVManager.getAuxRatingInterfaceInstance() != null ) {
						AuxTVManager.getAuxRatingInterfaceInstance().enableRating();
					}
					break;
					
				case ACTION_POWER_BOOT_COMPLETED:
					if ( MainTVManager.getMainRatingInterfaceInstance() != null ) {
						MainTVManager.getMainRatingInterfaceInstance().setDefaultRating();
					}
					break;
					
				default:
					break;
			
			}
		
		}
	
//	}
		
		@Override
		public void onReceive(Context context, Intent intent) 
		{
			Log.i(LOG_TAG," onReceive called : " + intent.getAction());
			final String action = intent.getAction();
			
			if ("android.media.tv.action.BLOCKED_RATINGS_CHANGED" == action)	
			{
			    Log.i(LOG_TAG,"BLOCKED_RATINGS_CHANGED intent is received");
				
//				Message msgObj = new Message();
//				int msgObj.arg1 = ;
				handleMessage(BLOCKED_RATINGS_CHANGED);
				
				
			}
/*
			if ("android.media.tv.action.PARENTAL_CONTROLS_ENABLED_CHANGED" == action)
			{
				Log.i(LOG_TAG," PARENTAL_CONTROLS_ENABLED_CHANGED intent is received");
				
				Message msgObj = new Message();
				msgObj.arg1 = PARENTAL_CONTROLS_ENABLED_CHANGED;
				mRatingHandler.sendMessage(msgObj);
				
				
			}
*/
			if ( action.equals(TvIntent.ACTION_POWER_BOOT_COMPLETED) ) 
			{
				Log.i(LOG_TAG," ACTION_BOOT_COMPLETED intent is received");
				
//				Message msgObj = new Message();
//				msgObj.arg1 = ACTION_POWER_BOOT_COMPLETED;
				handleMessage(ACTION_POWER_BOOT_COMPLETED);
				
				
			}

		}
}
