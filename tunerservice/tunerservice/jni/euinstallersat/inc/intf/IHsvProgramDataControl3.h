#ifndef IHSVPROGRAMDATACONTROL3_H
#define IHSVPROGRAMDATACONTROL3_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataControl3
{
public:
	virtual ~IHsvProgramDataControl3(){}
	#define IHsvProgramDataControl3_Terrestrial		((int)0 )
	#define IHsvProgramDataControl3_Cable		((int)1 )
	#define IHsvProgramDataControl3_Satellite		((int)2 )
	#define IHsvProgramDataControl3_CcOn		((int)0 )
	#define IHsvProgramDataControl3_CcOff		((int)1 )
	#define IHsvProgramDataControl3_CcOnDuringMute		((int)2 )
	#define IHsvProgramDataControl3_SubtitleOff		((int)0 )
	#define IHsvProgramDataControl3_SubtitleOn		((int)1 )
	#define IHsvProgramDataControl3_SubtitleOnDuringMute		((int)2 )
	#define IHsvProgramDataControl3_SelectionTypeNormal		((int)0 )
	#define IHsvProgramDataControl3_SelectionTypeQuite		((int)1 )
	#define IHsvProgramDataControl3_SelectionTypeNonDestructive		((int)2 )
	#define IHsvProgramDataControl3_SelectionTypeQuiteNonDestructive		((int)3 )
	virtual void SetSelectedMedium(int medium)= 0;
	virtual int GetSelectedMedium(void)= 0;
	virtual void SetInstalledMedium(int medium)= 0;
	virtual int GetInstalledMedium(void)= 0;
	virtual AppApiReturnCode SelectChannel(int seltype,AppApiChannel channel)= 0;
	virtual AppApiReturnCode DirectTuning(AppApiDirectTuningParameters param)= 0;
	virtual AppApiReturnCode GetUserParentalRating(AppApiParentalRating * Rating)= 0;
	virtual AppApiReturnCode GetStreamParentalRating(AppApiParentalRating * Rating)= 0;
	virtual AppApiReturnCode IsChannelLocked(int * Status)= 0;
	virtual AppApiReturnCode EnableSubtitle(void)= 0;
	virtual AppApiReturnCode DisableSubtitle(void)= 0;
	virtual AppApiReturnCode DisableClosedCaption(void)= 0;
	virtual AppApiReturnCode EnableClosedCaption(void)= 0;
	virtual AppApiReturnCode GetCCSettings(int * CCSetting)= 0;
	virtual AppApiReturnCode GetCurrentProgram(AppApiChannel * Channel)= 0;
	virtual AppApiReturnCode EnableLocks(Bool enable)= 0;
	virtual AppApiReturnCode GetSubtitleSetting(int * SubtitleSetting)= 0;
	virtual int GetCurrentPMTPID(void)= 0;
	virtual void SetChannelUniqueNodeId(AppApiChannel channel,Nat64 node_id)= 0;
	virtual AppApiReturnCode GetCurrentSubtitleStatus(AppApiSubtitleType * SubtitleType)= 0;
	virtual AppApiReturnCode GetCurrentTeletextStatus(Bool * Present)= 0;
	virtual AppApiReturnCode GetCurrentVisuallyImpairedStatus(Bool * Present)= 0;
	virtual AppApiReturnCode GetCurrentAudioLanguage(int * Language)= 0;
	virtual AppApiReturnCode GetCurrentSubtitleLanguage(int * Language)= 0;
	virtual AppApiReturnCode GetCurrentAudioType(int * AudioType)= 0;
	virtual AppApiReturnCode GetCurrentSubtitleType(int * SubtitleType)= 0;
	virtual AppApiReturnCode GetCurrentSatelliteName(Nat16 * SatelliteName)= 0;
	virtual AppApiReturnCode SaveChannelMap(char * destdir,int MapType)= 0;
	virtual AppApiReturnCode LoadChannelMap(char * sourcedir,int MapType)= 0;
};


#define IHsvProgramDataControl3Impl(Comp,intf)    \
virtual void intf ## _SetSelectedMedium(int medium);\
virtual int intf ## _GetSelectedMedium(void);\
virtual void intf ## _SetInstalledMedium(int medium);\
virtual int intf ## _GetInstalledMedium(void);\
virtual AppApiReturnCode intf ## _SelectChannel(int seltype,AppApiChannel channel);\
virtual AppApiReturnCode intf ## _DirectTuning(AppApiDirectTuningParameters param);\
virtual AppApiReturnCode intf ## _GetUserParentalRating(AppApiParentalRating * Rating);\
virtual AppApiReturnCode intf ## _GetStreamParentalRating(AppApiParentalRating * Rating);\
virtual AppApiReturnCode intf ## _IsChannelLocked(int * Status);\
virtual AppApiReturnCode intf ## _EnableSubtitle(void);\
virtual AppApiReturnCode intf ## _DisableSubtitle(void);\
virtual AppApiReturnCode intf ## _DisableClosedCaption(void);\
virtual AppApiReturnCode intf ## _EnableClosedCaption(void);\
virtual AppApiReturnCode intf ## _GetCCSettings(int * CCSetting);\
virtual AppApiReturnCode intf ## _GetCurrentProgram(AppApiChannel * Channel);\
virtual AppApiReturnCode intf ## _EnableLocks(Bool enable);\
virtual AppApiReturnCode intf ## _GetSubtitleSetting(int * SubtitleSetting);\
virtual int intf ## _GetCurrentPMTPID(void);\
virtual void intf ## _SetChannelUniqueNodeId(AppApiChannel channel,Nat64 node_id);\
virtual AppApiReturnCode intf ## _GetCurrentSubtitleStatus(AppApiSubtitleType * SubtitleType);\
virtual AppApiReturnCode intf ## _GetCurrentTeletextStatus(Bool * Present);\
virtual AppApiReturnCode intf ## _GetCurrentVisuallyImpairedStatus(Bool * Present);\
virtual AppApiReturnCode intf ## _GetCurrentAudioLanguage(int * Language);\
virtual AppApiReturnCode intf ## _GetCurrentSubtitleLanguage(int * Language);\
virtual AppApiReturnCode intf ## _GetCurrentAudioType(int * AudioType);\
virtual AppApiReturnCode intf ## _GetCurrentSubtitleType(int * SubtitleType);\
virtual AppApiReturnCode intf ## _GetCurrentSatelliteName(Nat16 * SatelliteName);\
virtual AppApiReturnCode intf ## _SaveChannelMap(char * destdir,int MapType);\
virtual AppApiReturnCode intf ## _LoadChannelMap(char * sourcedir,int MapType);\
class Comp ## _ ## intf : public IHsvProgramDataControl3 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SetSelectedMedium(int medium){ return m_parent->intf ## _SetSelectedMedium(medium);}\
virtual int GetSelectedMedium(void){ return m_parent->intf ## _GetSelectedMedium();}\
virtual void SetInstalledMedium(int medium){ return m_parent->intf ## _SetInstalledMedium(medium);}\
virtual int GetInstalledMedium(void){ return m_parent->intf ## _GetInstalledMedium();}\
virtual AppApiReturnCode SelectChannel(int seltype,AppApiChannel channel){ return m_parent->intf ## _SelectChannel(seltype,channel);}\
virtual AppApiReturnCode DirectTuning(AppApiDirectTuningParameters param){ return m_parent->intf ## _DirectTuning(param);}\
virtual AppApiReturnCode GetUserParentalRating(AppApiParentalRating * Rating){ return m_parent->intf ## _GetUserParentalRating(Rating);}\
virtual AppApiReturnCode GetStreamParentalRating(AppApiParentalRating * Rating){ return m_parent->intf ## _GetStreamParentalRating(Rating);}\
virtual AppApiReturnCode IsChannelLocked(int * Status){ return m_parent->intf ## _IsChannelLocked(Status);}\
virtual AppApiReturnCode EnableSubtitle(void){ return m_parent->intf ## _EnableSubtitle();}\
virtual AppApiReturnCode DisableSubtitle(void){ return m_parent->intf ## _DisableSubtitle();}\
virtual AppApiReturnCode DisableClosedCaption(void){ return m_parent->intf ## _DisableClosedCaption();}\
virtual AppApiReturnCode EnableClosedCaption(void){ return m_parent->intf ## _EnableClosedCaption();}\
virtual AppApiReturnCode GetCCSettings(int * CCSetting){ return m_parent->intf ## _GetCCSettings(CCSetting);}\
virtual AppApiReturnCode GetCurrentProgram(AppApiChannel * Channel){ return m_parent->intf ## _GetCurrentProgram(Channel);}\
virtual AppApiReturnCode EnableLocks(Bool enable){ return m_parent->intf ## _EnableLocks(enable);}\
virtual AppApiReturnCode GetSubtitleSetting(int * SubtitleSetting){ return m_parent->intf ## _GetSubtitleSetting(SubtitleSetting);}\
virtual int GetCurrentPMTPID(void){ return m_parent->intf ## _GetCurrentPMTPID();}\
virtual void SetChannelUniqueNodeId(AppApiChannel channel,Nat64 node_id){ return m_parent->intf ## _SetChannelUniqueNodeId(channel,node_id);}\
virtual AppApiReturnCode GetCurrentSubtitleStatus(AppApiSubtitleType * SubtitleType){ return m_parent->intf ## _GetCurrentSubtitleStatus(SubtitleType);}\
virtual AppApiReturnCode GetCurrentTeletextStatus(Bool * Present){ return m_parent->intf ## _GetCurrentTeletextStatus(Present);}\
virtual AppApiReturnCode GetCurrentVisuallyImpairedStatus(Bool * Present){ return m_parent->intf ## _GetCurrentVisuallyImpairedStatus(Present);}\
virtual AppApiReturnCode GetCurrentAudioLanguage(int * Language){ return m_parent->intf ## _GetCurrentAudioLanguage(Language);}\
virtual AppApiReturnCode GetCurrentSubtitleLanguage(int * Language){ return m_parent->intf ## _GetCurrentSubtitleLanguage(Language);}\
virtual AppApiReturnCode GetCurrentAudioType(int * AudioType){ return m_parent->intf ## _GetCurrentAudioType(AudioType);}\
virtual AppApiReturnCode GetCurrentSubtitleType(int * SubtitleType){ return m_parent->intf ## _GetCurrentSubtitleType(SubtitleType);}\
virtual AppApiReturnCode GetCurrentSatelliteName(Nat16 * SatelliteName){ return m_parent->intf ## _GetCurrentSatelliteName(SatelliteName);}\
virtual AppApiReturnCode SaveChannelMap(char * destdir,int MapType){ return m_parent->intf ## _SaveChannelMap(destdir,MapType);}\
virtual AppApiReturnCode LoadChannelMap(char * sourcedir,int MapType){ return m_parent->intf ## _LoadChannelMap(sourcedir,MapType);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
