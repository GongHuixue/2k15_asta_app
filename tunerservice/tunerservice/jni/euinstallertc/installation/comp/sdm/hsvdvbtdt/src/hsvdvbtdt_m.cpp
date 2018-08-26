/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: hsvdvbtdt_m.c %
 *       %version: TVG_tv550r4dev3 %
 * %date_modified: Tue Dec 23 20:24:24 2008 %
 *    %derived_by: vijayan %
 */


#include "_hsvdvbtdt_m.h"

TRACESYMBOL(m, "dvb/sitables/hsvdvbtdt_m")

//#include "Parser.h"


#ifndef __cplusplus

#else

#endif




struct _DmxData CHsvDvbTDT_Priv::s__DmxData[HsvDmxLast];




/***************Local Functions******************************************/



/**************************Initialisations*****************************************/





void CHsvDvbTDT_Priv::pow_Init(void)
{
    HsvDemux dmx;    

    for( dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {        
        /* Clear our structures to ensure that we dont have junk values in them*/
        DmxData[dmx].SubscrId  = HSV_INVALID_SCT_REQUEST;
        DmxData[dmx].SectionInfo[0] = 0x0100;
        DmxData[dmx].dt.Version = HSV_INVALID_VERSION;
    }        
}

void CHsvDvbTDT_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbTDT_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbTDT_Priv::ena_Enable(HsvDemux dmx)
{


    InitDateTime(dmx);
    /* Initialise Sections */
    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[TDT_INDEX]) &&
            ( (eurdiv_GetDVBTMode() != eurdiv_ScanDVBTMpegOnly) || (ins_Cable == ins_GetInstalledMedium()) ) ) 
    {
        DmxData[dmx].dt.Version =   HSV_INVALID_VERSION;
        DmxData[dmx].SubscrId  = sec_RequestSection(HsvDmxMain, (int)TDT_PID_VALUE, (int)TDT_TABLE_ID,(int)(&DmxData[dmx].SubscrId ), FNADDR(Tdt_Parser_Parser));
        ASSERT(DmxData[dmx].SubscrId != HSV_INVALID_SCT_REQUEST);                 
    }
}

void CHsvDvbTDT_Priv::ena_Disable(HsvDemux dmx)
{
    /* Initialise Sections */
    if( conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[TDT_INDEX]) && 
            ( (eurdiv_GetDVBTMode() != eurdiv_ScanDVBTMpegOnly) || (ins_Cable == ins_GetInstalledMedium()) ) )  
    {
        if( DmxData[dmx].SubscrId != HSV_INVALID_SCT_REQUEST )
        {
            sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxData[dmx].SubscrId);
            DmxData[dmx].SubscrId = HSV_INVALID_SCT_REQUEST ;
        }        
        DmxData[dmx].dt.Version =   HSV_INVALID_VERSION;

    }
    InitDateTime(dmx);
}

void CHsvDvbTDT_Priv::ena_Sync(HsvDemux dmx)
{
    UNUSED (dmx);
    /* TODO */
}

Bool CHsvDvbTDT_Priv::ipop_PopulateTDT ( HsvDemux   dmx, Address pTdt_Parser, int code )
{

    TypeTdt_Parser* TimeDateTable = (TypeTdt_Parser*)pTdt_Parser;  
    return PopulateTimeDate ( dmx, TimeDateTable, 0, 0, code);
}

void CHsvDvbTDT_Priv::InitDateTime(HsvDemux dmx)
{
    DmxData[dmx].dt.Version = HSV_INVALID_VERSION;
}


Bool CHsvDvbTDT_Priv::PopulateTimeDate ( HsvDemux dmx, TypeTdt_Parser* TimeDateTable, int Ppty, int tableid, int code)
{
    UNUSED (Ppty);
    UNUSED (tableid);
    if( sec_SctArrived & code )
    {
        if(TimeDateTable->TableId == TDT_TABLE_ID)
        {
            IncrementVersion(&(DmxData[dmx].dt.Version));
            dtconv_EncodeDataTime(TimeDateTable->Date, TimeDateTable->Time, &(DmxData[dmx].dt.dt));
        }
    }
    return FALSE;   /* To get further sections */
}


/*************************IHsvStream Implementation *******************************/


int CHsvDvbTDT_Priv::strapi_GetSize   (HsvDestination inst, int prop)
{

    UNUSED (inst);
    UNUSED (prop);
    ASSERT(!"Not to be called");
    return 0;
}

Bool CHsvDvbTDT_Priv::strapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    UNUSED (inst);
    UNUSED (prop);
    UNUSED (key1);
    UNUSED (key2);
    UNUSED (key3);
    UNUSED (index);
    ASSERT(!"Not to be called");
    return TRUE;
}

Bool CHsvDvbTDT_Priv::strapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    int retval = FALSE;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);

    UNUSED (prop);
    UNUSED (key1);
    UNUSED (key2);
    UNUSED (key3);

    if(HSV_INVALID_VERSION != DmxData[demux].dt.Version)
    {    
        HsvDateTime *pval = (HsvDateTime *)val;
        *pval = DmxData[demux].dt;
        retval = TRUE;
    }
    return retval;
}

Bool CHsvDvbTDT_Priv::strapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    UNUSED (inst);
    UNUSED (prop);
    UNUSED (index);
    UNUSED (val);
    ASSERT(!"Not to be called");
    return TRUE;
}


void CHsvDvbTDT_Priv::IncrementVersion (int *version)
{
    (*version)++;
    if(*version == HSV_INVALID_VERSION)
    {
        (*version)++;
    }
}


void CHsvDvbTDT_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
{
    int dmx = HsvDmxMain;

    for(  dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {
        if( DmxData[dmx].SubscrId == subscrid )
        {
            /* This was a matching request. Clear our local variables */
            DmxData[dmx].SubscrId  = HSV_INVALID_SCT_REQUEST;
        }
    }
}

Nat8 CHsvDvbTDT_Priv::s__mBuffer[4*1024];

Bool CHsvDvbTDT_Priv::Tdt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
    register Nat8 *ptr = mBuffer;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    TypeTdt_Parser Tdt_Parser;      
    int dummy, tableLen = 0; 

    UNUSED (cookie);
    UNUSED (crc);
    if(secondarySectionSize > 0)
    {
        memcpy(ptr,PrimarySectionStartAddress,primarySectionSize);
        memcpy((ptr+primarySectionSize),SecondarySectionStartAddress,secondarySectionSize);

    }
    else
    {
        ptr = PrimarySectionStartAddress;
    }
    v32 = GET32(0); 

    tableLen = HSV_GETSECTION_LENGTH(ptr);
    memset((void*)(&Tdt_Parser),0,(sizeof(Tdt_Parser)));
    Tdt_Parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    Tdt_Parser.SectionLen = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    Tdt_Parser.Date = GETNBITS(v32,0,16);
    v32 = GET32( 5);
    Tdt_Parser.Time = GETNBITS(v32,0,24);
    v32 = GET32( 8);
    dummy = GETNBITS(v32,0,32);
    return ipop_PopulateTDT(demux, (Address)&Tdt_Parser,code);      
}//end function

int CHsvDvbTDT_Priv::GetDescriptorIDOntdt( int descriptor_tag, int cookie )
{
    UNUSED (descriptor_tag);
    UNUSED (cookie);
    return 0;
}

Bool CHsvDvbTDT_Priv::strapi_GetRangeByKey(HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
    return FALSE;
}

void CHsvDvbTDT_Priv::dmxsecfN_OnRequestAllowed(HsvDestination dest)
{
    return;
}

void CHsvDvbTDT_Priv::dmxsecfN_OnRequestNotAllowed(void)
{
    return;
}