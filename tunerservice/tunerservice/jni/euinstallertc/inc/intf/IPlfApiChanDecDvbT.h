#ifndef IPLFAPICHANDECDVBT_H
#define IPLFAPICHANDECDVBT_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiChanDecDvbT
{
public:
	virtual ~IPlfApiChanDecDvbT(){}
	virtual FResult SetChanBandwidth(int winid,tmFe_ChanBandwidth_t bandwidth,Nat32 * retval)= 0;
	virtual FResult GetActualChanBandwidth(int winid,tmFe_ChanBandwidth_t * Bandwidth,Nat32 * retval)= 0;
	virtual FResult SetStreamPriority(int winid,tmFe_StreamPriority_t streamPriority,Nat32 * retval)= 0;
	virtual FResult GetStreamPriority(int winid,tmFe_StreamPriority_t * streamPriority,Nat32 * retval)= 0;
	virtual FResult GetHierarchyMuxPresence(int winid,Bool * HierarchymodePresent,Nat32 * retval)= 0;
	virtual FResult GetTPSId(int winid, HsvDvbTParams* TPSId, Nat32* retval )=0;
};


#define IPlfApiChanDecDvbTImpl(Comp,intf)    \
virtual FResult intf ## _SetChanBandwidth(int winid,tmFe_ChanBandwidth_t bandwidth,Nat32 * retval);\
virtual FResult intf ## _GetActualChanBandwidth(int winid,tmFe_ChanBandwidth_t * Bandwidth,Nat32 * retval);\
virtual FResult intf ## _SetStreamPriority(int winid,tmFe_StreamPriority_t streamPriority,Nat32 * retval);\
virtual FResult intf ## _GetStreamPriority(int winid,tmFe_StreamPriority_t * streamPriority,Nat32 * retval);\
virtual FResult intf ## _GetHierarchyMuxPresence(int winid,Bool * HierarchymodePresent,Nat32 * retval);\
virtual FResult intf ## _GetTPSId(int winid, HsvDvbTParams* TPSId, Nat32* retval );\
class Comp ## _ ## intf : public IPlfApiChanDecDvbT \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult SetChanBandwidth(int winid,tmFe_ChanBandwidth_t bandwidth,Nat32 * retval){ return m_parent->intf ## _SetChanBandwidth(winid,bandwidth,retval);}\
virtual FResult GetActualChanBandwidth(int winid,tmFe_ChanBandwidth_t * Bandwidth,Nat32 * retval){ return m_parent->intf ## _GetActualChanBandwidth(winid,Bandwidth,retval);}\
virtual FResult SetStreamPriority(int winid,tmFe_StreamPriority_t streamPriority,Nat32 * retval){ return m_parent->intf ## _SetStreamPriority(winid,streamPriority,retval);}\
virtual FResult GetStreamPriority(int winid,tmFe_StreamPriority_t * streamPriority,Nat32 * retval){ return m_parent->intf ## _GetStreamPriority(winid,streamPriority,retval);}\
virtual FResult GetHierarchyMuxPresence(int winid,Bool * HierarchymodePresent,Nat32 * retval){ return m_parent->intf ## _GetHierarchyMuxPresence(winid,HierarchymodePresent,retval);}\
virtual FResult GetTPSId(int winid, HsvDvbTParams* TPSId, Nat32* retval ){ return m_parent->intf ## _GetTPSId(winid,TPSId,retval);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
