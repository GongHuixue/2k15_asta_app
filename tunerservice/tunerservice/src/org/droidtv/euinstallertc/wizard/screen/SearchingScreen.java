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
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.DVBTOrDVBCMacro;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.service.LogoAssociationHandler.ILogoAssociationListner;
import org.droidtv.euinstallertc.util.CustomDialog;
import org.droidtv.euinstallertc.util.EventIDs;
import org.droidtv.euinstallertc.util.NetworkDialogWithPicker;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.euinstallertc.wizard.InstallerWizardActivity;
import org.droidtv.tunerservice.R;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.inputPicker.InputPicker;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

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
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

/*
 Algorithm:
 if(check if network frequency pop-up){

 }else{
 // start AUTOINSTALL
 }

 catchevents(){

 }
 */
public class SearchingScreen extends WizardStep implements IInstallationScreen {

    private static final String     TAG                        = SearchingScreen.class.getName();

    private int                     mStepCount;

    private int                     networkFeqAttempt          = 0;
    private int                     networkIDAttempt           = 0;
    private FrequncyPopupCause      frequencyPopupMessage       = FrequncyPopupCause.HIDE;
    private boolean					ifFreqSkip					= false;

    private TextView                digitalChannelFoundTxt;
    private TextView                digitalChannelFoundValue;
    private TextView                analogChannelFoundTxt;
    private TextView                analogChannelFoundValue;
    private TextView                networkNameTxt;
    private TextView                channelFoundTxt;
    private TextView                channelFoundValue;

    private Button					skipButton;
    private Button					doneButton;
    private InputPicker 			pickerLeft;
	private InputPicker 			pickerRight;
	private String                 	NETWORK_FREQ_DIALOG        = "NETWORK_FREQ_DIALOG";
	private String                  NETWORK_ID_DIALOG          = "NETWORK_ID_DIALOG";

    private NetworkDialogWithPicker networkFreq                = null;
    private NetworkDialogWithPicker networkID                  = null;
    private TimerTask               localProgTimerTask         = null;
    private Timer                   localProgTimer             = null;
    private IInstallationScreen     mInstallationScreen;
    private Context                 mContext;
    private ArrayList<Dialog>       mDialogList;
    private InstallationWizard      mInstallationWizard;
    private int                     MAX_PER_BEFORE_LOGOASSOC   = 99;
    private int                     MAX_PER_AFTER_LOGOASSOC    = 100;
    private Boolean                 ifLogoAssociationDone      = false;

    private NativeAPIWrapper        nwrap                      = NativeAPIWrapper.getInstance();
    private NotificationHandler     ntf                        = NotificationHandler.getInstance();

    private View                    searchingScreen;
    private Dialog                  dialog;

    private int                     enteredNID                 = 0;
    
    private ArrayList<ModalDialog>  mModalDialogList;
    private ModalDialog mModalDialog;
    private ModalDialog.Builder mBuilder;
    
    private enum FrequncyPopupCause {
    	NO_RF_LOCK,
    	NO_NETWORK_INFO, // in case of invalid NID & invalid freq also
    	HIDE
    }

    public SearchingScreen(Context context) {
        super(context, null, 0);
    }

    public SearchingScreen(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public SearchingScreen(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        mContext = context;
        mInstallationScreen = this;

        mDialogList = new ArrayList<Dialog>();
        mModalDialogList = new ArrayList<ModalDialog>();
        loadLayout(context, attrs, defStyle);
    }

    private void loadLayout(final Context context, AttributeSet attrs, int defStyle) {
        final LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        searchingScreen = inflater.inflate(R.layout.searchingscreen, null);
        addView(searchingScreen);

        digitalChannelFoundTxt = (TextView) searchingScreen.findViewById(R.id.line1String);
        digitalChannelFoundValue = (TextView) searchingScreen.findViewById(R.id.line1Value);
        analogChannelFoundTxt = (TextView) searchingScreen.findViewById(R.id.line2String);
        analogChannelFoundValue = (TextView) searchingScreen.findViewById(R.id.line2Value);
        networkNameTxt = (TextView) searchingScreen.findViewById(R.id.line3String);
        channelFoundTxt = (TextView) searchingScreen.findViewById(R.id.line1String);
        channelFoundValue = (TextView) searchingScreen.findViewById(R.id.line1Value);

        OnClickListener buttonStop_Listener = new OnClickListener() {

            @Override
            public void onClick(View v) {
                stopInstallation(true);
            }
        };
        setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_STOP), buttonStop_Listener, View.VISIBLE);
        setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), null, View.INVISIBLE);
        setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_START), null, View.INVISIBLE);

        setHintText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_SEARCHING));

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
        					 stopLocalInstallationProgress();
        					 nwrap.stopInstallation(false);
        					 (NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
        					 enableWaitingAnimation(false);
        					 mInstallationWizard.launchPreviousScreen();
        				}
        			});
        	mModalDialog = mBuilder.build();
        	mModalDialog.setCancelable(false);
        	mModalDialog.show();
        	mNoButton.requestFocus();
        	mModalDialogList.add(mModalDialog);
        	
        } else {
            stopLocalInstallationProgress();
            nwrap.stopInstallation(false);
            (NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
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
                mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.FINISH_SCREEN, getScreenName());
            }
        });
    }

    @Override
    public void setInstance(InstallationWizard wizard) {
        mInstallationWizard = wizard;
    }

    @Override
    public ScreenRequest getScreenName() {
        return InstallationWizard.ScreenRequest.SEARCHING_SCREEN;
    }

    private void stopLocalInstallationProgress() {
        Log.d(TAG, "stopLocalInstallationProgress ");
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
            // localProgTimerTask = null;
        }

        if (localProgTimer != null) {
            localProgTimer.cancel();
            // localProgTimer = null;
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
        ((Activity) mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {
                TextView stepText = (TextView) searchingScreen.findViewById(R.id.progressStep);
                stepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + stepsNum + ":");
            }
        });
    }

    private void updateLocalProgress(final int argProgress) {
        // Log.i(TAG, "updateLocalProgress:" + progressPercentage);
        ((Activity) mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {

                int progressPercentage = argProgress;
                if (progressPercentage > 100) {
                    progressPercentage = 100;
                }

                ProgressBar progressBar = (ProgressBar) searchingScreen.findViewById(R.id.installationProgress);
                progressBar.setMax(100);
                progressBar.setProgress(progressPercentage);

                TextView progressValue = (TextView) searchingScreen.findViewById(R.id.progressPercentage);
                progressValue.setText(progressPercentage + "%");
            }
        });
    }

    private void updateNetworkName(final String argNetworkName) {
        Log.i(TAG, "updateNetworkName: " + argNetworkName);
        ((Activity) mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {
                networkNameTxt.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_NETWORK_NAME_COLON) + " " + argNetworkName);
                networkNameTxt.setVisibility(View.VISIBLE);
            }
        });
    }

    private void updateTotalProgress(final int argProgress) {
       // Log.i(TAG, "updateTotalProgress:" + argProgress);
        ((Activity) mContext).runOnUiThread(new Runnable() {

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
                ProgressBar installationProgress = (ProgressBar) searchingScreen.findViewById(R.id.totalProgress);
                installationProgress.setMax(maxValue);
                installationProgress.setProgress(progressPercentage);

                TextView progressValue = (TextView) searchingScreen.findViewById(R.id.totalPercentage);
                progressValue.setText(progressPercentage + "%");
            }
        });
    }

    private void updateDigitalChannelCount(final int channelCount) {
        Log.i(TAG, "updateDigitalChannelCount:" + channelCount);
        ((Activity) mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {
                digitalChannelFoundValue.setText(Integer.toString(channelCount));
            }
        });
    }

    /*
     * Updating the analog channel count
     * 
     * Params int channelCount
     */
    private void updateAnalogueChannelCount(final int channelCount) {
        Log.i(TAG, "updateAnalogueChannelCount:" + channelCount);
        ((Activity) mContext).runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (nwrap.getCachedAnalogueDigital() == NativeAPIEnums.AnalogueOrDigital.ANALOGUE) {
                    channelFoundValue.setText(Integer.toString(channelCount));
                } else {
                    analogChannelFoundValue.setText(Integer.toString(channelCount));
                }
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

                // update network name for DVBC-Full installation or ziggo/Telenet
                if ((nwrap.ifShowNetworkName() || (nwrap.ifCheckNIDs() == false))) {
                    // get the network name and populate it
                    String netwkName = nwrap.getNetworkName(enteredNID);
                    if(netwkName != null) {
                        if (netwkName.trim() != "") {
                            updateNetworkName(netwkName);
                        }
                    }
                }
                
                // query mw for digital channel count
                // update digit channels count
                updateDigitalChannelCount(nwrap.getDigitalChannelCount());
                updateTotalProgress(nwrap.getInstallationProgress());
                break;
            case EventIDs.EVENT_ANALOG_CH_FOUND:
                // query mw for analogue channel count
                // update analogue channels count
                updateTotalProgress(nwrap.getInstallationProgress());
                updateAnalogueChannelCount(nwrap.getAnalogueChannelCount());
                break;
            case EventIDs.EVENT_FAV_NETWORK:
            case EventIDs.EVENT_NETWORK_FREQ:
            case EventIDs.EVENT_NETWORK_ID:
            case EventIDs.EVENT_NETWORK_ID_LOCAL:
            case EventIDs.EVENT_REGION_NAMES:
            case EventIDs.EVENT_LCN_CONFLICT:
                // show dialog
                ((Activity) mContext).runOnUiThread(new Runnable() {

                    @Override
                    public void run() {
                        eventDialog(eventID);
                    }

                });
                break;
			case EventIDs.EVENT_FAV_CHANNELLIST:
                // show dialog
                if(nwrap.ifLCNV2Supported()==true){
                ((Activity) mContext).runOnUiThread(new Runnable() {

                    @Override
                    public void run() {
                        eventDialog(eventID);
                    }

                });
                }
                break;
            case EventIDs.EVENT_INST_COMPLETED:
                Log.d(TAG, "SearchingScreen EventIDs.EVENT_INST_COMPLETED");
                if (nwrap.getMWInstallationMode() == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN) {
                    Log.d(TAG, "EventIDs.EVENT_INST_COMPLETED eventTuningStationNotFound frequencyPopupMessage " + frequencyPopupMessage);

                    // EventTuningStationNotFound
                    if ((frequencyPopupMessage == FrequncyPopupCause.NO_NETWORK_INFO) ||
                    		(frequencyPopupMessage == FrequncyPopupCause.NO_RF_LOCK)) {
                        // network freq scan failed retry
                        ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_FREQ, "");
                    } else {
                        // hide the network freq window, proceed
                        Log.d(TAG, "hide network freq");

                        if ((dialog != null) && dialog.isShowing()) {
                            dialog.dismiss();
                        }

                        Log.d(TAG, "check if to show NID");
                        if(nwrap.ifYouseeOperator()){
                        	// nid dialog is up wait for user to press done/skip. from NID dialog start installation
							Log.d(TAG,"ignore installation complete event");
							
							// check if nid's detected during prescan
							int[] nIDList = nwrap.getNIDsFound();
							Log.d(TAG, "nIDList.length " + nIDList.length);
							if (nIDList.length > 0) {
								// show network ID dialogue
                                ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_ID_LOCAL, "");
							}else{
								moveToNextPage();
							}
						}else if (nwrap.ifCheckNIDs()) {
                            int[] nIDList = nwrap.getNIDsFound();

                            if(DVBTOrDVBCMacro.DVBC_Light ==  nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName())){
                            	nwrap.setWSNetworkFrequencyMode(1);
                            }
                            
                            if (nIDList.length > 1) {
                                Log.d(TAG, "nIDList.length " + nIDList.length);
                                Log.d(TAG, "more than one NID found launch dialog");
                                // show network ID dialog
                                ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_ID_LOCAL, "");
                            }else if (nIDList.length == 1) {
                                Log.d(TAG, "nIDList.length " + nIDList.length);
                                // set the default network ID
                                nwrap.setNetworkID(nIDList[0]);

                                // get the network name and populate it
                                updateNetworkName(nwrap.getNetworkName(nIDList[0]));

                                // start start auto installation
                                nwrap.startInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
                            }else if ((nIDList.length == 0) && 
                            		(nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBC_Light)){
                            		Log.d(TAG, "nIDList.length 0 & DVBC Lite Country");
                            	 nwrap.startInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
                            }else{
                                // start auto install
                                Log.d(TAG, "nIDList.length " + nIDList.length);
								if (PlayTvUtils.isPbsMode()) { // HTV - Need auto scan other if network freq is not exist.
									nwrap.startInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
								} else {
	                                // nwrap.startInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
    	                            moveToNextPage();
								}
                            }
                        } else {
                            Log.d(TAG, "no NID dialog start installation");
                            // network ID not required start AutoInstallation
                            nwrap.startInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
                        }
                    }
                } else if ((nwrap.getCurrentInstallationMode() == NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION)  || (nwrap.getCurrentInstallationMode() == NativeAPIEnums.InstallationMode.CAM_INSTALLATION)) {
                    Log.d(TAG, "NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION");

                    // set sorting phase to disable back key
                    nwrap.setSortingPhase(true);
                    
                    // reset flags
                    nwrap.channelsUpdated(false);
                    nwrap.networkChangeDetected(false);
                    
                    // update analog channel count
                    nwrap.getAnalogueChannelCount();
                    
                    // commit changes to TVSettings
                    nwrap.commitToTVSettings();

					Log.d(TAG, "DATABASE Commit ");
					nwrap.commitDatabaseToTvProvider(true);

                    // disable stop button
                    ((Activity) mContext).runOnUiThread(new Runnable() {

                        @Override
                        public void run() {
                            setButton1Enabled(false);
                        }
                    });
                    
                }
                break;
            case EventIDs.EVENT_INST_TUNING_STATION_NOT_FOUND:
            	Log.d(TAG, "EventIDs.EVENT_TUNING_STATION_NOT_FOUND");
                if(nwrap.ifNetwkFreqDialogDuringPrescan() || (nwrap.getMWInstallationMode() == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN)){
                    if(nwrap.ifNetworkFreqDialog() && (ifFreqSkip == false)){
                        frequencyPopupMessage = FrequncyPopupCause.NO_RF_LOCK;
                    } else{
                        frequencyPopupMessage = FrequncyPopupCause.HIDE;
                    }
                }
                Log.d(TAG, "EventIDs.EVENT_TUNING_STATION_NOT_FOUND eventTuningStationNotFound " + frequencyPopupMessage);
                break;
            case EventIDs.EVENT_USER_INITIATED_STOP:
                Log.d(TAG, "EventIDs.EVENT_USER_INITIATED_STOP");
                stopInstallation(false);
                break;
            case EventIDs.EVENT_INST_TUNING_STATION_FOUND:
                Log.d(TAG, "EventIDs.EVENT_INST_TUNING_STATION_FOUND");
                if((nwrap.ifNetwkFreqDialogDuringPrescan()) && 
                		(nwrap.getCurrentInstallationMode() == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN)){
                	ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_ID_LOCAL, "");
                }
                break;
            case EventIDs.EVENT_LAUNCH_ACI_PAGE:
                Log.d(TAG, "EventIDs.EVENT_LAUNCH_ACI_PAGE");
                mContext.startActivity(new Intent(mContext, ACIPageActivity.class));
                break;
            case EventIDs.EVENT_INST_STOPPED:
            	Log.d(TAG, "EventIDs.EVENT_INST_STOPPED");
            	break;
			case EventIDs.EVENT_COMMIT_FINISHED:
				Log.d(TAG, "EVENT_COMMIT_FINISHED");
				// start logo association & wait for the callback
				if(nwrap.ifWaitForLogoAssociation()){
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
				}else{
					nwrap.startLogoAssociation(nwrap.getCachedDVBTOrDVBC(),null);
					screenExit();
				}
				break;
        }
    }

    private void eventDialog(int actionID) {
        Log.i(TAG, "eventDialog ->ACTIONid:" + actionID);

        switch (actionID) {
            case EventIDs.EVENT_NETWORK_FREQ:
                launchNetWorkFreqDialog(actionID);
                break;
            case EventIDs.EVENT_NETWORK_ID_LOCAL:
                launchNetWorkIDDialog();
                break;
            case EventIDs.EVENT_NETWORK_ID:
                if (nwrap.ifNetwkFreqDialogDuringPrescan()) {
                    launchNetWorkIDDialog();
                } else {
                   if(nwrap.ifNetworkFreqDialog()){
                       frequencyPopupMessage = FrequncyPopupCause.NO_NETWORK_INFO;
                   } else{
                       frequencyPopupMessage = FrequncyPopupCause.HIDE;
                   }
                   
                   Log.d(TAG, "EventIDs.EVENT_NETWORK_ID eventTuningStationNotFound " + frequencyPopupMessage);
                }
                break;
            case EventIDs.EVENT_FAV_NETWORK:
                dialog = new CustomDialog(mContext);
                dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
                mDialogList.add(dialog);
                listDialog(dialog, actionID);
                break;
            case EventIDs.EVENT_REGION_NAMES:
                dialog = new CustomDialog(mContext);
                dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
                mDialogList.add(dialog);
                listDialog(dialog, actionID);
                break;
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
			case EventIDs.EVENT_FAV_CHANNELLIST:
                dialog = new CustomDialog(mContext);
                dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
                mDialogList.add(dialog);
                listDialog(dialog, actionID);
                break;
        }
    }

	private int getValueFromDialogPickerUI(String dialogType) {
		int returnValue = 0;
		if (dialogType.equalsIgnoreCase(NETWORK_FREQ_DIALOG)) {
			returnValue = pickerLeft.getCurrValue() * 100;
			returnValue = returnValue
					+ ((pickerRight.getCurrValue() * 100) / 100);
		} else if (dialogType.equalsIgnoreCase(NETWORK_ID_DIALOG)) {
			returnValue = pickerLeft.getCurrValue();
		}

		Log.d(TAG, "getValueFromDialogPickerUI() " + dialogType + " "
				+ returnValue);
		return returnValue;
	}
	
	private void setValueInPickerUI(String dialogType, int value) {
		int firstDigit = 0;
		int decimalDigits = 0;
		
		if (dialogType.equalsIgnoreCase(NETWORK_FREQ_DIALOG)) {
			firstDigit = value / 100;
			decimalDigits = value - (firstDigit * 100);
			
			pickerLeft.setCurrValue(firstDigit);
			pickerRight.setCurrValue(decimalDigits);
		} else if (dialogType.equalsIgnoreCase(NETWORK_ID_DIALOG)) {
			pickerLeft.setCurrValue(value);
		}

		Log.d(TAG, "setValueInPickerUI() " + dialogType + " " + value);
	}
    
    private void launchNetWorkIDDialog() {
        Log.d(TAG, "launchNetWorkIDDialog networkIDAttempt " + networkIDAttempt);
        if (networkID != null) {
            networkID.dismiss();
        }

        networkID = new NetworkDialogWithPicker(mContext);
        mDialogList.add(networkID);

        networkID.setContentView(R.layout.dialog_network_id);

        pickerLeft = (InputPicker) networkID.findViewById(R.id.dialog_picker_left);
		skipButton = (Button) networkID.findViewById(R.id.dialog_skip);
		doneButton = (Button) networkID.findViewById(R.id.dialog_done);

		pickerLeft.setMinValue(0);
		pickerLeft.enableLeandingZero(true);
		pickerLeft.setValueConfirmListener(networkID);
		pickerLeft.setValueEnteredListener(networkID);
		
		if(nwrap.getNetworkIDCharCount() == 4){
			pickerLeft.setMaxValue(9999);
		}else{
			pickerLeft.setMaxValue(99999);
		}
		
        TextView descText = (TextView) networkID.findViewById(R.id.dialog_description);

        if (networkIDAttempt == 0) {
            if (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == DVBTOrDVBCMacro.DVBC_Full) {
                descText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_NETWORK_ID_FULL));
            } else if (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == DVBTOrDVBCMacro.DVBC_Light) {
                descText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_NETWORK_ID_LIGHT));
            }
            setValueInPickerUI(NETWORK_ID_DIALOG, nwrap.getNetworkID());
        } else {
            descText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_NETWORK_ID_RETRY));
            setValueInPickerUI(NETWORK_ID_DIALOG, 0);
        }

        networkIDAttempt = networkIDAttempt + 1;

        skipButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.d(TAG, "NID dialog skip clicked");
                // reset progress bar
                updateTotalProgress(0);
               
                int nID = nwrap.skipNetworkID(networkIDAttempt);
                // get the network name and populate it
                updateNetworkName(nwrap.getNetworkName(nID));
                networkID.dismiss();
            }
        });

        doneButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                enteredNID = getValueFromDialogPickerUI(NETWORK_ID_DIALOG);
                if (nwrap.ifValidNetworkID(enteredNID)) {
					networkID.dismiss();
					
					if(false == nwrap.ifCheckNIDs() && 
							(nwrap.getMWInstallationMode() == NativeAPIEnums.InstallationMode.AUTOSTORE_PRESCAN)){
						Log.d(TAG, "launchNetWorkIDDialog ifCheckNIDs done case I ");
						// ziggo cases
						nwrap.setNetworkID(enteredNID);			
					}else{
						Log.d(TAG, "launchNetWorkIDDialog ifCheckNIDs done case II ");
						
						int[] nIDList = nwrap.getNIDsFound();
						// search the user entered NID in the NID list
						boolean nidFoundInList = false;
						try{
							for(int nidIndex =0; nidIndex < nIDList.length; nidIndex++){
								if(enteredNID == nIDList[nidIndex]){
									nidFoundInList = true;
								}
							}
						}catch(Exception ex){
							Log.d(TAG, "launchNetWorkIDDialog ifCheckNIDs done case II exception caught");
						}
						
						if(nidFoundInList){
							Log.d(TAG, "launchNetWorkIDDialog valid NID detected ");
							nwrap.setNetworkID(enteredNID);
							
							 // get the network name and populate it
                            updateNetworkName(nwrap.getNetworkName(enteredNID));
                            
							nwrap.stopAndRestartInstallation(NativeAPIEnums.InstallationMode.AUTOSTORE_INSTALLATION);
						}else{
							Log.d(TAG, "launchNetWorkIDDialog invalid NID detected ");
							ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_ID_LOCAL, "");
						}
					}
                } else {
                    // user input ID is not within range reset the
                	networkID.dismiss();
                    // ID string
                    ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_ID_LOCAL, "");
                }
            }
        });

        networkID.registerButtonInstance(skipButton, doneButton);
        networkID.show();
    }
   
    private void launchNetWorkFreqDialog(int actionID) {
        Log.d(TAG, "launchNetWorkFreqDialog networkFeqAttempt " + networkFeqAttempt);
        if (networkFreq != null) {
            networkFreq.dismiss();
        }
        
        networkFreq = new NetworkDialogWithPicker(mContext);
        mDialogList.add(networkFreq);
        
        networkFreq.setContentView(R.layout.dialog_network_frequency);
        
        pickerLeft = (InputPicker) networkFreq.findViewById(R.id.dialog_picker_left);
		pickerRight = (InputPicker) networkFreq.findViewById(R.id.dialog_picker_right);
		skipButton = (Button) networkFreq.findViewById(R.id.dialog_skip);
		doneButton = (Button) networkFreq.findViewById(R.id.dialog_done);

		pickerLeft.setMinValue(0);
		pickerLeft.enableLeandingZero(true);
		pickerLeft.setValueConfirmListener(networkFreq);
		pickerLeft.setValueEnteredListener(networkFreq);
		pickerLeft.setMaxValue(999);
		
		pickerRight.setMinValue(0);
		pickerRight.enableLeandingZero(true);
		pickerRight.setValueConfirmListener(networkFreq);
		pickerRight.setValueEnteredListener(networkFreq);
		pickerRight.setMaxValue(99);
               
        TextView descText = (TextView) networkFreq.findViewById(R.id.dialog_description);
        if (networkFeqAttempt == 0) {
            if (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == DVBTOrDVBCMacro.DVBC_Full) {
                descText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_NETWORK_FREQUENCY_FULL));
            } else if (nwrap.countrySupportsDVBCFullorLite(nwrap.getCachedCountryName()) == DVBTOrDVBCMacro.DVBC_Light) {
                descText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_NETWORK_FREQUENCY_LIGHT));
            }
            setValueInPickerUI(NETWORK_FREQ_DIALOG, nwrap.getNetworkFrequency());
        } else {
        	if(frequencyPopupMessage == FrequncyPopupCause.NO_RF_LOCK){
        		 descText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_NETWORK_FREQUENCY_NO_SIGNAL));
        	}else{
        		descText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_NETWORK_FREQUENCY_RETRY));
        	}
            setValueInPickerUI(NETWORK_FREQ_DIALOG, 0);
        }
        
        // reset for retry
    	frequencyPopupMessage = FrequncyPopupCause.HIDE;
        networkFeqAttempt = networkFeqAttempt + 1;

        skipButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                // reset progress bar
            	ifFreqSkip = true;
                updateTotalProgress(0);
                nwrap.skipNetworkFrequency(networkFeqAttempt);
                networkFreq.dismiss();
            }
        });

        doneButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                int pickerValue = getValueFromDialogPickerUI(NETWORK_FREQ_DIALOG);
                networkFreq.dismiss();
                
                if (nwrap.ifValidNetworkFrequency(pickerValue)) {

                    try {
                        nwrap.setNetworkFrequency(pickerValue);
                    } catch (Exception e) {
                        //e.printStackTrace();
                    }

                    // network frequency set start the prescan
                    nwrap.startAutoInstallation();

                } else {
                    // user input frequency is not within range reset the
                    // frequency string
                    ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_FREQ, "");
                }

                
            }
        });
        
        networkFreq.registerButtonInstance(skipButton, doneButton);
        networkFreq.show();
    }

    // List Dialog will be displayed while searching for channels if any event
    // comes from MW
    private void listDialog(final Dialog dialog, final int actionID) {

    	dialog.getWindow().setBackgroundDrawableResource(android.R.color.transparent);
        dialog.setContentView(R.layout.dialog_radiolist);
        dialog.setCancelable(false);

        TextView dialog_title = (TextView) dialog.findViewById(R.id.dialog_title);
        final RadioSelector radioSelector = (RadioSelector) dialog.findViewById(R.id.dialog_RadioList);
        final Button doneButton = (Button) dialog.findViewById(R.id.dialog_done);

        if (actionID == EventIDs.EVENT_FAV_NETWORK) {
            String[] favNeworkNames = nwrap.getFavouriteNwkList();
            if ((favNeworkNames == null) || (favNeworkNames.length == 0) || (favNeworkNames.length == 1)) {
                nwrap.setFavouriteNetwork(0);
                dialog.dismiss();
            } else {
                // more than one fav network id's
            	dialog_title.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_FAVOURITE_NETWORK));
                radioSelector.setArray(favNeworkNames);
                dialog.show();
            }

        } else if (actionID == EventIDs.EVENT_REGION_NAMES) {
        	//dialog.setCancelable(true);
            String[] regionNames = null;
            if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.PRIMARY) {
            	dialog_title.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SELECT_PRIMARY_REGION));
                regionNames = nwrap.getPrimaryRegions();
            } else if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.SECONDARY) {
            	dialog_title.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SELECT_SECONDARY_REGION));
                regionNames = nwrap.getSecondayRegions();
            } else if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.TERTIARY) {
            	dialog_title.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SELECT_SECONDARY_REGION));
                regionNames = nwrap.getTeritaryRegions();
            }

            radioSelector.setArray(regionNames);
            
            // attach listener to handle back key
            dialog.setOnKeyListener(new Dialog.OnKeyListener() {

				@Override
				public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event) {
					Log.d(TAG,"list dialog key: " + keyCode );
					if (keyCode == KeyEvent.KEYCODE_BACK) {
						if(event.getAction() == KeyEvent.ACTION_UP){ // handle only up key and ignore down key
							
							if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.PRIMARY) {
								// user selection done
								 mDialogList.remove(dialog);
								 dialog.dismiss();
								 nwrap.setIfUserSelectionDone(true);
							}else if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.SECONDARY) {
								 // go back to primary region
								 mDialogList.remove(dialog);
								 dialog.dismiss();
								 nwrap.setCurrentRegionMode(NativeAPIEnums.Regions.PRIMARY);
								 ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
							 }else if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.TERTIARY) {
								 // go back to secondary region
								 mDialogList.remove(dialog);
								 dialog.dismiss();
								 nwrap.setCurrentRegionMode( NativeAPIEnums.Regions.SECONDARY);
								 ntf.notifyAllObservers(EventIDs.EVENT_REGION_NAMES, "");
							 }
						}
						return true;
                    } else {
						return false;
					}
					
				}
            });
            dialog.show();
        } else if (actionID == EventIDs.EVENT_FAV_CHANNELLIST) {
			String[] favChannelListId = nwrap.getFavouritechannelList();
			if ((favChannelListId == null) || (favChannelListId.length == 1)) {
				dialog.dismiss();
			} else {
				dialog_title.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_CHANNEL_LIST));
			    radioSelector.setArray(favChannelListId);
			    dialog.show();
			}
		}
        
        radioSelector.setOnItemClickListener(new OnItemClickListener()
		{
			@Override
			public void onItemClick(AdapterView<?> arg0, View selectedView,int selectedItem, long arg3)
			{
				Log.i(TAG, "Selected item:" + selectedItem);
				doneButton.requestFocus();
			}
		});
       
        doneButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                
            	int selectedItem = radioSelector.getCheckedItemPosition();
            	
            	if (actionID == EventIDs.EVENT_FAV_NETWORK) {
                    nwrap.setFavouriteNetwork(selectedItem);
                } else if (actionID == EventIDs.EVENT_REGION_NAMES) {
                    if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.PRIMARY) {
                        nwrap.setPrimaryRegion(selectedItem);
                    } else if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.SECONDARY) {
                        nwrap.setSecondayRegion(selectedItem);
                    } else if (nwrap.getCurrentRegionMode() == NativeAPIEnums.Regions.TERTIARY) {
                        nwrap.setTeritoryRegion(selectedItem);
                    }
                }
				else if(actionID==EventIDs.EVENT_FAV_CHANNELLIST)
					{
					nwrap.setFavouritechannelList(selectedItem);
                }
            	
                dialog.dismiss();
            }
        });
    }

  	private void screenExit(){
		Log.d(TAG, "screenExit");
		
	    ifLogoAssociationDone = true;
        stopLocalInstallationProgress();
        updateDigitalChannelCount(nwrap.getDigitalChannelCount());
        updateAnalogueChannelCount(nwrap.getAnalogueChannelCount());
        updateLocalProgress(100);
        updateTotalProgress(100);
        
        (NotificationHandler.getInstance()).unregisterForNotification(mInstallationScreen);
        Iterator<Dialog> iterator = mDialogList.iterator();
        while (iterator.hasNext()) {
            Dialog dialog = iterator.next();
            if (dialog != null) {
                dialog.dismiss();
            }
        }

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
        intent.putExtra("InstallMode", "Auto");
        if (NativeAPIEnums.DVBTOrDVBC.DVBC == nwrap.getCachedDVBTOrDVBC()) {
            intent.putExtra("InstallMedium", "Cable");
        } else {
            intent.putExtra("InstallMedium", "Terrestrial");
        }
        mContext.sendStickyBroadcast(intent);

        enableWaitingAnimation(true);
        nwrap.setSortingPhase(false);

        // register this class for notifications
        (NotificationHandler.getInstance()).registerForNotification(mInstallationScreen);

        // update UI
        if (nwrap.getCachedAnalogueDigital() == NativeAPIEnums.AnalogueOrDigital.ANALOGUE) {
            //channelFoundTxt.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_CHANNELS_STORED));
        	channelFoundTxt.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_ANALOGUE_CHANNELS_FOUND));
            channelFoundTxt.setVisibility(View.VISIBLE);
            channelFoundValue.setText("0");
            channelFoundValue.setVisibility(View.VISIBLE);
        } else {
            digitalChannelFoundTxt.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_DIGITAL_CHANNELS_FOUND));
            digitalChannelFoundTxt.setVisibility(View.VISIBLE);
            digitalChannelFoundValue.setText("0");
            digitalChannelFoundValue.setVisibility(View.VISIBLE);
            analogChannelFoundTxt.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_ANALOGUE_CHANNELS_FOUND));
            analogChannelFoundTxt.setVisibility(View.VISIBLE);
            analogChannelFoundValue.setText("0");
            analogChannelFoundValue.setVisibility(View.VISIBLE);
        }
        
        networkNameTxt.setVisibility(View.INVISIBLE);

        ifFreqSkip = false;
        ifLogoAssociationDone = false;
        updateDigitalChannelCount(0);
        updateAnalogueChannelCount(0);
        updateLocalProgress(1);
        updateTotalProgress(0);
        startLocalInstallationProgress();

        // reset data variables eventTuningStationNotFound
        frequencyPopupMessage = FrequncyPopupCause.HIDE;
        networkFeqAttempt = 0;
        networkIDAttempt = 0;
        enteredNID = 0;

        // prescan step network freq -> network ID -> startInstallation
        if (nwrap.ifNetworkFreqDialog()) {
            // launch network frequency dialog
            ntf.notifyAllObservers(EventIDs.EVENT_NETWORK_FREQ, "");
        } else {
        	// start installation prescan/full
        	nwrap.startAutoInstallation();
        }

        setButton1focussed();
    }
}
