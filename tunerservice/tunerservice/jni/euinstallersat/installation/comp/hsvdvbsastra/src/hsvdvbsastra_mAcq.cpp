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
 *          %name: hsvdvbsastra_mAcq.c %
 *       %version: TVG_r3ext_12 %
 * %date_modified: Fri Jan 23 18:40:16 2009 %
 *    %derived_by: shivam %
 */
 

#include "CHsvDvbsAstra_mAcq.h"

TRACESYMBOL(m, "s2/installation/hsvdvbsastra_macq")

/****************************************************************************
 * Macros and types
 ****************************************************************************/


#define	AUTO_MODE								(insstate_InstallationServiceScan)

#define	UPDATE_MODE							(insstate_InstallationUpdate)

#define	GETSERVICETYPE(servicetype)			( ((servicetype == AppApiRadioService) || (servicetype == AppApiAdvCodecRadioService)) ? HsvRadio: HsvOnePart )

#define	GETHSVSPID(prop, tableid)				(mHsvDVBPIDList[prop][tableid])

#define	ACTUAL_TABLE							(0)

#define	OTHER_TABLE							(1)

#define	IS_VALID_ONID							( (DataAcqInstance.Onid >= 0xFF00)? FALSE: TRUE )		

#define	IS_VALID_NID							( (DataAcqInstance.NetworkId >= 0xFF01)? FALSE: TRUE )

#define	IS_VALID_TSID							( TRUE ) /* Not using yet in field.. might come soon */

#define	IS_VALID_TS							( IS_VALID_ONID && IS_VALID_NID && IS_VALID_TSID )

#define	INVALID_PRESET							(0XFFFF)

#define	SAT_INFO_TABLE						(pgdbconst_Satellite | pgdbconst_SatInfo)

#define	PTC_TABLE							    	(pgdbconst_Satellite | pgdbconst_DigitalTS)

#define	SERVICE_TABLE							(pgdbconst_Satellite | pgdbconst_DigitalService)

#define	PRESET_TABLE							(pgdbconst_Satellite | pgdbconst_Preset)

#define	INVALID_VERSION						(-1)

#define	VERSION1								(1)

#define 	MIN_VALID_LCN    						(1)

#define	MAX_VALID_LCN    						(1000)

#define	VALID_LCN_RANGE(x)  					(((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))

#define	REVALIDATE(x)     						((x) &= 0x7FFF)  

#define 	IS_RADIO_SERVICE(x)     ((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService) )

#define	ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)	 { \
														svcdat1.Tpid	= svcdat2.Tpid; \
														svcdat1.ServiceId			= svcdat2.ServiceId; \
													 }

#define	MAX_LNBS_SUPPORTED						(4)

#define	IS_VALID_ROLLOFF(x)		(x<(sizeof(RollOffTable)/sizeof(RollOffTable[0])))

#define	MAX_SERVICES				(1500)

#define	MAX_LCN_NUMBERS			(1500)

#define MAX_NUM_LCN_ENTRY			8

#define MAX_NUM_PRESET_ENTRY		MAX_NUM_LCN_ENTRY

#define INVALID_LCN			(0xC000)



#define	ABS(freq1, freq2)			((freq1 >= freq2) ? (freq1 - freq2) : (freq2 - freq1))

#define 	FREQ_DRIFT_TOLERANCE		(4000)

typedef enum
{
	EvStartAcquire = 0,
	EvAcquireTSInfo,
	EvCompleteAcquire
}AcqEvents;




/****************************************************************************
 * Static variables
 ****************************************************************************/

AstraSatDSDesc CHsvDvbsAstra_mAcq::s__mAstraDSDesc;


int CHsvDvbsAstra_mAcq::s__mDigitalChannelsFound = 0,CHsvDvbsAstra_mAcq::s__mDigitalTvChannelsFound = 0 ,CHsvDvbsAstra_mAcq::s__mDigitalRadioChannelsFound = 0;

Pump CHsvDvbsAstra_mAcq::s__mDataAcqPump;


int CHsvDvbsAstra_mAcq::s__removeCurTv = 0,CHsvDvbsAstra_mAcq::s__removeCurRadio =0;

AstraDataAcqInstance CHsvDvbsAstra_mAcq::s__DataAcqInstance;


HsvInstallationPTC CHsvDvbsAstra_mAcq::s__CurrentPTC;


double CHsvDvbsAstra_mAcq::s__RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};


void CHsvDvbsAstra_mAcq::mPumpHandler(int value, Nat32 param)
{
	Bool Status = FALSE;
	TraceInfo (m," mPumpHandler %d value",value);
	switch(value)
	{
	case EvStartAcquire:
		if(param  == idataacq_Homing)
		{
			DataAcqInstance.Mode = AstraHoming;
			mCollectSdsds();
			mGetSatelliteLnbNo(ASTRA_19_2_E);
			idataacqN_OnDataAquired(TRUE);
		}
		else
		{
			TraceNotice(m,"Size of SGT table: %d", strapi_GetSize (HsvMain, HSVSPID(ActualTSService, dvb, sgt)));
			DataAcqInstance.Mode = AstraAcquireServices;
			mAcquireTSInfo();
		}
		break;
	case EvAcquireTSInfo:
		mAcquireTSInfo();
		break;
	case EvCompleteAcquire:
		idataacqN_OnDataAquired(param);
		TraceNotice (m, "EvCompleteAcquire with status: %d\n", param);
		break;
	}
		
}

void CHsvDvbsAstra_mAcq::mGetPTCInfo(HSVSPTYPE(SatelliteDS,dvb,nit) Sdsd, HsvInstallationPTC *ptc)
{
	ptc->LnbNumber = DataAcqInstance.LnbNumber;
	ptc->Polarization = Sdsd.Polarization;	
	ptc->Frequency = Sdsd.Frequency;
	ptc->SDSDFrequency = Sdsd.Frequency;
	ptc->SymbolRate = Sdsd.SymbolRate;
	ptc->ModulationType = Sdsd.ModulationType;
	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);
	ptc->ChannelBandwidth = CalculateBandwidthFromSdsd (Sdsd.RollOff, Sdsd.SymbolRate, Sdsd.FECInner);
	ptc->ModulationStd = Sdsd.ModulationSystem;
	ptc->FECInner = Sdsd.FECInner;
	ptc->RollOff = Sdsd.RollOff;
}

void CHsvDvbsAstra_mAcq::mAcquireTSInfo(void)
{
	HSVSPTYPE(SatelliteDS,dvb,nit) CurrentSdsd;
	AstraKeyUpdateReason KeyUpdate = AstraNoUpdate;
	HsvPgdatDigTSData OldTsData;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &OldTsData);
	
	TraceInfo  (m, " DataAcqInstance.CurSdsd %d DataAcqInstance.NumSdsds %d sizeof(CurrentSdsd) %d", DataAcqInstance.CurSdsd, DataAcqInstance.NumSdsds,sizeof(CurrentSdsd));
	if(DataAcqInstance.CurSdsd < DataAcqInstance.NumSdsds)
	{
		DataAcqInstance.NetworkId = mAstraDSDesc.SatDesc[DataAcqInstance.CurSdsd].NetworkId;
		DataAcqInstance.Onid	= mAstraDSDesc.SatDesc[DataAcqInstance.CurSdsd].Original_NetworkId;
		DataAcqInstance.Tsid = mAstraDSDesc.SatDesc[DataAcqInstance.CurSdsd].Tsid;
		/*In Homing mode PTC info is built with in Acq. module as no tuning to SDSD is required*/
		mGetPTCInfo(mAstraDSDesc.SatDesc[DataAcqInstance.CurSdsd],&CurrentPTC);

		if(IsUpdateInstall() == TRUE)
		{
			/*If TS is already present with different Keys then add services with new keys returned*/
			mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
			if(mInstallMux(CurrentPTC, KeyUpdate, &OldTsData) == FALSE )
			{
				/* If no services are added\updated, delete entry from TS Table */
				mDeleteTSTable(&CurrentPTC);
			}
		}
		else
		{
			/*Intsall the services and Add to TS Table*/
			if(mInstallMux(CurrentPTC, KeyUpdate, &OldTsData) == TRUE )
			{
				/* Add entry to TS Table */
				mAddToTSTable(&CurrentPTC, &KeyUpdate, &OldTsData);
			}
		}
		/*Increment CurSdsd after installing mux*/
		DataAcqInstance.CurSdsd++;
	}
	
	if(DataAcqInstance.CurSdsd >= DataAcqInstance.NumSdsds)
	{
		/*Delete all Carriers(SDSDs) removed from NIT */
		if(IsUpdateInstall() == TRUE)
		{
			mDeleteMuxesFromCurrentNIT();
		}
		pmp_PmpSend(mDataAcqPump, EvCompleteAcquire, (Nat32)NULL);	
	}
	else
	{
		pmp_PmpSend(mDataAcqPump, EvAcquireTSInfo, (Nat32)NULL);
	}
}


void CHsvDvbsAstra_mAcq::mDeleteTSTable(HsvInstallationPTC *ptc)
{
	HsvPgdatDigTSData   tsdata;
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Frequency				= ptc->Frequency;
	tsdata.Polarization				= ptc->Polarization;
	if( pgdb_GetByKey(PTC_TABLE, (Address )&tsdata) == TRUE )
	{
		TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization);
		pgdb_Delete(PTC_TABLE, (Address )&tsdata);
	}
}

void CHsvDvbsAstra_mAcq::mDeleteMuxesFromCurrentNIT(void)
{
	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0 , i = 0;

	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);

	NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

	for(i = NoOfTSTables; i > 0; i--)
	{
		pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
		if((pgdb_GetByIndex(PTC_TABLE, (i-1), (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
		{	/*Check if this TS table present in SDSD list*/
			if(mIsTSPresentInSDSDList(&tmptsdata) == FALSE)			
			{
				mDeleteAllServicesFromCarrier(tmptsdata.Tpid);
				TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d> tsid: %d\n", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization, tmptsdata.Tsid);
				pgdb_Delete(PTC_TABLE, (Address) &tmptsdata);
			}
		}
	}

}

Bool CHsvDvbsAstra_mAcq::mIsTSPresentInSDSDList(HsvPgdatDigTSData *tmptsdata)
{
	HSVSPTYPE(SatelliteDS,dvb,nit) tmpsdsd;
	Bool RetVal = FALSE;
	int i;

	for (i = 0; i < mAstraDSDesc.NumOfSDSD; i++)
	{
		if((tmptsdata->OriginalNetworkId == mAstraDSDesc.SatDesc[i].Original_NetworkId) && (tmptsdata->Tsid == mAstraDSDesc.SatDesc[i].Tsid))
		{
			RetVal = TRUE;
			break;
		}
	}
	
	return RetVal;
}

/*Keyupdate reason indicates if any key(freq/pol) is updated in SDSD.  
old TPID entry is deleted and new entry is added with new freq\pol and oldTPID is returned which is used to add/update services*/
void CHsvDvbsAstra_mAcq::mAddToTSTable(HsvInstallationPTC *ptc, AstraKeyUpdateReason *KeyUpdate, HsvPgdatDigTSData *OldTsData)
{

	HsvPgdatDigTSData   tsdata, tmptsdata;
	int NoOfTSTables = 0 , i = 0;
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tsdata);
	pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);

	/* Filling attributes from ptc, and acqinstance */
	tsdata.Frequency					= ptc->Frequency;
	tsdata.SymbolRate				= ptc->SymbolRate;

	tsdata.OriginalNetworkId			= DataAcqInstance.Onid;
	tsdata.Tsid						= DataAcqInstance.Tsid;
	tsdata.NetworkId					= DataAcqInstance.NetworkId;
	tsdata.ModulationType			= ptc->ModulationType;

	tsdata.Bandwidth				= ptc->ChannelBandwidth;

	tsdata.PtcListVersion			= isvcscandata_GetInstallationVersion();
	tsdata.SDSDFrequency			= ptc->SDSDFrequency;
	tsdata.UserInstalled			= IsManualInstall();
	tsdata.LnbNumber				= ptc->LnbNumber;
	tsdata.Polarization				= ptc->Polarization;
	tsdata.Tpid						= ptc->TPID;
	tsdata.DecoderType				= ptc->ModulationStd;

	tmptsdata.LnbNumber			= tsdata.LnbNumber;
	tmptsdata.Frequency			= tsdata.Frequency;
	tmptsdata.Polarization			= tsdata.Polarization;

	/* check entry already present. If yes update else add */
	if( pgdb_GetByKey(PTC_TABLE, (Address )&tmptsdata) == FALSE )
	{
		/*If GetByKey is failed, check if any Keys(Frequency/polarization) are updated */
		if(IsUpdateInstall() == TRUE)
		{
			NoOfTSTables = pgdb_GetNoRecords(PTC_TABLE);

			for(i = 0; i<NoOfTSTables; i++)
			{
				pgdb_Initialise(pgdbconst_DigitalTS, (Address) &tmptsdata);
				/*Check only TS tables installed via pkg install*/
				if((pgdb_GetByIndex(PTC_TABLE, i, (Address)&tmptsdata) == TRUE) && (tmptsdata.SDSDFrequency != 0))
				{
					if((tmptsdata.OriginalNetworkId == tsdata.OriginalNetworkId) && (tmptsdata.Tsid == tsdata.Tsid))
					{
						/*Return old Keys and TS table*/
						OldTsData->LnbNumber = tmptsdata.LnbNumber;
						OldTsData->Frequency = tmptsdata.Frequency;
						OldTsData->Polarization = tmptsdata.Polarization;
						pgdb_GetByKey(PTC_TABLE, (Address )OldTsData);

						*KeyUpdate = AstraSDSDChange;
						
						/*Delete the Old TS Table with old TPID and Add new TS Table with updated TPID and keys */
						pgdb_Delete(PTC_TABLE, (Address)&tmptsdata);
						TraceNotice (m, "Deletion to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tmptsdata.Frequency, tmptsdata.Polarization);
						pgdb_Add(PTC_TABLE, (Address )&tsdata);
						TraceNotice (m, "Addition to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.Polarization);
						break;
					}
				}
			}
			/*It is a New TS, Add to TS table*/
			if(i == NoOfTSTables)
			{
				pgdb_Add(PTC_TABLE, (Address )&tsdata);
			}
		}
		else
		{
			/*In Auto install, Add to TS table*/
			tsdata.SDTVersion	= INVALID_VERSION;
			pgdb_Add(PTC_TABLE, (Address )&tsdata);
		}

	}
	else
	{
		//TraceNotice (m, "Updation to pgdb table %s %d <%ld %d>\n", __FUNCTION__, __LINE__, tsdata.Frequency, tsdata.StreamPriority);

		tsdata.SDTVersion	= tmptsdata.SDTVersion;
		pgdb_Update(PTC_TABLE, (Address )&tsdata);
	}
}

Bool CHsvDvbsAstra_mAcq::mInstallMux(HsvInstallationPTC ptc, AstraKeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData)
{
	Bool	retval = FALSE;
	HSVSPTYPE(ActualTSService, dvb, sgt) service;
	int		index, from = 0, to = 0,LCN_from = 0, LCN_to = 0,InstalledServices = 0, NoOfLCNSvcs = 0;

	if(strapi_GetRangeByKey(HsvMain, HSVSPID(ActualTSService, dvb, sgt), 2, DataAcqInstance.Onid, DataAcqInstance.Tsid, 0, &from, &to) == TRUE)
	{
		TraceNotice (m, "%s %d NoOfServices in MUX = %d ONID = %d TSID = %d \n",__FUNCTION__, __LINE__, ((to - from)+1),DataAcqInstance.Onid, DataAcqInstance.Tsid);

		/* From strapi get all the services and add/update in SERVICE_TABLE */
		for(index = to; index >= from ; )
		{
			NoOfLCNSvcs = 0, LCN_from = 0, LCN_to = 0;
			if(strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sgt), index, (void *)(&service)) == TRUE)
			{
				if(strapi_GetRangeByKey(HsvMain, HSVSPID(ActualTSService, dvb, sgt), 3, DataAcqInstance.Onid, DataAcqInstance.Tsid, service.ServiceId, &LCN_from, &LCN_to) == TRUE)
				{
					NoOfLCNSvcs = (LCN_to-LCN_from)+1;
				}
				TraceNotice (m, "%s %d NoOfLCNs for service = %d ONID = %d TSID = %d SVCID = %d\n",__FUNCTION__, __LINE__, NoOfLCNSvcs,DataAcqInstance.Onid, DataAcqInstance.Tsid,service.ServiceId);
				if(mCheckServiceForInstall(&ptc, KeyUpdate, OldTsData,&service))
				{
					InstalledServices++;
					retval = TRUE;
				}
			}

			index = ((NoOfLCNSvcs == 0) ? (index - 1) :(index - NoOfLCNSvcs));
		}

	}
	else
	{
		TraceNotice(m, "No services found in service list of ONID = %d TSID = %d \n", DataAcqInstance.Onid, DataAcqInstance.Tsid);
	}
	
	if(IsUpdateInstall())
	{
		if (KeyUpdate == AstraSDSDChange)
		{
			/*Here OldTPID will remain with non transmitted services*/
			mDeleteAllServicesFromCarrier(OldTsData->Tpid);
		}
		else
		{
			mDeleteServicesCurrentCarrier(&ptc);
		}
	}


	TraceNotice (m, "Homing Mode: Updateprint: Num TV: %d Num Radio: %d \n", mDigitalTvChannelsFound, mDigitalRadioChannelsFound);

       return retval;
}

Bool CHsvDvbsAstra_mAcq::mCheckServiceForInstall(HsvInstallationPTC *ptc, AstraKeyUpdateReason KeyUpdate, HsvPgdatDigTSData* OldTsData, HSVSPTYPE(ActualTSService, dvb, sgt) *service)
{

	Bool	retval = FALSE, channelExists = FALSE, IsDuplicatesvc = FALSE, IsServiceAdded = FALSE, ToAdd = TRUE;
	HsvPgdatDigServiceData 		svcdat, tempsvcdat;
	HsvPgdatPresetData			presetData;
	int LoopCount;

	pgdb_Initialise(pgdbconst_DigitalService, (Address)(&svcdat));
	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
	{
		svcdat.MultipleLCN[LoopCount] = INVALID_LCN;
		svcdat.MultiplePreset[LoopCount] = INVALID_PRESET;
	}

	/*If db key(TPID) is updated, delete the service and add it again with new TPID (as TPID is the key for service table)*/
	if(KeyUpdate == AstraSDSDChange)
	{
		svcdat.Tpid = OldTsData->Tpid;
		svcdat.ServiceId = service->ServiceId;

		if(pgdb_GetByKey(SERVICE_TABLE, (Address )&svcdat) == TRUE)
		{
			IsDuplicatesvc = TRUE;
		}
	}

	svcdat.Frequency		  = ptc->Frequency;
	svcdat.OriginalNetworkId = DataAcqInstance.Onid;
	svcdat.Tsid 			  = DataAcqInstance.Tsid;
	svcdat.LnbNumber 		  = ptc->LnbNumber;
	svcdat.Polarization 		  = ptc->Polarization;
	svcdat.Tpid	       	  = ptc->TPID;
	svcdat.ServiceId		= service->ServiceId;
	/*TODO: check if this is required*/
//	svcdat.NetworkId		=   service->NetworkId;
	svcdat.SDSDFrequency	= ptc->SDSDFrequency;
	svcdat.DecoderType	= ptc->ModulationStd;
	/*TODO: uncomment after adding these items in db*/
//	svcdat.FECInner	= ptc->FECInner;
//	svcdat.RollOff	= ptc->RollOff;
	

	if((mIsServiceInstallable(service) == FALSE) || (service-> LogicalChannelNum == 0))
	{
		ToAdd = FALSE;
		PrintfNotice("service is not installable onid: %d, tsid: %d, svcid: %d",svcdat.OriginalNetworkId,svcdat.Tsid  , svcdat.ServiceId );
	}


	if(ToAdd == TRUE)
	{
		tempsvcdat.Tpid	 = svcdat.Tpid;
		tempsvcdat.ServiceId	 = svcdat.ServiceId;

		channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		if(channelExists)
		{
			TraceNotice (m, " Channel exists SvcId %d and SvcType %d \n", service->ServiceId, service->ServiceType);
			/* If entry already present update the service data */
			mUpdateService(&svcdat, ptc, service);
			retval = TRUE;	

		}
		else
		{

			mAddNewService(&svcdat, ptc, service,IsDuplicatesvc);
			IsServiceAdded = TRUE;
			retval = TRUE;
		}
		
	}
	else
	{

		tempsvcdat.Tpid	 = svcdat.Tpid;
		tempsvcdat.ServiceId	 = svcdat.ServiceId;

		channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);
		if(channelExists)
		{
			mDeleteService(&tempsvcdat, FALSE);
		}
	}
	if(IsDuplicatesvc )
	{
		/*Delete the duplicate service with old TPID,svcid*/
		pgdb_Initialise(pgdbconst_DigitalService, (Address)(&tempsvcdat));
		tempsvcdat.Tpid = OldTsData->Tpid;
		tempsvcdat.ServiceId = service->ServiceId;
		if(pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat))
		{
			/*If Duplicate service is added, preset table should not be deleted*/
			mDeleteService(&tempsvcdat, (IsDuplicatesvc && IsServiceAdded));
		}
		
	}
	return retval;
}

void CHsvDvbsAstra_mAcq::mDeleteService(HsvPgdatDigServiceData *psvcdat, Bool Is_DuplicateService)
{
	int LoopIndex = 0;
	int NumSrvDeleted = 0;
	HsvPgdatPresetData presetData;

	/*Preset table should not be deleted for duplicate service*/
	if(!Is_DuplicateService){
		
		for(LoopIndex =0; LoopIndex < MAX_NUM_LCN_ENTRY; LoopIndex++)
		{
			presetData.PresetNumber = psvcdat->MultiplePreset[LoopIndex];

			if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&presetData))
			{
				pgdb_Delete(PRESET_TABLE, (Address)&presetData);
				NumSrvDeleted++;
			}
		}

		/*if the service is a duplicate service, then removed service count will be increased while assigning LCN itself*/
		if (IsDigitalTvChannel (psvcdat))
		{
			removeCurTv += NumSrvDeleted;
		}
		else if (IsDigitalRadioService (psvcdat))
		{
			removeCurRadio += NumSrvDeleted;
		}
	}

	pgdb_Delete(SERVICE_TABLE, (Address)psvcdat);
	TraceNotice (m, "Deleted service Ser-id[%d] Tsid[%d] Onid[%d]",
				psvcdat->ServiceId,
				psvcdat->Tsid,
				psvcdat->OriginalNetworkId);
}


void CHsvDvbsAstra_mAcq::mDeleteServicesCurrentCarrier(HsvInstallationPTC *ptc)
{
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	
	int							From = 0, To = 0, count = 0;
	
	TempSvcData.Tpid 		 = ptc->TPID;
	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal == TRUE)
	{
		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData); 
			if ( (RetVal == TRUE) && (mIsSvcPresentInSGT(&TempSvcData) == FALSE) &&
			(TempSvcData.SDSDFrequency != 0)) /* Dont delete services installed by generic module*/
			{
				mDeleteService(&TempSvcData, FALSE);
			}
		}
	}
	else
	{
		TraceNotice(m,"Get Range failed in %s\n", __FUNCTION__);
	}
}

Bool CHsvDvbsAstra_mAcq::mIsSvcPresentInSGT(HsvPgdatDigServiceData *svcdata)
{
	Bool retval = FALSE;
	HSVSPTYPE(ActualTSService, dvb, sgt) service;
	int i, from, to;

	if(strapi_GetRangeByKey(HsvMain, HSVSPID(ActualTSService, dvb, sgt), 3, svcdata->OriginalNetworkId, svcdata->Tsid, svcdata->ServiceId, &from, &to) == TRUE)
	{
		retval = TRUE; 	
	}
	return retval;
}

void CHsvDvbsAstra_mAcq::mDeleteAllServicesFromCarrier(int TPID)
{
	Bool						RetVal = FALSE;
	HsvPgdatDigServiceData		TempSvcData;
	HsvPgdatPresetData			presetData;	
	int							From = 0, To = 0, count = 0;	

	TempSvcData.Tpid 		 = TPID;

	RetVal = pgdb_GetRange(SERVICE_TABLE,1,(Address)&TempSvcData,&From,&To);

	if (RetVal == TRUE)
	{

		for (count = To;count >=From; count--)
		{
			RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData); 
			if ( RetVal == TRUE)
			{
				RetVal = pgdb_GetByIndex (SERVICE_TABLE, count ,(Address)&TempSvcData);
				if ( RetVal == TRUE)
				{
					mDeleteService(&TempSvcData, FALSE);
				}
			}
		}
	}
}

void CHsvDvbsAstra_mAcq::mUpdateService(HsvPgdatDigServiceData* psvcdat, HsvInstallationPTC* ptc,HSVSPTYPE(ActualTSService, dvb, sgt) *service)
{
	/* Filling update details and updating */
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service,TRUE);
	mAssignLCN(psvcdat);
	mAssignSvcNonBroadcastAttributes(psvcdat);

	pgdb_Update(SERVICE_TABLE, (Address )psvcdat);
		
	TraceNotice(m,"Updated Service LCN:%d ONID:%d SVCID:%d\n", psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId);
}

void CHsvDvbsAstra_mAcq::mUpdateSatelliteName (HsvPgdatDigServiceData *psvcdat)
{
	HsvPgdatDigSatInfoData	SatInfo;

	SatInfo.LnbNumber = psvcdat->LnbNumber;
	
	if (TRUE == pgdb_GetByKey (SAT_INFO_TABLE, (Address)&SatInfo))
	{
		memcpy (psvcdat->SatelliteName, SatInfo.SatelliteName, sizeof(psvcdat->SatelliteName));
	}
}

void CHsvDvbsAstra_mAcq::mAddNewService(HsvPgdatDigServiceData *psvcdat ,HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sgt) *service, Bool IsDuplicatesvc)
{
	Nat8	ToAdd = FALSE;
	HsvPgdatPresetData			PresetData;
	int LoopIndex = 0;

	/* Filling details of service, then adding it */	
	mAssignSvcBroadcastAttributes(psvcdat, ptc,service,FALSE);
	mUpdateSatelliteName (psvcdat);

	mAssignLCN(psvcdat);
	
	/*User attributes should be retained for duplicate service*/
	if(IsDuplicatesvc == FALSE)
	{
		mAssignSvcNonBroadcastAttributes(psvcdat);
	}


	/* Add to service table */
	/* Add only if its TV or Radio Service */
	pgdb_Add(SERVICE_TABLE, (Address )psvcdat);
	TraceNotice(m,"Added Service LCN:%d ONID:%d SVCID:%d SystemHidden = %d\n",psvcdat->LCN, psvcdat->OriginalNetworkId, psvcdat->ServiceId,psvcdat->SystemHidden);
		
	/*If it is duplicate service Update the Preset table with new parameters*/
	if(IsDuplicatesvc)
	{
		for(LoopIndex = 0; LoopIndex < MAX_NUM_PRESET_ENTRY; LoopIndex++){
			PresetData.PresetNumber = psvcdat->MultiplePreset[LoopIndex];
			if (TRUE == pgdb_GetByKey (PRESET_TABLE, (Address)&PresetData))
			{
				PresetData.OriginalNetworkId = psvcdat->OriginalNetworkId;
				PresetData.ServiceId = psvcdat->ServiceId;
				PresetData.Tsid = psvcdat->Tsid;
				PresetData.Tpid = psvcdat->Tpid;
				PresetData.Frequency = psvcdat->Frequency;
				PresetData.Polarization = psvcdat->Polarization;
				PresetData.LnbNumber = psvcdat->LnbNumber;
				pgdb_Update(PRESET_TABLE, (Address)&PresetData);
			}				
		}
	}
}

Bool CHsvDvbsAstra_mAcq::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
	Bool retval = TRUE;

    while((*src) && (*dest) && (*dest++ == *src++));
	if((*src) || (*dest))
	{
		retval = FALSE;
	}

	return retval;
}


void CHsvDvbsAstra_mAcq::mAssignSvcBroadcastAttributes(HsvPgdatDigServiceData *psvcdat, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sgt) *service, Bool IsChannelExists)
{
	HsvPgdatDigServiceData		svcdat;

	psvcdat->ModulationType        =   ptc->ModulationType;
	psvcdat->Bandwidth	   			=   ptc->ChannelBandwidth;

	psvcdat->SymbolRate            =   ptc->SymbolRate;
	psvcdat->LnbNumber			   =   ptc->LnbNumber;
	psvcdat->Polarization		   =   ptc->Polarization;
	psvcdat->Tpid				   =   ptc->TPID;
	psvcdat->AudioPid              =   INVALID_PID;
	psvcdat->VideoPid              =   INVALID_PID;
	psvcdat->PcrPid                =   INVALID_PID;
	psvcdat->ServiceType           =   mConvertToPgdatServiceType(service->ServiceType);

/*TODO: check this*/
//psvcdat->FreeCiMode	    	   =   service->Free_Ci_Mode;

	/*do not update for existing channels*/
	if(!IsChannelExists)
	{
		psvcdat->ScramblingStatus		= 0; 
	}

	/*do not update with invalid name for existing channels*/
	if(IsChannelExists)
	{
	
		ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
		pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat);
		
		if((svcdat.UserModifiedName == FALSE) && (mIsServiceNameValid(service->ServiceName)))
		{
			mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_PresetNameLength - 1) );		
		}
		else if(svcdat.UserModifiedName == TRUE)
		{
			TraceNotice(m,"UserModified name can not be updated");
			mCopyString( psvcdat->ChannelName, svcdat.ChannelName, (eurdiv_PresetNameLength - 1) );
		}
	}
	else
	{
		mCopyString( psvcdat->ChannelName, service->ServiceName, (eurdiv_PresetNameLength - 1) );
	}

	//psvcdat->NumericSelect = TRUE;
	psvcdat->VisibleService	=	service->VisibleService;
	psvcdat->SystemHidden = !(psvcdat->VisibleService);

}

Bool CHsvDvbsAstra_mAcq::mIsServiceNameValid(Nat16* src)
{
	Nat16 Unicode_DefaultServiceName[10];
	char DefaultServiceName[10] = "-----";
	int loop = 0;
	Bool retval = FALSE;
	Nat16* dest = Unicode_DefaultServiceName;

	/*Convert to unicode*/
    while( loop < strlen(DefaultServiceName))
    {
        Unicode_DefaultServiceName[loop] = DefaultServiceName[loop];
        ++loop;
    }
	Unicode_DefaultServiceName[loop] = 0;

	/*Compare the strings*/
    while((*src) && (*dest) && (*dest++ == *src++));
	if((*dest) || (*src))
	{
		retval = TRUE;
	}
	else
	{
		retval = FALSE;
		TraceNotice(m," %s: Service need to be updated, RetVal: %d",__FUNCTION__, retval);
	}

	return retval;
}

void CHsvDvbsAstra_mAcq::mAssignSvcNonBroadcastAttributes(HsvPgdatDigServiceData* psvcdat)
{
	int mode, state;
	int LoopIndex = 0;
	Bool Proceed = FALSE;
	HsvPgdatPresetData			presetData;		
	HsvPgdatDigServiceData		svcdat;

	rins_GetCurrentInstallationState(&mode, &state);
	
	psvcdat->UserHidden             = FALSE;
	psvcdat->ChannelLock		    = FALSE;
	psvcdat->Favorite			    = FALSE;
	psvcdat->DateStamp			    = 0;
	for(LoopIndex = 0; LoopIndex < MAX_NUM_LCN_ENTRY; LoopIndex++)
	{
		psvcdat->MultiplePreset[LoopIndex] = INVALID_PRESET;
	}

	psvcdat->ServiceListVersion     = isvcscandata_GetInstallationVersion();
	psvcdat->NewPreset				= (mode == AUTO_MODE)? FALSE : TRUE;
	psvcdat->HbbTvOption 		= 1;
	psvcdat->PackageGroup 			= ASTRALCN_MATCH_SETTINGS_DB_PACKAGE_ID;
	

	ASSIGN_KEYS_OF_SVC(svcdat, (*psvcdat));
	if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat) == TRUE)
	{
		psvcdat->NewPreset				= svcdat.NewPreset;
		psvcdat->ChannelLock			= svcdat.ChannelLock;;
		psvcdat->UserHidden				= svcdat.UserHidden;
		psvcdat->Favorite				= svcdat.Favorite;
		psvcdat->ServiceListVersion     = svcdat.ServiceListVersion;
		psvcdat->HbbTvOption			= svcdat.HbbTvOption;
		psvcdat->DeltaVolume			= svcdat.DeltaVolume;
		psvcdat->UserModifiedName				= svcdat.UserModifiedName;
		psvcdat->FavoriteNumber			= svcdat.FavoriteNumber;
		psvcdat->LogoURL				= svcdat.LogoURL;
		
		if (mCompareUnicodeString(psvcdat->ChannelName, svcdat.ChannelName) == FALSE)
		{
			TraceNotice(m, "Service name updated");
			psvcdat->LogoURL = 0;
		}

		for(LoopIndex = 0; LoopIndex < MAX_NUM_LCN_ENTRY; LoopIndex++)
		{
			if(INVALID_LCN != svcdat.MultipleLCN[LoopIndex])
			{
				REVALIDATE(svcdat.MultipleLCN[LoopIndex]);
				Proceed |= ((VALID_LCN_RANGE(psvcdat->MultipleLCN[LoopIndex]) || VALID_LCN_RANGE(svcdat.MultipleLCN[LoopIndex])) && (psvcdat->MultipleLCN[LoopIndex] != svcdat.MultipleLCN[LoopIndex]));
				 if(Proceed)
				 {
					TraceNotice(m,"%s %d deleted preset becoz => newLCN %d oldLCN %d PresetNumber %d", __FUNCTION__, __LINE__, psvcdat->MultipleLCN[LoopIndex], svcdat.MultipleLCN[LoopIndex], svcdat.MultiplePreset[LoopIndex]);
					presetData.PresetNumber =   svcdat.MultiplePreset[LoopIndex];
					pgdb_Delete(PRESET_TABLE, (Address)&presetData);
					psvcdat->MultiplePreset[LoopIndex] = INVALID_PRESET;
				 }
				 else
				 {
					 psvcdat->MultiplePreset[LoopIndex] = svcdat.MultiplePreset[LoopIndex];
				 }
			}
		}
		 memcpy(psvcdat->UniqueIds, svcdat.UniqueIds, sizeof(svcdat.UniqueIds));

	}

	    if( Timerclk_IsClockDefined())
		{
			psvcdat->DateStamp = Timerclk_GetUniversalTime();
		}

}


int CHsvDvbsAstra_mAcq::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
{
	double	Bandwidth = 0;

	if (IS_VALID_ROLLOFF(RollOff))
	{
		/* SB = SR(1+Ro) */
		Bandwidth = SymbolRate * (1+RollOffTable[RollOff]);
	}
	Bandwidth /= 1000;	/* To make it in KHz */
	UNUSED (FECInner);

	return (Nat8)Bandwidth;
}

int CHsvDvbsAstra_mAcq::mConvertToPgdatServiceType(int servicetype)
{
	int retval = servicetype;
    switch(servicetype)
    {
        case TelevisionService:     
            retval  =   AppApiTelevisionService;
            break;
        case RadioService:
            retval  =   AppApiRadioService;
            break;
        case AdvCodecRadioService:    
            retval  =   AppApiAdvCodecRadioService;
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
	case	0x1C:
			retval  =   AppApiTelevisionService;
			break;
        default:
            break;
    }
    return retval;
}

Bool CHsvDvbsAstra_mAcq::IsDigitalTvChannel (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = FALSE;
	switch (psvcdat->ServiceType)
	{
	case	AppApiTelevisionService:
	case	AppApiTeletextService:
	case	AppApiMPEG2HDService:
	case	AppApiAdvCodecHDTelevisionService:
	case	AppApiAdvCodecSDTelevisionService:
	case	0x1C:
	case	AppApiHevcService:
		RetVal = TRUE;
		break;
	default:
		break;
	}
	return RetVal;
}

Bool CHsvDvbsAstra_mAcq::IsDigitalRadioService (HsvPgdatDigServiceData *psvcdat)
{
	Bool	RetVal = ((psvcdat->ServiceType == AppApiRadioService) || (psvcdat->ServiceType == AppApiAdvCodecRadioService)) ? TRUE: FALSE;
	return RetVal;
}

void CHsvDvbsAstra_mAcq::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}


Bool CHsvDvbsAstra_mAcq::mIsServiceInstallable(HSVSPTYPE(ActualTSService, dvb, sgt)* service)
{

	/* check service type*/
	Bool					lRetVal = FALSE;
	switch(service->ServiceType)
	{
	case TelevisionService:
	case RadioService:
	case TeletextService:
	case AdvCodecRadioService:
	case MPEG2HDService:
	case AdvCodecSDTelevisionService:
	case AdvCodecHDTelevisionService:
	case 0x0B:
	case 0x1C:
	case AppApiHevcService:
		lRetVal = TRUE;
		break;
	default:
		break;
	}
	return lRetVal;	    
}

void CHsvDvbsAstra_mAcq::mCollectSdsds (void)
{
	int i =0;

	mAstraDSDesc.NumOfSDSD = strapi_GetSize (HsvMain, HSVSPID(SatelliteDS, dvb, nit));
	for(i = 0; i < mAstraDSDesc.NumOfSDSD; i++)
	{
		if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&(mAstraDSDesc.SatDesc[i]))) == FALSE)
		{
			TraceNotice (m," Collect SDSD failed for SDSD: %d \n",i);
		}

		TraceNotice(m,"SDSD[%d]: Frequency: %d Pol: %d",i,mAstraDSDesc.SatDesc[i].Frequency,mAstraDSDesc.SatDesc[i].Polarization);
	}

	DataAcqInstance.CurSdsd = 0;
	DataAcqInstance.NumSdsds = 	mAstraDSDesc.NumOfSDSD;
	TraceNotice (m," DataAcqInstance.NumSdsds %d \n",DataAcqInstance.NumSdsds);
}

void CHsvDvbsAstra_mAcq::mGetSatelliteLnbNo(int SatId)
{
	int i;
	HsvPgdatDigSatInfoData SatDetails;
	for(i=0; i < MAX_LNBS_SUPPORTED; i++)
	{
		pgdb_Initialise(pgdbconst_SatInfo, (Address) &SatDetails);
		SatDetails.LnbNumber = i;
		if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatDetails) != TRUE)
		{
			TraceNotice (m," ERROR: Getting Sat. details failed for LNB: %d!!! \n",i);
		}

		if(SatDetails.SatelliteId == SatId)
		{
			DataAcqInstance.LnbNumber = i;
			break;
		}
	}
}

void CHsvDvbsAstra_mAcq::mAssignLCN(HsvPgdatDigServiceData *psvcdat)
{
	int LoopCount = 0, from = 0, to = 0, index = 0, i = 0, j = 0;
	HSVSPTYPE(ActualTSService, dvb, sgt) service;
	int newLCN[MAX_NUM_LCN_ENTRY];
	Bool Found = FALSE, channelExists = FALSE;
	HsvPgdatDigServiceData 		tempsvcdat;
	
	tempsvcdat.Tpid  = psvcdat->Tpid;
	tempsvcdat.ServiceId	 = psvcdat->ServiceId;
	
	for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount++)
	newLCN[LoopCount] = INVALID_LCN;
	
	channelExists = pgdb_GetByKey(SERVICE_TABLE, (Address)&tempsvcdat);

	//Take Old LCNs, this is to retain the position of previous LCNs in MultipleLCN[] if service is already present
	if(channelExists)
	{
		for(LoopCount = 0; LoopCount < MAX_NUM_LCN_ENTRY; LoopCount ++)
		{
			psvcdat->MultipleLCN[LoopCount] = tempsvcdat.MultipleLCN[LoopCount];
			if(psvcdat->MultipleLCN[LoopCount] != INVALID_LCN)
			{
				REVALIDATE(psvcdat->MultipleLCN[LoopCount]);
			}
		}
			
	}
	else
	{
		TraceDebug(m,"Channel does not exists");
	}

	if(strapi_GetRangeByKey(HsvMain, HSVSPID(ActualTSService, dvb, sgt), 3, DataAcqInstance.Onid, DataAcqInstance.Tsid, psvcdat->ServiceId, &from, &to) == FALSE)
	{
		TraceErr(m,"ERROR: strapi_GetRangeByKey failed at %s: %d",__FUNCTION__,__LINE__);
	}
	else
	{
//		TraceNotice(m,"Shiva: mAssignLCN: from: %d to: %d", from, to);
	}

	/* Get New LCNs */
	LoopCount = 0;
	for(index = to; ((LoopCount < MAX_NUM_LCN_ENTRY)&& (index >= from)); index --)
	{

		if(strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sgt), index, (void *)(&service)) == TRUE)
		{
			newLCN[LoopCount] = service.LogicalChannelNum;
			TraceNotice(m,"New LCN: %d at %d",newLCN[LoopCount],LoopCount);
			LoopCount++;
		}
		
	}

	/* Remove LCNs which does not exist anymore*/
	for(i = 0; i < MAX_NUM_LCN_ENTRY; i++)
	{
		if(psvcdat->MultipleLCN[i] != INVALID_LCN)
		{
			Found = FALSE;
			for(j = 0; j < MAX_NUM_LCN_ENTRY; j++)
			{
				if(psvcdat->MultipleLCN[i] == newLCN[j])
				{
					Found  = TRUE;
					break;
				}
				
			}
			if(!Found)
			{
				TraceNotice(m,"LCN: %d removed for service: ONID[%d] TSID[%d] SVCID[%d]",psvcdat->MultipleLCN[i],DataAcqInstance.Onid, DataAcqInstance.Tsid, psvcdat->ServiceId);
				psvcdat->MultipleLCN[i] = INVALID_LCN;
				
				/* Check service is TV or Radio */
				if (IsDigitalTvChannel (psvcdat))
				{
					removeCurTv++;
				}
				else if (IsDigitalRadioService (psvcdat))
				{
					removeCurRadio++;
				}

			}
		}
		
	}
	
	/* Add New LCNs */
	for(i = 0; i < MAX_NUM_LCN_ENTRY; i++)
	{
		if(newLCN[i] != INVALID_LCN)
		{
			Found  = FALSE;
			for(j = 0; j < MAX_NUM_LCN_ENTRY; j++)
			{
				if(psvcdat->MultipleLCN[j] == newLCN[i])
				{
					Found  = TRUE;
					break;
				}
				
			}
			if(!Found)
			{
				for(j = 0; j < MAX_NUM_LCN_ENTRY; j++)
				{
					if(psvcdat->MultipleLCN[j] == INVALID_LCN)
					{
						psvcdat->MultipleLCN[j] = newLCN[i];
						TraceNotice(m,"LCN: %d Added for service: ONID[%d] TSID[%d] SVCID[%d]",psvcdat->MultipleLCN[j],DataAcqInstance.Onid, DataAcqInstance.Tsid, psvcdat->ServiceId);
						break;
					}
				}
				if(j == MAX_NUM_LCN_ENTRY)
				{
					TraceErr(m,"ERROR: LCNs overflow");
				}
				
				/* Check service is TV or Radio */
				if(IsDigitalTvChannel(psvcdat))
				{
					mDigitalTvChannelsFound++;
				}
				else if(IsDigitalRadioService(psvcdat))
				{
					mDigitalRadioChannelsFound++;
				}
			}
		}
	}


}


Bool CHsvDvbsAstra_mAcq::IsManualInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return ((mode == insstate_InstallationManual)? TRUE: FALSE);
}

Bool CHsvDvbsAstra_mAcq::IsUpdateInstall(void)
{
	int mode, state;
	
	rins_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate ))? TRUE: FALSE);
}

int CHsvDvbsAstra_mAcq::MapRollOffFactor(int RollOff)
{	
	int RetVal = IHsvSatelliteFrontEnd_RollOffOP35;

	switch(RollOff)
	{
		case 0:
			RetVal = IHsvSatelliteFrontEnd_RollOffOP35;
			break;
		case 1:
			RetVal = IHsvSatelliteFrontEnd_RollOffOP25;
			break;
		case 2:
			RetVal = IHsvSatelliteFrontEnd_RollOffOP20;
			break;
		default:
			break;
	}

	TraceNotice(m, "%s: RetVal : %d", __FUNCTION__, RetVal);
	return RetVal;
}


/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iacqpow */

void CHsvDvbsAstra_mAcq::Init(void)
{
	/* Creating the pump */
	mDataAcqPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE,"hsvdvbastra_mDataAcq" );
	
	TraceNotice (m, " Astra Acq Module pow Initialized \n");

}

void CHsvDvbsAstra_mAcq::TurnOn(void)
{

}

void CHsvDvbsAstra_mAcq::TurnOff (void)
{

}

/*  provides IHsvDigitalAcquisition  idigacq  */
	
void CHsvDvbsAstra_mAcq::Initialise(int LnbNumber)
{
    /* Resetting all the variables */
    mDigitalChannelsFound = mDigitalTvChannelsFound = mDigitalRadioChannelsFound = 0;
    removeCurTv = removeCurRadio = 0;
	UNUSED(LnbNumber);
}

void CHsvDvbsAstra_mAcq::AcquireData(int Mode)
{

	pmp_PmpSend(mDataAcqPump, EvStartAcquire, (Nat32)Mode);
}

int CHsvDvbsAstra_mAcq::GetNumberOfDigitalChannelsFound()
{
	return mDigitalChannelsFound;
}

int CHsvDvbsAstra_mAcq::GetNumberOfDigitalChannelsRemoved()
{
    return 0;
}

int CHsvDvbsAstra_mAcq::GetNumberOfTvChannelsFound ()
{
	TraceNotice (m,"%s %d>Tv Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalTvChannelsFound);
	return mDigitalTvChannelsFound;
}

int CHsvDvbsAstra_mAcq::GetNumberOfRadioChannelsFound ()
{
	TraceNotice (m,"%s %d>Radio Added[%d]",
						__FUNCTION__,
						__LINE__,
						mDigitalRadioChannelsFound);
	return mDigitalRadioChannelsFound;
}

int CHsvDvbsAstra_mAcq::GetNumberOfTvChannelsRemoved ()
{
	TraceNotice (m,"%s %d>Tv Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurTv);
	
	return removeCurTv;
}

int CHsvDvbsAstra_mAcq::GetNumberofRadioChannelsRemoved()
{
	TraceNotice (m,"%s %d>Radio Removed[%d]",
					__FUNCTION__,
					__LINE__,
					removeCurRadio);
	
	return removeCurRadio;
}

int CHsvDvbsAstra_mAcq::GetNumberOfSdsds ()
{
	return mAstraDSDesc.NumOfSDSD;
}

Bool CHsvDvbsAstra_mAcq::GetSdsdByIndex (int count, HsvNITSatelliteDS	*SdSdEntry)
{
	Bool	RetVal = FALSE;
	if(count < mAstraDSDesc.NumOfSDSD)
	{
		memcpy(SdSdEntry, &mAstraDSDesc.SatDesc[count], sizeof(HsvNITSatelliteDS));
		mAstraDSDesc.CurrentSDSDIndex = count;
		RetVal = TRUE;
	}

	return RetVal;
}


int CHsvDvbsAstra_mAcq::GetNumberOfTvChannelsInLnb	(int Lnb)
{
	int	TvChannelsFound = 0;

	TvChannelsFound = mDigitalTvChannelsFound;
	UNUSED(Lnb);

	return TvChannelsFound;
}

int CHsvDvbsAstra_mAcq::GetNumberOfRadioChannelsInLnb	(int Lnb)
{
	int	RadioChannelsFound = 0;

	RadioChannelsFound = mDigitalRadioChannelsFound;
	UNUSED(Lnb);
	
	return RadioChannelsFound;
}


int CHsvDvbsAstra_mAcq::StoreBarkerMuxDetails(void)
{
	int RetVal = FALSE;
#if 0
	HsvBarkerMuxData BarkerMuxData;
	BarkerMuxData.NoOfRecords = 0;
	if(iutil_WriteBarkerMuxData(BarkerMuxData) == TRUE)
	{
		TraceNotice(m,"Cleared Previous BarkerMux details ");
		RetVal = TRUE;
	}
#endif

	return RetVal;
}

void CHsvDvbsAstra_mAcq::AssignLCN(HsvPgdatDigServiceData *psvcdat)
{

}

void CHsvDvbsAstra_mAcq::AcquireDataOnTimeout                        (   void    )
{
}

void CHsvDvbsAstra_mAcq::SyncTemporaryTableRecords			(	void	)
{
}

void CHsvDvbsAstra_mAcq::GetTricolorRegionNames (Nat16 **names, int *len)
{
	// Do nothing
}