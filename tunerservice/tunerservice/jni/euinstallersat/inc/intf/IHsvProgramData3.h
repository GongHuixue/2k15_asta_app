#ifndef IHSVPROGRAMDATA3_H
#define IHSVPROGRAMDATA3_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramData3
{
public:
	virtual ~IHsvProgramData3(){}
	#define	IHsvProgramData3_IntLnbNumber		0
	#define	IHsvProgramData3_IntPolarization	1
	#define	IHsvProgramData3_IntFrequency		2
	#define	IHsvProgramData3_Nat32SymbolRate	3
	
	virtual int BoolLock(void)= 0;
	virtual int BoolFavorite(void)= 0;
	virtual int BoolUserHidden(void)= 0;
	virtual int BoolSystemHidden(void)= 0;
	virtual int BoolNewPreset(void)= 0;
	virtual int BoolFreeCiMode(void)= 0;
	virtual int BoolUpdateName(void)= 0;
	virtual int IntDeltaVolume(void)= 0;
	virtual int Nat32DateStamp(void)= 0;
	virtual int Nat32AppsCookie(void)= 0;
	virtual int Nat32TxtCookie(void)= 0;
	virtual int StringChannelName(void)= 0;
	virtual int StringExtChannelName(void)= 0;
	virtual int IntModulation(void)= 0;
	virtual int IntSignalStrength(void)= 0;
	virtual int IntSignalQuality(void)= 0;
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
	virtual int IntPresetNumber(void)= 0;
	virtual int IntModulationType(void)= 0;
	virtual int IntLCN(void)= 0;
	virtual int IntPtc(void)= 0;
	#define IHsvProgramData3_DecoderNone		((int)0 )
	#define IHsvProgramData3_DecoderExt1		((int)1 )
	#define IHsvProgramData3_DecoderExt2		((int)2 )
	#define IHsvProgramData3_Antenna		((int)0 )
	#define IHsvProgramData3_Cable		((int)1 )
	virtual int IntSystemHidden(void)= 0;
	virtual int IntNumericSelect(void)= 0;
	virtual int IntNewChannel(void)= 0;
	virtual int StringSatelliteName(void)= 0;
	virtual int IntSrcambledStatus(void)= 0;
	virtual int IntInstalledSatelliteNumber(void)= 0;
	virtual int IntUserHidden(void)= 0;
	virtual int FavoriteNumber(void)= 0;
	virtual int IntHbbTvOption(void)= 0;
	virtual Bool BoolChannelLock(void)= 0;
	virtual int StringTxtPages(void)= 0;
	virtual int IntLogoURL(void)= 0;
	virtual int BoolMatchBrandFlag(void)= 0;
	virtual int Nat32NumBrandIds(void)= 0;
	virtual int StringBrandIds(void)= 0;
	virtual Nat64 Nat64UniqueNodeId(void)= 0;
	virtual Bool BoolUserModifiedLogo(void)= 0;
	virtual int Nat32TPID(void)= 0;
	virtual int IntSatelliteId(void)= 0;
	virtual int IntInstalledSatelliteId(void)= 0;
	virtual int IntPackageGroup(void)= 0;
	virtual int IntDpTsid(void)= 0;
	virtual int IntDpServiceId(void)= 0;
	virtual int MultipleLCN(void)= 0;
	virtual int MultiplePreset(void)= 0;
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
	virtual AppApiReturnCode GetDigitalChannelForFreesat(int *MultiplePresetList,int OnId,int TsId,int Sid,int Ptc)= 0;
	virtual AppApiReturnCode SwapChannels(AppApiChannel channel1,AppApiChannel channel2)= 0;
	virtual AppApiReturnCode LoadChannelTable(char * dir)= 0;
	virtual AppApiReturnCode SaveChannelTable(char * dir)= 0;
	virtual AppApiReturnCode ReorderChannels(AppApiChannel channel1,AppApiChannel channel2,Bool Swap)= 0;
	virtual AppApiReturnCode LoadChannelTableFromMedium(char * dir,int medium)= 0;
	virtual AppApiReturnCode SaveChannelTableToMedium(char * dir,int medium)= 0;
	virtual AppApiReturnCode GetMediumFromTable(char * dir,int * medium)= 0;
	virtual AppApiReturnCode GetNoOfBarkerMultiplexes(int * NoOfMuxes)= 0;
	virtual AppApiReturnCode GetBarkerMultiplexByIndex(int index,AppApiMultiplex * muxes)= 0;
	virtual AppApiReturnCode ReArrangeChannels(AppApiChannel channel1,AppApiChannel channel2)= 0;
	virtual AppApiReturnCode GetBarkerMultiplexesForChannel(AppApiChannel channel,int * NoOfMuxes,AppApiMultiplex * muxes)= 0;
	virtual AppApiReturnCode GetOperator(AppApiOperator * OperatorId)= 0;
	virtual AppApiReturnCode StoreChannelDataNat64(AppApiChannel channel,int dataid,Nat64 value)= 0;
	virtual AppApiReturnCode GetChannelDataNat64(AppApiChannel channel,int dataid,Nat64 * value)= 0;
	virtual AppApiReturnCode GetSatelliteName(int LnbNumber,Nat16 * SatelliteName)= 0;
	virtual AppApiReturnCode GetSatellitePackage(AppApiPackageId * PackageId,AppApiPackageGroup * PackageIGroupId)= 0;
};


#define IHsvProgramData3Impl(Comp,intf)    \
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
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Nat64>;\
friend class InterfaceParam<Comp,Bool>;\
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
virtual AppApiReturnCode intf ## _SwapChannels(AppApiChannel channel1,AppApiChannel channel2);\
virtual AppApiReturnCode intf ## _LoadChannelTable(char * dir);\
virtual AppApiReturnCode intf ## _SaveChannelTable(char * dir);\
virtual AppApiReturnCode intf ## _ReorderChannels(AppApiChannel channel1,AppApiChannel channel2,Bool Swap);\
virtual AppApiReturnCode intf ## _LoadChannelTableFromMedium(char * dir,int medium);\
virtual AppApiReturnCode intf ## _SaveChannelTableToMedium(char * dir,int medium);\
virtual AppApiReturnCode intf ## _GetMediumFromTable(char * dir,int * medium);\
virtual AppApiReturnCode intf ## _GetNoOfBarkerMultiplexes(int * NoOfMuxes);\
virtual AppApiReturnCode intf ## _GetBarkerMultiplexByIndex(int index,AppApiMultiplex * muxes);\
virtual AppApiReturnCode intf ## _ReArrangeChannels(AppApiChannel channel1,AppApiChannel channel2);\
virtual AppApiReturnCode intf ## _GetBarkerMultiplexesForChannel(AppApiChannel channel,int * NoOfMuxes,AppApiMultiplex * muxes);\
virtual AppApiReturnCode intf ## _GetOperator(AppApiOperator * OperatorId);\
virtual AppApiReturnCode intf ## _StoreChannelDataNat64(AppApiChannel channel,int dataid,Nat64 value);\
virtual AppApiReturnCode intf ## _GetChannelDataNat64(AppApiChannel channel,int dataid,Nat64 * value);\
virtual AppApiReturnCode intf ## _GetSatelliteName(int LnbNumber,Nat16 * SatelliteName);\
virtual AppApiReturnCode intf ## _GetSatellitePackage(AppApiPackageId * PackageId,AppApiPackageGroup * PackageIGroupId);\
virtual AppApiReturnCode intf ## _GetDigitalChannelForFreesat(int * MultiplePresetList,int OnId,int TsId,int Sid,int Ptc);\
class Comp ## _ ## intf : public IHsvProgramData3 \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_BoolLock; \
    InterfaceParam<Comp,int> m_BoolFavorite; \
    InterfaceParam<Comp,int> m_BoolUserHidden; \
    InterfaceParam<Comp,int> m_BoolSystemHidden; \
    InterfaceParam<Comp,int> m_BoolNewPreset; \
    InterfaceParam<Comp,int> m_BoolFreeCiMode; \
    InterfaceParam<Comp,int> m_BoolUpdateName; \
    InterfaceParam<Comp,int> m_IntDeltaVolume; \
    InterfaceParam<Comp,int> m_Nat32DateStamp; \
    InterfaceParam<Comp,int> m_Nat32AppsCookie; \
    InterfaceParam<Comp,int> m_Nat32TxtCookie; \
    InterfaceParam<Comp,int> m_StringChannelName; \
    InterfaceParam<Comp,int> m_StringExtChannelName; \
    InterfaceParam<Comp,int> m_IntModulation; \
    InterfaceParam<Comp,int> m_IntSignalStrength; \
    InterfaceParam<Comp,int> m_IntSignalQuality; \
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
    InterfaceParam<Comp,int> m_IntPresetNumber; \
    InterfaceParam<Comp,int> m_IntModulationType; \
    InterfaceParam<Comp,int> m_IntLCN; \
    InterfaceParam<Comp,int> m_IntPtc; \
    InterfaceParam<Comp,int> m_IntSystemHidden; \
    InterfaceParam<Comp,int> m_IntNumericSelect; \
    InterfaceParam<Comp,int> m_IntNewChannel; \
    InterfaceParam<Comp,int> m_StringSatelliteName; \
    InterfaceParam<Comp,int> m_IntSrcambledStatus; \
    InterfaceParam<Comp,int> m_IntInstalledSatelliteNumber; \
    InterfaceParam<Comp,int> m_IntUserHidden; \
    InterfaceParam<Comp,int> m_FavoriteNumber; \
    InterfaceParam<Comp,int> m_IntHbbTvOption; \
    InterfaceParam<Comp,Bool> m_BoolChannelLock; \
    InterfaceParam<Comp,int> m_StringTxtPages; \
    InterfaceParam<Comp,int> m_IntLogoURL; \
    InterfaceParam<Comp,int> m_BoolMatchBrandFlag; \
    InterfaceParam<Comp,int> m_Nat32NumBrandIds; \
    InterfaceParam<Comp,int> m_StringBrandIds; \
    InterfaceParam<Comp,Nat64> m_Nat64UniqueNodeId; \
    InterfaceParam<Comp,Bool> m_BoolUserModifiedLogo; \
    InterfaceParam<Comp,int> m_Nat32TPID; \
    InterfaceParam<Comp,int> m_IntSatelliteId; \
    InterfaceParam<Comp,int> m_IntInstalledSatelliteId; \
    InterfaceParam<Comp,int> m_IntPackageGroup; \
    InterfaceParam<Comp,int> m_IntDpTsid; \
    InterfaceParam<Comp,int> m_IntDpServiceId; \
    InterfaceParam<Comp,int> m_MultipleLCN; \
    InterfaceParam<Comp,int> m_MultiplePreset; \
    Comp ## _ ## intf( Comp *parent):m_BoolLock(parent),m_BoolFavorite(parent),m_BoolUserHidden(parent),m_BoolSystemHidden(parent),m_BoolNewPreset(parent),m_BoolFreeCiMode(parent),m_BoolUpdateName(parent),m_IntDeltaVolume(parent),m_Nat32DateStamp(parent),m_Nat32AppsCookie(parent),m_Nat32TxtCookie(parent),m_StringChannelName(parent),m_StringExtChannelName(parent),m_IntModulation(parent),m_IntSignalStrength(parent),m_IntSignalQuality(parent),m_IntNetworkId(parent),m_IntOriginalNwId(parent),m_IntTsid(parent),m_IntServiceId(parent),m_IntServiceType(parent),m_IntPmtPid(parent),m_IntPcrPid(parent),m_IntVideoPid(parent),m_IntVideoStreamType(parent),m_IntAudioPid(parent),m_IntAudioStreamType(parent),m_IntSecAudioPid(parent),m_IntSecAudioStreamType(parent),m_IntPresetNumber(parent),m_IntModulationType(parent),m_IntLCN(parent),m_IntPtc(parent),m_IntSystemHidden(parent),m_IntNumericSelect(parent),m_IntNewChannel(parent),m_StringSatelliteName(parent),m_IntSrcambledStatus(parent),m_IntInstalledSatelliteNumber(parent),m_IntUserHidden(parent),m_FavoriteNumber(parent),m_IntHbbTvOption(parent),m_BoolChannelLock(parent),m_StringTxtPages(parent),m_IntLogoURL(parent),m_BoolMatchBrandFlag(parent),m_Nat32NumBrandIds(parent),m_StringBrandIds(parent),m_Nat64UniqueNodeId(parent),m_BoolUserModifiedLogo(parent),m_Nat32TPID(parent),m_IntSatelliteId(parent),m_IntInstalledSatelliteId(parent),m_IntPackageGroup(parent),m_IntDpTsid(parent),m_IntDpServiceId(parent),m_MultipleLCN(parent),m_MultiplePreset(parent) \
    {\
        m_parent = parent;\
    }\
virtual int BoolLock(void){ return m_BoolLock.Call();}\
virtual int BoolFavorite(void){ return m_BoolFavorite.Call();}\
virtual int BoolUserHidden(void){ return m_BoolUserHidden.Call();}\
virtual int BoolSystemHidden(void){ return m_BoolSystemHidden.Call();}\
virtual int BoolNewPreset(void){ return m_BoolNewPreset.Call();}\
virtual int BoolFreeCiMode(void){ return m_BoolFreeCiMode.Call();}\
virtual int BoolUpdateName(void){ return m_BoolUpdateName.Call();}\
virtual int IntDeltaVolume(void){ return m_IntDeltaVolume.Call();}\
virtual int Nat32DateStamp(void){ return m_Nat32DateStamp.Call();}\
virtual int Nat32AppsCookie(void){ return m_Nat32AppsCookie.Call();}\
virtual int Nat32TxtCookie(void){ return m_Nat32TxtCookie.Call();}\
virtual int StringChannelName(void){ return m_StringChannelName.Call();}\
virtual int StringExtChannelName(void){ return m_StringExtChannelName.Call();}\
virtual int IntModulation(void){ return m_IntModulation.Call();}\
virtual int IntSignalStrength(void){ return m_IntSignalStrength.Call();}\
virtual int IntSignalQuality(void){ return m_IntSignalQuality.Call();}\
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
virtual int IntPresetNumber(void){ return m_IntPresetNumber.Call();}\
virtual int IntModulationType(void){ return m_IntModulationType.Call();}\
virtual int IntLCN(void){ return m_IntLCN.Call();}\
virtual int IntPtc(void){ return m_IntPtc.Call();}\
virtual int IntSystemHidden(void){ return m_IntSystemHidden.Call();}\
virtual int IntNumericSelect(void){ return m_IntNumericSelect.Call();}\
virtual int IntNewChannel(void){ return m_IntNewChannel.Call();}\
virtual int StringSatelliteName(void){ return m_StringSatelliteName.Call();}\
virtual int IntSrcambledStatus(void){ return m_IntSrcambledStatus.Call();}\
virtual int IntInstalledSatelliteNumber(void){ return m_IntInstalledSatelliteNumber.Call();}\
virtual int IntUserHidden(void){ return m_IntUserHidden.Call();}\
virtual int FavoriteNumber(void){ return m_FavoriteNumber.Call();}\
virtual int IntHbbTvOption(void){ return m_IntHbbTvOption.Call();}\
virtual Bool BoolChannelLock(void){ return m_BoolChannelLock.Call();}\
virtual int StringTxtPages(void){ return m_StringTxtPages.Call();}\
virtual int IntLogoURL(void){ return m_IntLogoURL.Call();}\
virtual int BoolMatchBrandFlag(void){ return m_BoolMatchBrandFlag.Call();}\
virtual int Nat32NumBrandIds(void){ return m_Nat32NumBrandIds.Call();}\
virtual int StringBrandIds(void){ return m_StringBrandIds.Call();}\
virtual Nat64 Nat64UniqueNodeId(void){ return m_Nat64UniqueNodeId.Call();}\
virtual Bool BoolUserModifiedLogo(void){ return m_BoolUserModifiedLogo.Call();}\
virtual int Nat32TPID(void){ return m_Nat32TPID.Call();}\
virtual int IntSatelliteId(void){ return m_IntSatelliteId.Call();}\
virtual int IntInstalledSatelliteId(void){ return m_IntInstalledSatelliteId.Call();}\
virtual int IntPackageGroup(void){ return m_IntPackageGroup.Call();}\
virtual int IntDpTsid(void){ return m_IntDpTsid.Call();}\
virtual int IntDpServiceId(void){ return m_IntDpServiceId.Call();}\
virtual int MultipleLCN(void){ return m_MultipleLCN.Call();}\
virtual int MultiplePreset(void){ return m_MultiplePreset.Call();}\
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
virtual AppApiReturnCode SwapChannels(AppApiChannel channel1,AppApiChannel channel2){ return m_parent->intf ## _SwapChannels(channel1,channel2);}\
virtual AppApiReturnCode LoadChannelTable(char * dir){ return m_parent->intf ## _LoadChannelTable(dir);}\
virtual AppApiReturnCode SaveChannelTable(char * dir){ return m_parent->intf ## _SaveChannelTable(dir);}\
virtual AppApiReturnCode ReorderChannels(AppApiChannel channel1,AppApiChannel channel2,Bool Swap){ return m_parent->intf ## _ReorderChannels(channel1,channel2,Swap);}\
virtual AppApiReturnCode LoadChannelTableFromMedium(char * dir,int medium){ return m_parent->intf ## _LoadChannelTableFromMedium(dir,medium);}\
virtual AppApiReturnCode SaveChannelTableToMedium(char * dir,int medium){ return m_parent->intf ## _SaveChannelTableToMedium(dir,medium);}\
virtual AppApiReturnCode GetMediumFromTable(char * dir,int * medium){ return m_parent->intf ## _GetMediumFromTable(dir,medium);}\
virtual AppApiReturnCode GetNoOfBarkerMultiplexes(int * NoOfMuxes){ return m_parent->intf ## _GetNoOfBarkerMultiplexes(NoOfMuxes);}\
virtual AppApiReturnCode GetBarkerMultiplexByIndex(int index,AppApiMultiplex * muxes){ return m_parent->intf ## _GetBarkerMultiplexByIndex(index,muxes);}\
virtual AppApiReturnCode ReArrangeChannels(AppApiChannel channel1,AppApiChannel channel2){ return m_parent->intf ## _ReArrangeChannels(channel1,channel2);}\
virtual AppApiReturnCode GetBarkerMultiplexesForChannel(AppApiChannel channel,int * NoOfMuxes,AppApiMultiplex * muxes){ return m_parent->intf ## _GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes);}\
virtual AppApiReturnCode GetOperator(AppApiOperator * OperatorId){ return m_parent->intf ## _GetOperator(OperatorId);}\
virtual AppApiReturnCode StoreChannelDataNat64(AppApiChannel channel,int dataid,Nat64 value){ return m_parent->intf ## _StoreChannelDataNat64(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataNat64(AppApiChannel channel,int dataid,Nat64 * value){ return m_parent->intf ## _GetChannelDataNat64(channel,dataid,value);}\
virtual AppApiReturnCode GetSatelliteName(int LnbNumber,Nat16 * SatelliteName){ return m_parent->intf ## _GetSatelliteName(LnbNumber,SatelliteName);}\
virtual AppApiReturnCode GetSatellitePackage(AppApiPackageId * PackageId,AppApiPackageGroup * PackageIGroupId){ return m_parent->intf ## _GetSatellitePackage(PackageId,PackageIGroupId);}\
virtual AppApiReturnCode GetDigitalChannelForFreesat(int * MultiplePresetList,int OnId,int TsId,int Sid,int Ptc){ return m_parent->intf ## _GetDigitalChannelForFreesat(MultiplePresetList,OnId,TsId,Sid,Ptc);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
