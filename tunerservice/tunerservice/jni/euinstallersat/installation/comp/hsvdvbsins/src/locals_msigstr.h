#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define DP(x)

#define WINDOWID        (wnddest_GetWindowId(HsvMain))

#define SIGSTRENGTHZERO                     ( 0 )                                            

#define TM_OK       0

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
TypeSignalStrengthStatus SigStrStatus;
static TypeSignalStrengthStatus s__SigStrStatus;
Nat32 gQSigStrength;
static Nat32 s__gQSigStrength;
Nat32 gSSigStrength;
static Nat32 s__gSSigStrength;
void UpdateSigStrMeasuredFlag(void);
Bool StartSigStrMeasWithMode(int mode, Nat32 *store, Bool *MeasuredFlag);
Nat32 GetSignalstrength(int measmode);
FResult plfwrapper_Start( int winid, int ssm, Bool* Avail, Nat32* retval );
FResult plfwrapper_GetSigStrengthRange( int winid, int ssm, Nat32* MinStrength, Nat32* MaxStrength, Nat32* retval );
FResult plfwrapper_GetMeasValid( int winid, int ssm, Bool* Valid, Nat32* retval );
FResult plfwrapper_GetSigStrength( int winid, int ssm, Nat32* Strength, Nat32* retval );
FResult plfwrapper_Stop( int winid, int ssm, Bool* Stopped, Nat32* retval );
void module__init(void){
	SigStrStatus	=	s__SigStrStatus;
	gQSigStrength	=	s__gQSigStrength;
	gSSigStrength	=	s__gSSigStrength;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef DP(x)
#undef DP(x)
#endif //DP(x)
#ifdef WINDOWID
#undef WINDOWID
#endif //WINDOWID
#ifdef SIGSTRENGTHZERO
#undef SIGSTRENGTHZERO
#endif //SIGSTRENGTHZERO
#ifdef TM_OK
#undef TM_OK
#endif //TM_OK
#endif //LOCAL_UNDEFINES
