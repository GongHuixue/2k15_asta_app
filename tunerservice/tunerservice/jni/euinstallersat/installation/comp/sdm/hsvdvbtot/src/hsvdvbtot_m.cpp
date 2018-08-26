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
 *          %name: hsvdvbtot_m.c %
 *       %version: TVG_tv550r4dev10 %
 * %date_modified: Mon Dec 08 10:51:45 2008 %
 *    %derived_by: ponraman %
 */



#include "_hsvdvbtot_m.h";


TRACESYMBOL(m, "dvb/sitables/hsvdvbtot_m")



#ifndef __cplusplus

#else

#endif



struct _DmxData CHsvDvbTOT_Priv::s__DmxData[HsvDmxLast];






/***************Local Functions******************************************/



/**************************Initialisations*****************************************/








void CHsvDvbTOT_Priv::pow_Init(void)
{
    int dmx;

    for( dmx = (int)HsvDmxMain; dmx < (int)HsvDmxLast; dmx++ )
    {
        /* Clear our structures to ensure that we dont have junk values in them*/
        DmxData[dmx].SubscrId  = HSV_INVALID_SCT_REQUEST;
        DmxData[dmx].SectionInfo[0] = conf_TotParsing;
    }
}

void CHsvDvbTOT_Priv::pow_TurnOn(void)
{
    /* Do Nothing */
}

void CHsvDvbTOT_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbTOT_Priv::ena_Enable(HsvDemux dmx)
{

    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
	
    InitTimeDate(dmx);  
    InitTimeOffset(dmx);    
	/* Initialise Sections */
    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[TOT_INDEX]))
	    {
	        DmxData[dmx].SubscrId  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx), (int)TOT_PID_VALUE ,(int)TOT_TABLE_ID,(int)(&DmxData[dmx].SubscrId ),FNADDR(Tot_Parser_Parser));
	        ASSERT(DmxData[dmx].SubscrId != HSV_INVALID_SCT_REQUEST);                 
	        DmxData[dmx].dt.Version =   HSV_INVALID_VERSION; 
	 }
}

/*This func was provided to enable tot only after collection of freesat tunnelled tot pid from pmt*/
void CHsvDvbTOT_Priv::Freesatena_Enable(HsvDemux dmx){}
/*{
	TraceNotice(m,"Entering Function %s",__FUNCTION__);
	int tunnelled_tot_pid = FREESAT_TUNNELLED_PID_INVALID;
    InitTimeDate(dmx);  
    InitTimeOffset(dmx);*/
    /* Initialise Sections */

/*	if(hsvdvbsdm_div->IsTunnelledExtractionReqd())
	{
		ipmtstrapi->GetByKey(HsvMain,HSVSPID(CurrentTunnelledTOTPid, dvb, pmt),0,0,0,&tunnelled_tot_pid);
	  	TraceNotice(m,"Tunnelled Extraction Required : tunnelled tot pid %d",tunnelled_tot_pid);
	
	    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[TOT_INDEX]) && (!DmxData[dmx].enabled) &&
            ( (eurdiv_GetDVBTMode() != eurdiv_ScanDVBTMpegOnly) || (ins_Cable == ins_GetInstalledMedium()) ) ) 
	    {
	        DmxData[dmx].SubscrId  = sec_RequestSection(HSV_MAP_DMX_TO_DEST(dmx),tunnelled_tot_pid,(int)TOT_TABLE_ID,(int)(&DmxData[dmx].SubscrId ),FNADDR(Tot_Parser_Parser));
	        ASSERT(DmxData[dmx].SubscrId != HSV_INVALID_SCT_REQUEST);                 
	        DmxData[dmx].dt.Version =   HSV_INVALID_VERSION; 
			DmxData[dmx].enabled = true;
	    }
	}
}*/

void CHsvDvbTOT_Priv::Freesatena_Disable(HsvDemux dmx)
{
}
void CHsvDvbTOT_Priv::Freesatena_Sync(HsvDemux dmx)
{
}

void CHsvDvbTOT_Priv::ena_Disable(HsvDemux dmx)
{
	TraceNotice(m,"%s LINE %d",__FUNCTION__,__LINE__);
    /* Initialise Sections */
    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[TOT_INDEX]))
    {
    	TraceNotice(m,"%s LINE %d",__FUNCTION__,__LINE__);
        if( DmxData[dmx].SubscrId != HSV_INVALID_SCT_REQUEST )
        {
        	TraceNotice(m,"%s LINE %d",__FUNCTION__,__LINE__);
            sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx), DmxData[dmx].SubscrId);                                     
            DmxData[dmx].SubscrId = HSV_INVALID_SCT_REQUEST;            
        }

        DmxData[dmx].dt.Version =   HSV_INVALID_VERSION;
		DmxData[dmx].enabled = false;

    }
    InitTimeDate(dmx);
    InitTimeOffset(dmx);
}

void CHsvDvbTOT_Priv::ena_Sync(HsvDemux dmx)
{
    /* TODO */
    UNUSED(dmx);
}

HSVCOMPAREKEY(totmainconf, Primary,     HsvTimeOffsetDescription, CountryId)

HSVCOMPAREKEY(totmainconf, Secondary,   HsvTimeOffsetDescription, Timezone)


#ifndef __cplusplus

Nat8 CHsvDvbTOT_Priv::totmainconf_CompareTeritiaryKey( Nat32 key, Address data )
{
    ASSERT (! "TOT Table does not have a teritiary key" );
    UNUSED(key);
    UNUSED(data);

    return 0;
}

Nat8 CHsvDvbTOT_Priv::totmainconf_CompareQuaternaryKey( Nat32 key, Address data )
{
    UNUSED(key);
    UNUSED(data);
    return FALSE;
}
#else

HSVCOMPAREKEY(totmainconf, Quaternary,   HsvTimeOffsetDescription, Timezone)

HSVCOMPAREKEY(totmainconf, Teritiary,	 HsvTimeOffsetDescription, Timezone)

#endif


Bool CHsvDvbTOT_Priv::ipop_PopulateTOT ( HsvDemux dmx , Address pTot_Parser, int code )
{

    int retval = FALSE;
    TypeTot_Parser* TimeOffsetTable = (TypeTot_Parser*)pTot_Parser;
    if(conf_IsActionAllowed(dmx, DmxData[dmx].SectionInfo[TOT_INDEX]))
    {
        if(TOT_TABLE_ID == TimeOffsetTable->TableId)
        {
            TraceNotice(m,"ipop_PopulateTOT::LINE:%d TimeOffsetTable->TableId:%d,",__LINE__,TimeOffsetTable->TableId);
            DP(("Entered ipop_Populate function after table matching\n\n"));
            PopulateDateTime(dmx, TimeOffsetTable, code);
            PopulateTimeOffset(dmx, TimeOffsetTable, code);
			if( ctrlN_iPresent())
			{
				ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_TOT);
			}

        }
    }
    return retval;
}

void CHsvDvbTOT_Priv::InitTimeDate(HsvDemux dmx)
{
    DmxData[dmx].dt.Version = HSV_INVALID_VERSION;
}

void CHsvDvbTOT_Priv::InitTimeOffset(HsvDemux dmx)
{
    UNUSED (dmx);
    srtdb_Init(srtdbids_TotTableMain);
}




Bool CHsvDvbTOT_Priv::PopulateDateTime (HsvDemux dmx, TypeTot_Parser* TimeOffsetTable,  int code)
{
    // UNUSED (pptyindex);
    if( sec_SctArrived & code )
    {
        IncrementVersion(&(DmxData[dmx].dt.Version));
        dtconv_EncodeDataTime(TimeOffsetTable->Date,
                TimeOffsetTable->Time,
                &(DmxData[dmx].dt.dt));
        TraceNotice(m,"PopulateDateTime::LINE:%d TimeOffsetTable->Date:%d,TimeOffsetTable->Time:%d,\n\n",__LINE__,TimeOffsetTable->Date,TimeOffsetTable->Time);
    }
    return FALSE;   /* To get further sections */

}

Bool CHsvDvbTOT_Priv::PopulateTimeOffset (HsvDemux dmx, TypeTot_Parser* TimeOffsetTable,  int code)
{


    return PopulateTimeOffsetprivate (dmx, TimeOffsetTable, HSVSPID(TimeOffset, dvb, tot), srtdbids_TotTableMain, code);
    DP(("Entered PopulateTimeOffset line 281 executed\n\n"));

}


Bool CHsvDvbTOT_Priv::PopulateTimeOffsetprivate ( HsvDemux dmx, TypeTot_Parser* TimeOffsetTable, int Ppty, int tableid, int code)
{
    int i =0;
    int j = 0;
	int			lCountry;
    UNUSED (Ppty);
    UNUSED (dmx);
    if( sec_SctArrived & code )
    {
        /*
           Dont clear tables here. Versioning is already done inherently
           srtdb_Init ( tableid );
           */
        TraceNotice(m, "Entered PopulateTimeOffsetprivate %d executed", __LINE__);
        int TimeOffsetDescriptionNum = TimeOffsetTable->TimeOffsetDescNum;
           srtdb_Init ( tableid );
        for( i = 0; i < TimeOffsetDescriptionNum; i++)
        {
            if(TimeOffsetTable->TimeOffset_Descriptor[i].DescriptorValid)
            {
                int OffsetDescriptionNum = TimeOffsetTable->TimeOffset_Descriptor[i].OffsetNum;
                for(j = 0; j < OffsetDescriptionNum; j++)
                {
                    HsvTimeOffsetDescription TimeOffsetDescription;
                    HsvTimeOffsetDescription DbaseVersion;

                    TimeOffsetDescription.Version = 0;
                    Nat32 Country_Code = mInterpretCountryCode(TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Code);
/*					lCountry = sysset_GetInstallCountry();

					if(lCountry == cids_CountryBelgium)
					{
						if(Country_Code == cids_CountryNetherlands)
						{
							Country_Code = cids_CountryBelgium;
							//PrintfNotice("Adarsh: Country_Code = %d\n",Country_Code);
						}
					}
                    if(Country_Code == cids_CountryChina)
                    {
                        TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Region_Id = 0;
                    }*/
                    TraceNotice(m,"PopulateTimeOffsetprivate::LINE:%d Country_Code:%d,",__LINE__,Country_Code);
                    if ( srtdb_QueryOnKey( tableid,Country_Code,TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Region_Id , 0, 0, (Address)(&DbaseVersion) ) )
                    {
						DateTime prevChangeDt = DbaseVersion.ChangeDt;
                        TraceNotice(m,"PopulateTimeOffsetprivate::LINE:%d Country_Code:%d, Desc.Country_Region_Id:%d,tableid:%d\n\n",
                             __LINE__, TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Code,
                             TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Region_Id,tableid);
                        DbaseVersion.Polarity      = TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Local_Time_Offset_Polarity ;

                        /* We convert and give now. */
                        /* DVB standard gives time information at the granularity of minutes. infra understands time information at the granularity of seconds */
                        encodeTimeBcd( &DbaseVersion.TimeOffset,  ((TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Local_Time_Offset) << 8) );
                        encodeTimeBcd( &DbaseVersion.NextTimeOffset,  ((TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Next_Time_Offset) << 8) );


                        dtconv_EncodeDataTime(TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].ChangeDate,
                                TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].ChangeTime,
                                &DbaseVersion.ChangeDt);
						/* If Ahead of time ignore .. we will come back to this case anyway .. may be delayed by 20 seconds */
						if (DmxData[dmx].dt.dt >= DbaseVersion.ChangeDt)
						{
                            IncrementVersion(&(DbaseVersion.Version));
                            srtdb_Update(tableid, Country_Code,
                                TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Region_Id , 0, 0,
                                (Address)(&DbaseVersion) );

                        }
                        else
                        {
        						TraceNotice(m,"PopulateTimeOffsetprivate::LINE:%d Country_Code:%d, \
                                    desc.Country_Region_Id:%d,tableid:%d",__LINE__,
                                    TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Code,
                                    TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Region_Id,tableid);
    					}
                        TraceNotice(m,"Update: ChangeDt = %d offset = %d NextTimeOffset = %d", DbaseVersion.ChangeDt, DbaseVersion.TimeOffset, DbaseVersion.NextTimeOffset);
                    }
                    else
                    {
                        TimeOffsetDescription.CountryId     = Country_Code;
                        TimeOffsetDescription.Timezone      = TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Country_Region_Id ;
                        TimeOffsetDescription.Polarity      = TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Local_Time_Offset_Polarity ;
                        /* We encode in BCD and give now */
                        encodeTimeBcd( &TimeOffsetDescription.TimeOffset,        ((TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Local_Time_Offset)<<8) ) ;
                        encodeTimeBcd( &TimeOffsetDescription.NextTimeOffset,    ((TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].Next_Time_Offset) << 8) );

                        TraceNotice(m,"Else part is entered  line %d", __LINE__);
                        dtconv_EncodeDataTime(TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].ChangeDate,
                                TimeOffsetTable->TimeOffset_Descriptor[i].OffsetDesc[j].ChangeTime,
                                &TimeOffsetDescription.ChangeDt);


                        IncrementVersion(&(TimeOffsetDescription.Version));
                        srtdb_Insert( tableid, Country_Code, TimeOffsetDescription.Timezone, 0, 0,(Address)(&TimeOffsetDescription));
                        TraceNotice(m,"Insert: ChangeDt = %d offset = %d NextTimeOffset = %d", TimeOffsetDescription.ChangeDt, TimeOffsetDescription.TimeOffset, TimeOffsetDescription.NextTimeOffset);

                        /* TODO: Do we require notifications. CE requirements says that the system shall update
                           these values in persistant storage every minute. TRS says no
                           */
                    }

                }
            }
        }
    }
    return FALSE;   /* To get further sections */
}

/*************************IHsvStream Implementation *******************************/
Nat32 CHsvDvbTOT_Priv::mInterpretCountryCode( Nat32 country )
{
    /* Examine the lower 3 bytes of the country code and try to determine the corresponding country ID in cids */
    Nat32       retval = cids_CountryOther;
    Nat8        byte1;
    Nat8        byte2;
    Nat8        byte3;
	int			lCountry;

#define HSV_TO_UPPER(x) ( ( (x) >= 'a' && (x) <= 'z' ) ? ( (x) - 'a' + 'A')  : ( (x) ) )


    /* Dont assume case dependency for country codes */
    byte1 = (country & 0xFF);
    byte1 = HSV_TO_UPPER(byte1);

    byte2 = ((country & 0xFF00) >> 8);
    byte2 = HSV_TO_UPPER(byte2);

    byte3 = ((country & 0xFF0000) >> 16);
    byte3 = HSV_TO_UPPER(byte3);

    country = ((byte3 << 16) | (byte2 << 8) | (byte1)) & 0xFFFFFF;

    switch ( (country & 0x00FFFFFF) )
    {
#define COUNTRYITEM(a, b, c)    case a:   \
        retval = cids_Country##b; \
        break;
#ifdef __cplusplus
#include <hsvcountry.h>
#else
#include "../../../prod/hsveur/hsvcountry.h"
#endif
        default:
            break;
            /* Commented to avoid a case where a stream with non supported country can cause this assert
               usually seen in test streams or DTG streams */
            /* ASSERT(FALSE);*/ /* New country Id passed, assert has less impact as we return the cids_CountryOther */

    }

    return retval;

}   /* End of function MapToCountryId() */


/********************************************************************************/



int CHsvDvbTOT_Priv::strapi_GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(DateTime, dvb, tot):
            ASSERT("It is a scalar propert !!!");
            break;
        case HSVSPID(TimeOffset, dvb, tot):
            retval = srtdb_GetNoOfRecords(srtdbids_TotTableMain);
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    return retval;
}

Bool CHsvDvbTOT_Priv::strapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(DateTime, dvb, tot):
            ASSERT("It is a scalar propert !!!");
            break;
        case HSVSPID(TimeOffset, dvb, tot):
            srtdb_SearchOnKey(srtdbids_TotTableMain, key1, key2, key3, 0, (int *)&index);
            DP(("TOT-strapi_GetIndex::LINE:%d (int *)&index:%d\n\n",__LINE__,(int *)&index));
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    return TRUE;
}

Bool CHsvDvbTOT_Priv::strapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);

    /*    if(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable != -1)
          {
          retval = srtdb_QueryOnKey(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable, key1, key2, key3, (Address)val);
          }
          else
          {    Scalar Properties }*/
    switch(prop)
    {
        case HSVSPID(DateTime, dvb, tot):
            {
                if(HSV_INVALID_VERSION != DmxData[demux].dt.Version)
                {
                    HsvDateTime *pval = (HsvDateTime *)val;
                    *pval = DmxData[demux].dt;
                    retval = TRUE;
                }
                break;
            }
        case HSVSPID(TimeOffset, dvb, tot):
			/*if  (key1 == cids_CountryRussia)
			{
				if (sysset_getValue(sysset_Medium) == 2)*/ /* Satellite */
				//{
					/* Key2 becoming 0 is a fallback when there is no LTO found for requested TimeZone. Keep it as such */
				/*	if (key2 != 0)
					{
						switch (key2) 
						{
							case	IHsvTimeZoneSettings_Kalingrad:
								key2 = 6;
								break;
							case	IHsvTimeZoneSettings_Moscow:
								key2 = 5;
								break;
							case	IHsvTimeZoneSettings_Yekaterinburg:
								key2 = 3;
								break;
							case	IHsvTimeZoneSettings_Omsk:
								key2 = 2;
								break;
							case	IHsvTimeZoneSettings_Krasnoyarsk:
								key2 = 1;
								break;
							default:
								break;
						}
					}
		            retval = srtdb_QueryOnKey(srtdbids_TotTableMain, key1, key2, key3,0, (Address)val);
				}
				else
				{
					if (srtdb_GetNoOfRecords(srtdbids_TotTableMain) == 1)
					{*/
						/* Take this value from Index 0, without checking any region */
					/*	retval = srtdb_QueryOnIndex(srtdbids_TotTableMain, 0, (Address)val);
					}
				}
			}
			else*/
			{
				retval = srtdb_QueryOnKey(srtdbids_TotTableMain, key1, key2, key3,0, (Address)val);
			}
            TraceNotice(m,"TOT-strapi_GetByKey::LINE:%d (Address)val:%d\n\n",__LINE__,(Address)val);
            TraceNotice(m,"TOT-strapi_GetByKey::LINE:%d retval:%d\n\n",__LINE__,retval);
            break;
        default:
            ASSERT(!"Unknown Property");
            break;
    }
    return retval;
}

Bool CHsvDvbTOT_Priv::strapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;

    UNUSED (inst);
    switch (prop)
    {
        case HSVSPID(DateTime, dvb, tot):
            ASSERT("It is a scalar propert !!!");
            break;
        case HSVSPID(TimeOffset, dvb, tot):
            retval = srtdb_QueryOnIndex(srtdbids_TotTableMain, index, (Address)val);
            DP(("TOT-strapi_GetByIndex::LINE:%d (Address)val:%d\n\n",__LINE__,(Address)val));
            break;

        default:
            ASSERT(FALSE);
            break;
    }

    return retval;
}

void CHsvDvbTOT_Priv::IncrementVersion (int *version)
{
    (*version)++;
    if(*version == HSV_INVALID_VERSION)
    {
        (*version)++;
    }
}


void CHsvDvbTOT_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
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

Nat8 CHsvDvbTOT_Priv::s__mBuffer[4*1024];


Bool CHsvDvbTOT_Priv::Tot_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
    register Nat8 *ptr = mBuffer;
    register int v32=0;
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);
    TypeTot_Parser Tot_Parser;
    int dummy, loopcount = 0, descTag, descLen = 0, descLoopLen = 0, loop1index = 0, tableLen = 0, loop1length = 0, templen = 0;

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
    memset((void*)(&Tot_Parser),0,(sizeof(Tot_Parser)));
    Tot_Parser.TableId = GETNBITS(v32,0,8);
    dummy = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    Tot_Parser.SectionLen = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    Tot_Parser.Date = GETNBITS(v32,0,16);
    v32 = GET32( 5);
    Tot_Parser.Time = GETNBITS(v32,0,24);
    dummy = GETNBITS(v32,24,4);
    v32 = GET32( 8);
    Tot_Parser.descriptors_loop_length = GETNBITS(v32,4,12);
    ptr += 10;
    tableLen = tableLen - 10;
    v32 = GET32( 0);
    while(loopcount < Tot_Parser.descriptors_loop_length)
    {
        descLoopLen = 0;
        descTag = GETNBITS(v32,0, 8);
        descLen = GETNBITS(v32,8, 8);
        switch(descTag) {
            case 0x58:
                if(Tot_Parser.TimeOffsetDescNum<5)
                {
                    Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].DescriptorTag = GETNBITS(v32,0,8);
                    Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].DescriptorLen = GETNBITS(v32,8,8);

                    ptr += 2;
                    v32 = GET32( 0 );
                    loop1index = 0, loop1length = 0, templen = sizeof(Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc)*50 ;
                    while( loop1length< HSV_PARSER_MIN(Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].DescriptorLen, templen ))
                    {

                        if(loop1index < 20)
                        {
                            Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc[loop1index].Country_Code= GETNBITS(v32,0, 24);
                            Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc[loop1index].Country_Region_Id= GETNBITS(v32,24, 6);
                            Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc[loop1index].reserved1= GETNBITS(v32,30, 1);
                            Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc[loop1index].Local_Time_Offset_Polarity= GETNBITS(v32,31, 1);
                            v32 = GET32( 4);
                            Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc[loop1index].Local_Time_Offset= GETNBITS(v32,0, 16);
                            Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc[loop1index].ChangeDate= GETNBITS(v32,16, 16);
                            v32 = GET32( 8);
                            Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc[loop1index].ChangeTime= GETNBITS(v32,0, 24);
                            v32 = GET32( 11);
                            Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetDesc[loop1index].Next_Time_Offset= GETNBITS(v32,0, 16);
                            // loop1length += 13;
                            loop1index++;
                        }
                        loop1length += 13;
                        ptr += 13;
                        v32 = GET32( 0);
                    }
                    Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].OffsetNum = loop1index;
                    Tot_Parser.TimeOffset_Descriptor[Tot_Parser.TimeOffsetDescNum].DescriptorValid = TRUE;
                    Tot_Parser.TimeOffsetDescNum++;
                }
                else
                {
                    ptr += 2 + descLen;
                }
                loopcount += 2 + descLen;
                tableLen = tableLen - (2 + descLen);

                v32 = GET32( 0);
                break;

            default:
                loopcount += 2 + descLen;
                ptr += 2 + descLen;
                v32 = GET32( 0);
                break;
        }//endswitch
    }//endwhile
    dummy = GETNBITS(v32,0,32);
    return ipop_PopulateTOT(demux, (Address)&Tot_Parser,code);
}//end function

int CHsvDvbTOT_Priv::GetDescriptorIDOntot( int descriptor_tag, int cookie )
{
    UNUSED (descriptor_tag);
    UNUSED (cookie);
    return 0;
}

Bool CHsvDvbTOT_Priv::strapi_GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to)
{
	return FALSE;
}

void CHsvDvbTOT_Priv::dmxsecfN_OnRequestAllowed(HsvDestination dest)
{
}

void CHsvDvbTOT_Priv::dmxsecfN_OnRequestNotAllowed()
{
}

int CHsvDvbTOT_Priv::encodeTimeBcd (DateTime *time, unsigned int timeBCD)
{
    int hr, min, sec;
    int result = 0;

#define BCD2DEC(_bcd) (int)(((((unsigned int)(_bcd)) >> 4) * 10) + (_bcd) % 16)
#define VALIDATE_RANGE(var, floor, ceil) ((var < floor) || (var > ceil))

    hr  = BCD2DEC((timeBCD>>16) & 0xFF);
    min = BCD2DEC((timeBCD>>8) & 0xFF);
    sec = BCD2DEC(timeBCD & 0xFF);

    /* Validate the time */
    if (VALIDATE_RANGE(hr, 0, 23) || VALIDATE_RANGE(min, 0, 59) ||
            VALIDATE_RANGE(sec, 0, 59)) {
        *time = 0;
        result = -1;
    }
    else {
        *time = (DateTime) (sec + (min * 60) + (hr * 60 * 60));
        result = 1;
    }
    return result;
}
