/**********************************************************************
 *
 *   C Source:       hsvdvbcins_mprescan.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    nareshj %
 *   %date_created:  Wed Aug 22 21:24:23 2012 %
 *
 **********************************************************************/

#include "_hsvdvbcins_mprescan.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbcins_mprescan")

#include "hsvdvbcins.h"

/**************************************************************************
 * Macros and types
 **************************************************************************/




#ifndef __cplusplus

#else

#endif










/* keep this struct consistent with macq.c 
   cable ds moved to dvbcins.h */

/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/















/****************************************************************************
 * Static variables
 ****************************************************************************/
Pump CHsvDvbCInstallation_mprescan_Priv::s__mPreScanPump;

t_DVBCPreScanStatus CHsvDvbCInstallation_mprescan_Priv::s__mDvbcPreScanStatus;


int CHsvDvbCInstallation_mprescan_Priv::s__mConstellation[14] =
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




const FunctionNat32 CHsvDvbCInstallation_mprescan_Priv::StateEventMatrix[][StMax] =
{                       	/*StIdle            	StInit          	StFeWait            	StDmxWait      		StDecision			StWaitAbort*/
    /*EvStart*/             {FNADDR(FuncStartInstall),  NULL,           NULL,               	NULL,           	NULL,				NULL},
    /*EvStationFound*/      {NULL,              	NULL,           	FNADDR(FuncStationFound), NULL,           	NULL,				NULL},
    /*EvStationNotFound*/   {NULL,              	NULL,           	FNADDR(FuncStationNotFound),NULL,           NULL,				FNADDR(FuncScanAborted)},
    /*EvDmxNtf*/            {NULL,              	NULL,           	NULL,               	FNADDR(FuncDmxData),NULL,				NULL},
    /*EvMakeDecision*/      {NULL,              	NULL,           	NULL,              	 	NULL,           	FNADDR(FuncMakeDecision),NULL},
    /*EvStop*/              {NULL,              	FNADDR(FuncStop), 	FNADDR(FuncStop),      	FNADDR(FuncStop),   FNADDR(FuncStop),	NULL},
    /*EvSdmStopped*/        {NULL,              	FNADDR(FuncSdmStopped), NULL,               FNADDR(FuncSdmStopped), NULL,			NULL}
};
                                          

/*******************************************FuncSdmStopped, *********************************
 * Static functions Implementation
 ****************************************************************************/
void CHsvDvbCInstallation_mprescan_Priv::PumpHandler(int event, Nat32 param )
{
    if(StateEventMatrix[event][mDvbcPreScanStatus.State] != NULL)
    {
        FPCALL(StateEventMatrix[event][mDvbcPreScanStatus.State])(param);
    }
    else
    {
        TraceDebug(m,"Ignored event = %d, state = %d\r\n",event,mDvbcPreScanStatus.State);
    }
}

/***************************
  provides IHsvPower
 ****************************/
void CHsvDvbCInstallation_mprescan_Priv::iprescanpow_Init()
{
    mPreScanPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE, "hsvdvbcins_mprescan_pmp");
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanpow_TurnOn()
{
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanpow_TurnOff()
{
}

void CHsvDvbCInstallation_mprescan_Priv::ipena_Enable(void)
{
    mDvbcPreScanStatus.Active = TRUE;
}

void CHsvDvbCInstallation_mprescan_Priv::ipena_Disable(void)
{
    mDvbcPreScanStatus.Active = FALSE;
}

/************************************
  provides IHsvDigitalScan iprescan
 *************************************/
void CHsvDvbCInstallation_mprescan_Priv::iprescan_Initialise(void)
{
    int i = 0, j = 0, slen = 0, mlen = 0;
    int aslen = 0; /* Acutal Symbol Length */
    Nat32 retval, decoder, err=TM_OK;


    TraceDebug(m,"%s\r\n",__FUNCTION__);


    retval = feapi_GetFreqRange(WINDOWID, &(mDvbcPreScanStatus.StartFrequency), &(mDvbcPreScanStatus.EndFrequency), &err);    
    ASSERT(retval == plferrids_Ok);
    ASSERT(err == TM_OK);
    if(mDvbcPreScanStatus.StartFrequency < START_FREQUENCY)
    {
        mDvbcPreScanStatus.StartFrequency = START_FREQUENCY;
    }       
    mDvbcPreScanStatus.ScanState = DvbcPreScanIdle;
    mDvbcPreScanStatus.State = StIdle;
    mDvbcPreScanStatus.CurrentDemux = HsvDmxMain;
    mDvbcPreScanStatus.Frequency = idvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq);
    TraceDebug(m,"Intial Network Freq = %ld\r\n",(mDvbcPreScanStatus.Frequency>>4));
    mDvbcPreScanStatus.FrequencyMode = idvbset_GetAttributeMode(AUTO_MODE, rins_AttributeNetworkFreq);
    TraceDebug(m,"Intial Network Freq Mode = %d\r\n",mDvbcPreScanStatus.FrequencyMode);

    slen = idvbset_GetAttributeLength(AUTO_MODE, rins_AttributeSymbolRate);
    mlen = idvbset_GetAttributeLength(AUTO_MODE, rins_AttributeModulation);

    if(eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite)
    {
        if(mDvbcPreScanStatus.Frequency == 0)
        {
            //means USER has not SET anything & had cancelled the Network Frequency Pop-up.
            mDvbcPreScanStatus.Frequency = mDvbcPreScanStatus.StartFrequency;
            TraceNotice(m,"%s %d mDvbcQuickStatus.Frequency %ld", __FUNCTION__, __LINE__, mDvbcPreScanStatus.Frequency);
        }
    }
    if((slen * mlen) >= MAX_SEARCH_RATES)
    {
        ASSERT(!"Combination of sym rate and mod cannot be so high");
    }
    {
        int temprate = INVALID_SYMBOLRATE;
        for(i = 0; i < slen; i++)
        {
            int tempconst = HsvUnknownConstellation;

            temprate = idvbset_GetNextAttributeValue(AUTO_MODE, rins_AttributeSymbolRate, temprate);
            if (temprate != INVALID_SYMBOLRATE)
            {
                for(j = 0; j < mlen; j++)
                {
                    if(((mlen*aslen) + j) >= MAX_SEARCH_RATES)
                    {
                        break;
                    }
                    tempconst = idvbset_GetNextAttributeValue(AUTO_MODE, rins_AttributeModulation, tempconst);
                    mDvbcPreScanStatus.SearchRates[(mlen*aslen) + j].rate = temprate;
                    mDvbcPreScanStatus.SearchRates[(mlen*aslen) + j].constellation = (tmFe_Constellation_t)mConstellation[tempconst];
                    TraceDebug(m,"Initialise: SymRate[%d] = %d\r\n", ((mlen*aslen) + j),temprate);
                    TraceDebug(m,"Initialise: Modulation[%d] = %x\r\n", ((mlen*aslen) + j),mConstellation[tempconst]);
                }
                aslen++;
            }
        }
    }
    if((aslen * mlen) > MAX_SEARCH_RATES)
    {
        mDvbcPreScanStatus.SearchRateLen = MAX_SEARCH_RATES;
    }
    else
    {
        mDvbcPreScanStatus.SearchRateLen = (aslen * mlen);
    }

    TraceDebug(m,"Initialise:SearchRateLen = %d\r\n", mDvbcPreScanStatus.SearchRateLen);

    idataacq_Initialise();
}

FResult CHsvDvbCInstallation_mprescan_Priv::iprescan_StartDigitalScan(void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(mDvbcPreScanStatus.State == StIdle)
    {
        pmp_PmpSend(mPreScanPump, EvStart, (Nat32)NULL);
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
}

FResult CHsvDvbCInstallation_mprescan_Priv::iprescan_StartDigitalTuning(int freq)
{
    UNUSED(freq);
    FResult retval = 0;
    ASSERT(!"mPreScan: Cannot do Manual install in PreScan Mode\r\n");
    return retval;
}

FResult CHsvDvbCInstallation_mprescan_Priv::iprescan_StopDigitalScan (void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(mDvbcPreScanStatus.State == StIdle)
    {
        retval = hsverr_InstallationNotInProgress;
    }
    else
    {
        pmp_PmpSend(mPreScanPump, EvStop, (Nat32)NULL);
    }
    return retval;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescan_GetPTCInfo(HsvInstallationPTC *ptc)
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    ptc->DecoderType        =   feapi_ChanDecDvbC;   
    ptc->Frequency          =   mDvbcPreScanStatus.Frequency;
    ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
    ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
    ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);
}

FResult CHsvDvbCInstallation_mprescan_Priv::iprescan_StoreWeakSignalInstallationChannel()       
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);
    ASSERT(FALSE);

    retval = hsverr_InstallationCommandNotAllowed;
    return retval;
}

int CHsvDvbCInstallation_mprescan_Priv::iprescan_GetNumberOfDigitalChannelsFound()
{
    ASSERT(FALSE);
    return 0;
}

int CHsvDvbCInstallation_mprescan_Priv::iprescan_GetNumberOfDigitalChannelsRemoved()
{
    ASSERT(FALSE);
    return 0;
}

int CHsvDvbCInstallation_mprescan_Priv::iprescan_GetTargetNitType(Nat16* NetworkId)
{
    UNUSED(NetworkId);
    ASSERT(FALSE);
    return rins_NitNone;
}

int CHsvDvbCInstallation_mprescan_Priv::iprescan_GetCurrentState()
{
    int retval = iprescan_stidle;
    switch(mDvbcPreScanStatus.State)
    {
        case StIdle: 
            retval = iprescan_stidle;
            break;
        case StFeWait:
            retval = iprescan_stfewait;
            break;
        case StDmxWait:
            retval = iprescan_stdmxwait;
            break;
        case StDecision:
            retval = iprescan_stdecision;
            break;
        case StInit:
            retval = iprescan_stdmxwait;
            break;
        case StMax:
        default:
            break;
    }
    return retval;
}

/************************************
  provides IHsvFrontEndApiNotify  
 *************************************/

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnStationFound()
{
    if(mDvbcPreScanStatus.State == StFeWait)
    {
        TraceDebug(m,"%s\r\n",__FUNCTION__);
        pmp_PmpSend(mPreScanPump, EvStationFound, (Nat32)NULL);
    }
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnStationNotFound()
{
    if((mDvbcPreScanStatus.State == StFeWait) || (mDvbcPreScanStatus.State == StWaitAbort))
    {
        TraceDebug(m,"%s\r\n",__FUNCTION__);
        pmp_PmpSend(mPreScanPump, EvStationNotFound, (Nat32)NULL);
    }
}

/********************************************
  provides IHsvSdmControlNotifyEx ipctrlN
 *********************************************/
void CHsvDvbCInstallation_mprescan_Priv::ipctrlN_OnEvent( HsvDemux dmx, int eventid, int value)
{
    UNUSED(dmx);
    UNUSED(value);
    TraceDebug(m,"ctrlN_OnEvent:eventid = %d\r\n",eventid);

    if((mDvbcPreScanStatus.State == StInit) || (mDvbcPreScanStatus.State == StDmxWait))
    {
        switch(eventid)
        {
            case ipctrlN_DataAvailable:
                TraceDebug(m,"ipctrlN: DataAvailable\r\n");
                pmp_PmpSend(mPreScanPump, EvDmxNtf, TRUE);
                break;
            case ipctrlN_DataNotAvailable:
                TraceDebug(m,"ipctrlN: DataNotAvailable\r\n");
                pmp_PmpSend(mPreScanPump, EvDmxNtf, FALSE);
                break;
            case ipctrlN_StartedCollection:
                TraceDebug(m,"ipctrlN: StartedCollection\r\n");
                break;
            case ipctrlN_StoppedCollection:
                TraceDebug(m,"ipctrlN: StoppedCollection\r\n");
                pmp_PmpSend(mPreScanPump, EvSdmStopped, TRUE);
                break;
            default:
                break;
        }   
    }
    UNUSED(dmx);
}

void CHsvDvbCInstallation_mprescan_Priv::FuncScanAborted (int param)
{
	mResetInstallationState();
	iprescanN_OnEvent(iprescanN_EventScanCompleted);
}

void CHsvDvbCInstallation_mprescan_Priv::FuncSdmStopped(int param)
{
    Nat32 errorcode = TM_OK;
    Nat32 srtmode = 0;
    if(StInit == mDvbcPreScanStatus.State)
    {
        feapi_SetSearchRates(WINDOWID, mDvbcPreScanStatus.SearchRates, mDvbcPreScanStatus.SearchRateLen, &errorcode);
        ASSERT(TM_OK == errorcode);

	feapi_SetSymbolRate(srtmode, mDvbcPreScanStatus.SymbolRate, &errorcode);
        ASSERT(TM_OK == errorcode);

		
        TraceDebug(m,"SetFreq = %ld symbolRate = %d \r\n",mDvbcPreScanStatus.Frequency,mDvbcPreScanStatus.SymbolRate);

	mDvbcPreScanStatus.State = StFeWait;
        feapi_SetFreq (WINDOWID, mDvbcPreScanStatus.Frequency, FALSE, &errorcode);
        ASSERT(TM_OK == errorcode);


        UNUSED(param);
        insN_OnEvent(insN_EventSearchInProgress, mDvbcPreScanStatus.Frequency);
    }
    else if(StDmxWait == mDvbcPreScanStatus.State)
    {
        mDvbcPreScanStatus.State = StDecision;
        pmp_PmpSend(mPreScanPump, EvMakeDecision, FALSE);
    }
    UNUSED(errorcode);
}

void CHsvDvbCInstallation_mprescan_Priv::FuncStartInstall(int param)
{
    UNUSED(param);
    Nat32 errorcode = TM_OK; 
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    mDvbcPreScanStatus.ScanState = DvbcPreScanScanningDefaultList;
    mDvbcPreScanStatus.State = StInit;
    if( ( CURRENT_MODE == AUTO_MODE ) || ( CURRENT_MODE == UPDATE_MODE ) || ( CURRENT_MODE == rins_InstallationModePreScan ) )
    {
        feapi_SetFreqStep(WINDOWID, ((idvbset_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeFreqStepSize))*16), &errorcode);
        ASSERT(TM_OK == errorcode);
    }
    mStopSdm(mDvbcPreScanStatus.CurrentDemux);

}

void CHsvDvbCInstallation_mprescan_Priv::FuncStationFound(int param)
{
    Nat32 errorcode = TM_OK;

    feapi_GetFreq(WINDOWID, &mDvbcPreScanStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    TraceDebug(m,"%s : Frequency = %ld\r\n", __FUNCTION__, (mDvbcPreScanStatus.Frequency>>4));

    switch(CURRENT_MODE)
    {
        case PRESCAN_MODE:
            mDvbcPreScanStatus.State = StDmxWait;
            ctrl_StartCollection(mDvbcPreScanStatus.CurrentDemux, ctrl_Minimal);
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}

void CHsvDvbCInstallation_mprescan_Priv::FuncStationNotFound(int param)
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    switch(CURRENT_MODE)
    {
        case PRESCAN_MODE:
            TraceDebug(m,"State set to StDecision\r\n");
            mDvbcPreScanStatus.State = StDecision;
            if(mDvbcPreScanStatus.FrequencyMode == rins_ManualValue)
            {
                insN_OnEvent(insN_EventTuningStationNotFound, CURRENT_MODE);
            }
            pmp_PmpSend(mPreScanPump, EvMakeDecision, FALSE);
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}

void CHsvDvbCInstallation_mprescan_Priv::FuncDmxData(int param)
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    switch(CURRENT_MODE)
    {
        case PRESCAN_MODE:
            {
                if(mOnNitAvailable())
                {
                    mDvbcPreScanStatus.State = StDecision;
                    pmp_PmpSend(mPreScanPump, EvMakeDecision, TRUE);
                }
                else
                {
                    mStopSdm(mDvbcPreScanStatus.CurrentDemux);
                }
            }
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}

void CHsvDvbCInstallation_mprescan_Priv::FuncMakeDecision(int param)
{
    Nat32 errorcode = TM_OK;
    Nat32 srtmode = 0;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(param == TRUE)
    {
		mDvbcPreScanStatus.State = StWaitAbort;
		feapi_StopSearch (WINDOWID, &errorcode);
		if(errorcode == IHsvFrontEndApi_SearchStopped)
		{
			mResetInstallationState();
			iprescanN_OnEvent(iprescanN_EventScanCompleted);
		}
    }
    else
    {


        switch(CURRENT_MODE)
        {
            case PRESCAN_MODE:
                switch(mDvbcPreScanStatus.ScanState)
                {
                    case DvbcPreScanIdle:
                        ASSERT(FALSE);
                        break;

                    case DvbcPreScanScanningDefaultList:
                        mDvbcPreScanStatus.Frequency = idvbset_GetNextAttributeValue(AUTO_MODE, rins_AttributeNetworkFreq, mDvbcPreScanStatus.Frequency);
                        mDvbcPreScanStatus.State = StFeWait;
                        if(INVALID_FREQUENCY != mDvbcPreScanStatus.Frequency)
                        {
                            /*PVD: This is not required. StartSearch should solve*/
                            TraceDebug(m,"%s : %d :  using the next frequency form homing list freq = %ldMHz\n", __FUNCTION__, __LINE__, (mDvbcPreScanStatus.Frequency >> 4));
			    feapi_SetSymbolRate(srtmode, mDvbcPreScanStatus.SymbolRate, &errorcode);
        		    ASSERT(TM_OK == errorcode);
		
                            feapi_SetFreq (WINDOWID, mDvbcPreScanStatus.Frequency, FALSE, &errorcode);
                            insN_OnEvent(insN_EventSearchInProgress,mDvbcPreScanStatus.Frequency); 
                            ASSERT(TM_OK == errorcode);
                        }
                        else
                        {
                            TraceDebug(m,"%s : %d :  exhausted the homing frequency list, starting scan from beginning with freq = %dMHz\n", __FUNCTION__, __LINE__, (START_FREQUENCY >> 4));
                            if(mDvbcPreScanStatus.FrequencyMode == rins_ManualValue)
                            {
                                TraceDebug(m,"MakeDecision: NIT OTHER/ACTUAL not found, Scan complete\r\n");
                                mResetInstallationState();
                                iprescanN_OnEvent(iprescanN_EventScanCompleted);
                            }
                            else
                            {
                                mDvbcPreScanStatus.ScanState = DvbcPreScanScanningNetworkFreq;
                                mDvbcPreScanStatus.Frequency = mDvbcPreScanStatus.StartFrequency;

                                TraceNotice(m,"%s %d mDvbcPreScanStatus.Frequency %ld", __FUNCTION__, __LINE__, mDvbcPreScanStatus.Frequency);
								feapi_StartSearch(WINDOWID, mDvbcPreScanStatus.Frequency, tmFe_SmDefault, mDvbcPreScanStatus.EndFrequency, &errorcode );
                                ASSERT(TM_OK == errorcode);
                                insN_OnEvent(insN_EventSearchInProgress,mDvbcPreScanStatus.Frequency); 
                            }
                        }

                        break;

                    case DvbcPreScanScanningNetworkFreq:
                        feapi_GetFreq(WINDOWID, &mDvbcPreScanStatus.Frequency, &errorcode);
                        ASSERT(TM_OK == errorcode);
                        if(mDvbcPreScanStatus.Frequency < mDvbcPreScanStatus.EndFrequency)
                        {
                            /* End of frequency band is not reached yet. Continue tuning */
                            TraceDebug(m,"%s : %d\n", __FUNCTION__, __LINE__);
                            mDvbcPreScanStatus.State = StFeWait;
                            feapi_StartSearch(WINDOWID, mDvbcPreScanStatus.Frequency, tmFe_SmDefault, mDvbcPreScanStatus.EndFrequency, &errorcode ); /* ANEESH: TODO: Confirm 2nd param */
                            ASSERT(TM_OK == errorcode);
                        }
                        else
                        {
                            TraceDebug(m,"MakeDecision: NIT OTHER/ACTUAL not found, Scan complete\r\n");
							/* ANEESH: Just see in case testing done with some higher freq near to EndFreq. 
								Gap can be less than 8Mhz. This will be causing issues in QuickScan */
							//feapi_StopSearch (WINDOWID, &errorcode);
                            mResetInstallationState();
                            iprescanN_OnEvent(iprescanN_EventScanCompleted);
                        }
                        break;

                    default:
                        ASSERT(FALSE);
                        break;
                }        
                break;

            default:
                /* should not reach here */
                ASSERT(FALSE);
                break;
        }
    }
    UNUSED(param);
}

void CHsvDvbCInstallation_mprescan_Priv::FuncStop(int param)
{
    tmErrorCode_t errorcode = TM_OK;
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    switch(mDvbcPreScanStatus.State)
    {
        case StFeWait:
            feapi_StopSearch(WINDOWID, &errorcode);
            ASSERT(TM_OK  ==  errorcode);
            break;
        case StDmxWait:
            ctrl_StopCollection(mDvbcPreScanStatus.CurrentDemux);
            break;
        case StDecision:
            TraceDebug(m,"Nothing can be done ??\r\n");
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    mResetInstallationState();
    iprescanN_OnEvent(iprescanN_EventScanStopped);
    UNUSED(param);
}

Bool CHsvDvbCInstallation_mprescan_Priv::mOnNitAvailable()
{
    Bool ret = FALSE;
    Nat16 NetworkID;
    Nat32 lONIDValue;
    Bool lValidNIDFound = FALSE;
    Bool lValidONIDFound = FALSE;

    Nat16 lOtherNIDLen ;
    HSVSPTYPE(OtherNetworkIDInfo, dvb, nit)  OtherNIDIndex;    //Hsv##std##table##ppty##Type   hsvdvbnitOtherNetworkIDInfoType
    int i;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    lOtherNIDLen = strapi_GetSize(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit));

    TraceDebug(m,"%d %s ", __LINE__, __FUNCTION__);

    if(strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkID))
    {
        TraceDebug(m,"%d: strapi_GetByKey succeeded for Actual NetworkId (%d)\n", __LINE__, NetworkID);
        if( VALID_NTKID(NetworkID) || (eurdiv_InstallTestStreams(CURRENT_MODE, rins_Cable)  == eurdiv_Install) )
        {
            TraceDebug(m,"%d %s ", __LINE__, __FUNCTION__);
            lValidNIDFound = TRUE;
            if((strapi_GetSize(HsvMain, HSVSPID(ActualCableDS, dvb, nit))) > 0)
            {
                TraceDebug(m,"%d %s ", __LINE__, __FUNCTION__);
                ret = TRUE;
            }
        }
        else
        {
            TraceDebug(m,"NitAvail: Invalid NetworkID\r\n");
        }
    }
    if( (lOtherNIDLen > 0) && (lValidNIDFound == FALSE) )
    {
        TraceDebug(m,"%d: strapi_GetSize > 0 for Other NetworkId\n", __LINE__);

        for(i = 0; i < lOtherNIDLen; i++)
        {
            if(strapi_GetByIndex(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit), i, (void*)(&OtherNIDIndex)))
            {
                if( VALID_NTKID(OtherNIDIndex.NetworkId)  || (eurdiv_InstallTestStreams(CURRENT_MODE, rins_Cable)  == eurdiv_Install) )
                {
                    TraceDebug(m,"%d %s ", __LINE__, __FUNCTION__);
                    lValidNIDFound = TRUE;
                    ret = TRUE;
                    break;
                }
            }
        }
    }

    if((strapi_GetByKey(HsvMain, HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0,&lONIDValue)))
    {
        if(ISONID_VALID(lONIDValue))
        {
            TraceDebug(m,"%d %s ", __LINE__, __FUNCTION__);
            lValidONIDFound = TRUE;
        }
    }

    if(eurdiv_InstallTestStreams(CURRENT_MODE, rins_Cable)  == eurdiv_NotInstall)
    {
        TraceDebug(m,"%d %s ", __LINE__, __FUNCTION__);
        if((lValidONIDFound == FALSE) || (lValidNIDFound == FALSE))
        {
            TraceDebug(m,"%d %s Event Raised to Apps for NID INVALID ", __LINE__,__FUNCTION__);
            insN_OnEvent(insN_EventNIDInvalid, TRUE);
        }
    }
    return ret;
}

void CHsvDvbCInstallation_mprescan_Priv::mResetInstallationState(void)
{
    Nat32 errorcode = TM_OK;

    mDvbcPreScanStatus.State = StIdle;
    mDvbcPreScanStatus.ScanState = DvbcPreScanIdle;
    feapi_SetSearchRates(WINDOWID, NULL, 0, &errorcode);
    ASSERT(TM_OK == errorcode);
}

void CHsvDvbCInstallation_mprescan_Priv::mStopSdm(HsvDemux dmx)
{
    if(ctrl_GetMode(dmx) == ctrl_Idle)
    {
        pmp_PmpSend(mPreScanPump, EvSdmStopped, TRUE);
    }
    else
    {
        ctrl_StopCollection(dmx);
    }
}

/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnSearchStateChanged (  tmFe_SearchState_t state  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnSearchInProgress (  tmFe_SearchState_t state  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnTvSystemDetected (  tmFe_TvSystem_t tvSystem  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnAfcFreqChanged (  Nat32 freq  )   
{
	return;
}
void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnAfcLimitReached ( Nat32 freq  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnAfcModeChanged (  void  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnMeasReady (  int ssm ,  Nat32 strength  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnMeasAborted (  int ssm  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnConstellationDetected (  tmFe_Constellation_t  ellation  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnIqModeDetected (  tmFe_IqMode_t mode  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnCodeRateDetected (  tmFe_CodeRate_t highPrioRate ,  tmFe_CodeRate_t lowPrioRate  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnHierarchyModeDetected (  tmFe_HierarchyMode_t mode  )   
{
	return;
}
void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnGuardIntervalDetected (  tmFe_GuardInterval_t interval  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnTxModeDetected (  tmFe_TxMode_t mode  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnChanBandwidthDetected (  tmFe_ChanBandwidth_t bandwith  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnCarrierPresentChanged (  Bool carrier  )   
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescanfeN_OnBerThresholdCrossed (  Nat32 ber ,  Nat32 berThreshold  )   
{
	return;
}

FResult CHsvDvbCInstallation_mprescan_Priv::iprescan_StartInstallation(int source, int ptc, int mode) 
{
	return 0;
}

FResult CHsvDvbCInstallation_mprescan_Priv::iprescan_StopInstallation(void ) 
{
	return 0;
}
int CHsvDvbCInstallation_mprescan_Priv::iprescan_GetNoOfPass(void) 
{
	return 0;
}

int CHsvDvbCInstallation_mprescan_Priv::iprescan_GetCurrentPass ( void ) 
{
	return 0;
}
int CHsvDvbCInstallation_mprescan_Priv::iprescan_GetSDTType() 
{
	return 0;
}

Bool CHsvDvbCInstallation_mprescan_Priv::iprescan_GetAltTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

Bool CHsvDvbCInstallation_mprescan_Priv::iprescan_GetCurTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}
HsvStreamPriority CHsvDvbCInstallation_mprescan_Priv::iprescan_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescan_SetStreamPriority (HsvStreamPriority prio) 
{
	return;
}
void CHsvDvbCInstallation_mprescan_Priv::iprescan_SyncComplete(void)     
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescan_ClearCache(void) 
{
	return;
}
int CHsvDvbCInstallation_mprescan_Priv::iprescan_GetPLPIds(int *PLPIds) 
{
	return NULL;
}

HsvHierarchyMode CHsvDvbCInstallation_mprescan_Priv::iprescan_GetHierarchyMode(void) 
{
	return (HsvHierarchyMode)0;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescan_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid) 
{
	return;
}

int CHsvDvbCInstallation_mprescan_Priv::iprescan_ZiggoGetSDTType(Nat16 Frequency) 
{
	return 0;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescan_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvDvbCInstallation_mprescan_Priv::iprescan_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}
void CHsvDvbCInstallation_mprescan_Priv::iprescan_ClearPersistent() 
{
	return;
}

void CHsvDvbCInstallation_mprescan_Priv::iprescan_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}

