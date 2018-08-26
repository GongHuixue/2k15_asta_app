#ifndef IPLFAPITSDMXABSTRACTEX_H
#define IPLFAPITSDMXABSTRACTEX_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiTsDmxAbstractEx
{
public:
	virtual ~IPlfApiTsDmxAbstractEx(){}
	virtual FResult IsRequestAllowed(int winid,Bool * retval)= 0;
	#define IPlfApiTsDmxAbstractEx_CrcModeSkipBadSections		((int)1 )
	#define IPlfApiTsDmxAbstractEx_CrcModeAcceptAllSections		((int)2 )
	#define IPlfApiTsDmxAbstractEx_CrcModeDontCheckCrc		((int)3 )
	#define IPlfApiTsDmxAbstractEx_FilterDepth		((int)12 )
	#define IPlfApiTsDmxAbstractEx_StreamTypeInvalid		((int)0 )
	#define IPlfApiTsDmxAbstractEx_StreamTypemp1v		((int)1 )
	#define IPlfApiTsDmxAbstractEx_StreamTypemp2v		((int)2 )
	#define IPlfApiTsDmxAbstractEx_StreamTypemp4v		((int)3 )
	#define IPlfApiTsDmxAbstractEx_StreamTypemp1a		((int)4 )
	#define IPlfApiTsDmxAbstractEx_StreamTypemp2a		((int)5 )
	#define IPlfApiTsDmxAbstractEx_StreamTypemp4a		((int)6 )
	#define IPlfApiTsDmxAbstractEx_StreamTypettxt		((int)7 )
	#define IPlfApiTsDmxAbstractEx_StreamTypesubt		((int)8 )
	#define IPlfApiTsDmxAbstractEx_StreamTypepcr		((int)9 )
	#define IPlfApiTsDmxAbstractEx_StreamTypeac3		((int)10 )
	#define IPlfApiTsDmxAbstractEx_StreamTypeh264		((int)11 )
	#define IPlfApiTsDmxAbstractEx_StreamTypedivx		((int)12 )
	#define IPlfApiTsDmxAbstractEx_StreamTypevc1		((int)13 )
	#define IPlfApiTsDmxAbstractEx_StreamTypeaac		((int)14 )
	#define IPlfApiTsDmxAbstractEx_StreamTypeheaac		((int)15 )
	#define IPlfApiTsDmxAbstractEx_StreamTypewma		((int)16 )
	#define IPlfApiTsDmxAbstractEx_StreamTypeddplus		((int)17 )
	#define IPlfApiTsDmxAbstractEx_StreamTypedts		((int)18 )
	#define IPlfApiTsDmxAbstractEx_StreamTypemmw		((int)19 )
	#define IPlfApiTsDmxAbstractEx_StreamTypemma		((int)20 )
	#define IPlfApiTsDmxAbstractEx_StreamTypeOther		((int)21 )
	#define IPlfApiTsDmxAbstractEx_StreamTypeLpcm		((int)22 )
	#define IPlfApiTsDmxAbstractEx_InvalidSubscrId		((Nat32)0xffffffff )
	virtual FResult RequestFilter(int winid,int pid,int BufferSize,int CrcMode,Bool ContinuousMode,Nat32 cookie,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval)= 0;
	virtual FResult UpdateFilter(int winid,Nat32 subscrId,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Bool * retval)= 0;
	virtual FResult CancelFilter(int winid,Nat32 subscrId,Nat32 * error)= 0;
	virtual FResult RequestListFilter(int winid,int pid,int BufferSize,int CrcMode,Bool ContinuousMode,Nat32 timeout,Nat32 listLength,Nat32 cookie,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval)= 0;
	virtual FResult UpdateListFilter(int winid,Nat32 subscrId,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Bool * retval)= 0;
	virtual FResult CancelListFilter(int winid,Nat32 subscrId,Nat32 * error)= 0;
	virtual FResult RequestPes(int winid,int pid,int BufferSize,Nat32 cookie,int FilterDepth,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval)= 0;
	virtual FResult CancelPes(int winid,Nat32 subscrId,Nat32 * error)= 0;
	virtual FResult RequestPesList(int winid,int pid,int BufferSize,Nat32 timeout,Nat32 listLength,Nat32 cookie,int FilterDepth,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval)= 0;
	virtual FResult CancelPesList(int winid,Nat32 subscrId,Nat32 * error)= 0;
	virtual FResult IsVideoStreamTypeSupported(int winid,int streamtype,Bool * supported,Nat32 * error)= 0;
	virtual FResult SetVideoStreamType(int winid,int streamtype,Nat32 * error)= 0;
	virtual FResult GetVideoStreamType(int winid,int * streamtype,Nat32 * error)= 0;
	virtual FResult IsAudioStreamTypeSupported(int winid,int streamtype,Bool * supported,Nat32 * error)= 0;
	virtual FResult SetAudioStreamType(int winid,int streamtype,Nat32 * error)= 0;
	virtual FResult GetAudioStreamType(int winid,int * streamtype,Nat32 * error)= 0;
	virtual FResult GetPcrPid(int winid,Nat16 * pid,Nat32 * error)= 0;
	virtual FResult GetAudioPid(int winid,Nat16 * pid,Nat32 * error)= 0;
	virtual FResult GetVideoPid(int winid,Nat16 * pid,Nat32 * error)= 0;
	virtual FResult GetAudioDescriptivePid(int winid,Nat16 * pid,Nat32 * error)= 0;
	virtual FResult SetPcrPid(int winid,Nat16 pid,Nat32 * error)= 0;
	virtual FResult SetAudioPid(int winid,Nat16 pid,Nat32 * error)= 0;
	virtual FResult SetVideoPid(int winid,Nat16 pid,Nat32 * error)= 0;
	virtual FResult SetAudioDescriptivePid(int winid,Nat16 pid,Nat32 * error)= 0;
	virtual FResult StopPcrPid(int winid,Nat32 * error)= 0;
	virtual FResult StopAudioPid(int winid,Nat32 * error)= 0;
	virtual FResult StopVideoPid(int winid,Nat32 * error)= 0;
	virtual FResult StopAudioDescriptivePid(int winid,Nat32 * error)= 0;
	#define IPlfApiTsDmxAbstractEx_ScramblingUnknown		((int)1 )
	#define IPlfApiTsDmxAbstractEx_NotScrambled		((int)2 )
	#define IPlfApiTsDmxAbstractEx_Scrambled		((int)3 )
	#define IPlfApiTsDmxAbstractEx_MediaTypeAudio		((int)1 )
	#define IPlfApiTsDmxAbstractEx_MediaTypeVideo		((int)2 )
	#define IPlfApiTsDmxAbstractEx_MediaTypeAudioDesc		((int)3 )
	virtual FResult GetScramblingStatus(int winid,int MediaType,Nat32 * error,int * retval)= 0;
	virtual FResult FreeSectionBuffer(int winid,Nat32 subscrId,Nat32 datacookie,Nat32 * error)= 0;
	virtual FResult FreeListBuffer(int winid,Nat32 subscrId,Nat32 listcookie,Nat32 * error)= 0;
	virtual FResult FreePesBuffer(int winid,Nat32 subscrId,Nat32 datacookie,Nat32 * error)= 0;
	virtual FResult FreePesListBuffer(int winid,Nat32 subscrId,Nat32 listcookie,Nat32 * error)= 0;
};


#define IPlfApiTsDmxAbstractExImpl(Comp,intf)    \
virtual FResult intf ## _IsRequestAllowed(int winid,Bool * retval);\
virtual FResult intf ## _RequestFilter(int winid,int pid,int BufferSize,int CrcMode,Bool ContinuousMode,Nat32 cookie,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval);\
virtual FResult intf ## _UpdateFilter(int winid,Nat32 subscrId,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Bool * retval);\
virtual FResult intf ## _CancelFilter(int winid,Nat32 subscrId,Nat32 * error);\
virtual FResult intf ## _RequestListFilter(int winid,int pid,int BufferSize,int CrcMode,Bool ContinuousMode,Nat32 timeout,Nat32 listLength,Nat32 cookie,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval);\
virtual FResult intf ## _UpdateListFilter(int winid,Nat32 subscrId,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Bool * retval);\
virtual FResult intf ## _CancelListFilter(int winid,Nat32 subscrId,Nat32 * error);\
virtual FResult intf ## _RequestPes(int winid,int pid,int BufferSize,Nat32 cookie,int FilterDepth,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval);\
virtual FResult intf ## _CancelPes(int winid,Nat32 subscrId,Nat32 * error);\
virtual FResult intf ## _RequestPesList(int winid,int pid,int BufferSize,Nat32 timeout,Nat32 listLength,Nat32 cookie,int FilterDepth,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval);\
virtual FResult intf ## _CancelPesList(int winid,Nat32 subscrId,Nat32 * error);\
virtual FResult intf ## _IsVideoStreamTypeSupported(int winid,int streamtype,Bool * supported,Nat32 * error);\
virtual FResult intf ## _SetVideoStreamType(int winid,int streamtype,Nat32 * error);\
virtual FResult intf ## _GetVideoStreamType(int winid,int * streamtype,Nat32 * error);\
virtual FResult intf ## _IsAudioStreamTypeSupported(int winid,int streamtype,Bool * supported,Nat32 * error);\
virtual FResult intf ## _SetAudioStreamType(int winid,int streamtype,Nat32 * error);\
virtual FResult intf ## _GetAudioStreamType(int winid,int * streamtype,Nat32 * error);\
virtual FResult intf ## _GetPcrPid(int winid,Nat16 * pid,Nat32 * error);\
virtual FResult intf ## _GetAudioPid(int winid,Nat16 * pid,Nat32 * error);\
virtual FResult intf ## _GetVideoPid(int winid,Nat16 * pid,Nat32 * error);\
virtual FResult intf ## _GetAudioDescriptivePid(int winid,Nat16 * pid,Nat32 * error);\
virtual FResult intf ## _SetPcrPid(int winid,Nat16 pid,Nat32 * error);\
virtual FResult intf ## _SetAudioPid(int winid,Nat16 pid,Nat32 * error);\
virtual FResult intf ## _SetVideoPid(int winid,Nat16 pid,Nat32 * error);\
virtual FResult intf ## _SetAudioDescriptivePid(int winid,Nat16 pid,Nat32 * error);\
virtual FResult intf ## _StopPcrPid(int winid,Nat32 * error);\
virtual FResult intf ## _StopAudioPid(int winid,Nat32 * error);\
virtual FResult intf ## _StopVideoPid(int winid,Nat32 * error);\
virtual FResult intf ## _StopAudioDescriptivePid(int winid,Nat32 * error);\
virtual FResult intf ## _GetScramblingStatus(int winid,int MediaType,Nat32 * error,int * retval);\
virtual FResult intf ## _FreeSectionBuffer(int winid,Nat32 subscrId,Nat32 datacookie,Nat32 * error);\
virtual FResult intf ## _FreeListBuffer(int winid,Nat32 subscrId,Nat32 listcookie,Nat32 * error);\
virtual FResult intf ## _FreePesBuffer(int winid,Nat32 subscrId,Nat32 datacookie,Nat32 * error);\
virtual FResult intf ## _FreePesListBuffer(int winid,Nat32 subscrId,Nat32 listcookie,Nat32 * error);\
class Comp ## _ ## intf : public IPlfApiTsDmxAbstractEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult IsRequestAllowed(int winid,Bool * retval){ return m_parent->intf ## _IsRequestAllowed(winid,retval);}\
virtual FResult RequestFilter(int winid,int pid,int BufferSize,int CrcMode,Bool ContinuousMode,Nat32 cookie,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval){ return m_parent->intf ## _RequestFilter(winid,pid,BufferSize,CrcMode,ContinuousMode,cookie,FilterDepth,ModeArray,MatchArray,MaskArray,error,retval);}\
virtual FResult UpdateFilter(int winid,Nat32 subscrId,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Bool * retval){ return m_parent->intf ## _UpdateFilter(winid,subscrId,FilterDepth,ModeArray,MatchArray,MaskArray,error,retval);}\
virtual FResult CancelFilter(int winid,Nat32 subscrId,Nat32 * error){ return m_parent->intf ## _CancelFilter(winid,subscrId,error);}\
virtual FResult RequestListFilter(int winid,int pid,int BufferSize,int CrcMode,Bool ContinuousMode,Nat32 timeout,Nat32 listLength,Nat32 cookie,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval){ return m_parent->intf ## _RequestListFilter(winid,pid,BufferSize,CrcMode,ContinuousMode,timeout,listLength,cookie,FilterDepth,ModeArray,MatchArray,MaskArray,error,retval);}\
virtual FResult UpdateListFilter(int winid,Nat32 subscrId,int FilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Bool * retval){ return m_parent->intf ## _UpdateListFilter(winid,subscrId,FilterDepth,ModeArray,MatchArray,MaskArray,error,retval);}\
virtual FResult CancelListFilter(int winid,Nat32 subscrId,Nat32 * error){ return m_parent->intf ## _CancelListFilter(winid,subscrId,error);}\
virtual FResult RequestPes(int winid,int pid,int BufferSize,Nat32 cookie,int FilterDepth,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval){ return m_parent->intf ## _RequestPes(winid,pid,BufferSize,cookie,FilterDepth,MatchArray,MaskArray,error,retval);}\
virtual FResult CancelPes(int winid,Nat32 subscrId,Nat32 * error){ return m_parent->intf ## _CancelPes(winid,subscrId,error);}\
virtual FResult RequestPesList(int winid,int pid,int BufferSize,Nat32 timeout,Nat32 listLength,Nat32 cookie,int FilterDepth,Nat8 * MatchArray,Nat8 * MaskArray,Nat32 * error,Nat32 * retval){ return m_parent->intf ## _RequestPesList(winid,pid,BufferSize,timeout,listLength,cookie,FilterDepth,MatchArray,MaskArray,error,retval);}\
virtual FResult CancelPesList(int winid,Nat32 subscrId,Nat32 * error){ return m_parent->intf ## _CancelPesList(winid,subscrId,error);}\
virtual FResult IsVideoStreamTypeSupported(int winid,int streamtype,Bool * supported,Nat32 * error){ return m_parent->intf ## _IsVideoStreamTypeSupported(winid,streamtype,supported,error);}\
virtual FResult SetVideoStreamType(int winid,int streamtype,Nat32 * error){ return m_parent->intf ## _SetVideoStreamType(winid,streamtype,error);}\
virtual FResult GetVideoStreamType(int winid,int * streamtype,Nat32 * error){ return m_parent->intf ## _GetVideoStreamType(winid,streamtype,error);}\
virtual FResult IsAudioStreamTypeSupported(int winid,int streamtype,Bool * supported,Nat32 * error){ return m_parent->intf ## _IsAudioStreamTypeSupported(winid,streamtype,supported,error);}\
virtual FResult SetAudioStreamType(int winid,int streamtype,Nat32 * error){ return m_parent->intf ## _SetAudioStreamType(winid,streamtype,error);}\
virtual FResult GetAudioStreamType(int winid,int * streamtype,Nat32 * error){ return m_parent->intf ## _GetAudioStreamType(winid,streamtype,error);}\
virtual FResult GetPcrPid(int winid,Nat16 * pid,Nat32 * error){ return m_parent->intf ## _GetPcrPid(winid,pid,error);}\
virtual FResult GetAudioPid(int winid,Nat16 * pid,Nat32 * error){ return m_parent->intf ## _GetAudioPid(winid,pid,error);}\
virtual FResult GetVideoPid(int winid,Nat16 * pid,Nat32 * error){ return m_parent->intf ## _GetVideoPid(winid,pid,error);}\
virtual FResult GetAudioDescriptivePid(int winid,Nat16 * pid,Nat32 * error){ return m_parent->intf ## _GetAudioDescriptivePid(winid,pid,error);}\
virtual FResult SetPcrPid(int winid,Nat16 pid,Nat32 * error){ return m_parent->intf ## _SetPcrPid(winid,pid,error);}\
virtual FResult SetAudioPid(int winid,Nat16 pid,Nat32 * error){ return m_parent->intf ## _SetAudioPid(winid,pid,error);}\
virtual FResult SetVideoPid(int winid,Nat16 pid,Nat32 * error){ return m_parent->intf ## _SetVideoPid(winid,pid,error);}\
virtual FResult SetAudioDescriptivePid(int winid,Nat16 pid,Nat32 * error){ return m_parent->intf ## _SetAudioDescriptivePid(winid,pid,error);}\
virtual FResult StopPcrPid(int winid,Nat32 * error){ return m_parent->intf ## _StopPcrPid(winid,error);}\
virtual FResult StopAudioPid(int winid,Nat32 * error){ return m_parent->intf ## _StopAudioPid(winid,error);}\
virtual FResult StopVideoPid(int winid,Nat32 * error){ return m_parent->intf ## _StopVideoPid(winid,error);}\
virtual FResult StopAudioDescriptivePid(int winid,Nat32 * error){ return m_parent->intf ## _StopAudioDescriptivePid(winid,error);}\
virtual FResult GetScramblingStatus(int winid,int MediaType,Nat32 * error,int * retval){ return m_parent->intf ## _GetScramblingStatus(winid,MediaType,error,retval);}\
virtual FResult FreeSectionBuffer(int winid,Nat32 subscrId,Nat32 datacookie,Nat32 * error){ return m_parent->intf ## _FreeSectionBuffer(winid,subscrId,datacookie,error);}\
virtual FResult FreeListBuffer(int winid,Nat32 subscrId,Nat32 listcookie,Nat32 * error){ return m_parent->intf ## _FreeListBuffer(winid,subscrId,listcookie,error);}\
virtual FResult FreePesBuffer(int winid,Nat32 subscrId,Nat32 datacookie,Nat32 * error){ return m_parent->intf ## _FreePesBuffer(winid,subscrId,datacookie,error);}\
virtual FResult FreePesListBuffer(int winid,Nat32 subscrId,Nat32 listcookie,Nat32 * error){ return m_parent->intf ## _FreePesListBuffer(winid,subscrId,listcookie,error);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
