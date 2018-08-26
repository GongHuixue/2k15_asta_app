package org.droidtv.euinstallersat.model.mwapi;

import java.util.Arrays;

public class HsvInstalledSatellites
{
	public int NumberOfLnbs;
	public SatelliteDetails[] SatInfo;
	public int retVal;


	public HsvInstalledSatellites()
	{
	}

	public HsvInstalledSatellites(int param1, SatelliteDetails[] param2,int param3)
	{
		this.NumberOfLnbs = param1;
		this.SatInfo = Arrays.copyOf(param2, param2.length);
		this.retVal = param3;
	}
}