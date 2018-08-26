#ifndef  _CEUINSTALLERSTUB_MTXTSTUB_PRIV_H
#define  _CEUINSTALLERSTUB_MTXTSTUB_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvTxtPageAccess.h>
#include <IHsvTsvChannelName.h>
#include <IHsvTxtPageConvert.h>
#include <IHsvTxtDecode.h>
#include <IHsvTxtDisplayDriver.h>
#include <ITxtDisplayDriver3.h>
#include <IEnable.h>
#include <IHsvTextDisplay.h>
#include <IHsvTxtPacket830Data.h>
#include <IHsvTxtPacket0.h>
#include <IHsvTxtPageRequest.h>
#include <IHsvTxtPresent.h>
#include <IHsvTxtVpsData.h>
#include <IPlfApiVbi.h>
#include <IPlfApiVbiNotify.h>
#include <IHsvPower.h>
class CEuInstallerStub_mtxtstub_Priv;
#define CLASSSCOPE CEuInstallerStub_mtxtstub_Priv::
#include "locals_mtxtstub.h"
#include <CGfxNativeWindow.h>
#include <CTvMwCore.h>
#include <CTCMwBase.h>

#include <IPumpEngine.h>
#include <IPumpExSub.h>

class CEuInstallerStub_mtxtstub_Priv : public CTCMwBase
{
public:
virtual ~CEuInstallerStub_mtxtstub_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mtxtstub.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvTxtPageAccessImpl(CEuInstallerStub_mtxtstub_Priv,acc);
IHsvTsvChannelNameImpl(CEuInstallerStub_mtxtstub_Priv,chlname);
IHsvTxtPageConvertImpl(CEuInstallerStub_mtxtstub_Priv,cnv);
IHsvTxtDecodeImpl(CEuInstallerStub_mtxtstub_Priv,dec);
IHsvTxtDisplayDriverImpl(CEuInstallerStub_mtxtstub_Priv,dsdrv);
ITxtDisplayDriver3Impl(CEuInstallerStub_mtxtstub_Priv,dsdrv3);
IEnableImpl(CEuInstallerStub_mtxtstub_Priv,dsenb);
IHsvTextDisplayImpl(CEuInstallerStub_mtxtstub_Priv,gfxtxt);
IHsvTxtPacket830DataImpl(CEuInstallerStub_mtxtstub_Priv,p830);
IHsvTxtPacket0Impl(CEuInstallerStub_mtxtstub_Priv,pkt0);
IHsvTxtPageRequestImpl(CEuInstallerStub_mtxtstub_Priv,req);
IHsvTxtPresentImpl(CEuInstallerStub_mtxtstub_Priv,txtpre);
IHsvTxtVpsDataImpl(CEuInstallerStub_mtxtstub_Priv,vps);
IPlfApiVbiNotifyImpl(CEuInstallerStub_mtxtstub_Priv,plfvbintf);
IEnableImpl(CEuInstallerStub_mtxtstub_Priv,dcu);
IHsvPowerImpl(CEuInstallerStub_mtxtstub_Priv,pow);
public:
ProvidesInterface<IHsvTxtPageAccess>	acc;

ProvidesInterface<IHsvTsvChannelName>	chlname;

ProvidesInterface<IHsvTxtPageConvert>	cnv;

ProvidesInterface<IHsvTxtDecode>	dec;

ProvidesInterface<IHsvTxtDisplayDriver>	dsdrv;

ProvidesInterface<ITxtDisplayDriver3>	dsdrv3;

ProvidesInterface<IEnable>	dsenb;

ProvidesInterface<IHsvTextDisplay>	gfxtxt;

ProvidesInterface<IHsvTxtPacket830Data>	p830;

ProvidesInterface<IHsvTxtPacket0>	pkt0;

ProvidesInterface<IHsvTxtPageRequest>	req;

ProvidesInterface<IHsvTxtPresent>	txtpre;

ProvidesInterface<IHsvTxtVpsData>	vps;

ProvidesInterface<IPlfApiVbiNotify>	  	    plfvbintf;
ProvidesInterface<IEnable>		dcu;
ProvidesInterface<IHsvPower>	pow;
void SetMwCoreInstance (CTvMwCore *Core);
public:
RequiresInterface<IPlfApiVbi>		plfvbi;
RequiresInterface<IPumpEngine>		pen;

void Settxtplfhandle( CEuInstallerStub_mtxtstub_Priv* txtplfhandle);
void SetGfxhandle( IGfxANWabs* gfxhandle);

public:
CEuInstallerStub_mtxtstub_Priv():i__acc(this),i__chlname(this),i__cnv(this),i__dec(this),i__dsdrv(this),i__dsdrv3(this),i__dsenb(this),i__gfxtxt(this),i__p830(this),i__pkt0(this),i__req(this),i__txtpre(this),i__vps(this),i__plfvbintf(this),i__dcu(this), i__pow(this)
{
acc	=	&i__acc;
chlname	=	&i__chlname;
cnv	=	&i__cnv;
dec	=	&i__dec;
dsdrv	=	&i__dsdrv;
dsdrv3	=	&i__dsdrv3;
dsenb	=	&i__dsenb;
gfxtxt	=	&i__gfxtxt;
p830	=	&i__p830;
pkt0	=	&i__pkt0;
req	=	&i__req;
txtpre	=	&i__txtpre;
vps	=	&i__vps;
plfvbintf=&i__plfvbintf;
dcu = &i__dcu;
pow= &i__pow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define chlname_ChannelLabelLength	i__chlname.m_ChannelLabelLength
#define cnv_LEVEL_10	IHsvTxtPageConvert_LEVEL_10
#define cnv_LEVEL_15	IHsvTxtPageConvert_LEVEL_15
#define cnv_LEVEL_25	IHsvTxtPageConvert_LEVEL_25
#define cnv_TRH_HOLD	IHsvTxtPageConvert_TRH_HOLD
#define cnv_TRH_ROL	IHsvTxtPageConvert_TRH_ROL
#define cnv_TRT_HOLD	IHsvTxtPageConvert_TRT_HOLD
#define cnv_TRT_ROL	IHsvTxtPageConvert_TRT_ROL
#define dsdrv_FillerPad	i__dsdrv.m_FillerPad
#define dsdrv_BodyPad	i__dsdrv.m_BodyPad
#define dsdrv_SidePanelL	i__dsdrv.m_SidePanelL
#define dsdrv_SidePanelR	i__dsdrv.m_SidePanelR
#define dsdrv_StatusPad	i__dsdrv.m_StatusPad
#define dsdrv_HeaderPad	i__dsdrv.m_HeaderPad
#define dsdrv_TimePad	i__dsdrv.m_TimePad
#define dsdrv3_FlashModeNone	ITxtDisplayDriver3_FlashModeNone
#define dsdrv3_FlashModeNormal	ITxtDisplayDriver3_FlashModeNormal
#define dsdrv3_FlashModeInverse	ITxtDisplayDriver3_FlashModeInverse
#define dsdrv3_FlashModeColour	ITxtDisplayDriver3_FlashModeColour
#define dsdrv3_FlashPhase1H50	ITxtDisplayDriver3_FlashPhase1H50
#define dsdrv3_FlashPhase2H501	ITxtDisplayDriver3_FlashPhase2H501
#define dsdrv3_FlashPhase2H502	ITxtDisplayDriver3_FlashPhase2H502
#define dsdrv3_FlashPhase2H503	ITxtDisplayDriver3_FlashPhase2H503
#define dsdrv3_FillerPad	i__dsdrv3.m_FillerPad
#define dsdrv3_HeaderPad	i__dsdrv3.m_HeaderPad
#define dsdrv3_TimePad	i__dsdrv3.m_TimePad
#define dsdrv3_BodyPad	i__dsdrv3.m_BodyPad
#define dsdrv3_SidePanelL	i__dsdrv3.m_SidePanelL
#define dsdrv3_SidePanelR	i__dsdrv3.m_SidePanelR
#define dsdrv3_StatusPad	i__dsdrv3.m_StatusPad
#define gfxtxt_MaxDisplayList	i__gfxtxt.m_MaxDisplayList
#define gfxtxt_MaxClutSize	i__gfxtxt.m_MaxClutSize
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
#define vps_PilCodeField	IHsvTxtVpsData_PilCodeField
#define vps_CNICodeField	IHsvTxtVpsData_CNICodeField
#define vps_ProgramTypeField	IHsvTxtVpsData_ProgramTypeField
#define vps_ProgramControlStatusField	IHsvTxtVpsData_ProgramControlStatusField
#define vps_DistinctionBitsField	IHsvTxtVpsData_DistinctionBitsField
#define vps_InvalidRequestId	IHsvTxtVpsData_InvalidRequestId
#define plfvbi_EnableAutoSlicing(winid,enable,retval)		plfvbi->EnableAutoSlicing(winid,enable,retval)
#define plfvbi_SetSlicermode(winid,ubscriptions,retval)		plfvbi->SetSlicermode(winid,ubscriptions,retval)
#define plfvbi_Enable()								plfvbi->Enable()
#define plfvbi_Disable()			plfvbi->Disable()
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
#include "locals_mtxtstub.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

