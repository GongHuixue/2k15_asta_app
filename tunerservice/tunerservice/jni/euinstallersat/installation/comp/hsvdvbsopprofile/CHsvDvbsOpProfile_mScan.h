#ifndef  _CHSVDVBSOPPROFILE_MSCAN_H
#define  _CHSVDVBSOPPROFILE_MSCAN_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteFrontEndNotify.h>
#include <IHsvCamDataParser.h>
#include <IHsvDigitalScanData.h>
#include <ICesOperatorProfileNotify.h>
#include <IHsvPower.h>
#include <IHsvStreamNotify.h>
#include <IHsvSdmEnable.h>
#include <IHsvCountryIds.h>
#include <IHsvSdmControl2.h>
#include <IHsvEuropeDiversity2.h>
#include <IHsvErrorCodeEx.h>
#include <IHsvDigitalAcquisition.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvMediaControl.h>
#include <ICesOperatorProfile.h>
#include <IPumpEngine.h>
#include <IPlfApiErrorIds.h>
#include <IPumpExSub.h>
#include <IHsvInstallationSigStrength.h>
#include <IHsvStream.h>
#include <IHsvWindowDestinationMap.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvSatelliteFrontEnd.h>
#include <IHsvSatellitePackageInstallation.h>
#include <IHsvDigitalAcquisitionNotify.h>
#include <IHsvSdmControlNotifyEx.h>
#include <IAppApiSystemSettings5.h>
#include <IPlfApiSigStrengthMeas.h>
#include <IHsvSatelliteInstallation.h>
#include <IHsvSdmControlNotifyEx.h>
#include <CS2MwBase.h>


class CHsvDvbsOpProfile_mScan: 	public IHsvPower, public IHsvSatellitePackageInstallation, 
								public IHsvDigitalScanData, public IHsvDigitalAcquisitionNotify,
								public IHsvSatelliteFrontEndNotify, public IHsvSdmControlNotifyEx,
								public ICesOperatorProfileNotify, public IHsvStreamNotify,
								public CS2MwBase
{
private:
	
	Pumpdefines(CHsvDvbsOpProfile_mScan);

	#define CLASSSCOPE CHsvDvbsOpProfile_mScan::
	#define FNADDR(f) (& CLASSSCOPE f)
	#define FPCALL(f) (this->* f)

	
	#define WINDOWID            			(wnddest_GetWindowId(HsvMain))
	#define TURNED_ON						(mModuleLifeCycle == TurnedOn)
		
	#define SATELLITE_MEDIUM  				(TRUE)	
	
	#define START_FREQUENCY 				(45 * 16)	
	#define END_FREQUENCY   				(863 * 16)

	//#define CURRENT_MODE    				(rins->GetInstallationMode())	
	#define CURRENT_MODE    				(1)	
	#define AUTO_CAM_MODE					(IHsvSatelliteInstallation_InstallationServiceScan)	
	#define CAM_NIT_UPDATE_MODE				(IHsvSatelliteInstallation_InstallationCamNit)
	#define BACKGROUND_CAM_MODE				(3)
	
	#define ACQUIRE_DSD						(0)	
	#define GET_DSD							(1)
	
	#define MAX_SERVICE_TYPES_SUPPORTED		(17)
	
	#define DVBS_DELIVERY_TAG				(0x43)	
	#define DVBS2_DELIVERY_OFFSET_TAG		(0x79)
	
	#define DVBS_DESCRIPTOR_ENTRY_LENGTH	(11) // Length of one location (pointing to a frequency..) in the DSD	
	
	#define AUTO_INSTALL					(GET_INS_MODE == AUTO_CAM_MODE)	
	#define CAM_NIT_INSTALL					(GET_INS_MODE == CAM_NIT_UPDATE_MODE)
	#define VALID_EVENT(Event)      		((Event >= EvStart) && (Event < EvMax))
	
	#define VALID_STATE(state)      		((state >= StIdle) && (state < StMax))	
	#define GET_INS_STATE		    		(mInstStatus.State)
	#define SET_INS_STATE(state)    		(mInstStatus.State = state)
	
	#define GET_INS_MODE		    		(mInstStatus.Mode)	
	#define SET_INS_MODE(mode)    			(mInstStatus.Mode = mode)	
	//#define VALID_CAM_INSTALL_MODE(mode)	(mode == IHsvInstallation2_InstallationModeCam)
	#define VALID_CAM_INSTALL_MODE(mode)	((mode == IHsvSatelliteInstallation_InstallationServiceScan) || (mode == IHsvSatelliteInstallation_InstallationCamNit))
	
	#define SERVICE_TYPES_SUPPORTED			("0x010203040506100A0C11161718191C2021")	
	#define TUNING_REQUIRED					((AUTO_INSTALL) || (REFRESH_REQUEST_FLAG != 0))	
	#define GET_CAM_DELIVERY_HINT			(mStatusInfo.op_Status.Delivery_System_Hint)	
	#define CAM_INITIALISED					(mStatusInfo.op_Status.Initialised_Flag)	
	#define ENTITLEMENT_CHANGE_REQUESTED	(mStatusInfo.op_Status.Entitlement_Change_Flag)	
	#define CAM_UPDATED_NIT_VERSION			(mStatusInfo.op_Status.NIT_Version)	
	#define PROFILE_INFO_VALID				(mStatusInfo.op_Info.info_Valid == 1)	
	#define REFRESH_REQUEST_FLAG			(mStatusInfo.op_Status.Refresh_Request_Flag)	
	#define LAST_CAM_NIT_VERSION			-1//(idvbset_GetAttribute(AUTO_MODE, rins_AttributeCamNITVersion))
	#define NIT_REQUIRED(version)			((mStatusInfo.op_Status.Profile_Type == OP_PROFILE_TYPE_1) &&			\
											((CAM_INITIALISED == FALSE) /*|| (version != LAST_CAM_NIT_VERSION)*/ || 	\
											  (ENTITLEMENT_CHANGE_REQUESTED == 1)))	
	#define CURRENT_SDSD_INDEX				(mCamDSDesc.currSdsdIndex)	
	#define CURRENT_FREQUENCY      			(mCamDSDesc.SatDesc[CURRENT_SDSD_INDEX].Frequency)			
	#define CURRENT_SYMBOL_RATE    		    (mCamDSDesc.SatDesc[CURRENT_SDSD_INDEX].SymbolRate)	
	#define CURRENT_POLARIZATION  			(mCamDSDesc.SatDesc[CURRENT_SDSD_INDEX].Polarization)

	#define MAX_SDSD						(100)
	//Constants defined in HsvPropertyTypes.dd
	#define MAX_LCNS						(8)
	#define MAX_CDSD_PER_TS    				10
	#define MAX_DSD_PER_TS     				20

	#define ADVANCE_TUNING_REQUIRED   	 		(REFRESH_REQUEST_FLAG == 1)
	#define URGENT_TUNING_REQUIRED   	 		(REFRESH_REQUEST_FLAG == 2)
	#define SCHEDULE_UPDATE					(REFRESH_REQUEST_FLAG == 3)

	//Constants defined in HsvInstallationTypes.dd
	#define MAX_MUXES_PER_NTK       (94)

	
	#define	ROUNDOFF_TPFREQ(UpdateFreq,OrgFreq)	(UpdateFreq = ((OrgFreq % 1000) > 500) ? (((OrgFreq / 1000) + 1) * 1000):\
												((OrgFreq/1000) * 1000))

	typedef void (CLASSSCOPE *FunctionNat32)(Nat32);

		
	typedef enum
	{
		StIdle,
		StStart,
		StTunerWait,
		StStrapiWait,
		StAcquireWait,
		StSearchStartWait,
		StMax
	}InsStates;
	typedef enum
	{
		EvStart,
		EvStop,
		EvStationFound,
		EvMakeDecision,
		EvStartTuning,
		EvDataAvailable,
		EvCheckLock,
		EvDataAcquired,
		EvDateTimeReceived,
		EvInstallComplete,
		EvMax
	}ScanPumpEvents;

	typedef enum
	{
		EvCamSearchStatus,
		EvCamStatusInfo,
		EvCamNITReceived,
		EvCamTuneRequest,
		EvCamTuneReply,
		EvCamAck,
		EvCamMax,
	}CamPumpEvents;
	typedef enum
	{
		Initialised = 0,
		TurnedOn,
		TurnedOff
	}ModuleLifeCycle;
	typedef struct 
	{
		int State;
		int Mode;		
		int	LnbNumber;
		int	LnbType;
		int	numSDSD;
		int	currSdsdIndex;
	}InstStatus;

	typedef struct
	{
		Nat8 numSDSD;
		int currSdsdIndex;
		HsvNITSatelliteDS SatDesc[MAX_SDSD];
	} CamDSDesc;

	
	static InstStatus mInstStatus;	
	static CamDSDesc mCamDSDesc;	
	static Pump mScanPump, mCamDataPump;	
	static Op_ProfileStatusInfo mStatusInfo;	
	static Op_ProfileTuneData *mTempTuneDataPtr;	
	static Op_Search_Settings mSearchSettings;	
	static Op_Tune_Status *mTempTuneReplyDataPtr;	
	static ModuleLifeCycle mModuleLifeCycle;
	static const FunctionNat32 EventActionMatrix[][StMax];
	
	void mScanPumpHandler(int event, Nat32 param);
	void FuncStartServiceScan(Nat32 Param);
	void FuncStartTuning (Nat32 param);
	void FuncCheckLockStatus (Nat32 param);
	void FuncDataAcquired (Nat32 param);
	void FuncStopServiceScan(Nat32 Param);
	void FuncStationFound(Nat32 Param);
	void FuncDataAvailable(Nat32 Param);
	void FuncMakeDecision(Nat32 param);
	void FuncDateTimeReceived(Nat32 Param);
	void FuncInstallComplete(Nat32 Param);
	void mSelectDecoder(void);
	void mSetTunerAttributes(void);
	void mStopSdm(HsvDemux dmx);
	Bool mGetNextDSD(void);
	void mGetPTCInfo(HsvInstallationPTC *ptc, Nat16 OnId, Nat16 TsId);
	Bool mLoadStrapiData(void);
	Bool mLoadOpTuneSDSDData(void);
	Bool mLoadDSDFromStrapi(int hsvspid);
	Bool mLoadOpTuneDSDFromStrapi(int hsvspid);
	int mGetNumOfDSD(int hsvspid, void *DSDesc);
	int mMapDSDTypeToChanDecoder(int DSDType);
	void* mGetLocalBuffer(int size);
	void* mReturnLocalBuffer(void **Buffer);
	Bool mIsValidDeliveryHint(int DeliveryHint);
	Bool mIsValidDeliveryDescriptorType();
	Bool mIsValidDeliveryDescriptorData(void);
	Bool mValidateCDS(void);
	Bool mValidateTerrestrialDS(void);
	Bool mValidateT2DS(void);
	Bool mValidateC2DS(void);
	void mCamDataPumpHandler(int event, Nat32 param);
	void mCamSearchStatus(Op_ProfileSearchStatus *TempSearchStatusInfo);
	void mCamStatusInfo(void);
	void mCamNITReceived(Op_ProfileNitData *TempNitData);
	void mCamTuneRequest(Op_ProfileTuneData *TempTuneData);
	void mCamTuneReply(void);
	void mUpdateTuneReplyData(OP_Status Status);
	void mCopyTuneDescriptorsLoop(Bool ValidLocation);
	int mGetDescriptorEntryLength(void);
	void mInitialise(void);
	void mGetLnbDetails(int lnb);
	void mStationFound();
	void mNoStationFound();
	void mGetCurrentTunerParams (HsvInstallationPTC *ptc);
	void mSetCharacterCode (void);
	
public:

	//IHsvPower
	virtual void Init(void);
	virtual void TurnOn(void);
	virtual void TurnOff(void);

	//IHsvSatellitePackageInstallation
	virtual FResult StartInstallation(int source, int lnb, int mode);
	virtual FResult StopInstallation(void);
	virtual int GetCurrentInstallationState (int *mode,int *state);
	virtual int GetNumberOfTvChannelsFound (int mode,int lnb);
	virtual int GetNumberofRadioChannelsFound(int mode,int lnb);
	virtual int GetNumberOfTvChannelsRemoved(int mode,int lnb);
	virtual int GetNumberofRadioChannelsRemoved(int mode,int lnb);
	virtual FResult WriteBarkerMuxData (void);
	virtual int GetNumberOfDigitalChannelsAdded(void);
	virtual int GetNumberOfDigitalChannelsRemoved(void);
	virtual int GetNumberOfDigitalChannelsMoved(void);
	virtual FResult LoadManualInstallationDefaultValues(void);
	virtual FResult StoreManualInstallationValues(void);
	virtual Bool SetManualInstallationAttributes(int attributeId,int value);
	virtual int GetAttribute(int mode,int attributeId);
	virtual int GetScanProgressStatus(int mode);
	virtual void GetSIDetails(HsvSDMSIDataValues *siValues);
	virtual FResult SetPostcode(Nat8 postcodeLen, Nat8 *postcode);
	virtual FResult StartTricolorRegionParsing ();
	virtual FResult SetTricolorRegionIndex (int index);
	virtual FResult GetTricolorRegionNames (Nat16 **names, int *len);

	//IHsvDigitalScanData
	virtual void GetPtcInfo (HsvInstallationPTC * ptc);
	virtual int GetInstallationVersion(void);
	virtual void GetPtcInfoForSdSd(HsvInstallationPTC * ptc);
	virtual void SyncComplete(void);
	
	//IHsvDigitalAcquisitionNotify
	virtual void OnDataAquired (Bool status);
	
	//IHsvSatelliteFrontEndNotify
	virtual void OnLockChanged(Bool lockState);
	virtual void OnBlindScanEnd(void);
	
	//IHsvSdmControlNotifyEx
	virtual void OnEvent(HsvDemux dmx,int eventid,int value);
	
	//ICesOperatorProfileNotify
	virtual void OnOpSearchStatus (Op_ProfileSearchStatus opStatus);
	virtual void OnOpStatusInfo(Op_ProfileStatusInfo StatusInfo);
	virtual void OnOpNIT(Op_ProfileNitData nitData);
	virtual void OnOpTune(Op_ProfileTuneData tuneData);

	//IHsvStreamNotify
	virtual void OnCompleted (HsvDestination dest,int spid);
	virtual void OnAdded (HsvDestination dest,int spid,int key1,int key2,int key3);
	virtual void OnChanged (HsvDestination dest,int spid,int key1,int key2,int key3,int eventid);
	virtual void OnRemoved (HsvDestination dest,int spid,int key1,int key2,int key3);
	

	//Constructor
	CHsvDvbsOpProfile_mScan()
	{
		satpkgins	= this;
		satfeN		= this;
		iscandata	= this;
		opinsN		= this;
		pow			= this;
		strapiN		= this;
		dataacqN		= this;
		ctrlN = this;
	}

	//Destructor
	virtual ~CHsvDvbsOpProfile_mScan()
	{
	}
	
	//Provides interfaces
	ProvidesInterface<IHsvSatellitePackageInstallation> satpkgins;	
	ProvidesInterface<IHsvSatelliteFrontEndNotify> satfeN;
	ProvidesInterface<IHsvDigitalScanData> iscandata;
	ProvidesInterface<ICesOperatorProfileNotify> opinsN;
	ProvidesInterface<IHsvPower> pow;
	ProvidesInterface<IHsvStreamNotify> strapiN;
	ProvidesInterface<IHsvDigitalAcquisitionNotify>	dataacqN;
	ProvidesInterface<IHsvSdmControlNotifyEx>	ctrlN;

	//Required interfaces
	RequiresInterface<IHsvCamDataParser>	camdataparser;
	RequiresInterface<IHsvSdmEnable>	camnitena;
	RequiresInterface<IHsvCountryIds>	cids;
	RequiresInterface<IHsvSdmControl2>	ctrl;
	RequiresInterface<IHsvEuropeDiversity2>	eurdiv;
	RequiresInterface<IHsvErrorCodeEx>	hsverr;
	RequiresInterface<IHsvDigitalAcquisition>	idataacq;
	RequiresInterface<IHsvSatelliteInstallationNotify>	insN;
	RequiresInterface<IHsvSatelliteInstallation>	ins;
	RequiresInterface<IHsvMediaControl>	mctl;
	RequiresInterface<ICesOperatorProfile>	opins;
	RequiresInterface<IPumpEngine>	pen;
	RequiresInterface<IPlfApiErrorIds>	plferrids;
	RequiresInterface<IPumpExSub>	pmp;
	RequiresInterface<IHsvInstallationSigStrength>	sigstr;
	RequiresInterface<IHsvStream>	strapi;
	RequiresInterface<IHsvWindowDestinationMap>	wnddest;
	RequiresInterface<IHsvSatelliteSettings>	idvbset;
	RequiresInterface<IHsvSatelliteFrontEnd>	satfeapi;
	RequiresInterface<IAppApiSystemSettings5> apsysset;
	RequiresInterface<IPlfApiSigStrengthMeas> sigstrmeas;
	RequiresInterface<IHsvPower>	iacqpow;
	RequiresInterface<IHsvPower>	isortpow;
};

#endif
