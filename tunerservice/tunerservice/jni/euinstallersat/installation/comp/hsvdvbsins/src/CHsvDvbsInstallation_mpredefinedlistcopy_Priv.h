#ifndef  _CHSVDVBSINSTALLATION_MPREDEFINEDLISTCOPY_PRIV_H
#define  _CHSVDVBSINSTALLATION_MPREDEFINEDLISTCOPY_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPredefinedListCopy.h>
#include <IHsvPower.h>
#include <IPlfApiStorageDeviceNotify.h>
#include <IPlfApiPhysDeviceNotify.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IPumpEngine.h>
#include <IPumpExSub.h>
#include <IPlfApiStorageDevice.h>
#include <ICeIsTpHostRtk2.h>
#include <tprtkdefines.h>
#include <IPlfApiPhysDevice.h>
#include <IHsvWindowDestinationMap.h>
#include <CS2MwBase.h>
class CHsvDvbsInstallation_mpredefinedlistcopy_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_mpredefinedlistcopy_Priv::
#include "locals_mpredefinedlistcopy.h"

class CHsvDvbsInstallation_mpredefinedlistcopy_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_mpredefinedlistcopy_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mpredefinedlistcopy.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPredefinedListCopyImpl(CHsvDvbsInstallation_mpredefinedlistcopy_Priv,ipredefcopy);
IHsvPowerImpl(CHsvDvbsInstallation_mpredefinedlistcopy_Priv,ipredefpow);
IPlfApiStorageDeviceNotifyImpl(CHsvDvbsInstallation_mpredefinedlistcopy_Priv,recdevN);
IPlfApiPhysDeviceNotifyImpl(CHsvDvbsInstallation_mpredefinedlistcopy_Priv,usbdevexN);
public:
ProvidesInterface<IHsvPredefinedListCopy>	ipredefcopy;

ProvidesInterface<IHsvPower>	ipredefpow;

ProvidesInterface<IPlfApiStorageDeviceNotify>	recdevN;

ProvidesInterface<IPlfApiPhysDeviceNotify>	usbdevexN;

//Required interfaces
public:
RequiresInterface<IHsvErrorCodeEx>	err;
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IPlfApiStorageDevice>	recdev;
RequiresInterface<ICeIsTpHostRtk2>	tprtk;
RequiresInterface<IPlfApiPhysDevice>	usbms;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;
private:
Pumpdefines(CHsvDvbsInstallation_mpredefinedlistcopy_Priv);
TpRtkDefines(CHsvDvbsInstallation_mpredefinedlistcopy_Priv);

public:
CHsvDvbsInstallation_mpredefinedlistcopy_Priv():i__ipredefcopy(this),i__ipredefpow(this),i__recdevN(this),i__usbdevexN(this)
{
ipredefcopy	=	&i__ipredefcopy;
ipredefpow	=	&i__ipredefpow;
recdevN	=	&i__recdevN;
usbdevexN	=	&i__usbdevexN;
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
#define iinsN_iPresent() (iinsN.Present())
#define iinsN_EventInsStarted	IHsvSatelliteInstallationNotify_EventInsStarted
#define iinsN_EventInsStopped	IHsvSatelliteInstallationNotify_EventInsStopped
#define iinsN_EventInsCompleted	IHsvSatelliteInstallationNotify_EventInsCompleted
#define iinsN_EventInsFailed	IHsvSatelliteInstallationNotify_EventInsFailed
#define iinsN_EventSatelliteFound	IHsvSatelliteInstallationNotify_EventSatelliteFound
#define iinsN_EventSatelliteNotFound	IHsvSatelliteInstallationNotify_EventSatelliteNotFound
#define iinsN_EventSortingStarted	IHsvSatelliteInstallationNotify_EventSortingStarted
#define iinsN_EventSortStopped	IHsvSatelliteInstallationNotify_EventSortStopped
#define iinsN_EventSortCompleted	IHsvSatelliteInstallationNotify_EventSortCompleted
#define iinsN_EventSortInProgress	IHsvSatelliteInstallationNotify_EventSortInProgress
#define iinsN_EventChannelFound	IHsvSatelliteInstallationNotify_EventChannelFound
#define iinsN_EventChannelNotFound	IHsvSatelliteInstallationNotify_EventChannelNotFound
#define iinsN_EventInsProgress	IHsvSatelliteInstallationNotify_EventInsProgress
#define iinsN_EventInsCompletedForLnb	IHsvSatelliteInstallationNotify_EventInsCompletedForLnb
#define iinsN_EventSatLnbRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalCompleted
#define iinsN_EventContentLibRead	IHsvSatelliteInstallationNotify_EventContentLibRead
#define iinsN_EventPkgInstallStart	IHsvSatelliteInstallationNotify_EventPkgInstallStart
#define iinsN_EventPkgInstallEnd	IHsvSatelliteInstallationNotify_EventPkgInstallEnd
#define iinsN_EventRegionScanEnd	IHsvSatelliteInstallationNotify_EventRegionScanEnd
#define iinsN_EventLNBStart	IHsvSatelliteInstallationNotify_EventLNBStart
#define iinsN_EventLNBEnd	IHsvSatelliteInstallationNotify_EventLNBEnd
#define iinsN_EventSatLnbRemovalStarted	IHsvSatelliteInstallationNotify_EventSatLnbRemovalStarted
#define iinsN_EventSatRemovalCompleted	IHsvSatelliteInstallationNotify_EventSatRemovalCompleted
#define iinsN_EventPackageInstallFailed	IHsvSatelliteInstallationNotify_EventPackageInstallFailed
#define iinsN_EventPackageId	IHsvSatelliteInstallationNotify_EventPackageId
#define iinsN_EventPredefinedListCopySuccesful	IHsvSatelliteInstallationNotify_EventPredefinedListCopySuccesful
#define iinsN_EventPredefinedListCopyGenericError	IHsvSatelliteInstallationNotify_EventPredefinedListCopyGenericError
#define iinsN_EventPredefinedListCopyOlderVersion	IHsvSatelliteInstallationNotify_EventPredefinedListCopyOlderVersion
#define iinsN_EventDifferentSatelliteFound	IHsvSatelliteInstallationNotify_EventDifferentSatelliteFound
#define iinsN_EventPkgParsingStarted	IHsvSatelliteInstallationNotify_EventPkgParsingStarted
#define iinsN_EventPkgParsingCompleted	IHsvSatelliteInstallationNotify_EventPkgParsingCompleted
#define iinsN_EventTriggerBckgndUpdateInstall	IHsvSatelliteInstallationNotify_EventTriggerBckgndUpdateInstall
#define iinsN_OnEvent(eventid,value)	iinsN->OnEvent(eventid,value)
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsInstallation_mpredefinedlistcopy_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define recdev_iPresent() (recdev.Present())
#define recdev_ErrorOk	IPlfApiStorageDevice_ErrorOk
#define recdev_ErrorInvalidArgument	IPlfApiStorageDevice_ErrorInvalidArgument
#define recdev_ErrorContainerListTooBig	IPlfApiStorageDevice_ErrorContainerListTooBig
#define recdev_ErrorMountPathTooBig	IPlfApiStorageDevice_ErrorMountPathTooBig
#define recdev_ErrorStorageNameTooBig	IPlfApiStorageDevice_ErrorStorageNameTooBig
#define recdev_ContTypeUnknown	IPlfApiStorageDevice_ContTypeUnknown
#define recdev_ContTypeMedia	IPlfApiStorageDevice_ContTypeMedia
#define recdev_ContTypeRecording	IPlfApiStorageDevice_ContTypeRecording
#define recdev_ContTypeTimeshift	IPlfApiStorageDevice_ContTypeTimeshift
#define recdev_ContTypeVideostore	IPlfApiStorageDevice_ContTypeVideostore
#define recdev_ContTypeAll	IPlfApiStorageDevice_ContTypeAll
#define recdev_PhysIdsAll	IPlfApiStorageDevice_PhysIdsAll
#define recdev_MaxContainerListSize	IPlfApiStorageDevice_MaxContainerListSize
#define recdev_MaxMountPathSize	IPlfApiStorageDevice_MaxMountPathSize
#define recdev_MaxStorageNameSize	IPlfApiStorageDevice_MaxStorageNameSize
#define recdev_IsInitializationDone(winid,done)	recdev->IsInitializationDone(winid,done)
#define recdev_IsStoragePrepared(winid,conttype,prepared)	recdev->IsStoragePrepared(winid,conttype,prepared)
#define recdev_PrepareStorage(winid,id,conttype,retval)	recdev->PrepareStorage(winid,id,conttype,retval)
#define recdev_GetContainerList(winid,conttype,physid,items,numitems,retval)	recdev->GetContainerList(winid,conttype,physid,items,numitems,retval)
#define recdev_GetSize(winid,id,size)	recdev->GetSize(winid,id,size)
#define recdev_GetFreeSize(winid,id,size)	recdev->GetFreeSize(winid,id,size)
#define recdev_GetWriteProtected(winid,contid,protect)	recdev->GetWriteProtected(winid,contid,protect)
#define recdev_GetPath(winid,contid,path)	recdev->GetPath(winid,contid,path)
#define recdev_GetStorageName(winid,contid,name)	recdev->GetStorageName(winid,contid,name)
#define recdev_GetUniqueID(winid,contid,uid)	recdev->GetUniqueID(winid,contid,uid)
#define recdev_GetType(winid,contid,conttype)	recdev->GetType(winid,contid,conttype)
#define recdev_GetPhysID(winid,contid,physid)	recdev->GetPhysID(winid,contid,physid)
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
#define tprtk_TaskCreate(n,pr,s,e,p) tprtk->TaskCreate(n,pr,s,reinterpret_cast<FunctionInt>(static_cast<IRunnable*>(new RtkThreadRunnable<CHsvDvbsInstallation_mpredefinedlistcopy_Priv>(&CHsvDvbsInstallation_mpredefinedlistcopy_Priv::e, this)) ),0)
#define usbms_iPresent() (usbms.Present())
#define usbms_ErrorOk	IPlfApiPhysDevice_ErrorOk
#define usbms_ErrorDeviceListTooBig	IPlfApiPhysDevice_ErrorDeviceListTooBig
#define usbms_ErrorDeviceNameTooBig	IPlfApiPhysDevice_ErrorDeviceNameTooBig
#define usbms_PhysTypeUnknown	IPlfApiPhysDevice_PhysTypeUnknown
#define usbms_PhysTypeUsbMs	IPlfApiPhysDevice_PhysTypeUsbMs
#define usbms_PhysTypeUsbImage	IPlfApiPhysDevice_PhysTypeUsbImage
#define usbms_PhysTypeUsbHid	IPlfApiPhysDevice_PhysTypeUsbHid
#define usbms_PhysTypeUsbNet	IPlfApiPhysDevice_PhysTypeUsbNet
#define usbms_PhysTypeSD	IPlfApiPhysDevice_PhysTypeSD
#define usbms_PhysTypeEmmc	IPlfApiPhysDevice_PhysTypeEmmc
#define usbms_PhysTypeNetSmb	IPlfApiPhysDevice_PhysTypeNetSmb
#define usbms_PhysTypeNetNfs	IPlfApiPhysDevice_PhysTypeNetNfs
#define usbms_PhysTypeSkypeCam	IPlfApiPhysDevice_PhysTypeSkypeCam
#define usbms_PhysTypeUsbWifi	IPlfApiPhysDevice_PhysTypeUsbWifi
#define usbms_PhysTypeAll	IPlfApiPhysDevice_PhysTypeAll
#define usbms_MaxDeviceListSize	IPlfApiPhysDevice_MaxDeviceListSize
#define usbms_MaxDeviceNameSize	IPlfApiPhysDevice_MaxDeviceNameSize
#define usbms_IsInitializationDone(winid,done)	usbms->IsInitializationDone(winid,done)
#define usbms_GetDeviceList(winid,phystype,items,numitems,retval)	usbms->GetDeviceList(winid,phystype,items,numitems,retval)
#define usbms_GetDeviceName(winid,physid,name)	usbms->GetDeviceName(winid,physid,name)
#define usbms_GetType(winid,physid,phystype)	usbms->GetType(winid,physid,phystype)
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
#define recdevN_ErrorUnknown	IPlfApiStorageDeviceNotify_ErrorUnknown
#define recdevN_ErrorMaxStorages	IPlfApiStorageDeviceNotify_ErrorMaxStorages
#define recdevN_ErrorUnmountStorage	IPlfApiStorageDeviceNotify_ErrorUnmountStorage
#define recdevN_StatusOk	IPlfApiStorageDeviceNotify_StatusOk
#define recdevN_StatusPartitionFailed	IPlfApiStorageDeviceNotify_StatusPartitionFailed
#define recdevN_StatusFormatFailed	IPlfApiStorageDeviceNotify_StatusFormatFailed
#define recdevN_StatusSpeedtestFailed	IPlfApiStorageDeviceNotify_StatusSpeedtestFailed
#define recdevN_StepFormat	IPlfApiStorageDeviceNotify_StepFormat
#define recdevN_StepSpeedtest	IPlfApiStorageDeviceNotify_StepSpeedtest
#define usbdevexN_ErrorUnknown	IPlfApiPhysDeviceNotify_ErrorUnknown
#define usbdevexN_ErrorMaxDevices	IPlfApiPhysDeviceNotify_ErrorMaxDevices
#define usbdevexN_ErrorMountDevice	IPlfApiPhysDeviceNotify_ErrorMountDevice
#define usbdevexN_ErrorUnmountDevice	IPlfApiPhysDeviceNotify_ErrorUnmountDevice
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
#include "locals_mpredefinedlistcopy.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

