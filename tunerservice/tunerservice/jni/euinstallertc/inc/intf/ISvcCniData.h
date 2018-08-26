#ifndef ISVCCNIDATA_H
#define ISVCCNIDATA_H
#include <intfparam.h>
#include <provreq.h>
class ISvcCniData
{
public:
	virtual ~ISvcCniData(){}
	virtual Bool Add(Nat16 cni,int presetId)= 0;
	virtual Bool Remove(int presetId)= 0;
	virtual Bool IsCniPresent(Nat16 cni)= 0;
	virtual int GetPreset(Nat16 cni)= 0;
	virtual Nat16 GetCni(int pr)= 0;
	virtual void ClearCNIList(void)= 0;
	#define ISvcCniData_InvalidPreset		((int)- 1 )
	virtual int MinCNIPreset(void)= 0;
	virtual int MaxCNIPreset(void)= 0;
};


#define ISvcCniDataImpl(Comp,intf)    \
virtual Bool intf ## _Add(Nat16 cni,int presetId);\
virtual Bool intf ## _Remove(int presetId);\
virtual Bool intf ## _IsCniPresent(Nat16 cni);\
virtual int intf ## _GetPreset(Nat16 cni);\
virtual Nat16 intf ## _GetCni(int pr);\
virtual void intf ## _ClearCNIList(void);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public ISvcCniData \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_MinCNIPreset; \
    InterfaceParam<Comp,int> m_MaxCNIPreset; \
    Comp ## _ ## intf( Comp *parent):m_MinCNIPreset(parent),m_MaxCNIPreset(parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool Add(Nat16 cni,int presetId){ return m_parent->intf ## _Add(cni,presetId);}\
virtual Bool Remove(int presetId){ return m_parent->intf ## _Remove(presetId);}\
virtual Bool IsCniPresent(Nat16 cni){ return m_parent->intf ## _IsCniPresent(cni);}\
virtual int GetPreset(Nat16 cni){ return m_parent->intf ## _GetPreset(cni);}\
virtual Nat16 GetCni(int pr){ return m_parent->intf ## _GetCni(pr);}\
virtual void ClearCNIList(void){ return m_parent->intf ## _ClearCNIList();}\
virtual int MinCNIPreset(void){ return m_MinCNIPreset.Call();}\
virtual int MaxCNIPreset(void){ return m_MaxCNIPreset.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
