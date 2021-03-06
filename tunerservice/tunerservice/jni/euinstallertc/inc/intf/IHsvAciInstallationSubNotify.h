#ifndef IHSVACIINSTALLATIONSUBNOTIFY_H
#define IHSVACIINSTALLATIONSUBNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAciInstallationSubNotify
{
public:
	virtual ~IHsvAciInstallationSubNotify(){}
	virtual void OnAciInstallationCompleted(Bool success)= 0;
	virtual void aciPresetsWriteInDataStarted(void)= 0;
};


#define IHsvAciInstallationSubNotifyImpl(Comp,intf)    \
virtual void intf ## _OnAciInstallationCompleted(Bool success);\
virtual void intf ## _aciPresetsWriteInDataStarted(void);\
class Comp ## _ ## intf : public IHsvAciInstallationSubNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnAciInstallationCompleted(Bool success){ return m_parent->intf ## _OnAciInstallationCompleted(success);}\
virtual void aciPresetsWriteInDataStarted(void){ return m_parent->intf ## _aciPresetsWriteInDataStarted();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
