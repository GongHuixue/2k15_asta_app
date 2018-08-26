#ifndef EUINSSTUB_MTXTSTUB
#define EUINSSTUB_MTXTSTUB

#define GENERATE__LEGACY__DEFINES

#include "../CEuInstallerStub_mtxtstub.h"
#include "CEuInstallerStub_mtxtstub_Priv.h"
#include <InfraGlobals.h>
#include <CTvMwCore.h>


#undef GENERATE__LEGACY__DEFINES
void CEuInstallerStub_mtxtstub_Priv::params__init(void)
{
}
CEuInstallerStub_mtxtstub_Priv::~CEuInstallerStub_mtxtstub_Priv()
{
}
//public class connections
CEuInstallerStub_mtxtstub::CEuInstallerStub_mtxtstub()
{
 m_priv = new CEuInstallerStub_mtxtstub_Priv();
acc	= m_priv->acc;
chlname	= m_priv->chlname;
cnv	= m_priv->cnv;
dec	= m_priv->dec;
dsdrv	= m_priv->dsdrv;
dsdrv3	= m_priv->dsdrv3;
dsenb	= m_priv->dsenb;
gfxtxt	= m_priv->gfxtxt;
p830	= m_priv->p830;
pkt0	= m_priv->pkt0;
req	= m_priv->req;
txtpre	= m_priv->txtpre;
vps	= m_priv->vps;
plfvbintf = m_priv->plfvbintf;
m_priv->Settxtplfhandle( m_priv);
m_priv->plfvbi = plfvbi;
dcu = m_priv->dcu;
txtpow = m_priv->pow;
m_priv->pen = pen;
}
CEuInstallerStub_mtxtstub::~CEuInstallerStub_mtxtstub()
{
 delete m_priv;
}

void CEuInstallerStub_mtxtstub::SetMwCoreInstance (CTvMwCore *Core)
{
	m_priv->SetMwCoreInstance(Core);
}

void CEuInstallerStub_mtxtstub::SetGfxhandle( IGfxANWabs* gfxhandle)
{
	m_priv->SetGfxhandle(gfxhandle);
}

#endif
