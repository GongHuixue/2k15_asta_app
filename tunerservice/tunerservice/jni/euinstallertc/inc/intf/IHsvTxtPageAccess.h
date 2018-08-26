#ifndef IHSVTXTPAGEACCESS_H
#define IHSVTXTPAGEACCESS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtPageAccess
{
public:
	virtual ~IHsvTxtPageAccess(){}
	virtual TxtPageHandle OpenPageForRead(PageNr page,Subcode subcode)= 0;
	virtual void ClosePage(TxtPageHandle hnd)= 0;
	virtual Nat8* GetPacket(TxtPageHandle hnd,PacketNumber pkt_num)= 0;
};


#define IHsvTxtPageAccessImpl(Comp,intf)    \
virtual TxtPageHandle intf ## _OpenPageForRead(PageNr page,Subcode subcode);\
virtual void intf ## _ClosePage(TxtPageHandle hnd);\
virtual Nat8* intf ## _GetPacket(TxtPageHandle hnd,PacketNumber pkt_num);\
class Comp ## _ ## intf : public IHsvTxtPageAccess \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual TxtPageHandle OpenPageForRead(PageNr page,Subcode subcode){ return m_parent->intf ## _OpenPageForRead(page,subcode);}\
virtual void ClosePage(TxtPageHandle hnd){ return m_parent->intf ## _ClosePage(hnd);}\
virtual Nat8* GetPacket(TxtPageHandle hnd,PacketNumber pkt_num){ return m_parent->intf ## _GetPacket(hnd,pkt_num);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
