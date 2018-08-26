#ifndef IHSVDEMUXSECTIONFILTERNOTIFY_H
#define IHSVDEMUXSECTIONFILTERNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDemuxSectionFilterNotify
{
public:
	virtual ~IHsvDemuxSectionFilterNotify(){}
	virtual void OnRequestAllowed(HsvDestination dest)= 0;
	virtual void OnRequestCancelled(Nat32 subscrId)= 0;
	virtual void OnRequestNotAllowed(void)= 0;
};


#define IHsvDemuxSectionFilterNotifyImpl(Comp,intf)    \
virtual void intf ## _OnRequestAllowed(HsvDestination dest);\
virtual void intf ## _OnRequestCancelled(Nat32 subscrId);\
virtual void intf ## _OnRequestNotAllowed(void);\
class Comp ## _ ## intf : public IHsvDemuxSectionFilterNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnRequestAllowed(HsvDestination dest){ return m_parent->intf ## _OnRequestAllowed(dest);}\
virtual void OnRequestCancelled(Nat32 subscrId){ return m_parent->intf ## _OnRequestCancelled(subscrId);}\
virtual void OnRequestNotAllowed(void){ return m_parent->intf ## _OnRequestNotAllowed();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
