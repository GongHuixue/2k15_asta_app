package org.droidtv.euinstallersat.util;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.widget.ImageView;

public class SignalIndicatorView extends ImageView
{
	private int[] m_resIdArray;
	private int[] m_valueArray;
	
	private static final String TAG = "SignalIndicatorView";
	
	 /**
     * @param context
     */
	public SignalIndicatorView(Context context)
	{
		super(context);
	}
	
	
    

    /**
     * @param context
     * @param attrs
     */
    public SignalIndicatorView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        // TODO Auto-generated constructor stub
    }

    /**
     * @param context
     * @param attrs
     * @param defStyle
     */
    public SignalIndicatorView(Context context, AttributeSet attrs, int defStyle)
    {
        super(context, attrs, defStyle);
        // TODO Auto-generated constructor stub
    }
	
	public void init(int[] p_resIdArray, int[] p_valueArray)
	{
		m_resIdArray = p_resIdArray.clone();
		m_valueArray = p_valueArray.clone();
	}
	
	public void setValue(int p_value)
	{
		Log.d(TAG, "setValue entry");
		int l_idx = 0;
		int l_numItems = m_valueArray.length;
		while((p_value > m_valueArray[l_idx]) && (l_idx < (l_numItems-1)))
		{
			Log.d(TAG, "l_idx = "+ String.valueOf(l_idx));
			l_idx++;
		}
		Log.d(TAG, "showing image with index "+ String.valueOf(l_idx));
		setImageResource(m_resIdArray[l_idx]);
	}

}
