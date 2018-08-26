#ifndef IHSVMPEGSERVICES_H
#define IHSVMPEGSERVICES_H
#include <intfparam.h>
#include <provreq.h>
class IHsvMpegServices
{
public:
	virtual ~IHsvMpegServices(){}
	virtual int GetLanguageId(char byte1,char byte2,char byte3)= 0;
	virtual Bool IsProgramPresent(HsvDemux dmx,int prg)= 0;
	virtual void ReadTsPacketFields(Nat32 subscr_id,HsvSdmTsSection * sec)= 0;
	virtual void* GetCcDescriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed)= 0;
	virtual void* GetCaDescriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed)= 0;
	virtual void* GetAc3Descriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed)= 0;
};


#define IHsvMpegServicesImpl(Comp,intf)    \
virtual int intf ## _GetLanguageId(char byte1,char byte2,char byte3);\
virtual Bool intf ## _IsProgramPresent(HsvDemux dmx,int prg);\
virtual void intf ## _ReadTsPacketFields(Nat32 subscr_id,HsvSdmTsSection * sec);\
virtual void* intf ## _GetCcDescriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed);\
virtual void* intf ## _GetCaDescriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed);\
virtual void* intf ## _GetAc3Descriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed);\
class Comp ## _ ## intf : public IHsvMpegServices \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetLanguageId(char byte1,char byte2,char byte3){ return m_parent->intf ## _GetLanguageId(byte1,byte2,byte3);}\
virtual Bool IsProgramPresent(HsvDemux dmx,int prg){ return m_parent->intf ## _IsProgramPresent(dmx,prg);}\
virtual void ReadTsPacketFields(Nat32 subscr_id,HsvSdmTsSection * sec){ return m_parent->intf ## _ReadTsPacketFields(subscr_id,sec);}\
virtual void* GetCcDescriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed){ return m_parent->intf ## _GetCcDescriptor(dmx,prg,IsDescriptorParsed);}\
virtual void* GetCaDescriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed){ return m_parent->intf ## _GetCaDescriptor(dmx,prg,IsDescriptorParsed);}\
virtual void* GetAc3Descriptor(HsvDemux dmx,int prg,Bool * IsDescriptorParsed){ return m_parent->intf ## _GetAc3Descriptor(dmx,prg,IsDescriptorParsed);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
