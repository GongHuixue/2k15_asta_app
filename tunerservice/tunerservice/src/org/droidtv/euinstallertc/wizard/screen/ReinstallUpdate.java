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

import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

/*
 * This class will display two radio buttons in the wizard step and it allows you autostore or update. 
 */
public class ReinstallUpdate extends WizardStep implements IInstallationScreen {

	private static final String TAG = ReinstallUpdate.class.getName();
	private Context mContext;
	private InstallationWizard mInstallationWizard;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private RadioSelector radioSelector;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;

	public ReinstallUpdate(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		Log.d(TAG, "WizardStatus() called");
		mContext = context;
		loadLayout(context, attrs, defStyle);
	}

	public ReinstallUpdate(Context context, AttributeSet attrs) {
		this(context, null, 0);
	}

	public ReinstallUpdate(Context context) {
		this(context, null, 0);
	}

	/*
	 * This method is responsible for setting the view to wizard step and it
	 * will change button names,make it visible or invisible. setting hint text
	 * and handling the start and cancel buttons navigation. Clicking on
	 * "Cancel" button It will navigate to home screen. Based on the radio items
	 * selection it will navigate to startupdate screen or country screen.
	 * 
	 * @params context,attribute set,default style
	 */
	private void loadLayout(final Context context, AttributeSet attrs,
			int defStyle) {
		String[] wizardStatus = {
				context.getString(org.droidtv.ui.strings.R.string.MAIN_FULL_INSTALLATION),
				context.getString(org.droidtv.ui.strings.R.string.MAIN_UPDATE_DIGITAL_CHANNELS) };
		LayoutInflater inflater = (LayoutInflater) context
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View v = inflater.inflate(
				org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout, null);
		Log.d(TAG, "Resource ID: " + org.droidtv.ui.tvwidget2k15.R.layout.radio_selector_layout);
		Log.d(TAG, "View v " + v);
		addView(v);

		radioSelector = (RadioSelector) v
				.findViewById(org.droidtv.ui.tvwidget2k15.R.id.radioSelector1);
		radioSelector.setArray(wizardStatus);
		
		radioSelector.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View selectedView,
					int selectedItem, long arg3) {
			    Log.d(TAG, "selected Item:" + selectedItem);
				setButton3focussed();
			}
		});

		// OnClick Listener for NEXT button
		OnClickListener buttonNext_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				Log.i(TAG, "text:"+radioSelector.getItemAtPosition(radioSelector.getCheckedItemPosition()));
				String mStatusCheck = (String) (radioSelector.getItemAtPosition(radioSelector.getCheckedItemPosition()))
						.toString();
				if (mStatusCheck.equals(mContext
						.getString(org.droidtv.ui.strings.R.string.MAIN_UPDATE_DIGITAL_CHANNELS))) {
					mInstallationWizard
							.launchScreen(
									InstallationWizard.ScreenRequest.STARTUPDATE_SCREEN,
									getScreenName());
				} else {
					mInstallationWizard.launchScreen(
							InstallationWizard.ScreenRequest.COUNTRY_SCREEN,
							getScreenName());
				}
			}
		};
		
		//OnClickListener for cancel button
		OnClickListener buttonCancel_Listener = new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
                mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_AUTOSTORE_STOP), "");
            	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_AUTOSTORE_STOP));
            	
            	ModalDialogFooterButtonProp mNoButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
            			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NO),
            			true,
            			new ModalDialogInterface.OnClickListener(){
            				@Override
            				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
            					Log.d(TAG, "Stop cancelled Resume");
            					mModalDialog.hide();
            				}
            			});
            	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
            			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_YES),
            			true,
            			new ModalDialogInterface.OnClickListener(){
            				@Override
            				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
            					 Log.d(TAG, "Stop installation");
            					(NotificationHandler.getInstance()).removeAllObservers();
            					mModalDialog.hide();
         						nwrap.stopInstallation(true);
            				}
            			});
            	mModalDialog = mBuilder.build();
            	mModalDialog.setCancelable(false);
            	mModalDialog.show();
            	mNoButton.requestFocus();
            	
			}
		};
		
		// OnClick Listener for PREVIOUS button
		OnClickListener buttonPrevious_Listener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				mInstallationWizard.launchPreviousScreen();
			}
		};

		setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), buttonCancel_Listener,
				View.VISIBLE);
		setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener,
				View.VISIBLE);
		setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT), buttonNext_Listener,
				View.VISIBLE);

		setHintText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_AUTOSTORE_OR_UPDATE));

	}

	/*
	 * @see
	 * org.droidtv.broadcasttv.InstallationScreen#setIntance(org.droidtv.broadcasttv
	 * .InstallationWizard) Getting the InstallationWizard instance and keeping
	 * it for screen navigation.
	 * 
	 * @params InstallationWizard wizard
	 * 
	 * @return
	 */
	@Override
	public void setInstance(InstallationWizard wizard) {
		mInstallationWizard = wizard;
	}

	/*
	 * @see org.droidtv.broadcasttv.InstallationScreen#getScreenName() setting
	 * the currenct screen name for backward screen navigation.
	 * 
	 * @Param
	 * 
	 * @Return ScreenRequest
	 */
	@Override
	public ScreenRequest getScreenName() {
		return InstallationWizard.ScreenRequest.REINSTALL_SCREEN;
	}

	/*
	 * @see java.util.Observer#update(java.util.Observable, java.lang.Object)
	 * Call back method from InstallationScreen
	 * 
	 * @params observable,data
	 * 
	 * @return
	 */
	@Override
	public void update(Observable observable, Object data) {

	}
	
	private void setfocusOnTheRadioList(){
		if (nwrap.ifUpdateInstallationSupported()) {
			// initially selected if controllable
			radioSelector.setItemChecked(1, true);
			radioSelector.setSelection(1);
		} else {
			// default focus on Autostore
			radioSelector.setItemChecked(0, true);
			radioSelector.setSelection(0);
			// downhighlight update
		}
		
		radioSelector.requestFocusFromTouch();
		radioSelector.requestFocus();	
	}

	@Override
	public void screenIntialization() {
		/*
		 * 	Autostore (Re-install all channels)
			Update (Update digital channels) (*) (**)
			(*) Controllable:
			DVB-T installation is supported: Always.
			DVB-C installation is supported: Channel list is not empty or the installation parameters (see
			functional part) are known.
			(**) Initially selected if controllable; else: Autostore.
		 * */

		setfocusOnTheRadioList();

	}

}
