/**********************************************************************
 *
 *   C Source:       hsvdvbcamins_msettings.c
 *   Instance:       blr81mgr_1
 *   Description:    
 *   %created_by:    Anantha %
 *   %date_created:  Sat Jan 4 10:47:10 2014 %
 *
 **********************************************************************/
#include "_hsvdvbcamins_mSettings.h"
//TRACESYMBOL(m, "dvb/installation/hsvdvbcamins_msettings")


                                   /** koala type HsvDVBSettings **/

/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/






/****************************************************************************
 * Static variables
 ****************************************************************************/
/* NB: Currently just for Scan Mode later had to be extended to a structure
   if needed */ 
HsvDVBCamSettings CHsvDvbCamInstallation_mSettings_Priv::s__mCurrentData;

HsvDVBCamSettings CHsvDvbCamInstallation_mSettings_Priv::s__mDefaultData;

HsvDVBCamSettings CHsvDvbCamInstallation_mSettings_Priv::s__mPersistentData;



char CHsvDvbCamInstallation_mSettings_Priv::s__mFileName[MAX_CHARACTERS];


/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/

inline void CHsvDvbCamInstallation_mSettings_Priv::mAttributeCopy(HsvDVBCamSettings* dest, HsvDVBCamSettings* src, int attribute)
{
    switch(attribute)
    {
        case rins_Attributecamcharset:
            dest->charTableId = src->charTableId;
            break;

        case rins_AttributeNetworkOperator:
            dest->OperatorProfileInstalled = src->OperatorProfileInstalled;
            break;

        case rins_AttributeOpProfilecicamId:
            dest->cicamId = src->cicamId;
            break;

		case rins_AttributeCamNITVersion:
            dest->camNitVersion= src->camNitVersion;
            break;	


    }   
}

inline Bool CHsvDvbCamInstallation_mSettings_Priv::mAttributeValueCopy(HsvDVBCamSettings* tmp, int attribute, int value)
{
    Bool retval = FALSE;

    switch(attribute)
    {
        case rins_Attributecamcharset:
            tmp->charTableId = value;
            retval = TRUE;
            break;

        case rins_AttributeNetworkOperator:
            tmp->OperatorProfileInstalled = value;
            retval = TRUE;
            break;

        case rins_AttributeOpProfilecicamId:
            tmp->cicamId = value;
            break;

		case rins_AttributeCamNITVersion:
            tmp->camNitVersion= value;
            break;

    }   
    return retval;
}

inline int CHsvDvbCamInstallation_mSettings_Priv::mGetAttrValue(HsvDVBCamSettings tmp, int attribute)
{
    int retval = FALSE;

    switch(attribute)
    {
        case rins_Attributecamcharset:
            retval = tmp.charTableId;
            break;

        case rins_AttributeNetworkOperator:
            retval = tmp.OperatorProfileInstalled;
            break;

        case rins_AttributeOpProfilecicamId:
            retval = tmp.cicamId; 
            break;

		case rins_AttributeCamNITVersion:
            retval = tmp.camNitVersion; 
            break;
    }
    return retval;
}

/********************************
  provides IHsvPower isetpow
 ********************************/
void CHsvDvbCamInstallation_mSettings_Priv::isetpow_Init()
{
    mLoadDefaults();
    idvbset_ResetAllToDefault();
}
void CHsvDvbCamInstallation_mSettings_Priv::isetpow_TurnOn()
{
    FILE* fp;
    int readRecords;

	mGetFilePath();
    //TraceDebug(m,"Fopen of %s", mFileName);
    fp = fopen(mFileName, "rb");
    if(fp)
    {
        readRecords = fread((Address)(&mPersistentData), sizeof(HsvDVBCamSettings), 1, fp);
        if(readRecords)
        {
            //TraceDebug(m,"Persistent Settings is loaded from Flash file");
            //TraceDebug(m,"Write Persistent Settings to Current");
            idvbset_ResetAllToPersistent();
        }
        else
        {
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_Attributecamcharset);
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeNetworkOperator);
            mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeOpProfilecicamId);
			mAttributeCopy(&mPersistentData, &mDefaultData, rins_AttributeCamNITVersion);
            //TraceDebug(m,"Nothing present in the file.Load Defaults instead");
        }
        fclose(fp);
    }
    else
    {
        mLoadDefaults();
        idvbset_ResetAllToDefault();
        //TraceDebug(m,"No Flash file present.Load Defaults instead");
    }
}
void CHsvDvbCamInstallation_mSettings_Priv::isetpow_TurnOff()
{
}

/********************************
  IBool idvbset
 ********************************/
/* Set and Get works on temporary data */

Bool CHsvDvbCamInstallation_mSettings_Priv::idvbset_SetAttribute(int installationmode, int attribute, int value)
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

int CHsvDvbCamInstallation_mSettings_Priv::idvbset_GetAttribute(int installationmode, int attribute)
{
    int retval = 0;

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        retval = mGetAttrValue(mCurrentData, attribute);
    }

    return retval;
}

Bool CHsvDvbCamInstallation_mSettings_Priv::idvbset_IsAvailable(int installationmode, int attribute) //added to solve PR brg36mgr#77588
{
    Bool retval = FALSE;
 

	if(attribute == rins_AttributeNetworkOperator)
	{
		retval = mIsPersistentFileAvailable();
	}

    return retval;
}
/* Copies Default to Temporary */
void CHsvDvbCamInstallation_mSettings_Priv::idvbset_ResetAttributeToDefault(int installationmode, int attribute)
{

    //TraceDebug(m,"%s",__FUNCTION__);

    if((installationmode == AUTO_MODE) || (installationmode == UPDATE_MODE))
    {
        mAttributeCopy(&mCurrentData, &mDefaultData, attribute);
    }
}

/* Copies Persistent to Temporary */
void CHsvDvbCamInstallation_mSettings_Priv::idvbset_ResetAttributeToPersistent(int installationmode, int attribute)
{
    //TraceDebug(m,"%s",__FUNCTION__);
    UNUSED(installationmode);

    if(AUTO_MODE || UPDATE_MODE)
    {
        mAttributeCopy(&mCurrentData, &mPersistentData, attribute);
    }
}

/* Copies all Default attributes to Temporary */
void CHsvDvbCamInstallation_mSettings_Priv::idvbset_ResetAllToDefault()
{
    //TraceDebug(m,"%s\n",__FUNCTION__);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_Attributecamcharset);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeNetworkOperator);
    mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeOpProfilecicamId);
 	mAttributeCopy(&mCurrentData, &mDefaultData, rins_AttributeCamNITVersion);
}

/* Copies all Persistent attributes to Temporary */
void CHsvDvbCamInstallation_mSettings_Priv::idvbset_ResetAllToPersistent()
{
    //TraceDebug(m,"%s\n",__FUNCTION__);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_Attributecamcharset);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeNetworkOperator);
    mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeOpProfilecicamId);
	mAttributeCopy(&mCurrentData, &mPersistentData, rins_AttributeCamNITVersion);
 
}

/* Writes persistent values to flash */

void CHsvDvbCamInstallation_mSettings_Priv::idvbset_CommitPreferred()
{
    /* Write to Flash */
    FILE* fp;
    int writenrec = 0;

    //TraceDebug(m,"Fopen for write = %s", mFileName);
    fp = fopen(mFileName, "wb");
    if( fp )
    {
        writenrec = fwrite((Address)(&mPersistentData), sizeof(HsvDVBCamSettings), 1, fp);
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

void CHsvDvbCamInstallation_mSettings_Priv::idvbset_CopyTemporaryToPersistent()
{
    //TraceDebug(m,"%s",__FUNCTION__);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_Attributecamcharset);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeNetworkOperator);
    mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeOpProfilecicamId);
 	mAttributeCopy(&mPersistentData, &mCurrentData, rins_AttributeCamNITVersion);
}

/****************************************************
  provides IHsvSystemSettingsNotifyEx syssetN
 ****************************************************/

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnCountryChanged( int country )
{
    UNUSED(country);
    mLoadDefaults();
    idvbset_ResetAllToDefault();
}

void CHsvDvbCamInstallation_mSettings_Priv::mLoadDefaults(void)
{
    mDefaultData.charTableId = 0;
    mDefaultData.OperatorProfileInstalled = 0;
    mDefaultData.cicamId = 0;
	mDefaultData.camNitVersion= 0;
}   

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnMediumChanged( int medium )
{
    UNUSED(medium);
    mLoadDefaults();
    idvbset_ResetAllToDefault();
}

void CHsvDvbCamInstallation_mSettings_Priv::idvbset_ClearPersistent()
{
	mGetFilePath();
//    PrintfErr("%s %d mFileName %s\n",__FUNCTION__, __LINE__, mFileName);
    unlink(mFileName);
}

Bool CHsvDvbCamInstallation_mSettings_Priv::mIsPersistentFileAvailable(void)
{
    FILE* fp;
    int readRecords;
	Bool retval = FALSE;
	HsvDVBCamSettings CurrentData;

	mGetFilePath();
	fp = fopen(mFileName, "rb");
    if(fp)
    {
        readRecords = fread((Address)(&CurrentData), sizeof(HsvDVBCamSettings), 1, fp);
        retval = (readRecords)? TRUE: FALSE;
	}
	return retval;
}

void CHsvDvbCamInstallation_mSettings_Priv::mGetFilePath(void)
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
	
	str_strcpy (mFileName, "/user_setting/rw/tvserver/databases/channellib/HsvDVBCamSettings.bin");
}
int CHsvDvbCamInstallation_mSettings_Priv::idvbset_GetAttributeLength(int installationmode, int attribute) 
{
	return 0;
}

int CHsvDvbCamInstallation_mSettings_Priv::idvbset_GetNextAttributeValue(int installationmode, int attribute, int value) 
{
	return 0;
}

void CHsvDvbCamInstallation_mSettings_Priv::idvbset_SetPreferred(int attribute, int value, Bool preferred) 
{
	return;
}

Bool CHsvDvbCamInstallation_mSettings_Priv::idvbset_GetAttributeRange(int installationmode, int attribute, int* minValue, int* maxValue) 
{
	return FALSE;
}

int CHsvDvbCamInstallation_mSettings_Priv::idvbset_GetAttributeMode(int installationmode, int attribute) 
{
	return 0;
}

Bool CHsvDvbCamInstallation_mSettings_Priv::idvbset_SetAttributeMode(int installationmode, int attribute, int attributeMode) 
{
	return FALSE;
}
void CHsvDvbCamInstallation_mSettings_Priv::idvbset_SetUserSymbolRates( int installationmode, int *values, int len ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::idvbset_GetUserSymbolRates( int installationmode, int *values, int *len ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::idvbset_GetPredefinedSymbolRates( int installationmode, int *values, int *len ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::idvbset_ClearUserSymbolRates(void) 
{
	return;
}

Nat8 CHsvDvbCamInstallation_mSettings_Priv::idvbset_GetONIDNetworkOperator ( int ONID ) 
{
	return 0;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnLanguageChanged (  int lang  ) 
{
	return;
}
void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnInstalledCountryChanged (  int country ) 
{
	return;
}
void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnHearingImpairedTypeChanged (  int lang  ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnPreferredAudioFormatChanged ( int format ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnPreferredPrimaryAudioLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnPreferredSecondaryAudioLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnPreferredPrimarySubtitleLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnPreferredSecondarySubtitleLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnPreferredPrimaryTxtLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnPreferredSecondaryTxtLanguageChanged ( int value ) 
{
	return;
}

void CHsvDvbCamInstallation_mSettings_Priv::syssetN_OnCityChanged (  int city  ) 
{
	return;
}


