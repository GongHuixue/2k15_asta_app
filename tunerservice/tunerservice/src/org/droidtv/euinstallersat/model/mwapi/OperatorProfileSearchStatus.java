package org.droidtv.euinstallersat.model.mwapi;

public class OperatorProfileSearchStatus {
		
    public int 	Info_Version;
    public int 	NIT_Version;		
    public int	 	Profile_Type;			
    public int 	Initialised_Flag;					
    public int 	Entitlement_Change_Flag;
    public int 	Entitlement_Valid_Flag;
    public int	 	Refresh_Request_Flag;
    public int	 	Error_Flag;
    public int 	Delivery_System_Hint;
    public int 	Refresh_Request_Date;
    public int 	Refresh_Request_Time;
    
    public OperatorProfileSearchStatus() {
    }
    
    public OperatorProfileSearchStatus (int param1, int param2, int param3, int param4, int param5, int param6, 
                                        int param7, int param8, int param9, int param10, int param11)
    {
        this.Info_Version				= param1;
        this.NIT_Version					= param2;
        this.Profile_Type				= param3;			
        this.Initialised_Flag			= param4;		
        this.Entitlement_Change_Flag		= param5;
        this.Entitlement_Valid_Flag		= param6;
        this.Refresh_Request_Flag		= param7;
        this.Error_Flag					= param8;
        this.Delivery_System_Hint		= param9;
        this.Refresh_Request_Date		= param10;
        this.Refresh_Request_Time		= param11;
    }
}