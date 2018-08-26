#ifndef IHSVSATELLITEPACKAGEINSTALLATION_H
#define IHSVSATELLITEPACKAGEINSTALLATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatellitePackageInstallation
{
public:
	virtual ~IHsvSatellitePackageInstallation(){}
	#define IHsvSatellitePackageInstallation_ManualInstallLnb		((int)1 )
	#define IHsvSatellitePackageInstallation_ManualInstallFreq		((int)2 )
	#define IHsvSatellitePackageInstallation_ManualInstallPolaraization		((int)3 )
	#define IHsvSatellitePackageInstallation_ManualInstallSymRate		((int)4 )
	#define IHsvSatellitePackageInstallation_ManualInstallSymRateMode		((int)5 )
	#define IHsvSatellitePackageInstallation_ManualInstallModulation		((int)6 )
	virtual int GetCurrentInstallationState(int * mode,int * state)= 0;
	virtual FResult StartInstallation(int Source,int Lnb,int Mode)= 0;
	virtual FResult StopInstallation(void)= 0;
	virtual FResult WriteBarkerMuxData(void)= 0;
	virtual int GetNumberOfTvChannelsFound(int Mode,int Lnb)= 0;
	virtual int GetNumberofRadioChannelsFound(int Mode,int Lnb)= 0;
	virtual int GetNumberOfTvChannelsRemoved(int Mode,int Lnb)= 0;
	virtual int GetNumberofRadioChannelsRemoved(int Mode,int Lnb)= 0;
	virtual int GetNumberOfDigitalChannelsAdded(void)= 0;
	virtual int GetNumberOfDigitalChannelsRemoved(void)= 0;
	virtual int GetNumberOfDigitalChannelsMoved(void)= 0;
	virtual FResult LoadManualInstallationDefaultValues(void)= 0;
	virtual FResult StoreManualInstallationValues(void)= 0;
	virtual Bool SetManualInstallationAttributes(int AttributeId,int Value)= 0;
	virtual int GetAttribute(int Mode,int AttributeId)= 0;
	virtual int GetScanProgressStatus(int Mode)= 0;
	virtual void GetSIDetails(HsvSDMSIDataValues * SiValues)= 0;
	virtual FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode)= 0;
	virtual FResult StartTricolorRegionParsing () = 0;
	virtual FResult SetTricolorRegionIndex (int index) = 0;
	virtual FResult GetTricolorRegionNames (Nat16 **regionNames, int *len) = 0;
};


#define IHsvSatellitePackageInstallationImpl(Comp,intf)    \
virtual int intf ## _GetCurrentInstallationState(int * mode,int * state);\
virtual FResult intf ## _StartInstallation(int Source,int Lnb,int Mode);\
virtual FResult intf ## _StopInstallation(void);\
virtual FResult intf ## _WriteBarkerMuxData(void);\
virtual int intf ## _GetNumberOfTvChannelsFound(int Mode,int Lnb);\
virtual int intf ## _GetNumberofRadioChannelsFound(int Mode,int Lnb);\
virtual int intf ## _GetNumberOfTvChannelsRemoved(int Mode,int Lnb);\
virtual int intf ## _GetNumberofRadioChannelsRemoved(int Mode,int Lnb);\
virtual int intf ## _GetNumberOfDigitalChannelsAdded(void);\
virtual int intf ## _GetNumberOfDigitalChannelsRemoved(void);\
virtual int intf ## _GetNumberOfDigitalChannelsMoved(void);\
virtual FResult intf ## _LoadManualInstallationDefaultValues(void);\
virtual FResult intf ## _StoreManualInstallationValues(void);\
virtual Bool intf ## _SetManualInstallationAttributes(int AttributeId,int Value);\
virtual int intf ## _GetAttribute(int Mode,int AttributeId);\
virtual int intf ## _GetScanProgressStatus(int Mode);\
virtual void intf ## _GetSIDetails(HsvSDMSIDataValues * SiValues);\
virtual FResult intf##_SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode);\
virtual FResult intf##_StartTricolorRegionParsing ();\
virtual FResult intf##_SetTricolorRegionIndex (int index);\
virtual FResult intf##_GetTricolorRegionNames (Nat16 **regionNames, int *len);\
class Comp ## _ ## intf : public IHsvSatellitePackageInstallation \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetCurrentInstallationState(int * mode,int * state){ return m_parent->intf ## _GetCurrentInstallationState(mode,state);}\
virtual FResult StartInstallation(int Source,int Lnb,int Mode){ return m_parent->intf ## _StartInstallation(Source,Lnb,Mode);}\
virtual FResult StopInstallation(void){ return m_parent->intf ## _StopInstallation();}\
virtual FResult WriteBarkerMuxData(void){ return m_parent->intf ## _WriteBarkerMuxData();}\
virtual int GetNumberOfTvChannelsFound(int Mode,int Lnb){ return m_parent->intf ## _GetNumberOfTvChannelsFound(Mode,Lnb);}\
virtual int GetNumberofRadioChannelsFound(int Mode,int Lnb){ return m_parent->intf ## _GetNumberofRadioChannelsFound(Mode,Lnb);}\
virtual int GetNumberOfTvChannelsRemoved(int Mode,int Lnb){ return m_parent->intf ## _GetNumberOfTvChannelsRemoved(Mode,Lnb);}\
virtual int GetNumberofRadioChannelsRemoved(int Mode,int Lnb){ return m_parent->intf ## _GetNumberofRadioChannelsRemoved(Mode,Lnb);}\
virtual int GetNumberOfDigitalChannelsAdded(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsAdded();}\
virtual int GetNumberOfDigitalChannelsRemoved(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsRemoved();}\
virtual int GetNumberOfDigitalChannelsMoved(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsMoved();}\
virtual FResult LoadManualInstallationDefaultValues(void){ return m_parent->intf ## _LoadManualInstallationDefaultValues();}\
virtual FResult StoreManualInstallationValues(void){ return m_parent->intf ## _StoreManualInstallationValues();}\
virtual Bool SetManualInstallationAttributes(int AttributeId,int Value){ return m_parent->intf ## _SetManualInstallationAttributes(AttributeId,Value);}\
virtual int GetAttribute(int Mode,int AttributeId){ return m_parent->intf ## _GetAttribute(Mode,AttributeId);}\
virtual int GetScanProgressStatus(int Mode){ return m_parent->intf ## _GetScanProgressStatus(Mode);}\
virtual void GetSIDetails(HsvSDMSIDataValues * SiValues){ return m_parent->intf ## _GetSIDetails(SiValues);}\
virtual FResult SetPostcode(Nat8 PostcodeLen, Nat8 *Postcode) { return m_parent->intf ## _SetPostcode(PostcodeLen,Postcode);}\
virtual FResult StartTricolorRegionParsing() { return m_parent->intf ## _StartTricolorRegionParsing();}\
virtual FResult SetTricolorRegionIndex(int index) { return m_parent->intf ## _SetTricolorRegionIndex(index);}\
virtual FResult GetTricolorRegionNames(Nat16 **regionNames, int *len) { return m_parent->intf ## _GetTricolorRegionNames(regionNames, len);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
