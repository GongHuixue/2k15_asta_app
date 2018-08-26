#ifndef IHSVSORTING_H
#define IHSVSORTING_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSorting
{
public:
	virtual ~IHsvSorting(){}
	virtual void Sort(Nat32 PackageIndex)= 0;
};


#define IHsvSortingImpl(Comp,intf)    \
virtual void intf ## _Sort(Nat32 PackageIndex);\
class Comp ## _ ## intf : public IHsvSorting \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Sort(Nat32 PackageIndex){ return m_parent->intf ## _Sort(PackageIndex);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
