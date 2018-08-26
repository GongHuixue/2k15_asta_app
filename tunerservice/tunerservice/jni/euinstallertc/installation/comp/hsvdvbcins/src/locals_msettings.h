#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <errno.h>

#include <stdio.h>

#include <sys/types.h>

#include <unistd.h> 

#include <fcntl.h>

#include <string.h>

/************************************************************************
  pavan
  1.HKK::Copy all the values from Default to Current whenever country changes - done
  2.HKK::Maintain separate DS for manual settings. Dont club - done
  3.HKK::Use preferred notion correctly
  4.pvn::Write persistent to flash

 **************************************************************************/

/**************************************************************************
 * Macros and types
 **************************************************************************/

#define SYS_COUNTRY     (sysset_GetSystemCountry()) 

#define MAX_CHARACTERS			(128)

#define MAX_USERSYMRATES    (2)

#define DEFAULT_STEP_SIZE  rins_DVBCStepSize8;

#define MAX_PREDEFINE_SYMRATE   (8)

#define FILE_NAME			    "HsvDVBCSettingsFile"

#define DEFAULT_FILE_PATH       "nandffs0/HsvDVBCSettingsFile"

#define MAX_SETS                3

#define MAX_SYMRATES_PER_SET    5

#define MAX_MOD_TYP             3   

#define MAX_MODULATION_VALS     5

#define VALID_NTKID(NetworkID)  (((NetworkID) >= (0xFF01))? (FALSE) : (TRUE))

#define MAX_CHARACTERS				     (128)

#define MAX_SEARCH_RATES    (25)

#define AID_USER_SETTING 9997 /*Value taken from android_filesystem_config.h*/

#define AUTO_MODE             (rins_InstallationModeAutomatic)

#define UPDATE_MODE           (rins_InstallationModeUpdate)

#define CHECKDRIFT(Value1,Value2)		((Value1 > Value2) ? (Value1 - Value2) : (Value2 - Value1))

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int mConstellation[14];
static int s__mConstellation[14];
int ModulationVals[MAX_MODULATION_VALS];
static int s__ModulationVals[MAX_MODULATION_VALS];
int ModulationVals_Sweden    [MAX_MOD_TYP];
static int s__ModulationVals_Sweden    [MAX_MOD_TYP];
int ModulationVals_Norway    [MAX_MOD_TYP];
static int s__ModulationVals_Norway    [MAX_MOD_TYP];
int ModulationVals_Denmark   [MAX_MOD_TYP];
static int s__ModulationVals_Denmark   [MAX_MOD_TYP];
int SearchRates_Sweden [MAX_SETS][MAX_SYMRATES_PER_SET];
static int s__SearchRates_Sweden [MAX_SETS][MAX_SYMRATES_PER_SET];
int SearchRates_Norway [MAX_SETS][MAX_SYMRATES_PER_SET];
static int s__SearchRates_Norway [MAX_SETS][MAX_SYMRATES_PER_SET];
int SearchRates_Denmark [MAX_SETS][MAX_SYMRATES_PER_SET];
static int s__SearchRates_Denmark [MAX_SETS][MAX_SYMRATES_PER_SET];
HsvDVBSettings mCurrentData;
static HsvDVBSettings s__mCurrentData;
HsvDVBSettings mDefaultData;
static HsvDVBSettings s__mDefaultData;
HsvDVBSettings mPersistentData;
static HsvDVBSettings s__mPersistentData;
HsvDVBSettings mConsistencyCheckData;
static HsvDVBSettings s__mConsistencyCheckData;
HsvDVBSettings mManualData;
static HsvDVBSettings s__mManualData;
char mDirName[MAX_CHARACTERS];
static char s__mDirName[MAX_CHARACTERS];
char mFileName[MAX_CHARACTERS];
static char s__mFileName[MAX_CHARACTERS];
void mLoadDefaults(HsvDVBSettings* tmpdata);
void mAttributeCopy(HsvDVBSettings* dest, HsvDVBSettings* src, int attribute);
Bool mModeCopy(HsvDVBSettings* tmp, int attribute, int mode);
Bool mAttributeValueCopy(HsvDVBSettings* tmp, int attribute, int value);
int mGetAttrMode(HsvDVBSettings* tmp, int attribute);
int mGetAttrValue(HsvDVBSettings* tmp, int attribute);
void mInitialiseStruct(HsvDVBSettings* tmp);
int mGetNextAttrib(HsvDVBSettings* tmp, int attribute, Nat32 value);
void mGetPredefinedSymbolRatesNordic(int country, int *SearchRates, int *SearchRateLen );
Bool mIsPersistentFileAvailable();
void mGetFilePath(void);
void module__init(void){
	memcpy((void*)mConstellation,(void*)s__mConstellation,sizeof(mConstellation));
	memcpy((void*)ModulationVals,(void*)s__ModulationVals,sizeof(ModulationVals));
	memcpy((void*)ModulationVals_Sweden,(void*)s__ModulationVals_Sweden,sizeof(ModulationVals_Sweden));
	memcpy((void*)ModulationVals_Norway,(void*)s__ModulationVals_Norway,sizeof(ModulationVals_Norway));
	memcpy((void*)ModulationVals_Denmark,(void*)s__ModulationVals_Denmark,sizeof(ModulationVals_Denmark));
	memcpy((void*)SearchRates_Sweden,(void*)s__SearchRates_Sweden,sizeof(SearchRates_Sweden));
	memcpy((void*)SearchRates_Norway,(void*)s__SearchRates_Norway,sizeof(SearchRates_Norway));
	memcpy((void*)SearchRates_Denmark,(void*)s__SearchRates_Denmark,sizeof(SearchRates_Denmark));
	mCurrentData	=	s__mCurrentData;
	mDefaultData	=	s__mDefaultData;
	mPersistentData	=	s__mPersistentData;
	mConsistencyCheckData	=	s__mConsistencyCheckData;
	mManualData	=	s__mManualData;
	memcpy((void*)mDirName,(void*)s__mDirName,sizeof(mDirName));
	memcpy((void*)mFileName,(void*)s__mFileName,sizeof(mFileName));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef SYS_COUNTRY
#undef SYS_COUNTRY
#endif //SYS_COUNTRY
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef MAX_USERSYMRATES
#undef MAX_USERSYMRATES
#endif //MAX_USERSYMRATES
#ifdef DEFAULT_STEP_SIZE
#undef DEFAULT_STEP_SIZE
#endif //DEFAULT_STEP_SIZE
#ifdef MAX_PREDEFINE_SYMRATE
#undef MAX_PREDEFINE_SYMRATE
#endif //MAX_PREDEFINE_SYMRATE
#ifdef FILE_NAME
#undef FILE_NAME
#endif //FILE_NAME
#ifdef DEFAULT_FILE_PATH
#undef DEFAULT_FILE_PATH
#endif //DEFAULT_FILE_PATH
#ifdef MAX_SETS
#undef MAX_SETS
#endif //MAX_SETS
#ifdef MAX_SYMRATES_PER_SET
#undef MAX_SYMRATES_PER_SET
#endif //MAX_SYMRATES_PER_SET
#ifdef MAX_MOD_TYP
#undef MAX_MOD_TYP
#endif //MAX_MOD_TYP
#ifdef MAX_MODULATION_VALS
#undef MAX_MODULATION_VALS
#endif //MAX_MODULATION_VALS
#ifdef VALID_NTKID(NetworkID)
#undef VALID_NTKID(NetworkID)
#endif //VALID_NTKID(NetworkID)
#ifdef MAX_CHARACTERS
#undef MAX_CHARACTERS
#endif //MAX_CHARACTERS
#ifdef MAX_SEARCH_RATES
#undef MAX_SEARCH_RATES
#endif //MAX_SEARCH_RATES
#endif //LOCAL_UNDEFINES
