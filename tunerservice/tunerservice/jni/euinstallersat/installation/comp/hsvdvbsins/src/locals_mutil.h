#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#define FREQUENCY_TOLERANCE_FOR_MUX_COMPARISON	(2000)

#define MAX_TP_PER_SATELLITE    			(200)

#define IS_DUPLICATE_FREQ(Freq,Entry)       ((((Freq) > ((Entry) - FREQUENCY_TOLERANCE_FOR_MUX_COMPARISON)) && ((Freq) < ((Entry) + FREQUENCY_TOLERANCE_FOR_MUX_COMPARISON)  )) ? TRUE: FALSE)

#define COMPARE_ABS_VALUES(a,b)             (((a) == (b) ) ? TRUE : FALSE)

#define BARKER_MUX_FILE_PATH        		"/mnt/jffs0/boot/broadcast/barkermuxdata.bin"

#define BARKER_MUX_FILE_CURRENT_PRIMARYVERSION			(1)

#define BARKER_MUX_FILE_CURRENT_SECONDARYVERSION		(1)

#define ISDIGITURK_PACKAGEID(PackageId)		(((PackageId == DIGITURK_TURKSAT_PACKAGE_ID) || (PackageId == DIGITURK_EUTELSAT_PACKAGE_ID))?TRUE: FALSE)

/****************************************************************************
 * Static variables
 ****************************************************************************/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
FrequencyDataList FrequencyData[MAX_TP_PER_SATELLITE];
static FrequencyDataList s__FrequencyData[MAX_TP_PER_SATELLITE];
int NumOfEntries;
static int s__NumOfEntries;
HsvBarkerMuxFlashData mBarkerMuxFlashData;
static HsvBarkerMuxFlashData s__mBarkerMuxFlashData;
Nat32 CalculateCrc32( void* buffer, int size );
HsvBarkerMuxHeaderCompatibility mCheckVersions(HsvBarkerMuxFlashHeader* Header);
void module__init(void){
	memcpy((void*)FrequencyData,(void*)s__FrequencyData,sizeof(FrequencyData));
	NumOfEntries	=	s__NumOfEntries;
	mBarkerMuxFlashData	=	s__mBarkerMuxFlashData;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef FREQUENCY_TOLERANCE_FOR_MUX_COMPARISON
#undef FREQUENCY_TOLERANCE_FOR_MUX_COMPARISON
#endif //FREQUENCY_TOLERANCE_FOR_MUX_COMPARISON
#ifdef MAX_TP_PER_SATELLITE
#undef MAX_TP_PER_SATELLITE
#endif //MAX_TP_PER_SATELLITE
#ifdef IS_DUPLICATE_FREQ(Freq,Entry)
#undef IS_DUPLICATE_FREQ(Freq,Entry)
#endif //IS_DUPLICATE_FREQ(Freq,Entry)
#ifdef COMPARE_ABS_VALUES(a,b)
#undef COMPARE_ABS_VALUES(a,b)
#endif //COMPARE_ABS_VALUES(a,b)
#ifdef BARKER_MUX_FILE_PATH
#undef BARKER_MUX_FILE_PATH
#endif //BARKER_MUX_FILE_PATH
#ifdef BARKER_MUX_FILE_CURRENT_PRIMARYVERSION
#undef BARKER_MUX_FILE_CURRENT_PRIMARYVERSION
#endif //BARKER_MUX_FILE_CURRENT_PRIMARYVERSION
#ifdef BARKER_MUX_FILE_CURRENT_SECONDARYVERSION
#undef BARKER_MUX_FILE_CURRENT_SECONDARYVERSION
#endif //BARKER_MUX_FILE_CURRENT_SECONDARYVERSION
#ifdef ISDIGITURK_PACKAGEID(PackageId)
#undef ISDIGITURK_PACKAGEID(PackageId)
#endif //ISDIGITURK_PACKAGEID(PackageId)
#endif //LOCAL_UNDEFINES
