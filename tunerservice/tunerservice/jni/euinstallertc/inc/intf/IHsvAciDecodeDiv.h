#ifndef IHSVACIDECODEDIV_H
#define IHSVACIDECODEDIV_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAciDecodeDiv
{
public:
	virtual ~IHsvAciDecodeDiv(){}
	virtual Bool PrefetchAciPage(void)= 0;
	virtual Nat8 PresetNameLength(void)= 0;
	virtual int AciDispStartRow(void)= 0;
	virtual int AciDispStartCol(void)= 0;
	virtual int AciDispEndRow(void)= 0;
	virtual int AciDispEndCol(void)= 0;
	virtual int AciRowHeight(void)= 0;
};


#define IHsvAciDecodeDivImpl(Comp,intf)    \
friend class InterfaceParam<Comp,Bool>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvAciDecodeDiv \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,Bool> m_PrefetchAciPage; \
    InterfaceParam<Comp,Nat8> m_PresetNameLength; \
    InterfaceParam<Comp,int> m_AciDispStartRow; \
    InterfaceParam<Comp,int> m_AciDispStartCol; \
    InterfaceParam<Comp,int> m_AciDispEndRow; \
    InterfaceParam<Comp,int> m_AciDispEndCol; \
    InterfaceParam<Comp,int> m_AciRowHeight; \
    Comp ## _ ## intf( Comp *parent):m_PrefetchAciPage(parent),m_PresetNameLength(parent),m_AciDispStartRow(parent),m_AciDispStartCol(parent),m_AciDispEndRow(parent),m_AciDispEndCol(parent),m_AciRowHeight(parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool PrefetchAciPage(void){ return m_PrefetchAciPage.Call();}\
virtual Nat8 PresetNameLength(void){ return m_PresetNameLength.Call();}\
virtual int AciDispStartRow(void){ return m_AciDispStartRow.Call();}\
virtual int AciDispStartCol(void){ return m_AciDispStartCol.Call();}\
virtual int AciDispEndRow(void){ return m_AciDispEndRow.Call();}\
virtual int AciDispEndCol(void){ return m_AciDispEndCol.Call();}\
virtual int AciRowHeight(void){ return m_AciRowHeight.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
