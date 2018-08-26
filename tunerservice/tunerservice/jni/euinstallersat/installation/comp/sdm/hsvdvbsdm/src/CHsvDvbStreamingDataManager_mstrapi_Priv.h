#ifndef  _CHSVDVBSTREAMINGDATAMANAGER_MSTRAPI_PRIV_H
#define  _CHSVDVBSTREAMINGDATAMANAGER_MSTRAPI_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvStreamNotify.h>
#include <IHsvStream.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSdmEnable.h>
#include <CS2MwBase.h>

class CHsvDvbStreamingDataManager_mstrapi_Priv;
#define CLASSSCOPE CHsvDvbStreamingDataManager_mstrapi_Priv::
#include "locals_mstrapi.h"

class CHsvDvbStreamingDataManager_mstrapi_Priv : public CS2MwBase
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
IHsvStreamNotifyImpl(CHsvDvbStreamingDataManager_mstrapi_Priv,hsvdvbsi_strapiN);
IHsvStreamNotifyImpl(CHsvDvbStreamingDataManager_mstrapi_Priv,hsvsimplempeg_strapiN);
IHsvStreamImpl(CHsvDvbStreamingDataManager_mstrapi_Priv,istrapi);
public:
ProvidesInterface<IHsvStreamNotify>	hsvdvbsi_strapiN;

ProvidesInterface<IHsvStreamNotify>	hsvsimplempeg_strapiN;

ProvidesInterface<IHsvStream>	istrapi;

//Required interfaces
public:
RequiresInterface<IHsvStream>	ibatstrapi;
RequiresInterface<IHsvStream>	ifntstrapi;
RequiresInterface<IHsvStream>	ifststrapi;
RequiresInterface<IHsvStream>	ilclstrapi;
RequiresInterface<IHsvStream>	initstrapi;
RequiresInterface<IHsvStream>	isdtstrapi;
RequiresInterface<IHsvStream>	isgtstrapi;
RequiresInterface<IHsvStream>	isimplepatstrapi;
RequiresInterface<IHsvStream>	isimplepmtstrapi;
RequiresInterface<IHsvStream>	ipostcodestrapi;
RequiresInterface<IHsvStreamNotify>	strapiN;
RequiresInterface<IHsvStream>	icamnitstrapi;
RequiresInterface<IHsvSatelliteInstallation>	ins;
RequiresInterface<IHsvSdmEnable>  chsvdvbsdt_Freesatena;
RequiresInterface<IHsvStream>	itotstrapi;

public:
CHsvDvbStreamingDataManager_mstrapi_Priv():i__hsvdvbsi_strapiN(this),i__hsvsimplempeg_strapiN(this),i__istrapi(this)
{
hsvdvbsi_strapiN	=	&i__hsvdvbsi_strapiN;
hsvsimplempeg_strapiN	=	&i__hsvsimplempeg_strapiN;
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
#define ibatstrapi_iPresent() (ibatstrapi.Present())
#define ibatstrapi_GetSize(dest,spid)	ibatstrapi->GetSize(dest,spid)
#define ibatstrapi_GetIndex(dest,spid,key1,key2,key3,index)	ibatstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define ibatstrapi_GetByKey(dest,spid,key1,key2,key3,val)	ibatstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define ibatstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	ibatstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define ibatstrapi_GetByIndex(dest,spid,index,val)	ibatstrapi->GetByIndex(dest,spid,index,val)
#define ifntstrapi_iPresent() (ifntstrapi.Present())
#define ifntstrapi_GetSize(dest,spid)	ifntstrapi->GetSize(dest,spid)
#define ifntstrapi_GetIndex(dest,spid,key1,key2,key3,index)	ifntstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define ifntstrapi_GetByKey(dest,spid,key1,key2,key3,val)	ifntstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define ifntstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	ifntstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define ifntstrapi_GetByIndex(dest,spid,index,val)	ifntstrapi->GetByIndex(dest,spid,index,val)
#define ifststrapi_iPresent() (ifststrapi.Present())
#define ifststrapi_GetSize(dest,spid)	ifststrapi->GetSize(dest,spid)
#define ifststrapi_GetIndex(dest,spid,key1,key2,key3,index)	ifststrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define ifststrapi_GetByKey(dest,spid,key1,key2,key3,val)	ifststrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define ifststrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	ifststrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define ifststrapi_GetByIndex(dest,spid,index,val)	ifststrapi->GetByIndex(dest,spid,index,val)
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
#define isdtstrapi_iPresent() (isdtstrapi.Present())
#define isdtstrapi_GetSize(dest,spid)	isdtstrapi->GetSize(dest,spid)
#define isdtstrapi_GetIndex(dest,spid,key1,key2,key3,index)	isdtstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define isdtstrapi_GetByKey(dest,spid,key1,key2,key3,val)	isdtstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define isdtstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	isdtstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define isdtstrapi_GetByIndex(dest,spid,index,val)	isdtstrapi->GetByIndex(dest,spid,index,val)
#define ipostcodestrapi_iPresent() (ipostcodestrapi.Present())
#define ipostcodestrapi_GetSize(dest,spid)	ipostcodestrapi->GetSize(dest,spid)
#define ipostcodestrapi_GetIndex(dest,spid,key1,key2,key3,index)	ipostcodestrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define ipostcodestrapi_GetByKey(dest,spid,key1,key2,key3,val)	ipostcodestrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define ipostcodestrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	ipostcodestrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define ipostcodestrapi_GetByIndex(dest,spid,index,val)	ipostcodestrapi->GetByIndex(dest,spid,index,val)
#define isimplepatstrapi_iPresent() (isimplepatstrapi.Present())
#define isimplepatstrapi_GetSize(dest,spid)	isimplepatstrapi->GetSize(dest,spid)
#define isimplepatstrapi_GetIndex(dest,spid,key1,key2,key3,index)	isimplepatstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define isimplepatstrapi_GetByKey(dest,spid,key1,key2,key3,val)	isimplepatstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define isimplepatstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	isimplepatstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define isimplepatstrapi_GetByIndex(dest,spid,index,val)	isimplepatstrapi->GetByIndex(dest,spid,index,val)
#define isimplepmtstrapi_iPresent() (isimplepmtstrapi.Present())
#define isimplepmtstrapi_GetSize(dest,spid)	isimplepmtstrapi->GetSize(dest,spid)
#define isimplepmtstrapi_GetIndex(dest,spid,key1,key2,key3,index)	isimplepmtstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define isimplepmtstrapi_GetByKey(dest,spid,key1,key2,key3,val)	isimplepmtstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define isimplepmtstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	isimplepmtstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define isimplepmtstrapi_GetByIndex(dest,spid,index,val)	isimplepmtstrapi->GetByIndex(dest,spid,index,val)
#define icamnitstrapi_iPresent() (icamnitstrapi.Present())
#define icamnitstrapi_GetSize(dest,spid)	icamnitstrapi->GetSize(dest,spid)
#define icamnitstrapi_GetIndex(dest,spid,key1,key2,key3,index)	icamnitstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define icamnitstrapi_GetByKey(dest,spid,key1,key2,key3,val)	icamnitstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define icamnitstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	icamnitstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define icamnitstrapi_GetByIndex(dest,spid,index,val)	icamnitstrapi->GetByIndex(dest,spid,index,val)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
#define isgtstrapi_iPresent() (isgtstrapi.Present())
#define isgtstrapi_GetSize(dest,spid)	isgtstrapi->GetSize(dest,spid)
#define isgtstrapi_GetIndex(dest,spid,key1,key2,key3,index)	isgtstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define isgtstrapi_GetByKey(dest,spid,key1,key2,key3,val)	isgtstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define isgtstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	isgtstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define isgtstrapi_GetByIndex(dest,spid,index,val)	isgtstrapi->GetByIndex(dest,spid,index,val)
#define itotstrapi_iPresent() (itotstrapi.Present())
#define itotstrapi_GetSize(dest,spid)	itotstrapi->GetSize(dest,spid)
#define itotstrapi_GetIndex(dest,spid,key1,key2,key3,index)	itotstrapi->GetIndex(dest,spid,key1,key2,key3,index)
#define itotstrapi_GetByKey(dest,spid,key1,key2,key3,val)	itotstrapi->GetByKey(dest,spid,key1,key2,key3,val)
#define itotstrapi_GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)	itotstrapi->GetRangeByKey(dest,spid,noofkeys,key1,key2,key3,from,to)
#define itotstrapi_GetByIndex(dest,spid,index,val)	itotstrapi->GetByIndex(dest,spid,index,val)
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

