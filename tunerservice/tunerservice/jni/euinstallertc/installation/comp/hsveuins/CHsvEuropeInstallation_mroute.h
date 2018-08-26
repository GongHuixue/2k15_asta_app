#ifndef  _CHSVEUROPEINSTALLATION_MROUTE_H
#define  _CHSVEUROPEINSTALLATION_MROUTE_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortRoute.h>
class CHsvEuropeInstallation_mroute_Priv;
class CHsvEuropeInstallation_mroute
{
public:
ProvidesInterface<IHsvHybridPresetSort>	isort;

//Required interfaces
public:
RequiresInterface<IHsvHybridPresetSort>	idbooksort;
RequiresInterface<IHsvHybridPresetSort>	idvbclitesort;
RequiresInterface<IHsvHybridPresetSort>	idvbcsort;
RequiresInterface<IHsvHybridPresetSort>	iblizoosort;
RequiresInterface<IHsvHybridPresetSort>	idvbtlitesort;
RequiresInterface<IHsvHybridPresetSort>	idvbtsort;
RequiresInterface<IHsvHybridPresetSort>	ifinsort;
RequiresInterface<IHsvHybridPresetSort>	inorsort;
RequiresInterface<IHsvHybridPresetSort>	idvbtapmeasort;
RequiresInterface<IHsvHybridPresetSort>	idvbthungarysort;
RequiresInterface<IHsvSortRoute>	isortroute;
RequiresInterface<IHsvHybridPresetSort>	istubsort;
RequiresInterface<IHsvHybridPresetSort>	itasort;
public:
CHsvEuropeInstallation_mroute();
virtual ~CHsvEuropeInstallation_mroute();
private:
CHsvEuropeInstallation_mroute_Priv	*m_priv;
};

#endif

