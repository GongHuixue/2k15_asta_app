#ifndef  _CHSVDVBSDIGITURK_MPOW_PRIV_H
#define  _CHSVDVBSDIGITURK_MPOW_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <CS2MwBase.h>
class CHsvDvbsDigiTurk_mPow_Priv;
#define CLASSSCOPE CHsvDvbsDigiTurk_mPow_Priv::
#include "locals_mPow.h"

class CHsvDvbsDigiTurk_mPow_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbsDigiTurk_mPow_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mPow.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvPowerImpl(CHsvDvbsDigiTurk_mPow_Priv,pow);
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvPower>	iscanpow;
RequiresInterface<IHsvPower>	isortpow;

public:
CHsvDvbsDigiTurk_mPow_Priv():i__pow(this)
{
pow	=	&i__pow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define iacqpow_iPresent() (iacqpow.Present())
#define iacqpow_Init()	iacqpow->Init()
#define iacqpow_TurnOn()	iacqpow->TurnOn()
#define iacqpow_TurnOff()	iacqpow->TurnOff()
#define iscanpow_iPresent() (iscanpow.Present())
#define iscanpow_Init()	iscanpow->Init()
#define iscanpow_TurnOn()	iscanpow->TurnOn()
#define iscanpow_TurnOff()	iscanpow->TurnOff()
#define isortpow_iPresent() (isortpow.Present())
#define isortpow_Init()	isortpow->Init()
#define isortpow_TurnOn()	isortpow->TurnOn()
#define isortpow_TurnOff()	isortpow->TurnOff()
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
#include "locals_mPow.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

