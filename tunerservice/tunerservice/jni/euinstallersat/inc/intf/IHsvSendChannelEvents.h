#ifndef IHSVSENDCHANNELEVENTS_H
#define IHSVSENDCHANNELEVENTS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSendChannelEvents
{
public:
	virtual ~IHsvSendChannelEvents(){}
	#define IHsvSendChannelEvents_SelectChannel		((int)0 )
	#define IHsvSendChannelEvents_TuneChannelStart		((int)1 )
	#define IHsvSendChannelEvents_TuneChannelEnd		((int)2 )
	#define IHsvSendChannelEvents_ChannelTableUpdateStart		((int)3 )
	#define IHsvSendChannelEvents_ChannelTableUpdateEnd		((int)4 )
	#define IHsvSendChannelEvents_ChannelTableChanged		((int)5 )
	#define IHsvSendChannelEvents_DirectTune		((int)6 )
	#define IHsvSendChannelEvents_DirectTuneStart		((int)7 )
	#define IHsvSendChannelEvents_DirectTuneEnd		((int)8 )
	#define IHsvSendChannelEvents_UserRating		((int)9 )
	#define IHsvSendChannelEvents_StreamRating		((int)10 )
	#define IHsvSendChannelEvents_LockStatus		((int)11 )
	#define IHsvSendChannelEvents_PlayPid		((int)12 )
	#define IHsvSendChannelEvents_StopPid		((int)13 )
	#define IHsvSendChannelEvents_PlayIPPid		((int)14 )
	#define IHsvSendChannelEvents_StopIPPid		((int)15 )
	#define IHsvSendChannelEvents_PidChanged		((int)16 )
	#define IHsvSendChannelEvents_PidStopped		((int)17 )
	#define IHsvSendChannelEvents_SubtitleControl		((int)18 )
	#define IHsvSendChannelEvents_CCControl		((int)19 )
	#define IHsvSendChannelEvents_SubtitleSetting		((int)20 )
	#define IHsvSendChannelEvents_CCSetting		((int)21 )
	#define IHsvSendChannelEvents_EnableLocks		((int)22 )
	#define IHsvSendChannelEvents_CurrentPmtPidChanged		((int)23 )
	#define IHsvSendChannelEvents_SelectChannel2		((int)24 )
	#define IHsvSendChannelEvents_SetSubtitle		((int)25 )
	#define IHsvSendChannelEvents_SetCC		((int)26 )
	#define IHsvSendChannelEvents_SetTvSystem		((int)27 )
	#define IHsvSendChannelEvents_SetFrequency		((int)28 )
	#define IHsvSendChannelEvents_SetNodeId		((int)29 )
	#define IHsvSendChannelEvents_SubtitleAvailStatus		((int)30 )
	#define IHsvSendChannelEvents_TXTAvailStatus		((int)31 )
	#define IHsvSendChannelEvents_VIAvailStatus		((int)32 )
	#define IHsvSendChannelEvents_CurrentAudioLanguage		((int)33 )
	#define IHsvSendChannelEvents_CurrentSubtLanguage		((int)34 )
	#define IHsvSendChannelEvents_SaveChannelMapToMedium		((int)35 )
	#define IHsvSendChannelEvents_LoadChannelMapFromMedium		((int)36 )
	#define IHsvSendChannelEvents_EuContentLibCreateComplete		((int)37 )
	#define IHsvSendChannelEvents_PackageId		((int)38 )
	#define IHsvSendChannelEvents_DirectProgramTune		((int)39 )
	#define IHsvSendChannelEvents_EventS2AppEnabled		((int)40 )
	#define IHsvSendChannelEvents_EventS2AppAlive		((int)41 )
	#define IHsvSendChannelEvents_NetworkOperator		((int)42 )
	#define IHsvSendChannelEvents_TxtRatedContent		((int)43 )
	#define IHsvSendChannelEvents_MaxEvents		((int)44 )
	virtual void SendEvent(int EventId,Address data,Nat32 size)= 0;
};


#define IHsvSendChannelEventsImpl(Comp,intf)    \
virtual void intf ## _SendEvent(int EventId,Address data,Nat32 size);\
class Comp ## _ ## intf : public IHsvSendChannelEvents \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SendEvent(int EventId,Address data,Nat32 size){ return m_parent->intf ## _SendEvent(EventId,data,size);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
