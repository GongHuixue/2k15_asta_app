#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <string.h>

#include <stdlib.h>

#define  EMPHASIS_START     (0x0086)

#define  EMPHASIS_END       (0x0087)

#define  EMPHASIS_START_U     (0xe086)

#define  EMPHASIS_END_U       (0xe087)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
void ApplyShortName(Nat16 *wcstr, int *wclen);
void ApplyEITShortLongEvent(Nat16 *wcstr, int *wclen);
Bool IsControlCode(Nat16 c);
FResult MbToWcEx( Nat8 *mbstr, int mblen, Nat16 *wcstr, int *wclen, int exinfo);
FResult MbToWc( Nat8 *mbstr, int mblen, Nat16 *wcstr, int wclen, int exinfo);
FResult MbToWcExChina( Nat8 *mbstr, int mblen, Nat16 *wcstr, int *wclen, int exinfo);
FResult MbToWcChina( Nat8 *mbstr, int mblen, Nat16 *wcstr, int wclen, int exinfo);
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef EMPHASIS_START
#undef EMPHASIS_START
#endif //EMPHASIS_START
#ifdef EMPHASIS_END
#undef EMPHASIS_END
#endif //EMPHASIS_END
#ifdef EMPHASIS_START_U
#undef EMPHASIS_START_U
#endif //EMPHASIS_START_U
#ifdef EMPHASIS_END_U
#undef EMPHASIS_END_U
#endif //EMPHASIS_END_U
#endif //LOCAL_UNDEFINES
