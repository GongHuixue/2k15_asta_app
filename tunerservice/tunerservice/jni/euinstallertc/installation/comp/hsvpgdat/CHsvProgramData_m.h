#ifndef  _CHSVPROGRAMDATA_M_H
#define  _CHSVPROGRAMDATA_M_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
class CHsvProgramData_m_Priv;
class CHsvProgramData_m
{
public:
ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvPower>	ipgdatpow;
RequiresInterface<IHsvPower>	ipgdbpow;
public:
CHsvProgramData_m();
virtual ~CHsvProgramData_m();
private:
CHsvProgramData_m_Priv	*m_priv;
};

#endif

