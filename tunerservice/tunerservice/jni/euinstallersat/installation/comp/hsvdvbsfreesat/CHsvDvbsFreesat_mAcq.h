#ifndef  _CHSVDVBSFREESAT_MACQ_H
#define  _CHSVDVBSFREESAT_MACQ_H

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvPower.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvDigitalScanData.h>
#include <IHsvSatelliteUtility.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvStream.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvDigitalScanSdsdData.h>
#include <IHsvSatelliteUtility.h>
#include <CS2MwBase.h>



/*****************************************************************************************
 * Class definition
 *****************************************************************************************/
class CHsvDvbsFreesat_mAcq: public IHsvPower, public IHsvDigitalAcquisition, public CS2MwBase
{
private:

	Pumpdefines (CHsvDvbsFreesat_mAcq);

	#define	AUTO_MODE								(IHsvSatelliteInstallation_InstallationServiceScan)

	#define	GETSERVICETYPE(serviceType)				(((serviceType == AppApiRadioService) || (serviceType == AppApiAdvCodecRadioService)) ? HsvRadio: HsvOnePart)

	#define	IS_VALID_ONID							((DataAcqInstance.Onid >= 0xFF00)? FALSE: TRUE)
	#define	IS_VALID_NID							((DataAcqInstance.NetworkId >= 0xFF01)? FALSE: TRUE)
	#define	IS_VALID_TSID							( TRUE ) /* Not using yet in field.. might come soon */
	#define	IS_VALID_TS								(IS_VALID_ONID && IS_VALID_NID && IS_VALID_TSID)
	#define	INVALID_PRESET							(0X1FFF) //(0XFFFF)
	#define	SAT_INFO_TABLE							(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_SatInfo)
	#define	PTC_TABLE							    (IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_DigitalTS)
	#define	SERVICE_TABLE							(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_DigitalService)
	#define	INTERACTIVE_SERVICE_TABLE				(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_InteractiveService)
	#define	HOMING_SERVICE_TABLE					(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_HomingService)
	#define	PRESET_TABLE							(IHsvProgramDatabaseConstants_Satellite | IHsvProgramDatabaseConstants_Preset)
	#define MIN_VALID_LCN    						(1)
	#define	MAX_VALID_LCN    						(4095)
	#define	VALID_LCN_RANGE(x)  					(((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))
	#define	REVALIDATE(x)     						((x) &= 0x7FFF) /*Revalidate to negate signed bit*/
	#define IS_RADIO_SERVICE(x)     				((x == AppApiRadioService) || (x == AppApiAdvCodecRadioService) )
	#define	ASSIGN_KEYS_OF_SVC(svcdat1, svcdat2)	{ \
														svcdat1.Tpid	= svcdat2.Tpid; \
														svcdat1.ServiceId			= svcdat2.ServiceId; \
													}
	#define	MAX_LNBS_SUPPORTED						(4)
	#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)		(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
													((OrgFreq/1000) * 1000))
	#define	IS_VALID_ROLLOFF(x)						(x<(sizeof(RollOffTable)/sizeof(RollOffTable[0])))
	#define	MAX_SERVICES							 MAX_VALID_LCN
	//#define	MAX_LCN_NUMBERS							(2001)
	#define MAX_SDSD								(100)
	//#define	ABS(freq1, freq2)						((freq1 >= freq2) ? (freq1 - freq2) : (freq2 - freq1))
	//#define FREQ_DRIFT_TOLERANCE					(4000)
	//#define BARKER_MUX_LINKAGE_TYPE					(0x04)
	#define FREESAT_INVALID_LCN						(0x1000)
	#define MAX_NUM_LCN_ENTRY						(8)
	#define MAX_NUM_PRESET_ENTRY					MAX_NUM_LCN_ENTRY
	#define REGIONAL_LCN_INDEX						(0)
	#define GLOBAL_REGION_ID						(0xFFFF)

	typedef enum
	{
		LD = 1,
		ILD
	}HomingServiceType;

	typedef enum
	{
		EvStartAcquire = 0,
		EvAcquireTSInfo,
		EvCompleteAcquire
	} AcqEvents;

	typedef struct
	{
		Nat16 OnId;
		Nat16 TsId;
		Nat16 NetworkId;
		Nat16 NumSdsds;
		Nat16 CurSdsd;
		Nat8 LnbNumber;
		HsvPgdatDigServiceData currService;
		Bool deleteCurrSvcOnZap;
	} HsvDataAcqInstance;

	typedef struct
	{
		Nat16 OnId;
		Nat16 TsId;
		Nat16 ServiceId;
		Nat8 ServiceType;
	} SvcListInfo;

	typedef struct
	{
		Nat8 VersionNumber;
		Nat16 NumOfRecords;
		SvcListInfo mSvcListInfo[MAX_SERVICES];
	} FreesatServiceList;

	typedef struct
	{
		Nat8 numSDSD;
		int CurrentSDSDIndex;
		HsvNITSatelliteDS SatDesc[MAX_SDSD];
	}FreesatSatDSDesc;

	typedef struct HomingMuxData 
	{
		Nat32	Frequency;
		Nat8	Polarization;
		Nat16	SatelliteId;
	} HomingMuxData;

	static Pump mDataAcqPump;

	static FreesatSatDSDesc mFreesatDSDesc;
	static FreesatServiceList mSvcListData;

	static int mDigitalChannelsFound;
	static int mDigitalTvChannelsFound;
	static int mDigitalRadioChannelsFound;
	static int mRemoveCurTv;
	static int mRemoveCurRadio;
	static Nat16 mUnicodeBuffer[11];
	


	static HsvDataAcqInstance DataAcqInstance;
	static HsvInstallationPTC CurrentPTC;
	static double RollOffTable[4];

	static HsvBarkerMuxData BarkerMuxData;

	void mPumpHandler (int value, Nat32 param);
	void mStartAcquisition (void);
	//void mStartFallbackAcquisition(void);
	void mGetPTCInfo (HSVSPTYPE(SatelliteDS,dvb,nit) sdsd, HsvInstallationPTC *ptc);
	Bool mGetTSMetaData (void);
	void mAcquireTSInfo (void);
	void mPopulateInteractiveServiceTable (void);
	void mPopulateHomingServiceTable (void);
	void mDeleteTSTable (HsvInstallationPTC *ptc);
	void mDeleteServicesFromDeletedMuxesInCurrentBAT (void);
	Bool mIsTSPresentInSLDList (HsvPgdatDigTSData *pTmpTsData);
	Bool mIsTSPresentInSDSDList (HsvPgdatDigTSData *pTmpTsData);
	void mAddToTSTable (HsvInstallationPTC *ptc, Bool *pIsSdsdChange, HsvPgdatDigTSData *pOldTsData);
	Bool mInstallMux (HsvInstallationPTC ptc, Bool isSdsdChange, HsvPgdatDigTSData *pOldTsData);
	Bool mCheckAndInstallService (HsvInstallationPTC *ptc, Bool isSdsdChange, HsvPgdatDigTSData *pOldTsData, SvcListInfo *pSvcList);
	void mAssignLCN (HsvPgdatDigServiceData *pSvcData, Bool channelExists);
	void mDeleteService (HsvPgdatDigServiceData *pSvcData, Bool duplicateSvc);
	void mDeleteServicesCurrentCarrier (HsvInstallationPTC *ptc);
	Bool mIsSvcPresentInServiceList (HsvPgdatDigServiceData *pSvcData);
	void mDeleteAllServicesFromCarrier (int tpId);
	void mUpdateService (HsvPgdatDigServiceData *pSvcData, HsvInstallationPTC* ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
	void mUpdateSatelliteName (HsvPgdatDigServiceData *pSvcData);
	void mAddNewService (HsvPgdatDigServiceData *pSvcData ,HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service, Bool duplicateSvc);
	void mAssignSvcBroadcastAttributes (HsvPgdatDigServiceData *pSvcData, HsvInstallationPTC *ptc, HSVSPTYPE(ActualTSService, dvb, sdt) *service);
	void mAssignSvcNonBroadcastAttributes (HsvPgdatDigServiceData *pSvcData);
	int mCalculateBandwidthFromSdsd (Nat8 rollOff, int symbolRate, Nat8 fecInner);
	int mConvertToPgdatServiceType (int serviceType);
	Bool mIsDigitalTvChannel (HsvPgdatDigServiceData *pSvcData);
	Bool mIsDigitalRadioService (HsvPgdatDigServiceData *pSvcData);
	void mCopyString (Nat16 *dest, Nat16 *src, int maxChars);
	Bool mIsServiceInstallable (SvcListInfo *service);
	void mCollectSdsds (void);
	void mCollectServicelistData (void);
	void mPopulateSatelliteLnbNumber (int satId);
	void mPopulateCurrentService (void);
	Bool mIsManualInstall (void);
	Bool mIsUpdateInstall (void);
	Bool mIsBackgroundUpdateInstall (void);
	void GetTricolorRegionNames (Nat16 **names, int *len);
	Nat16* mAsciiToUnicode(char *ascii_str,int length);
	Bool mCollectFreesatBarkerMuxData(void);

public:

	//IHsvPower
	virtual void Init(void);
	virtual void TurnOn(void);
	virtual void TurnOff(void);

	//IHsvDigitalAcquisition
	virtual void Initialise (int lnbNumber);
	virtual void AcquireData (int mode);
	virtual int GetNumberOfDigitalChannelsFound (void);
	virtual int GetNumberOfDigitalChannelsRemoved (void);
	virtual int GetNumberOfTvChannelsFound (void);
	virtual int GetNumberOfRadioChannelsFound (void);
	virtual int GetNumberOfTvChannelsRemoved (void);
	virtual int GetNumberofRadioChannelsRemoved (void);
	virtual int GetNumberOfSdsds (void);
	virtual Bool GetSdsdByIndex (int index, HsvNITSatelliteDS	*SdSdEntry);
	virtual int GetNumberOfTvChannelsInLnb (int lnb);
	virtual int GetNumberOfRadioChannelsInLnb (int lnb);
	virtual void AcquireDataOnTimeout (void);
	virtual int StoreBarkerMuxDetails (void);
	virtual void SyncTemporaryTableRecords (void);
	virtual void AssignLCN(HsvPgdatDigServiceData *psvcdat);

	//Constructor
	CHsvDvbsFreesat_mAcq()
	{
		iacqpow = this;
		idataacq = this;
	}

	//Destructor
	virtual ~CHsvDvbsFreesat_mAcq()
	{

	}

	//Provides interfaces
	ProvidesInterface<IHsvPower> iacqpow;
	ProvidesInterface<IHsvDigitalAcquisition> idataacq;

	//Required interfaces
	RequiresInterface<IHsvErrorCodeEx>	err;
	RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
	RequiresInterface<IHsvDigitalAcquisitionNotify>	ibckAcqN;
	RequiresInterface<IHsvDigitalAcquisitionNotify>	idataacqN;
	RequiresInterface<IHsvSatelliteInstallation>	insstate;
	RequiresInterface<IHsvDigitalScanData>	isvcscandata;
	RequiresInterface<IHsvSatelliteUtility>	iutil;
	RequiresInterface<IPumpEngine>	pen;
	RequiresInterface<IHsvProgramDatabase>	pgdb;
	RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
	RequiresInterface<IPumpExSub>	pmp;
	RequiresInterface<IHsvSatellitePackageInstallation>	rins;
	RequiresInterface<IHsvStream>	strapi;
	RequiresInterface<IHsvSatelliteSettings> isettings;
	RequiresInterface<IHsvDigitalScanSdsdData> iscansdsd;
	
};

#endif

