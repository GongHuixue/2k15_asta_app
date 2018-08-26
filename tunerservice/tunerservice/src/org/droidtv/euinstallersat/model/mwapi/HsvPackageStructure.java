package org.droidtv.euinstallersat.model.mwapi;

public class HsvPackageStructure
{
	public int	Index;
	public int	PackageId;
	public String PackageName;
	public String PackageListName;
	public String PredefinedListBinFile;
	public int retVal;
	public int PackageIndex;
	public boolean IsPackage;


	public HsvPackageStructure()
	{

	}
	
	public HsvPackageStructure(int param1,int param2) {
		this.Index = param1;
		this.PackageId = param2;
	}
	public HsvPackageStructure(int param1,int param2,String param3,String param4)
	{
		this.Index = param1;
		this.PackageId = param2;
		this.PackageName = param3;
		this.PackageListName = param4;
		//this.PredefinedListBinFile = param5;
		//this.retVal = param6;
	}

	public HsvPackageStructure(int param1,boolean param2,int param3)
	{
		this.PackageIndex = param1;
		this.IsPackage = param2;
		this.retVal = param3;
	}

	public HsvPackageStructure(String param1,int param2)
	{
		this.PackageName = param1;
		this.retVal=param2;
	} 
}