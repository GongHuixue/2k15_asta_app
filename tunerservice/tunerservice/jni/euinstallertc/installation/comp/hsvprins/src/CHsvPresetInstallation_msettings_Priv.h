#ifndef  _CHSVPRESETINSTALLATION_MSETTINGS_PRIV_H
#define  _CHSVPRESETINSTALLATION_MSETTINGS_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAnalogSettings.h>
#include <ITvColorDecode2.h>
#include <IHsvFrontEndApi.h>
#include <IHsvWindowDestinationMap.h>
#include <CTCMwBase.h>
class CHsvPresetInstallation_msettings_Priv;
#define CLASSSCOPE CHsvPresetInstallation_msettings_Priv::
#include "locals_msettings.h"

class CHsvPresetInstallation_msettings_Priv : public CTCMwBase
{
public:
virtual ~CHsvPresetInstallation_msettings_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_msettings.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvAnalogSettingsImpl(CHsvPresetInstallation_msettings_Priv,anaset);
public:
ProvidesInterface<IHsvAnalogSettings>	anaset;

//Required interfaces
public:
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IHsvFrontEndApi>	feapi;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
RequiresInterface<ITvColorDecode2>	xcol;

public:
CHsvPresetInstallation_msettings_Priv():i__anaset(this)
{
anaset	=	&i__anaset;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
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
#define xcol_iPresent() (xcol.Present())
#define xcol_ColorSystemSupported(colorsystem)	xcol->ColorSystemSupported(colorsystem)
#define xcol_ColorSystemSupportedEx(colorsystem,carrierfrequency)	xcol->ColorSystemSupportedEx(colorsystem,carrierfrequency)
#define xcol_ForceColorSystem(colorsystem)	xcol->ForceColorSystem(colorsystem)
#define xcol_ForceColorSystemEx(colorsystem,carrierfrequency)	xcol->ForceColorSystemEx(colorsystem,carrierfrequency)
#define xcol_GetForcedColorSystem()	xcol->GetForcedColorSystem()
#define xcol_GetForcedCarrierFrequency()	xcol->GetForcedCarrierFrequency()
#define xcol_SuggestColorSystem(colorsystem)	xcol->SuggestColorSystem(colorsystem)
#define xcol_SuggestColorSystemEx(colorsystem,carrierfrequency)	xcol->SuggestColorSystemEx(colorsystem,carrierfrequency)
#define xcol_GetSuggestedColorSystem()	xcol->GetSuggestedColorSystem()
#define xcol_GetSuggestedCarrierFrequency()	xcol->GetSuggestedCarrierFrequency()
#define xcol_GetColorSystem()	xcol->GetColorSystem()
#define xcol_GetCarrierFrequency()	xcol->GetCarrierFrequency()
#define xcol_CombFilterSupported()	xcol->CombFilterSupported()
#define xcol_EnableCombFilter(mode)	xcol->EnableCombFilter(mode)
#define xcol_CombFilterEnabled()	xcol->CombFilterEnabled()
#define xcol_CombFilterActive()	xcol->CombFilterActive()
#define xcol_UnknownColorSystem	xcol->UnknownColorSystem()
#define xcol_InvalidColorSystem	xcol->InvalidColorSystem()
#define xcol_Pal	xcol->Pal()
#define xcol_Secam	xcol->Secam()
#define xcol_Ntsc	xcol->Ntsc()
#define xcol_FreqUnknown	xcol->FreqUnknown()
#define xcol_FreqInvalid	xcol->FreqInvalid()
#define xcol_Freq4pt433619	xcol->Freq4pt433619()
#define xcol_Freq3pt582056	xcol->Freq3pt582056()
#define xcol_Freq3pt575611	xcol->Freq3pt575611()
#define xcol_Freq3pt579545	xcol->Freq3pt579545()
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
#include "locals_msettings.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

