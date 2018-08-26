#ifndef HSVFE_M
#define HSVFE_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvFrontEnd.h"
#include "CHsvFrontEnd_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvFrontEnd_Priv::params__init(void)
{
}
CHsvFrontEnd_Priv::~CHsvFrontEnd_Priv()
{
}
//public class connections
CHsvFrontEnd::CHsvFrontEnd()
{
 m_priv = new CHsvFrontEnd_Priv();
assmN	= m_priv->assmN;
chdec2N	= m_priv->chdec2N;
chdecN	= m_priv->chdecN;
feapi	= m_priv->feapi;
fetunN	= m_priv->fetunN;
pow	= m_priv->pow;
qssmN	= m_priv->qssmN;
vssmN	= m_priv->vssmN;
m_priv->assm	=assm;
m_priv->chdec	=chdec;
m_priv->chdecC	=chdecC;
m_priv->chdecT	=chdecT;
m_priv->feapiN	=feapiN;
m_priv->fetun	=fetun;
m_priv->plferrids	=plferrids;
m_priv->qssm	=qssm;
m_priv->vssm	=vssm;
}
CHsvFrontEnd::~CHsvFrontEnd()
{
 delete m_priv;
}
#endif
