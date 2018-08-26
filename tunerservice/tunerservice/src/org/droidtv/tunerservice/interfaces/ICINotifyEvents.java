package org.droidtv.tunerservice.interfaces;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;


public interface ICINotifyEvents {
	abstract void notifyChannelInstallStatus(boolean status,Medium medium);
}