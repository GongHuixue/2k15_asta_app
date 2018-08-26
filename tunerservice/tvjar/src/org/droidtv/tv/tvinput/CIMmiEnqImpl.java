package org.droidtv.tv.tvinput;

import android.os.Parcel;
import android.os.Parcelable;
import android.os.Parcelable.Creator;
import org.droidtv.tv.tvinput.ITVCIControl;

/** @hide */
public class CIMmiEnqImpl extends ITVCIControl.CIMmiEnq implements Parcelable{
	public CIMmiEnqImpl() 
	{
		System.out.println("CamInfo has been instantiated");
	}
	
	
	public CIMmiEnqImpl(ITVCIControl.CIMmiEnq ciMmiEnq){
		this.isVisible		= ciMmiEnq.isVisible;
		this.answerLength 	= ciMmiEnq.answerLength;
		this.promptText 	= ciMmiEnq.promptText;
	}
	
	public int describeContents() {
		return 0;
	}

	public  static final Creator<CIMmiEnqImpl> CREATOR = new Creator<CIMmiEnqImpl>() {
		public CIMmiEnqImpl createFromParcel(final Parcel source) {
			CIMmiEnqImpl ep = new CIMmiEnqImpl();
			ep.readFromParcel(source);
			return ep;
		}

		public CIMmiEnqImpl[] newArray(final int size) {
			return new CIMmiEnqImpl[size];
		}

	};		

	public void readFromParcel( Parcel p) {
		this.isVisible		= (p.readByte()==1);
		this.answerLength 	= p.readInt();
		this.promptText 	= p.readString();
	}

	public void writeToParcel(Parcel dest, int flags) {		
		dest.writeByte((byte)(isVisible ? 1:0));
		dest.writeInt(answerLength);
		dest.writeString(promptText);	
	}
}