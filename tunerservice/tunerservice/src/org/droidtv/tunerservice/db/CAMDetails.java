package org.droidtv.tunerservice.db;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
//import org.droidtv.playtv.ci.CIApplication;
import java.util.Arrays;

public class CAMDetails {

	public static final String TCINSTALLMEDIUM = "tcmedium";
	public static final String SATINSTALLMEDIUM = "satmedium";
	public static final String UNKNOWNMEDIUM = "unknownmedium";
	private String camID;
	private int slotID;
	private String medium;
	private boolean camStatus;
	private byte[] camIDBlob;
	
	public byte[] getCamIDBlob() {
		return camIDBlob;
	}
	public void setCamIDBlob(byte[] lcamIDBlob) {
		if(lcamIDBlob!=null){
			camIDBlob = Arrays.copyOf(lcamIDBlob,lcamIDBlob.length);
		}
		else{
			camIDBlob=null;
		}
	}
	
	public String getCamID() {
		return camID;
	}
	public void setCamID(String camID) {
		this.camID = camID;
	}
	public int getSlotID() {
		return slotID;
	}
	public void setSlotID(int slotID) {
		this.slotID = slotID;
	}
	public String getMedium() {
		return medium;
	}
	public void setMedium(String medium) {
		this.medium = medium;
	}
	public void setMedium(Medium medium) {
		if( (medium==Medium.MEDIUM_CABLE) || (medium==Medium.MEDIUM_TERRESTRIAL)) {
			this.medium = TCINSTALLMEDIUM; 
		}
		else if(medium==Medium.MEDIUM_SATELLITE) {
			this.medium = SATINSTALLMEDIUM; 
		}
		else {
			this.medium = UNKNOWNMEDIUM; 
		}		
	}
	public boolean isCamStatus() {
		return camStatus;
	}
	public void setCamStatus(boolean camStatus) {
		this.camStatus = camStatus;
	}
}
