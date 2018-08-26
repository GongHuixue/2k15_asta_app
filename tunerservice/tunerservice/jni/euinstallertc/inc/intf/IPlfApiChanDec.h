#ifndef IPLFAPICHANDEC_H
#define IPLFAPICHANDEC_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiChanDec
{
public:
	virtual ~IPlfApiChanDec(){}
	virtual FResult GetActualConstellation(int winid,int decoder,tmFe_Constellation_t * pConstellation,Nat32 * retval)= 0;
	virtual FResult SetConstellation(int winid,int decoder,tmFe_Constellation_t constellation,Nat32 * retval)= 0;
	virtual FResult GetCarrierPresent(int winid,Bool * Present,Nat32 * retval)= 0;
	virtual FResult GetBer(int winid,int decoder,Nat32 * Ber)= 0;
};


#define IPlfApiChanDecImpl(Comp,intf)    \
virtual FResult intf ## _GetActualConstellation(int winid,int decoder,tmFe_Constellation_t * pConstellation,Nat32 * retval);\
virtual FResult intf ## _SetConstellation(int winid,int decoder,tmFe_Constellation_t constellation,Nat32 * retval);\
virtual FResult intf ## _GetCarrierPresent(int winid,Bool * Present,Nat32 * retval);\
virtual FResult intf ## _GetBer(int winid,int decoder,Nat32 * Ber);\
class Comp ## _ ## intf : public IPlfApiChanDec \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult GetActualConstellation(int winid,int decoder,tmFe_Constellation_t * pConstellation,Nat32 * retval){ return m_parent->intf ## _GetActualConstellation(winid,decoder,pConstellation,retval);}\
virtual FResult SetConstellation(int winid,int decoder,tmFe_Constellation_t constellation,Nat32 * retval){ return m_parent->intf ## _SetConstellation(winid,decoder,constellation,retval);}\
virtual FResult GetCarrierPresent(int winid,Bool * Present,Nat32 * retval){ return m_parent->intf ## _GetCarrierPresent(winid,Present,retval);}\
virtual FResult GetBer(int winid,int decoder,Nat32 * Ber){ return m_parent->intf ## _GetBer(winid,decoder,Ber);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
