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
 *     \file          hsvcanaldigital_mPreInstall.c
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
#include "_hsvcanaldigital_mPreInstall.h"

TRACESYMBOL(m, "dvb/installation/hsvcanaldigital_mPreInstall")

#include "hsvcanaldigital.h"





#ifndef __cplusplus

#else

#endif












t_DVBCPreScanStatus CHsvCanalDigitalInstallation_mPreInstall_Priv::s__mInstStatus;




Pump CHsvCanalDigitalInstallation_mPreInstall_Priv::s__mInstallPump;



int CHsvCanalDigitalInstallation_mPreInstall_Priv::s__mConstellation[14] =
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




#define START_FREQUENCY ( ( dvbset_GetAttribute( rins_InstallationModeAutomatic, rins_AttributeFreqStepSize ) == rins_DVBCStepSize8)?   \
                            ( ( ( dvbset_GetAttribute( CURRENT_MODE, rins_AttributeScanMode) == rins_FullScan ) ||                          \
                            ( dvbset_GetAttributeMode ( rins_InstallationModeAutomatic, rins_AttributeNetworkFreq ) == rins_AutomaticValue )   || \
							( eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite)	) ? (114 * 16) : (108 * 16))  : (108 * 16) )





#define END_FREQUENCY       ((863) * (16))







const FunctionNat32 CHsvCanalDigitalInstallation_mPreInstall_Priv::StateEventMatrix[][StMax] =
{							/*StIdle				StInit				StFeWait				StDmxWait			StDecision			StWaitAbort*/
	/*EvStart*/ 			{FNADDR(FuncStartInstall),	NULL,			NULL,					NULL,				NULL,				NULL},
	/*EvStationFound*/		{NULL,					NULL,				FNADDR(FuncStationFound), NULL, 			NULL,				NULL},
	/*EvStationNotFound*/	{NULL,					NULL,				FNADDR(FuncStationNotFound),NULL,			NULL,				FNADDR(FuncScanAborted)},
	/*EvDmxNtf*/			{NULL,					NULL,				NULL,					FNADDR(FuncDmxData),NULL,				NULL},
	/*EvMakeDecision*/		{NULL,					NULL,				NULL,					NULL,				FNADDR(FuncMakeDecision),NULL},
	/*EvStop*/				{NULL,					FNADDR(FuncStop),	FNADDR(FuncStop),		FNADDR(FuncStop),	FNADDR(FuncStop),	NULL},
	/*EvSdmStopped*/		{NULL,					FNADDR(FuncSdmStopped), NULL,				FNADDR(FuncSdmStopped), NULL,			NULL}
};



void CHsvCanalDigitalInstallation_mPreInstall_Priv::PumpHandler(int event, Nat32 param)
{
  
  if(StateEventMatrix[event][mInstStatus.State] != NULL)
   {
	   FPCALL(StateEventMatrix[event][mInstStatus.State])(param);
   }
   else
   {
	   TraceDebug(m,"Ignored event = %d, state = %d\r\n",event,mInstStatus.State);
   }

}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinspow_Init(void)
{
    mInstallPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE,"hsvcanaldigital_mPreInstall");
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinspow_TurnOn(void)
{

}
void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinspow_TurnOff(void)
{ 

}
// Need to check Mahesh
/*
void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipena_Enable(void)
{
	mInstStatus.Active = TRUE;
}
void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipena_Disable(void)
{
	mInstStatus.Active = FALSE;
}
*/


void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_Initialise(void)
{
	
	int i = 0, j = 0, slen = 0, mlen = 0;
	int aslen = 0; /* Acutal Symbol Length */
	Nat32 retval, decoder, err=TM_OK;
	
	
	TraceDebug(m,"%s\r\n",__FUNCTION__);

	retval = feapi_GetFreqRange(WINDOWID, &(mInstStatus.StartFrequency), &(mInstStatus.EndFrequency), &err);    
    ASSERT(retval == plferrids_Ok);
    ASSERT(err == TM_OK);
	if(mInstStatus.StartFrequency < START_FREQUENCY)
    {
        mInstStatus.StartFrequency = START_FREQUENCY;
    }    
	mInstStatus.ScanState = DvbcPreScanIdle;
    mInstStatus.State = StIdle;
    mInstStatus.CurrentDemux = HsvDmxMain;
    mInstStatus.Frequency = dvbset_GetAttribute(AUTO_MODE, rins_AttributeNetworkFreq);
    TraceDebug(m,"Intial Network Freq = %ld\r\n",(mInstStatus.Frequency>>4));
    mInstStatus.FrequencyMode = dvbset_GetAttributeMode(AUTO_MODE, rins_AttributeNetworkFreq);
    TraceDebug(m,"Intial Network Freq Mode = %d\r\n",mInstStatus.FrequencyMode);

    slen = dvbset_GetAttributeLength(AUTO_MODE, rins_AttributeSymbolRate);
    mlen = dvbset_GetAttributeLength(AUTO_MODE, rins_AttributeModulation);

	
	if(eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite)
    {
        if(mInstStatus.Frequency == 0)
        {
            //means USER has not SET anything & had cancelled the Network Frequency Pop-up.
            mInstStatus.Frequency = mInstStatus.StartFrequency;
            TraceNotice(m,"%s %d mDvbcQuickStatus.Frequency %ld", __FUNCTION__, __LINE__, mInstStatus.Frequency);
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

		    temprate = dvbset_GetNextAttributeValue(AUTO_MODE, rins_AttributeSymbolRate, temprate);
		    if (temprate != INVALID_SYMBOLRATE)
		    {
		        for(j = 0; j < mlen; j++)
		        {
		            if(((mlen*aslen) + j) >= MAX_SEARCH_RATES)
		            {
		                break;
		            }
		            tempconst = dvbset_GetNextAttributeValue(AUTO_MODE, rins_AttributeModulation, tempconst);
		            mInstStatus.SearchRates[(mlen*aslen) + j].rate = temprate;
		            mInstStatus.SearchRates[(mlen*aslen) + j].constellation = (tmFe_Constellation_t)mConstellation[tempconst];
		            TraceDebug(m,"Initialise: SymRate[%d] = %d\r\n", ((mlen*aslen) + j),temprate);
		            TraceDebug(m,"Initialise: Modulation[%d] = %x\r\n", ((mlen*aslen) + j),mConstellation[tempconst]);
		        }
		        aslen++;
		    }
		}
	}

	if((aslen * mlen) > MAX_SEARCH_RATES)
    {
        mInstStatus.SearchRateLen = MAX_SEARCH_RATES;
    }
    else
    {
        mInstStatus.SearchRateLen = (aslen * mlen);
    }

    TraceDebug(m,"Initialise:SearchRateLen = %d\r\n", mInstStatus.SearchRateLen);

    idataacq_Initialise(); 
	 
}


inline FResult CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_StartDigitalScan(void)
{
	FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(mInstStatus.State == StIdle)
    {
        pmp_PmpSend(mInstallPump, EvStart, (Nat32)NULL);
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;

}

inline FResult CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_StartDigitalTuning(int freq)
{
    UNUSED(freq);
    FResult retval = 0;
    ASSERT(!"mPreScan: Cannot do Manual install in PreScan Mode\r\n");
    return retval;
}

inline FResult CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_StopDigitalScan (void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(mInstStatus.State == StIdle)
    {
        retval = hsverr_InstallationNotInProgress;
    }
    else
    {
        pmp_PmpSend(mInstallPump, EvStop, (Nat32)NULL);
    }
    return retval;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetPTCInfo(HsvInstallationPTC *ptc)
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    ptc->DecoderType        =   feapi_ChanDecDvbC;   
    ptc->Frequency          =   mInstStatus.Frequency;
    ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
    ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
    ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);
}

FResult CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_StoreWeakSignalInstallationChannel()       
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);
    ASSERT(FALSE);

    retval = hsverr_InstallationCommandNotAllowed;
    return retval;
}


int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetNumberOfDigitalChannelsFound()
{
    ASSERT(FALSE);
    return 0;
}

int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetNumberOfDigitalChannelsRemoved()
{
    ASSERT(FALSE);
    return 0;
}

int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetTargetNitType(Nat16* NetworkId)
{
    UNUSED(NetworkId);
    ASSERT(FALSE);
    return rins_NitNone;
}


int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetCurrentState()
{
    int retval = ipreins_stidle;
    switch(mInstStatus.State)
    {
        case StIdle: 
            retval = ipreins_stidle;
            break;
        case StFeWait:
            retval = ipreins_stfewait;
            break;
        case StDmxWait:
            retval = ipreins_stdmxwait;
            break;
        case StDecision:
            retval = ipreins_stdecision;
            break;
        case StInit:
            retval = ipreins_stdmxwait;
            break;
        case StMax:
        default:
            break;
    }
    return retval;
}


void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnStationFound()
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    if(mInstStatus.State == StFeWait)
    {
        pmp_PmpSend( mInstallPump, EvStationFound, (Nat32)NULL);
    }
	
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnStationNotFound()
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
 	if((mInstStatus.State == StFeWait) || (mInstStatus.State == StWaitAbort))
    {
        TraceDebug(m,"%s\r\n",__FUNCTION__);
        pmp_PmpSend(mInstallPump, EvStationNotFound, (Nat32)NULL);
    }
}


void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
	UNUSED(dmx);
    UNUSED(value);
    TraceDebug(m,"ctrlN_OnEvent:eventid = %d\r\n",eventid);

    if((mInstStatus.State == StInit) || (mInstStatus.State == StDmxWait))
    {
        switch(eventid)
        {
            case ipreinsctrlN_DataAvailable:
                TraceDebug(m,"ipctrlN: DataAvailable\r\n");
                pmp_PmpSend(mInstallPump, EvDmxNtf, TRUE);
                break;
            case ipreinsctrlN_DataNotAvailable:
                TraceDebug(m,"ipctrlN: DataNotAvailable\r\n");
                pmp_PmpSend(mInstallPump, EvDmxNtf, FALSE);
                break;
            case ipreinsctrlN_StartedCollection:
                TraceDebug(m,"ipctrlN: StartedCollection\r\n");
                break;
            case ipreinsctrlN_StoppedCollection:
                TraceDebug(m,"ipctrlN: StoppedCollection\r\n");
                pmp_PmpSend(mInstallPump, EvSdmStopped, TRUE);
                break;
            default:
                break;
        }   
    }
    UNUSED(dmx);
  
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::mResetInstallationState(void)
{
    Nat32 errorcode = TM_OK;

    mInstStatus.State = StIdle;
    mInstStatus.ScanState = DvbcPreScanIdle;
    feapi_SetSearchRates(WINDOWID, NULL, 0, &errorcode);
    ASSERT(TM_OK == errorcode);
}


void CHsvCanalDigitalInstallation_mPreInstall_Priv::FuncScanAborted (int param)
{
	mResetInstallationState();
	insN_OnEvent(ipreinsctrlN_EventScanCompleted,CURRENT_MODE); 
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::FuncSdmStopped(int param)
{
    Nat32 errorcode = TM_OK;
    Nat32 srtmode = 0;
    if(StInit == mInstStatus.State)
    {
        feapi_SetSearchRates(WINDOWID, mInstStatus.SearchRates, mInstStatus.SearchRateLen, &errorcode);
        ASSERT(TM_OK == errorcode);

		feapi_SetSymbolRate(srtmode, mInstStatus.SymbolRate, &errorcode);
        ASSERT(TM_OK == errorcode);

		
        TraceDebug(m,"SetFreq = %ld symbolRate = %d \r\n",mInstStatus.Frequency,mInstStatus.SymbolRate);

		mInstStatus.State = StFeWait;
        feapi_SetFreq (WINDOWID, mInstStatus.Frequency, FALSE, &errorcode);
        ASSERT(TM_OK == errorcode);


        UNUSED(param);
        insN_OnEvent(insN_EventSearchInProgress, mInstStatus.Frequency);
    }
    else if(StDmxWait == mInstStatus.State)
    {
        mInstStatus.State = StDecision;
        pmp_PmpSend(mInstallPump, EvMakeDecision, FALSE);
    }
    UNUSED(errorcode);
}


void CHsvCanalDigitalInstallation_mPreInstall_Priv::FuncStartInstall(int param)
{
    UNUSED(param);
    Nat32 errorcode = TM_OK; 
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    mInstStatus.ScanState = DvbcPreScanScanningDefaultList;
    mInstStatus.State = StInit;
    if( ( CURRENT_MODE == AUTO_MODE ) || ( CURRENT_MODE == UPDATE_MODE ) || ( CURRENT_MODE == rins_InstallationModePreScan ) )
    {
        feapi_SetFreqStep(WINDOWID, ((dvbset_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeFreqStepSize))*16), &errorcode);
        ASSERT(TM_OK == errorcode);
		
    }
    mStopSdm(mInstStatus.CurrentDemux);

}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::FuncStationFound(int param)
{
    Nat32 errorcode = TM_OK;

	int NetworkOperator = rins_GetAttribute(AUTO_MODE,rins_AttributeNetworkOperator);
	if(NetworkOperator == rins_YouSee)
	{
		insN_OnEvent(insN_EventTuningStationFound, CURRENT_MODE);
	}
	
    feapi_GetFreq(WINDOWID, &mInstStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    TraceDebug(m,"%s : Frequency = %ld\r\n", __FUNCTION__, (mInstStatus.Frequency>>4));

    switch(CURRENT_MODE)
    {
        case PRESCAN_MODE:
            mInstStatus.State = StDmxWait;
            ctrl_StartCollection(mInstStatus.CurrentDemux, ctrl_Minimal); // Need to check Mahesh
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::FuncStationNotFound(int param)
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    switch(CURRENT_MODE)
    {
        case PRESCAN_MODE:
            TraceDebug(m,"State set to StDecision\r\n");
            mInstStatus.State = StDecision;
            if(mInstStatus.FrequencyMode == rins_ManualValue)
            {
                insN_OnEvent(insN_EventTuningStationNotFound, CURRENT_MODE);
            }
            pmp_PmpSend(mInstallPump, EvMakeDecision, FALSE);
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}


void CHsvCanalDigitalInstallation_mPreInstall_Priv::FuncDmxData(int param)
{
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    switch(CURRENT_MODE)
    {
        case PRESCAN_MODE:
            {
                if(mOnNitAvailable())
                {
                    mInstStatus.State = StDecision;
                    pmp_PmpSend(mInstallPump, EvMakeDecision, TRUE);
                }
                else
                {
                    mStopSdm(mInstStatus.CurrentDemux);
                }
            }
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::FuncMakeDecision(int param)
	{
		Nat32 errorcode = TM_OK;
		Nat32 srtmode = 0;
	
		TraceDebug(m,"%s\r\n",__FUNCTION__);
	
		if(param == TRUE)
		{
			mInstStatus.State = StWaitAbort;
			feapi_StopSearch (WINDOWID, &errorcode);
			if(errorcode == IHsvFrontEndApi_SearchStopped)
			{
				mResetInstallationState();
				insN_OnEvent(ipreinsN_EventScanCompleted,CURRENT_MODE);
			}
		}
		else
		{
	
	
			switch(CURRENT_MODE)
			{
				case PRESCAN_MODE:
					switch(mInstStatus.ScanState)
					{
						case DvbcPreScanIdle:
							ASSERT(FALSE);
							break;
	
						case DvbcPreScanScanningDefaultList:
							mInstStatus.Frequency = dvbset_GetNextAttributeValue(AUTO_MODE, rins_AttributeNetworkFreq, mInstStatus.Frequency);
							mInstStatus.State = StFeWait;
							if(INVALID_FREQUENCY != mInstStatus.Frequency)
							{
								/*PVD: This is not required. StartSearch should solve*/
								//TraceDebug(m,"%s : %d :  using the next frequency form homing list freq = %ldMHz\n", __FUNCTION__, __LINE__, (mInstStatus.Frequency >> 4));
								feapi_SetSymbolRate(srtmode, mInstStatus.SymbolRate, &errorcode);
								ASSERT(TM_OK == errorcode);
			
								feapi_SetFreq (WINDOWID, mInstStatus.Frequency, FALSE, &errorcode);
								insN_OnEvent(insN_EventSearchInProgress,mInstStatus.Frequency); 
								ASSERT(TM_OK == errorcode);
							}
							else
							{
								TraceDebug(m,"%s : %d :  exhausted the homing frequency list, starting scan from beginning with freq = %dMHz\n", __FUNCTION__, __LINE__, (START_FREQUENCY >> 4));
								if(mInstStatus.FrequencyMode == rins_ManualValue)
								{
									TraceDebug(m,"MakeDecision: NIT OTHER/ACTUAL not found, Scan complete\r\n");
									mResetInstallationState();
									insN_OnEvent(ipreinsN_EventScanCompleted,CURRENT_MODE);
								}
								else
								{
									mInstStatus.ScanState = DvbcPreScanScanningNetworkFreq;
									mInstStatus.Frequency = mInstStatus.StartFrequency;
	
									TraceNotice(m,"%s %d mDvbcPreScanStatus.Frequency %ld", __FUNCTION__, __LINE__, mInstStatus.Frequency);
									feapi_StartSearch(WINDOWID, mInstStatus.Frequency, tmFe_SmDefault, mInstStatus.EndFrequency, &errorcode );
									ASSERT(TM_OK == errorcode);
									insN_OnEvent(insN_EventSearchInProgress,mInstStatus.Frequency); 
								}
							}
	
							break;
	
						case DvbcPreScanScanningNetworkFreq:
							feapi_GetFreq(WINDOWID, &mInstStatus.Frequency, &errorcode);
							TraceDebug(m,"%s : %d Frequency[%d] \n", __FUNCTION__, __LINE__,mInstStatus.Frequency);
						
							ASSERT(TM_OK == errorcode);
							if(mInstStatus.Frequency < mInstStatus.EndFrequency)
							{
								/* End of frequency band is not reached yet. Continue tuning */
								TraceDebug(m,"%s : %d\n", __FUNCTION__, __LINE__);
								mInstStatus.State = StFeWait;
								feapi_StartSearch(WINDOWID, mInstStatus.Frequency, tmFe_SmDefault, mInstStatus.EndFrequency, &errorcode ); /* ANEESH: TODO: Confirm 2nd param */
								ASSERT(TM_OK == errorcode);
							}
							else
							{
								TraceDebug(m,"MakeDecision: NIT OTHER/ACTUAL not found, Scan complete\r\n");
								/* ANEESH: Just see in case testing done with some higher freq near to EndFreq. 
									Gap can be less than 8Mhz. This will be causing issues in QuickScan */
								//feapi_StopSearch (WINDOWID, &errorcode);
								mResetInstallationState();
								insN_OnEvent(ipreinsN_EventScanCompleted,CURRENT_MODE);
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


void CHsvCanalDigitalInstallation_mPreInstall_Priv::FuncStop(int param)
{
    tmErrorCode_t errorcode = TM_OK;
    TraceDebug(m,"%s\r\n",__FUNCTION__);

    switch(mInstStatus.State)
    {
        case StFeWait:
            feapi_StopSearch(WINDOWID, &errorcode);
            ASSERT(TM_OK  ==  errorcode);
            break;
        case StDmxWait:
            ctrl_StopCollection(mInstStatus.CurrentDemux);
            break;
        case StDecision:
            TraceDebug(m,"Nothing can be done ??\r\n");
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    mResetInstallationState();
    insN_OnEvent(ipreinsN_EventScanStopped,CURRENT_MODE);
    UNUSED(param);
}


Bool CHsvCanalDigitalInstallation_mPreInstall_Priv::mOnNitAvailable()
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


void CHsvCanalDigitalInstallation_mPreInstall_Priv::mStopSdm(HsvDemux dmx)
{
    if(ctrl_GetMode(dmx) == ctrl_Idle)
    {
        pmp_PmpSend(mInstallPump, EvSdmStopped, TRUE);
    }
    else
    {
        ctrl_StopCollection(dmx);
    }
}
FResult CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_StartInstallation(int source, int ptc, int mode) 
{
	TraceNotice(m,"[%s][%d] \n",__FUNCTION__,__LINE__);
	FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r\n",__FUNCTION__);

    if(mInstStatus.State == StIdle)
    {
        pmp_PmpSend(mInstallPump, EvStart, (Nat32)NULL);
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
	
	return 0;
}
FResult CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_StopInstallation(void ) 
{
	return 0;
}

int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetNoOfPass(void) 
{
	return 0;
}

int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetCurrentPass ( void ) 
{
	return 0;
}
int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetSDTType() 
{
	return 0;
}
Bool CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetAltTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

Bool CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetCurTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}
HsvStreamPriority CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_SetStreamPriority (HsvStreamPriority prio) 
{
	return;
}
void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_SyncComplete(void)     
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_ClearCache(void) 
{
	return;
}
int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetPLPIds(int *PLPIds) 
{
	return NULL;
}

HsvHierarchyMode CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetHierarchyMode(void) 
{
	return (HsvHierarchyMode)0;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid) 
{
	return;
}

int CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_ZiggoGetSDTType(Nat16 Frequency) 
{
	return 0;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}
void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_ClearPersistent() 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreins_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}
void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnMeasReady( int ssm, Nat32 strength ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvCanalDigitalInstallation_mPreInstall_Priv::ipreinsfeapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}





