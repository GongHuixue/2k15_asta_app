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
#include "CHsvDvbsFreesat_mAcq.h"

/*****************************************************************************************
* Macros and types
*****************************************************************************************/
TRACESYMBOL(m, "installation/hsvdvbsfreesat/hsvdvbsfreesat_mAcq")


/****************************************************************************
* Static variables
****************************************************************************/
Pump CHsvDvbsFreesat_mAcq::mDataAcqPump = 0xFFFF;

CHsvDvbsFreesat_mAcq::FreesatSatDSDesc CHsvDvbsFreesat_mAcq::mFreesatDSDesc;
CHsvDvbsFreesat_mAcq::FreesatServiceList CHsvDvbsFreesat_mAcq::mSvcListData;


int CHsvDvbsFreesat_mAcq::mDigitalChannelsFound = 0;
int CHsvDvbsFreesat_mAcq::mDigitalTvChannelsFound = 0;
int CHsvDvbsFreesat_mAcq::mDigitalRadioChannelsFound = 0;
int CHsvDvbsFreesat_mAcq::mRemoveCurTv = 0;
int CHsvDvbsFreesat_mAcq::mRemoveCurRadio =0;
Nat16 CHsvDvbsFreesat_mAcq::mUnicodeBuffer[11];

CHsvDvbsFreesat_mAcq::HsvDataAcqInstance CHsvDvbsFreesat_mAcq::DataAcqInstance;
HsvInstallationPTC CHsvDvbsFreesat_mAcq::CurrentPTC;


double CHsvDvbsFreesat_mAcq::RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};

HsvBarkerMuxData CHsvDvbsFreesat_mAcq::BarkerMuxData;

#define FLAG 0

/****************************************************************************
* Static functions
****************************************************************************/

void CHsvDvbsFreesat_mAcq::mPumpHandler (int value, Nat32 param)
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


void CHsvDvbsFreesat_mAcq::mStartAcquisition (void)
{
	mPopulateSatelliteLnbNumber (ASTRA_28_2_E);

	mCollectSdsds();

	m_pfac.PmpSend (mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
	
	mPopulateHomingServiceTable();

	Bool retval = mCollectFreesatBarkerMuxData();
	TraceNotice(m,"Barker mux data collection for Freesat %s", (retval == TRUE)?"Success" : "Failed");
}

Bool CHsvDvbsFreesat_mAcq::mCollectFreesatBarkerMuxData(void)
{
	Bool RetVal = FALSE;
	
	int index = 0;
	HomingMuxData HomingData;

	memset(&HomingData,0x00,sizeof(HomingData));
	
	if(iutil->ReadBarkerMuxData(&BarkerMuxData) == FALSE)
	{
		BarkerMuxData.NoOfRecords = 0;
	}
	
	BarkerMuxData.NoOfRecords++; 
	TraceNotice(m, " %d : BarkerMuxData.NoOfRecords = %d", __LINE__, BarkerMuxData.NoOfRecords);


	if(iscansdsd->GetHomingData((void*)&HomingData))
	{
		TraceNotice(m,"[%d] [%d] [%d]",HomingData.Frequency,HomingData.Polarization,HomingData.SatelliteId);
		BarkerMuxData.Mux[0].Params.TuningParams.DVBSParam.Frequency = HomingData.Frequency;
		BarkerMuxData.Mux[0].Params.TuningParams.DVBSParam.sat_id = HomingData.SatelliteId;
		BarkerMuxData.Mux[0].Params.TuningParams.DVBSParam.tp_id = CREATE_TPID(HomingData.SatelliteId,HomingData.Frequency,HomingData.Polarization);
		RetVal = TRUE;
	}
	
	return RetVal;
}

void CHsvDvbsFreesat_mAcq::mPopulateSatelliteLnbNumber (int satId)
{
	int lnbNumber = 0;
	HsvPgdatDigSatInfoData satDetails;

	for(lnbNumber = 0; lnbNumber < MAX_LNBS_SUPPORTED; ++lnbNumber)
	{
		pgdb->Initialise (IHsvProgramDatabaseConstants_SatInfo, (Address) &satDetails);
		satDetails.LnbNumber = lnbNumber;

		if (TRUE == pgdb->GetByKey (SAT_INFO_TABLE, (Address) &satDetails))
		{
			if(satDetails.SatelliteId == satId)
			{
				DataAcqInstance.LnbNumber = lnbNumber;
				break;
			}
		}
		else
		{
			TraceNotice (m," ERROR: Getting Sat. details failed for LNB: %d!!! \n", lnbNumber);
		}
	}
}


void CHsvDvbsFreesat_mAcq::mCollectSdsds (void)
{
	int numSDSD = 0;
	int loopCount = 0;
	int sdsdLoopCount = 0;
	Bool addSDSDEntry =  FALSE;
	int startCount = 0;
	int endCount = 0;
	HSVSPTYPE(SatelliteDS,dvb,nit) satSDSD;

	numSDSD = strapi->GetSize (HsvMain,  HSVSPID(SatelliteDS, dvb, nit));
	mFreesatDSDesc.numSDSD = 0;

	TraceNotice (m," Number of SDSD %d\n", numSDSD);

	for(sdsdLoopCount = 0; sdsdLoopCount < numSDSD; ++sdsdLoopCount)
	{
		if(strapi->GetByIndex (HsvMain, HSVSPID(SatelliteDS, dvb, nit), sdsdLoopCount, (void*)&satSDSD))
		{
			addSDSDEntry =  TRUE;

			TraceDebug (m,"SDSD Entry ONID 0x%x NID 0x%x TSID 0x%x\n", \
			satSDSD.Original_NetworkId, satSDSD.NetworkId, satSDSD.Tsid);
			for(loopCount = 0; loopCount < mFreesatDSDesc.numSDSD; ++loopCount)
			{
				// search for existing entry before adding new entry
				if((mFreesatDSDesc.SatDesc[loopCount].Original_NetworkId == satSDSD.Original_NetworkId) &&
						(mFreesatDSDesc.SatDesc[loopCount].NetworkId == satSDSD.NetworkId) &&
						(mFreesatDSDesc.SatDesc[loopCount].Tsid == satSDSD.Tsid))
				{
					// Entry already available
					addSDSDEntry = FALSE;
					TraceNotice (m,"SDSD entry already present\n");
					break;
				}
			}

			if (addSDSDEntry)
			{
				startCount = 0;
				endCount = 0;

				// Add only the valid services present in BAT SLD list
				if(strapi->GetRangeByKey (HsvMain, HSVSPID(ActualServiceList, dvb, bat), 2,
							satSDSD.Original_NetworkId, satSDSD.Tsid, 0, &startCount, &endCount))
				{
					memcpy (&(mFreesatDSDesc.SatDesc[mFreesatDSDesc.numSDSD]), &satSDSD, sizeof(HSVSPTYPE(SatelliteDS,dvb,nit)));
					++mFreesatDSDesc.numSDSD;
					TraceDebug (m,"SDSD Entry Added ONID 0x%x NID 0x%x TSID 0x%x",  \
					satSDSD.Original_NetworkId,  satSDSD.NetworkId, satSDSD.Tsid);
				}
				else
				{
					TraceNotice (m, "Get range of service from SLD list failed");
				}
			}
		}
	}

	DataAcqInstance.CurSdsd = 0;
	DataAcqInstance.NumSdsds = mFreesatDSDesc.numSDSD;
	TraceNotice (m," DataAcqInstance.NumSdsds %d \n", DataAcqInstance.NumSdsds);
}


void CHsvDvbsFreesat_mAcq::mPopulateCurrentService (void)
{
#if FLAG
	HsvSource  source;
	HsvChannel channelNo;
	FResult	retVal;
	int tpId, serviceId;

	pgsel_GetCurrentProgram(HsvMain,&source,&channelNo);

	retVal = pgdat3_GetChannelDataInt(channelNo, pgdat3_Nat32TPID, &tpId);
	retVal = (err_Ok == retVal) ? pgdat3_GetChannelDataInt(channelNo, pgdat3_IntServiceId, &serviceId) : retVal;

	if (err_Ok == retVal)
	{
		DataAcqInstance.CurrService.Tpid	    = tpId;
		DataAcqInstance.CurrService.ServiceId	= serviceId;

		retVal = pgdb_GetByKey (SERVICE_TABLE, (Address) &DataAcqInstance.CurrService);
	}
#endif
}


void CHsvDvbsFreesat_mAcq::mAcquireTSInfo (void)
{
	HSVSPTYPE(SatelliteDS,dvb,nit) currentSdsd;
	Bool isSdsdChange = FALSE;
	HsvPgdatDigTSData oldTsData;

	pgdb->Initialise(IHsvProgramDatabaseConstants_DigitalTS, (Address) &oldTsData);

	TraceNotice(m, "DataAcqInstance.CurSdsd %d, DataAcqInstance.NumSdsds %d, sizeof(CurrentSdsd) %d\n",
	DataAcqInstance.CurSdsd, DataAcqInstance.NumSdsds,sizeof(currentSdsd));
	if(DataAcqInstance.CurSdsd < DataAcqInstance.NumSdsds)
	{
		memcpy(&currentSdsd, &mFreesatDSDesc.SatDesc[DataAcqInstance.CurSdsd], sizeof(HsvNITSatelliteDS));

		DataAcqInstance.NetworkId = currentSdsd.NetworkId;
		DataAcqInstance.OnId	  = currentSdsd.Original_NetworkId;
		DataAcqInstance.TsId      = currentSdsd.Tsid;
		// For Freesat, PTC info is built within Acq. module as no tuning to SDSD is required
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
		// Delete services from all deleted muxes, in current version of BAT
		// delete the service atleast if one valid service (one valid mux) present in BAT,
		// otherwise the retain existing service list
		if((TRUE == mIsUpdateInstall()) && (0 < DataAcqInstance.NumSdsds))
		{
			mDeleteServicesFromDeletedMuxesInCurrentBAT();
		}
		m_pfac.PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);
	}
	else
	{
		m_pfac.PmpSend(mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
	}
}

void CHsvDvbsFreesat_mAcq::mPopulateHomingServiceTable (void)
{
	HsvFreesatHomingServiceData homSvcData;
	HsvFreesatLinkageInfo linkageInfo; // LD info
	HsvFreesatInfoLocation locationInfo; // ILD info
	HSVSPTYPE(SatelliteDS,dvb,nit) sdsdInfo;
	int numLinkageInfo = 0;
	int numLocationInfo = 0;
	int loopCount = 0;
	
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	numLinkageInfo = strapi->GetSize (HsvMain, HSVSPID(FreesatLinkageInfo, dvb, nit));
	numLocationInfo = strapi->GetSize (HsvMain, HSVSPID(FreesatInfoLocation, dvb, bat));

	//TraceNotice(m,"TMP_DEBUG numLinkageInfo %d numLocationInfo %d",numLinkageInfo, numLocationInfo);
	
	memset(&homSvcData,0x00,sizeof(HsvFreesatHomingServiceData));

	if(numLinkageInfo != 0)
	{
		//Update Freesat LD info
		for (loopCount = 0; loopCount < numLinkageInfo; loopCount++)
		{
			if (strapi->GetByIndex(HsvMain, HSVSPID(FreesatLinkageInfo, dvb, nit), loopCount, (void *)&linkageInfo))
			{
				if (strapi->GetByKey(HsvMain, HSVSPID(SatelliteDS, dvb, nit), linkageInfo.OriginalNetworkId,
							linkageInfo.Tsid, linkageInfo.NetworkId, (void *)&sdsdInfo))
				{
					homSvcData.HomingServices[loopCount].OnId 				= linkageInfo.OriginalNetworkId;
					homSvcData.HomingServices[loopCount].TsId 				= linkageInfo.Tsid;
					homSvcData.HomingServices[loopCount].ServiceId 			= linkageInfo.ServiceId;
					homSvcData.HomingServices[loopCount].LNBNumber 			= DataAcqInstance.LnbNumber;
					homSvcData.HomingServices[loopCount].Frequency 			= sdsdInfo.Frequency;
					homSvcData.HomingServices[loopCount].Polarization 		= sdsdInfo.Polarization;
					homSvcData.HomingServices[loopCount].HomingServiceType 	= LD;
				}
				else
				{
					TraceNotice (m, "LD Entry not present in SatelliteDS for sid %d\n",linkageInfo.ServiceId);
				}
			}
		}
	}
	else
	{
		TraceNotice(m,"Linkage Info List Empty !!!");
	}

	homSvcData.LinkageServiceCount = numLinkageInfo;
	isettings->SetAttribute(IHsvSatelliteSettings_AttributeFreesatHomingServiceData,(Nat32)&homSvcData);

	//Update Freesat ILD info
	
	if(numLocationInfo != 0)
	{
		for (loopCount = numLinkageInfo ; loopCount < numLocationInfo + numLinkageInfo; loopCount++)
		{
			if (TRUE == strapi->GetByIndex (HsvMain, HSVSPID(FreesatInfoLocation, dvb, bat), (loopCount - numLinkageInfo), (void *)&locationInfo))
			{
				if (strapi->GetByKey(HsvMain, HSVSPID(SatelliteDS, dvb, nit), locationInfo.OriginalNetworkId,
							locationInfo.Tsid, 0x3B, (void *)&sdsdInfo))
				{
					homSvcData.HomingServices[loopCount].OnId 				= locationInfo.OriginalNetworkId;
					homSvcData.HomingServices[loopCount].TsId 				= locationInfo.Tsid;
					homSvcData.HomingServices[loopCount].ServiceId 			= locationInfo.ServiceId;
					homSvcData.HomingServices[loopCount].LNBNumber 			= DataAcqInstance.LnbNumber;
					homSvcData.HomingServices[loopCount].Frequency 			= sdsdInfo.Frequency;
					homSvcData.HomingServices[loopCount].Polarization		= sdsdInfo.Polarization;
					homSvcData.HomingServices[loopCount].HomingServiceType 	= ILD;
				}
				else
				{
					TraceNotice (m, "ILD Entry not present in SatelliteDS for sid %d\n",locationInfo.ServiceId);
				}
			}
		}
	
	}
	else
	{
		TraceNotice(m,"Location Info List Empty !!!");
	}

	homSvcData.InfoLocationServiceCount = numLocationInfo;
	isettings->SetAttribute(IHsvSatelliteSettings_AttributeFreesatHomingServiceData,(Nat32)&homSvcData);
}


void CHsvDvbsFreesat_mAcq::mGetPTCInfo (HSVSPTYPE(SatelliteDS,dvb,nit) Sdsd, HsvInstallationPTC *ptc)
{
	int	TransponderFreq = 0;

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
void CHsvDvbsFreesat_mAcq::mAddToTSTable (HsvInstallationPTC *ptc, Bool *pIsSdsdChange, HsvPgdatDigTSData *pOldTsData)
{
	HsvPgdatDigTSData tsData, tmpTsData;
	int numTsTables = 0;
	int tsTableCount = 0;

	pgdb->Initialise(IHsvProgramDatabaseConstants_DigitalTS, (Address) &tsData);
	pgdb->Initialise(IHsvProgramDatabaseConstants_DigitalTS, (Address) &tmpTsData);

	// Filling attributes from ptc and acqinstance
	tsData.Frequency			= ptc->Frequency;
	tsData.SymbolRate			= ptc->SymbolRate;

	tsData.OriginalNetworkId	= DataAcqInstance.OnId;
	tsData.Tsid					= DataAcqInstance.TsId;
	tsData.NetworkId			= DataAcqInstance.NetworkId;
	tsData.ModulationType		= ptc->ModulationType;

	tsData.Bandwidth			= ptc->ChannelBandwidth;

	tsData.PtcListVersion		= isvcscandata->GetInstallationVersion();
	tsData.SDSDFrequency		= ptc->SDSDFrequency;
	tsData.UserInstalled		= mIsManualInstall();
	tsData.LnbNumber			= ptc->LnbNumber;
	tsData.Polarization			= ptc->Polarization;
	tsData.Tpid					= ptc->TPID;

	tmpTsData.LnbNumber			= tsData.LnbNumber;
	tmpTsData.Frequency			= tsData.Frequency;
	tmpTsData.Polarization		= tsData.Polarization;

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


Bool CHsvDvbsFreesat_mAcq::mInstallMux (HsvInstallationPTC ptc, Bool isSdsdChange, HsvPgdatDigTSData *pOldTsData)
{
	Bool retVal = FALSE;
	HSVSPTYPE(ActualServiceList, dvb, bat) batSvcList;
	SvcListInfo	svcListInfo;
	int loopCount = 0;
	int startCount = 0;
	int endCount = 0;
	int installedServices = 0;

	if(TRUE == strapi->GetRangeByKey (HsvMain, HSVSPID(ActualServiceList, dvb, bat), 2, DataAcqInstance.OnId,
				DataAcqInstance.TsId, 0, &startCount, &endCount))
	{
		TraceDebug(m, "%s %d NoOfServices in MUX = %d ONID = 0x%x TSID = 0x%x \n", __FUNCTION__, __LINE__, \
		((endCount - startCount)+1), DataAcqInstance.OnId, DataAcqInstance.TsId);

		// From strapi get all the services and add/update in SERVICE_TABLE
		for(loopCount = endCount; loopCount >= startCount; --loopCount)
		{
			if(TRUE == strapi->GetByIndex (HsvMain, HSVSPID(ActualServiceList, dvb, bat), loopCount, (void *)(&batSvcList)))
			{
				svcListInfo.OnId            = batSvcList.Original_NetworkId;
				svcListInfo.TsId            = batSvcList.Tsid;
				svcListInfo.ServiceId       = batSvcList.ServiceId;
				svcListInfo.ServiceType     = batSvcList.ServiceType;
				mSvcListData.VersionNumber  = batSvcList.VersionNumber;

				TraceDebug(m, "ONID 0x%x TSID 0x%x Srv ID 0x%x isSdsdChange %d\n", svcListInfo.OnId, \
				svcListInfo.TsId, svcListInfo.ServiceId, isSdsdChange);

				if (mCheckAndInstallService(&ptc, isSdsdChange, pOldTsData, &svcListInfo))
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


Bool CHsvDvbsFreesat_mAcq::mCheckAndInstallService (HsvInstallationPTC *ptc, Bool isSdsdChange,
HsvPgdatDigTSData *pOldTsData, SvcListInfo *pSvcList)
{
	Bool retVal = FALSE;
	Bool channelExists = FALSE;
	Bool duplicateSvc = FALSE;
	Bool serviceAdded = FALSE;
	Bool toAdd = TRUE;
	int loopCount = 0;
	HSVSPTYPE(OtherSDTSection, dvb, sdt) service;
	HSVSPTYPE(FreesatLCN,dvb,bat) batService;
	HsvPgdatDigServiceData svcData, tempSvcData;

	pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalService, (Address)(&svcData));
	pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalService, (Address)(&tempSvcData));

	for(loopCount = 0; loopCount < MAX_NUM_LCN_ENTRY; ++loopCount)
	{
		svcData.MultipleLCN[loopCount] = FREESAT_INVALID_LCN;
		svcData.MultiplePreset[loopCount] = INVALID_PRESET;
	}
	TraceNotice(m,"TMP_DEBUG %s %d isSdsdChange %d",__FUNCTION__,__LINE__,isSdsdChange);
	// If db key(Tpid) is updated, delete the service and add it again with new Tpid (as Tpid is the key for service table)
	if(TRUE == isSdsdChange)
	{
		svcData.Tpid = pOldTsData->Tpid;
		svcData.ServiceId = pSvcList->ServiceId;

		if(TRUE == pgdb->GetByKeyForFreesat(SERVICE_TABLE, (Address )&svcData))
		{
			duplicateSvc = TRUE;
		}
	}
	else
	{
		svcData.Tpid = ptc->TPID;
		svcData.ServiceId = pSvcList->ServiceId;
		TraceNotice(m,"svcData.Tpid %d,svcData.ServiceId 0x%x",svcData.Tpid,svcData.ServiceId);
		pgdb->GetByKey(SERVICE_TABLE, (Address )&svcData);
	}

	for(loopCount = 0; loopCount < MAX_NUM_LCN_ENTRY; loopCount++)
	{
		TraceNotice(m,"svcData.MultipleLCN[%d] : %d",loopCount,svcData.MultipleLCN[loopCount]);
	}
	
	svcData.Frequency		  	= ptc->Frequency;
	svcData.OriginalNetworkId 	= DataAcqInstance.OnId;
	svcData.Tsid 			  	= DataAcqInstance.TsId;
	svcData.LnbNumber 		 	= ptc->LnbNumber;
	svcData.Polarization 		= ptc->Polarization;
	svcData.Tpid	       	  	= ptc->TPID;
	svcData.ServiceId			= pSvcList->ServiceId;
	
	// For Freesat service visibility is taken from regionalised_logical_channel_descriptor and differs for each LCN
	// Hence handled in mAssignLCN()
	//svcData.VisibleService 		= TRUE;
	svcData.NetworkId			= DataAcqInstance.NetworkId;
	svcData.SDSDFrequency		= ptc->SDSDFrequency;

	// For Freesat if service is persent in BAT but not availabe in SDT, then add the service with empty service name
	memset(&service, 0, sizeof(HSVSPTYPE(OtherSDTSection, dvb, sdt)));
	 
	// Copying is done to keep the existing name, if the service is removed from SDT
	mCopyString(service.ServiceName, svcData.ChannelName, (eurdiv->PresetNameLength() - 1));

	//For freesat, ServiceType should be taken from BAT SLD
	service.ServiceType = pSvcList->ServiceType;

	if(FALSE == mIsServiceInstallable (pSvcList))
	{
		toAdd = FALSE;
		TraceNotice (m, "service is not installable onid: %d, tsid: %d, svcid: %d\n", \
									svcData.OriginalNetworkId, svcData.Tsid, svcData.ServiceId );
	}

	// For Freesat services, service name has to be updated from SDTOther
	// Hence get entry from SDT other
	if(TRUE == strapi->GetByKey(HsvMain, HSVSPID(OtherSDTSection, dvb, sdt),
				svcData.OriginalNetworkId, svcData.ServiceId, svcData.Tsid, (void *)(&service)))
	{
		
		if(service.ServiceName[0] != 0)
		{
			mCopyString(svcData.ChannelName,service.ServiceName,(eurdiv->PresetNameLength() - 1));
			TraceDebug(m, "SDT OTHER available for svcId: %d, svcType: %d servicename %x\n", service.ServiceId, service.ServiceType,*service.ServiceName);
		}
		else
		{
			if(!mIsUpdateInstall())
			{
				TraceNotice(m,"service present in SDT other but service name is NULL(DTG test suite use case).. this is too much ha!!");
				mCopyString(svcData.ChannelName,mAsciiToUnicode("-----", 5), 5);
			}
		}
	
	}
	else
	{
		if(!mIsUpdateInstall())
		{
			TraceNotice(m,"SDT other not available in Auto Installation");
			mCopyString(svcData.ChannelName,mAsciiToUnicode("-----", 5), 5);
		}
	}

	if(strapi->GetByKey (HsvMain, HSVSPID(FreesatLCN, dvb, bat), svcData.OriginalNetworkId,
				svcData.Tsid, svcData.ServiceId, (void*)(&batService)))
	{
			TraceNotice(m,"FreesatServiceIdentifier %d",batService.FreeSatelliteServiceIdentifier);
			tempSvcData.FreesatServiceIdentifier = batService.FreeSatelliteServiceIdentifier;
			svcData.FreesatServiceIdentifier = batService.FreeSatelliteServiceIdentifier;
			
	}
	else
	{
		TraceNotice(m,"RLCD is not present for service. So FSID : 0x%x",svcData.FreesatServiceIdentifier);
		toAdd = FALSE;
	}

	if(toAdd == TRUE)
	{

		//For a freesat service , if theres an update in TSID or SID, service shall be considered as a moved service as long as
		// free_satellite_service_identifier is not changed .Moved service shall retain user set attributes( favourite list/timers/channel lock) .
		channelExists = pgdb->GetByKeyForFreesat(SERVICE_TABLE,(Address)&tempSvcData);
		TraceDebug (m, "tpId 0x%x svcId 0x%x channelExists %d\n", tempSvcData.Tpid, tempSvcData.ServiceId, channelExists);

		if(channelExists)
		{
			TraceDebug (m, "channelExists for svcId 0x%x and SvcType %d\n", svcData.ServiceId, svcData.ServiceType);
			// If entry already present update the service data
			mUpdateService (&svcData, ptc, &service);
			retVal = TRUE;

		}
		else
		{
			mAddNewService(&svcData, ptc, &service,duplicateSvc);
			serviceAdded = TRUE;
			retVal = TRUE;
		}

	}
	else
	{
		// if service type is not valid then delete the service from database, also
		// delete it's preset table entry
		//tempSvcData.Tpid	    = svcData.Tpid;
		//tempSvcData.ServiceId	= svcData.ServiceId;
				
		tempSvcData.FreesatServiceIdentifier = svcData.FreesatServiceIdentifier;
		

		if(pgdb->GetByKeyForFreesat(SERVICE_TABLE, (Address)&tempSvcData))
		{
			mDeleteService(&tempSvcData, FALSE);
		}
	}
	if (duplicateSvc)
	{
		// Delete the duplicate service with old tpId, svcId
		pgdb->Initialise(IHsvProgramDatabaseConstants_DigitalService, (Address)(&tempSvcData));
		tempSvcData.Tpid      = pOldTsData->Tpid;
		tempSvcData.ServiceId = pSvcList->ServiceId;
		if(pgdb->GetByKey(SERVICE_TABLE, (Address)&tempSvcData))
		{
			mDeleteService(&tempSvcData, TRUE);
		}
	}
	return retVal;
}


Nat16* CHsvDvbsFreesat_mAcq::mAsciiToUnicode(char *ascii_str,int length)
{
	int loop = 0;
    while( loop < length )
    {
        mUnicodeBuffer[loop] = ascii_str[loop];
        ++loop;
    }
	return  mUnicodeBuffer;
}

void CHsvDvbsFreesat_mAcq::mAddNewService (HsvPgdatDigServiceData *pSvcData ,HsvInstallationPTC *ptc,
HSVSPTYPE(OtherSDTSection, dvb, sdt) *service, Bool duplicateSvc)
{
	HsvPgdatPresetData presetData;
	int loopCount = 0;

	// Filling details of service, then adding it
	mAssignSvcBroadcastAttributes (pSvcData, ptc,service);
	mUpdateSatelliteName (pSvcData);
	mAssignLCN(pSvcData, FALSE);
	//User attributes should be retained for duplicate service
	if(FALSE == duplicateSvc)
	{
		mAssignSvcNonBroadcastAttributes(pSvcData);
	}
	// if service entry is present only in BAT, but not availabe in SDT actual/other then service type will be empty
	// in that case also we have add service
	// Add to service table
	pgdb->Add(SERVICE_TABLE, (Address )pSvcData);
	TraceDebug(m,"Added Service:Name %s ONID:0x%x TSID 0x%x SVCID:0x%x SystemHidden = %d LCN %d %d %d %d %d %d %d %d Preset %d %d %d %d %d %d %d %d\n", pSvcData ->ChannelName, \
	pSvcData->OriginalNetworkId, pSvcData->Tsid, pSvcData->ServiceId,pSvcData->SystemHidden, pSvcData->MultipleLCN[0], pSvcData->MultipleLCN[1], pSvcData->MultipleLCN[2],pSvcData->MultipleLCN[3], pSvcData->MultipleLCN[4],
	pSvcData->MultipleLCN[5], pSvcData->MultipleLCN[6], pSvcData->MultipleLCN[7], pSvcData->MultiplePreset[0], pSvcData->MultiplePreset[1], pSvcData->MultiplePreset[2],pSvcData->MultiplePreset[3], pSvcData->MultiplePreset[4],
	pSvcData->MultiplePreset[5], pSvcData->MultiplePreset[6], pSvcData->MultiplePreset[7]);

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

void CHsvDvbsFreesat_mAcq::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *pSvcData, HsvInstallationPTC *ptc,
HSVSPTYPE(ActualTSService, dvb, sdt) *service)
{
	pSvcData->ModulationType 	= ptc->ModulationType;
	pSvcData->Bandwidth 		= ptc->ChannelBandwidth;

	pSvcData->SymbolRate 		= ptc->SymbolRate;
	pSvcData->LnbNumber 		= ptc->LnbNumber;
	pSvcData->Polarization 		= ptc->Polarization;
	pSvcData->Tpid				= ptc->TPID;
	pSvcData->AudioPid          = INVALID_PID;
	pSvcData->VideoPid          = INVALID_PID;
	pSvcData->PcrPid            = INVALID_PID;
	pSvcData->ServiceType       = mConvertToPgdatServiceType(service->ServiceType);

	pSvcData->FreeCiMode	    = service->Free_Ci_Mode;
	pSvcData->MatchBrandFlag    = service->Match_Brand_Flag;
	pSvcData->NumBrandIds       = service->NumBrandIds;
	mCopyString (pSvcData->BrandIds, service->Brand_Ids, service->NumBrandIds);

	pSvcData->ScrambledStatus	= 0;
	if (TRUE == service->Free_CA_Mode)
	{
		pSvcData->ScrambledStatus = 1;
	}
	

	/*For Freesat ServiceVisibility & NumericSelect differs for each LCN and hence kept as an array but SystemHidden is still scalar;
	So no point in updating SystemHidden here
	pSvcData->NumericSelect 	= TRUE;
	pSvcData->SystemHidden 	= !(pSvcData->VisibleService);*/

}

void CHsvDvbsFreesat_mAcq::mAssignSvcNonBroadcastAttributes (HsvPgdatDigServiceData* pSvcData)
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
	pSvcData->NewPreset = (mode == AUTO_MODE)? FALSE : TRUE;
	pSvcData->HbbTvOption = 1;

	pSvcData->ServiceListVersion = mSvcListData.VersionNumber;
	pSvcData->PackageGroup = APPAPISAT_Freesat;

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
			if(FREESAT_INVALID_LCN != svcData.MultipleLCN[loopCount])
			{
				REVALIDATE(svcData.MultipleLCN[loopCount]);
				proceed = ((VALID_LCN_RANGE(pSvcData->MultipleLCN[loopCount]) ||
							VALID_LCN_RANGE(svcData.MultipleLCN[loopCount])) &&
											(pSvcData->MultipleLCN[loopCount] != svcData.MultipleLCN[loopCount]));
				if(proceed)
				{
					TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d\n", __FUNCTION__, __LINE__, \
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

// Invalid LCN
// Unwanted next LCN
// why 0s
//If package is Freesat, only services with valid LCN shall be installed.
//Non honored services shall NOT be installed. Also, LCN range 0 to 4095 only shall be supported .
//Return TRUE for valid LCN services so that it will get added in SERVICE_TABLE
void CHsvDvbsFreesat_mAcq::mAssignLCN(HsvPgdatDigServiceData *pSvcData, Bool channelExists)
{
	Nat8 numValidLCNOld = 0;
	Nat8 numValidLCNNew = 0;
	Nat8 loopCount = 0;
	Nat8 globalLCNCount = 0;
	Nat16 LogicalChannelNumber[MAX_NUM_LCN_ENTRY];
	HSVSPTYPE(FreesatLCN,dvb,bat) batService;
	Nat16 regionId = 0xFF;
	Bool addLCN = FALSE;
	Bool isVisible = FALSE;
	HsvFreesatServiceGroupInfo freesatSvcGroup;

	for(loopCount = 0; loopCount < MAX_NUM_LCN_ENTRY; loopCount++)
	{
		LogicalChannelNumber[loopCount] = FREESAT_INVALID_LCN;
	}

	// Get the installed regionId from persistence
	regionId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeRegionId);

	for(loopCount = 0; loopCount < MAX_NUM_LCN_ENTRY; loopCount++)
	{
		TraceNotice(m,"psvcData.MultipleLCN[%d] : %d",loopCount,pSvcData->MultipleLCN[loopCount]);
	}

	if(strapi->GetByKey (HsvMain, HSVSPID(FreesatLCN, dvb, bat), pSvcData->OriginalNetworkId,
				pSvcData->Tsid, pSvcData->ServiceId, (void*)(&batService)))
	{

		pSvcData->FreesatServiceIdentifier = batService.FreeSatelliteServiceIdentifier;
		for(loopCount = 0; loopCount < MAX_NUM_LCN_ENTRY; ++loopCount)
		{
			addLCN = FALSE;
			if ((regionId == batService.RegionId[loopCount] || GLOBAL_REGION_ID == batService.RegionId[loopCount]) &&
					VALID_LCN_RANGE(batService.LogicalChannelNumber[loopCount]))
			{
				addLCN  = TRUE;
				++numValidLCNNew;
			}
			if(FREESAT_INVALID_LCN != pSvcData->MultipleLCN[loopCount])
			{
				++numValidLCNOld;
			}
			TraceDebug(m,"LCN old %d, LCN new %d addLCN %d RID %d", pSvcData->MultipleLCN[loopCount], batService.LogicalChannelNumber[loopCount], addLCN, batService.RegionId[loopCount] );
			if (TRUE == addLCN)
			{
				/*LCN ouside the rance 100 -999 and 1100 - 1999 shall not be visible and selectable by user
				**Reference Section 8.2.9 Freesat Requirements for Interoperability Part 3: System Management, version 1.6
				*/
				isVisible = FALSE;
				isVisible = (((100 <= batService.LogicalChannelNumber[loopCount]) && (batService.LogicalChannelNumber[loopCount] <= 999) ||
										(1100 <= batService.LogicalChannelNumber[loopCount]) && (batService.LogicalChannelNumber[loopCount] <= 1999)) ? TRUE : FALSE);
				if (regionId == batService.RegionId[loopCount])
				{
					LogicalChannelNumber[REGIONAL_LCN_INDEX] = batService.LogicalChannelNumber[loopCount];
					pSvcData->MultipleVisibleService[REGIONAL_LCN_INDEX] = ((isVisible) ? batService.VisibleServiceFlag[loopCount] : 0);
					if(pSvcData->MultipleVisibleService[REGIONAL_LCN_INDEX] == 1)
					{
						pSvcData->MultipleNumericSelect[REGIONAL_LCN_INDEX] = 1;
					}
					else
					{
						pSvcData->MultipleNumericSelect[REGIONAL_LCN_INDEX] = ((isVisible) ? batService.NumericSelectionFlag[loopCount]: 0);
					}
					TraceNotice(m,"regional Visibility / NumericSelection: %d %d",pSvcData->MultipleVisibleService[REGIONAL_LCN_INDEX],pSvcData->MultipleNumericSelect[REGIONAL_LCN_INDEX]);
				}
				else
				{
					++globalLCNCount;
					if(globalLCNCount < MAX_NUM_LCN_ENTRY)
					{
						LogicalChannelNumber[globalLCNCount] = batService.LogicalChannelNumber[loopCount];
						pSvcData->MultipleVisibleService[globalLCNCount] = ((isVisible) ? batService.VisibleServiceFlag[loopCount] : 0);
						if(pSvcData->MultipleVisibleService[globalLCNCount] == 1)
						{
							pSvcData->MultipleNumericSelect[globalLCNCount] = 1;
						}
						else
						{
							pSvcData->MultipleNumericSelect[globalLCNCount] = ((isVisible) ? batService.NumericSelectionFlag[loopCount]: 0);
						}
						TraceNotice(m,"Global Visibility / NumericSelection: %d %d",pSvcData->MultipleVisibleService[globalLCNCount],pSvcData->MultipleNumericSelect[globalLCNCount]);
					}
					else
					{
						TraceNotice(m,"Line %d Max nuber of Global LCN reached, skipping LCN ",__LINE__, batService.LogicalChannelNumber[loopCount]);
					}
				}
			}

			
		}

		/*Data is copied to local buffer to avoid multiple numValidLCNOld field increment during update installtion*/
		memcpy(pSvcData->MultipleLCN, LogicalChannelNumber, (sizeof(Nat16) * MAX_NUM_LCN_ENTRY));
		
		TraceDebug(m,"Valid New LCN %d Valid Old LCN %d", numValidLCNNew, numValidLCNOld);

		if(numValidLCNNew >= numValidLCNOld)
		{
			// Check service is TV or Radio
			if (mIsDigitalTvChannel (pSvcData))
			{
				// if the channel already exist, then add only the new LCN entries
				mDigitalTvChannelsFound += ((channelExists) ? (numValidLCNNew - numValidLCNOld) : numValidLCNNew);
			}
			else if (mIsDigitalRadioService (pSvcData))
			{
				mDigitalRadioChannelsFound += ((channelExists) ? (numValidLCNNew - numValidLCNOld) : numValidLCNNew);
			}

			mDigitalChannelsFound += numValidLCNNew;
			TraceNotice(m,"TMP_DEBUG Line %d mDigitalTvChannelsFound %d mDigitalRadioChannelsFound %d mDigitalChannelsFound %d",__LINE__,mDigitalTvChannelsFound, mDigitalRadioChannelsFound, mDigitalChannelsFound);
		}
		else
		{
			// Check service is TV or Radio
			if (mIsDigitalTvChannel (pSvcData))
			{
				mRemoveCurTv += (numValidLCNOld - numValidLCNNew);
			}
			else if (mIsDigitalRadioService (pSvcData))
			{
				mRemoveCurRadio +=  (numValidLCNOld - numValidLCNNew);
			}

			mDigitalChannelsFound += numValidLCNNew;
			TraceNotice(m,"TMP_DEBUG Line %d mDigitalTvChannelsFound %d mDigitalRadioChannelsFound %d mDigitalChannelsFound %d",__LINE__,mDigitalTvChannelsFound, mDigitalRadioChannelsFound, mDigitalChannelsFound);
		}

		// If free_satellite_servicegroup_id = 640(0x280) Adult genre ,then services belonging to that group has ParentalRating service attribute TRUE
		if(TRUE == strapi->GetByKey (HsvMain, HSVSPID(FreesatSrvGroup,dvb,bat), pSvcData->FreesatServiceIdentifier, 0x280, 0, &freesatSvcGroup))
		{
			pSvcData->AdultGenere = TRUE;
		}
	}
	else
	{	
		TraceNotice(m,"Get LCN failed, ONID 0x%x TSID 0x%x SID 0x%x",  pSvcData->OriginalNetworkId, \
		pSvcData->Tsid, pSvcData->ServiceId);
	}

}


void CHsvDvbsFreesat_mAcq::mUpdateService (HsvPgdatDigServiceData* pSvcData, HsvInstallationPTC* ptc,
HSVSPTYPE(OtherSDTSection, dvb, sdt) *service)
{
	mAssignSvcBroadcastAttributes (pSvcData, ptc, service);
	mAssignLCN(pSvcData, TRUE);
	mAssignSvcNonBroadcastAttributes(pSvcData);

	pgdb->Update(SERVICE_TABLE, (Address )pSvcData);
	TraceDebug(m,"Updated Service ONID:%d SVCID:%d\n", pSvcData->OriginalNetworkId, pSvcData->ServiceId);
}


void CHsvDvbsFreesat_mAcq::mUpdateSatelliteName (HsvPgdatDigServiceData *pSvcData)
{
	HsvPgdatDigSatInfoData satInfo;

	satInfo.LnbNumber = pSvcData->LnbNumber;

	if (TRUE == pgdb->GetByKey (SAT_INFO_TABLE, (Address)&satInfo))
	{
		memcpy (pSvcData->SatelliteName, satInfo.SatelliteName, sizeof(pSvcData->SatelliteName));
	}
}


// TO DO : During Background update, check for current viewing service and trigger deletion of the same during next zap
void CHsvDvbsFreesat_mAcq::mDeleteService(HsvPgdatDigServiceData *pSvcData, Bool duplicateService)
{
	int loopCount = 0;
	int numDeletedSvcs = 0;
	HsvPgdatPresetData presetData;
	Bool deleteService = TRUE;

	if (TRUE == mIsBackgroundUpdateInstall () /* && TRUE == mIsCurrentService (*pSvcData) */)
	{
		deleteService = FALSE;
		DataAcqInstance.deleteCurrSvcOnZap = TRUE;
		//TO DO : Notify Background module

	}
	if (deleteService)
	{
		for(loopCount =0; loopCount < MAX_NUM_LCN_ENTRY;loopCount++)
		{
			presetData.PresetNumber = pSvcData->MultiplePreset[loopCount];

			if (TRUE == pgdb->GetByKey (PRESET_TABLE, (Address)&presetData))
			{
				pgdb->Delete(PRESET_TABLE, (Address)&presetData);
				++numDeletedSvcs;
			}
		}

		// if the service is a duplicate service, then removed service count will be increased while assigning LCN itself
		if(!duplicateService)
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
}


void CHsvDvbsFreesat_mAcq::mDeleteTSTable(HsvInstallationPTC *ptc)
{
	HsvPgdatDigTSData tsData;
	pgdb->Initialise (IHsvProgramDatabaseConstants_DigitalTS, (Address) &tsData);

	tsData.LnbNumber     = ptc->LnbNumber;
	tsData.Frequency     = ptc->Frequency;
	tsData.Polarization  = ptc->Polarization;
	if (pgdb->GetByKey (PTC_TABLE, (Address )&tsData) == TRUE)
	{
		TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tsData.Frequency, tsData.Polarization);
		pgdb->Delete (PTC_TABLE, (Address )&tsData);
	}
}


void CHsvDvbsFreesat_mAcq::mDeleteServicesCurrentCarrier (HsvInstallationPTC *ptc)
{
	Bool retVal = FALSE;
	HsvPgdatDigServiceData tempSvcData;
	int startCount = 0;
	int endCount = 0;
	int loopCount = 0;

	tempSvcData.Tpid = ptc->TPID;
	retVal = pgdb->GetRange (SERVICE_TABLE, 1, (Address)&tempSvcData, &startCount, &endCount);
	TraceNotice(m,"SC %d EC %d retval %d",startCount,endCount,retVal);
	if (retVal)
	{
		for (loopCount = endCount; loopCount >= startCount; --loopCount)
		{
			retVal = pgdb->GetByIndex (SERVICE_TABLE, loopCount ,(Address)&tempSvcData);
			if ((TRUE == retVal) &&
				(FALSE == mIsSvcPresentInServiceList(&tempSvcData)) &&
				(0 != tempSvcData.SDSDFrequency)) // Dont delete services installed by generic module (Not appicable for Freesat as it supports only Quick scan)
			{
				mDeleteService(&tempSvcData, FALSE);
			}
		}
	}
}


void CHsvDvbsFreesat_mAcq::mDeleteAllServicesFromCarrier (int tpId)
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
			retVal = pgdb->GetByIndex (SERVICE_TABLE, loopCount ,(Address)&tempSvcData);
			if (retVal == TRUE)
			{
				mDeleteService(&tempSvcData, FALSE);
			}
		}
	}
}


void CHsvDvbsFreesat_mAcq::mDeleteServicesFromDeletedMuxesInCurrentBAT (void)
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
			// Check if any service belongs to this TS is present in BAT SLD
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


Bool CHsvDvbsFreesat_mAcq::mIsTSPresentInSLDList (HsvPgdatDigTSData *pTmpTsData)
{
	Bool retVal = FALSE;
	int startCount = 0;
	int endCount = 0;

	// incase of Freesat BAT table transmitted across the muxes are same, so in both homing and
	// fallback mode TS considered as availabe if any service belongs to that TS is present in BAT
	if(strapi->GetRangeByKey(HsvMain, HSVSPID(ActualServiceList, dvb, bat), 2,
				pTmpTsData->OriginalNetworkId,
				pTmpTsData->Tsid, 0, &startCount, &endCount))
	{
		retVal = TRUE;
	}

	return retVal;
}


Bool CHsvDvbsFreesat_mAcq::mIsTSPresentInSDSDList (HsvPgdatDigTSData *pTmpTsData)
{
	Bool retVal = FALSE;
	HSVSPTYPE(SatelliteDS,dvb,nit) satSDSD;

	if (strapi->GetByKey(HsvMain, HSVSPID(SatelliteDS, dvb, nit), pTmpTsData->OriginalNetworkId,
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


Bool CHsvDvbsFreesat_mAcq::mIsSvcPresentInServiceList (HsvPgdatDigServiceData *pSvcdata)
{
	Bool retVal = FALSE;
	HSVSPTYPE(ActualServiceList,dvb,bat) batService;

	if(TRUE == strapi->GetByKey (HsvMain, HSVSPID(ActualServiceList, dvb, bat), pSvcdata->OriginalNetworkId,
				pSvcdata->Tsid, pSvcdata->ServiceId, (void *)(&batService)))
	{
		retVal = TRUE;
	}
	else
	{
		TraceNotice (m,"Service not present in BAT SLD\n");
	}

	return retVal;
}

#if FLAG
Bool CHsvDvbsFreesat_mAcq::mIsSvcLCNValid (SvcListInfo scvInfo)
{
	Bool retVal = FALSE;
	HSVSPID(FreesatLCN, dvb, bat) lcnInfo;

	if(TRUE == strapi->GetByKey (HsvMain, HSVSPID(FreesatLCN, dvb, bat), scvInfo->OnId,
				scvInfo->TsId, scvInfo->ServiceId, (void *)(&lcnInfo)))
	{
		retVal = TRUE;
	}
	else
	{
		TraceNotice (m,"Service not present in LCN descriptor\n");
	}

	return retVal;
}
#endif

int CHsvDvbsFreesat_mAcq::mCalculateBandwidthFromSdsd (Nat8 rollOff, int symbolRate, Nat8 fecInner)
{
	double	bandWidth = 0;

	if (IS_VALID_ROLLOFF(rollOff))
	{
		/* SB = SR(1+Ro) */
		bandWidth = symbolRate * (1+RollOffTable[rollOff]);
	}
	bandWidth /= 1000;	/* To make it in KHz */
	UNUSED (fecInner);

	return (Nat8)bandWidth;
}

int CHsvDvbsFreesat_mAcq::mConvertToPgdatServiceType (int serviceType)
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

Bool CHsvDvbsFreesat_mAcq::mIsDigitalTvChannel (HsvPgdatDigServiceData *pSvcData)
{
	Bool	retVal = FALSE;
	switch (pSvcData->ServiceType)
	{
		case	AppApiTelevisionService:
		case	AppApiTeletextService:
		case	AppApiMPEG2HDService:
		case	AppApiAdvCodecHDTelevisionService:
		case	AppApiAdvCodecSDTelevisionService:
		case	AppApiHevcService:
		retVal = TRUE;
		break;
	default:
		break;
	}
	return retVal;
}

Bool CHsvDvbsFreesat_mAcq::mIsDigitalRadioService (HsvPgdatDigServiceData *pSvcData)
{
	Bool retVal = FALSE;
	switch (pSvcData->ServiceType)
	{
	case AppApiRadioService:
	case AppApiAdvCodecRadioService:
		retVal = TRUE;
		break;
	default:
		break;
	}
	return retVal;
}

Bool CHsvDvbsFreesat_mAcq::mIsServiceInstallable (SvcListInfo  *service)
{
	Bool lRetVal = FALSE;
	switch(service->ServiceType)
	{
	case TelevisionService:
	case RadioService:
	case TeletextService:
	case AdvCodecSDTelevisionService:
	case AdvCodecHDTelevisionService:
	/*case DatabroadcastService: removed as we are not supporting MHEG as of now*/
	case AdvCodecRadioService: //added as per the overriding statement in the requirement Freesat XRS bc5549
	/*Freesat specifies only above mentioned service types but our TV supports a superset of this and shall be continued for Freesat as well*/
	case AppApiHevcService:
		lRetVal = TRUE;
		break;
	default:
		break;
	}
	return lRetVal;
}


Bool CHsvDvbsFreesat_mAcq::mIsManualInstall (void)
{
	int mode, state;

	rins->GetCurrentInstallationState(&mode, &state);

	return ((IHsvSatelliteInstallation_InstallationManual == mode) ? TRUE : FALSE);
}

Bool CHsvDvbsFreesat_mAcq::mIsUpdateInstall (void)
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

Bool CHsvDvbsFreesat_mAcq::mIsBackgroundUpdateInstall (void)
{
	int mode, state;

	rins->GetCurrentInstallationState(&mode, &state);

	return ((IHsvSatelliteInstallation_InstallationBackground == mode) ? TRUE : FALSE);
}

#if 0
Bool CHsvDvbsFreesat_mAcq::mIsCurrentService (HsvPgdatDigServiceData service)
{
	Bool retVal = FALSE;

	if (service.OriginalNetworkId == DataAcqInstance.CurrService.OriginalNetworkId &&
			service.Tsid == DataAcqInstance.CurrService.Tsid &&
			service.ServiceId == DataAcqInstance.CurrService.ServiceId)
	{
		retVal = TRUE;
	}

	return retVal;
}
#endif


void CHsvDvbsFreesat_mAcq::mCopyString (Nat16 *dest, Nat16 *src, int maxChars)
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

void CHsvDvbsFreesat_mAcq::Init (void)
{
	TraceNotice (m, " %s()\n", __FUNCTION__);
	mDataAcqPump = m_pfac.PmpCreate (pen->PumpEngine(), &CHsvDvbsFreesat_mAcq::mPumpHandler, \
	FALSE, (char *)"hsvdvbsfreesat_mDataAcq", this);
}

void CHsvDvbsFreesat_mAcq::TurnOn (void)
{
	TraceNotice (m, " %s()\n", __FUNCTION__);
}

void CHsvDvbsFreesat_mAcq::TurnOff (void)
{
	TraceNotice (m, " %s()\n", __FUNCTION__);
}


// Overridden IHsvDigitalAcquisition methods

void CHsvDvbsFreesat_mAcq::Initialise (int lnbNumber)
{
	TraceNotice(m,"%s Entry",__FUNCTION__);
	// Resetting all static variables
	mDigitalChannelsFound = 0;
	mDigitalTvChannelsFound = 0;
	mDigitalRadioChannelsFound = 0;
	mRemoveCurTv = 0;
	mRemoveCurRadio = 0;

	UNUSED(lnbNumber);
}

void CHsvDvbsFreesat_mAcq::AcquireData (int mode)
{
	m_pfac.PmpSend (mDataAcqPump, EvStartAcquire, (Nat32)NULL);
	UNUSED (mode);
}

int CHsvDvbsFreesat_mAcq::GetNumberOfDigitalChannelsFound (void)
{
	TraceNotice (m,"%s() %d > DigitalChannels Added[%d]", __FUNCTION__, __LINE__, mDigitalChannelsFound);
	return mDigitalChannelsFound;
}

int CHsvDvbsFreesat_mAcq::GetNumberOfDigitalChannelsRemoved (void)
{
	return 0;
}

int CHsvDvbsFreesat_mAcq::GetNumberOfTvChannelsFound (void)
{
	TraceNotice (m,"%s() %d > Tv Added[%d]", __FUNCTION__, __LINE__, mDigitalTvChannelsFound);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsFreesat_mAcq::GetNumberOfRadioChannelsFound (void)
{
	TraceNotice (m,"%s() %d > Radio Added[%d]", __FUNCTION__, __LINE__, mDigitalRadioChannelsFound);
	return mDigitalRadioChannelsFound;
}

int CHsvDvbsFreesat_mAcq::GetNumberOfTvChannelsRemoved (void)
{
	TraceNotice (m,"%s() %d > Tv Removed[%d]", __FUNCTION__, __LINE__, mRemoveCurTv);
	return mRemoveCurTv;
}

int CHsvDvbsFreesat_mAcq::GetNumberofRadioChannelsRemoved (void)
{
	TraceNotice (m,"%s() %d > Radio Removed[%d]", __FUNCTION__, __LINE__, mRemoveCurRadio);
	return mRemoveCurRadio;
}

int CHsvDvbsFreesat_mAcq::GetNumberOfSdsds (void)
{
	TraceNotice (m,"%s() %d > Num SDSDs[%d]", __FUNCTION__, __LINE__, mFreesatDSDesc.numSDSD);
	return mFreesatDSDesc.numSDSD;
}

Bool CHsvDvbsFreesat_mAcq::GetSdsdByIndex (int index, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool retVal = FALSE;

	if(index < mFreesatDSDesc.numSDSD)
	{
		memcpy(SdSdEntry,&mFreesatDSDesc.SatDesc[index], sizeof(HsvNITSatelliteDS));

		mFreesatDSDesc.CurrentSDSDIndex = index;
		retVal = TRUE;
	}

	return retVal;
}

int CHsvDvbsFreesat_mAcq::GetNumberOfTvChannelsInLnb (int lnb)
{
	UNUSED (lnb);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsFreesat_mAcq::GetNumberOfRadioChannelsInLnb (int lnb)
{
	UNUSED (lnb);
	return mDigitalRadioChannelsFound;
}

void CHsvDvbsFreesat_mAcq::AssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	// Do nothing
}
void CHsvDvbsFreesat_mAcq::AcquireDataOnTimeout (void)
{
	// Do nothing
}

int CHsvDvbsFreesat_mAcq::StoreBarkerMuxDetails (void)
{
	int RetVal = FALSE;
	if(iutil->WriteBarkerMuxData(BarkerMuxData) == TRUE)
	{
		RetVal = TRUE;
	}
	return RetVal;	
}

void CHsvDvbsFreesat_mAcq::SyncTemporaryTableRecords (void)
{
	// Do nothing
}

void CHsvDvbsFreesat_mAcq::GetTricolorRegionNames (Nat16 **names, int *len)
{
	// Do nothing
}
