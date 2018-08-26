#ifndef  _CHSVDVBSINSTALLATION_MSIGSTR_PRIV_H
#define  _CHSVDVBSINSTALLATION_MSIGSTR_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvInstallationSigStrength.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvWindowDestinationMap.h>
#include <CS2MwBase.h>
class CHsvDvbsInstallation_msigstr_Priv;
#define CLASSSCOPE CHsvDvbsInstallation_msigstr_Priv::
#include "locals_msigstr.h"

class CHsvDvbsInstallation_msigstr_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsInstallation_msigstr_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_msigstr.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvInstallationSigStrengthImpl(CHsvDvbsInstallation_msigstr_Priv,isigstr);
public:
ProvidesInterface<IHsvInstallationSigStrength>	isigstr;

//Required interfaces
public:
RequiresInterface<IPlfApiSigStrengthMeas>	qssm;
RequiresInterface<IPlfApiSigStrengthMeas>	vssm;
RequiresInterface<IHsvWindowDestinationMap>	wnddest;

public:
CHsvDvbsInstallation_msigstr_Priv():i__isigstr(this)
{
isigstr	=	&i__isigstr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define qssm_iPresent() (qssm.Present())
#define qssm_GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)	qssm->GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)
#define qssm_Start(winid,Avail,retval)	qssm->Start(winid,Avail,retval)
#define qssm_Stop(winid,Stopped,retval)	qssm->Stop(winid,Stopped,retval)
#define qssm_GetMeasValid(winid,Valid,retval)	qssm->GetMeasValid(winid,Valid,retval)
#define qssm_GetSigStrength(winid,Strength,retval)	qssm->GetSigStrength(winid,Strength,retval)
#define vssm_iPresent() (vssm.Present())
#define vssm_GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)	vssm->GetSigStrengthRange(winid,MinStrength,MaxStrength,retval)
#define vssm_Start(winid,Avail,retval)	vssm->Start(winid,Avail,retval)
#define vssm_Stop(winid,Stopped,retval)	vssm->Stop(winid,Stopped,retval)
#define vssm_GetMeasValid(winid,Valid,retval)	vssm->GetMeasValid(winid,Valid,retval)
#define vssm_GetSigStrength(winid,Strength,retval)	vssm->GetSigStrength(winid,Strength,retval)
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
#define isigstr_InsQsm	IHsvInstallationSigStrength_InsQsm
#define isigstr_InsSsm	IHsvInstallationSigStrength_InsSsm
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

