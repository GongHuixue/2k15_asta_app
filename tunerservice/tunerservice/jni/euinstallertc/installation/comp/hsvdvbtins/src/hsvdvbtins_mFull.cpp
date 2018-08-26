
#include "_hsvdvbtins_mFull.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbtins_mFull")


#ifndef __cplusplus

#include "../type/InstallationConstants.h"

#else

#include "InstallationConstants.h"

#endif

#include "plftoMWconstantsWrapper.h"



#ifndef __cplusplus

#else

#endif




int CHsvDvbTInstallation_mFull_Priv::s__mScanPLPState,CHsvDvbTInstallation_mFull_Priv::s__mInstalledPLPIds,CHsvDvbTInstallation_mFull_Priv::s__mDetectedPlpIds[MAX_PLP_IDS],CHsvDvbTInstallation_mFull_Priv::s__mNumPLPIds;

Nat16 CHsvDvbTInstallation_mFull_Priv::s__mCurrentDecoder;


















/* static variables */



const FunctionNat32 CHsvDvbTInstallation_mFull_Priv::EventActionMatrix[][10] =
{
    									/*  ConstStIdle,		           ConstStScanProgress,  		ConstStTunerWait,     					ConstStDemuxWait        				*/
    /* ConstEvStart */             		{  	FNADDR(FuncStartInstallation), NULL,                 		NULL,                 					NULL                   					},
    /* ConstEvStop */              		{  	NULL,       		           FNADDR(FuncStopInstallation),FNADDR(FuncStopInstallation), 			FNADDR(FuncStopInstallation)   			},
    /* ConstEvSdmStopped */        		{  	NULL,               		   FNADDR(FuncSdmStopped),      NULL,                 					FNADDR(FuncSdmStopped)         			},
    /* ConstEvDataAvailable */     		{  	NULL,                 		   NULL,                 		NULL,                 					FNADDR(FuncDataAvailable)      			},
    /* ConstEvStationFound */      		{  	NULL,                  		   NULL,                 		FNADDR(FuncStationFound),     			NULL                   					},
    /* ConstEvStationNotFound */   		{  	NULL,                  		   NULL,                 		FNADDR(FuncStationNotFound),  			NULL                   					},
    /* ConstEvMakeDecision */      		{  	NULL,			               FNADDR(FuncMakeDecision),    NULL,                 					NULL                   					},
    /* DummyEvent */            		{  	NULL,                     	   NULL,                       	NULL,                     				NULL                      				},
    /* ConstEvHierarchyModeDetected */  {	NULL,                          NULL,                       	FNADDR(FuncOnHierarchyModeDetected), 	FNADDR(FuncOnHierarchyModeDetected)		},
	/* ConstEvOnMeasReady */       		{  	NULL,                  		   NULL,                 		FNADDR(FuncOnMeasReady),				FNADDR(FuncOnMeasReady)		  		 	},
	/* ConstEvPMTCollected */           {   NULL,                     	   NULL,                       	NULL,                     				NULL                      				}    
};


void CHsvDvbTInstallation_mFull_Priv::ifull_SetStreamPriority(HsvStreamPriority prio)
{
    UNUSED(prio);
    TraceNotice(m," Stubbed ifull_SetStreamPriority called "); 
}

void CHsvDvbTInstallation_mFull_Priv::PumpHandler(int event, Nat32 param)
{
    UNUSED(param);
    TraceDebug(m,"%s %d event %d mInstStatus.State %d", __FUNCTION__, __LINE__, event, mInstStatus.State);
    if(VALID_EVENT(event) && VALID_STATE(mInstStatus.State))
    {
        TraceDebug(m,"%s %d event %d mInstStatus.State %d", __FUNCTION__, __LINE__, event, mInstStatus.State);
        if(EventActionMatrix[event][mInstStatus.State] != NULL)
        {
            TraceDebug(m,"%s %d event %d mInstStatus.State %d", __FUNCTION__, __LINE__, event, mInstStatus.State);
            FPCALL(EventActionMatrix[event][mInstStatus.State])(param);
        }
    }
}

void CHsvDvbTInstallation_mFull_Priv::FuncStartInstallation(Nat32 param)
{
    TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
	int start_frequency=START_FREQUENCY;
	switch(COUNTRY)
	  {
		case cids_CountryAustralia:
		case cids_CountrySingapore:
		case cids_CountryMalaysia:	
		  start_frequency=START_FREQUENCY_44MHZ;
		  break;
		case cids_CountryThailand:
		case cids_CountryNewZealand:
		case cids_CountryTaiwan:	
		  start_frequency=START_FREQUENCY_470MHZ;
		  break;
		case cids_CountryIndonesia: 
		case cids_CountryVietnam:
		  start_frequency=START_FREQUENCY_174MHZ;
		  break;
		default:
		  start_frequency=START_FREQUENCY;
		  break;
	  }  
    mInitialise(start_frequency);
    mctl_Stop(HsvMain);

    SET_INS_STATE(ConstStScanProgress);
    mStopSdm(HsvDmxMain);
    UNUSED(param);
}

void CHsvDvbTInstallation_mFull_Priv::FuncStopInstallation(Nat32 param)
{
    tmErrorCode_t errorcode;
	int start_frequency=START_FREQUENCY;
    TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
    SET_INS_STATE(ConstStIdle);

    feapi_StopSearch(WINDOWID, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    sigstr_StopSigStrMeasAll();
    mStopSdm(HsvDmxMain);
	switch(COUNTRY)
	  {
		case cids_CountryAustralia:
		case cids_CountrySingapore:
		case cids_CountryMalaysia:	
		  start_frequency=START_FREQUENCY_44MHZ;
		  break;
		case cids_CountryThailand:
		case cids_CountryNewZealand:
		case cids_CountryTaiwan:	
		  start_frequency=START_FREQUENCY_470MHZ;
		  break;
		case cids_CountryIndonesia: 
		case cids_CountryVietnam:
		  start_frequency=START_FREQUENCY_174MHZ;
		  break;
		default:
		  start_frequency=START_FREQUENCY;
		  break;
	  }  
    mInitialise(start_frequency);
    insN_OnEvent(insN_EventInstallationStopped, rins_GetInstallationMode());
    UNUSED(param);
}

void CHsvDvbTInstallation_mFull_Priv::FuncSdmStopped(Nat32 param)
{
    if(mInstStatus.State == ConstStScanProgress)
    {
        TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
        mSetChannelDecoderAttributes();
        mSetTunerAttributes();
    }
    else
    {
        TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
        SET_INS_STATE(ConstStScanProgress);
        pmp_PmpSend(mPump, ConstEvMakeDecision, (Nat32)NULL);       
    }
    UNUSED(param);
}

void CHsvDvbTInstallation_mFull_Priv::FuncStationFound(Nat32 param)
{
    Nat32 errorcode;
	Bool HierarchialMuxPresent = FALSE;
	int TempPlpIds[MAX_PLP_IDS];
    feapi_GetFreq(WINDOWID, &mInstStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode );

    if(mIsDvbt2CarrierDetected() == TRUE)
    {


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
			
			if(mNumPLPIds > MAX_PLP_IDS)
			{
				mNumPLPIds = MAX_PLP_IDS;
			}
            /* set PLP state */
            mScanPLPState = ConstStScanProgress;

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
    //sigstr_StartSigStrMeasAll();

    /* start sdm collection with appropriate mode */
    ctrl_StartCollection(HsvDmxMain, ctrl_Normal);  
    UNUSED(param);
}

void CHsvDvbTInstallation_mFull_Priv::FuncStationNotFound(Nat32 param)
{
    Nat32 errorcode;
    feapi_GetFreq(WINDOWID, &mInstStatus.Frequency, &errorcode);

    ASSERT(TM_OK  ==  errorcode );

    TraceNotice(m,"%s %d mInstStatus.HierarchyMode %d", __FUNCTION__, __LINE__, mInstStatus.HierarchyMode);

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

void CHsvDvbTInstallation_mFull_Priv::FuncDataAvailable(Nat32 param)
{
    TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
    idataacq_AcquireData();
    /* ntf to apps, to query for num of channels */
    insN_OnEvent(insN_EventChannelFound, CURRENT_MODE);

    mStopSdm(HsvDmxMain);
    UNUSED(param);
}

void CHsvDvbTInstallation_mFull_Priv::FuncMakeDecision(Nat32 param)
{
    Nat32 StartFrequency = 0, EndFrequency = 0, errorcode = 0;

    mGetBandScan(&StartFrequency, &EndFrequency);
    /* 2nd check - to take care of heirarchy for the last MUX boundary case */
    if( ( (mInstStatus.Frequency >> 4) < ((EndFrequency >> 4) - 7) ) || 
            ( (mInstStatus.HierarchyMode == TRUE) && (mAllMUXsInHierarchyScanned() == FALSE) ) )
    {
        TraceDebug(m,"%s %d mInstStatus.State %d Frequency %d EndFrequency %d", __FUNCTION__, __LINE__, mInstStatus.State, (int)mInstStatus.Frequency, (int)EndFrequency);
        mStopSdm(HsvDmxMain);
    }
    else
    {                
        TraceDebug(m,"%s %d mInstStatus.State %d Frequency %d EndFrequency %d", __FUNCTION__, __LINE__, mInstStatus.State, (int)mInstStatus.Frequency, (int)EndFrequency);
        SET_INS_STATE(ConstStIdle);
        feapi_StopSearch(WINDOWID, &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        mStopSdm(HsvDmxMain);
        sigstr_StopSigStrMeasAll();
        TraceDebug(m,"%s %d Scan completed", __FUNCTION__, __LINE__);
        idataacq_SyncTemporaryTableRecords();
    }
    UNUSED(param);
}
void CHsvDvbTInstallation_mFull_Priv::FuncOnHierarchyModeDetected(Nat32 param)
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
                if(mIsDvbt2CarrierDetected() == FALSE)
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

void CHsvDvbTInstallation_mFull_Priv::FuncOnMeasReady(Nat32  param)
{
	if(sigstr_GetSigStrengthMeasured() == TRUE)
    {
        TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
        /*if sdm data available -> Acquire & process it now */
        if(mInstStatus.SdmData == ACQUISITION_COMPLETED)
        {
            TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
            pmp_PmpSend(mPump, ConstEvDataAvailable, (Nat32)NULL);
        }
    }
	UNUSED(param);
}

void CHsvDvbTInstallation_mFull_Priv::mInitialise(Nat32 freq)
{
    SET_INS_STATE(ConstStIdle);
    mInstStatus.SdmData       = NO_DATA;
    mInstStatus.HierarchyMode = FALSE;
    mInstStatus.Frequency     = freq;

    mInitialiseDecoderParams();
    idataacq_Initialise();
}
void CHsvDvbTInstallation_mFull_Priv::mStopSdm(HsvDemux dmx)
{
    if(ctrl_GetMode(dmx) == ctrl_Idle)
    {
        TraceDebug(m,"%s %d mInstStatus.State %d Frequency %d", __FUNCTION__, __LINE__, mInstStatus.State, (int)mInstStatus.Frequency);
        pmp_PmpSend(mPump, ConstEvSdmStopped, (Nat32)NULL);
    }
    else
    {
        TraceDebug(m,"%s %d mInstStatus.State %d Frequency %d", __FUNCTION__, __LINE__, mInstStatus.State,(int)mInstStatus.Frequency);
        ctrl_StopCollection(dmx);
    }
}

void CHsvDvbTInstallation_mFull_Priv::mSetChannelDecoderAttributes(void)
{
    Nat32 errorcode = TM_OK;
    Nat16 Decoder = mGetChannelDecoder();

    TraceDebug(m,"%s %d mCurrentDecoder %d Decoder %d", __FUNCTION__, __LINE__, mCurrentDecoder, Decoder);

    if(mCurrentDecoder != Decoder)
    {
        mCurrentDecoder = Decoder;

        TraceDebug(m,"%s %d mCurrentDecoder %d", __FUNCTION__, __LINE__, mCurrentDecoder);
    }
		/*As per discussion with Pavan,HK,sachin use odd combination of BW for 1MHZ step size
		for scan of 8Mhz or 7Mhz.  we are using auto BW that do scan for 7 then 8 MHz */
	switch(COUNTRY)
	{
		case cids_CountryTaiwan:		
		case cids_CountryIndonesia:
			feapi_SetChanBandwidth(WINDOWID, tmFe_ChanBandwidth_6_7_8MHz, &errorcode);
			break;
		default:
    		feapi_SetChanBandwidth(WINDOWID, tmFe_ChanBandwidthAuto, &errorcode); 
			break;
	}		
    ASSERT(TM_OK == errorcode);
}

void CHsvDvbTInstallation_mFull_Priv::mSetTunerAttributes(void)
{
    int HeirarchyValue = 0;
    Bool  HierarchyMode = mInstStatus.HierarchyMode;
    Nat32 Frequency = 0, StartFrequency = 0, EndFrequency = 0, errorcode = 0;

    /* This function sets current tuned frequency - heirarchyMode(DVBT/DVBT2)
       else sets start frequency in the band intially - non-heirarchyMode(DVBT/DVBT2) */
    mGetBandScan(&StartFrequency, &EndFrequency);

    Frequency = (HierarchyMode || (mInstStatus.Frequency > StartFrequency))? mInstStatus.Frequency: StartFrequency;
    TraceDebug(m,"%s %d Freq %d StartFreq %d EndFreq %d", __FUNCTION__, __LINE__, (int)Frequency,(int) StartFrequency, (int)EndFrequency);

    mGetHierarchyMUX(&HeirarchyValue);
    mSetHeirarchyMux(HeirarchyValue);
	/* ANEESH: Adding the below HierarchMode setting. InSide mGetHierarchyMux reset of 
		InstStatus.HierarchigMode is done when all the PLPs are collected */
	TraceNotice (m, "ANEESH: HierarchyMode old val %d new val %d ", HierarchyMode, mInstStatus.HierarchyMode);
	HierarchyMode = mInstStatus.HierarchyMode;
    mInstStatus.HierarchyMode = FALSE;  //reset before setfreq, just in case plf ntf.. comes syncronously   
    SET_INS_STATE(ConstStTunerWait);

    /* setfreq is done in 1. Initial case to set freq.
       2. heirarchy MUX to install other MUXs transmitted @ same frequency.
       after this its only startsearch to be called to continue band scan */
    if(/* (Frequency <= StartFrequency) || */HierarchyMode)
    {
		/* ANEESH: Changed for T2 */
        TraceDebug(m,"%s %d SetFreq %d", __FUNCTION__, __LINE__, (int)Frequency);
        feapi_SetFreq(WINDOWID, Frequency, FALSE, &errorcode);
        ASSERT(TM_OK == errorcode);
    }

    if(HierarchyMode == FALSE)
    {
        TraceDebug(m,"%s %d feapi_StartSearch called mInstStatus.State %d Frequency %d", __FUNCTION__, __LINE__, mInstStatus.State, (int)mInstStatus.Frequency);
        /* do this only in case of non-heirarchy mode, as in other case, we have to still 
           install the other MUXs transmitted in current frequency */
        feapi_StartSearch(WINDOWID, mInstStatus.Frequency, tmFe_SmDefault, EndFrequency, &errorcode);/* ANEESH: TODO: Cnfirm this change */
        ASSERT(TM_OK == errorcode);
    }
}

void CHsvDvbTInstallation_mFull_Priv::mGetBandScan(Nat32 *StartFrequency, Nat32 *EndFrequency)
{
    Nat32 errorcode = TM_OK;
	int start_frequency;
    feapi_GetFreqRange(WINDOWID, StartFrequency, EndFrequency, &errorcode);
    ASSERT(errorcode == TM_OK);
	switch(COUNTRY)
	  {
		case cids_CountryAustralia:
		case cids_CountrySingapore:
		case cids_CountryMalaysia:	
		  start_frequency=START_FREQUENCY_44MHZ;
		  break;
		case cids_CountryThailand:
		case cids_CountryNewZealand:
		case cids_CountryTaiwan:	
		  start_frequency=START_FREQUENCY_470MHZ;
		  break;
		case cids_CountryIndonesia: 
		case cids_CountryVietnam:
		  start_frequency=START_FREQUENCY_174MHZ;
		  break;
		default:
		  start_frequency=START_FREQUENCY;
		  break;
	  }

    if(*StartFrequency < start_frequency)
    {
        ASSERT(FALSE);
        *StartFrequency = start_frequency;
    }   
    if(*EndFrequency > END_FREQUENCY)
    {
        ASSERT(FALSE);
        *EndFrequency = END_FREQUENCY;
    }
}

void CHsvDvbTInstallation_mFull_Priv::mGetHierarchyMUX(int *HierarchyValue)
{
    Nat32 errorcode;
    int i = 0, temp = 0, Active_PlpId;

    TraceDebug(m,"%s %d mScanPLPState %d", __FUNCTION__, __LINE__, mScanPLPState);
    if(mScanPLPState == ConstStScanProgress)
    {
        /* This means PLPId is in progress */
        *HierarchyValue = chdecdvbt2_PlpIdAuto;

        chdecdvbt2_GetActivePlpId (WINDOWID, &Active_PlpId);

        TraceDebug(m,"%s %d Active PlpId %d", __FUNCTION__, __LINE__, Active_PlpId);
        for (i = 0; i < mNumPLPIds; i++)
        {
            TraceDebug(m,"%s %d mDetectedPlpIds[%d] %d", __FUNCTION__, __LINE__, i, mDetectedPlpIds[i]);
            if(mDetectedPlpIds[i] == Active_PlpId)
            {
                TraceDebug(m,"mInstalledPLPIds %d NumPlpIds %d", mInstalledPLPIds, mNumPLPIds);
                if(mInstalledPLPIds < mNumPLPIds)
                {
                    /* ensure swap is done only in initial case, 2nd check will ensure that */
                    if( (i != 0) && (mInstalledPLPIds == 1) )
                    {
                        TraceDebug(m,"Swap mDetectedPlpIds[0] %d & mDetectedPlpIds[%d] %d", mDetectedPlpIds[0], i, mDetectedPlpIds[i]);
                        temp = mDetectedPlpIds[i];
                        mDetectedPlpIds[i] = mDetectedPlpIds[0];
                        mDetectedPlpIds[0] = temp;
						i = 0;
                    }
                    *HierarchyValue =   mDetectedPlpIds [i + 1];
                    mInstalledPLPIds++;
                }
				else
				{
					TraceNotice (m, "ANEESH: DVBT2: Completed with all the PLPIDs ");
					/* ANEESH: Finished scanning all PLP IDs. Now time to reset the hierarchical mux variables */
					mInitialiseDecoderParams ();
				}
                break;
                TraceDebug(m,"   : %d %s mDetectedPlpIds [i + 1] = %d ", __LINE__, __FUNCTION__, mDetectedPlpIds [i + 1]);
            }

        }
        TraceDebug(m," : %s %d *HierarchyValue %d\r", __FUNCTION__, __LINE__, *HierarchyValue);
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

    TraceDebug(m,"%s %d *HierarchyValue %d", __FUNCTION__, __LINE__, *HierarchyValue);
}

Bool CHsvDvbTInstallation_mFull_Priv::mAllMUXsInHierarchyScanned(void)
{
    Nat32 errorcode;
    Bool retval = TRUE;

    TraceDebug(m,"%s %d mScanPLPState %d", __FUNCTION__, __LINE__, mScanPLPState);
    if(mScanPLPState == ConstStScanProgress)
    {
        if(mInstalledPLPIds < mNumPLPIds)
        {
            retval = FALSE;
        }
        else
        {
            mInitialiseDecoderParams();
        }
        TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
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

    TraceDebug(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}

void CHsvDvbTInstallation_mFull_Priv::mSetHeirarchyMux(int HeirarchyValue)
{
    Nat32 errorcode;

    TraceDebug(m,"%s %d mCurrentDecoder %d", __FUNCTION__, __LINE__, mCurrentDecoder);

    if(mCurrentDecoder == feapi_ChanDecDvbT2)
    {
        errorcode = chdecdvbt2_SelectPlpId(WINDOWID, HeirarchyValue);   
        TraceDebug(m,"%s %d chdecdvbt2_SelectPlpId called, PlpId %d errorcode %d", __FUNCTION__, __LINE__, HeirarchyValue, (int)errorcode);
    }
    else
    {
        feapi_SetStreamPriority(WINDOWID, (tmFe_StreamPriority_t)HeirarchyValue, &errorcode);
        ASSERT(TM_OK == errorcode);
        TraceDebug(m,"%s %d HeirarchyValue %d errorcode %d", __FUNCTION__, __LINE__, HeirarchyValue, (int)errorcode);
        /* Set PLPId to Auto in case of T2 | T decoder */
        //errorcode = chdecdvbt2_SelectPlpId(WINDOWID, chdecdvbt2_PlpIdAuto);
        TraceDebug(m,"%s %d HeirarchyValue %d errorcode %d", __FUNCTION__, __LINE__, HeirarchyValue, (int)errorcode);
    }
}

inline Bool CHsvDvbTInstallation_mFull_Priv::mIsDvbt2CarrierDetected(void)
{
    FResult ret;
	Nat32 Decoder;
    Bool retval = FALSE;

	if(eurdiv_IsDVBT2Supported())
	{
		ret = chdecdvbt2_GetT2CarrierPresent(WINDOWID, &retval);

		TraceDebug(m,"%s %d retval %d ret %d ", __FUNCTION__, __LINE__, retval,ret);
		if( (ret == TRUE) || (mNumPLPIds >= 1) )
		{
			retval = TRUE;
		}
	}
    return retval;
}

void CHsvDvbTInstallation_mFull_Priv::mSetHierarchyMode(void)
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

int CHsvDvbTInstallation_mFull_Priv::mWaitForData(void)
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


void CHsvDvbTInstallation_mFull_Priv::ifullpow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, PumpHandler, FALSE,"hsvdvbtins_mFull" );
    mConstModuleLifeCycle = ConstInitialised;
}

void CHsvDvbTInstallation_mFull_Priv::ifullpow_TurnOn(void)
{
    mConstModuleLifeCycle = ConstTurnedOn;
	int start_frequency=START_FREQUENCY;
	switch(COUNTRY)
	  {
		case cids_CountryAustralia:
		case cids_CountrySingapore:
		case cids_CountryMalaysia:	
		  start_frequency=START_FREQUENCY_44MHZ;
		  break;
		case cids_CountryThailand:
		case cids_CountryNewZealand:
		case cids_CountryTaiwan:	
		  start_frequency=START_FREQUENCY_470MHZ;
		  break;
		case cids_CountryIndonesia: 
		case cids_CountryVietnam:
		  start_frequency=START_FREQUENCY_174MHZ;
		  break;
		default:
		  start_frequency=START_FREQUENCY;
		  break;
	  }

    mInitialise(start_frequency);// Naresh: guess this is not reqd, correct me
}
void CHsvDvbTInstallation_mFull_Priv::ifullpow_TurnOff(void)
{
    ASSERT(!"Not Implemented here");
}

FResult CHsvDvbTInstallation_mFull_Priv::ifull_StartInstallation(int source, int ptc, int mode)
{
    UNUSED(ptc);
    FResult retval = 0;

    TraceDebug(m,"%s %d source %d mode %d", __FUNCTION__, __LINE__, source, mode);
    if(TURNED_ON)
    {
        if(VALID_SOURCE(source) && VALID_INSTALL_MODE(mode))
        {
            TraceDebug(m,"%s %d mInstStatus.State %d", __FUNCTION__, __LINE__, mInstStatus.State);
            pmp_PmpSend(mPump, ConstEvStart, (Nat32)NULL);
        }
    }
    return retval;
}

FResult CHsvDvbTInstallation_mFull_Priv::ifull_StopInstallation(void )
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

void CHsvDvbTInstallation_mFull_Priv::ifull_SyncComplete(void)
{
    if(TURNED_ON)
    {
        TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
        idvbset_CommitPreferred();
        insN_OnEvent(insN_EventInstallationCompleted, CURRENT_MODE);
    }
}

void CHsvDvbTInstallation_mFull_Priv::ifull_GetPTCInfo(HsvInstallationPTC *ptc)
{
    int PLPId, PlfParam1 ;
    Nat32 errorcode = TM_OK;
	ptc->NITVersion  		= 	-1;	
    ptc->Frequency          =   mInstStatus.Frequency;
	ptc->Frequency			=	(ptc->Frequency * 1000)/16;
    ptc->IqMode             =   HsvIqModeNormal;
    ptc->SymbolRate         =   0;
   
	ptc->VSignalStrength 	= 	sigstr_GetActualSignalStrength(rins_InsVssm, 0);
	ptc->ASignalStrength 	= 	sigstr_GetActualSignalStrength(rins_InsAssm, 0);
	ptc->QSignalStrength 	= 	sigstr_GetActualSignalStrength(rins_InsQssm, 0);
	

	feapi_GetActualConstellation (WINDOWID,feapi_ChanDecDvbT, (tmFe_Constellation_t*) (&PlfParam1), &errorcode );
    ASSERT(TM_OK  ==  errorcode);

    ptc->ModulationType     =  PlfParam1; //ConvertFromPlatformConstellation((tmFe_Constellation_t)PlfParam1);

    ptc->FrequencyError = ptc->TimeError = ptc->ChannelInformation = ptc->CodeRateHigh = ptc->CodeRateLow = ptc->TxMode = ptc->GuardInterval = 0;
    ptc->FrequencyOffset = ptc->SymbolRate = ptc->HierarchyMode = 0;    
	
	feapi_GetActualChanBandwidth (WINDOWID, (tmFe_ChanBandwidth_t* ) (&PlfParam1), &errorcode);
    ASSERT(TM_OK  ==  errorcode);
	
    ptc->ChannelBandwidth   =   PlfParam1;//ConvertFromPlatformChanBandwidth((tmFe_ChanBandwidth_t)PlfParam1);

    if(mIsDvbt2CarrierDetected() == TRUE)
    {
        ptc->DecoderType        =   feapi_ChanDecDvbT2;
        chdecdvbt2_GetActivePlpId(WINDOWID, &PLPId);
        ptc->StreamPriority     =   PLPId;

        TraceDebug(m,"@ %d PLPId %d ptc->StreamPriority %d", __LINE__, PLPId, ptc->StreamPriority);
    }
    else
    {
        ptc->DecoderType = feapi_ChanDecDvbT;
        feapi_GetStreamPriority ( WINDOWID, (tmFe_StreamPriority_t* ) (&PlfParam1), &errorcode);
        ASSERT(TM_OK  ==  errorcode);
        ptc->StreamPriority     =   ConvertFromPlatformStreamPriority((tmFe_StreamPriority_t)PlfParam1);

        TraceDebug(m,"@ %d Frequency %d PlfParam1 %d errorcode %d ptc->StreamPriority %d", __LINE__, (int)ptc->Frequency, PlfParam1, (int)errorcode, ptc->StreamPriority);
    }


}

int CHsvDvbTInstallation_mFull_Priv::ifull_GetPLPIds(int *PLPIds)
{
    UNUSED(PLPIds);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

Bool CHsvDvbTInstallation_mFull_Priv::ifull_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{
    UNUSED(ONID);
    UNUSED(TSID);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mFull_Priv::ifull_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}

int CHsvDvbTInstallation_mFull_Priv::ifull_GetNumberOfDigitalChannelsRemoved()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

FResult CHsvDvbTInstallation_mFull_Priv::ifull_StoreWeakSignalInstallationChannel()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

FResult CHsvDvbTInstallation_mFull_Priv::ifull_StartDigitalScan()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mFull_Priv::ifull_ClearCache()
{
    ASSERT(!"Not Implemented here");
}

int CHsvDvbTInstallation_mFull_Priv::ifull_GetNoOfPass()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

Bool CHsvDvbTInstallation_mFull_Priv::ifull_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{
    UNUSED(ONID);
    UNUSED(TSID);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

#ifndef __cplusplus

void CHsvDvbTInstallation_mFull_Priv::ifull_StreamPriority (HsvStreamPriority prio)
{
    UNUSED(prio);
    ASSERT(!"Not Implemented here");
}
#endif


FResult CHsvDvbTInstallation_mFull_Priv::ifull_StartDigitalTuning(int frequency)
{   
    UNUSED(frequency);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mFull_Priv::ifull_GetCurrentPass()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mFull_Priv::ifull_GetNumberOfDigitalChannelsFound()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mFull_Priv::ifull_Initialise()
{
	int start_frequency=START_FREQUENCY;
	switch(COUNTRY)
	  {
		case cids_CountryAustralia:
		case cids_CountrySingapore:
		case cids_CountryMalaysia:	
		  start_frequency=START_FREQUENCY_44MHZ;
		  break;
		case cids_CountryThailand:
		case cids_CountryNewZealand:
		case cids_CountryTaiwan:	
		  start_frequency=START_FREQUENCY_470MHZ;
		  break;
		case cids_CountryIndonesia: 
		case cids_CountryVietnam:
		  start_frequency=START_FREQUENCY_174MHZ;
		  break;
		default:
		  start_frequency=START_FREQUENCY;
		  break;
	  }  
		mInitialise(start_frequency);
    ASSERT(!"Not Implemented here");
}

int CHsvDvbTInstallation_mFull_Priv::ifull_GetSDTType()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mFull_Priv::ifull_ZiggoGetSDTType(Nat16 Frequency)
{
    UNUSED(Frequency);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mFull_Priv::ifull_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    UNUSED(ptc);
    UNUSED(Onid);
    UNUSED(Tsid);
}

FResult CHsvDvbTInstallation_mFull_Priv::ifull_StopDigitalScan()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mFull_Priv::ifull_GetTargetNitType(Nat16* NetworkId)
{
    UNUSED(NetworkId);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

int CHsvDvbTInstallation_mFull_Priv::ifull_GetCurrentState()
{
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnStationFound()
{
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {
        pmp_PmpSend( mPump, ConstEvStationFound, (Nat32)NULL);
    }
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnStationNotFound()
{
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {       
        pmp_PmpSend( mPump, ConstEvStationNotFound, (Nat32)NULL);
    }
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnMeasReady( int ssm, Nat32 strength )
{
    UNUSED(strength);
    
    if(TURNED_ON)
    {
		pmp_PmpSend( mPump, ConstEvOnMeasReady, (Nat32)ssm);
	}
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode )
{
    TraceNotice(m,"%s %d\n", __FUNCTION__, __LINE__);

    if(TURNED_ON)
    { 
        pmp_PmpSend( mPump, ConstEvHierarchyModeDetected, (Nat32)mode);


    }
}

void CHsvDvbTInstallation_mFull_Priv::ifctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    UNUSED(value);
    if(TURNED_ON && (rins_GetInstallationState() == rins_StDigital) && (mInstStatus.State != ConstStIdle))
    {
        TraceDebug(m,"%s %d eventid %d", __FUNCTION__, __LINE__, eventid);
        switch(eventid)
        {
            case ifctrlN_DataAvailable:
                mInstStatus.SdmData = ACQUISITION_COMPLETED;
                if(sigstr_GetSigStrengthMeasured() == TRUE)
                {   
                    pmp_PmpSend(mPump, ConstEvDataAvailable, (Nat32)NULL);
                }
                break;
            case ifctrlN_DataNotAvailable:
                mInstStatus.SdmData       = NO_DATA;
                mStopSdm(HsvDmxMain);
                break;
            case ifctrlN_StartedCollection:
                SET_INS_STATE(ConstStDemuxWait);
                break;

            case ifctrlN_StoppedCollection:
                mInstStatus.SdmData       = NO_DATA;
                pmp_PmpSend(mPump, ConstEvSdmStopped, (Nat32)NULL);
                break;

            case ifctrlN_SiDataAvailable:
                if(mWaitForData() == ifctrlN_SiDataAvailable)
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

HsvHierarchyMode CHsvDvbTInstallation_mFull_Priv::ifull_GetHierarchyMode(void)
{
    return (HsvHierarchyMode)0;
}

inline Nat16 CHsvDvbTInstallation_mFull_Priv::mGetChannelDecoder(void)
{
    Nat16 retval = feapi_ChanDecDvbT;

    if(mScanPLPState == ConstStScanProgress)
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

inline void CHsvDvbTInstallation_mFull_Priv::mInitialiseDecoderParams(void)
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


/* Interfaces from IHsvdigitalscan.id */






HsvStreamPriority CHsvDvbTInstallation_mFull_Priv::ifull_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}





void CHsvDvbTInstallation_mFull_Priv::ifull_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvDvbTInstallation_mFull_Priv::ifull_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}

void CHsvDvbTInstallation_mFull_Priv::ifull_ClearPersistent() 
{
	return;
}


/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}


void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}

void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnSearchInProgress( tmFe_SearchState_t state )
{
	return;
}
void CHsvDvbTInstallation_mFull_Priv::ifullfeN_OnMeasAborted( int ssm )
{
	return;
}



