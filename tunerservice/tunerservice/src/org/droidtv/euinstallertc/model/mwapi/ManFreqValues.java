package org.droidtv.euinstallertc.model.mwapi;

public class ManFreqValues
{
	public int frequency;
	public int offset;
	public boolean finetune;
	
	public ManFreqValues()
	{

	}

	public ManFreqValues(int param1, int param2, boolean param3)
	{
		this.frequency = param1;
		this.offset = param2;
		this.finetune = param3;
	}
}