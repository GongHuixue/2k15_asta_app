#ifndef IHSVDEMUXSECTIONFILTER2_H
#define IHSVDEMUXSECTIONFILTER2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDemuxSectionFilter2
{
public:
	virtual ~IHsvDemuxSectionFilter2(){}
	#define IHsvDemuxSectionFilter2_SctArrived		((int)0x1 )
	#define IHsvDemuxSectionFilter2_TableCompleted		((int)0x2 )
	virtual int SectionDepth(void)= 0;
	virtual Bool IsRequestAllowed(HsvDestination dest)= 0;
	virtual Nat32 RequestSection(HsvDestination dest,int pid,int tableid,int cookie,HsvSectionCallback sctCallback)= 0;
	virtual Nat32 RequestSection2(HsvDestination dest,int pid,int tableid,Nat16 tableidextn,int cookie,HsvSectionCallback sctCallback)= 0;
	virtual Nat32 RequestSection3(HsvDestination dest,int pid,int tableid,Nat16 tableidextn,Nat16 tableidextn2,int cookie,HsvSectionCallback sctCallback)= 0;
	virtual void ResetRequest(HsvDestination dest,Nat32 subscrId)= 0;
	virtual Bool CancelSection(HsvDestination dest,Nat32 subscrId)= 0;
	virtual Nat32 RequestPes(HsvDestination dest,int pid,int cookie,HsvPesCallback pesCallback)= 0;
	virtual Bool CancelPes(HsvDestination dest,Nat32 subscrId)= 0;
	virtual Nat32 RequestSectionFilter(HsvDestination dest,HsvSectionFilterConfig * sctconfig,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,HsvSectionFilterCallback sctCallback)= 0;
	virtual Bool UpdateFilter(HsvDestination dest,Nat32 subscrId,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray)= 0;
	virtual Nat32 RequestSectionFilterList(HsvDestination dest,HsvSectionFilterListConfig * sctconfig,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,HsvSectionFilterCallback sctCallback)= 0;
	virtual Nat32 RequestPesList(HsvDestination dest,int pid,int cookie,HsvPesCallback pesCallback,int TimeOut,int ListLength)= 0;
	virtual Nat32 GetBits(Nat32 sectionid,int numbits)= 0;
	virtual Nat32 ShowBits(Nat32 sectionid,int numbits)= 0;
	virtual void SkipBits(Nat32 sectionid,int numbits)= 0;
	virtual void AlignToNextByte(Nat32 sectionid)= 0;
	virtual Bool IsEndOfSection(Nat32 sectionid)= 0;
	virtual Nat32 GetBitsRead(Nat32 sectionid)= 0;
	virtual Nat32 GetBitsUnread(Nat32 sectionid)= 0;
	virtual void* GetSectionBuffer(Nat32 sectionid)= 0;
	virtual int GetSectionLength(Nat32 sectionid)= 0;
	virtual void CheckandCancelSection(HsvDestination dest,int PidValue)= 0;
};


#define IHsvDemuxSectionFilter2Impl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
virtual Bool intf ## _IsRequestAllowed(HsvDestination dest);\
virtual Nat32 intf ## _RequestSection(HsvDestination dest,int pid,int tableid,int cookie,HsvSectionCallback sctCallback);\
virtual Nat32 intf ## _RequestSection2(HsvDestination dest,int pid,int tableid,Nat16 tableidextn,int cookie,HsvSectionCallback sctCallback);\
virtual Nat32 intf ## _RequestSection3(HsvDestination dest,int pid,int tableid,Nat16 tableidextn,Nat16 tableidextn2,int cookie,HsvSectionCallback sctCallback);\
virtual void intf ## _ResetRequest(HsvDestination dest,Nat32 subscrId);\
virtual Bool intf ## _CancelSection(HsvDestination dest,Nat32 subscrId);\
virtual Nat32 intf ## _RequestPes(HsvDestination dest,int pid,int cookie,HsvPesCallback pesCallback);\
virtual Bool intf ## _CancelPes(HsvDestination dest,Nat32 subscrId);\
virtual Nat32 intf ## _RequestSectionFilter(HsvDestination dest,HsvSectionFilterConfig * sctconfig,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,HsvSectionFilterCallback sctCallback);\
virtual Bool intf ## _UpdateFilter(HsvDestination dest,Nat32 subscrId,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray);\
virtual Nat32 intf ## _RequestSectionFilterList(HsvDestination dest,HsvSectionFilterListConfig * sctconfig,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,HsvSectionFilterCallback sctCallback);\
virtual Nat32 intf ## _RequestPesList(HsvDestination dest,int pid,int cookie,HsvPesCallback pesCallback,int TimeOut,int ListLength);\
virtual Nat32 intf ## _GetBits(Nat32 sectionid,int numbits);\
virtual Nat32 intf ## _ShowBits(Nat32 sectionid,int numbits);\
virtual void intf ## _SkipBits(Nat32 sectionid,int numbits);\
virtual void intf ## _AlignToNextByte(Nat32 sectionid);\
virtual Bool intf ## _IsEndOfSection(Nat32 sectionid);\
virtual Nat32 intf ## _GetBitsRead(Nat32 sectionid);\
virtual Nat32 intf ## _GetBitsUnread(Nat32 sectionid);\
virtual void* intf ## _GetSectionBuffer(Nat32 sectionid);\
virtual int intf ## _GetSectionLength(Nat32 sectionid);\
virtual void intf ## _CheckandCancelSection(HsvDestination dest,int PidValue);\
class Comp ## _ ## intf : public IHsvDemuxSectionFilter2 \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_SectionDepth; \
    Comp ## _ ## intf( Comp *parent):m_SectionDepth(parent) \
    {\
        m_parent = parent;\
    }\
virtual int SectionDepth(void){ return m_SectionDepth.Call();}\
virtual Bool IsRequestAllowed(HsvDestination dest){ return m_parent->intf ## _IsRequestAllowed(dest);}\
virtual Nat32 RequestSection(HsvDestination dest,int pid,int tableid,int cookie,HsvSectionCallback sctCallback){ return m_parent->intf ## _RequestSection(dest,pid,tableid,cookie,sctCallback);}\
virtual Nat32 RequestSection2(HsvDestination dest,int pid,int tableid,Nat16 tableidextn,int cookie,HsvSectionCallback sctCallback){ return m_parent->intf ## _RequestSection2(dest,pid,tableid,tableidextn,cookie,sctCallback);}\
virtual Nat32 RequestSection3(HsvDestination dest,int pid,int tableid,Nat16 tableidextn,Nat16 tableidextn2,int cookie,HsvSectionCallback sctCallback){ return m_parent->intf ## _RequestSection3(dest,pid,tableid,tableidextn,tableidextn2,cookie,sctCallback);}\
virtual void ResetRequest(HsvDestination dest,Nat32 subscrId){ return m_parent->intf ## _ResetRequest(dest,subscrId);}\
virtual Bool CancelSection(HsvDestination dest,Nat32 subscrId){ return m_parent->intf ## _CancelSection(dest,subscrId);}\
virtual Nat32 RequestPes(HsvDestination dest,int pid,int cookie,HsvPesCallback pesCallback){ return m_parent->intf ## _RequestPes(dest,pid,cookie,pesCallback);}\
virtual Bool CancelPes(HsvDestination dest,Nat32 subscrId){ return m_parent->intf ## _CancelPes(dest,subscrId);}\
virtual Nat32 RequestSectionFilter(HsvDestination dest,HsvSectionFilterConfig * sctconfig,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,HsvSectionFilterCallback sctCallback){ return m_parent->intf ## _RequestSectionFilter(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback);}\
virtual Bool UpdateFilter(HsvDestination dest,Nat32 subscrId,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray){ return m_parent->intf ## _UpdateFilter(dest,subscrId,pFilterDepth,ModeArray,MatchArray,MaskArray);}\
virtual Nat32 RequestSectionFilterList(HsvDestination dest,HsvSectionFilterListConfig * sctconfig,int pFilterDepth,Nat8 * ModeArray,Nat8 * MatchArray,Nat8 * MaskArray,HsvSectionFilterCallback sctCallback){ return m_parent->intf ## _RequestSectionFilterList(dest,sctconfig,pFilterDepth,ModeArray,MatchArray,MaskArray,sctCallback);}\
virtual Nat32 RequestPesList(HsvDestination dest,int pid,int cookie,HsvPesCallback pesCallback,int TimeOut,int ListLength){ return m_parent->intf ## _RequestPesList(dest,pid,cookie,pesCallback,TimeOut,ListLength);}\
virtual Nat32 GetBits(Nat32 sectionid,int numbits){ return m_parent->intf ## _GetBits(sectionid,numbits);}\
virtual Nat32 ShowBits(Nat32 sectionid,int numbits){ return m_parent->intf ## _ShowBits(sectionid,numbits);}\
virtual void SkipBits(Nat32 sectionid,int numbits){ return m_parent->intf ## _SkipBits(sectionid,numbits);}\
virtual void AlignToNextByte(Nat32 sectionid){ return m_parent->intf ## _AlignToNextByte(sectionid);}\
virtual Bool IsEndOfSection(Nat32 sectionid){ return m_parent->intf ## _IsEndOfSection(sectionid);}\
virtual Nat32 GetBitsRead(Nat32 sectionid){ return m_parent->intf ## _GetBitsRead(sectionid);}\
virtual Nat32 GetBitsUnread(Nat32 sectionid){ return m_parent->intf ## _GetBitsUnread(sectionid);}\
virtual void* GetSectionBuffer(Nat32 sectionid){ return m_parent->intf ## _GetSectionBuffer(sectionid);}\
virtual int GetSectionLength(Nat32 sectionid){ return m_parent->intf ## _GetSectionLength(sectionid);}\
virtual void CheckandCancelSection(HsvDestination dest,int PidValue){ return m_parent->intf ## _CheckandCancelSection(dest,PidValue);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
