#ifndef  _CSVCPACI_H
#define  _CSVCPACI_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CSvcPaci_m.h>
#include <CSvcPaci_mdiv.h>
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

class CSvcPaci
{
public:
virtual ~CSvcPaci(){}

//Contained Modules
private:
CSvcPaci_m m;
CSvcPaci_mdiv mdiv;
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
RequiresInterface<ICesPaciDiv>	div;
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
Pumpdefines(CSvcPaci);

public:
CSvcPaci()
{
pow	=	m.pow;
pgaci	=	m.pgaci;
acids	=	m.acids;
txrstN	=	m.txrstN;
pginsN	=	m.pginsN;
m.pmp	=	pmp;
m.pen	=	pen;
m.adiv	=	mdiv.adiv;
mdiv.div	=	div;
m.pgaciN	=	pgaciN;
m.acidsN	=	acidsN;
m.pgcni	=	pgcni;
m.tmr	=	tmr;
m.vip	=	vip;
m.txtpre	=	txtpre;
m.pkt0	=	pkt0;
m.sysset	=	sysset;
m.langid	=	langid;
acidecN	=	m.acidecN;
m.acidec	=	acidec;
m.acidat	=	acidat;
m.prins	=	prins;
}

};

#endif

