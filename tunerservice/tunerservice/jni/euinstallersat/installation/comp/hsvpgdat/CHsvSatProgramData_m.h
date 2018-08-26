#ifndef  _CHSVSATPROGRAMDATA_M_H
#define  _CHSVSATPROGRAMDATA_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
class CHsvSatProgramData_m_Priv;
class CHsvSatProgramData_m
{
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	ipgdatpow;
RequiresInterface<IHsvPower>	ipgdbpow;
public:
CHsvSatProgramData_m();
virtual ~CHsvSatProgramData_m();
private:
CHsvSatProgramData_m_Priv	*m_priv;
};

#endif

