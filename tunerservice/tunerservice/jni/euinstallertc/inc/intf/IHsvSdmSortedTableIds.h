#ifndef IHSVSDMSORTEDTABLEIDS_H
#define IHSVSDMSORTEDTABLEIDS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSdmSortedTableIds
{
public:
	virtual ~IHsvSdmSortedTableIds(){}
	virtual int VcTableMain(void)= 0;
	virtual int VcTableAux(void)= 0;
	virtual int MgtTableMain(void)= 0;
	virtual int MgtTableAux(void)= 0;
	virtual int PmtTableMain(void)= 0;
	virtual int PmtTableAux(void)= 0;
	virtual int BasicPidInfoMain(void)= 0;
	virtual int BasicPidInfoAux(void)= 0;
	virtual int AudioInfoMain(void)= 0;
	virtual int AudioInfoAux(void)= 0;
	virtual int SubtitlingInfoMain(void)= 0;
	virtual int SubtitlingInfoAux(void)= 0;
	virtual int TeletextInfoMain(void)= 0;
	virtual int TeletextInfoAux(void)= 0;
	virtual int ComponentTagInfoMain(void)= 0;
	virtual int ComponentTagInfoAux(void)= 0;
	virtual int DatabroadcastInfoMain(void)= 0;
	virtual int DatabroadcastInfoAux(void)= 0;
	virtual int ReqTableMain(void)= 0;
	virtual int ReqTableAux(void)= 0;
	virtual int EitTableMain(void)= 0;
	virtual int EitTableAux(void)= 0;
};


#define IHsvSdmSortedTableIdsImpl(Comp,intf)    \
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
class Comp ## _ ## intf : public IHsvSdmSortedTableIds \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_VcTableMain; \
    InterfaceParam<Comp,int> m_VcTableAux; \
    InterfaceParam<Comp,int> m_MgtTableMain; \
    InterfaceParam<Comp,int> m_MgtTableAux; \
    InterfaceParam<Comp,int> m_PmtTableMain; \
    InterfaceParam<Comp,int> m_PmtTableAux; \
    InterfaceParam<Comp,int> m_BasicPidInfoMain; \
    InterfaceParam<Comp,int> m_BasicPidInfoAux; \
    InterfaceParam<Comp,int> m_AudioInfoMain; \
    InterfaceParam<Comp,int> m_AudioInfoAux; \
    InterfaceParam<Comp,int> m_SubtitlingInfoMain; \
    InterfaceParam<Comp,int> m_SubtitlingInfoAux; \
    InterfaceParam<Comp,int> m_TeletextInfoMain; \
    InterfaceParam<Comp,int> m_TeletextInfoAux; \
    InterfaceParam<Comp,int> m_ComponentTagInfoMain; \
    InterfaceParam<Comp,int> m_ComponentTagInfoAux; \
    InterfaceParam<Comp,int> m_DatabroadcastInfoMain; \
    InterfaceParam<Comp,int> m_DatabroadcastInfoAux; \
    InterfaceParam<Comp,int> m_ReqTableMain; \
    InterfaceParam<Comp,int> m_ReqTableAux; \
    InterfaceParam<Comp,int> m_EitTableMain; \
    InterfaceParam<Comp,int> m_EitTableAux; \
    Comp ## _ ## intf( Comp *parent):m_VcTableMain(parent),m_VcTableAux(parent),m_MgtTableMain(parent),m_MgtTableAux(parent),m_PmtTableMain(parent),m_PmtTableAux(parent),m_BasicPidInfoMain(parent),m_BasicPidInfoAux(parent),m_AudioInfoMain(parent),m_AudioInfoAux(parent),m_SubtitlingInfoMain(parent),m_SubtitlingInfoAux(parent),m_TeletextInfoMain(parent),m_TeletextInfoAux(parent),m_ComponentTagInfoMain(parent),m_ComponentTagInfoAux(parent),m_DatabroadcastInfoMain(parent),m_DatabroadcastInfoAux(parent),m_ReqTableMain(parent),m_ReqTableAux(parent),m_EitTableMain(parent),m_EitTableAux(parent) \
    {\
        m_parent = parent;\
    }\
virtual int VcTableMain(void){ return m_VcTableMain.Call();}\
virtual int VcTableAux(void){ return m_VcTableAux.Call();}\
virtual int MgtTableMain(void){ return m_MgtTableMain.Call();}\
virtual int MgtTableAux(void){ return m_MgtTableAux.Call();}\
virtual int PmtTableMain(void){ return m_PmtTableMain.Call();}\
virtual int PmtTableAux(void){ return m_PmtTableAux.Call();}\
virtual int BasicPidInfoMain(void){ return m_BasicPidInfoMain.Call();}\
virtual int BasicPidInfoAux(void){ return m_BasicPidInfoAux.Call();}\
virtual int AudioInfoMain(void){ return m_AudioInfoMain.Call();}\
virtual int AudioInfoAux(void){ return m_AudioInfoAux.Call();}\
virtual int SubtitlingInfoMain(void){ return m_SubtitlingInfoMain.Call();}\
virtual int SubtitlingInfoAux(void){ return m_SubtitlingInfoAux.Call();}\
virtual int TeletextInfoMain(void){ return m_TeletextInfoMain.Call();}\
virtual int TeletextInfoAux(void){ return m_TeletextInfoAux.Call();}\
virtual int ComponentTagInfoMain(void){ return m_ComponentTagInfoMain.Call();}\
virtual int ComponentTagInfoAux(void){ return m_ComponentTagInfoAux.Call();}\
virtual int DatabroadcastInfoMain(void){ return m_DatabroadcastInfoMain.Call();}\
virtual int DatabroadcastInfoAux(void){ return m_DatabroadcastInfoAux.Call();}\
virtual int ReqTableMain(void){ return m_ReqTableMain.Call();}\
virtual int ReqTableAux(void){ return m_ReqTableAux.Call();}\
virtual int EitTableMain(void){ return m_EitTableMain.Call();}\
virtual int EitTableAux(void){ return m_EitTableAux.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
