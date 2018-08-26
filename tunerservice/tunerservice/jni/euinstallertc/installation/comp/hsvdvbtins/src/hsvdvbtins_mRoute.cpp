#include "_hsvdvbtins_mRoute.h"
////TRACESYMBOL(m, "dvb/installation/hsvdvbtins_mRoute")



int CHsvDvbTInstallation_mRoute_Priv::iroute_GetActiveScanInterface(void)
{
    int retval = iroute_stubscan;

    switch(CURRENT_MODE)
    {
        case MANUAL_MODE:
            retval = iroute_userentryscan;
            break;
        default:
            switch(CURRENT_SCAN)
            {
                case rins_QuickScan:
                    retval = iroute_quickscan;
                    break;
                case rins_FullScan:
                    retval = iroute_fullscan;
                    break;
                default:
                    break;
            }   
            break;
    }
    //TraceNotice(m,"%s %d retval %d", __FUNCTION__, __LINE__, retval);
    return retval;
}

FResult CHsvDvbTInstallation_mRoute_Priv::istub_StartInstallation(int source, int ptc, int mode)
{
    UNUSED(source);
    UNUSED(ptc);
    UNUSED(mode);

    //TraceNotice(m,"Danger!!! hey, look all the installation calls are grounded in dvbt comp.");
    return 0;
}
void CHsvDvbTInstallation_mRoute_Priv::istub_Initialise(void)
{
    //TraceNotice(m," Stubbed Initialise called : Check if connections are correct");    
}
void CHsvDvbTInstallation_mRoute_Priv::istub_SetStreamPriority(HsvStreamPriority prio)
{
    UNUSED(prio);
    //TraceNotice(m," Stubbed istub_SetStreamPriority called : Check if connections are correct");   
}
void CHsvDvbTInstallation_mRoute_Priv::ctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{

    if(eurdiv_GetDVBTMode() != SCAN_MPEG_ONLY)
    {
        switch(CURRENT_MODE)
        {
            case AUTO_MODE:
            case UPDATE_MODE:
                switch(CURRENT_SCAN)
                {
                    case rins_QuickScan:
                        iqctrlN_OnEvent(dmx, eventid, value);
                        break;
                    case rins_FullScan:
                        ifctrlN_OnEvent(dmx, eventid, value);
                        break;
                    default:
                        break;
                }
                break;
            case MANUAL_MODE:
                idctrlN_OnEvent(dmx, eventid, value);
                break;
            case BACKGROUND_MODE:
                ibctrlN_OnEvent(dmx, eventid, value);
                break;
        }
        icctrlN_OnEvent(dmx, eventid, value);
    }
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnStationFound()
{

    if(MANUAL_INSTALL)
    {
        idtrfeN_OnStationFound();
    }
    else
    {
        switch(CURRENT_SCAN)
        {
            case rins_QuickScan:
                iquickfeN_OnStationFound();
                break;
            case rins_FullScan:
                ifullfeN_OnStationFound();
                break;
            default:
                break;
        }
    }
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnStationNotFound()
{

    if(MANUAL_INSTALL)
    {
        idtrfeN_OnStationNotFound();
    }
    else
    {
        switch(CURRENT_SCAN)
        {
            case rins_QuickScan:
                iquickfeN_OnStationNotFound();
                break;
            case rins_FullScan:
                ifullfeN_OnStationNotFound();
                break;
            default:
                break;
        }
    }
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode )
{

    if(MANUAL_INSTALL)
    {
        idtrfeN_OnHierarchyModeDetected(mode);
    }
    else
    {
        switch(CURRENT_SCAN)
        {
            case rins_QuickScan:
                iquickfeN_OnHierarchyModeDetected(mode);
                break;
            case rins_FullScan:
                ifullfeN_OnHierarchyModeDetected(mode);
                break;
            default:
                break;
        }
    }
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnMeasReady( int ssm, Nat32 strength )
{

    if(MANUAL_INSTALL)
    {
        idtrfeN_OnMeasReady(ssm, strength);
    }
    else
    {
        switch(CURRENT_SCAN)
        {
            case rins_QuickScan:
                iquickfeN_OnMeasReady(ssm, strength);
                break;
            case rins_FullScan:
                ifullfeN_OnMeasReady(ssm, strength);
                break;
            default:
                break;
        }
    }
}

int CHsvDvbTInstallation_mRoute_Priv::istub_ZiggoGetSDTType(Nat16 Frequency)
{
    UNUSED(Frequency);
    ASSERT(!"Not Implemented here");
    return FALSE;
}

void CHsvDvbTInstallation_mRoute_Priv::istub_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{
    UNUSED(ptc);
    UNUSED(Onid);
    UNUSED(Tsid);
}

/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}


void CHsvDvbTInstallation_mRoute_Priv::pow_Init()
{
    iquickpow_Init();
    ifullpow_Init();
    ibpow_Init();
    idtrpow_Init();
    idatapow_Init();
	icntrypow_Init();
	isetpow_Init();
}

void CHsvDvbTInstallation_mRoute_Priv::pow_TurnOn()
{
	iquickpow_TurnOn();
	ifullpow_TurnOn();
	ibpow_TurnOn();
	idtrpow_TurnOn();
	idatapow_TurnOn();
	icntrypow_TurnOn();
	isetpow_TurnOn();
}

void CHsvDvbTInstallation_mRoute_Priv::pow_TurnOff()
{
	iquickpow_TurnOff();
	ifullpow_TurnOff();
	ibpow_TurnOff();
	idtrpow_TurnOff();
	idatapow_TurnOff();
	icntrypow_TurnOff();
	isetpow_TurnOff();
}




void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnAfcModeChanged( void ) 
{
	return;
}


void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}


void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::feapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::strapiN_OnAdded         ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	ibstrapiN_OnAdded(dest,spid, key1, key2, key3);
	icntrystrapiN_OnAdded(dest,spid, key1, key2, key3);
	idstrapiN_OnAdded(dest,spid, key1, key2, key3);
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::strapiN_OnChanged           ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
	ibstrapiN_OnChanged(dest, spid, key1, key2, key3, eventid);
	icntrystrapiN_OnChanged(dest, spid, key1, key2, key3, eventid);
	idstrapiN_OnChanged(dest, spid, key1, key2, key3, eventid);
	return;
}
void CHsvDvbTInstallation_mRoute_Priv::strapiN_OnRemoved           ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
	ibstrapiN_OnRemoved(dest,spid, key1, key2, key3);
	icntrystrapiN_OnRemoved(dest,spid, key1, key2, key3);
	idstrapiN_OnRemoved(dest,spid, key1, key2, key3);
	return;
}
void CHsvDvbTInstallation_mRoute_Priv::strapiN_OnCompleted           ( HsvDestination dest, int spid)
{
	ibstrapiN_OnCompleted(dest, spid);
	icntrystrapiN_OnCompleted(dest, spid);
	idstrapiN_OnCompleted(dest, spid);
}


/* interface idvbt : IHsvDigitalScan */

 void CHsvDvbTInstallation_mRoute_Priv::idvbt_ClearCache( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    idtr_ClearCache( );
  else if ( Mode==iroute_fullscan )
    ifull_ClearCache( );
  else if ( Mode==iroute_quickscan )
    iquick_ClearCache( );
  else
    istub_ClearCache( );
}

 void CHsvDvbTInstallation_mRoute_Priv::idvbt_ClearPersistent( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    idtr_ClearPersistent( );
  else if ( Mode==iroute_fullscan )
    ifull_ClearPersistent( );
  else if ( Mode==iroute_quickscan )
    iquick_ClearPersistent( );
  else
    istub_ClearPersistent( );
}

 Bool CHsvDvbTInstallation_mRoute_Priv::idvbt_GetAltTSValues( Nat16 * ONID, Nat16 * TSID ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetAltTSValues( ONID, TSID );
  else if ( Mode==iroute_fullscan )
    return ifull_GetAltTSValues( ONID, TSID );
  else if ( Mode==iroute_quickscan )
    return iquick_GetAltTSValues( ONID, TSID );
  else
    return 0x0;
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_GetCurrentPass( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetCurrentPass( );
  else if ( Mode==iroute_fullscan )
    return ifull_GetCurrentPass( );
  else if ( Mode==iroute_quickscan )
    return iquick_GetCurrentPass( );
  else
    return 0x0;
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_GetCurrentState( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetCurrentState( );
  else if ( Mode==iroute_fullscan )
    return ifull_GetCurrentState( );
  else if ( Mode==iroute_quickscan )
    return iquick_GetCurrentState( );
  else
    return 0x0;
}

 Bool CHsvDvbTInstallation_mRoute_Priv::idvbt_GetCurTSValues( Nat16 * ONID, Nat16 * TSID ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetCurTSValues( ONID, TSID );
  else if ( Mode==iroute_fullscan )
    return ifull_GetCurTSValues( ONID, TSID );
  else if ( Mode==iroute_quickscan )
    return iquick_GetCurTSValues( ONID, TSID );
  else
    return 0x0;
}

 void CHsvDvbTInstallation_mRoute_Priv::idvbt_GetEpgBarkerMux( Nat16 * ONID, Nat16 * TSID ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    idtr_GetEpgBarkerMux( ONID, TSID );
  else if ( Mode==iroute_fullscan )
    ifull_GetEpgBarkerMux( ONID, TSID );
  else if ( Mode==iroute_quickscan )
    iquick_GetEpgBarkerMux( ONID, TSID );
  else
    istub_GetEpgBarkerMux( ONID, TSID );
}

 HsvHierarchyMode CHsvDvbTInstallation_mRoute_Priv::idvbt_GetHierarchyMode( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetHierarchyMode( );
  else if ( Mode==iroute_fullscan )
    return ifull_GetHierarchyMode( );
  else if ( Mode==iroute_quickscan )
    return iquick_GetHierarchyMode( );
  else
    return (HsvHierarchyMode)0x0;
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_GetNoOfPass( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetNoOfPass( );
  else if ( Mode==iroute_fullscan )
    return ifull_GetNoOfPass( );
  else if ( Mode==iroute_quickscan )
    return iquick_GetNoOfPass( );
  else
    return 0x0;
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_GetNumberOfDigitalChannelsFound( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetNumberOfDigitalChannelsFound( );
  else if ( Mode==iroute_fullscan )
    return ifull_GetNumberOfDigitalChannelsFound( );
  else if ( Mode==iroute_quickscan )
    return iquick_GetNumberOfDigitalChannelsFound( );
  else
    return 0x0;
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_GetNumberOfDigitalChannelsRemoved( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetNumberOfDigitalChannelsRemoved( );
  else if ( Mode==iroute_fullscan )
    return ifull_GetNumberOfDigitalChannelsRemoved( );
  else if ( Mode==iroute_quickscan )
    return iquick_GetNumberOfDigitalChannelsRemoved( );
  else
    return 0x0;
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_GetPLPIds( int * PLPIds ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetPLPIds( PLPIds );
  else if ( Mode==iroute_fullscan )
    return ifull_GetPLPIds( PLPIds );
  else if ( Mode==iroute_quickscan )
    return iquick_GetPLPIds( PLPIds );
  else
    return 0x0;
}

 void CHsvDvbTInstallation_mRoute_Priv::idvbt_GetPTCInfo( HsvInstallationPTC * ptc ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    idtr_GetPTCInfo( ptc );
  else if ( Mode==iroute_fullscan )
    ifull_GetPTCInfo( ptc );
  else if ( Mode==iroute_quickscan )
    iquick_GetPTCInfo( ptc );
  else
    istub_GetPTCInfo( ptc );
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_GetSDTType( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetSDTType( );
  else if ( Mode==iroute_fullscan )
    return ifull_GetSDTType( );
  else if ( Mode==iroute_quickscan )
    return iquick_GetSDTType( );
  else
    return 0x0;
}

 HsvStreamPriority CHsvDvbTInstallation_mRoute_Priv::idvbt_GetStreamPriority( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetStreamPriority( );
  else if ( Mode==iroute_fullscan )
    return ifull_GetStreamPriority( );
  else if ( Mode==iroute_quickscan )
    return iquick_GetStreamPriority( );
  else
    return (HsvStreamPriority)0x0;
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_GetTargetNitType( Nat16 * NetworkId ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_GetTargetNitType( NetworkId );
  else if ( Mode==iroute_fullscan )
    return ifull_GetTargetNitType( NetworkId );
  else if ( Mode==iroute_quickscan )
    return iquick_GetTargetNitType( NetworkId );
  else
    return 0x0;
}

 void CHsvDvbTInstallation_mRoute_Priv::idvbt_Initialise( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    idtr_Initialise( );
  else if ( Mode==iroute_fullscan )
    ifull_Initialise( );
  else if ( Mode==iroute_quickscan )
    iquick_Initialise( );
  else
    istub_Initialise( );
}

 void CHsvDvbTInstallation_mRoute_Priv::idvbt_SetStreamPriority( HsvStreamPriority prio ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    idtr_SetStreamPriority( prio );
  else if ( Mode==iroute_fullscan )
    ifull_SetStreamPriority( prio );
  else if ( Mode==iroute_quickscan )
    iquick_SetStreamPriority( prio );
  else
    istub_SetStreamPriority( prio );
}

 FResult CHsvDvbTInstallation_mRoute_Priv::idvbt_StartDigitalScan( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_StartDigitalScan( );
  else if ( Mode==iroute_fullscan )
    return ifull_StartDigitalScan( );
  else if ( Mode==iroute_quickscan )
    return iquick_StartDigitalScan( );
  else
    return 0x0;
}

 FResult CHsvDvbTInstallation_mRoute_Priv::idvbt_StartDigitalTuning( int frequency ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_StartDigitalTuning( frequency );
  else if ( Mode==iroute_fullscan )
    return ifull_StartDigitalTuning( frequency );
  else if ( Mode==iroute_quickscan )
    return iquick_StartDigitalTuning( frequency );
  else
    return 0x0;
}

 FResult CHsvDvbTInstallation_mRoute_Priv::idvbt_StartInstallation( int source, int ptc, int mode ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_StartInstallation( source, ptc, mode );
  else if ( Mode==iroute_fullscan )
    return ifull_StartInstallation( source, ptc, mode );
  else if ( Mode==iroute_quickscan )
    return iquick_StartInstallation( source, ptc, mode );
  else
    return istub_StartInstallation( source, ptc, mode );
}

 FResult CHsvDvbTInstallation_mRoute_Priv::idvbt_StopDigitalScan( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_StopDigitalScan( );
  else if ( Mode==iroute_fullscan )
    return ifull_StopDigitalScan( );
  else if ( Mode==iroute_quickscan )
    return iquick_StopDigitalScan( );
  else
    return 0x0;
}

 FResult CHsvDvbTInstallation_mRoute_Priv::idvbt_StopInstallation( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_StopInstallation( );
  else if ( Mode==iroute_fullscan )
    return ifull_StopInstallation( );
  else if ( Mode==iroute_quickscan )
    return iquick_StopInstallation( );
  else
    return 0x0;
}

 FResult CHsvDvbTInstallation_mRoute_Priv::idvbt_StoreWeakSignalInstallationChannel( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_StoreWeakSignalInstallationChannel( );
  else if ( Mode==iroute_fullscan )
    return ifull_StoreWeakSignalInstallationChannel( );
  else if ( Mode==iroute_quickscan )
    return iquick_StoreWeakSignalInstallationChannel( );
  else
    return 0x0;
}

 void CHsvDvbTInstallation_mRoute_Priv::idvbt_SyncComplete( void ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    idtr_SyncComplete( );
  else if ( Mode==iroute_fullscan )
    ifull_SyncComplete( );
  else if ( Mode==iroute_quickscan )
    iquick_SyncComplete( );
  else
    istub_SyncComplete( );
}

 void CHsvDvbTInstallation_mRoute_Priv::idvbt_ZiggoGetPTCInfo( HsvInstallationPTC * ptc, Nat16 Onid, Nat16 Tsid ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    idtr_ZiggoGetPTCInfo( ptc, Onid, Tsid );
  else if ( Mode==iroute_fullscan )
    ifull_ZiggoGetPTCInfo( ptc, Onid, Tsid );
  else if ( Mode==iroute_quickscan )
    iquick_ZiggoGetPTCInfo( ptc, Onid, Tsid );
  else
    istub_ZiggoGetPTCInfo( ptc, Onid, Tsid );
}

 int CHsvDvbTInstallation_mRoute_Priv::idvbt_ZiggoGetSDTType( Nat16 Frequency ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_ZiggoGetSDTType( Frequency );
  else if ( Mode==iroute_fullscan )
    return ifull_ZiggoGetSDTType( Frequency );
  else if ( Mode==iroute_quickscan )
    return iquick_ZiggoGetSDTType( Frequency );
  else
    return istub_ZiggoGetSDTType( Frequency );
}

 Bool CHsvDvbTInstallation_mRoute_Priv::idvbt_ZiggoNetworkDataSet( Bool ActionValue ) {
  int Mode = iroute_GetActiveScanInterface();
  if ( Mode==iroute_userentryscan )
    return idtr_ZiggoNetworkDataSet( ActionValue );
  else if ( Mode==iroute_fullscan )
    return ifull_ZiggoNetworkDataSet( ActionValue );
  else if ( Mode==iroute_quickscan )
    return iquick_ZiggoNetworkDataSet( ActionValue );
  else
    return istub_ZiggoNetworkDataSet( ActionValue );
}
 
void CHsvDvbTInstallation_mRoute_Priv::idvbt_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}

/* Interfaces from IHsvdigitalscan.id */

FResult CHsvDvbTInstallation_mRoute_Priv::istub_StopInstallation(void ) 
{
	return 0;
}

FResult CHsvDvbTInstallation_mRoute_Priv::istub_StartDigitalScan(void) 
{
	return 0;
}

FResult CHsvDvbTInstallation_mRoute_Priv::istub_StartDigitalTuning(int frequency) 
{
	return 0;
}

FResult CHsvDvbTInstallation_mRoute_Priv::istub_StopDigitalScan (void) 
{
	return 0;
}

int CHsvDvbTInstallation_mRoute_Priv::istub_GetNoOfPass(void) 
{
	return 0;
}

int CHsvDvbTInstallation_mRoute_Priv::istub_GetCurrentPass ( void ) 
{
	return 0;
}

void CHsvDvbTInstallation_mRoute_Priv::istub_GetPTCInfo(HsvInstallationPTC *ptc) 
{
	return;
}

FResult CHsvDvbTInstallation_mRoute_Priv::istub_StoreWeakSignalInstallationChannel()         
{
	return 0;
}

int CHsvDvbTInstallation_mRoute_Priv::istub_GetNumberOfDigitalChannelsFound() 
{
	return 0;
}

int CHsvDvbTInstallation_mRoute_Priv::istub_GetNumberOfDigitalChannelsRemoved() 
{
	return 0;
}

int CHsvDvbTInstallation_mRoute_Priv::istub_GetTargetNitType(Nat16* NetworkId) 
{
	return 0;
}

int CHsvDvbTInstallation_mRoute_Priv::istub_GetCurrentState() 
{
	return 0;
}

int CHsvDvbTInstallation_mRoute_Priv::istub_GetSDTType() 
{
	return 0;
}

Bool CHsvDvbTInstallation_mRoute_Priv::istub_GetAltTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

Bool CHsvDvbTInstallation_mRoute_Priv::istub_GetCurTSValues( Nat16* ONID, Nat16* TSID ) 
{
	return FALSE;
}

HsvStreamPriority CHsvDvbTInstallation_mRoute_Priv::istub_GetStreamPriority(void) 
{
	return (HsvStreamPriority)0;
}

void CHsvDvbTInstallation_mRoute_Priv::istub_SyncComplete(void)     
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::istub_ClearCache(void) 
{
	return;
}

int CHsvDvbTInstallation_mRoute_Priv::istub_GetPLPIds(int *PLPIds) 
{
	return 0;
}

HsvHierarchyMode CHsvDvbTInstallation_mRoute_Priv::istub_GetHierarchyMode(void) 
{
	return (HsvHierarchyMode)0;
}



void CHsvDvbTInstallation_mRoute_Priv::istub_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID) 
{
	return;
}

Bool CHsvDvbTInstallation_mRoute_Priv::istub_ZiggoNetworkDataSet(Bool ActionValue) 
{
	return FALSE;
}

void CHsvDvbTInstallation_mRoute_Priv::istub_ClearPersistent() 
{
	return;
}

void CHsvDvbTInstallation_mRoute_Priv::istub_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}


