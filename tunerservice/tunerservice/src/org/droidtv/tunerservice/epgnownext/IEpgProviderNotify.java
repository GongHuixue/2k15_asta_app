package org.droidtv.tunerservice.epgnownext;

public interface IEpgProviderNotify   {

	public void onEpgDataChanged(int presetID);
	public void onEpgModeChanged();
}
