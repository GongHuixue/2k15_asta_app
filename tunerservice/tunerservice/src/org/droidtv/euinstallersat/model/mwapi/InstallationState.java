package org.droidtv.euinstallersat.model.mwapi;


public class InstallationState{
	public int mode;
	public int state;
	public boolean retVal;

	public InstallationState()
	{
	}
	public InstallationState(int param1,int param2,boolean param3)
	{
		this.mode = param1;
		this.state = param2;
		this.retVal = param3;
	}
}