#ifndef  _CHSVDVBSIDATAMANAGER_M_PRIV_H
#define  _CHSVDVBSIDATAMANAGER_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStreamFilter.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <CS2MwBase.h>
class CHsvDvbSiDataManager_m_Priv;
#define CLASSSCOPE CHsvDvbSiDataManager_m_Priv::
#include "locals_m.h"

class CHsvDvbSiDataManager_m_Priv : public CS2MwBase
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
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSdmEnable>	chsvdvbcamnit_ena;
RequiresInterface<IHsvPower>	chsvdvbcamnit_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbcamnit_strmfltr;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbsgt_dmxsecfN;
RequiresInterface<IHsvSdmEnable>	chsvdvbsgt_ena;
RequiresInterface<IHsvPower>	chsvdvbsgt_pow;
RequiresInterface<IHsvStreamFilter>	chsvdvbsgt_strmfltr;
RequiresInterface<IHsvSdmEnable>	chsvdvbtot_ena;
RequiresInterface<IHsvPower>	chsvdvbtot_pow;
RequiresInterface<IHsvDemuxSectionFilterNotify>	chsvdvbtot_dmxsecfN;

private:
DEMUX_DEFINES(CHsvDvbSiDataManager_m_Priv,sec);

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
#define chsvdvbbat_dmxsecfN_iPresent() (chsvdvbbat_dmxsecfN.Present())
#define chsvdvbbat_dmxsecfN_OnRequestAllowed(dest)	chsvdvbbat_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbbat_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbbat_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbbat_dmxsecfN_OnRequestNotAllowed()	chsvdvbbat_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbbat_ena_iPresent() (chsvdvbbat_ena.Present())
#define chsvdvbbat_ena_Enable(dmx)	chsvdvbbat_ena->Enable(dmx)
#define chsvdvbbat_ena_Disable(dmx)	chsvdvbbat_ena->Disable(dmx)
#define chsvdvbbat_ena_Sync(dmx)	chsvdvbbat_ena->Sync(dmx)
#define chsvdvbbat_pow_iPresent() (chsvdvbbat_pow.Present())
#define chsvdvbbat_pow_Init()	chsvdvbbat_pow->Init()
#define chsvdvbbat_pow_TurnOn()	chsvdvbbat_pow->TurnOn()
#define chsvdvbbat_pow_TurnOff()	chsvdvbbat_pow->TurnOff()
#define chsvdvbfnt_dmxsecfN_iPresent() (chsvdvbfnt_dmxsecfN.Present())
#define chsvdvbfnt_dmxsecfN_OnRequestAllowed(dest)	chsvdvbfnt_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbfnt_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbfnt_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbfnt_dmxsecfN_OnRequestNotAllowed()	chsvdvbfnt_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbfnt_ena_iPresent() (chsvdvbfnt_ena.Present())
#define chsvdvbfnt_ena_Enable(dmx)	chsvdvbfnt_ena->Enable(dmx)
#define chsvdvbfnt_ena_Disable(dmx)	chsvdvbfnt_ena->Disable(dmx)
#define chsvdvbfnt_ena_Sync(dmx)	chsvdvbfnt_ena->Sync(dmx)
#define chsvdvbfnt_pow_iPresent() (chsvdvbfnt_pow.Present())
#define chsvdvbfnt_pow_Init()	chsvdvbfnt_pow->Init()
#define chsvdvbfnt_pow_TurnOn()	chsvdvbfnt_pow->TurnOn()
#define chsvdvbfnt_pow_TurnOff()	chsvdvbfnt_pow->TurnOff()
#define chsvdvbfnt_strmfltr_iPresent() (chsvdvbfnt_strmfltr.Present())
#define chsvdvbfnt_strmfltr_IsSet(dest,filterid,value)	chsvdvbfnt_strmfltr->IsSet(dest,filterid,value)
#define chsvdvbfnt_strmfltr_IsReady(dest,filterid)	chsvdvbfnt_strmfltr->IsReady(dest,filterid)
#define chsvdvbfnt_strmfltr_Set(dest,filterid,value)	chsvdvbfnt_strmfltr->Set(dest,filterid,value)
#define chsvdvbfnt_strmfltr_Clear(dest,filterid,value)	chsvdvbfnt_strmfltr->Clear(dest,filterid,value)
#define chsvdvbfst_dmxsecfN_iPresent() (chsvdvbfst_dmxsecfN.Present())
#define chsvdvbfst_dmxsecfN_OnRequestAllowed(dest)	chsvdvbfst_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbfst_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbfst_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbfst_dmxsecfN_OnRequestNotAllowed()	chsvdvbfst_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbfst_ena_iPresent() (chsvdvbfst_ena.Present())
#define chsvdvbfst_ena_Enable(dmx)	chsvdvbfst_ena->Enable(dmx)
#define chsvdvbfst_ena_Disable(dmx)	chsvdvbfst_ena->Disable(dmx)
#define chsvdvbfst_ena_Sync(dmx)	chsvdvbfst_ena->Sync(dmx)
#define chsvdvbfst_pow_iPresent() (chsvdvbfst_pow.Present())
#define chsvdvbfst_pow_Init()	chsvdvbfst_pow->Init()
#define chsvdvbfst_pow_TurnOn()	chsvdvbfst_pow->TurnOn()
#define chsvdvbfst_pow_TurnOff()	chsvdvbfst_pow->TurnOff()
#define chsvdvbfst_strmfltr_iPresent() (chsvdvbfst_strmfltr.Present())
#define chsvdvbfst_strmfltr_IsSet(dest,filterid,value)	chsvdvbfst_strmfltr->IsSet(dest,filterid,value)
#define chsvdvbfst_strmfltr_IsReady(dest,filterid)	chsvdvbfst_strmfltr->IsReady(dest,filterid)
#define chsvdvbfst_strmfltr_Set(dest,filterid,value)	chsvdvbfst_strmfltr->Set(dest,filterid,value)
#define chsvdvbfst_strmfltr_Clear(dest,filterid,value)	chsvdvbfst_strmfltr->Clear(dest,filterid,value)
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
#define chsvdvbpostcode_dmxsecfN_iPresent() (chsvdvbpostcode_dmxsecfN.Present())
#define chsvdvbpostcode_dmxsecfN_OnRequestAllowed(dest)	chsvdvbpostcode_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbpostcode_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbpostcode_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbpostcode_dmxsecfN_OnRequestNotAllowed()	chsvdvbpostcode_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbpostcode_ena_iPresent() (chsvdvbpostcode_ena.Present())
#define chsvdvbpostcode_ena_Enable(dmx)	chsvdvbpostcode_ena->Enable(dmx)
#define chsvdvbpostcode_ena_Disable(dmx)	chsvdvbpostcode_ena->Disable(dmx)
#define chsvdvbpostcode_ena_Sync(dmx)	chsvdvbpostcode_ena->Sync(dmx)
#define chsvdvbpostcode_pow_iPresent() (chsvdvbpostcode_pow.Present())
#define chsvdvbpostcode_pow_Init()	chsvdvbpostcode_pow->Init()
#define chsvdvbpostcode_pow_TurnOn()	chsvdvbpostcode_pow->TurnOn()
#define chsvdvbpostcode_pow_TurnOff()	chsvdvbpostcode_pow->TurnOff()
#define chsvdvbpostcode_strmfltr_iPresent() (chsvdvbpostcode_strmfltr.Present())
#define chsvdvbpostcode_strmfltr_IsSet(dest,filterid,value)	chsvdvbpostcode_strmfltr->IsSet(dest,filterid,value)
#define chsvdvbpostcode_strmfltr_IsReady(dest,filterid)	chsvdvbpostcode_strmfltr->IsReady(dest,filterid)
#define chsvdvbpostcode_strmfltr_Set(dest,filterid,value)	chsvdvbpostcode_strmfltr->Set(dest,filterid,value)
#define chsvdvbpostcode_strmfltr_Clear(dest,filterid,value)	chsvdvbpostcode_strmfltr->Clear(dest,filterid,value)
#define chsvdvbcamnit_ena_iPresent() (chsvdvbcamnit_ena.Present())
#define chsvdvbcamnit_ena_Enable(dmx)	chsvdvbcamnit_ena->Enable(dmx)
#define chsvdvbcamnit_ena_Disable(dmx)	chsvdvbcamnit_ena->Disable(dmx)
#define chsvdvbcamnit_ena_Sync(dmx)	chsvdvbcamnit_ena->Sync(dmx)
#define chsvdvbcamnit_pow_iPresent() (chsvdvbcamnit_pow.Present())
#define chsvdvbcamnit_pow_Init()	chsvdvbcamnit_pow->Init()
#define chsvdvbcamnit_pow_TurnOn()	chsvdvbcamnit_pow->TurnOn()
#define chsvdvbcamnit_pow_TurnOff()	chsvdvbcamnit_pow->TurnOff()
#define chsvdvbcamnit_strmfltr_iPresent() (chsvdvbcamnit_strmfltr.Present())
#define chsvdvbcamnit_strmfltr_IsSet(dest,filterid,value)	chsvdvbcamnit_strmfltr->IsSet(dest,filterid,value)
#define chsvdvbcamnit_strmfltr_IsReady(dest,filterid)	chsvdvbcamnit_strmfltr->IsReady(dest,filterid)
#define chsvdvbcamnit_strmfltr_Set(dest,filterid,value)	chsvdvbcamnit_strmfltr->Set(dest,filterid,value)
#define chsvdvbcamnit_strmfltr_Clear(dest,filterid,value)	chsvdvbcamnit_strmfltr->Clear(dest,filterid,value)
#define sec_iPresent() (sec.Present())
#define sec_SctArrived	IHsvDemuxSectionFilter2_SctArrived
#define sec_TableCompleted	IHsvDemuxSectionFilter2_TableCompleted
#define sec_SectionDepth	sec->SectionDepth()
#define sec_IsRequestAllowed(dest)	sec->IsRequestAllowed(dest)
#define sec_RequestSection(dest,pid,tableid,cookie,sctCallback)	sec->RequestSection(dest,pid,tableid,cookie,sctCallback)
#define sec_RequestSection2(dest,pid,tableid,tableidextn,cookie,sctCallback)	sec->RequestSection2(dest,pid,tableid,tableidextn,cookie,sctCallback)
#define sec_RequestSection3(dest,pid,tableid,tableidextn,tableidextn2,cookie,sctCallback)	sec->RequestSection3(dest,pid,tableid,tableidextn,tableidextn2,cookie,sctCallback)
#define sec_ResetRequest(dest,subscrId)	sec->ResetRequest(dest,subscrId)
#define sec_CancelSection(dest,subscrId)	sec->CancelSection(dest,subscrId)
#define sec_RequestPes(dest,pid,cookie,pesCallback)	sec->RequestPes(dest,pid,cookie,pesCallback)
#define sec_CancelPes(dest,subscrId)	sec->CancelPes(dest,subscrId)
#define sec_RequestSectionFilter(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)	sec->RequestSectionFilter(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)
#define sec_UpdateFilter(dest,subscrId,pFilterDepth,ModeArray,MatchArray,MaskArray)	sec->UpdateFilter(dest,subscrId,pFilterDepth,ModeArray,MatchArray,MaskArray)
#define sec_RequestSectionFilterList(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)	sec->RequestSectionFilterList(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback)
#define sec_RequestPesList(dest,pid,cookie,pesCallback,TimeOut,ListLength)	sec->RequestPesList(dest,pid,cookie,pesCallback,TimeOut,ListLength)
#define sec_GetBits(sectionid,numbits)	sec->GetBits(sectionid,numbits)
#define sec_ShowBits(sectionid,numbits)	sec->ShowBits(sectionid,numbits)
#define sec_SkipBits(sectionid,numbits)	sec->SkipBits(sectionid,numbits)
#define sec_AlignToNextByte(sectionid)	sec->AlignToNextByte(sectionid)
#define sec_IsEndOfSection(sectionid)	sec->IsEndOfSection(sectionid)
#define sec_GetBitsRead(sectionid)	sec->GetBitsRead(sectionid)
#define sec_GetBitsUnread(sectionid)	sec->GetBitsUnread(sectionid)
#define sec_GetSectionBuffer(sectionid)	sec->GetSectionBuffer(sectionid)
#define sec_GetSectionLength(sectionid)	sec->GetSectionLength(sectionid)
#define sec_CheckandCancelSection(dest,PidValue)	sec->CheckandCancelSection(dest,PidValue)
#define chsvdvbsgt_dmxsecfN_iPresent() (chsvdvbsgt_dmxsecfN.Present())
#define chsvdvbsgt_dmxsecfN_OnRequestAllowed(dest)	chsvdvbsgt_dmxsecfN->OnRequestAllowed(dest)
#define chsvdvbsgt_dmxsecfN_OnRequestCancelled(subscrId)	chsvdvbsgt_dmxsecfN->OnRequestCancelled(subscrId)
#define chsvdvbsgt_dmxsecfN_OnRequestNotAllowed()	chsvdvbsgt_dmxsecfN->OnRequestNotAllowed()
#define chsvdvbsgt_ena_iPresent() (chsvdvbsgt_ena.Present())
#define chsvdvbsgt_ena_Enable(dmx)	chsvdvbsgt_ena->Enable(dmx)
#define chsvdvbsgt_ena_Disable(dmx)	chsvdvbsgt_ena->Disable(dmx)
#define chsvdvbsgt_ena_Sync(dmx)	chsvdvbsgt_ena->Sync(dmx)
#define chsvdvbsgt_pow_iPresent() (chsvdvbsgt_pow.Present())
#define chsvdvbsgt_pow_Init()	chsvdvbsgt_pow->Init()
#define chsvdvbsgt_pow_TurnOn()	chsvdvbsgt_pow->TurnOn()
#define chsvdvbsgt_pow_TurnOff()	chsvdvbsgt_pow->TurnOff()
#define chsvdvbsgt_strmfltr_iPresent() (chsvdvbsgt_strmfltr.Present())
#define chsvdvbsgt_strmfltr_IsSet(dest,filterid,value)	chsvdvbsgt_strmfltr->IsSet(dest,filterid,value)
#define chsvdvbsgt_strmfltr_IsReady(dest,filterid)	chsvdvbsgt_strmfltr->IsReady(dest,filterid)
#define chsvdvbsgt_strmfltr_Set(dest,filterid,value)	chsvdvbsgt_strmfltr->Set(dest,filterid,value)
#define chsvdvbsgt_strmfltr_Clear(dest,filterid,value)	chsvdvbsgt_strmfltr->Clear(dest,filterid,value)
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
#ifdef sec_RequestSectionFilter
#undef sec_RequestSectionFilter
#endif
#ifdef sec_RequestSectionFilterList
#undef sec_RequestSectionFilterList
#endif
#ifdef sec_RequestSection
#undef sec_RequestSection
#endif
#ifdef sec_RequestSection2
#undef sec_RequestSection2
#endif
#ifdef sec_RequestSection3
#undef sec_RequestSection3
#endif
#ifdef sec_RequestPes
#undef sec_RequestPes
#endif
#ifdef sec_RequestPesList
#undef sec_RequestPesList
#endif
#ifdef sec_CancelSection
#undef sec_CancelSection
#endif
#ifdef sec_CancelPes
#undef sec_CancelPes
#endif
#define sec_RequestSectionFilter dmxlocal_RequestSectionFilter
#define sec_RequestSectionFilterList dmxlocal_RequestSectionFilterList
#define sec_RequestSection dmxlocal_RequestSection
#define sec_RequestSection2 dmxlocal_RequestSection2
#define sec_RequestSection3 dmxlocal_RequestSection3
#define sec_RequestPes dmxlocal_RequestPes
#define sec_RequestPesList dmxlocal_RequestPesList
#define sec_CancelSection dmxlocal_CancelSection
#define sec_CancelPes dmxlocal_CancelPes
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

