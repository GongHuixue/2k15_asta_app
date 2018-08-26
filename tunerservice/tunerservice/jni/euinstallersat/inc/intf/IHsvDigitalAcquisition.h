#ifndef IHSVDIGITALACQUISITION_H
#define IHSVDIGITALACQUISITION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalAcquisition
{
public:
	virtual ~IHsvDigitalAcquisition(){}
	#define IHsvDigitalAcquisition_Homing		((int)0 )
	#define IHsvDigitalAcquisition_Fallback		((int)1 )
	#define IHsvDigitalAcquisition_Normal		((int)0 )
	#define IHsvDigitalAcquisition_Background		((int)1 )
	#define IHsvDigitalAcquisition_AcquireSDSDs		((int)2 )
	virtual void Initialise(int LnbNumber)= 0;
	virtual void AcquireData(int Mode)= 0;
	virtual void AcquireDataOnTimeout(void)= 0;
	virtual int GetNumberOfDigitalChannelsFound(void)= 0;
	virtual int GetNumberOfDigitalChannelsRemoved(void)= 0;
	virtual int GetNumberOfTvChannelsFound(void)= 0;
	virtual int GetNumberOfRadioChannelsFound(void)= 0;
	virtual int GetNumberOfTvChannelsRemoved(void)= 0;
	virtual int GetNumberofRadioChannelsRemoved(void)= 0;
	virtual int StoreBarkerMuxDetails(void)= 0;
	virtual void SyncTemporaryTableRecords(void)= 0;
	virtual int GetNumberOfSdsds(void)= 0;
	virtual Bool GetSdsdByIndex(int count,HsvNITSatelliteDS * SdSdEntry)= 0;
	virtual int GetNumberOfTvChannelsInLnb(int Lnb)= 0;
	virtual int GetNumberOfRadioChannelsInLnb(int Lnb)= 0;
	virtual void AssignLCN(HsvPgdatDigServiceData *psvcdat) = 0;
	virtual void GetTricolorRegionNames (Nat16 **names, int *len) = 0;
};


#define IHsvDigitalAcquisitionImpl(Comp,intf)    \
virtual void intf ## _Initialise(int LnbNumber);\
virtual void intf ## _AcquireData(int Mode);\
virtual void intf ## _AcquireDataOnTimeout(void);\
virtual int intf ## _GetNumberOfDigitalChannelsFound(void);\
virtual int intf ## _GetNumberOfDigitalChannelsRemoved(void);\
virtual int intf ## _GetNumberOfTvChannelsFound(void);\
virtual int intf ## _GetNumberOfRadioChannelsFound(void);\
virtual int intf ## _GetNumberOfTvChannelsRemoved(void);\
virtual int intf ## _GetNumberofRadioChannelsRemoved(void);\
virtual int intf ## _StoreBarkerMuxDetails(void);\
virtual void intf ## _SyncTemporaryTableRecords(void);\
virtual int intf ## _GetNumberOfSdsds(void);\
virtual Bool intf ## _GetSdsdByIndex(int count,HsvNITSatelliteDS * SdSdEntry);\
virtual int intf ## _GetNumberOfTvChannelsInLnb(int Lnb);\
virtual int intf ## _GetNumberOfRadioChannelsInLnb(int Lnb);\
virtual void intf ## _AssignLCN(HsvPgdatDigServiceData *psvcdat);\
virtual void intf ## _GetTricolorRegionNames(Nat16 ** names, int *len);\
class Comp ## _ ## intf : public IHsvDigitalAcquisition \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Initialise(int LnbNumber){ return m_parent->intf ## _Initialise(LnbNumber);}\
virtual void AcquireData(int Mode){ return m_parent->intf ## _AcquireData(Mode);}\
virtual void AcquireDataOnTimeout(void){ return m_parent->intf ## _AcquireDataOnTimeout();}\
virtual int GetNumberOfDigitalChannelsFound(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsFound();}\
virtual int GetNumberOfDigitalChannelsRemoved(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsRemoved();}\
virtual int GetNumberOfTvChannelsFound(void){ return m_parent->intf ## _GetNumberOfTvChannelsFound();}\
virtual int GetNumberOfRadioChannelsFound(void){ return m_parent->intf ## _GetNumberOfRadioChannelsFound();}\
virtual int GetNumberOfTvChannelsRemoved(void){ return m_parent->intf ## _GetNumberOfTvChannelsRemoved();}\
virtual int GetNumberofRadioChannelsRemoved(void){ return m_parent->intf ## _GetNumberofRadioChannelsRemoved();}\
virtual int StoreBarkerMuxDetails(void){ return m_parent->intf ## _StoreBarkerMuxDetails();}\
virtual void SyncTemporaryTableRecords(void){ return m_parent->intf ## _SyncTemporaryTableRecords();}\
virtual int GetNumberOfSdsds(void){ return m_parent->intf ## _GetNumberOfSdsds();}\
virtual Bool GetSdsdByIndex(int count,HsvNITSatelliteDS * SdSdEntry){ return m_parent->intf ## _GetSdsdByIndex(count,SdSdEntry);}\
virtual int GetNumberOfTvChannelsInLnb(int Lnb){ return m_parent->intf ## _GetNumberOfTvChannelsInLnb(Lnb);}\
virtual int GetNumberOfRadioChannelsInLnb(int Lnb){ return m_parent->intf ## _GetNumberOfRadioChannelsInLnb(Lnb);}\
virtual void AssignLCN(HsvPgdatDigServiceData *psvcdat){ return m_parent->intf ## _AssignLCN(psvcdat);}\
virtual void GetTricolorRegionNames(Nat16 **names, int *len){ return m_parent->intf ## _GetTricolorRegionNames(names, len);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
