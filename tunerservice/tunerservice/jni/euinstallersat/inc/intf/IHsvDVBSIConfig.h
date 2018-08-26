#ifndef IHSVDVBSICONFIG_H
#define IHSVDVBSICONFIG_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDVBSIConfig
{
public:
	virtual ~IHsvDVBSIConfig(){}
	#define IHsvDVBSIConfig_NitActualParsing		((int)0x0001 )
	#define IHsvDVBSIConfig_NitOtherParsing		((int)0x0002 )
	#define IHsvDVBSIConfig_SdtActualParsing		((int)0x0004 )
	#define IHsvDVBSIConfig_SdtOtherParsing		((int)0x0008 )
	#define IHsvDVBSIConfig_EitNowNextActualParsing		((int)0x0010 )
	#define IHsvDVBSIConfig_EitNowNextOtherParsing		((int)0x0020 )
	#define IHsvDVBSIConfig_EitSchedActualParsing		((int)0x0040 )
	#define IHsvDVBSIConfig_EitSchedOtherParsing		((int)0x0080 )
	#define IHsvDVBSIConfig_TdtParsing		((int)0x0100 )
	#define IHsvDVBSIConfig_TotParsing		((int)0x0200 )
	#define IHsvDVBSIConfig_BatParsing		((int)0x0400 )
	#define IHsvDVBSIConfig_FntParsing		((int)0x0800 )
	#define IHsvDVBSIConfig_FstParsing		((int)0x1000 )
	#define IHsvDVBSIConfig_PostcodeParsing		((int)0x2000 )
	#define IHsvDVBSIConfig_SgtParsing		((int)0x4000 )
	#define IHsvDVBSIConfig_Notifications		((int)0x8000 )
	virtual int CurrentCountry(void)= 0;
	virtual Bool IsActionAllowed(HsvDemux dmx,int table)= 0;
};


#define IHsvDVBSIConfigImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsActionAllowed(HsvDemux dmx,int table);\
class Comp ## _ ## intf : public IHsvDVBSIConfig \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_CurrentCountry; \
    Comp ## _ ## intf( Comp *parent):m_CurrentCountry(parent) \
    {\
        m_parent = parent;\
    }\
virtual int CurrentCountry(void){ return m_CurrentCountry.Call();}\
virtual Bool IsActionAllowed(HsvDemux dmx,int table){ return m_parent->intf ## _IsActionAllowed(dmx,table);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
