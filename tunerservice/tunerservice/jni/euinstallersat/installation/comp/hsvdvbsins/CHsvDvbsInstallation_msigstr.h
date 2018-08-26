#ifndef  _CHSVDVBSINSTALLATION_MSIGSTR_H
#define  _CHSVDVBSINSTALLATION_MSIGSTR_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvInstallationSigStrength.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvWindowDestinationMap.h>
class CHsvDvbsInstallation_msigstr_Priv;
class CHsvDvbsInstallation_msigstr
{
public:
ProvidesInterface<IHsvInstallationSigStrength>	isigstr;

//Required interfaces
public:
RequiresInterface<IPlfApiSigStrengthMeas>	qssm;
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
public:
CHsvDvbsInstallation_msigstr();
virtual ~CHsvDvbsInstallation_msigstr();
private:
CHsvDvbsInstallation_msigstr_Priv	*m_priv;
};

#endif

