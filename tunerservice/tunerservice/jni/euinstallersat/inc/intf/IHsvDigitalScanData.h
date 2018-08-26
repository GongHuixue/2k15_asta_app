#ifndef IHSVDIGITALSCANDATA_H
#define IHSVDIGITALSCANDATA_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalScanData
{
public:
	virtual ~IHsvDigitalScanData(){}
	virtual void GetPtcInfo(HsvInstallationPTC * ptc)= 0;
	virtual int GetInstallationVersion(void)= 0;
	virtual void GetPtcInfoForSdSd(HsvInstallationPTC * ptc)= 0;
	virtual void SyncComplete(void)= 0;
};


#define IHsvDigitalScanDataImpl(Comp,intf)    \
virtual void intf ## _GetPtcInfo(HsvInstallationPTC * ptc);\
virtual int intf ## _GetInstallationVersion(void);\
virtual void intf ## _GetPtcInfoForSdSd(HsvInstallationPTC * ptc);\
virtual void intf ## _SyncComplete(void);\
class Comp ## _ ## intf : public IHsvDigitalScanData \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void GetPtcInfo(HsvInstallationPTC * ptc){ return m_parent->intf ## _GetPtcInfo(ptc);}\
virtual int GetInstallationVersion(void){ return m_parent->intf ## _GetInstallationVersion();}\
virtual void GetPtcInfoForSdSd(HsvInstallationPTC * ptc){ return m_parent->intf ## _GetPtcInfoForSdSd(ptc);}\
virtual void SyncComplete(void){ return m_parent->intf ## _SyncComplete();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
