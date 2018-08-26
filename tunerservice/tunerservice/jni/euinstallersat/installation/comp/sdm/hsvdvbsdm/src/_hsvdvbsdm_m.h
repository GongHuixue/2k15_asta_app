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
hsvdvbsi_ctrlN	= m_priv->hsvdvbsi_ctrlN;
hsvdvbsi_dvbsvc	= m_priv->hsvdvbsi_dvbsvc;
hsvsimplempeg_ctrlN	= m_priv->hsvsimplempeg_ctrlN;
ictrl	= m_priv->ictrl;
ilclstrapi	= m_priv->ilclstrapi;
pdmxsecfN	= m_priv->pdmxsecfN;
phsvdmxN	= m_priv->phsvdmxN;
pow	= m_priv->pow;
strmfltr	= m_priv->strmfltr;
m_priv->cids	=cids;
m_priv->ctrlN	=ctrlN;
m_priv->ctrlpen	=ctrlpen;
m_priv->div	=div;
m_priv->dmxena	=dmxena;
m_priv->dmxsecfN	=dmxsecfN;
m_priv->eurdiv	=eurdiv;
m_priv->hsvdmxN	=hsvdmxN;
m_priv->hsvdvbsi_dmxsecfN	=hsvdvbsi_dmxsecfN;
m_priv->hsvdvbsi_ena	=hsvdvbsi_ena;
m_priv->hsvdvbsi_pow	=hsvdvbsi_pow;
m_priv->hsvdvbsi_strmfltr	=hsvdvbsi_strmfltr;
m_priv->hsvsimplempeg_enable	=hsvsimplempeg_enable;
m_priv->hsvsimplempeg_pow	=hsvsimplempeg_pow;
m_priv->ins	=ins;
m_priv->istrapi	=istrapi;
m_priv->pakgins	=pakgins;
m_priv->pen	=pen;
m_priv->pmp	=pmp;
m_priv->strmfltrN	=strmfltrN;
m_priv->sysset	=sysset;
}
CHsvDvbStreamingDataManager_m::~CHsvDvbStreamingDataManager_m()
{
 delete m_priv;
}
#endif
