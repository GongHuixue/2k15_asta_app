package org.droidtv.euinstallertc.common;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Observer;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;

import android.app.Activity;
import android.util.Log;
import android.content.Intent;

public class InstallerActivityManager {

	private static String TAG = InstallerActivityManager.class.getName();
	private static InstallerActivityManager singletonInstance = null;
	private NativeAPIWrapper nwrap = null;
	private NotificationHandler ntf = null;
	private List<Activity> activityList = null;
	private Iterator<Activity> activityIterator = null;
	private ACTIVITY_MANAGER_STATE activityManagerState = ACTIVITY_MANAGER_STATE.IDLE;
	private boolean ifIgnoreNotification = false;
	private Timer delayedTimer = null;
	private TimerTask delayedTask = null; 

	public enum EXIT_INSTALLER_REASON {
		ON_VISIBLILITY_CANCELLED, 
		VISIBLE_BEHIND_NOT_ALLOWED, 
		USER_TRIGGERED_EXIT, 
		SESSION_CREATION_FAILED,
		INSTALLTION_COMPLETE,
		EXIT_WIZARD_RECORDING_IN_PROGRESS,
		POWER_STATE_TO_SEMISTANDY
	}

	public enum ACTIVITY_MANAGER_STATE {
		EXITING, IDLE
	}

	private InstallerActivityManager() {
		// Private Constructor
		nwrap = NativeAPIWrapper.getInstance();
		ntf = NotificationHandler.getInstance();
		activityList = new ArrayList<Activity>();
	}

	// get single instance of NativeAPIHandler class
	public synchronized static InstallerActivityManager getInstance() {
		if (singletonInstance == null) {
			singletonInstance = new InstallerActivityManager();
		}
		return singletonInstance;
	}

	public void addActivityToStack(Activity argAct) {
		Log.d(TAG, "addActivityToStack :" + argAct);
		ifIgnoreNotification = false;
		try {
			if (false == activityList.contains(argAct)) {
				activityList.add(argAct);
			} else {
				Log.d(TAG, "addActivityToStack already in activity stack");
			}
			if (activityList.size() == 1) {
				Log.d(TAG, "addActivityToStack: set euinstallertc.app.OsdStatus to 1");
				Intent intent = new Intent();
				intent.setAction("org.droidtv.euinstallertc.OSD_STATUS");
				intent.putExtra("euinstallertc.app.OsdStatus", 1);
				intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				argAct.startActivity(intent);
			}
		} catch (Exception ex) {
			Log.d(TAG, "Caught ex " + ex.getMessage());
		}
	}

	public void removeActivityFromStack(Activity argAct) {
		Log.d(TAG, "removeActivityFromStack :" + argAct);
		try {
			if (activityList.contains(argAct)) {
				activityList.remove(argAct);
			}
			if (activityList.size() == 0) {
				Log.d(TAG, "removeActivityFromStack: set euinstallertc.app.OsdStatus to 0");
				Intent intent = new Intent();
				intent.setAction("org.droidtv.euinstallertc.OSD_STATUS");
				intent.putExtra("euinstallertc.app.OsdStatus", 0);
				intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
				argAct.startActivity(intent);
			}
		} catch (Exception ex) {
			Log.d(TAG, "Caught ex " + ex.getMessage());
		}
	}

	public void exitInstallation(EXIT_INSTALLER_REASON argReason) {
		// this function should complete within 500ms
		Log.d(TAG, "exitInstallation reason: " + argReason
				+ " activityManagerState: " + activityManagerState);
		if (activityManagerState != ACTIVITY_MANAGER_STATE.EXITING) {
			activityManagerState = ACTIVITY_MANAGER_STATE.EXITING;
			
			switch (argReason) {
			case POWER_STATE_TO_SEMISTANDY:
			case ON_VISIBLILITY_CANCELLED:
			case VISIBLE_BEHIND_NOT_ALLOWED:
				if (delayedTask != null) {
					delayedTask.cancel();
				}
				if (delayedTimer != null) {
					delayedTimer.cancel();
				}		
				// release the session
				nwrap.exitWithoutInstallation();
				Log.d(TAG, "ifIgnoreNotification: " + ifIgnoreNotification);
				// show notification to user
				if ((nwrap.getCurrentContext() != null) && (false == ifIgnoreNotification)) {
					// as per Rama needn't to show any notification to user ( Analog Installation > watchtv case)
					//nwrap.showTVNofification(nwrap.getCurrentContext(), nwrap.getCurrentContext().getString(org.droidtv.ui.strings.R.string.MAIN_MSG_CHANNEL_INSTALLATION_ABORTED));
				}
				
				// trigger finish of all the activities
				finishActivityStack();
				break;
			case USER_TRIGGERED_EXIT:
				// release the session
				nwrap.exitWithoutInstallation();

				// trigger finish of all the activities
				finishActivityStack();
				break;
			case INSTALLTION_COMPLETE:
				nwrap.exitOnInstallationComplete();
				nwrap.exitNonInteruptableMode();
				ifIgnoreNotification = true;
				
				// delay finish activity stack 
				delayedTimer = new Timer();
				delayedTask = new TimerTask() {
					@Override
					public void run() {
						Log.d(TAG, "delayHandler run");
						
						if (delayedTimer != null) {
							delayedTimer.cancel();
						}

						if(nwrap.ifPendingNonInteruptableRequest) {
							//Log.d(TAG, "launched Installer Activity again, exit from Non interuptable mode to continue");
							nwrap.exitNonInteruptableMode();
						} else {
							// trigger finish of all the activities
							finishActivityStack();
						}
					}
				};
				
				// delay 3000ms
				if(activityList.isEmpty() == false){
					delayedTimer.schedule(delayedTask, 3000);
				}
				break;
			case SESSION_CREATION_FAILED:
				// release the session
				nwrap.exitWithoutInstallation();
				finishActivityStack();
				break;
			case EXIT_WIZARD_RECORDING_IN_PROGRESS:
				
				// trigger finish of all the activities
				finishActivityStack();
				break;
			default:
				break;
			}
			
			activityManagerState = ACTIVITY_MANAGER_STATE.IDLE;
		}
	}

	public synchronized void finishActivityStack() {
		Log.d(TAG, "finishActivityStack()");
		Activity actInst = null;
		/* YanFu 2017/09/25 fix [GZ-CET][V5.249.5.075] Can't change channels by ch+/ch- and key numbers, can only select witch channel list */
		nwrap.notifyPlayTvUpdateChannelDB();
		try {
			activityIterator = activityList.iterator();
			while (activityIterator.hasNext()) {
				actInst = activityIterator.next();
				Log.d(TAG, "Calling finish for activity " + actInst);
				try {
					ntf.unregisterForNotification((Observer) actInst);
					if (false == actInst.isDestroyed()) {
						actInst.finish();
					}
				} catch(Exception ex) {
					Log.d(TAG, "Caught ex " + ex.getMessage());
				}
			}
		} catch(Exception ex) {
		}
		// clear activity stack
		activityList.clear();
	}
}
