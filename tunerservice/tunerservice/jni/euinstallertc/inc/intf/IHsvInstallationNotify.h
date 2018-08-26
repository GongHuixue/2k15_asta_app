#ifndef IHSVINSTALLATIONNOTIFY_H
#define IHSVINSTALLATIONNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallationNotify
{
public:
	virtual ~IHsvInstallationNotify(){}
	#define IHsvInstallationNotify_EventInstallationCompleted		((int)1 )
	#define IHsvInstallationNotify_EventInstallationStarted		((int)2 )
	#define IHsvInstallationNotify_EventInstallationStopped		((int)3 )
	#define IHsvInstallationNotify_EventInstallationPaused		((int)4 )
	#define IHsvInstallationNotify_EventInstallationContinued		((int)5 )
	#define IHsvInstallationNotify_EventChannelFound		((int)6 )
	#define IHsvInstallationNotify_EventChannelNotFound		((int)7 )
	#define IHsvInstallationNotify_EventSearchInProgress		((int)8 )
	#define IHsvInstallationNotify_EventTuningStarted		((int)9 )
	#define IHsvInstallationNotify_EventTuningStationFound		((int)10 )
	#define IHsvInstallationNotify_EventTuningStationNotFound		((int)11 )
	#define IHsvInstallationNotify_EventManualInstallationCniExtractionStarted		((int)12 )
	#define IHsvInstallationNotify_EventManualInstallationCniExtractionEnded		((int)13 )
	#define IHsvInstallationNotify_EventATSSortingStarted		((int)14 )
	#define IHsvInstallationNotify_EventAciStoreStarted		((int)15 )
	#define IHsvInstallationNotify_EventTvSystemChanged		((int)16 )
	#define IHsvInstallationNotify_EventMediumChanged		((int)17 )
	#define IHsvInstallationNotify_EventSignalStrengthChanged		((int)18 )
	#define IHsvInstallationNotify_EventBackGroundCNIUpdated		((int)19 )
	#define IHsvInstallationNotify_EventPresetStored		((int)20 )
	#define IHsvInstallationNotify_EventPhaseStarted		((int)22 )
	#define IHsvInstallationNotify_EventPhaseCompleted		((int)23 )
	#define IHsvInstallationNotify_EventChannelIterationStarted		((int)24 )
	#define IHsvInstallationNotify_EventHeirarchyModeDetected		((int)25 )
	#define IHsvInstallationNotify_EventChannelAdded		((int)26 )
	#define IHsvInstallationNotify_EventChannelRemoved		((int)27 )
	#define IHsvInstallationNotify_EventNetworkUpdateDetected		((int)28 )
	#define IHsvInstallationNotify_EventDisplayNetworkNames		((int)29 )
	#define IHsvInstallationNotify_EventNIDInvalid		((int)30 )
	#define IHsvInstallationNotify_EventNetworkUpdateNotDetected		((int)31 )
	#define IHsvInstallationNotify_EventOnConflictsDetected		((int)32 )
	#define IHsvInstallationNotify_EventDisplayRegionNames		((int)33 )
	#define IHsvInstallationNotify_EventPLPsDetected		((int)34 )
	#define IHsvInstallationNotify_NetworkOperator		((int)35 )
	#define IHsvInstallationNotify_EventCamInstallRequestNormal ((int)36 )
	#define IHsvInstallationNotify_EventCamInstallRequestUrgent ((int)37 )
	#define IHsvInstallationNotify_EventPresetAdded		((int)38 )
	#define IHsvInstallationNotify_EventPresetDeleted		((int)39 )
	#define IHsvInstallationNotify_EventUpdated		((int)40 )
	#define IHsvInstallationNotify_EventMultiPackageFound	((int)41)
	#define	IHsvInstallationNotify_EventMultiPackageToBeDisplayed	((int)42)
	#define	IHsvInstallationNotify_EventMultiPackageRemoved			((int)43)
	#define IHsvInstallationNotify_EventNewPresetNumber				((int)44)
	#define IHsvInstallationNotify_EventDisplayChannelListId		((int)45)
	#define IHsvInstallationNotify_EventTelenetNameUpdate			((int)46)
	#define IHsvInstallationNotify_EventTelenetMajorVersionUpdate	((int)47)
	#define IHsvInstallationNotify_EventLanguageUpdate	((int)48)
	#define IHsvInstallationNotify_EventChannelNameUpdated	((int)49)
	#define IHsvInstallationNotify_EventServiceFound ((int)50)
	#define IHsvInstallationNotify_EventServiceNotFound ((int)51)
	#define IHsvInstallationNotify_EventT2SwitchPLPID ((int)52)
	virtual void OnEvent(int eventid,int value)= 0;
};


#define IHsvInstallationNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int eventid,int value);\
class Comp ## _ ## intf : public IHsvInstallationNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int eventid,int value){ return m_parent->intf ## _OnEvent(eventid,value);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
