package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.InstalledLNBCache;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

public class MiniPrescanScreen extends WizardStep implements SatelliteScreen
{

	private static final String TAG = MiniPrescanScreen.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private NativeAPIWrapper mNativeAPIWrapper;
	private SatelliteScreen mSatelliteScreen;
	private View view;
	private TextView mPackageName;
	private TextView mStepProgPercent;
	private TextView mTotalProgPercent;
	private TextView mStepText;
	private ProgressBar mInstallProgress;
	private Timer mTimer;
	private int mStepCount;
	private int mStepProgress;
	private InstalledLNBCache m_lnbCache;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;

	private String m_stopBtn_text;


	public MiniPrescanScreen(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		mSatelliteScreen = this;
		mNativeAPIWrapper = NativeAPIWrapper.getInstance();
		m_lnbCache = InstalledLNBCache.getInstance();
		m_stopBtn_text = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_STOP);

		loadLayout(context);
	}

	public MiniPrescanScreen(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public MiniPrescanScreen(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		view = inflater.inflate(R.layout.installscreen, null);
		addView(view);

		mPackageName = (TextView) view.findViewById(R.id.packagename);
		mInstallProgress = (ProgressBar) view.findViewById(R.id.installationProgress);
		ProgressBar l_totalProgress = (ProgressBar) view.findViewById(R.id.totalProgress);
		TextView l_tvChannels = (TextView)findViewById(R.id.tvchadded);
		TextView l_radioChannels = (TextView)findViewById(R.id.radiochAdd);
		TextView l_totalProgressText = (TextView)findViewById(R.id.totalprogresstext);
		mStepText = (TextView) findViewById(R.id.step);
		mStepProgPercent = (TextView) findViewById(R.id.stepVal);
		mTotalProgPercent = (TextView) findViewById(R.id.totalprogresstextVal);
		mStepProgPercent.setText("0%");
		mTotalProgPercent.setText("");
		l_totalProgress.setVisibility(View.INVISIBLE);
		l_tvChannels.setVisibility(View.INVISIBLE);
		l_radioChannels.setVisibility(View.INVISIBLE);
		l_totalProgressText.setVisibility(View.INVISIBLE);
		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_UPDATE_MINI_PRESCAN));
		mPackageName.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_DIGITURK_LNB_DETECTION));
		OnClickListener buttonStop_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
		        mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_SAT_AUTOSTORE_STOP), "");
		    	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_SAT_AUTOSTORE_STOP));
		    	
		    	ModalDialogFooterButtonProp mNoButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
		    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NO),
		    			true,
		    			new ModalDialogInterface.OnClickListener(){
		    				@Override
		    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
		    					Log.d(TAG, "MAIN_BUTTON_NO clicked ");
		    					mModalDialog.hide();
		    				}
		    			});
		    	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
		    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_YES),
		    			true,
		    			new ModalDialogInterface.OnClickListener(){
		    				@Override
		    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
		    					Log.d(TAG, "MAIN_BUTTON_YES clicked ");
		    					Log.d(TAG, "Stop Dialog: Yes button pressed for screen: " + mSatelliteWizard.getCurrentScreen());
								if (mTimer != null)
								{
									mTimer.purge();
									mTimer.cancel();
								}
								enableWaitingAnimation(false);
								mNativeAPIWrapper.SetScanStops();
								mSatelliteWizard.launchScreen(ScreenRequest.STARTSCREEN, getScreenName());
		    					mModalDialog.hide();
		    				}
		    			});
		    	mModalDialog = mBuilder.build();
		    	mModalDialog.setCancelable(false);
		    	mModalDialog.show();
		    	mNoButton.requestFocus();
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

			case EventIDs.PRESCAN_SUCCESS:
				Log.d(TAG, "PRESCAN_SUCCESS");
				l_activity.runOnUiThread(new Runnable()
				{
					@Override
					public void run()
					{
						mSatelliteWizard.launchScreen(ScreenRequest.UPDATESCAN, getScreenName());
						
					}
				});
				break;
				
			case EventIDs.FOUND_DIFFERENT_SATELLITE:
				Log.d(TAG, "FOUND_DIFFERENT_SATELLITE");
				l_activity.runOnUiThread(new Runnable()
				{
					@Override
					public void run()
					{
						mSatelliteWizard.launchScreen(ScreenRequest.INSTALLSCREEN, getScreenName());
					}
				});
				break;	
				
	
			case EventIDs.PRESCAN_FAIL:
				Log.d(TAG, "PRESCAN_FAIL");
				l_activity.runOnUiThread(new Runnable()
				{
					@Override
					public void run()
					{
						(InstalledLNBCache.getInstance()).setInstallationState(InstalledLNBCache.INSTALLATION_FAILURE);
						mSatelliteWizard.launchScreen(ScreenRequest.FINISHUPDATE, getScreenName());
					}
				});
				break;

		}
	}
	
	
	
	private void unRegisterFromNotifications()
	{
		NotificationHandler.getInstance().unRegisterForNotification(this);
	}

	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.MINI_PRESCAN;
	}

	@Override
	public void screenIntialization()
	{
		int		mLnbToPerformMiniPrescan = 0;
		Log.d(TAG,"screenIntialization");
		(NotificationHandler.getInstance()).registerForNotification(mSatelliteScreen);
		mTimer = new Timer();
		m_lnbCache.emptyCache();
		enableWaitingAnimation(true);
		mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount + 1));
		startStepProgress();
		mLnbToPerformMiniPrescan = mNativeAPIWrapper.GetMduSlotForMiniPrescan();
		mNativeAPIWrapper.SetScanStarts(MwDataTypes.IHsvSatelliteInstallation_InstallationMiniPrecan, mLnbToPerformMiniPrescan);
	}


	private void startStepProgress()
	{
		mStepCount = 0;
		mStepProgress = 0;
		mTimer.purge();
		mTimer.cancel();
		mTimer = new Timer();
		mTimer.schedule(new UpdateStepProgress(), 0, 5000);
		mStepText.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_STEP) + " " + (mStepCount + 1));
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
