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
m_priv->chsvdvbbat_dmxsecfN	=chsvdvbbat_dmxsecfN;
m_priv->chsvdvbbat_ena	=chsvdvbbat_ena;
m_priv->chsvdvbbat_pow	=chsvdvbbat_pow;
m_priv->chsvdvbfnt_dmxsecfN	=chsvdvbfnt_dmxsecfN;
m_priv->chsvdvbfnt_ena	=chsvdvbfnt_ena;
m_priv->chsvdvbfnt_pow	=chsvdvbfnt_pow;
m_priv->chsvdvbfnt_strmfltr	=chsvdvbfnt_strmfltr;
m_priv->chsvdvbfst_dmxsecfN	=chsvdvbfst_dmxsecfN;
m_priv->chsvdvbfst_ena	=chsvdvbfst_ena;
m_priv->chsvdvbfst_pow	=chsvdvbfst_pow;
m_priv->chsvdvbfst_strmfltr	=chsvdvbfst_strmfltr;
m_priv->chsvdvbnit_dmxsecfN	=chsvdvbnit_dmxsecfN;
m_priv->chsvdvbnit_ena	=chsvdvbnit_ena;
m_priv->chsvdvbnit_pow	=chsvdvbnit_pow;
m_priv->chsvdvbnit_strmfltr	=chsvdvbnit_strmfltr;
m_priv->chsvdvbsdt_dmxsecfN	=chsvdvbsdt_dmxsecfN;
m_priv->chsvdvbsdt_ena	=chsvdvbsdt_ena;
m_priv->chsvdvbsdt_pow	=chsvdvbsdt_pow;
m_priv->chsvdvbsdt_strmfltr	=chsvdvbsdt_strmfltr;
m_priv->chsvdvbpostcode_dmxsecfN	=chsvdvbpostcode_dmxsecfN;
m_priv->chsvdvbpostcode_ena	=chsvdvbpostcode_ena;
m_priv->chsvdvbpostcode_pow	=chsvdvbpostcode_pow;
m_priv->chsvdvbpostcode_strmfltr	=chsvdvbpostcode_strmfltr;
m_priv->chsvdvbcamnit_ena	=chsvdvbcamnit_ena;
m_priv->chsvdvbcamnit_pow	=chsvdvbcamnit_pow;
m_priv->chsvdvbcamnit_strmfltr	=chsvdvbcamnit_strmfltr;
m_priv->chsvdvbtot_dmxsecfN	=chsvdvbtot_dmxsecfN;
m_priv->chsvdvbtot_ena	=chsvdvbtot_ena;
m_priv->chsvdvbtot_pow	=chsvdvbtot_pow;
m_priv->sec	=sec;
m_priv->chsvdvbsgt_dmxsecfN	=chsvdvbsgt_dmxsecfN;
m_priv->chsvdvbsgt_ena	=chsvdvbsgt_ena;
m_priv->chsvdvbsgt_pow	=chsvdvbsgt_pow;
m_priv->chsvdvbsgt_strmfltr	=chsvdvbsgt_strmfltr;
}
CHsvDvbSiDataManager_m::~CHsvDvbSiDataManager_m()
{
 delete m_priv;
}
#endif
