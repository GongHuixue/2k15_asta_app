/*****************************************************************************************
  *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
  *
  *  This  source code and any compilation or derivative thereof is the proprietary information of Koninklijke
  *  Philips Electronics N.V. and is confidential in nature.  Under no circumstances is this software to beexposed  
  *  to or placed under an Open Source License of any type without the expressed written permission of 
  *  Koninklijke Philips Electronics N.V.
  *
  *  %name: hsvdvbsfransat_mBckgnd.c %
  *  %version:  TVG_2 %
  *  %date_modified:  %
  *  %derived_by:  anuma %
  *
  ****************************************************************************************/

/*****************************************************************************************
 * Include files
 *****************************************************************************************/
#include "_hsvdvbsfransat_mBckgnd.h"


TRACESYMBOL(m, "installation/hsvdvbsfransat/hsvdvbsfransat_mBckgnd")

/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/




/*****************************************************************************************
 * Static variables and functions
 *****************************************************************************************/
Pump CHsvDvbsFransat_mBckgnd_Priv::s__mPump;

Bool CHsvDvbsFransat_mBckgnd_Priv::s__mActive,CHsvDvbsFransat_mBckgnd_Priv::s__mUpdatePending;










Bool CHsvDvbsFransat_mBckgnd_Priv::IsBackgroundInstall ()
{
    int mode, state;

    insstate_GetCurrentInstallationState (&mode, &state);
    
    return ((mode == BACKGROUND_MODE) ? TRUE : FALSE);
}

void CHsvDvbsFransat_mBckgnd_Priv::PumpHandler (int event, Nat32 param)
{
    UNUSED(param);
    
    switch (event)
    {
    case EvTriggerBckgndUpdateInstall:
        iinsN_OnEvent(iinsN_EventTriggerBckgndUpdateInstall, 0);
		break;
    case EvSDTAvailable:
        /* Anu : Will be implemented as part of background SDT monitoring */
        break;
    default:
        break;
    }
}

Bool CHsvDvbsFransat_mBckgnd_Priv::mIsBATVersionChanged (void)
{
    Bool isChanged = FALSE;	
    HsvPgdatDigServiceData svcdat; 
    HsvPgdatPresetData presetdat;
    HSVSPTYPE(batECN,dvb,bat) batservice; 
    int curBouquetId = 0xFF; 
    int dBaseBouquetId = 0xFF;
    int packageId = 0;
    Nat32 numOfPresetRecs = pgdb_GetNoRecords (PRESET_TABLE);
    Nat32 numOfECNEntries = strapi_GetSize(HsvMain, HSVSPID(batECN, dvb, bat));
    
    /* Get the installed bouquetId from packageId */
    packageId = insstate_GetAttribute(insstate_InstallationNone, insstate_AttributePackageId);
	dBaseBouquetId = ((packageId >> 16)  & 0xFFFF);
    
    if (strapi_GetByKey(HsvMain,HSVSPID(ActualBouquetId, dvb, bat), 0, 0, 0, (void *)(&curBouquetId)))
    {
        TraceNotice (m, "%s() @ %d : dBaseBouquetId %d, curBouquetId %d\n", __FUNCTION__, __LINE__, dBaseBouquetId, curBouquetId);
        if (curBouquetId != dBaseBouquetId)
        {
            TraceNotice (m, "%s() @ %d : Ignoring the BAT version change....\n", __FUNCTION__, __LINE__);
            return isChanged;
        }
    }
    
    /* ECN check is added because when PDSD is invalid or not availabe then the database will be empty
     * which will cause unexpected BAT triggered update.
     */
    if((numOfPresetRecs > 0) && (numOfECNEntries > 0))
    {
        /* Get the first service from PRESET_TABLE and check for valid LCN range */
        if(pgdb_GetByIndex(PRESET_TABLE, (numOfPresetRecs - 1), (Address)&presetdat))
        {
            TraceNotice (m, "%s() @ %d : PRESET_TABLE[0] - {%d, %d, %d}, Preset %d\n", __FUNCTION__, __LINE__, presetdat.OriginalNetworkId, presetdat.Tsid, presetdat.ServiceId, presetdat.PresetNumber);
            if (VALID_LCN_RANGE(presetdat.PresetNumber))
            {
                if (strapi_GetByKey(HsvMain, HSVSPID(batECN, dvb, bat), presetdat.OriginalNetworkId, presetdat.Tsid, presetdat.ServiceId, (void*)(&batservice)))
                {    
                    svcdat.Tpid = presetdat.Tpid;
                    svcdat.ServiceId = presetdat.ServiceId;
                    if(pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat))
                    {
                        TraceNotice(m, "%s() @ %d : dBaseBatVers %d, curBatVer %d\n", __FUNCTION__, __LINE__, svcdat.ServiceListVersion, batservice.VersionNumber);
                        if (svcdat.ServiceListVersion != batservice.VersionNumber)
                        {
                            /* Current BAT version differs from installed service list version */
                            isChanged = TRUE;
                        }
                    }                
                }
                else 
                {
                    /* Service from PRESET_TABLE is not present in BAT ==> BAT version has changed */
                    isChanged = TRUE;
                }
            }
        }
    }
    
    TraceNotice(m, "%s() @ %d : isChanged %s\n", __FUNCTION__, __LINE__, (isChanged == TRUE ? "TRUE" : "FALSE"));
    return isChanged;
}

Bool CHsvDvbsFransat_mBckgnd_Priv::mIsBackgroundUpdateInstallAllowed (void)
{
	// Currently we will be always available with the resources; So returning TRUE	
	return TRUE;
}

void CHsvDvbsFransat_mBckgnd_Priv::mTriggerBckgndUpdateInstallation(void)
{
    if (TRUE == mIsBackgroundUpdateInstallAllowed())
    {
        TraceNotice(m, "%s() @ %d : Triggering BAT Update\n", __FUNCTION__, __LINE__);			
        pmp_PmpSendAfter (mPump, EvTriggerBckgndUpdateInstall, (Nat32)NULL, 1000);
        mUpdatePending = FALSE;
    } else 
    {
        mUpdatePending = TRUE;
    }
}

Bool CHsvDvbsFransat_mBckgnd_Priv::UpdateServiceTable (HSVSPTYPE(ActualTSService, dvb, sdt) service)
{
    HsvChannel svcChannel; 
    HsvPgdatDigServiceData svcData;
    HsvPgdatPresetData   presetData;
    	
    int ret = pgdat_GetDigitalChannel (&svcChannel, service.Original_NetworkId, service.Tsid, service.ServiceId, 0);

    if (err_Ok == ret) 
    {
        presetData.PresetNumber = svcChannel.Channel.Digit;
        pgdb_GetByKey(PRESET_TABLE, (Address) &presetData);
        
        svcData.Tpid = presetData.Tpid;;
        svcData.ServiceId = presetData.ServiceId;
        
        if (TRUE == pgdb_GetByKey(SERVICE_TABLE, (Address)&svcData))
        {
            //TraceNotice (m, "pgdbGetByKey succesful  for serviceId %d preset %d ", svcData.ServiceId, svcData.PresetNumber);
            if (mCompareUnicodeString(svcData.ChannelName, service.ServiceName) == FALSE)
            {
                TraceNotice (m, "ChannelName update for Preset %d ", svcChannel.Channel.OnePart);
				mCopyString( svcData.ChannelName, service.ServiceName, (eurdiv_PresetNameLength - 1) );
				pgdb_Update(SERVICE_TABLE, (Address )&svcData);
//                pgdat_StoreChannelDataString (svcChannel, pgdat_StringChannelName,  service.ServiceName, eurdiv_ChannelNameLength);
				
            }
            else
            {
                TraceDebug (m, " ChannelName same  for Preset %d ", svcChannel.Channel.OnePart);
            }
        }
    }
    
	return TRUE;
}


void CHsvDvbsFransat_mBckgnd_Priv::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}
Bool CHsvDvbsFransat_mBckgnd_Priv::mCompareUnicodeString(Nat16* dest, Nat16* src)
{
    Bool retval = TRUE;
    
    while((*src) && (*dest) && (*dest == *src))
    {        
        dest++;
        src++;
    }    
    if((*src) || (*dest))
    {
    	retval = FALSE;
    }        

    return retval;
}


/*****************************************************************************************
 * External functions
 *****************************************************************************************/
void CHsvDvbsFransat_mBckgnd_Priv::ibckInstall_EnableBackgroundInstallation (void)
{
    //mActive = s2div_IsBackgroundInstallRequired();
    mActive = TRUE;
    TraceNotice (m, "mActive %d\n", mActive);
}

void CHsvDvbsFransat_mBckgnd_Priv::ibckInstall_DisableBackgroundInstallation (void)
{
    mActive = FALSE;
}

void CHsvDvbsFransat_mBckgnd_Priv::ibckgndpow_Init (void)
{
    mPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, TRUE,"hsvdvbsfransat_mBckgnd");
}

void CHsvDvbsFransat_mBckgnd_Priv::ibckgndpow_TurnOn (void)
{
    mActive = FALSE;
    mUpdatePending = FALSE;
}

void CHsvDvbsFransat_mBckgnd_Priv::ibckgndpow_TurnOff (void)
{

}

void CHsvDvbsFransat_mBckgnd_Priv::strapiN_OnAdded (HsvDestination dest, int spid, int key1, int key2, int key3)
{
    //TraceNotice (m, "%s() @ %d : spid %d, key1 %d, key2 %d, key3 %d \n", __FUNCTION__, __LINE__, spid, key1, key2, key3);	    
    HSVSPTYPE(ActualTSService, dvb, sdt) service;
    
    if(mActive && BACKGROUND_INSTALL)
    {
        switch(spid)
        {
            case HSVSPID(ActualTSService, dvb, sdt):
               if (TRUE == strapi_GetByKey(dest, spid, key1, key2, key3, &service))
                {
                    UpdateServiceTable (service);	
                }
                break;
            case HSVSPID(OtherTSService, dvb, sdt):
               if (TRUE == strapi_GetByKey(dest, HSVSPID(OtherSDTSection, dvb, sdt), key1, key2, key3, &service))
                {
                    UpdateServiceTable (service);	
                }
                break;
            default:
                break;
        }        
    }
}

void CHsvDvbsFransat_mBckgnd_Priv::strapiN_OnChanged  (HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{    
    HSVSPTYPE(ActualTSService, dvb, sdt) service;
    
    if(mActive && BACKGROUND_INSTALL)
    {
        switch(spid)
        {
            case HSVSPID(ActualTSService, dvb, sdt):
            {
               //TraceNotice (m, "%s() @ %d : spid %d, key1 %d, key2 %d, key3 %d, eventid %d \n", __FUNCTION__, __LINE__, spid, key1, key2, key3, eventid);
               if (TRUE == strapi_GetByKey(dest, spid, key1, key2, key3, &service))
                {
                    UpdateServiceTable (service);	
                }
            }
            break;
            case HSVSPID(OtherTSService, dvb, sdt):
            {
               TraceNotice (m, "%s() @ %d : spid %d, key1 %d, key2 %d, key3 %d, eventid %d \n", __FUNCTION__, __LINE__, spid, key1, key2, key3, eventid);
               if (TRUE == strapi_GetByKey(dest, HSVSPID(OtherSDTSection, dvb, sdt), key1, key2, key3, &service))
                {
                    UpdateServiceTable (service);	
                }
            }
            break;
            default:
                break;
        }        
    }
    UNUSED(eventid);
}

void CHsvDvbsFransat_mBckgnd_Priv::strapiN_OnRemoved (HsvDestination dest, int spid, int key1, int key2, int key3)
{
    /* Anu : Will be implemented as part of background SDT monitoring */
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbsFransat_mBckgnd_Priv::strapiN_OnCompleted (HsvDestination dest, int spid)
{
    /* Anu : Will be implemented as part of background SDT monitoring */
    UNUSED(dest);
    UNUSED(spid);
}

void CHsvDvbsFransat_mBckgnd_Priv::bckctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(dmx);

    TraceNotice (m,"%s() @ %d : eventid %d, value %d, mActive %d, BACKGROUND_INSTALL %d", __FUNCTION__, __LINE__, eventid, value, mActive, BACKGROUND_INSTALL);
    if (mActive && BACKGROUND_INSTALL)
    {
        switch (eventid)
        {
        case bckctrlN_DataAvailable:
            switch (value)
            {
            case bckctrlN_BAT:
                if (TRUE == mIsBATVersionChanged())
                {
                    mTriggerBckgndUpdateInstallation();
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }        
    }
}

void CHsvDvbsFransat_mBckgnd_Priv::ibckAcqN_OnDataAquired  (Bool Status)
{
    /* Anu : Will be implemented as part of background SDT monitoring */
	UNUSED(Status);
}

void CHsvDvbsFransat_mBckgnd_Priv::plfresN_OnResourceGained(Nat32 resources)
{
    TraceDebug(m,"%s() @ %d\n", __FUNCTION__, __LINE__);
    if (mActive && BACKGROUND_INSTALL)
    {
        if((TRUE == mUpdatePending) && ((resources & plfres_Frontend) || (resources & plfres_Source)))
        {
            mTriggerBckgndUpdateInstallation();
        }
    }
}

void CHsvDvbsFransat_mBckgnd_Priv::plfresN_OnResourceLost( Nat32 resources )
{
    UNUSED(resources);
}

void CHsvDvbsFransat_mBckgnd_Priv::plfresN_OnResourceStateChanged( int state )
{
    UNUSED(state);
}

void CHsvDvbsFransat_mBckgnd_Priv::sysstateN_OnSystemStateChanged(int State)
{
    TraceDebug(m,"%s() @ %d\n", __FUNCTION__, __LINE__);
	switch(State)
	{
	case sysstateN_RecordingStateChanged:
        TraceNotice(m,"%s() @ %d : RecordingStateChanged\n", __FUNCTION__, __LINE__);
        if (mActive && BACKGROUND_INSTALL)
        {
            if(TRUE == mUpdatePending)
            {
                mTriggerBckgndUpdateInstallation();
            }
        }
        break;
	case sysstateN_MultiviewStateChanged:
	case sysstateN_DisabledEventsStateChanged:
	case sysstateN_TimeshiftStateChanged:
	default:
		break;
	}
}
