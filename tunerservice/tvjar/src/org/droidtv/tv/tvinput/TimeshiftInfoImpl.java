package org.droidtv.tv.tvinput;

import android.os.Parcel;
import android.os.Parcelable;
import android.os.Parcelable.Creator;
import org.droidtv.tv.tvinput.ITVTunerSession;

/** @hide */
public class TimeshiftInfoImpl extends ITVTunerSession.TimeshiftInfo implements Parcelable{
	public TimeshiftInfoImpl() 
	{
		System.out.println("TimeshiftInfoImpl has been instantiated");
	}

	public TimeshiftInfoImpl(ITVTunerSession.TimeshiftInfo timeshiftinfo) 
	{
		eventName		= timeshiftinfo.eventName;
		shortInfo 		= timeshiftinfo.shortInfo;
		extendedInfo	= timeshiftinfo.extendedInfo;
		guidanceInfo 	= timeshiftinfo.guidanceInfo;
		channelId		= timeshiftinfo.channelId;
		genre			= timeshiftinfo.genre;
		rating			= timeshiftinfo.rating;
	}
	
	public int describeContents() {
		return 0;
	}

	public  static final Creator<TimeshiftInfoImpl> CREATOR = new Creator<TimeshiftInfoImpl>() {

		public TimeshiftInfoImpl createFromParcel(final Parcel source) {
			TimeshiftInfoImpl ep = new TimeshiftInfoImpl();
			ep.readFromParcel(source);
			return ep;
		}

		public TimeshiftInfoImpl[] newArray(final int size) {
			return new TimeshiftInfoImpl[size];
		}

	};		

	public void readFromParcel( Parcel p)
	{
		this.eventName		= p.readString();
		this.shortInfo 		= p.readString();
		this.extendedInfo	= p.readString();
		this.guidanceInfo	= p.readString();
		this.channelId		= p.readInt();
		this.genre			= p.readInt();
		this.rating			= p.readInt();
	}

	public void writeToParcel(Parcel dest, int flags) {
		dest.writeString(eventName);
		dest.writeString(shortInfo);
		dest.writeString(extendedInfo);
		dest.writeString(guidanceInfo);
		dest.writeInt(channelId);
		dest.writeInt(genre);
		dest.writeInt(rating);
	}
}