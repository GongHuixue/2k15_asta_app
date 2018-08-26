#ifndef  _CHSVEUROPEINSTALLATION_MPOW_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MPOW_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <ISvPower.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_mpow_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_mpow_Priv::
#include "locals_mpow.h"

class CHsvEuropeInstallation_mpow_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_mpow_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mpow.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CHsvEuropeInstallation_mpow_Priv,pow);
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	hsvacidec_pow;
RequiresInterface<IHsvPower>	hsvdvbcamins_pow;
RequiresInterface<IHsvPower>	hsvdvbcins_pow;
RequiresInterface<IHsvPower>	hsvdvbtins_pow;
RequiresInterface<IHsvPower>	hsvdvbtmpegins_pow;
RequiresInterface<IHsvPower>	hsvprins_pow;
RequiresInterface<IHsvPower>	hsvziggoins_pow;
RequiresInterface<IHsvPower>	icabpow;
RequiresInterface<IHsvPower>	iblizoopow;
RequiresInterface<IHsvPower>	icamsortpow;
RequiresInterface<IHsvPower>	iconpow;
RequiresInterface<IHsvPower>	idbookconpow;
RequiresInterface<IHsvPower>	idbooksortpow;
RequiresInterface<IHsvPower>	idvbtsortpow;
RequiresInterface<IHsvPower>	ifinsortpow;
RequiresInterface<IHsvPower>	iitapow;
RequiresInterface<IHsvPower>	ilitepow;
RequiresInterface<IHsvPower>	imfreqctlpow;
RequiresInterface<IHsvPower>	impegpow;
RequiresInterface<IHsvPower>	impow;
RequiresInterface<IHsvPower>	inorpow;
RequiresInterface<IHsvPower>	idvbtapmeasortpow;
RequiresInterface<IHsvPower>	idvbthungarysortpow;
RequiresInterface<ISvPower>	svpaci_pow;
RequiresInterface<IHsvPower>	hsvcanaldigitalins_pow;

public:
CHsvEuropeInstallation_mpow_Priv():i__pow(this)
{
pow	=	&i__pow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define hsvacidec_pow_iPresent() (hsvacidec_pow.Present())
#define hsvacidec_pow_Init()	hsvacidec_pow->Init()
#define hsvacidec_pow_TurnOn()	hsvacidec_pow->TurnOn()
#define hsvacidec_pow_TurnOff()	hsvacidec_pow->TurnOff()
#define hsvdvbcamins_pow_iPresent() (hsvdvbcamins_pow.Present())
#define hsvdvbcamins_pow_Init()	hsvdvbcamins_pow->Init()
#define hsvdvbcamins_pow_TurnOn()	hsvdvbcamins_pow->TurnOn()
#define hsvdvbcamins_pow_TurnOff()	hsvdvbcamins_pow->TurnOff()
#define hsvdvbcins_pow_iPresent() (hsvdvbcins_pow.Present())
#define hsvdvbcins_pow_Init()	hsvdvbcins_pow->Init()
#define hsvdvbcins_pow_TurnOn()	hsvdvbcins_pow->TurnOn()
#define hsvdvbcins_pow_TurnOff()	hsvdvbcins_pow->TurnOff()
#define hsvdvbtins_pow_iPresent() (hsvdvbtins_pow.Present())
#define hsvdvbtins_pow_Init()	hsvdvbtins_pow->Init()
#define hsvdvbtins_pow_TurnOn()	hsvdvbtins_pow->TurnOn()
#define hsvdvbtins_pow_TurnOff()	hsvdvbtins_pow->TurnOff()
#define hsvdvbtmpegins_pow_iPresent() (hsvdvbtmpegins_pow.Present())
#define hsvdvbtmpegins_pow_Init()	hsvdvbtmpegins_pow->Init()
#define hsvdvbtmpegins_pow_TurnOn()	hsvdvbtmpegins_pow->TurnOn()
#define hsvdvbtmpegins_pow_TurnOff()	hsvdvbtmpegins_pow->TurnOff()
#define hsvprins_pow_iPresent() (hsvprins_pow.Present())
#define hsvprins_pow_Init()	hsvprins_pow->Init()
#define hsvprins_pow_TurnOn()	hsvprins_pow->TurnOn()
#define hsvprins_pow_TurnOff()	hsvprins_pow->TurnOff()
#define hsvziggoins_pow_iPresent() (hsvziggoins_pow.Present())
#define hsvziggoins_pow_Init()	hsvziggoins_pow->Init()
#define hsvziggoins_pow_TurnOn()	hsvziggoins_pow->TurnOn()
#define hsvziggoins_pow_TurnOff()	hsvziggoins_pow->TurnOff()
#define hsvcanaldigitalins_pow_iPresent() (hsvcanaldigitalins_pow.Present())
#define hsvcanaldigitalins_pow_Init()	hsvcanaldigitalins_pow->Init()
#define hsvcanaldigitalins_pow_TurnOn()	hsvcanaldigitalins_pow->TurnOn()
#define hsvcanaldigitalins_pow_TurnOff()	hsvcanaldigitalins_pow->TurnOff()
#define icabpow_iPresent() (icabpow.Present())
#define icabpow_Init()	icabpow->Init()
#define icabpow_TurnOn()	icabpow->TurnOn()
#define icabpow_TurnOff()	icabpow->TurnOff()
#define iblizoopow_iPresent() (icabpow.Present())
#define iblizoopow_Init()	iblizoopow->Init()
#define iblizoopow_TurnOn()	iblizoopow->TurnOn()
#define iblizoopow_TurnOff()	iblizoopow->TurnOff()
#define icamsortpow_iPresent() (icamsortpow.Present())
#define icamsortpow_Init()	icamsortpow->Init()
#define icamsortpow_TurnOn()	icamsortpow->TurnOn()
#define icamsortpow_TurnOff()	icamsortpow->TurnOff()
#define iconpow_iPresent() (iconpow.Present())
#define iconpow_Init()	iconpow->Init()
#define iconpow_TurnOn()	iconpow->TurnOn()
#define iconpow_TurnOff()	iconpow->TurnOff()
#define idbookconpow_iPresent() (idbookconpow.Present())
#define idbookconpow_Init()	idbookconpow->Init()
#define idbookconpow_TurnOn()	idbookconpow->TurnOn()
#define idbookconpow_TurnOff()	idbookconpow->TurnOff()
#define idbooksortpow_iPresent() (idbooksortpow.Present())
#define idbooksortpow_Init()	idbooksortpow->Init()
#define idbooksortpow_TurnOn()	idbooksortpow->TurnOn()
#define idbooksortpow_TurnOff()	idbooksortpow->TurnOff()
#define idvbtsortpow_iPresent() (idvbtsortpow.Present())
#define idvbtsortpow_Init()	idvbtsortpow->Init()
#define idvbtsortpow_TurnOn()	idvbtsortpow->TurnOn()
#define idvbtsortpow_TurnOff()	idvbtsortpow->TurnOff()
#define ifinsortpow_iPresent() (ifinsortpow.Present())
#define ifinsortpow_Init()	ifinsortpow->Init()
#define ifinsortpow_TurnOn()	ifinsortpow->TurnOn()
#define ifinsortpow_TurnOff()	ifinsortpow->TurnOff()
#define iitapow_iPresent() (iitapow.Present())
#define iitapow_Init()	iitapow->Init()
#define iitapow_TurnOn()	iitapow->TurnOn()
#define iitapow_TurnOff()	iitapow->TurnOff()
#define ilitepow_iPresent() (ilitepow.Present())
#define ilitepow_Init()	ilitepow->Init()
#define ilitepow_TurnOn()	ilitepow->TurnOn()
#define ilitepow_TurnOff()	ilitepow->TurnOff()
#define imfreqctlpow_iPresent() (imfreqctlpow.Present())
#define imfreqctlpow_Init()	imfreqctlpow->Init()
#define imfreqctlpow_TurnOn()	imfreqctlpow->TurnOn()
#define imfreqctlpow_TurnOff()	imfreqctlpow->TurnOff()
#define impegpow_iPresent() (impegpow.Present())
#define impegpow_Init()	impegpow->Init()
#define impegpow_TurnOn()	impegpow->TurnOn()
#define impegpow_TurnOff()	impegpow->TurnOff()
#define impow_iPresent() (impow.Present())
#define impow_Init()	impow->Init()
#define impow_TurnOn()	impow->TurnOn()
#define impow_TurnOff()	impow->TurnOff()
#define inorpow_iPresent() (inorpow.Present())
#define inorpow_Init()	inorpow->Init()
#define inorpow_TurnOn()	inorpow->TurnOn()
#define inorpow_TurnOff()	inorpow->TurnOff()
#define svpaci_pow_iPresent() (svpaci_pow.Present())
#define svpaci_pow_Init()	svpaci_pow->Init()
#define svpaci_pow_TurnOn()	svpaci_pow->TurnOn()
#define svpaci_pow_TurnOff()	svpaci_pow->TurnOff()
#define idvbtapmeasortpow_iPresent() (idvbtapmeasortpow.Present())
#define idvbtapmeasortpow_Init()	idvbtapmeasortpow->Init()
#define idvbtapmeasortpow_TurnOn()	idvbtapmeasortpow->TurnOn()
#define idvbtapmeasortpow_TurnOff()	idvbtapmeasortpow->TurnOff()
#define idvbtapmeasortpow_iPresent() (idvbtapmeasortpow.Present())
#define idvbtapmeasortpow_Init()	idvbtapmeasortpow->Init()
#define idvbtapmeasortpow_TurnOn()	idvbtapmeasortpow->TurnOn()
#define idvbtapmeasortpow_TurnOff()	idvbtapmeasortpow->TurnOff()
#define idvbthungarysortpow_iPresent() (idvbthungarysortpow.Present())
#define idvbthungarysortpow_Init()	idvbthungarysortpow->Init()
#define idvbthungarysortpow_TurnOn()	idvbthungarysortpow->TurnOn()
#define idvbthungarysortpow_TurnOff()	idvbthungarysortpow->TurnOff()


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

