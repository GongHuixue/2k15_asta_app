/*******************************************************************************
*              Copyright(c) 2004  Philips Innovation Campus.
*           All rights reserved. Reproduction in whole or in part is
*        prohibited without the written consent of the copyright holder.
*
*                     Project: SAPI
*                      Source: Include File  
*                    Filename: Nit_ParserDef.h
*               Creation date: Wed Oct 01 11:32:39 2008 
*                      Author: ing01859
*                 %created_by: dnilanjan %
*                    %version: TVG_7 %
*              %full_filespec: Nit_ParserDef.h,TVG_7:h:blr81mgr#5 %
*              %date_modified: Fri Jan 30 12:21:05 2009 %
* 
* Description : 
********************************************************************************
*  Change history      :
*  ---------------
*  VERSION             DATE(MM/DD/YYYY)      NAME             CHANGE DESCRIPTION
*
*******************************************************************************/

typedef  struct _NetworkName_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     NetworkNameLen;
    char     NetworkName[80];
    Nat8     DescriptorValid;
}NitNetworkName_Descriptor;

typedef struct _HeadEndFreqDescriptor{
    Nat16     TSID;
    Nat16     SiteHeadEndFrequency;
} NitHeadEndFreqDescriptor;

typedef struct _HeadEndFreq_Descriptor{
    Nat32     PrivateDataSpecifier;
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     HeadEndFreqLen;
	NitHeadEndFreqDescriptor	HeadEndFreqDescriptor[100];
    Nat8     DescriptorValid;
} NitHeadEndFreq_Descriptor;

typedef struct _Linkage_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat16     TSID;
    Nat16     ONID;
    Nat16     ServiceId;
    Nat8     LinkageType;
    Nat16     Private_ByteLen;
    Nat8     Private_Byte[40];
    Nat8     DescriptorValid;
} NitLinkage_Descriptor;

typedef struct _TsNetworkName_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     NetworkNameLen;
    char     NetworkName[80];
    Nat8     DescriptorValid;
} NitTsNetworkName_Descriptor;

typedef struct _TsLinkage_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat16     TSID;
    Nat16     ONID;
    Nat16     ServiceId;
    Nat8     LinkageType;
    Nat16     Private_ByteLen;
    Nat8     Private_Byte[40];
    Nat8     DescriptorValid;
} NitTsLinkage_Descriptor;


typedef struct __NitFreesatLinkageDesc{
	Nat16     TSID;
	Nat16     ONID;
	Nat16 ServiceId;
	Nat8 TunnelledTypeLoopLen;
	Nat8 TunnelledLinkageType[20];
}NitFreesatLinkageDesc;
typedef struct _FreesatLinkage_Descriptor{
	Nat32 PrivateDataSpecifier;
	Nat8 DescriptorTag;
    	Nat8 DescriptorLen;
	Nat8 FreesatLinkageDescNum;
	NitFreesatLinkageDesc FreesatLinkageDesc[25];
}NitFreesatLinkage_Descriptor;
struct _TsHDSLCNDesc{
    Nat16     Service_ID;
    Nat8     Visible_Service_Flag;
    Nat8     reserved1;
    Nat16     LCNValue;
};

struct _TsHDSLCN_Descriptor{
    Nat32     PrivateDataSpecifier;
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     HDSLCNLen;
	struct _TsHDSLCNDesc HDSLCNDesc[50];
    Nat8     DescriptorValid;
    Nat32    prevPrivateDataSpecifier;
};

struct _TsLCNDesc{
    Nat16     ServiceId;
    Nat16     LCNValue;
};


struct _TsLCN_Descriptor{
    Nat32     PrivateDataSpecifier;
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     LCNLen;
	struct _TsLCNDesc	LCNDesc[100];
    Nat8     DescriptorValid;
    Nat32    prevPrivateDataSpecifier;
};

struct _TsLCN2Desc{
    Nat16     ServiceId;
    Nat16     LCNValue;
};

struct _TsLCN2ChannelLstDesc{
    Nat8     Channel_List_ID;
    Nat8     Channel_List_NameLngth;
    char     Channel_List_Name[40];
    Nat32     Country_Code;
    Nat8     DescriptorLen;
    Nat8     LCN2DescLen;
	struct _TsLCN2Desc	LCN2Desc[100];
};

struct _TsLCN2_Descriptor{
    Nat32     PrivateDataSpecifier;
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     LCN2ChannelListLen;
	struct _TsLCN2ChannelLstDesc LCN2ChannelLstDesc[10];
    Nat8     DescriptorValid;
};

struct _TsLCN3Desc
{
	Nat16     ServiceId;
	Nat16     ChannelId;
	Nat16     CpServiceId;
};

struct _TsLCN3_Descriptor
{
    Nat32    PrivateDataSpecifier;
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     LCN3Len;
	struct _TsLCN3Desc LCN3Desc[100];
    Nat8     DescriptorValid;
};

struct _TsSDSD{
	Nat32     Frequency;
	Nat16     OrbitalPostion;
	Nat8     WestEastFlag;
	Nat8     Polarization;
	Nat8     RollOff;
	Nat8     Modulationsystem;
	Nat8     Modulationtype;
	Nat32    SymbolRate;
	Nat8     FEC_Inner;
};

struct _TsSDSD_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     SDSDLen;
	struct _TsSDSD SDSD[100];
    Nat8     DescriptorValid;
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

struct _NitTsLoopData{
	Nat16     TSID;
	Nat16     ONID;
	Nat16     TsDescLoopLen;

	NitTsNetworkName_Descriptor NetworkName_Descriptor;
	Nat8     NtkNameDescNum;

	NitTsLinkage_Descriptor Linkage_Descriptor[50];
	Nat8     LinkageDescNum;

	struct _TsHDSLCN_Descriptor HDSLCN_Descriptor[10];
	Nat8     HDSLCNDescNum;

	struct _TsLCN_Descriptor LCN_Descriptor[100];
	Nat8     LCNDescNum;

	struct _TsLCN2_Descriptor LCN2_Descriptor[10];
	Nat8     LCN2DescNum;

	struct _TsLCN3_Descriptor LCN3_Descriptor[100];    
	Nat8     LCN3DescNum;

	struct _TsSDSD_Descriptor SDSD_Descriptor[20];
	Nat16     SDSDDescNum;

	struct _TsService_List_Descriptor Service_List_Descriptor[10];
	Nat8     ServiceListDescNum;
};

typedef struct _Nit_Parser{
    Nat8     TableId;
    Nat16     SectionLen;
    Nat16     NetworkId;
    Nat8     VersionNo;
    Nat16     NetworkDescLen;
    
	NitNetworkName_Descriptor	NetworkName_Descriptor;
    Nat8     NtkNameDescNum;
    
	NitHeadEndFreq_Descriptor	HeadEndFreq_Descriptor[10];
    Nat8     HeadEndFreqDescNum;

    NitLinkage_Descriptor Linkage_Descriptor[50];
    Nat8     LinkageDescNum;

	NitFreesatLinkage_Descriptor FreesatLinkage_Descriptor[10];
	Nat8     FreesatLinkageDescNum;
	
    Nat16     TsLoopLen;
    Nat8     TsLoopDataNum;
	struct _NitTsLoopData TsLoopData[4];
}TypeNit_Parser;
