package org.droidtv.euinstallersat.model.mwapi;


public class HsvSDMSIDataValues
{
	public short Pid;
	public short TableId;
	public short BouquetId;
	public short FreesatPostCodeTableType;

	public HsvSDMSIDataValues()
	{

	}

	public HsvSDMSIDataValues(short param1,short param2, short param3,short param4)
	{
		this.Pid = param1;
		this.TableId = param2;
		this.BouquetId = param3;
		this.FreesatPostCodeTableType = param4;
	}
}