#ifndef  _CS2INSTALLERMW_MPOW_PRIV_H
#define  _CS2INSTALLERMW_MPOW_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <CS2MwBase.h>
class CS2InstallerMw_mpow_Priv;
#define CLASSSCOPE CS2InstallerMw_mpow_Priv::
#include "locals_mpow.h"

class CS2InstallerMw_mpow_Priv : public CS2MwBase
{
public:
virtual ~CS2InstallerMw_mpow_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mpow.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CS2InstallerMw_mpow_Priv,pow);
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	hsvdvbsdm_pow;
RequiresInterface<IHsvPower>	hsvdvbsins_pow;
RequiresInterface<IHsvPower>	hsvsatfe_pow;
RequiresInterface<IHsvPower>	sathsvpgdat_pow;

public:
CS2InstallerMw_mpow_Priv():i__pow(this)
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
#define hsvdvbsins_pow_iPresent() (hsvdvbsins_pow.Present())
#define hsvdvbsins_pow_Init()	hsvdvbsins_pow->Init()
#define hsvdvbsins_pow_TurnOn()	hsvdvbsins_pow->TurnOn()
#define hsvdvbsins_pow_TurnOff()	hsvdvbsins_pow->TurnOff()
#define hsvsatfe_pow_iPresent() (hsvsatfe_pow.Present())
#define hsvsatfe_pow_Init()	hsvsatfe_pow->Init()
#define hsvsatfe_pow_TurnOn()	hsvsatfe_pow->TurnOn()
#define hsvsatfe_pow_TurnOff()	hsvsatfe_pow->TurnOff()
#define sathsvpgdat_pow_iPresent() (sathsvpgdat_pow.Present())
#define sathsvpgdat_pow_Init()	sathsvpgdat_pow->Init()
#define sathsvpgdat_pow_TurnOn()	sathsvpgdat_pow->TurnOn()
#define sathsvpgdat_pow_TurnOff()	sathsvpgdat_pow->TurnOff()
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

