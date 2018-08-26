#include    "_hsvdvbtins_mDataAcq.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbtins_mDataAcq")

#include    "hsvdvbtins_mDataAcq.h"
#include	"HtvDebug.h"












/*HsvDBookOperators.c*/
/* static functions */











/*HsvDvbGeneric.c*/



/*HsvRiksTvOperator.c*/
/* static functions */












st_LCNInfo CHsvDvbTInstallation_mDataAcq_Priv::s__mLCNInfo[MAX_NUMBER_SERVICES];


/*HsvDBookOperators.c*/
/* static variables */
HsvNetworkRegionsData CHsvDvbTInstallation_mDataAcq_Priv::s__mRegionsData;

int CHsvDvbTInstallation_mDataAcq_Priv::s__mUserPrimaryRegionIndex,CHsvDvbTInstallation_mDataAcq_Priv::s__mUserSecondaryRegionIndex,CHsvDvbTInstallation_mDataAcq_Priv::s__mUserTertiaryRegionIndex;





HsvTargetRegionCache * CHsvDvbTInstallation_mDataAcq_Priv::s__mTargetRegionCache = NULL;

int CHsvDvbTInstallation_mDataAcq_Priv::s__TargetRegionCachePoolId = -1;

Bool CHsvDvbTInstallation_mDataAcq_Priv::s__updateBarkerMuxDvbtins = FALSE;

/*HsvRiksTvOperator.c*/
/* static variables */
int CHsvDvbTInstallation_mDataAcq_Priv::s__mNetworkIndex = 0;




TypeNwIDCache CHsvDvbTInstallation_mDataAcq_Priv::s__NwIDCache[MAX_MUXES_PER_NTK];



void CHsvDvbTInstallation_mDataAcq_Priv::idatapow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE, "hsveuins_msvcacq" );
}

void CHsvDvbTInstallation_mDataAcq_Priv::idatapow_TurnOff(void)
{

}

void CHsvDvbTInstallation_mDataAcq_Priv::idatapow_TurnOn(void)
{
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_Initialise (void)
{
    DigInsStatus.Onwid              =   0xFFFF;
    DigInsStatus.Tsid               =   0xFFFF;
    DigInsStatus.NetworkId          =   0x0000; 
    DigInsStatus.TsVersionNumber    =   0;
    mRiksTvInitialise();
    mDbookInitialise();
	ChannelListDataCache.TotalNumberofChannelListId=0;
	memset((Address)&ChannelListDataCache, 0, sizeof(ChannelListDataCache));

    if(eurdiv_DeleteTSNotIntransmission()&&(CURRENT_MODE == UPDATE_MODE))
    {
        memset((Address)&mLCNInfo, 0xFF, sizeof(mLCNInfo));
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_InitialiseTotalChannels()
{
	mDigitalChannelsFound = 0;
}



int CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetNumberOfChannelListIds()

{
int retval =0;
retval=ChannelListDataCache.TotalNumberofChannelListId;
TraceDebug(m,"idataacq_GetNumberOfChannelListIds=[%d]",retval);

return retval;
}

int CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetChannelListIdByIndex(int index)
{
	TraceDebug(m,"idataacq_GetChannelListIdByIndex ::channelId[%d]=[%d]",index,ChannelListDataCache.CachedChannelList[index].ChannelId);	
	return ChannelListDataCache.CachedChannelList[index].ChannelId;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_SetFavouriteChannelListId(int mode,int attrib,int index)
{
	TraceDebug(m,"idataacq_SetFavouriteChannelListId=[%d]",ChannelListDataCache.CachedChannelList[index].ChannelId);
	for(int i=0;i<ChannelListDataCache.CachedChannelList[index].NoOfServiceInChannelList;i++)
{
		TraceDebug(m,"No of service present in selected channelList[%d]",ChannelListDataCache.CachedChannelList[index].NoOfServiceInChannelList);
		TraceDebug(m, "ServiceId=[%d]",ChannelListDataCache.CachedChannelList[index].ChannelID_services[i].ServiceId);
		TraceDebug(m, "LCN=[%d]",ChannelListDataCache.CachedChannelList[index].ChannelID_services[i].LCN);
}
	mAssignLCNforChannelList(index,NULL);
	idvbset_SetAttribute(mode,attrib,ChannelListDataCache.CachedChannelList[index].ChannelId);//store channellsit ID for update installation usecase

}

Nat32 CHsvDvbTInstallation_mDataAcq_Priv::mAdjustFrequency(Nat32 Frequency)
{
	int i, noOfRecs = pgdb_GetNoRecords(PTC_TABLE);
	int FreqDiff = 0;	
    HsvPgdatDigTSData   tsdata;
	Nat32 RetVal = Frequency;

	TraceDebug(m,"mAdjustFrequency [%d]",Frequency);
	
	for (i = 0; i < noOfRecs; i++)
	{
		pgdb_GetByIndex(PTC_TABLE,i,&tsdata);
		FreqDiff = (tsdata.Frequency > Frequency) ? (tsdata.Frequency - Frequency) : (Frequency - tsdata.Frequency);
		/*Check for Frequncy drift of 75 KHz*/
		if(FreqDiff < 75)
		{
			RetVal = tsdata.Frequency;
			break;
		}
	}
	
	TraceDebug(m,"AdjustedFrequency [%d]",RetVal);
	return RetVal;
	
}


void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_AcquireData (void)
{
    HsvInstallationPTC    ptc;
    Bool retval = mGetTSMetaData();

    TraceDebug(m, "%s %d", __FUNCTION__, __LINE__);
    /* if the TS found is valid then go ahead for installation of services in the TS */
    if (retval == TRUE )
    {
        idvbt_GetPTCInfo(&ptc);
		
		if(CURRENT_MODE == BACKGROUND_MODE )
		{
			ptc.Frequency = mAdjustFrequency(ptc.Frequency);
		}
		
        mDbookAcquireNetworkData();

        /* write to freqmaptable */
        mAddToFreqMapTable(ptc);

        mDeleteServicesOfSameMux(ptc.Frequency, ptc.StreamPriority);

		 if(CURRENT_MODE == BACKGROUND_MODE )
        {
      
			if(eurdiv_DeleteServiceOnFly())
				{
				TraceDebug(m,"mDeleteSDTActuallNotService Not called for sweden");
				}
			else{
					mDeleteSDTActuallNotService(&ptc);
				}
        }

        TraceDebug(m, "New TS  (%d, %d, %d)", DigInsStatus.Onwid, DigInsStatus.Tsid, (int)ptc.Frequency); 
        if( mInstallMux(&ptc) == TRUE )
        {
			/* Store Network Names only if atleast one service is installed from that MUX */
			mRiksTvAcquireData();			
            /* Add entry to TS Table */
            mAddToTSTable(ptc);
        }

        if(CURRENT_MODE == BACKGROUND_MODE )
        {
            mDeleteHDSimulcastSDServices();
        }

        if(eurdiv_DeleteTSNotIntransmission()&&(CURRENT_MODE == UPDATE_MODE ))
        {
            mCreateLCNList();
        }
		if(eurdiv_IsApmeaChannelListCountry()==TRUE)
		{
			//HSVSPTYPE(FavoriteChannelListLCNV2, dvb, nit) lcnv2;
			int NoofRecs = strapi_GetSize(HsvMain, HSVSPID(FavoriteChannelListLCNV2, dvb, nit));
			if(NoofRecs>0)
			{ 
				mAddToCachedChannelListID();
				TraceDebug(m, "ChannelListDataCache.TotalNumberofChannelListId=[%d]",ChannelListDataCache.TotalNumberofChannelListId);
			}	
	     	/*It can be possibe on first frequency v2 channelist present and next freq only v1 present
			Then instead of no of service in channlList we should rely on total No cahnnellist id for reseting it to 0xffff.*/
			else if(0==ChannelListDataCache.TotalNumberofChannelListId) 
			{
			idvbset_SetAttribute(AUTO_MODE,rins_AttributeFavoriteChannelId,0xFFFF);	
			TraceDebug(m,"No channelList Present Reset it to default Value in setting");
			}
		}
    }
    else
    {
        TraceDebug(m, "PTC Ignored: Invalid PTC or Incomplete Data");
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::mCreateLCNList(void)
{
    HsvDestination dest = HsvMain;
    int NoOfRecs =0, i=0;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) lcn2; 
    HSVSPTYPE(ActualNetworkHDSLCN, dvb, nit) nwhdslcn;  
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) nwlcn;
	
	memset((Address)&lcn2, 0, sizeof(HSVSPTYPE(ActualNetworkLCN2, dvb, nit)));

    NoOfRecs = strapi_GetSize(dest, HSVSPID(ActualNetworkLCN2, dvb, nit));

    for(i=0;i<NoOfRecs;i++)
    {   
        if(strapi_GetByIndex(dest, HSVSPID(ActualNetworkLCN2, dvb, nit),i,&lcn2))
        {
            InsertLCNList(lcn2.Original_NetworkId,lcn2.Tsid,lcn2.ServiceId);
        }
    }

    NoOfRecs = strapi_GetSize(dest, HSVSPID(ActualNetworkHDSLCN, dvb, nit));

    for(i=0;i<NoOfRecs;i++)
    {   
        if(strapi_GetByIndex(dest, HSVSPID(ActualNetworkHDSLCN, dvb, nit),i,&nwhdslcn))
        {
            InsertLCNList(nwhdslcn.Original_NetworkId,nwhdslcn.Tsid,nwhdslcn.ServiceId);
        }
    }

    NoOfRecs = strapi_GetSize(dest, HSVSPID(ActualNetworkLCN, dvb, nit));

    for(i=0;i<NoOfRecs;i++)
    {   
        if(strapi_GetByIndex(dest, HSVSPID(ActualNetworkLCN, dvb, nit),i,&nwlcn))
        {
            InsertLCNList(nwlcn.Original_NetworkId,nwlcn.Tsid,nwlcn.ServiceId);
        }
    }

}

void CHsvDvbTInstallation_mDataAcq_Priv::InsertLCNList(Nat16 Onid,Nat16 Tsid,Nat16 ServiceId)
{
    int i =0;
    
    for(i=0; (i<MAX_NUMBER_SERVICES) &&(mLCNInfo[i].ServiceId != 0xFFFF);i++)
    {
        if( (mLCNInfo[i].Onid== Onid) &&(mLCNInfo[i].ServiceId == ServiceId)&&(mLCNInfo[i].Tsid == Tsid) )
        {
            break;//already present
        }
    }

    if((i<MAX_NUMBER_SERVICES)&&(mLCNInfo[i].ServiceId == 0xFFFF) )
    {
        //notpresent, insert here
        mLCNInfo[i].Onid= Onid;
        mLCNInfo[i].ServiceId = ServiceId;
        mLCNInfo[i].Tsid = Tsid;

    }

}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_SyncTemporaryTableRecords(void)
{
    TraceDebug(m, "%s %d mPump %d", __FUNCTION__, __LINE__, mPump);
	if(AUTO_INSTALL)
	{
//#if (!HTV_ENABLE)
	if(sysset_GetPbsMode() == 0)
	{
		pgdb_ClearTable(PTC_TABLE);
		pgdb_ClearTable(SERVICE_TABLE);
		pgdb_ClearTable(PRESET_TABLE);
	}
//#endif		
	}
    pmp_PmpSend(mPump, evStep0, (Nat32)NULL);
}

int CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetNumberOfDigitalChannelsFound(void)
{
    int retval = 0;

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
        case MANUAL_MODE:
            retval = mDigitalChannelsFound;
            break;
        default:
            break;
    }
    return retval;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_ClearCache()
{
    mClearCache();
}   

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_AcquireSDTOtherData()
{
	return;
}


void CHsvDvbTInstallation_mDataAcq_Priv::mPumpHandler(int value, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m, "%s: CURRENT STEP = %d\r",__FUNCTION__, value);

    switch(value)
    {
        case evStep0:
            /* Step 1: Update the service records of the current pass to SERVICE TABLE */
            mUpdateServiceTableRecords(value);
            break;
        case evStep1:
            /* Step 2: Delete Services which are not in transmission anymore */
            mDeleteServiceNotInTransmission(value);
            break;
        case evStep2:
            /* NON HONOURED PRESETS */
            mUpdatePtcTableRecords(value);
            break;
        case evStepComplete:
            /* Notification to mdig */
            mDeleteHDSimulcastSDServices();
			if(AUTO_INSTALL)
			{
			if(ChannelListDataCache.TotalNumberofChannelListId==1)
				{
				mAssignLCNforChannelList(0,NULL);
				}
			}
            idvbt_SyncComplete();
            break;
    }

}
void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_UpdateBarkerMuxInfo(Nat16 onid, Nat16 tsid)
{
    HsvPgdatDigTSData   tmptsdata;
	int index, NoOfRecs = 0;
	NoOfRecs = pgdb_GetNoRecords(PTC_TABLE);
	for(index = 0; index < NoOfRecs; index++)
	{
    	if( pgdb_GetByIndex(PTC_TABLE, index, (Address )&tmptsdata)) 
    	{
			if((onid == tmptsdata.OriginalNetworkId) && (tsid == tmptsdata.Tsid))
			{
				tmptsdata.BarkerMux = TRUE;
				pgdb_Update(PTC_TABLE,&tmptsdata);
				break;
			}
		}
	}
} 
void CHsvDvbTInstallation_mDataAcq_Priv::mUpdateServiceTableRecords(int evCurrentStep)
{
    Bool ProceedUpdate = TRUE, PreviousServiceDeleted = FALSE;
    int indx = 0, noOfRecs = pgdb_GetNoRecords(TEMP_SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat, svcdat_temp;
    HsvPgdatDigTSData tsdat;
    HsvPgdatPresetData presetdat;

    svcdat.NewChannelMap = 1;
    /* Step 1: Update the service records of the current pass to SERVICE TABLE */
    for(indx = 0; indx < noOfRecs; indx++)
    {
        if( pgdb_GetByIndex(TEMP_SERVICE_TABLE, indx, (Address)&svcdat_temp) == TRUE )
        {
            ASSIGN_KEYS_OF_SVC(svcdat, svcdat_temp);
            ProceedUpdate = pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat);

			if(sysset_GetPbsMode() == 0)
			{
            //#if 0 //[HTV]duplicate channel information.
            if(ProceedUpdate == FALSE)
            {
				if (!(eurdiv_IsDbookCountry() && (AUTO_INSTALL)))
				{
					/* For UK auto installation, there is no need to delete the duplicate entries. 
						They will be taken care for deletion after the TRD selection */
					PreviousServiceDeleted = mDeleteDuplicateRecords(&svcdat_temp);
				}		
            }
            //#endif
			}
            
            if(ProceedUpdate)
            {
                tsdat.Frequency        =   svcdat.Frequency;
                tsdat.StreamPriority   =   svcdat.StreamPriority;
                if( pgdb_GetByKey( PTC_TABLE, (Address) &tsdat) == TRUE)
                {
                    TraceDebug(m, "%s %d", __FUNCTION__,  __LINE__);
					if( IS_NOT_USER_INSTALLED(tsdat) )
					{
						
						if(eurdiv_MultipleLCNSupported())
						{
							Nat8 k=0,j=0;
							Bool Present = FALSE;
							/*Remove the LCNS if not present in the New list*/

							for(k=0;k<MAX_LCNS;k++)
							{
								Present = FALSE;
								if(svcdat.MultipleLCN[k] != INVALID_LCN)
								{
									for(j=0;j<MAX_LCNS;j++)
									{	
										REVALIDATE(svcdat.MultipleLCN[k]);
										if(svcdat.MultipleLCN[k] == svcdat_temp.MultipleLCN[j])
										{
											Present = TRUE;
											break;				
										}
									}
									
									if( (Present == FALSE) && (svcdat.MultiplePreset[k] !=INVALID_PRESET) )
									{
									
										if(eurdiv_UpdateLCN(rins_GetMedium()))
										{
											/* below done, because the LCN changes presets are sorted freshly as per design of ItaSort */
											//PrintfNotice("%s %d deleted preset LCN %d svcdat.PresetNumber %d\n", __FUNCTION__, __LINE__, svcdat.MultipleLCN[k], svcdat.MultiplePreset[k]);
											presetdat.PresetNumber =   svcdat.MultiplePreset[k];
											presetdat.Type         =   HsvOnePart;
											if(pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat)==TRUE)
											{
												svcdat.MultipleFavorite[k]=presetdat.FavoriteNumber;
											}
											pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
											
											svcdat.MultiplePreset[k] = INVALID_PRESET;
											svcdat.MultipleLCN[k] = INVALID_LCN;
										}
										else
										{
											//PrintfNotice("LCN changed but could not be updated as due to user re-arranged presets\n");
										}
										
									}
								}
							}
							
							/*Add new LCNs in the svcdat LCN list*/
							for(k=0;k<MAX_LCNS;k++)
							{
								Present = FALSE;
								if(svcdat_temp.MultipleLCN[k] != INVALID_LCN)						
								{
									for(j=0;j<MAX_LCNS;j++)
									{	
										
										if(svcdat_temp.MultipleLCN[k] == svcdat.MultipleLCN[j])
										{
											//found	
											Present = TRUE;;
										}
									}
									
									if(Present == FALSE)
									{
										for(j=0;j<MAX_LCNS;j++)
										{
											if(svcdat.MultipleLCN[j] == INVALID_LCN)
											{
												svcdat.MultipleLCN[j] = svcdat_temp.MultipleLCN[k];
												svcdat.MultiplePreset[j] = INVALID_PRESET;
												break;
											}
										}
										//add
										//PrintfNotice("Add svcdat_temp.MultipleLCN[%d] = %d\n",k,svcdat_temp.MultipleLCN[k]);										
									}
								}
							}			
							
						}
						else
						{
							
							REVALIDATE(svcdat.LCN); //this is required because we would have invalidated LCN in previous pass due to conflicts if any
							if( (VALID_LCN_RANGE(svcdat.LCN) || VALID_LCN_RANGE(svcdat_temp.LCN)) &&
								(svcdat.LCN != svcdat_temp.LCN) )
                        {
                            if(eurdiv_UpdateLCN(rins_GetMedium()))
                            {
                                /* below done, because the LCN changes presets are sorted freshly as per design of ItaSort */
                                TraceNotice(m,"%s %d deleted preset becoz => psvcdat->LCN %d svcdat_temp.LCN %d svcdat.PresetNumber %d", __FUNCTION__, __LINE__, svcdat.LCN, svcdat_temp.LCN, svcdat.PresetNumber);
                                presetdat.PresetNumber =   svcdat.PresetNumber;
                                presetdat.Type         =   HsvOnePart;
                                pgdb_Delete(PRESET_TABLE,(Address)&presetdat);

                                svcdat.PresetNumber = INVALID_PRESET;
                            }
                            else
                            {
                                TraceNotice(m,"svcdat.LCN %d svcdat_temp.LCN %d LCN changed but could not be updated as due to user re-arranged presets", svcdat.LCN, svcdat_temp.LCN);
							}
						}
						}
						mCopySvcBroadcastAttributes(&svcdat, svcdat_temp);
						pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
					}
                }
            }
            else
            {
                /* new record Add to SERVICE TABLE */
                TraceDebug(m, "%s %d <%d %d %d>", __FUNCTION__,  __LINE__, svcdat_temp.ServiceId, svcdat_temp.Frequency, svcdat_temp.PresetNumber);
                pgdb_Add(SERVICE_TABLE, (Address)&svcdat_temp);
                /* below is required as we have to update preset table when any of the keys of service table
                   entry is changed */
                if(PreviousServiceDeleted)
                {
                    sort_UpdateDigitalPreset(&svcdat_temp);
                }
            }
        }
    }
    pmp_PmpSend(mPump, (evCurrentStep + 1), (Nat32)NULL);
}

void CHsvDvbTInstallation_mDataAcq_Priv::mDeleteServiceNotInTransmission(int evCurrentStep)
{
    int indx = 0, j, noOfPtcRec, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat;
    HsvPgdatPresetData presetdat;
    HsvPgdatDigTSData tsdat;
    Bool lToBeDeleted = FALSE;
    HsvDestination dest = HsvMain;
    int NoOfRecs =0,k =0, i = 0;               
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) lcn; 

    UNUSED(dest);
    UNUSED(k);
    UNUSED(NoOfRecs);
    UNUSED(lcn);

    for(indx = 0; indx < noOfRecs; indx++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, indx, (Address)&svcdat) == TRUE )
        {
            tsdat.Frequency        =   svcdat.Frequency;
            tsdat.StreamPriority   =   svcdat.StreamPriority;
            lToBeDeleted = pgdb_GetByKey( TEMP_PTC_TABLE, (Address) &tsdat);
            if( (lToBeDeleted == FALSE) && (svcdat.DecoderType == feapi_ChanDecDvbT2) ) // To delete services transmitted in the same frequency with different PLP id (streamPriority)
            {
                noOfPtcRec = pgdb_GetNoRecords(TEMP_PTC_TABLE);
                for(j = 0; j<noOfPtcRec; j++)
                {
                    if( pgdb_GetByIndex(TEMP_PTC_TABLE, j, (Address)&tsdat) == TRUE )
                    {
                        if((tsdat.Frequency ==   svcdat.Frequency) && (tsdat.DecoderType != feapi_ChanDecDvbC))
                        {
                            lToBeDeleted = TRUE;
                        }
                    }
                }
            }

            if(lToBeDeleted)
            {
                /* Dont remove UserInstalled presets */
                if( IS_NOT_USER_INSTALLED(tsdat) )
                {
                    /* delete record from SERVICE TABLE */
                    if( pgdb_GetByKey(TEMP_SERVICE_TABLE, (Address)&svcdat) == FALSE )
                    {
                        /* This means MUX is present but the service is removed from that MUX by broadcaster */
                        if(eurdiv_MultipleLCNSupported())
						{
							for(i=0;i<MAX_LCNS;i++)
							{
								if(svcdat.MultiplePreset[i] !=INVALID_PRESET )
								{
									presetdat.PresetNumber =   svcdat.MultiplePreset[i];
									presetdat.Type         =   HsvOnePart;
									pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
								}

							}

						}
						else
						{
							presetdat.PresetNumber =   svcdat.PresetNumber;
							presetdat.Type         =   HsvOnePart;
							pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
						}
                        
                        
                        pgdb_Delete(SERVICE_TABLE,(Address) &svcdat);
                        sortN_OnEvent(sortN_EventChannelRemoved, rins_GetInstallationMode());

                        TraceDebug(m, " @ %d Ntf EventChannelRemoved sent for Preset %d, ServiceId:%d ", __LINE__, svcdat.PresetNumber, svcdat.ServiceId);
                        indx--;
                        noOfRecs--;
                    }
                }
            }
			/* Dont delete services of there is no RF Lock seen. AN-77777. Confirmed by Paul */
            else if(eurdiv_DeleteTSNotIntransmission() && UPDATE_INSTALL && (0 != pgdb_GetNoRecords(TEMP_SERVICE_TABLE)))
            {               

                
                for(k=0;(k<MAX_NUMBER_SERVICES) &&(mLCNInfo[k].ServiceId != 0xFFFF);k++)
                {
                
                    if((mLCNInfo[k].Onid== svcdat.OriginalNetworkId) && (mLCNInfo[k].Tsid == svcdat.Tsid)&& (mLCNInfo[k].ServiceId==svcdat.ServiceId))
                    {

                        break;
                    }
                    
                }

                //if not present in LCN list, delete the service

                if((k >= MAX_NUMBER_SERVICES )||(mLCNInfo[k].ServiceId == 0xFFFF))
                {
					if(eurdiv_MultipleLCNSupported())
					{
						for(i=0;i<MAX_LCNS;i++)
						{
							if(svcdat.MultiplePreset[i] !=INVALID_PRESET )
							{
								presetdat.PresetNumber =   svcdat.MultiplePreset[i];
								presetdat.Type         =   HsvOnePart;
								pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
							}
						}
					}
					else
					{
						presetdat.PresetNumber =   svcdat.PresetNumber;
						presetdat.Type         =   HsvOnePart;
						pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
					}
                    pgdb_Delete(SERVICE_TABLE,(Address) &svcdat);
                    sortN_OnEvent(sortN_EventChannelRemoved, rins_GetInstallationMode());
                    TraceNotice(m, " @ %d Ntf EventChannelRemoved sent for Preset %d, ServiceId:%d ", __LINE__, svcdat.PresetNumber, svcdat.ServiceId);
                    indx--;
                    noOfRecs--;
                }
                
            }
        }
    }

    pmp_PmpSend(mPump, (evCurrentStep + 1), (Nat32)NULL);
}

void CHsvDvbTInstallation_mDataAcq_Priv::mUpdatePtcTableRecords(int evCurrentStep)
{
    int indx = 0, noOfRecs = pgdb_GetNoRecords(TEMP_PTC_TABLE);
    HsvPgdatDigTSData tsdata;
    HsvPgdatDigTSData tsdata_temp;

    /* Step 1: Update the PTC records of the current pass to PTC TABLE */
    for(indx = 0; indx < noOfRecs; indx++)
    {
        if( pgdb_GetByIndex(TEMP_PTC_TABLE, indx, (Address)&tsdata_temp) == TRUE )
        {
            tsdata.Frequency        =   tsdata_temp.Frequency;
            tsdata.StreamPriority   =   tsdata_temp.StreamPriority;
            if( pgdb_GetByKey(PTC_TABLE, (Address)&tsdata) == TRUE )
            {
                if( IS_NOT_USER_INSTALLED(tsdata) )
                {
                    mCopyPtcBroadcastAttributes(&tsdata, tsdata_temp);
                    pgdb_Update(PTC_TABLE, (Address)&tsdata);
                }
            }
            else
            {
                /* new record Add to PTC TABLE */
                pgdb_Add(PTC_TABLE, (Address)&tsdata_temp);
            }
        }
    }

    pmp_PmpSend(mPump, (evCurrentStep + 1), (Nat32)NULL);
}

Bool CHsvDvbTInstallation_mDataAcq_Priv::mInstallCellIdService(HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) service,int *InstalledServices)
{

	HSVSPTYPE(SvcAvailabilty, dvb, sdt) Cell_id,Cell_id_temp;
	int TotalCellIdforeachservice   = 0;	
	int index 						= 0;
	int TPSId 						= INVALID_TPS_ID;
	Nat16 currentTpsId = 0;
	Nat32 errorcode 				= TM_OK;		
    HsvDestination dest 			= HsvMain;
    Bool retval                     = FALSE;
	Cell_id_temp.Original_NetworkId = service.Original_NetworkId;
	Cell_id_temp.Tsid 				= service.TsId;	
	Cell_id_temp.ServiceId			= service.ServiceId;
	memset((Address)&Cell_id, 0, sizeof(HSVSPTYPE(SvcAvailabilty, dvb, sdt)));
	
	feapi_GetTPSId(WINDOWID,(HsvDvbTParams* )(&TPSId),&errorcode);/*PLF api for TPS*/
	currentTpsId = (Nat16)TPSId;	
	if(TRUE == strapi_GetByKey(dest,HSVSPID(SvcAvailabilty, dvb, sdt),(int)Cell_id_temp.Original_NetworkId,(int)Cell_id_temp.Tsid,(int)Cell_id_temp.ServiceId,(void *)(&Cell_id)))
	{
		if(TRUE == Cell_id.Availability_flag)
		{
			if(Cell_id.ServiceId == service.ServiceId)	
			{		
				TotalCellIdforeachservice = Cell_id.NumGlobalCellIDs;
				TraceNotice(m,"NumberOfCellId=[%d]",TotalCellIdforeachservice);

				for( index = TotalCellIdforeachservice-1 ;index >=0 ; index--)
				{			
					TraceDebug(m,"Frontend TPS =[%d]",currentTpsId);
					TraceDebug(m,"CellId[%d] =[%d]", index, Cell_id.GlobalCellID[index]);
					
					if(Cell_id.GlobalCellID[index] == currentTpsId)
					{
					    TraceDebug(m, "Cell_Id matches Go for installation of this service");
						if( mCheckServiceForInstall (ptc, &service) == TRUE )
						{
							*InstalledServices+=1;
							retval = TRUE;
							break;
						}
					}
					else
					{
						TraceDebug(m, "No Cell_Id matches Dont installation this service");
					}
				}		
			}
			else
			{
				TraceDebug(m, "ServiceID doesnt matches");
			}
		}
		else if ( FALSE == Cell_id.Availability_flag)
		{
	      	if(Cell_id.ServiceId == service.ServiceId)	
			{		
				bool tobeinstalled = TRUE;
				TotalCellIdforeachservice = Cell_id.NumGlobalCellIDs;
				TraceNotice(m,"%d NumberOfCellId=[%d]",__LINE__,TotalCellIdforeachservice);
				
				for(index = TotalCellIdforeachservice - 1; index >= 0; index--)
				{			
					TraceDebug(m,"%d Frontend TPS =[%d]",__LINE__,currentTpsId);
					TraceDebug(m,"%d CellId[%d] =[%d]",__LINE__,index,Cell_id.GlobalCellID[index]);

					if(Cell_id.GlobalCellID[index] == currentTpsId)
					{
						tobeinstalled = FALSE;
						TraceDebug(m,"Tobeinstalled=[%d]",tobeinstalled);
					}
					else
					{
						TraceDebug(m, "%d No Cell_id matches Dont installation this service",__LINE__);
					}
				}
				
				if(TRUE == tobeinstalled)
				{
					if(mCheckServiceForInstall(ptc, &service) == TRUE )
					{
						TraceDebug(m,"%s %d ",__FUNCTION__,__LINE__);
						*InstalledServices+=1;
						retval = TRUE;
					}
				}
				
			}
			else
			{
				TraceDebug(m, "ServiceID doesnt matches");
			}
		  	
		}
	}
	else if( TRUE == mCheckServiceForInstall (ptc, &service))  /*although country is NZ but 0x72 not present do fall back*/
	{
		*InstalledServices+=1;
		retval = TRUE;
	}	
	TraceDebug(m,"service =[%d] InstalledServices =[%d]",service.ServiceId,*InstalledServices);
	return retval;	
}

Bool CHsvDvbTInstallation_mDataAcq_Priv::mInstallMux ( HsvInstallationPTC *ptc )
{
    HsvDestination dest = HsvMain;
    HSVSPTYPE(ActualTSService, dvb, sdt) service;
    int index, TotalServices = 0, InstalledServices = 0;
    Bool retval = FALSE;
    TotalServices = strapi_GetSize (dest, HSVSPID(ActualTSService, dvb, sdt));
	memset((Address)&service, 0, sizeof(HSVSPTYPE(ActualTSService, dvb, sdt)));

	TraceDebug(m,"TotalServices=[%d]",TotalServices);
	int from,to=0;
	
    for(index = TotalServices - 1; index >= 0 ; index--)
    {
    	if(strapi_GetByIndex(dest, HSVSPID(ActualTSService, dvb, sdt), index, (void *)(&service)) == TRUE)
		{
			if(sysset_GetSystemCountry() == cids_CountryNewZealand)
			{
				if (mInstallCellIdService(ptc,service,&InstalledServices) == TRUE) {
					retval = TRUE;
				}
			}
			else if( mCheckServiceForInstall (ptc, &service) == TRUE )
			{
				InstalledServices++;
				retval = TRUE;
			}	
		}
	}
    TraceDebug(m, "Installed %d services", InstalledServices);
    return retval;
}

/**** Copy channel name to unicode ******/

void CHsvDvbTInstallation_mDataAcq_Priv::mCopyString(Nat16 *dest, Nat16 *src, int maxchars)
{
    int i = 0;
    for (i = 0 ; (i < maxchars) && (*src); i++)
    {
        *dest++ = *src++;
    }   
    *dest = 0;
}

Bool CHsvDvbTInstallation_mDataAcq_Priv::mGetTSMetaData(void)
{
    Bool retval = FALSE;
    Nat16 NetworkId = 0;
    HsvDestination dest = HsvMain;          

    retval = strapi_GetByKey(HsvMain, HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0, &DigInsStatus.Onwid) ;
    retval = retval && strapi_GetByKey(HsvMain, HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, &DigInsStatus.Tsid) ;
    retval = retval && strapi_GetByKey(HsvMain, HSVSPID(ActualTsVersionNo, dvb, sdt), 0, 0, 0, &DigInsStatus.TsVersionNumber) ;
	TraceNotice (m, "TSVersion number %d ", DigInsStatus.TsVersionNumber);

    /* Some streams might not contain an NIT. eg.Finnish. This should not prevent them
       from being installed. Hence dont base the return value on the strapi_GetByKey */
    DigInsStatus.NetworkId = 0;
    if(strapi_GetByKey(dest, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkId) )
    {
        DigInsStatus.NetworkId = NetworkId;
    }

    if( (retval == TRUE) && (eurdiv_InstallTestStreams(rins_GetInstallationMode(), rins_GetMedium()) == eurdiv_NotInstall) )
    {
        retval = IS_VALID_TS;
    }

    TraceDebug(m, "%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}

int CHsvDvbTInstallation_mDataAcq_Priv::mConvertToPgDataServiceType  (int servicetype)
{
    int retval = servicetype;
    switch(servicetype)
    {
        case TelevisionService:     
            retval  =   AppApiTelevisionService;
            break;
        case RadioService:
        case AdvCodecRadioService:    
            retval  =   AppApiRadioService;
            break;
        case TeletextService:         
            retval  =   AppApiTeletextService;
            break;
        case NVODTimeShiftedService:         
            retval  =   AppApiNVODTimeshiftedService;
            break;
        case NVODReferenceService:         
            retval  =   AppApiNVODReferenceService;
            break;
        case MosaicService:        
            retval  =   AppApiMosaicService;
            break;
        case DatabroadcastService:        
            retval  =   AppApiDatabroadcastService;
            break;
        case DVBMHPService:        
            retval  =   AppApiDVBMHPService;
            break;
        case MPEG2HDService:        
            retval  =   AppApiMPEG2HDService;
            break;
        case AdvCodecSDTelevisionService:        
            retval  =   AppApiAdvCodecSDTelevisionService;
            break;
        case AdvCodecSDNVODTimeShiftedService:        
            retval  =   AppApiAdvCodecSDNVODTimeShiftedService;
            break;
        case AdvCodecSDNVODReferenceService:        
            retval  =   AppApiAdvCodecSDNVODReferenceService;
            break;
        case AdvCodecHDTelevisionService:        
            retval  =   AppApiAdvCodecHDTelevisionService;
            break;
        case AdvCodecHDNVODTimeShiftedService:        
            retval  =   AppApiAdvCodecHDNVODTimeShiftedService;
            break;
        case AdvCodecHDNVODReferenceService:        
            retval  =   AppApiAdvCodecHDNVODReferenceService;
            break;
        case HD3DDigitalService:
            retval  =   AppApi3DHDDigitalService;
            break;
        default:
            break;
    }
    return retval;
}


void CHsvDvbTInstallation_mDataAcq_Priv::mUpdateService (HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{    
    int tableid = TEMP_SERVICE_TABLE;
    HsvPgdatDigServiceData tmpsvcdat;

    mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
    mAssignSvcNonBroadcastAttributes(psvcdat);
    
    mLCNOverRuling(psvcdat);

    if(BACKGROUND_INSTALL)
    {
        tableid = SERVICE_TABLE;
    }
    
    ASSIGN_KEYS_OF_SVC(tmpsvcdat, (*psvcdat));
    if(pgdb_GetByKey(tableid, (Address)&tmpsvcdat) == FALSE)
    {
		ASSIGN_KEYS_OF_SVC(tmpsvcdat, (*psvcdat));
		if((pgdb_GetByKey(SERVICE_TABLE, (Address)&tmpsvcdat) == FALSE) && (UPDATE_INSTALL) )
		{
			TraceNotice (m, "Added After Best Mux Selection");
			mDigitalChannelsFound++;
		}
			
        /* should have been deleted due to Best MUX Algo, or primary keys changed during background install so add again.to service table */
        pgdb_Add(tableid, (Address)psvcdat);
        TraceDebug(m, "Added Service LCN:%d ONID:%d SVCID:%d",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
    }
    else
    {
        pgdb_Update(tableid, (Address)psvcdat);
        TraceDebug(m, "Updated Service LCN:%d ONID:%d SVCID:%d",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
    }



    if(BACKGROUND_INSTALL)
    {
        sort_UpdateDigitalPreset(psvcdat);
    }
}

/******** retval = FALSE: indicates retaining a multiplex - equivalent to selecting channel 1 *********/
/******** retval = TRUE : indicates replacing a multiplex - equivalent to selecting channel 2 *********/

Bool CHsvDvbTInstallation_mDataAcq_Priv::mCompareMultiplex(HsvPgdatDigTSData tsdata, HsvInstallationPTC *ptc )
{
    Bool retval     =   TRUE;    

    /* If the Two TSs are from the same Hierarchical Mux */
    if((tsdata.Frequency == ptc->Frequency) && (tsdata.StreamPriority != ptc->StreamPriority))
    {
        retval = TRUE;
        if((tsdata.QSignalStrength > 40) && (ptc->QSignalStrength > 40))
        {
            /* Low Priority Stream is Selected */
            retval = FALSE;
        }
    }      
    else 
    {
        if(tsdata.QSignalStrength == ptc->QSignalStrength)
        {
            retval = (ptc->VSignalStrength > tsdata.VSignalStrength)? TRUE: FALSE;
        }
        else
        {       
            if(tsdata.QSignalStrength > ptc->QSignalStrength)
            {
                if ( tsdata.VSignalStrength < ptc->VSignalStrength )
                {
                    if((tsdata.QSignalStrength - ptc->QSignalStrength) < DELTASQI )
                    {
                        retval = ((ptc->VSignalStrength - tsdata.VSignalStrength ) > DELTASSI)? TRUE: FALSE;
                    }
                    else
                    {
                        retval = FALSE;
                    }
                }
                else
                {
                    retval = FALSE; //select A
                }
            } 
            else if( tsdata.VSignalStrength > ptc->VSignalStrength )
            {
                if(( ptc->QSignalStrength - tsdata.QSignalStrength ) < DELTASQI ) 
                {
                    retval = ((tsdata.VSignalStrength - ptc->VSignalStrength) > DELTASSI )? FALSE: TRUE;
                }
                else
                {
                    retval = TRUE;
                }
            }
            else
            {
                retval = TRUE;
            }
        }
    } 
    return retval;
}


/******** retval = FALSE: indicates retaining a multiplex - equivalent to selecting channel 1 *********/
/******** retval = TRUE : indicates replacing a multiplex - equivalent to selecting channel 2 *********/

Bool CHsvDvbTInstallation_mDataAcq_Priv::mCompareTSSignal(HsvPgdatDigTSData tsdata, HsvPgdatDigTSData ts2data )
{
    Bool retval     =   TRUE;    

    /* If the Two TSs are from the same Hierarchical Mux */
    if((tsdata.Frequency == ts2data.Frequency) && (tsdata.StreamPriority != ts2data.StreamPriority))
    {
        retval = TRUE;
        if((tsdata.QSignalStrength > 40) && (ts2data.QSignalStrength > 40))
        {
            /* Low Priority Stream is Selected */
            retval = FALSE;
        }
    }      
    else 
    {
        if(tsdata.QSignalStrength == ts2data.QSignalStrength)
        {
            retval = (ts2data.VSignalStrength > tsdata.VSignalStrength)? TRUE: FALSE;
        }
        else
        {       
            if(tsdata.QSignalStrength > ts2data.QSignalStrength)
            {
                if ( tsdata.VSignalStrength < ts2data.VSignalStrength )
                {
                    if((tsdata.QSignalStrength - ts2data.QSignalStrength) < DELTASQI )
                    {
                        retval = ((ts2data.VSignalStrength - tsdata.VSignalStrength ) > DELTASSI)? TRUE: FALSE;
                    }
                    else
                    {
                        retval = FALSE;
                    }
                }
                else
                {
                    retval = FALSE; //select A
                }
            } 
            else if( tsdata.VSignalStrength > ts2data.VSignalStrength )
            {
                if(( ts2data.QSignalStrength - tsdata.QSignalStrength ) < DELTASQI ) 
                {
                    retval = ((tsdata.VSignalStrength - ts2data.VSignalStrength) > DELTASSI )? FALSE: TRUE;
                }
                else
                {
                    retval = TRUE;
                }
            }
            else
            {
                retval = TRUE;
            }
        }
    } 
    return retval;
}

int CHsvDvbTInstallation_mDataAcq_Priv::mGetPSTIndexFromCache (HsvPgdatDigServiceData *SvcDat)
{
	int	Count =0;

	for (Count = 0; Count < MAX_NUMBER_SERVICES; Count++)
	{
		if ((mTargetRegionCache[Count].OnId == SvcDat->OriginalNetworkId) && 
		    (mTargetRegionCache[Count].Tsid == SvcDat->Tsid) &&
			(mTargetRegionCache[Count].ServiceId == SvcDat->ServiceId) /*&&
			(mTargetRegionCache[Count].NetworkId == SvcDat->NetworkId)*/)		/* Not mandatorily check NID. Just in case NIT Missing service then it will cause issue */
			break;
	}
	
	//TraceNotice (m, "TempPrint: Matching Index found in cache %d ", Count);
	
	return Count;
	
}

int  CHsvDvbTInstallation_mDataAcq_Priv::mCheckAndComparePSTFromStrapiForUpdateInstall (HsvPgdatDigServiceData *SvcDat, int PSTIndexInCache)
{
	/* Returns TRUE when SAME PST found as earlier OR No PST found in both TS */
	int  RetVal = NO_TRD_MATCH;
	/* Get the current Mux PST Details */	
	Nat16 NetworkId = 0;
    HsvSDTTargetRegion SdtTargetRegion;
    HsvNITTargetRegion NitTargetRegion;
	int 	Count =0;
	int		FoundTrd = 0;	/* 0: Not Found, 1: Found from SDT, 2: From from NIT 2nd loop, 3: Found from NIT 1st loop */
	Nat16 PrimaryRegion   = idvbset_GetAttribute(AUTO_MODE, rins_AttributePrimaryRegion);
    Nat16 SecondaryRegion = idvbset_GetAttribute(AUTO_MODE, rins_AttributeSecondaryRegion);
    Nat32 TertiaryRegion  = idvbset_GetAttribute(AUTO_MODE, rins_AttributeTertiaryRegion);
	int 	mCheckCurrentMuxMatchingTrd = 0, mCheckEarlierMuxMatchingTrd = 0;

	if (IS_VALID_REGION(PrimaryRegion,SecondaryRegion,TertiaryRegion))
	{
		if(!strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkId))
		{
			NetworkId = 0;
		}
		if(strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, sdt), SvcDat->OriginalNetworkId, SvcDat->Tsid, SvcDat->ServiceId, &SdtTargetRegion))
		{
			FoundTrd = 1;
		}
		else
		{
			/* check if available in the 2nd loop of NIT */
			Bool retval = strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, nit), SvcDat->OriginalNetworkId, SvcDat->Tsid, NetworkId, &NitTargetRegion);
			FoundTrd = (retval == TRUE) ? 2 : ((strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, nit), 0xFFFF, 0xFFFF, NetworkId, &NitTargetRegion) == TRUE) ?  3 : 0) ; 
		}

		/* Check current MUX have matching TRD */
		if (FoundTrd == 1)
		{
			FIND_MATCHING_TRD(PrimaryRegion,SecondaryRegion,TertiaryRegion,SdtTargetRegion,Count,mCheckCurrentMuxMatchingTrd)
		}
		else if ((FoundTrd == 2) || (FoundTrd == 3))
		{
			FIND_MATCHING_TRD(PrimaryRegion,SecondaryRegion,TertiaryRegion,NitTargetRegion,Count,mCheckCurrentMuxMatchingTrd)
		}
		
		/* Check conflicting mux have matching TRD */
		if (PSTIndexInCache < MAX_NUMBER_SERVICES)
		{
			FIND_MATCHING_TRD(PrimaryRegion,SecondaryRegion,TertiaryRegion,(mTargetRegionCache[PSTIndexInCache]),Count,mCheckEarlierMuxMatchingTrd)
		}
		
		TraceNotice (m, "UK: UpdateInstall: P %d S %d T %d CurrentMatchinTrd %d EarlierMatchingTrd %d ", PrimaryRegion, SecondaryRegion, TertiaryRegion, mCheckCurrentMuxMatchingTrd,mCheckEarlierMuxMatchingTrd);
	}
	
	/* Now select the relevant region */
	if (mCheckCurrentMuxMatchingTrd > mCheckEarlierMuxMatchingTrd)
	{
		RetVal = SELECT_CURRENT_MUX;
	}
	else if (mCheckEarlierMuxMatchingTrd > mCheckCurrentMuxMatchingTrd)
	{
		RetVal = SELECT_OTHER_MUX;
	}
	
	//TraceNotice (m, "TempPrint. Return value of %s is %d ", __FUNCTION__, RetVal);
	return RetVal;
}			

Bool  CHsvDvbTInstallation_mDataAcq_Priv::mCheckAndComparePSTFromStrapiForAutoInstall (HsvPgdatDigServiceData *SvcDat, int PSTIndexInCache)
{
	/* Returns TRUE when SAME PST found as earlier OR No PST found in both TS */
	Bool RetVal = TRUE;
	/* Get the current Mux PST Details */	
	Nat16 NetworkId = 0;
    HsvSDTTargetRegion SdtTargetRegion;
    HsvNITTargetRegion NitTargetRegion;
	int 	Count =0;
	int		FoundTrd = 0;	/* 0: Not Found, 1: Found from SDT, 2: From from NIT 2nd loop, 3: Found from NIT 1st loop */
	
    if(!strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkId))
    {
        NetworkId = 0;
    }
    if(strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, sdt), SvcDat->OriginalNetworkId, SvcDat->Tsid, SvcDat->ServiceId, &SdtTargetRegion))
    {
		FoundTrd = 1;
    }
    else
    {
        /* check if available in the 2nd loop of NIT */
        Bool retval = strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, nit), SvcDat->OriginalNetworkId, SvcDat->Tsid, NetworkId, &NitTargetRegion);
        FoundTrd = (retval == TRUE) ? 2 : ((strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, nit), 0xFFFF, 0xFFFF, NetworkId, &NitTargetRegion) == TRUE) ?  3 : 0) ; 
    }

	/* Check if Previous service had TRD. If both current and previous service does not have TRD, then best mux can be done. */
	/* Check if at least one of them have TRD. If yes, we cannot take decision untill User Selection happens. Hence don't do Best Mux */
	/* Check if both of them have same TRD. If yes, Best mux can be done */

	if (PSTIndexInCache == MAX_NUMBER_SERVICES)
	{
		/* No valid TRD found for ealier mux */
		RetVal = (FoundTrd == 0) ? TRUE: FALSE;
		TraceNotice (m, "UK: Already installed mux don't have TRD. Current mux have FoundTrd %d  ", FoundTrd);
	}
	else
	{
		/* Valid TRD present from earlier mux */
		if (FoundTrd == 1)
		{
			
			/* Check if both TRD are same */
			for (Count = 0; Count < MAX_REGIONS_PER_SERVICE; Count++)
			{
				if (!(((SdtTargetRegion.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] == INVALID_REGION_DEPTH) && 
				(mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] == INVALID_REGION_DEPTH))   || 
				((SdtTargetRegion.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] != INVALID_REGION_DEPTH) && 
				(SdtTargetRegion.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] == mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX]) &&
                (SdtTargetRegion.RegionList.RegionMap [Count][MULT_PRIMARY_INDEX] == mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_PRIMARY_INDEX]) &&
                (SdtTargetRegion.RegionList.RegionMap [Count][MULT_SECONDARY_INDEX] == mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_SECONDARY_INDEX]) &&
                (SdtTargetRegion.RegionList.RegionMap [Count][MULT_TERTIARY_INDEX] == mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_TERTIARY_INDEX]))))
				{
					RetVal = FALSE;
					break;
				}
			}
			TraceNotice (m, "UK: Already installed Mux have TRD. Current Max have %s TRD in SDT ", (RetVal == TRUE)?"Same":"Different");
		}
		else if ((FoundTrd == 2) || (FoundTrd == 3))
		{
			for (Count = 0; Count < MAX_REGIONS_PER_SERVICE; Count++)
			{
				if (!(((NitTargetRegion.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] == INVALID_REGION_DEPTH) && 
				(mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] == INVALID_REGION_DEPTH))   || 
				((NitTargetRegion.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] != INVALID_REGION_DEPTH) && 
				(NitTargetRegion.RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX] == mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_REGION_DEPTH_INDEX]) &&
                (NitTargetRegion.RegionList.RegionMap [Count][MULT_PRIMARY_INDEX] == mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_PRIMARY_INDEX]) &&
                (NitTargetRegion.RegionList.RegionMap [Count][MULT_SECONDARY_INDEX] == mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_SECONDARY_INDEX]) &&
                (NitTargetRegion.RegionList.RegionMap [Count][MULT_TERTIARY_INDEX] == mTargetRegionCache[PSTIndexInCache].RegionList.RegionMap [Count][MULT_TERTIARY_INDEX]))))
				{
					RetVal = FALSE;
					break;
				}			
			}
			TraceNotice (m, "UK: Already installed Mux have TRD. Current Max have %s TRD in NIT ", (RetVal == TRUE)?"Same":"Different");
		}
		else
		{
			/* No TRD for current MUX, but present for previously installed Mux. Hence not same */
			RetVal = FALSE;
			TraceNotice (m, "UK: Already installed Mux have TRD. Current Mux dont have TRD");
		}
	}
		
	return RetVal;
}			


Bool CHsvDvbTInstallation_mDataAcq_Priv::mCheckServiceForInstall (HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
    Bool retval = FALSE, ChannelExists = FALSE, Update = TRUE, ProceedToBestMux = TRUE, SameOrNoPST = TRUE;
    HsvPgdatDigTSData tsdata, tmptsdata;
	int 	ConflictService1PSTIndex = 0, UpdateInstallRetval =0;
	Bool 	Mux1MatchingPST = FALSE, Mux2MatchingPST = FALSE;

    if( mIsServiceInstallable(ptc, service)/*eurdiv_IsServiceInstallable( rins_GetMedium(), service->ServiceType )*/)
    {   
        HsvPgdatDigServiceData svcdat;
        HsvPgdatDigServiceData svcdat_temp;
        svcdat.NewChannelMap = 1;
        int from = -1, to = -1, indx = 0;


        pgdb_Initialise(pgdbconst_DigitalService, (Address)&svcdat);   
		

		for(int i = 0; i<MAX_LCNS;i++)
		{
			svcdat.MultipleLCN[i] = 0xC000;
			svcdat.MultiplePreset[i] = 0xFFFF;
		}

        svcdat.OriginalNetworkId     =   DigInsStatus.Onwid;
        svcdat.ServiceId             =   service->ServiceId;
        svcdat.Frequency             =   ptc->Frequency;
        svcdat.StreamPriority        =   ptc->StreamPriority;
        svcdat.Tsid                  =   DigInsStatus.Tsid; 
        svcdat.DecoderType           =   ptc->DecoderType;

        /* 2 below is no of keys */
		TraceNotice(m, " background value %d" , BACKGROUND_INSTALL);
        if(pgdb_GetRange( ((BACKGROUND_INSTALL)? SERVICE_TABLE : TEMP_SERVICE_TABLE), 2,(Address)&svcdat, &from, &to))
        {
			TraceNotice (m, "GetRange returned From %d To %d  for ONID %d SID %d ", from, to, svcdat.OriginalNetworkId, svcdat.ServiceId);
            if((to >= 0) && (from >=0))
            {
                for (indx = from; indx <= to ; indx++)
                {
                    if(pgdb_GetByIndex( ((BACKGROUND_INSTALL )? SERVICE_TABLE : TEMP_SERVICE_TABLE), indx, (Address)&svcdat_temp ))
                    {
                        if(mDuplicateEntry(&svcdat,&svcdat_temp))
                        {
                            ChannelExists = TRUE;
                        }
                    }
                }
            }
        }       
        if(ChannelExists)
        {   
	        if(sysset_GetPbsMode() == 0) // [HTV]
	        {
            if(MANUAL_INSTALL)
            {
				TraceNotice (m, "Manual installation ");
                HsvPgdatDigServiceData tmpsvcdat;
                /* Forcefully update the new service */
                Update = TRUE;
                mDigitalChannelsFound++;
                ASSIGN_KEYS_OF_SVC(tmpsvcdat, svcdat);
                
                if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tmpsvcdat) == FALSE)
                {
                    pgdb_Delete(SERVICE_TABLE, (Address)&tmpsvcdat);
                }
            }
            else
            {
                if(BACKGROUND_INSTALL)
                {
					TraceNotice (m, "Background installation ");
                    /* As the keys(streampriority) is changed have to delete the previous entry and freshly add again */
                    if( (svcdat_temp.StreamPriority != ptc->StreamPriority) && (svcdat_temp.DecoderType == ptc->DecoderType) )
                    {
                        TraceNotice(m,"%s %d svcdat.StreamPriority %d ptc->StreamPriority %d %d %d", __FUNCTION__, __LINE__, svcdat_temp.StreamPriority, ptc->StreamPriority, svcdat.PresetNumber, svcdat_temp.PresetNumber);
                        mRetainNonBroadcastAttributes(&svcdat, svcdat_temp);
                        pgdb_Delete(SERVICE_TABLE, (Address)&svcdat_temp);
                        Update = TRUE;
                    }
                    else if((svcdat_temp.Frequency != ptc->Frequency) && (svcdat_temp.DecoderType == ptc->DecoderType))
                    {
                        /* keys are changed so, do not update, will be taken in update installation */
                        Update = FALSE;
                    }
                }
                else
                {
					/* UK CR: TF515PHIALLMTK02-6 */
					if (eurdiv_IsDbookCountry())
					{
						/* Handle the TRD selection for UK */
						ProceedToBestMux = FALSE;
						if (AUTO_INSTALL)
						{
							/* ANEESH: TODO: Check below conditions will work when there is more than 2 same Duplets */
							/* Check if Previous service had TRD. If both current and previous service does not have TRD, then best mux can be done. */
							/* Check if at least one of them have TRD. If yes, we cannot take decision untill User Selection happens. Hence don't do Best Mux */
							/* Check if both of them have same TRD. If yes, Best mux can be done */
							ConflictService1PSTIndex = mGetPSTIndexFromCache (&svcdat_temp);
							SameOrNoPST = mCheckAndComparePSTFromStrapiForAutoInstall (&svcdat, ConflictService1PSTIndex);			
							ProceedToBestMux = (SameOrNoPST) ? TRUE : FALSE;
							TraceNotice(m, "UK: Going to do %s for ONID %d SID %d ", ((ProceedToBestMux == TRUE)? "BestMux":"TempStore "), svcdat.OriginalNetworkId, svcdat.ServiceId);
							
						}
						else if (UPDATE_INSTALL)
						{
							/* Check if any one of them belong to last selected TRD. If not directly proceed with Best Mux */
							ConflictService1PSTIndex = mGetPSTIndexFromCache (&svcdat_temp);
							UpdateInstallRetval = mCheckAndComparePSTFromStrapiForUpdateInstall (&svcdat, ConflictService1PSTIndex);
							
							ProceedToBestMux = (UpdateInstallRetval == NO_TRD_MATCH) ? TRUE : FALSE;							
							TraceNotice (m, "UK: Going to Select %s for ONID %d , SID %d ", ((UpdateInstallRetval == NO_TRD_MATCH) ? "BestMux": ((UpdateInstallRetval == SELECT_CURRENT_MUX) ? "CurMux" :"OthMux")), svcdat.OriginalNetworkId, svcdat.ServiceId);
						}
					}
					if (ProceedToBestMux)
					{
						/* For Update & Auto install pick the best service using best MUX algo. */
						tsdata.Frequency        = svcdat_temp.Frequency;
						tsdata.StreamPriority   = svcdat_temp.StreamPriority;
						if( pgdb_GetByKey(TEMP_PTC_TABLE, (Address )&tsdata) == TRUE )
						{
							Bool Proceed = FALSE;
							
							if(!mCompareMultiplex(tsdata, ptc))
							{
								tmptsdata.Frequency        = ptc->Frequency;
								tmptsdata.StreamPriority   = ptc->StreamPriority;
								if(pgdb_GetByKey(PTC_TABLE, (Address )&tmptsdata) == TRUE)
								{
									if(!IS_NOT_USER_INSTALLED(tmptsdata))
									{
										Proceed = TRUE;
									}
								}
							}
							else
							{
								if(IS_NOT_USER_INSTALLED(tsdata))
								{
									Proceed = TRUE;
								}
							}
							
							if(Proceed)
							{
								if (UPDATE_INSTALL) {
									mDigitalChannelsFound--;
									TraceNotice (m, "Deletion of Service Due to Best Mux algorithm");
								}
								/* As the keys(frequency) is changed have to delete the previous entry and freshly add again */
								pgdb_Delete(TEMP_SERVICE_TABLE, (Address)&svcdat_temp);
								Update = TRUE;
							}
							else
							{
								Update = FALSE;
							}
						}
					}
					else
					{
						if (eurdiv_IsDbookCountry())
						{
							if (AUTO_INSTALL)
							{
								/* Current Mux needs to be added */
								mAddNewService(&svcdat,ptc,service);
								Update = FALSE;
								retval = TRUE;
							}
							else if (UPDATE_INSTALL)
							{
								if (UpdateInstallRetval == SELECT_CURRENT_MUX)
								{
									/* Delete earlier mux */
									pgdb_Delete(TEMP_SERVICE_TABLE, (Address)&svcdat_temp);
									Update = TRUE;
									TraceNotice (m, "UK: Deleting already installed Service ");
								}
								else if (UpdateInstallRetval == SELECT_OTHER_MUX)
								{
									/* Earlier conflicted service is of higher priority. So dont add current service at all */
									Update = FALSE;
									TraceNotice(m, "UK: Already installed service is higher priority. Ignoring current Service ");
								}
							}
						}
					}
                }
            }           
            if(Update == TRUE)
            {
				TraceNotice (m, "Update True Checking for BackGroundInstall %d ", BACKGROUND_INSTALL);
                if(BACKGROUND_INSTALL)
                {
                    tsdata.Frequency = ptc->Frequency;
                    tsdata.StreamPriority = ptc->StreamPriority;
					TraceNotice (m, "GetByKey triggered for Freq %d Sp %d ", tsdata.Frequency, tsdata.StreamPriority);
                    pgdb_GetByKey( PTC_TABLE, (Address )&tsdata);
					TraceNotice (m, "TsDataVersion %d DigInsVersion %d ", tsdata.TSVersion , DigInsStatus.TsVersionNumber);
                    if(tsdata.TSVersion == DigInsStatus.TsVersionNumber) 
                    {
                        Update = FALSE;
                    }
                }

                if(Update == TRUE)
                {
					TraceNotice (m, "Going to update in DB.... ");
                    mUpdateService(&svcdat, ptc, service);
                    retval = TRUE;
                }
            }
			}
			else {
                mAddNewService(&svcdat,ptc,service);
                mDigitalChannelsFound--;
                retval = TRUE;
			}
        }
        else
        {
            mAddNewService(&svcdat,ptc,service);
            retval = TRUE;
        }           
    }
    return retval;
}

void CHsvDvbTInstallation_mDataAcq_Priv::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc,HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
    HsvPgdatDigServiceData svcdat;
	Nat8 k =0;
    
    mAssignSvcBroadcastAttributes(psvcdat, ptc, service);
    mAssignSvcNonBroadcastAttributes(psvcdat);
	
	if(eurdiv_MultipleLCNSupported())
	{
		for(k=0;k<MAX_LCNS;k++)	
		{
			psvcdat->MultiplePreset[k] = INVALID_PRESET;
		}
	}

    
    ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
    if( MANUAL_INSTALL || (pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == FALSE)|| (AUTO_INSTALL) )
    {
        mDigitalChannelsFound++;
    }
    pgdb_Add( ((BACKGROUND_INSTALL)? SERVICE_TABLE : TEMP_SERVICE_TABLE), (Address )psvcdat);
    TraceNotice(m,"Added Service LCN:%d ONID:%d SVCID:%d",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);

    if(BACKGROUND_INSTALL)
    {
        TraceDebug(m, "%s %d", __FUNCTION__, __LINE__);
        sort_AddDigitalPreset(psvcdat);
    }
}


Bool CHsvDvbTInstallation_mDataAcq_Priv::mDuplicateEntry(HsvPgdatDigServiceData *psvcdat1, HsvPgdatDigServiceData *psvcdat2)
{
    Bool retval = TRUE;
	TraceNotice (m, "Entering DuplicateEntry ");
    if(eurdiv_TripletKey( rins_GetMedium()))
    {
		TraceNotice (m, "Mux1 TSID %d Freq %d SP %d Mux2 TSID %d Freq %d SP %d ",psvcdat1->Tsid, psvcdat1->Frequency, psvcdat1->StreamPriority,  \
											psvcdat2->Tsid, psvcdat2->Frequency, psvcdat2->StreamPriority);
        if(
                ((psvcdat1->Tsid != psvcdat2->Tsid) && (psvcdat1->Frequency != psvcdat2->Frequency)) ||
                ((psvcdat1->Tsid != psvcdat2->Tsid) && (psvcdat1->Frequency == psvcdat2->Frequency) &&
                 (psvcdat1->StreamPriority != psvcdat2->StreamPriority)) 
          )
        {
            retval = FALSE;
        }
    }
    if(psvcdat1->DecoderType != psvcdat2->DecoderType)
    {
		TraceNotice (m, "Decoder type mismatch %d %d ",psvcdat1->DecoderType, psvcdat2->DecoderType);
        retval = FALSE;
    }
    return retval;
}

void CHsvDvbTInstallation_mDataAcq_Priv::mAddToFreqMapTable(HsvInstallationPTC ptc)
{
    HsvPgdatDigFreqMapData      freqdat;
    HsvPgdatDigFreqMapData      tmpfreqdat;

	pgdb_Initialise (pgdbconst_FrequencyMapTable, &freqdat);
    freqdat.OriginalNetworkId   = DigInsStatus.Onwid;
    freqdat.Tsid                = DigInsStatus.Tsid;
    freqdat.Frequency           = ptc.Frequency;
    freqdat.ModulationType      = ptc.ModulationType;
    freqdat.SymbolRate          = ptc.SymbolRate;
    freqdat.DecoderType         = ptc.DecoderType;
	freqdat.Bandwidth			= ptc.ChannelBandwidth;

    tmpfreqdat.OriginalNetworkId    = freqdat.OriginalNetworkId;
    tmpfreqdat.Tsid                 = freqdat.Tsid;

    if(pgdb_GetByKey(ANTENNA_FREQ, (Address )&tmpfreqdat))
    {
        pgdb_Update(ANTENNA_FREQ, (Address )&freqdat);
    }
    else
    {
        TraceDebug(m, "%s %d freqdat.Frequency %d", __FUNCTION__, __LINE__, (int)freqdat.Frequency);
        pgdb_Add( ANTENNA_FREQ, (Address )&freqdat);
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::mAddToTSTable(HsvInstallationPTC ptc)
{
    HsvPgdatDigTSData   tsdata, tmptsdata;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	HsvDestination dest = HsvMain;
	Nat8 retval = -1;
	memset((Address)&service, 0, sizeof(HSVSPTYPE(ActualTSService, dvb, sdt)));
    tsdata.Frequency            =   ptc.Frequency;                
    tsdata.ModulationType       =   ptc.ModulationType;               
    tsdata.HierarchyMode        =   ptc.HierarchyMode;
    tsdata.GuardInterval        =   ptc.GuardInterval;
    tsdata.TxMode               =   ptc.TxMode;
    tsdata.IqMode               =   ptc.IqMode;
    tsdata.Bandwidth     		=   ptc.ChannelBandwidth;
    tsdata.StreamPriority       =   ptc.StreamPriority;   
    tsdata.TimeError            =   ptc.TimeError;
    tsdata.FrequencyError       =   ptc.FrequencyError;
    tsdata.FrequencyOffset      =   ptc.FrequencyOffset;
    tsdata.VSignalStrength      =   ptc.VSignalStrength;
    tsdata.ASignalStrength      =   ptc.ASignalStrength;
    tsdata.QSignalStrength      =   ptc.QSignalStrength;
    tsdata.ChannelInformation   =   ptc.ChannelInformation; 
    tsdata.DecoderType          =   ptc.DecoderType;
    tsdata.SymbolRate           =   ptc.SymbolRate; 
    tsdata.OriginalNetworkId    =   DigInsStatus.Onwid;
    tsdata.Tsid                 =   DigInsStatus.Tsid;
    tsdata.NetworkId            =   DigInsStatus.NetworkId;
    tsdata.TSVersion            =   DigInsStatus.TsVersionNumber;
    tsdata.PtcListVersion       =   rins_GetInstallationVersion();
    tsdata.CodeRate             =   (ptc.StreamPriority == HsvStreamPriorityHigh) ? ptc.CodeRateHigh: ptc.CodeRateLow;
	tsdata.NITVersion			=	ptc.NITVersion;
	/* Introducing the SDT version for DVB-T also. This will be used for background updates */
	if(strapi_GetByIndex(dest, HSVSPID(ActualTSService, dvb, sdt), 0, (void *)(&service)) == TRUE)
	{
		tsdata.SDTVersion           = service.VersionNumber;
	}
	if(strapi_GetByKey(HsvMain, HSVSPID(ActualNITVer, dvb, nit), 0, 0, 0, (Address)(&retval)))
	{
	tsdata.NITVersion=retval;
	}
	tsdata.LanguageCode			=	sysset_GetSystemLanguage();
	
    tmptsdata.Frequency         =   tsdata.Frequency;
    tmptsdata.StreamPriority    =   tsdata.StreamPriority;
    if( pgdb_GetByKey((BACKGROUND_INSTALL)? PTC_TABLE: TEMP_PTC_TABLE, (Address )&tmptsdata) == FALSE ) 
    {
		tsdata.UserInstalled        =   (MANUAL_INSTALL)? TRUE: FALSE;
        if( pgdb_GetByKey( PTC_TABLE, (Address )&tmptsdata) ) 
        {
            tsdata.UserInstalled        =   (MANUAL_INSTALL)? TRUE: ( (UPDATE_INSTALL || BACKGROUND_INSTALL)? tmptsdata.UserInstalled  : FALSE );
        }
		tmptsdata.BarkerMux = updateBarkerMuxDvbtins;
        pgdb_Add( TEMP_PTC_TABLE, (Address )&tsdata);
    }
    else
    {
		TraceNotice (m, "Updating Version %d to PTC Table ", tsdata.TSVersion);
		tsdata.UserInstalled        =   ((MANUAL_INSTALL)? TRUE: ((UPDATE_INSTALL || BACKGROUND_INSTALL)? tmptsdata.UserInstalled : FALSE));
        pgdb_Update( (BACKGROUND_INSTALL)? PTC_TABLE: TEMP_PTC_TABLE, (Address )&tsdata);
    }
}

Bool CHsvDvbTInstallation_mDataAcq_Priv::mLCNParsingRequired(Nat16 OnwId)
{
    Bool retval = FALSE;
    UNUSED(OnwId);

    retval = eurdiv_ParseLCN(rins_GetMedium(), rins_GetInstallationMode()); 

    return retval;
}

Bool CHsvDvbTInstallation_mDataAcq_Priv::GetSvcNameWithCurrentLanguage(HsvPgdatDigServiceData *psvcdat, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	int from = 0, to = 0;
	Bool  retval = false;
	HsvSDTMultiLingSvcName MultiLingName;
	if(strapi_GetRangeByKey(HsvMain,HSVSPID(MultiLingSvcName, dvb, sdt),3,psvcdat->OriginalNetworkId,psvcdat->Tsid,psvcdat->ServiceId,&from,&to))
	{
		TraceDebug(m,"No. of MultiLing Descriptors present : %d", ((to - from) + 1));
		for(int i = from; i <= to; i++)
		{
			TraceNotice(m,"sysset_GetSystemLanguage() %d, MultiLingName.LangCode: %d",sysset_GetSystemLanguage(),MultiLingName.LangCode);
			if(strapi_GetByIndex(HsvMain,HSVSPID(MultiLingSvcName, dvb, sdt),i,(Address)&MultiLingName))
			{
				TraceNotice(m,"sysset_GetSystemLanguage() %d, MultiLingName.LangCode: %d",sysset_GetSystemLanguage(),MultiLingName.LangCode);
				if(sysset_GetSystemLanguage() == MultiLingName.LangCode)
				{
					//Copy Service Name
					mCopyString(service->ServiceName, MultiLingName.ServiceName, (eurdiv_ChannelNameLength - 1));
					retval = true;
					break;
				}
			}
		}		
		
	}

	return retval;

}



void CHsvDvbTInstallation_mDataAcq_Priv::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	Nat8 k =0;
    HsvChannel Channelinfo;
	HsvPgdatDigServiceData  svcdat;

    psvcdat->NewChannelMap         =   1;
    psvcdat->OriginalNetworkId     =   DigInsStatus.Onwid;
    psvcdat->ServiceId             =   service->ServiceId;
    psvcdat->NetworkId             =   DigInsStatus.NetworkId;
    psvcdat->Frequency             =   ptc->Frequency ; 
    psvcdat->DecoderType           =   ptc->DecoderType;
    psvcdat->ModulationType        =   ptc->ModulationType;
    psvcdat->Bandwidth      =   ptc->ChannelBandwidth;
    psvcdat->StreamPriority        =   ptc->StreamPriority; 
    psvcdat->LCN                   =   INVALID_LCN;
    psvcdat->LowPrioLCN            =   INVALID_LCN;
    psvcdat->OUI                   =   0;
    psvcdat->ServiceType           =   mConvertToPgDataServiceType(service->ServiceType);
    psvcdat->Type                  =   GETSERVICETYPE(service->ServiceType);
    psvcdat->FreeCiMode            =   service->Free_Ci_Mode;
    psvcdat->MatchBrandFlag        =   service->Match_Brand_Flag;
    psvcdat->NumBrandIds           =   service->NumBrandIds;

	if(eurdiv_MultipleLCNSupported())
	{
		for(k=0;k<MAX_LCNS;k++)	
		{
			psvcdat->MultipleLCN[k] = INVALID_LCN;
		}
	}
    if(service->Free_CA_Mode == TRUE)
    {
        psvcdat->SrcambledStatus = 1;
		psvcdat->ScramblingStatus =   1;
    }

    mAssignSvcHDSimulcastLinkageParams(psvcdat);

	ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));        
	if ( (!BACKGROUND_INSTALL) || (pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == FALSE) )
	{
		mAssignLCN(psvcdat);
	}

    if(eurdiv_IsServiceSortable(rins_GetMedium(), mConvertToDVBServiceType(psvcdat->ServiceType)) == FALSE)
    {
    	INVALIDATE(psvcdat->LCN);
	    TraceNotice(m,"%s: %d: Invalidated LCN: %d",__FUNCTION__,__LINE__,psvcdat->LCN);
    }

	
    if( (eurdiv_IsServiceHidden(rins_GetMedium(),mConvertToDVBServiceType(psvcdat->ServiceType)))
            || (eurdiv_InstallTestStreams(rins_GetInstallationMode(),rins_GetMedium()) == eurdiv_Hide) )
    {
        psvcdat->SystemHidden = TRUE;
		psvcdat->VisibleService=FALSE;
    }
    else                
    {
        //if hdlcn is present then hd visible flag will gets the priority of t2 contries 

        if((eurdiv_IsDbookCountry() == TRUE)&&(psvcdat->LowPrioLCN != INVALID_LCN))
        {
            psvcdat->SystemHidden = !(psvcdat->LowPrioVisibleService);
        }
        else
        {
            psvcdat->SystemHidden = !(psvcdat->VisibleService);
        }
    }
    mCopyString( psvcdat->BrandIds, service->Brand_Ids, service->NumBrandIds );
	if(eurdiv_MultiLingSupported() && GetSvcNameWithCurrentLanguage(psvcdat,service))
	{
		TraceDebug(m,"Service Name with LangCode: %d is available",sysset_GetSystemLanguage());
	}
	else
	{
		//TraceDebug(m,"MultiLingual Descriptor is not supported / present");
	}
    if(service->ServiceName[0] == 0)
    {
        mCopyString( psvcdat->ChannelName, instutil_AsciiToUnicode("-----", 10), 10);
    }
    else
    {
		
        ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
        TraceNotice (m, "Running Query on SERVICE TABLE for OnId %d  Sid %d Freq %d StPrio %d ", svcdat.OriginalNetworkId, svcdat.ServiceId, svcdat.Frequency, svcdat.StreamPriority);
        if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
        {
            if(svcdat.UserModifiedName == FALSE)
            {
				if(BACKGROUND_INSTALL)
				{
					/* For Channellib notifications to be generated */
					Channelinfo.Ptc = svcdat.PresetNumber; 
					Channelinfo.Channel.OnePart = svcdat.PresetNumber;                  
					Channelinfo.Type = GETSERVICETYPE(svcdat.ServiceType);
					
					TraceDebug(m,"Update NAME = %d", svcdat.UserModifiedName);

					/*Meaning user has not updated the name. So its ok we can update now. */
					if (mCompareUnicodeString(psvcdat->ChannelName, service->ServiceName) == FALSE)
					{
						pgdat_StoreChannelDataString (Channelinfo, pgdat_StringExtChannelName,  service->ServiceName, eurdiv_ChannelNameLength);
					}
					TraceDebug(m,"Channel Name Update for preset %d done Background Mode",svcdat.PresetNumber);
				}
				mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_ChannelNameLength - 1));
            }
            else
            {
                mCopyString( psvcdat->ChannelName, svcdat.ChannelName, (eurdiv_ChannelNameLength - 1));

            }
        }
        else
        {
            mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_ChannelNameLength - 1));
        }
    }
	if(BACKGROUND_INSTALL)
	{
		ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
        
        if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
		{
			/* if in background install do not update new LCN descriptor values as they have not sorted based upon LCN change here */
			psvcdat->LCN = svcdat.LCN;
			psvcdat->LowPrioLCN = svcdat.LowPrioLCN;
			psvcdat->VisibleService = svcdat.VisibleService;
			psvcdat->LowPrioVisibleService = svcdat.LowPrioVisibleService;
			
			if(eurdiv_MultipleLCNSupported())
			{
				for(k=0;k<MAX_LCNS;k++) 
				{
					psvcdat->MultipleLCN[k] = svcdat.MultipleLCN[k];
				}
			}

												

			/* For Channellib notifications to be generated */
			Channelinfo.Ptc = svcdat.PresetNumber; 
			Channelinfo.Channel.OnePart = svcdat.PresetNumber;                  
			Channelinfo.Type = GETSERVICETYPE(svcdat.ServiceType);
	    
		    if (psvcdat->SrcambledStatus != svcdat.SrcambledStatus)
		    {
				//PrintfNotice("%s: :;::: SCramble status change ", __FUNCTION__);
		        pgdat_StoreChannelDataInt (Channelinfo, pgdat_IntSrcambledStatus, (Bool)psvcdat->SrcambledStatus);
		    }
			if (psvcdat->ScramblingStatus != svcdat.ScramblingStatus)
		    {
		        pgdat_StoreChannelDataInt (Channelinfo, pgdat_IntSrcambledStatus, (Bool)psvcdat->ScramblingStatus);
		    }
		}
    }
    mDbookAcquireServiceData(psvcdat);
}

void CHsvDvbTInstallation_mDataAcq_Priv::mCopySvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat_temp)
{
    /* No need to copy Primary keys again, copy rest of them */
    psvcdat->NetworkId             =    svcdat_temp.NetworkId;
    psvcdat->ModulationType        =    svcdat_temp.ModulationType;
    psvcdat->Bandwidth			   =    svcdat_temp.Bandwidth;
    psvcdat->Tsid                  =    svcdat_temp.Tsid;
    psvcdat->LCN                   =    svcdat_temp.LCN;
    psvcdat->LowPrioLCN            =    svcdat_temp.LowPrioLCN;
    psvcdat->LowPrioVisibleService =    svcdat_temp.LowPrioVisibleService;
    psvcdat->VisibleService        =    svcdat_temp.VisibleService;
    psvcdat->NumericSelect         =    svcdat_temp.NumericSelect;
    psvcdat->ServiceType           =    svcdat_temp.ServiceType;
    psvcdat->Type                  =    svcdat_temp.Type;
    psvcdat->FreeCiMode            =    svcdat_temp.FreeCiMode;
    psvcdat->MatchBrandFlag        =    svcdat_temp.MatchBrandFlag;
    psvcdat->NumBrandIds           =    svcdat_temp.NumBrandIds;
    psvcdat->SystemHidden          =    svcdat_temp.SystemHidden;
    psvcdat->NewPreset             =    svcdat_temp.NewPreset;
    psvcdat->ServiceListVersion    =    svcdat_temp.ServiceListVersion;
    psvcdat->HDSimulcastRepOnId    =    svcdat_temp.HDSimulcastRepOnId;
    psvcdat->HDSimulcastRepTsId    =    svcdat_temp.HDSimulcastRepTsId;
    psvcdat->HDSimulcastRepSvcId   =    svcdat_temp.HDSimulcastRepSvcId;
    psvcdat->VideoPid              =    svcdat_temp.VideoPid;               
    psvcdat->AudioPid              =    svcdat_temp.AudioPid;
    psvcdat->PcrPid                =    svcdat_temp.PcrPid; 
    psvcdat->VideoStreamType       =    svcdat_temp.VideoStreamType;
    psvcdat->AudioStreamType       =    svcdat_temp.AudioStreamType;
    psvcdat->SecAudioStreamType    =    svcdat_temp.SecAudioStreamType;
    psvcdat->SecAudioPid           =    svcdat_temp.SecAudioPid;
	psvcdat->SrcambledStatus	   =	svcdat_temp.SrcambledStatus;
	psvcdat->ScramblingStatus	   =	svcdat_temp.ScramblingStatus;
    mCopyString( psvcdat->BrandIds, svcdat_temp.BrandIds, svcdat_temp.NumBrandIds );

    if(psvcdat->UserModifiedName == FALSE)
    {
        /* This means user has not renamed the service, so we can update the one sent by broadcaster */
        mCopyString( psvcdat->ChannelName, svcdat_temp.ChannelName, (eurdiv_ChannelNameLength - 1));
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::mCopyPtcBroadcastAttributes(HsvPgdatDigTSData *tsdata, HsvPgdatDigTSData tsdata_temp)
{
    tsdata->Frequency            =   tsdata_temp.Frequency;
    tsdata->ModulationType       =   tsdata_temp.ModulationType;               
    tsdata->HierarchyMode        =   tsdata_temp.HierarchyMode;
    tsdata->GuardInterval        =   tsdata_temp.GuardInterval;
    tsdata->TxMode               =   tsdata_temp.TxMode;
    tsdata->IqMode               =   tsdata_temp.IqMode;
    tsdata->Bandwidth            =   tsdata_temp.Bandwidth;
    tsdata->StreamPriority       =   tsdata_temp.StreamPriority;   
    tsdata->TimeError            =   tsdata_temp.TimeError;
    tsdata->FrequencyError       =   tsdata_temp.FrequencyError;
    tsdata->FrequencyOffset      =   tsdata_temp.FrequencyOffset;
    tsdata->VSignalStrength      =   tsdata_temp.VSignalStrength;
    tsdata->ASignalStrength      =   tsdata_temp.ASignalStrength;
    tsdata->QSignalStrength      =   tsdata_temp.QSignalStrength;
    tsdata->ChannelInformation   =   tsdata_temp.ChannelInformation; 
    tsdata->DecoderType          =   tsdata_temp.DecoderType;
    tsdata->SymbolRate           =   tsdata_temp.SymbolRate; 
    tsdata->OriginalNetworkId    =   tsdata_temp.OriginalNetworkId;
    tsdata->Tsid                 =   tsdata_temp.Tsid;
    tsdata->NetworkId            =   tsdata_temp.NetworkId;
    tsdata->TSVersion            =   tsdata_temp.TSVersion;
    tsdata->PtcListVersion       =   tsdata_temp.PtcListVersion;
    tsdata->CodeRate             =   tsdata_temp.CodeRate;
	tsdata->SDTVersion 			 = 	 tsdata_temp.SDTVersion;
	tsdata->NITVersion			 =	 tsdata_temp.NITVersion;
    tsdata->UserInstalled        =   tsdata_temp.UserInstalled;
}

void CHsvDvbTInstallation_mDataAcq_Priv::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat)
{
    HsvPATProgramPIDInfo    val;
    HsvPgdatDigServiceData  svcdat;

    psvcdat->DvbType                = AppApiDvbTypeT;
    psvcdat->ChannelLock            = 0;
    psvcdat->UserHidden             = 0;
    psvcdat->Favorite               = 0;
    psvcdat->ServiceListVersion     = rins_GetInstallationVersion();
    psvcdat->DateStamp = 0;
    psvcdat->HbbTvOption = 1;

    if( Timerclk_IsClockDefined() && (!MANUAL_INSTALL) )
    {
        psvcdat->DateStamp = Timerclk_GetUniversalTime();
    }
    if(strapi_GetByKey(HsvMain, HSVSPID(Program, mpeg, pat), psvcdat->ServiceId, HSVINVALIDKEY,HSVINVALIDKEY, (Address)(&val)))
    {
        psvcdat->PmtPid = val.Pid;

    }
    psvcdat->NewPreset = !AUTO_INSTALL;

    ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
    if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
    {
        mRetainNonBroadcastAttributes(psvcdat, svcdat);
    }


}

Bool CHsvDvbTInstallation_mDataAcq_Priv::mLcnVersion2Data(HsvPgdatDigServiceData *psvcdat)
{
    Bool retval = FALSE; 
    HsvDestination dest = HsvMain;
    int NoOfRecs, i, channellistid, from, to, countrycode;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) nwlcn; 

    NoOfRecs = strapi_GetSize(dest, HSVSPID(ActualNetworkLCN2, dvb, nit));
	TraceNotice(m,"NoOfRecs: %d",NoOfRecs);
    if( LCN_VERSION2_PRESENT(NoOfRecs) )
    {
	/* ANEESH: TODO: Currently srtdbids cannot be directly accessed from installation as its available only with the
		SDM class. So just commenting out this for compilation to go through. Have to check with Amith on how this
		implementation to be completed */
        /* 1. Matching country */
//		if(srtdb_SearchOnPrimaryKey(srtdbids_NitLcn2TableMain, sysset_GetSystemCountry(), &from, &to) == FALSE)
	    if(strapi_GetRangeByKey(dest,HSVSPID(ActualNetworkLCN2, dvb, nit),1 ,sysset_GetSystemCountry() ,0 ,0 , &from, &to) == FALSE)
        {
            from = 0, to = NoOfRecs;
        }
        /* 2. Matching country & smallest channel list */
        channellistid = mGetInterestedChanneListId(from, to, &countrycode); 
//      if(srtdb_SearchOnPrimaryAndSecondaryKey(srtdbids_NitLcn2TableMain, countrycode, channellistid, &from, &to) == TRUE) 
		if(strapi_GetRangeByKey(dest,HSVSPID(ActualNetworkLCN2, dvb, nit),2, countrycode, channellistid,0, &from, &to) == TRUE) 

        {
            for(i = from; i <= to; i++)
            {
//               if( (srtdb_QueryOnIndex(srtdbids_NitLcn2TableMain, i, (Address)&nwlcn) == TRUE) )
                if( (strapi_GetByIndex(dest,HSVSPID(ActualNetworkLCN2, dvb, nit), i, (Address)&nwlcn) == TRUE) )
                {
                    if( (psvcdat->OriginalNetworkId == nwlcn.Original_NetworkId) &&
                            (psvcdat->ServiceId == nwlcn.ServiceId)               &&
                            (psvcdat->Tsid == nwlcn.Tsid) )
                    {
						if(eurdiv_MultipleLCNSupported())
						{
							Nat8 k =0;
							for(k=0;k<MAX_LCNS;k++)	
							{
								psvcdat->MultipleLCN[k] = nwlcn.LCN[k];
								psvcdat->MultipleLCN[k] = ((psvcdat->MultipleLCN[k]==ZEROLCN)?(INVALID_ZERO_LCN):(psvcdat->MultipleLCN[k]));

							}
						}
						else
						{
							psvcdat->LCN			= (VALID_LCN_RANGE(nwlcn.LogicalChannelNum) == TRUE)? nwlcn.LogicalChannelNum: psvcdat->LCN;
						}
                        psvcdat->VisibleService = nwlcn.VisibleService;
                        retval = TRUE;

                        break;
                    }
                }
            }
        }
    }
    return retval;
}

inline int CHsvDvbTInstallation_mDataAcq_Priv::mGetInterestedChanneListId(int from, int to, int *countrycode)
{
    int i, channellistid;
    HsvDestination dest = HsvMain;
    HSVSPTYPE(ActualNetworkLCN2, dvb, nit) nwlcn; 

    strapi_GetByIndex(HsvMain, HSVSPID(ActualNetworkLCN2, dvb, nit), from, (void*)(&nwlcn));
    channellistid = nwlcn.ChannelListId;
    *countrycode = nwlcn.CountryCode;
    for(i = (from + 1); i <= to; i++)
    {
        if(TRUE == strapi_GetByIndex(dest, HSVSPID(ActualNetworkLCN2, dvb, nit), i, (void*)(&nwlcn)))
        {
            if(nwlcn.ChannelListId < channellistid)
            {
                *countrycode = nwlcn.CountryCode;
                channellistid = nwlcn.ChannelListId;
            }
        }
    }
    return channellistid;
}

void CHsvDvbTInstallation_mDataAcq_Priv::mAssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	TraceNotice(m,"mAssignLCN: %s: %d %d", __FUNCTION__,__LINE__,psvcdat->LCN);

    if(eurdiv_IsDbookCountry() == TRUE)
    {
        mAssignLCNForDbook(psvcdat);
    }
	else if(eurdiv_MultipleLCNSupported())
	{
		TraceNotice(m,"mAssignLCN: %s: %d : %d", __FUNCTION__,__LINE__,eurdiv_MultipleLCNSupported());
		mAssignMultipleLCN(psvcdat);

	}
    else
    {
        mAssignLCNForFrance(psvcdat);       
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::mDeleteServicesOfSameMux(Nat32 Frequency, Nat32 StreamPriority)
{
    int i = 0, noOfRecs,j=0;
    Bool pgdbRetval = FALSE;
    HsvPgdatDigTSData tsdata;
    HsvPgdatPresetData  presetdat;
    HsvPgdatDigServiceData tempsvcdat;

    if(MANUAL_INSTALL)
    {
        tsdata.Frequency = Frequency;
        tsdata.StreamPriority = StreamPriority;

        TraceDebug(m, "%s %d tsdata.Frequency %d tsdata.StreamPriority %d ", __FUNCTION__, __LINE__, (int)tsdata.Frequency, tsdata.StreamPriority);
        if(pgdb_GetByKey(PTC_TABLE, (Address)&tsdata))
        {
            noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
            for(i=0; i < noOfRecs; i++)
            {
                if(pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&tempsvcdat))
                {
                    if( (tempsvcdat.Frequency == tsdata.Frequency) && (tempsvcdat.StreamPriority == tsdata.StreamPriority) )
                    {
						if(eurdiv_MultipleLCNSupported())
						{
							for(j=0;j<MAX_LCNS;j++)
							{
								if(tempsvcdat.MultiplePreset[j] !=INVALID_PRESET )
								{
									presetdat.PresetNumber =   tempsvcdat.MultiplePreset[j];
									presetdat.Type         =   HsvOnePart;
									pgdbRetval = pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
								}
							}
						}
						else
						{
							presetdat.PresetNumber = tempsvcdat.PresetNumber;
							presetdat.Type = HsvOnePart;
                        
							pgdbRetval = pgdb_Delete(PRESET_TABLE,(void*)&presetdat);
                        TraceDebug(m, "%s %d pgdbRetval %d", __FUNCTION__, __LINE__, pgdbRetval);
						}
                        
                        pgdbRetval = pgdb_Delete(SERVICE_TABLE, (Address)&tempsvcdat);
                        TraceDebug(m, "%s %d pgdbRetval %d", __FUNCTION__, __LINE__, pgdbRetval);
                        i--;
                        noOfRecs--;                 
                    }
                }
            }
            pgdbRetval = pgdb_Delete(PTC_TABLE, (Address )&tsdata);
            TraceDebug(m, "%s %d pgdbRetval %d", __FUNCTION__, __LINE__, pgdbRetval);
        }
    }
}

inline void CHsvDvbTInstallation_mDataAcq_Priv::mLCNOverRuling(HsvPgdatDigServiceData *svcdat)
{
    HsvPgdatPresetData  presetdat;
    Bool pgdbRetval = FALSE;
	Nat8 j=0;
    
    if(MANUAL_INSTALL)
    {
		if(eurdiv_MultipleLCNSupported())
		{
			for(j=0;j<MAX_LCNS;j++)
			{
				if(svcdat->MultiplePreset[j] !=INVALID_PRESET )
				{
					presetdat.PresetNumber =   svcdat->MultiplePreset[j];
					if(pgdb_GetByKey (PRESET_TABLE, (Address)&presetdat))
					{
						pgdbRetval = pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
						svcdat->MultiplePreset[j] = INVALID_PRESET;
					}
					
				}
			}
		}
		else
		{
			presetdat.PresetNumber  =   svcdat->PresetNumber;   
			if(pgdb_GetByKey (PRESET_TABLE, (Address)&presetdat))
			{
				pgdbRetval = pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
				svcdat->PresetNumber = INVALID_PRESET;
            TraceDebug(m, "%s %d pgdbRetval %d PresetNumber %d", __FUNCTION__, __LINE__, pgdbRetval, presetdat.PresetNumber);
			}
		}
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::mAssignSvcHDSimulcastLinkageParams( HsvPgdatDigServiceData *svcdat )
{
	HsvLinkageInfo		sdtlinkage;
    HsvDestination dest = HsvMain;

    if( (svcdat->ServiceType == AppApiTelevisionService) && (TRUE == strapi_GetByKey(dest, HSVSPID(LinkageInfo, dvb, sdt), (int )svcdat->OriginalNetworkId, (int )svcdat->ServiceId, HDSimulcastNORDIG, (Address )&sdtlinkage) ) )
    {
        TraceDebug(m, "HDSimulcast: sdtlinkage.LinkageType = %02x ",sdtlinkage.LinkageType);
        TraceDebug(m, "HDSimulCast: Updating Service HDSimulcast LinkageType: [%04x|%04x|%04x] ",
                sdtlinkage.Original_NetworkId, sdtlinkage.Tsid, sdtlinkage.ServiceId);
        svcdat->HDSimulcastRepOnId  = sdtlinkage.Original_NetworkId;
        svcdat->HDSimulcastRepTsId  = sdtlinkage.Tsid;
        svcdat->HDSimulcastRepSvcId = sdtlinkage.ServiceId;
    }
}
void CHsvDvbTInstallation_mDataAcq_Priv::mDeleteSDTActuallNotService(HsvInstallationPTC *ptc)
{
	HsvPgdatDigServiceData svcdat;
	HsvDestination dest = HsvMain;
	HsvPgdatPresetData presetdat;
	HsvSDTSection val;
	int num =pgdb_GetNoRecords(SERVICE_TABLE);
	TraceDebug(m,"NoRecords=%d",num);
	int index=num;
	int TotalServicesInSdt = 0;
    TotalServicesInSdt = strapi_GetSize (dest, HSVSPID(ActualTSService, dvb, sdt));
	if (TotalServicesInSdt)
	{
		for(index;index>0;index--)
		{
			if(pgdb_GetByIndex(SERVICE_TABLE,(index-1),(Address)&svcdat))
			{	
				if((svcdat.Frequency==ptc->Frequency)&&(svcdat.StreamPriority==ptc->StreamPriority))
					{
						TraceDebug(m,"svcdat.Frequency[%d]=%d and svcdat.StreamPriority =%d",(index-1),svcdat.Frequency,svcdat.StreamPriority);
						if(FALSE == strapi_GetByKey(dest,HSVSPID(ActualTSService, dvb, sdt), (int )svcdat.OriginalNetworkId, (int )svcdat.ServiceId, (int )svcdat.Tsid, (Address)&val) ) 
						{
							pgdb_Delete(SERVICE_TABLE,(Address)&svcdat);
							if(eurdiv_MultipleLCNSupported())
							{
								for(int k=0;k<MAX_LCNS;k++)	
								{
									if(svcdat.MultiplePreset[k] != INVALID_PRESET)
									{
										TraceDebug(m,"presetdat Preset deleted=%d",svcdat.MultiplePreset[k]);										
										presetdat.PresetNumber = svcdat.MultiplePreset[k];
										pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
									}
								}
							}
							else
							{
								presetdat.PresetNumber = svcdat.PresetNumber;
								pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
									
							}
						}
					}	
			}
			else
				{
				TraceDebug(m,"GetByIndex fail at Index[%d]=%d",index,index);

				}
		}
	}
	else
	{
		TraceNotice (m, "Deletion Triggered when nothing in strapi. May be next tune happened. Ignoring.. ");
	}
}
void CHsvDvbTInstallation_mDataAcq_Priv::mDeleteHDSimulcastSDServices(void)
{
    HsvPgdatDigServiceData  svcdat_temp,svcdat,qry_svcdat;
    HsvPgdatPresetData presetdat;
    int index       = -1, srvindex    = -1, from,to,max,min;
    
    if ( eurdiv_IsHDSimulcastSupported() == TRUE )
    {
        max = pgdb_GetNoRecords(SERVICE_TABLE);
        min = 0;
        TraceDebug(m, "HDSimulCast: Into %s ", __FUNCTION__);
        for (index = min; index <=max; index++)
        {
            if(pgdb_GetByIndex( SERVICE_TABLE, index,(Address)&svcdat))
            {
                if( (svcdat.ServiceType == TelevisionService)  && HD_SIMULCAST_LINKAGE(svcdat) )
                {
                    TraceDebug(m, "HDSimulCast: Service [%04x|%04x|%04x|%02d] ",  svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId,svcdat.ServiceType );
                    TraceDebug(m, "HDSimulCast: is Linked to [%04x|%04x|%04x] ",svcdat.HDSimulcastRepOnId,svcdat.HDSimulcastRepTsId,svcdat.HDSimulcastRepSvcId);

                    svcdat_temp.OriginalNetworkId = svcdat.HDSimulcastRepOnId;
                    svcdat_temp.ServiceId = svcdat.HDSimulcastRepSvcId;
                    if(pgdb_GetRange(SERVICE_TABLE, 2, (Address)&svcdat_temp, &from, &to))
                    {
                        ASSERT(from<=to);
                        for(srvindex=from; srvindex<=to; srvindex++)
                        {
                            if( pgdb_GetByIndex(SERVICE_TABLE, srvindex, (Address)&qry_svcdat) )
                            {
                                if(svcdat.HDSimulcastRepTsId == qry_svcdat.Tsid)
                                {
                                    TraceDebug(m,"HDSimulCast: Replacement Service Found.. Checking if its HD");
                                    if(qry_svcdat.ServiceType == AppApiAdvCodecHDTelevisionService )
                                    {
                                        TraceDebug(m, "HDSimulCast: Service to be deleted svcdat.PresetNumber %d", svcdat.PresetNumber);
                                        if(svcdat.PresetNumber != INVALID_PRESET)
                                        {
											TraceNotice(m,"HDSimulcast: Deleting Preset %d",svcdat.PresetNumber);
                                            presetdat.PresetNumber = svcdat.PresetNumber;
                                            presetdat.Type = HsvOnePart;
                                            pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
											if(CURRENT_MODE == UPDATE_MODE)
											{
												TraceDebug(m, "we are not decrementing mDigitalChannelsFound[%d]",mDigitalChannelsFound);
											}
											else
											{
                                           		 mDigitalChannelsFound--;
											}
                                            TraceDebug(m, "HDSimulCast: Raising Channel Removed Event");
                                            sortN_OnEvent(sortN_EventChannelRemoved, rins_GetInstallationMode());
                                        }
                                        else
                                        {
                                           	if(CURRENT_MODE == UPDATE_MODE)
											{
											TraceDebug(m, "we are not decrementing mDigitalChannelsFound[%d]",mDigitalChannelsFound);
											}
											else{
                                            mDigitalChannelsFound--;
											}
                                            TraceDebug(m, "HDSimulCast: Digital Channels Found =%d",mDigitalChannelsFound );
                                        }
										TraceNotice(m,"HDSimulcast: Deleting Service %d",svcdat.ServiceId);
                                        pgdb_Delete(SERVICE_TABLE,(Address)&svcdat);srvindex--;to--;index--;max--;
                                        break;
                                    }
                                }
                            }       
                        }               
                    }                   
                }
            }
        }
    }
} 

Bool CHsvDvbTInstallation_mDataAcq_Priv::mDeleteDuplicateRecords(HsvPgdatDigServiceData *svcdat)
{
    Bool retval = FALSE, Proceed = TRUE;
    HsvPgdatDigServiceData svcdat2;
    int j,i, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
	HsvPgdatPresetData presetdat;

    for(j = 0; j < noOfRecs; j++)
    {
        if( pgdb_GetByIndex(SERVICE_TABLE, j, (Address)&svcdat2) == TRUE )
        {
            /* check for triplet key & decoder type */
            if( (svcdat->OriginalNetworkId == svcdat2.OriginalNetworkId)    &&
                (svcdat->ServiceId         == svcdat2.ServiceId)            &&
                (svcdat->DecoderType       == svcdat2.DecoderType)
              )
            {
                Proceed = TRUE;
                if(eurdiv_TripletKey( rins_GetMedium()) && (svcdat->Tsid != svcdat2.Tsid))
                {
                    Proceed = FALSE;
                }
                if(Proceed)
                {/*we are storing all other details of old service so that we can retain their attribute in update of same service at different Frequency*/
					svcdat->NewPreset			= svcdat2.NewPreset;
					svcdat->PresetNumber		= svcdat2.PresetNumber;
					svcdat->EPGEnabled			= svcdat2.EPGEnabled;
					svcdat->ChannelLock 		= svcdat2.ChannelLock;
					svcdat->UserHidden			= svcdat2.UserHidden;
					svcdat->Favorite			= svcdat2.Favorite;
					svcdat->FavoriteNumber		= svcdat2.FavoriteNumber;
					svcdat->ServiceListVersion	= svcdat2.ServiceListVersion;
					svcdat->HbbTvOption 		= svcdat2.HbbTvOption;
					svcdat->EPGShortInfo		= svcdat2.EPGShortInfo;
                	
                /* Retain Preset Number of the old service */
				if(eurdiv_MultipleLCNSupported())
				{
					for(i=0;i<MAX_LCNS;i++)
					{
						svcdat->MultiplePreset[i] =   svcdat2.MultiplePreset[i];
					}
				}
				else
				{			
					svcdat->PresetNumber    =   svcdat2.PresetNumber;
				}
                pgdb_Delete(SERVICE_TABLE,(Address) &svcdat2);
                j--;noOfRecs--;
                sortN_OnEvent(sortN_EventChannelRemoved, rins_GetInstallationMode());


				REVALIDATE(svcdat2.LCN); //this is required because we would have invalidated LCN in previous pass due to conflicts if any			
				if( (VALID_LCN_RANGE(svcdat2.LCN) || VALID_LCN_RANGE(svcdat->LCN)) &&		
					(svcdat2.LCN != svcdat->LCN) )				
				{
					if(eurdiv_UpdateLCN(rins_GetMedium()))	
					{		
					/* below done, because the LCN changes presets are sorted freshly as per design of ItaSort */				
					TraceNotice(m,"%s %d deleted preset becoz => psvcdat->LCN %d svcdat.LCN %d svcdat.PresetNumber %d", __FUNCTION__, __LINE__, svcdat2.LCN, svcdat->LCN, svcdat2.PresetNumber);	
					presetdat.PresetNumber =   svcdat2.PresetNumber;		
					presetdat.Type         =   HsvOnePart;						
					pgdb_Delete(PRESET_TABLE,(Address)&presetdat);				
					svcdat->PresetNumber = INVALID_PRESET;					
					}				
				}
				
                retval = TRUE;
                TraceDebug(m, "service deleted Preset %d, ServiceId:%d ", svcdat->PresetNumber, svcdat->ServiceId);
               
                }
            }
        }
    }
    return retval;
}

void CHsvDvbTInstallation_mDataAcq_Priv::mRetainNonBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvPgdatDigServiceData svcdat)
{
	Nat8 i =0;
	
	if(eurdiv_MultipleLCNSupported())
	{
		for(i=0;i<MAX_LCNS;i++)
		{
			psvcdat->MultiplePreset[i] =   (BACKGROUND_INSTALL)? svcdat.MultiplePreset[i] : psvcdat->MultiplePreset[i];
		}
		psvcdat->PresetNumber =   (BACKGROUND_INSTALL)? svcdat.MultiplePreset[0] : psvcdat->MultiplePreset[0];
		
	}
	else
	{	
		psvcdat->PresetNumber			= (BACKGROUND_INSTALL)? svcdat.PresetNumber : psvcdat->PresetNumber;
	}
    psvcdat->NewPreset              = svcdat.NewPreset;
    psvcdat->EPGEnabled             = svcdat.EPGEnabled;
    psvcdat->ChannelLock            = svcdat.ChannelLock;
    psvcdat->UserHidden             = svcdat.UserHidden;
    psvcdat->Favorite               = svcdat.Favorite;
    psvcdat->FavoriteNumber         = svcdat.FavoriteNumber;
    psvcdat->ServiceListVersion     = svcdat.ServiceListVersion;
    psvcdat->HbbTvOption            = svcdat.HbbTvOption;
    psvcdat->EPGShortInfo           = svcdat.EPGShortInfo;
    psvcdat->SAP                    = svcdat.SAP;
    psvcdat->DeltaVolume            = svcdat.DeltaVolume;
    psvcdat->UserModifiedName       = svcdat.UserModifiedName;
    psvcdat->PreferredStereo        = svcdat.PreferredStereo;
    psvcdat->HMBlanked              = svcdat.HMBlanked;
    psvcdat->HMProtectedChannel     = svcdat.HMProtectedChannel ;
    psvcdat->HMMapChannelNo         = svcdat.HMMapChannelNo;
    psvcdat->LogoURL                = svcdat.LogoURL;
    psvcdat->EPGShortInfo           = svcdat.EPGShortInfo;
    psvcdat->VideoPid               = svcdat.VideoPid;             
    psvcdat->AudioPid               = svcdat.AudioPid;
    psvcdat->PcrPid                 = svcdat.PcrPid;   
    psvcdat->VideoStreamType        = svcdat.VideoStreamType;
    psvcdat->AudioStreamType        = svcdat.AudioStreamType;
    psvcdat->SecAudioStreamType     = svcdat.SecAudioStreamType;
    psvcdat->SecAudioPid            = svcdat.SecAudioPid;
    memcpy(psvcdat->UniqueIds, svcdat.UniqueIds, sizeof(svcdat.UniqueIds));
}

Bool CHsvDvbTInstallation_mDataAcq_Priv::mIsServiceInstallable(HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt)* service)
{
    Bool lRetVal = TRUE;
    HsvPgdatDigServiceData lsvcdat;
    int FreeCAMode = DVBC_INVALID_FREECA_MODE;
	Nat8 i=0;

    lsvcdat.OriginalNetworkId = DigInsStatus.Onwid;
    lsvcdat.ServiceId = service->ServiceId;
    lsvcdat.Frequency = ptc->Frequency;
    lsvcdat.StreamPriority = ptc->StreamPriority;
    lsvcdat.Tsid = DigInsStatus.Tsid;
    lsvcdat.DecoderType = feapi_ChanDecDvbT;

    FreeCAMode = idvbset_GetAttribute(rins_InstallationModeAutomatic , rins_AttributeScrOrFTA);
    TraceNotice(m,"FREECAMODE=%d",FreeCAMode);
    if(FreeCAMode == FALSE)
    {
        TraceNotice(m,"Function:%s::Line %d",__FUNCTION__,__LINE__);
        if(((int)service->Free_CA_Mode != FreeCAMode))
        {
            lRetVal = FALSE;
            TraceNotice(m,"Function:%s::Line %d",__FUNCTION__,__LINE__);
            if ((!AUTO_INSTALL) &&  (pgdb_GetByKey(SERVICE_TABLE, (Address )&lsvcdat) == TRUE))
            {
				if(eurdiv_MultipleLCNSupported())
				{
					for(i=0;i<MAX_LCNS;i++)
					{
						if(PRESET_ALLOCATED(lsvcdat.MultiplePreset[i])) //already present
						{
							//PrintfNotice("ALREADY Present in List Function:%s::Line %d\n",__FUNCTION__,__LINE__);
							lRetVal = TRUE;
							break;
						}

					}
				}
				else
				{
					if(PRESET_ALLOCATED(lsvcdat.PresetNumber)) //already present
					{
						TraceNotice(m,"ALREADY Present in List Function:%s::Line %d",__FUNCTION__,__LINE__);
						lRetVal = TRUE;
					}
				}
			}
        }
                
    }
    TraceNotice(m,"FUNCTION=%s:Line=%d::FREECA MODE Of Service=%d::ServiceID=%x",__FUNCTION__,__LINE__,service->Free_CA_Mode,service->ServiceId);
    lRetVal = lRetVal && eurdiv_IsServiceInstallable( rins_GetMedium(), service->ServiceType); 

    return lRetVal;

}

Bool CHsvDvbTInstallation_mDataAcq_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}

/*From HsvDbookOperators.c*/

void CHsvDvbTInstallation_mDataAcq_Priv::mDbookInitialise(void)
{
    int i;
    int BufferPoolSize  =  ( MAX_NUMBER_SERVICES * sizeof(HsvTargetRegionCache) );
    memset((Address)(&mRegionsData), 0, sizeof(mRegionsData));
    if (TargetRegionCachePoolId == -1)
    {
        TargetRegionCachePoolId = hpool_Create( hpool_MemLocalNoFatal, ( BufferPoolSize + BUFF_ADMIN_MEMORY ),"Mult TRD Cache pool");
    }

    if( ( TargetRegionCachePoolId != -1) && ( !mTargetRegionCache ) )
    {
        mTargetRegionCache = (HsvTargetRegionCache *)hpool_Malloc( TargetRegionCachePoolId, BufferPoolSize );
    }

    if( mTargetRegionCache )
    {
        memset ((Address)( mTargetRegionCache ), 0, (sizeof(HsvTargetRegionCache) * MAX_NUMBER_SERVICES));

        for (i = 0; i < MAX_NUMBER_SERVICES; i++)
        {
            mTargetRegionCache[i].OnId        = 0xFFFF;
            mTargetRegionCache[i].Tsid        = 0xFFFF;
            mTargetRegionCache[i].ServiceId   = 0xFFFF;
            mTargetRegionCache[i].NetworkId   = 0xFFFF;

        }
    }
    mUserPrimaryRegionIndex = mUserSecondaryRegionIndex = mUserTertiaryRegionIndex = 0;
}

void CHsvDvbTInstallation_mDataAcq_Priv::mDbookAcquireNetworkData(void)
{
    int i;
    HsvNITTargetRegionName TargetRegionName;

    if(AUTO_INSTALL)
    {
        int NoofRecs = strapi_GetSize(HsvMain, HSVSPID(TargetRegionName, dvb, nit));

        TraceDebug(m,"%s %d NoofRecs %d", __FUNCTION__, __LINE__, NoofRecs);
        for(i = 0; i < NoofRecs; i++)
        {
            if(strapi_GetByIndex(HsvMain, HSVSPID(TargetRegionName, dvb, nit), i, &TargetRegionName))
            {       
                /* Store RegionName */
                mAddRegionInList(TargetRegionName);
            }
        }
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::mDbookAcquireServiceData(HsvPgdatDigServiceData *psvcdat)
{
    Nat16 NetworkId = 0;
    HsvSDTTargetRegion SdtTargetRegion;
    HsvNITTargetRegion NitTargetRegion;

    if(!strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkId))
    {
        NetworkId = 0;
    }
    if(strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, sdt), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &SdtTargetRegion))
    {
        if(VALID_REGIONS(*psvcdat) == FALSE)
        {
			mAddinCachedRegionList (&SdtTargetRegion, psvcdat );
        }
    }
    else
    {
        /* check if available in the 2nd loop of NIT */
        Bool retval = strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, NetworkId, &NitTargetRegion);

        if(retval == FALSE)
        {
            /* query again as it mioght be there in the 1st loop of NIT */
            retval = strapi_GetByKey(HsvMain, HSVSPID(TargetRegion, dvb, nit), 0xFFFF, 0xFFFF, NetworkId, &NitTargetRegion);
        }

        if(retval == TRUE)
        {
            if(VALID_REGIONS(*psvcdat) == FALSE)
			{
			    mAddinCachedRegionList ( ( HsvSDTTargetRegion * ) &NitTargetRegion, psvcdat );
			}
        }
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetRegionList(HsvNetworkRegionsData *RegionsData)
{
    TraceNotice(m,"%s %d NoOfPrimaryRegions %d", __FUNCTION__, __LINE__, NUM_PRIMARY_REGIONS);
    memcpy((Address)(RegionsData), (Address)(&mRegionsData), sizeof(HsvNetworkRegionsData));
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_SetFavouriteRegion(int mode, int index, HsvEnmRegionType RegionType)
{
    int   Attribute;
    Bool  ValidData = FALSE;
    Nat16 RegionCode;

    switch(RegionType)
    {
        case HsvPrimaryRegion:
            ValidData   = (index <= mRegionsData.NoOfRegions - 1)?   TRUE : FALSE;
            if(ValidData)
            {
                mUserPrimaryRegionIndex = index;
                Attribute = rins_AttributePrimaryRegion;
                RegionCode  = PRIMARY_REGION_CODE(mUserPrimaryRegionIndex);
            }
            break;
        case HsvSecondaryRegion:
            ValidData   = (index <= SECONDARY_REGION_LASTINDEX(mUserPrimaryRegionIndex))? TRUE : FALSE;
            if(ValidData)
            {
                mUserSecondaryRegionIndex = index;
                Attribute = rins_AttributeSecondaryRegion;
                RegionCode  = SECONDARY_REGION_CODE(mUserPrimaryRegionIndex, mUserSecondaryRegionIndex);
            }
            break;
        case HsvTertiaryRegion:
            ValidData   = (index <= TERTIARY_REGION_LASTINDEX(mUserPrimaryRegionIndex, mUserSecondaryRegionIndex))?  TRUE : FALSE;
            if(ValidData)
            {
                mUserTertiaryRegionIndex = index;
                Attribute = rins_AttributeTertiaryRegion;
                RegionCode  = TERTIARY_REGION_CODE(mUserPrimaryRegionIndex, mUserSecondaryRegionIndex, mUserTertiaryRegionIndex);
            }
            break;
        default:
            break;
    }

    if(ValidData)
    {
        idvbset_SetAttribute(mode, Attribute, RegionCode);
        TraceDebug(m,"%s %d user selected %s Region => %d", __FUNCTION__, __LINE__, (RegionType == HsvPrimaryRegion)? "Primary" : (RegionType == HsvSecondaryRegion)? "Secondary" : "Tertiary", RegionCode);
    }
}

int CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetFavouriteRegion(int mode, HsvEnmRegionType RegionType)
{
    int retval = 0;
    if(mode == AUTO_MODE)
    {
        switch(RegionType)
        {
            case HsvPrimaryRegion:
                retval = mUserPrimaryRegionIndex;
                break;
            case HsvSecondaryRegion:
                retval = mUserSecondaryRegionIndex;
                break;
            case HsvTertiaryRegion:
                retval = mUserTertiaryRegionIndex;
                break;
            default:
                break;
        }
    }
    TraceDebug(m,"%s %d retval %d Region %d", __FUNCTION__, __LINE__, retval, RegionType);
    return retval;
}
void CHsvDvbTInstallation_mDataAcq_Priv::mClearCache(void)
{
    TraceDebug(m,"%s %d P %d", __FUNCTION__, __LINE__, PRIMARY_REGION_LASTINDEX);
    memset((Address)&mRegionsData, 0, sizeof(mRegionsData));
    // free the buffer allocated to the target region cache for service at the end of installation. 
    if ( ( mTargetRegionCache ) && ( TargetRegionCachePoolId != -1 ) )
    {
        hpool_Free( TargetRegionCachePoolId, mTargetRegionCache );
        mTargetRegionCache = NULL;
    }

    if (TargetRegionCachePoolId != (-1))
    {
        hpool_Destroy(TargetRegionCachePoolId);
        TargetRegionCachePoolId = -1;
    }
    mUserPrimaryRegionIndex = mUserSecondaryRegionIndex = mUserTertiaryRegionIndex = 0;
}

void CHsvDvbTInstallation_mDataAcq_Priv::mAddRegionInList(HsvNITTargetRegionName TargetRegionName)
{
    Bool Update = FALSE;
    int i = 0, j = 0, k = 0;
    switch(TargetRegionName.RegionDepth)
    {
        case HsvPrimaryRegion:

            i = mGetPrimaryRegionIndex(TargetRegionName.Primary.RegionCode, TargetRegionName.Langcode, &Update);
            TraceNotice(m," HsvDbookOperators %d %s i = %d, TargetRegionName.Primary.RegionCode = %d  ", __LINE__, __FUNCTION__, i, TargetRegionName.Primary.RegionCode);
            if( ( i == INVALID_INDEX ) && ( mRegionsData.NoOfRegions < MAX_NETWORKS ) )
            {
                Update = TRUE; 
                mRegionsData.NoOfRegions++;
                i = mRegionsData.NoOfRegions - 1;
                TraceNotice(m,"HsvDbookOperators %d %s i = %d, mRegionsData.NoOfRegions = %d ", __LINE__, __FUNCTION__, i, mRegionsData.NoOfRegions );
            }
            if(Update == TRUE)
            {
                mRegionsData.Primary[i].RegionCode = TargetRegionName.Primary.RegionCode;
                memcpy((Address)mRegionsData.Primary[i].RegionName , TargetRegionName.Primary.RegionName, MAX_REGION_NAME_SIZE);

                TraceDebug(m,"%s %d <P> => <%ld> Added i = %d ", __FUNCTION__, __LINE__, PRIMARY_REGION_CODE(i), j);
            }
            break;


        case HsvSecondaryRegion:


            i = mGetPrimaryRegionIndex(TargetRegionName.Primary.RegionCode, TargetRegionName.Langcode, &Update);
            TraceNotice(m,"HsvDbookOperators %d %s i = %d, TargetRegionName.Primary.RegionCode = %d  ", __LINE__, __FUNCTION__, i, TargetRegionName.Primary.RegionCode);
            if( ( i == INVALID_INDEX) && ( mRegionsData.NoOfRegions <MAX_NETWORKS ) )
            {

                Update = TRUE; 
                mRegionsData.NoOfRegions++;
                i = mRegionsData.NoOfRegions -1;


                TraceNotice(m,"HsvDbookOperators : %d %s mRegionsData.NoOfRegions = %d ", __LINE__, __FUNCTION__, mRegionsData.NoOfRegions);
            }
            if(Update == TRUE)
            {
                mRegionsData.Primary[i].RegionCode = TargetRegionName.Primary.RegionCode;
                memcpy((Address)(mRegionsData.Primary[i].RegionName), TargetRegionName.Primary.RegionName, MAX_REGION_NAME_SIZE);


            }

            Update = FALSE; /* Reset and check for Next Region */
            j = mGetSecondaryRegionIndex(TargetRegionName.Primary.Secondary.RegionCode, TargetRegionName.Langcode, i, &Update);
            if( ( j == INVALID_INDEX ) && ( mRegionsData.Primary[i].NoOfRegions < MAX_NETWORKS ) )
            {
                Update = TRUE;
                mRegionsData.Primary[i].NoOfRegions++;
                j = mRegionsData.Primary[i].NoOfRegions - 1;

            }
            if(Update == TRUE)
            {
                mRegionsData.Primary[i].Secondary[j].RegionCode  = TargetRegionName.Primary.Secondary.RegionCode;
                memcpy((Address)( mRegionsData.Primary[i].Secondary[j].RegionName ), TargetRegionName.Primary.Secondary.RegionName, MAX_REGION_NAME_SIZE);
                TraceDebug(m,"%s %d <P S> => <%ld %ld> Added", __FUNCTION__, __LINE__, mRegionsData.Primary[i].RegionCode, mRegionsData.Primary[i].Secondary[j].RegionCode);
            }
            break;
        case HsvTertiaryRegion:     /* means it has Primary, Secondary & Tertiary regions in stream - so populate all */        

            i = mGetPrimaryRegionIndex(TargetRegionName.Primary.RegionCode, TargetRegionName.Langcode, &Update);
            if( ( i == INVALID_INDEX ) && (mRegionsData.NoOfRegions < MAX_NETWORKS))
            {
                Update = TRUE; 
                mRegionsData.NoOfRegions++;
                i = mRegionsData.NoOfRegions -1;
            }
            if(Update == TRUE)
            {
                mRegionsData.Primary[i].RegionCode = TargetRegionName.Primary.RegionCode;
                memcpy((Address)(mRegionsData.Primary[i].RegionName), TargetRegionName.Primary.RegionName, MAX_REGION_NAME_SIZE);
            }

            Update = FALSE; /* Reset and check for Next Region */
            j = mGetSecondaryRegionIndex(TargetRegionName.Primary.Secondary.RegionCode, TargetRegionName.Langcode, i, &Update);

            if( ( j == INVALID_INDEX) && ( mRegionsData.Primary[i].NoOfRegions < MAX_NETWORKS ) )
            {
                Update = TRUE;
                mRegionsData.Primary[i].NoOfRegions++;
                j = mRegionsData.Primary[i].NoOfRegions - 1;
                TraceNotice(m,"Lithesh : %d %s mRegionsData.Primary[i].NoOfRegions  = %d ", __LINE__, __FUNCTION__, mRegionsData.Primary[i].NoOfRegions );
            }

            if(Update == TRUE)
            {
                mRegionsData.Primary[i].Secondary[j].RegionCode  = TargetRegionName.Primary.Secondary.RegionCode;
                memcpy((Address)( mRegionsData.Primary[i].Secondary[j].RegionName ), TargetRegionName.Primary.Secondary.RegionName, MAX_REGION_NAME_SIZE);
            }

            Update = FALSE; /* Reset and check for Next Region */
            k = mGetTertiaryRegionIndex(TargetRegionName.Primary.Secondary.Tertiary.RegionCode, TargetRegionName.Langcode, i, j, &Update);

            if( ( k == INVALID_INDEX )  && ( mRegionsData.Primary[i].Secondary[j].NoOfRegions < MAX_NETWORKS ) )
            {
                Update = TRUE; 
                mRegionsData.Primary[i].Secondary[j].NoOfRegions++;
                k = ( mRegionsData.Primary[i].Secondary[j].NoOfRegions - 1 );
            }

            if(Update == TRUE)
            {
                mRegionsData.Primary[i].Secondary[j].Tertiary[k].RegionCode = TargetRegionName.Primary.Secondary.Tertiary.RegionCode;
                memcpy((Address)(TERTIARY_REGION_NAME(i, j, k)), TargetRegionName.Primary.Secondary.Tertiary.RegionName, MAX_REGION_NAME_SIZE);

                TraceDebug(m,"%s %d <P S T> => <%ld %ld %ld> Added", __FUNCTION__, __LINE__, PRIMARY_REGION_CODE(i), SECONDARY_REGION_CODE(i, j), TERTIARY_REGION_CODE(i, j, k));
            }
            break;
        default:
            break;
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::mAssignLCNForDbook(HsvPgdatDigServiceData *psvcdat)
{

    Bool retval = FALSE;
    HsvPgdatDigServiceData svcdat_temp;

    HSVSPTYPE(ActualSRVCATRB, dvb, nit) nwsrvcattrb;
    HSVSPTYPE(ActualNetworkHDSLCN, dvb, nit) nwhdslcn;
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) nwlcn;

    if(mLCNParsingRequired((Nat16)(psvcdat->OriginalNetworkId)))
    {
        Bool LCNv2Present = mLcnVersion2Data(psvcdat);

        if(eurdiv_SupportHDSLCN(rins_GetMedium()) == TRUE)
        {
            if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkHDSLCN, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &nwhdslcn))
            {   
                psvcdat->LowPrioLCN     = (VALID_LCN_RANGE(nwhdslcn.LogicalChannelNum) == TRUE)? nwhdslcn.LogicalChannelNum: psvcdat->LCN;
                psvcdat->LowPrioVisibleService = nwhdslcn.VisibleService;
                retval = TRUE;
            }
        }       
        if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkLCN, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &nwlcn) == TRUE)
        {
            if(LCNv2Present == FALSE)
            {
                psvcdat->LCN            = (VALID_LCN_RANGE(nwlcn.LogicalChannelNum) == TRUE)? nwlcn.LogicalChannelNum: psvcdat->LCN;
                psvcdat->VisibleService = nwlcn.VisibleService;
                retval = TRUE;

            }
        }
    }

    if(eurdiv_IsServiceAttrbDescSupported(rins_GetMedium()))
    {
        if(strapi_GetByKey(HsvMain, HSVSPID(ActualSRVCATRB, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &nwsrvcattrb))
        {
            psvcdat->NumericSelect  = nwsrvcattrb.NumericSelect;
            psvcdat->VisibleService = nwsrvcattrb.VisibleService;
            retval = TRUE;
        }
    }

    if(psvcdat->LCN == ZEROLCN)
    {
        if (eurdiv_IsZeroLCNHidden())   /* brg36mgr# 95132 CR */
        {
            psvcdat->NumericSelect  = SRVCNOTSELECTABLE;
            psvcdat->VisibleService = SRVCNOTVISIBLE;
        }
        else
        {
            /* CR implementation. change lcn to invalid lcn so that its not hidden but
               treated as normal non honoured service */
            psvcdat->LCN            = INVALID_LCN;
            psvcdat->NumericSelect  = TRUE;
            psvcdat->VisibleService = TRUE;
        }
    }

    if(!retval)
    {
        svcdat_temp.OriginalNetworkId=psvcdat->OriginalNetworkId;
        svcdat_temp.ServiceId=psvcdat->ServiceId;
        svcdat_temp.Frequency=psvcdat->Frequency;
        svcdat_temp.StreamPriority=psvcdat->StreamPriority;

        if(pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat_temp) == TRUE)
        {
            psvcdat->LCN            = svcdat_temp.LCN;
            psvcdat->VisibleService = svcdat_temp.VisibleService;
            psvcdat->NumericSelect  = svcdat_temp.NumericSelect;
            
            TraceDebug(m,"%s %d LCN %d <%d, %d, %d>", __FUNCTION__, __LINE__, psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
        }
    }


    TraceDebug(m,"%s %d LCN %d <%d, %d, %d>", __FUNCTION__, __LINE__, psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
}

int CHsvDvbTInstallation_mDataAcq_Priv::mGetPrimaryRegionIndex(Nat16 RegionCode, Nat32 Langcode, Bool *UpdateEntry)
{
    int i, retval = INVALID_INDEX;
    *UpdateEntry = FALSE;
    for(i = 0; i <= (int)PRIMARY_REGION_LASTINDEX; i++)
    {
        if(RegionCode == mRegionsData.Primary[i].RegionCode)
        {
            retval = i;
            if(Langcode != mRegionsData.Langcode)
            {
                if( (sysset_GetSystemLanguage() == (int)Langcode) || (langids_LangEnglish == (int)Langcode) )
                {
                    *UpdateEntry = TRUE;
                }
            }
        }
    }
    TraceDebug(m,"%s %d retval %d for <%d %ld>", __FUNCTION__, __LINE__, retval, RegionCode, Langcode);
    return retval;
}

int CHsvDvbTInstallation_mDataAcq_Priv::mGetSecondaryRegionIndex(Nat16 RegionCode, Nat32 Langcode, int PrimaryIndex, Bool *UpdateEntry)
{
    int i, retval = INVALID_INDEX;
    *UpdateEntry = FALSE;
    for(i = 0; i < (int)(mRegionsData.Primary[PrimaryIndex].NoOfRegions); i++)
    {
        if(RegionCode == mRegionsData.Primary[PrimaryIndex].Secondary[i].RegionCode)
        {
            TraceNotice(m,"Lithesh : %d %s ", __LINE__, __FUNCTION__);
            retval = i;
            if(Langcode != mRegionsData.Langcode)
            {
                if( (sysset_GetSystemLanguage() == (int)Langcode) || (langids_LangEnglish == (int)Langcode) )
                {
                    *UpdateEntry = TRUE;
                }
            }
        }
    } 
    TraceDebug(m,"%s %d retval %d for <%d %ld>", __FUNCTION__, __LINE__, retval, RegionCode, Langcode);
    return retval;
}

int CHsvDvbTInstallation_mDataAcq_Priv::mGetTertiaryRegionIndex(Nat16 RegionCode, Nat32 Langcode, int PrimaryIndex, int SecondaryIndex, Bool *UpdateEntry)
{
    int i, retval = INVALID_INDEX;
    *UpdateEntry = FALSE;
    for(i = 0; i <= (int)(TERTIARY_REGION_LASTINDEX(PrimaryIndex, SecondaryIndex)); i++)
    {
        if(RegionCode == mRegionsData.Primary[PrimaryIndex].Secondary[SecondaryIndex].Tertiary[i].RegionCode)
        {
            retval = i;
            if(Langcode != mRegionsData.Langcode)
            {
                if( (sysset_GetSystemLanguage() == (int)Langcode) || (langids_LangEnglish == (int)Langcode) )
                {
                    *UpdateEntry = TRUE;
                }
            }
        }
    }
    TraceDebug(m,"%s %d retval %d for <%d %ld>", __FUNCTION__, __LINE__, retval, RegionCode, Langcode);
    return retval;
}


void CHsvDvbTInstallation_mDataAcq_Priv::mAddinCachedRegionList ( HsvSDTTargetRegion * TargetRegion, HsvPgdatDigServiceData *psvcdat )
{
    // implement the cache here. 
    int i = 0;
	if ( mTargetRegionCache != NULL  )
	{
		for (i = 0; i < MAX_NUMBER_SERVICES ; i++)
		{
			if ( (mTargetRegionCache[i].ServiceId == 0xFFFF) ||( ( mTargetRegionCache[i].OnId ==  psvcdat->OriginalNetworkId ) && ( mTargetRegionCache[i].Tsid == psvcdat->Tsid ) && ( mTargetRegionCache[i].ServiceId == psvcdat->ServiceId ) ) )
			{
				//PrintfNotice("DbookOperators : %d %s i = %d \n", __LINE__, __FUNCTION__, i);
                
                /*  Update the attributes we need to cache the target regions with (i.e. triplets) */
                /*  Based on this cached list, we calculate the priority of the services  */
                TargetRegion->OnId      = psvcdat->OriginalNetworkId;
                TargetRegion->Tsid      = psvcdat->Tsid;
                TargetRegion->ServiceId = psvcdat->ServiceId;
                
				memcpy((Address)( mTargetRegionCache + i ), (Address)(TargetRegion), sizeof(HsvTargetRegionCache));
				break;
			}	
		}
	}
}


void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetCachedRegionDetails(HsvTargetRegionCache * RegionCache)
{
    if ( ( mTargetRegionCache != NULL ) && ( RegionCache != NULL ) )
    {
        memcpy((Address)RegionCache, (Address)mTargetRegionCache, (MAX_NUMBER_SERVICES * sizeof(HsvTargetRegionCache)));
    }
}

/*From HsvDvbGeneric*/

void CHsvDvbTInstallation_mDataAcq_Priv::mAssignLCNForFrance(HsvPgdatDigServiceData *psvcdat)
{
    Bool retval = FALSE;
    HsvPgdatDigServiceData svcdat_temp;
    HsvDestination dest = HsvMain;
    HSVSPTYPE(ActualNetworkHDSLCN, dvb, nit) nwhdslcn;
    HSVSPTYPE(ActualSRVCATRB, dvb, nit) nwsrvcattrb;
    HSVSPTYPE(ActualNetworkLCN, dvb, nit) nwlcn;
	HSVSPTYPE(FavoriteChannelListLCNV2, dvb, nit) lcnv2;

    if(mLCNParsingRequired((Nat16)psvcdat->OriginalNetworkId))
    {
        Bool HDSLCNPresent = FALSE, LCNv2Present = mLcnVersion2Data(psvcdat);
		retval = LCNv2Present;
        if(eurdiv_SupportHDSLCN(rins_GetMedium()) == TRUE)
        {
            if(strapi_GetByKey(dest, HSVSPID(ActualNetworkHDSLCN, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &nwhdslcn))
            {   
				if (eurdiv_IsZeroLCNHidden())
				{
					if ((VALID_LCN_RANGE(nwhdslcn.LogicalChannelNum) == TRUE) || (nwhdslcn.LogicalChannelNum == ZEROLCN))
					{
						psvcdat->LCN            = nwhdslcn.LogicalChannelNum;
					}
				}
				else
				{
					psvcdat->LCN            = (VALID_LCN_RANGE(nwhdslcn.LogicalChannelNum) == TRUE)? nwhdslcn.LogicalChannelNum: psvcdat->LCN;
				}
                psvcdat->VisibleService = nwhdslcn.VisibleService;
                retval = HDSLCNPresent = TRUE;
            }
        }       
        if(strapi_GetByKey(dest, HSVSPID(ActualNetworkLCN, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &nwlcn) == TRUE)
        {
        	
            if(HDSLCNPresent == FALSE)
            {
                if(LCNv2Present == FALSE)
                {
                	
					if (eurdiv_IsZeroLCNHidden())
					{
						if ((VALID_LCN_RANGE(nwlcn.LogicalChannelNum) == TRUE) || (nwlcn.LogicalChannelNum == ZEROLCN))
						{
							psvcdat->LCN            = nwlcn.LogicalChannelNum;
						}
					
					}
					else
					{
						psvcdat->LCN            = (VALID_LCN_RANGE(nwlcn.LogicalChannelNum) == TRUE)? nwlcn.LogicalChannelNum: psvcdat->LCN;
						
					}
                    psvcdat->VisibleService = nwlcn.VisibleService;
                    retval = TRUE;

					
                }
            }
            else
            {
			
                psvcdat->LowPrioLCN            = (VALID_LCN_RANGE(nwlcn.LogicalChannelNum) == TRUE)? nwlcn.LogicalChannelNum: psvcdat->LCN;
                psvcdat->LowPrioVisibleService =  nwlcn.VisibleService;
                retval = TRUE;
            }
        }
    }

    if(eurdiv_IsServiceAttrbDescSupported(rins_GetMedium()))
    {
        if(strapi_GetByKey(dest, HSVSPID(ActualSRVCATRB, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &nwsrvcattrb))
        {
            psvcdat->NumericSelect  = nwsrvcattrb.NumericSelect;
            psvcdat->VisibleService = nwsrvcattrb.VisibleService;
            retval = TRUE;
        }
    }

    if(psvcdat->LCN == ZEROLCN)
    {
        if (eurdiv_IsZeroLCNHidden())   /* brg36mgr# 95132 CR */
        {
            psvcdat->NumericSelect  = SRVCNOTSELECTABLE;
            psvcdat->VisibleService = SRVCNOTVISIBLE;
        }
        else
        {
            /* CR implementation. change lcn to invalid lcn so that its not hidden but
               treated as normal non honoured service */
            psvcdat->LCN            = INVALID_LCN;
            psvcdat->NumericSelect  = TRUE;
            psvcdat->VisibleService = TRUE;
        }
    }

    if(!retval)
    {
        svcdat_temp.OriginalNetworkId=psvcdat->OriginalNetworkId;
        svcdat_temp.ServiceId=psvcdat->ServiceId;
        svcdat_temp.Frequency=psvcdat->Frequency;
        svcdat_temp.StreamPriority=psvcdat->StreamPriority;

      /*  if(pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat_temp) == TRUE)
        {
            psvcdat->LCN            = svcdat_temp.LCN;
            psvcdat->VisibleService = svcdat_temp.VisibleService;
            psvcdat->NumericSelect  = svcdat_temp.NumericSelect;
            
            TraceDebug(m,"%s %d LCN %d <%d, %d, %d>\n", __FUNCTION__, __LINE__, psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId);
        }
       */ 
    }
	if(UPDATE_INSTALL||BACKGROUND_INSTALL||MANUAL_INSTALL)//Assign LCN based on userselected channelist in BCK and Manual installation
	{
		int UserSelectedFavChannelList=idvbset_GetAttribute(rins_InstallationModeUpdate, rins_AttributeFavoriteChannelId);
		TraceDebug(m,"PerstistentIndex=[%d]",UserSelectedFavChannelList);
		if(UserSelectedFavChannelList!=INVALID_CHANNELLIST_ID)
		{
		mAssignLCNforChannelList(UserSelectedFavChannelList,psvcdat);
		}
	}	
    TraceDebug(m,"%s %d LCN %d <%d, %d, %d> Visible %d", __FUNCTION__, __LINE__, psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId,psvcdat->VisibleService);
}



void CHsvDvbTInstallation_mDataAcq_Priv::mAddToCachedChannelListID()
{
	HsvDestination dest = HsvMain;
	HSVSPTYPE(FavoriteChannelListLCNV2, dvb, nit) lcnv2;
	int index,cachedChannelListIndex,k,from,to=0;
	Bool serviceexist=FALSE;       /*This variable tells the service in channelList alreay added in cached*/
	Bool ChannelListIdexist= FALSE;/*This variable tells the channelList Id alreay in cached*/
	HsvSDTSection sdtdata;
	int temp_channellist_count,temp_ChannellistService_Count=0;
	int NoofRecs = strapi_GetSize(HsvMain, HSVSPID(FavoriteChannelListLCNV2, dvb, nit));
	TraceDebug(m,"%s %d NoofRecs in FavoriteChannelListLCNV2 %d", __FUNCTION__, __LINE__, NoofRecs);
	if(strapi_GetRangeByKey(dest,HSVSPID(FavoriteChannelListLCNV2, dvb, nit),1 ,sysset_GetSystemCountry() ,0 ,0 , &from, &to) == TRUE)
	{
		TraceDebug(m,"%s %d from[%d]::to[%d]",__FUNCTION__, __LINE__,from,to);
		for(index=from;index<=to;index++)
		{
			if(strapi_GetByIndex(dest,HSVSPID(FavoriteChannelListLCNV2, dvb, nit),index,&lcnv2))
			{
				 if(strapi_GetByKey(dest,HSVSPID(ActualTSService, dvb, sdt), lcnv2.Original_NetworkId, lcnv2.ServiceId,lcnv2.Tsid, (Address)&sdtdata) ==TRUE)
				 {
					TraceDebug(m,"service present in SDT also so add in ChannelList");
					temp_channellist_count =ChannelListDataCache.TotalNumberofChannelListId;
					ChannelListIdexist=FALSE;
					if(ChannelListDataCache.TotalNumberofChannelListId>0)   //If cached channellist ID is >0
					{
						for(cachedChannelListIndex=0;cachedChannelListIndex<temp_channellist_count;cachedChannelListIndex++)
						{
							if(lcnv2.ChannelListId!=ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelId){//To detect whether channellist present
							}
							else{
							ChannelListIdexist=TRUE;
							TraceDebug(m,"channelId exist");
							}
						}
					}
					if(!ChannelListIdexist)//If channellist not exist add it in cache
					{
						ChannelListDataCache.CachedChannelList[ChannelListDataCache.TotalNumberofChannelListId].ChannelId=lcnv2.ChannelListId;					
						mCopyString(ChannelListDataCache.CachedChannelList[ChannelListDataCache.TotalNumberofChannelListId].ChannelListName,lcnv2.ChannelListName, (CHANNELLIST_NAME_LENGTH - 1));//TODO
						ChannelListDataCache.CachedChannelList[ChannelListDataCache.TotalNumberofChannelListId].NoOfServiceInChannelList=0;//To reset the no of service records
						ChannelListDataCache.TotalNumberofChannelListId++;					
						TraceDebug(m,"No of element in ChannelListDataCache=[%d]",ChannelListDataCache.TotalNumberofChannelListId);
					}
				 }
			}
		}
	}

	if(strapi_GetRangeByKey(dest,HSVSPID(FavoriteChannelListLCNV2, dvb, nit),1 ,sysset_GetSystemCountry() ,0 ,0 , &from, &to) == TRUE)//matching country id
	{
		TraceDebug(m,"%s %d from[%d]::to[%d]",__FUNCTION__, __LINE__,from,to);
		for(index=from;index<=to;index++)
		{
			TraceDebug(m,"index[%d]",index);
			if(strapi_GetByIndex(dest,HSVSPID(FavoriteChannelListLCNV2, dvb, nit),index,&lcnv2))
			{
				if(strapi_GetByKey(dest,HSVSPID(ActualTSService, dvb, sdt), lcnv2.Original_NetworkId, lcnv2.ServiceId,lcnv2.Tsid, (Address)&sdtdata) ==TRUE)
				{
					TraceDebug(m,"service present in SDT also so add in ChannelList");
					for(cachedChannelListIndex=0;cachedChannelListIndex<ChannelListDataCache.TotalNumberofChannelListId;cachedChannelListIndex++)
					{
						if(ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelId==lcnv2.ChannelListId)//To find matching channelList
						{
							temp_ChannellistService_Count=ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList;
							TraceDebug(m,"%s %d No of service in channellist[%d]=%d",__FUNCTION__, __LINE__,cachedChannelListIndex,temp_ChannellistService_Count);
							serviceexist=FALSE;
							if(ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList>0)
							{
								for(k=0;k<temp_ChannellistService_Count;k++)
								{
									if((lcnv2.ServiceId!=ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[k].ServiceId))
									{
									}
									else
									{
										if(lcnv2.Tsid==ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[k].Tsid)
										{
										serviceexist=TRUE;
										ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[k].ServiceId=lcnv2.ServiceId;//overwrite SID and LCN so that last LCN is allocated to same Service
										ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[k].LCN=lcnv2.LCN;
										ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[k].VisibiltyFlag=lcnv2.VisibleService;
										TraceDebug(m,"serviceexist exist");
										}
									}
								}
							}
							if(!serviceexist)
							{
							ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList].ServiceId=lcnv2.ServiceId;
							ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList].Original_NetworkId=lcnv2.Original_NetworkId;
							ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList].Tsid=lcnv2.Tsid;
							ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList].LCN=lcnv2.LCN;
							ChannelListDataCache.CachedChannelList[cachedChannelListIndex].ChannelID_services[ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList].VisibiltyFlag=lcnv2.VisibleService;
							ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList++;
							TraceDebug(m,"%s %d No of service in channellist[%d]=%d",__FUNCTION__, __LINE__,cachedChannelListIndex,ChannelListDataCache.CachedChannelList[cachedChannelListIndex].NoOfServiceInChannelList);
							TraceDebug(m,"SID %d visibilty=[%d]=",lcnv2.ServiceId,lcnv2.VisibleService);
							}	
						}
					}
				}
			}	
		}
	}
}	
					
void CHsvDvbTInstallation_mDataAcq_Priv::mAssignLCNforChannelList(int index,HsvPgdatDigServiceData *psvcdat)
{
/*This is generic function for all installation*/
	int noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
	HsvDestination dest = HsvMain;
	HsvPgdatDigServiceData svcdat,svcdat1;
	HSVSPTYPE(FavoriteChannelListLCNV2, dvb, nit) lcnv2,lcnv2temp;
	int from,to=0;	
	int retval=0;
	TraceDebug(m,"%s %d NoofRecs in SERVICE_TABLE %d", __FUNCTION__, __LINE__, noOfRecs);
	if(AUTO_INSTALL)
	{
	  	if(eurdiv_IsApmeaChannelListCountry()==TRUE)
	  	{
	  		for(int i=0;i<noOfRecs;i++)
	  		{
	  			if(pgdb_GetByIndex(SERVICE_TABLE,i,(Address)&svcdat))
				{
	  				svcdat.LCN=INVALID_LCN;
	  				int retval=pgdb_Update(SERVICE_TABLE,&svcdat);
	  			}
	  		}
	  		for(int i=0;i<noOfRecs;i++)
	  		{
	  			if(pgdb_GetByIndex(SERVICE_TABLE,i,(Address)&svcdat))
	  			{
	  				retval=FALSE;//For each service reset the flag so that if this is available in channelist or not .If not check low priority
	  				for(int srvindex=0;srvindex<ChannelListDataCache.CachedChannelList[index].NoOfServiceInChannelList;srvindex++)
	  				{
	  					if((svcdat.OriginalNetworkId==ChannelListDataCache.CachedChannelList[index].ChannelID_services[srvindex].Original_NetworkId)
	  						&&(svcdat.ServiceId==ChannelListDataCache.CachedChannelList[index].ChannelID_services[srvindex].ServiceId)
	  						&&(svcdat.Tsid==ChannelListDataCache.CachedChannelList[index].ChannelID_services[srvindex].Tsid))
	  					{
	  						svcdat.LCN=ChannelListDataCache.CachedChannelList[index].ChannelID_services[srvindex].LCN;//update LCN from cached
	  						svcdat.VisibleService=ChannelListDataCache.CachedChannelList[index].ChannelID_services[srvindex].VisibiltyFlag;
	  						pgdb_Update(SERVICE_TABLE,&svcdat);							
	  						TraceDebug(m,"%s %d svcdat.LCN=[%d] avd visiblity=[%d]", __FUNCTION__, __LINE__,svcdat.LCN,svcdat.VisibleService);
	  					}
	  				}				
	  			}
	  		}
	  	}
	}
		
	else if(UPDATE_INSTALL||BACKGROUND_INSTALL||MANUAL_INSTALL)
	{
		/*For Background and Manual/Update Installation */
		if((eurdiv_IsApmeaChannelListCountry()==TRUE) && (psvcdat != NULL))
		{
			lcnv2.ChannelListId=index;
			lcnv2.ServiceId=psvcdat->ServiceId;
			TraceDebug(m," UserInstalledChannelListId ,ONID and SID::<%d,%d,%d>",index,psvcdat->OriginalNetworkId,psvcdat->ServiceId);
			if(strapi_GetRangeByKey(dest,HSVSPID(FavoriteChannelListLCNV2, dvb, nit),3,sysset_GetSystemCountry(),
				lcnv2.ChannelListId,lcnv2.ServiceId,&from,&to))	
				{
					for(int cachedChannelListIndex = from; cachedChannelListIndex <= to; cachedChannelListIndex++)
					{
						if( (strapi_GetByIndex(dest,HSVSPID(FavoriteChannelListLCNV2, dvb, nit), cachedChannelListIndex, (Address)&lcnv2temp)==TRUE) )
						{
							if((lcnv2temp.Tsid==psvcdat->Tsid)&&(lcnv2temp.Original_NetworkId==psvcdat->OriginalNetworkId))
							{
								TraceDebug(m,"Update LCN =[%d] For ONID:SID:TSID=[%d],[%d],[%d] vis=[%d]",lcnv2temp.LCN,lcnv2temp.Original_NetworkId,lcnv2temp.ServiceId,lcnv2temp.Tsid,lcnv2temp.VisibleService);
								psvcdat->LCN=lcnv2temp.LCN;
								psvcdat->VisibleService=lcnv2temp.VisibleService;
							}
							else
							{
								psvcdat->LCN=INVALID_LCN;
							}
						}
					}
				}
			else /*ChanneList Delete usecase*/
			{					
				psvcdat->LCN=INVALID_LCN;

			}
		}
	}
}


void CHsvDvbTInstallation_mDataAcq_Priv::mAssignMultipleLCN(HsvPgdatDigServiceData *psvcdat)
{
	TraceNotice(m,"mAssignMultipleLCN: %s: %d", __FUNCTION__,__LINE__);

	HsvDestination dest = HsvMain;
	
	HSVSPTYPE(ActualSRVCATRB, dvb, nit) nwsrvcattrb;
	HSVSPTYPE(ActualNetworkLCN, dvb, nit) nwlcn;

	if(mLCNParsingRequired((Nat16)psvcdat->OriginalNetworkId))
    {
	    Bool LCNv2Present = mLcnVersion2Data(psvcdat);
		TraceNotice(m,"mAssignMultipleLCN: %s: %d: %d", __FUNCTION__,__LINE__,LCNv2Present);	
		if(strapi_GetByKey(dest, HSVSPID(ActualNetworkLCN, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &nwlcn) == TRUE)
		{
			TraceNotice(m,"mAssignMultipleLCN: %s: %d", __FUNCTION__,__LINE__);
			if(LCNv2Present == FALSE)
			{				
				Nat8 k =0;
				for(k=0;k<MAX_LCNS;k++)	
				{
					psvcdat->MultipleLCN[k] = nwlcn.LCN[k];

					TraceNotice(m,"mAssignMultipleLCN: %s: %d: k:%d LCN:%d", __FUNCTION__,__LINE__,k,psvcdat->MultipleLCN[k]);
					psvcdat->MultipleLCN[k] = ((psvcdat->MultipleLCN[k]==ZEROLCN)?(INVALID_ZERO_LCN):(psvcdat->MultipleLCN[k]));						
					if(psvcdat->MultipleLCN[k] == 0xFFFF)
					{
						psvcdat->MultipleLCN[k] = INVALID_LCN;
					}

					TraceNotice(m,"mAssignMultipleLCN: %s: %d: k:%d LCN:%d", __FUNCTION__,__LINE__,k,psvcdat->MultipleLCN[k]);
				}
				
				psvcdat->VisibleService = nwlcn.VisibleService;
			}
		}
	}

	if(eurdiv_IsServiceAttrbDescSupported(rins_GetMedium()))
	{
		if(strapi_GetByKey(dest, HSVSPID(ActualSRVCATRB, dvb, nit), psvcdat->OriginalNetworkId, psvcdat->Tsid, psvcdat->ServiceId, &nwsrvcattrb))
		{
			psvcdat->NumericSelect  = nwsrvcattrb.NumericSelect;
			psvcdat->VisibleService	= nwsrvcattrb.VisibleService;
		}
	}

	
	


}




/*HsvRiksTvOperator.c*/

void CHsvDvbTInstallation_mDataAcq_Priv::mStoreNetworkName(void)
{
    HsvDestination dest = HsvMain;
    int i = 0;
    Bool Found  = FALSE;

    if(AUTO_INSTALL)
    {
        for(i = 0; i < mNetworkIndex; i++)
        {
            if(NwIDCache[i].NetworkId == DigInsStatus.NetworkId)
            {
                Found = TRUE;
            }
        }

        if(!Found)
        {
            /* For NID & Network Name*/
            NwIDCache[mNetworkIndex].NetworkId = DigInsStatus.NetworkId;
            strapi_GetByKey(dest, HSVSPID(NetworkName, dvb, nit), 0, 0, 0, &NwIDCache[mNetworkIndex].NetworkName);
            mNetworkIndex++;
            mSortbyName(); 
        }
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::mSortbyName(void)
{
    int retval=0,i=0,j=0;
    TypeNwIDCache temp;

    for(i=0;i<mNetworkIndex;i++)
    {
        for(j=i+1;j<mNetworkIndex;j++)
        {
            retval = Unistrcmp(NwIDCache[i].NetworkName,NwIDCache[j].NetworkName);

            if(retval >0 )
            {
                //swap 
                temp = NwIDCache[i];
                NwIDCache[i] = NwIDCache[j];
                NwIDCache[j] = temp;

            }
        }
    }
}

int CHsvDvbTInstallation_mDataAcq_Priv::Unistrcmp(Nat16 *s1, Nat16 *s2)
{
    while((*s1 && *s2) && (*s1++ == *s2++))
        ;

    if(*(s1-1) == *(s2-1) )
    {
        if(*s1)
        {
            return 1;
        }       
    }
    return (*(--s1) - *(--s2));
}


void CHsvDvbTInstallation_mDataAcq_Priv::mRiksTvInitialise(void)
{
    int i=0, j=0;

    for(i=0; i<MAX_MUXES_PER_NTK; i++)
    {
        NwIDCache[i].NetworkId = -1;
        for(j=0; j<MAX_NETWORK_NAME_SIZE; j++)
        {
            NwIDCache[i].NetworkName[j] = 0;
        }
    }
    mNetworkIndex = 0;
}

void CHsvDvbTInstallation_mDataAcq_Priv::mRiksTvAcquireData(void)
{
    if(DigInsStatus.Onwid == sort_GetOriginalNetworkId(cids_CountryNorway))
    {
        mStoreNetworkName();
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetNetworkIDName(int index, Nat16 *NetworkName)
{
    if((index < mNetworkIndex) && (NetworkName != NULL))
    {
        memcpy(NetworkName, NwIDCache[index].NetworkName, (MAX_NETWORK_NAME_SIZE) + 2);
    }
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetChannelListIDName(int index, Nat16 *ChannelistName)
{

   TraceDebug(m,"ChannelListName[%d]=[%s]",index,ChannelListDataCache.CachedChannelList[index].ChannelListName);
	memcpy(ChannelistName, ChannelListDataCache.CachedChannelList[index].ChannelListName, (MAX_CHANNEL_LIST_NAME_SIZE) + 2);
}

int CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetNetworkIDList(void)
{
    return mNetworkIndex;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_SetFavouriteNetworkID(int mode, int attrib, int index)
{
    if(index < mNetworkIndex)
    {
        idvbset_SetAttribute(mode, attrib, NwIDCache[index].NetworkId);
    }   
}


void CHsvDvbTInstallation_mDataAcq_Priv::idvbtqctrlN_OnEvent(HsvDemux dmx, int eventid) 
{
	return;
}

 void CHsvDvbTInstallation_mDataAcq_Priv::digscanN_OnEvent(int event)
 {
 }
 
 int CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetNumberOfDigitalChannelsRemoved  (   void    )    
{
	return 0;
}

int CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetNumberOfChannels			    (   int servicetype ) 
{
	return 0;
}

int CHsvDvbTInstallation_mDataAcq_Priv::idataacq_GetNextSampleProgram               (   void    ) 
{
	return 0;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_AcquireLCNData                     (   void    ) 
{
	return;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_AcquireServiceListData             (   void    ) 
{
	return;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_StartBackgroundInstall             (   void    ) 
{
	return;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_ResetBackgroundInstall             (   void    ) 
{
	return;
}

Bool CHsvDvbTInstallation_mDataAcq_Priv::idataacq_IsNetworkUpdateDetected            (   void    ) 
{
	return FALSE;
}

/* 
void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_DeleteServices                     (   void    ) 
{
	return;
}
*/
void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_ClearNetworkNameCache(void) 
{
	return;
}

Bool CHsvDvbTInstallation_mDataAcq_Priv::idataacq_IsLCNValid() 
{
	return FALSE;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_AcquireONID() 
{
	return;
}
void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_Enable() 
{
	return;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_Disable() 
{
	return;
}

int CHsvDvbTInstallation_mDataAcq_Priv::mIdentifyHighPrioServiceIndex(int from, int to, Nat16 PrimaryRegion, Nat16 SecondaryRegion, Nat32 TertiaryRegion)
{
	HsvPgdatDigServiceData svcdat,svc2data;
	int index = 0,HighPrioServiceIndex = -1;
	Nat16  TempSvcPST = 0;
	Bool HighPrioServiceFound = FALSE;
    HsvPgdatDigTSData tsdata, ts2data;	
	int	HighestPrioriy =0,HighestPriorityInCurrentIteration =0; 

	/* Its quite possible that User has cancelled the TRD Selection. In this case, we do not have any reference
		to select closest region. So fallback directly to Best Mux Algorithm */
	if (IS_VALID_REGION(PrimaryRegion,SecondaryRegion,TertiaryRegion))
	{
		//TraceNotice (m, "TempPrint: PST Valid ");
		HighPrioServiceIndex = from;
		HighestPrioriy = 0;
		for (index = from ; (index <= to) ; index++ )
		{
			if(pgdb_GetByIndex(SERVICE_TABLE, index, (Address)&svcdat))
			{
				HighestPriorityInCurrentIteration = 0;
				if(VALID_PRIMARY_REGIONID(PrimaryRegion))
				{
					if ((svcdat.RegionDepth != INVALID_REGION_DEPTH) && (svcdat.RegionDepth >= 1) && (svcdat.PrimaryRegion == PrimaryRegion))
					{
						//TraceNotice (m, "Matching PRimary for index %d Onid %d Tsid %d SID %d Freq %d ", index, svcdat.OriginalNetworkId, svcdat.Tsid, svcdat.ServiceId, svcdat.Frequency);
						/* At least one mux have matching region. If none of them have any match, fallback to Best mux */
						HighPrioServiceFound = TRUE;
						HighestPriorityInCurrentIteration = PRIMARY_REGION_MATCH;
						if (VALID_SECONDARY_REGIONID(SecondaryRegion))
						{
							//TraceNotice (m, "Matching Secondary ");
							if ((svcdat.RegionDepth != INVALID_REGION_DEPTH) && (svcdat.RegionDepth >= 2) && (svcdat.SecondaryRegion == SecondaryRegion))
							{
								HighestPriorityInCurrentIteration |= SECONDARY_REGION_MATCH;
								
								if (VALID_TERTIARY_REGIONID(TertiaryRegion))
								{
									if ((svcdat.RegionDepth != INVALID_REGION_DEPTH) && (svcdat.RegionDepth >= 3) && (svcdat.TertiaryRegion == TertiaryRegion))
									{
										//TraceNotice (m, "Matching Tertiary ");
										HighestPriorityInCurrentIteration |= TERTIARY_REGION_MATCH;
									}
								}
							}
						}
						
						//TraceNotice (m, "Highprio %d highprioiniteration %d ", HighestPrioriy, HighestPriorityInCurrentIteration);
						/* Current Iteration is over. Check if its the highest priority */
						if (HighestPrioriy < HighestPriorityInCurrentIteration)
						{
							HighPrioServiceIndex = index;
							HighestPrioriy = HighestPriorityInCurrentIteration;
						}
					}
				}
			}
		}
	}
	
	TraceNotice (m, "UK: HighPrioFound %d HighPrio Service at index %d with priority %d ", HighPrioServiceFound, HighPrioServiceIndex, HighestPrioriy);
	
	/*Decide Based on Signal strength if could not decide based on target region descriptor*/
	if(HighPrioServiceFound = FALSE)
	{
		HighPrioServiceFound = TRUE;
		HighPrioServiceIndex = from;
		for(index = (from + 1); index <= to; index++)
		{

			pgdb_Initialise (pgdbconst_DigitalTS, &ts2data);
			pgdb_Initialise (pgdbconst_DigitalTS, &tsdata);
			
			if(pgdb_GetByIndex(SERVICE_TABLE, HighPrioServiceIndex, (Address)&svc2data))
			{
				ts2data.Frequency		= svc2data.Frequency;
				ts2data.StreamPriority	= svc2data.StreamPriority;
				
				if(pgdb_GetByKey(PTC_TABLE, (Address)&ts2data) == FALSE)
				{
					TraceErr(m,"%s: %d: GetbyKey FAILED",__FUNCTION__,__LINE__);
				}
			}
				
			if(pgdb_GetByIndex(TEMP_SERVICE_TABLE, index, (Address)&svcdat))
			{
				tsdata.Frequency		= svcdat.Frequency;
				tsdata.StreamPriority	= svcdat.StreamPriority;
				
				if(pgdb_GetByKey(TEMP_PTC_TABLE, /*index, */(Address)&tsdata))
				{
					TraceErr(m,"%s: %d: GetbyKey FAILED",__FUNCTION__,__LINE__);
				}				
			}

			if(mCompareTSSignal(ts2data,tsdata))
			{
				HighPrioServiceIndex = index;
			}
		}
	}
	
	//TraceNotice (m, "High Prio ServiceIndex %d ", HighPrioServiceIndex);
	return HighPrioServiceIndex;
}

int CHsvDvbTInstallation_mDataAcq_Priv::DeleteLowPrioServices(int from, int to, int HighPrioServiceIndex)
{
	int		RetVal = 0;
	HsvPgdatDigServiceData svcdat,svc;
    HsvPgdatDigTSData tsdata;
	int index = 0, /*from = 0, to = 0,*/ TSdataIndex = 0;
	Nat32 HighPrioMuxFreq = 0;
	Nat16 HighPrioMuxOnid = 0;
	Nat16 HighPrioMuxStreamPrio = 0;

	/*Delete low priority services */
	for(index = to; index >=from; index--)
	{
		if(index != HighPrioServiceIndex)
		{
			if(pgdb_GetByIndex(SERVICE_TABLE, index, (Address)&svcdat))
			{
				//TraceNotice (m, "Deleting Mux at index %d SID %d Freq %d ", index, svcdat.ServiceId, svcdat.Frequency);
				pgdb_Delete(SERVICE_TABLE,(Address)&svcdat);
				RetVal ++;
			}
		}
	}
	
	return RetVal;
}

void CHsvDvbTInstallation_mDataAcq_Priv::idataacq_DeleteServices (void)
{
    int indx = 0, from = 0, to = 0, noOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat, svcdat_temp;
    HsvPgdatDigTSData tsdat;
    HsvPgdatPresetData presetdat;
	int HighPrioServiceIndex = -1;
	Nat16 PrimaryRegion   = idvbset_GetAttribute(AUTO_MODE, rins_AttributePrimaryRegion);
    Nat16 SecondaryRegion = idvbset_GetAttribute(AUTO_MODE, rins_AttributeSecondaryRegion);
    Nat32 TertiaryRegion  = idvbset_GetAttribute(AUTO_MODE, rins_AttributeTertiaryRegion);

	TraceNotice (m, "UK: UserSelected Regions P %d S %d T %d ", PrimaryRegion, SecondaryRegion, TertiaryRegion);
	
	for(indx = 0; indx < noOfRecs; indx ++)
	{
		if( pgdb_GetByIndex(SERVICE_TABLE, indx, (Address)&svcdat) == TRUE )
		{
			
			pgdb_Initialise(pgdbconst_DigitalService, (Address)&svcdat_temp);		
			
			svcdat_temp.OriginalNetworkId	 =	 svcdat.OriginalNetworkId;
			svcdat_temp.ServiceId			 =	 svcdat.ServiceId;
			
			/* 2 below is no of keys */

			if(pgdb_GetRange(SERVICE_TABLE, 2,(Address)&svcdat_temp, &from, &to))
			{
				//TraceNotice (m, "GetRange returned From %d To %d  for ONID %d SID %d ", from, to, svcdat_temp.OriginalNetworkId, svcdat_temp.ServiceId);
				if((to >= 0) && (from >=0) && ((to-from) > 0))
				{
					/* More than 1 service present with same duplet. Check the high priority one and delete the other ones */
					HighPrioServiceIndex = mIdentifyHighPrioServiceIndex(from,to,PrimaryRegion,SecondaryRegion,TertiaryRegion);
					
					noOfRecs -= DeleteLowPrioServices(from, to, HighPrioServiceIndex);
					
					
					/* If current Service gets deleted then we need to adapt the indx and NoOfRecs */
					if (from == HighPrioServiceIndex)
					{
						indx--;
						TraceNotice (m, "UK: Deleted Mux current. Index %d NoOfRecs %d", indx, noOfRecs);
						
					}
					
					/* TODO: See how to delete entries from PTC_TABLE if all the services gets deleted due to Best Mux */
				}
				/* No need to take any action if above if condition fails. It simply means no duplicates are present */
			}
		}
	}
}

