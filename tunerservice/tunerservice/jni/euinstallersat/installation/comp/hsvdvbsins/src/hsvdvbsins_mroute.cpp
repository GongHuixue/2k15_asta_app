/**********************************************************************
 *  Copyright(C) 2004 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *	C Source:		hsvdvbsins_mroute.c
 *	Instance:		
 *	Description:	
 *	%created_by:	  anuma %
 *	%date_created:	  Fri May 10 18:07:16 2013 %
 *
**********************************************************************/
#include "_hsvdvbsins_mroute.h"

TRACESYMBOL(m, "s2/installation/hsvdvbsins_mroute")


/****************************************************************************
 * External functions
 ****************************************************************************/



int CHsvDvbsInstallation_mroute_Priv::ipackageroute_GetCurrentActivePackage (void)
{
	int	RetVal = ipackageroute_generic;
	Nat32 PackageIndex = 0;
	Nat16 PackageGroupId = 0;
	Bool IsPackage;
	/* Right now only generic framework is supported. As and when new packages are added
		corresponding package index to be identified and the selection of corresponding
		package module should be done here */
	if ((err_Ok == 	pins_GetUserPackageIndex(&PackageIndex, &IsPackage)) && (IsPackage == TRUE))
	{
		if (err_Ok == ipackage_GetPackageGroupId (PackageIndex, &PackageGroupId))
		{
			RetVal = PackageGroupId;
		}
	}
	return RetVal;
}

void CHsvDvbsInstallation_mroute_Priv::ipackagepow_Init(void)
{
	hsvdvbsgeneric_pow_Init();
	hsvdvbsm7_pow_Init();
	hsvdvbscanal_pow_Init();
	hsvdvbsn_pow_Init();
	hsvdvbspol_pow_Init();
	hsvdvbsrussia_pow_Init();
	hsvdvbsdigiturk_pow_Init();
	hsvdvbsfransat_pow_Init();
	hsvdvbsopprofile_pow_Init();
	hsvdvbsfreesat_pow->Init();
	hsvdvbsastra_pow_Init();
	hsvdvbstricolor_pow_Init();
}

void CHsvDvbsInstallation_mroute_Priv::ipackagepow_TurnOn(void)
{
	hsvdvbsgeneric_pow_TurnOn();
	hsvdvbsm7_pow_TurnOn();
	hsvdvbscanal_pow_TurnOn();
	hsvdvbsn_pow_TurnOn();
	hsvdvbspol_pow_TurnOn();
	hsvdvbsrussia_pow_TurnOn();
	hsvdvbsdigiturk_pow_TurnOn();
	hsvdvbsfransat_pow_TurnOn();
	hsvdvbsopprofile_pow_TurnOn();
	hsvdvbsfreesat_pow->TurnOn();
	hsvdvbsastra_pow_TurnOn();
	hsvdvbstricolor_pow_TurnOn();
}

void CHsvDvbsInstallation_mroute_Priv::ipackagepow_TurnOff()
{
	hsvdvbsgeneric_pow_TurnOff();
	hsvdvbsm7_pow_TurnOff();
	hsvdvbscanal_pow_TurnOff();
	hsvdvbsn_pow_TurnOff();
	hsvdvbspol_pow_TurnOff();
	hsvdvbsrussia_pow_TurnOff();
	hsvdvbsdigiturk_pow_TurnOff();
	hsvdvbsfransat_pow_TurnOff();
	hsvdvbsopprofile_pow_TurnOff();
	hsvdvbsfreesat_pow->TurnOff();
	hsvdvbsastra_pow_TurnOff();
	hsvdvbstricolor_pow_TurnOff();
}


int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetAttribute( int Mode, int AttributeId ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetAttribute( Mode, AttributeId );
 else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetAttribute( Mode, AttributeId );
  else if (ActivePackage==0xb)
   	return hsvdvbsfreesat_ins->GetAttribute( Mode, AttributeId );
  else if ( ActivePackage==0xc )
	return hsvdvbstricolor_ins_GetAttribute( Mode, AttributeId );
  else
    return hsvdvbsgeneric_ins_GetAttribute( Mode, AttributeId );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetCurrentInstallationState( int * mode, int * state ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetCurrentInstallationState( mode, state );
  else if (ActivePackage==0xb)
   	return hsvdvbsfreesat_ins->GetCurrentInstallationState( mode, state );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetCurrentInstallationState( mode, state );
  else
    return hsvdvbsgeneric_ins_GetCurrentInstallationState( mode, state );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetNumberOfDigitalChannelsAdded( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetNumberOfDigitalChannelsAdded( );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->GetNumberOfDigitalChannelsAdded( );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetNumberOfDigitalChannelsAdded( ); 
  else
    return hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsAdded( );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetNumberOfDigitalChannelsMoved( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetNumberOfDigitalChannelsMoved( );
  else if (ActivePackage==0xb)
   	return hsvdvbsfreesat_ins->GetNumberOfDigitalChannelsMoved( );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetNumberOfDigitalChannelsMoved( );
  else
    return hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsMoved( );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetNumberOfDigitalChannelsRemoved( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetNumberOfDigitalChannelsRemoved( );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetNumberOfDigitalChannelsRemoved( );
  else if (ActivePackage==0xb)
	return hsvdvbsfreesat_ins->GetNumberOfDigitalChannelsRemoved( );
   else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetNumberOfDigitalChannelsRemoved( );
  else
    return hsvdvbsgeneric_ins_GetNumberOfDigitalChannelsRemoved( );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetNumberofRadioChannelsFound( int Mode, int Lnb ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->GetNumberofRadioChannelsFound( Mode, Lnb );
   else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
  else
    return hsvdvbsgeneric_ins_GetNumberofRadioChannelsFound( Mode, Lnb );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetNumberofRadioChannelsRemoved( int Mode, int Lnb ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
 else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
  else
    return hsvdvbsgeneric_ins_GetNumberofRadioChannelsRemoved( Mode, Lnb );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetNumberOfTvChannelsFound( int Mode, int Lnb ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->GetNumberOfTvChannelsFound( Mode, Lnb );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
  else
    return hsvdvbsgeneric_ins_GetNumberOfTvChannelsFound( Mode, Lnb );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetNumberOfTvChannelsRemoved( int Mode, int Lnb ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
 else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->GetNumberOfTvChannelsRemoved( Mode, Lnb );
   else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
  else
    return hsvdvbsgeneric_ins_GetNumberOfTvChannelsRemoved( Mode, Lnb );
}

int CHsvDvbsInstallation_mroute_Priv::ipackageins_GetScanProgressStatus( int Mode ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_GetScanProgressStatus( Mode );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_GetScanProgressStatus( Mode );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->GetScanProgressStatus( Mode );
   else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_GetScanProgressStatus( Mode );
  else
    return hsvdvbsgeneric_ins_GetScanProgressStatus( Mode );
}

void CHsvDvbsInstallation_mroute_Priv::ipackageins_GetSIDetails( HsvSDMSIDataValues * SiValues ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsrussia_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0x3 )
    hsvdvbspol_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0x5 )
    hsvdvbsdigiturk_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0x1 )
    hsvdvbsm7_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0x6 )
    hsvdvbsn_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0x2 )
    hsvdvbscanal_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_ins_GetSIDetails( SiValues );
  else if ( ActivePackage==0x9 )
    hsvdvbsastra_ins_GetSIDetails( SiValues );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->GetSIDetails( SiValues );
  else if ( ActivePackage==0xc )
    hsvdvbstricolor_ins_GetSIDetails( SiValues );
  else
    hsvdvbsgeneric_ins_GetSIDetails( SiValues );
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_LoadManualInstallationDefaultValues( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_LoadManualInstallationDefaultValues( );
  else if (ActivePackage==0xb)
   return hsvdvbsfreesat_ins->LoadManualInstallationDefaultValues( );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_LoadManualInstallationDefaultValues( );
  else
    return hsvdvbsgeneric_ins_LoadManualInstallationDefaultValues( );
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)
{
	TraceNotice(m,"%s Entry postcodelen %d postcode:%s",__FUNCTION__,PostcodeLen,Postcode);
	FResult retValue = err_BadParameter;
	int ActivePackage = ipackageroute_GetCurrentActivePackage();

	if ( ActivePackage==0xb )
	{
		retValue = hsvdvbsfreesat_settings->SetPostcode(PostcodeLen, Postcode);
	}
		TraceNotice(m,"%s Exit retValue %d",__FUNCTION__,retValue);
	return retValue;
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_StartTricolorRegionParsing ()
{
	  hsvdvbstricolor_ins_StartTricolorRegionParsing();		
	  return err_Ok;
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_SetTricolorRegionIndex(int index)
{
	  TraceNotice (m,"SetTricolorRegionIndex Entry");
	  hsvdvbstricolor_ins_SetTricolorRegionIndex(index);
	  return err_Ok;
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_GetTricolorRegionNames (Nat16 **names, int *len)
{
	  TraceNotice(m,"ipackageins_GetTricolorRegionNames");
	  hsvdvbstricolor_ins_GetTricolorRegionNames(names,len);
	  
	  //TraceNotice(m,"region name %s",names[0]);
	  
	  return err_Ok;
}

Bool CHsvDvbsInstallation_mroute_Priv::ipackageins_SetManualInstallationAttributes( int AttributeId, int Value ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_SetManualInstallationAttributes( AttributeId, Value );
 else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_SetManualInstallationAttributes( AttributeId, Value );
  else if (ActivePackage==0xb)
  	return hsvdvbsfreesat_ins->SetManualInstallationAttributes( AttributeId, Value );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_SetManualInstallationAttributes( AttributeId, Value );
  else
    return hsvdvbsgeneric_ins_SetManualInstallationAttributes( AttributeId, Value );
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_StartInstallation( int Source, int Lnb, int Mode ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_StartInstallation (Source, Lnb, Mode);
 else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_StartInstallation (Source, Lnb, Mode);
  else if (ActivePackage==0xb)
  	return hsvdvbsfreesat_ins->StartInstallation( Source, Lnb, Mode );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_StartInstallation (Source, Lnb, Mode);
  else
    return hsvdvbsgeneric_ins_StartInstallation( Source, Lnb, Mode );
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_StopInstallation( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_StopInstallation( );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_StopInstallation( );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_StopInstallation( );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_StopInstallation( );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_StopInstallation( );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_StopInstallation( );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_StopInstallation( );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_StopInstallation( );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_StopInstallation ();
 else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_StopInstallation ();
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->StopInstallation( );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_StopInstallation ();
  else
    return hsvdvbsgeneric_ins_StopInstallation( );
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_StoreManualInstallationValues( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_StoreManualInstallationValues( );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_StoreManualInstallationValues( );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->StoreManualInstallationValues( );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_StoreManualInstallationValues( );
  else
    return hsvdvbsgeneric_ins_StoreManualInstallationValues( );
}

FResult CHsvDvbsInstallation_mroute_Priv::ipackageins_WriteBarkerMuxData( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    return hsvdvbsrussia_ins_WriteBarkerMuxData( );
  else if ( ActivePackage==0x3 )
    return hsvdvbspol_ins_WriteBarkerMuxData();
  else if ( ActivePackage==0x7 )
    return hsvdvbsfransat_ins_WriteBarkerMuxData( );
  else if ( ActivePackage==0x5 )
    return hsvdvbsdigiturk_ins_WriteBarkerMuxData( );
  else if ( ActivePackage==0x1 )
    return hsvdvbsm7_ins_WriteBarkerMuxData( );
  else if ( ActivePackage==0xFFFFFFFF )
    return hsvdvbsgeneric_ins_WriteBarkerMuxData( );
  else if ( ActivePackage==0x6 )
    return hsvdvbsn_ins_WriteBarkerMuxData( );
  else if ( ActivePackage==0x2 )
    return hsvdvbscanal_ins_WriteBarkerMuxData( );
  else if ( ActivePackage==0x8 )
    return hsvdvbsopprofile_ins_WriteBarkerMuxData( );
  else if ( ActivePackage==0x9 )
    return hsvdvbsastra_ins_WriteBarkerMuxData( );
  else if (ActivePackage==0xb)
    return hsvdvbsfreesat_ins->WriteBarkerMuxData( );
  else if ( ActivePackage==0xc )
    return hsvdvbstricolor_ins_WriteBarkerMuxData( );
  else
    return hsvdvbsgeneric_ins_WriteBarkerMuxData( );
}
/* interface ipackagectrlN : IHsvSdmControlNotifyEx */

void CHsvDvbsInstallation_mroute_Priv::ipackagectrlN_OnEvent( HsvDemux dmx, int eventid, int value ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsrussia_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x3 )
    hsvdvbspol_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x5 )
    hsvdvbsdigiturk_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x1 )
    hsvdvbsm7_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x6 )
    hsvdvbsn_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x2 )
    hsvdvbscanal_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x9 )
    hsvdvbsastra_ctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_ctrlN_OnEvent( dmx, eventid, value );
  else if (ActivePackage==0xb)
  	{
		TraceNotice(m,"Active Package : %d eventid %d value %d",ActivePackage,eventid,value);
		hsvdvbsfreesat_ctrlN->OnEvent( dmx, eventid, value );
	}
  else if ( ActivePackage==0xc )
    hsvdvbstricolor_ctrlN_OnEvent( dmx, eventid, value );
  else
    hsvdvbsgeneric_ctrlN_OnEvent( dmx, eventid, value );
}
/* interface ipackageplfApidvbsN : IHsvSatelliteFrontEndNotify */

void CHsvDvbsInstallation_mroute_Priv::ipackageplfApidvbsN_OnBlindScanEnd( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsrussia_plfApidvbsN_OnBlindScanEnd( );
  else if ( ActivePackage==0x3 )
    hsvdvbspol_plfApidvbsN_OnBlindScanEnd( );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_plfApidvbsN_OnBlindScanEnd( );
  else if ( ActivePackage==0x5 )
    hsvdvbsdigiturk_plfApidvbsN_OnBlindScanEnd( );
  else if ( ActivePackage==0x1 )
    hsvdvbsm7_plfApidvbsN_OnBlindScanEnd( );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_plfApidvbsN_OnBlindScanEnd( );
  else if ( ActivePackage==0x6 )
    hsvdvbsn_plfApidvbsN_OnBlindScanEnd( );
  else if ( ActivePackage==0x2 )
    hsvdvbscanal_plfApidvbsN_OnBlindScanEnd( );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_plfApidvbsN_OnBlindScanEnd( );
 else if ( ActivePackage==0x9 )
    hsvdvbsastra_plfApidvbsN_OnBlindScanEnd( );
  else if (ActivePackage==0xb)
    hsvdvbsfreesat_plfApidvbsN->OnBlindScanEnd( );
  else if ( ActivePackage==0xc )
    hsvdvbstricolor_plfApidvbsN_OnBlindScanEnd( );
  else
    hsvdvbsgeneric_plfApidvbsN_OnBlindScanEnd( );
}

void CHsvDvbsInstallation_mroute_Priv::ipackageplfApidvbsN_OnLockChanged( Bool LockState ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsrussia_plfApidvbsN_OnLockChanged( LockState );
  else if ( ActivePackage==0x3 )
    hsvdvbspol_plfApidvbsN_OnLockChanged( LockState );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_plfApidvbsN_OnLockChanged( LockState );
  else if ( ActivePackage==0x5 )
    hsvdvbsdigiturk_plfApidvbsN_OnLockChanged( LockState );
  else if ( ActivePackage==0x1 )
    hsvdvbsm7_plfApidvbsN_OnLockChanged( LockState );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_plfApidvbsN_OnLockChanged( LockState );
  else if ( ActivePackage==0x6 )
    hsvdvbsn_plfApidvbsN_OnLockChanged( LockState );
  else if ( ActivePackage==0x2 )
    hsvdvbscanal_plfApidvbsN_OnLockChanged( LockState );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_plfApidvbsN_OnLockChanged( LockState );
 else if ( ActivePackage==0x9 )
    hsvdvbsastra_plfApidvbsN_OnLockChanged( LockState );
  else if (ActivePackage==0xb)
    hsvdvbsfreesat_plfApidvbsN->OnLockChanged( LockState );
  else if ( ActivePackage==0xc )
    hsvdvbstricolor_plfApidvbsN_OnLockChanged( LockState );
  else
    hsvdvbsgeneric_plfApidvbsN_OnLockChanged( LockState );
}
/* interface ipackagesort : IHsvSorting */

void CHsvDvbsInstallation_mroute_Priv::ipackagesort_Sort( Nat32 PackageIndex ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsrussia_sort_Sort( PackageIndex );
  else if ( ActivePackage==0x3 )
    hsvdvbspol_sort_Sort( PackageIndex );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_sort_Sort( PackageIndex );
  else if ( ActivePackage==0x5 )
    hsvdvbsdigiturk_sort_Sort( PackageIndex );
  else if ( ActivePackage==0x1 )
    hsvdvbsm7_sort_Sort( PackageIndex );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_sort_Sort( PackageIndex );
  else if ( ActivePackage==0x6 )
    hsvdvbsn_sort_Sort( PackageIndex );
  else if ( ActivePackage==0x2 )
    hsvdvbscanal_sort_Sort( PackageIndex );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_sort_Sort( PackageIndex );
 else if ( ActivePackage==0x9 )
    hsvdvbsastra_sort_Sort( PackageIndex );
  else if (ActivePackage==0xb)
    hsvdvbsfreesat_sort->Sort( PackageIndex );
  else if ( ActivePackage==0xc )
    hsvdvbstricolor_sort_Sort( PackageIndex );
  else
    hsvdvbsgeneric_sort_Sort( PackageIndex );
}
/* interface ibckInstall : IHsvSatelliteBackgroundInstallation */

void CHsvDvbsInstallation_mroute_Priv::ibckInstall_DisableBackgroundInstallation( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0x3 )
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0x5 )
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0x1 )
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0x6 )
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0x2 )
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0x8 )
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
 else if ( ActivePackage==0x9 )
    hsvdvbsastra_bckInstall_DisableBackgroundInstallation( );
  else if ( ActivePackage==0xb )
    hsvdvbsfreesat_ibckInstall->DisableBackgroundInstallation( );
  else
    hsvdvbsgeneric_bckInstall_DisableBackgroundInstallation( );
}

void CHsvDvbsInstallation_mroute_Priv::ibckInstall_EnableBackgroundInstallation( void ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0x3 )
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0x5 )
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0x1 )
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0x6 )
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0x2 )
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0x8 )
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
 else if ( ActivePackage==0x9 )
    hsvdvbsastra_bckInstall_EnableBackgroundInstallation( );
  else if ( ActivePackage==0xb )
    hsvdvbsfreesat_ibckInstall->EnableBackgroundInstallation( );
  else
    hsvdvbsgeneric_bckInstall_EnableBackgroundInstallation( );
}
/* interface ibckctrlN : IHsvSdmControlNotifyEx */

void CHsvDvbsInstallation_mroute_Priv::ibckctrlN_OnEvent( HsvDemux dmx, int eventid, int value ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x3 )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x5 )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x1 )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x6 )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x2 )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x8 )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else if ( ActivePackage==0x9 )
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
  else
    hsvdvbsgeneric_bckctrlN_OnEvent( dmx, eventid, value );
}
/* interface istrapiN : IHsvStreamNotify */

void CHsvDvbsInstallation_mroute_Priv::istrapiN_OnAdded( HsvDestination dest, int spid, int key1, int key2, int key3 ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x3 )
    hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x5 )
    hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x1 )
    hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x6 )
    hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x2 )
    hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_strapiN_OnAdded( dest, spid, key1, key2, key3 );
	else if ( ActivePackage==0x9 )
    hsvdvbsastra_strapiN_OnAdded( dest, spid, key1, key2, key3 );
   else if ( ActivePackage==0xb )
    hsvdvbsfreesat_strapiN->OnAdded( dest, spid, key1, key2, key3 );
   else if ( ActivePackage==0xc )
  hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
  else
    hsvdvbsgeneric_strapiN_OnAdded( dest, spid, key1, key2, key3 );
}

void CHsvDvbsInstallation_mroute_Priv::istrapiN_OnChanged( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0x3 )
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0x5 )
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0x1 )
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0x6 )
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0x2 )
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
	else if ( ActivePackage==0x9 )
    hsvdvbsastra_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0xb )
	hsvdvbsfreesat_strapiN->OnChanged( dest, spid, key1, key2, key3, eventid );
  else if ( ActivePackage==0xc )
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
  else
    hsvdvbsgeneric_strapiN_OnChanged( dest, spid, key1, key2, key3, eventid );
}

void CHsvDvbsInstallation_mroute_Priv::istrapiN_OnCompleted( HsvDestination dest, int spid ) {
    
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0x3 )
    hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0x5 )
    hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0x1 )
    hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0x6 )
    hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0x2 )
	hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_strapiN_OnCompleted( dest, spid );
	else if ( ActivePackage==0x9 )
    hsvdvbsastra_strapiN_OnCompleted( dest, spid );
  else if ( ActivePackage==0xb )
    hsvdvbsfreesat_strapiN->OnCompleted( dest, spid );
  else if ( ActivePackage==0xc )
    hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
  else
    hsvdvbsgeneric_strapiN_OnCompleted( dest, spid );
}

void CHsvDvbsInstallation_mroute_Priv::istrapiN_OnRemoved( HsvDestination dest, int spid, int key1, int key2, int key3 ) {
  int ActivePackage = ipackageroute_GetCurrentActivePackage();
  if ( ActivePackage==0x4 )
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x3 )
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x7 )
    hsvdvbsfransat_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x5 )
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x1 )
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0xFFFFFFFF )
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x6 )
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x2 )
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x8 )
    hsvdvbsopprofile_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0x9 )
    hsvdvbsastra_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0xb )
	hsvdvbsfreesat_strapiN->OnRemoved( dest, spid, key1, key2, key3 );
  else if ( ActivePackage==0xc )
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
  else
    hsvdvbsgeneric_strapiN_OnRemoved( dest, spid, key1, key2, key3 );
}


void CHsvDvbsInstallation_mroute_Priv::ipackageopinsN_OnOpSearchStatus (Op_ProfileSearchStatus opStatus)
{
    TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    hsvdvbsopprofile_opinsN_OnOpSearchStatus(opStatus);
}

void CHsvDvbsInstallation_mroute_Priv::ipackageopinsN_OnOpStatusInfo(Op_ProfileStatusInfo StatusInfo)
{
     TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    hsvdvbsopprofile_opinsN_OnOpStatusInfo(StatusInfo);
}

void CHsvDvbsInstallation_mroute_Priv::ipackageopinsN_OnOpNIT(Op_ProfileNitData nitData)
{
     TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    hsvdvbsopprofile_opinsN_OnOpNIT(nitData);
}

void CHsvDvbsInstallation_mroute_Priv::ipackageopinsN_OnOpTune(Op_ProfileTuneData tuneData)
{
     TraceNotice(m, "%s %d", __FUNCTION__, __LINE__);
    hsvdvbsopprofile_opinsN_OnOpTune(tuneData);
}

