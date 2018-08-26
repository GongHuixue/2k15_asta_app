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
 *          %name: svpaci_m.c %
 *       %version: TVG_Fusion_2 %
 * %date_modified: Wed Oct 11 17:30:17 2006 %
 *    %derived_by: lakshminb %
 */
 
#include "_svpaci_mdiv.h"


int CSvcPaci_mdiv_Priv::adiv_MaxTunPreset ()
{
	return 99;
}

int CSvcPaci_mdiv_Priv::adiv_MinTunPreset ()
{
	return 0;
}

int CSvcPaci_mdiv_Priv::adiv_AciAcquisitionTimeoutTime ()
{
	return 120;
}

int CSvcPaci_mdiv_Priv::adiv_RestorePageAcqTimeoutTime ()
{
	return 120;
}

int CSvcPaci_mdiv_Priv::adiv_MultipageDisplayTimeoutTime ()
{
	return 60;
}

int CSvcPaci_mdiv_Priv::adiv_AciTxtHdrReqDelay ()
{

	return 5000;
}

int CSvcPaci_mdiv_Priv::adiv_TunNotifyTimeout ()
{
	return 2000;
}
