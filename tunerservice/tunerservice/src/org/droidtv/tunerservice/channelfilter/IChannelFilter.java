package org.droidtv.tunerservice.channelfilter;

import android.net.Uri;

public interface IChannelFilter {
	
	public Uri getNextUri(Uri uri);
	public Uri getPrevUri(Uri uri);

}
