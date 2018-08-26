package org.droidtv.tv.tvinput;
import android.os.IBinder;
import java.util.List;
import org.droidtv.tv.tvinput.ClonechannelParam;
import org.droidtv.tv.tvinput.ClonechannelCallBack;
interface Clonechannel
{
	void installCloneChannelApi(String type, in ClonechannelParam param, boolean islast );
	void registerCallback(ClonechannelCallBack callback);
	void setCursorId(boolean copyFromUSB, long cursorId);
	void installJapitCh();
}
