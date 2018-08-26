#ifndef  _CHSVDVBEIT_PRIV_H
#define  _CHSVDVBEIT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvDVBService.h>
#include <IHsvMpegServices.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvStreamNotify.h>
#include <CTCMwBase.h>
class CHsvDvbEIT_Priv;
#define CLASSSCOPE CHsvDvbEIT_Priv::
#include "locals_m.h"

class CHsvDvbEIT_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbEIT_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDemuxSectionFilterNotifyImpl(CHsvDvbEIT_Priv,dmxsecfN);
IHsvSdmEnableImpl(CHsvDvbEIT_Priv,ena);
IHsvPowerImpl(CHsvDvbEIT_Priv,pow);
IHsvStreamImpl(CHsvDvbEIT_Priv,strapi);
IHsvStreamFilterImpl(CHsvDvbEIT_Priv,strmfltr);
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvDVBService>	dvbsvc;
RequiresInterface<IHsvMpegServices>	mpegserv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvStreamNotify>	strapiN;
private:
DEMUX_DEFINES(CHsvDvbEIT_Priv,sec);

public:
CHsvDvbEIT_Priv():i__dmxsecfN(this),i__ena(this),i__pow(this),i__strapi(this),i__strmfltr(this)
{
dmxsecfN	=	&i__dmxsecfN;
ena	=	&i__ena;
pow	=	&i__pow;
strapi	=	&i__strapi;
strmfltr	=	&i__strmfltr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define conf_iPresent() (conf.Present())
#define conf_NitActualParsing	IHsvDVBSIConfig_NitActualParsing
#define conf_NitOtherParsing	IHsvDVBSIConfig_NitOtherParsing
#define conf_SdtActualParsing	IHsvDVBSIConfig_SdtActualParsing
#define conf_SdtOtherParsing	IHsvDVBSIConfig_SdtOtherParsing
#define conf_EitNowNextActualParsing	IHsvDVBSIConfig_EitNowNextActualParsing
#define conf_EitNowNextOtherParsing	IHsvDVBSIConfig_EitNowNextOtherParsing
#define conf_EitSchedActualParsing	IHsvDVBSIConfig_EitSchedActualParsing
#define conf_EitSchedOtherParsing	IHsvDVBSIConfig_EitSchedOtherParsing
#define conf_TdtParsing	IHsvDVBSIConfig_TdtParsing
#define conf_TotParsing	IHsvDVBSIConfig_TotParsing
#define conf_Notifications	IHsvDVBSIConfig_Notifications
#define conf_CurrentCountry	conf->CurrentCountry()
#define conf_IsActionAllowed(dmx,table)	conf->IsActionAllowed(dmx,table)
#define dvbsvc_iPresent() (dvbsvc.Present())
#define dvbsvc_GetCurrentService(dmx,onwid,svcid)	dvbsvc->GetCurrentService(dmx,onwid,svcid)
#define dvbsvc_GetCurrentService2(dmx,onwid,tsid,svcid)	dvbsvc->GetCurrentService2(dmx,onwid,tsid,svcid)
#define dvbsvc_GetOtherService(dmx,onwid,svcid)	dvbsvc->GetOtherService(dmx,onwid,svcid)
#define dvbsvc_GetActualEitSchedService(dmx,svcid)	dvbsvc->GetActualEitSchedService(dmx,svcid)
#define dvbsvc_GetOtherEitSchedService(dmx,svcid)	dvbsvc->GetOtherEitSchedService(dmx,svcid)
#define dvbsvc_GetExtendedInfoEventId(dmx,evtid)	dvbsvc->GetExtendedInfoEventId(dmx,evtid)
#define mpegserv_iPresent() (mpegserv.Present())
#define mpegserv_GetLanguageId(byte1,byte2,byte3)	mpegserv->GetLanguageId(byte1,byte2,byte3)
#define mpegserv_IsProgramPresent(dmx,prg)	mpegserv->IsProgramPresent(dmx,prg)
#define mpegserv_ReadTsPacketFields(subscr_id,sec)	mpegserv->ReadTsPacketFields(subscr_id,sec)
#define mpegserv_GetCcDescriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetCcDescriptor(dmx,prg,IsDescriptorParsed)
#define mpegserv_GetCaDescriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetCaDescriptor(dmx,prg,IsDescriptorParsed)
#define mpegserv_GetAc3Descriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetAc3Descriptor(dmx,prg,IsDescriptorParsed)
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
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
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

