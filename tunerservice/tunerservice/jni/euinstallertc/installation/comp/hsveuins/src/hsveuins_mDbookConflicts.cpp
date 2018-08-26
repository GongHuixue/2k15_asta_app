/*
 *  Copyright(C) 2009 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *  %name: hsveuins_mDbookConflicts.c %
 *  %version: TVG_Fusion_2 %
 *  %date_modified: Mon Apr 06 16:38:28 2010 %
 *  %derived_by: nareshj %
 */


#include "_hsveuins_mDbookConflicts.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mDbookConflicts")























                                                         
                                                         
                                                         
                                                         
                                                         
                                                         
                                                         
                                                         
                                                         
                                                         
                                                         
                                                         
                                                         

                                                         

int CHsvEuropeInstallation_mDbookConflicts_Priv::s__mServicePriority[MAX_SERVICE_TYPES] =
{
    /* Priority is in increasing order. Refer to honouring rules sheet of vsd  */
    AppApiDatabroadcastService,
    AppApiTeletextService,
    AppApiRadioService,
    AppApiTelevisionService,
    AppApiMPEG2HDService,
    AppApiAdvCodecSDTelevisionService,
    AppApiAdvCodecHDTelevisionService   
};



/* PST below will have values as below
 *  =============
 *  |Country: UK|
 *  |P    S    T|
 *  |===========|
 *  |0    0    0|       => REGION_NONE
 *  |1    0    0|       => REGION_PRIMARY
 *  |1    1    0|       => REGION_SECONDARY
 *  |1    1    1|       => REGION_TERTIARY
 *  =============
 */


int CHsvEuropeInstallation_mDbookConflicts_Priv::s__RegionCachePoolId = -1;

Pump CHsvEuropeInstallation_mDbookConflicts_Priv::s__mDbookConflictsPmp;

HsvDbookConflictsData CHsvEuropeInstallation_mDbookConflicts_Priv::s__mConflictList[ MAX_SERVICES ];

int CHsvEuropeInstallation_mDbookConflicts_Priv::s__TOTAL_NUM_OF_CONFLICTS = 0,CHsvEuropeInstallation_mDbookConflicts_Priv::s__mConflictResolutionPass;


void CHsvEuropeInstallation_mDbookConflicts_Priv::idbookconpow_Init()
{
    mDbookConflictsPmp = pmp_PmpCreateEx( pen_PumpEngine, mDvbTConflictsHandler, FALSE, "hsveuins_mDvbTConflicts" );
    mConflictResolutionPass   = NO_PASS;
}
void CHsvEuropeInstallation_mDbookConflicts_Priv::idbookconpow_TurnOn()
{ }
void CHsvEuropeInstallation_mDbookConflicts_Priv::idbookconpow_TurnOff()
{ }

/** trigger to the conflict resolution from the sorting module mDvbTSort.c  **/
void CHsvEuropeInstallation_mDbookConflicts_Priv::idbookconf_ResolveConflicts(int ConflictPass)
{
    TraceDebug(m,"%s: CURRENT PASS = %d", __FUNCTION__, ConflictPass);
    pmp_PmpSend( mDbookConflictsPmp, evStep1, (Nat32)ConflictPass );
}

void CHsvEuropeInstallation_mDbookConflicts_Priv::mPopulateListOfConflicts(int evCurrentSortStep)
{
    HsvPgdatPresetData presetdat;
    HsvPgdatDigServiceData svcdat1, svcdat2;
    int i, j, NoOfRecs  = pgdb_GetNoRecords( SERVICE_TABLE ), ServiceInfoIndex = 0, FirstConflictIndex = -1;

    mNumOfLCNsInConflict = 0;
    for(i = 0; i < NoOfRecs; i++)
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat1) == TRUE)
        {
            if( ( PRESET_NOT_ALLOCATED(svcdat1)||(mConflictResolutionPass != FIRST_PASS)) && VALID_LCN_RANGE(GET_LCN(svcdat1)) )
            {
                ServiceInfoIndex = 0, FirstConflictIndex = -1;

                if(mConflictResolutionPass == FIRST_PASS)
                {
                    presetdat.PresetNumber = GET_LCN(svcdat1);
                    if(pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat) == TRUE)
                    {
                        if(DIGITAL_PRESET(presetdat))
                        {
                            ASSIGN_SVC_FROM_PRESET(svcdat2,presetdat);
                            if((pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat2) == TRUE)&&(VALID_LCN_RANGE(GET_LCN(svcdat2))) )
                            {
                                pgdb_GetIndex(SERVICE_TABLE, &FirstConflictIndex, (Address)&svcdat2);
                                TraceDebug(m,"%s %d NoOfRecs %d LCN %d FirstConflictIndex %d OriginalNetworkId %d Tsid %d ServiceId %d Frequency %d StreamPriority %d", __FUNCTION__, __LINE__, NoOfRecs, GET_LCN(svcdat2), FirstConflictIndex, svcdat2.OriginalNetworkId, svcdat2.Tsid, svcdat2.ServiceId, svcdat2.Frequency, svcdat2.StreamPriority);
                                if(mIsPresentInConflictList(svcdat2) == FALSE)
                                {
                                    mCopyDataToList((HsvPgdatDigServiceData *) (&svcdat2), ServiceInfoIndex, GET_LCN(svcdat1));
                                    ServiceInfoIndex++;
                                }
                            }
                        }
                        TraceNotice(m,"%s %d Preset deleted %d", __FUNCTION__, __LINE__, presetdat.PresetNumber);
                    }
                }

                /* Now for rest of the records in ServiceTable */
                for( j = 0; j < NoOfRecs; j++)
                {
                    if(pgdb_GetByIndex(SERVICE_TABLE, j, (Address)&svcdat2) == TRUE)
                    {
                        /* first 2 checks are to prevent duplicate records in conflict list */
                        if( (GET_LCN(svcdat2) == GET_LCN(svcdat1)) && (j != FirstConflictIndex))
                        {
                            if(mIsPresentInConflictList(svcdat2) == FALSE)
                            {
                                mCopyDataToList((HsvPgdatDigServiceData *) (&svcdat2), ServiceInfoIndex, GET_LCN(svcdat1));
                                ServiceInfoIndex++;
                            }   
                        }
                    }       
                }

                if(ServiceInfoIndex > 0)
                {
                    /* means atleast one service is added to the comnflict list hence increment for next entry */
                    TOTAL_NUM_OF_CONFLICTS++;
                }
            }
        }
    }

    TraceNotice(m,"TOTAL_NUM_OF_CONFLICTS %d", TOTAL_NUM_OF_CONFLICTS);

    TraceDebug(m,"Pmp send done with event = %d", (evCurrentSortStep + 1));
    pmp_PmpSend( mDbookConflictsPmp, ( evCurrentSortStep + 1 ), ( Nat32 )NULL );
}

void CHsvEuropeInstallation_mDbookConflicts_Priv::mResolveConflicts(int evCurrentSortStep)
{
    mAssignPriorityForServices();
    mSelectPriorityService();

    TraceDebug(m,"Pmp send done with event = %d", (evCurrentSortStep + 1));
    pmp_PmpSend(mDbookConflictsPmp, (evCurrentSortStep + 1), (Nat32)NULL);
}

void CHsvEuropeInstallation_mDbookConflicts_Priv::mAssignPriorityForServices(void)
{
    int i = 0, j = 0, dist = 0, index;
    Bool ReachedUK = FALSE;
    Nat8  UserPST = 0;
    Nat16 PrimaryRegion = 0, SecondaryRegion = 0;
    int TertiaryRegion; 
    HsvPgdatDigServiceData svcdat;

    
    for(i = 0; i < TOTAL_NUM_OF_CONFLICTS; i++)
    {
        for(j = 0; j < mConflictList[i].NoOfServices; j++)
        {

            if(pgdb_GetByIndex(SERVICE_TABLE, CONFLICT_SERVICE_DBINDEX(i, j), (Address)&svcdat))
            {

                if(PRIORITY_NOT_ASSIGNED(mConflictList[i].ServiceInfo[j].Priority) && (svcdat.CountryCode == cids_CountryUK))
                {
                    ReachedUK = FALSE;
                    mGetUserPSTSettings(&PrimaryRegion, &SecondaryRegion, (Nat32 *)(&TertiaryRegion), &UserPST);
                    dist = CALCULATE_DISTANCE(UserPST);

                    index = UserPST;

                    while(dist > 1)
                    {

                        if(ReachedUK == FALSE)
                        {

                            if( SAME_RANK(index, mConflictList[i].ServiceInfo[j].ServicePST) )
                            {

                                if( SAME_REGION_CODE_B4UK(index))
                                {

                                    mConflictList[i].ServiceInfo[j].Priority = dist;
                                    break;
                                }
                            }
                        }
                        else
                        {

                            if(SAME_REGION_CODE_AFTERUK(UserPST, index))
                            {
                                mConflictList[i].ServiceInfo[j].Priority = dist;
                                break;
                            }
                        }

                        index = (((index << 1) & 0x7) == 0) ? 0 : ((index << 1) & 0x7);

                        dist--;

                        if(index == 0)
                        {

                            ReachedUK = TRUE;
                            /* All cases have 3 priority levels after reaching UK.
                               So to assign distances force UserPST value to 0x7 */
                            index = 0x7;

                            /* handling the UK level case*/
                            if(mConflictList[i].ServiceInfo[j].ServicePST == 0x0)
                            {
                                mConflictList[i].ServiceInfo[j].Priority = dist;
                                break;
                            }
                        }
                    }

                    if(dist == 1)
                    {
                        /* boundary condition. All priorities completed */
                        mConflictList[i].ServiceInfo[j].Priority = dist;
                    }
                }
            }
        }
    }
}

void CHsvEuropeInstallation_mDbookConflicts_Priv::mSelectPriorityService(void)
{
    int i = 0, j = 0, PrefServiceIndex = 0, NoOfHighestPriorityRecords, HighestPriority = 0;

    for(i = 0; i < TOTAL_NUM_OF_CONFLICTS; i++)
    {
        PrefServiceIndex = NoOfHighestPriorityRecords = 0;
        /* calculate highest priority in this conflict */
        HighestPriority = mConflictList[i].ServiceInfo[0].Priority;
        for(j = 1; j < mConflictList[i].NoOfServices; j++)
        {
            if(HighestPriority < mConflictList[i].ServiceInfo[j].Priority)
            {
                HighestPriority = mConflictList[i].ServiceInfo[j].Priority;
                PrefServiceIndex = j;
            }
        }       
        /* check for multiple records with highest priority */
        for(j = 0; j < mConflictList[i].NoOfServices; j++)
        {
            if(mConflictList[i].ServiceInfo[j].Priority == HighestPriority)
            {
                NoOfHighestPriorityRecords++;
            }
        }
        TraceDebug(m,"%s %d LCN %d HighestPriority %d NoOfHighestPriorityRecords %d PrefServiceIndex %d", __FUNCTION__, __LINE__, mConflictList[i].LCN, HighestPriority, NoOfHighestPriorityRecords, PrefServiceIndex);
        /* more no. of services with same highest priority, Now apply old dvbt rules, ServicePriority & signal Strength 
           to select the right one */
        if(NoOfHighestPriorityRecords > 1)
        {
            PrefServiceIndex = 0;
            for(j = 1; j < mConflictList[i].NoOfServices; j++)
            {
                if(mConflictList[i].ServiceInfo[j].Priority == HighestPriority)
                {
                    if(mDBookCompareServices(i, j, PrefServiceIndex) < 0)
                    {
                        PrefServiceIndex = j;
                    }
                }
            }
        }
        mUpdateConflictPresets(CONFLICT_SERVICE_DBINDEX(i, PrefServiceIndex));
		mInvalidateLessPrioHDLCNServices (i, PrefServiceIndex);
        mConflictList[i].Resolved = TRUE;
    }
}

void CHsvEuropeInstallation_mDbookConflicts_Priv::mInvalidateLessPrioHDLCNServices (int i, int PrefServiceIndex)
{
	int j =0,DbIndex = 0, MaxIndex = pgdb_GetNoRecords(SERVICE_TABLE) - 1;
	HsvPgdatDigServiceData svcdat;
	HsvPgdatPresetData presetdat;
	
	if(mConflictResolutionPass != FIRST_PASS)
	{
		for(j = 0; j < mConflictList[i].NoOfServices; j++)
		{
			/*  There can be cases in which one of the conflicting HD LCN preset is allocated with PresetNumber. But this index fails in Conflict resolution
				In previous steps invalidation of HD LCN is not done. But the service which exist in Preset is not cleared at all.
				This will create problems when there is HD and SD Swapping. We may end up with swapping between HD services itself
				Issue seen in [TF515PHIALLMTK01-16412] Pre FreeviewHD_SI_si06_004::HD Simulcast Logical Channel descriptor (Multiple SIP) */
			if (j != PrefServiceIndex) /* Dont needs to check for preferred index */
			{
				DbIndex = CONFLICT_SERVICE_DBINDEX(i, j);
				if (VALID_SERVICE_INDEX(DbIndex,MaxIndex))
				{
					if(pgdb_GetByIndex(SERVICE_TABLE, DbIndex, (Address)&svcdat) == TRUE)
					{
						TraceNotice (m, "PresetNumber for conflicting service %d: LCN %d Onid %d SID %d  ", svcdat.PresetNumber, mConflictList[i].LCN, svcdat.OriginalNetworkId, svcdat.ServiceId);
						/* Check if the preset is still occupied and if it matches with current conflicting HDLCN */
						if ((svcdat.PresetNumber != INVALID_PRESET) && (svcdat.PresetNumber == mConflictList[i].LCN))
						{
							presetdat.PresetNumber = svcdat.PresetNumber;
							if(pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat) == TRUE)
							{
								if(DIGITAL_PRESET(presetdat))
								{
									/* Just to avoid any problem, making sure the its the same preset */
									if ((svcdat.OriginalNetworkId == presetdat.OriginalNetworkId) &&
										(svcdat.ServiceId == presetdat.ServiceId) &&
										(svcdat.Frequency == presetdat.Frequency) &&
										(svcdat.StreamPriority == presetdat.StreamPriority))
									{
										pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
										svcdat.PresetNumber = INVALID_PRESET;
										pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
										TraceNotice(m,"%s %d Preset deleted %d", __FUNCTION__, __LINE__, presetdat.PresetNumber);
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

inline int CHsvEuropeInstallation_mDbookConflicts_Priv::mDBookCompareServices(int LCNConflictIndex, int ServiceIndex, int PrefServiceIndex)
{
    int retval = 0;
    HsvPgdatDigServiceData svcdat, Prefsvcdat;
    HsvPgdatDigTSData tsdata, Preftsdata;

    pgdb_GetByIndex(SERVICE_TABLE, CONFLICT_SERVICE_DBINDEX(LCNConflictIndex, ServiceIndex), (Address)&svcdat);
    pgdb_GetByIndex(SERVICE_TABLE, CONFLICT_SERVICE_DBINDEX(LCNConflictIndex, PrefServiceIndex), (Address)&Prefsvcdat);

    retval = mGetServicePriority(Prefsvcdat.ServiceType) - mGetServicePriority(svcdat.ServiceType);

    if(retval == 0)
    {
        tsdata.Frequency      = svcdat.Frequency;      Preftsdata.Frequency      = Prefsvcdat.Frequency;
        tsdata.StreamPriority = svcdat.StreamPriority; Preftsdata.StreamPriority = Prefsvcdat.StreamPriority;;      
        if(pgdb_GetByKey(PTC_TABLE, (Address)&tsdata) && pgdb_GetByKey(PTC_TABLE, (Address)&Preftsdata))
        {
            retval = Preftsdata.ASignalStrength - tsdata.ASignalStrength;
        }
    }
    TraceDebug(m,"svcdat1 <%d %d> svcdat2 <%d %d> => %d", svcdat.Frequency, svcdat.ServiceId, Prefsvcdat.Frequency, Prefsvcdat.ServiceId, retval);
    return retval;  
}

int CHsvEuropeInstallation_mDbookConflicts_Priv::mGetServicePriority(int serviceType)
{
    int i = 0, retval = 1;
    Bool found = FALSE;

    for(i = 0; i < MAX_SERVICE_TYPES; i++)
    {
        if(serviceType == mServicePriority[i])
        {
            found = TRUE;
            break;
        }
    }

    /* In case we dont find anything, just fallback to previous case */
    retval = (TRUE == found) ? i: mConvertToDVBServiceType(serviceType);

    return retval;
}

void CHsvEuropeInstallation_mDbookConflicts_Priv::InitConflictList(void)
{
    int i =0;

    for(i=0;i<MAX_SERVICES;i++)
    {
        mConflictList[i].NoOfServices = 0;
    }

}

void CHsvEuropeInstallation_mDbookConflicts_Priv::mDvbTConflictsHandler(int value, Nat32 param)
{
    TraceDebug(m,"%s: CURRENT STEP = %d",__FUNCTION__, value);

    switch(value)
    {
        case evStep1:
            /**  This is the first step towards the conflict resolution - check for presence of region priorities and then assign them **/
            TraceDebug(m,"%s %d mConflictResolutionPass %d", __FUNCTION__, __LINE__, mConflictResolutionPass);
            InitConflictList();
            mConflictResolutionPass = param;
            mPopulateListOfConflicts(value);
            break;
        case evStep2:
            TraceDebug(m,"%s %d mConflictResolutionPass %d", __FUNCTION__, __LINE__, mConflictResolutionPass);
            mResolveConflicts(value);
            break;
        case evStep3:
            /** This is the last step in conflicts handling. Notification back to sorting module to continue with next steps **/
            TraceDebug(m,"%s %d Conflict Resolution of pass %d Complete", __FUNCTION__, __LINE__, mConflictResolutionPass);
            idbookconfN_OnEvent( param );
            break;
        default:
            ASSERT(!"Unknown Step in sorting");
            break;
    }

}

void CHsvEuropeInstallation_mDbookConflicts_Priv::mCopyDataToList(HsvPgdatDigServiceData *svcdat, int ServiceInfoIndex, int ConflictLCN)
{
    if(ServiceInfoIndex < MAX_CONFLICT_SERVICES)
    {
        /* LCN */
        CONFLICT_LCN(TOTAL_NUM_OF_CONFLICTS) = ConflictLCN;

        /* DbIndex of the Service */
        pgdb_GetIndex(SERVICE_TABLE, &(CONFLICT_SERVICE_DBINDEX(TOTAL_NUM_OF_CONFLICTS, ServiceInfoIndex)), (Address)svcdat);

        /* initialize priority */
        mConflictList[TOTAL_NUM_OF_CONFLICTS].ServiceInfo[ServiceInfoIndex].Priority = 0;

        /* service PST */
        mConflictList[TOTAL_NUM_OF_CONFLICTS].ServiceInfo[ServiceInfoIndex].ServicePST = MASK_REGION_TYPES(svcdat->PrimaryRegion, svcdat->SecondaryRegion, svcdat->TertiaryRegion);

        mConflictList[TOTAL_NUM_OF_CONFLICTS].Resolved = FALSE;
        TraceNotice(m,"%s %d mConflictList[%d].LCN %d mConflictList[%d].NoOfServices %d ServicePST %d", __FUNCTION__, __LINE__, TOTAL_NUM_OF_CONFLICTS, CONFLICT_LCN(TOTAL_NUM_OF_CONFLICTS), TOTAL_NUM_OF_CONFLICTS, mConflictList[TOTAL_NUM_OF_CONFLICTS].NoOfServices,mConflictList[TOTAL_NUM_OF_CONFLICTS].ServiceInfo[ServiceInfoIndex].ServicePST);

        /* First invalidate all the LCNs and then only validate the priority selected servivce, 
           This ensures the LCN of priority service is honoured and all others are treated as Non-Honoured services */
        if(mConflictResolutionPass == FIRST_PASS)
        {
            INVALIDATE(svcdat->LCN);
        }
        else
        {
            INVALIDATE(svcdat->LowPrioLCN);
        }
        pgdb_Update(SERVICE_TABLE, (Address)svcdat);

        mConflictList[TOTAL_NUM_OF_CONFLICTS].NoOfServices++;
    }
    else
    {
        TraceNotice(m,"Danger: Conflict services exceeding MAX limit");
    }
}

inline Bool CHsvEuropeInstallation_mDbookConflicts_Priv::mIsPresentInConflictList(HsvPgdatDigServiceData svcdat)
{
    int i = 0,j =0,ConflictIndex = -1;
    Bool retval = FALSE;

    for( i = 0; i < TOTAL_NUM_OF_CONFLICTS; i++)
    {
        if(GET_LCN(svcdat) == CONFLICT_LCN(i) )
        {
            pgdb_GetIndex(SERVICE_TABLE, &ConflictIndex, (Address)&svcdat);
            for(j =0;j<mConflictList[i].NoOfServices;j++)
            {
                if(mConflictList[i].ServiceInfo[j].DbIndex == ConflictIndex)
                {
                    retval = TRUE;
                    break;
                }
            }
        }
    }
    TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}

inline void CHsvEuropeInstallation_mDbookConflicts_Priv::mGetUserPSTSettings(Nat16 *PrimaryRegion, Nat16 *SecondaryRegion, Nat32 *TertiaryRegion, Nat8 *UserPST)
{
    *PrimaryRegion   = hsvdvbtins_dvbset_GetAttribute(AUTO_MODE, rins_AttributePrimaryRegion);
    *SecondaryRegion = hsvdvbtins_dvbset_GetAttribute(AUTO_MODE, rins_AttributeSecondaryRegion);
    *TertiaryRegion  = hsvdvbtins_dvbset_GetAttribute(AUTO_MODE, rins_AttributeTertiaryRegion);
    *UserPST         = MASK_REGION_TYPES(*PrimaryRegion, *SecondaryRegion, *TertiaryRegion);

    TraceNotice(m,"%s %d User selected %s regions P = %d S = %d T = %ld ", __FUNCTION__, __LINE__, (*UserPST == 0)?"none":((*UserPST == 4)?"primary": \
                (*UserPST == 6)?"primary and secondary": ((*UserPST == 6)?"primary and secondary and tertiary" : "invalid option")), *PrimaryRegion, *SecondaryRegion, *TertiaryRegion);
}

void CHsvEuropeInstallation_mDbookConflicts_Priv::mUpdateConflictPresets(int PrefDbIndex)
{
    HsvPgdatDigServiceData svcdat, oldsvcdat;
    HsvPgdatPresetData presetdat;
    int DbIndex = 0, MaxIndex = pgdb_GetNoRecords(SERVICE_TABLE) - 1;

    if( VALID_SERVICE_INDEX(PrefDbIndex, MaxIndex) )
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, PrefDbIndex, (Address)&svcdat) == TRUE)
        {
            /* priority service, hence honouring the LCN of it */

            if(mConflictResolutionPass == FIRST_PASS)
            {   
                REVALIDATE(svcdat.LCN);
            }
            else
            {
                REVALIDATE(svcdat.LowPrioLCN);
            }
            pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
        }

        /* Also delete the first allocated LCN preset of this conflict(for sure there should be a preset allocated before) */
        if(mConflictResolutionPass == FIRST_PASS)
        {
            presetdat.PresetNumber = GET_LCN(svcdat);
            if(pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat) == TRUE)
            {
                if(DIGITAL_PRESET(presetdat))
                {
                    ASSIGN_SVC_FROM_PRESET(oldsvcdat,presetdat);
                    if(pgdb_GetByKey(SERVICE_TABLE, (Address)&oldsvcdat) == TRUE)
                    {
                        pgdb_GetIndex(SERVICE_TABLE, &DbIndex, (Address)&oldsvcdat);
                        if(PrefDbIndex != DbIndex)
                        {
                            pgdb_Delete(PRESET_TABLE,(Address)&presetdat);

                            if(mConflictResolutionPass == FIRST_PASS)
                            {   
                                INVALIDATE(oldsvcdat.LCN);
                            }
                            else
                            {

                                INVALIDATE(oldsvcdat.LowPrioLCN);
                            }
                            oldsvcdat.PresetNumber = INVALID_PRESET;

                            pgdb_Update(SERVICE_TABLE, (Address)&oldsvcdat);

                            TraceNotice(m,"%s %d Preset deleted %d", __FUNCTION__, __LINE__, presetdat.PresetNumber);
                        }
                        else
                        {
                            TraceDebug(m,"%s %d selected service is same as currently honoured one", __FUNCTION__, __LINE__);
                        }
                    }
                }
            }
        }
    }
    else
    {
        TraceDebug(m,"%s::%d Invalid database index",__FUNCTION__, __LINE__);
    }
}

int CHsvEuropeInstallation_mDbookConflicts_Priv::mConvertToDVBServiceType(int servicetype)
{
    int retval = servicetype;
    switch(servicetype)
    {
        case AppApiTelevisionService:     
            retval  =   TV_SERVICE;
            break;
        case AppApiRadioService:        
            retval  =   RADIO_SERVICE;
            break;
        case AppApiTeletextService:         
            retval  =   TELETEXT_SERVICE;
            break;
        case AppApiNVODReferenceService:         
            retval  =   NVOD_REFERENCE_SERVICE;
            break;
        case AppApiNVODTimeshiftedService:         
            retval  =   NVOD_TIMESHIFTED_SERVICE;
            break;
        case AppApiMosaicService:        
            retval  =   MOSAIC_SERVICE;
            break;
        case AppApiDatabroadcastService:        
            retval  =   DATABROADCAST_SERVICE;
            break;
        case AppApiDVBMHPService:        
            retval  =   DVBMHP_SERVICE;
            break;
        case AppApiMPEG2HDService:        
            retval  =   MPEG2HDService;
            break;
        case AppApiAdvCodecSDTelevisionService:        
            retval  =   AdvCodecSDTelevisionService;
            break;
        case AppApiAdvCodecSDNVODTimeShiftedService:        
            retval  =   AdvCodecSDNVODTimeShiftedService;
            break;
        case AppApiAdvCodecSDNVODReferenceService:        
            retval  =   AdvCodecSDNVODReferenceService;
            break;
        case AppApiAdvCodecHDTelevisionService:        
            retval  =   AdvCodecHDTelevisionService;
            break;
        case AppApiAdvCodecHDNVODTimeShiftedService:        
            retval  =   AdvCodecHDNVODTimeShiftedService;
            break;
        case AppApiAdvCodecHDNVODReferenceService:        
            retval  =   AdvCodecHDNVODReferenceService;
            break;      
        default:
            break;        
    }
    return retval;
}

/**************************************************************************************************************************/

/************************** MULTIPLE TARGET REGION DESCRIPTOR SPECIFIC MACROS BEGIN ***************************************/

/**************************************************************************************************************************/

















void CHsvEuropeInstallation_mDbookConflicts_Priv::idbookconf_AssignRegionAttributesForService ()
{
	int i = 0, j = 0, idx = 0, dist = 0, TertiaryRegion;
	Bool ReachedUK = FALSE;
	Nat8  UserPST = 0, index = 0, TempSvcPST = 0;
    Nat16 PrimaryRegion = 0, SecondaryRegion = 0;
    HsvPgdatDigServiceData svcdat;

    int BufferPoolSize = ( MAX_NUMBER_SERVICES * sizeof(HsvTargetRegionCache) ), NoOfRecords = pgdb_GetNoRecords( SERVICE_TABLE );

    HsvTargetRegionCache * mRegionCache = NULL;
    if ( RegionCachePoolId == -1 )
    {
        RegionCachePoolId = hpool_Create( hpool_MemLocalNoFatal, ( BufferPoolSize + BUFFER_ADMIN_MEM ),"TargetRegion Cache pool");
    }

    if( ( RegionCachePoolId != -1) && ( !mRegionCache ) )
    {
        mRegionCache = (HsvTargetRegionCache *)hpool_Malloc( RegionCachePoolId, BufferPoolSize );
    }

	TraceNotice(m,"RegionCache %x and PoolId %d ", mRegionCache, RegionCachePoolId);
    if ( ( mRegionCache) && ( RegionCachePoolId != -1 ) )
    {
        hsvdvbtins_digacq_GetCachedRegionDetails(mRegionCache);

        mGetUserPSTSettings(&PrimaryRegion, &SecondaryRegion, (Nat32 *)(&TertiaryRegion), &UserPST);
        // assign the priority triplet per service with the priority calculation algo : based on this, we add this to channel lib, and proceed as how we used to, 
        // for LCN conflict, sorting. 

        for (i = 0; ( ( i < MAX_NUMBER_SERVICES ) && ( (mRegionCache[i].OnId != 0xFFFF) && (mRegionCache[i].Tsid != 0xFFFF) && (mRegionCache[i].ServiceId != 0xFFFF) ) ) ; i++)
        {
            Nat8 Priority[ MAX_REGIONS_PER_SERVICE ] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;

            if (mRegionCache[i].CountryCode == cids_CountryUK)
            {
                for (j = 0; j < MAX_REGIONS_PER_SERVICE; j++)
                {   
						
					if( mRegionCache[i].RegionList.RegionMap[j][MULT_REGION_DEPTH_INDEX] != INVALID_REGION_DEPTH )
					{
						index = UserPST;
						// MASK_REGION_CODE ( mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX], mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX], mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX], mRegionCache[i].RegionList.RegionMap[j][MULT_REGION_DEPTH_INDEX] );

						TempSvcPST = MASK_REGION_TYPES (mRegionCache[i].RegionList.RegionMap[j][MULT_PRIMARY_INDEX], mRegionCache[i].RegionList.RegionMap[j][MULT_SECONDARY_INDEX], mRegionCache[i].RegionList.RegionMap[j][MULT_TERTIARY_INDEX]);

						ReachedUK = FALSE;
						dist = CALCULATE_DISTANCE(UserPST);
						//PrintfNotice (" Lithesh : %d %s P = %d S = %d T = %d SvcId = %d Onid = %d Tsid = %d  \n", __LINE__, __FUNCTION__, mRegionCache[i].RegionList.RegionMap[j][1], mRegionCache[i].RegionList.RegionMap[j][2], mRegionCache[i].RegionList.RegionMap[j][3], mRegionCache[i].ServiceId, mRegionCache[i].OnId, mRegionCache[i].Tsid);
						while(dist >= 1)
						{
							if(ReachedUK == FALSE)
							{
					
								if( SAME_RANK(index, TempSvcPST ) )
								{
									if( MULT_SAME_REGION_CODE_B4UK(index))
									{
								
                                    TraceNotice(m,"%d %s dist = %d ", __LINE__, __FUNCTION__, dist);
										Priority[ j ] = dist;
										break;
									}
								}
							}
							else
							{
								if(MULT_SAME_REGION_CODE_AFTERUK(UserPST, index))
								{
									//PrintfNotice("%d %s  dist = %d \n", __LINE__, __FUNCTION__, dist);
									Priority [ j ]= dist;
									break;
								}
							}
							
							index = (((index << 1) & 0x7) == 0) ? 0 : ((index << 1) & 0x7);
							
							dist--;
							
							if(index == 0)
							{
								//PrintfNotice("%d %s  dist = %d \n", __LINE__, __FUNCTION__, dist);
								
								ReachedUK = TRUE;
								/* All cases have 3 priority levels after reaching UK.
								So to assign distances force UserPST value to 0x7 */
								index = 0x7;
								
								/* handling the UK level case*/
								if(TempSvcPST == 0x0)
								{
									//PrintfNotice("%d %s  dist = %d \n", __LINE__, __FUNCTION__, dist);
									Priority[ j ] = dist;
									break;
								}

								if(dist == 1)
								{
									/* boundary condition. All priorities completed */
									//PrintfNotice("%d %s dist = %d \n", __LINE__, __FUNCTION__, dist);

									Priority[ j ] = dist;
									break;
								}
							}
						}
					}
					else
					{
						Priority[ j ] = 0;
					}
				}
			}

			// this is when each TRD per service gets a priority - now based on which is highest, we update channel lib here. 

			// implement the logic of assigning only one to channel lib and popping the rest out here, per service.
			
			for ( idx = 0; idx < NoOfRecords; idx++ )
			{
				if (pgdb_GetByIndex (SERVICE_TABLE, idx, (Address)&svcdat))
				{
					/* match onid, tsid, sid, if a record is found, find the max prio value in the array of Priority. Assign to service the particular P, S, T of the index (j)  */
					
					if ((svcdat.OriginalNetworkId == mRegionCache[i].OnId) && (svcdat.Tsid == mRegionCache[i].Tsid) && (svcdat.ServiceId == mRegionCache[i].ServiceId))
					{
						// calc max priority amongst the array of Priority. 
						int temp, max_prio_idx = 0, max_prio = 0;
						for (temp = 0;temp < MAX_REGIONS_PER_SERVICE; temp++)
						{
							if (max_prio < Priority[temp] )
							{
								max_prio = Priority[temp];
								max_prio_idx = temp;
							}
						}


						// update the particular index record to the channel lib now, if it hasn't been already allocated as part of DbookOperators module. 
						if ( svcdat.CountryCode != cids_CountryUK )
						{
							svcdat.PrimaryRegion		=  mRegionCache[i].RegionList.RegionMap[max_prio_idx][MULT_PRIMARY_INDEX];
							svcdat.SecondaryRegion		=  mRegionCache[i].RegionList.RegionMap[max_prio_idx][MULT_SECONDARY_INDEX];
							svcdat.TertiaryRegion		=  mRegionCache[i].RegionList.RegionMap[max_prio_idx][MULT_TERTIARY_INDEX];
							svcdat.CountryCode			=  mRegionCache[i].CountryCode;
							svcdat.RegionDepth			=  mRegionCache[i].RegionList.RegionMap[max_prio_idx][MULT_REGION_DEPTH_INDEX];

								switch (mRegionCache[i].RegionList.RegionMap[max_prio_idx][MULT_REGION_DEPTH_INDEX])
							{
							case 0:
								svcdat.PrimaryRegion	= 0xFFFF;
								svcdat.SecondaryRegion  = 0xFFFF;
								svcdat.TertiaryRegion   = 0x1FFFF;
								break;
							case 1: 
								svcdat.SecondaryRegion = 0xFFFF;
								svcdat.TertiaryRegion  = 0x1FFFF;
								break;

							case 2: 
								svcdat.TertiaryRegion  = 0x1FFFF;
								break;
							default:
								break;
							}

							//PrintfNotice ("Lithesh :: %d %s SvcId = %d P = %d S = %d T = %d country code = %d \n",__LINE__, __FUNCTION__, svcdat.ServiceId,svcdat.PrimaryRegion, svcdat.SecondaryRegion, svcdat.TertiaryRegion, svcdat.CountryCode);
							pgdb_Update( SERVICE_TABLE, (Address)&svcdat );

						}
					}
				}
			} 
		}
	

		hpool_Free( RegionCachePoolId, mRegionCache);
		mRegionCache = NULL;
		
		hpool_Destroy (RegionCachePoolId);
		RegionCachePoolId = -1;

	}
}


void CHsvEuropeInstallation_mDbookConflicts_Priv::idbookconf_SetUserSelectConflictService(int LcnIndex, int SvcIndex)
{
	return;
}
void CHsvEuropeInstallation_mDbookConflicts_Priv::idbookconf_ConflictsSelectionDone(Bool UserSelection)
{
	return;
}
void CHsvEuropeInstallation_mDbookConflicts_Priv::idbookconf_GetConflictServices( HsvConflictServicesData *ConflictList, int *NumRecords )
{
	return;
}

