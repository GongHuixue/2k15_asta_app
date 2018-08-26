/*****************************************************************************************
  *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
  *
  *  This  source code and any compilation or derivative thereof is the proprietary information of Koninklijke
  *  Philips Electronics N.V. and is confidential in nature.  Under no circumstances is this software to beexposed  
  *  to or placed under an Open Source License of any type without the expressed written permission of 
  *  Koninklijke Philips Electronics N.V.
  *
  *  %name: hsvdvbsfreesat_mAcq.c %
  *  %version:  TVG_1 %
  *  %date_modified:  %
  *  %derived_by:  anuma %
  *
  ****************************************************************************************/

/*****************************************************************************************
 * Include files
 *****************************************************************************************/
#include "CHsvDvbsOpProfile_mAcq.h"

/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/
TRACESYMBOL(m, "installation/hsvdvbsopprofile/hsvdvbsopprofile_mAcq")


/****************************************************************************
 * Static variables
 ****************************************************************************/
Pump CHsvDvbsOpProfile_mAcq::mDataAcqPump;

CHsvDvbsOpProfile_mAcq::CamDSDesc CHsvDvbsOpProfile_mAcq::mCamDSDesc;
CHsvDvbsOpProfile_mAcq::CamServiceList CHsvDvbsOpProfile_mAcq::mSvcListData;


int CHsvDvbsOpProfile_mAcq::mDigitalChannelsFound = 0;
int CHsvDvbsOpProfile_mAcq::mDigitalTvChannelsFound = 0;
int CHsvDvbsOpProfile_mAcq::mDigitalRadioChannelsFound = 0;
int CHsvDvbsOpProfile_mAcq::mRemoveCurTv = 0;
int CHsvDvbsOpProfile_mAcq::mRemoveCurRadio =0;

CHsvDvbsOpProfile_mAcq::HsvDataAcqInstance CHsvDvbsOpProfile_mAcq::DataAcqInstance;
HsvInstallationPTC CHsvDvbsOpProfile_mAcq::CurrentPTC;


double CHsvDvbsOpProfile_mAcq::RollOffTable[4]  =
{
    0.35, /* "00" */
    0.25, /* "01" */
    0.20, /* "10" */
    0.00  /* "11" -- Reserved */
};


/****************************************************************************
 * Static functions
 ****************************************************************************/

void CHsvDvbsOpProfile_mAcq::mPumpHandler (int value, Nat32 param)
{
    TraceInfo (m, "%s() : value %d\n", __FUNCTION__, value);

    switch (value)
    {
        case EvStartAcquire:
            mStartAcquisition();
            break;
        case EvAcquireTSInfo:
            mAcquireTSInfo();
            break;
        case EvCompleteAcquire:
            // Give acquire complete notification
            idataacqN->OnDataAquired(TRUE);
            TraceNotice (m, "Num of Channels %d, Added TV %d Radio %d. Removed TV %d Radio %d",
                                    mDigitalChannelsFound, mDigitalTvChannelsFound, mDigitalRadioChannelsFound,
                                    mRemoveCurTv,mRemoveCurRadio );
            break;
    }

    UNUSED(param);
}

void CHsvDvbsOpProfile_mAcq::mAddSatelliteInfo(void)
{
    HSVSPTYPE(SatelliteDS, dvb, camnit) currentSdsd;
    Bool isSdsdChange = FALSE;
    HsvPgdatDigSatInfoData satInfo;
	HsvSatelliteMapping	SatelliteMapping;
	int 	RetVal = FALSE;

    pgdb->Initialise(IHsvProgramDatabaseConstants_SatInfo, (Address) &satInfo);

    if(DataAcqInstance.NumSdsds)
    {
        memcpy(&currentSdsd, &mCamDSDesc.SatDesc[0], sizeof(HsvNITSatelliteDS));
		
		RetVal= iprescanparser->ExtractPreScanTableFromXml();
		if (RetVal == TRUE)
		{
			SatelliteMapping.OrbitalPosition = currentSdsd.OrbitalPosition;
			SatelliteMapping.EastWestFlag = currentSdsd.WestEastFlag;
			TraceNotice (m, "From SDSD OrbPos %d EWFlag %d ", SatelliteMapping.OrbitalPosition, SatelliteMapping.EastWestFlag); 
			RetVal = iprescanparser->GetSatelliteAttributeByPosition (&SatelliteMapping);
		}
		
		satInfo.LnbNumber = 0;
		satInfo.LnbType = LnbUniversal;
		satInfo.SatelliteId = SatelliteMapping.SatelliteId;
		satInfo.OrbitalPosition = SatelliteMapping.OrbitalPosition;
		memcpy (satInfo.SatelliteName, SatelliteMapping.SatelliteName, MAX_SATELLITE_NAME_LEN * sizeof(Nat16));
		TraceNotice(m, "SatInfoTable: Lnb %d Pos %d Id %d ", satInfo.LnbNumber, satInfo.OrbitalPosition, satInfo.SatelliteId);

		pgdb->Add (SAT_INFO_TABLE,(Address)&satInfo); 
	}
}

void CHsvDvbsOpProfile_mAcq::mStartAcquisition (void)
{
    mPopulateSatelliteLnbNumber();
    mCollectSdsds();
	mAddSatelliteInfo();
    m_pfac.PmpSend (mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
}


void CHsvDvbsOpProfile_mAcq::mPopulateSatelliteLnbNumber ()
{
    //Get the LnbNumber from Scan module
    isvcscandata->GetPtcInfo (&CurrentPTC);

    DataAcqInstance.LnbNumber = CurrentPTC.LnbNumber;
}


void CHsvDvbsOpProfile_mAcq::mCollectSdsds (void)
{
    int numSDSD = 0;
    int loopCount = 0;
    int sdsdLoopCount = 0;
    Bool addSDSDEntry =  FALSE;
    HSVSPTYPE(SatelliteDS, dvb, camnit) satSDSD;

    numSDSD = strapi->GetSize (HsvMain,  HSVSPID(SatelliteDS, dvb, camnit));
    mCamDSDesc.numSDSD = 0;

    TraceNotice (m," Number of SDSD %d\n", numSDSD);

    for(sdsdLoopCount = 0; sdsdLoopCount < numSDSD; ++sdsdLoopCount)
    {
        if(strapi->GetByIndex (HsvMain, HSVSPID(SatelliteDS, dvb, camnit), sdsdLoopCount, (void*)&satSDSD))
        {
            addSDSDEntry =  TRUE;

            TraceDebug (m,"SDSD Entry ONID 0x%x NID 0x%x TSID 0x%x\n", \
                           satSDSD.Original_NetworkId, satSDSD.NetworkId, satSDSD.Tsid);
            for(loopCount = 0; loopCount < mCamDSDesc.numSDSD; ++loopCount)
            {
                // search for existing entry before adding new entry
                if((mCamDSDesc.SatDesc[loopCount].Original_NetworkId == satSDSD.Original_NetworkId) &&
                   (mCamDSDesc.SatDesc[loopCount].NetworkId == satSDSD.NetworkId) &&
                   (mCamDSDesc.SatDesc[loopCount].Tsid == satSDSD.Tsid))
                {
                    // Entry already available
                    addSDSDEntry = FALSE;
                    TraceNotice (m,"SDSD entry already present\n");
                    break;
                }
            }

            if (addSDSDEntry)
            {
                memcpy (&(mCamDSDesc.SatDesc[mCamDSDesc.numSDSD]), &satSDSD, sizeof(HSVSPTYPE(SatelliteDS, dvb, camnit)));
                ++mCamDSDesc.numSDSD;
                TraceDebug (m,"SDSD Entry Added ONID 0x%x NID 0x%x TSID 0x%x",  \
                               satSDSD.Original_NetworkId,  satSDSD.NetworkId, satSDSD.Tsid);
            }
        }
    }

    DataAcqInstance.CurSdsd = 0;
    DataAcqInstance.NumSdsds = mCamDSDesc.numSDSD;
    TraceNotice (m," DataAcqInstance.NumSdsds %d \n", DataAcqInstance.NumSdsds);
}


void CHsvDvbsOpProfile_mAcq::mAcquireTSInfo (void)
{
    HSVSPTYPE(SatelliteDS, dvb, camnit) currentSdsd;
    Bool isSdsdChange = FALSE;
    HsvPgdatDigTSData oldTsData;

    pgdb->Initialise(IHsvProgramDatabaseConstants_DigitalTS, (Address) &oldTsData);

    TraceNotice(m, "DataAcqInstance.CurSdsd %d, DataAcqInstance.NumSdsds %d, sizeof(CurrentSdsd) %d\n", 
                            DataAcqInstance.CurSdsd, DataAcqInstance.NumSdsds, sizeof(currentSdsd));
    if(DataAcqInstance.CurSdsd < DataAcqInstance.NumSdsds)
    {
        memcpy(&currentSdsd, &mCamDSDesc.SatDesc[DataAcqInstance.CurSdsd], sizeof(HsvNITSatelliteDS));

        DataAcqInstance.NetworkId = currentSdsd.NetworkId;
        DataAcqInstance.OnId = currentSdsd.Original_NetworkId;
        DataAcqInstance.TsId = currentSdsd.Tsid;
        // PTC info is built within Acq. module as no tuning to SDSD is required
        mGetPTCInfo(currentSdsd, &CurrentPTC);

        if (TRUE == mIsUpdateInstall())
        {
            // If TS is already present with different Keys then add services with new keys returned
            mAddToTSTable (&CurrentPTC, &isSdsdChange, &oldTsData);
            if (FALSE == mInstallMux (CurrentPTC, isSdsdChange, &oldTsData))
            {
                // If no services are added/updated, delete entry from TS Table
                mDeleteTSTable (&CurrentPTC);
            }
        }
        else
        {
            // Intsall the services and Add to TS Table
            if (TRUE == mInstallMux (CurrentPTC, isSdsdChange, &oldTsData))
            {
                // Add entry to TS Table
                mAddToTSTable (&CurrentPTC, &isSdsdChange, &oldTsData);
            }
        }
        // Increment CurSdsd after installing mux
        ++DataAcqInstance.CurSdsd;

    }

    if(DataAcqInstance.CurSdsd >= DataAcqInstance.NumSdsds)
    {
        // Delete services from all deleted muxes, in current version of NIT
        // delete the service atleast if one valid service (one valid mux) present in NIT,
        // otherwise the retain existing service list
        if((TRUE == mIsUpdateInstall()) && (0 < DataAcqInstance.NumSdsds))
        {
            mDeleteServicesFromDeletedMuxesInCurrentNIT();
        }
        m_pfac.PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);
    }
    else
    {
        m_pfac.PmpSend(mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
    }
}


void CHsvDvbsOpProfile_mAcq::mGetPTCInfo (HSVSPTYPE(SatelliteDS,dvb,nit) Sdsd, HsvInstallationPTC *ptc)
{
    int TransponderFreq = 0;

    ptc->LnbNumber = DataAcqInstance.LnbNumber;
    ptc->Polarization = Sdsd.Polarization;
    ptc->Frequency = Sdsd.Frequency;
    ptc->SDSDFrequency = Sdsd.Frequency;
    ptc->SymbolRate = Sdsd.SymbolRate;
    ptc->ModulationType = Sdsd.ModulationType;
    TransponderFreq = ptc->Frequency;
    ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);
    ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);
    ptc->QSignalStrength = 0;
    ptc->SSignalStrength = 0;
    ptc->HierarchyMode = HsvHierarchyNone;
    ptc->StreamPriority = HsvStreamPriorityHigh;
    ptc->ChannelBandwidth = mCalculateBandwidthFromSdsd (Sdsd.RollOff, Sdsd.SymbolRate, Sdsd.FECInner);
}


// IsSdsdChange flag indicates if any key(freq/pol) is updated due to SDSD change.
// If SDSD freq\pol. is changed then old Tpid entry is deleted and new entry is added with new freq\pol and oldTpid is returned
void CHsvDvbsOpProfile_mAcq::mAddToTSTable (HsvInstallationPTC *ptc, Bool *pIsSdsdChange, HsvPgdatDigTSData *pOldTsData)
{
    HsvPgdatDigTSData tsData, tmpTsData;
    int numTsTables = 0;
    int tsTableCount = 0;

    pgdb->Initialise(IHsvProgramDatabaseConstants_DigitalTS, (Address) &tsData);
    pgdb->Initialise(IHsvProgramDatabaseConstants_DigitalTS, (Address) &tmpTsData);

    // Filling attributes from ptc and acqinstance
    tsData.Frequency = ptc->Frequency;
    tsData.SymbolRate = ptc->SymbolRate;

    tsData.OriginalNetworkId = DataAcqInstance.OnId;
    tsData.Tsid = DataAcqInstance.TsId;
    tsData.NetworkId = DataAcqInstance.NetworkId;
    tsData.ModulationType = ptc->ModulationType;

    tsData.Bandwidth = ptc->ChannelBandwidth;

    tsData.PtcListVersion = isvcscandata->GetInstallationVersion();
    tsData.SDSDFrequency = ptc->SDSDFrequency;
    tsData.UserInstalled = mIsManualInstall();
    tsData.LnbNumber = ptc->LnbNumber;
    tsData.Polarization = ptc->Polarization;
    tsData.Tpid = ptc->TPID;

    tmpTsData.LnbNumber = tsData.LnbNumber;
    tmpTsData.Frequency = tsData.Frequency;
    tmpTsData.Polarization = tsData.Polarization;

    // check entry already present; If yes update else add
    if (FALSE == pgdb->GetByKey (PTC_TABLE, (Address)&tmpTsData))
    {
        // If GetByKey is failed, check if any Keys(Frequency/polarization) are updated
        if (TRUE == mIsUpdateInstall())
        {
            numTsTables = pgdb->GetNoRecords (PTC_TABLE);

            for(tsTableCount = 0; tsTableCount < numTsTables; ++tsTableCount)
            {
                pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalTS, (Address) &tmpTsData);
                // Check only TS tables installed via pkg install
                if((TRUE == pgdb->GetByIndex(PTC_TABLE, tsTableCount, (Address)&tmpTsData)) && (0 != tmpTsData.SDSDFrequency))
                {
                    if((tmpTsData.OriginalNetworkId == tsData.OriginalNetworkId) && (tmpTsData.Tsid == tsData.Tsid))
                    {
                        // Return old Keys and TS table
                        pOldTsData->LnbNumber    = tmpTsData.LnbNumber;
                        pOldTsData->Frequency    = tmpTsData.Frequency;
                        pOldTsData->Polarization = tmpTsData.Polarization;
                        // read the current data from database using key
                        pgdb->GetByKey (PTC_TABLE, (Address) pOldTsData);
                        
                        *pIsSdsdChange = TRUE;

                        // Delete the Old TS Table with old Tpid and Add new TS Table with updated Tpid and keys
                        pgdb->Delete (PTC_TABLE, (Address)&tmpTsData);
                        TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, \
                                         tmpTsData.Frequency, tmpTsData.Polarization);
                        pgdb->Add (PTC_TABLE, (Address)&tsData);
                        TraceNotice (m, "Addition to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, \
                                         tsData.Frequency, tsData.Polarization);
                        break;

                    }
                }
            }

            // No TS matches..It is a New TS, Add to TS table
            if (tsTableCount == numTsTables)
            {
                pgdb->Add (PTC_TABLE, (Address )&tsData);
            }
        }
        else
        {
            // In Auto install, Add to TS table
            pgdb->Add (PTC_TABLE, (Address )&tsData);
        }
    }
    else
    {
        pgdb->Update(PTC_TABLE, (Address )&tsData);
    }
}


Bool CHsvDvbsOpProfile_mAcq::mInstallMux (HsvInstallationPTC ptc, Bool isSdsdChange, HsvPgdatDigTSData *pOldTsData)
{
    Bool retVal = FALSE;
    HSVSPTYPE(CamNITService, dvb, camnit) camNitSvc;
    int loopCount = 0;
    int startCount = 0;
    int endCount = 0;
    int installedServices = 0;

    int numServices = strapi->GetSize (HsvMain,  HSVSPID(CamNITService, dvb, camnit));

    TraceNotice (m, "Number of CAM Services %d", numServices);
    if(TRUE == strapi->GetRangeByKey (HsvMain, HSVSPID(CamNITService, dvb, camnit), 2, DataAcqInstance.OnId, 
                                      DataAcqInstance.TsId, 0, &startCount, &endCount))
    {
        TraceDebug(m, "%s %d NoOfServices in MUX = %d ONID = 0x%x TSID = 0x%x \n", __FUNCTION__, __LINE__, \
                        ((endCount - startCount) + 1), DataAcqInstance.OnId, DataAcqInstance.TsId);

        // From strapi get all the services and add/update in SERVICE_TABLE
        for(loopCount = endCount; loopCount >= startCount; --loopCount)
        {
            if(TRUE == strapi->GetByIndex (HsvMain, HSVSPID(CamNITService, dvb, camnit), loopCount, (void *)(&camNitSvc)))
            {

                TraceDebug(m, "ONID 0x%x TSID 0x%x Srv ID 0x%x isSdsdChange %d\n", camNitSvc.OriginalNetworkId, \
                               camNitSvc.TsId, camNitSvc.ServiceId, isSdsdChange);

                if (mCheckAndInstallService(&ptc, isSdsdChange, pOldTsData, &camNitSvc))
                {
                    ++installedServices;
                    retVal = TRUE;
                }
                
            }
        }

    }
    else
    {
        TraceNotice (m, "No services found in service list of ONID = 0x%x TSID = 0x%x \n", DataAcqInstance.OnId, DataAcqInstance.TsId);
    }
    if(mIsUpdateInstall())
    {
        if (TRUE == isSdsdChange)
        {
            // Here OldTPID will remain with non transmitted services
            mDeleteAllServicesFromCarrier (pOldTsData->Tpid);
        }
        else
        {
            mDeleteServicesCurrentCarrier (&ptc);
        }
    }

    TraceNotice (m, "Homing Mode: Num TV: %d Num Radio: %d \n", mDigitalTvChannelsFound, mDigitalRadioChannelsFound);

    return retVal;
}


Bool CHsvDvbsOpProfile_mAcq::mCheckAndInstallService (HsvInstallationPTC *ptc, Bool isSdsdChange, 
                                                     HsvPgdatDigTSData *pOldTsData, HSVSPTYPE(CamNITService, dvb, camnit) *camNitSvc)
{
    Bool retVal = FALSE;
    Bool channelExists = FALSE;
    Bool duplicateSvc = FALSE;
    Bool serviceAdded = FALSE;
    Bool toAdd = TRUE;
    int loopCount = 0;
    HsvPgdatDigServiceData svcData, tempSvcData;

    pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalService, (Address)(&svcData));
    pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalService, (Address)(&tempSvcData));

    for (loopCount = 0; loopCount < MAX_NUM_LCN_ENTRY; ++loopCount)
    {
        svcData.MultipleLCN[loopCount] = INVALID_LCN;
        svcData.MultiplePreset[loopCount] = INVALID_PRESET;
    }
    // If db key(Tpid) is updated, delete the service and add it again with new Tpid (as Tpid is the key for service table)
    if (TRUE == isSdsdChange)
    {
        svcData.Tpid = pOldTsData->Tpid;
        svcData.ServiceId = camNitSvc->ServiceId;

        if (TRUE == pgdb->GetByKey (SERVICE_TABLE, (Address) &svcData))
        {
            duplicateSvc = TRUE;
        }
    }
    else
    {      
        svcData.Tpid = ptc->TPID;
        svcData.ServiceId = camNitSvc->ServiceId;
        pgdb->GetByKey (SERVICE_TABLE, (Address) &svcData);
    }

    svcData.Frequency = ptc->Frequency;
    svcData.OriginalNetworkId = DataAcqInstance.OnId;
    svcData.Tsid = DataAcqInstance.TsId;
    svcData.LnbNumber = ptc->LnbNumber;
    svcData.Polarization = ptc->Polarization;
    svcData.Tpid = ptc->TPID;
    svcData.ServiceId = camNitSvc->ServiceId;
    svcData.VisibleService = TRUE;
    svcData.NetworkId = DataAcqInstance.NetworkId;
    svcData.SDSDFrequency = ptc->SDSDFrequency;

    if (FALSE == mIsServiceInstallable (camNitSvc))
    {
        toAdd = FALSE;
        TraceNotice (m, "service is not installable onid: %d, tsid: %d, svcid: %d\n", \
                     svcData.OriginalNetworkId, svcData.Tsid, svcData.ServiceId );
    }

    if (TRUE == toAdd)
    {
        tempSvcData.ServiceId = svcData.ServiceId;
        tempSvcData.Tpid = svcData.Tpid;        
        channelExists = pgdb->GetByKey (SERVICE_TABLE, (Address ) &tempSvcData);
        TraceNotice (m, "tpId 0x%x svcId 0x%x channelExists %d\n", tempSvcData.Tpid, tempSvcData.ServiceId, channelExists);

        if (channelExists)
        {
            TraceDebug (m, "channelExists for svcId 0x%x and SvcType %d\n", svcData.ServiceId, svcData.ServiceType);
            // If entry already present update the service data
            mUpdateService (&svcData, ptc, camNitSvc);
            retVal = TRUE;
        }
        else
        {
            mAddNewService(&svcData, ptc, camNitSvc, duplicateSvc);
            serviceAdded = TRUE;
            retVal = TRUE;
        }

    }
    else
    {
        // if service type is not valid then delete the service from database, also
        // delete it's preset table entry
        tempSvcData.Tpid = svcData.Tpid;
        tempSvcData.ServiceId = svcData.ServiceId;

        if (pgdb->GetByKey (SERVICE_TABLE, (Address)&tempSvcData))
        {
            mDeleteService(&tempSvcData, FALSE);
        }
    }
    if (duplicateSvc)
    {
        // Delete the duplicate service with old tpId, svcId
        pgdb->Initialise(IHsvProgramDatabaseConstants_DigitalService, (Address)(&tempSvcData));
        tempSvcData.Tpid      = pOldTsData->Tpid;
        tempSvcData.ServiceId = camNitSvc->ServiceId;
        if(pgdb->GetByKey(SERVICE_TABLE, (Address)&tempSvcData))
        {
            mDeleteService (&tempSvcData, TRUE);
        }
    }
    return retVal;
}


void CHsvDvbsOpProfile_mAcq::mAddNewService (HsvPgdatDigServiceData *pSvcData ,HsvInstallationPTC *ptc, 
                                                                                   HSVSPTYPE(CamNITService, dvb, camnit) *service, Bool duplicateSvc)
{
    HsvPgdatPresetData presetData;
    int loopCount = 0;
	int mode, state;
    rins->GetCurrentInstallationState(&mode, &state);
    // Filling details of service, then adding it
    mAssignSvcBroadcastAttributes (pSvcData, ptc, service);
    mAssignLCN(pSvcData, service);
    mUpdateSatelliteName (pSvcData);
    //User attributes should be retained for duplicate service
    if(FALSE == duplicateSvc)
    {
        mAssignSvcNonBroadcastAttributes(pSvcData);
	if((mode == AUTO_MODE) || (mode == CAM_NIT_UPDATE_MODE))
	{
		pSvcData->NewPreset = FALSE;
	}
	else
	{
		pSvcData->NewPreset = TRUE;
	}
	//	pSvcData->NewPreset = (mode == AUTO_MODE) ? FALSE : TRUE;
    }

    // Add to service table
    pgdb->Add(SERVICE_TABLE, (Address )pSvcData);
    TraceDebug(m, "Added Service:Name %s ONID:0x%x SVCID:0x%x SystemHidden = %d LCN 5d\n", pSvcData ->ExtChannelName, \
                            pSvcData->OriginalNetworkId, pSvcData->ServiceId,pSvcData->SystemHidden, pSvcData->MultipleLCN[0]);

    // If it is duplicate service, update the Preset Table with new parameters
    if(duplicateSvc)
    {
        for(loopCount = 0; loopCount < MAX_NUM_PRESET_ENTRY; ++loopCount){
            presetData.PresetNumber          = pSvcData->MultiplePreset[loopCount];
            if (TRUE == pgdb->GetByKey (PRESET_TABLE, (Address)&presetData))
            {
                presetData.OriginalNetworkId = pSvcData->OriginalNetworkId;
                presetData.ServiceId         = pSvcData->ServiceId;
                presetData.Tsid              = pSvcData->Tsid;
                presetData.Tpid              = pSvcData->Tpid;
                presetData.Frequency         = pSvcData->Frequency;
                presetData.Polarization      = pSvcData->Polarization;
                presetData.LnbNumber         = pSvcData->LnbNumber;
                pgdb->Update(PRESET_TABLE, (Address)&presetData);
            }
        }
    }
}

void CHsvDvbsOpProfile_mAcq::mAssignSvcBroadcastAttributes (HsvPgdatDigServiceData *pSvcData, HsvInstallationPTC *ptc, 
                                                                                                               HSVSPTYPE(CamNITService, dvb, camnit) *service)
{   
    pSvcData->ModulationType = ptc->ModulationType;
    pSvcData->Bandwidth = ptc->ChannelBandwidth;

    pSvcData->SymbolRate = ptc->SymbolRate;
    pSvcData->LnbNumber = ptc->LnbNumber;
    pSvcData->Polarization = ptc->Polarization;
    pSvcData->Tpid = ptc->TPID;
    pSvcData->AudioPid = INVALID_PID;
    pSvcData->VideoPid = INVALID_PID;
    pSvcData->PcrPid = INVALID_PID;
    pSvcData->ServiceType = mConvertToPgdatServiceType (service->ServiceType);

    TraceNotice (m, "%s() : service->ServiceType %d, pSvcData->ServiceType %d, \n", \
                            __FUNCTION__, service->ServiceType, pSvcData->ServiceType);

    pSvcData->FreeCiMode = 0;
    pSvcData->MatchBrandFlag = 0;
    pSvcData->NumBrandIds = 0;

    pSvcData->ScramblingStatus               = 1;
    mCopyString (pSvcData->ChannelName, service->ServiceName, (eurdiv->PresetNameLength() - 1));

    pSvcData->VisibleService = service->VisibleServiceFlag;
    pSvcData->NumericSelect = service->SelectableServiceFlag;
}

void CHsvDvbsOpProfile_mAcq::mAssignSvcNonBroadcastAttributes (HsvPgdatDigServiceData* pSvcData)
{
    int mode, state;
    int loopCount = 0;
    Bool proceed = FALSE;
    HsvPgdatPresetData presetData;
    HsvPgdatDigServiceData svcData;

    rins->GetCurrentInstallationState(&mode, &state);

    pSvcData->UserHidden = FALSE;
    pSvcData->ChannelLock = FALSE;
    pSvcData->Favorite = FALSE;

    pSvcData->DateStamp = 0;
    pSvcData->PresetNumber = INVALID_PRESET;
	/*if((mode == AUTO_MODE) || (mode == CAM_NIT_UPDATE_MODE))
	{
		pSvcData->NewPreset = FALSE;
	}
	else
	{
		pSvcData->NewPreset = TRUE;
	}*/
	//pSvcData->NewPreset = (mode == AUTO_MODE) ? FALSE : TRUE;
    pSvcData->HbbTvOption = 1;

    pSvcData->ServiceListVersion = mSvcListData.VersionNumber;
    pSvcData->PackageGroup = APPAPISAT_None;

    ASSIGN_KEYS_OF_SVC (svcData, (*pSvcData));

    if(pgdb->GetByKey(SERVICE_TABLE, (Address)&svcData) == TRUE)
    {
        pSvcData->NewPreset = svcData.NewPreset;

        pSvcData->ChannelLock = svcData.ChannelLock;;
        pSvcData->UserHidden = svcData.UserHidden;
        pSvcData->Favorite = svcData.Favorite;
        pSvcData->HbbTvOption = svcData.HbbTvOption;

        pSvcData->DeltaVolume = svcData.DeltaVolume;
        pSvcData->UserModifiedName = svcData.UserModifiedName;
        pSvcData->FavoriteNumber = svcData.FavoriteNumber;

        pSvcData->LogoURL = svcData.LogoURL;
        pSvcData->PresetNumber = svcData.PresetNumber;
        pSvcData->PackageGroup =  svcData.PackageGroup;

        // If the LCN is in valid range but LCNs are different then delete from Preset Table
        for(loopCount = 0; loopCount < MAX_NUM_LCN_ENTRY; ++loopCount)
        {
            if(INVALID_LCN != svcData.MultipleLCN[loopCount])
            {
                REVALIDATE(svcData.MultipleLCN[loopCount]);
                proceed = ((VALID_LCN_RANGE(pSvcData->MultipleLCN[loopCount]) || 
                                   VALID_LCN_RANGE(svcData.MultipleLCN[loopCount])) && 
                                 (pSvcData->MultipleLCN[loopCount] != svcData.MultipleLCN[loopCount]));
                if(proceed)
                {
                    TraceNotice (m, "%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d\n", __FUNCTION__, __LINE__, \
                                             pSvcData->MultipleLCN[loopCount], svcData.MultipleLCN[loopCount], svcData.MultiplePreset[loopCount]);
                    presetData.PresetNumber =   svcData.MultiplePreset[loopCount];
                    pgdb->Delete(PRESET_TABLE, (Address)&presetData);
                    pSvcData->MultiplePreset[loopCount] = INVALID_PRESET;
                }
            }
        }
        memcpy(pSvcData->UniqueIds, svcData.UniqueIds, sizeof(svcData.UniqueIds));
    }
}

void CHsvDvbsOpProfile_mAcq::mAssignLCN(HsvPgdatDigServiceData *pSvcData, HSVSPTYPE(CamNITService, dvb, camnit) *service)
{
    pSvcData->MultipleLCN[0] = service->LogicalChannelNumber;

    /* Check service is TV or Radio */
    if (mIsDigitalTvChannel (pSvcData))
    {        
        ++mDigitalTvChannelsFound;
    }
    else if (mIsDigitalRadioService (pSvcData))
    {
        ++mDigitalRadioChannelsFound;
    }
    ++mDigitalChannelsFound;
}


void CHsvDvbsOpProfile_mAcq::mUpdateService  (HsvPgdatDigServiceData* pSvcData, HsvInstallationPTC* ptc, 
                                           HSVSPTYPE(CamNITService, dvb, camnit) *service)
{
    mAssignSvcBroadcastAttributes (pSvcData, ptc, service);
    mAssignLCN(pSvcData, service);
    mAssignSvcNonBroadcastAttributes(pSvcData);
	pSvcData->NewPreset = FALSE;
    pgdb->Update(SERVICE_TABLE, (Address )pSvcData);
    TraceDebug(m,"Updated Service ONID:%d SVCID:%d\n", pSvcData->OriginalNetworkId, pSvcData->ServiceId);
}


void CHsvDvbsOpProfile_mAcq::mUpdateSatelliteName (HsvPgdatDigServiceData *pSvcData)
{
    HsvPgdatDigSatInfoData satInfo;

    satInfo.LnbNumber = pSvcData->LnbNumber;

    if (TRUE == pgdb->GetByKey (SAT_INFO_TABLE, (Address)&satInfo))
    {
        memcpy (pSvcData->SatelliteName, satInfo.SatelliteName, sizeof(pSvcData->SatelliteName));
    }
}


void CHsvDvbsOpProfile_mAcq::mDeleteService(HsvPgdatDigServiceData *pSvcData, Bool duplicateService)
{
    int loopCount = 0;
    int numDeletedSvcs = 0;
    HsvPgdatPresetData presetData;

    for (loopCount =0; loopCount < MAX_NUM_LCN_ENTRY; ++loopCount)
    {
        presetData.PresetNumber = pSvcData->MultiplePreset[loopCount];

        if (TRUE == pgdb->GetByKey (PRESET_TABLE, (Address)&presetData))
        {    
            pgdb->Delete(PRESET_TABLE, (Address)&presetData);
            ++numDeletedSvcs;
        }
    }

    // if the service is a duplicate service, then removed service count will be increased while assigning LCN itself
    if (!duplicateService)
    {
        if (mIsDigitalTvChannel (pSvcData))
        {
            mRemoveCurTv += numDeletedSvcs;
        }
        else if (mIsDigitalRadioService (pSvcData))
        {
            mRemoveCurRadio += numDeletedSvcs;
        }
    }

    pgdb->Delete(SERVICE_TABLE, (Address)pSvcData);
    TraceNotice (m, "Deleted service svcId[%d] tsId[%d] onId[%d]",
                                pSvcData->ServiceId,
                                pSvcData->Tsid,
                                pSvcData->OriginalNetworkId);    
}


void CHsvDvbsOpProfile_mAcq::mDeleteTSTable(HsvInstallationPTC *ptc)
{
    HsvPgdatDigTSData tsData;
    pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalTS, (Address) &tsData);

    tsData.LnbNumber     = ptc->LnbNumber;
    tsData.Frequency     = ptc->Frequency;
    tsData.Polarization  = ptc->Polarization;
    if (pgdb->GetByKey (PTC_TABLE, (Address )&tsData) == TRUE)
    {
        TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", \
                                __FUNCTION__, __LINE__, tsData.Frequency, tsData.Polarization);
        pgdb->Delete (PTC_TABLE, (Address )&tsData);
    }
}


void CHsvDvbsOpProfile_mAcq::mDeleteServicesCurrentCarrier (HsvInstallationPTC *ptc)
{
    Bool retVal = FALSE;
    HsvPgdatDigServiceData tempSvcData;
    int startCount = 0;
    int endCount = 0;
    int loopCount = 0;

    tempSvcData.Tpid = ptc->TPID;
    retVal = pgdb->GetRange (SERVICE_TABLE, 1, (Address)&tempSvcData, &startCount, &endCount);

    if (retVal)
    {
        for (loopCount = endCount; loopCount >= startCount; --loopCount)
        {
            retVal = pgdb->GetByIndex (SERVICE_TABLE, loopCount ,(Address)&tempSvcData);
            if ((TRUE == retVal) && 
                 (FALSE == mIsSvcPresentInServiceList(&tempSvcData)) &&
                 (0 != tempSvcData.SDSDFrequency)) // Dont delete services installed by generic module
            {    
                mDeleteService(&tempSvcData, FALSE);
            }
        }
    }
}


void CHsvDvbsOpProfile_mAcq::mDeleteAllServicesFromCarrier (int tpId)
{
    Bool retVal = FALSE;
    HsvPgdatDigServiceData tempSvcData;
    int startCount = 0;
    int endCount = 0;
    int loopCount = 0;

    tempSvcData.Tpid = tpId;

    retVal = pgdb->GetRange (SERVICE_TABLE, 1, (Address)&tempSvcData, &startCount, &endCount);

    if (retVal == TRUE)
    {
        for (loopCount = endCount; loopCount >= startCount; --loopCount)
        {
            retVal = pgdb->GetByIndex (SERVICE_TABLE, loopCount, (Address)&tempSvcData);
            if (retVal == TRUE)
            {    
                mDeleteService (&tempSvcData, FALSE);
            }
        }
    }
}


void CHsvDvbsOpProfile_mAcq::mDeleteServicesFromDeletedMuxesInCurrentNIT (void)
{
    HsvPgdatDigTSData tsData, tmpTsData;
    int numTsTables = 0;

    pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalTS, (Address) &tsData);

    numTsTables = pgdb->GetNoRecords (PTC_TABLE);

    while(numTsTables > 0)
    {
        --numTsTables;
        pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalTS, (Address) &tmpTsData);
        if ((TRUE == pgdb->GetByIndex (PTC_TABLE, numTsTables, (Address)&tmpTsData)) && (0 != tmpTsData.SDSDFrequency))
        {
            // Check if any service belongs to this TS is present in NIT SLD
            if((FALSE == mIsTSPresentInSLDList(&tmpTsData)) || (FALSE == mIsTSPresentInSDSDList(&tmpTsData)))
            {
                mDeleteAllServicesFromCarrier(tmpTsData.Tpid);
                TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, 
                                            tmpTsData.Frequency, tmpTsData.Polarization);
                pgdb->Delete (PTC_TABLE, (Address) &tmpTsData);
            }
        }
        else
        {
            TraceNotice (m,"Get PTC table failed Index %d SDSD Frequency %d\n",numTsTables,tmpTsData.SDSDFrequency);
        }
    }
}


Bool CHsvDvbsOpProfile_mAcq::mIsTSPresentInSLDList (HsvPgdatDigTSData *pTmpTsData)
{
    Bool retVal = FALSE;
    int startCount = 0;
    int endCount = 0;

    if (strapi->GetRangeByKey (HsvMain, HSVSPID(CamNITService, dvb, camnit), 2,
                                                pTmpTsData->OriginalNetworkId,
                                                pTmpTsData->Tsid, 0, &startCount, &endCount))
    {
        retVal = TRUE;
    }
    return retVal;
}


Bool CHsvDvbsOpProfile_mAcq::mIsTSPresentInSDSDList (HsvPgdatDigTSData *pTmpTsData)
{
    Bool retVal = FALSE;
    HSVSPTYPE(SatelliteDS, dvb, camnit) satSDSD;

    if (strapi->GetByKey(HsvMain, HSVSPID(SatelliteDS, dvb, camnit), pTmpTsData->OriginalNetworkId,
                         pTmpTsData->Tsid, pTmpTsData->NetworkId, &satSDSD))
    {
        retVal = TRUE;
    }
    else
    {
        TraceNotice(m,"SDSD entry removed from NIT ONID %d TSID %d NID %d\n",
                                pTmpTsData->OriginalNetworkId, pTmpTsData->Tsid, pTmpTsData->NetworkId);
    }
    return retVal;
}


Bool CHsvDvbsOpProfile_mAcq::mIsSvcPresentInServiceList (HsvPgdatDigServiceData *pSvcdata)
{
    Bool retVal = FALSE;
    HSVSPTYPE(CamNITService, dvb, camnit) camService;

    if (TRUE == strapi->GetByKey (HsvMain, HSVSPID(CamNITService, dvb, camnit), pSvcdata->OriginalNetworkId, 
                     pSvcdata->Tsid, pSvcdata->ServiceId, (void *)(&camService)))
    {
        retVal = TRUE;
    }
    else
    {
        TraceNotice (m,"Service not present in BAT SLD\n");
    }

    return retVal;
}


int CHsvDvbsOpProfile_mAcq::mCalculateBandwidthFromSdsd (Nat8 rollOff, int symbolRate, Nat8 fecInner)
{
    double bandWidth = 0;

    if (IS_VALID_ROLLOFF(rollOff))
    {
        /* SB = SR(1+Ro) */
        bandWidth = symbolRate * (1+RollOffTable[rollOff]);
    }
    bandWidth /= 1000;  /* To make it in KHz */
    UNUSED (fecInner);

    return (Nat8)bandWidth;
}

int CHsvDvbsOpProfile_mAcq::mConvertToPgdatServiceType (int serviceType)
{
    int pgDatSvcType = serviceType;

    switch(serviceType)
    {
    case TelevisionService:
        pgDatSvcType = AppApiTelevisionService;
        break;
    case RadioService:
        pgDatSvcType = AppApiRadioService;
        break;
    case AdvCodecRadioService:
        pgDatSvcType = AppApiAdvCodecRadioService;
        break;
    case TeletextService:
        pgDatSvcType = AppApiTeletextService;
        break;
    case NVODTimeShiftedService:
        pgDatSvcType = AppApiNVODTimeshiftedService;
        break;
    case NVODReferenceService:
        pgDatSvcType = AppApiNVODReferenceService;
        break;
    case MosaicService:
        pgDatSvcType = AppApiMosaicService;
        break;
    case DatabroadcastService:
        pgDatSvcType = AppApiDatabroadcastService;
        break;
    case DVBMHPService:
        pgDatSvcType = AppApiDVBMHPService;
        break;
    case MPEG2HDService:
        pgDatSvcType = AppApiMPEG2HDService;
        break;
    case AdvCodecSDTelevisionService:
        pgDatSvcType = AppApiAdvCodecSDTelevisionService;
        break;
    case AdvCodecSDNVODTimeShiftedService:
        pgDatSvcType = AppApiAdvCodecSDNVODTimeShiftedService;
        break;
    case AdvCodecSDNVODReferenceService:
        pgDatSvcType = AppApiAdvCodecSDNVODReferenceService;
        break;
    case AdvCodecHDTelevisionService:
        pgDatSvcType = AppApiAdvCodecHDTelevisionService;
        break;
    case AdvCodecHDNVODTimeShiftedService:
        pgDatSvcType = AppApiAdvCodecHDNVODTimeShiftedService;
        break;
    case AdvCodecHDNVODReferenceService:
        pgDatSvcType = AppApiAdvCodecHDNVODReferenceService;
        break;
    case 0x1C:
        pgDatSvcType = AppApiTelevisionService;
        break;
    default:
        break;
    }
    return pgDatSvcType;
}

Bool CHsvDvbsOpProfile_mAcq::mIsDigitalTvChannel (HsvPgdatDigServiceData *pSvcData)
{
    Bool retVal = FALSE;

    TraceNotice (m, "%s() : ServiceType %d \n", __FUNCTION__, pSvcData->ServiceType);
    
    switch (pSvcData->ServiceType)
    {
    case    AppApiTelevisionService:
    case    AppApiTeletextService:
    case    AppApiMPEG2HDService:
    case    AppApiAdvCodecHDTelevisionService:
    case    AppApiAdvCodecSDTelevisionService:
        retVal = TRUE;
        break;
    default:
        break;
    }
    TraceNotice (m, "%s() : IsDigitalTvChannel %s \n", __FUNCTION__, ((retVal == TRUE) ? "True" : "False"));
    return retVal;
}

Bool CHsvDvbsOpProfile_mAcq::mIsDigitalRadioService (HsvPgdatDigServiceData *pSvcData)
{
    Bool retVal = FALSE;

    TraceNotice (m, "%s() : ServiceType %d \n", __FUNCTION__, pSvcData->ServiceType);
    
    switch (pSvcData->ServiceType)
    {
    case AppApiRadioService:
    case AppApiAdvCodecRadioService:
        retVal = TRUE;
        break;
    default:
        break;
    }
    TraceNotice (m, "%s() : IsDigitalRadioChannel %s \n", __FUNCTION__, ((retVal == TRUE) ? "True" : "False"));
    return retVal;
}

Bool CHsvDvbsOpProfile_mAcq::mIsServiceInstallable (HSVSPTYPE(CamNITService, dvb, camnit) *service)
{
    Bool lRetVal = FALSE;

    TraceNotice (m, "%s() : ServiceType %d \n", __FUNCTION__, service->ServiceType);
    
    switch(service->ServiceType)
    {
        case TelevisionService:
        case RadioService:
        case AdvCodecSDTelevisionService:
        case AdvCodecHDTelevisionService:
        case DatabroadcastService:
	case AppApiHevcService:
            lRetVal = TRUE;
            break;
        default:
            break;
    }
    return lRetVal;
}


Bool CHsvDvbsOpProfile_mAcq::mIsManualInstall (void)
{
    int mode, state;

    rins->GetCurrentInstallationState(&mode, &state);

    return ((IHsvSatelliteInstallation_InstallationManual == mode) ? TRUE : FALSE);
}

Bool CHsvDvbsOpProfile_mAcq::mIsUpdateInstall (void)
{
    int mode, state;
    Bool lRetVal = FALSE;

    rins->GetCurrentInstallationState(&mode, &state);

    switch(mode)
    {
        case IHsvSatelliteInstallation_InstallationUpdate:
        case IHsvSatelliteInstallation_InstallationAutomaticUpdate:
        case IHsvSatelliteInstallation_InstallationBackgroundUpdate:
        case IHsvSatelliteInstallation_InstallationBackground:
            lRetVal = TRUE;
            break;
        default:
            break;
    }
    
    return lRetVal;
}

Bool CHsvDvbsOpProfile_mAcq::mIsBackgroundUpdateInstall (void)
{
    int mode, state;

    rins->GetCurrentInstallationState(&mode, &state);

    return ((IHsvSatelliteInstallation_InstallationBackground == mode) ? TRUE : FALSE); 
}


void CHsvDvbsOpProfile_mAcq::mCopyString (Nat16 *dest, Nat16 *src, int maxChars)
{
    int i = 0;
    for(i = 0; i < maxChars; ++i)
    {
        *dest++ = *src++;
    }
    *dest = '\0';
}


/*****************************************************************************************
 * Public methods
 *****************************************************************************************/

// Overridden IHsvPower methods

void CHsvDvbsOpProfile_mAcq::Init (void)
{
    TraceNotice (m, " %s()\n", __FUNCTION__);
    mDataAcqPump = m_pfac.PmpCreate (pen->PumpEngine(), &CHsvDvbsOpProfile_mAcq::mPumpHandler, FALSE, (char *)"hsvdvbsopprofile_mDataAcq", this);    
}

void CHsvDvbsOpProfile_mAcq::TurnOn (void)
{
    TraceNotice (m, " %s()\n", __FUNCTION__);
}

void CHsvDvbsOpProfile_mAcq::TurnOff (void)
{
    TraceNotice (m, " %s()\n", __FUNCTION__);
}


// Overridden IHsvDigitalAcquisition methods

void CHsvDvbsOpProfile_mAcq::Initialise (int lnbNumber)
{
    // Resetting all static variables
    mDigitalChannelsFound = 0;
    mDigitalTvChannelsFound = 0;
    mDigitalRadioChannelsFound = 0;
    mRemoveCurTv = 0;
    mRemoveCurRadio = 0;

    UNUSED(lnbNumber);
}

void CHsvDvbsOpProfile_mAcq::AcquireData (int mode)
{
    TraceNotice (m,"%s() %d \n", __FUNCTION__, __LINE__);
    m_pfac.PmpSend (mDataAcqPump, EvStartAcquire, (Nat32)mode);
    UNUSED (mode);
}

int CHsvDvbsOpProfile_mAcq::GetNumberOfDigitalChannelsFound (void)
{
    TraceNotice (m,"%s() %d > DigitalChannels Added[%d]", __FUNCTION__, __LINE__, mDigitalChannelsFound);
    return mDigitalChannelsFound;
}

int CHsvDvbsOpProfile_mAcq::GetNumberOfDigitalChannelsRemoved (void)
{
    return 0;
}

int CHsvDvbsOpProfile_mAcq::GetNumberOfTvChannelsFound (void)
{
    TraceNotice (m,"%s() %d > Tv Added[%d]", __FUNCTION__, __LINE__, mDigitalTvChannelsFound);
    return mDigitalTvChannelsFound;
}

int CHsvDvbsOpProfile_mAcq::GetNumberOfRadioChannelsFound (void)
{
    TraceNotice (m,"%s() %d > Radio Added[%d]", __FUNCTION__, __LINE__, mDigitalRadioChannelsFound);
    return mDigitalRadioChannelsFound;
}

int CHsvDvbsOpProfile_mAcq::GetNumberOfTvChannelsRemoved (void)
{
    TraceNotice (m,"%s() %d > Tv Removed[%d]", __FUNCTION__, __LINE__, mRemoveCurTv);
    return mRemoveCurTv;
}

int CHsvDvbsOpProfile_mAcq::GetNumberofRadioChannelsRemoved (void)
{
    TraceNotice (m,"%s() %d > Radio Removed[%d]", __FUNCTION__, __LINE__, mRemoveCurRadio);
    return mRemoveCurRadio;
}

int CHsvDvbsOpProfile_mAcq::GetNumberOfSdsds (void)
{
    TraceNotice (m,"%s() %d > Num SDSDs[%d]", __FUNCTION__, __LINE__, mCamDSDesc.numSDSD);
    return mCamDSDesc.numSDSD;
}

Bool CHsvDvbsOpProfile_mAcq::GetSdsdByIndex (int index, HsvNITSatelliteDS	*SdSdEntry)
{
    Bool retVal = FALSE;

    if(index < mCamDSDesc.numSDSD)
    {
        memcpy(SdSdEntry,&mCamDSDesc.SatDesc[index], sizeof(HsvNITSatelliteDS));

        mCamDSDesc.CurrentSDSDIndex = index;
        retVal = TRUE;
    }

    return retVal;
}

int CHsvDvbsOpProfile_mAcq::GetNumberOfTvChannelsInLnb (int lnb)
{
    UNUSED (lnb);
    return mDigitalTvChannelsFound;
}

int CHsvDvbsOpProfile_mAcq::GetNumberOfRadioChannelsInLnb (int lnb)
{
    UNUSED (lnb);
    return mDigitalRadioChannelsFound;	
}

void CHsvDvbsOpProfile_mAcq::AcquireDataOnTimeout (void)
{
    // Do nothing
}

void CHsvDvbsOpProfile_mAcq::AssignLCN(HsvPgdatDigServiceData *psvcdat)
{
    // Do nothing
}

void CHsvDvbsOpProfile_mAcq::GetTricolorRegionNames (Nat16 **names, int *len)
{
    // Do nothing
}

int CHsvDvbsOpProfile_mAcq::StoreBarkerMuxDetails (void)
{
    return 0;
}

void CHsvDvbsOpProfile_mAcq::SyncTemporaryTableRecords (void)
{
    // Do nothing
}
