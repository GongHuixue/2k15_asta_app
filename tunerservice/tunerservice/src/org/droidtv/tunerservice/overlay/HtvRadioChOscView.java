package org.droidtv.tunerservice.overlay;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Typeface;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
//import android.util.DisplayMetrics;
import android.util.Log;
import android.util.TypedValue;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Date;

import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tunerservice.R;

import org.droidtv.tv.tvclock.ITvClockManager;

public class HtvRadioChOscView extends RelativeLayout {

    private static final String TAG = "HtvRadioChOscView";

    private Context mContext = null;
    private ITvSettingsManager mTvSettingsManager = null;
    private boolean isAmPmFormat = false;

    private TextView mTextViewDay = null;
    private TextView mTextViewTime = null;
    private TextView mTextViewDate = null;
    private TextView mTextViewTimeInvalid = null;

    public static BroadcastReceiver HtvRadioChOscReceiver = null;
    public static IntentFilter oscIntentFilter = null;

    public HtvRadioChOscView(Context context) {
        super(context);

        mContext = context;
        int clockFormat = ITvSettingsManager.Instance.getInterface().getInt(TvSettingsConstants.PBSMGR_PROPERTY_DNT_CLOCK_FORMAT, 0, 0);
        isAmPmFormat = clockFormat == TvSettingsDefinitions.PbsClockFormatConstants.PBSMGR_CLOCK_FORMAT_AMPM;
        Log.d(TAG, "isAmPmFormat == " + isAmPmFormat);

        initView();
        updateClock();
        initClockReceiver();
    }

    private void initView() {
        Log.d(TAG, "initView()");

        LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        inflater.inflate(R.layout.htv_radio_ch_osc_view, this);

        mTextViewDay = (TextView) findViewById(R.id.text_day);
        mTextViewTime = (TextView) findViewById(R.id.text_time);
        mTextViewDate = (TextView) findViewById(R.id.text_date);

        mTextViewTimeInvalid = (TextView) findViewById(R.id.text_time_invalid);

/* Adding a TextView this way doesn't work.
        mTextViewDay = new TextView(mContext);
        RelativeLayout.LayoutParams dayLp = new RelativeLayout.LayoutParams(dpToPx(255.5), dpToPx(40.5));
        dayLp.setMargins(dpToPx(352), dpToPx(170.5), dpToPx(607.5), dpToPx(211));
        mTextViewDay.setLayoutParams(dayLp);
        mTextViewDay.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM);
        mTextViewDay.setTypeface(Typeface.createFromFile("/system/fonts/Roboto-Light.ttf"));
        mTextViewDay.setTextColor(0xFFFFFF);
        mTextViewDay.setTextSize(TypedValue.COMPLEX_UNIT_SP, 35);
        oscLayout.addView(mTextViewDay);

        mTextViewTime = new TextView(mContext);
        RelativeLayout.LayoutParams timeLp = new RelativeLayout.LayoutParams(dpToPx(470), dpToPx(110));
        timeLp.setMargins(dpToPx(244.5), dpToPx(224), dpToPx(714.5), dpToPx(334));
        mTextViewTime.setLayoutParams(timeLp);
        mTextViewTime.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM);
        mTextViewTime.setTypeface(Typeface.createFromFile("/system/fonts/Roboto-Light.ttf"));
        mTextViewTime.setTextColor(0xFFFFFF);
        mTextViewTime.setTextSize(TypedValue.COMPLEX_UNIT_SP, 105);
        oscLayout.addView(mTextViewTime);

        mTextViewDate = new TextView(mContext);
        RelativeLayout.LayoutParams dateLp = new RelativeLayout.LayoutParams(dpToPx(255.5), dpToPx(40.5));
        dateLp.setMargins(dpToPx(352), dpToPx(335.5), dpToPx(607.5), dpToPx(376));
        mTextViewDate.setLayoutParams(dateLp);
        mTextViewDate.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM);
        mTextViewDate.setTypeface(Typeface.createFromFile("/system/fonts/Roboto-Light.ttf"));
        mTextViewDate.setTextColor(0xFFFFFF);
        mTextViewDate.setTextSize(TypedValue.COMPLEX_UNIT_SP, 35);
        oscLayout.addView(mTextViewDate);
*/
    }

/*
    private int dpToPx(double dp) {
        return (int) (dp * mContext.getResources().getDisplayMetrics().density);
    }
*/
    private String getAmPmString(Date date) {
        return getAmPmString(date, true); //default with space
    }

    private String getAmPmString(Date date, boolean withSpace) {
        // AM PM using stringID TF415PHIEUMTK66-2576
        String spaceStr = "";
        if (withSpace) {
            spaceStr = " ";
        }

        if(date.getHours() > 11){
           return spaceStr+mContext.getResources().getString(org.droidtv.ui.strings.R.string.HTV_MAIN_PM);
        }else{
           return spaceStr+mContext.getResources().getString(org.droidtv.ui.strings.R.string.HTV_MAIN_AM);
        }
    }

    public void updateClock() {
        Log.d(TAG, "updateClock()");

        if (ITvClockManager.eClockSources.INVALID == ITvClockManager.Instance.getInterface().GetCurrentClockSourceEnum()) {
            mTextViewDay.setText("");
            mTextViewTime.setVisibility(View.GONE);
            mTextViewTimeInvalid.setVisibility(View.VISIBLE);
            mTextViewTimeInvalid.setText("Clock not available");
            mTextViewDate.setText("");
            return;
        }

        Date date = new Date();
        SimpleDateFormat formatDay = new SimpleDateFormat("cccc");
        // AM PM using stringID TF415PHIEUMTK66-2576
        //SimpleDateFormat formatTime = isAmPmFormat ? new SimpleDateFormat("hh:mm a") : new SimpleDateFormat("HH:mm");
        SimpleDateFormat formatTime = isAmPmFormat ? new SimpleDateFormat("hh:mm") : new SimpleDateFormat("HH:mm");
        SimpleDateFormat formatDate = new SimpleDateFormat("MMM d, yyyy");

        mTextViewTime.setVisibility(View.VISIBLE);
        mTextViewTimeInvalid.setVisibility(View.GONE);
        mTextViewDay.setText(formatDay.format(date));
        if (isAmPmFormat) { // AM PM using stringID TF415PHIEUMTK66-2576
            mTextViewTime.setText(formatTime.format(date)+getAmPmString(date));
        } else {
            mTextViewTime.setText(formatTime.format(date));
        }
        mTextViewDate.setText(formatDate.format(date));

        Log.d(TAG, "Current Time is " + formatDate.format(date) + " " + formatTime.format(date));
    }

    private void initClockReceiver() {
        Log.d(TAG, "initClockReceiver()");

        HtvRadioChOscReceiver = new BroadcastReceiver() {

            @Override
            public void onReceive(Context context, Intent intent) {
                Log.d(TAG, "HtvRadioChOscReceiver - onReceive");

                String action = intent.getAction();
                Log.d(TAG, "action = " + action);
                switch (action) {
                    case Intent.ACTION_TIME_TICK:
                    case Intent.ACTION_TIME_CHANGED:
                    case Intent.ACTION_DATE_CHANGED:
                    case Intent.ACTION_TIMEZONE_CHANGED:
                        updateClock();
                        break;
                    default:
                        Log.w(TAG, "unknown intent action");
                        break;
                }
            }

        };

        oscIntentFilter = new IntentFilter();
        oscIntentFilter.addAction(Intent.ACTION_TIME_TICK);
        oscIntentFilter.addAction(Intent.ACTION_TIME_CHANGED);
        oscIntentFilter.addAction(Intent.ACTION_DATE_CHANGED);
        oscIntentFilter.addAction(Intent.ACTION_TIMEZONE_CHANGED);
    }

}