#ifndef  _CEUINSTALLERMW_MPOW_H
#define  _CEUINSTALLERMW_MPOW_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
class CEuInstallerMw_mpow_Priv;
class CEuInstallerMw_mpow
{
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
CEuInstallerMw_mpow();
virtual ~CEuInstallerMw_mpow();
private:
CEuInstallerMw_mpow_Priv	*m_priv;
};

#endif

