#ifndef  _CHSVDVBSINSTALLATION_MROUTE_H
#define  _CHSVDVBSINSTALLATION_MROUTE_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvPower.h>
#include <IHsvPackageRoute.h>
#include <IHsvSorting.h>
#include <IHsvStreamNotify.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvPackageParser.h>
#include <IHsvSatelliteInstallation.h>
#include <ICesOperatorProfileNotify.h>
#include <IHsvSatelliteSettings.h>
class CHsvDvbsInstallation_mroute_Priv;
class CHsvDvbsInstallation_mroute
{
public:
ProvidesInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;

ProvidesInterface<IHsvSdmControlNotifyEx>	ibckctrlN;

ProvidesInterface<IHsvSdmControlNotifyEx>	ipackagectrlN;

ProvidesInterface<IHsvSatellitePackageInstallation>	ipackageins;

ProvidesInterface<IHsvSatelliteFrontEndNotify>	ipackageplfApidvbsN;

ProvidesInterface<IHsvPower>	ipackagepow;

ProvidesInterface<IHsvPackageRoute>	ipackageroute;

ProvidesInterface<IHsvSorting>	ipackagesort;

ProvidesInterface<IHsvStreamNotify>	istrapiN;

ProvidesInterface<ICesOperatorProfileNotify>	ipackageopinsN;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbscanal_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbscanal_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbscanal_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbscanal_pow;
RequiresInterface<IHsvSorting>	hsvdvbscanal_sort;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsopprofile_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsopprofile_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsopprofile_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsopprofile_pow;
RequiresInterface<IHsvSorting>	hsvdvbsopprofile_sort;
RequiresInterface<IHsvStreamNotify>	hsvdvbsopprofile_strapiN;
RequiresInterface<ICesOperatorProfileNotify>	hsvdvbsopprofile_opinsN;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsdigiturk_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsdigiturk_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsdigiturk_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsdigiturk_pow;
RequiresInterface<IHsvSorting>	hsvdvbsdigiturk_sort;
RequiresInterface<IHsvSatelliteBackgroundInstallation>	hsvdvbsfransat_bckInstall;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsfransat_bckctrlN;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsfransat_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsfransat_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsfransat_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsfransat_pow;
RequiresInterface<IHsvSorting>	hsvdvbsfransat_sort;
RequiresInterface<IHsvStreamNotify>	hsvdvbsfransat_strapiN;
RequiresInterface<IHsvSatelliteBackgroundInstallation>	hsvdvbsgeneric_bckInstall;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsgeneric_bckctrlN;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsgeneric_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsgeneric_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsgeneric_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsgeneric_pow;
RequiresInterface<IHsvSorting>	hsvdvbsgeneric_sort;
RequiresInterface<IHsvStreamNotify>	hsvdvbsgeneric_strapiN;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsm7_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsm7_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsm7_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsm7_pow;
RequiresInterface<IHsvSorting>	hsvdvbsm7_sort;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsn_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsn_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsn_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsn_pow;
RequiresInterface<IHsvSorting>	hsvdvbsn_sort;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbspol_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbspol_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbspol_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbspol_pow;
RequiresInterface<IHsvSorting>	hsvdvbspol_sort;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsrussia_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsrussia_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsrussia_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsrussia_pow;
RequiresInterface<IHsvSorting>	hsvdvbsrussia_sort;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsfreesat_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsfreesat_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsfreesat_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsfreesat_pow;
RequiresInterface<IHsvSorting>	hsvdvbsfreesat_sort;
RequiresInterface<IHsvSatelliteSettings>	hsvdvbsfreesat_settings;
RequiresInterface<IHsvStreamNotify> hsvdvbsfreesat_strapiN;
RequiresInterface<IHsvSatelliteBackgroundInstallation>hsvdvbsfreesat_ibckInstall;
RequiresInterface<IHsvPackageParser>	ipackage;
RequiresInterface<IHsvSatelliteInstallation>	pins;
RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbsastra_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbsastra_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbsastra_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbsastra_pow;
RequiresInterface<IHsvSorting>	hsvdvbsastra_sort;
RequiresInterface<IHsvSatelliteBackgroundInstallation>	hsvdvbsastra_bckInstall;
RequiresInterface<IHsvStreamNotify>	hsvdvbsastra_strapiN;

RequiresInterface<IHsvSdmControlNotifyEx>	hsvdvbstricolor_ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	hsvdvbstricolor_ins;
RequiresInterface<IHsvSatelliteFrontEndNotify>	hsvdvbstricolor_plfApidvbsN;
RequiresInterface<IHsvPower>	hsvdvbstricolor_pow;
RequiresInterface<IHsvSorting>	hsvdvbstricolor_sort;
RequiresInterface<IHsvStreamNotify>	hsvdvbstricolor_strapiN;

public:
CHsvDvbsInstallation_mroute();
virtual ~CHsvDvbsInstallation_mroute();
private:
CHsvDvbsInstallation_mroute_Priv	*m_priv;
};

#endif

