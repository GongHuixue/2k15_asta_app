#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#include <stdio.h>

#define WINDOWID            			(wnddest_GetWindowId(HsvMain))

#define CABLE_MEDIUM    				(rins_GetMedium() == rins_Cable)

#define AUTO_MODE       (rins_InstallationModeAutomatic)
#define ANTENNA_MEDIUM  				((rins_GetMedium() == rins_Terrestrial) || (idvbset_GetAttribute(AUTO_MODE,rins_AttributeNetworkOperator)  == rins_DvbTCAM))

#define CURRENT_MODE    				(rins_GetInstallationMode())

#define TURNED_ON						(mModuleLifeCycle == TurnedOn)

#define START_FREQUENCY 				(45 * 16)

#define END_FREQUENCY   				(863 * 16)

#define AUTO_CAM_MODE					(1)

#define BACKGROUND_CAM_MODE				(2)

#define ACQUIRE_DSD						(0)

#define GET_DSD							(1)

#define MAX_SERVICE_TYPES_SUPPORTED		(17)

#define DVBC_DELIVERY_TAG				(0x44)

#define DVBT_DELIVERY_TAG				(0x5a)

#define DELIVERY_EXTN_TAG				(0x7F)

#define DVBT2_DELIVERY_OFFSET_TAG		(0x04)

#define DVBC_DESCRIPTOR_ENTRY_LENGTH	(11)					/* Length of one location (pointing to a frequency..) in the DSD */

#define DVBT_DESCRIPTOR_ENTRY_LENGTH	(11)

#define DVBT2_DESCRIPTOR_ENTRY_LENGTH	(12)

#define AUTO_INSTALL					(GET_CAM_INS_MODE == AUTO_CAM_MODE)

#define VALID_EVENT(Event)      		((Event >= EvStart) && (Event < EvMax))

#define VALID_STATE(state)      		((state >= StIdle) && (state < StMax))

#define GET_INS_STATE		    		(mCamInstStatus.State)

#define SET_INS_STATE(state)    		(mCamInstStatus.State = state)

#define GET_CAM_INS_MODE		    	(mCamInstStatus.Mode)

#define SET_CAM_INS_MODE(mode)    		(mCamInstStatus.Mode = mode)

#define VALID_CAM_INSTALL_MODE(mode)	(mode == rins_InstallationModeCam)

#define SERVICE_TYPES_SUPPORTED			("0x010203040506100A0C11161718191C2021")

#define TUNING_REQUIRED					(AUTO_INSTALL || (REFRESH_REQUEST_FLAG != 0))

#define ADVANCE_TUNING_REQUIRED   	 		(REFRESH_REQUEST_FLAG == 1)
#define URGENT_TUNING_REQUIRED   	 		(REFRESH_REQUEST_FLAG == 2)

#define SCHEDULE_UPDATE					(REFRESH_REQUEST_FLAG == 3)

#define GET_CAM_DELIVERY_HINT			(mStatusInfo.op_Status.Delivery_System_Hint)

#define CAM_INITIALISED					(mStatusInfo.op_Status.Initialised_Flag)

#define ENTITLEMENT_CHANGE_REQUESTED	(mStatusInfo.op_Status.Entitlement_Change_Flag)

#define CAM_UPDATED_NIT_VERSION			(mStatusInfo.op_Status.NIT_Version)

#define CAM_LAST_NIT_VERSION			(idvbset_GetAttribute(AUTO_MODE, rins_AttributeCamNITVersion))

#define PROFILE_INFO_VALID				(mStatusInfo.op_Info.info_Valid == 1)

#define REFRESH_REQUEST_FLAG			(mStatusInfo.op_Status.Refresh_Request_Flag)

#define NIT_REQUIRED(version)			((mStatusInfo.op_Status.Profile_Type == OP_PROFILE_TYPE_1) && 										\
										 ((CAM_INITIALISED == FALSE) || (version != CAM_LAST_NIT_VERSION) || ENTITLEMENT_CHANGE_REQUESTED))

#define CURRENT_TS_INDEX				(mCamDSDesc.CurrentTsIndex)

#define CURRENT_RUNNING_DSD_INDEX		(mCamDSDesc.TsParam[CURRENT_TS_INDEX].CurrentDSDIndex)

#define CURRENT_DSD_TYPE    		    (mCamDSDesc.TsParam[CURRENT_TS_INDEX].DSDesc[CURRENT_RUNNING_DSD_INDEX].DSDType)

#define CURRENT_SYMBOL_RATE    		    (mCamDSDesc.TsParam[CURRENT_TS_INDEX].DSDesc[CURRENT_RUNNING_DSD_INDEX].SymbolRate)

#define CURRENT_FREQUENCY      			(mCamDSDesc.TsParam[CURRENT_TS_INDEX].DSDesc[CURRENT_RUNNING_DSD_INDEX].Frequency)

#define CURRENT_MODULATION  			(mCamDSDesc.TsParam[CURRENT_TS_INDEX].DSDesc[CURRENT_RUNNING_DSD_INDEX].Modulation)

#define CURRENT_BANDWIDTH    		    (mCamDSDesc.TsParam[CURRENT_TS_INDEX].DSDesc[CURRENT_RUNNING_DSD_INDEX].Bandwidth)

#define CURRENT_STREAM_PRIORITY    		(mCamDSDesc.TsParam[CURRENT_TS_INDEX].DSDesc[CURRENT_RUNNING_DSD_INDEX].Priority)

#define CURRENT_PLP_ID    		    	(mCamDSDesc.TsParam[CURRENT_TS_INDEX].DSDesc[CURRENT_RUNNING_DSD_INDEX].PLP_Id)
#define CAM_CHAR_CODE_TYPE                (mStatusInfo.op_Info.character_Code_Table)
#define CAM_CHAR_CODE_BYTE2                (mStatusInfo.op_Info.character_Code_Table_2)
#define CAM_CHAR_CODE_BYTE3                (mStatusInfo.op_Info.character_Code_Table_3)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

/***** Enums & Data Structures Definition   *****/

typedef enum
{
    StIdle,
    StInit,
    StTunerWait,
    StStrapiWait,
    StMax
}InsStates;
typedef enum
{
    EvStart,
    EvStop,
	EvStationFound,
    EvMakeDecision,
    EvDataAvailable,
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
    int         State;
	int			Mode;
}InstStatus;
typedef struct
{
    Nat8 NumOfTs;
    int CurrentTsIndex; 
    struct 
    {
        Nat16 ONID;
        Nat16 TsId;
        Nat8  NumOfDSD;
        int   CurrentDSDIndex;
        struct
        {
			Nat8  DSDType;
            Nat32 SymbolRate;
            Nat32 Frequency;
            Nat16 SystemId;
			Nat8  Modulation;
			Nat8  PLP_Id;
			Nat8  Bandwidth;			
			Nat8  Priority;
        }DSDesc[MAX_DSD_PER_TS];
	}TsParam[MAX_MUXES_PER_NTK_FOR_CAM];
}t_CamDSDesc;
typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

InstStatus mCamInstStatus;
static InstStatus s__mCamInstStatus;
t_CamDSDesc mCamDSDesc;
static t_CamDSDesc s__mCamDSDesc;
Pump mScanPump,mCamDataPump;
static Pump s__mScanPump,s__mCamDataPump;
Op_ProfileStatusInfo mTempStatusInfo;
static Op_ProfileStatusInfo s__mTempStatusInfo;
Op_ProfileStatusInfo mStatusInfo;
static Op_ProfileStatusInfo s__mStatusInfo;
Op_ProfileTuneData *mTempTuneDataPtr;
static Op_ProfileTuneData *s__mTempTuneDataPtr;
Op_Search_Settings mSearchSettings;
static Op_Search_Settings s__mSearchSettings;
Op_Tune_Status *mTempTuneReplyDataPtr;
static Op_Tune_Status *s__mTempTuneReplyDataPtr;
ModuleLifeCycle mModuleLifeCycle;
static ModuleLifeCycle s__mModuleLifeCycle;
static const FunctionNat32 EventActionMatrix[][StMax];
void mScanPumpHandler(int event, Nat32 param);
void FuncStartInstallation(Nat32 Param);
void FuncStopInstallation(Nat32 Param);
void FuncStationFound(Nat32 Param);
void FuncDataAvailable(Nat32 Param);
void FuncMakeDecision(Nat32 param);
void mSelectDecoder(void);
void mSetTunerAttributes(void);
void mStopSdm(HsvDemux dmx);
Bool mGetNextDSD(void);
void mGetPTCInfo(HsvInstallationPTC *ptc, Nat16 OnId, Nat16 TsId);
Bool mLoadStrapiData(void);
Bool mLoadDSDFromStrapi(int hsvspid, Address TempDSDesc);
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
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mCamInstStatus	=	s__mCamInstStatus;
	mCamDSDesc	=	s__mCamDSDesc;
	mScanPump	=	s__mScanPump;
	mCamDataPump	=	s__mCamDataPump;
	mStatusInfo	=	s__mStatusInfo;
	mTempStatusInfo = s__mTempStatusInfo;
	mTempTuneDataPtr	=	s__mTempTuneDataPtr;
	mSearchSettings	=	s__mSearchSettings;
	mTempTuneReplyDataPtr	=	s__mTempTuneReplyDataPtr;
	mModuleLifeCycle	=	s__mModuleLifeCycle;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef CABLE_MEDIUM
#undef CABLE_MEDIUM
#endif //CABLE_MEDIUM
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef ANTENNA_MEDIUM
#undef ANTENNA_MEDIUM
#endif //ANTENNA_MEDIUM
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef CAM_CHAR_CODE_TYPE
#undef CAM_CHAR_CODE_TYPE
#endif //CAM_CHAR_CODE_TYPE
#ifdef CAM_CHAR_CODE_BYTE2
#undef CAM_CHAR_CODE_BYTE2
#endif //CAM_CHAR_CODE_BYTE2
#ifdef CAM_CHAR_CODE_BYTE3
#undef CAM_CHAR_CODE_BYTE3
#endif //CURRENT_MODE
#ifdef TURNED_ON
#undef TURNED_ON
#endif //TURNED_ON
#ifdef START_FREQUENCY
#undef START_FREQUENCY
#endif //START_FREQUENCY
#ifdef END_FREQUENCY
#undef END_FREQUENCY
#endif //END_FREQUENCY
#ifdef AUTO_CAM_MODE
#undef AUTO_CAM_MODE
#endif //AUTO_CAM_MODE
#ifdef BACKGROUND_CAM_MODE
#undef BACKGROUND_CAM_MODE
#endif //BACKGROUND_CAM_MODE
#ifdef ACQUIRE_DSD
#undef ACQUIRE_DSD
#endif //ACQUIRE_DSD
#ifdef GET_DSD
#undef GET_DSD
#endif //GET_DSD
#ifdef MAX_SERVICE_TYPES_SUPPORTED
#undef MAX_SERVICE_TYPES_SUPPORTED
#endif //MAX_SERVICE_TYPES_SUPPORTED
#ifdef DVBC_DELIVERY_TAG
#undef DVBC_DELIVERY_TAG
#endif //DVBC_DELIVERY_TAG
#ifdef DVBT_DELIVERY_TAG
#undef DVBT_DELIVERY_TAG
#endif //DVBT_DELIVERY_TAG
#ifdef DELIVERY_EXTN_TAG
#undef DELIVERY_EXTN_TAG
#endif //DELIVERY_EXTN_TAG
#ifdef DVBT2_DELIVERY_OFFSET_TAG
#undef DVBT2_DELIVERY_OFFSET_TAG
#endif //DVBT2_DELIVERY_OFFSET_TAG
#ifdef DVBC_DESCRIPTOR_ENTRY_LENGTH
#undef DVBC_DESCRIPTOR_ENTRY_LENGTH
#endif //DVBC_DESCRIPTOR_ENTRY_LENGTH
#ifdef DVBT_DESCRIPTOR_ENTRY_LENGTH
#undef DVBT_DESCRIPTOR_ENTRY_LENGTH
#endif //DVBT_DESCRIPTOR_ENTRY_LENGTH
#ifdef DVBT2_DESCRIPTOR_ENTRY_LENGTH
#undef DVBT2_DESCRIPTOR_ENTRY_LENGTH
#endif //DVBT2_DESCRIPTOR_ENTRY_LENGTH
#ifdef AUTO_INSTALL
#undef AUTO_INSTALL
#endif //AUTO_INSTALL
#ifdef VALID_EVENT(Event)
#undef VALID_EVENT(Event)
#endif //VALID_EVENT(Event)
#ifdef VALID_STATE(state)
#undef VALID_STATE(state)
#endif //VALID_STATE(state)
#ifdef GET_INS_STATE
#undef GET_INS_STATE
#endif //GET_INS_STATE
#ifdef SET_INS_STATE(state)
#undef SET_INS_STATE(state)
#endif //SET_INS_STATE(state)
#ifdef GET_CAM_INS_MODE
#undef GET_CAM_INS_MODE
#endif //GET_CAM_INS_MODE
#ifdef SET_CAM_INS_MODE(mode)
#undef SET_CAM_INS_MODE(mode)
#endif //SET_CAM_INS_MODE(mode)
#ifdef VALID_CAM_INSTALL_MODE(mode)
#undef VALID_CAM_INSTALL_MODE(mode)
#endif //VALID_CAM_INSTALL_MODE(mode)
#ifdef SERVICE_TYPES_SUPPORTED
#undef SERVICE_TYPES_SUPPORTED
#endif //SERVICE_TYPES_SUPPORTED
#ifdef TUNING_REQUIRED
#undef TUNING_REQUIRED
#endif //TUNING_REQUIRED
#ifdef URGENT_TUNING_REQUIRED
#undef URGENT_TUNING_REQUIRED
#endif //URGENT_TUNING_REQUIRED
#ifdef ADVANCE_TUNING_REQUIRED
#undef ADVANCE_TUNING_REQUIRED
#endif //ADVANCE_TUNING_REQUIRED
#ifdef GET_CAM_DELIVERY_HINT
#undef GET_CAM_DELIVERY_HINT
#endif //GET_CAM_DELIVERY_HINT
#ifdef CAM_INITIALISED
#undef CAM_INITIALISED
#endif //CAM_INITIALISED
#ifdef ENTITLEMENT_CHANGE_REQUESTED
#undef ENTITLEMENT_CHANGE_REQUESTED
#endif //ENTITLEMENT_CHANGE_REQUESTED
#ifdef CAM_UPDATED_NIT_VERSION
#undef CAM_UPDATED_NIT_VERSION
#endif //CAM_UPDATED_NIT_VERSION
#ifdef PROFILE_INFO_VALID
#undef PROFILE_INFO_VALID
#endif //PROFILE_INFO_VALID
#ifdef REFRESH_REQUEST_FLAG
#undef REFRESH_REQUEST_FLAG
#endif //REFRESH_REQUEST_FLAG
#ifdef NIT_REQUIRED(version)
#undef NIT_REQUIRED(version)
#endif //NIT_REQUIRED(version)
#ifdef CURRENT_TS_INDEX
#undef CURRENT_TS_INDEX
#endif //CURRENT_TS_INDEX
#ifdef CURRENT_RUNNING_DSD_INDEX
#undef CURRENT_RUNNING_DSD_INDEX
#endif //CURRENT_RUNNING_DSD_INDEX
#ifdef CURRENT_DSD_TYPE
#undef CURRENT_DSD_TYPE
#endif //CURRENT_DSD_TYPE
#ifdef CURRENT_SYMBOL_RATE
#undef CURRENT_SYMBOL_RATE
#endif //CURRENT_SYMBOL_RATE
#ifdef CURRENT_FREQUENCY
#undef CURRENT_FREQUENCY
#endif //CURRENT_FREQUENCY
#ifdef CURRENT_MODULATION
#undef CURRENT_MODULATION
#endif //CURRENT_MODULATION
#ifdef CURRENT_BANDWIDTH
#undef CURRENT_BANDWIDTH
#endif //CURRENT_BANDWIDTH
#ifdef CURRENT_STREAM_PRIORITY
#undef CURRENT_STREAM_PRIORITY
#endif //CURRENT_STREAM_PRIORITY
#ifdef CURRENT_PLP_ID
#undef CURRENT_PLP_ID
#endif //CURRENT_PLP_ID
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif //CLASSSCOPE
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FPCALL(f)
#undef FPCALL(f)
#endif //FPCALL(f)
#ifdef FNADDR(f)
#undef FNADDR(f)
#endif //FNADDR(f)
#endif //LOCAL_UNDEFINES
