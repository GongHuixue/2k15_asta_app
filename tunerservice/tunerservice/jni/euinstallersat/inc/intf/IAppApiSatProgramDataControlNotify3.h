#ifndef IAPPAPISATPROGRAMDATACONTROLNOTIFY3_H
#define IAPPAPISATPROGRAMDATACONTROLNOTIFY3_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataControlNotify3
{
public:
	virtual ~IAppApiSatProgramDataControlNotify3(){}
	virtual void OnChannelChangeStart(int seltype,AppApiChannel channel)= 0;
	virtual void OnChannelChangeEnd(int seltype,AppApiChannel channel)= 0;
	virtual void OnDirectTuningStart(AppApiDirectTuningParameters Param)= 0;
	virtual void OnDirectTuningEnd(AppApiDirectTuningParameters Param)= 0;
	virtual void OnUserParentalRatingChanged(AppApiParentalRating Rating)= 0;
	virtual void OnStreamParentalRatingChanged(AppApiParentalRating Rating)= 0;
	virtual void OnLockStatusChanged(int Status)= 0;
	virtual void OnCCSettingChanged(int CCSetting)= 0;
	virtual void OnSubtitleSettingChanged(int SubtitleSetting)= 0;
	virtual void OnCurrentPmtPidChanged(int PmtPid)= 0;
};


#define IAppApiSatProgramDataControlNotify3Impl(Comp,intf)    \
virtual void intf ## _OnChannelChangeStart(int seltype,AppApiChannel channel);\
virtual void intf ## _OnChannelChangeEnd(int seltype,AppApiChannel channel);\
virtual void intf ## _OnDirectTuningStart(AppApiDirectTuningParameters Param);\
virtual void intf ## _OnDirectTuningEnd(AppApiDirectTuningParameters Param);\
virtual void intf ## _OnUserParentalRatingChanged(AppApiParentalRating Rating);\
virtual void intf ## _OnStreamParentalRatingChanged(AppApiParentalRating Rating);\
virtual void intf ## _OnLockStatusChanged(int Status);\
virtual void intf ## _OnCCSettingChanged(int CCSetting);\
virtual void intf ## _OnSubtitleSettingChanged(int SubtitleSetting);\
virtual void intf ## _OnCurrentPmtPidChanged(int PmtPid);\
class Comp ## _ ## intf : public IAppApiSatProgramDataControlNotify3 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnChannelChangeStart(int seltype,AppApiChannel channel){ return m_parent->intf ## _OnChannelChangeStart(seltype,channel);}\
virtual void OnChannelChangeEnd(int seltype,AppApiChannel channel){ return m_parent->intf ## _OnChannelChangeEnd(seltype,channel);}\
virtual void OnDirectTuningStart(AppApiDirectTuningParameters Param){ return m_parent->intf ## _OnDirectTuningStart(Param);}\
virtual void OnDirectTuningEnd(AppApiDirectTuningParameters Param){ return m_parent->intf ## _OnDirectTuningEnd(Param);}\
virtual void OnUserParentalRatingChanged(AppApiParentalRating Rating){ return m_parent->intf ## _OnUserParentalRatingChanged(Rating);}\
virtual void OnStreamParentalRatingChanged(AppApiParentalRating Rating){ return m_parent->intf ## _OnStreamParentalRatingChanged(Rating);}\
virtual void OnLockStatusChanged(int Status){ return m_parent->intf ## _OnLockStatusChanged(Status);}\
virtual void OnCCSettingChanged(int CCSetting){ return m_parent->intf ## _OnCCSettingChanged(CCSetting);}\
virtual void OnSubtitleSettingChanged(int SubtitleSetting){ return m_parent->intf ## _OnSubtitleSettingChanged(SubtitleSetting);}\
virtual void OnCurrentPmtPidChanged(int PmtPid){ return m_parent->intf ## _OnCurrentPmtPidChanged(PmtPid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
