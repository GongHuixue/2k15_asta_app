package org.droidtv.euinstallersat.model.mwapi;

public class LnbSettingsEntry {

	public static final int LnbConnectionSingle = 0;
	public static final int LnbConnectionDiSeqcMini = 1;
	public static final int LnbConnectionDiSeqc1_0 = 2;
	public static final int LnbConnectionUnicableLnb = 3;
	public static final int LnbConnectionUnicableSwitch = 4;
	public static final int LnbConnectionSatIP = 5;
	
	public int	LnbType;
	public int	LnbStatus;
	public int	LowLoFreq;		/* For universal both low and high LO values are applicable. For single only low LO applicable */
	public int	HighLoFreq;
	public byte	ToneControl;
	public byte	LnbPower;
	public byte	UserBand;	/* Valid for Unicable */
	public int	UserBandFrequency;	/* Valid for Unicable */
	public int  SatelliteId;
	public boolean		UpdateInstallEnabled;
	
	LnbSettingsEntry(int lnbType,int lnbStatus,int lowLoFreq,int highLoFreq,byte toneControl,byte lnbPower,byte userBand,int userBandFrequency,int satelliteId,boolean updateInstallEnabled)
	{
		LnbType = lnbType;
		LnbStatus = lnbStatus;
		LowLoFreq = lowLoFreq;
		HighLoFreq = highLoFreq;
		ToneControl = toneControl;
		LnbPower = lnbPower;
		UserBand = userBand;
		UserBandFrequency = userBandFrequency;
		SatelliteId = satelliteId;
		UpdateInstallEnabled = updateInstallEnabled;
	}
}
