package org.droidtv.euinstallersat.settings.node.view;

import org.droidtv.euinstallersat.settings.node.IViewListener;
import org.droidtv.tunerservice.R;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.widget.RelativeLayout;

public class DTRView extends RelativeLayout
{

	private static final String TAG = "DTRView";
	public IViewListener m_keyListener;

	public DTRView(Context context)
	{
		this(context, null, 0);

	}

	public DTRView(Context context, AttributeSet attrs)
	{
		this(context, attrs, 0);

	}

	public DTRView(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		loadLayout();

	}

	private void loadLayout()
	{
		LayoutInflater lInflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		lInflater.inflate(R.layout.satellite_dtr_layout, this, true);

	}

	public void addListener(IViewListener p_keyListener)
	{
		m_keyListener = p_keyListener;
	}

	public void removeListener()
	{
		m_keyListener = null;
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
	    Log.d(TAG, "dispatchKeyEvent for the DTR screen");
        Log.d(TAG, String.valueOf(event.getAction()));
        Boolean l_ret = false;

        if (m_keyListener != null) {
            l_ret = super.dispatchKeyEvent(event);
            if (l_ret == false) {
                l_ret = m_keyListener.handleKeyEvent(event);
            };
            return l_ret;
        } else {
            return super.dispatchKeyEvent(event);
        }
	}
}
