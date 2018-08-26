/*
 *  Copyright(C) 2002 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.      
 *                                                                  
 *############################################################
 */
/*!
 *     \file          hsvziggo_mDtr.c
 *
 *     \brief         -
 *
 */
/*----------------------------------------------------------*
 *
 *     %version:       TVG_Fusion_2 %
 *     %date_created:  Tue Feb 28 15:15:53 2012 %
 *     %date_modified: Tue Oct 28 19:17:58 2008 %
 *     %derived_by:    nareshj %
 *
 *
 *############################################################
 */

#include "_hsvziggo_mDtr.h"

TRACESYMBOL(m, "dvb/installation/hsvziggo_mDtr")




#ifndef __cplusplus

#else

#endif









ModuleLifeCycle CHsvZiggoInstallation_mDtr_Priv::s__mModuleLifeCycle = TurnedOff;


int CHsvZiggoInstallation_mDtr_Priv::s__mInsState;

Pump CHsvZiggoInstallation_mDtr_Priv::s__mInstallPump;









const FunctionVoid CHsvZiggoInstallation_mDtr_Priv::EventActionMatrix[][StMax] =
{
    /* StIdle,                 StInProgress        */
    /* EvStart */           {  FNADDR(FuncStartInstallation),   NULL,                },
    /* EvStop */            {  NULL,                    FNADDR(FuncStopInstallation) },
    /* EvOnMeasReady */     {  NULL,                    FNADDR(FuncComplete)         }
};


void CHsvZiggoInstallation_mDtr_Priv::PumpHandler(int event, Nat32 param)
{
    if(VALID_EVENT(event) && VALID_STATE(mInsState))
    {
        TraceDebug(m,"@ %d event %d state %d - %s\n", __LINE__, event, mInsState, (EventActionMatrix[event][mInsState] == NULL)?"Ignored":"Handled");
        if(EventActionMatrix[event][mInsState] != NULL)
        {
            FPCALL(EventActionMatrix[event][mInsState])();
        }
    }
    UNUSED(param);
}

inline void CHsvZiggoInstallation_mDtr_Priv::FuncStartInstallation(void)
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    sigstr_StartSigStrMeasAll();
    SET_INS_STATE(StInProgress);
	/* start sdm collection with appropriate mode */
    ctrl_StartCollection(HsvDmxMain, ctrl_Normal);
    pmp_PmpSendAfter(mInstallPump, EvOnMeasReady, (Nat32)NULL, 15000);
}

inline void CHsvZiggoInstallation_mDtr_Priv::FuncStopInstallation(void)
{
	TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    SET_INS_STATE(StIdle);
	ctrl_StopCollection(HsvDmxMain);
    insN_OnEvent(insN_EventInstallationStopped, MANUAL_MODE);
}

inline void CHsvZiggoInstallation_mDtr_Priv::FuncComplete(void)
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
   
    insN_OnEvent(insN_EventChannelFound, MANUAL_MODE);
   // insN_OnEvent(insN_EventInstallationCompleted, MANUAL_MODE);
}

FResult CHsvZiggoInstallation_mDtr_Priv::idtr_StartInstallation(int source, int ptc, int mode)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d source %d mode %d\n", __FUNCTION__, __LINE__, TURNED_ON, source, mode);
    if( TURNED_ON && VALID_SOURCE(source) && (mode == MANUAL_MODE) )
    {
        pmp_PmpSend(mInstallPump, EvStart, (Nat32)NULL);
    }
    UNUSED(ptc);

    return retval;
}

FResult CHsvZiggoInstallation_mDtr_Priv::idtr_StopInstallation(void)
{
    FResult retval = (mInsState == StIdle)? hsverr_InstallationNotInProgress : hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d\n", __FUNCTION__, __LINE__, TURNED_ON);
    if(TURNED_ON)
    {
        pmp_PmpSend(mInstallPump, EvStop, (Nat32)NULL);
    }
    return retval;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrpow_Init(void)
{
    mInstallPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE,"hsvziggo_mInstall");
    mModuleLifeCycle = Initialised;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrpow_TurnOn(void)
{
    mModuleLifeCycle = TurnedOn;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnMeasReady( int ssm, Nat32 strength )
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    
	UNUSED(ssm);
    UNUSED(strength);
}

void CHsvZiggoInstallation_mDtr_Priv::idtr_Initialise()
{ }
FResult CHsvZiggoInstallation_mDtr_Priv::idtr_StartDigitalScan(void)
{ return 0; }
FResult CHsvZiggoInstallation_mDtr_Priv::idtr_StartDigitalTuning(int frequency)
{   UNUSED(frequency); return 0; }
FResult CHsvZiggoInstallation_mDtr_Priv::idtr_StopDigitalScan (void)
{ return 0; }
int CHsvZiggoInstallation_mDtr_Priv::idtr_GetNoOfPass(void)
{ return 0; }
int CHsvZiggoInstallation_mDtr_Priv::idtr_GetCurrentPass ( void )
{ return 0; }
FResult CHsvZiggoInstallation_mDtr_Priv::idtr_StoreWeakSignalInstallationChannel()
{ return 0; }
int CHsvZiggoInstallation_mDtr_Priv::idtr_GetNumberOfDigitalChannelsFound()
{ return 0; }
int CHsvZiggoInstallation_mDtr_Priv::idtr_GetNumberOfDigitalChannelsRemoved()
{ return 0; }
int CHsvZiggoInstallation_mDtr_Priv::idtr_GetCurrentState()
{ return 0; }
Bool CHsvZiggoInstallation_mDtr_Priv::idtr_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }
HsvStreamPriority CHsvZiggoInstallation_mDtr_Priv::idtr_GetStreamPriority(void)
{ return (HsvStreamPriority)0; }
HsvHierarchyMode CHsvZiggoInstallation_mDtr_Priv::idtr_GetHierarchyMode(void)
{ return (HsvHierarchyMode)0; }
void CHsvZiggoInstallation_mDtr_Priv::idtr_SetStreamPriority (HsvStreamPriority prio)
{ UNUSED(prio); }
void CHsvZiggoInstallation_mDtr_Priv::idtr_SyncComplete(void)
{ }
void CHsvZiggoInstallation_mDtr_Priv::idtr_ClearCache(void)
{ }
int CHsvZiggoInstallation_mDtr_Priv::idtr_GetPLPIds(int *PLPIds)
{ UNUSED(PLPIds); return 0; }
void CHsvZiggoInstallation_mDtr_Priv::idtrpow_TurnOff(void)
{ }
int CHsvZiggoInstallation_mDtr_Priv::idtr_GetSDTType()
{ return 0; }
void CHsvZiggoInstallation_mDtr_Priv::idtr_GetPTCInfo(HsvInstallationPTC *ptc)
{ UNUSED(ptc); }
void CHsvZiggoInstallation_mDtr_Priv::idtr_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{ UNUSED(ONID); UNUSED(TSID); }
void CHsvZiggoInstallation_mDtr_Priv::idtr_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{ UNUSED(ptc); UNUSED(Onid); UNUSED(Tsid); }
Bool CHsvZiggoInstallation_mDtr_Priv::idtr_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }
int CHsvZiggoInstallation_mDtr_Priv::idtr_GetTargetNitType(Nat16* NetworkId)
{ UNUSED(NetworkId); return 0; }
int CHsvZiggoInstallation_mDtr_Priv::idtr_ZiggoGetSDTType(Nat16 Frequency)
{ UNUSED(Frequency); return 0; }
Bool CHsvZiggoInstallation_mDtr_Priv::idtr_ZiggoNetworkDataSet(Bool ActionValue)
{
	UNUSED(ActionValue);
	return FALSE;
}
void CHsvZiggoInstallation_mDtr_Priv::idtr_ClearPersistent()
{
}
void CHsvZiggoInstallation_mDtr_Priv::idtr_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnStationFound( void ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnStationNotFound( void ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvZiggoInstallation_mDtr_Priv::idtrfeapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}


