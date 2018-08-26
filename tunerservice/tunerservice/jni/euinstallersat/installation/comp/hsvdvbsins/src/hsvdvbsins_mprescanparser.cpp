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
 *   C Source:       hsvdvbsins_mprescanparser.c
 *   Instance:       
 *   Description:    
 *   %created_by:     smirajkar %
 *   %date_created:   Thu Jan 03 14:47:04 2013 %
 *
**********************************************************************/

#include "_hsvdvbsins_mprescanparser.h"




TRACESYMBOL(m, "s2/installation/hsvdvbsins_mprescanparser")

/****************************************************************************
 * Macros and types
 ****************************************************************************/











int CHsvDvbsInstallation_mprescanparser_Priv::s__mCurrentSatelliteIndex;
 
int CHsvDvbsInstallation_mprescanparser_Priv::s__mTotalNumSatellites;

HsvSatelliteList CHsvDvbsInstallation_mprescanparser_Priv::s__mSatellitePreScanList[MAX_NUM_OF_PRESCAN_ENTRIES] = 
{
#include "PrescanTable.h"
};

HsvSatelliteList CHsvDvbsInstallation_mprescanparser_Priv::s__mSatelliteCountryPreScanList[MAX_NUM_OF_PRESCAN_ENTRIES];





HsvSatelliteMapping CHsvDvbsInstallation_mprescanparser_Priv::s__mSatelliteMapping[MAX_NUM_OF_SATELLITES] = 
{
#include "SatelliteMappingTable.h"
};

const char SatelliteNameArray[MAX_NUM_OF_SATELLITES][MAX_SATELLITE_NAME_LEN] = {
"ASTRA 19.2E",
"HOTBIRD 13E",
"ASTRA 23.5E",
"ASTRA 28.2E",
"TURKSAT 42E",
"EUTELSAT W3A 7E",
"THOR 1W",
"EUTELSAT W3A 7E MDU4",
"EUTELSAT W3A 7E MDU5" ,
"EUTELSAT W3A 7E MDU3" ,
"EUTELSAT W3A 7E MDU2" ,
"EUTELSAT W3A 7E MDU1" ,
"EUTELSAT W4 36E" ,
"EUTELSAT 5WA",
"EUTELSAT 9A",
"Sat",
} ;


Bool CHsvDvbsInstallation_mprescanparser_Priv::s__PreScanListFound = FALSE;

Bool CHsvDvbsInstallation_mprescanparser_Priv::s__CountryDependantTablePopulated = FALSE;


/****************************************************************************
 * Static functions
 ****************************************************************************/


/****************************************************************************
 * External functions
 ****************************************************************************/


Bool CHsvDvbsInstallation_mprescanparser_Priv::iprescanparser_GetSatelliteEntryFromPreScanTable(int index, HsvSatelliteList *PreScanTableSatellite)
{
    Bool retval = FALSE;
    
    if(index < TOTAL_NUM_OF_PRESCANENTRIES)
    {
    	if(CountryDependantTablePopulated == TRUE)
    	{
        	*PreScanTableSatellite = mSatelliteCountryPreScanList[index];
    	}
		else
		{
			*PreScanTableSatellite = mSatellitePreScanList[index];
		}
        retval = TRUE;
    }
    return retval;
}

/* Converting the Satellite Information from XML to Binary Tables */
Bool CHsvDvbsInstallation_mprescanparser_Priv::iprescanparser_ExtractPreScanTableFromXml(void)
{
    Bool    retval = FALSE;
    int     NumPreScanEntries = 0;
	int		NumSatellites = 0;
    char    TempString[MAX_ENTRY_LEN], OutputString[MAX_ENTRY_LEN];
    
	if (PreScanListFound == FALSE) {
		CURRENT_SATELLITE_INDEX = 0;
		TOTAL_NUM_OF_SATELLITES = NUM_SATELLITES_IN_CURRENT_PRESCAN;
		for (CURRENT_SATELLITE_INDEX = 0; CURRENT_SATELLITE_INDEX < TOTAL_NUM_OF_SATELLITES; CURRENT_SATELLITE_INDEX++)
		{			 
			
			memset(mSatelliteMapping[CURRENT_SATELLITE_INDEX].SatelliteName,0x00,MAX_SATELLITE_NAME_LEN * 2);
			charsetutil_MbToWc((Nat8*)SatelliteNameArray[CURRENT_SATELLITE_INDEX], strlen(SatelliteNameArray[CURRENT_SATELLITE_INDEX]), mSatelliteMapping[CURRENT_SATELLITE_INDEX].SatelliteName, MAX_SATELLITE_NAME_LEN, FALSE);			
		/*	
			TraceDebug (m, "PrescanParser: Index %d SatelliteId %d SatelliteName %s OrbPos %d EWFlag %d",CURRENT_SATELLITE_INDEX, mSatelliteMapping[CURRENT_SATELLITE_INDEX].SatelliteId, \
													SatelliteNameArray[CURRENT_SATELLITE_INDEX], mSatelliteMapping[CURRENT_SATELLITE_INDEX].OrbitalPosition,mSatelliteMapping[CURRENT_SATELLITE_INDEX].EastWestFlag);
			*/		
		}
	
		TOTAL_NUM_OF_PRESCANENTRIES = MAX_NUM_OF_PRESCAN_ENTRIES;
		
		PreScanListFound = TRUE;
		retval = TRUE;
		
	} else if(PreScanListFound == TRUE)
	{
		retval = TRUE;
	}
				
    return retval;
}

Bool CHsvDvbsInstallation_mprescanparser_Priv::IsCountryDependantTableRequired(int country, int* region)
{
	Bool retval = FALSE;

	switch(country)
	{
		case cids_CountryTurkey:
			*region = REGION_TURKEY;
			retval = TRUE;
			break;
		case cids_CountryFrance:
			*region = REGION_FRANCE;
			retval = TRUE;
			break;			
		case cids_CountryRussia:
			*region = REGION_RUSSIA;
			retval = TRUE;
			break;			
		case cids_CountryDenmark:
		case cids_CountryFinland:
		case cids_CountryNorway:
		case cids_CountrySweden:
			*region = REGION_NORDIG;
			retval = TRUE;
			break;
		case cids_CountryPoland:
			*region = REGION_POLAND;
			retval = TRUE;
			break;
		case cids_CountryHungary:
			*region = REGION_HUNGARY;
			retval = TRUE;
			break;
		case cids_CountryUK:
			*region = REGION_UK;
			retval = TRUE;
			break;
		default:
			retval = FALSE;
			break;
	}

	TraceNotice(m,"%s: %d country [%d] retval [%d]",__FUNCTION__,__LINE__,country,retval);
	return retval;
	
}

Bool CHsvDvbsInstallation_mprescanparser_Priv::iprescanparser_PopulateCountryDependantTable(int country)
{
	int Region;
	if(IsCountryDependantTableRequired(country, &Region) == TRUE)
	{
		int CurrentIndex = 0;

		TraceNotice(m,"Region: %d", Region);
		
		/*populate country specific entries*/
		for(int i = 0; i < TOTAL_NUM_OF_PRESCANENTRIES ; i++)
		{
			if(mSatellitePreScanList[i].PreferredRegion == Region)
			{
				memcpy(&mSatelliteCountryPreScanList[CurrentIndex],&mSatellitePreScanList[i],sizeof(HsvSatelliteList));
				TraceNotice(m,"%d index: [%d] Sat id [%d] Freq [%d]",__LINE__,CurrentIndex,mSatelliteCountryPreScanList[CurrentIndex].SatelliteId,mSatelliteCountryPreScanList[CurrentIndex].PrescanFrequency);
				CurrentIndex ++;

			}
		}

		/*populate non country specific entries*/
		for(int i = 0; i <TOTAL_NUM_OF_PRESCANENTRIES ; i++)
		{
			if(mSatellitePreScanList[i].PreferredRegion != Region)
			{
				memcpy(&mSatelliteCountryPreScanList[CurrentIndex],&mSatellitePreScanList[i],sizeof(HsvSatelliteList));
				//TraceNotice(m,"%d index: [%d] Sat id [%d] Freq [%d]",__LINE__,CurrentIndex,mSatelliteCountryPreScanList[CurrentIndex].SatelliteId,mSatelliteCountryPreScanList[CurrentIndex].PrescanFrequency);
				CurrentIndex ++;

			}
		}


		CountryDependantTablePopulated = TRUE;
	}
	else
	{
		TraceNotice(m, "Country dependant table is not required for country [%d]",country);
		CountryDependantTablePopulated = FALSE;
	}

	return CountryDependantTablePopulated;
	
}



int CHsvDvbsInstallation_mprescanparser_Priv::iprescanparser_GetNumberOfPrescanEntries (void)
{
    return  TOTAL_NUM_OF_PRESCANENTRIES;
}


/* Once valid satellite is identified, getting the satellite attributes. SatelliteId has to be passed */
Bool CHsvDvbsInstallation_mprescanparser_Priv::iprescanparser_GetSatelliteAttributeById (HsvSatelliteMapping *SatelliteAttribute)
{
	Bool	RetVal = FALSE;
	int		Count;

	if (SatelliteAttribute)
	{
		for (Count = 0; Count < TOTAL_NUM_OF_SATELLITES; Count++)
		{		
			if (SatelliteAttribute->SatelliteId == mSatelliteMapping[Count].SatelliteId)
			{
				memcpy (SatelliteAttribute, &mSatelliteMapping[Count], sizeof(HsvSatelliteMapping));
					
				RetVal = TRUE;
				break;
			}
		}
	}

	return RetVal;
}

/* This will return the satellite details on passing the orbital position + EW Flag */
Bool CHsvDvbsInstallation_mprescanparser_Priv::iprescanparser_GetSatelliteAttributeByPosition (HsvSatelliteMapping *SatelliteAttribute)
{
	int		Count;
	Bool	RetVal = FALSE;

	if (SatelliteAttribute)
	{
		TraceNotice (m, "TotalNum Sat %d ", TOTAL_NUM_OF_SATELLITES);
		for (Count = 0; Count < TOTAL_NUM_OF_SATELLITES; Count++)
		{
			TraceDebug (m , " Req %d %d Cur %d %d ", SatelliteAttribute->OrbitalPosition, SatelliteAttribute->EastWestFlag,\
							mSatelliteMapping[Count].OrbitalPosition, SatelliteAttribute->EastWestFlag , mSatelliteMapping[Count].EastWestFlag);
			if ((SatelliteAttribute->OrbitalPosition == mSatelliteMapping[Count].OrbitalPosition) &&
				(SatelliteAttribute->EastWestFlag == mSatelliteMapping[Count].EastWestFlag))
			{
				memcpy (SatelliteAttribute, &mSatelliteMapping[Count], sizeof(HsvSatelliteMapping));
				RetVal = TRUE;
				break;
			}
		}
	}

	return RetVal;
}

void CHsvDvbsInstallation_mprescanparser_Priv::iprescanparser_SetPrescanParserXmlString (char *InputString, int PrescanXmlStringLen)
{
	TraceNotice (m, "Warning!! Obselete API SetPrescanParserXmlString called from S2Installer ");
	return;
}
