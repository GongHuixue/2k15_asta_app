#ifndef EUINSSTUB_MDUMMY
#define EUINSSTUB_MDUMMY

#define GENERATE__LEGACY__DEFINES

#include "../CEuInstallerStub_mdummy.h"
#include "CEuInstallerStub_mdummy_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CEuInstallerStub_mdummy_Priv::params__init(void)
{
	//Added functions in the dummy cpp file
//	sdmdiv_SdmWaitTime = 50000;
	//sdmdiv_DataCollectionTimeout = sdmdiv_SdmWaitTime;
	eurdiv_ChannelNameLength = 41;// Increased channel name length to 41 CR:AN-81540
	eurdiv_PresetNameLength = 41;// Increased channel name length to 41 CR:AN-81540
	//insdiv_PresetNameLength = 23;
	eurdiv_MaxLCNValue = 1000;
	insdiv_MaxLCNValue = 1000;
	insdiv_SearchForTvSystemInInstallation = TRUE;
	insdiv_SearchForColorSystemInInstallation = FALSE;
	insdiv_AttenuatorDetectionInInstall = FALSE;
	insdiv_SortPresetsInAutoStoreModeNone = FALSE;
	insdiv_ImmediateStoreInAutoInstall = FALSE;
	insdiv_NotInstall = 0;
	insdiv_Install = 1;
	insdiv_Hide = 2;
	
	insdiv_CurrentCountryInvalidLCNSortKey1 = insdiv_KeyOriginalNetworkId;
	insdiv_CurrentCountryInvalidLCNSortKey2 = insdiv_KeyServiceType;
	insdiv_CurrentCountryInvalidLCNSortKey3 = insdiv_KeyLCN;
	insdiv_CurrentCountryInvalidLCNSortKey4 = insdiv_KeyServiceName;
	insdiv_CurrentCountryInvalidLCNSortKey5 = insdiv_KeyServiceId; 
}
CEuInstallerStub_mdummy_Priv::~CEuInstallerStub_mdummy_Priv()
{
}
//public class connections
CEuInstallerStub_mdummy::CEuInstallerStub_mdummy()
{
 m_priv = new CEuInstallerStub_mdummy_Priv();
Timerclk	= m_priv->Timerclk;
actl	= m_priv->actl;
apperr	= m_priv->apperr;
apsysset	= m_priv->apsysset;
chanlibret	= m_priv->chanlibret;
chdec2	= m_priv->chdec2;
chdecdvbt2	= m_priv->chdecdvbt2;
cids	= m_priv->cids;
cityids	= m_priv->cityids;
col	= m_priv->col;
ctrlpen	= m_priv->ctrlpen;
decsel	= m_priv->decsel;
destconfig	= m_priv->destconfig;
div	= m_priv->div;
dmxsecfN	= m_priv->dmxsecfN;
dt	= m_priv->dt;
dvbsrtdbids	= m_priv->dvbsrtdbids;
err	= m_priv->err;
eurdiv	= m_priv->eurdiv;
feassmx	= m_priv->feassmx;
fechandecdvbc	= m_priv->fechandecdvbc;
fechandecdvbtx	= m_priv->fechandecdvbtx;
fechandecx	= m_priv->fechandecx;
feqssmx	= m_priv->feqssmx;
fetunx	= m_priv->fetunx;
fevssmx	= m_priv->fevssmx;
ffsdir	= m_priv->ffsdir;
hpool	= m_priv->hpool;
hsvdmxN	= m_priv->hsvdmxN;
insN	= m_priv->insN;
insdiv	= m_priv->insdiv;
inserr	= m_priv->inserr;
instlaN	= m_priv->instlaN;
log	= m_priv->log;
mctl	= m_priv->mctl;
mem	= m_priv->mem;
memo	= m_priv->memo;
mpegN	= m_priv->mpegN;
mpegsecnN	= m_priv->mpegsecnN;
mpldiv	= m_priv->mpldiv;
nvmapps	= m_priv->nvmapps;
nvmcesvc	= m_priv->nvmcesvc;
nvmids	= m_priv->nvmids;
nvmpa	= m_priv->nvmpa;
nvmtxt	= m_priv->nvmtxt;
pen	= m_priv->pen;
pgctl	= m_priv->pgctl;
pgctl3	= m_priv->pgctl3;
pgdat	= m_priv->pgdat;
pgdatN	= m_priv->pgdatN;
pgdatNxx	= m_priv->pgdatNxx;
pgdatNxxx	= m_priv->pgdatNxxx;
pgdatrtk	= m_priv->pgdatrtk;
pgdiv	= m_priv->pgdiv;
pgitr	= m_priv->pgitr;
pgsel	= m_priv->pgsel;
plfdesigid	= m_priv->plfdesigid;
plfdmx	= m_priv->plfdmx;
plferrids	= m_priv->plferrids;
plfres	= m_priv->plfres;
plfsrcid	= m_priv->plfsrcid;
pmp	= m_priv->pmp;
pool	= m_priv->pool;
poolids	= m_priv->poolids;
powctlx	= m_priv->powctlx;
rtk	= m_priv->rtk;
sdmdiv	= m_priv->sdmdiv;
srcstp	= m_priv->srcstp;
srtdb2	= m_priv->srtdb2;
srtdbids	= m_priv->srtdbids;
str	= m_priv->str;
strmfltrN	= m_priv->strmfltrN;
subid	= m_priv->subid;
sync	= m_priv->sync;
sysset	= m_priv->sysset;
sysset5	= m_priv->sysset5;
syssetx	= m_priv->syssetx;
tmr	= m_priv->tmr;
tprtk	= m_priv->tprtk;
vctl	= m_priv->vctl;
vip	= m_priv->vip;
wnddestmap	= m_priv->wnddestmap;
m_priv->ins	=ins;
m_priv->tvcoresettings = tvcoresettings;
m_priv->globalSettings = globalSettings;
m_priv->plfav	= plfav;
m_priv->plfApiTsDmx = plfApiTsDmx;
}
CEuInstallerStub_mdummy::~CEuInstallerStub_mdummy()
{
 delete m_priv;
}
#endif
