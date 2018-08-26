#ifndef IHSVINSTALLATIONSIGSTRENGTH_H
#define IHSVINSTALLATIONSIGSTRENGTH_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallationSigStrength
{
public:
	virtual ~IHsvInstallationSigStrength(){}
	#define IHsvInstallationSigStrength_InsQsm		((int)0 )
	#define IHsvInstallationSigStrength_InsSsm		((int)1 )
	virtual void Initialise(void)= 0;
	virtual FResult GetSigStrengthRange(int mode,Nat32 * min,Nat32 * max)= 0;
	virtual Nat32 GetSignalStrength(int mode)= 0;
	virtual Nat32 GetMinSignalStrength(int mode)= 0;
	virtual Nat32 GetMaxSignalStrength(int mode)= 0;
	virtual Nat32 GetActualSignalStrength(int mode,Nat32 cookie)= 0;
	virtual Bool StartSigStrMeasAll(void)= 0;
	virtual void StopSigStrMeasAll(void)= 0;
	virtual void UpdateSigStrRange(void)= 0;
	virtual Bool GetSigStrengthMeasured(void)= 0;
	virtual void SetSigStrengthMeasured(Bool flag)= 0;
	virtual void StartSigStrMeas(int measmode)= 0;
	virtual void StopSigStrMeas(int measmode)= 0;
	virtual Bool IsSignalStrengthMeasurementValid(int measmode)= 0;
};


#define IHsvInstallationSigStrengthImpl(Comp,intf)    \
virtual void intf ## _Initialise(void);\
virtual FResult intf ## _GetSigStrengthRange(int mode,Nat32 * min,Nat32 * max);\
virtual Nat32 intf ## _GetSignalStrength(int mode);\
virtual Nat32 intf ## _GetMinSignalStrength(int mode);\
virtual Nat32 intf ## _GetMaxSignalStrength(int mode);\
virtual Nat32 intf ## _GetActualSignalStrength(int mode,Nat32 cookie);\
virtual Bool intf ## _StartSigStrMeasAll(void);\
virtual void intf ## _StopSigStrMeasAll(void);\
virtual void intf ## _UpdateSigStrRange(void);\
virtual Bool intf ## _GetSigStrengthMeasured(void);\
virtual void intf ## _SetSigStrengthMeasured(Bool flag);\
virtual void intf ## _StartSigStrMeas(int measmode);\
virtual void intf ## _StopSigStrMeas(int measmode);\
virtual Bool intf ## _IsSignalStrengthMeasurementValid(int measmode);\
class Comp ## _ ## intf : public IHsvInstallationSigStrength \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Initialise(void){ return m_parent->intf ## _Initialise();}\
virtual FResult GetSigStrengthRange(int mode,Nat32 * min,Nat32 * max){ return m_parent->intf ## _GetSigStrengthRange(mode,min,max);}\
virtual Nat32 GetSignalStrength(int mode){ return m_parent->intf ## _GetSignalStrength(mode);}\
virtual Nat32 GetMinSignalStrength(int mode){ return m_parent->intf ## _GetMinSignalStrength(mode);}\
virtual Nat32 GetMaxSignalStrength(int mode){ return m_parent->intf ## _GetMaxSignalStrength(mode);}\
virtual Nat32 GetActualSignalStrength(int mode,Nat32 cookie){ return m_parent->intf ## _GetActualSignalStrength(mode,cookie);}\
virtual Bool StartSigStrMeasAll(void){ return m_parent->intf ## _StartSigStrMeasAll();}\
virtual void StopSigStrMeasAll(void){ return m_parent->intf ## _StopSigStrMeasAll();}\
virtual void UpdateSigStrRange(void){ return m_parent->intf ## _UpdateSigStrRange();}\
virtual Bool GetSigStrengthMeasured(void){ return m_parent->intf ## _GetSigStrengthMeasured();}\
virtual void SetSigStrengthMeasured(Bool flag){ return m_parent->intf ## _SetSigStrengthMeasured(flag);}\
virtual void StartSigStrMeas(int measmode){ return m_parent->intf ## _StartSigStrMeas(measmode);}\
virtual void StopSigStrMeas(int measmode){ return m_parent->intf ## _StopSigStrMeas(measmode);}\
virtual Bool IsSignalStrengthMeasurementValid(int measmode){ return m_parent->intf ## _IsSignalStrengthMeasurementValid(measmode);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
