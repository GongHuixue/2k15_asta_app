/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *          %name: hsvdvbsfreesat_mScan.c %
 *       %version:  %
 * %date_modified: %
 *    %derived_by:  %
 */

#include "CHsvDvbsFreesat_mScan.h"
#include <string>

/****************************************************************************
 * Local include files
 ****************************************************************************/


TRACESYMBOL(m, "/installation/comp/hsvdvbsfreesat/HsvDvbsFreeSat_mScan")

/****************************************************************************
 * Macros and types
 ****************************************************************************/
 #define	FREESAT_SAT_ID		(ASTRA_28_2_E)

 #define	SAT_INFO_TABLE		(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_SatInfo)

#define	PTC_TABLE			(IHsvProgramDatabaseConstants_Satellite |IHsvProgramDatabaseConstants_DigitalTS)

#define	SERVICE_TABLE		(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_DigitalService)

#define	PRESET_TABLE		(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_Preset)

#define IS_HOMING_SERVICE(X)	((((X) & (1 << 0x03)) && ((X) & (1 << 0x04)) && ((X) & (1 << 0x07)) && ((X) & (1 << 0x0B))) ? TRUE : FALSE)
#define MAX_POSTCODE_LEN		(9)
#define FREESAT_DEFAULT_HD_BOUQUET_ID	(272)
#define HOMING_SERVICE_TABLE	(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_HomingService)
#define FREESAT_LD_SERVICE		(1)
#define FREESAT_ILD_SERVICE		(2)

/*static variables*/

int CHsvDvbsFreesat_mScan::s__mConstModuleLifeCycle = 0;
Pump CHsvDvbsFreesat_mScan::mPump = 0xFFFF;
Bool CHsvDvbsFreesat_mScan::mInNITActualMode = FALSE;

CHsvDvbsFreesat_mScan::InsInstance CHsvDvbsFreesat_mScan::mInstStatus;

CHsvDvbsFreesat_mScan::HomingMuxData CHsvDvbsFreesat_mScan::s__FreesatPackageDetails[NO_OF_HOMING_MUX] = {{11427.8, IHsvSatelliteFrontEnd_PolarisationHorizontal, FREESAT_SAT_ID}};

CHsvDvbsFreesat_mScan::FunctionNat32 CHsvDvbsFreesat_mScan::s__EventActionMatrix[EvMax][StMax] =
{
							/*StIdle*/								/*StStart*/						/*StTunerWait*/						/*StHomingServiceDetection*/		/*StAcquirePostcodekey*/			/*StPostcodekeyAcquireWait*/		/*StAcquireRegionkey*/				/*StRegionkeyAcquireWait*/		/*StAcquireSI*/					/*StSIAcquireWait*/					/*StServiceInstallWait*/		/*StServiceInstallComplete*/
/*EvStart*/					{FNADDR(FuncStartServiceScan),			NULL,							NULL,								NULL, 								NULL,								NULL,								NULL,								NULL,							NULL,								NULL,								NULL, 							NULL							},
/*EvStop*/					{NULL, 									FNADDR(FuncStopServiceScan),	FNADDR(FuncStopServiceScan),		FNADDR(FuncStopServiceScan),		FNADDR(FuncStopServiceScan),		FNADDR(FuncStopServiceScan),		FNADDR(FuncStopServiceScan),		FNADDR(FuncStopServiceScan),	FNADDR(FuncStopServiceScan),		FNADDR(FuncStopServiceScan),		FNADDR(FuncStopServiceScan),	FNADDR(FuncStopServiceScan)		},
/*EvStartTuning*/			{NULL,									FNADDR(FuncStartTuning),		NULL,								NULL,								NULL,								NULL,								NULL,								NULL,							NULL,								NULL,								NULL,							NULL							},
/*EvCheckLock*/				{NULL,									NULL,							FNADDR(FuncCheckLockStatus),		NULL,								NULL,								NULL,								NULL,								NULL,							NULL,								NULL,								NULL,							NULL							},
/*EvIdentifyHomingService*/	{NULL,									NULL,							NULL,								FNADDR(FuncIdentifyHomingService),	NULL,								NULL,								NULL,								NULL,							NULL,								NULL,								NULL,							NULL							},
/*EvStartTableCollection*/	{NULL,									NULL,							NULL,								NULL,								FNADDR(FuncStartTableCollection),	FNADDR(FuncStartTableCollection),	FNADDR(FuncStartTableCollection),	NULL,							FNADDR(FuncStartTableCollection),	NULL,								NULL,							NULL							},
/*EvDataAvailable*/			{NULL,									NULL,							NULL,								FNADDR(FuncDataAvailable),			NULL,								FNADDR(FuncDataAvailable),			NULL,								FNADDR(FuncDataAvailable),		NULL,								FNADDR(FuncDataAvailable),			NULL,							NULL							},
/*EvDataNotAvailable*/		{NULL,									NULL,							NULL,								FNADDR(FuncDataNotAvailable),		NULL,								FNADDR(FuncDataNotAvailable),		NULL,								FNADDR(FuncDataNotAvailable),	NULL,								FNADDR(FuncDataNotAvailable),		NULL,							NULL							},
/*EvIdentifyBouquet*/		{NULL,									NULL,							NULL,								NULL,								NULL,								NULL,								NULL,								FNADDR(FuncIdentifyBouquet),	NULL,								NULL,								NULL,							NULL							},
/*EvInstallComplete*/		{NULL,									NULL,							NULL,								NULL,								NULL,								NULL,								NULL,								NULL,							NULL,								NULL,								NULL,							FNADDR(FuncInstallComplete)		}
};


CHsvDvbsFreesat_mScan::FunctionNat32 CHsvDvbsFreesat_mScan::s__FreesatHomingSrvDetectionActionMatrix[MaxScanMode][MaxScanSubMode] =
{
							/*InvalidScanMode*/		/*AcquireSIPSITables/*				/*TableAcquireWait*/				/*AcquireNITOther*/			/*NITOtherAcquireWait*/
/*InvalidScanMode*/			{NULL,					NULL, 								NULL,							NULL,						NULL							},
/*FactoryMuxMode*/			{NULL,					FNADDR(mAcquireSIPSITables),		FNADDR(mCheckDataAvailable),	FNADDR(mAcquireNitOther),	FNADDR(mCheckDataAvailable)	},
/*StoredLDSearchMode*/		{NULL,					FNADDR(mAcquireSIPSITables),		FNADDR(mCheckDataAvailable), 	NULL,						NULL							},
/*StoredILDSearchMode*/		{NULL,					FNADDR(mAcquireSIPSITables),		FNADDR(mCheckDataAvailable), 	NULL,						NULL							},
/*BlindScanMode*/			{NULL,					FNADDR(mAcquireSIPSITables),		FNADDR(mCheckDataAvailable),	FNADDR(mAcquireNitOther),	FNADDR(mCheckDataAvailable)	},
/*LDSearchMode*/			{NULL,					FNADDR(mAcquireSIPSITables),		FNADDR(mCheckDataAvailable), 	NULL,						NULL							},
/*HomingServiceMode*/		{NULL,					NULL, 								NULL,							NULL,						NULL							}
};

void CHsvDvbsFreesat_mScan::PumpHandler(int event, Nat32 param)
{
	if((event < EvMax) && (CURRENT_INS_STATE < StMax))
	{
		if(s__EventActionMatrix[event][CURRENT_INS_STATE] != NULL)
		{
			TraceNotice(m,"%s Current Instate:%d and Event:%d ",__FUNCTION__,mInstStatus.State,event);
			FPCALL(s__EventActionMatrix[event][CURRENT_INS_STATE])(param);
		}
		else
		{
			TraceNotice (m," Event skiped  - %s Event Id %d Installation State %d",__FUNCTION__, event, CURRENT_INS_STATE);
		}
	}
}

void CHsvDvbsFreesat_mScan::FuncStartServiceScan (Nat32 param)
{
	mInstStatus.FactoryMuxIndex = 0;
	mInstStatus.StoredILDServiceIndex = 0;
	mInstStatus.StoredLDServiceIndex = 0;
	mInstStatus.LinkageServiceIndex = 0;
	mInstStatus.NumOfLinkageService = 0;
	mInstStatus.BlindScanInProgress = FALSE;
	SET_SCAN_MODE(FactoryMuxMode);
	SET_SCAN_SUB_MODE(AcquireSIPSITables);
	SET_INS_STATE (StStart);
	HsvFreesatHomingServiceData homSvcData;
	
	

	TraceNotice (m," Entering function Freesat - %s CURRENT_MODE %d",__FUNCTION__, CURRENT_MODE);
	if(IHsvSatelliteInstallation_InstallationServiceScan == CURRENT_MODE)
	{
		TraceNotice (m,"In Virgin Install or ReInstall Mode");
		/*If the mode is virgin install/Reinstall then clear all stored LD and ILD homing service info*/
		memset(&homSvcData,0x00,sizeof(homSvcData));
		isettings->SetAttribute(IHsvSatelliteSettings_AttributeFreesatHomingServiceData,(Nat32)&homSvcData);
		
		mInstStatus.BouquetId = DEFAULT_FREESAT_HD_BID;
		mInstStatus.RegionId = DEFAULT_FREESAT_HD_RID;
	}

	if(IHsvSatelliteInstallation_InstallationUpdate == CURRENT_MODE)
	{
		mInstStatus.BouquetId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeBouquetId);
		mInstStatus.RegionId  = isettings->GetAttribute(IHsvSatelliteSettings_AttributeRegionId);	
	}
	/* Getting the LNB Details */
	mGetLnbDetails(FREESAT_SAT_ID);

	iinsN->OnEvent(IHsvSatelliteInstallationNotify_EventPkgInstallStart,0);

	if(ctrl->GetMode(HsvDmxMain) == IHsvSdmControl2_Idle)
	{
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	else
	{
		ctrl->StopCollection(HsvDmxMain);
	}
}

void CHsvDvbsFreesat_mScan::FuncStartTuning (Nat32 param)
{
	FResult RetVal = IHsvErrorCodeEx_Ok;
	int ModlnStd = -1;
	int IqMode = -1;
	int Cookie = 0;
	int SymbolRate = 0;
	int ModlnType = -1;
	int RollOff = -1, FEC = -1, Pilots = -1; 
	HsvFreesatHomingServiceData *HomingService;
	Nat32 Data = 0;

	TraceNotice (m," Entering function Freesat - %s Scan Mode %d",__FUNCTION__, CURRENT_SCAN_MODE);
	switch(CURRENT_SCAN_MODE)
	{
	case FactoryMuxMode:
		if(mInstStatus.FactoryMuxIndex < NO_OF_HOMING_MUX)
		{
			SET_INS_STATE(StTunerWait);
			satfeapi->SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType,
										(s__FreesatPackageDetails[mInstStatus.FactoryMuxIndex].Frequency*1000), \
										SymbolRate, s__FreesatPackageDetails[mInstStatus.FactoryMuxIndex].Polarization,
										Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);

			TraceNotice  (m,"Tune request made %d LNB Num %d LNB Type %d Freq %d Sym rate %d Pol %d",
											__LINE__, mInstStatus.LnbNumber, mInstStatus.LnbType,
											(s__FreesatPackageDetails[mInstStatus.FactoryMuxIndex].Frequency * 1000),
											SymbolRate,
											s__FreesatPackageDetails[mInstStatus.FactoryMuxIndex].Polarization);
			mInstStatus.FactoryMuxIndex++;

			
		}
		else
		{
			/*Homing service is not identified using Factory search mode, so search in stored LD list*/
			mSwitchScanMode();
		}
		break;
	case StoredLDSearchMode:
		if(mInstStatus.StoredLDServiceIndex <  mInstStatus.MaxStoredLDServiceIndex)
		{
			Data = isettings->GetAttribute(IHsvSatelliteSettings_AttributeFreesatHomingServiceData);
			HomingService = (HsvFreesatHomingServiceData*)Data;
			
			SET_INS_STATE(StTunerWait);
			satfeapi->SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType,
										HomingService->HomingServices[mInstStatus.StoredLDServiceIndex].Frequency,
										SymbolRate, HomingService->HomingServices[mInstStatus.StoredLDServiceIndex].Polarization,
										Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);

			TraceNotice  (m,"Tune request made %d LNB Num %d LNB Type %d Freq %d Sym rate %d Pol %d",
									__LINE__, mInstStatus.LnbNumber, mInstStatus.LnbType,\
									HomingService->HomingServices[mInstStatus.StoredLDServiceIndex].Frequency, SymbolRate,\
									HomingService->HomingServices[mInstStatus.StoredLDServiceIndex].Polarization);

			free(HomingService);
			
			mInstStatus.StoredLDServiceIndex++;
		}
		else
		{
			mSwitchScanMode();
		}
		break;
	case StoredILDSearchMode:
		if(mInstStatus.StoredILDServiceIndex <  mInstStatus.MaxStoredILDServiceIndex)
		{
			Data = isettings->GetAttribute(IHsvSatelliteSettings_AttributeFreesatHomingServiceData);
			HomingService = (HsvFreesatHomingServiceData*)Data;
		
			SET_INS_STATE(StTunerWait);
			satfeapi->SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType,
										HomingService->HomingServices[mInstStatus.StoredILDServiceIndex].Frequency,
										SymbolRate, HomingService->HomingServices[mInstStatus.StoredILDServiceIndex].Polarization,
										Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);

			TraceNotice  (m,"Tune request made %d LNB Num %d LNB Type %d Freq %d Sym rate %d Pol %d",
									__LINE__, mInstStatus.LnbNumber, mInstStatus.LnbType,\
									HomingService->HomingServices[mInstStatus.StoredILDServiceIndex].Frequency, SymbolRate,\
									HomingService->HomingServices[mInstStatus.StoredILDServiceIndex].Polarization);

			free(HomingService);
			
			mInstStatus.StoredILDServiceIndex++;
		}
		else
		{
			mSwitchScanMode();
		}
		break;
	case BlindScanMode:
		SET_INS_STATE(StTunerWait);
		if(mInstStatus.BlindScanInProgress)
		{
			RetVal = satfeapi->ContinueSatelliteBlindScan ();
		}
		else
		{
			RetVal = satfeapi->StartSatelliteBlindScan (mInstStatus.LnbNumber, IHsvSatelliteFrontEnd_BlindScanModeNormal);
			mInstStatus.BlindScanInProgress = TRUE;
		}

		if(IHsvErrorCodeEx_Ok != RetVal)
		{
			mSwitchScanMode();
		}
		break;
	case LDSearchMode:
		TraceNotice(m,"mInstStatus.LinkageServiceIndex %d mInstStatus.NumOfLinkageService %d",mInstStatus.LinkageServiceIndex,mInstStatus.NumOfLinkageService);
		if(mInstStatus.LinkageServiceIndex < mInstStatus.NumOfLinkageService)
		{

			SET_INS_STATE(StTunerWait);
			satfeapi->SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType,
										mInstStatus.mLinkageServiceInfo[mInstStatus.LinkageServiceIndex].Frequency, \
										SymbolRate, mInstStatus.mLinkageServiceInfo[mInstStatus.LinkageServiceIndex].Polarization,
										Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);

			TraceNotice  (m,"Tune request made %d LNB Num %d LNB Type %d Freq %d Sym rate %d Pol %d",
									__LINE__, mInstStatus.LnbNumber, mInstStatus.LnbType,
									mInstStatus.mLinkageServiceInfo[mInstStatus.LinkageServiceIndex].Frequency,
									SymbolRate,
									mInstStatus.mLinkageServiceInfo[mInstStatus.LinkageServiceIndex].Polarization);

			mInstStatus.LinkageServiceIndex ++;
		}
		else
		{
			/*Homing service is not identified, so break the installation*/
			mSwitchScanMode();
		}
		break;
	case HomingServiceMode:
		if((mInstStatus.mHomingServiceInfo.IsDataValid) && (IS_HOMING_SERVICE(mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap)))
		{
			SET_INS_STATE(StTunerWait);
			/*Reset the valid homing service flag, this done to check lock only once.
			**i.e if tuner is not locked then installtion is failed
			*/
			mInstStatus.mHomingServiceInfo.IsDataValid = FALSE;
			satfeapi->SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType,
										mInstStatus.mHomingServiceInfo.Frequency, \
										SymbolRate, mInstStatus.mHomingServiceInfo.Polarization,
										Cookie, ModlnStd, ModlnType, IqMode, RollOff, FEC, Pilots);

			TraceNotice  (m,"Tune request made %d LNB Num %d LNB Type %d Freq %d Sym rate %d Pol %d",
									__LINE__, mInstStatus.LnbNumber, mInstStatus.LnbType,
									mInstStatus.mHomingServiceInfo.Frequency,
									SymbolRate,
									mInstStatus.mHomingServiceInfo.Polarization);
		}
		else
		{
			TraceNotice  (m,"ERROR!!! Invalid condition, should not enter here");
			mSwitchScanMode();
		}
		break;
	case InvalidScanMode:
	case MaxScanMode:
	default:
		TraceNotice  (m,"ERROR!!! Invalid scan mode, should not enter %d",CURRENT_SCAN_MODE);
		break;
	}
}

void CHsvDvbsFreesat_mScan::FuncCheckLockStatus(Nat32 param)
{
	FResult	RetVal = IHsvErrorCodeEx_Ok;
	int LnbNumber = 0;
	int LnbType = 0;
	int LockStatus = 0;
	int LockedFreq = 0;
	int Polarization = 0;
	int SymbolRate =0;
	int IqMode =0;
	int Bandwidth = 0;
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	RetVal = satfeapi->GetSatelliteFrontEndParams(&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);

	TraceNotice(m, "Line %d Freq %d Sym %d  \n",__LINE__,LockedFreq, SymbolRate);
	if ((RetVal == IHsvErrorCodeEx_Ok) && (0 == LockStatus))
	{
		mNoStationFound();
	}
	else
	{
		mStationFound();
	}
}

void CHsvDvbsFreesat_mScan::FuncIdentifyHomingService(Nat32 param)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	if((CURRENT_SCAN_MODE < MaxScanMode) && (CURRENT_SCAN_SUB_MODE < MaxScanSubMode))
	{
		if(s__FreesatHomingSrvDetectionActionMatrix[CURRENT_SCAN_MODE][CURRENT_SCAN_SUB_MODE])
		{
			FPCALL(s__FreesatHomingSrvDetectionActionMatrix[CURRENT_SCAN_MODE][CURRENT_SCAN_SUB_MODE])(param);
		}
		else
		{
			TraceNotice (m,"%s %d Error Event ignored Scan mode %d Sub scan mode %d",__FUNCTION__, __LINE__, CURRENT_SCAN_MODE, CURRENT_SCAN_SUB_MODE);
		}
	}
	else
	{
		TraceNotice (m,"%s %d Invalid mode, should bot enter Scan mode %d Sub scan mode %d",__FUNCTION__, __LINE__, CURRENT_SCAN_MODE, CURRENT_SCAN_SUB_MODE);
	}
}

void CHsvDvbsFreesat_mScan::FuncStartTableCollection(Nat32 param)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	if(IHsvSdmControl2_Idle == ctrl->GetMode(HsvDmxMain))
	{
		if(StAcquirePostcodekey == CURRENT_INS_STATE)
		{
			TraceNotice(m,"Start Collection Triggered with:IHsvSdmControl2_FreesatPostcode mode for PostCodeKey Collection");
			SET_INS_STATE(StPostcodekeyAcquireWait);
			ctrl->StartCollection(HsvDmxMain, IHsvSdmControl2_FreesatPostcode);
			
		}
		else if(StAcquireRegionkey == CURRENT_INS_STATE)
		{
			TraceNotice(m,"Start Collection Triggered with:IHsvSdmControl2_FreesatPostcode mode for RegionKey Collection");
			SET_INS_STATE(StRegionkeyAcquireWait);
			ctrl->StartCollection(HsvDmxMain, IHsvSdmControl2_FreesatPostcode);
			
		}
		else if(StAcquireSI == CURRENT_INS_STATE)
		{	
			TraceNotice(m,"Start Collection Triggered with:IHsvSdmControl2_FreesatNormal mode");
			SET_INS_STATE(StSIAcquireWait);
			ctrl->StartCollection(HsvDmxMain, IHsvSdmControl2_FreesatNormal);
			
		}
		else
		{
			TraceNotice  (m,"ERROR!!! Invalid state, should not enter %d",CURRENT_INS_STATE);
		}
	}
	else
	{
		TraceNotice (m,"%s %d Requesting stop collection",__FUNCTION__, __LINE__);
		ctrl->StopCollection(HsvDmxMain);
	}
}

void CHsvDvbsFreesat_mScan::FuncIdentifyBouquet(Nat32 param)
{
	Nat8 Postcode[MAX_POSTCODE_LEN] = {0};
	Nat8 PostcodeLen = 0;
	Nat16 NextChildIndex = 0;
	Nat16 ChildIndex = 0;
	Nat16 MaxChildIndex = 0;
	Nat16 PostcodeIndex = 0;
	Nat16 RegionKey = 0;
	Bool RegionKeyFound = FALSE;
	Bool NextChildIndexFound = TRUE;
	
	HSVSPTYPE(FreesatPostcodeKey, dvb, postcode) PostcodeKey;
	HSVSPTYPE(FreesatRegionKey, dvb, postcode) RegionKeyMap;

	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	/*Get the stored bouquet ID and region ID*/
	/*mInstStatus.BouquetId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeBouquetId);
	  mInstStatus.RegionId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeRegionId);*/
	
	isettings->GetPostcode(&PostcodeLen,Postcode);
	
	
	TraceNotice (m,"%d BouquetId %d RegionId %d Postcode %s",__LINE__, mInstStatus.BouquetId, mInstStatus.RegionId, Postcode);
	
	/*Read zeroth index to get the number of root nodes
	**Get number of child nodes
	**Search in all child nodes to match the postcode character
	**If postcode character is not matched then stop the search and use default Bouquet
	**If postcode character is found then restart search to match next postcode char with next word offset
	*/
	if(PostcodeLen != 0)
	{
		// This will take care usecase :if Postcode table not on-air
		if(0 < strapi->GetSize(HsvMain,HSVSPID(FreesatPostcodeKey, dvb, postcode)))
		{
			while((NextChildIndexFound) && (!RegionKeyFound) && (PostcodeIndex < (MAX_POSTCODE_LEN -1)) && ('\0' != Postcode[PostcodeIndex]))
			{
				TraceNotice(m,"%d NextChildIndex %d",__LINE__,NextChildIndex);
				
				if(strapi->GetByIndex(HsvMain, HSVSPID(FreesatPostcodeKey, dvb, postcode), NextChildIndex, (void*)&PostcodeKey))
				{
					TraceNotice(m,"Outer Loop NextChildIndex %d ChildCount %d PcIndex %d , NodeIndex %d\n"
						,NextChildIndex,PostcodeKey.ChildCount,PostcodeIndex,PostcodeKey.NodeIndex);
					
					NextChildIndexFound = FALSE;
					MaxChildIndex = NextChildIndex + PostcodeKey.ChildCount;
					ChildIndex = NextChildIndex + 1;

					while(ChildIndex <= MaxChildIndex)
					{
						TraceNotice(m,"%d ChildIndex %d",__LINE__,ChildIndex);
						if(strapi->GetByIndex(HsvMain, HSVSPID(FreesatPostcodeKey, dvb, postcode), ChildIndex, (void*)&PostcodeKey))
						{
							TraceNotice(m,"Inner Loop PostcodeChar %d IsLeaf %d ChildIndex %d PcIndex %d\n",PostcodeKey.PostcodeChar,PostcodeKey.IsLeafNode,ChildIndex,PostcodeIndex);
							if(Postcode[PostcodeIndex] == PostcodeKey.PostcodeChar)
							{
								/*increment the postcode index to check for next byte*/
								PostcodeIndex ++;
								if(PostcodeKey.IsLeafNode)
								{
									TraceNotice(m,"PostcodeKey.RegionKey %d",PostcodeKey.RegionKey);
									RegionKey = PostcodeKey.RegionKey;
									RegionKeyFound = TRUE;
								}
								else
								{
									TraceNotice(m,"PostcodeKey.NextWordOffset %d",PostcodeKey.NextWordOffset);
									NextChildIndex = PostcodeKey.NextWordOffset;
									NextChildIndexFound = TRUE;
								}
								break;
							}
						}
						else
						{
							TraceNotice  (m,"ERROR!!!GetByIndex for child - Failed, Index %d",ChildIndex);
							break;
						}

						ChildIndex++;
					}
				}
				else
				{
					TraceNotice  (m,"ERROR!!!GetByIndex - Failed, Index %d",NextChildIndex);
					break;
				}
			}
		}
		else
		{
			TraceNotice (m,"Line %d Size of post code key table is zero",__LINE__);
		}
		
		TraceNotice (m," %d RegionKey %d RegionKeyFound %d",__LINE__,RegionKey,RegionKeyFound);
		/*Region key found, get the bouquet ID and region ID from region key*/
		if(RegionKeyFound)
		{
			TraceNotice (m,"%d Region key %d",__LINE__,RegionKey);
			// This will take care usecase :region_code not in region keymap
			if(strapi->GetByKey(HsvMain, HSVSPID(FreesatRegionKey, dvb, postcode),RegionKey, 0, 0, (void *)&RegionKeyMap))
			{
				TraceNotice(m,"RegionKey %d BouquetId %d and RegionId %d",RegionKey,RegionKeyMap.HDBouquetId,RegionKeyMap.HDRegionId);
				mInstStatus.BouquetId = RegionKeyMap.HDBouquetId;
				mInstStatus.RegionId = RegionKeyMap.HDRegionId;
				
			}
			else
			{
				TraceNotice  (m,"ERROR!!!Bouquet not found from Region Key %d",RegionKey);
			}
		}
		else
		{
			TraceNotice  (m,"ERROR!!!Region key is not found from postcode tree table");
		}

	}
	else
	{
		TraceNotice  (m,"PostCode Len is Zero , Default RegionId and Bouquet Id Mapped");
		mInstStatus.BouquetId = DEFAULT_FREESAT_HD_BID;
		mInstStatus.RegionId  = DEFAULT_FREESAT_HD_RID;		
	}	

	/* store the current Region Id and BouquetId */
	isettings->SetAttribute(IHsvSatelliteSettings_AttributeBouquetId, mInstStatus.BouquetId);
	isettings->SetAttribute(IHsvSatelliteSettings_AttributeRegionId, mInstStatus.RegionId);

	TraceNotice (m,"After parsing postcode table %d BouquetId %d RegionId %d Postcode %s",__LINE__, mInstStatus.BouquetId, mInstStatus.RegionId, Postcode);

	/*bouquet and region ID are found, start SI aquision*/
	SET_INS_STATE(StAcquireSI);
	pmp_PmpSend(mPump, EvStartTableCollection, (Nat32)param);
}

void CHsvDvbsFreesat_mScan::FuncDataAvailable(Nat32 value)
{
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	switch(CURRENT_INS_STATE)
	{
	case StHomingServiceDetection:
		pmp_PmpSend(mPump, EvIdentifyHomingService, (Nat32)value);
		break;
	case StPostcodekeyAcquireWait:
		SET_INS_STATE(StAcquireRegionkey);
		pmp_PmpSend(mPump, EvStartTableCollection, (Nat32)value);
		break;
	case StRegionkeyAcquireWait:
		pmp_PmpSend(mPump, EvIdentifyBouquet, (Nat32)value);
		break;
	case StSIAcquireWait:
		mCheckBATAvailability(value);
		break;
	default:
		TraceNotice  (m,"ERROR!!! Invalid state, should not enter %d",CURRENT_INS_STATE);
		break;
	}
}

void CHsvDvbsFreesat_mScan::FuncDataNotAvailable(Nat32 value)
{
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	switch(CURRENT_INS_STATE)
	{
		case StHomingServiceDetection:
			pmp_PmpSend(mPump, EvIdentifyHomingService, (Nat32)value);
			break;
		case StPostcodekeyAcquireWait:
			SET_INS_STATE(StRegionkeyAcquireWait);
			pmp_PmpSend(mPump, EvIdentifyBouquet, (Nat32)value);
			break;
		case StRegionkeyAcquireWait:
			pmp_PmpSend(mPump, EvIdentifyBouquet, (Nat32)value);
			break;
		case StSIAcquireWait:
			/*Data not acquired, send installation complete notification*/
			SET_INS_STATE(StServiceInstallComplete);
			pmp_PmpSend(mPump, EvInstallComplete, (Nat32)FALSE);
			break;
		default:
			TraceNotice  (m,"ERROR!!! Invalid state, should not enter %d",CURRENT_INS_STATE);
			break;
	}
}

void CHsvDvbsFreesat_mScan::FuncStopServiceScan (Nat32 param1)
{
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	mInstStatus.IntallationState = IHsvSatelliteInstallation_InstallationStateIdle;
	SET_INS_MODE(IHsvSatelliteInstallation_InstallationNone);
	SET_INS_STATE (StIdle);
	SET_SCAN_MODE(InvalidScanMode);
	SET_SCAN_SUB_MODE(InvalidScanSubMode);

	/* Stop the SDM */
	isigstr->StopSigStrMeasAll();
	if (IHsvSdmControl2_Idle != ctrl->GetMode(HsvDmxMain))
	{
		ctrl->StopCollection(HsvDmxMain);
	}

	iinsN->OnEvent(IHsvSatelliteInstallationNotify_EventInsStopped,0);
	UNUSED (param1);
}

void CHsvDvbsFreesat_mScan::FuncInstallComplete(Nat32 param)
{
	TraceNotice (m,"Entering function Freesat - %s Value %d",__FUNCTION__, param);

	/* In UpdateInstalltion Mode - we always store the Rid and Bid of Last successful Auto-Installation*/
	if(CURRENT_MODE == IHsvSatelliteInstallation_InstallationUpdate)
	{
		
		mInstStatus.BouquetId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeBouquetId);
		mInstStatus.RegionId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeRegionId);
		TraceNotice(m,"Update Installtion:Recaptured Last successful Auto-Installation Rid %d and Bid %d ",mInstStatus.RegionId,mInstStatus.BouquetId);
	}
	
	/*store the bouquet and region ID, also commit the changes to persistent memory*/
	isettings->SetAttribute(IHsvSatelliteSettings_AttributeBouquetId, mInstStatus.BouquetId);
	isettings->SetAttribute(IHsvSatelliteSettings_AttributeRegionId, mInstStatus.RegionId);
	isettings->SaveSatelliteSettingsToPersistent();
	isettings->CommitSatelliteSettingsToPersistent();

	mInstStatus.IntallationState = IHsvSatelliteInstallation_InstallationStateIdle;
	SET_INS_MODE(IHsvSatelliteInstallation_InstallationNone);
	SET_INS_STATE (StIdle);
	SET_SCAN_MODE(InvalidScanMode);
	SET_SCAN_SUB_MODE(InvalidScanSubMode);

	if(param)
	{
		/*Package installation completed*/
		iinsN->OnEvent(IHsvSatelliteInstallationNotify_EventPkgInstallEnd, 0);
	}
	else
	{
		/*Package installation failed*/
		iinsN->OnEvent(IHsvSatelliteInstallationNotify_EventInsFailed, 0);
	}

	if (IHsvSdmControl2_Idle != ctrl->GetMode(HsvDmxMain))
	{
		ctrl->StopCollection(HsvDmxMain);
	}
}

void CHsvDvbsFreesat_mScan::mAcquireSIPSITables(Nat32 param)
{
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	if(IHsvSdmControl2_Idle == ctrl->GetMode(HsvDmxMain))
	{
		switch(CURRENT_SCAN_MODE)
		{
		case FactoryMuxMode:
			TraceNotice(m,"Triggerd startCollection:FreesatMinimalNitAct:NIT actual + PSI");
			mInNITActualMode = TRUE;
			SET_SCAN_SUB_MODE(TableAcquireWait);
			ctrl->StartCollection(HsvDmxMain, IHsvSdmControl2_FreesatMinimalNitAct);
			break;
		case BlindScanMode:
		case LDSearchMode:
		case StoredLDSearchMode:
		case StoredILDSearchMode:
			TraceNotice(m,"Triggerd startCollection:FreesatPSIMode: Only PSI");
			SET_SCAN_SUB_MODE(TableAcquireWait);
			ctrl->StartCollection(HsvDmxMain, IHsvSdmControl2_FreesatPSIMode);
			break;
		case MaxScanMode:
		case InvalidScanMode:
		default:
			TraceNotice  (m,"Invalid scan mode, should not enter %d",CURRENT_SCAN_MODE);
			break;
		}
	}
	else
	{
		TraceNotice (m,"%d Stop collection requested",__LINE__);
		ctrl->StopCollection(HsvDmxMain);
	}
}

void CHsvDvbsFreesat_mScan::mAcquireNitOther(Nat32 param)
{
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	if(IHsvSdmControl2_Idle == ctrl->GetMode(HsvDmxMain))
	{
		mInNITActualMode = FALSE;
		/*reset the linkage info list*/
		mInstStatus.NumOfLinkageService = 0;
		memset(mInstStatus.mLinkageServiceInfo, 0, (sizeof(LinkageServiceInfo) * MAX_LINKAGE_SERVICE));
		TraceNotice(m,"Triggerd startCollection:FreesatMinimalNitOth");
		SET_SCAN_SUB_MODE(NITOtherAcquireWait);
		ctrl->StartCollection(HsvDmxMain, IHsvSdmControl2_FreesatMinimalNitOth);
		
	}
	else
	{
		TraceNotice (m,"%d Stop collection requested",__LINE__);
		ctrl->StopCollection(HsvDmxMain);
	}
}

void CHsvDvbsFreesat_mScan::mCheckDataAvailable(Nat32 param)
{
	TraceNotice (m,"Entering function Freesat - %s ",__FUNCTION__);
	FResult RetVal = IHsvErrorCodeEx_Ok;
	int LnbNumber = 0;
	int LnbType = 0;
	int LockStatus = 0;
	int LockedFreq = 0;
	int Polarization = 0;
	int SymbolRate = 0;
	int IqMode = 0;
	int Bandwidth = 0;
	HSVSPTYPE(FreesatTunnelledInfo, mpeg, simplepmt) FreesatTunneldData;
	mIdentifyHomingServiceFromPMT(param);
	mStoreLinkageServiceList(param);

	TraceNotice (m,"%d Current scan mode %d Sub scan mode %d Current Inst state %d",__LINE__, CURRENT_SCAN_MODE, CURRENT_SCAN_SUB_MODE,CURRENT_INS_STATE);
	TraceNotice (m,"%d Num Linkage service %d Homing Srv data valid %d Homing srv %d",__LINE__, mInstStatus.NumOfLinkageService,
								mInstStatus.mHomingServiceInfo.IsDataValid, IS_HOMING_SERVICE(mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap));

	if(FactoryMuxMode == CURRENT_SCAN_MODE)
	{
		if(TableAcquireWait == CURRENT_SCAN_SUB_MODE)
		{
			if(mInstStatus.NumOfLinkageService)
			{
					if(strapi->GetByKey(HsvMain, HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt),
											mInstStatus.mLinkageServiceInfo[0].ServiceId,
											0,0,(void*)&FreesatTunneldData))
					{
						if(FreesatTunneldData.TunnelledDataTypeBitMap & (1 << 0x07))
						{
							
							mInstStatus.mHomingServiceInfo.IsDataValid = TRUE;
							mInstStatus.mHomingServiceInfo.ServiceId = FreesatTunneldData.ServiceId;
							memcpy(mInstStatus.mHomingServiceInfo.PID, FreesatTunneldData.PID, (sizeof(Nat16) * FREESAT_MAX_TUNNELED_PID_PER_SERVICE));
							mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap = FreesatTunneldData.TunnelledDataTypeBitMap;
							mInstStatus.mHomingServiceInfo.Frequency = LockedFreq;
							mInstStatus.mHomingServiceInfo.Polarization = Polarization;
							TraceNotice(m,"Homing Service :%d TunelledDataTypeBitMap: %d",mInstStatus.mHomingServiceInfo.ServiceId,mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap);
							TraceNotice(m,"Tunnelled PIDs Stored:");
							for(int i = 0; i < FREESAT_MAX_TUNNELED_PID_PER_SERVICE;i++)
							{
								TraceNotice(m,"PID[%d] = %d",i,mInstStatus.mHomingServiceInfo.PID[i]);
							}
						}
						else
						{
							TraceNotice(m,"Tunnlled Nit Other PID Not Available in Service Marked by FLD of NIT Act !! This should not happen");
						}
					}
					else
					{
						TraceNotice(m,"Service Marked by FLD of NIT Act is not present in PMT loop!! This should not happen");
					}
					SET_SCAN_SUB_MODE(AcquireNITOther);
					pmp_PmpSend(mPump, EvIdentifyHomingService, (Nat32)NULL);
			}
			else if(mInstStatus.mHomingServiceInfo.IsDataValid)
			{
				/*Linkage Descriptor is not found in NIT Actual,So Get NIT other PID is from tunnelled PMT, 
				**and initiate NIT other collection to get linkage descriptor
				*/
				SET_SCAN_SUB_MODE(AcquireNITOther);
				pmp_PmpSend(mPump, EvIdentifyHomingService, (Nat32)NULL);
			}
			else
			{
				/*Linkage descriptor is not available in NIT Actual, also tunnneled NIT other PID is not available PMT
				**so restart the search with next mux
				*/
				SET_SCAN_SUB_MODE(AcquireSIPSITables);
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
		}
		else if(NITOtherAcquireWait == CURRENT_SCAN_SUB_MODE)
		{
			if(mInstStatus.NumOfLinkageService)
			{
				/*Linkage descriptor is found in tunnelled NIT, find the homing service from the list*/
				SET_SCAN_MODE(LDSearchMode);
				SET_SCAN_SUB_MODE(AcquireSIPSITables);
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
			else if((mInstStatus.mHomingServiceInfo.IsDataValid) && (IS_HOMING_SERVICE(mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap)))
			{
				/*LD not available in Tunnelled NIT other, But Valid homing service is identified during PMT search, so tune to the service to acquire tables
				**No further search is required, so scan sub mode is set to invalid
				*/
				SET_SCAN_MODE(HomingServiceMode);
				SET_SCAN_SUB_MODE(InvalidScanSubMode);
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
			else
			{
				/*Nither LD is available in Tunnelled NIT other Nor Valid Homing Service identified during PMT 
				**search so, take up Next Mux.
				*/
				SET_SCAN_SUB_MODE(AcquireSIPSITables);
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
		}
		else
		{
			TraceNotice (m,"ERROR!!! Invalid scan sub mode, should not enter %d!!! \n",CURRENT_SCAN_SUB_MODE);
		}
	}
	else if((LDSearchMode == CURRENT_SCAN_MODE)||(StoredLDSearchMode == CURRENT_SCAN_MODE) ||(StoredILDSearchMode == CURRENT_SCAN_MODE))
	{
		if((mInstStatus.mHomingServiceInfo.IsDataValid) && (IS_HOMING_SERVICE(mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap)))
		{
			/*Valid homing service is identified during PMT search, so tune to the service to acquire tables*/
			SET_SCAN_MODE(HomingServiceMode);
			SET_SCAN_SUB_MODE(InvalidScanSubMode);
			SET_INS_STATE(StStart);
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
		}
		else
		{
			/*Valid homing service is NOT identified during PMT search, restart the search with next service*/
			SET_SCAN_SUB_MODE(AcquireSIPSITables);
			SET_INS_STATE(StStart);
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
		}
	}
	else if(BlindScanMode == CURRENT_SCAN_MODE)
	{
		TraceNotice(m,"Blind Scan Mode\n");
		if(TableAcquireWait == CURRENT_SCAN_SUB_MODE)
		{
			if((mInstStatus.mHomingServiceInfo.IsDataValid))
			{
				/*Since Tunnelled NIT other Holds priority in Blind Scan we trigger Nit other collection*/
				SET_SCAN_SUB_MODE(AcquireNITOther);
				pmp_PmpSend(mPump, EvIdentifyHomingService, (Nat32)NULL);
			}
			else
			{
				/*Freesat Service is Not found continue with Blind scan*/
				SET_SCAN_SUB_MODE(AcquireSIPSITables);
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
		}
		else if(NITOtherAcquireWait == CURRENT_SCAN_SUB_MODE)
		{
			if(mInstStatus.NumOfLinkageService)
			{
				/*Linkage descriptor is found in tunnelled NIT, find the homing service from the list*/
				SET_SCAN_MODE(LDSearchMode);
				SET_SCAN_SUB_MODE(AcquireSIPSITables);
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			}
			else
			{
				/*LD not available in tunnelled NIT,Continue with Blind Scan*/
				
				/*SET_INS_STATE(StServiceInstallComplete);
				pmp_PmpSend(mPump, EvInstallComplete, (Nat32)FALSE);*/
				/*Freesat Service is Not found continue with Blind scan*/

				TraceNotice(m,"LD not available in tunnelled NIT:Continue with Blind Scan");
				SET_SCAN_SUB_MODE(AcquireSIPSITables);
				SET_INS_STATE(StStart);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
				
			}
		}
		else
		{
			TraceNotice (m,"ERROR!!! Invalid scan sub mode,in Blind Scan Mode should not enter %d %d!!! \n",CURRENT_SCAN_SUB_MODE,CURRENT_SCAN_MODE);
		}
	}
	else
	{
		TraceNotice (m,"ERROR!!! Invalid scan mode, should not enter %d!!! \n",CURRENT_SCAN_MODE);
	}

}

void CHsvDvbsFreesat_mScan::mIdentifyHomingServiceFromPMT(Nat32 param)
{
	Bool DataAvailable = FALSE;
	Nat32 MaxIndex = 0;
	Nat32 CurrentIndex = 0;
	Nat16 NitOtherPid = 0xFFFF;
	FResult RetVal = IHsvErrorCodeEx_Ok;
	int LnbNumber = 0;
	int LnbType = 0;
	int LockStatus = 0;
	int LockedFreq = 0;
	int Polarization = 0;
	int SymbolRate = 0;
	int IqMode = 0;
	int Bandwidth = 0;
	HSVSPTYPE(FreesatTunnelledInfo, mpeg, simplepmt) FreesatTunneldData;
	HsvPgdatHomServiceData HomingService;

	TraceNotice (m,"Entering function Freesat - %s CURRENT_SCAN_MODE %d",__FUNCTION__,mInstStatus.ScanMode);
	if((InvalidScanMode < CURRENT_SCAN_MODE) && (CURRENT_SCAN_MODE < MaxScanMode))
	{
		DataAvailable = ((param & IHsvSdmControlNotifyEx_SIMPLEPMT) ? TRUE : FALSE);
		TraceNotice (m,"%s %d Data Available %d Param 0x%x",__FUNCTION__,__LINE__, DataAvailable, param);
	}

	/*if PMT is not detected, then homing service is not flushed because in Blind and Factory mux scan mode, during NIT othere collection mode
	**PMT is not collected, but homing service detected during AcquireSIPSITables mode will be considered as homing service
	**incase NIT other is not available
	*/
	if(DataAvailable)
	{
		/*Find the homing service from list of available service*/
		memset(&mInstStatus.mHomingServiceInfo, 0, sizeof(HomingServiceInfo));
		mInstStatus.mHomingServiceInfo.IsDataValid = FALSE;

	
		TraceNotice (m,"TMP_DEBUG %s %d LNB Numer %d Type %d frequency %d Sym %d Pol %d",__FUNCTION__,__LINE__,LnbNumber, LnbType, LockedFreq, SymbolRate, Polarization);
		if((FactoryMuxMode == CURRENT_SCAN_MODE) ||(BlindScanMode == CURRENT_SCAN_MODE))
		{
			MaxIndex = strapi->GetSize(HsvMain, HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt));
			TraceNotice(m,"%s %d Max Tunnelled info count %d",__FUNCTION__,__LINE__,MaxIndex);
			while(CurrentIndex < MaxIndex)
			{
				if(strapi->GetByIndex(HsvMain, HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt), CurrentIndex, (void*)&FreesatTunneldData))
				{
					if(IS_HOMING_SERVICE(FreesatTunneldData.TunnelledDataTypeBitMap))
					{
						/*Valid homing service identified*/
						mInstStatus.mHomingServiceInfo.IsDataValid = TRUE;
						mInstStatus.mHomingServiceInfo.BarkerValid = TRUE;
						mInstStatus.mHomingServiceInfo.ServiceId = FreesatTunneldData.ServiceId;
						memcpy(mInstStatus.mHomingServiceInfo.PID, FreesatTunneldData.PID, (sizeof(Nat16) * FREESAT_MAX_TUNNELED_PID_PER_SERVICE));
						mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap = FreesatTunneldData.TunnelledDataTypeBitMap;
						/*Frequency and Polarization are got from:Last Tuned Factory Homing Mux
																 :As here we will be still tuned to the Factory Homing Mux
						*/
						mInstStatus.mHomingServiceInfo.Frequency = (s__FreesatPackageDetails[mInstStatus.FactoryMuxIndex - 1].Frequency*1000);
						mInstStatus.mHomingServiceInfo.Polarization = s__FreesatPackageDetails[mInstStatus.FactoryMuxIndex].Polarization;
						TraceNotice (m,"TMP_DEBUG %s %d Homing service found, SID %d",__FUNCTION__,__LINE__,mInstStatus.mHomingServiceInfo.ServiceId);
						break;
					}
					else if((FreesatTunneldData.TunnelledDataTypeBitMap & (1 << 0x07)))
					{
						/*homing service is not detected in PMT search, but NIT other PID is avaialble
						**then store NIT other PID information to initiate NIT other collection
						*/
						mInstStatus.mHomingServiceInfo.IsDataValid = TRUE;
						mInstStatus.mHomingServiceInfo.ServiceId = FreesatTunneldData.ServiceId;
						mInstStatus.mHomingServiceInfo.PID[7] = FreesatTunneldData.PID[7];
						mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap = (1 << 0x07);
						/*Frequency and Polarization details are not Stored delibrately, 
						 *as this Homing Mux info is used only to collct NIT other
						 */
						TraceNotice (m,"TMP_DEBUG %s %d Nit other PID found SID %d PID %d",__FUNCTION__,__LINE__,mInstStatus.mHomingServiceInfo.ServiceId, mInstStatus.mHomingServiceInfo.PID[7]);
					}
				}
				else
				{
					TraceNotice (m,"%d Error Strapi get by index failed, Index %d",__LINE__, CurrentIndex);
					break;
				}
				CurrentIndex ++;
			}
		}
		else
		{
			/*if the mode is LD search (live/stored) or ILD search then search only in the specified PMT*/
			if(LDSearchMode == CURRENT_SCAN_MODE)
			{
				/*Index is value is already incremented after tuning, so take the previous index*/
				CurrentIndex = (mInstStatus.LinkageServiceIndex - 1);
				if(strapi->GetByKey(HsvMain, HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt),
									mInstStatus.mLinkageServiceInfo[CurrentIndex].ServiceId,
									0,0,(void*)&FreesatTunneldData))
				{
					
					mInstStatus.mHomingServiceInfo.IsDataValid = TRUE;
					mInstStatus.mHomingServiceInfo.BarkerValid = TRUE;
					mInstStatus.mHomingServiceInfo.ServiceId = FreesatTunneldData.ServiceId;
					memcpy(mInstStatus.mHomingServiceInfo.PID, FreesatTunneldData.PID, (sizeof(Nat16) * FREESAT_MAX_TUNNELED_PID_PER_SERVICE));
					mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap = FreesatTunneldData.TunnelledDataTypeBitMap;
					/*Frequency and Polarization are stored here from SDSD, of NIT other for particular Service,tsid,onid
					  mention in FLD of Tunnelled NIT other.
					*/
					mInstStatus.mHomingServiceInfo.Frequency = mInstStatus.mLinkageServiceInfo[CurrentIndex].Frequency;
					mInstStatus.mHomingServiceInfo.Polarization = mInstStatus.mLinkageServiceInfo[CurrentIndex].Polarization;
					TraceNotice(m,"Homing Service :%d TunelledDataTypeBitMap: %d",mInstStatus.mHomingServiceInfo.ServiceId,mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap);
					TraceNotice(m,"Tunnelled PIDs Stored:");
					for(int i = 0; i < FREESAT_MAX_TUNNELED_PID_PER_SERVICE;i++)
					{
						TraceNotice(m,"PID[%d] = %d",i,mInstStatus.mHomingServiceInfo.PID[i]);
					}
				}
				else
				{
					TraceNotice (m,"%d Failure case: Service Mentioned in LD of Tunnelled NIT other is NOT Present in PMT of Mux indicated by LD of Tunnlled NIT othr %d SID %d",__LINE__,CurrentIndex,  mInstStatus.mLinkageServiceInfo[CurrentIndex].ServiceId);
				}
			}
			else if((StoredLDSearchMode == CURRENT_SCAN_MODE) || (StoredILDSearchMode == CURRENT_SCAN_MODE))
			{
				/*Index is value is already incremented after tuning, so take the previous index*/
				CurrentIndex = ( (StoredLDSearchMode == CURRENT_SCAN_MODE) ? (mInstStatus.StoredLDServiceIndex - 1) : (mInstStatus.StoredILDServiceIndex - 1));
				if(pgdb->GetByIndex(HOMING_SERVICE_TABLE, CurrentIndex, (Address)&HomingService))
				{
					if(strapi->GetByKey(HsvMain, HSVSPID(FreesatTunnelledInfo, mpeg, simplepmt),
												HomingService.ServiceId, 0,0,(void*)&FreesatTunneldData))
					{
						mInstStatus.mHomingServiceInfo.IsDataValid = TRUE;
						mInstStatus.mHomingServiceInfo.ServiceId = FreesatTunneldData.ServiceId;
						memcpy(mInstStatus.mHomingServiceInfo.PID, FreesatTunneldData.PID, (sizeof(Nat16) * FREESAT_MAX_TUNNELED_PID_PER_SERVICE));
						mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap = FreesatTunneldData.TunnelledDataTypeBitMap;
						/*Frequency and Polarization are stored here from Freesat Info Location Dptr, of BAT.*/
						mInstStatus.mHomingServiceInfo.Frequency = HomingService.Frequency;
						mInstStatus.mHomingServiceInfo.Polarization = HomingService.Polarization;
					}
					else
					{
						TraceNotice (m,"%d Error Strapi get by key failed, Index %d Scan mode %d SID %d",__LINE__, CurrentIndex, CURRENT_SCAN_MODE, HomingService.ServiceId);
					}
				}
				else
				{
					TraceNotice(m,"%d Error pgdb get by index failed Scan Mode %d Index %d",__LINE__,CURRENT_SCAN_MODE, CurrentIndex);
				}
			}
			else
			{
				TraceNotice (m,"ERROR!!! Invalid scan mode, should not enter %d!!! \n",CURRENT_SCAN_MODE);
			}
		}
		
	}
}

void CHsvDvbsFreesat_mScan::mStoreLinkageServiceList(Nat32 param)
{
	Bool DataAvailable = FALSE;
	Nat32 MaxIndex = 0;
	Nat32 CurrentIndex = 0;
	HSVSPTYPE(SatelliteDS,dvb,nit) SatSDSD;
	HSVSPTYPE(FreesatLinkageInfo, dvb, nit) FreesatLinkageData;

	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	if((InvalidScanMode < CURRENT_SCAN_MODE) && (CURRENT_SCAN_MODE < MaxScanMode))
	{
		DataAvailable = ((param & IHsvSdmControlNotifyEx_NIT) ? TRUE : FALSE);
		TraceNotice (m,"%s %d Data Available %d Param 0x%x",__FUNCTION__,__LINE__, DataAvailable, param);
	}
  
	if(DataAvailable)
	{
		/*Reset the linkage info*/
		memset(&mInstStatus.mLinkageServiceInfo, 0, (sizeof(LinkageServiceInfo) * MAX_LINKAGE_SERVICE));
		mInstStatus.NumOfLinkageService = 0;

		MaxIndex = strapi->GetSize(HsvMain, HSVSPID(FreesatLinkageInfo, dvb, nit));
		TraceNotice(m,"%s %d Max Linkage count %d",__FUNCTION__,__LINE__,MaxIndex);
		while((CurrentIndex < MaxIndex) && (mInstStatus.NumOfLinkageService < MAX_LINKAGE_SERVICE))
		{
			if(strapi->GetByIndex(HsvMain, HSVSPID(FreesatLinkageInfo, dvb, nit), CurrentIndex, (void*)&FreesatLinkageData))
			{
				if(strapi->GetByKey(HsvMain, HSVSPID(SatelliteDS, dvb, nit),FreesatLinkageData.OriginalNetworkId,
																		    FreesatLinkageData.Tsid,
																	    	FreesatLinkageData.NetworkId,
														                    &SatSDSD))
				{
					mInstStatus.mLinkageServiceInfo[mInstStatus.NumOfLinkageService].Onid = FreesatLinkageData.OriginalNetworkId;
					mInstStatus.mLinkageServiceInfo[mInstStatus.NumOfLinkageService].Tsid = FreesatLinkageData.Tsid;
					mInstStatus.mLinkageServiceInfo[mInstStatus.NumOfLinkageService].ServiceId = FreesatLinkageData.ServiceId;
					mInstStatus.mLinkageServiceInfo[mInstStatus.NumOfLinkageService].LinkageTypeBitMap = FreesatLinkageData.FreeSatelliteLinkageTypeBitMap;
					mInstStatus.mLinkageServiceInfo[mInstStatus.NumOfLinkageService].Polarization = SatSDSD.Polarization;
					mInstStatus.mLinkageServiceInfo[mInstStatus.NumOfLinkageService].Frequency = SatSDSD.Frequency;
					mInstStatus.NumOfLinkageService++;
					TraceNotice (m,"TMP_DEBUG Linkage service found ONID %d NID %d TSID %d SID %d Freq %d Pol %d",FreesatLinkageData.OriginalNetworkId,
																	FreesatLinkageData.NetworkId, FreesatLinkageData.Tsid, FreesatLinkageData.ServiceId, SatSDSD.Frequency, SatSDSD.Polarization);
				}
				else
				{
					TraceNotice (m,"%s %d SDSD  not found ONID %d NID %d TSID %d ",__FUNCTION__,__LINE__, FreesatLinkageData.OriginalNetworkId,
																	FreesatLinkageData.NetworkId, FreesatLinkageData.Tsid);
				}
			}
			else
			{
				TraceNotice (m,"ERROR!!! FreesatLinkageInfo - get by index failed - index %d",CurrentIndex);
				break;
			}
			CurrentIndex ++;
		}
	}
}

void CHsvDvbsFreesat_mScan::mCheckBATAvailability(Nat32 param)
{
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	
	/*If BAT is avaialble start the service installation*/
	if(param & IHsvSdmControlNotifyEx_BAT)
	{
		TraceNotice (m,"%s %d BAT available, start service acausition",__FUNCTION__,__LINE__);
		SET_INS_STATE(StServiceInstallWait);
		/*In Freesat for acquisition there is no mode, so value is always passed as zero*/
		idataacq->Initialise(0);
		idataacq->AcquireData(0);
	}
	else
	{
		TraceNotice (m,"%s %d BAT not available, Current BouquetId %d",__FUNCTION__,__LINE__, mInstStatus.BouquetId);

		if((FREESAT_DEFAULT_HD_BOUQUET_ID != mInstStatus.BouquetId))
		{
			if(CURRENT_MODE == IHsvSatelliteInstallation_InstallationServiceScan)
			{
				TraceNotice(m,"AutoInstallation : Assigning Default Bid and Rid");
				mInstStatus.BouquetId = DEFAULT_FREESAT_HD_BID;
				mInstStatus.RegionId = DEFAULT_FREESAT_HD_RID;
			}
			else if(CURRENT_MODE == IHsvSatelliteInstallation_InstallationUpdate)
			{
				TraceNotice(m,"Update Installation");
				if(mInstStatus.BouquetId == isettings->GetAttribute(IHsvSatelliteSettings_AttributeBouquetId))
				{
					TraceNotice(m,"Assigning Default Bid and Rid");
					mInstStatus.BouquetId = DEFAULT_FREESAT_HD_BID;
					mInstStatus.RegionId = DEFAULT_FREESAT_HD_RID;	
				}
				else
				{
					TraceNotice(m,"Assigning Previous Installtion Stored Bid and Rid");
					mInstStatus.BouquetId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeBouquetId);
					mInstStatus.RegionId = isettings->GetAttribute(IHsvSatelliteSettings_AttributeRegionId);
				}
			}

			/* store the current Region Id and BouquetId */
			isettings->SetAttribute(IHsvSatelliteSettings_AttributeBouquetId, mInstStatus.BouquetId);
			isettings->SetAttribute(IHsvSatelliteSettings_AttributeRegionId, mInstStatus.RegionId);


			/*BAT is not found in the stream, then start BAT collection using default bouquet ID (initial installation) or
			**using previous bouquet ID (update installation)
			*/
			SET_INS_STATE(StAcquireSI);
			pmp_PmpSend(mPump, EvStartTableCollection, (Nat32)NULL);
		}
		else
		{
			SET_INS_STATE(StServiceInstallComplete);
			pmp_PmpSend(mPump, EvInstallComplete, (Nat32)FALSE);
		}
	}
	
}

void CHsvDvbsFreesat_mScan::mStationFound(void)
{
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	if(HomingServiceMode == CURRENT_SCAN_MODE)
	{
		if(IHsvSatelliteInstallation_InstallationServiceScan == CURRENT_MODE)
		{
			/*Already homing service is found, so start the postcode collection*/
			SET_INS_STATE(StAcquirePostcodekey);
			pmp_PmpSend(mPump, EvStartTableCollection, (Nat32)NULL);
		}
		else if (IHsvSatelliteInstallation_InstallationUpdate == CURRENT_MODE)
		{
			/*bouquet and region ID are already found,for Update Installation*/
			SET_INS_STATE(StAcquireSI);
			pmp_PmpSend(mPump, EvStartTableCollection, (Nat32)NULL);
		}
		
	}
	else
	{
		/*identify the homing service from current mux*/
		SET_INS_STATE(StHomingServiceDetection);
		SET_SCAN_SUB_MODE(AcquireSIPSITables);
		pmp_PmpSend(mPump, EvIdentifyHomingService, (Nat32)NULL);
	}
}

void CHsvDvbsFreesat_mScan::mNoStationFound(void)
{
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	SET_INS_STATE (StStart);
	pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
}

void CHsvDvbsFreesat_mScan::mOnSdmStoppedCollection(void)
{
	TraceNotice (m,"Entering function Freesat - %s sub scan state %d",__FUNCTION__,CURRENT_SCAN_SUB_MODE);
	if(StHomingServiceDetection == CURRENT_INS_STATE)
	{	
		/*if((CURRENT_SCAN_SUB_MODE != TableAcquireWait)&&(CURRENT_SCAN_SUB_MODE != NITOtherAcquireWait))
		{*/
			pmp_PmpSend(mPump, EvIdentifyHomingService, (Nat32)NULL);
		
	}
	else if((StAcquirePostcodekey == CURRENT_INS_STATE) || (StAcquireSI == CURRENT_INS_STATE) || (StAcquireRegionkey == CURRENT_INS_STATE))
	{
		pmp_PmpSend(mPump, EvStartTableCollection, (Nat32)NULL);
	}
	else if(StStart == CURRENT_INS_STATE)
	{
		pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
	}
	else
	{
		TraceNotice (m,"ERROR!!! Invalid state, should not enter %d!!! \n",CURRENT_SCAN_MODE);
	}
}

void CHsvDvbsFreesat_mScan::mGetLnbDetails(int SatId)
{
	int LnbIndex;
	HsvPgdatDigSatInfoData SatDetails;
	TraceNotice (m,"@Entering - %s ",__FUNCTION__);
	for(LnbIndex=0; LnbIndex < MAX_NUM_LNBS_SUPPORTED; LnbIndex++)
	{
		pgdb->Initialise(SAT_INFO_TABLE, (Address) &SatDetails);
		SatDetails.LnbNumber = LnbIndex;
		TraceNotice (m,"@SatDetails.LnbNumber: %d",SatDetails.LnbNumber);
		if (TRUE == pgdb->GetByKey (SAT_INFO_TABLE, (Address) &SatDetails))
		{
			TraceNotice (m,"@GetByKey Passed:SatDetails.SatelliteId %d",SatDetails.SatelliteId);
			if(SatDetails.SatelliteId == SatId)
			{
				mInstStatus.LnbNumber = LnbIndex;
				mInstStatus.LnbType = SatDetails.LnbType;
				break;
			}
		}
		else
		{
			TraceNotice (m," ERROR: Getting Sat. details failed for LNB: %d!!! \n",LnbIndex);
		}
	}
	TraceNotice (m,"@Exit - %s mInstStatus.LnbNumber %d mInstStatus.LnbType %d",__FUNCTION__,mInstStatus.LnbNumber,mInstStatus.LnbType);
}

void CHsvDvbsFreesat_mScan::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
{
	FResult	RetVal = IHsvErrorCodeEx_Ok;
	int LnbNumber = 0;
	int LnbType = 0;
	int LockStatus = 0;
	int LockedFreq = 0;
	int Polarization = 0;
	int SymbolRate =0;
	int IqMode =0;
	int Bandwidth = 0;

	RetVal = satfeapi->GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);

	if (RetVal == IHsvErrorCodeEx_Ok)
	{
		ptc->Frequency = LockedFreq;
		ptc->SymbolRate = SymbolRate;
		ptc->ModulationType = 0;
		ptc->CodeRateHigh = 0;
		ptc->CodeRateLow = 0;
		ptc->IqMode = IqMode;
		ptc->ChannelBandwidth = Bandwidth;
		ptc->Polarization = Polarization;
	}
}

void CHsvDvbsFreesat_mScan::mSwitchScanMode(void)
{
	int StartIndex = 0;
	int EndIndex = 0;
	HsvFreesatHomingServiceData *HomingService;
	Nat32 Data = 0;

	
	TraceNotice (m,"Entering function Freesat - %s",__FUNCTION__);
	switch(CURRENT_SCAN_MODE)
	{
		case FactoryMuxMode:
			TraceNotice (m,"Factory mux mode completed switching to Stored LD search mode");
		
			SET_SCAN_MODE(StoredLDSearchMode);
			SET_SCAN_SUB_MODE(AcquireSIPSITables);
			SET_INS_STATE(StStart);

			Data = isettings->GetAttribute(IHsvSatelliteSettings_AttributeFreesatHomingServiceData);
			HomingService = (HsvFreesatHomingServiceData*)Data;

			TraceNotice(m," %s linkage count [%d] & info count [%d]",__FUNCTION__,HomingService->LinkageServiceCount,\
																		          HomingService->InfoLocationServiceCount);

			for(int i = 0;i < (HomingService->LinkageServiceCount + HomingService->InfoLocationServiceCount);i++)
			{
				TraceNotice(m,"stored [%d] [%d] [%d] [%d]",HomingService->HomingServices[i].HomingServiceType,
														   HomingService->HomingServices[i].ServiceId,\
													       HomingService->HomingServices[i].Frequency,\
													       HomingService->HomingServices[i].TsId);
			}
					
			mInstStatus.StoredLDServiceIndex = 0;
			mInstStatus.MaxStoredLDServiceIndex = HomingService->LinkageServiceCount;
							
			free(HomingService);
			
			TraceNotice (m,"LD Service start Index %d End Index %d",mInstStatus.StoredLDServiceIndex, mInstStatus.MaxStoredLDServiceIndex);
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			break;
		case StoredLDSearchMode:
			TraceNotice (m,"Stored LD mode completed switching to Stored ILD search mode");

			SET_SCAN_MODE(StoredILDSearchMode);
			SET_SCAN_SUB_MODE(AcquireSIPSITables);
			SET_INS_STATE(StStart);

			Data = isettings->GetAttribute(IHsvSatelliteSettings_AttributeFreesatHomingServiceData);
			HomingService = (HsvFreesatHomingServiceData*)Data;
			
			mInstStatus.StoredILDServiceIndex = HomingService->LinkageServiceCount;
			mInstStatus.MaxStoredILDServiceIndex = (HomingService->InfoLocationServiceCount + HomingService->LinkageServiceCount);
			
			free(HomingService);
			
			TraceNotice (m,"ILD Service start Index %d End Index %d",mInstStatus.StoredILDServiceIndex, mInstStatus.MaxStoredILDServiceIndex);
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			break;

		case StoredILDSearchMode:
			
			TraceNotice (m,"Stored ILD mode completed switching to Blind search mode");
			mInstStatus.BlindScanInProgress = FALSE;
			SET_SCAN_MODE(BlindScanMode);
			SET_SCAN_SUB_MODE(AcquireSIPSITables);
			SET_INS_STATE(StStart);
			pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			break;
			
		case LDSearchMode:
			 TraceNotice(m,"mInNITActualMode is %d",mInNITActualMode);
			 if(mInNITActualMode)
			 {
			 	mInNITActualMode = FALSE;
				mInstStatus.LinkageServiceIndex = 0;
				TraceNotice (m,"No Proper LD found in NITActual switching to Stored LD search mode");

				SET_SCAN_MODE(StoredLDSearchMode);
				SET_SCAN_SUB_MODE(AcquireSIPSITables);
				SET_INS_STATE(StStart);
				
				Data = isettings->GetAttribute(IHsvSatelliteSettings_AttributeFreesatHomingServiceData);
				HomingService = (HsvFreesatHomingServiceData*)Data;
				
				mInstStatus.StoredLDServiceIndex = 0;
				mInstStatus.MaxStoredLDServiceIndex = HomingService->LinkageServiceCount;
				TraceNotice (m,"LD Service start Index %d End Index %d",mInstStatus.StoredLDServiceIndex, mInstStatus.MaxStoredLDServiceIndex);

				free(HomingService);
				pmp_PmpSend(mPump, EvStartTuning, (Nat32)NULL);
			 }
			 else
			 {
			 	TraceNotice (m,"No proper LD found in NIT other Aborting Installation: LD search Mode");
				SET_INS_STATE(StServiceInstallComplete);
				pmp_PmpSend(mPump, EvInstallComplete, (Nat32)FALSE);
			 }
			 break;
		case BlindScanMode:
		case HomingServiceMode:
			TraceNotice (m,"Tune request failed, Installation failed, Current scan mode %d", CURRENT_SCAN_MODE);
			SET_INS_STATE(StServiceInstallComplete);
			pmp_PmpSend(mPump, EvInstallComplete, (Nat32)FALSE);
			break;
		case InvalidScanMode:
		case MaxScanMode:
		default:
			TraceNotice  (m,"ERROR!!! Invalid scan mode, should not enter %d",CURRENT_SCAN_MODE);
			break;
	}
}

void CHsvDvbsFreesat_mScan::Init(void)
{
	
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	/* Creating the pump */
	mPump = pmp_PmpCreateEx( pen->PumpEngine(), PumpHandler, FALSE,"hsvdvbfreesat_mscan");
	s__mConstModuleLifeCycle = ConstInitialized;

	/* Initialize acquisition module also */
	iacqpow->Init();
	isortpow->Init ();
	isettingspow->Init();
}

void CHsvDvbsFreesat_mScan::TurnOn(void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	/* Initializing the other modules.*/
	s__mConstModuleLifeCycle = ConstTurnedOn;
	
	iacqpow->TurnOn ();
	isortpow->TurnOn ();
	isettingspow->TurnOn();
}
void CHsvDvbsFreesat_mScan::TurnOff(void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	s__mConstModuleLifeCycle = ConstTurnedOff;
	iacqpow->TurnOff ();
	isortpow->TurnOff ();
	isettingspow->TurnOff();
}

FResult CHsvDvbsFreesat_mScan::StartInstallation(int Source,int Lnb,int Mode)
{
	FResult	RetVal = IHsvErrorCodeEx_BadParameter;
	
	TraceNotice (m," Entering function Freesat - %s Source %d Lnb %d Mode %d",__FUNCTION__, Source, Lnb, Mode);
	if (TURNED_ON)
	{
		TraceNotice(m,"Turned On");
		if (VALID_SOURCE(Source) && IS_VALID_LNBNUMBER(Lnb) && VALID_MODE(Mode))
		{
			TraceNotice(m,"Valid Source / Valid LNB number / Valid Mode ");
			TraceNotice(m,"mInstStatus.State = %d",mInstStatus.State);
			if (SCAN_NOT_INPROGESS)
			{
				TraceNotice(m,"mInstStatus.State = Idle");
				SET_INS_MODE(Mode);
				mInstStatus.IntallationState = IHsvSatelliteInstallation_InstallationStateInProgress;
				pmp_PmpSend(mPump, EvStart, (Nat32)NULL);
			}
			RetVal = IHsvErrorCodeEx_Ok;
		}
	}
	return RetVal;
}

FResult CHsvDvbsFreesat_mScan::StopInstallation(void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	FResult	RetVal = IHsvErrorCodeEx_Ok;
	pmp_PmpSend(mPump, EvStop, (Nat32)NULL);
	return RetVal;
}

int CHsvDvbsFreesat_mScan::GetCurrentInstallationState(int * mode, int * state)
{
	/* Function to get the installation mode and status */
	int RetVal = IHsvErrorCodeEx_Ok;
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	if (mode && state)
	{
		*mode = CURRENT_MODE;
		*state = mInstStatus.IntallationState;
	}
	return RetVal;
}

int CHsvDvbsFreesat_mScan::GetNumberOfTvChannelsFound(int Mode,int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq->GetNumberOfTvChannelsFound();
	return RetVal;
}
int CHsvDvbsFreesat_mScan::GetNumberofRadioChannelsFound(int Mode,int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq->GetNumberOfRadioChannelsFound();
	return RetVal;
}

int CHsvDvbsFreesat_mScan::GetNumberOfTvChannelsRemoved(int Mode,int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq->GetNumberOfTvChannelsRemoved();
	return RetVal;
}

int CHsvDvbsFreesat_mScan::GetNumberofRadioChannelsRemoved(int Mode,int Lnb)
{
	int	RetVal = 0;

	RetVal = idataacq->GetNumberofRadioChannelsRemoved();
	return RetVal;
}

void CHsvDvbsFreesat_mScan::GetSIDetails(HsvSDMSIDataValues * SiValues)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	SiValues->Pid = 0xFFFF;
	SiValues->FreesatPostCodeTableType = 0xFFFF;
	switch(SiValues->TableId)
	{
	case 0x41: /*NIT Other*/
		SiValues->Pid = ((mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap & (1 << 0x07)) ? mInstStatus.mHomingServiceInfo.PID[0x07] : 0xFFFF);
		break;
	case 0x46: /*SDT Other*/
		SiValues->Pid = ((mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap & (1 << 0x03)) ? mInstStatus.mHomingServiceInfo.PID[0x03] : 0xFFFF);
		break;
	case 0x4A: /*BAT*/
		SiValues->Pid = ((mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap & (1 << 0x04)) ? mInstStatus.mHomingServiceInfo.PID[0x04] : 0xFFFF);
		SiValues->BouquetId = mInstStatus.BouquetId;
		break;
	case 0xD2: /*Postcode table*/
		SiValues->Pid = ((mInstStatus.mHomingServiceInfo.TunnelledDataTypeBitMap & (1 << 0x0B)) ? mInstStatus.mHomingServiceInfo.PID[0x0B] : 0xFFFF);
		TraceNotice(m,"CurrentInsState: %d",mInstStatus.State);
		if(CURRENT_INS_STATE == StPostcodekeyAcquireWait)
		{
			SiValues->FreesatPostCodeTableType = POSTCODE_TREE_TABLE;
		}
		else if(CURRENT_INS_STATE == StRegionkeyAcquireWait)
		{
			SiValues->FreesatPostCodeTableType = REGION_KEY_MAP_TABLE;
		}
		break;
	case 0x40: /*NIT Actual*/
	case 0x42: /*SDT Actual*/
	default:
		break;
	}
	TraceNotice(m,"%s %d Tableid 0x%x PID 0x%x",__FUNCTION__,__LINE__,SiValues->TableId, SiValues->Pid);
}

void CHsvDvbsFreesat_mScan::GetPtcInfo(HsvInstallationPTC * ptc)
{
	/*Required for fallback installation mode (sdsd based), in Freesat no fallback installation*/
#if 0
	int	TransponderFreq = 0;
	HsvNITSatelliteDS CurrSDSD;

	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	ptc->LnbNumber = mInstStatus.LnbNumber;
	ptc->LnbType = mInstStatus.LnbType;

	mGetCurrentTunerParams (ptc);

	TransponderFreq = ptc->Frequency;
	ROUNDOFF_TPFREQ(ptc->Frequency, TransponderFreq);

	ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);

	TraceNotice  (m, " Freq %d and BW : %d \n", TransponderFreq, ptc->ChannelBandwidth);
	ptc->QSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsQsm);
	ptc->SSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsSsm);

	/* Get the SDSD from Acq*/
	idataacq->GetSdsdByIndex(mInstStatus.CurrSdsdIndex,&CurrSDSD );

	ptc->SDSDFrequency = CurrSDSD.Frequency;
	ptc->PlpId = 0;
	ptc->HierarchyMode = HsvHierarchyNone;
	ptc->StreamPriority = HsvStreamPriorityHigh;
#endif
}

void CHsvDvbsFreesat_mScan::SyncComplete(void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	pgdb->CommitTable(pgdb->GetCurrentTable());
}

void CHsvDvbsFreesat_mScan:: OnEvent(HsvDemux dmx,int eventid,int value)
{
	TraceNotice (m," Entering function Freesat - %s Dmx %d Event 0x%x Value 0x%x",__FUNCTION__, dmx,eventid,value);
	if (VALID_DEMUX(dmx))
	{
		switch(eventid)
		{
		case IHsvSdmControlNotifyEx_DataNotAvailable:
			pmp_PmpSend(mPump, EvDataNotAvailable, (Nat32)NULL);
			break;
		case IHsvSdmControlNotifyEx_DataAvailable:
			pmp_PmpSend(mPump, EvDataAvailable, value);
			break;
		case IHsvSdmControlNotifyEx_StoppedCollection:
			mOnSdmStoppedCollection();
			break;
		case IHsvSdmControlNotifyEx_OnlyPsiDataAvailable:
		case IHsvSdmControlNotifyEx_SiDataAvailable:
		case IHsvSdmControlNotifyEx_StartedCollection:
		default:
			TraceNotice (m, "Event received from SDM, Event %d",eventid);
			break;
		}
	}
}
void CHsvDvbsFreesat_mScan::OnLockChanged(Bool LockState)
{
	TraceNotice (m," Entering function Freesat - %s Lockstate %d",__FUNCTION__, LockState);
	/* Notifiation Handler for DVB-S platform FE */
	pmp_PmpSend(mPump, EvCheckLock, (Nat32)LockState);
}

void CHsvDvbsFreesat_mScan::OnBlindScanEnd(void)
{
	TraceNotice (m," Entering function Freesat - %s",__FUNCTION__);
	/*Blind scan is over, send the install complete notification*/
	SET_INS_STATE(StServiceInstallComplete);
	pmp_PmpSend(mPump, EvInstallComplete, (Nat32)FALSE);
}

void CHsvDvbsFreesat_mScan::OnDataAquired(Bool Status)
{
	TraceNotice (m," Entering function Freesat - %s status %d",__FUNCTION__, Status);
	/*service scan completed, send compte notification*/
	SET_INS_STATE(StServiceInstallComplete);
	pmp_PmpSend(mPump, EvInstallComplete, (Nat32)TRUE);
}

void CHsvDvbsFreesat_mScan::GetPtcInfoForSdSd(HsvInstallationPTC * ptc)
{
	TraceNotice(m,"DummyCall:GetInstallationVersion");
}

int CHsvDvbsFreesat_mScan::GetInstallationVersion(void)
{
	TraceNotice(m,"DummyCall:GetInstallationVersion");
	return 0;
}

FResult CHsvDvbsFreesat_mScan::WriteBarkerMuxData(void)
{
	idataacq->StoreBarkerMuxDetails();
	return 0;
}


int CHsvDvbsFreesat_mScan::GetNumberOfDigitalChannelsAdded(void)
{
	TraceNotice(m,"DummyCall:GetNumberOfDigitalChannelsAdded");
	return 0;
}

int CHsvDvbsFreesat_mScan::GetNumberOfDigitalChannelsRemoved(void)
{
	TraceNotice(m,"DummyCall:GetNumberOfDigitalChannelsRemoved");
	return 0;
}

int CHsvDvbsFreesat_mScan::GetNumberOfDigitalChannelsMoved(void)
{
	TraceNotice(m,"DummyCall:GetNumberOfDigitalChannelsMoved");
	return 0;
}

FResult CHsvDvbsFreesat_mScan::LoadManualInstallationDefaultValues(void)
{
	TraceNotice(m,"DummyCall:LoadManualInstallationDefaultValues");
	return 0;
}
FResult CHsvDvbsFreesat_mScan::StoreManualInstallationValues(void)
{
	TraceNotice(m,"DummyCall:StoreManualInstallationValues");
	return 0;
}
Bool CHsvDvbsFreesat_mScan::SetManualInstallationAttributes(int AttributeId, int Value)
{
	TraceNotice(m,"DummyCall:StoreManualInstallationValues");
	return 0;
}
int CHsvDvbsFreesat_mScan::GetAttribute(int Mode,int AttributeId)
{
	TraceNotice(m,"DummyCall:GetAttribute");
	return 0;
}

FResult CHsvDvbsFreesat_mScan::SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	TraceNotice(m,"Error!!! SetPostcode- call should not land here");
	return 0;
}
FResult CHsvDvbsFreesat_mScan::StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return IHsvErrorCodeEx_Ok;
}

FResult CHsvDvbsFreesat_mScan::SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return IHsvErrorCodeEx_Ok;
}

FResult CHsvDvbsFreesat_mScan::GetTricolorRegionNames(Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return IHsvErrorCodeEx_Ok;
}
int CHsvDvbsFreesat_mScan::GetScanProgressStatus(int Mode)
{
	TraceNotice(m,"DummyCall:GetScanProgressStatus");
	return 0;
}


Bool CHsvDvbsFreesat_mScan::GetHomingData(void* data)
{
	Bool retVal = FALSE;
	int TransponderFreq = 0;

	TransponderFreq = mInstStatus.mHomingServiceInfo.Frequency;
	ROUNDOFF_TPFREQ(mInstStatus.mHomingServiceInfo.Frequency, TransponderFreq);
	HomingMuxData *HomingData = (HomingMuxData*)data;

	TraceNotice(m,"[%d] [%d] [%d]",mInstStatus.mHomingServiceInfo.BarkerValid,\
								   mInstStatus.mHomingServiceInfo.Frequency,\
		 						   mInstStatus.mHomingServiceInfo.Polarization);

	
	if(mInstStatus.mHomingServiceInfo.BarkerValid)
	{
		HomingData->Frequency = mInstStatus.mHomingServiceInfo.Frequency;
		HomingData->Polarization = mInstStatus.mHomingServiceInfo.Polarization;
		HomingData->SatelliteId = mInstStatus.LnbNumber;

		retVal = TRUE;
	}
	return retVal;
}

int CHsvDvbsFreesat_mScan::GetSDSDData(void *data)
{
	return 0;
}
CHsvDvbsFreesat_mScan::~CHsvDvbsFreesat_mScan()
{
}


