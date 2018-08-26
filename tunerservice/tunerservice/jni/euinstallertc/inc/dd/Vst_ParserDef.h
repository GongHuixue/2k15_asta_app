/*******************************************************************************
*              Copyright(c) 2004  Philips Innovation Campus.
*           All rights reserved. Reproduction in whole or in part is
*        prohibited without the written consent of the copyright holder.
*
*                     Project: SAPI
*                      Source: Include File  
*                    Filename: VstParserDef.h
*               Creation date: Wed Oct 01 11:38:27 2008 
*                      Author: ing01859
*                 %created_by: lakshminb %
*                    %version: TVG_tv550r4dev %
*              %full_filespec: Vst_ParserDef.h,TVG_tv550r4dev:h:blr81mgr#4 %
*              %date_modified: Fri Oct 03 12:20:30 2008 %
* 
* Description : 
********************************************************************************
*  Change history      :
*  ---------------
*  VERSION             DATE(MM/DD/YYYY)      NAME             CHANGE DESCRIPTION
*
*******************************************************************************/
#ifndef _VST_PARSER_H_
#define _VST_PARSER_H_

#include <unistd.h>

typedef struct _Vst_Parser{
    Nat8     TableId;
    Nat16     SectionLen;
    Nat16     Date;
    Nat32     Time;
}TypeVst_Parser;

#define TVID_FILE_PATH "/user_setting/HTV/Vsecure/PHTVCK001T"
#define EKSHARE_FILE_PATH "/user_setting/HTV/Vsecure/PHTVCK001S"
#define EKEVEN_FILE_PATH "/user_setting/HTV/Vsecure/PHTVCK001E"
#define EKODD_FILE_PATH "/user_setting/HTV/Vsecure/PHTVCK001O"
#define VSECKEY_FILE_PATH "/user_setting/HTV/Vsecure/vseckeys.txt"

#define TRACE_MODULE_ID         	HTV_TRACE_MODULE_HTVAPP
#define SECTION_HEADER_SIZE       	8	 
#define TABLE_BYTE                 	3
#define SECTION_BYTE               	6
#define DATA_HEADER_SIZE          	20
#define HSV_SECTION_BUFFER_SIZE 	(1024*8)
#define MAX_SCT_FLT_DEPTH 			(12)
#define MAX_DATA_PER_SECTION    	4096
#define BUFFER_SIZE               	(16 * 1024)
#define MAX_SECTION_POSSIBLE      	256
#define SECTION_PAYLOAD           	(MAX_DATA_PER_SECTION - SECTION_HEADER_SIZE - CRC_SIZE)
#define CRC_SIZE                  	4
#define INVALID_INDEX				-1
#define MAX_SECTION_FILTERS       	10
#define RF_DYNAMIC_SECTION        	(2)
#define WRITE_OFFSET(table,section) (((table)*(MAX_SECTION_POSSIBLE)* SECTION_PAYLOAD) + (section * SECTION_PAYLOAD) - (DATA_HEADER_SIZE)) 
#define HSV_INVALID_VERSION         (-1)
#define TM_OK 11 
#define RF_STATIC_SECTION         (0)
#define MAX_RF_SECTION_TYPES      (3)

#define FSYNC(f)                  fsync(fileno(f))
#define CRC_CHECK  1

#define iVseckpN_TvIdLength                 ((unsigned char)10)
#define iVseckpN_EkShareKeyLength           ((unsigned short int)256)
#define iVseckpN_EkScrambleKeyLength        ((unsigned char)16)


#define ASCII_CR                (0x0D)
#define ASCII_LF                (0x0A)
#define ASCII_WS                (0x20)
#define ASCII_PLUS              ('+')
#define ASCII_0                 (0x30)
#define ASCII_9                 (0x39)
#define ASCII_A                 (0x41)
#define ASCII_F                 (0x46)
#define ASCII_a                 (0x61)
#define ASCII_f                 (0x66)


#define MAX_KEY_BUFFER_LEN              (512)
#define iVseckpN_TvIdLength	((uint8_t)10)
#define iVseckpN_EkScrambleKeyLength	((uint8_t)16)
#define iVseckpN_EkShareKeyLength	((unsigned short int)256)
#define iVseckpN_EKKeysFound	((uint8_t)0)
#define iVseckpN_SyntaxError	((uint8_t)6)
#define iVseckpN_TvIdNotFound	((uint8_t)5)
#define iVseckpN_VsecKeyFileNotPresent	((uint8_t)3)
#define iVseckpN_UsbNotConnected	((uint8_t)1)
#define iVseckpN_CertificateLength	((unsigned short int)960)
#define iVseckpN_PublicKeysNotFound	((uint8_t)2)

typedef struct
{
    char    Header[SECTION_HEADER_SIZE];
    Nat8 SectionBuff[MAX_DATA_PER_SECTION] ;
    Nat32   Size;
    Nat32   Offset;
    Bool    ReturnVal;
    Bool    State;
    char    Subtable;
    char    Section;
}RfdSectionFilterType;

typedef enum
{
	EvStore,
	EvComplete,
    EvAbort
}event;

typedef struct
{
    Nat32 SubscrId;
    Nat32 SubsrcPid;
    Nat8  CurrentVersion;
}RfdFilterData;

typedef enum
{
    StIdle = 0,
    StTuning,
    StReqFilter,
    StDownLoading,
    StKeyProcessing
}VsecDlState;

typedef enum
{
        WT_unknown = 0
    ,   WT_ID
    ,   WT_Ekshared
    ,   WT_EkOdd
    ,   WT_EkEven
    ,   WT_comment
}WORD_TYPE;

typedef enum
{
        PSIdle      = 0
    ,   PSParsing
}ParserState;



#endif /* _VST_PARSER_H_ */
