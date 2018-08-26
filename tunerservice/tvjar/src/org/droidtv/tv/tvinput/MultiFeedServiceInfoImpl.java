package org.droidtv.tv.tvinput;

import android.os.Parcel;

import android.os.Parcelable;
import android.os.Parcelable.Creator;
import org.droidtv.tv.tvinput.ITVTunerSession;
import android.os.Bundle;

/** @hide */
public class MultiFeedServiceInfoImpl extends ITVTunerSession.MultiFeedServiceInfo implements Parcelable{
	
	public MultiFeedServiceInfoImpl() 
	{
		System.out.println("ITvTunerSession.MultiFeedServiceInfo has been instantiated");
	}
	
	public MultiFeedServiceInfoImpl(String mId, Bundle mExtra)
	{
		this.mID = mId;
		this.mExtra = mExtra;
	}

	//@Override
	public int describeContents() {
		return 0;
	}

	public  static final Creator<MultiFeedServiceInfoImpl> CREATOR = new Creator<MultiFeedServiceInfoImpl>() {
		//@Override
		public MultiFeedServiceInfoImpl createFromParcel(final Parcel source) {
			MultiFeedServiceInfoImpl ep = new MultiFeedServiceInfoImpl();
			ep.readFromParcel(source);
			return ep;
		}


	//	@Override
		public MultiFeedServiceInfoImpl[] newArray(final int size) {
			return new MultiFeedServiceInfoImpl[size];
		}

	};		

	public void readFromParcel( Parcel p)
	{
		//fill once defined
		this.mID = p.readString();
		this.mExtra = p.readBundle();
		System.out.println("TvTunerSession.MultiFeedServiceInfo readFromParcel ");
	}

	//@Override
	public void writeToParcel(Parcel dest, int flags) {
		dest.writeString(mID);
		dest.writeBundle(mExtra);
		System.out.println("TvTunerSession.MultiFeedServiceInfoImpl writeToParcel");
	}
}
