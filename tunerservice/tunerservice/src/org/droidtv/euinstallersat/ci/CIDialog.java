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


package org.droidtv.euinstallersat.ci;



import org.droidtv.tunerservice.R;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class CIDialog extends RelativeLayout implements OnClickListener {
	private Dialog mMessageDialog;
	private ViewGroup mVg;
	private Button mButton1, mButton2, mButton3, mButton4;
	private TextView mTitleText;
	private TextView mSunTitleText;
	private TextView mBottomText;
	private String TAG = CIDialog.class.getName();
	private MessageDialogListener mMessageDialogListener;
	private Context mContext;

	public CIDialog(Context context) {
		super(context);
		mContext = context;
		loadLayout(context);
	}

	private void loadLayout(Context context) {
		final LayoutInflater inflater = (LayoutInflater) context
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View v = inflater.inflate(R.layout.common, this);
		v.setBackgroundResource(org.droidtv.ui.tvwidget2k15.R.drawable.panels_standard_bg);
		mVg = (FrameLayout) v.findViewById(R.id.bodytext);
		mTitleText = (TextView) v.findViewById(R.id.titletext);
		mSunTitleText = (TextView) v.findViewById(R.id.subtitle);
		mBottomText = (TextView) v.findViewById(R.id.bottomText);
		mButton1 = (Button) v.findViewById(R.id.button1);
		mButton2 = (Button) v.findViewById(R.id.button2);
		mButton3 = (Button) v.findViewById(R.id.button3);
		mButton4 = (Button) v.findViewById(R.id.button4);
		mButton1.setOnClickListener(this);
		mButton2.setOnClickListener(this);
		mButton3.setOnClickListener(this);
		mButton4.setOnClickListener(this);
		mMessageDialog = new Dialog(context);
		mMessageDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
		mMessageDialog.getWindow().setBackgroundDrawableResource(android.R.color.transparent);
		mMessageDialog.setContentView(this);
		mMessageDialog.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
		mMessageDialog.getWindow().setLayout(
				getResources().getDimensionPixelSize(
						R.dimen.ci_messagedialog_width),
						getResources().getDimensionPixelSize(
								R.dimen.ci_messagedialog_height));
		mMessageDialog.setCanceledOnTouchOutside(false);
	}

	public void addView(View view) {

		View v = mVg.getChildAt(0);
		if (v != null){
			mVg.removeViewAt(0);
		}
			mVg.addView(view);
	}

	/**
	 * this is used to show the Message Dialog
	 */
	public void show() {

		Log.i(TAG, "show() called:" + mContext);
		if(!((Activity)mContext).isFinishing()){
		mMessageDialog.show();
		}
	}

	/**
	 * this is used to hide the Message Dialog
	 */
	public void hide() {
		Log.i(TAG, "hide() called");
		mMessageDialog.cancel();
	}

	/**
	 * this is used to hide the Message Dialog
	 */
	public void hide(Context actiivty) {
		Log.i(TAG, "hide() called");
		mMessageDialog.cancel();
	}

	public void setDialogPersistent() {
		mMessageDialog.setCancelable(false);
	}

	/*
	 * To Set the Title
	 * 
	 * @Params String title
	 */
	public void setTitleText(String text) {
		mTitleText.setText(text);
	}

	/*
	 * Set the title visibility
	 * 
	 * @Params int visibility
	 */
	public void setTitleVisibility(int visibility) {
		mTitleText.setVisibility(visibility);
	}

	/*
	 * To Set the Sub Title
	 * 
	 * @Params String sub title
	 */
	public void setSubtitleText(String subTitle) {
		mSunTitleText.setText(subTitle);
	}

	/*
	 * Set the sub title visibility
	 * 
	 * @Params int visibility
	 */
	public void setSubtitleVisibility(int visibility) {
		mSunTitleText.setVisibility(visibility);
	}

	public void setBottomText(String bottomeText) {
		mBottomText.setText(bottomeText);
	}

	public void setBottomTextVisibility(int visibility) {
		mBottomText.setVisibility(visibility);
	}

	public void setMessageDialogListener(
			MessageDialogListener messageDialogListener) {
		mMessageDialogListener = messageDialogListener;

	}

	public void setButton1Text(String text) {
		mButton1.setText(text);

	}

	public void setButton2Text(String text) {
		mButton2.setText(text);

	}

	public void setButton3Text(String text) {
		mButton3.setText(text);

	}
	
	/*public void setButton3Enabled(){
		mButton3.setEnabled(false);
		mButton3.setFocusable(false);
	}*/

	public void setButton4Text(String text) {
		mButton4.setText(text);
	}

	public void setButton1Visibility(int visibility) {
		if (visibility == View.VISIBLE) {
			mButton1.setVisibility(View.VISIBLE);
		} else {
			mButton1.setVisibility(View.INVISIBLE);
		}
	}

	public void setButton2Visibility(int visibility) {
		if (visibility == View.VISIBLE) {
			mButton2.setVisibility(View.VISIBLE);
		} else {
			mButton2.setVisibility(View.INVISIBLE);
		}
	}

	public void setButton3Visibility(int visibility) {
		if (visibility == View.VISIBLE) {
			mButton3.setVisibility(View.VISIBLE);
		} else {
			mButton3.setVisibility(View.INVISIBLE);
		}
	}

	public void setButton4Visibility(int visibility) {
		if (visibility == View.VISIBLE) {
			mButton4.setVisibility(View.VISIBLE);
		} else {
			mButton4.setVisibility(View.INVISIBLE);
		}
	}

	// Set focus to Button1
	public void setButton1focussed() {
		mButton1.setFocusableInTouchMode(true);
		mButton1.requestFocus();
	}

	// Set focus to Button2
	public void setButton2focussed() {
		mButton2.setFocusableInTouchMode(true);
		mButton2.requestFocus();
	}

	// Set focus to Button3
	public void setButton3focussed() {
		mButton3.setFocusableInTouchMode(true);
		mButton3.requestFocus();
	}

	// Set focus to Button4
	public void setButton4focussed() {

		mButton4.setFocusableInTouchMode(true);
		mButton4.requestFocus();
	}

	public interface MessageDialogListener {
		void onButton1Clicked();

		void onButton2Clicked();

		void onButton3Clicked();

		void onButton4Clicked();
	}

	public void onClick(View v) {

		if (mMessageDialogListener != null) {
			if (v.getId() == R.id.button1) {
				Log.i(TAG, "Clicked on button button");
				mMessageDialogListener.onButton1Clicked();

			} else if (v.getId() == R.id.button2) {

				mMessageDialogListener.onButton2Clicked();

			} else if (v.getId() == R.id.button3) {

				mMessageDialogListener.onButton3Clicked();

			} else if (v.getId() == R.id.button4) {

				mMessageDialogListener.onButton4Clicked();
			}
		}
	}
}
