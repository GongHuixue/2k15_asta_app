#ifndef  _CHSVDVBSIDATAMANAGER_M_H
#define  _CHSVDVBSIDATAMANAGER_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStreamFilter.h>
class CHsvDvbSiDataManager_m_Priv;
class CHsvDvbSiDataManager_m
{
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbeit_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbeit_ena;
RequiresInterface<IHsvPower>	chsvdvbeit_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbeit_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbnit_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbnit_ena;
RequiresInterface<IHsvPower>	chsvdvbnit_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbnit_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbsdt_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbsdt_ena;
RequiresInterface<IHsvPower>	chsvdvbsdt_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbsdt_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbtdt_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbtdt_ena;
RequiresInterface<IHsvPower>	chsvdvbtdt_pow;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbtot_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbtot_ena;
RequiresInterface<IHsvPower>	chsvdvbtot_pow;
public:
CHsvDvbSiDataManager_m();
virtual ~CHsvDvbSiDataManager_m();
private:
CHsvDvbSiDataManager_m_Priv	*m_priv;
};

#endif

