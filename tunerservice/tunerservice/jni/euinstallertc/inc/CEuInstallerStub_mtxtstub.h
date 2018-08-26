#ifndef  _CEUINSTALLERSTUB_MTXTSTUB_H
#define  _CEUINSTALLERSTUB_MTXTSTUB_H 

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
#include <IPumpEngine.h>
#include <CTvMwCore.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <CGfxNativeWindow.h>

class CEuInstallerStub_mtxtstub_Priv;
class CEuInstallerStub_mtxtstub
{
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
ProvidesInterface<IEnable>			dcu;
ProvidesInterface<IHsvPower>		txtpow;
void SetMwCoreInstance (CTvMwCore *Core);
void SetGfxhandle( IGfxANWabs* gfxhandle);
public:
RequiresInterface<IPlfApiVbi>			plfvbi;
RequiresInterface<IPumpEngine>			pen;

public:
CEuInstallerStub_mtxtstub();
virtual ~CEuInstallerStub_mtxtstub();
private:
CEuInstallerStub_mtxtstub_Priv	*m_priv;
};

#endif

