package org.droidtv.euinstallertc.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

/*
 * This class allows the user to update the channels list.
 * If user clicks on "start" button the user will navigated to UpdatingWizard screen
 */
public class StartUpdateScreen extends WizardStep implements
		IInstallationScreen {

	private static final String TAG = StartUpdateScreen.class.getName();
	private InstallationWizard mInstallationWizard;
	private Context mContext;
	private View updateStartScreen;
    private TextView informationLine;

	public StartUpdateScreen(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		loadLayout(context, attrs, defStyle);
	}

	public StartUpdateScreen(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public StartUpdateScreen(Context context) {
		this(context, null, 0);
	}

	private OnClickListener buttonStart_Listener = new OnClickListener() {
        @Override
        public void onClick(View v) {
            Log.d(TAG, "You clicked on Start button:" + mInstallationWizard);
            mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.UPDATING_SCREEN, getScreenName());
        }
    };
    
    private OnClickListener buttonPrevious_Listener = new OnClickListener() {
        
        @Override
        public void onClick(View v) {
            mInstallationWizard.launchPreviousScreen();
        }
    }; 
    
    
	private void loadLayout(Context context, AttributeSet attrs, int defStyle) {

	    mContext = context;
		
		final LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		updateStartScreen = inflater.inflate(R.layout.information_layout, null);
        addView(updateStartScreen);
        
        informationLine = (TextView) updateStartScreen.findViewById(R.id.line1String);
        informationLine.setText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_UPDATE_START));
		hideHint();

        setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), null, View.INVISIBLE);
        setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener, View.VISIBLE);
        setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_START), buttonStart_Listener, View.VISIBLE);

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
		Log.v(TAG, "IInstallationWizard:" + wizard);
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
		return InstallationWizard.ScreenRequest.STARTUPDATE_SCREEN;
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

	@Override
	public void screenIntialization() {
		
		setButton3focussed();
	}
}
