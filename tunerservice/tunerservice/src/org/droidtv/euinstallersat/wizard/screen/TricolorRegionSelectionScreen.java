/*
 *  Copyright(C) 2014 TP Vision Holding B.V.,
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

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;



import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;


/**
 * @author shibu.salam
 *
 */
public class TricolorRegionSelectionScreen extends WizardStep implements
		SatelliteScreen {

	private static final String TAG = TricolorRegionSelectionScreen.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private RadioSelector mRadioSelector;
	private NativeAPIWrapper mNativeAPIWrapper;
	private SatelliteScreen mSatelliteScreen;
	
	/**
	 * @param arg0
	 * @param arg1
	 * @param arg2
	 */
	public TricolorRegionSelectionScreen(Context ctx, AttributeSet attrSet, int defStyle) {
		super(ctx, attrSet, defStyle);
		mContext = ctx;
		mNativeAPIWrapper = NativeAPIWrapper.getInstance();
		mSatelliteScreen = this;
		loadLayout ();
	}
	
	/**
	 * @param arg0
	 * @param arg1
	 */
	public TricolorRegionSelectionScreen(Context ctx, AttributeSet attrSet) {
		this (ctx, attrSet, 0);
	}
	
	/**
	 * @param arg0
	 * 
	 */
	public TricolorRegionSelectionScreen(Context ctx) {
		this (ctx, null, 0);
	}
	
	/**
	 * 
	 */
	private void loadLayout() {
		
		LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate (org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		
		addView(view);
		
		
		mRadioSelector = (RadioSelector) view.findViewById (org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		mRadioSelector.setOnKeyListener(this);
		mRadioSelector.requestFocus();
		
		mRadioSelector.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view, int position, long id) 
			{
				Log.d(TAG, "Selected Item "+position);
				setButton3focussed();
				
			}
			
		});	
			
		OnClickListener cancelButtonListener = new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				
				Log.d(TAG, "Cancel Button pressed");
				mNativeAPIWrapper.SetScanStops();
				mNativeAPIWrapper.resetInstallation();
				mSatelliteWizard.launchScreen(ScreenRequest.STARTSCREEN, getScreenName());
				
			}
		};
		
		OnClickListener nextButtonListener = new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				
				int selectedRegionIndex = mRadioSelector.getSelectedItemPosition();
				Log.d(TAG, "Region Selected Index - "+selectedRegionIndex);

				mNativeAPIWrapper.SetSelectedPackage(true);
				mNativeAPIWrapper.setRegionIndex(selectedRegionIndex);
				mSatelliteWizard.launchScreen(ScreenRequest.INSTALLSCREEN, getScreenName());
				
			}
		};
		
		OnClickListener prevButtonListener = new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				
				Log.d(TAG, "Previous Button pressed");
				mNativeAPIWrapper.SetScanStops();
				mNativeAPIWrapper.resetInstallation();
				mSatelliteWizard.launchScreen(ScreenRequest.STARTSCREEN, getScreenName());
				
			}
		};
		
		/**
		 * TODO: Get UI Strings specific to TRICOLOR
		 * 
		 */
		String nextButtonText = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String prevButtonText = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String cancelButtonText = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);
		
		setButton1(cancelButtonText, cancelButtonListener, VISIBLE);
		setButton2(prevButtonText, prevButtonListener, VISIBLE);
		setButton3(nextButtonText, nextButtonListener, VISIBLE);
		
		
		
	}



		/* (non-Javadoc)
	 * @see java.util.Observer#update(java.util.Observable, java.lang.Object)
	 */
	@Override
	public void update(Observable arg0, Object obj) {
		int actionID = ((NotificationInfoObject)obj).actionID;
		
		Log.d(TAG, "Got an Update event actionID - "+ actionID+ " Message - "+((NotificationInfoObject)obj).message);
		
		switch (actionID) {
		
		case EventIDs.REGION_SCAN_END:
			NotificationHandler.getInstance().unRegisterForNotification(this);
			final String regionNamesAll[] = mNativeAPIWrapper.getTricolorRegionNames();
			final String regionNameGeneral[] = {mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_REGION_GENERAL)};
			final String regionNames[];
			
			if(regionNamesAll != null)
			{
				 regionNames = new String[regionNamesAll.length + regionNameGeneral.length];
				 System.arraycopy(regionNameGeneral, 0, regionNames, 0, regionNameGeneral.length);
  				 System.arraycopy(regionNamesAll, 0, regionNames, regionNameGeneral.length, regionNamesAll.length);
			}
			else
			{
				regionNames = new String[regionNameGeneral.length];
				System.arraycopy(regionNameGeneral, 0, regionNames, 0, regionNameGeneral.length);
			}

			
			
			((Activity)mContext).runOnUiThread( new Runnable() {
				
				@Override
				public void run() {
					enableWaitingAnimation(false);
					/**
					 * TODO:: update with the actual String constant
					 * 
					 */
					setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_REGION_SELECTION));
					mRadioSelector.setArray(regionNames);
					mRadioSelector.setChoiceMode(RadioSelector.CHOICE_MODE_SINGLE);
					mRadioSelector.setVisibility(VISIBLE);
					setButton3Enabled(true);
					mRadioSelector.requestFocus();
					
				}
			});
			
			break;
			
		}

	}

	/* (non-Javadoc)
	 * @see org.droidtv.euinstallersat.wizard.util.SatelliteScreen#setInstance(org.droidtv.euinstallersat.wizard.SatelliteWizard)
	 */
	@Override
	public void setInstance(SatelliteWizard wizard) {
		this.mSatelliteWizard = wizard;

	}

	/* (non-Javadoc)
	 * @see org.droidtv.euinstallersat.wizard.util.SatelliteScreen#getScreenName()
	 */
	@Override
	public ScreenRequest getScreenName() {
		
		return ScreenRequest.TRICOLOR_REGION_SELECTION;
	}

	/* (non-Javadoc)
	 * @see org.droidtv.euinstallersat.wizard.util.SatelliteScreen#screenIntialization()
	 */
	@Override
	public void screenIntialization() {
		
		Log.d(TAG, "screenInitialization(): Registering listeners");
		
		NotificationHandler.getInstance().registerForNotification(mSatelliteScreen);
		mRadioSelector.setVisibility(INVISIBLE);
		mNativeAPIWrapper.startTricolorRegionParsing ();
		enableWaitingAnimation(true);

	}

	/* (non-Javadoc)
	 * @see org.droidtv.euinstallersat.wizard.util.SatelliteScreen#screenExit()
	 */
	@Override
	public void screenExit() {
		Log.d(TAG, "screenExit(): Unregistering the event");
		NotificationHandler.getInstance().unRegisterForNotification(mSatelliteScreen);
	}

}
