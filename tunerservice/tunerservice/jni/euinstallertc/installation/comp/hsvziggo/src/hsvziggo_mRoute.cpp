#include "_hsvziggo_mRoute.h"

TRACESYMBOL(m, "dvb/installation/hsvziggo_mRoute")



FResult CHsvZiggoInstallation_mRoute_Priv::istub_StartInstallation(int source, int ptc, int mode)
{
    UNUSED(source);
    UNUSED(ptc);
    UNUSED(mode);
    TraceNotice(m,"Danger!!! hey, look all the installation calls are grounded in dvbt comp.");
    return 0;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnStationFound()
{
    if(PRE_INSTALL)
    {
        ipreinsfeapiN_OnStationFound();
    }
    else
    {
        iinsfeapiN_OnStationFound();
    }
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnStationNotFound()
{
    if(PRE_INSTALL)
    {
        ipreinsfeapiN_OnStationNotFound();
    }
    else
    {
        iinsfeapiN_OnStationNotFound();
    }
}

void CHsvZiggoInstallation_mRoute_Priv::ctrlN_OnEvent( HsvDemux dmx, int eventid, int value )
{
    switch(CURRENT_MODE)
    {
        case PRESCAN_MODE:
            ipreinsctrlN_OnEvent(dmx, eventid, value);
            break;
        case BACKGROUND_MODE:
            ibckgctrlN_OnEvent(dmx, eventid, value);
            break;
        default:
            iinsctrlN_OnEvent(dmx, eventid, value);
            break;
    }
}

void CHsvZiggoInstallation_mRoute_Priv::istub_Initialise()
{ }
FResult CHsvZiggoInstallation_mRoute_Priv::istub_StopInstallation(void)
{ return 0; }
FResult CHsvZiggoInstallation_mRoute_Priv::istub_StartDigitalScan(void)
{ return 0; }
FResult CHsvZiggoInstallation_mRoute_Priv::istub_StartDigitalTuning(int frequency)
{   UNUSED(frequency); return 0; }
FResult CHsvZiggoInstallation_mRoute_Priv::istub_StopDigitalScan (void)
{ return 0; }
int CHsvZiggoInstallation_mRoute_Priv::istub_GetNoOfPass(void)
{ return 0; }
int CHsvZiggoInstallation_mRoute_Priv::istub_GetCurrentPass ( void )
{ return 0; }
FResult CHsvZiggoInstallation_mRoute_Priv::istub_StoreWeakSignalInstallationChannel()
{ return 0; }
int CHsvZiggoInstallation_mRoute_Priv::istub_GetNumberOfDigitalChannelsFound()
{ return 0; }
int CHsvZiggoInstallation_mRoute_Priv::istub_GetNumberOfDigitalChannelsRemoved()
{ return 0; }
int CHsvZiggoInstallation_mRoute_Priv::istub_GetTargetNitType(Nat16* NetworkId)
{ UNUSED(NetworkId); return 0; }
int CHsvZiggoInstallation_mRoute_Priv::istub_GetCurrentState()
{ return 0; }
int CHsvZiggoInstallation_mRoute_Priv::istub_GetSDTType()
{ return 0; }
Bool CHsvZiggoInstallation_mRoute_Priv::istub_GetCurTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }    
HsvStreamPriority CHsvZiggoInstallation_mRoute_Priv::istub_GetStreamPriority(void)
{ return (HsvStreamPriority)0; }
HsvHierarchyMode CHsvZiggoInstallation_mRoute_Priv::istub_GetHierarchyMode(void)
{ return (HsvHierarchyMode)0; }
void CHsvZiggoInstallation_mRoute_Priv::istub_GetPTCInfo(HsvInstallationPTC *ptc)
{ UNUSED(ptc); }
void CHsvZiggoInstallation_mRoute_Priv::istub_ZiggoGetPTCInfo(HsvInstallationPTC *ptc, Nat16 Onid, Nat16 Tsid)
{ UNUSED(ptc); UNUSED(Onid); UNUSED(Tsid); }
int CHsvZiggoInstallation_mRoute_Priv::istub_ZiggoGetSDTType(Nat16 Frequency)
{ UNUSED(Frequency); return 0; }
Bool CHsvZiggoInstallation_mRoute_Priv::istub_GetAltTSValues( Nat16* ONID, Nat16* TSID )
{ UNUSED(ONID); UNUSED(TSID); return 0; }
void CHsvZiggoInstallation_mRoute_Priv::istub_SetStreamPriority (HsvStreamPriority prio)
{ UNUSED(prio); }
void CHsvZiggoInstallation_mRoute_Priv::istub_SyncComplete(void)
{ }
void CHsvZiggoInstallation_mRoute_Priv::istub_ClearCache(void)
{ }
int CHsvZiggoInstallation_mRoute_Priv::istub_GetPLPIds(int *PLPIds)
{ UNUSED(PLPIds); return 0; }
void CHsvZiggoInstallation_mRoute_Priv::istub_GetEpgBarkerMux(Nat16 *ONID, Nat16 *TSID)
{
    UNUSED(ONID);
    UNUSED(TSID);
}
Bool CHsvZiggoInstallation_mRoute_Priv::istub_ZiggoNetworkDataSet(Bool ActionValue)
{
	UNUSED(ActionValue);
	return FALSE;
}
void CHsvZiggoInstallation_mRoute_Priv::istub_ClearPersistent()
{
}
void CHsvZiggoInstallation_mRoute_Priv::istub_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}

/* Interfaces from IHsvFrontEndApiNotify.id */
void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnSearchStateChanged( tmFe_SearchState_t state ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnSearchInProgress( tmFe_SearchState_t state ) 
{
	return;
}


void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnTvSystemDetected( tmFe_TvSystem_t tvSystem ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnAfcFreqChanged( Nat32 freq ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnAfcLimitReached(Nat32 freq ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnAfcModeChanged( void ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnMeasReady( int ssm, Nat32 strength ) 
{
	idtrfeapiN_OnMeasReady( ssm, strength );
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnMeasAborted( int ssm ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnConstellationDetected( tmFe_Constellation_t constellation ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnIqModeDetected( tmFe_IqMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnCodeRateDetected( tmFe_CodeRate_t highPrioRate, tmFe_CodeRate_t lowPrioRate ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnHierarchyModeDetected( tmFe_HierarchyMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnGuardIntervalDetected( tmFe_GuardInterval_t interval ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnTxModeDetected( tmFe_TxMode_t mode ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnChanBandwidthDetected( tmFe_ChanBandwidth_t bandwith ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnCarrierPresentChanged( Bool carrier ) 
{
	return;
}

void CHsvZiggoInstallation_mRoute_Priv::feapiN_OnBerThresholdCrossed( Nat32 ber, Nat32 berThreshold ) 
{
	return;
}

/* interface ins : IHsvDigitalScan */

void CHsvZiggoInstallation_mRoute_Priv::ins_ClearCache( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    ibckg_ClearCache( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    idtr_ClearCache( );
  else if ( Mode==rins_InstallationModePreScan )
    ipreins_ClearCache( );
  else if ( Mode==rins_InstallationModeAutomatic )
    iins_ClearCache( );
  else
    istub_ClearCache( );
}

void CHsvZiggoInstallation_mRoute_Priv::ins_ClearPersistent( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    ibckg_ClearPersistent( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    idtr_ClearPersistent( );
  else if ( Mode==rins_InstallationModePreScan )
    ipreins_ClearPersistent( );
  else if ( Mode==rins_InstallationModeAutomatic )
    iins_ClearPersistent( );
  else
    istub_ClearPersistent( );
}

Bool CHsvZiggoInstallation_mRoute_Priv::ins_GetAltTSValues( Nat16 * ONID, Nat16 * TSID ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetAltTSValues( ONID, TSID );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetAltTSValues( ONID, TSID );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetAltTSValues( ONID, TSID );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetAltTSValues( ONID, TSID );
  else
    return istub_GetAltTSValues( ONID, TSID );
}


void CHsvZiggoInstallation_mRoute_Priv::ins_GetSIDetails(HsvSDMSIDataValues* sivalues)
{
	return;
}

int CHsvZiggoInstallation_mRoute_Priv::ins_GetCurrentPass( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetCurrentPass( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetCurrentPass( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetCurrentPass( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetCurrentPass( );
  else
    return istub_GetCurrentPass( );
}

int CHsvZiggoInstallation_mRoute_Priv::ins_GetCurrentState( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetCurrentState( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetCurrentState( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetCurrentState( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetCurrentState( );
  else
    return istub_GetCurrentState( );
}

Bool CHsvZiggoInstallation_mRoute_Priv::ins_GetCurTSValues( Nat16 * ONID, Nat16 * TSID ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetCurTSValues( ONID, TSID );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetCurTSValues( ONID, TSID );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetCurTSValues( ONID, TSID );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetCurTSValues( ONID, TSID );
  else
    return istub_GetCurTSValues( ONID, TSID );
}

void CHsvZiggoInstallation_mRoute_Priv::ins_GetEpgBarkerMux( Nat16 * ONID, Nat16 * TSID ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    ibckg_GetEpgBarkerMux( ONID, TSID );
  else if ( Mode==rins_InstallationModeWeakSignal )
    idtr_GetEpgBarkerMux( ONID, TSID );
  else if ( Mode==rins_InstallationModePreScan )
    ipreins_GetEpgBarkerMux( ONID, TSID );
  else if ( Mode==rins_InstallationModeAutomatic )
    iins_GetEpgBarkerMux( ONID, TSID );
  else
    istub_GetEpgBarkerMux( ONID, TSID );
}

HsvHierarchyMode CHsvZiggoInstallation_mRoute_Priv::ins_GetHierarchyMode( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetHierarchyMode( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetHierarchyMode( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetHierarchyMode( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetHierarchyMode( );
  else
    return istub_GetHierarchyMode( );
}

int CHsvZiggoInstallation_mRoute_Priv::ins_GetNoOfPass( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetNoOfPass( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetNoOfPass( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetNoOfPass( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetNoOfPass( );
  else
    return istub_GetNoOfPass( );
}

int CHsvZiggoInstallation_mRoute_Priv::ins_GetNumberOfDigitalChannelsFound( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetNumberOfDigitalChannelsFound( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetNumberOfDigitalChannelsFound( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetNumberOfDigitalChannelsFound( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetNumberOfDigitalChannelsFound( );
  else
    return istub_GetNumberOfDigitalChannelsFound( );
}

int CHsvZiggoInstallation_mRoute_Priv::ins_GetNumberOfDigitalChannelsRemoved( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetNumberOfDigitalChannelsRemoved( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetNumberOfDigitalChannelsRemoved( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetNumberOfDigitalChannelsRemoved( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetNumberOfDigitalChannelsRemoved( );
  else
    return istub_GetNumberOfDigitalChannelsRemoved( );
}

int CHsvZiggoInstallation_mRoute_Priv::ins_GetPLPIds( int * PLPIds ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetPLPIds( PLPIds );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetPLPIds( PLPIds );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetPLPIds( PLPIds );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetPLPIds( PLPIds );
  else
    return istub_GetPLPIds( PLPIds );
}

void CHsvZiggoInstallation_mRoute_Priv::ins_GetPTCInfo( HsvInstallationPTC * ptc ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    ibckg_GetPTCInfo( ptc );
  else if ( Mode==rins_InstallationModeWeakSignal )
    idtr_GetPTCInfo( ptc );
  else if ( Mode==rins_InstallationModePreScan )
    ipreins_GetPTCInfo( ptc );
  else if ( Mode==rins_InstallationModeAutomatic )
    iins_GetPTCInfo( ptc );
  else
    istub_GetPTCInfo( ptc );
}

int CHsvZiggoInstallation_mRoute_Priv::ins_GetSDTType( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetSDTType( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetSDTType( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetSDTType( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetSDTType( );
  else
    return istub_GetSDTType( );
}

HsvStreamPriority CHsvZiggoInstallation_mRoute_Priv::ins_GetStreamPriority( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetStreamPriority( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetStreamPriority( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetStreamPriority( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetStreamPriority( );
  else
    return istub_GetStreamPriority( );
}

int CHsvZiggoInstallation_mRoute_Priv::ins_GetTargetNitType( Nat16 * NetworkId ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_GetTargetNitType( NetworkId );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_GetTargetNitType( NetworkId );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_GetTargetNitType( NetworkId );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_GetTargetNitType( NetworkId );
  else
    return istub_GetTargetNitType( NetworkId );
}

void CHsvZiggoInstallation_mRoute_Priv::ins_Initialise( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    ibckg_Initialise( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    idtr_Initialise( );
  else if ( Mode==rins_InstallationModePreScan )
    ipreins_Initialise( );
  else if ( Mode==rins_InstallationModeAutomatic )
    iins_Initialise( );
  else
    istub_Initialise( );
}

void CHsvZiggoInstallation_mRoute_Priv::ins_SetStreamPriority( HsvStreamPriority prio ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    ibckg_SetStreamPriority( prio );
  else if ( Mode==rins_InstallationModeWeakSignal )
    idtr_SetStreamPriority( prio );
  else if ( Mode==rins_InstallationModePreScan )
    ipreins_SetStreamPriority( prio );
  else if ( Mode==rins_InstallationModeAutomatic )
    iins_SetStreamPriority( prio );
  else
    istub_SetStreamPriority( prio );
}

FResult CHsvZiggoInstallation_mRoute_Priv::ins_StartDigitalScan( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_StartDigitalScan( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_StartDigitalScan( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_StartDigitalScan( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_StartDigitalScan( );
  else
    return istub_StartDigitalScan( );
}

FResult CHsvZiggoInstallation_mRoute_Priv::ins_StartDigitalTuning( int frequency ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_StartDigitalTuning( frequency );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_StartDigitalTuning( frequency );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_StartDigitalTuning( frequency );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_StartDigitalTuning( frequency );
  else
    return istub_StartDigitalTuning( frequency );
}

FResult CHsvZiggoInstallation_mRoute_Priv::ins_StartInstallation( int source, int ptc, int mode ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_StartInstallation( source, ptc, mode );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_StartInstallation( source, ptc, mode );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_StartInstallation( source, ptc, mode );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_StartInstallation( source, ptc, mode );
  else
    return istub_StartInstallation( source, ptc, mode );
}

FResult CHsvZiggoInstallation_mRoute_Priv::ins_StopDigitalScan( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_StopDigitalScan( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_StopDigitalScan( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_StopDigitalScan( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_StopDigitalScan( );
  else
    return istub_StopDigitalScan( );
}

FResult CHsvZiggoInstallation_mRoute_Priv::ins_StopInstallation( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_StopInstallation( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_StopInstallation( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_StopInstallation( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_StopInstallation( );
  else
    return istub_StopInstallation( );
}

FResult CHsvZiggoInstallation_mRoute_Priv::ins_StoreWeakSignalInstallationChannel( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_StoreWeakSignalInstallationChannel( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_StoreWeakSignalInstallationChannel( );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_StoreWeakSignalInstallationChannel( );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_StoreWeakSignalInstallationChannel( );
  else
    return istub_StoreWeakSignalInstallationChannel( );
}

void CHsvZiggoInstallation_mRoute_Priv::ins_SyncComplete( void ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    ibckg_SyncComplete( );
  else if ( Mode==rins_InstallationModeWeakSignal )
    idtr_SyncComplete( );
  else if ( Mode==rins_InstallationModePreScan )
    ipreins_SyncComplete( );
  else if ( Mode==rins_InstallationModeAutomatic )
    iins_SyncComplete( );
  else
    istub_SyncComplete( );
}

void CHsvZiggoInstallation_mRoute_Priv::ins_ZiggoGetPTCInfo( HsvInstallationPTC * ptc, Nat16 Onid, Nat16 Tsid ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    ibckg_ZiggoGetPTCInfo( ptc, Onid, Tsid );
  else if ( Mode==rins_InstallationModeWeakSignal )
    idtr_ZiggoGetPTCInfo( ptc, Onid, Tsid );
  else if ( Mode==rins_InstallationModePreScan )
    ipreins_ZiggoGetPTCInfo( ptc, Onid, Tsid );
  else if ( Mode==rins_InstallationModeAutomatic )
    iins_ZiggoGetPTCInfo( ptc, Onid, Tsid );
  else
    istub_ZiggoGetPTCInfo( ptc, Onid, Tsid );
}

int CHsvZiggoInstallation_mRoute_Priv::ins_ZiggoGetSDTType( Nat16 Frequency ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_ZiggoGetSDTType( Frequency );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_ZiggoGetSDTType( Frequency );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_ZiggoGetSDTType( Frequency );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_ZiggoGetSDTType( Frequency );
  else
    return istub_ZiggoGetSDTType( Frequency );
}

Bool CHsvZiggoInstallation_mRoute_Priv::ins_ZiggoNetworkDataSet( Bool ActionValue ) {
  int Mode = rins_GetInstallationMode();
  if ( Mode==rins_InstallationModeBackground )
    return ibckg_ZiggoNetworkDataSet( ActionValue );
  else if ( Mode==rins_InstallationModeWeakSignal )
    return idtr_ZiggoNetworkDataSet( ActionValue );
  else if ( Mode==rins_InstallationModePreScan )
    return ipreins_ZiggoNetworkDataSet( ActionValue );
  else if ( Mode==rins_InstallationModeAutomatic )
    return iins_ZiggoNetworkDataSet( ActionValue );
  else
    return istub_ZiggoNetworkDataSet( ActionValue );
}


void CHsvZiggoInstallation_mRoute_Priv::pow_Init    ( void )
{
	ipreinspow_Init();
    iinspow_Init();
    ibckgpow_Init();
	idtrpow_Init();

}
void CHsvZiggoInstallation_mRoute_Priv::pow_TurnOn  ( void )
{
	ipreinspow_TurnOn();
	iinspow_TurnOn();
	ibckgpow_TurnOn();
	idtrpow_TurnOn();
}
void CHsvZiggoInstallation_mRoute_Priv::pow_TurnOff ( void )
{
	ipreinspow_TurnOff();
	iinspow_TurnOff();
	ibckgpow_TurnOff();
	idtrpow_TurnOff();
}