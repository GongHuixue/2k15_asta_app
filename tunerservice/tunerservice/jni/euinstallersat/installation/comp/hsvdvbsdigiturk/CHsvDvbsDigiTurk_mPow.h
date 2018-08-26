#ifndef  _CHSVDVBSDIGITURK_MPOW_H
#define  _CHSVDVBSDIGITURK_MPOW_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
class CHsvDvbsDigiTurk_mPow_Priv;
class CHsvDvbsDigiTurk_mPow
{
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	iacqpow;
RequiresInterface<IHsvPower>	iscanpow;
RequiresInterface<IHsvPower>	isortpow;
public:
CHsvDvbsDigiTurk_mPow();
virtual ~CHsvDvbsDigiTurk_mPow();
private:
CHsvDvbsDigiTurk_mPow_Priv	*m_priv;
};

#endif

