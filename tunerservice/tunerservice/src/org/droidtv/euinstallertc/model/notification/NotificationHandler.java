package org.droidtv.euinstallertc.model.notification;

import java.util.Observable;
import java.util.Observer;

public class NotificationHandler extends Observable {
	// single instance holder
	private static volatile NotificationHandler singletonInstance = null;

	// private constructor
	private NotificationHandler(){}

	// get single instance of NotificationHandler class
	public synchronized static NotificationHandler getInstance(){
		if(singletonInstance == null){
			singletonInstance = new NotificationHandler();
		}
		return singletonInstance;
	}

	public void registerForNotification(Observer obs){
		this.addObserver(obs);
	}

	public void unregisterForNotification(Observer obs){
		this.deleteObserver(obs);
	}

	public synchronized void notifyAllObservers(final int actionID, final String message){
		this.setChanged(); // important call to trigger all notifications
		// notify all using separate thread otherwise if one observer update takes time whole UI hangs
		/*new Thread(new Runnable() {

			@Override
			public void run() {
				singletonInstance.notifyObservers(new NotificationInfoObject(actionID, message));				
			}
			
		}).start();		*/
		singletonInstance.notifyObservers(new NotificationInfoObject(actionID, message));
	}

	public void removeAllObservers(){
		// remove all the observers, clear up
		this.deleteObservers();
	}
}
