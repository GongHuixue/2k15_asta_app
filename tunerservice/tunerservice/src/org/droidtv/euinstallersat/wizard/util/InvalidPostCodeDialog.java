package org.droidtv.euinstallersat.wizard.util;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;

import android.content.Context;
import android.util.Log;

public class InvalidPostCodeDialog 
{

	private static final String TAG = InvalidPostCodeDialog.class.getName();
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	private ScreenRequest m_currentScreen = null;
	private ScreenRequest m_nextScreen = null;
	private SatelliteWizard m_wizard;
	private NativeAPIWrapper m_wrapper;
	
	public InvalidPostCodeDialog(Context p_context, SatelliteWizard p_wizard)
	{
		Log.d(TAG,"InvalidPostCodeDialog");
		m_wrapper = NativeAPIWrapper.getInstance();
		
		mBuilder = new ModalDialog.Builder(p_context,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(p_context.getString(org.droidtv.ui.strings.R.string.MAIN_TI_SAT_WRONG_POSTCODE), "");
    	mBuilder.setMessage(p_context.getString(org.droidtv.ui.strings.R.string.MAIN_DI_SAT_WRONG_POSTCODE));
    	
    	mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			p_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_TRY_AGAIN),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_TRY_AGAIN clicked");
    					mModalDialog.hide();
    				}
    			});
    	ModalDialogFooterButtonProp mTryAgainButton = mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			p_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DEFAULT_POSTCODE),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_DEFAULT_POSTCODE clicked ");
    					
    					Log.d(TAG, "Move to Installation Screen:Default button pressed:Default RegionId and Bouquet Id set");
    					
    					m_wrapper.setPostCode("");
    					
						if (m_currentScreen != null) {
							m_wrapper.SetSelectedPackage(true);
							m_wizard.launchScreen(m_nextScreen, m_currentScreen);
						} else {
							Log.d(TAG, "Error: CurrentScreen == Null , should not land here");
						}
    					
    					mModalDialog.hide();
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setCancelable(false);
    	
    	mTryAgainButton.requestFocus();
    	mModalDialog.hide();
		
		m_wizard = p_wizard;
	}
	
	/*indicates which screen to move to if user selects yes
	 * Moves to first screen of wizard if not set*/
	public void setNextScreen(ScreenRequest p_currentScreen, ScreenRequest p_nextScreen)
	{
		m_currentScreen = p_currentScreen;
		m_nextScreen = p_nextScreen;
	}

	public void showDialog()
	{
		Log.d(TAG, "displayInvalidPostCodeDialog");
		mModalDialog.show();
	}


}
