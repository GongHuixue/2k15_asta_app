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
 *     \file          hsvcanaldigital_mDtr.c
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

#include "_hsvcanaldigital_mDtr.h"

TRACESYMBOL(m, "dvb/installation/hsvcanaldigital_mDtr")




#ifndef __cplusplus

#else

#endif









ModuleLifeCycle CHsvCanalDigitalInstallation_mDtr_Priv::s__mModuleLifeCycle = TurnedOff;


int CHsvCanalDigitalInstallation_mDtr_Priv::s__mInsState;

Pump CHsvCanalDigitalInstallation_mDtr_Priv::s__mInstallPump;

int CHsvCanalDigitalInstallation_mDtr_Priv::s__mCurrentCookie;
Bool  CHsvCanalDigitalInstallation_mDtr_Priv::s__mStopPending;







const FunctionNat32 CHsvCanalDigitalInstallation_mDtr_Priv::EventActionMatrix[][StMax] =
{
    /* StIdle,                 StInProgress        */
    /* EvStart */           {  FNADDR(FuncStartInstallation),   NULL,                },
    /* EvStop */            {  NULL,                    FNADDR(FuncStopInstallation) },
    /* EvOnMeasReady */     {  NULL,                    FNADDR(FuncComplete)         }
};


void CHsvCanalDigitalInstallation_mDtr_Priv::PumpHandler(int event, Nat32 param)
{
	TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    if(VALID_EVENT(event) && VALID_STATE(mInsState))
    {
        TraceDebug(m,"@ %d event %d state %d - %s\n currentCookie %d param %d ", __LINE__, event, mInsState, (EventActionMatrix[event][mInsState] == NULL)?"Ignored":"Handled", mCurrentCookie, param);
        if(EventActionMatrix[event][mInsState] != NULL)
        {
            FPCALL(EventActionMatrix[event][mInsState])(param);
        }
    }
    UNUSED(param);
}

inline void CHsvCanalDigitalInstallation_mDtr_Priv::FuncStartInstallation(Nat32 param)
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    sigstr_StartSigStrMeasAll();
	if(ctrl_GetMode(HsvDmxMain) != ctrl_Idle)
	{
		ctrl_StopCollection (HsvDmxMain);
	}

    SET_INS_STATE(StInProgress);
	mStopPending = TRUE;
	/* start sdm collection with appropriate mode */
    ctrl_StartCollection(HsvDmxMain, ctrl_Normal);
    mCurrentCookie++;
    pmp_PmpSendAfter(mInstallPump, EvOnMeasReady, (Nat32)mCurrentCookie, 15000);
}

inline void CHsvCanalDigitalInstallation_mDtr_Priv::FuncStopInstallation(Nat32 param)
{
	TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    SET_INS_STATE(StIdle);
	ctrl_StopCollection(HsvDmxMain);
    mCurrentCookie++;
	if (mStopPending == TRUE)
	{
		insN_OnEvent(insN_EventInstallationStopped, MANUAL_MODE);
	}
    
}

inline void CHsvCanalDigitalInstallation_mDtr_Priv::FuncComplete(Nat32 param)
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
   
	/* Below check is added to avoid the previous installatoin even interfering with current installation.
		Use case : 1. DTR Started
			   2. DTR stopped within 15 seconds (by back key for eg)
			   3. Now again start DTR. Now in this case, State is StInProgress, hence the EvMeasReady (for request1) notification will be treated */
    if (mCurrentCookie == param)
    { 
    	//SET_INS_STATE(StIdle);
    	//ctrl_StopCollection(HsvDmxMain);
		mStopPending = FALSE;
    	insN_OnEvent(insN_EventChannelFound, MANUAL_MODE);
    }
   // insN_OnEvent(insN_EventInstallationCompleted, MANUAL_MODE);
}

FResult CHsvCanalDigitalInstallation_mDtr_Priv::idtr_StartInstallation(int source, int ptc, int mode)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d source %d mode %d\n", __FUNCTION__, __LINE__, TURNED_ON, source, mode);
    if( TURNED_ON && VALID_SOURCE(source) && (mode == MANUAL_MODE) )
    {
    	TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
        pmp_PmpSend(mInstallPump, EvStart, (Nat32)NULL);
    }
    UNUSED(ptc);

    return retval;
}

FResult CHsvCanalDigitalInstallation_mDtr_Priv::idtr_StopInstallation(void)
{
	/* If StopPending then give as InstallationNotInProgress, as this wll make the State to Idle in hsvueins */
    FResult retval = (mStopPending == FALSE) ? hsverr_InstallationNotInProgress : hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d\n", __FUNCTION__, __LINE__, TURNED_ON);
    if(TURNED_ON)
    {
        pmp_PmpSend(mInstallPump, EvStop, (Nat32)NULL);
    }
    return retval;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrpow_Init(void)
{
    mInstallPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE,"hsvcanaldigital_mInstall");
    mModuleLifeCycle = Initialised;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrpow_TurnOn(void)
{
    mModuleLifeCycle = TurnedOn;
    mCurrentCookie = 0;
	mStopPending = FALSE;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnMeasReady( int ssm, Nat32 strength )
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    
	UNUSED(ssm);
    UNUSED(strength);
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_Initialise()
{ }
FResult CHsvCanalDigitalInstallation_mDtr_Priv::idtr_StartDigitalScan(void)
{ return 0; }
FResult CHsvCanalDigitalInstallation_mDtr_Priv::idtr_StartDigitalTuning(int frequency)
{   UNUSED(frequency); return 0; }
FResult CHsvCanalDigitalInstallation_mDtr_Priv::idtr_StopDigitalScan (void)
{ return 0; }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetNoOfPass(void)
{ return 0; }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetCurrentPass ( void )
{ return 0; }
FResult CHsvCanalDigitalInstallation_mDtr_Priv::idtr_StoreWeakSignalInstallationChannel()
{ return 0; }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetNumberOfDigitalChannelsFound()
{ return 0; }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetNumberOfDigitalChannelsRemoved()
{ return 0; }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetCurrentState()
{ return 0; }
Bool CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }
HsvStreamPriority CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetStreamPriority(void)
{ return (HsvStreamPriority)0; }
HsvHierarchyMode CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetHierarchyMode(void)
{ return (HsvHierarchyMode)0; }
void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_SetStreamPriority (HsvStreamPriority prio)
{ UNUSED(prio); }
void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_SyncComplete(void)
{ }
void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_ClearCache(void)
{ }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetPLPIds(int *PLPIds)
{ UNUSED(PLPIds); return 0; }
void CHsvCanalDigitalInstallation_mDtr_Priv::idtrpow_TurnOff(void)
{ }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetSDTType()
{ return 0; }
void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetPTCInfo(HsvInstallationPTC *ptc)
{ UNUSED(ptc); }
void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{ UNUSED(ONID); UNUSED(TSID); }
void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{ UNUSED(ptc); UNUSED(Onid); UNUSED(Tsid); }
Bool CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetTargetNitType(Nat16* NetworkId)
{ UNUSED(NetworkId); return 0; }
int CHsvCanalDigitalInstallation_mDtr_Priv::idtr_ZiggoGetSDTType(Nat16 Frequency)
{ UNUSED(Frequency); return 0; }
Bool CHsvCanalDigitalInstallation_mDtr_Priv::idtr_ZiggoNetworkDataSet(Bool ActionValue)
{
	UNUSED(ActionValue);
	return FALSE;
}
void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_ClearPersistent()
{
}
void CHsvCanalDigitalInstallation_mDtr_Priv::idtr_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnStationFound( void ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnStationNotFound( void ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mDtr_Priv::idtrfeapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}


