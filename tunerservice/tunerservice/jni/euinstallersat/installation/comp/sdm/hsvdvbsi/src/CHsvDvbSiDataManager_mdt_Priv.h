#ifndef  _CHSVDVBSIDATAMANAGER_MDT_PRIV_H
#define  _CHSVDVBSIDATAMANAGER_MDT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <CMwBase.h>
#include <IHsvDateTimeConversion.h>
#include <IDateTime.h>
#include <CS2MwBase.h>
class CHsvDvbSiDataManager_mdt_Priv;
#define CLASSSCOPE CHsvDvbSiDataManager_mdt_Priv::
#include "locals_mdt.h"

class CHsvDvbSiDataManager_mdt_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbSiDataManager_mdt_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mdt.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvDateTimeConversionImpl(CHsvDvbSiDataManager_mdt_Priv,idtconv);
public:
ProvidesInterface<IHsvDateTimeConversion>	idtconv;

//Required interfaces
public:
RequiresInterface<IDateTime>	dt;

public:
CHsvDvbSiDataManager_mdt_Priv():i__idtconv(this)
{
idtconv	=	&i__idtconv;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define dt_iPresent() (dt.Present())
#define dt_Monday	IDateTime_Monday
#define dt_Tuesday	IDateTime_Tuesday
#define dt_Wednesday	IDateTime_Wednesday
#define dt_Thursday	IDateTime_Thursday
#define dt_Friday	IDateTime_Friday
#define dt_Saturday	IDateTime_Saturday
#define dt_Sunday	IDateTime_Sunday
#define dt_Hour	IDateTime_Hour
#define dt_Day	IDateTime_Day
#define dt_DateTimeMin	IDateTime_DateTimeMin
#define dt_DateTimeMax	IDateTime_DateTimeMax
#define dt_OffsetModifiedJulianDate	IDateTime_OffsetModifiedJulianDate
#define dt_DecodeDateTime(datetime,year,month,day,hour,minute,second)	dt->DecodeDateTime(datetime,year,month,day,hour,minute,second)
#define dt_EncodeDateTime(datetime,year,month,day,hour,minute,second)	dt->EncodeDateTime(datetime,year,month,day,hour,minute,second)
#define dt_DecodeDate(date,year,month,day)	dt->DecodeDate(date,year,month,day)
#define dt_EncodeDate(date,year,month,day)	dt->EncodeDate(date,year,month,day)
#define dt_DecodeTime(time,hour,minute,second)	dt->DecodeTime(time,hour,minute,second)
#define dt_EncodeTime(time,hour,minute,second)	dt->EncodeTime(time,hour,minute,second)
#define dt_DayOfWeek(datetime)	dt->DayOfWeek(datetime)
#define dt_DecodeDateTimeBcd(datetime,bcddate,bcdtime)	dt->DecodeDateTimeBcd(datetime,bcddate,bcdtime)
#define dt_EncodeDateTimeBcd(datetime,bcddate,bcdtime)	dt->EncodeDateTimeBcd(datetime,bcddate,bcdtime)
#define dt_DecodeDateBcd(date,bcddate)	dt->DecodeDateBcd(date,bcddate)
#define dt_EncodeDateBcd(date,bcddate)	dt->EncodeDateBcd(date,bcddate)
#define dt_DecodeTimeBcd(time,bcdtime)	dt->DecodeTimeBcd(time,bcdtime)
#define dt_EncodeTimeBcd(time,bcdtime)	dt->EncodeTimeBcd(time,bcdtime)
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mdt.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

