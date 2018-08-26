#ifndef IHSVANALOGSETTINGS_H
#define IHSVANALOGSETTINGS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAnalogSettings
{
public:
	virtual ~IHsvAnalogSettings(){}
	virtual Bool IsTvSystemSupported(int instvsystem)= 0;
	virtual void SetTvSystem(int instvsystem)= 0;
	virtual int GetTvSystem(void)= 0;
	virtual Bool IsColorSystemSupported(int colorsystem)= 0;
	virtual void SetColorSystem(int colorsystem)= 0;
	virtual int GetColorSystem(void)= 0;
};


#define IHsvAnalogSettingsImpl(Comp,intf)    \
virtual Bool intf ## _IsTvSystemSupported(int instvsystem);\
virtual void intf ## _SetTvSystem(int instvsystem);\
virtual int intf ## _GetTvSystem(void);\
virtual Bool intf ## _IsColorSystemSupported(int colorsystem);\
virtual void intf ## _SetColorSystem(int colorsystem);\
virtual int intf ## _GetColorSystem(void);\
class Comp ## _ ## intf : public IHsvAnalogSettings \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool IsTvSystemSupported(int instvsystem){ return m_parent->intf ## _IsTvSystemSupported(instvsystem);}\
virtual void SetTvSystem(int instvsystem){ return m_parent->intf ## _SetTvSystem(instvsystem);}\
virtual int GetTvSystem(void){ return m_parent->intf ## _GetTvSystem();}\
virtual Bool IsColorSystemSupported(int colorsystem){ return m_parent->intf ## _IsColorSystemSupported(colorsystem);}\
virtual void SetColorSystem(int colorsystem){ return m_parent->intf ## _SetColorSystem(colorsystem);}\
virtual int GetColorSystem(void){ return m_parent->intf ## _GetColorSystem();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
