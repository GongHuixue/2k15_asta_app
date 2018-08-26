#ifndef  _CHSVSIMPLEMPEGDATAMANAGER_PRIV_H
#define  _CHSVSIMPLEMPEGDATAMANAGER_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IPumpEngine.h>
#include <IPumpExSub.h>
#include <IHsvSdmDiv.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvSdmSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <CS2MwBase.h>
class CHsvSimpleMpegDataManager_Priv;
#define CLASSSCOPE CHsvSimpleMpegDataManager_Priv::
#include "locals_m.h"

class CHsvSimpleMpegDataManager_Priv : public CS2MwBase
{
public:
virtual ~CHsvSimpleMpegDataManager_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSdmEnableImpl(CHsvSimpleMpegDataManager_Priv,enable);
IHsvPowerImpl(CHsvSimpleMpegDataManager_Priv,pow);
IHsvStreamImpl(CHsvSimpleMpegDataManager_Priv,simplepatstrapi);
IHsvSortedTableConfigurationExImpl(CHsvSimpleMpegDataManager_Priv,simplepmtinfoaux);
IHsvSortedTableConfigurationExImpl(CHsvSimpleMpegDataManager_Priv,simplepmtinfomain);
IHsvSortedTableConfigurationExImpl(CHsvSimpleMpegDataManager_Priv,simplepmtFreesatTunnelledInfo);
IHsvStreamImpl(CHsvSimpleMpegDataManager_Priv,simplepmtstrapi);
public:
ProvidesInterface<IHsvSdmEnable>	enable;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	simplepatstrapi;

ProvidesInterface<IHsvSortedTableConfigurationEx>	simplepmtinfoaux;

ProvidesInterface<IHsvSortedTableConfigurationEx>	simplepmtinfomain;
ProvidesInterface<IHsvSortedTableConfigurationEx>	simplepmtFreesatTunnelledInfo;

ProvidesInterface<IHsvStream>	simplepmtstrapi;

//Required interfaces
public:
RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSdmDiv>	sdmdiv;
RequiresInterface<IHsvDemuxSectionFilter2>	sec;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvSdmSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvSatelliteInstallation>		ins;
private:
Pumpdefines(CHsvSimpleMpegDataManager_Priv);
DEMUX_DEFINES(CHsvSimpleMpegDataManager_Priv,sec);

public:
CHsvSimpleMpegDataManager_Priv():i__enable(this),i__pow(this),i__simplepatstrapi(this),i__simplepmtinfoaux(this),i__simplepmtinfomain(this),i__simplepmtstrapi(this),i__simplepmtFreesatTunnelledInfo(this)
{
enable	=	&i__enable;
pow	=	&i__pow;
simplepatstrapi	=	&i__simplepatstrapi;
simplepmtinfoaux	=	&i__simplepmtinfoaux;
simplepmtinfomain	=	&i__simplepmtinfomain;
simplepmtFreesatTunnelledInfo = &i__simplepmtFreesatTunnelledInfo;
simplepmtstrapi	=	&i__simplepmtstrapi;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
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
#define ctrlN_Postcode	IHsvSdmControlNotifyEx_Postcode
#define ctrlN_OnEvent(dmx,eventid,value)	ctrlN->OnEvent(dmx,eventid,value)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvSimpleMpegDataManager_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define sdmdiv_iPresent() (sdmdiv.Present())
#define sdmdiv_NoOfVirtualChannels(medium)	sdmdiv->NoOfVirtualChannels(medium)
#define sdmdiv_NoOfDescriptors	sdmdiv->NoOfDescriptors()
#define sdmdiv_NoOfEvents	sdmdiv->NoOfEvents()
#define sdmdiv_SdmWaitTime	sdmdiv->SdmWaitTime()
#define sdmdiv_MaxStringLength	sdmdiv->MaxStringLength()
#define sdmdiv_DataCollectionTimeout	sdmdiv->DataCollectionTimeout()
#define sdmdiv_RRTParsingAllowed	sdmdiv->RRTParsingAllowed()
#define sdmdiv_SystemTime	sdmdiv->SystemTime()
#define sdmdiv_RatingStringLength	sdmdiv->RatingStringLength()
#define sdmdiv_Enable12hourEitParsing	sdmdiv->Enable12hourEitParsing()
#define sdmdiv_MaxPmtMonitors	sdmdiv->MaxPmtMonitors()
#define sdmdiv_ChannelNameLength	sdmdiv->ChannelNameLength()
#define sdmdiv_SystemLanguage	sdmdiv->SystemLanguage()
#define sdmdiv_MaxSimplePmtFilterSupported	sdmdiv->MaxSimplePmtFilterSupported()
#define sdmdiv_MaxSimplePmtSupported	sdmdiv->MaxSimplePmtSupported()
#define sdmdiv_ForceLCNSyntax(medium)	sdmdiv->ForceLCNSyntax(medium)
#define sdmdiv_EnableCountryFallbackForLCNSyntax(medium)	sdmdiv->EnableCountryFallbackForLCNSyntax(medium)
#define sdmdiv_EnableONIDFallbackForLCNSyntax(medium)	sdmdiv->EnableONIDFallbackForLCNSyntax(medium)
#define sdmdiv_AcceptedStreamType(medium,StreamType)	sdmdiv->AcceptedStreamType(medium,StreamType)
#define sdmdiv_IsMpeg4STBoltOnSupported()	sdmdiv->IsMpeg4STBoltOnSupported()
#define sdmdiv_IsAc3AudioSupported()	sdmdiv->IsAc3AudioSupported()
#define sdmdiv_ReapplyChildLockOnEventChange()	sdmdiv->ReapplyChildLockOnEventChange()
#define sdmdiv_IsAVCDescriptorSupported()	sdmdiv->IsAVCDescriptorSupported()
#define ins_iPresent() (ins.Present())
#define ins_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define ins_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define ins_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define ins_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define ins_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define ins_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define ins_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define ins_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define ins_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define ins_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define ins_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define ins_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define ins_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
#define ins_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define ins_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define ins_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define ins_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define ins_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define ins_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define ins_AttributeRegionIndex	IHsvSatelliteInstallation_AttributeRegionIndex
#define ins_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define ins_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define ins_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define ins_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define ins_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define ins_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define ins_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define ins_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define ins_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define ins_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define ins_GetCurrentInstallationState(mode,state)	ins->GetCurrentInstallationState(mode,state)
#define ins_StartInstallation(Source,Lnb,Mode)	ins->StartInstallation(Source,Lnb,Mode)
#define ins_StopInstallation()	ins->StopInstallation()
#define ins_ResetInstallation()	ins->ResetInstallation()
#define ins_GetNumberOfTvChannelsFound(Lnb)	ins->GetNumberOfTvChannelsFound(Lnb)
#define ins_GetNumberofRadioChannelsFound(Lnb)	ins->GetNumberofRadioChannelsFound(Lnb)
#define ins_GetNumberOfTvChannelsRemoved(Lnb)	ins->GetNumberOfTvChannelsRemoved(Lnb)
#define ins_GetNumberofRadioChannelsRemoved(Lnb)	ins->GetNumberofRadioChannelsRemoved(Lnb)
#define ins_GetSatelliteName(Lnb,SatelliteName)	ins->GetSatelliteName(Lnb,SatelliteName)
#define ins_GetNumberOfDigitalChannelsAdded()	ins->GetNumberOfDigitalChannelsAdded()
#define ins_GetNumberOfDigitalChannelsRemoved()	ins->GetNumberOfDigitalChannelsRemoved()
#define ins_GetNumberOfDigitalChannelsMoved()	ins->GetNumberOfDigitalChannelsMoved()
#define ins_IdentifyPackagesAvailable()	ins->IdentifyPackagesAvailable()
#define ins_GetTotalNumberOfPackagesFound()	ins->GetTotalNumberOfPackagesFound()
#define ins_GetPackageByIndex(Index,Package)	ins->GetPackageByIndex(Index,Package)
#define ins_SetUserPackageIndex(PackageIndex)	ins->SetUserPackageIndex(PackageIndex)
#define ins_GetUserPackageIndex(PackageIndex,IsPackage)	ins->GetUserPackageIndex(PackageIndex,IsPackage)
#define ins_GetInstalledSatellites(mode,SatelliteEntries)	ins->GetInstalledSatellites(mode,SatelliteEntries)
#define ins_InstallAddedSatellites()	ins->InstallAddedSatellites()
#define ins_ResetAddedSatellites()	ins->ResetAddedSatellites()
#define ins_RemoveSatelliteEntry(LnbNumber)	ins->RemoveSatelliteEntry(LnbNumber)
#define ins_GetSatelliteSignalStrength(LnbNumber)	ins->GetSatelliteSignalStrength(LnbNumber)
#define ins_GetSatelliteSignalQuality(LnbNumber)	ins->GetSatelliteSignalQuality(LnbNumber)
#define ins_LoadManualInstallationDefaultValues()	ins->LoadManualInstallationDefaultValues()
#define ins_StoreManualInstallationValues()	ins->StoreManualInstallationValues()
#define ins_GetAttribute(Mode,AttributeId)	ins->GetAttribute(Mode,AttributeId)
#define ins_SetAttribute(Mode,AttributeId,Value)	ins->SetAttribute(Mode,AttributeId,Value)
#define ins_GetScanProgressStatus(Mode)	ins->GetScanProgressStatus(Mode)
#define ins_GetSITableIds(NetworkID,BouquetID)	ins->GetSITableIds(NetworkID,BouquetID)
#define ins_GetPackageName(PackageId,PackageName)	ins->GetPackageName(PackageId,PackageName)
#define ins_GetSIDetails(SiValues)	ins->GetSIDetails(SiValues)
#define ins_EnableUnicable(LnbNumber,Enable)	ins->EnableUnicable(LnbNumber,Enable)
#define ins_StopSignalStrengthMeas(LnbNumber)	ins->StopSignalStrengthMeas(LnbNumber)
#define ins_GetSignalQuality(Param)	ins->GetSignalQuality(Param)
#define ins_StartSignalStrengthMeas(LnbNumber)	ins->StartSignalStrengthMeas(LnbNumber)
#define ins_GetSignalStrength(param)	ins->GetSignalStrength(param)
#define ins_StartPredefinedListCopy()	ins->StartPredefinedListCopy()
#define ins_GetFirstInstalledChannel()	ins->GetFirstInstalledChannel()
#define ins_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	ins->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define ins_StartTricolorRegionParsing()	ins->StartTricolorRegionParsing()
#define ins_SetTricolorRegionIndex()	ins->SetTricolorRegionIndex()
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
#define srtdbids_SimplePmtMain	 reinterpret_cast<int>(&i__simplepmtinfomain)
#define srtdbids_SimplePmtAux	 reinterpret_cast<int>(&i__simplepmtinfoaux)
#define srtdbids_SimplepmtFreesatTunnelledInfo	 reinterpret_cast<int>(&i__simplepmtFreesatTunnelledInfo)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
#define simplepmtinfoaux_MaxElements	i__simplepmtinfoaux.m_MaxElements
#define simplepmtinfoaux_ElementSize	i__simplepmtinfoaux.m_ElementSize
#define simplepmtinfoaux_ThreadSafe	i__simplepmtinfoaux.m_ThreadSafe
#define simplepmtinfoaux_Primary	IHsvSortedTableConfigurationEx_Primary
#define simplepmtinfoaux_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define simplepmtinfoaux_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define simplepmtinfoaux_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define simplepmtinfoaux_SortCriteria	i__simplepmtinfoaux.m_SortCriteria
#define simplepmtinfoaux_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define simplepmtinfoaux_Equal	IHsvSortedTableConfigurationEx_Equal
#define simplepmtinfoaux_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define simplepmtinfomain_MaxElements	i__simplepmtinfomain.m_MaxElements
#define simplepmtinfomain_ElementSize	i__simplepmtinfomain.m_ElementSize
#define simplepmtinfomain_ThreadSafe	i__simplepmtinfomain.m_ThreadSafe
#define simplepmtinfomain_Primary	IHsvSortedTableConfigurationEx_Primary
#define simplepmtinfomain_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define simplepmtinfomain_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define simplepmtinfomain_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define simplepmtinfomain_SortCriteria	i__simplepmtinfomain.m_SortCriteria
#define simplepmtinfomain_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define simplepmtinfomain_Equal	IHsvSortedTableConfigurationEx_Equal
#define simplepmtinfomain_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define simplepmtFreesatTunnelledInfo_MaxElements	i__simplepmtFreesatTunnelledInfo.m_MaxElements
#define simplepmtFreesatTunnelledInfo_ElementSize	i__simplepmtFreesatTunnelledInfo.m_ElementSize
#define simplepmtFreesatTunnelledInfo_ThreadSafe	i__simplepmtFreesatTunnelledInfo.m_ThreadSafe
#define simplepmtFreesatTunnelledInfo_Primary	IHsvSortedTableConfigurationEx_Primary
#define simplepmtFreesatTunnelledInfo_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define simplepmtFreesatTunnelledInfo_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define simplepmtFreesatTunnelledInfo_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define simplepmtFreesatTunnelledInfo_SortCriteria	i__simplepmtFreesatTunnelledInfo.m_SortCriteria
#define simplepmtFreesatTunnelledInfo_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define simplepmtFreesatTunnelledInfo_Equal	IHsvSortedTableConfigurationEx_Equal
#define simplepmtFreesatTunnelledInfo_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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

