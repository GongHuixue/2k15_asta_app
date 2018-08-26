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
 *          %name: hsvdvbsdm_m.c %
 *       %version: TVG_fusion_6 %
 * %date_modified: Fri Jan 30 13:13:44 2009 %
 *    %derived_by: zaheer %
 */




#include "_hsvdvbsdm_m.h"

TRACESYMBOL(m, "dvb/sitables/hsvdvbsdm_m")


/* This macro encodes the Nat16 (or int) parameter passed to it, into a Nat32 with the 
   most significant 16 bits containing the event and the lower 16 bits containing the mode */





#ifdef WIN32

#else

#endif







    


struct SdmDemux_t CHsvDvbStreamingDataManager_m_Priv::s__SdmDemux[HsvDmxLast];



/* This array is required to determine if a particular action is allowed, as requested by the
   function in the IHsvDVBSIConfig interface. The order in which the elements are defined in this 
   array is closely coupled with the values of the constants in IHsvDVBSIConfig*/
int CHsvDvbStreamingDataManager_m_Priv::s__Actions[SDM_ACTION_TABLE_ENTRIES]=
{
    /* Idle                         */       0,       

    /* Minimal                      */       conf_NitActualParsing | 
        conf_NitOtherParsing |
        conf_SdtActualParsing | 
        conf_SdtOtherParsing | 
        conf_Notifications, 

    /* Normal                       */       conf_NitActualParsing |
        conf_NitOtherParsing |
        conf_SdtActualParsing | 
        conf_SdtOtherParsing | 
        conf_EitNowNextActualParsing | 
        conf_EitNowNextOtherParsing |
        conf_TdtParsing | 
        conf_TotParsing | 
        conf_EitSchedActualParsing|
        conf_EitSchedOtherParsing|
        conf_Notifications, 
    /* External                     */       0,

    /* CrossCarraige                */       conf_NitActualParsing | 
        conf_NitOtherParsing | 
        conf_SdtActualParsing | 
        conf_SdtOtherParsing | 
        conf_EitNowNextActualParsing | 
        conf_EitNowNextOtherParsing | 
        conf_TdtParsing | 
        conf_TotParsing | 
        conf_Notifications,    
};



/* Enum of the events which can be triggered inside the SDM */




struct StreamFilterValues_t CHsvDvbStreamingDataManager_m_Priv::s__StreamFilterValues[HsvDmxLast];
 

Pump CHsvDvbStreamingDataManager_m_Priv::s__ControlPump;

Pump CHsvDvbStreamingDataManager_m_Priv::s__NoDataPump;

Pump CHsvDvbStreamingDataManager_m_Priv::s__SyncPump;

int CHsvDvbStreamingDataManager_m_Priv::s__conf_CurrentCountry = 0;




      /* Pump function */
 /* Delay pump function */
    /* Sync handler*/




/*********************************************************************/
/* Functions of the IHsvPower interface, provided by SDM             */
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::pow_Init(void)
{
    HsvDemux dmx;
    for (dmx = HsvDmxMain ; dmx < HsvDmxLast; dmx++ ) 
    {
        /* Clear all demuxes        */
        SdmDemux[dmx].Mode   = ctrl_Idle;
        SdmDemux[dmx].Status = ctrl_Invalid;
    }

	//It will be called from libtvMiddleware
    //dmxpow_Init();
    hsvmpeg_pow_Init();
    hsvdvbsi_pow_Init();

    //ControlPump = pmp_PmpCreateEx( pen_PumpEngine, SdmControlEventHandler, FALSE, "hsvdvbsdm.mcontrol.CtrlPmp");
    ControlPump = pmp_PmpCreateEx( ctrlpen_PumpEngine, SdmControlEventHandler, FALSE, "hsvdvbsdm.mcontrol.CtrlPmp");
    ASSERT( ControlPump );

    NoDataPump      = pmp_PmpCreateEx( pen_PumpEngine, SdmNoDataAvailableHandler,TRUE, "hsvatscsdm.m.NoDataPump");   /* Replacing pump*/
    ASSERT( NoDataPump );    /* Failed to create the required number of pumps. Is the infra diversity set to a sufficiently high value ?*/


    SyncPump        = pmp_PmpCreateEx( pen_PumpEngine, SdmSyncHandler, TRUE,"hsvatscsdm.m.SyncPump");  /* Replacing pump*/
    ASSERT( SyncPump );    
}
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::pow_TurnOn(void)
{
	//It will be called from libtvMiddleware
    //dmxpow_TurnOn();
    hsvmpeg_pow_TurnOn();
    hsvdvbsi_pow_TurnOn();    

    /* Clear our internal data structures */
    InitializeTables( HsvDmxMain );
    InitializeTables( HsvDmxAux  );
}
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::pow_TurnOff(void)
{
    hsvdvbsi_pow_TurnOff();
    hsvmpeg_pow_TurnOff();
	//It will be called from libtvMiddleware
    //dmxpow_TurnOff();

    /* Clear our internal data structures */
    InitializeTables( HsvDmxMain );
    InitializeTables( HsvDmxAux  );
}

/*********************************************************************/
/* Functions of the IHsvSdmControl interface, provided by SDM        */
/*********************************************************************/
int CHsvDvbStreamingDataManager_m_Priv::ctrl_GetMode( HsvDemux dmx )
{
    return (SdmDemux[dmx].Mode);
}
/*********************************************************************/
int CHsvDvbStreamingDataManager_m_Priv::ctrl_GetStatus( HsvDemux dmx )
{
    return (SdmDemux[dmx].Status);
}
/*********************************************************************/

/* Function : StartCollection() of the IHsvSdmControl interface
 * Instruction from outside world to start collecting data on a particular demux 
 * Input Parameters :  1] HsvDemux dmx : Demux on which data is to be collected 
 2] int mode     : This parameter can only take on the values 
 defined inside the IHsvSdmControl interface
 */                                              
void CHsvDvbStreamingDataManager_m_Priv::ctrl_StartCollection(HsvDemux dmx, int mode)
{
    int country = 0;

	TraceNotice(m, "%s-%d mode=%d", __FUNCTION__, __LINE__, mode);
    ASSERT( ctrl_Idle == mode || ctrl_Minimal == mode || ctrl_Normal == mode || ctrl_CrossCarraige == mode );

    if( mode != ctrl_Idle)
    { /* The client cannot start us in Idle mode */

        //if( ctrl_Idle == SdmDemux[dmx].Mode )             PR brg36mgr#58089 Removing the check because of timing issues.Start demux called when stop demux was still in progress
        {  
#ifndef __cplusplus
            /* Pull in the current country setting from inset */
            /* fixme: This stream filter setting is expected to be done from outside by selection */
            country = MapCountry( sysset_GetSystemCountry() );
#else
			country = 11;
#endif

            strmfltr_Set( HSV_MAP_DMX_TO_DEST(dmx), HsvCurrentCountry, country);

            /* Current mode is Idle implies that we have not been started previosly */
            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK(evHsvSdmStart, mode ) );
        }   
    }   
}   /* End of function ctrl_StartCollection() */
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::ctrl_StopCollection(HsvDemux dmx)
{
    //if( SdmDemux[dmx].Mode != ctrl_Idle )
    {
        /* The PmpSend() solves two problems. Modification of the "Status" value is now centralized
           and pending messages on the pump, if any, when StopCollection is called, are processed
           before the StoppedCollection notification is generated 
           */
        TraceNotice(m,"%d %s pmp send for stop collection done ... ", __LINE__, __FUNCTION__);
        pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK(evHsvSdmStop,0) );
        InitializeTables( dmx );
    }
}
/*********************************************************************/

/*********************************************************************/
/* Functions of the IHsvDVBSIConfig interface, contained inside SDM   */
/*********************************************************************/

/* Return true or false, depending on whether the requested action is allowed when the SDM is in the current state. This interface function
   is required by the PSIP data manager, to determine if, for example,notifications need to be generated or not.
   Input parameters        : 1] HsvDemux dmx : The demux on which data is being collected
   2] int action   : An action, which can (or cannot) be allowed to 
   occur. For the possible values of the action 
   parameter, refer to the IHsvDVBSIConfig interface.
   Note that the order in which the elements of the static array "Actions" are
   defined, is coupled to the order in which the different actions are defined
   in the IHsvDVBSIConfig interface
   */   
Bool CHsvDvbStreamingDataManager_m_Priv::conf_IsActionAllowed( HsvDemux dmx, int action )
{
    return ( (Actions[ SdmDemux[dmx].Mode ] & action) ? TRUE : FALSE );
}


/*********************************************************************/
/* Notifications obtained through the demux notification interface from the 
   demux controller */
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::hsvdmxN_OnDemuxSyncLock( HsvDemux dmx )
{
    ASSERT( HsvDmxMain == dmx || HsvDmxAux == dmx );
	/*currently nobody using thsi notification*/
    if( ctrl_Invalid == SdmDemux[ dmx ].Status || ctrl_NoDataAvailable == SdmDemux[ dmx ].Status )
    {
        
    }
}
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::hsvdmxN_OnDemuxSyncLost( HsvDemux dmx )
{
    ASSERT( HsvDmxMain == dmx || HsvDmxAux == dmx );
    
    UNUSED(dmx);
}


/*********************************************************************/
/* Functions of the IHsvMpegSectionsNotify interface, required by MpegDataManager 
   and provided by PsipDataManager
   This interface is also required optionally on the boundary of SDM   
   All functions of this interface are redirected to the outside world.In case 
   PsipDataManager has been activated, the notifications are provided to that 
   component also
   */
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::hsvmpeg_mpegsecnN_OnChanged( HsvDemux dmx, int value, int tableid )
{    
    if( mpegsecnN_iPresent() )
    {
        mpegsecnN_OnChanged( dmx, value, tableid );
    }
    /* fixme */
}
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::hsvmpeg_mpegsecnN_OnAdded( HsvDemux dmx, int value, int tableid )
{
    if( mpegsecnN_iPresent() )
    {
        mpegsecnN_OnAdded( dmx, value, tableid );
    }
    /* fixme */
}
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::hsvmpeg_mpegsecnN_OnRemoved( HsvDemux dmx, int value, int tableid )
{
    if( mpegsecnN_iPresent() )
    {
        mpegsecnN_OnRemoved( dmx, value, tableid );
    }
    /* fixme */
}
/*********************************************************************/
/* Internal static functions                                         */
/*********************************************************************/
/* Function name    : SdmControlEventHandler
 * Parameters       :  a] int      dmx          :- The demux to which we are referring
 b] Nat32    eventmask    :- A mask, comprising of the event which occurred
 and a mode parameter, if required. The "event" 
 value will be in the top 16 bits and the "mode"
 value in the lower 16 bits
 * Description      : This function is called, when a particular event has occured inside
 the SDM. The logic for deciding if a change in SDM state is necessary,
 is contained inside this function
 * Output           : None
 * Error condition  : None signalled
 */               
void CHsvDvbStreamingDataManager_m_Priv::SdmControlEventHandler( int dmx, Nat32 eventmask )
{        

    ASSERT( dmx >= HsvDmxMain && dmx < HsvDmxLast );

    /* Extract the "event" value from the top 16 bits */
    switch ( HSV_GET_EVENT( eventmask ) )
    {
        /* The first 16 bits of the "event" parameter will contain the actual event that occurred */
        /* The last 16 bits will contain the "mode", if it is applicable to a certain state       */  
        case evHsvSdmNoDataAvailable :
            {            
                /* Timeout was hit. Send a "NoDataAvailable" notification if we were still in the 
                   Invalid (initial) state. */
                   TraceNotice(m,"Time out happened");

                if(  (ctrl_SiDataAvailable == SdmDemux[dmx].Status ) ||
                        (ctrl_SDTAvailable == SdmDemux[dmx].Status ) )
                {
                    if( ctrlN_iPresent() )
                    {
   	                   TraceNotice(m,"sent Data Available from %d",__LINE__);
                        ctrlN_OnEvent( dmx, ctrlN_DataAvailable, -1  );
                    }            
                }
                else
                {   /* Only NIT is also data not available */
                    if( ctrlN_iPresent() )
                    {
                        ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, ((ctrl_NITAvailable == SdmDemux[dmx].Status)? ctrlN_SDT : ctrlN_NIT) );
                    }
                    SdmDemux[dmx].Status = ctrl_NoDataAvailable;
                }
                break;
            }
        case evHsvSdmSDTAvailable :
            {
                if( SdmDemux[dmx].Mode != ctrl_Idle )/*This check is to not process the SDT available after stop collection*/
                {
	                /* SI data was found in the stream*/
	                if( ctrl_NITAvailable == SdmDemux[dmx].Status )
	                {
	                    SdmDemux[dmx].Status = ctrl_SiDataAvailable;
	                    if( ctrlN_iPresent() )
	                    {
	   	                   TraceNotice(m,"sent Data Available from %d",__LINE__);
	                        ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_NIT | ctrlN_SDT) );
	                    }
	                }
	                else
	                {
	                    SdmDemux[dmx].Status = ctrl_SDTAvailable;

	                    if( ctrlN_iPresent() )
	                    {
	   	                   TraceNotice(m,"sent SIData Available from %d",__LINE__);
	                        ctrlN_OnEvent( dmx, ctrlN_SiDataAvailable, ctrlN_SDT);
	                    }
	                }
                }
                break;
            }
        case evHsvSdmNITAvailable :
            {
                if( SdmDemux[dmx].Mode != ctrl_Idle )/*This check is to not process the NIT available after stop collection*/
                {
	                /* SI data was found in the stream*/
	                if( ctrl_SDTAvailable == SdmDemux[dmx].Status )
	                {
	                    SdmDemux[dmx].Status = ctrl_SiDataAvailable;
	                    if( ctrlN_iPresent() )
	                    {
	   	                   TraceNotice(m,"sent Data Available from %d",__LINE__);
	                        ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_NIT | ctrlN_SDT));
	                    }
	                }
		            else
		            {
		                SdmDemux[dmx].Status = ctrl_NITAvailable;
						if((ins_GetMedium() == ins_Cable) && (ins_InstallationModePreScan == ins_GetInstallationMode()) )
						{
							if( ctrlN_iPresent() )
							{
								ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_NIT );
							}
							pmp_PmpSendAfter( NoDataPump, 0, IGNORE_MESSAGE, 20 );
						}
		            }
    	        }
                break;
            }
        case evHsvSdmStart :
            {
                if( ctrl_Idle == SdmDemux[dmx].Mode )
                {
                    /* SDM has just been started. Perform the initializations */
                    SdmDemux[dmx].Status = ctrl_Invalid;
                    SdmDemux[dmx].Mode   = (eventmask & 0xFFFF);            /* The last 16 bits of the event parameter contain the mode value */

                    /* Enable the demux controller before we enable any other components */
                    //                    MyTestFunc();

                    dmxena_Enable(dmx);

                    /* enable only when dmx give ntf onstarted : temp*/
                    /* We start the mpeg and SI components when demux is started */
                    /*pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmDemuxSyncLock, 0 ));*/

                    /* Generate a timeout after a set number of milliseconds to check if we have data or not*/
                    /* This will be done in the DmxStarted event */
                    /* pmp_PmpSendAfter( ControlPump, dmx, HSV_CREATE_EVENT_MASK(evHsvSdmNoDataAvailable,0), div_SdmWaitTime );*/



                    /* We now wait for a SyncLock() notification before we enable PSIP and MPEG */
                }
                break;
            }
        case evHsvSdmDmxStarted :
            {
                /* Sync locked onto the stream. Check if we are in the Invalid state and 
                   enable MPEG and PSIP if so */
				int sdmtimeout = eurdiv_sdmWaitTime();
                if( ctrl_Invalid == SdmDemux[ dmx ].Status || ctrl_NoDataAvailable == SdmDemux[ dmx ].Status )
                {
                    hsvmpeg_enable_Enable(dmx);
                    if(DVB_SI_ENABLED)
                    {
                        hsvdvbsi_ena_Enable(dmx);
                    }

                    /* Start the no data timer */
					//TraceNotice(m,"no data timer set to: %d msec TARGET_CORRECTION: %d",div_SdmWaitTime,TARGET_CORRECTION);
                    pmp_PmpSendAfter( NoDataPump, dmx, PROCESS_MESSAGE, sdmtimeout * TARGET_CORRECTION);

					//TraceNotice(m,"data collection time out set to: %d",div_DataCollectionTimeout);

                    /* Generate another timeout, to ensure that we notify clients to start collecting data from us */
                    pmp_PmpSendAfter( SyncPump, dmx, PROCESS_MESSAGE, sdmtimeout * TARGET_CORRECTION );

                }   /* End of if ( ctrl_Invalid == SdmDemux [ dmx ].Status ) */
                else
                {
                    /* Sync lock notification being generated even though we have
                       started collecting data. This could have happened due to a 
                       loss and re-lock of sync from the platform */
                }

                if( ctrlN_iPresent() )
                {             
                    ctrlN_OnEvent( dmx, ctrlN_StartedCollection, 0 );
                }           

                break;
            }
        case evHsvSdmSyncComponents :
            {
                /* Timeout was hit for Sync() notifications. Force all clients to 
                   generate a notification by calling Sync() for each component */

                if( ctrl_SiDataAvailable == SdmDemux[ dmx ].Status )
                {
                    /* There was some data which was seen previously, either PSI or PSIP.
                       Force PSIP and MPEG data manager to give notifications, by calling a Sync()
                       on them */              
                    hsvmpeg_enable_Sync( dmx );
                    if(DVB_SI_ENABLED)
                    {
                        hsvdvbsi_ena_Sync( dmx );
                    }
                }
                SyncFilter(dmx);
                break;
            }
        case evHsvSdmStop :
            {
                if( SdmDemux[dmx].Mode != ctrl_Idle )
                {
                    TraceNotice(m,"%d %s Inside pump handler of stop collection ... ", __LINE__, __FUNCTION__);
                    /* diable sdm components (synchronously to avoid conflicts 
                       between OnInstanceremoved and the caller of this function */
                    /* SDM has to be stopped */

                    if(DVB_SI_ENABLED)
                    {
                        hsvdvbsi_ena_Disable(dmx);
                    }
                    hsvmpeg_enable_Disable(dmx);
                    dmxena_Disable(dmx);
                    /* Reset the mode and status values */
                    SdmDemux[dmx].Mode      = ctrl_Idle;
                    SdmDemux[dmx].Status    = ctrl_Invalid;

                    /* Erase our timers by send a pump message with a small value */
                    pmp_PmpSendAfter( NoDataPump, 0, IGNORE_MESSAGE, 20 );
                    pmp_PmpSendAfter( SyncPump, 0, IGNORE_MESSAGE, 20 );
                }

                if( ctrlN_iPresent() )
                {
                    ctrlN_OnEvent( dmx, ctrlN_StoppedCollection, 0 );
                }

                break;
            }
        default :
            {
                /* Ignore all other events */
                break;
            }
    }   /* End of switch( SdmDemux[dmx].Status )   */     
}   /* End of function SdmControlEventHandler() */


/*********************************************************************/
/* Functions of the IHsvSdmControlNotify interface, required by the MpegDataManager */
/*********************************************************************/
/*
void hsvmpeg_ctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(dmx);
    UNUSED(eventid);
    UNUSED(value);
  //* Not Processed. Not Interesting for anyone 
}*/

/*********************************************************************/
/* Functions of the IHsvSdmControlNotify interface, required by the SI data manager  
/*********************************************************************/

void CHsvDvbStreamingDataManager_m_Priv::hsvdvbsi_ctrlN_OnEvent( HsvDemux dmx, int eventid, int value  )
{
  	
	UNUSED (eventid);
    switch (value)
    {
        case hsvdvbsi_ctrlN_SDT:
            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmSDTAvailable, 0 ) );
            break;
        case hsvdvbsi_ctrlN_NIT:
            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmNITAvailable, 0 ) );
            break;
    }

}


/*********************************************************************/
/* Notifications obtained through the demux notification interface from the 
   demux controller */
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::hsvdmxN_OnStarted( HsvDemux dmx )
{    
    pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmDmxStarted, 0 ) );
}

void CHsvDvbStreamingDataManager_m_Priv::hsvdmxN_OnStopped( HsvDemux dmx )
{
    /*pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmDmxStopped, 0 ) );*/
}




/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::SdmNoDataAvailableHandler( int dmx, Nat32 eventmask)
{
    if( PROCESS_MESSAGE == eventmask )
    {
        pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK(evHsvSdmNoDataAvailable,0) );
    }
    else
    {
        /* This was an 'erase' request. Do not do a pmpsend. Let this message pass away and clear our pump */
    }

}/* End of function SdmNoDataAvailableHandler() */
/*********************************************************************/

void CHsvDvbStreamingDataManager_m_Priv::SdmSyncHandler( int dmx, Nat32 eventmask)
{
    if( PROCESS_MESSAGE == eventmask )
    {
        pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK(evHsvSdmSyncComponents,0) );
    }
    else
    {
        /* This was an 'erase' request. Do not do a pmpsend. Let this message pass away and clear our pump */
    }

}/* End of function SdmSyncHandler() */
/*********************************************************************/



/********************************LCL Strapi***************************************/
/*************************IHsvStream Implementation *******************************/


int CHsvDvbStreamingDataManager_m_Priv::ilclstrapi_GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;
    UNUSED (inst);
    switch(prop)
    {
        case HSVSPID(Services, dvb, lcl ):
            /* Get the number of programs from SDT & PAT. Resolve the same ones
               and give a consolidated list */
            break;
        default:
            break;
    }

    return retval;
}

Bool CHsvDvbStreamingDataManager_m_Priv::ilclstrapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;
    UNUSED (inst);
    UNUSED (key1);
    UNUSED (key2);
    UNUSED (key3);
    UNUSED (index);
    switch(prop)
    {
        case HSVSPID(Services, dvb, lcl ):
            retval = TRUE;
            break;
        default:
            break;
    }

    return TRUE;
}

Bool CHsvDvbStreamingDataManager_m_Priv::ilclstrapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;
    UNUSED (inst);
    UNUSED (key1);
    UNUSED (key2);
    UNUSED (key3);
    UNUSED (val);
    switch(prop)
    {
        case HSVSPID(Services, dvb, lcl ):
            retval = TRUE;
            break;
        default:
            break;
    }

    return retval;
}

Bool CHsvDvbStreamingDataManager_m_Priv::ilclstrapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;
    UNUSED (inst);
    UNUSED (index);
    UNUSED (val);

    switch(prop)
    {
        case HSVSPID(Services, dvb, lcl ):
            retval = TRUE;
            break;
        default:
            break;
    }

    return retval;
}

Bool CHsvDvbStreamingDataManager_m_Priv::ilclstrapi_GetRangeByKey( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(noofkeys);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
    UNUSED (from);
    UNUSED (to);

    return FALSE;
}

/* I dont like this implementation...i did it when it was needed urgently...
   Ideally all this info should go to a dd file & be included here as macros 
   Hope some smart guy/gal who finds time will change this ....*/

/*int strmfltr_GetFilter(HsvDestination dest, int filterid)
  {
  int retval = 0;
  switch(filterid)
  {
  case HsvStartMode:       
  break;
  case HsvCurrentCountry:  
  break;
  case HsvCurrentLanguage: 
  break;
  case HsvCurrentProgram:
  retval = StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentProgram;
  break;        
  case HsvOtherSDTOnwidId: 
  retval = StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTOnwidId;
  break;
  case HsvOtherSDTServiceId:
  retval = StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTServiceId;
  break;
  default:
  retval = FALSE;
  break;
  }
  return retval;
  }
  */

Bool CHsvDvbStreamingDataManager_m_Priv::strmfltr_IsSet(HsvDestination dest, int filterid, int value )
{
    Bool retval = FALSE;
    switch(filterid)
    {
        case HsvStartMode:       
            retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].StartMode) == (value));
            break;
        case HsvCurrentCountry:  
            retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentCountry) == (value));
            break;
        case HsvCurrentLanguage: 
            retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentLanguage) == (value));
            break;
        case HsvCurrentProgram:
            retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentProgram) == (value));
            break;
        case HsvOtherSDTOnwidId: 
            retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTOnwidId) ==(value));
            break;
        case HsvOtherSDTServiceId:
            retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTServiceId) ==(value));
            break;
        case HsvExtraProgram0 :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram0) ==(value));
                break;
            }
        case HsvExtraProgram1 :
            {                
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram1) ==(value));
                break;                
            }
        case HsvExtraProgram2 :
            {                
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram2) ==(value));
                break;                
            }
        case HsvExtraProgram3 :
            {                
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram3) ==(value));
                break;                
            }
        case HsvExtraProgram4 :
            {                
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram4) ==(value));
                break;                
            }
        case HsvExtraProgram5 :
            {                
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram5) ==(value));
                break;                
            }
        case HsvActualEitScheduleService :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ActualEitScheduleService) ==(value));
                break;
            }
        case HsvOtherEitScheduleService :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherEitScheduleService) ==(value));
                break;
            }
        case HsvExtendedInfoEventId :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoEventId) ==(value));
                break;
            }
        case HsvExtendedInfoONId :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoONId) ==(value));
                break;
            }
        case HsvExtendedInfoTsId :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoTsId) ==(value));
                break;
            }

        case HsvExtendedInfoSerId :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoSerId) ==(value));
                break;
            }
        case HsvShortDescEventId :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescEventId) ==(value));
                break;
            }

        case HsvShortDescONId :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescONId) ==(value));
                break;
            }
        case HsvShortDescTsId :
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescTsId) ==(value));
                break;
            }

        case HsvShortDescSerId :    
            {
                retval = ((StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescSerId) ==(value));
                break;
            }
        default:
            retval = FALSE;
            break;
    }
    return retval;
}/* End of function strmfltr_IsSet() */
/*****************************************************/


Bool CHsvDvbStreamingDataManager_m_Priv::strmfltr_IsReady(HsvDestination dest, int filterid ) /* Ready for Strapi */
{
    return(!(StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].WaitingFor & SET_BIT(filterid)));
}/* End of function strmfltr_IsReady() */
/*****************************************************/


void CHsvDvbStreamingDataManager_m_Priv::SyncFilter(HsvDemux dmx)
{
    if(StreamFilterValues[dmx].WaitingFor&SET_BIT(HsvCurrentProgram))
    {
        StreamFilterValues[dmx].WaitingFor &=RESET_BIT(HsvCurrentProgram);
        strmfltrN_OnReady(HSV_MAP_DMX_TO_DEST(dmx),HsvCurrentProgram);
    }
    else if(StreamFilterValues[dmx].WaitingFor&SET_BIT(HsvOtherSDTOnwidId))
    {
        StreamFilterValues[dmx].WaitingFor &=RESET_BIT(HsvOtherSDTOnwidId);
        strmfltrN_OnReady(HSV_MAP_DMX_TO_DEST(dmx),HsvOtherSDTOnwidId);
    }
    else if(StreamFilterValues[dmx].WaitingFor&SET_BIT(HsvOtherSDTServiceId))
    {
        StreamFilterValues[dmx].WaitingFor &=RESET_BIT(HsvOtherSDTServiceId);
        strmfltrN_OnReady(HSV_MAP_DMX_TO_DEST(dmx),HsvOtherSDTServiceId); 
    }
}/* Enf of function SyncFilter() */
/*****************************************************/




Bool CHsvDvbStreamingDataManager_m_Priv::strmfltr_Clear(HsvDestination dest, int filterid,int value)
{    
    Bool retval = FALSE;
    switch(filterid)
    {
        case HsvStartMode:       
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].StartMode = (HSV_INVALID_FILTER_VALUE);
            retval = TRUE;
            break;
        case HsvCurrentCountry:  
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentCountry = (HSV_INVALID_FILTER_VALUE);
            retval = TRUE;
            break;
        case HsvCurrentLanguage: 
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentLanguage = (HSV_INVALID_FILTER_VALUE);
            retval = TRUE;
            break;
        case HsvCurrentProgram:
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentProgram = (HSV_INVALID_FILTER_VALUE);
            hsvmpeg_mpegsecn_MonitorProgram( HSV_MAP_DEST_TO_DMX(dest), HSV_INVALID_FILTER_VALUE );
            hsvdvbsi_strmfltr_Clear( dest, filterid, value );
            retval = TRUE;
            break;
        case HsvOtherSDTOnwidId: 
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTOnwidId = (HSV_INVALID_FILTER_VALUE);
            retval = TRUE;
            break;
        case HsvOtherSDTServiceId:
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTServiceId = (HSV_INVALID_FILTER_VALUE);
            retval = TRUE;
            break;

        case HsvExtraProgram0 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram0 = (HSV_INVALID_FILTER_VALUE);
                hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), HSV_INVALID_FILTER_VALUE, 0 );
                retval  = TRUE;
                break;
            }
        case HsvExtraProgram1 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram1 = (HSV_INVALID_FILTER_VALUE);
                hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), HSV_INVALID_FILTER_VALUE, 1 );
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram2 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram2 = (HSV_INVALID_FILTER_VALUE);
                hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), HSV_INVALID_FILTER_VALUE, 2 );
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram3 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram3 = (HSV_INVALID_FILTER_VALUE);
                hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), HSV_INVALID_FILTER_VALUE, 3 );
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram4 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram4 = (HSV_INVALID_FILTER_VALUE);
                hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), HSV_INVALID_FILTER_VALUE, 4 );
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram5 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram5 = (HSV_INVALID_FILTER_VALUE);
                hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), HSV_INVALID_FILTER_VALUE, 5 );
                retval  = TRUE;
                break;                
            }
        case HsvActualEitScheduleService :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ActualEitScheduleService = (HSV_INVALID_FILTER_VALUE);                
                hsvdvbsi_strmfltr_Clear( dest, filterid, value );
                retval  = TRUE;
                break;                
            }
        case HsvOtherEitScheduleService :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherEitScheduleService = (HSV_INVALID_FILTER_VALUE);                
                hsvdvbsi_strmfltr_Clear( dest, filterid, value );
                retval  = TRUE;
                break;                
            }
        case HsvExtendedInfoEventId:
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoEventId = (HSV_INVALID_FILTER_VALUE);                                
                retval  = TRUE;
                break;                
            }
        case HsvExtendedInfoONId :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoONId = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;
            }
        case HsvExtendedInfoTsId :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoTsId = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;
            }

        case HsvExtendedInfoSerId :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoSerId = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;
            }
        case HsvShortDescEventId :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescEventId = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;
            }

        case HsvShortDescONId :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescONId = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;
            }
        case HsvShortDescTsId :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescTsId = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;
            }
        case HsvShortDescSerId :    
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescSerId = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;
            }
        default:
            retval = FALSE;
            break;
    }
    return retval;
}   /* End of function strmfltr_Clear() */
/**************************************************/


Bool CHsvDvbStreamingDataManager_m_Priv::strmfltr_Set(HsvDestination dest, int filterid, int value)
{
    Bool retval = FALSE;
	int sdmtimeout = eurdiv_sdmWaitTime();
    if( !strmfltr_IsSet(dest, filterid, value ) )
    {                
        switch(filterid)
        {
            case HsvStartMode:       
                break;
            case HsvCurrentCountry:  
#ifndef __cplusplus
				conf_CurrentCountry                                          = value;
#endif				
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentCountry = value;
                retval                                                       = TRUE;
                break;
            case HsvCurrentLanguage: 
                break;
            case HsvCurrentProgram:
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentProgram = value;
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].WaitingFor    |= SET_BIT(HsvCurrentProgram);                        
                hsvmpeg_mpegsecn_MonitorProgram( HSV_MAP_DEST_TO_DMX(dest), value );
                hsvdvbsi_strmfltr_Set( dest, filterid, value);            
                /* Generate another timeout, to ensure that we notify clients to start collecting data from us */
                pmp_PmpSendAfter( SyncPump, HSV_MAP_DEST_TO_DMX(dest), PROCESS_MESSAGE, sdmtimeout * TARGET_CORRECTION );
                retval = TRUE;
                break;
            case HsvOtherSDTOnwidId: 
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTOnwidId = value;
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].WaitingFor    |= SET_BIT(HsvOtherSDTOnwidId);
                hsvdvbsi_strmfltr_Set( dest, filterid, value);
                retval                                                       = TRUE;
                pmp_PmpSendAfter( SyncPump, HSV_MAP_DEST_TO_DMX(dest), PROCESS_MESSAGE, sdmtimeout * TARGET_CORRECTION );
                break;
            case HsvOtherSDTServiceId:
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTServiceId = value;
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].WaitingFor    |= SET_BIT(HsvOtherSDTServiceId);            
                hsvdvbsi_strmfltr_Set( dest, filterid, value);
                retval                                                       = TRUE;
                pmp_PmpSendAfter( SyncPump, HSV_MAP_DEST_TO_DMX(dest), PROCESS_MESSAGE, sdmtimeout * TARGET_CORRECTION );
                break;

                /* Extra properties do not excite a filter notification */
            case HsvExtraProgram0 :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram0 = value;
                    hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), value, 0 );
                    retval  = TRUE;
                    break;
                }
            case HsvExtraProgram1 :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram1 = value;
                    hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), value, 1 );
                    retval  = TRUE;
                    break;                
                }
            case HsvExtraProgram2 :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram2 = value;
                    hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), value, 2 );
                    retval  = TRUE;
                    break;                
                }
            case HsvExtraProgram3 :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram3 = value;
                    hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), value, 3 );
                    retval  = TRUE;
                    break;                
                }
            case HsvExtraProgram4 :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram4 = value;
                    hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), value, 4 );
                    retval  = TRUE;
                    break;                
                }
            case HsvExtraProgram5 :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram5 = value;
                    hsvmpeg_mpegsecn_MonitorProgramByIndex( HSV_MAP_DEST_TO_DMX(dest), value, 5 );
                    retval  = TRUE;
                    break;                
                }
            case HsvActualEitScheduleService :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ActualEitScheduleService = (value);
                    retval = hsvdvbsi_strmfltr_Set( dest,HsvActualEitScheduleService, value );                
                    break;                
                }
            case HsvOtherEitScheduleService :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherEitScheduleService = (value);
                    retval = hsvdvbsi_strmfltr_Set( dest,HsvOtherEitScheduleService, value );
                    break;                
                }
            case HsvExtendedInfoEventId :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoEventId = (value);
                    retval = hsvdvbsi_strmfltr_Set( dest,HsvExtendedInfoEventId, value );
                    break;                
                }
            case HsvExtendedInfoONId :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoONId = (value);
                    retval  = hsvdvbsi_strmfltr_Set( dest,HsvExtendedInfoONId, value );
                    break;
                }
            case HsvExtendedInfoTsId :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoTsId = (value);
                    retval  = hsvdvbsi_strmfltr_Set( dest,HsvExtendedInfoTsId, value );
                    break;
                }

            case HsvExtendedInfoSerId :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtendedInfoSerId = (value);
                    retval  = hsvdvbsi_strmfltr_Set( dest,HsvExtendedInfoSerId, value );
                    break;
                }
            case HsvShortDescEventId :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescEventId = (value);
                    retval  = hsvdvbsi_strmfltr_Set( dest,HsvShortDescEventId, value );
                    break;
                }

            case HsvShortDescONId :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescONId = (value);
                    retval  = hsvdvbsi_strmfltr_Set( dest,HsvShortDescONId, value );
                    break;
                }
            case HsvShortDescTsId :
                {
                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescTsId = (value);
                    retval  = hsvdvbsi_strmfltr_Set( dest,HsvShortDescTsId, value );
                    break;
                }
            case HsvShortDescSerId :    
                {

                    StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ShortDescSerId = (value);
                    retval  = hsvdvbsi_strmfltr_Set( dest,HsvShortDescSerId, value );
                    break;
                }


            default:
                retval = FALSE;
                break;
        }
    }            
    else
    {
        pmp_PmpSendAfter( SyncPump, HSV_MAP_DEST_TO_DMX(dest), PROCESS_MESSAGE, eurdiv_sdmWaitTime() * TARGET_CORRECTION );
        retval = TRUE;
    }
    return retval;
}/* End of function strmfltr_Set() */
/*************************************************************/
Bool CHsvDvbStreamingDataManager_m_Priv::strmfltr_ForceClear(HsvDestination dest, int filterid, int value)
{
    Bool retval = FALSE;
    switch(filterid)
    {
        case HsvOtherSDTServiceId:
        {
            // Currently used for telenet =>  cancel the sdt other filters 
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTServiceId = (HSV_INVALID_FILTER_VALUE);
            hsvdvbsi_strmfltr_ForceClear( dest, filterid, value );
            retval = TRUE;
        }
        break;

        break;
        default:
            retval = FALSE;
    }
    
    return retval;
}



Bool CHsvDvbStreamingDataManager_m_Priv::hsvdvbsi_dvbsvc_GetOtherService (HsvDemux dmx, int *onwid, int *svcid)
{
    Bool    retval = FALSE;
    if( (StreamFilterValues[dmx].OtherSDTOnwidId) && (StreamFilterValues[dmx].OtherSDTServiceId) )
    {
        *onwid = StreamFilterValues[dmx].OtherSDTOnwidId;
        *svcid = StreamFilterValues[dmx].OtherSDTServiceId;
        retval = TRUE;
    }

    return retval;
}/* End of function hsvdvbsi_dvbsvc_GetOtherService() */
/*************************************************************/

Bool CHsvDvbStreamingDataManager_m_Priv::hsvdvbsi_dvbsvc_GetActualEitSchedService(HsvDemux dmx, int *svcid)
{
    Bool    retval = FALSE;
    if( (StreamFilterValues[dmx].ActualEitScheduleService != HSV_INVALID_FILTER_VALUE) )
    {
        *svcid = StreamFilterValues[dmx].ActualEitScheduleService;
        retval = TRUE;
    }

    return retval;
}

Bool CHsvDvbStreamingDataManager_m_Priv::hsvdvbsi_dvbsvc_GetOtherEitSchedService(HsvDemux dmx, int *svcid)
{
    Bool    retval = FALSE;
    if( (StreamFilterValues[dmx].OtherEitScheduleService != HSV_INVALID_FILTER_VALUE) )
    {
        *svcid = StreamFilterValues[dmx].OtherEitScheduleService;
        retval = TRUE;
    }

    return retval;
}


Bool CHsvDvbStreamingDataManager_m_Priv::hsvdvbsi_dvbsvc_GetCurrentService (HsvDemux dmx, int *onwid, int *svcid)
{
#if 0
    Deepak
    Bool    retval = FALSE;
    Nat16   onid = 0;



    if( (StreamFilterValues[dmx].CurrentProgram) )
    {
        istrapi_GetByKey(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0, &onid) ;
        *onwid = onid;
        *svcid = StreamFilterValues[dmx].CurrentProgram;
        retval = TRUE;
    }
#endif
    return FALSE;
} 
Bool CHsvDvbStreamingDataManager_m_Priv::hsvdvbsi_dvbsvc_GetCurrentService2 (HsvDemux dmx, int *onwid, int *tsid,int *svcid)
{
    Bool    retval = FALSE;
#if 0
    Deepak
	HSVSPTYPE(ActualOriginalNetworkId, dvb, sdt) onid = 0;
	HSVSPTYPE(ActualTsId, dvb, sdt) TsId = 0;

    if( (StreamFilterValues[dmx].CurrentProgram) )
    {
        istrapi_GetByKey(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0, &onid) ;
        istrapi_GetByKey(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, &TsId) ;
        *onwid = onid;
        *tsid = TsId;
        *svcid = StreamFilterValues[dmx].CurrentProgram;
        retval = TRUE;
    }
#endif
    return retval;
}

/* End of function hsvdvbsi_dvbsvc_GetCurrentService () */
/*************************************************************/



Bool CHsvDvbStreamingDataManager_m_Priv::hsvdvbsi_dvbsvc_GetExtendedInfoEventId (HsvDemux dmx, int *eventid )
{
    Bool    retval = FALSE;    

    if( (StreamFilterValues[dmx].ExtendedInfoEventId) != HSV_INVALID_FILTER_VALUE )
    {
        *eventid = StreamFilterValues[dmx].ExtendedInfoEventId;
        retval = TRUE;
    }

    return retval;
} /* End of function hsvdvbsi_dvbsvc_GetExtendedInfoEventId () */
/*************************************************************/




void CHsvDvbStreamingDataManager_m_Priv::InitializeTables( HsvDemux dmx )
{
    /* Clear all tables on this demux */

    /* WARNING REMOVAL: Currently the HsvDmxMain value is 0. And HsvDemux is unsigned. So first condition is always 
       true. So first check can be removed. Check only if dmx datatype modified to signed */
    if( /*(dmx >= HsvDmxMain) && */ (dmx < HsvDmxLast ) )
    {
        StreamFilterValues[dmx].StartMode                   = HSV_INVALID_FILTER_VALUE;       
        StreamFilterValues[dmx].CurrentCountry              = HSV_INVALID_FILTER_VALUE;   /* Lets be choosy. 0  can be a valid country code */
        StreamFilterValues[dmx].CurrentLanguage             = HSV_INVALID_FILTER_VALUE; 
        StreamFilterValues[dmx].CurrentProgram              = HSV_INVALID_FILTER_VALUE; 
        /*StreamFilterValues[dmx].ExtraProgram         = HSV_INVALID_FILTER_VALUE;    */
        StreamFilterValues[dmx].OtherSDTOnwidId             = HSV_INVALID_FILTER_VALUE; 
        StreamFilterValues[dmx].OtherSDTServiceId           = HSV_INVALID_FILTER_VALUE;
        StreamFilterValues[dmx].WaitingFor                  = HSV_INVALID_FILTER_VALUE;
        StreamFilterValues[dmx].ActualEitScheduleService    = HSV_INVALID_FILTER_VALUE;
        StreamFilterValues[dmx].OtherEitScheduleService     = HSV_INVALID_FILTER_VALUE;
        StreamFilterValues[dmx].ExtendedInfoEventId         = HSV_INVALID_FILTER_VALUE;

    }
}   /* End of function InitializeTables() */
/*************************************************************/




int CHsvDvbStreamingDataManager_m_Priv::MapCountry( int cntry )
{   
    /* Map from inset country to country code as per standard */
    int retval = 0;


    switch( cntry )
    {
        case  cids_CountryAustria: 
            retval = HSV_MAKE_CHAR_MASK('A','U','T');
            break;        
        case  cids_CountryBelgium: 
            retval = HSV_MAKE_CHAR_MASK('B','E','L');
            break;

        case  cids_CountryCroatia: 
            retval = HSV_MAKE_CHAR_MASK('H','R','V');
            break;

        case  cids_CountryCzechrep: 
            retval = HSV_MAKE_CHAR_MASK('C','Z','E');
            break;

        case  cids_CountryDenmark: 
            retval = HSV_MAKE_CHAR_MASK('D','N','K');
            break;

        case  cids_CountryFinland: 
            retval = HSV_MAKE_CHAR_MASK('F','I','N');
            break;

        case  cids_CountryFrance: 
            retval = HSV_MAKE_CHAR_MASK('F','R','A');
            break;

        case  cids_CountryGermany: 
            retval = HSV_MAKE_CHAR_MASK('D','E','U');
            break;

        case  cids_CountryGreece: 
            retval = HSV_MAKE_CHAR_MASK('G','R','C');
            break;

        case  cids_CountryHungary: 
            retval = HSV_MAKE_CHAR_MASK('H','U','N');
            break;

        case  cids_CountryIreland: 
            retval = HSV_MAKE_CHAR_MASK('I','R','L');
            break;

        case  cids_CountryItaly: 
            retval = HSV_MAKE_CHAR_MASK('I','T','A');
            break;

        case  cids_CountryLuxembourg: 
            retval = HSV_MAKE_CHAR_MASK('L','U','X');
            break;

        case  cids_CountryNetherlands: 
            retval = HSV_MAKE_CHAR_MASK('N','L','D');
            break;

        case  cids_CountryNorway: 
            retval = HSV_MAKE_CHAR_MASK('N','O','R');
            break;

        case  cids_CountryPoland:
            retval = HSV_MAKE_CHAR_MASK('P','O','L');        
            break;

        case  cids_CountryPortugal:
            retval = HSV_MAKE_CHAR_MASK('P','R','T');        
            break;

        case  cids_CountryRomania: 
            retval = HSV_MAKE_CHAR_MASK('R','O','U');
            break;

        case cids_CountryRussia: 
            retval = HSV_MAKE_CHAR_MASK('R','U','S');
            break;

        case  cids_CountrySerbia: 
            retval = HSV_MAKE_CHAR_MASK('S','E','R');
            break;

        case  cids_CountrySlovakia: 
            retval = HSV_MAKE_CHAR_MASK('S','V','K');
            break;

        case  cids_CountrySlovenia: 
            retval = HSV_MAKE_CHAR_MASK('S','V','N');  
            break;

        case  cids_CountrySpain: 
            retval = HSV_MAKE_CHAR_MASK('E','S','P');
            break;

        case  cids_CountrySweden: 
            retval = HSV_MAKE_CHAR_MASK('S','W','E');  
            break;

        case  cids_CountrySwitzerland: 
            retval = HSV_MAKE_CHAR_MASK('C','H','E');  
            break;

        case  cids_CountryTurkey: 
            retval = HSV_MAKE_CHAR_MASK('T','U','R');  
            break;

        case  cids_CountryUK: 
            retval = HSV_MAKE_CHAR_MASK('G','B','R');  
            break;

        case  cids_CountryAustralia: 
            retval = HSV_MAKE_CHAR_MASK('A','U','S');
            break;            

        case  cids_CountryOther: 
            retval = HSV_MAKE_CHAR_MASK('X','X','X');            
            break;

		case cids_CountryNewZealand:
			retval = HSV_MAKE_CHAR_MASK('N','Z','L');            
            break;
		case cids_CountrySingapore:
			retval = HSV_MAKE_CHAR_MASK('S','G','P');            
            break;
		case cids_CountryMalaysia:
			retval = HSV_MAKE_CHAR_MASK('M','Y','S');            
            break;
		case cids_CountryThailand:
			retval = HSV_MAKE_CHAR_MASK('T','H','A');            
            break;	
		case cids_CountryTaiwan:
			retval = HSV_MAKE_CHAR_MASK('T','W','N');            
            break;	
		case cids_CountryIndonesia:
			retval = HSV_MAKE_CHAR_MASK('I','D','N');            
            break;
		case cids_CountryVietnam:
			retval = HSV_MAKE_CHAR_MASK('V','N','M');          
            break;
			
        default :
            retval = 0;
            break;        
    }

    /* Put the 3 char country code in the lower 3 bytes and send out. */
    return retval;
}







void CHsvDvbStreamingDataManager_m_Priv::dmxsecfN_OnRequestCancelled( Nat32 subscrid )
{
    // hsvdvbsi_dmxsecfN_OnRequestCancelled( subscrid );
}

void CHsvDvbStreamingDataManager_m_Priv::dmxsecfN_OnRequestAllowed( HsvDestination dest )
{
    
}

void CHsvDvbStreamingDataManager_m_Priv::dmxsecfN_OnRequestNotAllowed()
{

}

