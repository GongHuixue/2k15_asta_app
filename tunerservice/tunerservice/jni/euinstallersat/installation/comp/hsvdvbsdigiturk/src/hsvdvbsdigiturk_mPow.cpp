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
 *	C Source:		hsvdvbsdigiturk_mPow.c
 *	Instance:		blr81mgr_1
 *	Description:	
 *	%created_by:	dnilanjan %
 *	%date_created:	Tue Apr 23 14:21:12 2013 %
 *
**********************************************************************/

#include "_hsvdvbsdigiturk_mPow.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsdigiturk_mPow")



void CHsvDvbsDigiTurk_mPow_Priv::pow_Init ()
{
	iscanpow_Init ();
	iacqpow_Init ();
	isortpow_Init ();
}

void CHsvDvbsDigiTurk_mPow_Priv::pow_TurnOn ()
{
	iscanpow_TurnOn ();
	iacqpow_TurnOn ();
	isortpow_TurnOn ();
}

void CHsvDvbsDigiTurk_mPow_Priv::pow_TurnOff ()
{
	iscanpow_TurnOff ();
	iacqpow_TurnOff ();
	isortpow_TurnOff ();
}
