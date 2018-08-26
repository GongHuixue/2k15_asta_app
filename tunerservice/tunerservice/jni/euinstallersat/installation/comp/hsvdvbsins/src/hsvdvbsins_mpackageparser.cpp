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
 *   C Source:       hsvdvbsins_mpackageparser.c
 *   Instance:       
 *   Description:    
 *   %created_by:     anuma %
 *   %date_created:   Mon May 13 11:56:11 2013 %
 *
**********************************************************************/

#include "_hsvdvbsins_mpackageparser.h"




TRACESYMBOL(m, "s2/installation/hsvdvbsins_mpackageparser")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#ifndef __cplusplus

#else

#endif




 






























 





/****************************************************************************
 * Static variables
 ****************************************************************************/


PackageSatelliteList CHsvDvbsInstallation_mpackageparser_Priv::s__DefaultPackageList [MAX_PACKAGE_SUPPORTED];

const PackageSatelliteListTemp DefaultPackageListTemp [MAX_PACKAGE_SUPPORTED] = 
{
	#include "SatellitePackageList.h"
};

const char PackageGroupNames [CURRENT_SUPPORTED_PACKAGE_GROUP][MAX_PACKAGE_GROUP_NAME_LEN] =
{
"M7",
"DIGITURK",
"Pol",
"Canal Digital",
"NTV+",
"Poland N",
"OpProfile",
"Tricolor",
"AstraLCN"
};

PackageGroupMapping CHsvDvbsInstallation_mpackageparser_Priv::s__DefaultPackageGroup [MAX_PACKAGE_GROUP_SUPPORTED] =
{
	#include "SatellitePackageGroup.h"
};




HsvPackageStructure CHsvDvbsInstallation_mpackageparser_Priv::s__FoundPackageList[MAX_PACKAGE_SUPPORTED];

HsvPackageStructure CHsvDvbsInstallation_mpackageparser_Priv::s__DynamicPackageList[MAX_DYNAMIC_PACKAGES];

FoundSatList CHsvDvbsInstallation_mpackageparser_Priv::s__FoundSatelliteList;

int CHsvDvbsInstallation_mpackageparser_Priv::s__NumPackagesFound = 0;

int CHsvDvbsInstallation_mpackageparser_Priv::s__NumDynamicPackagesFound = 0;

Nat32 CHsvDvbsInstallation_mpackageparser_Priv::s__TotalPackages = 0,CHsvDvbsInstallation_mpackageparser_Priv::s__TotalPackageGroups = 0;

Bool CHsvDvbsInstallation_mpackageparser_Priv::s__PackageListFound = FALSE;

Pump CHsvDvbsInstallation_mpackageparser_Priv::s__mPkgBldPump;

TypePackageParsingStatus CHsvDvbsInstallation_mpackageparser_Priv::s__PkgInsStatus;

ModuleLifeCycle CHsvDvbsInstallation_mpackageparser_Priv::s__mModuleLifeCycle = TurnedOff;


Op_ProfileStatusInfo CHsvDvbsInstallation_mpackageparser_Priv::s__mOpProfileStatusInfo;

CIPlusStatus_e CHsvDvbsInstallation_mpackageparser_Priv::s__mDynamicCIPlusStatus = Status_Inactive;


int CHsvDvbsInstallation_mpackageparser_Priv::s__SortedCountryIds [SUPPORTED_COUNTRIES_IN_PACKAGE] = { /* When a new package is added, enable the coresponding country too */ 
 /*   cids_CountryArgentina,*/\
/*    cids_CountryAlbania,*/\
/*    cids_CountryArmenia,*/\
/*    cids_CountryAustralia,*/\
    cids_CountryAustria,\
/*    cids_CountryAzerbaijan,*/\
/*    cids_CountryBelarus,*/\
    cids_CountryBelgium,\
/*    cids_CountryBosniaAndHerzegovina,*/\
/*    cids_CountryBrazil,*/\
/*    cids_CountryBulgaria,*/\
/*    cids_CountryChina,*/\
/*    cids_CountryCroatia,*/\
    cids_CountryCzechrep,\
    cids_CountryDenmark,\
/*    cids_CountryEstonia,*/\
    cids_CountryFinland,\
    cids_CountryFrance,\
/*    cids_CountryGeorgia,*/\
    cids_CountryGermany,\
/*    cids_CountryGreece,*/\
    cids_CountryHungary,
/*    cids_CountryIreland,*/\
/*    cids_CountryIsrael,*/\
/*    cids_CountryItaly,*/\
/*    cids_CountryKazakhstan,*/\
/*    cids_CountryLatvia,*/\
/*    cids_CountryLithuania,*/\
    cids_CountryLuxembourg,
/*    cids_CountryMacedoniafyrom*/\
/*    cids_CountryMontenegro,*/\
    cids_CountryNetherlands,
    cids_CountryNorway,
    cids_CountryPoland,
/*    cids_CountryPortugal,*/\
/*    cids_CountryRomania,*/\
    cids_CountryRussia,\
/*    cids_CountrySerbia,*/\
    cids_CountrySlovakia,
/*    cids_CountrySlovenia,*/\
/*    cids_CountrySpain,*/\
    cids_CountrySweden,
    cids_CountrySwitzerland,
    cids_CountryTurkey,
    cids_CountryUK,
/*    cids_CountryUkraine,*/\
};

/****************************************************************************
 * Static functions
 ****************************************************************************/




























FunctionNat32 CHsvDvbsInstallation_mpackageparser_Priv::s__PackageBuildingActionMatrix[EvPkgParseMax][StPkgMax] =
{
                                  /*	StPkgParseIdle,					StPkgParseStart,			StPkgParseTune,						StPkgParseDemuxWait					StPkgParsePopulatePkg */
/* EvPkgParseStart				*/ {	NULL,							FNADDR(FuncPkgParseStart),	NULL,								NULL,								NULL },
/* EvPkgParseTune				*/ {	NULL,							NULL,						FNADDR(FuncPkgParseStartTuning),	NULL,								NULL },
/* EvPkgParseLockChange			*/ {	NULL,							NULL,						FNADDR(FuncPkgParseCheckLockStatus),NULL,								NULL },
/* EvPkgParseDataAcquire		*/ {	NULL,							NULL,						NULL,								FNADDR(FuncPkgParseStartCollection),NULL },
/* EvPkgParseDataAcqComplete	*/ {	NULL,							NULL,						NULL,								FNADDR(FuncPkgParseStopCollection), NULL },
/* EvPkgParsePopulatePkg		*/ {	NULL,							NULL,						NULL,								NULL,								FNADDR(FuncPkgParsePopulatePackage) },
/* EvPkgParseComplete			*/ {	FNADDR(FuncPkgParseComplete),	NULL,						NULL,								NULL,								NULL }
};



void CHsvDvbsInstallation_mpackageparser_Priv::mPkgBuildPumpHandler(int event, Nat32 param)
{
    //TraceDebug (m, "event %d param %d state %d\n", event, (int)param, GET_PKG_BLD_INS_STATE);
    if(PKG_BLD_VALID_EVENT(event) && PKG_BLD_VALID_STATE(GET_PKG_BLD_INS_STATE))
    {
        //TraceDebug (m, "event %d param %d state %d\n", event, (int)param, GET_PKG_BLD_INS_STATE);
        if(PackageBuildingActionMatrix[event][GET_PKG_BLD_INS_STATE] != NULL)
        {
            TraceDebug (m, "event %d param %d state %d\n", event, (int)param, GET_PKG_BLD_INS_STATE);
            FPCALL(PackageBuildingActionMatrix[event][GET_PKG_BLD_INS_STATE])(param);
        }
    }
}

void CHsvDvbsInstallation_mpackageparser_Priv::mBuildPackageSatelliteList (void)
{
    Nat32       NumberOfPredefEntries = 0, NumberOfHomingEntries = 0, NumPackageGroups = 0, Count;
	int			MandatoryFlag = 0;

	if (PackageListFound == FALSE)
	{
		memset (DefaultPackageList, 0x00, sizeof(DefaultPackageList));

		NumPackageGroups = CURRENT_SUPPORTED_PACKAGE_GROUP;
		NumberOfPredefEntries = CURRENT_SUPPORTED_PREDEF_PACKAGES;
		NumberOfHomingEntries = CURRENT_SUPPORTED_HOMING_PACKAGES;

			NumPackageGroups = MIN (NumPackageGroups, MAX_PACKAGE_GROUP_SUPPORTED);

			/* Read the package group information */
			for (Count = 0; Count < NumPackageGroups; Count++)
			{
			charsetutil_MbToWc( (Nat8 *)PackageGroupNames[Count], strlen(PackageGroupNames[Count]),DefaultPackageGroup[Count].PackageGroupName, MAX_PACKAGE_GROUP_NAME_LEN, FALSE);
//			TraceDebug (m, " PackageGrouping: %d. GroupId %d GroupName %s" , Count, DefaultPackageGroup[Count].PackageGroupId, PackageGroupNames[Count]);
			}
			TotalPackageGroups = NumPackageGroups;

			if ((NumberOfPredefEntries + NumberOfHomingEntries) > MAX_PACKAGE_SUPPORTED)
			{
				TraceDebug (m, "Warning. More packages than currently configured");
				if (NumberOfPredefEntries > MAX_PACKAGE_SUPPORTED)
				{
					NumberOfPredefEntries = MAX_PACKAGE_SUPPORTED;
					NumberOfHomingEntries = 0;
				}
				else
				{
					NumberOfHomingEntries = (MAX_PACKAGE_SUPPORTED - NumberOfPredefEntries);
				}
			}

//		TraceDebug (m, " Predef %d Homing %d ", NumberOfPredefEntries, NumberOfHomingEntries);
		
		/* At first copy the Predefined Ranking list entries */
		for (Count = 0; Count < NumberOfHomingEntries; Count++)
		{
			DefaultPackageList[Count].MandatorySatellites = 0;
			
			DefaultPackageList[Count].PackageIndex = DefaultPackageListTemp[Count].PackageIndex;
			DefaultPackageList[Count].CountryIndex = DefaultPackageListTemp[Count].CountryIndex;
			DefaultPackageList[Count].Satellite1 = DefaultPackageListTemp[Count].Satellite1;
			MandatoryFlag = DefaultPackageListTemp[Count].Satellite1Mandatory;
			DefaultPackageList[Count].MandatorySatellites |= SET_MANDATORY_SAT(MandatoryFlag, 0);
			
			DefaultPackageList[Count].Satellite2 = DefaultPackageListTemp[Count].Satellite2;
			MandatoryFlag = DefaultPackageListTemp[Count].Satellite2Mandatory;
			DefaultPackageList[Count].MandatorySatellites |= SET_MANDATORY_SAT(MandatoryFlag, 1);
			
			DefaultPackageList[Count].Satellite3 = DefaultPackageListTemp[Count].Satellite3;
			MandatoryFlag = DefaultPackageListTemp[Count].Satellite3Mandatory;
			DefaultPackageList[Count].MandatorySatellites |= SET_MANDATORY_SAT(MandatoryFlag, 2);
			
			DefaultPackageList[Count].Satellite4 = DefaultPackageListTemp[Count].Satellite4;
			MandatoryFlag = DefaultPackageListTemp[Count].Satellite4Mandatory;
			DefaultPackageList[Count].MandatorySatellites |= SET_MANDATORY_SAT(MandatoryFlag, 3);
			
			charsetutil_MbToWc( (Nat8 *)DefaultPackageListTemp[Count].PackageName, strlen(DefaultPackageListTemp[Count].PackageName),DefaultPackageList[Count].PackageName, MAX_PACKAGE_NAME_LEN, FALSE);
			charsetutil_MbToWc( (Nat8 *)DefaultPackageListTemp[Count].PackageListName, strlen(DefaultPackageListTemp[Count].PackageListName),DefaultPackageList[Count].PackageListName, MAX_PACKAGELIST_NAME_LEN, FALSE);
		//	TraceDebug (m, "HomingPackages: PacakgeId %d Country %d  PackageName %s ", DefaultPackageList[Count].PackageIndex,\
												DefaultPackageList[Count].CountryIndex,DefaultPackageListTemp[Count].PackageListName);
		}

		/* Parse the Predefined Ranking list entries */
		for (Count = 0; Count < NumberOfPredefEntries; Count++)
		{
			DefaultPackageList[NumberOfHomingEntries + Count].MandatorySatellites = 0;
			DefaultPackageList[NumberOfHomingEntries + Count].PackageIndex = DefaultPackageListTemp[NumberOfHomingEntries + Count].PackageIndex;
			DefaultPackageList[NumberOfHomingEntries + Count].CountryIndex = DefaultPackageListTemp[NumberOfHomingEntries + Count].CountryIndex;
			
			DefaultPackageList[NumberOfHomingEntries + Count].Satellite1 = DefaultPackageListTemp[NumberOfHomingEntries + Count].Satellite1;
			MandatoryFlag = DefaultPackageListTemp[NumberOfHomingEntries + Count].Satellite1Mandatory;
			DefaultPackageList[NumberOfHomingEntries + Count].MandatorySatellites |= SET_MANDATORY_SAT(MandatoryFlag, 0);
	
			DefaultPackageList[NumberOfHomingEntries + Count].Satellite2 = DefaultPackageListTemp[NumberOfHomingEntries + Count].Satellite2;
			MandatoryFlag = DefaultPackageListTemp[NumberOfHomingEntries + Count].Satellite2Mandatory;
			DefaultPackageList[NumberOfHomingEntries + Count].MandatorySatellites |= SET_MANDATORY_SAT(MandatoryFlag, 1);
			
			DefaultPackageList[NumberOfHomingEntries + Count].Satellite3 = DefaultPackageListTemp[NumberOfHomingEntries + Count].Satellite3;
			MandatoryFlag = DefaultPackageListTemp[NumberOfHomingEntries + Count].Satellite3Mandatory;
			DefaultPackageList[NumberOfHomingEntries + Count].MandatorySatellites |= SET_MANDATORY_SAT(MandatoryFlag, 2);
			
			DefaultPackageList[NumberOfHomingEntries + Count].Satellite4 = DefaultPackageListTemp[NumberOfHomingEntries + Count].Satellite4;
			MandatoryFlag = DefaultPackageListTemp[NumberOfHomingEntries + Count].Satellite4Mandatory;
			DefaultPackageList[NumberOfHomingEntries + Count].MandatorySatellites |= SET_MANDATORY_SAT(MandatoryFlag, 3);
			
			
			charsetutil_MbToWc( (Nat8 *)DefaultPackageListTemp[NumberOfHomingEntries + Count].PackageName, strlen(DefaultPackageListTemp[NumberOfHomingEntries + Count].PackageName),DefaultPackageList[NumberOfHomingEntries + Count].PackageName, MAX_PACKAGE_NAME_LEN, FALSE);
			
			
			charsetutil_MbToWc( (Nat8 *)DefaultPackageListTemp[NumberOfHomingEntries + Count].PackageListName, strlen(DefaultPackageListTemp[NumberOfHomingEntries + Count].PackageListName),DefaultPackageList[NumberOfHomingEntries + Count].PackageListName, MAX_PACKAGELIST_NAME_LEN, FALSE);
			
			strcpy ((char*)DefaultPackageList[NumberOfHomingEntries + Count].PredefinedListBinFile, (const char *) DefaultPackageListTemp[NumberOfHomingEntries + Count].PredefinedListBinFile);

		//	TraceDebug (m, "PredefinedList: PacakgeId %d Country %d  PackageName %s BinFileName %s ", DefaultPackageList[NumberOfHomingEntries + Count].PackageIndex,\
												DefaultPackageList[NumberOfHomingEntries + Count].CountryIndex,DefaultPackageListTemp[NumberOfHomingEntries + Count].PackageListName, DefaultPackageList[NumberOfHomingEntries + Count].PredefinedListBinFile);
		}

		TotalPackages = NumberOfPredefEntries + NumberOfHomingEntries;

		PackageListFound = TRUE;
	}
}

void CHsvDvbsInstallation_mpackageparser_Priv::mBuildFoundSatelliteList (void)
{
    HsvPgdatDigSatInfoData  SatInfo;
    Nat8                    Count = 0, NumSatellites = 0;

    /* Get the Satellite Details from pgdb. And put those details to cache */
    for (Count = 0; Count < MAX_SATELLITES_SUPPORTED; Count++)
    {
        SatInfo.LnbNumber = Count;
        if(pgdb_GetByKey(SAT_INFO_TABLE, (Address)&SatInfo) == TRUE)
        {
            FoundSatelliteList.SatelliteIndex[NumSatellites] = SatInfo.SatelliteId;
            TraceDebug (m,"FoundSatellite in Lnb %d ID %d ", Count, SatInfo.SatelliteId);
            NumSatellites++;
        }
    }

    FoundSatelliteList.NumSatellites = NumSatellites;
}

void CHsvDvbsInstallation_mpackageparser_Priv::mBuildDynamicPackageList(int CountryId)
{
	HsvBATDetails DbaseBatDetails = {0};
	Nat32 OuterLoop = 0,InnerLoop = 0,TotRecords = 0,BouquetIndex = 0,PackageId = 0;

	memset(DynamicPackageList, 0,(MAX_DYNAMIC_PACKAGES * sizeof(HsvPackageStructure)));
	NumDynamicPackagesFound = 0;

	for (OuterLoop = 0;	OuterLoop < FoundSatelliteList.NumSatellites; OuterLoop++ )
	{
		PackageId = 0;
		GET_PACKAGE_ID(FoundSatelliteList.SatelliteIndex[OuterLoop], CountryId, PackageId);

		if(FRANSAT_PACKAGE_ID == PackageId)
		{
			TotRecords = strapi_GetSize(HsvMain, HSVSPID(batDetails, dvb, bat));
			TraceDebug (m,"Fransat package detected, Num of bat %d", TotRecords);
			for(InnerLoop = 0; InnerLoop < TotRecords; InnerLoop++)
			{
				strapi_GetByIndex(HsvMain, HSVSPID(batDetails, dvb, bat), InnerLoop, (void*)(&DbaseBatDetails));
				TraceDebug (m,"Fransat package detected, Index %d Batid 0x%x", InnerLoop, DbaseBatDetails.BouquetId);

				BouquetIndex = GET_INDEX_FOR_BOUQUET_ID(DbaseBatDetails.BouquetId);

				if( BouquetIndex < MAX_FRANSAT_PACKAGES )
				{
					/* Setting Index to true to indicate package available */
					DynamicPackageList[BouquetIndex].Index = TRUE;
					DynamicPackageList[BouquetIndex].PackageId = CREATE_DYNAMIC_PACKAGE_ID(PackageId,DbaseBatDetails.BouquetId);
					memcpy((char*)DynamicPackageList[BouquetIndex].PackageName,DbaseBatDetails.BouquetName, (64 * sizeof(Nat8)));
					++NumDynamicPackagesFound;
					TraceDebug (m,"Fransat package detected, Index %d Pkg id 0x%x Pkg Name %s", InnerLoop,
											DynamicPackageList[BouquetIndex].PackageId,
											DynamicPackageList[BouquetIndex].PackageName);
				}
			}
		}
	}
}

void CHsvDvbsInstallation_mpackageparser_Priv::mFindNationalPackages (int CountryId,Bool IsSatIP)
{
    Nat32   Count = 0, InnerLoop = 0, SatFound = 0, tempCount = 0;
	Nat16	GroupID = 0;

    if (FoundSatelliteList.NumSatellites > 0)
    {
        for (Count = 0; Count < TotalPackages; Count++)
        {
   			if((!IsSatIP) || (DefaultPackageList[Count].SatIP))
   			{
	            SatFound = 0;
	            if (DefaultPackageList[Count].CountryIndex == CountryId)
	            {
	                if (DefaultPackageList[Count].Satellite1 != INVALID_SAT_INDEX)
	                {
	                	ipackage_GetPackageGroupId((Nat32)DefaultPackageList[Count].PackageIndex,&GroupID);
						if(GroupID != M7)
						{
		                    CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite1)
		                    if ((SatFound) && (DefaultPackageList[Count].Satellite2 != INVALID_SAT_INDEX) && (IS_MANDATORY_SAT(DefaultPackageList[Count].MandatorySatellites,1)))
		                    {
		                        CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite2)
		                        if ((SatFound) && (DefaultPackageList[Count].Satellite3 != INVALID_SAT_INDEX) && (IS_MANDATORY_SAT(DefaultPackageList[Count].MandatorySatellites,2)))
		                        {
		                            CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite3)
		                            if ((SatFound) && (DefaultPackageList[Count].Satellite4 != INVALID_SAT_INDEX) && (IS_MANDATORY_SAT(DefaultPackageList[Count].MandatorySatellites,3)))
		                            {
		                                CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite4)
		                                ADD_PACKAGE_TO_FOUND_LIST
		                            }
		                            else ADD_PACKAGE_TO_FOUND_LIST
		                        }
		                        else ADD_PACKAGE_TO_FOUND_LIST
		                    }
		                    else ADD_PACKAGE_TO_FOUND_LIST
						}
						else
						{
							if (DefaultPackageList[Count].Satellite1 != INVALID_SAT_INDEX)
							{
								CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite1)
			                    if ((!SatFound) && (DefaultPackageList[Count].Satellite2 != INVALID_SAT_INDEX))
			                   	{
			                   		CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite2)
			                    }
								ADD_PACKAGE_TO_FOUND_LIST
							}
						}
	                }
	            }
        	}
        }
    }
}
    
void CHsvDvbsInstallation_mpackageparser_Priv::mAddNoSorting (void)
{
    char    *NoSortingString = NO_SORTING_STRING;
    
    FoundPackageList[NumPackagesFound].Index = NumPackagesFound;
    FoundPackageList[NumPackagesFound].PackageId = NO_SORTING_PACKAGE_ID;
    charsetutil_MbToWc( (Nat8 *)NoSortingString, strlen(NoSortingString),FoundPackageList[NumPackagesFound].PackageName, MAX_PACKAGE_NAME_LEN, FALSE);
	charsetutil_MbToWc( (Nat8 *)NoSortingString, strlen(NoSortingString),FoundPackageList[NumPackagesFound].PackageListName, MAX_PACKAGELIST_NAME_LEN, FALSE);
    NumPackagesFound++;
}

void CHsvDvbsInstallation_mpackageparser_Priv::mAddOpProfileName (void)
{
    char *defaultOpProfileString = DEFAULT_OPERATOR_PROFILE;
    
//    TraceNotice (m, "%s() : IN\n", __FUNCTION__);

  //  TraceNotice (m, "Profile_Type %d, profile_Name %s \n", mOpProfileStatusInfo.op_Status.Profile_Type, mOpProfileStatusInfo.op_Info.profile_Name);
    if ((2 == mOpProfileStatusInfo.op_Status.Delivery_System_Hint) && 
         (OP_PROFILE_TYPE_0 == mOpProfileStatusInfo.op_Status.Profile_Type || OP_PROFILE_TYPE_1 == mOpProfileStatusInfo.op_Status.Profile_Type))
    {
        if (0 != mOpProfileStatusInfo.op_Info.profile_Name_Length) 
        {
            FoundPackageList[NumPackagesFound].Index = NumPackagesFound;
            FoundPackageList[NumPackagesFound].PackageId = OP_PROFILE_PACKAGE_ID;
            charsetutil_MbToWc( (Nat8 *)mOpProfileStatusInfo.op_Info.profile_Name, mOpProfileStatusInfo.op_Info.profile_Name_Length, FoundPackageList[NumPackagesFound].PackageName, MAX_PACKAGE_NAME_LEN, FALSE);
            charsetutil_MbToWc( (Nat8 *)mOpProfileStatusInfo.op_Info.profile_Name, mOpProfileStatusInfo.op_Info.profile_Name_Length, FoundPackageList[NumPackagesFound].PackageListName, MAX_PACKAGELIST_NAME_LEN, FALSE);
    //        TraceNotice (m, "%s() : Profile Name -> %s\n", __FUNCTION__, mOpProfileStatusInfo.op_Info.profile_Name);
            NumPackagesFound++;
        }
        else if (0 == mOpProfileStatusInfo.op_Info.info_Valid)
        {
            FoundPackageList[NumPackagesFound].Index = NumPackagesFound;
            FoundPackageList[NumPackagesFound].PackageId = OP_PROFILE_PACKAGE_ID;
            charsetutil_MbToWc( (Nat8 *)defaultOpProfileString, strlen(defaultOpProfileString), FoundPackageList[NumPackagesFound].PackageName, MAX_PACKAGE_NAME_LEN, FALSE);
            charsetutil_MbToWc( (Nat8 *)defaultOpProfileString, strlen(defaultOpProfileString), FoundPackageList[NumPackagesFound].PackageListName, MAX_PACKAGELIST_NAME_LEN, FALSE);
            TraceNotice (m, "%s() : Profile Name -> %s\n", __FUNCTION__, defaultOpProfileString);
            NumPackagesFound++;
        }
    }

    //TraceNotice (m, "%s() : OUT\n", __FUNCTION__);
}


void CHsvDvbsInstallation_mpackageparser_Priv::mFindForeignPackages (int CountryId, Bool IsSatIP)
{
    Nat32   Count = 0, InnerLoop = 0, SatFound = 0, tempCount = 0;
	Nat16	GroupID = 0;
    Nat32   CountryIdLoop, MaxCountryIds = sizeof(SortedCountryIds)/sizeof(SortedCountryIds[0]);

    if (FoundSatelliteList.NumSatellites > 0)
    {
        /* Country sorted order is already defined. Based on this group the foreign packages.
         * Not distringuishing between predefined and homing basex mux */
        for (CountryIdLoop = 0; CountryIdLoop < MaxCountryIds; CountryIdLoop++)
        {
            if (SortedCountryIds[CountryIdLoop] != CountryId)
            {
                for (Count = 0; Count < TotalPackages; Count++)
                {
					if((!IsSatIP) || (DefaultPackageList[Count].SatIP))
					{
	                    SatFound = 0;
						/* brg36mgr#251712 : Canal digital packages are not to be shown on foreign package list */
	                    if ((SortedCountryIds[CountryIdLoop] == DefaultPackageList[Count].CountryIndex) \
	                            && (DefaultPackageList[Count].CountryIndex != CountryId) 
	                            && (IsForeignPackageAvailable(DefaultPackageList[Count].PackageIndex)== FALSE))
	                    {
		                    
		                	ipackage_GetPackageGroupId((Nat32)DefaultPackageList[Count].PackageIndex,&GroupID);
							if(GroupID != M7)
							{
								if (DefaultPackageList[Count].Satellite1 != INVALID_SAT_INDEX)
		                        {
		                            CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite1)
	                                if ((SatFound) && (DefaultPackageList[Count].Satellite2 != INVALID_SAT_INDEX) && (IS_MANDATORY_SAT(DefaultPackageList[Count].MandatorySatellites,1)))
	                                {
	                                    CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite2)
	                                        if ((SatFound) && (DefaultPackageList[Count].Satellite3 != INVALID_SAT_INDEX) && (IS_MANDATORY_SAT(DefaultPackageList[Count].MandatorySatellites,2)))
	                                        {
	                                            CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite3)
	                                                if ((SatFound) && (DefaultPackageList[Count].Satellite4 != INVALID_SAT_INDEX) && (IS_MANDATORY_SAT(DefaultPackageList[Count].MandatorySatellites,3)))
	                                                {
	                                                    CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite4)
	                                                    ADD_PACKAGE_TO_FOUND_LIST
	                                                }
	                                                else ADD_PACKAGE_TO_FOUND_LIST
	                                        }
	                                        else ADD_PACKAGE_TO_FOUND_LIST
	                                }
	                                else ADD_PACKAGE_TO_FOUND_LIST
		                        }
							}
							else
							{
								if (DefaultPackageList[Count].Satellite1 != INVALID_SAT_INDEX)
		                        {
									CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite1)
				                    if ((!SatFound) && (DefaultPackageList[Count].Satellite2 != INVALID_SAT_INDEX))
				                   	{
				                   		CHK_PACKAGE_SAT_IN_FOUND_LIST(DefaultPackageList[Count].Satellite2)
				                    }
									ADD_PACKAGE_TO_FOUND_LIST
								}
							}
	                    }
                	}
               }
			}
        }
    }
}

void CHsvDvbsInstallation_mpackageparser_Priv::mReorderOnMenuLanguage (int CountryId)
{
    int     Count = 0;
	HsvPackageStructure		TempPackageInfo;
    /* This is a very specific requirment for Belgium only. If menu language is French, 
     * Telesat Belgium should come on top of TV Vlanderen HD/SD. Since its a specific requirement
     * doing it seperately */
    if ((CountryId == cids_CountryBelgium) && (apsysset_GetMenuLanguage() == lngids_LangFrench))
    {
        for (Count = 0; Count < NumPackagesFound; Count++)
        {
            if (FoundPackageList[Count].PackageId == TVVLAANDEREN_HD_BOUQUET_ID)
            {
                /* Order will be TVVlander HD, SD, TeleSat Belgium.
                 * Reorder to Telesat Belgium TVVlanderen HD Sd */
				memcpy (&TempPackageInfo, &(FoundPackageList[Count+2]), sizeof(HsvPackageStructure));
				memcpy (&(FoundPackageList[Count+2]), &(FoundPackageList[Count+1]), sizeof(HsvPackageStructure));
				memcpy (&(FoundPackageList[Count+1]), &(FoundPackageList[Count]), sizeof(HsvPackageStructure));
				memcpy (&(FoundPackageList[Count]), &TempPackageInfo, sizeof(HsvPackageStructure));
				break;
            }
        }
    }
}

void CHsvDvbsInstallation_mpackageparser_Priv::DetermineCanalDigitalPackage (int CountryId, Bool *IsNordigCountry, Bool *IsThorDetected)
{
	int		count = 0;
	*IsNordigCountry = *IsThorDetected = FALSE;

	switch (CountryId)
	{
	case	cids_CountryDenmark:
	case	cids_CountryFinland:
	case	cids_CountryNorway:
	case	cids_CountrySweden:
		*IsNordigCountry = TRUE;
		break;
	default:
		break;
	}

	for (count = 0; count < FoundSatelliteList.NumSatellites; count++)
	{
		if (FoundSatelliteList.SatelliteIndex[count] == THOR_1W)
		{
			*IsThorDetected = TRUE;	
			break;
        }
    }
}

void CHsvDvbsInstallation_mpackageparser_Priv::DetermineDigiturkMduDetected (Bool *MduDetected)
{
	int		count = 0;
	Bool	MduOnlyDetected = FALSE, NonMduDetected = FALSE;

	*MduDetected = FALSE;
	//if (FoundSatelliteList.NumSatellites)
	for (count = 0; count < FoundSatelliteList.NumSatellites; count++)
	{
		switch (FoundSatelliteList.SatelliteIndex[count])
		{
			case	EUTELSAT_W3A_7E_MDU4:
			case	EUTELSAT_W3A_7A_MDU5:
			case	EUTELSAT_W3A_7E_MDU3:
			case	EUTELSAT_W3A_7E_MDU2:
			case	EUTELSAT_W3A_7E_MDU1:
				MduOnlyDetected = TRUE;
				break;
			default:
				NonMduDetected = TRUE;
				break;
		}
	}
	*MduDetected = ((MduOnlyDetected == TRUE) && (NonMduDetected == FALSE));
}


void CHsvDvbsInstallation_mpackageparser_Priv::mFindCanalDigitalPackage (int CountryId)
{
	int PackageId = 0, Count = 0;

	switch (CountryId)
	{
		case	cids_CountryDenmark:
			PackageId = CANALDIGITAL_DENMARK_PACKAGE_ID;
			break;
		case	cids_CountryFinland:
			PackageId = CANALDIGITAL_FINLAND_PACKAGE_ID;
			break;
		case	cids_CountryNorway:
			PackageId = CANALDIGITAL_NORWAY_PACKAGE_ID;
			break;
		case	cids_CountrySweden:
			PackageId = CANALDIGITAL_SWEDEN_PACKAGE_ID;
			break;
		default:
			break;
	}

	for (Count = 0; Count < TotalPackages; Count++)
	{
		if (DefaultPackageList[Count].PackageIndex == PackageId)
		{
			FoundPackageList[NumPackagesFound].Index = NumPackagesFound;
			FoundPackageList[NumPackagesFound].PackageId = DefaultPackageList[Count].PackageIndex;
			memcpy (FoundPackageList[NumPackagesFound].PackageName, DefaultPackageList[Count].PackageName, (MAX_PACKAGE_NAME_LEN * sizeof(Nat16)));
			memcpy (FoundPackageList[NumPackagesFound].PackageListName, DefaultPackageList[Count].PackageListName, (MAX_PACKAGELIST_NAME_LEN * sizeof(Nat16)));
			memcpy (FoundPackageList[NumPackagesFound].PredefinedListBinFile, DefaultPackageList[Count].PredefinedListBinFile, MAX_PREDEFBINFILE_NAME_LEN);
			NumPackagesFound++;
		}
	}

//	TraceNotice(m, "NumPkg %d PkgIndex %d ", NumPackagesFound, (int)FoundPackageList[NumPackagesFound-1].PackageId);
}

Bool CHsvDvbsInstallation_mpackageparser_Priv::IsForeignPackageAvailable(int PackageId)
{
	Bool	RetVal = FALSE;

	switch (PackageId)
	{
		case	CANALDIGITAL_DENMARK_PACKAGE_ID:
		case	CANALDIGITAL_FINLAND_PACKAGE_ID:
		case	CANALDIGITAL_NORWAY_PACKAGE_ID:
		case	CANALDIGITAL_SWEDEN_PACKAGE_ID:
		case    FREESAT_PACKAGE_ID:
			RetVal = TRUE;
			break;
		default:
			break;
	}
	return RetVal;
}


void CHsvDvbsInstallation_mpackageparser_Priv::mStopPackageParsing( void )
{
    /* Package parsing completed, Consumer callback have TO DO */
    if( StPkgParseIdle != GET_PKG_BLD_INS_STATE )
    {
        TraceNotice (m, "Package parsing stoped");
        /* Since if user interrupts parsing to stop then this condition works */
        ctrl_StopCollection(HsvDmxMain);
        SET_PKG_BLD_INS_STATE(StPkgParseIdle);
    }

    PkgInsStatus.CurrentLNBNumber = 0;
}


void CHsvDvbsInstallation_mpackageparser_Priv::FuncPkgParseStart( Nat32 param )
{
    Nat32 CurrentLNBNumber = param;

    if( CurrentLNBNumber < MAX_SATELLITES_SUPPORTED )
    {
        TraceNotice (m, "Package parsing started LNB Number %ld\n", CurrentLNBNumber );
        PkgInsStatus.CurrentPrescanIndex = 0;
        SET_PKG_BLD_INS_STATE(StPkgParseTune);
        /* This msg calls FuncPkgParseStartTuning */
        pmp_PmpSend(mPkgBldPump, EvPkgParseTune, CurrentLNBNumber);
    }
    else
    {
        //TraceNotice (m, "Populate package notification send" );
        /* All satellites completed populate the package */
        SET_PKG_BLD_INS_STATE(StPkgParsePopulatePkg);
        /* This msg calls FuncPkgParsePopulatePackage */
        pmp_PmpSend(mPkgBldPump, EvPkgParsePopulatePkg, 0);

    }
}

void CHsvDvbsInstallation_mpackageparser_Priv::FuncPkgParseCheckLockStatus(Nat32 param)
{
    FResult     RetVal = err_InstallationCommandNotAllowed;
    int         LnbNumber = 0,
                LnbType = 0,
                LockStatus = 0,
                LockedFreq = 0,
                Polarization = 0,
                SymbolRate = 0,
                IqMode = 0,
                Bandwidth = 0;

    RetVal = satfeapi_GetSatelliteFrontEndParams (&LnbNumber, &LnbType, &LockStatus, &LockedFreq, &Polarization, &SymbolRate, &IqMode, &Bandwidth);

    TraceNotice (m, "Lock status %d Locked Freq#%u Sym#%u\n",LockStatus, LockedFreq, SymbolRate);

    if ((RetVal == err_Ok) && LockStatus )
    {
        SET_PKG_BLD_INS_STATE(StPkgParseDemuxWait);
        /* This msg calls FuncPkgParseStartCollection */
        pmp_PmpSend(mPkgBldPump, EvPkgParseDataAcquire, (Nat32)0);
    }
    else
    {
        /* Satellite Not Locked, Tune to next Satellite */
        pmp_PmpSend(mPkgBldPump, EvPkgParseTune, (Nat32)0);
    }
}

void CHsvDvbsInstallation_mpackageparser_Priv::FuncPkgParseStartTuning(Nat32 param)
{
    Nat32 LnbNumber = param,TotalNoOfPrescanEntries = 0,PrescanIndex = 0;

    HsvPgdatDigSatInfoData  SatInfo = {0};
    HsvSatelliteList        PreScanTableSatellite = {0};

    SatInfo.LnbNumber = LnbNumber;

    if( pgdb_GetByKey( SAT_INFO_TABLE, (Address)&SatInfo))
    {
        if( (EUTELSAT_5_W == SatInfo.SatelliteId ) && ( cids_CountryFrance == sysset_GetSystemCountry()))
        {
            TotalNoOfPrescanEntries = iprescanparser_GetNumberOfPrescanEntries();
                     PrescanIndex =  PkgInsStatus.CurrentPrescanIndex;
                     TraceNotice (m,"Prescan index %ld",PrescanIndex);
            while ( PrescanIndex < TotalNoOfPrescanEntries )
            {
                if( iprescanparser_GetSatelliteEntryFromPreScanTable(PrescanIndex,&PreScanTableSatellite ) )
                {
                    TraceDebug(m,"Prescan index %d Sat Id %d",PrescanIndex, PreScanTableSatellite.SatelliteId);
                    if( EUTELSAT_5_W == PreScanTableSatellite.SatelliteId )
                    {
                        TraceNotice (m, "{Freq#%d LN#%d LT#%d Pol#%d}\n",
                                                    PreScanTableSatellite.PrescanFrequency,
                                                    SatInfo.LnbNumber,
                                                    SatInfo.LnbType,
                                                    PreScanTableSatellite.Polarization );

                        /* Only if fransat then we have collected the BAT for bouquet name */
                        satfeapi_SatelliteFrontEndTune( SatInfo.LnbNumber,
                                                        SatInfo.LnbType,
                                                        PreScanTableSatellite.PrescanFrequency,
                                                        0,
                                                        PreScanTableSatellite.Polarization,
                                                        0,
                                                        -1,
                                                        -1,
                                                        -1,
                                                        -1,
                                                        -1,
                                                        -1);
                        break;
                    }
                }
                ++PrescanIndex;
            }
             PkgInsStatus.CurrentPrescanIndex =  PrescanIndex;
             PkgInsStatus.CurrentPrescanIndex++;
        }

    }

    /*if the tuning is initiated, then don't post EvPkgParseStart event, it will be posted
    after acquiring data*/
    if( PrescanIndex == TotalNoOfPrescanEntries )
    {
        TraceNotice (m, "Prescan completed for LNB %ld\n",PkgInsStatus.CurrentLNBNumber);
        /* Tune to next Satellite, skipping satellites having predefined package list */
        SET_PKG_BLD_INS_STATE(StPkgParseStart);
        /* This msg calls FuncPkgParseStart */
        pmp_PmpSend(mPkgBldPump, EvPkgParseStart, (Nat32)(++PkgInsStatus.CurrentLNBNumber));
    }
}

void CHsvDvbsInstallation_mpackageparser_Priv::FuncPkgParseStartCollection(Nat32 param)
{
//    TraceNotice (m, "Start collection" );
    ctrl_StartCollection(HsvDmxMain, ctrl_PkgBuildMode );
    /* Note : On completion of collection, ctrlN_OnEvent of hsvdvbsins is called,
     * where tuning of next satellite is posted
     */
}

void CHsvDvbsInstallation_mpackageparser_Priv::FuncPkgParseStopCollection(Nat32 param)
{
//     TraceNotice (m, "Stop collection" );
    /* Stop previous collection and Tune to next satellite */
    ctrl_StopCollection(HsvDmxMain);
    SET_PKG_BLD_INS_STATE(StPkgParseStart);

    /* This msg calls FuncPkgParseStart */
    pmp_PmpSend(mPkgBldPump, EvPkgParseStart, (Nat32)++PkgInsStatus.CurrentLNBNumber);
}

void CHsvDvbsInstallation_mpackageparser_Priv::FuncPkgParsePopulatePackage(Nat32 param)
{
//     TraceNotice (m, "Populate package" );
    ipackage_IdentifyPackagesAvailable( );

    SET_PKG_BLD_INS_STATE(StPkgParseIdle);

    /* This msg calls FuncPkgParseComplete */
    pmp_PmpSend(mPkgBldPump, EvPkgParseComplete, (Nat32)0);
}

void CHsvDvbsInstallation_mpackageparser_Priv::FuncPkgParseComplete(Nat32 param)
{
    mStopPackageParsing( );
    iinsN_OnEvent(iinsN_EventPkgParsingCompleted,0);
}

void CHsvDvbsInstallation_mpackageparser_Priv::ipackageparsersatfrontendN_OnLockChanged(Bool LockState)
{
//    TraceNotice (m, "Onlock change notificaton received" );
    /* This msg calls FuncPkgParseCheckLockStatus where lock status will be checked */
    pmp_PmpSend(mPkgBldPump, EvPkgParseLockChange, (Nat32)LockState );
}


void CHsvDvbsInstallation_mpackageparser_Priv::mInitOpProfileStatusInfo (void)
{    
    memset(&mOpProfileStatusInfo, 0, sizeof(mOpProfileStatusInfo));
    mOpProfileStatusInfo.op_Status.Profile_Type = OP_PROFILE_TYPE_INVALID;
    
}

Bool CHsvDvbsInstallation_mpackageparser_Priv::mIsCAMInserted (void)
{
    Bool retVal = FALSE;
    Nat8 camStatus = 0;

    cipStatus->GetCipStatus (&camStatus);

    switch (camStatus)
    {
        case Status_Initialising:
        case Status_Initialsed:
        case Status_Authorised:
        case Status_NOT_Authorised:
        case Status_V1:
            retVal = TRUE;
            break;
        case Status_Inactive:
        default:
            break;
    }
    TraceNotice (m, "%s() : CAMInserted is %s \n", __FUNCTION__, (retVal == TRUE ? "True" : "False"));
    return retVal;
}

/****************************************************************************
 * External functions
 ****************************************************************************/


/* provides IHsvPower iPackage */

void CHsvDvbsInstallation_mpackageparser_Priv::impackagepow_Init (void)
{
    mPkgBldPump = pmp_PmpCreateEx( pen_PumpEngine, mPkgBuildPumpHandler, FALSE, "hsvdvbsins_m_pkbld_pmp" );
    mModuleLifeCycle = Initialised;
    mInitOpProfileStatusInfo ();    
}

void CHsvDvbsInstallation_mpackageparser_Priv::impackagepow_TurnOn (void)
{
    mModuleLifeCycle = TurnedOn;
    SET_PKG_BLD_INS_STATE(StPkgParseIdle);
}

void CHsvDvbsInstallation_mpackageparser_Priv::impackagepow_TurnOff (void)
{
    mModuleLifeCycle = TurnedOff;
    mStopPackageParsing();
    SET_PKG_BLD_INS_STATE(StPkgParseIdle);
}


FResult CHsvDvbsInstallation_mpackageparser_Priv::ipackage_StartPackageParsing( void )
{
    FResult retval = err_InstallationCommandNotAllowed;

  //  TraceNotice (m, "Start Package parsing incoked%d#%d\n", TURNED_ON,GET_PKG_BLD_INS_STATE );

    if((TURNED_ON ) && ( StPkgParseIdle == GET_PKG_BLD_INS_STATE ))
    {
            /* 0 => first satelite index */
            PkgInsStatus.CurrentLNBNumber = 0;
            PkgInsStatus.CurrentPrescanIndex = 0;
            SET_PKG_BLD_INS_STATE(StPkgParseStart);
            /* This msg calls FuncPkgParseStart */
            pmp_PmpSend(mPkgBldPump, EvPkgParseStart, (Nat32)PkgInsStatus.CurrentLNBNumber);
            retval = err_Ok;
    }

    return retval;
}


FResult CHsvDvbsInstallation_mpackageparser_Priv::ipackage_StopPackageParsing(void)
{
    FResult RetVal = err_InstallationCommandNotAllowed;

    //TraceNotice (m, "Stop package parsing invoked %d#%d\n", TURNED_ON,GET_PKG_BLD_INS_STATE);

    if((TURNED_ON ) &&  ( StPkgParseIdle != GET_PKG_BLD_INS_STATE ))
    {
        mStopPackageParsing( );
        RetVal = err_Ok;
    }

    return RetVal;
}


/* provides IHsvInstallationPackage ipackage */

FResult CHsvDvbsInstallation_mpackageparser_Priv::ipackage_IdentifyPackagesAvailable (void)
{
    FResult     RetVal = err_Ok;
    int     CountryId;
    Bool IsThorDetected = FALSE, IsNordigCountry = FALSE;
    Bool MduDetected = FALSE;
	HsvLnbSettings				LnbSettings;
	Bool IsSatIP = FALSE;

	
	if (err_Ok == dvbset_GetLnbSettings(&LnbSettings))
	{
		if(LnbSettings.ConnectionType == LnbConnectionSatIp)
		{
			IsSatIP = TRUE;		
		}
	}

    mBuildPackageSatelliteList ();

    NumPackagesFound = 0;

    /* Getting the current country */
    CountryId = sysset_GetSystemCountry();

    /* Now build the found satellite details */
    mBuildFoundSatelliteList ();

    /* This API builds the package list dynamically */
    mBuildDynamicPackageList(CountryId);

    DetermineCanalDigitalPackage (CountryId, &IsNordigCountry, &IsThorDetected);
    DetermineDigiturkMduDetected (&MduDetected);

    /* Find the national Packages first. Then add 'NO SORTING' 
        and finally add the foreign Packages */
    if ((IsNordigCountry == TRUE) && (IsThorDetected == TRUE))
    {
        /* brg36mgr#251712: When Thor detected in Nordig country. Only show Canal Digital and No sorting. Foreign packages r not required */
        TraceNotice (m, "IsNordigCountry is TRUE \n");
        mFindCanalDigitalPackage (CountryId);
    }
    else
    {
        mFindNationalPackages (CountryId,IsSatIP);
    }
    
    if ((MduDetected == FALSE) && (!IsSatIP))
    {
        mAddNoSorting ();
    }

    if (!((IsNordigCountry == TRUE) && (IsThorDetected == TRUE)))
    {
        TraceNotice (m, "Foreign package parsing ");
        mFindForeignPackages (CountryId, IsSatIP);
    }

  //  TraceNotice (m, "NumberOf Packages available for CurrentPrescan %d ", NumPackagesFound);
    mReorderOnMenuLanguage (CountryId);

    return RetVal;
}

int CHsvDvbsInstallation_mpackageparser_Priv::ipackage_GetNumberOfPackages (void)
{
    //TraceNotice (m, "NumberOf Packages available for CurrentPrescan %d ", NumPackagesFound);
    return NumPackagesFound;
}

FResult CHsvDvbsInstallation_mpackageparser_Priv::ipackage_GetPackageByIndex (int Index, HsvPackageStructure  *Package)
{
    FResult RetVal  =   err_BadParameter;

    /* List is already made. Just copy the details back */
    if ((Index < NumPackagesFound) && (Package != NULL))
    {
        TraceDebug (m, " GetPackageByIndex: Index:%d PackageId %d ",Index, FoundPackageList[Index].PackageId);
        memcpy (Package, &FoundPackageList[Index], sizeof(HsvPackageStructure));
        RetVal = err_Ok;
    }

    return RetVal;
}

FResult CHsvDvbsInstallation_mpackageparser_Priv::ipackage_GetPackageByKey (HsvPackageStructure   *Package)
{
    FResult RetVal  =   err_BadParameter;
    int     Count = 0;

    if (NumPackagesFound)
    {
        for (Count = 0; Count < NumPackagesFound; Count++)
        {
            if (FoundPackageList[Count].PackageId == Package->PackageId)
            {
      //          TraceDebug (m, " GetPackageByKey: Found Matching PackageId %d ",FoundPackageList[Count].PackageId);
                memcpy (Package, &FoundPackageList[Count], sizeof(HsvPackageStructure));
                RetVal = err_Ok;
            }
        }
    }

    return RetVal;
}

/* Get the package group name for given package ID */
FResult CHsvDvbsInstallation_mpackageparser_Priv::ipackage_GetPackageGroupId (Nat32 PackageID, Nat16 *PackageGroupId)
{
	FResult		RetVal = err_BadParameter;
	int			Count = 0, InnerLoop = 0;

	if (PackageGroupId)
	{
		mBuildPackageSatelliteList ();
		*PackageGroupId = 0;

		/*remove Bouquet ID from the package ID, for dynamic package ,
		**package ID is combination of BAT ID and package id
		*/
		PackageID = PackageID & 0xFFFF;
		for (Count = 0; Count < TotalPackageGroups; Count++)
		{
			for (InnerLoop = 0; InnerLoop < MAX_PACKAGEID_PER_GROUP; InnerLoop++)
			{
				if (DefaultPackageGroup[Count].PackageId[InnerLoop] == PackageID)
				{
					*PackageGroupId = DefaultPackageGroup[Count].PackageGroupId;
					RetVal = err_Ok;
					break;
				}
			}
			if (InnerLoop < MAX_PACKAGEID_PER_GROUP)
			{
				break;
			}
		}
	}

	return RetVal;
}

/* Get the package group name for given package ID */
FResult CHsvDvbsInstallation_mpackageparser_Priv::ipackage_GetPackageGroupName (Nat32 PackageGroupId, Nat16 *PackageGroupName)
{
    FResult RetVal = err_BadParameter;
    int Count = 0;

    if (PackageGroupName)
    {
        mBuildPackageSatelliteList ();

        if (FIND_FRANSAT_PACKAGE(PackageGroupId) || IS_OPERATOR_PROFILE (PackageGroupId))
        {
            /* For fransat, Packegeid = FRANSAT_PACKAGE_ID | Fsat-Bouquetids */
            for (Count = 0; Count < NumPackagesFound; Count++)
            {
                if (PackageGroupId == FoundPackageList[Count].PackageId)
                {
                    memcpy (PackageGroupName, FoundPackageList[Count].PackageListName, (sizeof(Nat16) * MAX_PACKAGELIST_NAME_LEN));
                    RetVal = err_Ok;
                    break;
                }
            }
        }
        else
        {
            for (Count = 0; Count < TotalPackages; Count++)
            {
                if (PackageGroupId == DefaultPackageList[Count].PackageIndex)
                {
                    memcpy (PackageGroupName, DefaultPackageList[Count].PackageListName, (sizeof(Nat16) * MAX_PACKAGELIST_NAME_LEN));
                    RetVal = err_Ok;
                    break;
                }
            }
        }
    }
    return RetVal;
}

void CHsvDvbsInstallation_mpackageparser_Priv::ipackage_LoadPackageGroupInfo (void)
{
	mBuildPackageSatelliteList ();
}

void CHsvDvbsInstallation_mpackageparser_Priv::ipackage_SetPackageParserXmlString (char *InputString, int PackageParserXmlStringLen)
{
	mBuildPackageSatelliteList ();
}

void CHsvDvbsInstallation_mpackageparser_Priv::ipackageparserctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    if((ipackageparserctrlN_DataNotAvailable == eventid) || (ipackageparserctrlN_DataAvailable == eventid)){
    	/* This msg calls FuncPkgParseStopCollection */
    	pmp_PmpSend(mPkgBldPump, EvPkgParseDataAcqComplete, (Nat32)0);
    }
}
void CHsvDvbsInstallation_mpackageparser_Priv::ipackageparsersatfrontendN_OnBlindScanEnd ()
{
}

//ICesOperatorProfileNotify
void CHsvDvbsInstallation_mpackageparser_Priv::opinsN_OnOpSearchStatus (Op_ProfileSearchStatus opStatus)
{
    //Do nothing
}

void CHsvDvbsInstallation_mpackageparser_Priv::opinsN_OnOpStatusInfo(Op_ProfileStatusInfo StatusInfo)
{
    TraceNotice  (m, "%s() : IN", __FUNCTION__);
    mOpProfileStatusInfo    = StatusInfo;
}

void CHsvDvbsInstallation_mpackageparser_Priv::opinsN_OnOpNIT(Op_ProfileNitData nitData)
{
     // Do nothing
}

void CHsvDvbsInstallation_mpackageparser_Priv::opinsN_OnOpTune(Op_ProfileTuneData tuneData)
{
     // Do nothing
}

//ICesCipCAMStatusNotify
void CHsvDvbsInstallation_mpackageparser_Priv::cipStatusN_OnEvent (CIPlusStatus_e status)
{
//    TraceNotice  (m, "%s() : status %d \n", __FUNCTION__, status);
    
    mDynamicCIPlusStatus = status;
#if 0
    if (Status_Inactive == status)
    {
        TraceNotice  (m, "%s() : Clearing cached OpStatusInfo\n", __FUNCTION__);
        mInitOpProfileStatusInfo ();
    }
#endif    
}
