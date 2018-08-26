package org.droidtv.euinstallersat.settings;

public interface IDataChangeListener
{
	public void showNotification(int p_notificationStringId);
	public void showDialog(int p_msgStringId);
	public void onControllabilityChanged(int p_nodeId, boolean p_isControllable);

}
