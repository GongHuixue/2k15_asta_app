#ifndef HSVUTIL_GPIMWCHAR
#define HSVUTIL_GPIMWCHAR

#define GENERATE__LEGACY__DEFINES

#include "../CHsvUtil_gpimwchar.h"
#include "CHsvUtil_gpimwchar_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvUtil_gpimwchar_Priv::params__init(void)
{
}
CHsvUtil_gpimwchar_Priv::~CHsvUtil_gpimwchar_Priv()
{
}
//public class connections
CHsvUtil_gpimwchar::CHsvUtil_gpimwchar()
{
 m_priv = new CHsvUtil_gpimwchar_Priv();
ling	= m_priv->ling;
}
CHsvUtil_gpimwchar::~CHsvUtil_gpimwchar()
{
 delete m_priv;
}
#endif
