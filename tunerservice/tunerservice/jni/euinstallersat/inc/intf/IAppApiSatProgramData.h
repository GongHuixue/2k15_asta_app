#ifndef IAPPAPISATPROGRAMDATA_H
#define IAPPAPISATPROGRAMDATA_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramData
{
public:
	virtual ~IAppApiSatProgramData(){}
	virtual int StringChannelName(void)= 0;
	virtual int IntFrequency(void)= 0;
	virtual int IntPtc(void)= 0;
	virtual int IntNetworkId(void)= 0;
	virtual int IntOriginalNetworkId(void)= 0;
	virtual int IntTsid(void)= 0;
	virtual int IntServiceId(void)= 0;
	virtual int BoolFreeCiMode(void)= 0;
	#define IAppApiSatProgramData_DecoderNone		((int)0 )
	#define IAppApiSatProgramData_DecoderExt1		((int)1 )
	#define IAppApiSatProgramData_DecoderExt2		((int)2 )
	virtual Bool IsAttributeSupported(int attribute)= 0;
	virtual AppApiReturnCode GetChannelDataInt(AppApiChannel channel,int dataid,int * value)= 0;
	virtual AppApiReturnCode GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value)= 0;
	virtual AppApiReturnCode GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size)= 0;
	virtual AppApiReturnCode GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc_or_Freq)= 0;
};


#define IAppApiSatProgramDataImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsAttributeSupported(int attribute);\
virtual AppApiReturnCode intf ## _GetChannelDataInt(AppApiChannel channel,int dataid,int * value);\
virtual AppApiReturnCode intf ## _GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value);\
virtual AppApiReturnCode intf ## _GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size);\
virtual AppApiReturnCode intf ## _GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc_or_Freq);\
class Comp ## _ ## intf : public IAppApiSatProgramData \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_StringChannelName; \
    InterfaceParam<Comp,int> m_IntFrequency; \
    InterfaceParam<Comp,int> m_IntPtc; \
    InterfaceParam<Comp,int> m_IntNetworkId; \
    InterfaceParam<Comp,int> m_IntOriginalNetworkId; \
    InterfaceParam<Comp,int> m_IntTsid; \
    InterfaceParam<Comp,int> m_IntServiceId; \
    InterfaceParam<Comp,int> m_BoolFreeCiMode; \
    Comp ## _ ## intf( Comp *parent):m_StringChannelName(parent),m_IntFrequency(parent),m_IntPtc(parent),m_IntNetworkId(parent),m_IntOriginalNetworkId(parent),m_IntTsid(parent),m_IntServiceId(parent),m_BoolFreeCiMode(parent) \
    {\
        m_parent = parent;\
    }\
virtual int StringChannelName(void){ return m_StringChannelName.Call();}\
virtual int IntFrequency(void){ return m_IntFrequency.Call();}\
virtual int IntPtc(void){ return m_IntPtc.Call();}\
virtual int IntNetworkId(void){ return m_IntNetworkId.Call();}\
virtual int IntOriginalNetworkId(void){ return m_IntOriginalNetworkId.Call();}\
virtual int IntTsid(void){ return m_IntTsid.Call();}\
virtual int IntServiceId(void){ return m_IntServiceId.Call();}\
virtual int BoolFreeCiMode(void){ return m_BoolFreeCiMode.Call();}\
virtual Bool IsAttributeSupported(int attribute){ return m_parent->intf ## _IsAttributeSupported(attribute);}\
virtual AppApiReturnCode GetChannelDataInt(AppApiChannel channel,int dataid,int * value){ return m_parent->intf ## _GetChannelDataInt(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value){ return m_parent->intf ## _GetChannelDataBool(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size){ return m_parent->intf ## _GetChannelDataString(channel,dataid,value,size);}\
virtual AppApiReturnCode GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc_or_Freq){ return m_parent->intf ## _GetDigitalChannel(channel,OnId,TsId,Sid,Ptc_or_Freq);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
