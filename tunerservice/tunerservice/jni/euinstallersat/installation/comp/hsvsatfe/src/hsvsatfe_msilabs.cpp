/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: hsvsatfe_msilabs.c %
 *       %version:  TVG_FUSIONR3Ext_12 %
 * %date_modified:  %
 *    %derived_by:  dnilanjan % 
 */


#include "_hsvsatfe_msilabs.h"



TRACESYMBOL(m, "s2/hsvsatfe/satfe_msilabs")

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#ifndef __cplusplus

#else

#endif




















/* BlindScan */





BlindScanTable CHsvSatelliteFrontEnd_msilabs_Priv::s__mBlindScanFrequency[NUM_BLINSCAN_LNB_ENTRIES] =
{
	{
		LnbUniversal,	sisatfrontend_BlindScanModeNormal, 4,	/* For Universal frequency mentioned in Transponder Range */
		{
			{KUBAND_HIGHBAND_START_FREQ,	KUBAND_HIGHBAND_END_FREQ,	    plfdvbs_TUNING_DVBS_HORIZONTAL},
			{KUBAND_HIGHBAND_START_FREQ,	KUBAND_HIGHBAND_END_FREQ,	    plfdvbs_TUNING_DVBS_VERTICAL},
			{KUBAND_LOWBAND_START_FREQ,		(KUBAND_LOWBAND_END_FREQ-1),	plfdvbs_TUNING_DVBS_HORIZONTAL},
			{KUBAND_LOWBAND_START_FREQ,		(KUBAND_LOWBAND_END_FREQ-1),	plfdvbs_TUNING_DVBS_VERTICAL}
		}
	},
	{
		LnbUniversal,	sisatfrontend_BlindScanModeMinimal, 1,	/* For Universal frequency mentioned in Transponder Range */
		{
			{KUBAND_LOWBAND_START_FREQ,		(KUBAND_LOWBAND_END_FREQ-1),	plfdvbs_TUNING_DVBS_VERTICAL}
		}
	},

	{
		LnbMdutype4,	sisatfrontend_BlindScanModeNormal, 1,	/*	For MDU frequency mentioned in LNB (IF) Range */
		{
			{KUBAND_LOWBAND_START_FREQ,		KUBAND_LOWBAND_END_FREQ,		plfdvbs_TUNING_DVBS_HORIZONTAL},
		}
	},
	{
		LnbMdutype1,	sisatfrontend_BlindScanModeNormal, 1,	/*	For MDU frequency mentioned in LNB (IF) Range */
		{
			{KUBAND_LOWBAND_START_FREQ,		KUBAND_LOWBAND_END_FREQ,		plfdvbs_TUNING_DVBS_HORIZONTAL},
		}
	},
	{
		LnbMdutype2,	sisatfrontend_BlindScanModeNormal, 1,	/*	For MDU frequency mentioned in LNB (IF) Range */
		{
			{KUBAND_LOWBAND_START_FREQ,		KUBAND_LOWBAND_END_FREQ,		plfdvbs_TUNING_DVBS_HORIZONTAL},
		}
	},
	{
		LnbMdutype3,	sisatfrontend_BlindScanModeNormal, 1,	/*	For MDU frequency mentioned in LNB (IF) Range */
		{
			{KUBAND_LOWBAND_START_FREQ,		KUBAND_LOWBAND_END_FREQ,		plfdvbs_TUNING_DVBS_HORIZONTAL},
		}
	},
	{
		LnbMdutype5,	sisatfrontend_BlindScanModeNormal, 1,	/*	For MDU frequency mentioned in LNB (IF) Range */
		{
			{KUBAND_LOWBAND_START_FREQ,		KUBAND_LOWBAND_END_FREQ,		plfdvbs_TUNING_DVBS_HORIZONTAL},
		}
	},
	{
		LnbUnicable,	sisatfrontend_BlindScanModeNormal, 4,	/* For Unicable frequency mentioned in Transponder Range */
		{
			{KUBAND_HIGHBAND_START_FREQ,	KUBAND_HIGHBAND_END_FREQ,	    plfdvbs_TUNING_DVBS_HORIZONTAL},
			{KUBAND_HIGHBAND_START_FREQ,	KUBAND_HIGHBAND_END_FREQ,	    plfdvbs_TUNING_DVBS_VERTICAL},
			{KUBAND_LOWBAND_START_FREQ,		(KUBAND_LOWBAND_END_FREQ-1),	plfdvbs_TUNING_DVBS_HORIZONTAL},
			{KUBAND_LOWBAND_START_FREQ,		(KUBAND_LOWBAND_END_FREQ-1),	plfdvbs_TUNING_DVBS_VERTICAL}
		}
	},
	{
		LnbUnicable,	sisatfrontend_BlindScanModeMinimal, 1,	/* For Unicable frequency mentioned in Transponder Range */
		{
			{KUBAND_LOWBAND_START_FREQ,		(KUBAND_LOWBAND_END_FREQ-1),	plfdvbs_TUNING_DVBS_VERTICAL}
		}
	}
};


char CHsvSatelliteFrontEnd_msilabs_Priv::s__StateNames[StSatfeMax][32] = 
{
	"StIdle",
	"StTuningIdle",
	"StTuningAwaiting",
	"StBlindScanIdle",
	"StBlindScanProgress",
	"StBlindScanEnd",
};


char CHsvSatelliteFrontEnd_msilabs_Priv::s__EventNames[EvSatfeMax][32] = 
{
	"EvNewFeRequest",
	"EvStartTune",
	"EvTuneResult",
	"EvStartBlindScan",
	"EvContinueBlindScan",
	"EvAbortBlindScan",
	"EvBlindScanNtf",
	"EvBlindScanEnd"
};



/****************************************************************************
 * Static variables
 ****************************************************************************/
Bool CHsvSatelliteFrontEnd_msilabs_Priv::s__tuneresult = FALSE;

TuningParameters CHsvSatelliteFrontEnd_msilabs_Priv::s__mNewFeRequestParams,CHsvSatelliteFrontEnd_msilabs_Priv::s__mCurrentFeParams;

SatFeInstance CHsvSatelliteFrontEnd_msilabs_Priv::s__mSatFeIns;

BlindScanStatus CHsvSatelliteFrontEnd_msilabs_Priv::s__mBlindScanStatus;


int CHsvSatelliteFrontEnd_msilabs_Priv::s__SatFeSem;

Pump CHsvSatelliteFrontEnd_msilabs_Priv::s__mPump;


/****************************************************************************
 * Static functions
 ****************************************************************************/





























/* State Machine */
FunctionNat32 CHsvSatelliteFrontEnd_msilabs_Priv::s__SatFeEventActionMatrix[EvSatfeMax][StSatfeMax] = 
{
/*							StIdle						StTuningIdle,				StTuningAwaiting,			StBlindScanIdle,			StBlindScanProgress,			StBlindScanEnd	*/
/*	EvNewFeRequest	*/	{	FNADDR(mProcessFeRequest),	FNADDR(mNewFeRequest),		FNADDR(mNewFeRequest),		FNADDR(mGotoNewFeRequest),	FNADDR(mGotoNewFeRequest),		FNADDR(mGotoNewFeRequest)	},
/*	EvStartTune		*/	{	FNADDR(mProcessFeRequest),	FNADDR(mSendTuneRequest),	FNADDR(mNewTuneRequest),	FNADDR(mTriggerBlindScan),	NULL,							NULL				},
/*	EvTuneResult	*/	{	FNADDR(mProcessFeRequest),	FNADDR(mSendTuneRequest),	FNADDR(mNotifyTuneResult),	NULL,						NULL,							NULL				},
/*	EvStartBlindScan*/	{	FNADDR(mProcessBlindScan),	NULL,						NULL,						FNADDR(mStartBlindScan),	NULL,							NULL				},
/*	EvContBlindScan	*/	{	NULL,						NULL,						NULL,						NULL,						FNADDR(mContinueBlindScan),		NULL				},
/*	EvAbortBlindScan*/	{	NULL,						NULL,						NULL,						FNADDR(mAbortBlindSCan),	FNADDR(mAbortBlindSCan),		NULL				},
/*	EvBlindScanNtf	*/	{	NULL,						NULL,						NULL,						NULL,						FNADDR(mNotifyBlindScanResult),	NULL				},
/*	EvBlindScanEnd	*/	{	NULL,						NULL,						NULL,						NULL,						FNADDR(mProcessBlindScanEnd),	FNADDR(mNotifyBlindScanEnd)	}
};



/********************************/
/*  STATE MACHINE FUNCTIONS		*/
/********************************/

void CHsvSatelliteFrontEnd_msilabs_Priv::mPumpHandler(int event, Nat32 param)
{
    if (VALID_EVENT(event) && VALID_STATE(mSatFeIns.CurrentState))
    {
        if (SatFeEventActionMatrix[event][mSatFeIns.CurrentState])
        {
            TraceNotice (m, " silabs: %s %s ", EventNames[event], StateNames[mSatFeIns.CurrentState]);
            FPCALL(SatFeEventActionMatrix[event][mSatFeIns.CurrentState])(param);
        }
    }
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mProcessFeRequest (Nat32 Param)
{
	Bool	Proceed = FALSE;

	SEM_TAKE(SatFeSem);
	
	/* Indicated by plf. There can be LockChanged ntf whenever signal loss happens. So in Idle state
		Processing should be done only if some explicit user request hav come */
	Proceed = mNewFeRequestParams.Valid;

	SEM_GIVE(SatFeSem);

	if (Proceed)
	{
		switch (mNewFeRequestParams.LnbType)
		{
	    /* Only for universal LNB Diseqc msg sending is needed. For MDU/Unicable trigger the tuning directl */	
		case	LnbUniversal:
		case	LnbMdutype1:
		case	LnbMdutype2:
		case	LnbMdutype3:
		case	LnbMdutype4:
		case	LnbMdutype5:
		case	LnbUnicable:
			mCopyTuningRequest ();
			SET_STATE(StTuningIdle);
			pmp_PmpSend(mPump, EvStartTune, (Nat32)NULL);
			break;
		default:
			ASSERT ("Invalid LnbType in Tuning ");
			break;
		}
	}
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mNewFeRequest (Nat32 Param)
{
    /* No Actions needed. Make State to Idle. Next notification (OnLockChanged, OnMsgSent) will 
     * trigger the tuning */
	SET_STATE(StIdle);
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mSendTuneRequest (Nat32 Param)
{
    FResult     RetVal = err_BadParameter;

    /* Based on the Selected LNB Type send the tuning request */
	switch (mCurrentFeParams.LnbType)
	{
	case	LnbUniversal:
        RetVal = mSendUniversalLnbTuningRequest ();
		break;

	case	LnbMdutype4:
	case	LnbMdutype1:
	case	LnbMdutype2:
	case	LnbMdutype3:
	case	LnbMdutype5:
        RetVal = mSendMduTuningRequest ();
		break;
	case	LnbUnicable:
        RetVal = mSendUnicableTuningRequest ();
		break;

    default:
        break;
    }

    if (RetVal != err_Ok)
    {
        /* Tuning Failed. Give Unlock notification to clients */
        SET_STATE(StIdle);
        satfrontendNotify_OnLockChanged(FALSE);
    }
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mNewTuneRequest (Nat32 Param)
{
    /* New Tune request came. Make State to TuningIdle. Current notification will 
     * trigger Tuning again */
	SET_STATE(StTuningIdle);
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mNotifyTuneResult (Nat32 Param)
{
    /* Notify Tuning result to clients */
    SET_STATE(StIdle);
	SEM_TAKE(SatFeSem);
	mNewFeRequestParams.Valid = FALSE;
	SEM_GIVE(SatFeSem);
    satfrontendNotify_OnLockChanged((Bool)Param);
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mGotoNewFeRequest (Nat32 Param)
{
    /* FE request can come when blind scan lock triggers MW. MW decides to move on to
     *  Tuning rather than continuing */
    SET_STATE(StIdle);
	pmp_PmpSend(mPump, EvNewFeRequest, (Nat32)NULL);
}


void CHsvSatelliteFrontEnd_msilabs_Priv::mProcessBlindScan (Nat32 Param)
{
	FResult RetVal;
	HsvLnbSettings	LnbSettings;
	Nat8	Count;
	Bool	Found = FALSE;

	/* Identify the LNB Type. Get the range */
	RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);
	if (RetVal == err_Ok)
	{
		for (Count = 0; Count < (sizeof(mBlindScanFrequency)/sizeof(mBlindScanFrequency[0])); Count++)
		{
			if ((LnbSettings.LnbSettings[Param].LnbType == mBlindScanFrequency[Count].LnbType) && (mSatFeIns.BlindScanMode == mBlindScanFrequency[Count].BlindScanMode))
			{
				mBlindScanStatus.LnbNumber = Param;
				mBlindScanStatus.CurrentTableIndex = Count;
				mBlindScanStatus.CurrentBandInTable = 0;
				Found = TRUE;
				
				SET_STATE(StBlindScanIdle);
                TraceNotice (m, "silabs: Lnb %d CurrenTableIndex %d ", mBlindScanStatus.LnbNumber, mBlindScanStatus.CurrentTableIndex);
				pmp_PmpSend(mPump, EvStartBlindScan, (Nat32)NULL);
				break;
			}
		}
	}
	if (Found == FALSE)
	{
		satfrontendNotify_OnBlindScanEnd();
		SET_STATE(StIdle);
	}
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mStartBlindScan (Nat32 Param)
{
	switch (mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].LnbType)
	{
	case	LnbUniversal:
	case	LnbMdutype1:
	case	LnbMdutype2:
	case	LnbMdutype3:
	case	LnbMdutype4:
	case	LnbMdutype5:
	case	LnbUnicable:
		SET_STATE(StBlindScanIdle);
		pmp_PmpSend(mPump, EvStartTune, (Nat32)NULL);	
		break;
	default:
		ASSERT (" BlindScan initiated on Unsupported LnbType");
		break;
	}
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mTriggerBlindScan (Nat32 Param)
{
	FResult	RetVal = err_BadParameter;
	Nat32	MinFrequency,	MaxFrequency;
	int		Polarization;
	HsvDvbSLNBConfig	LnbConfig;
	HsvDvbSCustomLNBConfig	CustomLnbConfig;
	HsvDvbSUnicableConfig	UnicableConfig;
	HsvLnbSettings		LnbSettings;
	int		Band;
	int		ConnectionType;

	switch (mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].LnbType)
	{
	case	LnbUniversal:
		RetVal = err_Ok;
		RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);
		Polarization = mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].Ranges[mBlindScanStatus.CurrentBandInTable].Polarization;

		LnbConfig.Tone = plfdvbs_TUNING_DVBSEX_TONENONE;
		LnbConfig.LNBNumber = mBlindScanStatus.LnbNumber;
		/*Fill Tone and Burst select parameters for DiSeqcMini*/
		if(LnbConnectionDiSeqcMini == LnbSettings.ConnectionType)
		{
			LnbConfig.BurstSelect = (mBlindScanStatus.LnbNumber == 0) ? plfdvbs_DVBSEX_TONEBURST_SAT_A : plfdvbs_DVBSEX_TONEBURST_SAT_B;
			LnbConfig.Tone = plfdvbs_TUNING_DVBSEX_TONELOW;
		}
		
		if(LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].HighLoFreq == CIRCULAR_HIGH_LO_FREQ)
		{
			TraceNotice(m,"Setting LNB type as Circular");
			LnbConfig.LNBType = plfdvbs_TUNING_DVBS_CIRCULAR;
		}
		else
		{
			TraceNotice(m,"Setting LNB type as Universal for tuning");
			LnbConfig.LNBType = plfdvbs_TUNING_DVBS_UNIVERSAL;
		}

		LnbConfig.LNBType = plfdvbs_TUNING_DVBS_UNIVERSAL;

		if(LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].LnbPower == plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF)
		{
			TraceNotice(m,"[%s]: [%d] Setting LNB type as Custom for tuning with Power off",__FUNCTION__,__LINE__);
			LnbConfig.LNBType = plfdvbs_TUNING_DVBS_CUSTOM;
			CustomLnbConfig.CustomPow = plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF;
		}

		Band = MAP_UNIVERSAL_FREQ_TO_BAND(mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].Ranges[mBlindScanStatus.CurrentBandInTable].StartFreq);
		RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);
		/*TODO: check if any mapping is required b/w MW and PLF*/
		ConnectionType = LnbSettings.ConnectionType;

		plfdvbs_configureLNB (LnbConfig,CustomLnbConfig);
		plfdvbs_setPolarization (Polarization);
		plfdvbs_setBand(Band);
		plfdvbs_setLNBConnectionType(ConnectionType);
		plfdvbs_setSymbolRate (plfdvbs_TUNING_DVBS_SR_DETECTMODE_AUTO, 0);

		MinFrequency = mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].Ranges[mBlindScanStatus.CurrentBandInTable].StartFreq;
		MaxFrequency = mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].Ranges[mBlindScanStatus.CurrentBandInTable].EndFreq;
		break;

	case	LnbMdutype1:
	case	LnbMdutype2:
	case	LnbMdutype3:
	case	LnbMdutype4:
	case	LnbMdutype5:
		RetVal = err_Ok;

		LnbConfig.LNBNumber = mBlindScanStatus.LnbNumber;
		LnbConfig.LNBType = MapMwLnbTypeToPlf (mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].LnbType);
		LnbConfig.Tone = plfdvbs_TUNING_DVBSEX_TONENONE;
		
		if(LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].LnbPower == plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF)
		{
			TraceNotice(m,"[%s]: [%d] Setting LNB type as Custom for tuning with Power off",__FUNCTION__,__LINE__);
			LnbConfig.LNBType = plfdvbs_TUNING_DVBS_CUSTOM;
			CustomLnbConfig.CustomPow = plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF;
		}
		plfdvbs_configureLNB (LnbConfig, CustomLnbConfig);
		/*CR: AN-2908*/
		MinFrequency = plfdvbs_TUNING_DVBS_START_FREQUENCY;
		MaxFrequency = plfdvbs_TUNING_DVBS_END_FREQUENCY;
		
		break;

	case	LnbUnicable:
		RetVal = err_Ok;

		RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);
		LnbConfig.LNBNumber = mBlindScanStatus.LnbNumber;
		LnbConfig.LNBType = plfdvbs_TUNING_DVBS_UNICABLE;
		LnbConfig.Tone = plfdvbs_TUNING_DVBSEX_TONENONE;
		LnbConfig.LUserBandNumber = LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].UserBand;
		LnbConfig.LUserBandFrequency = LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].UserBandFrequency;
		
		CustomLnbConfig.Custom_High_LO_Value = LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].HighLoFreq;
		CustomLnbConfig.Custom_Low_LO_Value = LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].LowLoFreq;
		/*TODO: Chage this value once CR is clear abt this*/
		CustomLnbConfig.CustomPow = (LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].LnbPower) ? plfdvbs_TUNING_DVBSEX_CUSTOMPOW_ON : plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF;

		Band = MAP_UNIVERSAL_FREQ_TO_BAND(mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].Ranges[mBlindScanStatus.CurrentBandInTable].StartFreq);
		RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);
		/*TODO: check if any mapping is required b/w MW and PLF*/
		ConnectionType = LnbSettings.ConnectionType;
//		RetVal = plfdvbs_configureUnicable(UnicableConfig);

		Polarization = mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].Ranges[mBlindScanStatus.CurrentBandInTable].Polarization;
		plfdvbs_configureLNB (LnbConfig,CustomLnbConfig);
		plfdvbs_setPolarization (Polarization);
		plfdvbs_setBand(Band);
		plfdvbs_setLNBConnectionType(ConnectionType);
		plfdvbs_setSymbolRate (plfdvbs_TUNING_DVBS_SR_DETECTMODE_AUTO, 0);

	
		MinFrequency = mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].Ranges[mBlindScanStatus.CurrentBandInTable].StartFreq;
		MaxFrequency = mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].Ranges[mBlindScanStatus.CurrentBandInTable].EndFreq;
		break;
	default:
		ASSERT (" BlindScan initiated on Unsupported LnbType");
		break;
	}


	if (RetVal == err_Ok)
	{
		TraceNotice (m, "silabs: Sending BlindScan Start to Plf ");
		RetVal = plftune_scanStart (MinFrequency, MaxFrequency, TRUE);
        TraceNotice (m, "silabs: BlindScan Start returned %d ", RetVal);
	}

	if (RetVal != err_Ok)
	{
		TraceNotice (m, "silabs: Error in initiating BlindScan Start to Plf ");
		satfrontendNotify_OnBlindScanEnd();
		SET_STATE(StIdle);
	}
    else
    {
        SET_STATE(StBlindScanProgress);
    }
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mNotifyBlindScanResult (Nat32 Param)
{
	/* Lock changed FALSE is triggered from plf many times after BlindScanEnd. So ignore this notification.
		SatFE dont expect LockChanged FALSE during blind scan. If no mux found/end of band reached it should
		be informed by BlindScanEnd notification */
	if (Param == TRUE)
	{
		satfrontendNotify_OnLockChanged(TRUE);
	}
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mContinueBlindScan (Nat32 Param)
{
	FResult	RetVal = err_BadParameter;

    TraceNotice (m ,"silabs: Continue BlindScan ");
	RetVal = plftune_scanNext();
	if (RetVal != err_Ok)
	{
		satfrontendNotify_OnBlindScanEnd();
		SET_STATE(StIdle);
	}
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mAbortBlindSCan (Nat32 Param)
{
	FResult	RetVal = err_BadParameter;

	SET_STATE(StBlindScanEnd);
	RetVal = plftune_scanAbort();
    
	if (RetVal != err_Ok)
	{
		satfrontendNotify_OnBlindScanEnd();
		SET_STATE(StIdle);
	}
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mProcessBlindScanEnd (Nat32 Param)
{
     
	mBlindScanStatus.CurrentBandInTable++;
    TraceNotice (m, "silabs: CurrentBandInTable %d ", mBlindScanStatus.CurrentBandInTable);
	/*TODO: Hack to skip other bands*/
//	if(TRUE || ((mBlindScanStatus.CurrentBandInTable >= mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].TotalNumOfBands)))
	if(((mBlindScanStatus.CurrentBandInTable >= mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].TotalNumOfBands)))	
	{
		/* All bands covered. Time to Trigger MW blind scan end */
		SET_STATE(StBlindScanEnd);
		pmp_PmpSend(mPump, EvBlindScanEnd, (Nat32)NULL);
	}
	else
	{
		/* Still bands remaining. */
		SET_STATE(StBlindScanIdle);
		pmp_PmpSend(mPump, EvStartBlindScan, (Nat32)NULL);	
	}
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mNotifyBlindScanEnd (Nat32 Param)
{
	SET_STATE(StIdle);
	satfrontendNotify_OnBlindScanEnd();
}

/********************************/
/*      GENERIC FUNCTIONS		*/
/********************************/

void CHsvSatelliteFrontEnd_msilabs_Priv::mInitialize (void)
{
	memset (&mNewFeRequestParams, 0x00, sizeof(mNewFeRequestParams));
	memset (&mCurrentFeParams, 0x00, sizeof(mCurrentFeParams));
	memset (&mBlindScanStatus, 0x00, sizeof(mBlindScanStatus));
	mSatFeIns.CurrentState = StIdle;
	mSatFeIns.CurrentMode = SatFeModeNone;
    mSatFeIns.UnicableEnabed = FALSE;
}

Bool CHsvSatelliteFrontEnd_msilabs_Priv::mValidTuningCombination(int LnbNumber, HsvLnbType LnbType)
{
    FResult RetVal;
	Bool	Match = FALSE;
	HsvLnbSettings	LnbSettings;

	RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);
	Match = ((RetVal == err_Ok) && ((LnbSettings.LnbSettings[LnbNumber].LnbType == LnbType) || 
				((LnbSettings.LnbSettings[LnbNumber].LnbType == LnbUniversal) && (IS_MDU(LnbType)) ) )) ? TRUE : FALSE;

    TraceNotice (m, "ValidTuningCombination %d ", Match);
	return Match;
}

void CHsvSatelliteFrontEnd_msilabs_Priv::mCopyTuningRequest (void)
{
	SEM_TAKE (SatFeSem);

	mCurrentFeParams.LnbNumber = mNewFeRequestParams.LnbNumber;
	mCurrentFeParams.LnbType = mNewFeRequestParams.LnbType;
	mCurrentFeParams.Frequency = mNewFeRequestParams.Frequency;
	mCurrentFeParams.Polarization = mNewFeRequestParams.Polarization;
	mCurrentFeParams.TuningParams.SymbolRate = mNewFeRequestParams.TuningParams.SymbolRate;
	mCurrentFeParams.TuningParams.ModulationStandard = mNewFeRequestParams.TuningParams.ModulationStandard;
	mCurrentFeParams.TuningParams.Constellation = mNewFeRequestParams.TuningParams.Constellation;
	mCurrentFeParams.TuningParams.CodeRate = mNewFeRequestParams.TuningParams.CodeRate;
	mCurrentFeParams.TuningParams.IqMode = mNewFeRequestParams.TuningParams.IqMode;
	mCurrentFeParams.SatIpParams.ModulationSystem= mNewFeRequestParams.SatIpParams.ModulationSystem;
	mCurrentFeParams.SatIpParams.ModulationType= mNewFeRequestParams.SatIpParams.ModulationType;
	mCurrentFeParams.SatIpParams.RollOffFactor= mNewFeRequestParams.SatIpParams.RollOffFactor;
	mCurrentFeParams.SatIpParams.FECInner= mNewFeRequestParams.SatIpParams.FECInner;
	mCurrentFeParams.SatIpParams.Pilots= mNewFeRequestParams.SatIpParams.Pilots;
	mCurrentFeParams.Valid = TRUE;

	/*If its used for the plf on lock change will come in Idle need give FalseOnly after on lock changed*/
	//mNewFeRequestParams.Valid = FALSE;

	SEM_GIVE (SatFeSem);
    TraceNotice (m, "silabs: Copied Tuning Parameters: %d ", mCurrentFeParams.TuningParams.CodeRate);
	//TraceNotice(m,"Nilanjan %s: ModStd %d ModType %d CodeRate %d", mCurrentFeParams.TuningParams.ModulationStandard, mCurrentFeParams.TuningParams.Constellation, mCurrentFeParams.TuningParams.CodeRate);
}



/********************************/
/*  UNIVERSAL LNB FUNCTIONS		*/
/********************************/


FResult CHsvSatelliteFrontEnd_msilabs_Priv::mSendUniversalLnbTuningRequest (void)
{
	FResult		RetVal = err_TunerError;
    int         Polarization, LnbNumber, Band, ConnectionType;
    Nat32       LnbFreq, SymbolRate;
	HsvDvbSLNBConfig	LnbConfig;
	HsvDvbSCustomLNBConfig	CustomLnbConfig;
	HsvLnbSettings		LnbSettings;

    SEM_TAKE (SatFeSem);
	LnbFreq = mCurrentFeParams.Frequency;
	SymbolRate = mCurrentFeParams.TuningParams.SymbolRate;
	Polarization = mCurrentFeParams.Polarization;
	LnbNumber = mCurrentFeParams.LnbNumber;
	mCurrentFeParams.Valid = FALSE;
    SEM_GIVE (SatFeSem);

	Band = MAP_UNIVERSAL_FREQ_TO_BAND(LnbFreq);	
	RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);
	/*TODO: check if any mappig is required b/w MW and PLF*/
	ConnectionType = LnbSettings.ConnectionType;
	if(LnbSettings.LnbSettings[mBlindScanStatus.LnbNumber].HighLoFreq == CIRCULAR_HIGH_LO_FREQ)
	{
		LnbConfig.LNBType = plfdvbs_TUNING_DVBS_CIRCULAR;
	}
	else
	{
		LnbConfig.LNBType = plfdvbs_TUNING_DVBS_UNIVERSAL;
	}
	LnbConfig.LNBNumber = LnbNumber;

	
	if(LnbSettings.LnbSettings[mCurrentFeParams.LnbNumber].LnbPower == plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF)
	{
		TraceNotice(m,"[%s]: [%d] Setting LNB type as Custom for tuning with Power off",__FUNCTION__,__LINE__);
		LnbConfig.LNBType = plfdvbs_TUNING_DVBS_CUSTOM;
		CustomLnbConfig.CustomPow = plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF;
	}

	RetVal = plfdvbs_configureLNB(LnbConfig, CustomLnbConfig);
	RetVal = plfdvbs_setPolarization (Polarization);
	RetVal = (SymbolRate == 0) ? plfdvbs_setSymbolRate (plfdvbs_TUNING_DVBS_SR_DETECTMODE_AUTO, SymbolRate) :\
						plfdvbs_setSymbolRate (plfdvbs_TUNING_DVBS_SR_DETECTMODE_MANUAL, SymbolRate);
	
	RetVal = plfdvbs_setBand(Band);
	RetVal = plfdvbs_setLNBConnectionType(ConnectionType);

	if(LnbSettings.ConnectionType == LnbConnectionSatIp)
	{
		TraceNotice(m,"SAT-IP Params: Mod. System: %d Mod. Type: %d RollOff: %d, FEC: %d, Pilots: %d",mCurrentFeParams.SatIpParams.ModulationSystem, mCurrentFeParams.SatIpParams.ModulationType, \
			mCurrentFeParams.SatIpParams.RollOffFactor,mCurrentFeParams.SatIpParams.FECInner,mCurrentFeParams.SatIpParams.Pilots);
		
		plfdvbs_setSatIPParams(mCurrentFeParams.SatIpParams.ModulationSystem, mCurrentFeParams.SatIpParams.ModulationType, \
			mCurrentFeParams.SatIpParams.RollOffFactor,mCurrentFeParams.SatIpParams.FECInner,mCurrentFeParams.SatIpParams.Pilots);
	}
					

	TraceNotice (m, "Universal Tuning: Freq %d SymbolRate %d Polarization %d LnbNumber %d ",(int) LnbFreq, (int)SymbolRate, Polarization, LnbNumber);

	SET_STATE(StTuningAwaiting);
	RetVal = plftune_tune (LnbFreq, TRUE);
    
    return RetVal;
}


/********************************/
/*      MDU FUNCTIONS   		*/
/********************************/

FResult CHsvSatelliteFrontEnd_msilabs_Priv::mSendMduTuningRequest (void)
{
	FResult		RetVal = err_TunerError;
    int         Polarization, LnbNumber, LnbType = plfdvbs_TUNING_DVBS_MDU4;
    Nat32       LnbFreq, SymbolRate;
	HsvDvbSLNBConfig	LnbConfig;
	HsvDvbSCustomLNBConfig	CustomLnbConfig;
	HsvLnbSettings		LnbSettings;

    SEM_TAKE (SatFeSem);
	LnbFreq = mCurrentFeParams.Frequency;
	SymbolRate = mCurrentFeParams.TuningParams.SymbolRate;
	Polarization = mCurrentFeParams.Polarization;
	LnbNumber = mCurrentFeParams.LnbNumber;
	mCurrentFeParams.Valid = FALSE;
	LnbType =  (mCurrentFeParams.LnbType);

    SEM_GIVE (SatFeSem);

	LnbConfig.LNBType = MapMwLnbTypeToPlf(LnbType);
	LnbConfig.LNBNumber = LnbNumber;

	RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);
	
	if(LnbSettings.LnbSettings[mCurrentFeParams.LnbNumber].LnbPower == plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF)
	{
		TraceNotice(m,"[%s]: [%d] Setting LNB type as Custom for tuning with Power off",__FUNCTION__,__LINE__);
		LnbConfig.LNBType = plfdvbs_TUNING_DVBS_CUSTOM;
		CustomLnbConfig.CustomPow = plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF;
	}

	/*TODO: Check if connectiontype and band also required for MDU*/
	RetVal = plfdvbs_configureLNB(LnbConfig, CustomLnbConfig);
	RetVal = plfdvbs_setPolarization (Polarization);
	RetVal = (SymbolRate == 0) ? plfdvbs_setSymbolRate (plfdvbs_TUNING_DVBS_SR_DETECTMODE_AUTO, SymbolRate) :\
						plfdvbs_setSymbolRate (plfdvbs_TUNING_DVBS_SR_DETECTMODE_MANUAL, SymbolRate);
						

	TraceNotice (m, "MDU Tuning: Freq %d SymbolRate %d Polarization %d LnbNumber %d ",(int) LnbFreq, (int)SymbolRate, Polarization, LnbNumber);

	SET_STATE(StTuningAwaiting);
	RetVal = plftune_tune (LnbFreq, TRUE);
    
    return RetVal;
}



/********************************/
/*      UNICABLE FUNCTIONS		*/
/********************************/

FResult CHsvSatelliteFrontEnd_msilabs_Priv::mEnableUnicableDevice (int LnbNumber, Bool Flag, Bool ForceSet)
{
    FResult         RetVal = err_Ok;
	HsvLnbSettings	LnbSettings;
	HsvDvbSUnicableConfig	UnicableConfig;

    if ((ForceSet) || (Flag != mSatFeIns.UnicableEnabed))
    {
        mSatFeIns.UnicableEnabed = Flag;
        RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);

		UnicableConfig.UserBandNumber = LnbSettings.LnbSettings[LnbNumber].UserBand;
		UnicableConfig.UserBandFrequency = LnbSettings.LnbSettings[LnbNumber].UserBandFrequency;
		RetVal = plfdvbs_configureUnicable(UnicableConfig);
    }

    return RetVal;
}

FResult CHsvSatelliteFrontEnd_msilabs_Priv::mSendUnicableTuningRequest (void)
{
	FResult		RetVal = err_TunerError;
    int         Polarization, LnbNumber, Band, ConnectionType;
    Nat32       LnbFreq, SymbolRate;
	HsvDvbSUnicableConfig	UnicableConfig;
	HsvLnbSettings		LnbSettings;
	HsvDvbSLNBConfig	LnbConfig;
	HsvDvbSCustomLNBConfig	CustomLnbConfig;

    SEM_TAKE (SatFeSem);
	LnbFreq = mCurrentFeParams.Frequency;
	SymbolRate = mCurrentFeParams.TuningParams.SymbolRate;
	Polarization = mCurrentFeParams.Polarization;
	LnbNumber = mCurrentFeParams.LnbNumber;
	mCurrentFeParams.Valid = FALSE;

    SEM_GIVE (SatFeSem);

	RetVal = hsvsatsettings_GetLnbSettings (&LnbSettings);

	LnbConfig.LNBNumber = LnbNumber;
	LnbConfig.LNBType= plfdvbs_TUNING_DVBS_UNICABLE;
	LnbConfig.LUserBandNumber = LnbSettings.LnbSettings[LnbNumber].UserBand;
	LnbConfig.LUserBandFrequency= LnbSettings.LnbSettings[LnbNumber].UserBandFrequency;
	CustomLnbConfig.Custom_High_LO_Value = LnbSettings.LnbSettings[LnbNumber].HighLoFreq;
	CustomLnbConfig.Custom_Low_LO_Value = LnbSettings.LnbSettings[LnbNumber].LowLoFreq;
	/*TODO: Chage this value once CR is clear abt this*/
	CustomLnbConfig.CustomPow = (LnbSettings.LnbSettings[LnbNumber].LnbPower) ? plfdvbs_TUNING_DVBSEX_CUSTOMPOW_ON : plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF;
 	/*TODO: check if any mappig is required b/w MW and PLF*/
	ConnectionType = LnbSettings.ConnectionType;
	Band = MAP_UNIVERSAL_FREQ_TO_BAND(LnbFreq);
	

//	RetVal = plfdvbs_configureUnicable(UnicableConfig);


	RetVal = plfdvbs_configureLNB(LnbConfig, CustomLnbConfig);
	RetVal = plfdvbs_setPolarization (Polarization);
	RetVal = (SymbolRate == 0) ? plfdvbs_setSymbolRate (plfdvbs_TUNING_DVBS_SR_DETECTMODE_AUTO, SymbolRate) :\
						plfdvbs_setSymbolRate (plfdvbs_TUNING_DVBS_SR_DETECTMODE_MANUAL, SymbolRate);
	RetVal = plfdvbs_setBand(Band);
	RetVal = plfdvbs_setLNBConnectionType(ConnectionType);
						

	TraceNotice (m, "Unicable Tuning: Freq %d SymbolRate %d Polarization %d LnbNumber %d ",(int) LnbFreq, (int)SymbolRate, Polarization, LnbNumber);

	SET_STATE(StTuningAwaiting);
	RetVal = plftune_tune (LnbFreq, TRUE);
    
    return RetVal;
}


int CHsvSatelliteFrontEnd_msilabs_Priv::MapMwLnbTypeToPlf (int LnbType)
{
	int PlfLnbType = plfdvbs_TUNING_DVBS_UNIVERSAL;
	switch (LnbType)
	{
		case	LnbUniversal:
			PlfLnbType = plfdvbs_TUNING_DVBS_UNIVERSAL;
			break;
		case	LnbMdutype1:
			PlfLnbType = plfdvbs_TUNING_DVBS_MDU1;
			break;
		case	LnbMdutype2:
			PlfLnbType = plfdvbs_TUNING_DVBS_MDU2;
			break;
		case	LnbMdutype3:
			PlfLnbType = plfdvbs_TUNING_DVBS_MDU3;
			break;
		case	LnbMdutype4:
			PlfLnbType = plfdvbs_TUNING_DVBS_MDU4;
			break;
		case	LnbMdutype5:
			PlfLnbType = plfdvbs_TUNING_DVBS_MDU5;
			break;
		case	LnbUnicable:
			PlfLnbType = plfdvbs_TUNING_DVBS_UNICABLE; /* Aneesh: TODO: Add this type in the interface file */
			break;
		default:
			break;
	}
	return PlfLnbType;
}

/********************************/
/*      INTERFACE FUNCTIONS		*/
/********************************/

/* provides IHsvPower	pow */
void CHsvSatelliteFrontEnd_msilabs_Priv::sipow_Init(void)
{
    mPump = pmp_PmpCreateEx( pen_PumpEngine, mPumpHandler, FALSE, "hsvsatfe_msilabs_pmp" );
	SatFeSem = SEM_CREATE;	
	mInitialize ();
}

void CHsvSatelliteFrontEnd_msilabs_Priv::sipow_TurnOn(void)
{
}

void CHsvSatelliteFrontEnd_msilabs_Priv::sipow_TurnOff(void)
{

}

/* provides IHsvSatelliteFrontEnd	satfrontend */

FResult CHsvSatelliteFrontEnd_msilabs_Priv::sisatfrontend_SatelliteFrontEndTune(int	LnbNumber,int LnbType,int Frequency,int	SymbolRate,int	Polarization,int	Cookie,int	ModlnStd,int	ModlnType,int	CodeRate, int RollOff, int FECInner, int Pilots)
{
	FResult		RetVal = err_Ok;

	RetVal |= CHK_VALID_LNB (LnbNumber);
	RetVal |= CHK_VALID_LNBTYPE(LnbType);
	RetVal |= CHK_VALID_FREQ(Frequency);

	if (RetVal == err_Ok)
	{
		if (mValidTuningCombination(LnbNumber, (HsvLnbType)LnbType))
		{

			SEM_TAKE (SatFeSem);

			mNewFeRequestParams.LnbNumber = LnbNumber;
			mNewFeRequestParams.LnbType	  = (HsvLnbType)LnbType;
			mNewFeRequestParams.Frequency = Frequency;
			mNewFeRequestParams.Polarization = Polarization;
			mNewFeRequestParams.TuningParams.SymbolRate = SymbolRate;
			mNewFeRequestParams.TuningParams.ModulationStandard = ModlnStd;
			mNewFeRequestParams.TuningParams.Constellation = ModlnType; /* OR plfapidvbs3_ConstellationUnknown */
			mNewFeRequestParams.TuningParams.CodeRate = CodeRate; 
			mNewFeRequestParams.TuningParams.IqMode = -1; /* OR plfapidvbs3_IQModeNormal */
			mNewFeRequestParams.Valid = TRUE;
			mNewFeRequestParams.SatIpParams.ModulationSystem = ModlnStd;
			mNewFeRequestParams.SatIpParams.ModulationType = ModlnType;
			mNewFeRequestParams.SatIpParams.RollOffFactor = RollOff;
			mNewFeRequestParams.SatIpParams.FECInner = FECInner;
			mNewFeRequestParams.SatIpParams.Pilots = Pilots;
				

			SEM_GIVE (SatFeSem);

			mSatFeIns.CurrentMode = SatFeModeTune;
			
			pmp_PmpSend(mPump, EvNewFeRequest, (Nat32)NULL);
		}
		else
		{
			TraceNotice (m, "SatFE: LnbType Mismatch between Requested & Settings ");
		}
	}

	return RetVal;
}

FResult CHsvSatelliteFrontEnd_msilabs_Priv::sisatfrontend_GetSatelliteFrontEndParams(int *LnbNumber,int *LnbType,int *LockStatus,int *LockedFreq,int *Polarization,int *SymbolRate,int *IqMode,int	*Bandwidth)
{
    FResult     RetVal = err_BadParameter;
    int TempPol = 0;
    Bool lockstate = TRUE;
	HsvDvbSParams	DvbsParams;

    *LockedFreq = *SymbolRate = *IqMode = *Bandwidth = 0;

	RetVal = plfdvbs_getParams(&DvbsParams);
	RetVal = plftune_getFreq (LockedFreq);
	
	TempPol = DvbsParams.polarization;
	*SymbolRate	 = DvbsParams.symbolrate;
	lockstate = DvbsParams.lockstatus;

    if (mSatFeIns.CurrentMode == SatFeModeTune)
    {
	    SEM_TAKE (SatFeSem);

        *LnbNumber = mCurrentFeParams.LnbNumber;
		*LnbType = mCurrentFeParams.LnbType;

        SEM_GIVE (SatFeSem);
    }
    else if (mSatFeIns.CurrentMode == SatFeModeBlindScan)
    {
        *LnbNumber = mBlindScanStatus.LnbNumber;
		*LnbType = mBlindScanFrequency[mBlindScanStatus.CurrentTableIndex].LnbType;
    }

	*Polarization = TempPol;
	*LockStatus = (int)lockstate;

    TraceNotice (m, "silabs: GetParams: LnbNum %d Type %d SatFreq %d SymRate %d LockState %d Pol %d",\
                        *LnbNumber, *LnbType, *LockedFreq, *SymbolRate, *LockStatus, *Polarization);

    return RetVal;
}

FResult CHsvSatelliteFrontEnd_msilabs_Priv::sisatfrontend_StartSatelliteBlindScan(int LnbNumber, int Mode)
{
    FResult     RetVal = err_Ok;

	RetVal |= CHK_VALID_LNB (LnbNumber);

	if (RetVal == err_Ok)
	{

        TraceNotice (m, "silabs: BlindScan Mode Selected ");
		mSatFeIns.CurrentMode = SatFeModeBlindScan;
		mSatFeIns.BlindScanMode = Mode;
		SET_STATE(StIdle);
		pmp_PmpSend(mPump, EvStartBlindScan, (Nat32)LnbNumber);
	}

    return RetVal;
}

FResult CHsvSatelliteFrontEnd_msilabs_Priv::sisatfrontend_ContinueSatelliteBlindScan( )
{
    FResult     RetVal = err_Ok;

	pmp_PmpSend(mPump, EvContinueBlindScan, (Nat32)NULL);

    return RetVal;
}



FResult CHsvSatelliteFrontEnd_msilabs_Priv::sisatfrontend_AbortSatelliteBlindScan (int LnbNumber)
{
    FResult     RetVal = err_Ok;

	pmp_PmpSend(mPump, EvAbortBlindScan, (Nat32)LnbNumber);
	
    return RetVal;
}

FResult CHsvSatelliteFrontEnd_msilabs_Priv::sisatfrontend_UnicableEnable (int LnbNumber, Bool Enable)
{
    /* This is called whenever call comes from Menu. So it should be forcefully
     * Set with enable/disable */
	return mEnableUnicableDevice(LnbNumber, Enable, TRUE);
}

Bool CHsvSatelliteFrontEnd_msilabs_Priv::sisatfrontend_IsSameFrequencyInIfRange (int LnbNumber, int SatelliteFreq, int Polarization)
{
	Bool		IsSameFreq = FALSE;
    return IsSameFreq;
}

int CHsvSatelliteFrontEnd_msilabs_Priv::plfapidvbsN_onScanningStandardDetected(int std, int freq)
{
	if (mSatFeIns.CurrentMode == SatFeModeBlindScan)
	{
		tuneresult = TRUE;
		TraceNotice (m, "silabs: BlindScanNtf ");
		pmp_PmpSend(mPump, EvBlindScanNtf, (Nat32)TRUE);
	}
	return 0;
}

int CHsvSatelliteFrontEnd_msilabs_Priv::plfapidvbsN_onScanAborted(void)
{
	pmp_PmpSend(mPump, EvBlindScanEnd, (Nat32)NULL);
	return 0;
}

int CHsvSatelliteFrontEnd_msilabs_Priv::plfapidvbsN_onScanEnded(void)
{
	TraceNotice (m, "silabs: BlindScan End ");
	pmp_PmpSend(mPump, EvBlindScanEnd, (Nat32)NULL);
	return 0;
}

int CHsvSatelliteFrontEnd_msilabs_Priv::plfapidvbsN_onTuned(int tuningresult, int freq)
{
    TraceNotice (m, "silabs: OnLock Changed Ntf ");
    if(tuningresult == 1)
    {
    	tuneresult = TRUE;
    }
    else
    {
    	tuneresult = FALSE;
    }

	if (mSatFeIns.CurrentMode == SatFeModeTune)
	{
		pmp_PmpSend(mPump, EvTuneResult, (Nat32)tuningresult);
	}
	return 0;
}



