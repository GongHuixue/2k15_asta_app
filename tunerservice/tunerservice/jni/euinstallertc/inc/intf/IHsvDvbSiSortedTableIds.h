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
	virtual int NitCableDSMain(void)= 0;
	virtual int NitCableDSSub(void)= 0;
	virtual int NitLinkageInfoSub(void)= 0;
	virtual int NitOtherNetworkIdTable(void)= 0;
	virtual int NitFreqList(void)= 0;
	virtual int NitLcn2TableMain(void)= 0;
	virtual int NitLcn2TableSub(void)= 0;
	virtual int NitHDSLcnTableMain(void)= 0;
	virtual int NitSrvcAtrbTableMain(void)= 0;
	virtual int NitSrvclstTableMain(void)= 0;
	virtual int NitSrvclstTableSub(void)= 0;
	virtual int NitTsRelocateTableMain(void)= 0;
	virtual int NitHDSLcnTableSub(void)= 0;
	virtual int SdtTargetRegion(void)= 0;
	virtual int NitTargetRegion(void)= 0;
	virtual int NitTargetRegionName(void)= 0;
	virtual int CamNitCableDS(void)= 0;
	virtual int CamNitTerrestrialDS(void)= 0;
	virtual int CamNitC2DS(void)= 0;
	virtual int CamNitT2DS(void)= 0;
	virtual int CamNitContentLabel(void)= 0;
	virtual int CamNitService(void)= 0;
	virtual int CamNitLinkageInfo(void)= 0;
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
    InterfaceParam<Comp,int> m_NitCableDSMain; \
    InterfaceParam<Comp,int> m_NitCableDSSub; \
    InterfaceParam<Comp,int> m_NitLinkageInfoSub; \
    InterfaceParam<Comp,int> m_NitOtherNetworkIdTable; \
    InterfaceParam<Comp,int> m_NitFreqList; \
    InterfaceParam<Comp,int> m_NitLcn2TableMain; \
    InterfaceParam<Comp,int> m_NitLcn2TableSub; \
    InterfaceParam<Comp,int> m_NitHDSLcnTableMain; \
    InterfaceParam<Comp,int> m_NitSrvcAtrbTableMain; \
    InterfaceParam<Comp,int> m_NitSrvclstTableMain; \
    InterfaceParam<Comp,int> m_NitSrvclstTableSub; \
    InterfaceParam<Comp,int> m_NitTsRelocateTableMain; \
    InterfaceParam<Comp,int> m_NitHDSLcnTableSub; \
    InterfaceParam<Comp,int> m_SdtTargetRegion; \
    InterfaceParam<Comp,int> m_NitTargetRegion; \
    InterfaceParam<Comp,int> m_NitTargetRegionName; \
    InterfaceParam<Comp,int> m_CamNitCableDS; \
    InterfaceParam<Comp,int> m_CamNitTerrestrialDS; \
    InterfaceParam<Comp,int> m_CamNitC2DS; \
    InterfaceParam<Comp,int> m_CamNitT2DS; \
    InterfaceParam<Comp,int> m_CamNitContentLabel; \
    InterfaceParam<Comp,int> m_CamNitService; \
    InterfaceParam<Comp,int> m_CamNitLinkageInfo; \
    Comp ## _ ## intf( Comp *parent):m_NitLcnTableMain(parent),m_SdtTableActual(parent),m_SdtTableOther(parent),m_EitPresentActual(parent),m_EitFollowActual(parent),m_EitPresentOther(parent),m_EitFollowOther(parent),m_EitScheduleActual(parent),m_EitScheduleOther(parent),m_EitLinkageInfo(parent),m_TotTableMain(parent),m_LinkageInfoMain(parent),m_NitLinkageInfoMain(parent),m_NitLcnTableSub(parent),m_NitCableDSMain(parent),m_NitCableDSSub(parent),m_NitLinkageInfoSub(parent),m_NitOtherNetworkIdTable(parent),m_NitFreqList(parent),m_NitLcn2TableMain(parent),m_NitLcn2TableSub(parent),m_NitHDSLcnTableMain(parent),m_NitSrvcAtrbTableMain(parent),m_NitSrvclstTableMain(parent),m_NitSrvclstTableSub(parent),m_NitTsRelocateTableMain(parent),m_NitHDSLcnTableSub(parent),m_SdtTargetRegion(parent),m_NitTargetRegion(parent),m_NitTargetRegionName(parent),m_CamNitCableDS(parent),m_CamNitTerrestrialDS(parent),m_CamNitC2DS(parent),m_CamNitT2DS(parent),m_CamNitContentLabel(parent),m_CamNitService(parent),m_CamNitLinkageInfo(parent) \
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
virtual int NitCableDSMain(void){ return m_NitCableDSMain.Call();}\
virtual int NitCableDSSub(void){ return m_NitCableDSSub.Call();}\
virtual int NitLinkageInfoSub(void){ return m_NitLinkageInfoSub.Call();}\
virtual int NitOtherNetworkIdTable(void){ return m_NitOtherNetworkIdTable.Call();}\
virtual int NitFreqList(void){ return m_NitFreqList.Call();}\
virtual int NitLcn2TableMain(void){ return m_NitLcn2TableMain.Call();}\
virtual int NitLcn2TableSub(void){ return m_NitLcn2TableSub.Call();}\
virtual int NitHDSLcnTableMain(void){ return m_NitHDSLcnTableMain.Call();}\
virtual int NitSrvcAtrbTableMain(void){ return m_NitSrvcAtrbTableMain.Call();}\
virtual int NitSrvclstTableMain(void){ return m_NitSrvclstTableMain.Call();}\
virtual int NitSrvclstTableSub(void){ return m_NitSrvclstTableSub.Call();}\
virtual int NitTsRelocateTableMain(void){ return m_NitTsRelocateTableMain.Call();}\
virtual int NitHDSLcnTableSub(void){ return m_NitHDSLcnTableSub.Call();}\
virtual int SdtTargetRegion(void){ return m_SdtTargetRegion.Call();}\
virtual int NitTargetRegion(void){ return m_NitTargetRegion.Call();}\
virtual int NitTargetRegionName(void){ return m_NitTargetRegionName.Call();}\
virtual int CamNitCableDS(void){ return m_CamNitCableDS.Call();}\
virtual int CamNitTerrestrialDS(void){ return m_CamNitTerrestrialDS.Call();}\
virtual int CamNitC2DS(void){ return m_CamNitC2DS.Call();}\
virtual int CamNitT2DS(void){ return m_CamNitT2DS.Call();}\
virtual int CamNitContentLabel(void){ return m_CamNitContentLabel.Call();}\
virtual int CamNitService(void){ return m_CamNitService.Call();}\
virtual int CamNitLinkageInfo(void){ return m_CamNitLinkageInfo.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
