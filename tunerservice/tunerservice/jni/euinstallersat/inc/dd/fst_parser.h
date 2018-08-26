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
*	 %name:		fst_parser.h %
*             %version: TVG_2 %
*	%created_by:	shreeshav %
*	%date_created:	Tue Aug 28 11:24:42 2012 %
*             %date_modified: Thu Feb 26 12:31:08 2009 %
*             %derived_by: shreeshav %                  
 *############################################################
 */

struct _TsService_Descriptor{
    Nat8     DescriptorTag;
    Nat8     DescriptorLen;
    Nat8     ServiceType;
    Nat8     ProviderNameLen;
    char     ProviderName[80];
    Nat8     ServiceNameLen;
    char     ServiceName[80];
    Nat8     DescriptorValid;
};

struct _FstTsLoopData{
	Nat16     original_network_id;
	Nat16     Transport_stream_id;
	Nat16     service_id;
	Nat16     Default_video_PID;
	Nat16     Default_audio_PID;
	Nat16     Default_video_ECM_PID;
	Nat16     Default_audio_ECM_PID;
	Nat16     Default_PCR_PID;
	Nat8     reserved4;
	Nat16     Descriptor_loop_length;

	struct _TsService_Descriptor Service_Descriptor[100];
	Nat8     ServiceDescNum;
};

typedef struct _fst_parser{
    Nat8     TableId;
    Nat16     SectionLen;
    Nat16     NetworkId;
    Nat8     VersionNo;
    Nat8     TsLoopDataNum;
	struct _FstTsLoopData TsLoopData[2];
}Typefst_parser;
