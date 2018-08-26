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
 *	Cpp Source:		hsvdvbstricolor_msettings.cpp
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	 sutendra %
 *	%date_created:	 Tue Mar 17 11:07:36 2015%
**********************************************************************/

#include "_hsvdvbstricolor_msettings.h"


TRACESYMBOL(m, "s2/hsvdvbstricolor/hsvdvbstricolor_msettings")


/*define the persistent and current data*/
HsvTricolorRegionNameStore CHsvDvbsTricolor_msettings_Priv::s__HsvTricolorCurrentRegionNameData;
HsvTricolorRegionNameStore CHsvDvbsTricolor_msettings_Priv::s__HsvTricolorPersistentRegionNameData;
HsvTricolorRegionNameStore CHsvDvbsTricolor_msettings_Priv::s__HsvTricolorDefaultRegionNameData;


	
/****************************************************************************
 * Static functions
 ****************************************************************************/

Bool CHsvDvbsTricolor_msettings_Priv::LoadDataFromPersistentFile (void)
{
	FILE *	fp = NULL;
	Bool	bCheckFlag = FALSE;

    fp = fopen(TRICOLOR_REGION_NAME_STORE_FILE_PATH, "r" );
	
    if(fp != NULL)
    {	
        Nat32  Crc = 0;

        fread (&HsvTricolorPersistentRegionNameData,sizeof(HsvTricolorPersistentRegionNameData),1,fp);
        Crc = HsvTricolorPersistentRegionNameData.Crc;
        	  HsvTricolorPersistentRegionNameData.Crc = 0;
        	  HsvTricolorPersistentRegionNameData.Crc = CalculateCrc32(&HsvTricolorPersistentRegionNameData, sizeof(HsvTricolorPersistentRegionNameData));

		/**Traces**/

		TraceNotice(m,"CRC read from File %d, CRC Generated %d",Crc,HsvTricolorPersistentRegionNameData.Crc);

		TraceNotice(m,"[%s] [%d] [%d]",HsvTricolorPersistentRegionNameData.regionNameData.regionName\
			 						   ,HsvTricolorPersistentRegionNameData.regionNameData.regionNameLength);
			 						   
		



        if ( Crc == HsvTricolorPersistentRegionNameData.Crc &&
                HsvTricolorPersistentRegionNameData.RecordSize == sizeof( HsvTricolorPersistentRegionNameData )&&
                HsvTricolorPersistentRegionNameData.PrimaryVersion == PRIMARY_VERSION &&
                HsvTricolorPersistentRegionNameData.SecondaryVersion == SECONDARY_VERSION )
        {
            bCheckFlag = TRUE;
            memmove(&HsvTricolorCurrentRegionNameData,&HsvTricolorPersistentRegionNameData,sizeof(HsvTricolorPersistentRegionNameData));		
        }
        fclose(fp);
        TraceNotice(m, "%s Region Name Set %s ", __FUNCTION__, HsvTricolorCurrentRegionNameData.regionNameData.regionName);
       
    }
	else
	{
		TraceNotice (m,"Line %d Tricolor settings File open failed",__LINE__);
	}
    return bCheckFlag;

}

Nat32 CHsvDvbsTricolor_msettings_Priv::CalculateCrc32( void* buffer, int size )
{
    /* http://www.cl.cam.ac.uk/Research/SRG/bluebook/21/crc/crc.html */
    Nat32 Result = 0xFFFFFFFF;
    int   i = 0;
    int   j = 0;
    Nat8  Octet = 0;
    Nat8 *Buf   = (Nat8*)buffer;
    
    for ( i = 0; i < size; i++ )
    {
        Octet = *Buf++;
        for ( j = 0; j < 8; j++ )
        {
            Result = ( Result << 1 );
            if ( ( Octet >> 7 ) ^ ( Result >> 31 ) )
            {
                Result ^= 0x04C11DB7;
            }
            Octet <<= 1;
        }
    }
    
    return ~Result;             /* The complement of the remainder */
}

/****************************************************************************
 * External functions
 ****************************************************************************/

/* provides IHsvPower idvbsetpow */

void CHsvDvbsTricolor_msettings_Priv::idvbsetpow_TurnOn (void)
{
	TraceNotice (m," Entering function Tricolor - %s",__FUNCTION__);
	
	Bool	bCheckFlag = FALSE;

	memset(&HsvTricolorDefaultRegionNameData,0x00,sizeof(HsvTricolorDefaultRegionNameData));
	
	bCheckFlag = LoadDataFromPersistentFile ();

	TraceNotice(m,"Data loaded from persistant memory, CRC %d",bCheckFlag);
	
	if ( !bCheckFlag )
	{
		memmove(&s__HsvTricolorPersistentRegionNameData,&s__HsvTricolorDefaultRegionNameData,sizeof(HsvTricolorRegionNameStore));
		memmove(&s__HsvTricolorCurrentRegionNameData,&s__HsvTricolorPersistentRegionNameData,sizeof(HsvTricolorRegionNameStore));
	}
}

/* provides IHsvSatelliteSettings	idvbset	*/



void CHsvDvbsTricolor_msettings_Priv::idvbset_SaveSatelliteSettingsToPersistent (void)
{
	memmove (&HsvTricolorPersistentRegionNameData.regionNameData.regionName,&HsvTricolorCurrentRegionNameData.regionNameData.regionName,sizeof(HsvTricolorCurrentRegionNameData.regionNameData.regionName));
	HsvTricolorPersistentRegionNameData.regionNameData.regionNameLength = HsvTricolorCurrentRegionNameData.regionNameData.regionNameLength;
	
}

FResult CHsvDvbsTricolor_msettings_Priv::idvbset_CommitSatelliteSettingsToPersistent (void)
{
	FResult		RetVal = err_Ok;
	FILE*		fp = NULL;

	fp = fopen(TRICOLOR_REGION_NAME_STORE_FILE_PATH, "w+" );

	if ( fp != NULL )
	{
		HsvTricolorPersistentRegionNameData.RecordSize = sizeof(HsvTricolorPersistentRegionNameData);
		HsvTricolorPersistentRegionNameData.PrimaryVersion = PRIMARY_VERSION;
		HsvTricolorPersistentRegionNameData.SecondaryVersion = SECONDARY_VERSION;
		HsvTricolorPersistentRegionNameData.Crc = 0;
		HsvTricolorPersistentRegionNameData.Crc = CalculateCrc32(&HsvTricolorPersistentRegionNameData, sizeof(HsvTricolorPersistentRegionNameData));	
		fwrite ( &HsvTricolorPersistentRegionNameData,sizeof(HsvTricolorPersistentRegionNameData),1,fp);	
		fclose (fp);
	}	
	else
	{
		RetVal = err_FileError;
	}
	return RetVal;
}

Nat32 CHsvDvbsTricolor_msettings_Priv::idvbset_GetAttribute(int AttributeId)
{
	FResult RetVal = 0;
	HsvTricolorRegionNameData *Data = NULL;

	
	if (AttributeId == idvbset_AttributeTricolorRegionNameData)
	{
		if(HsvTricolorCurrentRegionNameData.regionNameData.regionNameLength > 0)
		{
			Data = (HsvTricolorRegionNameData*)malloc(sizeof(HsvTricolorRegionNameData));

			/*TraceNotice(m,"[%s] [%d] [%p]",HsvTricolorCurrentRegionNameData.regionNameData.regionName,\
								  HsvTricolorCurrentRegionNameData.regionNameData.regionNameLength,\
								  Data);*/

			memset(Data,0x00,sizeof(HsvTricolorRegionNameData));
			
			memcpy(Data->regionName,&HsvTricolorCurrentRegionNameData.regionNameData.regionName,sizeof(HsvTricolorCurrentRegionNameData.regionNameData.regionName));
    		Data->regionNameLength = HsvTricolorCurrentRegionNameData.regionNameData.regionNameLength;
    		

			RetVal = (Nat32)Data;
		}
		else
		{
			TraceNotice(m,"RegionName Empty!!!!");
		}
	}
	else
	{
		TraceNotice(m,"Invalid Attribute !!!");
	}

	//TraceNotice(m,"%s Attribute id: %d regionname %s\n",__FUNCTION__,AttributeId,Data->regionName);
	return RetVal;
}



FResult CHsvDvbsTricolor_msettings_Priv::idvbset_SetAttribute(int AttributeId,Nat32 Data)
{
	FResult RetVal = err_BadParameter;

//	HsvTricolorRegionNameData tempStruct;
	HsvTricolorRegionNameData *tempData;

	tempData = (HsvTricolorRegionNameData*)Data;
	//TraceNotice(m,"RegionNameLength %d %p, %p",tempData->regionNameLength,&tempData->regionNameLength, tempData);
	
	if (AttributeId == idvbset_AttributeTricolorRegionNameData)
	{
		memcpy(&HsvTricolorCurrentRegionNameData.regionNameData.regionName,tempData->regionName,sizeof(HsvTricolorCurrentRegionNameData.regionNameData.regionName));
	    HsvTricolorCurrentRegionNameData.regionNameData.regionNameLength =  tempData->regionNameLength;
		RetVal = err_Ok;
	    
	}
	else
	{
		TraceNotice(m,"Invalid Attribute !!!");
	}

	TraceNotice(m,"%s Attribute id: %d regionname %s %d\n",__FUNCTION__,AttributeId,HsvTricolorCurrentRegionNameData.regionNameData.regionName,\
																					HsvTricolorCurrentRegionNameData.regionNameData.regionNameLength);
	return RetVal;
}



/**************************************************Stub Functions***********************************************************/

/* provides IHsvPower idvbsetpow */

void CHsvDvbsTricolor_msettings_Priv::idvbsetpow_Init (void)
{

}
void CHsvDvbsTricolor_msettings_Priv::idvbsetpow_TurnOff (void)
{

}

/* provides IHsvSatelliteSettings	idvbset	*/


FResult CHsvDvbsTricolor_msettings_Priv::idvbset_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
 TraceNotice (m, "Error!!! SetPostcode-Should not land here");
 return err_Ok;
}

FResult CHsvDvbsTricolor_msettings_Priv::idvbset_GetPostcode(Nat8 *PostcodeLen,Nat8 *Postcode)
{
 TraceNotice (m, "Error!!! GetPostcode-Should not land here");	 
 return err_Ok;
}

void CHsvDvbsTricolor_msettings_Priv::idvbset_LoadLnbParametersFromPersistent (void)
{

}
void CHsvDvbsTricolor_msettings_Priv::idvbset_ReLoadLnbParametersFromPersistent (void)
{

}
FResult CHsvDvbsTricolor_msettings_Priv::idvbset_GetLnbSettings (HsvLnbSettings *LnbSettings)
{
	TraceNotice (m, "Error!!! GetPostcode-Should not land here");	 
 return err_Ok;
}
FResult CHsvDvbsTricolor_msettings_Priv::idvbset_SetLnbSettings (HsvLnbSettings *LnbSettings)
{
	TraceNotice (m, "Error!!! GetPostcode-Should not land here");	 
 	return err_Ok;
}
FResult CHsvDvbsTricolor_msettings_Priv::idvbset_ResetLnbSettings (void)
{
	TraceNotice (m, "Error!!! GetPostcode-Should not land here");	 
 	return err_Ok;
}
FResult CHsvDvbsTricolor_msettings_Priv::idvbset_GetDefaultValues (LnbSettingsEntry	*LnbSettingsEntry)
{
	TraceNotice (m, "Error!!! GetPostcode-Should not land here");	 
	return err_Ok;
}
FResult CHsvDvbsTricolor_msettings_Priv::idvbset_ResetToDefaultLnbSettings (void)
{
	TraceNotice (m, "Error!!! GetPostcode-Should not land here");	 
	return err_Ok;
}
			