/*******************************************************************************
*              Copyright(c) 2004  Philips Innovation Campus.
*           All rights reserved. Reproduction in whole or in part is
*        prohibited without the written consent of the copyright holder.
*
*                     Project: SAPI
*                      Source: Include File
*                    Filename: TotParserDef.h
*               Creation date: Wed Oct 01 11:38:27 2008
*                      Author: ing01859
*                 %created_by: lakshminb %
*                    %version: TVG_tv550r4dev %
*              %full_filespec: Tot_ParserDef.h,TVG_tv550r4dev:h:blr81mgr#4 %
*              %date_modified: Fri Oct 03 12:20:30 2008 %
*
* Description :
********************************************************************************
*  Change history      :
*  ---------------
*  VERSION             DATE(MM/DD/YYYY)      NAME             CHANGE DESCRIPTION
*
*******************************************************************************/
#ifndef _TOT_PARSER_H_
#define _TOT_PARSER_H_

typedef struct _Tot_Parser{
    Nat8     TableId;
    Nat16     SectionLen;
    Nat16     Date;
    Nat32     Time;
    Nat16     descriptors_loop_length;

    struct _TimeOffset_Descriptor{
        Nat8     DescriptorTag;
        Nat8     DescriptorLen;
        Nat8     OffsetNum;
    struct _OffsetDesc{
        Nat32     Country_Code;
        Nat8     Country_Region_Id;
        Nat8     reserved1;
        Nat8     Local_Time_Offset_Polarity;
        Nat16     Local_Time_Offset;
        Nat16     ChangeDate;
        Nat32     ChangeTime;
        Nat16     Next_Time_Offset;
    }OffsetDesc[20];
        Nat8     DescriptorValid;
    }TimeOffset_Descriptor[5];

    Nat8     TimeOffsetDescNum;
}TypeTot_Parser;

#endif /* _TOT_PARSER_H_ */
