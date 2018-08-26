#ifndef HSVUTIL_MWCHAR
#define HSVUTIL_MWCHAR

#define GENERATE__LEGACY__DEFINES

#include "../CHsvUtil_mwchar.h"
#include "CHsvUtil_mwchar_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvUtil_mwchar_Priv::params__init(void)
{
}
CHsvUtil_mwchar_Priv::~CHsvUtil_mwchar_Priv()
{
}
//public class connections
CHsvUtil_mwchar::CHsvUtil_mwchar()
{
 m_priv = new CHsvUtil_mwchar_Priv();
charsetutil	= m_priv->charsetutil;
charsetutil2	= m_priv->charsetutil2;
m_priv->cids	=cids;
m_priv->div	=div;
m_priv->istringdec	=istringdec;
m_priv->ling	=ling;
m_priv->sysset	=sysset;
}
CHsvUtil_mwchar::~CHsvUtil_mwchar()
{
 delete m_priv;
}
#endif
