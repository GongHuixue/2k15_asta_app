package org.droidtv.euinstallersat.model.notification;

public class NotificationInfoObject
{
	public int actionID;
	public String message;
	public int value = 0;

	public NotificationInfoObject(int actionID, String message)
	{
		this.actionID = actionID;
		this.message = message;
	}
	
	public void setValue(int p_value)
	{
		value = p_value;
	}
}
