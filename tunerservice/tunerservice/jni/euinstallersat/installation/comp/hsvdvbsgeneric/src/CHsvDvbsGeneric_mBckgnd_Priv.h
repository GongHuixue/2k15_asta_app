#ifndef  _CHSVDVBSGENERIC_MBCKGND_PRIV_H
#define  _CHSVDVBSGENERIC_MBCKGND_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteBackgroundInstallation.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteInstallation.h>
#include <IPumpEngine.h>
#include <ITvPlatformResource.h>
#include <IPumpExSub.h>
#include <IHsvSatelliteDiversity.h>
#include <CS2MwBase.h>
class CHsvDvbsGeneric_mBckgnd_Priv;
#define CLASSSCOPE CHsvDvbsGeneric_mBckgnd_Priv::
#include "locals_mBckgnd.h"

class CHsvDvbsGeneric_mBckgnd_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsGeneric_mBckgnd_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mBckgnd.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvSdmControlNotifyExImpl(CHsvDvbsGeneric_mBckgnd_Priv,bckctrlN);
IHsvDigitalAcquisitionNotifyImpl(CHsvDvbsGeneric_mBckgnd_Priv,ibckAcqN);
IHsvSatelliteBackgroundInstallationImpl(CHsvDvbsGeneric_mBckgnd_Priv,ibckInstall);
IHsvPowerImpl(CHsvDvbsGeneric_mBckgnd_Priv,ibckgndpow);
IHsvStreamNotifyImpl(CHsvDvbsGeneric_mBckgnd_Priv,strapiN);
public:
ProvidesInterface<IHsvSdmControlNotifyEx>	bckctrlN;

ProvidesInterface<IHsvDigitalAcquisitionNotify>	ibckAcqN;

ProvidesInterface<IHsvSatelliteBackgroundInstallation>	ibckInstall;

ProvidesInterface<IHsvPower>	ibckgndpow;

ProvidesInterface<IHsvStreamNotify>	strapiN;

//Required interfaces
public:
RequiresInterface<IHsvDigitalAcquisition>	idataacq;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<ITvPlatformResource>	plfres;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatelliteDiversity>	s2div;
private:
Pumpdefines(CHsvDvbsGeneric_mBckgnd_Priv);

public:
CHsvDvbsGeneric_mBckgnd_Priv():i__bckctrlN(this),i__ibckAcqN(this),i__ibckInstall(this),i__ibckgndpow(this),i__strapiN(this)
{
bckctrlN	=	&i__bckctrlN;
ibckAcqN	=	&i__ibckAcqN;
ibckInstall	=	&i__ibckInstall;
ibckgndpow	=	&i__ibckgndpow;
strapiN	=	&i__strapiN;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define idataacq_iPresent() (idataacq.Present())
#define idataacq_Homing	IHsvDigitalAcquisition_Homing
#define idataacq_Fallback	IHsvDigitalAcquisition_Fallback
#define idataacq_Normal	IHsvDigitalAcquisition_Normal
#define idataacq_Background	IHsvDigitalAcquisition_Background
#define idataacq_Initialise(LnbNumber)	idataacq->Initialise(LnbNumber)
#define idataacq_AcquireData(Mode)	idataacq->AcquireData(Mode)
#define idataacq_AcquireDataOnTimeout()	idataacq->AcquireDataOnTimeout()
#define idataacq_GetNumberOfDigitalChannelsFound()	idataacq->GetNumberOfDigitalChannelsFound()
#define idataacq_GetNumberOfDigitalChannelsRemoved()	idataacq->GetNumberOfDigitalChannelsRemoved()
#define idataacq_GetNumberOfTvChannelsFound()	idataacq->GetNumberOfTvChannelsFound()
#define idataacq_GetNumberOfRadioChannelsFound()	idataacq->GetNumberOfRadioChannelsFound()
#define idataacq_GetNumberOfTvChannelsRemoved()	idataacq->GetNumberOfTvChannelsRemoved()
#define idataacq_GetNumberofRadioChannelsRemoved()	idataacq->GetNumberofRadioChannelsRemoved()
#define idataacq_StoreBarkerMuxDetails()	idataacq->StoreBarkerMuxDetails()
#define idataacq_SyncTemporaryTableRecords()	idataacq->SyncTemporaryTableRecords()
#define idataacq_GetNumberOfSdsds()	idataacq->GetNumberOfSdsds()
#define idataacq_GetSdsdByIndex(count,SdSdEntry)	idataacq->GetSdsdByIndex(count,SdSdEntry)
#define idataacq_GetNumberOfTvChannelsInLnb(Lnb)	idataacq->GetNumberOfTvChannelsInLnb(Lnb)
#define idataacq_GetNumberOfRadioChannelsInLnb(Lnb)	idataacq->GetNumberOfRadioChannelsInLnb(Lnb)
#define insstate_iPresent() (insstate.Present())
#define insstate_InstallationNone	IHsvSatelliteInstallation_InstallationNone
#define insstate_InstallationPreScan	IHsvSatelliteInstallation_InstallationPreScan
#define insstate_InstallationServiceScan	IHsvSatelliteInstallation_InstallationServiceScan
#define insstate_InstallationUpdate	IHsvSatelliteInstallation_InstallationUpdate
#define insstate_InstallationManual	IHsvSatelliteInstallation_InstallationManual
#define insstate_InstallationAddSatellite	IHsvSatelliteInstallation_InstallationAddSatellite
#define insstate_InstallationAutomaticUpdate	IHsvSatelliteInstallation_InstallationAutomaticUpdate
#define insstate_InstallationBackground	IHsvSatelliteInstallation_InstallationBackground
#define insstate_InstallationMiniPrecan	IHsvSatelliteInstallation_InstallationMiniPrecan
#define insstate_InstallationBackgroundUpdate	IHsvSatelliteInstallation_InstallationBackgroundUpdate
#define insstate_InstallationPackageParsing	IHsvSatelliteInstallation_InstallationPackageParsing
#define insstate_InstallationStateIdle	IHsvSatelliteInstallation_InstallationStateIdle
#define insstate_InstallationStateRegionScan	IHsvSatelliteInstallation_InstallationStateRegionScan
#define insstate_InstallationStateInProgress	IHsvSatelliteInstallation_InstallationStateInProgress
#define insstate_InstallationStateSorting	IHsvSatelliteInstallation_InstallationStateSorting
#define insstate_AttributePackageId	IHsvSatelliteInstallation_AttributePackageId
#define insstate_AttributePackageOnly	IHsvSatelliteInstallation_AttributePackageOnly
#define insstate_AttributePackageGroup	IHsvSatelliteInstallation_AttributePackageGroup
#define insstate_AttributeAssetManager	IHsvSatelliteInstallation_AttributeAssetManager
#define insstate_ManualInstallLnb	IHsvSatelliteInstallation_ManualInstallLnb
#define insstate_ManualInstallFreq	IHsvSatelliteInstallation_ManualInstallFreq
#define insstate_ManualInstallPolaraization	IHsvSatelliteInstallation_ManualInstallPolaraization
#define insstate_ManualInstallSymRate	IHsvSatelliteInstallation_ManualInstallSymRate
#define insstate_ManualInstallSymRateMode	IHsvSatelliteInstallation_ManualInstallSymRateMode
#define insstate_ManualInstallModulation	IHsvSatelliteInstallation_ManualInstallModulation
#define insstate_SatLnb1	IHsvSatelliteInstallation_SatLnb1
#define insstate_SatLnb2	IHsvSatelliteInstallation_SatLnb2
#define insstate_SatLnb3	IHsvSatelliteInstallation_SatLnb3
#define insstate_SatLnb4	IHsvSatelliteInstallation_SatLnb4
#define insstate_GetCurrentInstallationState(mode,state)	insstate->GetCurrentInstallationState(mode,state)
#define insstate_StartInstallation(Source,Lnb,Mode)	insstate->StartInstallation(Source,Lnb,Mode)
#define insstate_StopInstallation()	insstate->StopInstallation()
#define insstate_ResetInstallation()	insstate->ResetInstallation()
#define insstate_GetNumberOfTvChannelsFound(Lnb)	insstate->GetNumberOfTvChannelsFound(Lnb)
#define insstate_GetNumberofRadioChannelsFound(Lnb)	insstate->GetNumberofRadioChannelsFound(Lnb)
#define insstate_GetNumberOfTvChannelsRemoved(Lnb)	insstate->GetNumberOfTvChannelsRemoved(Lnb)
#define insstate_GetNumberofRadioChannelsRemoved(Lnb)	insstate->GetNumberofRadioChannelsRemoved(Lnb)
#define insstate_GetSatelliteName(Lnb,SatelliteName)	insstate->GetSatelliteName(Lnb,SatelliteName)
#define insstate_GetNumberOfDigitalChannelsAdded()	insstate->GetNumberOfDigitalChannelsAdded()
#define insstate_GetNumberOfDigitalChannelsRemoved()	insstate->GetNumberOfDigitalChannelsRemoved()
#define insstate_GetNumberOfDigitalChannelsMoved()	insstate->GetNumberOfDigitalChannelsMoved()
#define insstate_IdentifyPackagesAvailable()	insstate->IdentifyPackagesAvailable()
#define insstate_GetTotalNumberOfPackagesFound()	insstate->GetTotalNumberOfPackagesFound()
#define insstate_GetPackageByIndex(Index,Package)	insstate->GetPackageByIndex(Index,Package)
#define insstate_SetUserPackageIndex(PackageIndex)	insstate->SetUserPackageIndex(PackageIndex)
#define insstate_GetUserPackageIndex(PackageIndex,IsPackage)	insstate->GetUserPackageIndex(PackageIndex,IsPackage)
#define insstate_GetInstalledSatellites(mode,SatelliteEntries)	insstate->GetInstalledSatellites(mode,SatelliteEntries)
#define insstate_InstallAddedSatellites()	insstate->InstallAddedSatellites()
#define insstate_ResetAddedSatellites()	insstate->ResetAddedSatellites()
#define insstate_RemoveSatelliteEntry(LnbNumber)	insstate->RemoveSatelliteEntry(LnbNumber)
#define insstate_GetSatelliteSignalStrength(LnbNumber)	insstate->GetSatelliteSignalStrength(LnbNumber)
#define insstate_GetSatelliteSignalQuality(LnbNumber)	insstate->GetSatelliteSignalQuality(LnbNumber)
#define insstate_LoadManualInstallationDefaultValues()	insstate->LoadManualInstallationDefaultValues()
#define insstate_StoreManualInstallationValues()	insstate->StoreManualInstallationValues()
#define insstate_GetAttribute(Mode,AttributeId)	insstate->GetAttribute(Mode,AttributeId)
#define insstate_SetAttribute(Mode,AttributeId,Value)	insstate->SetAttribute(Mode,AttributeId,Value)
#define insstate_GetScanProgressStatus(Mode)	insstate->GetScanProgressStatus(Mode)
#define insstate_GetSITableIds(NetworkID,BouquetID)	insstate->GetSITableIds(NetworkID,BouquetID)
#define insstate_GetPackageName(PackageId,PackageName)	insstate->GetPackageName(PackageId,PackageName)
#define insstate_GetSIDetails(SiValues)	insstate->GetSIDetails(SiValues)
#define insstate_EnableUnicable(LnbNumber,Enable)	insstate->EnableUnicable(LnbNumber,Enable)
#define insstate_StopSignalStrengthMeas(LnbNumber)	insstate->StopSignalStrengthMeas(LnbNumber)
#define insstate_GetSignalQuality(Param)	insstate->GetSignalQuality(Param)
#define insstate_StartSignalStrengthMeas(LnbNumber)	insstate->StartSignalStrengthMeas(LnbNumber)
#define insstate_GetSignalStrength(param)	insstate->GetSignalStrength(param)
#define insstate_StartPredefinedListCopy()	insstate->StartPredefinedListCopy()
#define insstate_GetFirstInstalledChannel()	insstate->GetFirstInstalledChannel()
#define insstate_UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)	insstate->UpdateConfigXmlStrings(PrescanXmlString,PrescanXmlStringLen,SatellitePackageXmlString,SatellitePackageXmlStringLen)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define plfres_iPresent() (plfres.Present())
#define plfres_IsResourceOwned(resid)	plfres->IsResourceOwned(resid)
#define plfres_GetOwnedResources()	plfres->GetOwnedResources()
#define plfres_AudioFeaturing	ITvPlatformResource_AudioFeaturing
#define plfres_Connectivity	ITvPlatformResource_Connectivity
#define plfres_Frontend	ITvPlatformResource_Frontend
#define plfres_General	ITvPlatformResource_General
#define plfres_Infrastructure	ITvPlatformResource_Infrastructure
#define plfres_Source	ITvPlatformResource_Source
#define plfres_VideoFeaturing	ITvPlatformResource_VideoFeaturing
#define plfres_Xray	ITvPlatformResource_Xray
#define plfres_Scale	ITvPlatformResource_Scale
#define plfres_Gfx	ITvPlatformResource_Gfx
#define plfres_Mute	ITvPlatformResource_Mute
#define plfres_GetResourceState()	plfres->GetResourceState()
#define plfres_RequestResourceState(State)	plfres->RequestResourceState(State)
#define plfres_RestorePreviousState()	plfres->RestorePreviousState()
#define plfres_ConvertStateToResourceid(State)	plfres->ConvertStateToResourceid(State)
#define plfres_RequestResource(resid)	plfres->RequestResource(resid)
#define plfres_FullState	ITvPlatformResource_FullState
#define plfres_SubState	ITvPlatformResource_SubState
#define plfres_IdleState	ITvPlatformResource_IdleState
#define plfres_FullStateWithVideoScale	ITvPlatformResource_FullStateWithVideoScale
#define plfres_Invalid	ITvPlatformResource_Invalid
#define plfres_FullWithScaleState	ITvPlatformResource_FullWithScaleState
#define plfres_IdleWithMuteState	ITvPlatformResource_IdleWithMuteState
#define plfres_FullStateWithOutMute	ITvPlatformResource_FullStateWithOutMute
#define plfres_FrontEndState	ITvPlatformResource_FrontEndState
#define plfres_ScaleState	ITvPlatformResource_ScaleState
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsGeneric_mBckgnd_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define s2div_iPresent() (s2div.Present())
#define s2div_iVersion	s2div->iVersion()
#define s2div_IsHomingMuxTuningRequired(SatelliteId,CountryId)	s2div->IsHomingMuxTuningRequired(SatelliteId,CountryId)
#define s2div_LoadDefaultConnectionType(CountryId,ConnectionType)	s2div->LoadDefaultConnectionType(CountryId,ConnectionType)
#define s2div_LoadDefaultLnbType(CountryId,LnbType)	s2div->LoadDefaultLnbType(CountryId,LnbType)
#define s2div_IsBackgroundInstallRequired()	s2div->IsBackgroundInstallRequired()
#define s2div_PerformReinstallInSemiStandby()	s2div->PerformReinstallInSemiStandby()
#define bckctrlN_DataNotAvailable	IHsvSdmControlNotifyEx_DataNotAvailable
#define bckctrlN_OnlyPsiDataAvailable	IHsvSdmControlNotifyEx_OnlyPsiDataAvailable
#define bckctrlN_SiDataAvailable	IHsvSdmControlNotifyEx_SiDataAvailable
#define bckctrlN_StartedCollection	IHsvSdmControlNotifyEx_StartedCollection
#define bckctrlN_StoppedCollection	IHsvSdmControlNotifyEx_StoppedCollection
#define bckctrlN_DataAvailable	IHsvSdmControlNotifyEx_DataAvailable
#define bckctrlN_SDT	IHsvSdmControlNotifyEx_SDT
#define bckctrlN_NIT	IHsvSdmControlNotifyEx_NIT
#define bckctrlN_EIT	IHsvSdmControlNotifyEx_EIT
#define bckctrlN_TOT	IHsvSdmControlNotifyEx_TOT
#define bckctrlN_TDT	IHsvSdmControlNotifyEx_TDT
#define bckctrlN_PMT	IHsvSdmControlNotifyEx_PMT
#define bckctrlN_PAT	IHsvSdmControlNotifyEx_PAT
#define bckctrlN_CAT	IHsvSdmControlNotifyEx_CAT
#define bckctrlN_UNT	IHsvSdmControlNotifyEx_UNT
#define bckctrlN_SIMPLEPAT	IHsvSdmControlNotifyEx_SIMPLEPAT
#define bckctrlN_SIMPLEPMT	IHsvSdmControlNotifyEx_SIMPLEPMT
#define bckctrlN_BAT	IHsvSdmControlNotifyEx_BAT
#define bckctrlN_FNT	IHsvSdmControlNotifyEx_FNT
#define bckctrlN_FST	IHsvSdmControlNotifyEx_FST
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
#include "locals_mBckgnd.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

