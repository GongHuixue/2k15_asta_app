#ifndef IHSVPROGRAMDATABASECONSTS_H
#define IHSVPROGRAMDATABASECONSTS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDatabaseConsts
{
public:
	virtual ~IHsvProgramDatabaseConsts(){}
	#define IHsvProgramDatabaseConsts_Satellite		((int)0x00010000 )
	#define IHsvProgramDatabaseConsts_TempSatellite		((int)0x00020000 )
	#define IHsvProgramDatabaseConsts_SatInfo		((int)0x00000001 )
	#define IHsvProgramDatabaseConsts_DigitalTS		((int)0x00000002 )
	#define IHsvProgramDatabaseConsts_DigitalService		((int)0x00000004 )
	#define IHsvProgramDatabaseConsts_Preset		((int)0x00000008 )
};


#define IHsvProgramDatabaseConstsImpl(Comp,intf)    \
class Comp ## _ ## intf : public IHsvProgramDatabaseConsts \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
};\
Comp ## _ ## intf i__ ## intf;


#endif
