#ifndef IHSVALTFREQUENCYITERATOR_H
#define IHSVALTFREQUENCYITERATOR_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAltFrequencyIterator
{
public:
	virtual ~IHsvAltFrequencyIterator(){}
	#define IHsvAltFrequencyIterator_InvalidFrequency		((Nat32)0 )
	virtual int GetNoOfAltFrequencies(Nat16 OnId,Nat16 TsId)= 0;
	virtual Nat32 GetFirstAltFrequency(Nat16 OnId,Nat16 TsId)= 0;
	virtual Nat32 GetNextAltFrequency(Nat16 OnId,Nat16 TsId,Nat32 Freq)= 0;
	virtual Nat32 GetPreviousAltFrequency(Nat16 OnId,Nat16 TsId,Nat32 Freq)= 0;
	virtual Nat32 GetLastAltFrequency(Nat16 OnId,Nat16 TsId)= 0;
	virtual Bool IsNetworkUpdateDetected(void)= 0;
};


#define IHsvAltFrequencyIteratorImpl(Comp,intf)    \
virtual int intf ## _GetNoOfAltFrequencies(Nat16 OnId,Nat16 TsId);\
virtual Nat32 intf ## _GetFirstAltFrequency(Nat16 OnId,Nat16 TsId);\
virtual Nat32 intf ## _GetNextAltFrequency(Nat16 OnId,Nat16 TsId,Nat32 Freq);\
virtual Nat32 intf ## _GetPreviousAltFrequency(Nat16 OnId,Nat16 TsId,Nat32 Freq);\
virtual Nat32 intf ## _GetLastAltFrequency(Nat16 OnId,Nat16 TsId);\
virtual Bool intf ## _IsNetworkUpdateDetected(void);\
class Comp ## _ ## intf : public IHsvAltFrequencyIterator \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetNoOfAltFrequencies(Nat16 OnId,Nat16 TsId){ return m_parent->intf ## _GetNoOfAltFrequencies(OnId,TsId);}\
virtual Nat32 GetFirstAltFrequency(Nat16 OnId,Nat16 TsId){ return m_parent->intf ## _GetFirstAltFrequency(OnId,TsId);}\
virtual Nat32 GetNextAltFrequency(Nat16 OnId,Nat16 TsId,Nat32 Freq){ return m_parent->intf ## _GetNextAltFrequency(OnId,TsId,Freq);}\
virtual Nat32 GetPreviousAltFrequency(Nat16 OnId,Nat16 TsId,Nat32 Freq){ return m_parent->intf ## _GetPreviousAltFrequency(OnId,TsId,Freq);}\
virtual Nat32 GetLastAltFrequency(Nat16 OnId,Nat16 TsId){ return m_parent->intf ## _GetLastAltFrequency(OnId,TsId);}\
virtual Bool IsNetworkUpdateDetected(void){ return m_parent->intf ## _IsNetworkUpdateDetected();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
