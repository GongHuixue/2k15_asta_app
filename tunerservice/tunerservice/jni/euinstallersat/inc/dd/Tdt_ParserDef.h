/*******************************************************************************
*              Copyright(c) 2004  Philips Innovation Campus.
*           All rights reserved. Reproduction in whole or in part is
*        prohibited without the written consent of the copyright holder.
*
*                     Project: SAPI
*                      Source: Include File  
*                    Filename: Tdt_ParserDef.h
*               Creation date: Wed Oct 01 11:37:04 2008 
*                      Author: ing01859
*                 %created_by: lakshminb %
*                    %version: TVG_tv550r4dev %
*              %full_filespec: Tdt_ParserDef.h,TVG_tv550r4dev:h:blr81mgr#4 %
*              %date_modified: Wed Oct 01 11:37:07 2008 %
* 
* Description : 
********************************************************************************
*  Change history      :
*  ---------------
*  VERSION             DATE(MM/DD/YYYY)      NAME             CHANGE DESCRIPTION
*
*******************************************************************************/
#ifndef _TDT_PARSER_H_
#define _TDT_PARSER_H_

typedef struct _Tdt_Parser{
    Nat8     TableId;
    Nat16     SectionLen;
    Nat16     Date;
    Nat32     Time;
}TypeTdt_Parser;

#endif /* _TDT_PARSER_H_ */