#include "_satinstallerstub_mdummy.h"

#include "string.h"


TRACESYMBOL(m, "comps/satinstaller_mdummy")


int CS2InstallerStub_Priv::s__InsCountry = 0,CS2InstallerStub_Priv::s__InsInstallCountry = 0;

/* Below are the AV pids to set during manual installation. 
 * These variables will be set using mctl_SetMedia(), played during 
 * mctl_Play() and cleared using mctl_Flush(). 
 */
Nat16 CS2InstallerStub_Priv::s__AudioPid = INVALID_PID;
Nat16 CS2InstallerStub_Priv::s__VideoPid = INVALID_PID;
Nat16 CS2InstallerStub_Priv::s__PcrPid = INVALID_PID;
Nat16 CS2InstallerStub_Priv::s__AudioStreamType = INVALID_PID;
Nat16 CS2InstallerStub_Priv::s__VideoStreamType = INVALID_PID;


#ifndef __cplusplus
/*intf: pmp*/


Pump CS2InstallerStub_Priv::pmp_PmpCreateEx(PumpEngine pen, PumpFunc func, Bool replace, char* name)
{
	return 0;
}

void CS2InstallerStub_Priv::pmp_PmpSend( Pump pmp, int param1, Nat32 param2 )
{
	return;
}

void CS2InstallerStub_Priv::pmp_PmpSendAfter( Pump pmp, int param1, Nat32 param2, int msecs )
{
	return;
}

Bool CS2InstallerStub_Priv::pmp_PenTaskHasLock( PumpEngine pen )
{
	return 0;
}
#endif


/* Interfaces from IProdApiClockEx.id */

void CS2InstallerStub_Priv::Timerclk_SetTime( DateTime utc, DateTime lto, int source ) 
{
	return;
}

void CS2InstallerStub_Priv::Timerclk_SetLocalTime( DateTime time, int source ) 
{
	return;
}


DateTime CS2InstallerStub_Priv::Timerclk_GetLocalTimeOffset ( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::Timerclk_SetNextLTOChange( DateTime timeOfChange, int nextLTO, int source ) 
{
	return;
}

void CS2InstallerStub_Priv::Timerclk_GetAbsoluteLocalTime( DateTime Utc, DateTime *localTime) 
{
	return;
}

void CS2InstallerStub_Priv::Timerclk_GetAbsoluteUTC( DateTime localTime, DateTime *Utc) 
{
	return;
}

void CS2InstallerStub_Priv::Timerclk_SetUserTimeZone( int timezone ) 
{
	return;
}

int CS2InstallerStub_Priv::Timerclk_GetUserTimeZone( void ) 
{
	return 0;
}

int CS2InstallerStub_Priv::Timerclk_GetTimeZone( void ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::Timerclk_IsDstActive( void ) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::Timerclk_SetUserDst( int dst ) 
{
	return;
}

int CS2InstallerStub_Priv::Timerclk_GetUserDst( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::Timerclk_SetLtoMode( int ltomode ) 
{
	return;
}

int CS2InstallerStub_Priv::Timerclk_GetLtoMode( void ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::Timerclk_IsClockManual( void ) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::Timerclk_SetUniversalTime( DateTime utc, int source )
{
	return;
}

DateTime CS2InstallerStub_Priv::Timerclk_GetLocalTime( void ) 
{
	return (DateTime)0;
}


Bool CS2InstallerStub_Priv::Timerclk_IsClockDefined( void )
{
	return 0;
}

DateTime CS2InstallerStub_Priv::Timerclk_GetUniversalTime( void )
{
	return 0;
}

	 /* Interfaces from IRealTimeKernel.id */
Task CS2InstallerStub_Priv::rtk_TskCreate( TaskFunction func, int priority, int stacksize ) 
{
	return 0;
}

Task CS2InstallerStub_Priv::rtk_TskCreateNoWatchdog( TaskFunction func, int priority, int stacksize ) 
{
	return 0;
}

void CS2InstallerStub_Priv::rtk_TskDelete( Task tsk ) 
{
	return;
}

Task CS2InstallerStub_Priv::rtk_TskCurrent( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::rtk_TskSetPriority( Task tsk, int priority ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_TskSuspend( int msecs ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_TskResume( Task tsk ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_TskBeginCriticalSection( void ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_TskEndCriticalSection( void ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_TskFeedWatchdog( void ) 
{
	return;
}

Bool CS2InstallerStub_Priv::rtk_TskBoostWatchdog( int seconds ) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::rtk_TskWatchdogPeriod( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::rtk_IsrBegin( void ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_IsrEnd( void ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_IsrEvtSend( Task tsk, Event evt ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_IsrMbxSend( Mailbox mbx, int msg, int param1, Nat32 param2 ) 
{
	return;
}

Semaphore CS2InstallerStub_Priv::rtk_SemCreate( void ) 
{
	return 0;
}

Semaphore CS2InstallerStub_Priv::rtk_SemCreateWithCeiling( int ceiling ) 
{
	return 0;
}

void CS2InstallerStub_Priv::rtk_SemDelete( Semaphore sem ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_SemAcquire( Semaphore sem ) 
{
	return;
}

Bool CS2InstallerStub_Priv::rtk_SemAcquireNoWait( Semaphore sem ) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::rtk_SemRelease( Semaphore sem ) 
{
	return;
}

Event CS2InstallerStub_Priv::rtk_EvtCreate( Task tsk ) 
{
	return 0;
}

void CS2InstallerStub_Priv::rtk_EvtDelete( Task tsk, Event evt ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_EvtSend( Task tsk, Event evt ) 
{
	return;
}

Event CS2InstallerStub_Priv::rtk_EvtReceive( Event mask ) 
{
	return 0;
}

Event CS2InstallerStub_Priv::rtk_EvtReceiveNoWait( Event mask ) 
{
	return 0;
}

Event CS2InstallerStub_Priv::rtk_EvtReceiveWait( Event mask, int msecs )  /* NOTE: might not be available when not using CMX */
{
	return 0;
}

Event CS2InstallerStub_Priv::rtk_EvtGetReserved( Task tsk )               /* NOTE: might not be available when not using CMX */
{
	return 0;
}

Timer CS2InstallerStub_Priv::rtk_TmrCreate( Task tsk, Event evt ) 
{
	return 0;
}

void CS2InstallerStub_Priv::rtk_TmrDelete( Timer tmr ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_TmrEvery( Timer tmr, int msecs ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_TmrOnce( Timer tmr, int msecs ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_TmrCancel( Timer tmr ) 
{
	return;
}

int CS2InstallerStub_Priv::rtk_TmrTime( void ) 
{
	return 0;
}

int CS2InstallerStub_Priv::rtk_TmrResolution( void ) 
{
	return 0;
}

Mailbox CS2InstallerStub_Priv::rtk_MbxCreate( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::rtk_MbxDelete( Mailbox mbx ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_MbxSend( Mailbox mbx, int msg, int param1, Nat32 param2 ) 
{
	return;
}

void CS2InstallerStub_Priv::rtk_MbxReceive( Mailbox mbx , Message *msg ) 
{
	return;
}

Bool CS2InstallerStub_Priv::rtk_MbxReceiveNoWait( Mailbox mbx, Message *msg ) 
{
	return FALSE;
}

Talos CS2InstallerStub_Priv::rtk_TlsCreate( int size ) 
{
	return 0;
}

void * CS2InstallerStub_Priv::rtk_TlsAccess( Talos tls ) 
{
	return NULL;
}



/* Interfaces from IHsvSystemSettings.id */
void CS2InstallerStub_Priv::sysset_SetSystemLanguage( int lang ) 
{
	return;
}

void CS2InstallerStub_Priv::sysset_SetPreferredPrimaryAudioLanguage (int lang) 
{
	return;
}

int CS2InstallerStub_Priv::sysset_GetPreferredPrimaryAudioLanguage (void) 
{
	return 0;
}

int CS2InstallerStub_Priv::sysset_GetPreferredSecondarySubtitleLanguage( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::sysset_SetPreferredSecondarySubtitleLanguage( int lang ) 
{
	return;
}

int CS2InstallerStub_Priv::sysset_GetPreferredSecondaryAudioLanguage( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::sysset_SetPreferredSecondaryAudioLanguage( int lang ) 
{
	return;
}

void CS2InstallerStub_Priv::sysset_SetPreferredPrimarySubtitleLanguage (int lang) 
{
	return;
}

int CS2InstallerStub_Priv::sysset_GetPreferredPrimarySubtitleLanguage (void) 
{
	return 0;
}

void CS2InstallerStub_Priv::sysset_SetPreferredAudioFormat(int format) 
{
	return;
}

int CS2InstallerStub_Priv::sysset_GetPreferredAudioFormat(void) 
{
	return 0;
}

void CS2InstallerStub_Priv::sysset_SetPreferredPrimaryTxtLanguage(int lang) 
{
	return;
}

int CS2InstallerStub_Priv::sysset_GetPreferredPrimaryTxtLanguage(void) 
{
	return 0;
}

void CS2InstallerStub_Priv::sysset_SetPreferredSecondaryTxtLanguage(int lang) 
{
	return;
}

int CS2InstallerStub_Priv::sysset_GetPreferredSecondaryTxtLanguage(void) 
{
	return 0;
}

void CS2InstallerStub_Priv::sysset_SetSystemCountry( int country )  /* installationSettingsCountry, user country */
{
	InsCountry = country;
	//TraceNotice(m,"sysset_SetSystemCountry: country %d",InsCountry);   
//	InsCountry = 11; //Temp
	return;
}

void CS2InstallerStub_Priv::sysset_SetInstallCountry( int country )  
{

	InsInstallCountry = country;
	return;
}


void CS2InstallerStub_Priv::sysset_SetInstallCity(int city) 
{
	return;
}

void CS2InstallerStub_Priv::sysset_SetSystemCity(int city) 
{
	return;
}

int CS2InstallerStub_Priv::sysset_GetSystemLanguage( void )
{
	return tvcoresettings_getValue (tvcoresettings_MenuLanguage);

}
int CS2InstallerStub_Priv::sysset_GetInstallCountry( void )
{
	return tvcoresettings_getValue (tvcoresettings_InstalledCountry);
}   

int CS2InstallerStub_Priv::sysset_GetInstallCity(void)
{
	return 0;
}
int CS2InstallerStub_Priv::sysset_GetSystemCountry( void )
{
//	InsCountry = 11; //Temp
	//TraceNotice(m, "sysset_GetSystemCountry: country %d",tvcoresettings_getValue (tvcoresettings_InstalledCountry));   
	return tvcoresettings_getValue (tvcoresettings_InstalledCountry);
}    
int CS2InstallerStub_Priv::sysset_GetSystemCity(void)
{
	return 0;
}


/* Interfaces from IHsvMediaControl.id */
int CS2InstallerStub_Priv::mctl_GetMediaSize        ( HsvDestination dest, int media ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::mctl_GetMediaByKey       ( HsvDestination dest, int media, int selector1, int selector2, void *value ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mctl_GetMediaIndex       ( HsvDestination dest, int media, int selector1, int selecto2, int *index ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mctl_GetMediaByIndex     ( HsvDestination dest, int media, int index, void *value ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mctl_SetMedia      (HsvDestination dest, int media, int selector, int value) 
{
    Bool retVal = TRUE;
  
   	//TraceNotice(m,"%s) : media %d, pid %d\n", __FUNCTION__, media, value);   
    switch (media)
    {
    case mctl_Audio:
        AudioPid = value;
		AudioStreamType = ConvertToSTAudioType(selector);
        break;
    case mctl_Video:
        VideoPid = value;
		VideoStreamType = ConvertToSTVideoType(selector);
        break;
    case mctl_Pcr:
        PcrPid = value;
        break;
    default:
        TraceNotice(m,"%s) : Invalid Media\n", __FUNCTION__);   
        retVal = FALSE;
        break;
    }

    UNUSED(dest);
    UNUSED(selector);
    
	return retVal;
}

Bool CS2InstallerStub_Priv::mctl_SetMediaWithProgram ( HsvDestination dest, int program, int media, int selector, int value) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mctl_PlayMedia           ( HsvDestination dest, int media ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mctl_StopMedia           ( HsvDestination dest, int media ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mctl_EnableMedia			( HsvDestination dest, int media ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mctl_DisableMedia		( HsvDestination dest, int media ) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::mctl_GetCurrentSelection ( HsvDestination dest, int media, int selector) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::mctl_IsMediaPlaying      ( HsvDestination dest, int media) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mctl_IsMediaEnabled      ( HsvDestination dest, int media) 
{
	return FALSE;
}


Bool CS2InstallerStub_Priv::mctl_Play    (HsvDestination dest)
{
    Bool retVal = FALSE;
    Nat32 error;
    int winid = 0;

	if (INVALID_PID != VideoStreamType)
		plfApiTsDmx->SetVideoStreamType(winid, VideoStreamType, &error);
	
	if (INVALID_PID != VideoPid)
		plfApiTsDmx->SetVideoPid(winid, VideoPid, &error);

	if (INVALID_PID != AudioStreamType)
		plfApiTsDmx->SetAudioStreamType(winid, AudioStreamType, &error);
	
	if (INVALID_PID != AudioPid)
		plfApiTsDmx->SetAudioPid(winid, AudioPid, &error);
		
	if (INVALID_PID != PcrPid)
		plfApiTsDmx->SetPcrPid(winid, PcrPid, &error);
		   
	retVal = TRUE;

    UNUSED(dest);
    
	return retVal;
}

Bool CS2InstallerStub_Priv::mctl_Stop    (HsvDestination dest)
{
	Bool retVal = FALSE;
    Nat32 error;
    int winid = 0;

        TraceDebug(m,"%s() : %d \n", __FUNCTION__, __LINE__);
		
	if (INVALID_PID != VideoPid)
		plfApiTsDmx->StopVideoPid(winid, &error);
	
	if (INVALID_PID != AudioPid)
		plfApiTsDmx->StopAudioPid(winid, &error);
	
	if (INVALID_PID != PcrPid)
		plfApiTsDmx->StopPcrPid(winid, &error);
	
	mctl_Flush (dest);
	
	retVal = TRUE;

    UNUSED(dest);
    
	return retVal;
}

Bool CS2InstallerStub_Priv::mctl_Flush     (HsvDestination dest)
{    
	AudioPid = INVALID_PID;
    VideoPid = INVALID_PID;
    PcrPid = INVALID_PID;
    AudioStreamType = INVALID_PID;
	VideoStreamType = INVALID_PID;
    UNUSED(dest);

    return TRUE;
}

/* Interfaces from IAppApiSystemSettings5.id */
int CS2InstallerStub_Priv::apsysset_GetClockMode(void) 
{
	return 0;
}

void CS2InstallerStub_Priv::apsysset_SetClockMode(int mode) 
{
	return;
}

Bool CS2InstallerStub_Priv::apsysset_IsDstSettingControllable(void) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::apsysset_GetDst(void) 
{
	return 0;
}

void CS2InstallerStub_Priv::apsysset_SetDst(Bool dst) 
{
	return;
}

Bool CS2InstallerStub_Priv::apsysset_IsManualClockSettingControllable(void)  
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::apsysset_GetAutoPowerDownMode(void) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_SetAutoPowerDownMode(Bool mode)     
{
	return;
}

FResult CS2InstallerStub_Priv::apsysset_SetMenuLanguage(int language) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetMenuLanguage(void) 
{
	return tvcoresettings_getValue (tvcoresettings_MenuLanguage);
}

FResult CS2InstallerStub_Priv::apsysset_SetInstallCountry(int country ) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetInstallCountry(void) 
{
	return tvcoresettings_getValue (tvcoresettings_InstalledCountry);
}

Bool CS2InstallerStub_Priv::apsysset_IsDateSet(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::apsysset_IsClockDefined(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::apsysset_IsLTOSet(void) 
{
	return FALSE;
}

FResult CS2InstallerStub_Priv::apsysset_SetRCLock( Bool OnOff ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetRCLockStatus(void) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_OverrideRCLock(Bool Override) 
{
	return;
}

FResult CS2InstallerStub_Priv::apsysset_SetKeyboardLock(Bool OnOff) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetKeyboardLock( void ) 
{
	return FALSE;
}

FResult CS2InstallerStub_Priv::apsysset_SetBDSMode ( Bool mode ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_GetBDSMode( Bool *mode ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetSXApplicationControl (Bool onoff ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetSXApplicationControl ( void ) 
{
	return FALSE;
}

FResult CS2InstallerStub_Priv::apsysset_SetBDSFeatureEnabled (Bool onoff) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetBDSFeatureEnabled ( void ) 
{
	return FALSE;
}

FResult CS2InstallerStub_Priv::apsysset_SetBDSPowerOnState( int state ) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetBDSPowerOnState( void ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetOSDDisplay( Bool on_off ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetOSDDisplay( void ) 
{
	return FALSE;
}

FResult CS2InstallerStub_Priv::apsysset_SetBdsWakeupSource( int src ) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetBdsWakeupSource( void ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetHotelModeUsbBreakInAllowed(Bool onOff) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetHotelModeUsbBreakInAllowed( void ) 
{
	return FALSE;
}

FResult CS2InstallerStub_Priv::apsysset_SetMaxAllowedVolume(int MaxVol) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetMaxAllowedVolume( void ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetEpgType(int epgType) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetEpgType(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetFactoryMode( Bool onoff ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetFactoryMode( void ) 
{
	return FALSE;
}

FResult CS2InstallerStub_Priv::apsysset_SetShopHomeMode(int mode) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetShopHomeMode(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetVirginBit(Bool virginBit) 
{
	return 0;
}


FResult CS2InstallerStub_Priv::apsysset_SetClockCalibSource( int src ) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetClockCalibSource(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetCurrentAVSource( int src ) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetCurrentAVSource( void ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetPreferredAudioFormat(int format) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetPreferredAudioFormat(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetServiceMode( int mode ) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetServiceMode( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::apsysset_SetTimeZone ( int timezone ) 
{
	return;
}

int CS2InstallerStub_Priv::apsysset_GetTimeZone ( void ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_IsTimeZoneSettingControllable(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::apsysset_IsTimeZoneAvailable(int timezone) 
{
	return FALSE;
}

Nat32 CS2InstallerStub_Priv::apsysset_GetSystemVersionNumber(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetOsdSize(int size) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetOsdSize(void) 
{
	return 0;
}

void CS2InstallerStub_Priv::apsysset_SetClockCaliberated(int state) 
{
	return;
}

FResult CS2InstallerStub_Priv::apsysset_SetHotelModeUsbBrowseAllowed(Bool OnOff) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetHotelModeUsbBrowseAllowed(void) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_SetFactoryReset(void) 
{
	return;
}

FResult CS2InstallerStub_Priv::apsysset_SetPrimaryAudioLanguage(int language) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetPrimaryAudioLanguage(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetSecondaryAudioLanguage(int language) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetSecondaryAudioLanguage(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetPrimarySubtitleLanguage(int language) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetPrimarySubtitleLanguage(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetSecondarySubtitleLanguage(int language) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetSecondarySubtitleLanguage(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetPrimaryTxtLanguage(int language) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetPrimaryTxtLanguage(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetSecondaryTxtLanguage(int language) 
{
	return 0;
}

int CS2InstallerStub_Priv::apsysset_GetSecondaryTxtLanguage(void) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::apsysset_SetHearingImpaired(Bool OnOff) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::apsysset_GetHearingImpaired(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::apsysset_ResetInternet(void) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_SetHbbTv(Bool OnOff ) 
{
	return;
}

Bool CS2InstallerStub_Priv::apsysset_GetHbbTv(void) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_AllowLastSourceUpdateInNVM(Bool enable) 
{
	return;
}

void CS2InstallerStub_Priv::apsysset_SetActiveChannelList(int ChannelList) 
{
	return;
}

int CS2InstallerStub_Priv::apsysset_GetActiveChannelList(void) 	
{
	return 0;
}


int CS2InstallerStub_Priv::apsysset_GetMedium(void) 	
{
	return 0;
}

void CS2InstallerStub_Priv::apsysset_SetUserPinEntryStatus(Bool Status) 	
{
	return;
}

Bool CS2InstallerStub_Priv::apsysset_GetUserPinEntryStatus(void) 	
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_SetVisuallyImpairedStatus(Bool onoff) 	
{
	return;
}

Bool CS2InstallerStub_Priv::apsysset_GetVisuallyImpairedStatus(void) 	
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_SetSubtitlePreference(int val) 	
{
	return;
}

int CS2InstallerStub_Priv::apsysset_GetSubtitlePreference(void) 	
{
	return 0;
}

void CS2InstallerStub_Priv::apsysset_SetPinCode(int val) 	
{
	return;
}

int CS2InstallerStub_Priv::apsysset_GetPinCode(void) 
{
	return 0;
}

void CS2InstallerStub_Priv::apsysset_SetDMR(Bool val) 
{
	return;
}

Bool CS2InstallerStub_Priv::apsysset_GetDMR(void) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_SetWiFiSmartScreen(Bool val) 
{
	return;
}

Bool CS2InstallerStub_Priv::apsysset_GetWiFiSmartScreen(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::apsysset_GetChannelLogo(void) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::apsysset_SetTvFriendlyName(Nat16* val) 
{
	return;
}

Nat16* CS2InstallerStub_Priv::apsysset_GetTvFriendlyName(void) 	
{
	return NULL;
}

char* CS2InstallerStub_Priv::apsysset_GetMenuLangICUFormat(int language) 
{
	return NULL;
}

void CS2InstallerStub_Priv::apsysset_SetTimeOfChange(DateTime changeTime, DateTime nextTimeOffset) 
{
	return;
}

void CS2InstallerStub_Priv::apsysset_GetTimeOfChange(DateTime *changeTime, DateTime *nextTimeOffset) 
{
	return;
}

void CS2InstallerStub_Priv::apsysset_SetLastViewedEPG(int val) 
{
	return;
}

int CS2InstallerStub_Priv::apsysset_GetLastViewedEPG(void) 
{
	return 0;
}

void CS2InstallerStub_Priv::apsysset_SetChannelLogo(Bool val)	
{
	return;
}


Bool CS2InstallerStub_Priv::apsysset_GetVirginBit()
{
	Bool retval;
	retval = tvcoresettings_getValue (tvcoresettings_VirginBitStatus);
	TraceNotice(m,"apsysset_GetVirginBit : %d",retval);
	return retval;
}

void CS2InstallerStub_Priv::apsysset_SetMedium(int Medium)
{
	return;
}

/*intf: ITvPlatformResource*/
Nat32 CS2InstallerStub_Priv::plfres_GetOwnedResources()
{
	return 0;
}

Bool CS2InstallerStub_Priv::plfres_IsResourceOwned( Nat32 resid )
{
	return FALSE;
}
int CS2InstallerStub_Priv::plfres_GetResourceState( void )
{
	return 0;
}
void CS2InstallerStub_Priv::plfres_RequestResourceState( int State)
{
	return;
}
void CS2InstallerStub_Priv::plfres_RestorePreviousState( void)
{
	return;
}

Nat32 CS2InstallerStub_Priv::plfres_ConvertStateToResourceid(int State)
{
	return 0;
}

void CS2InstallerStub_Priv::plfres_RequestResource(Nat32 resid)
{
}



/*intf: ISvcVideoControl3*/

#ifndef __cplusplus

int CS2InstallerStub_Priv::vctl_iPresent()
{
	return 1;
}
#endif

void CS2InstallerStub_Priv::vctl_Set2(int property, int value1, int value2)
{
	return;
}

 void CS2InstallerStub_Priv::vctl_Set(int property, int value)
 {
 	return;
 }
 int CS2InstallerStub_Priv::vctl_Get(int property)
 {
 	return 0;
 }
 void CS2InstallerStub_Priv::vctl_Set3(int property, int value1, int value2)
 {
 	return;
 }
 Bool CS2InstallerStub_Priv::vctl_IsAvailable   (int property, int value)
 {
 	return FALSE;
 }
 Bool CS2InstallerStub_Priv::vctl_IsControllable(int property, int value)	
 {
 	return FALSE;
 }


 /* Interfaces from IMemoryOperations.id */
int CS2InstallerStub_Priv::memo_memcmp   ( void * ptr1, void * ptr2, int num ) 
{
	return 0;
}

int CS2InstallerStub_Priv::memo_memcmpRom( void * ptr1, void ROM * ptr2, int num ) 
{
	return 0;
}

void * CS2InstallerStub_Priv::memo_memcpy   ( void * dest, void * source, int num ) 
{
	return NULL;
}

void * CS2InstallerStub_Priv::memo_memcpyRom( void * dest, void ROM * source, int num ) 
{
	return NULL;
}

void * CS2InstallerStub_Priv::memo_memmove  ( void * dest, void * source, int num ) 
{
	return NULL;
}

void * CS2InstallerStub_Priv::memo_memset   ( void * ptr, int val, int num )
{
	return memset(ptr,val,num);
}


/* Interfaces from IString.id */

int CS2InstallerStub_Priv::str_strcmpRom ( char     * str1, char ROM * str2 ) 
{
	return 0;
}

int CS2InstallerStub_Priv::str_strncmp   ( char     * str1, char     * str2, int num) 
{
	return 0;
}

int CS2InstallerStub_Priv::str_strncmpRom( char     * str1, char ROM * str2, int num) 
{
	return 0;
}


int CS2InstallerStub_Priv::str_strlenRom ( char ROM * str ) 
{
	return 0;
}


char * CS2InstallerStub_Priv::str_strcpyRom ( char     * dest, char ROM * source ) 
{
	return NULL;
}

char * CS2InstallerStub_Priv::str_strncpy   ( char     * dest, char     * source, int num ) 
{
	return NULL;
}

char * CS2InstallerStub_Priv::str_strncpyRom( char     * dest, char ROM * source, int num ) 
{
	return NULL;
}


char * CS2InstallerStub_Priv::str_strcatRom ( char     * dest, char ROM * source ) 
{
	return NULL;
}

char * CS2InstallerStub_Priv::str_strncat   ( char     * dest, char     * source, int num ) 
{
	return NULL;
}

char * CS2InstallerStub_Priv::str_strstr    ( char     * book, char     * word ) 
{
	return NULL;
}

char * CS2InstallerStub_Priv::str_strchr    ( char     * book, int letter ) 
{
	return NULL;
}


int CS2InstallerStub_Priv::str_strcmp    ( char     * str1, char     * str2 )
{
	return strcmp(str1,str2);
}
int CS2InstallerStub_Priv::str_strlen    ( char     * str )
{
	return strlen(str);
}
char * CS2InstallerStub_Priv::str_strcat    ( char     * dest, char     * source )
{
	return strcat(dest,source);
}
char * CS2InstallerStub_Priv::str_strcpy    ( char     * dest, char     * source )
{
	return strcpy(dest,source);
}


/* Interfaces from IPlfApiTsDmxAbstractEx.id */
FResult CS2InstallerStub_Priv::plfdmx_IsRequestAllowed( int winid  , Bool* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_RequestFilter( int winid, int pid, int BufferSize, int CrcMode, Bool ContinuousMode, Nat32 cookie, int FilterDepth, Nat8 *ModeArray, Nat8 *MatchArray, Nat8 *MaskArray, Nat32* error, Nat32* retval) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_UpdateFilter ( int winid, Nat32 subscrId, int FilterDepth, Nat8 *ModeArray, Nat8 *MatchArray, Nat8 *MaskArray, Nat32* error, Bool* retval) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_CancelFilter( int winid , Nat32 subscrId, Nat32* error) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_RequestListFilter( int winid, int pid, int BufferSize, int CrcMode, Bool ContinuousMode, Nat32 timeout, Nat32 listLength, Nat32 cookie, int FilterDepth, Nat8 *ModeArray,Nat8 *MatchArray, Nat8 *MaskArray, Nat32* error, Nat32* retval) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_UpdateListFilter ( int winid, Nat32 subscrId, int FilterDepth, Nat8 *ModeArray, Nat8 *MatchArray, Nat8 *MaskArray, Nat32* error, Bool* retval) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_CancelListFilter( int winid  , Nat32 subscrId, Nat32* error) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_RequestPes( int winid, int pid, int BufferSize, Nat32 cookie, int FilterDepth, Nat8 *MatchArray, Nat8 *MaskArray, Nat32* error, Nat32* retval) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_CancelPes( int winid,  Nat32 subscrId, Nat32* error) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_RequestPesList( int winid, int pid, int BufferSize, Nat32 timeout, Nat32 listLength, Nat32 cookie, int FilterDepth, Nat8 *MatchArray, Nat8 *MaskArray, Nat32* error, Nat32* retval) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_CancelPesList( int winid  , Nat32 subscrId, Nat32* error) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_IsVideoStreamTypeSupported  ( int winid  , int streamtype, Bool* supported, Nat32* error  ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_SetVideoStreamType          ( int winid  , int streamtype, Nat32* error  ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_GetVideoStreamType          ( int winid  , int* streamtype, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_IsAudioStreamTypeSupported  ( int winid  , int streamtype, Bool* supported, Nat32* error  ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_SetAudioStreamType          ( int winid  , int streamtype, Nat32* error  ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_GetAudioStreamType          ( int winid  , int* streamtype, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_GetPcrPid( int winid  , Nat16 *pid, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_GetAudioPid( int winid  , Nat16 *pid, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_GetVideoPid( int winid  , Nat16 *pid, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_GetAudioDescriptivePid( int winid  , Nat16 *pid, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_SetPcrPid( int winid  , Nat16 pid, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_SetAudioPid( int winid  , Nat16 pid, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_SetVideoPid( int winid  , Nat16 pid, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_SetAudioDescriptivePid( int winid  , Nat16 pid, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_StopPcrPid( int winid  , Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_StopAudioPid( int winid  , Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_StopVideoPid( int winid  , Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_StopAudioDescriptivePid( int winid  , Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_GetScramblingStatus( int winid  , int MediaType, Nat32* error, int* retval) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_FreeSectionBuffer( int winid  , Nat32 subscrId, Nat32 datacookie, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_FreeListBuffer   ( int winid  , Nat32 subscrId, Nat32 listcookie, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_FreePesBuffer    ( int winid  , Nat32 subscrId, Nat32 datacookie, Nat32* error ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::plfdmx_FreePesListBuffer  ( int winid  , Nat32 subscrId, Nat32 listcookie, Nat32* error ) 
{
	return 0;
}

 void CS2InstallerStub_Priv::pool_Init    (int poolid)
 {
 }

 Address CS2InstallerStub_Priv::pool_Malloc  (int poolid)
{
return NULL;
}

 void CS2InstallerStub_Priv::pool_Free    (int poolid, Address addr)
{
}

int CS2InstallerStub_Priv::srtdb2_GetNoOfRecords      (int tableid                                                        ) 
{
	return 0;
}

void CS2InstallerStub_Priv::srtdb2_Init                (int tableid                                                        ) 
{
	return;
}

Bool CS2InstallerStub_Priv::srtdb2_Insert              (int tableid, Nat32 PrimaryKey, Nat32 SecondaryKey, Nat32 TeritiaryKey, Nat32 QuaternaryKey, Address data   ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::srtdb2_Update              (int tableid, Nat32 PrimaryKey, Nat32 SecondaryKey, Nat32 TeritiaryKey, Nat32 QuaternaryKey, Address data   ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::srtdb2_Delete              (int tableid, Nat32 PrimaryKey, Nat32 SecondaryKey, Nat32 TeritiaryKey, Nat32 QuaternaryKey ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::srtdb2_SearchOnPrimaryKey  (int tableid, Nat32 PrimaryKey,    int* from,  int* to ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::srtdb2_SearchOnPrimaryAndSecondaryKey(int tableid, Nat32 PrimaryKey, Nat32 SecondaryKey,  int* from,  int* to) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::srtdb2_SearchOnPrimarySecondaryAndTeritiaryKey(int tableid,Nat32 PrimaryKey,Nat32 SecondaryKey,Nat32 TeritiaryKey,int * from,int * to)
{
	return FALSE;
}


Bool CS2InstallerStub_Priv::srtdb2_QueryOnKey          (int tableid, Nat32 PrimaryKey, Nat32 SecondaryKey,  Nat32 TeritiaryKey, Nat32 QuaternaryKey, Address data   ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::srtdb2_QueryOnIndex        (int tableid, int   index,      Address data                        ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::srtdb2_SearchOnKey          (int tableid, Nat32 PrimaryKey, Nat32 SecondaryKey, Nat32 TeritiaryKey,  Nat32 QuaternaryKey, int * index ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::srtdb2_SearchOnKey2         (int tableid, Nat32 PrimaryKey, Nat32 SecondaryKey, Nat32 TeritiaryKey,  Nat32 QuaternaryKey, int op,   int * index ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::mpldiv_SubtitlePidFallbackFirstPMT()
{
	return FALSE;
}

/*intf: IHsvLog*/
#ifndef __cplusplus

int CS2InstallerStub_Priv::log_iPresent()
{
	return 1;
}
#endif

void CS2InstallerStub_Priv::log_Error(int prio,     int errid)
{
	return;
}

void CS2InstallerStub_Priv::log_Trace(int callerid, int arg1, int arg2)
{
	return;
}

#ifndef __cplusplus

int CS2InstallerStub_Priv::main (int argc, const char* argv[])
{
	return 0;
}
void CS2InstallerStub_Priv::__libc_csu_init()
{
	return;
}

void CS2InstallerStub_Priv::__libc_csu_fini()
{
	return;
}

int CS2InstallerStub_Priv::compids_iPresent()
{
	return 1;
}
#endif

/* Interfaces from IHsvChanlibPosixLight.id */

void * CS2InstallerStub_Priv::pgdatrtk_SemCreate( char * key ) 
{
	return NULL;
}

void CS2InstallerStub_Priv::pgdatrtk_SemRelease( void * fildes ) 
{
	return;
}

void CS2InstallerStub_Priv::pgdatrtk_SemAcquire( void * fildes ) 
{
	return;
}

/* Interfaces from IHsvChannelLibSyncEvents.id */
void CS2InstallerStub_Priv::sync_OnInsert(int tableid, Address data) 
{
	return;
}

void CS2InstallerStub_Priv::sync_OnUpdate(int tableid, Address data) 
{
	return;
}

void CS2InstallerStub_Priv::sync_OnDelete(int tableid, Address data) 
{
	return;
}

void CS2InstallerStub_Priv::sync_EnableEvents(Bool status)
{

}

void CS2InstallerStub_Priv::sync_MasterEnableEvents(Bool status)
{

}



/* Interfaces from IHsvEuropeDiversity2.id */
int CS2InstallerStub_Priv::eurdiv_InstallTestStreams(int installationmode, int medium) 
{
	return 0;
}

int CS2InstallerStub_Priv::eurdiv_NoOfVirtualChannelsSupported(int medium) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::eurdiv_ForceLCNSyntax(int medium) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::eurdiv_DefaultStreamPriority(int medium)     /* Name change from StreamPriorityToBeUsed */
{
	return 0;
}

Bool CS2InstallerStub_Priv::eurdiv_IsServiceInstallable(int medium, int ServiceType ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsServiceHidden(int medium, int ServiceType ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_AcceptedStreamType (int medium, HsvAVStreamType StreamType )  /* iVersion= 12 */
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_UpdateChannelName(int medium)  /* New CR brg29mgr#6409 */
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsDbookCountry( void ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsHDSubtitleSupported() 
{
	return FALSE;
}

int CS2InstallerStub_Priv::eurdiv_GetNoOfBackBuffers( int clientId ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::eurdiv_IsMpeg4STBoltOnSupported(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_TripletKey(int medium) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_InstallDuplicateServices(int medium) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_EnableCountryFallbackForLCNSyntax(int medium)  /* iVersion = 11 */
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_EnableONIDFallbackForLCNSyntax(int medium)     /* iVersion = 11 */
{
	return FALSE;
}

int CS2InstallerStub_Priv::eurdiv_GetDefaultScanMode(int medium) 
{
	return 0;
}

Nat16 CS2InstallerStub_Priv::eurdiv_GetNextScan(int medium, int installationmode, Nat16 ScanPreference) 
{
	return 0;
}

Nat8 CS2InstallerStub_Priv::eurdiv_GetAudioPreference(void)       /* Primary or Primary & Secondary */
{
	return 0;
}

Nat8 CS2InstallerStub_Priv::eurdiv_GetSubtitlePreference(void)    /* Primary or Primary & Secondary */
{
	return 0;
}

Bool CS2InstallerStub_Priv::eurdiv_UserPreferredAudioFormat()     /* TRUE if PreferredAudioFormat Menu item is available */
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsBackgroundInstallRequired(int medium) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_SupportLCNVersion2(int medium) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_ParseLCN(int medium, int installationmode) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsPreScanSupported(int medium) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_SupportHDSLCN(int medium) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsServiceAttrbDescSupported(int medium) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsTSRelocatedDescSupported(int medium) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::eurdiv_GetAltSDTType(int medium) 
{
	return 0;
}

Nat8 CS2InstallerStub_Priv::eurdiv_GetAlternateTSLocation(int medium) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::eurdiv_IsAc3AudioSupported(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_StaticTable(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_GetDefaultDigitalInstallStatus(int country) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsMultifeedSupported(void) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::eurdiv_GetViterbiBER(void) 
{
	return 0;
}

int CS2InstallerStub_Priv::eurdiv_DeltaViterbiBER(void) 
{
	return 0;
}

Nat32 CS2InstallerStub_Priv::eurdiv_GetShortInfoCacheSize( void ) 
{
	return 0;
}

int CS2InstallerStub_Priv::eurdiv_GetDeltaSQI() 
{
	return 0;
}

int CS2InstallerStub_Priv::eurdiv_GetDeltaSSI() 
{
	return 0;
}

int CS2InstallerStub_Priv::eurdiv_NonRadioStartPreset(int country, int medium, int numRecords) 
{
	return 0;
}

int CS2InstallerStub_Priv::eurdiv_NonRadioEndPreset(int country, int medium) 
{
	return 0;
}

int CS2InstallerStub_Priv::eurdiv_RadioStartPreset(int country, int medium, int numRecords) 
{
	return 0;
}

int CS2InstallerStub_Priv::eurdiv_RadioEndPreset(int country, int medium) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::eurdiv_IsHDSimulcastSupported() 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_FirstLCNOnlySupported() 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::eurdiv_IsDigiturkPackage(void) 
{
	Bool retval = FALSE;
	Nat32 PackageId = 0;
	
	PackageId = dvbset_GetAttribute(dvbset_AttributePackageId);

	switch (PackageId)
	{
	case	DIGITURK_TURKSAT_PACKAGE_ID:
    case    DIGITURK_EUTELSAT_PACKAGE_ID:
		retval = TRUE;
		break;
	default:
		break;
	}

	//TraceNotice(m,"eurdiv_IsDigiturkPackage : %d", retval);
    return( retval );
}


/* Interfaces from IHsvSatelliteDiversity.id */
Bool CS2InstallerStub_Priv::s2div_IsHomingMuxTuningRequired (int SatelliteId, int CountryId) 
{
	Bool	retVal = FALSE;
	/* This is needed only for below combinations
		1. TurkSat + Turkey
		2. Hotbird + Poland */


	return retVal;
}

void CS2InstallerStub_Priv::s2div_LoadDefaultConnectionType (int CountryId, int *ConnectionType) 
{
	/* Belgium, Netherlands, Luxumbourg, Switzerland Connection type 1.0. DefaultLnb : Universal */
	switch (CountryId)
	{
	case	cids_CountryBelgium:
	case	cids_CountryLuxembourg:
	case	cids_CountryNetherlands:
		*ConnectionType = LnbConnectionDiSeqc1_0;
		break;
	case	cids_CountrySwitzerland:
		*ConnectionType = LnbConnectionDiSeqcMini;
		break;
	default:
		break;
		*ConnectionType = LnbConnectionSingle;
	}

	TraceNotice(m,"s2div_LoadDefaultConnectionType : %d country: %d", *ConnectionType,CountryId);

}

void CS2InstallerStub_Priv::s2div_LoadDefaultLnbType	(int CountryId, int *LnbType) 
{
	/* Belgium, Netherlands, Luxumbourg, Switzerland Connection type 1.0. DefaultLnb : Universal */
	switch (CountryId)
	{
	case	cids_CountryBelgium:
	case	cids_CountryLuxembourg:
	case	cids_CountryNetherlands:
	case	cids_CountrySwitzerland:
		*LnbType = LnbUniversal;
		break;
	default:
		break;
		*LnbType = LnbUniversal;
	}
}

Bool CS2InstallerStub_Priv::s2div_IsBackgroundInstallRequired (void) 
{
	Bool retval = FALSE;
	Nat32 PackageId = 0;
	
	PackageId = dvbset_GetAttribute(dvbset_AttributePackageId);
	if( 1 == PackageId || FRANSAT_PACKAGE_ID == PackageId)
	{
		retval = TRUE;
	}
	
	PrintfNotice("%s PackageId = %d retval %d",__FUNCTION__, (int)PackageId, retval);
    return( retval );
}

Bool CS2InstallerStub_Priv::s2div_PerformReinstallInSemiStandby (void) 
{
	Bool retval = FALSE;
	Nat32 PackageId = 0;
    HsvLnbSettings  LnbSettings;
	int count, loopcount;

	/* As per 2k14: Check package is Eutelsat and at least one MDU is detected */
	PackageId = dvbset_GetAttribute(dvbset_AttributePackageId);
	if (PackageId == DIGITURK_EUTELSAT_PACKAGE_ID)
	{	
		dvbset_GetLnbSettings (&LnbSettings);
		count =  ((LnbSettings.ConnectionType == LnbConnectionSingle) ? 1: ((LnbSettings.ConnectionType == LnbConnectionDiSeqcMini) ? 2 : 4 ));
		for (loopcount = 0; (loopcount < count); loopcount++)
		{
			switch (LnbSettings.LnbSettings[loopcount].LnbType) 
			{
				case	LnbMdutype1:
				case	LnbMdutype2:
				case	LnbMdutype3:
				case	LnbMdutype4:
				case	LnbMdutype5:
					retval = TRUE;
					break;
				default:
					break;
			}
		}		
	}
	
    return( retval );
}



/* Interfaces from IHsvWindowDestinationMap.id */
int CS2InstallerStub_Priv::wnddest_GetWindowId(HsvDestination dest) 
{
	return 0;
}

int CS2InstallerStub_Priv::wnddest_GetAudioNodeId(HsvDestination dest) 
{
	return 0;
}

int CS2InstallerStub_Priv::wnddest_GetMonitorWindow() 
{
	return 0;
}

int CS2InstallerStub_Priv::wnddest_GetWindowType(int winid) 
{
	return 0;
}

HsvDestination CS2InstallerStub_Priv::wnddest_GetDestinationForWindow(int windowid) 
{
	return (HsvDestination)0;
}


/* Interfaces from IPlfApiSigStrengthMeas.id */
FResult CS2InstallerStub_Priv::vssm_GetSigStrengthRange( int winid , Nat32* MinStrength, Nat32* MaxStrength, Nat32* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::vssm_Start( int winid , Bool* Avail, Nat32* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::vssm_Stop( int winid , Bool* vssm_Stopped, Nat32* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::vssm_GetMeasValid( int winid , Bool* Valid, Nat32* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::vssm_GetSigStrength( int winid , Nat32* Strength, Nat32* retval ) 
{
	return 0;
}

/* Interfaces from IPlfApiSigStrengthMeas.id */
FResult CS2InstallerStub_Priv::qssm_GetSigStrengthRange( int winid , Nat32* MinStrength, Nat32* MaxStrength, Nat32* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::qssm_Start( int winid , Bool* Avail, Nat32* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::qssm_Stop( int winid , Bool* qssm_Stopped, Nat32* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::qssm_GetMeasValid( int winid , Bool* Valid, Nat32* retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::qssm_GetSigStrength( int winid , Nat32* Strength, Nat32* retval ) 
{
	return 0;
}

/* Interfaces from ISvcAudioControl4ExEx.id */
int CS2InstallerStub_Priv::actl3_Get( int audioProperty ) 
{
	return 0;
}

void CS2InstallerStub_Priv::actl3_Set( int audioProperty, int value ) 
{
	return;
}

void CS2InstallerStub_Priv::actl3_Set2( int audioProperty, int value1,int value2) 
{
	return;
}

int CS2InstallerStub_Priv::actl3_Get2(int audioproperty, int value1 ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::actl3_IsAvailable(    int audioProperty, int value ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::actl3_IsControllable( int audioProperty, int value ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::actl3_IsAvailable2( int audioProperty, int value1,int value2 ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::actl3_IsControllable2( int audioProperty, int value1,int value2 ) 
{
	return FALSE;
}


/* Interfaces from IHsvProgramSelection2.id */
FResult CS2InstallerStub_Priv::pgsel_SelectProgram(HsvSource Source, HsvChannel ChannelNo, HsvDestination Dest,int TypeOfSelection,int Priority) 
{
	return 0;
}

void CS2InstallerStub_Priv::pgsel_GetCurrentProgram(HsvDestination Dest ,HsvSource *Source, HsvChannel *ChannelNo) 
{
	int PresetNumber = 0;
	
	TraceNotice(m,"###### [%s] [%d] \n",__FUNCTION__,__LINE__); 
	globalsettings_GetValuesFromGlobalSettings(0,&PresetNumber);
	TraceNotice(m,"Value got in Native is %d ", PresetNumber);
	
	ChannelNo->Type = (AppApiChannelType)3;
	ChannelNo->Channel.Digit = PresetNumber;
	
	return;

	
}

void CS2InstallerStub_Priv::pgsel_GetActualCurrentProgram(HsvDestination Dest ,HsvSource *Source, HsvChannel *ChannelNo) 
{
	return;
}

FResult CS2InstallerStub_Priv::pgsel_IsSelectionAllowed(HsvSource Source, HsvChannel ChannelNo, HsvDestination Dest) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::pgsel_IsSelectionInProgress(void) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::pgsel_GetLastRequestedProgram(HsvDestination Dest ,HsvSource *Source, HsvChannel *ChannelNo) 
{
	return;
}

void CS2InstallerStub_Priv::pgsel_GetLastActualRequestedProgram(HsvDestination Dest ,HsvSource *Source, HsvChannel *ChannelNo) 
{
	return;
}

FResult CS2InstallerStub_Priv::pgsel_SetAttribute(int attribute, int value ) 
{
	return 0;
}

void CS2InstallerStub_Priv::pgsel_GetAttribute(int attribute ,int *value) 
{
	return;
}

Bool CS2InstallerStub_Priv::pgsel_IsTuningRequired(HsvSource Source, HsvChannel ChannelNo, HsvDestination Dest,int TypeOfSelection) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::pgsel_GetActualTypeOfSelection(HsvDestination Dest) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::pgsel_IsProgramSelectionRequired(HsvChannel channelno) 
{
	return FALSE;
}

/* Interfaces from IProdApiSystemStateObserverExExExEx.id */
Bool CS2InstallerStub_Priv::observer_IsRecordingOngoing( void ) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::observer_GetMultiviewState( Bool* ena ) 
{
	return;
}

int CS2InstallerStub_Priv::observer_GetSystemDisabledEvents( void ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::observer_IsTimeShiftActive( void ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::observer_IsSkypeActive( void ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::observer_IsTopmenubarActive( void ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::observer_IsDmsPlaybackOngoing( void ) 
{
	return FALSE;
}

/* Interfaces from IPlfApiPhysDevice.id */

FResult CS2InstallerStub_Priv::usbms_IsInitializationDone(int winid ,Bool *done ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::usbms_GetDeviceList(int winid ,int phystype,Nat32 *items ,Nat32 *numitems ,int *retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::usbms_GetDeviceName(int winid ,Nat32 physid,char *name ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::usbms_GetType(int winid ,Nat32 physid,int *phystype) 
{
	return 0;
}


/* Interfaces from IPlfApiStorageDevice.id */

FResult CS2InstallerStub_Priv::recdev_IsInitializationDone(int winid ,Bool *done ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_IsStoragePrepared(int winid ,int conttype,Bool *prepared ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_PrepareStorage(int winid ,Nat32 id,int conttype,int *retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetContainerList(int winid ,int conttype,Nat32 physid,Nat32 *items ,Nat32 *numitems ,int *retval ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetSize(int winid ,Nat32 id,Nat64 *size ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetFreeSize(int winid ,Nat32 id,Nat64 *size ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetWriteProtected(int winid ,Nat32 contid,Bool *protect ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetPath(int winid ,Nat32 contid,char *path ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetStorageName(int winid ,Nat32 contid,char *name ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetUniqueID(int winid ,Nat32 contid,Nat64 *uid ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetType(int winid ,Nat32 contid,int *conttype ) 
{
	return 0;
}

FResult CS2InstallerStub_Priv::recdev_GetPhysID(int winid ,Nat32 contid,Nat32 *physid ) 
{
	return 0;
}



/* Interfaces from ICeIsTpHostRtk2.id */
int CS2InstallerStub_Priv::tprtk_TaskCreate( char* name, int priority, int stacksize, FunctionInt entry, int param ) 
{
	return 0;
}

void CS2InstallerStub_Priv::tprtk_TaskDelete( int task ) 
{
	return;
}

Bool CS2InstallerStub_Priv::tprtk_TaskExists( int task ) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::tprtk_TaskJoin( int task ) 
{
	return;
}

int CS2InstallerStub_Priv::tprtk_TaskGetCurrent( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::tprtk_TaskSetPriority( int task, int prio ) 
{
	return;
}

int CS2InstallerStub_Priv::tprtk_TaskGetPriority( int task ) 
{
	return 0;
}

void CS2InstallerStub_Priv::tprtk_TaskSleep( int timeout ) 
{
	return;
}

int CS2InstallerStub_Priv::tprtk_SemCreateBinary( int initval ) 
{
	return 0;
}

int CS2InstallerStub_Priv::tprtk_SemCreateCounting( int initcount ) 
{
	return 0;
}

void CS2InstallerStub_Priv::tprtk_SemDelete( int sema ) 
{
	return;
}

void CS2InstallerStub_Priv::tprtk_SemWait( int sema ) 
{
	return;
}

Bool CS2InstallerStub_Priv::tprtk_SemTimedWait( int sema, int timeout ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::tprtk_SemTryWait( int sema ) 
{
	return FALSE;
}

void CS2InstallerStub_Priv::tprtk_SemSignal( int sema ) 
{
	return;
}

int CS2InstallerStub_Priv::tprtk_MutexCreate( void ) 
{
	return 0;
}

void CS2InstallerStub_Priv::tprtk_MutexDelete( int mutex ) 
{
	return;
}

void CS2InstallerStub_Priv::tprtk_MutexLock( int mutex ) 
{
	return;
}

void CS2InstallerStub_Priv::tprtk_MutexUnlock( int mutex ) 
{
	return;
}

void CS2InstallerStub_Priv::tprtk_EventSend( int task, Nat32 event ) 
{
	return;
}

Nat32 CS2InstallerStub_Priv::tprtk_EventReceive( Nat32 eventmask, Bool waitall, int timeout ) 
{
	return 0;
}

void CS2InstallerStub_Priv::tprtk_EventClear( Nat32 eventmask )                                        
{
	return;
}

int CS2InstallerStub_Priv::tprtk_MsgQCreate( int maxmsg, int maxmsglength ) 
{
	return 0;
}

void CS2InstallerStub_Priv::tprtk_MsgQDelete( int msgq ) 
{
	return;
}

int CS2InstallerStub_Priv::tprtk_MsgQGetMessageCount( int msgq ) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::tprtk_MsgQSend( int msgq, Address buffer, int length, int timeout ) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::tprtk_MsgQReceive( int msgq, Address buffer, int maxlength, int timeout ) 
{
	return 0;
}

Nat32 CS2InstallerStub_Priv::tprtk_TimeGetCurrent( void ) 
{
	return 0;
}

Nat32 CS2InstallerStub_Priv::tprtk_TimeAdd( Nat32 a, Nat32 b ) 
{
	return 0;
}

Nat32 CS2InstallerStub_Priv::tprtk_TimeSubtract( Nat32 a, Nat32 b ) 
{
	return 0;
}

/* Interfaces from IHsvSdmDiv.id */
int CS2InstallerStub_Priv::div_NoOfVirtualChannels(int medium) 
{
	return 0;
}

Bool CS2InstallerStub_Priv::div_ForceLCNSyntax( int medium ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::div_EnableCountryFallbackForLCNSyntax( int medium ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::div_EnableONIDFallbackForLCNSyntax( int medium ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::div_AcceptedStreamType( int medium, HsvAVStreamType StreamType ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::div_IsMpeg4STBoltOnSupported(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::div_IsAc3AudioSupported(void) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::div_ReapplyChildLockOnEventChange( void ) 
{
	return FALSE;
}

Bool CS2InstallerStub_Priv::div_IsAVCDescriptorSupported(void) 
{
	return FALSE;
}

int CS2InstallerStub_Priv::plfdvbs_getParams( HsvDvbSParams *par )
{
	return 0;
}

int CS2InstallerStub_Priv::plfdvbs_configureLNB(HsvDvbSLNBConfig lnbcfg, HsvDvbSCustomLNBConfig CustomLnbConfig)
{
	return 0;
}


int CS2InstallerStub_Priv::plfdvbs_configureUnicable(HsvDvbSUnicableConfig uccfg)
{
	return 0;
}

int CS2InstallerStub_Priv::plfdvbs_setPolarization(int polarization)
{
	return 0;
}

int CS2InstallerStub_Priv::plfdvbs_setSymbolRate(int srdetectmode, int symbolrate)
{
	return 0;
}


int CS2InstallerStub_Priv::plfdvbs_setPLP(Nat8 plpid)
{
	return 0;
}

int CS2InstallerStub_Priv::plfdvbs_setBand(int band)
{
	return 0;
}

int CS2InstallerStub_Priv::plfdvbs_setLNBConnectionType(int connectiontype)
{
	return 0;
}

int CS2InstallerStub_Priv::plfdvbs_setSatIPParams(int modsys,int modtype,int RollOff, int fec, int pilots)
{
	return 0;
}

int CS2InstallerStub_Priv::plftune_tune(int freq, Bool finetune)
{
	return 0;
}

int CS2InstallerStub_Priv::plftune_getFreq(int *freq)
{
	return 0;
}

int CS2InstallerStub_Priv::plftune_scanStart(int startfreq, int endfreq, Bool scanforward)
{
	return 0;
}

int CS2InstallerStub_Priv::plftune_scanAbort(void)
{
	return 0;
}

int CS2InstallerStub_Priv::plftune_scanNext(void)
{
	return 0;
}

/*************************************************************************
 *                                                                       *
 * Character table Id's (from sub/ceinfra/prod/ceisjag/ceisjag_mwchar.c) *
 *                                                                       *
 * tableid     meaning                       name                        *
 * -----------------------------------------------------------           *
 *   0x00     ISO/IEC 6937[9](1994)      Latin alphabet                  *
 *   0x01     ISO/IEC 8859-5[5](1988)    Latin/Cyrillic alphabet         *
 *   0x02     ISO/IEC 8859-6[5](1987)    Latin/Arabic alphabet           *
 *   0x03     ISO/IEC 8859-7[5](1987)    Latin/Greek alphabet            *
 *   0x04     ISO/IEC 8859-8[5](1988)    Latin/Hebrew alphabet           *
 *   0x05     ISO/IEC 8859-9[5]          Latin alphabet number 5         *
 *   0x06     ISO/IEC 8859-2             Latin alphabet number 2         *
 *   0x11     ISO/IEC 10646-1            UCS-2                           *
 *   0x20-0xFF --> Default character coding (Latin alphabet)             *
 *                                                                       *
 *************************************************************************/

Bool CS2InstallerStub_Priv::IsM7Package (int PackageId)
{
	Bool	RetVal = FALSE;
	switch (PackageId)
	{
	case	CANALDIGITAAL_SD_BOUQUET_ID:
	case	CANALDIGITAAL_HD_BOUQUET_ID:
	case	TVVLAANDEREN_SD_BOUQUET_ID:
	case	TVVLAANDEREN_HD_BOUQUET_ID:
	case	TELESAT_BEL_BOUQUET_ID:
	case	TELESAT_LUX_BOUQUET_ID:
	case	AUSRTIA_BOUQUET_ID:
	case	CZECH_REPUBLIC_BOUQUET_ID:
	case	SLOVAK_REPUBLIC_BOUQUET_ID:
		RetVal = TRUE;
		break;
	default:
		break;
	}
	return RetVal;
}
int CS2InstallerStub_Priv::utildiv_DefaultCharacterTable(void)/*CR-AN-67883*/
{
    int l_retval = 0;
    int  country =  sysset_GetInstallCountry();
	switch( country )
    {
		case cids_CountryTurkey:
		case cids_CountryAustria:	
		case cids_CountryBelgium:
		case cids_CountryNetherlands:	
		case cids_CountryLuxembourg:
		l_retval=5;//ISO/IEC 8859-9
		break;
		case cids_CountryPoland:
		l_retval = 6;	//ISO/IEC 8859-2
		break;
		case cids_CountryGermany:	
		l_retval = IAppApiMultiLingualStringConversion_TableISO8859_1;	// ISO/IEC 8859-1
		break;
		
		case IHsvLanguageIds2_LangRussian:// Added For Tricolor Region name Implementation
			 l_retval = 1;   // ISO/IEC 8859-5
		break;
		default:
		l_retval = 0;//ISO/IEC 6937 default value
		break;
	}	
	//TraceNotice(m,"dvbset_DefaultCharacterTableSatellite : retval: %d", l_retval);
	return l_retval;											
}

Bool CS2InstallerStub_Priv::utildiv_ForceCharacterTable(void)
{
    Bool l_retval = FALSE;
    int  country =  sysset_GetInstallCountry();

    switch( country )
    {
    case cids_CountryHungary:
    case cids_CountrySlovenia:   /*   brg36mgr#68735  */ 
        l_retval = FALSE;
        break;
    default:
        l_retval = FALSE;
        break;
    }

    return (l_retval);

		
}

int CS2InstallerStub_Priv::utildiv_RegionalCharacterTable(void)
{
    int l_retval = 0;
    int country =  sysset_GetInstallCountry();
    
    switch( country )
    {
    case cids_CountryHungary:
    case cids_CountrySlovenia:   /*   brg36mgr#68735  */ 
        l_retval = 6;
        break;
    default:
        l_retval = utildiv_DefaultCharacterTable();
        break;
    }    

    return (l_retval);
	
}

int CS2InstallerStub_Priv::ConvertToSTAudioType(int stmType)
{
    int retval = plfdmx_StreamTypemp2a; //change default value to mpeg2
    switch(stmType & 0x27000000) 
    {
        case HSV_MPEG_AUDIO_TYPE:
            {
                retval = plfdmx_StreamTypemp2a;
                break;
            }
        case HSV_AC3_TYPE:
            {
                retval = plfdmx_StreamTypeac3;
                break;
            }
        case HSV_HEAAC_TYPE:
            {

                {
                    retval = plfdmx_StreamTypeheaac;
                }
                break;
            }
        case HSV_AAC_TYPE:
            {

                {
                    retval = plfdmx_StreamTypeaac;
                }
                break;
            }
        case HSV_AC3PLUS_TYPE:
            {
                {
                    retval = plfdmx_StreamTypeddplus;
                }
                break;
            }
        default:
            {
                TraceNotice(m,"Audio StmType Invalid, hence use default value mpeg2");
                break;
            }
    }
    
    return retval;
}
int CS2InstallerStub_Priv::ConvertToSTVideoType(int stmType)
{
    int retval = plfdmx_StreamTypemp2v; //make default as mpeg2 as sending invalid anyway doesnt help.
  
    switch(stmType)
    {
        case Hsv_ISOIEC_11172_STREAM_TYPE_VIDEO:
        case Hsv_ISOIEC_13818_2_STREAM_TYPE_VIDEO:
            {
                retval = plfdmx_StreamTypemp2v;
                break;
            }
        case Hsv_H264_STREAM_TYPE_VIDEO:
            {
                {
                    retval = plfdmx_StreamTypeh264;
                }
                break;
            }
        default:
            {
                break;
            }
    }
	
    return retval;
}
