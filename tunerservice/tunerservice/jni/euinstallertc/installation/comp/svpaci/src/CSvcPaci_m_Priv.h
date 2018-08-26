#ifndef  _CSVCPACI_M_PRIV_H
#define  _CSVCPACI_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciDecodeNotify.h>
#include <IHsvAciDisplay.h>
#include <ISvcAciInstallation.h>
#include <IHsvInstallationNotify.h>
#include <ISvPower.h>
#include <ISvcTxtResetNotify.h>
#include <IHsvAciData.h>
#include <IHsvAciDecode.h>
#include <IHsvAciDisplayNotify.h>
#include <ICesPaciDiv.h>
#include <IHsvLanguageIds2.h>
#include <IPumpEngine.h>
#include <IHsvAciInstallationSubNotify.h>
#include <ISvcCniData.h>
#include <IHsvTxtPacket0.h>
#include <IPumpExSub.h>
#include <IHsvInstallation2.h>
#include <IHsvTcSystemSettings.h>
#include <IInfraTimerServer.h>
#include <IHsvTxtPresent.h>
#include <ITvVideoProperties3Ex.h>
#include <CTCMwBase.h>
class CSvcPaci_m_Priv;
#define CLASSSCOPE CSvcPaci_m_Priv::
#include "locals_m.h"

class CSvcPaci_m_Priv : public CTCMwBase
{
public:
virtual ~CSvcPaci_m_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvAciDecodeNotifyImpl(CSvcPaci_m_Priv,acidecN);
IHsvAciDisplayImpl(CSvcPaci_m_Priv,acids);
ISvcAciInstallationImpl(CSvcPaci_m_Priv,pgaci);
IHsvInstallationNotifyImpl(CSvcPaci_m_Priv,pginsN);
ISvPowerImpl(CSvcPaci_m_Priv,pow);
ISvcTxtResetNotifyImpl(CSvcPaci_m_Priv,txrstN);
public:
ProvidesInterface<IHsvAciDecodeNotify>	acidecN;

ProvidesInterface<IHsvAciDisplay>	acids;

ProvidesInterface<ISvcAciInstallation>	pgaci;

ProvidesInterface<IHsvInstallationNotify>	pginsN;

ProvidesInterface<ISvPower>	pow;

ProvidesInterface<ISvcTxtResetNotify>	txrstN;

//Required interfaces
public:
RequiresInterface<IHsvAciData>	acidat;
RequiresInterface<IHsvAciDecode>	acidec;
RequiresInterface<IHsvAciDisplayNotify>	acidsN;
RequiresInterface<ICesPaciDiv>	adiv;
RequiresInterface<IHsvLanguageIds2>	langid;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvAciInstallationSubNotify>	pgaciN;
RequiresInterface<ISvcCniData>	pgcni;
RequiresInterface<IHsvTxtPacket0>	pkt0;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvInstallation2>	prins;
RequiresInterface<IHsvTcSystemSettings>	sysset;
RequiresInterface<IInfraTimerServer>	tmr;
RequiresInterface<IHsvTxtPresent>	txtpre;
RequiresInterface<ITvVideoProperties3Ex>	vip;
private:
Pumpdefines(CSvcPaci_m_Priv);

public:
CSvcPaci_m_Priv():i__acidecN(this),i__acids(this),i__pgaci(this),i__pginsN(this),i__pow(this),i__txrstN(this)
{
acidecN	=	&i__acidecN;
acids	=	&i__acids;
pgaci	=	&i__pgaci;
pginsN	=	&i__pginsN;
pow	=	&i__pow;
txrstN	=	&i__txrstN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define acidat_iPresent() (acidat.Present())
#define acidat_StorePreset(presetInfo,clear)	acidat->StorePreset(presetInfo,clear)
#define acidat_GetAciLanguage(language)	acidat->GetAciLanguage(language)
#define acidec_iPresent() (acidec.Present())
#define acidec_DecodeStart(pn)	acidec->DecodeStart(pn)
#define acidec_DecodeStop()	acidec->DecodeStop()
#define acidec_Reset()	acidec->Reset()
#define acidec_GetDecodeStatus()	acidec->GetDecodeStatus()
#define acidec_ContinueDecoding()	acidec->ContinueDecoding()
#define acidec_GetMode()	acidec->GetMode()
#define acidec_GetNetworkInformation()	acidec->GetNetworkInformation()
#define acidec_GetBroadcasterInformation()	acidec->GetBroadcasterInformation()
#define acidec_GetNoOfPresetEntries()	acidec->GetNoOfPresetEntries()
#define acidec_GetNoOfMultipackageItems()	acidec->GetNoOfMultipackageItems()
#define acidec_GetAciLanguage(lanIndex)	acidec->GetAciLanguage(lanIndex)
#define acidec_GetExtensionPageForLanguage(lan)	acidec->GetExtensionPageForLanguage(lan)
#define acidec_GetExtensionPage()	acidec->GetExtensionPage()
#define acidec_GetSinglePackageInformation(packageIndex,singleInfo)	acidec->GetSinglePackageInformation(packageIndex,singleInfo)
#define acidec_GetMultiPackageInformation(packageIndex,multiInfo)	acidec->GetMultiPackageInformation(packageIndex,multiInfo)
#define acidec_GetDefaultPage()	acidec->GetDefaultPage()
#define acidec_MatchServiceLabel(srcLabel)	acidec->MatchServiceLabel(srcLabel)
#define acidec_DisplayACIPage(pn)	acidec->DisplayACIPage(pn)
#define acidec_IsAciPresent()	acidec->IsAciPresent()
#define acidec_SetCursor(item)	acidec->SetCursor(item)
#define acidec_RemoveCursor()	acidec->RemoveCursor()
#define acidec_RemoveACIPage(pn)	acidec->RemoveACIPage(pn)
#define acidec_ConstAciPage	IHsvAciDecode_ConstAciPage
#define acidec_StateIdle	IHsvAciDecode_StateIdle
#define acidec_StateDecoding	IHsvAciDecode_StateDecoding
#define acidec_StateSuccess	IHsvAciDecode_StateSuccess
#define acidec_StateFail	IHsvAciDecode_StateFail
#define acidsN_iPresent() (acidsN.Present())
#define acidsN_OnMultiPackageFound()	acidsN->OnMultiPackageFound()
#define acidsN_OnMultiPackageToBeDisplayed()	acidsN->OnMultiPackageToBeDisplayed()
#define acidsN_OnMultiPackageDisplayed()	acidsN->OnMultiPackageDisplayed()
#define acidsN_OnMultiPackageRemoved()	acidsN->OnMultiPackageRemoved()
#define adiv_iPresent() (adiv.Present())
#define adiv_MaxPresets	ICesPaciDiv_MaxPresets
#define adiv_MaxTunPreset	adiv->MaxTunPreset()
#define adiv_MinTunPreset	adiv->MinTunPreset()
#define adiv_AciAcquisitionTimeoutTime	adiv->AciAcquisitionTimeoutTime()
#define adiv_RestorePageAcqTimeoutTime	adiv->RestorePageAcqTimeoutTime()
#define adiv_MultipageDisplayTimeoutTime	adiv->MultipageDisplayTimeoutTime()
#define adiv_AciTxtHdrReqDelay	adiv->AciTxtHdrReqDelay()
#define adiv_TunNotifyTimeout	adiv->TunNotifyTimeout()
#define langid_iPresent() (langid.Present())
#define langid_LangEnglish	IHsvLanguageIds2_LangEnglish
#define langid_LangGerman	IHsvLanguageIds2_LangGerman
#define langid_LangSwedish	IHsvLanguageIds2_LangSwedish
#define langid_LangItalian	IHsvLanguageIds2_LangItalian
#define langid_LangFrench	IHsvLanguageIds2_LangFrench
#define langid_LangSpanish	IHsvLanguageIds2_LangSpanish
#define langid_LangCzech	IHsvLanguageIds2_LangCzech
#define langid_LangPolish	IHsvLanguageIds2_LangPolish
#define langid_LangTurkish	IHsvLanguageIds2_LangTurkish
#define langid_LangRussian	IHsvLanguageIds2_LangRussian
#define langid_LangGreek	IHsvLanguageIds2_LangGreek
#define langid_LangBasque	IHsvLanguageIds2_LangBasque
#define langid_LangCatalan	IHsvLanguageIds2_LangCatalan
#define langid_LangCroatian	IHsvLanguageIds2_LangCroatian
#define langid_LangDanish	IHsvLanguageIds2_LangDanish
#define langid_LangDutch	IHsvLanguageIds2_LangDutch
#define langid_LangFinnish	IHsvLanguageIds2_LangFinnish
#define langid_LangGaelic	IHsvLanguageIds2_LangGaelic
#define langid_LangGalligan	IHsvLanguageIds2_LangGalligan
#define langid_LangNorwegian	IHsvLanguageIds2_LangNorwegian
#define langid_LangPortuguese	IHsvLanguageIds2_LangPortuguese
#define langid_LangSerbian	IHsvLanguageIds2_LangSerbian
#define langid_LangSlovak	IHsvLanguageIds2_LangSlovak
#define langid_LangSlovenian	IHsvLanguageIds2_LangSlovenian
#define langid_LangWelsh	IHsvLanguageIds2_LangWelsh
#define langid_LangRomanian	IHsvLanguageIds2_LangRomanian
#define langid_LangEstonian	IHsvLanguageIds2_LangEstonian
#define langid_LangUkrainian	IHsvLanguageIds2_LangUkrainian
#define langid_LangArabic	IHsvLanguageIds2_LangArabic
#define langid_LangHebrew	IHsvLanguageIds2_LangHebrew
#define langid_LangHungarian	IHsvLanguageIds2_LangHungarian
#define langid_LangHungal	IHsvLanguageIds2_LangHungal
#define langid_LangMalay	IHsvLanguageIds2_LangMalay
#define langid_LangPersian	IHsvLanguageIds2_LangPersian
#define langid_LangSimplifiedchinese	IHsvLanguageIds2_LangSimplifiedchinese
#define langid_LangTaiwanese	IHsvLanguageIds2_LangTaiwanese
#define langid_LangBrazilianPortuguese	IHsvLanguageIds2_LangBrazilianPortuguese
#define langid_LangBulgarian	IHsvLanguageIds2_LangBulgarian
#define langid_LangLatinspanish	IHsvLanguageIds2_LangLatinspanish
#define langid_LangLithuanian	IHsvLanguageIds2_LangLithuanian
#define langid_LangLatvian	IHsvLanguageIds2_LangLatvian
#define langid_LangKazakh	IHsvLanguageIds2_LangKazakh
#define langid_LangThai	IHsvLanguageIds2_LangThai
#define langid_LangIrish	IHsvLanguageIds2_LangIrish
#define langid_LangUndefined	IHsvLanguageIds2_LangUndefined
#define langid_LangOriginalVersion	IHsvLanguageIds2_LangOriginalVersion
#define langid_LangAudioDescription	IHsvLanguageIds2_LangAudioDescription
#define langid_LangNone	IHsvLanguageIds2_LangNone
#define langid_MaxNumberOfLanguages	langid->MaxNumberOfLanguages()
#define langid_iVersion	langid->iVersion()
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pgaciN_iPresent() (pgaciN.Present())
#define pgaciN_OnAciInstallationCompleted(success)	pgaciN->OnAciInstallationCompleted(success)
#define pgaciN_aciPresetsWriteInDataStarted()	pgaciN->aciPresetsWriteInDataStarted()
#define pgcni_iPresent() (pgcni.Present())
#define pgcni_Add(cni,presetId)	pgcni->Add(cni,presetId)
#define pgcni_Remove(presetId)	pgcni->Remove(presetId)
#define pgcni_IsCniPresent(cni)	pgcni->IsCniPresent(cni)
#define pgcni_GetPreset(cni)	pgcni->GetPreset(cni)
#define pgcni_GetCni(pr)	pgcni->GetCni(pr)
#define pgcni_ClearCNIList()	pgcni->ClearCNIList()
#define pgcni_InvalidPreset	ISvcCniData_InvalidPreset
#define pgcni_MinCNIPreset	pgcni->MinCNIPreset()
#define pgcni_MaxCNIPreset	pgcni->MaxCNIPreset()
#define pkt0_iPresent() (pkt0.Present())
#define pkt0_GetLatestHeader(pkt0ptr,mag)	pkt0->GetLatestHeader(pkt0ptr,mag)
#define pkt0_GetLatestTime(time_ptr)	pkt0->GetLatestTime(time_ptr)
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CSvcPaci_m_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define prins_iPresent() (prins.Present())
#define prins_InvalidChannel	IHsvInstallation2_InvalidChannel
#define prins_InvalidFrequency	IHsvInstallation2_InvalidFrequency
#define prins_StIdle	IHsvInstallation2_StIdle
#define prins_StSourceSetupWait	IHsvInstallation2_StSourceSetupWait
#define prins_StDigital	IHsvInstallation2_StDigital
#define prins_StAnalog	IHsvInstallation2_StAnalog
#define prins_StPreSorting	IHsvInstallation2_StPreSorting
#define prins_StSorting	IHsvInstallation2_StSorting
#define prins_Terrestrial	IHsvInstallation2_Terrestrial
#define prins_Cable	IHsvInstallation2_Cable
#define prins_Satellite	IHsvInstallation2_Satellite
#define prins_InstallationInPassAnalog	IHsvInstallation2_InstallationInPassAnalog
#define prins_InstallationInDigitalPass	IHsvInstallation2_InstallationInDigitalPass
#define prins_InstallationStateScrambledSearch	IHsvInstallation2_InstallationStateScrambledSearch
#define prins_InstallationStateIdle	IHsvInstallation2_InstallationStateIdle
#define prins_InstallationStateInProgress	IHsvInstallation2_InstallationStateInProgress
#define prins_InstallationStatePaused	IHsvInstallation2_InstallationStatePaused
#define prins_InstallationModeNone	IHsvInstallation2_InstallationModeNone
#define prins_InstallationModeManual	IHsvInstallation2_InstallationModeManual
#define prins_InstallationModeAutomatic	IHsvInstallation2_InstallationModeAutomatic
#define prins_InstallationModeBackground	IHsvInstallation2_InstallationModeBackground
#define prins_InstallationModeImplicit	IHsvInstallation2_InstallationModeImplicit
#define prins_InstallationModeUpdate	IHsvInstallation2_InstallationModeUpdate
#define prins_InstallationModeWeakSignal	IHsvInstallation2_InstallationModeWeakSignal
#define prins_InstallationModeSingleChannel	IHsvInstallation2_InstallationModeSingleChannel
#define prins_InstallationModePreScan	IHsvInstallation2_InstallationModePreScan
#define prins_InstallationModeDtr	IHsvInstallation2_InstallationModeDtr
#define prins_InstallationModeCam	IHsvInstallation2_InstallationModeCam
#define prins_MaxChannel	IHsvInstallation2_MaxChannel
#define prins_ManualInstallationModeFrequency	IHsvInstallation2_ManualInstallationModeFrequency
#define prins_InsTvSystemBg	IHsvInstallation2_InsTvSystemBg
#define prins_InsTvSystemDk	IHsvInstallation2_InsTvSystemDk
#define prins_InsTvSystemI	IHsvInstallation2_InsTvSystemI
#define prins_InsTvSystemL	IHsvInstallation2_InsTvSystemL
#define prins_InsTvSystemN	IHsvInstallation2_InsTvSystemN
#define prins_InsTvSystemM	IHsvInstallation2_InsTvSystemM
#define prins_InsTvSystemAuto	IHsvInstallation2_InsTvSystemAuto
#define prins_InsColourSystemPal	IHsvInstallation2_InsColourSystemPal
#define prins_InsColurSystemSecam	IHsvInstallation2_InsColurSystemSecam
#define prins_InsColurSystemNtsc358	IHsvInstallation2_InsColurSystemNtsc358
#define prins_InsColurSystemNtsc443	IHsvInstallation2_InsColurSystemNtsc443
#define prins_InsColurSystemAuto	IHsvInstallation2_InsColurSystemAuto
#define prins_InsColurSystemInvalid	IHsvInstallation2_InsColurSystemInvalid
#define prins_InsColurSystemNtscUnknown	IHsvInstallation2_InsColurSystemNtscUnknown
#define prins_InsAssm	IHsvInstallation2_InsAssm
#define prins_InsVssm	IHsvInstallation2_InsVssm
#define prins_InsQssm	IHsvInstallation2_InsQssm
#define prins_InsSssm	IHsvInstallation2_InsSssm
#define prins_StartInstallation(source,ptc,mode)	prins->StartInstallation(source,ptc,mode)
#define prins_StopInstallation()	prins->StopInstallation()
#define prins_GetNumberOfAnalogChannelsFound()	prins->GetNumberOfAnalogChannelsFound()
#define prins_GetNumberOfDigitalChannelsFound()	prins->GetNumberOfDigitalChannelsFound()
#define prins_GetNumberOfDigitalChannelsRemoved()	prins->GetNumberOfDigitalChannelsRemoved()
#define prins_GetInstallationProgress()	prins->GetInstallationProgress()
#define prins_GetInstallationStatus()	prins->GetInstallationStatus()
#define prins_GetInstallationMode()	prins->GetInstallationMode()
#define prins_IsUpdateInstallationSupported()	prins->IsUpdateInstallationSupported()
#define prins_SetInstallCountry(country)	prins->SetInstallCountry(country)
#define prins_SetSystemCountry(country)	prins->SetSystemCountry(country)
#define prins_GetFirstIntalledDigitalChannel(channelno)	prins->GetFirstIntalledDigitalChannel(channelno)
#define prins_GetFirstIntalledAnalogueChannel(channelno)	prins->GetFirstIntalledAnalogueChannel(channelno)
#define prins_GetFirstIntalledRadioChannel(channelno)	prins->GetFirstIntalledRadioChannel(channelno)
#define prins_GetFirstInstalledChannel(channelno)	prins->GetFirstInstalledChannel(channelno)
#define prins_GetNetworkNameForNetworkID(networkID,NetworkName)	prins->GetNetworkNameForNetworkID(networkID,NetworkName)
#define prins_GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)	prins->GetListOfNetworkIDs(NumberOfEntries,NetworkIDList)
#define prins_IsValidNetworkId(networkID)	prins->IsValidNetworkId(networkID)
#define prins_SetLowestNetworkId(networkID)	prins->SetLowestNetworkId(networkID)
#define prins_SetManualFrequency(frequency,offset,finetune)	prins->SetManualFrequency(frequency,offset,finetune)
#define prins_GetManualFrequency(frequency,offset,finetune)	prins->GetManualFrequency(frequency,offset,finetune)
#define prins_SetManualChannel(channel,finetune)	prins->SetManualChannel(channel,finetune)
#define prins_GetManualChannel(channel,finetune)	prins->GetManualChannel(channel,finetune)
#define prins_IsManualInstallationModeSupported(mode)	prins->IsManualInstallationModeSupported(mode)
#define prins_SetManualInstallationMode(mode)	prins->SetManualInstallationMode(mode)
#define prins_GetManualInstallationMode()	prins->GetManualInstallationMode()
#define prins_StoreManualInstallationValues(channel)	prins->StoreManualInstallationValues(channel)
#define prins_AutoStoreManualInstallationValues()	prins->AutoStoreManualInstallationValues()
#define prins_StartFrequencySearch()	prins->StartFrequencySearch()
#define prins_GetSigStrengthRange(measmode,min,max)	prins->GetSigStrengthRange(measmode,min,max)
#define prins_GetSignalstrength(measmode)	prins->GetSignalstrength(measmode)
#define prins_StoreWeakSignalInstallationChannel()	prins->StoreWeakSignalInstallationChannel()
#define prins_GetInstalledWeakSignalChannel()	prins->GetInstalledWeakSignalChannel()
#define prins_GetSignalQualityBer()	prins->GetSignalQualityBer()
#define prins_IsFrequencySearchDirectionSupported(searchup)	prins->IsFrequencySearchDirectionSupported(searchup)
#define prins_SetFrequencySearchDirection(searchup)	prins->SetFrequencySearchDirection(searchup)
#define prins_GetFrequencySearchDirection()	prins->GetFrequencySearchDirection()
#define prins_GetMinFrequency()	prins->GetMinFrequency()
#define prins_GetMaxFrequency()	prins->GetMaxFrequency()
#define prins_GetTunerFrequency()	prins->GetTunerFrequency()
#define prins_SetTunerFrequency(freq,fineTune)	prins->SetTunerFrequency(freq,fineTune)
#define prins_GetFrequency2Channel(chantbl,frequency)	prins->GetFrequency2Channel(chantbl,frequency)
#define prins_GetChannel2CarrierFrequency(chantbl,channel)	prins->GetChannel2CarrierFrequency(chantbl,channel)
#define prins_GetChannel2CentreFrequency(chantbl,channel)	prins->GetChannel2CentreFrequency(chantbl,channel)
#define prins_GetCurrentPass()	prins->GetCurrentPass()
#define prins_GetNoOfPass()	prins->GetNoOfPass()
#define prins_GetCurrentPassType()	prins->GetCurrentPassType()
#define prins_IsMediumSupported(medium)	prins->IsMediumSupported(medium)
#define prins_GetMedium()	prins->GetMedium()
#define prins_SetMedium(medium)	prins->SetMedium(medium)
#define prins_GetInstalledMedium()	prins->GetInstalledMedium()
#define prins_SetInstalledMedium(medium)	prins->SetInstalledMedium(medium)
#define prins_IsTvSystemSupported(tvsystem)	prins->IsTvSystemSupported(tvsystem)
#define prins_SetTvSystem(tvsystem)	prins->SetTvSystem(tvsystem)
#define prins_GetTvSystem()	prins->GetTvSystem()
#define prins_IsColorSystemSupported(colorsystem)	prins->IsColorSystemSupported(colorsystem)
#define prins_SetColorSystem(colorsystem)	prins->SetColorSystem(colorsystem)
#define prins_GetColorSystem()	prins->GetColorSystem()
#define prins_IsValidPTC(medium,PTC)	prins->IsValidPTC(medium,PTC)
#define prins_GetMinPTC(medium)	prins->GetMinPTC(medium)
#define prins_GetMaxPTC(medium)	prins->GetMaxPTC(medium)
#define prins_GetLastPTCFound()	prins->GetLastPTCFound()
#define prins_GetNumberOfPTCsFound()	prins->GetNumberOfPTCsFound()
#define prins_StartSigStrMeas(measmode)	prins->StartSigStrMeas(measmode)
#define prins_StopSigStrMeas(measmode)	prins->StopSigStrMeas(measmode)
#define prins_IsSignalStrengthMeasurementValid(measmode)	prins->IsSignalStrengthMeasurementValid(measmode)
#define prins_ScanNone	IHsvInstallation2_ScanNone
#define prins_ScanAnalog	IHsvInstallation2_ScanAnalog
#define prins_ScanDVBT	IHsvInstallation2_ScanDVBT
#define prins_ScanDVBC	IHsvInstallation2_ScanDVBC
#define prins_ScanDVBS	IHsvInstallation2_ScanDVBS
#define prins_AttributeScanMode	IHsvInstallation2_AttributeScanMode
#define prins_AttributeSymbolRate	IHsvInstallation2_AttributeSymbolRate
#define prins_AttributeNetworkId	IHsvInstallation2_AttributeNetworkId
#define prins_AttributeNetworkFreq	IHsvInstallation2_AttributeNetworkFreq
#define prins_AttributeModulation	IHsvInstallation2_AttributeModulation
#define prins_AttributeDigitalOption	IHsvInstallation2_AttributeDigitalOption
#define prins_AttributeFreqStepSize	IHsvInstallation2_AttributeFreqStepSize
#define prins_AttributeCity	IHsvInstallation2_AttributeCity
#define prins_AttributePrimaryRegion	IHsvInstallation2_AttributePrimaryRegion
#define prins_AttributeSecondaryRegion	IHsvInstallation2_AttributeSecondaryRegion
#define prins_AttributeTertiaryRegion	IHsvInstallation2_AttributeTertiaryRegion
#define prins_AttributeScrOrFTA	IHsvInstallation2_AttributeScrOrFTA
#define prins_AttributeNetworkOperator	IHsvInstallation2_AttributeNetworkOperator
#define prins_AttributeUpdateInstall	IHsvInstallation2_AttributeUpdateInstall
#define prins_AttributeAnalogEnabled	IHsvInstallation2_AttributeAnalogEnabled
#define prins_AttributePersistentFile	IHsvInstallation2_AttributePersistentFile
#define prins_AttributeLCNSorting	IHsvInstallation2_AttributeLCNSorting
#define prins_QuickScan	IHsvInstallation2_QuickScan
#define prins_FullScan	IHsvInstallation2_FullScan
#define prins_GridScan	IHsvInstallation2_GridScan
#define prins_AutomaticValue	IHsvInstallation2_AutomaticValue
#define prins_ManualValue	IHsvInstallation2_ManualValue
#define prins_GetAttributeRange(installationmode,attribute,minValue,maxValue)	prins->GetAttributeRange(installationmode,attribute,minValue,maxValue)
#define prins_SetAttributeMode(installationmode,attribute,attributeMode)	prins->SetAttributeMode(installationmode,attribute,attributeMode)
#define prins_SetAttribute(installationmode,attribute,value)	prins->SetAttribute(installationmode,attribute,value)
#define prins_GetAttributeMode(installationmode,attribute)	prins->GetAttributeMode(installationmode,attribute)
#define prins_GetAttribute(installationmode,attribute)	prins->GetAttribute(installationmode,attribute)
#define prins_IsAvailable(installationmode,attribute)	prins->IsAvailable(installationmode,attribute)
#define prins_ResetAttributeToDefault(installationmode,attribute)	prins->ResetAttributeToDefault(installationmode,attribute)
#define prins_ResetAttributeToPersistent(installationmode,attribute)	prins->ResetAttributeToPersistent(installationmode,attribute)
#define prins_NitNone	IHsvInstallation2_NitNone
#define prins_NitActual	IHsvInstallation2_NitActual
#define prins_NitOther	IHsvInstallation2_NitOther
#define prins_GetTargetNitType(NetworkId)	prins->GetTargetNitType(NetworkId)
#define prins_IsNetworkUpdateDetected()	prins->IsNetworkUpdateDetected()
#define prins_DVBCStepSize1	IHsvInstallation2_DVBCStepSize1
#define prins_DVBCStepSize8	IHsvInstallation2_DVBCStepSize8
#define prins_Initialise()	prins->Initialise()
#define prins_SkipInstallationScans(ScanTypes)	prins->SkipInstallationScans(ScanTypes)
#define prins_GetAltTSValues(ONID,TSID)	prins->GetAltTSValues(ONID,TSID)
#define prins_SetUserSymbolRates(installationmode,values,len)	prins->SetUserSymbolRates(installationmode,values,len)
#define prins_GetUserSymbolRates(installationmode,values,len)	prins->GetUserSymbolRates(installationmode,values,len)
#define prins_GetPredefinedSymbolRates(installationmode,values,len)	prins->GetPredefinedSymbolRates(installationmode,values,len)
#define prins_GetNetworkIDList()	prins->GetNetworkIDList()
#define prins_GetNetworkIDName(index,NetworkName)	prins->GetNetworkIDName(index,NetworkName)
#define prins_SetFavouriteNetworkID(mode,attrib,index)	prins->SetFavouriteNetworkID(mode,attrib,index)
#define prins_SetFavouriteRegion(mode,index,RegionType)	prins->SetFavouriteRegion(mode,index,RegionType)
#define prins_None	IHsvInstallation2_None
#define prins_Ziggo	IHsvInstallation2_Ziggo
#define prins_UPC	IHsvInstallation2_UPC
#define prins_UnityMedia	IHsvInstallation2_UnityMedia
#define prins_Kdg	IHsvInstallation2_Kdg
#define prins_Telenet	IHsvInstallation2_Telenet
#define prins_RCSRDS	IHsvInstallation2_RCSRDS
#define prins_SetUserSelectConflictService(LcnIndex,SvcIndex)	prins->SetUserSelectConflictService(LcnIndex,SvcIndex)
#define prins_ConflictsSelectionDone(UserSelection)	prins->ConflictsSelectionDone(UserSelection)
#define prins_GetConflictServices(ConflictList,NumRecords)	prins->GetConflictServices(ConflictList,NumRecords)
#define prins_GetInstallationVersion()	prins->GetInstallationVersion()
#define prins_GetInstallationState()	prins->GetInstallationState()
#define prins_GetPLPIds(PLPIds)	prins->GetPLPIds(PLPIds)
#define prins_GetRegionList(RegionsData)	prins->GetRegionList(RegionsData)
#define prins_UserSelectionDone(UserSelection)	prins->UserSelectionDone(UserSelection)
#define prins_GetFavouriteRegion(mode,RegionType)	prins->GetFavouriteRegion(mode,RegionType)
#define prins_GetStreamPriority()	prins->GetStreamPriority()
#define prins_SetStreamPriority(prio)	prins->SetStreamPriority(prio)
#define prins_GetConstellation()	prins->GetConstellation()
#define prins_GetSymbolRate()	prins->GetSymbolRate()
#define prins_GetHierarchyMode()	prins->GetHierarchyMode()
#define prins_GetEpgBarkerMux(OnId,TsId)	prins->GetEpgBarkerMux(OnId,TsId)
#define prins_ZiggoNetworkDataSet(ActionValue)	prins->ZiggoNetworkDataSet(ActionValue)
#define prins_ClearPersistent()	prins->ClearPersistent()
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
#define tmr_iPresent() (tmr.Present())
#define tmr_Create(ntf)	tmr->Create(ntf)
#define tmr_FireOnce(timer,seconds)	tmr->FireOnce(timer,seconds)
#define tmr_FireEvery(timer,seconds)	tmr->FireEvery(timer,seconds)
#define tmr_Cancel(timer)	tmr->Cancel(timer)
#define tmr_Delete(timer)	tmr->Delete(timer)
#define tmr_State(timer,remaining,reload)	tmr->State(timer,remaining,reload)
#define txtpre_iPresent() (txtpre.Present())
#define txtpre_WstPresent()	txtpre->WstPresent()
#define txtpre_VpsPresent()	txtpre->VpsPresent()
#define vip_iPresent() (vip.Present())
#define vip_VideoPresenceInvalid	vip->VideoPresenceInvalid()
#define vip_VideoPresenceUnknown	vip->VideoPresenceUnknown()
#define vip_VideoPresenceDetected	vip->VideoPresenceDetected()
#define vip_VideoPresenceNotDetected	vip->VideoPresenceNotDetected()
#define vip_FieldFrequencyInvalid	vip->FieldFrequencyInvalid()
#define vip_FieldFrequencyUnknown	vip->FieldFrequencyUnknown()
#define vip_NumberOfLinesInvalid	vip->NumberOfLinesInvalid()
#define vip_NumberOfLinesUnknown	vip->NumberOfLinesUnknown()
#define vip_InterlaceInvalid	vip->InterlaceInvalid()
#define vip_InterlaceUnknown	vip->InterlaceUnknown()
#define vip_InterlaceOneOne	vip->InterlaceOneOne()
#define vip_InterlaceTwoOne	vip->InterlaceTwoOne()
#define vip_InterlaceFourTwo	vip->InterlaceFourTwo()
#define vip_ImageFormatInvalid	vip->ImageFormatInvalid()
#define vip_ImageFormatUnknown	vip->ImageFormatUnknown()
#define vip_ImageFormat4by3FullFormat	vip->ImageFormat4by3FullFormat()
#define vip_ImageFormat14by9Top	vip->ImageFormat14by9Top()
#define vip_ImageFormat14by9Center	vip->ImageFormat14by9Center()
#define vip_ImageFormat16by9Top	vip->ImageFormat16by9Top()
#define vip_ImageFormat16by9Center	vip->ImageFormat16by9Center()
#define vip_ImageFormat4by3Use14by9	vip->ImageFormat4by3Use14by9()
#define vip_ImageFormat16by9Use14by9	vip->ImageFormat16by9Use14by9()
#define vip_ImageFormat16by9Use4by3	vip->ImageFormat16by9Use4by3()
#define vip_ImageFormat16by9FullFormat	vip->ImageFormat16by9FullFormat()
#define vip_ImageFormatMoreThan16by9Center	vip->ImageFormatMoreThan16by9Center()
#define vip_VideoCodingInvalid	vip->VideoCodingInvalid()
#define vip_VideoCodingUnknown	vip->VideoCodingUnknown()
#define vip_VideoCodingCvbs	vip->VideoCodingCvbs()
#define vip_VideoCodingYc	vip->VideoCodingYc()
#define vip_VideoCodingYuv	vip->VideoCodingYuv()
#define vip_VideoCodingYuv2FH	vip->VideoCodingYuv2FH()
#define vip_VideoCodingYuv3FH	vip->VideoCodingYuv3FH()
#define vip_VideoCodingRgb	vip->VideoCodingRgb()
#define vip_VideoCodingRgb2FH	vip->VideoCodingRgb2FH()
#define vip_VideoCodingRgb3FH	vip->VideoCodingRgb3FH()
#define vip_VideoCodingYPbPr	vip->VideoCodingYPbPr()
#define vip_VideoCodingYPbPr2FH	vip->VideoCodingYPbPr2FH()
#define vip_VideoCodingYPbPr3FH	vip->VideoCodingYPbPr3FH()
#define vip_GetVideoPresent()	vip->GetVideoPresent()
#define vip_GetFieldFrequency()	vip->GetFieldFrequency()
#define vip_GetNumberOfFrameLines()	vip->GetNumberOfFrameLines()
#define vip_GetNumberOfVisibleLines()	vip->GetNumberOfVisibleLines()
#define vip_GetNumberOfVisiblePixels()	vip->GetNumberOfVisiblePixels()
#define vip_GetInterlace()	vip->GetInterlace()
#define vip_GetImageFormat()	vip->GetImageFormat()
#define vip_IsFilmMode()	vip->IsFilmMode()
#define vip_IsFromVcr()	vip->IsFromVcr()
#define vip_GetVideoCoding()	vip->GetVideoCoding()
#define vip_GetVideoProtection()	vip->GetVideoProtection()
#define vip_IsVideoDetectionSensitivitySupported(sensitivity)	vip->IsVideoDetectionSensitivitySupported(sensitivity)
#define vip_SetVideoDetectionSensitivity(sensitivity)	vip->SetVideoDetectionSensitivity(sensitivity)
#define vip_GetVideoDetectionSensitivity()	vip->GetVideoDetectionSensitivity()
#define pginsN_EventInstallationCompleted	IHsvInstallationNotify_EventInstallationCompleted
#define pginsN_EventInstallationStarted	IHsvInstallationNotify_EventInstallationStarted
#define pginsN_EventInstallationStopped	IHsvInstallationNotify_EventInstallationStopped
#define pginsN_EventInstallationPaused	IHsvInstallationNotify_EventInstallationPaused
#define pginsN_EventInstallationContinued	IHsvInstallationNotify_EventInstallationContinued
#define pginsN_EventChannelFound	IHsvInstallationNotify_EventChannelFound
#define pginsN_EventChannelNotFound	IHsvInstallationNotify_EventChannelNotFound
#define pginsN_EventSearchInProgress	IHsvInstallationNotify_EventSearchInProgress
#define pginsN_EventTuningStarted	IHsvInstallationNotify_EventTuningStarted
#define pginsN_EventTuningStationFound	IHsvInstallationNotify_EventTuningStationFound
#define pginsN_EventTuningStationNotFound	IHsvInstallationNotify_EventTuningStationNotFound
#define pginsN_EventManualInstallationCniExtractionStarted	IHsvInstallationNotify_EventManualInstallationCniExtractionStarted
#define pginsN_EventManualInstallationCniExtractionEnded	IHsvInstallationNotify_EventManualInstallationCniExtractionEnded
#define pginsN_EventATSSortingStarted	IHsvInstallationNotify_EventATSSortingStarted
#define pginsN_EventAciStoreStarted	IHsvInstallationNotify_EventAciStoreStarted
#define pginsN_EventTvSystemChanged	IHsvInstallationNotify_EventTvSystemChanged
#define pginsN_EventMediumChanged	IHsvInstallationNotify_EventMediumChanged
#define pginsN_EventSignalStrengthChanged	IHsvInstallationNotify_EventSignalStrengthChanged
#define pginsN_EventBackGroundCNIUpdated	IHsvInstallationNotify_EventBackGroundCNIUpdated
#define pginsN_EventPresetStored	IHsvInstallationNotify_EventPresetStored
#define pginsN_EventPhaseStarted	IHsvInstallationNotify_EventPhaseStarted
#define pginsN_EventPhaseCompleted	IHsvInstallationNotify_EventPhaseCompleted
#define pginsN_EventChannelIterationStarted	IHsvInstallationNotify_EventChannelIterationStarted
#define pginsN_EventHeirarchyModeDetected	IHsvInstallationNotify_EventHeirarchyModeDetected
#define pginsN_EventChannelAdded	IHsvInstallationNotify_EventChannelAdded
#define pginsN_EventChannelRemoved	IHsvInstallationNotify_EventChannelRemoved
#define pginsN_EventNetworkUpdateDetected	IHsvInstallationNotify_EventNetworkUpdateDetected
#define pginsN_EventDisplayNetworkNames	IHsvInstallationNotify_EventDisplayNetworkNames
#define pginsN_EventNIDInvalid	IHsvInstallationNotify_EventNIDInvalid
#define pginsN_EventNetworkUpdateNotDetected	IHsvInstallationNotify_EventNetworkUpdateNotDetected
#define pginsN_EventOnConflictsDetected	IHsvInstallationNotify_EventOnConflictsDetected
#define pginsN_EventDisplayRegionNames	IHsvInstallationNotify_EventDisplayRegionNames
#define pginsN_EventPLPsDetected	IHsvInstallationNotify_EventPLPsDetected
#define pginsN_NetworkOperator	IHsvInstallationNotify_NetworkOperator
#define pginsN_EventMultiPackageFound 	IHsvInstallationNotify_EventMultiPackageFound
#define	pginsN_EventMultiPackageToBeDisplayed 	IHsvInstallationNotify_EventMultiPackageToBeDisplayed
#define	pginsN_EventMultiPackageRemoved	 IHsvInstallationNotify_EventMultiPackageRemoved
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

