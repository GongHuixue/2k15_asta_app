package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.wizard.SatelliteInstallationActivity;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.CheckBoxSelector;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.util.SparseBooleanArray;
import android.view.LayoutInflater;
import android.view.View;

public class SatelliteSelection extends WizardStep implements SatelliteScreen
{

	private static final String TAG = SatelliteScreen.class.getName();
	private Context mContext;
	private SatelliteWizard mSatelliteWizard;
	private CheckBoxSelector mCheckBoxSelector;
	private NativeAPIWrapper mNativeAPIWrapper;
	private int m_lnbCount;
	

	public SatelliteSelection(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		mNativeAPIWrapper = NativeAPIWrapper.getInstance();
		loadLayout(context);
	}

	public SatelliteSelection(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public SatelliteSelection(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

		View view = inflater.inflate(org.droidtv.ui.tvwidget2k15.R.layout.checkbox_selector_layout, null);
		addView(view);

		mCheckBoxSelector = (CheckBoxSelector) view.findViewById(org.droidtv.ui.tvwidget2k15.R.id.checkBoxSelector1);

		OnClickListener buttonPrevious_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				mSatelliteWizard.launchPreviousScren();
			}
		};

		OnClickListener buttonNext_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				//mCheckBoxSelector.isItemChecked(position);
				SparseBooleanArray l_arr = mCheckBoxSelector.getCheckedItemPositions();
				mNativeAPIWrapper.SelectLNBForUpdate(l_arr);
				mSatelliteWizard.launchScreen(ScreenRequest.UPDATESCAN, getScreenName());
			}
		};

		OnClickListener buttonCancel_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				((SatelliteInstallationActivity) mContext).exitInstallationWizard();
			}
		};
		
		String l_btnNext_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);

		setButton3(l_btnNext_txt, buttonNext_Listener, VISIBLE);
		setButton2(l_btnPrev_txt, buttonPrevious_Listener, VISIBLE);
		setButton1(l_btnCancel_txt, buttonCancel_Listener, VISIBLE);

		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_SELECTION));
	}

	@Override
	public void update(Observable observable, Object data)
	{

	}

	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.SATELLITESELECTION;
	}

	@Override
	public void screenIntialization()
	{
		Log.d(TAG,"screenInitialization");
		int l_idx;
		String l_satName;
		boolean l_isDuplicate = false;
		
		m_lnbCount = mNativeAPIWrapper.getLNBCount();
		String[] l_nameArray = new String[m_lnbCount];
		for(l_idx = 0; l_idx < m_lnbCount; l_idx ++)
		{
			l_satName = mNativeAPIWrapper.GetSatelliteName(l_idx);
			l_isDuplicate = mNativeAPIWrapper.IsSatelliteDuplicate(l_idx);
			if(l_isDuplicate)
			{
				l_satName += mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_DUPLICATE);
			}
			l_nameArray[l_idx] = l_satName;
		}
		mCheckBoxSelector.setArray(l_nameArray);
		for(l_idx = 0; l_idx < m_lnbCount; l_idx ++)
		{
			mCheckBoxSelector.setItemChecked(l_idx, mNativeAPIWrapper.GetInsUpdateSatelliteChecked(l_idx));
			
		}
	}

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		
	}

}
