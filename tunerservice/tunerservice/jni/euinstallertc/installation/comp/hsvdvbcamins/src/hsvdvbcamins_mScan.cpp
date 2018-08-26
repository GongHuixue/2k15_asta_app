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
 *     \file          hsvdvbcamins_mScan.c
 *
 *     \brief         -
 *
 */
/*----------------------------------------------------------*
 *
 *     %version:       TVG_Android_1 %
 *     %date_created:  Thu Jan 19 21:07:09 2012 %
 *     %date_modified: Tue Oct 28 19:17:58 2008 %
 *     %derived_by:    lakshminb %
 *
 *
 *############################################################
 */

#include "_hsvdvbcamins_mScan.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbcamins_mScan")



										 


#ifndef __cplusplus

#else

#endif











InstStatus CHsvDvbCamInstallation_mScan_Priv::s__mCamInstStatus;




/*****   static variables   *****/
t_CamDSDesc CHsvDvbCamInstallation_mScan_Priv::s__mCamDSDesc;

Pump CHsvDvbCamInstallation_mScan_Priv::s__mScanPump,CHsvDvbCamInstallation_mScan_Priv::s__mCamDataPump;

Op_ProfileStatusInfo CHsvDvbCamInstallation_mScan_Priv::s__mStatusInfo;

Op_ProfileStatusInfo CHsvDvbCamInstallation_mScan_Priv::s__mTempStatusInfo;

Op_ProfileTuneData *CHsvDvbCamInstallation_mScan_Priv::s__mTempTuneDataPtr = NULL;

Op_Search_Settings CHsvDvbCamInstallation_mScan_Priv::s__mSearchSettings;

Op_Tune_Status *CHsvDvbCamInstallation_mScan_Priv::s__mTempTuneReplyDataPtr = NULL;

ModuleLifeCycle CHsvDvbCamInstallation_mScan_Priv::s__mModuleLifeCycle = TurnedOff;


/*****   Module Pump Handler Functions   *****/



/*****   mScanPump Functions   *****/






/*****   Cam Data communication functions   *****/













/*****   Validate Descriptor Parameters Functions   *****/





/*****   Strapi data related functions    *****/





/*****   Tuner & decoder related functions   *****/






/*****   Init & Utility functions   *****/




/* Parser code implemented in hsvdvbcamnit inside sdm component */

			


const FunctionNat32 CHsvDvbCamInstallation_mScan_Priv::EventActionMatrix[][StMax] =
{
							  /* StIdle,                		StInit,               		  StTunerWait,          		StStrapiWait             		*/
    /* EvStart */             {  FNADDR(FuncStartInstallation), NULL,                 		  NULL,                 		NULL                    		},
    /* EvStop */              {  NULL,                  		FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation), FNADDR(FuncStopInstallation)    },
    /* EvStationFound */      {  NULL,                  		NULL,                 		  FNADDR(FuncStationFound),     NULL                    		},
    /* EvMakeDecision */   	  {  NULL,                  		NULL,                 		  FNADDR(FuncMakeDecision),  	FNADDR(FuncMakeDecision)        },
    /* EvDataAvailable */     {  NULL,                  		NULL,                 		  NULL,                 	 	FNADDR(FuncDataAvailable)       },
};


void CHsvDvbCamInstallation_mScan_Priv::mScanPumpHandler(int event, Nat32 param)
{
	TraceDebug(m,"@ %d event %d state %d - %s\n", __LINE__, event, GET_INS_STATE, (EventActionMatrix[event][GET_INS_STATE] == NULL)?"Ignored":"Handled");
    if(VALID_EVENT(event) && VALID_STATE(GET_INS_STATE))
    {
        TraceDebug(m,"@ %d event %d state %d - %s\n", __LINE__, event, GET_INS_STATE, (EventActionMatrix[event][GET_INS_STATE] == NULL)?"Ignored":"Handled");
        if(EventActionMatrix[event][GET_INS_STATE] != NULL)
        {
            FPCALL(EventActionMatrix[event][GET_INS_STATE])(param);
        }
    }
    UNUSED(param);
}

void CHsvDvbCamInstallation_mScan_Priv::FuncStartInstallation(Nat32 Param)
{
    //ibckg_StopInstallation();
	mInitialise();
	
	TraceDebug(m,"%s %d state %d", __FUNCTION__, __LINE__, GET_INS_STATE);
	SET_CAM_INS_MODE(AUTO_CAM_MODE);
	
	mStopSdm(HsvDmxMain);
    mctl_Stop(HsvMain);
	
	camena_Enable(HsvDmxMain);
	
	SET_INS_STATE(StInit);
	opins_RequestStatusInfo();
	
}

void CHsvDvbCamInstallation_mScan_Priv::FuncStopInstallation(Nat32 Param)
{
    mInitialise();
	
	if(TUNING_REQUIRED)
	{
		TraceNotice(m, "%s opins_SendOpSearchCancel called", __FUNCTION__);
		opins_SendOpSearchCancel();
	}
	TraceNotice(m, "%s Installation stopped in CAM component", __FUNCTION__);
    insN_OnEvent(insN_EventInstallationStopped, CURRENT_MODE);
	
	camena_Disable(HsvDmxMain);
}

void CHsvDvbCamInstallation_mScan_Priv::FuncStationFound(Nat32 Param)
{
	/* Naresh: Open point - signal strength is started and queried immediately, should we wait for onMeasReqdy */
    /* Start signal strength measurement */
	sigstr_StartSigStrMeasAll();
	
	mUpdateTuneReplyData(OP_TUNESTATUS_SUCCESS);
	
	pmp_PmpSend(mCamDataPump, EvCamTuneReply, (Nat32)NULL);
}

void CHsvDvbCamInstallation_mScan_Priv::FuncDataAvailable(Nat32 Param)
{
       char charCode[3];
	if(Param == EnmTypeTuneDSDescData)
	{
		/* Tune descriptors is available in strapi database so get them sequentially and tune this is done in make decision with necessary checks done
		   on the descriptor data received from cam */
		mLoadStrapiData();
		
		CURRENT_TS_INDEX = -1;
        
		pmp_PmpSend(mScanPump, EvMakeDecision, (Nat32)NULL);
	}
	else if(Param == EnmTypeCamNITData)
	{
		/* NIT Data Available so build the channel map tables through mDataAcq module */
		if(mLoadStrapiData())
		{
			idataacq_AcquireServiceListData();
			idataacq_AcquireData();
			
			insN_OnEvent(insN_EventChannelFound, rins_InstallationModeCam);
			/*if(idataacq_GetNumberOfDigitalChannelsFound == 0)
			{
				TraceNotice(m, "Number of channels installed is 0.. so stop installation \n");
				insN_OnEvent(insN_EventInstallationStopped, CURRENT_MODE);
			}
			else
			{*/
			TraceNotice(m, "%s Installation Successfully completed in CAM component", __FUNCTION__);
			insN_OnEvent(insN_EventInstallationCompleted, mStatusInfo.op_Status.Profile_Type);
			int networkOperator = ((rins_GetMedium() == rins_Terrestrial) ? rins_DvbTCAM:rins_DvbCCAM);
			idvbset_SetAttribute(AUTO_MODE, rins_AttributeNetworkOperator, networkOperator);
			idvbset_SetAttribute(AUTO_MODE, rins_AttributeCamNITVersion, mStatusInfo.op_Status.NIT_Version);
			charCode[0] = CAM_CHAR_CODE_TYPE;
			charCode[1] = CAM_CHAR_CODE_BYTE2;
			charCode[2] = CAM_CHAR_CODE_BYTE3;
			camacqhelper_SetCharacterCode(charCode);
			camena_Disable(HsvDmxMain);
			
			mInitialise();
			
			opins_CacheOperatorData();
			//}
			pmp_PmpSend(mCamDataPump, EvCamAck, (Nat32)NULL);
		}
	}
}

void CHsvDvbCamInstallation_mScan_Priv::FuncMakeDecision(Nat32 param)
{
	Bool DSDListExhausted = TRUE;
	Bool InvalidParamsFromCam = FALSE;
	
	while(mGetNextDSD())
	{
		/* Entry of Next DSD is available check if it is valid and tune, otherwise iterate for next DSD, continue this until DSD list exhausts */
		if(!mIsValidDeliveryDescriptorType())
		{
			TraceNotice(m, "OP_TUNESTATUS_NOT_SUPPORTED");
			InvalidParamsFromCam = TRUE;
			mUpdateTuneReplyData(OP_TUNESTATUS_NOT_SUPPORTED);
			if(mTempTuneReplyDataPtr->Descriptor_Number != 0xFF){
				DSDListExhausted = FALSE;
			}
//			pmp_PmpSend(mCamDataPump, EvCamTuneReply, (Nat32)NULL);
			break;
		}
		else if(!mIsValidDeliveryDescriptorData())
		{
			TraceNotice(m, "OP_TUNESTATUS_INVALID");
			InvalidParamsFromCam = TRUE;
			mUpdateTuneReplyData(OP_TUNESTATUS_INVALID);
			if(mTempTuneReplyDataPtr->Descriptor_Number != 0xFF){
				DSDListExhausted = FALSE;
			}
//			pmp_PmpSend(mCamDataPump, EvCamTuneReply, (Nat32)NULL);
			break;
		}
		else
		{
			/* Tune to the next entry of the tuning descriptor */
			mSelectDecoder();       /* Select the DVBC decoder */
			mSetTunerAttributes();  /* Make the Tuner ready */
			
			DSDListExhausted = FALSE;
			break;
		}
	}
	
	if(DSDListExhausted == TRUE)
	{
		if(!mIsValidDeliveryDescriptorType())
		{
			InvalidParamsFromCam = TRUE;
			mUpdateTuneReplyData(OP_TUNESTATUS_NOT_SUPPORTED);
		}
		else if(!mIsValidDeliveryDescriptorData())
		{
			InvalidParamsFromCam = TRUE;
			mUpdateTuneReplyData(OP_TUNESTATUS_INVALID);
		}

	
		if(InvalidParamsFromCam == FALSE)
		{
			mUpdateTuneReplyData(OP_TUNESTATUS_FAILED);
		}
		TraceNotice(m, "DSD List Exhausted so send the CAM with tune fail reply with appropriate values that are cached previously ");
		
	}
	if(DSDListExhausted == TRUE || InvalidParamsFromCam == TRUE)
	{
		TraceNotice(m, "Sending Tune status because DSDListExhausted is %d  & InvalidParamsFromCam is %d\n",DSDListExhausted,InvalidParamsFromCam);
		//InvalidParamsFromCam = FALSE;
		pmp_PmpSend(mCamDataPump, EvCamTuneReply, (Nat32)NULL);
	}
}

void CHsvDvbCamInstallation_mScan_Priv::mSelectDecoder(void)
{
	/* Check where the decoder is moved and implement to select the right decoder */
}

void CHsvDvbCamInstallation_mScan_Priv::mSetTunerAttributes(void)
{
    Nat32 errorcode = TM_OK;
    
	SET_INS_STATE(StTunerWait);	
    switch(CURRENT_DSD_TYPE)
	{
		case HSVSPID(CamNITCableDS, dvb, camnit):
		
			feapi_SetConstellation(WINDOWID, feapi_ChanDecDvbC, (tmFe_Constellation_t)CURRENT_MODULATION, &errorcode);
			TraceNotice(m, "plf call SetConstellation with %d returns errorcode %ld", CURRENT_MODULATION, errorcode);

			feapi_SetSymbolRate(WINDOWID, CURRENT_SYMBOL_RATE, &errorcode);
			TraceNotice(m, "plf call SetStreamPriority with %ld returns errorcode %ld", CURRENT_SYMBOL_RATE, errorcode);

			feapi_SetFreq (WINDOWID, CURRENT_FREQUENCY, FALSE, &errorcode);
			TraceNotice(m, "plf call feapi_SetFreq with %ld returns errorcode %ld", CURRENT_FREQUENCY, errorcode);
			
			break;
		case HSVSPID(CamNITTerrestrialDS, dvb, camnit):
			
			feapi_SetStreamPriority(WINDOWID, (tmFe_StreamPriority_t)CURRENT_STREAM_PRIORITY, &errorcode);	
			TraceNotice(m, "plf call SetStreamPriority with %d returns errorcode %ld", CURRENT_STREAM_PRIORITY, errorcode);
			
			feapi_SetChanBandwidth(WINDOWID, (tmFe_ChanBandwidth_t)CURRENT_BANDWIDTH, &errorcode);
			TraceNotice(m, "plf call SetChanBandwidth with %d returns errorcode %ld", CURRENT_BANDWIDTH, errorcode);
			
			feapi_SetFreq (WINDOWID, CURRENT_FREQUENCY, FALSE, &errorcode);
			TraceNotice(m, "plf call SetFreq with %ld returns errorcode %ld", CURRENT_FREQUENCY, errorcode);
			
			break;
		case HSVSPID(CamNITT2DS, dvb, camnit):
			
			errorcode = chdecdvbt2_SelectPlpId(WINDOWID, CURRENT_PLP_ID);
			TraceNotice(m, "plf call SelectPlpId with %d returns errorcode %ld", CURRENT_PLP_ID, errorcode);
			
			feapi_SetChanBandwidth(WINDOWID, (tmFe_ChanBandwidth_t)CURRENT_BANDWIDTH, &errorcode);
			TraceNotice(m, "plf call SetChanBandwidth with %d returns errorcode %ld", CURRENT_BANDWIDTH, errorcode);
			
			feapi_SetFreq (WINDOWID, CURRENT_FREQUENCY, FALSE, &errorcode);
			TraceNotice(m, "plf call SetFreq with %ld returns errorcode %ld", CURRENT_FREQUENCY, errorcode);
			
			break;			
		case HSVSPID(CamNITC2DS, dvb, camnit):
			/* C2 DSD present in CAMNIT => DVBC2 decoder type */
			/* To be used in future */
			break;
		default:
			break;
	}	   
}

void CHsvDvbCamInstallation_mScan_Priv::mStopSdm(HsvDemux dmx)
{
    if(ctrl_GetMode(dmx) != ctrl_Idle)
    {
        ctrl_StopCollection(dmx);
    }
}

Bool CHsvDvbCamInstallation_mScan_Priv::mGetNextDSD(void)
{
    Bool retval = TRUE;
	int count = 0;

	TraceNotice(m, "%s mCamDSDesc.NumOfTs %d", __FUNCTION__, mCamDSDesc.NumOfTs);
    if(mCamDSDesc.NumOfTs > 0) 
    {
		TraceNotice(m, "%s mCamDSDesc.NumOfTs %d CURRENT_TS_INDEX %d", __FUNCTION__, mCamDSDesc.NumOfTs, CURRENT_TS_INDEX);
        if(CURRENT_TS_INDEX >= 0)
        {
			TraceNotice(m, "%s mCamDSDesc.NumOfTs %d CURRENT_TS_INDEX %d %d %d", __FUNCTION__, mCamDSDesc.NumOfTs, CURRENT_TS_INDEX, mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex, mCamDSDesc.TsParam[CURRENT_TS_INDEX].NumOfDSD);
            if (mCamDSDesc.TsParam[CURRENT_TS_INDEX].NumOfDSD > 0) 
            {
                if((mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex + 1) == mCamDSDesc.TsParam[CURRENT_TS_INDEX].NumOfDSD)
                {
					TraceNotice(m, "%s mCamDSDesc.NumOfTs %d CURRENT_TS_INDEX %d %d %d", __FUNCTION__, mCamDSDesc.NumOfTs, CURRENT_TS_INDEX, mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex, mCamDSDesc.TsParam[CURRENT_TS_INDEX].NumOfDSD);
                    if((CURRENT_TS_INDEX + 1) == mCamDSDesc.NumOfTs)
                    {
                        retval = FALSE;
                    }
                    else
                    {
                        CURRENT_TS_INDEX++;
                        mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex = 0;
						TraceNotice(m, "%s mCamDSDesc.NumOfTs %d CURRENT_TS_INDEX %d %d %d", __FUNCTION__, mCamDSDesc.NumOfTs, CURRENT_TS_INDEX, mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex, mCamDSDesc.TsParam[CURRENT_TS_INDEX].NumOfDSD);
                    }
                }
                else
                {
                    mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex++;
					TraceNotice(m, "%s mCamDSDesc.NumOfTs %d CURRENT_TS_INDEX %d %d %d", __FUNCTION__, mCamDSDesc.NumOfTs, CURRENT_TS_INDEX, mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex, mCamDSDesc.TsParam[CURRENT_TS_INDEX].NumOfDSD);
                }
            }
            else 
            {
                retval = FALSE;
                TraceDebug(m,"mCamDSDesc.TsParam[CURRENT_TS_INDEX].NumOfDSD is Zero\r\n");
            }
        }
        else
        {
            CURRENT_TS_INDEX = 0;
            mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex = 0;
			TraceNotice(m, "%s mCamDSDesc.NumOfTs %d CURRENT_TS_INDEX %d %d %d", __FUNCTION__, mCamDSDesc.NumOfTs, CURRENT_TS_INDEX, mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex, mCamDSDesc.TsParam[CURRENT_TS_INDEX].NumOfDSD);
        }
    }
    else 
    {
        retval = FALSE;
        TraceNotice(m,"mCamDSDesc.NumOfTs is Zero\n");
    }
	
    return retval;
}

void CHsvDvbCamInstallation_mScan_Priv::mGetPTCInfo(HsvInstallationPTC *ptc, Nat16 OnId, Nat16 TsId)
{
    int i = 0;

    for(i = 0; i < mCamDSDesc.NumOfTs; i++ )
    {
        if( (mCamDSDesc.TsParam[i].ONID == OnId) && (mCamDSDesc.TsParam[i].TsId == TsId) )
        {
            ptc->Frequency          = ((mCamDSDesc.TsParam[i].DSDesc[0].Frequency/16)*1000);
            ptc->SymbolRate         = mCamDSDesc.TsParam[i].DSDesc[0].SymbolRate;
            ptc->ModulationType     = mCamDSDesc.TsParam[i].DSDesc[0].Modulation;
			ptc->DecoderType        = mMapDSDTypeToChanDecoder(mCamDSDesc.TsParam[i].DSDesc[0].DSDType);
			ptc->ChannelBandwidth   = mCamDSDesc.TsParam[i].DSDesc[0].Bandwidth;
			//ptc->SystemId			= mCamDSDesc.TsParam[i].DSDesc[0].SystemId;				/* Used for DVBC2 */
			ptc->StreamPriority     = (ptc->DecoderType == feapi_ChanDecDvbT2)? (mCamDSDesc.TsParam[i].DSDesc[0].PLP_Id) : (mCamDSDesc.TsParam[i].DSDesc[0].Priority);
			
			TraceNotice(m, "%s %d %d %d %d", __FUNCTION__, mCamDSDesc.TsParam[i].DSDesc[0].SymbolRate, mCamDSDesc.TsParam[i].DSDesc[0].Frequency, mCamDSDesc.TsParam[i].DSDesc[0].Bandwidth, ptc->DecoderType);
			break;
        }
    }
    ptc->CodeRateHigh       =   ptc->CodeRateLow = HsvCodeRateAuto;
    ptc->ChannelInformation =   ptc->TimeError   = ptc->FrequencyError = ptc->FrequencyOffset = 0;
    ptc->HierarchyMode      =   HsvHierarchyNone;
    ptc->GuardInterval      =   HsvGuardIntervalAuto;
    ptc->TxMode             =   HsvTxModeAuto;           
    ptc->IqMode             =   HsvIqModeNormal;
    ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
    ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
    ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);
    
}

Bool CHsvDvbCamInstallation_mScan_Priv::mLoadStrapiData(void)
{
	Bool retval = FALSE;
	HSVSPTYPE(CamNITCableDS, dvb, camnit) 		TempCDSDesc;
	HSVSPTYPE(CamNITC2DS, dvb, camnit) 			TempC2DSDesc;
	HSVSPTYPE(CamNITT2DS, dvb, camnit) 			TempT2DSDesc;
	HSVSPTYPE(CamNITTerrestrialDS, dvb, camnit) TempTDSDesc;
	
    if(CABLE_MEDIUM)
	{
		retval = mLoadDSDFromStrapi(HSVSPID(CamNITCableDS, dvb, camnit), &TempCDSDesc);
		retval |= mLoadDSDFromStrapi(HSVSPID(CamNITC2DS, dvb, camnit), &TempC2DSDesc);		
	}
	else
	{
		retval = mLoadDSDFromStrapi(HSVSPID(CamNITTerrestrialDS, dvb, camnit), &TempTDSDesc);
		retval |= mLoadDSDFromStrapi(HSVSPID(CamNITT2DS, dvb, camnit), &TempT2DSDesc);
	}
	
	TraceNotice(m,"%s retval %d\n", __FUNCTION__, retval);
	return retval;
}

Bool CHsvDvbCamInstallation_mScan_Priv::mLoadDSDFromStrapi(int hsvspid, Address TempDSDesc)
{
	int i = 0, j = 0, dbindex;
	
	mCamDSDesc.NumOfTs += strapi_GetSize(HsvMain, hsvspid);
	if(mCamDSDesc.NumOfTs > MAX_MUXES_PER_NTK_FOR_CAM)
    {
        TraceNotice(m,"%s %d NumofDSD > MAX_MUXES_PER_NTK => (%d > %d)\n", __FUNCTION__, __LINE__, mCamDSDesc.NumOfTs, MAX_MUXES_PER_NTK_FOR_CAM);
        mCamDSDesc.NumOfTs = MAX_MUXES_PER_NTK_FOR_CAM;
    }
	
	TraceNotice(m,"%s %d mCamDSDesc.NumOfTs %d\n", __FUNCTION__, __LINE__, mCamDSDesc.NumOfTs);
	
    for(dbindex = (mCamDSDesc.NumOfTs - 1); dbindex >= 0; dbindex--)
    {
        if(strapi_GetByIndex(HsvMain, hsvspid, dbindex, TempDSDesc))
        {
            mCamDSDesc.TsParam[i].NumOfDSD = mGetNumOfDSD(hsvspid, TempDSDesc);
	
			TraceNotice(m,"%s %d mCamDSDesc.NumOfTs %d %d\n", __FUNCTION__, __LINE__, mCamDSDesc.NumOfTs, mCamDSDesc.TsParam[i].NumOfDSD);
			for(j = 0; j < mCamDSDesc.TsParam[i].NumOfDSD; j++)
            {
                switch(hsvspid)
				{
					case HSVSPID(CamNITCableDS, dvb, camnit):
						{
							HSVSPTYPE(CamNITCableDS, dvb, camnit) *TempCDSDesc = (HSVSPTYPE(CamNITCableDS, dvb, camnit) *) TempDSDesc;
							mCamDSDesc.TsParam[i].DSDesc[j].Frequency  = TempCDSDesc->DSD[j].Frequency;
							mCamDSDesc.TsParam[i].DSDesc[j].SymbolRate = TempCDSDesc->DSD[j].SymbolRate;
							mCamDSDesc.TsParam[i].DSDesc[j].Modulation = TempCDSDesc->DSD[j].Modulation;
							mCamDSDesc.TsParam[i].ONID 				   = TempCDSDesc->OriginalNetworkId;
							mCamDSDesc.TsParam[i].TsId 				   = TempCDSDesc->TsId;
							mCamDSDesc.TsParam[i].DSDesc[j].DSDType	   = HSVSPID(CamNITCableDS, dvb, camnit);
							TraceNotice(m," DSD => Frequency %ld Modulation %d SymbolRate %ld>\n", (TempCDSDesc->DSD[j].Frequency>>4), TempCDSDesc->DSD[j].Modulation, TempCDSDesc->DSD[j].SymbolRate);
						}
						break;
					case HSVSPID(CamNITTerrestrialDS, dvb, camnit):
						{
							HSVSPTYPE(CamNITTerrestrialDS, dvb, camnit) *TempTDSDesc = (HSVSPTYPE(CamNITTerrestrialDS, dvb, camnit) *) TempDSDesc;
							
							mCamDSDesc.TsParam[i].DSDesc[j].Frequency  = TempTDSDesc->DSD[j].Frequency;
							mCamDSDesc.TsParam[i].DSDesc[j].Bandwidth  = TempTDSDesc->DSD[j].Bandwidth;
							mCamDSDesc.TsParam[i].DSDesc[j].Priority   = TempTDSDesc->DSD[j].Priority;
							mCamDSDesc.TsParam[i].DSDesc[j].Modulation = TempTDSDesc->DSD[j].Modulation;
							mCamDSDesc.TsParam[i].ONID 				   = TempTDSDesc->OriginalNetworkId;
							mCamDSDesc.TsParam[i].TsId 				   = TempTDSDesc->TsId;
							mCamDSDesc.TsParam[i].DSDesc[j].DSDType	   = HSVSPID(CamNITTerrestrialDS, dvb, camnit);
							TraceNotice(m," DSD => i %d j %d Frequency %ld Bandwidth %d Priority %d>\n", i, j, (TempTDSDesc->DSD[j].Frequency>>4), TempTDSDesc->DSD[j].Bandwidth, TempTDSDesc->DSD[j].Priority);
						}
						break;
					case HSVSPID(CamNITT2DS, dvb, camnit):
						{
							HSVSPTYPE(CamNITT2DS, dvb, camnit) *TempT2DSDesc = (HSVSPTYPE(CamNITT2DS, dvb, camnit) *) TempDSDesc;
							
							mCamDSDesc.TsParam[i].DSDesc[j].Frequency  = TempT2DSDesc->DSD[j].Frequency;
							mCamDSDesc.TsParam[i].DSDesc[j].Bandwidth  = TempT2DSDesc->DSD[j].Bandwidth;
							mCamDSDesc.TsParam[i].DSDesc[j].PLP_Id     = TempT2DSDesc->DSD[j].PLP_Id;
							mCamDSDesc.TsParam[i].ONID 				   = TempT2DSDesc->OriginalNetworkId;
							mCamDSDesc.TsParam[i].TsId 				   = TempT2DSDesc->TsId;
							mCamDSDesc.TsParam[i].DSDesc[j].DSDType	   = HSVSPID(CamNITT2DS, dvb, camnit);
							TraceNotice(m," DSD => Frequency %ld Bandwidth %d PLP_Id %d>\n", (TempT2DSDesc->DSD[j].Frequency>>4), TempT2DSDesc->DSD[j].Bandwidth, TempT2DSDesc->DSD[j].PLP_Id);
						}
						break;
					case HSVSPID(CamNITC2DS, dvb, camnit):
						{
							HSVSPTYPE(CamNITC2DS, dvb, camnit) *TempC2DSDesc = (HSVSPTYPE(CamNITC2DS, dvb, camnit) *) TempDSDesc;
							
							mCamDSDesc.TsParam[i].DSDesc[j].Frequency  = TempC2DSDesc->DSD[j].Frequency;
							mCamDSDesc.TsParam[i].DSDesc[j].SystemId   = TempC2DSDesc->DSD[j].SystemId;
							mCamDSDesc.TsParam[i].DSDesc[j].PLP_Id     = TempC2DSDesc->DSD[j].PLP_Id;
							mCamDSDesc.TsParam[i].ONID 				   = TempC2DSDesc->OriginalNetworkId;
							mCamDSDesc.TsParam[i].TsId 				   = TempC2DSDesc->TsId;
							mCamDSDesc.TsParam[i].DSDesc[j].DSDType	   = HSVSPID(CamNITC2DS, dvb, camnit);
							TraceNotice(m," DSD => Frequency %ld PLP_Id %d SystemId %d>\n", (TempC2DSDesc->DSD[j].Frequency>>4), TempC2DSDesc->DSD[j].PLP_Id, TempC2DSDesc->DSD[j].SystemId);
						}
						break;
				}
			}
			i++;
        }
        else
        {
            //TraceErr(m,"%s %d strapi_GetByIndex failed for pid %d index %d\n", __FUNCTION__, __LINE__, hsvspid, i);
        }
    }

    return ((mCamDSDesc.NumOfTs == 0)? FALSE: TRUE);
}

int CHsvDvbCamInstallation_mScan_Priv::mGetNumOfDSD(int hsvspid, void *DSDesc)
{
	int retval = 0;
	
	TraceNotice(m,"%s hsvspid %d retval %d\n", __FUNCTION__, hsvspid, retval);
	switch(hsvspid)
	{
		case HSVSPID(CamNITCableDS, dvb, camnit):
			{
				HSVSPTYPE(CamNITCableDS, dvb, camnit) *TempCDSDesc = (HSVSPTYPE(CamNITCableDS, dvb, camnit) *) DSDesc;
				
				retval = TempCDSDesc->NumOfDSD;
			}
			break;
		case HSVSPID(CamNITTerrestrialDS, dvb, camnit):
			{
				HSVSPTYPE(CamNITTerrestrialDS, dvb, camnit) *TempTDSDesc = (HSVSPTYPE(CamNITTerrestrialDS, dvb, camnit) *) DSDesc;
				
				retval = TempTDSDesc->NumOfDSD;
			}
			break;
		case HSVSPID(CamNITT2DS, dvb, camnit):
			{
				HSVSPTYPE(CamNITT2DS, dvb, camnit) *TempT2DSDesc = (HSVSPTYPE(CamNITT2DS, dvb, camnit) *) DSDesc;
				
				retval = TempT2DSDesc->NumOfDSD;
			}
			break;
		case HSVSPID(CamNITC2DS, dvb, camnit):
			{
				HSVSPTYPE(CamNITC2DS, dvb, camnit) *TempC2DSDesc = (HSVSPTYPE(CamNITC2DS, dvb, camnit) *) DSDesc;
				
				retval = TempC2DSDesc->NumOfDSD;
			}
			break;
	}
	TraceNotice(m,"%s hsvspid %d retval %d\n", __FUNCTION__, hsvspid, retval);
	return retval;
}

int CHsvDvbCamInstallation_mScan_Priv::mMapDSDTypeToChanDecoder(int DSDType)
{
	/* Get it from DSD descriptors stored in strapi from CAMNIT population */
	int DecoderType = 0;
	
	switch(DSDType)
	{
		case HSVSPID(CamNITCableDS, dvb, camnit):
			DecoderType = feapi_ChanDecDvbC;
			break;
		case HSVSPID(CamNITTerrestrialDS, dvb, camnit):
			DecoderType = feapi_ChanDecDvbT;
			break;
		case HSVSPID(CamNITT2DS, dvb, camnit):
			DecoderType = feapi_ChanDecDvbT2;
			break;
		case HSVSPID(CamNITC2DS, dvb, camnit):
			/* C2 DSD present in CAMNIT => DVBC2 decoder type */
			/* To be used in future */
			break;
		default:
			break;
	}
	
	TraceNotice(m, "%s %d %d", __FUNCTION__, DecoderType, DSDType);
	return DecoderType;
}

void* CHsvDvbCamInstallation_mScan_Priv::mGetLocalBuffer(int size)
{
	void* Buffer	=	malloc(size);
	
	if(Buffer == NULL)
	{
		TraceErr(m, "malloc failure %d from 0x%x", size, (unsigned int)__builtin_return_address(0));
	}
	
	return Buffer;
}

void* CHsvDvbCamInstallation_mScan_Priv::mReturnLocalBuffer(void **Buffer)
{
	if(*Buffer != NULL){
		free(*Buffer);
		*Buffer = NULL;
	}
	return NULL;
}

Bool CHsvDvbCamInstallation_mScan_Priv::mIsValidDeliveryHint(int DeliveryHint)
{
	Bool retval = FALSE;
	
	if((ANTENNA_MEDIUM && (DeliveryHint & 0b0100)) || (CABLE_MEDIUM && (DeliveryHint & 0b0001)))
	{
		retval = TRUE;
	}
	
	return retval;
}

Bool CHsvDvbCamInstallation_mScan_Priv::mIsValidDeliveryDescriptorType()
{
	Bool retval = FALSE;
	int dsdtype = 0;
	if(mCamDSDesc.NumOfTs > 0)
	dsdtype = CURRENT_DSD_TYPE;	
	else
	dsdtype = mTempTuneDataPtr->TuneData[0];
	switch(dsdtype)
	{
		case HSVSPID(CamNITCableDS, dvb, camnit):
			/* DVBC */
			retval = (CABLE_MEDIUM)?TRUE : FALSE;
			break;
		case HSVSPID(CamNITTerrestrialDS, dvb, camnit):
		case HSVSPID(CamNITT2DS, dvb, camnit):
			/* DVBT or T2 */
			retval = (ANTENNA_MEDIUM)?TRUE : FALSE;
			break;
		case HSVSPID(CamNITC2DS, dvb, camnit):
			/* C2 not supported at this moment */
		default:
			/* Satellite not supported in euinstallerTC */
			break;
	}
	
	return retval;
}

Bool CHsvDvbCamInstallation_mScan_Priv::mIsValidDeliveryDescriptorData(void)
{
	Bool retval = FALSE;
	int dsdtype = 0;
	if(mCamDSDesc.NumOfTs > 0)
	dsdtype = CURRENT_DSD_TYPE;	
	else
	dsdtype = mTempTuneDataPtr->TuneData[0];	
	switch(dsdtype)
	{
		case HSVSPID(CamNITCableDS, dvb, camnit):
			retval = mValidateCDS();
			TraceNotice(m,"%s %d", __FUNCTION__, retval);
			break;
		case HSVSPID(CamNITTerrestrialDS, dvb, camnit):
			retval = mValidateTerrestrialDS();
			TraceNotice(m,"%s %d", __FUNCTION__, retval);
			break;
		case HSVSPID(CamNITT2DS, dvb, camnit):
			retval = mValidateT2DS();
			TraceNotice(m,"%s %d", __FUNCTION__, retval);
			break;
		case HSVSPID(CamNITC2DS, dvb, camnit):
			retval = mValidateC2DS();
			TraceNotice(m,"%s %d", __FUNCTION__, retval);
		default:
			/* Satellite not supported in euinstallerTC */
			break;
	}
	TraceNotice(m,"%s %d %d", __FUNCTION__, retval, CURRENT_DSD_TYPE);	
	return retval;
}

/* Validate Parameters Functions */
Bool CHsvDvbCamInstallation_mScan_Priv::mValidateCDS(void)
{
	Bool retval = FALSE;
	
	if( (CURRENT_SYMBOL_RATE > 0) && (CURRENT_MODULATION != HsvUnknownConstellation) && \
	    (CURRENT_FREQUENCY >= START_FREQUENCY) && (CURRENT_FREQUENCY <= END_FREQUENCY) )
    {
        TraceNotice(m,"SymbolRate %ld Modulation %d Frequency %ld", CURRENT_SYMBOL_RATE, CURRENT_MODULATION, CURRENT_FREQUENCY);
        retval = TRUE;
    }
	
	return retval;
}
Bool CHsvDvbCamInstallation_mScan_Priv::mValidateTerrestrialDS(void)
{
	Bool retval = FALSE;
	
	TraceNotice(m,"Bandwidth %d  Frequency %ld", CURRENT_BANDWIDTH, CURRENT_FREQUENCY);
	if( (CURRENT_BANDWIDTH > 0) && (CURRENT_FREQUENCY >= START_FREQUENCY) && (CURRENT_FREQUENCY <= END_FREQUENCY) )
    {
        TraceNotice(m,"Bandwidth %d  Frequency %ld", CURRENT_BANDWIDTH, CURRENT_FREQUENCY);
        retval = TRUE;
    }
	
	return retval;
}

Bool CHsvDvbCamInstallation_mScan_Priv::mValidateT2DS(void)
{
	Bool retval = FALSE;
	
	if( (CURRENT_FREQUENCY >= START_FREQUENCY) && (CURRENT_FREQUENCY <= END_FREQUENCY) )
    {
        TraceNotice(m,"PLP_Id %d Frequency %ld", CURRENT_PLP_ID, CURRENT_FREQUENCY);
        retval = TRUE;
    }
	
	return retval;
}

Bool CHsvDvbCamInstallation_mScan_Priv::mValidateC2DS(void)
{
	Bool retval = FALSE;
	
	/* Do Nothing */
	
	return retval;
}

void CHsvDvbCamInstallation_mScan_Priv::mCamDataPumpHandler(int event, Nat32 param)
{
	TraceNotice(m, "%s event %d", __FUNCTION__, event);
       TraceNotice(m, "GET_INS_STATE = %d\n",GET_INS_STATE);
	
	switch(event)
	{
		case EvCamSearchStatus:
			
			mCamSearchStatus((Op_ProfileSearchStatus *) param);
			mReturnLocalBuffer((void **)&param);
			break;
		case EvCamStatusInfo:
		       TraceNotice(m, "GET_INS_STATE = %d\n",GET_INS_STATE);
			/* Copy to static module variable */
			mStatusInfo = *(Op_ProfileStatusInfo *) param;
			mCamStatusInfo();
			//mTempStatusInfo = *(Op_ProfileStatusInfo *) param;	//CAM_UPDATED_NIT_VERSION
			mReturnLocalBuffer((void **)&param);
			break;
		case EvCamNITReceived:
			
			mCamNITReceived((Op_ProfileNitData *) param);
			mReturnLocalBuffer((void **)&param);
			break;
		case EvCamTuneRequest:
			
			mTempTuneDataPtr = (Op_ProfileTuneData *) param;
			
			/* create & init the buffer for reply data which will be sent to cam in tune status reply */
			mTempTuneReplyDataPtr = (Op_Tune_Status *) mGetLocalBuffer(sizeof(Op_Tune_Status));
			memset(mTempTuneReplyDataPtr, 0, sizeof(Op_Tune_Status));
			
			mCamTuneRequest((Op_ProfileTuneData *) param);
			/* Do not free both the temp buffer here, as we need the descriptor data to be passed in the tune reply, 
			   the free of this buffer is done when below event (EvCamTuneReply) occurs */
			
			break;
		case EvCamTuneReply:
		
			mCamTuneReply();
			
			memset((Address)(&mCamDSDesc), 0, sizeof(mCamDSDesc));
			mReturnLocalBuffer((void **)&mTempTuneDataPtr);
			mReturnLocalBuffer((void **)&(mTempTuneReplyDataPtr->Descriptor_Loop));
			mReturnLocalBuffer((void **)&mTempTuneReplyDataPtr);
			break;
		case EvCamAck:
			/* Acknowledge the handled entitlement change as we have honoured the CAM installation request with tuning and with CAMNIT */
			if(ENTITLEMENT_CHANGE_REQUESTED)
			{
				TraceNotice(m, "%s opins_SendOpAck called", __FUNCTION__);
				opins_SendOpAck();
			}
		default:
			break;
	}
}

void CHsvDvbCamInstallation_mScan_Priv::mCamSearchStatus(Op_ProfileSearchStatus *TempSearchStatusInfo)
{
       char charCode[3];
	if(TempSearchStatusInfo->op_Status.Error_Flag != 0)//For fixing 7.2.4
	{
	   TraceNotice(m, "Error flag returned.. so stop installation proceeded\n");
	   insN_OnEvent(insN_EventInstallationStopped, CURRENT_MODE);
	}
	else if(NIT_REQUIRED(TempSearchStatusInfo->op_Status.NIT_Version) ||((mStatusInfo.op_Status.Profile_Type == OP_PROFILE_TYPE_1) && (AUTO_INSTALL))) //to resolve 7.2.6.1 [Initial_DTVL_Cases
	{
		TraceNotice(m, "%s opins_RequestNit called", __FUNCTION__);
		opins_RequestNit();
		mStatusInfo.op_Status.NIT_Version = TempSearchStatusInfo->op_Status.NIT_Version;
	}
	else
	{
		TraceNotice(m, "%s Nit Not requested New NITVersion %d CAM Updated NITVersion %d", __FUNCTION__, TempSearchStatusInfo->op_Status.NIT_Version, CAM_UPDATED_NIT_VERSION);
		
		/* Acknowledge the handled entitlement change as we have honoured the CAM installation request with tuning, 
		   However it did not send the updated NIT version, perhaps it already has it or it is profile 0 CAM.. */
		if(ENTITLEMENT_CHANGE_REQUESTED) //&& (mStatusInfo.op_Status.Profile_Type == OP_PROFILE_TYPE_1))
		{
			TraceNotice(m, "%s opins_SendOpAck called", __FUNCTION__);
			opins_SendOpAck();
		}		
		

		insN_OnEvent(insN_EventChannelFound, rins_InstallationModeCam);
			
		TraceNotice(m, "%s Installation Successfully completed in CAM component", __FUNCTION__);
		insN_OnEvent(insN_EventInstallationCompleted, mStatusInfo.op_Status.Profile_Type);
		int networkOperator = ((rins_GetMedium() == rins_Terrestrial) ? rins_DvbTCAM:rins_DvbCCAM);
		idvbset_SetAttribute(AUTO_MODE, rins_AttributeNetworkOperator, networkOperator);
		idvbset_SetAttribute(AUTO_MODE, rins_AttributeCamNITVersion, TempSearchStatusInfo->op_Status.NIT_Version);
		charCode[0] = CAM_CHAR_CODE_TYPE;
		charCode[1] = CAM_CHAR_CODE_BYTE2;
		charCode[2] = CAM_CHAR_CODE_BYTE3;
		camacqhelper_SetCharacterCode(charCode);
		camena_Disable(HsvDmxMain);
		
		mInitialise();
	}
}

void CHsvDvbCamInstallation_mScan_Priv::mCamStatusInfo(void)
{
       TraceNotice(m, "GET_INS_STATE = %d\n",GET_INS_STATE);
	   TraceNotice(m, "ENTITLEMENT_CHANGE_REQUESTED = %d\n",ENTITLEMENT_CHANGE_REQUESTED);
	Bool Proceed = TRUE;
	
	/* Check for error conditions whether to proceed or not */
	if((mIsValidDeliveryHint(GET_CAM_DELIVERY_HINT) == FALSE) || (!PROFILE_INFO_VALID))
	{
		Proceed = FALSE;
		
		TraceErr(m, "Unsupported delivery System %d sent from CAM or Info valid flag is %d ", GET_CAM_DELIVERY_HINT,mStatusInfo.op_Info.info_Valid);		
		if(AUTO_INSTALL)
		{
			pmp_PmpSend(mScanPump, EvStop, (Nat32)NULL);
		}
	}
	
	if(Proceed)
	{
		if(SCHEDULE_UPDATE && (GET_INS_STATE == StIdle))
		{
			/* Schedule update request has come don't take any action here as alarm will be triggered in uper layer and later we get startinstallation trigger */
			TraceNotice(m, "Schedule update request has come don't take any action here as alarm will be triggered in uper layer and later we get startinstallation trigger");
		}
		else
		{
			if((CAM_INITIALISED == FALSE) || (TUNING_REQUIRED))
			{
				TraceNotice(m, "%s:%d", __FUNCTION__, __LINE__);
				/* First time CAM has sent the profile request so honour the request and ignore other flags, or tuning required flag is true */
				
				/* if StIdle Background installation trigger from the cam same rules are followed for both auto & background except that with insN event UI is displayed in latter case */
				if(GET_INS_STATE == StIdle )//&& (sysset_GetOperatorCable() == 6))//Operator Profile - 6
				{
				    if(idvbset_IsAvailable(AUTO_MODE, rins_AttributeNetworkOperator))
					{
						TraceNotice(m, "%s:%d", __FUNCTION__, __LINE__);
						SET_CAM_INS_MODE(BACKGROUND_CAM_MODE);
					 	if(URGENT_TUNING_REQUIRED)
					 	{
							insN_OnEvent(insN_EventCamInstallRequestUrgent, CURRENT_MODE); //Trigger Urgent Installation as CICAM needs it to be urgent mode installation
					 	}
						else if(ADVANCE_TUNING_REQUIRED)
					 	{
					 		insN_OnEvent(insN_EventCamInstallRequestNormal, CURRENT_MODE); //Get acknowledgement from user for OP installation
					 	}
					}
				}
				else
				{
					TraceNotice(m, "%s:%d", __FUNCTION__, __LINE__);
					insN_OnEvent(insN_EventInstallationStarted, CURRENT_MODE);				
					TraceNotice(m, "%s opins_SendOperatorSearchStart called", __FUNCTION__);
					TraceNotice(m, "Values are \n");
					TraceNotice(m, "Delivery data length %d Unattented Mode %d Delivery data %d App length %d App data %d service length %d Service data %s",mSearchSettings.Delivery_Cap_Length,mSearchSettings.Unattended_Flag,mSearchSettings.Delivery_Capability,mSearchSettings.Application_Cap_Length,mSearchSettings.Application_Capability,mSearchSettings.Service_Type_Length,mSearchSettings.Service_Type);
					opins_SendOperatorSearchStart(mSearchSettings);
			              char charCode[3];
					charCode[0] = CAM_CHAR_CODE_TYPE;
					charCode[1] = CAM_CHAR_CODE_BYTE2;
					charCode[2] = CAM_CHAR_CODE_BYTE3;
					camacqhelper_SetCharacterCode(charCode);  // New design for Character code
					camScanparser_SetCharacterCode(charCode);
				}
			}
			else if(NIT_REQUIRED(CAM_UPDATED_NIT_VERSION))
			{
				TraceNotice(m, "%s:%d state = %d", __FUNCTION__, __LINE__, GET_INS_STATE);
				if(GET_INS_STATE == StIdle)
				{
				 	if((idvbset_IsAvailable(AUTO_MODE, rins_AttributeNetworkOperator)) && (CAM_UPDATED_NIT_VERSION >= 1)) //ADVANCE_TUNING_REQUIRED
					{
						TraceNotice(m, "%s:%d", __FUNCTION__, __LINE__);
						SET_CAM_INS_MODE(BACKGROUND_CAM_MODE);
						insN_OnEvent(insN_EventCamInstallRequestNormal, CURRENT_MODE);
					}
				}
				else
				{
					TraceNotice(m, "%s:%d", __FUNCTION__, __LINE__);
					insN_OnEvent(insN_EventInstallationStarted, CURRENT_MODE);
					
					TraceNotice(m, "%s opins_RequestNit called", __FUNCTION__);
					opins_RequestNit();
				}
			}
			else
			{
				if((GET_INS_STATE == StIdle) && (idvbset_IsAvailable(AUTO_MODE, rins_AttributeNetworkOperator)))
			    {
			    	char charCode[3];
					charCode[0] = CAM_CHAR_CODE_TYPE;
					charCode[1] = CAM_CHAR_CODE_BYTE2;
					charCode[2] = CAM_CHAR_CODE_BYTE3;
					camacqhelper_SetCharacterCode(charCode);
				}
			}
		}
	}
}

void CHsvDvbCamInstallation_mScan_Priv::mCamNITReceived(Op_ProfileNitData *TempNitData)
{
	if( (TempNitData->NitStatus == TRUE) && (TempNitData->NitDataLength > 0) )
	{
		SET_INS_STATE(StStrapiWait);
		camena_Enable(HsvDmxMain);
		TraceErr(m, "%s %d NitDataLength = %d", __FUNCTION__, __LINE__, TempNitData->NitDataLength);
		camScanparser_CamNitParser_Parser(0, EnmTypeCamNITData, TempNitData->NitDataLength, TempNitData->NitData);
	}
	else
	{
		TraceErr(m, "%s Invalid NIT data received with status %d length %d", __FUNCTION__, TempNitData->NitStatus, TempNitData->NitDataLength);
		pmp_PmpSend(mScanPump, EvStop, (Nat32)NULL);
	}
}

void CHsvDvbCamInstallation_mScan_Priv::mCamTuneRequest(Op_ProfileTuneData *TempTuneData)
{
	if(TempTuneData->TuneDataLength > 0)
	{
		SET_INS_STATE(StStrapiWait);
		camena_Enable(HsvDmxMain);
		TraceErr(m, "%s @ 890 TuneDataLength %d first 2 bytes %d %d", __FUNCTION__, TempTuneData->TuneDataLength, TempTuneData->TuneData[0], TempTuneData->TuneData[1]);
		camScanparser_CamNitParser_Parser(0, EnmTypeTuneDSDescData, TempTuneData->TuneDataLength, TempTuneData->TuneData);
	}
	else
	{
		TraceErr(m, "%s TuneDataLength %d", __FUNCTION__, TempTuneData->TuneDataLength);
		pmp_PmpSend(mScanPump, EvStop, (Nat32)NULL);
	}
}

void CHsvDvbCamInstallation_mScan_Priv::mCamTuneReply(void)
{
	TraceNotice(m, "%s opins_SendOpTuneStatus called with (%d %d %d %d)", __FUNCTION__, mTempTuneReplyDataPtr->Descriptor_Number, mTempTuneReplyDataPtr->Signal_Strength, mTempTuneReplyDataPtr->Signal_Quality, mTempTuneReplyDataPtr->Descriptor_Loop_Length);
	opins_SendOpTuneStatus(*mTempTuneReplyDataPtr);
}

void CHsvDvbCamInstallation_mScan_Priv::mUpdateTuneReplyData(OP_Status Status)
{
	mTempTuneReplyDataPtr->Status 				  = Status;
	TraceErr(m, "%s Tune status of the DSD = %d", __FUNCTION__, Status);
	switch(Status)
	{
		case OP_TUNESTATUS_SUCCESS:
		
			mTempTuneReplyDataPtr->Descriptor_Number      = ((CURRENT_TS_INDEX + 1) == mCamDSDesc.NumOfTs)? 0xFF: (CURRENT_TS_INDEX + 1);				    /* Points to the next unprocessed descriptor in tune request */
			mTempTuneReplyDataPtr->Signal_Strength        = 100;
			mTempTuneReplyDataPtr->Signal_Quality		  = 100;
			
			mCopyTuneDescriptorsLoop(TRUE);
			break;
		case OP_TUNESTATUS_FAILED:
		
			mTempTuneReplyDataPtr->Descriptor_Number 	  = 0xFF;
			mTempTuneReplyDataPtr->Signal_Strength 		  = 0;
			mTempTuneReplyDataPtr->Signal_Quality  		  = 0;		
			mTempTuneReplyDataPtr->Descriptor_Loop_Length = 0;
			mTempTuneReplyDataPtr->Descriptor_Loop		  = 0;			
			break;
		case OP_TUNESTATUS_NOT_SUPPORTED:
		
			mTempTuneReplyDataPtr->Descriptor_Number      = ((CURRENT_TS_INDEX + 1) == mCamDSDesc.NumOfTs)? 0xFF: (CURRENT_TS_INDEX + 1);
			mTempTuneReplyDataPtr->Signal_Strength 		  = 0;
			mTempTuneReplyDataPtr->Signal_Quality  		  = 0;
			
			mCopyTuneDescriptorsLoop(FALSE);
			break;
		case OP_TUNESTATUS_INVALID:
		
			mTempTuneReplyDataPtr->Descriptor_Number      = ((CURRENT_TS_INDEX + 1) == mCamDSDesc.NumOfTs)? 0xFF: (CURRENT_TS_INDEX + 1);
			mTempTuneReplyDataPtr->Signal_Strength 		  = 0;
			mTempTuneReplyDataPtr->Signal_Quality  		  = 0;
			
			mCopyTuneDescriptorsLoop(FALSE);
    		break;
		default:
			TraceErr(m, "%s Invalid Tune status of the DSD", __FUNCTION__, Status);
			break;
	}
}

void CHsvDvbCamInstallation_mScan_Priv::mCopyTuneDescriptorsLoop(Bool ValidLocation)
{
	int DescriptorEntryLength = mGetDescriptorEntryLength();
	int copyLength = CURRENT_TS_INDEX;
	if(mTempTuneReplyDataPtr->Descriptor_Loop == NULL)
	{
		mTempTuneReplyDataPtr->Descriptor_Loop = (Nat8 *)mGetLocalBuffer(mTempTuneDataPtr->TuneDataLength);
	}
	TraceNotice(m,"mTempTuneReplyDataPtr->Descriptor_Loop_Length %d , CURRENT_TS_INDEX %d \n",mTempTuneReplyDataPtr->Descriptor_Loop_Length,CURRENT_TS_INDEX);		
	if(CURRENT_TS_INDEX < 0)
	{
		copyLength = 0;
		TraceNotice(m,"Fix for copying correct tune reply data \n");
	}

	memcpy((mTempTuneReplyDataPtr->Descriptor_Loop + mTempTuneReplyDataPtr->Descriptor_Loop_Length), \
	       (mTempTuneDataPtr->TuneData + (mTempTuneReplyDataPtr->Descriptor_Loop_Length + (copyLength * (DescriptorEntryLength + 2)))), (DescriptorEntryLength + 2));
	
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

int CHsvDvbCamInstallation_mScan_Priv::mGetDescriptorEntryLength(void)
{
	int retval = 0;
	int dsdtype = 0;
	if(mCamDSDesc.NumOfTs > 0)
	dsdtype = CURRENT_DSD_TYPE;
	switch(dsdtype)
	{
		case HSVSPID(CamNITCableDS, dvb, camnit):
			retval = DVBC_DESCRIPTOR_ENTRY_LENGTH;
			break;
		case HSVSPID(CamNITTerrestrialDS, dvb, camnit):
			retval = DVBT_DESCRIPTOR_ENTRY_LENGTH;
			break;
		case HSVSPID(CamNITT2DS, dvb, camnit):
			retval = DVBT2_DESCRIPTOR_ENTRY_LENGTH;
			break;
		case HSVSPID(CamNITC2DS, dvb, camnit):
		default:
			retval = DVBT_DESCRIPTOR_ENTRY_LENGTH + 2; //workaround for 27686
			break;
	}
	return retval;
}

void CHsvDvbCamInstallation_mScan_Priv::mInitialise(void)
{
	Nat8 DeliveryCapility[4]      =	{ DVBC_DELIVERY_TAG, DVBT_DELIVERY_TAG, DELIVERY_EXTN_TAG, DVBT2_DELIVERY_OFFSET_TAG };
	Nat8 ApplicationCapability[4] =	{0};
	Nat8 ServiceType[17] = {0x01,0x02,0x03,0x04,0x05,0x06,0x10,0x0A,0x0C,0x11,0x16,0x17,0x18,0x19,0x1C,0x20,0x21};
	
	/* Scan data related */
	SET_INS_STATE(StIdle);
	SET_CAM_INS_MODE(BACKGROUND_CAM_MODE);
    memset((Address)(&mCamDSDesc), 0, sizeof(mCamDSDesc));
	
	/* Cam data related */
	mSearchSettings.Unattended_Flag 		    =	1;							 /* As we do nto support MMI/ AMMI during installation wizard */
	mSearchSettings.Service_Type_Length			=	MAX_SERVICE_TYPES_SUPPORTED;
	mSearchSettings.Service_Type	 = (Nat8*)malloc(MAX_SERVICE_TYPES_SUPPORTED);
	memcpy(mSearchSettings.Service_Type,ServiceType,MAX_SERVICE_TYPES_SUPPORTED);
//	mSearchSettings.Service_Type			    =	(Nat8*)(Service_Type);
	mSearchSettings.Delivery_Capability = (Nat8*)malloc(4);
	mSearchSettings.Application_Capability = (Nat8*)malloc(2);
	if(ANTENNA_MEDIUM)
	{
		mSearchSettings.Delivery_Cap_Length		=	3;
		*(mSearchSettings.Delivery_Capability)		=	DeliveryCapility[1];  /* DVBT & T2 */
	}
	else
	{
		mSearchSettings.Delivery_Cap_Length		=	1;
		*(mSearchSettings.Delivery_Capability)		=	DeliveryCapility[0];  	 /* DVBC, C2 yet to be supported */
	}
	
	mSearchSettings.Application_Cap_Length			=	0;
	*(mSearchSettings.Application_Capability)		=	ApplicationCapability[0];
	
	TraceDebug(m,"%s %d state %d", __FUNCTION__, __LINE__, GET_INS_STATE);
}

int CHsvDvbCamInstallation_mScan_Priv::icamhelper_GetCamInstallationMode(void)
{
	return GET_CAM_INS_MODE;
}

void CHsvDvbCamInstallation_mScan_Priv::icamhelper_SetCharacterCode(char* charCode)
{
	return ;
}
Bool CHsvDvbCamInstallation_mScan_Priv::icamhelper_CamNitParser_Parser( HsvDestination   dest,  Nat32 cookie, int DataSize, Nat8 * DataPtr)
{
return TRUE;
}

void CHsvDvbCamInstallation_mScan_Priv::pow_Init(void)
{
       isetpow_Init();
	mScanPump = pmp_PmpCreateEx(pen_PumpEngine, mScanPumpHandler, FALSE,"hsvdvbcamins_mScan");
	mCamDataPump = pmp_PmpCreateEx(pen_PumpEngine, mCamDataPumpHandler, FALSE,"hsvdvbcamins_CamDataPump");
    
	TraceDebug(m,"%s %d %d %d\n", __FUNCTION__, __LINE__, mScanPump, mCamDataPump);
	mModuleLifeCycle = Initialised;
}

void CHsvDvbCamInstallation_mScan_Priv::pow_TurnOn(void)
{
    mModuleLifeCycle = TurnedOn;
       isetpow_TurnOn();
	TraceDebug(m,"%s %d %d %d\n", __FUNCTION__, __LINE__, mScanPump, mCamDataPump);
	mInitialise();
}

FResult CHsvDvbCamInstallation_mScan_Priv::iins_StartInstallation(int source, int ptc, int mode)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s %d TURNED_ON %d source %d mode %d\n", __FUNCTION__, __LINE__, TURNED_ON, source, mode);
    if( TURNED_ON && VALID_CAM_INSTALL_MODE(mode) )
    {
        pmp_PmpSend(mScanPump, EvStart, (Nat32)NULL);
    }
    UNUSED(ptc);

    return retval;
}

FResult CHsvDvbCamInstallation_mScan_Priv::iins_StopInstallation(void)
{
    FResult retval = (GET_INS_STATE == StIdle)? hsverr_InstallationNotInProgress : hsverr_Ok;

    TraceDebug(m,"%s TURNED_ON %d\n", __FUNCTION__, TURNED_ON);
    if(TURNED_ON && (retval == hsverr_Ok) )
    {
        pmp_PmpSend(mScanPump, EvStop, (Nat32)NULL);
    }
    return retval;
}

void CHsvDvbCamInstallation_mScan_Priv::iins_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 OnId, Nat16 TsId)
{
   mGetPTCInfo(ptc, OnId, TsId);
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnStationFound()
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, TURNED_ON);
    if(TURNED_ON)
    {
        pmp_PmpSend(mScanPump, EvStationFound, (Nat32)NULL);
    }
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnStationNotFound()
{
    TraceDebug(m,"%s %d\n", __FUNCTION__, TURNED_ON);
    if(TURNED_ON)
    {       
        pmp_PmpSend(mScanPump, EvMakeDecision, (Nat32)NULL);
    }
}

void CHsvDvbCamInstallation_mScan_Priv::strapiN_OnCompleted( HsvDestination dest, int spid)
{
	UNUSED(dest);
	
	if( (spid == EnmTypeCamNITData) || (spid == EnmTypeTuneDSDescData) )
	{
		pmp_PmpSend(mScanPump, EvDataAvailable, (Nat32)spid);
	}
}

/* Cam Event Functions */
void CHsvDvbCamInstallation_mScan_Priv::opinsN_OnOpSearchStatus(Op_ProfileSearchStatus opStatus)
{
	TraceNotice(m, "%s %d", __FUNCTION__, TURNED_ON);
	if(TURNED_ON)
	{
		Op_ProfileSearchStatus *SearchStatusInfo = (Op_ProfileSearchStatus *) mGetLocalBuffer(sizeof(Op_ProfileSearchStatus));
		
		memcpy(SearchStatusInfo, (void *)&opStatus, sizeof(Op_ProfileSearchStatus));
		
		pmp_PmpSend(mCamDataPump, EvCamSearchStatus, (Nat32)SearchStatusInfo);
	}
}

void CHsvDvbCamInstallation_mScan_Priv::opinsN_OnOpStatusInfo(Op_ProfileStatusInfo StatusInfo)
{
	TraceNotice(m, "%s %d", __FUNCTION__, TURNED_ON);
	if(TURNED_ON)
	{
		Op_ProfileStatusInfo *TempStatusInfo = (Op_ProfileStatusInfo *) mGetLocalBuffer(sizeof(Op_ProfileStatusInfo));
		
		memcpy(TempStatusInfo, (void *)&StatusInfo, sizeof(Op_ProfileStatusInfo));
		
		pmp_PmpSend(mCamDataPump, EvCamStatusInfo, (Nat32)TempStatusInfo);
	}
}

void CHsvDvbCamInstallation_mScan_Priv::opinsN_OnOpNIT(Op_ProfileNitData nitData)
{
	TraceNotice(m, "%s %d", __FUNCTION__, TURNED_ON);
	if(TURNED_ON)
	{
		Op_ProfileNitData *TempNitData = (Op_ProfileNitData *)mGetLocalBuffer(sizeof(Op_ProfileNitData));
		
		memcpy(TempNitData, (void *)&nitData, sizeof(Op_ProfileNitData));
		
		pmp_PmpSend(mCamDataPump, EvCamNITReceived, (Nat32)TempNitData);
	}
}

void CHsvDvbCamInstallation_mScan_Priv::opinsN_OnOpTune(Op_ProfileTuneData tuneData)
{
	TraceNotice(m, "%s %d", __FUNCTION__, TURNED_ON);
	if(TURNED_ON)
	{
		Op_ProfileTuneData *TempTuneData = (Op_ProfileTuneData *) mGetLocalBuffer(sizeof(Op_ProfileTuneData));
		
		memcpy(TempTuneData, (void *)&tuneData, sizeof(Op_ProfileTuneData));
		
		pmp_PmpSend(mCamDataPump, EvCamTuneRequest, (Nat32)TempTuneData);
	}
}

void CHsvDvbCamInstallation_mScan_Priv::ena_Enable(void)
{
 
}

void CHsvDvbCamInstallation_mScan_Priv::ena_Disable(void)
{

}
/* Stub implementation of not relevant function of providing Interfaces */
void CHsvDvbCamInstallation_mScan_Priv::iins_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{ }
void CHsvDvbCamInstallation_mScan_Priv::iins_Initialise()
{ }
FResult CHsvDvbCamInstallation_mScan_Priv::iins_StartDigitalScan(void)
{ return 0; }
FResult CHsvDvbCamInstallation_mScan_Priv::iins_StartDigitalTuning(int frequency)
{   UNUSED(frequency); return 0; }
FResult CHsvDvbCamInstallation_mScan_Priv::iins_StopDigitalScan (void)
{ return 0; }
int CHsvDvbCamInstallation_mScan_Priv::iins_GetNoOfPass(void)
{ return 0; }
int CHsvDvbCamInstallation_mScan_Priv::iins_GetCurrentPass ( void )
{ return 0; }
FResult CHsvDvbCamInstallation_mScan_Priv::iins_StoreWeakSignalInstallationChannel()
{ return 0; }
int CHsvDvbCamInstallation_mScan_Priv::iins_GetNumberOfDigitalChannelsFound()
{ return 0; }
int CHsvDvbCamInstallation_mScan_Priv::iins_GetNumberOfDigitalChannelsRemoved()
{ return 0; }
int CHsvDvbCamInstallation_mScan_Priv::iins_GetCurrentState()
{ return 0; }
Bool CHsvDvbCamInstallation_mScan_Priv::iins_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }
HsvStreamPriority CHsvDvbCamInstallation_mScan_Priv::iins_GetStreamPriority(void)
{ return (HsvStreamPriority)0; }
HsvHierarchyMode CHsvDvbCamInstallation_mScan_Priv::iins_GetHierarchyMode(void)
{ return (HsvHierarchyMode)0; }
void CHsvDvbCamInstallation_mScan_Priv::iins_SetStreamPriority (HsvStreamPriority prio)
{ UNUSED(prio); }
void CHsvDvbCamInstallation_mScan_Priv::iins_SyncComplete(void)
{ }
void CHsvDvbCamInstallation_mScan_Priv::iins_ClearCache(void)
{ }
int CHsvDvbCamInstallation_mScan_Priv::iins_GetPLPIds(int *PLPIds)
{ UNUSED(PLPIds); return 0; }
void CHsvDvbCamInstallation_mScan_Priv::pow_TurnOff(void)
{
	isetpow_TurnOff();
}
int CHsvDvbCamInstallation_mScan_Priv::iins_GetSDTType()
{ return 0; }
Bool CHsvDvbCamInstallation_mScan_Priv::iins_ZiggoNetworkDataSet(Bool ActionValue)
{
    UNUSED(ActionValue);
    return FALSE;
}
void CHsvDvbCamInstallation_mScan_Priv::iins_ClearPersistent()
{ }

void CHsvDvbCamInstallation_mScan_Priv::iins_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnMeasReady( int ssm, Nat32 strength ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvDvbCamInstallation_mScan_Priv::feapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}
int CHsvDvbCamInstallation_mScan_Priv::iins_GetTargetNitType(Nat16* NetworkId)
{
    return 0;
}
void CHsvDvbCamInstallation_mScan_Priv::iins_GetPTCInfo(HsvInstallationPTC *ptc)
{
	
}

Bool  CHsvDvbCamInstallation_mScan_Priv::iins_GetAltTSValues(Nat16 * ONID,Nat16 * TSID)
{
return TRUE;
}


int CHsvDvbCamInstallation_mScan_Priv::iins_ZiggoGetSDTType(Nat16 Frequency)
{
return 0;
}


void CHsvDvbCamInstallation_mScan_Priv::strapiN_OnAdded(HsvDestination dest,int spid,int key1,int key2,int key3){
}

void CHsvDvbCamInstallation_mScan_Priv::strapiN_OnRemoved(HsvDestination dest,int spid,int key1,int key2,int key3){
}

void CHsvDvbCamInstallation_mScan_Priv::strapiN_OnChanged(HsvDestination dest,int spid,int key1,int key2,int key3,int eventid){
}
