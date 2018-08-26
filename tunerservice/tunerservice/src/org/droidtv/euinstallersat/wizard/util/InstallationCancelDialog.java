package org.droidtv.euinstallersat.wizard.util;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;

import android.content.Context;
import android.util.Log;

public class InstallationCancelDialog
{

	private static final String TAG = InstallationCancelDialog.class.getName();
	private ScreenRequest m_currentScreen = null;
	private ScreenRequest m_nextScreen = null;
	private SatelliteWizard m_wizard;
	private Context m_context;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	
	public InstallationCancelDialog(Context p_context, SatelliteWizard p_wizard)
	{
		Log.d(TAG,"InstallationCancelDialog");
		m_wizard = p_wizard;
		m_context = p_context;
		
		mBuilder = new ModalDialog.Builder(m_context,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_TI_SAT_AUTOSTORE_STOP), "");
    	mBuilder.setMessage(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_DI_SAT_AUTOSTORE_STOP));
    	
    	ModalDialogFooterButtonProp mNoButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NO),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_NO clicked ");
    					mModalDialog.hide();
    				}
    			});
    	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_YES),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_YES clicked ");
    					
    					if((m_wizard != null) && (m_currentScreen!=null)){
    						m_wizard.launchScreen(m_nextScreen, m_currentScreen);
    					}else{
    						if(m_wizard == null){
    							// still in waiting animation
    							Log.d(TAG, "Still in waiting animation");
    							((SatelliteInstallationActivity) m_context).exitInstallationWizard();
    						}else if (!m_wizard.launchFirstScreen()){
    							Log.d(TAG, "On first screen of wizard, closing activity");
    							((SatelliteInstallationActivity) m_context).exitInstallationWizard();
    						}
    					}
    					NativeAPIWrapper.getInstance().cancelInstallation();
    					mModalDialog.hide();
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setCancelable(false);	
    	mNoButton.requestFocus();
		
	}
	
	/*indicates which screen to move to if user selects yes
	 * Moves to first screen of wizard if not set*/
	public void setNextScreen(ScreenRequest p_currentScreen, ScreenRequest p_nextScreen)
	{
		m_currentScreen = p_currentScreen;
		m_nextScreen = p_nextScreen;
	}

	public void showDialog() {
		Log.d(TAG, "displayCancelDialog");
		mModalDialog.show();
	}

}
