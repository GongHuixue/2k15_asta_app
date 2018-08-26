#ifndef IHSVDIGITALSCANSDSDDATA_H
#define IHSVDIGITALSCANSDSDDATA_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalScanSdsdData
{
public:
	virtual ~IHsvDigitalScanSdsdData(){}
	virtual int GetSDSDData(void * data)= 0;
	virtual int GetHomingData(void * data)= 0;
};


#define IHsvDigitalScanSdsdDataImpl(Comp,intf)    \
virtual int intf ## _GetSDSDData(void * data);\
virtual int intf ## _GetHomingData(void * data);\
class Comp ## _ ## intf : public IHsvDigitalScanSdsdData \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetSDSDData(void * data){ return m_parent->intf ## _GetSDSDData(data);}\
virtual int GetHomingData(void * data){ return m_parent->intf ## _GetHomingData(data);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
