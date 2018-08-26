#ifndef  _CHSVEUROPEINSTALLATION_MSTUB_H
#define  _CHSVEUROPEINSTALLATION_MSTUB_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <ISvcCniData.h>
class CHsvEuropeInstallation_mstub_Priv;
class CHsvEuropeInstallation_mstub
{
public:
ProvidesInterface<ISvcCniData>	hsvprins_pgdatcni;

public:
CHsvEuropeInstallation_mstub();
virtual ~CHsvEuropeInstallation_mstub();
private:
CHsvEuropeInstallation_mstub_Priv	*m_priv;
};

#endif

