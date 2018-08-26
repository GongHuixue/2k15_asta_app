package org.droidtv.euinstallertc.model.mwapi;

import java.util.Arrays;

public class MwDataTypes {

	public class InstallerConstants {
		public int IHsvInstallation2_InvalidChannel = -1;
		public int IHsvInstallation2_InvalidFrequency = -1;
		public int IHsvInstallation2_StIdle = 0;
		public int IHsvInstallation2_StSourceSetupWait = 1;
		public int IHsvInstallation2_StDigital = 2;
		public int IHsvInstallation2_StAnalog = 3;
		public int IHsvInstallation2_StPreSorting = 4;
		public int IHsvInstallation2_StSorting = 5;
		public int IHsvInstallation2_Terrestrial = 0;
		public int IHsvInstallation2_Cable = 1;
		public int IHsvInstallation2_Satellite = 2;
		public int IHsvInstallation2_InstallationInPassAnalog = 1;
		public int IHsvInstallation2_InstallationInDigitalPass = 3;
		public int IHsvInstallation2_InstallationStateScrambledSearch = 3;
		public int IHsvInstallation2_InstallationStateIdle = 0;
		public int IHsvInstallation2_InstallationStateInProgress = 1;
		public int IHsvInstallation2_InstallationStatePaused = 2;
		public int IHsvInstallation2_InstallationModeNone = 0;
		public int IHsvInstallation2_InstallationModeManual = 1;
		public int IHsvInstallation2_InstallationModeAutomatic = 2;
		public int IHsvInstallation2_InstallationModeBackground = 3;
		public int IHsvInstallation2_InstallationModeImplicit = 4;
		public int IHsvInstallation2_InstallationModeUpdate = 5;
		public int IHsvInstallation2_InstallationModeWeakSignal = 6;
		public int IHsvInstallation2_InstallationModeSingleChannel = 7;
		public int IHsvInstallation2_InstallationModePreScan = 8;
		public int IHsvInstallation2_InstallationModeDtr = 9;
		public int IHsvInstallation2_InstallationModeCam = 10;
		public int IHsvInstallation2_MaxChannel = 14;
		public int IHsvInstallation2_ManualInstallationModeFrequency = 0;
		public int IHsvInstallation2_InsTvSystemBg = 0;
		public int IHsvInstallation2_InsTvSystemDk = 1;
		public int IHsvInstallation2_InsTvSystemI = 2;
		public int IHsvInstallation2_InsTvSystemL = 3;
		public int IHsvInstallation2_InsTvSystemN = 4;
		public int IHsvInstallation2_InsTvSystemM = 5;
		public int IHsvInstallation2_InsTvSystemAuto = 6;
 		public int IHsvInstallation2_InsTvSystemBG_A2 = 7;
		public int IHsvInstallation2_InsTvSystemDK_A2 = 8;
		public int IHsvInstallation2_InsColourSystemPal = 0;
		public int IHsvInstallation2_InsColurSystemSecam = 1;
		public int IHsvInstallation2_InsColurSystemNtsc358 = 2;
		public int IHsvInstallation2_InsColurSystemNtsc443 = 3;
		public int IHsvInstallation2_InsColurSystemAuto = 4;
		public int IHsvInstallation2_InsColurSystemInvalid = 5;
		public int IHsvInstallation2_InsColurSystemNtscUnknown = 6;
		public int IHsvInstallation2_InsAssm = 0;
		public int IHsvInstallation2_InsVssm = 1;
		public int IHsvInstallation2_InsQssm = 2;
		public int IHsvInstallation2_InsSssm = 3;
		public int IHsvInstallation2_ScanNone = 0x0;
		public int IHsvInstallation2_ScanAnalog = 0x1;
		public int IHsvInstallation2_ScanDVBT = 0x2;
		public int IHsvInstallation2_ScanDVBC = 0x4;
		public int IHsvInstallation2_ScanDVBS = 0x8;
		public int IHsvInstallation2_AttributeScanMode = 0;
		public int IHsvInstallation2_AttributeSymbolRate = 1;
		public int IHsvInstallation2_AttributeNetworkId = 2;
		public int IHsvInstallation2_AttributeNetworkFreq = 3;
		public int IHsvInstallation2_AttributeModulation = 4;
		public int IHsvInstallation2_AttributeDigitalOption = 5;
		public int IHsvInstallation2_AttributeFreqStepSize = 6;
		public int IHsvInstallation2_AttributeCity = 7;
		public int IHsvInstallation2_AttributePrimaryRegion = 8;
		public int IHsvInstallation2_AttributeSecondaryRegion = 9;
		public int IHsvInstallation2_AttributeTertiaryRegion = 10;
		public int IHsvInstallation2_AttributeScrOrFTA = 11;
		public int IHsvInstallation2_AttributeNetworkOperator = 12;
		public int IHsvInstallation2_AttributeUpdateInstall = 13;
		public int IHsvInstallation2_AttributePersistentFile = 14;
		public int IHsvInstallation2_AttributeLCNSorting = 15;
		public int  IHsvInstallation2_AttributeDualAnalogPass = 19;
	    public int  IHsvInstallation2_AttributeDTTScanOnAnalog = 20;
	    public int  IHsvInstallation2_AttributeLCNOption = 21;
		public int IHsvInstallation2_QuickScan = 0;
		public int IHsvInstallation2_FullScan = 1;
		public int IHsvInstallation2_GridScan = 2;
		public int IHsvInstallation2_AutomaticValue = 0;
		public int IHsvInstallation2_ManualValue = 1;
		public int IHsvAppApiNoSource = 0;
		public int IHsvAppApiMainTuner = 1;
		public int IHsvAppApiAuxTuner = 2;

		public int IHsvInstallation2_DVBCStepSize1 = 1;
		public int IHsvInstallation2_DVBCStepSize8 = 8;
	}

	class EventConstants {

		public int IHsvInstallationNotify_EventInstallationCompleted = 1;
		public int IHsvInstallationNotify_EventInstallationStarted = 2;
		public int IHsvInstallationNotify_EventInstallationStopped = 3;
		public int IHsvInstallationNotify_EventInstallationPaused = 4;
		public int IHsvInstallationNotify_EventInstallationContinued = 5;
		public int IHsvInstallationNotify_EventChannelFound = 6;
		public int IHsvInstallationNotify_EventChannelNotFound = 7;
		public int IHsvInstallationNotify_EventSearchInProgress = 8;
		public int IHsvInstallationNotify_EventTuningStarted = 9;
		public int IHsvInstallationNotify_EventTuningStationFound = 10;
		public int IHsvInstallationNotify_EventTuningStationNotFound = 11;
		public int IHsvInstallationNotify_EventManualInstallationCniExtractionStarted = 12;
		public int IHsvInstallationNotify_EventManualInstallationCniExtractionEnded = 13;
		public int IHsvInstallationNotify_EventATSSortingStarted = 14;
		public int IHsvInstallationNotify_EventAciStoreStarted = 15;
		public int IHsvInstallationNotify_EventTvSystemChanged = 16;
		public int IHsvInstallationNotify_EventMediumChanged = 17;
		public int IHsvInstallationNotify_EventSignalStrengthChanged = 18;
		public int IHsvInstallationNotify_EventBackGroundCNIUpdated = 19;
		public int IHsvInstallationNotify_EventPresetStored = 20;
		public int IHsvInstallationNotify_EventPhaseStarted = 22;
		public int IHsvInstallationNotify_EventPhaseCompleted = 23;
		public int IHsvInstallationNotify_EventChannelIterationStarted = 24;
		public int IHsvInstallationNotify_EventHeirarchyModeDetected = 25;
		public int IHsvInstallationNotify_EventChannelAdded = 26;
		public int IHsvInstallationNotify_EventChannelRemoved = 27;
		public int IHsvInstallationNotify_EventNetworkUpdateDetected = 28;
		public int IHsvInstallationNotify_EventDisplayNetworkNames = 29;
		public int IHsvInstallationNotify_EventNIDInvalid = 30;
		public int IHsvInstallationNotify_EventNetworkUpdateNotDetected = 31;
		public int IHsvInstallationNotify_EventOnConflictsDetected = 32;
		public int IHsvInstallationNotify_EventDisplayRegionNames = 33;
		public int IHsvInstallationNotify_EventPLPsDetected = 34;
		public int IHsvInstallationNotify_NetworkOperator = 35;
		public int IHsvInstallationNotify_EventCamInstallRequestNormal = 36;
		public int IHsvInstallationNotify_EventCamInstallRequestUrgent = 37;
		public int IHsvInstallationNotify_EventPresetAdded=38;
		public int IHsvInstallationNotify_EventPresetDeleted=39;
		public int IHsvInstallationNotify_EventUpdated=40;	
		public int IHsvInstallationNotify_EventMultiPackageFound = 41;
		public int IHsvInstallationNotify_EventMultiPackageToBeDisplayed = 42;
		public int IHsvInstallationNotify_EventMultiPackageRemoved = 43;
		public int IHsvInstallationNotify_EventNewPresetNumber = 44;
		public int IHsvInstallationNotify_EventDisplayChannelListId	=45;
		public int IHsvInstallationNotify_EventTelenetNameUpdate = 46;
		public int IHsvInstallationNotify_EventTelenetMajorVersionUpdate = 47;
		public int IHsvInstallationNotify_EventLanguageUpdate = 48;
		public int IHsvInstallationNotify_EventChannelNameUpdate = 49;
		public int IHsvInstallationNotify_EventServiceFound = 50;
		public int IHsvInstallationNotify_EventServiceNotFound = 51;
		public int IHsvInstallationNotify_EventT2SwitchPLPID = 52;

	}
	public static class opSearchSettings {
		
		public int     Unattended_Flag;
		public int  	Service_Type_Length;	
		public int		Service_Type[];			
		public int 	Delivery_Cap_Length;	
		public int		Delivery_Capability[];
		public int 	Application_Cap_Length;
		public int 	Application_Capability[];
		
		public opSearchSettings(){}
		public opSearchSettings(int param1, int param2, int param3[], int param4, int param5[], int param6, int param7[]) {
		
			this.Unattended_Flag 		 = param1;
			this.Service_Type_Length 	 = param2;	
			this.Service_Type 		 = Arrays.copyOf(param3,param3.length);
			this.Delivery_Cap_Length	 = param4;
			this.Delivery_Capability	 = Arrays.copyOf(param5,param5.length);
			this.Application_Cap_Length  = param6;
			this.Application_Capability	 = Arrays.copyOf(param7,param7.length);
		}
	}
	
	public static class opTuneStatus {
		
		public int 	Descriptor_Number;		
		public int 	Signal_Strength;		
		public int 	Signal_Quality;			
		public int 	Status;					
		public int 	Descriptor_Loop_Length;	
		public int 	Descriptor_Loop[];
		public opTuneStatus(){}
		public opTuneStatus(int param1, int param2, int param3, int param4, int param5, int param6[]) {
		
			this.Descriptor_Number			= param1;
			this.Signal_Strength			= param2;
			this.Signal_Quality				= param3;
			this.Status						= param4;	
			this.Descriptor_Loop_Length  	= param5;
			this.Descriptor_Loop			= Arrays.copyOf(param6,param6.length);
		}
	}
	
	public static class opProfileSearchStatus {
		
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
		
		public opProfileSearchStatus(){}
		public opProfileSearchStatus(int param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8, int param9, int param10, int param11)
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
	
	public static class opProfileTuneData {
		
		public int 	TuneDataLength;		
		public int 	TuneData[];		
		public opProfileTuneData(){}
		public opProfileTuneData(int param1, int param2[]) {
			
			this.TuneDataLength		= param1;
			this.TuneData			= Arrays.copyOf(param2,param2.length);
		}
	}
	
	public static class opProfileNitData {
		
		public int 	NitStatus;
		public int	NitDataLength;
		public int 	NitData[];		
		public opProfileNitData(){}
		public opProfileNitData(int param1, int param2, int param3[]) {
			
			this.NitStatus		= param1;
			this.NitDataLength	= param2;
			this.NitData		= Arrays.copyOf(param3,param3.length);
		}
	}

	public static class opProfileStatusInfo {
		
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
		
		//Profile Info
		public int 	InfoValid;					
		public int 	ProfileInfoVersion;				
		public int	CiCamOriginalNetworkId;	
		public int 		CiCamIdentifier;			
		public int 	CharacterCodeTable;		
		public int 	CharacterCodeTable2;
		public int 	CharacterCodeTable3;
		public int 	SdtRunningTrusted;		
		public int 	EitRunningTrusted;		
		public int 		EitPfUsage;				
		public int 		EitScheduleUsage;
		public int 	ExtendedEventUsage;		
		public int 	SdtOtherTrusted;		
		public int 	EitEventTrigger;		
		public int 	ISO639LangCode[];																
		public int	ProfileNameLength;		
		public int 	ProfileName[];
						
		public opProfileStatusInfo(){}
		public opProfileStatusInfo(int param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8, int param9, int param10, int param11, 
								   int param12, int param13, int param14, int param15, int param16, int param17, int param18, int param19, int param20, int param21, int param22, 
								   int param23, int param24, int param25, int param26[], int param27, int param28[])
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
			this.ISO639LangCode 			=Arrays.copyOf(param26,param26.length);		
			this.ProfileNameLength			= param27;		
			this.ProfileName				= Arrays.copyOf(param28,param28.length);
		
		}
	}
}
