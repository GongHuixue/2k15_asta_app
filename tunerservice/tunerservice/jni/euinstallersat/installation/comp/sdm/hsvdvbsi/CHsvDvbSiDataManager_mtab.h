#ifndef  _CHSVDVBSIDATAMANAGER_MTAB_H
#define  _CHSVDVBSIDATAMANAGER_MTAB_H 

#include <InfraGlobals.h>
#include <provreq.h>
class CHsvDvbSiDataManager_mtab_Priv;
class CHsvDvbSiDataManager_mtab
{
public:
CHsvDvbSiDataManager_mtab();
virtual ~CHsvDvbSiDataManager_mtab();
private:
CHsvDvbSiDataManager_mtab_Priv	*m_priv;
};

#endif

