#ifndef IHSVPROGRAMDATA_H
#define IHSVPROGRAMDATA_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramData
{
public:
	virtual ~IHsvProgramData(){}
	virtual int BoolLock(void)= 0;
	virtual int BoolFavorite(void)= 0;
	virtual int BoolFavorite1(void)= 0;
	virtual int BoolFavorite2(void)= 0;
	virtual int BoolFavorite3(void)= 0;
	virtual int BoolPreferredFavorite(void)= 0;
	virtual int BoolPreferredNicam(void)= 0;
	virtual int BoolPreferredStereo(void)= 0;
	virtual int BoolSAP(void)= 0;
	virtual int BoolHMProtectedChannel(void)= 0;
	virtual int BoolHMBlanked(void)= 0;
	virtual int BoolUserHidden(void)= 0;
	virtual int BoolSystemHidden(void)= 0;
	virtual int BoolNumericSelect(void)= 0;
	virtual int BoolEpgChannel(void)= 0;
	virtual int BoolEPGShortInfoEnabled(void)= 0;
	virtual int BoolNewPreset(void)= 0;
	virtual int BoolFreeCiMode(void)= 0;
	virtual int BoolTuned(void)= 0;
	virtual int BoolDeTuned(void)= 0;
	virtual int BoolAttenuator(void)= 0;
	virtual int BoolAgcInstalled(void)= 0;
	virtual int BoolChannelVirgin(void)= 0;
	virtual int BoolUpdateName(void)= 0;
	virtual int IntDeltaVolume(void)= 0;
	virtual int Nat32DateStamp(void)= 0;
	virtual int Nat32AppsCookie(void)= 0;
	virtual int Nat32TxtCookie(void)= 0;
	virtual int Nat32CesvcCookie(void)= 0;
	virtual int Nat32DvbType(void)= 0;
	virtual int StringChannelName(void)= 0;
	virtual int StringExtChannelName(void)= 0;
	virtual int IntFrequency(void)= 0;
	virtual int IntTvSystem(void)= 0;
	virtual int IntModulation(void)= 0;
	virtual int IntNewChannelMap(void)= 0;
	virtual int IntSignalStrength(void)= 0;
	virtual int IntSignalQuality(void)= 0;
	virtual int IntColoursystem(void)= 0;
	virtual int IntDecoderType(void)= 0;
	virtual int IntFineTuneOffset(void)= 0;
	virtual int IntFineTuneFrequency(void)= 0;
	virtual int Nat32SymbolRate(void)= 0;
	virtual int IntNetworkId(void)= 0;
	virtual int IntOriginalNwId(void)= 0;
	virtual int IntTsid(void)= 0;
	virtual int IntServiceId(void)= 0;
	virtual int IntServiceType(void)= 0;
	virtual int IntPmtPid(void)= 0;
	virtual int IntPcrPid(void)= 0;
	virtual int IntVideoPid(void)= 0;
	virtual int IntVideoStreamType(void)= 0;
	virtual int IntAudioPid(void)= 0;
	virtual int IntAudioStreamType(void)= 0;
	virtual int IntSecAudioPid(void)= 0;
	virtual int IntSecAudioStreamType(void)= 0;
	virtual int IntInstallMode(void)= 0;
	virtual int IntCniNi(void)= 0;
	virtual int IntDataIndicator(void)= 0;
	virtual int IntPresetNumber(void)= 0;
	virtual int IntModulationType(void)= 0;
	virtual int IntLCN(void)= 0;
	virtual int IntStreamPriority(void)= 0;
	virtual int IntHMMapChannelNo(void)= 0;
	virtual int IntPtc(void)= 0;
	virtual int IntAssociatedDecoder(void)= 0;
	virtual int IntChannelBandwidth(void)= 0;
	#define IHsvProgramData_DecoderNone		((int)0 )
	#define IHsvProgramData_DecoderExt1		((int)1 )
	#define IHsvProgramData_DecoderExt2		((int)2 )
	#define IHsvProgramData_Antenna		((int)0 )
	#define IHsvProgramData_Cable		((int)1 )
	virtual int BoolMatchBrandFlag(void)= 0;
	virtual int Nat32NumBrandIds(void)= 0;
	virtual int StringBrandIds(void)= 0;
	virtual Bool IsValidChannel(AppApiChannel channel)= 0;
	virtual Bool IsChannelInstalled(AppApiChannel * channel)= 0;
	virtual Bool IsAttributeSupported(int attribute)= 0;
	virtual void ClearCurrentTable(void)= 0;
	virtual void ClearAllTables(void)= 0;
	virtual AppApiReturnCode GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value)= 0;
	virtual AppApiReturnCode GetChannelDataInt(AppApiChannel channel,int dataid,int * value)= 0;
	virtual AppApiReturnCode GetChannelDataNat32(AppApiChannel channel,int dataid,Nat32 * value)= 0;
	virtual AppApiReturnCode GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size)= 0;
	virtual AppApiReturnCode StoreChannelDataBool(AppApiChannel channel,int dataid,Bool value)= 0;
	virtual AppApiReturnCode StoreChannelDataInt(AppApiChannel channel,int dataid,int value)= 0;
	virtual AppApiReturnCode StoreChannelDataNat32(AppApiChannel channel,int dataid,Nat32 value)= 0;
	virtual AppApiReturnCode StoreChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size)= 0;
	virtual AppApiReturnCode GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc)= 0;
	virtual AppApiReturnCode LoadChannelTable(char * dir)= 0;
	virtual AppApiReturnCode SaveChannelTable(char * dir)= 0;
	virtual AppApiReturnCode SwapChannels(AppApiChannel channel1,AppApiChannel channel2)= 0;
	virtual AppApiReturnCode ReorderChannels(AppApiChannel channel1,AppApiChannel channel2,Bool Swap)= 0;
	virtual AppApiReturnCode LoadChannelTableFromMedium(char * dir,int medium)= 0;
	virtual AppApiReturnCode SaveChannelTableToMedium(char * dir,int medium)= 0;
};


#define IHsvProgramDataImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsValidChannel(AppApiChannel channel);\
virtual Bool intf ## _IsChannelInstalled(AppApiChannel * channel);\
virtual Bool intf ## _IsAttributeSupported(int attribute);\
virtual void intf ## _ClearCurrentTable(void);\
virtual void intf ## _ClearAllTables(void);\
virtual AppApiReturnCode intf ## _GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value);\
virtual AppApiReturnCode intf ## _GetChannelDataInt(AppApiChannel channel,int dataid,int * value);\
virtual AppApiReturnCode intf ## _GetChannelDataNat32(AppApiChannel channel,int dataid,Nat32 * value);\
virtual AppApiReturnCode intf ## _GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size);\
virtual AppApiReturnCode intf ## _StoreChannelDataBool(AppApiChannel channel,int dataid,Bool value);\
virtual AppApiReturnCode intf ## _StoreChannelDataInt(AppApiChannel channel,int dataid,int value);\
virtual AppApiReturnCode intf ## _StoreChannelDataNat32(AppApiChannel channel,int dataid,Nat32 value);\
virtual AppApiReturnCode intf ## _StoreChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size);\
virtual AppApiReturnCode intf ## _GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc);\
virtual AppApiReturnCode intf ## _LoadChannelTable(char * dir);\
virtual AppApiReturnCode intf ## _SaveChannelTable(char * dir);\
virtual AppApiReturnCode intf ## _SwapChannels(AppApiChannel channel1,AppApiChannel channel2);\
virtual AppApiReturnCode intf ## _ReorderChannels(AppApiChannel channel1,AppApiChannel channel2,Bool Swap);\
virtual AppApiReturnCode intf ## _LoadChannelTableFromMedium(char * dir,int medium);\
virtual AppApiReturnCode intf ## _SaveChannelTableToMedium(char * dir,int medium);\
class Comp ## _ ## intf : public IHsvProgramData \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_BoolLock; \
    InterfaceParam<Comp,int> m_BoolFavorite; \
    InterfaceParam<Comp,int> m_BoolFavorite1; \
    InterfaceParam<Comp,int> m_BoolFavorite2; \
    InterfaceParam<Comp,int> m_BoolFavorite3; \
    InterfaceParam<Comp,int> m_BoolPreferredFavorite; \
    InterfaceParam<Comp,int> m_BoolPreferredNicam; \
    InterfaceParam<Comp,int> m_BoolPreferredStereo; \
    InterfaceParam<Comp,int> m_BoolSAP; \
    InterfaceParam<Comp,int> m_BoolHMProtectedChannel; \
    InterfaceParam<Comp,int> m_BoolHMBlanked; \
    InterfaceParam<Comp,int> m_BoolUserHidden; \
    InterfaceParam<Comp,int> m_BoolSystemHidden; \
    InterfaceParam<Comp,int> m_BoolNumericSelect; \
    InterfaceParam<Comp,int> m_BoolEpgChannel; \
    InterfaceParam<Comp,int> m_BoolEPGShortInfoEnabled; \
    InterfaceParam<Comp,int> m_BoolNewPreset; \
    InterfaceParam<Comp,int> m_BoolFreeCiMode; \
    InterfaceParam<Comp,int> m_BoolTuned; \
    InterfaceParam<Comp,int> m_BoolDeTuned; \
    InterfaceParam<Comp,int> m_BoolAttenuator; \
    InterfaceParam<Comp,int> m_BoolAgcInstalled; \
    InterfaceParam<Comp,int> m_BoolChannelVirgin; \
    InterfaceParam<Comp,int> m_BoolUpdateName; \
    InterfaceParam<Comp,int> m_IntDeltaVolume; \
    InterfaceParam<Comp,int> m_Nat32DateStamp; \
    InterfaceParam<Comp,int> m_Nat32AppsCookie; \
    InterfaceParam<Comp,int> m_Nat32TxtCookie; \
    InterfaceParam<Comp,int> m_Nat32CesvcCookie; \
    InterfaceParam<Comp,int> m_Nat32DvbType; \
    InterfaceParam<Comp,int> m_StringChannelName; \
    InterfaceParam<Comp,int> m_StringExtChannelName; \
    InterfaceParam<Comp,int> m_IntFrequency; \
    InterfaceParam<Comp,int> m_IntTvSystem; \
    InterfaceParam<Comp,int> m_IntModulation; \
    InterfaceParam<Comp,int> m_IntNewChannelMap; \
    InterfaceParam<Comp,int> m_IntSignalStrength; \
    InterfaceParam<Comp,int> m_IntSignalQuality; \
    InterfaceParam<Comp,int> m_IntColoursystem; \
    InterfaceParam<Comp,int> m_IntDecoderType; \
    InterfaceParam<Comp,int> m_IntFineTuneOffset; \
    InterfaceParam<Comp,int> m_IntFineTuneFrequency; \
    InterfaceParam<Comp,int> m_Nat32SymbolRate; \
    InterfaceParam<Comp,int> m_IntNetworkId; \
    InterfaceParam<Comp,int> m_IntOriginalNwId; \
    InterfaceParam<Comp,int> m_IntTsid; \
    InterfaceParam<Comp,int> m_IntServiceId; \
    InterfaceParam<Comp,int> m_IntServiceType; \
    InterfaceParam<Comp,int> m_IntPmtPid; \
    InterfaceParam<Comp,int> m_IntPcrPid; \
    InterfaceParam<Comp,int> m_IntVideoPid; \
    InterfaceParam<Comp,int> m_IntVideoStreamType; \
    InterfaceParam<Comp,int> m_IntAudioPid; \
    InterfaceParam<Comp,int> m_IntAudioStreamType; \
    InterfaceParam<Comp,int> m_IntSecAudioPid; \
    InterfaceParam<Comp,int> m_IntSecAudioStreamType; \
    InterfaceParam<Comp,int> m_IntInstallMode; \
    InterfaceParam<Comp,int> m_IntCniNi; \
    InterfaceParam<Comp,int> m_IntDataIndicator; \
    InterfaceParam<Comp,int> m_IntPresetNumber; \
    InterfaceParam<Comp,int> m_IntModulationType; \
    InterfaceParam<Comp,int> m_IntLCN; \
    InterfaceParam<Comp,int> m_IntStreamPriority; \
    InterfaceParam<Comp,int> m_IntHMMapChannelNo; \
    InterfaceParam<Comp,int> m_IntPtc; \
    InterfaceParam<Comp,int> m_IntAssociatedDecoder; \
    InterfaceParam<Comp,int> m_IntChannelBandwidth; \
    InterfaceParam<Comp,int> m_BoolMatchBrandFlag; \
    InterfaceParam<Comp,int> m_Nat32NumBrandIds; \
    InterfaceParam<Comp,int> m_StringBrandIds; \
    Comp ## _ ## intf( Comp *parent):m_BoolLock(parent),m_BoolFavorite(parent),m_BoolFavorite1(parent),m_BoolFavorite2(parent),m_BoolFavorite3(parent),m_BoolPreferredFavorite(parent),m_BoolPreferredNicam(parent),m_BoolPreferredStereo(parent),m_BoolSAP(parent),m_BoolHMProtectedChannel(parent),m_BoolHMBlanked(parent),m_BoolUserHidden(parent),m_BoolSystemHidden(parent),m_BoolNumericSelect(parent),m_BoolEpgChannel(parent),m_BoolEPGShortInfoEnabled(parent),m_BoolNewPreset(parent),m_BoolFreeCiMode(parent),m_BoolTuned(parent),m_BoolDeTuned(parent),m_BoolAttenuator(parent),m_BoolAgcInstalled(parent),m_BoolChannelVirgin(parent),m_BoolUpdateName(parent),m_IntDeltaVolume(parent),m_Nat32DateStamp(parent),m_Nat32AppsCookie(parent),m_Nat32TxtCookie(parent),m_Nat32CesvcCookie(parent),m_Nat32DvbType(parent),m_StringChannelName(parent),m_StringExtChannelName(parent),m_IntFrequency(parent),m_IntTvSystem(parent),m_IntModulation(parent),m_IntNewChannelMap(parent),m_IntSignalStrength(parent),m_IntSignalQuality(parent),m_IntColoursystem(parent),m_IntDecoderType(parent),m_IntFineTuneOffset(parent),m_IntFineTuneFrequency(parent),m_Nat32SymbolRate(parent),m_IntNetworkId(parent),m_IntOriginalNwId(parent),m_IntTsid(parent),m_IntServiceId(parent),m_IntServiceType(parent),m_IntPmtPid(parent),m_IntPcrPid(parent),m_IntVideoPid(parent),m_IntVideoStreamType(parent),m_IntAudioPid(parent),m_IntAudioStreamType(parent),m_IntSecAudioPid(parent),m_IntSecAudioStreamType(parent),m_IntInstallMode(parent),m_IntCniNi(parent),m_IntDataIndicator(parent),m_IntPresetNumber(parent),m_IntModulationType(parent),m_IntLCN(parent),m_IntStreamPriority(parent),m_IntHMMapChannelNo(parent),m_IntPtc(parent),m_IntAssociatedDecoder(parent),m_IntChannelBandwidth(parent),m_BoolMatchBrandFlag(parent),m_Nat32NumBrandIds(parent),m_StringBrandIds(parent) \
    {\
        m_parent = parent;\
    }\
virtual int BoolLock(void){ return m_BoolLock.Call();}\
virtual int BoolFavorite(void){ return m_BoolFavorite.Call();}\
virtual int BoolFavorite1(void){ return m_BoolFavorite1.Call();}\
virtual int BoolFavorite2(void){ return m_BoolFavorite2.Call();}\
virtual int BoolFavorite3(void){ return m_BoolFavorite3.Call();}\
virtual int BoolPreferredFavorite(void){ return m_BoolPreferredFavorite.Call();}\
virtual int BoolPreferredNicam(void){ return m_BoolPreferredNicam.Call();}\
virtual int BoolPreferredStereo(void){ return m_BoolPreferredStereo.Call();}\
virtual int BoolSAP(void){ return m_BoolSAP.Call();}\
virtual int BoolHMProtectedChannel(void){ return m_BoolHMProtectedChannel.Call();}\
virtual int BoolHMBlanked(void){ return m_BoolHMBlanked.Call();}\
virtual int BoolUserHidden(void){ return m_BoolUserHidden.Call();}\
virtual int BoolSystemHidden(void){ return m_BoolSystemHidden.Call();}\
virtual int BoolNumericSelect(void){ return m_BoolNumericSelect.Call();}\
virtual int BoolEpgChannel(void){ return m_BoolEpgChannel.Call();}\
virtual int BoolEPGShortInfoEnabled(void){ return m_BoolEPGShortInfoEnabled.Call();}\
virtual int BoolNewPreset(void){ return m_BoolNewPreset.Call();}\
virtual int BoolFreeCiMode(void){ return m_BoolFreeCiMode.Call();}\
virtual int BoolTuned(void){ return m_BoolTuned.Call();}\
virtual int BoolDeTuned(void){ return m_BoolDeTuned.Call();}\
virtual int BoolAttenuator(void){ return m_BoolAttenuator.Call();}\
virtual int BoolAgcInstalled(void){ return m_BoolAgcInstalled.Call();}\
virtual int BoolChannelVirgin(void){ return m_BoolChannelVirgin.Call();}\
virtual int BoolUpdateName(void){ return m_BoolUpdateName.Call();}\
virtual int IntDeltaVolume(void){ return m_IntDeltaVolume.Call();}\
virtual int Nat32DateStamp(void){ return m_Nat32DateStamp.Call();}\
virtual int Nat32AppsCookie(void){ return m_Nat32AppsCookie.Call();}\
virtual int Nat32TxtCookie(void){ return m_Nat32TxtCookie.Call();}\
virtual int Nat32CesvcCookie(void){ return m_Nat32CesvcCookie.Call();}\
virtual int Nat32DvbType(void){ return m_Nat32DvbType.Call();}\
virtual int StringChannelName(void){ return m_StringChannelName.Call();}\
virtual int StringExtChannelName(void){ return m_StringExtChannelName.Call();}\
virtual int IntFrequency(void){ return m_IntFrequency.Call();}\
virtual int IntTvSystem(void){ return m_IntTvSystem.Call();}\
virtual int IntModulation(void){ return m_IntModulation.Call();}\
virtual int IntNewChannelMap(void){ return m_IntNewChannelMap.Call();}\
virtual int IntSignalStrength(void){ return m_IntSignalStrength.Call();}\
virtual int IntSignalQuality(void){ return m_IntSignalQuality.Call();}\
virtual int IntColoursystem(void){ return m_IntColoursystem.Call();}\
virtual int IntDecoderType(void){ return m_IntDecoderType.Call();}\
virtual int IntFineTuneOffset(void){ return m_IntFineTuneOffset.Call();}\
virtual int IntFineTuneFrequency(void){ return m_IntFineTuneFrequency.Call();}\
virtual int Nat32SymbolRate(void){ return m_Nat32SymbolRate.Call();}\
virtual int IntNetworkId(void){ return m_IntNetworkId.Call();}\
virtual int IntOriginalNwId(void){ return m_IntOriginalNwId.Call();}\
virtual int IntTsid(void){ return m_IntTsid.Call();}\
virtual int IntServiceId(void){ return m_IntServiceId.Call();}\
virtual int IntServiceType(void){ return m_IntServiceType.Call();}\
virtual int IntPmtPid(void){ return m_IntPmtPid.Call();}\
virtual int IntPcrPid(void){ return m_IntPcrPid.Call();}\
virtual int IntVideoPid(void){ return m_IntVideoPid.Call();}\
virtual int IntVideoStreamType(void){ return m_IntVideoStreamType.Call();}\
virtual int IntAudioPid(void){ return m_IntAudioPid.Call();}\
virtual int IntAudioStreamType(void){ return m_IntAudioStreamType.Call();}\
virtual int IntSecAudioPid(void){ return m_IntSecAudioPid.Call();}\
virtual int IntSecAudioStreamType(void){ return m_IntSecAudioStreamType.Call();}\
virtual int IntInstallMode(void){ return m_IntInstallMode.Call();}\
virtual int IntCniNi(void){ return m_IntCniNi.Call();}\
virtual int IntDataIndicator(void){ return m_IntDataIndicator.Call();}\
virtual int IntPresetNumber(void){ return m_IntPresetNumber.Call();}\
virtual int IntModulationType(void){ return m_IntModulationType.Call();}\
virtual int IntLCN(void){ return m_IntLCN.Call();}\
virtual int IntStreamPriority(void){ return m_IntStreamPriority.Call();}\
virtual int IntHMMapChannelNo(void){ return m_IntHMMapChannelNo.Call();}\
virtual int IntPtc(void){ return m_IntPtc.Call();}\
virtual int IntAssociatedDecoder(void){ return m_IntAssociatedDecoder.Call();}\
virtual int IntChannelBandwidth(void){ return m_IntChannelBandwidth.Call();}\
virtual int BoolMatchBrandFlag(void){ return m_BoolMatchBrandFlag.Call();}\
virtual int Nat32NumBrandIds(void){ return m_Nat32NumBrandIds.Call();}\
virtual int StringBrandIds(void){ return m_StringBrandIds.Call();}\
virtual Bool IsValidChannel(AppApiChannel channel){ return m_parent->intf ## _IsValidChannel(channel);}\
virtual Bool IsChannelInstalled(AppApiChannel * channel){ return m_parent->intf ## _IsChannelInstalled(channel);}\
virtual Bool IsAttributeSupported(int attribute){ return m_parent->intf ## _IsAttributeSupported(attribute);}\
virtual void ClearCurrentTable(void){ return m_parent->intf ## _ClearCurrentTable();}\
virtual void ClearAllTables(void){ return m_parent->intf ## _ClearAllTables();}\
virtual AppApiReturnCode GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value){ return m_parent->intf ## _GetChannelDataBool(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataInt(AppApiChannel channel,int dataid,int * value){ return m_parent->intf ## _GetChannelDataInt(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataNat32(AppApiChannel channel,int dataid,Nat32 * value){ return m_parent->intf ## _GetChannelDataNat32(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size){ return m_parent->intf ## _GetChannelDataString(channel,dataid,value,size);}\
virtual AppApiReturnCode StoreChannelDataBool(AppApiChannel channel,int dataid,Bool value){ return m_parent->intf ## _StoreChannelDataBool(channel,dataid,value);}\
virtual AppApiReturnCode StoreChannelDataInt(AppApiChannel channel,int dataid,int value){ return m_parent->intf ## _StoreChannelDataInt(channel,dataid,value);}\
virtual AppApiReturnCode StoreChannelDataNat32(AppApiChannel channel,int dataid,Nat32 value){ return m_parent->intf ## _StoreChannelDataNat32(channel,dataid,value);}\
virtual AppApiReturnCode StoreChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size){ return m_parent->intf ## _StoreChannelDataString(channel,dataid,value,size);}\
virtual AppApiReturnCode GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc){ return m_parent->intf ## _GetDigitalChannel(channel,OnId,TsId,Sid,Ptc);}\
virtual AppApiReturnCode LoadChannelTable(char * dir){ return m_parent->intf ## _LoadChannelTable(dir);}\
virtual AppApiReturnCode SaveChannelTable(char * dir){ return m_parent->intf ## _SaveChannelTable(dir);}\
virtual AppApiReturnCode SwapChannels(AppApiChannel channel1,AppApiChannel channel2){ return m_parent->intf ## _SwapChannels(channel1,channel2);}\
virtual AppApiReturnCode ReorderChannels(AppApiChannel channel1,AppApiChannel channel2,Bool Swap){ return m_parent->intf ## _ReorderChannels(channel1,channel2,Swap);}\
virtual AppApiReturnCode LoadChannelTableFromMedium(char * dir,int medium){ return m_parent->intf ## _LoadChannelTableFromMedium(dir,medium);}\
virtual AppApiReturnCode SaveChannelTableToMedium(char * dir,int medium){ return m_parent->intf ## _SaveChannelTableToMedium(dir,medium);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
