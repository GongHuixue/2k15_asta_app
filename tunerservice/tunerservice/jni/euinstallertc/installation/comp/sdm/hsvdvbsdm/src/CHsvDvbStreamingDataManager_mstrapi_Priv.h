#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_MSTRAPI_PRIV_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_MSTRAPI_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvStreamNotify.h>
#include <IHsvStream.h>
#include <CTCMwBase.h>
class CHsvDvbStreamingDataManager_mstrapi_Priv;
#define CLASSSCOPE CHsvDvbStreamingDataManager_mstrapi_Priv::
#include "locals_mstrapi.h"

class CHsvDvbStreamingDataManager_mstrapi_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbStreamingDataManager_mstrapi_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mstrapi.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvStreamNotifyImpl(CHsvDvbStreamingDataManager_mstrapi_Priv,hsvdvbcamsdm_strapiN);
IHsvStreamNotifyImpl(CHsvDvbStreamingDataManager_mstrapi_Priv,hsvdvbsi_strapiN);
IHsvStreamNotifyImpl(CHsvDvbStreamingDataManager_mstrapi_Priv,hsvmpeg_strapiN);
IHsvStreamImpl(CHsvDvbStreamingDataManager_mstrapi_Priv,istrapi);
public:
ProvidesInterface<IHsvStreamNotify>	hsvdvbcamsdm_strapiN;
ProvidesInterface<IHsvStreamNotify>	hsvdvbsi_strapiN;

ProvidesInterface<IHsvStreamNotify>	hsvmpeg_strapiN;

ProvidesInterface<IHsvStream>	istrapi;

//Required interfaces
public:
RequiresInterface<IHsvStream>	icamnitstrapi;
RequiresInterface<IHsvStream>	ieitstrapi;
RequiresInterface<IHsvStream>	ilclstrapi;
RequiresInterface<IHsvStream>	initstrapi;
RequiresInterface<IHsvStream>	ipatstrapi;
RequiresInterface<IHsvStream>	ipmtstrapi;
RequiresInterface<IHsvStream>	isdtstrapi;
RequiresInterface<IHsvStream>	itdtstrapi;
RequiresInterface<IHsvStream>	itotstrapi;
RequiresInterface<IHsvStreamNotify>	strapiN;

public:
CHsvDvbStreamingDataManager_mstrapi_Priv():i__hsvdvbcamsdm_strapiN(this),i__hsvdvbsi_strapiN(this),i__hsvmpeg_strapiN(this),i__istrapi(this)
{
hsvdvbcamsdm_strapiN	=	&i__hsvdvbcamsdm_strapiN;
hsvdvbsi_strapiN	=	&i__hsvdvbsi_strapiN;
hsvmpeg_strapiN	=	&i__hsvmpeg_strapiN;
istrapi	=	&i__istrapi;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define icamnitstrapi_iPresent() (icamnitstrapi.Present())
#define icamnitstrapi_GetSize(dest,spid)	icamnitstrapi->GetSize(dest,spid)
#define icamnitstrapi_GetIndex(dest,spid,key1,key2,key3,index)	icamnitstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define icamnitstrapi_GetByKey(dest,spid,key1,key2,key3,val)	icamnitstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define icamnitstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	icamnitstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define icamnitstrapi_GetByIndex(dest,spid,index,val)	icamnitstrapi->GetByIndex(dest,spid,index,val)
#define ieitstrapi_iPresent() (ieitstrapi.Present())
#define ieitstrapi_GetSize(dest,spid)	ieitstrapi->GetSize(dest,spid)
#define ieitstrapi_GetIndex(dest,spid,key1,key2,key3,index)	ieitstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define ieitstrapi_GetByKey(dest,spid,key1,key2,key3,val)	ieitstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define ieitstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	ieitstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define ieitstrapi_GetByIndex(dest,spid,index,val)	ieitstrapi->GetByIndex(dest,spid,index,val)
#define ilclstrapi_iPresent() (ilclstrapi.Present())
#define ilclstrapi_GetSize(dest,spid)	ilclstrapi->GetSize(dest,spid)
#define ilclstrapi_GetIndex(dest,spid,key1,key2,key3,index)	ilclstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define ilclstrapi_GetByKey(dest,spid,key1,key2,key3,val)	ilclstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define ilclstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	ilclstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define ilclstrapi_GetByIndex(dest,spid,index,val)	ilclstrapi->GetByIndex(dest,spid,index,val)
#define initstrapi_iPresent() (initstrapi.Present())
#define initstrapi_GetSize(dest,spid)	initstrapi->GetSize(dest,spid)
#define initstrapi_GetIndex(dest,spid,key1,key2,key3,index)	initstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define initstrapi_GetByKey(dest,spid,key1,key2,key3,val)	initstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define initstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	initstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define initstrapi_GetByIndex(dest,spid,index,val)	initstrapi->GetByIndex(dest,spid,index,val)
#define ipatstrapi_iPresent() (ipatstrapi.Present())
#define ipatstrapi_GetSize(dest,spid)	ipatstrapi->GetSize(dest,spid)
#define ipatstrapi_GetIndex(dest,spid,key1,key2,key3,index)	ipatstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define ipatstrapi_GetByKey(dest,spid,key1,key2,key3,val)	ipatstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define ipatstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	ipatstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define ipatstrapi_GetByIndex(dest,spid,index,val)	ipatstrapi->GetByIndex(dest,spid,index,val)
#define ipmtstrapi_iPresent() (ipmtstrapi.Present())
#define ipmtstrapi_GetSize(dest,spid)	ipmtstrapi->GetSize(dest,spid)
#define ipmtstrapi_GetIndex(dest,spid,key1,key2,key3,index)	ipmtstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define ipmtstrapi_GetByKey(dest,spid,key1,key2,key3,val)	ipmtstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define ipmtstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	ipmtstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define ipmtstrapi_GetByIndex(dest,spid,index,val)	ipmtstrapi->GetByIndex(dest,spid,index,val)
#define isdtstrapi_iPresent() (isdtstrapi.Present())
#define isdtstrapi_GetSize(dest,spid)	isdtstrapi->GetSize(dest,spid)
#define isdtstrapi_GetIndex(dest,spid,key1,key2,key3,index)	isdtstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define isdtstrapi_GetByKey(dest,spid,key1,key2,key3,val)	isdtstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define isdtstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	isdtstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define isdtstrapi_GetByIndex(dest,spid,index,val)	isdtstrapi->GetByIndex(dest,spid,index,val)
#define itdtstrapi_iPresent() (itdtstrapi.Present())
#define itdtstrapi_GetSize(dest,spid)	itdtstrapi->GetSize(dest,spid)
#define itdtstrapi_GetIndex(dest,spid,key1,key2,key3,index)	itdtstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define itdtstrapi_GetByKey(dest,spid,key1,key2,key3,val)	itdtstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define itdtstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	itdtstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define itdtstrapi_GetByIndex(dest,spid,index,val)	itdtstrapi->GetByIndex(dest,spid,index,val)
#define itotstrapi_iPresent() (itotstrapi.Present())
#define itotstrapi_GetSize(dest,spid)	itotstrapi->GetSize(dest,spid)
#define itotstrapi_GetIndex(dest,spid,key1,key2,key3,index)	itotstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define itotstrapi_GetByKey(dest,spid,key1,key2,key3,val)	itotstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define itotstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	itotstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define itotstrapi_GetByIndex(dest,spid,index,val)	itotstrapi->GetByIndex(dest,spid,index,val)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
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
#include "locals_mstrapi.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

