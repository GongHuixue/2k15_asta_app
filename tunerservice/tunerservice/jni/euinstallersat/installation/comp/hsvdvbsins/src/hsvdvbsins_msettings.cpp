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
 *	C Source:		hsvdvbsins_msettings.c
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	 anuma %
 *	%date_created:	 Fri May 10 18:09:36 2013 %
**********************************************************************/

#include "_hsvdvbsins_msettings.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsins_msettings")
/****************************************************************************
 * Macros and types
 ****************************************************************************/

/* ANEESH: Pending in this file for DELTA
1. Changed needed for MDU and UniCable
2. Option to set the Package Id
*/




int CHsvDvbsInstallation_msettings_Priv::s__AssetManager = 0;

/*define the persistent and current data*/
HsvSatInstallationSettings CHsvDvbsInstallation_msettings_Priv::s__HsvsatInsSetCurrentData,CHsvDvbsInstallation_msettings_Priv::s__HsvsatInsSetPersistentData,CHsvDvbsInstallation_msettings_Priv::s__HsvsatInsSetDefaultData;



int CHsvDvbsInstallation_msettings_Priv::s__NordigUnicableUBF[UnicableUserBandMax] =  {
	1210000,
	1420000,
	1680000,
	2040000,
	1484000,
	1586000,
	1688000,
	1790000};

	
/****************************************************************************
 * Static functions
 ****************************************************************************/







void CHsvDvbsInstallation_msettings_Priv::Loaddefaultdata (void)
{
	int		TempVal = 0, Count = 0;
	memset(&HsvsatInsSetDefaultData,0x00,sizeof(HsvsatInsSetDefaultData));


	s2div_LoadDefaultConnectionType (sysset_GetSystemCountry(), &TempVal);
	HsvsatInsSetDefaultData.HsvLnbset.ConnectionType = (HsvLnbConnectionType)TempVal;
	s2div_LoadDefaultLnbType (sysset_GetSystemCountry(), &TempVal);
	for (Count = 0; Count < MAX_LNB_SUPPORTED; Count++)
	{
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].LnbType = (HsvLnbType)TempVal;
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].LowLoFreq = UNIVERSAL_LOW_LO_FREQ;
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].HighLoFreq = UNIVERSAL_HIGH_LO_FREQ;
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].ToneControl = UNIVERSAL_TONE_DEFLT;
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].LnbPower = UNIVERSAL_POW_DEFLT;
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].UserBand = 0;
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].UserBandFrequency = (ISNORDIGCOUNTRY(sysset_GetSystemCountry()) ? NordigUnicableUBF[0] : 0);
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].UpdateInstallEnabled = FALSE;
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].SatelliteId = 0;
		HsvsatInsSetDefaultData.HsvLnbset.LnbSettings[Count].LnbStatus = LnbFree;
	}

	HsvsatInsSetDefaultData.PackageId = 0;	/* No Sorting */
	HsvsatInsSetDefaultData.PackageOnly = FALSE;
	HsvsatInsSetDefaultData.Frequency = 0;
	HsvsatInsSetDefaultData.Polarization = 1;
	HsvsatInsSetDefaultData.SymbolRate = 0;
}

Bool CHsvDvbsInstallation_msettings_Priv::LoadDataFromPersistentFile (void)
{
	FILE *	fp = NULL;
	Bool	bCheckFlag = FALSE;

    fp = fopen(INSTALL_SETTING_FILE_PATH, "r" );
    if ( fp != NULL )
    {	
        Nat32  Crc = 0;

        fread (&HsvsatInsSetPersistentData,sizeof(HsvsatInsSetPersistentData),1,fp);
        Crc = HsvsatInsSetPersistentData.Footer.Crc;
        HsvsatInsSetPersistentData.Footer.Crc = 0;
        HsvsatInsSetPersistentData.Footer.Crc = CalculateCrc32(&HsvsatInsSetPersistentData, sizeof(HsvsatInsSetPersistentData));

        if ( Crc == HsvsatInsSetPersistentData.Footer.Crc &&
                HsvsatInsSetPersistentData.Header.RecordSize == sizeof( HsvsatInsSetPersistentData )&&
                HsvsatInsSetPersistentData.Header.PrimaryVersion == PRIMARY_VERSION &&
                HsvsatInsSetPersistentData.Header.SecondaryVersion == SECONDARY_VERSION )
        {
            bCheckFlag = TRUE;
            memmove(&HsvsatInsSetCurrentData,&HsvsatInsSetPersistentData,sizeof(HsvsatInsSetPersistentData));		
        }
        fclose(fp);
        TraceNotice(m, "%s PackageId set %d ", __FUNCTION__, HsvsatInsSetPersistentData.PackageId);
        insN_OnEvent(insN_EventPackageId, HsvsatInsSetPersistentData.PackageId);
    }

    return bCheckFlag;
}

Nat32 CHsvDvbsInstallation_msettings_Priv::CalculateCrc32( void* buffer, int size )
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

Bool CHsvDvbsInstallation_msettings_Priv::IsPersistentFilePresent (void)
{
	Bool PersistentFilePresent = FALSE;
	struct stat statbuf;

		
	if ((stat(INSTALL_SETTING_FILE_PATH, &statbuf) != -1) && (statbuf.st_size != 0))
	{
		PersistentFilePresent = TRUE;
	}

	TraceNotice (m, "PersistentFile status %d ", PersistentFilePresent);
	return PersistentFilePresent;
}
/****************************************************************************
 * External functions
 ****************************************************************************/

/* provides IHsvPower idvbsetpow */

void CHsvDvbsInstallation_msettings_Priv::idvbsetpow_Init (void)
{

}

void CHsvDvbsInstallation_msettings_Priv::idvbsetpow_TurnOff (void)
{

}

void CHsvDvbsInstallation_msettings_Priv::idvbsetpow_TurnOn (void)
{
	Bool	bCheckFlag = FALSE;
	struct stat statbuf;
	FILE* fp;

		
	if (stat(INSTALL_SETTING_FILE_PATH, &statbuf) == -1)
	{
		fp = fopen(INSTALL_SETTING_FILE_PATH, "w+" );
		fclose(fp);
		TraceNotice(m,"%s: %d :File is created",__FUNCTION__,__LINE__);
	}

	/*ownership need to be changed if file is created by older SW also*/
	if(chown(INSTALL_SETTING_FILE_PATH,-1,AID_USER_SETTING) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chown: %d",__FUNCTION__,__LINE__);
	}
	if(chmod(INSTALL_SETTING_FILE_PATH, (S_IRWXU | S_IRWXG )) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chmod : %d",__FUNCTION__,__LINE__);
	}
		

	Loaddefaultdata ();
	
    if (apsysset_GetVirginBit() == FALSE)
    {
        bCheckFlag = LoadDataFromPersistentFile ();
    }
	
	if ( !bCheckFlag )
	{	
		memmove ( &HsvsatInsSetPersistentData,&HsvsatInsSetDefaultData,sizeof(HsvsatInsSetDefaultData));
		memmove(&HsvsatInsSetCurrentData,&HsvsatInsSetPersistentData,sizeof(HsvsatInsSetPersistentData));
	}
}


/* provides IHsvSatelliteSettings	idvbset	*/

void CHsvDvbsInstallation_msettings_Priv::idvbset_LoadLnbParametersFromPersistent (void)
{
	memmove ( &HsvsatInsSetCurrentData.HsvLnbset,&HsvsatInsSetPersistentData.HsvLnbset,sizeof(HsvsatInsSetPersistentData.HsvLnbset));
	HsvsatInsSetCurrentData.PackageId = HsvsatInsSetPersistentData.PackageId;
	HsvsatInsSetCurrentData.PackageOnly = HsvsatInsSetPersistentData.PackageOnly;
	HsvsatInsSetCurrentData.Frequency = HsvsatInsSetPersistentData.Frequency;
	HsvsatInsSetCurrentData.Polarization = HsvsatInsSetPersistentData.Polarization;
	HsvsatInsSetCurrentData.SymbolRate = HsvsatInsSetPersistentData.SymbolRate;
	HsvsatInsSetCurrentData.SymbolRateMode = HsvsatInsSetPersistentData.SymbolRateMode;
}

void CHsvDvbsInstallation_msettings_Priv::idvbset_ReLoadLnbParametersFromPersistent (void)
{
    /* If the file is not present. Load default */
    Loaddefaultdata ();
    LoadDataFromPersistentFile ();
}

FResult CHsvDvbsInstallation_msettings_Priv::idvbset_GetLnbSettings (HsvLnbSettings *LnbSettings)
{
	int retval = err_BadParameter;
	
	if (LnbSettings)
	{
		memmove (LnbSettings,&HsvsatInsSetCurrentData.HsvLnbset,sizeof(HsvLnbSettings));
		retval = err_Ok;
	}
	
	return retval;
}

FResult CHsvDvbsInstallation_msettings_Priv::idvbset_SetLnbSettings (HsvLnbSettings *LnbSettings)
{
	int retval = err_BadParameter;

	if (LnbSettings)
	{	
		memmove ( &HsvsatInsSetCurrentData.HsvLnbset,LnbSettings,sizeof(HsvLnbSettings));
		retval = err_Ok;
	}
	return retval;
}


FResult CHsvDvbsInstallation_msettings_Priv::idvbset_ResetLnbSettings (void)
{
	FResult		RetVal = err_Ok;
	memmove ( &HsvsatInsSetCurrentData.HsvLnbset,&HsvsatInsSetPersistentData.HsvLnbset,sizeof(HsvsatInsSetPersistentData.HsvLnbset));
	HsvsatInsSetCurrentData.PackageId = HsvsatInsSetPersistentData.PackageId;
	HsvsatInsSetCurrentData.PackageOnly = HsvsatInsSetPersistentData.PackageOnly ;
	HsvsatInsSetCurrentData.Frequency = HsvsatInsSetPersistentData.Frequency;
	HsvsatInsSetCurrentData.Polarization = HsvsatInsSetPersistentData.Polarization;
	HsvsatInsSetCurrentData.SymbolRate = HsvsatInsSetPersistentData.SymbolRate;
	HsvsatInsSetCurrentData.SymbolRateMode = HsvsatInsSetPersistentData.SymbolRateMode;
	return RetVal;
}

void CHsvDvbsInstallation_msettings_Priv::idvbset_SaveSatelliteSettingsToPersistent (void)
{
	memmove ( &HsvsatInsSetPersistentData.HsvLnbset,&HsvsatInsSetCurrentData.HsvLnbset,sizeof(HsvsatInsSetPersistentData.HsvLnbset));
	HsvsatInsSetPersistentData.PackageId = HsvsatInsSetCurrentData.PackageId;
	HsvsatInsSetPersistentData.PackageOnly = HsvsatInsSetCurrentData.PackageOnly;
	HsvsatInsSetPersistentData.Frequency = HsvsatInsSetCurrentData.Frequency;
	HsvsatInsSetPersistentData.Polarization = HsvsatInsSetCurrentData.Polarization;
	HsvsatInsSetPersistentData.SymbolRate= HsvsatInsSetCurrentData.SymbolRate;
	HsvsatInsSetPersistentData.SymbolRateMode= HsvsatInsSetCurrentData.SymbolRateMode;

}

FResult CHsvDvbsInstallation_msettings_Priv::idvbset_CommitSatelliteSettingsToPersistent (void)
{
	FResult		RetVal = err_Ok;
	FILE*		fp = NULL;

	fp = fopen(INSTALL_SETTING_FILE_PATH, "w+" );

	if ( fp != NULL )
	{
		HsvsatInsSetPersistentData.Header.RecordSize = sizeof(HsvsatInsSetPersistentData);
		HsvsatInsSetPersistentData.Header.PrimaryVersion = PRIMARY_VERSION;
		HsvsatInsSetPersistentData.Header.SecondaryVersion = SECONDARY_VERSION;
		HsvsatInsSetPersistentData.Footer.Crc = 0;
		HsvsatInsSetPersistentData.Footer.Crc = CalculateCrc32(&HsvsatInsSetPersistentData, sizeof(HsvsatInsSetPersistentData));	
		fwrite ( &HsvsatInsSetPersistentData,sizeof(HsvsatInsSetPersistentData),1,fp);	
		fclose (fp);
	}	
	else
	{
		RetVal = err_FileError;
	}
	return RetVal;
}

FResult CHsvDvbsInstallation_msettings_Priv::idvbset_GetDefaultValues (LnbSettingsEntry	*LnbSettingsEntry)
{
	FResult RetVal = err_BadParameter;

	if (LnbSettingsEntry) 
	{
		switch (LnbSettingsEntry->LnbType)
		{
			case	LnbUniversal:
				LnbSettingsEntry->LowLoFreq = UNIVERSAL_LOW_LO_FREQ;
				LnbSettingsEntry->HighLoFreq = UNIVERSAL_HIGH_LO_FREQ;
				LnbSettingsEntry->ToneControl = UNIVERSAL_TONE_DEFLT;
				LnbSettingsEntry->LnbPower = UNIVERSAL_POW_DEFLT;
				LnbSettingsEntry->UserBand = 0;
				LnbSettingsEntry->UpdateInstallEnabled = FALSE;
				LnbSettingsEntry->SatelliteId = 0;
				LnbSettingsEntry->LnbStatus = LnbFree;
				LnbSettingsEntry->UserBandFrequency = (ISNORDIGCOUNTRY(sysset_GetSystemCountry()) ? NordigUnicableUBF[0] : 0);
				
				RetVal = err_Ok;
				break;

			case	LnbUnicable:
				LnbSettingsEntry->UserBandFrequency = ISNORDIGCOUNTRY(sysset_GetSystemCountry()) ? NordigUnicableUBF[LnbSettingsEntry->UserBand] : 0;
				LnbSettingsEntry->LowLoFreq = UNIVERSAL_LOW_LO_FREQ;
				LnbSettingsEntry->HighLoFreq = UNIVERSAL_HIGH_LO_FREQ;
				break;				
            default:
                break;
		}
	}
	/* ANEESH: TODO: Add support for other LNBs also */

	return RetVal;
}
FResult CHsvDvbsInstallation_msettings_Priv::idvbset_ResetToDefaultLnbSettings (void)
{
	FResult RetVal = err_Ok;
	memmove (&HsvsatInsSetPersistentData,&HsvsatInsSetDefaultData,sizeof(HsvsatInsSetDefaultData));
	memmove(&HsvsatInsSetCurrentData,&HsvsatInsSetPersistentData,sizeof(HsvsatInsSetPersistentData));
	return RetVal;
}

Nat32 CHsvDvbsInstallation_msettings_Priv::idvbset_GetAttribute(int AttributeId)
{
	int		RetVal = 0;
	switch (AttributeId)
	{
	case	idvbset_AttributePackageId:
		RetVal = HsvsatInsSetCurrentData.PackageId;
		break;
	case	idvbset_AttributePackageOnly:
		RetVal = HsvsatInsSetCurrentData.PackageOnly;
		break;
	case	idvbset_AttributeAssetManager:
		RetVal = AssetManager;
		break;
	case	IHsvSatelliteSettings_AttributeFrequency:
		RetVal = HsvsatInsSetCurrentData.Frequency;
		break;
	case	IHsvSatelliteSettings_AttributePolarization:
		RetVal = HsvsatInsSetCurrentData.Polarization;
		break;
	case	IHsvSatelliteSettings_AttributeSymbolRate:
		RetVal = HsvsatInsSetCurrentData.SymbolRate;
	break;
	case	IHsvSatelliteSettings_AttributeSymbolRateMode:
		RetVal = HsvsatInsSetCurrentData.SymbolRateMode;
	break;

	default:
		break;
	}

	return RetVal;

	TraceNotice(m,"%s Attribute id: %d retval %d\n",__FUNCTION__,AttributeId,RetVal);
}

FResult CHsvDvbsInstallation_msettings_Priv::idvbset_SetAttribute(int AttributeId, Nat32 Value)
{
	FResult RetVal = err_BadParameter;
	switch (AttributeId)
	{
	case	idvbset_AttributePackageId:
		HsvsatInsSetCurrentData.PackageId = Value;
		RetVal = err_Ok;
		break;
	case	idvbset_AttributePackageOnly:
		HsvsatInsSetCurrentData.PackageOnly = Value;
		RetVal = err_Ok;
		break;
	case	IHsvSatelliteSettings_AttributeFrequency:
		HsvsatInsSetCurrentData.Frequency = Value;
		RetVal = err_Ok;
		break;
	case	IHsvSatelliteSettings_AttributePolarization:
		HsvsatInsSetCurrentData.Polarization = Value;
		RetVal = err_Ok;
		break;
	case	IHsvSatelliteSettings_AttributeSymbolRate:
		(HsvsatInsSetCurrentData.SymbolRateMode == SymbolRateModeAuto)?HsvsatInsSetCurrentData.SymbolRate = 0:HsvsatInsSetCurrentData.SymbolRate = Value;
		RetVal = err_Ok;
		break;
		case	IHsvSatelliteSettings_AttributeSymbolRateMode:
		HsvsatInsSetCurrentData.SymbolRateMode = Value;
		RetVal = err_Ok;
		break;
	case	idvbset_AttributeAssetManager:
		AssetManager = Value;
		break;
	default:
		break;
	}

	return RetVal;
}

FResult CHsvDvbsInstallation_msettings_Priv::idvbset_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! SetPostcode-Should not land here");
	  return err_Ok;
}

FResult CHsvDvbsInstallation_msettings_Priv::idvbset_GetPostcode(Nat8 *PostcodeLen,Nat8 *Postcode)
{
	  TraceNotice (m, "Error!!! GetPostcode-Should not land here");
	  return err_Ok;
}


/* provides  IHsvSatelliteInstallationRoute  insroute */
int CHsvDvbsInstallation_msettings_Priv::insroute_GetActiveScanInterface(void)
{
	return HsvsatInsSetCurrentData.PackageOnly;
}

Bool CHsvDvbsInstallation_msettings_Priv::insroute_SetActiveScanInterface(int ScanMode)
{
	Bool	RetVal = FALSE;

	switch (ScanMode)
	{
		case	insroute_ScanCompleteSatellite:
		case	insroute_ScanPackageOnly:
			HsvsatInsSetCurrentData.PackageOnly = ScanMode;
			RetVal = TRUE;
			break;
		default:
			break;
	}
	return RetVal;
}
void CHsvDvbsInstallation_msettings_Priv::sysnotifyN_Notify(int property,int value)
{
	
    if(property == IHsvSystemSettings_InstalledCountry)
    {
        TraceNotice (m,"Installed country changed to: %d",value);
        if ((apsysset_GetVirginBit() == TRUE) || (IsPersistentFilePresent() == FALSE))
        {
            Loaddefaultdata ();
            memmove ( &HsvsatInsSetPersistentData,&HsvsatInsSetDefaultData,sizeof(HsvsatInsSetDefaultData));
            memmove(&HsvsatInsSetCurrentData,&HsvsatInsSetPersistentData,sizeof(HsvsatInsSetPersistentData));
        }
    }

}
