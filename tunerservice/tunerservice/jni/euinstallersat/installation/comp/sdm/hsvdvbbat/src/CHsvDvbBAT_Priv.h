#ifndef  _CHSVDVBBAT_PRIV_H
#define  _CHSVDVBBAT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControl2.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvSatSystemSettings.h>
#include <IHsvSatelliteSettings.h>
#include <CS2MwBase.h>

class CHsvDvbBAT_Priv;
#define CLASSSCOPE CHsvDvbBAT_Priv::
#include "locals_m.h"

class CHsvDvbBAT_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbBAT_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batDetailsconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batECNconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batlcn2conf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batlcnconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batlinkmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batsrvclstmainconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batFreesatSrvGroupconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batFreesatInfoLocationconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batFreesatLCNconf);

IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batLCNV2conf);
IHsvSortedTableConfigurationExImpl(CHsvDvbBAT_Priv,batMulLCNV2conf);
IHsvDemuxSectionFilterNotifyImpl(CHsvDvbBAT_Priv,dmxsecfN);
IHsvSdmEnableImpl(CHsvDvbBAT_Priv,ena);
IHsvPowerImpl(CHsvDvbBAT_Priv,pow);
IHsvStreamImpl(CHsvDvbBAT_Priv,strapi);
public:
ProvidesInterface<IHsvSortedTableConfigurationEx>	batDetailsconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batECNconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batlcn2conf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batlcnconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batlinkmainconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batsrvclstmainconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batFreesatSrvGroupconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batFreesatInfoLocationconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batFreesatLCNconf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batLCNV2conf;
ProvidesInterface<IHsvSortedTableConfigurationEx>	batMulLCNV2conf;
ProvidesInterface<IHsvDemuxSectionFilterNotify>		dmxsecfN;
ProvidesInterface<IHsvSdmEnable>					ena;
ProvidesInterface<IHsvPower>						pow;
ProvidesInterface<IHsvStream>						strapi;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtilityEx>				charsetutil;
RequiresInterface<IHsvDVBSIConfig>					conf;
RequiresInterface<IHsvSdmControl2>					ctrl;
RequiresInterface<IHsvSdmControlNotifyEx>			ctrlN;
RequiresInterface<IHsvSatelliteInstallation>		ins;
RequiresInterface<IHsvDemuxSectionFilter2>			sec;
RequiresInterface<IHsvSortedTable2>					srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>			srtdbids;
RequiresInterface<IHsvStreamNotify>					strapiN;
RequiresInterface<IHsvSatSystemSettings> 			sysset;
RequiresInterface<IHsvSatelliteSettings> 			itricolorsettings;

private:
DEMUX_DEFINES(CHsvDvbBAT_Priv,sec);

public:
CHsvDvbBAT_Priv():i__batDetailsconf(this),i__batECNconf(this),i__batlcn2conf(this),i__batlcnconf(this),i__batlinkmainconf(this),i__batsrvclstmainconf(this),i__dmxsecfN(this),i__ena(this),i__pow(this),i__strapi(this),i__batLCNV2conf(this),i__batFreesatSrvGroupconf(this),i__batFreesatInfoLocationconf(this),i__batFreesatLCNconf(this),i__batMulLCNV2conf(this)
{
batDetailsconf	=	&i__batDetailsconf;
batECNconf	=	&i__batECNconf;
batlcn2conf	=	&i__batlcn2conf;
batlcnconf	=	&i__batlcnconf;
batlinkmainconf	=	&i__batlinkmainconf;
batsrvclstmainconf	=	&i__batsrvclstmainconf;

batFreesatSrvGroupconf = &i__batFreesatSrvGroupconf;
batFreesatInfoLocationconf = &i__batFreesatInfoLocationconf;
batFreesatLCNconf = &i__batFreesatLCNconf;

batLCNV2conf =	&i__batLCNV2conf;
batMulLCNV2conf = &i__batMulLCNV2conf;
dmxsecfN	=	&i__dmxsecfN;
ena	=	&i__ena;
pow	=	&i__pow;
strapi	=	&i__strapi;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define charsetutil_iPresent() (charsetutil.Present())
#define charsetutil_MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName)	charsetutil->MbToWcEx(mbstr,mblen,wcstr,wclen,ExtractShortName)
#define charsetutil_MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName)	charsetutil->MbToWc(mbstr,mblen,wcstr,wclen,ExtractShortName)
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
#define ctrl_iPresent() (ctrl.Present())
#define ctrl_Idle	IHsvSdmControl2_Idle
#define ctrl_Minimal	IHsvSdmControl2_Minimal
#define ctrl_Normal	IHsvSdmControl2_Normal
#define ctrl_External	IHsvSdmControl2_External
#define ctrl_CrossCarraige	IHsvSdmControl2_CrossCarraige
#define ctrl_NormalPlusPmt	IHsvSdmControl2_NormalPlusPmt
#define ctrl_M7Minimal	IHsvSdmControl2_M7Minimal
#define ctrl_HomingMuxData	IHsvSdmControl2_HomingMuxData
#define ctrl_PkgBuildMode	IHsvSdmControl2_PkgBuildMode
#define ctrl_FransatNormal	IHsvSdmControl2_FransatNormal
#define ctrl_MinimalPlusBat	IHsvSdmControl2_MinimalPlusBat
#define ctrl_FreesatNormal IHsvSdmControl2_FreesatNormal
#define ctrl_FreesatMinimalNitAct IHsvSdmControl2_FreesatMinimalNitAct
#define ctrl_FreesatPostcode IHsvSdmControl2_FreesatPostcode
#define ctrl_TricolorNormal IHsvSdmControl2_TricolorNormal
#define ctrl_Invalid	IHsvSdmControl2_Invalid
#define ctrl_NoDataAvailable	IHsvSdmControl2_NoDataAvailable
#define ctrl_OnlyPsiDataAvailable	IHsvSdmControl2_OnlyPsiDataAvailable
#define ctrl_SiDataAvailable	IHsvSdmControl2_SiDataAvailable
#define ctrl_NITAvailable	IHsvSdmControl2_NITAvailable
#define ctrl_SDTAvailable	IHsvSdmControl2_SDTAvailable
#define ctrl_FNTAvailable	IHsvSdmControl2_FNTAvailable
#define ctrl_FSTAvailable	IHsvSdmControl2_FSTAvailable
#define ctrl_BATAvailable	IHsvSdmControl2_BATAvailable
#define ctrl_GetMode(dmx)	ctrl->GetMode(dmx)
#define ctrl_GetStatus(dmx)	ctrl->GetStatus(dmx)
#define ctrl_StartCollection(dmx,mode)	ctrl->StartCollection(dmx,mode)
#define ctrl_StopCollection(dmx)	ctrl->StopCollection(dmx)
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
#define sysset_GetSystemLanguage()	sysset->GetSystemLanguage()
#define itricolorsettings_GetAttribute(AttributeId)			itricolorsettings->GetAttribute(AttributeId)
#define itricolorsettings_SetAttribute(AttributeId, Value)	itricolorsettings->SetAttribute(AttributeId, Value)
#define idvbset_AttributeTricolorRegionNameData 			IHsvSatelliteSettings_AttributeTricolorRegionNameData

#define langid_LangEnglish      IHsvLanguageIds2_LangEnglish
#define langid_LangGerman       IHsvLanguageIds2_LangGerman
#define langid_LangSwedish      IHsvLanguageIds2_LangSwedish
#define langid_LangItalian      IHsvLanguageIds2_LangItalian
#define langid_LangFrench       IHsvLanguageIds2_LangFrench
#define langid_LangSpanish      IHsvLanguageIds2_LangSpanish
#define langid_LangCzech        IHsvLanguageIds2_LangCzech
#define langid_LangPolish       IHsvLanguageIds2_LangPolish
#define langid_LangTurkish      IHsvLanguageIds2_LangTurkish
#define langid_LangRussian      IHsvLanguageIds2_LangRussian
#define langid_LangGreek        IHsvLanguageIds2_LangGreek
#define langid_LangBasque       IHsvLanguageIds2_LangBasque
#define langid_LangCatalan      IHsvLanguageIds2_LangCatalan
#define langid_LangCroatian     IHsvLanguageIds2_LangCroatian
#define langid_LangDanish       IHsvLanguageIds2_LangDanish
#define langid_LangDutch        IHsvLanguageIds2_LangDutch
#define langid_LangFinnish      IHsvLanguageIds2_LangFinnish
#define langid_LangGaelic       IHsvLanguageIds2_LangGaelic
#define langid_LangGalligan     IHsvLanguageIds2_LangGalligan
#define langid_LangNorwegian    IHsvLanguageIds2_LangNorwegian
#define langid_LangPortuguese   IHsvLanguageIds2_LangPortuguese
#define langid_LangSerbian      IHsvLanguageIds2_LangSerbian
#define langid_LangSlovak       IHsvLanguageIds2_LangSlovak
#define langid_LangSlovenian    IHsvLanguageIds2_LangSlovenian
#define langid_LangWelsh        IHsvLanguageIds2_LangWelsh
#define langid_LangRomanian     IHsvLanguageIds2_LangRomanian
#define langid_LangEstonian     IHsvLanguageIds2_LangEstonian
#define langid_LangUkrainian    IHsvLanguageIds2_LangUkrainian
#define langid_LangArabic       IHsvLanguageIds2_LangArabic
#define langid_LangHebrew       IHsvLanguageIds2_LangHebrew
#define langid_LangHungarian    IHsvLanguageIds2_LangHungarian
#define langid_LangHungal       IHsvLanguageIds2_LangHungal
#define langid_LangMalay        IHsvLanguageIds2_LangMalay
#define langid_LangPersian      IHsvLanguageIds2_LangPersian
#define langid_LangSimplifiedchinese    IHsvLanguageIds2_LangSimplifiedchinese
#define langid_LangTaiwanese    IHsvLanguageIds2_LangTaiwanese
#define langid_LangBrazilianPortuguese  IHsvLanguageIds2_LangBrazilianPortuguese
#define langid_LangBulgarian    IHsvLanguageIds2_LangBulgarian
#define langid_LangLatinspanish IHsvLanguageIds2_LangLatinspanish
#define langid_LangLithuanian   IHsvLanguageIds2_LangLithuanian
#define langid_LangLatvian      IHsvLanguageIds2_LangLatvian
#define langid_LangKazakh       IHsvLanguageIds2_LangKazakh
#define langid_LangThai IHsvLanguageIds2_LangThai
#define langid_LangIrish        IHsvLanguageIds2_LangIrish
#define langid_LangUndefined    IHsvLanguageIds2_LangUndefined
#define langid_LangOriginalVersion      IHsvLanguageIds2_LangOriginalVersion
#define langid_LangAudioDescription     IHsvLanguageIds2_LangAudioDescription
#define langid_LangNone IHsvLanguageIds2_LangNone


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
#define srtdbids_BatLcnTable	 reinterpret_cast<int>(&i__batlcnconf)
#define srtdbids_BatLcn2Table	 reinterpret_cast<int>(&i__batlcn2conf)
#define srtdbids_BatLinkageInfoMain	 reinterpret_cast<int>(&i__batlinkmainconf)
#define srtdbids_BatSrvclstTableMain	 reinterpret_cast<int>(&i__batsrvclstmainconf)
#define srtdbids_BatDetailsTable	 reinterpret_cast<int>(&i__batDetailsconf)
#define srtdbids_BatECNTable	 reinterpret_cast<int>(&i__batECNconf)
#define srtdbids_BatFreesatSrvGroupTable	 reinterpret_cast<int>(&i__batFreesatSrvGroupconf)
#define srtdbids_BatFreesatInfoLocationTable	 reinterpret_cast<int>(&i__batFreesatInfoLocationconf)
#define srtdbids_BatFreesatLCNTable	 reinterpret_cast<int>(&i__batFreesatLCNconf)
#define srtdbids_BatLCNV2Table	 reinterpret_cast<int>(&i__batLCNV2conf)
#define srtdbids_BatMulLCNV2Table	 reinterpret_cast<int>(&i__batMulLCNV2conf)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
#define batDetailsconf_MaxElements	i__batDetailsconf.m_MaxElements
#define batDetailsconf_ElementSize	i__batDetailsconf.m_ElementSize
#define batDetailsconf_ThreadSafe	i__batDetailsconf.m_ThreadSafe
#define batDetailsconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batDetailsconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batDetailsconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batDetailsconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batDetailsconf_SortCriteria	i__batDetailsconf.m_SortCriteria
#define batDetailsconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batDetailsconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batDetailsconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define batECNconf_MaxElements	i__batECNconf.m_MaxElements
#define batECNconf_ElementSize	i__batECNconf.m_ElementSize
#define batECNconf_ThreadSafe	i__batECNconf.m_ThreadSafe
#define batECNconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batECNconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batECNconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batECNconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batECNconf_SortCriteria	i__batECNconf.m_SortCriteria
#define batECNconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batECNconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batECNconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

#define batFreesatSrvGroupconf_MaxElements	i__batFreesatSrvGroupconf.m_MaxElements
#define batFreesatSrvGroupconf_ElementSize	i__batFreesatSrvGroupconf.m_ElementSize
#define batFreesatSrvGroupconf_ThreadSafe	i__batFreesatSrvGroupconf.m_ThreadSafe
#define batFreesatSrvGroupconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batFreesatSrvGroupconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batFreesatSrvGroupconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batFreesatSrvGroupconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batFreesatSrvGroupconf_SortCriteria	i__batFreesatSrvGroupconf.m_SortCriteria
#define batFreesatSrvGroupconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batFreesatSrvGroupconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batFreesatSrvGroupconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

#define batFreesatInfoLocationconf_MaxElements	i__batFreesatInfoLocationconf.m_MaxElements
#define batFreesatInfoLocationconf_ElementSize	i__batFreesatInfoLocationconf.m_ElementSize
#define batFreesatInfoLocationconf_ThreadSafe	i__batFreesatInfoLocationconf.m_ThreadSafe
#define batFreesatInfoLocationconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batFreesatInfoLocationconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batFreesatInfoLocationconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batFreesatInfoLocationconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batFreesatInfoLocationconf_SortCriteria	i__batFreesatInfoLocationconf.m_SortCriteria
#define batFreesatInfoLocationconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batFreesatInfoLocationconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batFreesatInfoLocationconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

#define batFreesatLCNconf_MaxElements	i__batFreesatLCNconf.m_MaxElements
#define batFreesatLCNconf_ElementSize	i__batFreesatLCNconf.m_ElementSize
#define batFreesatLCNconf_ThreadSafe	i__batFreesatLCNconf.m_ThreadSafe
#define batFreesatLCNconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batFreesatLCNconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batFreesatLCNconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batFreesatLCNconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batFreesatLCNconf_SortCriteria	i__batFreesatLCNconf.m_SortCriteria
#define batFreesatLCNconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batFreesatLCNconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batFreesatLCNconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

#define batlcn2conf_MaxElements	i__batlcn2conf.m_MaxElements
#define batlcn2conf_ElementSize	i__batlcn2conf.m_ElementSize
#define batlcn2conf_ThreadSafe	i__batlcn2conf.m_ThreadSafe
#define batlcn2conf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batlcn2conf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batlcn2conf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batlcn2conf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batlcn2conf_SortCriteria	i__batlcn2conf.m_SortCriteria
#define batlcn2conf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batlcn2conf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batlcn2conf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define batLCNV2conf_MaxElements	i__batLCNV2conf.m_MaxElements
#define batLCNV2conf_ElementSize	i__batLCNV2conf.m_ElementSize
#define batLCNV2conf_ThreadSafe	i__batLCNV2conf.m_ThreadSafe
#define batLCNV2conf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batLCNV2conf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batLCNV2conf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batLCNV2conf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batLCNV2conf_SortCriteria	i__batLCNV2conf.m_SortCriteria
#define batLCNV2conf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batLCNV2conf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batLCNV2conf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

#define batMulLCNV2conf_MaxElements	i__batMulLCNV2conf.m_MaxElements
#define batMulLCNV2conf_ElementSize	i__batMulLCNV2conf.m_ElementSize
#define batMulLCNV2conf_ThreadSafe	i__batMulLCNV2conf.m_ThreadSafe
#define batMulLCNV2conf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batMulLCNV2conf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batMulLCNV2conf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batMulLCNV2conf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batMulLCNV2conf_SortCriteria	i__batMulLCNV2conf.m_SortCriteria
#define batMulLCNV2conf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batMulLCNV2conf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batMulLCNV2conf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey

#define batlcnconf_MaxElements	i__batlcnconf.m_MaxElements
#define batlcnconf_ElementSize	i__batlcnconf.m_ElementSize
#define batlcnconf_ThreadSafe	i__batlcnconf.m_ThreadSafe
#define batlcnconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batlcnconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batlcnconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batlcnconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batlcnconf_SortCriteria	i__batlcnconf.m_SortCriteria
#define batlcnconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batlcnconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batlcnconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define batlinkmainconf_MaxElements	i__batlinkmainconf.m_MaxElements
#define batlinkmainconf_ElementSize	i__batlinkmainconf.m_ElementSize
#define batlinkmainconf_ThreadSafe	i__batlinkmainconf.m_ThreadSafe
#define batlinkmainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batlinkmainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batlinkmainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batlinkmainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batlinkmainconf_SortCriteria	i__batlinkmainconf.m_SortCriteria
#define batlinkmainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batlinkmainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batlinkmainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define batsrvclstmainconf_MaxElements	i__batsrvclstmainconf.m_MaxElements
#define batsrvclstmainconf_ElementSize	i__batsrvclstmainconf.m_ElementSize
#define batsrvclstmainconf_ThreadSafe	i__batsrvclstmainconf.m_ThreadSafe
#define batsrvclstmainconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define batsrvclstmainconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define batsrvclstmainconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define batsrvclstmainconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define batsrvclstmainconf_SortCriteria	i__batsrvclstmainconf.m_SortCriteria
#define batsrvclstmainconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define batsrvclstmainconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define batsrvclstmainconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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

