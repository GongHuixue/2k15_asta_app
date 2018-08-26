/**********************************************************************
 *
 *  Copyright(C) 2004 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *
 *
*	C Source:		hsvdvbsins_mpow.c
*	Instance:		
*	Description:	
*	%created_by:	  anuma %
*	%date_created:	  Fri May 10 18:12:35 2013 %
*
**********************************************************************/


#include "_hsvdvbsins_mpow.h"

TRACESYMBOL(m, "s2/installation/hsvdvbsins_mpow")



void CHsvDvbsInstallation_mpow_Priv::pow_Init()
{
    ipow_Init();
	idvbsetpow_Init();
	iprescanpow_Init();
	impackagepow_Init();
	iremovesatpow_Init();
	ipackagepow_Init();
	iminiprescanpow_Init();
	ipredefpow_Init();
	isatipprescanpow_Init();
}

void CHsvDvbsInstallation_mpow_Priv::pow_TurnOn()
{
	ipow_TurnOn();
	idvbsetpow_TurnOn();
	iprescanpow_TurnOn();
	impackagepow_TurnOn();
	iremovesatpow_TurnOn();
	ipackagepow_TurnOn();
	iminiprescanpow_TurnOn();
	ipredefpow_TurnOn();
	isatipprescanpow_TurnOn();
}

void CHsvDvbsInstallation_mpow_Priv::pow_TurnOff()
{
	ipow_TurnOff();
	idvbsetpow_TurnOff();
	iprescanpow_TurnOff();
	impackagepow_TurnOff();
	iremovesatpow_TurnOff();
	ipackagepow_TurnOff();
	iminiprescanpow_TurnOff();
	ipredefpow_TurnOff();
	isatipprescanpow_TurnOff();
}
