#ifndef HSVDVBSDM_MSTRAPI
#define HSVDVBSDM_MSTRAPI

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbStreamingDataManager_mstrapi.h"
#include "CHsvDvbStreamingDataManager_mstrapi_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbStreamingDataManager_mstrapi_Priv::params__init(void)
{
}
CHsvDvbStreamingDataManager_mstrapi_Priv::~CHsvDvbStreamingDataManager_mstrapi_Priv()
{
}
//public class connections
CHsvDvbStreamingDataManager_mstrapi::CHsvDvbStreamingDataManager_mstrapi()
{
 m_priv = new CHsvDvbStreamingDataManager_mstrapi_Priv();
hsvdvbcamsdm_strapiN	= m_priv->hsvdvbcamsdm_strapiN;
hsvdvbsi_strapiN	= m_priv->hsvdvbsi_strapiN;
hsvmpeg_strapiN	= m_priv->hsvmpeg_strapiN;
istrapi	= m_priv->istrapi;
m_priv->icamnitstrapi	=icamnitstrapi;
m_priv->ieitstrapi	=ieitstrapi;
m_priv->ilclstrapi	=ilclstrapi;
m_priv->initstrapi	=initstrapi;
m_priv->ipatstrapi	=ipatstrapi;
m_priv->ipmtstrapi	=ipmtstrapi;
m_priv->isdtstrapi	=isdtstrapi;
m_priv->itdtstrapi	=itdtstrapi;
m_priv->itotstrapi	=itotstrapi;
m_priv->strapiN	=strapiN;
}
CHsvDvbStreamingDataManager_mstrapi::~CHsvDvbStreamingDataManager_mstrapi()
{
 delete m_priv;
}
#endif
