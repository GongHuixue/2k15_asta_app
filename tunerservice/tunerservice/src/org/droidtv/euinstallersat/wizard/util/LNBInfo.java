package org.droidtv.euinstallersat.wizard.util;

public class LNBInfo implements Cloneable
{
	public String m_name = "";
	public int m_tvChannelsAdded = 0;
	public int m_tvChannelsRemoved = 0;
	public int m_radioChannelsAdded = 0;
	public int m_radioChannelsRemoved = 0;
	public int m_lnbIdx = 0;
	
	@Override
	protected Object clone() throws CloneNotSupportedException
	{
		return super.clone();
	}
}
