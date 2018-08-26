#ifndef HSVDVBSI_MTAB
#define HSVDVBSI_MTAB

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbSiDataManager_mtab.h"
#include "CHsvDvbSiDataManager_mtab_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbSiDataManager_mtab_Priv::params__init(void)
{
}
CHsvDvbSiDataManager_mtab_Priv::~CHsvDvbSiDataManager_mtab_Priv()
{
}
//public class connections
CHsvDvbSiDataManager_mtab::CHsvDvbSiDataManager_mtab()
{
 m_priv = new CHsvDvbSiDataManager_mtab_Priv();
}
CHsvDvbSiDataManager_mtab::~CHsvDvbSiDataManager_mtab()
{
 delete m_priv;
}
#endif
