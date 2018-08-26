#ifndef IHSVANALOGINSTALLATIONNOTIFY_H
#define IHSVANALOGINSTALLATIONNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAnalogInstallationNotify
{
public:
	virtual ~IHsvAnalogInstallationNotify(){}
	#define IHsvAnalogInstallationNotify_EventManualInstallationCniExtractionStarted		((int)0 )
	#define IHsvAnalogInstallationNotify_EventManualInstallationCniExtractionEnded		((int)1 )
	#define IHsvAnalogInstallationNotify_EventAutomaticInstallationCompleted		((int)2 )
	#define IHsvAnalogInstallationNotify_EventChannelFound		((int)3 )
	#define IHsvAnalogInstallationNotify_EventATSSortingStarted		((int)4 )
	#define IHsvAnalogInstallationNotify_EventAciStoreStarted		((int)5 )
	#define IHsvAnalogInstallationNotify_EventTvSystemChanged		((int)6 )
	#define IHsvAnalogInstallationNotify_EventManualInstallationChannelNotFound		((int)7 )
	#define IHsvAnalogInstallationNotify_EventSearchInProgress		((int)8 )
	#define IHsvAnalogInstallationNotify_EventTuningStarted		((int)9 )
	#define IHsvAnalogInstallationNotify_EventTuningStationFound		((int)10 )
	#define IHsvAnalogInstallationNotify_EventTuningStationNotFound		((int)11 )
	#define IHsvAnalogInstallationNotify_EventPhaseStarted		((int)12 )
	#define IHsvAnalogInstallationNotify_EventPhaseCompleted		((int)13 )
	#define	IHsvAnalogInstallationNotify_EventMultiPackageFound		((int)14)
	#define	IHsvAnalogInstallationNotify_EventMultiPackageToBeDisplayed		((int)15)
	#define	IHsvAnalogInstallationNotify_EventMultiPackageRemoved		((int)16)
	virtual void OnEvent(int eventid,int value)= 0;
	virtual void OnManualInstallationStored(HsvChannel channel)= 0;
	virtual void OnBackgroundCniUpdated(Nat16 Cni,HsvChannel channel)= 0;
};


#define IHsvAnalogInstallationNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int eventid,int value);\
virtual void intf ## _OnManualInstallationStored(HsvChannel channel);\
virtual void intf ## _OnBackgroundCniUpdated(Nat16 Cni,HsvChannel channel);\
class Comp ## _ ## intf : public IHsvAnalogInstallationNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int eventid,int value){ return m_parent->intf ## _OnEvent(eventid,value);}\
virtual void OnManualInstallationStored(HsvChannel channel){ return m_parent->intf ## _OnManualInstallationStored(channel);}\
virtual void OnBackgroundCniUpdated(Nat16 Cni,HsvChannel channel){ return m_parent->intf ## _OnBackgroundCniUpdated(Cni,channel);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
