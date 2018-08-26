#ifndef HSVDVBSI_M
#define HSVDVBSI_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbSiDataManager_m.h"
#include "CHsvDvbSiDataManager_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbSiDataManager_m_Priv::params__init(void)
{
}
CHsvDvbSiDataManager_m_Priv::~CHsvDvbSiDataManager_m_Priv()
{
}
//public class connections
CHsvDvbSiDataManager_m::CHsvDvbSiDataManager_m()
{
 m_priv = new CHsvDvbSiDataManager_m_Priv();
dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
pow	= m_priv->pow;
strmfltr	= m_priv->strmfltr;
m_priv->chsvdvbeit_dmxsecfN	=chsvdvbeit_dmxsecfN;
m_priv->chsvdvbeit_ena	=chsvdvbeit_ena;
m_priv->chsvdvbeit_pow	=chsvdvbeit_pow;
m_priv->chsvdvbeit_strmfltr	=chsvdvbeit_strmfltr;
m_priv->chsvdvbnit_dmxsecfN	=chsvdvbnit_dmxsecfN;
m_priv->chsvdvbnit_ena	=chsvdvbnit_ena;
m_priv->chsvdvbnit_pow	=chsvdvbnit_pow;
m_priv->chsvdvbnit_strmfltr	=chsvdvbnit_strmfltr;
m_priv->chsvdvbsdt_dmxsecfN	=chsvdvbsdt_dmxsecfN;
m_priv->chsvdvbsdt_ena	=chsvdvbsdt_ena;
m_priv->chsvdvbsdt_pow	=chsvdvbsdt_pow;
m_priv->chsvdvbsdt_strmfltr	=chsvdvbsdt_strmfltr;
m_priv->chsvdvbtdt_dmxsecfN	=chsvdvbtdt_dmxsecfN;
m_priv->chsvdvbtdt_ena	=chsvdvbtdt_ena;
m_priv->chsvdvbtdt_pow	=chsvdvbtdt_pow;
m_priv->chsvdvbtot_dmxsecfN	=chsvdvbtot_dmxsecfN;
m_priv->chsvdvbtot_ena	=chsvdvbtot_ena;
m_priv->chsvdvbtot_pow	=chsvdvbtot_pow;
}
CHsvDvbSiDataManager_m::~CHsvDvbSiDataManager_m()
{
 delete m_priv;
}
#endif
