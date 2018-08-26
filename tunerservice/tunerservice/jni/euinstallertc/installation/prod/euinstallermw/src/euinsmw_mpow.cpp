#include "_euinsmw_mpow.h"



void CEuInstallerMw_mpow_Priv::pow_Init    ( void )
{
	hsveuins_pow_Init();
	hsvfe_pow_Init();
       hsvpgdat_pow_Init();
	   hsvdvbsdm_pow_Init();
	   txtpow_Init();
}
void CEuInstallerMw_mpow_Priv::pow_TurnOn  ( void )
{
	hsveuins_pow_TurnOn();
	hsvfe_pow_TurnOn();
       hsvpgdat_pow_TurnOn();
	   hsvdvbsdm_pow_TurnOn();
	   txtpow_TurnOn();
}
void CEuInstallerMw_mpow_Priv::pow_TurnOff ( void )
{
	hsveuins_pow_TurnOff();
	hsvfe_pow_TurnOff();
       hsvpgdat_pow_TurnOff();
	   hsvdvbsdm_pow_TurnOff();
	   txtpow_TurnOff();
}

