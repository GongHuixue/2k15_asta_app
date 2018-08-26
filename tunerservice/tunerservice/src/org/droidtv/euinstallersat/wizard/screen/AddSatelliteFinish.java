package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.InstalledLNBCache;
import org.droidtv.euinstallersat.wizard.util.LNBInfo;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

public class AddSatelliteFinish extends WizardStep implements SatelliteScreen
{

	private static final String TAG = AddSatelliteFinish.class.getName();
	private Context mContext;
	private NativeAPIWrapper mNativeApiWrapper;
	private View view;
	private TextView[] m_nameTextArray;
	private TextView[] m_tvCountArray;
	private TextView[] m_radioCountArray;
	private TextView m_tvTitle;
	private TextView m_radioTitle;
	private InstalledLNBCache m_cache;
	private int MAX_LNB_COUNT = 4;
	private TimerTask localProgTimerTask         = null;
    private Timer     localProgTimer             = null;
    private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	public AddSatelliteFinish(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		mNativeApiWrapper = NativeAPIWrapper.getInstance();
		m_cache = InstalledLNBCache.getInstance();
		loadLayout(context);
	}

	public AddSatelliteFinish(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public AddSatelliteFinish(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		view = inflater.inflate(R.layout.addsatfinishscreen, null);
		addView(view);

		OnClickListener butondone_listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Log.d(TAG,"Ok on finish");
				onFinishButton();
			}
		};

		setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE), butondone_listener, VISIBLE);
		setButton2(null, null, INVISIBLE);
		setButton3(null, null, INVISIBLE);

		
		
		initTextViews();
	}
	
	private void onFinishButton(){
		Log.d(TAG, "onFinishButton");
		
		stopInternalTimer();
		instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
		//mNativeApiWrapper.tuneOnFinish();
		//((Activity)view.getContext()).setResult(SatelliteConstants.RESULT_CODE_CLOSE_SETTINGS_ACTIVITY);
		//((Activity)view.getContext()).finish();
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
		return ScreenRequest.ADDSATFINISH;
	}
	
	private void initTextViews()
	{
		Log.d(TAG, "initSigStrengthArray entry");
		
		
		m_nameTextArray = new TextView[MAX_LNB_COUNT];
		m_nameTextArray[0] = (TextView) view.findViewById(R.id.satelnb1text);
		m_nameTextArray[1] = (TextView) view.findViewById(R.id.satellitelnb2text);
		m_nameTextArray[2] = (TextView) view.findViewById(R.id.satellitelnb3text);
		m_nameTextArray[3] = (TextView) view.findViewById(R.id.satellitelnb4text);
		
		m_tvCountArray = new TextView[MAX_LNB_COUNT];
		m_tvCountArray[0] = (TextView) view.findViewById(R.id.tvvalue);
		m_tvCountArray[1] = (TextView) view.findViewById(R.id.tvvalue2);
		m_tvCountArray[2] = (TextView) view.findViewById(R.id.tvvalue3);
		m_tvCountArray[3] = (TextView) view.findViewById(R.id.tvvalue4);
		
		
		m_radioCountArray = new TextView[MAX_LNB_COUNT];
		m_radioCountArray[0] = (TextView) view.findViewById(R.id.radiovalue);
		m_radioCountArray[1] = (TextView) view.findViewById(R.id.radiovalue2);
		m_radioCountArray[2] = (TextView) view.findViewById(R.id.radiovalue3);
		m_radioCountArray[3] = (TextView) view.findViewById(R.id.radiovalue4);
		
		m_tvTitle = (TextView) view.findViewById(R.id.tv);
		m_radioTitle = (TextView) view.findViewById(R.id.radio);
	}

	@Override
	public void screenIntialization()
	{
		Log.d(TAG, "screenIntialization entry");
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
		
		for(l_idx = 0; l_idx < l_count; l_idx ++)
		{
			l_infoObj = m_cache.getItemAtIndex(l_idx);
			m_nameTextArray[l_idx].setText(l_infoObj.m_name);
			m_tvCountArray[l_idx].setText(Integer.toString(l_infoObj.m_tvChannelsAdded));
			m_radioCountArray[l_idx].setText(Integer.toString(l_infoObj.m_radioChannelsAdded));
		}
		m_tvTitle.setVisibility(View.VISIBLE);
		m_radioTitle.setVisibility(View.VISIBLE);
		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_AUTOSTORE_FINISHED));
		Log.d(TAG,"showInstalledLNBInfo exit");
	}
	
	private void showResultFailure()
	{
		Log.d(TAG,"showResultFailure entry");
		m_nameTextArray[0].setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_LNB_NO_CHANNELS_FOUND));
		m_tvTitle.setVisibility(View.INVISIBLE);
		m_radioTitle.setVisibility(View.INVISIBLE);
		setHintText("");
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
		else if (((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) && event.getAction() == KeyEvent.ACTION_UP)
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
