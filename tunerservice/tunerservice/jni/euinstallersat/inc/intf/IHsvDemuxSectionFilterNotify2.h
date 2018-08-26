#ifndef IHSVDEMUXSECTIONFILTERNOTIFY2_H
#define IHSVDEMUXSECTIONFILTERNOTIFY2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDemuxSectionFilterNotify2
{
public:
	virtual ~IHsvDemuxSectionFilterNotify2(){}
	virtual void OnRequestAllowed(HsvDestination dest)= 0;
	virtual void OnRequestCancelled(Nat32 subscrId)= 0;
};


#define IHsvDemuxSectionFilterNotify2Impl(Comp,intf)    \
virtual void intf ## _OnRequestAllowed(HsvDestination dest);\
virtual void intf ## _OnRequestCancelled(Nat32 subscrId);\
class Comp ## _ ## intf : public IHsvDemuxSectionFilterNotify2 \
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
};\
Comp ## _ ## intf i__ ## intf;


#endif
