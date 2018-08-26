#ifndef  _CHSVEUROPEINSTALLATION_MPOW_H
#define  _CHSVEUROPEINSTALLATION_MPOW_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <ISvPower.h>
class CHsvEuropeInstallation_mpow_Priv;
class CHsvEuropeInstallation_mpow
{
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
RequiresInterface<IHsvPower>	idvbtapmeasortpow;
RequiresInterface<IHsvPower>	idvbthungarysortpow;
RequiresInterface<IHsvPower>	imfreqctlpow;
RequiresInterface<IHsvPower>	impegpow;
RequiresInterface<IHsvPower>	impow;
RequiresInterface<IHsvPower>	inorpow;
RequiresInterface<ISvPower>		svpaci_pow;
RequiresInterface<IHsvPower>	hsvcanaldigitalins_pow;
public:
CHsvEuropeInstallation_mpow();
virtual ~CHsvEuropeInstallation_mpow();
private:
CHsvEuropeInstallation_mpow_Priv	*m_priv;
};

#endif

