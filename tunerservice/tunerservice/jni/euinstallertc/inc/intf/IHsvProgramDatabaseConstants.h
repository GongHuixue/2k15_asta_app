#ifndef IHSVPROGRAMDATABASECONSTANTS_H
#define IHSVPROGRAMDATABASECONSTANTS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDatabaseConstants
{
public:
	virtual ~IHsvProgramDatabaseConstants(){}
	#define IHsvProgramDatabaseConstants_Antenna		((int)0x00010000 )
	#define IHsvProgramDatabaseConstants_Cable		((int)0x00020000 )
	#define IHsvProgramDatabaseConstants_TempAntenna		((int)0x00040000 )
	#define IHsvProgramDatabaseConstants_TempCable		((int)0x00080000 )
	#define IHsvProgramDatabaseConstants_Satellite		((int)0x00100000 )
	#define IHsvProgramDatabaseConstants_TempSatellite		((int)0x00200000 )
	#define IHsvProgramDatabaseConstants_Analog		((int)0x00000001 )
	#define IHsvProgramDatabaseConstants_DigitalTS		((int)0x00000002 )
	#define IHsvProgramDatabaseConstants_DigitalService		((int)0x00000004 )
	#define IHsvProgramDatabaseConstants_Preset		((int)0x00000008 )
	#define IHsvProgramDatabaseConstants_FrequencyMapTable		((int)0x00000010 )
	#define IHsvProgramDatabaseConstants_CurrentDigitalService		((int)0x00000020 )
	#define IHsvProgramDatabaseConstants_CurrentDigitalTS		((int)0x00000040 )
	#define IHsvProgramDatabaseConstants_CurrentAnalog		((int)0x00000080 )
	#define IHsvProgramDatabaseConstants_CurrentPreset		((int)0x00000100 )
	#define IHsvProgramDatabaseConstants_CurrentFrequencyMapTable		((int)0x00000200 )
	#define IHsvProgramDatabaseConstants_SatInfo		((int)0x00000400 )
	#define IHsvProgramDatabaseConstants_CurrentSatInfo		((int)0x00000800 )
};


#define IHsvProgramDatabaseConstantsImpl(Comp,intf)    \
class Comp ## _ ## intf : public IHsvProgramDatabaseConstants \
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
