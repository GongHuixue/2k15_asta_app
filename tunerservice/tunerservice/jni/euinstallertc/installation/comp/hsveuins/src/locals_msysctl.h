#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <stdio.h>

#define VIDEO_MUTE_BLACK                    (0)

#define VIDEO_MUTE_BLUE                     (1)

#define VIDEO_MUTE_GREY                     (2)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
Bool soundMuteOnOff;
static Bool s__soundMuteOnOff;
static Bool MuteStatus;
Nat16 unicodestring[IHsvPresetInstallationDiv_PresetNameLength];
static Nat16 s__unicodestring[IHsvPresetInstallationDiv_PresetNameLength];

int GetMuteColor(void);
void PError(int ErrorID);
void module__init(void){
	soundMuteOnOff	=	s__soundMuteOnOff;
	memcpy((void*)unicodestring,(void*)s__unicodestring,sizeof(unicodestring));
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef VIDEO_MUTE_BLACK
#undef VIDEO_MUTE_BLACK
#endif //VIDEO_MUTE_BLACK
#ifdef VIDEO_MUTE_BLUE
#undef VIDEO_MUTE_BLUE
#endif //VIDEO_MUTE_BLUE
#ifdef VIDEO_MUTE_GREY
#undef VIDEO_MUTE_GREY
#endif //VIDEO_MUTE_GREY
#endif //LOCAL_UNDEFINES
