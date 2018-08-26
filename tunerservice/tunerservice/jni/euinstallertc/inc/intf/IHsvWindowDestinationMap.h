#ifndef IHSVWINDOWDESTINATIONMAP_H
#define IHSVWINDOWDESTINATIONMAP_H
#include <intfparam.h>
#include <provreq.h>
class IHsvWindowDestinationMap
{
public:
	virtual ~IHsvWindowDestinationMap(){}
	virtual int InvalidWindowId(void)= 0;
	virtual int GetWindowId(HsvDestination dest)= 0;
	virtual int GetAudioNodeId(HsvDestination dest)= 0;
	virtual int GetMonitorWindow(void)= 0;
	#define IHsvWindowDestinationMap_WndTypeInvalid		((int)-1 )
	#define IHsvWindowDestinationMap_WndTypeMainVideo		((int)0 )
	#define IHsvWindowDestinationMap_WndTypeMainAudio		((int)1 )
	#define IHsvWindowDestinationMap_WndTypeMonitor		((int)2 )
	#define IHsvWindowDestinationMap_WndTypeAuxVideo		((int)3 )
	virtual int GetWindowType(int winid)= 0;
	virtual HsvDestination GetDestinationForWindow(int windowid)= 0;
};


#define IHsvWindowDestinationMapImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
virtual int intf ## _GetWindowId(HsvDestination dest);\
virtual int intf ## _GetAudioNodeId(HsvDestination dest);\
virtual int intf ## _GetMonitorWindow(void);\
virtual int intf ## _GetWindowType(int winid);\
virtual HsvDestination intf ## _GetDestinationForWindow(int windowid);\
class Comp ## _ ## intf : public IHsvWindowDestinationMap \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_InvalidWindowId; \
    Comp ## _ ## intf( Comp *parent):m_InvalidWindowId(parent) \
    {\
        m_parent = parent;\
    }\
virtual int InvalidWindowId(void){ return m_InvalidWindowId.Call();}\
virtual int GetWindowId(HsvDestination dest){ return m_parent->intf ## _GetWindowId(dest);}\
virtual int GetAudioNodeId(HsvDestination dest){ return m_parent->intf ## _GetAudioNodeId(dest);}\
virtual int GetMonitorWindow(void){ return m_parent->intf ## _GetMonitorWindow();}\
virtual int GetWindowType(int winid){ return m_parent->intf ## _GetWindowType(winid);}\
virtual HsvDestination GetDestinationForWindow(int windowid){ return m_parent->intf ## _GetDestinationForWindow(windowid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
