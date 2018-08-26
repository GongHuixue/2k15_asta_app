#include "_hsvdvbtins_mDtr.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbtins_mDtr")

#ifndef __cplusplus

#include "../hsveuins/DVBTSpectrum.h"

//#include "../type/InstallationConstants.h"

#else

#include "DVBTSpectrum.h"

//#include "InstallationConstants.h"

#endif

#include "plftoMWconstantsWrapper.h"




#ifndef __cplusplus

#else

#endif



Bool CHsvDvbTInstallation_mDtr_Priv::s__mUserSelectedMux;

Bool CHsvDvbTInstallation_mDtr_Priv::s__mPlayStarted = FALSE;

int CHsvDvbTInstallation_mDtr_Priv::s__mScanPLPState,CHsvDvbTInstallation_mDtr_Priv::s__mDetectedPlpIds[MAX_PLP_IDS],CHsvDvbTInstallation_mDtr_Priv::s__mNumPLPIds;

Nat16 CHsvDvbTInstallation_mDtr_Priv::s__mCurrentDecoder;

HsvStreamPriority CHsvDvbTInstallation_mDtr_Priv::s__mHeirarchyValue = HsvStreamPriorityHigh;


/* static functions */



















const FunctionNat32 CHsvDvbTInstallation_mDtr_Priv::EventActionMatrix[][ConstEvMax] =
{
/*                                   ConstStIdle                        ConstStScanProgress,            ConstStTunerWait,                   ConstStDemuxWait,                       ConstStPMTWait                      */
/* ConstEvStart */                  {FNADDR(FuncStartDtrInstallation),  NULL,                           NULL,                               NULL,                                   NULL                                },
/* ConstEvStop */                   {NULL,                              FNADDR(FuncStopDtrInstallation),FNADDR(FuncStopDtrInstallation),    FNADDR(FuncStopDtrInstallation),        FNADDR(FuncStopDtrInstallation)     },
/* ConstEvSdmStopped */             {NULL,                              FNADDR(FuncDtrSdmStopped),      NULL,                               FNADDR(FuncDtrSdmStopped),              FNADDR(FuncDtrSdmStopped)           },
/* ConstEvDataAvailable */          {NULL,                              NULL,                           FNADDR(FuncDtrSdmStopped),          FNADDR(FuncDtrDataAvailable),           NULL                                },
/* ConstEvStationFound */           {NULL,                              NULL,                           FNADDR(FuncDtrStationFound),        NULL,                                   NULL                                },
/* ConstEvStationNotFound */        {NULL,                              NULL,                           FNADDR(FuncDtrStationNotFound),     NULL,                                   NULL                                },
/* DummyEvent          */           {NULL,                              NULL,                           NULL,                               NULL,                                   NULL                                },
/* ConstEvMeasureSignalStr */       {NULL,                              NULL,                           FNADDR(FuncSignalStrength),         FNADDR(FuncSignalStrength),             FNADDR(FuncSignalStrength)          },
/* ConstEvHierarchyModeDetected */  {NULL,                              NULL,                           FNADDR(FuncOnHierarchyModeDetected),FNADDR(FuncOnHierarchyModeDetected),    FNADDR(FuncOnHierarchyModeDetected) },
/* ConstEvOnMeasReady */            {NULL,                              NULL,						    FNADDR(FuncOnMeasReady),		    FNADDR(FuncOnMeasReady),		        FNADDR(FuncOnMeasReady)		        },
/* ConstEvPMTCollected */           {NULL,                              NULL,						    NULL,		                        NULL,		                            FNADDR(FuncDtrPMTCollected)	        }
};

void CHsvDvbTInstallation_mDtr_Priv::PumpHandler(int event, Nat32 param)
{

    if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
    {

        if(EventActionMatrix[event][mInstStatus.State] != NULL)
        {
            TraceDebug(m,"%s %d event %d State %d", __FUNCTION__, __LINE__, event, mInstStatus.State);
            FPCALL(EventActionMatrix[event][mInstStatus.State])(param);
        }
    }
}

void CHsvDvbTInstallation_mDtr_Priv::FuncStartDtrInstallation(Nat32 freq)
{
    mInitialise(freq);
    mctl_Stop(HsvMain);

    SET_INS_STATE(ConstStScanProgress);
    mStopSdm(HsvDmxMain);
}

void CHsvDvbTInstallation_mDtr_Priv::FuncStopDtrInstallation(Nat32  param)
{
    TraceDebug(m,"%s() : %d \n", __FUNCTION__, __LINE__);
    SET_INS_STATE(ConstStIdle);
    sigstr_StopSigStrMeasAll();
    mInitialise(START_FREQUENCY);
    if (mPlayStarted)
    {
        mctl_Stop(HsvMain);
        mPlayStarted = TRUE;
    }

	mUserSelectedMux = FALSE;
    insN_OnEvent(insN_EventInstallationStopped, MANUAL_MODE);
    UNUSED(param);  
}

void CHsvDvbTInstallation_mDtr_Priv::FuncDtrSdmStopped(Nat32  param)
{
    mSetChannelDecoderAttributes();
    mSetTunerAttributes();
    UNUSED(param);
}

void CHsvDvbTInstallation_mDtr_Priv::FuncDtrStationFound(Nat32  param)
{
    tmErrorCode_t errorcode;
	Bool HierarchialMuxPresent = FALSE;

    feapi_GetFreq(WINDOWID,&mInstStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode );

    if(mIsDvbt2CarrierDetected() == TRUE)
    {
        TraceDebug(m,"   : %d %s  ", __LINE__, __FUNCTION__);

        chdecdvbt2_GetDetectedPlpIds(WINDOWID, &mNumPLPIds, mDetectedPlpIds);

        TraceNotice(m,"%s %d NumPLPIds %d mUserSelectedMux %d", __FUNCTION__, __LINE__, mNumPLPIds, mUserSelectedMux);
        if(mNumPLPIds > 1)
        {
            mInstStatus.HierarchyMode = TRUE;
            /* set PLP state */
            mScanPLPState = ConstStScanProgress;
			
			if(mNumPLPIds > MAX_PLP_IDS)
			{
				mNumPLPIds = MAX_PLP_IDS;
			}


			if(mUserSelectedMux == FALSE)
            {
				int fiFocusedPlpId = sysset_GetFocusedPlpId();

				if(fiFocusedPlpId != -1)
				{
					mUserSelectedMux = TRUE;
					mHeirarchyValue = (HsvStreamPriority)fiFocusedPlpId;
				}
				else
				{
					if(sysset_GetServiceIDForChNameUpdate())
					{
						mUserSelectedMux = TRUE;
						mHeirarchyValue = (HsvStreamPriority)mDetectedPlpIds[0];
						miT2PLPIDX = 0;
						insN_OnEvent(insN_EventT2SwitchPLPID, mDetectedPlpIds[miT2PLPIDX]);
					}
					else
						insN_OnEvent(insN_EventPLPsDetected, MANUAL_MODE);
				}
            }


        }
        else if(mNumPLPIds == 1 && sysset_GetServiceIDForChNameUpdate())
        {
        	insN_OnEvent(insN_EventT2SwitchPLPID, mDetectedPlpIds[0]);
        }
    }
	else
	{
		feapi_GetHierarchyMuxPresence(WINDOWID, &HierarchialMuxPresent,&errorcode);
		TraceNotice(m,"%s %d HierarchialMuxPresent: %d",__FUNCTION__, __LINE__,HierarchialMuxPresent);
		if(HierarchialMuxPresent == TRUE)
		{
			insN_OnEvent(insN_EventHeirarchyModeDetected, MANUAL_MODE); 
		}
	}
    TraceDebug(m,"   : %d %s  ", __LINE__, __FUNCTION__);
    if(sigstr_StartSigStrMeasAll() == TRUE)
    {
        pmp_PmpSend(mPump, ConstEvMeasureSignalStr, (Nat32)NULL);
    }
    if( (mUserSelectedMux == TRUE) || (mNumPLPIds == 1) || (mIsDvbt2CarrierDetected() == FALSE) )
    {
        /* start sdm collection with appropriate mode */
        ctrl_StartCollection(HsvDmxMain, ctrl_Normal);
    }
    UNUSED(param);
}

void CHsvDvbTInstallation_mDtr_Priv::FuncDtrStationNotFound (Nat32 param)
{
	SET_INS_STATE(ConstStScanProgress);
	mStopSdm(HsvDmxMain);
    UNUSED(param);
}

void CHsvDvbTInstallation_mDtr_Priv::FuncDtrDataAvailable (Nat32 param)
{
    HSVSPTYPE(ActualTSService, dvb, sdt) service;
    int index = 0;
    int loopCount = 0;
    int numSvcs = strapi_GetSize (HsvMain, HSVSPID(ActualTSService, dvb, sdt));
    int Onid = 0, Tsid = 0, retval = 0;

    int fiServID = sysset_GetServiceIDForChNameUpdate();

    if(fiServID > 0)
    {
    	int fiIsExtractScanResult = sysset_GetExtractScanResult();

    	for (loopCount = 0; loopCount < numSvcs; ++loopCount)
    	{
    		if(TRUE == strapi_GetByIndex(HsvMain, HSVSPID(ActualTSService, dvb, sdt), loopCount, &service))
    	    {
    			if(service.ServiceId == fiServID)
    			{
    				if(fiIsExtractScanResult)
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
    				}

    				break;
    			}
    	    }
    	}

    	if(loopCount >= numSvcs)
    	{
    		if(mNumPLPIds > 1) {
    			miT2PLPIDX++;

    			TraceDebug(m,"%s %d : select next PLP ID: %d", __FUNCTION__, __LINE__, miT2PLPIDX);

    			if(miT2PLPIDX < mNumPLPIds) {
    				idtr_SetStreamPriority ((HsvStreamPriority)mDetectedPlpIds[miT2PLPIDX]);
    				insN_OnEvent(insN_EventT2SwitchPLPID, mDetectedPlpIds[miT2PLPIDX]);
    			}
    			else
    				insN_OnEvent(insN_EventServiceNotFound, 0);
    		}
    		else
    			insN_OnEvent(insN_EventServiceNotFound, 0);

    		UNUSED(param);

    		return;
    	}

    	if(fiIsExtractScanResult)
    	{
    		insN_OnEvent(insN_EventServiceFound, 0);
    		UNUSED(param);

    		return;
    	}
    } else {

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
    		SET_INS_STATE(ConstStPMTWait);
    		//Set the filter for monitoring CurrentProgram PMT
    		strmfltr_Set(HsvMain, HsvCurrentProgram, service.ServiceId);
    	}
    }
	//else
	//{
		/* Just in case some error happens, UI should not keep waiting. Ignore AV Playback, Give notificaiton further */
		insN_OnEvent(insN_EventChannelFound, MANUAL_MODE);
	//}
    
    UNUSED(param);
}


void CHsvDvbTInstallation_mDtr_Priv::FuncDtrPMTCollected (Nat32 param)
{    
    TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);

    if(!mPlayStarted)
    {
        //Start the AV playback for CurrentProgram            
        mPlayService(param);
    }
    /* ntf to apps, to show "store" button */
    insN_OnEvent(insN_EventChannelFound, MANUAL_MODE);
    UNUSED(param);
}

void CHsvDvbTInstallation_mDtr_Priv::FuncSignalStrength(Nat32 param)
{

    if(sigstr_StartSigStrMeasAll() == TRUE)
    {
        TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);
        pmp_PmpSendAfter(mPump, ConstEvMeasureSignalStr, (Nat32)NULL, SIGNALSTRENGTH_POLLTIME);
    }
    UNUSED(param);
}

void CHsvDvbTInstallation_mDtr_Priv::FuncOnHierarchyModeDetected(Nat32 param)
{
    if(TURNED_ON)
    { 
        switch(param)
        {
            case tmFe_HierarchyNone:
            case tmFe_HierarchyModeInvalid:
            case tmFe_HierarchyModeUnknown:
                mInstStatus.HierarchyMode = FALSE;
                break;
            default:
                mInstStatus.HierarchyMode = TRUE;
                insN_OnEvent(insN_EventHeirarchyModeDetected, MANUAL_MODE); 
                break;
        }
    }
}

void CHsvDvbTInstallation_mDtr_Priv::FuncOnMeasReady(Nat32  param)
{
	if(sigstr_GetSigStrengthMeasured() == TRUE)
    {
        TraceDebug(m,"%s %d mHeirarchyValue %d", __FUNCTION__, __LINE__, mHeirarchyValue);
        /*if sdm data available -> Acquire & process it now */
        if(mInstStatus.SdmData == ACQUISITION_COMPLETED)
        {
            TraceDebug(m,"%s %d mHeirarchyValue %d", __FUNCTION__, __LINE__, mHeirarchyValue);
            pmp_PmpSend(mPump, ConstEvDataAvailable, (Nat32)NULL);
        }
    }
}

void CHsvDvbTInstallation_mDtr_Priv::mInitialise(Nat32 freq)
{
    SET_INS_STATE(ConstStIdle);
    mInstStatus.SdmData       = NO_DATA;
    mInstStatus.HierarchyMode = FALSE;
    
	if(mUserSelectedMux == FALSE)
	{
		/* default value */
		mHeirarchyValue           = HsvStreamPriorityHigh;
	}
	mInstStatus.Frequency     = freq; 
    idataacq_Initialise();

    mInitialiseDecoderParams();
}
void CHsvDvbTInstallation_mDtr_Priv::mStopSdm(HsvDemux dmx)
{

    if(ctrl_GetMode(dmx) == ctrl_Idle)
    {
        TraceDebug(m,"  :  %d %s state = %d ", __LINE__, __FUNCTION__, mInstStatus.State);
        if(rins_GetInstallationState() == rins_StDigital)
        {
            TraceDebug(m,"  :  %d %s state = %d ", __LINE__, __FUNCTION__, mInstStatus.State);
            pmp_PmpSend(mPump, ConstEvSdmStopped, (Nat32)NULL);
        }
    }
    else
    {
        TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);
        ctrl_StopCollection(dmx);
    }
}

void CHsvDvbTInstallation_mDtr_Priv::mSetChannelDecoderAttributes(void)
{
    tmErrorCode_t errorcode = TM_OK;
    Nat16 Decoder = mGetChannelDecoder();

    if(mCurrentDecoder != Decoder)
    {
        mCurrentDecoder = Decoder;
    }
	switch(COUNTRY)
	{
	case cids_CountryTaiwan:		
		feapi_SetChanBandwidth(WINDOWID, tmFe_ChanBandwidth6MHz, &errorcode); 
		break;
	case cids_CountryIndonesia: 	
		feapi_SetChanBandwidth(WINDOWID, tmFe_ChanBandwidth_6_7_8MHz, &errorcode); 
		break;
	default:
		feapi_SetChanBandwidth(WINDOWID, tmFe_ChanBandwidthAuto, &errorcode); 
		break;
	}		
    ASSERT(TM_OK == errorcode);

    TraceDebug(m,"%s %d ChanBandwidth %d", __FUNCTION__, __LINE__,mGetChanBandwidth(mGetCorrectedBand(mInstStatus.Frequency, sysset_GetInstallCountry()), sysset_GetInstallCountry()));

    feapi_SetConstellation(WINDOWID,feapi_ChanDecDvbT, tmFe_AutoConstellation, &errorcode);
    ASSERT(TM_OK == errorcode);

}

void CHsvDvbTInstallation_mDtr_Priv::mSetTunerAttributes()
{
    tmErrorCode_t errorcode;

    mSetHeirarchyMux(mHeirarchyValue);

    mInstStatus.HierarchyMode = FALSE;  //reset before setfreq, just in case plf ntf.. comes syncronously   
    SET_INS_STATE(ConstStTunerWait);
    mPlayStarted = FALSE;

    TraceDebug(m,"%s %d SetFreq %ld", __FUNCTION__, __LINE__, mInstStatus.Frequency);
    feapi_SetFreq(WINDOWID, mInstStatus.Frequency, TRUE, &errorcode);
    ASSERT(TM_OK == errorcode);
}

void CHsvDvbTInstallation_mDtr_Priv::mPlayService(int serviceid)
{
    HsvPMTAudioInfo audioInfo;
    HsvPMTBasicPidInfo basicPIDInfo;    
    HsvDestination dest = HsvMain;
	Nat8		IsAvPidSet = FALSE;
	
    if(mPlayStarted == FALSE)
    {
		/* Initializing with INVALID PID Values */
		audioInfo.Pid = 8191;
		basicPIDInfo.VideoPid = 8191;
		basicPIDInfo.PcrPid = 8191;

		TraceDebug(m,"Play Started on Service = %d\r\n", serviceid);
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
			mPlayStarted = TRUE;
		}
        else
        {
            TraceDebug(m,"%s(): Error... Failed to get AV pids for Service = 0x%x", __FUNCTION__, serviceid);
        }
    }
}

void CHsvDvbTInstallation_mDtr_Priv::mSetHeirarchyMux(int HeirarchyValue)
{
    tmErrorCode_t errorcode;


    if(mCurrentDecoder == feapi_ChanDecDvbT2)
    {
        TraceNotice(m,"%s %d HeirarchyValue %d", __FUNCTION__, __LINE__, HeirarchyValue);
        chdecdvbt2_SelectPlpId(WINDOWID, HeirarchyValue);
    }
    else
    {
        TraceDebug(m,"%s %d auto PLP ID also selected HeirarchyValue %d", __FUNCTION__, __LINE__, HeirarchyValue);
        feapi_SetStreamPriority(WINDOWID, ConvertToPlatformStreamPriority((HsvStreamPriority)HeirarchyValue), &errorcode);
        ASSERT(TM_OK == errorcode);

        int fiFocusedPlpId = sysset_GetFocusedPlpId();

        /* Set PLPId to Auto in case of T2 | T decoder */
        if(fiFocusedPlpId == -1)
        	errorcode = chdecdvbt2_SelectPlpId(WINDOWID, chdecdvbt2_PlpIdAuto);
        else
        	errorcode = chdecdvbt2_SelectPlpId(WINDOWID, (HsvStreamPriority)fiFocusedPlpId);

        ASSERT(TM_OK == errorcode);
    }
}

inline Bool CHsvDvbTInstallation_mDtr_Priv::mIsDvbt2CarrierDetected(void)
{
    FResult ret;
    Nat32 Decoder;
    Bool retval = FALSE;
    
	if(eurdiv_IsDVBT2Supported())
	{
		ret = chdecdvbt2_GetT2CarrierPresent(WINDOWID, &retval);
	
		TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
		if(ret == TRUE)
		{
			retval = TRUE;
		}
	}    
    return retval;
}


int CHsvDvbTInstallation_mDtr_Priv::mWaitForData(void)
{
	int retval = idvbtqctrlN_DataAvailable;
	if(MANUAL_INSTALL)
	{
		int fiServID = sysset_GetServiceIDForChNameUpdate();

		if( fiServID > 0 ||
				((rins_GetMedium() == rins_Cable) && (eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite)) )
		{
			retval = idvbtqctrlN_SiDataAvailable;
		}
	}
	return retval;
}


void CHsvDvbTInstallation_mDtr_Priv::idtrpow_Init(void)
{
    mPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE,"hsvdvbtins_mDtr");
    mConstModuleLifeCycle = ConstInitialised;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrpow_TurnOn(void)
{
    mConstModuleLifeCycle = ConstTurnedOn;
    mInitialise(START_FREQUENCY);   // Naresh: guess this is not reqd, correct me
}

void CHsvDvbTInstallation_mDtr_Priv::idtrpow_TurnOff(void)
{
    ASSERT(!"Not Implemented here");
}

FResult CHsvDvbTInstallation_mDtr_Priv::idtr_StartInstallation(int source, int ptc, int mode)
{
    FResult retval = 0;

    TraceDebug(m,"%s %d source %d mode %d", __FUNCTION__, __LINE__, source, mode);
    if(TURNED_ON)
    {
        if(VALID_SOURCE(source) && VALID_INSTALL_MODE(mode))
        {
            TraceDebug(m,"%s %d source %d mode %d", __FUNCTION__, __LINE__, source, mode);
            pmp_PmpSend(mPump, ConstEvStart, (Nat32)ptc);
        }
    }
    return retval;
}

FResult CHsvDvbTInstallation_mDtr_Priv::idtr_StopInstallation(void )
{
    FResult retval = err_Ok;

    TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
    if(TURNED_ON)
    {
        if(mInstStatus.State != ConstStIdle)
        {
            pmp_PmpSend(mPump, ConstEvStop, (Nat32)NULL);
        }
        else
        {
            retval = err_InstallationNotInProgress;
        }
    }
    return retval;
}

void CHsvDvbTInstallation_mDtr_Priv::idtr_SyncComplete(void)
{
    tmErrorCode_t errorcode;
    if(TURNED_ON)
    {
        TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
//        pgdb_CommitTable(pgdb_GetCurrentTable());

        SET_INS_STATE(ConstStIdle);
        feapi_SetSearchRates(WINDOWID, NULL, 0, &errorcode);
        ASSERT(TM_OK == errorcode);
        sigstr_StopSigStrMeasAll();


		mUserSelectedMux = FALSE;
		mStopSdm(HsvDmxMain);

        /* ntf to apps, to query the number of installed channels */
        insN_OnEvent(insN_EventChannelFound, MANUAL_MODE);
        insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
    }
}

void CHsvDvbTInstallation_mDtr_Priv::idtr_GetPTCInfo(HsvInstallationPTC *ptc)
{
    int PLPId = 0, PlfParam1;
    tmErrorCode_t errorcode = TM_OK;
    ptc->IqMode             =   HsvIqModeNormal;
    ptc->SymbolRate         =   0;


    ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
    ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
    ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);
    feapi_GetFreq(WINDOWID, &(ptc->Frequency), &errorcode);
	ptc->Frequency = (ptc->Frequency *1000)/16;
    ASSERT(TM_OK  ==  errorcode);

    ptc->FrequencyError = ptc->TimeError = ptc->ChannelInformation = ptc->CodeRateHigh = ptc->CodeRateLow = ptc->TxMode = ptc->GuardInterval = 0;
    ptc->FrequencyOffset = ptc->SymbolRate = ptc->HierarchyMode = 0;

    feapi_GetActualConstellation (WINDOWID,feapi_ChanDecDvbT, (tmFe_Constellation_t*) (&PlfParam1), &errorcode);
    ASSERT(TM_OK  ==  errorcode);
    
    ptc->ModulationType     = PlfParam1;// ConvertFromPlatformConstellation((tmFe_Constellation_t)PlfParam1); 

    feapi_GetActualChanBandwidth (WINDOWID, (tmFe_ChanBandwidth_t* ) (&PlfParam1), &errorcode);
    ASSERT(TM_OK  ==  errorcode);
    ptc->ChannelBandwidth   =   PlfParam1;//ConvertFromPlatformChanBandwidth((tmFe_ChanBandwidth_t)PlfParam1);

    if(mIsDvbt2CarrierDetected() == TRUE)
    {
        ptc->DecoderType        =   feapi_ChanDecDvbT2;
        chdecdvbt2_GetActivePlpId(WINDOWID, &PLPId);
        ptc->StreamPriority     =   PLPId;

        TraceNotice(m,"@ %d PLPId %d ptc->StreamPriority %d", __LINE__, PLPId, ptc->StreamPriority);
    }
    else
    {
        ptc->DecoderType        =   feapi_ChanDecDvbT;
        feapi_GetStreamPriority ( WINDOWID, (tmFe_StreamPriority_t* ) (&PlfParam1), &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        ptc->StreamPriority     =   ConvertFromPlatformStreamPriority((tmFe_StreamPriority_t)PlfParam1);

        TraceNotice(m,"@ %d Frequency %ld PlfParam1 %d errorcode %d ptc->StreamPriority %d", __LINE__, ptc->Frequency, PlfParam1, (int)errorcode, ptc->StreamPriority);
    }
}

FResult CHsvDvbTInstallation_mDtr_Priv::idtr_StoreWeakSignalInstallationChannel()        
{
    FResult retval = 0;

    TraceDebug(m,"%s %d TURNED_ON %d", __FUNCTION__, __LINE__, TURNED_ON);
    if(TURNED_ON)
    {
        idataacq_AcquireData();
        idataacq_SyncTemporaryTableRecords();

        mInitialiseDecoderParams();
    }
    return retval;
}

void CHsvDvbTInstallation_mDtr_Priv::idtr_SetStreamPriority (HsvStreamPriority prio)
{
	mUserSelectedMux = TRUE;
    mHeirarchyValue = prio;
	
	
    mPlayStarted = FALSE;
    SET_INS_STATE(ConstStScanProgress);
    mStopSdm(HsvDmxMain);
}

HsvStreamPriority CHsvDvbTInstallation_mDtr_Priv::idtr_GetStreamPriority(void)
{
    TraceDebug(m,"%s %d mHeirarchyValue %d", __FUNCTION__, __LINE__, mHeirarchyValue);
    return mHeirarchyValue;
}

HsvHierarchyMode CHsvDvbTInstallation_mDtr_Priv::idtr_GetHierarchyMode(void)
{
    return (HsvHierarchyMode)0;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnStationFound()
{
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {
        pmp_PmpSend( mPump, ConstEvStationFound, (Nat32)NULL);
    }
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnStationNotFound()
{
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {       
        pmp_PmpSend( mPump, ConstEvStationNotFound, (Nat32)NULL);
    }
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnMeasReady( int ssm, Nat32 strength )
{
    UNUSED(strength);
    
    if(TURNED_ON)
    {
		pmp_PmpSend( mPump, ConstEvOnMeasReady, (Nat32)ssm);
	}
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode )
{
    TraceNotice(m,"%s %d\n", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {
        pmp_PmpSend( mPump, ConstEvHierarchyModeDetected, (Nat32)mode);
    }
    
}

void CHsvDvbTInstallation_mDtr_Priv::idctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(value);
    TraceDebug(m,"%s %d eventid %d TURNED_ON %d", __FUNCTION__, __LINE__, eventid,TURNED_ON);
	TraceNotice (m," Notification from SDM reached DTR %d  ", eventid);
	TraceNotice (m," GetInstallationState: %d StDigital: %d mInstStatus.State: %d st: %d ",rins_GetInstallationState(), rins_StDigital,mInstStatus.State, ConstStIdle);
    if(TURNED_ON && (rins_GetInstallationState() == rins_StDigital) && (mInstStatus.State != ConstStIdle))
    {
        TraceDebug(m,"%s %d eventid %d", __FUNCTION__, __LINE__, eventid);
        switch(eventid)
        {
            case idctrlN_DataAvailable:
				TraceNotice (m," DataAvailable   ");
                mInstStatus.SdmData = ACQUISITION_COMPLETED;
                //if(sigstr_GetSigStrengthMeasured() == TRUE)
                {   
                    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
                    pmp_PmpSend(mPump, ConstEvDataAvailable, (Nat32)NULL);
                }
                break;

            case idctrlN_DataNotAvailable:
                mInstStatus.SdmData       = NO_DATA;
                SET_INS_STATE(ConstStIdle);
                insN_OnEvent(insN_EventChannelNotFound, MANUAL_MODE);
                insN_OnEvent(insN_EventInstallationStopped, MANUAL_MODE);
                break;

            case idctrlN_StartedCollection:
                SET_INS_STATE(ConstStDemuxWait);
                break;

            case idctrlN_StoppedCollection:
                mInstStatus.SdmData       = NO_DATA;
                pmp_PmpSend(mPump, ConstEvSdmStopped, (Nat32)NULL);
                break;

            case idctrlN_SiDataAvailable:
				TraceNotice (m," SiDataAvailable   ");
                if(mWaitForData() == idvbtqctrlN_SiDataAvailable)
                {
                    mInstStatus.SdmData = ACQUISITION_COMPLETED;
                    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
                    if(sigstr_GetSigStrengthMeasured() == TRUE)
                    {   
                        pmp_PmpSend(mPump, ConstEvDataAvailable, (Nat32)NULL);
                    }
                }       
                break;
            default:
                break;
        }
        UNUSED(dmx);
    }
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_GetPLPIds(int *PLPIds)
{
    int NumPLPIds;
    chdecdvbt2_GetDetectedPlpIds(WINDOWID, &NumPLPIds, PLPIds);
    return NumPLPIds;
}

Bool CHsvDvbTInstallation_mDtr_Priv::idtr_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{
    UNUSED(ONID);
    UNUSED(TSID);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mDtr_Priv::idtr_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_GetNumberOfDigitalChannelsRemoved()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

/*
   FResult idtr_StoreWeakSignalInstallationChannel()
   {
   ASSERT(!"Not Implemented here");
   }
   */

FResult CHsvDvbTInstallation_mDtr_Priv::idtr_StartDigitalScan()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mDtr_Priv::idtr_ClearCache()
{
    ASSERT(!"Not Implemented here");
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_GetNoOfPass()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

Bool CHsvDvbTInstallation_mDtr_Priv::idtr_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{
    UNUSED(ONID);
    UNUSED(TSID);
    ASSERT(!"Not Implemented here");
    return FALSE;   
}

/*
   FResult idtr_SetStreamPriority( int winid, tmFe_StreamPriority_t streamPriority, Nat32* retval )
   {
   UNUSED(winid);
   UNUSED(streamPriority);
   UNUSED(retval);
   ASSERT(!"Not Implemented here");

   }
   */

FResult CHsvDvbTInstallation_mDtr_Priv::idtr_StartDigitalTuning(int frequency)
{   
    UNUSED(frequency);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_GetCurrentPass()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_GetNumberOfDigitalChannelsFound()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mDtr_Priv::idtr_Initialise()
{
    mInitialise(START_FREQUENCY);
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_GetSDTType()
{
    return FALSE;
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_ZiggoGetSDTType(Nat16 Frequency)
{
    UNUSED(Frequency);
    return FALSE;
}

void CHsvDvbTInstallation_mDtr_Priv::idtr_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    UNUSED(ptc);
    UNUSED(Onid);
    UNUSED(Tsid);
}

FResult CHsvDvbTInstallation_mDtr_Priv::idtr_StopDigitalScan()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_GetTargetNitType(Nat16* NetworkId)
{
    UNUSED(NetworkId);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mDtr_Priv::idtr_GetCurrentState()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

inline Nat16 CHsvDvbTInstallation_mDtr_Priv::mGetChannelDecoder(void)
{
    Nat16 retval = feapi_ChanDecDvbT;

    if(mScanPLPState == ConstStScanProgress || sysset_GetIsDVBT2Scan()==1)
    {
        retval = feapi_ChanDecDvbT2;
        TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    }
    else
    {
		/* means it is a non PLP DVBT/T2 case */
		if(mInstStatus.HierarchyMode == TRUE)
		{
			retval = feapi_ChanDecDvbT;
			TraceNotice(m,"%s %d retval %d\n", __FUNCTION__, __LINE__, retval);
		}
		else if(eurdiv_IsDVBT2Supported())
        {
            retval = (feapi_ChanDecDvbT | feapi_ChanDecDvbT2);
            TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
        }
    }   
    return retval;
}

inline void CHsvDvbTInstallation_mDtr_Priv::mInitialiseDecoderParams(void)
{
    int i = 0;

    TraceDebug(m,"%s %d mCurrentDecoder %d mNumPLPIds %d", __FUNCTION__, __LINE__, mCurrentDecoder, mNumPLPIds);

    mCurrentDecoder           = 0xFFFF;
    mNumPLPIds                = 0;
    mScanPLPState             = ConstStIdle;
    mInstStatus.HierarchyMode = FALSE;
    mPlayStarted              = FALSE;

    for(i=0; i < MAX_PLP_IDS; i++)
    {
        mDetectedPlpIds[i] = -1;
    }
}

int CHsvDvbTInstallation_mDtr_Priv::mGetChanBandwidth (int Band, int Country)
{
    HsvInstallationSpectrum *Spectrum = (HsvInstallationSpectrum *)((ANTENNA_MEDIUM)?AntennaSpectrum[Country]: CableSpectrum);

    if(Band >= MAX_BANDS)
    {
        Band = (MAX_BANDS - 1);
    }

    TraceDebug(m,"%s Spectrum[%d].Bandwidth %d", __FUNCTION__, Band, Spectrum[Band].Bandwidth);

    return Spectrum[Band].Bandwidth;
}

int CHsvDvbTInstallation_mDtr_Priv::mGetCorrectedBand(int Frequency, int Country)
{
    Bool FrequencyCorrected = FALSE;
    int MinFreq =   INVALID_FREQUENCY, MaxFreq  =   INVALID_FREQUENCY, FrequencyBand=0, centrefrequency;
    int i = 0, NoofMatches = 0, FrequencyDiff = 0, UserFrequency = Frequency, CorrectedFrequency = Frequency;
    HsvInstallationSpectrum *Spectrum = (HsvInstallationSpectrum *)((ANTENNA_MEDIUM)?AntennaSpectrum[Country]: CableSpectrum);

    while( (MinFreq = Spectrum[i].StartFrequency)!= INVALID_FREQUENCY)
    {
        MaxFreq    =   Spectrum[i].EndFrequency;
        CorrectedFrequency = UserFrequency;
        if ( MinFreq <= UserFrequency )
        {
            if( MaxFreq >= UserFrequency)
            {
                /* Found the right band */
                int bandbw      =   mConvertBandwidthToValue(Spectrum[i].Bandwidth) << 4;
                if ((UserFrequency - MinFreq) % bandbw  > bandbw/2 )
                {
                    /* Correct to the higher value */
                    CorrectedFrequency = UserFrequency + bandbw;
                }
                CorrectedFrequency = CorrectedFrequency - (UserFrequency-MinFreq) % bandbw;

                /*  Calculate the corrected frequency
                    if  centrefrequency + bw/2 =  max frequency in that band    */

                centrefrequency = UserFrequency + ((MaxFreq- UserFrequency) % bandbw) + bandbw/2;

                if ((centrefrequency + bandbw/2 == MaxFreq) && ((centrefrequency - bandbw) == MinFreq))
                {
                    CorrectedFrequency =  centrefrequency;
                }
                TraceDebug(m,"centrefrequency:%d,CorrectedFrequency:%d",centrefrequency,CorrectedFrequency);
                FrequencyCorrected = TRUE;
                NoofMatches++;
                if ( NoofMatches == 1 )
                {
                    FrequencyDiff = GET_ABSOLUTE_VAL (UserFrequency - CorrectedFrequency);
                    Frequency = CorrectedFrequency;
                    FrequencyBand = i;
                } else
                {
                    if  (FrequencyDiff > GET_ABSOLUTE_VAL (UserFrequency - CorrectedFrequency))
                    {
                        FrequencyDiff = GET_ABSOLUTE_VAL (UserFrequency - CorrectedFrequency);
                        Frequency = CorrectedFrequency;
                        FrequencyBand =i;
                    }
                }

            }
            else
            {
                /* Let it go once more into the loop and it will hit upon the next one */
            }
        }
        else
        {   /* Outside the country band - but there may be valid bands after it */
            break;
        }
        i++;
    }
    if(!FrequencyCorrected)
    {
        /* No Band found - Its outside all the bands for the country - could be inbetween two bands also */
        if( Spectrum[i].StartFrequency == INVALID_FREQUENCY)
            FrequencyBand = i-1;
        else
            FrequencyBand = i;
    }

    TraceDebug(m,"[CS]returning Corrected Band:%d",FrequencyBand);

    return FrequencyBand;
}

tmFe_StreamPriority_t CHsvDvbTInstallation_mDtr_Priv::ConvertToPlatformStreamPriority(HsvStreamPriority inval)
{
    tmFe_StreamPriority_t outval = tmFe_StreamPriorityHigh;
    switch(inval)
    {
#define HSVSTREAMPRIORITY(a)  case (Hsv##a): \
        outval  =   tmFe_##a;                \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif
        default:
            break;
    }
    return outval;
}

int CHsvDvbTInstallation_mDtr_Priv::mConvertBandwidthToValue(tmFe_ChanBandwidth_t Bandwidth)
{
    int retval = 8;
    switch(Bandwidth)
    {
        case tmFe_ChanBandwidth6MHz:
            retval = 6;
            break;
        case tmFe_ChanBandwidth7MHz:
            retval = 7;
            break;
        case tmFe_ChanBandwidth8MHz:
            retval = 8;
            break;
        default:
            break;
    }
    return retval;
}


void CHsvDvbTInstallation_mDtr_Priv::idtr_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvDvbTInstallation_mDtr_Priv::idtr_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}


void CHsvDvbTInstallation_mDtr_Priv::idtr_ClearPersistent() 
{
	return;
}


/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvDvbTInstallation_mDtr_Priv::idtrfeN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}


void CHsvDvbTInstallation_mDtr_Priv::idstrapiN_OnAdded (HsvDestination dest, int spid, int key1, int key2, int key3)
{  
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);    
}

void CHsvDvbTInstallation_mDtr_Priv::idstrapiN_OnChanged  (HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{    
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3); 
    UNUSED(eventid); 
}

void CHsvDvbTInstallation_mDtr_Priv::idstrapiN_OnRemoved (HsvDestination dest, int spid, int key1, int key2, int key3)
{    
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}

void CHsvDvbTInstallation_mDtr_Priv::idstrapiN_OnCompleted (HsvDestination dest, int spid)
{
    switch(spid)
    {
        case HSVSPID(CurrentProgram, mpeg, pmt):
            {
                int currentPgm = -1;
                if (TRUE == strapi_GetByKey (dest, HSVSPID(CurrentProgram, mpeg, pmt), 0, 0, 0, (void *)(&currentPgm)))
                {
                    pmp_PmpSend(mPump, ConstEvPMTCollected, currentPgm);
                }
            }
            break;

        default:
            break;
    }
}



