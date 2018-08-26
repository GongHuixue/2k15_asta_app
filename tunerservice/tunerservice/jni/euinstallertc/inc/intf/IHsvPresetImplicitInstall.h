#ifndef IHSVPRESETIMPLICITINSTALL_H
#define IHSVPRESETIMPLICITINSTALL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPresetImplicitInstall
{
public:
	virtual ~IHsvPresetImplicitInstall(){}
	virtual void StartImplicitInstallation(HsvChannel chan)= 0;
	virtual void StopImplicitInstallation(void)= 0;
};


#define IHsvPresetImplicitInstallImpl(Comp,intf)    \
virtual void intf ## _StartImplicitInstallation(HsvChannel chan);\
virtual void intf ## _StopImplicitInstallation(void);\
class Comp ## _ ## intf : public IHsvPresetImplicitInstall \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void StartImplicitInstallation(HsvChannel chan){ return m_parent->intf ## _StartImplicitInstallation(chan);}\
virtual void StopImplicitInstallation(void){ return m_parent->intf ## _StopImplicitInstallation();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
