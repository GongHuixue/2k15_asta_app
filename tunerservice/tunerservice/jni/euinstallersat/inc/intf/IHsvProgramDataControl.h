#ifndef IHSVPROGRAMDATACONTROL_H
#define IHSVPROGRAMDATACONTROL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataControl
{
public:
	virtual ~IHsvProgramDataControl(){}
	#define IHsvProgramDataControl_Terrestrial		((int)0 )
	#define IHsvProgramDataControl_Cable		((int)1 )
	#define IHsvProgramDataControl_Satellite		((int)2 )
	virtual void SetSelectedMedium(int medium)= 0;
	virtual int GetSelectedMedium(void)= 0;
	virtual void SetInstalledMedium(int medium)= 0;
	virtual int GetInstalledMedium(void)= 0;
	virtual AppApiReturnCode GetCurrentProgram(AppApiChannel * Channel)= 0;
	virtual AppApiReturnCode SelectChannel(AppApiChannel channel)= 0;
	virtual AppApiReturnCode DirectTuning(AppApiDirectTuningParameters param)= 0;
	virtual AppApiReturnCode GetUserParentalRating(AppApiParentalRating * Rating)= 0;
	virtual AppApiReturnCode GetStreamParentalRating(AppApiParentalRating * Rating)= 0;
	virtual AppApiReturnCode IsChannelLocked(int * Status)= 0;
	virtual AppApiReturnCode EnableSubtitle(void)= 0;
	virtual AppApiReturnCode DisableSubtitle(void)= 0;
	virtual AppApiReturnCode DisableClosedCaption(void)= 0;
	virtual AppApiReturnCode EnableClosedCaption(void)= 0;
	virtual AppApiReturnCode GetCCSettings(int * CCSetting)= 0;
};


#define IHsvProgramDataControlImpl(Comp,intf)    \
virtual void intf ## _SetSelectedMedium(int medium);\
virtual int intf ## _GetSelectedMedium(void);\
virtual void intf ## _SetInstalledMedium(int medium);\
virtual int intf ## _GetInstalledMedium(void);\
virtual AppApiReturnCode intf ## _GetCurrentProgram(AppApiChannel * Channel);\
virtual AppApiReturnCode intf ## _SelectChannel(AppApiChannel channel);\
virtual AppApiReturnCode intf ## _DirectTuning(AppApiDirectTuningParameters param);\
virtual AppApiReturnCode intf ## _GetUserParentalRating(AppApiParentalRating * Rating);\
virtual AppApiReturnCode intf ## _GetStreamParentalRating(AppApiParentalRating * Rating);\
virtual AppApiReturnCode intf ## _IsChannelLocked(int * Status);\
virtual AppApiReturnCode intf ## _EnableSubtitle(void);\
virtual AppApiReturnCode intf ## _DisableSubtitle(void);\
virtual AppApiReturnCode intf ## _DisableClosedCaption(void);\
virtual AppApiReturnCode intf ## _EnableClosedCaption(void);\
virtual AppApiReturnCode intf ## _GetCCSettings(int * CCSetting);\
class Comp ## _ ## intf : public IHsvProgramDataControl \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SetSelectedMedium(int medium){ return m_parent->intf ## _SetSelectedMedium(medium);}\
virtual int GetSelectedMedium(void){ return m_parent->intf ## _GetSelectedMedium();}\
virtual void SetInstalledMedium(int medium){ return m_parent->intf ## _SetInstalledMedium(medium);}\
virtual int GetInstalledMedium(void){ return m_parent->intf ## _GetInstalledMedium();}\
virtual AppApiReturnCode GetCurrentProgram(AppApiChannel * Channel){ return m_parent->intf ## _GetCurrentProgram(Channel);}\
virtual AppApiReturnCode SelectChannel(AppApiChannel channel){ return m_parent->intf ## _SelectChannel(channel);}\
virtual AppApiReturnCode DirectTuning(AppApiDirectTuningParameters param){ return m_parent->intf ## _DirectTuning(param);}\
virtual AppApiReturnCode GetUserParentalRating(AppApiParentalRating * Rating){ return m_parent->intf ## _GetUserParentalRating(Rating);}\
virtual AppApiReturnCode GetStreamParentalRating(AppApiParentalRating * Rating){ return m_parent->intf ## _GetStreamParentalRating(Rating);}\
virtual AppApiReturnCode IsChannelLocked(int * Status){ return m_parent->intf ## _IsChannelLocked(Status);}\
virtual AppApiReturnCode EnableSubtitle(void){ return m_parent->intf ## _EnableSubtitle();}\
virtual AppApiReturnCode DisableSubtitle(void){ return m_parent->intf ## _DisableSubtitle();}\
virtual AppApiReturnCode DisableClosedCaption(void){ return m_parent->intf ## _DisableClosedCaption();}\
virtual AppApiReturnCode EnableClosedCaption(void){ return m_parent->intf ## _EnableClosedCaption();}\
virtual AppApiReturnCode GetCCSettings(int * CCSetting){ return m_parent->intf ## _GetCCSettings(CCSetting);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
