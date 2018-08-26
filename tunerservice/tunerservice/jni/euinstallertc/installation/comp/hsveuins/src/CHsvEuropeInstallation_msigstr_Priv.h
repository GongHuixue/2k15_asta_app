#ifndef  _CHSVEUROPEINSTALLATION_MSIGSTR_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MSIGSTR_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvFrontEndApi.h>
#include <IHsvInstallationUtility.h>
#include <IHsvLog.h>
#include <IHsvInstallation2.h>
#include <IHsvWindowDestinationMap.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_msigstr_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_msigstr_Priv::
#include "locals_msigstr.h"

class CHsvEuropeInstallation_msigstr_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_msigstr_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_msigstr.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvInstallationSigStrengthImpl(CHsvEuropeInstallation_msigstr_Priv,sigstr);
public:
ProvidesInterface<IHsvInstallationSigStrength>	sigstr;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvInstallationUtility>	instutil;
RequiresInterface<IHsvLog>	log;
RequiresInterface<IHsvInstallation2>	rins;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;

public:
CHsvEuropeInstallation_msigstr_Priv():i__sigstr(this)
{
sigstr	=	&i__sigstr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
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
#define instutil_iPresent() (instutil.Present())
#define instutil_LogError(Priority,ErrorId)	instutil->LogError(Priority,ErrorId)
#define instutil_AsciiToUnicode(str,len)	instutil->AsciiToUnicode(str,len)
#define log_iPresent() (log.Present())
#define log_Information	IHsvLog_Information
#define log_SoftErr	IHsvLog_SoftErr
#define log_FatalErr	IHsvLog_FatalErr
#define log_Error(prio,errid)	log->Error(prio,errid)
#define log_Trace(callerid,arg1,arg2)	log->Trace(callerid,arg1,arg2)
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
#include "locals_msigstr.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

