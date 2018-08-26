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
hsvdvbsi_strapiN	= m_priv->hsvdvbsi_strapiN;
hsvsimplempeg_strapiN	= m_priv->hsvsimplempeg_strapiN;
istrapi	= m_priv->istrapi;
m_priv->icamnitstrapi	=icamnitstrapi;
m_priv->ibatstrapi	=ibatstrapi;
m_priv->ifntstrapi	=ifntstrapi;
m_priv->ifststrapi	=ifststrapi;
m_priv->ilclstrapi	=ilclstrapi;
m_priv->initstrapi	=initstrapi;
m_priv->isdtstrapi	=isdtstrapi;
m_priv->isimplepatstrapi	=isimplepatstrapi;
m_priv->isimplepmtstrapi	=isimplepmtstrapi;
m_priv->icamnitstrapi	=icamnitstrapi;
m_priv->itotstrapi	=itotstrapi;
m_priv->strapiN	=strapiN;
m_priv->ipostcodestrapi = ipostcodestrapi;
m_priv->ins = ins;
m_priv->chsvdvbsdt_Freesatena = chsvdvbsdt_Freesatena;
m_priv->isgtstrapi	=isgtstrapi;
}
CHsvDvbStreamingDataManager_mstrapi::~CHsvDvbStreamingDataManager_mstrapi()
{
 delete m_priv;
}
#endif
