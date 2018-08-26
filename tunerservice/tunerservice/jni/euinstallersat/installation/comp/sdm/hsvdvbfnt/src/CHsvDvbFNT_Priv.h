#ifndef  _CHSVDVBFNT_PRIV_H
#define  _CHSVDVBFNT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <CS2MwBase.h>
class CHsvDvbFNT_Priv;
#define CLASSSCOPE CHsvDvbFNT_Priv::
#include "locals_m.h"

class CHsvDvbFNT_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbFNT_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDemuxSectionFilterNotifyImpl(CHsvDvbFNT_Priv,dmxsecfN);
IHsvSdmEnableImpl(CHsvDvbFNT_Priv,ena);
IHsvSortedTableConfigurationExImpl(CHsvDvbFNT_Priv,fntlcnconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbFNT_Priv,fntsatellitedsdconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbFNT_Priv,fntsrvclstconf);
IHsvPowerImpl(CHsvDvbFNT_Priv,pow);
IHsvStreamImpl(CHsvDvbFNT_Priv,strapi);
IHsvStreamFilterImpl(CHsvDvbFNT_Priv,strmfltr);
public:
ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvSortedTableConfigurationEx>	fntlcnconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	fntsatellitedsdconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	fntsrvclstconf;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
RequiresInterface<IHsvDVBSIConfig>	conf;
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
private:
DEMUX_DEFINES(CHsvDvbFNT_Priv,sec);

public:
CHsvDvbFNT_Priv():i__dmxsecfN(this),i__ena(this),i__fntlcnconf(this),i__fntsatellitedsdconf(this),i__fntsrvclstconf(this),i__pow(this),i__strapi(this),i__strmfltr(this)
{
dmxsecfN	=	&i__dmxsecfN;
ena	=	&i__ena;
fntlcnconf	=	&i__fntlcnconf;
fntsatellitedsdconf	=	&i__fntsatellitedsdconf;
fntsrvclstconf	=	&i__fntsrvclstconf;
pow	=	&i__pow;
strapi	=	&i__strapi;
strmfltr	=	&i__strmfltr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define charsetutil_iPresent() (charsetutil.Present())
#define charsetutil_ExtractNone	IHsvCharSetUtility2_ExtractNone
#define charsetutil_ExtractShortName	IHsvCharSetUtility2_ExtractShortName
#define charsetutil_ExtractEITShortEvent	IHsvCharSetUtility2_ExtractEITShortEvent
#define charsetutil_ExtractEITExtendedEvent	IHsvCharSetUtility2_ExtractEITExtendedEvent
#define charsetutil_MbToWcEx(mbstr,mblen,wcstr,wclen,exinfo)	charsetutil->MbToWcEx(mbstr,mblen,wcstr,wclen,exinfo)
#define charsetutil_MbToWc(mbstr,mblen,wcstr,wclen,exinfo)	charsetutil->MbToWc(mbstr,mblen,wcstr,wclen,exinfo)
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
#define conf_BatParsing	IHsvDVBSIConfig_BatParsing
#define conf_FntParsing	IHsvDVBSIConfig_FntParsing
#define conf_FstParsing	IHsvDVBSIConfig_FstParsing
#define conf_Notifications	IHsvDVBSIConfig_Notifications
#define conf_CurrentCountry	conf->CurrentCountry()
#define conf_IsActionAllowed(dmx,table)	conf->IsActionAllowed(dmx,table)
#define ctrlN_iPresent() (ctrlN.Present())
#define ctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define ctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define ctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define ctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define ctrlN_FST	IHsvSdmControlNotifyEx_FST
#define ctrlN_OnEvent(dmx,eventid,value)	ctrlN->OnEvent(dmx,eventid,value)
#define pakgins_iPresent() (pakgins.Present())
#define pakgins_ManualInstallLnb	IHsvSatellitePackageInstallation_ManualInstallLnb
#define pakgins_ManualInstallFreq	IHsvSatellitePackageInstallation_ManualInstallFreq
#define pakgins_ManualInstallPolaraization	IHsvSatellitePackageInstallation_ManualInstallPolaraization
#define pakgins_ManualInstallSymRate	IHsvSatellitePackageInstallation_ManualInstallSymRate
#define pakgins_ManualInstallSymRateMode	IHsvSatellitePackageInstallation_ManualInstallSymRateMode
#define pakgins_ManualInstallModulation	IHsvSatellitePackageInstallation_ManualInstallModulation
#define pakgins_GetCurrentInstallationState(mode,state)	pakgins->GetCurrentInstallationState(mode,state)
#define pakgins_StartInstallation(Source,Lnb,Mode)	pakgins->StartInstallation(Source,Lnb,Mode)
#define pakgins_StopInstallation()	pakgins->StopInstallation()
#define pakgins_WriteBarkerMuxData()	pakgins->WriteBarkerMuxData()
#define pakgins_GetNumberOfTvChannelsFound(Mode,Lnb)	pakgins->GetNumberOfTvChannelsFound(Mode,Lnb)
#define pakgins_GetNumberofRadioChannelsFound(Mode,Lnb)	pakgins->GetNumberofRadioChannelsFound(Mode,Lnb)
#define pakgins_GetNumberOfTvChannelsRemoved(Mode,Lnb)	pakgins->GetNumberOfTvChannelsRemoved(Mode,Lnb)
#define pakgins_GetNumberofRadioChannelsRemoved(Mode,Lnb)	pakgins->GetNumberofRadioChannelsRemoved(Mode,Lnb)
#define pakgins_GetNumberOfDigitalChannelsAdded()	pakgins->GetNumberOfDigitalChannelsAdded()
#define pakgins_GetNumberOfDigitalChannelsRemoved()	pakgins->GetNumberOfDigitalChannelsRemoved()
#define pakgins_GetNumberOfDigitalChannelsMoved()	pakgins->GetNumberOfDigitalChannelsMoved()
#define pakgins_LoadManualInstallationDefaultValues()	pakgins->LoadManualInstallationDefaultValues()
#define pakgins_StoreManualInstallationValues()	pakgins->StoreManualInstallationValues()
#define pakgins_SetManualInstallationAttributes(AttributeId,Value)	pakgins->SetManualInstallationAttributes(AttributeId,Value)
#define pakgins_GetAttribute(Mode,AttributeId)	pakgins->GetAttribute(Mode,AttributeId)
#define pakgins_GetScanProgressStatus(Mode)	pakgins->GetScanProgressStatus(Mode)
#define pakgins_GetSIDetails(SiValues)	pakgins->GetSIDetails(SiValues)
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
#define srtdb_iPresent() (srtdb.Present())
#define srtdb_OperatorEqual	IHsvSortedTable2_OperatorEqual
#define srtdb_OperatorSmaller	IHsvSortedTable2_OperatorSmaller
#define srtdb_OperatorGreater	IHsvSortedTable2_OperatorGreater
#define srtdb_GetNoOfRecords(tableid)	srtdb->GetNoOfRecords(tableid)
#define srtdb_Init(tableid)	srtdb->Init(tableid)
#define srtdb_Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)	srtdb->Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)
#define srtdb_SearchOnPrimaryKey(tableid,PrimaryKey,from,to)	srtdb->SearchOnPrimaryKey(tableid,PrimaryKey,from,to)
#define srtdb_SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)	srtdb->SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)
#define srtdb_QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_QueryOnIndex(tableid,index,data)	srtdb->QueryOnIndex(tableid,index,data)
#define srtdb_SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)	srtdb->SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)
#define srtdb_SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)	srtdb->SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)
#define srtdbids_FntLcnTable	 reinterpret_cast<int>(&i__fntlcnconf)
#define srtdbids_FntSatelliteDS	 reinterpret_cast<int>(&i__fntsatellitedsdconf)
#define srtdbids_FntSrvclstTable	 reinterpret_cast<int>(&i__fntsrvclstconf)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
#define fntlcnconf_MaxElements	i__fntlcnconf.m_MaxElements
#define fntlcnconf_ElementSize	i__fntlcnconf.m_ElementSize
#define fntlcnconf_ThreadSafe	i__fntlcnconf.m_ThreadSafe
#define fntlcnconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define fntlcnconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define fntlcnconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define fntlcnconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define fntlcnconf_SortCriteria	i__fntlcnconf.m_SortCriteria
#define fntlcnconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define fntlcnconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define fntlcnconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define fntsatellitedsdconf_MaxElements	i__fntsatellitedsdconf.m_MaxElements
#define fntsatellitedsdconf_ElementSize	i__fntsatellitedsdconf.m_ElementSize
#define fntsatellitedsdconf_ThreadSafe	i__fntsatellitedsdconf.m_ThreadSafe
#define fntsatellitedsdconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define fntsatellitedsdconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define fntsatellitedsdconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define fntsatellitedsdconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define fntsatellitedsdconf_SortCriteria	i__fntsatellitedsdconf.m_SortCriteria
#define fntsatellitedsdconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define fntsatellitedsdconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define fntsatellitedsdconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define fntsrvclstconf_MaxElements	i__fntsrvclstconf.m_MaxElements
#define fntsrvclstconf_ElementSize	i__fntsrvclstconf.m_ElementSize
#define fntsrvclstconf_ThreadSafe	i__fntsrvclstconf.m_ThreadSafe
#define fntsrvclstconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define fntsrvclstconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define fntsrvclstconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define fntsrvclstconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define fntsrvclstconf_SortCriteria	i__fntsrvclstconf.m_SortCriteria
#define fntsrvclstconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define fntsrvclstconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define fntsrvclstconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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

