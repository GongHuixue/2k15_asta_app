#ifndef IAPPAPISATPROGRAMDATACONTROL_H
#define IAPPAPISATPROGRAMDATACONTROL_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataControl
{
public:
	virtual ~IAppApiSatProgramDataControl(){}
	virtual AppApiReturnCode GetCurrentChannel(AppApiChannel * Channel)= 0;
	virtual AppApiReturnCode TuneToChannel(AppApiChannel channel)= 0;
};


#define IAppApiSatProgramDataControlImpl(Comp,intf)    \
virtual AppApiReturnCode intf ## _GetCurrentChannel(AppApiChannel * Channel);\
virtual AppApiReturnCode intf ## _TuneToChannel(AppApiChannel channel);\
class Comp ## _ ## intf : public IAppApiSatProgramDataControl \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual AppApiReturnCode GetCurrentChannel(AppApiChannel * Channel){ return m_parent->intf ## _GetCurrentChannel(Channel);}\
virtual AppApiReturnCode TuneToChannel(AppApiChannel channel){ return m_parent->intf ## _TuneToChannel(channel);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
