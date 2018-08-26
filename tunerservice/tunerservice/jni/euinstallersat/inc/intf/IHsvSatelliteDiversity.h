#ifndef IHSVSATELLITEDIVERSITY_H
#define IHSVSATELLITEDIVERSITY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteDiversity
{
public:
	virtual ~IHsvSatelliteDiversity(){}
	virtual int iVersion(void)= 0;
	virtual Bool IsHomingMuxTuningRequired(int SatelliteId,int CountryId)= 0;
	virtual void LoadDefaultConnectionType(int CountryId,int * ConnectionType)= 0;
	virtual void LoadDefaultLnbType(int CountryId,int * LnbType)= 0;
	virtual Bool IsBackgroundInstallRequired(void)= 0;
	virtual Bool PerformReinstallInSemiStandby(void)= 0;
};


#define IHsvSatelliteDiversityImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsHomingMuxTuningRequired(int SatelliteId,int CountryId);\
virtual void intf ## _LoadDefaultConnectionType(int CountryId,int * ConnectionType);\
virtual void intf ## _LoadDefaultLnbType(int CountryId,int * LnbType);\
virtual Bool intf ## _IsBackgroundInstallRequired(void);\
virtual Bool intf ## _PerformReinstallInSemiStandby(void);\
class Comp ## _ ## intf : public IHsvSatelliteDiversity \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_iVersion; \
    Comp ## _ ## intf( Comp *parent):m_iVersion(parent) \
    {\
        m_parent = parent;\
    }\
virtual int iVersion(void){ return m_iVersion.Call();}\
virtual Bool IsHomingMuxTuningRequired(int SatelliteId,int CountryId){ return m_parent->intf ## _IsHomingMuxTuningRequired(SatelliteId,CountryId);}\
virtual void LoadDefaultConnectionType(int CountryId,int * ConnectionType){ return m_parent->intf ## _LoadDefaultConnectionType(CountryId,ConnectionType);}\
virtual void LoadDefaultLnbType(int CountryId,int * LnbType){ return m_parent->intf ## _LoadDefaultLnbType(CountryId,LnbType);}\
virtual Bool IsBackgroundInstallRequired(void){ return m_parent->intf ## _IsBackgroundInstallRequired();}\
virtual Bool PerformReinstallInSemiStandby(void){ return m_parent->intf ## _PerformReinstallInSemiStandby();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
