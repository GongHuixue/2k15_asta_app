#ifndef IPRODAPICLOCKEX_H
#define IPRODAPICLOCKEX_H
#include <intfparam.h>
#include <provreq.h>
class IProdApiClockEx
{
public:
	virtual ~IProdApiClockEx(){}
	#define IProdApiClockEx_ClocksourceManual		((int)0x01 )
	#define IProdApiClockEx_ClocksourceTOT		((int)0x02 )
	#define IProdApiClockEx_ClocksourceECD		((int)0x04 )
	#define IProdApiClockEx_ClocksourceTXT		((int)0x08 )
	#define IProdApiClockEx_ClocksourceTDT		((int)0x10 )
	#define IProdApiClockEx_ClocksourceTOTDVBS		((int)0x20 )
	#define IProdApiClockEx_ClocksourceTDTDVBS		((int)0x40 )
	#define IProdApiClockEx_InvalidClock		((DateTime)0xFFFFFFFF )
	virtual void SetTime(DateTime utc,DateTime lto,int source)= 0;
	virtual void SetUniversalTime(DateTime utc,int source)= 0;
	virtual void SetLocalTime(DateTime time,int source)= 0;
	virtual DateTime GetUniversalTime(void)= 0;
	virtual DateTime GetLocalTimeOffset(void)= 0;
	virtual DateTime GetLocalTime(void)= 0;
	virtual void SetNextLTOChange(DateTime timeOfChange,int nextLTO,int source)= 0;
	virtual void GetAbsoluteLocalTime(DateTime Utc,DateTime * localTime)= 0;
	virtual void GetAbsoluteUTC(DateTime localTime,DateTime * Utc)= 0;
	#define IProdApiClockEx_TimeZoneNone		((int)0 )
	#define IProdApiClockEx_TimeZoneBaleares		((int)1 )
	#define IProdApiClockEx_TimeZoneCanaryIsland		((int)2 )
	#define IProdApiClockEx_TimeZoneContinental		((int)3 )
	#define IProdApiClockEx_TimeZoneAzores		((int)4 )
	#define IProdApiClockEx_TimeZoneKalingrad		((int)5 )
	#define IProdApiClockEx_TimeZoneMoscow		((int)6 )
	#define IProdApiClockEx_TimeZoneSamara		((int)7 )
	#define IProdApiClockEx_TimeZoneYekaterinburg		((int)8 )
	#define IProdApiClockEx_TimeZoneOmsk		((int)9 )
	#define IProdApiClockEx_TimeZoneKrasnoyarsk		((int)10 )
	#define IProdApiClockEx_TimeZoneIrkutsk		((int)11 )
	#define IProdApiClockEx_TimeZoneYakutsk		((int)12 )
	#define IProdApiClockEx_TimeZoneVladivostok		((int)13 )
	#define IProdApiClockEx_TimeZoneMagadan		((int)14 )
	#define IProdApiClockEx_TimeZoneKamchatka		((int)15 )
	virtual void SetUserTimeZone(int timezone)= 0;
	virtual int GetUserTimeZone(void)= 0;
	virtual int GetTimeZone(void)= 0;
	#define IProdApiClockEx_DstAuto		((int)1 )
	#define IProdApiClockEx_DstOn		((int)2 )
	#define IProdApiClockEx_DstOff		((int)3 )
	virtual Bool IsDstActive(void)= 0;
	virtual void SetUserDst(int dst)= 0;
	virtual int GetUserDst(void)= 0;
	#define IProdApiClockEx_LtoModeAutomatic		((int)0x00 )
	#define IProdApiClockEx_LtoModeCountryDependent		((int)0x01 )
	virtual void SetLtoMode(int ltomode)= 0;
	virtual int GetLtoMode(void)= 0;
	virtual Bool IsClockManual(void)= 0;
	virtual Bool IsClockDefined(void)= 0;
};


#define IProdApiClockExImpl(Comp,intf)    \
virtual void intf ## _SetTime(DateTime utc,DateTime lto,int source);\
virtual void intf ## _SetUniversalTime(DateTime utc,int source);\
virtual void intf ## _SetLocalTime(DateTime time,int source);\
virtual DateTime intf ## _GetUniversalTime(void);\
virtual DateTime intf ## _GetLocalTimeOffset(void);\
virtual DateTime intf ## _GetLocalTime(void);\
virtual void intf ## _SetNextLTOChange(DateTime timeOfChange,int nextLTO,int source);\
virtual void intf ## _GetAbsoluteLocalTime(DateTime Utc,DateTime * localTime);\
virtual void intf ## _GetAbsoluteUTC(DateTime localTime,DateTime * Utc);\
virtual void intf ## _SetUserTimeZone(int timezone);\
virtual int intf ## _GetUserTimeZone(void);\
virtual int intf ## _GetTimeZone(void);\
virtual Bool intf ## _IsDstActive(void);\
virtual void intf ## _SetUserDst(int dst);\
virtual int intf ## _GetUserDst(void);\
virtual void intf ## _SetLtoMode(int ltomode);\
virtual int intf ## _GetLtoMode(void);\
virtual Bool intf ## _IsClockManual(void);\
virtual Bool intf ## _IsClockDefined(void);\
class Comp ## _ ## intf : public IProdApiClockEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SetTime(DateTime utc,DateTime lto,int source){ return m_parent->intf ## _SetTime(utc,lto,source);}\
virtual void SetUniversalTime(DateTime utc,int source){ return m_parent->intf ## _SetUniversalTime(utc,source);}\
virtual void SetLocalTime(DateTime time,int source){ return m_parent->intf ## _SetLocalTime(time,source);}\
virtual DateTime GetUniversalTime(void){ return m_parent->intf ## _GetUniversalTime();}\
virtual DateTime GetLocalTimeOffset(void){ return m_parent->intf ## _GetLocalTimeOffset();}\
virtual DateTime GetLocalTime(void){ return m_parent->intf ## _GetLocalTime();}\
virtual void SetNextLTOChange(DateTime timeOfChange,int nextLTO,int source){ return m_parent->intf ## _SetNextLTOChange(timeOfChange,nextLTO,source);}\
virtual void GetAbsoluteLocalTime(DateTime Utc,DateTime * localTime){ return m_parent->intf ## _GetAbsoluteLocalTime(Utc,localTime);}\
virtual void GetAbsoluteUTC(DateTime localTime,DateTime * Utc){ return m_parent->intf ## _GetAbsoluteUTC(localTime,Utc);}\
virtual void SetUserTimeZone(int timezone){ return m_parent->intf ## _SetUserTimeZone(timezone);}\
virtual int GetUserTimeZone(void){ return m_parent->intf ## _GetUserTimeZone();}\
virtual int GetTimeZone(void){ return m_parent->intf ## _GetTimeZone();}\
virtual Bool IsDstActive(void){ return m_parent->intf ## _IsDstActive();}\
virtual void SetUserDst(int dst){ return m_parent->intf ## _SetUserDst(dst);}\
virtual int GetUserDst(void){ return m_parent->intf ## _GetUserDst();}\
virtual void SetLtoMode(int ltomode){ return m_parent->intf ## _SetLtoMode(ltomode);}\
virtual int GetLtoMode(void){ return m_parent->intf ## _GetLtoMode();}\
virtual Bool IsClockManual(void){ return m_parent->intf ## _IsClockManual();}\
virtual Bool IsClockDefined(void){ return m_parent->intf ## _IsClockDefined();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
