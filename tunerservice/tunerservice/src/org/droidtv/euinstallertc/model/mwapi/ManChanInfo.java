package org.droidtv.euinstallertc.model.mwapi;

import android.util.Log;


public class ManChanInfo
{
   public int   channel;
   public boolean  finetune;
   private static final String TAG = "ManChanInfo";

	public ManChanInfo ()
 	{

	}
 	public ManChanInfo (int param1, boolean param2)
 	{
 		channel = param1;
 		finetune = param2;
 		Log.d(TAG, "channel=" + channel);
 		Log.d(TAG, "finetune=" + finetune);
	}
}