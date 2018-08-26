package org.droidtv.tunerservice.util;

import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.util.Log;

public abstract class LooperTimer {
	private HandlerThread		mThread;
	private Handler				mHandler;
	private int					mTimerIntervalMs;
	private boolean				mRepetativeTimer;
    
    private final String tag = "TimerImpl";

	private static final int mTIMER_WHAT			= 0xdeadbaad;
	private static final int mTIMER_DELAY 			= 0x1;
	private static final int mTIMER_TIMER 			= 0x2;
	private static final int mTIMER_DELAY_IMMEDIATE = 0x3;

	public LooperTimer() {
		
	}
	
	public void LooperTimerInit(){
		mThread = new HandlerThread("Generic-Timer");
		mThread.start();
		mHandler = new Handler(mThread.getLooper()) {

			@Override
			public void handleMessage(Message msg) {
                Log.d(tag, "HandleMessage");
				Message	nextMsg = new Message();
				switch (msg.arg1) {
				case mTIMER_DELAY_IMMEDIATE:
					timerHandler();
					nextMsg.arg1	= mTIMER_TIMER;
					nextMsg.what 	= mTIMER_WHAT;
					if (mHandler != null) {
						mHandler.sendMessageDelayed(nextMsg, mTimerIntervalMs);
					}
					break;
				case mTIMER_DELAY:
					nextMsg.arg1	= mTIMER_TIMER;
					nextMsg.what 	= mTIMER_WHAT;
					if (mHandler != null) {
						mHandler.sendMessageDelayed(nextMsg, mTimerIntervalMs);
					}
					break;
				case mTIMER_TIMER:
				default:
					timerHandler();
					if (true == mRepetativeTimer) {
						nextMsg.arg1	= mTIMER_TIMER;
						nextMsg.what 	= mTIMER_WHAT;
						if (mHandler != null) {
							mHandler.sendMessageDelayed(nextMsg, mTimerIntervalMs);
						}
					}
				}
				super.handleMessage(msg);
			}
		};
	}

	/**
	* The task to be done should be implemented in the {@code timerHandler()}
	* method. Make sure that the handler is light
	*/
	public abstract void timerHandler();
	
	/**
	 * This API is used to stop the timer.
	 * @warning Timer becomes obsolete and cannot be started after this
	 */
	public void stopTimer() {
        Log.d(tag, "StopTimer");
		mHandler.removeCallbacksAndMessages(null);
		mThread.quitSafely();
		mHandler = null;
		mThread = null;
	}
	
	/**
	 * Restart a timer that is running with new interval.
	 *
	 * @param intervalMs	: Timer interval in milli seconds
	 * @param repeat		: Set false for one shot timer.
	 * @param sendDelayMs	: Delay in milli seconds after which timer should be
	 * started
	 */
	public void resetTimer(int intervalMs, boolean repeat, int sendDelayMs) {
        Log.d(tag, "resetTimer");
		if (mHandler != null) {
			mHandler.removeMessages(mTIMER_WHAT);
		}
		startTimer(intervalMs, repeat, sendDelayMs);
	}
	
	/**
	 * Starts the timer.
	 *
	 * @param intervalMs	: Timer interval in milli seconds
	 * @param repeat		: Set false for one shot timer.
	 * @param sendDelayMs	: Delay in milli seconds after which timer should be
	 * started
	 */
	public void startTimer(int intervalMs, boolean repeat, int sendDelayMs) {
        Log.d(tag, "startTimer");
		mTimerIntervalMs = intervalMs;
		mRepetativeTimer = repeat;

		Message	nextMsg = new Message();
		int		interval = mTimerIntervalMs;

		if (sendDelayMs > 0) {
			nextMsg.arg1	= mTIMER_DELAY;
			interval = sendDelayMs;
		}
		else {
			nextMsg.arg1	= mTIMER_TIMER;
		}
		nextMsg.what 	= mTIMER_WHAT;
		if (mHandler != null) {
			mHandler.sendMessageDelayed(nextMsg, interval);
		}
	}
}
