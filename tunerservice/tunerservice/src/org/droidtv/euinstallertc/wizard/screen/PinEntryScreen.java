package org.droidtv.euinstallertc.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.util.PasswordTransformation;
import org.droidtv.euinstallertc.wizard.IInstallationScreen;
import org.droidtv.euinstallertc.wizard.InstallationWizard;
import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;

import android.content.Context;
import android.text.Editable;
import android.text.InputType;
import android.text.TextWatcher;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;

public class PinEntryScreen extends WizardStep implements IInstallationScreen {

    private static final String TAG = PinEntryScreen.class.getName();
    private Context ctx;
    private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
    private View pinEntryView;
    private InstallationWizard mInstallationWizard;
    private EditText mEditPinAgain;
    private EditText mEditPin;
    private int MAX_LENGTH = 4;
    private String pinEntryString;
    private String pinEntryAgainString;
    private boolean pinEntrySuccess;
	private TvToast mTimeOutTvToast;
	private TvToastMessenger messenger;

    public PinEntryScreen(Context context) {
        super(context, null, 0);
    }

    public PinEntryScreen(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public PinEntryScreen(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        loadLayout(context, attrs, defStyle);
    }

    private void loadLayout(Context context, AttributeSet attrs, int defStyle) {
        ctx = context;

        final LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        pinEntryView = inflater.inflate(R.layout.pinentry_layout, null);
        addView(pinEntryView);

        mEditPin = (EditText) pinEntryView.findViewById(R.id.input_pin);
        mEditPinAgain = (EditText) pinEntryView.findViewById(R.id.input_pin_again);

        // stop oskb from popping up
        mEditPin.setRawInputType(InputType.TYPE_NULL);
        mEditPinAgain.setRawInputType(InputType.TYPE_NULL);

        // to hide the charters and show passchar instantly
        mEditPin.setTransformationMethod(new PasswordTransformation());
        mEditPinAgain.setTransformationMethod(new PasswordTransformation());

        //mEditPin.setOnKeyListener(this);
        mEditPin.addTextChangedListener(new TextWatcher() {

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                Log.d("logs", "onTextChanged for first");
                pinEntryString = mEditPin.getText().toString();
                if (pinEntryString.equals("0000")) {
                    //TvNotificationManager.postTvNotification(ctx, org.droidtv.ui.tvwidget2k14.R.drawable.warning_d_ico_16x12_118, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_PINCODE_0000_INVALID), TvNotificationManager.FLAG_TIMED_NOTIFICATION);
                	
                	messenger = TvToastMessenger.getInstance(ctx);
        			mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", org.droidtv.ui.tvwidget2k15.R.drawable.icon_punched_push_m_alert_n_36x36);
        			mTimeOutTvToast.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_PINCODE_0000_INVALID));
        			messenger.showTvToastMessage(mTimeOutTvToast);
        			
                    mEditPin.setText("");
                }
            }

            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                mEditPinAgain.setEnabled(false);
            }

            @Override
            public void afterTextChanged(Editable s) {
                if (pinEntryString.length() == MAX_LENGTH) {
                    Log.d("set pinEntryString ", pinEntryString);
                    mEditPinAgain.setEnabled(true);
                    mEditPinAgain.setFocusable(true);
                    mEditPinAgain.setFocusableInTouchMode(true);
                    mEditPinAgain.requestFocus();
                }
            }
        });

        //mEditPinAgain.setOnKeyListener(this);
        mEditPinAgain.addTextChangedListener(new TextWatcher() {

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                // TODO Auto-generated method stub
                pinEntryAgainString = mEditPinAgain.getText().toString();
                if (pinEntryAgainString.length() == MAX_LENGTH) {
                    if (pinEntryAgainString.equals("0000")) {
                       //TvNotificationManager.postTvNotification(ctx, org.droidtv.ui.tvwidget2k14.R.drawable.warning_d_ico_16x12_118, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_PINCODE_0000_INVALID), TvNotificationManager.FLAG_TIMED_NOTIFICATION);
                    	
                    	// display tvtoast
            			messenger = TvToastMessenger.getInstance(ctx);
            			mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", org.droidtv.ui.tvwidget2k15.R.drawable.icon_punched_push_m_alert_n_36x36);
            			mTimeOutTvToast.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_PINCODE_0000_INVALID));
            			messenger.showTvToastMessage(mTimeOutTvToast);
            			                    	
                        mEditPin.setText("");
                    } else {
                        validatePin();
                    }
                }
            }

            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                // TODO Auto-generated method stub

            }

            @Override
            public void afterTextChanged(Editable s) {
                // TODO Auto-generated method stub

            }
        });
        mEditPin.requestFocus();
        setButton3Enabled(false);

        setButton1(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), null, View.INVISIBLE);
        setButton2(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener, View.VISIBLE);
        setButton3(context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT), buttonNext_Listener, View.VISIBLE);
        setHintText(context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_PINCODE));

    }
    
    public boolean ifPinentrySuccess(){
        return pinEntrySuccess;
    }

    private void validatePin() {
        Log.d(TAG, "validatePin()");
        pinEntryString = mEditPin.getText().toString();
        pinEntryAgainString = mEditPinAgain.getText().toString();
        if (pinEntryString.equals(pinEntryAgainString)) {
            Log.d(TAG, "validatePin() validated same");
            setButton3Enabled(true);
            setButton3focussed();
            pinEntrySuccess = true;
        } else {
            //TvNotificationManager.postTvNotification(ctx, org.droidtv.ui.tvwidget2k14.R.drawable.warning_d_ico_16x12_118, ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_PINCODE_NOT_MATCHING), TvNotificationManager.FLAG_TIMED_NOTIFICATION);
        	messenger = TvToastMessenger.getInstance(ctx);
			mTimeOutTvToast = TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", org.droidtv.ui.tvwidget2k15.R.drawable.icon_punched_push_m_alert_n_36x36);
			mTimeOutTvToast.setMessage(ctx.getString(org.droidtv.ui.strings.R.string.MAIN_MSG_PINCODE_NOT_MATCHING));
			messenger.showTvToastMessage(mTimeOutTvToast);
			
            mEditPin.setText("");
            mEditPinAgain.setText("");
            mEditPin.requestFocus();
            mEditPinAgain.setFocusable(false);
            mEditPinAgain.setFocusableInTouchMode(false);
        }
    }

    // OnClick Listener for PREVIOUS button
    private OnClickListener buttonPrevious_Listener = new OnClickListener() {
        @Override
        public void onClick(View v) {
            Log.d(TAG, "previous clicked");
            mInstallationWizard.launchPreviousScreen();
        }
    };

    // OnClick Listener for NEXT button
    private OnClickListener buttonNext_Listener = new OnClickListener() {
        @Override
        public void onClick(View v) {

            /*
             * Requirement: Timezone country and Virgin installation: <Screen:
             * Timezone> Not Timezone country or not Virgin installation: DVB-C
             * installation is supported: <Screen: Antenna/Cable> DVB-C
             * installation is not supported: Search subwizard, first applicable
             */
            Log.d(TAG, "next clicked");
            int setPinentry = -1;
            try {
                setPinentry = Integer.parseInt(pinEntryString);
                nwrap.setPinEntryInTVS(setPinentry);
            } catch (Exception ex) {
                Log.d(TAG, "Caught exception while setting pin " + setPinentry);
            }

            if (nwrap.ifTimezoneCountry(nwrap.getCachedCountryName())) {
                if (nwrap.ifVirginInstallation()) {
                    if (nwrap.ifDVBCSupportedCountry(nwrap.getCachedCountryName())) {
                        mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.ANTENNA_SCREEN, getScreenName());
                    } else {
                        mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
                    }
                } else {
                    mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.TIMEZONE_SCREEN, getScreenName());
                }
            } else {
            	if (PlayTvUtils.isPbsMode()) {
                	nwrap.setCachedAnalogueDigital(NativeAPIEnums.AnalogueOrDigital.DIGITAL_AND_ANALOGUE);
                	mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
            	} else {
                	if (nwrap.ifDVBCSupportedCountry(nwrap.getCachedCountryName())) {
                	    mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.ANTENNA_SCREEN, getScreenName());
                	} else {
                	    mInstallationWizard.launchScreen(InstallationWizard.ScreenRequest.SEARCH_SCREEN, getScreenName());
                	}
				}
            }
        }
    };

    @Override
    public void update(Observable arg0, Object arg1) {
        // TODO Auto-generated method stub
    }

    @Override
    public void setInstance(InstallationWizard wizard) {
        mInstallationWizard = wizard;
    }

    @Override
    public ScreenRequest getScreenName() {
        return InstallationWizard.ScreenRequest.PINENTRY_SCREEN;
    }

    @Override
    public void screenIntialization() {
        mEditPin.setText("");
        mEditPinAgain.setEnabled(true);
        mEditPinAgain.setText("");
        mEditPinAgain.setEnabled(false);
        setButton3Enabled(false);
        pinEntrySuccess = false;
        mEditPin.requestFocus();
        mEditPinAgain.setFocusable(false);
        mEditPinAgain.setFocusableInTouchMode(false);
    }
}
