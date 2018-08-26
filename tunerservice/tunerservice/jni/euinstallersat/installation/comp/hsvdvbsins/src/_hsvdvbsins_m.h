#ifndef HSVDVBSINS_M
#define HSVDVBSINS_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_m.h"
#include "CHsvDvbsInstallation_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_m_Priv::params__init(void)
{
}
CHsvDvbsInstallation_m_Priv::~CHsvDvbsInstallation_m_Priv()
{
}
//public class connections
CHsvDvbsInstallation_m::CHsvDvbsInstallation_m()
{
 m_priv = new CHsvDvbsInstallation_m_Priv();
ctrlN	= m_priv->ctrlN;
iinsN	= m_priv->iinsN;
iminiprescanN	= m_priv->iminiprescanN;
insconst	= m_priv->insconst;
ipow	= m_priv->ipow;
isyssetN	= m_priv->isyssetN;
pins	= m_priv->pins;
satfeapiN	= m_priv->satfeapiN;
strapiN	= m_priv->strapiN;
opinsN	= m_priv->opinsN;
cipStatusN	= m_priv->cipStatusN;
m_priv->actl3	=actl3;
m_priv->charsetutil	=charsetutil;
m_priv->cids	=cids;
m_priv->ctrl	=ctrl;
m_priv->err	=err;
m_priv->hsvdvbsgeneric_ctrlN	=hsvdvbsgeneric_ctrlN;
m_priv->hsvdvbsgeneric_ins	=hsvdvbsgeneric_ins;
m_priv->hsvdvbsgeneric_plfApidvbsN	=hsvdvbsgeneric_plfApidvbsN;
m_priv->iaddremove	=iaddremove;
m_priv->ibckInstall	=ibckInstall;
m_priv->ibckctrlN	=ibckctrlN;
m_priv->idvbset	=idvbset;
m_priv->iminiprescan	=iminiprescan;
m_priv->iminiprescanctrlN	=iminiprescanctrlN;
m_priv->iminiprescansatfrontendN	=iminiprescansatfrontendN;
m_priv->insN	=insN;
m_priv->ipackage	=ipackage;
m_priv->ipackagectrlN	=ipackagectrlN;
m_priv->ipackageins	=ipackageins;
m_priv->ipackageparserctrlN	=ipackageparserctrlN;
m_priv->ipackageparsersatfrontendN	=ipackageparsersatfrontendN;
m_priv->ipackageplfApidvbsN	=ipackageplfApidvbsN;
m_priv->ipackagesort	=ipackagesort;
m_priv->ipredefcopy	=ipredefcopy;
m_priv->iprescan	=iprescan;
m_priv->isatipprescan	=isatipprescan;
m_priv->iprescanctrlN	=iprescanctrlN;
m_priv->iprescanparser	=iprescanparser;
m_priv->iprescansatfrontendN	=iprescansatfrontendN;
m_priv->isigstr	=isigstr;
m_priv->istrapiN	=istrapiN;
m_priv->iutil	=iutil;
m_priv->mctl	=mctl;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->s2div	=s2div;
m_priv->satfeapi	=satfeapi;
m_priv->sysset	=sysset;
m_priv->vctl	=vctl;
m_priv->wnddest	=wnddest;
m_priv->ipackageopinsN	=ipackageopinsN;
m_priv->ipackageparseropinsN	= ipackageparseropinsN;
m_priv->ipackageparsercipStatusN = ipackageparsercipStatusN;
m_priv->isatipprescanctrlN = isatipprescanctrlN;
m_priv->isatipprescansatfrontendN = isatipprescansatfrontendN;
m_priv->hsvdvbstricolor_plfApidvbsN = hsvdvbstricolor_plfApidvbsN;
m_priv->hsvdvbstricolor_ctrlN = hsvdvbstricolor_ctrlN;
}
CHsvDvbsInstallation_m::~CHsvDvbsInstallation_m()
{
 delete m_priv;
}
#endif
