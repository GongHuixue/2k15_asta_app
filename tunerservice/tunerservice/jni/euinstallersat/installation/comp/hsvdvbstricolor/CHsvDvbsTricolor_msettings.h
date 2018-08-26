#ifndef  _CHSVDVBSTRICOLOR_MSETTINGS_H
#define  _CHSVDVBSTRICOLOR_MSETTINGS_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvPower.h>
#include <IHsvErrorCodeEx.h>

class CHsvDvbsTricolor_msettings_Priv;
class CHsvDvbsTricolor_msettings
{
//Provided Interfaces
public:
	ProvidesInterface<IHsvSatelliteSettings>	idvbset;
	ProvidesInterface<IHsvPower>	idvbsetpow;
	
//Required Interfaces
public:

	RequiresInterface<IHsvErrorCodeEx>	err;

public:

CHsvDvbsTricolor_msettings();
virtual ~CHsvDvbsTricolor_msettings();
private:
CHsvDvbsTricolor_msettings_Priv	*m_priv;
};

#endif

