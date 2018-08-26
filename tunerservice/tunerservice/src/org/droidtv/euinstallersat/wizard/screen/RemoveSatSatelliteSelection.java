package org.droidtv.euinstallersat.wizard.screen;

import java.util.ArrayList;
import java.util.List;
import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.MwDataTypes;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.CheckBoxSelector;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.util.SparseBooleanArray;
import android.view.KeyEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class RemoveSatSatelliteSelection extends WizardStep implements SatelliteScreen
{

	private static final String TAG = RemoveSatSatelliteSelection.class.getName();
	private Context mContext;
	private NativeAPIWrapper mNativeApiWrapper;
	private View view;
	private CheckBoxSelector mCheckBoxSelector;
	private List<String> mCheckBoxList;
	private ArrayList<Integer> lnbIdx_arr;
	private String mItems[];
	private String m_satNameArray[];
	private int[] m_lnbConst;
	private View mNoChannelText;
	private int MAX_LNB_COUNT = 4;
	private SatelliteWizard mSatelliteWizard;
	private String m_satelliteString;
	private String m_duplicateString;
	private boolean m_isRemoveSatInProgress = false;
	private ModalDialog mModalDialog;
	private ModalDialog.Builder mBuilder;
	private int oredLnbIdx = 0x00;

	public RemoveSatSatelliteSelection(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		mContext = context;
		lnbIdx_arr = new ArrayList<Integer>();
		mNativeApiWrapper = NativeAPIWrapper.getInstance();
		loadLayout(context);
	}

	public RemoveSatSatelliteSelection(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public RemoveSatSatelliteSelection(Context context)
	{
		this(context, null, 0);
	}

	private void loadLayout(Context context)
	{
		//LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

		view = inflate(context, R.layout.removesatselection, null);
		addView(view);

		mNoChannelText = view.findViewById(R.id.nochannel);
		mCheckBoxSelector = (CheckBoxSelector) view.findViewById(R.id.checkboxselector);
		mCheckBoxSelector.setOnKeyListener(this);
		m_satelliteString = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_SATELLITE);
		m_duplicateString = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_DUPLICATE);
		m_satNameArray = new String[MAX_LNB_COUNT];
		m_satNameArray[0] = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB1);
		m_satNameArray[1] = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB2);
		m_satNameArray[2] = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB3);
		m_satNameArray[3] = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_LNB4);
		
		
		mCheckBoxSelector.setOnItemClickListener(new OnItemClickListener()
		{

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,long arg3)
			{
				
				int lCheckedItemCount = mCheckBoxSelector.getCheckedItemCount();
				Log.d(TAG,"lCheckedItemCount " + lCheckedItemCount);
				if (lCheckedItemCount > 0)
				{
					setButton3Enabled(true);
				} 
				else
				{
					setButton3Enabled(false);
				}

			}
		});
		
		
		OnClickListener buttonRemove_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				removeDialog();
			}
		};

		OnClickListener buttonExit_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				Log.d(TAG,"Click on exit button");
				unregisterForNotification();
				 mSatelliteWizard.launchPreviousScren();
			}

			
		};

		setButton1(null, null, INVISIBLE);
		setButton2(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_EXIT), buttonExit_Listener, VISIBLE);
		setButton3(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_REMOVE), buttonRemove_Listener, VISIBLE);

		setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_SATELLITE_REMOVE));

	}

	protected void removeDialog()
	{
		mBuilder = new ModalDialog.Builder(mContext,ModalDialog.HEADING_TYPE_DEFAULT);
        mBuilder.setHeading(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_TI_SAT_CONFIRM_REMOVE), "");
    	mBuilder.setMessage(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_DI_SAT_CONFIRM_REMOVE));
    	
    	ModalDialogFooterButtonProp mCancelButton = mBuilder.setButton(ModalDialog.BUTTON_MID_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_CANCEL clicked ");
    					mModalDialog.hide();
    				}
    			});
    	mBuilder.setButton(ModalDialog.BUTTON_RIGHT,
    			mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_REMOVE),
    			true,
    			new ModalDialogInterface.OnClickListener(){
    				@Override
    				public void onClick(ModalDialogInterface mDialogInterface, int iWhich){
    					Log.d(TAG, "MAIN_BUTTON_REMOVE clicked ");
    					enableWaitingAnimation(true);
    					mNativeApiWrapper.setInstallMode(NativeAPIWrapper.INSTALL_MODE_UPDATE);
    					mNativeApiWrapper.sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_START");
    					setButton2Enabled(false);
    					setButton3Enabled(false);
    					SparseBooleanArray checkedItems = mCheckBoxSelector.getCheckedItemPositions();
    					int length = mCheckBoxList.size();
    					int l_lnbIdx;
						oredLnbIdx = 0x00;
    					Log.d(TAG,"Number of satellites shown =" + length);
    					for (int i = length - 1; i >= 0; i--)
    					{
    						if (checkedItems.get(i) == true)
    						{
    							Log.i(TAG, "i value :" + i);
    							mCheckBoxList.remove(i);
    							l_lnbIdx = lnbIdx_arr.get(i);
    							Log.d(TAG, "Removing lnb with idx " + l_lnbIdx);
    							oredLnbIdx |= m_lnbConst[l_lnbIdx];
    							lnbIdx_arr.remove(i);
    						}
    					}
    					m_isRemoveSatInProgress = true;
    					mNativeApiWrapper.SetRemoveSatellite(oredLnbIdx);
    					
    					mModalDialog.hide();
                       
    				}
    			});
    	mModalDialog = mBuilder.build();
    	mModalDialog.setCancelable(false);
    	mModalDialog.show();
    	mCancelButton.requestFocus();

	}

	@Override
	public void update(Observable observable, Object data)
	{
		final int eventID = ((NotificationInfoObject) data).actionID;
		Log.i(TAG, "eventID:" + eventID);
		switch (eventID)
		{
			case EventIDs.SATELLITE_REMOVED:
				Log.d(TAG,"SATELLITE_REMOVED");
					mNativeApiWrapper.RemoveFromSatelliteDb(oredLnbIdx);
					updateRemoveList();
					Activity l_activity = (Activity) mContext;
					l_activity.runOnUiThread(new Runnable()
					{

						@Override
						public void run()
						{
							enableWaitingAnimation(false);
							mNativeApiWrapper.sendIntent("org.droidtv.euinstallersat.SATELLITE_INSTALL_COMPLETE");
						}
					});
					
					break;
		}

	}

	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;
	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.REMOVESATSELECTION;
	}

	@Override
	public void screenIntialization()
	{
		Log.d(TAG, "mNativeAPIWrapper:" + mNativeApiWrapper);
		NotificationHandler.getInstance().registerForNotification(this);
		m_lnbConst = new int[]{	MwDataTypes.IHsvSatelliteInstallation_SatLnb1,
								MwDataTypes.IHsvSatelliteInstallation_SatLnb2,
								MwDataTypes.IHsvSatelliteInstallation_SatLnb3,
								MwDataTypes.IHsvSatelliteInstallation_SatLnb4};
		mNoChannelText.setVisibility(INVISIBLE);
		updateRemoveList();
		

	}
	
	private void updateRemoveList()
	{
		Log.d(TAG,"updateRemoveList entry");
		int l_idx;
		mCheckBoxList = new ArrayList<String>();
		lnbIdx_arr.clear();
		m_isRemoveSatInProgress = false;
		for(l_idx = 0; l_idx < MAX_LNB_COUNT; l_idx++)
		{
			if(mNativeApiWrapper.isRemoveControllable(l_idx))
			{
				mCheckBoxList.add(m_satNameArray[l_idx] + ": " + getSatelliteName(l_idx));
				lnbIdx_arr.add(l_idx);
			}
		}
		
		Activity l_activity = (Activity) mContext;
		l_activity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{

				if (mCheckBoxList.size() > 0)
				{
					mCheckBoxSelector.setVisibility(View.VISIBLE);
					mItems = new String[mCheckBoxList.size()];
					mItems = mCheckBoxList.toArray(mItems);
					mCheckBoxSelector.setArray(mItems);
					mCheckBoxSelector.setItemChecked(0, false);
					Log.d(TAG,"List contents: " + mCheckBoxList.toString());
					Log.d(TAG,"new list size : " + mCheckBoxList.size());
				} else
				{
					Log.d(TAG, "List is empty");
					mCheckBoxSelector.setVisibility(View.INVISIBLE);
					mCheckBoxSelector.setEnabled(false);
					setHintText(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_NO_SATELLITES_FOUND));
					
				}
				setButton3Enabled(false);
				setButton2Enabled(true);
				setButton2focussed();
			}
		});
		
		
	}
	
	private String getSatelliteName(int p_lnbIdx)
	{
		Log.d(TAG, "getSatelliteName");
		String l_satName = "";
		if (!mNativeApiWrapper.IsLNBFree(p_lnbIdx))
		{
			boolean l_isDuplicate = mNativeApiWrapper.IsSatelliteDuplicate(p_lnbIdx);
			if (mNativeApiWrapper.GetIsRecognisedSatellite(p_lnbIdx))
			{
				l_satName = mNativeApiWrapper.GetSatelliteName(p_lnbIdx);
			}
			else
			{
				l_satName = m_satelliteString + p_lnbIdx;
			}
			if (l_isDuplicate)
			{
				l_satName = l_satName + " " + m_duplicateString;
			}

		}
		Log.d(TAG, "getSatelliteName returning" + l_satName);
		return l_satName;
	}
	
	@Override
    public boolean onKey(View view, int keyCode, KeyEvent event)
    {

           Log.d(TAG,"OnKey");
           boolean l_isKeyHandled = false;
           if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
           {
                  Log.d(TAG,"KEYCODE_DPAD_RIGHT");
                  if(mCheckBoxSelector == view)
                  {
                        setButton2focussed();
                  }
				  else
				  {
					super.onKey(view, keyCode, event);
				  }
                  l_isKeyHandled = true;
           }
           else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
           {
                  Log.d(TAG,"KEYCODE_DPAD_LEFT");
                  if(mCheckBoxSelector == view)
                  {
                        setButton1focussed();
                  }
				  else
				  {
					super.onKey(view, keyCode, event);
				  }
                  l_isKeyHandled = true;
           }
           else if (((keyCode == KeyEvent.KEYCODE_BACK) || (keyCode == KeyEvent.KEYCODE_ESCAPE)) && event.getAction() == KeyEvent.ACTION_UP)
           {
        	   if(!m_isRemoveSatInProgress)
        	   {
        		   mSatelliteWizard.launchPreviousScren();
        	   }
        	   l_isKeyHandled = true;
           }
           
           Log.d(TAG,"OnKey returning " + l_isKeyHandled);
           return l_isKeyHandled;

    }

	private void unregisterForNotification()
	{
		NotificationHandler.getInstance().unRegisterForNotification(this);
		
	}

	@Override
	public void screenExit()
	{
		Log.d(TAG,"screenExit");
		enableWaitingAnimation(false);
		unregisterForNotification();
	}

}
