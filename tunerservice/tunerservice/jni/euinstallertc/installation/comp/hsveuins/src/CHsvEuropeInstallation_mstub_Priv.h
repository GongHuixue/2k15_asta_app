#ifndef  _CHSVEUROPEINSTALLATION_MSTUB_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MSTUB_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <ISvcCniData.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_mstub_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_mstub_Priv::
#include "locals_mstub.h"

class CHsvEuropeInstallation_mstub_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_mstub_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mstub.h"
#undef MEMBERVARS
//Provided interfaces
private:
ISvcCniDataImpl(CHsvEuropeInstallation_mstub_Priv,hsvprins_pgdatcni);
public:
ProvidesInterface<ISvcCniData>	hsvprins_pgdatcni;


public:
CHsvEuropeInstallation_mstub_Priv():i__hsvprins_pgdatcni(this)
{
hsvprins_pgdatcni	=	&i__hsvprins_pgdatcni;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define hsvprins_pgdatcni_InvalidPreset	ISvcCniData_InvalidPreset
#define hsvprins_pgdatcni_MinCNIPreset	i__hsvprins_pgdatcni.m_MinCNIPreset
#define hsvprins_pgdatcni_MaxCNIPreset	i__hsvprins_pgdatcni.m_MaxCNIPreset
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
#include "locals_mstub.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

