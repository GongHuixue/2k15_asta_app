package org.droidtv.euinstallersat.notification;

import java.util.Observable;
import java.util.Observer;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.util.LNBInfo;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.tvinput.ILogoAssociationControl.ILogoAssociationListener;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.SessionHandlerTIF.SESSION_PURPOSE;
import org.droidtv.euinstallersat.wizard.util.InstalledLNBCache;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.view.KeyEvent;


public class BackGroundUpdateInstallActivity extends Activity implements Observer {

	private static final String TAG = BackGroundUpdateInstallActivity.class.getName();
	private NativeAPIWrapper nwrap;
	private Context mContext;
	private int mStepCount;
	private TextView mTvChannelAdded;
	private TextView mTvChannelRemoved;
	private TextView mRadioChannelAdded;
	private TextView mRadioChannelRemoved;
	private TextView mStepProgPercent;
	private TextView mTotalProgPercent;
	private TextView mSatName;
	private TextView mVerticalText;
	private TextView mStatusText;
	private TextView mStepText;
	
	private Timer mTimer;
	private int mStepProgress;
	private ProgressBar mTotalProgress;
	private ProgressBar mInstallProgress;
	private ProgressBar mScreenHeaderProgessBar;
	private ProgressBar mSpinnerProgressBar;
	
	private Button mButtonFinish;
	private OnClickListener buttonFinish_Listener;

	private InstalledLNBCache m_lnbCache;
	private LNBInfo m_lnbInfo;
	private int mIdxCurLNB;
	
	private ILogoAssociationControl logoAssoInt                = null;
    private ListenerImpl            listener                   = new ListenerImpl();
    private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	
	protected void onCreate(Bundle savedInstanceState)
	{
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		mContext = this;
		Log.d(TAG, "onCreate ");
		super.onCreate(savedInstanceState);
		instActManager.addActivityToStack(this);
		nwrap = NativeAPIWrapper.getInstance();
		nwrap.enterNonInteruptableMode();
		m_lnbCache = InstalledLNBCache.getInstance();
		loadLayout();
		
	}
	
	@Override
	protected void onStart() {
		Log.d(TAG, "onStart");
		super.onStart();
		nwrap.enterNonInteruptableMode();
	}
	
	@Override
	protected void onDestroy(){
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
	}
	
	private void loadLayout()
	{
		setContentView(R.layout.background_update_install);
		mSatName = (TextView)findViewById(R.id.bg_satname);
		mTvChannelAdded = (TextView)findViewById(R.id.bg_tvchAddValue);
		mTvChannelRemoved = (TextView)findViewById(R.id.bg_tvchRemoveValue);
		mRadioChannelAdded = (TextView)findViewById(R.id.bg_radiochAddValue);
		mRadioChannelRemoved = (TextView)findViewById(R.id.bg_radiochremovevalue);
		mTotalProgress = (ProgressBar)findViewById(R.id.bg_totalProgress);
		mInstallProgress = (ProgressBar)findViewById(R.id.bg_installationProgress);
		mStepCount = 0;
		mStepText =(TextView)findViewById(R.id.bg_steptext);
		mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount+1));
		mStepProgPercent = (TextView)findViewById(R.id.bg_steptextVal);
		mTotalProgPercent = (TextView)findViewById(R.id.bg_totalprogresstextVal);
		mButtonFinish = (Button)findViewById(R.id.bg_finishbtn);
		mScreenHeaderProgessBar = (ProgressBar)findViewById(R.id.bgupdateInstall_Header_Progress);
		mSpinnerProgressBar = (ProgressBar)findViewById(R.id.progressBarSpinner);
		mVerticalText = (TextView)findViewById(R.id.bgupdateInstall_verticalText);
		mStatusText = (TextView)findViewById(R.id.bg_belowspinnertext);
		(InstalledLNBCache.getInstance()).emptyCache();
		
		screenIntialization();
		
		buttonFinish_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
				/*nwrap.setApplicationState(NativeAPIWrapper.STATE_IDLE);
				nwrap.tuneOnFinish();
				((Activity)mContext).finish();*/
			}
		};
		mButtonFinish.setOnClickListener(buttonFinish_Listener);
	}

	
	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		Log.d(TAG, "dispatchKeyEvent for background update install activity");
		int keyCode = event.getKeyCode();
		
		boolean l_ret = true;
		switch(keyCode)
		{
			case KeyEvent.KEYCODE_BACK:
				l_ret = true;
				break;
			default:
				l_ret = super.dispatchKeyEvent(event);
				break;
		}
		Log.d(TAG, "dispatchKeyEvent for background update install activity returning " + l_ret);
		return l_ret;

	}
	
	private void screenIntialization()
	{
		mTvChannelAdded.setText("0");
		mTvChannelAdded.setVisibility(View.VISIBLE);
		mTvChannelRemoved.setText("0");
		mTvChannelRemoved.setVisibility(View.VISIBLE);
		mRadioChannelAdded.setText("0");
		mRadioChannelAdded.setVisibility(View.VISIBLE);
		mRadioChannelRemoved.setText("0");
		mRadioChannelRemoved.setVisibility(View.VISIBLE);
		mStepProgPercent.setText("0%");
		mTotalProgPercent.setText("0%");
		mButtonFinish.setEnabled(false);
		//mVerticalText.setTextColor(getResources().getColor(org.droidtv.ui.tvwidget2k15.R.color.npanelbrowser_textcolor_activated));
		mVerticalText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_SAT_UPDATING));
		
		(NotificationHandler.getInstance()).registerForNotification(this);
		Log.d(TAG,"starting update");
		nwrap.setApplicationState(NativeAPIWrapper.STATE_BACKGROUND_UPDATE);
		
		//nwrap.initTVMediaPlayer(NativeAPIWrapper.TunerName.TUNER1);
		nwrap.createTIFSession(SESSION_PURPOSE.SESSION_PURPOSE_INSTALLER);
        //nwrap.startInstallation(NativeAPIEnums.InstallationMode.UPDATE_INSTALLATION);
        Log.d(TAG,"screenIntialization Exit");
		//nwrap.SetUpdateInstallStart();
	}

	@Override
	public void update(Observable observable, Object data) 
	{
		Log.d(TAG, "update entry");
		final int eventID = ((NotificationInfoObject) data).actionID;
		
		switch (eventID) 
		{
				case EventIDs.LNB_INSTALL_STARTED:
					Log.d(TAG, "LNB_INSTALL_STARTED");
					m_lnbInfo = new LNBInfo();
					mIdxCurLNB = nwrap.GetScannedLNB();
					String l_satName = nwrap.GetSatelliteName(mIdxCurLNB);
					m_lnbInfo.m_name = l_satName;
					m_lnbInfo.m_lnbIdx = mIdxCurLNB;
					resetUI(m_lnbInfo.m_name);
					updateDisplayedChannelCount();
					break;
					
				case EventIDs.LNB_INSTALL_FINISHED:
					Log.d(TAG, "LNB_INSTALL_FINISHED");
					updateCachedChannelCount();
					m_lnbCache.addItem(m_lnbInfo);
					updateDisplayedChannelCount();
					break;
					
				case EventIDs.PACKAGE_INSTALL_STARTED:
					Log.d(TAG, "PACKAGE_INSTALL_STARTED");
					m_lnbInfo = new LNBInfo();
					String l_packageName = nwrap.GetPackageName();
					m_lnbInfo.m_name = l_packageName;
					resetUI(m_lnbInfo.m_name);
					updateDisplayedChannelCount();
					break;
					
				case EventIDs.PACKAGE_INSTALL_FINISHED:
					Log.d(TAG, "PACKAGE_INSTALL_FINISHED");
					updateCachedChannelCount();
					updateDisplayedChannelCount();
					m_lnbCache.addItem(m_lnbInfo);
					break;
					
				case EventIDs.SERVICE_SCAN_UPDATE:
					Log.d(TAG, "SERVICE_SCAN_UPDATE");
					updateCachedChannelCount();
					updateDisplayedChannelCount();
					updateTotalProgress();
					break;
						
				case EventIDs.SERVICE_SCAN_COMPLETE:
					Log.d(TAG, "SERVICE_SCAN_COMPLETE");
					nwrap.saveSatelliteSettingsToPersistent();
					nwrap.commitSatelliteSettingsToPersistent();
					if (nwrap.GetSemistandbyFlag() == true) {
						/* Force finish this activity. Do synctvprovider and logo association in SemistandbyUpdate.Java 
							Further notify PlayTv */
						forceFinishUpdateInstall ();
					}
					else {
					nwrap.commitDatabaseToTvProvider(nwrap.INSTALL_TYPE_UPDATE);
					}
					break;
		
				case EventIDs.INSTALLATION_FAILED:
					Log.d(TAG, "INSTALLATION_FAILED");
					m_lnbInfo = new LNBInfo();
					m_lnbInfo.m_name = "";
					m_lnbInfo.m_tvChannelsAdded = 0;
					m_lnbInfo.m_radioChannelsAdded = 0;
					enableFinish();
					break;
				case EventIDs.NATIVELAYER_INIT_DONE:
					Log.d(TAG, "NATIVELAYER_INIT_DONE ");
					nwrap.SetUpdateInstallStart(MwDataTypes.IHsvSatelliteInstallation_InstallationBackgroundUpdate);
					break;
				case EventIDs.COMMIT_TVPROVIDER_FINISHED:
					Log.d(TAG, "COMMIT_TVPROVIDER_FINISHED");
					startLogoAssociation();
					Log.d(TAG, "Logo association triggered");
					break;
					

		}
		
	}
	
	private void resetUI(final String p_name)
	{
		Log.d(TAG,"resetUI Entry");
		final Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				mStepCount = 0;
				mStepProgress = 0;
				if (mTimer != null)
				{
					mTimer.purge();
					mTimer.cancel();
				}
				Log.d(TAG, "resetUI Entry 1");
				mTvChannelAdded.setText("0");
				mRadioChannelAdded.setText("0");
				mTvChannelRemoved.setText("0");
				mRadioChannelRemoved.setText("0");
				mTimer = new Timer();
				mTimer.schedule(new UpdateStepProgress(), 0, 5000);
				if (mSatName != null)
				{
					mSatName.setText(p_name);
				}
				Log.d(TAG, "resetUI Exit");
			}
		});
	}
	
	private void updateCachedChannelCount()
	{
		Log.d(TAG,"updateCachedChannelCount");
		m_lnbInfo.m_tvChannelsAdded = nwrap.GetTvServices(true, mIdxCurLNB);
		m_lnbInfo.m_radioChannelsAdded = nwrap.GetRadioServices(true, mIdxCurLNB);
		m_lnbInfo.m_tvChannelsRemoved = nwrap.GetTvServices(false, mIdxCurLNB);
		m_lnbInfo.m_radioChannelsRemoved = nwrap.GetRadioServices(false, mIdxCurLNB);
	}
	
	private void updateDisplayedChannelCount()
	{		
		final Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				mTvChannelAdded.setText(String.valueOf(m_lnbInfo.m_tvChannelsAdded));
				mRadioChannelAdded.setText(String.valueOf(m_lnbInfo.m_radioChannelsAdded));
				mTvChannelRemoved.setText(String.valueOf(m_lnbInfo.m_tvChannelsRemoved));
				mRadioChannelRemoved.setText(String.valueOf(m_lnbInfo.m_radioChannelsRemoved));
			}
		});

	}
	
	private void updateTotalProgress()
	{
		final int l_progress = nwrap.GetServiceScanStatus();
		((Activity) mContext).runOnUiThread(new Runnable() 
		{
			public void run()
			{
				mTotalProgress.setProgress(l_progress);
				mTotalProgPercent.setText(Integer.toString(l_progress) + "%");
			}
		});
	}
	
	class UpdateStepProgress extends TimerTask
	{
		@Override
		public void run()
		{
			Log.d(TAG, "in timer task to UpdateStepProgress");
			Activity l_activity = (Activity) mContext;
			l_activity.runOnUiThread(new Runnable()
			{

				@Override
				public void run()
				{
					mStepProgress += 1; /* update the Step progress by 1 count */
					if (mStepProgress > 99)
					{
						mStepCount++;
						mStepProgress = 1;
						mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount+1));
					}
					mInstallProgress.setProgress(mStepProgress);
					mStepProgPercent.setText(Integer.toString(mStepProgress) + "%");
					Log.d(TAG, "UpdateStepProgress exit run");
				}
			});

		}
	}
	
	private void startLogoAssociation()
	{
		Log.d(TAG, "startLogoAssociation");
		Intent i = new Intent("org.droidtv.tvcontentprovider.LogoService");
		((Activity) mContext).bindService(i, mConnection, Context.BIND_AUTO_CREATE);
	}

	private ServiceConnection mConnection = new ServiceConnection()
	{

		@Override
		public void onServiceConnected(ComponentName name, IBinder service)
		{
			Log.d(TAG, "ILogoAssociationControl called");

			logoAssoInt = ILogoAssociationControl.Instance.asInterface(service);
			if (logoAssoInt != null)
			{
				Log.d(TAG, "logoAssoInt is not null");
				logoAssoInt.registerListenerCallback(listener);
				logoAssoInt.StartLogoAssociation(ILogoAssociationControl.MEDIUM_SATELLITE);
			} 
			else
			{
				Log.d(TAG, "NULL logoAssoInt found");
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name)
		{
			// TODO Auto-generated method
			// stub
		}
	};

	public class ListenerImpl extends ILogoAssociationListener
	{

		@Override
		public void onLogoAssociationStateChanged(int state)
		{
			Log.d(TAG, "onLogoAssociationStateChanged called with State:" + state);

			if (state == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_COMPLETE)
			{
				Log.d(TAG, "Logo Association complete received");

				// Navigating to next screen
				try
				{
					((Activity) mContext).unbindService(mConnection);
				} catch (Exception ex)
				{
					Log.d(TAG, "Exception caught while unbinding service org.droidtv.tvcontentprovider.LogoService");
				}
				enableFinish();

			}
		}
	}
	
	private void enableFinish()
	{

		Log.i(TAG, "enableFinish:");
		unRegisterFromNotifications();
		
		Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable()
		{
			
			@Override
			public void run()
			{
				mTotalProgress.setProgress(100);
    			mTotalProgPercent.setText("100%");
				mInstallProgress.setProgress(100);
				mStepProgPercent.setText("100%");
				if(mTimer != null)
				{
					mTimer.purge();
					mTimer.cancel();
				}
				mScreenHeaderProgessBar.setProgress(100);
				mButtonFinish.setEnabled(true);
				mVerticalText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_UPDATE_FINISHED));
				mStatusText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_UPDATE_FINISHED));
				mSpinnerProgressBar.setVisibility(View.INVISIBLE);
			}
		});

    }

	private void forceFinishUpdateInstall () 
	{
		unRegisterFromNotifications ();
		((Activity)mContext).finish();
	}
		
	private void unRegisterFromNotifications()
	{
		Log.i(TAG, "unRegisterFromNotifications called");
		// register this class for notifications
		(NotificationHandler.getInstance()).unRegisterForNotification(this);
	}


}
