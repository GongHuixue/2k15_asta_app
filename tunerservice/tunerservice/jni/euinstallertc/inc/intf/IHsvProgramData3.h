#ifndef IHSVPROGRAMDATA3_H
#define IHSVPROGRAMDATA3_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramData3
{
public:
	virtual ~IHsvProgramData3(){}
	#define IHsvProgramData3_BoolLock		((int)0 )
	#define IHsvProgramData3_BoolPreferredFavorite		((int)1 )
	#define IHsvProgramData3_BoolPreferredStereo		((int)2 )
	#define IHsvProgramData3_BoolPreferredNicam		((int)3 )
	#define IHsvProgramData3_BoolSAP		((int)4 )
	#define IHsvProgramData3_BoolSystemHidden		((int)5 )
	#define IHsvProgramData3_BoolNumericSelect		((int)6 )
	#define IHsvProgramData3_BoolNewPreset		((int)7 )
	#define IHsvProgramData3_BoolFreeCiMode		((int)8 )
	#define IHsvProgramData3_BoolTuned		((int)9 )
	#define IHsvProgramData3_BoolDeTuned		((int)10 )
	#define IHsvProgramData3_BoolAttenuator		((int)11 )
	#define IHsvProgramData3_BoolAgcInstalled		((int)12 )
	#define IHsvProgramData3_BoolUpdateName		((int)13 )
	#define IHsvProgramData3_IntDeltaVolume		((int)14 )
	#define IHsvProgramData3_IntFrequency		((int)15 )
	#define IHsvProgramData3_IntPresetNumber		((int)16 )
	#define IHsvProgramData3_IntTvSystem		((int)17 )
	#define IHsvProgramData3_IntModulation		((int)18 )
	#define IHsvProgramData3_IntSignalStrength		((int)19 )
	#define IHsvProgramData3_IntSignalQuality		((int)20 )
	#define IHsvProgramData3_IntColoursystem		((int)21 )
	#define IHsvProgramData3_IntDecoderType		((int)22 )
	#define IHsvProgramData3_IntFineTuneOffset		((int)23 )
	#define IHsvProgramData3_IntFineTuneFrequency		((int)24 )
	#define IHsvProgramData3_IntNetworkId		((int)25 )
	#define IHsvProgramData3_IntOriginalNwId		((int)26 )
	#define IHsvProgramData3_IntTsid		((int)27 )
	#define IHsvProgramData3_IntServiceId		((int)28 )
	#define IHsvProgramData3_IntServiceType		((int)29 )
	#define IHsvProgramData3_IntPmtPid		((int)30 )
	#define IHsvProgramData3_IntPcrPid		((int)31 )
	#define IHsvProgramData3_IntVideoPid		((int)32 )
	#define IHsvProgramData3_IntVideoStreamType		((int)33 )
	#define IHsvProgramData3_IntAudioPid		((int)34 )
	#define IHsvProgramData3_IntAudioStreamType		((int)35 )
	#define IHsvProgramData3_IntSecAudioPid		((int)36 )
	#define IHsvProgramData3_IntSecAudioStreamType		((int)37 )	
	#define IHsvProgramData3_IntCniNi		((int)38 )
	#define IHsvProgramData3_IntModulationType		((int)39 )
	#define IHsvProgramData3_IntLCN		((int)40 )
	#define IHsvProgramData3_IntStreamPriority		((int)41 )
	#define IHsvProgramData3_IntPtc		((int)42 )
	#define IHsvProgramData3_Nat32SymbolRate		((int)43 )
	#define IHsvProgramData3_Nat32DvbType		((int)44 )
	#define IHsvProgramData3_StringChannelName		((int)45 )
	#define IHsvProgramData3_StringExtChannelName		((int)45 )	
	#define IHsvProgramData3_BoolMatchBrandFlag		((int)46 )
	#define IHsvProgramData3_Nat32NumBrandIds		((int)47 )
	#define IHsvProgramData3_StringBrandIds		((int)48 )
	#define IHsvProgramData3_IntChannelBandwidth		((int)49 )
	#define IHsvProgramData3_IntSystemHidden		((int)50 )
	#define IHsvProgramData3_IntNumericSelect		((int)51 )
	#define IHsvProgramData3_IntNewChannel		((int)52 )
	#define IHsvProgramData3_IntSrcambledStatus		((int)53 )
	#define IHsvProgramData3_FavoriteNumber		((int)54 )
	#define IHsvProgramData3_IntHbbTvOption		((int)55 )
	#define IHsvProgramData3_BoolChannelLock		((Bool)56 )
	#define IHsvProgramData3_StringTxtPages		((int)57 )
	#define IHsvProgramData3_IntLogoURL		((int)58 )
	#define IHsvProgramData3_Nat16PrimaryRegion		((int)59 )
	#define IHsvProgramData3_Nat16SecondaryRegion		((int)60 )
	#define IHsvProgramData3_IntTertiaryRegion		((int)61 )
	#define IHsvProgramData3_Nat32CountryCode		((int)62 )
	#define IHsvProgramData3_BoolUserModifiedLogo		((Bool)63 )
	#define IHsvProgramData3_MultipleLCN		((int)64 )
	#define IHsvProgramData3_MultiplePreset		((int)65 )
	
	/* From here below dataIds are not supported currently */
	#define IHsvProgramData3_BoolFavorite		((int)66 )
	#define IHsvProgramData3_BoolFavorite1		((int)67 )
	#define IHsvProgramData3_BoolFavorite2		((int)68)
	#define IHsvProgramData3_BoolFavorite3		((int)69 )
	#define IHsvProgramData3_BoolHMProtectedChannel		((int)70 )
	#define IHsvProgramData3_BoolHMBlanked		((int)71 )
	#define IHsvProgramData3_BoolUserHidden		((int)72 )
	#define IHsvProgramData3_BoolEpgChannel		((int)73 )
	#define IHsvProgramData3_BoolEPGShortInfoEnabled		((int)74 )
	#define IHsvProgramData3_BoolChannelVirgin		((int)75 )
	#define IHsvProgramData3_Nat32DateStamp		((int)76 )
	#define IHsvProgramData3_Nat32AppsCookie		((int)77 )
	#define IHsvProgramData3_Nat32TxtCookie		((int)78 )
	#define IHsvProgramData3_Nat32CesvcCookie		((int)79 )
	#define IHsvProgramData3_IntNewChannelMap		((int)80 )
	#define IHsvProgramData3_IntInstallMode		((int)81 )
	#define IHsvProgramData3_IntDataIndicator		((int)82 )
	#define IHsvProgramData3_IntHMMapChannelNo		((int)83 )
	#define IHsvProgramData3_IntAssociatedDecoder		((int)84 )
	#define IHsvProgramData3_StringSatelliteName		((int)85 )
	#define IHsvProgramData3_IntInstalledSatelliteNumber		((int)86 )
	#define IHsvProgramData3_IntUserHidden		((int)87 )
	#define IHsvProgramData3_FavoriteNumber1		((int)88 )
	#define IHsvProgramData3_FavoriteNumber2		((int)89 )
	#define IHsvProgramData3_FavoriteNumber3		((int)90 )
	#define IHsvProgramData3_IntEPGEnabled		((int)91 )
	#define IHsvProgramData3_Nat64UniqueNodeId		((Nat64)92 )
	
	#define IHsvProgramData3_DecoderNone		((int)0 )
	#define IHsvProgramData3_DecoderExt1		((int)1 )
	#define IHsvProgramData3_DecoderExt2		((int)2 )
	#define IHsvProgramData3_Antenna		((int)0 )
	#define IHsvProgramData3_Cable		((int)1 )	
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
};


#define IHsvProgramData3Impl(Comp,intf)    \
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
class Comp ## _ ## intf : public IHsvProgramData3 \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
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
};\
Comp ## _ ## intf i__ ## intf;


#endif
