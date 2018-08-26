

struct _PrivateDataSpecifierDescriptor
{
	Nat8     DescriptorTag;
	Nat8     DescriptorLen;
	Nat32   PrivateDataSpecifierValue;
};

struct _BouquetName_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     BouquetNameLen;
    char     BouquetName[ MAX_BOUQUET_NAME_LEN ];
    Nat8     DescriptorValid;
};

struct _EutelsatChannelDescriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
	Nat16 	Onid;
	Nat16 	Tsid;
	Nat16 	ServiceId;
	Nat16 	EutelsatChannelNum;
  Nat32   PrivateDataSpecifierValue;
  Nat8     DescriptorValid;
};

struct _Linkage_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat16     TSID;
    Nat16     ONID;
    Nat16     ServiceId;
    Nat8     LinkageType;
    Nat8     DescriptorValid;
};

struct _FreesatInfoLocation_Descriptor{
	Nat32     PrivateDataSpecifier;
	Nat8     	DescriptorTag;
	Nat8     	DescriptorLen;
	Nat16	ServiceId;
	Nat16     TSID;
	Nat16     ONID;
};

struct _FreesatServiceGroup_Descriptor{
	Nat32 	PrivateDataSpecifier;
	Nat8    DescriptorTag;
	Nat8    DescriptorLen;
	Nat8	NonDestructiveTuneFlag;
	Nat8 	ReturnChannelAccessFlag;
	Nat16 	FreeSatelliteServicegroupId;
	Nat16 	FreeSatelliteServiceIdentifier;
};

struct _FreesatInteractiveStorage_Descriptor
{
	Nat32 	PrivateDataSpecifier;
	Nat8    DescriptorTag;
	Nat8    DescriptorLen;
	Nat8 	AllocationUnit;
	Nat8	GroupFlag;
	Nat16 	FreeSatelliteServicegroupId;
	Nat16	FreeSatelliteServiceIdentifier;
	Nat8 	NumBlocks;
};

/* Russion Tricolor related */
struct _Tricolor_ChannelListDetails 
{
	char 	channelListName[24];
	char 	channelListNameTranslation[24];
	Nat8 	channelListNameLength;            /* To be used for getting the LCN v2 */
	Nat8 	channelListNameTranslationLength; /* To be displayed to used in UI     */
};

struct _TricolorLRN_Descriptor 
{
	char									langCode[3];          /* ISO 639-2 Language code */
	Nat8									channelListDetailNum; /* Number of channel list names for given language code */
	struct _Tricolor_ChannelListDetails		Tricolor_ChannelListDetails[TRICOLOR_MAX_REGION_NAMES]; /* Minimum as per requirement is 10 */
};

struct _TsLCNDesc{
    Nat16     ServiceId;
    Nat16     LCNValue;
    Nat16     DpServiceId;
    Nat16     DpTSId;
};

struct _TsLCN_Descriptor{
    Nat32     PrivateDataSpecifier;
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     LCNLen;
    Nat16     Frequency;
    Nat8     Polarization;
	struct _TsLCNDesc LCNDesc[100];
    Nat8     DescriptorValid;
};

struct _TsLCN2Desc{
    Nat16     ServiceId;
    Nat16     LCNValue;
};

struct _TsLCN2ServiceDesc{
    Nat16     ServiceId;
    Nat16     LCNValue;
	Nat8 	  Visibility;
};

struct _TsLCN2ChannelLstDesc{
    Nat8     Channel_List_ID;
    Nat8     Channel_List_NameLngth;
    char     Channel_List_Name[40];
    Nat32    Country_Code;
    Nat8     DescriptorLen;
    Nat8     LCN2SvcDescLen;
	struct _TsLCN2ServiceDesc LCN2SvcDesc[70];
};

struct _TsLCN2_Descriptor
{
    Nat32    PrivateDataSpecifier;
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     LCN2Len;
	struct 	_TsLCN2Desc LCN2Desc[100];
	Nat8     LCN2ChannelListLen;	
	struct 	_TsLCN2ChannelLstDesc LCN2ChannelLstDesc[20];
    Nat8     DescriptorValid;
    Nat32    PrevPrivateDataSpecifier;
};

struct _TsServiceListDesc{
    Nat16     ServiceId;
    Nat8     ServiceType;
};

struct _TsService_List_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     ServiceListLen;
	struct _TsServiceListDesc ServiceListDesc[100];
    Nat8     DescriptorValid;
};

struct _TsLinkage_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat16     TSID;
    Nat16     ONID;
    Nat16     ServiceId;
    Nat8     LinkageType;
    Nat8     DescriptorValid;
};

struct _TsFreesatRegionalisedLCN_Descriptor{
	Nat32     PrevPrivateDataSpecifier;
	Nat8     	DescriptorTag;
	Nat8     	DescriptorLen;
	Nat16	ServiceId;
	Nat16     TSID;
	Nat16     ONID;
	Nat16 	FreeSatelliteServiceIdentifier;
	Nat8	NumericSelectionFlag;
	Nat8 	VisibleServiceFlag;
	Nat8 	UserCustomisableFlag;
	Nat16 	LogicalChannelNumber;
	Nat16 	RegionId;
};

struct _TsFreesatInteractiveRestriction_Descriptor{
	Nat32     PrevPrivateDataSpecifier;
	Nat8     	DescriptorTag;
	Nat8     	DescriptorLen;
	Nat16	ServiceId;
	Nat16     TSID;
	Nat16     ONID;
};

struct _BatTsLoopData{
	Nat16     TSID;
	Nat16     ONID;
	Nat16     TsDescLoopLen;

	struct _TsLCN_Descriptor LCN_Descriptor[100];
	Nat8     LCNDescNum;
	
	struct _TsLCN2_Descriptor LCN2_Descriptor[100];
	Nat8   LCN2DescNum;

	struct _TsService_List_Descriptor Service_List_Descriptor[100];
	Nat8     ServiceListDescNum;

	struct _TsLinkage_Descriptor Linkage_Descriptor[50];
	Nat8     LinkageDescNum;

	struct _TsFreesatRegionalisedLCN_Descriptor FreesatLCN_Descriptor[250];
	Nat8     FreesatLCNDescNum;

	struct _TsFreesatInteractiveRestriction_Descriptor FreesatInteractiveRestriction_Descriptor[128];
	Nat8     FreesatInteractiveRestrictionDescNum;
};

typedef struct _Bat_Parser
{
    Nat8     TableId;
    Nat16    SectionLen;
    Nat16    BouquetId;
    Nat8     VersionNo;
    Nat16    BouquetDescLen;
    
	struct _PrivateDataSpecifierDescriptor PrivateDataSpecifierDescriptor;

	struct _BouquetName_Descriptor BouquetName_Descriptor;
	Nat8     TotalNoOfEutelsatDesc;
	
	struct _EutelsatChannelDescriptor EutelsatChannelDescriptor[MAX_ECN_SERVICES];
    
    struct _Linkage_Descriptor Linkage_Descriptor[10];
    Nat8     LinkageDescNum;
	
	struct 	_TricolorLRN_Descriptor	TricolorLRN_Descriptor[20]; /* Tricolor Logical Region Name Descriptor - TAG 0x88 */
	Nat8	TricolorLRN_DescNum;
	
	struct _TsLCN2_Descriptor LCNV2_Descriptor[10];
	Nat8   LCNV2DescNum;

	struct  _FreesatInfoLocation_Descriptor FreesatInfoLocation_Descriptor[42];
	Nat8     FreesatInfoLocationDescNum;

	struct _FreesatServiceGroup_Descriptor FreesatServiceGroup_Descriptor[500];
	Nat8	FreesatServiceGroupDescNum;

	struct _FreesatInteractiveStorage_Descriptor FreesatInteractiveStorage_Descriptor[340];
	Nat8	FreesatInteractiveStorageDescNum;

    Nat16     TsLoopLen;
    Nat8     TsLoopDataNum;
	struct _BatTsLoopData TsLoopData[4];
}TypeBat_Parser;
