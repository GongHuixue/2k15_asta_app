#ifndef ICESPATSDIV_H
#define ICESPATSDIV_H
#include <intfparam.h>
#include <provreq.h>
class ICesPatsDiv
{
public:
	virtual ~ICesPatsDiv(){}
	#define ICesPatsDiv_PresetNameLength		((int)7 )
	#define ICesPatsDiv_MaxPresets		((int)200 )
	virtual char* GetDefaultPresetName(void)= 0;
};


#define ICesPatsDivImpl(Comp,intf)    \
virtual char* intf ## _GetDefaultPresetName(void);\
class Comp ## _ ## intf : public ICesPatsDiv \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent)\
    {\
        m_parent = parent;\
    }\
virtual char* GetDefaultPresetName(void){ return m_parent->intf ## _GetDefaultPresetName();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
