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
 *          %name: hsvdvbeit_m.c % 
 *       %version: cltv1_fusion_2 %
 * %date_modified: Wed Mar 11 19:18:07 2009 %
 *    %derived_by: lakshminb %
 */


#include "_hsvdvbeit_m.h"

TRACESYMBOL(m, "dvb/sitables/hsvdvbeit_m")




#ifdef WIN32

#else

#endif




                                                
                                                
            Nat8 CHsvDvbEIT_Priv::s__EPGData[MAX_EPG_SIZE];


			



#ifndef __cplusplus

#else

#endif




 

 


 
 


/******************************Constants***************************/


Bool CHsvDvbEIT_Priv::s__mSubscribeEpg4to8days   = FALSE;
 
Bool CHsvDvbEIT_Priv::s__EitSchedParsingStarted = FALSE;

/* To be handled in egpApp
static void SubscribeForEitSched( HsvDemux dmx, int svcid );*/




Bool CHsvDvbEIT_Priv::s__EnableNowNextInfoReset      = TRUE;

int CHsvDvbEIT_Priv::s__LinkageInfoVersionNumber    = -1;



struct DmxData_t CHsvDvbEIT_Priv::s__DmxData[HsvDmxLast];

/***************Local Functions******************************************/








/**************************Initialisations*****************************************/

void CHsvDvbEIT_Priv::pow_Init(void)
{
    HsvDemux dmx;
    int      i;

    for( dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
    {        
        for(i = 0; i < MAX_SECTIONS; i++)
        {
            /* Clear our structures to ensure that we dont have junk values in them*/
            DmxData[dmx].SubscrId[i]  = HSV_INVALID_SCT_REQUEST;
        }
        CLEAR_DATA
    }

    /* Clear our data valid structures */
}

void CHsvDvbEIT_Priv::pow_TurnOn(void)
{
    /* Do Nothing */    
}

void CHsvDvbEIT_Priv::pow_TurnOff(void)
{
    /* Do Nothing */
}

void CHsvDvbEIT_Priv::ena_Enable(HsvDemux dmx)
{

    /* Initialise Sections */
    int i;
    int j;
    Bool Proceed = TRUE;
    Nat16 TableId =0;

    /*  Initialise Tables. Prepare for the incoming EIT */
   


    /* Start setting up the section filters */
    for(i = 0; i < MAX_SECTIONS; i++)
    {
        Proceed = TRUE;
        TableId = 0x4e ;

        if(EIT_8DAYS_DATA_NOTREQ(TableId) || EIT_OTHER_PF_DATA_NOTREQ(TableId)) // EPG sched data for 4 to 8 days
        {                     
            Proceed = FALSE;
        }
        if(Proceed && conf_IsActionAllowed(dmx, conf_EitNowNextActualParsing))
        {
            int         svcid           =0;
            int         onwid           =0;
            int         tsid            =0;


            if( dvbsvc_GetCurrentService2( dmx, &onwid, &tsid,&svcid) )
            {
                /* Create mode, match and mask arrays for the section filter we are interested in */
                Nat8                    ModeArray [ SCT_FLT_DEPTH ];
                Nat8                    MaskArray [ SCT_FLT_DEPTH ];
                Nat8                    MatchArray[ SCT_FLT_DEPTH ];
                HsvSectionFilterListConfig  sctconfig;

                /* Clear the mode, match and mask arrays of all junk values */
                for( j = 0; j < SCT_FLT_DEPTH; j++ )
                {
                    ModeArray[j] = MatchArray[j] = MaskArray[j] = 0;
                }


                /* Store the table_id field */
                MatchArray[TABLEID_FIELD]           = (Nat8)(0x4e);
                MaskArray [TABLEID_FIELD]           = TABLEID_MASK;
                ModeArray [TABLEID_FIELD]           = 0x00;

                /* Table ID extension is a 2 byte field */
                /* Ensure that we copy the lower 16 bits of the filter value into this field */
                /* This represents the service_id which we want to filter */
                MatchArray[TABLE_ID_EXTN_FIELD]     = (Nat8)(((svcid) & 0xFF00) >> 8 );
                MatchArray[TABLE_ID_EXTN_FIELD + 1] = (Nat8)(((svcid) & 0xFF));

                /* We are interested in both bytes. Set the mask accordingly  */
                MaskArray [TABLE_ID_EXTN_FIELD]     = 0xFF;
                MaskArray [TABLE_ID_EXTN_FIELD + 1] = 0xFF;


                /* We dont want negative filtering */
                ModeArray [TABLE_ID_EXTN_FIELD]     = 0x00;
                ModeArray [TABLE_ID_EXTN_FIELD + 1] = 0x00;

                MatchArray[SECTION_NUMBER_FIELD]    = (Nat8)(i);            
                MaskArray [SECTION_NUMBER_FIELD]    = SECTION_NUMBER_MASK;
                ModeArray [SECTION_NUMBER_FIELD]    = 0x00;                 

                /* Set up the configuration parameters */
                sctconfig.BufferSize        = EIT_SECTION_BUFFER_SIZE;
                sctconfig.CrcMode           = HsvCrcModeSkipBadSections;
                sctconfig.ContinuousMode    = TRUE;      
                sctconfig.cookie            = (int)(&(DmxData[dmx].SubscrId[i]));
                sctconfig.pid               = (int)EIT_PID_VALUE;
                sctconfig.TimeOut           = EIT_SECFLTR_LIST_TIMEOUT;
                sctconfig.ListLength        = EIT_SECFLTR_LIST_LENGTH;  //PED ; added

                /* Check if we had a valid request before. If so, cancel it */
                /* Subscribe only for the first section. The next is going to be a duplicate anyways */
                if( DmxData[dmx].SubscrId[i] != HSV_INVALID_SCT_REQUEST )
                {
                    sec_CancelSection( HSV_MAP_DMX_TO_DEST(dmx), DmxData[dmx].SubscrId[i] ); //PED first parameter added
                    DmxData[dmx].SubscrId[i] = HSV_INVALID_SCT_REQUEST;
                }

                DmxData[dmx].SubscrId[i]  = sec_RequestSectionFilterList(HsvDmxMain,
                 &sctconfig, SCT_FLT_DEPTH , ModeArray, MatchArray, MaskArray,
                 FNADDR(EITParser));  // NDC remove hardcode after koala rebuild
                //ASSERT(DmxData[dmx].SubscrId[i] != HSV_INVALID_SCT_REQUEST);                 
            }
        }
        else
        {
            if( (i == EIT_SCHED_ACTUAL4_INDEX ) || (i == EIT_SCHED_ACTUAL8_INDEX ))
            {
                int svcid = 0;
                if( dvbsvc_GetActualEitSchedService( dmx, &svcid ) )
                {
                    /* Handled in epgApp
                    SubscribeForEitSched( dmx, svcid );*/
                }
            }
        }
    }

    /* Invalidate our data cache */
    if(EnableNowNextInfoReset)
    {
        CLEAR_DATA
    }
}

void CHsvDvbEIT_Priv::ena_Disable(HsvDemux dmx)
{
    int i;
    /* Initialise Sections */
    for(i = 0; i < MAX_SECTIONS; i++)
    {
        if(conf_IsActionAllowed(dmx, conf_EitNowNextActualParsing))  
        {
            if( DmxData[dmx].SubscrId[i] != HSV_INVALID_SCT_REQUEST )
            {
                sec_CancelSection(HSV_MAP_DMX_TO_DEST(dmx),DmxData[dmx].SubscrId[i]); //PED first param added
                DmxData[dmx].SubscrId[i] = HSV_INVALID_SCT_REQUEST ;
            }
        }
    }
    /*  Initialise Tables */    
    for(i = 0 ; i < MAX_PROPERTIES; i++)
    {
        if( (conf_IsActionAllowed(dmx, conf_EitNowNextActualParsing)) && 
                ( DmxData[dmx].TableIds[i] != HSV_INVALID_TABLE_ID) && EnableNowNextInfoReset )
        {                                                   
            //srtdb_Init ( DmxData[dmx].TableIds[i] );                                               
        }
    }

    if(EnableNowNextInfoReset)
    {
        CLEAR_DATA
            strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HsvdvbeitActualPresentRatingProperty, HSV_INVALID_KEY, HSV_INVALID_KEY,HSV_INVALID_KEY);
    }
}


void CHsvDvbEIT_Priv::ena_Sync(HsvDemux dmx)
{
    UNUSED( dmx );
}


Bool CHsvDvbEIT_Priv::PopulateEIT ( HsvDemux dmx, HsvEITTable *EITTable, int code )
{    
    int retval = FALSE;
    int i = 0;

    HsvEITSectionType EITType = HsvdvbeitLastSection;

    if( (EIT_ACTUAL_PF_TABLEID == EITTable->TableId) || (EIT_OTHER_PF_TABLEID == EITTable->TableId) )
    {       
        //if(EnableNowNextInfoReset)
        {   
            if((EITTable->section_number == 0 )||(EITTable->section_number == 1) )
            {
                if( iparconst_HeaderParsed == code )           
                {
                    retval = TRUE;
                }
                else
                {                     
                    PopulateEIT_PF(dmx, EITTable, i, EITType, code);
                    PopulateLinkage(dmx, EITTable, i, EITType, code);
                    if(EITTable->section_number == 0 )  //rating only for present event
                    {
                        PopulateRating(dmx, EITTable, i, EITType, code);
                    }                     
                    retval = TRUE;
                }
            }
            else
            {
                retval = FALSE;;
            }
        }

    }
    else if( 
            ( (EITTable->TableId == EIT_SCHED_ACTUAL4_TABLEID)||(EITTable->TableId == EIT_SCHED_ACTUAL8_TABLEID)|| 
              (EITTable->TableId == EIT_SCHED_OTHER4_TABLEID)||(EITTable->TableId == EIT_SCHED_OTHER8_TABLEID))&&(EitSchedParsingStarted) )         
    {
        //add for loop
        TraceDebug(m,"EIT SCHEDULE tbl ");
//        retval =  PopulateEIT_Sched(dmx, EITTable, i, EITType, code);
        
        
    }    

    DmxData[dmx].ValidTable = TRUE;    
    TraceDebug(m,"SREE: EITTable->TableId = 0x%x EITType = %d ,section_number = %d  ",EITTable->TableId ,EITType ,EITTable->section_number); 
    TraceDebug(m,"POPU EIT retval = %d code = %d ",retval,code);
    return retval;
}


/* EIT has to be flushed explicitly by changes in SDT.
   We dont get to know if the event description for a service is no longer transmitted.

*/

Bool CHsvDvbEIT_Priv::PopulateEIT_PF ( HsvDemux   dmx, HsvEITTable *EITTable, int pptyindex, int secindex, int code)
{
#if 0 //TvSvr
    /*Bool retval = FALSE;*/
    HsvEITSection DbaseVersion; 
    HsvEITSection EITSection; 
    HsvDVBPropertyType ppty     = DmxROMData[dmx].PropertyInfo[pptyindex].property;
    int tableid                 = DmxROMData[dmx].PropertyInfo[pptyindex].dbtable;
    int index = 0;
    Bool Proced = FALSE;

    if(EITTable->section_number == 0)
    {
        tableid =  srtdbids_EitPresentActual;
        ppty =  HsvdvbeitActualEITPresentProperty;
        Proced = TRUE;
    }
    else if(EITTable->section_number == 1)
    {
        tableid =  srtdbids_EitFollowActual;
        ppty =  HsvdvbeitActualEITFollowProperty;
        Proced = TRUE;
    }
    if ( Proced && (EITTable->TableId == EIT_OTHER_PF_TABLEID)/* &&  (sysset_GetSystemCountry() == cids_CountryChina)*/ )
    {
        int     onwid   = 0;
        int     tsid   = 0;
        int     svcid   = 0;            

        Proced = FALSE;        

        if( dvbsvc_GetCurrentService2( dmx, &onwid,&tsid, &svcid) )
        {
            if ((svcid == EITTable->service_id) &&
                    (onwid == EITTable->original_network_id)&&
                    (tsid == EITTable->transport_stream_id))
            {
                Proced = TRUE;
            }
        }

    }
    UNUSED( code );
    UNUSED( secindex );
    TraceDebug(m,"SREE: EITTable->TsLoopDataNum = %d tableid = %d ppty = %d pptyindex = %d  ",EITTable->TsLoopDataNum ,tableid,ppty,pptyindex);

    if( (iparconst_DataParsed == code ) &&(Proced == TRUE))
    {
        //for(index = 0 ;index < EITTable->TsLoopDataNum;index++)
        if(EITTable->TsLoopData[index].ShortEventNum > 0)
        {
            TraceDebug(m,"ONID = %d , TSID = %d, SID = %d ",EITTable->original_network_id,EITTable->transport_stream_id,EITTable->service_id);
            TraceDebug(m,"duration = %d ",EITTable->TsLoopData[index].duration);
            TraceDebug(m,"event_id = %d StartDate = 0x%x StartTime = 0x%x duration = %d  ",EITTable->TsLoopData[index].event_id,EITTable->TsLoopData[index].StartDate ,EITTable->TsLoopData[index].StartTime ,EITTable->TsLoopData[index].duration);

            {
                if( srtdb_QueryOnKey( tableid, EITTable->original_network_id,EITTable->transport_stream_id,EITTable->service_id, EITTable->service_id, (Address)(&DbaseVersion) ) )
                {   
                    // trigger notifitication that the currently viewed event number has changed
                    if( ( eitevtN_iPresent() )
                            &&( div_ReapplyChildLockOnEventChange() )
                            &&( ppty ==  HsvdvbeitActualEITPresentProperty ) 
                            &&( DbaseVersion.EventId != EITTable->TsLoopData[index].event_id ) 
                      )
                    {
                        int     onwid   = 0;
                        int     tsid   = 0;
                        int     svcid   = 0;            

                        if( dvbsvc_GetCurrentService2( dmx, &onwid,&tsid, &svcid) )
                        {
                            if ((svcid == EITTable->service_id) &&
                                    (onwid == EITTable->original_network_id)&&
                                    (tsid == EITTable->transport_stream_id))
                            {
                                eitevtN_OnEvent( 0 );
                            }
                        }
                    }
                    TraceDebug(m,"inside  IF  -------- ");
                    /* Record Exists - Update the information & notify if needed*/
                    DbaseVersion.EventId              =   EITTable->TsLoopData[index].event_id; 
                    DbaseVersion.Duration             =   EITTable->TsLoopData[index].duration;
                    DbaseVersion.TableId              =   EITTable->TableId;
                    //DbaseVersion.RunningStatus        =   EITTable->TsLoopData[index].RunningStatus;
                    //DbaseVersion.Free_CA_Mode         =   EITTable->TsLoopData[index].FreeCAMode;        

                    dtconv_EncodeDataTime(EITTable->TsLoopData[index].StartDate, EITTable->TsLoopData[index].StartTime, &DbaseVersion.dt);

                        /*AssignContentDescriptor(EITTable, index, &DbaseVersion);
                        AssignShortEventDescriptor(dmx, EITTable, index, &DbaseVersion);
                        PopulateExtendedInfo( dmx, EITTable, index);*/


                    if( srtdb_Update(tableid, EITTable->original_network_id, EITTable->transport_stream_id,EITTable->service_id,EITTable->service_id,(Address)(&DbaseVersion)) )
                    {
                        TraceDebug(m,"HYSVC :strapiN_OnChanged  ");
                        strapiN_OnChanged( HSV_MAP_DMX_TO_DEST(dmx), ppty, EITTable->original_network_id, EITTable->transport_stream_id,EITTable->service_id,  HsvEvtNull );
                    }
                    else
                    {
                        TraceDebug(m,"HYSVC :srtdb_Update FAILURE  ");
                    }


                }
                else
                {
                    TraceDebug(m,"IN ELSE --------");
                    EITSection.Original_NetworkId   =   EITTable->original_network_id;
                    EITSection.TsId                 =   EITTable->transport_stream_id;
                    EITSection.ServiceId            =   EITTable->service_id;
                    EITSection.EventId              =   EITTable->TsLoopData[index].event_id; 
                    EITSection.Duration             =   EITTable->TsLoopData[index].duration;
                    EITSection.TableId              =   EITTable->TableId;
                    //EITSection.RunningStatus        =   EITTable->EITDATA[0].RunningStatus;
                    //EITSection.Free_CA_Mode         =   EITTable->EITDATA[0].FreeCAMode;        

                    dtconv_EncodeDataTime(EITTable->TsLoopData[index].StartDate, EITTable->TsLoopData[index].StartTime, &EITSection.dt);

                /*AssignContentDescriptor(EITTable, index, &EITSection);
                AssignShortEventDescriptor(dmx, EITTable, index, &EITSection);
                PopulateExtendedInfo( dmx, EITTable,index);*/



                    if( srtdb_Insert( tableid, EITTable->original_network_id , EITTable->transport_stream_id,EITTable->service_id,  0, (Address)(&EITSection)) )
                    {
                        TraceDebug(m,"HYSVC :strapiN_OnAdded  ");
                        strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), ppty, EITTable->original_network_id, EITTable->transport_stream_id, EITTable->service_id);
                    }
                    else
                    {
                        TraceDebug(m,"HYSVC :srtdb_Insert FAILURE  ");
                    }
                }

            }
        }
        else
        {   //Empty EIT. No event 
            DbaseVersion.EventId              =   HSV_INVALID_EVENT; 
        }
    }
#endif
    return TRUE;
}

Bool CHsvDvbEIT_Priv::PopulateRating ( HsvDemux   dmx, HsvEITTable *EITTable, int pptyindex, int secindex, int code)
{
    /* Store the ratings for only the current playing service */
    int         svcid           =0;     /* Service ID is stored as an int in our filter cache */
    int         onwid           =0;     /* This is retreived via a strapi property, which needs a type of Nat16 */
    int         tsid           =0;
    Bool        countryfound    =FALSE;
    int   TempCountryCode;
    Nat8    byte1;
    Nat8    byte2;
    Nat8    byte3;
    HsvSource dummySource;
    HsvChannel channelNo;

#define HSV_TO_UPPER(x) ( ( ((x) >= 'a') && ((x) <= 'z') ) ? ( (x) - 'a' + 'A')  : ( (x) ) )

    UNUSED( code );
    UNUSED( secindex );
    UNUSED( pptyindex );

    if( iparconst_DataParsed == code )
    {

/*        pgsel_GetCurrentProgram(HSV_MAP_DMX_TO_DEST(dmx),&dummySource,&channelNo);
        pgdat_GetChannelDataInt(channelNo,pgdat_IntOriginalNwId,&onwid);
        pgdat_GetChannelDataInt(channelNo,pgdat_IntTsid,&tsid);
        pgdat_GetChannelDataInt(channelNo,pgdat_IntServiceId,&svcid);*/ //Tvsvr

        {


            if(1)
            {
                //HsvParental_RatingDescriptor RatingDesc = EITTable->EITDATA[0].Parental_RatingDescriptor;
                if(EITTable->TsLoopData[0].ParentalRatingNum )
                {  
                    int i = 0;
                    for(i = 0 ; i < EITTable->TsLoopData[0].ParentalRating_Descriptor[0].CountryRatingNum; i++)
                    {
                        byte1 = ((EITTable->TsLoopData[0].ParentalRating_Descriptor[0].CountryRating[i].CountryCode) & 0xFF);
                        byte1 = HSV_TO_UPPER(byte1);

                        byte2 = (((EITTable->TsLoopData[0].ParentalRating_Descriptor[0].CountryRating[i].CountryCode) & 0xFF00) >> 8);
                        byte2 = HSV_TO_UPPER(byte2);

                        byte3 = (((EITTable->TsLoopData[0].ParentalRating_Descriptor[0].CountryRating[i].CountryCode) & 0xFF0000) >> 16);
                        byte3 = HSV_TO_UPPER(byte3);

                        TempCountryCode = ((byte3 << 16) | (byte2 << 8) | (byte1)) & 0xFFFFFF;
                        if(TempCountryCode == conf_CurrentCountry)
                        {
                            countryfound = TRUE;
                            DmxData[dmx].RatingDesc.CountryId  = conf_CurrentCountry;        
                            DmxData[dmx].RatingDesc.Rating     = EITTable->TsLoopData[0].ParentalRating_Descriptor[0].CountryRating[i].Rating;        
                            DmxData[dmx].RatingDesc.DataValid  = TRUE;
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HsvdvbeitActualPresentRatingProperty, onwid, tsid,svcid);
                            break;
                        }
                    }
                    if( !countryfound )
                    {
#if 0 //Tvsvr
                        int NetworkOperator = ins_GetAttribute(ins_InstallationModeAutomatic,ins_AttributeNetworkOperator);
                            if(((NetworkOperator == ins_Ziggo) || (NetworkOperator == ins_UPC) ||   \
                               (/*(sysset_GetSystemCountry() == cids_CountryNetherlands) && */(NetworkOperator == ins_None))) \
                               && (ins_GetMedium() == ins_Cable))
                        {
                            /*done for CR 85653
                              "in case a program has no parental rating with a country code of the Netherlands, the program shall be (b)locked when parental rating is set by user "*/
                            /* the rating is invalid when the coutry code does not match */ 
                            DmxData[dmx].RatingDesc.DataValid  = FALSE;
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HsvdvbeitActualPresentRatingProperty  ,onwid, tsid,svcid);
                        }
                        else
#endif
                        {
                            // No country found yet. Pick first in loop 
                            DmxData[dmx].RatingDesc.CountryId  = EITTable->TsLoopData[0].ParentalRating_Descriptor[0].CountryRating[0].CountryCode;        
                            DmxData[dmx].RatingDesc.Rating     = EITTable->TsLoopData[0].ParentalRating_Descriptor[0].CountryRating[0].Rating;        
                            DmxData[dmx].RatingDesc.DataValid  = TRUE;
                            strapiN_OnAdded(HSV_MAP_DMX_TO_DEST(dmx), HsvdvbeitActualPresentRatingProperty  ,onwid, tsid,svcid);
                        }
                    }
                    else
                    {
                        /// Some country was found. Be happy 
                    }
                }
                else
                {
                    if(DmxData[dmx].RatingDesc.DataValid == TRUE)
                    {
                        TraceDebug(m,"Earlier desc is now gone. So remove the lock.");
                        DmxData[dmx].RatingDesc.DataValid = FALSE;
                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HsvdvbeitActualPresentRatingProperty  ,onwid, tsid,svcid);
                    }
                }
            }

        }
    }
    return TRUE;


}

Bool CHsvDvbEIT_Priv::PopulateLinkage ( HsvDemux   dmx, HsvEITTable *EITTable, int pptyindex, int secindex, int code)
{
   return TRUE;

}

void CHsvDvbEIT_Priv::AssignContentDescriptor(HsvEITTable  *EITTable, int i, HsvEITSection *DbaseVersion)
{
#if 0
    if(EITTable->TsLoopData[i].ContentDescNum > 0) 
    {  
        DbaseVersion->ContentDesc[0].ContentNibble  = EITTable->TsLoopData[i].Content_Descriptor[0].ContentNibble[0].Content1;        
        DbaseVersion->ContentDesc[0].UserNibble     = EITTable->TsLoopData[i].Content_Descriptor[0].ContentNibble[0].User1;        
    }
#endif


}


/*************************IHsvStream Implementation *******************************/



int CHsvDvbEIT_Priv::strapi_GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);

    //if(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable != -1)
    {
        //retval = srtdb_GetNoOfRecords(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable);
    }
    return retval;
}

Bool CHsvDvbEIT_Priv::strapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);

    //if(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable != -1)
    {
        //retval = srtdb_SearchOnKey(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable, key1, key2, key3,0,(int *)&index);
    }
    return TRUE;
}

Bool CHsvDvbEIT_Priv::strapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);

    if(0)//(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable != -1)
    {
        HsvEITSection eitsec;
        //retval = srtdb_QueryOnKey(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable, key1, key2, key3,0,(Address)&eitsec);
        TraceDebug(m,"strapi_GetByKey :prop = %d  retval = %d key1 = %d key2 = %d key3 = %d  ",prop ,retval,key1,key2,key3);
        switch(prop)
        {
#ifndef __cplusplus		
            case HsvdvbeitActualEITPresentProperty :
            case HsvdvbeitActualEITFollowProperty  :
                if(TRUE == retval)
                {                
                    //ASSERT( sizeof(HSVSPTYPE(ActualEITPresent, dvb, eit)) == sizeof(HSVSPTYPE(ActualEITFollow, dvb, eit)));
                    CopyEitData (val, (Address )&eitsec);

                }
                break;
#endif
            default:
                break;
        }
    }
    else
    {   /* Scalar Properties */
        switch(prop)
        {
            case HsvdvbeitActualPresentRatingProperty :
                {
                    if( DmxData[demux].RatingDesc.DataValid )
                    {
                        HsvParentalRatingDescription *pval = (HsvParentalRatingDescription *)val;
                        *pval = DmxData[demux].RatingDesc;
                        retval = TRUE;
                    }
                    break;
                }
#ifndef __cplusplus            
			case HsvdvbeitLinkageDescProperty :
                {
                    if( DmxData[demux].ValidLinkageDesc )
                    {
                        //memcpy(val, &(DmxData[ demux ].LinkageDesc), sizeof(HsvLinkageDescription) );
                        retval = TRUE;
                    }
                    break;
                }
            case HsvdvbeitExtendedInfoProperty :
                {                    
                    if( DmxData[ demux ].ValidExtendedInfo )
                    {
                        /* We have valid extended info. Fire away */
                        if( (key1 == DmxData[ demux ].ExtendedInfo.EventId) && (val != NULL) )
                        {
                            memcpy(val, &(DmxData[ demux ].ExtendedInfo), sizeof(HsvExtendedEventInfo) );
                            retval = TRUE;
                        }                    
                    }
                    break;
                }
            case HsvdvbeitExtendedInfoForNowProperty :
                {                    
                    if( DmxData[ demux ].ValidExtendedInfoForNow )
                    {
                        /* We have valid extended info. Fire away */
                        if( (key1 == DmxData[ demux ].ExtendedInfoForNow.EventId) && (val != NULL) )
                        {
                            memcpy(val, &(DmxData[ demux ].ExtendedInfoForNow), sizeof(HsvExtendedEventInfo) );
                            retval = TRUE;
                        }                    
                    }
                    break;
                }
            case HsvdvbeitExtendedInfoForNextProperty :
                {                    
                    if( DmxData[ demux ].ValidExtendedInfoForNext )
                    {
                        /* We have valid extended info. Fire away */
                        if( (key1 == DmxData[ demux ].ExtendedInfoForNext.EventId) && (val != NULL) )
                        {
                            memcpy(val, &(DmxData[ demux ].ExtendedInfoForNext), sizeof(HsvExtendedEventInfo) );
                            retval = TRUE;
                        }                    
                    }
                    break;
                }
            case HsvdvbeitShortDescProperty :
                {                    
                    if( DmxData[ demux ].ValidShortDesc )
                    {
                        /* We have valid extended info. Fire away */
                        if( (key1 == DmxData[ demux ].ShortDesc.EventId) && (val != NULL) )
                        {
                            memcpy(val, &(DmxData[ demux ].ShortDesc), sizeof(HsvEITShortDesc) );
                            retval = TRUE;
                        }                    
                    }
                    break;
                }
#endif				
            default:
                //ASSERT(!"Unknown Property");
                break;
        }
    }
    return retval;
}

Bool CHsvDvbEIT_Priv::strapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;
    HsvDemux demux   = HSV_MAP_DEST_TO_DMX(inst);

    //if(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable != -1)
    {
        //retval = srtdb_QueryOnIndex(DmxROMData[demux].PropertyInfo[GETINDEX(prop)].dbtable, index, (Address)val);
    }
    return retval;
}



/****For Debugging *****/

Bool CHsvDvbEIT_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool        retval = FALSE;
    HsvDemux    dmx    = HSV_MAP_DEST_TO_DMX(dest);
    Bool Proceed = TRUE;
    Nat16   TableId = 0; 

    switch(filterid)
    {
        /* Do nothing */
        case HsvStartMode:       
            break;
        case HsvCurrentCountry:  
            break;
        case HsvCurrentLanguage: 
            break;
        case HsvOtherSDTOnwidId: 
        case HsvOtherSDTServiceId:
            break;                    
        case HsvCurrentProgram:
            {
                int i;
                int j;
                TraceDebug(m,"strmfltr_Set :HsvCurrentProgram  ");
                /*  Initialise Tables. Prepare for the incoming EIT */
                /*for(i = 0 ; i < MAX_PROPERTIES; i++)
                {
                    DmxData[dmx].TableIds[i]    =   -1;   
                    if( (conf_IsActionAllowed(dmx, DmxROMData[dmx].PropertyInfo[i].confdiv)) && 
                            ( DmxData[dmx].TableIds[i] != HSV_INVALID_TABLE_ID) && EnableNowNextInfoReset )
                    {                                                   
                        //srtdb_Init ( DmxData[dmx].TableIds[i] );                                               
                    }
                }*/


                /* Start setting up the section filters */
                for(i = 0; i < MAX_SECTIONS; i++)
                {
                    Proceed = TRUE;
                    TableId = 0x4e ;

                    if(EIT_8DAYS_DATA_NOTREQ(TableId) || EIT_OTHER_PF_DATA_NOTREQ(TableId)) // EPG sched data for 4 to 8 days
                    {                     
                        Proceed = FALSE;
                    }

                    if(Proceed && conf_IsActionAllowed(dmx, conf_EitNowNextActualParsing))
                    {
                        /* Create mode, match and mask arrays for the section filter we are interested in */
                        Nat8                    ModeArray [ SCT_FLT_DEPTH ];
                        Nat8                    MaskArray [ SCT_FLT_DEPTH ];
                        Nat8                    MatchArray[ SCT_FLT_DEPTH ];
                        HsvSectionFilterListConfig  sctconfig;

                        /* Clear the mode, match and mask arrays of all junk values */
                        for( j = 0; j < SCT_FLT_DEPTH; j++ )
                        {
                            ModeArray[j] = MatchArray[j] = MaskArray[j] = 0;
                        }


                        /* Store the table_id field */
                        MatchArray[TABLEID_FIELD]           = 0x4e;
                        MaskArray [TABLEID_FIELD]           = TABLEID_MASK;
                        ModeArray [TABLEID_FIELD]           = 0x00;

                        /* Table ID extension is a 2 byte field */
                        /* Ensure that we copy the lower 16 bits of the filter value into this field */
                        /* This represents the service_id which we want to filter */
                        MatchArray[TABLE_ID_EXTN_FIELD]     = (Nat8)(((value) & 0xFF00) >> 8 );
                        MatchArray[TABLE_ID_EXTN_FIELD + 1] = (Nat8)(((value) & 0xFF));

                        /* We are interested in both bytes. Set the mask accordingly  */
                        MaskArray [TABLE_ID_EXTN_FIELD]     = 0xFF;
                        MaskArray [TABLE_ID_EXTN_FIELD + 1] = 0xFF;


                        /* We dont want negative filtering */
                        ModeArray [TABLE_ID_EXTN_FIELD]     = 0x00;
                        ModeArray [TABLE_ID_EXTN_FIELD + 1] = 0x00;


                        MatchArray[SECTION_NUMBER_FIELD]    = (Nat8)(i);            
                        MaskArray [SECTION_NUMBER_FIELD]    = SECTION_NUMBER_MASK;
                        ModeArray [SECTION_NUMBER_FIELD]    = 0x00;                 


                        /* Set up the configuration parameters */
                        sctconfig.BufferSize        = EIT_SECTION_BUFFER_SIZE;
                        sctconfig.CrcMode           = HsvCrcModeSkipBadSections;
                        sctconfig.ContinuousMode    = TRUE;      
                        sctconfig.cookie            = (int)(&(DmxData[dmx].SubscrId[i]));
                        sctconfig.pid               = (int)EIT_PID_VALUE;
                        sctconfig.TimeOut           = EIT_SECFLTR_LIST_TIMEOUT;
                        sctconfig.ListLength        = EIT_SECFLTR_LIST_LENGTH;  //PED ; added

                        /* Check if we had a valid request before. If so, cancel it */
                        if( DmxData[dmx].SubscrId[i] != HSV_INVALID_SCT_REQUEST )
                        {
                            sec_CancelSection( HSV_MAP_DMX_TO_DEST(dmx),DmxData[dmx].SubscrId[i] );//PED first param added
                            DmxData[dmx].SubscrId[i] = HSV_INVALID_SCT_REQUEST;
                        }                            
                        DmxData[dmx].SubscrId[i]  = sec_RequestSectionFilterList(HsvDmxMain,
                         &sctconfig, SCT_FLT_DEPTH, ModeArray, MatchArray, MaskArray, FNADDR(EITParser));
                    }
                }

                /* Invalidate our data cache */
                if(EnableNowNextInfoReset)
                {
                    CLEAR_DATA
                        strapiN_OnRemoved(HSV_MAP_DMX_TO_DEST(dmx), HsvdvbeitActualPresentRatingProperty, HSV_INVALID_KEY, HSV_INVALID_KEY,HSV_INVALID_KEY);
                }

                retval = TRUE;
                break;
            }
        case HsvActualEitScheduleService :
            {
                /* Handled in epgApp
                SubscribeForEitSched( dmx, value );*/
                retval = TRUE;
                break;                
            }
        case HsvOtherEitScheduleService :
            {
                
                retval = TRUE;
                break;                
            }

        case HsvExtendedInfoEventId :
            {
                /* Do nothing. The cache for the extended info event ID will be in the main store of filter values 
                   Maintaining duplicates is not ok  */
                DmxData[dmx].ExtEvtVersionNumber = -1;
                DmxData[dmx].ExtendedInfo.EventId = value;
                DmxData[dmx].ValidExtendedInfo      = FALSE;
                retval = TRUE;
                break;
            }
        case HsvExtendedInfoONId:
            {
                DmxData[dmx].ExtendedInfo.OnId = value;
                retval = TRUE;
                break;
            }
        case HsvExtendedInfoTsId:
            {
                DmxData[dmx].ExtendedInfo.Tsid = value;
                retval = TRUE;
                break;
            }

        case HsvExtendedInfoSerId:
            {
                DmxData[dmx].ExtEvtVersionNumber = -1;
                DmxData[dmx].ExtendedInfo.ServiceId = value;
                retval = TRUE;
                break;
            }
        case HsvShortDescEventId:
            {
                DmxData[dmx].ShortEvtVersionNumber = -1;
                DmxData[dmx].ShortDesc.EventId = value;
                DmxData[dmx].ValidShortDesc    = FALSE;
                retval = TRUE;
                break;
            }
        case HsvShortDescONId:
            {
                DmxData[dmx].ShortDesc.OnId = value;
                retval = TRUE;
                break;
            }
        case HsvShortDescTsId:
            {
                DmxData[dmx].ShortDesc.Tsid = value;
                retval = TRUE;
                break;
            }
        case HsvShortDescSerId:
            {
                DmxData[dmx].ShortEvtVersionNumber = -1;
                DmxData[dmx].ShortDesc.ServiceId = value;
                retval = TRUE;
                break;
            }

        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_Set() */
/*************************************************************/

Bool CHsvDvbEIT_Priv::strmfltr_Clear(HsvDestination dest, int filterid, int value)
{
    Bool        retval = FALSE;
    HsvDemux    dmx    = HSV_MAP_DEST_TO_DMX(dest);

    UNUSED (value);
    switch(filterid)
    {
        /* Do nothing */
        case HsvStartMode:       
            break;
        case HsvCurrentCountry:  
            break;
        case HsvCurrentLanguage: 
            break;
        case HsvOtherSDTOnwidId: 
        case HsvOtherSDTServiceId:
            break;                    
        case HsvCurrentProgram:
            {
                int i;
                /*  Initialise Tables. Prepare for the incoming EIT */
                for(i = 0 ; i < MAX_PROPERTIES; i++)
                {
                    DmxData[dmx].TableIds[i]    =   -1;   
                    if( (conf_IsActionAllowed(dmx, conf_EitNowNextActualParsing)) && 
                            ( DmxData[dmx].TableIds[i] != HSV_INVALID_TABLE_ID) && EnableNowNextInfoReset)
                    {                                                   
                        //srtdb_Init ( DmxData[dmx].TableIds[i] );                                               
                    }
                }


                /* Start setting up the section filters */
                for(i = 0; i < MAX_SECTIONS; i++)
                {
                    if(conf_IsActionAllowed(dmx, conf_EitNowNextActualParsing))
                    {
                        /* Check if we had a valid request before. If so, cancel it */
                        if( DmxData[dmx].SubscrId[i] != HSV_INVALID_SCT_REQUEST )
                        {
                            sec_CancelSection( HSV_MAP_DMX_TO_DEST(dmx),DmxData[dmx].SubscrId[i] );//PED added
                            DmxData[dmx].SubscrId[i] = HSV_INVALID_SCT_REQUEST;
                        }

                    }
                }

                retval = TRUE;
                break;
            }

        case HsvActualEitScheduleService :
            {
                int i;

                for(i = EIT_SCHED_ACTUAL4_INDEX; i <= EIT_SCHED_ACTUAL8_INDEX; i++)
                {
                    if(conf_IsActionAllowed(dmx, conf_EitNowNextActualParsing))
                    {
                        /* Check if we had a valid request before. If so, cancel it */
                        if( DmxData[dmx].SubscrId[i] != HSV_INVALID_SCT_REQUEST )
                        {
                            sec_CancelSection( HSV_MAP_DMX_TO_DEST(dmx),DmxData[dmx].SubscrId[i] );//PED added
                            DmxData[dmx].SubscrId[i] = HSV_INVALID_SCT_REQUEST;
                        }

                    }
                }

                EitSchedParsingStarted = FALSE;
                retval = TRUE;
                break;

            }
        case HsvOtherEitScheduleService :
            {
                int i;
                /* Clear our other EIT schedule section filters  */
                for(i = EIT_SCHED_OTHER4_INDEX; i <= EIT_SCHED_OTHER8_INDEX; i++)
                {
                    if(conf_IsActionAllowed(dmx, conf_EitNowNextActualParsing))
                    {
                        /* Check if we had a valid request before. If so, cancel it */
                        if( DmxData[dmx].SubscrId[i] != HSV_INVALID_SCT_REQUEST )
                        {
                            sec_CancelSection( HSV_MAP_DMX_TO_DEST(dmx),DmxData[dmx].SubscrId[i] );//ped added
                            DmxData[dmx].SubscrId[i] = HSV_INVALID_SCT_REQUEST;
                        }

                    }
                }
                EitSchedParsingStarted = FALSE;
                retval = TRUE;
                break;                
            }
        case HsvExtendedInfoONId :
            {
                DmxData[dmx].ExtendedInfo.OnId      = HSV_INVALID_FILTER_VALUE;
                DmxData[dmx].ValidExtendedInfo      = FALSE;
                retval = TRUE;
                break;
            }
        case HsvExtendedInfoTsId:
            {
                DmxData[dmx].ExtendedInfo.Tsid      = HSV_INVALID_FILTER_VALUE;
                DmxData[dmx].ValidExtendedInfo      = FALSE;
                retval = TRUE;
                break;
            }

        case HsvExtendedInfoSerId :
            {
                DmxData[dmx].ExtendedInfo.ServiceId = HSV_INVALID_FILTER_VALUE;
                DmxData[dmx].ValidExtendedInfo      = FALSE;
                retval = TRUE;
                break;
            }
        case HsvExtendedInfoEventId :
            {
                DmxData[dmx].ExtendedInfo.EventId   = HSV_INVALID_FILTER_VALUE;
                DmxData[dmx].ValidExtendedInfo      = FALSE;
                retval = TRUE;
                break;
            }
        case HsvShortDescEventId:
            {
                DmxData[dmx].ShortDesc.EventId = HSV_INVALID_FILTER_VALUE;
                DmxData[dmx].ValidShortDesc    = FALSE;
                retval = TRUE;
                break;
            }
        case HsvShortDescONId:
            {
                DmxData[dmx].ShortDesc.OnId    = HSV_INVALID_FILTER_VALUE;
                DmxData[dmx].ValidShortDesc    = FALSE;
                retval = TRUE;
                break;
            }
        case HsvShortDescTsId:
            {
                DmxData[dmx].ShortDesc.Tsid    = HSV_INVALID_FILTER_VALUE;
                DmxData[dmx].ValidShortDesc    = FALSE;
                retval = TRUE;
                break;
            }
        case HsvShortDescSerId:
            {
                DmxData[dmx].ShortDesc.ServiceId   = HSV_INVALID_FILTER_VALUE;
                DmxData[dmx].ValidShortDesc    = FALSE;
                retval = TRUE;
                break;
            }


        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_Set() */

void CHsvDvbEIT_Priv::CopyEitData (Address dest, Address source)
{   /* NOTE: This is working on the assumption tat both EITActual & Follow has same structure */
#if 0
    HSVSPTYPE(ActualEITPresent,dvb, eit) *eitdest = (HSVSPTYPE(ActualEITPresent,dvb, eit) *)dest; 
    HsvEITSection *eitsrc   =   (HsvEITSection *)source;
    int i = 0;

    eitdest->Original_NetworkId     =       eitsrc->Original_NetworkId;
    eitdest->TsId                   =       eitsrc->TsId;  
    eitdest->ServiceId              =       eitsrc->ServiceId;
    eitdest->dt                     =       eitsrc->dt;
    eitdest->EventId                =       eitsrc->EventId;
    eitdest->Duration               =       eitsrc->Duration;
    //eitdest->RunningStatus          =       eitsrc->RunningStatus;
    //eitdest->Free_CA_Mode           =       eitsrc->Free_CA_Mode;

    TraceDebug(m,"CopyEitData :ONID = %d TSID = %d  SID = %d EVID = %d ",eitdest->Original_NetworkId,eitdest->TsId,eitdest->ServiceId,eitdest->EventId);

    for(i = 0; i < MAX_CONTENTS ; i++ )
    {
        eitdest->ContentDesc[i].ContentNibble   =   eitsrc->ContentDesc[i].ContentNibble; 
        eitdest->ContentDesc[i].UserNibble      =   eitsrc->ContentDesc[i].UserNibble; 
    }

    eitdest->EvtDesc.LanguageId  =   eitsrc->EvtDesc.LanguageId;

    memcpy(eitdest->EvtDesc.ShortName, eitsrc->EvtDesc.ShortName,  (MAX_SHORTNAME_SIZE * 2));

    {

        /*  TraceDebug(m,"SHORT NAME  ");
            for(k =0;(k<10)&&(eitdest->EvtDesc.ShortName[k]);k++)
            TraceDebug(m,"%c",eitdest->EvtDesc.ShortName[k]);
            TraceDebug(m," ");
            */

    }

    /* Dependency on the size defined in HsvPropertypes.dd */
    eitdest->EvtDesc.ShortName[MAX_SHORTNAME_SIZE] = 0;

    memcpy(eitdest->EvtDesc.ShortDesc, eitsrc->EvtDesc.ShortDesc,  (MAX_SHORTDESC_SIZE * 2 - 2));

    /* Dependency on the size defined in HsvPropertypes.dd */
    eitdest->EvtDesc.ShortDesc[MAX_SHORTDESC_SIZE - 1] = 0;
#endif
}


/*************************************************************/





void CHsvDvbEIT_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
{
    int i   = 0;
    int dmx = HsvDmxMain;

    for(i = 0; i < MAX_SECTIONS; i++)
    {
        for(  dmx = HsvDmxMain; dmx < HsvDmxLast; dmx++ )
        {
            if( DmxData[dmx].SubscrId[i] == subscrid )
            {
                /* This was a matching request. Clear our local variables */
                DmxData[dmx].SubscrId[i]  = HSV_INVALID_SCT_REQUEST;
            }
        }
    }
}






Bool CHsvDvbEIT_Priv::EITParser( HsvDestination   dest, Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc )
{
#ifndef __cplusplus
    HsvDemux demux = HSV_MAP_DEST_TO_DMX(dest);    
    static    HsvEITTable Eit_Parser;    
    Bool retval = TRUE;

    register Nat8 *ptr = (Nat8*)EPGData;
    register int v32 = 0;
    int dummy, loopcount = 0, descTag, descLen = 0, descLoopLen = 0, tsloopIndex = 0, loop1index = 0, tableLen = 0, loop1length = 0, templen = 0; 


    UNUSED (cookie);
    UNUSED (code);
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

    memset((void*)(&Eit_Parser),0,13);




    Eit_Parser.TableId = GETNBITS(v32,0,8);
    Eit_Parser.section_syntax_indicator = GETNBITS(v32,8,1);
    dummy = GETNBITS(v32,9,1);
    dummy = GETNBITS(v32,10,2);
    Eit_Parser.section_length = GETNBITS(v32,12,12);
    v32 = GET32( 3);
    Eit_Parser.service_id = GETNBITS(v32,0,16);
    dummy = GETNBITS(v32,16,2);
    Eit_Parser.version_number = GETNBITS(v32,18,5);
    Eit_Parser.current_next_indicator = GETNBITS(v32,23,1);
    Eit_Parser.section_number = GETNBITS(v32,24,8);
    v32 = GET32( 7);    
    Eit_Parser.last_section_number = GETNBITS(v32,0,8);
    Eit_Parser.transport_stream_id = GETNBITS(v32,8,16);
    v32 = GET32( 10);
    Eit_Parser.original_network_id = GETNBITS(v32,0,16);    
    Eit_Parser.segment_last_section_number = GETNBITS(v32,16,8);



    dummy = GETNBITS(v32,24,8);
    ptr += 14;
    tableLen = tableLen - 14;
    v32 = GET32( 0);

    if(PopulateEIT( demux,  &Eit_Parser, parconst_HeaderParsed ))
    {
        Eit_Parser.TsLoopDataNum = 0;

        while( ((tableLen - 4) >  0)  &&  ( tsloopIndex < 1 ))
        {
            Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum = 0;
            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum = 0;
            Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum = 0;
            Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum = 0;
            Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum = 0;  

            Eit_Parser.TsLoopData[tsloopIndex].event_id = GETNBITS(v32, 0,16);
            Eit_Parser.TsLoopData[tsloopIndex].StartDate = GETNBITS(v32, 16,16);
            v32 = GET32( 4);
            Eit_Parser.TsLoopData[tsloopIndex].StartTime = GETNBITS(v32, 0,24);
            v32 = GET32( 7);
            Eit_Parser.TsLoopData[tsloopIndex].duration = GETNBITS(v32, 0,24);
            Eit_Parser.TsLoopData[tsloopIndex].running_status = GETNBITS(v32, 24,3);
            dummy = GETNBITS(v32,27,1);
            v32 = GET32( 10);
            Eit_Parser.TsLoopData[tsloopIndex].descriptors_loop_length = GETNBITS(v32, 4,12);
            ptr += 12;
            tableLen = tableLen - 12;
            v32 = GET32( 0);

            while(loopcount < Eit_Parser.TsLoopData[tsloopIndex].descriptors_loop_length)
            {
                descLoopLen = 0, loop1length = 0;
                descTag = GETNBITS(v32,0, 8); 
                descLen = GETNBITS(v32,8, 8); 

                switch(descTag) {
                    case 0x4E:
                        if(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum<16)
                        {
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].DescriptorTag = GETNBITS(v32, 0,8);
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].DescriptorLen = GETNBITS(v32, 8,8);
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].DescNumber = GETNBITS(v32, 16,4);
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].LastDescNumber = GETNBITS(v32, 20,4);
                            v32 = GET32( 3);
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].LangCode = GETNBITS(v32, 0,24);
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].LenOfItems = GETNBITS(v32, 24,8);
                            ptr += 7;
                            v32 = GET32( 0 );
                            loop1index = 0, loop1length = 0, templen = sizeof(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData);
                            while( loop1length< MIN(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].LenOfItems, templen))
                            {
                                int minLength = 0;
                                Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemDescLen = GETNBITS(v32,0, 8); 
                                minLength = MIN(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemDescLen,51);
                                ptr += 1;
                                memcpy(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemDescChar,ptr, minLength);
                                ptr += Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemDescLen;
                                loop1length += Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemDescLen;
                                v32 = GET32( 0);
                                Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemDescLen = minLength;
                                Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemCharLen = GETNBITS(v32,0, 8); 
                                minLength = MIN(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemCharLen,101);
                                ptr += 1;
                                memcpy(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemChar,ptr, minLength);
                                ptr += Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemCharLen;
                                loop1length += Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemCharLen;
                                v32 = GET32( 0);
                                Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemData[loop1index].ItemCharLen = minLength;
                                loop1length += 2;
                                loop1index++;
                                v32 = GET32( 0);
                            }
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].ItemDataLen = loop1index;
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].TextLen = GETNBITS(v32, 0,8);
                            descLoopLen = MIN(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].TextLen,255); 
                            ptr += 1;
                            memcpy(Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].TextChar,ptr,descLoopLen);
                            ptr += Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].TextLen;
                            v32 = GET32( 0);
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].TextLen = descLoopLen;
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum].DescriptorValid = TRUE;
                            Eit_Parser.TsLoopData[tsloopIndex].ExtendedEventNum++;
                        }
                        else
                        {
                            ptr += 2 + descLen;
                        }
                        loopcount += 2 + descLen;
                        tableLen = tableLen - (2 + descLen);

                        v32 = GET32( 0);
                        break;

                    case 0x4D:
                        if(Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum<16)
                        {
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].DescriptorTag = GETNBITS(v32, 0,8);
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].DescriptorLen = GETNBITS(v32, 8,8);
                            v32 = GET32( 2);
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].LangCode = GETNBITS(v32, 0,24);
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].EventNameLen = GETNBITS(v32, 24,8);
                            descLoopLen = MIN(80,Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].EventNameLen); 
                            ptr += 6;
                            memcpy(Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].EventName,ptr,descLoopLen);
                            ptr += Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].EventNameLen;
                            v32 = GET32( 0);
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].EventNameLen = descLoopLen;
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].TextNameLen = GETNBITS(v32, 0,8);
                            descLoopLen = MIN(Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].TextNameLen, 255); 
                            ptr += 1;
                            memcpy(Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].TextName,ptr,descLoopLen);
                            ptr += Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].TextNameLen;
                            v32 = GET32( 0);
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].TextNameLen = descLoopLen;
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEvent_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum].DescriptorValid = TRUE;
                            Eit_Parser.TsLoopData[tsloopIndex].ShortEventNum++;
                        }
                        else
                        {
                            ptr += 2 + descLen;
                        }
                        loopcount += 2 + descLen;
                        tableLen = tableLen - (2 + descLen);

                        v32 = GET32( 0);
                        break;

                    case 0x54:
                        if(Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum<2)
                        {
                            Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                            Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                            ptr += 2;
                            v32 = GET32( 0 );
                            loop1index = 0, loop1length = 0, templen = sizeof(Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].ContentNibble);
                            while( loop1length< MIN(Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].DescriptorLen, templen))
                            {

                                Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].ContentNibble[loop1index].Content1 = GETNBITS(v32,0, 4); 
                                Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].ContentNibble[loop1index].Content2 = GETNBITS(v32,4, 4); 
                                Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].ContentNibble[loop1index].User1 = GETNBITS(v32,8, 4); 
                                Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].ContentNibble[loop1index].User2 = GETNBITS(v32,12, 4); 
                                loop1length += 2;
                                loop1index++;
                                ptr += 2;
                                v32 = GET32( 0);
                            }
                            if(Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].DescriptorLen > templen)

                            {

                                ptr += (Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].DescriptorLen - templen );

                                v32 = GET32( 0);

                            }
                            Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].ContentNibbleLen = loop1index;
                            Eit_Parser.TsLoopData[tsloopIndex].Content_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum].DescriptorValid = TRUE;
                            Eit_Parser.TsLoopData[tsloopIndex].ContentDescNum++;
                        }
                        else
                        {
                            ptr += 2 + descLen;
                        }
                        loopcount += 2 + descLen;
                        tableLen = tableLen - (2 + descLen);

                        v32 = GET32( 0);
                        break;

                    case 0x55:
                        if(Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum<2)
                        {
                            Eit_Parser.TsLoopData[tsloopIndex].ParentalRating_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum].DescriptorTag = GETNBITS(v32, 0,8);
                            Eit_Parser.TsLoopData[tsloopIndex].ParentalRating_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum].DescriptorLen = GETNBITS(v32, 8,8);
                            ptr += 2;
                            v32 = GET32( 0 );
                            loop1index = 0, loop1length = 0, templen = sizeof(Eit_Parser.TsLoopData[tsloopIndex].ParentalRating_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum].CountryRating);
                            while( loop1length< MIN(Eit_Parser.TsLoopData[tsloopIndex].ParentalRating_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum].DescriptorLen, templen))
                            {

                                Eit_Parser.TsLoopData[tsloopIndex].ParentalRating_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum].CountryRating[loop1index].CountryCode = GETNBITS(v32,0, 24); 
                                Eit_Parser.TsLoopData[tsloopIndex].ParentalRating_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum].CountryRating[loop1index].Rating = GETNBITS(v32,24, 8); 
                                loop1length += 4;
                                loop1index++;
                                ptr += 4;
                                v32 = GET32( 0);
                            }
                            Eit_Parser.TsLoopData[tsloopIndex].ParentalRating_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum].CountryRatingNum = loop1index;
                            Eit_Parser.TsLoopData[tsloopIndex].ParentalRating_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum].DescriptorValid = TRUE;
                            Eit_Parser.TsLoopData[tsloopIndex].ParentalRatingNum++;
                        }
                        else
                        {
                            ptr += 2 + descLen;
                        }
                        loopcount += 2 + descLen;
                        tableLen = tableLen - (2 + descLen);

                        v32 = GET32( 0);
                        break;

                    case 0x4A:
                        if(Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum<64)
                        {
                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorTag = GETNBITS(v32, 0,8);
                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorLen = GETNBITS(v32, 8,8);
                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].TSID = GETNBITS(v32, 16,16);
                            v32 = GET32( 4);
                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].ONID = GETNBITS(v32, 0,16);
                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].ServiceId = GETNBITS(v32, 16,16);
                            v32 = GET32( 8);
                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].LinkageType = GETNBITS(v32, 0,8);
                            ptr += 9;
                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].Private_ByteLen = descLen - 7;;
                            descLoopLen = MIN(40,Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].Private_ByteLen); 
                            ptr += 0;
                            memcpy(Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].Private_Byte,ptr,descLoopLen);
                            ptr += Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].Private_ByteLen;
                            v32 = GET32( 0);
                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].Private_ByteLen = descLoopLen;

                            Eit_Parser.TsLoopData[tsloopIndex].Linkage_Descriptor[Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum].DescriptorValid = TRUE;
                            Eit_Parser.TsLoopData[tsloopIndex].LinkageDescNum++;
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
                        tableLen = tableLen - (2 + descLen);
                        v32 = GET32( 0);
                        break;
                }//endswitch
            }//endwhile descloop
            tsloopIndex++;
            loopcount = 0;

            Eit_Parser.TsLoopDataNum = tsloopIndex;

            retval = retval & PopulateEIT( demux,  &Eit_Parser, parconst_DataParsed  );    
            tsloopIndex = 0;    

        }//endwhile tsloop
        PopulateEIT( demux,  &Eit_Parser, parconst_CompletedParsing );

    }//end if(PopulateEIT)


    //Eit_Parser.TsLoopDataNum = tsloopIndex;



    dummy = GETNBITS(v32,0,32);



    return retval;
#else
	return FALSE;
#endif		
}


Bool CHsvDvbEIT_Priv::strapi_GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to)
{
	return FALSE;
}

Bool CHsvDvbEIT_Priv::strmfltr_IsSet(HsvDestination dest,int filterid,int value)
{
	return FALSE;
}
Bool CHsvDvbEIT_Priv::strmfltr_IsReady(HsvDestination dest,int filterid)
{
	return FALSE;
}

Bool CHsvDvbEIT_Priv::strmfltr_ForceClear(HsvDestination dest,int filterid,int valu)
{
	return FALSE;
}

void CHsvDvbEIT_Priv::dmxsecfN_OnRequestAllowed(HsvDestination dest)
{

}

void CHsvDvbEIT_Priv::dmxsecfN_OnRequestNotAllowed(void)
{
}

