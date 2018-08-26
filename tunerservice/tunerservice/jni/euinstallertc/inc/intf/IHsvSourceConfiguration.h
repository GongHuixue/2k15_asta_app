#ifndef IHSVSOURCECONFIGURATION_H
#define IHSVSOURCECONFIGURATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSourceConfiguration
{
public:
	virtual ~IHsvSourceConfiguration(){}
	virtual int iVersion(void)= 0;
	virtual int NoOfSources(void)= 0;
	virtual HsvSource* SourceList(void)= 0;
	#define IHsvSourceConfiguration_AnalogTuner		((int)1 )
	#define IHsvSourceConfiguration_DigitalTuner		((int)2 )
	#define IHsvSourceConfiguration_AnalogExtension		((int)4 )
	#define IHsvSourceConfiguration_DigitalExtension		((int)8 )
	#define IHsvSourceConfiguration_ServiceDefaultSource		((int)16 )
	#define IHsvSourceConfiguration_InvalidSrcType		((int)32 )
	#define IHsvSourceConfiguration_None		((Nat8)0xFF )
	#define IHsvSourceConfiguration_Ext1		((Nat8)1 )
	#define IHsvSourceConfiguration_Ext2		((Nat8)2 )
	#define IHsvSourceConfiguration_Ext3		((Nat8)3 )
	#define IHsvSourceConfiguration_Side		((Nat8)4 )
	#define IHsvSourceConfiguration_Hdmi1		((Nat8)5 )
	#define IHsvSourceConfiguration_Hdmi2		((Nat8)6 )
	#define IHsvSourceConfiguration_Hdmi3		((Nat8)7 )
	#define IHsvSourceConfiguration_Hdmi4		((Nat8)8 )
	#define IHsvSourceConfiguration_Hdmi5		((Nat8)9 )
	virtual int GetSourceType(HsvSource source)= 0;
	virtual HsvModulationType GetModulationType(HsvSource source)= 0;
	virtual HsvStreamType GetStreamType(HsvSource source)= 0;
	virtual Bool IsSourceSupported(HsvSource source)= 0;
	virtual Bool IsSourceLockable(HsvSource source)= 0;
	virtual Bool IsMultiProgram(HsvSource source)= 0;
	virtual Bool IsSourceViewable(HsvSource source)= 0;
	virtual Bool IsPropertySupported(HsvSource source,tmConnMgrHybridPlf_InputDesignatorSet_t property)= 0;
	virtual tmConnMgrHybridPlf_InputDesignatorSet_t GetSourceProperty(HsvSource source)= 0;
	virtual tmConnMgrHybridPlf_Input_t ConvertToPlfSource(HsvSource source)= 0;
	virtual HsvSource ConvertToUsrSource(tmConnMgrHybridPlf_Input_t plfsource)= 0;
	virtual Bool GetPhysicalAddress(HsvSource source,Nat8 * phyAddr)= 0;
	virtual HsvSource ConvertToHsvSource(Nat8 Ext)= 0;
};


#define IHsvSourceConfigurationImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,HsvSource*>;\
virtual int intf ## _GetSourceType(HsvSource source);\
virtual HsvModulationType intf ## _GetModulationType(HsvSource source);\
virtual HsvStreamType intf ## _GetStreamType(HsvSource source);\
virtual Bool intf ## _IsSourceSupported(HsvSource source);\
virtual Bool intf ## _IsSourceLockable(HsvSource source);\
virtual Bool intf ## _IsMultiProgram(HsvSource source);\
virtual Bool intf ## _IsSourceViewable(HsvSource source);\
virtual Bool intf ## _IsPropertySupported(HsvSource source,tmConnMgrHybridPlf_InputDesignatorSet_t property);\
virtual tmConnMgrHybridPlf_InputDesignatorSet_t intf ## _GetSourceProperty(HsvSource source);\
virtual tmConnMgrHybridPlf_Input_t intf ## _ConvertToPlfSource(HsvSource source);\
virtual HsvSource intf ## _ConvertToUsrSource(tmConnMgrHybridPlf_Input_t plfsource);\
virtual Bool intf ## _GetPhysicalAddress(HsvSource source,Nat8 * phyAddr);\
virtual HsvSource intf ## _ConvertToHsvSource(Nat8 Ext);\
class Comp ## _ ## intf : public IHsvSourceConfiguration \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_iVersion; \
    InterfaceParam<Comp,int> m_NoOfSources; \
    InterfaceParam<Comp,HsvSource*> m_SourceList; \
    Comp ## _ ## intf( Comp *parent):m_iVersion(parent),m_NoOfSources(parent),m_SourceList(parent) \
    {\
        m_parent = parent;\
    }\
virtual int iVersion(void){ return m_iVersion.Call();}\
virtual int NoOfSources(void){ return m_NoOfSources.Call();}\
virtual HsvSource* SourceList(void){ return m_SourceList.Call();}\
virtual int GetSourceType(HsvSource source){ return m_parent->intf ## _GetSourceType(source);}\
virtual HsvModulationType GetModulationType(HsvSource source){ return m_parent->intf ## _GetModulationType(source);}\
virtual HsvStreamType GetStreamType(HsvSource source){ return m_parent->intf ## _GetStreamType(source);}\
virtual Bool IsSourceSupported(HsvSource source){ return m_parent->intf ## _IsSourceSupported(source);}\
virtual Bool IsSourceLockable(HsvSource source){ return m_parent->intf ## _IsSourceLockable(source);}\
virtual Bool IsMultiProgram(HsvSource source){ return m_parent->intf ## _IsMultiProgram(source);}\
virtual Bool IsSourceViewable(HsvSource source){ return m_parent->intf ## _IsSourceViewable(source);}\
virtual Bool IsPropertySupported(HsvSource source,tmConnMgrHybridPlf_InputDesignatorSet_t property){ return m_parent->intf ## _IsPropertySupported(source,property);}\
virtual tmConnMgrHybridPlf_InputDesignatorSet_t GetSourceProperty(HsvSource source){ return m_parent->intf ## _GetSourceProperty(source);}\
virtual tmConnMgrHybridPlf_Input_t ConvertToPlfSource(HsvSource source){ return m_parent->intf ## _ConvertToPlfSource(source);}\
virtual HsvSource ConvertToUsrSource(tmConnMgrHybridPlf_Input_t plfsource){ return m_parent->intf ## _ConvertToUsrSource(plfsource);}\
virtual Bool GetPhysicalAddress(HsvSource source,Nat8 * phyAddr){ return m_parent->intf ## _GetPhysicalAddress(source,phyAddr);}\
virtual HsvSource ConvertToHsvSource(Nat8 Ext){ return m_parent->intf ## _ConvertToHsvSource(Ext);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
