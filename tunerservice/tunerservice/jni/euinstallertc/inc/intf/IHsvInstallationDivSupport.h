#ifndef IHSVINSTALLATIONDIVSUPPORT_H
#define IHSVINSTALLATIONDIVSUPPORT_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallationDivSupport
{
public:
	virtual ~IHsvInstallationDivSupport(){}
	virtual Bool ParseLCN(void)= 0;
	virtual Bool StaticTable(void)= 0;
	virtual int InstallTestStreams(int installationmode,int medium)= 0;
	virtual int PresetNameLength(void)= 0;
};


#define IHsvInstallationDivSupportImpl(Comp,intf)    \
virtual Bool intf ## _ParseLCN(void);\
virtual Bool intf ## _StaticTable(void);\
virtual int intf ## _InstallTestStreams(int installationmode,int medium);\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvInstallationDivSupport \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_PresetNameLength; \
    Comp ## _ ## intf( Comp *parent):m_PresetNameLength(parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool ParseLCN(void){ return m_parent->intf ## _ParseLCN();}\
virtual Bool StaticTable(void){ return m_parent->intf ## _StaticTable();}\
virtual int InstallTestStreams(int installationmode,int medium){ return m_parent->intf ## _InstallTestStreams(installationmode,medium);}\
virtual int PresetNameLength(void){ return m_PresetNameLength.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
