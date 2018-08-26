package org.droidtv.euinstallertc.wizard.screen;

import java.util.Arrays;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.ui.tvwidget2k15.ColorKeys;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class LCNConflictScreenActivity extends Activity implements OnItemClickListener, OnItemSelectedListener
{

	private static final String TAG = LCNConflictScreenActivity.class.getName();
	private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
	private NotificationHandler ntf = NotificationHandler.getInstance();
	private Context mContext;
	private int[] mFocusChIdx_arr;
	private int mSelectedChNum = 0;

	private ListView lcnNumList;
	private ListView lcnChanList;
	
	private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		mContext = this;

		Log.d(TAG, "onCreate ");

		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		instActManager.addActivityToStack(this);
		
		setContentView(R.layout.lcn_conflict_layout);
		
		lcnNumList = (ListView) findViewById(R.id.lcn_numberlist);
		lcnChanList = (ListView) findViewById(R.id.lcn_channellist);

		String[] lcnNumListArray = nwrap.getConflictingChannelNumbers();
		
		int lNumChNumbers = lcnNumListArray.length;
		mFocusChIdx_arr = new int[lNumChNumbers];
		
		Arrays.fill(mFocusChIdx_arr, 0);
		mSelectedChNum = 0;
		
		lcnNumList.setChoiceMode(ListView.CHOICE_MODE_SINGLE );
		lcnNumList.setAdapter(new ArrayAdapter<String>(mContext, org.droidtv.ui.tvwidget2k15.R.layout.simple_list_item_activated_1, lcnNumListArray));
		lcnNumList.setOnItemSelectedListener(this);
		lcnNumList.setSelection(mSelectedChNum);
		//lcnNumList.setFocusable(true);
		lcnNumList.requestFocus();

		lcnChanList.setOnItemClickListener(this);
		// Color key handling
		final ColorKeys mColourKeyBar = (ColorKeys) findViewById(R.id.lcn_colorkeys);
		mColourKeyBar.setRedLabel(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_DONE));
		mColourKeyBar.setBlueLabel(null);
		mColourKeyBar.setGreenLabel(null);
		mColourKeyBar.setYellowLabel(null);
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		int keyCode = event.getKeyCode();
		int keyAction = event.getAction();
		boolean l_ret = false;
		switch(keyCode)
		{
			case KeyEvent.KEYCODE_PROG_RED:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					Log.d(TAG,"LCN Selection Done");
					nwrap.lcnSelectionDone(true);
					finish();
				}
				break;
			case KeyEvent.KEYCODE_BACK:
			case KeyEvent.KEYCODE_ESCAPE:
				if (keyAction == KeyEvent.ACTION_DOWN)
				{
					Log.d(TAG,"LCN Selection Cancelled");
					nwrap.lcnSelectionDone(false);
				}
				break;
			case KeyEvent.KEYCODE_PROG_BLUE:
				l_ret = true;
				break;
			case KeyEvent.KEYCODE_DPAD_LEFT:
			case KeyEvent.KEYCODE_SOFT_LEFT:
				if (lcnChanList.isFocused())
				{
					lcnNumList.setSelection(mSelectedChNum);
					lcnNumList.requestFocus();
					lcnNumList.getSelectedView().setSelected(false);
				}
				break;
			case KeyEvent.KEYCODE_DPAD_RIGHT:
			case KeyEvent.KEYCODE_SOFT_RIGHT:
				Log.d(TAG,"KEYCODE_DPAD_RIGHT "+ lcnNumList.isFocused());
				if (lcnNumList.isFocused()){
					
					//lcnNumList.setSelection(mSelectedChNum);
					//lcnNumList.setItemChecked(mSelectedChNum, true);
					lcnNumList.performItemClick(lcnNumList, mSelectedChNum, lcnNumList.getItemIdAtPosition(mSelectedChNum));
					
					//lcnNumList.performClick();
					lcnChanList.requestFocus();
				}
				break;
			default:
				break;
			
		}
		if(!l_ret)
		{
			l_ret = super.dispatchKeyEvent(event);
		}
		
		// black android from handling by default
		l_ret = true;
		return l_ret;
		
	}

	@Override
	public void onItemClick(AdapterView<?> p_listView, View p_view, int p_selItem, long arg3)
	{
		Log.d(TAG, "onItemClick for name list mSelectedChNum = " + mSelectedChNum);
		Log.d(TAG, "onItemClick for name list p_selItem = " + p_selItem);
		mFocusChIdx_arr[mSelectedChNum] = p_selItem;
		nwrap.setConflictingChannelNames(p_selItem);
		
		lcnNumList.setItemChecked(mSelectedChNum, true);
	}

	@Override
	public void onItemSelected(AdapterView<?> p_listView, View p_view, int p_selItem, long arg3)
	{
		int l_viewIdx;
		if (p_listView.getId() == lcnNumList.getId())
		{
			Log.d(TAG, "onItemSelected for number list");
			updateChannelList(p_selItem);
			l_viewIdx = p_selItem-1;
			if(l_viewIdx < 0)
			{
				l_viewIdx = 0;
			}
			lcnChanList.setItemChecked(mFocusChIdx_arr[mSelectedChNum], true);
			
			lcnNumList.setSelection(p_selItem);
		}
	}

	@Override
	public void finish() {
		super.finish();
		overridePendingTransition(0, 0);
	}
	
	@Override
	public void onNothingSelected(AdapterView<?> arg0)
	{
		// TODO Auto-generated method stub

	}
	
	private void updateChannelList(int p_selItem)
	{
		Log.d(TAG,"updating channel list");
		nwrap.setConflictingChannelNumbers(p_selItem);
		mSelectedChNum = p_selItem;
		// update sub list
		lcnChanList.setAdapter(new ArrayAdapter<String>(mContext, org.droidtv.ui.tvwidget2k15.R.layout.simple_list_item_activated_1, nwrap
				.getConflictingChannelNames(p_selItem)));
		lcnChanList.setChoiceMode(AbsListView.CHOICE_MODE_SINGLE );
		
		Log.d(TAG, "Current selection = " + mFocusChIdx_arr[mSelectedChNum]);
		lcnChanList.setSelection(mFocusChIdx_arr[mSelectedChNum]);
		
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		Log.d(TAG, "onResume");
	}
	
	@Override
	protected void onPause() {
		Log.d(TAG, "onPause");
		if(isFinishing()){
		   Log.d(TAG, "onPause & the reason is activity is finishing");
		}
		super.onPause();
	}

	@Override
	protected void onStop() {
		super.onStop();
		Log.d(TAG, "onStop");
		
	}

	@Override
	protected void onDestroy() {
		Log.d(TAG, "onDestroy");
		instActManager.removeActivityFromStack(this);
		super.onDestroy();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Log.d(TAG, "onRestart");
	}

}
