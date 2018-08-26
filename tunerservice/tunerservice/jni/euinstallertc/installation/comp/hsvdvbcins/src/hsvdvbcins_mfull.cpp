/**********************************************************************
 *
 *   C Source:       hsvdvbcins_mfull.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    nareshj %
 *   %date_created:  Tue Sep 11 19:45:38 2012 %
 *
 **********************************************************************/
#include "_hsvdvbcins_mfull.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbcins_mfull")

#include "hsvdvbcins.h"

#include "cabletuner_attributes.h"

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
Pump CHsvDvbCInstallation_mfull_Priv::s__mFullPump;

t_DVBCFullStatus CHsvDvbCInstallation_mfull_Priv::s__mDvbcFullStatus;

t_CableDSDesc CHsvDvbCInstallation_mfull_Priv::s__mFlashCableDS;

char CHsvDvbCInstallation_mfull_Priv::s__mDirName[MAX_CHARACTERS];

char CHsvDvbCInstallation_mfull_Priv::s__mFileName[MAX_CHARACTERS];
Nat32 CHsvDvbCInstallation_mfull_Priv::s__mCacheFrequency[MAX_TS_FREQUENCIES];


const FunctionNat32 CHsvDvbCInstallation_mfull_Priv::StateEventMatrix[][StMax] =
{   /*                         StIdle                     StFeWait                    StDmxWait                   StDecision                StPMTWait               */
    /* EvStart */             {FNADDR(FuncStartInstall),  NULL,                       NULL,                       NULL,                     NULL                    },
    /* EvStationFound */      {NULL,                      FNADDR(FuncStationFound),   NULL,                       NULL,                     NULL                    },
    /* EvStationNotFound */   {NULL,                      FNADDR(FuncStationNotFound),NULL,                       NULL,                     NULL                    },
    /* EvDmxNtf */            {FNADDR(FuncBackground),    NULL,                       FNADDR(FuncDmxData),        NULL,                     NULL                    },
    /* EvMakeDecision */      {NULL,                      NULL,                       NULL,                       FNADDR(FuncMakeDecision), NULL                    },
    /* EvStop */              {NULL,                      FNADDR(FuncStop),           FNADDR(FuncStop),           FNADDR(FuncStop),         FNADDR(FuncStop)        },         
    /* EvSigStrMeasured */    {NULL,                      NULL,                       FNADDR(FuncSigStrMeasured), NULL,                     NULL                    },
    /* EvPMTCollected */      {NULL,                      NULL,                       NULL,                       NULL,                     FNADDR(FuncPMTCollected)}
};


/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/
void CHsvDvbCInstallation_mfull_Priv::PumpHandler(int event, Nat32 param )
{
    if(StateEventMatrix[event][mDvbcFullStatus.State] != NULL)
    {
	    FPCALL(StateEventMatrix[event][mDvbcFullStatus.State])(param);
    }
    else
    {
        TraceDebug(m,"Ignored event = %d, state = %d",event,mDvbcFullStatus.State);
    }
}

void CHsvDvbCInstallation_mfull_Priv::FuncStartInstall(int param)
{
    Nat32 errorcode = TM_OK;
    Nat32 srtmode = 0;
    TraceDebug(m,"%s",__FUNCTION__);
	int		NoOfTsEntries, Count;
	HsvPgdatDigTSData   tsdata;

    mctl_Stop(HsvMain);
    ctrl_StopCollection(mDvbcFullStatus.CurrentDemux);

    TraceDebug(m,"SetSearchRates called with len = %d",mDvbcFullStatus.SearchRateLen);
    feapi_SetSearchRates(WINDOWID, mDvbcFullStatus.SearchRates, mDvbcFullStatus.SearchRateLen, &errorcode);
    ASSERT(TM_OK == errorcode);

    feapi_SetSymbolRate(srtmode, mDvbcFullStatus.SymbolRate, &errorcode);
    ASSERT(TM_OK == errorcode);
							
    TraceDebug(m,"SetFreq called with freq = %ld MHz SymRate = %d ",(Nat32) (mDvbcFullStatus.Frequency >> 4),mDvbcFullStatus.SymbolRate);
    if((CURRENT_MODE == AUTO_MODE) || (CURRENT_MODE == UPDATE_MODE))
    {
	    feapi_SetFreqStep(WINDOWID, ((idvbset_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeFreqStepSize))*16), &errorcode);
	    ASSERT(TM_OK == errorcode);
    }
    if(MANUAL_INSTALL)
    {
	    TraceDebug(m,"SetFreq called with freq = %ld MHz",(Nat32) (mDvbcFullStatus.Frequency));
	    feapi_SetFreq (WINDOWID, mDvbcFullStatus.Frequency, FALSE, &errorcode);
    }
	if (CURRENT_MODE == UPDATE_MODE)
	{
		/* Caching all the frequencies found in auto installation. This will be used upon detecting frequencies later */
		memset(&mCacheFrequency, 0x00, sizeof(mCacheFrequency));
		/* Cache the current frequencies */
		NoOfTsEntries = pgdb_GetNoRecords(PTC_TABLE);
		for (Count=0; Count<NoOfTsEntries;Count++)
		{
			if( pgdb_GetByIndex(PTC_TABLE, Count, (Address )&tsdata)) 
			{
				mCacheFrequency[Count] = tsdata.Frequency;
			}
		}
	}
    ASSERT(TM_OK == errorcode);

    /*Pavan : Based on comment from MCH. Include has to be done, else the band will be missed out */
    if(!MANUAL_INSTALL)
    {
        TraceDebug(m,"StartSearch called with freq = %ld",mDvbcFullStatus.Frequency);
        feapi_StartSearch(WINDOWID, mDvbcFullStatus.Frequency, (tmFe_SearchMode_t)(tmFe_SmCurrentIncluded | tmFe_SmDefault), mDvbcFullStatus.EndFrequency, &errorcode );
        ASSERT(TM_OK == errorcode);
    }
    mDvbcFullStatus.State = StFeWait;
    UNUSED(param);
}
void CHsvDvbCInstallation_mfull_Priv::FuncStationFound(int param)
{
    TraceDebug(m,"%s",__FUNCTION__);
    mUpdateTunerStatus();
    mDvbcFullStatus.StationFound = TRUE;

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:

            TraceDebug(m,"State set to DmxWait");
            mDvbcFullStatus.State = StDmxWait;
            sigstr_SetSigStrengthMeasured(FALSE);
            sigstr_Initialise();
            sigstr_UpdateSigStrRange();
            sigstr_StartSigStrMeasAll();
            ctrl_StartCollection(mDvbcFullStatus.CurrentDemux, ctrl_Minimal);
            break;

        case MANUAL_MODE:
            /*pavan: check why this is required */
            TraceDebug(m,"State set to DmxWait in Manual Mode");
            mDvbcFullStatus.State = StDmxWait;
            sigstr_StartSigStrMeasAll();

            pmp_PmpSend(mFullPump, EvSigStrMeasured, (Nat32)NULL);

            if( TRUE == sigstr_GetSigStrengthMeasured() )
            {
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigAssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigSssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigVssm);
                insN_OnEvent( insN_EventSignalStrengthChanged, feapi_SigQssm);
            }

            ctrl_StartCollection(mDvbcFullStatus.CurrentDemux, ctrl_Normal);

            insN_OnEvent(insN_EventTuningStarted, CURRENT_MODE); 
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}
void CHsvDvbCInstallation_mfull_Priv::FuncStationNotFound(int param)
{
    Nat32 errorcode = TM_OK;

    feapi_GetFreq(WINDOWID, &mDvbcFullStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    mDvbcFullStatus.StationFound = FALSE;
    TraceDebug(m,"%s",__FUNCTION__);

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            TraceDebug(m,"State set to StDecision");
            mDvbcFullStatus.State = StDecision;
            pmp_PmpSend(mFullPump, EvMakeDecision, (Nat32)NULL);
            break;

        case MANUAL_MODE:
            TraceDebug(m,"State set to StIdle");
            mResetInstallationState();
            /* Not Found so generate this ntf so that DVBT scan is started */
            ifullN_OnEvent(ifullN_EventScanFailed);
            insN_OnEvent(insN_EventChannelNotFound, MANUAL_MODE);
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}
void CHsvDvbCInstallation_mfull_Priv::FuncDmxData(int param)
{
    TraceDebug(m,"%s param %d",__FUNCTION__, param);

    if(param == ifctrlN_DataAvailable)
    {
        switch(CURRENT_MODE)
        {
            case AUTO_MODE:
            case UPDATE_MODE:
                mDvbcFullStatus.State = StDecision;
                idataacq_AcquireData();
                mDvbcFullStatus.NumChannelsAdded = idataacq_GetNumberOfDigitalChannelsFound();
                mDvbcFullStatus.NumChannelsRemoved = idataacq_GetNumberOfDigitalChannelsRemoved();
                ctrl_StopCollection(mDvbcFullStatus.CurrentDemux);
                insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
                pmp_PmpSend(mFullPump, EvMakeDecision, mDvbcFullStatus.Frequency);
                break;

            case MANUAL_MODE:
                {
                    HSVSPTYPE(ActualTSService, dvb, sdt) service;
                    int index = 0;
                    int loopCount = 0;
                    int numSvcs = strapi_GetSize (HsvMain, HSVSPID(ActualTSService, dvb, sdt));
                    int fiServID = sysset_GetServiceIDForChNameUpdate();

                    if(fiServID > 0)
                    {
                    	int fiIsExtractScanResult = sysset_GetExtractScanResult();

                    	if(fiIsExtractScanResult > 0)
                    	{
                    		int Onid = 0, Tsid = 0;

                    		for (loopCount = 0; loopCount < numSvcs; ++loopCount)
                    		{
                    			if(TRUE == strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sdt), loopCount, &service))
                    		    {
                    				if(service.ServiceId == fiServID)
                    				{
                    					if(strapi_GetByKey(HsvMain, HSVSPID(ActualOriginalNetworkId, dvb, sdt), 0, 0, 0, &Onid))
                    						sysset_SetUpdatedONID(Onid);
                    				    else
                    				    	sysset_SetUpdatedONID(-1);

                    				    if(strapi_GetByKey(HsvMain, HSVSPID(ActualTsId, dvb, sdt), 0, 0, 0, &Tsid))
                    				    	sysset_SetUpdatedTsID(Tsid);
                    				    else
                    				    	sysset_SetUpdatedTsID(-1);

                    				    sysset_SetUpdatedChannelName(service.ServiceName);

                    				    sysset_SetUpdatedSymbolRate(mDvbcFullStatus.SymbolRate);


                    				    break;
                    				}

                    		    }
                    		}

                    		if(loopCount < numSvcs)
                    		{
                    			insN_OnEvent(insN_EventServiceFound, 0);
                    			break;
                    		}
                    	}
                    }

                    for (loopCount = 0; loopCount < numSvcs; ++loopCount)
                    {
                        if(TRUE == strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sdt), loopCount, &service))
                        {
                            if ((TV_SERVICE == service.ServiceType) && (FALSE == service.Free_CA_Mode))
                            {
                                TraceDebug(m,"%s %d : FTA TV Svc <%d %d %d> found @ index %d", __FUNCTION__, __LINE__, 
                                                service.Original_NetworkId, service.TsId, service.ServiceId, loopCount); 
                                break;
                            }
                        }
                    }
                    // If loopCount == numSvcs, no TV service found in Actual TS list; set the first Radio service
                    // as current pgm; else first TV service will be available at index = loopCount
                    index = ((numSvcs == loopCount) ? 0 : loopCount);

                    TraceDebug(m,"%s %d : index %d", __FUNCTION__, __LINE__, index);
                    
                    if(TRUE == strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sdt), index, &service))
                    {
                        mDvbcFullStatus.State = StPMTWait;
                        //Set the filter for monitoring CurrentProgram PMT            
                        strmfltr_Set(HsvMain, HsvCurrentProgram, service.ServiceId);
						//pmp_PmpSendAfter(mFullPump, EvPMTTimeOut, (Nat32)mCurrentSessionCookie, SIGSTR_WAITTIME);
                    }
					insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
						
                }
                break;
                
            default:
                ASSERT(FALSE);
                break;
        }
    }
    else if(param == ifctrlN_DataNotAvailable)
    {
        ctrl_StopCollection(mDvbcFullStatus.CurrentDemux);

        switch(CURRENT_MODE)
        {
            case AUTO_MODE:
            case UPDATE_MODE:
                mDvbcFullStatus.State = StDecision;
                pmp_PmpSend(mFullPump, EvMakeDecision, mDvbcFullStatus.Frequency);
                break;

            case MANUAL_MODE:
                mResetInstallationState();
                ifullN_OnEvent(ifullN_EventScanFailed);
                insN_OnEvent(insN_EventChannelNotFound, MANUAL_MODE);
                break;
            default:
                ASSERT(FALSE);
                break;
        }
    }
}
void CHsvDvbCInstallation_mfull_Priv::FuncMakeDecision(int param)
{
    Nat32 errorcode = TM_OK;
	int Stepsize;
	Nat32 retval;


    TraceDebug(m,"%s",__FUNCTION__);
    /* This is called only during auto and update install only */
    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            feapi_GetFreq(WINDOWID, &mDvbcFullStatus.Frequency, &errorcode);
            ASSERT(TM_OK == errorcode);

            TraceDebug(m,"GetFreq returns %ld",(Nat32) mDvbcFullStatus.Frequency);
            TraceDebug(m,"EndFreq = %ld",(Nat32) mDvbcFullStatus.EndFrequency);

            Stepsize = rins_GetAttribute(rins_InstallationModeAutomatic,rins_AttributeFreqStepSize);
            if( ((Stepsize == rins_DVBCStepSize1)&&((mDvbcFullStatus.Frequency>>4) < (mDvbcFullStatus.EndFrequency>>4))) ||
				((Stepsize == rins_DVBCStepSize8)&&((mDvbcFullStatus.Frequency>>4) < ((mDvbcFullStatus.EndFrequency>>4) - 7))))
            {
                TraceDebug(m,"MakeDecision: Freq < End");

                /* Frequency within the range. So start search again */

                mDvbcFullStatus.State = StFeWait;
                TraceDebug(m,"MakeDecision: StartSearch called with freq = %ldMHz, End Freq = %ldMHz",(Nat32) (mDvbcFullStatus.Frequency >> 4),(Nat32) (mDvbcFullStatus.EndFrequency >> 4));
                feapi_StartSearch(WINDOWID, (mDvbcFullStatus.Frequency + (1 * 16)), tmFe_SmDefault, mDvbcFullStatus.EndFrequency, &errorcode );
                ASSERT(TM_OK == errorcode);
            }
            else
            {
                TraceDebug(m,"MakeDecision: Freq >= End");
                TraceDebug(m,"MakeDecision: Install Complete");
				feapi_StopSearch(WINDOWID,&retval);
                mResetCableDSLen();
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


void CHsvDvbCInstallation_mfull_Priv::FuncPMTCollected (int param)
{
    TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);
    
    //Start the AV playback for CurrentProgram            
    mPlayService(param);
    /* ntf to apps, to show "store" button */
    insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
    UNUSED(param);

}
  
void CHsvDvbCInstallation_mfull_Priv::FuncStop(int param)
{
    tmErrorCode_t errorcode;

    TraceDebug(m,"%s",__FUNCTION__);

    switch(mDvbcFullStatus.State)
    {
        case StFeWait:
            feapi_StopSearch(WINDOWID, &errorcode);
            ASSERT(TM_OK  ==  errorcode);
            break;
        case StDmxWait:
            ctrl_StopCollection(mDvbcFullStatus.CurrentDemux);
            sigstr_StopSigStrMeasAll();
            break;
        case StDecision:
            /* pavan: Not possible actually. State change happens in Makedecision anyways */
            TraceDebug(m,"Nothing can be done ??");
            break;
        case StPMTWait:  
            if (mDvbcFullStatus.PlayStarted)
            {
                mctl_Stop(HsvMain);
                mDvbcFullStatus.PlayStarted = FALSE;
            }
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    mResetInstallationState();
    ifullN_OnEvent(ifullN_EventScanStopped);
    UNUSED(param);
}

void CHsvDvbCInstallation_mfull_Priv::FuncBackground(int param)
{
    UNUSED(param);
    mUpdateTunerStatus();

}


void CHsvDvbCInstallation_mfull_Priv::FuncSigStrMeasured(int param)
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
        pmp_PmpSendAfter(mFullPump, EvSigStrMeasured, (Nat32)NULL, SIGSTR_WAITTIME);
    }
}

void CHsvDvbCInstallation_mfull_Priv::mUpdateTunerStatus(void)
{
    int param1;
    tmErrorCode_t errorcode = TM_OK;

    TraceDebug(m,"%s",__FUNCTION__);

    feapi_GetFreq(WINDOWID, &mDvbcFullStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    feapi_GetActualConstellation(WINDOWID, feapi_ChanDecDvbC, (tmFe_Constellation_t*)(&param1), &errorcode);
    ASSERT(TM_OK  ==  errorcode);
    mDvbcFullStatus.ModulationType = param1; // (Nat8)FindHsvValue(param1, mConstellation, sizeof(mConstellation));

    feapi_GetActualCodeRate(WINDOWID, &mDvbcFullStatus.SymbolRate, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

}

void CHsvDvbCInstallation_mfull_Priv::mPlayService(int serviceid)
{
    HsvPMTAudioInfo audioInfo;
    HsvPMTBasicPidInfo basicPIDInfo;    
    HsvDestination dest = HsvMain;
	Nat8		IsAvPidSet = FALSE;

    if(mDvbcFullStatus.PlayStarted == FALSE)
    { 
		audioInfo.Pid = 8191;
		basicPIDInfo.VideoPid = 8191;
		basicPIDInfo.PcrPid = 8191;

		TraceDebug(m,"Play Started on Service = %d\r", serviceid);
		mctl_Flush(dest);
		
		/* Earlier code was having ||. If first condition meets, Shortcircuit happens and second condition is not evaluated. 
			Hence Video and PCR PIDs are not set */
        if (TRUE == strapi_GetByIndex(dest, HSVSPID(CurrentAudioInfo, mpeg, pmt), 0, &audioInfo))
		{
			mctl_SetMedia(dest, mctl_Audio, audioInfo.AudioType, audioInfo.Pid);  
			IsAvPidSet = TRUE;
		}
        
		if (TRUE == strapi_GetByKey(dest, HSVSPID(BasicPidInfo, mpeg, pmt), serviceid, 0, 0, &basicPIDInfo))
        {  
            mctl_SetMedia(dest, mctl_Video, basicPIDInfo.VideoStreamType, basicPIDInfo.VideoPid);
            mctl_SetMedia(dest, mctl_Pcr, mctl_InvalidSelector, basicPIDInfo.PcrPid);
            IsAvPidSet = TRUE;
        }
		
		if (IsAvPidSet == TRUE)
		{
			mctl_Play(dest);            
			mDvbcFullStatus.PlayStarted = TRUE;
		}
        else
        {
            TraceDebug(m,"%s(): Error... Failed to get AV pids for Service = 0x%x", __FUNCTION__, serviceid);
        }
    }
}


int CHsvDvbCInstallation_mfull_Priv::mGetSymbolRates( tmFe_SearchSymbolRate_t *SearchRates, int *SearchRateLen )
{
    int country = sysset_GetSystemCountry();
    
    if( ((country == cids_CountryNorway) || (country == cids_CountrySweden) || (country == cids_CountryDenmark))
		&& (rins_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeScanMode) == rins_FullScan) )
    {
        mGetSymbolRatesNordic(country, SearchRates, SearchRateLen );
    }
    else
    {
        mGetSymbolRatesOthers(SearchRates, SearchRateLen );
    }
    return 0;
}

int CHsvDvbCInstallation_mfull_Priv::mGetSymbolRatesNordic( int country, tmFe_SearchSymbolRate_t *SearchRates, int *SearchRateLen )
{
    int i,j;
    int aslen = 0;
    int selconst = 0;
    int uvals[MAX_SYMBOL_RATES], ulen;

    idvbset_GetUserSymbolRates(CURRENT_MODE, uvals, &ulen);
        
    for(i=0;i<MAX_MOD_TYP;i++)
    {
        for(j=0;j<(MAX_SYMRATES_PER_SET+ulen);j++)
        {
            if(j<MAX_SYMRATES_PER_SET)
            {
                switch(country) 
                {
                    case cids_CountrySweden:
                        SearchRates[aslen].rate = SearchRates_Sweden[i][j];
                        selconst = mConstellation[ModulationVals_Sweden[i]];
                    break;  
                    case cids_CountryNorway:    
                        SearchRates[aslen].rate = SearchRates_Norway[i][j];
                        selconst = mConstellation[ModulationVals_Norway[i]];
                    break;  
                    case cids_CountryDenmark:   
                        SearchRates[aslen].rate = SearchRates_Denmark[i][j];
                        selconst = mConstellation[ModulationVals_Denmark[i]];
                    break;  
                }
            }
            else
            {
                SearchRates[aslen].rate = uvals[j-MAX_SYMRATES_PER_SET];
                //keep the previous selconst user values are updated after the predefined symbol rates 
            }
            SearchRates[aslen].constellation =(tmFe_Constellation_t) selconst; 
            
            if(SearchRates[aslen].rate != INVALID_SYMBOLRATE )
            {
                TraceDebug(m,"Initialise: SymRate[%d] = %ld", aslen,SearchRates[aslen].rate);
                TraceDebug(m,"Initialise: Modulation[%d] = %x",aslen,SearchRates[aslen].constellation);
                aslen++;
            }
        }
    }
    if(aslen > MAX_SEARCH_RATES)
    {
        *SearchRateLen = MAX_SEARCH_RATES;
    }
    else
    {
        *SearchRateLen = aslen;
    }
    return 0;
}

int CHsvDvbCInstallation_mfull_Priv::mGetSymbolRatesOthers(tmFe_SearchSymbolRate_t *SearchRates, int *SearchRateLen)
{
    int i,j;
    int aslen = 0;
    int slen = 0, mlen = 0;
    slen = idvbset_GetAttributeLength(CURRENT_MODE, rins_AttributeSymbolRate);
    mlen = MAX_MODULATION_VALS;     

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
                    SearchRates[(mlen*aslen) + j].rate = temprate;
                    SearchRates[(mlen*aslen) + j].constellation =(tmFe_Constellation_t) mConstellation[ModulationVals[j]];
                    TraceDebug(m,"Initialise: SymRate[%d] = %d", ((mlen*aslen) + j),temprate);
                    TraceDebug(m,"Initialise: Modulation[%d] = %x", ((mlen*aslen) + j),mConstellation[ModulationVals[j]]);
                }
                aslen++;
            }
        }
    }
    if((aslen * mlen) > MAX_SEARCH_RATES)
    {
        *SearchRateLen = MAX_SEARCH_RATES;
    }
    else
    {
        *SearchRateLen = (aslen * mlen);
    }
    return 0;
}


/***************************
  provides IHsvPower
 ****************************/
void CHsvDvbCInstallation_mfull_Priv::ifullpow_Init()
{
    mFullPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE, "hsvdvbcins_mfull_pmp");
}

void CHsvDvbCInstallation_mfull_Priv::ifullpow_TurnOn()
{
}

void CHsvDvbCInstallation_mfull_Priv::ifullpow_TurnOff()
{
}

/************************************
  provides IHsvDigitalScan ifull
 *************************************/
void CHsvDvbCInstallation_mfull_Priv::ifull_Initialise(void)
{
    Nat32 decoder, retval, err = TM_OK;
    TraceDebug(m,"%s",__FUNCTION__);

    /* Select Decoder */

    mDvbcFullStatus.State = StIdle;
    mDvbcFullStatus.ModulationType = HsvAutoConstellation;
    mDvbcFullStatus.CodeRateHigh = HsvCodeRateAuto;  
    mDvbcFullStatus.CodeRateLow = HsvCodeRateAuto;
    mDvbcFullStatus.GuardInterval = HsvGuardIntervalAuto;
    mDvbcFullStatus.TxMode = HsvTxModeAuto;
    mDvbcFullStatus.IqMode = HsvIqModeNormal;
    mDvbcFullStatus.ChannelBandwidth = HsvChanBandwidth8MHz;
    mDvbcFullStatus.ChannelInformation = 0;
    mDvbcFullStatus.TimeError = 0;
    mDvbcFullStatus.FrequencyError = 0;
    mDvbcFullStatus.FrequencyOffset = HsvOffsetNone;
    mDvbcFullStatus.CurrentDemux = HsvDmxMain;
    mDvbcFullStatus.SDTAcquired = FALSE;
    mDvbcFullStatus.PlayStarted = FALSE;
    mDvbcFullStatus.StationFound = FALSE;
    mDvbcFullStatus.NumChannelsAdded = 0;
    mDvbcFullStatus.NumChannelsRemoved = 0;
    mDvbcFullStatus.FirstPresetNumber = INVALID_PRESET;

    retval = feapi_GetFreqRange(WINDOWID, &(mDvbcFullStatus.Frequency), &(mDvbcFullStatus.EndFrequency), &err);    
	mDvbcFullStatus.Frequency = 50 * 16;
	mDvbcFullStatus.EndFrequency = 860 * 16;
	TraceNotice (m, "DvbcFull: MinFreq %dMhz MaxFreq %dMhz ", mDvbcFullStatus.Frequency/16, mDvbcFullStatus.EndFrequency/16); 
    ASSERT(retval == plferrids_Ok);
    ASSERT(err == TM_OK);
    ASSERT(mDvbcFullStatus.Frequency <= START_FREQUENCY);
    ASSERT(mDvbcFullStatus.EndFrequency >= END_FREQUENCY);

    if(mDvbcFullStatus.Frequency < START_FREQUENCY)
    {
        mDvbcFullStatus.Frequency = START_FREQUENCY;
    }

    mGetSymbolRates ( mDvbcFullStatus.SearchRates, &mDvbcFullStatus.SearchRateLen );

    TraceDebug(m,"Initialise:SearchRateLen = %d", mDvbcFullStatus.SearchRateLen);

    idataacq_Initialise();
}
FResult CHsvDvbCInstallation_mfull_Priv::ifull_StartDigitalScan(void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s",__FUNCTION__);

    if(mDvbcFullStatus.State == StIdle)
    {
        pmp_PmpSend(mFullPump, EvStart, (Nat32)NULL);
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
}
FResult CHsvDvbCInstallation_mfull_Priv::ifull_StartDigitalTuning(int freq)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s",__FUNCTION__);

    if(mDvbcFullStatus.State == StIdle)
    {
        mDvbcFullStatus.Frequency = freq;
        idvbset_SetAttribute(MANUAL_MODE, rins_AttributeNetworkFreq, freq);
        pmp_PmpSend(mFullPump, EvStart, (Nat32)NULL);
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
}
FResult CHsvDvbCInstallation_mfull_Priv::ifull_StopDigitalScan (void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s",__FUNCTION__);

    if(mDvbcFullStatus.State == StIdle)
    {
        retval = hsverr_InstallationNotInProgress;
    }
    else
    {
        pmp_PmpSend(mFullPump, EvStop, (Nat32)NULL);
    }
    return retval;
}
void CHsvDvbCInstallation_mfull_Priv::ifull_GetPTCInfo(HsvInstallationPTC *ptc)
{
    Nat32 errorcode = TM_OK;
    int temp;
    TraceDebug(m,"%s",__FUNCTION__);

    if(mDvbcFullStatus.State == StIdle)
    {
        ptc->DecoderType = feapi_ChanDecDvbC;

        // DvbC full scan sometimes will result in accuracy freq instead of standard freq
		// For example: standard freq 570000
		// After full scan, for some stream, tuner will return 569986
		// After integer calculation (((*freq) * 16)/1000) and  (ptc->Frequency * 1000) /16 
		// it will store 569937 to database.
		// Later when retrieve the freq, this will execute again: (((*freq) * 16)/1000) and  (ptc->Frequency * 1000) /16
		// it will change the number 569937 to 569875,and this will cause inconsistant with database
		// which will make pgdb_GetByKey failed
		// feapi_GetFreq(WINDOWID, &(ptc->Frequency), &errorcode);
        feapi_GetCarrierFreq(WINDOWID, 0, tmFe_TableEuropeC, &(ptc->Frequency), &errorcode);
        ASSERT(TM_OK  ==  errorcode);

        feapi_GetActualCodeRate(WINDOWID, &(ptc->SymbolRate), &errorcode);
        ASSERT(TM_OK  ==  errorcode);

        feapi_GetActualConstellation(WINDOWID, feapi_ChanDecDvbC, (tmFe_Constellation_t*)(&temp), &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        mDvbcFullStatus.ModulationType = temp; //(Nat8)FindHsvValue(temp, mConstellation, sizeof(mConstellation));

        ptc->ModulationType     =   mDvbcFullStatus.ModulationType;
        ptc->HierarchyMode      =   HsvHierarchyNone;    
        ptc->StreamPriority     =   HsvStreamPriorityHigh;
    }
    else
    {
        ptc->DecoderType        =   feapi_ChanDecDvbC;
        ptc->Frequency          =   mDvbcFullStatus.Frequency;
        ptc->SymbolRate         =   mDvbcFullStatus.SymbolRate;
        ptc->ModulationType     =   mDvbcFullStatus.ModulationType;   
        ptc->CodeRateHigh       =   mDvbcFullStatus.CodeRateHigh;         
        ptc->CodeRateLow        =   mDvbcFullStatus.CodeRateLow;         
        ptc->HierarchyMode      =   HsvHierarchyNone;    
        ptc->GuardInterval      =   mDvbcFullStatus.GuardInterval;    
        ptc->TxMode             =   mDvbcFullStatus.TxMode;           
        ptc->IqMode             =   mDvbcFullStatus.IqMode;           
        ptc->ChannelBandwidth   =   mDvbcFullStatus.ChannelBandwidth; 
        ptc->StreamPriority     =   HsvStreamPriorityHigh;
        ptc->ChannelInformation =   mDvbcFullStatus.ChannelInformation;   
        ptc->TimeError          =   mDvbcFullStatus.TimeError;        
        ptc->FrequencyError     =   mDvbcFullStatus.FrequencyError;   
        ptc->FrequencyOffset    =   mDvbcFullStatus.FrequencyOffset;  
        ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
        ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
        ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);
        ptc->CDSDFrequency      =   0;
		ptc->Frequency = (ptc->Frequency * 1000) /16;
    }

	if (CURRENT_MODE == UPDATE_MODE)
	{
		for (temp=0; temp<MAX_TS_FREQUENCIES;temp++)
		{
			if (mCacheFrequency[temp] != 0)
			{
				if (DIFFERENCE_IN_FREQUENCY((ptc->Frequency), (mCacheFrequency[temp])) <= ALLOWABLE_DRIFT_IN_FREQUENCY)
				{
					ptc->Frequency = mCacheFrequency[temp];
					TraceNotice (m, "Drift seen in Update of %d . Pointing to older Freq %d ", ptc->Frequency, mCacheFrequency[temp]);
				}
			}
			else
			{
				break;
			}
		}
	}
}

FResult CHsvDvbCInstallation_mfull_Priv::ifull_StoreWeakSignalInstallationChannel()       
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s",__FUNCTION__);

    if(MANUAL_INSTALL)
    {
        idataacq_AcquireData();
        idataacq_SyncTemporaryTableRecords();

    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
}

int CHsvDvbCInstallation_mfull_Priv::ifull_GetNumberOfDigitalChannelsFound()
{
    TraceDebug(m,"%s: retval = %d",__FUNCTION__,mDvbcFullStatus.NumChannelsAdded);
    return mDvbcFullStatus.NumChannelsAdded;
}
int CHsvDvbCInstallation_mfull_Priv::ifull_GetNumberOfDigitalChannelsRemoved()
{
    TraceDebug(m,"%s: retval = %d",__FUNCTION__,mDvbcFullStatus.NumChannelsRemoved);
    return mDvbcFullStatus.NumChannelsRemoved;
}

int CHsvDvbCInstallation_mfull_Priv::ifull_GetSDTType()
{
    return eurdiv_SDTActual;
}

/************************************
  provides IHsvFrontEndApiNotify  
 *************************************/

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnStationFound()
{
    TraceDebug(m,"%s  State:%d",__FUNCTION__,mDvbcFullStatus.State);
    if(mDvbcFullStatus.State == StFeWait)
    {
    	TraceDebug(m,"%s",__FUNCTION__);
        pmp_PmpSend(mFullPump, EvStationFound, (Nat32)NULL);
    }
}
void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnStationNotFound()
{
    TraceDebug(m,"%s",__FUNCTION__);
    if(mDvbcFullStatus.State == StFeWait)
    {
        pmp_PmpSend(mFullPump, EvStationNotFound, (Nat32)NULL);
    }
}
void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnMeasReady( int ssm, Nat32 strength )
{
    UNUSED(ssm);
    UNUSED(strength);
}
void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnMeasAborted( int ssm )
{
    UNUSED(ssm);
}

/***************************************
  provides IHsvStreamNotify ifstrapiN
 ****************************************/

void CHsvDvbCInstallation_mfull_Priv::ifstrapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED (dest);
    UNUSED (spid);
    UNUSED (key1);
    UNUSED (key2);
    UNUSED (key3);
}
void CHsvDvbCInstallation_mfull_Priv::ifstrapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
    UNUSED(eventid);
    /* pavan: how do we handle dynamic updates */
}
void CHsvDvbCInstallation_mfull_Priv::ifstrapiN_OnRemoved  ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}
void CHsvDvbCInstallation_mfull_Priv::ifstrapiN_OnCompleted  ( HsvDestination dest, int spid)
{
    switch(spid)
    {
        case HSVSPID(CurrentProgram, mpeg, pmt):
            {
                int currentPgm = -1;
                if (TRUE == strapi_GetByKey (dest, HSVSPID(CurrentProgram, mpeg, pmt), 0, 0, 0, (void *)(&currentPgm)))
                {
                    pmp_PmpSend(mFullPump, EvPMTCollected, currentPgm);
                }
            }
            break;

        default:
            break;
    }
}

/***************************************
  provides IHsvSdmControlNotify ifctrlN
 ****************************************/
void CHsvDvbCInstallation_mfull_Priv::ifctrlN_OnEvent( HsvDemux dmx, int eventid, int value)
{
    TraceDebug(m,"ctrlN_OnEvent:eventid = %d",eventid);

    UNUSED(value);
    if(mDvbcFullStatus.State == StDmxWait)
    {
        switch(eventid)
        {
            case ifctrlN_DataAvailable:
                TraceDebug(m,"ifctrlN: DataAvailable");
                pmp_PmpSend(mFullPump, EvDmxNtf, ifctrlN_DataAvailable);
                break;
            case ifctrlN_SiDataAvailable:
                TraceDebug(m,"ifctrlN: SiDataAvailable");
                /* 2nd check diversity means we will not wait for NIT for the Multiple NIT Other countries */
                if(MANUAL_INSTALL && (eurdiv_ParseLCN(rins_GetMedium(), rins_GetInstallationMode()) == FALSE) )
                {
                    pmp_PmpSend(mFullPump, EvDmxNtf, ifctrlN_DataAvailable);
                }       
                break;
            case ifctrlN_DataNotAvailable:
                TraceDebug(m,"ifctrlN: DataNotAvailable");
                pmp_PmpSend(mFullPump, EvDmxNtf, ifctrlN_DataNotAvailable);
                break;
            case ifctrlN_StartedCollection:
                TraceDebug(m,"ifctrlN: StartedCollection");
                break;
            case ifctrlN_StoppedCollection:
                TraceDebug(m,"ifctrlN: StoppedCollection");
                break;
            default:
                ASSERT(FALSE);
                break;
        }   
    }
    else if((mDvbcFullStatus.State == StIdle) && mDvbcFullStatus.Active)
    {
        switch(eventid)
        {
            case ifctrlN_DataAvailable:
                pmp_PmpSend(mFullPump, EvDmxNtf, ifctrlN_DataAvailable);
                break;
            case ifctrlN_DataNotAvailable:
            case ifctrlN_StartedCollection:
            case ifctrlN_StoppedCollection:
            default:
                break;
        }
    }
    UNUSED(dmx);
}

void CHsvDvbCInstallation_mfull_Priv::mResetInstallationState(void)
{
    Nat32 errorcode = TM_OK;

    mDvbcFullStatus.State = StIdle;
    feapi_SetSearchRates(WINDOWID, NULL, 0, &errorcode);
    ASSERT(TM_OK == errorcode);
}

void CHsvDvbCInstallation_mfull_Priv::ifena_Enable(void)
{
    mDvbcFullStatus.Active = TRUE;
}

void CHsvDvbCInstallation_mfull_Priv::ifena_Disable(void)
{
    mDvbcFullStatus.Active = FALSE;
}
void CHsvDvbCInstallation_mfull_Priv::mResetCableDSLen()
{
    /* Read all CableDS from flash and update it in RAM */
    FILE* fp;
    int readrec = 0, ret = 0;
/*
    ffsdir_GetDirPath( mDirName, ffsdir_Boot, ffsdir_Broadcast );
    if(str_strlen(mDirName))
    {
		str_strcat(mDirName, "/channellib/");    
    }
    else
    {
        ASSERT(!"Boot parition mount has failed");
    }
  
*/
	str_strcpy (mDirName, "/user_setting/rw/tvserver/databases/channellib/");
	mGetPathNameFull(mDirName, CABLE_DEL_FILEPATH, mFileName);
    TraceDebug(m,"Fopen of %s", mFileName);

    fp = fopen(mFileName, "wb");

    if(fp)
    {
        readrec = fread((Address)(&mFlashCableDS), sizeof(mFlashCableDS), 1, fp);
        if(readrec)
        {
            TraceDebug(m,"Read Cable Del Sys from Flash");
        }
        else
        {
            mFlashCableDS.TargetNITValue = INVALID_NETWORKID;
            TraceDebug(m,"Read Cable Del Sys from Flash Fail");
        }
        mFlashCableDS.NumOfTs = 0;
        ret = fwrite((Address)(&mFlashCableDS), sizeof(mFlashCableDS), 1, fp);
        if(ret!=1)
        {
            TraceDebug(m,"Writing CableDes Failed");
            ASSERT(!"Unable to write");
        }
        fclose(fp);
    }
    else
    {
        mFlashCableDS.TargetNITValue = INVALID_NETWORKID;
        TraceDebug(m,"Unable to open %s",mFileName);
        ASSERT(!"Unable to open CABLE_DEL_FILEPATH");
    }
}

void CHsvDvbCInstallation_mfull_Priv::mGetPathNameFull(char* dirName, char* FileName , char* PathName)
{
    if(str_strlen(dirName))
    {
        if(str_strlen(FileName))
        {
            str_strcpy(PathName, dirName);
            str_strcat(PathName, FileName);
        }
    }
    else
    {   
        str_strcpy(PathName,FileName);
    }
}

void CHsvDvbCInstallation_mfull_Priv::ifull_SyncComplete(void)
{
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    if(MANUAL_INSTALL)  
    {
        mDvbcFullStatus.NumChannelsAdded = idataacq_GetNumberOfDigitalChannelsFound();
        mDvbcFullStatus.NumChannelsRemoved = idataacq_GetNumberOfDigitalChannelsRemoved();
        pgdb_CommitTable(pgdb_GetCurrentTable());

        insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);
        insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE); 
        mResetInstallationState();
    }
    else
    {
        mResetInstallationState();
        ifullN_OnEvent(ifullN_EventScanCompleted);
    }
}

int CHsvDvbCInstallation_mfull_Priv::FindHsvValue(int plfval, int* arr, int len)
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

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnSearchInProgress( tmFe_SearchState_t state )
{
	return;
}




FResult CHsvDvbCInstallation_mfull_Priv::ifull_StartInstallation(int source, int ptc, int mode) 
{
	return 0;
}

FResult CHsvDvbCInstallation_mfull_Priv::ifull_StopInstallation(void ) 
{
	return 0;
}


int CHsvDvbCInstallation_mfull_Priv::ifull_GetNoOfPass(void) 
{
	return 0;
}

int CHsvDvbCInstallation_mfull_Priv::ifull_GetCurrentPass ( void ) 
{
	return 0;
}


int CHsvDvbCInstallation_mfull_Priv::ifull_GetTargetNitType(Nat16* NetworkId) 
{
	return NULL;
}

int CHsvDvbCInstallation_mfull_Priv::ifull_GetCurrentState() 
{
	return 0;
}


Bool CHsvDvbCInstallation_mfull_Priv::ifull_GetAltTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

void CHsvDvbCInstallation_mfull_Priv::ifull_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


Bool CHsvDvbCInstallation_mfull_Priv::ifull_GetCurTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

HsvStreamPriority CHsvDvbCInstallation_mfull_Priv::ifull_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}

void CHsvDvbCInstallation_mfull_Priv::ifull_SetStreamPriority (HsvStreamPriority prio) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifull_ClearCache(void) 
{
	return;
}

int CHsvDvbCInstallation_mfull_Priv::ifull_GetPLPIds(int *PLPIds) 
{
	return NULL;
}

HsvHierarchyMode CHsvDvbCInstallation_mfull_Priv::ifull_GetHierarchyMode(void) 
{
	return (HsvHierarchyMode)0;
}

void CHsvDvbCInstallation_mfull_Priv::ifull_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid) 
{
	return;
}

int CHsvDvbCInstallation_mfull_Priv::ifull_ZiggoGetSDTType(Nat16 Frequency) 
{
	return 0;
}

void CHsvDvbCInstallation_mfull_Priv::ifull_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return ;
}

Bool CHsvDvbCInstallation_mfull_Priv::ifull_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}

void CHsvDvbCInstallation_mfull_Priv::ifull_ClearPersistent() 
{
	return;
}

/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}


void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvDvbCInstallation_mfull_Priv::ifullfeN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}


