/**********************************************************************
 *
 *   C Source:       hsvdvbcins_m.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    nareshj %
 *   %date_created:  Sat May 12 18:11:35 2012 %
 *
 **********************************************************************/
#include "_hsvdvbcins_m.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbcins_m")

#include "hsvdvbcins.h"

/**************************************************************************
  1.HKK:: Scan Mode doesnt make sense in ManualInstall
 **************************************************************************/

/**************************************************************************
 * Macros and types
 **************************************************************************/

 
#ifndef __cplusplus

#else

#endif



 








/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/













/****************************************************************************
 * Static variables
 ****************************************************************************/
Pump CHsvDvbCInstallation_m_Priv::s__mInstallPump;

t_DVBCStatus CHsvDvbCInstallation_m_Priv::s__mDvbcStatus;




const FunctionNat32 CHsvDvbCInstallation_m_Priv::StateEventMatrix[][StMax] = 
{                       /*StIdle            StPreScan       StQuick         StFull          StGrid          StScansDone*/
    /*EvStart*/             {FNADDR(FuncStart),         NULL,            	NULL,          			NULL,           		NULL,           		NULL},
    /*EvPreScanDone*/       {NULL,              	FNADDR(FuncPreScanDone), NULL,          		NULL,          	 		NULL,           		NULL},
    /*EvQuickDone*/         {NULL,              	NULL,            		FNADDR(FuncQuickDone), 	NULL,           		NULL,           		NULL},
    /*EvFullDone*/          {NULL,              	NULL,            		NULL,          			FNADDR(FuncFullDone),   NULL,           		NULL},
    /*EvGridDone*/          {NULL,              	NULL,            		NULL,          			NULL,           		FNADDR(FuncGridDone),   NULL},
    /*EvScansDone*/         {NULL,              	NULL,            		NULL,          			NULL,           		NULL,           		FNADDR(FuncScansDone)},
    /*EvStop*/              {NULL,              	FNADDR(FuncPreScanStop), FNADDR(FuncQuickStop), FNADDR(FuncFullStop),   FNADDR(FuncGridStop),   NULL},
};


/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/
void CHsvDvbCInstallation_m_Priv::PumpHandler(int event, Nat32 param )
{
    if(StateEventMatrix[event][mDvbcStatus.State] != NULL)
    {
		FPCALL(StateEventMatrix[event][mDvbcStatus.State])(param);
    }
    else
    {
        TraceDebug(m,"Ignored event = %d, state = %d",event,mDvbcStatus.State);
    }
}
void CHsvDvbCInstallation_m_Priv::FuncStart(Nat32 param)
{
    /* Scan Mode doesnt make sense in MANUAL_INSTALL */
    mDvbcStatus.ScanMode = idvbset_GetAttribute(CURRENT_MODE, rins_AttributeScanMode);
    if(MANUAL_INSTALL)
    {
        mDvbcStatus.ScanMode = rins_FullScan;
        mDvbcStatus.State = StFull;
        TraceDebug(m,"Manual Install Started: Calling fullScan");
        ifull_Initialise();
        ifull_StartDigitalTuning(param);
    }
    else
    {
        if(PRE_INSTALL) /*prescan installation mode*/ 
        {
            mDvbcStatus.State = StPreScan;
            iprescan_Initialise();
            iprescan_StartDigitalScan();
        }    
        else if(mDvbcStatus.ScanMode == rins_QuickScan)
        {
            mDvbcStatus.State = StQuick;
            iquick_Initialise();
            iquick_StartDigitalScan();
        }
        else if(mDvbcStatus.ScanMode == rins_GridScan)
        {
            mDvbcStatus.State = StGrid;
            igrid_Initialise();
            igrid_StartDigitalScan();

        }
        else
        {        
            mDvbcStatus.State = StFull;
            ifull_Initialise();
            ifull_StartDigitalScan();
        }
    }
}
void CHsvDvbCInstallation_m_Priv::FuncPreScanDone(Nat32 param)
{
    mDvbcStatus.State = StScansDone;
    pmp_PmpSend(mInstallPump, EvScansDone, (Nat32)param);
}
void CHsvDvbCInstallation_m_Priv::FuncQuickDone(Nat32 param)
{
    /* In case a full scan needs to be trigerred after a quick scan then this function has a major role 
       Else just goto ScansDone to indicate the completion of all scans */
    /* pavan: check the status and do further scans if required */
    mDvbcStatus.State = StScansDone;
    pmp_PmpSend(mInstallPump, EvScansDone, (Nat32)param);
}
void CHsvDvbCInstallation_m_Priv::FuncFullDone(Nat32 param)
{
    mDvbcStatus.State = StScansDone;
    if( (param == ifullN_EventScanFailed) && (eurdiv_GetDVBCMode() != eurdiv_ScanDVBCLite) )
    {
        insN_OnEvent(insN_EventChannelNotFound, 0);
    }
    pmp_PmpSend(mInstallPump, EvScansDone, (Nat32)param);
}
void CHsvDvbCInstallation_m_Priv::FuncGridDone(Nat32 param)
{
    mDvbcStatus.State = StScansDone;
    pmp_PmpSend(mInstallPump, EvScansDone, (Nat32)param);
}
void CHsvDvbCInstallation_m_Priv::FuncScansDone(Nat32 param)
{
    if( (param == iquickN_EventScanStopped)   || (param == ifullN_EventScanStopped)
            || (param == igridN_EventScanStopped) || (param == iprescanN_EventScanStopped) )
    {
        insN_OnEvent(insN_EventInstallationStopped,0);
    }
    else if((param == iquickN_EventScanCompleted) || (param == ifullN_EventScanCompleted) || (param == igridN_EventScanCompleted))
    {
        if(AUTO_INSTALL || UPDATE_INSTALL)
        {
            idataacq_ResetBackgroundInstall();
        }
        TraceDebug(m,"Both Scans done\n");
        insN_OnEvent(insN_EventInstallationCompleted,0);
    }
    else  if( (param != ifullN_EventScanFailed) || (param != igridN_EventScanFailed) || (eurdiv_GetDVBCMode() != eurdiv_ScanDVBCLite) ) /* iprescanN_EventScanCompleted */
    {
        insN_OnEvent(insN_EventInstallationCompleted,0);
    }
    mDvbcStatus.State = StIdle;
}
void CHsvDvbCInstallation_m_Priv::FuncPreScanStop(Nat32 param)
{
    UNUSED(param);
    if(mDvbcStatus.State == StPreScan)
    {
        iprescan_StopDigitalScan();
    }
    else
    {
        TraceDebug(m,"%s:State = %d",__FUNCTION__,mDvbcStatus.State);
    }
}
void CHsvDvbCInstallation_m_Priv::FuncQuickStop(Nat32 param)
{
    UNUSED(param);
    if(mDvbcStatus.State == StQuick)
    {
        iquick_StopDigitalScan();
    }
    else
    {
        TraceDebug(m,"%s:State = %d",__FUNCTION__,mDvbcStatus.State);
    }
}
void CHsvDvbCInstallation_m_Priv::FuncFullStop(Nat32 param)
{
    UNUSED(param);
    if(mDvbcStatus.State == StFull)
    {
        ifull_StopDigitalScan();
    }
    else
    {
        TraceDebug(m,"%s:State = %d",__FUNCTION__,mDvbcStatus.State);
    }
}
void CHsvDvbCInstallation_m_Priv::FuncGridStop(Nat32 param)
{
    UNUSED(param);
    if(mDvbcStatus.State == StGrid)
    {
        igrid_StopDigitalScan();
    }
    else
    {
        TraceDebug(m,"%s:State = %d",__FUNCTION__,mDvbcStatus.State);
    }
}

/***************************
  provides IHsvPower
 ****************************/
void CHsvDvbCInstallation_m_Priv::pow_Init()
{
    mInstallPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE, "hsvdvbcins_m_pmp");
    isetpow_Init();
    iprescanpow_Init();
    iquickpow_Init();
    ifullpow_Init();
    igridpow_Init();
    iacqpow_Init();
    mDvbcStatus.State = StIdle;
}

void CHsvDvbCInstallation_m_Priv::pow_TurnOn()
{
    isetpow_TurnOn();
    iprescanpow_TurnOn();
    iquickpow_TurnOn();
    ifullpow_TurnOn();
    igridpow_TurnOn();
    iacqpow_TurnOn();
}

void CHsvDvbCInstallation_m_Priv::pow_TurnOff()
{
    isetpow_TurnOff();
    iprescanpow_TurnOff();
    iquickpow_TurnOff();
    ifullpow_TurnOff();
    igridpow_TurnOff();
}

/**************************************
  provides IHsvInstallationExExEx
 ***************************************/

FResult CHsvDvbCInstallation_m_Priv::ins_StartInstallation(int source, int ptc, int mode)
{
    UNUSED(source);
    UNUSED(mode);
    FResult retval = hsverr_Ok;
    /* UseCase Selection is already made. */
    if(AUTO_INSTALL || UPDATE_INSTALL || MANUAL_INSTALL || PRE_INSTALL)
    {
        pmp_PmpSend(mInstallPump, EvStart, ptc);
    }
    else
    {
        retval = hsverr_InstallationModeNotSupported;
    }
    return retval;
}
FResult CHsvDvbCInstallation_m_Priv::ins_StopInstallation()
{
    FResult retval = hsverr_Ok;
    if((mDvbcStatus.State == StQuick) || (mDvbcStatus.State == StFull) || (mDvbcStatus.State == StGrid) ||(mDvbcStatus.State == StPreScan))
    {
        TraceDebug(m,"%s",__FUNCTION__);
        pmp_PmpSend(mInstallPump, EvStop, (Nat32)NULL);
    }
    else
    {
        TraceDebug(m,"%s",__FUNCTION__);
        retval = hsverr_InstallationNotInProgress;
    }
    return retval;
}
int CHsvDvbCInstallation_m_Priv::ins_GetNumberOfDigitalChannelsFound()
{
    return idataacq_GetNumberOfDigitalChannelsFound();
}
int CHsvDvbCInstallation_m_Priv::ins_GetNumberOfDigitalChannelsRemoved()
{
    ASSERT(!" Wrong inteface call");
    return 0;
}

#ifndef __cplusplus

int CHsvDvbCInstallation_m_Priv::ins_GetNumberOfChannels( int servicetype )
{
    return idataacq_GetNumberOfChannels(servicetype);
}
#endif


int CHsvDvbCInstallation_m_Priv::ins_GetInstallationMode()
{
    return mDvbcStatus.ScanMode;
}

FResult CHsvDvbCInstallation_m_Priv::ins_StoreWeakSignalInstallationChannel (void)
{
    if(mDvbcStatus.State == StFull)
    {
        ifull_StoreWeakSignalInstallationChannel();
        mDvbcStatus.State = StIdle;
        return TRUE;
    }
    else if(mDvbcStatus.State == StGrid)
    {
        igrid_StoreWeakSignalInstallationChannel();
        mDvbcStatus.State = StIdle;
        return TRUE;
    }
    else
    {
        ASSERT(!" This can be called in Full scan mode only");
        return FALSE;
    }
}

#ifndef __cplusplus

HsvChannel CHsvDvbCInstallation_m_Priv::ins_GetPresetSearchingFor( void ) 
{
    HsvChannel dummyChannel;
    dummyChannel.Type = HsvUnknown;
    dummyChannel.Ptc = HsvUnknownPtc;
    return dummyChannel;
}


HsvChannel CHsvDvbCInstallation_m_Priv::ins_GetLastFoundPreset( void )
{
    HsvChannel dummyChannel;
    dummyChannel.Type = HsvUnknown;
    dummyChannel.Ptc = HsvUnknownPtc;
    return dummyChannel;
}
#endif


void CHsvDvbCInstallation_m_Priv::iprescanN_OnEvent(int event)
{
    if(mDvbcStatus.State == StPreScan)
    {
        switch(event)
        {
            case iprescanN_EventScanStopped:
                pmp_PmpSend(mInstallPump, EvPreScanDone, (Nat32)iprescanN_EventScanStopped);
                break;
            case iprescanN_EventScanCompleted:
                pmp_PmpSend(mInstallPump, EvPreScanDone, (Nat32)iprescanN_EventScanCompleted);
                break;
        }
    }
    else
    {
        ASSERT(!"Invalid Notifcation of iPreScan");
    }
}
void CHsvDvbCInstallation_m_Priv::iquickN_OnEvent(int event)
{
    if(mDvbcStatus.State == StQuick)
    {
        switch(event)
        {
            case iquickN_EventScanStopped:
                pmp_PmpSend(mInstallPump, EvQuickDone, (Nat32)iquickN_EventScanStopped);
                break;
            case iquickN_EventScanCompleted:
                pmp_PmpSend(mInstallPump, EvQuickDone, (Nat32)iquickN_EventScanCompleted);
                break;
        }
    }
    else
    {
        ASSERT(!"Invalid Notifcation of iquickN");
    }
}

void CHsvDvbCInstallation_m_Priv::ifullN_OnEvent(int event)
{
    if(mDvbcStatus.State == StFull)
    {
        switch(event)
        {
            case ifullN_EventScanStopped:
                pmp_PmpSend(mInstallPump, EvFullDone, (Nat32)ifullN_EventScanStopped);
                break;
            case ifullN_EventScanCompleted:
                pmp_PmpSend(mInstallPump, EvFullDone, (Nat32)ifullN_EventScanCompleted);
                break;
            case ifullN_EventScanFailed:
                pmp_PmpSend(mInstallPump, EvFullDone, (Nat32)ifullN_EventScanFailed);
                break;          
        }
    }
    else
    {
        ASSERT(!"Invalid Notifcation of ifullN");
    }
}
void CHsvDvbCInstallation_m_Priv::igridN_OnEvent(int event)
{
    TraceDebug(m,"%s:State = %d",__FUNCTION__,mDvbcStatus.State);
    if(mDvbcStatus.State == StGrid)
    {
        switch(event)
        {
            case igridN_EventScanStopped:
                pmp_PmpSend(mInstallPump, EvGridDone, (Nat32)igridN_EventScanStopped);
                break;
            case igridN_EventScanCompleted:
                pmp_PmpSend(mInstallPump, EvGridDone, (Nat32)igridN_EventScanCompleted);
                break;
            case igridN_EventScanFailed:
                pmp_PmpSend(mInstallPump, EvGridDone, (Nat32)igridN_EventScanFailed);
                break;          
        }
    }
    else
    {
        ASSERT(!"Invalid Notifcation of igridN");
    }
}

void CHsvDvbCInstallation_m_Priv::ena_Enable(void)
{
    ipena_Enable();
    ifena_Enable();
    igena_Enable();
    iqena_Enable();
    idataacq_Enable();
}

void CHsvDvbCInstallation_m_Priv::ena_Disable(void)
{
    ipena_Disable();
    ifena_Disable();
    igena_Disable();
    iqena_Disable();
    idataacq_Disable();
}

void CHsvDvbCInstallation_m_Priv::ins_ClearPersistent()
{
    idvbset_ClearPersistent();
    iquick_ClearPersistent();
}

/*within*/

/* Interfaces from IHsvInstallation2.id */


int CHsvDvbCInstallation_m_Priv::ins_GetNumberOfAnalogChannelsFound(void) 
{
	return 0;
}


int CHsvDvbCInstallation_m_Priv::ins_GetInstallationStatus( void ) 
{
	return 0;
}


Bool CHsvDvbCInstallation_m_Priv::ins_IsUpdateInstallationSupported( void ) 
{
	return FALSE;
}

void CHsvDvbCInstallation_m_Priv::ins_SetManualFrequency( int frequency, int offset, Bool finetune ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_GetManualFrequency ( int *frequency, int *offset, Bool *finetune ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_SetManualChannel( int channel, Bool finetune ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_GetManualChannel( int *channel, Bool *finetune ) 
{
	return;
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsManualInstallationModeSupported ( int mode ) 
{
	return FALSE;
}

void CHsvDvbCInstallation_m_Priv::ins_SetManualInstallationMode( int mode ) 
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetManualInstallationMode( void ) 
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_StoreManualInstallationValues( HsvChannel channel ) 
{
	return;
}

Bool CHsvDvbCInstallation_m_Priv::ins_AutoStoreManualInstallationValues( ) 
{
	return FALSE;
}

Bool CHsvDvbCInstallation_m_Priv::ins_StartFrequencySearch(void) 
{
	return FALSE;
}

FResult CHsvDvbCInstallation_m_Priv::ins_GetSigStrengthRange(int measmode, Nat32* min, Nat32* max) 
{
	return 0;
}

Nat32 CHsvDvbCInstallation_m_Priv::ins_GetSignalstrength(int measmode) 
{
	return 0;
}

/*TODO: return dummy channel*/
HsvChannel CHsvDvbCInstallation_m_Priv::ins_GetInstalledWeakSignalChannel(void) 
{
	HsvChannel dummyChannel;
	return dummyChannel;
}

Nat32 CHsvDvbCInstallation_m_Priv::ins_GetSignalQualityBer(void) 
{
	return 0;
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsFrequencySearchDirectionSupported( Bool searchup ) 
{
	return FALSE;
}

void CHsvDvbCInstallation_m_Priv::ins_SetFrequencySearchDirection ( Bool searchup ) 
{
	return;
}

Bool CHsvDvbCInstallation_m_Priv::ins_GetFrequencySearchDirection ( void ) 
{
	return FALSE;
}

int CHsvDvbCInstallation_m_Priv::ins_GetMinFrequency( void ) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetMaxFrequency( void ) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetTunerFrequency( void ) 
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_SetTunerFrequency( int freq, Bool fineTune ) 
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetFrequency2Channel( int chantbl, int frequency ) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetChannel2CarrierFrequency ( int chantbl, int channel ) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetChannel2CentreFrequency ( int chantbl, int channel ) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetCurrentPass ( void ) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetNoOfPass (void) 
{
	return 0;
}

Nat16 CHsvDvbCInstallation_m_Priv::ins_GetCurrentPassType(void) 
{
	return 0;
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsMediumSupported(int medium) 
{
	return FALSE;
}

int CHsvDvbCInstallation_m_Priv::ins_GetMedium(void) 
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_SetMedium(int medium) 
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetInstalledMedium(void) 
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_SetInstalledMedium(int medium)  
{
	return;
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsTvSystemSupported( int tvsystem ) 
{
	return FALSE;
}

void CHsvDvbCInstallation_m_Priv::ins_SetTvSystem ( int tvsystem ) 
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetTvSystem( void ) 
{
	return 0;
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsColorSystemSupported( int colorsystem ) 
{
	return FALSE;
}

void CHsvDvbCInstallation_m_Priv::ins_SetColorSystem ( int colorsystem ) 
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetColorSystem( void ) 
{
	return 0;
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsValidPTC(int medium,int PTC) 
{
	return FALSE;
}

int CHsvDvbCInstallation_m_Priv::ins_GetMinPTC(int medium) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetMaxPTC(int medium) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetLastPTCFound(void) 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetNumberOfPTCsFound(void) 
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_StartSigStrMeas(int measmode) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_StopSigStrMeas(int measmode) 
{
	return;
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsSignalStrengthMeasurementValid( int measmode ) 
{
	return FALSE;
}

Bool CHsvDvbCInstallation_m_Priv::ins_GetAttributeRange(int installationmode, int attribute, int* minValue, int* maxValue) 
{
	return idvbset_GetAttributeRange(installationmode, attribute, minValue, maxValue);
}

Bool CHsvDvbCInstallation_m_Priv::ins_SetAttributeMode(int installationmode, int attribute, int attributeMode) 
{
	return idvbset_SetAttributeMode(installationmode, attribute, attributeMode);
}

Bool CHsvDvbCInstallation_m_Priv::ins_SetAttribute(int installationmode, int attribute, int value) 
{
	return idvbset_SetAttribute( installationmode, attribute, value) ;
}

int CHsvDvbCInstallation_m_Priv::ins_GetAttributeMode(int installationmode, int attribute) 
{
	return idvbset_GetAttributeMode( installationmode, attribute );
}

int CHsvDvbCInstallation_m_Priv::ins_GetAttribute(int installationmode, int attribute) 
{
	return idvbset_GetAttribute( installationmode, attribute );
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsAvailable(int installationmode, int attribute) 
{
	return idvbset_IsAvailable( installationmode, attribute );
}

void CHsvDvbCInstallation_m_Priv::ins_ResetAttributeToDefault(int installationmode, int attribute) 
{
	idvbset_ResetAttributeToDefault( installationmode, attribute );
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_ResetAttributeToPersistent(int installationmode, int attribute) 
{
	idvbset_ResetAttributeToPersistent( installationmode, attribute );
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetTargetNitType(Nat16* NetworkId) 
{
	return iquick_GetTargetNitType(NetworkId);
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsNetworkUpdateDetected(void) 
{
	return idataacq_IsNetworkUpdateDetected();
}

void CHsvDvbCInstallation_m_Priv::ins_Initialise(void) 
{
	return;
}

FResult CHsvDvbCInstallation_m_Priv::ins_SkipInstallationScans(int ScanTypes) 
{
	return 0;
}

Bool CHsvDvbCInstallation_m_Priv::ins_GetAltTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return iquick_GetAltTSValues( ONID, TSID );
}

void CHsvDvbCInstallation_m_Priv::ins_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	iquick_GetSIDetails(sivalues);
}


void CHsvDvbCInstallation_m_Priv::ins_SetUserSymbolRates( int installationmode, int *values, int len ) 
{
	idvbset_SetUserSymbolRates(installationmode, values, len);
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_GetUserSymbolRates( int installationmode, int *values, int *len ) 
{
	idvbset_GetUserSymbolRates(installationmode, values, len);
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_GetPredefinedSymbolRates( int installationmode, int *values, int *len ) 
{
	idvbset_GetPredefinedSymbolRates(installationmode, values, len);
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetNetworkIDList(void) 
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_GetNetworkIDName(int index, Nat16 *NetworkName) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_SetFavouriteNetworkID(int mode, int attrib, int index) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_SetFavouriteRegion(int mode, int index, HsvEnmRegionType RegionType) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_SetUserSelectConflictService(int LcnIndex, int SvcIndex) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_ConflictsSelectionDone(Bool UserSelection) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_GetConflictServices( HsvConflictServicesData *ConflictList, int *NumRecords ) 
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetInstallationVersion() 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetInstallationState() 
{
	return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetPLPIds(int *PLPIds) 
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_GetRegionList(HsvNetworkRegionsData *RegionsData) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_UserSelectionDone(Bool UserSelection) 
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetFavouriteRegion(int mode, HsvEnmRegionType RegionType) 
{
	return 0;
}

HsvStreamPriority CHsvDvbCInstallation_m_Priv::ins_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}

void CHsvDvbCInstallation_m_Priv::ins_SetStreamPriority (HsvStreamPriority prio) 
{
	return;
}

HsvConstellation CHsvDvbCInstallation_m_Priv::ins_GetConstellation(void) 
{
	return (HsvConstellation)0;
}

Nat32 CHsvDvbCInstallation_m_Priv::ins_GetSymbolRate(void) 
{
	return 0;
}

HsvHierarchyMode CHsvDvbCInstallation_m_Priv::ins_GetHierarchyMode(void) 
{
	return (HsvHierarchyMode)0;
}

void CHsvDvbCInstallation_m_Priv::ins_GetEpgBarkerMux(Nat16 *OnId, Nat16 *TsId) 
{
	return;
}

Bool CHsvDvbCInstallation_m_Priv::ins_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}


int CHsvDvbCInstallation_m_Priv::ins_GetInstallationProgress() /*New*/
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_SetInstallRfSetting( int value ) /*New*/
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_SetLCNSortingControl( int mode ) /*New*/
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetLCNSortingControl() /*New*/
{
	return 1;
}

void CHsvDvbCInstallation_m_Priv::ins_SetPbsMode( int value ) /*New*/
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_PrepareChNameUpdate(int value1, int value2)
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_GetUpdatedChannelName(Nat16* pChName)
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetUpdatedONID()
{
	return -1;
}

int CHsvDvbCInstallation_m_Priv::ins_GetUpdatedTsID()
{
	return -1;
}

void CHsvDvbCInstallation_m_Priv::ins_SetIsDVBT2Scan(int abIsTrue)
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_SetFocusedPlpId(int aiPlpId)
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_SetExtractScanResult(int abIsTrue)
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetUpdatedSymbolRate()
{
	return -1;
}

void CHsvDvbCInstallation_m_Priv::ins_SetInstallCountry( int country ) /*New*/
{
	return;
}
void CHsvDvbCInstallation_m_Priv::ins_SetSystemCountry( int country ) /*New*/
{
	return; 
}




/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvDvbCInstallation_m_Priv::feapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	iquickfeN_OnSearchInProgress( state );
    ifullfeN_OnSearchInProgress( state );
    igridfeN_OnSearchInProgress( state );
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnStationFound( void ) 
{
	iquickfeN_OnStationFound( );
    ifullfeN_OnStationFound( );
    igridfeN_OnStationFound( );
    iprescanfeN_OnStationFound( );
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnStationNotFound( void ) 
{
	iquickfeN_OnStationNotFound( ),
    ifullfeN_OnStationNotFound( ),
    igridfeN_OnStationNotFound( ),
    iprescanfeN_OnStationNotFound( );
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnMeasReady( int ssm, Nat32 strength ) 
{
	iquickfeN_OnMeasReady( ssm, strength ),
	ifullfeN_OnMeasReady( ssm, strength ),
    igridfeN_OnMeasReady( ssm, strength );
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnMeasAborted( int ssm ) 
{
	iquickfeN_OnMeasAborted( ssm ),
    ifullfeN_OnMeasAborted( ssm ),
    igridfeN_OnMeasAborted( ssm );
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::feapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}

void CHsvDvbCInstallation_m_Priv::strapiN_OnCompleted         ( HsvDestination dest, int spid)
{
	iqstrapiN_OnCompleted( dest, spid); 
    ifstrapiN_OnCompleted( dest, spid);
    igstrapiN_OnCompleted( dest, spid);
    iacqstrapiN_OnCompleted( dest, spid);
	return;
}

void CHsvDvbCInstallation_m_Priv::strapiN_OnAdded         ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	iqstrapiN_OnAdded( dest, spid, key1, key2, key3);
	ifstrapiN_OnAdded( dest, spid, key1, key2, key3); 
	igstrapiN_OnAdded( dest, spid, key1, key2, key3); 
	iacqstrapiN_OnAdded( dest, spid, key1, key2, key3);
	return;
}

void CHsvDvbCInstallation_m_Priv::strapiN_OnChanged           ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
	iqstrapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
	ifstrapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
	igstrapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
	iacqstrapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
	return;
}
void CHsvDvbCInstallation_m_Priv::strapiN_OnRemoved           ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	iqstrapiN_OnRemoved( dest, spid, key1, key2, key3);
    ifstrapiN_OnRemoved( dest, spid, key1, key2, key3);
	igstrapiN_OnRemoved( dest, spid, key1, key2, key3);
    iacqstrapiN_OnRemoved( dest, spid, key1, key2, key3);
	return;
}

void CHsvDvbCInstallation_m_Priv::ctrlN_OnEvent(HsvDemux dmx, int eventid, int value)
{
	iqctrlN_OnEvent(dmx, eventid, value);
	ifctrlN_OnEvent(dmx, eventid, value);
	igctrlN_OnEvent(dmx, eventid, value);
	ipctrlN_OnEvent(dmx, eventid, value);
}


void CHsvDvbCInstallation_m_Priv::ins_GetFirstIntalledDigitalChannel(int *channelno)
{
	*channelno = 0;
}

void CHsvDvbCInstallation_m_Priv::ins_GetFirstIntalledAnalogueChannel(int *channelno)
{
	*channelno = 0;
}


void CHsvDvbCInstallation_m_Priv::ins_GetFirstIntalledRadioChannel(int *channelno)
{
	*channelno = 0;
}

void CHsvDvbCInstallation_m_Priv::ins_GetFirstInstalledChannel(int *channelno)
{
	*channelno = 0;
}

void CHsvDvbCInstallation_m_Priv::ins_GetNetworkNameForNetworkID(int networkID, Nat16 *NetworkName)
{
}

void CHsvDvbCInstallation_m_Priv::ins_GetListOfNetworkIDs (int *NumberOfEntries, int *NetworkIDList)
{
}

Bool CHsvDvbCInstallation_m_Priv::ins_IsValidNetworkId (int networkID)
{
    return FALSE;
}


void CHsvDvbCInstallation_m_Priv::ins_SetLowestNetworkId (int *networkID)
{
}

int CHsvDvbCInstallation_m_Priv::ins_GetNumberOfDatabaseRecords(int TSDataOnly)
{
	return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_GetTvProviderBlobDataByIndex(int Index, void *TpvData, void*PrivateData,int TSDataOnly)
{
	return;
}
void CHsvDvbCInstallation_m_Priv::ins_GetChannelListIDName(int index, Nat16*ChannelistName)        
{
   return;
}
int CHsvDvbCInstallation_m_Priv::ins_GetNumberOfChannelListIds()        
{
    return 0;
}

int CHsvDvbCInstallation_m_Priv::ins_GetChannelListIdByIndex(int index)
{
   return 0;
}

void CHsvDvbCInstallation_m_Priv::ins_SetFavouriteChannelListId(int mode, int attrib, int index)     
{
   return;
}

void CHsvDvbCInstallation_m_Priv::ins_AddTvpData(HsvPgdatTvProviderBlobData *TvpData,int Clear)
{
	return;
}

void CHsvDvbCInstallation_m_Priv::ins_SyncUniqueIdToMW (HsvPgdatTvProviderBlobData *TvpData)
{
	return;
}

int CHsvDvbCInstallation_m_Priv::ins_GetLastAnalogPresetNumber()
{
	return -1;
}

int CHsvDvbCInstallation_m_Priv::ins_GetActiveMedium()
{
	return 0;
}

