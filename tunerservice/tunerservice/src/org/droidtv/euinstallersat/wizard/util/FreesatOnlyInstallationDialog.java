package org.droidtv.euinstallersat.wizard.util;

import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;

import android.content.Context;
import android.util.Log;

public class FreesatOnlyInstallationDialog 
{
	private static final String TAG = FreesatOnlyInstallationDialog.class.getName();
	private ScreenRequest m_currentScreen = null;
	private ScreenRequest m_nextScreen = null;
	private SatelliteWizard m_wizard;
	private Context mContext;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	
	public FreesatOnlyInstallationDialog(Context p_context, SatelliteWizard p_wizard)
	{
		m_wizard = p_wizard;
		mContext = p_context;
		
		Log.d(TAG,"FreesatOnlyInstallationDialog");
		mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_SAT_FREESAT), "");
    	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_SAT_FREESAT));
    	
    	mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_CANCEL clicked ");
    					mModalDialog.hide();
    				}
    			});
    	ModalDialogFooterButtonProp mOkButton = mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_OK),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_OK clicked ");
    					Log.d(TAG, "Move to Freesat PostCode Entry Screen:Ok button pressed");
    					if(m_currentScreen!=null){
    						m_wizard.launchScreen(m_nextScreen, m_currentScreen);
    					}else{
    						Log.d(TAG, "Error: CurrentScreen == Null , should not land here");
    					}
    					mModalDialog.hide();
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setCancelable(false);
    	mOkButton.requestFocus();		
	}
	
	/*indicates which screen to move to if user selects yes
	 * Moves to first screen of wizard if not set*/
	public void setNextScreen(ScreenRequest p_currentScreen, ScreenRequest p_nextScreen)
	{
		m_currentScreen = p_currentScreen;
		m_nextScreen = p_nextScreen;
	}

	public void showDialog() {
		Log.d(TAG, "displayFreesatOnlyInstallationDialog");
		mModalDialog.show();
	}

}
