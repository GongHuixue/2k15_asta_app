#ifndef IHSVPROGRAMDATA2EXEXEXEX_H
#define IHSVPROGRAMDATA2EXEXEXEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramData2ExExExEx
{
public:
	virtual ~IHsvProgramData2ExExExEx(){}
	#define IHsvProgramData2ExExExEx_AnalogTelevision		((int)1 )
	#define IHsvProgramData2ExExExEx_DigitalTelevision		((int)2 )
	#define IHsvProgramData2ExExExEx_AudioOnly		((int)3 )
	#define IHsvProgramData2ExExExEx_DataBroadcastService		((int)4 )
	#define IHsvProgramData2ExExExEx_NVODReferenceService		((int)5 )
	#define IHsvProgramData2ExExExEx_NVODTimeshiftedService		((int)6 )
	#define IHsvProgramData2ExExExEx_MosaicService		((int)7 )
	#define IHsvProgramData2ExExExEx_TeletextService		((int)8 )
	#define IHsvProgramData2ExExExEx_DVBMHPservice		((int)9 )
	#define IHsvProgramData2ExExExEx_MPEG2HDService		((int)10 )
	#define IHsvProgramData2ExExExEx_AdvCodecSDTelevisionService		((int)11 )
	#define IHsvProgramData2ExExExEx_AdvCodecSDNVODTimeShiftedService		((int)12 )
	#define IHsvProgramData2ExExExEx_AdvCodecSDNVODReferenceService		((int)13 )
	#define IHsvProgramData2ExExExEx_AdvCodecHDTelevisionService		((int)14 )
	#define IHsvProgramData2ExExExEx_AdvCodecHDNVODTimeShiftedService		((int)15 )
	#define IHsvProgramData2ExExExEx_AdvCodecHDNVODReferenceService		((int)16 )
	#define IHsvProgramData2ExExExEx_AntennaTable		((int)0 )
	#define IHsvProgramData2ExExExEx_CableTable		((int)1 )
	#define IHsvProgramData2ExExExEx_OobTable		((int)2 )
	#define IHsvProgramData2ExExExEx_ExtensionTable		((int)3 )
	#define IHsvProgramData2ExExExEx_pgBoolTuned		((int)0 )
	#define IHsvProgramData2ExExExEx_pgBoolDetuned		((int)1 )
	#define IHsvProgramData2ExExExEx_pgBoolAttenuator		((int)2 )
	#define IHsvProgramData2ExExExEx_pgBoolAGCInstalled		((int)3 )
	#define IHsvProgramData2ExExExEx_pgBoolChannelVirgin		((int)4 )
	#define IHsvProgramData2ExExExEx_pgIntDecoder		((int)5 )
	#define IHsvProgramData2ExExExEx_pgIntInstallmode		((int)6 )
	#define IHsvProgramData2ExExExEx_pgIntFineTuneOffset		((int)7 )
	#define IHsvProgramData2ExExExEx_pgIntColoursystem		((int)8 )
	#define IHsvProgramData2ExExExEx_pgIntFinetunefrequency		((int)9 )
	#define IHsvProgramData2ExExExEx_pgIntFrequency		((int)10 )
	#define IHsvProgramData2ExExExEx_pgIntTvSystem		((int)11 )
	#define IHsvProgramData2ExExExEx_pgIntSignalStrength		((int)12 )
	#define IHsvProgramData2ExExExEx_pgStringName		((int)13 )
	#define IHsvProgramData2ExExExEx_pgNat32CesvcCookie		((int)14 )
	#define IHsvProgramData2ExExExEx_pgNat32TxtCookie		((int)15 )
	#define IHsvProgramData2ExExExEx_pgNat32AppsCookie		((int)16 )
	#define IHsvProgramData2ExExExEx_pgNat16OriginalNwId		((int)17 )
	#define IHsvProgramData2ExExExEx_pgNat16Tsid		((int)18 )
	#define IHsvProgramData2ExExExEx_pgIntModulationType		((int)19 )
	#define IHsvProgramData2ExExExEx_pgNat16ServiceId		((int)20 )
	#define IHsvProgramData2ExExExEx_pgNat8ServiceType		((int)21 )
	#define IHsvProgramData2ExExExEx_pgNat16AudioPid		((int)22 )
	#define IHsvProgramData2ExExExEx_pgNat16VideoPid		((int)23 )
	#define IHsvProgramData2ExExExEx_pgNat16PcrPid		((int)24 )
	#define IHsvProgramData2ExExExEx_pgBoolUserHidden		((int)25 )
	#define IHsvProgramData2ExExExEx_pgBoolSystemHidden		((int)26 )
	#define IHsvProgramData2ExExExEx_pgBoolNewPreset		((int)27 )
	#define IHsvProgramData2ExExExEx_pgNat16Lcn		((int)28 )
	#define IHsvProgramData2ExExExEx_pgNat8CodeRate		((int)29 )
	#define IHsvProgramData2ExExExEx_pgNat8HierarchyMode		((int)30 )
	#define IHsvProgramData2ExExExEx_pgNat8GuardInterval		((int)31 )
	#define IHsvProgramData2ExExExEx_pgNat8TxMode		((int)32 )
	#define IHsvProgramData2ExExExEx_pgNat8ChannelBandwidth		((int)33 )
	#define IHsvProgramData2ExExExEx_pgNat8StreamPriority		((int)34 )
	#define IHsvProgramData2ExExExEx_pgNat8TimeError		((int)35 )
	#define IHsvProgramData2ExExExEx_pgNat8FrequencyError		((int)36 )
	#define IHsvProgramData2ExExExEx_pgNat8FrequencyOffset		((int)37 )
	#define IHsvProgramData2ExExExEx_pgNat8PtcListVersion		((int)38 )
	#define IHsvProgramData2ExExExEx_pgInt8TSVersion		((int)39 )
	#define IHsvProgramData2ExExExEx_pgNat16NetworkId		((int)40 )
	#define IHsvProgramData2ExExExEx_pgNat8IqMode		((int)41 )
	#define IHsvProgramData2ExExExEx_pgNat8ChannelInformation		((int)42 )
	#define IHsvProgramData2ExExExEx_pgBoolEPGEnabled		((int)43 )
	#define IHsvProgramData2ExExExEx_pgNat16CniNi		((int)44 )
	#define IHsvProgramData2ExExExEx_pgNat8DataIndicator		((int)45 )
	#define IHsvProgramData2ExExExEx_pgIntProgramNumber		((int)46 )
	#define IHsvProgramData2ExExExEx_pgBoolUpdateName		((int)47 )
	#define IHsvProgramData2ExExExEx_pgNat8ScramblingStatus		((int)48 )
	#define IHsvProgramData2ExExExEx_pgNat8StreamType		((int)49 )
	#define IHsvProgramData2ExExExEx_pgBoolVideoDescPresent		((Bool)50 )
	#define IHsvProgramData2ExExExEx_pgNat8DecoderType		((int)51 )
	#define IHsvProgramData2ExExExEx_pgNat32SymbolRate		((int)52 )
	#define IHsvProgramData2ExExExEx_pgBoolUserMoved		((Bool)53 )
	#define IHsvProgramData2ExExExEx_pgBoolUserMovedConsequent		((Bool)54 )
	#define IHsvProgramData2ExExExEx_pgBoolNumericSelect		((Bool)55 )
	#define IHsvProgramData2ExExExEx_pgBoolFreeCiMode		((Bool)59 )
	#define IHsvProgramData2ExExExEx_pgIntDateStamp		((int)60 )
	#define IHsvProgramData2ExExExEx_pgDecNone		((int)0 )
	#define IHsvProgramData2ExExExEx_pgDecExt1		((int)1 )
	#define IHsvProgramData2ExExExEx_pgDecExt2		((int)2 )
	#define IHsvProgramData2ExExExEx_pgInsModeFreq		((int)0 )
	#define IHsvProgramData2ExExExEx_pgInsModeChan		((int)1 )
	#define IHsvProgramData2ExExExEx_InvalidValue		((int)-1 )
	virtual Bool SelectTable(int tableid)= 0;
	virtual int GetCurrentTable(void)= 0;
	virtual Bool ClearTable(int tableid)= 0;
	virtual Bool IsValidChannel(int tableid,HsvChannel * channelno)= 0;
	virtual Bool IsChannelInstalled(int tableid,HsvChannel * channelno)= 0;
	virtual Bool IsAttributeSupported(int attribute)= 0;
	virtual Bool SetChannelDataBool(int tableid,HsvChannel channel,int attribute,Bool value)= 0;
	virtual Bool SetChannelDataInt(int tableid,HsvChannel channel,int attribute,int value)= 0;
	virtual Bool SetChannelDataNat32(int tableid,HsvChannel channel,int attribute,Nat32 value)= 0;
	virtual Bool SetChannelDataString(int tableid,HsvChannel channel,int attribute,Nat16 * value)= 0;
	virtual Bool GetChannelDataBool(int tableid,HsvChannel channel,int attribute,Bool * value)= 0;
	virtual Bool GetChannelDataInt(int tableid,HsvChannel channel,int attribute,int * value)= 0;
	virtual Bool GetChannelDataNat32(int tableid,HsvChannel channel,int attribute,Nat32 * value)= 0;
	virtual Bool GetChannelDataString(int tableid,HsvChannel channel,int attribute,Nat16 * value,int size)= 0;
	virtual Bool SwapChannels(int tableid,HsvChannel channel1,HsvChannel channel2)= 0;
	virtual Bool ReorderChannels(int tableId,HsvChannel channel1,HsvChannel channel2)= 0;
	virtual Bool GetDigitalPresetById(Nat16 OriginalNwId,Nat16 ServiceId,HsvChannel * channel)= 0;
	virtual Bool GetDigitalPresetById2(Nat16 OriginalNwId,Nat16 ServiceId,Nat16 TsId,HsvChannel * channel)= 0;
	virtual Bool MoveChannel(int tableid,HsvChannel channel1,HsvChannel channel2)= 0;
	virtual Bool CopyChannel(int tableid,HsvChannel channel1,HsvChannel channel2)= 0;
	virtual Bool DeleteChannel(int tableid,HsvChannel channel)= 0;
	virtual Bool IsModulationTypeSupported(HsvModulationType modulationtype)= 0;
	virtual Bool StoreProgramData(int tableid,HsvChannelData * channeldata)= 0;
	virtual Bool GetProgramData(int tableid,HsvChannelData * channeldata)= 0;
};


#define IHsvProgramData2ExExExExImpl(Comp,intf)    \
virtual Bool intf ## _SelectTable(int tableid);\
virtual int intf ## _GetCurrentTable(void);\
virtual Bool intf ## _ClearTable(int tableid);\
virtual Bool intf ## _IsValidChannel(int tableid,HsvChannel * channelno);\
virtual Bool intf ## _IsChannelInstalled(int tableid,HsvChannel * channelno);\
virtual Bool intf ## _IsAttributeSupported(int attribute);\
virtual Bool intf ## _SetChannelDataBool(int tableid,HsvChannel channel,int attribute,Bool value);\
virtual Bool intf ## _SetChannelDataInt(int tableid,HsvChannel channel,int attribute,int value);\
virtual Bool intf ## _SetChannelDataNat32(int tableid,HsvChannel channel,int attribute,Nat32 value);\
virtual Bool intf ## _SetChannelDataString(int tableid,HsvChannel channel,int attribute,Nat16 * value);\
virtual Bool intf ## _GetChannelDataBool(int tableid,HsvChannel channel,int attribute,Bool * value);\
virtual Bool intf ## _GetChannelDataInt(int tableid,HsvChannel channel,int attribute,int * value);\
virtual Bool intf ## _GetChannelDataNat32(int tableid,HsvChannel channel,int attribute,Nat32 * value);\
virtual Bool intf ## _GetChannelDataString(int tableid,HsvChannel channel,int attribute,Nat16 * value,int size);\
virtual Bool intf ## _SwapChannels(int tableid,HsvChannel channel1,HsvChannel channel2);\
virtual Bool intf ## _ReorderChannels(int tableId,HsvChannel channel1,HsvChannel channel2);\
virtual Bool intf ## _GetDigitalPresetById(Nat16 OriginalNwId,Nat16 ServiceId,HsvChannel * channel);\
virtual Bool intf ## _GetDigitalPresetById2(Nat16 OriginalNwId,Nat16 ServiceId,Nat16 TsId,HsvChannel * channel);\
virtual Bool intf ## _MoveChannel(int tableid,HsvChannel channel1,HsvChannel channel2);\
virtual Bool intf ## _CopyChannel(int tableid,HsvChannel channel1,HsvChannel channel2);\
virtual Bool intf ## _DeleteChannel(int tableid,HsvChannel channel);\
virtual Bool intf ## _IsModulationTypeSupported(HsvModulationType modulationtype);\
virtual Bool intf ## _StoreProgramData(int tableid,HsvChannelData * channeldata);\
virtual Bool intf ## _GetProgramData(int tableid,HsvChannelData * channeldata);\
class Comp ## _ ## intf : public IHsvProgramData2ExExExEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool SelectTable(int tableid){ return m_parent->intf ## _SelectTable(tableid);}\
virtual int GetCurrentTable(void){ return m_parent->intf ## _GetCurrentTable();}\
virtual Bool ClearTable(int tableid){ return m_parent->intf ## _ClearTable(tableid);}\
virtual Bool IsValidChannel(int tableid,HsvChannel * channelno){ return m_parent->intf ## _IsValidChannel(tableid,channelno);}\
virtual Bool IsChannelInstalled(int tableid,HsvChannel * channelno){ return m_parent->intf ## _IsChannelInstalled(tableid,channelno);}\
virtual Bool IsAttributeSupported(int attribute){ return m_parent->intf ## _IsAttributeSupported(attribute);}\
virtual Bool SetChannelDataBool(int tableid,HsvChannel channel,int attribute,Bool value){ return m_parent->intf ## _SetChannelDataBool(tableid,channel,attribute,value);}\
virtual Bool SetChannelDataInt(int tableid,HsvChannel channel,int attribute,int value){ return m_parent->intf ## _SetChannelDataInt(tableid,channel,attribute,value);}\
virtual Bool SetChannelDataNat32(int tableid,HsvChannel channel,int attribute,Nat32 value){ return m_parent->intf ## _SetChannelDataNat32(tableid,channel,attribute,value);}\
virtual Bool SetChannelDataString(int tableid,HsvChannel channel,int attribute,Nat16 * value){ return m_parent->intf ## _SetChannelDataString(tableid,channel,attribute,value);}\
virtual Bool GetChannelDataBool(int tableid,HsvChannel channel,int attribute,Bool * value){ return m_parent->intf ## _GetChannelDataBool(tableid,channel,attribute,value);}\
virtual Bool GetChannelDataInt(int tableid,HsvChannel channel,int attribute,int * value){ return m_parent->intf ## _GetChannelDataInt(tableid,channel,attribute,value);}\
virtual Bool GetChannelDataNat32(int tableid,HsvChannel channel,int attribute,Nat32 * value){ return m_parent->intf ## _GetChannelDataNat32(tableid,channel,attribute,value);}\
virtual Bool GetChannelDataString(int tableid,HsvChannel channel,int attribute,Nat16 * value,int size){ return m_parent->intf ## _GetChannelDataString(tableid,channel,attribute,value,size);}\
virtual Bool SwapChannels(int tableid,HsvChannel channel1,HsvChannel channel2){ return m_parent->intf ## _SwapChannels(tableid,channel1,channel2);}\
virtual Bool ReorderChannels(int tableId,HsvChannel channel1,HsvChannel channel2){ return m_parent->intf ## _ReorderChannels(tableId,channel1,channel2);}\
virtual Bool GetDigitalPresetById(Nat16 OriginalNwId,Nat16 ServiceId,HsvChannel * channel){ return m_parent->intf ## _GetDigitalPresetById(OriginalNwId,ServiceId,channel);}\
virtual Bool GetDigitalPresetById2(Nat16 OriginalNwId,Nat16 ServiceId,Nat16 TsId,HsvChannel * channel){ return m_parent->intf ## _GetDigitalPresetById2(OriginalNwId,ServiceId,TsId,channel);}\
virtual Bool MoveChannel(int tableid,HsvChannel channel1,HsvChannel channel2){ return m_parent->intf ## _MoveChannel(tableid,channel1,channel2);}\
virtual Bool CopyChannel(int tableid,HsvChannel channel1,HsvChannel channel2){ return m_parent->intf ## _CopyChannel(tableid,channel1,channel2);}\
virtual Bool DeleteChannel(int tableid,HsvChannel channel){ return m_parent->intf ## _DeleteChannel(tableid,channel);}\
virtual Bool IsModulationTypeSupported(HsvModulationType modulationtype){ return m_parent->intf ## _IsModulationTypeSupported(modulationtype);}\
virtual Bool StoreProgramData(int tableid,HsvChannelData * channeldata){ return m_parent->intf ## _StoreProgramData(tableid,channeldata);}\
virtual Bool GetProgramData(int tableid,HsvChannelData * channeldata){ return m_parent->intf ## _GetProgramData(tableid,channeldata);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
