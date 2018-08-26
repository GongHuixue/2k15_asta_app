#ifndef IHSVPRESETIMPLICITINSTALLNOTIFY_H
#define IHSVPRESETIMPLICITINSTALLNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPresetImplicitInstallNotify
{
public:
	virtual ~IHsvPresetImplicitInstallNotify(){}
	#define IHsvPresetImplicitInstallNotify_OnImplicitInstallationCompleted		((int)0 )
	#define IHsvPresetImplicitInstallNotify_OnFrequencyBandSearchStarted		((int)1 )
	virtual void OnEvent(int eventid)= 0;
};


#define IHsvPresetImplicitInstallNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int eventid);\
class Comp ## _ ## intf : public IHsvPresetImplicitInstallNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int eventid){ return m_parent->intf ## _OnEvent(eventid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
