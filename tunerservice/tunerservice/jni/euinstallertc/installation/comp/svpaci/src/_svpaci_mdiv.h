#ifndef SVPACI_MDIV
#define SVPACI_MDIV

#define GENERATE__LEGACY__DEFINES

#include "../CSvcPaci_mdiv.h"
#include "CSvcPaci_mdiv_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CSvcPaci_mdiv_Priv::params__init(void)
{
}
CSvcPaci_mdiv_Priv::~CSvcPaci_mdiv_Priv()
{
}
//public class connections
CSvcPaci_mdiv::CSvcPaci_mdiv()
{
 m_priv = new CSvcPaci_mdiv_Priv();
adiv	= m_priv->adiv;
m_priv->div	=div;
}
CSvcPaci_mdiv::~CSvcPaci_mdiv()
{
 delete m_priv;
}
#endif
