#ifndef ICESOPERATORPROFILENOTIFY_H
#define ICESOPERATORPROFILENOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class ICesOperatorProfileNotify
{
public:
	virtual ~ICesOperatorProfileNotify(){}
	virtual void OnOpSearchStatus(Op_ProfileSearchStatus opStatus)= 0;
	virtual void OnOpStatusInfo(Op_ProfileStatusInfo statusInfo)= 0;
	virtual void OnOpNIT(Op_ProfileNitData nitData)= 0;
	virtual void OnOpTune(Op_ProfileTuneData tuneData)= 0;
};


#define ICesOperatorProfileNotifyImpl(Comp,intf)    \
virtual void intf ## _OnOpSearchStatus(Op_ProfileSearchStatus opStatus);\
virtual void intf ## _OnOpStatusInfo(Op_ProfileStatusInfo statusInfo);\
virtual void intf ## _OnOpNIT(Op_ProfileNitData nitData);\
virtual void intf ## _OnOpTune(Op_ProfileTuneData tuneData);\
class Comp ## _ ## intf : public ICesOperatorProfileNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnOpSearchStatus(Op_ProfileSearchStatus opStatus){ return m_parent->intf ## _OnOpSearchStatus(opStatus);}\
virtual void OnOpStatusInfo(Op_ProfileStatusInfo statusInfo){ return m_parent->intf ## _OnOpStatusInfo(statusInfo);}\
virtual void OnOpNIT(Op_ProfileNitData nitData){ return m_parent->intf ## _OnOpNIT(nitData);}\
virtual void OnOpTune(Op_ProfileTuneData tuneData){ return m_parent->intf ## _OnOpTune(tuneData);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
