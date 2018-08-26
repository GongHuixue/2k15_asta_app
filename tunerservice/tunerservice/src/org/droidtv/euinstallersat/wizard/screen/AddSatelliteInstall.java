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

public class AddSatelliteInstall extends WizardStep implements SatelliteScreen
{

	private static final String TAG = AddSatelliteInstall.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper mNativeAPIWrapper;
	private SatelliteScreen mSatelliteScreen;
	private View view;
	private TextView mPackageName;
	private TextView mTvChannelsAdded;
	private TextView mRadioChannelsAdded;
	private TextView mStepProgPercent;
	private TextView mTotalProgPercent;
	private TextView mStepText;
	private ProgressBar mTotalProgress;
	private ProgressBar mInstallProgress;
	private Timer mTimer;
	private int mStepCount;
	private int mStepProgress;
	private int mIdxCurLNB;
	private InstalledLNBCache m_lnbCache;
	private LNBInfo m_lnbInfo;

	private String m_stopBtn_text;

	private String[] m_lnbHintText;

	private ILogoAssociationControl logoAssoInt = null;
	private ListenerImpl listener = new ListenerImpl();

	public AddSatelliteInstall(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		mSatelliteScreen = this;
		mNativeAPIWrapper = NativeAPIWrapper.getInstance();
		m_lnbCache = InstalledLNBCache.getInstance();
		m_stopBtn_text = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_STOP);
		m_lnbHintText = new String[] { mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTALLING_LNB1),
				mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTALLING_LNB2),
				mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTALLING_LNB3),
				mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_INSTALLING_LNB4) };
		loadLayout(context);
	}

	public AddSatelliteInstall(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public AddSatelliteInstall(Context context)
	{
		super(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		view = inflater.inflate(R.layout.installscreen1, null);
		addView(view);

		mPackageName = (TextView) view.findViewById(R.id.packagename);
		mTvChannelsAdded = (TextView) view.findViewById(R.id.tvchaddedValue);
		mRadioChannelsAdded = (TextView) view.findViewById(R.id.radiochAddValue);
		mTotalProgress = (ProgressBar) view.findViewById(R.id.totalProgress);
		mInstallProgress = (ProgressBar) view.findViewById(R.id.installationProgress);
		mStepText = (TextView) findViewById(R.id.step);
		mStepProgPercent = (TextView) findViewById(R.id.stepVal);
		mTotalProgPercent = (TextView) findViewById(R.id.totalprogresstextVal);
		mStepProgPercent.setText("0%");
		mTotalProgPercent.setText("0%");
		OnClickListener buttonStop_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				mNativeAPIWrapper.SetScanStops();
				mSatelliteWizard.launchScreen(ScreenRequest.INSTALLMODES, getScreenName());
			}

		};
		setButton1(m_stopBtn_text, buttonStop_Listener, VISIBLE);
		setButton2(null, null, INVISIBLE);
		setButton3(null, null, INVISIBLE);

	}

	@Override
	public void update(Observable observable, Object data)
	{
		Log.d(TAG, "update entry");

		final int eventID = ((NotificationInfoObject) data).actionID;
		final Activity l_activity = (Activity) mContext;

		switch (eventID)
		{
			case EventIDs.LNB_INSTALL_STARTED:
				Log.d(TAG, "LNB_INSTALL_STARTED");
				String l_msg = (String) ((NotificationInfoObject) data).message;
				mIdxCurLNB = Integer.parseInt(l_msg);
				m_lnbInfo = new LNBInfo();
				final String l_satName = mNativeAPIWrapper.GetSatelliteName(mIdxCurLNB);
				m_lnbInfo.m_name = l_satName;
				m_lnbInfo.m_lnbIdx = mIdxCurLNB;
				Log.d(TAG, "m_currentLNBIdx set to : " + mIdxCurLNB);
				l_activity.runOnUiThread(new Runnable()
				{
					@Override
					public void run()
					{
						setHintText(m_lnbHintText[mIdxCurLNB]);
						resetUI(l_satName);
					}
				});
				
				
				break;

			case EventIDs.LNB_INSTALL_FINISHED:
				Log.d(TAG, "LNB_INSTALL_FINISHED");
				m_lnbInfo.m_tvChannelsAdded = mNativeAPIWrapper.GetTvServices(true, mIdxCurLNB);
				m_lnbInfo.m_radioChannelsAdded = mNativeAPIWrapper.GetRadioServices(true, mIdxCurLNB);
				m_lnbCache.addItem(m_lnbInfo);
				updateChannelCount();
				break;

			case EventIDs.SERVICE_SCAN_UPDATE:
				Log.d(TAG, "SERVICE_SCAN_UPDATE");
				m_lnbInfo.m_tvChannelsAdded = mNativeAPIWrapper.GetTvServices(true, mIdxCurLNB);
				m_lnbInfo.m_radioChannelsAdded = mNativeAPIWrapper.GetRadioServices(true, mIdxCurLNB);
				updateChannelCount();
				updateTotalProgress();
				break;

			case EventIDs.SORTING_STARTED:
				Log.d(TAG, "SORTING_STARTED");
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
				Log.d(TAG, "Logo association triggered");
				launchFinishScreen();
				break;

		}
	}

	private void launchFinishScreen()
	{
		Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				Log.d(TAG,"launchFinishScreen entry");
				mSatelliteWizard.launchScreen(ScreenRequest.ADDSATFINISH, getScreenName());
			}
		});
	}
	
	private void unRegisterFromNotifications()
	{
		NotificationHandler.getInstance().unRegisterForNotification(this);
	}

	private void updateChannelCount()
	{
		Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{

				mTvChannelsAdded.setText(String.valueOf(m_lnbInfo.m_tvChannelsAdded));
				mRadioChannelsAdded.setText(String.valueOf(m_lnbInfo.m_radioChannelsAdded));
			}
		});

	}

	private void updateTotalProgress()
	{

		final int l_progress = mNativeAPIWrapper.GetServiceScanStatus();
		Activity l_activity = (Activity) mContext;
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
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.ADDSATINSTALL;
	}

	@Override
	public void screenIntialization()
	{

		// register this class for notifications
		(NotificationHandler.getInstance()).registerForNotification(mSatelliteScreen);

		mTvChannelsAdded.setVisibility(VISIBLE);
		mRadioChannelsAdded.setVisibility(VISIBLE);
		mTimer = new Timer();
		enableWaitingAnimation(true);
		mNativeAPIWrapper.SetAddInstallStart();
		(InstalledLNBCache.getInstance()).emptyCache();
		mIdxCurLNB = 0;
		mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount + 1));
	}

	private void resetUI(final String p_name)
	{
		mStepCount = 0;
		mStepProgress = 0;
		mTimer.purge();
		mTimer.cancel();
		mTvChannelsAdded.setText("0");
		mRadioChannelsAdded.setText("0");
		mTimer = new Timer();
		mTimer.schedule(new UpdateStepProgress(), 0, 5000);
		mPackageName.setText(p_name);
		mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount + 1));
			
	}
	
	
	
	
    private void startLogoAssociation() {
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
		} else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
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
						mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount + 1));
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
		
		if(mTimer!=null)
		{
			mTimer.purge();
			mTimer.cancel();
		}
		unRegisterFromNotifications();
		
		
		
	}
}
