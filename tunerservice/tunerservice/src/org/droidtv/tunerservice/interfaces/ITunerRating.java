package org.droidtv.tunerservice.interfaces;
import android.content.Context;

public interface ITunerRating {
	abstract void enableRating();
	abstract void setParentalRating();
	abstract void setDefaultRating();
	abstract void setContext(Context context);
}
