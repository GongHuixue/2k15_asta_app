#ifndef IHSVDIGITALSCANSTEP_H
#define IHSVDIGITALSCANSTEP_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalScanStep
{
public:
	virtual ~IHsvDigitalScanStep(){}
	virtual void Initialize(int InstallationMode)= 0;
	virtual FResult LoadCurrentSdsdList(int InstallationMode,int Lnb)= 0;
	virtual void ResetCurrentSdsdList(void)= 0;
	virtual FResult GetNextFrequencyValues(int InstallationMode,int * StartFreq,int * EndFreq,int * SymbolRate,Nat8 * Polarization,int * ModlnStd,int * ModlnType,Nat8 * Complete)= 0;
	virtual FResult UpdateFrequencyOnStationFound(void)= 0;
	virtual FResult UpdateFrequencyOnStationNotFound(void)= 0;
	virtual int GetScanProgressStatus(int Mode)= 0;
};


#define IHsvDigitalScanStepImpl(Comp,intf)    \
virtual void intf ## _Initialize(int InstallationMode);\
virtual FResult intf ## _LoadCurrentSdsdList(int InstallationMode,int Lnb);\
virtual void intf ## _ResetCurrentSdsdList(void);\
virtual FResult intf ## _GetNextFrequencyValues(int InstallationMode,int * StartFreq,int * EndFreq,int * SymbolRate,Nat8 * Polarization,int * ModlnStd,int * ModlnType,Nat8 * Complete);\
virtual FResult intf ## _UpdateFrequencyOnStationFound(void);\
virtual FResult intf ## _UpdateFrequencyOnStationNotFound(void);\
virtual int intf ## _GetScanProgressStatus(int Mode);\
class Comp ## _ ## intf : public IHsvDigitalScanStep \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Initialize(int InstallationMode){ return m_parent->intf ## _Initialize(InstallationMode);}\
virtual FResult LoadCurrentSdsdList(int InstallationMode,int Lnb){ return m_parent->intf ## _LoadCurrentSdsdList(InstallationMode,Lnb);}\
virtual void ResetCurrentSdsdList(void){ return m_parent->intf ## _ResetCurrentSdsdList();}\
virtual FResult GetNextFrequencyValues(int InstallationMode,int * StartFreq,int * EndFreq,int * SymbolRate,Nat8 * Polarization,int * ModlnStd,int * ModlnType,Nat8 * Complete){ return m_parent->intf ## _GetNextFrequencyValues(InstallationMode,StartFreq,EndFreq,SymbolRate,Polarization,ModlnStd,ModlnType,Complete);}\
virtual FResult UpdateFrequencyOnStationFound(void){ return m_parent->intf ## _UpdateFrequencyOnStationFound();}\
virtual FResult UpdateFrequencyOnStationNotFound(void){ return m_parent->intf ## _UpdateFrequencyOnStationNotFound();}\
virtual int GetScanProgressStatus(int Mode){ return m_parent->intf ## _GetScanProgressStatus(Mode);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
