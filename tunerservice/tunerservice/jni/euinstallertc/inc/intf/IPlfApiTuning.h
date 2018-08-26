#ifndef IPLFAPITUNING_H
#define IPLFAPITUNING_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiTuning
{
public:
	virtual ~IPlfApiTuning(){}
	virtual FResult GetFreqRange(int winid,Nat32 * MinFreq,Nat32 * MaxFreq,Nat32 * retval)= 0;
	virtual FResult GetFreq(int winid,Nat32 * Freq,Nat32 * retval)= 0;
	virtual FResult SetFreq(int winid,Nat32 freq,Bool finetune,Nat32 * retval)= 0;
	virtual FResult GetTvSystemSupp(int winid,tmFe_TvSystem_t tvSystem,Bool * Supp,Nat32 * retval)= 0;
	virtual FResult GetTvSystem(int winid,tmFe_TvSystem_t * TvSystem,Nat32 * retval)= 0;
	virtual FResult SetTvSystem(int winid,tmFe_TvSystem_t TvSystem,Nat32 * retval)= 0;
	virtual FResult StartSearch(int winid,Nat32 startFreq,tmFe_SearchMode_t mode,Nat32 endFreq,Nat32 * retval)= 0;
	virtual FResult StopSearch(int winid,Nat32 * retval)= 0;
	#define IPlfApiTuning_WaitforAbort	((Nat32)0 )
	#define IPlfApiTuning_SearchStopped	((Nat32)1 )

};


#define IPlfApiTuningImpl(Comp,intf)    \
virtual FResult intf ## _GetFreqRange(int winid,Nat32 * MinFreq,Nat32 * MaxFreq,Nat32 * retval);\
virtual FResult intf ## _GetFreq(int winid,Nat32 * Freq,Nat32 * retval);\
virtual FResult intf ## _SetFreq(int winid,Nat32 freq,Bool finetune,Nat32 * retval);\
virtual FResult intf ## _GetTvSystemSupp(int winid,tmFe_TvSystem_t tvSystem,Bool * Supp,Nat32 * retval);\
virtual FResult intf ## _GetTvSystem(int winid,tmFe_TvSystem_t * TvSystem,Nat32 * retval);\
virtual FResult intf ## _SetTvSystem(int winid,tmFe_TvSystem_t TvSystem,Nat32 * retval);\
virtual FResult intf ## _StartSearch(int winid,Nat32 startFreq,tmFe_SearchMode_t mode,Nat32 endFreq,Nat32 * retval);\
virtual FResult intf ## _StopSearch(int winid,Nat32 * retval);\
class Comp ## _ ## intf : public IPlfApiTuning \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult GetFreqRange(int winid,Nat32 * MinFreq,Nat32 * MaxFreq,Nat32 * retval){ return m_parent->intf ## _GetFreqRange(winid,MinFreq,MaxFreq,retval);}\
virtual FResult GetFreq(int winid,Nat32 * Freq,Nat32 * retval){ return m_parent->intf ## _GetFreq(winid,Freq,retval);}\
virtual FResult SetFreq(int winid,Nat32 freq,Bool finetune,Nat32 * retval){ return m_parent->intf ## _SetFreq(winid,freq,finetune,retval);}\
virtual FResult GetTvSystemSupp(int winid,tmFe_TvSystem_t tvSystem,Bool * Supp,Nat32 * retval){ return m_parent->intf ## _GetTvSystemSupp(winid,tvSystem,Supp,retval);}\
virtual FResult GetTvSystem(int winid,tmFe_TvSystem_t * TvSystem,Nat32 * retval){ return m_parent->intf ## _GetTvSystem(winid,TvSystem,retval);}\
virtual FResult SetTvSystem(int winid,tmFe_TvSystem_t TvSystem,Nat32 * retval){ return m_parent->intf ## _SetTvSystem(winid,TvSystem,retval);}\
virtual FResult StartSearch(int winid,Nat32 startFreq,tmFe_SearchMode_t mode,Nat32 endFreq,Nat32 * retval){ return m_parent->intf ## _StartSearch(winid,startFreq,mode,endFreq,retval);}\
virtual FResult StopSearch(int winid,Nat32 * retval){ return m_parent->intf ## _StopSearch(winid,retval);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
