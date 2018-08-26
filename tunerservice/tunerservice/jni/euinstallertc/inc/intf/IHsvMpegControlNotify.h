#ifndef IHSVMPEGCONTROLNOTIFY_H
#define IHSVMPEGCONTROLNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvMpegControlNotify
{
public:
	virtual ~IHsvMpegControlNotify(){}
	virtual void OnCurrentPmtPidChanged(int CurrentPmtPid)= 0;
};


#define IHsvMpegControlNotifyImpl(Comp,intf)    \
virtual void intf ## _OnCurrentPmtPidChanged(int CurrentPmtPid);\
class Comp ## _ ## intf : public IHsvMpegControlNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnCurrentPmtPidChanged(int CurrentPmtPid){ return m_parent->intf ## _OnCurrentPmtPidChanged(CurrentPmtPid);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
