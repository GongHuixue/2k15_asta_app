#ifndef IHSVDATETIMECONVERSION_H
#define IHSVDATETIMECONVERSION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDateTimeConversion
{
public:
	virtual ~IHsvDateTimeConversion(){}
	virtual void DecodeMJD(Nat16 date,int * year,int * month,int * day)= 0;
	virtual void EncodeDataTime(Nat16 Date,Nat32 Time,DateTime * dt)= 0;
};


#define IHsvDateTimeConversionImpl(Comp,intf)    \
virtual void intf ## _DecodeMJD(Nat16 date,int * year,int * month,int * day);\
virtual void intf ## _EncodeDataTime(Nat16 Date,Nat32 Time,DateTime * dt);\
class Comp ## _ ## intf : public IHsvDateTimeConversion \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void DecodeMJD(Nat16 date,int * year,int * month,int * day){ return m_parent->intf ## _DecodeMJD(date,year,month,day);}\
virtual void EncodeDataTime(Nat16 Date,Nat32 Time,DateTime * dt){ return m_parent->intf ## _EncodeDataTime(Date,Time,dt);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
