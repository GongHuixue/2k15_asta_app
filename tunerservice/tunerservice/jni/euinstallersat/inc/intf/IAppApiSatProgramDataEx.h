#ifndef IAPPAPISATPROGRAMDATAEX_H
#define IAPPAPISATPROGRAMDATAEX_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatProgramDataEx
{
public:
	virtual ~IAppApiSatProgramDataEx(){}
	virtual int StringChannelName(void)= 0;
	virtual int IntFrequency(void)= 0;
	virtual int IntPtc(void)= 0;
	virtual int IntNetworkId(void)= 0;
	virtual int IntOriginalNetworkId(void)= 0;
	virtual int IntTsid(void)= 0;
	virtual int IntServiceId(void)= 0;
	virtual int BoolFreeCiMode(void)= 0;
	virtual int IntSystemHidden(void)= 0;
	virtual int IntNumericSelect(void)= 0;
	virtual int IntNewChannel(void)= 0;
	virtual int StringSatelliteName(void)= 0;
	virtual int IntSrcambledStatus(void)= 0;
	virtual int IntServiceType(void)= 0;
	virtual int IntUserHidden(void)= 0;
	virtual int Favorite(void)= 0;
	virtual int FavoriteNumber(void)= 0;
	virtual int IntHbbTvOption(void)= 0;
	virtual Bool BoolChannelLock(void)= 0;
	virtual int IntLogoURL(void)= 0;
	virtual Nat64 Nat64UniqueNodeId(void)= 0;
	virtual int IntTpId(void)= 0;
	virtual int IntLNBId(void)= 0;
	virtual int Nat32SymbolRate(void)= 0;
	virtual int IntModulationType(void)= 0;
	virtual int IntInstalledSatelliteNumber(void)= 0;
	virtual int IntPolarization(void)= 0;
	virtual int IntInstalledSatelliteId(void)= 0;
	virtual int IntDecoderType(void)= 0;
	virtual int IntDpTsid(void)= 0;
	virtual int IntDpServiceId(void)= 0;
	virtual int IntPackageGroup(void)= 0;
	virtual int StringTxtPages(void)= 0;
	virtual int Nat32AppsCookie(void)= 0;
	virtual Bool IsAttributeSupported(int attribute)= 0;
	virtual AppApiReturnCode GetChannelDataInt(AppApiChannel channel,int dataid,int * value)= 0;
	virtual AppApiReturnCode GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value)= 0;
	virtual AppApiReturnCode GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size)= 0;
	virtual AppApiReturnCode GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc_or_Freq)= 0;
	virtual AppApiReturnCode GetNoOfBarkerMultiplexes(int * NoOfMuxes)= 0;
	virtual AppApiReturnCode GetBarkerMultiplexByIndex(int index,AppApiMultiplex * muxes)= 0;
	virtual AppApiReturnCode StoreChannelDataInt(AppApiChannel channel,int attribute,int value)= 0;
	virtual AppApiReturnCode StoreChannelDataString(AppApiChannel channel,int attribute,char * value,int size)= 0;
	virtual AppApiReturnCode ReArrangeChannels(AppApiChannel channel1,AppApiChannel channel2)= 0;
	virtual AppApiReturnCode SwapChannels(AppApiChannel channel1,AppApiChannel channel2)= 0;
	virtual AppApiReturnCode GetBarkerMultiplexesForChannel(AppApiChannel channel,int * NoOfMuxes,AppApiMultiplex * muxes)= 0;
	virtual AppApiReturnCode GetOperator(AppApiOperator * OperatorId)= 0;
	virtual AppApiReturnCode StoreChannelDataNat64(AppApiChannel channel,int dataid,Nat64 value)= 0;
	virtual AppApiReturnCode GetChannelDataNat64(AppApiChannel channel,int dataid,Nat64 * value)= 0;
	virtual AppApiReturnCode GetSatelliteName(int LnbNumber,Nat16 * SatelliteName)= 0;
	virtual AppApiReturnCode GetSatellitePackage(AppApiPackageId * PackageId,AppApiPackageGroup * PackageIGroupId)= 0;
};


#define IAppApiSatProgramDataExImpl(Comp,intf)    \
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
friend class InterfaceParam<Comp,Nat64>;\
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
virtual Bool intf ## _IsAttributeSupported(int attribute);\
virtual AppApiReturnCode intf ## _GetChannelDataInt(AppApiChannel channel,int dataid,int * value);\
virtual AppApiReturnCode intf ## _GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value);\
virtual AppApiReturnCode intf ## _GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size);\
virtual AppApiReturnCode intf ## _GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc_or_Freq);\
virtual AppApiReturnCode intf ## _GetNoOfBarkerMultiplexes(int * NoOfMuxes);\
virtual AppApiReturnCode intf ## _GetBarkerMultiplexByIndex(int index,AppApiMultiplex * muxes);\
virtual AppApiReturnCode intf ## _StoreChannelDataInt(AppApiChannel channel,int attribute,int value);\
virtual AppApiReturnCode intf ## _StoreChannelDataString(AppApiChannel channel,int attribute,char * value,int size);\
virtual AppApiReturnCode intf ## _ReArrangeChannels(AppApiChannel channel1,AppApiChannel channel2);\
virtual AppApiReturnCode intf ## _SwapChannels(AppApiChannel channel1,AppApiChannel channel2);\
virtual AppApiReturnCode intf ## _GetBarkerMultiplexesForChannel(AppApiChannel channel,int * NoOfMuxes,AppApiMultiplex * muxes);\
virtual AppApiReturnCode intf ## _GetOperator(AppApiOperator * OperatorId);\
virtual AppApiReturnCode intf ## _StoreChannelDataNat64(AppApiChannel channel,int dataid,Nat64 value);\
virtual AppApiReturnCode intf ## _GetChannelDataNat64(AppApiChannel channel,int dataid,Nat64 * value);\
virtual AppApiReturnCode intf ## _GetSatelliteName(int LnbNumber,Nat16 * SatelliteName);\
virtual AppApiReturnCode intf ## _GetSatellitePackage(AppApiPackageId * PackageId,AppApiPackageGroup * PackageIGroupId);\
class Comp ## _ ## intf : public IAppApiSatProgramDataEx \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_StringChannelName; \
    InterfaceParam<Comp,int> m_IntFrequency; \
    InterfaceParam<Comp,int> m_IntPtc; \
    InterfaceParam<Comp,int> m_IntNetworkId; \
    InterfaceParam<Comp,int> m_IntOriginalNetworkId; \
    InterfaceParam<Comp,int> m_IntTsid; \
    InterfaceParam<Comp,int> m_IntServiceId; \
    InterfaceParam<Comp,int> m_BoolFreeCiMode; \
    InterfaceParam<Comp,int> m_IntSystemHidden; \
    InterfaceParam<Comp,int> m_IntNumericSelect; \
    InterfaceParam<Comp,int> m_IntNewChannel; \
    InterfaceParam<Comp,int> m_StringSatelliteName; \
    InterfaceParam<Comp,int> m_IntSrcambledStatus; \
    InterfaceParam<Comp,int> m_IntServiceType; \
    InterfaceParam<Comp,int> m_IntUserHidden; \
    InterfaceParam<Comp,int> m_Favorite; \
    InterfaceParam<Comp,int> m_FavoriteNumber; \
    InterfaceParam<Comp,int> m_IntHbbTvOption; \
    InterfaceParam<Comp,Bool> m_BoolChannelLock; \
    InterfaceParam<Comp,int> m_IntLogoURL; \
    InterfaceParam<Comp,Nat64> m_Nat64UniqueNodeId; \
    InterfaceParam<Comp,int> m_IntTpId; \
    InterfaceParam<Comp,int> m_IntLNBId; \
    InterfaceParam<Comp,int> m_Nat32SymbolRate; \
    InterfaceParam<Comp,int> m_IntModulationType; \
    InterfaceParam<Comp,int> m_IntInstalledSatelliteNumber; \
    InterfaceParam<Comp,int> m_IntPolarization; \
    InterfaceParam<Comp,int> m_IntInstalledSatelliteId; \
    InterfaceParam<Comp,int> m_IntDecoderType; \
    InterfaceParam<Comp,int> m_IntDpTsid; \
    InterfaceParam<Comp,int> m_IntDpServiceId; \
    InterfaceParam<Comp,int> m_IntPackageGroup; \
    InterfaceParam<Comp,int> m_StringTxtPages; \
    InterfaceParam<Comp,int> m_Nat32AppsCookie; \
    Comp ## _ ## intf( Comp *parent):m_StringChannelName(parent),m_IntFrequency(parent),m_IntPtc(parent),m_IntNetworkId(parent),m_IntOriginalNetworkId(parent),m_IntTsid(parent),m_IntServiceId(parent),m_BoolFreeCiMode(parent),m_IntSystemHidden(parent),m_IntNumericSelect(parent),m_IntNewChannel(parent),m_StringSatelliteName(parent),m_IntSrcambledStatus(parent),m_IntServiceType(parent),m_IntUserHidden(parent),m_Favorite(parent),m_FavoriteNumber(parent),m_IntHbbTvOption(parent),m_BoolChannelLock(parent),m_IntLogoURL(parent),m_Nat64UniqueNodeId(parent),m_IntTpId(parent),m_IntLNBId(parent),m_Nat32SymbolRate(parent),m_IntModulationType(parent),m_IntInstalledSatelliteNumber(parent),m_IntPolarization(parent),m_IntInstalledSatelliteId(parent),m_IntDecoderType(parent),m_IntDpTsid(parent),m_IntDpServiceId(parent),m_IntPackageGroup(parent),m_StringTxtPages(parent),m_Nat32AppsCookie(parent) \
    {\
        m_parent = parent;\
    }\
virtual int StringChannelName(void){ return m_StringChannelName.Call();}\
virtual int IntFrequency(void){ return m_IntFrequency.Call();}\
virtual int IntPtc(void){ return m_IntPtc.Call();}\
virtual int IntNetworkId(void){ return m_IntNetworkId.Call();}\
virtual int IntOriginalNetworkId(void){ return m_IntOriginalNetworkId.Call();}\
virtual int IntTsid(void){ return m_IntTsid.Call();}\
virtual int IntServiceId(void){ return m_IntServiceId.Call();}\
virtual int BoolFreeCiMode(void){ return m_BoolFreeCiMode.Call();}\
virtual int IntSystemHidden(void){ return m_IntSystemHidden.Call();}\
virtual int IntNumericSelect(void){ return m_IntNumericSelect.Call();}\
virtual int IntNewChannel(void){ return m_IntNewChannel.Call();}\
virtual int StringSatelliteName(void){ return m_StringSatelliteName.Call();}\
virtual int IntSrcambledStatus(void){ return m_IntSrcambledStatus.Call();}\
virtual int IntServiceType(void){ return m_IntServiceType.Call();}\
virtual int IntUserHidden(void){ return m_IntUserHidden.Call();}\
virtual int Favorite(void){ return m_Favorite.Call();}\
virtual int FavoriteNumber(void){ return m_FavoriteNumber.Call();}\
virtual int IntHbbTvOption(void){ return m_IntHbbTvOption.Call();}\
virtual Bool BoolChannelLock(void){ return m_BoolChannelLock.Call();}\
virtual int IntLogoURL(void){ return m_IntLogoURL.Call();}\
virtual Nat64 Nat64UniqueNodeId(void){ return m_Nat64UniqueNodeId.Call();}\
virtual int IntTpId(void){ return m_IntTpId.Call();}\
virtual int IntLNBId(void){ return m_IntLNBId.Call();}\
virtual int Nat32SymbolRate(void){ return m_Nat32SymbolRate.Call();}\
virtual int IntModulationType(void){ return m_IntModulationType.Call();}\
virtual int IntInstalledSatelliteNumber(void){ return m_IntInstalledSatelliteNumber.Call();}\
virtual int IntPolarization(void){ return m_IntPolarization.Call();}\
virtual int IntInstalledSatelliteId(void){ return m_IntInstalledSatelliteId.Call();}\
virtual int IntDecoderType(void){ return m_IntDecoderType.Call();}\
virtual int IntDpTsid(void){ return m_IntDpTsid.Call();}\
virtual int IntDpServiceId(void){ return m_IntDpServiceId.Call();}\
virtual int IntPackageGroup(void){ return m_IntPackageGroup.Call();}\
virtual int StringTxtPages(void){ return m_StringTxtPages.Call();}\
virtual int Nat32AppsCookie(void){ return m_Nat32AppsCookie.Call();}\
virtual Bool IsAttributeSupported(int attribute){ return m_parent->intf ## _IsAttributeSupported(attribute);}\
virtual AppApiReturnCode GetChannelDataInt(AppApiChannel channel,int dataid,int * value){ return m_parent->intf ## _GetChannelDataInt(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataBool(AppApiChannel channel,int dataid,Bool * value){ return m_parent->intf ## _GetChannelDataBool(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataString(AppApiChannel channel,int dataid,Nat16 * value,int size){ return m_parent->intf ## _GetChannelDataString(channel,dataid,value,size);}\
virtual AppApiReturnCode GetDigitalChannel(AppApiChannel * channel,int OnId,int TsId,int Sid,int Ptc_or_Freq){ return m_parent->intf ## _GetDigitalChannel(channel,OnId,TsId,Sid,Ptc_or_Freq);}\
virtual AppApiReturnCode GetNoOfBarkerMultiplexes(int * NoOfMuxes){ return m_parent->intf ## _GetNoOfBarkerMultiplexes(NoOfMuxes);}\
virtual AppApiReturnCode GetBarkerMultiplexByIndex(int index,AppApiMultiplex * muxes){ return m_parent->intf ## _GetBarkerMultiplexByIndex(index,muxes);}\
virtual AppApiReturnCode StoreChannelDataInt(AppApiChannel channel,int attribute,int value){ return m_parent->intf ## _StoreChannelDataInt(channel,attribute,value);}\
virtual AppApiReturnCode StoreChannelDataString(AppApiChannel channel,int attribute,char * value,int size){ return m_parent->intf ## _StoreChannelDataString(channel,attribute,value,size);}\
virtual AppApiReturnCode ReArrangeChannels(AppApiChannel channel1,AppApiChannel channel2){ return m_parent->intf ## _ReArrangeChannels(channel1,channel2);}\
virtual AppApiReturnCode SwapChannels(AppApiChannel channel1,AppApiChannel channel2){ return m_parent->intf ## _SwapChannels(channel1,channel2);}\
virtual AppApiReturnCode GetBarkerMultiplexesForChannel(AppApiChannel channel,int * NoOfMuxes,AppApiMultiplex * muxes){ return m_parent->intf ## _GetBarkerMultiplexesForChannel(channel,NoOfMuxes,muxes);}\
virtual AppApiReturnCode GetOperator(AppApiOperator * OperatorId){ return m_parent->intf ## _GetOperator(OperatorId);}\
virtual AppApiReturnCode StoreChannelDataNat64(AppApiChannel channel,int dataid,Nat64 value){ return m_parent->intf ## _StoreChannelDataNat64(channel,dataid,value);}\
virtual AppApiReturnCode GetChannelDataNat64(AppApiChannel channel,int dataid,Nat64 * value){ return m_parent->intf ## _GetChannelDataNat64(channel,dataid,value);}\
virtual AppApiReturnCode GetSatelliteName(int LnbNumber,Nat16 * SatelliteName){ return m_parent->intf ## _GetSatelliteName(LnbNumber,SatelliteName);}\
virtual AppApiReturnCode GetSatellitePackage(AppApiPackageId * PackageId,AppApiPackageGroup * PackageIGroupId){ return m_parent->intf ## _GetSatellitePackage(PackageId,PackageIGroupId);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
