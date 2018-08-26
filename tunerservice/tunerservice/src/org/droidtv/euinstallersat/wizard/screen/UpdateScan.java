package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.InstalledLNBCache;
import org.droidtv.euinstallersat.wizard.util.LNBInfo;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.tvinput.ILogoAssociationControl.ILogoAssociationListener;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

public class UpdateScan extends WizardStep implements SatelliteScreen
{

	private static final String TAG = UpdateScan.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private int mStepCount;
	private View view;
	private TextView mTvChannelAdded;
	private TextView mTvChannelRemoved;
	private TextView mRadioChannelAdded;
	private TextView mRadioChannelRemoved;
	private SatelliteScreen mSatelliteScreen;
	private TextView mStepProgPercent;
	private TextView mTotalProgPercent;
	private NativeAPIWrapper mNativeAPIWrapper;
	private ProgressBar mTotalProgress;
	private TextView mSatName;

	
	private InstalledLNBCache m_lnbCache;
	private LNBInfo m_lnbInfo;
	private int mIdxCurLNB;

	private Timer mTimer;
	private int mStepProgress;
	private TextView mStepText;
	private ProgressBar mInstallProgress;
	private boolean m_isInstallationComplete = false;
	
	private ILogoAssociationControl logoAssoInt                = null;
    private ListenerImpl            listener                   = new ListenerImpl();

	public UpdateScan(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		mSatelliteScreen = this;
		mNativeAPIWrapper = NativeAPIWrapper.getInstance();
		m_lnbCache = InstalledLNBCache.getInstance();
		loadLayout(context);
	}

	public UpdateScan(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public UpdateScan(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{

		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		view = inflater.inflate(R.layout.updatescan, null);
		addView(view);

		mSatName = (TextView) view.findViewById(R.id.satname);
		mTvChannelAdded = (TextView) view.findViewById(R.id.tvchAddValue);
		mTvChannelRemoved = (TextView) view.findViewById(R.id.tvchRemoveValue);
		mRadioChannelAdded = (TextView) view.findViewById(R.id.radiochAddValue);
		mRadioChannelRemoved = (TextView) view.findViewById(R.id.radiochremovevalue);
		mTotalProgress = (ProgressBar) view.findViewById(R.id.totalProgress);
		mInstallProgress = (ProgressBar) view.findViewById(R.id.installationProgress);
		mStepCount = 0;
		mStepText = (TextView) findViewById(R.id.step);
		mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount+1));
		mStepProgPercent = (TextView)findViewById(R.id.stepVal);
		mTotalProgPercent = (TextView)findViewById(R.id.totalprogresstextVal);
		mStepProgPercent.setText("0%");
		mTotalProgPercent.setText("0%");
		Log.i(TAG, "mTvChannelValue:" + mTvChannelAdded);
		(InstalledLNBCache.getInstance()).emptyCache();

		OnClickListener buttonStop_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				mNativeAPIWrapper.SetScanStops();
				mSatelliteWizard.launchScreen(ScreenRequest.INSTALLMODES, getScreenName());
			}
		};
		
		String l_stopBtn_text =  mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_STOP);
		
		setButton1(l_stopBtn_text, buttonStop_Listener, VISIBLE);
		setButton2(null, null, INVISIBLE);
		setButton3(null, null, INVISIBLE);
		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_UPDATING));
	}
	
	private void resetUI(final String p_name)
	{
		Log.d(TAG, "resetUI Entry");
		
		
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
		m_lnbInfo.m_tvChannelsAdded = mNativeAPIWrapper.GetTvServices(true, mIdxCurLNB);
		m_lnbInfo.m_radioChannelsAdded = mNativeAPIWrapper.GetRadioServices(true, mIdxCurLNB);
		m_lnbInfo.m_tvChannelsRemoved = mNativeAPIWrapper.GetTvServices(false, mIdxCurLNB);
		m_lnbInfo.m_radioChannelsRemoved = mNativeAPIWrapper.GetRadioServices(false, mIdxCurLNB);
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

		final int l_progress = mNativeAPIWrapper.GetServiceScanStatus();
		
		final Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				mTotalProgress.setProgress(l_progress);
				mTotalProgPercent.setText(Integer.toString(l_progress) + "%");
			}
		});
		
		
	}
	
	@Override
	public void update(Observable observable, final Object data)
	{
		Log.d(TAG, "update entry");

		final int eventID = ((NotificationInfoObject) data).actionID;
		
				switch (eventID)
				{
					case EventIDs.LNB_INSTALL_STARTED:
						Log.d(TAG, "LNB_INSTALL_STARTED");
						m_lnbInfo = new LNBInfo();
						String l_msg = (String) ((NotificationInfoObject) data).message;
						mIdxCurLNB = Integer.parseInt(l_msg);
						Log.d(TAG, "m_currentLNBIdx set to : " + mIdxCurLNB);
						String l_satName = mNativeAPIWrapper.GetSatelliteName(mIdxCurLNB);
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
						String l_packageName = mNativeAPIWrapper.GetPackageName();
						m_lnbInfo.m_name = l_packageName;
						resetUI(l_packageName);
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
						
					case EventIDs.SORTING_STARTED:
						Log.d(TAG, "SORTING_STARTED");
						final Activity l_activity = (Activity) mContext;
						l_activity.runOnUiThread(new Runnable()
						{
							@Override
							public void run()
							{
								setButton1Enabled(false);
							}
						});
						break;
						
					case EventIDs.SERVICE_SCAN_COMPLETE:
						Log.d(TAG, "SERVICE_SCAN_COMPLETE");
						mNativeAPIWrapper.saveSatelliteSettingsToPersistent();
						mNativeAPIWrapper.commitSatelliteSettingsToPersistent();
						mNativeAPIWrapper.commitDatabaseToTvProvider(mNativeAPIWrapper.INSTALL_TYPE_UPDATE);
						break;

					case EventIDs.INSTALLATION_FAILED:
						Log.d(TAG, "INSTALLATION_FAILED");
						(InstalledLNBCache.getInstance()).setInstallationState(InstalledLNBCache.INSTALLATION_FAILURE);
						launchFinishScreen();
						break;
						
					case EventIDs.COMMIT_TVPROVIDER_FINISHED:
						Log.d(TAG, "COMMIT_TVPROVIDER_FINISHED");
						startLogoAssociation();
						launchFinishScreen();
						break;

				}

			

	}


	

	private void launchFinishScreen()
	{

		Log.i(TAG, "launchScreen:" + mSatelliteWizard);
		Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				m_isInstallationComplete = true;
				enableWaitingAnimation(false);
				mSatelliteWizard.launchScreen(ScreenRequest.FINISHUPDATE, getScreenName());
			}
		});

	}
	
	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.UPDATESCAN;
	}

	@Override
	public void screenIntialization()
	{
		Log.i(TAG, "mTvChannelValue:" + mTvChannelAdded);
		mTvChannelAdded.setVisibility(VISIBLE);
		mTvChannelRemoved.setVisibility(VISIBLE);
		mRadioChannelAdded.setVisibility(VISIBLE);
		mRadioChannelRemoved.setVisibility(VISIBLE);
		(NotificationHandler.getInstance()).registerForNotification(mSatelliteScreen);
		mIdxCurLNB = 0;
		m_isInstallationComplete = false;
		mNativeAPIWrapper.SetUpdateInstallStart(MwDataTypes.IHsvSatelliteInstallation_InstallationUpdate);
		enableWaitingAnimation(true);
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
				//logoAssoInt.registerListenerCallback(listener);
				logoAssoInt.StartLogoAssociation(ILogoAssociationControl.MEDIUM_SATELLITE);
			} else
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
				//launchFinishScreen();

			}
		}
	}
	
	 @Override
	    public boolean onKey(View view, int keyCode, KeyEvent event)
	    {
			 boolean l_ret = false;
			 if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
			 {
				super.onKey(view, keyCode, event); 
				l_ret = true;
			 }
			 else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
			 {
				 super.onKey(view, keyCode, event); 
				 l_ret = true; 
			 }
			 
			 return l_ret;
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
	};

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		enableWaitingAnimation(false);
		if (mTimer != null)
		{
			mTimer.purge();
			mTimer.cancel();
		}
		(NotificationHandler.getInstance()).unRegisterForNotification(mSatelliteScreen);
		
	}
}
