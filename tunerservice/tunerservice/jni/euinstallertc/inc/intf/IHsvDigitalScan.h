#ifndef IHSVDIGITALSCAN_H
#define IHSVDIGITALSCAN_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalScan
{
public:
	virtual ~IHsvDigitalScan(){}
	#define IHsvDigitalScan_stidle		((int)0 )
	#define IHsvDigitalScan_stfewait		((int)1 )
	#define IHsvDigitalScan_stdmxwait		((int)2 )
	#define IHsvDigitalScan_stdecision		((int)3 )
	virtual void Initialise(void)= 0;
	virtual FResult StartInstallation(int source,int ptc,int mode)= 0;
	virtual FResult StopInstallation(void)= 0;
	virtual FResult StartDigitalScan(void)= 0;
	virtual FResult StartDigitalTuning(int frequency)= 0;
	virtual FResult StopDigitalScan(void)= 0;
	virtual int GetNoOfPass(void)= 0;
	virtual int GetCurrentPass(void)= 0;
	virtual void GetPTCInfo(HsvInstallationPTC * ptc)= 0;
	virtual FResult StoreWeakSignalInstallationChannel(void)= 0;
	virtual int GetNumberOfDigitalChannelsFound(void)= 0;
	virtual int GetNumberOfDigitalChannelsRemoved(void)= 0;
	virtual int GetTargetNitType(Nat16 * NetworkId)= 0;
	virtual int GetCurrentState(void)= 0;
	virtual int GetSDTType(void)= 0;
	virtual Bool GetAltTSValues(Nat16 * ONID,Nat16 * TSID)= 0;
	virtual Bool GetCurTSValues(Nat16 * ONID,Nat16 * TSID)= 0;
	virtual HsvStreamPriority GetStreamPriority(void)= 0;
	virtual void SetStreamPriority(HsvStreamPriority prio)= 0;
	virtual void SyncComplete(void)= 0;
	virtual void ClearCache(void)= 0;
	virtual int GetPLPIds(int * PLPIds)= 0;
	virtual HsvHierarchyMode GetHierarchyMode(void)= 0;
	virtual void ZiggoGetPTCInfo(HsvInstallationPTC * ptc,Nat16 Onid,Nat16 Tsid)= 0;
	virtual int ZiggoGetSDTType(Nat16 Frequency)= 0;
	virtual void GetEpgBarkerMux(Nat16 * ONID,Nat16 * TSID)= 0;
	virtual Bool ZiggoNetworkDataSet(Bool ActionValue)= 0;
	virtual void ClearPersistent(void)= 0;
	virtual void GetSIDetails(HsvSDMSIDataValues* sivalues)= 0;
};


#define IHsvDigitalScanImpl(Comp,intf)    \
virtual void intf ## _Initialise(void);\
virtual FResult intf ## _StartInstallation(int source,int ptc,int mode);\
virtual FResult intf ## _StopInstallation(void);\
virtual FResult intf ## _StartDigitalScan(void);\
virtual FResult intf ## _StartDigitalTuning(int frequency);\
virtual FResult intf ## _StopDigitalScan(void);\
virtual int intf ## _GetNoOfPass(void);\
virtual int intf ## _GetCurrentPass(void);\
virtual void intf ## _GetPTCInfo(HsvInstallationPTC * ptc);\
virtual FResult intf ## _StoreWeakSignalInstallationChannel(void);\
virtual int intf ## _GetNumberOfDigitalChannelsFound(void);\
virtual int intf ## _GetNumberOfDigitalChannelsRemoved(void);\
virtual int intf ## _GetTargetNitType(Nat16 * NetworkId);\
virtual int intf ## _GetCurrentState(void);\
virtual int intf ## _GetSDTType(void);\
virtual Bool intf ## _GetAltTSValues(Nat16 * ONID,Nat16 * TSID);\
virtual Bool intf ## _GetCurTSValues(Nat16 * ONID,Nat16 * TSID);\
virtual HsvStreamPriority intf ## _GetStreamPriority(void);\
virtual void intf ## _SetStreamPriority(HsvStreamPriority prio);\
virtual void intf ## _SyncComplete(void);\
virtual void intf ## _ClearCache(void);\
virtual int intf ## _GetPLPIds(int * PLPIds);\
virtual HsvHierarchyMode intf ## _GetHierarchyMode(void);\
virtual void intf ## _ZiggoGetPTCInfo(HsvInstallationPTC * ptc,Nat16 Onid,Nat16 Tsid);\
virtual int intf ## _ZiggoGetSDTType(Nat16 Frequency);\
virtual void intf ## _GetEpgBarkerMux(Nat16 * ONID,Nat16 * TSID);\
virtual Bool intf ## _ZiggoNetworkDataSet(Bool ActionValue);\
virtual void intf ## _ClearPersistent(void);\
virtual void intf ## _GetSIDetails(HsvSDMSIDataValues* sivalues);\
class Comp ## _ ## intf : public IHsvDigitalScan \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Initialise(void){ return m_parent->intf ## _Initialise();}\
virtual FResult StartInstallation(int source,int ptc,int mode){ return m_parent->intf ## _StartInstallation(source,ptc,mode);}\
virtual FResult StopInstallation(void){ return m_parent->intf ## _StopInstallation();}\
virtual FResult StartDigitalScan(void){ return m_parent->intf ## _StartDigitalScan();}\
virtual FResult StartDigitalTuning(int frequency){ return m_parent->intf ## _StartDigitalTuning(frequency);}\
virtual FResult StopDigitalScan(void){ return m_parent->intf ## _StopDigitalScan();}\
virtual int GetNoOfPass(void){ return m_parent->intf ## _GetNoOfPass();}\
virtual int GetCurrentPass(void){ return m_parent->intf ## _GetCurrentPass();}\
virtual void GetPTCInfo(HsvInstallationPTC * ptc){ return m_parent->intf ## _GetPTCInfo(ptc);}\
virtual FResult StoreWeakSignalInstallationChannel(void){ return m_parent->intf ## _StoreWeakSignalInstallationChannel();}\
virtual int GetNumberOfDigitalChannelsFound(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsFound();}\
virtual int GetNumberOfDigitalChannelsRemoved(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsRemoved();}\
virtual int GetTargetNitType(Nat16 * NetworkId){ return m_parent->intf ## _GetTargetNitType(NetworkId);}\
virtual int GetCurrentState(void){ return m_parent->intf ## _GetCurrentState();}\
virtual int GetSDTType(void){ return m_parent->intf ## _GetSDTType();}\
virtual Bool GetAltTSValues(Nat16 * ONID,Nat16 * TSID){ return m_parent->intf ## _GetAltTSValues(ONID,TSID);}\
virtual Bool GetCurTSValues(Nat16 * ONID,Nat16 * TSID){ return m_parent->intf ## _GetCurTSValues(ONID,TSID);}\
virtual HsvStreamPriority GetStreamPriority(void){ return m_parent->intf ## _GetStreamPriority();}\
virtual void SetStreamPriority(HsvStreamPriority prio){ return m_parent->intf ## _SetStreamPriority(prio);}\
virtual void SyncComplete(void){ return m_parent->intf ## _SyncComplete();}\
virtual void ClearCache(void){ return m_parent->intf ## _ClearCache();}\
virtual int GetPLPIds(int * PLPIds){ return m_parent->intf ## _GetPLPIds(PLPIds);}\
virtual HsvHierarchyMode GetHierarchyMode(void){ return m_parent->intf ## _GetHierarchyMode();}\
virtual void ZiggoGetPTCInfo(HsvInstallationPTC * ptc,Nat16 Onid,Nat16 Tsid){ return m_parent->intf ## _ZiggoGetPTCInfo(ptc,Onid,Tsid);}\
virtual int ZiggoGetSDTType(Nat16 Frequency){ return m_parent->intf ## _ZiggoGetSDTType(Frequency);}\
virtual void GetEpgBarkerMux(Nat16 * ONID,Nat16 * TSID){ return m_parent->intf ## _GetEpgBarkerMux(ONID,TSID);}\
virtual Bool ZiggoNetworkDataSet(Bool ActionValue){ return m_parent->intf ## _ZiggoNetworkDataSet(ActionValue);}\
virtual void ClearPersistent(void){ return m_parent->intf ## _ClearPersistent();}\
virtual void GetSIDetails(HsvSDMSIDataValues* sivalues){return m_parent->intf ## _GetSIDetails(sivalues);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
