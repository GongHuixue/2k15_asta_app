#include "_hsvdvbtins_mQuick.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbtins_mQuick")

#ifndef __cplusplus

#include "../hsveuins/DVBTSpectrum.h"

#include "../type/InstallationConstants.h"

#else

#include "DVBTSpectrum.h"

#include "InstallationConstants.h"

#endif

#include "plftoMWconstantsWrapper.h"



#ifndef __cplusplus

#else

#endif





int CHsvDvbTInstallation_mQuick_Priv::s__mScanPLPState,CHsvDvbTInstallation_mQuick_Priv::s__mInstalledPLPIds,CHsvDvbTInstallation_mQuick_Priv::s__mDetectedPlpIds[MAX_PLP_IDS],CHsvDvbTInstallation_mQuick_Priv::s__mNumPLPIds;

Nat16 CHsvDvbTInstallation_mQuick_Priv::s__mCurrentDecoder;




















const FunctionNat32 CHsvDvbTInstallation_mQuick_Priv::EventActionMatrix[][10] =
{
										/*    ConstStIdle,       			ConstStScanProgress,  			ConstStTunerWait,						ConstStDemuxWait        			*/
    /* ConstEvStart */             		{  FNADDR(FuncStartInstallation), 	NULL,                 			NULL,									NULL                  				 },
    /* ConstEvStop */              		{  NULL,                  			FNADDR(FuncStopInstallation), 	FNADDR(FuncStopInstallation),			FNADDR(FuncStopInstallation)   		 },
    /* ConstEvSdmStopped */        		{  NULL,                  			FNADDR(FuncSdmStopped),       	NULL,									FNADDR(FuncSdmStopped)         		 },
    /* ConstEvDataAvailable */     		{  NULL,                  			NULL,                 			NULL,									FNADDR(FuncDataAvailable)            },
    /* ConstEvStationFound */      		{  NULL,                  			NULL,                 			FNADDR(FuncStationFound),				NULL                                 },
    /* ConstEvStationNotFound */   		{  NULL,                  			NULL,                 			FNADDR(FuncStationNotFound),			NULL                                 },
    /* ConstEvMakeDecision */      		{  NULL,                  			FNADDR(FuncMakeDecision),     	NULL,									NULL                                 },
    /* DummyEvent */               		{  NULL,                  			NULL,                 			NULL,									NULL                                 },
    /* ConstEvHierarchyModeDetected */  {  NULL,               				NULL,                 			FNADDR(FuncOnHierarchyModeDetected), 	FNADDR(FuncOnHierarchyModeDetected)  },
	/* ConstEvOnMeasReady */       		{  NULL,                  			NULL,                 			FNADDR(FuncOnMeasReady),				FNADDR(FuncOnMeasReady)		         },
    /* ConstEvPMTCollected */			{  NULL,                  			NULL,                 			NULL,									NULL                                 }
};										


void CHsvDvbTInstallation_mQuick_Priv::iquick_SetStreamPriority(HsvStreamPriority prio)
{
    UNUSED(prio);
    TraceNotice(m," Stubbed iquick_SetStreamPriority called ");    
}

void CHsvDvbTInstallation_mQuick_Priv::PumpHandler(int event, Nat32 param)
{
    UNUSED(param);
    TraceNotice(m,"%s %d event %d mInstStatus.State %d", __FUNCTION__, __LINE__, event, mInstStatus.State);
    if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
    {
        TraceNotice(m,"%s %d event %d mInstStatus.State %d", __FUNCTION__, __LINE__, event, mInstStatus.State);
        if(EventActionMatrix[event][mInstStatus.State] != NULL)
        {
            TraceNotice(m,"%s %d event %d mInstStatus.State %d", __FUNCTION__, __LINE__, event, mInstStatus.State);
            FPCALL(EventActionMatrix[event][mInstStatus.State])(param);
        }
    }
}

void CHsvDvbTInstallation_mQuick_Priv::FuncStartInstallation(Nat32  param)
{
    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    mInitialise(START_FREQUENCY);
    mctl_Stop(HsvMain);

    SET_INS_STATE(ConstStScanProgress);
    mStopSdm(HsvDmxMain);
    UNUSED(param);
}

void CHsvDvbTInstallation_mQuick_Priv::FuncStopInstallation(Nat32  param)
{
    Nat32 errorcode;

    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    /* Naresh: correct me: calling plfApi calls invariably here in all states, does this harm */
    SET_INS_STATE(ConstStIdle);

    feapi_StopSearch(WINDOWID, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    sigstr_StopSigStrMeasAll();
    mStopSdm(HsvDmxMain);
    mInitialise(START_FREQUENCY);
    insN_OnEvent(insN_EventInstallationStopped, rins_GetInstallationMode());
    UNUSED(param);
}

void CHsvDvbTInstallation_mQuick_Priv::FuncSdmStopped(Nat32  param)
{
    if(mInstStatus.State == ConstStScanProgress)
    {
        TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
        mSetChannelDecoderAttributes();
        mSetTunerAttributes();
    }
    else
    {
        TraceNotice(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
        SET_INS_STATE(ConstStScanProgress);
        pmp_PmpSend(mPump, ConstEvMakeDecision, (Nat32)NULL);
    }
    UNUSED(param);
}

void CHsvDvbTInstallation_mQuick_Priv::FuncStationFound(Nat32  param)
{
    Nat32 errorcode;

    mInstStatus.StationFound  = TRUE;
	Bool HierarchialMuxPresent = FALSE;
	int TempPlpIds[MAX_PLP_IDS];
    feapi_GetFreq(WINDOWID, &mInstStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode );

    if(mIsDvbt2CarrierDetected() == TRUE)
    {
        TraceNotice(m,"%s %d mCurrentDecoder %d", __FUNCTION__, __LINE__,mCurrentDecoder);


		if(mInstalledPLPIds == 1)
		{
        	chdecdvbt2_GetDetectedPlpIds(WINDOWID, &mNumPLPIds, mDetectedPlpIds);
		}
		else
		{
			chdecdvbt2_GetDetectedPlpIds(WINDOWID, &mNumPLPIds, TempPlpIds);
	        TraceNotice(m,"%s %d mInstalledPLPIds %d mNumPLPIds %d", __FUNCTION__, __LINE__, mInstalledPLPIds, mNumPLPIds);
		}

        TraceNotice(m,"%s %d NumPLPIds %d", __FUNCTION__, __LINE__, mNumPLPIds);
        if(mNumPLPIds > 1)
        {
            mInstStatus.HierarchyMode = TRUE;

            /* set PLP state */
            mScanPLPState = ConstStScanProgress;
			if(mNumPLPIds > MAX_PLP_IDS)
			{
				mNumPLPIds = MAX_PLP_IDS;
			}
        }
    }
	else
	{
		feapi_GetHierarchyMuxPresence(WINDOWID, &HierarchialMuxPresent,&errorcode);
		TraceNotice(m,"%s %d HierarchialMuxPresent: %d",__FUNCTION__, __LINE__,HierarchialMuxPresent);
		if(HierarchialMuxPresent == TRUE)
		{
			mSetHierarchyMode();
		}
	}
		
    /* start signal strength measurement */
    sigstr_StartSigStrMeasAll();

    /* start sdm collection with appropriate mode */
    ctrl_StartCollection(HsvDmxMain, ctrl_Minimal); 
    UNUSED(param);
}

void CHsvDvbTInstallation_mQuick_Priv::FuncStationNotFound(Nat32  param)
{
    TraceNotice(m,"%s %d mInstStatus.HierarchyMode %d", __FUNCTION__, __LINE__, mInstStatus.HierarchyMode);

    mInstStatus.StationFound  = FALSE;

    if(mInstStatus.HierarchyMode == TRUE)
    {
        mInstStatus.HierarchyMode = FALSE;
        mStopSdm(HsvDmxMain);
    }
    else
    {
        SET_INS_STATE(ConstStScanProgress);
        pmp_PmpSend(mPump, ConstEvMakeDecision, (Nat32)NULL);
    }
    UNUSED(param);
}

void CHsvDvbTInstallation_mQuick_Priv::FuncDataAvailable(Nat32  param)
{
    idataacq_AcquireData();
    /* ntf to apps, to query for num of channels */
    insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);

    mStopSdm(HsvDmxMain);
    UNUSED(param);
}

void CHsvDvbTInstallation_mQuick_Priv::FuncMakeDecision(Nat32  param)
{
    /* progress to next band in the spectrum */
    Nat32 errorcode;
    HsvInstallationSpectrum *Spectrum;

    if( (mInstStatus.HierarchyMode == TRUE) && (mAllMUXsInHierarchyScanned() == FALSE) )
    {
        TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
        mStopSdm(HsvDmxMain);
    }
    else
    {
        if(mInstStatus.HierarchyMode == TRUE)
        {
            /* reset it for next MUX */
            TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
            mInitialiseDecoderParams();
        }

        if( (mInstStatus.StationFound == FALSE) && (mInstStatus.HierarchyMode == FALSE) )
        {
            mInstStatus.FrequencyBand++;
        }
        Spectrum = (HsvInstallationSpectrum *)((ANTENNA_MEDIUM)?AntennaSpectrum[COUNTRY]: CableSpectrum);

        if(Spectrum[mInstStatus.FrequencyBand].StartFrequency == INVALID_FREQUENCY)
        {
            TraceNotice(m,"%s %d Scan completed", __FUNCTION__, __LINE__);

            SET_INS_STATE(ConstStIdle);
            feapi_StopSearch(WINDOWID, &errorcode);
            ASSERT(TM_OK  ==  errorcode);
            mStopSdm(HsvDmxMain);
            sigstr_StopSigStrMeasAll();
            idataacq_SyncTemporaryTableRecords();
        }
        else
        {                        
            TraceNotice(m,"%s %d mInstStatus.FrequencyBand %d", __FUNCTION__, __LINE__, mInstStatus.FrequencyBand);
            sigstr_StopSigStrMeasAll();
            mStopSdm(HsvDmxMain);
        }
    }
    UNUSED(param);
}

void CHsvDvbTInstallation_mQuick_Priv::FuncOnMeasReady(Nat32  param)
{
	if(sigstr_GetSigStrengthMeasured() == TRUE)
    {
        TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
        /*if sdm data available -> Acquire & process it now */
        if(mInstStatus.SdmData == ACQUISITION_COMPLETED)
        {
            TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
            pmp_PmpSend(mPump, ConstEvDataAvailable, (Nat32)NULL);
        }
    }
    else
    {
        TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    }
}

void CHsvDvbTInstallation_mQuick_Priv::mInitialise(Nat32 freq)
{
    SET_INS_STATE(ConstStIdle);
    mInstStatus.FrequencyBand = 0;
    mInstStatus.SdmData       = NO_DATA;
    mInstStatus.HierarchyMode = FALSE;
    mInstStatus.Frequency     = freq;
    mInstStatus.StationFound  = FALSE;

    mInitialiseDecoderParams();

    idataacq_Initialise();
}
void CHsvDvbTInstallation_mQuick_Priv::mStopSdm(HsvDemux dmx)
{
    if(ctrl_GetMode(dmx) == ctrl_Idle)
    {
        pmp_PmpSend(mPump, ConstEvSdmStopped, (Nat32)NULL);
    }
    else
    {
        ctrl_StopCollection(dmx);
    }
}

void CHsvDvbTInstallation_mQuick_Priv::mSetChannelDecoderAttributes(void)
{
    Nat32 errorcode = TM_OK;
    Nat16 Decoder = mGetChannelDecoder();
    HsvInstallationSpectrum *Spectrum = (HsvInstallationSpectrum *)((ANTENNA_MEDIUM)?AntennaSpectrum[COUNTRY]: CableSpectrum);

    TraceNotice(m,"%s %d Bandwidth %d mCurrentDecoder %d Decoder %d", __FUNCTION__, __LINE__, Spectrum[mInstStatus.FrequencyBand].Bandwidth, mCurrentDecoder, Decoder);

    if(mCurrentDecoder != Decoder)
    {
        mCurrentDecoder = Decoder;

        TraceNotice(m,"%s %d mCurrentDecoder %d", __FUNCTION__, __LINE__, mCurrentDecoder);
        ASSERT(errorcode == plferrids_Ok);
    }

    feapi_SetChanBandwidth ( WINDOWID, Spectrum[mInstStatus.FrequencyBand].Bandwidth, &errorcode ); 
    ASSERT(TM_OK == errorcode);

    feapi_SetConstellation(WINDOWID, feapi_ChanDecDvbT, tmFe_AutoConstellation, &errorcode);
    ASSERT(TM_OK == errorcode);
}

void CHsvDvbTInstallation_mQuick_Priv::mSetTunerAttributes(void)
{
    int HeirarchyValue = 0;
    Nat32 Frequency, errorcode           = TM_OK;
    Bool  HierarchyMode = mInstStatus.HierarchyMode;
	

	//TraceNotice(m,"%s :Country %d",__FUNCTION__,COUNTRY);

	HsvInstallationSpectrum *Spectrum    = (HsvInstallationSpectrum *)((ANTENNA_MEDIUM)?AntennaSpectrum[COUNTRY]: CableSpectrum);

    /* This function sets current tuned frequency - heirarchyMode(DVBT/DVBT2)
       start frequency in the current selected band - non-heirarchyMode(DVBT/DVBT2) */
    
	
    Frequency = ( (mInstStatus.HierarchyMode) || (mInstStatus.StationFound) )? mGetCorrectedFrequency(mInstStatus.Frequency, sysset_GetSystemCountry()): Spectrum[mInstStatus.FrequencyBand].StartFrequency;

    mGetHierarchyMUX(&HeirarchyValue);
    mSetHeirarchyMux(HeirarchyValue);
	HierarchyMode = mInstStatus.HierarchyMode;

    mInstStatus.HierarchyMode = FALSE;  //reset before setfreq, just in case plf ntf.. comes syncronously 
    SET_INS_STATE(ConstStTunerWait);

    TraceNotice(m,"%s %d SetFreq %d EndFreq %d", __FUNCTION__, __LINE__, (int)Frequency, Spectrum[mInstStatus.FrequencyBand].EndFrequency);
	//Sending start frequency as as Winid in strat search
	if (HierarchyMode == TRUE)
	{
		/* ANEESH: Making this change here for DVBT2 bringup */
		feapi_SetFreq ( WINDOWID, Frequency, FALSE, &errorcode);   
	}
    ASSERT(TM_OK == errorcode);

    if(HierarchyMode == FALSE)
    {
        TraceNotice(m,"%s %d startsearch with EndFreq %d", __FUNCTION__, __LINE__, Spectrum[mInstStatus.FrequencyBand].EndFrequency);
        /* only in case of non-heirarchy mode, as in other case, we have to still 
           install the other MUXes transmitted in current frequency */
        feapi_StartSearch ( WINDOWID, Frequency, tmFe_SmDefault, Spectrum[mInstStatus.FrequencyBand].EndFrequency, &errorcode );
        ASSERT(TM_OK == errorcode);
    }
}

void CHsvDvbTInstallation_mQuick_Priv::mGetHierarchyMUX(int *HierarchyValue)
{
    Nat32 errorcode;
    int i = 0, temp = 0, Active_PlpId;

    TraceNotice(m,"%s %d mScanPLPState %d", __FUNCTION__, __LINE__, mScanPLPState);
    if(mScanPLPState == ConstStScanProgress)
    {
        /* This means PLPId is in progress */
        *HierarchyValue = chdecdvbt2_PlpIdAuto;

        chdecdvbt2_GetActivePlpId (WINDOWID, &Active_PlpId);

        TraceNotice(m,"%s %d Active PlpId %d", __FUNCTION__, __LINE__, Active_PlpId);
        for (i = 0; i < mNumPLPIds; i++)
        {
            TraceNotice(m,"%s %d mDetectedPlpIds[%d] %d", __FUNCTION__, __LINE__, i, mDetectedPlpIds[i]);
            if(mDetectedPlpIds[i] == Active_PlpId)
            {
                TraceNotice(m,"mInstalledPLPIds %d NumPlpIds %d", mInstalledPLPIds, mNumPLPIds);
                if(mInstalledPLPIds < mNumPLPIds)
                {
                    /* ensure swap is done only in initial case, 2nd check will ensure that */
                    if( (i != 0) && (mInstalledPLPIds == 1) )
                    {
                        TraceNotice(m,"Swap mDetectedPlpIds[0] %d & mDetectedPlpIds[%d] %d", mDetectedPlpIds[0], i, mDetectedPlpIds[i]);
                        temp = mDetectedPlpIds[i];
                        mDetectedPlpIds[i] = mDetectedPlpIds[0];
                        mDetectedPlpIds[0] = temp;

                        /* Reset index to 0, as we have swapped the current plpid to 0th location */
                        i = 0;
                    }
                    *HierarchyValue =   mDetectedPlpIds [i + 1];
                    mInstalledPLPIds++;
                }
                break;
            }

        }
        TraceNotice(m,"Lithesh : %s %d *HierarchyValue %d", __FUNCTION__, __LINE__, *HierarchyValue);
    }
    else
    {
        tmFe_StreamPriority_t StreamPriority;

        *HierarchyValue  = tmFe_StreamPriorityHigh;
        if(mInstStatus.HierarchyMode == TRUE)
        {
            feapi_GetStreamPriority(WINDOWID, &StreamPriority, &errorcode);
            ASSERT(TM_OK  ==  errorcode);       
            if(StreamPriority == tmFe_StreamPriorityHigh)
            {
                *HierarchyValue  = tmFe_StreamPriorityLow;
            }
        }
    }

    TraceNotice(m,"%s %d *HierarchyValue %d", __FUNCTION__, __LINE__, *HierarchyValue);
}

Bool CHsvDvbTInstallation_mQuick_Priv::mAllMUXsInHierarchyScanned(void)
{
    Nat32 errorcode;
    Bool retval = TRUE;

    TraceNotice(m,"%s %d mScanPLPState %d", __FUNCTION__, __LINE__, mScanPLPState);
    if(mScanPLPState == ConstStScanProgress)
    {
        if(mInstalledPLPIds < mNumPLPIds)
        {
            retval = FALSE;
        }
        TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    }
    else
    {
        tmFe_StreamPriority_t StreamPriority;

        if(mInstStatus.HierarchyMode == TRUE)
        {
            feapi_GetStreamPriority(WINDOWID, &StreamPriority, &errorcode);
            ASSERT(TM_OK  ==  errorcode);       
            if(StreamPriority == tmFe_StreamPriorityHigh)
            {
                /* we have to try to tune to Low Priority MUX also */
                retval = FALSE;
            }
        }
    }

    TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}

void CHsvDvbTInstallation_mQuick_Priv::mSetHeirarchyMux(int HeirarchyValue)
{
    Nat32 errorcode;

    TraceNotice(m,"%s %d mCurrentDecoder %d", __FUNCTION__, __LINE__, mCurrentDecoder);

    if(mCurrentDecoder == feapi_ChanDecDvbT2)
    {
        errorcode = chdecdvbt2_SelectPlpId(WINDOWID, HeirarchyValue);   
        TraceNotice(m,"%s %d chdecdvbt2_SelectPlpId called, PlpId %d errorcode %d", __FUNCTION__, __LINE__, HeirarchyValue, (int)errorcode);
    }
    else
    {
        feapi_SetStreamPriority(WINDOWID, (tmFe_StreamPriority_t)HeirarchyValue, &errorcode);
        ASSERT(TM_OK == errorcode);
        TraceNotice(m,"%s %d HeirarchyValue %d errorcode %d", __FUNCTION__, __LINE__, HeirarchyValue,(int) errorcode);

        /* Set PLPId to Auto in case of T2 | T decoder */
        errorcode = chdecdvbt2_SelectPlpId(WINDOWID, chdecdvbt2_PlpIdAuto);
        TraceNotice(m,"%s %d HeirarchyValue %d errorcode %d", __FUNCTION__, __LINE__, HeirarchyValue, (int)errorcode);
    }
}

inline Bool CHsvDvbTInstallation_mQuick_Priv::mIsDvbt2CarrierDetected(void)
{
    FResult ret;
    Nat32 Decoder;
    Bool retval = FALSE;
    
    if(eurdiv_IsDVBT2Supported())
	{
		/* This function is to get DVBT2 carrier MUX presence as belwo function is not reliable
		   so try to get the value by decoder selected or NumofPLPIds stored upon stationFound */
		ret = chdecdvbt2_GetT2CarrierPresent(WINDOWID, &retval);

		TraceNotice(m,"%s %d retval %d mNumPLPIds %d", __FUNCTION__, __LINE__, retval, mNumPLPIds);
    
		
		if( (ret == TRUE) || (mNumPLPIds >= 1) )
		{
			retval = TRUE;
		}
	}
	TraceNotice(m, "T2 Detected %d ", retval);
    return retval;
}

void CHsvDvbTInstallation_mQuick_Priv::FuncOnHierarchyModeDetected(Nat32 param)
{
    Nat32 errorcode = TM_OK;
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
                {
                    tmFe_StreamPriority_t StreamPriority;
                    feapi_GetStreamPriority(WINDOWID, &StreamPriority, &errorcode);
                    ASSERT(TM_OK  ==  errorcode);
                    mInstStatus.HierarchyMode = TRUE;
                    if(StreamPriority == tmFe_StreamPriorityLow)
                    {
                        mInstStatus.HierarchyMode = FALSE;
                    }
                }
                break;
        }
    }
}

void CHsvDvbTInstallation_mQuick_Priv::mSetHierarchyMode(void)
{
    Nat32 errorcode = TM_OK;
    tmFe_StreamPriority_t StreamPriority;
    feapi_GetStreamPriority(WINDOWID, &StreamPriority, &errorcode);
	TraceNotice(m,"%s: Stream priority : %d",__FUNCTION__,StreamPriority);
    ASSERT(TM_OK  ==  errorcode);
    mInstStatus.HierarchyMode = TRUE;
    if(StreamPriority == tmFe_StreamPriorityLow)
    {
        mInstStatus.HierarchyMode = FALSE;
    }
}


int CHsvDvbTInstallation_mQuick_Priv::mWaitForData(void)
{
	int retval = idvbtqctrlN_DataAvailable;
	if(MANUAL_INSTALL)
	{
		if( (rins_GetMedium() == rins_Cable) && (eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite) )
		{
			retval = idvbtqctrlN_SiDataAvailable;
		}
	}
	return retval;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickpow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbtins_mQuick" );
    mConstModuleLifeCycle = ConstInitialised;
    TraceDebug(m,"%s %d TURNED_ON %d mPump %d", __FUNCTION__, __LINE__, TURNED_ON,mPump);
}

void CHsvDvbTInstallation_mQuick_Priv::iquickpow_TurnOn(void)
{
    mConstModuleLifeCycle = ConstTurnedOn;
    mInitialise(START_FREQUENCY);   // Naresh: guess this is not reqd, correct me
}
void CHsvDvbTInstallation_mQuick_Priv::iquickpow_TurnOff(void)
{

}

FResult CHsvDvbTInstallation_mQuick_Priv::iquick_StartInstallation(int source, int ptc, int mode)
{
    FResult retval = 0;
    UNUSED(ptc);

    TraceNotice(m,"%s %d source %d mode %d TURNED_ON %d", __FUNCTION__, __LINE__, source, mode, TURNED_ON);
    if(TURNED_ON)
    {
        if(VALID_SOURCE(source) && VALID_INSTALL_MODE(mode))
        {
            pmp_PmpSend(mPump, ConstEvStart, (Nat32)NULL);
        }
    }
    return retval;
}

FResult CHsvDvbTInstallation_mQuick_Priv::iquick_StopInstallation(void)
{
    FResult retval = err_Ok;

    TraceNotice(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
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

void CHsvDvbTInstallation_mQuick_Priv::iquick_GetPTCInfo(HsvInstallationPTC *ptc)
{
    int PLPId, PlfParam1;
    Nat32 errorcode = TM_OK;
    feapi_GetFreq(WINDOWID, &mInstStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode);
	ptc->NITVersion  		= 	-1;
    ptc->Frequency          =   mInstStatus.Frequency;
	ptc->Frequency = (ptc->Frequency * 1000)/16;
	/*For background installation take the frequency without conversion from Java*/
	if(rins_GetInstallationMode() == rins_InstallationModeBackground)
	{
	    feapi_GetCarrierFreq(WINDOWID,0,(tmFe_ChanTable_t)0,&mInstStatus.Frequency, &errorcode);
		ptc->Frequency = mInstStatus.Frequency;
	}
    ptc->IqMode             =   HsvIqModeNormal;
    ptc->SymbolRate         =   0;
	ptc->VSignalStrength 	= 	sigstr_GetActualSignalStrength(rins_InsVssm, 0);
	ptc->ASignalStrength 	= 	sigstr_GetActualSignalStrength(rins_InsAssm, 0);
	ptc->QSignalStrength 	= 	sigstr_GetActualSignalStrength(rins_InsQssm, 0);

	TraceNotice (m, "SignalStrength V %d A %d Q %d ", ptc->VSignalStrength, ptc->ASignalStrength, ptc->QSignalStrength);
    ptc->FrequencyError = ptc->TimeError = ptc->ChannelInformation = ptc->CodeRateHigh = ptc->CodeRateLow = ptc->TxMode = ptc->GuardInterval = 0;
    ptc->FrequencyOffset = ptc->SymbolRate = ptc->HierarchyMode = 0;

    feapi_GetActualConstellation (WINDOWID, feapi_ChanDecDvbT, (tmFe_Constellation_t*) (&PlfParam1), &errorcode);
    ASSERT(TM_OK  ==  errorcode);
    ptc->ModulationType     =   PlfParam1; //ConvertFromPlatformConstellation((tmFe_Constellation_t)PlfParam1);

    feapi_GetActualChanBandwidth (WINDOWID, (tmFe_ChanBandwidth_t* ) (&PlfParam1), &errorcode);
    ASSERT(TM_OK  ==  errorcode);
    ptc->ChannelBandwidth   =  PlfParam1;// (HsvChanBandwidth)ConvertFromPlatformChanBandwidth((tmFe_ChanBandwidth_t)PlfParam1);
	TraceNotice (m, "In DVBTQuick Bandwidth value is %d ", ptc->ChannelBandwidth);
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

        TraceNotice(m,"@ %d Frequency %d PlfParam1 %d errorcode %d ptc->StreamPriority %d", __LINE__, (int)ptc->Frequency, PlfParam1, (int)errorcode, ptc->StreamPriority);
    }


}

void CHsvDvbTInstallation_mQuick_Priv::iquick_SyncComplete(void)
{
    if(TURNED_ON)
    {
        TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
        idvbset_CommitPreferred();
        insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
    }
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnStationFound()
{
    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {
        pmp_PmpSend( mPump, ConstEvStationFound, (Nat32)NULL);
    }
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnStationNotFound()
{
    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {       
        pmp_PmpSend( mPump, ConstEvStationNotFound, (Nat32)NULL);
    }
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnMeasReady( int ssm, Nat32 strength )
{
    UNUSED(strength);

    if(TURNED_ON)
    {
		pmp_PmpSend( mPump, ConstEvOnMeasReady, (Nat32)ssm);
	}
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode )
{
    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);

    if(TURNED_ON)
    { 
        pmp_PmpSend( mPump, ConstEvHierarchyModeDetected, (Nat32)mode);


    }
}

void CHsvDvbTInstallation_mQuick_Priv::iqctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(value);
    TraceNotice(m,"%s %d eventid %d TURNED_ON %d", __FUNCTION__, __LINE__, eventid,TURNED_ON);
    if(TURNED_ON && (rins_GetInstallationState() == rins_StDigital) && (mInstStatus.State != ConstStIdle) )
    {
        TraceNotice(m,"%s %d eventid %d", __FUNCTION__, __LINE__, eventid);
        switch(eventid)
        {
            case iqctrlN_DataAvailable:
                mInstStatus.SdmData = ACQUISITION_COMPLETED;
                if(sigstr_GetSigStrengthMeasured() == TRUE)
                {   
                    pmp_PmpSend(mPump, ConstEvDataAvailable, (Nat32)NULL);
                }
                break;
            case iqctrlN_DataNotAvailable:
                mInstStatus.SdmData       = NO_DATA;
                mStopSdm(HsvDmxMain);
                break;
            case iqctrlN_StartedCollection:
                SET_INS_STATE(ConstStDemuxWait);
                break;

            case iqctrlN_StoppedCollection:
                TraceNotice(m,"%s %d eventid %d", __FUNCTION__, __LINE__, eventid);
                mInstStatus.SdmData       = NO_DATA; 
                pmp_PmpSend(mPump, ConstEvSdmStopped, (Nat32)NULL);
                break;

            case iqctrlN_SiDataAvailable:
                if(mWaitForData() == iqctrlN_SiDataAvailable)
                {
                    mInstStatus.SdmData = ACQUISITION_COMPLETED;
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


int CHsvDvbTInstallation_mQuick_Priv::iquick_GetPLPIds(int *PLPIds)
{
    UNUSED(PLPIds);
    return FALSE;
}

Bool CHsvDvbTInstallation_mQuick_Priv::iquick_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{
    UNUSED(ONID);
    UNUSED(TSID);    
    return FALSE;
}

void CHsvDvbTInstallation_mQuick_Priv::iquick_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


int CHsvDvbTInstallation_mQuick_Priv::iquick_GetNumberOfDigitalChannelsRemoved()
{    
    return FALSE;
}

FResult CHsvDvbTInstallation_mQuick_Priv::iquick_StoreWeakSignalInstallationChannel()
{    
    return FALSE;
}

FResult CHsvDvbTInstallation_mQuick_Priv::iquick_StartDigitalScan()
{    
    return FALSE;
}

void CHsvDvbTInstallation_mQuick_Priv::iquick_ClearCache()
{

}

int CHsvDvbTInstallation_mQuick_Priv::iquick_GetNoOfPass()
{    
    return FALSE;
}

Bool CHsvDvbTInstallation_mQuick_Priv::iquick_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{
    UNUSED(ONID);
    UNUSED(TSID);    
    return FALSE;
}

#ifndef __cplusplus

void CHsvDvbTInstallation_mQuick_Priv::iquick_StreamPriority (HsvStreamPriority prio)
{
    UNUSED(prio);    
}
#endif


FResult CHsvDvbTInstallation_mQuick_Priv::iquick_StartDigitalTuning(int frequency)
{   
    UNUSED(frequency);    
    return FALSE;
}

int CHsvDvbTInstallation_mQuick_Priv::iquick_GetCurrentPass()
{    
    return FALSE;
}

int CHsvDvbTInstallation_mQuick_Priv::iquick_GetNumberOfDigitalChannelsFound()
{
    return FALSE;
}

void CHsvDvbTInstallation_mQuick_Priv::iquick_Initialise()
{
    mInitialise(START_FREQUENCY);    
}

int CHsvDvbTInstallation_mQuick_Priv::iquick_GetSDTType()
{ 
    return FALSE;
}

int CHsvDvbTInstallation_mQuick_Priv::iquick_ZiggoGetSDTType(Nat16 Frequency)
{
    UNUSED(Frequency); 
    return FALSE;
}

void CHsvDvbTInstallation_mQuick_Priv::iquick_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    UNUSED(ptc);
    UNUSED(Onid);
    UNUSED(Tsid);
}

FResult CHsvDvbTInstallation_mQuick_Priv::iquick_StopDigitalScan()
{
 return FALSE;
}

int CHsvDvbTInstallation_mQuick_Priv::iquick_GetTargetNitType(Nat16* NetworkId)
{
    UNUSED(NetworkId); 
    return FALSE;
}

int CHsvDvbTInstallation_mQuick_Priv::iquick_GetCurrentState()
{
    return FALSE;
}

HsvHierarchyMode CHsvDvbTInstallation_mQuick_Priv::iquick_GetHierarchyMode(void)
{
    return (HsvHierarchyMode)0;
}

inline Nat16 CHsvDvbTInstallation_mQuick_Priv::mGetChannelDecoder(void)
{
    Nat16 retval = feapi_ChanDecDvbT;

    if(mScanPLPState == ConstStScanProgress)
    {
        retval = feapi_ChanDecDvbT2;
        TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    }
    else
    {
		/* means it is a non PLP DVBT/T2 case */
		if(mInstStatus.HierarchyMode == TRUE)
		{
			retval = feapi_ChanDecDvbT;
			TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
		}
		else if(eurdiv_IsDVBT2Supported())
        {
            retval = (feapi_ChanDecDvbT | feapi_ChanDecDvbT2);
            TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
        }
    }   
    return retval;
}

inline void CHsvDvbTInstallation_mQuick_Priv::mInitialiseDecoderParams(void)
{
    int i = 0;

    TraceDebug(m,"%s %d mCurrentDecoder %d mNumPLPIds %d mInstalledPLPIds %d", __FUNCTION__, __LINE__, mCurrentDecoder, mNumPLPIds, mInstalledPLPIds);

    mInstalledPLPIds          = 1;
    mCurrentDecoder           = 0xFFFF;
    mNumPLPIds                = 0;
    mScanPLPState             = ConstStIdle;
    mInstStatus.HierarchyMode = FALSE;

    for(i=0; i < MAX_PLP_IDS; i++)
    {
        mDetectedPlpIds[i] = -1;
    }
}

int CHsvDvbTInstallation_mQuick_Priv::mGetCorrectedFrequency(int Frequency, int Country)
{
    Bool FrequencyCorrected = FALSE;
    int i = 0, MinFreq, MaxFreq, NoofMatches = 0, FrequencyDiff = 0, UserFrequency, CorrectedFrequency, centrefrequency;

    MinFreq = MaxFreq = INVALID_FREQUENCY;
    UserFrequency = CorrectedFrequency = Frequency;
    HsvInstallationSpectrum *Spectrum = (HsvInstallationSpectrum *)((ANTENNA_MEDIUM)?AntennaSpectrum[Country]: CableSpectrum);

    while( (MinFreq = Spectrum[i].StartFrequency)!= INVALID_FREQUENCY )
    {
        MaxFreq    =   Spectrum[i].EndFrequency;
        CorrectedFrequency = UserFrequency;
        if ( MinFreq <= UserFrequency )
        {
            if( MaxFreq >= UserFrequency)
            {
                int bandbw      =   mConvertBandwidthToValue(Spectrum[i].Bandwidth) << 4;
                if((UserFrequency - MinFreq) % bandbw  > bandbw/2)
                {
                    CorrectedFrequency = UserFrequency + bandbw;
                }
                CorrectedFrequency = CorrectedFrequency - (UserFrequency-MinFreq) % bandbw;
                centrefrequency = UserFrequency + ((MaxFreq- UserFrequency) % bandbw) + bandbw/2;

                if ((centrefrequency + bandbw/2 == MaxFreq) && ((centrefrequency - bandbw) == MinFreq))
                {
                    CorrectedFrequency =  centrefrequency;
                }

                FrequencyCorrected = TRUE;
                NoofMatches++;
                if(NoofMatches == 1)
                {
                    FrequencyDiff = GET_ABSOLUTE_VAL (UserFrequency - CorrectedFrequency);
                    Frequency = CorrectedFrequency;
                }
                else
                {
                    if(FrequencyDiff > GET_ABSOLUTE_VAL(UserFrequency - CorrectedFrequency))
                    {
                        FrequencyDiff = GET_ABSOLUTE_VAL(UserFrequency - CorrectedFrequency);
                        Frequency = CorrectedFrequency;
                    }
                }
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
        if( Spectrum[i].StartFrequency == INVALID_FREQUENCY)
        {
            Frequency = Spectrum[i - 1].EndFrequency;
        }
        else
        {
            Frequency = Spectrum[i].StartFrequency;
        }
    }
    TraceNotice(m,"%s %d Frequency %d", __FUNCTION__, __LINE__, Frequency);
    return Frequency;
}

int CHsvDvbTInstallation_mQuick_Priv::mConvertBandwidthToValue(tmFe_ChanBandwidth_t Bandwidth)
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


HsvStreamPriority CHsvDvbTInstallation_mQuick_Priv::iquick_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}

void CHsvDvbTInstallation_mQuick_Priv::iquick_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvDvbTInstallation_mQuick_Priv::iquick_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}


void CHsvDvbTInstallation_mQuick_Priv::iquick_ClearPersistent() 
{
	return;
}
/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnSearchStateChanged (  tmFe_SearchState_t state  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnSearchInProgress (  tmFe_SearchState_t state  )   
{
	return;
}


void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnTvSystemDetected (  tmFe_TvSystem_t tvSystem  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnAfcFreqChanged (  Nat32 freq  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnAfcLimitReached ( Nat32 freq  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnAfcModeChanged (  void  )   
{
	return;
}



void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnMeasAborted (  int ssm  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnConstellationDetected (tmFe_Constellation_t  ellation)
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnIqModeDetected (  tmFe_IqMode_t mode  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnCodeRateDetected (  tmFe_CodeRate_t highPrioRate ,  tmFe_CodeRate_t lowPrioRate  )   
{
	return;
}


void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnGuardIntervalDetected (  tmFe_GuardInterval_t interval  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnTxModeDetected (  tmFe_TxMode_t mode  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnChanBandwidthDetected (  tmFe_ChanBandwidth_t bandwith  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnCarrierPresentChanged (  Bool carrier  )   
{
	return;
}

void CHsvDvbTInstallation_mQuick_Priv::iquickfeN_OnBerThresholdCrossed (  Nat32 ber ,  Nat32 berThreshold  )   
{
	return;
}

