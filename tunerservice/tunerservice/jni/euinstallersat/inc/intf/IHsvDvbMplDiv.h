#ifndef IHSVDVBMPLDIV_H
#define IHSVDVBMPLDIV_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDvbMplDiv
{
public:
	virtual ~IHsvDvbMplDiv(){}
	virtual int AvSignalDetectionTimeOut(void)= 0;
	virtual Bool HearingImpairedOn(void)= 0;
	virtual Bool VisuallyImpairedOn(void)= 0;
	virtual Bool SubtitleOn(void)= 0;
	virtual Bool PidCachingEnabled(void)= 0;
	virtual Bool SubtitlePidFallbackFirstPMT(void)= 0;
};


#define IHsvDvbMplDivImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Bool>;\
virtual Bool intf ## _SubtitlePidFallbackFirstPMT(void);\
class Comp ## _ ## intf : public IHsvDvbMplDiv \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_AvSignalDetectionTimeOut; \
    InterfaceParam<Comp,Bool> m_HearingImpairedOn; \
    InterfaceParam<Comp,Bool> m_VisuallyImpairedOn; \
    InterfaceParam<Comp,Bool> m_SubtitleOn; \
    InterfaceParam<Comp,Bool> m_PidCachingEnabled; \
    Comp ## _ ## intf( Comp *parent):m_AvSignalDetectionTimeOut(parent),m_HearingImpairedOn(parent),m_VisuallyImpairedOn(parent),m_SubtitleOn(parent),m_PidCachingEnabled(parent) \
    {\
        m_parent = parent;\
    }\
virtual int AvSignalDetectionTimeOut(void){ return m_AvSignalDetectionTimeOut.Call();}\
virtual Bool HearingImpairedOn(void){ return m_HearingImpairedOn.Call();}\
virtual Bool VisuallyImpairedOn(void){ return m_VisuallyImpairedOn.Call();}\
virtual Bool SubtitleOn(void){ return m_SubtitleOn.Call();}\
virtual Bool PidCachingEnabled(void){ return m_PidCachingEnabled.Call();}\
virtual Bool SubtitlePidFallbackFirstPMT(void){ return m_parent->intf ## _SubtitlePidFallbackFirstPMT();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
