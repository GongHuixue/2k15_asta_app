#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define DP(x)

#define WINDOWID        (wnddest_GetWindowId(HsvMain))

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
TypeSignalStrengthStatus SigStrStatus;
static TypeSignalStrengthStatus s__SigStrStatus;
Nat32 gQSigStrength;
static Nat32 s__gQSigStrength;
Nat32 gASigStrength;
static Nat32 s__gASigStrength;
Nat32 gVSigStrength;
static Nat32 s__gVSigStrength;
void UpdateSigStrMeasuredFlag(void);
Bool StartSigStrMeasWithMode(int mode, Nat32 *store, Bool *MeasuredFlag);
Nat32 GetSignalstrength(int measmode);
void module__init(void){
	SigStrStatus	=	s__SigStrStatus;
	gQSigStrength	=	s__gQSigStrength;
	gASigStrength	=	s__gASigStrength;
	gVSigStrength	=	s__gVSigStrength;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef DP(x)
#undef DP(x)
#endif //DP(x)
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#endif //LOCAL_UNDEFINES
