package org.droidtv.euinstallersat.wizard.util;

import java.util.ArrayList;



/* This class is a UI class and is 
 * solely for passing data between the installation and finish 
 * wizard screens
 * 
 */
public class InstalledLNBCache
{
	private static InstalledLNBCache m_instance = null;
	private ArrayList<LNBInfo> m_LNBInfoArray;
	
	public static int INSTALLATION_SUCCESS = 0;
	public static int INSTALLATION_FAILURE = 1;
	private int m_installState = INSTALLATION_SUCCESS;
	
	private InstalledLNBCache(){
		m_LNBInfoArray = new ArrayList<LNBInfo>();
	}
	
	public static InstalledLNBCache getInstance() {
		if (m_instance == null) {
			m_instance = new InstalledLNBCache();
		}
		return m_instance;
	}
	
	public void emptyCache()
	{
		m_installState = INSTALLATION_SUCCESS;
		m_LNBInfoArray.clear();
	}
	
	public void addItem(LNBInfo p_lnbInfo)
	{
		LNBInfo l_clonedObj = null;
		try
		{
			l_clonedObj = (LNBInfo)p_lnbInfo.clone();
		} catch (CloneNotSupportedException e)
		{
			e.printStackTrace();
		}
		m_LNBInfoArray.add(l_clonedObj);
	}
	
	public int getSize()
	{
		return m_LNBInfoArray.size();
	}
	
	public LNBInfo getItemAtIndex(int p_idx)
	{
		if(p_idx >= m_LNBInfoArray.size())
		{
			p_idx = 0;
		}
		return m_LNBInfoArray.get(p_idx);
	}
	
	public void setInstallationState(int p_installState)
	{
		m_installState = p_installState;
	}
	
	public int getInstallationState()
	{
		return m_installState;
	}
}
