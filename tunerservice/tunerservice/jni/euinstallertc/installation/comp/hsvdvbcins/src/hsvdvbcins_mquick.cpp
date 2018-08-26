/**********************************************************************
 *
 *   C Source:       hsvdvbcins_mquick.c
 *   Instance:       blr81mgr_2
 *   Description:    
 *   %created_by:    zaheer %
 *   %date_created:  Fri Nov 30 17:18:32 2012 %
 *
 **********************************************************************/
#include "_hsvdvbcins_mquick.h"

TRACESYMBOL(m, "dvb/installation/hsvdvbcins_mquick")

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
Pump CHsvDvbCInstallation_mquick_Priv::s__mQuickPump;

t_DVBCQuickStatus CHsvDvbCInstallation_mquick_Priv::s__mDvbcQuickStatus;

t_CableDSDesc CHsvDvbCInstallation_mquick_Priv::s__mCableDSDesc;

t_CableDSDesc CHsvDvbCInstallation_mquick_Priv::s__mFlashCableDS;

char CHsvDvbCInstallation_mquick_Priv::s__mDirName[MAX_CHARACTERS];

char CHsvDvbCInstallation_mquick_Priv::s__mFileName[MAX_CHARACTERS];


int CHsvDvbCInstallation_mquick_Priv::s__mConstellation[14] =
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




const FunctionNat32 CHsvDvbCInstallation_mquick_Priv::StateEventMatrix[][StMax] =
{                       /*StIdle            StInit          StFeWait            StNITWait       StDmxWait      StDecision*/
    /*EvStart*/             {FNADDR(FuncStartInstall),  NULL,           NULL,               NULL,           NULL,           NULL},
    /*EvStationFound*/      {NULL,              NULL,           FNADDR(FuncStationFound),   NULL,           NULL,           NULL},
    /*EvStationNotFound*/   {NULL,              NULL,           FNADDR(FuncStationNotFound),NULL,           NULL,           NULL},
    /*EvNITFound*/          {NULL,              NULL,           NULL,               FNADDR(FuncNITFound),   NULL,           NULL},
    /*EvNITNotFound*/       {NULL,              NULL,           NULL,               FNADDR(FuncNITNotFound),NULL,           NULL},
    /*EvDmxNtf*/            {NULL,              NULL,           NULL,               NULL,           FNADDR(FuncDmxData),    NULL},
    /*EvMakeDecision*/      {NULL,              NULL,           NULL,               NULL,           NULL,           FNADDR(FuncMakeDecision)},
    /*EvStop*/              {NULL,              FNADDR(FuncStop),       FNADDR(FuncStop),           FNADDR(FuncStop),       FNADDR(FuncStop),       FNADDR(FuncStop)},
    /*EvSdmStopped*/        {NULL,              FNADDR(FuncSdmStopped), NULL,               FNADDR(FuncSdmStopped), FNADDR(FuncSdmStopped), NULL}
};
                                                                          

/****************************************************************************
 * Static functions Implementation
 ****************************************************************************/
void CHsvDvbCInstallation_mquick_Priv::PumpHandler(int event, Nat32 param )
{
    if(StateEventMatrix[event][mDvbcQuickStatus.State] != NULL)
    {
        FPCALL(StateEventMatrix[event][mDvbcQuickStatus.State])(param);
    }
    else
    {
        TraceDebug(m,"Ignored event = %d, state = %d\r",event,mDvbcQuickStatus.State);
    }
}

void CHsvDvbCInstallation_mquick_Priv::FuncSdmStopped(int param)
{
    Nat32 errorcode = TM_OK, Frequency;
    Nat32 srtmode = 0;

    if(StInit == mDvbcQuickStatus.State)
    {
        feapi_GetFreq (WINDOWID, &Frequency, &errorcode);
        ASSERT(TM_OK == errorcode);
		TraceErr(m,"GetFreq = %ld Frequency %ld",Frequency, (Nat32) mDvbcQuickStatus.Frequency);
		if(CURRENT_MODE == AUTO_MODE)
		{
			mDvbcQuickStatus.StationFound = TRUE;			
			mDvbcQuickStatus.State = StNITWait;
			sigstr_SetSigStrengthMeasured(FALSE);
			sigstr_Initialise();
			sigstr_UpdateSigStrRange();
			sigstr_StartSigStrMeasAll();
			mDvbcQuickStatus.SDTAcquired = FALSE;
			TraceErr(m,"State set to NITWait ctrl_StartCollection done");
			ctrl_StartCollection(mDvbcQuickStatus.CurrentDemux, ctrl_Minimal);
		}
		else
		{
        feapi_SetSearchRates(WINDOWID, mDvbcQuickStatus.SearchRates, mDvbcQuickStatus.SearchRateLen, &errorcode);
        ASSERT(TM_OK == errorcode);

	feapi_SetSymbolRate(srtmode, mDvbcQuickStatus.SymbolRate, &errorcode);
    	ASSERT(TM_OK == errorcode);
	
	TraceErr(m,"SetFreq = %ld\r",(Nat32) mDvbcQuickStatus.Frequency);
        if(mDvbcQuickStatus.Frequency != 0)
        {
            feapi_SetFreq (WINDOWID, mDvbcQuickStatus.Frequency, FALSE, &errorcode);
            ASSERT(TM_OK == errorcode);
        }
        else
        {
            /* This is an erroneous condition, as frequency is 0, so go 4 completion state in such case */
            mResetInstallationState();
            iquickN_OnEvent(iquickN_EventScanCompleted);
        }
        mDvbcQuickStatus.State = StFeWait;
		}
        insN_OnEvent(insN_EventSearchInProgress,mDvbcQuickStatus.Frequency); 
    }
    else
    {
        mDvbcQuickStatus.State = StDecision;
        pmp_PmpSend(mQuickPump, EvMakeDecision, (Nat32)NULL);
    }
	UNUSED(param);
}

void CHsvDvbCInstallation_mquick_Priv::FuncStartInstall(int param)
{
    UNUSED(param);
    TraceDebug(m,"%s\r",__FUNCTION__);
    Nat32 errorcode = TM_OK; 
    mDvbcQuickStatus.ScanState = DvbcQuickScanningDefaultList;

    mDvbcQuickStatus.State = StInit;
    if((CURRENT_MODE == AUTO_MODE) || (CURRENT_MODE == UPDATE_MODE))
    {
        feapi_SetFreqStep(WINDOWID, ((idvbset_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeFreqStepSize))*16), &errorcode);
        ASSERT(TM_OK == errorcode);
    }
    mctl_Stop(HsvMain);
    mStopSdm(mDvbcQuickStatus.CurrentDemux);
}

void CHsvDvbCInstallation_mquick_Priv::FuncStationFound(int param)
{
    TraceDebug(m,"%s\r",__FUNCTION__);
    mUpdateTunerStatus();
    mDvbcQuickStatus.StationFound = TRUE;

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            /* pavan: no separate state required like evMeasNtfSigStr.
               NIT doesnt come into picture during MANUAL mode */
            if(mDvbcQuickStatus.TargeNITFound == TRUE)
            {
                TraceDebug(m,"State set to DmxWait\r");
                mDvbcQuickStatus.State = StDmxWait;
            }
            else
            {
				if(CURRENT_MODE == UPDATE_MODE)
				{
                /* Still in the process of searching NIT. So move to that state */
                TraceDebug(m,"State set to NITWait\r");
                mDvbcQuickStatus.State = StNITWait;
            }
            }
            sigstr_SetSigStrengthMeasured(FALSE);
            sigstr_Initialise();
            sigstr_UpdateSigStrRange();
            sigstr_StartSigStrMeasAll();
            mDvbcQuickStatus.SDTAcquired = FALSE;
            mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].Installed = TRUE;
			
            ctrl_StartCollection(mDvbcQuickStatus.CurrentDemux, ctrl_Minimal);

            break;

        case MANUAL_MODE:
            ASSERT(!"Manual Mode not possible in Quick Scan\r");
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}
void CHsvDvbCInstallation_mquick_Priv::FuncStationNotFound(int param)
{
    mDvbcQuickStatus.StationFound = FALSE;
    TraceDebug(m,"%s\r",__FUNCTION__);

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            TraceDebug(m,"State set to StDecision\r");
            mDvbcQuickStatus.State = StDecision;
            pmp_PmpSend(mQuickPump, EvMakeDecision, (Nat32)NULL);
            break;
        case MANUAL_MODE:
            ASSERT(!"Manual Mode not possible in Quick Scan\r");
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}
void CHsvDvbCInstallation_mquick_Priv::FuncNITFound(int param)
{
    TraceDebug(m,"%s\r",__FUNCTION__);

    /* Though Dmx Data is already available, force the state to DmxWait so that FuncDmxData is called */
    mDvbcQuickStatus.State = StDmxWait;

    pmp_PmpSend(mQuickPump, EvDmxNtf, (Nat32)NULL);

    UNUSED(param);
}

void CHsvDvbCInstallation_mquick_Priv::FuncNITNotFound(int param)
{
    TraceDebug(m,"%s\r",__FUNCTION__);

    if((Nat32)param == mDvbcQuickStatus.Frequency)
    {
        if(mDvbcQuickStatus.State == StNITWait)
        {
            /* No use of waiting for data as there is no valid NIT. So goto make decision */
            TraceDebug(m,"FuncNITNotFound: State set to StDecision\r");
            mStopSdm(mDvbcQuickStatus.CurrentDemux);

        }
        else
        {
            TraceDebug(m,"FuncNITNotFound: Ignored delayed pmpsend\r");
            /* A lazy pmpsendAfter has caused this event. its ok forget it */
        }
    }
    else
    {
        TraceDebug(m,"FuncNITNotFound: Stray Pump Send After\r");
    }
    UNUSED(param);
}

void CHsvDvbCInstallation_mquick_Priv::FuncDmxData(int param)
{
    TraceDebug(m,"%s\r",__FUNCTION__);

    idataacq_AcquireData();

    mDvbcQuickStatus.NumChannelsAdded = idataacq_GetNumberOfDigitalChannelsFound();
    mDvbcQuickStatus.NumChannelsRemoved = idataacq_GetNumberOfDigitalChannelsRemoved();

    insN_OnEvent(insN_EventChannelFound, CURRENT_MODE); 

    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            mStopSdm(mDvbcQuickStatus.CurrentDemux);

            break;

        case MANUAL_MODE:
            ASSERT(!"Manual Mode not possible in Quick Scan\r");
            break;

        default:
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}
void CHsvDvbCInstallation_mquick_Priv::FuncMakeDecision(int param)
{
    Nat32 errorcode = TM_OK;
    Nat32 srtmode = 0;

    TraceDebug(m,"%s\r",__FUNCTION__);

    /* This is called only during auto and update install only */
    switch(CURRENT_MODE)
    {
        case AUTO_MODE:
        case UPDATE_MODE:
            switch(mDvbcQuickStatus.ScanState)
            {
                case DvbcQuickIdle:
                    ASSERT(FALSE);
                    break;

                case DvbcQuickScanningDefaultList:
                    mDvbcQuickStatus.Frequency = idvbset_GetNextAttributeValue(CURRENT_MODE, rins_AttributeNetworkFreq, mDvbcQuickStatus.Frequency);
                    mDvbcQuickStatus.State = StFeWait;
                    if(INVALID_FREQUENCY != mDvbcQuickStatus.Frequency)
                    {
                        /*PVD: This is not required. StartSearch should solve*/
			    TraceDebug(m,"%s : %d :  using the next frequency form homing list freq = %ld MHz", __FUNCTION__, __LINE__,(Nat32) (mDvbcQuickStatus.Frequency >> 4));
			    srtmode = 0;
			    feapi_SetSymbolRate(srtmode, mDvbcQuickStatus.SymbolRate, &errorcode);
			    ASSERT(TM_OK == errorcode);	

                        feapi_SetFreq (WINDOWID, mDvbcQuickStatus.Frequency, FALSE, &errorcode);
                        insN_OnEvent(insN_EventSearchInProgress,mDvbcQuickStatus.Frequency); 
                        ASSERT(TM_OK == errorcode);
                    }
                    else
                    {
                        TraceDebug(m,"%s : %d :  exhausted the homing frequency list, starting scan from beginning with freq = %dMHz", __FUNCTION__, __LINE__, (START_FREQUENCY >> 4));
                        if( (mDvbcQuickStatus.FrequencyMode == rins_ManualValue) && 
                                ( ( (eurdiv_GetDVBCMode() != eurdiv_ScanDVBCLite) || (mDvbcQuickStatus.StationFound == TRUE) )
                                  || (CURRENT_MODE != AUTO_MODE))  )
                        {
                            if((rins_ManualValue == mDvbcQuickStatus.NitMode) && (NIT_TYPE_INVALID != mDvbcQuickStatus.TargetNITType))
                            {
                                TraceDebug(m,"%s : %d :  Using the Nit other awith freq", __FUNCTION__, __LINE__);
                                /* 
                                   1. eurdiv_GetNitPriority was set to both actual and other, in which case we first look for NIT actual
                                   2. We could not find nit actual, but we did find NIT other on some frequency which we have remembered in mDvbcQuickStatus.NonPreferredNitFrequency
                                   3. Use the nit other as preferred nit, and tune to the frequency where we first found NIT other with valid CDS*/


                            }
                            else
                            {
                                /* 
                                   We come here in below conditions
                                   When the NIT mode is automatic and we could not find NIT actual
                                   OR
                                   When the NIT mode is manual and we could not find NIT actual or NIT other
                                   */
                                TraceDebug(m,"MakeDecision: NIT OTHER/ACTUAL not found, Scan complete\r");
                                mInvalidateFlash();
                                mResetInstallationState();
                                iquickN_OnEvent(iquickN_EventScanCompleted);
                            }
                        }
                        else
                        {
							TraceNotice (m, "Frequency Mode %d DVBCMode %d StationFound %d TargetNITFound %d ", mDvbcQuickStatus.FrequencyMode, \
											eurdiv_GetDVBCMode() , mDvbcQuickStatus.StationFound, mDvbcQuickStatus.TargeNITFound);
							if( (mDvbcQuickStatus.FrequencyMode == rins_AutomaticValue) && (eurdiv_GetDVBCMode() != eurdiv_ScanDVBCLite) && 
								(mDvbcQuickStatus.StationFound == TRUE) && (FALSE == mDvbcQuickStatus.TargeNITFound) && (CURRENT_MODE == AUTO_MODE) )
							{
								/* To handle the use case in which from NIT Actual is not found in the Automatic mode.
									Prescan find sht NIT. But in auto installation same NID is not found. Gracefully finishing the installation */
								TraceNotice (m, "Target NIT is not found.");
								mInvalidateFlash();
								mResetInstallationState();
								iquickN_OnEvent(iquickN_EventScanCompleted);
							}
							else
							{							
								mDvbcQuickStatus.ScanState = DvbcQuickScanningNetworkFreq;
								mDvbcQuickStatus.Frequency = mDvbcQuickStatus.StartFrequency;
								srtmode = 0;
								feapi_SetSymbolRate(srtmode, mDvbcQuickStatus.SymbolRate, &errorcode);
								ASSERT(TM_OK == errorcode);	
							
								TraceNotice(m,"%s %d set freq : %ld", __FUNCTION__, __LINE__, mDvbcQuickStatus.Frequency);
								feapi_SetFreq (WINDOWID, mDvbcQuickStatus.Frequency, FALSE, &errorcode);
								ASSERT(TM_OK == errorcode);
								insN_OnEvent(insN_EventSearchInProgress,mDvbcQuickStatus.Frequency); 
							}
                        }
                    }

                    break;

                case DvbcQuickScanningNetworkFreq:
                    feapi_GetFreq(WINDOWID, &mDvbcQuickStatus.Frequency, &errorcode);
                    ASSERT(TM_OK == errorcode);
                    if(mDvbcQuickStatus.Frequency < mDvbcQuickStatus.EndFrequency)
                    {
                        /* End of frequency band is not reached yet. Continue tuning */
                        TraceDebug(m,"%s : %d", __FUNCTION__, __LINE__);
                        mDvbcQuickStatus.State = StFeWait;
                        feapi_StartSearch(WINDOWID, mDvbcQuickStatus.Frequency, tmFe_SmDefault, mDvbcQuickStatus.EndFrequency, &errorcode );/* ANEESH: TODO: Confirm the change */
                        ASSERT(TM_OK == errorcode);
                    }
                    else
                    {
                        if((rins_ManualValue == mDvbcQuickStatus.NitMode) && (NIT_TYPE_INVALID != mDvbcQuickStatus.TargetNITType))
                        {
                            TraceDebug(m,"%s : %d :  Using the Nit other awith freq", __FUNCTION__, __LINE__);
                            /* 
                               1. eurdiv_GetNitPriority was set to both actual and other, in which case we first look for NIT actual
                               2. We could not find nit actual, but we did find NIT other on some frequency which we have remembered in mDvbcQuickStatus.NonPreferredNitFrequency
                               3. Use the nit other as preferred nit, and tune to the frequency where we first found NIT other with valid CDS */


                        }
                        else
                        {
                            /* 
                               We come here in below conditions
                               When the NIT mode is automatic and we could not find NIT actual
                               OR
                               When the NIT mode is manual and we could not find NIT actual or NIT other
                               */
                            TraceDebug(m,"MakeDecision: NIT OTHER/ACTUAL not found, Scan complete\r");
                            mInvalidateFlash();
                            mResetInstallationState();
                            iquickN_OnEvent(iquickN_EventScanCompleted);
                        }
                    }
                    break;

                case DvbcQuickScanningCDS:
                    if(mCableDSDesc.CurrentTsIndex >= 0)
                    {
                        TraceDebug(m,"%s : %d :  Current frequency frm CDS freq  = %ld MHz", __FUNCTION__, __LINE__,(Nat32) (CURRENT_FREQ >> 4));
                    }

                    if(mGetNextcableDS() )
                    {
                        TraceDebug(m,"%s : %d :  Next frequency frm CDS freq  = %ld MHz", __FUNCTION__, __LINE__,(Nat32) (CURRENT_FREQ >> 4));
                        mDvbcQuickStatus.State = StFeWait;
                        /* Start Tuning with these parameters */
                        mDvbcQuickStatus.SymbolRate = CURRENT_SYM_RATE;
                        mDvbcQuickStatus.Frequency = CURRENT_FREQ;
                        mDvbcQuickStatus.ModulationType = CURRENT_MODULATION;

                        TraceDebug(m,"SetModulation = 0x%x\r",mConstellation[mDvbcQuickStatus.ModulationType]);
                        feapi_SetConstellation(WINDOWID, feapi_ChanDecDvbC, (tmFe_Constellation_t)mConstellation[mDvbcQuickStatus.ModulationType], &errorcode);
                        ASSERT(TM_OK == errorcode);
						
			srtmode = 1;
                        TraceDebug(m,"srtmode = %d SymRate = %ld \r",srtmode,(Nat32)mDvbcQuickStatus.SymbolRate);
                        feapi_SetSymbolRate(srtmode, mDvbcQuickStatus.SymbolRate, &errorcode);
                        ASSERT(TM_OK == errorcode);
						
					
	
                        TraceDebug(m,"Setting Freq = %ld \r",(Nat32)(mDvbcQuickStatus.Frequency>>4));

                        feapi_SetFreq (WINDOWID, mDvbcQuickStatus.Frequency, FALSE, &errorcode);
                        ASSERT(TM_OK == errorcode);
                        insN_OnEvent(insN_EventSearchInProgress,mDvbcQuickStatus.Frequency); 
                    }
                    else
                    {
                        /* 
                           All the frequencies described by this NIT are traversed.
                           Implies Installation based on Target NIT complete 
                           */
                        /* No Alternate values. So just quit */
                        if(eurdiv_GetAlternateTSLocation(rins_Cable) == eurdiv_AltNone)
                        {
                            TraceDebug(m,"MakeDecision: TargetNIT Found and Install Success from CDSD list\r");

                            TraceDebug(m,"Setting all preferred values after NIT is found\r");

                            idvbset_SetPreferred(rins_AttributeSymbolRate, mDvbcQuickStatus.TargetNITSymRate, TRUE);
                            idvbset_SetPreferred(rins_AttributeNetworkFreq, mDvbcQuickStatus.TargetNITFreq, TRUE);
                            idvbset_SetPreferred(rins_AttributeNetworkId, mDvbcQuickStatus.TargetNITValue, TRUE);
							/* Setting of operators for Germany Cable */
							if(eurdiv_StaticTable())
							{
								if(KDG_NETWORK(mDvbcQuickStatus.TargetNITValue))
								{
									idvbset_SetPreferred(rins_AttributeNetworkOperator, AppApiOperatorKDG, TRUE);
								}
								else if(KABLEBW_NETWORK(mDvbcQuickStatus.TargetNITValue))
								{
									idvbset_SetPreferred(rins_AttributeNetworkOperator, AppApiOperatorKabelBW, TRUE);
								}
							}

                            /* To delete services based on Service List Desc */
                            //idataacq_DeleteServices();

                            /* Set all preferred values */
                            idataacq_SyncTemporaryTableRecords();
                        }
                        else
                        {
                            /* There are alternate values. So start tuning to them starting from first TS */
                            mCableDSDesc.CurrentTsIndex = 0;
                            mDvbcQuickStatus.ScanState = DvbcQuickScanningAlt;
                            mDvbcQuickStatus.State = StDecision;
                            pmp_PmpSend(mQuickPump, EvMakeDecision, (Nat32)NULL);
                        }
                    }
                    break;

                case DvbcQuickScanningAlt:
                    if(mGetNextAltTs())
                    {
                        TraceDebug(m,"%s : %d :  Next frequency frm Alt freq  = %ld MHz", __FUNCTION__, __LINE__,(Nat32) (ALT_FREQ >> 4));
                        if(mDvbcQuickStatus.Frequency != ALT_FREQ)
                        {
                            mDvbcQuickStatus.State = StFeWait;
                            /* Start Tuning with these parameters */
                            mDvbcQuickStatus.SymbolRate = ALT_SYM_RATE;
                            mDvbcQuickStatus.Frequency = ALT_FREQ;
                            mDvbcQuickStatus.ModulationType = ALT_MODULATION;

                            TraceDebug(m,"SetAltModulation = 0x%x\r",mConstellation[mDvbcQuickStatus.ModulationType]);
                            feapi_SetConstellation(WINDOWID, feapi_ChanDecDvbC, (tmFe_Constellation_t)mConstellation[mDvbcQuickStatus.ModulationType], &errorcode);
                            ASSERT(TM_OK == errorcode);
			    srtmode = 1;
                            TraceDebug(m,"srtmode = %d AltSymRate = %ld \r",(Nat32)mDvbcQuickStatus.SymbolRate);
                            feapi_SetSymbolRate(srtmode, mDvbcQuickStatus.SymbolRate, &errorcode);
                            ASSERT(TM_OK == errorcode);

                            TraceDebug(m,"Setting AltFreq = %ld \r",(Nat32)(mDvbcQuickStatus.Frequency>>4));

                            feapi_SetFreq (WINDOWID, mDvbcQuickStatus.Frequency, FALSE, &errorcode);
                            ASSERT(TM_OK == errorcode);
                            insN_OnEvent(insN_EventSearchInProgress,mDvbcQuickStatus.Frequency); 
                        }
                        else
                        {
                            /* Tuning to the same frequency. So directly start SDM for SDT Other */
                            TraceDebug(m,"State set to DmxWait\r");
                            mDvbcQuickStatus.State = StDmxWait;
                            ctrl_StartCollection(mDvbcQuickStatus.CurrentDemux, ctrl_Minimal);
                        }
                    }
                    else
                    {
                        TraceDebug(m,"MakeDecision: TargetNIT Found and Install Success from CDSD list\r");

                        TraceDebug(m,"Setting all preferred values after NIT is found\r");

                        idvbset_SetPreferred(rins_AttributeSymbolRate, mDvbcQuickStatus.TargetNITSymRate, TRUE);
                        idvbset_SetPreferred(rins_AttributeNetworkFreq, mDvbcQuickStatus.TargetNITFreq, TRUE);
                        idvbset_SetPreferred(rins_AttributeNetworkId, mDvbcQuickStatus.TargetNITValue, TRUE);

						/* Setting of operators for Germany Cable */
						if(eurdiv_StaticTable())
						{
							if(KDG_NETWORK(mDvbcQuickStatus.TargetNITValue))
							{
								idvbset_SetPreferred(rins_AttributeNetworkOperator, AppApiOperatorKDG, TRUE);
							}
							else if(KABLEBW_NETWORK(mDvbcQuickStatus.TargetNITValue))
							{
								idvbset_SetPreferred(rins_AttributeNetworkOperator, AppApiOperatorKabelBW, TRUE);
							}
						}
                        /* To delete services based on Service List Desc */
                        //idataacq_DeleteServices();

                        /* Set all preferred values */
                        idataacq_SyncTemporaryTableRecords();
                    }

                    break;
                default:
                    ASSERT(FALSE);
                    break;
            }        
            break;

        case MANUAL_MODE:
            /* should not reach here */
            ASSERT(FALSE);
            break;
    }
    UNUSED(param);
}

void CHsvDvbCInstallation_mquick_Priv::FuncStop(int param)
{
    tmErrorCode_t errorcode = TM_OK;
    TraceDebug(m,"%s\r",__FUNCTION__);

    switch(mDvbcQuickStatus.State)
    {
        case StFeWait:
            feapi_StopSearch(WINDOWID, &errorcode);
            ASSERT(TM_OK  ==  errorcode);
            break;
        case StDmxWait:
        case StNITWait:
            mStopSdm(mDvbcQuickStatus.CurrentDemux);
            sigstr_StopSigStrMeasAll();
            break;
        case StDecision:
            /* pavan: Not possible actually. State change happens in Makedecision anyways */
            TraceDebug(m,"Nothing can be done ??\r");
            break;
        default:
            ASSERT(FALSE);
            break;
    }
    mResetInstallationState();
    iquickN_OnEvent(iquickN_EventScanStopped);
    UNUSED(param);
}

int CHsvDvbCInstallation_mquick_Priv::mMapFromHsvToPlfDvbcModulation(int InputModulation)
{
	
	int 	OutputModulation = InputModulation;
	switch (InputModulation)
	{
	   case HsvQam16:
			   OutputModulation = PLF_TUNING_DVBC_QAM16;
			   break;
	   case HsvQam32:
			   OutputModulation = PLF_TUNING_DVBC_QAM32;
			   break;
	   case HsvQam64:
			   OutputModulation = PLF_TUNING_DVBC_QAM64;
			   break;
	   case HsvQam128:
			   OutputModulation = PLF_TUNING_DVBC_QAM128;
			   break;
	   case HsvQam256:
			   OutputModulation = PLF_TUNING_DVBC_QAM256;
			   break;
	   default:
			   break;
	}
	return OutputModulation;
	

}

void CHsvDvbCInstallation_mquick_Priv::mUpdateTunerStatus()
{
    int param1;
    Nat32 errorcode = TM_OK;

    TraceDebug(m,"%s\r",__FUNCTION__);

    feapi_GetFreq(WINDOWID, &mDvbcQuickStatus.Frequency, &errorcode);
    ASSERT(TM_OK  ==  errorcode);

    TraceDebug(m,"Frequency for StationFound = %ld\r",(Nat32)(mDvbcQuickStatus.Frequency>>4));

    feapi_GetActualConstellation(WINDOWID,feapi_ChanDecDvbC, (tmFe_Constellation_t*)(&param1), &errorcode);
    ASSERT(TM_OK  ==  errorcode);
    mDvbcQuickStatus.ModulationType = param1; //(Nat8)FindHsvValue(param1, mConstellation, sizeof(mConstellation));

    feapi_GetActualCodeRate(WINDOWID, &mDvbcQuickStatus.SymbolRate, &errorcode);
    ASSERT(TM_OK  ==  errorcode);
}

Bool CHsvDvbCInstallation_mquick_Priv::mGetNextcableDS(void)
{
    Bool retval = TRUE;

    TraceDebug(m,"%s\r",__FUNCTION__);

    if (mCableDSDesc.NumOfTs > 0) 
    {

        if(mCableDSDesc.CurrentTsIndex >= 0)
        {
            if (mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].NumOfCDSD > 0) 
            {
                if((mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentCDSDIndex + 1) == mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].NumOfCDSD)
                {
                    if((mCableDSDesc.CurrentTsIndex + 1) == mCableDSDesc.NumOfTs)
                    {
                        retval = FALSE;
                        TraceDebug(m,"Exhausted CDSDs\r");
                    }
                    else
                    {
                        mCableDSDesc.CurrentTsIndex++;
                        mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentCDSDIndex = 0;
                    }
                }
                else
                {
                    mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentCDSDIndex++;
                }
            }
            else 
            {
                retval = FALSE;
                TraceDebug(m,"mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].NumOfCDSD is Zero\r");
            }
        }
        else
        {
            mCableDSDesc.CurrentTsIndex = 0;
            mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentCDSDIndex = 0;
        }
    }
    else 
    {
        retval = FALSE;
        TraceDebug(m,"mCableDSDesc.NumOfTs is Zero\r");
    }


    TraceDebug(m,"mGetNextCableDS: retval = %d\r",retval);
    return retval;
}

Bool CHsvDvbCInstallation_mquick_Priv::mGetNextAltTs()
{
    Bool retval = FALSE;

    while(mCableDSDesc.CurrentTsIndex < mCableDSDesc.NumOfTs)
    {
        if((mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].Installed == FALSE) &&
                (mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].NumOfAltTs > 0))
        {
            if((mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentAltTsIndex + 1) == mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].NumOfAltTs)
            {
                /* Num of Alt Frequencies exhausted. So goto next Ts */
            }
            else
            {
                /* Found next alt frequency */
                mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CurrentAltTsIndex++;
                retval = TRUE;
                break;
            }
        }
        mCableDSDesc.CurrentTsIndex++;
    }
    TraceDebug(m,"mGetNextAltTs: retval = %d\r",retval);
    return retval;
}

void CHsvDvbCInstallation_mquick_Priv::mOnNitAvailable()
{
    int errorcode = TM_OK;
    Nat16 NetworkID = INVALID_NETWORKID;
    Bool lFallbackToNITActualReqd = FALSE;


    TraceDebug(m,"%s\r",__FUNCTION__);

    if(FALSE == mDvbcQuickStatus.TargeNITFound)
    {
        TraceDebug(m,"%d: mDvbcQuickStatus.TargeNITFound = FALSE", __LINE__);

        strapi_GetByKey(HsvMain, HSVSPID(ActualNetworkID, dvb, nit), 0, 0, 0, &NetworkID);

        if(NIT_ACTUAL_REQD)
        {
            /* ActualNIT is present */
            TraceDebug(m,"%d: NIT_ACTUAL_REQD && strapi_GetByKey succeeded for NetworkId", __LINE__);

            if((VALID_NTKID(NetworkID)) || (rins_AutomaticValue == mDvbcQuickStatus.NitMode) || (eurdiv_InstallTestStreams(CURRENT_MODE, rins_Cable) == eurdiv_Install))
            {
                /* First if -> NO Target NIT is set. Second if -> Target NIT is set and that is found. So enter */
                TraceDebug(m,"%d: Valid Network Id Found", __LINE__);
                if( (mDvbcQuickStatus.TargetNITValue == INVALID_NETWORKID) || (mDvbcQuickStatus.TargetNITValue == NetworkID) )
                {
                    if(mLoadCDSDFromStrapi(HSVSPID(ActualCableDS, dvb, nit), HSVSPID(ActualTSRelocated, dvb, nit)))
                    {
                        TraceDebug(m,"NitAvail: Found NitActual ID = 0x%x\r",NetworkID);
                        mDvbcQuickStatus.TargetNITValue = NetworkID;
                        mDvbcQuickStatus.TargetNITType = eurdiv_NitActual;
                        if(strapi_GetByKey(HsvMain, HSVSPID(ActualNITVer, dvb, nit), 0, 0, 0, (void*) (&mDvbcQuickStatus.TargetNITVersion)))
                        {
                            TraceDebug(m,"NitAvail: Found NitActual ID Version = 0x%x\r",mDvbcQuickStatus.TargetNITVersion);
                        }
                        feapi_GetFreq(WINDOWID, &mDvbcQuickStatus.TargetNITFreq, (Nat32*)&errorcode);
                    }
                    else
                    {
                        TraceDebug(m,"NO cable delivery system descriptors found\r");
                    }
                }
                else
                {
                    lFallbackToNITActualReqd = TRUE;
                    TraceDebug(m,"NitAvail: Fallback to NIT Actual required , Network ID = 0x%x ", NetworkID);
                }
            }
        }
        if(NIT_OTHER_REQD && (rins_ManualValue == mDvbcQuickStatus.NitMode))
        {
            /* OtherNIT is present. If Targetnitvalue is valid one it means that target NIT mode is manual. So dont look at NIT Other */
            HSVSPTYPE(OtherNetworkIDInfo, dvb, nit) networkinfo;

            TraceDebug(m,"Target NID = %d", mDvbcQuickStatus.TargetNITValue);

            if(strapi_GetByKey(HsvMain, HSVSPID(OtherNetworkIDInfo, dvb, nit),mDvbcQuickStatus.TargetNITValue, 0, 0, &networkinfo))
            {
                TraceDebug(m,"%d: NIT_OTHER_REQD && strapi_GetByKey succeeded for NetworkId", __LINE__);

                /* TS Relocated is not present in NIT other */
                if(mLoadCDSDFromStrapi(HSVSPID(OtherCableDS, dvb, nit), INVALID_HSVSPID))
                {
                    TraceDebug(m,"NitAvail: Found NitOther ID = 0x%x and Version = %d\r",NetworkID,networkinfo.VersionNumber);
                }
                else
                {
                    TraceDebug(m,"NO cable delivery system descriptors found\r");
                }
                lFallbackToNITActualReqd = FALSE;
                /* Irrespective of presence/absence of CDSD, store it */
                TraceDebug(m,"NitAvail: Found NitOther ID = %d\r", mDvbcQuickStatus.TargetNITValue);
                mDvbcQuickStatus.TargetNITType = eurdiv_NitOther;
                mDvbcQuickStatus.PreferredNit = eurdiv_NitOther;
                mDvbcQuickStatus.TargetNITVersion = networkinfo.VersionNumber;
                feapi_GetFreq(WINDOWID, &mDvbcQuickStatus.TargetNITFreq, (Nat32*)&errorcode);
            }
            else
            {
                TraceDebug(m,"NIT Actual found is not of entered Manual Value\r");
            }
        }
        if(lFallbackToNITActualReqd)
        {
            if(((VALID_NTKID(NetworkID)) || (eurdiv_InstallTestStreams(CURRENT_MODE, rins_Cable) == eurdiv_Install)) && (UPDATE_INSTALL))
            {
                if(mLoadCDSDFromStrapi(HSVSPID(ActualCableDS, dvb, nit), HSVSPID(ActualTSRelocated, dvb, nit)))
                {
                    TraceDebug(m,"NitAvail: Found NitActual ID = 0x%x\r",NetworkID);
                    mDvbcQuickStatus.TargetNITValue = NetworkID;
                    mDvbcQuickStatus.TargetNITType = eurdiv_NitActual;
                    if(strapi_GetByKey(HsvMain, HSVSPID(ActualNITVer, dvb, nit), 0, 0, 0, (void*) (&mDvbcQuickStatus.TargetNITVersion)))
                    {
                        TraceDebug(m,"NitAvail: Found NitActual ID Version = 0x%x\r",mDvbcQuickStatus.TargetNITVersion);
                    }
                    feapi_GetFreq(WINDOWID, &mDvbcQuickStatus.TargetNITFreq, (Nat32*)&errorcode);
                }
                else
                {
                    TraceDebug(m,"NO cable delivery system descriptors found\r");
                }
            }
        }

        if(mDvbcQuickStatus.TargetNITType == mDvbcQuickStatus.PreferredNit)
        {
            TraceDebug(m,"NitAvail: Found preferred NIT. Send EvNitFound\r");
            mDvbcQuickStatus.TargeNITFound = TRUE;
            mDvbcQuickStatus.ScanState = DvbcQuickScanningCDS;
            feapi_GetActualCodeRate(WINDOWID, &mDvbcQuickStatus.TargetNITSymRate, (Nat32*)&errorcode);
            mCableDSDesc.TargetNITType = mDvbcQuickStatus.TargetNITType;
            mCableDSDesc.TargetNITValue = mDvbcQuickStatus.TargetNITValue;
            mFlashCableDS.TargetNITType = mDvbcQuickStatus.TargetNITType;
            mFlashCableDS.TargetNITValue = mDvbcQuickStatus.TargetNITValue;

            feapi_SetSearchRates(WINDOWID, NULL, 0, (Nat32*)&errorcode);
            idataacq_AcquireONID();
            /* Acquire LCN from this target NIT before it goes away */
            idataacq_AcquireLCNData();

            /* Acquire Service List Data before it goes away */
            idataacq_AcquireServiceListData();

			if((idvbset_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeNetworkOperator) == rins_UPC))
			{
				idataacq_AcquireSDTOtherData();
			}



            iquickN_OnEvent(iquickN_EventTargetNITFound);
            mWriteCableDSToFlash();
            /* this change is done so that it starts from 0th frequency
               i.s.o from 1. In mgetnextcableds, it becomes 0 else its missed */
            mCableDSDesc.CurrentTsIndex = -1;

            mStopSdm(mDvbcQuickStatus.CurrentDemux);

        }

        else
        {
            TraceDebug(m,"Not Nit Actual or Nit Other Found\r");
        }
    }
}

void CHsvDvbCInstallation_mquick_Priv::mGetPathName(char* dirName, char* FileName , char* PathName)
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

void CHsvDvbCInstallation_mquick_Priv::mWriteCableDSToFlash()
{
    FILE* fp;
    int writenrec = 0;

    TraceDebug(m,"Fopen of %s\r", mFileName);

    fp = fopen(mFileName, "wb");

    if(fp)
    {
        writenrec = fwrite((Address)(&mCableDSDesc), sizeof(mCableDSDesc), 1, fp);
        if(writenrec)
        {
            TraceDebug(m,"Written Cable Del Sys to Flash\r");
        }
        else
        {
            TraceDebug(m,"Write Cable Del Sys to Flash Fail\r");
        }
        fclose(fp);
    }
    else
    {
        TraceDebug(m,"Unable to open %s\r",mFileName);
        ASSERT(!"Unable to open CABLE_DEL_FILEPATH");
    }
}

void CHsvDvbCInstallation_mquick_Priv::mInvalidateFlash()
{
    FILE *fp, *svcListfp;
    int writenrec = 0;
    char FileName[MAX_CHARACTERS];
    t_ServiceList SvcListData;

    TraceDebug(m,"Fopen of %s\r", mFileName);
    mCableDSDesc.TargetNITType = rins_NitNone;
    mCableDSDesc.TargetNITValue = INVALID_NETWORKID;

    fp = fopen(mFileName, "wb");

    if(fp)
    {
        writenrec = fwrite((Address)(&mCableDSDesc), sizeof(mCableDSDesc), 1, fp);
        if(writenrec)
        {
            TraceDebug(m,"Written Cable Del Sys to Flash\r");
        }
        else
        {
            TraceDebug(m,"Write Cable Del Sys to Flash Fail\r");
        }
        fclose(fp);
    }
    else
    {
        TraceDebug(m,"Unable to open %s\r",mFileName);
        ASSERT(!"Unable to open CABLE_DEL_FILEPATH");
    }

	str_strcpy(mDirName, "/user_setting/rw/tvserver/databases/channellib/");
    mGetPathName(mDirName, SVC_LIST_DESC_FILEPATH, FileName);

    TraceDebug(m,"Fopen of %s\r", FileName);
    svcListfp = fopen(FileName, "wb");

    if(svcListfp)
    {
        SvcListData.VersionNumber = INVALID_VERSION;
        SvcListData.NumOfRecords = 0;
        writenrec = fwrite((Address)(&SvcListData), sizeof(SvcListData), 1, svcListfp);
        if(writenrec)
        {
            TraceDebug(m,"Written SLD to Flash\r");
        }
        else
        {
            TraceDebug(m,"Write SLD to Flash Fail\r");
        }
        fclose(svcListfp);
    }
    else
    {
        TraceDebug(m,"Unable to open %s\r",FileName);
        ASSERT(!"Unable to open SVC_LIST_DESC_FILEPATH");
    }
}

Bool CHsvDvbCInstallation_mquick_Priv::mLoadCDSDFromStrapi(int hsvspid, int hsvaltspid)
{
    Bool retval = TRUE;
    int i, j;
    HSVSPTYPE(ActualCableDS, dvb, nit)    CableDSDesc;
    HSVSPTYPE(ActualTSRelocated, dvb, nit)  TsRelocDesc;

    mCableDSDesc.NumOfTs = strapi_GetSize(HsvMain, hsvspid);

    TraceDebug(m,"Total NumofCDSD = %d\r",mCableDSDesc.NumOfTs);
    if(mCableDSDesc.NumOfTs)
    {
        if(mCableDSDesc.NumOfTs > MAX_MUXES_PER_NTK)
        {
            TraceDebug(m,"NitAvail: numCableDSDesc is more than 10\r");
            mCableDSDesc.NumOfTs = MAX_MUXES_PER_NTK;
        }
        for(i = 0; i < mCableDSDesc.NumOfTs; i++ )
        {
            if(strapi_GetByIndex(HsvMain, hsvspid, i, (void*)(&CableDSDesc)))
            {
                mCableDSDesc.TsParam[i].ONID = CableDSDesc.Original_NetworkId;
                mCableDSDesc.TsParam[i].Tsid = CableDSDesc.Tsid;
                mCableDSDesc.TsParam[i].NumOfCDSD = CableDSDesc.NumOfCDSD;
                mCableDSDesc.TsParam[i].CurrentCDSDIndex = -1;
                mCableDSDesc.TsParam[i].Installed = FALSE;

                TraceDebug(m,"NumofCDSD = %d\r",CableDSDesc.NumOfCDSD);

                for(j = 0; j < CableDSDesc.NumOfCDSD; j++)
                {
                    mCableDSDesc.TsParam[i].CableDescParam[j].Frequency = CableDSDesc.CDSD[j].Frequency;
                    TraceDebug(m,"Frequency[%d] from CDS = %d\r",j,(CableDSDesc.CDSD[j].Frequency>>4));
                    mCableDSDesc.TsParam[i].CableDescParam[j].Modulation = CableDSDesc.CDSD[j].Modulation;
                    mCableDSDesc.TsParam[i].CableDescParam[j].SymbolRate = CableDSDesc.CDSD[j].SymbolRate;
                }
                if(eurdiv_GetAlternateTSLocation(rins_Cable) == eurdiv_AltTSRelocatedDesc)
                {
                    /* populate from TS Relcoated Desc */
                    mCableDSDesc.TsParam[i].NumOfAltTs = 0;
                    if(hsvaltspid != INVALID_HSVSPID)
                    {
                        TraceDebug(m,"ONID TsReloc = %d, TSID = %d, NID = %d\r",CableDSDesc.Original_NetworkId,CableDSDesc.Tsid,CableDSDesc.NetworkId);
                        if(strapi_GetByKey(HsvMain, hsvaltspid, CableDSDesc.Original_NetworkId, CableDSDesc.Tsid, CableDSDesc.NetworkId, (void*)(&TsRelocDesc)))
                        {
                            mCableDSDesc.TsParam[i].NumOfAltTs = TsRelocDesc.NumOfCDSD;
                            mCableDSDesc.TsParam[i].CurrentAltTsIndex = -1;

                            TraceDebug(m,"NumofAltCDSD = %d\r",TsRelocDesc.NumOfCDSD);

                            for(j = 0; j < TsRelocDesc.NumOfCDSD; j++)
                            {
                                mCableDSDesc.TsParam[i].AltTsParam[j].Frequency = TsRelocDesc.CDSD[j].Frequency;
                                TraceDebug(m,"Frequency[%d] from TsReloc = %d\r",j,(TsRelocDesc.CDSD[j].Frequency>>4));
                                mCableDSDesc.TsParam[i].AltTsParam[j].Modulation = TsRelocDesc.CDSD[j].Modulation;
                                mCableDSDesc.TsParam[i].AltTsParam[j].SymbolRate = TsRelocDesc.CDSD[j].SymbolRate;
                            }
                        }
                        else
                        {
                            TraceDebug(m,"TsReloc not found for <onid,tsid,nid> = <%d,%d,%d>\r",CableDSDesc.Original_NetworkId, CableDSDesc.Tsid, CableDSDesc.NetworkId);
                        }
                    }
                }
                else if(eurdiv_GetAlternateTSLocation(rins_Cable) == eurdiv_AltHomingFrequency)
                {
                    mCableDSDesc.TsParam[i].NumOfAltTs = 1;
                    mCableDSDesc.TsParam[i].CurrentAltTsIndex = -1;
                    mCableDSDesc.TsParam[i].AltTsParam[0].Frequency = mDvbcQuickStatus.Frequency;
                    mCableDSDesc.TsParam[i].AltTsParam[0].Modulation = mDvbcQuickStatus.ModulationType;
                    mCableDSDesc.TsParam[i].AltTsParam[0].SymbolRate = mDvbcQuickStatus.SymbolRate;
                    TraceDebug(m,"Alt Frequencies are from Homing Mux\r");
                }
                else if(eurdiv_GetAlternateTSLocation(rins_Cable) == eurdiv_AltNone)
                {
                    mCableDSDesc.TsParam[i].NumOfAltTs = 0;
                    mCableDSDesc.TsParam[i].CurrentAltTsIndex = 0;
                    TraceDebug(m,"No Alt Frequencies\r");
                }
            }
            else
            {
                TraceDebug(m,"strapi_GetByIndex failed");
            }
        }
        TraceDebug(m,"No Of CDS records found = %d", mCableDSDesc.NumOfTs);
    }
    else
    {
        retval = FALSE;
    }
    return retval;
}

/***************************
  provides IHsvPower
 ****************************/
void CHsvDvbCInstallation_mquick_Priv::iquickpow_Init()
{
    mQuickPump = pmp_PmpCreateEx(pen_PumpEngine, PumpHandler, FALSE, "hsvdvbcins_mquick_pmp");
}

void CHsvDvbCInstallation_mquick_Priv::iquickpow_TurnOn()
{
    /* Read all CableDS from flash and update it in RAM */
    FILE* fp;
    int readrec = 0;
    
/*
    ffsdir_GetDirPath( mDirName, ffsdir_Boot, ffsdir_Broadcast );
    
	if(str_strlen(mDirName))
    {
        
    }
    else
    {
        ASSERT(!"Boot parition mount has failed");
    }
	str_strcat(mDirName, "/channellib/");
	*/
	str_strcpy(mDirName, "/user_setting/rw/tvserver/databases/channellib/");
	
    TraceDebug(m,"DirName = %s\r",mDirName);

    mGetPathName(mDirName, CABLE_DEL_FILEPATH, mFileName);

    TraceDebug(m,"Fopen of %s\r", mFileName);

    fp = fopen(mFileName, "rb");

    if(fp)
    {
        readrec = fread((Address)(&mFlashCableDS), sizeof(mFlashCableDS), 1, fp);
        if(readrec)
        {
            TraceDebug(m,"Read Cable Del Sys from Flash\r");
        }
        else
        {
            mFlashCableDS.TargetNITValue = INVALID_NETWORKID;
            TraceDebug(m,"Read Cable Del Sys from Flash Fail\r");
        }
        fclose(fp);
    }
    else
    {
        mFlashCableDS.TargetNITValue = INVALID_NETWORKID;
        TraceDebug(m,"Unable to open %s\r",mFileName);

    }
}

void CHsvDvbCInstallation_mquick_Priv::iquickpow_TurnOff()
{
}

/************************************
  provides IHsvDigitalScan iquick
 *************************************/
void CHsvDvbCInstallation_mquick_Priv::iquick_Initialise(void)
{
    int i = 0, j = 0, slen = 0, mlen = 0;
    int aslen = 0; /* Acutal Symbol Length */
    Nat32 retval, decoder, err=TM_OK;
    Nat32 StartFrequency = 0; 

    TraceDebug(m,"%s\r",__FUNCTION__);


    if(UPDATE_INSTALL)
    {
        idvbset_ResetAllToPersistent();
        TraceDebug(m,"All attributes restored to Persistent\r");
    }

    retval = feapi_GetFreqRange(WINDOWID, &StartFrequency, &(mDvbcQuickStatus.EndFrequency), &err);    
    ASSERT(retval == plferrids_Ok);
    ASSERT(err == TM_OK);

    if(StartFrequency < START_FREQUENCY)
    {
        StartFrequency = START_FREQUENCY;
    }

    ASSERT(StartFrequency <= START_FREQUENCY);
    ASSERT(mDvbcQuickStatus.EndFrequency >= END_FREQUENCY);

    mDvbcQuickStatus.StartFrequency = StartFrequency;
    mDvbcQuickStatus.ScanState = DvbcQuickIdle;
    mDvbcQuickStatus.PreferredNit = NIT_PREFERRED;
    mDvbcQuickStatus.TargetNITVersion = 0;

    mDvbcQuickStatus.State = StIdle;
    mDvbcQuickStatus.ModulationType = HsvAutoConstellation;
    mDvbcQuickStatus.CodeRateHigh = HsvCodeRateAuto;  
    mDvbcQuickStatus.CodeRateLow = HsvCodeRateAuto;
    mDvbcQuickStatus.GuardInterval = HsvGuardIntervalAuto;
    mDvbcQuickStatus.TxMode = HsvTxModeAuto;
    mDvbcQuickStatus.IqMode = HsvIqModeNormal;
    mDvbcQuickStatus.ChannelBandwidth = HsvChanBandwidth8MHz;
    mDvbcQuickStatus.ChannelInformation = 0;
    mDvbcQuickStatus.TimeError = 0;
    mDvbcQuickStatus.FrequencyError = 0;
    mDvbcQuickStatus.CurrentDemux = HsvDmxMain;
    mDvbcQuickStatus.SDTAcquired = FALSE;
    mDvbcQuickStatus.TargeNITFound = FALSE;
    mDvbcQuickStatus.TargetNITType = NIT_TYPE_INVALID;
    mDvbcQuickStatus.SymbolRate = idvbset_GetAttribute(CURRENT_MODE,rins_AttributeSymbolRate);
    mDvbcQuickStatus.Frequency = idvbset_GetAttribute(CURRENT_MODE, rins_AttributeNetworkFreq);

    if((AUTO_INSTALL) && (PRE_SCAN_SUPPORTED))
    {
        feapi_GetFreq(WINDOWID, &mDvbcQuickStatus.Frequency, &err);

        ASSERT(TM_OK == err);

    }
    TraceDebug(m,"Intial Network Freq = %d\r",(int)(mDvbcQuickStatus.Frequency>>4));
    mDvbcQuickStatus.FrequencyMode = idvbset_GetAttributeMode(CURRENT_MODE, rins_AttributeNetworkFreq);
    TraceDebug(m,"Intial Network Freq Mode = %d\r",(int)mDvbcQuickStatus.FrequencyMode);
    mDvbcQuickStatus.PlayStarted = FALSE;
    mDvbcQuickStatus.StationFound = FALSE;
    mDvbcQuickStatus.NumChannelsAdded = 0;
    mDvbcQuickStatus.NumChannelsRemoved = 0;
    mDvbcQuickStatus.FirstPresetNumber = INVALID_PRESET;
    mDvbcQuickStatus.NitMode = idvbset_GetAttributeMode(CURRENT_MODE, rins_AttributeNetworkId);
    mDvbcQuickStatus.TargetNITValue = INVALID_NETWORKID;

    if(rins_ManualValue == mDvbcQuickStatus.NitMode)
    {
        mDvbcQuickStatus.TargetNITValue = idvbset_GetAttribute(CURRENT_MODE, rins_AttributeNetworkId);
        TraceDebug(m,"Intial Target NIT = %d\r",mDvbcQuickStatus.TargetNITValue);
    }

    mCableDSDesc.NumOfTs = 0;
    mCableDSDesc.CurrentTsIndex = 0;

    slen = idvbset_GetAttributeLength(CURRENT_MODE, rins_AttributeSymbolRate);
    mlen = idvbset_GetAttributeLength(CURRENT_MODE, rins_AttributeModulation);

    if((slen * mlen) >= MAX_SEARCH_RATES)
    {
        ASSERT(!"Combination of sym rate and mod cannot be so high");
    }
    {
        int temprate = INVALID_SYMBOLRATE;
        for(i = 0; i < slen; i++)
        {
            int tempconst = HsvUnknownConstellation;

            temprate = idvbset_GetNextAttributeValue(CURRENT_MODE, rins_AttributeSymbolRate, temprate);
            if (temprate != INVALID_SYMBOLRATE)
            {
                for(j = 0; j < mlen; j++)
                {
                    if(((mlen*aslen) + j) >= MAX_SEARCH_RATES)
                    {
                        break;
                    }
                    tempconst = idvbset_GetNextAttributeValue(CURRENT_MODE, rins_AttributeModulation, tempconst);
                    mDvbcQuickStatus.SearchRates[(mlen*aslen) + j].rate = temprate;
                    mDvbcQuickStatus.SearchRates[(mlen*aslen) + j].constellation = (tmFe_Constellation_t)mConstellation[tempconst];
                    TraceDebug(m,"Initialise: SymRate[%d] = %d\r", ((mlen*aslen) + j),temprate);
                    TraceDebug(m,"Initialise: Modulation[%d] = %x\r", ((mlen*aslen) + j),mConstellation[tempconst]);
                }
                aslen++;
            }
        }
    }
    if((aslen * mlen) > MAX_SEARCH_RATES)
    {
        mDvbcQuickStatus.SearchRateLen = MAX_SEARCH_RATES;
    }
    else
    {
        mDvbcQuickStatus.SearchRateLen = (aslen * mlen);
    }

    TraceDebug(m,"Initialise:SearchRateLen = %d\r", mDvbcQuickStatus.SearchRateLen);

    mCableDSDesc.NumOfTs = 0;

    idataacq_Initialise();
}

FResult CHsvDvbCInstallation_mquick_Priv::iquick_StartDigitalScan(void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r",__FUNCTION__);

    if(mDvbcQuickStatus.State == StIdle)
    {
        pmp_PmpSend(mQuickPump, EvStart, (Nat32)NULL);
    }
    else
    {
        retval = hsverr_InstallationCommandNotAllowed;
    }
    return retval;
}

FResult CHsvDvbCInstallation_mquick_Priv::iquick_StartDigitalTuning(int freq)
{
    FResult retval;

    UNUSED(freq);
    TraceDebug(m,"%s\r",__FUNCTION__);

    retval = hsverr_InstallationCommandNotAllowed;

    ASSERT(!"mquick: Cannot do Manual install in quick Mode\r");
    return retval;
}
FResult CHsvDvbCInstallation_mquick_Priv::iquick_StopDigitalScan (void)
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r",__FUNCTION__);

    if(mDvbcQuickStatus.State == StIdle)
    {
        retval = hsverr_InstallationNotInProgress;
    }
    else
    {
        pmp_PmpSend(mQuickPump, EvStop, (Nat32)NULL);
    }
    return retval;
}
void CHsvDvbCInstallation_mquick_Priv::iquick_GetPTCInfo(HsvInstallationPTC *ptc)
{
    TraceDebug(m,"%s\r",__FUNCTION__);

    ptc->DecoderType = feapi_ChanDecDvbC;   

    if(mDvbcQuickStatus.ScanState == DvbcQuickScanningAlt)
    {
        if(eurdiv_GetAlternateTSLocation(rins_Cable) == eurdiv_AltTSRelocatedDesc)
        {
            ptc->Frequency          =   ALT_FREQ;
            ptc->SymbolRate         =   ALT_SYM_RATE;
            ptc->ModulationType     =   ALT_MODULATION;
        }
        else if(eurdiv_GetAlternateTSLocation(rins_Cable) == eurdiv_AltHomingFrequency)
        {
            ptc->Frequency          =   mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CableDescParam[0].Frequency;
            ptc->SymbolRate         =   mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CableDescParam[0].SymbolRate;
            ptc->ModulationType     =   mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].CableDescParam[0].Modulation;
            TraceDebug(m,"GetptcInfo: Freq = %ld\r",ptc->Frequency);
            TraceDebug(m,"GetptcInfo: SymRate = %ld\r",ptc->SymbolRate);
            TraceDebug(m,"GetptcInfo: Modulation = %d\r",ptc->ModulationType);
        }
        else
        {
            ASSERT(!"Invalid condition. Correct frequency is not obtained");
            TraceDebug(m,"Invalid condition. Correct frequency is not obtained\r");
        }
    }
    else
    {
        ptc->Frequency          =   CURRENT_FREQ;
        ptc->SymbolRate         =   CURRENT_SYM_RATE;
        ptc->ModulationType     =   CURRENT_MODULATION;

        TraceDebug(m,"GetptcInfo: Freq = %ld\r",ptc->Frequency);
        TraceDebug(m,"GetptcInfo: SymRate = %ld\r",ptc->SymbolRate);
        TraceDebug(m,"GetptcInfo: Modulation = %d\r",ptc->ModulationType);
    }
	ptc->ModulationType = mMapFromHsvToPlfDvbcModulation (ptc->ModulationType);
    ptc->CodeRateHigh       =   mDvbcQuickStatus.CodeRateHigh;         
    ptc->CodeRateLow        =   mDvbcQuickStatus.CodeRateLow;         
    ptc->HierarchyMode      =   HsvHierarchyNone;    
    ptc->GuardInterval      =   mDvbcQuickStatus.GuardInterval;    
    ptc->TxMode             =   mDvbcQuickStatus.TxMode;           
    ptc->IqMode             =   mDvbcQuickStatus.IqMode;           
    ptc->ChannelBandwidth   =   mDvbcQuickStatus.ChannelBandwidth; 
    ptc->StreamPriority     =   HsvStreamPriorityHigh;
    ptc->ChannelInformation =   mDvbcQuickStatus.ChannelInformation;   
    ptc->TimeError          =   mDvbcQuickStatus.TimeError;        
    ptc->FrequencyError     =   mDvbcQuickStatus.FrequencyError;   
    ptc->FrequencyOffset    =   mDvbcQuickStatus.FrequencyOffset;  
    ptc->VSignalStrength    =   sigstr_GetSignalStrength(rins_InsVssm);
    ptc->ASignalStrength    =   sigstr_GetSignalStrength(rins_InsAssm);
    ptc->QSignalStrength    =   sigstr_GetSignalStrength(rins_InsQssm);
    ptc->CDSDFrequency      =   mDvbcQuickStatus.Frequency;
    ptc->NITVersion         =   mDvbcQuickStatus.TargetNITVersion;
	ptc->Frequency = (ptc->Frequency * 1000)/16;
}

FResult CHsvDvbCInstallation_mquick_Priv::iquick_StoreWeakSignalInstallationChannel()       
{
    FResult retval = hsverr_Ok;

    TraceDebug(m,"%s\r",__FUNCTION__);
    ASSERT(!"mquick: Cannot do Manual install in quick Mode\r");

    retval = hsverr_InstallationCommandNotAllowed;
    return retval;
}

int CHsvDvbCInstallation_mquick_Priv::iquick_GetNumberOfDigitalChannelsFound()
{
    TraceDebug(m,"%s: retval = %d\r",__FUNCTION__,mDvbcQuickStatus.NumChannelsAdded);
    return mDvbcQuickStatus.NumChannelsAdded;    
}

int CHsvDvbCInstallation_mquick_Priv::iquick_GetNumberOfDigitalChannelsRemoved()
{
    TraceDebug(m,"%s: retval = %d\r",__FUNCTION__,mDvbcQuickStatus.NumChannelsRemoved);
    return mDvbcQuickStatus.NumChannelsRemoved;
}

int CHsvDvbCInstallation_mquick_Priv::iquick_GetTargetNitType(Nat16* NetworkId)
{
    if(mFlashCableDS.TargetNITValue == INVALID_NETWORKID)
    {
        return rins_NitNone;
    }
    else
    {
        *NetworkId = mFlashCableDS.TargetNITValue;
        return mFlashCableDS.TargetNITType;
    }
}
int CHsvDvbCInstallation_mquick_Priv::iquick_GetCurrentState()
{
    int retval = iquick_stidle;
    switch(mDvbcQuickStatus.State)
    {
        case StIdle: 
            retval = iquick_stidle;
            break;
        case StFeWait:
            retval = iquick_stfewait;
            break;
        case StNITWait:
        case StDmxWait:
            retval = iquick_stdmxwait;
            break;
        case StDecision:
            retval = iquick_stdecision;
            break;
        case StMax:
        default:
            ASSERT(!"Incorrect State");
            break;
    }
    return retval;
}

int CHsvDvbCInstallation_mquick_Priv::iquick_GetSDTType()
{
    int retval = eurdiv_SDTActual;

    if((mDvbcQuickStatus.State != StIdle) && (mDvbcQuickStatus.ScanState == DvbcQuickScanningAlt))
    {
        if(eurdiv_GetAltSDTType(rins_Cable) == eurdiv_SDTOther)
        {
            retval = eurdiv_SDTOther;
        }
    }
    TraceDebug(m,"SDTTYPE = %d\r",retval);
    return retval;
}

Bool CHsvDvbCInstallation_mquick_Priv::iquick_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{
    Bool retval = FALSE;
    int SDTType;

    SDTType = eurdiv_GetAltSDTType(rins_Cable);

    if((mDvbcQuickStatus.State != StIdle) && (mDvbcQuickStatus.ScanState == DvbcQuickScanningAlt) && (SDTType == eurdiv_SDTOther))
    {
        if(mCableDSDesc.CurrentTsIndex != -1)
        {
            *ONID = mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].ONID;
            *TSID = mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].Tsid;
            retval = TRUE;
        }
    }
    TraceDebug(m,"retval = %d, onid = %d, tsid = %d\r",retval, *ONID, *TSID);
    return retval;
}

void CHsvDvbCInstallation_mquick_Priv::iquick_GetSIDetails(HsvSDMSIDataValues* sivalues)
{

	if((idvbset_GetAttribute(rins_InstallationModeAutomatic, rins_AttributeNetworkOperator) == rins_UPC) && (DvbcQuickScanningCDS != mDvbcQuickStatus.ScanState))
	{
		sivalues->TableId = SDT_OTHER_TABLE_ID;
	}
	return;
}


Bool CHsvDvbCInstallation_mquick_Priv::iquick_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{
    Bool retval = FALSE;
    int SDTType;

    SDTType = eurdiv_GetAltSDTType(rins_Cable);

    if((mDvbcQuickStatus.State != StIdle) && (mDvbcQuickStatus.ScanState == DvbcQuickScanningAlt) && (SDTType == eurdiv_SDTActual))
    {
        if(mCableDSDesc.CurrentTsIndex != -1)
        {
            *ONID = mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].ONID;
            *TSID = mCableDSDesc.TsParam[mCableDSDesc.CurrentTsIndex].Tsid;
            retval = TRUE;
        }
    }
    TraceDebug(m,"retval = %d, onid = %d, tsid = %d\r",retval, *ONID, *TSID);
    return retval;
}

/************************************
  provides IHsvFrontEndApiNotify  
 *************************************/

void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnStationFound()
{
    if(mDvbcQuickStatus.State == StFeWait)
    {
        TraceDebug(m,"%s\r",__FUNCTION__);
        pmp_PmpSend(mQuickPump, EvStationFound, (Nat32)NULL);
    }
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnStationNotFound()
{
    if(mDvbcQuickStatus.State == StFeWait)
    {
        TraceDebug(m,"%s\r",__FUNCTION__);
        pmp_PmpSend(mQuickPump, EvStationNotFound, (Nat32)NULL);
    }
}

/* Are these 2 really required */
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnMeasReady( int ssm, Nat32 strength )
{
    UNUSED(ssm);
    UNUSED(strength);
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnMeasAborted( int ssm )
{
    UNUSED(ssm);
}
/***************************************
  provides IHsvStreamNotify iqstrapiN
 ****************************************/

void CHsvDvbCInstallation_mquick_Priv::iqstrapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);

    switch(spid)
    {
        case HSVSPID(ActualCableDS, dvb, nit):

            break;
        case HSVSPID(OtherCableDS, dvb, nit):

            break;
        case HSVSPID(ActualTSService, dvb, sdt):


        default:
            break;
    }
}
void CHsvDvbCInstallation_mquick_Priv::iqstrapiN_OnChanged( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    /* pavan: how do we handle dynamic updates */
    UNUSED(dest);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
    UNUSED(eventid);

    switch(spid)
    {
        case HSVSPID(ActualCableDS, dvb, nit):
            break;
        default:
            break;
    }
}
void CHsvDvbCInstallation_mquick_Priv::iqstrapiN_OnRemoved( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    UNUSED(dest);
    UNUSED(spid);
    UNUSED(key1);
    UNUSED(key2);
    UNUSED(key3);
}
void CHsvDvbCInstallation_mquick_Priv::iqstrapiN_OnCompleted( HsvDestination dest, int spid)
{
    UNUSED(dest);
    UNUSED(spid);
}

/********************************************
  provides IHsvSdmControlNotifyEx iqctrlN
 *********************************************/
void CHsvDvbCInstallation_mquick_Priv::iqctrlN_OnEvent( HsvDemux dmx, int eventid, int value)
{
    UNUSED(dmx);
    UNUSED(value);
    TraceDebug(m,"ctrlN_OnEvent:eventid = %d\r",eventid);

    if((mDvbcQuickStatus.State == StInit) || (mDvbcQuickStatus.State == StDmxWait) || (mDvbcQuickStatus.State == StNITWait))
    {
        switch(eventid)
        {
            case iqctrlN_DataAvailable:
                if((mDvbcQuickStatus.ScanState == DvbcQuickScanningDefaultList) || (mDvbcQuickStatus.ScanState == DvbcQuickScanningNetworkFreq))
                {
                    TraceDebug(m,"iqctrlN: DataAvailable\r");

                    //mDvbcQuickStatus.SDTAcquired = TRUE;
                    mOnNitAvailable();
                    if(FALSE == mDvbcQuickStatus.TargeNITFound)
                    {
                        TraceDebug(m,"iqctrlN: DataAvailable if\r");
                        pmp_PmpSend(mQuickPump, EvNitNotFound, mDvbcQuickStatus.Frequency);
                    }
                    else
                    {
                        TraceDebug(m,"iqctrlN: DataAvailable else\r");
                        pmp_PmpSend(mQuickPump, EvDmxNtf, mDvbcQuickStatus.Frequency);
                    }           
                }
                else if((mDvbcQuickStatus.ScanState == DvbcQuickScanningCDS) || (mDvbcQuickStatus.ScanState == DvbcQuickScanningAlt))
                {
                    TraceNotice(m,"%s %d mDvbcQuickStatus.SDTAcquired %d", __FUNCTION__, __LINE__, mDvbcQuickStatus.SDTAcquired);
                    if(mDvbcQuickStatus.SDTAcquired == FALSE)
                    {
                        TraceDebug(m,"mquick: iqctrlN_SiDataAvailable mDvbcQuickStatus.ScanState %d", mDvbcQuickStatus.ScanState);
                        if( (rins_ManualValue == mDvbcQuickStatus.NitMode) || (eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite) )
                        {       
                            TraceDebug(m,"iqctrlN: SiDataAvailable\r");
                            mDvbcQuickStatus.SDTAcquired = TRUE;

                            if(mDvbcQuickStatus.TargeNITFound)
                            {
                                TraceDebug(m,"iqctrlN: SiDataAvailable\r");
                                pmp_PmpSend(mQuickPump, EvDmxNtf, mDvbcQuickStatus.Frequency);
                            }
                            else
                            {
                                TraceDebug(m,"%d %s Target NIT Not found! ", __LINE__, __FUNCTION__);
                            }
                            /* Base it on SDT on just DataAvailable */
                        }
                    }
                }
                /* Base it on SDT on just DataAvailable */            
                break;



            case iqctrlN_SiDataAvailable:

                if((mDvbcQuickStatus.ScanState == DvbcQuickScanningCDS) || (mDvbcQuickStatus.ScanState == DvbcQuickScanningAlt))
                {
                    if( (rins_ManualValue == mDvbcQuickStatus.NitMode) || (eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite) )
                    {       
                        TraceDebug(m,"iqctrlN: SiDataAvailable\r");
                        mDvbcQuickStatus.SDTAcquired = TRUE;

                        if(mDvbcQuickStatus.TargeNITFound)
                        {
                            TraceDebug(m,"iqctrlN: SiDataAvailable\r");
                            pmp_PmpSend(mQuickPump, EvDmxNtf, mDvbcQuickStatus.Frequency);
                        }
                        else
                        {
                            TraceDebug(m,"%d %s Target NIT Not found! ", __LINE__, __FUNCTION__);
                        }
                        /* Base it on SDT on just DataAvailable */
                    }
                }
                break;
            case iqctrlN_DataNotAvailable:
                TraceDebug(m,"iqctrlN: DataNotAvailable\r");
                if(TRUE == mDvbcQuickStatus.TargeNITFound)
                {
                    pmp_PmpSend(mQuickPump, EvDmxNtf, (Nat32)NULL);
                }
                else if(ctrl_NITAvailable == ctrl_GetStatus(dmx))
                {
                    mOnNitAvailable();
                }
                if(FALSE == mDvbcQuickStatus.TargeNITFound)
                {
                    pmp_PmpSend(mQuickPump, EvNitNotFound, mDvbcQuickStatus.Frequency);
                }
                break;
            case iqctrlN_StartedCollection:
                mDvbcQuickStatus.SDTAcquired = FALSE;
                TraceDebug(m,"iqctrlN: StartedCollection\r");
                break;
            case iqctrlN_StoppedCollection:
                TraceDebug(m,"iqctrlN: StoppedCollection\r");
                pmp_PmpSend(mQuickPump, EvSdmStopped, (Nat32)NULL);
                break;

            default:
                ASSERT(FALSE);
                break;
        }   
    }
    UNUSED(dmx);
}

void CHsvDvbCInstallation_mquick_Priv::mResetInstallationState(void)
{
    Nat32 errorcode = TM_OK;

    mDvbcQuickStatus.State = StIdle;
    mDvbcQuickStatus.ScanState = DvbcQuickIdle;
    mDvbcQuickStatus.PreferredNit = NIT_PREFERRED;

    mDvbcQuickStatus.SDTAcquired = FALSE;
    mDvbcQuickStatus.TargeNITFound = FALSE;
    mDvbcQuickStatus.TargetNITType = NIT_TYPE_INVALID;

    mDvbcQuickStatus.PlayStarted = FALSE;
    mDvbcQuickStatus.StationFound = FALSE;
    mDvbcQuickStatus.TargetNITValue = INVALID_NETWORKID;
    memo_memset((void*)&mCableDSDesc, 0, sizeof(mCableDSDesc));
    feapi_SetSearchRates(WINDOWID, NULL, 0, &errorcode);
    ASSERT(TM_OK == errorcode);

    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
}

void CHsvDvbCInstallation_mquick_Priv::iqena_Enable(void)
{
    mDvbcQuickStatus.Active = TRUE;
}

void CHsvDvbCInstallation_mquick_Priv::iqena_Disable(void)
{
    mDvbcQuickStatus.Active = FALSE;
}

void CHsvDvbCInstallation_mquick_Priv::mStopSdm(HsvDemux dmx)
{
    if(ctrl_GetMode(dmx) == ctrl_Idle)
    {
        pmp_PmpSend(mQuickPump, EvSdmStopped, (Nat32)NULL);
    }
    else
    {
        ctrl_StopCollection(dmx);
    }
}

void CHsvDvbCInstallation_mquick_Priv::iquick_SyncComplete(void)
{
    TraceDebug(m,"%s %d", __FUNCTION__, __LINE__);
    mResetInstallationState();
    iquickN_OnEvent(iquickN_EventScanCompleted);
}

int CHsvDvbCInstallation_mquick_Priv::FindHsvValue(int plfval, int* arr, int len)
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

void CHsvDvbCInstallation_mquick_Priv::iquick_ClearPersistent()
{
	/* Read all CableDS from flash and update it in RAM */
//    FILE* fp;
//    int readrec = 0;
    /*
	ffsdir_GetDirPath( mDirName, ffsdir_Boot, ffsdir_Broadcast );
    
	str_strcat(mDirName, "/channellib/");
	if(str_strlen(mDirName))
    {
        
    }
    else
    {
        ASSERT(!"Boot parition mount has failed");
    }
*/
	str_strcpy(mDirName, "/user_setting/rw/tvserver/databases/channellib/");	
	
    mGetPathName(mDirName, CABLE_DEL_FILEPATH, mFileName);

    TraceNotice(m,"%s %d", __FUNCTION__, __LINE__);
    remove(mFileName);
    mFlashCableDS.TargetNITValue = INVALID_NETWORKID;
}

/*Within*/
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnSearchInProgress( tmFe_SearchState_t state )
{
	return;
}

void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnSearchStateChanged (  tmFe_SearchState_t state  )   
{
	return;
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnTvSystemDetected (  tmFe_TvSystem_t tvSystem  )   
{
	return;
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnAfcFreqChanged (  Nat32 freq  )   
{
	return;
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnAfcLimitReached ( Nat32 freq  )   
{
	return;
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnAfcModeChanged (  void  )   
{
	return;
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnIqModeDetected (  tmFe_IqMode_t mode  )   
{
	return;
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnCodeRateDetected (  tmFe_CodeRate_t highPrioRate ,  tmFe_CodeRate_t lowPrioRate  )   
{
	return;
}
void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnHierarchyModeDetected (  tmFe_HierarchyMode_t mode  )   
{
	return;
}

void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnGuardIntervalDetected (  tmFe_GuardInterval_t interval  )   
{
	return;
}

void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnTxModeDetected (  tmFe_TxMode_t mode  )   
{
	return;
}

void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnChanBandwidthDetected (  tmFe_ChanBandwidth_t bandwith  )   
{
	return;
}

void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnCarrierPresentChanged (  Bool carrier  )   
{
	return;
}

void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnBerThresholdCrossed (  Nat32 ber ,  Nat32 berThreshold  )   
{
	return;
}

FResult CHsvDvbCInstallation_mquick_Priv::iquick_StartInstallation(int source, int ptc, int mode) 
{
	return 0;
}
FResult CHsvDvbCInstallation_mquick_Priv::iquick_StopInstallation(void ) 
{
	return 0;
}
int CHsvDvbCInstallation_mquick_Priv::iquick_GetNoOfPass(void) 
{
	return 0;
}
int CHsvDvbCInstallation_mquick_Priv::iquick_GetCurrentPass ( void ) 
{
	return 0;
}
HsvStreamPriority CHsvDvbCInstallation_mquick_Priv::iquick_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}
void CHsvDvbCInstallation_mquick_Priv::iquick_SetStreamPriority (HsvStreamPriority prio) 
{
	return;
}
void CHsvDvbCInstallation_mquick_Priv::iquick_ClearCache(void) 
{
	return;
}
int CHsvDvbCInstallation_mquick_Priv::iquick_GetPLPIds(int *PLPIds) 
{
	return 0;
}
HsvHierarchyMode CHsvDvbCInstallation_mquick_Priv::iquick_GetHierarchyMode(void) 
{
	return (HsvHierarchyMode)0;
}
void CHsvDvbCInstallation_mquick_Priv::iquick_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid) 
{
	return;
}

int CHsvDvbCInstallation_mquick_Priv::iquick_ZiggoGetSDTType(Nat16 Frequency) 
{
	return 0;
}
void CHsvDvbCInstallation_mquick_Priv::iquick_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvDvbCInstallation_mquick_Priv::iquick_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}

void CHsvDvbCInstallation_mquick_Priv::iquickfeN_OnConstellationDetected( tmFe_Constellation_t constellation )
{
	return;
}
