#ifndef IHSVTXTPACKET0_H
#define IHSVTXTPACKET0_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtPacket0
{
public:
	virtual ~IHsvTxtPacket0(){}
	virtual void GetLatestHeader(TxtPacket0 * pkt0ptr,Nat8 mag)= 0;
	virtual Bool GetLatestTime(Time * time_ptr)= 0;
};


#define IHsvTxtPacket0Impl(Comp,intf)    \
virtual void intf ## _GetLatestHeader(TxtPacket0 * pkt0ptr,Nat8 mag);\
virtual Bool intf ## _GetLatestTime(Time * time_ptr);\
class Comp ## _ ## intf : public IHsvTxtPacket0 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void GetLatestHeader(TxtPacket0 * pkt0ptr,Nat8 mag){ return m_parent->intf ## _GetLatestHeader(pkt0ptr,mag);}\
virtual Bool GetLatestTime(Time * time_ptr){ return m_parent->intf ## _GetLatestTime(time_ptr);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
