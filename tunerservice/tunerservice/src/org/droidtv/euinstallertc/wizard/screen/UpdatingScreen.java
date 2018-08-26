/*
 *  Copyright(C) 2012 TP Vision Holding B.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of TP Vision Holding B.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of TP Vision Holding B.V.
 *
 */
package org.droidtv.euinstallertc.wizard.screen;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.service.LogoAssociationHandler.ILogoAssociationListner;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.euinstallertc.wizard.InstallerWizardActivity;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

/*
 * This class will search the digital and analogue channels.
 * If the user clicks on "stop" button the search will stop. 
 */
public class UpdatingScreen extends WizardStep implements IInstallationScreen {

    private static final String TAG                = UpdatingScreen.class.getName();
    private int                 mStepCount;
    private IInstallationScreen mInstallationScreen;
    private Context             mContext;

    private InstallationWizard  mInstallationWizard;
    private NativeAPIWrapper    nwrap              = NativeAPIWrapper.getInstance();
    private View                updatingScreen;

    private TimerTask           localProgTimerTask = null;
    private Timer               localProgTimer     = null;

    private int                     MAX_PER_BEFORE_LOGOASSOC   = 99;
    private int                     MAX_PER_AFTER_LOGOASSOC    = 100;
    private Boolean                 ifLogoAssociationDone      = false;
    
    private ArrayList<ModalDialog>  mModalDialogList;
    private ModalDialog mModalDialog;
    private ModalDialog.Builder mBuilder;
    
    public UpdatingScreen(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        mContext = context;
        mInstallationScreen = this;

        mModalDialogList = new ArrayList<ModalDialog>();
        loadLayout(context, attrs, defStyle);

    }

    public UpdatingScreen(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public UpdatingScreen(Context context) {
        this(context, null, 0);
    }

    private void loadLayout(final Context context, AttributeSet attrs, int defStyle) {
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        updatingScreen = inflater.inflate(R.layout.updatingwizard, null);
        addView(updatingScreen);

        OnClickListener buttonStop_Listener = new OnClickListener() {

            @Override
            public void onClick(View v) {
                stopInstallation(true);
            }
        };

        setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_STOP), buttonStop_Listener, View.VISIBLE);
        setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), null, View.INVISIBLE);
        setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_START), null, View.INVISIBLE);
        setHintText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_UPDATE_UPDATING));

    }

    private void stopInstallation(Boolean ifShowDialog) {
        // ifShowDialog: flag because same function can be invoked by pressing
        // back key in activity and pressing stop key
        if (ifShowDialog) {
            Log.d(TAG, "stopDialog displaying");
            mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
            mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_AUTOSTORE_STOP), "");
        	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_STOP));
        	
        	ModalDialogFooterButtonProp mNoButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
        			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NO),
        			true,
        			new ModalDialogInterface.OnClickListener(){
        				@Override
        				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
        					Log.d(TAG, "Stop cancelled Resume");
        					mModalDialog.hide();
        				}
        			});
        	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
        			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_YES),
        			true,
        			new ModalDialogInterface.OnClickListener(){
        				@Override
        				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
        					 Log.d(TAG, "Stop installation");
        					 (NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
    	                    stopLocalInstallationProgress();
    	                    nwrap.stopInstallation(false);
    	                    enableWaitingAnimation(false);
    	                    if(nwrap.isCamUpdateMode()){
    	                    	Log.d("TAG","isCamUpdateMode is true, calling activity finish");
    	                    	((Activity)mContext).finish();
    	                    }else{
    	                    	mInstallationWizard.launchPreviousScreen();
    	                    }
        				}
        			});
        	mModalDialog = mBuilder.build();
        	mModalDialog.setCancelable(false);
        	mModalDialog.show();
        	mNoButton.requestFocus();
        	mModalDialogList.add(mModalDialog);      
        } else {
            stopLocalInstallationProgress();
            (NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
            stopLocalInstallationProgress();
            nwrap.stopInstallation(false);
            enableWaitingAnimation(false);
            mInstallationWizard.launchPreviousScreen();
        }
    }

    private void moveToNextPage() {
        Log.d(TAG, "moveToNextPage()");
        nwrap.setSortingPhase(false);
        ((InstallerWizardActivity) mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {
                enableWaitingAnimation(false);
                stopLocalInstallationProgress();
                (NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
                mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.UPDATEFINISHED_SCREEN, getScreenName());
            }
        });
    }

    @Override
    public void setInstance(InstallationWizard wizard) {
        mInstallationWizard = wizard;
    }

    @Override
    public ScreenRequest getScreenName() {
        return InstallationWizard.ScreenRequest.UPDATING_SCREEN;
    }

    private void stopLocalInstallationProgress() {
        if (localProgTimerTask != null) {
            localProgTimerTask.cancel();
        }

        if (localProgTimer != null) {
            localProgTimer.cancel();
        }
    }

    private void startLocalInstallationProgress() {
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
                    updateLocalProgress(progressPer);
                    progressPer = progressPer + 1;
                } else {
                    progressPer = 0;
                    mStepCount = mStepCount + 1;
                    updateSteps(mStepCount);
                    updateLocalProgress(progressPer);
                }
            }
        };

        localProgTimer = new Timer();
        localProgTimer.schedule(localProgTimerTask, 0, 3000); // 5*60*1000/100
		
		nwrap.registerTimerTask(localProgTimer);
    }

    private void updateSteps(final int stepsNum) {
        ((Activity)mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {
                TextView stepText = (TextView) updatingScreen.findViewById(R.id.progressStep);
                stepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + stepsNum + ":");
            }
        });
    }

    private void updateLocalProgress(final int argProgress) {
        // Log.i(TAG, "updateLocalProgress:" + progressPercentage);
        ((Activity)mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {

                int progressPercentage = argProgress;
                if(progressPercentage > 100){
                    progressPercentage = 100;
                }
                
                ProgressBar progressBar = (ProgressBar) updatingScreen.findViewById(R.id.installationProgress);
                progressBar.setMax(100);
                progressBar.setProgress(progressPercentage);
                
                TextView progressValue = (TextView) updatingScreen.findViewById(R.id.progressPercentage);
                progressValue.setText(progressPercentage + "%");
            }
        });
    }

    /*
     * Updating the installation progress from MW
     * 
     * Params int progressPercentage
     */
    private void updateTotalProgress(final int argProgress) {
        Log.i(TAG, "updateInstallationProgress:" + argProgress);
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
                
                ProgressBar installationProgress = (ProgressBar) updatingScreen.findViewById(R.id.totalProgress);
                installationProgress.setMax(maxValue);
                installationProgress.setProgress(progressPercentage);
                
                TextView progressValue = (TextView) updatingScreen.findViewById(R.id.totalPercentage);
                progressValue.setText(progressPercentage + "%");
            }
        });
    }

    /*
     * Updating the digital channel count
     * 
     * Params int channelCount
     */
    private void updateDigitalChannelAdded(final int channelCount) {
        Log.i(TAG, "updateDigitalChannelCount:" + channelCount);
        ((Activity)mContext).runOnUiThread(new Runnable() {
            @Override
            public void run() {
                TextView digitalChannels = (TextView) updatingScreen.findViewById(R.id.line1Value);
                digitalChannels.setText("" + channelCount);
            }
        });

    }

    /*
     * Updating the analog channel count
     * 
     * Params int channelCount
     */
    private void updateDigitalChannelRemoved(final int channelCount) {
        Log.i(TAG, "updateDigitalChannelRemoved:" + channelCount);
        ((Activity)mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {
                TextView analogueChannels = (TextView) updatingScreen.findViewById(R.id.line2Value);
                analogueChannels.setText("" + channelCount);
            }
        });

    }

    @Override
    public void update(Observable observable, Object data) {

        final int eventID = ((NotificationInfoObject) data).actionID;
        switch (eventID) {
            case EventIDs.EVENT_INST_PROGRESS:
                // query mw progress percentage
                // UI update progress count
                updateTotalProgress(nwrap.getInstallationProgress());
                break;
            case EventIDs.EVENT_DIGIT_CH_FOUND:
                // query mw for digital channel count
                // update digit channels count
                updateDigitalChannelAdded(nwrap.getDigitalChannelCount());
                //updateDigitalChannelRemoved(nwrap.getDigitalChannelsRemoved());
                updateTotalProgress(nwrap.getInstallationProgress());
                break;
            /*case EventIDs.EVENT_ANALOG_CH_FOUND:
                // query mw for analogue channel count
                // update analogue channels count
            	updateDigitalChannelRemoved(nwrap.getDigitalChannelsRemoved());
                updateTotalProgress(nwrap.getInstallationProgress());
                break;*/
            case EventIDs.EVENT_LCN_CONFLICT:
                // show dialog
                ((Activity) mContext).runOnUiThread(new Runnable() {

                    @Override
                    public void run() {
                        eventDialog(eventID);
                    }

                });

                break;
            case EventIDs.EVENT_INST_COMPLETED:
            	
            	 // set sorting phase to disable back key
                nwrap.setSortingPhase(true);
                
                // disable stop button
                ((Activity) mContext).runOnUiThread(new Runnable() {

                    @Override
                    public void run() {
                        setButton1Enabled(false);
                    }
                });

				nwrap.commitDatabaseToTvProvider(false);
               
                break;
            case EventIDs.EVENT_USER_INITIATED_STOP:
                Log.d(TAG, "EventIDs.EVENT_USER_INITIATED_STOP");
                stopInstallation(false);
                break;
			case EventIDs.EVENT_DIGIT_CH_REMOVED:
                Log.d(TAG, "EventIDs.EVENT_DIGIT_CH_REMOVED");
                updateDigitalChannelRemoved(nwrap.getDigitalChannelsRemoved());
                updateTotalProgress(nwrap.getInstallationProgress());
                break; 
			case EventIDs.EVENT_DIGIT_CH_ADDED:	
				Log.d(TAG, "EventIDs.EVENT_DIGIT_CH_ADDED");
				updateDigitalChannelAdded(nwrap.getDigitalChannelCount());
                updateTotalProgress(nwrap.getInstallationProgress());
                break;     
			case EventIDs.EVENT_COMMIT_FINISHED:
				Log.d(TAG, "EVENT_COMMIT_FINISHED");
                // reset flags
                nwrap.channelsUpdated(false);
                nwrap.networkChangeDetected(false);
                
                // start logo association & wait for the callback
				nwrap.startLogoAssociation(nwrap.getCachedDVBTOrDVBC(),new ILogoAssociationListner() {
					
					@Override
					public void notifyLogoAssociationComplete() {
						screenExit();
					}
					
					@Override
					public void notifyLogoAssociationAborted() {
						screenExit();
					}
				});
				
				break;
				
        }

    }
    
    private void eventDialog(int actionID) {
        Log.i(TAG, "eventDialog ->ACTIONid:" + actionID);

        switch (actionID) {
            case EventIDs.EVENT_LCN_CONFLICT:
            	
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
    
    private void screenExit(){
    	Log.d(TAG, "screenExit");
    	
    	ifLogoAssociationDone = true;

        stopLocalInstallationProgress();
        updateDigitalChannelAdded(nwrap.getDigitalChannelCount());
        updateDigitalChannelRemoved(nwrap.getDigitalChannelsRemoved());
        updateLocalProgress(100);
        updateTotalProgress(100);
        
        (NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
                      
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

        
        final Timer delayedTimer = new Timer();
        final TimerTask delayedTask = new TimerTask() {
            @Override
            public void run() {
            	Log.d(TAG, "delayHandler run");
            	
                if (delayedTimer != null) {
                	delayedTimer.cancel();
                }
                
				moveToNextPage();
            }
        };
        
        delayedTimer.schedule(delayedTask, 1000 );

    }

    
    @Override
    public void screenIntialization() {
        // broadcast message to all the modules that auto installation started
        Intent intent = new Intent("org.droidtv.euinstallertc.CHANNEL_INSTALL_START");
        intent.putExtra("InstallMode", "Update");
        if (NativeAPIEnums.DVBTOrDVBC.DVBC == nwrap.getCachedDVBTOrDVBC()) {
            intent.putExtra("InstallMedium", "Cable");
        } else {
            intent.putExtra("InstallMedium", "Terrestrial");
        }
        mContext.sendStickyBroadcast(intent);

        enableWaitingAnimation(true);
        nwrap.setSortingPhase(false);
        
        (NotificationHandler.getInstance()).registerForNotification(mInstallationScreen);
        ifLogoAssociationDone = false;
        updateDigitalChannelAdded(0);
        updateDigitalChannelRemoved(0);
        updateLocalProgress(1);
        updateTotalProgress(0);
        startLocalInstallationProgress();

        // trigger start searching in mw
        if(nwrap.isCamUpdateMode())
        {
        	Log.d(TAG,"starting update for cam");
        	nwrap.startInstallation(NativeAPIEnums.InstallationMode.CAM_INSTALLATION);
        }
        else
        {
        	Log.d(TAG,"starting update");
        nwrap.startInstallation(NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION);
        }

        setButton1focussed();
    }
}
