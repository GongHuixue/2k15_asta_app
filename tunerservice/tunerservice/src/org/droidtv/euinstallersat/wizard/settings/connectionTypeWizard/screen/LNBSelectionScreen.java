package org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.screen;

import java.util.Observable;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper.CONNECTION_TYPE;
import org.droidtv.euinstallersat.wizard.settings.WizardSettingsActivity;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeScreen;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeWizard;
import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeWizard.ConnTypeScreenReq;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.CheckBoxSelector;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.AttributeSet;
import android.util.Log;
import android.util.SparseBooleanArray;
import android.view.FocusFinder;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;

public class LNBSelectionScreen extends WizardStep implements ConnTypeScreen {
	private final String TAG = LNBSelectionScreen.class.getName();
	private Context mContext;
	private NativeAPIWrapper nwrap;
	private CheckBoxSelector mCheckBoxSelector;

	public LNBSelectionScreen(Context context, AttributeSet attrSet, int defStyle) {
		super(context, attrSet, defStyle);
		mContext = context;
		nwrap = NativeAPIWrapper.getInstance();
		loadLayout(context);
	}

	private void loadLayout(final Context context) {
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.checkbox_selector_layout, null);
		addView(view);

		mCheckBoxSelector = (CheckBoxSelector) view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.checkBoxSelector1);

		OnClickListener buttonPrevious_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				launchWizardSettings();
			}
		};

		OnClickListener buttonNext_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				// mCheckBoxSelector.isItemChecked(position);
				SparseBooleanArray arr = mCheckBoxSelector.getCheckedItemPositions();
				if(arr.size() == 0){
					// cannot proceed
				}else{
					
					// reset 
					for(int index = 0; index < 4; index++){
						nwrap.setPrescanLNBs(index,true);
					}
					// save selected LNB's
					for(int index = 0; index < arr.size(); index++){
						if(arr.get(index) == true){
							nwrap.setPrescanLNBs(index, true);
						}else{
							nwrap.setPrescanLNBs(index, false);
						}
					}
					launchWizardSettings();
				}
			}
		};

		OnClickListener buttonCancel_Listener = new OnClickListener() {

			@Override
			public void onClick(View v) {
				launchWizardSettings();
			}
		};
		
		mCheckBoxSelector.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
				SparseBooleanArray arr = mCheckBoxSelector.getCheckedItemPositions();
				int selectedLNBCount = 0;
				for(int index = 0; index < arr.size(); index++){
					if(arr.get(index) == true){
						selectedLNBCount++;
					}
				}
				
				if(selectedLNBCount == 0){
					setButton3Enabled(false);
				}else{
					setButton3Enabled(true);
				}
				
			}
		});

		setButton1(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL), buttonCancel_Listener, VISIBLE);
		setButton2(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS), buttonPrevious_Listener, INVISIBLE);
		setButton3(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT), buttonNext_Listener, VISIBLE);
		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_CH_LNB_SELECTION));
	}

	private void launchWizardSettings() {
		Intent intent;
		intent = new Intent(mContext, WizardSettingsActivity.class);
		((Activity) mContext).finish();
		mContext.startActivity(intent);
	}
	
	public LNBSelectionScreen(Context context, AttributeSet attrSet) {
		this(context, attrSet, 0);
	}

	public LNBSelectionScreen(Context context) {
		super(context);
	}

	@Override
	public void setInstance(ConnTypeWizard p_wizard) {
	}

	@Override
	public ConnTypeScreenReq getScreenName() {
		return ConnTypeScreenReq.LNBSELECTION;
	}

	@Override
	public void screenIntialization() {
		int maxLNBCount = 4;
		if (nwrap.getConnectionTypeFromMW() == CONNECTION_TYPE.DISEQC_MINI) {
			mCheckBoxSelector.setArray(new String[] { 
					mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB1),
					mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB2) 
					});
			maxLNBCount = 2;
		} else if (nwrap.getConnectionTypeFromMW() == CONNECTION_TYPE.DISEQC_1_0) {
			mCheckBoxSelector.setArray(new String[] {
					mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB1),
					mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB2),
					mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB3),
					mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB4) 
					});
			maxLNBCount = 4;
		}
		
		for(int index = 0; index < maxLNBCount; index++){
			mCheckBoxSelector.setItemChecked(index, nwrap.getPrescanForLNBs()[index]);
		}
		
		mCheckBoxSelector.requestFocus();
	}

	@Override
	public void update(Observable arg0, Object arg1) {

	}
	
	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		int keyCode = event.getKeyCode();
        int keyAction = event.getAction();
        boolean handled = false;

        View currentFocus;
        View leftFocus = null;
        View rightFocus = null;

        currentFocus = ((Activity)mContext).getCurrentFocus();
        if (currentFocus != null) {
            leftFocus = FocusFinder.getInstance().findNextFocus((ViewGroup) currentFocus.getParent(), currentFocus, View.FOCUS_LEFT);
            rightFocus = FocusFinder.getInstance().findNextFocus((ViewGroup) currentFocus.getParent(), currentFocus, View.FOCUS_RIGHT);
        }
        
		/*if ((event.getKeyCode() == KeyEvent.KEYCODE_BACK) || (event.getKeyCode() == KeyEvent.KEYCODE_ESCAPE)) {
			launchWizardSettings();
		}*/
        
        Log.d(TAG, "dispatchKeyEvent currentFocus: " + currentFocus + " ,leftFocus:" + leftFocus + ",rightFocus:" + rightFocus);

		 if ((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) {
	            if (keyAction == KeyEvent.ACTION_DOWN) {
	                launchWizardSettings();
	                handled = true;
	            } else if (keyAction == KeyEvent.ACTION_UP) {
	                handled = true;
	            }
	        } else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT) {
	            if (keyAction == KeyEvent.ACTION_DOWN) {

	                if (currentFocus instanceof Button) {
	                    // left key pressed over wizard buttons
	                    if (leftFocus == null) {
	                        // nothing on the left side go to previous screen
	                        handled = true;
	                    }else if(leftFocus instanceof Button){
	                    	leftFocus.requestFocus();
	                    	handled = true;
	                    }
	                    // else let android handled the default case
	                } else if (currentFocus instanceof CheckBoxSelector) {
	                    // left key pressed over radio list
	                    handled = true;
	                } else {
	                    // block other default cases
	                    handled = true;
	                }
	            } else if (keyAction == KeyEvent.ACTION_UP) {
	                handled = true;
	            }
	        } else if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
	            if (keyAction == KeyEvent.ACTION_DOWN) {

					if (currentFocus instanceof Button) {
						// right key pressed over wizard buttons
						if (rightFocus == null) {
							// nothing on the right side consume the key
							handled = true;
						}else if(rightFocus instanceof Button){
							rightFocus.requestFocus();
	                    	handled = true;
	                    }// else let android handled the default case
					} else if (currentFocus instanceof CheckBoxSelector) {
						// right key pressed over radio list
						setButton3focussed();
	                    handled = true;
	                }else {
	                    // block other default cases
	                    handled = true;
	                }
	            } else if (keyAction == KeyEvent.ACTION_UP) {
	                handled = true;
	            }
	        } else if (keyCode == KeyEvent.KEYCODE_DPAD_UP) {
	            handled = super.dispatchKeyEvent(event);
	        } else if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
	            handled = super.dispatchKeyEvent(event);
	        }else {
	            // for other keys let it call super to retain default behavior from wizard framework
	            super.dispatchKeyEvent(event);
	            handled = false;
	        }

	        return handled;
	}
}
