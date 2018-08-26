/**********************************************************************
 *  Copyright(C) 2004 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *	C Source:		hsvdvbsins_mservicescan.c
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	 aneeshc %
 *	%date_created:	 Fri Apr 19 16:05:19 2013 %
 *
**********************************************************************/

#include "_hsvdvbsdigiturk_mScan.h"



TRACESYMBOL(m, "s2/installation/hsvdvbsdigiturk_mScan")

/****************************************************************************
 * Local include files
 ****************************************************************************/



/****************************************************************************
 * Macros and types
 ****************************************************************************/



























/****************************************************************************
 * Static variables
 ****************************************************************************/

const char CHsvDvbsDigiTurk_mScan_Priv::SvcScanEventNames[EvMax+1][32] = 
{
	"EvStart",
	"EvStop",
	"EvStartTuning",
	"EvCheckLock",
	"EvStationFound",
	"EvStationNotFound",
	"EvDataAvailable",
	"EvDataNotAvailable",
	"EvDataAquired",
	"EvComplete",
	"EvMax"
};


Pump CHsvDvbsDigiTurk_mScan_Priv::s__mPump;

InsInstance CHsvDvbsDigiTurk_mScan_Priv::s__mInstStatus;

SDSDList CHsvDvbsDigiTurk_mScan_Priv::s__mSdsdList;

HeadEndFrequencyList CHsvDvbsDigiTurk_mScan_Priv::s__mHeadEndFrequencyList;

UpdateTuneList CHsvDvbsDigiTurk_mScan_Priv::s__UpdateInstallList[MAX_SERVICES_PER_SAT];

int CHsvDvbsDigiTurk_mScan_Priv::s__mConstModuleLifeCycle = ConstTurnedOff,CHsvDvbsDigiTurk_mScan_Priv::s__mCurrentHomingMuxIndex,CHsvDvbsDigiTurk_mScan_Priv::s__mCurrentSDSDMuxIndex,CHsvDvbsDigiTurk_mScan_Priv::s__mInstallationVersion;

int CHsvDvbsDigiTurk_mScan_Priv::s__NumEntriesForUpdate = 0;


const HomingMuxData CHsvDvbsDigiTurk_mScan_Priv::EutelSatHomingFrequency[7] =
{
	{	11575000, satfeapi_PolarisationVertical, 6		},
	{	11575000, satfeapi_PolarisationVertical, 9		},
	{	11575000, satfeapi_PolarisationVertical, 8		},
	{	11575000, satfeapi_PolarisationVertical, 10		},
	{	11575000, satfeapi_PolarisationVertical, 11		},
	{	11575000, satfeapi_PolarisationVertical, 12		},
	{	(int)NULL, (int)NULL,					 (int)NULL	}
};


const HomingMuxData CHsvDvbsDigiTurk_mScan_Priv::TurkSatHomingFrequency[3] =
{
	{	11729000, satfeapi_PolarisationVertical, 5		},
	{	11675000, satfeapi_PolarisationVertical, 5		},
	{	(int)NULL, (int)NULL,					 (int)NULL	}
};


PackageDetails CHsvDvbsDigiTurk_mScan_Priv::s__DigiTurkPackages[3] = 
{
	{ DIGITURK_EUTELSAT_W3_BOUQUET_ID, EutelSatHomingFrequency},
	{ DIGITURK_TURKSAT_42E_BOUQUET_ID, TurkSatHomingFrequency},
	{ DIGITURK_EUTELSAT_W3_SD_BOUQUET_ID, EutelSatHomingFrequency},
};


PackageDetails CHsvDvbsDigiTurk_mScan_Priv::s__mUserSelectedPackage = 
{	
	INVALID_BOUQUET_ID, NULL
};


double CHsvDvbsDigiTurk_mScan_Priv::s__RollOffTable[4]  =
{
	0.35, /* "00" */
	0.25, /* "01" */
	0.20, /* "10" */
	0.00  /* "11" -- Reserved */
};

























#ifndef __cplusplus

#else

#endif





FunctionNat32 CHsvDvbsDigiTurk_mScan_Priv::s__EventActionMatrix[EvMax][StMax] = 
{
						/*	   StIdle,						StStart,					StHomingScan,				StDemuxWait,				StAcquireWait,				StSDSDScan			*/
/* EvStart */				{  FNADDR(FuncStartServiceScan),NULL,						NULL,						NULL,						NULL,						NULL					},
/* EvStop */				{  NULL,						FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan)	},
/* EvStartTuning */			{  NULL,						FNADDR(FuncStartTuning),	NULL,						NULL,						NULL,						NULL					},
/* EvCheckLock */		    {  NULL,						NULL,						FNADDR(FuncCheckLockStatus),NULL,						NULL,						FNADDR(FuncCheckLockStatus)	},
/* EvStationFound */		{  NULL,						NULL,						FNADDR(FuncStationFound),	NULL,						NULL,						FNADDR(FuncStationFound)		},
/* EvStationNotFound */		{  NULL,						NULL,						FNADDR(FuncNoStationFound),	NULL,						NULL,						FNADDR(FuncNoStationFound)	},
/* EvDataAvailable */		{  NULL,						NULL,   					NULL,						FNADDR(FuncDataAvailable),	NULL,						NULL					},
/* EvDataNotAvailable */	{  NULL,						NULL,   					NULL,						FNADDR(FuncNoDataAvailable),NULL,						NULL					},
/* EvDataAcquired */		{  NULL,						NULL,   					NULL,						NULL,						FNADDR(FuncDataAcquired),	NULL					},
/* EvComplete */			{  NULL,						FNADDR(FuncComplete),		FNADDR(FuncComplete),		FNADDR(FuncComplete),		FNADDR(FuncComplete),		FNADDR(FuncComplete)	}
};



/****************************************************************************
 * Static functions
 ****************************************************************************/

void CHsvDvbsDigiTurk_mScan_Priv::PumpHandler(int event, Nat32 param)
{
	TraceNotice (m, "%s event %s State %d \n", __FUNCTION__, SvcScanEventNames[event],  CURRENT_STATE);
	if(VALID_EVENT(event) && VALID_STATE(CURRENT_STATE))
	{
		if(EventActionMatrix[event][CURRENT_STATE] != NULL)
		{
			TraceNotice (m, "Handled %s event %s State %d \n", __FUNCTION__, SvcScanEventNames[event],  CURRENT_STATE);
			FPCALL(EventActionMatrix[event][CURRENT_STATE])(param);
		}
		else
		{
			TraceNotice (m, "Ignored %s event %s State %d \n", __FUNCTION__, SvcScanEventNames[event],  CURRENT_STATE);
		}
	}
}

void CHsvDvbsDigiTurk_mScan_Priv::mStopSdm (void)
{
	SET_INS_STATE (StStart);
	if(ctrl_GetMode(HsvDmxMain) == ctrl_Idle)
	{
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	else
	{
		ctrl_StopCollection(HsvDmxMain);
	}
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncStopServiceScan (Nat32 Param)
{
	TraceNotice(m,"%s:%d\n",__FUNCTION__, __LINE__);
	
	/* Stop the SDM */
	isigstr_StopSigStrMeasAll();
	if (ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection(HsvDmxMain);
	}
	
	mInitInstallationValues(iinsN_EventInsStopped);

	UNUSED (Param);
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncStationFound (Nat32 Param)
{
	/* Start the SDM module. TODO: Check with Pavan: whether the mode should be Normal */
	SET_INS_STATE(StDemuxWait);
	ctrl_StartCollection(HsvDmxMain, ((HOMING_DATA_ACQUIRED)? ctrl_Normal : ctrl_HomingMuxData));
	UNUSED (Param);
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncNoStationFound (Nat32 Param)
{
	TraceErr  (m, "%s\n", __FUNCTION__);

	/* continue with the scan to be based on SDSD scan or iterting to next Homing MUX in the Package list */
	SET_INS_STATE (StStart);
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	
	UNUSED (Param);
}


void CHsvDvbsDigiTurk_mScan_Priv::FuncDataAvailable (Nat32 Param)
{
	TraceNotice(m,"%s mSdsdList.NumofSDSDs %d\n",__FUNCTION__, mSdsdList.NumofSDSDs);
	
	SET_INS_STATE(StAcquireWait);
	if(HOMING_DATA_ACQUIRED)
	{
		/*Lnb number is ignored in mAcq*/
		idataacq_AcquireData(idataacq_Fallback);	
	}
	else
	{
		idataacq_Initialise (0);
		mGetSDSDFromStrapi();
		mGetHeadEndFrequencyFromStrapi();
		idataacq_AcquireData(idataacq_Homing);
	}

	UNUSED (Param);
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncNoDataAvailable (Nat32 Param)
{
	mStopSdm();

	UNUSED (Param);
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncDataAcquired (Nat32 Param)
{
	/*Update the progress*/
	iinsN_OnEvent(iinsN_EventInsProgress, mInstStatus.Lnb);
	iinsN_OnEvent (iinsN_EventChannelFound, mInstStatus.Lnb);
	mStopSdm();

	UNUSED (Param);
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncCheckLockStatus(Nat32 Cookie)
{
	FResult		RetVal;
	int			LnbNumber, LnbType, LockStatus, LockedFreq, Polarization,  SymbolRate,IqMode,  Bandwidth;

	RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);
	
	TraceNotice (m, "%s Frequency %d Sym %d LockStatus %d RetVal %d\n", __FUNCTION__, LockedFreq, SymbolRate, LockStatus, RetVal);
	if(RetVal == err_Ok)
	{
		pmp_PmpSend(mPump, ((LockStatus != 0)? EvStationFound : EvStationNotFound), (Nat32)NULL);
	}
	else
	{
		TraceErr(m, "%s satfeapi_GetSatelliteFrontEndParams returns failure", __FUNCTION__);
		pmp_PmpSend(mPump, EvStationNotFound, (Nat32)NULL);
	}
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncStartTuning (Nat32 Param)
{
	int		RetVal, SymbolRate = 0, ModlnStd = -1, ModlnType = -1, IqMode = -1, Frequency, Polarization, CodeRate=0;
	int 	RollOff = -1, FEC = -1, Pilots = -1; 

	RetVal = mGetNextTunerParameters(&Frequency, &Polarization, &SymbolRate, &ModlnStd, &ModlnType, &CodeRate);
	
	if(RetVal == err_Ok) 
	{
		/* Have to do a direct tuning here */
		SET_INS_STATE((HOMING_DATA_ACQUIRED)? StSDSDScan : StHomingScan);
		
		TraceNotice (m, "satfeapi_SatelliteFrontEndTune done with params <%d %d %d %d %d %d %d>\n", mInstStatus.Lnb, mInstStatus.LnbType, Frequency, Polarization, SymbolRate, ModlnStd, ModlnType);
		TraceNotice(m, "%s mSdsdList.NumofSDSDs %d", __FUNCTION__, mSdsdList.NumofSDSDs);
		TraceNotice(m, "%s Tune for SDSD Num %d of total SDSD %d", __FUNCTION__, (CURRENT_SDSD_MUX_INDEX-1), mSdsdList.NumofSDSDs);
		RetVal = satfeapi_SatelliteFrontEndTune(mInstStatus.Lnb, mInstStatus.LnbType, Frequency, \
									   SymbolRate, Polarization, mInstStatus.Cookie, ModlnStd, ModlnType, CodeRate, RollOff, FEC, Pilots);
		if (RetVal != err_Ok)
		{
			SET_INS_STATE (StStart);
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
		}
	}
	else
	{
		TraceNotice (m, "%s Package only scan completed on Lnb %d \n", __FUNCTION__, mInstStatus.Lnb);
		
		/* Will ensure to sync the cuurent data */
		if(mIsUpdateInstall() && HOMING_DATA_ACQUIRED)
		{
			idataacq_SyncTemporaryTableRecords();
		}
		else if(HOMING_DATA_ACQUIRED)
		{
			pmp_PmpSend(mPump, EvComplete, (Nat32)NULL);
		}
		else
		{
			mInitInstallationValues(iinsN_EventInsFailed);
		}
	}
	UNUSED (Param);
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncStartServiceScan (Nat32 Param)
{
	int						i = MAX_NUM_LNBS_SUPPORTED;
	int MaxPkg, flag = 0;
	FResult					RetVal = err_NotSupported;
	HsvPgdatDigSatInfoData	SatInfo;
	CURRENT_SDSD_MUX_INDEX = 0;
	mSdsdList.NumofSDSDs = 0;

	/* Retrieve the User selected package */
	RetVal = mGetUserPackageDetails();

	if (RetVal == err_Ok)
	{
		/* Getting the LNB Details */
		for(i=0; i < MAX_NUM_LNBS_SUPPORTED; i++)
		{
			SatInfo.LnbNumber = i;
			if (pgdb_GetByKey (SAT_INFO_TABLE, (Address) &SatInfo) == TRUE)
			{
				for (MaxPkg=0; MaxPkg<MAX_DIGITURK_PKG; MaxPkg++)
				{
					TraceNotice(m, "SatInfo.SatelliteId = %d, SatelliteId = %d", SatInfo.SatelliteId, mUserSelectedPackage.HomingMuxDetails[MaxPkg].SatelliteId);
					if(SatInfo.SatelliteId == mUserSelectedPackage.HomingMuxDetails[MaxPkg].SatelliteId)
					{
						mInstStatus.Lnb = i;
						mInstStatus.LnbType = SatInfo.LnbType;
						mInstStatus.Polarization = mUserSelectedPackage.HomingMuxDetails[MaxPkg].Polarization;

						TraceNotice (m, "In HomingStart Setting LNB as %d and Type %d mInstStatus.Polarization %d\n",mInstStatus.Lnb,mInstStatus.LnbType, mInstStatus.Polarization);
					
						mInitInstallationValues(iinsN_EventPkgInstallStart);

						mStopSdm();
						flag = 1;
						break;
					}
					
					
				}
			}
			if (flag == 1)
				break;
		}
	}
	if(i == MAX_NUM_LNBS_SUPPORTED)
	{
		TraceErr (m, "No Sat Info... \n");
		mInitInstallationValues(iinsN_EventInsFailed);
		/* Notify installation failed/completed */
	}
	UNUSED (Param);
}

void CHsvDvbsDigiTurk_mScan_Priv::FuncComplete(Nat32 Param)
{
	mInitInstallationValues(iinsN_EventPkgInstallEnd);
}

FResult CHsvDvbsDigiTurk_mScan_Priv::mGetUserPackageDetails(void)
{
	int		i;
	FResult	RetVal = err_NotSupported;
	Nat32	PackageId = insstate_GetAttribute(mInstStatus.InstallationMode, insstate_AttributePackageId);
	Nat16   BouquetId = mMapBouquetIdtoPackageId(PackageId);

	TraceNotice(m,"%s PackageId %d\n",__FUNCTION__, BouquetId);
	for(i=0; i < 3; i++)
	{
		if(DigiTurkPackages[i].BouquetIndex == BouquetId)
		{
			mUserSelectedPackage.BouquetIndex = BouquetId;
			mUserSelectedPackage.HomingMuxDetails = DigiTurkPackages[i].HomingMuxDetails;
			RetVal = err_Ok;
			break;
		}
	}
	if(RetVal != err_Ok)
	{
		TraceErr(m,"Invalid PackageId index:%d",(int)PackageId);
	}
	return RetVal;
}

void CHsvDvbsDigiTurk_mScan_Priv::mInitInstallationValues(int EventId)
{
	TraceNotice(m, "%s EventId %d", __FUNCTION__, EventId);
	
	SET_INS_STATE(StIdle);
	SET_INS_MODE(insstate_InstallationNone);
	CURRENT_HOMING_MUX_INDEX = CURRENT_SDSD_MUX_INDEX = 0;
	memset((Address)&mSdsdList, 0, sizeof(mSdsdList));
	mInstallationVersion = 0;
	
	if(mIsUpdateInstall())
	{
		mBuildCurrentFrequencyList ();

		
		HsvPgdatDigServiceData svcdat;
		if(pgdb_GetByIndex(SERVICE_TABLE, 0, (Address)&svcdat) == TRUE)
		{
			TraceNotice(m, "%s Last ServiceListVersion %d", __FUNCTION__, svcdat.ServiceListVersion);
			mInstallationVersion = ++(svcdat.ServiceListVersion);
		}
	}

	//TraceNotice(m, "Nilanjan: %s", __FUNCTION__);
	if(EventId == iinsN_EventPkgInstallEnd)
	{
		TraceNotice(m, "%s PackageId set %d ", __FUNCTION__, insstate_GetAttribute(mInstStatus.InstallationMode, insstate_AttributePackageId));
		iinsN_OnEvent(iinsN_EventPackageId, insstate_GetAttribute(mInstStatus.InstallationMode, insstate_AttributePackageId));
	}
	iinsN_OnEvent(EventId, 0);
}

Bool CHsvDvbsDigiTurk_mScan_Priv::mGetSDSDFromStrapi(void)
{
	int i;
	int NumSdsds = 0;
	HSVSPTYPE(SatelliteDS, dvb, nit)    SatelliteDSDesc;
    
    mSdsdList.NumofSDSDs = strapi_GetSize(HsvMain, HSVSPID(SatelliteDS, dvb, nit));
    
	for(i = 0; i < mSdsdList.NumofSDSDs; i++ )
    {
        if(strapi_GetByIndex(HsvMain, HSVSPID(SatelliteDS, dvb, nit), i, (void*)(&SatelliteDSDesc)))
        {
            mSdsdList.SDSD[NumSdsds] = SatelliteDSDesc;
			TraceNotice (m, "%s  SDSD[%d] Entry <%d %d %d %d>\n", __FUNCTION__, NumSdsds, mSdsdList.SDSD[NumSdsds].Original_NetworkId, mSdsdList.SDSD[NumSdsds].Tsid, mSdsdList.SDSD[NumSdsds].Frequency, mSdsdList.SDSD[NumSdsds].SymbolRate);
			NumSdsds++;
		}
    }
	mSdsdList.NumofSDSDs = NumSdsds;
    
	TraceNotice (m, "SvcScan: %s Num Of Homing SDSD = %d\n", __FUNCTION__, mSdsdList.NumofSDSDs);
    
	return 0;
}

Bool CHsvDvbsDigiTurk_mScan_Priv::mGetHeadEndFrequencyFromStrapi(void)
{
	int i;
	int NumOfEntries = 0;
	HSVSPTYPE(HeadEndFrequencyList, dvb, nit)    HeadEndFrequencyList;
    
    mHeadEndFrequencyList.NumofFreqs = strapi_GetSize(HsvMain, HSVSPID(HeadEndFrequencyList, dvb, nit));
    
	for(i = 0; i < mHeadEndFrequencyList.NumofFreqs; i++ )
    {
        if(strapi_GetByIndex(HsvMain, HSVSPID(HeadEndFrequencyList, dvb, nit), i, (void*)(&HeadEndFrequencyList)))
        {
            mHeadEndFrequencyList.HeadEndFrequency[NumOfEntries] = HeadEndFrequencyList;
			TraceNotice (m, "%s  HeadEnd Entry <%d %d>\n", __FUNCTION__, HeadEndFrequencyList.Tsid, HeadEndFrequencyList.SiteHeadEndFrequency);
			NumOfEntries++;
		}
    }
	mHeadEndFrequencyList.NumofFreqs = NumOfEntries;
    
	TraceNotice (m, "%s Num Of HeadEndFrequency %d\n", __FUNCTION__, mHeadEndFrequencyList.NumofFreqs);
    
	return 0;
}

FResult CHsvDvbsDigiTurk_mScan_Priv::mGetNextTunerParameters(int *Frequency, int *Polarization, int *SymbolRate, int *ModlnStd, int *ModlnType, int *CodeRate)
{
	FResult retval = err_BadParameter;

	if( HOMING_DATA_ACQUIRED )
	{
		if( CURRENT_SDSD_MUX_INDEX < (mSdsdList.NumofSDSDs) )
		{
			*Frequency    =		mMapFrequency(CURRENT_SDSD_MUX_INDEX);

			*Polarization =		mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX].Polarization;
			*SymbolRate   =		mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX].SymbolRate;
			*ModlnStd     =		mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX].ModulationSystem;
			*ModlnType    =		mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX].ModulationType;
			*CodeRate    =		mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX].FECInner;
			
			/* Made in MHz because of the decimal factor for Turksat 2nd homing MUX */

			CURRENT_SDSD_MUX_INDEX++;
			retval = err_Ok;
		}
	}
	else
	{
		if( mUserSelectedPackage.HomingMuxDetails[CURRENT_HOMING_MUX_INDEX].Frequency != (int)NULL )
		{
			*Frequency    =		mUserSelectedPackage.HomingMuxDetails[CURRENT_HOMING_MUX_INDEX].Frequency;
			*Polarization =		mUserSelectedPackage.HomingMuxDetails[CURRENT_HOMING_MUX_INDEX].Polarization;

			CURRENT_HOMING_MUX_INDEX++;
			retval = err_Ok;
		}
	}

	return retval;
}

int CHsvDvbsDigiTurk_mScan_Priv::CalculateBandwidthFromSdsd (Nat8 RollOff, int SymbolRate, Nat8 FECInner)
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

Nat16 CHsvDvbsDigiTurk_mScan_Priv::mMapBouquetIdtoPackageId(Nat32 PackageId)
{
	Nat16 retval = 0xFFFF;

	switch (PackageId)
	{
		case DIGITURK_TURKSAT_PACKAGE_ID:
			retval = DIGITURK_TURKSAT_42E_BOUQUET_ID;
			break;
		case DIGITURK_EUTELSAT_PACKAGE_ID:
			retval = ((mInstStatus.LnbType == LnbMdutype1) ? DIGITURK_EUTELSAT_W3_SD_BOUQUET_ID : DIGITURK_EUTELSAT_W3_BOUQUET_ID);
			break;
	}
	return retval;
}

Bool CHsvDvbsDigiTurk_mScan_Priv::mIsUpdateInstall(void)
{
	int mode, state;
	
	insstate_GetCurrentInstallationState(&mode, &state);

	return (((mode == insstate_InstallationUpdate) || (mode == insstate_InstallationAutomaticUpdate ))? TRUE: FALSE);
}

int CHsvDvbsDigiTurk_mScan_Priv::mMapFrequency(int index)
{
	int i, retval;
	
	retval = mSdsdList.SDSD[index].Frequency;

	if(mInstStatus.LnbType == LnbMdutype1)
	{
		for(i = 0; i < mHeadEndFrequencyList.NumofFreqs; i++ )
		{
			if(mSdsdList.SDSD[index].Tsid == mHeadEndFrequencyList.HeadEndFrequency[i].Tsid)
			{
				TraceNotice(m,"Nilanjan: Replacing freq %d with %d", mSdsdList.SDSD[index].Frequency, (mHeadEndFrequencyList.HeadEndFrequency[i].SiteHeadEndFrequency*1000));
				retval = (mHeadEndFrequencyList.HeadEndFrequency[i].SiteHeadEndFrequency * 1000);
			}
		}
	}
	return retval;
}

int CHsvDvbsDigiTurk_mScan_Priv::isdsddata_GetSDSDData(void *data)
{
	SDSDList *SDSDListData	 = (SDSDList *)data;

	memcpy((Address)SDSDListData, (Address)(&mSdsdList), sizeof(SDSDList));
	
	return (CURRENT_SDSD_MUX_INDEX-1);
}

int CHsvDvbsDigiTurk_mScan_Priv::isdsddata_GetHomingData(void *data)
{
	PackageDetails *HomingData = (PackageDetails *)data;

	memcpy((Address)HomingData, (Address)(&mUserSelectedPackage), sizeof(PackageDetails));
	
	return (CURRENT_HOMING_MUX_INDEX-1);
}

/****************************************************************************
 * External functions
 ****************************************************************************/

/* Provides IHsvSdmControlNotifyEx		iscanctrlN */
void CHsvDvbsDigiTurk_mScan_Priv::iscanctrlN_OnEvent(HsvDemux Dmx, int EventId,int Value)
{
	/* Notificaton Handler for SDM events */
	TraceErr(m, "%s EventId 0x%x Value 0x%x ", __FUNCTION__, EventId, Value);
	if (VALID_DEMUX(Dmx))
	{
		switch (EventId)
		{
			case iscanctrlN_DataNotAvailable:
				 pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
				 break;
			case iscanctrlN_StoppedCollection:
				 pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
				 break;
			case iscanctrlN_DataAvailable:
				if(HOMING_DATA_ACQUIRED)
				{
					if(Value & iscanctrlN_SDT)
					{
						pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
					}
					else
					{
						pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
					}
				}
				else
				{
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				}
				break;
			case iscanctrlN_SiDataAvailable:
				 if(HOMING_DATA_ACQUIRED)
				 {
					pmp_PmpSend(mPump, EvDataAvailable, (Nat32)NULL);
				 }	
				 break;
			case iscanctrlN_StartedCollection:
				 break;
			default:
				break;
		}
	}
	UNUSED (Value);	/* TODO: Make sure this is not needed */
}

/* provides IPlfApiDvbsNotify	isvcscanplfApidvbsN */

void CHsvDvbsDigiTurk_mScan_Priv::plfApidvbsN_OnLockChanged( Bool LockState)
{
	/* TODO: Verify Cookie check is needed here or not */
	/* Notifiation Handler for DVB-S platform FE */	
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

/* provides IHsvDigitalScanData		iscandata	*/


void CHsvDvbsDigiTurk_mScan_Priv::iscandata_GetPtcInfo (HsvInstallationPTC *ptc)
{
	int count;
	
	ptc->LnbNumber        = mInstStatus.Lnb;
	ptc->Polarization     =  mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].Polarization;
	ptc->Frequency        =  mMapFrequency(CURRENT_SDSD_MUX_INDEX - 1);  
	ptc->SDSDFrequency    =  mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].Frequency;
	ptc->SymbolRate       = mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].SymbolRate;
	ptc->ModulationType   = (Nat8)mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].ModulationType;
	ptc->ModulationStd    = (Nat8)mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].ModulationSystem;
	ptc->CodeRate   	  = mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].FECInner;

	if(mIsUpdateInstall())
	{
		for (count = 0; count <= NumEntriesForUpdate ; count++)
		{
			if (  (UpdateInstallList[count].Polarization == ptc->Polarization) && 
				 (util_CheckFreqDuplicationwithRolFact(ptc->Frequency, UpdateInstallList[count].Frequency, ptc->SymbolRate)))
			{
				/* Frequency drift handling. SI based check will happen in Acq module */
				TraceNotice(m,"%s: Replacing TS freq %d with %d", __FUNCTION__, ptc->Frequency, UpdateInstallList[count].Frequency);
				ptc->Frequency = UpdateInstallList[count].Frequency;
				break;
			}
			if ( count == NumEntriesForUpdate &&
				 NumEntriesForUpdate  < (MAX_SERVICES_PER_SAT - 1) )
			{				
				++NumEntriesForUpdate;
				UpdateInstallList[NumEntriesForUpdate].Frequency = ptc->Frequency;
				UpdateInstallList[NumEntriesForUpdate].Polarization = ptc->Polarization;
				UpdateInstallList[NumEntriesForUpdate].SymbolRate = ptc->SymbolRate;
				break;
			}
		}
	}
	ptc->TPID             = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);
		
	ptc->QSignalStrength  = 0;
	ptc->SSignalStrength  = 0;
	ptc->HierarchyMode    = HsvHierarchyNone;
	ptc->StreamPriority   = HsvStreamPriorityHigh;
	ptc->ChannelBandwidth = CalculateBandwidthFromSdsd (mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].RollOff, mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].SymbolRate, mSdsdList.SDSD[CURRENT_SDSD_MUX_INDEX-1].FECInner);
}

int CHsvDvbsDigiTurk_mScan_Priv::iscandata_GetInstallationVersion(void)
{
	/* TODO: Have to implement this function when update installation comes */
	return mInstallationVersion;
}

void CHsvDvbsDigiTurk_mScan_Priv::iscandata_SyncComplete(void)
{
	pmp_PmpSend(mPump, EvComplete, (Nat32)NULL);
}

void CHsvDvbsDigiTurk_mScan_Priv::iscandata_GetPtcInfoForSdSd (HsvInstallationPTC *ptc)
{
}


/* provides IHsvPower	isvcscanpow */

void CHsvDvbsDigiTurk_mScan_Priv::iscanpow_Init    ( void )
{
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbm7_svcscan" );
	mConstModuleLifeCycle = ConstInitialized;

	TraceNotice (m, " ServiceScan Module pow Initialized \n");
	/* Initialize acquisition module also */
	iacqpow_Init();
}

void CHsvDvbsDigiTurk_mScan_Priv::iscanpow_TurnOn  ( void )
{
	mConstModuleLifeCycle = ConstTurnedOn;
	
	mInstStatus.Cookie = 0;
	/* Initializing the other modules */
	idataacq_Initialise (0);
}

void CHsvDvbsDigiTurk_mScan_Priv::iscanpow_TurnOff ( void )
{
	mConstModuleLifeCycle = ConstTurnedOff;
}

/* provides IHsvSatalliteInstallation isvcscan */

int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetCurrentInstallationState (int *mode, int *state)
{
	/* Function to get the installation mode and status */
	int		RetVal = err_BadParameter;

	if (mode && state)
	{
		*mode  = CURRENT_MODE;
		*state = ((CURRENT_STATE == StIdle)? insstate_InstallationStateIdle : insstate_InstallationStateInProgress);
		
		RetVal = err_Ok;
		TraceErr (m, "mode %d state %d\n",*mode, *state);
	}
	
	
	return RetVal;
}

FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_WriteBarkerMuxData(void)
{
	TraceNotice(m,"DIGITURK:isvcscan_WriteBarkerMuxData"); 
	idataacq_StoreBarkerMuxDetails();
	return 0;
}
/* Functions for automatic installation + update installation */
FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_StartInstallation(int Source, int Lnb, int Mode)
{
	FResult			RetVal = err_BadParameter;

	TraceErr(m, "%s TURNED_ON %d Source %d Lnb %d Mode %d", __FUNCTION__, TURNED_ON, Source, Lnb, Mode);
	if (TURNED_ON)
	{
		/* Currently supporting only service scan. Have to update VALID_MODE as features added */
		if (VALID_SOURCE(Source) && IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
		{
			if (SCAN_NOT_INPROGESS)
			{
				TraceNotice (m, " No Service Scan in progress.. Initiating \n");
				
				SET_INS_MODE(Mode);

				pmp_PmpSend(mPump, EvStart, (Nat32)NULL);
			}
			RetVal = err_Ok;
		}
	}

	return RetVal;
}

FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_StopInstallation(void)
{
	FResult	RetVal = err_Ok;

	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);

	return RetVal;
}

/* During auto install once the notification is given, it has to display the number of TV and Radio channels */
int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetNumberOfTvChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsFound();

	TraceNotice(m, "%s %d", __FUNCTION__, RetVal);

	return RetVal;
}
int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetNumberofRadioChannelsFound (int Mode, int Lnb)
{
	int	RetVal = 0;
	
	RetVal = idataacq_GetNumberOfRadioChannelsFound ();

	TraceNotice(m, "%s %d", __FUNCTION__, RetVal);
	return RetVal;
}

int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetNumberOfTvChannelsRemoved(int Mode, int Lnb)
{
	int RetVal = 0;

	RetVal = idataacq_GetNumberOfTvChannelsRemoved();

	TraceNotice(m, "%s %d", __FUNCTION__, RetVal);

	UNUSED(Lnb);
	
	return RetVal;
}
int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetNumberofRadioChannelsRemoved(int Mode, int Lnb)
{
	int RetVal = 0;

	RetVal = idataacq_GetNumberofRadioChannelsRemoved();

	TraceNotice(m, "%s %d", __FUNCTION__, RetVal);

	UNUSED(Lnb);

	return	RetVal;
}

int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetNumberOfDigitalChannelsAdded(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetNumberOfDigitalChannelsRemoved(void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetNumberOfDigitalChannelsMoved (void)
{
	int		Retval = 0;
	/* Service Scan doesnt expects this to be called: Can call IS_SERVICE_SCAN*/
	return Retval;
}

void CHsvDvbsDigiTurk_mScan_Priv::iscan_GetSIDetails(HsvSDMSIDataValues* SiValues)
{
	if(SiValues)
	{
		Nat32	PackageId = insstate_GetAttribute(mInstStatus.InstallationMode, insstate_AttributePackageId);
		
		TraceNotice(m,"%s PackageId %d\n",__FUNCTION__, PackageId);
		SiValues->BouquetId = mMapBouquetIdtoPackageId(PackageId);
	}
}

void CHsvDvbsDigiTurk_mScan_Priv::idataacqN_OnDataAquired(Bool Status)
{
	TraceNotice (m, "%s\n", __FUNCTION__);
	if(TURNED_ON)
	{
		pmp_PmpSend(mPump, EvDataAcquired, (Nat32)NULL);
	}
}

void CHsvDvbsDigiTurk_mScan_Priv::mBuildCurrentFrequencyList (void)
{
	int		Count, From, To, NumEntry =0;
	HsvPgdatDigTSData	TempTsData;
	
	TempTsData.LnbNumber = mInstStatus.Lnb; 
	if (pgdb_GetRange (PTC_TABLE, 1, (Address)&TempTsData, &From, &To))
	{
		for (Count = From, NumEntry = 0; ((Count <= To) && (NumEntry < MAX_SERVICES_PER_SAT)); Count++,NumEntry++)
		{
			if (TRUE == pgdb_GetByIndex (PTC_TABLE, Count ,(Address)&TempTsData))
			{
				UpdateInstallList[NumEntry].Frequency = TempTsData.Frequency;
				UpdateInstallList[NumEntry].Polarization = TempTsData.Polarization;
				UpdateInstallList[NumEntry].SymbolRate = TempTsData.SymbolRate;
				TraceNotice(m,"[%d][%d][%d]",UpdateInstallList[NumEntry].Frequency,TempTsData.Frequency,Count);
			}
		}
		NumEntriesForUpdate = NumEntry;
		
	}	
}


int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetAttribute(int Mode, int AttributeId)
{
	return 0;
}

FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return err_Ok;
}

Bool CHsvDvbsDigiTurk_mScan_Priv::iscan_SetManualInstallationAttributes (int AttributeId, int Value)
{
	return FALSE;
}

FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_StoreManualInstallationValues (void)
{
	return 0;
}

int CHsvDvbsDigiTurk_mScan_Priv::iscan_GetScanProgressStatus (int Mode)
{

	int RetVal = 0;
	if(mSdsdList.NumofSDSDs != 0)
	{
		RetVal = (int)(CURRENT_SDSD_MUX_INDEX * 100 )/ mSdsdList.NumofSDSDs;
	}
	return RetVal;
}
			
void CHsvDvbsDigiTurk_mScan_Priv::plfApidvbsN_OnBlindScanEnd ()
{
}
			
FResult CHsvDvbsDigiTurk_mScan_Priv::iscan_LoadManualInstallationDefaultValues (void)
{
	return 0;
}
