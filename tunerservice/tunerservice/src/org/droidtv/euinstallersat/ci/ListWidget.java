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

import java.util.ArrayList;
import java.util.List;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.media.ITvMediaCI.CICamIdInfo;
import java.util.Observable;
import java.util.Observer;
import java.util.Iterator;
import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.SatInstaller;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.ui.tvwidget2k15.wizardframework.common.RadioSelector;
import android.view.KeyEvent;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class ListWidget extends CIDialog  implements Observer{

	private static final String TAG = ListWidget.class.getName();
	private SatInstaller mSatInstaller;
	private int mSelectedListPanelItem;
	private CIInitializeInterface mCiInitializeInterface;
	private Context mContext;
	private RadioSelector rs;
	private NotificationHandler mNotificationHandler;
	private static final int mTitlesArray =3;
	private static final int mInitialPosition = 0;
	private static final int  mDefaultSelectedItem = 0;
	private static final int mTitlePosition = 1;
	private static final int mSubTitlePosition = 2;
	private static final int mBottomTextPosition = 3;
	public ListWidget(Context context,SatInstaller satInstaller,CIInitializeInterface ciInitializeInterface){
		super(context);
		mContext = context; 
		mCiInitializeInterface = ciInitializeInterface;
		mSatInstaller = satInstaller;
		//Register for notifications
		registerForNotification();
		Log.i(TAG, "ListWidget constructor calling:"+mSatInstaller+"mContext:"+mContext);
	}
	
	private void setMWEVENT(){
			//mPlayTvCIPlusHandler.setMmiOpenSupported(false);
	}
	
	@Override
	public void update(Observable observable, Object data) {
		
		final int eventID = ((NotificationInfoObject) data).actionID;
		Log.i(TAG,"update called EventID:"+eventID);
		switch (eventID) {
		case EventIDs.CI_OPENMMI_WIDGET:
			//set call to MW
			setMWEVENT();
			break;
		case EventIDs.CI_CLOSEMMI_WIDGET:
			closeWidget();
			break;
		default:
			break;
		}

	}
	
	/*
	 * Registering for notifications
	 */
	private void registerForNotification(){
		mNotificationHandler = NotificationHandler.getInstance();
		mNotificationHandler.registerForNotification(this);
	}
	
	/*
	 * Unregistering notifications
	 */
	private void unRegisterFromNotifications(){
		if(mNotificationHandler != null){
			mNotificationHandler.unRegisterForNotification(this);
		}
	}

	public void closeWidget(){
	Log.i(TAG, "closeWidget called:"+mCiInitializeInterface);
		if(mCiInitializeInterface != null && mContext != null) {
				mCiInitializeInterface.setCurrentEvent();
				//set to MW
				setMWExit();
				hideDialog();
		}
	}
	
	/*
	 * Set call to MW when the dialog is opened
	 */
	private void setMWInitial(){
	Log.i(TAG, "setMWInitial called:"+mSatInstaller);
		if(mSatInstaller != null) {
			mSatInstaller.setMmiEnable();
			mSatInstaller.setMMIInProgress(true);
		}
		
	}
	
	/*
	 * Set call to MW when the user pressed EXIT button
	 */
	private void setMWExit(){
	Log.i(TAG, "setMWExit called:"+mSatInstaller);
	if(mSatInstaller != null){ 
			Log.i(TAG, "setMWExit called else block:");
			mSatInstaller.setExitResponse();
			mSatInstaller.setExitToOSD();
			mSatInstaller.setMMIInProgress(false);
		}
	}
	
	/*
	 * Set call to MW when the user pressed OK button
	 */
	private void setMWOK(){
	Log.i(TAG, "setMWOK called:"+mSatInstaller);
		if(mSatInstaller != null){ 
			Log.d(TAG, "setMWOK called else block:");
			mSatInstaller.setMmiOKListCmdResponse(++mSelectedListPanelItem);
		}
	}
	
	
	/*
	 * Set call to MW when the user pressed Cancel button
	 */
	private void setMWCancel(){
		Log.i(TAG,"setMWCancel called:"+mSatInstaller);
		if(mSatInstaller != null){ 
			Log.d(TAG,"setMWCancel called else block:");
			mSatInstaller.setMmiCancelListCmdResponse();
		}
	}
	
	
	public void displayListWidget() {
				Log.i(TAG, "displayListWidget() calling:"+mSatInstaller+"mContext:"+mContext+"mNotificationHandler:"+mNotificationHandler);
				
				
				//set call to MW
				setMWInitial();
				
				View onePanelScreen;
				final LayoutInflater inflater = (LayoutInflater) mContext
						.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
				onePanelScreen = inflater.inflate(R.layout.onepanellist, null);
				
				String[] listPanelItems = mSatInstaller.getMmiListItems().MenuStrings;
				Log.i(TAG, "listPanelItems:" + listPanelItems.length);
				String[] titleItems = new String[mTitlesArray];
				String[] optionItems = new String[listPanelItems.length-mTitlesArray];
				
				
				System.arraycopy(listPanelItems, mInitialPosition, titleItems, mInitialPosition, mTitlesArray);
				System.arraycopy(listPanelItems, mTitlesArray, optionItems, mInitialPosition, listPanelItems.length-mTitlesArray);
				Log.i(TAG, "listtitleItems:" + titleItems.length);
				Log.i(TAG, "listoptionsItems:" + optionItems.length);
				List<String> listTitleItems = new ArrayList<String>();
				for (String values : titleItems){
						listTitleItems.add(values);
				}
				Iterator<String> iterator1 = listTitleItems.iterator();
							while (iterator1.hasNext()) {
								Log.i("TAG","listTitleItems items:"+iterator1.next());
								
							}
				Log.i(TAG, "menuPanelITems:" + listTitleItems.size());
				List<String> listOptionItems = new ArrayList<String>();
				for (String values : optionItems){
					if (values != null && values.length() > 0 ){
						listOptionItems.add(values);
					}
				}
				Iterator<String> iterator2 = listOptionItems.iterator();
							while (iterator2.hasNext()) {
								Log.i("TAG","listOptionItems items:"+iterator2.next());
								
							}
				Log.i(TAG, "menuPanelITems:" + listOptionItems.size());
				try { 

					int panelSize = listTitleItems.size();
					// Set the tile
					if (panelSize >= mTitlePosition) {
						CICamIdInfo cICamIdInfo = mSatInstaller.getCamIDInfo(ITvMediaCI.SLOT_UNKNOWN);
						int slotID = -1;
						if(cICamIdInfo != null && cICamIdInfo.SlotID <= 1 && cICamIdInfo.SlotID >= 0){
							slotID = cICamIdInfo.SlotID;
						}
						Log.i(TAG,"MenuWidget slotID:"+slotID+"cICamIdInfo:"+cICamIdInfo);
						String slotName = null;
						if(slotID == 0){
							slotName = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_COMMON_INTERFACE_SLOT_2);
						} else {
							slotName = mContext.getString(org.droidtv.ui.strings.R.string.MAIN_COMMON_INTERFACE_SLOT_1);
						}
						setTitleText(slotName+" "+listTitleItems.get(0).toString());
						setTitleVisibility(View.VISIBLE);
					}
					// Set the subtitle
					if (panelSize >= mSubTitlePosition) {
						Log.i(TAG,
								"inside loop subtitle:" + listTitleItems.get(1));
						setSubtitleText(listTitleItems.get(1).toString());
						setSubtitleVisibility(View.VISIBLE);
					}
					// Set the bottom text
					if (panelSize >= mBottomTextPosition) {
						Log.i(TAG,
								"inside loop subtitle:" + listTitleItems.get(2));
						setBottomText(listTitleItems.get(2).toString());
						setBottomTextVisibility(View.VISIBLE);
					}
					
						if (listOptionItems.size() > 0) {
							// Set the list count
							rs = (RadioSelector)onePanelScreen.findViewById(R.id.radioselector);
							String[] listItems = new String[listOptionItems.size()];
							Log.i("TAG","List Size"+listItems.length);
							listItems = listOptionItems.toArray(listItems);
							Log.i("TAG","Radio Selector:"+rs);
							rs.setArray(listOptionItems.toArray(listItems));
							setfocusOnTheRadioList();
							Log.i("TAG","List Size"+rs.getChildCount());
							rs.setOnItemClickListener(new OnItemClickListener() {

								@Override
								public void onItemClick(AdapterView<?> arg0,
										View view, int clickedITem, long arg3) {
									
									mSelectedListPanelItem = clickedITem;
									setButton4focussed();
								}
								
							});

						}else {
							rs = (RadioSelector)onePanelScreen.findViewById(R.id.radioselector);
							String[] listItems = new String[listOptionItems.size()];
							Log.i("TAG","List Size"+listItems.length);
							listItems = listOptionItems.toArray(listItems);
							rs.setArray(listItems);
						}
					
				} catch (Exception e) {
					Log.e(TAG, e.toString());
				}

				setButton2Text(mContext
						.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_EXIT));
				setButton2Visibility(View.VISIBLE);

				setButton4Text(mContext
						.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_OK));
				setButton4Visibility(View.VISIBLE);

				setButton3Text(mContext
						.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL));
				setButton3Visibility(View.VISIBLE);

				setButton1Visibility(View.INVISIBLE);


				setMessageDialogListener(new MessageDialogListener() {
					@Override
					public void onButton4Clicked() {
						//set call to MW
						setMWOK();
					}
					@Override
					public void onButton3Clicked() {
						//set call to MW
						setMWCancel();						
					}
					@Override
					public void onButton2Clicked() {
						closeWidget();
					}

					@Override
					public void onButton1Clicked() {
					}
				});
				//setButton4focussed();
				addView(onePanelScreen);
				show();
	}
	
	/*
	 * Hide the dialog and unregister from notifications
	 */
	public void hideDialog(){
		Log.i(TAG,"hideDialog called:");
		unRegisterFromNotifications();
		hide();
	}
	
	private void setfocusOnTheRadioList(){
		Log.d(TAG,"setfocusOnTheRadioList called:");
	    if(rs != null){
        rs.requestFocusFromTouch();
        rs.requestFocus();
        rs.setSelection(mDefaultSelectedItem);
        rs.setItemChecked(mDefaultSelectedItem, true);
		}
	}
	 
	 @Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		boolean handled = false;
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		Log.i(TAG,"List Widget dispatchKeyEvent pressed:"+keyCode);
		switch (keyCode) {
		case KeyEvent.KEYCODE_BACK:
			if (keyAction == KeyEvent.ACTION_DOWN) {
				Log.d(TAG,"BackKey pressed");
				closeWidget();
				handled = true;
			}
			break;
		case KeyEvent.KEYCODE_TV:
		case KeyEvent.KEYCODE_CHANNEL_UP:
		case KeyEvent.KEYCODE_CHANNEL_DOWN:
		case KeyEvent.KEYCODE_GUIDE:
		case KeyEvent.KEYCODE_INFO:
		case KeyEvent.KEYCODE_WINDOW:
		case KeyEvent.KEYCODE_TELETEXT:
		case KeyEvent.KEYCODE_MEDIA_RECORD:
			Log.i(TAG," GUIDE OR INFO OR WINDOW key pressed");
			handled = true;
			break;
		/*case KeyEvent.KEYCODE_DPAD_DOWN:
			Log.i(TAG, "keyAction Focus:" + keyAction);
			if (keyAction == KeyEvent.ACTION_DOWN) {
				Log.i(TAG, "current Focus:" + alphanumeric.isFocused());
				if (alphanumeric.isFocused()) {
					Log.d(TAG, "setting focus for the button");
					setButton4focussed();
				}
			}
			break;*/
			
		}
		Log.i(TAG,"List Widget dispatchKeyEvent pressed handle:"+handled);
	return handled || super.dispatchKeyEvent(event);
	}
	
}

