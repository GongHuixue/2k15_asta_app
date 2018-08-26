package org.droidtv.tunerservice.interfaces;

public interface IPlayTvMPLFactoryCallback {
	boolean onAvailable(int clientType);
	boolean onNotAvailable(int clientType);
	void onOlympicUsecaseUpdate(boolean enable,boolean isOTR);
}
