package org.droidtv.euinstallertc.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.common.InstallerActivityManager.EXIT_INSTALLER_REASON;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
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

public class FinishScreen extends WizardStep implements IInstallationScreen
{

	private final String TAG = FinishScreen.class.getName();
	private Context ctx;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private View finishPageView;
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();
	private InstallationWizard      mInstallationWizard;
	
	public FinishScreen(Context context)
	{
		super(context, null, 0);
	}

	public FinishScreen(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);
	}

	public FinishScreen(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		loadLayout(context, attrs, defStyle);
	}

	private void loadLayout(Context context, AttributeSet attrs, int defStyle)
	{
		ctx = context;

		final LayoutInflater inflater = (LayoutInflater) context
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		finishPageView = inflater.inflate(R.layout.finishpage, null);
		addView(finishPageView);

		OnClickListener finishButton_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				// un-registering this class for notifications
				(NotificationHandler.getInstance()).unregisterForNotification(FinishScreen.this);
				if(nwrap.ifCountrySupportsHBBTV()){
					instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
					//mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.HBBTV_PRIVACY_STATEMENT, getScreenName());
				}else{
					// installation done
					instActManager.exitInstallation(EXIT_INSTALLER_REASON.INSTALLTION_COMPLETE);
				}
			}
		};

		setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE),
				finishButton_Listener, View.VISIBLE);
		setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), null,
				View.INVISIBLE);
		setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_START), null,
				View.INVISIBLE);

		hideHint();
		setButton1focussed();
	}

	@Override
	public void setInstance(InstallationWizard wizard) {
		  mInstallationWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName() {
		return InstallationWizard.ScreenRequest.FINISH_SCREEN;
	}

	@Override
	public void update(Observable observable, Object data) {

	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		boolean ret = super.dispatchKeyEvent(event);
		int keyCode = event.getKeyCode();
		switch (keyCode) {
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
		Log.d(TAG,"screenIntialization " );
		TextView line1String = (TextView)finishPageView.findViewById(R.id.line1String);
		TextView line1Value = (TextView)finishPageView.findViewById(R.id.line1Value);
		TextView line2String = (TextView)finishPageView.findViewById(R.id.line2String);
		TextView line2Value = (TextView)finishPageView.findViewById(R.id.line2Value);
		TextView line3String = (TextView)finishPageView.findViewById(R.id.line3String);
		TextView line3Value = (TextView)finishPageView.findViewById(R.id.line3Value);
		TextView line4String = (TextView)finishPageView.findViewById(R.id.line4String);
		TextView line4Value = (TextView)finishPageView.findViewById(R.id.line4Value);

		if(nwrap.getCachedAnalogueDigital() == NativeAPIEnums.AnalogueOrDigital.ANALOGUE){
			// DVB is not supported i.e analog
			line1String.setVisibility(View.VISIBLE);
			line1String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_CHANNELS_STORED));
			line1Value.setVisibility(View.VISIBLE);
			line1Value.setText(Integer.toString(nwrap.getCachedAnalogueChannelCount()));
		}else{
			// DVB is supported Digital, Analog + Digital

			if(nwrap.countrySupportsDVBTFullorLite(nwrap.getCachedCountryName()) == NativeAPIEnums.DVBTOrDVBCMacro.DVBT_Light){
				// DVB-T light installation is supported.

				// The digital channels stored.
				line1String.setVisibility(View.VISIBLE);
				line1String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_DIGITAL_CHANNELS_STORED));
				line1Value.setVisibility(View.VISIBLE);
				line1Value.setText(Integer.toString(nwrap.getCachedDigitalChannelCount()));

				// The analogue channels stored.
				line2String.setVisibility(View.VISIBLE);
				line2String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_ANALOGUE_CHANNELS_STORED));
				line2Value.setVisibility(View.VISIBLE);
				line2Value.setText(Integer.toString(nwrap.getCachedAnalogueChannelCount()));

				// The first digital channel.
				if(nwrap.getCachedDigitalChannelCount() > 0){
					line3String.setVisibility(View.VISIBLE);
					line3String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_FIRST_DIGITAL_CHANNEL));
					line3Value.setVisibility(View.VISIBLE);
					line3Value.setText(Integer.toString(nwrap.getFirstChannel(NativeAPIEnums.ChannelType.DIGITAL)));
				}

			}else{
				// DVB-T light installation is not supported i.e DVB-T Full installation

				// The digital channels stored.
				line1String.setVisibility(View.VISIBLE);
				line1String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_DIGITAL_CHANNELS_STORED));
				line1Value.setVisibility(View.VISIBLE);
				line1Value.setText(Integer.toString(nwrap.getCachedDigitalChannelCount()));

				// The analogue channels stored.
				line2String.setVisibility(View.VISIBLE);
				line2String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_ANALOGUE_CHANNELS_STORED));
				line2Value.setVisibility(View.VISIBLE);
				line2Value.setText(Integer.toString(nwrap.getCachedAnalogueChannelCount()));

				// The first analogue channel.
				if(nwrap.getCachedAnalogueChannelCount() > 0){
					line3String.setVisibility(View.VISIBLE);
					line3String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_FIRST_ANALOGUE_CHANNEL));
					line3Value.setVisibility(View.VISIBLE);
					line3Value.setText(Integer.toString(nwrap.getFirstChannel(NativeAPIEnums.ChannelType.ANALOG)));
				}
				
				if(nwrap.getFirstChannel(NativeAPIEnums.ChannelType.RADIO) >= 1000){
					// The first radio channel.
					line4String.setVisibility(View.VISIBLE);
					line4String.setText(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_WI_FIRST_RADIO_CHANNEL));
					line4Value.setVisibility(View.VISIBLE);
					line4Value.setText(Integer.toString(nwrap.getFirstChannel(NativeAPIEnums.ChannelType.RADIO)));
				}
			}
		}

		setButton1focussed();
	}
}
