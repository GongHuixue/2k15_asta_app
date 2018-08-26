package org.droidtv.euinstallertc.util;

import org.droidtv.tv.contextualhelp.IHelpContext;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;

import org.droidtv.ui.tvwidget2k15.utils.LogHelper;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;

public class ContextHelper {
	
	public final String TAG = "TCContextHelper";
	private static ContextHelper mContextHelper=null;
	private String ACTION_CONTEXTUAL="org.droidtv.intent.action.CONTEXTUALHELP";
	private String mHelpContextString = null;
	private int mHelpContextLevel = -1;
	private IHelpContext intHelpContext;
	private Handler mHandler = null;
	private Context mContext;
	
	private ServiceConnection serConn=new ServiceConnection() {
		
		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d(TAG,"onServiceDisconnected");
			intHelpContext = null;
		}
		
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG,"onServiceConnected");
			intHelpContext=IHelpContext.Instance.asInterface(service);
			if(intHelpContext==null){
				Log.d(TAG," intHelpContext onServiceConnected is null");
			}
			else{
				Log.d(TAG,"intHelpContext onServiceConnected is not null");
			}
			
		}
	};
	private ContextHelper(){
		Log.d(TAG,"Its in ContextualHelper constructor");
		
		WorkerThread mWorkerThread = new WorkerThread("Contexual Help thread"); 
		
		if(mWorkerThread.isAlive() == false){
			mWorkerThread.start();
		}
		
		mHandler = new Handler(mWorkerThread.getLooper()){
			@Override
			public void handleMessage(Message msg) {
				
				switch(msg.what){
					
					case BINDTOEUMSERVICE:
						Log.d(TAG,"BINDTOEUMSERVICE");
						bindtoEumService();
						break;
					
					case SETCONTEXT:
						Log.d(TAG,"SETCONTEXT");
						bindtoEumService();
						Bundle lb = msg.getData();
						int contextLevel = lb.getInt(CONTEXTLEVEL, 0);
						String context = lb.getString(CONTEXTSTRING, CONTEXTSTRING);
						try{
							if(contextLevel>0 && contextLevel<5 && intHelpContext!=null){
								String[] contextURL={
										org.droidtv.tv.contextualhelp.IContextualHelp.ContextID_WatchTv, 
										org.droidtv.tv.contextualhelp.IContextualHelp.ContextID_Settings,
										context,
										org.droidtv.tv.contextualhelp.IContextualHelp.ContextID_NA
										};
								mHelpContextString = context;
								mHelpContextLevel = contextLevel;
								Log.d(TAG," SET context --"+contextURL[0]+":"+contextURL[1]+":"+contextURL[2]+":"+contextURL[3]);
								intHelpContext.setHelpContext(contextURL);
								String[] getValue=intHelpContext.getHelpContext();
								Log.d(TAG," GET context --"+getValue[0]+":"+getValue[1]+"::"+getValue[2]);
							}else{
								Log.d(TAG,"Don't Set the context here and the set context value is--");
							}
						}catch(Exception e){
							Log.d(TAG,"Exception at SetContext = "+e.getMessage());
						}
						break;
					case CLEARCONTEXT:
						Log.d(TAG,"CLEARCONTEXT");
						try{							
							bindtoEumService();
							if(intHelpContext!=null){
								Log.d(TAG,"intHelpContext is not null");
								intHelpContext.clearContext();
							}
						}catch(Exception e){
							Log.d(TAG,"Exception at Clear context = "+e.getMessage());
						}
						break;
					}
				}	
			/**
			 * bindtoEumService: loops untill connection to eum service is estabilished
			 */
			private void bindtoEumService(){
				Log.d(TAG, "intHelpContext: " + intHelpContext + " mContext: " + mContext);
				if(intHelpContext == null && mContext != null){
					Log.d(TAG,"bindtoEumService..");
					boolean l = false;
					Intent i = new Intent();
					i.setAction(ACTION_CONTEXTUAL);
			
					while(intHelpContext == null){/*Loop untill the connection is received*/
						while(l == false){/*Loop untill the bindservice call is successfully made*/
						    PackageManager pm = mContext.getApplicationContext().getPackageManager();
							ResolveInfo ri = pm.resolveService(i, 0);
							i.setClassName(ri.serviceInfo.packageName,ri.serviceInfo.name);
							l = mContext.bindService(i, serConn, Context.BIND_AUTO_CREATE);
							Log.d(TAG," Bind service = "+l);
						}
						
						try {
							Thread.sleep(10);
						} catch (InterruptedException e) {
							Log.d(TAG, ""+e.toString());
						}
					}
					Log.d(TAG,"End to bindtoEumService");
				}else{
					Log.d(TAG," bindtoEumService.. already binded to eum service");
				}
			}
		};
	}
	
	private static final int BINDTOEUMSERVICE = 0;
	private static final int SETCONTEXT = 1;
	private static final int CLEARCONTEXT = 2;
	
	public void setAppContext(Context lContext){
		Log.d(TAG,"lContext " + lContext);
		mContext = lContext;
		/*Bind to EUM service*/
		mHandler.sendEmptyMessage(BINDTOEUMSERVICE);
	}
	
	public static ContextHelper getInstance(){
		if(mContextHelper==null){
			mContextHelper=new ContextHelper();
		}
		return mContextHelper;
	}
	
	private static final String CONTEXTLEVEL = "0";
	private static final String CONTEXTSTRING = "1";
	
	public void setContext(int contextLevel, String context){	
		Message msg = new Message();
		Bundle lb = new Bundle();
		lb.putInt(CONTEXTLEVEL, contextLevel);
		lb.putString(CONTEXTSTRING, context);
		msg.setData(lb);
		msg.what = SETCONTEXT;
		mHandler.sendMessage(msg);
	}
	
	public String clearContext(){
		mHandler.removeMessages(BINDTOEUMSERVICE);
		mHandler.removeMessages(SETCONTEXT);
		mHandler.sendEmptyMessage(CLEARCONTEXT);
		return mHelpContextString;
	}
	
	public int getCurrentContextLevel(){
		return mHelpContextLevel;
	}

	public void unBindEumService(Context lContext){
		LogHelper.i(TAG, " unBindEumService");
		mHandler.removeMessages(SETCONTEXT);
		mHandler.removeMessages(CLEARCONTEXT);
		if(intHelpContext != null){
			if(mContext != null && lContext == mContext) {
				mContext.unbindService(serConn);
				mContext = null;
			}
			Log.d(TAG,"intHelpContext to NUll");
			intHelpContext = null;
		}
	}
}
/**
 * class WorkerThread: extends HandlerThread
 * WorkerThread creates a thread with a looper. This looper is used by Handler to perform parallel tasks.
 */
class WorkerThread extends HandlerThread{

	public WorkerThread(String name) {
		super(name);
	}
	
}
