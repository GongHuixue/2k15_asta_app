#ifndef IDATETIME_H
#define IDATETIME_H
#include <intfparam.h>
#include <provreq.h>
class IDateTime
{
public:
	virtual ~IDateTime(){}
	#define IDateTime_Monday		((int)0 )
	#define IDateTime_Tuesday		((int)1 )
	#define IDateTime_Wednesday		((int)2 )
	#define IDateTime_Thursday		((int)3 )
	#define IDateTime_Friday		((int)4 )
	#define IDateTime_Saturday		((int)5 )
	#define IDateTime_Sunday		((int)6 )
	#define IDateTime_Hour		((DateTime)3600 )
	#define IDateTime_Day		((DateTime)86400 )
	#define IDateTime_DateTimeMin		((DateTime)0 )
	#define IDateTime_DateTimeMax		((DateTime)2147483647 )
	#define IDateTime_OffsetModifiedJulianDate		((Int32)50083 )
	virtual void DecodeDateTime(DateTime datetime,int * year,int * month,int * day,int * hour,int * minute,int * second)= 0;
	virtual Bool EncodeDateTime(DateTime * datetime,int year,int month,int day,int hour,int minute,int second)= 0;
	virtual void DecodeDate(DateTime date,int * year,int * month,int * day)= 0;
	virtual Bool EncodeDate(DateTime * date,int year,int month,int day)= 0;
	virtual void DecodeTime(DateTime time,int * hour,int * minute,int * second)= 0;
	virtual Bool EncodeTime(DateTime * time,int hour,int minute,int second)= 0;
	virtual int DayOfWeek(DateTime datetime)= 0;
	virtual void DecodeDateTimeBcd(DateTime datetime,Nat32 * bcddate,Nat32 * bcdtime)= 0;
	virtual Bool EncodeDateTimeBcd(DateTime * datetime,Nat32 bcddate,Nat32 bcdtime)= 0;
	virtual void DecodeDateBcd(DateTime date,Nat32 * bcddate)= 0;
	virtual Bool EncodeDateBcd(DateTime * date,Nat32 bcddate)= 0;
	virtual void DecodeTimeBcd(DateTime time,Nat32 * bcdtime)= 0;
	virtual Bool EncodeTimeBcd(DateTime * time,Nat32 bcdtime)= 0;
};


#define IDateTimeImpl(Comp,intf)    \
virtual void intf ## _DecodeDateTime(DateTime datetime,int * year,int * month,int * day,int * hour,int * minute,int * second);\
virtual Bool intf ## _EncodeDateTime(DateTime * datetime,int year,int month,int day,int hour,int minute,int second);\
virtual void intf ## _DecodeDate(DateTime date,int * year,int * month,int * day);\
virtual Bool intf ## _EncodeDate(DateTime * date,int year,int month,int day);\
virtual void intf ## _DecodeTime(DateTime time,int * hour,int * minute,int * second);\
virtual Bool intf ## _EncodeTime(DateTime * time,int hour,int minute,int second);\
virtual int intf ## _DayOfWeek(DateTime datetime);\
virtual void intf ## _DecodeDateTimeBcd(DateTime datetime,Nat32 * bcddate,Nat32 * bcdtime);\
virtual Bool intf ## _EncodeDateTimeBcd(DateTime * datetime,Nat32 bcddate,Nat32 bcdtime);\
virtual void intf ## _DecodeDateBcd(DateTime date,Nat32 * bcddate);\
virtual Bool intf ## _EncodeDateBcd(DateTime * date,Nat32 bcddate);\
virtual void intf ## _DecodeTimeBcd(DateTime time,Nat32 * bcdtime);\
virtual Bool intf ## _EncodeTimeBcd(DateTime * time,Nat32 bcdtime);\
class Comp ## _ ## intf : public IDateTime \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void DecodeDateTime(DateTime datetime,int * year,int * month,int * day,int * hour,int * minute,int * second){ return m_parent->intf ## _DecodeDateTime(datetime,year,month,day,hour,minute,second);}\
virtual Bool EncodeDateTime(DateTime * datetime,int year,int month,int day,int hour,int minute,int second){ return m_parent->intf ## _EncodeDateTime(datetime,year,month,day,hour,minute,second);}\
virtual void DecodeDate(DateTime date,int * year,int * month,int * day){ return m_parent->intf ## _DecodeDate(date,year,month,day);}\
virtual Bool EncodeDate(DateTime * date,int year,int month,int day){ return m_parent->intf ## _EncodeDate(date,year,month,day);}\
virtual void DecodeTime(DateTime time,int * hour,int * minute,int * second){ return m_parent->intf ## _DecodeTime(time,hour,minute,second);}\
virtual Bool EncodeTime(DateTime * time,int hour,int minute,int second){ return m_parent->intf ## _EncodeTime(time,hour,minute,second);}\
virtual int DayOfWeek(DateTime datetime){ return m_parent->intf ## _DayOfWeek(datetime);}\
virtual void DecodeDateTimeBcd(DateTime datetime,Nat32 * bcddate,Nat32 * bcdtime){ return m_parent->intf ## _DecodeDateTimeBcd(datetime,bcddate,bcdtime);}\
virtual Bool EncodeDateTimeBcd(DateTime * datetime,Nat32 bcddate,Nat32 bcdtime){ return m_parent->intf ## _EncodeDateTimeBcd(datetime,bcddate,bcdtime);}\
virtual void DecodeDateBcd(DateTime date,Nat32 * bcddate){ return m_parent->intf ## _DecodeDateBcd(date,bcddate);}\
virtual Bool EncodeDateBcd(DateTime * date,Nat32 bcddate){ return m_parent->intf ## _EncodeDateBcd(date,bcddate);}\
virtual void DecodeTimeBcd(DateTime time,Nat32 * bcdtime){ return m_parent->intf ## _DecodeTimeBcd(time,bcdtime);}\
virtual Bool EncodeTimeBcd(DateTime * time,Nat32 bcdtime){ return m_parent->intf ## _EncodeTimeBcd(time,bcdtime);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
