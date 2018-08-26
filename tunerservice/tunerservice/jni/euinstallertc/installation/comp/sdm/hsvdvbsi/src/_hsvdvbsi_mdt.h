#ifndef HSVDVBSI_MDT
#define HSVDVBSI_MDT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbSiDataManager_mdt.h"
#include "CHsvDvbSiDataManager_mdt_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbSiDataManager_mdt_Priv::params__init(void)
{
}
CHsvDvbSiDataManager_mdt_Priv::~CHsvDvbSiDataManager_mdt_Priv()
{
}
//public class connections
CHsvDvbSiDataManager_mdt::CHsvDvbSiDataManager_mdt()
{
 m_priv = new CHsvDvbSiDataManager_mdt_Priv();
idtconv	= m_priv->idtconv;
m_priv->dt	=dt;
}
CHsvDvbSiDataManager_mdt::~CHsvDvbSiDataManager_mdt()
{
 delete m_priv;
}
#endif
