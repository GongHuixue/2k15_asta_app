#ifndef  _CHSVZIGGOINSTALLATION_MROUTE_PRIV_H
#define  _CHSVZIGGOINSTALLATION_MROUTE_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvFrontEndApiNotify.h>
#include <IHsvDigitalScan.h>
#include <IHsvPower.h>
#include <IHsvInstallation2.h>
#include <CTCMwBase.h>
class CHsvZiggoInstallation_mRoute_Priv;
#define CLASSSCOPE CHsvZiggoInstallation_mRoute_Priv::
#include "locals_mRoute.h"

class CHsvZiggoInstallation_mRoute_Priv : public CTCMwBase
{
public:
virtual ~CHsvZiggoInstallation_mRoute_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mRoute.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSdmControlNotifyExImpl(CHsvZiggoInstallation_mRoute_Priv,ctrlN);
IHsvFrontEndApiNotifyImpl(CHsvZiggoInstallation_mRoute_Priv,feapiN);
IHsvDigitalScanImpl(CHsvZiggoInstallation_mRoute_Priv,ins);
IHsvDigitalScanImpl(CHsvZiggoInstallation_mRoute_Priv,istub);
IHsvPowerImpl(CHsvZiggoInstallation_mRoute_Priv,pow);
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

ProvidesInterface<IHsvFrontEndApiNotify>	feapiN;

ProvidesInterface<IHsvDigitalScan>	ins;

ProvidesInterface<IHsvDigitalScan>	istub;

ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvDigitalScan>	ibckg;
RequiresInterface<IHsvSdmControlNotifyEx>	ibckgctrlN;
RequiresInterface<IHsvPower>	ibckgpow;
RequiresInterface<IHsvDigitalScan>	idtr;
RequiresInterface<IHsvFrontEndApiNotify>	idtrfeapiN;
RequiresInterface<IHsvPower>	idtrpow;
RequiresInterface<IHsvDigitalScan>	iins;
RequiresInterface<IHsvSdmControlNotifyEx>	iinsctrlN;
RequiresInterface<IHsvFrontEndApiNotify>	iinsfeapiN;
RequiresInterface<IHsvPower>	iinspow;
RequiresInterface<IHsvDigitalScan>	ipreins;
RequiresInterface<IHsvSdmControlNotifyEx>	ipreinsctrlN;
RequiresInterface<IHsvFrontEndApiNotify>	ipreinsfeapiN;
RequiresInterface<IHsvPower>	ipreinspow;
RequiresInterface<IHsvInstallation2>	rins;

public:
CHsvZiggoInstallation_mRoute_Priv():i__ctrlN(this),i__feapiN(this),i__ins(this),i__istub(this),i__pow(this)
{
ctrlN	=	&i__ctrlN;
feapiN	=	&i__feapiN;
ins	=	&i__ins;
istub	=	&i__istub;
pow	=	&i__pow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define ibckg_iPresent() (ibckg.Present())
#define ibckg_stidle	IHsvDigitalScan_stidle
#define ibckg_stfewait	IHsvDigitalScan_stfewait
#define ibckg_stdmxwait	IHsvDigitalScan_stdmxwait
#define ibckg_stdecision	IHsvDigitalScan_stdecision
#define ibckg_Initialise()	ibckg->Initialise()
#define ibckg_StartInstallation(source,ptc,mode)	ibckg->StartInstallation(source,ptc,mode)
#define ibckg_StopInstallation()	ibckg->StopInstallation()
#define ibckg_StartDigitalScan()	ibckg->StartDigitalScan()
#define ibckg_StartDigitalTuning(frequency)	ibckg->StartDigitalTuning(frequency)
#define ibckg_StopDigitalScan()	ibckg->StopDigitalScan()
#define ibckg_GetNoOfPass()	ibckg->GetNoOfPass()
#define ibckg_GetCurrentPass()	ibckg->GetCurrentPass()
#define ibckg_GetPTCInfo(ptc)	ibckg->GetPTCInfo(ptc)
#define ibckg_StoreWeakSignalInstallationChannel()	ibckg->StoreWeakSignalInstallationChannel()
#define ibckg_GetNumberOfDigitalChannelsFound()	ibckg->GetNumberOfDigitalChannelsFound()
#define ibckg_GetNumberOfDigitalChannelsRemoved()	ibckg->GetNumberOfDigitalChannelsRemoved()
#define ibckg_GetTargetNitType(NetworkId)	ibckg->GetTargetNitType(NetworkId)
#define ibckg_GetCurrentState()	ibckg->GetCurrentState()
#define ibckg_GetSDTType()	ibckg->GetSDTType()
#define ibckg_GetAltTSValues(ONID,TSID)	ibckg->GetAltTSValues(ONID,TSID)
#define ibckg_GetCurTSValues(ONID,TSID)	ibckg->GetCurTSValues(ONID,TSID)
#define ibckg_GetStreamPriority()	ibckg->GetStreamPriority()
#define ibckg_SetStreamPriority(prio)	ibckg->SetStreamPriority(prio)
#define ibckg_SyncComplete()	ibckg->SyncComplete()
#define ibckg_ClearCache()	ibckg->ClearCache()
#define ibckg_GetPLPIds(PLPIds)	ibckg->GetPLPIds(PLPIds)
#define ibckg_GetHierarchyMode()	ibckg->GetHierarchyMode()
#define ibckg_ZiggoGetPTCInfo(ptc,Onid,Tsid)	ibckg->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define ibckg_ZiggoGetSDTType(Frequency)	ibckg->ZiggoGetSDTType(Frequency)
#define ibckg_GetEpgBarkerMux(ONID,TSID)	ibckg->GetEpgBarkerMux(ONID,TSID)
#define ibckg_ZiggoNetworkDataSet(ActionValue)	ibckg->ZiggoNetworkDataSet(ActionValue)
#define ibckg_ClearPersistent()	ibckg->ClearPersistent()
#define ibckgctrlN_iPresent() (ibckgctrlN.Present())
#define ibckgctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ibckgctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ibckgctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ibckgctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ibckgctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ibckgctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ibckgctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ibckgctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ibckgctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ibckgctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ibckgctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ibckgctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ibckgctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ibckgctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ibckgctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ibckgctrlN_OnEvent(dmx,eventid,value)	ibckgctrlN->OnEvent(dmx,eventid,value)
#define ibckgpow_iPresent() (ibckgpow.Present())
#define ibckgpow_Init()	ibckgpow->Init()
#define ibckgpow_TurnOn()	ibckgpow->TurnOn()
#define ibckgpow_TurnOff()	ibckgpow->TurnOff()
#define idtr_iPresent() (idtr.Present())
#define idtr_stidle	IHsvDigitalScan_stidle
#define idtr_stfewait	IHsvDigitalScan_stfewait
#define idtr_stdmxwait	IHsvDigitalScan_stdmxwait
#define idtr_stdecision	IHsvDigitalScan_stdecision
#define idtr_Initialise()	idtr->Initialise()
#define idtr_StartInstallation(source,ptc,mode)	idtr->StartInstallation(source,ptc,mode)
#define idtr_StopInstallation()	idtr->StopInstallation()
#define idtr_StartDigitalScan()	idtr->StartDigitalScan()
#define idtr_StartDigitalTuning(frequency)	idtr->StartDigitalTuning(frequency)
#define idtr_StopDigitalScan()	idtr->StopDigitalScan()
#define idtr_GetNoOfPass()	idtr->GetNoOfPass()
#define idtr_GetCurrentPass()	idtr->GetCurrentPass()
#define idtr_GetPTCInfo(ptc)	idtr->GetPTCInfo(ptc)
#define idtr_StoreWeakSignalInstallationChannel()	idtr->StoreWeakSignalInstallationChannel()
#define idtr_GetNumberOfDigitalChannelsFound()	idtr->GetNumberOfDigitalChannelsFound()
#define idtr_GetNumberOfDigitalChannelsRemoved()	idtr->GetNumberOfDigitalChannelsRemoved()
#define idtr_GetTargetNitType(NetworkId)	idtr->GetTargetNitType(NetworkId)
#define idtr_GetCurrentState()	idtr->GetCurrentState()
#define idtr_GetSDTType()	idtr->GetSDTType()
#define idtr_GetAltTSValues(ONID,TSID)	idtr->GetAltTSValues(ONID,TSID)
#define idtr_GetCurTSValues(ONID,TSID)	idtr->GetCurTSValues(ONID,TSID)
#define idtr_GetStreamPriority()	idtr->GetStreamPriority()
#define idtr_SetStreamPriority(prio)	idtr->SetStreamPriority(prio)
#define idtr_SyncComplete()	idtr->SyncComplete()
#define idtr_ClearCache()	idtr->ClearCache()
#define idtr_GetPLPIds(PLPIds)	idtr->GetPLPIds(PLPIds)
#define idtr_GetHierarchyMode()	idtr->GetHierarchyMode()
#define idtr_ZiggoGetPTCInfo(ptc,Onid,Tsid)	idtr->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define idtr_ZiggoGetSDTType(Frequency)	idtr->ZiggoGetSDTType(Frequency)
#define idtr_GetEpgBarkerMux(ONID,TSID)	idtr->GetEpgBarkerMux(ONID,TSID)
#define idtr_ZiggoNetworkDataSet(ActionValue)	idtr->ZiggoNetworkDataSet(ActionValue)
#define idtr_ClearPersistent()	idtr->ClearPersistent()
#define idtrfeapiN_iPresent() (idtrfeapiN.Present())
#define idtrfeapiN_OnSearchStateChanged(state)	idtrfeapiN->OnSearchStateChanged(state)
#define idtrfeapiN_OnSearchInProgress(state)	idtrfeapiN->OnSearchInProgress(state)
#define idtrfeapiN_OnStationFound()	idtrfeapiN->OnStationFound()
#define idtrfeapiN_OnStationNotFound()	idtrfeapiN->OnStationNotFound()
#define idtrfeapiN_OnTvSystemDetected(tvSystem)	idtrfeapiN->OnTvSystemDetected(tvSystem)
#define idtrfeapiN_OnAfcFreqChanged(freq)	idtrfeapiN->OnAfcFreqChanged(freq)
#define idtrfeapiN_OnAfcLimitReached(freq)	idtrfeapiN->OnAfcLimitReached(freq)
#define idtrfeapiN_OnAfcModeChanged()	idtrfeapiN->OnAfcModeChanged()
#define idtrfeapiN_OnMeasReady(ssm,strength)	idtrfeapiN->OnMeasReady(ssm,strength)
#define idtrfeapiN_OnMeasAborted(ssm)	idtrfeapiN->OnMeasAborted(ssm)
#define idtrfeapiN_OnConstellationDetected(constellation)	idtrfeapiN->OnConstellationDetected(constellation)
#define idtrfeapiN_OnIqModeDetected(mode)	idtrfeapiN->OnIqModeDetected(mode)
#define idtrfeapiN_OnCodeRateDetected(highPrioRate,lowPrioRate)	idtrfeapiN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define idtrfeapiN_OnHierarchyModeDetected(mode)	idtrfeapiN->OnHierarchyModeDetected(mode)
#define idtrfeapiN_OnGuardIntervalDetected(interval)	idtrfeapiN->OnGuardIntervalDetected(interval)
#define idtrfeapiN_OnTxModeDetected(mode)	idtrfeapiN->OnTxModeDetected(mode)
#define idtrfeapiN_OnChanBandwidthDetected(bandwith)	idtrfeapiN->OnChanBandwidthDetected(bandwith)
#define idtrfeapiN_OnCarrierPresentChanged(carrier)	idtrfeapiN->OnCarrierPresentChanged(carrier)
#define idtrfeapiN_OnBerThresholdCrossed(ber,berThreshold)	idtrfeapiN->OnBerThresholdCrossed(ber,berThreshold)
#define idtrpow_iPresent() (idtrpow.Present())
#define idtrpow_Init()	idtrpow->Init()
#define idtrpow_TurnOn()	idtrpow->TurnOn()
#define idtrpow_TurnOff()	idtrpow->TurnOff()
#define iins_iPresent() (iins.Present())
#define iins_stidle	IHsvDigitalScan_stidle
#define iins_stfewait	IHsvDigitalScan_stfewait
#define iins_stdmxwait	IHsvDigitalScan_stdmxwait
#define iins_stdecision	IHsvDigitalScan_stdecision
#define iins_Initialise()	iins->Initialise()
#define iins_StartInstallation(source,ptc,mode)	iins->StartInstallation(source,ptc,mode)
#define iins_StopInstallation()	iins->StopInstallation()
#define iins_StartDigitalScan()	iins->StartDigitalScan()
#define iins_StartDigitalTuning(frequency)	iins->StartDigitalTuning(frequency)
#define iins_StopDigitalScan()	iins->StopDigitalScan()
#define iins_GetNoOfPass()	iins->GetNoOfPass()
#define iins_GetCurrentPass()	iins->GetCurrentPass()
#define iins_GetPTCInfo(ptc)	iins->GetPTCInfo(ptc)
#define iins_StoreWeakSignalInstallationChannel()	iins->StoreWeakSignalInstallationChannel()
#define iins_GetNumberOfDigitalChannelsFound()	iins->GetNumberOfDigitalChannelsFound()
#define iins_GetNumberOfDigitalChannelsRemoved()	iins->GetNumberOfDigitalChannelsRemoved()
#define iins_GetTargetNitType(NetworkId)	iins->GetTargetNitType(NetworkId)
#define iins_GetCurrentState()	iins->GetCurrentState()
#define iins_GetSDTType()	iins->GetSDTType()
#define iins_GetAltTSValues(ONID,TSID)	iins->GetAltTSValues(ONID,TSID)
#define iins_GetCurTSValues(ONID,TSID)	iins->GetCurTSValues(ONID,TSID)
#define iins_GetStreamPriority()	iins->GetStreamPriority()
#define iins_SetStreamPriority(prio)	iins->SetStreamPriority(prio)
#define iins_SyncComplete()	iins->SyncComplete()
#define iins_ClearCache()	iins->ClearCache()
#define iins_GetPLPIds(PLPIds)	iins->GetPLPIds(PLPIds)
#define iins_GetHierarchyMode()	iins->GetHierarchyMode()
#define iins_ZiggoGetPTCInfo(ptc,Onid,Tsid)	iins->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define iins_ZiggoGetSDTType(Frequency)	iins->ZiggoGetSDTType(Frequency)
#define iins_GetEpgBarkerMux(ONID,TSID)	iins->GetEpgBarkerMux(ONID,TSID)
#define iins_ZiggoNetworkDataSet(ActionValue)	iins->ZiggoNetworkDataSet(ActionValue)
#define iins_ClearPersistent()	iins->ClearPersistent()
#define iinsctrlN_iPresent() (iinsctrlN.Present())
#define iinsctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define iinsctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define iinsctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define iinsctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define iinsctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define iinsctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define iinsctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define iinsctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define iinsctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define iinsctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define iinsctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define iinsctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define iinsctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define iinsctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define iinsctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define iinsctrlN_OnEvent(dmx,eventid,value)	iinsctrlN->OnEvent(dmx,eventid,value)
#define iinsfeapiN_iPresent() (iinsfeapiN.Present())
#define iinsfeapiN_OnSearchStateChanged(state)	iinsfeapiN->OnSearchStateChanged(state)
#define iinsfeapiN_OnSearchInProgress(state)	iinsfeapiN->OnSearchInProgress(state)
#define iinsfeapiN_OnStationFound()	iinsfeapiN->OnStationFound()
#define iinsfeapiN_OnStationNotFound()	iinsfeapiN->OnStationNotFound()
#define iinsfeapiN_OnTvSystemDetected(tvSystem)	iinsfeapiN->OnTvSystemDetected(tvSystem)
#define iinsfeapiN_OnAfcFreqChanged(freq)	iinsfeapiN->OnAfcFreqChanged(freq)
#define iinsfeapiN_OnAfcLimitReached(freq)	iinsfeapiN->OnAfcLimitReached(freq)
#define iinsfeapiN_OnAfcModeChanged()	iinsfeapiN->OnAfcModeChanged()
#define iinsfeapiN_OnMeasReady(ssm,strength)	iinsfeapiN->OnMeasReady(ssm,strength)
#define iinsfeapiN_OnMeasAborted(ssm)	iinsfeapiN->OnMeasAborted(ssm)
#define iinsfeapiN_OnConstellationDetected(constellation)	iinsfeapiN->OnConstellationDetected(constellation)
#define iinsfeapiN_OnIqModeDetected(mode)	iinsfeapiN->OnIqModeDetected(mode)
#define iinsfeapiN_OnCodeRateDetected(highPrioRate,lowPrioRate)	iinsfeapiN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define iinsfeapiN_OnHierarchyModeDetected(mode)	iinsfeapiN->OnHierarchyModeDetected(mode)
#define iinsfeapiN_OnGuardIntervalDetected(interval)	iinsfeapiN->OnGuardIntervalDetected(interval)
#define iinsfeapiN_OnTxModeDetected(mode)	iinsfeapiN->OnTxModeDetected(mode)
#define iinsfeapiN_OnChanBandwidthDetected(bandwith)	iinsfeapiN->OnChanBandwidthDetected(bandwith)
#define iinsfeapiN_OnCarrierPresentChanged(carrier)	iinsfeapiN->OnCarrierPresentChanged(carrier)
#define iinsfeapiN_OnBerThresholdCrossed(ber,berThreshold)	iinsfeapiN->OnBerThresholdCrossed(ber,berThreshold)
#define iinspow_iPresent() (iinspow.Present())
#define iinspow_Init()	iinspow->Init()
#define iinspow_TurnOn()	iinspow->TurnOn()
#define iinspow_TurnOff()	iinspow->TurnOff()
#define ipreins_iPresent() (ipreins.Present())
#define ipreins_stidle	IHsvDigitalScan_stidle
#define ipreins_stfewait	IHsvDigitalScan_stfewait
#define ipreins_stdmxwait	IHsvDigitalScan_stdmxwait
#define ipreins_stdecision	IHsvDigitalScan_stdecision
#define ipreins_Initialise()	ipreins->Initialise()
#define ipreins_StartInstallation(source,ptc,mode)	ipreins->StartInstallation(source,ptc,mode)
#define ipreins_StopInstallation()	ipreins->StopInstallation()
#define ipreins_StartDigitalScan()	ipreins->StartDigitalScan()
#define ipreins_StartDigitalTuning(frequency)	ipreins->StartDigitalTuning(frequency)
#define ipreins_StopDigitalScan()	ipreins->StopDigitalScan()
#define ipreins_GetNoOfPass()	ipreins->GetNoOfPass()
#define ipreins_GetCurrentPass()	ipreins->GetCurrentPass()
#define ipreins_GetPTCInfo(ptc)	ipreins->GetPTCInfo(ptc)
#define ipreins_StoreWeakSignalInstallationChannel()	ipreins->StoreWeakSignalInstallationChannel()
#define ipreins_GetNumberOfDigitalChannelsFound()	ipreins->GetNumberOfDigitalChannelsFound()
#define ipreins_GetNumberOfDigitalChannelsRemoved()	ipreins->GetNumberOfDigitalChannelsRemoved()
#define ipreins_GetTargetNitType(NetworkId)	ipreins->GetTargetNitType(NetworkId)
#define ipreins_GetCurrentState()	ipreins->GetCurrentState()
#define ipreins_GetSDTType()	ipreins->GetSDTType()
#define ipreins_GetAltTSValues(ONID,TSID)	ipreins->GetAltTSValues(ONID,TSID)
#define ipreins_GetCurTSValues(ONID,TSID)	ipreins->GetCurTSValues(ONID,TSID)
#define ipreins_GetStreamPriority()	ipreins->GetStreamPriority()
#define ipreins_SetStreamPriority(prio)	ipreins->SetStreamPriority(prio)
#define ipreins_SyncComplete()	ipreins->SyncComplete()
#define ipreins_ClearCache()	ipreins->ClearCache()
#define ipreins_GetPLPIds(PLPIds)	ipreins->GetPLPIds(PLPIds)
#define ipreins_GetHierarchyMode()	ipreins->GetHierarchyMode()
#define ipreins_ZiggoGetPTCInfo(ptc,Onid,Tsid)	ipreins->ZiggoGetPTCInfo(ptc,Onid,Tsid)
#define ipreins_ZiggoGetSDTType(Frequency)	ipreins->ZiggoGetSDTType(Frequency)
#define ipreins_GetEpgBarkerMux(ONID,TSID)	ipreins->GetEpgBarkerMux(ONID,TSID)
#define ipreins_ZiggoNetworkDataSet(ActionValue)	ipreins->ZiggoNetworkDataSet(ActionValue)
#define ipreins_ClearPersistent()	ipreins->ClearPersistent()
#define ipreinsctrlN_iPresent() (ipreinsctrlN.Present())
#define ipreinsctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define ipreinsctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define ipreinsctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define ipreinsctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define ipreinsctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define ipreinsctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define ipreinsctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define ipreinsctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define ipreinsctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define ipreinsctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define ipreinsctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define ipreinsctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define ipreinsctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define ipreinsctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define ipreinsctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define ipreinsctrlN_OnEvent(dmx,eventid,value)	ipreinsctrlN->OnEvent(dmx,eventid,value)
#define ipreinsfeapiN_iPresent() (ipreinsfeapiN.Present())
#define ipreinsfeapiN_OnSearchStateChanged(state)	ipreinsfeapiN->OnSearchStateChanged(state)
#define ipreinsfeapiN_OnSearchInProgress(state)	ipreinsfeapiN->OnSearchInProgress(state)
#define ipreinsfeapiN_OnStationFound()	ipreinsfeapiN->OnStationFound()
#define ipreinsfeapiN_OnStationNotFound()	ipreinsfeapiN->OnStationNotFound()
#define ipreinsfeapiN_OnTvSystemDetected(tvSystem)	ipreinsfeapiN->OnTvSystemDetected(tvSystem)
#define ipreinsfeapiN_OnAfcFreqChanged(freq)	ipreinsfeapiN->OnAfcFreqChanged(freq)
#define ipreinsfeapiN_OnAfcLimitReached(freq)	ipreinsfeapiN->OnAfcLimitReached(freq)
#define ipreinsfeapiN_OnAfcModeChanged()	ipreinsfeapiN->OnAfcModeChanged()
#define ipreinsfeapiN_OnMeasReady(ssm,strength)	ipreinsfeapiN->OnMeasReady(ssm,strength)
#define ipreinsfeapiN_OnMeasAborted(ssm)	ipreinsfeapiN->OnMeasAborted(ssm)
#define ipreinsfeapiN_OnConstellationDetected(constellation)	ipreinsfeapiN->OnConstellationDetected(constellation)
#define ipreinsfeapiN_OnIqModeDetected(mode)	ipreinsfeapiN->OnIqModeDetected(mode)
#define ipreinsfeapiN_OnCodeRateDetected(highPrioRate,lowPrioRate)	ipreinsfeapiN->OnCodeRateDetected(highPrioRate,lowPrioRate)
#define ipreinsfeapiN_OnHierarchyModeDetected(mode)	ipreinsfeapiN->OnHierarchyModeDetected(mode)
#define ipreinsfeapiN_OnGuardIntervalDetected(interval)	ipreinsfeapiN->OnGuardIntervalDetected(interval)
#define ipreinsfeapiN_OnTxModeDetected(mode)	ipreinsfeapiN->OnTxModeDetected(mode)
#define ipreinsfeapiN_OnChanBandwidthDetected(bandwith)	ipreinsfeapiN->OnChanBandwidthDetected(bandwith)
#define ipreinsfeapiN_OnCarrierPresentChanged(carrier)	ipreinsfeapiN->OnCarrierPresentChanged(carrier)
#define ipreinsfeapiN_OnBerThresholdCrossed(ber,berThreshold)	ipreinsfeapiN->OnBerThresholdCrossed(ber,berThreshold)
#define ipreinspow_iPresent() (ipreinspow.Present())
#define ipreinspow_Init()	ipreinspow->Init()
#define ipreinspow_TurnOn()	ipreinspow->TurnOn()
#define ipreinspow_TurnOff()	ipreinspow->TurnOff()
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
#define ins_stidle	IHsvDigitalScan_stidle
#define ins_stfewait	IHsvDigitalScan_stfewait
#define ins_stdmxwait	IHsvDigitalScan_stdmxwait
#define ins_stdecision	IHsvDigitalScan_stdecision
#define istub_stidle	IHsvDigitalScan_stidle
#define istub_stfewait	IHsvDigitalScan_stfewait
#define istub_stdmxwait	IHsvDigitalScan_stdmxwait
#define istub_stdecision	IHsvDigitalScan_stdecision
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
#include "locals_mRoute.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

