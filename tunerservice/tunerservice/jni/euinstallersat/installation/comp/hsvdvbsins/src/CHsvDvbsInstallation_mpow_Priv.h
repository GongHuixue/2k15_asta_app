#ifndef  _CHSVDVBSINSTALLATION_MPOW_PRIV_H
#define  _CHSVDVBSINSTALLATION_MPOW_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <CS2MwBase.h>
class CHsvDvbsInstallation_mpow_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_mpow_Priv::
#include "locals_mpow.h"

class CHsvDvbsInstallation_mpow_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_mpow_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mpow.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CHsvDvbsInstallation_mpow_Priv,pow);
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	idvbsetpow;
RequiresInterface<IHsvPower>	iminiprescanpow;
RequiresInterface<IHsvPower>	impackagepow;
RequiresInterface<IHsvPower>	ipackagepow;
RequiresInterface<IHsvPower>	ipow;
RequiresInterface<IHsvPower>	ipredefpow;
RequiresInterface<IHsvPower>	iprescanpow;
RequiresInterface<IHsvPower>	iremovesatpow;
RequiresInterface<IHsvPower>	isatipprescanpow;


public:
CHsvDvbsInstallation_mpow_Priv():i__pow(this)
{
pow	=	&i__pow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define idvbsetpow_iPresent() (idvbsetpow.Present())
#define idvbsetpow_Init()	idvbsetpow->Init()
#define idvbsetpow_TurnOn()	idvbsetpow->TurnOn()
#define idvbsetpow_TurnOff()	idvbsetpow->TurnOff()
#define iminiprescanpow_iPresent() (iminiprescanpow.Present())
#define iminiprescanpow_Init()	iminiprescanpow->Init()
#define iminiprescanpow_TurnOn()	iminiprescanpow->TurnOn()
#define iminiprescanpow_TurnOff()	iminiprescanpow->TurnOff()
#define impackagepow_iPresent() (impackagepow.Present())
#define impackagepow_Init()	impackagepow->Init()
#define impackagepow_TurnOn()	impackagepow->TurnOn()
#define impackagepow_TurnOff()	impackagepow->TurnOff()
#define ipackagepow_iPresent() (ipackagepow.Present())
#define ipackagepow_Init()	ipackagepow->Init()
#define ipackagepow_TurnOn()	ipackagepow->TurnOn()
#define ipackagepow_TurnOff()	ipackagepow->TurnOff()
#define ipow_iPresent() (ipow.Present())
#define ipow_Init()	ipow->Init()
#define ipow_TurnOn()	ipow->TurnOn()
#define ipow_TurnOff()	ipow->TurnOff()
#define ipredefpow_iPresent() (ipredefpow.Present())
#define ipredefpow_Init()	ipredefpow->Init()
#define ipredefpow_TurnOn()	ipredefpow->TurnOn()
#define ipredefpow_TurnOff()	ipredefpow->TurnOff()
#define iprescanpow_iPresent() (iprescanpow.Present())
#define iprescanpow_Init()	iprescanpow->Init()
#define iprescanpow_TurnOn()	iprescanpow->TurnOn()
#define iprescanpow_TurnOff()	iprescanpow->TurnOff()
#define iremovesatpow_iPresent() (iremovesatpow.Present())
#define iremovesatpow_Init()	iremovesatpow->Init()
#define iremovesatpow_TurnOn()	iremovesatpow->TurnOn()
#define iremovesatpow_TurnOff()	iremovesatpow->TurnOff()
#define isatipprescanpow_iPresent() (isatipprescanpow.Present())
#define isatipprescanpow_Init()	isatipprescanpow->Init()
#define isatipprescanpow_TurnOn()	isatipprescanpow->TurnOn()
#define isatipprescanpow_TurnOff()	isatipprescanpow->TurnOff()
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

