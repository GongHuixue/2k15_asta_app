#ifndef IHSVSATELLITEUTILITY_H
#define IHSVSATELLITEUTILITY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatelliteUtility
{
public:
	virtual ~IHsvSatelliteUtility(){}
	virtual void ResetData(void)= 0;
	virtual Bool CheckFreqDuplicationwithRolFact(Nat32 Newfreq,Nat32 Oldfreq,Nat32 SymbolRate)= 0;
	virtual void AddEntryToList(FrequencyDataList * Entry)= 0;
	virtual Bool IsDuplicate(FrequencyDataList * Entry)= 0;
	virtual Bool ReadBarkerMuxData(HsvBarkerMuxData * Data)= 0;
	virtual Bool WriteBarkerMuxData(HsvBarkerMuxData Data)= 0;
	virtual void ResetBarkerMuxData(void)= 0;
};


#define IHsvSatelliteUtilityImpl(Comp,intf)    \
virtual void intf ## _ResetData(void);\
virtual Bool intf ## _CheckFreqDuplicationwithRolFact(Nat32 Newfreq,Nat32 Oldfreq,Nat32 SymbolRate);\
virtual void intf ## _AddEntryToList(FrequencyDataList * Entry);\
virtual Bool intf ## _IsDuplicate(FrequencyDataList * Entry);\
virtual Bool intf ## _ReadBarkerMuxData(HsvBarkerMuxData * Data);\
virtual Bool intf ## _WriteBarkerMuxData(HsvBarkerMuxData Data);\
virtual void intf ## _ResetBarkerMuxData(void);\
class Comp ## _ ## intf : public IHsvSatelliteUtility \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void ResetData(void){ return m_parent->intf ## _ResetData();}\
virtual Bool CheckFreqDuplicationwithRolFact(Nat32 Newfreq,Nat32 Oldfreq,Nat32 SymbolRate){ return m_parent->intf ## _CheckFreqDuplicationwithRolFact(Newfreq,Oldfreq,SymbolRate);}\
virtual void AddEntryToList(FrequencyDataList * Entry){ return m_parent->intf ## _AddEntryToList(Entry);}\
virtual Bool IsDuplicate(FrequencyDataList * Entry){ return m_parent->intf ## _IsDuplicate(Entry);}\
virtual Bool ReadBarkerMuxData(HsvBarkerMuxData * Data){ return m_parent->intf ## _ReadBarkerMuxData(Data);}\
virtual Bool WriteBarkerMuxData(HsvBarkerMuxData Data){ return m_parent->intf ## _WriteBarkerMuxData(Data);}\
virtual void ResetBarkerMuxData(void){ return m_parent->intf ## _ResetBarkerMuxData();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
