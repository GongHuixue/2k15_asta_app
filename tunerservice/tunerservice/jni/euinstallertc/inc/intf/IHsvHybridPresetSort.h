#ifndef IHSVHYBRIDPRESETSORT_H
#define IHSVHYBRIDPRESETSORT_H
#include <intfparam.h>
#include <provreq.h>
class IHsvHybridPresetSort
{
public:
	virtual ~IHsvHybridPresetSort(){}
	virtual void Initialise(void)= 0;
	virtual void AddAnalogPreset(Address adata)= 0;
	virtual Bool AnalogPresetEntry(void)= 0;
	virtual Bool AssignPresetsForCurrentCountry(int CurrentOnwid,Bool CheckLCN)= 0;
	virtual Bool AssignPresetsWithStaticTable(int CurrentOnwid,int Country)= 0;
	virtual Bool AssignPresetsOfOtherCountries(void)= 0;
	virtual void AddDigitalPreset(HsvPgdatDigServiceData * svcdat)= 0;
	virtual Bool AutoStoreManualInstallationValues(void)= 0;
	virtual void RemoveDigitalPresets(void)= 0;
	virtual int GetNumberOfAnalogChannelsFound(void)= 0;
	virtual void UpdateDigitalPreset(HsvPgdatDigServiceData * svcdat)= 0;
	virtual Bool DeleteAllDigitalChannels(void)= 0;
	virtual Bool UpdatingLCNDuringUpdateInstallation(void)= 0;
	virtual Bool DeleteInvalidPTCTable(void)= 0;
	virtual int GetOriginalNetworkId(int CurrentCountry)= 0;
	virtual Bool IsPresetInstalled(Int32 frequency)= 0;
	virtual void AssignPresetsForCountry(int ONID)= 0;
	virtual void SortAll(void)= 0;
	virtual Bool AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid,int * FillHoles)= 0;
	virtual Bool AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid)= 0;
	virtual HsvChannel GetInstalledWeakSignalChannel(void)= 0;
};


#define IHsvHybridPresetSortImpl(Comp,intf)    \
virtual void intf ## _Initialise(void);\
virtual void intf ## _AddAnalogPreset(Address adata);\
virtual Bool intf ## _AnalogPresetEntry(void);\
virtual Bool intf ## _AssignPresetsForCurrentCountry(int CurrentOnwid,Bool CheckLCN);\
virtual Bool intf ## _AssignPresetsWithStaticTable(int CurrentOnwid,int Country);\
virtual Bool intf ## _AssignPresetsOfOtherCountries(void);\
virtual void intf ## _AddDigitalPreset(HsvPgdatDigServiceData * svcdat);\
virtual Bool intf ## _AutoStoreManualInstallationValues(void);\
virtual void intf ## _RemoveDigitalPresets(void);\
virtual int intf ## _GetNumberOfAnalogChannelsFound(void);\
virtual void intf ## _UpdateDigitalPreset(HsvPgdatDigServiceData * svcdat);\
virtual Bool intf ## _DeleteAllDigitalChannels(void);\
virtual Bool intf ## _UpdatingLCNDuringUpdateInstallation(void);\
virtual Bool intf ## _DeleteInvalidPTCTable(void);\
virtual int intf ## _GetOriginalNetworkId(int CurrentCountry);\
virtual Bool intf ## _IsPresetInstalled(Int32 frequency);\
virtual void intf ## _AssignPresetsForCountry(int ONID);\
virtual void intf ## _SortAll(void);\
virtual Bool intf ## _AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid,int * FillHoles);\
virtual Bool intf ## _AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid);\
virtual HsvChannel intf ## _GetInstalledWeakSignalChannel(void);\
class Comp ## _ ## intf : public IHsvHybridPresetSort \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Initialise(void){ return m_parent->intf ## _Initialise();}\
virtual void AddAnalogPreset(Address adata){ return m_parent->intf ## _AddAnalogPreset(adata);}\
virtual Bool AnalogPresetEntry(void){ return m_parent->intf ## _AnalogPresetEntry();}\
virtual Bool AssignPresetsForCurrentCountry(int CurrentOnwid,Bool CheckLCN){ return m_parent->intf ## _AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN);}\
virtual Bool AssignPresetsWithStaticTable(int CurrentOnwid,int Country){ return m_parent->intf ## _AssignPresetsWithStaticTable(CurrentOnwid,Country);}\
virtual Bool AssignPresetsOfOtherCountries(void){ return m_parent->intf ## _AssignPresetsOfOtherCountries();}\
virtual void AddDigitalPreset(HsvPgdatDigServiceData * svcdat){ return m_parent->intf ## _AddDigitalPreset(svcdat);}\
virtual Bool AutoStoreManualInstallationValues(void){ return m_parent->intf ## _AutoStoreManualInstallationValues();}\
virtual void RemoveDigitalPresets(void){ return m_parent->intf ## _RemoveDigitalPresets();}\
virtual int GetNumberOfAnalogChannelsFound(void){ return m_parent->intf ## _GetNumberOfAnalogChannelsFound();}\
virtual void UpdateDigitalPreset(HsvPgdatDigServiceData * svcdat){ return m_parent->intf ## _UpdateDigitalPreset(svcdat);}\
virtual Bool DeleteAllDigitalChannels(void){ return m_parent->intf ## _DeleteAllDigitalChannels();}\
virtual Bool UpdatingLCNDuringUpdateInstallation(void){ return m_parent->intf ## _UpdatingLCNDuringUpdateInstallation();}\
virtual Bool DeleteInvalidPTCTable(void){ return m_parent->intf ## _DeleteInvalidPTCTable();}\
virtual int GetOriginalNetworkId(int CurrentCountry){ return m_parent->intf ## _GetOriginalNetworkId(CurrentCountry);}\
virtual Bool IsPresetInstalled(Int32 frequency){ return m_parent->intf ## _IsPresetInstalled(frequency);}\
virtual void AssignPresetsForCountry(int ONID){ return m_parent->intf ## _AssignPresetsForCountry(ONID);}\
virtual void SortAll(void){ return m_parent->intf ## _SortAll();}\
virtual Bool AssignPresetsForCurrentCountryNonLCNs(int CurrentOnwid,int * FillHoles){ return m_parent->intf ## _AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles);}\
virtual Bool AssignPresetsForCurrentCountryLowPrioLCN(int CurrentOnwid){ return m_parent->intf ## _AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid);}\
virtual HsvChannel GetInstalledWeakSignalChannel(void){ return m_parent->intf ## _GetInstalledWeakSignalChannel();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
