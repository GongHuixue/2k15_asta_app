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
 *          %name: msysctl.c %
 *       %version: TVG_tv550r4dev1_5 %
 * %date_modified: Wed Nov 21 17:18:35 2007 %
 *    %derived_by: vijayan % 
 */

#include "_hsveuins_mroute.h"

TRACESYMBOL(m,"hsveuins/hsveuins_mroute")

void CHsvEuropeInstallation_mroute_Priv::isort_AddAnalogPreset( Address adata ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    itasort_AddAnalogPreset( adata );
  else if ( ret==isortroute_dvbtlitesort )
    idvbtlitesort_AddAnalogPreset( adata );
  else if ( ret==isortroute_finsort )
    ifinsort_AddAnalogPreset( adata );
  else if ( ret==isortroute_dvbt2sort )
    idbooksort_AddAnalogPreset( adata );
  else if ( ret==isortroute_dvbcsort )
    idvbcsort_AddAnalogPreset( adata );
  else if ( ret==isortroute_dvbtsort )
    idvbtsort_AddAnalogPreset( adata );
  else if ( ret==isortroute_dvbclitesort )
    idvbclitesort_AddAnalogPreset( adata );
  else if ( ret==isortroute_norsort )
    inorsort_AddAnalogPreset( adata );
  else if ( ret==isortroute_apmeasort )
  	 idvbtapmeasort_AddAnalogPreset(adata);
  else if ( ret==isortroute_hungarysort )
	idvbthungarysort_AddAnalogPreset(adata);
  else if ( ret==isortroute_blizoosort )
  	 iblizoosort_AddAnalogPreset(adata);	 
  else
    istubsort_AddAnalogPreset( adata );
}

void CHsvEuropeInstallation_mroute_Priv::isort_AddDigitalPreset( HsvPgdatDigServiceData * svcdat ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    itasort_AddDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbtlitesort )
    idvbtlitesort_AddDigitalPreset( svcdat );
  else if ( ret==isortroute_finsort )
    ifinsort_AddDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbt2sort )
    idbooksort_AddDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbcsort )
    idvbcsort_AddDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbtsort )
    idvbtsort_AddDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbclitesort )
    idvbclitesort_AddDigitalPreset( svcdat );
  else if ( ret==isortroute_norsort )
    inorsort_AddDigitalPreset( svcdat );
  else if ( ret==isortroute_apmeasort )
    idvbtapmeasort_AddDigitalPreset(svcdat);
  else if ( ret==isortroute_hungarysort )
    idvbthungarysort_AddDigitalPreset(svcdat);  
  else if ( ret==isortroute_blizoosort )
    iblizoosort_AddDigitalPreset(svcdat);
  else
    istubsort_AddDigitalPreset( svcdat );
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_AnalogPresetEntry( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_AnalogPresetEntry( );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_AnalogPresetEntry( );
  else if ( ret==isortroute_finsort )
    return ifinsort_AnalogPresetEntry( );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_AnalogPresetEntry( );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_AnalogPresetEntry( );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_AnalogPresetEntry( );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_AnalogPresetEntry( );
  else if ( ret==isortroute_norsort )
    return inorsort_AnalogPresetEntry( );
   else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_AnalogPresetEntry( );
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_AnalogPresetEntry( );   
   else if ( ret==isortroute_blizoosort )
    return iblizoosort_AnalogPresetEntry( );
  else
    return 0;
}

void CHsvEuropeInstallation_mroute_Priv::isort_AssignPresetsForCountry( int ONID ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    itasort_AssignPresetsForCountry( ONID );
  else if ( ret==isortroute_dvbtlitesort )
    idvbtlitesort_AssignPresetsForCountry( ONID );
  else if ( ret==isortroute_finsort )
    ifinsort_AssignPresetsForCountry( ONID );
  else if ( ret==isortroute_dvbt2sort )
    idbooksort_AssignPresetsForCountry( ONID );
  else if ( ret==isortroute_dvbcsort )
    idvbcsort_AssignPresetsForCountry( ONID );
  else if ( ret==isortroute_dvbtsort )
    idvbtsort_AssignPresetsForCountry( ONID );
  else if ( ret==isortroute_dvbclitesort )
    idvbclitesort_AssignPresetsForCountry( ONID );
  else if ( ret==isortroute_norsort )
    inorsort_AssignPresetsForCountry( ONID );
  else if ( ret==isortroute_apmeasort )
	idvbtapmeasort_AssignPresetsForCountry( ONID );
   else if ( ret==isortroute_hungarysort )
	idvbthungarysort_AssignPresetsForCountry( ONID ); 
  else if ( ret==isortroute_blizoosort )
	iblizoosort_AssignPresetsForCountry( ONID );	
  else
    istubsort_AssignPresetsForCountry( ONID );
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_AssignPresetsForCurrentCountry( int CurrentOnwid, Bool CheckLCN ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
  else if ( ret==isortroute_finsort )
    return ifinsort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
  else if ( ret==isortroute_norsort )
    return inorsort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
    else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );
    else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );	
    else if ( ret==isortroute_blizoosort )
    return iblizoosort_AssignPresetsForCurrentCountry( CurrentOnwid, CheckLCN );	
  else
    return 0;
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_AssignPresetsForCurrentCountryLowPrioLCN( int CurrentOnwid ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid );
  else if ( ret==isortroute_finsort )
    return ifinsort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid );
  else if ( ret==isortroute_norsort )
    return inorsort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid );
   else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid ) ;
    else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid ) ;  
   else if ( ret==isortroute_blizoosort )
    return iblizoosort_AssignPresetsForCurrentCountryLowPrioLCN( CurrentOnwid ) ;	
  else
    return 0;
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_AssignPresetsForCurrentCountryNonLCNs( int CurrentOnwid, int * FillHoles ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );
  else if ( ret==isortroute_finsort )
    return ifinsort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );
  else if ( ret==isortroute_norsort )
    return inorsort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles ); 
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );  
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_AssignPresetsForCurrentCountryNonLCNs( CurrentOnwid, FillHoles );	
  else
    return 0;
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_AssignPresetsOfOtherCountries( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_finsort )
    return ifinsort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_norsort )
    return inorsort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_AssignPresetsOfOtherCountries( ); 
  else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_AssignPresetsOfOtherCountries( );
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_AssignPresetsOfOtherCountries( );	
  else
    return 0;
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_AssignPresetsWithStaticTable( int CurrentOnwid, int Country ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_AssignPresetsWithStaticTable( CurrentOnwid, Country );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_AssignPresetsWithStaticTable( CurrentOnwid, Country );
  else if ( ret==isortroute_finsort )
    return ifinsort_AssignPresetsWithStaticTable( CurrentOnwid, Country );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_AssignPresetsWithStaticTable( CurrentOnwid, Country );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_AssignPresetsWithStaticTable( CurrentOnwid, Country );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_AssignPresetsWithStaticTable( CurrentOnwid, Country );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_AssignPresetsWithStaticTable( CurrentOnwid, Country );
  else if ( ret==isortroute_norsort )
    return inorsort_AssignPresetsWithStaticTable( CurrentOnwid, Country );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_AssignPresetsWithStaticTable( CurrentOnwid, Country );  
  else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_AssignPresetsWithStaticTable( CurrentOnwid, Country ); 
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_AssignPresetsWithStaticTable( CurrentOnwid, Country );	
  else
    return 0;
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_AutoStoreManualInstallationValues( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_AutoStoreManualInstallationValues( );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_AutoStoreManualInstallationValues( );
  else if ( ret==isortroute_finsort )
    return ifinsort_AutoStoreManualInstallationValues( );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_AutoStoreManualInstallationValues( );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_AutoStoreManualInstallationValues( );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_AutoStoreManualInstallationValues( );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_AutoStoreManualInstallationValues( );
  else if ( ret==isortroute_norsort )
    return inorsort_AutoStoreManualInstallationValues( );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_AutoStoreManualInstallationValues( );  
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_AutoStoreManualInstallationValues( );  
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_AutoStoreManualInstallationValues( );	
  else
    return 0;
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_DeleteAllDigitalChannels( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_DeleteAllDigitalChannels( );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_DeleteAllDigitalChannels( );
  else if ( ret==isortroute_finsort )
    return ifinsort_DeleteAllDigitalChannels( );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_DeleteAllDigitalChannels( );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_DeleteAllDigitalChannels( );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_DeleteAllDigitalChannels( );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_DeleteAllDigitalChannels( );
  else if ( ret==isortroute_norsort )
    return inorsort_DeleteAllDigitalChannels( );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_DeleteAllDigitalChannels( );  
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_DeleteAllDigitalChannels( );   
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_DeleteAllDigitalChannels( ); 	
  else
    return 0;
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_DeleteInvalidPTCTable( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_finsort )
    return ifinsort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_norsort )
    return inorsort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_DeleteInvalidPTCTable( );  
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_DeleteInvalidPTCTable( );
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_DeleteInvalidPTCTable( );	
  else
    return 0;
}

HsvChannel CHsvEuropeInstallation_mroute_Priv::isort_GetInstalledWeakSignalChannel( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_GetInstalledWeakSignalChannel( );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_GetInstalledWeakSignalChannel( );
  else if ( ret==isortroute_finsort )
    return ifinsort_GetInstalledWeakSignalChannel( );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_GetInstalledWeakSignalChannel( );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_GetInstalledWeakSignalChannel( );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_GetInstalledWeakSignalChannel( );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_GetInstalledWeakSignalChannel( );
  else if ( ret==isortroute_norsort )
    return inorsort_GetInstalledWeakSignalChannel( );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_GetInstalledWeakSignalChannel( );  
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_GetInstalledWeakSignalChannel( );  
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_GetInstalledWeakSignalChannel( ); 	
  else
    return istubsort_GetInstalledWeakSignalChannel( );
}

int CHsvEuropeInstallation_mroute_Priv::isort_GetNumberOfAnalogChannelsFound( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_GetNumberOfAnalogChannelsFound( );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_GetNumberOfAnalogChannelsFound( );
  else if ( ret==isortroute_finsort )
    return ifinsort_GetNumberOfAnalogChannelsFound( );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_GetNumberOfAnalogChannelsFound( );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_GetNumberOfAnalogChannelsFound( );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_GetNumberOfAnalogChannelsFound( );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_GetNumberOfAnalogChannelsFound( );
  else if ( ret==isortroute_norsort )
    return inorsort_GetNumberOfAnalogChannelsFound( );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_GetNumberOfAnalogChannelsFound( );  
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_GetNumberOfAnalogChannelsFound( );   
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_GetNumberOfAnalogChannelsFound( );	
  else
    return isortroute_dvbtsort;
}

int CHsvEuropeInstallation_mroute_Priv::isort_GetOriginalNetworkId( int CurrentCountry ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_GetOriginalNetworkId( CurrentCountry );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_GetOriginalNetworkId( CurrentCountry );
  else if ( ret==isortroute_finsort )
    return ifinsort_GetOriginalNetworkId( CurrentCountry );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_GetOriginalNetworkId( CurrentCountry );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_GetOriginalNetworkId( CurrentCountry );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_GetOriginalNetworkId( CurrentCountry );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_GetOriginalNetworkId( CurrentCountry );
  else if ( ret==isortroute_norsort )
    return inorsort_GetOriginalNetworkId( CurrentCountry );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_GetOriginalNetworkId( CurrentCountry ); 
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_GetOriginalNetworkId( CurrentCountry );  
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_GetOriginalNetworkId( CurrentCountry );	
  else
    return isortroute_dvbtsort;
}

void CHsvEuropeInstallation_mroute_Priv::isort_Initialise( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    itasort_Initialise( );
  else if ( ret==isortroute_dvbtlitesort )
    idvbtlitesort_Initialise( );
  else if ( ret==isortroute_finsort )
    ifinsort_Initialise( );
  else if ( ret==isortroute_dvbt2sort )
    idbooksort_Initialise( );
  else if ( ret==isortroute_dvbcsort )
    idvbcsort_Initialise( );
  else if ( ret==isortroute_dvbtsort )
    idvbtsort_Initialise( );
  else if ( ret==isortroute_dvbclitesort )
    idvbclitesort_Initialise( );
  else if ( ret==isortroute_norsort )
    inorsort_Initialise( );
  else if ( ret==isortroute_apmeasort )
    idvbtapmeasort_Initialise( );  
   else if ( ret==isortroute_hungarysort )
    idvbthungarysort_Initialise( );  
  else if ( ret==isortroute_blizoosort )
    iblizoosort_Initialise( ); 	
  else
    istubsort_Initialise( );
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_IsPresetInstalled( Int32 frequency ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_finsort )
    return ifinsort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_norsort )
    return inorsort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_IsPresetInstalled( frequency );  
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_IsPresetInstalled( frequency );
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_IsPresetInstalled( frequency );	
  else
    return 0;
}

void CHsvEuropeInstallation_mroute_Priv::isort_RemoveDigitalPresets( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    itasort_RemoveDigitalPresets( );
  else if ( ret==isortroute_dvbtlitesort )
    idvbtlitesort_RemoveDigitalPresets( );
  else if ( ret==isortroute_finsort )
    ifinsort_RemoveDigitalPresets( );
  else if ( ret==isortroute_dvbt2sort )
    idbooksort_RemoveDigitalPresets( );
  else if ( ret==isortroute_dvbcsort )
    idvbcsort_RemoveDigitalPresets( );
  else if ( ret==isortroute_dvbtsort )
    idvbtsort_RemoveDigitalPresets( );
  else if ( ret==isortroute_dvbclitesort )
    idvbclitesort_RemoveDigitalPresets( );
  else if ( ret==isortroute_norsort )
    inorsort_RemoveDigitalPresets( );
  else if ( ret==isortroute_apmeasort )
    idvbtapmeasort_RemoveDigitalPresets( );  
  else if ( ret==isortroute_hungarysort )
    idvbthungarysort_RemoveDigitalPresets( ); 
  else if ( ret==isortroute_blizoosort )
    iblizoosort_RemoveDigitalPresets( );	
  else
    istubsort_RemoveDigitalPresets( );
}

void CHsvEuropeInstallation_mroute_Priv::isort_SortAll( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
  if ( ret==isortroute_italysort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    itasort_SortAll( );
  	}
  else if ( ret==isortroute_dvbtlitesort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    idvbtlitesort_SortAll( );
  	}
  else if ( ret==isortroute_finsort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    ifinsort_SortAll( );
  	}
  else if ( ret==isortroute_dvbt2sort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    idbooksort_SortAll( );
  	}
  else if ( ret==isortroute_dvbcsort )
  	{  
  	TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    idvbcsort_SortAll( );
  	}
  else if ( ret==isortroute_blizoosort )
  	{  
  	TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    iblizoosort_SortAll( );
  	}	
  else if ( ret==isortroute_dvbtsort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    idvbtsort_SortAll( );
  	}
  else if ( ret==isortroute_dvbclitesort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    idvbclitesort_SortAll( );
  	}
  else if ( ret==isortroute_norsort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    inorsort_SortAll( );
  	}
    else if ( ret==isortroute_apmeasort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
     idvbtapmeasort_SortAll( );
  	}
	else if ( ret==isortroute_hungarysort )
  	{
  	  TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
     idvbthungarysort_SortAll( );
  	}
  else
  	{  
  	TraceNotice(m,"%s:%d",__FUNCTION__,__LINE__);
    istubsort_SortAll( );
  	}
}

void CHsvEuropeInstallation_mroute_Priv::isort_UpdateDigitalPreset( HsvPgdatDigServiceData * svcdat ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    itasort_UpdateDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbtlitesort )
    idvbtlitesort_UpdateDigitalPreset( svcdat );
  else if ( ret==isortroute_finsort )
    ifinsort_UpdateDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbt2sort )
    idbooksort_UpdateDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbcsort )
    idvbcsort_UpdateDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbtsort )
    idvbtsort_UpdateDigitalPreset( svcdat );
  else if ( ret==isortroute_dvbclitesort )
    idvbclitesort_UpdateDigitalPreset( svcdat );
  else if ( ret==isortroute_norsort )
    inorsort_UpdateDigitalPreset( svcdat );
  else if ( ret==isortroute_apmeasort )
    idvbtapmeasort_UpdateDigitalPreset( svcdat );  
   else if ( ret==isortroute_hungarysort )
    idvbthungarysort_UpdateDigitalPreset( svcdat );  
  else if ( ret==isortroute_blizoosort )
    iblizoosort_UpdateDigitalPreset( svcdat );	
  else
    istubsort_UpdateDigitalPreset( svcdat );
}

Bool CHsvEuropeInstallation_mroute_Priv::isort_UpdatingLCNDuringUpdateInstallation( void ) {
  int ret = isortroute_GetCurrentActiveSortInterface();
  if ( ret==isortroute_italysort )
    return itasort_UpdatingLCNDuringUpdateInstallation( );
  else if ( ret==isortroute_dvbtlitesort )
    return idvbtlitesort_UpdatingLCNDuringUpdateInstallation( );
  else if ( ret==isortroute_finsort )
    return ifinsort_UpdatingLCNDuringUpdateInstallation( );
  else if ( ret==isortroute_dvbt2sort )
    return idbooksort_UpdatingLCNDuringUpdateInstallation( );
  else if ( ret==isortroute_dvbcsort )
    return idvbcsort_UpdatingLCNDuringUpdateInstallation( );
  else if ( ret==isortroute_dvbtsort )
    return idvbtsort_UpdatingLCNDuringUpdateInstallation( );
  else if ( ret==isortroute_dvbclitesort )
    return idvbclitesort_UpdatingLCNDuringUpdateInstallation( );
  else if ( ret==isortroute_norsort )
    return inorsort_UpdatingLCNDuringUpdateInstallation( );
  else if ( ret==isortroute_apmeasort )
    return idvbtapmeasort_UpdatingLCNDuringUpdateInstallation( );  
   else if ( ret==isortroute_hungarysort )
    return idvbthungarysort_UpdatingLCNDuringUpdateInstallation( ); 
  else if ( ret==isortroute_blizoosort )
    return iblizoosort_UpdatingLCNDuringUpdateInstallation( );	  
  else
    return 0;
}
