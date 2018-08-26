#ifndef IHSVDIGITALACQUISITION_H
#define IHSVDIGITALACQUISITION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDigitalAcquisition
{
public:
	virtual ~IHsvDigitalAcquisition(){}
	virtual void Initialise(void)= 0;
	virtual void InitialiseTotalChannels(void)= 0;
	virtual void AcquireData(void)= 0;
	virtual int GetNumberOfDigitalChannelsFound(void)= 0;
	virtual int GetNumberOfDigitalChannelsRemoved(void)= 0;
	virtual int GetNumberOfChannels(int servicetype)= 0;
	virtual int GetNextSampleProgram(void)= 0;
	virtual void AcquireLCNData(void)= 0;
	virtual void AcquireServiceListData(void)= 0;
	virtual void StartBackgroundInstall(void)= 0;
	virtual void ResetBackgroundInstall(void)= 0;
	virtual Bool IsNetworkUpdateDetected(void)= 0;
	virtual void DeleteServices(void)= 0;
	virtual int GetNetworkIDList(void)= 0;
	virtual void GetNetworkIDName(int index,Nat16 * NetworkName)= 0;
	virtual void SetFavouriteNetworkID(int mode,int attrib,int index)= 0;
	virtual int GetNumberOfChannelListIds()= 0;
	virtual int GetChannelListIdByIndex(int index)= 0;
	virtual void SetFavouriteChannelListId(int mode,int attrib,int index)= 0;
	virtual void GetChannelListIDName(int index,Nat16 *ChannelistName)=0;
	virtual void ClearNetworkNameCache(void)= 0;
	virtual Bool IsLCNValid(void)= 0;
	virtual void AcquireONID(void)= 0;
	virtual void SyncTemporaryTableRecords(void)= 0;
	virtual void ClearCache(void)= 0;
	virtual void GetRegionList(HsvNetworkRegionsData * RegionsData)= 0;
	virtual void SetFavouriteRegion(int mode,int index,HsvEnmRegionType RegionType)= 0;
	virtual int GetFavouriteRegion(int mode,HsvEnmRegionType RegionType)= 0;
	virtual void Enable(void)= 0;
	virtual void Disable(void)= 0;
	virtual void GetCachedRegionDetails(HsvTargetRegionCache * RegionCache)= 0;
	virtual void UpdateBarkerMuxInfo(Nat16 ONID,Nat16 TSID)= 0;
	virtual void AcquireSDTOtherData()= 0;
};


#define IHsvDigitalAcquisitionImpl(Comp,intf)    \
virtual void intf ## _Initialise(void);\
virtual void intf ## _InitialiseTotalChannels(void);\
virtual void intf ## _AcquireData(void);\
virtual int intf ## _GetNumberOfDigitalChannelsFound(void);\
virtual int intf ## _GetNumberOfDigitalChannelsRemoved(void);\
virtual int intf ## _GetNumberOfChannels(int servicetype);\
virtual int intf ## _GetNextSampleProgram(void);\
virtual void intf ## _AcquireLCNData(void);\
virtual void intf ## _AcquireServiceListData(void);\
virtual void intf ## _StartBackgroundInstall(void);\
virtual void intf ## _ResetBackgroundInstall(void);\
virtual Bool intf ## _IsNetworkUpdateDetected(void);\
virtual void intf ## _DeleteServices(void);\
virtual int intf ## _GetNetworkIDList(void);\
virtual void intf ## _GetNetworkIDName(int index,Nat16 * NetworkName);\
virtual void intf ## _SetFavouriteNetworkID(int mode,int attrib,int index);\
virtual int intf ## _GetNumberOfChannelListIds();\
virtual int intf ## _GetChannelListIdByIndex(int index);\
virtual void intf ## _SetFavouriteChannelListId(int mode,int attrib,int index );\
virtual void intf ## _GetChannelListIDName(int index,Nat16 *ChannelistName);\
virtual void intf ## _ClearNetworkNameCache(void);\
virtual Bool intf ## _IsLCNValid(void);\
virtual void intf ## _AcquireONID(void);\
virtual void intf ## _SyncTemporaryTableRecords(void);\
virtual void intf ## _ClearCache(void);\
virtual void intf ## _GetRegionList(HsvNetworkRegionsData * RegionsData);\
virtual void intf ## _SetFavouriteRegion(int mode,int index,HsvEnmRegionType RegionType);\
virtual int intf ## _GetFavouriteRegion(int mode,HsvEnmRegionType RegionType);\
virtual void intf ## _Enable(void);\
virtual void intf ## _Disable(void);\
virtual void intf ## _GetCachedRegionDetails(HsvTargetRegionCache * RegionCache);\
virtual void intf ## _UpdateBarkerMuxInfo(Nat16 ONID,Nat16 TSID);\
virtual void intf ## _AcquireSDTOtherData();\
class Comp ## _ ## intf : public IHsvDigitalAcquisition \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Initialise(void){ return m_parent->intf ## _Initialise();}\
virtual void InitialiseTotalChannels(void){ return m_parent->intf ## _InitialiseTotalChannels();}\
virtual void AcquireData(void){ return m_parent->intf ## _AcquireData();}\
virtual int GetNumberOfDigitalChannelsFound(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsFound();}\
virtual int GetNumberOfDigitalChannelsRemoved(void){ return m_parent->intf ## _GetNumberOfDigitalChannelsRemoved();}\
virtual int GetNumberOfChannels(int servicetype){ return m_parent->intf ## _GetNumberOfChannels(servicetype);}\
virtual int GetNextSampleProgram(void){ return m_parent->intf ## _GetNextSampleProgram();}\
virtual void AcquireLCNData(void){ return m_parent->intf ## _AcquireLCNData();}\
virtual void AcquireServiceListData(void){ return m_parent->intf ## _AcquireServiceListData();}\
virtual void StartBackgroundInstall(void){ return m_parent->intf ## _StartBackgroundInstall();}\
virtual void ResetBackgroundInstall(void){ return m_parent->intf ## _ResetBackgroundInstall();}\
virtual Bool IsNetworkUpdateDetected(void){ return m_parent->intf ## _IsNetworkUpdateDetected();}\
virtual void DeleteServices(void){ return m_parent->intf ## _DeleteServices();}\
virtual int GetNetworkIDList(void){ return m_parent->intf ## _GetNetworkIDList();}\
virtual void GetNetworkIDName(int index,Nat16 * NetworkName){ return m_parent->intf ## _GetNetworkIDName(index,NetworkName);}\
virtual void SetFavouriteNetworkID(int mode,int attrib,int index){ return m_parent->intf ## _SetFavouriteNetworkID(mode,attrib,index);}\
virtual int GetNumberOfChannelListIds(){ return m_parent->intf ## _GetNumberOfChannelListIds();}\
virtual int GetChannelListIdByIndex(int index){ return m_parent->intf ## _GetChannelListIdByIndex(index);}\
virtual void SetFavouriteChannelListId(int mode,int attrib,int index){ return m_parent->intf ## _SetFavouriteChannelListId(mode,attrib,index );}\
virtual void GetChannelListIDName(int index,Nat16 * ChannelistName){ return m_parent->intf ## _GetChannelListIDName(index,ChannelistName);}\
virtual void ClearNetworkNameCache(void){ return m_parent->intf ## _ClearNetworkNameCache();}\
virtual Bool IsLCNValid(void){ return m_parent->intf ## _IsLCNValid();}\
virtual void AcquireONID(void){ return m_parent->intf ## _AcquireONID();}\
virtual void SyncTemporaryTableRecords(void){ return m_parent->intf ## _SyncTemporaryTableRecords();}\
virtual void ClearCache(void){ return m_parent->intf ## _ClearCache();}\
virtual void GetRegionList(HsvNetworkRegionsData * RegionsData){ return m_parent->intf ## _GetRegionList(RegionsData);}\
virtual void SetFavouriteRegion(int mode,int index,HsvEnmRegionType RegionType){ return m_parent->intf ## _SetFavouriteRegion(mode,index,RegionType);}\
virtual int GetFavouriteRegion(int mode,HsvEnmRegionType RegionType){ return m_parent->intf ## _GetFavouriteRegion(mode,RegionType);}\
virtual void Enable(void){ return m_parent->intf ## _Enable();}\
virtual void Disable(void){ return m_parent->intf ## _Disable();}\
virtual void GetCachedRegionDetails(HsvTargetRegionCache * RegionCache){ return m_parent->intf ## _GetCachedRegionDetails(RegionCache);}\
virtual void UpdateBarkerMuxInfo(Nat16 ONID,Nat16 TSID){ return m_parent->intf ## _UpdateBarkerMuxInfo(ONID,TSID);}\
virtual void AcquireSDTOtherData(void){ return m_parent->intf ## _AcquireSDTOtherData();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
