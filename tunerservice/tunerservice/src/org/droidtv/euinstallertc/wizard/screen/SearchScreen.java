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

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.euinstallertc.wizard.settings.WizardSettingsActivity;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;

import android.content.Context;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

/*
 * This class allows the user start the channel scan 
 * If the user clicks on "Start" button the user will navigated to start scan page.
 * If the user clicks on "Settings" button the user will navigated to settings page. 
 */
public class SearchScreen extends WizardStep implements IInstallationScreen
{

	private static final String TAG = SearchScreen.class.getName();
	private InstallationWizard mInstallationWizard;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private ITvSettingsManager mTvSettingsManager = ITvSettingsManager.Instance.getInterface();
	private Context mContext;
	private View searchScreen;
	private TextView informationLine;

	public SearchScreen(Context context)
	{
		super(context, null, 0);
	}

	public SearchScreen(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);
	}

	public SearchScreen(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		mContext = context;
		loadLayout(context, attrs, defStyle);
	}
	
	private OnClickListener buttonPrevious_Listener = new OnClickListener() {
        
	    @Override
        public void onClick(View v) {
            mInstallationWizard.launchPreviousScreen();
        }
    }; 
    
   private OnClickListener buttonStart_Listener = new OnClickListener() {
        
        @Override
        public void onClick(View v) {
            Log.i(TAG,"Search Screen onClick called");
			if (PlayTvUtils.isPbsMode()) {
	            nwrap.setLCNSortingControl(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_LCN, 0, 0));

				NativeAPIEnums.DVBTOrDVBC curIsDVBTorDVBC = nwrap.getCurrentMedium();
				if (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_C_C2, 0, 0)) {
					nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBC);
					nwrap.setWSSetFreeCAChannels(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_SCRAMBLED_CHANNELS, 0, 0));
				}
				if (0 != mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_DVB_T_T2, 0, 0)) {
					nwrap.setMedium(NativeAPIEnums.DVBTOrDVBC.DVBT);
					nwrap.setWSSetFreeCAChannels(mTvSettingsManager.getInt(TvSettingsConstants.PBSMGR_PROPERTY_CHANNELS_INSTALL_SCRAMBLED_CHANNELS, 0, 0));
				}
				nwrap.setMedium(curIsDVBTorDVBC);
			} else {
				nwrap.setLCNSortingControl(1);
			}
            mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCHING_SCREEN,getScreenName());
        }
    };
    
    private OnClickListener buttonSettings_Listener = new OnClickListener() {
		
		@Override
		public void onClick(View v) {
			mContext.startActivity(new Intent(mContext, WizardSettingsActivity.class));
		}
	}; 
	
	private void loadLayout(final Context context, AttributeSet attrs,
			int defStyle)
	{
		
	    final LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        searchScreen = inflater.inflate(R.layout.information_layout, null);
        addView(searchScreen);
        
        informationLine = (TextView) searchScreen.findViewById(R.id.line1String);
        informationLine.setText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_START_SEARCH));
        
		hideHint();
		
		OnClickListener buttonSkip_Listener = new OnClickListener() {

            @Override
            public void onClick(View v) {
                nwrap.stopInstallation(true);
            }
        };
        
		if(nwrap.ifVirginInstallation()){
		    setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SKIP), buttonSkip_Listener, View.VISIBLE);
        }else{
            setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener, View.VISIBLE);
        }
        
        setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SETTINGS), buttonSettings_Listener, View.INVISIBLE);
        setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_START), buttonStart_Listener, View.VISIBLE);
		
		if(nwrap.ifSettingsAvaliable()){
			setButton2(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SETTINGS), buttonSettings_Listener,View.VISIBLE);
		}else{
			setButton2(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SETTINGS), buttonSettings_Listener,View.INVISIBLE);
		}
	}
	
	@Override
	public void setInstance(InstallationWizard wizard)
	{
		mInstallationWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return InstallationWizard.ScreenRequest.SEARCH_SCREEN;
	}

	@Override
	public void update(Observable observable, Object data)
	{
	}

	@Override
	public void screenIntialization() {
		
		setButton3focussed();
		
		if(nwrap.ifSettingsAvaliable()){
			setButton2(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SETTINGS), buttonSettings_Listener,View.VISIBLE);
		}else{
			setButton2(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SETTINGS), buttonSettings_Listener,View.INVISIBLE);
		}
	}
}
