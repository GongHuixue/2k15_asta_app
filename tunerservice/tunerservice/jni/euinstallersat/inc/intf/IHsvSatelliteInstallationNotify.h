#ifndef IHSVSATELLITEINSTALLATIONNOTIFY_H
#define IHSVSATELLITEINSTALLATIONNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteInstallationNotify
{
public:
	virtual ~IHsvSatelliteInstallationNotify(){}
	#define IHsvSatelliteInstallationNotify_EventInsStarted		((int)0 )
	#define IHsvSatelliteInstallationNotify_EventInsStopped		((int)1 )
	#define IHsvSatelliteInstallationNotify_EventInsCompleted		((int)2 )
	#define IHsvSatelliteInstallationNotify_EventInsFailed		((int)3 )
	#define IHsvSatelliteInstallationNotify_EventSatelliteFound		((int)4 )
	#define IHsvSatelliteInstallationNotify_EventSatelliteNotFound		((int)5 )
	#define IHsvSatelliteInstallationNotify_EventSortingStarted		((int)6 )
	#define IHsvSatelliteInstallationNotify_EventSortStopped		((int)7 )
	#define IHsvSatelliteInstallationNotify_EventSortCompleted		((int)8 )
	#define IHsvSatelliteInstallationNotify_EventSortInProgress		((int)9 )
	#define IHsvSatelliteInstallationNotify_EventChannelFound		((int)10 )
	#define IHsvSatelliteInstallationNotify_EventChannelNotFound		((int)11 )
	#define IHsvSatelliteInstallationNotify_EventInsProgress		((int)12 )
	#define IHsvSatelliteInstallationNotify_EventInsCompletedForLnb		((int)13 )
	#define IHsvSatelliteInstallationNotify_EventSatLnbRemovalCompleted		((int)14 )
	#define IHsvSatelliteInstallationNotify_EventContentLibRead		((int)15 )
	#define IHsvSatelliteInstallationNotify_EventPkgInstallStart		((int)16 )
	#define IHsvSatelliteInstallationNotify_EventPkgInstallEnd		((int)17 )
	#define IHsvSatelliteInstallationNotify_EventLNBStart		((int)18 )
	#define IHsvSatelliteInstallationNotify_EventLNBEnd		((int)19 )
	#define IHsvSatelliteInstallationNotify_EventSatLnbRemovalStarted		((int)20 )
	#define IHsvSatelliteInstallationNotify_EventSatRemovalCompleted		((int)21 )
	#define IHsvSatelliteInstallationNotify_EventPackageInstallFailed		((int)22 )
	#define IHsvSatelliteInstallationNotify_EventPackageId		((int)23 )
	#define IHsvSatelliteInstallationNotify_EventPredefinedListCopySuccesful		((int)24 )
	#define IHsvSatelliteInstallationNotify_EventPredefinedListCopyGenericError		((int)25 )
	#define IHsvSatelliteInstallationNotify_EventPredefinedListCopyOlderVersion		((int)26 )
	#define IHsvSatelliteInstallationNotify_EventDifferentSatelliteFound		((int)27 )
	#define IHsvSatelliteInstallationNotify_EventPkgParsingStarted		((int)28 )
	#define IHsvSatelliteInstallationNotify_EventPkgParsingCompleted		((int)29 )
	#define IHsvSatelliteInstallationNotify_EventTriggerBckgndUpdateInstall		((int)30 )
	#define IHsvSatelliteInstallationNotify_EventInsOpProfileRequestNormal ((int)31 )
	#define IHsvSatelliteInstallationNotify_EventInsOpProfileRequestUrgent ((int)32 )
	#define IHsvSatelliteInstallationNotify_EventPresetAdded		((int)33 )
	#define IHsvSatelliteInstallationNotify_EventPresetDeleted		((int)34 )
	#define IHsvSatelliteInstallationNotify_EventUpdated		((int)35 )
	#define IHsvSatelliteInstallationNotify_EventInsOpProfileRequestImmediate ((int) 36 )
	#define IHsvSatelliteInstallationNotify_EventCamNitInstallation		((int)37 )
	#define IHsvSatelliteInstallationNotify_EventSetTime		((int)38 )
	#define IHsvSatelliteInstallationNotify_EventRegionScanEnd		((int)39)
	#define IHsvSatelliteInstallationNotify_EventSetTimeOffset		((int)40 )

	virtual void OnEvent(int eventid,int value)= 0;
};


#define IHsvSatelliteInstallationNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int eventid,int value);\
class Comp ## _ ## intf : public IHsvSatelliteInstallationNotify \
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
