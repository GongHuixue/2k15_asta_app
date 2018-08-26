#ifndef ICESPACIDIV_H
#define ICESPACIDIV_H
#include <intfparam.h>
#include <provreq.h>
class ICesPaciDiv
{
public:
	virtual ~ICesPaciDiv(){}
	#define ICesPaciDiv_MaxPresets		((int)200 )
	virtual int MaxTunPreset(void)= 0;
	virtual int MinTunPreset(void)= 0;
	virtual int AciAcquisitionTimeoutTime(void)= 0;
	virtual int RestorePageAcqTimeoutTime(void)= 0;
	virtual int MultipageDisplayTimeoutTime(void)= 0;
	virtual int AciTxtHdrReqDelay(void)= 0;
	virtual int TunNotifyTimeout(void)= 0;
};


#define ICesPaciDivImpl(Comp,intf)    \
virtual int intf ## _MaxTunPreset(void);\
virtual int intf ## _MinTunPreset(void);\
virtual int intf ## _AciAcquisitionTimeoutTime(void);\
virtual int intf ## _RestorePageAcqTimeoutTime(void);\
virtual int intf ## _MultipageDisplayTimeoutTime(void);\
virtual int intf ## _AciTxtHdrReqDelay(void);\
virtual int intf ## _TunNotifyTimeout(void);\
class Comp ## _ ## intf : public ICesPaciDiv \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int MaxTunPreset(void){ return m_parent->intf ## _MaxTunPreset();}\
virtual int MinTunPreset(void){ return m_parent->intf ## _MinTunPreset();}\
virtual int AciAcquisitionTimeoutTime(void){ return m_parent->intf ## _AciAcquisitionTimeoutTime();}\
virtual int RestorePageAcqTimeoutTime(void){ return m_parent->intf ## _RestorePageAcqTimeoutTime();}\
virtual int MultipageDisplayTimeoutTime(void){ return m_parent->intf ## _MultipageDisplayTimeoutTime();}\
virtual int AciTxtHdrReqDelay(void){ return m_parent->intf ## _AciTxtHdrReqDelay();}\
virtual int TunNotifyTimeout(void){ return m_parent->intf ## _TunNotifyTimeout();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
