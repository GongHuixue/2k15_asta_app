
#include "_hsveuins_mconflicts.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_mconflicts")






Pump CHsvEuropeInstallation_mconflicts_Priv::s__mConflictsPmp;


/*****   Local Structures and enums   *****/



HsvConflictServicesData CHsvEuropeInstallation_mconflicts_Priv::*mConflictList = NULL/*[MAX_SERVICES]*/;

HsvConflictServicesData CHsvEuropeInstallation_mconflicts_Priv::*mAppConflictList = NULL/*[MAX_SERVICES]*/;

int CHsvEuropeInstallation_mconflicts_Priv::s__TOTAL_NUM_OF_CONFLICTS,CHsvEuropeInstallation_mconflicts_Priv::s__NUM_OF_USER_CONFLICTS;


/*****   static functions   *****/










/*****   provides interfaces functions implementation   *****/

void CHsvEuropeInstallation_mconflicts_Priv::iconpow_Init()
{
    mConflictsPmp = pmp_PmpCreateEx( pen_PumpEngine, mConflictsHandler, FALSE, "hsveuins_mConflicts" );
}

void CHsvEuropeInstallation_mconflicts_Priv::iconpow_TurnOn()
{

}

void CHsvEuropeInstallation_mconflicts_Priv::iconpow_TurnOff()
{

}


void CHsvEuropeInstallation_mconflicts_Priv::iconf_ResolveConflicts(int ConflictPass)
{
    UNUSED(ConflictPass);
    TOTAL_NUM_OF_CONFLICTS = NUM_OF_USER_CONFLICTS = 0;
	mConflictList = new HsvConflictServicesData [MAX_SERVICES];
	mAppConflictList = new HsvConflictServicesData [MAX_SERVICES];	
    memset((Address)mConflictList, 0, (sizeof(HsvConflictServicesData) * MAX_SERVICES));
    memset((Address)mAppConflictList, 0, (sizeof(HsvConflictServicesData) * MAX_SERVICES));
	TraceNotice (m, "Allocating memory for Conflicts");
    pmp_PmpSend(mConflictsPmp, evStep1, (Nat32)NULL);
}

void CHsvEuropeInstallation_mconflicts_Priv::iconf_SetUserSelectConflictService(int LcnIndex, int SvcIndex)
{
    TraceNotice(m,"%s %d LCN %d - LcnIndex %d SvcIndex %d", __FUNCTION__, __LINE__, CONFLICT_LCN(LcnIndex), LcnIndex, SvcIndex);
    CONFLICT_USER_INTERESTED(LcnIndex) = SvcIndex;
}

void CHsvEuropeInstallation_mconflicts_Priv::iconf_ConflictsSelectionDone(Bool UserSelection)
{
    /* User Selection would be Done => TRUE or Cancel => FALSE*/

    if(UserSelection == TRUE)
    {
        mSelectUserInterestedServices();
        TraceDebug(m,"Pmp send done with event = %d\n", evComplete);
        pmp_PmpSend(mConflictsPmp, evComplete, (Nat32)iconfN_ConflictsResolved);    
    }
    else
    {
        TraceNotice(m,"User is too lazy to select the services by himself - So Apply old rules <ServicePriority, SignalStrength> for sorting honoured services");
        TraceDebug(m,"Pmp send done with event = %d\n", evComplete);
        pmp_PmpSend(mConflictsPmp, evComplete, (Nat32)iconfN_ConflictsNotResolved);
    }
}

/*****   static functions implementation   *****/

void CHsvEuropeInstallation_mconflicts_Priv::mConflictsHandler(int value, Nat32 param)
{
    TraceDebug(m,"%s: CURRENT STEP = %d\n",__FUNCTION__, value);

    switch(value)
    {
        case evStep1:
            TraceDebug(m,"%s %d populate list of conflicts\n", __FUNCTION__, __LINE__);
            mPopulateListOfConflicts(value);
            break;
        case evStep2:
            TraceDebug(m,"%s %d automatic resolution of conflicts whichever is possible\n", __FUNCTION__, __LINE__);
            /* Automatic resolution of conflicts whichever is possible */
            mAutomaticConflictResolution(value);
            break;
        case evStep3:
            TraceDebug(m,"%s %d user resolution of conflicts\n", __FUNCTION__, __LINE__);
            mUserConflictResolution(value);
            break;
        case evComplete:
            TraceDebug(m,"%s %d Conflict Resolution Complete, services to be sorted now\n", __FUNCTION__, __LINE__);
			delete[]	mConflictList;
			delete[]	mAppConflictList;	
			TraceNotice (m, "Deleting memory for Conflicts");
            iconfN_OnEvent(param);
            break;
        default:
            ASSERT(!"Unknown Step in sorting");
            break;
    }
}


void CHsvEuropeInstallation_mconflicts_Priv::mPopulateListOfConflicts(int evCurrentSortStep)
{
    int i = 0, j = 0, ServiceInfoIndex = 0, FirstConflictIndex = -1, NoOfRecs = pgdb_GetNoRecords(SERVICE_TABLE);
    HsvPgdatDigServiceData svcdat1, svcdat2;
    HsvPgdatPresetData presetdat;

    /* Before this pass all the non-Conflict services should be allocated 
       so, just a query for PRESET_NOT_ALLOCATED presets should give all the conflict services */

    for( i = 0; i < NoOfRecs; i++)
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, i, (Address)&svcdat1) == TRUE)
        {
            /* The VALID LCN RANGE check is required because perhaps in previous iterations of this loop we would have
               deleted a preset if it is occupied earlier, so this check would avoid that service being populated twice */
            if( PRESET_NOT_ALLOCATED(svcdat1) && VALIDLCNRANGE(svcdat1))
            {
                ServiceInfoIndex = 0, FirstConflictIndex = -1;

                presetdat.PresetNumber = svcdat1.LCN;
                if(pgdb_GetByKey(PRESET_TABLE, (Address)&presetdat) == TRUE)
                {
                    if(DIGITAL_PRESET(presetdat))
                    {   
                        ASSIGN_SVC_FROM_PRESET(svcdat2, presetdat);
                        if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat2) == TRUE)
                        {
                            pgdb_GetIndex(SERVICE_TABLE, &FirstConflictIndex, (Address)&svcdat2);

                            TraceNotice(m,"%s %d NoOfRecs %d svcdat2.LCN %d FirstConflictIndex %d OriginalNetworkId %d Tsid %d ServiceId %d Frequency %d StreamPriority %d", __FUNCTION__, __LINE__, NoOfRecs, svcdat2.LCN, FirstConflictIndex, svcdat2.OriginalNetworkId, svcdat2.Tsid, svcdat2.ServiceId, svcdat2.Frequency, svcdat2.StreamPriority);
                            if(mIsPresentInConflictList(svcdat1.LCN) == FALSE)
                            {
                                mCopyDataToList((Address) &svcdat2, ServiceInfoIndex, DIGITAL, svcdat1.LCN);
                                ServiceInfoIndex++;
                            }
                        }
                    }
                    else
                    {
                        /* Analog Service */
                        HsvPgdatAnalogData    anadat;

                        ASSIGN_ANALOG_KEYS(&anadat, &presetdat);

                        if(pgdb_GetByKey(ANALOG_TABLE, (Address)&anadat))
                        {
                            if(mIsPresentInConflictList(svcdat1.LCN) == FALSE)
                            {
                                mCopyDataToList((Address) &anadat, ServiceInfoIndex, ANALOG, svcdat1.LCN);
                                ServiceInfoIndex++;
                            }
                        }
                    }   
                }

                /* Now for rest of the records in ServiceTable */
                for( j = 0; j < NoOfRecs; j++)
                {
                    if(pgdb_GetByIndex(SERVICE_TABLE, j, (Address)&svcdat2) == TRUE)
                    {
                        /* first 2 checks are to prevent duplicate records in conflict list */
                        if( (svcdat2.LCN == svcdat1.LCN) && (j != FirstConflictIndex) && IS_VALID_CONFLICT(svcdat2) )
                        {
                            if(mIsPresentInConflictList(svcdat1.LCN) == FALSE)
                            {
                                mCopyDataToList((Address) &svcdat2, ServiceInfoIndex, DIGITAL, svcdat1.LCN);
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
	if(sysset_GetSystemCountry() == cids_CountryPoland)
	{
		TraceDebug(m,"Pmp send done with event = %d\n", (evCurrentSortStep + 1));
		pmp_PmpSend(mConflictsPmp, (evCurrentSortStep + 2), (Nat32)NULL);

	}
	else
	{
		TraceDebug(m,"Pmp send done with event = %d\n", (evCurrentSortStep + 1));
		pmp_PmpSend(mConflictsPmp, (evCurrentSortStep + 1), (Nat32)NULL);
	}
}

void CHsvEuropeInstallation_mconflicts_Priv::mAutomaticConflictResolution(int evCurrentStep)
{
    int i = 0, j = 0, ItalianServicesFoundInAutoInstall = 0, ConflictServiceIndex = 0;

    int MaxIndex =  pgdb_GetNoRecords(SERVICE_TABLE) - 1;

    for(i = 0; i < TOTAL_NUM_OF_CONFLICTS; i++)
    {
        HsvPgdatDigServiceData svcdat;

        ItalianServicesFoundInAutoInstall = 0; 
        ConflictServiceIndex = -1;
        for(j = 0; j < mConflictList[i].NoOfServices; j++)
        {
            if( VALID_SERVICE_INDEX(CONFLICT_SERVICE_DBINDEX(i,j), MaxIndex) )

            {
                pgdb_GetByIndex(SERVICE_TABLE, CONFLICT_SERVICE_DBINDEX(i, j), (Address)&svcdat);

                /* Spec. => The distinguish between the Networks are made only in autoinstallation, whereas in update & manual it is not */
                if(AUTO_INSTALL)
                {
                    if(IS_ITALIAN_NTK(svcdat))
                    {
                        /* Italian service found in the existing conflicts, so wat else best service you can get here on than this */
                        ItalianServicesFoundInAutoInstall++;
                        ConflictServiceIndex = j;
                    }
                }
                else
                {
                    /* AutomaticResolution for update/manual install would have taken care by sorting module in mConflictDetection function 
                       so, nothing to do here */
                }
            }

        }

        if(ItalianServicesFoundInAutoInstall == 1)
        {
            /* Only 1 ITALIAN SERVICE found in conflicts and rest NON-ITALIAN Services found, so user intervention not needed automatically resolve */
            mUpdateConflictPresets(ConflictServiceIndex, CONFLICT_SERVICE_DBINDEX(i, ConflictServiceIndex), FALSE);
            mConflictList[i].AutomaticConflictResolution = TRUE;
        }
    }

    TraceDebug(m,"Pmp send done with event = %d\n", (evCurrentStep + 1));
    pmp_PmpSend(mConflictsPmp, (evCurrentStep + 1), (Nat32)NULL);

}

/* Forms the temporary list of Conflicts which has records to be resolved by only "User" resolution methods 
   if No records are found, then sends complete event, else sends notification to Apps to display these records */
void CHsvEuropeInstallation_mconflicts_Priv::mUserConflictResolution(int evCurrentStep)
{
    UNUSED(evCurrentStep);
    int i = 0, LastAppRecIndex = INVALID_INDEX;

    /* Check if All conflict records are resolved by "Automatic Resolution" in previous step
       and generate the AppList which does not contain Automatic Resolved Conflict records, if any */

    TraceNotice(m,"%s %d TOTAL_NUM_OF_CONFLICTS %d mConflictList[%d].LCN %d LastAppRecIndex %d", __FUNCTION__, __LINE__, TOTAL_NUM_OF_CONFLICTS, i, CONFLICT_LCN(i), LastAppRecIndex);
    for(i = 0; i < TOTAL_NUM_OF_CONFLICTS; i++)
    {
        if(mConflictList[i].AutomaticConflictResolution != TRUE)
        {
            LastAppRecIndex++;
            mAppConflictList[LastAppRecIndex] = mConflictList[i];
            TraceNotice(m,"%s %d mConflictList[%d].LCN %d LastAppRecIndex %d", __FUNCTION__, __LINE__, i, CONFLICT_LCN(i), LastAppRecIndex);
        }
        else
        {
            TraceNotice(m,"%s %d mConflictList[%d].LCN %d", __FUNCTION__, __LINE__, i, CONFLICT_LCN(i));
        }

    }

    if(LastAppRecIndex == INVALID_INDEX)
    {
        /* All conflicts resolved already, No need of user intervention */
        TraceNotice(m,"All conflicts resolved already, No need of user intervention");
        TraceDebug(m,"Pmp send done with event = %d\n", evComplete);

        pmp_PmpSend(mConflictsPmp, evComplete, (Nat32)iconfN_ConflictsResolved);
    }
    else
    {
        /* Conflicts still remaining after "Automatic Resolution step" So, User has to resolve the conflicts by choosing what he needs */
        TraceNotice(m,"Conflicts still remaining after Automatic Resolution step");
        TraceNotice(m,"So, User has to resolve the conflicts by choosing what he needs");

        NUM_OF_USER_CONFLICTS = LastAppRecIndex + 1;

        TraceNotice(m,"%s %d NUM_OF_USER_CONFLICTS %d", __FUNCTION__, __LINE__, NUM_OF_USER_CONFLICTS);
        insN_OnEvent(insN_EventOnConflictsDetected, rins_GetInstallationMode());
    }
}

/**** Copy channel name to unicode ******/
void CHsvEuropeInstallation_mconflicts_Priv::mCopyString(Nat16 *dest, Nat16 *src, int maxchars)
{
    int i = 0;
    for (i = 0 ; i < maxchars; i++)
    {
        *dest++ = *src++;
    }   
    *dest = '\0';
}

/* Forms the temporary list of Conflicts which has records to be resolved by either "Automatic" OR "User" resolution methods */
void CHsvEuropeInstallation_mconflicts_Priv::mCopyDataToList(Address data, int ServiceInfoIndex, int ChannelType, int ConflictLCN)
{
    if(ServiceInfoIndex < MAX_CONFLICT_SERVICES)
    {
        if(ChannelType == DIGITAL)
        {
            HsvPgdatDigServiceData *svcdat = (HsvPgdatDigServiceData *)data;
            /* LCN */
            CONFLICT_LCN(TOTAL_NUM_OF_CONFLICTS) = ConflictLCN;
            /* Service Name */
            mCopyString( mConflictList[TOTAL_NUM_OF_CONFLICTS].ServiceInfo[ServiceInfoIndex].ServiceName, svcdat->ChannelName, div_PresetNameLength );
            /* DbIndex of the Service */
            pgdb_GetIndex(SERVICE_TABLE, &(CONFLICT_SERVICE_DBINDEX(TOTAL_NUM_OF_CONFLICTS, ServiceInfoIndex)), (Address)svcdat);

            TraceNotice(m,"%s %d mConflictList[%d].LCN %d mConflictList[%d].NoOfServices %d", __FUNCTION__, __LINE__, TOTAL_NUM_OF_CONFLICTS, CONFLICT_LCN(TOTAL_NUM_OF_CONFLICTS), TOTAL_NUM_OF_CONFLICTS, mConflictList[TOTAL_NUM_OF_CONFLICTS].NoOfServices);
            /* First invalidate all the LCNs and then only validate the User selected servivce, 
               This ensures the LCN of user interested service is honoured and all others are treated as Non-Honoured services */
            INVALIDATE(svcdat->LCN);
            pgdb_Update(SERVICE_TABLE, (Address)svcdat);
        }
        else
        {
            HsvPgdatAnalogData  *anadat = (HsvPgdatAnalogData *)data;

            /* LCN */
            CONFLICT_LCN(TOTAL_NUM_OF_CONFLICTS) = ConflictLCN;
            /* Service Name */
            mCopyString( mConflictList[TOTAL_NUM_OF_CONFLICTS].ServiceInfo[ServiceInfoIndex].ServiceName, anadat->ChannelName, div_PresetNameLength );
            /* DbIndex df Analog Table not needed */
            CONFLICT_SERVICE_DBINDEX(TOTAL_NUM_OF_CONFLICTS, ServiceInfoIndex) = INVALID_INDEX;
        }
        /* CURRENT_SERVICE_INDEX is 0 because on population of conflict list we first the preset allocated service and then rest of the services follow */
        mConflictList[TOTAL_NUM_OF_CONFLICTS].UserPreferedServiceIndex = CURRENT_SERVICE_INDEX;
        mConflictList[TOTAL_NUM_OF_CONFLICTS].AutomaticConflictResolution = FALSE;
        mConflictList[TOTAL_NUM_OF_CONFLICTS].NoOfServices++;
    }
    else
    {
        TraceNotice(m,"Danger: Conflict services exceeding MAX limit");
    }
}

void CHsvEuropeInstallation_mconflicts_Priv::iconf_GetConflictServices( HsvConflictServicesData *ConflictList, int *NumRecords )
{
    int i = 0;

    for(i = 0; i < NUM_OF_USER_CONFLICTS; i++)
    {
        ConflictList[i] = mAppConflictList[i];
    }
    *NumRecords = NUM_OF_USER_CONFLICTS;

    TraceNotice(m,"%s %d NUM_OF_USER_CONFLICTS %d", __FUNCTION__, __LINE__, NUM_OF_USER_CONFLICTS);
}

Bool CHsvEuropeInstallation_mconflicts_Priv::mIsPresentInConflictList(Nat16 LCN)
{
    int i = 0;
    Bool retval = FALSE;

    for( i = 0; i < TOTAL_NUM_OF_CONFLICTS; i++)
    {
        if(LCN == CONFLICT_LCN(i) )
        {
            retval = TRUE;
            break;
        }       
    }
    TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}

/* This function would make the LCNs of user installed service valid again, so that it would be honoured this time in sorting pass,
   Also delete the already allocated preset if user selected is different from one, if it is same then it would revalidate the LCN of the service
   All Analog cases are also handled(implicitly) */
void CHsvEuropeInstallation_mconflicts_Priv::mSelectUserInterestedServices(void)
{
    int LCNIndex, DbIndex;

    for(LCNIndex = 0; LCNIndex < NUM_OF_USER_CONFLICTS; LCNIndex++)
    {
        DbIndex = CONFLICT_USER_SERVICE_DBINDEX(LCNIndex, CONFLICT_USER_INTERESTED(LCNIndex));

        mUpdateConflictPresets(CONFLICT_USER_INTERESTED(LCNIndex), DbIndex, TRUE);
    }
}

void CHsvEuropeInstallation_mconflicts_Priv::mUpdateConflictPresets(int PrefConflictServiceIndex, int DbIndex, Bool UserOrAutomatic)
{
    HsvPgdatDigServiceData svcdat, oldsvcdat;
    HsvPgdatPresetData presetdat;
    int MaxIndex = pgdb_GetNoRecords(SERVICE_TABLE) - 1;

    if( VALID_SERVICE_INDEX(DbIndex, MaxIndex) )
    {
        if(pgdb_GetByIndex(SERVICE_TABLE, DbIndex, (Address)&svcdat) == TRUE)
        {
            /* User interested service, hence honouring the LCN of it */
            TraceDebug(m,"%s::%d %s has selected Service %d\n",__FUNCTION__, __LINE__, UserOrAutomatic?"User":"AutomaticResolution", DbIndex);
            REVALIDATE(svcdat.LCN);
            pgdb_Update(SERVICE_TABLE, (Address)&svcdat);
        }
    }
    else
    {
        TraceDebug(m,"%s::%d Invalid database index received from apps\n",__FUNCTION__, __LINE__);

        //ASSERT(!"Invalid database index received from apps");
        /* Not ASSERT as this could be analog usecase :) */
    }

    if(PrefConflictServiceIndex != CURRENT_SERVICE_INDEX)
    {
        /* Also delete the first allocated LCN preset of this conflict(for sure there should be a preset allocated before) */
        presetdat.PresetNumber = svcdat.LCN;
        if(pgdb_GetByKey(PRESET_TABLE,(Address)&presetdat) == TRUE)
        {
            pgdb_Delete(PRESET_TABLE,(Address)&presetdat);
            TraceNotice(m,"%s %d Preset deleted %d", __FUNCTION__, __LINE__, presetdat.PresetNumber);
            if(DIGITAL_PRESET(presetdat))
            {
                ASSIGN_SVC_FROM_PRESET(oldsvcdat,presetdat);
                if(pgdb_GetByKey(SERVICE_TABLE, (Address)&oldsvcdat) == TRUE)
                {
                    INVALIDATE(oldsvcdat.LCN);
                    oldsvcdat.PresetNumber = INVALID_PRESET;
                    pgdb_Update(SERVICE_TABLE, (Address)&oldsvcdat);
                }
            }
        }
    }
    else
    {
        TraceNotice(m,"%s selected service is same as currently honoured one", UserOrAutomatic?"User":"AutomaticResolution");
    }
}


void CHsvEuropeInstallation_mconflicts_Priv::iconf_AssignRegionAttributesForService ()
{
	return;
}