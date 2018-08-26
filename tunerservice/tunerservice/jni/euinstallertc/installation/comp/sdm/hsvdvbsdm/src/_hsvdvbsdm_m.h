#ifndef HSVDVBSDM_M
#define HSVDVBSDM_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbStreamingDataManager_m.h"
#include "CHsvDvbStreamingDataManager_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbStreamingDataManager_m_Priv::params__init(void)
{
}
CHsvDvbStreamingDataManager_m_Priv::~CHsvDvbStreamingDataManager_m_Priv()
{
}
//public class connections
CHsvDvbStreamingDataManager_m::CHsvDvbStreamingDataManager_m()
{
 m_priv = new CHsvDvbStreamingDataManager_m_Priv();
conf	= m_priv->conf;
ctrl	= m_priv->ctrl;
dmxsecfN	= m_priv->dmxsecfN;
hsvdmxN	= m_priv->hsvdmxN;
hsvdvbsi_ctrlN	= m_priv->hsvdvbsi_ctrlN;
hsvdvbsi_dvbsvc	= m_priv->hsvdvbsi_dvbsvc;
hsvmpeg_mpegsecnN	= m_priv->hsvmpeg_mpegsecnN;
ilclstrapi	= m_priv->ilclstrapi;
pow	= m_priv->pow;
strmfltr	= m_priv->strmfltr;
m_priv->cids	=cids;
m_priv->ctrlN	=ctrlN;
m_priv->ctrlpen	=ctrlpen;
m_priv->div	=div;
m_priv->dmxena	=dmxena;
m_priv->dmxpow	=dmxpow;
m_priv->eurdiv	=eurdiv;
m_priv->hsvdvbcamsdm_pow	=hsvdvbcamsdm_pow;
m_priv->hsvdvbcamsdm_strmfltr	=hsvdvbcamsdm_strmfltr;
m_priv->hsvdvbsi_dmxsecfN	=hsvdvbsi_dmxsecfN;
m_priv->hsvdvbsi_ena	=hsvdvbsi_ena;
m_priv->hsvdvbsi_pow	=hsvdvbsi_pow;
m_priv->hsvdvbsi_strmfltr	=hsvdvbsi_strmfltr;
m_priv->hsvmpeg_enable	=hsvmpeg_enable;
m_priv->hsvmpeg_mpegsecn	=hsvmpeg_mpegsecn;
m_priv->hsvmpeg_pow	=hsvmpeg_pow;
m_priv->ins	=ins;
m_priv->istrapi	=istrapi;
m_priv->mpegsecnN	=mpegsecnN;
m_priv->pen	=pen;
m_priv->pmp	=pmp;
m_priv->secfltr	=secfltr;
m_priv->strmfltrN	=strmfltrN;
m_priv->sysset	=sysset;
}
CHsvDvbStreamingDataManager_m::~CHsvDvbStreamingDataManager_m()
{
 delete m_priv;
}
#endif
