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
import java.util.Iterator;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.SatInstaller;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.model.notification.NotificationInfoObject;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.media.ITvMediaCI.CICamIdInfo;

import android.content.Context;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class MenuWidget extends CIDialog implements Observer {

	private static final String TAG= MenuWidget.class.getName();
	private Context mContext;
	private int mSelectedMenuPanelItem;
	
	private SatInstaller mSatInstaller;
	private CIInitializeInterface mCiInitializeInterface;
	private ListView mlistView;
	private View onePanelScreen;
	private boolean isCancelled = false;
	private NotificationHandler mNotificationHandler;
	private static final int mTitlesArray =3;
	private static final int mInitialPosition = 0;
	private static final int  mDefaultSelectedItem = 0;
	private static final int mTitlePosition = 1;
	private static final int mSubTitlePosition = 2;
	private static final int mBottomTextPosition = 3;
	
	public MenuWidget(Context context,SatInstaller satInstaller,CIInitializeInterface ciInitializeInterface){
		super(context);
		mContext = context;
		mCiInitializeInterface = ciInitializeInterface;
		mSatInstaller = satInstaller;
		//Register for notifications
		registerForNotification();
		Log.i(TAG, "MenuWidget constructor calling:"+mSatInstaller+"mContext:"+mContext);
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

	/*
	 * Set call to MW when the dialog is opened
	 */
	private void setMWInitial(){
	Log.i(TAG, "setMWInitial called:"+mSatInstaller);
	if(mSatInstaller != null){
		mSatInstaller.setMmiEnable();
		mSatInstaller.setMMIInProgress(true);
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
	 * Set call to MW when the user pressed EXIT button
	 */
	private void setMWExit(){
		Log.i(TAG, "setMWExit called:");
		Log.i(TAG, "setMWExit called else block:"+mSatInstaller);
		if(mSatInstaller != null){
				mSatInstaller.setExitResponse();
				mSatInstaller.setExitToOSD();
				mSatInstaller.setMMIInProgress(false);
		}
	}
	
	/*
	 * Set call to MW when the user pressed OK button
	 */
	private void setMWOK(){
	Log.i(TAG, "setMWOK called ");
		Log.i(TAG,"setMWOK called else block:"+mSelectedMenuPanelItem);
		++mSelectedMenuPanelItem;
		Log.i(TAG,"setMWOK called else block:"+mSatInstaller +"mSelectedMenuPanelItem:"+mSelectedMenuPanelItem);
		if(mSatInstaller != null){
			mSatInstaller.setMmiOKMenuCmdResponse(mSelectedMenuPanelItem);
		}
	}
	
	
	
	/*
	 * Set call to MW when the user pressed Cancel button
	 */
	private void setMWCancel(){
		Log.i(TAG,"setMWCancel called");
			Log.i(TAG,"setMWCancel called else block:"+mSatInstaller);
			if(mSatInstaller != null){
				mSatInstaller.setMmiCancelMenuCmdResponse();
			}
	}
	
	public void displayMenuWidget() {
				Log.i(TAG, "displayMenuWidget() called:"+mSatInstaller+"mContext:"+mContext+"mNotificationHandler:"+mNotificationHandler+"isCancelled:"+isCancelled);
				
				//Set call to MW
				setMWInitial();
				
				final LayoutInflater inflater = (LayoutInflater) mContext
						.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
				onePanelScreen = inflater.inflate(R.layout.menuonepanel, null);
				String[] menuPanelItems = mSatInstaller.getMmiMenuItems().MenuStrings;
				Log.i(TAG, "menuPanelITems:" + menuPanelItems.length);
				String[] titleItems = new String[mTitlesArray];
				
				String[] optionItems = new String[menuPanelItems.length-mTitlesArray];
				
				System.arraycopy(menuPanelItems, mInitialPosition, titleItems, mInitialPosition, mTitlesArray);
				System.arraycopy(menuPanelItems, mTitlesArray, optionItems, mInitialPosition, menuPanelItems.length-mTitlesArray);
				Log.i(TAG, "titleItems:" + titleItems.length);
				Log.i(TAG, "optionItems:" + optionItems.length);
				List<String> menuTitleList = new ArrayList<String>();
				for (String values : titleItems){
						menuTitleList.add(values);
						
				}
				Iterator<String> iterator2 = menuTitleList.iterator();
							while (iterator2.hasNext()) {
								Log.i("TAG","menuTitleList items:"+iterator2.next());
								
							}
				
				List<String> menuOptionsList = new ArrayList<String>();
				for (String values : optionItems){
						if (values != null && values.length() > 0 ){
							menuOptionsList.add(values);
						
						
						}
				}
				Iterator<String> iterator1 = menuOptionsList.iterator();
							while (iterator1.hasNext()) {
								Log.i("TAG","menuOptionsList items:"+iterator1.next());
								
							}
				Log.i(TAG, "menuTitleList Size:" + menuTitleList.size());
				Log.i(TAG, "menuOptionsList Size:" + menuOptionsList.size());
				 try {
					int panelSize = menuTitleList.size();
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
						setTitleText(slotName+" "+menuTitleList.get(0).toString());
						setTitleVisibility(View.VISIBLE);
					}
					// Set the subtitle
					if (panelSize >= mSubTitlePosition) {
						Log.i(TAG,
								"inside loop subtitle:" + menuTitleList.get(1));
						setSubtitleText(menuTitleList.get(1).toString());
						setSubtitleVisibility(View.VISIBLE);
					}
					// Set the bottom text
					if (panelSize >= mBottomTextPosition) {
						Log.i(TAG,
								"inside loop subtitle:" + menuTitleList.get(2));
						setBottomText(menuTitleList.get(2).toString());
						setBottomTextVisibility(View.VISIBLE);
					}
					
					handleListView(menuOptionsList);
						/*if (menuOptionsList.size() > 0) {
							// Set the title
							
							rs = (RadioSelector)onePanelScreen.findViewById(R.id.radioselector);
							Iterator<String> iterator = menuOptionsList.iterator();
							while (iterator.hasNext()) {
								Log.i("TAG","List items:"+iterator.next());
								
							}
							String[] listItems = new String[menuOptionsList.size()];
							Log.i("TAG","List Size"+listItems.length);
							listItems = menuOptionsList.toArray(listItems);
							
							
							rs.setArray(listItems);
							Log.i("TAG","Radio Selector child count:"+rs.getChildCount());
							rs.setOnItemClickListener(new OnItemClickListener() {

								@Override
								public void onItemClick(AdapterView<?> arg0,
										View view, int clickedITem, long arg3) {
									
									mSelectedMenuPanelItem = clickedITem;
									Log.i(TAG,"onClicked radaio list :"+clickedITem);
									setButton4focussed();
								}
								
							});
					setfocusOnTheRadioList();
	
					}else {
							rs = (RadioSelector)onePanelScreen.findViewById(R.id.radioselector);
							String[] listItems = new String[menuOptionsList.size()];
							Log.i("TAG","List Size"+listItems.length);
							listItems = menuOptionsList.toArray(listItems);
							rs.setArray(listItems);
					}*/

				} catch (Exception nxe) {
					Log.e(TAG, nxe.toString());
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
					Log.i(TAG, "onButton4Clicked() called");
						//Set to MW
						setMWOK();
					}
					@Override
					public void onButton3Clicked() {
						isCancelled = true;
						Log.i(TAG, "onButton3Clicked() called");
						//Set to MW
						setMWCancel();
					}
					@Override
					public void onButton2Clicked() {
						Log.i(TAG,"MenuWidget onButton2Clicked Activity:"+mContext);
						closeWidget();
					}
					@Override
					public void onButton1Clicked() {
					}
				});
				//setButton4focussed();
				addView(onePanelScreen);
				show();
			//}
		//});
	}
	
	private void handleListView(List<String> argListItems) {
		Log.i(TAG, "handleListView");

		// print the list items
		Iterator<String> iterator = argListItems.iterator();
		while (iterator.hasNext()) {
			Log.i("TAG", "List items:" + iterator.next());

		}

		if (argListItems.size() > 0) {

			// inflate list
			mlistView = (ListView) onePanelScreen.findViewById(R.id.listview);

			// populate list & set adapter
			String[] listArray = new String[argListItems.size()];
			listArray = argListItems.toArray(listArray);
			mlistView.setAdapter(new ArrayAdapter<String>(mContext, org.droidtv.ui.tvwidget2k15.R.layout.simple_list_item_activated_1, listArray));

			mlistView.setOnItemClickListener(new OnItemClickListener() {

				@Override
				public void onItemClick(AdapterView<?> arg0, View arg1, int selectedItem, long arg3) {
					Log.i(TAG, "selected item in list :" + selectedItem);
					mSelectedMenuPanelItem = selectedItem;
					setButton4focussed();
				}
			});

			// set default focus on first item
			Log.d(TAG, "setfocusOnTheRadioList called:");

			Log.i(TAG, "handleListView isCancelled:" + isCancelled);

			int lastSelectedIndex = 0;
			if (isCancelled) {
				// the dialog has been canceled launched second time
				// Retrieve and focus last selected index
				lastSelectedIndex = mSatInstaller.getLastSelectedMenuIndex();
				--lastSelectedIndex;
				isCancelled = false;
			} else {
				// the dialog has not been canceled launched for first time
				// set the selection on default selected item
				lastSelectedIndex = mDefaultSelectedItem;
			}

			mlistView.setSelection(lastSelectedIndex);
			mlistView.setItemChecked(lastSelectedIndex, true);
			mlistView.requestFocus();

		} else {
			Log.d(TAG, "no items to show directly set focus on button");
			setButton4focussed();
		}
	}
	
	private void setMWEVENT(){
			//mPlayTvCIPlusHandler.setMmiOpenSupported(false);
	}
	
	@Override
	public void update(Observable observable, Object data) {
		final int eventID = ((NotificationInfoObject) data).actionID;
		Log.i(TAG,"MenuWidget update called:"+eventID);
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
	 * Hide the dialog and unregister from notifications
	 */
	public void hideDialog(){
		Log.i(TAG,"hideDialog called:");
		unRegisterFromNotifications();
		hide();
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		boolean handled = false;
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		Log.i(TAG,"Menu Widget dispatchKeyEvent pressed:"+keyCode);
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
			Log.i(TAG,"Menu Widget dispatchKeyEvent pressed handle:"+handled);
		Log.i(TAG,"Menu Widget dispatchKeyEvent pressed return values:"+handled);
		return handled || super.dispatchKeyEvent(event);
	}
	
} 
