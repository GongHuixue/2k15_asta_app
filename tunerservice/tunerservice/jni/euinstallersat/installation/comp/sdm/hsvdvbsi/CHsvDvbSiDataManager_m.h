#ifndef  _CHSVDVBSIDATAMANAGER_M_H
#define  _CHSVDVBSIDATAMANAGER_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStreamFilter.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
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
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbbat_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbbat_ena;
RequiresInterface<IHsvPower>	chsvdvbbat_pow;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbfnt_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbfnt_ena;
RequiresInterface<IHsvPower>	chsvdvbfnt_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbfnt_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbfst_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbfst_ena;
RequiresInterface<IHsvPower>	chsvdvbfst_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbfst_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbnit_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbnit_ena;
RequiresInterface<IHsvPower>	chsvdvbnit_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbnit_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbsdt_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbsdt_ena;
RequiresInterface<IHsvPower>	chsvdvbsdt_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbsdt_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbpostcode_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbpostcode_ena;
RequiresInterface<IHsvPower>	chsvdvbpostcode_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbpostcode_strmfltr;
RequiresInterface<IHsvSdmEnable>	chsvdvbcamnit_ena;
RequiresInterface<IHsvPower>	chsvdvbcamnit_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbcamnit_strmfltr;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbsgt_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbsgt_ena;
RequiresInterface<IHsvPower>	chsvdvbsgt_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbsgt_strmfltr;
RequiresInterface<IHsvSdmEnable>	chsvdvbtot_ena;
RequiresInterface<IHsvPower>	chsvdvbtot_pow;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbtot_dmxsecfN;
public:
CHsvDvbSiDataManager_m();
virtual ~CHsvDvbSiDataManager_m();
private:
CHsvDvbSiDataManager_m_Priv	*m_priv;
};

#endif

