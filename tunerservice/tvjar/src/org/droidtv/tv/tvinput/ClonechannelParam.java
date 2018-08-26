package org.droidtv.tv.tvinput;
import android.os.Parcel;
import android.os.Parcelable;
import android.os.Parcelable.Creator;

/** @hide */
public class ClonechannelParam implements Parcelable{
	private String 	MediumType;
	private int 	Frequency;
	private int       SystemType;
	private String 	ServiceId;
	
	private String 	ONID;
	private String 	TSID;
	private int 	ModulationType;
	private int 	SymbolRate;
	private int 	Bandwidth;
	private String 	ServiceType;

	private String Url;
	private String SoureType;

	private String   PresetNumber;
	private String   Name;
	private String 	 Blank;
	private String   Skip;
	private String   FreePKG;
	private String   PayPKG1;
	private String   PayPKG2;
	private String   LogoURL;
	private String TTV1_ORDER;
	private String TTV2_ORDER;
	private String TTV3_ORDER;
	private String TTV4_ORDER;
	private String TTV5_ORDER;
	private String TTV6_ORDER;
	private String TTV7_ORDER;
	private String TTV8_ORDER;
	private String TTV9_ORDER;
	private String TTV10_ORDER;

	public ClonechannelParam() 
	{
		
	}

	public void setMediumType(String type)
	{
		this.MediumType = type;
	}

	public void setFrequency(int frequency)
	{
		this.Frequency = frequency;
	}
	public void setSystemType(int type)
	{
		this.SystemType = type;
	}
	public void setServiceId(String id)
	{
		this.ServiceId = id;
	}
	public void setONID(String id)
	{
		this.ONID = id;
	}
	public void setTSID(String id)
	{
		this.TSID = id;
	}
	public void setModulationType(int type)
	{
		this.ModulationType = type;
	}
	public void setSymbolRate(int rate)
	{
		this.SymbolRate = rate;
	}
	public void setBandwidth(int bandwidth)
	{
		this.Bandwidth = bandwidth;
	}
	public void setServiceType(String type)
	{
		this.ServiceType = type;
	}
	public void seturl(String url)
	{
		this.Url = url;
	}
	public void setSoureType(String type)
	{
		this.SoureType = type;
	}
	public void setPresetNumber(String number)
	{
		this.PresetNumber = number;
	}
	public void setName(String name)
	{
		this.Name = name;
	}
	public void setBlank(String blank)
	{
		this.Blank = blank;
	}
	public void setSkip(String skip)
	{
		this.Skip = skip;
	}
	public void setFreePKG(String type)
	{
		this.FreePKG = type;
	}
	public void setPayPKG1(String type)
	{
		this.PayPKG1 = type;
	}
	public void setPayPKG2(String type)
	{
		this.PayPKG2 = type;
	}
	public void setLogoURL(String logo)
	{
		this.LogoURL = logo;
	}
	public void setTTV1order(String order)
	{
		this.TTV1_ORDER = order;
	}
	public void setTTV2order(String order)
	{
		this.TTV2_ORDER = order;
	}
	public void setTTV3order(String order)
	{
		this.TTV3_ORDER = order;
	}
	public void setTTV4order(String order)
	{
		this.TTV4_ORDER = order;
	}
	public void setTTV5order(String order)
	{
		this.TTV5_ORDER = order;
	}
	public void setTTV6order(String order)
	{
		this.TTV6_ORDER = order;
	}
	public void setTTV7order(String order)
	{
		this.TTV7_ORDER = order;
	}
	public void setTTV8order(String order)
	{
		this.TTV8_ORDER = order;
	}
	public void setTTV9order(String order)
	{
		this.TTV9_ORDER = order;
	}
	public void setTTV10order(String order)
	{
		this.TTV10_ORDER = order;
	}
	
	
	public String getMediumType()
	{
		return MediumType;
	}

	public int getFrequency()
	{
		return Frequency ;
	}
	public int getSystemType()
	{
		return SystemType;
	}
	public String getServiceId()
	{
		return ServiceId ;
	}
	public String getONID()
	{
		return ONID;
	}
	public String getTSID()
	{
		return TSID;
	}
	public int getModulationType()
	{
		return ModulationType;
	}
	public int getSymbolRate()
	{
		return SymbolRate;
	}
	public int getBandwidth()
	{
		return Bandwidth;
	}
	public String getServiceType()
	{
		return ServiceType;
	}
	public String geturl()
	{
		return Url ;
	}
	public String getSoureType()
	{
		return SoureType;
	}
	public String getPresetNumber()
	{
		return PresetNumber ;
	}
	public String getName()
	{
		return Name;
	}
	public String getBlank()
	{
		return Blank;
	}
	public String getSkip()
	{
		return Skip;
	}
	public String getFreePKG()
	{
		return FreePKG;
	}
	public String getPayPKG1()
	{
		return PayPKG1;
	}
	public String getPayPKG2()
	{
		return PayPKG2;
	}
	public String getLogoURL()
	{
		return LogoURL;
	}
	public String getTTV1order()
	{
		return TTV1_ORDER;
	}
	public String getTTV2order()
	{
		return TTV2_ORDER;
	}
	public String getTTV3order()
	{
		return TTV3_ORDER;
	}
	public String getTTV4order()
	{
		return TTV4_ORDER;
	}
	public String getTTV5order()
	{
		return TTV5_ORDER;
	}
	public String getTTV6order()
	{
		return TTV6_ORDER;
	}
	public String getTTV7order()
	{
		return TTV7_ORDER;
	}
	public String getTTV8order()
	{
		return TTV8_ORDER;
	}
	public String getTTV9order()
	{
		return TTV9_ORDER;
	}
	public String getTTV10order()
	{
		return TTV10_ORDER;
	}
	
	
	public int describeContents() {
		return 0;
	}

	public  static final Creator<ClonechannelParam> CREATOR = new Creator<ClonechannelParam>() {

		public ClonechannelParam createFromParcel(final Parcel source) {
			ClonechannelParam ep = new ClonechannelParam();
			ep.readFromParcel(source);
			return ep;
		}

		public ClonechannelParam[] newArray(final int size) {
			return new ClonechannelParam[size];
		}

	};		

	public void readFromParcel( Parcel p)
	{
		this.MediumType		= p.readString();
		this.Frequency 		= p.readInt();
		this.SystemType	= p.readInt();
		this.ServiceId	= p.readString();
		this.ONID		= p.readString();
		this.TSID			= p.readString();
		this.ModulationType			= p.readInt();
		this.SymbolRate			= p.readInt();
		this.Bandwidth			= p.readInt();
		this.ServiceType		= p.readString();
		this.Url = p.readString();
		this.SoureType		= p.readString();
		this.PresetNumber		= p.readString();
		this.Name		= p.readString();
		this.Blank		= p.readString();
		this.Skip		= p.readString();
		this.FreePKG		= p.readString();
		this.PayPKG1		= p.readString();
		this.PayPKG2		= p.readString();
		this.LogoURL		= p.readString();
		this.TTV1_ORDER		= p.readString();
		this.TTV2_ORDER		= p.readString();
		this.TTV3_ORDER		= p.readString();
		this.TTV4_ORDER		= p.readString();
		this.TTV5_ORDER		= p.readString();
		this.TTV6_ORDER		= p.readString();
		this.TTV7_ORDER		= p.readString();
		this.TTV8_ORDER		= p.readString();
		this.TTV9_ORDER		= p.readString();
		this.TTV10_ORDER		= p.readString();
		
	}

	public void writeToParcel(Parcel dest, int flags) {
		dest.writeString(MediumType);
		dest.writeInt(Frequency);
		dest.writeInt(SystemType);
		dest.writeString(ServiceId);
		dest.writeString(ONID);
		dest.writeString(TSID);
		dest.writeInt(ModulationType);
		dest.writeInt(SymbolRate);
		dest.writeInt(Bandwidth);
		dest.writeString(ServiceType);
		dest.writeString(Url);
		dest.writeString(SoureType);
		dest.writeString(PresetNumber);
		dest.writeString(Name);
		dest.writeString(Blank);
		dest.writeString(Skip);
		dest.writeString(FreePKG);
		dest.writeString(PayPKG1);
		dest.writeString(PayPKG2);
		dest.writeString(LogoURL);
		dest.writeString(TTV1_ORDER);
		dest.writeString(TTV2_ORDER);
		dest.writeString(TTV3_ORDER);
		dest.writeString(TTV4_ORDER);
		dest.writeString(TTV5_ORDER);
		dest.writeString(TTV6_ORDER);
		dest.writeString(TTV7_ORDER);
		dest.writeString(TTV8_ORDER);
		dest.writeString(TTV9_ORDER);
		dest.writeString(TTV10_ORDER);
	}
}