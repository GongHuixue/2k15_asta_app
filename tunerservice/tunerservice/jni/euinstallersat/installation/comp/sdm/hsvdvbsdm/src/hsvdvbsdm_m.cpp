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
 *       %version: FUSION_TVG_29.1.1 %
 * %date_modified: Fri Jan 30 13:13:44 2009 %
 *    %derived_by: anuma %
 */
 


 
#include "_hsvdvbsdm_m.h"


TRACESYMBOL(m, "s2/sdm/hsvdvbsdm")

/* This macro encodes the Nat16 (or int) parameter passed to it, into a Nat32 with the 
   most significant 16 bits containing the event and the lower 16 bits containing the mode */





#ifdef WIN32

#else

#endif



int CHsvDvbStreamingDataManager_m_Priv::s__mPackageSelected = 0xfff;




struct SdmDemuxStruct CHsvDvbStreamingDataManager_m_Priv::s__SdmDemux[HsvDmxLast];


int CHsvDvbStreamingDataManager_m_Priv::s__Actions[NUM_SDM_COLLECTION_MODES]=
{
   /* Idle                         */       0,       

   /* Minimal                      */       conf_NitActualParsing | 
   											conf_NitOtherParsing |
                                            conf_SdtActualParsing | 
                                            conf_SdtOtherParsing |	
											conf_BatParsing |		
                                            conf_Notifications, 

   /* Normal                       */       conf_NitActualParsing |
                                            conf_SdtActualParsing |
											conf_BatParsing |
                                            conf_Notifications, 

    /* External                     */       0,   

    /* CrossCarraige                */       conf_NitActualParsing |                                             
								    		 conf_SdtActualParsing |                                            
								    		 conf_EitNowNextActualParsing |                                             
								           	 conf_EitNowNextOtherParsing |                                             
								             conf_TdtParsing |                                             
								             conf_TotParsing |                                             
								             conf_Notifications,    


	/* NormalPlusPmt               */       conf_NitActualParsing | 
                                            conf_SdtActualParsing | 
                                            conf_Notifications, 

	 /* M7Minimal                 */		conf_FntParsing | 
                                            conf_FstParsing | 
                                            conf_Notifications, 
											
    /* ctrl_HomingMuxData */				conf_BatParsing | 
											conf_NitActualParsing,

    /* ctrl_PkgBuildMode */					conf_BatParsing |
    										conf_Notifications,

   /* FransatNormal     */					conf_NitActualParsing |
                                            conf_SdtActualParsing |
                                            conf_SdtOtherParsing |
                                            conf_EitNowNextActualParsing | 
											conf_EitNowNextOtherParsing |
                                            conf_TdtParsing | 
                                            conf_TotParsing | 
											conf_BatParsing |
											conf_Notifications,

   /* MinimalPlusBat*/						0,

	/*FreesatMinimalNitAct*/
											conf_NitActualParsing,

	/*FreesatPostcode*/
											conf_PostcodeParsing,

	/*FreesatNormal*/
											conf_NitOtherParsing|
											conf_SdtOtherParsing|
											conf_BatParsing,

	/*FreesatMinimalNitOth*/
											conf_NitOtherParsing,

	/*FreesatPSIMode*/
											0,
	/*FreesatMinimalSDTOth*/				conf_SdtOtherParsing,
	
	/* ctrl_AstraSGT */				   		conf_SgtParsing |
										    conf_Notifications,
										   
	   /* TricolorNormal */       			conf_NitActualParsing | 
                                            conf_SdtActualParsing | 
											conf_BatParsing |		
                                            conf_Notifications, 

   /*TricolorRegionScanMode*/				conf_BatParsing |
   											conf_Notifications,
											
   /* FransatCamIns */					    conf_TotParsing 				

};




/* Enum of the events which can be triggered inside the SDM */



struct StreamFilterTypesStruct CHsvDvbStreamingDataManager_m_Priv::s__StreamFilterValues [HsvDmxLast];


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
    int dmx;
    for (dmx = HsvDmxMain ; dmx < HsvDmxLast; dmx++ ) 
    {
        /* Clear all demuxes        */
        SdmDemux[dmx].Mode   = ctrl_Idle;
        SdmDemux[dmx].Status = ctrl_Invalid;
		SdmDemux[dmx].TablesCollectionStatus = 0;
    }

    //dmxpow_Init();
    hsvdvbsi_pow_Init();
	hsvsimplempeg_pow_Init();

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
    //dmxpow_TurnOn();
    hsvdvbsi_pow_TurnOn();    
	hsvsimplempeg_pow_TurnOn();

    /* Clear our internal data structures */
    InitializeTables( HsvDmxMain );
    InitializeTables( HsvDmxAux  );
}
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::pow_TurnOff(void)
{
    hsvdvbsi_pow_TurnOff();
    //dmxpow_TurnOff();
	hsvsimplempeg_pow_TurnOff();

    /* Clear our internal data structures */
    InitializeTables( HsvDmxMain );
    InitializeTables( HsvDmxAux  );
}

/*********************************************************************/
/* Functions of the IHsvSdmControl interface, provided by SDM        */
/*********************************************************************/
int CHsvDvbStreamingDataManager_m_Priv::ctrl_GetMode( HsvDemux dmx )
{
	TraceNotice(m,"SDM ctrl_GetMode - mode 0x%x",SdmDemux[dmx].Mode);
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


    ASSERT( ctrl_Idle == mode || ctrl_Minimal == mode || ctrl_Normal == mode || ctrl_CrossCarraige == mode || ctrl_NormalPlusPmt == mode || ctrl_M7Minimal == mode  
	|| ctrl_HomingMuxData == mode || ctrl_PkgBuildMode == mode || ctrl_FransatNormal == mode || ctrl_TricolorNormal == mode);
	
    TraceDebug (m, "%s() : Mode %d\n", __FUNCTION__, mode);
    if( mode != ctrl_Idle)
    { /* The client cannot start us in Idle mode */
        
        //if( ctrl_Idle == SdmDemux[dmx].Mode )             PR brg36mgr#58089 Removing the check because of timing issues.Start demux called when stop demux was still in progress
        {  
            /* Pull in the current country setting from inset */
            /* fixme: This stream filter setting is expected to be done from outside by selection */
            country = MapCountry( sysset_GetSystemCountry() );


            strmfltr_Set( HSV_MAP_DMX_TO_DEST(dmx), HsvCurrentCountry, country);

            /* Current mode is Idle implies that we have not been started previosly */
            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK(evHsvSdmStart, mode ) );
        }
		if((mode == ctrl_Minimal) || (mode == ctrl_NormalPlusPmt)  || (mode == ctrl_PkgBuildMode) || (mode == ctrl_TricolorNormal))
		{
			/*
			* As of now , package information is required only For differentiating Cyfra+ (Poland) package with others, as Cyfra+ is using Minimal mode. If in future, its 
			* Required for other packages or other modes , remove the condition check of mode
			*/
			mPackageSelected = ins_GetAttribute(ins_InstallationNone, ins_AttributePackageId);
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
		PrintfNotice ("%d %s pmp send for stop collection done ... \n", __LINE__, __FUNCTION__);
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
void CHsvDvbStreamingDataManager_m_Priv::phsvdmxN_OnDemuxSyncLock( HsvDemux dmx )
{
    ASSERT( HsvDmxMain == dmx || HsvDmxAux == dmx );

    if( ctrl_Invalid == SdmDemux[ dmx ].Status || ctrl_NoDataAvailable == SdmDemux[ dmx ].Status )
    {
        if( hsvdmxN_iPresent() )
        {
            hsvdmxN_OnDemuxSyncLock( dmx );
        }
    }
}
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::phsvdmxN_OnDemuxSyncLost( HsvDemux dmx )
{
    ASSERT( HsvDmxMain == dmx || HsvDmxAux == dmx );
    if( hsvdmxN_iPresent() )
    {
        hsvdmxN_OnDemuxSyncLost( dmx );
    }
	UNUSED(dmx);
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
void CHsvDvbStreamingDataManager_m_Priv::SdmControlEventHandler( int dmxval, Nat32 eventmask )
{        
	HsvDemux	dmx = (HsvDemux)dmxval;

    ASSERT( dmx >= HsvDmxMain && dmx < HsvDmxLast );
	int table = 0;
	int event = 0;
	int insMode,insState;
	ins_GetCurrentInstallationState(&insMode,&insState);
	TraceNotice(m,"insMode %d insState %d",insMode,insState);
    /* Extract the "event" value from the top 16 bits */
    switch ( HSV_GET_EVENT( eventmask ) )
    {
        /* The first 16 bits of the "event" parameter will contain the actual event that occurred */
        /* The last 16 bits will contain the "mode", if it is applicable to a certain state       */  
    case evHsvSdmNoDataAvailable :
        {  
					
            /* Timeout was hit. Send a "NoDataAvailable" notification if we were still in the 
               Invalid (initial) state. */

			/* Check mode now */
			TraceNotice(m,"Timeout Happend \n");
			if (SdmDemux[dmx].Mode == ctrl_M7Minimal) 
			{
				
				{   /* Only FNT/FST is also data not available */
					{
						if( ctrlN_iPresent() )
						{
							ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, ((ctrl_FNTAvailable == SdmDemux[dmx].Status)? ctrlN_FST : ctrlN_FNT) );
						}
						SdmDemux[dmx].Status = ctrl_NoDataAvailable;
					}
				}			
			}
			else if (SdmDemux[dmx].Mode == ctrl_HomingMuxData)
			{
				TraceNotice(m,"[%s] [%d]  \n",__FUNCTION__,__LINE__);
				if(SdmDemux[dmx].Status != ctrl_SiDataAvailable)
				{
					if( ctrlN_iPresent() )
					{
						ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, ((ctrl_BATAvailable == SdmDemux[dmx].Status)? ctrlN_BAT : ctrlN_NIT) );
					}
					SdmDemux[dmx].Status = ctrl_NoDataAvailable;
				}
			}
			else if(((mPackageSelected == CYFRAPLUS_POLSAT_PACKAGE_ID) || (mPackageSelected == NTVPLUS_PACKAGE_ID) ) && (SdmDemux[dmx].Mode == ctrl_Minimal))
			{
				if( ctrlN_iPresent() )
				{
					
					if(CHECK_ALL_TABLE(SdmDemux[dmx].TablesCollectionStatus))
					{
						table = (ctrlN_NIT | ctrlN_SDT |ctrlN_BAT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );								
					}
					else if((SdmDemux[dmx].TablesCollectionStatus & (BAT_AVAILABLE|NIT_AVAILABLE)) == (BAT_AVAILABLE|NIT_AVAILABLE))
					{
						table = (ctrlN_NIT|ctrlN_BAT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );
					}
					else
					{
						ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, table);
						SdmDemux[dmx].Status = ctrl_NoDataAvailable;
					}
				}
			}
			else if ((IS_FRANSAT_PACKAGE(mPackageSelected)) && (SdmDemux[dmx].Mode == ctrl_Minimal))
			{
				if( ctrlN_iPresent() )
				{
					table = 0;
					if(SdmDemux[dmx].TablesCollectionStatus & BAT_AVAILABLE)
					{
						table |= ctrlN_BAT;
					}
					if(SdmDemux[dmx].TablesCollectionStatus & NIT_AVAILABLE)
					{
						table |= ctrlN_NIT;
					}
					if(SdmDemux[dmx].TablesCollectionStatus & SDT_AVAILABLE)
					{
						table |= ctrlN_SDT;
					}

					if(table)
					{
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );
					}
					else
					{
						ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, table);
						SdmDemux[dmx].Status = ctrl_NoDataAvailable;
					}
				}
			}
			else if (SdmDemux[dmx].Mode == ctrl_PkgBuildMode)
			{
				TraceNotice(m,"[%s] [%d]  \n",__FUNCTION__,__LINE__);
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_BAT);
				}
			}
			else if (ctrl_FreesatMinimalNitAct == SdmDemux[dmx].Mode)
			{
				if((SdmDemux[dmx].TablesCollectionStatus & SIMPLEPMT_AVAILABLE) && (SdmDemux[dmx].TablesCollectionStatus & NIT_AVAILABLE))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					event = ctrlN_DataAvailable;
					table = (ctrlN_NIT | ctrlN_SIMPLEPAT| ctrlN_SIMPLEPMT);
				}
				else if(SdmDemux[dmx].TablesCollectionStatus & SIMPLEPMT_AVAILABLE)
				{
					SdmDemux[dmx].Status = ctrl_OnlyPsiDataAvailable;
					table = (ctrlN_SIMPLEPAT | ctrlN_SIMPLEPMT);
					event = ctrlN_DataAvailable;
				}
				else if(SdmDemux[dmx].TablesCollectionStatus & NIT_AVAILABLE)
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					table = ctrlN_NIT;
					event = ctrlN_DataAvailable;
				}
				else
				{
					event = ctrlN_DataNotAvailable;
				}

				if( ctrlN_iPresent() )
				{
					TraceNotice(m,"TMP_DEBUG %d Notification triggered from SDM",__LINE__);
					ctrlN_OnEvent( dmx, event, table);
				}
			}
			else if (ctrl_FreesatNormal == SdmDemux[dmx].Mode)
			{
				TraceNotice(m,"Timeout happend for Freesat Normal, status 0x%x",SdmDemux[dmx].TablesCollectionStatus);
				if((SdmDemux[dmx].TablesCollectionStatus & SDT_AVAILABLE) &&
						(SdmDemux[dmx].TablesCollectionStatus & NIT_AVAILABLE) && (SdmDemux[dmx].TablesCollectionStatus & BAT_AVAILABLE))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					event = ctrlN_DataAvailable;
					table = (ctrlN_NIT | ctrlN_SDT| ctrlN_BAT);
				}
				else if((SdmDemux[dmx].TablesCollectionStatus & NIT_AVAILABLE) &&  (SdmDemux[dmx].TablesCollectionStatus &  BAT_AVAILABLE))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					event = ctrlN_DataAvailable;
					table = (ctrlN_NIT |  ctrlN_BAT);
				}
				else if(SdmDemux[dmx].TablesCollectionStatus & (NIT_AVAILABLE))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					event = ctrlN_DataAvailable;
					table = ctrlN_NIT;
				}
				else
				{
					event = ctrlN_DataNotAvailable;
				}

				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, event, table);
				}
			}
			else if (ctrl_FreesatPostcode == SdmDemux[dmx].Mode)
			{
				SdmDemux[dmx].Status = ctrl_NoDataAvailable;
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, table);
				}
			}
			else if (ctrl_FreesatMinimalNitOth == SdmDemux[dmx].Mode)
			{
				SdmDemux[dmx].Status = ctrl_NoDataAvailable;
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, table);
				}
			}
			else if (ctrl_FreesatPSIMode == SdmDemux[dmx].Mode)
			{
				SdmDemux[dmx].Status = ctrl_NoDataAvailable;
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, table);
				}
			}
			else if (SdmDemux[dmx].Mode == ctrl_AstraSGT)
			{
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SGT  );
				}
			}
			else if(((mPackageSelected == TRICOLOR_HD_PACKAGE_ID)|| (mPackageSelected == TRICOLOR_SD_PACKAGE_ID)) && (SdmDemux[dmx].Mode == ctrl_TricolorNormal))
			{
				if( ctrlN_iPresent() )
				{
					
					if(CHECK_ALL_TABLE(SdmDemux[dmx].TablesCollectionStatus))
					{
						table = (ctrlN_NIT | ctrlN_SDT |ctrlN_BAT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );								
					}
					else if((SdmDemux[dmx].TablesCollectionStatus & (BAT_AVAILABLE|NIT_AVAILABLE)) == (BAT_AVAILABLE|NIT_AVAILABLE))
					{
						table = (ctrlN_NIT|ctrlN_BAT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );
					}
					else
					{
						TraceNotice(m,"No Data Availble Tricolor Normal");
						ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, table);
						SdmDemux[dmx].Status = ctrl_NoDataAvailable;
					}
				}
			}
			else
			{	
				TraceNotice(m,"[%s] [%d]  \n",__FUNCTION__,__LINE__);
				if (((SdmDemux[dmx].Mode == ctrl_Normal) ||(SdmDemux[dmx].Mode == ctrl_Minimal) ||(SdmDemux[dmx].Mode == ctrl_FransatNormal)) 
					&& ((SdmDemux[dmx].Status == ctrl_NITAvailable) ||(ctrl_SiDataAvailable == SdmDemux[dmx].Status )) )
				{
					if( ctrlN_iPresent() )
					{									
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_NIT  );
					}            
					TraceNotice (m, "Prescan and Canal Digital Phase Handled. No Data Available timeout happened  ");
				}
				else if(  (ctrl_SiDataAvailable == SdmDemux[dmx].Status ) ||
					 (ctrl_SDTAvailable == SdmDemux[dmx].Status ) )
				{
					TraceNotice(m,"[%s] [%d]  \n",__FUNCTION__,__LINE__);
					if( ctrlN_iPresent() )
					{
						if ((SdmDemux[dmx].Mode == ctrl_NormalPlusPmt) && ((mPackageSelected  == CANALDIGITAL_NORWAY_PACKAGE_ID) || \
							(mPackageSelected  == CANALDIGITAL_SWEDEN_PACKAGE_ID) || (mPackageSelected  == CANALDIGITAL_FINLAND_PACKAGE_ID) || (mPackageSelected  == CANALDIGITAL_DENMARK_PACKAGE_ID)))
						{
							if (ctrl_SDTAvailable == SdmDemux[dmx].Status )
							{
								/* Only SDT in NORDIG Manual installation. Give as DataNotAvailable so that SRT doesnt hang
									For full scan once SDT is available, PsiDataAvailable will be sent */
								ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, ctrlN_SDT  );
							}
							else
							{
								ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SDT | ctrlN_NIT );
							}
						}
						else
						{
							TraceNotice(m,"[%s] [%d]  \n",__FUNCTION__,__LINE__);
							/*TODO: Remove NIT here, this is hack for prescan*/
							//ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SDT | ctrlN_NIT );
							ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SDT  );
						}
					}            
				}			
				else
				{   /* Only NIT is also data not available */
					if( ctrlN_iPresent() )
					{
						/*TODO: Hack for prescan test*/
						ctrlN_OnEvent( dmx, ctrlN_DataNotAvailable, (ctrl_NITAvailable == SdmDemux[dmx].Status)? ctrlN_SDT : ctrlN_NIT);
						TraceNotice (m, "DATA AVAILABLE \n");
						
						//ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_NIT  );

					}
					SdmDemux[dmx].Status = ctrl_NoDataAvailable;
				}
            }
            break;
        }
    case evHsvSdmSDTAvailable :
        {
			/* Nothing to be done for Prescan */
			if (SdmDemux[dmx].Mode == ctrl_NormalPlusPmt)
			{
				/* In case of SimpleMpeg Mode, notification should be given
					after SDT and PMT collected */
				if (SdmDemux[dmx].PmtCollectedStatus == TRUE)
				{	
					if( ctrlN_iPresent() )
					{
						if (SdmDemux[dmx].Status == ctrl_NITAvailable)
						{
							/* If NIT also arrived, then while sending update the OR NIT */
							ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SDT | ctrlN_NIT| ctrlN_SIMPLEPMT);
						}
						else
						{
							ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SDT|ctrlN_SIMPLEPMT);
						}
					}
				}
				else
				{
					/* SI data was found in the stream*/
					if( ctrl_NITAvailable == SdmDemux[dmx].Status )
					{
						SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					}
					else
					{
						SdmDemux[dmx].Status = ctrl_SDTAvailable;
					}
				}
			}
			else if ((IS_FRANSAT_PACKAGE(mPackageSelected)) && (SdmDemux[dmx].Mode == ctrl_Minimal))
			{
				/*if package is Fransat and mode minimal then notification is provided only after timeout,
				**This done to provide enough time to collect all available NIT other and SDT other
				*/
				SdmDemux[dmx].TablesCollectionStatus |= SDT_AVAILABLE;
			}
			else if (SdmDemux[dmx].Mode == ctrl_FreesatNormal)
			{
				SdmDemux[dmx].TablesCollectionStatus |= SDT_AVAILABLE;
				SdmDemux[dmx].Status = ctrl_SDTAvailable;
				if(CHECK_ALL_TABLE(SdmDemux[dmx].TablesCollectionStatus))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if( ctrlN_iPresent() )
					{
						table = (ctrlN_NIT | ctrlN_SDT |ctrlN_BAT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );
					}
				}
			}
			else if (((mPackageSelected == TRICOLOR_HD_PACKAGE_ID)|| (mPackageSelected == TRICOLOR_SD_PACKAGE_ID)) && (SdmDemux[dmx].Mode == ctrl_TricolorNormal))
			{
				TraceNotice(m,"SDT Availble Tricolor Normal");
				SdmDemux[dmx].TablesCollectionStatus |= SDT_AVAILABLE;
			}
			else
			{
				/* SI data was found in the stream*/
				if( ctrl_NITAvailable == SdmDemux[dmx].Status )
				{						
					if( ctrlN_iPresent() )
					{
						if(((mPackageSelected == CYFRAPLUS_POLSAT_PACKAGE_ID)|| (mPackageSelected == NTVPLUS_PACKAGE_ID) ) && (SdmDemux[dmx].Mode == ctrl_Minimal))										
						{
							if(CHECK_ALL_TABLE(SdmDemux[dmx].TablesCollectionStatus))
							{
								SdmDemux[dmx].Status = ctrl_SiDataAvailable;	
								if( ctrlN_iPresent() )
								{
									table = (ctrlN_NIT | ctrlN_SDT |ctrlN_BAT );
									ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );								
								}
							}
							else
							{								
								SdmDemux[dmx].TablesCollectionStatus |= SDT_AVAILABLE;
							}
						}
						else
						{
							SdmDemux[dmx].Status = ctrl_SiDataAvailable;						
							ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_NIT | ctrlN_SDT ));
						}						
					}
				}
				else
				{
					SdmDemux[dmx].Status = ctrl_SDTAvailable;
					
					if( ctrlN_iPresent() )
					{
						ctrlN_OnEvent( dmx, ctrlN_SiDataAvailable, ctrlN_SDT);
					}
				}
			}
            break;
        }
    case evHsvSdmNITAvailable :
        {

			if (SdmDemux[dmx].Mode == ctrl_NormalPlusPmt)
			{
				/* SI data was found in the stream*/
				if( ctrl_SDTAvailable == SdmDemux[dmx].Status )
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if (SdmDemux[dmx].PmtCollectedStatus == TRUE)
					{
						if( ctrlN_iPresent() )
						{
							ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_NIT | ctrlN_SDT | ctrlN_SIMPLEPMT));
						}
					}
				}
				else
				{
					SdmDemux[dmx].Status = ctrl_NITAvailable;
				}
			}
			else if (SdmDemux[dmx].Mode == ctrl_HomingMuxData)
			{
				if(ctrl_BATAvailable == SdmDemux[dmx].Status)
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if( ctrlN_iPresent() )
					{
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_NIT | ctrlN_BAT));
					}
				}
				else
				{
					SdmDemux[dmx].Status = ctrl_NITAvailable;
				}
			}	
			else if (SdmDemux[dmx].Mode == ctrl_PkgBuildMode)
			{
				if(ctrl_BATAvailable == SdmDemux[dmx].Status)
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
				}
				else
				{
					SdmDemux[dmx].Status = ctrl_NITAvailable;
				}
			}
			else if(((mPackageSelected == CYFRAPLUS_POLSAT_PACKAGE_ID)|| (mPackageSelected == NTVPLUS_PACKAGE_ID) )&& (SdmDemux[dmx].Mode == ctrl_Minimal))
			{
				if(CHECK_ALL_TABLE(SdmDemux[dmx].TablesCollectionStatus))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;	
					if( ctrlN_iPresent() )					
					{
						table = (ctrlN_NIT | ctrlN_SDT |ctrlN_BAT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );								
					}
				}
				else
				{								
					SdmDemux[dmx].TablesCollectionStatus |= NIT_AVAILABLE;
				}
			}
			else if ((IS_FRANSAT_PACKAGE(mPackageSelected)) && (SdmDemux[dmx].Mode == ctrl_Minimal))
			{
				/*if package is Fransat and mode minimal then notification is provided only after timeout,
				**This done to provide enough time to collect all available NIT other and SDT other
				*/
				SdmDemux[dmx].TablesCollectionStatus |= NIT_AVAILABLE;
			}			
			else if (SdmDemux[dmx].Mode == ctrl_FreesatNormal)
			{
				SdmDemux[dmx].TablesCollectionStatus |= NIT_AVAILABLE;
				SdmDemux[dmx].Status = ctrl_NITAvailable;
				if(CHECK_ALL_TABLE(SdmDemux[dmx].TablesCollectionStatus))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if( ctrlN_iPresent() )
					{
						table = (ctrlN_NIT | ctrlN_SDT |ctrlN_BAT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );
						TraceNotice(m,"TMP_DEBUG %d Notification triggered from SDM",__LINE__);
					}
				}
			}
			else if (SdmDemux[dmx].Mode == ctrl_FreesatMinimalNitAct)
			{
				SdmDemux[dmx].TablesCollectionStatus |= NIT_AVAILABLE;
				SdmDemux[dmx].Status = ctrl_NITAvailable;
				if(SdmDemux[dmx].PmtCollectedStatus)
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if( ctrlN_iPresent() )
					{
						table = (ctrlN_NIT |ctrlN_SIMPLEPAT |ctrlN_SIMPLEPMT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );
					}
				}
			}
			else if (SdmDemux[dmx].Mode == ctrl_FreesatMinimalNitOth)
			{
				SdmDemux[dmx].TablesCollectionStatus |= NIT_AVAILABLE;
				SdmDemux[dmx].Status = ctrl_NITAvailable;
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_NIT );
				}
			}
			else if (((mPackageSelected == TRICOLOR_HD_PACKAGE_ID)|| (mPackageSelected == TRICOLOR_SD_PACKAGE_ID)) && (SdmDemux[dmx].Mode == ctrl_TricolorNormal))
			{
				TraceNotice(m,"NIT Availble Tricolor Normal");
				SdmDemux[dmx].TablesCollectionStatus |= NIT_AVAILABLE;
			}
			else
			{
				/* SI data was found in the stream*/
				if( ctrl_SDTAvailable == SdmDemux[dmx].Status )
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if( ctrlN_iPresent() )
					{
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_NIT | ctrlN_SDT));
					}
				}
				else
				{
					SdmDemux[dmx].Status = ctrl_NITAvailable;
				}
			}
            break;
        }
	case evHsvSdmSIMPLEPATAvailable :
		{
			if ((ctrl_FreesatMinimalNitAct == SdmDemux[dmx].Mode) ||(ctrl_FreesatPSIMode == SdmDemux[dmx].Mode))
			{
				/*provide notification after PMT and NIT avaialble*/
				SdmDemux[dmx].TablesCollectionStatus |= SIMPLEPAT_AVAILABLE;
			}
			else
			{
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SIMPLEPAT);
				}
			}
			break;
		}

	case evHsvSdmSIMPLEPMTAvailable :
		{
			SdmDemux[dmx].PmtCollectedStatus = TRUE;
			if (ctrl_FreesatMinimalNitAct == SdmDemux[dmx].Mode)
			{
				SdmDemux[dmx].TablesCollectionStatus |= SIMPLEPMT_AVAILABLE;
				SdmDemux[dmx].Status = ctrl_OnlyPsiDataAvailable;

				if((SdmDemux[dmx].TablesCollectionStatus & NIT_AVAILABLE) && (ctrlN_iPresent()))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					table = (ctrlN_NIT |ctrlN_SIMPLEPAT |ctrlN_SIMPLEPMT );
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );
					TraceNotice(m,"TMP_DEBUG %d Notification triggered from SDM",__LINE__);
				}
			}
			else if (ctrl_FreesatPSIMode == SdmDemux[dmx].Mode)
			{
				SdmDemux[dmx].TablesCollectionStatus |= SIMPLEPMT_AVAILABLE;
				SdmDemux[dmx].Status = ctrl_OnlyPsiDataAvailable;
				if(ctrlN_iPresent())
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SIMPLEPMT );
				}
			}
			else if(  (ctrl_SiDataAvailable == SdmDemux[dmx].Status ) ||
                 (ctrl_SDTAvailable == SdmDemux[dmx].Status ) )
			{
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SDT|ctrlN_SIMPLEPMT);
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
				SdmDemux[dmx].TablesCollectionStatus = 0;
                SdmDemux[dmx].Mode   = (eventmask & 0xFFFF);            /* The last 16 bits of the event parameter contain the mode value */
                TraceNotice(m,"TMP_DEBUG SDM mode update, mode 0x%x", SdmDemux[dmx].Mode);
            
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
            
			TraceNotice(m,"Demux Strarted");
            if( ctrl_Invalid == SdmDemux[ dmx ].Status || ctrl_NoDataAvailable == SdmDemux[ dmx ].Status )
            {
				/* ANEESH: TODO: Extend this here */
				if ((SdmDemux[dmx].Mode == ctrl_NormalPlusPmt) || (SdmDemux[dmx].Mode == ctrl_FreesatMinimalNitAct) ||(SdmDemux[dmx].Mode == ctrl_FreesatPSIMode) || (SdmDemux[dmx].Mode == IHsvSdmControl2_FreesatMinimalSdtOth))
				{
					SdmDemux[dmx].PmtCollectedStatus = FALSE;
					hsvsimplempeg_enable_Enable(dmx);	
				}
				if(DVB_SI_ENABLED)
				{
					TraceNotice(m,"Si enabling started");
					hsvdvbsi_ena_Enable(dmx);
				}
				

                /* Start the no data timer */
                pmp_PmpSendAfter( NoDataPump, dmx, PROCESS_MESSAGE, getTimeOut() * TARGET_CORRECTION);


                /* Generate another timeout, to ensure that we notify clients to start collecting data from us */
                pmp_PmpSendAfter( SyncPump, dmx, PROCESS_MESSAGE, div_DataCollectionTimeout * TARGET_CORRECTION );
                
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
				if ((SdmDemux[dmx].Mode == ctrl_NormalPlusPmt) ||(SdmDemux[dmx].Mode == ctrl_FreesatMinimalNitAct) ||(SdmDemux[dmx].Mode == ctrl_FreesatPSIMode) || (SdmDemux[dmx].Mode == IHsvSdmControl2_FreesatMinimalSdtOth))
				{
					TraceNotice (m, "Sdm: SimpleMpeg Synced ");
					hsvsimplempeg_enable_Sync (dmx);
				}

                if(DVB_SI_ENABLED)
				{
					hsvdvbsi_ena_Sync( dmx );
				}
				
            }
            //SyncFilter(dmx);
            break;
        }
    case evHsvSdmStop :
        {
            if( SdmDemux[dmx].Mode != ctrl_Idle )
            {
				PrintfNotice ("%d %s Inside pump handler of stop collection ... \n", __LINE__, __FUNCTION__);
               /* diable sdm components (synchronously to avoid conflicts 
                between OnInstanceremoved and the caller of this function */
                /* SDM has to be stopped */

				if(DVB_SI_ENABLED)
				{
					hsvdvbsi_ena_Disable(dmx);
				}

				if ((SdmDemux[dmx].Mode == ctrl_NormalPlusPmt) || (SdmDemux[dmx].Mode == ctrl_FreesatMinimalNitAct) ||(SdmDemux[dmx].Mode == ctrl_FreesatPSIMode) || (SdmDemux[dmx].Mode == IHsvSdmControl2_FreesatMinimalSdtOth))
				{
					TraceNotice (m, "Sdm: SimpleMpeg Disabled ");
					hsvsimplempeg_enable_Disable(dmx);
				}
				else
				{
					TraceNotice(m,"Demux Disabling");
	                dmxena_Disable(dmx);
					
	                /* Reset the mode and status values */
	                SdmDemux[dmx].Mode      = ctrl_Idle;
	                SdmDemux[dmx].Status    = ctrl_Invalid;
					SdmDemux[dmx].TablesCollectionStatus = 0;

	                /* Erase our timers by send a pump message with a small value */
	                pmp_PmpSendAfter( NoDataPump, 0, IGNORE_MESSAGE, 20 );
	                pmp_PmpSendAfter( SyncPump, 0, IGNORE_MESSAGE, 20 );
				}
			}
			else
			{
				TraceNotice(m,"SdmDemux[dmx].Mode is Idle %d",SdmDemux[dmx].Mode);
			}

            if( ctrlN_iPresent() && (SdmDemux[dmx].Mode != ctrl_NormalPlusPmt) && (SdmDemux[dmx].Mode != ctrl_FreesatMinimalNitAct) && (SdmDemux[dmx].Mode != ctrl_FreesatPSIMode) && (SdmDemux[dmx].Mode != IHsvSdmControl2_FreesatMinimalSdtOth))
            {
                ctrlN_OnEvent( dmx, ctrlN_StoppedCollection, 0 );
            }
            
            break;
        }
	case	evHsvSdmBatAvailable:
		{		
			if (SdmDemux[dmx].Mode == ctrl_HomingMuxData)
			{
				if(ctrl_NITAvailable == SdmDemux[dmx].Status)
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if( ctrlN_iPresent() )
					{
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_NIT | ctrlN_BAT));
					}
				}
				else
				{
					SdmDemux[dmx].Status = ctrl_BATAvailable;
				}
			}
			else if (SdmDemux[dmx].Mode == ctrl_PkgBuildMode)
			{
				if(ctrl_NITAvailable == SdmDemux[dmx].Status)
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
				}
				else
				{
					//Incase of Tricolor No need to wait for 15seconds time out.Notify immediately.
					if((mPackageSelected == TRICOLOR_HD_PACKAGE_ID)|| (mPackageSelected == TRICOLOR_SD_PACKAGE_ID))
					{
						SdmDemux[dmx].Status = ctrl_BATAvailable;
						SdmDemux[dmx].TablesCollectionStatus |= BAT_AVAILABLE;
						if( ctrlN_iPresent() )
						{
							ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_BAT);
						}
					}
					else
					{
						SdmDemux[dmx].Status = ctrl_BATAvailable;
					}
					
				}
			}
			else if ((IS_FRANSAT_PACKAGE(mPackageSelected)) && (SdmDemux[dmx].Mode == ctrl_Minimal))
			{
				/*if package is Fransat and mode minimal then notification is provided only after timeout,
				**This done to provide enough time to collect all available NIT other and SDT other
				*/
				SdmDemux[dmx].TablesCollectionStatus |= BAT_AVAILABLE;
			}			
			else if (SdmDemux[dmx].Mode == ctrl_FreesatNormal)
			{
				SdmDemux[dmx].TablesCollectionStatus |= BAT_AVAILABLE;
				SdmDemux[dmx].Status = ctrl_BATAvailable;
				if(CHECK_ALL_TABLE(SdmDemux[dmx].TablesCollectionStatus))
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if( ctrlN_iPresent() )
					{
						table = (ctrlN_NIT | ctrlN_SDT |ctrlN_BAT );
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, table );
					}
				}
			}
			else if (((mPackageSelected == TRICOLOR_HD_PACKAGE_ID)|| (mPackageSelected == TRICOLOR_SD_PACKAGE_ID)) && (SdmDemux[dmx].Mode == ctrl_TricolorNormal))
			{
				TraceNotice(m,"BAT Availble Tricolor Normal");
				SdmDemux[dmx].TablesCollectionStatus |= BAT_AVAILABLE;
			}			
			else
			{
				if(((mPackageSelected == CYFRAPLUS_POLSAT_PACKAGE_ID)|| (mPackageSelected == NTVPLUS_PACKAGE_ID) ) && (SdmDemux[dmx].Mode == ctrl_Minimal))
				{
					if(CHECK_ALL_TABLE(SdmDemux[dmx].TablesCollectionStatus))
					{
						SdmDemux[dmx].Status = ctrl_SiDataAvailable;
						if( ctrlN_iPresent() )
						{
							ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_BAT|ctrlN_NIT|ctrlN_SDT);
						}	
					}
					else
					{
						SdmDemux[dmx].TablesCollectionStatus |= BAT_AVAILABLE;					
					}
				}
				else
				{
					SdmDemux[dmx].TablesCollectionStatus |= BAT_AVAILABLE;
					if( ctrlN_iPresent() )
					{
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_BAT);
					}	
				}
				
			}
			break;
		}
	case	 evHsvSdmFNTAvailable:
		{
			if( ctrl_FSTAvailable == SdmDemux[dmx].Status )
			{
				SdmDemux[dmx].Status = ctrl_SiDataAvailable;
				if( ctrlN_iPresent() )
				{	/*TODO: uncomment this when table comeplete is sent properly from demux */
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_FNT | ctrlN_FST));
				}
			}
			else
			{
				SdmDemux[dmx].Status = ctrl_FNTAvailable;
			}
            break;
		}
	case 	evHsvSdmFSTAvailable:
		{
				if( ctrl_FNTAvailable == SdmDemux[dmx].Status )
				{
					SdmDemux[dmx].Status = ctrl_SiDataAvailable;
					if( ctrlN_iPresent() )
					{
						/*TODO: uncomment this when table comeplete is sent properly from demux */
						ctrlN_OnEvent( dmx, ctrlN_DataAvailable, (ctrlN_FNT | ctrlN_FST) );
					}
				}
				else
				{
					SdmDemux[dmx].Status = ctrl_FSTAvailable;
				}
		break;	
		}
	case 	evHsvSdmSGTAvailable:
		{
			if (SdmDemux[dmx].Mode == ctrl_AstraSGT)
			{
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_SGT  );
				}
			}
		break;	
		}
	case	evHsvSdmMPEGStopped:
		{
			TraceNotice(m,"SimpleMPEG stopped");
			dmxena_Disable(dmx);
			
	        /* Reset the mode and status values */
	        SdmDemux[dmx].Mode      = ctrl_Idle;
	        SdmDemux[dmx].Status    = ctrl_Invalid;
			SdmDemux[dmx].TablesCollectionStatus = 0;

	        /* Erase our timers by send a pump message with a small value */
	        pmp_PmpSendAfter( NoDataPump, 0, IGNORE_MESSAGE, 20 );
	        pmp_PmpSendAfter( SyncPump, 0, IGNORE_MESSAGE, 20 );

	        if( ctrlN_iPresent())
	        {
	            ctrlN_OnEvent( dmx, ctrlN_StoppedCollection, 0 );
	        }
	        
		}
		break;
	case evHsvSdmPostcodeAvailable:
		if (ctrl_FreesatPostcode == SdmDemux[dmx].Mode)
		{
				SdmDemux[dmx].Status = ctrl_SiDataAvailable;
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_Postcode);
				}
		}
		break;
	case evHsvSdmTOTAvailable:
		{
			
			if(SdmDemux[dmx].Mode == ctrl_FransatCamIns)
			{
				SdmDemux[dmx].Status = ctrl_TOTAvailable;
				if( ctrlN_iPresent() )
				{
					ctrlN_OnEvent( dmx, ctrlN_DataAvailable, ctrlN_TOT  );
				}
				TraceNotice (m, "TOT acquisition done for Fransat");
			}
		}
	break;		
    default :
        {
            /* Ignore all other events */
            break;
        }
    }   /* End of switch( SdmDemux[dmx].Status )   */     
}   /* End of function SdmControlEventHandler() */
/*********************************************************************/
/* Functions of the IHsvSdmControlNotify interface, required by the SI data manager  */
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
		case hsvdvbsi_ctrlN_BAT:
			pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmBatAvailable, 0 ) );
            break;
		case hsvdvbsi_ctrlN_FST:
            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmFSTAvailable, 0 ) );
            break;
        case hsvdvbsi_ctrlN_FNT:
            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmFNTAvailable, 0 ) );
            break;
		case hsvdvbsi_ctrlN_Postcode:
			pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmPostcodeAvailable, 0 ) );
            break;
		case hsvdvbsi_ctrlN_SGT:
            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmSGTAvailable, 0 ) );
            break;
		case hsvdvbsi_ctrlN_TOT:
            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmTOTAvailable, 0 ) );
            break;
    }
}


/*********************************************************************/
/* Functions of the IHsvSdmControlNotify interface, required by the SI data manager  */
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::hsvsimplempeg_ctrlN_OnEvent( HsvDemux dmx, int eventid, int value  )
{
	if(eventid == hsvdvbsi_ctrlN_StoppedCollection)
	{
		pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmMPEGStopped, 0 ) );
	}
	else
	{
	    switch (value)
	    {
	        case hsvdvbsi_ctrlN_SIMPLEPAT:
	            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmSIMPLEPATAvailable, 0 ) );
	            break;
	        case hsvdvbsi_ctrlN_SIMPLEPMT:
	            pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmSIMPLEPMTAvailable, 0 ) );
	            break;
	    }
	}
}


/*********************************************************************/
/* Notifications obtained through the demux notification interface from the 
   demux controller */
/*********************************************************************/
void CHsvDvbStreamingDataManager_m_Priv::phsvdmxN_OnStarted( HsvDemux dmx )
{    
    pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmDmxStarted, 0 ) );
    if( hsvdmxN_iPresent() )
    {
        hsvdmxN_OnStarted( dmx );
    }
}

void CHsvDvbStreamingDataManager_m_Priv::phsvdmxN_OnStopped( HsvDemux dmx )
{
    /*pmp_PmpSend( ControlPump, dmx, HSV_CREATE_EVENT_MASK( evHsvSdmDmxStopped, 0 ) );*/
    if( hsvdmxN_iPresent() )
    {
        hsvdmxN_OnStopped( dmx );
    }
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
                retval  = TRUE;
                break;
            }
        case HsvExtraProgram1 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram1 = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram2 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram2 = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram3 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram3 = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram4 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram4 = (HSV_INVALID_FILTER_VALUE);
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram5 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram5 = (HSV_INVALID_FILTER_VALUE);
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
    
    if( !strmfltr_IsSet(dest, filterid, value ) )
    {                
        switch(filterid)
        {
        case HsvStartMode:       
            break;
        case HsvCurrentCountry:  
            conf_CurrentCountry                                          = value;
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentCountry = value;
            retval                                                       = TRUE;
            break;
        case HsvCurrentLanguage: 
            break;
        case HsvCurrentProgram:
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].CurrentProgram = value;
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].WaitingFor    |= SET_BIT(HsvCurrentProgram);                        
            hsvdvbsi_strmfltr_Set( dest, filterid, value);            
            /* Generate another timeout, to ensure that we notify clients to start collecting data from us */
            pmp_PmpSendAfter( SyncPump, HSV_MAP_DEST_TO_DMX(dest), PROCESS_MESSAGE, div_DataCollectionTimeout * TARGET_CORRECTION );
            retval = TRUE;
            break;
        case HsvOtherSDTOnwidId: 
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTOnwidId = value;
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].WaitingFor    |= SET_BIT(HsvOtherSDTOnwidId);
            hsvdvbsi_strmfltr_Set( dest, filterid, value);
            retval                                                       = TRUE;
            pmp_PmpSendAfter( SyncPump, HSV_MAP_DEST_TO_DMX(dest), PROCESS_MESSAGE, div_DataCollectionTimeout * TARGET_CORRECTION );
            break;
        case HsvOtherSDTServiceId:
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].OtherSDTServiceId = value;
            StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].WaitingFor    |= SET_BIT(HsvOtherSDTServiceId);            
            hsvdvbsi_strmfltr_Set( dest, filterid, value);
            retval                                                       = TRUE;
            pmp_PmpSendAfter( SyncPump, HSV_MAP_DEST_TO_DMX(dest), PROCESS_MESSAGE, div_DataCollectionTimeout * TARGET_CORRECTION );
            break;

           /* Extra properties do not excite a filter notification */
        case HsvExtraProgram0 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram0 = value;
                retval  = TRUE;
                break;
            }
        case HsvExtraProgram1 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram1 = value;
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram2 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram2 = value;
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram3 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram3 = value;
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram4 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram4 = value;
                retval  = TRUE;
                break;                
            }
        case HsvExtraProgram5 :
            {
                StreamFilterValues[HSV_MAP_DEST_TO_DMX(dest)].ExtraProgram5 = value;
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
        pmp_PmpSendAfter( SyncPump, HSV_MAP_DEST_TO_DMX(dest), PROCESS_MESSAGE, div_DataCollectionTimeout * TARGET_CORRECTION );
        retval = TRUE;
    }
    return retval;
}/* End of function strmfltr_Set() */
/*************************************************************/



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
    Bool    retval = FALSE;
    Nat16   onid = 0;
	

    
    if( (StreamFilterValues[dmx].CurrentProgram) )
    {
        istrapi_GetByKey(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0, &onid) ;
        *onwid = onid;
        *svcid = StreamFilterValues[dmx].CurrentProgram;
        retval = TRUE;
    }

    return retval;
} 
Bool CHsvDvbStreamingDataManager_m_Priv::hsvdvbsi_dvbsvc_GetCurrentService2 (HsvDemux dmx, int *onwid, int *tsid,int *svcid)
{
    Bool    retval = FALSE;
    Nat16   onid = 0;
	Nat16   TsId = 0;
    
    if( (StreamFilterValues[dmx].CurrentProgram) )
    {
        istrapi_GetByKey(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0, &onid) ;
		istrapi_GetByKey(HSV_MAP_DMX_TO_DEST(dmx), HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, &TsId) ;
        *onwid = onid;
		*tsid = TsId;
        *svcid = StreamFilterValues[dmx].CurrentProgram;
        retval = TRUE;
	}
	
    return retval;
}

/* End of function hsvdvbsi_dvbsvc_GetCurrentService () */
/*************************************************************/

int CHsvDvbStreamingDataManager_m_Priv::ictrl_GetMode(HsvDemux dmx)
{
	return ctrl_GetMode(dmx);
}

int CHsvDvbStreamingDataManager_m_Priv::ictrl_GetStatus(HsvDemux dmx)
{
	return ctrl_GetStatus(dmx);
}

void CHsvDvbStreamingDataManager_m_Priv::ictrl_StartCollection(HsvDemux dmx, int mode)
{
	return ctrl_StartCollection(dmx, mode);
}

void CHsvDvbStreamingDataManager_m_Priv::ictrl_StopCollection(HsvDemux dmx)
{
	return ctrl_StopCollection(dmx);
}


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
    default :
        retval = 0;
        break;        
    }
    
    /* Put the 3 char country code in the lower 3 bytes and send out. */
    return retval;
}


int CHsvDvbStreamingDataManager_m_Priv::getTimeOut(void)
{
	HsvSDMSIDataValues SiValues;	
	int retval = 0;

	SiValues.TableId = INVALID_TABLEID;
	pakgins_GetSIDetails(&SiValues);
	
	if(SdmDemux[HsvDmxMain].Mode == ctrl_M7Minimal)
	{
		retval = M7_TIMEOUT;
	}
	else if(SdmDemux[HsvDmxMain].Mode == ctrl_PkgBuildMode )
	{
		retval = FRANSAT_DATA_ACQ_TIMEOUT;
	}
	else if(SdmDemux[HsvDmxMain].Mode == ctrl_FreesatNormal)
	{
		retval = FREESAT_NORMAL_TIMEOUT;
	}
	else if(SdmDemux[HsvDmxMain].Mode == ctrl_FreesatMinimalNitAct)
	{
		retval = FREESAT_NORMAL_PLUS_PMT_TIMEOUT;
	}
	else if(SdmDemux[HsvDmxMain].Mode == ctrl_FreesatPostcode)
	{
		retval = FREESAT_POSTCODE_TIMEOUT;
	}
	else if(SdmDemux[HsvDmxMain].Mode == ctrl_FreesatMinimalNitOth)
	{
		retval = FREESAT_NORMAL_PLUS_PMT_TIMEOUT;
	}
	else if(SdmDemux[HsvDmxMain].Mode == ctrl_FreesatPSIMode)
	{
		retval = FREESAT_NORMAL_PLUS_PMT_TIMEOUT;
	}
	else if(SdmDemux[HsvDmxMain].Mode == ctrl_AstraSGT )
	{
		retval = SGT_TIMEOUT;
	}
	else if(SiValues.TableId == SDT_OTHER_TABLE_ID)
	{

		mPackageSelected = ins_GetAttribute(ins_InstallationNone, ins_AttributePackageId);
		/*masking mPackageSelected with 0xFFFF, since for fransat first 16bits are package id and next 16 bits are bouquet id*/
              switch ((mPackageSelected & 0xFFFF)) 
              {              
                  case NTVPLUS_PACKAGE_ID:
                        retval = NTVPLUS_SDTOTHER_TIMEOUT;
                        break;            
                  case POLAND_N_PACKAGE_ID:
                        retval = N_SDTOTHER_TIMEOUT;
                        break;
				  case FRANSAT_PACKAGE_ID:
				  	     retval = FRANSAT_SDTOTHER_TIMEOUT;
						 break;
                  default:
                        retval = CANAL_SDTOTHER_TIMEOUT;
                        break;                    
              }
	}
	else
	{
		retval = div_SdmWaitTime;
	}
	TraceNotice(m,"timeout = %d",retval);
	return retval;
}




void CHsvDvbStreamingDataManager_m_Priv::pdmxsecfN_OnRequestCancelled( Nat32 subscrid )
{
    hsvdvbsi_dmxsecfN_OnRequestCancelled( subscrid );

    if( dmxsecfN_iPresent() )
    {
        dmxsecfN_OnRequestCancelled( subscrid );
    }
}

void CHsvDvbStreamingDataManager_m_Priv::pdmxsecfN_OnRequestAllowed( HsvDestination dest )
{
    if( dmxsecfN_iPresent() )
    {
        dmxsecfN_OnRequestAllowed( dest );
    }
}

void CHsvDvbStreamingDataManager_m_Priv::pdmxsecfN_OnRequestNotAllowed()
{
	if( dmxsecfN_iPresent() )
    {
        dmxsecfN_OnRequestNotAllowed();
    }
}

