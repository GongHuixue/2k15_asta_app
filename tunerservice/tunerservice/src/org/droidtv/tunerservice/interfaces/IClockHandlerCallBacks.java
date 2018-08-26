package org.droidtv.tunerservice.interfaces;

import android.net.Uri;
public interface IClockHandlerCallBacks {
	
	public static final int RESULT_SUCCESS_TDT	= 1;
	public static final int RESULT_SUCCESS_TOT  = 2;
	public static final int RESULT_TIMEOUT 		= 3;
	public static final int RESULT_FAILED 		= 4;
	
	abstract void OnClockSetResult(Uri uri, int result);//min.jiang modify 2015-07-09	
}
