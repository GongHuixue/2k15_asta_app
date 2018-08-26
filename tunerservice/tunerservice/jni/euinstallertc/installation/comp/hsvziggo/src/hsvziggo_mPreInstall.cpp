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
 *     \file          hsvziggo_mPreInstall.c
 *
 *     \brief         -
 *
 */
/*----------------------------------------------------------*
 *
 *     %version:       TVG_550toFusion_15 %
 *     %date_created:  Mon Jan 16 13:26:41 2012 %
 *     %date_modified: Tue Oct 28 19:17:58 2008 %
 *     %derived_by:    lakshminb %
 *
 *
 *############################################################
 */
#include "_hsvziggo_mPreInstall.h"

TRACESYMBOL(m, "dvb/installation/hsvziggo_mPreInstall")

#include "hsvziggo.h"





#ifndef __cplusplus

#else

#endif












InstStatus CHsvZiggoInstallation_mPreInstall_Priv::s__mInstStatus;




Pump CHsvZiggoInstallation_mPreInstall_Priv::s__mInstallPump;


ModuleLifeCycle CHsvZiggoInstallation_mPreInstall_Priv::s__mModuleLifeCycle = TurnedOff;

Bool CHsvZiggoInstallation_mPreInstall_Priv::s__mUserNetworkDataSet = FALSE,CHsvZiggoInstallation_mPreInstall_Priv::s__mDataAvailable = FALSE;

int CHsvZiggoInstallation_mPreInstall_Priv::s__mConstellation[14] =
{
    /*HsvUnknownConstellation*/ tmFe_UnknownConstellation,
    /*HsvAutoConstellation*/    tmFe_AutoConstellation,
    /*HsvBpsk*/                 tmFe_Bpsk,
    /*HsvQpsk*/                 tmFe_Qpsk,
    /*Hsv8psk*/                 tmFe_8psk,
    /*HsvQam4*/                 tmFe_Qam4,
    /*HsvQam16*/                tmFe_Qam16,
    /*HsvQam32*/                tmFe_Qam32,
    /*HsvQam64*/                tmFe_Qam64,
    /*HsvQam128*/               tmFe_Qam128,
    /*HsvQam256*/               tmFe_Qam256,
    /*HsvQam1024*/              tmFe_Qam1024,
    /*HsvVsb8*/                 tmFe_Vsb8,
    /*HsvVsb16*/                tmFe_Vsb16
};

















const FunctionVoid CHsvZiggoInstallation_mPreInstall_Priv::EventActionMatrix[][StMax] =
{
    /* StIdle,                StInit,               StTunerWait,          StDemuxWait         */
    /* EvStart */             {  FNADDR(FuncStartInstallation), NULL,                 NULL,                 NULL,                   },
    /* EvStop */              {  NULL,                  FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation)    },
    /* EvSdmStopped */        {  NULL,                  FNADDR(FuncSdmStopped),       NULL,                 NULL,                   },
    /* EvStationFound */      {  NULL,                  NULL,                 FNADDR(FuncStationFound),     NULL,                   },
    /* EvStationNotFound */   {  NULL,                  NULL,                 FNADDR(FuncStationNotFound),  NULL,                   },
    /* EvDataAvailable */     {  NULL,                  NULL,                 NULL,                 FNADDR(FuncDataAvailable),      },
    /* EvDataNotAvailable */  {  NULL,                  NULL,                 NULL,                 FNADDR(FuncDataNotAvailable),   }
};


void CHsvZiggoInstallation_mPreInstall_Priv::PumpHandler(int event, Nat32 param)
{
    if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
    {
        TraceDebug(m,"@ %d event %d state %d - %s\n", __LINE__, event, mInstStatus.State, (EventActionMatrix[event][mInstStatus.State] == NULL)?"Ignored":"Handled");
        if(EventActionMatrix[event][mInstStatus.State] != NULL)
        {
            FPCALL(EventActionMatrix[event][mInstStatus.State])();
        }
    }
    UNUSED(param);
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::FuncStartInstallation(void)
{
    ibckg_StopInstallation();

    mctl_Stop(HsvMain);
    SET_INS_STATE(StInit);
    mUserNetworkDataSet = mDataAvailable = FALSE;
    mStopSdm(HsvDmxMain);
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::FuncStopInstallation(void)
{
    SET_INS_STATE(StIdle);
    mUserNetworkDataSet = mDataAvailable = FALSE;
    mStopSdm(HsvDmxMain);

    insN_OnEvent(insN_EventInstallationStopped, CURRENT_MODE);
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::FuncSdmStopped(void)
{
    mSelectDecoder();       /* Select the DVBC decoder */
    mSetTunerAttributes();  /* Make the Tuner ready */
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::mSetTunerAttributes(void)
{
    Nat32 errorcode = TM_OK;
	Nat32 srtmode = 0;
    tmFe_SearchSymbolRate_t SearchRates[MAX_SEARCH_RATES];

    int i, j, Frequency = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq);
    int NumOfSymRates   = dvbset_GetAttributeLength(AUTO_MODE, rins_AttributeSymbolRate), TempSymbolrate = INVALID_SYMBOLRATE, CurrSymRatelen = 0;
    int NumOfModRates   = dvbset_GetAttributeLength(AUTO_MODE, rins_AttributeModulation), TempModrate = HsvUnknownConstellation;

    if( (NumOfSymRates * NumOfModRates) > MAX_SEARCH_RATES )
    {
        TraceDebug(m,"SearchRates exceeds limit <=> symbolrateLen %d modlen %d MAX_SEARCH_RATES %d\n", NumOfSymRates, NumOfModRates, MAX_SEARCH_RATES);
        ASSERT(FALSE);
    }

    for(i = 0; i < NumOfSymRates; i++)
    {
        TempSymbolrate = dvbset_GetNextAttributeValue(AUTO_MODE, rins_AttributeSymbolRate, TempSymbolrate);

        if( TempSymbolrate != INVALID_SYMBOLRATE)
        {
            TempModrate = HsvUnknownConstellation;
            for(j = 0; j < NumOfModRates; j++)
            {
                if(((NumOfModRates*CurrSymRatelen) + j) >= MAX_SEARCH_RATES)
                {
                    break;
                }
                TempModrate = dvbset_GetNextAttributeValue(AUTO_MODE, rins_AttributeModulation, TempModrate);

                SearchRates[(NumOfModRates * CurrSymRatelen) + j].rate = TempSymbolrate;
                SearchRates[(NumOfModRates * CurrSymRatelen) + j].constellation = (tmFe_Constellation_t)mConstellation[TempModrate];

                TraceDebug(m,"SymRate[%d] = %d\n", ((NumOfModRates * CurrSymRatelen) + j), TempSymbolrate);
                TraceDebug(m,"Modulation[%d] = %x\n", ((NumOfModRates * CurrSymRatelen) + j), mConstellation[TempModrate]);
            }
            CurrSymRatelen++;
        }
    }

    feapi_SetFreqStep(WINDOWID, ((dvbset_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeFreqStepSize))*16), &errorcode);
    ASSERT(TM_OK == errorcode);

    feapi_SetSearchRates(WINDOWID, SearchRates, (NumOfModRates * CurrSymRatelen), &errorcode);
    ASSERT(TM_OK == errorcode);

    feapi_SetSymbolRate(srtmode, 0, &errorcode);
    ASSERT(TM_OK == errorcode);

    TraceDebug(m,"%s %d Frequency %d SearchRateLen %d\n", __FUNCTION__, __LINE__, Frequency, (NumOfModRates * CurrSymRatelen));

    SET_INS_STATE(StTunerWait);
    feapi_SetFreq (WINDOWID, Frequency, FALSE, &errorcode);
    ASSERT(TM_OK == errorcode);

    insN_OnEvent(insN_EventSearchInProgress, Frequency);
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::FuncStationFound(void)
{
    insN_OnEvent(insN_EventTuningStationFound, CURRENT_MODE);
    /* start signal strength measurement */
    sigstr_StartSigStrMeasAll();

    SET_INS_STATE(StDemuxWait);
    /* start sdm collection with appropriate mode */
    ctrl_StartCollection(HsvDmxMain, ctrl_Normal);  
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::FuncStationNotFound(void)
{
    SET_INS_STATE(StIdle);

    /* send ceapps notification, so as to pop up UI, for user to enter the right frequency */
    insN_OnEvent(insN_EventTuningStationNotFound, CURRENT_MODE);
    insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::FuncDataAvailable(void)
{
    Bool NitValid = mNitValid();
    mDataAvailable = TRUE;
    if(mUserNetworkDataSet)
    {
        TraceNotice(m,"%s %d insN_EventNIDInvalid raised NitValid %d\n",__FUNCTION__, __LINE__, NitValid);
        insN_OnEvent(insN_EventNIDInvalid, !NitValid);
        
        if(NitValid)
        {
        	SET_INS_STATE(StIdle);
            insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
        }
    }
    else
    {
        TraceNotice(m,"%s %d\n",__FUNCTION__, __LINE__);
    }
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::FuncDataNotAvailable(void)
{
    SET_INS_STATE(StIdle);
    mStopSdm(HsvDmxMain);
    insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::mStopSdm(HsvDemux dmx)
{
    if(ctrl_GetMode(dmx) == ctrl_Idle)
    {
        pmp_PmpSend(mInstallPump, EvSdmStopped, (Nat32)NULL);
    }
    else
    {
        ctrl_StopCollection(dmx);
    }
}

inline void CHsvZiggoInstallation_mPreInstall_Priv::mSelectDecoder(void)
{
}

inline Bool CHsvZiggoInstallation_mPreInstall_Priv::mNitValid(void)
{
    Bool retval = FALSE;
    Nat16 Data = 0xFFFF, NetworkId;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) networkinfo;

    NetworkId = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkId);
    if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &Data))
    {
        TraceDebug(m,"%s %d Actual NetworkId %d\n", __FUNCTION__, __LINE__, Data);
        retval = (NetworkId == Data)? TRUE : FALSE;
    }
    
    if(retval == FALSE)
    {
        TraceDebug(m,"%s %d NetworkId %d\n", __FUNCTION__, __LINE__, NetworkId);
        if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), NetworkId, 0, 0, &networkinfo))
        {
            TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
            retval = TRUE;
        }
    }

    TraceDebug(m,"%s %d retval %d\n",__FUNCTION__, __LINE__, retval);
    return retval;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinspow_Init(void)
{
    mInstallPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE,"hsvziggo_mPreInstall");
    mModuleLifeCycle = Initialised;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinspow_TurnOn(void)
{
    mModuleLifeCycle = TurnedOn;
    SET_INS_STATE(StIdle);
}

FResult CHsvZiggoInstallation_mPreInstall_Priv::ipreins_StartInstallation(int source, int ptc, int mode)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d source %d mode %d\n", __FUNCTION__, __LINE__, TURNED_ON, source, mode);
    if( TURNED_ON && VALID_SOURCE(source) && VALID_INSTALL_MODE(mode) )
    {
        pmp_PmpSend(mInstallPump, EvStart, (Nat32)NULL);
    }

    UNUSED(ptc);
    return retval;
}

FResult CHsvZiggoInstallation_mPreInstall_Priv::ipreins_StopInstallation(void)
{
    FResult retval = (mInstStatus.State == StIdle)? hsverr_InstallationNotInProgress : hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d\n", __FUNCTION__, __LINE__, TURNED_ON);
    if(TURNED_ON && (retval == hsverr_Ok) )
    {
        pmp_PmpSend(mInstallPump, EvStop, (Nat32)NULL);
    }
    return retval;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnStationFound()
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {
        pmp_PmpSend( mInstallPump, EvStationFound, (Nat32)NULL);
    }
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnStationNotFound()
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {       
        pmp_PmpSend( mInstallPump, EvStationNotFound, (Nat32)NULL);
    }
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    if(TURNED_ON)
    {
        TraceDebug(m,"%s %d eventid %d\n", __FUNCTION__, __LINE__, eventid);
        switch(eventid)
        {
            case ipreinsctrlN_DataAvailable:
                pmp_PmpSend(mInstallPump, EvDataAvailable, (Nat32)NULL);
                break;
        case ipreinsctrlN_DataNotAvailable:
            pmp_PmpSend(mInstallPump, EvDataAvailable, (Nat32)NULL);
                break;
            case ipreinsctrlN_StoppedCollection:
                pmp_PmpSend(mInstallPump, EvSdmStopped, (Nat32)NULL);
                break;
            default:
                break;
        }
    }
    UNUSED(dmx);
    UNUSED(value);
}

int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetTargetNitType(Nat16* NetworkId)
{ 
    Nat16 TmpNetworkId;
    int retval = rins_NitOther;

    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    *NetworkId = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkId);
    if( strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &TmpNetworkId) )
    {
        TraceDebug(m,"%s %d Actual NetworkId %d\n", __FUNCTION__, __LINE__, TmpNetworkId);
        if(TmpNetworkId == *NetworkId)
        {
            retval = rins_NitActual;
        }
    }
    return retval;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_Initialise()
{ }
FResult CHsvZiggoInstallation_mPreInstall_Priv::ipreins_StartDigitalScan(void)
{ return 0; }
FResult CHsvZiggoInstallation_mPreInstall_Priv::ipreins_StartDigitalTuning(int frequency)
{   UNUSED(frequency); return 0; }
FResult CHsvZiggoInstallation_mPreInstall_Priv::ipreins_StopDigitalScan (void)
{ return 0; }
int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetNoOfPass(void)
{ return 0; }
int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetCurrentPass ( void )
{ return 0; }
FResult CHsvZiggoInstallation_mPreInstall_Priv::ipreins_StoreWeakSignalInstallationChannel()
{ return 0; }
int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetNumberOfDigitalChannelsFound()
{ return 0; }
int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetNumberOfDigitalChannelsRemoved()
{ return 0; }
int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetCurrentState()
{ return 0; }
int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetSDTType()
{ return 0; }
Bool CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }    
HsvStreamPriority CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetStreamPriority(void)
{ return (HsvStreamPriority)0; }
HsvHierarchyMode CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetHierarchyMode(void)
{ return (HsvHierarchyMode)0; }
void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetPTCInfo(HsvInstallationPTC *ptc)
{ UNUSED(ptc); }
void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{ UNUSED(ptc); UNUSED(Onid); UNUSED(Tsid); }
int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_ZiggoGetSDTType(Nat16 Frequency)
{ UNUSED(Frequency); return 0; }
Bool CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return FALSE; }
void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_SetStreamPriority (HsvStreamPriority prio)
{ UNUSED(prio); }
void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_SyncComplete(void)
{ }
void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_ClearCache(void)
{ }
int CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetPLPIds(int *PLPIds)
{ UNUSED(PLPIds); return 0; }
void CHsvZiggoInstallation_mPreInstall_Priv::ipreinspow_TurnOff(void)
{ }
void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{
    UNUSED(ONID);
    UNUSED(TSID);
}

Bool CHsvZiggoInstallation_mPreInstall_Priv::ipreins_ZiggoNetworkDataSet(Bool ActionValue)
{

    if(ActionValue == SET_VALUE)
    {
        mUserNetworkDataSet = ActionValue;
        if(mNitValid())
        {
            pmp_PmpSend(mInstallPump, EvDataAvailable, (Nat32)NULL);    
        }
        else
        {
            if(mDataAvailable)
            {
                insN_OnEvent(insN_EventNIDInvalid, TRUE);
            }
        }
        TraceDebug(m,"%s %d mUserNetworkDataSet %d\n", __FUNCTION__, __LINE__,mUserNetworkDataSet);
    }
    TraceDebug(m,"%s %d mUserNetworkDataSet %d\n", __FUNCTION__, __LINE__,mUserNetworkDataSet);

    return mUserNetworkDataSet;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_ClearPersistent()
{
    
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreins_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}



/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnMeasReady( int ssm, Nat32 strength ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvZiggoInstallation_mPreInstall_Priv::ipreinsfeapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}


