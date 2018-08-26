#ifndef IPLFAPICHANDECDVBC_H
#define IPLFAPICHANDECDVBC_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiChanDecDvbC
{
public:
	virtual ~IPlfApiChanDecDvbC(){}
	virtual FResult GetSymbolRateRange(int winid,Nat32 * MinSymbolRate,Nat32 * MaxSymbolRate,Nat32 * retval)= 0;
	virtual FResult SetSymbolRate(int winid,Nat32 rate,Nat32 * retval)= 0;
	virtual FResult GetSymbolRate(int winid,Nat32 * rate,Nat32 * retval)= 0;
	virtual FResult SetSearchRates(int winid,tmFe_SearchSymbolRate_t * SearchRate,Nat32 size,Nat32 * retval)= 0;
	virtual FResult SetFreqStep(int winid,Nat32 step,Nat32 * retval)= 0;
	virtual FResult GetFreqStep(int winid,Nat32 * step,Nat32 * retval)= 0;
};


#define IPlfApiChanDecDvbCImpl(Comp,intf)    \
virtual FResult intf ## _GetSymbolRateRange(int winid,Nat32 * MinSymbolRate,Nat32 * MaxSymbolRate,Nat32 * retval);\
virtual FResult intf ## _SetSymbolRate(int winid,Nat32 rate,Nat32 * retval);\
virtual FResult intf ## _GetSymbolRate(int winid,Nat32 * rate,Nat32 * retval);\
virtual FResult intf ## _SetSearchRates(int winid,tmFe_SearchSymbolRate_t * SearchRate,Nat32 size,Nat32 * retval);\
virtual FResult intf ## _SetFreqStep(int winid,Nat32 step,Nat32 * retval);\
virtual FResult intf ## _GetFreqStep(int winid,Nat32 * step,Nat32 * retval);\
class Comp ## _ ## intf : public IPlfApiChanDecDvbC \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult GetSymbolRateRange(int winid,Nat32 * MinSymbolRate,Nat32 * MaxSymbolRate,Nat32 * retval){ return m_parent->intf ## _GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval);}\
virtual FResult SetSymbolRate(int winid,Nat32 rate,Nat32 * retval){ return m_parent->intf ## _SetSymbolRate(winid,rate,retval);}\
virtual FResult GetSymbolRate(int winid,Nat32 * rate,Nat32 * retval){ return m_parent->intf ## _GetSymbolRate(winid,rate,retval);}\
virtual FResult SetSearchRates(int winid,tmFe_SearchSymbolRate_t * SearchRate,Nat32 size,Nat32 * retval){ return m_parent->intf ## _SetSearchRates(winid,SearchRate,size,retval);}\
virtual FResult SetFreqStep(int winid,Nat32 step,Nat32 * retval){ return m_parent->intf ## _SetFreqStep(winid,step,retval);}\
virtual FResult GetFreqStep(int winid,Nat32 * step,Nat32 * retval){ return m_parent->intf ## _GetFreqStep(winid,step,retval);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
