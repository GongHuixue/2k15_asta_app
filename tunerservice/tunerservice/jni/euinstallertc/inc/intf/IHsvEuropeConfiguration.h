#ifndef IHSVEUROPECONFIGURATION_H
#define IHSVEUROPECONFIGURATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvEuropeConfiguration
{
public:
	virtual ~IHsvEuropeConfiguration(){}
	#define IHsvEuropeConfiguration_AutoStoreModeNone		((int)0 )
	#define IHsvEuropeConfiguration_AutoStoreModeVpsPdc		((int)1 )
	#define IHsvEuropeConfiguration_AutoStoreModeAci		((int)2 )
	#define IHsvEuropeConfiguration_AutoStoreModeVpsPdcAci		((int)3 )
	virtual int GetAutoStoreMode(void)= 0;
	virtual int GetMedium(void)= 0;
	virtual void GetBreakOutSource(HsvSource * Source)= 0;
	virtual void GetBreakOutChannel(HsvChannel * ChannelNo)= 0;
	virtual HsvSource GetDefaultSpdifAssociation(HsvSource SpdifSource)= 0;
	virtual Nat32 InstallationCookie(void)= 0;
};


#define IHsvEuropeConfigurationImpl(Comp,intf)    \
virtual int intf ## _GetAutoStoreMode(void);\
virtual int intf ## _GetMedium(void);\
virtual void intf ## _GetBreakOutSource(HsvSource * Source);\
virtual void intf ## _GetBreakOutChannel(HsvChannel * ChannelNo);\
virtual HsvSource intf ## _GetDefaultSpdifAssociation(HsvSource SpdifSource);\
friend class InterfaceParam<Comp,Nat32>;\
class Comp ## _ ## intf : public IHsvEuropeConfiguration \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,Nat32> m_InstallationCookie; \
    Comp ## _ ## intf( Comp *parent):m_InstallationCookie(parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetAutoStoreMode(void){ return m_parent->intf ## _GetAutoStoreMode();}\
virtual int GetMedium(void){ return m_parent->intf ## _GetMedium();}\
virtual void GetBreakOutSource(HsvSource * Source){ return m_parent->intf ## _GetBreakOutSource(Source);}\
virtual void GetBreakOutChannel(HsvChannel * ChannelNo){ return m_parent->intf ## _GetBreakOutChannel(ChannelNo);}\
virtual HsvSource GetDefaultSpdifAssociation(HsvSource SpdifSource){ return m_parent->intf ## _GetDefaultSpdifAssociation(SpdifSource);}\
virtual Nat32 InstallationCookie(void){ return m_InstallationCookie.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
