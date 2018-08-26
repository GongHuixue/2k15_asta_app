#ifndef IHSVCONFLICTS_H
#define IHSVCONFLICTS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvConflicts
{
public:
	virtual ~IHsvConflicts(){}
	virtual void SetUserSelectConflictService(int LcnIndex,int SvcIndex)= 0;
	virtual void ConflictsSelectionDone(Bool UserSelection)= 0;
	virtual void ResolveConflicts(int ConflictPass)= 0;
	virtual void GetConflictServices(HsvConflictServicesData * ConflictList,int * NumRecords)= 0;
	virtual void AssignRegionAttributesForService(void)= 0;
};


#define IHsvConflictsImpl(Comp,intf)    \
virtual void intf ## _SetUserSelectConflictService(int LcnIndex,int SvcIndex);\
virtual void intf ## _ConflictsSelectionDone(Bool UserSelection);\
virtual void intf ## _ResolveConflicts(int ConflictPass);\
virtual void intf ## _GetConflictServices(HsvConflictServicesData * ConflictList,int * NumRecords);\
virtual void intf ## _AssignRegionAttributesForService(void);\
class Comp ## _ ## intf : public IHsvConflicts \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SetUserSelectConflictService(int LcnIndex,int SvcIndex){ return m_parent->intf ## _SetUserSelectConflictService(LcnIndex,SvcIndex);}\
virtual void ConflictsSelectionDone(Bool UserSelection){ return m_parent->intf ## _ConflictsSelectionDone(UserSelection);}\
virtual void ResolveConflicts(int ConflictPass){ return m_parent->intf ## _ResolveConflicts(ConflictPass);}\
virtual void GetConflictServices(HsvConflictServicesData * ConflictList,int * NumRecords){ return m_parent->intf ## _GetConflictServices(ConflictList,NumRecords);}\
virtual void AssignRegionAttributesForService(void){ return m_parent->intf ## _AssignRegionAttributesForService();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
