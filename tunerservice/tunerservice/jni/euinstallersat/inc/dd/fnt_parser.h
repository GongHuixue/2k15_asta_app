/*
 *  Copyright(C) 2002 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.      
 *     
*	 %name:		fnt_parser.h %
*             %version: TVG_3 %
*	%created_by:	shreeshav %
*	%date_created:	Tue Aug 28 11:24:20 2012 %
*             %date_modified: Thu Feb 26 12:31:08 2009 %
*             %derived_by: shreeshav %                  
 *############################################################
 */

struct _FntNetworkName_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     NetworkNameLen;
    char     NetworkName[80];
    Nat8     DescriptorValid;
};

struct _TsSDSD{
	Nat32     Frequency;
	Nat16     OrbitalPostion;
	Nat8     WestEastFlag;
	Nat8     Polarization;
	Nat8     RollOff;
	Nat32     Modulationsystem;
	Nat8     Modulationtype;
	Nat32     SymbolRate;
	Nat8     FEC_Inner;
};

struct _TsSDSD_Descriptor{
	Nat8     DescriptorTag;
	Nat8     DescriptorLen;
	Nat8     SDSDLen;
	struct _TsSDSD SDSD[40];
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

struct _TsLCNDesc{
		Nat16     ServiceId;
		Nat8     Hidden;
		Nat16     LCNValue;
};

struct _TsLCNM7_Descriptor{
	Nat8     DescriptorTag;
	Nat8     DescriptorLen;
	Nat8     LCNLen;
	struct _TsLCNDesc LCNDesc[100];
	Nat8     DescriptorValid;
};

struct _FntTsLoopData{
	Nat16     TSID;
	Nat16     ONID;
	Nat16     TsDescLoopLen;

	struct _TsSDSD_Descriptor SDSD_Descriptor[10];
	Nat8     SDSDDescNum;

	struct _TsService_List_Descriptor Service_List_Descriptor[10];
	Nat8     ServiceListDescNum;

	struct _TsLCNM7_Descriptor LCNM7_Descriptor[10];

	Nat8     LCNM7DescNum;
};

typedef struct _fnt_parser{
    Nat8     TableId;
    Nat16     SectionLen;
    Nat16     NetworkId;
    Nat8     VersionNo;
    Nat16     NetworkDescLen;

	struct _FntNetworkName_Descriptor NetworkName_Descriptor;    
	Nat8     NtkNameDescNum;

	Nat16     TsLoopLen;
	Nat8     TsLoopDataNum;
	struct _FntTsLoopData TsLoopData[2];
}Typefnt_parser;
