#ifndef ICETVTSDMXCONTROL_H
#define ICETVTSDMXCONTROL_H
#include <intfparam.h>
#include <provreq.h>
class ICetvTsDmxControl
{
public:
	virtual ~ICetvTsDmxControl(){}
	virtual int StreamTypeInvalid(void)= 0;
	virtual int StreamTypemp1v(void)= 0;
	virtual int StreamTypemp2v(void)= 0;
	virtual int StreamTypemp4v(void)= 0;
	virtual int StreamTypemp1a(void)= 0;
	virtual int StreamTypemp2a(void)= 0;
	virtual int StreamTypemp4a(void)= 0;
	virtual int StreamTypettxt(void)= 0;
	virtual int StreamTypesubt(void)= 0;
	virtual int StreamTypepcr(void)= 0;
	virtual int StreamTypeac3(void)= 0;
	virtual int StreamTypeh264(void)= 0;
	virtual int StreamTypedivx(void)= 0;
	virtual int StreamTypevc1(void)= 0;
	virtual int StreamTypeaac(void)= 0;
	virtual int StreamTypewma(void)= 0;
	virtual int StreamTypeOther(void)= 0;
	virtual Bool IsStreamTypeSupported(int streamtype)= 0;
	virtual void SetPid(int pid,int streamtype)= 0;
	virtual int GetPid(void)= 0;
	virtual int GetStreamType(void)= 0;
	virtual void StartDemux(void)= 0;
	virtual void StopDemux(void)= 0;
	virtual Bool GetScramblingStatus(void)= 0;
};


#define ICetvTsDmxControlImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsStreamTypeSupported(int streamtype);\
virtual void intf ## _SetPid(int pid,int streamtype);\
virtual int intf ## _GetPid(void);\
virtual int intf ## _GetStreamType(void);\
virtual void intf ## _StartDemux(void);\
virtual void intf ## _StopDemux(void);\
virtual Bool intf ## _GetScramblingStatus(void);\
class Comp ## _ ## intf : public ICetvTsDmxControl \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_StreamTypeInvalid; \
    InterfaceParam<Comp,int> m_StreamTypemp1v; \
    InterfaceParam<Comp,int> m_StreamTypemp2v; \
    InterfaceParam<Comp,int> m_StreamTypemp4v; \
    InterfaceParam<Comp,int> m_StreamTypemp1a; \
    InterfaceParam<Comp,int> m_StreamTypemp2a; \
    InterfaceParam<Comp,int> m_StreamTypemp4a; \
    InterfaceParam<Comp,int> m_StreamTypettxt; \
    InterfaceParam<Comp,int> m_StreamTypesubt; \
    InterfaceParam<Comp,int> m_StreamTypepcr; \
    InterfaceParam<Comp,int> m_StreamTypeac3; \
    InterfaceParam<Comp,int> m_StreamTypeh264; \
    InterfaceParam<Comp,int> m_StreamTypedivx; \
    InterfaceParam<Comp,int> m_StreamTypevc1; \
    InterfaceParam<Comp,int> m_StreamTypeaac; \
    InterfaceParam<Comp,int> m_StreamTypewma; \
    InterfaceParam<Comp,int> m_StreamTypeOther; \
    Comp ## _ ## intf( Comp *parent):m_StreamTypeInvalid(parent),m_StreamTypemp1v(parent),m_StreamTypemp2v(parent),m_StreamTypemp4v(parent),m_StreamTypemp1a(parent),m_StreamTypemp2a(parent),m_StreamTypemp4a(parent),m_StreamTypettxt(parent),m_StreamTypesubt(parent),m_StreamTypepcr(parent),m_StreamTypeac3(parent),m_StreamTypeh264(parent),m_StreamTypedivx(parent),m_StreamTypevc1(parent),m_StreamTypeaac(parent),m_StreamTypewma(parent),m_StreamTypeOther(parent) \
    {\
        m_parent = parent;\
    }\
virtual int StreamTypeInvalid(void){ return m_StreamTypeInvalid.Call();}\
virtual int StreamTypemp1v(void){ return m_StreamTypemp1v.Call();}\
virtual int StreamTypemp2v(void){ return m_StreamTypemp2v.Call();}\
virtual int StreamTypemp4v(void){ return m_StreamTypemp4v.Call();}\
virtual int StreamTypemp1a(void){ return m_StreamTypemp1a.Call();}\
virtual int StreamTypemp2a(void){ return m_StreamTypemp2a.Call();}\
virtual int StreamTypemp4a(void){ return m_StreamTypemp4a.Call();}\
virtual int StreamTypettxt(void){ return m_StreamTypettxt.Call();}\
virtual int StreamTypesubt(void){ return m_StreamTypesubt.Call();}\
virtual int StreamTypepcr(void){ return m_StreamTypepcr.Call();}\
virtual int StreamTypeac3(void){ return m_StreamTypeac3.Call();}\
virtual int StreamTypeh264(void){ return m_StreamTypeh264.Call();}\
virtual int StreamTypedivx(void){ return m_StreamTypedivx.Call();}\
virtual int StreamTypevc1(void){ return m_StreamTypevc1.Call();}\
virtual int StreamTypeaac(void){ return m_StreamTypeaac.Call();}\
virtual int StreamTypewma(void){ return m_StreamTypewma.Call();}\
virtual int StreamTypeOther(void){ return m_StreamTypeOther.Call();}\
virtual Bool IsStreamTypeSupported(int streamtype){ return m_parent->intf ## _IsStreamTypeSupported(streamtype);}\
virtual void SetPid(int pid,int streamtype){ return m_parent->intf ## _SetPid(pid,streamtype);}\
virtual int GetPid(void){ return m_parent->intf ## _GetPid();}\
virtual int GetStreamType(void){ return m_parent->intf ## _GetStreamType();}\
virtual void StartDemux(void){ return m_parent->intf ## _StartDemux();}\
virtual void StopDemux(void){ return m_parent->intf ## _StopDemux();}\
virtual Bool GetScramblingStatus(void){ return m_parent->intf ## _GetScramblingStatus();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
