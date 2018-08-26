/*****************************************************************************************
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V., All Rights Reserved.
 *
 *  This	source code and any compilation or derivative thereof is the proprietary
 *  information of Koninklijke Philips Electronics N.V. and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed under an Open
 *  Source License of any type without the expressed written permission of Koninklijke
 *  Philips Electronics N.V.
 *
 *  %name: hsvdvbcamins_mScan.cpp %
 *  %version:  TVG_Android_1 %
 *  %date_modified:  %
 *  %derived_by: anuma %
 *
 *****************************************************************************************/
 
/*****************************************************************************************
 * Include files
 *****************************************************************************************/
#include "CHsvDvbsOpProfile_mScan.h"


/*****************************************************************************************
 * Macros and types
 *****************************************************************************************/
TRACESYMBOL(m, "installation/hsvdvbsopprofile/hsvdvbsopprofile_mScan")


/*****************************************************************************************
 * Static variables
 *****************************************************************************************/
CHsvDvbsOpProfile_mScan::InstStatus CHsvDvbsOpProfile_mScan::mInstStatus;
CHsvDvbsOpProfile_mScan::CamDSDesc CHsvDvbsOpProfile_mScan::mCamDSDesc;
Pump CHsvDvbsOpProfile_mScan::mScanPump,CHsvDvbsOpProfile_mScan::mCamDataPump;
Op_ProfileStatusInfo CHsvDvbsOpProfile_mScan::mStatusInfo;
Op_ProfileTuneData *CHsvDvbsOpProfile_mScan::mTempTuneDataPtr = NULL;
Op_Search_Settings CHsvDvbsOpProfile_mScan::mSearchSettings;
Op_Tune_Status *CHsvDvbsOpProfile_mScan::mTempTuneReplyDataPtr = NULL;
CHsvDvbsOpProfile_mScan::ModuleLifeCycle CHsvDvbsOpProfile_mScan::mModuleLifeCycle = TurnedOff;


const CHsvDvbsOpProfile_mScan::FunctionNat32 CHsvDvbsOpProfile_mScan::EventActionMatrix[][StMax] =
{
/*                                  StIdle,    			StStart,               			StTunerWait,       				StStrapiWait,        		StAcquireWait                                     */
/* EvStart     		*/ {FNADDR(FuncStartServiceScan),	NULL,                         	NULL,                        	NULL,                      	NULL                           	},
/* EvStop          	*/ {NULL,                       	FNADDR(FuncStopServiceScan),	FNADDR(FuncStopServiceScan),  	FNADDR(FuncStopServiceScan),FNADDR(FuncStopServiceScan)    	},
/* EvStationFound  	*/ {NULL,                        	NULL,                        	FNADDR(FuncStationFound),      	NULL,                     	NULL                         	},
/* EvMakeDecision 	*/ {NULL,                         	NULL,                      		FNADDR(FuncMakeDecision),   	FNADDR(FuncMakeDecision), 	NULL                         	},
/* EvStartTuning	*/ {NULL,                        	NULL,                     		NULL,                     		FNADDR(FuncStartTuning),  	NULL                        	},
/* EvDataAvailable 	*/ {NULL,                         	NULL,                         	NULL,                       	FNADDR(FuncDataAvailable), 	NULL                        	},
/* EvCheckLock     	*/ {NULL,                         	NULL,                        	FNADDR(FuncCheckLockStatus), 	NULL,                    	NULL                          	},
/* EvDataAcquired  	*/ {NULL,                     		NULL,                         	NULL,                        	NULL,                  		FNADDR(FuncDataAcquired)    	},
/* EvDateTimeReceived*/ {NULL,							NULL,							FNADDR(FuncDateTimeReceived),	FNADDR(FuncDateTimeReceived),		FNADDR(FuncDateTimeReceived)	},
/* EvInstallComplete */   {NULL, 							NULL,							FNADDR(FuncInstallComplete),		FNADDR(FuncInstallComplete),		FNADDR(FuncInstallComplete)		}
};


/*****************************************************************************************
 * Private methods
 *****************************************************************************************/

void CHsvDvbsOpProfile_mScan::mScanPumpHandler(int event, Nat32 param)
{
    if(VALID_EVENT(event) && VALID_STATE(GET_INS_STATE))
    {
        TraceNotice (m, "@ %d event %d state %d - %s \n",  __LINE__, event, GET_INS_STATE, 
                                 (EventActionMatrix[event][GET_INS_STATE] == NULL) ? "Ignored" : "Handled");
        if (NULL != EventActionMatrix[event][GET_INS_STATE])
        {
            FPCALL(EventActionMatrix[event][GET_INS_STATE])(param);
        }
    }
}

void CHsvDvbsOpProfile_mScan::FuncStartServiceScan(Nat32 param)
{
    mGetLnbDetails(param);
    mInitialise();

    //SET_INS_MODE(AUTO_CAM_MODE);
    SET_INS_STATE(StStart);

    mStopSdm(HsvDmxMain);
    camnitena->Enable(HsvDmxMain);

    TraceNotice(m, "%s() : %d\n", __FUNCTION__, __LINE__);
    opins->RequestStatusInfo();

    insN->OnEvent(IHsvSatelliteInstallationNotify_EventPkgInstallStart, GET_INS_MODE);
}


void CHsvDvbsOpProfile_mScan::FuncStartTuning (Nat32 param)
{
    int ModlnStd = -1, IqMode = -1, Cookie = 0;
    int SymbolRate = 0, ModlnType = -1;
	int RollOff = -1, FEC = -1, Pilots = -1; 
    
    TraceNotice (m,"LNB Num %d LNB Type %d Freq %d Sym rate %d Pol %d", mInstStatus.LnbNumber,
                             mInstStatus.LnbType, mCamDSDesc.SatDesc[mCamDSDesc.currSdsdIndex].Frequency,
                             mCamDSDesc.SatDesc[mCamDSDesc.currSdsdIndex].SymbolRate, mCamDSDesc.SatDesc[mCamDSDesc.currSdsdIndex].Polarization);
    TraceNotice (m,"%s() : currSdsdIndex %d\n", __FUNCTION__, mCamDSDesc.currSdsdIndex);
    SET_INS_STATE(StTunerWait);
    satfeapi->SatelliteFrontEndTune(mInstStatus.LnbNumber, mInstStatus.LnbType, \
                                                    mCamDSDesc.SatDesc[mCamDSDesc.currSdsdIndex].Frequency, \
                                                    mCamDSDesc.SatDesc[mCamDSDesc.currSdsdIndex].SymbolRate, \
                                                    mCamDSDesc.SatDesc[mCamDSDesc.currSdsdIndex].Polarization, Cookie, \
                                                    ModlnStd, mCamDSDesc.SatDesc[mCamDSDesc.currSdsdIndex].ModulationType, IqMode, \
                                                    RollOff, FEC, Pilots);
    UNUSED (param);
}

void CHsvDvbsOpProfile_mScan::FuncCheckLockStatus (Nat32 param)
{
    FResult retVal;
    int lnbNumber, lnbType, lockStatus, lockedFreq, polarization,  symbolRate,iqMode,  bandwidth;

    retVal = satfeapi->GetSatelliteFrontEndParams (&lnbNumber, &lnbType, &lockStatus, &lockedFreq, \
                                                                          &polarization, &symbolRate, &iqMode, &bandwidth);

    TraceNotice(m, "Freq %d Sym %d  \n",lockedFreq, symbolRate);
    if ((retVal == IHsvErrorCodeEx_Ok) && (lockStatus == 0))
    {
        mNoStationFound();
    }
    else
    {
        mStationFound();
    }
}

void CHsvDvbsOpProfile_mScan::FuncStationFound(Nat32 param)
{
    // Anu: Open point - signal strength is started and queried immediately, should we wait for onMeasReqdy
    // Start signal strength measurement
    sigstr->StartSigStrMeasAll();

    mUpdateTuneReplyData(OP_TUNESTATUS_SUCCESS);
	ctrl->StartCollection(HsvDmxMain, IHsvSdmControl2_FransatCamIns);

    m_pfac.PmpSend(mCamDataPump, EvCamTuneReply, (Nat32)NULL);
}

void CHsvDvbsOpProfile_mScan::FuncDataAvailable(Nat32 param)
{
    TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
    
    if(param == EnmTypeTuneDSDescData)
    {
        TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
        // Tune descriptors is available in strapi database so get them sequentially and tune this is done in make decision 
        //  with necessary checks done on the descriptor data received from CAM
        mLoadOpTuneSDSDData();

        m_pfac.PmpSend(mScanPump, EvMakeDecision, (Nat32)NULL);
    } 
    else if(param == EnmTypeCamNITData)
    {
        TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
        // NIT Data Available so build the channel map tables through mDataAcq module
        if (mLoadStrapiData())
        {            
            TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
            idataacq->AcquireData(0);
            SET_INS_STATE(StAcquireWait);            

            //opins_StoreCamOperatorMetaData();
            //m_pfac.PmpSend(mCamDataPump, EvCamAck, (Nat32)NULL);
        }
    }
}

void CHsvDvbsOpProfile_mScan::FuncMakeDecision(Nat32 param)
{
    Bool DSDListExhausted = TRUE;
    static Bool camDescValid = TRUE;

    //while(mGetNextDSD())
    TraceNotice(m, "%s() : currSdsdIndex %d, numSDSD %d\n", __FUNCTION__, mCamDSDesc.currSdsdIndex, mCamDSDesc.numSDSD);
    while (mCamDSDesc.currSdsdIndex < mCamDSDesc.numSDSD)
    {
        // Entry of Next DSD is available check if it is valid and tune, otherwise iterate for next DSD, continue this until DSD list exhausts
        if(FALSE == mIsValidDeliveryDescriptorData())
        {
            camDescValid = FALSE;
            mUpdateTuneReplyData (OP_TUNESTATUS_INVALID);
        }
        else
        {
            TraceNotice(m, "%s() : Start Tuning \n", __FUNCTION__);
            SET_INS_STATE(StStrapiWait);
            m_pfac.PmpSend(mScanPump, EvStartTuning, (Nat32)NULL);

            DSDListExhausted = FALSE;
            break;
        }
    }
    if (DSDListExhausted == TRUE)
    {
        if(camDescValid == TRUE)
        {
            mUpdateTuneReplyData (OP_TUNESTATUS_FAILED);
        }
        TraceNotice(m, "DSD List Exhausted so send the CAM with tune fail reply with appropriate values that are cached previously ");
        m_pfac.PmpSend(mCamDataPump, EvCamTuneReply, (Nat32)NULL);
    }
}


void CHsvDvbsOpProfile_mScan::FuncDataAcquired (Nat32 param)
{
    TraceNotice(m, "%s() @ %d : Calling SendOpAck(), Entitlement_Change_Flag %d\n", __FUNCTION__, __LINE__, ENTITLEMENT_CHANGE_REQUESTED);
    camnitena->Disable(HsvDmxMain);
    

    opins->CacheOperatorData();
    
    if (ENTITLEMENT_CHANGE_REQUESTED)
    {
        TraceNotice(m, "%s opins->SendOpAck() called", __FUNCTION__);
        opins->SendOpAck();
		m_pfac.PmpSendAfter(mScanPump, EvInstallComplete, (Nat32)NULL,2000);
    }
	else
	{
		SET_INS_STATE (StIdle);
    	insN->OnEvent(IHsvSatelliteInstallationNotify_EventPkgInstallEnd, GET_INS_MODE);
		SET_INS_MODE(BACKGROUND_CAM_MODE);		
		mInitialise();
	}
    
	// This delay has been added to display correct package name from CAM
	

}

void CHsvDvbsOpProfile_mScan::FuncInstallComplete(Nat32 param)
{
	TraceNotice(m, "%s() @ %d",__FUNCTION__, __LINE__);
	SET_INS_STATE (StIdle);
    insN->OnEvent(IHsvSatelliteInstallationNotify_EventPkgInstallEnd, GET_INS_MODE);
	SET_INS_MODE(BACKGROUND_CAM_MODE);
	mInitialise();
}

void CHsvDvbsOpProfile_mScan::FuncDateTimeReceived (Nat32 param)
{
	HsvDateTime	dt = {0};
    HSVSPTYPE(DateTime,dvb,tot) hsvTOTUTC = {0};
	TraceNotice(m, "%s() @ %d : ",__FUNCTION__, __LINE__);
	if (strapi->GetByKey( HsvMain, HSVSPID(DateTime,dvb,tot), 0, 0, 0, (HSVSPTYPE(DateTime,dvb,tot)*)&hsvTOTUTC)) {
		TraceNotice(m, "Notify date & time to App layer with datetime in ms as %d",hsvTOTUTC.dt);
		 insN->OnEvent(IHsvSatelliteInstallationNotify_EventSetTime, int(hsvTOTUTC.dt));
	}	
}

void CHsvDvbsOpProfile_mScan::FuncStopServiceScan (Nat32 param)
{
    mInitialise();

    if(TUNING_REQUIRED)
    {
        TraceNotice(m, "%s opins_SendOpSearchCancel called", __FUNCTION__);
        opins->SendOpSearchCancel();
    }
    TraceNotice(m, "%s Installation stopped in CAM component", __FUNCTION__);
    insN->OnEvent(IHsvSatelliteInstallationNotify_EventInsStopped, GET_INS_MODE);
	SET_INS_MODE(BACKGROUND_CAM_MODE);
}

void CHsvDvbsOpProfile_mScan::mGetLnbDetails(int lnb)
{  
    HsvLnbSettings lnbSettings;
    idataacq->Initialise (lnb);

    // Save the current LNB Settings to local data
    idvbset->GetLnbSettings (&lnbSettings);
    mInstStatus.LnbNumber = lnb;
    mInstStatus.LnbType = lnbSettings.LnbSettings[lnb].LnbType;
}

void CHsvDvbsOpProfile_mScan::mStationFound()
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    if (TURNED_ON)
    {
        m_pfac.PmpSend(mScanPump, EvStationFound, (Nat32)NULL);
    }
}

void CHsvDvbsOpProfile_mScan::mNoStationFound()
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, __LINE__);
    if (TURNED_ON)
    {       
        ++mCamDSDesc.currSdsdIndex;
        m_pfac.PmpSend(mScanPump, EvMakeDecision, (Nat32)NULL);
    }
}


void CHsvDvbsOpProfile_mScan::mStopSdm(HsvDemux dmx)
{
    if(IHsvSdmControl2_Idle != ctrl->GetMode(dmx))
    {
        ctrl->StopCollection(dmx);
    }
}

Bool CHsvDvbsOpProfile_mScan::mLoadOpTuneSDSDData(void)
{
    Bool retval = FALSE;

    TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);

    if(SATELLITE_MEDIUM)
    {
        TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
        retval = mLoadOpTuneDSDFromStrapi(HSVSPID(OpTuneSatelliteDS, dvb, camnit));
    }
    else
    {
        TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
        // Cable & Terrestrial not supported in euinstallerSat 
        TraceNotice(m, "Error: Invalid Medium\n",__FUNCTION__, __LINE__);
    }

    TraceNotice(m,"%s retval %d\n", __FUNCTION__, retval);
    return retval;
}


Bool CHsvDvbsOpProfile_mScan::mLoadStrapiData(void)
{
    Bool retval = FALSE;

    TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);

    if(SATELLITE_MEDIUM)
    {
        TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
        retval = mLoadDSDFromStrapi(HSVSPID(SatelliteDS, dvb, camnit));
    }
    else
    {
        TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
        // Cable & Terrestrial not supported in euinstallerSat 
        TraceNotice(m, "Error: Invalid Medium\n",__FUNCTION__, __LINE__);
    }

    TraceNotice(m,"%s retval %d\n", __FUNCTION__, retval);
    return retval;
}

Bool CHsvDvbsOpProfile_mScan::mLoadDSDFromStrapi(int hsvspid)
{
    int numSDSD = 0;
    int loopCount = 0;
    int sdsdLoopCount = 0;
    Bool addSDSDEntry =  FALSE;
    HSVSPTYPE(SatelliteDS,dvb,nit) satSDSD;
    
    TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
    
    numSDSD = strapi->GetSize (HsvMain,  HSVSPID(SatelliteDS, dvb, camnit));
    mCamDSDesc.numSDSD = 0;

    TraceNotice (m," Number of SDSD %d\n", numSDSD);

    for(sdsdLoopCount = 0; sdsdLoopCount < numSDSD; ++sdsdLoopCount)
    {
        if(strapi->GetByIndex (HsvMain, HSVSPID(SatelliteDS, dvb, camnit), sdsdLoopCount, (void*)&satSDSD))
        {
            addSDSDEntry = TRUE;

            TraceDebug (m,"SDSD Entry ONID 0x%x NID 0x%x TSID 0x%x\n", \
            satSDSD.Original_NetworkId, satSDSD.NetworkId, satSDSD.Tsid);
            for(loopCount = 0; loopCount < mCamDSDesc.numSDSD; ++loopCount)
            {
                // search for existing entry before adding new entry
                if((mCamDSDesc.SatDesc[loopCount].Original_NetworkId == satSDSD.Original_NetworkId) &&
                (mCamDSDesc.SatDesc[loopCount].NetworkId == satSDSD.NetworkId) &&
                (mCamDSDesc.SatDesc[loopCount].Tsid == satSDSD.Tsid))
                {
                    // Entry already available
                    addSDSDEntry = FALSE;
                    TraceNotice (m,"SDSD entry already present\n");
                    break;
                }
            }

            if (addSDSDEntry)
            {
                memcpy (&(mCamDSDesc.SatDesc[mCamDSDesc.numSDSD]), &satSDSD, sizeof(HSVSPTYPE(SatelliteDS, dvb, camnit)));
                ++mCamDSDesc.numSDSD;
                TraceDebug (m,"SDSD Entry Added ONID 0x%x NID 0x%x TSID 0x%x", \
                satSDSD.Original_NetworkId, satSDSD.NetworkId, satSDSD.Tsid);
            }
        }
    }
   
    mCamDSDesc.currSdsdIndex = 0;

    return ((mCamDSDesc.numSDSD == 0) ? FALSE : TRUE);
}

Bool CHsvDvbsOpProfile_mScan::mLoadOpTuneDSDFromStrapi(int hsvspid)
{
    int numSDSD = 0;
    int loopCount = 0;
    int sdsdLoopCount = 0;
    Bool addSDSDEntry =  FALSE;
    HSVSPTYPE(SatelliteDS,dvb,nit) satSDSD;
    
    TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
    
    numSDSD = strapi->GetSize (HsvMain,  hsvspid);
    mCamDSDesc.numSDSD = 0;

    TraceNotice (m," Number of SDSD %d\n", numSDSD);

    for(sdsdLoopCount = (numSDSD - 1); sdsdLoopCount >= 0; sdsdLoopCount--)
    {
        if(strapi->GetByIndex (HsvMain, hsvspid, sdsdLoopCount, (void*)&satSDSD))
        {
            addSDSDEntry = TRUE;

            TraceDebug (m,"SDSD Entry Frequency %d Pol %d SymRate %d\n", \
            satSDSD.Frequency, satSDSD.Polarization, satSDSD.SymbolRate);
            for(loopCount = 0; loopCount < mCamDSDesc.numSDSD; ++loopCount)
            {
                // search for existing entry before adding new entry
                if((mCamDSDesc.SatDesc[loopCount].Frequency == satSDSD.Frequency) &&
                (mCamDSDesc.SatDesc[loopCount].Polarization == satSDSD.Polarization))
                {
                    // Entry already available
                    addSDSDEntry = FALSE;
                    TraceNotice (m,"SDSD entry already present\n");
                    break;
                }
            }

            if (addSDSDEntry)
            {
                memcpy (&(mCamDSDesc.SatDesc[mCamDSDesc.numSDSD]), &satSDSD, sizeof(HSVSPTYPE(SatelliteDS, dvb, camnit)));
                ++mCamDSDesc.numSDSD;
                TraceDebug (m,"SDSD Entry Added Frequency %d Pol %d SymRate %d\n", satSDSD.Frequency, satSDSD.Polarization, satSDSD.SymbolRate);
            }
        }
    }
   
    mCamDSDesc.currSdsdIndex = 0;

    return ((mCamDSDesc.numSDSD == 0) ? FALSE : TRUE);
}


void* CHsvDvbsOpProfile_mScan::mGetLocalBuffer(int size)
{
    void* Buffer = malloc(size);

    if (Buffer == NULL)
    {
        TraceErr(m, "malloc failure %d from 0x%x", size, (unsigned int)__builtin_return_address(0));
    }

    return Buffer;
}

void* CHsvDvbsOpProfile_mScan::mReturnLocalBuffer(void **Buffer)
{
    free(*Buffer);
    *Buffer = NULL;

    return NULL;
}

Bool CHsvDvbsOpProfile_mScan::mIsValidDeliveryHint(int DeliveryHint)
{
    Bool retval = FALSE;

    switch (DeliveryHint)
    {
        case 0b0010:
            // DVBS or S2
            retval = (SATELLITE_MEDIUM) ? TRUE : FALSE;
            break;
        case 0b0001:
        case 0b0100:
        default:
            // Terrestrial/Cable not supported in euinstallersat
            break;
    }
    return retval;
}


Bool CHsvDvbsOpProfile_mScan::mIsValidDeliveryDescriptorData(void)
{
    return TRUE;
}

/* Validate Parameters Functions */
void CHsvDvbsOpProfile_mScan::mCamDataPumpHandler(int event, Nat32 param)
{
    TraceNotice(m, "%s event %d", __FUNCTION__, event);

    switch(event)
    {
        case EvCamSearchStatus:

            mCamSearchStatus((Op_ProfileSearchStatus *) param);
            mReturnLocalBuffer((void **)&param);
            break;
        case EvCamStatusInfo:

            // Copy to static module variable
            mStatusInfo = *(Op_ProfileStatusInfo *) param;

            mCamStatusInfo();
            mReturnLocalBuffer((void **)&param);
            break;
        case EvCamNITReceived:
                    mCamNITReceived((Op_ProfileNitData *) param);
                    mReturnLocalBuffer((void **)&param);
                    break;
        case EvCamTuneRequest:

            mTempTuneDataPtr = (Op_ProfileTuneData *) param;

            // create & init the buffer for reply data which will be sent to cam in tune status reply
            mTempTuneReplyDataPtr = (Op_Tune_Status *) mGetLocalBuffer(sizeof(Op_Tune_Status));
            memset(mTempTuneReplyDataPtr, 0, sizeof(Op_Tune_Status));

            mCamTuneRequest((Op_ProfileTuneData *) param);
            // Do not free both the temp buffer here, as we need the descriptor data to be passed in the tune reply, 
            // the free of this buffer is done when below event (EvCamTuneReply) occurs

            break;
        case EvCamTuneReply:

            mCamTuneReply();
            mReturnLocalBuffer((void **)&mTempTuneDataPtr);
            mReturnLocalBuffer((void **)&mTempTuneReplyDataPtr);
            break;
        case EvCamAck:
            // Acknowledge the handled entitlement change as we have honoured the CAM installation request with tuning and with CAMNIT
            if(ENTITLEMENT_CHANGE_REQUESTED)
            {
                TraceNotice(m, "%s opins->SendOpAck() called", __FUNCTION__);
                opins->SendOpAck();
            }
        default:
            break;
    }
}

void CHsvDvbsOpProfile_mScan::mCamSearchStatus(Op_ProfileSearchStatus *TempSearchStatusInfo)
{
	if(TempSearchStatusInfo->op_Status.Error_Flag != 0)//For fixing 7.2.4
	{
	   TraceNotice(m, "Error flag returned.. so stop installation proceeded\n");
	   insN->OnEvent(IHsvSatelliteInstallationNotify_EventInsStopped, GET_INS_MODE);
	   SET_INS_MODE(BACKGROUND_CAM_MODE);
	   mInitialise();
	}
    else if(NIT_REQUIRED (TempSearchStatusInfo->op_Status.NIT_Version) || ((mStatusInfo.op_Status.Profile_Type == OP_PROFILE_TYPE_1) && ((AUTO_INSTALL) || (CAM_NIT_INSTALL))))
    {
        TraceNotice(m, "%s opins_RequestNit called", __FUNCTION__);
        opins->RequestNit();
        mStatusInfo.op_Status.NIT_Version = TempSearchStatusInfo->op_Status.NIT_Version;
		mStatusInfo.op_Status.Entitlement_Change_Flag = TempSearchStatusInfo->op_Status.Entitlement_Change_Flag;
		mStatusInfo.op_Status.Entitlement_Valid_Flag = TempSearchStatusInfo->op_Status.Entitlement_Valid_Flag;                 
    }
    else
    {
        TraceNotice(m, "%s Nit Not requested New NITVersion %d CAM Updated NITVersion %d", __FUNCTION__, 
                                TempSearchStatusInfo->op_Status.NIT_Version, CAM_UPDATED_NIT_VERSION);

        // Acknowledge the handled entitlement change as we have honoured the CAM installation request with tuning, 
        // However it did not send the updated NIT version, perhaps it already has it or it is profile 0 CAM.
        if(ENTITLEMENT_CHANGE_REQUESTED)
        {
            TraceNotice(m, "%s opins_SendOpAck called", __FUNCTION__);
            opins->SendOpAck();
			SET_INS_MODE(BACKGROUND_CAM_MODE);
        }

        if (TempSearchStatusInfo->op_Status.Error_Flag == 3)
        {
            TraceNotice (m, "Error flag returned.. so stop installation proceeded\n");
        }
        else
        {
            #if 0        
            insN_OnEvent(insN_EventChannelFound, rins_InstallationModeCam);

            TraceNotice (m, "%s Installation Successfully completed in CAM component", __FUNCTION__);
            insN_OnEvent (insN_EventInstallationCompleted, mStatusInfo.op_Status.Profile_Type);
            int networkOperator = ((rins_GetMedium() == rins_Terrestrial) ? rins_DvbTCAM:rins_DvbCCAM);
            idvbset_SetAttribute(AUTO_MODE, rins_AttributeNetworkOperator, networkOperator);
            idvbset_SetAttribute(AUTO_MODE, rins_AttributeCamNITVersion, TempSearchStatusInfo->op_Status.NIT_Version);
            #endif
            mSetCharacterCode();
        }
        camnitena->Disable(HsvDmxMain);

        mInitialise();
    }
}

void CHsvDvbsOpProfile_mScan::mCamStatusInfo(void)
{
    Bool proceed = TRUE;

    TraceNotice (m, "%s() : %d, Entitlement_Change_Flag = %d with GET_INS_STATE %d and GET_INS_MODE %d\n", __FUNCTION__, __LINE__, ENTITLEMENT_CHANGE_REQUESTED,GET_INS_STATE,GET_INS_MODE);
	TraceNotice(m,"mStatusInfo.op_Status.Profile_Type %d ENTITLEMENT_CHANGE_REQUESTED %d NIT_REQUIRED (CAM_UPDATED_NIT_VERSION) %d TUNING_REQUIRED %d",mStatusInfo.op_Status.Profile_Type,ENTITLEMENT_CHANGE_REQUESTED,NIT_REQUIRED (CAM_UPDATED_NIT_VERSION),TUNING_REQUIRED);
    // Check for error conditions whether to proceed or not
    if ((FALSE == mIsValidDeliveryHint(GET_CAM_DELIVERY_HINT) || (!PROFILE_INFO_VALID)) && (CAM_INITIALISED == TRUE))
    {
        proceed = FALSE;

        TraceErr(m, "Unsupported delivery System %d sent from CAM or Info valid flag is %d \n", GET_CAM_DELIVERY_HINT, mStatusInfo.op_Info.info_Valid);
        if (AUTO_INSTALL)
        {
            m_pfac.PmpSend(mScanPump, EvStop, (Nat32)NULL);
        }
    }

    if (proceed)
    {
        if(SCHEDULE_UPDATE && (GET_INS_STATE == StIdle))
        {
            // Schedule update request has come; Don't take any action here as alarm will be  
            // triggered in upper layer and later we get startInstallation trigger
            TraceNotice (m, "Schedule update request has come don't take any action here as alarm will be triggered \
                                     in upper layer and later we get startInstallation trigger \n"); 
        }
        else
        {
            if ((FALSE == CAM_INITIALISED) || (TUNING_REQUIRED))
            {
                // First time CAM has sent the profile request so honour the request and ignore other flags, or tuning required 
                // flag is true. if StIdle Background installation trigger from the cam same rules are followed for both auto & 
                // background except that with insN event UI is displayed in latter case
                if (GET_INS_STATE == StIdle)
                {
                    SET_INS_MODE(BACKGROUND_CAM_MODE);
                    if ((URGENT_TUNING_REQUIRED) && (CAM_INITIALISED == TRUE))
                    {
                        insN->OnEvent(IHsvSatelliteInstallationNotify_EventInsOpProfileRequestUrgent, GET_INS_MODE); //Trigger Urgent Installation as CICAM needs it to be urgent mode installation
                    }
                    else if ((ADVANCE_TUNING_REQUIRED)&& (CAM_INITIALISED == TRUE))
                    {
                        insN->OnEvent(IHsvSatelliteInstallationNotify_EventInsOpProfileRequestNormal, GET_INS_MODE); //Get acknowledgement from user for OP installation
                    }
                }
                else
                {	//SET_INS_MODE(CAM_NIT_UPDATE_MODE);
                    TraceNotice(m, "%s @ %d : mInstStatus.State %d \n", __FUNCTION__, __LINE__, GET_INS_STATE);
					/*if((CAM_NIT_INSTALL) && (GET_INS_STATE == StStart))
					{
						TraceNotice(m, "%s opins_RequestNit called", __FUNCTION__);
						opins->RequestNit();
					}
                    else*/ if (GET_INS_STATE == StStart) {
                        insN->OnEvent(IHsvSatelliteInstallationNotify_EventPkgInstallStart, GET_INS_MODE);

                        TraceNotice(m, "%s @ %d : Calling SendOperatorSearchStart \n", __FUNCTION__, __LINE__);
                        opins->SendOperatorSearchStart (mSearchSettings);
                        mSetCharacterCode ();
                        SET_INS_STATE (StSearchStartWait);
                    }
                }
            }
           /* else if (NIT_REQUIRED (CAM_UPDATED_NIT_VERSION))
            {
                if (GET_INS_STATE == StIdle)
                {
                    SET_INS_MODE (BACKGROUND_CAM_MODE);
                    insN->OnEvent(IHsvSatelliteInstallationNotify_EventInsOpProfileRequestNormal, GET_INS_MODE);
                }
                else
                {
                    insN->OnEvent(IHsvSatelliteInstallationNotify_EventPkgInstallStart, GET_INS_MODE);

                    TraceNotice(m, "%s opins_RequestNit called", __FUNCTION__);
                    opins->RequestNit();
                }
            }*/
			else if (NIT_REQUIRED (CAM_UPDATED_NIT_VERSION))
            {
				TraceNotice(m, "Entered into Entitlement change mode");
                if (GET_INS_STATE == StIdle)
                {			
                   // SET_INS_MODE (BACKGROUND_CAM_MODE);
					if(ENTITLEMENT_CHANGE_REQUESTED == 1)
					{
						TraceNotice(m, "Entered into cam nit installation mode");
						insN->OnEvent(IHsvSatelliteInstallationNotify_EventCamNitInstallation, GET_INS_MODE);
					}
					else if (NIT_REQUIRED (CAM_UPDATED_NIT_VERSION))
					{
                   // SET_INS_MODE (BACKGROUND_CAM_MODE);
                    insN->OnEvent(IHsvSatelliteInstallationNotify_EventInsOpProfileRequestNormal, GET_INS_MODE);
					}
                }
                else
                {
					if((CAM_NIT_INSTALL) && (GET_INS_STATE == StStart))
					{
						TraceNotice(m, "%s opins_RequestNit called", __FUNCTION__);
						opins->RequestNit();
					}
					else
					{
                   /* insN->OnEvent(IHsvSatelliteInstallationNotify_EventPkgInstallStart, GET_INS_MODE);

                    TraceNotice(m, "%s opins_RequestNit called", __FUNCTION__);
                    opins->RequestNit();*/
					}
                }
            }
			else if((CAM_NIT_INSTALL) && (GET_INS_STATE == StStart))
			{
				TraceNotice(m, "%s opins_RequestNit called", __FUNCTION__);
				opins->RequestNit();
			}

			
        }
    }
}

void CHsvDvbsOpProfile_mScan::mCamNITReceived(Op_ProfileNitData *TempNitData)
{
    if ((TempNitData->NitStatus == TRUE) && (TempNitData->NitDataLength > 0) )
    {
        SET_INS_STATE(StStrapiWait);
        TraceNotice(m, "%s Start parsing CAM NIT \n", __FUNCTION__);
        mSetCharacterCode();
        camdataparser->ParseCamData(HsvMain, EnmTypeCamNITData, TempNitData->NitDataLength, TempNitData->NitData);
    }
    else
    {
        TraceErr(m, "%s Invalid NIT data received with status %d length %d", __FUNCTION__, 
                            TempNitData->NitStatus, TempNitData->NitDataLength);
        m_pfac.PmpSend(mScanPump, EvStop, (Nat32)NULL);
    }
}

void CHsvDvbsOpProfile_mScan::mCamTuneRequest(Op_ProfileTuneData *TempTuneData)
{
    TraceNotice (m, "%s TuneDataLength %d", __FUNCTION__, TempTuneData->TuneDataLength);
    if (TempTuneData->TuneDataLength > 0)
    {
        SET_INS_STATE(StStrapiWait);
        camdataparser->ParseCamData(HsvMain, EnmTypeTuneDSDescData, TempTuneData->TuneDataLength, TempTuneData->TuneData);
    }
    else
    {
        TraceErr(m, "%s TuneDataLength %d", __FUNCTION__, TempTuneData->TuneDataLength);
        m_pfac.PmpSend(mScanPump, EvStop, (Nat32)NULL);
    }
}

void CHsvDvbsOpProfile_mScan::mCamTuneReply(void)
{
    TraceNotice(m, "%s opins_SendOpTuneStatus called with (%d %d %d %d)", __FUNCTION__, 
                            mTempTuneReplyDataPtr->Descriptor_Number, mTempTuneReplyDataPtr->Signal_Strength, 
                            mTempTuneReplyDataPtr->Signal_Quality, mTempTuneReplyDataPtr->Descriptor_Loop_Length);
    opins->SendOpTuneStatus (*mTempTuneReplyDataPtr);
}

void CHsvDvbsOpProfile_mScan::mUpdateTuneReplyData(OP_Status status)
{
    mTempTuneReplyDataPtr->Status = status;

    switch(status)
    {
        case OP_TUNESTATUS_SUCCESS:

            mTempTuneReplyDataPtr->Descriptor_Number = ((mCamDSDesc.currSdsdIndex + 1 == mCamDSDesc.numSDSD) ? 0xFF : mCamDSDesc.currSdsdIndex + 1);    // Points to the next unprocessed descriptor in tune request
            //mTempTuneReplyDataPtr->Signal_Strength = sigstr->GetActualSignalStrength(IHsvInstallationSigStrength_InsSsm, 0);
            //mTempTuneReplyDataPtr->Signal_Quality = sigstr->GetActualSignalStrength(IHsvInstallationSigStrength_InsQsm, 0);
            mTempTuneReplyDataPtr->Signal_Strength = 100;
            mTempTuneReplyDataPtr->Signal_Quality = 100;

            mCopyTuneDescriptorsLoop(TRUE);
            ++mInstStatus.currSdsdIndex;
            break;
        case OP_TUNESTATUS_FAILED:

            mTempTuneReplyDataPtr->Descriptor_Number = 0xFF;
            mTempTuneReplyDataPtr->Signal_Strength = 0;
            mTempTuneReplyDataPtr->Signal_Quality = 0;
            mTempTuneReplyDataPtr->Descriptor_Loop_Length = 0;
            mTempTuneReplyDataPtr->Descriptor_Loop = 0;
            break;
    case OP_TUNESTATUS_NOT_SUPPORTED:

            mTempTuneReplyDataPtr->Descriptor_Number = 0xFF; //(mInstStatus.currSdsdIndex + 1);
            mTempTuneReplyDataPtr->Signal_Strength = 0;
            mTempTuneReplyDataPtr->Signal_Quality = 0;

            mCopyTuneDescriptorsLoop(FALSE);
            break;
        case OP_TUNESTATUS_INVALID:

            mTempTuneReplyDataPtr->Descriptor_Number = 0xFF; //(mInstStatus.currSdsdIndex + 1);
            mTempTuneReplyDataPtr->Signal_Strength = 0;
            mTempTuneReplyDataPtr->Signal_Quality = 0;

            mCopyTuneDescriptorsLoop(FALSE);
            break;
        default:
            TraceErr(m, "%s Invalid Tune status of the DSD", __FUNCTION__, status);
            break;
    }
}

void CHsvDvbsOpProfile_mScan::mCopyTuneDescriptorsLoop(Bool ValidLocation)
{
    //int DescriptorEntryLength = mGetDescriptorEntryLength();
    int DescriptorEntryLength = DVBS_DESCRIPTOR_ENTRY_LENGTH;

    if(mTempTuneReplyDataPtr->Descriptor_Loop == NULL)
    {
        mTempTuneReplyDataPtr->Descriptor_Loop = (Nat8 *) mGetLocalBuffer (mTempTuneDataPtr->TuneDataLength);
    }

    memcpy ((mTempTuneReplyDataPtr->Descriptor_Loop + mTempTuneReplyDataPtr->Descriptor_Loop_Length), \
                  (mTempTuneDataPtr->TuneData + (mTempTuneReplyDataPtr->Descriptor_Loop_Length + (mCamDSDesc.currSdsdIndex * (DescriptorEntryLength + 2)))), (DescriptorEntryLength + 2));

    mTempTuneReplyDataPtr->Descriptor_Loop_Length = (DescriptorEntryLength + 2);

    TraceNotice(m, "mTempTuneReplyDataPtr contents start with length %d", mTempTuneReplyDataPtr->Descriptor_Loop_Length);
    for(int i = 0; i < mTempTuneReplyDataPtr->Descriptor_Loop_Length; i++)
    {
        TraceNotice(m, "%x ", mTempTuneReplyDataPtr->Descriptor_Loop[i]);
    }
    TraceNotice(m, "mTempTuneReplyDataPtr contents end");

    TraceNotice(m, "mTempTuneDataPtr contents start");
    for(int i = 0; i < mTempTuneReplyDataPtr->Descriptor_Loop_Length; i++)
    {
        TraceNotice(m, "%x ", mTempTuneDataPtr->TuneData[i]);
    }
    TraceNotice(m, "mTempTuneDataPtr contents end");
}


void CHsvDvbsOpProfile_mScan::mInitialise(void)
{
    TraceNotice(m, "%s() : %d",__FUNCTION__, __LINE__);

    Nat8 DeliveryCapility[4]      = {DVBS_DELIVERY_TAG, DVBS2_DELIVERY_OFFSET_TAG};
    Nat8 ApplicationCapability[4] = {0};
    Nat8 ServiceType[17] = {0x01,0x02,0x03,0x04,0x05,0x06,0x10,0x0A,0x0C,0x11,0x16,0x17,0x18,0x19,0x1C,0x20,0x21};

    // Scan data related
    SET_INS_STATE(StIdle);
    //SET_INS_MODE(BACKGROUND_CAM_MODE);
    memset((Address)(&mCamDSDesc), 0, sizeof(mCamDSDesc));

    // Cam data related
    mSearchSettings.Unattended_Flag = 0; // As we  support MMI/ AMMI during installation wizard for fransat
    mSearchSettings.Service_Type_Length = MAX_SERVICE_TYPES_SUPPORTED;    
    mSearchSettings.Service_Type = (Nat8*) malloc (MAX_SERVICE_TYPES_SUPPORTED);
    memcpy (mSearchSettings.Service_Type, ServiceType, MAX_SERVICE_TYPES_SUPPORTED);
        
    if (SATELLITE_MEDIUM)
    {
        TraceNotice(m, "%s() : %d",__FUNCTION__, __LINE__);
        mSearchSettings.Delivery_Cap_Length = 2;
        mSearchSettings.Delivery_Capability = (Nat8*) malloc (2);
       // *(mSearchSettings.Delivery_Capability) = DeliveryCapility[0];  // DVBS & S2
        memcpy(mSearchSettings.Delivery_Capability, &DeliveryCapility[0],2);
    }
    mSearchSettings.Application_Capability = (Nat8*) malloc (2);
    mSearchSettings.Application_Cap_Length = 0;
    *(mSearchSettings.Application_Capability) = ApplicationCapability[0];

    TraceNotice(m, "%s() : %d",__FUNCTION__, __LINE__);
}

void CHsvDvbsOpProfile_mScan::mGetCurrentTunerParams (HsvInstallationPTC *ptc)
{

    FResult retVal;
    int lnbNumber, lnbType, lockStatus, lockedFreq, polarization,  symbolRate,iqMode,  bandwidth;

    retVal = satfeapi->GetSatelliteFrontEndParams (&lnbNumber, &lnbType, &lockStatus, &lockedFreq, \
                                                                          &polarization, &symbolRate, &iqMode, &bandwidth);

    if (retVal == IHsvErrorCodeEx_Ok)
    {
        ptc->Frequency = lockedFreq;
        ptc->SymbolRate = symbolRate;
        ptc->ModulationType = 0;
        ptc->CodeRateHigh = 0;
        ptc->CodeRateLow = 0;
        ptc->IqMode = iqMode;
        ptc->ChannelBandwidth = bandwidth;
        ptc->Polarization = polarization;
    }
}

void CHsvDvbsOpProfile_mScan::mSetCharacterCode (void)
{
    char charCode[3];
    
    TraceNotice (m, "%s() : %d \n", __FUNCTION__, __LINE__);
    
    charCode[0] = mStatusInfo.op_Info.character_Code_Table;
    charCode[1] = mStatusInfo.op_Info.character_Code_Table_2;
    charCode[2] = mStatusInfo.op_Info.character_Code_Table_3;
    camdataparser->SetCharacterCode (charCode);
}


/*****************************************************************************************
 * Public methods
 *****************************************************************************************/

// Overridden IHsvPower methods

void CHsvDvbsOpProfile_mScan::Init(void)
{
    mScanPump = m_pfac.PmpCreate(pen->PumpEngine(), &CHsvDvbsOpProfile_mScan::mScanPumpHandler, FALSE, (char *)"hsvdvbsopprofile_mScanPump", this);
    mCamDataPump = m_pfac.PmpCreate(pen->PumpEngine(), &CHsvDvbsOpProfile_mScan::mCamDataPumpHandler, FALSE, (char *)"hsvdvbsopprofile_mCamDataPump", this);
    mModuleLifeCycle = Initialised;

    iacqpow->Init();
    isortpow->Init();
}

void CHsvDvbsOpProfile_mScan::TurnOn(void)
{
    mModuleLifeCycle = TurnedOn;
    mInitialise();
	SET_INS_MODE(BACKGROUND_CAM_MODE);
    iacqpow->TurnOn();
    isortpow->TurnOn();
}

void CHsvDvbsOpProfile_mScan::TurnOff (void)
{
    mModuleLifeCycle = TurnedOff;

    iacqpow->TurnOff();
    isortpow->TurnOff();
}


// Overridden IHsvSatellitePackageInstallation methods

FResult CHsvDvbsOpProfile_mScan::StartInstallation (int source, int lnb, int mode)
{
    FResult retVal = IHsvErrorCodeEx_Ok;

    TraceNotice(m,"%s %d TURNED_ON %d source %d mode %d\n", __FUNCTION__, __LINE__, TURNED_ON, source, mode);
    if( TURNED_ON && VALID_CAM_INSTALL_MODE(mode) )
    {
        SET_INS_MODE (mode);
        m_pfac.PmpSend (mScanPump, EvStart, lnb);
    }

    return retVal;
}

FResult CHsvDvbsOpProfile_mScan::StopInstallation(void)
{
    FResult retVal = (GET_INS_STATE == StIdle)? IHsvErrorCodeEx_InstallationNotInProgress : IHsvErrorCodeEx_Ok;

    TraceDebug(m,"%s TURNED_ON %d\n", __FUNCTION__, TURNED_ON);
    if(TURNED_ON && (retVal == IHsvErrorCodeEx_Ok) )
    {
        m_pfac.PmpSend(mScanPump, EvStop, (Nat32)NULL);
    }

    return retVal;
}

int CHsvDvbsOpProfile_mScan::GetCurrentInstallationState (int *mode,int *state)
{
    // Function to get the installation mode and status
    int retVal = IHsvErrorCodeEx_Ok;
    TraceNotice (m," Entering function - %s()\n",__FUNCTION__);
    if (mode && state)
    {
        *mode = GET_INS_MODE;
        *state = GET_INS_STATE;
    }

    return retVal;
}

int CHsvDvbsOpProfile_mScan::GetNumberOfTvChannelsFound (int mode,int lnb)
{
    int retVal = 0;

    retVal = idataacq->GetNumberOfTvChannelsFound();

    UNUSED(mode);
    UNUSED(lnb);

    return retVal;
}

int CHsvDvbsOpProfile_mScan::GetNumberofRadioChannelsFound(int mode,int lnb)
{
    int retVal = 0;

    retVal = idataacq->GetNumberOfRadioChannelsFound();

    UNUSED(mode);
    UNUSED(lnb);

    return retVal;
}

int CHsvDvbsOpProfile_mScan::GetNumberOfTvChannelsRemoved(int mode,int lnb)
{
    int retVal = 0;

    retVal = idataacq->GetNumberOfTvChannelsRemoved();

    UNUSED(mode);
    UNUSED(lnb);

    return retVal;
}

int CHsvDvbsOpProfile_mScan::GetNumberofRadioChannelsRemoved(int mode,int lnb)
{
    int retVal = 0;

    retVal = idataacq->GetNumberofRadioChannelsRemoved();

    UNUSED(mode);
    UNUSED(lnb);

    return retVal;
}

FResult CHsvDvbsOpProfile_mScan::WriteBarkerMuxData (void)
{
    TraceNotice(m,"DummyCall:WriteBarkerMuxData\n");
    return 0;
}

int CHsvDvbsOpProfile_mScan::GetNumberOfDigitalChannelsAdded(void)
{
    TraceNotice(m,"DummyCall:GetNumberOfDigitalChannelsAdded\n");
    return 0;
}

int CHsvDvbsOpProfile_mScan::GetNumberOfDigitalChannelsRemoved(void)
{
    TraceNotice(m,"DummyCall:GetNumberOfDigitalChannelsRemoved\n");
    return 0;
}

int CHsvDvbsOpProfile_mScan::GetNumberOfDigitalChannelsMoved(void)
{
    TraceNotice(m,"DummyCall:GetNumberOfDigitalChannelsMoved\n");
    return 0;
}

FResult CHsvDvbsOpProfile_mScan::LoadManualInstallationDefaultValues(void)
{
    TraceNotice(m,"DummyCall:LoadManualInstallationDefaultValues\n");
    return 0;
}

FResult CHsvDvbsOpProfile_mScan::StoreManualInstallationValues(void)
{
    TraceNotice(m,"DummyCall:StoreManualInstallationValues\n");
    return 0;
}

Bool CHsvDvbsOpProfile_mScan::SetManualInstallationAttributes(int attributeId,int value)
{
    TraceNotice(m,"DummyCall:SetManualInstallationAttributes\n");
    return 0;
}

int CHsvDvbsOpProfile_mScan::GetAttribute(int mode,int attributeId)
{
    TraceNotice(m,"GetAttribute called In OP - Satellite\n");
	int retVal =0;
	HSVSPTYPE(TimeOffset,dvb,tot) TimeOffsetInfo={0};
	if(strapi->GetByKey( HsvMain, HSVSPID(TimeOffset, dvb, tot), 0,0, 0, (HSVSPTYPE(TimeOffset,dvb,tot)*)&TimeOffsetInfo))
	{
		TraceNotice(m,"Entered into TOT case");
		if(attributeId == IHsvSatelliteInstallation_AttributeTimeOffset)
		{
			TraceNotice(m,"Timeoffste value is %d",TimeOffsetInfo.TimeOffset);
			retVal = TimeOffsetInfo.TimeOffset;
		}
		else if(attributeId == IHsvSatelliteInstallation_AttributeChangeDate)
		{
			retVal = TimeOffsetInfo.ChangeDt;
			TraceNotice(m,"Changedate value is %d",TimeOffsetInfo.ChangeDt);
		}
		else if(attributeId == IHsvSatelliteInstallation_AttributeNextTimeOffset)
		{
			retVal = TimeOffsetInfo.NextTimeOffset;
			TraceNotice(m,"Nexttimeoffset value is %d",retVal);
		}

	}
    return retVal;
}

int CHsvDvbsOpProfile_mScan::GetScanProgressStatus(int mode)
{
    TraceNotice(m,"DummyCall:GetScanProgressStatus\n");
    return 0;
}

void CHsvDvbsOpProfile_mScan::GetSIDetails(HsvSDMSIDataValues *siValues)
{
    TraceNotice(m,"DummyCall:GetSIDetails\n");
}

FResult CHsvDvbsOpProfile_mScan::StartTricolorRegionParsing ()
{
	  TraceNotice (m, "Error!!! StartTricolorRegionParsing-Should not land here");
	  return 0;
}

FResult CHsvDvbsOpProfile_mScan::SetTricolorRegionIndex(int index)
{
	  TraceNotice (m, "Error!!! SetTricolorRegionIndex-Should not land here");
	  return 0;
}

FResult CHsvDvbsOpProfile_mScan::GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice (m, "Error!!! GetTricolorRegionNames-Should not land here");
	  return 0;
}
FResult CHsvDvbsOpProfile_mScan::SetPostcode(Nat8 postcodeLen, Nat8 *postcode)
{
    TraceNotice(m,"DummyCall:SetPostcode\n");
    return 0;
}


// Overridden IHsvDigitalScanData methods
void CHsvDvbsOpProfile_mScan::GetPtcInfo (HsvInstallationPTC * ptc)
{
    int transponderFreq;

    ptc->LnbNumber = mInstStatus.LnbNumber;
    ptc->LnbType = mInstStatus.LnbType;

    mGetCurrentTunerParams (ptc);

    transponderFreq = ptc->Frequency;
    ROUNDOFF_TPFREQ(ptc->Frequency, transponderFreq);

    ptc->TPID = CREATE_TPID(ptc->LnbNumber, ptc->Frequency, ptc->Polarization);

    TraceNotice  (m, " Freq %d and BW : %d \n", transponderFreq, ptc->ChannelBandwidth);
    ptc->QSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsQsm);
    ptc->SSignalStrength    =   0;//isigstr_GetSignalStrength(isigstr_InsSsm);

    ptc->SDSDFrequency = mCamDSDesc.SatDesc[CURRENT_SDSD_INDEX].Frequency;
    ptc->PlpId = 0;
    ptc->HierarchyMode = HsvHierarchyNone;
    ptc->StreamPriority = HsvStreamPriorityHigh;
}

int CHsvDvbsOpProfile_mScan::GetInstallationVersion(void)
{
    TraceNotice(m,"DummyCall:GetInstallationVersion\n");
    return 0;
}
void CHsvDvbsOpProfile_mScan::GetPtcInfoForSdSd(HsvInstallationPTC * ptc)
{
    TraceNotice(m,"DummyCall:GetPtcInfoForSdSd\n");
}
void CHsvDvbsOpProfile_mScan::SyncComplete(void)
{
    TraceNotice(m,"DummyCall:SyncComplete\n");
}


// Overridden IHsvDigitalAcquisitionNotify methods
void CHsvDvbsOpProfile_mScan::OnDataAquired (Bool status)
{
    TraceNotice (m," Entering function - %s status %d\n",__FUNCTION__, status);
    /*service scan completed, send compte notification*/
    m_pfac.PmpSend (mScanPump, EvDataAcquired, (Nat32)TRUE);
}


// Overridden IHsvSatelliteFrontEndNotify methods
void CHsvDvbsOpProfile_mScan::OnLockChanged(Bool lockState)
{
    // Notifiation Handler for DVB-S platform FE
    m_pfac.PmpSend(mScanPump, EvCheckLock, (Nat32)lockState);
}

void CHsvDvbsOpProfile_mScan::OnBlindScanEnd(void)
{
}


//Overridden IHsvSdmControlNotifyEx methods
void CHsvDvbsOpProfile_mScan::OnEvent(HsvDemux dmx,int eventid,int value)
{
	TraceNotice(m, "Date Time received notification");
	if((eventid == IHsvSdmControlNotifyEx_DataAvailable) && (value == IHsvSdmControlNotifyEx_TOT))
	{
			 m_pfac.PmpSend(mScanPump, EvDateTimeReceived, (Nat32)NULL);
	}
}


// Overridden ICesOperatorProfileNotify methods
void CHsvDvbsOpProfile_mScan::OnOpSearchStatus (Op_ProfileSearchStatus opStatus)
{
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    if (TURNED_ON)
    {
        Op_ProfileSearchStatus *SearchStatusInfo = (Op_ProfileSearchStatus *) mGetLocalBuffer(sizeof(Op_ProfileSearchStatus));

        memcpy(SearchStatusInfo, (void *)&opStatus, sizeof(Op_ProfileSearchStatus));

        m_pfac.PmpSend(mCamDataPump, EvCamSearchStatus, (Nat32)SearchStatusInfo);
    }
}

void CHsvDvbsOpProfile_mScan::OnOpStatusInfo(Op_ProfileStatusInfo StatusInfo)
{
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    if (TURNED_ON)
    {
        Op_ProfileStatusInfo *TempStatusInfo = (Op_ProfileStatusInfo *) mGetLocalBuffer(sizeof(Op_ProfileStatusInfo));

        memcpy(TempStatusInfo, (void *)&StatusInfo, sizeof(Op_ProfileStatusInfo));

        m_pfac.PmpSend(mCamDataPump, EvCamStatusInfo, (Nat32)TempStatusInfo);
    }
}

void CHsvDvbsOpProfile_mScan::OnOpNIT(Op_ProfileNitData nitData)
{
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    if (TURNED_ON)
    {
        Op_ProfileNitData *TempNitData = (Op_ProfileNitData *)mGetLocalBuffer(sizeof(Op_ProfileNitData));

        memcpy(TempNitData, (void *)&nitData, sizeof(Op_ProfileNitData));

        m_pfac.PmpSend(mCamDataPump, EvCamNITReceived, (Nat32)TempNitData);
    }
}

void CHsvDvbsOpProfile_mScan::OnOpTune(Op_ProfileTuneData tuneData)
{
	int index = 0;
    TraceNotice(m, "%s() : %d", __FUNCTION__, __LINE__);
    if(TURNED_ON)
    {
        Op_ProfileTuneData *TempTuneData = (Op_ProfileTuneData *) mGetLocalBuffer(sizeof(Op_ProfileTuneData));

        memcpy(TempTuneData, (void *)&tuneData, sizeof(Op_ProfileTuneData));
        TraceNotice(m, "%s() : %d : TempTuneData->TuneDataLength %d", __FUNCTION__, __LINE__,TempTuneData->TuneDataLength);
        for(index =0; index<TempTuneData->TuneDataLength;index++){
        	TraceNotice(m, "%s() : %d : %d", __FUNCTION__, __LINE__,TempTuneData->TuneData[index]);
        }

        m_pfac.PmpSend(mCamDataPump, EvCamTuneRequest, (Nat32)TempTuneData);
    }
}


//IHsvStreamNotify
void CHsvDvbsOpProfile_mScan::OnCompleted (HsvDestination dest, int spid)
{
    UNUSED(dest);

    TraceNotice(m, "%s() : %d \n", __FUNCTION__, __LINE__);
    
    switch (spid)
    {
        case EnmTypeCamNITData:
        case EnmTypeTuneDSDescData:
            m_pfac.PmpSend(mScanPump, EvDataAvailable, (Nat32)spid);
            break;
        default:
        break;
    }
    }

void CHsvDvbsOpProfile_mScan::OnAdded (HsvDestination dest,int spid,int key1,int key2,int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key2);

}

void CHsvDvbsOpProfile_mScan::OnChanged (HsvDestination dest,int spid,int key1,int key2,int key3,int eventid)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key2);
    UNUSED(eventid);

}

void CHsvDvbsOpProfile_mScan::OnRemoved (HsvDestination dest,int spid,int key1,int key2,int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key2);
}
