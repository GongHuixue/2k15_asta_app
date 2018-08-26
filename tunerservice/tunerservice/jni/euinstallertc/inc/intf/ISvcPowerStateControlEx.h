#ifndef ISVCPOWERSTATECONTROLEX_H
#define ISVCPOWERSTATECONTROLEX_H
#include <intfparam.h>
#include <provreq.h>
class ISvcPowerStateControlEx
{
public:
	virtual ~ISvcPowerStateControlEx(){}
	virtual void SetPowerMode(PwrMode p)= 0;
	virtual PwrMode GetPowerMode(void)= 0;
	virtual void SetWakeupReason(WkupReason wkupr)= 0;
	virtual WkupReason GetWakeupReason(void)= 0;
	virtual Bool RequestSsbyActivity(int Activity)= 0;
	virtual void StepwiseUp(void)= 0;
	virtual void StepwiseDown(void)= 0;
	virtual int GetCurrentStep(void)= 0;
	virtual void EnterStepwiseMode(Bool exit_enter)= 0;
	virtual void SetMainLed(GlowDescriptor gd,int msec_on,int msec_off,Bool pref_only)= 0;
	virtual Bool IsPowerStable(void)= 0;
	#define ISvcPowerStateControlEx_SemiSbyAcquisition		((int)0 )
	#define ISvcPowerStateControlEx_SemiSbyClkCalib		((int)0 )
	#define ISvcPowerStateControlEx_SemiSbyTvtvAcq		((int)0 )
	#define ISvcPowerStateControlEx_SemiSbyInstall		((int)0 )
	#define ISvcPowerStateControlEx_SemiSbyRecording		((int)0 )
	#define ISvcPowerStateControlEx_SemiSbyHoming		((int)0 )
};


#define ISvcPowerStateControlExImpl(Comp,intf)    \
virtual void intf ## _SetPowerMode(PwrMode p);\
virtual PwrMode intf ## _GetPowerMode(void);\
virtual void intf ## _SetWakeupReason(WkupReason wkupr);\
virtual WkupReason intf ## _GetWakeupReason(void);\
virtual Bool intf ## _RequestSsbyActivity(int Activity);\
virtual void intf ## _StepwiseUp(void);\
virtual void intf ## _StepwiseDown(void);\
virtual int intf ## _GetCurrentStep(void);\
virtual void intf ## _EnterStepwiseMode(Bool exit_enter);\
virtual void intf ## _SetMainLed(GlowDescriptor gd,int msec_on,int msec_off,Bool pref_only);\
virtual Bool intf ## _IsPowerStable(void);\
class Comp ## _ ## intf : public ISvcPowerStateControlEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SetPowerMode(PwrMode p){ return m_parent->intf ## _SetPowerMode(p);}\
virtual PwrMode GetPowerMode(void){ return m_parent->intf ## _GetPowerMode();}\
virtual void SetWakeupReason(WkupReason wkupr){ return m_parent->intf ## _SetWakeupReason(wkupr);}\
virtual WkupReason GetWakeupReason(void){ return m_parent->intf ## _GetWakeupReason();}\
virtual Bool RequestSsbyActivity(int Activity){ return m_parent->intf ## _RequestSsbyActivity(Activity);}\
virtual void StepwiseUp(void){ return m_parent->intf ## _StepwiseUp();}\
virtual void StepwiseDown(void){ return m_parent->intf ## _StepwiseDown();}\
virtual int GetCurrentStep(void){ return m_parent->intf ## _GetCurrentStep();}\
virtual void EnterStepwiseMode(Bool exit_enter){ return m_parent->intf ## _EnterStepwiseMode(exit_enter);}\
virtual void SetMainLed(GlowDescriptor gd,int msec_on,int msec_off,Bool pref_only){ return m_parent->intf ## _SetMainLed(gd,msec_on,msec_off,pref_only);}\
virtual Bool IsPowerStable(void){ return m_parent->intf ## _IsPowerStable();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
