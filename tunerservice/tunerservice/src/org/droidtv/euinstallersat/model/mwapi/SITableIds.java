
package org.droidtv.euinstallersat.model.mwapi;


public class SITableIds
{
	public short NetworkID;
	public short BouquetID;
	public int retVal;

	public SITableIds()
	{
		
	}

	public SITableIds(short param1,short param2,int param3)
	{
		this.NetworkID = param1;
		this.BouquetID = param2;
		this.retVal = param3;
	}
}