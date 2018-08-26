#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <Pat_Parser.h>

#include <Pmt_Parser.h>

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#ifndef __cplusplus

#define CLASSSCOPE

#define FPCALL(f) (* f)

#else

#define FPCALL(f) (this->* f)

#endif

#define FNADDR(f) (& CLASSSCOPE f)

#define	PAT_PID_VALUE		(0x00)

#define	PAT_TABLE_ID		(0x00)

#define	PMT_TABLE_ID		(0x02)

#define	INVALID_PID			(0x1FFF)

#define	IsValidPid(x)		(x != 0x1FFF)

#define	IsInvalidPid(x)		(x == 0x1FFF)

#define ISO_IEC_11172_VIDEO_STREAM_TYPE         (Hsv_ISOIEC_11172_STREAM_TYPE_VIDEO)

#define ISO_IEC_13818_2_VIDEO_STREAM_TYPE       (Hsv_ISOIEC_13818_2_STREAM_TYPE_VIDEO)

#define ISO_IEC_11172_2_VIDEO_STREAM_TYPE       (Hsv_ISOIEC_11172_2_STREAM_TYPE_VIDEO)

#define ISO_IEC_13818_6_STREAM_TYPE_B           (Hsv_ISOIEC_13818_6_STREAM_TYPE_B)

#define H264_VIDEO_STREAM_TYPE					(Hsv_H264_STREAM_TYPE_VIDEO)

#define ISO_IEC_11172_AUDIO_STREAM_TYPE     (Hsv_ISOIEC_11172_STREAM_TYPE_AUDIO)

#define ISO_IEC_13818_3_AUDIO_STREAM_TYPE   (Hsv_ISOIEC_13818_3_STREAM_TYPE_AUDIO)

#define ATSC_A52_AC3_STREAM_TYPE            (Hsv_ATSC_A52_STREAM_TYPE_AC3)

#define MPEG4_HEAAC_STREAM_TYPE				(Hsv_MPEG4_STREAM_TYPE_HEAAC)

#define MPEG4_AAC_STREAM_TYPE				(Hsv_MPEG4_STREAM_TYPE_AAC)

#define MPEG4_AC3PLUS_STREAM_TYPE			(6)

#define SGT_REF_STREAM_TYPE					(5)


#define	IsValidVideoStreamType(x)		((x == ISO_IEC_11172_VIDEO_STREAM_TYPE) | \
										 (x == ISO_IEC_13818_2_VIDEO_STREAM_TYPE) | \
										 (x == ISO_IEC_11172_2_VIDEO_STREAM_TYPE) | \
										 (x == H264_VIDEO_STREAM_TYPE) )

#define	IsValidAudioStreamType(x)		((x == ISO_IEC_11172_AUDIO_STREAM_TYPE) | \
										 (x == ISO_IEC_13818_3_AUDIO_STREAM_TYPE) | \
										 (x == ATSC_A52_AC3_STREAM_TYPE) | \
										 (x == MPEG4_HEAAC_STREAM_TYPE) | \
										 (x == MPEG4_AAC_STREAM_TYPE) | \
										 (x == MPEG4_AC3PLUS_STREAM_TYPE) )

#define	MAX_PMT_FILTERS		(5)


#define	VALID_EVENT(x)		((x<EvMax)	? TRUE	: FALSE)

#define	VALID_STATE(x)		((x<StMax)	? TRUE	: FALSE)

#define	SET_STATE(x)		(mStatus.CurState = x)

#define	CUR_STATE			(mStatus.CurState)

#define	SET_CUR_DMX(x)		(mStatus.CurDemux = x)

#define	CUR_DMX				(mStatus.CurDemux)

#define	MAX_PMT_FILTERS_SUPPORTED	(5 /*sdmdiv_MaxSimplePmtFilterSupported*/)

#define	MAX_POSSIBLE_PROGRAMS		(100 /*sdmdiv_MaxSimplePmtSupported*/)

#define	IsValidDemux(Dmx)	((Dmx<HsvDmxLast) ? TRUE : FALSE)

#define	PAT_COLLECTION_TIMEOUT	(3000)

#define	MIN(a,b)			((a<b) ? a : b)

#define	SIMPLE_PMT_SORTEDTABLE_ID(Dmx)		((Dmx==HsvDmxMain) ? srtdbids_SimplePmtMain : srtdbids_SimplePmtAux)

#define	INVALID_SRTDB_KEY	(0xFFFF)

#define IGNORE_STRAPI     0x01
#define FREESAT_TUNNELLED_DATA_DESCRIPTOR		(0xD0)
#define FREESAT_MAX_TUNNELLED_DATA_DESC_COUNT		(130)
#define FREESAT_ALT_TUNNELLED_DATA_DESCRIPTOR		(0xD1)
#define FREESAT_MAX_ALT_TUNNELLED_DATA_DESC_COUNT		(25)
#define STREAM_IDENTIFIER_DESCRIPTOR			(0x52)
#define MAX_STREAM_IDENTIFIER_DESCRIPTOR_PER_LOOP			(5)
#define PRIVATE_DATA_INDICATOR_DESCRIPTOR		(0x0F)
#define PRIVATE_DATA_SPECIFIER_DESCRIPTOR			(0x5F)
#define AC3_DESCRIPTOR									(0x6A)
#define FREESAT_PDSD_VALUE 	0x46534154

typedef enum {
	StIdle,
	StWaitPat,
	StWaitPmt,
	StMax
} States;
typedef enum {
	EvStart,
	EvPatCollected,
	EvPatNotCollected,
	EvPmtCollected,
	EvPmtTimeout,
	EvStop,
	EvMax
} Events;
typedef void (CLASSSCOPE *FunctionNat32)(Nat32);
typedef struct _mpegAcqStatus {
	int		CurState;
	HsvDemux	CurDemux;
	Nat16	CurrentPmtRequestIndex;
	Nat16	NumCollectedPmts;
} MpegAcqStatus;
typedef struct HsvPatSection
{
    int                 NumPrograms;
    Nat16               ProgramNumber[MAX_POSSIBLE_PROGRAMS];
    Nat16               ProgramMapPid[MAX_POSSIBLE_PROGRAMS];
} HsvPatSection;
typedef struct PatTableData
{
    Nat32               PatSubscriptionId;
    Bool                TablesInitialized;                        /* Flag which indicates if the tables corresponding to a demux have been initialized or not */
    Bool                PatSubscriptionStarted;
    Bool                PmtAcquisitionComplete;
    HsvPatSection       patsec;
} PatTableData;
typedef	struct HsvSimplePmtSection
{
	Nat16				ServiceId;
	Nat16				VideoPid;
	Nat16				AudioPid;
	Nat16				PcrPid;
	Nat16				SgtPid;
	Nat16				VideoStreamType;
	Nat16				AudioStreamType;
} HsvSimplePmtSection;
typedef struct PmtTableData
{
	Nat32				PmtSubscriptionId;
	Bool				TablesInitialized;
	Bool				PmtSubscriptionStarted;
	HsvSimplePmtSection	pmtsec;
} PmtTableData;
#ifdef __cplusplus

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

static const char MpegAcqEventNames[EvMax+1][32];
Pump mPump;
static Pump s__mPump;
Pump NoDataPump;
static Pump s__NoDataPump;
PatTableData ProgramTables[HsvDmxLast];
static PatTableData s__ProgramTables[HsvDmxLast];
PmtTableData PmtTables [HsvDmxLast][MAX_PMT_FILTERS_SUPPORTED];
static PmtTableData s__PmtTables [HsvDmxLast][MAX_PMT_FILTERS_SUPPORTED];
MpegAcqStatus mStatus;
static MpegAcqStatus s__mStatus;
Nat8 mBuffer[16*1024];
static Nat8 s__mBuffer[16*1024];
FunctionNat32 EventActionMatrix[EvMax][StMax];
static FunctionNat32 s__EventActionMatrix[EvMax][StMax];
int mFreesatServiceId;
static int s__mFreesatServiceId;

#ifdef __cplusplus

#endif

void PumpHandler(int event, Nat32 param);
void FuncStartPatCollection (Nat32 Param);
void FuncProcessPat (Nat32 Param);
void FuncPatTimeout (Nat32 Param);
void FuncProcessPmt (Nat32 Param);
void FuncPmtTimeout (Nat32 Param);
void FuncStopCollection (Nat32 Param);
void NoDataAvailableHandler( int dmx, Nat32 eventmask);
void mInitialize (Nat32 Param);
void mCollectPat (Nat32 Param);
void mStopPat (int Dmx);
void mCollectPmt (int FilterIndex, Nat16 ServiceId, Nat16 PmtPid);
void mStopPmt (int Dmx, int FilterIndex);
Bool mPopulateSimplePat (HsvDemux dmx , Address Ptr, int code );
Bool mPopulateSimplePmt ( HsvDemux dmx , Address Ptr, int code );
Bool mPopulateFreesatTunnelledInfo(HsvDemux dmx , Address Ptr, int code );
void InitSimplePmtInfo (int Dmx);
void InitFreesatTunnelledInfo(int Dmx);
void mUpdateStrapiWithSimplePmt (int FilterIndex);
Bool ipop_PopulatePAT ( HsvDemux dmx , Address ProgramAssocationTable, int code );
Bool ipop_PopulatePMT ( HsvDemux dmx , Address ProgramMapTable, int code );
Bool Pat_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
Bool Pmt_Parser_Parser( HsvDestination   dest,  Nat32   cookie, int code, int primarySectionSize, Nat8 * PrimarySectionStartAddress, int secondarySectionSize,  Nat8 * SecondarySectionStartAddress, HsvSectionCrcStatus crc );
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mPump	=	s__mPump;
	NoDataPump	=	s__NoDataPump;
	memcpy((void*)ProgramTables,(void*)s__ProgramTables,sizeof(ProgramTables));
	memcpy((void*)PmtTables,(void*)s__PmtTables,sizeof(PmtTables));
	mStatus	=	s__mStatus;
	memcpy((void*)mBuffer,(void*)s__mBuffer,sizeof(mBuffer));
	memcpy((void*)EventActionMatrix,(void*)s__EventActionMatrix,sizeof(EventActionMatrix));
	mFreesatServiceId = s__mFreesatServiceId;
#ifdef __cplusplus

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
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
#ifdef PAT_PID_VALUE
#undef PAT_PID_VALUE
#endif //PAT_PID_VALUE
#ifdef PAT_TABLE_ID
#undef PAT_TABLE_ID
#endif //PAT_TABLE_ID
#ifdef PMT_TABLE_ID
#undef PMT_TABLE_ID
#endif //PMT_TABLE_ID
#ifdef INVALID_PID
#undef INVALID_PID
#endif //INVALID_PID
#ifdef IsValidPid(x)
#undef IsValidPid(x)
#endif //IsValidPid(x)
#ifdef IsInvalidPid(x)
#undef IsInvalidPid(x)
#endif //IsInvalidPid(x)
#ifdef ISO_IEC_11172_VIDEO_STREAM_TYPE
#undef ISO_IEC_11172_VIDEO_STREAM_TYPE
#endif //ISO_IEC_11172_VIDEO_STREAM_TYPE
#ifdef ISO_IEC_13818_2_VIDEO_STREAM_TYPE
#undef ISO_IEC_13818_2_VIDEO_STREAM_TYPE
#endif //ISO_IEC_13818_2_VIDEO_STREAM_TYPE
#ifdef ISO_IEC_11172_2_VIDEO_STREAM_TYPE
#undef ISO_IEC_11172_2_VIDEO_STREAM_TYPE
#endif //ISO_IEC_11172_2_VIDEO_STREAM_TYPE
#ifdef ISO_IEC_13818_6_STREAM_TYPE_B
#undef ISO_IEC_13818_6_STREAM_TYPE_B
#endif //ISO_IEC_13818_6_STREAM_TYPE_B
#ifdef H264_VIDEO_STREAM_TYPE
#undef H264_VIDEO_STREAM_TYPE
#endif //H264_VIDEO_STREAM_TYPE
#ifdef ISO_IEC_11172_AUDIO_STREAM_TYPE
#undef ISO_IEC_11172_AUDIO_STREAM_TYPE
#endif //ISO_IEC_11172_AUDIO_STREAM_TYPE
#ifdef ISO_IEC_13818_3_AUDIO_STREAM_TYPE
#undef ISO_IEC_13818_3_AUDIO_STREAM_TYPE
#endif //ISO_IEC_13818_3_AUDIO_STREAM_TYPE
#ifdef ATSC_A52_AC3_STREAM_TYPE
#undef ATSC_A52_AC3_STREAM_TYPE
#endif //ATSC_A52_AC3_STREAM_TYPE
#ifdef MPEG4_HEAAC_STREAM_TYPE
#undef MPEG4_HEAAC_STREAM_TYPE
#endif //MPEG4_HEAAC_STREAM_TYPE
#ifdef MPEG4_AAC_STREAM_TYPE
#undef MPEG4_AAC_STREAM_TYPE
#endif //MPEG4_AAC_STREAM_TYPE
#ifdef MPEG4_AC3PLUS_STREAM_TYPE
#undef MPEG4_AC3PLUS_STREAM_TYPE
#endif //MPEG4_AC3PLUS_STREAM_TYPE
#ifdef IsValidVideoStreamType(x)
#undef IsValidVideoStreamType(x)
#endif //IsValidVideoStreamType(x)
#ifdef IsValidAudioStreamType(x)
#undef IsValidAudioStreamType(x)
#endif //IsValidAudioStreamType(x)
#ifdef MAX_PMT_FILTERS
#undef MAX_PMT_FILTERS
#endif //MAX_PMT_FILTERS
#ifdef VALID_EVENT(x)
#undef VALID_EVENT(x)
#endif //VALID_EVENT(x)
#ifdef VALID_STATE(x)
#undef VALID_STATE(x)
#endif //VALID_STATE(x)
#ifdef SET_STATE(x)
#undef SET_STATE(x)
#endif //SET_STATE(x)
#ifdef CUR_STATE
#undef CUR_STATE
#endif //CUR_STATE
#ifdef SET_CUR_DMX(x)
#undef SET_CUR_DMX(x)
#endif //SET_CUR_DMX(x)
#ifdef CUR_DMX
#undef CUR_DMX
#endif //CUR_DMX
#ifdef MAX_PMT_FILTERS_SUPPORTED
#undef MAX_PMT_FILTERS_SUPPORTED
#endif //MAX_PMT_FILTERS_SUPPORTED
#ifdef MAX_POSSIBLE_PROGRAMS
#undef MAX_POSSIBLE_PROGRAMS
#endif //MAX_POSSIBLE_PROGRAMS
#ifdef IsValidDemux(Dmx)
#undef IsValidDemux(Dmx)
#endif //IsValidDemux(Dmx)
#ifdef PAT_COLLECTION_TIMEOUT
#undef PAT_COLLECTION_TIMEOUT
#endif //PAT_COLLECTION_TIMEOUT
#ifdef MIN(a,b)
#undef MIN(a,b)
#endif //MIN(a,b)
#ifdef SIMPLE_PMT_SORTEDTABLE_ID(Dmx)
#undef SIMPLE_PMT_SORTEDTABLE_ID(Dmx)
#endif //SIMPLE_PMT_SORTEDTABLE_ID(Dmx)
#ifdef INVALID_SRTDB_KEY
#undef INVALID_SRTDB_KEY
#endif //INVALID_SRTDB_KEY
#ifdef IGNORE_STRAPI
#undef IGNORE_STRAPI
#endif //IGNORE_STRAPI
#endif //LOCAL_UNDEFINES
