package org.droidtv.euinstallertc.util;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;

public class NotificationCenterMessage {

	private Context ctx;
	public static final int TC_INSTALLER_NOTIFICATION_ID = 7777;
	
	public void showChannelUpdateMessage(Context argCtx, String title,String message) {
		ctx = argCtx;

		NotificationManager notificationManager = (NotificationManager) argCtx.getApplicationContext().getSystemService(Context.NOTIFICATION_SERVICE);

		Intent intent = new Intent();
		PendingIntent pIntent = PendingIntent.getActivity(ctx, 0, intent, PendingIntent.FLAG_ONE_SHOT);

		Notification notification = new Notification.Builder(ctx)
				.setContentTitle(title)
				.setSmallIcon(org.droidtv.ui.tvwidget2k15.R.drawable.play_tv_ico_72x72)
				.setContentIntent(pIntent)
				/*.setContentText(message)*/
				.setStyle(new Notification.BigTextStyle().bigText(message))
				.setAutoCancel(true).build();

		// Will show lights and make the notification disappear when the presses it
		notification.flags |= Notification.FLAG_AUTO_CANCEL| Notification.FLAG_SHOW_LIGHTS;
		
		notificationManager.notify(TC_INSTALLER_NOTIFICATION_ID, notification);
	}
}
