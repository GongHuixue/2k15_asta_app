#ifndef HSVDVBSINS_MPRESCANPARSER
#define HSVDVBSINS_MPRESCANPARSER

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_mprescanparser.h"
#include "CHsvDvbsInstallation_mprescanparser_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_mprescanparser_Priv::params__init(void)
{
}
CHsvDvbsInstallation_mprescanparser_Priv::~CHsvDvbsInstallation_mprescanparser_Priv()
{
}
//public class connections
CHsvDvbsInstallation_mprescanparser::CHsvDvbsInstallation_mprescanparser()
{
 m_priv = new CHsvDvbsInstallation_mprescanparser_Priv();
iprescanparser	= m_priv->iprescanparser;
m_priv->charsetutil	=charsetutil;
m_priv->satfeapi	=satfeapi;
}
CHsvDvbsInstallation_mprescanparser::~CHsvDvbsInstallation_mprescanparser()
{
 delete m_priv;
}
#endif
