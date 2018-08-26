package org.droidtv.tunerservice.services.sbyservice;

import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.ClientStates;
import org.droidtv.tunerservice.services.sbyservice.SSBYDefinitions.SSBYClientDeathListener;
import org.droidtv.tv.tvpower.ITvSemiStandbyControl.ITvSemiStandbyCallback;

import android.os.Handler;
import android.os.IBinder;
import android.util.Log;

public class SSBYClient extends ITvSemiStandbyCallback implements IBinder.DeathRecipient{
	private int id;
	private ITvSemiStandbyCallback cb;
	private SSBYDefinitions.ClientStates mstate = SSBYDefinitions.ClientStates.CSTATE_INIT;
	private IBinder mBinder = null;
	private String TAG = "SSBYClient-";
	private SSBYClientDeathListener mDeathlistener=null;
	
	public SSBYClient(int id, ITvSemiStandbyCallback cb, IBinder binder, SSBYClientDeathListener listener) {
		this.mBinder= binder; 
		this.mDeathlistener = listener;
		this.id = id;
		this.cb = cb;
		TAG = TAG+id;
		mstate = ClientStates.CSTATE_CONNECTED;
		try {
			binder.linkToDeath(this, 0);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	
	
	@Override
	public void onAlarmFired() {
		if(mBinder.isBinderAlive()) {
			cb.onAlarmFired();
		}
	}


	@Override
	public void onStartAction(){
		switch(mstate){
			case CSTATE_CONNECTED:
				Log.d(TAG,"onStartAction called");
				mstate = ClientStates.CSTATE_INPROGRESS;
				if(mBinder.isBinderAlive()) {
					cb.onStartAction();
				}else {
					Handler handler = new Handler();
					Runnable r = new Runnable() {
						@Override
						public void run() {
							binderDied();
						}
					};
					handler.post(r);
				}
				break;
			case CSTATE_INPROGRESS:
				break;
			case CSTATE_WAITING_TO_CONNECT:
				break;
			case CSTATE_STOPPING:
				break;
			case CSTATE_INIT:
				break;
		}
	}
	
	@Override
	public void onStopAction() {
		switch(mstate) {
		case CSTATE_CONNECTED:
			break;
		case CSTATE_INPROGRESS:
			Log.d(TAG,"onStopAction called");
			mstate = ClientStates.CSTATE_STOPPING;
			if(mBinder.isBinderAlive()) {
				cb.onStopAction();
			}else {
				Handler handler = new Handler();
				Runnable r = new Runnable() {
					@Override
					public void run() {
						binderDied();
					}
				};
				handler.post(r);
			}
			break;
		case CSTATE_WAITING_TO_CONNECT:
			break;
		case CSTATE_STOPPING:
			break;
		case CSTATE_INIT:
			break;
		}
	}

	@Override
	public long onGetNextAlarm() {
		if(mBinder.isBinderAlive()) {
			return cb.onGetNextAlarm();
		}else {
			return 0;
		}
	}
	
	public ClientStates getcurrentState(){
		return mstate;
	}

	public void onActioncompleted() {
		mstate = ClientStates.CSTATE_CONNECTED;
	}

	public int getId() {
		return id;
	}
	
	public void onDisconnected() {
		mstate = ClientStates.CSTATE_WAITING_TO_CONNECT;
	}

	public void onActionReset() {
		mstate = ClientStates.CSTATE_CONNECTED;
	}
		
	public void unregister() {
		if(mBinder!=null) {
			mBinder.unlinkToDeath(this,0);
		}
	}

	@Override
	public void binderDied() {
		Log.d(TAG,"binderDied ");
		if(mDeathlistener!=null) {
			mDeathlistener.onSSBYClientDied(this);
		}
	}

	@Override
	protected void finalize() throws Throwable {
		Log.d(TAG,"finalize called");
		super.finalize();
	}
	
}
