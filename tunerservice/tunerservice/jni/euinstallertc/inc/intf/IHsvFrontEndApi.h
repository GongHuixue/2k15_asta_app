#ifndef IHSVFRONTENDAPI_H
#define IHSVFRONTENDAPI_H
#include <intfparam.h>
#include <provreq.h>
class IHsvFrontEndApi
{
public:
	virtual ~IHsvFrontEndApi(){}
	virtual FResult GetFreqRange(int winid,Nat32 * MinFreq,Nat32 * MaxFreq,Nat32 * retval)= 0;
	virtual FResult GetFreq(int winid,Nat32 * Freq,Nat32 * retval)= 0;
	virtual FResult SetFreq(int winid,Nat32 freq,Bool finetune,Nat32 * retval)= 0;
	virtual FResult GetTvSystemSupp(int winid,tmFe_TvSystem_t tvSystem,Bool * Supp,Nat32 * retval)= 0;
	virtual FResult GetTvSystem(int winid,tmFe_TvSystem_t * TvSystem,Nat32 * retval)= 0;
	virtual FResult SetTvSystem(int winid,tmFe_TvSystem_t TvSystem,Nat32 * retval)= 0;
	virtual FResult StartSearch(int winid,Nat32 startFreq,tmFe_SearchMode_t mode,Nat32 endFreq,Nat32 * retval)= 0;
	virtual FResult StopSearch(int winid,Nat32 * retval)= 0;
	#define IHsvFrontEndApi_WaitforAbort	((Nat32)0 )
	#define IHsvFrontEndApi_SearchStopped	((Nat32)1 )
	virtual FResult Freq2Chan(int winid,Nat32 freq,tmFe_ChanTable_t table,Nat32 * Chan,Nat32 * retval)= 0;
	virtual FResult GetCarrierFreq(int winid,Nat32 chan,tmFe_ChanTable_t table,Nat32 * Freq,Nat32 * retval)= 0;
	#define IHsvFrontEndApi_SigAssm		((int)0 )
	#define IHsvFrontEndApi_SigVssm		((int)1 )
	#define IHsvFrontEndApi_SigQssm		((int)2 )
	#define IHsvFrontEndApi_SigSssm		((int)3 )
	virtual FResult GetSigStrengthRange(int winid,int ssm,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval)= 0;
	virtual FResult Start(int winid,int ssm,Bool * Avail,Nat32 * retval)= 0;
	virtual FResult Stop(int winid,int ssm,Bool * Stopped,Nat32 * retval)= 0;
	virtual FResult GetMeasValid(int winid,int ssm,Bool * Valid,Nat32 * retval)= 0;
	virtual FResult GetSigStrength(int winid,int ssm,Nat32 * Strength,Nat32 * retval)= 0;
	virtual FResult GetActualConstellation(int winid,int decoder,tmFe_Constellation_t * pConstellation,Nat32 * retval)= 0;
	virtual FResult SetConstellation(int winid,int decoder,tmFe_Constellation_t constellation,Nat32 * retval)= 0;
	virtual FResult GetBer(int winid,int decoder,Nat32 * Ber,Nat32 * retval)= 0;
	virtual FResult GetCarrierPresent(int winid,Bool * Present,Nat32 * retval)= 0;
	virtual FResult SetChanBandwidth(int winid,tmFe_ChanBandwidth_t bandwidth,Nat32 * retval)= 0;
	virtual FResult GetActualChanBandwidth(int winid,tmFe_ChanBandwidth_t * Bandwidth,Nat32 * retval)= 0;
	virtual FResult SetStreamPriority(int winid,tmFe_StreamPriority_t streamPriority,Nat32 * retval)= 0;
	virtual FResult GetStreamPriority(int winid,tmFe_StreamPriority_t * streamPriority,Nat32 * retval)= 0;
	virtual FResult GetHierarchyMuxPresence( int winid, Bool * HierarchyMuxPresent, Nat32* retval ) = 0;
	virtual FResult GetTPSId(int winid, HsvDvbTParams* TPSId, Nat32* retval )=0;
	virtual FResult GetSymbolRateRange(int winid,Nat32 * MinSymbolRate,Nat32 * MaxSymbolRate,Nat32 * retval)= 0;
	virtual FResult SetSymbolRate(int winid,Nat32 rate,Nat32 * retval)= 0;
	virtual FResult GetSymbolRate(int winid,Nat32 * rate,Nat32 * retval)= 0;
	virtual FResult SetSearchRates(int winid,tmFe_SearchSymbolRate_t * SearchRate,Nat32 size,Nat32 * retval)= 0;
	virtual FResult GetActualCodeRate(int winid,Nat32 * rate,Nat32 * retval)= 0;
	virtual FResult SetFreqStep(int winid,Nat32 step,Nat32 * retval)= 0;
	virtual FResult GetFreqStep(int winid,Nat32 * step,Nat32 * retval)= 0;
	#define IHsvFrontEndApi_ChanDecDvbT		((Nat32)0x1 )
	#define IHsvFrontEndApi_ChanDecDvbC		((Nat32)0x2 )
	#define IHsvFrontEndApi_ChanDecDvbS		((Nat32)0x4 )
	#define IHsvFrontEndApi_ChanDecISDBT		((Nat32)0x8 )
	#define IHsvFrontEndApi_ChanDecDvbT2		((Nat32)0x10 )
};


#define IHsvFrontEndApiImpl(Comp,intf)    \
virtual FResult intf ## _GetFreqRange(int winid,Nat32 * MinFreq,Nat32 * MaxFreq,Nat32 * retval);\
virtual FResult intf ## _GetFreq(int winid,Nat32 * Freq,Nat32 * retval);\
virtual FResult intf ## _SetFreq(int winid,Nat32 freq,Bool finetune,Nat32 * retval);\
virtual FResult intf ## _GetTvSystemSupp(int winid,tmFe_TvSystem_t tvSystem,Bool * Supp,Nat32 * retval);\
virtual FResult intf ## _GetTvSystem(int winid,tmFe_TvSystem_t * TvSystem,Nat32 * retval);\
virtual FResult intf ## _SetTvSystem(int winid,tmFe_TvSystem_t TvSystem,Nat32 * retval);\
virtual FResult intf ## _StartSearch(int winid,Nat32 startFreq,tmFe_SearchMode_t mode,Nat32 endFreq,Nat32 * retval);\
virtual FResult intf ## _StopSearch(int winid,Nat32 * retval);\
virtual FResult intf ## _Freq2Chan(int winid,Nat32 freq,tmFe_ChanTable_t table,Nat32 * Chan,Nat32 * retval);\
virtual FResult intf ## _GetCarrierFreq(int winid,Nat32 chan,tmFe_ChanTable_t table,Nat32 * Freq,Nat32 * retval);\
virtual FResult intf ## _GetSigStrengthRange(int winid,int ssm,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval);\
virtual FResult intf ## _Start(int winid,int ssm,Bool * Avail,Nat32 * retval);\
virtual FResult intf ## _Stop(int winid,int ssm,Bool * Stopped,Nat32 * retval);\
virtual FResult intf ## _GetMeasValid(int winid,int ssm,Bool * Valid,Nat32 * retval);\
virtual FResult intf ## _GetSigStrength(int winid,int ssm,Nat32 * Strength,Nat32 * retval);\
virtual FResult intf ## _GetActualConstellation(int winid,int decoder,tmFe_Constellation_t * pConstellation,Nat32 * retval);\
virtual FResult intf ## _SetConstellation(int winid,int decoder,tmFe_Constellation_t constellation,Nat32 * retval);\
virtual FResult intf ## _GetBer(int winid,int decoder,Nat32 * Ber,Nat32 * retval);\
virtual FResult intf ## _GetCarrierPresent(int winid,Bool * Present,Nat32 * retval);\
virtual FResult intf ## _SetChanBandwidth(int winid,tmFe_ChanBandwidth_t bandwidth,Nat32 * retval);\
virtual FResult intf ## _GetActualChanBandwidth(int winid,tmFe_ChanBandwidth_t * Bandwidth,Nat32 * retval);\
virtual FResult intf ## _SetStreamPriority(int winid,tmFe_StreamPriority_t streamPriority,Nat32 * retval);\
virtual FResult intf ## _GetStreamPriority(int winid,tmFe_StreamPriority_t * streamPriority,Nat32 * retval);\
virtual FResult intf ## _GetHierarchyMuxPresence(int winid,Bool* HierarchyMuxPresent,Nat32 * retval);\
virtual FResult intf ## _GetTPSId(int winid, HsvDvbTParams* TPSId, Nat32* retval );\
virtual FResult intf ## _GetSymbolRateRange(int winid,Nat32 * MinSymbolRate,Nat32 * MaxSymbolRate,Nat32 * retval);\
virtual FResult intf ## _SetSymbolRate(int winid,Nat32 rate,Nat32 * retval);\
virtual FResult intf ## _GetSymbolRate(int winid,Nat32 * rate,Nat32 * retval);\
virtual FResult intf ## _SetSearchRates(int winid,tmFe_SearchSymbolRate_t * SearchRate,Nat32 size,Nat32 * retval);\
virtual FResult intf ## _GetActualCodeRate(int winid,Nat32 * rate,Nat32 * retval);\
virtual FResult intf ## _SetFreqStep(int winid,Nat32 step,Nat32 * retval);\
virtual FResult intf ## _GetFreqStep(int winid,Nat32 * step,Nat32 * retval);\
class Comp ## _ ## intf : public IHsvFrontEndApi \
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
virtual FResult Freq2Chan(int winid,Nat32 freq,tmFe_ChanTable_t table,Nat32 * Chan,Nat32 * retval){ return m_parent->intf ## _Freq2Chan(winid,freq,table,Chan,retval);}\
virtual FResult GetCarrierFreq(int winid,Nat32 chan,tmFe_ChanTable_t table,Nat32 * Freq,Nat32 * retval){ return m_parent->intf ## _GetCarrierFreq(winid,chan,table,Freq,retval);}\
virtual FResult GetSigStrengthRange(int winid,int ssm,Nat32 * MinStrength,Nat32 * MaxStrength,Nat32 * retval){ return m_parent->intf ## _GetSigStrengthRange(winid,ssm,MinStrength,MaxStrength,retval);}\
virtual FResult Start(int winid,int ssm,Bool * Avail,Nat32 * retval){ return m_parent->intf ## _Start(winid,ssm,Avail,retval);}\
virtual FResult Stop(int winid,int ssm,Bool * Stopped,Nat32 * retval){ return m_parent->intf ## _Stop(winid,ssm,Stopped,retval);}\
virtual FResult GetMeasValid(int winid,int ssm,Bool * Valid,Nat32 * retval){ return m_parent->intf ## _GetMeasValid(winid,ssm,Valid,retval);}\
virtual FResult GetSigStrength(int winid,int ssm,Nat32 * Strength,Nat32 * retval){ return m_parent->intf ## _GetSigStrength(winid,ssm,Strength,retval);}\
virtual FResult GetActualConstellation(int winid,int decoder,tmFe_Constellation_t * pConstellation,Nat32 * retval){ return m_parent->intf ## _GetActualConstellation(winid,decoder,pConstellation,retval);}\
virtual FResult SetConstellation(int winid,int decoder,tmFe_Constellation_t constellation,Nat32 * retval){ return m_parent->intf ## _SetConstellation(winid,decoder,constellation,retval);}\
virtual FResult GetBer(int winid,int decoder,Nat32 * Ber,Nat32 * retval){ return m_parent->intf ## _GetBer(winid,decoder,Ber,retval);}\
virtual FResult GetCarrierPresent(int winid,Bool * Present,Nat32 * retval){ return m_parent->intf ## _GetCarrierPresent(winid,Present,retval);}\
virtual FResult SetChanBandwidth(int winid,tmFe_ChanBandwidth_t bandwidth,Nat32 * retval){ return m_parent->intf ## _SetChanBandwidth(winid,bandwidth,retval);}\
virtual FResult GetActualChanBandwidth(int winid,tmFe_ChanBandwidth_t * Bandwidth,Nat32 * retval){ return m_parent->intf ## _GetActualChanBandwidth(winid,Bandwidth,retval);}\
virtual FResult GetTPSId(int winid, HsvDvbTParams* TPSId, Nat32* retval ){ return m_parent->intf ## _GetTPSId(winid,TPSId,retval);}\
virtual FResult SetStreamPriority(int winid,tmFe_StreamPriority_t streamPriority,Nat32 * retval){ return m_parent->intf ## _SetStreamPriority(winid,streamPriority,retval);}\
virtual FResult GetStreamPriority(int winid,tmFe_StreamPriority_t * streamPriority,Nat32 * retval){ return m_parent->intf ## _GetStreamPriority(winid,streamPriority,retval);}\
virtual FResult GetHierarchyMuxPresence(int winid,Bool * HierarchyMuxPresent,Nat32 * retval){ return m_parent->intf ## _GetHierarchyMuxPresence(winid,HierarchyMuxPresent,retval);}\
virtual FResult GetSymbolRateRange(int winid,Nat32 * MinSymbolRate,Nat32 * MaxSymbolRate,Nat32 * retval){ return m_parent->intf ## _GetSymbolRateRange(winid,MinSymbolRate,MaxSymbolRate,retval);}\
virtual FResult SetSymbolRate(int winid,Nat32 rate,Nat32 * retval){ return m_parent->intf ## _SetSymbolRate(winid,rate,retval);}\
virtual FResult GetSymbolRate(int winid,Nat32 * rate,Nat32 * retval){ return m_parent->intf ## _GetSymbolRate(winid,rate,retval);}\
virtual FResult SetSearchRates(int winid,tmFe_SearchSymbolRate_t * SearchRate,Nat32 size,Nat32 * retval){ return m_parent->intf ## _SetSearchRates(winid,SearchRate,size,retval);}\
virtual FResult GetActualCodeRate(int winid,Nat32 * rate,Nat32 * retval){ return m_parent->intf ## _GetActualCodeRate(winid,rate,retval);}\
virtual FResult SetFreqStep(int winid,Nat32 step,Nat32 * retval){ return m_parent->intf ## _SetFreqStep(winid,step,retval);}\
virtual FResult GetFreqStep(int winid,Nat32 * step,Nat32 * retval){ return m_parent->intf ## _GetFreqStep(winid,step,retval);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
