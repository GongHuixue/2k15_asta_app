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
 *          %name: hsveuins_mpow.c %
 *       %version: TVG_tv550r4dev1_5 %
 * %date_modified: Wed Nov 21 17:18:35 2007 %
 *    %derived_by: vijayan % 
 */

#include "_hsveuins_mpow.h"


void CHsvEuropeInstallation_mpow_Priv::pow_Init    ( void )
{
	impow_Init();
	hsvdvbtins_pow_Init();
	hsvdvbtmpegins_pow_Init();
	imfreqctlpow_Init();
	hsvprins_pow_Init();
	hsvdvbcins_pow_Init();
	icabpow_Init();
	iblizoopow_Init();
	impegpow_Init();
	ilitepow_Init();
	inorpow_Init();
	iitapow_Init();
	iconpow_Init();
	idbookconpow_Init();
	idbooksortpow_Init();
	idvbtsortpow_Init();
	hsvziggoins_pow_Init();
	ifinsortpow_Init();
	icamsortpow_Init();	
	idvbtapmeasortpow_Init();	
	idvbthungarysortpow_Init();
	svpaci_pow_Init();
	hsvacidec_pow_Init();
	hsvdvbcamins_pow_Init();
	hsvcanaldigitalins_pow_Init();
	
	
}
void CHsvEuropeInstallation_mpow_Priv::pow_TurnOn  ( void )
{
	impow_TurnOn();
	hsvdvbtins_pow_TurnOn();
	hsvdvbtmpegins_pow_TurnOn();
	imfreqctlpow_TurnOn();
	hsvprins_pow_TurnOn();
	hsvdvbcins_pow_TurnOn();
	icabpow_TurnOn();
	iblizoopow_TurnOn();
	impegpow_TurnOn();
	ilitepow_TurnOn();
	iitapow_TurnOn();
	iconpow_TurnOn();
	idbookconpow_TurnOn();
	idbooksortpow_TurnOn();
	idvbtsortpow_TurnOn();
	idvbtapmeasortpow_TurnOn();	
	idvbthungarysortpow_TurnOn();
	hsvziggoins_pow_TurnOn();
	ifinsortpow_TurnOn();
	icamsortpow_TurnOn();
	svpaci_pow_TurnOn();
	hsvacidec_pow_TurnOn();
	hsvdvbcamins_pow_TurnOn();
	hsvcanaldigitalins_pow_TurnOn();
}
void CHsvEuropeInstallation_mpow_Priv::pow_TurnOff ( void )
{
	impow_TurnOff();
	hsvdvbtins_pow_TurnOff();
	hsvdvbtmpegins_pow_TurnOff();
	imfreqctlpow_TurnOff();
	hsvprins_pow_TurnOff();
	hsvdvbcins_pow_TurnOff();
	icabpow_TurnOff();
	iblizoopow_TurnOff();
	impegpow_TurnOff();
	ilitepow_TurnOff();
	iitapow_TurnOff();
	iconpow_TurnOff();
	idbookconpow_TurnOff();
	idbooksortpow_TurnOff();
	idvbtsortpow_TurnOff();
	idvbtapmeasortpow_TurnOff();	
	idvbthungarysortpow_TurnOff();
	hsvziggoins_pow_TurnOff();
	ifinsortpow_TurnOff();
	icamsortpow_TurnOff();
	svpaci_pow_TurnOff();
	hsvacidec_pow_TurnOff();
	hsvdvbcamins_pow_TurnOff();
	hsvcanaldigitalins_pow_TurnOff();
}
