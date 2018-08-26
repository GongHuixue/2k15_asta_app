#ifndef  _CHSVDVBSIDATAMANAGER_MDT_H
#define  _CHSVDVBSIDATAMANAGER_MDT_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDateTimeConversion.h>
#include <IDateTime.h>
class CHsvDvbSiDataManager_mdt_Priv;
class CHsvDvbSiDataManager_mdt
{
public:
ProvidesInterface<IHsvDateTimeConversion>	idtconv;

//Required interfaces
public:
RequiresInterface<IDateTime>	dt;
public:
CHsvDvbSiDataManager_mdt();
virtual ~CHsvDvbSiDataManager_mdt();
private:
CHsvDvbSiDataManager_mdt_Priv	*m_priv;
};

#endif

