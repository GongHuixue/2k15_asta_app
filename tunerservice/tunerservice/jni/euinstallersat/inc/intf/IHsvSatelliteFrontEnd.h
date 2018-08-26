#ifndef IHSVSATELLITEFRONTEND_H
#define IHSVSATELLITEFRONTEND_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteFrontEnd
{
public:
	virtual ~IHsvSatelliteFrontEnd(){}
	#define IHsvSatelliteFrontEnd_PolarisationHorizontal		((int)0 )
	#define IHsvSatelliteFrontEnd_PolarisationVertical		((int)1 )
	#define IHsvSatelliteFrontEnd_BlindScanModeNormal		((int)1 )
	#define IHsvSatelliteFrontEnd_BlindScanModeMinimal		((int)2 )

	/*These are values from ITuningDVBS.java*/
	/*Modulation standard*/
	#define IHsvSatelliteFrontEnd_ModSysDVBS				((int)0 )
	#define IHsvSatelliteFrontEnd_ModSysDVBS2				((int)1 )

	/*Modulation type*/
	#define IHsvSatelliteFrontEnd_DVBSUnknown				((int)0 )
	#define IHsvSatelliteFrontEnd_DVBSQPSK					((int)1 )
	#define IHsvSatelliteFrontEnd_DVBSPSK8					((int)2 )
	#define IHsvSatelliteFrontEnd_DVBSAPSK16				((int)3 )
	#define IHsvSatelliteFrontEnd_DVBSAPSK32				((int)4 )

	/*FECInner*/
	#define IHsvSatelliteFrontEnd_FECInnerUnknown			((int)0 )
	#define IHsvSatelliteFrontEnd_FECInner12				((int)12 )
	#define IHsvSatelliteFrontEnd_FECInner23				((int)23 )
	#define IHsvSatelliteFrontEnd_FECInner34				((int)34 )
	#define IHsvSatelliteFrontEnd_FECInner35				((int)35 )
	#define IHsvSatelliteFrontEnd_FECInner45				((int)45 )
	#define IHsvSatelliteFrontEnd_FECInner56				((int)56 )
	#define IHsvSatelliteFrontEnd_FECInner78				((int)78 )
	#define IHsvSatelliteFrontEnd_FECInner89				((int)89 )
	#define IHsvSatelliteFrontEnd_FECInner910				((int)910 )

	/* ROll OFF Type*/
	#define IHsvSatelliteFrontEnd_RollOffUnknown			((int)0 )
	#define IHsvSatelliteFrontEnd_RollOffOP35				((int)35 )
	#define IHsvSatelliteFrontEnd_RollOffOP25				((int)25 )
	#define IHsvSatelliteFrontEnd_RollOffOP20				((int)20 )

	/** DVBS Pilots */
	#define IHsvSatelliteFrontEnd_PilotsOFF		((int)0 )
	#define IHsvSatelliteFrontEnd_PilotsON		((int)1 )
	
	virtual FResult SatelliteFrontEndTune(int LnbNumber,int LnbType,int Frequency,int SymbolRate,int Polarization,int Cookie,int ModlnStd,int ModlnType,int CodeRate, int RollOff, int FEC, int Pilots)= 0;
	virtual FResult StartSatelliteBlindScan(int LnbNumber,int Mode)= 0;
	virtual FResult ContinueSatelliteBlindScan(void)= 0;
	virtual FResult AbortSatelliteBlindScan(int LnbNumber)= 0;
	virtual FResult GetSatelliteFrontEndParams(int * LnbNumber,int * LnbType,int * LockStatus,int * LockedFreq,int * Polarization,int * SymbolRate,int * IqMode,int * Bandwidth)= 0;
	virtual FResult UnicableEnable(int LnbNumber,Bool Enable)= 0;
	virtual Bool IsSameFrequencyInIfRange(int LnbNumber,int SatelliteFreq,int Polarization)= 0;
};


#define IHsvSatelliteFrontEndImpl(Comp,intf)    \
virtual FResult intf ## _SatelliteFrontEndTune(int LnbNumber,int LnbType,int Frequency,int SymbolRate,int Polarization,int Cookie,int ModlnStd,int ModlnType,int CodeRate, int RollOff, int FEC, int Pilots);\
virtual FResult intf ## _StartSatelliteBlindScan(int LnbNumber,int Mode);\
virtual FResult intf ## _ContinueSatelliteBlindScan(void);\
virtual FResult intf ## _AbortSatelliteBlindScan(int LnbNumber);\
virtual FResult intf ## _GetSatelliteFrontEndParams(int * LnbNumber,int * LnbType,int * LockStatus,int * LockedFreq,int * Polarization,int * SymbolRate,int * IqMode,int * Bandwidth);\
virtual FResult intf ## _UnicableEnable(int LnbNumber,Bool Enable);\
virtual Bool intf ## _IsSameFrequencyInIfRange(int LnbNumber,int SatelliteFreq,int Polarization);\
class Comp ## _ ## intf : public IHsvSatelliteFrontEnd \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult SatelliteFrontEndTune(int LnbNumber,int LnbType,int Frequency,int SymbolRate,int Polarization,int Cookie,int ModlnStd,int ModlnType,int CodeRate, int RollOff, int FEC, int Pilots){ return m_parent->intf ## _SatelliteFrontEndTune(LnbNumber,LnbType,Frequency,SymbolRate,Polarization,Cookie,ModlnStd,ModlnType,CodeRate,RollOff,FEC,Pilots);}\
virtual FResult StartSatelliteBlindScan(int LnbNumber,int Mode){ return m_parent->intf ## _StartSatelliteBlindScan(LnbNumber,Mode);}\
virtual FResult ContinueSatelliteBlindScan(void){ return m_parent->intf ## _ContinueSatelliteBlindScan();}\
virtual FResult AbortSatelliteBlindScan(int LnbNumber){ return m_parent->intf ## _AbortSatelliteBlindScan(LnbNumber);}\
virtual FResult GetSatelliteFrontEndParams(int * LnbNumber,int * LnbType,int * LockStatus,int * LockedFreq,int * Polarization,int * SymbolRate,int * IqMode,int * Bandwidth){ return m_parent->intf ## _GetSatelliteFrontEndParams(LnbNumber,LnbType,LockStatus,LockedFreq,Polarization,SymbolRate,IqMode,Bandwidth);}\
virtual FResult UnicableEnable(int LnbNumber,Bool Enable){ return m_parent->intf ## _UnicableEnable(LnbNumber,Enable);}\
virtual Bool IsSameFrequencyInIfRange(int LnbNumber,int SatelliteFreq,int Polarization){ return m_parent->intf ## _IsSameFrequencyInIfRange(LnbNumber,SatelliteFreq,Polarization);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
