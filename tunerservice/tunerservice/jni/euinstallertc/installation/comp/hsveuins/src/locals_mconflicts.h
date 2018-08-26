#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#define     AUTO_MODE                           (rins_InstallationModeAutomatic)

#define     UPDATE_MODE                         (rins_InstallationModeUpdate)

#define     MANUAL_MODE                         (rins_InstallationModeWeakSignal)

#define     CURRENT_MODE                        (rins_GetInstallationMode()) 

#define     AUTO_INSTALL                        (CURRENT_MODE == AUTO_MODE)

#define     CURRENT_TABLE                       ( pgdb_GetCurrentTable() )

#define     PRESET_TABLE                        ( CURRENT_TABLE | pgdbconst_Preset )

#define     SERVICE_TABLE                       ( CURRENT_TABLE | pgdbconst_DigitalService )

#define     ANALOG_TABLE                        ( CURRENT_TABLE | pgdbconst_Analog )

#define     DIGITAL                             (HsvOnePart)

#define     ANALOG                              (HsvAnalog)

#define     DIGITAL_PRESET(presetdat)           ((presetdat).Type == DIGITAL)

#define     INVALID_INDEX                       ( -1 )

#define     PRESET_NOT_ALLOCATED(svcdat)        ( (svcdat).PresetNumber == INVALID_PRESET )

#define     VALIDLCNRANGE(svcdat)               ( ((svcdat).LCN > 0) && ((svcdat).LCN < 1000) )

#define     IS_ITALIAN_NTK(svcdat)              ( ((svcdat).NetworkId >= 0x3001) && ((svcdat).NetworkId <= 0X3100) )

#define     CURRENT_SERVICE_INDEX               ( 0 )

#define     TOTAL_NUM_OF_CONFLICTS              ( mNumOfLCNsInConflict )

#define     NUM_OF_USER_CONFLICTS               ( mAppNumOfLCNsInConflict )

#define     CONFLICT_LCN(Indx)                  ( mConflictList[Indx].LCN)

#define     CONFLICT_USER_INTERESTED(Indx)      ( mAppConflictList[Indx].UserPreferedServiceIndex)

#define     IS_VALID_CONFLICT(svcdat)           ( PRESET_NOT_ALLOCATED(svcdat) || (svcdat.PresetNumber == svcdat.LCN) )

#define     CONFLICT_SERVICE_DBINDEX(Indx1, Indx2)      ( mConflictList[Indx1].ServiceInfo[Indx2].DbIndex )

#define     CONFLICT_USER_SERVICE_DBINDEX(Indx1, Indx2)     ( mAppConflictList[Indx1].ServiceInfo[Indx2].DbIndex )

#define     VALID_SERVICE_INDEX(DbIndex, MaxIndex)      ( (DbIndex >= 0) && (DbIndex <= MaxIndex) )

/*****   static variables   *****/

typedef enum
{
    evStep1 = 0,
    evStep2,
    evStep3,
    evComplete
}SortSteps;
#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Pump mConflictsPmp;
static Pump s__mConflictsPmp;
HsvConflictServicesData *mConflictList/*[MAX_SERVICES]*/;
//static HsvConflictServicesData *s__mConflictList/*[MAX_SERVICES]*/;
HsvConflictServicesData *mAppConflictList/*[MAX_SERVICES]*/;
//static HsvConflictServicesData *s__mAppConflictList/*[MAX_SERVICES]*/;
int TOTAL_NUM_OF_CONFLICTS,NUM_OF_USER_CONFLICTS;
static int s__TOTAL_NUM_OF_CONFLICTS,s__NUM_OF_USER_CONFLICTS;
void mConflictsHandler(int value, Nat32 param);
void mPopulateListOfConflicts(int evCurrentSortStep);
void mAutomaticConflictResolution(int evCurrentStep);
void mUserConflictResolution(int evCurrentStep);
void mCopyString(Nat16 *dest, Nat16 *src, int maxchars);
void mCopyDataToList(Address data, int ServiceInfoIndex, int ChannelType, int ConflictLCN);
Bool mIsPresentInConflictList(Nat16 LCN);
void mSelectUserInterestedServices(void);
void mUpdateConflictPresets(int PrefConflictServiceIndex, int DbIndex, Bool UserOrAutomatic);
void module__init(void){
	mConflictsPmp	=	s__mConflictsPmp;
	TOTAL_NUM_OF_CONFLICTS	=	s__TOTAL_NUM_OF_CONFLICTS;
	NUM_OF_USER_CONFLICTS	=	s__NUM_OF_USER_CONFLICTS;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef AUTO_MODE
#undef AUTO_MODE
#endif //AUTO_MODE
#ifdef UPDATE_MODE
#undef UPDATE_MODE
#endif //UPDATE_MODE
#ifdef MANUAL_MODE
#undef MANUAL_MODE
#endif //MANUAL_MODE
#ifdef CURRENT_MODE
#undef CURRENT_MODE
#endif //CURRENT_MODE
#ifdef AUTO_INSTALL
#undef AUTO_INSTALL
#endif //AUTO_INSTALL
#ifdef CURRENT_TABLE
#undef CURRENT_TABLE
#endif //CURRENT_TABLE
#ifdef PRESET_TABLE
#undef PRESET_TABLE
#endif //PRESET_TABLE
#ifdef SERVICE_TABLE
#undef SERVICE_TABLE
#endif //SERVICE_TABLE
#ifdef ANALOG_TABLE
#undef ANALOG_TABLE
#endif //ANALOG_TABLE
#ifdef DIGITAL
#undef DIGITAL
#endif //DIGITAL
#ifdef ANALOG
#undef ANALOG
#endif //ANALOG
#ifdef DIGITAL_PRESET(presetdat)
#undef DIGITAL_PRESET(presetdat)
#endif //DIGITAL_PRESET(presetdat)
#ifdef INVALID_INDEX
#undef INVALID_INDEX
#endif //INVALID_INDEX
#ifdef PRESET_NOT_ALLOCATED(svcdat)
#undef PRESET_NOT_ALLOCATED(svcdat)
#endif //PRESET_NOT_ALLOCATED(svcdat)
#ifdef VALIDLCNRANGE(svcdat)
#undef VALIDLCNRANGE(svcdat)
#endif //VALIDLCNRANGE(svcdat)
#ifdef IS_ITALIAN_NTK(svcdat)
#undef IS_ITALIAN_NTK(svcdat)
#endif //IS_ITALIAN_NTK(svcdat)
#ifdef CURRENT_SERVICE_INDEX
#undef CURRENT_SERVICE_INDEX
#endif //CURRENT_SERVICE_INDEX
#ifdef TOTAL_NUM_OF_CONFLICTS
#undef TOTAL_NUM_OF_CONFLICTS
#endif //TOTAL_NUM_OF_CONFLICTS
#ifdef NUM_OF_USER_CONFLICTS
#undef NUM_OF_USER_CONFLICTS
#endif //NUM_OF_USER_CONFLICTS
#ifdef CONFLICT_LCN(Indx)
#undef CONFLICT_LCN(Indx)
#endif //CONFLICT_LCN(Indx)
#ifdef CONFLICT_USER_INTERESTED(Indx)
#undef CONFLICT_USER_INTERESTED(Indx)
#endif //CONFLICT_USER_INTERESTED(Indx)
#ifdef IS_VALID_CONFLICT(svcdat)
#undef IS_VALID_CONFLICT(svcdat)
#endif //IS_VALID_CONFLICT(svcdat)
#ifdef CONFLICT_SERVICE_DBINDEX(Indx1,
#undef CONFLICT_SERVICE_DBINDEX(Indx1,
#endif //CONFLICT_SERVICE_DBINDEX(Indx1,
#ifdef CONFLICT_USER_SERVICE_DBINDEX(Indx1,
#undef CONFLICT_USER_SERVICE_DBINDEX(Indx1,
#endif //CONFLICT_USER_SERVICE_DBINDEX(Indx1,
#ifdef VALID_SERVICE_INDEX(DbIndex,
#undef VALID_SERVICE_INDEX(DbIndex,
#endif //VALID_SERVICE_INDEX(DbIndex,
#endif //LOCAL_UNDEFINES
