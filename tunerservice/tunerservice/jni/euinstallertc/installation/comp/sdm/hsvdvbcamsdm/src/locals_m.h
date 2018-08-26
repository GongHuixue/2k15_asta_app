#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#include <CamNit_ParserDef.h>

#define VALID_CAMLCN_RANGE(lcn)				((lcn >=0) &&(lcn <= 9999))	
#define	HEADER_PLUS_FIRST_LOOP_PRESENT(cookie)			(cookie == EnmTypeCamNITData)
#define GET_PARSE_TABLE_LEN(cookie)						((cookie == EnmTypeCamNITData)? (tableLen - 4) : (tableLen))	

#define div_ChannelNameLength  				(41)

#define srtdbids_CamNitLinkageInfo 			1

#define srtdbids_CamNitCableDS				1

#define srtdbids_CamNitTerrestrialDS		1

#define srtdbids_CamNitC2DS					1

#define srtdbids_CamNitT2DS					1

#define srtdbids_CamNitContentLabel			1

#define srtdbids_CamNitService				1

#define srtdb_Init(a) 1

#define srtdb_Insert(inst, pK, sK, tK, qK, data) 1

#define srtdb_GetNoOfRecords(inst) 1

#define srtdb_SearchOnPrimaryKey(inst, pK, frm, to) 1

#define srtdb_SearchOnKey(inst, pK, sK, tK, qK, index) 1

#define srtdb_QueryOnKey(inst, pK, sK, tK, qK, data) 1

#define srtdb_QueryOnIndex(inst, index, data) 1

#define srtdb_Update(inst, pK, sK, tK, qK, data) 1

#define srtdb_Delete(inst, pK, sK, tK, qK) 1

#define DEFAULT_CHAR_SET            (0) //Latin Alphabet - ISO8859-1 

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

/* Mapping to HsvGlobals using HsvConstellation */

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

Nat8 mModulation[7];
static Nat8 s__mModulation[7];
Bool mActive;
static Bool s__mActive;
Nat8 mBuffer[4*1024];
static Nat8 s__mBuffer[4*1024];
TypeCamNitParser CamNitParser;
static TypeCamNitParser s__CamNitParser;
Nat8 mcamCharCode;
static Nat8 s__mcamCharCode;
Bool mPrevPrivateDataSpecifierPresent;
static Bool s__mPrevPrivateDataSpecifierPresent;
void mInitCamNitCableDS(void);
void mInitCamNitTerrestrialDS(void);
void mInitCamNitC2DS(void);
void mInitCamNitT2DS(void);
void mInitCamNitContentLabel(void);
void mInitCamNitService(void);
void mInitCamNitLinkageInfo(void);
Nat8 mInterpretModulationValue(Nat8 *mod);
Nat32 mInterpretSymbolRate(Nat32 *symrate);
Nat32 mInterpretFrequencyValue(Nat32 *freq);
Nat8 mMapDVBTBandwidth(int bw);
void mPopulateCamNitCableDS(void);
void mPopulateCamNitTerrestrialDS(void);
void mPopulateCamNitC2DS(void);
void mPopulateCamNitT2DS(void);
void mPopulateCamNitContentLabel(void);
void mPopulateCamNitService(void);
void mPopulateCamNitLinkageInfo(void);
Bool mPopulateNIT(void);
Nat8 mGetLanguageId(Nat32 Language);
Nat8 mFindTableCode(Nat8* str);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	memcpy((void*)mModulation,(void*)s__mModulation,sizeof(mModulation));
	mActive	=	s__mActive;
	mcamCharCode = s__mcamCharCode;
	mPrevPrivateDataSpecifierPresent = s__mPrevPrivateDataSpecifierPresent;
	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
	CamNitParser	=	s__CamNitParser;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef VALID_CAMLCN_RANGE(lcn)
#undef VALID_CAMLCN_RANGE(lcn)
#endif //VALID_CAMLCN_RANGE(lcn)
#ifdef div_ChannelNameLength
#undef div_ChannelNameLength
#endif //div_ChannelNameLength
#ifdef srtdbids_CamNitLinkageInfo
#undef srtdbids_CamNitLinkageInfo
#endif //srtdbids_CamNitLinkageInfo
#ifdef srtdbids_CamNitCableDS
#undef srtdbids_CamNitCableDS
#endif //srtdbids_CamNitCableDS
#ifdef srtdbids_CamNitTerrestrialDS
#undef srtdbids_CamNitTerrestrialDS
#endif //srtdbids_CamNitTerrestrialDS
#ifdef srtdbids_CamNitC2DS
#undef srtdbids_CamNitC2DS
#endif //srtdbids_CamNitC2DS
#ifdef srtdbids_CamNitT2DS
#undef srtdbids_CamNitT2DS
#endif //srtdbids_CamNitT2DS
#ifdef srtdbids_CamNitContentLabel
#undef srtdbids_CamNitContentLabel
#endif //srtdbids_CamNitContentLabel
#ifdef srtdbids_CamNitService
#undef srtdbids_CamNitService
#endif //srtdbids_CamNitService
#ifdef DEFAULT_CHAR_SET
#undef DEFAULT_CHAR_SET
#endif //DEFAULT_CHAR_SET
#ifdef srtdb_Init(a)
#undef srtdb_Init(a)
#endif //srtdb_Init(a)
#ifdef srtdb_Insert(inst,
#undef srtdb_Insert(inst,
#endif //srtdb_Insert(inst,
#ifdef srtdb_GetNoOfRecords(inst)
#undef srtdb_GetNoOfRecords(inst)
#endif //srtdb_GetNoOfRecords(inst)
#ifdef srtdb_SearchOnPrimaryKey(inst,
#undef srtdb_SearchOnPrimaryKey(inst,
#endif //srtdb_SearchOnPrimaryKey(inst,
#ifdef srtdb_SearchOnKey(inst,
#undef srtdb_SearchOnKey(inst,
#endif //srtdb_SearchOnKey(inst,
#ifdef srtdb_QueryOnKey(inst,
#undef srtdb_QueryOnKey(inst,
#endif //srtdb_QueryOnKey(inst,
#ifdef srtdb_QueryOnIndex(inst,
#undef srtdb_QueryOnIndex(inst,
#endif //srtdb_QueryOnIndex(inst,
#ifdef srtdb_Update(inst,
#undef srtdb_Update(inst,
#endif //srtdb_Update(inst,
#ifdef srtdb_Delete(inst,
#undef srtdb_Delete(inst,
#endif //srtdb_Delete(inst,
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
