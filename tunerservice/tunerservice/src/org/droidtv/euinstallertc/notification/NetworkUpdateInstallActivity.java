package org.droidtv.euinstallertc.notification;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Observable;
import java.util.Observer;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.ApplicationState;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.service.LogoAssociationHandler.ILogoAssociationListner;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.euinstallertc.wizard.screen.LCNConflictScreenActivity;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

public class NetworkUpdateInstallActivity extends Activity implements Observer
{
	private static final String TAG = NetworkUpdateInstallActivity.class.getName();
	private NativeAPIWrapper nwrap;
	private NotificationHandler ntf;
	private Context mContext;
	private TextView mDigitalAdded;
	private TextView mDigitalRemoved;
	private TextView mStepProgPercent;
	private TextView mTotalProgPercent;
	private TextView mVerticalText;
	private TextView mStatusText;
	private TextView mStepText;
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;
	
	private Button mButtonFinish;
	private OnClickListener buttonFinish_Listener;
	
	private int mStepCount;
	private ProgressBar mTotalProgress;
	private ProgressBar mInstallProgress;
	private ProgressBar mScreenHeaderProgessBar;
	private ProgressBar mSpinnerProgressBar;
	
    private ArrayList<ModalDialog>  mModalDialogList;
    private ModalDialog mModalDialog;
    private ModalDialog.Builder mBuilder;
	
	private TimerTask           	localProgTimerTask = null;
	private Timer               	localProgTimer     = null;
	private final int               MAX_PER_BEFORE_LOGOASSOC   = 99;
	private final int               MAX_PER_AFTER_LOGOASSOC    = 100;
	private Boolean                 ifLogoAssociationDone      = false;
    private Boolean 				IsFinishButtonEnabled = false;   
	 
    private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		Log.d(TAG, "onCreate");
		mContext = this;
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		nwrap = NativeAPIWrapper.getInstance();
		nwrap.setApplicationContext(this);
		
		if(nwrap.ifRecordingIsInProgress()){
			nwrap.showRecordingMessage();
			finish();
		}else{
			instActManager.addActivityToStack(this);
			mModalDialogList = new ArrayList<ModalDialog>();
			ntf = NotificationHandler.getInstance();
			nwrap.enterNonInteruptableMode();
			nwrap.setApplicationState(ApplicationState.INST_NETWORK_UPDATE);
			loadLayout();
		}
	}

	private void loadLayout()
	{
		Log.d(TAG,"loadLayout Triggered Entry");
		setContentView(R.layout.activity_upcnetwork_update_install);
		mDigitalAdded = (TextView)findViewById(R.id.upc_digchAddValue);
		mDigitalRemoved = (TextView)findViewById(R.id.upc_digchRemovedValue);
		mTotalProgress = (ProgressBar)findViewById(R.id.upc_totalProgress);
		mInstallProgress = (ProgressBar)findViewById(R.id.upc_installationProgress);
		mStepCount = 0;
		mStepText =(TextView) findViewById(R.id.upc_steptext);
		mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount+1));
		mStepProgPercent = (TextView)findViewById(R.id.upc_steptextVal);
		mTotalProgPercent = (TextView)findViewById(R.id.upc_totalprogresstextVal);
		mVerticalText = (TextView)findViewById(R.id.upcupdateInstall_verticalText);
		mStatusText = (TextView)findViewById(R.id.upc_belowspinnertext);
		mSpinnerProgressBar = (ProgressBar)findViewById(R.id.upc_progressBarSpinner);
		mScreenHeaderProgessBar = (ProgressBar)findViewById(R.id.bgupdateInstall_Header_Progress);
		
		screenIntialization();
		
		mVerticalText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_SAT_UPDATING));
		
		mButtonFinish = (Button)findViewById(R.id.upc_finishbtn);
		buttonFinish_Listener = new OnClickListener()
		{
			
			@Override
			public void onClick(View v)
			{
				if(IsFinishButtonEnabled == true)
				{
					Log.d(TAG,"Pressed Finish Button");
					instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
					// Send an intent to playTv to tune to first channel
				}else{
					Log.d(TAG,"Pressed Stop Button");
					//TvNotificationManager.postTvNotification(nwrap.getApplicationServiceContext(), TvNotificationManager.FLAG_NO_IMAGE,mContext.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_NETWORK_UPDATE_LATER), TvNotificationManager.FLAG_TIMED_NOTIFICATION, 0);
					// display tvtoast
					messenger = TvToastMessenger.getInstance(nwrap.getApplicationServiceContext());
					mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
					mTimeOutTvToast.setMessage(nwrap.getApplicationServiceContext().getString(org.droidtv.ui.strings.R.string.MAIN_MSG_NETWORK_UPDATE_LATER));
					messenger.showTvToastMessage(mTimeOutTvToast);
					
					Intent intent = new Intent("org.droidtv.euinstallertc.CHANNEL_INSTALL_STOPPED");
					intent.putExtra("InstallMode", "Update");
					
					if (NativeAPIEnums.DVBTOrDVBC.DVBC == nwrap.getCachedDVBTOrDVBC()) {
						intent.putExtra("InstallMedium", "Cable");
					} else {
						intent.putExtra("InstallMedium", "Terrestrial");
					}
					mContext.sendStickyBroadcast(intent);

					instActManager.exitInstallation(EXIT_INSTALLER_REASON.USER_TRIGGERED_EXIT);
				}
			}
		};
		mButtonFinish.setOnClickListener(buttonFinish_Listener);
		Log.d(TAG,"loadLayout Triggered Exit");
	}

	@Override
	public void onVisibleBehindCanceled() {
		// should return within 500ms, release the resources after it otherwise android will kill the activity 
		Log.d(TAG, "onVisibleBehindCanceled");
		super.onVisibleBehindCanceled();
		if(instActManager != null){
			instActManager.exitInstallation(EXIT_INSTALLER_REASON.ON_VISIBLILITY_CANCELLED);
		}
	}
	
	private void screenIntialization()
	{
		Log.d(TAG,"screenIntialization Entry");
		
	    // broadcast message to all the modules that update installation started
        Intent intent = new Intent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
        intent.putExtra("InstallMode", "Update");
        if (NativeAPIEnums.DVBTOrDVBC.DVBC == nwrap.getCachedDVBTOrDVBC()) {
            intent.putExtra("InstallMedium", "Cable");
        } else {
            intent.putExtra("InstallMedium", "Terrestrial");
        }
        mContext.sendBroadcast(intent);
        
		updateDigitalChannelAdded(0);
        updateDigitalChannelRemoved(0);
        updateStepProgress(1);
        updateTotalProgress(0);
        startStepProgress();

		ifLogoAssociationDone = false;
	    (NotificationHandler.getInstance()).registerForNotification(this);
	
		Log.d(TAG,"starting update");
		nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
        //nwrap.startInstallation(NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION);
        Log.d(TAG,"screenIntialization Exit");
	}
	
	
	@Override
	public void update(Observable observable, Object data) 
	{
		Log.d(TAG, "update entry");
		final int eventID = ((NotificationInfoObject) data).actionID;
		switch (eventID) 
		{
		    case EventIDs.EVENT_INST_PROGRESS:
		    	Log.d(TAG, "EventIDs.EVENT_INST_PROGRESS");
		        // query mw progress percentage
		        // UI update progress count
		        updateTotalProgress(nwrap.getInstallationProgress());
		        break;
		    case EventIDs.EVENT_DIGIT_CH_FOUND:
		    	Log.d(TAG, "EventIDs.EVENT_DIGIT_CH_FOUND");
		        // query mw for digital channel count
		        // update digit channels count
		        updateDigitalChannelAdded(nwrap.getDigitalChannelCount());
		        updateTotalProgress(nwrap.getInstallationProgress());
		        break;
		    case EventIDs.EVENT_DIGIT_CH_ADDED:	
				Log.d(TAG, "EventIDs.EVENT_DIGIT_CH_ADDED");
				updateDigitalChannelAdded(nwrap.getDigitalChannelCount());
		        updateTotalProgress(nwrap.getInstallationProgress());
		        break;
		    case EventIDs.EVENT_DIGIT_CH_REMOVED:
		        Log.d(TAG, "EventIDs.EVENT_DIGIT_CH_REMOVED");
		        updateDigitalChannelRemoved(nwrap.getDigitalChannelsRemoved());
		        updateTotalProgress(nwrap.getInstallationProgress());
		        break; 
		    case EventIDs.EVENT_INST_COMPLETED:
		    	Log.d(TAG, "EventIDs.EVENT_INST_COMPLETED");
		    	
		    	// reset flags
                nwrap.channelsUpdated(false);
                nwrap.networkChangeDetected(false);
				nwrap.commitDatabaseToTvProvider(false);
		        break;
		    case EventIDs.EVENT_INST_ONPREPAREDTV:
				Log.d(TAG, "EVENT_INST_ONPREPAREDTV ");
					nwrap.stopAndRestartInstallation(NativeAPIEnums.InstallationMode.NETWORK_UPDATE);
				break;
		    case EventIDs.EVENT_LCN_CONFLICT:
                // show dialog
                ((Activity) mContext).runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        eventDialog(eventID);
                    }
                });
                break;
			case EventIDs.EVENT_COMMIT_FINISHED:
				Log.d(TAG, "EVENT_COMMIT_FINISHED");
		        // start logo association & wait for the callback
		       	nwrap.startLogoAssociation(nwrap.getCachedDVBTOrDVBC(), new ILogoAssociationListner() {
					
					@Override
					public void notifyLogoAssociationComplete() {
						enableFinish();
					}
					
					@Override
					public void notifyLogoAssociationAborted() {
						enableFinish();
					}
				});
				break;
		}
	}
	
    private void eventDialog(int actionID) {
        Log.i(TAG, "eventDialog ->ACTION id:" + actionID);

        switch (actionID) {
            case EventIDs.EVENT_LCN_CONFLICT:
            	Log.i(TAG, "eventDialog Launch LCN Conflict Dialog");
            	mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
            	mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_GENERIC_MESSAGE), "");
            	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_LCN_CONFLICT));
            	
            	mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
            			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SKIP),
            			true,
            			new ModalDialogInterface.OnClickListener(){
            				@Override
            				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
            					Log.d(TAG, "LCN Dialog Skip clicked");
            					mModalDialog.hide();
            					nwrap.lcnSelectionDone(false);
            				}
            			});
            	ModalDialogFooterButtonProp mLaunchButton = mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
            			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_RESOLVE),
            			true,
            			new ModalDialogInterface.OnClickListener(){
            				@Override
            				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
            					 Log.d(TAG, "LCN Dialog Resolve clicked");
            					 mModalDialog.hide();
                                 mContext.startActivity(new Intent(mContext, LCNConflictScreenActivity.class));
            				}
            			});
            	mModalDialog = mBuilder.build();
            	
            	mModalDialog.setOnKeyListener(new Dialog.OnKeyListener() {

					@Override
					public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event) {
						if (keyCode == KeyEvent.KEYCODE_BACK) {
                            mModalDialog.dismiss();
                            nwrap.lcnSelectionDone(false);
							return true;
                        } else {
							return false;
						}
						
					}
                });
            	
            	mLaunchButton.requestFocus();
            	mModalDialog.show();
            	mModalDialogList.add(mModalDialog);
          
                break;
        }
    }

	
	@Override
	public boolean dispatchKeyEvent(KeyEvent event) 
	{
		int keyCode = event.getKeyCode();
		boolean handled = true;
		switch(keyCode)
		{
			case KeyEvent.KEYCODE_ENTER:
			case KeyEvent.KEYCODE_DPAD_CENTER:
				handled = super.dispatchKeyEvent(event);
				break;
		}
		return handled;
	}

	/******************************************************
     * Updating the Total progress from MW
     ******************************************************/
    private void updateTotalProgress(final int argProgress) 
    {
        Log.i(TAG, "updateTotalProgress Entry:" + argProgress);
        ((Activity)mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {
                int progressPercentage = argProgress;
                int maxValue = 0;

                if (ifLogoAssociationDone) {
                    maxValue = MAX_PER_AFTER_LOGOASSOC;
                } else {
                    maxValue = MAX_PER_BEFORE_LOGOASSOC;
                }

                if (progressPercentage > maxValue) {
                    progressPercentage = maxValue;
                }
                
                mTotalProgress.setMax(maxValue);
                mTotalProgress.setProgress(progressPercentage);
                mTotalProgPercent.setText(progressPercentage + "%");
            }
        });
        Log.i(TAG, "updateTotalProgress Exit");
    }
    
    
    /******************************************************
     * Updating the DigitalChannelAdded from MW
     ******************************************************/
    private void updateDigitalChannelAdded(final int channelCount) 
    {
        Log.i(TAG, "updateDigitalChannelAdded Entry:" + channelCount);
        ((Activity)mContext).runOnUiThread(new Runnable() 
        {
            @Override
            public void run() 
            {
            	mDigitalAdded.setText("" + channelCount);
            }
        });
        Log.i(TAG, "updateDigitalChannelAdded Exit");
    }
    
    
    
    /******************************************************
     * Updating the DigitalChannelRemoved from MW
     ******************************************************/
    private void updateDigitalChannelRemoved(final int channelCount) 
    {
        Log.i(TAG, "updateDigitalChannelRemoved Entry:" + channelCount);
        ((Activity)mContext).runOnUiThread(new Runnable() 
        {
            @Override
            public void run() 
            {
            	mDigitalRemoved.setText("" + channelCount);
            }
        });
        Log.i(TAG, "updateDigitalChannelRemoved Exit");
    } 
    
    private void enableFinish()
    {
    	Log.d(TAG,"enableFinish Entry");
    	ifLogoAssociationDone = true;
        unRegisterFromNotifications();
        stopLocalInstallationProgress();
        updateStepProgress(100);
        updateTotalProgress(100);
        IsFinishButtonEnabled = true;
        
        // remove all the dialogs
        Iterator<ModalDialog> modalDialIterator = mModalDialogList.iterator();
        ModalDialog modalDialog;
        
        while (modalDialIterator.hasNext()) {
        	modalDialog = modalDialIterator.next();
            if (modalDialog != null) {
                try{
                	modalDialog.hide();
                }catch(Exception ex){
                    Log.d(TAG, " msgDialog.hide() " + ex.getMessage());
                }
            }
        }
              
        ((Activity)mContext).runOnUiThread(new Runnable() 
        {
            @Override
            public void run() 
            {
				mButtonFinish.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE));
                mVerticalText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_UPDATE_FINISHED));
				mStatusText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_UPDATE_FINISHED));
				mSpinnerProgressBar.setVisibility(View.INVISIBLE);
				mScreenHeaderProgessBar.setProgress(100);
            }
        });
        
        Log.d(TAG,"enableFinish Exit");
    }
    
    private void unRegisterFromNotifications()
	{
		Log.i(TAG, "unRegisterFromNotifications called");
		// register this class for notifications
		(NotificationHandler.getInstance()).unregisterForNotification(this);
	}
    
    private void updateStepProgress(final int argProgress) 
    {
 
         Log.d(TAG, "updateStepProgress:" + argProgress);
        ((Activity)mContext).runOnUiThread(new Runnable() 
        {

            @Override
            public void run() 
            {
                int progressPercentage = argProgress;
                if(progressPercentage > 100)
                {
                    progressPercentage = 100;
                }
                
                mInstallProgress.setMax(100);
                mInstallProgress.setProgress(progressPercentage);
                mStepProgPercent.setText(progressPercentage + "%");
            }
        });
    }
    
    
    private void stopLocalInstallationProgress() 
    {
        if (localProgTimerTask != null) 
        {
            localProgTimerTask.cancel();
        }

        if (localProgTimer != null) 
        {
            localProgTimer.cancel();
        }
    }
    
    /******************************************************
     * Updating the DigitalChannelAdded from MW
     ******************************************************/
    private void startStepProgress()
    {
    	 if (localProgTimerTask != null) {
             localProgTimerTask.cancel();
         }

         if (localProgTimer != null) {
             localProgTimer.cancel();
         }

         mStepCount = 1;
         updateSteps(mStepCount);
         localProgTimerTask = new TimerTask() {
             int progressPer = 1;

             @Override
             public void run() {
                 if (progressPer <= 100) {
                     updateStepProgress(progressPer);
                     progressPer = progressPer + 1;
                 } else {
                     progressPer = 0;
                     mStepCount = mStepCount + 1;
                     updateSteps(mStepCount);
                     updateStepProgress(progressPer);
                 }
             }
         };

         localProgTimer = new Timer();
         localProgTimer.schedule(localProgTimerTask, 0, 3000); // 5*60*1000/100
    }
    
    private void updateSteps(final int stepsNum) 
    {
        ((Activity)mContext).runOnUiThread(new Runnable() 
        {
            @Override
            public void run() 
            {
                mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + stepsNum + ":");
            }
        });
    }
    
	@Override
	protected void onStart() {
		super.onStart();
		Log.d(TAG, "onStart");
	}

	@Override
	protected void onResume() {
		super.onResume();
		Log.d(TAG, "onResume");
	}

	@Override
	protected void onPause() {
		super.onPause();
		Log.d(TAG, "onPause");
		
		if (isFinishing()) {
			Log.d(TAG, "onPause & the reason is activity is finishing");
		}else{
			boolean isVisible = requestVisibleBehind(true);
	        Log.d(TAG, "requestVisibleBehind returns: "+ isVisible);
	        
	        if(isVisible == false){
	        	instActManager.exitInstallation(EXIT_INSTALLER_REASON.VISIBLE_BEHIND_NOT_ALLOWED);
	        }
		}
	}

	@Override
	protected void onStop() {
		super.onStop();
		Log.d(TAG, "onStop");
	}

	@Override
	protected void onDestroy() {
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Log.d(TAG, "onRestart");
	}

	
}

