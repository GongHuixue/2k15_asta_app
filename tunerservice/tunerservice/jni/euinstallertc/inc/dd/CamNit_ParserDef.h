typedef struct _CamNitParser{
    Nat8     TableId;
    Nat16     SectionLen;
    Nat16     NetworkId;
    Nat8     VersionNo;
    Nat16     NetworkDescLen;
    
    struct _NetworkName_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     NetworkNameLen;
        char     NetworkName[80];
        Nat8     DescriptorValid;
    }NetworkName_Descriptor;
    
    Nat8     NtkNameDescNum;
    
    struct _Linkage_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat16     TSID;
        Nat16     ONID;
        Nat16     ServiceId;
        Nat8     LinkageType;
        Nat8     DescriptorValid;
    }Linkage_Descriptor[10];
    
    Nat8     LinkageDescNum;
    
    struct _CIPlus_Content_Label_Descriptor{
        Nat32    PrivateDataSpecifier;
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     Content_Byte_Min;
        Nat8     Content_Byte_Max;
        Nat32    ISO_639_Language_Code;
        Nat8     LabelCharLen;
        Nat8     LabelChar[80];
        Nat8     DescriptorValid;
    }CIPlus_Content_Label_Descriptor[10];
    
    Nat8     CIPlusContentLabelDescNum;
    Nat16     TsLoopLen;
    Nat8     TsLoopDataNum;
    struct _TsLoopData{
    Nat16     TSID;
    Nat16     ONID;
    Nat16     TsDescLoopLen;
    
    struct _TsNetworkName_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     NetworkNameLen;
        char     NetworkName[80];
        Nat8     DescriptorValid;
    }NetworkName_Descriptor;
    
    Nat8     NtkNameDescNum;
    
    struct _TsLinkage_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat16     TSID;
        Nat16     ONID;
        Nat16     ServiceId;
        Nat8     LinkageType;
        Nat8     DescriptorValid;
    }Linkage_Descriptor[80];
    
    Nat8     LinkageDescNum;
    
    struct _TsCDSD_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     CDSDLen;
    struct _TsCDSD{
        Nat32     Frequency;
        Nat8     reserved;
        Nat8     FEC_Outer;
        Nat8     Modulation;
        Nat32     SymbolRate;
        Nat8     FEC_Inner;
    }CDSD[20];
        Nat8     DescriptorValid;
    }CDSD_Descriptor[30];
    
    Nat8     CDSDDescNum;
    
    struct _TsTDSD_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     TDSDLen;
    struct _TsTDSD{
        Nat32    Frequency;
        Nat8     Bandwidth;
        Nat8     Priority;
        Nat8     TimeSlicingIndicator;
        Nat8     MPE_FECIndicator;
        Nat8     Constellation;
        Nat8     HierarchyInformation;
        Nat8     CodeRateHPSTream;
        Nat8     CodeRateLPSTream;
        Nat8     GuardInterval;
        Nat8     TransmissionMode;
        Nat8     OtherFrequencyFlag;
        Nat32    Reserved;
    }TDSD[20];
        Nat8     DescriptorValid;
    }TDSD_Descriptor[30];
    
    Nat8     TDSDDescNum;
    
	struct _TsC2DSD_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
		Nat8     DescriptorTagExtn;
		Nat8     C2DSDLen;
		struct _TsC2DSD{
			Nat8     PLP_Id;
			Nat16    SystemId;
			Nat32    Frequency;
		}C2DSD[20];
		Nat8     DescriptorValid;
    }C2DSD_Descriptor[30];
	
	Nat8     C2DSDDescNum;
	
	struct _TsT2DSD_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
		Nat8     DescriptorTagExtn;
		Nat8     T2DSDLen;
		struct _TsT2DSD{
			Nat8     PLP_Id;
			Nat8     SystemId;
			Nat8	 Bandwidth;
			Nat32    Frequency;
		}T2DSD[20];
		Nat8     DescriptorValid;
    }T2DSD_Descriptor[30];
	
	Nat8     T2DSDDescNum;
	
    struct _TsCIPlus_Service_Descriptor{
        Nat32    PrivateDataSpecifier;
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat16    ServiceId;
        Nat8     ServiceType;
        Nat8     VisibleServiceFlag;
        Nat8     SelectableServiceFlag;
        Nat16    LogicalChannelNumber;
        Nat8     ProviderNameLen;
        char     ProviderName[80];
        Nat8     ServiceNameLen;
        char     ServiceName[80];
        Nat8     DescriptorValid;
    }CIPlus_Service_Descriptor[300];
    
    Nat8     CIPlusServiceDescNum;
    }TsLoopData[4];
}TypeCamNitParser;
