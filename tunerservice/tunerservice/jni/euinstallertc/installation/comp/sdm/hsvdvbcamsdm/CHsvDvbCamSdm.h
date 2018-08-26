#ifndef  _CHSVDVBCAMSDM_H
#define  _CHSVDVBCAMSDM_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCamScanHelper.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvMpegServices.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
class CHsvDvbCamSdm_Priv;
class CHsvDvbCamSdm
{
public:
ProvidesInterface<IHsvCamScanHelper>	camScanparser;
ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitc2dsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitcabledsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitcontentlabelconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitlinkageinfoconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitserviceconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitt2dsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitterrestrialdsconf;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
RequiresInterface<IHsvMpegServices>	mpegserv;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
public:
CHsvDvbCamSdm();
virtual ~CHsvDvbCamSdm();
private:
CHsvDvbCamSdm_Priv	*m_priv;
};

#endif

