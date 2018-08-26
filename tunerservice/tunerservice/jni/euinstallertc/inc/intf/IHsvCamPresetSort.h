#ifndef IHSVCAMPRESETSORT_H
#define IHSVCAMPRESETSORT_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCamPresetSort
{
public:
	virtual ~IHsvCamPresetSort(){}
	virtual void Initialise(void)= 0;
	virtual void Sort(void)= 0;
	virtual void UpdateDigitalPreset(HsvPgdatDigServiceData * psvcdat)= 0;
};


#define IHsvCamPresetSortImpl(Comp,intf)    \
virtual void intf ## _Initialise(void);\
virtual void intf ## _Sort(void);\
virtual void intf ## _UpdateDigitalPreset(HsvPgdatDigServiceData * psvcdat);\
class Comp ## _ ## intf : public IHsvCamPresetSort \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Initialise(void){ return m_parent->intf ## _Initialise();}\
virtual void Sort(void){ return m_parent->intf ## _Sort();}\
virtual void UpdateDigitalPreset(HsvPgdatDigServiceData * psvcdat){ return m_parent->intf ## _UpdateDigitalPreset(psvcdat);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
