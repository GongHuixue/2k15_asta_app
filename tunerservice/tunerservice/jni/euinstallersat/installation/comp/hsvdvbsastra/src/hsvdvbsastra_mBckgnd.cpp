/*****************************************************************************************
  *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
  *
  *  This  source code and any compilation or derivative thereof is the proprietary information of Koninklijke
  *  Philips Electronics N.V. and is confidential in nature.  Under no circumstances is this software to beexposed  
  *  to or placed under an Open Source License of any type without the expressed written permission of 
  *  Koninklijke Philips Electronics N.V.
  *
  *  %name: hsvdvbsastra_mBckgnd.c %
  *  %version:  TVG_2 %
  *  %date_modified:  %
  *
  ****************************************************************************************/

/*****************************************************************************************
 * Include files
 *****************************************************************************************/

#include "astrasort.h"
#include <CHsvDvbsAstra_mBckgnd.h>


TRACESYMBOL(m, "installation/hsvdvbsastra/hsvdvbsastra_mBckgnd")

/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/

#define BACKGROUND_MODE                             (insstate_InstallationBackground)

#define BACKGROUND_INSTALL                          (IsBackgroundInstall())

#define EvDataAvaiable              (0x01)





/*****************************************************************************************
 * Static variables and functions
 *****************************************************************************************/
Bool CHsvDvbsAstra_mBckgnd::s__mActive;

Pump CHsvDvbsAstra_mBckgnd::s__mPump;




Bool CHsvDvbsAstra_mBckgnd::IsBackgroundInstall ()
{
    int mode, state;

    insstate_GetCurrentInstallationState (&mode, &state);
    
    return ((mode == BACKGROUND_MODE) ? TRUE : FALSE);
}

void CHsvDvbsAstra_mBckgnd::PumpHandler(int event, Nat32 param)
{
    if(event == EvDataAvaiable)
    {
        TraceNotice(m,"@ %d event %s - %s\n", __LINE__, "EvDataAvaiable", "Handled");
        mUpdateBackgroundService();    
    }
}


Bool CHsvDvbsAstra_mBckgnd::mIsBackgroundUpdateInstallAllowed (void)
{
	// Currently we will be always available with the resources; So returning TRUE	
	return TRUE;
}

Bool CHsvDvbsAstra_mBckgnd::mUpdateBackgroundService (void)
{
	Bool	RetVal = FALSE;
	Nat32	TpId;
	Bool VersionUpdate = FALSE;
	if(TRUE == mCheckAndUpdateSdtVersion (&TpId))
	{
		/*version mismatch happens For first zap also as version number is invalid in db*/
		iinsN_OnEvent(iinsN_EventInsStarted, BACKGROUND_MODE);
		RetVal = UpdateServiceTable (TpId);
		iinsN_OnEvent(iinsN_EventInsCompleted, BACKGROUND_MODE);
	}
	else
	{
		TraceNotice(m,"No Change in SDT version");
	}
	return RetVal;
}


Bool CHsvDvbsAstra_mBckgnd::mCheckAndUpdateSdtVersion (Nat32 *TpId)
{
	Bool	VersionUpdate = FALSE;
	FResult	RetVal;
    int LnbNumber, Frequency = 0, Polarization = 0;
	HsvSource  Source;
	HsvChannel ChannelNo ;
	HsvPgdatDigTSData			TsData;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	int		i = 0;

	pgsel_GetCurrentProgram(HsvMain,&Source,&ChannelNo);
	
	TraceNotice (m, "ChannelNumber in background %d ", ChannelNo.Channel.Digit);
    RetVal = pgdat_GetChannelDataInt(ChannelNo, pgdat_IntLnbNumber, &LnbNumber);
    RetVal = (RetVal == err_Ok) ? pgdat_GetChannelDataInt(ChannelNo, pgdat_IntPolarization, &Polarization) : RetVal;
    RetVal = (RetVal == err_Ok) ? pgdat_GetChannelDataInt(ChannelNo, pgdat_IntFrequency, &Frequency) : RetVal;
	TraceNotice (m, " Lnb %d Pol %d Freq %d ", LnbNumber, Polarization, Frequency);
	if (RetVal == err_Ok)
	{
		TsData.LnbNumber	= LnbNumber;
		TsData.Frequency	= Frequency;
		TsData.Polarization = Polarization;

		RetVal = pgdb_GetByKey (PTC_TABLE, (Address) &TsData);
		if ((RetVal == TRUE) && (strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sdt), i, (void *)(&service)) == TRUE))
		{
			TraceNotice (m, "ServiceVersion %d InChannelMaps %d ", service.VersionNumber, TsData.SDTVersion);
			VersionUpdate = (service.VersionNumber != TsData.SDTVersion) ? TRUE: FALSE;
			*TpId = TsData.Tpid;
		}

		if (VersionUpdate == TRUE)
		{
			TsData.SDTVersion = service.VersionNumber;
			pgdb_Update (PTC_TABLE, (Address) &TsData);
		}
	}

	return VersionUpdate;
}



Bool CHsvDvbsAstra_mBckgnd::UpdateServiceTable (Nat32 TpId)
{

	Bool	RetVal = TRUE, Update = FALSE;
	HsvPgdatDigServiceData svcdat;
	HSVSPTYPE(ActualTSService, dvb, sdt) service;
	int i, TotalServices = 0;
	HsvChannel Channelinfo;

	TotalServices = strapi_GetSize (HsvMain, HSVSPID(ActualTSService, dvb, sdt));
	TraceNotice (m, "Total services %d ", TotalServices);
	for(i = TotalServices - 1; i >= 0 ; i--)
    {
        if(strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sdt), i, (void *)(&service)) == TRUE)
        {
			svcdat.Tpid = TpId;
			svcdat.ServiceId = service.ServiceId;

			if (TRUE == pgdb_GetByKey(SERVICE_TABLE, (Address)&svcdat))
			{
				
				/*Update Service type and service name*/
				if(!mIsServiceDescriptorAcquired(svcdat.ChannelName))
				{
					/*Update Service Name and type from SDT*/
					svcdat.ServiceType = service.ServiceType;

					mCopyString( svcdat.ChannelName, service.ServiceName, (eurdiv_PresetNameLength - 1) );
					TraceNotice(m,"svc. desc. info updated for service ONID:[%d] TSID:[%d] SVCID[%d] with svctype: %d",service.Original_NetworkId,service.Tsid,svcdat.ServiceId,svcdat.ServiceType);

				}
			
				/*Update Free/Scrambled status*/
				if(service.Free_CA_Mode == TRUE)
				{
					svcdat.ScramblingStatus = 1;
				}
				else
				{
					svcdat.ScramblingStatus = 0;
				}
				TraceNotice(m,"scrambled updated for service ONID:[%d] TSID:[%d] SVCID[%d] with status: %d",service.Original_NetworkId,service.Tsid,svcdat.ServiceId,svcdat.ScramblingStatus);
					
				pgdb_Update(SERVICE_TABLE, (Address )&svcdat);

			}
		}
	}

	return TRUE;
}


void CHsvDvbsAstra_mBckgnd::mCopyString(Nat16* dest, Nat16* src, int maxchars)
{
    int i = 0;
    for(i = 0; i < maxchars; i++)
    {
        *dest++ = *src++;
    }
	*dest = '\0';
}
Bool CHsvDvbsAstra_mBckgnd::mCompareUnicodeString(Nat16* dest, Nat16* src)
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

Bool CHsvDvbsAstra_mBckgnd::mIsServiceDescriptorAcquired(Nat16* src)
{
	Nat16 Unicode_DefaultServiceName[10];
	char DefaultServiceName[10] = "-----";
	int loop = 0;
	Bool retval = FALSE;
	Nat16* dest = Unicode_DefaultServiceName;

	/*Convert to unicode*/
    while( loop < strlen(DefaultServiceName))
    {
        Unicode_DefaultServiceName[loop] = DefaultServiceName[loop];
        ++loop;
    }
	Unicode_DefaultServiceName[loop] = 0;

	/*Compare the strings*/
    while((*src) && (*dest) && (*dest++ == *src++));
	if((*dest) || (*src))
	{
		retval = TRUE;
	}
	else
	{
		retval = FALSE;
		TraceNotice(m," %s: Service need to be updated, RetVal: %d",__FUNCTION__, retval);
	}

	return retval;
}


/*****************************************************************************************
 * External functions
 *****************************************************************************************/
void CHsvDvbsAstra_mBckgnd::EnableBackgroundInstallation (void)
{
    mActive = TRUE;
    TraceNotice (m, "mActive %d\n", mActive);
}

void CHsvDvbsAstra_mBckgnd::DisableBackgroundInstallation (void)
{
    mActive = FALSE;
}

void CHsvDvbsAstra_mBckgnd::Init (void)
{

	mPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, TRUE,"hsvdvbsastra_mBackground");
	
}

void CHsvDvbsAstra_mBckgnd::TurnOn (void)
{
    mActive = FALSE;
}

void CHsvDvbsAstra_mBckgnd::TurnOff (void)
{

}

void CHsvDvbsAstra_mBckgnd::OnAdded (HsvDestination dest, int spid, int key1, int key2, int key3)
{
    HSVSPTYPE(ActualTSService, dvb, sdt) service;
    
    if(mActive && BACKGROUND_INSTALL)
    {
        switch(spid)
        {
            case HSVSPID(ActualTSService, dvb, sdt):
               if (TRUE == strapi_GetByKey(dest, spid, key1, key2, key3, &service))
                {
					pmp_PmpSendAfter( mPump, EvDataAvaiable, (Nat32)NULL, 1500);
                }
                break;
            default:
                break;
        }        
    }
}

void CHsvDvbsAstra_mBckgnd::OnChanged  (HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{    
    UNUSED(eventid);

    OnAdded( dest, spid, key1, key2, key3);
}

void CHsvDvbsAstra_mBckgnd::OnRemoved (HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbsAstra_mBckgnd::OnCompleted (HsvDestination dest, int spid)
{
    UNUSED(dest);
    UNUSED(spid);
}

