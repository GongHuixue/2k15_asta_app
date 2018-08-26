#ifndef IHSVINSTALLATIONSYSTEMCONTROL_H
#define IHSVINSTALLATIONSYSTEMCONTROL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallationSystemControl
{
public:
	virtual ~IHsvInstallationSystemControl(){}
	virtual void BlockDestinations(HsvDestination dest,Bool OnOff)= 0;
	virtual void SetVideoMute(Bool OnOff)= 0;
	virtual void SetAudioMute(Bool OnOff)= 0;
};


#define IHsvInstallationSystemControlImpl(Comp,intf)    \
virtual void intf ## _BlockDestinations(HsvDestination dest,Bool OnOff);\
virtual void intf ## _SetVideoMute(Bool OnOff);\
virtual void intf ## _SetAudioMute(Bool OnOff);\
class Comp ## _ ## intf : public IHsvInstallationSystemControl \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void BlockDestinations(HsvDestination dest,Bool OnOff){ return m_parent->intf ## _BlockDestinations(dest,OnOff);}\
virtual void SetVideoMute(Bool OnOff){ return m_parent->intf ## _SetVideoMute(OnOff);}\
virtual void SetAudioMute(Bool OnOff){ return m_parent->intf ## _SetAudioMute(OnOff);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
