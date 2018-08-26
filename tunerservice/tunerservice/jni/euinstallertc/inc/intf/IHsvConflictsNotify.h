#ifndef IHSVCONFLICTSNOTIFY_H
#define IHSVCONFLICTSNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvConflictsNotify
{
public:
	virtual ~IHsvConflictsNotify(){}
	#define IHsvConflictsNotify_ConflictsResolved		((int)0 )
	#define IHsvConflictsNotify_ConflictsNotResolved		((int)1 )
	virtual void OnEvent(int ConflictsResolutionStatus)= 0;
	virtual void OnConflictsDetected(void)= 0;
};


#define IHsvConflictsNotifyImpl(Comp,intf)    \
virtual void intf ## _OnEvent(int ConflictsResolutionStatus);\
virtual void intf ## _OnConflictsDetected(void);\
class Comp ## _ ## intf : public IHsvConflictsNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnEvent(int ConflictsResolutionStatus){ return m_parent->intf ## _OnEvent(ConflictsResolutionStatus);}\
virtual void OnConflictsDetected(void){ return m_parent->intf ## _OnConflictsDetected();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
