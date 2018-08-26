#ifndef  _CHSVDVBSINSTALLATION_MPOW_H
#define  _CHSVDVBSINSTALLATION_MPOW_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
class CHsvDvbsInstallation_mpow_Priv;
class CHsvDvbsInstallation_mpow
{
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
CHsvDvbsInstallation_mpow();
virtual ~CHsvDvbsInstallation_mpow();
private:
CHsvDvbsInstallation_mpow_Priv	*m_priv;
};

#endif

