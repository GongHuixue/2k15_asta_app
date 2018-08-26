#ifndef  _CHSVDVBSIDATAMANAGER_MTAB_PRIV_H
#define  _CHSVDVBSIDATAMANAGER_MTAB_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CTCMwBase.h>
class CHsvDvbSiDataManager_mtab_Priv;
#define CLASSSCOPE CHsvDvbSiDataManager_mtab_Priv::
#include "locals_mtab.h"

class CHsvDvbSiDataManager_mtab_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbSiDataManager_mtab_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mtab.h"
#undef MEMBERVARS

public:
CHsvDvbSiDataManager_mtab_Priv()
{
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mtab.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

