#ifndef IAPPAPISATPROGRAMDATACONTROL2_H
#define IAPPAPISATPROGRAMDATACONTROL2_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataControl2
{
public:
	virtual ~IAppApiSatProgramDataControl2(){}
	virtual AppApiReturnCode GetCurrentChannel(AppApiChannel * Channel)= 0;
	virtual AppApiReturnCode SelectChannel(AppApiChannel channel)= 0;
	virtual AppApiReturnCode DirectTuning(AppApiDirectTuningParameters param)= 0;
	virtual AppApiReturnCode GetUserParentalRating(AppApiParentalRating * Rating)= 0;
	virtual AppApiReturnCode GetStreamParentalRating(AppApiParentalRating * Rating)= 0;
	virtual AppApiReturnCode IsChannelLocked(int * Status)= 0;
	virtual AppApiReturnCode EnableSubtitle(void)= 0;
	virtual AppApiReturnCode DisableSubtitle(void)= 0;
	virtual AppApiReturnCode EnableClosedCaption(void)= 0;
	virtual AppApiReturnCode DisableClosedCaption(void)= 0;
};


#define IAppApiSatProgramDataControl2Impl(Comp,intf)    \
virtual AppApiReturnCode intf ## _GetCurrentChannel(AppApiChannel * Channel);\
virtual AppApiReturnCode intf ## _SelectChannel(AppApiChannel channel);\
virtual AppApiReturnCode intf ## _DirectTuning(AppApiDirectTuningParameters param);\
virtual AppApiReturnCode intf ## _GetUserParentalRating(AppApiParentalRating * Rating);\
virtual AppApiReturnCode intf ## _GetStreamParentalRating(AppApiParentalRating * Rating);\
virtual AppApiReturnCode intf ## _IsChannelLocked(int * Status);\
virtual AppApiReturnCode intf ## _EnableSubtitle(void);\
virtual AppApiReturnCode intf ## _DisableSubtitle(void);\
virtual AppApiReturnCode intf ## _EnableClosedCaption(void);\
virtual AppApiReturnCode intf ## _DisableClosedCaption(void);\
class Comp ## _ ## intf : public IAppApiSatProgramDataControl2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual AppApiReturnCode GetCurrentChannel(AppApiChannel * Channel){ return m_parent->intf ## _GetCurrentChannel(Channel);}\
virtual AppApiReturnCode SelectChannel(AppApiChannel channel){ return m_parent->intf ## _SelectChannel(channel);}\
virtual AppApiReturnCode DirectTuning(AppApiDirectTuningParameters param){ return m_parent->intf ## _DirectTuning(param);}\
virtual AppApiReturnCode GetUserParentalRating(AppApiParentalRating * Rating){ return m_parent->intf ## _GetUserParentalRating(Rating);}\
virtual AppApiReturnCode GetStreamParentalRating(AppApiParentalRating * Rating){ return m_parent->intf ## _GetStreamParentalRating(Rating);}\
virtual AppApiReturnCode IsChannelLocked(int * Status){ return m_parent->intf ## _IsChannelLocked(Status);}\
virtual AppApiReturnCode EnableSubtitle(void){ return m_parent->intf ## _EnableSubtitle();}\
virtual AppApiReturnCode DisableSubtitle(void){ return m_parent->intf ## _DisableSubtitle();}\
virtual AppApiReturnCode EnableClosedCaption(void){ return m_parent->intf ## _EnableClosedCaption();}\
virtual AppApiReturnCode DisableClosedCaption(void){ return m_parent->intf ## _DisableClosedCaption();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
