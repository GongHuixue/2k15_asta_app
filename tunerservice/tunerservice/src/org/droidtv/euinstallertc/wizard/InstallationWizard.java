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
package org.droidtv.euinstallertc.wizard;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Stack;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.ui.tvwidget2k15.NPanelBrowser;
import org.droidtv.ui.tvwidget2k15.VerticalText;
import org.droidtv.ui.tvwidget2k15.wizardframework.Wizard;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;

public class InstallationWizard extends Wizard {

	public enum ScreenRequest {
		WIZARD_INSTALLATION, REINSTALL_SCREEN, COUNTRY_SCREEN, PINENTRY_SCREEN, 
		TIMEZONE_SCREEN, ANTENNA_SCREEN, DIGITAL_SCREEN, OPERATOR_SCREEN, 
		SEARCH_SCREEN, SEARCHING_SCREEN, FINISH_SCREEN, STARTUPDATE_SCREEN, 
		UPDATING_SCREEN, UPDATEFINISHED_SCREEN, TERRIESTRIAL_OPERATOR_SCREEN, 
		HBBTV_PRIVACY_STATEMENT
	};

	private final String TAG = InstallationWizard.class.getName();
	private Context mContext;
	private ArrayList<View> mWizardInstallation = new ArrayList<View>();
	private ScreenRequest mLaunchItem = ScreenRequest.WIZARD_INSTALLATION;
	private Stack<ScreenRequest> mScreenRequestStack;
	private int progress = 0;
	private NPanelBrowser mNpb = null;
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();

	public InstallationWizard(Context context) {
		this(context, null, 0);
	}

	public InstallationWizard(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public InstallationWizard(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		mContext = context;
		if(NativeAPIWrapper.getInstance().isCamUpdateMode())
		{
			mLaunchItem = ScreenRequest.UPDATING_SCREEN;
		}
		mScreenRequestStack = new Stack<InstallationWizard.ScreenRequest>();
		mScreenRequestStack.push(mLaunchItem);
		loadLayout(context, attrs, defStyle);
	}

	private void loadLayout(Context context, AttributeSet attrs, int defStyle) {
		mContext = context;

		ViewGroup vg = (ViewGroup) View.inflate(mContext,
				R.layout.installationwizard_steps, null);

		mNpb = (NPanelBrowser) ((Activity)mContext)
				.findViewById(org.droidtv.ui.tvwidget2k15.R.id.nPanelBrowser1);
		while (vg.getChildCount() != 0) {
			View step = vg.getChildAt(0);
			((IInstallationScreen) step).setInstance(this);
			((WizardStep) step).setWizardListener(this);
			mWizardInstallation.add(step);
			vg.removeViewAt(0);
		}
	}

	@Override
	public void setWizardLabel(String arg0) {
		super.setWizardLabel(arg0);
	}

    public void launchPreviousScreen() {
        Log.d(TAG, "launchPreviousScreen previouscreen:" + mLaunchItem);
		if(!mScreenRequestStack.empty())
		{ // ignore multiple invalid calls
	        mLaunchItem = mScreenRequestStack.pop();
	        if (mLaunchItem == ScreenRequest.PINENTRY_SCREEN) {
	            if (nwrap.ifShowPinEntryScreen() == false) {
	                // remove pin entry screen from stack
	                mLaunchItem = mScreenRequestStack.pop();
	            }
	        }

	        Log.d(TAG, "launchPreviousScreen currentscreen:" + mLaunchItem);
	        mNpb.scrollPrevPage();
	        IInstallationScreen currentScreenInst = getScreenInstance(getCurrentScreen());
	        currentScreenInst.screenIntialization();
		}
    }

	public void launchScreen(ScreenRequest launchItem,
			ScreenRequest requestedByScreen) {
		Log.d(TAG, "launchScreen: " + launchItem + " requestedByScreen: "
				+ requestedByScreen);

		// populate in the stack with existing item
		mScreenRequestStack.push(mLaunchItem);

		// set the next screen to be launched
		mLaunchItem = launchItem;

		// trigger callback by framework to getPanelView(index) function
		mNpb.scrollNextPage();
		
		IInstallationScreen currentScreenInst = getScreenInstance(getCurrentScreen());
		currentScreenInst.screenIntialization();
	}

	public void initWizardScreen()
	{
		IInstallationScreen currentScreenInst = getScreenInstance(getCurrentScreen());
		currentScreenInst.screenIntialization();
	}
	
	public ScreenRequest getCurrentScreen() {
		Log.d(TAG, "getCurrentScreen() " + mLaunchItem);
		return mLaunchItem;
	}

	public IInstallationScreen getScreenInstance(ScreenRequest argScreenName ){
		IInstallationScreen returnScreen = null;
		// iterate and get the matching screen view
		Iterator<View> iterator = mWizardInstallation.iterator();
		
		while (iterator.hasNext()) {
			returnScreen = (IInstallationScreen)iterator.next();
			if (mLaunchItem == returnScreen.getScreenName()) {
				break;
			}
		}
		return returnScreen;
	}

	@Override
	public View getPanelView(int index) {
		View retView = null;
		
		setWizardLabel(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_VB_CHANNEL_INSTALLATION));

		// update the wizard progress
		progress = index;
		if (progress >= 0 && progress < mWizardInstallation.size() - 1) {
			setWizardProgress(progress + 1, mWizardInstallation.size() - 1);
		}

		// iterate and get the matching screen view
		Iterator<View> iterator = mWizardInstallation.iterator();
		while (iterator.hasNext()) {
			retView = iterator.next();

			if (mLaunchItem == (((IInstallationScreen) retView).getScreenName())) {

				if ((mLaunchItem == ScreenRequest.FINISH_SCREEN)|| 
						(mLaunchItem == ScreenRequest.UPDATEFINISHED_SCREEN)) {
					setWizardProgress(mWizardInstallation.size() - 1,
							mWizardInstallation.size() - 1);
				}
				break;
			}
		}

		return retView;
	}

	@Override
	public void setDepth(int depth) {
		super.setDepth(depth);
	}

    public View getBacktraceView(int depth, View view) {
        VerticalText verticalText;

        if (view == null) {
            view = new VerticalText(mContext);
        }

        Iterator<View> iterator = mWizardInstallation.iterator();
        while (iterator.hasNext()) {
            View retView = iterator.next();
            if (depth == -1) {
                verticalText = ((VerticalText) view);
                verticalText
                        .setText(mContext
                                .getString(org.droidtv.ui.strings.R.string.MAIN_VB_CHANNEL_INSTALLATION));
                break;
            } else {
                if (mLaunchItem == (((IInstallationScreen) retView)
                        .getScreenName())) {
                    verticalText = ((VerticalText) view);
                    if (retView.getTag() != null) {
                        verticalText.setText(retView.getTag().toString());
                    } else {
                        verticalText
                                .setText(mContext
                                        .getString(org.droidtv.ui.strings.R.string.MAIN_VB_AUTOSTORE_OR_UPDATE));
                    }
                    break;
                }
            }
        }

        return view;
    }

	@Override
	public void cancelStep() {
		super.cancelStep();
		((Activity)mContext).finish();
	}

	@Override
	public boolean isFocussable(int index) {
		if (index < mWizardInstallation.size()) {
			Log.v(TAG, "isFocussable called IF");
			return true;
		} else {
			Log.v(TAG, "isFocussable called else");
			return false;
		}
	}

	@Override
	public void gotoNextStep() {
		super.gotoNextStep();
	}

}
