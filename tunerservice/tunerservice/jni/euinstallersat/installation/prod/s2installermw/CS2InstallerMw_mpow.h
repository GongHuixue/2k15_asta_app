#ifndef  _CS2INSTALLERMW_MPOW_H
#define  _CS2INSTALLERMW_MPOW_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
class CS2InstallerMw_mpow_Priv;
class CS2InstallerMw_mpow
{
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	hsvdvbsdm_pow;
RequiresInterface<IHsvPower>	hsvdvbsins_pow;
RequiresInterface<IHsvPower>	hsvsatfe_pow;
RequiresInterface<IHsvPower>	sathsvpgdat_pow;
public:
CS2InstallerMw_mpow();
virtual ~CS2InstallerMw_mpow();
private:
CS2InstallerMw_mpow_Priv	*m_priv;
};

#endif

