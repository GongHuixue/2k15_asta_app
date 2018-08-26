#ifndef IHSVSDMDIV_H
#define IHSVSDMDIV_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSdmDiv
{
public:
	virtual ~IHsvSdmDiv(){}
	virtual int NoOfVirtualChannels(int medium)= 0;
	virtual int NoOfDescriptors(void)= 0;
	virtual int NoOfEvents(void)= 0;
	
	virtual int MaxStringLength(void)= 0;
	
	virtual int RRTParsingAllowed(void)= 0;
	virtual Bool SystemTime(void)= 0;
	virtual int RatingStringLength(void)= 0;
	virtual Bool Enable12hourEitParsing(void)= 0;
	virtual int MaxPmtMonitors(void)= 0;
	virtual int ChannelNameLength(void)= 0;
	virtual int SystemLanguage(void)= 0;
	virtual Bool ForceLCNSyntax(int medium)= 0;
	virtual Bool EnableCountryFallbackForLCNSyntax(int medium)= 0;
	virtual Bool EnableONIDFallbackForLCNSyntax(int medium)= 0;
	virtual Bool SupportMultipleOriginalNetworkId(int medium)= 0;
	virtual Bool AcceptedStreamType(int medium,HsvAVStreamType StreamType)= 0;
	virtual Bool IsMpeg4STBoltOnSupported(void)= 0;
	virtual Bool IsAc3AudioSupported(void)= 0;
	virtual Bool ReapplyChildLockOnEventChange(void)= 0;
	virtual Bool IsAVCDescriptorSupported(void)= 0;
};


#define IHsvSdmDivImpl(Comp,intf)    \
virtual int intf ## _NoOfVirtualChannels(int medium);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _ForceLCNSyntax(int medium);\
virtual Bool intf ## _EnableCountryFallbackForLCNSyntax(int medium);\
virtual Bool intf ## _EnableONIDFallbackForLCNSyntax(int medium);\
virtual Bool intf ## _SupportMultipleOriginalNetworkId(int medium);\
virtual Bool intf ## _AcceptedStreamType(int medium,HsvAVStreamType StreamType);\
virtual Bool intf ## _IsMpeg4STBoltOnSupported(void);\
virtual Bool intf ## _IsAc3AudioSupported(void);\
virtual Bool intf ## _ReapplyChildLockOnEventChange(void);\
virtual Bool intf ## _IsAVCDescriptorSupported(void);\
class Comp ## _ ## intf : public IHsvSdmDiv \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_NoOfDescriptors; \
    InterfaceParam<Comp,int> m_NoOfEvents; \
    InterfaceParam<Comp,int> m_MaxStringLength; \
    InterfaceParam<Comp,int> m_RRTParsingAllowed; \
    InterfaceParam<Comp,Bool> m_SystemTime; \
    InterfaceParam<Comp,int> m_RatingStringLength; \
    InterfaceParam<Comp,Bool> m_Enable12hourEitParsing; \
    InterfaceParam<Comp,int> m_MaxPmtMonitors; \
    InterfaceParam<Comp,int> m_ChannelNameLength; \
    InterfaceParam<Comp,int> m_SystemLanguage; \
    Comp ## _ ## intf( Comp *parent):m_NoOfDescriptors(parent),m_NoOfEvents(parent),m_MaxStringLength(parent),m_RRTParsingAllowed(parent),m_SystemTime(parent),m_RatingStringLength(parent),m_Enable12hourEitParsing(parent),m_MaxPmtMonitors(parent),m_ChannelNameLength(parent),m_SystemLanguage(parent) \
    {\
        m_parent = parent;\
    }\
virtual int NoOfVirtualChannels(int medium){ return m_parent->intf ## _NoOfVirtualChannels(medium);}\
virtual int NoOfDescriptors(void){ return m_NoOfDescriptors.Call();}\
virtual int NoOfEvents(void){ return m_NoOfEvents.Call();}\
virtual int MaxStringLength(void){ return m_MaxStringLength.Call();}\
virtual int RRTParsingAllowed(void){ return m_RRTParsingAllowed.Call();}\
virtual Bool SystemTime(void){ return m_SystemTime.Call();}\
virtual int RatingStringLength(void){ return m_RatingStringLength.Call();}\
virtual Bool Enable12hourEitParsing(void){ return m_Enable12hourEitParsing.Call();}\
virtual int MaxPmtMonitors(void){ return m_MaxPmtMonitors.Call();}\
virtual int ChannelNameLength(void){ return m_ChannelNameLength.Call();}\
virtual int SystemLanguage(void){ return m_SystemLanguage.Call();}\
virtual Bool ForceLCNSyntax(int medium){ return m_parent->intf ## _ForceLCNSyntax(medium);}\
virtual Bool EnableCountryFallbackForLCNSyntax(int medium){ return m_parent->intf ## _EnableCountryFallbackForLCNSyntax(medium);}\
virtual Bool EnableONIDFallbackForLCNSyntax(int medium){ return m_parent->intf ## _EnableONIDFallbackForLCNSyntax(medium);}\
virtual Bool SupportMultipleOriginalNetworkId(int medium){ return m_parent->intf ## _SupportMultipleOriginalNetworkId(medium);}\
virtual Bool AcceptedStreamType(int medium,HsvAVStreamType StreamType){ return m_parent->intf ## _AcceptedStreamType(medium,StreamType);}\
virtual Bool IsMpeg4STBoltOnSupported(void){ return m_parent->intf ## _IsMpeg4STBoltOnSupported();}\
virtual Bool IsAc3AudioSupported(void){ return m_parent->intf ## _IsAc3AudioSupported();}\
virtual Bool ReapplyChildLockOnEventChange(void){ return m_parent->intf ## _ReapplyChildLockOnEventChange();}\
virtual Bool IsAVCDescriptorSupported(void){ return m_parent->intf ## _IsAVCDescriptorSupported();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
