package org.droidtv.euinstallersat.model.mwapi;

import java.util.Arrays;

public class SatelliteDetails
{
	public int LnbType;
	public int LnbNumber;
	public boolean IsLnbFree;
	public boolean IsServicesScanComplete;
	public short[] SatelliteName;

	public SatelliteDetails()
	{
	}

	public SatelliteDetails(int param1,int param2,boolean param3,boolean param4,short[] param5)
	{
		this.LnbType = param1;
		this.LnbNumber = param2;
		this.IsLnbFree = param3;
		this.IsServicesScanComplete = param4;
		this.SatelliteName = Arrays.copyOf(param5, param5.length);
	}
}