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
 *          %name: hsveuins_macids.c %
 *       %version: TVG_tv550r4dev1 %
 * %date_modified: Tue Apr 18 10:49:07 2006 %
 *    %derived_by: lakshminb %
 */
 
#include "_hsveuins_mstub.h"


Bool CHsvEuropeInstallation_mstub_Priv::hsvprins_pgdatcni_Add(Nat16 cni,int presetId)
{
	return FALSE;
}
Bool CHsvEuropeInstallation_mstub_Priv::hsvprins_pgdatcni_Remove(int presetId)
{
	return FALSE;
}
Bool CHsvEuropeInstallation_mstub_Priv::hsvprins_pgdatcni_IsCniPresent(Nat16 cni)
{
	return FALSE;
}
int CHsvEuropeInstallation_mstub_Priv::hsvprins_pgdatcni_GetPreset(Nat16 cni)
{
	return 0;
}
Nat16 CHsvEuropeInstallation_mstub_Priv::hsvprins_pgdatcni_GetCni(int pr)
{
	return 0;
}
void CHsvEuropeInstallation_mstub_Priv::hsvprins_pgdatcni_ClearCNIList(void)
{
	return;
}
 
