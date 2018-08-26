package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.InstalledLNBCache;
import org.droidtv.euinstallersat.wizard.util.LNBInfo;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;
import android.app.Activity;

public class FinishUpdate extends WizardStep implements SatelliteScreen
{

	private final String TAG = FinishUpdate.class.getName();
	private Context mContext;
	private InstalledLNBCache m_cache;
	private int MAX_ENTRY_COUNT = 5;
	private TextView[] m_nameTextArray;
	private TextView[] m_tvCountArray;
	private TextView[] m_radioCountArray;
	private TextView m_tvTitle;
	private TextView m_radioTitle;
	private View view;
	private TimerTask localProgTimerTask         = null;
    private Timer     localProgTimer             = null;
    private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	public FinishUpdate(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		loadLayout(context);
		m_cache = InstalledLNBCache.getInstance();
	}

	public FinishUpdate(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public FinishUpdate(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		view = inflater.inflate(R.layout.finishupdate, null);
		addView(view);

		OnClickListener buttonFinish_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				Log.d(TAG,"Ok on finish");
				onFinishButton();
			}
		};

		setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE), buttonFinish_Listener, VISIBLE);
		setButton2(null, null, INVISIBLE);
		setButton3(null, null, INVISIBLE);
		
		
		initTextViews();
	}
	
	private void onFinishButton(){
		Log.d(TAG, "onFinishButton");
		
		stopInternalTimer();
		((Activity) mContext).runOnUiThread(new Runnable(){
			public void run(){
				instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
			}
		});
		
		/*m_wrapper.tuneOnFinish();
		((Activity)view.getContext()).setResult(SatelliteConstants.RESULT_CODE_CLOSE_SETTINGS_ACTIVITY);
		((Activity)view.getContext()).finish();*/
	}
	
	private void startInternalTimer(){
		Log.d(TAG, "startInternalTimer");
		stopInternalTimer();
		
		localProgTimerTask = new TimerTask() {
	        @Override
	        public void run() {
	        	Log.d(TAG, "timeout");
	        	onFinishButton();
	    	}
        };

        localProgTimer = new Timer();
        localProgTimer.schedule(localProgTimerTask, 1000*60*10); // after 10min autoexit the screen
		
	}
	
	private void  stopInternalTimer(){
		Log.d(TAG, "stopInternalTimer");
		
		if (localProgTimerTask != null) {
            localProgTimerTask.cancel();
        }

        if (localProgTimer != null) {
            localProgTimer.cancel();
        }
	}
	
	@Override
	public void update(Observable observable, Object data)
	{

	}

	@Override
	public void setInstance(SatelliteWizard wizard)
	{
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.FINISHUPDATE;
	}
	
	private void initTextViews()
	{
		Log.d(TAG, "initTextViews entry");
		
		m_nameTextArray = new TextView[MAX_ENTRY_COUNT];
		m_nameTextArray[0] = (TextView) view.findViewById(R.id.satname1);
		m_nameTextArray[1] = (TextView) view.findViewById(R.id.satname2);
		m_nameTextArray[2] = (TextView) view.findViewById(R.id.satname3);
		m_nameTextArray[3] = (TextView) view.findViewById(R.id.satname4);
		m_nameTextArray[4] = (TextView) view.findViewById(R.id.satname5);
		
		m_tvCountArray = new TextView[MAX_ENTRY_COUNT];
		m_tvCountArray[0] = (TextView) view.findViewById(R.id.tvvalue1);
		m_tvCountArray[1] = (TextView) view.findViewById(R.id.tvvalue2);
		m_tvCountArray[2] = (TextView) view.findViewById(R.id.tvvalue3);
		m_tvCountArray[3] = (TextView) view.findViewById(R.id.tvvalue4);
		m_tvCountArray[4] = (TextView) view.findViewById(R.id.tvvalue5);
		
		m_radioCountArray = new TextView[MAX_ENTRY_COUNT];
		m_radioCountArray[0] = (TextView) view.findViewById(R.id.radiovalue1);
		m_radioCountArray[1] = (TextView) view.findViewById(R.id.radiovalue2);
		m_radioCountArray[2] = (TextView) view.findViewById(R.id.radiovalue3);
		m_radioCountArray[3] = (TextView) view.findViewById(R.id.radiovalue4);
		m_radioCountArray[4] = (TextView) view.findViewById(R.id.radiovalue5);
		
		m_tvTitle = (TextView) view.findViewById(R.id.tv);
		m_radioTitle = (TextView) view.findViewById(R.id.radio);
		
		Log.d(TAG, "initTextViews Exit");
	}

	@Override
	public void screenIntialization()
	{
		Log.d(TAG, "screenIntialization Entry");
		if(m_cache.getInstallationState() == InstalledLNBCache.INSTALLATION_SUCCESS)
		{
			showInstalledLNBInfo();
		}
		else
		{
			showResultFailure();
		}
		startInternalTimer();
		Log.d(TAG, "screenIntialization Exit");
	}
	
	private void showInstalledLNBInfo()
	{
		Log.d(TAG,"showInstalledLNBInfo entry");
		int l_idx;
		int l_count = m_cache.getSize();
		LNBInfo  l_infoObj;
		
		l_count = (l_count > MAX_ENTRY_COUNT)?MAX_ENTRY_COUNT:l_count;
		
		for(l_idx = 0; l_idx < l_count; l_idx ++)
		{
			l_infoObj = m_cache.getItemAtIndex(l_idx);
			m_nameTextArray[l_idx].setText(l_infoObj.m_name);
			m_tvCountArray[l_idx].setText("+" + Integer.toString(l_infoObj.m_tvChannelsAdded) + ",-" +  Integer.toString(l_infoObj.m_tvChannelsRemoved));
			m_radioCountArray[l_idx].setText("+" + Integer.toString(l_infoObj.m_radioChannelsAdded) + ",-" +  Integer.toString(l_infoObj.m_radioChannelsRemoved));
		}
		m_tvTitle.setVisibility(View.VISIBLE);
		m_radioTitle.setVisibility(View.VISIBLE);
		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_UPDATE_FINISHED));
		Log.d(TAG,"showInstalledLNBInfo exit");
	}
	
	private void showResultFailure()
	{
		Log.d(TAG,"showResultFailure entry");
		m_nameTextArray[0].setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_LNB_NO_CHANNELS_FOUND));
		setHintText("");
		m_tvTitle.setVisibility(View.INVISIBLE);
		m_radioTitle.setVisibility(View.INVISIBLE);
		Log.d(TAG,"showResultFailure exit");
	}
	
	@Override
	public boolean onKey(View view, int keyCode, KeyEvent event)
	{
		boolean l_ret = super.onKey(view, keyCode, event);
		if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
		{
			//super.onKey(view, keyCode, event);
			l_ret = true;
		} else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
		{
			//super.onKey(view, keyCode, event);
			l_ret = true;
		}
		else if(((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) && event.getAction() == KeyEvent.ACTION_UP)
        {
			l_ret = true;
        }
		
		return l_ret;
	}

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		stopInternalTimer();
	}

}
