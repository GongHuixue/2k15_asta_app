#ifndef IHSVSDMCONTROLNOTIFY_H
#define IHSVSDMCONTROLNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSdmControlNotify
{
public:
	virtual ~IHsvSdmControlNotify(){}
	#define IHsvSdmControlNotify_DataNotAvailable		((int)0 )
	#define IHsvSdmControlNotify_OnlyPsiDataAvailable		((int)1 )
	#define IHsvSdmControlNotify_SiDataAvailable		((int)2 )
	#define IHsvSdmControlNotify_StartedCollection		((int)3 )
	#define IHsvSdmControlNotify_StoppedCollection		((int)4 )
	#define IHsvSdmControlNotify_DataAvailable		((int)5 )
	virtual void OnEvent(HsvDemux dmx,int eventid)= 0;
};


#define IHsvSdmControlNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(HsvDemux dmx,int eventid);\
class Comp ## _ ## intf : public IHsvSdmControlNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(HsvDemux dmx,int eventid){ return m_parent->intf ## _OnEvent(dmx,eventid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
