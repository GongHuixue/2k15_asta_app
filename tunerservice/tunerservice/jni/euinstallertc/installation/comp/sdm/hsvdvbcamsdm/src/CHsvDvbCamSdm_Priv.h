#ifndef  _CHSVDVBCAMSDM_PRIV_H
#define  _CHSVDVBCAMSDM_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCamScanHelper.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvSdmEnable.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvMpegServices.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <CTCMwBase.h>
class CHsvDvbCamSdm_Priv;
#define CLASSSCOPE CHsvDvbCamSdm_Priv::
#include "locals_m.h"

class CHsvDvbCamSdm_Priv : public CTCMwBase
{
public:
virtual ~CHsvDvbCamSdm_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvCamScanHelperImpl(CHsvDvbCamSdm_Priv,camScanparser);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamSdm_Priv,camnitc2dsconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamSdm_Priv,camnitcabledsconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamSdm_Priv,camnitcontentlabelconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamSdm_Priv,camnitlinkageinfoconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamSdm_Priv,camnitserviceconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamSdm_Priv,camnitt2dsconf);
IHsvSortedTableConfigurationExImpl(CHsvDvbCamSdm_Priv,camnitterrestrialdsconf);
IHsvSdmEnableImpl(CHsvDvbCamSdm_Priv,ena);
IHsvPowerImpl(CHsvDvbCamSdm_Priv,pow);
IHsvStreamImpl(CHsvDvbCamSdm_Priv,strapi);
IHsvStreamFilterImpl(CHsvDvbCamSdm_Priv,strmfltr);
public:
ProvidesInterface<IHsvCamScanHelper>	camScanparser;
ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitc2dsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitcabledsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitcontentlabelconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitlinkageinfoconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitserviceconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitt2dsconf;

ProvidesInterface<IHsvSortedTableConfigurationEx>	camnitterrestrialdsconf;

ProvidesInterface<IHsvSdmEnable>	ena;

ProvidesInterface<IHsvPower>	pow;

ProvidesInterface<IHsvStream>	strapi;

ProvidesInterface<IHsvStreamFilter>	strmfltr;

//Required interfaces
public:
RequiresInterface<IHsvCharSetUtility2>	charsetutil;
RequiresInterface<IHsvMpegServices>	mpegserv;
RequiresInterface<IHsvSortedTable2>	srtdb;
RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
RequiresInterface<IHsvStreamNotify>	strapiN;

public:
CHsvDvbCamSdm_Priv():i__camScanparser(this),i__camnitc2dsconf(this),i__camnitcabledsconf(this),i__camnitcontentlabelconf(this),i__camnitlinkageinfoconf(this),i__camnitserviceconf(this),i__camnitt2dsconf(this),i__camnitterrestrialdsconf(this),i__ena(this),i__pow(this),i__strapi(this),i__strmfltr(this)
{
camScanparser	=	&i__camScanparser;
camnitc2dsconf	=	&i__camnitc2dsconf;
camnitcabledsconf	=	&i__camnitcabledsconf;
camnitcontentlabelconf	=	&i__camnitcontentlabelconf;
camnitlinkageinfoconf	=	&i__camnitlinkageinfoconf;
camnitserviceconf	=	&i__camnitserviceconf;
camnitt2dsconf	=	&i__camnitt2dsconf;
camnitterrestrialdsconf	=	&i__camnitterrestrialdsconf;
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
#define srtdbids_CamNitCableDS	 				reinterpret_cast<int>(&i__camnitcabledsconf)
#define srtdbids_CamNitTerrestrialDS	 		reinterpret_cast<int>(&i__camnitterrestrialdsconf)
#define srtdbids_CamNitC2DS	 					reinterpret_cast<int>(&i__camnitc2dsconf)
#define srtdbids_CamNitT2DS	 					reinterpret_cast<int>(&i__camnitt2dsconf)
#define srtdbids_CamNitContentLabel	 			reinterpret_cast<int>(&i__camnitcontentlabelconf)
#define srtdbids_CamNitService	 				reinterpret_cast<int>(&i__camnitserviceconf)
#define strapiN_iPresent() (strapiN.Present())
#define strapiN_OnCompleted(dest,spid)	strapiN->OnCompleted(dest,spid)
#define strapiN_OnAdded(dest,spid,key1,key2,key3)	strapiN->OnAdded(dest,spid,key1,key2,key3)
#define strapiN_OnChanged(dest,spid,key1,key2,key3,eventid)	strapiN->OnChanged(dest,spid,key1,key2,key3,eventid)
#define strapiN_OnRemoved(dest,spid,key1,key2,key3)	strapiN->OnRemoved(dest,spid,key1,key2,key3)
#define camnitc2dsconf_MaxElements	i__camnitc2dsconf.m_MaxElements
#define camnitc2dsconf_ElementSize	i__camnitc2dsconf.m_ElementSize
#define camnitc2dsconf_ThreadSafe	i__camnitc2dsconf.m_ThreadSafe
#define camnitc2dsconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define camnitc2dsconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define camnitc2dsconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define camnitc2dsconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define camnitc2dsconf_SortCriteria	i__camnitc2dsconf.m_SortCriteria
#define camnitc2dsconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define camnitc2dsconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define camnitc2dsconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define camnitcabledsconf_MaxElements	i__camnitcabledsconf.m_MaxElements
#define camnitcabledsconf_ElementSize	i__camnitcabledsconf.m_ElementSize
#define camnitcabledsconf_ThreadSafe	i__camnitcabledsconf.m_ThreadSafe
#define camnitcabledsconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define camnitcabledsconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define camnitcabledsconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define camnitcabledsconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define camnitcabledsconf_SortCriteria	i__camnitcabledsconf.m_SortCriteria
#define camnitcabledsconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define camnitcabledsconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define camnitcabledsconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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
#define camnitt2dsconf_MaxElements	i__camnitt2dsconf.m_MaxElements
#define camnitt2dsconf_ElementSize	i__camnitt2dsconf.m_ElementSize
#define camnitt2dsconf_ThreadSafe	i__camnitt2dsconf.m_ThreadSafe
#define camnitt2dsconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define camnitt2dsconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define camnitt2dsconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define camnitt2dsconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define camnitt2dsconf_SortCriteria	i__camnitt2dsconf.m_SortCriteria
#define camnitt2dsconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define camnitt2dsconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define camnitt2dsconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
#define camnitterrestrialdsconf_MaxElements	i__camnitterrestrialdsconf.m_MaxElements
#define camnitterrestrialdsconf_ElementSize	i__camnitterrestrialdsconf.m_ElementSize
#define camnitterrestrialdsconf_ThreadSafe	i__camnitterrestrialdsconf.m_ThreadSafe
#define camnitterrestrialdsconf_Primary	IHsvSortedTableConfigurationEx_Primary
#define camnitterrestrialdsconf_Secondary	IHsvSortedTableConfigurationEx_Secondary
#define camnitterrestrialdsconf_Teritiary	IHsvSortedTableConfigurationEx_Teritiary
#define camnitterrestrialdsconf_Quaternary	IHsvSortedTableConfigurationEx_Quaternary
#define camnitterrestrialdsconf_SortCriteria	i__camnitterrestrialdsconf.m_SortCriteria
#define camnitterrestrialdsconf_SmallerKey	IHsvSortedTableConfigurationEx_SmallerKey
#define camnitterrestrialdsconf_Equal	IHsvSortedTableConfigurationEx_Equal
#define camnitterrestrialdsconf_BiggerKey	IHsvSortedTableConfigurationEx_BiggerKey
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

