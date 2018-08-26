#ifndef  _CHSVPRESETINSTALLATION_M_PRIV_H
#define  _CHSVPRESETINSTALLATION_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <ITvColorDecode2NotifyEx.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvPresetImplicitInstall.h>
#include <IHsvAciDisplayNotify.h>
#include <IHsvAciInstallationSubNotify.h>
#include <IHsvPower.h>
#include <IHsvAnalogInstallation.h>
#include <IHsvTxtResetNotify.h>
#include <IHsvChannelLibReturnCodes.h>
#include <IHsvTsvChannelName.h>
#include <IHsvCountryIds.h>
#include <IHsvCniPresetName.h>
#include <ITvColorDecode2.h>
#include <IHsvPresetInstallationDiv.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeConfiguration.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationFrequencyControl.h>
#include <IHsvPresetImplicitInstallNotify.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLog.h>
#include <IHsvMemoryPool.h>
#include <IMemoryOperations.h>
#include <IHsvTxtPacket830Data.h>
#include <IPumpEngine.h>
#include <ISvcAciInstallation.h>
#include <IHsvProgramData3.h>
#include <ISvcCniData.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvAnalogInstallationNotify.h>
#include <IHsvPresetSort.h>
#include <IHsvInstallation2.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvHybridPresetSort.h>
#include <IString.h>
#include <IHsvInstallationSystemControl.h>
#include <IHsvTcSystemSettings.h>
#include <IHsvTxtPresent.h>
#include <IHsvTxtVpsData.h>
#include <IHsvWindowDestinationMap.h>
#include <CTCMwBase.h>
class CHsvPresetInstallation_m_Priv;
#define CLASSSCOPE CHsvPresetInstallation_m_Priv::
#include "locals_m.h"

class CHsvPresetInstallation_m_Priv : public CTCMwBase
{
public:
virtual ~CHsvPresetInstallation_m_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
static Bool scanningInProgress;
private:
ITvColorDecode2NotifyExImpl(CHsvPresetInstallation_m_Priv,colN);
IHsvFrontEndApiNotifyImpl(CHsvPresetInstallation_m_Priv,feapiN);
IHsvPresetImplicitInstallImpl(CHsvPresetInstallation_m_Priv,implins);
IHsvAciDisplayNotifyImpl(CHsvPresetInstallation_m_Priv,pacidsN);
IHsvAciInstallationSubNotifyImpl(CHsvPresetInstallation_m_Priv,pgaciN);
IHsvPowerImpl(CHsvPresetInstallation_m_Priv,pow);
IHsvAnalogInstallationImpl(CHsvPresetInstallation_m_Priv,prins);
IHsvTxtResetNotifyImpl(CHsvPresetInstallation_m_Priv,resetN);
public:
ProvidesInterface<ITvColorDecode2NotifyEx>	colN;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvPresetImplicitInstall>	implins;

ProvidesInterface<IHsvAciDisplayNotify>	pacidsN;

ProvidesInterface<IHsvAciInstallationSubNotify>	pgaciN;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvAnalogInstallation>	prins;

ProvidesInterface<IHsvTxtResetNotify>	resetN;

//Required interfaces
public:
RequiresInterface<IHsvChannelLibReturnCodes>	chanlibret;
RequiresInterface<IHsvTsvChannelName>	chlname;
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvCniPresetName>	cniname;
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IHsvPresetInstallationDiv>	div;
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvEuropeConfiguration>	euconfig;
RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationFrequencyControl>	freqctl;
RequiresInterface<IHsvPresetImplicitInstallNotify>	implinsN;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvMemoryPool>	mem;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IHsvTxtPacket830Data>	p830;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<ISvcAciInstallation>	pgaci;
RequiresInterface<IHsvProgramData3>	pgdat;
RequiresInterface<ISvcCniData>	pgdatcni;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvAnalogInstallationNotify>	prinsN;
RequiresInterface<IHsvPresetSort>	prsort;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvInstallationSigStrength>	sigstr;
RequiresInterface<IHsvHybridPresetSort>	sort;
RequiresInterface<IString>	str;
RequiresInterface<IHsvInstallationSystemControl>	sysctl;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IHsvTxtPresent>	txtpre;
RequiresInterface<IHsvTxtVpsData>	vps;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvPresetInstallation_m_Priv);


public:
CHsvPresetInstallation_m_Priv():i__colN(this),i__feapiN(this),i__implins(this),i__pacidsN(this),i__pgaciN(this),i__pow(this),i__prins(this),i__resetN(this)
{
colN	=	&i__colN;
feapiN	=	&i__feapiN;
implins	=	&i__implins;
pacidsN	=	&i__pacidsN;
pgaciN	=	&i__pgaciN;
pow	=	&i__pow;
prins	=	&i__prins;
resetN	=	&i__resetN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define chanlibret_iPresent() (chanlibret.Present())
#define chanlibret_Ok	IHsvChannelLibReturnCodes_Ok
#define chanlibret_BadParameter	IHsvChannelLibReturnCodes_BadParameter
#define chanlibret_ChannelTableEmpty	IHsvChannelLibReturnCodes_ChannelTableEmpty
#define chanlibret_ChannelTableExhausted	IHsvChannelLibReturnCodes_ChannelTableExhausted
#define chanlibret_MinorNumbersExhausted	IHsvChannelLibReturnCodes_MinorNumbersExhausted
#define chanlibret_NotSupported	IHsvChannelLibReturnCodes_NotSupported
#define chanlibret_FileError	IHsvChannelLibReturnCodes_FileError
#define chanlibret_ChannelTableVersionError	IHsvChannelLibReturnCodes_ChannelTableVersionError
#define chanlibret_ChannelTableCrcError	IHsvChannelLibReturnCodes_ChannelTableCrcError
#define chanlibret_ChannelNotInstalled	IHsvChannelLibReturnCodes_ChannelNotInstalled
#define chanlibret_NVMError	IHsvChannelLibReturnCodes_NVMError
#define chlname_iPresent() (chlname.Present())
#define chlname_GetCurrentChannelLabel(label)	chlname->GetCurrentChannelLabel(label)
#define chlname_ChannelLabelLength	chlname->ChannelLabelLength()
#define cids_iPresent() (cids.Present())
#define cids_CountryAustria	IHsvCountryIds_CountryAustria
#define cids_CountryBelgium	IHsvCountryIds_CountryBelgium
#define cids_CountryCroatia	IHsvCountryIds_CountryCroatia
#define cids_CountryCzechrep	IHsvCountryIds_CountryCzechrep
#define cids_CountryDenmark	IHsvCountryIds_CountryDenmark
#define cids_CountryFinland	IHsvCountryIds_CountryFinland
#define cids_CountryFrance	IHsvCountryIds_CountryFrance
#define cids_CountryGermany	IHsvCountryIds_CountryGermany
#define cids_CountryGreece	IHsvCountryIds_CountryGreece
#define cids_CountryHungary	IHsvCountryIds_CountryHungary
#define cids_CountryIreland	IHsvCountryIds_CountryIreland
#define cids_CountryItaly	IHsvCountryIds_CountryItaly
#define cids_CountryLuxembourg	IHsvCountryIds_CountryLuxembourg
#define cids_CountryNetherlands	IHsvCountryIds_CountryNetherlands
#define cids_CountryNorway	IHsvCountryIds_CountryNorway
#define cids_CountryPoland	IHsvCountryIds_CountryPoland
#define cids_CountryPortugal	IHsvCountryIds_CountryPortugal
#define cids_CountryRomania	IHsvCountryIds_CountryRomania
#define cids_CountryRussia	IHsvCountryIds_CountryRussia
#define cids_CountrySerbia	IHsvCountryIds_CountrySerbia
#define cids_CountrySlovakia	IHsvCountryIds_CountrySlovakia
#define cids_CountrySlovenia	IHsvCountryIds_CountrySlovenia
#define cids_CountrySpain	IHsvCountryIds_CountrySpain
#define cids_CountrySweden	IHsvCountryIds_CountrySweden
#define cids_CountrySwitzerland	IHsvCountryIds_CountrySwitzerland
#define cids_CountryTurkey	IHsvCountryIds_CountryTurkey
#define cids_CountryUK	IHsvCountryIds_CountryUK
#define cids_CountryOther	IHsvCountryIds_CountryOther
#define cids_CountryAustralia	IHsvCountryIds_CountryAustralia
#define cids_CountryEstonia	IHsvCountryIds_CountryEstonia
#define cids_CountryLithuania	IHsvCountryIds_CountryLithuania
#define cids_CountryLatvia	IHsvCountryIds_CountryLatvia
#define cids_CountryKazakhstan	IHsvCountryIds_CountryKazakhstan
#define cids_CountryBulgaria	IHsvCountryIds_CountryBulgaria
#define cids_CountryChina	IHsvCountryIds_CountryChina
#define cids_CountryUkraine	IHsvCountryIds_CountryUkraine
#define cids_CountryBrazil	IHsvCountryIds_CountryBrazil
#define cids_CountryArgentina	IHsvCountryIds_CountryArgentina
#define cids_CountryAlbania	IHsvCountryIds_CountryAlbania
#define cids_CountryArmenia	IHsvCountryIds_CountryArmenia
#define cids_CountryAzerbaijan	IHsvCountryIds_CountryAzerbaijan
#define cids_CountryBelarus	IHsvCountryIds_CountryBelarus
#define cids_CountryBosniaAndHerzegovina	IHsvCountryIds_CountryBosniaAndHerzegovina
#define cids_CountryGeorgia	IHsvCountryIds_CountryGeorgia
#define cids_CountryMontenegro	IHsvCountryIds_CountryMontenegro
#define cids_CountryIsrael	IHsvCountryIds_CountryIsrael
#define cids_CountryMacedoniafyrom	IHsvCountryIds_CountryMacedoniafyrom
#define cids_CountryMax	IHsvCountryIds_CountryMax
#define cniname_iPresent() (cniname.Present())
#define cniname_CniNiInvalid	IHsvCniPresetName_CniNiInvalid
#define cniname_GetPresetName(vpsCni,pkt830Cni,pkt830Ni,ard)	cniname->GetPresetName(vpsCni,pkt830Cni,pkt830Ni,ard)
#define col_iPresent() (col.Present())
#define col_ColorSystemSupported(colorsystem)	col->ColorSystemSupported(colorsystem)
#define col_ColorSystemSupportedEx(colorsystem,carrierfrequency)	col->ColorSystemSupportedEx(colorsystem,carrierfrequency)
#define col_ForceColorSystem(colorsystem)	col->ForceColorSystem(colorsystem)
#define col_ForceColorSystemEx(colorsystem,carrierfrequency)	col->ForceColorSystemEx(colorsystem,carrierfrequency)
#define col_GetForcedColorSystem()	col->GetForcedColorSystem()
#define col_GetForcedCarrierFrequency()	col->GetForcedCarrierFrequency()
#define col_SuggestColorSystem(colorsystem)	col->SuggestColorSystem(colorsystem)
#define col_SuggestColorSystemEx(colorsystem,carrierfrequency)	col->SuggestColorSystemEx(colorsystem,carrierfrequency)
#define col_GetSuggestedColorSystem()	col->GetSuggestedColorSystem()
#define col_GetSuggestedCarrierFrequency()	col->GetSuggestedCarrierFrequency()
#define col_GetColorSystem()	col->GetColorSystem()
#define col_GetCarrierFrequency()	col->GetCarrierFrequency()
#define col_CombFilterSupported()	col->CombFilterSupported()
#define col_EnableCombFilter(mode)	col->EnableCombFilter(mode)
#define col_CombFilterEnabled()	col->CombFilterEnabled()
#define col_CombFilterActive()	col->CombFilterActive()
#define col_UnknownColorSystem	col->UnknownColorSystem()
#define col_InvalidColorSystem	col->InvalidColorSystem()
#define col_Pal	col->Pal()
#define col_Secam	col->Secam()
#define col_Ntsc	col->Ntsc()
#define col_FreqUnknown	col->FreqUnknown()
#define col_FreqInvalid	col->FreqInvalid()
#define col_Freq4pt433619	col->Freq4pt433619()
#define col_Freq3pt582056	col->Freq3pt582056()
#define col_Freq3pt575611	col->Freq3pt575611()
#define col_Freq3pt579545	col->Freq3pt579545()
#define div_iPresent() (div.Present())
#define div_iVersion	div->iVersion()
#define div_MaxPresets	IHsvPresetInstallationDiv_MaxPresets
#define div_PresetNameLength	IHsvPresetInstallationDiv_PresetNameLength
#define div_TxtResetTimeoutTime	div->TxtResetTimeoutTime()
#define div_SorCChannelSupported	div->SorCChannelSupported()
#define div_TxtInfoTimeoutTime	div->TxtInfoTimeoutTime()
#define div_AciOverallTimeoutTime	div->AciOverallTimeoutTime()
#define div_NITTimeoutTime	div->NITTimeoutTime()
#define div_SecondPassSearchSupported(country)	div->SecondPassSearchSupported(country)
#define div_SignalStrengthSorting	div->SignalStrengthSorting()
#define div_WeakSignalStrengthThreshold	div->WeakSignalStrengthThreshold()
#define div_AttenuatorDetectionInInstall	div->AttenuatorDetectionInInstall()
#define div_SupportNameExtractionInManIns	div->SupportNameExtractionInManIns()
#define div_GetDefaultPresetName	div->GetDefaultPresetName()
#define div_SearchForTvSystemInInstallation	div->SearchForTvSystemInInstallation()
#define div_SearchForColorSystemInInstallation	div->SearchForColorSystemInInstallation()
#define div_SortPresetsInAutoStoreModeNone	div->SortPresetsInAutoStoreModeNone()
#define div_SignalStrengthTimeoutTime	div->SignalStrengthTimeoutTime()
#define div_ManualSearchWithWrapAround	div->ManualSearchWithWrapAround()
#define div_ImmediateStoreInAutoInstall	div->ImmediateStoreInAutoInstall()
#define div_AudioMuteDuringInstall	div->AudioMuteDuringInstall()
#define div_NameExtractionDuringImplicitManInstall	div->NameExtractionDuringImplicitManInstall()
#define div_HandleSorCStationNotFoundinManInstall	div->HandleSorCStationNotFoundinManInstall()
#define div_DefaultSystemLanguage	div->DefaultSystemLanguage()
#define div_CookieDefaultValue	div->CookieDefaultValue()
#define div_MpegSectionsAcquisitionTimeout	div->MpegSectionsAcquisitionTimeout()
#define div_BlankVideo	div->BlankVideo()
#define div_SigStrengthThresholdValue	div->SigStrengthThresholdValue()
#define div_FirstInstallationPass	div->FirstInstallationPass()
#define div_PgctrlMuteColor	div->PgctrlMuteColor()
#define div_MaxPresetNo	div->MaxPresetNo()
#define div_MinPresetNo	div->MinPresetNo()
#define div_AnalogOnly	div->AnalogOnly()
#define div_InstallTestStreams(installationmode,medium)	div->InstallTestStreams(installationmode,medium)
#define div_NotInstall	div->NotInstall()
#define div_Install	div->Install()
#define div_Hide	div->Hide()
#define div_SupportMultipleOriginalNetworkId(medium)	div->SupportMultipleOriginalNetworkId(medium)
#define div_InstallDuplicateTsids(medium)	div->InstallDuplicateTsids(medium)
#define div_StreamPriorityToBeUsed(medium)	div->StreamPriorityToBeUsed(medium)
#define div_IsServiceInstallable(medium,ServiceType)	div->IsServiceInstallable(medium,ServiceType)
#define div_IsServiceSortable(medium,ServiceType)	div->IsServiceSortable(medium,ServiceType)
#define div_IsServiceHidden(medium,ServiceType)	div->IsServiceHidden(medium,ServiceType)
#define div_UpdateChannelName(medium)	div->UpdateChannelName(medium)
#define div_UpdateLCN(medium)	div->UpdateLCN(medium)
#define div_ChannelListVariant	div->ChannelListVariant()
#define div_DefaultChannelList	div->DefaultChannelList()
#define div_DualChannelList	div->DualChannelList()
#define div_TripleChannelList	div->TripleChannelList()
#define div_SkipInstallationPass	div->SkipInstallationPass()
#define div_AutoCommitOnInstallation	div->AutoCommitOnInstallation()
#define div_TripletKey(medium)	div->TripletKey(medium)
#define div_InstallDuplicateServices(medium)	div->InstallDuplicateServices(medium)
#define div_SkipAnalog	IHsvPresetInstallationDiv_SkipAnalog
#define div_SkipDigital	IHsvPresetInstallationDiv_SkipDigital
#define div_SkipNone	IHsvPresetInstallationDiv_SkipNone
#define div_ClearDataOnAutoInstallation	div->ClearDataOnAutoInstallation()
#define div_AnalogInstallationSequence	div->AnalogInstallationSequence()
#define div_PalOnly	IHsvPresetInstallationDiv_PalOnly
#define div_PalSecam	IHsvPresetInstallationDiv_PalSecam
#define div_SecamPal	IHsvPresetInstallationDiv_SecamPal
#define div_SecamOnly	IHsvPresetInstallationDiv_SecamOnly
#define div_CurrentCountryInvalidLCNSortKey1	div->CurrentCountryInvalidLCNSortKey1()
#define div_CurrentCountryInvalidLCNSortKey2	div->CurrentCountryInvalidLCNSortKey2()
#define div_CurrentCountryInvalidLCNSortKey3	div->CurrentCountryInvalidLCNSortKey3()
#define div_CurrentCountryInvalidLCNSortKey4	div->CurrentCountryInvalidLCNSortKey4()
#define div_CurrentCountryInvalidLCNSortKey5	div->CurrentCountryInvalidLCNSortKey5()
#define div_OtherCountrySortKey1	div->OtherCountrySortKey1()
#define div_OtherCountrySortKey2	div->OtherCountrySortKey2()
#define div_OtherCountrySortKey3	div->OtherCountrySortKey3()
#define div_OtherCountrySortKey4	div->OtherCountrySortKey4()
#define div_OtherCountrySortKey5	div->OtherCountrySortKey5()
#define div_KeyInvalid	IHsvPresetInstallationDiv_KeyInvalid
#define div_KeyOriginalNetworkId	IHsvPresetInstallationDiv_KeyOriginalNetworkId
#define div_KeyServiceType	IHsvPresetInstallationDiv_KeyServiceType
#define div_KeyLCN	IHsvPresetInstallationDiv_KeyLCN
#define div_KeyServiceName	IHsvPresetInstallationDiv_KeyServiceName
#define div_KeyServiceId	IHsvPresetInstallationDiv_KeyServiceId
#define div_MaxAnalogPresets	IHsvPresetInstallationDiv_MaxAnalogPresets
#define div_SupportEmptyAnalogChannels	div->SupportEmptyAnalogChannels()
#define div_StorePresetsOnStopInstallation	div->StorePresetsOnStopInstallation()
#define div_DefaultTunerPresetFrequency	div->DefaultTunerPresetFrequency()
#define div_MaxLCNValue	div->MaxLCNValue()
#define div_FreqListSortedTableId	div->FreqListSortedTableId()
#define div_GetViterbiBER()	div->GetViterbiBER()
#define div_DeltaViterbiBER()	div->DeltaViterbiBER()
#define err_iPresent() (err.Present())
#define err_Ok	IHsvErrorCodeEx_Ok
#define err_BadParameter	IHsvErrorCodeEx_BadParameter
#define err_ChannelNotInstalled	IHsvErrorCodeEx_ChannelNotInstalled
#define err_SelectionRequestNotHonored	IHsvErrorCodeEx_SelectionRequestNotHonored
#define err_ChannelAlreadySelected	IHsvErrorCodeEx_ChannelAlreadySelected
#define err_ValidSelectionRequest	IHsvErrorCodeEx_ValidSelectionRequest
#define err_InvalidSelectionRequest	IHsvErrorCodeEx_InvalidSelectionRequest
#define err_ChannelTableEmpty	IHsvErrorCodeEx_ChannelTableEmpty
#define err_ChannelTableExhausted	IHsvErrorCodeEx_ChannelTableExhausted
#define err_InvalidChannel	IHsvErrorCodeEx_InvalidChannel
#define err_FileError	IHsvErrorCodeEx_FileError
#define err_ChannelTableVersionError	IHsvErrorCodeEx_ChannelTableVersionError
#define err_ChannelTableCrcError	IHsvErrorCodeEx_ChannelTableCrcError
#define err_NotSupported	IHsvErrorCodeEx_NotSupported
#define err_InstallationModeNotSupported	IHsvErrorCodeEx_InstallationModeNotSupported
#define err_InstallationCommandNotAllowed	IHsvErrorCodeEx_InstallationCommandNotAllowed
#define err_InstallationNotInProgress	IHsvErrorCodeEx_InstallationNotInProgress
#define err_InvalidPTC	IHsvErrorCodeEx_InvalidPTC
#define err_InvalidMajorChannel	IHsvErrorCodeEx_InvalidMajorChannel
#define err_InvalidMinorChannel	IHsvErrorCodeEx_InvalidMinorChannel
#define err_NoNextMinorChannel	IHsvErrorCodeEx_NoNextMinorChannel
#define err_NoPreviousMinorChannel	IHsvErrorCodeEx_NoPreviousMinorChannel
#define err_InvalidSource	IHsvErrorCodeEx_InvalidSource
#define err_NoNextsource	IHsvErrorCodeEx_NoNextsource
#define err_NoPreviousSource	IHsvErrorCodeEx_NoPreviousSource
#define err_InvalidMode	IHsvErrorCodeEx_InvalidMode
#define err_InstallationStoreFailed	IHsvErrorCodeEx_InstallationStoreFailed
#define err_InvalidDestination	IHsvErrorCodeEx_InvalidDestination
#define err_EmptyPreset	IHsvErrorCodeEx_EmptyPreset
#define err_InvalidTypeOfSelection	IHsvErrorCodeEx_InvalidTypeOfSelection
#define err_ControlledSelectionNotAllowed	IHsvErrorCodeEx_ControlledSelectionNotAllowed
#define err_InvalidAttribute	IHsvErrorCodeEx_InvalidAttribute
#define err_AudioLanguageNotAvailable	IHsvErrorCodeEx_AudioLanguageNotAvailable
#define err_InvalidInterface	IHsvErrorCodeEx_InvalidInterface
#define euconfig_iPresent() (euconfig.Present())
#define euconfig_AutoStoreModeNone	IHsvEuropeConfiguration_AutoStoreModeNone
#define euconfig_AutoStoreModeVpsPdc	IHsvEuropeConfiguration_AutoStoreModeVpsPdc
#define euconfig_AutoStoreModeAci	IHsvEuropeConfiguration_AutoStoreModeAci
#define euconfig_AutoStoreModeVpsPdcAci	IHsvEuropeConfiguration_AutoStoreModeVpsPdcAci
#define euconfig_GetAutoStoreMode()	euconfig->GetAutoStoreMode()
#define euconfig_GetMedium()	euconfig->GetMedium()
#define euconfig_GetBreakOutSource(Source)	euconfig->GetBreakOutSource(Source)
#define euconfig_GetBreakOutChannel(ChannelNo)	euconfig->GetBreakOutChannel(ChannelNo)
#define euconfig_GetDefaultSpdifAssociation(SpdifSource)	euconfig->GetDefaultSpdifAssociation(SpdifSource)
#define euconfig_InstallationCookie	euconfig->InstallationCookie()
#define eurdiv_iPresent() (eurdiv.Present())
#define eurdiv_iVersion	eurdiv->iVersion()
#define eurdiv_NITTimeoutTime	eurdiv->NITTimeoutTime()
#define eurdiv_AttenuatorDetectionInInstall	eurdiv->AttenuatorDetectionInInstall()
#define eurdiv_SupportNameExtractionInManIns	eurdiv->SupportNameExtractionInManIns()
#define eurdiv_WeakSignalStrengthThreshold	eurdiv->WeakSignalStrengthThreshold()
#define eurdiv_SignalStrengthSorting	eurdiv->SignalStrengthSorting()
#define eurdiv_SearchForColorSystemInInstallation	eurdiv->SearchForColorSystemInInstallation()
#define eurdiv_SearchForTvSystemInInstallation	eurdiv->SearchForTvSystemInInstallation()
#define eurdiv_ManualSearchWithWrapAround	eurdiv->ManualSearchWithWrapAround()
#define eurdiv_SortPresetsInAutoStoreModeNone	eurdiv->SortPresetsInAutoStoreModeNone()
#define eurdiv_SignalStrengthTimeoutTime	eurdiv->SignalStrengthTimeoutTime()
#define eurdiv_DefaultTunerPresetFrequency	eurdiv->DefaultTunerPresetFrequency()
#define eurdiv_PgctrlMuteColor	eurdiv->PgctrlMuteColor()
#define eurdiv_ChannelNameLength	eurdiv->ChannelNameLength()
#define eurdiv_PresetNameLength	eurdiv->PresetNameLength()
#define eurdiv_MuteRequiredOnInstallation	eurdiv->MuteRequiredOnInstallation()
#define eurdiv_ClearDataOnAutoInstallation	eurdiv->ClearDataOnAutoInstallation()
#define eurdiv_AnalogOnly()	eurdiv->AnalogOnly()
#define eurdiv_InstallTestStreams(installationmode,medium)	eurdiv->InstallTestStreams(installationmode,medium)
#define eurdiv_NotInstall	IHsvEuropeDiversity2_NotInstall
#define eurdiv_Install	IHsvEuropeDiversity2_Install
#define eurdiv_Hide	IHsvEuropeDiversity2_Hide
#define eurdiv_NoOfVirtualChannelsSupported(medium)	eurdiv->NoOfVirtualChannelsSupported(medium)
#define eurdiv_SupportMultipleOriginalNetworkId(medium)	eurdiv->SupportMultipleOriginalNetworkId(medium)
#define eurdiv_ForceLCNSyntax(medium)	eurdiv->ForceLCNSyntax(medium)
#define eurdiv_InstallDuplicateTsids(medium)	eurdiv->InstallDuplicateTsids(medium)
#define eurdiv_DefaultStreamPriority(medium)	eurdiv->DefaultStreamPriority(medium)
#define eurdiv_IsServiceInstallable(medium,ServiceType)	eurdiv->IsServiceInstallable(medium,ServiceType)
#define eurdiv_IsServiceSortable(medium,ServiceType)	eurdiv->IsServiceSortable(medium,ServiceType)
#define eurdiv_IsServiceHidden(medium,ServiceType)	eurdiv->IsServiceHidden(medium,ServiceType)
#define eurdiv_AcceptedStreamType(medium,StreamType)	eurdiv->AcceptedStreamType(medium,StreamType)
#define eurdiv_UpdateChannelName(medium)	eurdiv->UpdateChannelName(medium)
#define eurdiv_IsApmeaChannelListCountry()	eurdiv->IsApmeaChannelListCountry()
#define eurdiv_IsApmeaNetworkUpdateCountry()	eurdiv->IsApmeaNetworkUpdateCountry()
#define eurdiv_IsDbookCountry()	eurdiv->IsDbookCountry()
#define eurdiv_SkipInstallationPass	eurdiv->SkipInstallationPass()
#define eurdiv_FirstInstallationPass	eurdiv->FirstInstallationPass()
#define eurdiv_SkipAnalog	IHsvEuropeDiversity2_SkipAnalog
#define eurdiv_SkipDigital	IHsvEuropeDiversity2_SkipDigital
#define eurdiv_SkipNone	IHsvEuropeDiversity2_SkipNone
#define eurdiv_UpdateLCN(medium)	eurdiv->UpdateLCN(medium)
#define eurdiv_TxtInfoTimeout	eurdiv->TxtInfoTimeout()
#define eurdiv_VideoMuteColor	eurdiv->VideoMuteColor()
#define eurdiv_VideoMuteColorForLocks	eurdiv->VideoMuteColorForLocks()
#define eurdiv_VideoMuteBlack	IHsvEuropeDiversity2_VideoMuteBlack
#define eurdiv_VideoMuteBlue	IHsvEuropeDiversity2_VideoMuteBlue
#define eurdiv_VideoMuteGrey	IHsvEuropeDiversity2_VideoMuteGrey
#define eurdiv_DecoderSupported	eurdiv->DecoderSupported()
#define eurdiv_BreakInSupported	eurdiv->BreakInSupported()
#define eurdiv_ScartRuleSupported	eurdiv->ScartRuleSupported()
#define eurdiv_HsvAntennaAnalogTable	eurdiv->HsvAntennaAnalogTable()
#define eurdiv_HsvAntennaDigSrvcTable	eurdiv->HsvAntennaDigSrvcTable()
#define eurdiv_HsvAntennaDigPtcTable	eurdiv->HsvAntennaDigPtcTable()
#define eurdiv_HsvAntennaFreqMapTable	eurdiv->HsvAntennaFreqMapTable()
#define eurdiv_PersistentMemUpdateTimeout	eurdiv->PersistentMemUpdateTimeout()
#define eurdiv_MaxNoOfChannelsToStoreAntennaUserTable	eurdiv->MaxNoOfChannelsToStoreAntennaUserTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaDigPtcTable	eurdiv->MaxNoOfChannelsToStoreAntennaDigPtcTable()
#define eurdiv_MaxNoOfChannelsToStoreAntennaAnalogTable	eurdiv->MaxNoOfChannelsToStoreAntennaAnalogTable()
#define eurdiv_MaxNoOfMultiplexsToStoreAntennaFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreAntennaFreqMapTable()
#define eurdiv_IsHDSubtitleSupported()	eurdiv->IsHDSubtitleSupported()
#define eurdiv_AvSignalDetectionTimeOut	eurdiv->AvSignalDetectionTimeOut()
#define eurdiv_HearingImpairedOn	eurdiv->HearingImpairedOn()
#define eurdiv_VisuallyImpairedOn()	eurdiv->VisuallyImpairedOn()
#define eurdiv_IsQaaSupported()	eurdiv->IsQaaSupported()
#define eurdiv_IsPremixedVISupported()	eurdiv->IsPremixedVISupported()
#define eurdiv_EPGSecondaryDirName	eurdiv->EPGSecondaryDirName()
#define eurdiv_DefaultCharacterTable	eurdiv->DefaultCharacterTable()
#define eurdiv_ShortInfoCacheForCountry	eurdiv->ShortInfoCacheForCountry()
#define eurdiv_OUI	eurdiv->OUI()
#define eurdiv_HardwareModel	eurdiv->HardwareModel()
#define eurdiv_HardwareVersion	eurdiv->HardwareVersion()
#define eurdiv_GetNoOfBackBuffers(clientId)	eurdiv->GetNoOfBackBuffers(clientId)
#define eurdiv_SubtitleTimeOut	eurdiv->SubtitleTimeOut()
#define eurdiv_IsMpeg4STBoltOnSupported()	eurdiv->IsMpeg4STBoltOnSupported()
#define eurdiv_IsAVCDescriptorSupported()	eurdiv->IsAVCDescriptorSupported()
#define eurdiv_ForceCharacterTable()	eurdiv->ForceCharacterTable()
#define eurdiv_RegionalCharacterTable()	eurdiv->RegionalCharacterTable()
#define eurdiv_CurrentCountryInvalidLCNSortKey1	eurdiv->CurrentCountryInvalidLCNSortKey1()
#define eurdiv_CurrentCountryInvalidLCNSortKey2	eurdiv->CurrentCountryInvalidLCNSortKey2()
#define eurdiv_CurrentCountryInvalidLCNSortKey3	eurdiv->CurrentCountryInvalidLCNSortKey3()
#define eurdiv_CurrentCountryInvalidLCNSortKey4	eurdiv->CurrentCountryInvalidLCNSortKey4()
#define eurdiv_CurrentCountryInvalidLCNSortKey5	eurdiv->CurrentCountryInvalidLCNSortKey5()
#define eurdiv_OtherCountrySortKey1	eurdiv->OtherCountrySortKey1()
#define eurdiv_OtherCountrySortKey2	eurdiv->OtherCountrySortKey2()
#define eurdiv_OtherCountrySortKey3	eurdiv->OtherCountrySortKey3()
#define eurdiv_OtherCountrySortKey4	eurdiv->OtherCountrySortKey4()
#define eurdiv_OtherCountrySortKey5	eurdiv->OtherCountrySortKey5()
#define eurdiv_KeyInvalid	IHsvEuropeDiversity2_KeyInvalid
#define eurdiv_KeyOriginalNetworkId	IHsvEuropeDiversity2_KeyOriginalNetworkId
#define eurdiv_KeyServiceType	IHsvEuropeDiversity2_KeyServiceType
#define eurdiv_KeyLCN	IHsvEuropeDiversity2_KeyLCN
#define eurdiv_KeyServiceName	IHsvEuropeDiversity2_KeyServiceName
#define eurdiv_KeyServiceId	IHsvEuropeDiversity2_KeyServiceId
#define eurdiv_TripletKey(medium)	eurdiv->TripletKey(medium)
#define eurdiv_InstallDuplicateServices(medium)	eurdiv->InstallDuplicateServices(medium)
#define eurdiv_MeasureSignalStrengthWhilePlaying	eurdiv->MeasureSignalStrengthWhilePlaying()
#define eurdiv_AnalogInstallationSequence	eurdiv->AnalogInstallationSequence()
#define eurdiv_Automatic	IHsvEuropeDiversity2_Automatic
#define eurdiv_PalOnly	IHsvEuropeDiversity2_PalOnly
#define eurdiv_PalSecam	IHsvEuropeDiversity2_PalSecam
#define eurdiv_SecamPal	IHsvEuropeDiversity2_SecamPal
#define eurdiv_SecamOnly	IHsvEuropeDiversity2_SecamOnly
#define eurdiv_ChannelListVariant	eurdiv->ChannelListVariant()
#define eurdiv_DefaultChannelList	IHsvEuropeDiversity2_DefaultChannelList
#define eurdiv_DualChannelList	IHsvEuropeDiversity2_DualChannelList
#define eurdiv_TripleChannelList	IHsvEuropeDiversity2_TripleChannelList
#define eurdiv_EnableCountryFallbackForLCNSyntax(medium)	eurdiv->EnableCountryFallbackForLCNSyntax(medium)
#define eurdiv_EnableONIDFallbackForLCNSyntax(medium)	eurdiv->EnableONIDFallbackForLCNSyntax(medium)
#define eurdiv_HsvCableAnalogTable	eurdiv->HsvCableAnalogTable()
#define eurdiv_HsvCableDigSrvcTable	eurdiv->HsvCableDigSrvcTable()
#define eurdiv_HsvCableDigPtcTable	eurdiv->HsvCableDigPtcTable()
#define eurdiv_HsvCableSvcListDescTable	eurdiv->HsvCableSvcListDescTable()
#define eurdiv_HsvCableFreqMapTable	eurdiv->HsvCableFreqMapTable()
#define eurdiv_MaxNoOfChannelsToStoreCableUserTable	eurdiv->MaxNoOfChannelsToStoreCableUserTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigSrvcTable	eurdiv->MaxNoOfChannelsToStoreCableDigSrvcTable()
#define eurdiv_MaxNoOfChannelsToStoreCableDigPtcTable	eurdiv->MaxNoOfChannelsToStoreCableDigPtcTable()
#define eurdiv_MaxNoOfChannelsToStoreCableAnalogTable	eurdiv->MaxNoOfChannelsToStoreCableAnalogTable()
#define eurdiv_MaxNoOfMultiplexsToStoreCableFreqMapTable	eurdiv->MaxNoOfMultiplexsToStoreCableFreqMapTable()
#define eurdiv_IsDVBCSupported()	eurdiv->IsDVBCSupported()
#define eurdiv_QuickScan	IHsvEuropeDiversity2_QuickScan
#define eurdiv_FullScan	IHsvEuropeDiversity2_FullScan
#define eurdiv_GetDefaultScanMode(medium)	eurdiv->GetDefaultScanMode(medium)
#define eurdiv_ScanNone	IHsvEuropeDiversity2_ScanNone
#define eurdiv_ScanAnalog	IHsvEuropeDiversity2_ScanAnalog
#define eurdiv_ScanDVBT	IHsvEuropeDiversity2_ScanDVBT
#define eurdiv_ScanDVBC	IHsvEuropeDiversity2_ScanDVBC
#define eurdiv_ScanDVBS	IHsvEuropeDiversity2_ScanDVBS
#define eurdiv_ScanDVBTMpegOnly	IHsvEuropeDiversity2_ScanDVBTMpegOnly
#define eurdiv_ScanDVBCLite	IHsvEuropeDiversity2_ScanDVBCLite
#define eurdiv_GetScanPreference(medium,installationmode)	eurdiv->GetScanPreference(medium,installationmode)
#define eurdiv_GetNextScan(medium,installationmode,ScanPreference)	eurdiv->GetNextScan(medium,installationmode,ScanPreference)
#define eurdiv_GetDVBTMode()	eurdiv->GetDVBTMode()
#define eurdiv_GetDVBCMode()	eurdiv->GetDVBCMode()
#define eurdiv_NitNone	IHsvEuropeDiversity2_NitNone
#define eurdiv_NitActual	IHsvEuropeDiversity2_NitActual
#define eurdiv_NitOther	IHsvEuropeDiversity2_NitOther
#define eurdiv_GetNitPriority(medium)	eurdiv->GetNitPriority(medium)
#define eurdiv_IsServiceListDescriptorMandatory(medium)	eurdiv->IsServiceListDescriptorMandatory(medium)
#define eurdiv_PrimaryPreference	IHsvEuropeDiversity2_PrimaryPreference
#define eurdiv_SecondaryPreference	IHsvEuropeDiversity2_SecondaryPreference
#define eurdiv_GetAudioPreference()	eurdiv->GetAudioPreference()
#define eurdiv_GetSubtitlePreference()	eurdiv->GetSubtitlePreference()
#define eurdiv_UserPreferredAudioFormat()	eurdiv->UserPreferredAudioFormat()
#define eurdiv_IsFrequencyListStorageRequired()	eurdiv->IsFrequencyListStorageRequired()
#define eurdiv_GetDefaultAttributeValues(attrib,country,mode,length,values)	eurdiv->GetDefaultAttributeValues(attrib,country,mode,length,values)
#define eurdiv_HsvDVBCSettingsFilePath	eurdiv->HsvDVBCSettingsFilePath()
#define eurdiv_HsvCableDelSysDescFilePath	eurdiv->HsvCableDelSysDescFilePath()
#define eurdiv_HsvServiceListDescFilePath	eurdiv->HsvServiceListDescFilePath()
#define eurdiv_MaxLCNValue	eurdiv->MaxLCNValue()
#define eurdiv_IsBackgroundInstallRequired(medium)	eurdiv->IsBackgroundInstallRequired(medium)
#define eurdiv_SupportLCNVersion2(medium)	eurdiv->SupportLCNVersion2(medium)
#define eurdiv_ParseLCN(medium,installationmode)	eurdiv->ParseLCN(medium,installationmode)
#define eurdiv_IsPreScanSupported(medium)	eurdiv->IsPreScanSupported(medium)
#define eurdiv_SortNonLCNs(medium)	eurdiv->SortNonLCNs(medium)
#define eurdiv_SupportHDSLCN(medium)	eurdiv->SupportHDSLCN(medium)
#define eurdiv_IsServiceAttrbDescSupported(medium)	eurdiv->IsServiceAttrbDescSupported(medium)
#define eurdiv_IsTSRelocatedDescSupported(medium)	eurdiv->IsTSRelocatedDescSupported(medium)
#define eurdiv_SDTActual	IHsvEuropeDiversity2_SDTActual
#define eurdiv_SDTOther	IHsvEuropeDiversity2_SDTOther
#define eurdiv_SDTNone	IHsvEuropeDiversity2_SDTNone
#define eurdiv_GetAltSDTType(medium)	eurdiv->GetAltSDTType(medium)
#define eurdiv_AltHomingFrequency	IHsvEuropeDiversity2_AltHomingFrequency
#define eurdiv_AltTSRelocatedDesc	IHsvEuropeDiversity2_AltTSRelocatedDesc
#define eurdiv_AltNone	IHsvEuropeDiversity2_AltNone
#define eurdiv_GetAlternateTSLocation(medium)	eurdiv->GetAlternateTSLocation(medium)
#define eurdiv_GetAltFreqScanSupported(country)	eurdiv->GetAltFreqScanSupported(country)
#define eurdiv_FreqListDescriptorSupported(medium)	eurdiv->FreqListDescriptorSupported(medium)
#define eurdiv_IsAc3AudioSupported()	eurdiv->IsAc3AudioSupported()
#define eurdiv_GetDefaultAnalogInstallStatus(country)	eurdiv->GetDefaultAnalogInstallStatus(country)
#define eurdiv_StaticTable()	eurdiv->StaticTable()
#define eurdiv_GetDefaultDigitalInstallStatus(country)	eurdiv->GetDefaultDigitalInstallStatus(country)
#define eurdiv_IsMultifeedSupported()	eurdiv->IsMultifeedSupported()
#define eurdiv_IsZeroLCNHidden()	eurdiv->IsZeroLCNHidden()
#define eurdiv_GetViterbiBER()	eurdiv->GetViterbiBER()
#define eurdiv_DeltaViterbiBER()	eurdiv->DeltaViterbiBER()
#define eurdiv_GetShortInfoCacheSize()	eurdiv->GetShortInfoCacheSize()
#define eurdiv_GetDeltaSQI()	eurdiv->GetDeltaSQI()
#define eurdiv_GetDeltaSSI()	eurdiv->GetDeltaSSI()
#define eurdiv_AutomaticAnalogPresetAllocation()	eurdiv->AutomaticAnalogPresetAllocation()
#define eurdiv_AutomaticDigitalPresetAllocation()	eurdiv->AutomaticDigitalPresetAllocation()
#define eurdiv_AnalogStartPreset(country,medium,numRecords)	eurdiv->AnalogStartPreset(country,medium,numRecords)
#define eurdiv_AnalogEndPreset(country,medium)	eurdiv->AnalogEndPreset(country,medium)
#define eurdiv_GetDualAnalogPassStatus()	eurdiv->GetDualAnalogPassStatus()
#define eurdiv_NonRadioStartPreset(country,medium,numRecords)	eurdiv->NonRadioStartPreset(country,medium,numRecords)
#define eurdiv_NonRadioEndPreset(country,medium)	eurdiv->NonRadioEndPreset(country,medium)
#define eurdiv_RadioStartPreset(country,medium,numRecords)	eurdiv->RadioStartPreset(country,medium,numRecords)
#define eurdiv_RadioEndPreset(country,medium)	eurdiv->RadioEndPreset(country,medium)
#define eurdiv_IsHDSimulcastSupported()	eurdiv->IsHDSimulcastSupported()
#define eurdiv_IsDVBT2Supported()	eurdiv->IsDVBT2Supported()
#define eurdiv_MultipleLCNSupported()	eurdiv->MultipleLCNSupported()
#define eurdiv_SubtitlePidFallbackFirstPMT()	eurdiv->SubtitlePidFallbackFirstPMT()
#define eurdiv_DeleteTSNotIntransmission()	eurdiv->DeleteTSNotIntransmission()
#define eurdiv_ReapplyChildLockOnEventChange()	eurdiv->ReapplyChildLockOnEventChange()
#define eurdiv_DeleteServiceOnFly()	eurdiv->DeleteServiceOnFly()
#define feapi_iPresent() (feapi.Present())
#define feapi_GetFreqRange(winid,MinFreq,MaxFreq,retval)	feapi->GetFreqRange(winid,MinFreq,MaxFreq,retval)
#define feapi_GetFreq(winid,Freq,retval)	feapi->GetFreq(winid,Freq,retval)
#define feapi_SetFreq(winid,freq,finetune,retval)	feapi->SetFreq(winid,freq,finetune,retval)
#define feapi_GetTvSystemSupp(winid,tvSystem,Supp,retval)	feapi->GetTvSystemSupp(winid,tvSystem,Supp,retval)
#define feapi_GetTvSystem(winid,TvSystem,retval)	feapi->GetTvSystem(winid,TvSystem,retval)
#define feapi_SetTvSystem(winid,TvSystem,retval)	feapi->SetTvSystem(winid,TvSystem,retval)
#define feapi_StartSearch(winid,startFreq,mode,endFreq,retval)	feapi->StartSearch(winid,startFreq,mode,endFreq,retval)
#define feapi_StopSearch(winid,retval)	feapi->StopSearch(winid,retval)
#define feapi_Freq2Chan(winid,freq,table,Chan,retval)	feapi->Freq2Chan(winid,freq,table,Chan,retval)
#define feapi_GetCarrierFreq(winid,chan,table,Freq,retval)	feapi->GetCarrierFreq(winid,chan,table,Freq,retval)
#define feapi_SigAssm	IHsvFrontEndApi_SigAssm
#define feapi_SigVssm	IHsvFrontEndApi_SigVssm
#define feapi_SigQssm	IHsvFrontEndApi_SigQssm
#define feapi_SigSssm	IHsvFrontEndApi_SigSssm
#define feapi_GetSigStrengthRange(winid,ssm,MinStrength,MaxStrength,retval)	feapi->GetSigStrengthRange(winid,ssm,MinStrength,MaxStrength,retval)
#define feapi_Start(winid,ssm,Avail,retval)	feapi->Start(winid,ssm,Avail,retval)
#define feapi_Stop(winid,ssm,Stopped,retval)	feapi->Stop(winid,ssm,Stopped,retval)
#define feapi_GetMeasValid(winid,ssm,Valid,retval)	feapi->GetMeasValid(winid,ssm,Valid,retval)
#define feapi_GetSigStrength(winid,ssm,Strength,retval)	feapi->GetSigStrength(winid,ssm,Strength,retval)
#define feapi_GetActualConstellation(winid,decoder,pConstellation,retval)	feapi->GetActualConstellation(winid,decoder,pConstellation,retval)
#define feapi_SetConstellation(winid,decoder,constellation,retval)	feapi->SetConstellation(winid,decoder,constellation,retval)
#define feapi_GetBer(winid,decoder,Ber,retval)	feapi->GetBer(winid,decoder,Ber,retval)
#define feapi_GetCarrierPresent(winid,Present,retval)	feapi->GetCarrierPresent(winid,Present,retval)
#define feapi_SetChanBandwidth(winid,bandwidth,retval)	feapi->SetChanBandwidth(winid,bandwidth,retval)
#define feapi_GetActualChanBandwidth(winid,Bandwidth,retval)	feapi->GetActualChanBandwidth(winid,Bandwidth,retval)
#define feapi_SetStreamPriority(winid,streamPriority,retval)	feapi->SetStreamPriority(winid,streamPriority,retval)
#define feapi_GetStreamPriority(winid,streamPriority,retval)	feapi->GetStreamPriority(winid,streamPriority,retval)
#define feapi_GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval)	feapi->GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval)
#define feapi_SetSymbolRate(winid,rate,retval)	feapi->SetSymbolRate(winid,rate,retval)
#define feapi_GetSymbolRate(winid,rate,retval)	feapi->GetSymbolRate(winid,rate,retval)
#define feapi_SetSearchRates(winid,SearchRate,size,retval)	feapi->SetSearchRates(winid,SearchRate,size,retval)
#define feapi_GetActualCodeRate(winid,rate,retval)	feapi->GetActualCodeRate(winid,rate,retval)
#define feapi_SetFreqStep(winid,step,retval)	feapi->SetFreqStep(winid,step,retval)
#define feapi_GetFreqStep(winid,step,retval)	feapi->GetFreqStep(winid,step,retval)
#define feapi_GetTPSId(winid,TPSId,retval)	feapi->GetTPSId(winid,TPSId,retval)
#define feapi_ChanDecDvbT	IHsvFrontEndApi_ChanDecDvbT
#define feapi_ChanDecDvbC	IHsvFrontEndApi_ChanDecDvbC
#define feapi_ChanDecDvbS	IHsvFrontEndApi_ChanDecDvbS
#define feapi_ChanDecISDBT	IHsvFrontEndApi_ChanDecISDBT
#define feapi_ChanDecDvbT2	IHsvFrontEndApi_ChanDecDvbT2
#define freqctl_iPresent() (freqctl.Present())
#define freqctl_GetMinFrequency()	freqctl->GetMinFrequency()
#define freqctl_GetMaxFrequency()	freqctl->GetMaxFrequency()
#define freqctl_GetTunerFrequency()	freqctl->GetTunerFrequency()
#define freqctl_SetTunerFrequency(freq,fineTune)	freqctl->SetTunerFrequency(freq,fineTune)
#define freqctl_GetFrequency2Channel(chantbl,frequency)	freqctl->GetFrequency2Channel(chantbl,frequency)
#define freqctl_GetChannel2CarrierFrequency(chantbl,channel)	freqctl->GetChannel2CarrierFrequency(chantbl,channel)
#define freqctl_GetChannel2CentreFrequency(chantbl,channel)	freqctl->GetChannel2CentreFrequency(chantbl,channel)
#define implinsN_iPresent() (implinsN.Present())
#define implinsN_OnImplicitInstallationCompleted	IHsvPresetImplicitInstallNotify_OnImplicitInstallationCompleted
#define implinsN_OnFrequencyBandSearchStarted	IHsvPresetImplicitInstallNotify_OnFrequencyBandSearchStarted
#define implinsN_OnEvent(eventid)	implinsN->OnEvent(eventid)
#define instutil_iPresent() (instutil.Present())
#define instutil_LogError(Priority,ErrorId)	instutil->LogError(Priority,ErrorId)
#define instutil_AsciiToUnicode(str,len)	instutil->AsciiToUnicode(str,len)
#define log_iPresent() (log.Present())
#define log_Information	IHsvLog_Information
#define log_SoftErr	IHsvLog_SoftErr
#define log_FatalErr	IHsvLog_FatalErr
#define log_Error(prio,errid)	log->Error(prio,errid)
#define log_Trace(callerid,arg1,arg2)	log->Trace(callerid,arg1,arg2)
#define mem_iPresent() (mem.Present())
#define mem_Init(poolid)	mem->Init(poolid)
#define mem_Malloc(poolid)	mem->Malloc(poolid)
#define mem_Free(poolid,addr)	mem->Free(poolid,addr)
#define memo_iPresent() (memo.Present())
#define memo_memcmp(ptr1,ptr2,num)	memo->memcmp(ptr1,ptr2,num)
#define memo_memcmpRom(ptr1,ptr2,num)	memo->memcmpRom(ptr1,ptr2,num)
#define memo_memcpy(dest,source,num)	memo->memcpy(dest,source,num)
#define memo_memcpyRom(dest,source,num)	memo->memcpyRom(dest,source,num)
#define memo_memmove(dest,source,num)	memo->memmove(dest,source,num)
#define memo_memset(ptr,val,num)	memo->memset(ptr,val,num)
#define p830_iPresent() (p830.Present())
#define p830_RequestDataFields(field_bit_vector,cb_fn,cb_on_every_update)	p830->RequestDataFields(field_bit_vector,cb_fn,cb_on_every_update)
#define p830_UnRequestDataFields(request_id)	p830->UnRequestDataFields(request_id)
#define p830_IsDataFieldsAvailable(field_bit_vector)	p830->IsDataFieldsAvailable(field_bit_vector)
#define p830_GetStatusMessage(msg_string)	p830->GetStatusMessage(msg_string)
#define p830_GetInitialPage(ptr_pn,ptr_sc)	p830->GetInitialPage(ptr_pn,ptr_sc)
#define p830_GetUTCDate(ptr_mjd)	p830->GetUTCDate(ptr_mjd)
#define p830_GetUTCTime(ptr_time)	p830->GetUTCTime(ptr_time)
#define p830_GetTimeOffset(ptr_time_offset)	p830->GetTimeOffset(ptr_time_offset)
#define p830_GetNetworkIdentificationCode(ptr_ni)	p830->GetNetworkIdentificationCode(ptr_ni)
#define p830_GetPilCode(ptr_pil_code)	p830->GetPilCode(ptr_pil_code)
#define p830_GetCountryNetworkIdentificationCode(ptr_cni)	p830->GetCountryNetworkIdentificationCode(ptr_cni)
#define p830_GetLabelInfo(ptr_li)	p830->GetLabelInfo(ptr_li)
#define p830_GetProgramControlInfo(ptr_pci)	p830->GetProgramControlInfo(ptr_pci)
#define p830_GetProgramType(ptr_ptype)	p830->GetProgramType(ptr_ptype)
#define p830_StatusMessageField	IHsvTxtPacket830Data_StatusMessageField
#define p830_InitialPageField	IHsvTxtPacket830Data_InitialPageField
#define p830_UTCDateField	IHsvTxtPacket830Data_UTCDateField
#define p830_UTCTimeField	IHsvTxtPacket830Data_UTCTimeField
#define p830_TimeOffsetField	IHsvTxtPacket830Data_TimeOffsetField
#define p830_NICodeField	IHsvTxtPacket830Data_NICodeField
#define p830_PilCodeField	IHsvTxtPacket830Data_PilCodeField
#define p830_CNICodeField	IHsvTxtPacket830Data_CNICodeField
#define p830_LabelInfoField	IHsvTxtPacket830Data_LabelInfoField
#define p830_ProgramControlInfoField	IHsvTxtPacket830Data_ProgramControlInfoField
#define p830_ProgramTypeField	IHsvTxtPacket830Data_ProgramTypeField
#define p830_InvalidRequestId	IHsvTxtPacket830Data_InvalidRequestId
#define p830_MinutesPerTimeOffsetUnit	IHsvTxtPacket830Data_MinutesPerTimeOffsetUnit
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pgaci_iPresent() (pgaci.Present())
#define pgaci_IsAciSupported()	pgaci->IsAciSupported()
#define pgaci_StartAciInstallation()	pgaci->StartAciInstallation()
#define pgaci_StopAciInstallation()	pgaci->StopAciInstallation()
#define pgaci_GetPagePriority()	pgaci->GetPagePriority()
#define pgaci_StoreAciTable()	pgaci->StoreAciTable()
#define pgaci_GetNoOfPresets()	pgaci->GetNoOfPresets()
#define pgdat_iPresent() (pgdat.Present())
#define pgdat_BoolLock	IHsvProgramData3_BoolLock
#define pgdat_BoolFavorite	IHsvProgramData3_BoolFavorite
#define pgdat_BoolFavorite1	IHsvProgramData3_BoolFavorite1
#define pgdat_BoolFavorite2	IHsvProgramData3_BoolFavorite2
#define pgdat_BoolFavorite3	IHsvProgramData3_BoolFavorite3
#define pgdat_BoolPreferredFavorite	IHsvProgramData3_BoolPreferredFavorite
#define pgdat_BoolPreferredNicam	IHsvProgramData3_BoolPreferredNicam
#define pgdat_BoolPreferredStereo	IHsvProgramData3_BoolPreferredStereo
#define pgdat_BoolSAP	IHsvProgramData3_BoolSAP
#define pgdat_BoolHMProtectedChannel	IHsvProgramData3_BoolHMProtectedChannel
#define pgdat_BoolHMBlanked	IHsvProgramData3_BoolHMBlanked
#define pgdat_BoolUserHidden	IHsvProgramData3_BoolUserHidden
#define pgdat_BoolSystemHidden	IHsvProgramData3_BoolSystemHidden
#define pgdat_BoolNumericSelect	IHsvProgramData3_BoolNumericSelect
#define pgdat_BoolEpgChannel	IHsvProgramData3_BoolEpgChannel
#define pgdat_BoolEPGShortInfoEnabled	IHsvProgramData3_BoolEPGShortInfoEnabled
#define pgdat_BoolNewPreset	IHsvProgramData3_BoolNewPreset
#define pgdat_BoolFreeCiMode	IHsvProgramData3_BoolFreeCiMode
#define pgdat_BoolTuned	IHsvProgramData3_BoolTuned
#define pgdat_BoolDeTuned	IHsvProgramData3_BoolDeTuned
#define pgdat_BoolAttenuator	IHsvProgramData3_BoolAttenuator
#define pgdat_BoolAgcInstalled	IHsvProgramData3_BoolAgcInstalled
#define pgdat_BoolChannelVirgin	IHsvProgramData3_BoolChannelVirgin
#define pgdat_BoolUpdateName	IHsvProgramData3_BoolUpdateName
#define pgdat_IntDeltaVolume	IHsvProgramData3_IntDeltaVolume
#define pgdat_Nat32DateStamp	IHsvProgramData3_Nat32DateStamp
#define pgdat_Nat32AppsCookie	IHsvProgramData3_Nat32AppsCookie
#define pgdat_Nat32TxtCookie	IHsvProgramData3_Nat32TxtCookie
#define pgdat_Nat32CesvcCookie	IHsvProgramData3_Nat32CesvcCookie
#define pgdat_Nat32DvbType	IHsvProgramData3_Nat32DvbType
#define pgdat_StringChannelName	IHsvProgramData3_StringChannelName
#define pgdat_StringExtChannelName	IHsvProgramData3_StringExtChannelName
#define pgdat_IntFrequency	IHsvProgramData3_IntFrequency
#define pgdat_IntTvSystem	IHsvProgramData3_IntTvSystem
#define pgdat_IntModulation	IHsvProgramData3_IntModulation
#define pgdat_IntNewChannelMap	IHsvProgramData3_IntNewChannelMap
#define pgdat_IntSignalStrength	IHsvProgramData3_IntSignalStrength
#define pgdat_IntSignalQuality	IHsvProgramData3_IntSignalQuality
#define pgdat_IntColoursystem	IHsvProgramData3_IntColoursystem
#define pgdat_IntDecoderType	IHsvProgramData3_IntDecoderType
#define pgdat_IntFineTuneOffset	IHsvProgramData3_IntFineTuneOffset
#define pgdat_IntFineTuneFrequency	IHsvProgramData3_IntFineTuneFrequency
#define pgdat_Nat32SymbolRate	IHsvProgramData3_Nat32SymbolRate
#define pgdat_IntNetworkId	IHsvProgramData3_IntNetworkId
#define pgdat_IntOriginalNwId	IHsvProgramData3_IntOriginalNwId
#define pgdat_IntTsid	IHsvProgramData3_IntTsid
#define pgdat_IntServiceId	IHsvProgramData3_IntServiceId
#define pgdat_IntServiceType	IHsvProgramData3_IntServiceType
#define pgdat_IntPmtPid	IHsvProgramData3_IntPmtPid
#define pgdat_IntPcrPid	IHsvProgramData3_IntPcrPid
#define pgdat_IntVideoPid	IHsvProgramData3_IntVideoPid
#define pgdat_IntVideoStreamType	IHsvProgramData3_IntVideoStreamType
#define pgdat_IntAudioPid	IHsvProgramData3_IntAudioPid
#define pgdat_IntAudioStreamType	IHsvProgramData3_IntAudioStreamType
#define pgdat_IntSecAudioPid	IHsvProgramData3_IntSecAudioPid
#define pgdat_IntSecAudioStreamType	IHsvProgramData3_IntSecAudioStreamType
#define pgdat_IntInstallMode	IHsvProgramData3_IntInstallMode
#define pgdat_IntCniNi	IHsvProgramData3_IntCniNi
#define pgdat_IntDataIndicator	IHsvProgramData3_IntDataIndicator
#define pgdat_IntPresetNumber	IHsvProgramData3_IntPresetNumber
#define pgdat_IntModulationType	IHsvProgramData3_IntModulationType
#define pgdat_IntLCN	IHsvProgramData3_IntLCN
#define pgdat_IntStreamPriority	IHsvProgramData3_IntStreamPriority
#define pgdat_IntHMMapChannelNo	IHsvProgramData3_IntHMMapChannelNo
#define pgdat_IntPtc	IHsvProgramData3_IntPtc
#define pgdat_IntAssociatedDecoder	IHsvProgramData3_IntAssociatedDecoder
#define pgdat_IntChannelBandwidth	IHsvProgramData3_IntChannelBandwidth
#define pgdat_DecoderNone	IHsvProgramData3_DecoderNone
#define pgdat_DecoderExt1	IHsvProgramData3_DecoderExt1
#define pgdat_DecoderExt2	IHsvProgramData3_DecoderExt2
#define pgdat_Antenna	IHsvProgramData3_Antenna
#define pgdat_Cable	IHsvProgramData3_Cable
#define pgdat_IntSystemHidden	IHsvProgramData3_IntSystemHidden
#define pgdat_IntNumericSelect	IHsvProgramData3_IntNumericSelect
#define pgdat_IntNewChannel	IHsvProgramData3_IntNewChannel
#define pgdat_StringSatelliteName	IHsvProgramData3_StringSatelliteName
#define pgdat_IntSrcambledStatus	IHsvProgramData3_IntSrcambledStatus
#define pgdat_IntInstalledSatelliteNumber	IHsvProgramData3_IntInstalledSatelliteNumber
#define pgdat_IntUserHidden	IHsvProgramData3_IntUserHidden
#define pgdat_FavoriteNumber	IHsvProgramData3_FavoriteNumber
#define pgdat_FavoriteNumber1	IHsvProgramData3_FavoriteNumber1
#define pgdat_FavoriteNumber2	IHsvProgramData3_FavoriteNumber2
#define pgdat_FavoriteNumber3	IHsvProgramData3_FavoriteNumber3
#define pgdat_IntEPGEnabled	IHsvProgramData3_IntEPGEnabled
#define pgdat_IntHbbTvOption	IHsvProgramData3_IntHbbTvOption
#define pgdat_BoolChannelLock	IHsvProgramData3_BoolChannelLock
#define pgdat_StringTxtPages	IHsvProgramData3_StringTxtPages
#define pgdat_IntLogoURL	IHsvProgramData3_IntLogoURL
#define pgdat_BoolMatchBrandFlag	IHsvProgramData3_BoolMatchBrandFlag
#define pgdat_Nat32NumBrandIds	IHsvProgramData3_Nat32NumBrandIds
#define pgdat_StringBrandIds	IHsvProgramData3_StringBrandIds
#define pgdat_Nat16PrimaryRegion	IHsvProgramData3_Nat16PrimaryRegion
#define pgdat_Nat16SecondaryRegion	IHsvProgramData3_Nat16SecondaryRegion
#define pgdat_IntTertiaryRegion	IHsvProgramData3_IntTertiaryRegion
#define pgdat_Nat32CountryCode	IHsvProgramData3_Nat32CountryCode
#define pgdat_Nat64UniqueNodeId	IHsvProgramData3_Nat64UniqueNodeId
#define pgdat_BoolUserModifiedLogo	IHsvProgramData3_BoolUserModifiedLogo
#define pgdat_MultipleLCN	IHsvProgramData3_MultipleLCN
#define pgdat_MultiplePreset	IHsvProgramData3_MultiplePreset
#define pgdat_IsValidChannel(channel)	pgdat->IsValidChannel(channel)
#define pgdat_IsChannelInstalled(channel)	pgdat->IsChannelInstalled(channel)
#define pgdat_IsAttributeSupported(attribute)	pgdat->IsAttributeSupported(attribute)
#define pgdat_ClearCurrentTable()	pgdat->ClearCurrentTable()
#define pgdat_ClearAllTables()	pgdat->ClearAllTables()
#define pgdat_GetChannelDataBool(channel,dataid,value)	pgdat->GetChannelDataBool(channel,dataid,value)
#define pgdat_GetChannelDataInt(channel,dataid,value)	pgdat->GetChannelDataInt(channel,dataid,value)
#define pgdat_GetChannelDataNat32(channel,dataid,value)	pgdat->GetChannelDataNat32(channel,dataid,value)
#define pgdat_GetChannelDataString(channel,dataid,value,size)	pgdat->GetChannelDataString(channel,dataid,value,size)
#define pgdat_StoreChannelDataBool(channel,dataid,value)	pgdat->StoreChannelDataBool(channel,dataid,value)
#define pgdat_StoreChannelDataInt(channel,dataid,value)	pgdat->StoreChannelDataInt(channel,dataid,value)
#define pgdat_StoreChannelDataNat32(channel,dataid,value)	pgdat->StoreChannelDataNat32(channel,dataid,value)
#define pgdat_StoreChannelDataString(channel,dataid,value,size)	pgdat->StoreChannelDataString(channel,dataid,value,size)
#define pgdat_GetDigitalChannel(channel,OnId,TsId,Sid,Ptc)	pgdat->GetDigitalChannel(channel,OnId,TsId,Sid,Ptc)
#define pgdat_SwapChannels(channel1,channel2)	pgdat->SwapChannels(channel1,channel2)
#define pgdat_LoadChannelTable(dir)	pgdat->LoadChannelTable(dir)
#define pgdat_SaveChannelTable(dir)	pgdat->SaveChannelTable(dir)
#define pgdat_ReorderChannels(channel1,channel2,Swap)	pgdat->ReorderChannels(channel1,channel2,Swap)
#define pgdat_LoadChannelTableFromMedium(dir,medium)	pgdat->LoadChannelTableFromMedium(dir,medium)
#define pgdat_SaveChannelTableToMedium(dir,medium)	pgdat->SaveChannelTableToMedium(dir,medium)
#define pgdat_GetMediumFromTable(dir,medium)	pgdat->GetMediumFromTable(dir,medium)
#define pgdat_GetNoOfBarkerMultiplexes(NoOfMuxes)	pgdat->GetNoOfBarkerMultiplexes(NoOfMuxes)
#define pgdat_GetBarkerMultiplexByIndex(index,muxes)	pgdat->GetBarkerMultiplexByIndex(index,muxes)
#define pgdat_ReArrangeChannels(channel1,channel2)	pgdat->ReArrangeChannels(channel1,channel2)
#define pgdat_GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes)	pgdat->GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes)
#define pgdat_GetOperator(OperatorId)	pgdat->GetOperator(OperatorId)
#define pgdat_StoreChannelDataNat64(channel,dataid,value)	pgdat->StoreChannelDataNat64(channel,dataid,value)
#define pgdat_GetChannelDataNat64(channel,dataid,value)	pgdat->GetChannelDataNat64(channel,dataid,value)
#define pgdatcni_iPresent() (pgdatcni.Present())
#define pgdatcni_Add(cni,presetId)	pgdatcni->Add(cni,presetId)
#define pgdatcni_Remove(presetId)	pgdatcni->Remove(presetId)
#define pgdatcni_IsCniPresent(cni)	pgdatcni->IsCniPresent(cni)
#define pgdatcni_GetPreset(cni)	pgdatcni->GetPreset(cni)
#define pgdatcni_GetCni(pr)	pgdatcni->GetCni(pr)
#define pgdatcni_ClearCNIList()	pgdatcni->ClearCNIList()
#define pgdatcni_InvalidPreset	ISvcCniData_InvalidPreset
#define pgdatcni_MinCNIPreset	pgdatcni->MinCNIPreset()
#define pgdatcni_MaxCNIPreset	pgdatcni->MaxCNIPreset()
#define pgdb_iPresent() (pgdb.Present())
#define pgdb_GetCurrentTable()	pgdb->GetCurrentTable()
#define pgdb_SelectTable(tableid)	pgdb->SelectTable(tableid)
#define pgdb_ClearTable(tableid)	pgdb->ClearTable(tableid)
#define pgdb_IsSupported(tableid)	pgdb->IsSupported(tableid)
#define pgdb_CommitTable(tableid)	pgdb->CommitTable(tableid)
#define pgdb_LoadTable(tableid)	pgdb->LoadTable(tableid)
#define pgdb_GetNoRecords(tableid)	pgdb->GetNoRecords(tableid)
#define pgdb_GetByKey(tableid,channeldata)	pgdb->GetByKey(tableid,channeldata)
#define pgdb_GetIndex(tableid,index,channeldata)	pgdb->GetIndex(tableid,index,channeldata)
#define pgdb_GetByIndex(tableid,index,channeldata)	pgdb->GetByIndex(tableid,index,channeldata)
#define pgdb_GetRange(tableid,noofkeys,channeldata,from,to)	pgdb->GetRange(tableid,noofkeys,channeldata,from,to)
#define pgdb_Add(tableid,channeldata)	pgdb->Add(tableid,channeldata)
#define pgdb_Update(tableid,channeldata)	pgdb->Update(tableid,channeldata)
#define pgdb_Delete(tableid,channeldata)	pgdb->Delete(tableid,channeldata)
#define pgdb_EnableAutoCommit(enable)	pgdb->EnableAutoCommit(enable)
#define pgdb_ChannelTableChanged()	pgdb->ChannelTableChanged()
#define pgdb_Initialise(tableid,channeldata)	pgdb->Initialise(tableid,channeldata)
#define pgdb_MasterEnableEvents(Status)	pgdb->MasterEnableEvents(Status)
#define pgdb_SaveChannelMapsToBackup()	pgdb->SaveChannelMapsToBackup()
#define pgdb_LoadChannelMapsFromBackup()	pgdb->LoadChannelMapsFromBackup()
#define	pgdb_SqliteDatabase 	IHsvProgramDatabase_SqliteDatabase
#define	pgdb_TempDatabase 		IHsvProgramDatabase_TempDatabase
#define	pgdb_SelectActiveChannelDatabase(ActiveDb) 		pgdb->SelectActiveChannelDatabase(ActiveDb)
#define	pgdb_AddInIndex(tableid,index,channeldata)		pgdb->AddInIndex(tableid,index,channeldata)
#define	pgdb_BeginSqliteTransaction()					pgdb->BeginSqliteTransaction()
#define	pgdb_CommitSqliteTransaction()					pgdb->CommitSqliteTransaction()
#define pgdbconst_iPresent() (pgdbconst.Present())
#define pgdbconst_Antenna	IHsvProgramDatabaseConstants_Antenna
#define pgdbconst_Cable	IHsvProgramDatabaseConstants_Cable
#define pgdbconst_TempAntenna	IHsvProgramDatabaseConstants_TempAntenna
#define pgdbconst_TempCable	IHsvProgramDatabaseConstants_TempCable
#define pgdbconst_Satellite	IHsvProgramDatabaseConstants_Satellite
#define pgdbconst_TempSatellite	IHsvProgramDatabaseConstants_TempSatellite
#define pgdbconst_Analog	IHsvProgramDatabaseConstants_Analog
#define pgdbconst_DigitalTS	IHsvProgramDatabaseConstants_DigitalTS
#define pgdbconst_DigitalService	IHsvProgramDatabaseConstants_DigitalService
#define pgdbconst_Preset	IHsvProgramDatabaseConstants_Preset
#define pgdbconst_FrequencyMapTable	IHsvProgramDatabaseConstants_FrequencyMapTable
#define pgdbconst_CurrentDigitalService	IHsvProgramDatabaseConstants_CurrentDigitalService
#define pgdbconst_CurrentDigitalTS	IHsvProgramDatabaseConstants_CurrentDigitalTS
#define pgdbconst_CurrentAnalog	IHsvProgramDatabaseConstants_CurrentAnalog
#define pgdbconst_CurrentPreset	IHsvProgramDatabaseConstants_CurrentPreset
#define pgdbconst_CurrentFrequencyMapTable	IHsvProgramDatabaseConstants_CurrentFrequencyMapTable
#define pgdbconst_SatInfo	IHsvProgramDatabaseConstants_SatInfo
#define pgdbconst_CurrentSatInfo	IHsvProgramDatabaseConstants_CurrentSatInfo
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvPresetInstallation_m_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define prinsN_iPresent() (prinsN.Present())
#define prinsN_EventManualInstallationCniExtractionStarted	IHsvAnalogInstallationNotify_EventManualInstallationCniExtractionStarted
#define prinsN_EventManualInstallationCniExtractionEnded	IHsvAnalogInstallationNotify_EventManualInstallationCniExtractionEnded
#define prinsN_EventAutomaticInstallationCompleted	IHsvAnalogInstallationNotify_EventAutomaticInstallationCompleted
#define prinsN_EventChannelFound	IHsvAnalogInstallationNotify_EventChannelFound
#define prinsN_EventATSSortingStarted	IHsvAnalogInstallationNotify_EventATSSortingStarted
#define prinsN_EventAciStoreStarted	IHsvAnalogInstallationNotify_EventAciStoreStarted
#define prinsN_EventTvSystemChanged	IHsvAnalogInstallationNotify_EventTvSystemChanged
#define prinsN_EventManualInstallationChannelNotFound	IHsvAnalogInstallationNotify_EventManualInstallationChannelNotFound
#define prinsN_EventSearchInProgress	IHsvAnalogInstallationNotify_EventSearchInProgress
#define prinsN_EventTuningStarted	IHsvAnalogInstallationNotify_EventTuningStarted
#define prinsN_EventTuningStationFound	IHsvAnalogInstallationNotify_EventTuningStationFound
#define prinsN_EventTuningStationNotFound	IHsvAnalogInstallationNotify_EventTuningStationNotFound
#define prinsN_EventPhaseStarted	IHsvAnalogInstallationNotify_EventPhaseStarted
#define prinsN_EventPhaseCompleted	IHsvAnalogInstallationNotify_EventPhaseCompleted
#define prinsN_EventMultiPackageFound 	IHsvAnalogInstallationNotify_EventMultiPackageFound
#define	prinsN_EventMultiPackageToBeDisplayed 	IHsvAnalogInstallationNotify_EventMultiPackageToBeDisplayed
#define	prinsN_EventMultiPackageRemoved	 IHsvAnalogInstallationNotify_EventMultiPackageRemoved
#define prinsN_OnEvent(eventid,value)	prinsN->OnEvent(eventid,value)
#define prinsN_OnManualInstallationStored(channel)	prinsN->OnManualInstallationStored(channel)
#define prinsN_OnBackgroundCniUpdated(Cni,channel)	prinsN->OnBackgroundCniUpdated(Cni,channel)
#define prsort_iPresent() (prsort.Present())
#define prsort_Sort(listOfPresetData,sizeOfList,numPresets)	prsort->Sort(listOfPresetData,sizeOfList,numPresets)
#define prsort_GetPresetIndex(presetNo)	prsort->GetPresetIndex(presetNo)
#define prsort_GetPresetIndexList(sizeOfList)	prsort->GetPresetIndexList(sizeOfList)
#define rins_iPresent() (rins.Present())
#define rins_InvalidChannel	IHsvInstallation2_InvalidChannel
#define rins_InvalidFrequency	IHsvInstallation2_InvalidFrequency
#define rins_StIdle	IHsvInstallation2_StIdle
#define rins_StSourceSetupWait	IHsvInstallation2_StSourceSetupWait
#define rins_StDigital	IHsvInstallation2_StDigital
#define rins_StAnalog	IHsvInstallation2_StAnalog
#define rins_StPreSorting	IHsvInstallation2_StPreSorting
#define rins_StSorting	IHsvInstallation2_StSorting
#define rins_Terrestrial	IHsvInstallation2_Terrestrial
#define rins_Cable	IHsvInstallation2_Cable
#define rins_Satellite	IHsvInstallation2_Satellite
#define rins_InstallationInPassAnalog	IHsvInstallation2_InstallationInPassAnalog
#define rins_InstallationInDigitalPass	IHsvInstallation2_InstallationInDigitalPass
#define rins_InstallationStateScrambledSearch	IHsvInstallation2_InstallationStateScrambledSearch
#define rins_InstallationStateIdle	IHsvInstallation2_InstallationStateIdle
#define rins_InstallationStateInProgress	IHsvInstallation2_InstallationStateInProgress
#define rins_InstallationStatePaused	IHsvInstallation2_InstallationStatePaused
#define rins_InstallationModeNone	IHsvInstallation2_InstallationModeNone
#define rins_InstallationModeManual	IHsvInstallation2_InstallationModeManual
#define rins_InstallationModeAutomatic	IHsvInstallation2_InstallationModeAutomatic
#define rins_InstallationModeBackground	IHsvInstallation2_InstallationModeBackground
#define rins_InstallationModeImplicit	IHsvInstallation2_InstallationModeImplicit
#define rins_InstallationModeUpdate	IHsvInstallation2_InstallationModeUpdate
#define rins_InstallationModeWeakSignal	IHsvInstallation2_InstallationModeWeakSignal
#define rins_InstallationModeSingleChannel	IHsvInstallation2_InstallationModeSingleChannel
#define rins_InstallationModePreScan	IHsvInstallation2_InstallationModePreScan
#define rins_InstallationModeDtr	IHsvInstallation2_InstallationModeDtr
#define rins_InstallationModeCam	IHsvInstallation2_InstallationModeCam
#define rins_MaxChannel	IHsvInstallation2_MaxChannel
#define rins_ManualInstallationModeFrequency	IHsvInstallation2_ManualInstallationModeFrequency
#define rins_InsTvSystemBg	IHsvInstallation2_InsTvSystemBg
#define rins_InsTvSystemDk	IHsvInstallation2_InsTvSystemDk
#define rins_InsTvSystemI	IHsvInstallation2_InsTvSystemI
#define rins_InsTvSystemL	IHsvInstallation2_InsTvSystemL
#define rins_InsTvSystemN	IHsvInstallation2_InsTvSystemN
#define rins_InsTvSystemM	IHsvInstallation2_InsTvSystemM
#define rins_InsTvSystemAuto	IHsvInstallation2_InsTvSystemAuto
#define rins_InsColourSystemPal	IHsvInstallation2_InsColourSystemPal
#define rins_InsColurSystemSecam	IHsvInstallation2_InsColurSystemSecam
#define rins_InsColurSystemNtsc358	IHsvInstallation2_InsColurSystemNtsc358
#define rins_InsColurSystemNtsc443	IHsvInstallation2_InsColurSystemNtsc443
#define rins_InsColurSystemAuto	IHsvInstallation2_InsColurSystemAuto
#define rins_InsColurSystemInvalid	IHsvInstallation2_InsColurSystemInvalid
#define rins_InsColurSystemNtscUnknown	IHsvInstallation2_InsColurSystemNtscUnknown
#define rins_InsAssm	IHsvInstallation2_InsAssm
#define rins_InsVssm	IHsvInstallation2_InsVssm
#define rins_InsQssm	IHsvInstallation2_InsQssm
#define rins_InsSssm	IHsvInstallation2_InsSssm
#define rins_StartInstallation(source,ptc,mode)	rins->StartInstallation(source,ptc,mode)
#define rins_StopInstallation()	rins->StopInstallation()
#define rins_GetNumberOfAnalogChannelsFound()	rins->GetNumberOfAnalogChannelsFound()
#define rins_GetNumberOfDigitalChannelsFound()	rins->GetNumberOfDigitalChannelsFound()
#define rins_GetNumberOfDigitalChannelsRemoved()	rins->GetNumberOfDigitalChannelsRemoved()
#define rins_GetInstallationProgress()	rins->GetInstallationProgress()
#define rins_GetInstallationStatus()	rins->GetInstallationStatus()
#define rins_GetInstallationMode()	rins->GetInstallationMode()
#define rins_IsUpdateInstallationSupported()	rins->IsUpdateInstallationSupported()
#define rins_SetInstallCountry(country)	rins->SetInstallCountry(country)
#define rins_SetSystemCountry(country)	rins->SetSystemCountry(country)
#define rins_GetFirstIntalledDigitalChannel(channelno)	rins->GetFirstIntalledDigitalChannel(channelno)
#define rins_GetFirstIntalledAnalogueChannel(channelno)	rins->GetFirstIntalledAnalogueChannel(channelno)
#define rins_GetFirstIntalledRadioChannel(channelno)	rins->GetFirstIntalledRadioChannel(channelno)
#define rins_GetFirstInstalledChannel(channelno)	rins->GetFirstInstalledChannel(channelno)
#define rins_GetNetworkNameForNetworkID(networkID,NetworkName)	rins->GetNetworkNameForNetworkID(networkID,NetworkName)
#define rins_GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)	rins->GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)
#define rins_IsValidNetworkId(networkID)	rins->IsValidNetworkId(networkID)
#define rins_SetLowestNetworkId(networkID)	rins->SetLowestNetworkId(networkID)
#define rins_SetManualFrequency(frequency,offset,finetune)	rins->SetManualFrequency(frequency,offset,finetune)
#define rins_GetManualFrequency(frequency,offset,finetune)	rins->GetManualFrequency(frequency,offset,finetune)
#define rins_SetManualChannel(channel,finetune)	rins->SetManualChannel(channel,finetune)
#define rins_GetManualChannel(channel,finetune)	rins->GetManualChannel(channel,finetune)
#define rins_IsManualInstallationModeSupported(mode)	rins->IsManualInstallationModeSupported(mode)
#define rins_SetManualInstallationMode(mode)	rins->SetManualInstallationMode(mode)
#define rins_GetManualInstallationMode()	rins->GetManualInstallationMode()
#define rins_StoreManualInstallationValues(channel)	rins->StoreManualInstallationValues(channel)
#define rins_AutoStoreManualInstallationValues()	rins->AutoStoreManualInstallationValues()
#define rins_StartFrequencySearch()	rins->StartFrequencySearch()
#define rins_GetSigStrengthRange(measmode,min,max)	rins->GetSigStrengthRange(measmode,min,max)
#define rins_GetSignalstrength(measmode)	rins->GetSignalstrength(measmode)
#define rins_StoreWeakSignalInstallationChannel()	rins->StoreWeakSignalInstallationChannel()
#define rins_GetInstalledWeakSignalChannel()	rins->GetInstalledWeakSignalChannel()
#define rins_GetSignalQualityBer()	rins->GetSignalQualityBer()
#define rins_IsFrequencySearchDirectionSupported(searchup)	rins->IsFrequencySearchDirectionSupported(searchup)
#define rins_SetFrequencySearchDirection(searchup)	rins->SetFrequencySearchDirection(searchup)
#define rins_GetFrequencySearchDirection()	rins->GetFrequencySearchDirection()
#define rins_GetMinFrequency()	rins->GetMinFrequency()
#define rins_GetMaxFrequency()	rins->GetMaxFrequency()
#define rins_GetTunerFrequency()	rins->GetTunerFrequency()
#define rins_SetTunerFrequency(freq,fineTune)	rins->SetTunerFrequency(freq,fineTune)
#define rins_GetFrequency2Channel(chantbl,frequency)	rins->GetFrequency2Channel(chantbl,frequency)
#define rins_GetChannel2CarrierFrequency(chantbl,channel)	rins->GetChannel2CarrierFrequency(chantbl,channel)
#define rins_GetChannel2CentreFrequency(chantbl,channel)	rins->GetChannel2CentreFrequency(chantbl,channel)
#define rins_GetCurrentPass()	rins->GetCurrentPass()
#define rins_GetNoOfPass()	rins->GetNoOfPass()
#define rins_GetCurrentPassType()	rins->GetCurrentPassType()
#define rins_IsMediumSupported(medium)	rins->IsMediumSupported(medium)
#define rins_GetMedium()	rins->GetMedium()
#define rins_SetMedium(medium)	rins->SetMedium(medium)
#define rins_GetInstalledMedium()	rins->GetInstalledMedium()
#define rins_SetInstalledMedium(medium)	rins->SetInstalledMedium(medium)
#define rins_IsTvSystemSupported(tvsystem)	rins->IsTvSystemSupported(tvsystem)
#define rins_SetTvSystem(tvsystem)	rins->SetTvSystem(tvsystem)
#define rins_GetTvSystem()	rins->GetTvSystem()
#define rins_IsColorSystemSupported(colorsystem)	rins->IsColorSystemSupported(colorsystem)
#define rins_SetColorSystem(colorsystem)	rins->SetColorSystem(colorsystem)
#define rins_GetColorSystem()	rins->GetColorSystem()
#define rins_IsValidPTC(medium,PTC)	rins->IsValidPTC(medium,PTC)
#define rins_GetMinPTC(medium)	rins->GetMinPTC(medium)
#define rins_GetMaxPTC(medium)	rins->GetMaxPTC(medium)
#define rins_GetLastPTCFound()	rins->GetLastPTCFound()
#define rins_GetNumberOfPTCsFound()	rins->GetNumberOfPTCsFound()
#define rins_StartSigStrMeas(measmode)	rins->StartSigStrMeas(measmode)
#define rins_StopSigStrMeas(measmode)	rins->StopSigStrMeas(measmode)
#define rins_IsSignalStrengthMeasurementValid(measmode)	rins->IsSignalStrengthMeasurementValid(measmode)
#define rins_ScanNone	IHsvInstallation2_ScanNone
#define rins_ScanAnalog	IHsvInstallation2_ScanAnalog
#define rins_ScanDVBT	IHsvInstallation2_ScanDVBT
#define rins_ScanDVBC	IHsvInstallation2_ScanDVBC
#define rins_ScanDVBS	IHsvInstallation2_ScanDVBS
#define rins_AttributeScanMode	IHsvInstallation2_AttributeScanMode
#define rins_AttributeSymbolRate	IHsvInstallation2_AttributeSymbolRate
#define rins_AttributeNetworkId	IHsvInstallation2_AttributeNetworkId
#define rins_AttributeNetworkFreq	IHsvInstallation2_AttributeNetworkFreq
#define rins_AttributeModulation	IHsvInstallation2_AttributeModulation
#define rins_AttributeDigitalOption	IHsvInstallation2_AttributeDigitalOption
#define rins_AttributeFreqStepSize	IHsvInstallation2_AttributeFreqStepSize
#define rins_AttributeCity	IHsvInstallation2_AttributeCity
#define rins_AttributePrimaryRegion	IHsvInstallation2_AttributePrimaryRegion
#define rins_AttributeSecondaryRegion	IHsvInstallation2_AttributeSecondaryRegion
#define rins_AttributeTertiaryRegion	IHsvInstallation2_AttributeTertiaryRegion
#define rins_AttributeScrOrFTA	IHsvInstallation2_AttributeScrOrFTA
#define rins_AttributeNetworkOperator	IHsvInstallation2_AttributeNetworkOperator
#define rins_AttributeUpdateInstall	IHsvInstallation2_AttributeUpdateInstall
#define rins_AttributeAnalogEnabled	IHsvInstallation2_AttributeAnalogEnabled
#define rins_AttributePersistentFile	IHsvInstallation2_AttributePersistentFile
#define rins_AttributeLCNSorting	IHsvInstallation2_AttributeLCNSorting
#define rins_AttributeFavoriteChannelId	IHsvInstallation2_AttributeFavoriteChannelId
#define rins_QuickScan	IHsvInstallation2_QuickScan
#define rins_FullScan	IHsvInstallation2_FullScan
#define rins_GridScan	IHsvInstallation2_GridScan
#define rins_AutomaticValue	IHsvInstallation2_AutomaticValue
#define rins_ManualValue	IHsvInstallation2_ManualValue
#define rins_GetAttributeRange(installationmode,attribute,minValue,maxValue)	rins->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define rins_SetAttributeMode(installationmode,attribute,attributeMode)	rins->SetAttributeMode(installationmode,attribute,attributeMode)
#define rins_SetAttribute(installationmode,attribute,value)	rins->SetAttribute(installationmode,attribute,value)
#define rins_GetAttributeMode(installationmode,attribute)	rins->GetAttributeMode(installationmode,attribute)
#define rins_GetAttribute(installationmode,attribute)	rins->GetAttribute(installationmode,attribute)
#define rins_IsAvailable(installationmode,attribute)	rins->IsAvailable(installationmode,attribute)
#define rins_ResetAttributeToDefault(installationmode,attribute)	rins->ResetAttributeToDefault(installationmode,attribute)
#define rins_ResetAttributeToPersistent(installationmode,attribute)	rins->ResetAttributeToPersistent(installationmode,attribute)
#define rins_NitNone	IHsvInstallation2_NitNone
#define rins_NitActual	IHsvInstallation2_NitActual
#define rins_NitOther	IHsvInstallation2_NitOther
#define rins_GetTargetNitType(NetworkId)	rins->GetTargetNitType(NetworkId)
#define rins_IsNetworkUpdateDetected()	rins->IsNetworkUpdateDetected()
#define rins_DVBCStepSize1	IHsvInstallation2_DVBCStepSize1
#define rins_DVBCStepSize8	IHsvInstallation2_DVBCStepSize8
#define rins_Initialise()	rins->Initialise()
#define rins_SkipInstallationScans(ScanTypes)	rins->SkipInstallationScans(ScanTypes)
#define rins_GetAltTSValues(ONID,TSID)	rins->GetAltTSValues(ONID,TSID)
#define rins_SetUserSymbolRates(installationmode,values,len)	rins->SetUserSymbolRates(installationmode,values,len)
#define rins_GetUserSymbolRates(installationmode,values,len)	rins->GetUserSymbolRates(installationmode,values,len)
#define rins_GetPredefinedSymbolRates(installationmode,values,len)	rins->GetPredefinedSymbolRates(installationmode,values,len)
#define rins_GetNetworkIDList()	rins->GetNetworkIDList()
#define rins_GetNetworkIDName(index,NetworkName)	rins->GetNetworkIDName(index,NetworkName)
#define rins_SetFavouriteNetworkID(mode,attrib,index)	rins->SetFavouriteNetworkID(mode,attrib,index)
#define rins_SetFavouriteRegion(mode,index,RegionType)	rins->SetFavouriteRegion(mode,index,RegionType)
#define rins_None	IHsvInstallation2_None
#define rins_Ziggo	IHsvInstallation2_Ziggo
#define rins_UPC	IHsvInstallation2_UPC
#define rins_UnityMedia	IHsvInstallation2_UnityMedia
#define rins_Kdg	IHsvInstallation2_Kdg
#define rins_Telenet	IHsvInstallation2_Telenet
#define rins_RCSRDS	IHsvInstallation2_RCSRDS
#define rins_SetUserSelectConflictService(LcnIndex,SvcIndex)	rins->SetUserSelectConflictService(LcnIndex,SvcIndex)
#define rins_ConflictsSelectionDone(UserSelection)	rins->ConflictsSelectionDone(UserSelection)
#define rins_GetConflictServices(ConflictList,NumRecords)	rins->GetConflictServices(ConflictList,NumRecords)
#define rins_GetInstallationVersion()	rins->GetInstallationVersion()
#define rins_GetInstallationState()	rins->GetInstallationState()
#define rins_GetPLPIds(PLPIds)	rins->GetPLPIds(PLPIds)
#define rins_GetRegionList(RegionsData)	rins->GetRegionList(RegionsData)
#define rins_UserSelectionDone(UserSelection)	rins->UserSelectionDone(UserSelection)
#define rins_GetFavouriteRegion(mode,RegionType)	rins->GetFavouriteRegion(mode,RegionType)
#define rins_GetStreamPriority()	rins->GetStreamPriority()
#define rins_SetStreamPriority(prio)	rins->SetStreamPriority(prio)
#define rins_GetConstellation()	rins->GetConstellation()
#define rins_GetSymbolRate()	rins->GetSymbolRate()
#define rins_GetHierarchyMode()	rins->GetHierarchyMode()
#define rins_GetEpgBarkerMux(OnId,TsId)	rins->GetEpgBarkerMux(OnId,TsId)
#define rins_ZiggoNetworkDataSet(ActionValue)	rins->ZiggoNetworkDataSet(ActionValue)
#define rins_ClearPersistent()	rins->ClearPersistent()
#define sigstr_iPresent() (sigstr.Present())
#define sigstr_Initialise()	sigstr->Initialise()
#define sigstr_GetSigStrengthRange(mode,min,max)	sigstr->GetSigStrengthRange(mode,min,max)
#define sigstr_GetSignalStrength(mode)	sigstr->GetSignalStrength(mode)
#define sigstr_GetMinSignalStrength(mode)	sigstr->GetMinSignalStrength(mode)
#define sigstr_GetMaxSignalStrength(mode)	sigstr->GetMaxSignalStrength(mode)
#define sigstr_GetActualSignalStrength(mode,cookie)	sigstr->GetActualSignalStrength(mode,cookie)
#define sigstr_StartSigStrMeasAll()	sigstr->StartSigStrMeasAll()
#define sigstr_StopSigStrMeasAll()	sigstr->StopSigStrMeasAll()
#define sigstr_UpdateSigStrRange()	sigstr->UpdateSigStrRange()
#define sigstr_GetSigStrengthMeasured()	sigstr->GetSigStrengthMeasured()
#define sigstr_SetSigStrengthMeasured(flag)	sigstr->SetSigStrengthMeasured(flag)
#define sigstr_StartSigStrMeas(measmode)	sigstr->StartSigStrMeas(measmode)
#define sigstr_StopSigStrMeas(measmode)	sigstr->StopSigStrMeas(measmode)
#define sigstr_IsSignalStrengthMeasurementValid(measmode)	sigstr->IsSignalStrengthMeasurementValid(measmode)
#define sort_iPresent() (sort.Present())
#define sort_Initialise()	sort->Initialise()
#define sort_AddAnalogPreset(adata)	sort->AddAnalogPreset(adata)
#define sort_AnalogPresetEntry()	sort->AnalogPresetEntry()
#define sort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	sort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define sort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	sort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define sort_AssignPresetsOfOtherCountries()	sort->AssignPresetsOfOtherCountries()
#define sort_AddDigitalPreset(svcdat)	sort->AddDigitalPreset(svcdat)
#define sort_AutoStoreManualInstallationValues()	sort->AutoStoreManualInstallationValues()
#define sort_RemoveDigitalPresets()	sort->RemoveDigitalPresets()
#define sort_GetNumberOfAnalogChannelsFound()	sort->GetNumberOfAnalogChannelsFound()
#define sort_UpdateDigitalPreset(svcdat)	sort->UpdateDigitalPreset(svcdat)
#define sort_DeleteAllDigitalChannels()	sort->DeleteAllDigitalChannels()
#define sort_UpdatingLCNDuringUpdateInstallation()	sort->UpdatingLCNDuringUpdateInstallation()
#define sort_DeleteInvalidPTCTable()	sort->DeleteInvalidPTCTable()
#define sort_GetOriginalNetworkId(CurrentCountry)	sort->GetOriginalNetworkId(CurrentCountry)
#define sort_IsPresetInstalled(frequency)	sort->IsPresetInstalled(frequency)
#define sort_AssignPresetsForCountry(ONID)	sort->AssignPresetsForCountry(ONID)
#define sort_SortAll()	sort->SortAll()
#define sort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	sort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define sort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	sort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define sort_GetInstalledWeakSignalChannel()	sort->GetInstalledWeakSignalChannel()
#define str_iPresent() (str.Present())
#define str_strcmp(str1,str2)	str->strcmp(str1,str2)
#define str_strcmpRom(str1,str2)	str->strcmpRom(str1,str2)
#define str_strncmp(str1,str2,num)	str->strncmp(str1,str2,num)
#define str_strncmpRom(str1,str2,num)	str->strncmpRom(str1,str2,num)
#define str_strlen(str1)	str->strlen(str1)
#define str_strlenRom(str1)	str->strlenRom(str1)
#define str_strcpy(dest,source)	str->strcpy(dest,source)
#define str_strcpyRom(dest,source)	str->strcpyRom(dest,source)
#define str_strncpy(dest,source,num)	str->strncpy(dest,source,num)
#define str_strncpyRom(dest,source,num)	str->strncpyRom(dest,source,num)
#define str_strcat(dest,source)	str->strcat(dest,source)
#define str_strcatRom(dest,source)	str->strcatRom(dest,source)
#define str_strncat(dest,source,num)	str->strncat(dest,source,num)
#define str_strstr(book,word)	str->strstr(book,word)
#define str_strchr(book,letter)	str->strchr(book,letter)
#define sysctl_iPresent() (sysctl.Present())
#define sysctl_BlockDestinations(dest,OnOff)	sysctl->BlockDestinations(dest,OnOff)
#define sysctl_SetVideoMute(OnOff)	sysctl->SetVideoMute(OnOff)
#define sysctl_SetAudioMute(OnOff)	sysctl->SetAudioMute(OnOff)
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
#define txtpre_iPresent() (txtpre.Present())
#define txtpre_WstPresent()	txtpre->WstPresent()
#define txtpre_VpsPresent()	txtpre->VpsPresent()
#define vps_iPresent() (vps.Present())
#define vps_RequestDataFields(field_bit_vector,cb_fn,cb_on_every_update)	vps->RequestDataFields(field_bit_vector,cb_fn,cb_on_every_update)
#define vps_UnRequestDataFields(request_id)	vps->UnRequestDataFields(request_id)
#define vps_IsDataFieldsAvailable(field_bit_vector)	vps->IsDataFieldsAvailable(field_bit_vector)
#define vps_GetPilCode(ptr_pil_code)	vps->GetPilCode(ptr_pil_code)
#define vps_GetCountryNetworkIdentificationCode(ptr_cni)	vps->GetCountryNetworkIdentificationCode(ptr_cni)
#define vps_GetProgramType(ptr_ptype)	vps->GetProgramType(ptr_ptype)
#define vps_GetProgramControlStatus(ptr_ps)	vps->GetProgramControlStatus(ptr_ps)
#define vps_GetDistinctionBits(ptr_dist_bits)	vps->GetDistinctionBits(ptr_dist_bits)
#define vps_PilCodeField	IHsvTxtVpsData_PilCodeField
#define vps_CNICodeField	IHsvTxtVpsData_CNICodeField
#define vps_ProgramTypeField	IHsvTxtVpsData_ProgramTypeField
#define vps_ProgramControlStatusField	IHsvTxtVpsData_ProgramControlStatusField
#define vps_DistinctionBitsField	IHsvTxtVpsData_DistinctionBitsField
#define vps_InvalidRequestId	IHsvTxtVpsData_InvalidRequestId
#define wnddest_iPresent() (wnddest.Present())
#define wnddest_InvalidWindowId	wnddest->InvalidWindowId()
#define wnddest_GetWindowId(dest)	wnddest->GetWindowId(dest)
#define wnddest_GetAudioNodeId(dest)	wnddest->GetAudioNodeId(dest)
#define wnddest_GetMonitorWindow()	wnddest->GetMonitorWindow()
#define wnddest_WndTypeInvalid	IHsvWindowDestinationMap_WndTypeInvalid
#define wnddest_WndTypeMainVideo	IHsvWindowDestinationMap_WndTypeMainVideo
#define wnddest_WndTypeMainAudio	IHsvWindowDestinationMap_WndTypeMainAudio
#define wnddest_WndTypeMonitor	IHsvWindowDestinationMap_WndTypeMonitor
#define wnddest_WndTypeAuxVideo	IHsvWindowDestinationMap_WndTypeAuxVideo
#define wnddest_GetWindowType(winid)	wnddest->GetWindowType(winid)
#define wnddest_GetDestinationForWindow(windowid)	wnddest->GetDestinationForWindow(windowid)
#define prins_InvalidCni	IHsvAnalogInstallation_InvalidCni
#define prins_InvalidChannel	i__prins.m_InvalidChannel
#define prins_InvalidFrequency	i__prins.m_InvalidFrequency
#define prins_InstallationStateIdle	IHsvAnalogInstallation_InstallationStateIdle
#define prins_InstallationStateInProgress	IHsvAnalogInstallation_InstallationStateInProgress
#define prins_InstallationModeNone	IHsvAnalogInstallation_InstallationModeNone
#define prins_InstallationModeManual	IHsvAnalogInstallation_InstallationModeManual
#define prins_InstallationModeAutomatic	IHsvAnalogInstallation_InstallationModeAutomatic
#define prins_InstallationModeBackground	IHsvAnalogInstallation_InstallationModeBackground
#define prins_InstallationModeImplicit	IHsvAnalogInstallation_InstallationModeImplicit
#define prins_SChannel	IHsvAnalogInstallation_SChannel
#define prins_CChannel	IHsvAnalogInstallation_CChannel
#define prins_ManualInstallationModeFrequency	IHsvAnalogInstallation_ManualInstallationModeFrequency
#define prins_ManualInstallationModeSChannel	IHsvAnalogInstallation_ManualInstallationModeSChannel
#define prins_ManualInstallationModeCChannel	IHsvAnalogInstallation_ManualInstallationModeCChannel
#define prins_InsTvSystemBg	IHsvAnalogInstallation_InsTvSystemBg
#define prins_InsTvSystemDk	IHsvAnalogInstallation_InsTvSystemDk
#define prins_InsTvSystemI	IHsvAnalogInstallation_InsTvSystemI
#define prins_InsTvSystemL	IHsvAnalogInstallation_InsTvSystemL
#define prins_InsTvSystemM	IHsvAnalogInstallation_InsTvSystemM
#define prins_InsTvSystemAuto	IHsvAnalogInstallation_InsTvSystemAuto
#define prins_InsColourSystemPal	IHsvAnalogInstallation_InsColourSystemPal
#define prins_InsColourSystemSecam	IHsvAnalogInstallation_InsColourSystemSecam
#define prins_InsColourSystemNtsc358	IHsvAnalogInstallation_InsColourSystemNtsc358
#define prins_InsColourSystemNtsc443	IHsvAnalogInstallation_InsColourSystemNtsc443
#define prins_InsColourSystemAuto	IHsvAnalogInstallation_InsColourSystemAuto
#define prins_InsColourSystemInvalid	IHsvAnalogInstallation_InsColourSystemInvalid
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

