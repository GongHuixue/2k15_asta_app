#ifndef  _CHSVEUROPEINSTALLATION_MDIV_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MDIV_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciDecodeDiv.h>
#include <IHsvEuropeConfiguration.h>
#include <ICesPaciDiv.h>
#include <ICesPatsDiv.h>
#include <ICesCountryIds.h>
#include <IHsvInstallation2.h>
#include <IHsvTcSystemSettings.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_mdiv_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_mdiv_Priv::
#include "locals_mdiv.h"

class CHsvEuropeInstallation_mdiv_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_mdiv_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mdiv.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvAciDecodeDivImpl(CHsvEuropeInstallation_mdiv_Priv,hsvacidec_div);
IHsvEuropeConfigurationImpl(CHsvEuropeInstallation_mdiv_Priv,ieuconfig);
ICesPaciDivImpl(CHsvEuropeInstallation_mdiv_Priv,svpaci_div);
ICesPatsDivImpl(CHsvEuropeInstallation_mdiv_Priv,svpats_div);
public:
ProvidesInterface<IHsvAciDecodeDiv>	hsvacidec_div;

ProvidesInterface<IHsvEuropeConfiguration>	ieuconfig;

ProvidesInterface<ICesPaciDiv>	svpaci_div;

ProvidesInterface<ICesPatsDiv>	svpats_div;

//Required interfaces
public:
RequiresInterface<ICesCountryIds>	icountid;
RequiresInterface<IHsvInstallation2>	pins;
RequiresInterface<IHsvTcSystemSettings>	sysset;

public:
CHsvEuropeInstallation_mdiv_Priv():i__hsvacidec_div(this),i__ieuconfig(this),i__svpaci_div(this),i__svpats_div(this)
{
hsvacidec_div	=	&i__hsvacidec_div;
ieuconfig	=	&i__ieuconfig;
svpaci_div	=	&i__svpaci_div;
svpats_div	=	&i__svpats_div;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define icountid_iPresent() (icountid.Present())
#define icountid_CountryAustria	ICesCountryIds_CountryAustria
#define icountid_CountryBelgium	ICesCountryIds_CountryBelgium
#define icountid_CountryCroatia	ICesCountryIds_CountryCroatia
#define icountid_CountryCzechrep	ICesCountryIds_CountryCzechrep
#define icountid_CountryDenmark	ICesCountryIds_CountryDenmark
#define icountid_CountryFinland	ICesCountryIds_CountryFinland
#define icountid_CountryFrance	ICesCountryIds_CountryFrance
#define icountid_CountryGermany	ICesCountryIds_CountryGermany
#define icountid_CountryGreece	ICesCountryIds_CountryGreece
#define icountid_CountryHungary	ICesCountryIds_CountryHungary
#define icountid_CountryIreland	ICesCountryIds_CountryIreland
#define icountid_CountryItaly	ICesCountryIds_CountryItaly
#define icountid_CountryLuxembourg	ICesCountryIds_CountryLuxembourg
#define icountid_CountryNetherlands	ICesCountryIds_CountryNetherlands
#define icountid_CountryNorway	ICesCountryIds_CountryNorway
#define icountid_CountryPoland	ICesCountryIds_CountryPoland
#define icountid_CountryPortugal	ICesCountryIds_CountryPortugal
#define icountid_CountryRomania	ICesCountryIds_CountryRomania
#define icountid_CountryRussia	ICesCountryIds_CountryRussia
#define icountid_CountrySerbia	ICesCountryIds_CountrySerbia
#define icountid_CountrySlovakia	ICesCountryIds_CountrySlovakia
#define icountid_CountrySlovenia	ICesCountryIds_CountrySlovenia
#define icountid_CountrySpain	ICesCountryIds_CountrySpain
#define icountid_CountrySweden	ICesCountryIds_CountrySweden
#define icountid_CountrySwitzerland	ICesCountryIds_CountrySwitzerland
#define icountid_CountryTurkey	ICesCountryIds_CountryTurkey
#define icountid_CountryUK	ICesCountryIds_CountryUK
#define icountid_CountryOther	ICesCountryIds_CountryOther
#define icountid_CountryAustralia	ICesCountryIds_CountryAustralia
#define icountid_CountryEstonia	ICesCountryIds_CountryEstonia
#define icountid_CountryLithuania	ICesCountryIds_CountryLithuania
#define icountid_CountryLatvia	ICesCountryIds_CountryLatvia
#define icountid_CountryKazakhstan	ICesCountryIds_CountryKazakhstan
#define icountid_CountryBulgaria	ICesCountryIds_CountryBulgaria
#define icountid_CountryChina	ICesCountryIds_CountryChina
#define icountid_CountryUkraine	ICesCountryIds_CountryUkraine
#define icountid_CountryBrazil	ICesCountryIds_CountryBrazil
#define icountid_CountryArgentina	ICesCountryIds_CountryArgentina
#define icountid_CountryAlbania	ICesCountryIds_CountryAlbania
#define icountid_CountryArmenia	ICesCountryIds_CountryArmenia
#define icountid_CountryAzerbaijan	ICesCountryIds_CountryAzerbaijan
#define icountid_CountryBelarus	ICesCountryIds_CountryBelarus
#define icountid_CountryBosniaAndHerzegovina	ICesCountryIds_CountryBosniaAndHerzegovina
#define icountid_CountryGeorgia	ICesCountryIds_CountryGeorgia
#define icountid_CountryMontenegro	ICesCountryIds_CountryMontenegro
#define icountid_CountryIsrael	ICesCountryIds_CountryIsrael
#define icountid_CountryMacedoniafyrom	ICesCountryIds_CountryMacedoniafyrom
#define cids_CountryParaguay	IHsvCountryIds_CountryParaguay
#define cids_CountryUruguay	IHsvCountryIds_CountryUruguay
#define cids_CountryThailand	IHsvCountryIds_CountryThailand
#define cids_CountryNewZealand	IHsvCountryIds_CountryNewZealand
#define cids_CountrySingapore	IHsvCountryIds_CountrySingapore
#define cids_CountryMalaysia	IHsvCountryIds_CountryMalaysia
#define cids_CountryTaiwan	IHsvCountryIds_CountryTaiwan
#define cids_CountryIndonesia	IHsvCountryIds_CountryIndonesia
#define cids_CountryUAE	IHsvCountryIds_CountryUAE
#define icountid_CountryMax	ICesCountryIds_CountryMax
#define icountid_CountryInvalid	ICesCountryIds_CountryInvalid
#define icountid_iVersion	icountid->iVersion()
#define pins_iPresent() (pins.Present())
#define pins_InvalidChannel	IHsvInstallation2_InvalidChannel
#define pins_InvalidFrequency	IHsvInstallation2_InvalidFrequency
#define pins_StIdle	IHsvInstallation2_StIdle
#define pins_StSourceSetupWait	IHsvInstallation2_StSourceSetupWait
#define pins_StDigital	IHsvInstallation2_StDigital
#define pins_StAnalog	IHsvInstallation2_StAnalog
#define pins_StPreSorting	IHsvInstallation2_StPreSorting
#define pins_StSorting	IHsvInstallation2_StSorting
#define pins_Terrestrial	IHsvInstallation2_Terrestrial
#define pins_Cable	IHsvInstallation2_Cable
#define pins_Satellite	IHsvInstallation2_Satellite
#define pins_InstallationInPassAnalog	IHsvInstallation2_InstallationInPassAnalog
#define pins_InstallationInDigitalPass	IHsvInstallation2_InstallationInDigitalPass
#define pins_InstallationStateScrambledSearch	IHsvInstallation2_InstallationStateScrambledSearch
#define pins_InstallationStateIdle	IHsvInstallation2_InstallationStateIdle
#define pins_InstallationStateInProgress	IHsvInstallation2_InstallationStateInProgress
#define pins_InstallationStatePaused	IHsvInstallation2_InstallationStatePaused
#define pins_InstallationModeNone	IHsvInstallation2_InstallationModeNone
#define pins_InstallationModeManual	IHsvInstallation2_InstallationModeManual
#define pins_InstallationModeAutomatic	IHsvInstallation2_InstallationModeAutomatic
#define pins_InstallationModeBackground	IHsvInstallation2_InstallationModeBackground
#define pins_InstallationModeImplicit	IHsvInstallation2_InstallationModeImplicit
#define pins_InstallationModeUpdate	IHsvInstallation2_InstallationModeUpdate
#define pins_InstallationModeWeakSignal	IHsvInstallation2_InstallationModeWeakSignal
#define pins_InstallationModeSingleChannel	IHsvInstallation2_InstallationModeSingleChannel
#define pins_InstallationModePreScan	IHsvInstallation2_InstallationModePreScan
#define pins_InstallationModeDtr	IHsvInstallation2_InstallationModeDtr
#define pins_InstallationModeCam	IHsvInstallation2_InstallationModeCam
#define pins_MaxChannel	IHsvInstallation2_MaxChannel
#define pins_ManualInstallationModeFrequency	IHsvInstallation2_ManualInstallationModeFrequency
#define pins_InsTvSystemBg	IHsvInstallation2_InsTvSystemBg
#define pins_InsTvSystemDk	IHsvInstallation2_InsTvSystemDk
#define pins_InsTvSystemI	IHsvInstallation2_InsTvSystemI
#define pins_InsTvSystemL	IHsvInstallation2_InsTvSystemL
#define pins_InsTvSystemN	IHsvInstallation2_InsTvSystemN
#define pins_InsTvSystemM	IHsvInstallation2_InsTvSystemM
#define pins_InsTvSystemAuto	IHsvInstallation2_InsTvSystemAuto
#define pins_InsColourSystemPal	IHsvInstallation2_InsColourSystemPal
#define pins_InsColurSystemSecam	IHsvInstallation2_InsColurSystemSecam
#define pins_InsColurSystemNtsc358	IHsvInstallation2_InsColurSystemNtsc358
#define pins_InsColurSystemNtsc443	IHsvInstallation2_InsColurSystemNtsc443
#define pins_InsColurSystemAuto	IHsvInstallation2_InsColurSystemAuto
#define pins_InsColurSystemInvalid	IHsvInstallation2_InsColurSystemInvalid
#define pins_InsColurSystemNtscUnknown	IHsvInstallation2_InsColurSystemNtscUnknown
#define pins_InsAssm	IHsvInstallation2_InsAssm
#define pins_InsVssm	IHsvInstallation2_InsVssm
#define pins_InsQssm	IHsvInstallation2_InsQssm
#define pins_InsSssm	IHsvInstallation2_InsSssm
#define pins_StartInstallation(source,ptc,mode)	pins->StartInstallation(source,ptc,mode)
#define pins_StopInstallation()	pins->StopInstallation()
#define pins_GetNumberOfAnalogChannelsFound()	pins->GetNumberOfAnalogChannelsFound()
#define pins_GetNumberOfDigitalChannelsFound()	pins->GetNumberOfDigitalChannelsFound()
#define pins_GetNumberOfDigitalChannelsRemoved()	pins->GetNumberOfDigitalChannelsRemoved()
#define pins_GetInstallationProgress()	pins->GetInstallationProgress()
#define pins_GetInstallationStatus()	pins->GetInstallationStatus()
#define pins_GetInstallationMode()	pins->GetInstallationMode()
#define pins_IsUpdateInstallationSupported()	pins->IsUpdateInstallationSupported()
#define pins_SetLCNSortingControl(mode)	pins->SetLCNSortingControl(mode)
#define pins_SetInstallCountry(country)	pins->SetInstallCountry(country)
#define pins_SetSystemCountry(country)	pins->SetSystemCountry(country)
#define pins_GetFirstIntalledDigitalChannel(channelno)	pins->GetFirstIntalledDigitalChannel(channelno)
#define pins_GetFirstIntalledAnalogueChannel(channelno)	pins->GetFirstIntalledAnalogueChannel(channelno)
#define pins_GetFirstIntalledRadioChannel(channelno)	pins->GetFirstIntalledRadioChannel(channelno)
#define pins_GetFirstInstalledChannel(channelno)	pins->GetFirstInstalledChannel(channelno)
#define pins_GetNetworkNameForNetworkID(networkID,NetworkName)	pins->GetNetworkNameForNetworkID(networkID,NetworkName)
#define pins_GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)	pins->GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)
#define pins_IsValidNetworkId(networkID)	pins->IsValidNetworkId(networkID)
#define pins_SetLowestNetworkId(networkID)	pins->SetLowestNetworkId(networkID)
#define pins_SetManualFrequency(frequency,offset,finetune)	pins->SetManualFrequency(frequency,offset,finetune)
#define pins_GetManualFrequency(frequency,offset,finetune)	pins->GetManualFrequency(frequency,offset,finetune)
#define pins_SetManualChannel(channel,finetune)	pins->SetManualChannel(channel,finetune)
#define pins_GetManualChannel(channel,finetune)	pins->GetManualChannel(channel,finetune)
#define pins_IsManualInstallationModeSupported(mode)	pins->IsManualInstallationModeSupported(mode)
#define pins_SetManualInstallationMode(mode)	pins->SetManualInstallationMode(mode)
#define pins_GetManualInstallationMode()	pins->GetManualInstallationMode()
#define pins_StoreManualInstallationValues(channel)	pins->StoreManualInstallationValues(channel)
#define pins_AutoStoreManualInstallationValues()	pins->AutoStoreManualInstallationValues()
#define pins_StartFrequencySearch()	pins->StartFrequencySearch()
#define pins_GetSigStrengthRange(measmode,min,max)	pins->GetSigStrengthRange(measmode,min,max)
#define pins_GetSignalstrength(measmode)	pins->GetSignalstrength(measmode)
#define pins_StoreWeakSignalInstallationChannel()	pins->StoreWeakSignalInstallationChannel()
#define pins_GetInstalledWeakSignalChannel()	pins->GetInstalledWeakSignalChannel()
#define pins_GetSignalQualityBer()	pins->GetSignalQualityBer()
#define pins_IsFrequencySearchDirectionSupported(searchup)	pins->IsFrequencySearchDirectionSupported(searchup)
#define pins_SetFrequencySearchDirection(searchup)	pins->SetFrequencySearchDirection(searchup)
#define pins_GetFrequencySearchDirection()	pins->GetFrequencySearchDirection()
#define pins_GetMinFrequency()	pins->GetMinFrequency()
#define pins_GetMaxFrequency()	pins->GetMaxFrequency()
#define pins_GetTunerFrequency()	pins->GetTunerFrequency()
#define pins_SetTunerFrequency(freq,fineTune)	pins->SetTunerFrequency(freq,fineTune)
#define pins_GetFrequency2Channel(chantbl,frequency)	pins->GetFrequency2Channel(chantbl,frequency)
#define pins_GetChannel2CarrierFrequency(chantbl,channel)	pins->GetChannel2CarrierFrequency(chantbl,channel)
#define pins_GetChannel2CentreFrequency(chantbl,channel)	pins->GetChannel2CentreFrequency(chantbl,channel)
#define pins_GetCurrentPass()	pins->GetCurrentPass()
#define pins_GetNoOfPass()	pins->GetNoOfPass()
#define pins_GetCurrentPassType()	pins->GetCurrentPassType()
#define pins_IsMediumSupported(medium)	pins->IsMediumSupported(medium)
#define pins_GetMedium()	pins->GetMedium()
#define pins_SetMedium(medium)	pins->SetMedium(medium)
#define pins_GetInstalledMedium()	pins->GetInstalledMedium()
#define pins_SetInstalledMedium(medium)	pins->SetInstalledMedium(medium)
#define pins_IsTvSystemSupported(tvsystem)	pins->IsTvSystemSupported(tvsystem)
#define pins_SetTvSystem(tvsystem)	pins->SetTvSystem(tvsystem)
#define pins_GetTvSystem()	pins->GetTvSystem()
#define pins_IsColorSystemSupported(colorsystem)	pins->IsColorSystemSupported(colorsystem)
#define pins_SetColorSystem(colorsystem)	pins->SetColorSystem(colorsystem)
#define pins_GetColorSystem()	pins->GetColorSystem()
#define pins_IsValidPTC(medium,PTC)	pins->IsValidPTC(medium,PTC)
#define pins_GetMinPTC(medium)	pins->GetMinPTC(medium)
#define pins_GetMaxPTC(medium)	pins->GetMaxPTC(medium)
#define pins_GetLastPTCFound()	pins->GetLastPTCFound()
#define pins_GetNumberOfPTCsFound()	pins->GetNumberOfPTCsFound()
#define pins_StartSigStrMeas(measmode)	pins->StartSigStrMeas(measmode)
#define pins_StopSigStrMeas(measmode)	pins->StopSigStrMeas(measmode)
#define pins_IsSignalStrengthMeasurementValid(measmode)	pins->IsSignalStrengthMeasurementValid(measmode)
#define pins_ScanNone	IHsvInstallation2_ScanNone
#define pins_ScanAnalog	IHsvInstallation2_ScanAnalog
#define pins_ScanDVBT	IHsvInstallation2_ScanDVBT
#define pins_ScanDVBC	IHsvInstallation2_ScanDVBC
#define pins_ScanDVBS	IHsvInstallation2_ScanDVBS
#define pins_AttributeScanMode	IHsvInstallation2_AttributeScanMode
#define pins_AttributeSymbolRate	IHsvInstallation2_AttributeSymbolRate
#define pins_AttributeNetworkId	IHsvInstallation2_AttributeNetworkId
#define pins_AttributeNetworkFreq	IHsvInstallation2_AttributeNetworkFreq
#define pins_AttributeModulation	IHsvInstallation2_AttributeModulation
#define pins_AttributeDigitalOption	IHsvInstallation2_AttributeDigitalOption
#define pins_AttributeFreqStepSize	IHsvInstallation2_AttributeFreqStepSize
#define pins_AttributeCity	IHsvInstallation2_AttributeCity
#define pins_AttributePrimaryRegion	IHsvInstallation2_AttributePrimaryRegion
#define pins_AttributeSecondaryRegion	IHsvInstallation2_AttributeSecondaryRegion
#define pins_AttributeTertiaryRegion	IHsvInstallation2_AttributeTertiaryRegion
#define pins_AttributeScrOrFTA	IHsvInstallation2_AttributeScrOrFTA
#define pins_AttributeNetworkOperator	IHsvInstallation2_AttributeNetworkOperator
#define pins_AttributeUpdateInstall	IHsvInstallation2_AttributeUpdateInstall
#define pins_AttributeAnalogEnabled	IHsvInstallation2_AttributeAnalogEnabled
#define pins_AttributePersistentFile	IHsvInstallation2_AttributePersistentFile
#define pins_AttributeLCNSorting	IHsvInstallation2_AttributeLCNSorting
#define pins_QuickScan	IHsvInstallation2_QuickScan
#define pins_FullScan	IHsvInstallation2_FullScan
#define pins_GridScan	IHsvInstallation2_GridScan
#define pins_AutomaticValue	IHsvInstallation2_AutomaticValue
#define pins_ManualValue	IHsvInstallation2_ManualValue
#define pins_GetAttributeRange(installationmode,attribute,minValue,maxValue)	pins->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define pins_SetAttributeMode(installationmode,attribute,attributeMode)	pins->SetAttributeMode(installationmode,attribute,attributeMode)
#define pins_SetAttribute(installationmode,attribute,value)	pins->SetAttribute(installationmode,attribute,value)
#define pins_GetAttributeMode(installationmode,attribute)	pins->GetAttributeMode(installationmode,attribute)
#define pins_GetAttribute(installationmode,attribute)	pins->GetAttribute(installationmode,attribute)
#define pins_IsAvailable(installationmode,attribute)	pins->IsAvailable(installationmode,attribute)
#define pins_ResetAttributeToDefault(installationmode,attribute)	pins->ResetAttributeToDefault(installationmode,attribute)
#define pins_ResetAttributeToPersistent(installationmode,attribute)	pins->ResetAttributeToPersistent(installationmode,attribute)
#define pins_NitNone	IHsvInstallation2_NitNone
#define pins_NitActual	IHsvInstallation2_NitActual
#define pins_NitOther	IHsvInstallation2_NitOther
#define pins_GetTargetNitType(NetworkId)	pins->GetTargetNitType(NetworkId)
#define pins_IsNetworkUpdateDetected()	pins->IsNetworkUpdateDetected()
#define pins_DVBCStepSize1	IHsvInstallation2_DVBCStepSize1
#define pins_DVBCStepSize8	IHsvInstallation2_DVBCStepSize8
#define pins_Initialise()	pins->Initialise()
#define pins_SkipInstallationScans(ScanTypes)	pins->SkipInstallationScans(ScanTypes)
#define pins_GetAltTSValues(ONID,TSID)	pins->GetAltTSValues(ONID,TSID)
#define pins_SetUserSymbolRates(installationmode,values,len)	pins->SetUserSymbolRates(installationmode,values,len)
#define pins_GetUserSymbolRates(installationmode,values,len)	pins->GetUserSymbolRates(installationmode,values,len)
#define pins_GetPredefinedSymbolRates(installationmode,values,len)	pins->GetPredefinedSymbolRates(installationmode,values,len)
#define pins_GetNetworkIDList()	pins->GetNetworkIDList()
#define pins_GetNetworkIDName(index,NetworkName)	pins->GetNetworkIDName(index,NetworkName)
#define pins_GetChannelListIDName(index,ChannelistName)	pins->GetChannelListIDName(index,ChannelistName)
#define pins_SetFavouriteNetworkID(mode,attrib,index)	pins->SetFavouriteNetworkID(mode,attrib,index)
#define pins_GetNumberOfChannelListIds()	pins->GetNumberOfChannelListIds()
#define pins_GetChannelListIdByIndex(index)	pins->GetChannelListIdByIndex(index)
#define pins_SetFavouriteChannelListId(mode,attrib,index)	pins->SetFavouriteChannelListId(mode,attrib,index)
#define pins_SetFavouriteRegion(mode,index,RegionType)	pins->SetFavouriteRegion(mode,index,RegionType)
#define pins_None	IHsvInstallation2_None
#define pins_Ziggo	IHsvInstallation2_Ziggo
#define pins_UPC	IHsvInstallation2_UPC
#define pins_UnityMedia	IHsvInstallation2_UnityMedia
#define pins_Kdg	IHsvInstallation2_Kdg
#define pins_Telenet	IHsvInstallation2_Telenet
#define pins_RCSRDS	IHsvInstallation2_RCSRDS
#define pins_CanalDigital	IHsvInstallation2_CanalDigital
#define pins_YouSee	IHsvInstallation2_YouSee
#define pins_DvbTCAM	IHsvInstallation2_DvbTCAM
#define pins_DvbCCAM	IHsvInstallation2_DvbCCAM
#define pins_SetUserSelectConflictService(LcnIndex,SvcIndex)	pins->SetUserSelectConflictService(LcnIndex,SvcIndex)
#define pins_ConflictsSelectionDone(UserSelection)	pins->ConflictsSelectionDone(UserSelection)
#define pins_GetConflictServices(ConflictList,NumRecords)	pins->GetConflictServices(ConflictList,NumRecords)
#define pins_GetInstallationVersion()	pins->GetInstallationVersion()
#define pins_GetInstallationState()	pins->GetInstallationState()
#define pins_GetPLPIds(PLPIds)	pins->GetPLPIds(PLPIds)
#define pins_GetRegionList(RegionsData)	pins->GetRegionList(RegionsData)
#define pins_UserSelectionDone(UserSelection)	pins->UserSelectionDone(UserSelection)
#define pins_GetFavouriteRegion(mode,RegionType)	pins->GetFavouriteRegion(mode,RegionType)
#define pins_GetStreamPriority()	pins->GetStreamPriority()
#define pins_SetStreamPriority(prio)	pins->SetStreamPriority(prio)
#define pins_GetConstellation()	pins->GetConstellation()
#define pins_GetSymbolRate()	pins->GetSymbolRate()
#define pins_GetHierarchyMode()	pins->GetHierarchyMode()
#define pins_GetEpgBarkerMux(OnId,TsId)	pins->GetEpgBarkerMux(OnId,TsId)
#define pins_ZiggoNetworkDataSet(ActionValue)	pins->ZiggoNetworkDataSet(ActionValue)
#define pins_ClearPersistent()	pins->ClearPersistent()
#define sysset_iPresent() (sysset.Present())
#define sysset_AudioFormatStandard	IHsvTcSystemSettings_AudioFormatStandard
#define sysset_AudioFormatAdvanced	IHsvTcSystemSettings_AudioFormatAdvanced
#define sysset_SetSystemLanguage(lang)	sysset->SetSystemLanguage(lang)
#define sysset_GetSystemLanguage()	sysset->GetSystemLanguage()
#define sysset_SetPreferredPrimaryAudioLanguage(lang)	sysset->SetPreferredPrimaryAudioLanguage(lang)
#define sysset_GetPreferredPrimaryAudioLanguage()	sysset->GetPreferredPrimaryAudioLanguage()
#define sysset_GetPreferredSecondarySubtitleLanguage()	sysset->GetPreferredSecondarySubtitleLanguage()
#define sysset_SetPreferredSecondarySubtitleLanguage(lang)	sysset->SetPreferredSecondarySubtitleLanguage(lang)
#define sysset_GetPreferredSecondaryAudioLanguage()	sysset->GetPreferredSecondaryAudioLanguage()
#define sysset_SetPreferredSecondaryAudioLanguage(lang)	sysset->SetPreferredSecondaryAudioLanguage(lang)
#define sysset_SetPreferredPrimarySubtitleLanguage(lang)	sysset->SetPreferredPrimarySubtitleLanguage(lang)
#define sysset_GetPreferredPrimarySubtitleLanguage()	sysset->GetPreferredPrimarySubtitleLanguage()
#define sysset_SetPreferredAudioFormat(format)	sysset->SetPreferredAudioFormat(format)
#define sysset_GetPreferredAudioFormat()	sysset->GetPreferredAudioFormat()
#define sysset_SetPreferredPrimaryTxtLanguage(lang)	sysset->SetPreferredPrimaryTxtLanguage(lang)
#define sysset_GetPreferredPrimaryTxtLanguage()	sysset->GetPreferredPrimaryTxtLanguage()
#define sysset_SetPreferredSecondaryTxtLanguage(lang)	sysset->SetPreferredSecondaryTxtLanguage(lang)
#define sysset_GetPreferredSecondaryTxtLanguage()	sysset->GetPreferredSecondaryTxtLanguage()
#define sysset_SetSystemCountry(country)	sysset->SetSystemCountry(country)
#define sysset_GetSystemCountry()	sysset->GetSystemCountry()
#define sysset_SetInstallCountry(country)	sysset->SetInstallCountry(country)
#define sysset_GetInstallCountry()	sysset->GetInstallCountry()
#define sysset_SetInstallCity(city)	sysset->SetInstallCity(city)
#define sysset_SetSystemCity(city)	sysset->SetSystemCity(city)
#define sysset_GetInstallCity()	sysset->GetInstallCity()
#define sysset_GetSystemCity()	sysset->GetSystemCity()
#define hsvacidec_div_PrefetchAciPage	i__hsvacidec_div.m_PrefetchAciPage
#define hsvacidec_div_PresetNameLength	i__hsvacidec_div.m_PresetNameLength
#define hsvacidec_div_AciDispStartRow	i__hsvacidec_div.m_AciDispStartRow
#define hsvacidec_div_AciDispStartCol	i__hsvacidec_div.m_AciDispStartCol
#define hsvacidec_div_AciDispEndRow	i__hsvacidec_div.m_AciDispEndRow
#define hsvacidec_div_AciDispEndCol	i__hsvacidec_div.m_AciDispEndCol
#define hsvacidec_div_AciRowHeight	i__hsvacidec_div.m_AciRowHeight
#define ieuconfig_AutoStoreModeNone	IHsvEuropeConfiguration_AutoStoreModeNone
#define ieuconfig_AutoStoreModeVpsPdc	IHsvEuropeConfiguration_AutoStoreModeVpsPdc
#define ieuconfig_AutoStoreModeAci	IHsvEuropeConfiguration_AutoStoreModeAci
#define ieuconfig_AutoStoreModeVpsPdcAci	IHsvEuropeConfiguration_AutoStoreModeVpsPdcAci
#define ieuconfig_InstallationCookie	i__ieuconfig.m_InstallationCookie
/*
#define svpaci_div_MaxPresets	ICesPaciDiv_MaxPresets
#define svpaci_div_MaxTunPreset	i__svpaci_div.m_MaxTunPreset
#define svpaci_div_MinTunPreset	i__svpaci_div.m_MinTunPreset
#define svpaci_div_AciAcquisitionTimeoutTime	i__svpaci_div.m_AciAcquisitionTimeoutTime
#define svpaci_div_RestorePageAcqTimeoutTime	i__svpaci_div.m_RestorePageAcqTimeoutTime
#define svpaci_div_MultipageDisplayTimeoutTime	i__svpaci_div.m_MultipageDisplayTimeoutTime
#define svpaci_div_AciTxtHdrReqDelay	i__svpaci_div.m_AciTxtHdrReqDelay
#define svpaci_div_TunNotifyTimeout	i__svpaci_div.m_TunNotifyTimeout
*/
#define svpats_div_PresetNameLength	ICesPatsDiv_PresetNameLength
#define svpats_div_MaxPresets	ICesPatsDiv_MaxPresets
//#define svpats_div_GetDefaultPresetName	i__svpats_div.m_GetDefaultPresetName
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
#include "locals_mdiv.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

