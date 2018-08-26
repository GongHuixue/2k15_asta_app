#ifndef IHSVMPEGSECTIONSNOTIFY_H
#define IHSVMPEGSECTIONSNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvMpegSectionsNotify
{
public:
	virtual ~IHsvMpegSectionsNotify(){}
	#define IHsvMpegSectionsNotify_PmtData		((int)0 )
	#define IHsvMpegSectionsNotify_PmtAcquisitionComplete		((int)1 )
	virtual void OnChanged(HsvDemux dmx,int value,int eventid)= 0;
	virtual void OnAdded(HsvDemux dmx,int value,int eventid)= 0;
	virtual void OnRemoved(HsvDemux dmx,int value,int eventid)= 0;
};


#define IHsvMpegSectionsNotifyImpl(Comp,intf)    \
virtual void intf ## _OnChanged(HsvDemux dmx,int value,int eventid);\
virtual void intf ## _OnAdded(HsvDemux dmx,int value,int eventid);\
virtual void intf ## _OnRemoved(HsvDemux dmx,int value,int eventid);\
class Comp ## _ ## intf : public IHsvMpegSectionsNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnChanged(HsvDemux dmx,int value,int eventid){ return m_parent->intf ## _OnChanged(dmx,value,eventid);}\
virtual void OnAdded(HsvDemux dmx,int value,int eventid){ return m_parent->intf ## _OnAdded(dmx,value,eventid);}\
virtual void OnRemoved(HsvDemux dmx,int value,int eventid){ return m_parent->intf ## _OnRemoved(dmx,value,eventid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
