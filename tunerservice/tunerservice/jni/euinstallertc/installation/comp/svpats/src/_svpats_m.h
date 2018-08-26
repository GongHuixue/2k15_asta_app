#ifndef SVPATS_M
#define SVPATS_M

#define GENERATE__LEGACY__DEFINES

#include "../CSvcPats.h"
#include "CSvcPats_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CSvcPats_Priv::params__init(void)
{
}
CSvcPats_Priv::~CSvcPats_Priv()
{
}
//public class connections
CSvcPats::CSvcPats()
{
 m_priv = new CSvcPats_Priv();
cniname	= m_priv->cniname;
prsort	= m_priv->prsort;
m_priv->countid	=countid;
m_priv->div	=div;
m_priv->langid	=langid;
m_priv->mem	=mem;
m_priv->memo	=memo;
m_priv->str	=str;
m_priv->sysset	=sysset;
}
CSvcPats::~CSvcPats()
{
 delete m_priv;
}
#endif
