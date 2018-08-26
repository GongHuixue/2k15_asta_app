package org.droidtv.euinstallertc.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

/*
 * This class will displays the total nof digital channels added and removed.
 * If the user clicks on "stop" button the search will stop and displays a dialog.
 * Based on user selection on the dialog corresponding action will done
 */
public class UpdateComplete extends WizardStep implements IInstallationScreen
{

	private static final String TAG = UpdateComplete.class.getName();
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private View updateCompletePageView;
	private Context ctx;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	
	public UpdateComplete(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		loadLayout(context, attrs, defStyle);
	}

	public UpdateComplete(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);
	}

	public UpdateComplete(Context context)
	{
		this(context, null, 0);
	}

	/*
	 * This method is responsible for setting the view to wizard step and it
	 * will change button names,make it visible or invisible. setting hint text
	 * and handling the start button navigation. If the user click on finish
	 * button.The application will close and navigate to home screen.
	 * 
	 * @params context,attribute set,default style
	 */
	private void loadLayout(Context context, AttributeSet attrs, int defStyle) {
		
		ctx = context;
		LayoutInflater inflater = (LayoutInflater) context
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		
		updateCompletePageView = inflater.inflate(R.layout.updatecomplete, null);
		addView(updateCompletePageView);

		OnClickListener buttonFinish_Listener = new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// un-registering this class for notifications
				instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
			}
		}; 
		
		setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE), buttonFinish_Listener,
				View.VISIBLE);
		setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), null,
				View.INVISIBLE);
		setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_START), null,
				View.INVISIBLE);

		setButton1focussed();
		hideHint();
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
	public void setInstance(InstallationWizard wizard)
	{
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
	public ScreenRequest getScreenName()
	{
		return InstallationWizard.ScreenRequest.UPDATEFINISHED_SCREEN;
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
	public void update(Observable observable, Object data)
	{

	}

	/*
	 * @see android.view.ViewGroup#dispatchKeyEvent(android.view.KeyEvent)
	 * Handling left and right keys in the keyboard Disable the left and right
	 * key.
	 * 
	 * @param KeyEvent event
	 * 
	 * @return boolean
	 */
	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		boolean ret = super.dispatchKeyEvent(event);
		int keyCode = event.getKeyCode();
		switch (keyCode)
		{
			case KeyEvent.KEYCODE_DPAD_RIGHT:
				ret = true;
				break;
			case KeyEvent.KEYCODE_DPAD_LEFT:
				ret = true;
				break;
		}
		Log.v(TAG, "dispatch key event:" + ret);
		return ret;
	}

	@Override
	public void screenIntialization() {
		
		TextView line1String = (TextView)updateCompletePageView.findViewById(R.id.line1String);
		TextView line1Value = (TextView)updateCompletePageView.findViewById(R.id.line1Value);
		TextView line2String = (TextView)updateCompletePageView.findViewById(R.id.line2String);
		TextView line2Value = (TextView)updateCompletePageView.findViewById(R.id.line2Value);
		
		// The amount of digital channels added.
		line1String.setVisibility(View.VISIBLE);
		line1String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_DIGITAL_CHANNELS_ADDED));
		line1Value.setVisibility(View.VISIBLE);
		line1Value.setText(Integer.toString(nwrap.getCachedDigitalChannelCount()));
		
		// The amount of digital channels removed.
		line2String.setVisibility(View.VISIBLE);
		line2String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_DIGITAL_CHANNELS_REMOVED));
		line2Value.setVisibility(View.VISIBLE);
		line2Value.setText(Integer.toString(nwrap.getCachedDigitalChannelRemoved()));
		
		setButton1focussed();
	}
}
