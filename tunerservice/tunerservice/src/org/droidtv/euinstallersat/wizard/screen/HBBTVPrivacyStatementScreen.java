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
package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.euinstallersat.common.InstallerActivityManager;
import org.droidtv.euinstallersat.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
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


public class HBBTVPrivacyStatementScreen extends WizardStep implements SatelliteScreen
{

	private final String TAG = HBBTVPrivacyStatementScreen.class.getName();
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private Context mContext;
	private View searchScreen;
	private TextView informationLine;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	public HBBTVPrivacyStatementScreen(Context context)
	{
		super(context, null, 0);
	}

	public HBBTVPrivacyStatementScreen(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);
	}

	public HBBTVPrivacyStatementScreen(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		mContext = context;
		loadLayout(context, attrs, defStyle);
	}
	
   private OnClickListener buttonHBBTVOn_Listener = new OnClickListener() {
        
        @Override
        public void onClick(View v) {
            Log.d(TAG,"HBBTV On onClick called");
            nwrap.setHBBTVStatus(true);
            instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
        }
    };
    
    private OnClickListener buttonHBBTVOff_Listener = new OnClickListener() {
		
		@Override
		public void onClick(View v) {
			Log.d(TAG,"HBBTV Off onClick called");
			nwrap.setHBBTVStatus(false);
			instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
		}
	}; 
	
	private void loadLayout(final Context context, AttributeSet attrs,
			int defStyle)
	{
		
	    final LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        searchScreen = inflater.inflate(R.layout.information_layout, null);
        addView(searchScreen);
        
        informationLine = (TextView) searchScreen.findViewById(R.id.line1String);
        informationLine.setText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_ONLINE_PRIVACY));
        
		hideHint();
		
		setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), null, View.INVISIBLE);
        setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_ON), buttonHBBTVOn_Listener, View.VISIBLE);
        setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_OFF), buttonHBBTVOff_Listener, View.VISIBLE);

	}
	
	@Override
	public void update(Observable observable, Object data)
	{
	}

	@Override
	public void screenIntialization() {
		
		setButton3focussed();
	}

	@Override
	public void setInstance(SatelliteWizard wizard) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public ScreenRequest getScreenName() {
		return ScreenRequest.SATELLITESELECTION.HBBTV_PRIVACY_STATEMENT;
	}

	@Override
	public void screenExit() {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public boolean onKey(View view, int keyCode, KeyEvent event)
	{
		boolean l_ret = super.onKey(view, keyCode, event);
		if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
		{
			l_ret = true;
		} else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
		{
			l_ret = true;
		}
		else if (((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) && event.getAction() == KeyEvent.ACTION_UP)
        {
			l_ret = true;
        }
		return l_ret;
	}
}
