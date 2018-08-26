#ifndef HSVUTIL_MHUFFDEC
#define HSVUTIL_MHUFFDEC

#define GENERATE__LEGACY__DEFINES

#include "../CHsvUtil_mhuffdec.h"
#include "CHsvUtil_mhuffdec_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvUtil_mhuffdec_Priv::params__init(void)
{
}
CHsvUtil_mhuffdec_Priv::~CHsvUtil_mhuffdec_Priv()
{
}
//public class connections
CHsvUtil_mhuffdec::CHsvUtil_mhuffdec()
{
 m_priv = new CHsvUtil_mhuffdec_Priv();
istringdec	= m_priv->istringdec;
}
CHsvUtil_mhuffdec::~CHsvUtil_mhuffdec()
{
 delete m_priv;
}
#endif
