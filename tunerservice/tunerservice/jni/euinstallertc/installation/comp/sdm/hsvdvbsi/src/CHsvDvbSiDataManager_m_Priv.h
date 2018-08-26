#ifndef  _CHSVDVBSIDATAMANAGER_M_PRIV_H
#define  _CHSVDVBSIDATAMANAGER_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStreamFilter.h>
#include <CTCMwBase.h>
class CHsvDvbSiDataManager_m_Priv;
#define CLASSSCOPE CHsvDvbSiDataManager_m_Priv::
#include "locals_m.h"

class CHsvDvbSiDataManager_m_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbSiDataManager_m_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDemuxSectionFilterNotifyImpl(CHsvDvbSiDataManager_m_Priv,dmxsecfN);
IHsvSdmEnableImpl(CHsvDvbSiDataManager_m_Priv,ena);
IHsvPowerImpl(CHsvDvbSiDataManager_m_Priv,pow);
IHsvStreamFilterImpl(CHsvDvbSiDataManager_m_Priv,strmfltr);
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
CHsvDvbSiDataManager_m_Priv():i__dmxsecfN(this),i__ena(this),i__pow(this),i__strmfltr(this)
{
dmxsecfN	=	&i__dmxsecfN;
ena	=	&i__ena;
pow	=	&i__pow;
strmfltr	=	&i__strmfltr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define chsvdvbeit_dmxsecfN_iPresent() (chsvdvbeit_dmxsecfN.Present())
#define chsvdvbeit_dmxsecfN_OnRequestAllowed(dest)	chsvdvbeit_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbeit_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbeit_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbeit_dmxsecfN_OnRequestNotAllowed()	chsvdvbeit_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbeit_ena_iPresent() (chsvdvbeit_ena.Present())
#define chsvdvbeit_ena_Enable(dmx)	chsvdvbeit_ena->Enable(dmx)
#define chsvdvbeit_ena_Disable(dmx)	chsvdvbeit_ena->Disable(dmx)
#define chsvdvbeit_ena_Sync(dmx)	chsvdvbeit_ena->Sync(dmx)
#define chsvdvbeit_pow_iPresent() (chsvdvbeit_pow.Present())
#define chsvdvbeit_pow_Init()	chsvdvbeit_pow->Init()
#define chsvdvbeit_pow_TurnOn()	chsvdvbeit_pow->TurnOn()
#define chsvdvbeit_pow_TurnOff()	chsvdvbeit_pow->TurnOff()
#define chsvdvbeit_strmfltr_iPresent() (chsvdvbeit_strmfltr.Present())
#define chsvdvbeit_strmfltr_IsSet(dest,filterid,value)	chsvdvbeit_strmfltr->IsSet(dest,filterid,value)
#define chsvdvbeit_strmfltr_IsReady(dest,filterid)	chsvdvbeit_strmfltr->IsReady(dest,filterid)
#define chsvdvbeit_strmfltr_Set(dest,filterid,value)	chsvdvbeit_strmfltr->Set(dest,filterid,value)
#define chsvdvbeit_strmfltr_Clear(dest,filterid,value)	chsvdvbeit_strmfltr->Clear(dest,filterid,value)
#define chsvdvbeit_strmfltr_ForceClear(dest,filterid,value)	chsvdvbeit_strmfltr->ForceClear(dest,filterid,value)
#define chsvdvbnit_dmxsecfN_iPresent() (chsvdvbnit_dmxsecfN.Present())
#define chsvdvbnit_dmxsecfN_OnRequestAllowed(dest)	chsvdvbnit_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbnit_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbnit_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbnit_dmxsecfN_OnRequestNotAllowed()	chsvdvbnit_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbnit_ena_iPresent() (chsvdvbnit_ena.Present())
#define chsvdvbnit_ena_Enable(dmx)	chsvdvbnit_ena->Enable(dmx)
#define chsvdvbnit_ena_Disable(dmx)	chsvdvbnit_ena->Disable(dmx)
#define chsvdvbnit_ena_Sync(dmx)	chsvdvbnit_ena->Sync(dmx)
#define chsvdvbnit_pow_iPresent() (chsvdvbnit_pow.Present())
#define chsvdvbnit_pow_Init()	chsvdvbnit_pow->Init()
#define chsvdvbnit_pow_TurnOn()	chsvdvbnit_pow->TurnOn()
#define chsvdvbnit_pow_TurnOff()	chsvdvbnit_pow->TurnOff()
#define chsvdvbnit_strmfltr_iPresent() (chsvdvbnit_strmfltr.Present())
#define chsvdvbnit_strmfltr_IsSet(dest,filterid,value)	chsvdvbnit_strmfltr->IsSet(dest,filterid,value)
#define chsvdvbnit_strmfltr_IsReady(dest,filterid)	chsvdvbnit_strmfltr->IsReady(dest,filterid)
#define chsvdvbnit_strmfltr_Set(dest,filterid,value)	chsvdvbnit_strmfltr->Set(dest,filterid,value)
#define chsvdvbnit_strmfltr_Clear(dest,filterid,value)	chsvdvbnit_strmfltr->Clear(dest,filterid,value)
#define chsvdvbnit_strmfltr_ForceClear(dest,filterid,value)	chsvdvbnit_strmfltr->ForceClear(dest,filterid,value)
#define chsvdvbsdt_dmxsecfN_iPresent() (chsvdvbsdt_dmxsecfN.Present())
#define chsvdvbsdt_dmxsecfN_OnRequestAllowed(dest)	chsvdvbsdt_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbsdt_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbsdt_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbsdt_dmxsecfN_OnRequestNotAllowed()	chsvdvbsdt_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbsdt_ena_iPresent() (chsvdvbsdt_ena.Present())
#define chsvdvbsdt_ena_Enable(dmx)	chsvdvbsdt_ena->Enable(dmx)
#define chsvdvbsdt_ena_Disable(dmx)	chsvdvbsdt_ena->Disable(dmx)
#define chsvdvbsdt_ena_Sync(dmx)	chsvdvbsdt_ena->Sync(dmx)
#define chsvdvbsdt_pow_iPresent() (chsvdvbsdt_pow.Present())
#define chsvdvbsdt_pow_Init()	chsvdvbsdt_pow->Init()
#define chsvdvbsdt_pow_TurnOn()	chsvdvbsdt_pow->TurnOn()
#define chsvdvbsdt_pow_TurnOff()	chsvdvbsdt_pow->TurnOff()
#define chsvdvbsdt_strmfltr_iPresent() (chsvdvbsdt_strmfltr.Present())
#define chsvdvbsdt_strmfltr_IsSet(dest,filterid,value)	chsvdvbsdt_strmfltr->IsSet(dest,filterid,value)
#define chsvdvbsdt_strmfltr_IsReady(dest,filterid)	chsvdvbsdt_strmfltr->IsReady(dest,filterid)
#define chsvdvbsdt_strmfltr_Set(dest,filterid,value)	chsvdvbsdt_strmfltr->Set(dest,filterid,value)
#define chsvdvbsdt_strmfltr_Clear(dest,filterid,value)	chsvdvbsdt_strmfltr->Clear(dest,filterid,value)
#define chsvdvbsdt_strmfltr_ForceClear(dest,filterid,value)	chsvdvbsdt_strmfltr->ForceClear(dest,filterid,value)
#define chsvdvbtdt_dmxsecfN_iPresent() (chsvdvbtdt_dmxsecfN.Present())
#define chsvdvbtdt_dmxsecfN_OnRequestAllowed(dest)	chsvdvbtdt_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbtdt_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbtdt_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbtdt_dmxsecfN_OnRequestNotAllowed()	chsvdvbtdt_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbtdt_ena_iPresent() (chsvdvbtdt_ena.Present())
#define chsvdvbtdt_ena_Enable(dmx)	chsvdvbtdt_ena->Enable(dmx)
#define chsvdvbtdt_ena_Disable(dmx)	chsvdvbtdt_ena->Disable(dmx)
#define chsvdvbtdt_ena_Sync(dmx)	chsvdvbtdt_ena->Sync(dmx)
#define chsvdvbtdt_pow_iPresent() (chsvdvbtdt_pow.Present())
#define chsvdvbtdt_pow_Init()	chsvdvbtdt_pow->Init()
#define chsvdvbtdt_pow_TurnOn()	chsvdvbtdt_pow->TurnOn()
#define chsvdvbtdt_pow_TurnOff()	chsvdvbtdt_pow->TurnOff()
#define chsvdvbtot_dmxsecfN_iPresent() (chsvdvbtot_dmxsecfN.Present())
#define chsvdvbtot_dmxsecfN_OnRequestAllowed(dest)	chsvdvbtot_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbtot_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbtot_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbtot_dmxsecfN_OnRequestNotAllowed()	chsvdvbtot_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbtot_ena_iPresent() (chsvdvbtot_ena.Present())
#define chsvdvbtot_ena_Enable(dmx)	chsvdvbtot_ena->Enable(dmx)
#define chsvdvbtot_ena_Disable(dmx)	chsvdvbtot_ena->Disable(dmx)
#define chsvdvbtot_ena_Sync(dmx)	chsvdvbtot_ena->Sync(dmx)
#define chsvdvbtot_pow_iPresent() (chsvdvbtot_pow.Present())
#define chsvdvbtot_pow_Init()	chsvdvbtot_pow->Init()
#define chsvdvbtot_pow_TurnOn()	chsvdvbtot_pow->TurnOn()
#define chsvdvbtot_pow_TurnOff()	chsvdvbtot_pow->TurnOff()
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_m.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

