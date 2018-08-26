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
 *
 *	C Source:		hsvdvbsgeneric_mSort.c
 *	Instance:		
 *	Description:	
 *	%created_by:	 integration %
 *	%date_created:	Tue Mar  5 00:49:00 2013 %
 *
**********************************************************************/


#include "_hsvdvbsgeneric_mSort.h"
#include <android/asset_manager.h>


TRACESYMBOL(m, "s2/installation/hsvdvbsgeneric_msort")

/****************************************************************************
 * Macros and types
 ****************************************************************************/







/* Entry in ranking list*/


/*Header in ranking list */







/****************************************************************************
 * Static variables
 ****************************************************************************/


Pump CHsvDvbsGeneric_mSort_Priv::s__Sortingpmp = -1;

int CHsvDvbsGeneric_mSort_Priv::s__SortingCount;

int CHsvDvbsGeneric_mSort_Priv::s__EndOfDummyPreset = INVALID_INDEX;

RANKING_LIST_DATA CHsvDvbsGeneric_mSort_Priv::s__CurrentRankingList;
 /*Holds the Ranking list details that are loaded from file*/



#if RANKING_LIST_STATIC


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__GermanHDPlusList[500] =
{
	#include "predefinedlist/GermanyHDplusRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__GermanFTAList[500] =
{
	#include "predefinedlist/GermanFTARankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__AustriaList[500] =
{
	#include "predefinedlist/AustriaRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__SwissFrenchList[500] =
{
	#include "predefinedlist/SwissFranceRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__SwissGermanList[500] =
{
	#include "predefinedlist/SwissGermanRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__NITINeoVisionList[500] =
{
	#include "predefinedlist/SwissGermanRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__CyfraPlusList[500] =
{
	#include "predefinedlist/SwissGermanRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__CyfrowyPolsatList[500] =
{
	#include "predefinedlist/SwissGermanRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__DigiturkEutelsatList[500] =
{
	#include "predefinedlist/SwissGermanRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__DigiturkTurkSatList[500] =
{
	#include "predefinedlist/SwissGermanRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__DSmartTurkSatHotbirdList[500] =
{
	#include "predefinedlist/SwissGermanRankingList.h"
};


RANKING_LIST_NODE CHsvDvbsGeneric_mSort_Priv::s__DSmartTurkSatList[500] =
{
	#include "predefinedlist/SwissGermanRankingList.h"
};



/*Holds static ranking list details*/ 


RANKING_LIST_DETAILS CHsvDvbsGeneric_mSort_Priv::s__RankingListsDetails[NO_OF_RANKING_LISTS] = {{ GET_NO_OF_SERVICES(AustriaList), AustriaList},
											{ GET_NO_OF_SERVICES(GermanFTAList), GermanFTAList},
											{GET_NO_OF_SERVICES(GermanHDPlusList), GermanHDPlusList},	
											{ GET_NO_OF_SERVICES(CyfraPlusList), CyfraPlusList},
											{ GET_NO_OF_SERVICES(CyfrowyPolsatList), CyfrowyPolsatList},
											{ GET_NO_OF_SERVICES(NITINeoVisionList), NITINeoVisionList},
											{ GET_NO_OF_SERVICES(SwissFrenchList), SwissFrenchList},
											{ GET_NO_OF_SERVICES(SwissGermanList), SwissGermanList},
											{ GET_NO_OF_SERVICES(DigiturkEutelsatList), DigiturkEutelsatList},
											{ GET_NO_OF_SERVICES(DigiturkTurkSatList), DigiturkTurkSatList},
											{ GET_NO_OF_SERVICES(DSmartTurkSatHotbirdList), DSmartTurkSatHotbirdList},
											{ GET_NO_OF_SERVICES(DSmartTurkSatList), DSmartTurkSatList}};

#endif

/****************************************************************************
 * Static functions
 ****************************************************************************/












void CHsvDvbsGeneric_mSort_Priv::SortingHandler( int event, Nat32 Param2 )
{
	switch (event)
	{
		case SORTING_START:
		{
			HsvPgdatPresetData      presetdat;
			Nat32 PackageIndex = Param2;
			SortingCount = 0;
			EndOfDummyPreset = INVALID_INDEX;

			SortingCount = pgdb_GetNoRecords(SERVICE_TABLE) - 1;
			/* Before starting the sort Ranking List need to be loaded*/
			Bool status = LoadRankingList(PackageIndex);
			if(status)
			{
				TraceNotice (m,"GetNoRecords  getting called in %s \n", __FUNCTION__);
				if (pgdb_GetNoRecords(PRESET_TABLE) && pgdb_GetByIndex(PRESET_TABLE, (0), (Address)&presetdat))
				{
					TraceNotice (m," GetByIndex Succesful. \n");
					EndOfDummyPreset = presetdat.PresetNumber;
				}
				else if(PackageIndex != NO_SORTING_PACKAGE_ID)
				{
					TraceNotice (m," GetByIndex UnSuccesful. Going for Larget PresetInList \n");
					EndOfDummyPreset = GetLargestPresetInList();
				}	
			
				TraceNotice(m,"%s %d EndOfDummyPreset %d\n", __FUNCTION__, __LINE__, EndOfDummyPreset);
			}
			else
			{
				LoadRankingList (NO_SORTING_PACKAGE_ID);
			}
		
			if ( EndOfDummyPreset != INVALID_INDEX )
			{
				TraceNotice(m,"%s %d\n", __FUNCTION__, __LINE__);
				pmp_PmpSend(Sortingpmp, SORTING_PROCESS, (Nat32)NULL);
				iinsN_OnEvent(iinsN_EventSortingStarted, 0);
			}
		}	
		break;

		case SORTING_PROCESS:
		{
			TraceNotice(m,"%s %d EndOfDummyPreset %d\n", __FUNCTION__, __LINE__, EndOfDummyPreset);
			if (mStartAssignStaticRank())
			{
				pmp_PmpSend(Sortingpmp, SORTING_END, (Nat32)NULL);
			}
			else
			{
				pmp_PmpSend(Sortingpmp, SORTING_PROCESS, (Nat32)NULL);
			}
		}
			break;

		case SORTING_END:
		{
			TraceNotice (m," Func %s and line %d \n", __FUNCTION__, __LINE__);
			SortingCount = 0;
			EndOfDummyPreset = INVALID_INDEX;
			CurrentRankingList.PackageIndex = INVALID_PACKAGE_ID;
			CurrentRankingList.NoofServices = 0;
			if(CurrentRankingList.StartNode)
			{
				free(CurrentRankingList.StartNode); 
				CurrentRankingList.StartNode = NULL;
			}

			iinsN_OnEvent(iinsN_EventSortCompleted, 0);
		}
			break;
			
		default:
			break;			
	}	
	UNUSED(Param2);
}

/************************************************************************
  * @brief :  Assign the ranks to all services
  * @param[in]: None
  * @param[out]: None
  * @returns:  TRUE if the rank is assigned for all services else FALSE
  * 
  *************************************************************************/
Bool CHsvDvbsGeneric_mSort_Priv::mStartAssignStaticRank(void)
{
	int	Noofservice = 0;	
	Bool	retVal = TRUE;

	TraceNotice(m,"%s : SortingCount: %d",__FUNCTION__,SortingCount);

	if ( (Noofservice = pgdb_GetNoRecords(SERVICE_TABLE)) )
	{
		TraceNotice(m,"%s : Noofservice: %d",__FUNCTION__,Noofservice);
		HsvPgdatDigServiceData tempsvcdat;
	
		
		for ( ;SortingCount >= 0; --SortingCount)
		{			
			if( (pgdb_GetByIndex(SERVICE_TABLE, SortingCount, (Address)&tempsvcdat) == TRUE) )
			{
				TraceNotice(m,"CurrentRankingList.PackageIndex : %d no srt pkg id: %d",CurrentRankingList.PackageIndex,NO_SORTING_PACKAGE_ID);
				TraceNotice(m,"tempsvcdat.PresetNumber: %d, INVALID_PRESETL %d",tempsvcdat.PresetNumber , INVALID_PRESET);
				TraceNotice(m,"tempsvcdat.EndOfDummyPreset: %d, INVALID_INDEX %d",EndOfDummyPreset , INVALID_INDEX);
				/* for No sorting start with dummy preset*/
				if ( CurrentRankingList.PackageIndex != NO_SORTING_PACKAGE_ID &&
					tempsvcdat.PresetNumber == INVALID_PRESET &&
					 CheckGivenServiceMatchedSortingList(&tempsvcdat))
				{
					AddPresetwithDigitalServiceData(&tempsvcdat);				
				}
				else if ( EndOfDummyPreset != INVALID_INDEX &&
					      tempsvcdat.PresetNumber == INVALID_PRESET )
				{
					++EndOfDummyPreset;
					tempsvcdat.PresetNumber = EndOfDummyPreset; 
					AddPresetwithDigitalServiceData(&tempsvcdat);
				}
			}

			if (SortingCount && (!((SortingCount-1) % 500)))
			{
				retVal = FALSE;
				--SortingCount;
				break;
			}
		}
	}
	return 	retVal;
}

/************************************************************************
  * @brief :  Checks if the service matched to any entry in ranking list
  * @param[in]: svcdat
  * 	svcdat: Digital service data to be checked
  * @param[out]: None
  * @returns:  TRUE if the service is matched with sorting list else FLASE
  * 
  *************************************************************************/

Bool CHsvDvbsGeneric_mSort_Priv::CheckGivenServiceMatchedSortingList ( HsvPgdatDigServiceData *svcdat )
{
	RANKING_LIST_NODE   *TempRankList = NULL;
	Nat32  NoofServiceInList = 0,
		   SortingLoop = 0;
	Bool retVal = FALSE;

	TempRankList = CurrentRankingList.StartNode;
	NoofServiceInList = CurrentRankingList.NoofServices;
	
	if ( TempRankList && NoofServiceInList && svcdat)
	{
		for ( SortingLoop = 0;SortingLoop < NoofServiceInList; ++SortingLoop)
		{
			HsvPgdatPresetData      presetdat;

			presetdat.PresetNumber = TempRankList ->Rank;
			
			if (CheckServiceMatchedWithRanking(svcdat,TempRankList) &&
				(TRUE != pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
				 )
			{
				svcdat->PresetNumber = TempRankList ->Rank;
				retVal = TRUE;		
				break;
			}
			++TempRankList;
		}
	}	
	return retVal;
}

/************************************************************************
  * @brief :  Adds Preset table and Updates service table with preset
  * @param[in]: svcdat
  * 	svcdat: Digital service data to be checked
  * @param[out]: None
  * @returns:  None
  * 
  *************************************************************************/

void CHsvDvbsGeneric_mSort_Priv::AddPresetwithDigitalServiceData ( HsvPgdatDigServiceData *svcdat )
{
	TraceNotice(m,"%s : ",__FUNCTION__);
	
	HsvPgdatPresetData      presetdat;

	pgdb_Initialise (pgdbconst_Preset, (Address)&presetdat);
	
	presetdat.PresetNumber = svcdat->PresetNumber;

	presetdat.OriginalNetworkId = svcdat->OriginalNetworkId;
    presetdat.ServiceId = svcdat->ServiceId;
    presetdat.Tsid = svcdat->Tsid;
    presetdat.Tpid = svcdat->Tpid;
    presetdat.Frequency = svcdat->Frequency;
	presetdat.Polarization = svcdat->Polarization;
	presetdat.LnbNumber = svcdat->LnbNumber;
	presetdat.VisibleService =  svcdat->VisibleService;
	//presetdat.SystemHidden = !svcdat->VisibleService[0];
	presetdat.NumericSelect = svcdat->NumericSelect;

	if(TRUE != pgdb_GetByKey (PRESET_TABLE,(Address)&presetdat))
	{
		pgdb_Add(PRESET_TABLE, (Address)&presetdat);

		pgdb_Update(SERVICE_TABLE,(Address)svcdat);
	}
	else
	{
		TraceNotice(m,"%s : pgdb_GetByKey success",__FUNCTION__);
	}
	
}

/************************************************************************
  * @brief :  Checks if the given service matches with the given ranking list entry
  * @param[in]: ptempsvcdat, TempRankList
  * 	ptempsvcdat: Digital service data to be checked
  *	TempRankList: Entry in ranking list
  * @param[out]: None
  * @returns: TRUE if the service is matches with given ranking list entry else FLASE
  * 
  *************************************************************************/
Bool CHsvDvbsGeneric_mSort_Priv::CheckServiceMatchedWithRanking( HsvPgdatDigServiceData *ptempsvcdat,RANKING_LIST_NODE   *TempRankList )
{
	Bool retVal = FALSE;
	HsvPgdatDigSatInfoData		SatInfo;
	int val = 0;

	SatInfo.LnbNumber = ptempsvcdat->LnbNumber;
	if (pgdb_GetByKey(SAT_INFO_TABLE, (Address)&SatInfo))
	{
		if ( (ptempsvcdat->ServiceId == TempRankList->ServiceId) && (ptempsvcdat->OriginalNetworkId == TempRankList->OriginalNetworkId) &&
			 (ptempsvcdat->Tsid == TempRankList->Tsid) && (SatInfo.OrbitalPosition == TempRankList->OrbitalPostion))
		{
			TraceNotice(m, "RANK: %d ONID: %d, TSID: %d, SVCID: %d",TempRankList-> Rank ,ptempsvcdat->OriginalNetworkId,ptempsvcdat->Tsid,ptempsvcdat->ServiceId);

			if(CHECK_IF_TURKEY_PREDEFINEDLIST(CurrentRankingList.PackageIndex))
			{
				val = ptempsvcdat->Frequency - (TempRankList->Frequency*1000);
				if((abs(val) <= FREQUENCY_TOLERANCE) && (ptempsvcdat->Polarization == MAP_PREDEFINEDLIST_POLARIZATION(TempRankList->Polarisation)))
				{
					retVal = TRUE;	
				}
				else
				{
					TraceNotice(m, "SVCFreq :%d, Freq: %d , SVCPol:%d, Pol:%d",(int)ptempsvcdat->Frequency,(int)(TempRankList->Frequency*1000),ptempsvcdat->Polarization,MAP_PREDEFINEDLIST_POLARIZATION(TempRankList->Polarisation));
				}
			}
			else
			{
				retVal = TRUE;			
			}
		}
	}
	return retVal;
}

/************************************************************************
  * @brief :  Load the Ranking list
  * @param[in]: BouquetIndex
  *	BouquetIndex: Bouque index of the ranking list
  * @param[out]: None
  * @returns:  TRUE if Ranking list is loaded else FALSE
  * Comments: Loads the ranking list from corresponding file
  * 
  *************************************************************************/

Bool CHsvDvbsGeneric_mSort_Priv::LoadRankingList (Nat32 PackageIndex )
{
	Bool retVal = FALSE;
	HsvPgdatPresetData      presetdat;
	
	/*for No sorting there there is no Ranking list to be loaded, start preset from predefine value*/
	if(PackageIndex == NO_SORTING_PACKAGE_ID)
	{
		/*TODO: for No sorting case preset value need to be confirmed*/
		EndOfDummyPreset = 0;
		if (pgdb_GetNoRecords(PRESET_TABLE) && pgdb_GetByIndex(PRESET_TABLE, (0), (Address)&presetdat))
		{
			EndOfDummyPreset = presetdat.PresetNumber;
		}
		CurrentRankingList.PackageIndex = PackageIndex;
		CurrentRankingList.NoofServices = 0;
		CurrentRankingList.StartNode = NULL;
		retVal = TRUE;
		return retVal;
	}
	else
	{
		/*for static list assign the pointer of corresponding array, for dynamic read the ranking list from file */
#if RANKING_LIST_STATIC
		if(PackageIndex <= NO_OF_RANKING_LISTS)
		{
			CurrentRankingList.PackageIndex = PackageIndex;
			CurrentRankingList.NoofServices = RankingListsDetails[PackageIndex-1].NoofServices;
			CurrentRankingList.StartNode = RankingListsDetails[PackageIndex-1].Data;
			retVal = TRUE;
		}
#else
		AAssetManager* mgr = (AAssetManager*)idvbset_GetAttribute (idvbset_AttributeAssetManager);
		AAsset* asset = NULL;
		RANKING_LIST_NODE *Node = NULL;
		RANKING_LIST_HEADER ListHeader;
		HsvPackageStructure Package;
		struct stat     statbuf;
		int AssetRetVal = 0;
		char FullName[BIN_FILE_NAME_LENGTH];
	
		memset(&Package,0,sizeof(HsvPackageStructure));
		/*Get Bouqeuet details */
		Package.PackageId = PackageIndex;
		ipackage_GetPackageByKey(&Package);

		TraceNotice (m, "Sort: Predefinedfilename to be opened %s AssetMgr %p ", (char*)Package.PredefinedListBinFile, mgr);
		asset = AAssetManager_open(mgr, (char*)Package.PredefinedListBinFile, AASSET_MODE_UNKNOWN);
		if(!asset) 
		{
			TraceErr (m, "NATIVE OPEN  FAILED \n ");
		} 
		else 
		{
			TraceErr (m, "NATIVE OPEN  SUCCESS \n ");
			long size = AAsset_getLength(asset);
			if (size)
			{
				AssetRetVal = AAsset_read (asset,(char *)&ListHeader,sizeof(RANKING_LIST_HEADER));
				if (AssetRetVal)
				{
					TraceNotice (m, "Sort: Predefined Num entries %d ",ListHeader.NoOfNodes);
					Node = (RANKING_LIST_NODE *) malloc((ListHeader.NoOfNodes)*(sizeof(RANKING_LIST_NODE)));
					if(!Node)
					{
						TraceErr (m,"Failed to allocate Memory\n");
					}
					else
					{
						AssetRetVal = AAsset_read (asset,(char *)Node,((ListHeader.NoOfNodes)*(sizeof( RANKING_LIST_NODE))));
						if (AssetRetVal)
						{
							CurrentRankingList.PackageIndex = PackageIndex;
							CurrentRankingList.NoofServices = ListHeader.NoOfNodes;
							CurrentRankingList.StartNode = Node;
							retVal = TRUE;
						}
						else
						{
							TraceNotice (m, "AssetRead failed for binary data ");
						}
					}
				}
				else
				{
					TraceNotice (m, "AssetRead failed for header ");
				}
			}
			else
			{
				TraceNotice (m," Predefined Binary Size ZERO in ASSETS!!!");
			}
			AAsset_close(asset);
		}	
#endif
	}
	return retVal;
}

/************************************************************************
  * @brief :  Read the data from file
  * @param[in]: Start, Bytes, file
  *	Start: Starting location in the file 
  *	Bytes: No. of bytes to read
  *	file: File name
  * @param[out]: Buff
  * 	Buff: Data red from file
  * @returns:  SUCCESS if file is read suceesfully else FAILURE
  * 
  *************************************************************************/
RESULT CHsvDvbsGeneric_mSort_Priv::FileRead(int Start, int Bytes, void *Buff, char *file)
{
	RESULT retVal = FAILURE;
	FILE *fp = NULL;

	if (!Buff) 
	{
		TraceErr (m,"NULL Buffer\n");
		return retVal;
	}

	fp = fopen(file, "rb");
	if(!fp)
	{
		TraceErr (m,"File Open failed\n");
	}
	else
	{
		/* Seek to specified start address */
		if(fseek(fp, Start, SEEK_SET)) 
		{
			TraceErr (m,"Failed to seek file pointer to position %d\n",Start);
		}
		else
		{
			if(fread(Buff, Bytes, 1,fp) != 1)
			{
				TraceErr (m,"File Read failed\n");
			}
			else
			{
				retVal = SUCCESS;
			}
		}
		fclose(fp);
	}
	return retVal;

}

/************************************************************************
  * @brief :  Gets largest preset in current loaded ranking list 
  * @param[in]: None
  * @param[out]: None
  * @returns:  largest preset
  * 
  *************************************************************************/
int CHsvDvbsGeneric_mSort_Priv::GetLargestPresetInList(void)
{
	RANKING_LIST_NODE   *TempRankList = NULL;
	Nat32	NoofServiceInList = 0, SortingLoop = 0;
	int		LastRank = INVALID_INDEX;

	TempRankList = CurrentRankingList.StartNode;
	NoofServiceInList = CurrentRankingList.NoofServices;
	
	if ( TempRankList &&
		 NoofServiceInList )
	{
		for ( SortingLoop = 0;SortingLoop < NoofServiceInList; ++SortingLoop)
		{
			if ( TempRankList[SortingLoop].Rank > LastRank)
			{	
			   LastRank = TempRankList[SortingLoop].Rank;
			}		
		}
	}
	return LastRank;
}

/****************************************************************************
 * External functions
 ****************************************************************************/

/* provides IHsvPower isortpow */
void CHsvDvbsGeneric_mSort_Priv::isortpow_Init()
{
	Sortingpmp = pmp_PmpCreateEx(pen_PumpEngine, SortingHandler, TRUE, "hsvdvbins_msort");   
}

void CHsvDvbsGeneric_mSort_Priv::isortpow_TurnOn (void)
{

}

void CHsvDvbsGeneric_mSort_Priv::isortpow_TurnOff (void)
{

}

/* provides IHsvSorting		isort */

void CHsvDvbsGeneric_mSort_Priv::isort_Sort (Nat32 PackageIndex)
{
		TraceNotice(m,"%s %d\n", __FUNCTION__, __LINE__);
		pmp_PmpSend(Sortingpmp, SORTING_START, PackageIndex);
}
