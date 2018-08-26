#ifndef IPLFAPICHANDECDVBT2_H
#define IPLFAPICHANDECDVBT2_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiChanDecDvbT2
{
public:
	virtual ~IPlfApiChanDecDvbT2(){}
	#define IPlfApiChanDecDvbT2_PlpIdAuto		((int)-1 )
	#define IPlfApiChanDecDvbT2_AdvSigTFS		((int)0x0001 )
	#define IPlfApiChanDecDvbT2_AdvSigFEF		((int)0x0002 )
	#define IPlfApiChanDecDvbT2_AdvSigAuxStream		((int)0x0004 )
	#define IPlfApiChanDecDvbT2_AdvSigGSE		((int)0x0008 )
	#define IPlfApiChanDecDvbT2_AdvSigGCS		((int)0x0010 )
	#define IPlfApiChanDecDvbT2_AdvSigGFPS		((int)0x0020 )
	#define IPlfApiChanDecDvbT2_AdvSigFuturePayloadType		((int)0x0040 )
	#define IPlfApiChanDecDvbT2_AdvSigMISO		((int)0x0080 )
	#define IPlfApiChanDecDvbT2_AdvSigS1Future		((int)0x0100 )
	#define IPlfApiChanDecDvbT2_AdvSigT2FutureVersion		((int)0x0200 )
	#define IPlfApiChanDecDvbT2_AdvSigFuturePlpType		((int)0x0400 )
	#define IPlfApiChanDecDvbT2_AdvSigL1Change		((int)0x0800 )
	#define IPlfApiChanDecDvbT2_SigPropSinglePlp		((int)0x00000001 )
	#define IPlfApiChanDecDvbT2_SigPropIQ		((int)0x00000002 )
	#define IPlfApiChanDecDvbT2_MaxPlp		((int)256 )
	virtual FResult GetT2CarrierPresent(int winid,Bool * Present)= 0;
	virtual FResult GetActivePlpId(int winid,int * plpid)= 0;
	virtual FResult SelectPlpId(int winid,int plpid)= 0;
	virtual FResult GetDetectedPlpIds(int winid,int * nrOfIds,int * plpids)= 0;
};


#define IPlfApiChanDecDvbT2Impl(Comp,intf)    \
virtual FResult intf ## _GetT2CarrierPresent(int winid,Bool * Present);\
virtual FResult intf ## _GetActivePlpId(int winid,int * plpid);\
virtual FResult intf ## _SelectPlpId(int winid,int plpid);\
virtual FResult intf ## _GetDetectedPlpIds(int winid,int * nrOfIds,int * plpids);\
class Comp ## _ ## intf : public IPlfApiChanDecDvbT2 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult GetT2CarrierPresent(int winid,Bool * Present){ return m_parent->intf ## _GetT2CarrierPresent(winid,Present);}\
virtual FResult GetActivePlpId(int winid,int * plpid){ return m_parent->intf ## _GetActivePlpId(winid,plpid);}\
virtual FResult SelectPlpId(int winid,int plpid){ return m_parent->intf ## _SelectPlpId(winid,plpid);}\
virtual FResult GetDetectedPlpIds(int winid,int * nrOfIds,int * plpids){ return m_parent->intf ## _GetDetectedPlpIds(winid,nrOfIds,plpids);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
