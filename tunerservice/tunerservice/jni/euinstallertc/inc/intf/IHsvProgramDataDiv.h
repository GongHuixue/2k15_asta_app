#ifndef IHSVPROGRAMDATADIV_H
#define IHSVPROGRAMDATADIV_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDataDiv
{
public:
	virtual ~IHsvProgramDataDiv(){}
	virtual int DefaultSystemLanguage(void)= 0;
	virtual Bool OobSupported(void)= 0;
	virtual int NoOfMinorChannelsToStoreAntenna(void)= 0;
	virtual int NoOfMinorChannelsToStoreCable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntenna(void)= 0;
	virtual int MaxNoOfChannelsToStoreCable(void)= 0;
	virtual int MaxNoOfPrograms(void)= 0;
	virtual int PersistentMemoryFileVersion(void)= 0;
	virtual int DefaultTunerPresetFrequency(void)= 0;
	virtual String HsvAntennaMajorTable(void)= 0;
	virtual String HsvAntennaPtcTable(void)= 0;
	virtual String HsvCableMajorTable(void)= 0;
	virtual String HsvCablePtcTable(void)= 0;
	virtual String HsvOobMajorTable(void)= 0;
	virtual String HsvOobPtcTable(void)= 0;
	virtual int PersistentMemUpdateTimeout(void)= 0;
	virtual Nat32 CookieDefaultValue(void)= 0;
	virtual Nat32 EpgCookieDefaultValue(void)= 0;
	virtual Nat32 TxtCookieDefaultValue(void)= 0;
	virtual Nat32 AppsCookieDefaultValue(void)= 0;
	virtual Bool ProgramViewForUS(void)= 0;
	virtual int ChannelNameLength(void)= 0;
	virtual String HsvAntennaAnalogTable(void)= 0;
	virtual String HsvAntennaDigSrvcTable(void)= 0;
	virtual String HsvAntennaDigPtcTable(void)= 0;
	virtual String HsvAntennaFreqMapTable(void)= 0;
	virtual String HsvCableAnalogTable(void)= 0;
	virtual String HsvCableDigSrvcTable(void)= 0;
	virtual String HsvCableDigPtcTable(void)= 0;
	virtual String HsvCableFreqMapTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaUserTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaDigSrvcTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaDigTSTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaDigPtcTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreAntennaAnalogTable(void)= 0;
	virtual int MaxNoOfMultiplexsToStoreAntennaFreqMapTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableUserTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableDigSrvcTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableDigTSTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableDigPtcTable(void)= 0;
	virtual int MaxNoOfChannelsToStoreCableAnalogTable(void)= 0;
	virtual int MaxNoOfMultiplexsToStoreCableFreqMapTable(void)= 0;
	virtual Bool AnalogOnly(void)= 0;
	virtual Bool InstallDuplicateTsids(int medium)= 0;
	virtual int PrimaryFileVersion(void)= 0;
	virtual int SecondaryFileVersion(void)= 0;
	virtual int ChannelListVariant(void)= 0;
	#define IHsvProgramDataDiv_DefaultChannelList		((int)0 )
	#define IHsvProgramDataDiv_DualChannelList		((int)1 )
	#define IHsvProgramDataDiv_TripleChannelList		((int)2 )
	virtual int ChannelNameSource(void)= 0;
	virtual Bool TripletKey(int medium)= 0;
	#define IHsvProgramDataDiv_ExtendedName		((int)1 )
	#define IHsvProgramDataDiv_ShortName		((int)2 )
	#define IHsvProgramDataDiv_Default		((int)3 )
	virtual Bool UpdateChannelName(int medium)= 0;
};


#define IHsvProgramDataDivImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
friend class InterfaceParam<Comp,String>;\
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
virtual Bool intf ## _InstallDuplicateTsids(int medium);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _TripletKey(int medium);\
virtual Bool intf ## _UpdateChannelName(int medium);\
class Comp ## _ ## intf : public IHsvProgramDataDiv \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_DefaultSystemLanguage; \
    InterfaceParam<Comp,Bool> m_OobSupported; \
    InterfaceParam<Comp,int> m_NoOfMinorChannelsToStoreAntenna; \
    InterfaceParam<Comp,int> m_NoOfMinorChannelsToStoreCable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntenna; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCable; \
    InterfaceParam<Comp,int> m_MaxNoOfPrograms; \
    InterfaceParam<Comp,int> m_PersistentMemoryFileVersion; \
    InterfaceParam<Comp,int> m_DefaultTunerPresetFrequency; \
    InterfaceParam<Comp,String> m_HsvAntennaMajorTable; \
    InterfaceParam<Comp,String> m_HsvAntennaPtcTable; \
    InterfaceParam<Comp,String> m_HsvCableMajorTable; \
    InterfaceParam<Comp,String> m_HsvCablePtcTable; \
    InterfaceParam<Comp,String> m_HsvOobMajorTable; \
    InterfaceParam<Comp,String> m_HsvOobPtcTable; \
    InterfaceParam<Comp,int> m_PersistentMemUpdateTimeout; \
    InterfaceParam<Comp,Nat32> m_CookieDefaultValue; \
    InterfaceParam<Comp,Nat32> m_EpgCookieDefaultValue; \
    InterfaceParam<Comp,Nat32> m_TxtCookieDefaultValue; \
    InterfaceParam<Comp,Nat32> m_AppsCookieDefaultValue; \
    InterfaceParam<Comp,Bool> m_ProgramViewForUS; \
    InterfaceParam<Comp,int> m_ChannelNameLength; \
    InterfaceParam<Comp,String> m_HsvAntennaAnalogTable; \
    InterfaceParam<Comp,String> m_HsvAntennaDigSrvcTable; \
    InterfaceParam<Comp,String> m_HsvAntennaDigPtcTable; \
    InterfaceParam<Comp,String> m_HsvAntennaFreqMapTable; \
    InterfaceParam<Comp,String> m_HsvCableAnalogTable; \
    InterfaceParam<Comp,String> m_HsvCableDigSrvcTable; \
    InterfaceParam<Comp,String> m_HsvCableDigPtcTable; \
    InterfaceParam<Comp,String> m_HsvCableFreqMapTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaUserTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaDigSrvcTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaDigTSTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaDigPtcTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreAntennaAnalogTable; \
    InterfaceParam<Comp,int> m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableUserTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableDigSrvcTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableDigTSTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableDigPtcTable; \
    InterfaceParam<Comp,int> m_MaxNoOfChannelsToStoreCableAnalogTable; \
    InterfaceParam<Comp,int> m_MaxNoOfMultiplexsToStoreCableFreqMapTable; \
    InterfaceParam<Comp,Bool> m_AnalogOnly; \
    InterfaceParam<Comp,int> m_PrimaryFileVersion; \
    InterfaceParam<Comp,int> m_SecondaryFileVersion; \
    InterfaceParam<Comp,int> m_ChannelListVariant; \
    InterfaceParam<Comp,int> m_ChannelNameSource; \
    Comp ## _ ## intf( Comp *parent):m_DefaultSystemLanguage(parent),m_OobSupported(parent),m_NoOfMinorChannelsToStoreAntenna(parent),m_NoOfMinorChannelsToStoreCable(parent),m_MaxNoOfChannelsToStoreAntenna(parent),m_MaxNoOfChannelsToStoreCable(parent),m_MaxNoOfPrograms(parent),m_PersistentMemoryFileVersion(parent),m_DefaultTunerPresetFrequency(parent),m_HsvAntennaMajorTable(parent),m_HsvAntennaPtcTable(parent),m_HsvCableMajorTable(parent),m_HsvCablePtcTable(parent),m_HsvOobMajorTable(parent),m_HsvOobPtcTable(parent),m_PersistentMemUpdateTimeout(parent),m_CookieDefaultValue(parent),m_EpgCookieDefaultValue(parent),m_TxtCookieDefaultValue(parent),m_AppsCookieDefaultValue(parent),m_ProgramViewForUS(parent),m_ChannelNameLength(parent),m_HsvAntennaAnalogTable(parent),m_HsvAntennaDigSrvcTable(parent),m_HsvAntennaDigPtcTable(parent),m_HsvAntennaFreqMapTable(parent),m_HsvCableAnalogTable(parent),m_HsvCableDigSrvcTable(parent),m_HsvCableDigPtcTable(parent),m_HsvCableFreqMapTable(parent),m_MaxNoOfChannelsToStoreAntennaUserTable(parent),m_MaxNoOfChannelsToStoreAntennaDigSrvcTable(parent),m_MaxNoOfChannelsToStoreAntennaDigTSTable(parent),m_MaxNoOfChannelsToStoreAntennaDigPtcTable(parent),m_MaxNoOfChannelsToStoreAntennaAnalogTable(parent),m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable(parent),m_MaxNoOfChannelsToStoreCableUserTable(parent),m_MaxNoOfChannelsToStoreCableDigSrvcTable(parent),m_MaxNoOfChannelsToStoreCableDigTSTable(parent),m_MaxNoOfChannelsToStoreCableDigPtcTable(parent),m_MaxNoOfChannelsToStoreCableAnalogTable(parent),m_MaxNoOfMultiplexsToStoreCableFreqMapTable(parent),m_AnalogOnly(parent),m_PrimaryFileVersion(parent),m_SecondaryFileVersion(parent),m_ChannelListVariant(parent),m_ChannelNameSource(parent) \
    {\
        m_parent = parent;\
    }\
virtual int DefaultSystemLanguage(void){ return m_DefaultSystemLanguage.Call();}\
virtual Bool OobSupported(void){ return m_OobSupported.Call();}\
virtual int NoOfMinorChannelsToStoreAntenna(void){ return m_NoOfMinorChannelsToStoreAntenna.Call();}\
virtual int NoOfMinorChannelsToStoreCable(void){ return m_NoOfMinorChannelsToStoreCable.Call();}\
virtual int MaxNoOfChannelsToStoreAntenna(void){ return m_MaxNoOfChannelsToStoreAntenna.Call();}\
virtual int MaxNoOfChannelsToStoreCable(void){ return m_MaxNoOfChannelsToStoreCable.Call();}\
virtual int MaxNoOfPrograms(void){ return m_MaxNoOfPrograms.Call();}\
virtual int PersistentMemoryFileVersion(void){ return m_PersistentMemoryFileVersion.Call();}\
virtual int DefaultTunerPresetFrequency(void){ return m_DefaultTunerPresetFrequency.Call();}\
virtual String HsvAntennaMajorTable(void){ return m_HsvAntennaMajorTable.Call();}\
virtual String HsvAntennaPtcTable(void){ return m_HsvAntennaPtcTable.Call();}\
virtual String HsvCableMajorTable(void){ return m_HsvCableMajorTable.Call();}\
virtual String HsvCablePtcTable(void){ return m_HsvCablePtcTable.Call();}\
virtual String HsvOobMajorTable(void){ return m_HsvOobMajorTable.Call();}\
virtual String HsvOobPtcTable(void){ return m_HsvOobPtcTable.Call();}\
virtual int PersistentMemUpdateTimeout(void){ return m_PersistentMemUpdateTimeout.Call();}\
virtual Nat32 CookieDefaultValue(void){ return m_CookieDefaultValue.Call();}\
virtual Nat32 EpgCookieDefaultValue(void){ return m_EpgCookieDefaultValue.Call();}\
virtual Nat32 TxtCookieDefaultValue(void){ return m_TxtCookieDefaultValue.Call();}\
virtual Nat32 AppsCookieDefaultValue(void){ return m_AppsCookieDefaultValue.Call();}\
virtual Bool ProgramViewForUS(void){ return m_ProgramViewForUS.Call();}\
virtual int ChannelNameLength(void){ return m_ChannelNameLength.Call();}\
virtual String HsvAntennaAnalogTable(void){ return m_HsvAntennaAnalogTable.Call();}\
virtual String HsvAntennaDigSrvcTable(void){ return m_HsvAntennaDigSrvcTable.Call();}\
virtual String HsvAntennaDigPtcTable(void){ return m_HsvAntennaDigPtcTable.Call();}\
virtual String HsvAntennaFreqMapTable(void){ return m_HsvAntennaFreqMapTable.Call();}\
virtual String HsvCableAnalogTable(void){ return m_HsvCableAnalogTable.Call();}\
virtual String HsvCableDigSrvcTable(void){ return m_HsvCableDigSrvcTable.Call();}\
virtual String HsvCableDigPtcTable(void){ return m_HsvCableDigPtcTable.Call();}\
virtual String HsvCableFreqMapTable(void){ return m_HsvCableFreqMapTable.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaUserTable(void){ return m_MaxNoOfChannelsToStoreAntennaUserTable.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaDigSrvcTable(void){ return m_MaxNoOfChannelsToStoreAntennaDigSrvcTable.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaDigTSTable(void){ return m_MaxNoOfChannelsToStoreAntennaDigTSTable.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaDigPtcTable(void){ return m_MaxNoOfChannelsToStoreAntennaDigPtcTable.Call();}\
virtual int MaxNoOfChannelsToStoreAntennaAnalogTable(void){ return m_MaxNoOfChannelsToStoreAntennaAnalogTable.Call();}\
virtual int MaxNoOfMultiplexsToStoreAntennaFreqMapTable(void){ return m_MaxNoOfMultiplexsToStoreAntennaFreqMapTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableUserTable(void){ return m_MaxNoOfChannelsToStoreCableUserTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableDigSrvcTable(void){ return m_MaxNoOfChannelsToStoreCableDigSrvcTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableDigTSTable(void){ return m_MaxNoOfChannelsToStoreCableDigTSTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableDigPtcTable(void){ return m_MaxNoOfChannelsToStoreCableDigPtcTable.Call();}\
virtual int MaxNoOfChannelsToStoreCableAnalogTable(void){ return m_MaxNoOfChannelsToStoreCableAnalogTable.Call();}\
virtual int MaxNoOfMultiplexsToStoreCableFreqMapTable(void){ return m_MaxNoOfMultiplexsToStoreCableFreqMapTable.Call();}\
virtual Bool AnalogOnly(void){ return m_AnalogOnly.Call();}\
virtual Bool InstallDuplicateTsids(int medium){ return m_parent->intf ## _InstallDuplicateTsids(medium);}\
virtual int PrimaryFileVersion(void){ return m_PrimaryFileVersion.Call();}\
virtual int SecondaryFileVersion(void){ return m_SecondaryFileVersion.Call();}\
virtual int ChannelListVariant(void){ return m_ChannelListVariant.Call();}\
virtual int ChannelNameSource(void){ return m_ChannelNameSource.Call();}\
virtual Bool TripletKey(int medium){ return m_parent->intf ## _TripletKey(medium);}\
virtual Bool UpdateChannelName(int medium){ return m_parent->intf ## _UpdateChannelName(medium);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
