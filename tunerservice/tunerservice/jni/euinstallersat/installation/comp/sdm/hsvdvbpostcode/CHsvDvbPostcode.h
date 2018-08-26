#ifndef  _CHSVDVBPOSTCODE_H
#define  _CHSVDVBPOSTCODE_H

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvDemuxSectionFilterNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvSortedTableConfigurationEx.h>
#include <IHsvPower.h>
#include <IHsvStream.h>
#include <IHsvStreamFilter.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvDVBSIConfig.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDemuxSectionFilter2.h>
#include <dmxdefines.h>
#include <IHsvSortedTable2.h>
#include <IHsvDvbSiSortedTableIds.h>
#include <IHsvStreamNotify.h>
#include <IHsvSatSystemSettings.h>
#include <Postcode_ParserDef.h>


#define CLASSSCOPE CHsvDvbPostcode::
#define FNADDR(f) (& CLASSSCOPE f)

#define FREESAT_POSTCODE_TABLE_ID                 		(0xD2)
#define FREESAT_POSTCODE_KEY_MAP_TABLE					(0)
#define FREESAT_REGION_KEY_MAP_TABLE					(1)

class CHsvDvbPostcode: public IHsvDemuxSectionFilterNotify, public IHsvSdmEnable, public IHsvPower, public IHsvStream, public IHsvStreamFilter
{

	typedef struct _DmxROMData
	{
		Nat8 Version;
		Nat8 TablesReq;
		Nat8 TablesRecvd;
		Nat32 SubscrId;
		Nat32 SectionInfo;
	}DmxROMData;

	typedef struct ConcatPostCode
	{
		Nat16 totalPostCodeLen;
		Nat8 mConcatPostCodeDump[16*4096];
	} ConcatPostCode;

	typedef struct ConcatRegionKeyMap
	{
		Nat16 totalRegionKeyMapLen;
		Nat8 mConcatRegionKeyMapDump[2*4096];
	} ConcatRegionKeyMap;

public:
	void OnRequestAllowed(HsvDestination dest);
	 void OnRequestCancelled(Nat32 subscrId);
	 void OnRequestNotAllowed(void);

	 void Enable(HsvDemux dmx);
	 void Disable(HsvDemux dmx);
	 void Sync(HsvDemux dmx);

	 void Init(void);
	 void TurnOn(void);
	 void TurnOff(void);

	 int GetSize(HsvDestination dest,int spid);
	 Bool GetIndex(HsvDestination dest,int spid,int key1,int key2,int key3,int * index);
	 Bool GetByKey(HsvDestination dest,int spid,int key1,int key2,int key3,void * val);
	 Bool GetRangeByKey(HsvDestination dest,int spid,int noofkeys,int key1,int key2,int key3,int * from,int * to);
	 Bool GetByIndex(HsvDestination dest,int spid,int index,void * val);

	 Bool IsSet(HsvDestination dest,int filterid,int value);
	 Bool IsReady(HsvDestination dest,int filterid);
	 Bool Set(HsvDestination dest,int filterid,int value);
	 Bool Clear(HsvDestination dest,int filterid,int value);
	 void createDump(Nat8 * PrimarySectionStartAddress);


public:
	ProvidesInterface<IHsvDemuxSectionFilterNotify>	dmxsecfN;

	ProvidesInterface<IHsvSdmEnable>	ena;

	ProvidesInterface<IHsvPower>	pow;

	ProvidesInterface<IHsvStream>	strapi;

	ProvidesInterface<IHsvStreamFilter>	strmfltr;

	ProvidesInterface<IHsvSortedTableConfigurationEx>	postcodekeyconf;

	ProvidesInterface<IHsvSortedTableConfigurationEx>	postcoderegionkeyconf;

	//Required interfaces
public:
	RequiresInterface<IHsvCharSetUtility2>	charsetutil;
	RequiresInterface<IHsvCountryIds>	cids;
	RequiresInterface<IHsvDVBSIConfig>	conf;
	RequiresInterface<IHsvSdmControlNotifyEx>	ctrlN;
	RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
	RequiresInterface<IHsvSatelliteInstallation>	ins;
	RequiresInterface<IHsvSatellitePackageInstallation>	pakgins;
	RequiresInterface<IHsvDemuxSectionFilter2>	sec;
	RequiresInterface<IHsvSortedTable2>	srtdb;
	RequiresInterface<IHsvDvbSiSortedTableIds>	srtdbids;
	RequiresInterface<IHsvStreamNotify>	strapiN;
	RequiresInterface<IHsvSatSystemSettings>	sysset;

private:
	DEMUX_DEFINES(CHsvDvbPostcode,sec);

private:
	DmxROMData DmxRomData[HsvDmxLast];
	static Bool bothSubTablesCollected;
	static Nat32 NodeIndex;
	static Nat32 K;
	Nat8 mBuffer[16*4096];
	ConcatPostCode mConcatPostCode;
	ConcatRegionKeyMap mConcatRegionKeyMap;
	static Nat16 CurrentLookupTableType;



	
	static PostCodeTree_Dump postCodeDump[FREESAT_MAX_POSTCODE_TREE_SECTIONS];  
	static RegionKeyMap_Dump regionKeyDump[FREESAT_MAX_REGION_KEY_SECTIONS];
	
	
	void params__init(void);
	void module__init(void);
	Bool Postcode_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
	void InitFreesatPostcodeKeyMap(HsvDemux dmx);
	void InitFreesatRegionKeyMap(HsvDemux dmx);
	Bool ipop_PopulatePostcode ( HsvDemux dmx ,int code );
	void mPopulatePostcodeTreeTable( HsvDemux dmx ,  int code);
	void mPopulateRegionKeyTable( HsvDemux dmx , int code);
	void startRequestForRegionKeyTable(int code,HsvDemux dmx);
	void concatPostCodeTree();
	void concatRegionKeyMapTree();
	void parsePostCodeDump(HsvDemux dmx,int code);
	void parseRegionKeyDump(HsvDemux dmx,int code);

	IHsvSortedTableConfigurationExImpl(CHsvDvbPostcode,postcodekeyconf);
	IHsvSortedTableConfigurationExImpl(CHsvDvbPostcode,postcoderegionkeyconf);

public:
	CHsvDvbPostcode():i__postcodekeyconf(this), i__postcoderegionkeyconf(this)
	{

		dmxsecfN	= this;
		ena	= this;
		pow	= this;
		strapi	= this;
		strmfltr	= this;

		postcodekeyconf = &i__postcodekeyconf;
		postcoderegionkeyconf = &i__postcoderegionkeyconf;

		module__init();
		params__init();
	}

	virtual ~CHsvDvbPostcode();

};


#define srtdbids_PostcodeFreesatPostcodeKeyMap	 reinterpret_cast<int>(&i__postcodekeyconf)
#define srtdbids_PostcodeFreesatRegionKeyMap	 reinterpret_cast<int>(&i__postcoderegionkeyconf)

#define postcodekeyconf_MaxElements	i__postcodekeyconf.m_MaxElements
#define postcodekeyconf_ElementSize		i__postcodekeyconf.m_ElementSize
#define postcodekeyconf_ThreadSafe		i__postcodekeyconf.m_ThreadSafe
#define postcodekeyconf_Primary			IHsvSortedTableConfigurationEx_Primary
#define postcodekeyconf_Secondary		IHsvSortedTableConfigurationEx_Secondary
#define postcodekeyconf_Teritiary			IHsvSortedTableConfigurationEx_Teritiary
#define postcodekeyconf_Quaternary		IHsvSortedTableConfigurationEx_Quaternary
#define postcodekeyconf_SortCriteria		i__postcodekeyconf.m_SortCriteria
#define postcodekeyconf_SmallerKey		IHsvSortedTableConfigurationEx_SmallerKey
#define postcodekeyconf_Equal			IHsvSortedTableConfigurationEx_Equal
#define postcodekeyconf_BiggerKey		IHsvSortedTableConfigurationEx_BiggerKey


#define postcoderegionkeyconf_MaxElements		i__postcoderegionkeyconf.m_MaxElements
#define postcoderegionkeyconf_ElementSize		i__postcoderegionkeyconf.m_ElementSize
#define postcoderegionkeyconf_ThreadSafe		i__postcoderegionkeyconf.m_ThreadSafe
#define postcoderegionkeyconf_Primary			IHsvSortedTableConfigurationEx_Primary
#define postcoderegionkeyconf_Secondary			IHsvSortedTableConfigurationEx_Secondary
#define postcoderegionkeyconf_Teritiary			IHsvSortedTableConfigurationEx_Teritiary
#define postcoderegionkeyconf_Quaternary		IHsvSortedTableConfigurationEx_Quaternary
#define postcoderegionkeyconf_SortCriteria		i__postcoderegionkeyconf.m_SortCriteria
#define postcoderegionkeyconf_SmallerKey		IHsvSortedTableConfigurationEx_SmallerKey
#define postcoderegionkeyconf_Equal				IHsvSortedTableConfigurationEx_Equal
#define postcoderegionkeyconf_BiggerKey		IHsvSortedTableConfigurationEx_BiggerKey

#endif

