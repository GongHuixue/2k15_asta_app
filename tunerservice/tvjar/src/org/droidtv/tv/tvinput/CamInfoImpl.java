package org.droidtv.tv.tvinput;

import android.os.Parcel;
import android.os.Parcelable;
import android.os.Parcelable.Creator;
import org.droidtv.tv.tvinput.ITVCIControl;

/** @hide */
public class CamInfoImpl extends ITVCIControl.CamInfo implements Parcelable{
	public CamInfoImpl() 
	{
		System.out.println("CamInfo has been instantiated");
	}

	public CamInfoImpl(ITVCIControl.CamInfo caminfo) 
	{
		slotId		= caminfo.slotId;
		camID		= caminfo.camID;
		camStatus 	= caminfo.camStatus;
		medium 		= caminfo.medium;
		isPremium	= caminfo.isPremium;
		packageId 	= caminfo.packageId;
	}
	
	public int describeContents() {
		return 0;
	}

	public  static final Creator<CamInfoImpl> CREATOR = new Creator<CamInfoImpl>() {

		public CamInfoImpl createFromParcel(final Parcel source) {
			CamInfoImpl ep = new CamInfoImpl();
			ep.readFromParcel(source);
			return ep;
		}

		public CamInfoImpl[] newArray(final int size) {
			return new CamInfoImpl[size];
		}

	};		

	public void readFromParcel( Parcel p)
	{
		this.slotId		= p.readInt();
		this.camID		= p.readString();
		this.camStatus 	= (p.readByte()==1);;
		this.medium 	= p.readString();
		this.isPremium	= (p.readByte()==1);
		this.packageId 	= p.readInt();
	}

	public void writeToParcel(Parcel dest, int flags) {
		
		dest.writeInt(slotId);
		dest.writeString(camID);
		dest.writeByte((byte)(camStatus ? 1:0));
		dest.writeString(medium);
		dest.writeByte((byte)(isPremium ? 1:0));
		dest.writeInt(packageId);
	}
}