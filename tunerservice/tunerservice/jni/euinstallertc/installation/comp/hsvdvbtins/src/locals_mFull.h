#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#ifndef __cplusplus

#else

#endif
/*
#define START_FREQUENCY (45*16)

#define END_FREQUENCY   (863*16)
  */
/* ANEESH: Changing this for testing in SoC */
#define START_FREQUENCY (50*16)

#define END_FREQUENCY   (866*16)

#define START_FREQUENCY_470MHZ (470*16)

#define START_FREQUENCY_174MHZ (174*16)

#define START_FREQUENCY_44MHZ (44*16)

#define COUNTRY (sysset_GetSystemCountry())
#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define MAX_PLP_IDS					(256)

typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
#ifndef __cplusplus

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

#ifndef __cplusplus

#else

#endif

int mScanPLPState,mInstalledPLPIds,mDetectedPlpIds[MAX_PLP_IDS],mNumPLPIds;
static int s__mScanPLPState,s__mInstalledPLPIds,s__mDetectedPlpIds[MAX_PLP_IDS],s__mNumPLPIds;
Nat16 mCurrentDecoder;
static Nat16 s__mCurrentDecoder;
static const FunctionNat32 EventActionMatrix[][10];
void PumpHandler(int event, Nat32 param);
void FuncStartInstallation(Nat32 param);
void FuncStopInstallation(Nat32 param);
void FuncSdmStopped(Nat32 param);
void FuncStationFound(Nat32 param);
void FuncStationNotFound(Nat32 param);
void FuncDataAvailable(Nat32 param);
void FuncMakeDecision(Nat32 param);
void FuncOnHierarchyModeDetected(Nat32 param);
void FuncOnMeasReady(Nat32  param);
void mInitialise(Nat32 freq);
void mStopSdm(HsvDemux dmx);
void mSetChannelDecoderAttributes(void);
void mSetTunerAttributes(void);
void mGetBandScan(Nat32 *StartFrequency, Nat32 *EndFrequency);
void mGetHierarchyMUX(int *HierarchyValue);
Bool mAllMUXsInHierarchyScanned(void);
void mSetHeirarchyMux(int HeirarchyValue);
inline Bool mIsDvbt2CarrierDetected(void);
void mSetHierarchyMode(void);

int mWaitForData(void);
#ifndef __cplusplus

#endif

inline Nat16 mGetChannelDecoder(void);
inline void mInitialiseDecoderParams(void);
void module__init(void){
#ifndef __cplusplus

#else

#endif

#ifndef __cplusplus

#else

#endif

	mScanPLPState	=	s__mScanPLPState;
	mInstalledPLPIds	=	s__mInstalledPLPIds;
	memcpy((void*)mDetectedPlpIds,(void*)s__mDetectedPlpIds,sizeof(mDetectedPlpIds));
	mNumPLPIds	=	s__mNumPLPIds;
	mCurrentDecoder	=	s__mCurrentDecoder;
#ifndef __cplusplus

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef START_FREQUENCY
#undef START_FREQUENCY
#endif //START_FREQUENCY
#ifdef END_FREQUENCY
#undef END_FREQUENCY
#endif //END_FREQUENCY
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
