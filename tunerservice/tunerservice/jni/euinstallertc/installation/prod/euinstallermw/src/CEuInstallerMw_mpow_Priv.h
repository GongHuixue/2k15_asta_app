#ifndef  _CEUINSTALLERMW_MPOW_PRIV_H
#define  _CEUINSTALLERMW_MPOW_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <CTCMwBase.h>
class CEuInstallerMw_mpow_Priv;
#define CLASSSCOPE CEuInstallerMw_mpow_Priv::
#include "locals_mpow.h"

class CEuInstallerMw_mpow_Priv : public CTCMwBase
{
public:
virtual ~CEuInstallerMw_mpow_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mpow.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CEuInstallerMw_mpow_Priv,pow);
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	hsvdvbsdm_pow;
RequiresInterface<IHsvPower>	hsveuins_pow;
RequiresInterface<IHsvPower>	hsvfe_pow;
RequiresInterface<IHsvPower>	hsvpgdat_pow;
RequiresInterface<IHsvPower>	txtpow;
public:
CEuInstallerMw_mpow_Priv():i__pow(this)
{
pow	=	&i__pow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define hsvdvbsdm_pow_iPresent() (hsvdvbsdm_pow.Present())
#define hsvdvbsdm_pow_Init()	hsvdvbsdm_pow->Init()
#define hsvdvbsdm_pow_TurnOn()	hsvdvbsdm_pow->TurnOn()
#define hsvdvbsdm_pow_TurnOff()	hsvdvbsdm_pow->TurnOff()
#define hsveuins_pow_iPresent() (hsveuins_pow.Present())
#define hsveuins_pow_Init()	hsveuins_pow->Init()
#define hsveuins_pow_TurnOn()	hsveuins_pow->TurnOn()
#define hsveuins_pow_TurnOff()	hsveuins_pow->TurnOff()
#define hsvfe_pow_iPresent() (hsvfe_pow.Present())
#define hsvfe_pow_Init()	hsvfe_pow->Init()
#define hsvfe_pow_TurnOn()	hsvfe_pow->TurnOn()
#define hsvfe_pow_TurnOff()	hsvfe_pow->TurnOff()
#define hsvpgdat_pow_iPresent() (hsvpgdat_pow.Present())
#define hsvpgdat_pow_Init()	hsvpgdat_pow->Init()
#define hsvpgdat_pow_TurnOn()	hsvpgdat_pow->TurnOn()
#define hsvpgdat_pow_TurnOff()	hsvpgdat_pow->TurnOff()
#define txtpow_Init()	txtpow->Init()
#define txtpow_TurnOn()	txtpow->TurnOn()
#define txtpow_TurnOff()	txtpow->TurnOff()
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mpow.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

