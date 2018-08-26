package org.droidtv.euinstallersat.ci;

import org.droidtv.euinstallersat.model.mwapi.SatInstaller;
import org.droidtv.euinstallersat.util.EventIDs;

import android.content.Context;
import android.util.Log;
public abstract class CIInitializeInterface {

	private static final String TAG = CIInitializeInterface.class.getName();
	private SatInstaller mSatInstaller;
	private Context mContext;
	public int currentEvent = -1;
	private static final int mInitialEvent = -1;
	private boolean nonInterruptStatus;
	private TextWidget textWidget;
	private EnquiryWidget enquiryWidget;
	private ListWidget listWidget;
	private MenuWidget menuWidget;
	
	public void setContext(Context context){
		mContext = context;
		Log.i(TAG, "setContext called:"+mContext);
	}
	
	public void setSatInstaller(SatInstaller satInstaller){
		mSatInstaller = satInstaller;
		Log.i(TAG, "setPlayTvCIPlusHandler called:"+mSatInstaller);
	}
	
	public void setCurrentEvent(){
		Log.i(TAG, "setCurrentEvent called currentEvent:"+currentEvent);
		currentEvent = -1;
	}
	public int getCurrentEvent(){
		return currentEvent;
	}
	
		
	public void handleInitialize(){
		if(currentEvent != mInitialEvent){
				hideCurrentWidgetDialog(currentEvent);
		}
		setCurrentEvent();
	}
		
	public boolean getNonInterruptStatus(){
		Log.i(TAG,"getNonInterruptStatus called:"+nonInterruptStatus);
		return nonInterruptStatus;
	}
	
	public void setNonInterruptStatus(final boolean status){
	Log.i(TAG,"setNonInterruptStatus called:"+status);
		
			if(status){
				setMMiDisable();
			} else {
				setMMIEnable();
			}
			nonInterruptStatus = status;
		
	}
	
	private void setMMIEnable(){
		Log.d(TAG,"setMMIEnable called:"+mSatInstaller);
		if(mSatInstaller != null){
			mSatInstaller.setMmiEnable();
		}
	}
	
	private void setMMiDisable(){
		Log.d(TAG,"setMMiDisable called:"+mSatInstaller);
		if(mSatInstaller != null){
			mSatInstaller.setMmiDisable();
		}
	}
	
	
	
	/*
	 * Displays corresponding dialog based on eventid
	 * @Params int eventId
	 */
	public void update(int eventId) {
		final int eventID = eventId;
		Log.i(TAG, "CIAUX update() called eventID:"+eventID);
		
			switch (eventID) {
			case EventIDs.CI_OPENTEXT_WIDGET:
				hideCurrentWidgetDialog(currentEvent);
				currentEvent = eventID;
				Log.i(TAG, "EventID:AUX displaytextWidget calling:"
						+ mSatInstaller);
				textWidget = new TextWidget(mContext, mSatInstaller,this);
				Log.i(TAG, "EventID: displaytextWidget calling");
				textWidget.displaytextWidget();
				break;
			case EventIDs.CI_OPENENQUIRY_WIDGET:
				hideCurrentWidgetDialog(currentEvent);
				currentEvent = eventID;
				enquiryWidget = new EnquiryWidget(mContext,
						mSatInstaller,this);
				Log.i(TAG, "EventID: displayEnquiryWidget calling:"
						+ mSatInstaller);
				enquiryWidget.displayEnquiryWidget();
				break;
			case EventIDs.CI_OPENLIST_WIDGET:
				if (currentEvent != eventID){
					hideCurrentWidgetDialog(currentEvent);
				listWidget = new ListWidget(mContext,
						mSatInstaller,this);
				}
				else if(currentEvent != eventID){
				listWidget = new ListWidget(mContext,
						mSatInstaller,this);
				}
				else {
				if(listWidget == null){
					listWidget = new ListWidget(mContext,
						mSatInstaller,this);
						}
				}
				Log.i(TAG, "CIMainWidget listwidget:" + mContext);
				currentEvent = eventID;
				listWidget.displayListWidget();
				break;
			case EventIDs.CI_OPENMENU_WIDGET:
				if (currentEvent != eventID){
								hideCurrentWidgetDialog(currentEvent);
							menuWidget = new MenuWidget(mContext,mSatInstaller,this);
					} else if(currentEvent != eventID){
					menuWidget = new MenuWidget(mContext,mSatInstaller,this);
					}
					else {
					if(menuWidget == null){
					menuWidget = new MenuWidget(mContext,mSatInstaller,this);
					}
					}
				currentEvent = eventID;
				Log.i(TAG, "CIMainWidget menuwidget:" + mContext);
				menuWidget.displayMenuWidget();
				break;
			case EventIDs.CI_INACTIVE_STATE:
				closeMMI();
			default:
				break;
			}
	}
	
		
	/*
	 * Closes the current displaying dialog
	 * @Params int currentWidget
	 */
	private void hideCurrentWidgetDialog(int currentWidget) {
	Log.i(TAG, "hideCurrentWidgetDialog called current Widget:"+currentWidget);
		switch (currentWidget) {
		case EventIDs.CI_OPENTEXT_WIDGET:
			Log.i(TAG, "hideCurrentWidgetDialog:"+textWidget);
			if (textWidget != null){
				textWidget.hideDialog();
			}
			break;
		case EventIDs.CI_OPENENQUIRY_WIDGET:
			Log.i(TAG, "hideCurrentWidgetDialog" + enquiryWidget);
			if (enquiryWidget != null){
				enquiryWidget.hideDialog();
			}
			break;
		case EventIDs.CI_OPENLIST_WIDGET:
			Log.i(TAG, "hideCurrentWidgetDialog" + listWidget);
			if (listWidget != null){
				listWidget.hideDialog();
			}
			break;
		case EventIDs.CI_OPENMENU_WIDGET:
			Log.i(TAG, "hideCurrentWidgetDialog" + menuWidget);
			if (menuWidget != null){
				menuWidget.hideDialog();
			}
			break;
		default:
			break;
		}
	}

	public void resetWidgetInstances(){
		currentEvent = -1;
		nonInterruptStatus = false;
		
	}
		

	public void closeMMI(){
		Log.i(TAG, "closeMMI called currentEvent:"+currentEvent);
	if(currentEvent != -1){
	switch (currentEvent) {
		case EventIDs.CI_OPENTEXT_WIDGET:
			Log.i(TAG, "Hiding TextWidget");
			if (textWidget != null)
				textWidget.closeWidget();
			break;
		case EventIDs.CI_OPENENQUIRY_WIDGET:
			Log.i(TAG, "Hiding EnquiryWidget:" + enquiryWidget);
			if (enquiryWidget != null)
				enquiryWidget.closeWidget();
			break;
		case EventIDs.CI_OPENLIST_WIDGET:
			Log.i(TAG, "Hiding ListWidget:" + listWidget);
			if (listWidget != null)
				listWidget.closeWidget();
			break;
		case EventIDs.CI_OPENMENU_WIDGET:
			Log.i(TAG, "Hiding MenuWidget:" + menuWidget);
			if (menuWidget != null)
				menuWidget.closeWidget();
			break;
		}
	  }
	}
	
	
}

