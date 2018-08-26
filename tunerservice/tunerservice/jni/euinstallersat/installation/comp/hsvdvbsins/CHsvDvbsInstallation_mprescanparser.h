#ifndef  _CHSVDVBSINSTALLATION_MPRESCANPARSER_H
#define  _CHSVDVBSINSTALLATION_MPRESCANPARSER_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPrescanParser.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvSatelliteFrontEnd.h>
class CHsvDvbsInstallation_mprescanparser_Priv;
class CHsvDvbsInstallation_mprescanparser
{
public:
ProvidesInterface<IHsvPrescanParser>	iprescanparser;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>	charsetutil;
RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
public:
CHsvDvbsInstallation_mprescanparser();
virtual ~CHsvDvbsInstallation_mprescanparser();
private:
CHsvDvbsInstallation_mprescanparser_Priv	*m_priv;
};

#endif

