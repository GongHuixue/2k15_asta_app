#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define MAX_MUXES_PER_NTK       (94)
#define MAX_MUXES_PER_NTK_FOR_CAM       (100)


#define DEBUG_PRINT printf 

/* German ranking list (for TV only at the moment)

   as specified in "Ranking_list_Germany_07012005_final_spec_v10.xls"
   */

#define AUTO_MODE       (rins_InstallationModeAutomatic)

#define CABLE_MEDIUM    (rins_GetMedium() == rins_Cable)

#define MAX_CHARACTERS		(128)

#define	GERMAN_RANKINGLIST_SIZE	(118)

#define	AUSTRIAN_RANKINGLIST_SIZE	(23)

typedef struct FreqListPlusMux {
    Nat16 Original_NetworkId;
    Nat16 Tsid;
    int   NoOfFreqs;
    Nat32 Frequency[MAX_NO_ALT_FREQ_PER_MUX];
    int VersionNumber;
    int NoOfMuxs;
} FreqListPlusMux;
#if 0

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Nat16 RankingList_Germany[GERMAN_RANKINGLIST_SIZE];
static Nat16 s__RankingList_Germany[GERMAN_RANKINGLIST_SIZE];
Nat16 RankingList_Austria[AUSTRIAN_RANKINGLIST_SIZE];
static Nat16 s__RankingList_Austria[AUSTRIAN_RANKINGLIST_SIZE];
HsvNITFreqList NITFreqListDesc[MAX_MUXES_PER_NTK],NITFreqListDescTmp[MAX_MUXES_PER_NTK];
static HsvNITFreqList s__NITFreqListDesc[MAX_MUXES_PER_NTK],s__NITFreqListDescTmp[MAX_MUXES_PER_NTK];
int mFreqListCounter;
static int s__mFreqListCounter;
Bool StrapiNDuringInstallation;
static Bool s__StrapiNDuringInstallation;
FreqListPlusMux FLPlusMux[MAX_MUXES_PER_NTK];
static FreqListPlusMux s__FLPlusMux[MAX_MUXES_PER_NTK];
Bool mAltFreqNetworkUpdateDetected;
static Bool s__mAltFreqNetworkUpdateDetected;
void LoadFLPlusMux(void);
void CopyDBase();
void WriteIntoFlash(void);
Bool CompareAndUpdateAltFrequency(void) /* returns true if same, hence no flash update */;
#if 0

#endif

void module__init(void){
	memcpy((void*)RankingList_Germany,(void*)s__RankingList_Germany,sizeof(RankingList_Germany));
	memcpy((void*)RankingList_Austria,(void*)s__RankingList_Austria,sizeof(RankingList_Austria));
	memcpy((void*)NITFreqListDesc,(void*)s__NITFreqListDesc,sizeof(NITFreqListDesc));
	memcpy((void*)NITFreqListDescTmp,(void*)s__NITFreqListDescTmp,sizeof(NITFreqListDescTmp));
	mFreqListCounter	=	s__mFreqListCounter;
	StrapiNDuringInstallation	=	s__StrapiNDuringInstallation;
	memcpy((void*)FLPlusMux,(void*)s__FLPlusMux,sizeof(FLPlusMux));
	mAltFreqNetworkUpdateDetected	=	s__mAltFreqNetworkUpdateDetected;
#if 0

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef MAX_MUXES_PER_NTK
#undef MAX_MUXES_PER_NTK
#endif //MAX_MUXES_PER_NTK
#ifdef MAX_MUXES_PER_NTK_FOR_CAM
#undef MAX_MUXES_PER_NTK_FOR_CAM
#endif //MAX_MUXES_PER_NTK_FOR_CAM
#ifdef DEBUG_PRINT
#undef DEBUG_PRINT
#endif //DEBUG_PRINT
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef CABLE_MEDIUM
#undef CABLE_MEDIUM
#endif //CABLE_MEDIUM
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef GERMAN_RANKINGLIST_SIZE
#undef GERMAN_RANKINGLIST_SIZE
#endif //GERMAN_RANKINGLIST_SIZE
#ifdef AUSTRIAN_RANKINGLIST_SIZE
#undef AUSTRIAN_RANKINGLIST_SIZE
#endif //AUSTRIAN_RANKINGLIST_SIZE
#endif //LOCAL_UNDEFINES
