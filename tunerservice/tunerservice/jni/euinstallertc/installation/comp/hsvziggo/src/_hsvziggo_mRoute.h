#ifndef HSVZIGGO_MROUTE
#define HSVZIGGO_MROUTE

#define GENERATE__LEGACY__DEFINES

#include "../CHsvZiggoInstallation_mRoute.h"
#include "CHsvZiggoInstallation_mRoute_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvZiggoInstallation_mRoute_Priv::params__init(void)
{
}
CHsvZiggoInstallation_mRoute_Priv::~CHsvZiggoInstallation_mRoute_Priv()
{
}
//public class connections
CHsvZiggoInstallation_mRoute::CHsvZiggoInstallation_mRoute()
{
 m_priv = new CHsvZiggoInstallation_mRoute_Priv();
ctrlN	= m_priv->ctrlN;
feapiN	= m_priv->feapiN;
ins	= m_priv->ins;
istub	= m_priv->istub;
pow	= m_priv->pow;
m_priv->ibckg	=ibckg;
m_priv->ibckgctrlN	=ibckgctrlN;
m_priv->ibckgpow	=ibckgpow;
m_priv->idtr	=idtr;
m_priv->idtrfeapiN	=idtrfeapiN;
m_priv->idtrpow	=idtrpow;
m_priv->iins	=iins;
m_priv->iinsctrlN	=iinsctrlN;
m_priv->iinsfeapiN	=iinsfeapiN;
m_priv->iinspow	=iinspow;
m_priv->ipreins	=ipreins;
m_priv->ipreinsctrlN	=ipreinsctrlN;
m_priv->ipreinsfeapiN	=ipreinsfeapiN;
m_priv->ipreinspow	=ipreinspow;
m_priv->rins	=rins;
}
CHsvZiggoInstallation_mRoute::~CHsvZiggoInstallation_mRoute()
{
 delete m_priv;
}
#endif
