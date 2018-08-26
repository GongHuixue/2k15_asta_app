#ifndef IHSVPRESETSORT_H
#define IHSVPRESETSORT_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPresetSort
{
public:
	virtual ~IHsvPresetSort(){}
	virtual int Sort(HsvPresetSortData * listOfPresetData,int sizeOfList,int numPresets)= 0;
	virtual int GetPresetIndex(int presetNo)= 0;
	virtual Nat8* GetPresetIndexList(int * sizeOfList)= 0;
};


#define IHsvPresetSortImpl(Comp,intf)    \
virtual int intf ## _Sort(HsvPresetSortData * listOfPresetData,int sizeOfList,int numPresets);\
virtual int intf ## _GetPresetIndex(int presetNo);\
virtual Nat8* intf ## _GetPresetIndexList(int * sizeOfList);\
class Comp ## _ ## intf : public IHsvPresetSort \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int Sort(HsvPresetSortData * listOfPresetData,int sizeOfList,int numPresets){ return m_parent->intf ## _Sort(listOfPresetData,sizeOfList,numPresets);}\
virtual int GetPresetIndex(int presetNo){ return m_parent->intf ## _GetPresetIndex(presetNo);}\
virtual Nat8* GetPresetIndexList(int * sizeOfList){ return m_parent->intf ## _GetPresetIndexList(sizeOfList);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
