package org.droidtv.euinstallersat.model.mwapi;

import org.droidtv.tv.media.ITvMediaOp.OpProfileStatusInfo;

import java.util.Arrays;

public class OperatorProfileStatusInfo {
		
    public int 	Info_Version;
    public int 	NIT_Version;
    public int	Profile_Type;
    public int 	Initialised_Flag;
    public int 	Entitlement_Change_Flag;
    public int 	Entitlement_Valid_Flag;
    public int	Refresh_Request_Flag;
    public int	Error_Flag;
    public int 	Delivery_System_Hint;
    public int 	Refresh_Request_Date;
    public int 	Refresh_Request_Time;
    
    //Profile Info
    public int 	InfoValid;
    public int 	ProfileInfoVersion;
    public int	CiCamOriginalNetworkId;
    public int 	CiCamIdentifier;
    public int 	CharacterCodeTable;
    public int 	CharacterCodeTable2;
    public int 	CharacterCodeTable3;
    public int 	SdtRunningTrusted;
    public int 	EitRunningTrusted;
    public int 	EitPfUsage;
    public int 	EitScheduleUsage;
    public int 	ExtendedEventUsage;
    public int 	SdtOtherTrusted;
    public int 	EitEventTrigger;
    public int 	ISO639LangCode[];
    public int	ProfileNameLength;
    public int 	ProfileName[];

    public OperatorProfileStatusInfo() {
    }
    
    public OperatorProfileStatusInfo (int param1, int param2, int param3, int param4, int param5, int param6, 
                                      int param7, int param8, int param9, int param10, int param11, int param12, 
                                      int param13, int param14, int param15, int param16, int param17, int param18, 
                                      int param19, int param20, int param21, int param22, int param23, int param24, 
                                      int param25, int param26[], int param27, int param28[])
    {
        this.Info_Version				= param1;
        this.NIT_Version				= param2;
        this.Profile_Type				= param3;
        this.Initialised_Flag			= param4;
        this.Entitlement_Change_Flag	= param5;
        this.Entitlement_Valid_Flag		= param6;
        this.Refresh_Request_Flag		= param7;
        this.Error_Flag					= param8;
        this.Delivery_System_Hint		= param9;
        this.Refresh_Request_Date		= param10;
        this.Refresh_Request_Time		= param11;
        
        this.InfoValid					= param12;
        this.ProfileInfoVersion			= param13;
        this.CiCamOriginalNetworkId		= param14;
        this.CiCamIdentifier			= param15;
        this.CharacterCodeTable			= param16;
        this.CharacterCodeTable2		= param17;
        this.CharacterCodeTable3		= param18;
        this.SdtRunningTrusted			= param19;
        this.EitRunningTrusted			= param20;
        this.EitPfUsage					= param21;
        this.EitScheduleUsage			= param22;
        this.ExtendedEventUsage			= param23;
        this.SdtOtherTrusted			= param24;
        this.EitEventTrigger			= param25;
        this.ISO639LangCode 			= Arrays.copyOf(param26,param26.length);
        this.ProfileNameLength			= param27;
        this.ProfileName				= Arrays.copyOf(param28,param28.length);
    
    }

    public OperatorProfileStatusInfo(OpProfileStatusInfo statusInfo) {

        int i = 0;
	
    	this.Info_Version				= statusInfo.Status_Info_Version;
    	this.NIT_Version				= statusInfo.NIT_Version;
    	this.Profile_Type				= statusInfo.Profile_Type;
    	this.Initialised_Flag			= statusInfo.Initialised_Flag;
    	this.Entitlement_Change_Flag	= statusInfo.Entitlement_Change_Flag;
    	this.Entitlement_Valid_Flag		= statusInfo.Entitlement_Valid_Flag;
    	this.Refresh_Request_Flag		= statusInfo.Refresh_Request_Flag;
    	this.Error_Flag					= statusInfo.Error_Flag;
    	this.Delivery_System_Hint		= statusInfo.Delivery_System_Hint;
    	this.Refresh_Request_Date		= statusInfo.Refresh_Request_Date;
    	this.Refresh_Request_Time		= statusInfo.Refresh_Request_Time;
    	                                
    	this.InfoValid					= statusInfo.info_Valid;
    	this.ProfileInfoVersion			= statusInfo.info_Version;
    	this.CiCamOriginalNetworkId		= statusInfo.cicam_Original_Network_Id;
    	this.CiCamIdentifier			= statusInfo.cicam_Identifier;
    	this.CharacterCodeTable			= statusInfo.character_Code_Table;
    	this.CharacterCodeTable2		= statusInfo.character_Code_Table_2;
    	this.CharacterCodeTable3		= statusInfo.character_Code_Table_3;
    	this.SdtRunningTrusted			= statusInfo.sDT_Running_Trusted;
    	this.EitRunningTrusted			= statusInfo.eIT_Running_Trusted;
    	this.EitPfUsage		        	= statusInfo.eIT_Pf_Usage;
    	this.EitScheduleUsage			= statusInfo.eIT_Schedule_Usage;
    	this.ExtendedEventUsage			= statusInfo.extended_Event_Usage;
    	this.SdtOtherTrusted			= statusInfo.sDT_Other_Trusted;
    	this.EitEventTrigger			= statusInfo.eIT_Event_Trigger;
		this.ISO639LangCode		    	= Arrays.copyOf (statusInfo.iSO_639_Lang_Code, statusInfo.iSO_639_Lang_Code.length);
    	this.ProfileNameLength			= statusInfo.profile_Name_Length;
		this.ProfileName				= Arrays.copyOf (statusInfo.profile_Name, statusInfo.profile_Name.length);
    }
}
