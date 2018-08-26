#ifndef IHSVDVBSISORTEDTABLEIDS_H
#define IHSVDVBSISORTEDTABLEIDS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDvbSiSortedTableIds
{
public:
	virtual ~IHsvDvbSiSortedTableIds(){}
	virtual int NitLcnTableMain(void)= 0;
	virtual int SdtTableActual(void)= 0;
	virtual int SdtTableOther(void)= 0;
	virtual int EitPresentActual(void)= 0;
	virtual int EitFollowActual(void)= 0;
	virtual int EitPresentOther(void)= 0;
	virtual int EitFollowOther(void)= 0;
	virtual int EitScheduleActual(void)= 0;
	virtual int EitScheduleOther(void)= 0;
	virtual int EitLinkageInfo(void)= 0;
	virtual int TotTableMain(void)= 0;
	virtual int LinkageInfoMain(void)= 0;
	virtual int NitLinkageInfoMain(void)= 0;
	virtual int NitLcnTableSub(void)= 0;
	virtual int NitSatelliteDS(void)= 0;
	virtual int NitLinkageInfoSub(void)= 0;
	virtual int NitOtherNetworkIdTable(void)= 0;
	virtual int NitFreqList(void)= 0;
	virtual int NitLcn2TableMain(void)= 0;
	virtual int NitLcn2TableSub(void)= 0;
	virtual int NitLcn3TableMain(void)= 0;
	virtual int NitHDSLcnTableMain(void)= 0;
	virtual int NitSrvcAtrbTableMain(void)= 0;
	virtual int NitSrvclstTableMain(void)= 0;
	virtual int NitSrvclstTableSub(void)= 0;
	virtual int NitTsRelocateTableMain(void)= 0;
	virtual int NitHDSLcnTableSub(void)= 0;
	virtual int SdtTargetRegion(void)= 0;
	virtual int BatSrvclstTableMain(void)= 0;
	virtual int FntSatelliteDS(void)= 0;
	virtual int FntSrvclstTable(void)= 0;
	virtual int FntLcnTable(void)= 0;
	virtual int FntTable(void)= 0;
	virtual int FstTable(void)= 0;
	virtual int BatLcnTable(void)= 0;
	virtual int BatLcn2Table(void)= 0;
	virtual int BatLinkageInfoMain(void)= 0;
	virtual int NitHeadEndFrequencyList(void)= 0;
	virtual int BatECNTable(void)= 0;
	virtual int BatDetailsTable(void)= 0;
	virtual int NitFreesatLinkageInfo(void)= 0;
	virtual int BatFreesatSrvGroupTable(void)= 0;
	virtual int BatFreesatInfoLocationTable(void)= 0;
	virtual int BatFreesatLCNTable(void)= 0;
	virtual int PostcodeFreesatPostcodeKeyMap(void)= 0;
	virtual int PostcodeFreesatRegionKeyMap(void)= 0;
};


#define IHsvDvbSiSortedTableIdsImpl(Comp,intf)    \
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
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvDvbSiSortedTableIds \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_NitLcnTableMain; \
    InterfaceParam<Comp,int> m_SdtTableActual; \
    InterfaceParam<Comp,int> m_SdtTableOther; \
    InterfaceParam<Comp,int> m_EitPresentActual; \
    InterfaceParam<Comp,int> m_EitFollowActual; \
    InterfaceParam<Comp,int> m_EitPresentOther; \
    InterfaceParam<Comp,int> m_EitFollowOther; \
    InterfaceParam<Comp,int> m_EitScheduleActual; \
    InterfaceParam<Comp,int> m_EitScheduleOther; \
    InterfaceParam<Comp,int> m_EitLinkageInfo; \
    InterfaceParam<Comp,int> m_TotTableMain; \
    InterfaceParam<Comp,int> m_LinkageInfoMain; \
    InterfaceParam<Comp,int> m_NitLinkageInfoMain; \
    InterfaceParam<Comp,int> m_NitLcnTableSub; \
    InterfaceParam<Comp,int> m_NitSatelliteDS; \
    InterfaceParam<Comp,int> m_NitLinkageInfoSub; \
    InterfaceParam<Comp,int> m_NitOtherNetworkIdTable; \
    InterfaceParam<Comp,int> m_NitFreqList; \
    InterfaceParam<Comp,int> m_NitLcn2TableMain; \
    InterfaceParam<Comp,int> m_NitLcn2TableSub; \
    InterfaceParam<Comp,int> m_NitLcn3TableMain; \
    InterfaceParam<Comp,int> m_NitHDSLcnTableMain; \
    InterfaceParam<Comp,int> m_NitSrvcAtrbTableMain; \
    InterfaceParam<Comp,int> m_NitSrvclstTableMain; \
    InterfaceParam<Comp,int> m_NitSrvclstTableSub; \
    InterfaceParam<Comp,int> m_NitTsRelocateTableMain; \
    InterfaceParam<Comp,int> m_NitHDSLcnTableSub; \
    InterfaceParam<Comp,int> m_SdtTargetRegion; \
    InterfaceParam<Comp,int> m_BatSrvclstTableMain; \
    InterfaceParam<Comp,int> m_FntSatelliteDS; \
    InterfaceParam<Comp,int> m_FntSrvclstTable; \
    InterfaceParam<Comp,int> m_FntLcnTable; \
    InterfaceParam<Comp,int> m_FntTable; \
    InterfaceParam<Comp,int> m_FstTable; \
    InterfaceParam<Comp,int> m_BatLcnTable; \
    InterfaceParam<Comp,int> m_BatLcn2Table; \
    InterfaceParam<Comp,int> m_BatLinkageInfoMain; \
    InterfaceParam<Comp,int> m_NitHeadEndFrequencyList; \
    InterfaceParam<Comp,int> m_BatECNTable; \
    InterfaceParam<Comp,int> m_BatDetailsTable; \
    InterfaceParam<Comp,int> m_NitFreesatLinkageInfo; \
    InterfaceParam<Comp,int> m_BatFreesatSrvGroupTable; \
    InterfaceParam<Comp,int> m_BatFreesatInteractiveStorageTable; \
    InterfaceParam<Comp,int> m_BatFreesatInteractiveResTable; \
    InterfaceParam<Comp,int> m_BatFreesatInfoLocationTable; \
    InterfaceParam<Comp,int> m_BatFreesatLCNTable; \
	InterfaceParam<Comp,int>m_PostcodeFreesatPostcodeKeyMap; \
	InterfaceParam<Comp,int> m_PostcodeFreesatRegionKeyMap; \
    Comp ## _ ## intf( Comp *parent):m_NitLcnTableMain(parent),m_SdtTableActual(parent),m_SdtTableOther(parent),m_EitPresentActual(parent),m_EitFollowActual(parent),m_EitPresentOther(parent),m_EitFollowOther(parent),m_EitScheduleActual(parent),m_EitScheduleOther(parent),m_EitLinkageInfo(parent),m_TotTableMain(parent),m_LinkageInfoMain(parent),m_NitLinkageInfoMain(parent),m_NitLcnTableSub(parent),m_NitSatelliteDS(parent),m_NitLinkageInfoSub(parent),m_NitOtherNetworkIdTable(parent),m_NitFreqList(parent),m_NitLcn2TableMain(parent),m_NitLcn2TableSub(parent),m_NitLcn3TableMain(parent),m_NitHDSLcnTableMain(parent),m_NitSrvcAtrbTableMain(parent),m_NitSrvclstTableMain(parent),m_NitSrvclstTableSub(parent),m_NitTsRelocateTableMain(parent),m_NitHDSLcnTableSub(parent),m_SdtTargetRegion(parent),m_BatSrvclstTableMain(parent),m_FntSatelliteDS(parent),m_FntSrvclstTable(parent),m_FntLcnTable(parent),m_FntTable(parent),m_FstTable(parent),m_BatLcnTable(parent),m_BatLcn2Table(parent),m_BatLinkageInfoMain(parent),m_NitHeadEndFrequencyList(parent),m_BatECNTable(parent),m_BatDetailsTable(parent),m_NitFreesatLinkageInfo(parent),m_BatFreesatSrvGroupTable(parent),m_BatFreesatInteractiveStorageTable(parent),m_BatFreesatInteractiveResTable(parent),m_BatFreesatInfoLocationTable(parent),m_BatFreesatLCNTable(parent),m_PostcodeFreesatPostcodeKeyMap(parent),m_PostcodeFreesatRegionKeyMap(parent) \
    {\
        m_parent = parent;\
    }\
virtual int NitLcnTableMain(void){ return m_NitLcnTableMain.Call();}\
virtual int SdtTableActual(void){ return m_SdtTableActual.Call();}\
virtual int SdtTableOther(void){ return m_SdtTableOther.Call();}\
virtual int EitPresentActual(void){ return m_EitPresentActual.Call();}\
virtual int EitFollowActual(void){ return m_EitFollowActual.Call();}\
virtual int EitPresentOther(void){ return m_EitPresentOther.Call();}\
virtual int EitFollowOther(void){ return m_EitFollowOther.Call();}\
virtual int EitScheduleActual(void){ return m_EitScheduleActual.Call();}\
virtual int EitScheduleOther(void){ return m_EitScheduleOther.Call();}\
virtual int EitLinkageInfo(void){ return m_EitLinkageInfo.Call();}\
virtual int TotTableMain(void){ return m_TotTableMain.Call();}\
virtual int LinkageInfoMain(void){ return m_LinkageInfoMain.Call();}\
virtual int NitLinkageInfoMain(void){ return m_NitLinkageInfoMain.Call();}\
virtual int NitLcnTableSub(void){ return m_NitLcnTableSub.Call();}\
virtual int NitSatelliteDS(void){ return m_NitSatelliteDS.Call();}\
virtual int NitLinkageInfoSub(void){ return m_NitLinkageInfoSub.Call();}\
virtual int NitOtherNetworkIdTable(void){ return m_NitOtherNetworkIdTable.Call();}\
virtual int NitFreqList(void){ return m_NitFreqList.Call();}\
virtual int NitLcn2TableMain(void){ return m_NitLcn2TableMain.Call();}\
virtual int NitLcn2TableSub(void){ return m_NitLcn2TableSub.Call();}\
virtual int NitLcn3TableMain(void){ return m_NitLcn3TableMain.Call();}\
virtual int NitHDSLcnTableMain(void){ return m_NitHDSLcnTableMain.Call();}\
virtual int NitSrvcAtrbTableMain(void){ return m_NitSrvcAtrbTableMain.Call();}\
virtual int NitSrvclstTableMain(void){ return m_NitSrvclstTableMain.Call();}\
virtual int NitSrvclstTableSub(void){ return m_NitSrvclstTableSub.Call();}\
virtual int NitTsRelocateTableMain(void){ return m_NitTsRelocateTableMain.Call();}\
virtual int NitHDSLcnTableSub(void){ return m_NitHDSLcnTableSub.Call();}\
virtual int SdtTargetRegion(void){ return m_SdtTargetRegion.Call();}\
virtual int BatSrvclstTableMain(void){ return m_BatSrvclstTableMain.Call();}\
virtual int FntSatelliteDS(void){ return m_FntSatelliteDS.Call();}\
virtual int FntSrvclstTable(void){ return m_FntSrvclstTable.Call();}\
virtual int FntLcnTable(void){ return m_FntLcnTable.Call();}\
virtual int FntTable(void){ return m_FntTable.Call();}\
virtual int FstTable(void){ return m_FstTable.Call();}\
virtual int BatLcnTable(void){ return m_BatLcnTable.Call();}\
virtual int BatLcn2Table(void){ return m_BatLcn2Table.Call();}\
virtual int BatLinkageInfoMain(void){ return m_BatLinkageInfoMain.Call();}\
virtual int NitHeadEndFrequencyList(void){ return m_NitHeadEndFrequencyList.Call();}\
virtual int BatECNTable(void){ return m_BatECNTable.Call();}\
virtual int BatDetailsTable(void){ return m_BatDetailsTable.Call();}\
virtual int NitFreesatLinkageInfo(void){ return m_NitFreesatLinkageInfo.Call();}\
virtual int BatFreesatSrvGroupTable(void){ return m_BatFreesatSrvGroupTable.Call();}\
virtual int BatFreesatInteractiveStorageTable(void){ return m_BatFreesatInteractiveStorageTable.Call();}\
virtual int BatFreesatInteractiveResTable(void){ return m_BatFreesatInteractiveResTable.Call();}\
virtual int BatFreesatInfoLocationTable(void){ return m_BatFreesatInfoLocationTable.Call();}\
virtual int BatFreesatLCNTable(void){ return m_BatFreesatLCNTable.Call();}\
virtual int PostcodeFreesatPostcodeKeyMap(void){ return m_PostcodeFreesatPostcodeKeyMap.Call();}\
virtual int PostcodeFreesatRegionKeyMap(void){ return m_PostcodeFreesatRegionKeyMap.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
