#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define dmxsecfN_ICONNECTED	1
// #define dmxsecfN_OnRequestAllowed( a )	((void)0)
// #define dmxsecfN_OnRequestCancelled( a )	(hsvdvbeit__dmxsecfN_OnRequestCancelled( a ), hsvdvbtot__dmxsecfN_OnRequestCancelled( a ), hsvdvbtdt__dmxsecfN_OnRequestCancelled( a ))
// #define dmxsecfN_OnRequestNotAllowed	hsvdvbsi__dmxsecfN_OnRequestNotAllowed
/*****************************************************************************/

#if 0

typedef struct
{
    int  Onwid;
    int  Tsid;
    int  Frequency;
    int  ModulationType;
    int  SignalStrength;    
    int  TSVersionNumber;
    int  DBVersionNumber;
    Bool SIValid;
}HsvDVBTSData;
typedef struct
{
    int                         Onwid;
    int                         ServiceId;
    int                         Tsid;
    int                         ProgramNo;
    int                         ServiceType;
    int                         LCN;
    Nat16                       ChannelName[32];
    int                         AudioPid;
    int                         VideoPid;
    int                         PcrPid;
    int                         Preset;
    int                         Version;
    int                         FlashIndex;
}HsvDVBPrimayServiceData;
typedef struct
{
    int Type;
    int Preset;
    int Onwid;
    int ServiceId;
    int Cookie;
    Bool PresetReserved;
}HsvPresetData;
#define INVALID_LCN (-1)

#define INVALID_PRESET (0)

#define GETVALIDANALOGPRESET(x)    ( x = (x > 91)   ? ( ((x/100) + 1)*100 + 1 ) : ( ((x/10 ) + 1)*10  + 1 ) )

#endif

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
#if 0

#endif

void module__init(void){
#if 0

#endif

}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef dmxsecfN_ICONNECTED
#undef dmxsecfN_ICONNECTED
#endif //dmxsecfN_ICONNECTED
#ifdef INVALID_LCN
#undef INVALID_LCN
#endif //INVALID_LCN
#ifdef INVALID_PRESET
#undef INVALID_PRESET
#endif //INVALID_PRESET
#ifdef GETVALIDANALOGPRESET(x)
#undef GETVALIDANALOGPRESET(x)
#endif //GETVALIDANALOGPRESET(x)
#endif //LOCAL_UNDEFINES
