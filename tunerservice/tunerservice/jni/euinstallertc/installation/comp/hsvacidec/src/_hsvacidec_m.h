#ifndef HSVACIDEC_M
#define HSVACIDEC_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvAciDecode.h"
#include "CHsvAciDecode_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvAciDecode_Priv::params__init(void)
{
}
CHsvAciDecode_Priv::~CHsvAciDecode_Priv()
{
}
//public class connections
CHsvAciDecode::CHsvAciDecode()
{
 m_priv = new CHsvAciDecode_Priv();
acidec	= m_priv->acidec;
cnvN	= m_priv->cnvN;
pow	= m_priv->pow;
m_priv->acc	=acc;
m_priv->acidecN	=acidecN;
m_priv->acinv	=acinv;
m_priv->cnv	=cnv;
m_priv->col	=col;
m_priv->dec	=dec;
m_priv->div	=div;
m_priv->dsdrv	=dsdrv;
m_priv->dsenb	=dsenb;
m_priv->euconfig	=euconfig;
m_priv->pen	=pen;
m_priv->pkt0	=pkt0;
m_priv->pmp	=pmp;
m_priv->req	=req;
m_priv->str	=str;
m_priv->Setacipagehandle( m_priv);
}
CHsvAciDecode::~CHsvAciDecode()
{
 delete m_priv;
}
#endif
