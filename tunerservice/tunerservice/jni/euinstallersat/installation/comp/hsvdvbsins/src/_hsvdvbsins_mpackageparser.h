#ifndef HSVDVBSINS_MPACKAGEPARSER
#define HSVDVBSINS_MPACKAGEPARSER

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_mpackageparser.h"
#include "CHsvDvbsInstallation_mpackageparser_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_mpackageparser_Priv::params__init(void)
{
}
CHsvDvbsInstallation_mpackageparser_Priv::~CHsvDvbsInstallation_mpackageparser_Priv()
{
}
//public class connections
CHsvDvbsInstallation_mpackageparser::CHsvDvbsInstallation_mpackageparser()
{
 m_priv = new CHsvDvbsInstallation_mpackageparser_Priv();
impackagepow	= m_priv->impackagepow;
ipackage	= m_priv->ipackage;
ipackageparserctrlN	= m_priv->ipackageparserctrlN;
ipackageparsersatfrontendN	= m_priv->ipackageparsersatfrontendN;
opinsN	=	m_priv->opinsN;
cipStatusN	=	m_priv->cipStatusN;
m_priv->apsysset	=apsysset;
m_priv->charsetutil	=charsetutil;
m_priv->cids	=cids;
m_priv->ctrl	=ctrl;
m_priv->err	=err;
m_priv->iinsN	=iinsN;
m_priv->iprescanparser	=iprescanparser;
m_priv->lngids	=lngids;
m_priv->pen	=pen;
m_priv->pgdb	=pgdb;
m_priv->pgdbconst	=pgdbconst;
m_priv->pmp	=pmp;
m_priv->satfeapi	=satfeapi;
m_priv->strapi	=strapi;
m_priv->sysset	=sysset;
m_priv->opins	=opins;
m_priv->cipStatus =cipStatus;
m_priv->dvbset = dvbset;
}
CHsvDvbsInstallation_mpackageparser::~CHsvDvbsInstallation_mpackageparser()
{
 delete m_priv;
}
#endif
