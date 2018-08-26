#ifndef SATINSTALLERSTUB_MDUMMY
#define SATINSTALLERSTUB_MDUMMY

#define GENERATE__LEGACY__DEFINES

#include "../CS2InstallerStub.h"
#include "CS2InstallerStub_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CS2InstallerStub_Priv::params__init(void)
{
	div_SdmWaitTime = 15000;
	div_DataCollectionTimeout = div_SdmWaitTime;
	eurdiv_ChannelNameLength = 41;// Increased channel name length to 41 CR:AN-81540
	eurdiv_PresetNameLength = 41;// Increased channel name length to 41 CR:AN-81540
	div_ChannelNameLength = 41; // Increased channel name length to 41 CR:AN-81540
} 
CS2InstallerStub_Priv::~CS2InstallerStub_Priv()
{
}
//public class connections
CS2InstallerStub::CS2InstallerStub()
{
 m_priv = new CS2InstallerStub_Priv();
Timerclk	= m_priv->Timerclk;
actl3	= m_priv->actl3;
apperr	= m_priv->apperr;
apsysset	= m_priv->apsysset;
cids	= m_priv->cids;
compids	= m_priv->compids;
ctrlpen	= m_priv->ctrlpen;
div	= m_priv->div;
dvbsrtdbids	= m_priv->dvbsrtdbids;
err	= m_priv->err;
eurdiv	= m_priv->eurdiv;
lngids	= m_priv->lngids;
log	= m_priv->log;
mctl	= m_priv->mctl;
memo	= m_priv->memo;
mpldiv	= m_priv->mpldiv;
observer	= m_priv->observer;
pen	= m_priv->pen;
pgdaterr	= m_priv->pgdaterr;
pgdatrtk	= m_priv->pgdatrtk;
pgsel	= m_priv->pgsel;
plfdmx	= m_priv->plfdmx;
plfdvbs	= m_priv->plfdvbs;
plferrids	= m_priv->plferrids;
plfres	= m_priv->plfres;
plftune	= m_priv->plftune;
pmp	= m_priv->pmp;
pool	= m_priv->pool;
poolids	= m_priv->poolids;
qssm	= m_priv->qssm;
recdev	= m_priv->recdev;
rtk	= m_priv->rtk;
s2div	= m_priv->s2div;
srtdb2	= m_priv->srtdb2;
srtdbids	= m_priv->srtdbids;
str	= m_priv->str;
sync	= m_priv->sync;
sysset	= m_priv->sysset;
tprtk	= m_priv->tprtk;
usbms	= m_priv->usbms;
utildiv	= m_priv->utildiv;
vctl	= m_priv->vctl;
vssm	= m_priv->vssm;
wnddest	= m_priv->wnddest;
m_priv->tvcoresettings = tvcoresettings;
m_priv->dvbset = dvbset;
m_priv->globalsettings = globalsettings;
m_priv->plfApiTsDmx = plfApiTsDmx;

}
CS2InstallerStub::~CS2InstallerStub()
{
 delete m_priv;
}
#endif
