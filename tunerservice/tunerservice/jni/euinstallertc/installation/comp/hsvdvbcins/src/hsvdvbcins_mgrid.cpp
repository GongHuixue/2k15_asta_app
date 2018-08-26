/**********************************************************************
 *
 *   C Source:       hsvdvbcins_mgrid.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    lakshminb %
 *   %date_created:  Thu Jan 19 21:07:25 2012 %
 *
 **********************************************************************/
#include "_hsvdvbcins_mgrid.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbcins_mgrid")

#include "hsvdvbcins.h"
/**************************************************************************
 * Macros and types
 **************************************************************************/






#ifndef __cplusplus

#else

#endif








   


t_DVBCFreqTable CHsvDvbCInstallation_mgrid_Priv::s__ChinaFreqTable[110] =  
{
    {52.5* 16, 53.5* 16}, 
    {60.5* 16, 61.5* 16},
    {68.5* 16, 69.5* 16},
    {80* 16,   81* 16},
    {88* 16,   89* 16},
    {115* 16,  116* 16},
    {123* 16,  124* 16},
    {131* 16,  132* 16},
    {139* 16,  140* 16},
    {147* 16,  148* 16},
    {155* 16,  156* 16},
    {163* 16,  164* 16},
    {171* 16,  172* 16},
    {179* 16,  180* 16},
    {187* 16,  188* 16},
    {195* 16,  196* 16},
    {203* 16,  204* 16},
    {211* 16,  212* 16},
    {219* 16,  220* 16},
    {227* 16,  228* 16},
    {235* 16,  236* 16},
    {243* 16,  244* 16},
    {251* 16,  252* 16},
    {259* 16,  260* 16},
    {267* 16,  268* 16},
    {275* 16,  276* 16},
    {283* 16,  284* 16},
    {291* 16,  292* 16},
    {299* 16,  300* 16},
    {307* 16,  308* 16},
    {315* 16,  316* 16},
    {323* 16,  324* 16},
    {331* 16,  332* 16},
    {339* 16,  340* 16},
    {347* 16,  348* 16},
    {355* 16,  356* 16},
    {363* 16,  364* 16},
    {371* 16,  372* 16},
    {379* 16,  380* 16},
    {387* 16,  388* 16},
    {395* 16,  396* 16},
    {403* 16,  404* 16},
    {411* 16,  412* 16},
    {419* 16,  420* 16},
    {427* 16,  428* 16},
    {435* 16,  436* 16},
    {443* 16,  444* 16},
    {451* 16,  452* 16},
    {459* 16,  460* 16},
    //{467* 16,  468* 16},
    {474* 16,  475* 16},
    {482* 16,  483* 16},
    {490* 16,  491* 16},
    {498* 16,  499* 16},
    {506* 16,  507* 16},
    {514* 16,  515* 16},
    {522* 16,  523* 16},
    {530* 16,  531* 16},
    {538* 16,  539* 16},
    {546* 16,  547* 16},
    {554* 16,  555* 16},
    {562* 16,  563* 16},
    {570* 16,  571* 16},
    {578* 16,  579* 16},
    {586* 16,  587* 16},
    {594* 16,  595* 16},
    {602* 16,  603* 16},
    {610* 16,  611* 16},
    {618* 16,  619* 16},
    {626* 16,  627* 16},
    {634* 16,  635* 16},
    {642* 16,  643* 16},
    {650* 16,  651* 16},
    {658* 16,  659* 16},
    {666* 16,  667* 16},
    {674* 16,  675* 16},
    {682* 16,  683* 16},
    {690* 16,  691* 16},
    {698* 16,  699* 16},
    {706* 16,  707* 16},
    {714* 16,  715* 16},
    {722* 16,  723* 16},
    {730* 16,  731* 16},
    {738* 16,  739* 16},
    {746* 16,  747* 16},
    {754* 16,  755* 16},
    {762* 16,  763* 16},
    {770* 16,  771* 16},
    {778* 16,  779* 16},
    {786* 16,  787* 16},
    {794* 16,  795* 16},
    {802* 16,  803* 16},
    {810* 16,  811* 16},
    {818* 16,  819* 16},
    {826* 16,  827* 16},
    {834* 16,  835* 16},
    {842* 16,  843* 16},
    {850* 16,  851* 16},
    {858* 16,  859* 16},
    {866* 16,  867* 16},
    {874* 16,  875* 16},
    {882* 16,  883* 16},
    {890* 16,  891* 16},
    {898* 16,  899* 16},
    {906* 16,  907* 16},
    {914* 16,  915* 16},
    {922* 16,  923* 16},
    {930* 16,  931* 16},
    {938* 16,  939* 16},
    {946* 16,  947* 16},
    {954* 16,  955* 16}

};


Nat32 CHsvDvbCInstallation_mgrid_Priv::s__FreqTableIndex = 0;


/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/















/****************************************************************************
 * Static variables
 ****************************************************************************/
Pump CHsvDvbCInstallation_mgrid_Priv::s__mGridPump;

t_DVBCGridStatus CHsvDvbCInstallation_mgrid_Priv::s__mDvbcGridStatus;


int CHsvDvbCInstallation_mgrid_Priv::s__ModulationVals[MAX_MODULATION_VALS]  = { 
    HsvQam128, 
    HsvQam64,
    HsvQam256,
    HsvQam32, 
    HsvQam16 
};


int CHsvDvbCInstallation_mgrid_Priv::s__mConstellation[14] =
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




const FunctionNat32 CHsvDvbCInstallation_mgrid_Priv::StateEventMatrix[][StMax] =
{                       /*StIdle            StFeWait            StDmxWait           StDecision*/
    /*EvStart*/             {FNADDR(FuncStartInstall),  NULL,               NULL,               NULL},
    /*EvStationFound*/      {NULL,              FNADDR(FuncStationFound),   NULL,               NULL},
    /*EvStationNotFound*/   {NULL,              FNADDR(FuncStationNotFound),NULL,               NULL},
    /*EvDmxNtf*/            {FNADDR(FuncBackground),    NULL,               FNADDR(FuncDmxData),        NULL},
    /*EvMakeDecision*/      {NULL,              NULL,               NULL,               FNADDR(FuncMakeDecision)},
    /*EvStop*/              {NULL,              FNADDR(FuncStop),           FNADDR(FuncStop),           FNADDR(FuncStop)},
    /*EvSigStrMeasured*/    {NULL,              NULL,               FNADDR(FuncSigStrMeasured), NULL},
};


/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/
void CHsvDvbCInstallation_mgrid_Priv::PumpHandler(int event, Nat32 param )
{
    if(StateEventMatrix[event][mDvbcGridStatus.State] != NULL)
    {
        FPCALL(StateEventMatrix[event][mDvbcGridStatus.State])(param);
    }
    else
    {
        TraceDebug(m,"Ignored event = %d, state = %d\r\n",event,mDvbcGridStatus.State);
    }
}

void CHsvDvbCInstallation_mgrid_Priv::FuncStartInstall(int param)
{
    Nat32 errorcode = TM_OK;
    Nat32 srtmode = 0;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    mctl_Stop(HsvMain);
    ctrl_StopCollection(mDvbcGridStatus.CurrentDemux);

    TraceDebug(m,"SetSearchRates called with len = %d\r\n",mDvbcGridStatus.SearchRateLen);
    feapi_SetSearchRates(WINDOWID, mDvbcGridStatus.SearchRates, mDvbcGridStatus.SearchRateLen, &errorcode);
    ASSERT(TM_OK == errorcode);
	
    feapi_SetSymbolRate(srtmode, mDvbcGridStatus.SymbolRate, &errorcode);
    ASSERT(TM_OK == errorcode);
	
    TraceDebug(m,"SetFreq called with freq = %ld MHz SymRate = %d \r\n",(Nat32) (ChinaFreqTable[FreqTableIndex].StartFrequency),mDvbcGridStatus.SymbolRate);
    feapi_SetFreq (WINDOWID, ChinaFreqTable[FreqTableIndex].StartFrequency, FALSE, &errorcode);
    ASSERT(TM_OK == errorcode);
    if(!MANUAL_INSTALL)
    {
    }
    mDvbcGridStatus.State = StFeWait;
    UNUSED(param);
}
void CHsvDvbCInstallation_mgrid_Priv::FuncStationFound(int param)
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);
    mUpdateTunerStatus();
    mDvbcGridStatus.StationFound = TRUE;

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:

            TraceDebug(m,"State set to DmxWait\r\n");
            mDvbcGridStatus.State = StDmxWait;
            sigstr_SetSigStrengthMeasured(FALSE);
            sigstr_Initialise();
            sigstr_UpdateSigStrRange();
            sigstr_StartSigStrMeasAll();
            ctrl_StartCollection(mDvbcGridStatus.CurrentDemux, ctrl_Minimal);
            break;

        case MANUAL_MODE:
            /*pavan: check why this is required */
            TraceDebug(m,"State set to DmxWait in Manual Mode\r\n");
            mDvbcGridStatus.State = StDmxWait;
            sigstr_StartSigStrMeasAll();

            pmp_PmpSend(mGridPump, EvSigStrMeasured, (Nat32)NULL);

            if( TRUE == sigstr_GetSigStrengthMeasured() )
            {
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigAssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigSssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigVssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigQssm);
            }

            ctrl_StartCollection(mDvbcGridStatus.CurrentDemux, ctrl_Normal);

            insN_OnEvent(insN_EventTuningStarted, CURRENT_MODE); 
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}
void CHsvDvbCInstallation_mgrid_Priv::FuncStationNotFound(int param)
{
    Nat32 errorcode = TM_OK;

    feapi_GetFreq(WINDOWID, &mDvbcGridStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    mDvbcGridStatus.StationFound = FALSE;
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            TraceDebug(m,"State set to StDecision\r\n");
            mDvbcGridStatus.State = StDecision;
            pmp_PmpSend(mGridPump, EvMakeDecision, (Nat32)NULL);
            break;

        case MANUAL_MODE:
            TraceDebug(m,"State set to StIdle\r\n");
            mResetInstallationState();
            /* Not Found so generate this ntf so that DVBT scan is started */
            igridN_OnEvent(igridN_EventScanFailed);
            insN_OnEvent(insN_EventChannelNotFound, MANUAL_MODE);
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}
void CHsvDvbCInstallation_mgrid_Priv::FuncDmxData(int param)
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(param == igctrlN_DataAvailable)
    {
        switch(CURRENT_MODE)
        {
            case AUTO_MODE:
            case UPDATE_MODE:
                mDvbcGridStatus.State = StDecision;
                idataacq_AcquireData();
                mDvbcGridStatus.NumChannelsAdded = idataacq_GetNumberOfDigitalChannelsFound();
                mDvbcGridStatus.NumChannelsRemoved = idataacq_GetNumberOfDigitalChannelsRemoved();
                ctrl_StopCollection(mDvbcGridStatus.CurrentDemux);
                insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
                pmp_PmpSend(mGridPump, EvMakeDecision, mDvbcGridStatus.Frequency);
                break;

            case MANUAL_MODE:

                /* Do not do anything. Wait for StoreWeakChannelData call to store.
                   On this ntf, the store button is highlighted. Only when pressed
                   acquire digital data and store */

                insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
                break;

            default:
                ASSERT(FALSE);
                break;
        }
    }
    else if(param == igctrlN_DataNotAvailable)
    {
        ctrl_StopCollection(mDvbcGridStatus.CurrentDemux);

        switch(CURRENT_MODE)
        {
            case AUTO_MODE:
            case UPDATE_MODE:
                mDvbcGridStatus.State = StDecision;
                pmp_PmpSend(mGridPump, EvMakeDecision, mDvbcGridStatus.Frequency);
                break;

            case MANUAL_MODE:
                mResetInstallationState();
                igridN_OnEvent(igridN_EventScanFailed);
                insN_OnEvent(insN_EventChannelNotFound, MANUAL_MODE);
                break;
            default:
                ASSERT(FALSE);
                break;
        }
    }
}
void CHsvDvbCInstallation_mgrid_Priv::FuncMakeDecision(int param)
{
    Nat32 errorcode = TM_OK;


    TraceDebug(m,"%s\r\n",__FUNCTION__);
    /* This is called only during auto and update install only */
    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            feapi_GetFreq(WINDOWID, &mDvbcGridStatus.Frequency, &errorcode);
            ASSERT(TM_OK == errorcode);
            FreqTableIndex++;

            TraceDebug(m,"Next Frequency to Search = %ld",(ChinaFreqTable[FreqTableIndex].StartFrequency>>4));
            TraceDebug(m,"End Frequency of Platform = %ld",(mDvbcGridStatus.EndFrequency>>4));

            if( (ChinaFreqTable[FreqTableIndex].StartFrequency) < (mDvbcGridStatus.EndFrequency) )
            {
                TraceDebug(m,"MakeDecision: Freq < End\r\n");

                feapi_SetFreq (WINDOWID, ChinaFreqTable[FreqTableIndex].StartFrequency, FALSE, &errorcode);

                /* Frequency within the range. So start search again */

                mDvbcGridStatus.State = StFeWait;
                //TraceDebug(m,"MakeDecision: StartSearch called with freq = %ldMHz, End Freq = %ldMHz\r\n",(Nat32) (mDvbcGridStatus.Frequency >> 4),(Nat32) (mDvbcGridStatus.EndFrequency >> 4));
                //feapi_StartSearch(WINDOWID, tmFe_SmDefault, mDvbcGridStatus.EndFrequency, &errorcode );

                insN_OnEvent(insN_EventSearchInProgress,mDvbcGridStatus.Frequency);
                ASSERT(TM_OK == errorcode);
            }
            else
            {
                TraceDebug(m,"MakeDecision: Freq >= End\r\n");
                TraceDebug(m,"MakeDecision: Install Complete\r\n");
                idataacq_SyncTemporaryTableRecords();
            }

            break;
        case MANUAL_MODE:
            /* should not reach here */
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}

void CHsvDvbCInstallation_mgrid_Priv::FuncStop(int param)
{
    tmErrorCode_t errorcode;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    switch(mDvbcGridStatus.State)
    {
        case StFeWait:      
            feapi_StopSearch(WINDOWID, &errorcode);
            ASSERT(TM_OK  ==  errorcode);
            break;
        case StDmxWait:
            ctrl_StopCollection(mDvbcGridStatus.CurrentDemux);
            sigstr_StopSigStrMeasAll();
            break;
        case StDecision:
            /* pavan: Not possible actually. State change happens in Makedecision anyways */
            TraceDebug(m,"Nothing can be done ??\r\n");
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    mResetInstallationState();
    igridN_OnEvent(igridN_EventScanStopped);
    UNUSED(param);
}

void CHsvDvbCInstallation_mgrid_Priv::FuncBackground(int param)
{
    UNUSED(param);
    mUpdateTunerStatus();

}


void CHsvDvbCInstallation_mgrid_Priv::FuncSigStrMeasured(int param)
{
    UNUSED(param);
    if(TRUE == sigstr_StartSigStrMeasAll())
    {
        if( TRUE == sigstr_GetSigStrengthMeasured() )
        {
            insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigAssm);
            insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigSssm);
            insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigVssm);
            insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigQssm);
        }
        pmp_PmpSendAfter(mGridPump, EvSigStrMeasured, (Nat32)NULL, SIGSTR_WAITTIME);
    }
}

void CHsvDvbCInstallation_mgrid_Priv::mUpdateTunerStatus(void)
{
    int param1;
    tmErrorCode_t errorcode = TM_OK;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    feapi_GetFreq(WINDOWID, &mDvbcGridStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    feapi_GetActualConstellation(WINDOWID, feapi_ChanDecDvbC, (tmFe_Constellation_t*)(&param1), &errorcode);
    ASSERT(TM_OK  ==  errorcode);
    mDvbcGridStatus.ModulationType = param1; //(Nat8)FindHsvValue(param1, mConstellation, sizeof(mConstellation));

    feapi_GetActualCodeRate(WINDOWID, &mDvbcGridStatus.SymbolRate, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

}

void CHsvDvbCInstallation_mgrid_Priv::mPlayService(int serviceid)
{
    TraceDebug(m,"%s::Service ID played = 0x%x\r\n",__FUNCTION__, serviceid);


    if(mDvbcGridStatus.PlayStarted == FALSE)
    {
        TraceDebug(m,"Play Started on Servide = %d\r\n", serviceid);
        mDvbcGridStatus.PlayStarted = TRUE;
        mctl_Stop(HsvMain);
        mctl_Flush(HsvMain);
        strmfltr_Clear(HsvMain,HsvCurrentProgram,serviceid);
        strmfltr_Set(HsvMain,HsvCurrentProgram,serviceid);
        mctl_Play(HsvMain);
    }
}

/***************************
  provides IHsvPower
 ****************************/
void CHsvDvbCInstallation_mgrid_Priv::igridpow_Init()
{
    mGridPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE, "hsvdvbcins_mgrid_pmp");
}

void CHsvDvbCInstallation_mgrid_Priv::igridpow_TurnOn()
{
}

void CHsvDvbCInstallation_mgrid_Priv::igridpow_TurnOff()
{
}

/************************************
  provides IHsvDigitalScan igrid
 *************************************/
void CHsvDvbCInstallation_mgrid_Priv::igrid_Initialise(void)
{
    int i = 0, j = 0, slen = 0, mlen = 0;
    int aslen = 0; /* Acutal Symbol Length */
    Nat32 decoder, retval, err = TM_OK;
    TraceDebug(m,"%s\r\n",__FUNCTION__);
    TraceDebug(m,"*********Dileep: Inside Grid Initialise*************");


    mDvbcGridStatus.State = StIdle;
    mDvbcGridStatus.ModulationType = HsvAutoConstellation;
    mDvbcGridStatus.CodeRateHigh = HsvCodeRateAuto;  
    mDvbcGridStatus.CodeRateLow = HsvCodeRateAuto;
    mDvbcGridStatus.GuardInterval = HsvGuardIntervalAuto;
    mDvbcGridStatus.TxMode = HsvTxModeAuto;
    mDvbcGridStatus.IqMode = HsvIqModeNormal;
    mDvbcGridStatus.ChannelBandwidth = HsvChanBandwidth8MHz;
    mDvbcGridStatus.ChannelInformation = 0;
    mDvbcGridStatus.TimeError = 0;
    mDvbcGridStatus.FrequencyError = 0;
    mDvbcGridStatus.FrequencyOffset = HsvOffsetNone;
    mDvbcGridStatus.CurrentDemux = HsvDmxMain;
    mDvbcGridStatus.SDTAcquired = FALSE;
    mDvbcGridStatus.PlayStarted = FALSE;
    mDvbcGridStatus.StationFound = FALSE;
    mDvbcGridStatus.NumChannelsAdded = 0;
    mDvbcGridStatus.NumChannelsRemoved = 0;
    mDvbcGridStatus.FirstPresetNumber = INVALID_PRESET;

    retval = feapi_GetFreqRange(WINDOWID, &(mDvbcGridStatus.Frequency), &(mDvbcGridStatus.EndFrequency), &err);    
    ASSERT(retval == plferrids_Ok);
    ASSERT(err == TM_OK);
    ASSERT(mDvbcGridStatus.Frequency <= START_FREQUENCY);
    ASSERT(mDvbcGridStatus.EndFrequency >= END_FREQUENCY);

    slen = idvbset_GetAttributeLength(CURRENT_MODE, rins_AttributeSymbolRate);
    mlen = MAX_MODULATION_VALS;     //idvbset_GetAttributeLength(CURRENT_MODE, rins_AttributeModulation);

    if((slen * mlen) > MAX_SEARCH_RATES)
    {
        ASSERT(!"Combination of sym rate and mod cannot be so high");
    }
    {
        int temprate = INVALID_SYMBOLRATE;
        for(i = 0; i < slen; i++)
        {


            temprate = idvbset_GetNextAttributeValue(CURRENT_MODE, rins_AttributeSymbolRate, temprate);
            if (temprate != INVALID_SYMBOLRATE)
            {
                for(j = 0; j < mlen; j++)
                {
                    if(((mlen*aslen) + j) >= MAX_SEARCH_RATES)
                    {
                        break;
                    }

                    mDvbcGridStatus.SearchRates[(mlen*aslen) + j].rate = temprate;
                    mDvbcGridStatus.SearchRates[(mlen*aslen) + j].constellation = (tmFe_Constellation_t)mConstellation[ModulationVals[j]];
                    TraceDebug(m,"Initialise: SymRate[%d] = %d\r\n", ((mlen*aslen) + j),temprate);
                    TraceDebug(m,"Initialise: Modulation[%d] = %x\r\n", ((mlen*aslen) + j),mConstellation[ModulationVals[j]]);
                }
                aslen++;
            }
        }
    }
    if((aslen * mlen) > MAX_SEARCH_RATES)
    {
        mDvbcGridStatus.SearchRateLen = MAX_SEARCH_RATES;
    }
    else
    {
        mDvbcGridStatus.SearchRateLen = (aslen * mlen);
    }

    TraceDebug(m,"Initialise:SearchRateLen = %d\r\n", mDvbcGridStatus.SearchRateLen);

    idataacq_Initialise();
}
FResult CHsvDvbCInstallation_mgrid_Priv::igrid_StartDigitalScan(void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    TraceDebug(m,"*********Dileep: Inside Grid StartDigitalScan*************");

    if(mDvbcGridStatus.State == StIdle)
    {
        pmp_PmpSend(mGridPump, EvStart, (Nat32)NULL);
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
}
FResult CHsvDvbCInstallation_mgrid_Priv::igrid_StartDigitalTuning(int freq)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(mDvbcGridStatus.State == StIdle)
    {
        mDvbcGridStatus.Frequency = freq;
        idvbset_SetAttribute(MANUAL_MODE, rins_AttributeNetworkFreq, freq);
        pmp_PmpSend(mGridPump, EvStart, (Nat32)NULL);
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
}
FResult CHsvDvbCInstallation_mgrid_Priv::igrid_StopDigitalScan (void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(mDvbcGridStatus.State == StIdle)
    {
        retval = hsverr_InstallationNotInProgress;
    }
    else
    {
        pmp_PmpSend(mGridPump, EvStop, (Nat32)NULL);
    }
    return retval;
}
void CHsvDvbCInstallation_mgrid_Priv::igrid_GetPTCInfo(HsvInstallationPTC *ptc)
{
    Nat32 errorcode = TM_OK;
    int temp;
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(mDvbcGridStatus.State == StIdle)
    {
        ptc->DecoderType = feapi_ChanDecDvbC;

        feapi_GetFreq(WINDOWID, &(ptc->Frequency), &errorcode);
		ptc->Frequency = (ptc->Frequency *1000)/16;
        ASSERT(TM_OK  ==  errorcode);

        feapi_GetActualCodeRate(WINDOWID, &(ptc->SymbolRate), &errorcode);
        ASSERT(TM_OK  ==  errorcode);

        feapi_GetActualConstellation(WINDOWID, feapi_ChanDecDvbC, (tmFe_Constellation_t*)(&temp), &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        mDvbcGridStatus.ModulationType = temp; //(Nat8)FindHsvValue(temp, mConstellation, sizeof(mConstellation));

        ptc->ModulationType     =   mDvbcGridStatus.ModulationType;
        ptc->HierarchyMode      =   HsvHierarchyNone;    
        ptc->StreamPriority     =   HsvStreamPriorityHigh;
    }
    else
    {
        ptc->DecoderType        =   feapi_ChanDecDvbC;
        ptc->Frequency          =   mDvbcGridStatus.Frequency;
		ptc->Frequency = (ptc->Frequency *1000)/16;
        ptc->SymbolRate         =   mDvbcGridStatus.SymbolRate;
        ptc->ModulationType     =   mDvbcGridStatus.ModulationType;   
        ptc->CodeRateHigh       =   mDvbcGridStatus.CodeRateHigh;         
        ptc->CodeRateLow        =   mDvbcGridStatus.CodeRateLow;         
        ptc->HierarchyMode      =   HsvHierarchyNone;    
        ptc->GuardInterval      =   mDvbcGridStatus.GuardInterval;    
        ptc->TxMode             =   mDvbcGridStatus.TxMode;           
        ptc->IqMode             =   mDvbcGridStatus.IqMode;           
        ptc->ChannelBandwidth   =   mDvbcGridStatus.ChannelBandwidth; 
        ptc->StreamPriority     =   HsvStreamPriorityHigh;
        ptc->ChannelInformation =   mDvbcGridStatus.ChannelInformation;   
        ptc->TimeError          =   mDvbcGridStatus.TimeError;        
        ptc->FrequencyError     =   mDvbcGridStatus.FrequencyError;   
        ptc->FrequencyOffset    =   mDvbcGridStatus.FrequencyOffset;  
        ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
        ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
        ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);
        ptc->CDSDFrequency      =   0;
    }
}

FResult CHsvDvbCInstallation_mgrid_Priv::igrid_StoreWeakSignalInstallationChannel()       
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(MANUAL_INSTALL)
    {
        idataacq_AcquireData();
        mDvbcGridStatus.NumChannelsAdded = idataacq_GetNumberOfDigitalChannelsFound();
        mDvbcGridStatus.NumChannelsRemoved = idataacq_GetNumberOfDigitalChannelsRemoved();
        pgdb_CommitTable(pgdb_GetCurrentTable());

        insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
        insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE); 
        mResetInstallationState();
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
}

int CHsvDvbCInstallation_mgrid_Priv::igrid_GetNumberOfDigitalChannelsFound()
{
    TraceDebug(m,"%s: retval = %d\r\n",__FUNCTION__,mDvbcGridStatus.NumChannelsAdded);
    return mDvbcGridStatus.NumChannelsAdded;
}
int CHsvDvbCInstallation_mgrid_Priv::igrid_GetNumberOfDigitalChannelsRemoved()
{
    TraceDebug(m,"%s: retval = %d\r\n",__FUNCTION__,mDvbcGridStatus.NumChannelsRemoved);
    return mDvbcGridStatus.NumChannelsRemoved;
}

int CHsvDvbCInstallation_mgrid_Priv::igrid_GetSDTType()
{
    return eurdiv_SDTActual;
}

/************************************
  provides IHsvFrontEndApiNotify  
 *************************************/

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnStationFound()
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);
    if(mDvbcGridStatus.State == StFeWait)
    {
        pmp_PmpSend(mGridPump, EvStationFound, (Nat32)NULL);
    }
}
void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnStationNotFound()
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);
    if(mDvbcGridStatus.State == StFeWait)
    {
        pmp_PmpSend(mGridPump, EvStationNotFound, (Nat32)NULL);
    }
}
void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnMeasReady( int ssm, Nat32 strength )
{
    UNUSED(ssm);
    UNUSED(strength);
}
void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnMeasAborted( int ssm )
{
    UNUSED(ssm);
}

/***************************************
  provides IHsvStreamNotify ifstrapiN
 ****************************************/

void CHsvDvbCInstallation_mgrid_Priv::igstrapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
#if 0
        switch(spid)
        {
            case HSVSPID(ActualTSService, dvb, sdt):
                if(MANUAL_INSTALL)
            {
                HSVSPTYPE(ActualTSService, dvb, sdt) service;

                if(TRUE == strapi_GetByKey(dest, HSVSPID(ActualTSService, dvb, sdt), key1, key2, key3, &service))
                {
                    if((TV_SERVICE == service.ServiceType) && (FALSE == mDvbcGridStatus.PlayStarted))
                    {
                        TraceDebug(m,"strapiN: Got a TV Service\r\n");
                        mPlayService(service.ServiceId);
                    }
                }
            }
                break;
            default:
                break;
        }
#endif    
}
void CHsvDvbCInstallation_mgrid_Priv::igstrapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    /* pavan: how do we handle dynamic updates */
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
    UNUSED(eventid);

}
void CHsvDvbCInstallation_mgrid_Priv::igstrapiN_OnRemoved  ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}
void CHsvDvbCInstallation_mgrid_Priv::igstrapiN_OnCompleted  ( HsvDestination dest, int spid)
{
    UNUSED(dest);
    UNUSED(spid);
}

/***************************************
  provides IHsvSdmControlNotify ifctrlN
 ****************************************/
void CHsvDvbCInstallation_mgrid_Priv::igctrlN_OnEvent( HsvDemux dmx, int eventid, int value)
{
    TraceDebug(m,"ctrlN_OnEvent:eventid = %d\r\n",eventid);

    UNUSED(value);
    if(mDvbcGridStatus.State == StDmxWait)
    {
        switch(eventid)
        {
            case igctrlN_DataAvailable:
                TraceDebug(m,"ifctrlN: DataAvailable\r\n");
                if(AUTO_INSTALL || UPDATE_INSTALL)
                {
                    pmp_PmpSend(mGridPump, EvDmxNtf, igctrlN_DataAvailable);
                }
                else
                {
                    /* For Manual Mode goto FuncDmxData but do not store until explicit 
                       command is issued. Deviation from DVBT */
                    pmp_PmpSend(mGridPump, EvDmxNtf, igctrlN_DataAvailable);
                }

                break;
            case igctrlN_DataNotAvailable:
                TraceDebug(m,"igctrlN: DataNotAvailable\r\n");
                pmp_PmpSend(mGridPump, EvDmxNtf, igctrlN_DataNotAvailable);
                break;
            case igctrlN_StartedCollection:
                TraceDebug(m,"igctrlN: StartedCollection\r\n");
                break;
            case igctrlN_StoppedCollection:
                TraceDebug(m,"igctrlN: StoppedCollection\r\n");
                break;
            default:
                ASSERT(FALSE);
                break;
        }   
    }
    else if((mDvbcGridStatus.State == StIdle) && mDvbcGridStatus.Active)
    {
        switch(eventid)
        {
            case igctrlN_DataAvailable:
                pmp_PmpSend(mGridPump, EvDmxNtf, igctrlN_DataAvailable);
                break;
            case igctrlN_DataNotAvailable:
            case igctrlN_StartedCollection:
            case igctrlN_StoppedCollection:
            default:
                break;
        }
    }
    UNUSED(dmx);
}

void CHsvDvbCInstallation_mgrid_Priv::mResetInstallationState(void)
{
    Nat32 errorcode = TM_OK;
    TraceDebug(m,"%s\r\n",__FUNCTION__);
    FreqTableIndex = 0;
    mDvbcGridStatus.State = StIdle;
    feapi_SetSearchRates(WINDOWID, NULL, 0, &errorcode);
    ASSERT(TM_OK == errorcode);
}

void CHsvDvbCInstallation_mgrid_Priv::igena_Enable(void)
{
    mDvbcGridStatus.Active = TRUE;
}

void CHsvDvbCInstallation_mgrid_Priv::igena_Disable(void)
{
    mDvbcGridStatus.Active = FALSE;
}
int CHsvDvbCInstallation_mgrid_Priv::igrid_GetCurrentState()
{
    int retval = igrid_stidle;
    switch(mDvbcGridStatus.State)
    {
        case StIdle: 
            retval = igrid_stidle;
            break;
        case StFeWait:
            retval = igrid_stfewait;
            break;
        case StDmxWait:
            retval = igrid_stdmxwait;
            break;
        case StDecision:
            retval = igrid_stdecision;
            break;
        default:
            ASSERT(!"Incorrect State");
            break;
    }
    return retval;
}

void CHsvDvbCInstallation_mgrid_Priv::igrid_SyncComplete(void)
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    mResetInstallationState();
    igridN_OnEvent(igridN_EventScanCompleted);
}

int CHsvDvbCInstallation_mgrid_Priv::FindHsvValue(int plfval, int* arr, int len)
{
    int i = 0;
    for( i = 0; i < len ;i++)
    {
        if(arr[i] == plfval)
        {
            return i;
        }
    }
    return 0;
}


void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnSearchInProgress( tmFe_SearchState_t state )
{
	return;
}

/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnSearchStateChanged (  tmFe_SearchState_t state  )   
{
	return;
}


void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnTvSystemDetected (  tmFe_TvSystem_t tvSystem  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnAfcFreqChanged (  Nat32 freq  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnAfcLimitReached ( Nat32 freq  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnAfcModeChanged (  void  )   
{
	return;
}



void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnConstellationDetected (  tmFe_Constellation_t  ellation  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnIqModeDetected (  tmFe_IqMode_t mode  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnCodeRateDetected (  tmFe_CodeRate_t highPrioRate ,  tmFe_CodeRate_t lowPrioRate  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnHierarchyModeDetected (  tmFe_HierarchyMode_t mode  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnGuardIntervalDetected (  tmFe_GuardInterval_t interval  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnTxModeDetected (  tmFe_TxMode_t mode  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnChanBandwidthDetected (  tmFe_ChanBandwidth_t bandwith  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnCarrierPresentChanged (  Bool carrier  )   
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igridfeN_OnBerThresholdCrossed (  Nat32 ber ,  Nat32 berThreshold  )   
{
	return;
}

/* Interfaces from IHsvdigitalscan.id */

FResult CHsvDvbCInstallation_mgrid_Priv::igrid_StartInstallation(int source, int ptc, int mode) 
{
	return 0;
}

FResult CHsvDvbCInstallation_mgrid_Priv::igrid_StopInstallation(void ) 
{
	return 0;
}
int CHsvDvbCInstallation_mgrid_Priv::igrid_GetNoOfPass(void) 
{
	return 0;
}

int CHsvDvbCInstallation_mgrid_Priv::igrid_GetCurrentPass ( void ) 
{
	return 0;
}
int CHsvDvbCInstallation_mgrid_Priv::igrid_GetTargetNitType(Nat16* NetworkId) 
{
	return 0;
}
Bool CHsvDvbCInstallation_mgrid_Priv::igrid_GetAltTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

Bool CHsvDvbCInstallation_mgrid_Priv::igrid_GetCurTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

HsvStreamPriority CHsvDvbCInstallation_mgrid_Priv::igrid_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}

void CHsvDvbCInstallation_mgrid_Priv::igrid_SetStreamPriority (HsvStreamPriority prio) 
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igrid_ClearCache(void) 
{
	return;
}

int CHsvDvbCInstallation_mgrid_Priv::igrid_GetPLPIds(int *PLPIds) 
{
	return NULL;
}

HsvHierarchyMode CHsvDvbCInstallation_mgrid_Priv::igrid_GetHierarchyMode(void) 
{
	return (HsvHierarchyMode)0;
}

void CHsvDvbCInstallation_mgrid_Priv::igrid_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid) 
{
	return;
}

int CHsvDvbCInstallation_mgrid_Priv::igrid_ZiggoGetSDTType(Nat16 Frequency) 
{
	return 0;
}

void CHsvDvbCInstallation_mgrid_Priv::igrid_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvDvbCInstallation_mgrid_Priv::igrid_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}

void CHsvDvbCInstallation_mgrid_Priv::igrid_ClearPersistent() 
{
	return;
}

void CHsvDvbCInstallation_mgrid_Priv::igrid_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


