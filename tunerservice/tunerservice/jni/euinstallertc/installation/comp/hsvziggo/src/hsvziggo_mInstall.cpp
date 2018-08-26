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
 *     \file          hsvziggo_mInstall.c
 *
 *     \brief         -
 *
 */
/*----------------------------------------------------------*
 *
 *     %version:       TVG_Fusion_1 %
 *     %date_created:  Thu Jan 19 21:07:09 2012 %
 *     %date_modified: Tue Oct 28 19:17:58 2008 %
 *     %derived_by:    lakshminb %
 *
 *
 *############################################################
 */

#include "_hsvziggo_mInstall.h"

TRACESYMBOL(m, "dvb/installation/hsvziggo_mInstall")

#include "hsvziggo.h"
//#include "hsvziggo_mCommonData.c"





#ifndef __cplusplus

#else

#endif











InstStatus CHsvZiggoInstallation_mInstall_Priv::s__mInstStatus;




Pump CHsvZiggoInstallation_mInstall_Priv::s__mInstallPump;


ModuleLifeCycle CHsvZiggoInstallation_mInstall_Priv::s__mModuleLifeCycle = TurnedOff;


t_ZiggoCableDSDesc CHsvZiggoInstallation_mInstall_Priv::s__mCableDSDesc;

Nat16 CHsvZiggoInstallation_mInstall_Priv::s__mBarkerMuxONID = 0xFFFF,CHsvZiggoInstallation_mInstall_Priv::s__mBarkerMuxTSID = 0xFFFF;



int CHsvZiggoInstallation_mInstall_Priv::s__mConstellation[14] =
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























const FunctionVoid CHsvZiggoInstallation_mInstall_Priv::EventActionMatrix[][StMax] =
{
    /* StIdle,                StInit,               StTunerWait,          StDemuxWait             */
    /* EvStart */             {  FNADDR(FuncStartInstallation), NULL,                 NULL,                 NULL                    },
    /* EvStop */              {  NULL,                  FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation)    },
    /* EvSdmStopped */        {  NULL,                  FNADDR(FuncSdmStopped),       NULL,                 NULL                    },
    /* EvStationFound */      {  NULL,                  NULL,                 FNADDR(FuncStationFound),     NULL                    },
    /* EvStationNotFound */   {  NULL,                  NULL,                 FNADDR(FuncStationNotFound),  NULL                    },
    /* EvDataAvailable */     {  NULL,                  NULL,                 NULL,                 FNADDR(FuncDataAvailable)       },
    /* EvDataNotAvailable */  {  NULL,                  NULL,                 NULL,                 FNADDR(FuncDataNotAvailable)    }
};


void CHsvZiggoInstallation_mInstall_Priv::PumpHandler(int event, Nat32 param)
{
    if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
    {
        TraceDebug(m,"@ %d event %d state %d - %s", __LINE__, event, mInstStatus.State, (EventActionMatrix[event][mInstStatus.State] == NULL)?"Ignored":"Handled");
        if(EventActionMatrix[event][mInstStatus.State] != NULL)
        {
            FPCALL(EventActionMatrix[event][mInstStatus.State])();
        }
    }
    UNUSED(param);
}

inline void CHsvZiggoInstallation_mInstall_Priv::FuncStartInstallation(void)
{
    ibckg_StopInstallation();

    mInitialise();
    mctl_Stop(HsvMain);

    SET_INS_STATE(StInit);
    mStopSdm(HsvDmxMain);
}

inline void CHsvZiggoInstallation_mInstall_Priv::FuncStopInstallation(void)
{
    mInitialise();

    insN_OnEvent(insN_EventInstallationStopped, CURRENT_MODE);
}

inline void CHsvZiggoInstallation_mInstall_Priv::FuncSdmStopped(void)
{
    TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
    mSelectDecoder();       /* Select the DVBC decoder */
    mSetTunerAttributes();  /* Make the Tuner ready */
}

inline void CHsvZiggoInstallation_mInstall_Priv::FuncStationFound(void)
{
    /* start signal strength measurement */
    sigstr_StartSigStrMeasAll();

    SET_INS_STATE(StDemuxWait);
	
//   idataacq_UpdateBarkerMuxInfo (FALSE);
    /* start sdm collection with appropriate mode */
    ctrl_StartCollection(HsvDmxMain, ctrl_Normal);
}

inline void CHsvZiggoInstallation_mInstall_Priv::FuncStationNotFound(void)
{
    /* No MUX available, cannot proceed further complete installation */
    mInitialise();
    insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
}

inline void CHsvZiggoInstallation_mInstall_Priv::FuncDataAvailable(void)
{
    Bool Proceed = TRUE;
    Nat32 TargetNITSymRate, errorcode = 0;

    TraceDebug(m,"%s %d mInstStatus.TargeNITFound %d", __FUNCTION__, __LINE__, mInstStatus.TargeNITFound);
    if(mInstStatus.TargeNITFound == FALSE)
    {
        mInstStatus.TargeNITFound = mAcquireValidNit();
        if(mInstStatus.TargeNITFound == FALSE)
        {
            /* No proper data available, need not proceed further, installation completes here */
            mInitialise();
            insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
            Proceed = FALSE;
        }
    }

    /* If target NIT available, so proceed for individual MUXs installation */
    if(Proceed)
    {
        TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
        idataacq_AcquireData();
        /* ntf. for ceapps to query for number of channels installed */
        insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
    }

    if(mInstStatus.TargeNITFound == TRUE)
    {
        TraceDebug(m,"TargetNIT Found and Install Success from CDSD list, Setting all preferred values after NIT is found");

        feapi_GetActualCodeRate(WINDOWID, (Nat32* )(&TargetNITSymRate), (Nat32*)&errorcode);
        /* Set all preferred values */
        dvbset_SetPreferred(rins_AttributeSymbolRate, TargetNITSymRate, TRUE);
        dvbset_SetPreferred(rins_AttributeNetworkFreq, dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq), TRUE);
        dvbset_SetPreferred(rins_AttributeNetworkId, mInstStatus.TargetNITValue, TRUE);

        mInitialise();
        insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
    }
}

inline void CHsvZiggoInstallation_mInstall_Priv::FuncDataNotAvailable(void)
{
    TraceDebug(m,"%s %d mInstStatus.TargeNITFound %d", __FUNCTION__, __LINE__, mInstStatus.TargeNITFound);
    if(mInstStatus.TargeNITFound == FALSE)
    {
        /* No proper data available, need not proceed further complete installation */
        mInitialise();
        insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
    }
}

inline void CHsvZiggoInstallation_mInstall_Priv::mSetTunerAttributes(void)
{
    Nat32 errorcode = TM_OK;
	Nat32 srtmode = 0;
    tmFe_SearchSymbolRate_t SearchRates[MAX_SEARCH_RATES];
    int i, j, Frequency = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq);
    int NumOfSymRates   = dvbset_GetAttributeLength(AUTO_MODE, rins_AttributeSymbolRate), TempSymbolrate = INVALID_SYMBOLRATE, CurrSymRatelen = 0;
    int NumOfModRates   = dvbset_GetAttributeLength(AUTO_MODE, rins_AttributeModulation), TempModrate = HsvUnknownConstellation;

    if( (NumOfSymRates * NumOfModRates) > MAX_SEARCH_RATES )
    {
        TraceDebug(m,"SearchRates exceeds limit <=> symbolrateLen %d modlen %d MAX_SEARCH_RATES %d", NumOfSymRates, NumOfModRates, MAX_SEARCH_RATES);
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

                TraceDebug(m,"SymRate[%d] = %d", ((NumOfModRates * CurrSymRatelen) + j), TempSymbolrate);
                TraceDebug(m,"Modulation[%d] = %x", ((NumOfModRates * CurrSymRatelen) + j), mConstellation[TempModrate]);
            }
            CurrSymRatelen++;
        }
    }

    feapi_SetFreqStep(WINDOWID, ((dvbset_GetAttribute(AUTO_MODE, rins_AttributeFreqStepSize))*16), &errorcode);
    ASSERT(TM_OK == errorcode);

    feapi_SetSearchRates(WINDOWID, SearchRates, (NumOfModRates * CurrSymRatelen), &errorcode);
    ASSERT(TM_OK == errorcode);
	
    feapi_SetSymbolRate(srtmode, 0, &errorcode);
    ASSERT(TM_OK == errorcode);
							
    TraceDebug(m,"%s %d Frequency %d SearchRateLen %d", __FUNCTION__, __LINE__, Frequency, (NumOfModRates * CurrSymRatelen));

    SET_INS_STATE(StTunerWait);
    feapi_SetFreq (WINDOWID, Frequency, FALSE, &errorcode);
    ASSERT(TM_OK == errorcode);

    insN_OnEvent(insN_EventSearchInProgress, Frequency);
}

inline void CHsvZiggoInstallation_mInstall_Priv::mStopSdm(HsvDemux dmx)
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

inline void CHsvZiggoInstallation_mInstall_Priv::mSelectDecoder(void)
{
}

inline Bool CHsvZiggoInstallation_mInstall_Priv::mAcquireValidNit(void)
{
    int hsvspid = 0;
    Bool retval = FALSE;
    Nat16 NetworkId = 0xFFFF;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit)  NitOtherData;

    if( strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkId) )
    {
        TraceDebug(m,"%s %d Actual NetworkId %d", __FUNCTION__, __LINE__, NetworkId);

        if(mInstStatus.TargetNITValue == NetworkId)
        {
            hsvspid = HSVSPID(ActualCableDS, dvb, nit);
            mInstStatus.TargetNITType = rins_NitActual;
        }
    }

    if(mInstStatus.TargetNITType == rins_NitNone)   /* means NIT Actual is not of entered value */
    {
        if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), mInstStatus.TargetNITValue, 0, 0, &NitOtherData))
        {
            TraceDebug(m,"%s %d NIT other present for entered NID %d", __FUNCTION__, __LINE__, NitOtherData.NetworkId);

            hsvspid = HSVSPID(OtherCableDS, dvb, nit);
            mInstStatus.TargetNITType = rins_NitOther;
        }
    }

    retval = (mInstStatus.TargetNITType == rins_NitNone)? FALSE: TRUE;

    if(retval == TRUE)
    {
        if( (retval = mLoadCDSDFromStrapi(hsvspid)) == TRUE )
        {
            /* Acquire Service List Data before it goes away */
            idataacq_AcquireLCNData();

            idataacq_AcquireServiceListData();
        }
    }

    TraceDebug(m,"%s %d retval %d",__FUNCTION__, __LINE__, retval);
    return retval;
}

inline void CHsvZiggoInstallation_mInstall_Priv::mInitialise(void)
{
    Nat32 errorcode = 0;
    SET_INS_STATE(StIdle);
    mInstStatus.TargeNITFound = FALSE;
    mInstStatus.TargetNITType = rins_NitNone; 
    mInstStatus.TargetNITValue = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkId);
    
    memset((Address)(&mCableDSDesc), 0, sizeof(mCableDSDesc));
    feapi_SetSearchRates(WINDOWID, NULL, 0, (Nat32*)&errorcode);
    ASSERT(TM_OK == errorcode);

    TraceDebug(m,"%s %d TargetNITValue %d", __FUNCTION__, __LINE__, mInstStatus.TargetNITValue);
}

void CHsvZiggoInstallation_mInstall_Priv::iinspow_Init(void)
{
    mInstallPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE,"hsvziggo_mInstall");
    mModuleLifeCycle = Initialised;
}

void CHsvZiggoInstallation_mInstall_Priv::iinspow_TurnOn(void)
{
    mModuleLifeCycle = TurnedOn;
    mInitialise();
}

FResult CHsvZiggoInstallation_mInstall_Priv::iins_StartInstallation(int source, int ptc, int mode)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d source %d mode %d", __FUNCTION__, __LINE__, TURNED_ON, source, mode);
    if( TURNED_ON && VALID_SOURCE(source) && VALID_INSTALL_MODE(mode) )
    {
        pmp_PmpSend(mInstallPump, EvStart, (Nat32)NULL);
    }
    UNUSED(ptc);

    return retval;
}

FResult CHsvZiggoInstallation_mInstall_Priv::iins_StopInstallation(void)
{
    FResult retval = (mInstStatus.State == StIdle)? hsverr_InstallationNotInProgress : hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d", __FUNCTION__, __LINE__, TURNED_ON);
    if(TURNED_ON && (retval == hsverr_Ok) )
    {
        pmp_PmpSend(mInstallPump, EvStop, (Nat32)NULL);
    }
    return retval;
}

void CHsvZiggoInstallation_mInstall_Priv::iins_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    mGetPTCInfo(ptc, Onid, Tsid);
}

int CHsvZiggoInstallation_mInstall_Priv::iins_GetTargetNitType(Nat16* NetworkId)
{
    *NetworkId = mInstStatus.TargetNITValue;

    TraceDebug(m,"%s %d TargetNITValue %d TargetNITType %d", __FUNCTION__, __LINE__, mInstStatus.TargetNITValue, mInstStatus.TargetNITType);
    return mInstStatus.TargetNITType;
}

Bool CHsvZiggoInstallation_mInstall_Priv::iins_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{
    UNUSED(ONID);
    UNUSED(TSID);
    return TRUE;
}


void CHsvZiggoInstallation_mInstall_Priv::iins_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


int CHsvZiggoInstallation_mInstall_Priv::iins_ZiggoGetSDTType(Nat16 Frequency)
{
    return mGetSDTType(Frequency);
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnStationFound()
{
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {
        pmp_PmpSend( mInstallPump, EvStationFound, (Nat32)NULL);
    }
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnStationNotFound()
{
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {       
        pmp_PmpSend( mInstallPump, EvStationNotFound, (Nat32)NULL);
    }
}

void CHsvZiggoInstallation_mInstall_Priv::iinsctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    if(TURNED_ON)
    {
        TraceDebug(m,"%s %d eventid %d", __FUNCTION__, __LINE__, eventid);
        switch(eventid)
        {
            case iinsctrlN_DataAvailable:
                pmp_PmpSend(mInstallPump, EvDataAvailable, (Nat32)NULL);
                break;
        case iinsctrlN_DataNotAvailable:
            pmp_PmpSend(mInstallPump, EvDataAvailable, (Nat32)NULL);
                break;
            case iinsctrlN_StoppedCollection:
                pmp_PmpSend(mInstallPump, EvSdmStopped, (Nat32)NULL);
                break;
            default:
                break;
        }
    }
    UNUSED(dmx);
    UNUSED(value);
}

void CHsvZiggoInstallation_mInstall_Priv::iins_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{
    mGetEpgBarkerMux(ONID, TSID);
}

void CHsvZiggoInstallation_mInstall_Priv::iins_Initialise()
{ }
FResult CHsvZiggoInstallation_mInstall_Priv::iins_StartDigitalScan(void)
{ return 0; }
FResult CHsvZiggoInstallation_mInstall_Priv::iins_StartDigitalTuning(int frequency)
{   UNUSED(frequency); return 0; }
FResult CHsvZiggoInstallation_mInstall_Priv::iins_StopDigitalScan (void)
{ return 0; }
int CHsvZiggoInstallation_mInstall_Priv::iins_GetNoOfPass(void)
{ return 0; }
int CHsvZiggoInstallation_mInstall_Priv::iins_GetCurrentPass ( void )
{ return 0; }
FResult CHsvZiggoInstallation_mInstall_Priv::iins_StoreWeakSignalInstallationChannel()
{ return 0; }
int CHsvZiggoInstallation_mInstall_Priv::iins_GetNumberOfDigitalChannelsFound()
{ return 0; }
int CHsvZiggoInstallation_mInstall_Priv::iins_GetNumberOfDigitalChannelsRemoved()
{ return 0; }
int CHsvZiggoInstallation_mInstall_Priv::iins_GetCurrentState()
{ return 0; }
Bool CHsvZiggoInstallation_mInstall_Priv::iins_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }
HsvStreamPriority CHsvZiggoInstallation_mInstall_Priv::iins_GetStreamPriority(void)
{ return (HsvStreamPriority)0; }
HsvHierarchyMode CHsvZiggoInstallation_mInstall_Priv::iins_GetHierarchyMode(void)
{ return (HsvHierarchyMode)0; }
void CHsvZiggoInstallation_mInstall_Priv::iins_SetStreamPriority (HsvStreamPriority prio)
{ UNUSED(prio); }
void CHsvZiggoInstallation_mInstall_Priv::iins_SyncComplete(void)
{ }
void CHsvZiggoInstallation_mInstall_Priv::iins_ClearCache(void)
{ }
int CHsvZiggoInstallation_mInstall_Priv::iins_GetPLPIds(int *PLPIds)
{ UNUSED(PLPIds); return 0; }
void CHsvZiggoInstallation_mInstall_Priv::iinspow_TurnOff(void)
{ }
int CHsvZiggoInstallation_mInstall_Priv::iins_GetSDTType()
{ return 0; }
void CHsvZiggoInstallation_mInstall_Priv::iins_GetPTCInfo(HsvInstallationPTC *ptc)
{ UNUSED(ptc); }
Bool CHsvZiggoInstallation_mInstall_Priv::iins_ZiggoNetworkDataSet(Bool ActionValue)
{
    UNUSED(ActionValue);
    return FALSE;
}
void CHsvZiggoInstallation_mInstall_Priv::iins_ClearPersistent()
{
    
}


int CHsvZiggoInstallation_mInstall_Priv::mMapFromHsvToPlfDvbcModulation(int InputModulation)
{
		int 	OutputModulation = InputModulation;
		switch (InputModulation)
		{
		   case HsvQam16:
				   OutputModulation = PLF_TUNING_DVBC_QAM16;
				   break;
		   case HsvQam32:
				   OutputModulation = PLF_TUNING_DVBC_QAM32;
				   break;
		   case HsvQam64:
				   OutputModulation = PLF_TUNING_DVBC_QAM64;
				   break;
		   case HsvQam128:
				   OutputModulation = PLF_TUNING_DVBC_QAM128;
				   break;
		   case HsvQam256:
				   OutputModulation = PLF_TUNING_DVBC_QAM256;
				   break;
		   default:
				   break;
		}
		return OutputModulation;
}


/*hsvziggo_mCommonData.c*/

inline int CHsvZiggoInstallation_mInstall_Priv::mGetSDTType(Nat16 Frequency)
{
    return ((BACKGROUND_INSTALL)? eurdiv_SDTActual : ((Frequency == dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq))? eurdiv_SDTActual : eurdiv_SDTOther));
}

inline void CHsvZiggoInstallation_mInstall_Priv::mGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    int i = 0;

    for(i = 0; i < mCableDSDesc.NumOfTs; i++ )
    {
        if( (mCableDSDesc.TsLoop[i].ONID == Onid) && (mCableDSDesc.TsLoop[i].Tsid == Tsid) )
        {
            ptc->Frequency      = (mCableDSDesc.TsLoop[i].CableDesc[0].Frequency * 1000)/16;
            ptc->SymbolRate     = mCableDSDesc.TsLoop[i].CableDesc[0].SymbolRate;
            ptc->ModulationType = mCableDSDesc.TsLoop[i].CableDesc[0].Modulation;
			ptc->ModulationType = mMapFromHsvToPlfDvbcModulation (ptc->ModulationType);
            break;
        }
    }
    ptc->CodeRateHigh       =   ptc->CodeRateLow = HsvCodeRateAuto;
    ptc->ChannelInformation =   ptc->TimeError   = ptc->FrequencyError = ptc->FrequencyOffset = 0;
    ptc->DecoderType        =   feapi_ChanDecDvbC; 
    ptc->HierarchyMode      =   HsvHierarchyNone;
    ptc->GuardInterval      =   HsvGuardIntervalAuto;
    ptc->TxMode             =   HsvTxModeAuto;           
    ptc->IqMode             =   HsvIqModeNormal;
    ptc->ChannelBandwidth   =   HsvChanBandwidth8MHz;
    ptc->StreamPriority     =   HsvStreamPriorityHigh;
    ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
    ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
    ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);

    TraceDebug(m,"%s %d mInstStatus.TargetNITType %d <Freq SymRate ModRate> = <%ld %ld %d>", __FUNCTION__, __LINE__, mInstStatus.TargetNITType, ptc->Frequency, ptc->SymbolRate, ptc->ModulationType);
}

inline Bool CHsvZiggoInstallation_mInstall_Priv::mLoadCDSDFromStrapi(int hsvspid)
{
    int i, j;
    HSVSPTYPE(ActualCableDS, dvb, nit)    CableDSDesc;
    Nat32 Frequency = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq);

    mCableDSDesc.NumOfTs = strapi_GetSize(HsvMain, hsvspid);
    mBarkerMuxONID = 0xFFFF; mBarkerMuxTSID = 0xFFFF;

    TraceDebug(m,"%s %d NumofCDSD %d Frequency %ld", __FUNCTION__, __LINE__, mCableDSDesc.NumOfTs, Frequency);

    if(mCableDSDesc.NumOfTs > MAX_MUXES_PER_NTK)
    {
        TraceDebug(m,"%s %d NumofCDSD > MAX_MUXES_PER_NTK => (%d > %d)", __FUNCTION__, __LINE__, mCableDSDesc.NumOfTs, MAX_MUXES_PER_NTK);
        mCableDSDesc.NumOfTs = MAX_MUXES_PER_NTK;
    }

    for(i = 0; i < mCableDSDesc.NumOfTs; i++ )
    {
        if(strapi_GetByIndex(HsvMain, hsvspid, i, (void*)(&CableDSDesc)))
        {
            mCableDSDesc.TsLoop[i].ONID = CableDSDesc.Original_NetworkId;
            mCableDSDesc.TsLoop[i].Tsid = CableDSDesc.Tsid;
            mCableDSDesc.TsLoop[i].NumOfCDSD = CableDSDesc.NumOfCDSD;

            TraceDebug(m,"%s %d NumofCDSD %d", __FUNCTION__, __LINE__, CableDSDesc.NumOfCDSD);
            for(j = 0; j < CableDSDesc.NumOfCDSD; j++)
            {
                mCableDSDesc.TsLoop[i].CableDesc[j].Frequency  = CableDSDesc.CDSD[j].Frequency;
                mCableDSDesc.TsLoop[i].CableDesc[j].Modulation = CableDSDesc.CDSD[j].Modulation;
                mCableDSDesc.TsLoop[i].CableDesc[j].SymbolRate = CableDSDesc.CDSD[j].SymbolRate;

                if( (VALID_BARKERMUX_FOUND == FALSE) && (Frequency == mCableDSDesc.TsLoop[i].CableDesc[j].Frequency) )
                {
                    mBarkerMuxONID = mCableDSDesc.TsLoop[i].ONID; mBarkerMuxTSID = mCableDSDesc.TsLoop[i].Tsid;
                }
                TraceDebug(m,"CDS:: Frequency %d\nModulation %d\nSymbolRate %d\n", (CableDSDesc.CDSD[j].Frequency>>4), CableDSDesc.CDSD[j].Modulation, CableDSDesc.CDSD[j].SymbolRate);
            }
        }
        else
        {
            TraceDebug(m,"%s %d strapi_GetByIndex failed for pid %d index %d", __FUNCTION__, __LINE__, hsvspid, i);
        }
    }

    return ((mCableDSDesc.NumOfTs == 0)? FALSE: TRUE);
}

inline Bool CHsvZiggoInstallation_mInstall_Priv::mGetAltTSValues(Nat16* ONID, Nat16* TSID)
{
    UNUSED(ONID);
    UNUSED(TSID);
    return TRUE;
}

inline void CHsvZiggoInstallation_mInstall_Priv::mGetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{
    *ONID = mBarkerMuxONID; *TSID = mBarkerMuxTSID;
}



/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnMeasReady( int ssm, Nat32 strength ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvZiggoInstallation_mInstall_Priv::iinsfeapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}


