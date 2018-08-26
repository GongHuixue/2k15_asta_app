#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#ifndef __cplusplus

#include "../type/InstallationConstants.h"

#else

#include "InstallationConstants.h"

#endif

#define START_FREQUENCY (45*16)

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define MAX_PLP_IDS					(256)

#define COUNTRY (sysset_GetSystemCountry())
/* static variables */

typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

#ifndef __cplusplus

#else

#endif

Bool mUserSelectedMux;
static Bool s__mUserSelectedMux;
Bool mPlayStarted;
static Bool s__mPlayStarted;
int mScanPLPState,mDetectedPlpIds[MAX_PLP_IDS],mNumPLPIds,miT2PLPIDX;
static int s__mScanPLPState,s__mDetectedPlpIds[MAX_PLP_IDS],s__mNumPLPIds;
Nat16 mCurrentDecoder;
static Nat16 s__mCurrentDecoder;
HsvStreamPriority mHeirarchyValue;
static HsvStreamPriority s__mHeirarchyValue;
static const FunctionNat32 EventActionMatrix[][ConstEvMax];
void PumpHandler(int event, Nat32 param);
void FuncStartDtrInstallation(Nat32 freq);
void FuncStopDtrInstallation(Nat32  param);
void FuncDtrSdmStopped(Nat32  param);
void FuncDtrStationFound(Nat32  param);
void FuncDtrStationNotFound(Nat32  param);
void FuncDtrDataAvailable(Nat32  param);
void FuncDtrPMTCollected(Nat32  param);
void FuncSignalStrength(Nat32 param);
void FuncOnHierarchyModeDetected(Nat32 param);
void FuncOnMeasReady(Nat32  param);
void mInitialise(Nat32 freq);
void mStopSdm(HsvDemux dmx);
void mSetChannelDecoderAttributes(void);
void mSetTunerAttributes();
void mPlayService(int serviceid);
void mSetHeirarchyMux(int HeirarchyValue);
inline Bool mIsDvbt2CarrierDetected(void);
int mWaitForData(void);
inline Nat16 mGetChannelDecoder(void);
inline void mInitialiseDecoderParams(void);
int mGetChanBandwidth (int Band, int Country);
int mGetCorrectedBand(int Frequency, int Country);
tmFe_StreamPriority_t ConvertToPlatformStreamPriority(HsvStreamPriority inval);
int mConvertBandwidthToValue(tmFe_ChanBandwidth_t Bandwidth);
void module__init(void){
#ifndef __cplusplus

#else

#endif

#ifndef __cplusplus

#else

#endif

	mUserSelectedMux	=	s__mUserSelectedMux;
	mPlayStarted	=	s__mPlayStarted;
	mScanPLPState	=	s__mScanPLPState;
	memcpy((void*)mDetectedPlpIds,(void*)s__mDetectedPlpIds,sizeof(mDetectedPlpIds));
	mNumPLPIds	=	s__mNumPLPIds;
	mCurrentDecoder	=	s__mCurrentDecoder;
	mHeirarchyValue	=	s__mHeirarchyValue;
	miT2PLPIDX = -1;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef START_FREQUENCY
#undef START_FREQUENCY
#endif //START_FREQUENCY
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
#ifdef MAX_PLP_IDS
#undef MAX_PLP_IDS
#endif //MAX_PLP_IDS
#endif //LOCAL_UNDEFINES
