#ifndef  _CHSVDVBCAMNIT_PRIV_H
#define  _CHSVDVBCAMNIT_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCamDataParser.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <CS2MwBase.h>
class CHsvDvbCamNIT_Priv;
#define CLASSSCOPE CHsvDvbCamNIT_Priv::
#include "locals_m.h"

class CHsvDvbCamNIT_Priv : public CS2MwBase
{
public:
virtual ~CHsvDvbCamNIT_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvCamDataParserImpl(CHsvDvbCamNIT_Priv,camdataparser);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamNIT_Priv,camnitsatellitedsconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamNIT_Priv,optunesatellitedsconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamNIT_Priv,camnitcontentlabelconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamNIT_Priv,camnitlinkageinfoconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamNIT_Priv,camnitserviceconf);
IHsvSdmEnableImpl(CHsvDvbCamNIT_Priv,ena);
IHsvPowerImpl(CHsvDvbCamNIT_Priv,pow);
IHsvStreamImpl(CHsvDvbCamNIT_Priv,strapi);
IHsvStreamFilterImpl(CHsvDvbCamNIT_Priv,strmfltr);
public:
ProvidesInterface<IHsvCamDataParser>	camdataparser;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitsatellitedsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	optunesatellitedsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitcontentlabelconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitlinkageinfoconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitserviceconf;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;

public:
CHsvDvbCamNIT_Priv():i__camdataparser(this),i__camnitsatellitedsconf(this),i__optunesatellitedsconf(this),i__camnitcontentlabelconf(this),i__camnitlinkageinfoconf(this),i__camnitserviceconf(this),i__ena(this),i__pow(this),i__strapi(this),i__strmfltr(this)
{
camdataparser	=	&i__camdataparser;
camnitsatellitedsconf	=	&i__camnitsatellitedsconf;
optunesatellitedsconf	=	&i__optunesatellitedsconf;
camnitcontentlabelconf	=	&i__camnitcontentlabelconf;
camnitlinkageinfoconf	=	&i__camnitlinkageinfoconf;
camnitserviceconf	=	&i__camnitserviceconf;
ena	=	&i__ena;
pow	=	&i__pow;
strapi	=	&i__strapi;
strmfltr	=	&i__strmfltr;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define charsetutil_iPresent() (charsetutil.Present())
#define charsetutil_ExtractNone	IHsvCharSetUtility2_ExtractNone
#define charsetutil_ExtractShortName	IHsvCharSetUtility2_ExtractShortName
#define charsetutil_ExtractEITShortEvent	IHsvCharSetUtility2_ExtractEITShortEvent
#define charsetutil_ExtractEITExtendedEvent	IHsvCharSetUtility2_ExtractEITExtendedEvent
#define charsetutil_MbToWcEx(mbstr,mblen,wcstr,wclen,exinfo)	charsetutil->MbToWcEx(mbstr,mblen,wcstr,wclen,exinfo)
#define charsetutil_MbToWc(mbstr,mblen,wcstr,wclen,exinfo)	charsetutil->MbToWc(mbstr,mblen,wcstr,wclen,exinfo)
#define mpegserv_iPresent() (mpegserv.Present())
#define mpegserv_GetLanguageId(byte1,byte2,byte3)	mpegserv->GetLanguageId(byte1,byte2,byte3)
#define mpegserv_IsProgramPresent(dmx,prg)	mpegserv->IsProgramPresent(dmx,prg)
#define mpegserv_ReadTsPacketFields(subscr_id,sec)	mpegserv->ReadTsPacketFields(subscr_id,sec)
#define mpegserv_GetCcDescriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetCcDescriptor(dmx,prg,IsDescriptorParsed)
#define mpegserv_GetCaDescriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetCaDescriptor(dmx,prg,IsDescriptorParsed)
#define mpegserv_GetAc3Descriptor(dmx,prg,IsDescriptorParsed)	mpegserv->GetAc3Descriptor(dmx,prg,IsDescriptorParsed)
#define srtdb_iPresent() (srtdb.Present())
#define srtdb_OperatorEqual	IHsvSortedTable2_OperatorEqual
#define srtdb_OperatorSmaller	IHsvSortedTable2_OperatorSmaller
#define srtdb_OperatorGreater	IHsvSortedTable2_OperatorGreater
#define srtdb_GetNoOfRecords(tableid)	srtdb->GetNoOfRecords(tableid)
#define srtdb_Init(tableid)	srtdb->Init(tableid)
#define srtdb_Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->Insert(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->Update(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)	srtdb->Delete(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey)
#define srtdb_SearchOnPrimaryKey(tableid,PrimaryKey,from,to)	srtdb->SearchOnPrimaryKey(tableid,PrimaryKey,from,to)
#define srtdb_SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)	srtdb->SearchOnPrimaryAndSecondaryKey(tableid,PrimaryKey,SecondaryKey,from,to)
#define srtdb_QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)	srtdb->QueryOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,data)
#define srtdb_QueryOnIndex(tableid,index,data)	srtdb->QueryOnIndex(tableid,index,data)
#define srtdb_SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)	srtdb->SearchOnKey(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,index)
#define srtdb_SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)	srtdb->SearchOnKey2(tableid,PrimaryKey,SecondaryKey,TeritiaryKey,QuaternaryKey,op,index)
#define srtdbids_CamNitLinkageInfo	 			reinterpret_cast<int>(&i__camnitlinkageinfoconf)
#define srtdbids_CamNitSatelliteDS	 				reinterpret_cast<int>(&i__camnitsatellitedsconf)
#define srtdbids_OpTuneSatelliteDS	 				reinterpret_cast<int>(&i__optunesatellitedsconf)
#define srtdbids_CamNitContentLabel	 			reinterpret_cast<int>(&i__camnitcontentlabelconf)
#define srtdbids_CamNitService	 				reinterpret_cast<int>(&i__camnitserviceconf)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
#define camnitsatellitedsconf_MaxElements	i__camnitsatellitedsconf.m_MaxElements
#define camnitsatellitedsconf_ElementSize	i__camnitsatellitedsconf.m_ElementSize
#define camnitsatellitedsconf_ThreadSafe	i__camnitsatellitedsconf.m_ThreadSafe
#define camnitsatellitedsconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define camnitsatellitedsconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define camnitsatellitedsconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define camnitsatellitedsconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define camnitsatellitedsconf_SortCriteria	i__camnitsatellitedsconf.m_SortCriteria
#define camnitsatellitedsconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define camnitsatellitedsconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define camnitsatellitedsconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define optunesatellitedsconf_MaxElements       i__optunesatellitedsconf.m_MaxElements
#define optunesatellitedsconf_ElementSize       i__optunesatellitedsconf.m_ElementSize
#define optunesatellitedsconf_ThreadSafe        i__optunesatellitedsconf.m_ThreadSafe
#define optunesatellitedsconf_Primary   IHsvSortedTableConfigurationEx_Primary
#define optunesatellitedsconf_Secondary IHsvSortedTableConfigurationEx_Secondary
#define optunesatellitedsconf_Teritiary IHsvSortedTableConfigurationEx_Teritiary
#define optunesatellitedsconf_Quaternary        IHsvSortedTableConfigurationEx_Quaternary
#define optunesatellitedsconf_SortCriteria      i__optunesatellitedsconf.m_SortCriteria
#define optunesatellitedsconf_SmallerKey        IHsvSortedTableConfigurationEx_SmallerKey
#define optunesatellitedsconf_Equal     IHsvSortedTableConfigurationEx_Equal
#define optunesatellitedsconf_BiggerKey IHsvSortedTableConfigurationEx_BiggerKey
#define camnitcontentlabelconf_MaxElements	i__camnitcontentlabelconf.m_MaxElements
#define camnitcontentlabelconf_ElementSize	i__camnitcontentlabelconf.m_ElementSize
#define camnitcontentlabelconf_ThreadSafe	i__camnitcontentlabelconf.m_ThreadSafe
#define camnitcontentlabelconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define camnitcontentlabelconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define camnitcontentlabelconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define camnitcontentlabelconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define camnitcontentlabelconf_SortCriteria	i__camnitcontentlabelconf.m_SortCriteria
#define camnitcontentlabelconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define camnitcontentlabelconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define camnitcontentlabelconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define camnitlinkageinfoconf_MaxElements	i__camnitlinkageinfoconf.m_MaxElements
#define camnitlinkageinfoconf_ElementSize	i__camnitlinkageinfoconf.m_ElementSize
#define camnitlinkageinfoconf_ThreadSafe	i__camnitlinkageinfoconf.m_ThreadSafe
#define camnitlinkageinfoconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define camnitlinkageinfoconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define camnitlinkageinfoconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define camnitlinkageinfoconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define camnitlinkageinfoconf_SortCriteria	i__camnitlinkageinfoconf.m_SortCriteria
#define camnitlinkageinfoconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define camnitlinkageinfoconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define camnitlinkageinfoconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define camnitserviceconf_MaxElements	i__camnitserviceconf.m_MaxElements
#define camnitserviceconf_ElementSize	i__camnitserviceconf.m_ElementSize
#define camnitserviceconf_ThreadSafe	i__camnitserviceconf.m_ThreadSafe
#define camnitserviceconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define camnitserviceconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define camnitserviceconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define camnitserviceconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define camnitserviceconf_SortCriteria	i__camnitserviceconf.m_SortCriteria
#define camnitserviceconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define camnitserviceconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define camnitserviceconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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
#include "locals_m.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

