#ifndef  _CHSVEUROPEINSTALLATION_MSORTROUTE_H
#define  _CHSVEUROPEINSTALLATION_MSORTROUTE_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSortRoute.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvCountryIds.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvInstallation2.h>
#include <IHsvTcSystemSettings.h>
class CHsvEuropeInstallation_mSortRoute_Priv;
class CHsvEuropeInstallation_mSortRoute
{
public:
ProvidesInterface<IHsvSortRoute>	isortroute;

ProvidesInterface<IHsvHybridPresetSort>	istubsort;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvHybridPresetSort>	idbooksort;
RequiresInterface<IHsvHybridPresetSort>	idvbclitesort;
RequiresInterface<IHsvHybridPresetSort>	idvbcsort;
RequiresInterface<IHsvHybridPresetSort>	iblizoosort;
RequiresInterface<IHsvHybridPresetSort>	idvbtlitesort;
RequiresInterface<IHsvHybridPresetSort>	idvbtsort;
RequiresInterface<IHsvHybridPresetSort>	ifinsort;
RequiresInterface<IHsvHybridPresetSort>	inorsort;
RequiresInterface<IHsvHybridPresetSort>	itasort;
RequiresInterface<IHsvHybridPresetSort>	idvbtapmeasort;
RequiresInterface<IHsvHybridPresetSort>	idvbthungarysort;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvTcSystemSettings>	sysset;
public:
CHsvEuropeInstallation_mSortRoute();
virtual ~CHsvEuropeInstallation_mSortRoute();
private:
CHsvEuropeInstallation_mSortRoute_Priv	*m_priv;
};

#endif

