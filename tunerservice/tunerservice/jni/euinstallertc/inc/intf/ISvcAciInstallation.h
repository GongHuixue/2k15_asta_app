#ifndef ISVCACIINSTALLATION_H
#define ISVCACIINSTALLATION_H
#include <intfparam.h>
#include <provreq.h>
class ISvcAciInstallation
{
public:
	virtual ~ISvcAciInstallation(){}
	virtual Bool IsAciSupported(void)= 0;
	virtual void StartAciInstallation(void)= 0;
	virtual void StopAciInstallation(void)= 0;
	virtual HsvAciPriority GetPagePriority(void)= 0;
	virtual void StoreAciTable(void)= 0;
	virtual int GetNoOfPresets(void)= 0;
};


#define ISvcAciInstallationImpl(Comp,intf)    \
virtual Bool intf ## _IsAciSupported(void);\
virtual void intf ## _StartAciInstallation(void);\
virtual void intf ## _StopAciInstallation(void);\
virtual HsvAciPriority intf ## _GetPagePriority(void);\
virtual void intf ## _StoreAciTable(void);\
virtual int intf ## _GetNoOfPresets(void);\
class Comp ## _ ## intf : public ISvcAciInstallation \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool IsAciSupported(void){ return m_parent->intf ## _IsAciSupported();}\
virtual void StartAciInstallation(void){ return m_parent->intf ## _StartAciInstallation();}\
virtual void StopAciInstallation(void){ return m_parent->intf ## _StopAciInstallation();}\
virtual HsvAciPriority GetPagePriority(void){ return m_parent->intf ## _GetPagePriority();}\
virtual void StoreAciTable(void){ return m_parent->intf ## _StoreAciTable();}\
virtual int GetNoOfPresets(void){ return m_parent->intf ## _GetNoOfPresets();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
