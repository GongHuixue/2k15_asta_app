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
*                 %created_by: integration %
*                    %version: TVG_fusion_1 %
*              %full_filespec: Nit_ParserDef.h,TVG_fusion_1:h:blr81mgr#4 %
*              %date_modified: Fri Jan 30 12:21:05 2009 %
* 
* Description : 
********************************************************************************
*  Change history      :
*  ---------------
*  VERSION             DATE(MM/DD/YYYY)      NAME             CHANGE DESCRIPTION
*
*******************************************************************************/

typedef struct _Nit_Parser{
    Nat8     TableId;
    Nat16     SectionLen;
    Nat16     NetworkId;
    Nat8     VersionNo;
    Nat16     NetworkDescLen;
    
    struct _NetworkName_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     NetworkNameLen;
        char     NetworkName[MAX_NETWORK_NAME_SIZE + 1];
        Nat8     DescriptorValid;
    }NetworkName_Descriptor;
    
    Nat8     NtkNameDescNum;
    
    struct _TSRelocate_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     TS_RelocateLen;
    struct _TS_RelocateDesc{
        Nat8     Transport_Stream_ID;
        Nat8     Original_Network_ID;
        Nat8     TS_DescriptorLen;
        Nat8     TSDescLen;
    struct _TSDesc{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat32     Frequency;
        Nat8     reserved;
        Nat8     FEC_Outer;
        Nat8     Modulation;
        Nat32     SymbolRate;
        Nat8     FEC_Inner;
    }TSDesc[100];
    }TS_RelocateDesc[10];
        Nat8     DescriptorValid;
    }TSRelocate_Descriptor[10];
    
    Nat8     TSRelocateDescNum;
    
    struct _Linkage_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat16     TSID;
        Nat16     ONID;
        Nat16     ServiceId;
        Nat8     LinkageType;
        Nat16     Private_ByteLen;
        Nat8     Private_Byte[40];
        Nat8     DescriptorValid;
    }Linkage_Descriptor[50];
    
    Nat8     LinkageDescNum;
    struct _Ext_TargetRegion_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     DescriptorTagExtn;
        Nat32     CountryCode;
		Nat32     TargetRegionLen;
    struct _TargetRegion{
        Nat8     reserved;
        Nat8     CountryCodeFlag;
        Nat8     RegionDepth;
        Nat32     CountryCode;
        Nat32     PrimaryRegionCode;
        Nat32     SecondaryRegionCode;
        Nat32     TertiaryRegionCode;
    }TargetRegion[20];
        Nat8     DescriptorValid;
    }Ext_TargetRegion_Descriptor[10];
    
    Nat8     ExtTargetRegionDescNum;
    
    struct _Ext_TargetRegionName_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     DescriptorTagExtn;
        Nat32     CountryCode;
        Nat32     LangCode;
        Nat8     TargetRegionNameLen;
    struct _TargetRegionName{
        Nat8     RegionDepth;
        Nat8     RegionNameLen;
        Nat8     RegionName[80];
        Nat8     PrimaryRegionCode;
        Nat32     SecondaryRegionCode;
        Nat32     TertiaryRegionCode;
    }TargetRegionName[20];
        Nat8     DescriptorValid;
    }Ext_TargetRegionName_Descriptor[10];
    
    Nat8     ExtTargetRegionNameDescNum;
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
        char     NetworkName[140];
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
        Nat16     Private_ByteLen;
        Nat8     Private_Byte[40];
        Nat8     DescriptorValid;
    }Linkage_Descriptor[50];
    
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
    }CDSD_Descriptor[10];
    
    Nat8     CDSDDescNum;
    
    struct _TsHDSLCN_Descriptor{
        Nat32     PrivateDataSpecifier;
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     HDSLCNLen;
    struct _TsHDSLCNDesc{
        Nat16     Service_ID;
        Nat8     Visible_Service_Flag;
        Nat8     reserved1;
        Nat16     LCNValue;
    }HDSLCNDesc[50];
        Nat8     DescriptorValid;
        Nat32    prevPrivateDataSpecifier;
    }HDSLCN_Descriptor[10];
    
    Nat8     HDSLCNDescNum;
    
    struct _TsLCN_Descriptor{
        Nat32     PrivateDataSpecifier;
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     LCNLen;
    struct _TsLCNDesc{
        Nat16     ServiceId;
        Nat16     LCNValue;
    }LCNDesc[100];
        Nat8     DescriptorValid;
        Nat32    prevPrivateDataSpecifier;
    }LCN_Descriptor[100];
    
    Nat8     LCNDescNum;
    
    struct _TsLCN2_Descriptor{
        Nat32     PrivateDataSpecifier;
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     LCN2ChannelListLen;
    struct _TsLCN2ChannelLstDesc{
        Nat8     Channel_List_ID;
        Nat8     Channel_List_NameLngth;
        char     Channel_List_Name[MAX_CHANNEL_LIST_NAME_SIZE +1];
        Nat32     Country_Code;
        Nat8     DescriptorLen;
        Nat8     LCN2DescLen;
    struct _TsLCN2Desc{
        Nat16     ServiceId;
        Nat16     LCNValue;
    }LCN2Desc[100];
    }LCN2ChannelLstDesc[10];
        Nat8     DescriptorValid;
		Nat32    prevPrivateDataSpecifier;
    }LCN2_Descriptor[10];
    
    Nat8     LCN2DescNum;
    
    struct _TsFrequencyList_Descriptor{
        Nat32     PrivateDataSpecifier;
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     Reserved;
        Nat8     CodingType;
        Nat8     FrequencyListLen;
    struct _TsFrequencyListDesc{
        Nat32     Center_Frequency;
    }FrequencyListDesc[199];
        Nat8     DescriptorValid;
    }FrequencyList_Descriptor[10];
    
    Nat8     FrequencyListDescNum;
    
    struct _TsService_List_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     ServiceListLen;
    struct _TsServiceListDesc{
        Nat16     ServiceId;
        Nat8     ServiceType;
    }ServiceListDesc[100];
        Nat8     DescriptorValid;
    }Service_List_Descriptor[10];
    
    Nat8     ServiceListDescNum;
    
    struct _TsService_Attribute_Descriptor{
        Nat32     PrivateDataSpecifier;
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     ServiceAttributeLen;
    struct _TsServiceAttributeDesc{
        Nat16     ServiceId;
        Nat8     Reserved;
        Nat8     Numeric_Selection_Flag;
        Nat8     Visible_Service_Flag;
    }ServiceAttributeDesc[100];
        Nat8     DescriptorValid;
        Nat32    prevPrivateDataSpecifier;
    }Service_Attribute_Descriptor[10];
    
    Nat8     ServiceAttrDescNum;
    
    struct _TsExt_TargetRegion_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     DescriptorTagExtn;
        Nat32     CountryCode;
        Nat8     TargetRegionLen;
    struct _TsTargetRegion{
        Nat8     reserved;
        Nat8     CountryCodeFlag;
        Nat8     RegionDepth;
        Nat32     CountryCode;
        Nat32     PrimaryRegionCode;
        Nat32     SecondaryRegionCode;
        Nat32     TertiaryRegionCode;
    }TargetRegion[10];
        Nat8     DescriptorValid;
    }Ext_TargetRegion_Descriptor[10];
    
    Nat8     ExtTargetRegionDescNum;
	
	struct _TsExt_TargetRegionName_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     DescriptorTagExtn;
        Nat32     CountryCode;
        Nat32     LangCode;
        Nat8     TargetRegionNameLen;
    struct _TsTargetRegionName{
        Nat8     RegionDepth;
        Nat8     RegionNameLen;
        Nat8     RegionName[80];
        Nat8     PrimaryRegionCode;
        Nat32     SecondaryRegionCode;
        Nat32     TertiaryRegionCode;
    }TargetRegionName[20];
        Nat8     DescriptorValid;
    }Ext_TargetRegionName_Descriptor[10];
    
    Nat8     ExtTargetRegionNameDescNum;
	
	
	
    }TsLoopData[4];
}TypeNit_Parser;
