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
 
#include "_hsveuins_mdiv.h"


int CHsvEuropeInstallation_mdiv_Priv::ieuconfig_GetAutoStoreMode(void)
{
	int retval;
	if((sysset_GetSystemCountry() == icountid_CountryNetherlands ) && ( pins_GetAttribute(pins_InstallationModeAutomatic, pins_AttributeNetworkOperator) == pins_UPC ))
	{
		retval = 0x1;
	}
	else
	{
		/* ANEESH: HACK: Changing this value to 0x00 untill ACI support comes */
		retval = 0x03;
	}
	return retval;
}

int CHsvEuropeInstallation_mdiv_Priv::ieuconfig_GetMedium(void)
{
	return 0;
}
void CHsvEuropeInstallation_mdiv_Priv::ieuconfig_GetBreakOutSource(HsvSource * Source)
{
}
void CHsvEuropeInstallation_mdiv_Priv::ieuconfig_GetBreakOutChannel(HsvChannel * ChannelNo)
{
}
HsvSource CHsvEuropeInstallation_mdiv_Priv::ieuconfig_GetDefaultSpdifAssociation(HsvSource SpdifSource)
{
	return (HsvSource)0;
}

int CHsvEuropeInstallation_mdiv_Priv::svpaci_div_MaxTunPreset ()
{
	return 99;
}

int CHsvEuropeInstallation_mdiv_Priv::svpaci_div_MinTunPreset ()
{
	return 0;
}

int CHsvEuropeInstallation_mdiv_Priv::svpaci_div_AciAcquisitionTimeoutTime ()
{
	return 120;
}

int CHsvEuropeInstallation_mdiv_Priv::svpaci_div_RestorePageAcqTimeoutTime ()
{
	return 120;
}

int CHsvEuropeInstallation_mdiv_Priv::svpaci_div_MultipageDisplayTimeoutTime ()
{
	return 60;
}

int CHsvEuropeInstallation_mdiv_Priv::svpaci_div_AciTxtHdrReqDelay ()
{
	return 5000;
}

int CHsvEuropeInstallation_mdiv_Priv::svpaci_div_TunNotifyTimeout ()
{
	return 2000;
}

char* CHsvEuropeInstallation_mdiv_Priv::svpats_div_GetDefaultPresetName (void)
{
	return "------";
}
