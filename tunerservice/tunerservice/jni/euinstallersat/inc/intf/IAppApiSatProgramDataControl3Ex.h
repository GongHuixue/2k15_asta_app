#ifndef IAPPAPISATPROGRAMDATACONTROL3EX_H
#define IAPPAPISATPROGRAMDATACONTROL3EX_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataControl3Ex
{
public:
	virtual ~IAppApiSatProgramDataControl3Ex(){}
	virtual AppApiReturnCode GetCurrentChannel(AppApiChannel * Channel)= 0;
	virtual AppApiReturnCode SelectChannel(int seltype,AppApiChannel channel)= 0;
	virtual AppApiReturnCode DirectTuning(AppApiDirectTuningParameters param)= 0;
	virtual AppApiReturnCode DirectProgramTuning(AppApiDirectTuningParameters2 param)= 0;
	virtual AppApiReturnCode GetUserParentalRating(AppApiParentalRating * Rating)= 0;
	virtual AppApiReturnCode GetStreamParentalRating(AppApiParentalRating * Rating)= 0;
	virtual AppApiReturnCode IsChannelLocked(int * Status)= 0;
	virtual AppApiReturnCode EnableLocks(Bool enable)= 0;
	virtual AppApiReturnCode EnableSubtitle(void)= 0;
	virtual AppApiReturnCode DisableSubtitle(void)= 0;
	virtual AppApiReturnCode EnableClosedCaption(void)= 0;
	virtual AppApiReturnCode DisableClosedCaption(void)= 0;
	virtual AppApiReturnCode GetCCSettings(int * CCSetting)= 0;
	virtual AppApiReturnCode GetSubtitleSetting(int * SubtitleSetting)= 0;
	virtual int GetCurrentPMTPID(void)= 0;
	virtual AppApiReturnCode GetCurrentSubtitleStatus(AppApiSubtitleType * SubtitleType)= 0;
	virtual AppApiReturnCode GetCurrentTeletextStatus(Bool * Present)= 0;
	virtual AppApiReturnCode GetCurrentVisuallyImpairedStatus(Bool * Present)= 0;
	virtual AppApiReturnCode GetCurrentAudioLanguage(int * Language)= 0;
	virtual AppApiReturnCode GetCurrentSubtitleLanguage(int * Language)= 0;
	virtual AppApiReturnCode GetCurrentSatelliteName(Nat16 * SatelliteName)= 0;
	virtual AppApiReturnCode GetCurrentAudioType(int * AudioType)= 0;
	virtual AppApiReturnCode GetCurrentSubtitleType(int * SubtitleType)= 0;
	#define IAppApiSatProgramDataControl3Ex_SelectionTypeNormal		((int)0 )
	#define IAppApiSatProgramDataControl3Ex_SelectionTypeQuite		((int)1 )
	#define IAppApiSatProgramDataControl3Ex_SelectionTypeNonDestructive		((int)2 )
	#define IAppApiSatProgramDataControl3Ex_SelectionTypeQuiteNonDestructive		((int)3 )
	virtual void SetChannelUniqueNodeId(AppApiChannel channel,Nat64 node_id)= 0;
	virtual AppApiReturnCode SaveChannelMap(char * destdir,int MapType)= 0;
	virtual AppApiReturnCode LoadChannelMap(char * sourcedir,int MapType)= 0;
	#define IAppApiSatProgramDataControl3Ex_CcOn		((int)0 )
	#define IAppApiSatProgramDataControl3Ex_CcOff		((int)1 )
	#define IAppApiSatProgramDataControl3Ex_CcOnDuringMute		((int)2 )
	#define IAppApiSatProgramDataControl3Ex_SubtitleOff		((int)0 )
	#define IAppApiSatProgramDataControl3Ex_SubtitleOn		((int)1 )
	#define IAppApiSatProgramDataControl3Ex_SubtitleOnDuringMute		((int)2 )
	#define IAppApiSatProgramDataControl3Ex_AntennaMap		((int)0 )
	#define IAppApiSatProgramDataControl3Ex_CableMap		((int)1 )
};


#define IAppApiSatProgramDataControl3ExImpl(Comp,intf)    \
virtual AppApiReturnCode intf ## _GetCurrentChannel(AppApiChannel * Channel);\
virtual AppApiReturnCode intf ## _SelectChannel(int seltype,AppApiChannel channel);\
virtual AppApiReturnCode intf ## _DirectTuning(AppApiDirectTuningParameters param);\
virtual AppApiReturnCode intf ## _DirectProgramTuning(AppApiDirectTuningParameters2 param);\
virtual AppApiReturnCode intf ## _GetUserParentalRating(AppApiParentalRating * Rating);\
virtual AppApiReturnCode intf ## _GetStreamParentalRating(AppApiParentalRating * Rating);\
virtual AppApiReturnCode intf ## _IsChannelLocked(int * Status);\
virtual AppApiReturnCode intf ## _EnableLocks(Bool enable);\
virtual AppApiReturnCode intf ## _EnableSubtitle(void);\
virtual AppApiReturnCode intf ## _DisableSubtitle(void);\
virtual AppApiReturnCode intf ## _EnableClosedCaption(void);\
virtual AppApiReturnCode intf ## _DisableClosedCaption(void);\
virtual AppApiReturnCode intf ## _GetCCSettings(int * CCSetting);\
virtual AppApiReturnCode intf ## _GetSubtitleSetting(int * SubtitleSetting);\
virtual int intf ## _GetCurrentPMTPID(void);\
virtual AppApiReturnCode intf ## _GetCurrentSubtitleStatus(AppApiSubtitleType * SubtitleType);\
virtual AppApiReturnCode intf ## _GetCurrentTeletextStatus(Bool * Present);\
virtual AppApiReturnCode intf ## _GetCurrentVisuallyImpairedStatus(Bool * Present);\
virtual AppApiReturnCode intf ## _GetCurrentAudioLanguage(int * Language);\
virtual AppApiReturnCode intf ## _GetCurrentSubtitleLanguage(int * Language);\
virtual AppApiReturnCode intf ## _GetCurrentSatelliteName(Nat16 * SatelliteName);\
virtual AppApiReturnCode intf ## _GetCurrentAudioType(int * AudioType);\
virtual AppApiReturnCode intf ## _GetCurrentSubtitleType(int * SubtitleType);\
virtual void intf ## _SetChannelUniqueNodeId(AppApiChannel channel,Nat64 node_id);\
virtual AppApiReturnCode intf ## _SaveChannelMap(char * destdir,int MapType);\
virtual AppApiReturnCode intf ## _LoadChannelMap(char * sourcedir,int MapType);\
class Comp ## _ ## intf : public IAppApiSatProgramDataControl3Ex \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual AppApiReturnCode GetCurrentChannel(AppApiChannel * Channel){ return m_parent->intf ## _GetCurrentChannel(Channel);}\
virtual AppApiReturnCode SelectChannel(int seltype,AppApiChannel channel){ return m_parent->intf ## _SelectChannel(seltype,channel);}\
virtual AppApiReturnCode DirectTuning(AppApiDirectTuningParameters param){ return m_parent->intf ## _DirectTuning(param);}\
virtual AppApiReturnCode DirectProgramTuning(AppApiDirectTuningParameters2 param){ return m_parent->intf ## _DirectProgramTuning(param);}\
virtual AppApiReturnCode GetUserParentalRating(AppApiParentalRating * Rating){ return m_parent->intf ## _GetUserParentalRating(Rating);}\
virtual AppApiReturnCode GetStreamParentalRating(AppApiParentalRating * Rating){ return m_parent->intf ## _GetStreamParentalRating(Rating);}\
virtual AppApiReturnCode IsChannelLocked(int * Status){ return m_parent->intf ## _IsChannelLocked(Status);}\
virtual AppApiReturnCode EnableLocks(Bool enable){ return m_parent->intf ## _EnableLocks(enable);}\
virtual AppApiReturnCode EnableSubtitle(void){ return m_parent->intf ## _EnableSubtitle();}\
virtual AppApiReturnCode DisableSubtitle(void){ return m_parent->intf ## _DisableSubtitle();}\
virtual AppApiReturnCode EnableClosedCaption(void){ return m_parent->intf ## _EnableClosedCaption();}\
virtual AppApiReturnCode DisableClosedCaption(void){ return m_parent->intf ## _DisableClosedCaption();}\
virtual AppApiReturnCode GetCCSettings(int * CCSetting){ return m_parent->intf ## _GetCCSettings(CCSetting);}\
virtual AppApiReturnCode GetSubtitleSetting(int * SubtitleSetting){ return m_parent->intf ## _GetSubtitleSetting(SubtitleSetting);}\
virtual int GetCurrentPMTPID(void){ return m_parent->intf ## _GetCurrentPMTPID();}\
virtual AppApiReturnCode GetCurrentSubtitleStatus(AppApiSubtitleType * SubtitleType){ return m_parent->intf ## _GetCurrentSubtitleStatus(SubtitleType);}\
virtual AppApiReturnCode GetCurrentTeletextStatus(Bool * Present){ return m_parent->intf ## _GetCurrentTeletextStatus(Present);}\
virtual AppApiReturnCode GetCurrentVisuallyImpairedStatus(Bool * Present){ return m_parent->intf ## _GetCurrentVisuallyImpairedStatus(Present);}\
virtual AppApiReturnCode GetCurrentAudioLanguage(int * Language){ return m_parent->intf ## _GetCurrentAudioLanguage(Language);}\
virtual AppApiReturnCode GetCurrentSubtitleLanguage(int * Language){ return m_parent->intf ## _GetCurrentSubtitleLanguage(Language);}\
virtual AppApiReturnCode GetCurrentSatelliteName(Nat16 * SatelliteName){ return m_parent->intf ## _GetCurrentSatelliteName(SatelliteName);}\
virtual AppApiReturnCode GetCurrentAudioType(int * AudioType){ return m_parent->intf ## _GetCurrentAudioType(AudioType);}\
virtual AppApiReturnCode GetCurrentSubtitleType(int * SubtitleType){ return m_parent->intf ## _GetCurrentSubtitleType(SubtitleType);}\
virtual void SetChannelUniqueNodeId(AppApiChannel channel,Nat64 node_id){ return m_parent->intf ## _SetChannelUniqueNodeId(channel,node_id);}\
virtual AppApiReturnCode SaveChannelMap(char * destdir,int MapType){ return m_parent->intf ## _SaveChannelMap(destdir,MapType);}\
virtual AppApiReturnCode LoadChannelMap(char * sourcedir,int MapType){ return m_parent->intf ## _LoadChannelMap(sourcedir,MapType);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
