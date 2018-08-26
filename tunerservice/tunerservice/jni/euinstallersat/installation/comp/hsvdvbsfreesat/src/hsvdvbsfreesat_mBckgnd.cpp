/*****************************************************************************************
  *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
  *
  *  This  source code and any compilation or derivative thereof is the proprietary
  *  information of Koninklijke Philips Electronics N.V. and is confidential in nature.
  *  Under no circumstances is this software to be exposed to or placed under an Open
  *  Source License of any type without the expressed written permission of Koninklijke
  *  Philips Electronics N.V.
  *
  *  %name: hsvdvbsfreesat_mBckgnd.cpp %
  *  %version:  TVG_1 %
  *  %date_modified:  %
  *  %derived_by:  anuma %
  *
  ****************************************************************************************/

/*****************************************************************************************
 * Include files
 *****************************************************************************************/
#include "CHsvDvbsFreesat_mBckgnd.h"


/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/
TRACESYMBOL(m, "installation/hsvdvbsfreesat/hsvdvbsfreesat_mBckgnd")


/****************************************************************************
 * Static variables
 ****************************************************************************/

Bool CHsvDvbsFreesat_mBckgnd::mActive = FALSE;
Bool CHsvDvbsFreesat_mBckgnd::mUpdateDone = FALSE;




/*****************************************************************************************
 * Public methods
 *****************************************************************************************/

/* Overridden IHsvPower methods */

void CHsvDvbsFreesat_mBckgnd::Init (void)
{
   mUpdateDone = FALSE;
}

void CHsvDvbsFreesat_mBckgnd::TurnOn (void)
{
    mActive = FALSE;
    mUpdateDone = FALSE;
}

void CHsvDvbsFreesat_mBckgnd::TurnOff (void)
{
    mActive = FALSE;
    mUpdateDone = FALSE;
}


/* Overridden IHsvSatelliteBackgroundInstallation methods */
void CHsvDvbsFreesat_mBckgnd::EnableBackgroundInstallation (void)
{
    mActive = TRUE;
    TraceNotice (m, "mActive %d\n", mActive);
}


void CHsvDvbsFreesat_mBckgnd::DisableBackgroundInstallation (void)
{
    mActive = FALSE;
}

/* Overridden IHsvStreamNotify methods */

void CHsvDvbsFreesat_mBckgnd::OnAdded (HsvDestination dest, int spid, int key1, int key2, int key3)
{
    HSVSPTYPE(OtherTSService, dvb, sdt) service;

    if(mActive && BACKGROUND_INSTALL)
    {
        switch(spid)
        {
            case HSVSPID(OtherTSService, dvb, sdt):
               if (TRUE == strapi->GetByKey(dest, HSVSPID(OtherSDTSection, dvb, sdt), key1, key2, key3, &service))
                {
                	TraceNotice(m,"%s %d key1 %d, key2 %d, key3 %d",__FUNCTION__,__LINE__,key1,key2,key2);
                    if(UpdateServiceTable(service))
					{												
					    TraceNotice(m,"%s %d ",__FUNCTION__,__LINE__);
						mUpdateDone = TRUE;
					}
                }
                break;
            default:
                break;
        }
    }
	if(!mUpdateDone)
	{
		TraceNotice(m,"%s Background Service Name update failed !!!!",__FUNCTION__);
	}
}

void CHsvDvbsFreesat_mBckgnd::OnChanged (HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
	
    HSVSPTYPE(OtherTSService, dvb, sdt) service;

	//TraceNotice(m,"%s %d mActive %d BACKGROUND_INSTALL %d ",__FUNCTION__,__LINE__,mActive,BACKGROUND_INSTALL);
    if(mActive && BACKGROUND_INSTALL)
    {
        switch(spid)
        {
           
            case HSVSPID(OtherTSService, dvb, sdt):
            {
			   TraceNotice(m,"%s %d key1 %d, key2 %d, key3 %d",__FUNCTION__,__LINE__,key1,key2,key2);
               if (TRUE == strapi->GetByKey(dest, HSVSPID(OtherSDTSection, dvb, sdt), key1, key2, key3, &service))
               {
               		TraceNotice(m,"%s %d ",__FUNCTION__,__LINE__);
                    if(UpdateServiceTable(service))
					{
						TraceNotice(m,"%s %d ",__FUNCTION__,__LINE__);
						mUpdateDone = TRUE;
					}
               }
            }
            break;
            default:
                break;
        }
    }

	if(!mUpdateDone)
	{
		TraceNotice(m,"%s Background Service Name update failed !!!!",__FUNCTION__);
	}
	
    UNUSED(eventid);
}

void CHsvDvbsFreesat_mBckgnd::OnRemoved (HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbsFreesat_mBckgnd::OnCompleted (HsvDestination dest, int spid)
{
    UNUSED(dest);
    UNUSED(spid);
}



/*****************************************************************************************
 * Internal methods
 *****************************************************************************************/

Bool CHsvDvbsFreesat_mBckgnd::UpdateServiceTable (HSVSPTYPE(OtherTSService, dvb, sdt) service)
{
    HsvChannel svcChannel;
    HsvPgdatDigServiceData svcData;
    HsvPgdatPresetData   presetData;
	int MultiplePresetList[MAX_NUM_LCN_ENTRY];
	
	//int FreesatSidList[2];
	//mCollectFreesatSidForTriplet(service,&FreesatSidList);

	int ret = pgdat->GetDigitalChannelForFreesat(MultiplePresetList,service.Original_NetworkId, service.Tsid, service.ServiceId, 0);
	

	for(int i=0;i<MAX_NUM_LCN_ENTRY;i++)
	{
	    if (IHsvErrorCodeEx_Ok == ret)
	    {
	    	TraceNotice(m,"MultiplePresetList[%d] %d",i,MultiplePresetList[i]);
	    	if(MultiplePresetList[i] != INVALID_PRESET)
			{
				svcChannel.Channel.Digit = MultiplePresetList[i];
				svcChannel.Type = AppApiOnePart;
				svcChannel.Ptc = 0;

				
		    	TraceNotice(m,"PresetNumber %d",svcChannel.Channel.Digit);
		        presetData.PresetNumber = svcChannel.Channel.Digit;
		        pgdb->GetByKey(PRESET_TABLE, (Address) &presetData);

		        svcData.Tpid = presetData.Tpid;
		        svcData.ServiceId = presetData.ServiceId;
				TraceNotice(m,"%s %d svcData.ServiceId %d ",__FUNCTION__,__LINE__,svcData.ServiceId);
		        if (TRUE == pgdb->GetByKey(SERVICE_TABLE, (Address)&svcData))
		        {
		        	TraceNotice(m,"svcData.ChannelName [%s] service.ServiceName [%s]",svcData.ChannelName,service.ServiceName);
		            if (mCompareUnicodeString(svcData.ChannelName, service.ServiceName) == FALSE)
		            {
		                TraceNotice (m, "ChannelName update for Preset %d ", svcChannel.Channel.OnePart);
		                //pgdat->StoreChannelDataString (svcChannel,IHsvProgramData3_StringChannelName,service.ServiceName,eurdiv->ChannelNameLength());
		                mCopyString( svcData.ChannelName, service.ServiceName, (eurdiv->PresetNameLength() - 1) );
		                pgdb->Update(SERVICE_TABLE, (Address)&svcData);
		            }
		            else
		            {
		                TraceDebug (m, " ChannelName same  for Preset %d ", svcChannel.Channel.OnePart);
		            }
		        }
			}
	    }
	}
	return TRUE;
}

void CHsvDvbsFreesat_mBckgnd::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}

Bool CHsvDvbsFreesat_mBckgnd::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
    Bool retval = TRUE;

    while((*src) && (*dest) && (*dest == *src))
    {
        dest++;
        src++;
    }
    if((*src) || (*dest))
    {
    	retval = FALSE;
    }

    return retval;
}

Bool CHsvDvbsFreesat_mBckgnd::mIsBackgroundInstall (void)
{
    int mode, state;

    insstate->GetCurrentInstallationState (&mode, &state);

    return ((mode == BACKGROUND_MODE) ? TRUE : FALSE);
}

/****************** Requirement Descoped for freesat BAT Triggered BackGroundUpdate**********************/
#if 0
Bool CHsvDvbsFreesat_mBckgnd::mCollectFreesatSidForTriplet()

Pump CHsvDvbsFreesat_mBckgnd::mBckgndPump = 0xFFFF;
CHsvDvbsFreesat_mBckgnd::BckgndInstance CHsvDvbsFreesat_mBckgnd::mBckgndStatus;

void CHsvDvbsFreesat_mBckgnd::Init (void)
{
   mBckgndPump = m_pfac.PmpCreate(pen->PumpEngine(), &CHsvDvbsFreesat_mBckgnd::PumpHandler, TRUE, (char *)"hsvdvbsfreesat_mBckgnd", this);
}

void CHsvDvbsFreesat_mBckgnd::OnEvent (HsvDemux dmx, int eventid, int value)
{
    UNUSED(dmx);

    if (mActive && BACKGROUND_INSTALL)
    {
        switch (eventid)
        {
        case IHsvSdmControlNotifyEx_DataAvailable:
            if (StIdle == CURRENT_BCKGND_STATE)
            {
                switch (value)
                {
                case IHsvSdmControlNotifyEx_BAT:
                    if (TRUE == mIsBATVersionChanged())
                    {
                        TraceNotice(m, "%s() @ %d : Triggering BAT Update\n", __FUNCTION__, __LINE__);
                        m_pfac.PmpSendAfter (mBckgndPump, EvStart, (Nat32)NULL, 1000);
                    }
                    break;
                default:
                    break;
                }
            } else {
                m_pfac.PmpSend (mBckgndPump, EvDataAvailable, value);
            }
            break;
        case IHsvSdmControlNotifyEx_DataNotAvailable:
            if (StIdle != CURRENT_BCKGND_STATE)
            {
                m_pfac.PmpSend (mBckgndPump, EvDataNotAvailable, (Nat32)NULL);
            }
		case IHsvSdmControlNotifyEx_StoppedCollection:
            if (StIdle != CURRENT_BCKGND_STATE)
            {
			    m_pfac.PmpSend (mBckgndPump, EvStartCollection, (Nat32)NULL);
            }
			break;
        default:
            break;
        }
    }
}


/* Overridden IHsvDigitalAcquisitionNotify methods */

void CHsvDvbsFreesat_mBckgnd::OnDataAquired  (Bool Status)
{
	// service scan completed, send compte notification
	SET_BCKGND_STATE(StServiceInstallComplete);
	m_pfac.PmpSend (mBckgndPump, EvInstallComplete, (Nat32)TRUE);
}

void CHsvDvbsFreesat_mBckgnd::FuncStopBackgroundInstallation (Nat32 param)
{
	SET_BCKGND_STATE (StIdle);
	UNUSED (param);
}

Bool CHsvDvbsFreesat_mBckgnd::mIsBATVersionChanged (void)
{
	Bool isChanged = FALSE;
    HsvPgdatDigServiceData svcData;
    HsvPgdatPresetData presetData;
    HSVSPTYPE(ActualServiceList,dvb,bat) batService;
    int curBouquetId = 0xFF;
    Nat32 dBaseBouquetId = 0xFF;

    Nat32 numPresetRecs = pgdb->GetNoRecords (PRESET_TABLE);
    Nat32 numBATEntries = strapi->GetSize(HsvMain, HSVSPID(ActualServiceList, dvb, bat));

    // Get the installed bouquetId from persistence
	dBaseBouquetId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeBouquetId);

    if (strapi->GetByKey(HsvMain,HSVSPID(ActualBouquetId, dvb, bat), 0, 0, 0, (void *)(&curBouquetId)))
    {
        TraceNotice (m, "%s() @ %d : dBaseBouquetId %d, curBouquetId %d\n", __FUNCTION__, __LINE__, dBaseBouquetId, curBouquetId);
        if (curBouquetId != dBaseBouquetId)
        {
            TraceNotice (m, "%s() @ %d : Ignoring the BAT version change....\n", __FUNCTION__, __LINE__);
            return isChanged;
        }
    }

    // ECN check is added because when PDSD is invalid or not availabe then the database will be empty
    // which will cause unexpected BAT triggered update.
    if((numPresetRecs > 0) && (numBATEntries > 0))
    {
        // Get the first service from PRESET_TABLE and check for valid LCN range
        if(pgdb->GetByIndex(PRESET_TABLE, (numPresetRecs - 1), (Address)&presetData))
        {
            TraceNotice (m, "%s() @ %d : PRESET_TABLE[0] - {%d, %d, %d}, Preset %d\n", __FUNCTION__, __LINE__,
                             presetData.OriginalNetworkId, presetData.Tsid, presetData.ServiceId, presetData.PresetNumber);
            if (VALID_LCN_RANGE(presetData.PresetNumber))
            {
                if (strapi->GetByKey(HsvMain, HSVSPID(ActualServiceList, dvb, bat), presetData.OriginalNetworkId,
                                     presetData.Tsid, presetData.ServiceId, (void*)(&batService)))
                {
                    svcData.Tpid = presetData.Tpid;
                    svcData.ServiceId = presetData.ServiceId;
                    if(pgdb->GetByKey(SERVICE_TABLE, (Address)&svcData))
                    {
                        TraceNotice(m, "%s() @ %d : dBaseBatVers %d, curBatVer %d\n", __FUNCTION__, __LINE__,
                                        svcData.ServiceListVersion, batService.VersionNumber);
                        if (svcData.ServiceListVersion != batService.VersionNumber)
                        {
                            // Current BAT version differs from installed service list version
                            isChanged = TRUE;
                        }
                    }
                }
                else
                {
                    // Service from PRESET_TABLE is not present in BAT ==> BAT version has changed
                    isChanged = TRUE;
                }
            }
        }
    }

    TraceNotice(m, "%s() @ %d : isChanged %s\n", __FUNCTION__, __LINE__, (isChanged == TRUE ? "TRUE" : "FALSE"));

    return isChanged;
}


CHsvDvbsFreesat_mBckgnd::FunctionNat32 CHsvDvbsFreesat_mBckgnd::mEventActionMatrix[EvMax][StMax] =
{
							/* StIdle							                   StStart                                                              StSIAcquireWait					              StServiceInstallWait			                     StServiceInstallComplete                                  StSorting                                                      */
/* EvStart */					{FNADDR(FuncStartBackgroundInstallation),  NULL,						            NULL,							        NULL, 						            NULL,							        NULL							       },
/* EvStop */					{NULL, 							           FNADDR(FuncStopBackgroundInstallation),	FNADDR(FuncStopBackgroundInstallation),	FNADDR(FuncStopBackgroundInstallation),	FNADDR(FuncStopBackgroundInstallation), NULL                                   },
/* EvStartCollection */		    {NULL,							           FNADDR(FuncStartCollection),	            NULL,							        NULL,							        NULL,							        NULL							       },
/* EvDataAvailable */			{NULL,							           NULL,						            FNADDR(FuncDataAvailable),		        NULL,							        NULL,							        NULL							       },
/* EvDataNotAvailable */		{NULL,							           NULL,						            FNADDR(FuncDataNotAvailable),	        NULL,							        NULL,							        NULL							       },
/* EvInstallComplete */		{NULL,							           NULL,						            NULL,							        NULL,							        FNADDR(FuncInstallComplete),		    NULL                                   },
/* EvSorting */		        {NULL,							           NULL,						            NULL,							        NULL,							        NULL,		                            FNADDR(FuncSorting)		               },
/* EvSortComplete */		    {NULL,							           NULL,						            NULL,							        NULL,							        NULL,		                            FNADDR(FuncSortComplete)		       }
};


/*****************************************************************************************
 * Private methods
 *****************************************************************************************/

void CHsvDvbsFreesat_mBckgnd::PumpHandler (int event, Nat32 param)
{
    if((event < EvMax) && (CURRENT_BCKGND_STATE < StMax))
	{
		if(mEventActionMatrix[event][mBckgndStatus.State] != NULL)
		{
			FPCALL(mEventActionMatrix[event][CURRENT_BCKGND_STATE])(param);
		}
	}
}

void CHsvDvbsFreesat_mBckgnd::FuncStartBackgroundInstallation (Nat32 param)
{
	SET_BCKGND_STATE (StStarted);

	if(ctrl->GetMode (HsvDmxMain) != IHsvSdmControl2_Idle)
	{
		// Always true for background installation
		ctrl->StopCollection(HsvDmxMain);
	}
}

void CHsvDvbsFreesat_mBckgnd::FuncStartCollection (Nat32 param)
{
    ctrl->StartCollection(HsvDmxMain, IHsvSdmControl2_FreesatNormal);
    SET_BCKGND_STATE (StSIAcquireWait);
}

void CHsvDvbsFreesat_mBckgnd::FuncDataAvailable (Nat32 param)
{
    // If BAT is avaialble start the service installation
	if(param & IHsvSdmControlNotifyEx_BAT)
	{
		SET_BCKGND_STATE(StServiceInstallWait);
		// In Freesat for acquisition there is no mode, so value is always passed as zero
		idataacq->AcquireData(0);
	}
}

void CHsvDvbsFreesat_mBckgnd::FuncDataNotAvailable(Nat32 param)
{
	// Data not acquired, send installation complete notification
	SET_BCKGND_STATE(StServiceInstallComplete);
	m_pfac.PmpSend (mBckgndPump, EvInstallComplete, (Nat32)FALSE);
}

void CHsvDvbsFreesat_mBckgnd::FuncInstallComplete (Nat32 param)
{
    // Start Sorting
	SET_BCKGND_STATE(StSorting);
	m_pfac.PmpSend (mBckgndPump, EvSorting, 0);
}


void CHsvDvbsFreesat_mBckgnd::FuncSorting (Nat32 param)
{
	int pkgIndex = 0;

	pkgIndex = isettings->GetAttribute (IHsvSatelliteSettings_AttributePackageId);

	TraceNotice (m, "Invoking Sort PackageId %d \n", pkgIndex);

	isort->Sort(pkgIndex);
}


void CHsvDvbsFreesat_mBckgnd::FuncSortComplete (Nat32 param)
{
    SET_BCKGND_STATE (StIdle);
	UNUSED (param);
}

#endif

#if 0
/* Overriden IHsvSatelliteInstallationNotify  methods  */

void CHsvDvbsFreesat_mBckgnd::OnEvent (int eventId, int value)
{
	TraceNotice (m, "%s %d eventid %d\n", __FUNCTION__, __LINE__, eventId);
    switch (eventId)
    {
	case IHsvSatelliteInstallationNotify_EventSortCompleted:
		m_pfac.PmpSend (mBckgndPump, EvSortComplete, (Nat32)NULL);
   
     break;

	default
:
		break
}

removed this from strapi on added and changed as we monitor only sdt other tunnelled pids
	 case HSVSPID(ActualTSService, dvb, sdt):
               if (TRUE == strapi->GetByKey(dest, spid, key1, key2, key3, &service))
                {
                    UpdateServiceTable (service);
                }
                break;
#endif
