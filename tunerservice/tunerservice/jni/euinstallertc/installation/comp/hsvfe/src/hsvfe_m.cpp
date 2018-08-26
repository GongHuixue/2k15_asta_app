/**********************************************************************
*
*   C Source:       hsvfe_m.c
*   Instance:       blr81mgr_1
*   Description:    
*   %created_by:    lakshminb %
*   %date_created:  Mon Apr 23 15:15:23 2012 %
*
**********************************************************************/

#include "_hsvfe_m.h"


TRACESYMBOL(m, "dvb/hsvfe/hsvfe_m")

/**************************************************************************
 * Macros and types
 **************************************************************************/

 /*************************************************************************
    Local Structures and enums
 **************************************************************************/

/****************************************************************************
 * Declaration of Static functions
 ****************************************************************************/
/****************************************************************************
 * Static variables
 ****************************************************************************/


/****************************************************************************   
 * Static functions Implementation
 ****************************************************************************/

/* IHsvPower */

void CHsvFrontEnd_Priv::pow_Init( )
{
}
void CHsvFrontEnd_Priv::pow_TurnOn( void )
{
}
void CHsvFrontEnd_Priv::pow_TurnOff( void )
{
}

/* IPlfApiTuning */

FResult CHsvFrontEnd_Priv::feapi_GetFreqRange( int winid, Nat32* minfreq, Nat32* maxfreq, Nat32* retval )
{
	FResult	fetunRet = 0; //fetun_GetFreqRange(winid, minfreq, maxfreq, retval);
//	*minfreq = (108 * 16);
//	*maxfreq = (863 * 16);
	*minfreq = (44 * 16);
	*maxfreq = (870 * 16);

	*retval = 0;
	TraceNotice (m, "Fe : MinFreq %d  MaxFreq %d", *minfreq, *maxfreq); 
    return fetunRet;
}
FResult CHsvFrontEnd_Priv::feapi_GetFreq( int winid, Nat32* freq, Nat32* retval )
{
	FResult	fetunRet = fetun_GetFreq(winid, freq, retval);
	TraceNotice (m, "Fe : GetFreq %d Khz ", *freq); 
	*freq = (((*freq) * 16)/1000) ;

    return fetunRet;
}
FResult CHsvFrontEnd_Priv::feapi_SetFreq( int winid, Nat32 freq, Bool finetune, Nat32* retval )
{
	TraceNotice (m, "Fe: SetFreq Freq %dMhz FineTune %d ", (freq * 1000)/16, finetune);
    return fetun_SetFreq(winid, ((freq * 1000)/16), finetune, retval);
}
FResult CHsvFrontEnd_Priv::feapi_GetTvSystemSupp( int winid, tmFe_TvSystem_t tvSystem, Bool* supp, Nat32* retval )
{
    return fetun_GetTvSystemSupp(winid, tvSystem, supp, retval);
}
FResult CHsvFrontEnd_Priv::feapi_GetTvSystem( int winid, tmFe_TvSystem_t* TvSystem, Nat32* retval )
{
    return fetun_GetTvSystem(winid, TvSystem, retval);
}
FResult CHsvFrontEnd_Priv::feapi_SetTvSystem( int winid, tmFe_TvSystem_t TvSystem, Nat32* retval )
{
    return fetun_SetTvSystem(winid, TvSystem, retval);
}
FResult CHsvFrontEnd_Priv::feapi_StartSearch( int winid, Nat32 startFreq, tmFe_SearchMode_t mode, Nat32 endFreq, Nat32* retval )
{
    TraceNotice (m, "Fe : StartSearch: StartFreq %dKhz  EndFreq %dKhz ", (startFreq * 1000) / 16, (endFreq * 1000) / 16);
    return fetun_StartSearch(winid,((startFreq * 1000) / 16), mode, ((endFreq * 1000) / 16), retval);
}
FResult CHsvFrontEnd_Priv::feapi_StopSearch( int winid, Nat32* retval )
{
	TraceNotice (m, "Fe: StopSearch ");
    return fetun_StopSearch(winid, retval);
}

FResult CHsvFrontEnd_Priv::feapi_Freq2Chan(int winid,Nat32 freq,tmFe_ChanTable_t table,Nat32 * Chan,Nat32 * retval)
{
	return 0;
}
FResult CHsvFrontEnd_Priv::feapi_GetCarrierFreq(int winid,Nat32 chan,tmFe_ChanTable_t table,Nat32 * Freq,Nat32 * retval)
{
	FResult	fetunRet = fetun_GetFreq(winid, Freq, retval);
	TraceNotice (m, "Fe : feapi_GetCarrierFreq %d Khz ", *Freq);

    return fetunRet;
}



/* IPlfApiSigStrengthMeas //vssm, assm, qssm */
FResult CHsvFrontEnd_Priv::feapi_GetSigStrengthRange( int winid, int ssm, Nat32* MinStrength, Nat32* MaxStrength, Nat32* retval )
{
    FResult plferr = 0;
    switch(ssm)
    {
    case feapi_SigAssm:
        plferr = assm_GetSigStrengthRange(winid, MinStrength, MaxStrength, retval);
        break;
    case feapi_SigVssm:
        plferr = vssm_GetSigStrengthRange(winid, MinStrength, MaxStrength, retval);
        break;
    case feapi_SigQssm:
        plferr = qssm_GetSigStrengthRange(winid, MinStrength, MaxStrength, retval);
        break;
    case feapi_SigSssm://same as Vssm ?
        plferr = vssm_GetSigStrengthRange(winid, MinStrength, MaxStrength, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
	*MinStrength = 0;
	*MaxStrength = 100;
    return plferr;
}
FResult CHsvFrontEnd_Priv::feapi_Start( int winid, int ssm, Bool* Avail, Nat32* retval )
{
    FResult plferr = 0;
    switch(ssm)
    {
    case feapi_SigAssm:
        plferr = assm_Start(winid, Avail, retval);
        break;
    case feapi_SigVssm:
        plferr = vssm_Start(winid, Avail, retval);
        break;
    case feapi_SigQssm:
        plferr = qssm_Start(winid, Avail, retval);
        break;
    case feapi_SigSssm://same as Vssm ?
        plferr = vssm_Start(winid, Avail, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}
FResult CHsvFrontEnd_Priv::feapi_Stop( int winid, int ssm, Bool* Stopped, Nat32* retval )
{
    FResult plferr = 0;
    switch(ssm)
    {
    case feapi_SigAssm:
        plferr = assm_Stop(winid, Stopped, retval);
        break;
    case feapi_SigVssm:
        plferr = vssm_Stop(winid, Stopped, retval);
        break;
    case feapi_SigQssm:
        plferr = qssm_Stop(winid, Stopped, retval);
        break;
    case feapi_SigSssm://same as Vssm ?
        plferr = vssm_Stop(winid, Stopped, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}
FResult CHsvFrontEnd_Priv::feapi_GetMeasValid( int winid, int ssm, Bool* Valid, Nat32* retval )
{
    FResult plferr = 0;
    switch(ssm)
    {
    case feapi_SigAssm:
        plferr = assm_GetMeasValid(winid, Valid, retval);
        break;
    case feapi_SigVssm:
        plferr = vssm_GetMeasValid(winid, Valid, retval);
        break;
    case feapi_SigQssm:
        plferr = qssm_GetMeasValid(winid, Valid, retval);
        break;
    case feapi_SigSssm://same as Vssm ?
        plferr = vssm_GetMeasValid(winid, Valid, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}
FResult CHsvFrontEnd_Priv::feapi_GetSigStrength( int winid, int ssm, Nat32* Strength, Nat32* retval )
{
    FResult plferr = 0;
    switch(ssm)
    {
    case feapi_SigAssm:
        plferr = assm_GetSigStrength(feapi_SigAssm, Strength, retval);
        break;
    case feapi_SigVssm:
        plferr = vssm_GetSigStrength(feapi_SigVssm, Strength, retval);
        break;
    case feapi_SigQssm:
        plferr = qssm_GetSigStrength(feapi_SigQssm, Strength, retval);
        break;
    case feapi_SigSssm://same as Vssm ?
        plferr = vssm_GetSigStrength(feapi_SigSssm, Strength, retval);
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    return plferr;
}

/* IPlfApiChanDec        chdecc & chdect */
FResult CHsvFrontEnd_Priv::feapi_GetActualConstellation( int winid, int decoder, tmFe_Constellation_t* pConstellation, Nat32* retval )
{
    return chdec_GetActualConstellation(winid, decoder,pConstellation, retval);
}
FResult CHsvFrontEnd_Priv::feapi_SetConstellation( int winid, int decoder, tmFe_Constellation_t constellation, Nat32* retval )
{
    return chdec_SetConstellation(winid,decoder, constellation, retval);

}
FResult CHsvFrontEnd_Priv::feapi_GetBer( int winid, int decoder, Nat32* Ber, Nat32* retval )
{
	FResult  fres = plferrids_Other;

	fres = chdec_GetBer(winid, decoder, Ber);
    if ( fres != plferrids_Ok )
    {
        *Ber = 0;
    }

	return fres;
}

FResult CHsvFrontEnd_Priv::feapi_GetCarrierPresent( int winid, Bool* Present, Nat32* retval )
{
    return chdec_GetCarrierPresent(winid, Present, retval);
}

/* IPlfApiChanDecDvbT    dvbt */
FResult CHsvFrontEnd_Priv::feapi_SetChanBandwidth( int winid, tmFe_ChanBandwidth_t bandwidth, Nat32* retval )
{
	FResult ret = 0;

	ret = chdecT_SetChanBandwidth(winid, bandwidth, retval);

	return ret;
}
FResult CHsvFrontEnd_Priv::feapi_GetActualChanBandwidth( int winid, tmFe_ChanBandwidth_t* Bandwidth, Nat32* retval )
{
	FResult ret = 0;
	
	ret = chdecT_GetActualChanBandwidth(winid, Bandwidth, retval);

	return ret;
}
FResult CHsvFrontEnd_Priv::feapi_GetTPSId(int winid, HsvDvbTParams* TPSId, Nat32* retval )
{
	FResult ret = 0;
	ret = chdecT_GetTPSId(winid, TPSId,retval );
	return ret;
}
FResult CHsvFrontEnd_Priv::feapi_SetStreamPriority( int winid, tmFe_StreamPriority_t streamPriority, Nat32* retval )
{
    return chdecT_SetStreamPriority(winid, streamPriority, retval);
}

FResult CHsvFrontEnd_Priv::feapi_GetHierarchyMuxPresence( int winid, Bool * HierarchyMuxPresent, Nat32* retval )
{
    return chdecT_GetHierarchyMuxPresence(winid, HierarchyMuxPresent, retval);
}

FResult CHsvFrontEnd_Priv::feapi_GetStreamPriority( int winid, tmFe_StreamPriority_t* streamPriority, Nat32* retval )
{
    return chdecT_GetStreamPriority(winid, streamPriority, retval);
}

/* IPlfApiChanDecDvbC    chdecC */
FResult CHsvFrontEnd_Priv::feapi_GetSymbolRateRange( int winid, Nat32* MinSymbolRate, Nat32* MaxSymbolRate, Nat32* retval )
{
    return chdecC_GetSymbolRateRange(winid, MinSymbolRate, MaxSymbolRate, retval);
}
FResult CHsvFrontEnd_Priv::feapi_SetSymbolRate( int srtmode, Nat32 rate, Nat32* retval )
{
	return chdecC_SetSymbolRate( srtmode, rate, retval );
}
FResult CHsvFrontEnd_Priv::feapi_GetSymbolRate( int winid, Nat32* rate, Nat32* retval )
{
    return chdecC_GetSymbolRate(winid, rate, retval );
}
FResult CHsvFrontEnd_Priv::feapi_SetSearchRates( int winid, tmFe_SearchSymbolRate_t* SearchRate, Nat32 size, Nat32* retval )
{
    return chdecC_SetSearchRates( winid, SearchRate, size, retval );
}
FResult CHsvFrontEnd_Priv::feapi_GetActualCodeRate( int winid, Nat32* rate, Nat32* retval )
{
    Nat32 TmpSymRate = 0;
    
    FResult ret = chdecC_GetSymbolRate( winid, &TmpSymRate, retval );
    
    TmpSymRate = ((int)(TmpSymRate / 1000) * 1000);
    *rate       = TmpSymRate;
    
    return ret;
}

FResult CHsvFrontEnd_Priv::feapi_GetFreqStep( int winid, Nat32* step, Nat32* retval )
{
	TraceNotice(m,"feapi_GetFreqStep");
    return (chdecC_GetFreqStep( winid, step, retval ));
}

FResult CHsvFrontEnd_Priv::feapi_SetFreqStep( int winid, Nat32 step, Nat32* retval )
{
	TraceNotice(m,"Freq step set to: %d Khz",((step/16)*1000));
	return (chdecC_SetFreqStep( winid, ((step/16)*1000), retval ) );
}


/*********************************
    Requires Ntf interfaces
*********************************/
/* IPlfApiTuningNotify   fetunN */
void CHsvFrontEnd_Priv::fetunN_OnSearchStateChanged( tmFe_SearchState_t state )
{
    if(feapiN_iPresent())
    {
        feapiN_OnSearchStateChanged( state );
    }
}
void CHsvFrontEnd_Priv::fetunN_OnSearchInProgress( tmFe_SearchState_t state )
{
    if(feapiN_iPresent())
    {
        feapiN_OnSearchInProgress( state );
    }
}
void CHsvFrontEnd_Priv::fetunN_OnStationFound( void )
{
	TraceNotice (m, "FeN : OnStationFound ");
    if(feapiN_iPresent())
    {
        feapiN_OnStationFound( );
    }
}
void CHsvFrontEnd_Priv::fetunN_OnStationNotFound( void )
{
	TraceNotice (m, "FeN : OnStationNotFound ");
    if(feapiN_iPresent())
    {
        feapiN_OnStationNotFound( );
    }
}
void CHsvFrontEnd_Priv::fetunN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem )
{
    if(feapiN_iPresent())
    {
        feapiN_OnTvSystemDetected( tvSystem );
    }
}
void CHsvFrontEnd_Priv::fetunN_OnAfcFreqChanged( Nat32 freq )
{
    if(feapiN_iPresent())
    {
        feapiN_OnAfcFreqChanged( freq );
    }
}
void CHsvFrontEnd_Priv::fetunN_OnAfcLimitReached(Nat32 freq )
{
    if(feapiN_iPresent())
    {
        feapiN_OnAfcLimitReached( freq );
    }
}
void CHsvFrontEnd_Priv::fetunN_OnAfcModeChanged( void )
{
    if(feapiN_iPresent())
    {
        feapiN_OnAfcModeChanged( );
    }
}

/* IPlfApiSigStrengthMeasNotify    //vssmN, assmN, qssmN */
void CHsvFrontEnd_Priv::vssmN_OnMeasReady( Nat32 strength )
{
    if(feapiN_iPresent())
    {
        feapiN_OnMeasReady( feapi_SigVssm, strength );
        feapiN_OnMeasReady( feapi_SigSssm, strength );
    }
}
void CHsvFrontEnd_Priv::vssmN_OnMeasAborted( )
{
    if(feapiN_iPresent())
    {
        feapiN_OnMeasAborted( feapi_SigVssm );
        feapiN_OnMeasAborted( feapi_SigSssm );
    }
}

void CHsvFrontEnd_Priv::assmN_OnMeasReady( Nat32 strength )
{
    if(feapiN_iPresent())
    {
        feapiN_OnMeasReady( feapi_SigAssm, strength );
    }
}

void CHsvFrontEnd_Priv::assmN_OnMeasAborted( )
{
    if(feapiN_iPresent())
    {
        feapiN_OnMeasAborted( feapi_SigAssm );
    }
}

void CHsvFrontEnd_Priv::qssmN_OnMeasReady( Nat32 strength )
{
    if(feapiN_iPresent())
    {
        feapiN_OnMeasReady( feapi_SigQssm, strength );
    }
}

void CHsvFrontEnd_Priv::qssmN_OnMeasAborted( )
{
    if(feapiN_iPresent())
    {
        feapiN_OnMeasAborted( feapi_SigQssm );
    }
}

#ifndef __cplusplus
/* IPlfApiChanDecNotify   //chdecN */

void CHsvFrontEnd_Priv::chdecN_OnConstellationDetected( tmFe_Constellation_t constellation )
{
    UNUSED(constellation);
    if(feapiN_iPresent())
    {
        feapiN_OnConstellationDetected(constellation);
    }
}
void CHsvFrontEnd_Priv::chdecN_OnIqModeDetected( tmFe_IqMode_t mode )
{
    UNUSED(mode);
    if(feapiN_iPresent())
    {
        feapiN_OnIqModeDetected(mode);
    }
}
void CHsvFrontEnd_Priv::chdecN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate )
{
    UNUSED(highPrioRate);
	UNUSED(lowPrioRate);
    if(feapiN_iPresent())
    {
        feapiN_OnCodeRateDetected(highPrioRate,lowPrioRate);
    }
}
#endif

void CHsvFrontEnd_Priv::chdecN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode )
{
    UNUSED(mode);
    if(feapiN_iPresent())
    {
        feapiN_OnHierarchyModeDetected(mode);
    }
}
#ifndef __cplusplus

void CHsvFrontEnd_Priv::chdecN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval )
{
    UNUSED(interval);
    if(feapiN_iPresent())
    {
        feapiN_OnGuardIntervalDetected(interval);
    }
}
void CHsvFrontEnd_Priv::chdecN_OnTxModeDetected( tmFe_TxMode_t mode )
{
    UNUSED(mode);
    if(feapiN_iPresent())
    {
        feapiN_OnTxModeDetected(mode);
    }
}
void CHsvFrontEnd_Priv::chdecN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith )
{
    UNUSED(bandwith);
    if(feapiN_iPresent())
    {
        feapiN_OnChanBandwidthDetected(bandwith);
    }
}
#endif

void CHsvFrontEnd_Priv::chdecN_OnCarrierPresentChanged( Bool carrier )
{
    UNUSED(carrier); 
    if(feapiN_iPresent())
    {
        feapiN_OnCarrierPresentChanged(carrier);
    }
}
#ifndef __cplusplus

void CHsvFrontEnd_Priv::chdecN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold )
{
    UNUSED(berThreshold);
    UNUSED(ber);
    if(feapiN_iPresent())
    {
        feapiN_OnBerThresholdCrossed(ber,berThreshold);
    }
}

/* IPlfApiChanDecNotify   //chdec2N */
void CHsvFrontEnd_Priv::chdec2N_OnConstellationDetected( tmFe_Constellation_t constellation )
{
     UNUSED(constellation);
    if(feapiN_iPresent())
    {
        feapiN_OnConstellationDetected(constellation);
    }
}
void CHsvFrontEnd_Priv::chdec2N_OnIqModeDetected( tmFe_IqMode_t mode )
{
    UNUSED(mode);
    if(feapiN_iPresent())
    {
        feapiN_OnIqModeDetected(mode);
    }
}
void CHsvFrontEnd_Priv::chdec2N_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, 
                                 tmFe_CodeRate_t lowPrioRate )
{
    UNUSED(highPrioRate);
	UNUSED(lowPrioRate);
    if(feapiN_iPresent())
    {
        feapiN_OnCodeRateDetected(highPrioRate,lowPrioRate);
    }
}
#endif

void CHsvFrontEnd_Priv::chdec2N_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode )
{   
    UNUSED(mode);
    if(feapiN_iPresent())
    {
        feapiN_OnHierarchyModeDetected(mode);
    }
}
#ifndef __cplusplus

void CHsvFrontEnd_Priv::chdec2N_OnGuardIntervalDetected( tmFe_GuardInterval_t interval )
{
    UNUSED(interval);
    if(feapiN_iPresent())
    {
        feapiN_OnGuardIntervalDetected(interval);
    }
}
void CHsvFrontEnd_Priv::chdec2N_OnTxModeDetected( tmFe_TxMode_t mode )
{
    UNUSED(mode);
    if(feapiN_iPresent())
    {
        feapiN_OnTxModeDetected(mode);
    }
}
void CHsvFrontEnd_Priv::chdec2N_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith )
{
    UNUSED(bandwith);
    if(feapiN_iPresent())
    {
        feapiN_OnChanBandwidthDetected(bandwith);
    }
}
#endif

void CHsvFrontEnd_Priv::chdec2N_OnCarrierPresentChanged( Bool carrier )
{
    UNUSED(carrier);
    if(feapiN_iPresent())
    {
        feapiN_OnCarrierPresentChanged(carrier);
    }
}
#ifndef __cplusplus

void CHsvFrontEnd_Priv::chdec2N_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold )
{
    UNUSED(ber);
    UNUSED(berThreshold);

    if(feapiN_iPresent())
    {
        feapiN_OnBerThresholdCrossed(ber,berThreshold);
    }
}
#endif

