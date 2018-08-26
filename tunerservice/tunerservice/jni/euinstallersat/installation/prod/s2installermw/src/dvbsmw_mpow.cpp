
#include "_dvbsmw_mpow.h"


void CS2InstallerMw_mpow_Priv::pow_Init(void)
{
	hsvdvbsins_pow_Init();
	hsvsatfe_pow_Init();
	hsvdvbsdm_pow_Init();
	sathsvpgdat_pow_Init();
}

void CS2InstallerMw_mpow_Priv::pow_TurnOn(void)
{
	hsvdvbsins_pow_TurnOn();
	hsvsatfe_pow_TurnOn();
	hsvdvbsdm_pow_TurnOn();
	sathsvpgdat_pow_TurnOn();
}

void CS2InstallerMw_mpow_Priv::pow_TurnOff(void)
{
	hsvdvbsins_pow_TurnOff();
	hsvsatfe_pow_TurnOff();
	hsvdvbsdm_pow_TurnOff();
	sathsvpgdat_pow_TurnOff();
}
