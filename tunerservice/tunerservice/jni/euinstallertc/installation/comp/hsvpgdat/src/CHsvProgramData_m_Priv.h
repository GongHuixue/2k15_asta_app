#ifndef  _CHSVPROGRAMDATA_M_PRIV_H
#define  _CHSVPROGRAMDATA_M_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <CTCMwBase.h>
class CHsvProgramData_m_Priv;
#define CLASSSCOPE CHsvProgramData_m_Priv::
#include "locals_m.h"

class CHsvProgramData_m_Priv : public CTCMwBase
{
public:
virtual ~CHsvProgramData_m_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CHsvProgramData_m_Priv,pow);
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	ipgdatpow;
RequiresInterface<IHsvPower>	ipgdbpow;

public:
CHsvProgramData_m_Priv():i__pow(this)
{
pow	=	&i__pow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define ipgdatpow_iPresent() (ipgdatpow.Present())
#define ipgdatpow_Init()	ipgdatpow->Init()
#define ipgdatpow_TurnOn()	ipgdatpow->TurnOn()
#define ipgdatpow_TurnOff()	ipgdatpow->TurnOff()
#define ipgdbpow_iPresent() (ipgdbpow.Present())
#define ipgdbpow_Init()	ipgdbpow->Init()
#define ipgdbpow_TurnOn()	ipgdbpow->TurnOn()
#define ipgdbpow_TurnOff()	ipgdbpow->TurnOff()
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
#include "locals_m.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

