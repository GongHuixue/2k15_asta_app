package org.droidtv.euinstallertc.model.mwapi;

import android.util.Log;

public class SigStrengthRange
{
	public boolean result;
	public int min;
	public int max;
	private static final String TAG = "SigStrengthRange";

	public SigStrengthRange(boolean param1,int param2,int param3)
	{
		result = param1;
		max = param2;
		min = param3;
		Log.d(TAG, "result=" + result);
		Log.d(TAG, "max=" + max);
		Log.d(TAG, "min=" + min);
	}
	
	public SigStrengthRange()
	{

	}
}