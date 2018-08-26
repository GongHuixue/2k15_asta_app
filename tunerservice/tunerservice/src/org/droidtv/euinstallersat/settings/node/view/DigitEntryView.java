package org.droidtv.euinstallersat.settings.node.view;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.settings.node.IViewListener;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.widget.RelativeLayout;

public class DigitEntryView extends RelativeLayout
{

	private static final String TAG = DigitEntryView.class.getName();
	public IViewListener mKeyListener;

	public DigitEntryView(Context context)
	{
		this(context, null, 0);
	}

	public DigitEntryView(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);

	}

	public DigitEntryView(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		loadLayout();
	}
	
	private void loadLayout()
	{
		LayoutInflater lInflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		lInflater.inflate(R.layout.ws_digit_entry_layout, this, true);

	}

	public void addListener(IViewListener argKeyListener)
	{
		mKeyListener = argKeyListener;
	}

	public void removeListener()
	{
		mKeyListener = null;
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		Log.d(TAG, "dispatchKeyEvent for RalativeLayoutView");
		Log.d(TAG, String.valueOf(event.getAction()));
		Boolean l_ret = false;

		if (mKeyListener != null)
		{
			l_ret = super.dispatchKeyEvent(event);
			if (l_ret == false)
			{
				l_ret = mKeyListener.handleKeyEvent(event);
			}
			return l_ret;
		} else
		{
			return super.dispatchKeyEvent(event);
		}
	}
}
