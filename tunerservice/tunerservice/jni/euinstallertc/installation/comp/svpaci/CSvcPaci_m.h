#ifndef  _CSVCPACI_M_H
#define  _CSVCPACI_M_H 

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
class CSvcPaci_m_Priv;
class CSvcPaci_m
{
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
public:
CSvcPaci_m();
virtual ~CSvcPaci_m();
private:
CSvcPaci_m_Priv	*m_priv;
};

#endif

