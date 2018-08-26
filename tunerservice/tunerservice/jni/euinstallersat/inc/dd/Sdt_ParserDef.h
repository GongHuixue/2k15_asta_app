/*******************************************************************************
*              Copyright(c) 2004  Philips Innovation Campus.
*           All rights reserved. Reproduction in whole or in part is
*        prohibited without the written consent of the copyright holder.
*
*                     Project: SAPI
*                      Source: Include File  
*                    Filename: Sdt_ParserDef.h
*               Creation date: Wed Oct 01 11:35:31 2008 
*                      Author: ing01859
*                 %created_by: aneeshc %
*                    %version: TVG_1 %
*              %full_filespec: Sdt_ParserDef.h,TVG_1:h:blr81mgr#5 %
*              %date_modified: Mon Feb 09 20:39:43 2009 %
* 
* Description : 
********************************************************************************
*  Change history      :
*  ---------------
*  VERSION             DATE(MM/DD/YYYY)      NAME             CHANGE DESCRIPTION
*
*******************************************************************************/

typedef struct _TsService_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     ServiceType;
        Nat8     ProviderNameLen;
        char     ProviderName[80];
        Nat8     ServiceNameLen;
        char     ServiceName[80];
        Nat8     DescriptorValid;
} TsService_Descriptor;

typedef struct _TsLinkage_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat16     TSID;
    Nat16     ONID;
    Nat16     ServiceId;
    Nat8     LinkageType;
    Nat16     Private_ByteLen;
    Nat8     Private_Byte[10];
    Nat8     DescriptorValid;
} TsLinkage_Descriptor;

typedef struct _TsCicamBrandDesc{
    Nat16     Cicam_Brand_Identifier;
}TsCicamBrandDesc;

typedef struct _TsCI_Plus_Descriptor{
    Nat32     PrivateDataSpecifier;
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     Free_Ci_Mode;
    Nat8     Match_Brand_Flag;
    Nat8     Reserved_Future_Use;
    Nat8     Number_Of_Entries;
    Nat8     Cicam_BrandDesc_Len;
	TsCicamBrandDesc	CicamBrandDesc[23];
    Nat8     DescriptorValid;
}TsCI_Plus_Descriptor;

typedef struct _TsTargetRegion{
    Nat8     reserved;
    Nat8     CountryCodeFlag;
    Nat8     RegionDepth;
    Nat32     CountryCode;
    Nat32     PrimaryRegionCode;
    Nat32     SecondaryRegionCode;
    Nat32     TertiaryRegionCode;
}TsTargetRegion;

typedef struct _TsExt_TargetRegion_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     DescriptorTagExtn;
    Nat32     CountryCode;
    Nat8     TargetRegionLen;
	TsTargetRegion	TargetRegion[20];
    Nat8     DescriptorValid;
} TsExt_TargetRegion_Descriptor;


typedef struct _SdtTsLoopData{
	Nat16     service_id;
	Nat8     Eit_Schedule_Flag;
	Nat8     Eit_Present_Following_Flag;
	Nat8     running_status;
	Nat8     free_CA_mode;
	Nat16     descriptors_loop_length;

	TsService_Descriptor	Service_Descriptor[100];
	Nat8     ServiceDescNum;

	TsLinkage_Descriptor	Linkage_Descriptor[50];
	Nat8     LinkageDescNum;

	TsCI_Plus_Descriptor	CI_Plus_Descriptor[5];
	Nat8     CIPlusDescNum;

	TsExt_TargetRegion_Descriptor Ext_TargetRegion_Descriptor[10];
	Nat8     ExtTargetRegionDescNum;
} SdtTsLoopData;

typedef struct _Sdt_Parser{
    Nat8     TableId;
    Nat16     section_length;
    Nat16     transport_stream_id;
    Nat8     version_number;
    Nat16     original_network_id;
    Nat8     TsLoopDataNum;
	SdtTsLoopData	TsLoopData[1];
}TypeSdt_Parser;
