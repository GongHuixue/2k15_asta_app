#ifndef IPLFAPICHANDECSELECT_H
#define IPLFAPICHANDECSELECT_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiChanDecSelect
{
public:
	virtual ~IPlfApiChanDecSelect(){}
	#define IPlfApiChanDecSelect_ChanDecDvbT		((Nat32)0x01 )
	#define IPlfApiChanDecSelect_ChanDecDvbC		((Nat32)0x02 )
	#define IPlfApiChanDecSelect_ChanDecDvbS		((Nat32)0x04 )
	#define IPlfApiChanDecSelect_ChanDecISDBT		((Nat32)0x08 )
	#define IPlfApiChanDecSelect_ChanDecDvbT2		((Nat32)0x10 )
	#define IPlfApiChanDecSelect_ChanDecDvbC2		((Nat32)0x20 )
	virtual FResult SetChanDec(int winid,Nat32 decoder)= 0;
	virtual FResult GetChanDec(int winid,Nat32 * decoder)= 0;
	virtual FResult IsChanDecSupported(int winid,Nat32 decoder,Nat32 * retval)= 0;
};


#define IPlfApiChanDecSelectImpl(Comp,intf)    \
virtual FResult intf ## _SetChanDec(int winid,Nat32 decoder);\
virtual FResult intf ## _GetChanDec(int winid,Nat32 * decoder);\
virtual FResult intf ## _IsChanDecSupported(int winid,Nat32 decoder,Nat32 * retval);\
class Comp ## _ ## intf : public IPlfApiChanDecSelect \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult SetChanDec(int winid,Nat32 decoder){ return m_parent->intf ## _SetChanDec(winid,decoder);}\
virtual FResult GetChanDec(int winid,Nat32 * decoder){ return m_parent->intf ## _GetChanDec(winid,decoder);}\
virtual FResult IsChanDecSupported(int winid,Nat32 decoder,Nat32 * retval){ return m_parent->intf ## _IsChanDecSupported(winid,decoder,retval);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
