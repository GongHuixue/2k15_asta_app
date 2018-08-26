/**********************************************************************
 *
 *   C Source:       hsvdvbtins_msettings.c
 *   Instance:       blr81mgr_1
 *   Description:    
 *   %created_by:    nareshj %
 *   %date_created:  Sat Apr 28 15:47:10 2012 %
 *
 **********************************************************************/
#include "_hsvdvbtins_msettings.h"
TRACESYMBOL(m, "dvb/installation/hsvdvbtins_msettings")


                                   /** koala type HsvDVBSettings **/

/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/






/****************************************************************************
 * Static variables
 ****************************************************************************/
/* NB: Currently just for Scan Mode later had to be extended to a structure
   if needed */ 
HsvDVBTSettings CHsvDvbTInstallation_msettings_Priv::s__mCurrentData;

HsvDVBTSettings CHsvDvbTInstallation_msettings_Priv::s__mDefaultData;

HsvDVBTSettings CHsvDvbTInstallation_msettings_Priv::s__mPersistentData;


/* Used for storage during Digital test reception */
char CHsvDvbTInstallation_msettings_Priv::s__mDirName[MAX_CHARACTERS];

char CHsvDvbTInstallation_msettings_Priv::s__mFileName[MAX_CHARACTERS];


/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

inline void CHsvDvbTInstallation_msettings_Priv::mAttributeCopy(HsvDVBTSettings* dest, HsvDVBTSettings* src, int attribute)
{
    switch(attribute)
    {
        case rins_AttributeScanMode:
            dest->ScanMode = src->ScanMode;
            break;

        case rins_AttributeNetworkId:
            dest->NetworkID = src->NetworkID;
            //TraceDebug(m,"%s %d tmp->NetworkID%d\n", __FUNCTION__, __LINE__, (int)dest->NetworkID);
            break;

        case rins_AttributePrimaryRegion:
            dest->PrimaryRegion = src->PrimaryRegion;
            //TraceDebug(m,"%s %d PrimaryRegion %d\n", __FUNCTION__, __LINE__, (int)dest->PrimaryRegion);
            break;

        case rins_AttributeSecondaryRegion:
            dest->SecondaryRegion = src->SecondaryRegion;
            //TraceDebug(m,"%s %d SecondaryRegion %d\n", __FUNCTION__, __LINE__, (int)dest->SecondaryRegion);
            break;

        case rins_AttributeTertiaryRegion:
            dest->TertiaryRegion = src->TertiaryRegion;
            //TraceDebug(m,"%s %d TertiaryRegion %d\n", __FUNCTION__, __LINE__, (int)dest->TertiaryRegion);
            break;

        case rins_AttributeScrOrFTA:
            dest->ScrambledState = src->ScrambledState;
            break;
		case rins_AttributeDualAnalogPass:
		    TraceDebug(m,"%s %d DualAnalogPass %d\n", __FUNCTION__, __LINE__, (int)src->DualAnalogPass);
       		dest->DualAnalogPass = src->DualAnalogPass;
			break;
		case rins_AttributeDTTScanOnAnalog:	
		    TraceDebug(m,"%s %d DTTScanonAnalog %d\n", __FUNCTION__, __LINE__, (int)src->DTTScanonAnalog);		
       		dest->DTTScanonAnalog = src->DTTScanonAnalog;
			break;			
		case rins_AttributeFavoriteChannelId:	
		    TraceDebug(m,"%s %d FavoriteChannelId %d\n", __FUNCTION__, __LINE__, (int)src->FavoriteChannelListId);		
       		dest->FavoriteChannelListId = src->FavoriteChannelListId;
			break;				

    }   
}

inline Bool CHsvDvbTInstallation_msettings_Priv::mAttributeValueCopy(HsvDVBTSettings* tmp, int attribute, int value)
{
    Bool retval = FALSE;

    switch(attribute)
    {
        case rins_AttributeScanMode:
            tmp->ScanMode = value;
            retval = TRUE;
            break;

        case rins_AttributeNetworkId:
            tmp->NetworkID = value;
            //TraceDebug(m,"%s %d tmp->NetworkID%d\n", __FUNCTION__, __LINE__, tmp->NetworkID);
            retval = TRUE;
            break;

        case rins_AttributePrimaryRegion:
            tmp->PrimaryRegion = value;
            //TraceDebug(m,"%s %d PrimaryRegion %d\n", __FUNCTION__, __LINE__, value);
            break;

        case rins_AttributeSecondaryRegion:
            tmp->SecondaryRegion = value;
            //TraceDebug(m,"%s %d SecondaryRegion %d\n", __FUNCTION__, __LINE__, value);
            break;

        case rins_AttributeTertiaryRegion:
            tmp->TertiaryRegion = value;
            //TraceDebug(m,"%s %d TertiaryRegion %d\n", __FUNCTION__, __LINE__, value);
            break;

        case rins_AttributeScrOrFTA:
            tmp->ScrambledState = value;
            retval = TRUE;
            break;
		case rins_AttributeDualAnalogPass:
       		tmp->DualAnalogPass = value;
		    retval = TRUE;	
			break;
		case rins_AttributeDTTScanOnAnalog:	
       		tmp->DTTScanonAnalog = value;
			retval = TRUE;
			break;		
		case rins_AttributeFavoriteChannelId:
			tmp->FavoriteChannelListId=value;
            TraceDebug(m,"%s %d rins_AttributeFavoriteChannelId %d\n", __FUNCTION__, __LINE__, value);
			retval=TRUE;
			break;

    }   
    return retval;
}

inline int CHsvDvbTInstallation_msettings_Priv::mGetAttrValue(HsvDVBTSettings tmp, int attribute)
{
    int retval = FALSE;

    switch(attribute)
    {
        case rins_AttributeScanMode:
            retval = tmp.ScanMode;
            break;

        case rins_AttributeNetworkId:
            retval = tmp.NetworkID;
            //TraceDebug(m,"%s %d tmp->NetworkID%d\n", __FUNCTION__, __LINE__, retval);
            break;

        case rins_AttributePrimaryRegion:
            retval = tmp.PrimaryRegion;
            //TraceDebug(m,"%s %d PrimaryRegion %d\n", __FUNCTION__, __LINE__, retval);
            break;

        case rins_AttributeSecondaryRegion:
            retval = tmp.SecondaryRegion;
            //TraceDebug(m,"%s %d SecondaryRegion %d\n", __FUNCTION__, __LINE__, retval);
            break;

        case rins_AttributeTertiaryRegion:
            retval = tmp.TertiaryRegion;
            //TraceDebug(m,"%s %d TertiaryRegion %d\n", __FUNCTION__, __LINE__, retval);
            break;

        case rins_AttributeScrOrFTA:
            retval = tmp.ScrambledState;
            break;
		case rins_AttributeDualAnalogPass:
       		retval = tmp.DualAnalogPass;
			     TraceDebug(m,"Rahul:: %s %d attr = %d value: %d",__FUNCTION__,__LINE__,attribute,tmp.DualAnalogPass);

			break;
		case rins_AttributeDTTScanOnAnalog:	
       		retval = tmp.DTTScanonAnalog;
			     TraceDebug(m,"Rahul:: %s %d attr = %d value:%d",__FUNCTION__,__LINE__,attribute,tmp.DTTScanonAnalog);
			break;	
		case rins_AttributeFavoriteChannelId:	
       		retval = tmp.FavoriteChannelListId;
			TraceDebug(m,"%s %d attr = %d value:%d",__FUNCTION__,__LINE__,attribute,tmp.FavoriteChannelListId);
			break;			
    }
    return retval;
}

/********************************
  provides IHsvPower isetpow
 ********************************/
void CHsvDvbTInstallation_msettings_Priv::isetpow_Init()
{
    mLoadDefaults();
    idvbset_ResetAllToDefault();
}
void CHsvDvbTInstallation_msettings_Priv::isetpow_TurnOn()
{
    FILE* fp;
    int readRecords;
	struct stat statbuf;

	mGetFilePath();
    //TraceDebug(m,"Fopen of %s", mFileName);
    fp = fopen(mFileName, "rb");
    if(fp)
    {
        readRecords = fread((Address)(&mPersistentData), sizeof(HsvDVBTSettings), 1, fp);
        if(readRecords)
        {
            //TraceDebug(m,"Persistent Settings is loaded from Flash file");
            //TraceDebug(m,"Write Persistent Settings to Current");
            idvbset_ResetAllToPersistent();
        }
        else
        {
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeScanMode);
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributePrimaryRegion);
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeSecondaryRegion);
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeTertiaryRegion);
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeScrOrFTA);
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeDualAnalogPass);
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeDTTScanOnAnalog);			
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeFavoriteChannelId);			
            //TraceDebug(m,"Nothing present in the file.Load Defaults instead");
        }
        fclose(fp);
    }
    else
    {
        mLoadDefaults();
        idvbset_ResetAllToDefault();
		 /* If no Persistent file available, fill the default values to PersistentData. 	
		   	Otherwise if user does a start and stop of installation it will corrupt the
			settings */
		idvbset_CopyTemporaryToPersistent();
		 
        //TraceDebug(m,"No Flash file present.Load Defaults instead");
    }

	
	/*If file does not exists, create the file and change the ownership for HsvDVBTSettings*/
	if (stat(mFileName, &statbuf) == -1)
	{
		fp = fopen(mFileName, "w+" );
		fclose(fp);
		TraceNotice(m,"%s: %d :File is created",__FUNCTION__,__LINE__);
	}

	/*ownership need to be changed if file is created by older SW also*/
	if(chown(mFileName,-1,AID_USER_SETTING) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chown: %d",__FUNCTION__,__LINE__);
	}
	if(chmod(mFileName, (S_IRWXU | S_IRWXG )) != 0)
	{
		TraceNotice(m,"%s: %d : Error in chmod : %d",__FUNCTION__,__LINE__);
	}
}
void CHsvDvbTInstallation_msettings_Priv::isetpow_TurnOff()
{
}

/********************************
  IBool idvbset
 ********************************/
/* Set and Get works on temporary data */

Bool CHsvDvbTInstallation_msettings_Priv::idvbset_SetAttribute(int installationmode, int attribute, int value)
{
    Bool retval = TRUE;

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        retval = mAttributeValueCopy(&mCurrentData, attribute, value);
    }
    if(retval == FALSE)
    {
        ASSERT(!"Cant set values in Automode");
    }
    return retval;
}

int CHsvDvbTInstallation_msettings_Priv::idvbset_GetAttribute(int installationmode, int attribute)
{
    int retval = 0;

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        retval = mGetAttrValue(mCurrentData, attribute);
    }

    return retval;
}

Bool CHsvDvbTInstallation_msettings_Priv::idvbset_IsAvailable(int installationmode, int attribute) //added to solve PR brg36mgr#77588
{
    Bool retval = TRUE;
    FResult feapiretval = plferrids_Ok;
    Nat32 Decoder = feapi_ChanDecDvbT;


    if((attribute == rins_AttributeSymbolRate) && (feapi_ChanDecDvbT == Decoder) && (installationmode == MANUAL_MODE))
    {
        retval = FALSE;
    }
	else if(attribute == rins_AttributePersistentFile)
	{
		retval = mIsPersistentFileAvailable();
	}

    return retval;
}
/* Copies Default to Temporary */
void CHsvDvbTInstallation_msettings_Priv::idvbset_ResetAttributeToDefault(int installationmode, int attribute)
{

    //TraceDebug(m,"%s",__FUNCTION__);

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        mAttributeCopy(&mCurrentData, &mDefaultData, attribute);
    }
}

/* Copies Persistent to Temporary */
void CHsvDvbTInstallation_msettings_Priv::idvbset_ResetAttributeToPersistent(int installationmode, int attribute)
{
    //TraceDebug(m,"%s",__FUNCTION__);
    UNUSED(installationmode);

    if(AUTO_MODE || UPDATE_MODE)
    {
        mAttributeCopy(&mCurrentData, &mPersistentData, attribute);
    }
    else if(MANUAL_MODE)
    {
        ASSERT(!"No persistent settings for Manaul mode");
    }
}

/* Copies all Default attributes to Temporary */
void CHsvDvbTInstallation_msettings_Priv::idvbset_ResetAllToDefault()
{
    //TraceDebug(m,"%s\n",__FUNCTION__);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeScanMode);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributePrimaryRegion);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeSecondaryRegion);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeTertiaryRegion);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeScrOrFTA);
	mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeDualAnalogPass);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeDTTScanOnAnalog);	
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeFavoriteChannelId);	
}

/* Copies all Persistent attributes to Temporary */
void CHsvDvbTInstallation_msettings_Priv::idvbset_ResetAllToPersistent()
{
    //TraceDebug(m,"%s\n",__FUNCTION__);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeScanMode);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributePrimaryRegion);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeSecondaryRegion);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeTertiaryRegion);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeScrOrFTA);
	mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeDualAnalogPass);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeDTTScanOnAnalog);	
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeFavoriteChannelId);	
	
}

/* Writes persistent values to flash */

void CHsvDvbTInstallation_msettings_Priv::idvbset_CommitPreferred()
{
    /* Write to Flash */
    FILE* fp;
    int writenrec = 0;

    //TraceDebug(m,"Fopen for write = %s", mFileName);
    fp = fopen(mFileName, "wb");
    if( fp )
    {
        writenrec = fwrite((Address)(&mPersistentData), sizeof(HsvDVBTSettings), 1, fp);
        if(writenrec)
        {
            //TraceDebug(m,"Persistent Settings is loaded to Flash file");
        }
        else
        {
            //TraceDebug(m,"Writing to flash failed ");
        }
        if(fflush(fp))
        {
            //TraceNotice(m,"fflush failed");
        }
        if(fsync(fileno(fp)))
        {
            //TraceNotice(m,"fsync failed");
        }
        fclose(fp);
    }
    else
    {
        //TraceDebug(m,"Flash file not present");
    }
}

void CHsvDvbTInstallation_msettings_Priv::idvbset_CopyTemporaryToPersistent()
{
    //TraceDebug(m,"%s",__FUNCTION__);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeScanMode);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributePrimaryRegion);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeSecondaryRegion);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeTertiaryRegion);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeScrOrFTA);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeDualAnalogPass);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeDTTScanOnAnalog);	
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeFavoriteChannelId);	
}

/****************************************************
  provides IHsvSystemSettingsNotifyEx syssetN
 ****************************************************/

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnCountryChanged( int country )
{
    UNUSED(country);
    mLoadDefaults();
    idvbset_ResetAllToDefault();
}

void CHsvDvbTInstallation_msettings_Priv::mLoadDefaults(void)
{
    mDefaultData.ScanMode = rins_QuickScan;
    mDefaultData.PrimaryRegion = mDefaultData.SecondaryRegion = 0xFFFF;
    mDefaultData.TertiaryRegion = 0x1FFFF;
    mDefaultData.ScrambledState = TRUE;
    mDefaultData.DualAnalogPass = FALSE;
    mDefaultData.DTTScanonAnalog = FALSE;	
    mDefaultData.FavoriteChannelListId= 0xFFFF;	
    TraceDebug(m,"%s %d mDefaultData.FavoriteChannelListId = %d",__FUNCTION__,__LINE__,mDefaultData.FavoriteChannelListId);
}   

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnMediumChanged( int medium )
{
    UNUSED(medium);
    mLoadDefaults();
    idvbset_ResetAllToDefault();
}

void CHsvDvbTInstallation_msettings_Priv::idvbset_ClearPersistent()
{
	mGetFilePath();
//    PrintfErr("%s %d mFileName %s\n",__FUNCTION__, __LINE__, mFileName);
    unlink(mFileName);
}

Bool CHsvDvbTInstallation_msettings_Priv::mIsPersistentFileAvailable(void)
{
    FILE* fp;
    int readRecords;
	Bool retval = FALSE;
	HsvDVBTSettings CurrentData;

	mGetFilePath();
	fp = fopen(mFileName, "rb");
    if(fp)
    {
        readRecords = fread((Address)(&CurrentData), sizeof(HsvDVBTSettings), 1, fp);
        retval = (readRecords)? TRUE: FALSE;
	}
	return retval;
}

void CHsvDvbTInstallation_msettings_Priv::mGetFilePath(void)
{
/*
	ffsdir_GetDirPath( mDirName, ffsdir_Boot, ffsdir_Broadcast );
	str_strcat(mDirName, "/channellib/");
	
	if(str_strlen(mDirName))
	{
		str_strcpy(mFileName, mDirName);
		str_strcat(mFileName, "/");
		str_strcat(mFileName, BOOT_FILE_NAME);
	}
	else
	{
		ASSERT(!"Boot parition mount has failed");
		str_strcpy(mFileName, DEFAULT_FILE_PATH);
	}
*/
	
	str_strcpy(mFileName, "/user_setting/rw/tvserver/databases/channellib/HsvDvbTSettings.bin");
 

}
int CHsvDvbTInstallation_msettings_Priv::idvbset_GetAttributeLength(int installationmode, int attribute) 
{
	return 0;
}

int CHsvDvbTInstallation_msettings_Priv::idvbset_GetNextAttributeValue(int installationmode, int attribute, int value) 
{
	return 0;
}

void CHsvDvbTInstallation_msettings_Priv::idvbset_SetPreferred(int attribute, int value, Bool preferred) 
{
	return;
}

Bool CHsvDvbTInstallation_msettings_Priv::idvbset_GetAttributeRange(int installationmode, int attribute, int* minValue, int* maxValue) 
{
	return FALSE;
}

int CHsvDvbTInstallation_msettings_Priv::idvbset_GetAttributeMode(int installationmode, int attribute) 
{
	return 0;
}

Bool CHsvDvbTInstallation_msettings_Priv::idvbset_SetAttributeMode(int installationmode, int attribute, int attributeMode) 
{
	return FALSE;
}
void CHsvDvbTInstallation_msettings_Priv::idvbset_SetUserSymbolRates( int installationmode, int *values, int len ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::idvbset_GetUserSymbolRates( int installationmode, int *values, int *len ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::idvbset_GetPredefinedSymbolRates( int installationmode, int *values, int *len ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::idvbset_ClearUserSymbolRates(void) 
{
	return;
}

Nat8 CHsvDvbTInstallation_msettings_Priv::idvbset_GetONIDNetworkOperator ( int ONID ) 
{
	return 0;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnLanguageChanged (  int lang  ) 
{
	return;
}
void CHsvDvbTInstallation_msettings_Priv::syssetN_OnInstalledCountryChanged (  int country ) 
{
	return;
}
void CHsvDvbTInstallation_msettings_Priv::syssetN_OnHearingImpairedTypeChanged (  int lang  ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnPreferredAudioFormatChanged ( int format ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnPreferredPrimaryAudioLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnPreferredSecondaryAudioLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnPreferredPrimarySubtitleLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnPreferredSecondarySubtitleLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnPreferredPrimaryTxtLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnPreferredSecondaryTxtLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbTInstallation_msettings_Priv::syssetN_OnCityChanged (  int city  ) 
{
	return;
}

