package org.droidtv.euinstallersat.model.notification;

import java.util.Observable;
import java.util.Observer;

public class NotificationHandler extends Observable
{

	private static volatile NotificationHandler mNotificationHandler;

	private NotificationHandler()
	{
	}

	public synchronized static NotificationHandler getInstance()
	{
		if (mNotificationHandler == null)
		{
			mNotificationHandler = new NotificationHandler();
		}
		return mNotificationHandler;
	}

	public void registerForNotification(Observer observer)
	{
		addObserver(observer);
	}

	public void unRegisterForNotification(Observer observer)
	{
		deleteObserver(observer);
	}

	public synchronized void notifyAllObservers(final int actionID, final String message)
	{
		setChanged();
		mNotificationHandler.notifyObservers(new NotificationInfoObject(actionID, message));
	}

	public void removeAllObservers()
	{
		deleteObservers();
	}

}
