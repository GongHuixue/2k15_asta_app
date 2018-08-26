#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include    <stdio.h>

#include    <string.h>

#include    <strings.h>

#ifndef __cplusplus

#else

#endif

#define     INVALID_INDEX  -1;


#define     MAX_NUM_OF_PRESCAN_ENTRIES          (32)

#define     CURRENT_SATELLITE_INDEX             (mCurrentSatelliteIndex)

#define     TOTAL_NUM_OF_PRESCANENTRIES			(mCurrentSatelliteIndex)

#define		TOTAL_NUM_OF_SATELLITES				(mTotalNumSatellites)

#define     MAX_ENTRY_LEN                       (64)

#define		MAX_NUM_OF_SATELLITES				(20)

#define		NUM_SATELLITES_IN_CURRENT_PRESCAN	(16)


/****************************************************************************
 * Static variables
 ****************************************************************************/

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#ifndef __cplusplus

#else

#endif

int mCurrentSatelliteIndex;
static int s__mCurrentSatelliteIndex;
int mTotalNumSatellites;
static int s__mTotalNumSatellites;
HsvSatelliteList mSatellitePreScanList[MAX_NUM_OF_PRESCAN_ENTRIES];
static HsvSatelliteList s__mSatellitePreScanList[MAX_NUM_OF_PRESCAN_ENTRIES];
HsvSatelliteList mSatelliteCountryPreScanList[MAX_NUM_OF_PRESCAN_ENTRIES];
static HsvSatelliteList s__mSatelliteCountryPreScanList[MAX_NUM_OF_PRESCAN_ENTRIES];
HsvSatelliteMapping mSatelliteMapping[MAX_NUM_OF_SATELLITES];
static HsvSatelliteMapping s__mSatelliteMapping[MAX_NUM_OF_SATELLITES];
Bool PreScanListFound;
static Bool s__PreScanListFound;
Bool CountryDependantTablePopulated;
static Bool s__CountryDependantTablePopulated;

Bool IsCountryDependantTableRequired(int country, int* region);
void module__init(void){
#ifndef __cplusplus

#else

#endif

	mCurrentSatelliteIndex	=	s__mCurrentSatelliteIndex;
	mTotalNumSatellites	=	s__mTotalNumSatellites;
	memcpy((void*)mSatellitePreScanList,(void*)s__mSatellitePreScanList,sizeof(mSatellitePreScanList));
	memcpy((void*)mSatelliteCountryPreScanList,(void*)s__mSatelliteCountryPreScanList,sizeof(mSatelliteCountryPreScanList));
	memcpy((void*)mSatelliteMapping,(void*)s__mSatelliteMapping,sizeof(mSatelliteMapping));
	PreScanListFound    = 	s__PreScanListFound;
	CountryDependantTablePopulated	=	s__CountryDependantTablePopulated;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#ifdef SATELLITE_STATICLIST_FILEPATH
#undef SATELLITE_STATICLIST_FILEPATH
#endif //SATELLITE_STATICLIST_FILEPATH
#ifdef MAX_NUM_OF_PRESCAN_ENTRIES
#undef MAX_NUM_OF_PRESCAN_ENTRIES
#endif //MAX_NUM_OF_PRESCAN_ENTRIES
#ifdef CURRENT_SATELLITE_INDEX
#undef CURRENT_SATELLITE_INDEX
#endif //CURRENT_SATELLITE_INDEX
#ifdef TOTAL_NUM_OF_PRESCANENTRIES
#undef TOTAL_NUM_OF_PRESCANENTRIES
#endif //TOTAL_NUM_OF_PRESCANENTRIES
#ifdef TOTAL_NUM_OF_SATELLITES
#undef TOTAL_NUM_OF_SATELLITES
#endif //TOTAL_NUM_OF_SATELLITES
#ifdef MAX_ENTRY_LEN
#undef MAX_ENTRY_LEN
#endif //MAX_ENTRY_LEN
#ifdef MAX_NUM_OF_SATELLITES
#undef MAX_NUM_OF_SATELLITES
#endif //MAX_NUM_OF_SATELLITES
#endif //LOCAL_UNDEFINES
