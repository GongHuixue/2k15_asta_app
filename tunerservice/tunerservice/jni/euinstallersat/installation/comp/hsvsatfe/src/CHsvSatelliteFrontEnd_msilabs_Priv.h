#ifndef  _CHSVSATELLITEFRONTEND_MSILABS_PRIV_H
#define  _CHSVSATELLITEFRONTEND_MSILABS_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IPlfApiTuningNotify.h>
#include <IHsvPower.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteSettings.h>
#include <IPumpEngine.h>
#include <IPlfApiDvbsTuning.h>
#include <IPlfApiTuning.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <ICeIsTpHostRtk2.h>
#include <tprtkdefines.h>
#include <IHsvWindowDestinationMap.h>
#include <CS2MwBase.h>
class CHsvSatelliteFrontEnd_msilabs_Priv;
#define CLASSSCOPE CHsvSatelliteFrontEnd_msilabs_Priv::
#include "locals_msilabs.h"

class CHsvSatelliteFrontEnd_msilabs_Priv : public CS2MwBase
{
public:
virtual ~CHsvSatelliteFrontEnd_msilabs_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_msilabs.h"
#undef MEMBERVARS
//Provided interfaces
private:
IPlfApiTuningNotifyImpl(CHsvSatelliteFrontEnd_msilabs_Priv,plfapidvbsN);
IHsvPowerImpl(CHsvSatelliteFrontEnd_msilabs_Priv,sipow);
IHsvSatelliteFrontEndImpl(CHsvSatelliteFrontEnd_msilabs_Priv,sisatfrontend);
public:
ProvidesInterface<IPlfApiTuningNotify>	plfapidvbsN;

ProvidesInterface<IHsvPower>	sipow;

ProvidesInterface<IHsvSatelliteFrontEnd>	sisatfrontend;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteSettings>	hsvsatsettings;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPlfApiDvbsTuning>	plfdvbs;
RequiresInterface<IPlfApiTuning>	plftune;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteFrontEndNotify>	satfrontendNotify;
RequiresInterface<ICeIsTpHostRtk2>	tprtk;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvSatelliteFrontEnd_msilabs_Priv);
TpRtkDefines(CHsvSatelliteFrontEnd_msilabs_Priv);

public:
CHsvSatelliteFrontEnd_msilabs_Priv():i__plfapidvbsN(this),i__sipow(this),i__sisatfrontend(this)
{
plfapidvbsN	=	&i__plfapidvbsN;
sipow	=	&i__sipow;
sisatfrontend	=	&i__sisatfrontend;
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
#define err_DiseqcError	IHsvErrorCodeEx_DiseqcError
#define err_TunerError	IHsvErrorCodeEx_TunerError
#define err_UsbPathNotFound	IHsvErrorCodeEx_UsbPathNotFound
#define hsvsatsettings_iPresent() (hsvsatsettings.Present())
#define hsvsatsettings_AttributePackageId	IHsvSatelliteSettings_AttributePackageId
#define hsvsatsettings_AttributePackageOnly	IHsvSatelliteSettings_AttributePackageOnly
#define hsvsatsettings_AttributeAssetManager	IHsvSatelliteSettings_AttributeAssetManager
#define hsvsatsettings_LoadLnbParametersFromPersistent()	hsvsatsettings->LoadLnbParametersFromPersistent()
#define hsvsatsettings_GetLnbSettings(LnbSettings)	hsvsatsettings->GetLnbSettings(LnbSettings)
#define hsvsatsettings_SetLnbSettings(LnbSettings)	hsvsatsettings->SetLnbSettings(LnbSettings)
#define hsvsatsettings_ResetLnbSettings()	hsvsatsettings->ResetLnbSettings()
#define hsvsatsettings_GetDefaultValues(LnbSettingsEntry)	hsvsatsettings->GetDefaultValues(LnbSettingsEntry)
#define hsvsatsettings_ResetToDefaultLnbSettings()	hsvsatsettings->ResetToDefaultLnbSettings()
#define hsvsatsettings_GetAttribute(AttributeId)	hsvsatsettings->GetAttribute(AttributeId)
#define hsvsatsettings_SetAttribute(AttributeId,Value)	hsvsatsettings->SetAttribute(AttributeId,Value)
#define hsvsatsettings_SaveSatelliteSettingsToPersistent()	hsvsatsettings->SaveSatelliteSettingsToPersistent()
#define hsvsatsettings_CommitSatelliteSettingsToPersistent()	hsvsatsettings->CommitSatelliteSettingsToPersistent()
#define hsvsatsettings_ReLoadLnbParametersFromPersistent()	hsvsatsettings->ReLoadLnbParametersFromPersistent()
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define plfdvbs_iPresent() (plfdvbs.Present())
#define plfdvbs_TUNING_DVBS_ERR_NONE	IPlfApiDvbsTuning_TUNING_DVBS_ERR_NONE
#define plfdvbs_TUNING_DVBS_ERR_BAD_PARAMETER	IPlfApiDvbsTuning_TUNING_DVBS_ERR_BAD_PARAMETER
#define plfdvbs_TUNING_DVBS_ERR_NOT_IMPLEMENTED	IPlfApiDvbsTuning_TUNING_DVBS_ERR_NOT_IMPLEMENTED
#define plfdvbs_TUNING_DVBS_ERR_EXEC_FAILURE	IPlfApiDvbsTuning_TUNING_DVBS_ERR_EXEC_FAILURE
#define plfdvbs_TUNING_DVBS_START_FREQUENCY	IPlfApiDvbsTuning_TUNING_DVBS_START_FREQUENCY
#define plfdvbs_TUNING_DVBS_END_FREQUENCY	IPlfApiDvbsTuning_TUNING_DVBS_END_FREQUENCY
#define plfdvbs_TUNING_DVBS_UNKNOWN	IPlfApiDvbsTuning_TUNING_DVBS_UNKNOWN
#define plfdvbs_TUNING_DVBS_QPSK	IPlfApiDvbsTuning_TUNING_DVBS_QPSK
#define plfdvbs_TUNING_DVBS_APSK16	IPlfApiDvbsTuning_TUNING_DVBS_APSK16
#define plfdvbs_TUNING_DVBS_APSK32	IPlfApiDvbsTuning_TUNING_DVBS_APSK32
#define plfdvbs_TUNING_DVBs_PSK8	IPlfApiDvbsTuning_TUNING_DVBs_PSK8
#define plfdvbs_TUNING_DVBS_SYMBOLRATE_MIN	IPlfApiDvbsTuning_TUNING_DVBS_SYMBOLRATE_MIN
#define plfdvbs_TUNING_DVBS_SYMBOLRATE_MAX	IPlfApiDvbsTuning_TUNING_DVBS_SYMBOLRATE_MAX
#define plfdvbs_TUNING_DVBS_SR_DETECTMODE_AUTO	IPlfApiDvbsTuning_TUNING_DVBS_SR_DETECTMODE_AUTO
#define plfdvbs_TUNING_DVBS_SR_DETECTMODE_MANUAL	IPlfApiDvbsTuning_TUNING_DVBS_SR_DETECTMODE_MANUAL
#define plfdvbs_TUNING_DVBS_HORIZONTAL	IPlfApiDvbsTuning_TUNING_DVBS_HORIZONTAL
#define plfdvbs_TUNING_DVBS_VERTICAL	IPlfApiDvbsTuning_TUNING_DVBS_VERTICAL
#define plfdvbs_TUNING_DVBS_UNIVERSAL	IPlfApiDvbsTuning_TUNING_DVBS_UNIVERSAL
#define plfdvbs_TUNING_DVBS_CUSTOM	IPlfApiDvbsTuning_TUNING_DVBS_CUSTOM
#define plfdvbs_TUNING_DVBS_CIRCULAR	IPlfApiDvbsTuning_TUNING_DVBS_CIRCULAR
#define plfdvbs_TUNING_DVBS_MDU1	IPlfApiDvbsTuning_TUNING_DVBS_MDU1
#define plfdvbs_TUNING_DVBS_MDU2	IPlfApiDvbsTuning_TUNING_DVBS_MDU2
#define plfdvbs_TUNING_DVBS_MDU3	IPlfApiDvbsTuning_TUNING_DVBS_MDU3
#define plfdvbs_TUNING_DVBS_MDU4	IPlfApiDvbsTuning_TUNING_DVBS_MDU4
#define plfdvbs_TUNING_DVBS_MDU5	IPlfApiDvbsTuning_TUNING_DVBS_MDU5
#define plfdvbs_TUNING_DVBS_UNICABLE	IPlfApiDvbsTuning_TUNING_DVBS_UNICABLE
#define plfdvbs_TUNING_DVBS_BANDLOW	IPlfApiDvbsTuning_TUNING_DVBS_BANDLOW
#define plfdvbs_TUNING_DVBS_BANDHIGH	IPlfApiDvbsTuning_TUNING_DVBS_BANDHIGH

#define plfdvbs_TUNING_DVBSEX_CUSTOMPOW_OFF	IPlfApiDvbsTuning_TUNING_DVBSEX_CUSTOMPOW_OFF
#define plfdvbs_TUNING_DVBSEX_CUSTOMPOW_ON	IPlfApiDvbsTuning_TUNING_DVBSEX_CUSTOMPOW_ON
	
#define plfdvbs_TUNING_DVBSEX_TONELOW	IPlfApiDvbsTuning_TUNING_DVBSEX_TONELOW
#define plfdvbs_TUNING_DVBSEX_TONEHIGH	IPlfApiDvbsTuning_TUNING_DVBSEX_TONEHIGH
#define plfdvbs_TUNING_DVBSEX_TONENONE	IPlfApiDvbsTuning_TUNING_DVBSEX_TONENONE
	/*BurstSelect For Diseqc Mini and Custom LNB */
#define plfdvbs_DVBSEX_TONEBURST_SAT_A	IPlfApiDvbsTuning_DVBSEX_TONEBURST_SAT_A
#define plfdvbs_DVBSEX_TONEBURST_SAT_B	IPlfApiDvbsTuning_DVBSEX_TONEBURST_SAT_B
#define plfdvbs_getParams(par)	plfdvbs->getParams(par)
#define plfdvbs_configureLNB(lnbcfg,customlnbcfg)	plfdvbs->configureLNB(lnbcfg,customlnbcfg)
#define plfdvbs_configureUnicable(uccfg)	plfdvbs->configureUnicable(uccfg)
#define plfdvbs_setPolarization(polarization)	plfdvbs->setPolarization(polarization)
#define plfdvbs_setSymbolRate(srdetectmode,symbolrate)	plfdvbs->setSymbolRate(srdetectmode,symbolrate)
#define plfdvbs_setPLP(plpid)	plfdvbs->setPLP(plpid)
#define plfdvbs_setBand(band)	plfdvbs->setBand(band)
#define plfdvbs_setLNBConnectionType(connectiontype)	plfdvbs->setLNBConnectionType(connectiontype)
#define plfdvbs_setSatIPParams(modsys,modtype,RollOff,fec,pilots)	plfdvbs->setSatIPParams(modsys,modtype,RollOff,fec,pilots)
#define plftune_iPresent() (plftune.Present())
#define plftune_TUNING_ERR_NONE	IPlfApiTuning_TUNING_ERR_NONE
#define plftune_TUNING_ERR_BAD_PARAMETER	IPlfApiTuning_TUNING_ERR_BAD_PARAMETER
#define plftune_TUNING_ERR_NOT_IMPLEMENTED	IPlfApiTuning_TUNING_ERR_NOT_IMPLEMENTED
#define plftune_TUNING_ERR_EXEC_FAILURE	IPlfApiTuning_TUNING_ERR_EXEC_FAILURE
#define plftune_TUNING_STANDARD_DVBT	IPlfApiTuning_TUNING_STANDARD_DVBT
#define plftune_TUNING_STANDARD_DVBT2	IPlfApiTuning_TUNING_STANDARD_DVBT2
#define plftune_TUNING_STANDARD_DVBC	IPlfApiTuning_TUNING_STANDARD_DVBC
#define plftune_TUNING_STANDARD_DVBC2	IPlfApiTuning_TUNING_STANDARD_DVBC2
#define plftune_TUNING_STANDARD_DVBS2	IPlfApiTuning_TUNING_STANDARD_DVBS2
#define plftune_TUNING_STANDARD_ANALOG	IPlfApiTuning_TUNING_STANDARD_ANALOG
#define plftune_TUNING_RESULT_LOCK	IPlfApiTuning_TUNING_RESULT_LOCK
#define plftune_TUNING_RESULT_NOLOCK	IPlfApiTuning_TUNING_RESULT_NOLOCK
#define plftune_tune(freq,finetune)	plftune->tune(freq,finetune)
#define plftune_getFreq(freq)	plftune->getFreq(freq)
#define plftune_scanStart(startfreq,endfreq,scanforward)	plftune->scanStart(startfreq,endfreq,scanforward)
#define plftune_scanAbort()	plftune->scanAbort()
#define plftune_scanNext()	plftune->scanNext()
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvSatelliteFrontEnd_msilabs_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define satfrontendNotify_iPresent() (satfrontendNotify.Present())
#define satfrontendNotify_OnLockChanged(LockState)	satfrontendNotify->OnLockChanged(LockState)
#define satfrontendNotify_OnBlindScanEnd()	satfrontendNotify->OnBlindScanEnd()
#define tprtk_iPresent() (tprtk.Present())
#define tprtk_TaskPrioHighest	tprtk->TaskPrioHighest()
#define tprtk_TaskPrioHigh	tprtk->TaskPrioHigh()
#define tprtk_TaskPrioAboveNormal	tprtk->TaskPrioAboveNormal()
#define tprtk_TaskPrioNormal	tprtk->TaskPrioNormal()
#define tprtk_TaskPrioBelowNormal	tprtk->TaskPrioBelowNormal()
#define tprtk_TaskPrioLow	tprtk->TaskPrioLow()
#define tprtk_TaskPrioLowest	tprtk->TaskPrioLowest()
#define tprtk_SemSignaled	tprtk->SemSignaled()
#define tprtk_SemUnsignaled	tprtk->SemUnsignaled()
#define tprtk_TimeoutInfinite	tprtk->TimeoutInfinite()
#define tprtk_TimeoutZero	tprtk->TimeoutZero()
#define tprtk_TaskCreate(name,priority,stacksize,entry,param)	tprtk->TaskCreate(name,priority,stacksize,entry,param)
#define tprtk_TaskDelete(task)	tprtk->TaskDelete(task)
#define tprtk_TaskExists(task)	tprtk->TaskExists(task)
#define tprtk_TaskJoin(task)	tprtk->TaskJoin(task)
#define tprtk_TaskGetCurrent()	tprtk->TaskGetCurrent()
#define tprtk_TaskSetPriority(task,prio)	tprtk->TaskSetPriority(task,prio)
#define tprtk_TaskGetPriority(task)	tprtk->TaskGetPriority(task)
#define tprtk_TaskSleep(timeout)	tprtk->TaskSleep(timeout)
#define tprtk_SemCreateBinary(initval)	tprtk->SemCreateBinary(initval)
#define tprtk_SemCreateCounting(initcount)	tprtk->SemCreateCounting(initcount)
#define tprtk_SemDelete(sema)	tprtk->SemDelete(sema)
#define tprtk_SemWait(sema)	tprtk->SemWait(sema)
#define tprtk_SemTimedWait(sema,timeout)	tprtk->SemTimedWait(sema,timeout)
#define tprtk_SemTryWait(sema)	tprtk->SemTryWait(sema)
#define tprtk_SemSignal(sema)	tprtk->SemSignal(sema)
#define tprtk_MutexCreate()	tprtk->MutexCreate()
#define tprtk_MutexDelete(mutex)	tprtk->MutexDelete(mutex)
#define tprtk_MutexLock(mutex)	tprtk->MutexLock(mutex)
#define tprtk_MutexUnlock(mutex)	tprtk->MutexUnlock(mutex)
#define tprtk_EventSend(task,event)	tprtk->EventSend(task,event)
#define tprtk_EventReceive(eventmask,waitall,timeout)	tprtk->EventReceive(eventmask,waitall,timeout)
#define tprtk_EventClear(eventmask)	tprtk->EventClear(eventmask)
#define tprtk_MsgQCreate(maxmsg,maxmsglength)	tprtk->MsgQCreate(maxmsg,maxmsglength)
#define tprtk_MsgQDelete(msgq)	tprtk->MsgQDelete(msgq)
#define tprtk_MsgQGetMessageCount(msgq)	tprtk->MsgQGetMessageCount(msgq)
#define tprtk_MsgQSend(msgq,buffer,length,timeout)	tprtk->MsgQSend(msgq,buffer,length,timeout)
#define tprtk_MsgQReceive(msgq,buffer,maxlength,timeout)	tprtk->MsgQReceive(msgq,buffer,maxlength,timeout)
#define tprtk_TimeGetCurrent()	tprtk->TimeGetCurrent()
#define tprtk_TimeAdd(a,b)	tprtk->TimeAdd(a,b)
#define tprtk_TimeSubtract(a,b)	tprtk->TimeSubtract(a,b)
#ifdef tprtk_TaskCreate
#undef tprtk_TaskCreate
#endif
#define tprtk_TaskCreate(n,pr,s,e,p) tprtk->TaskCreate(n,pr,s,reinterpret_cast<FunctionInt>(static_cast<IRunnable*>(new RtkThreadRunnable<CHsvSatelliteFrontEnd_msilabs_Priv>(&CHsvSatelliteFrontEnd_msilabs_Priv::e, this)) ),0)
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
#define sisatfrontend_PolarisationHorizontal	IHsvSatelliteFrontEnd_PolarisationHorizontal
#define sisatfrontend_PolarisationVertical	IHsvSatelliteFrontEnd_PolarisationVertical
#define sisatfrontend_BlindScanModeNormal	IHsvSatelliteFrontEnd_BlindScanModeNormal
#define sisatfrontend_BlindScanModeMinimal	IHsvSatelliteFrontEnd_BlindScanModeMinimal
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
#include "locals_msilabs.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

