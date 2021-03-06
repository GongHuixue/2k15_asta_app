/* How to use these macros

Usage1: In PC Test app parsing 

char ModulationStrings[HsvAutoConstellation] = {
#define  HSVMODULATION(a)   #a,
};

Usage2: In Test app Menu

Same as above
At display strcat("Hsv", ModulationStrings[i]);

Usage3: MgrToPlf(MgrConstellation const)

  switch(const)
  {
#define  HSVMODULATION(a)   Hsv##a:
            retval  = tmFe_##a;
  }
Usage4: PlfToMgr(PlatformConstellation const)
  switch(const)
  {
#define  HSVMODULATION(a)   tmFe_a:
            retval  = Hsv##a;
  }
*/


#ifndef HSVCONSTELLATION
#define HSVCONSTELLATION(a) 
#endif

HSVCONSTELLATION(UnknownConstellation)
HSVCONSTELLATION(AutoConstellation)
HSVCONSTELLATION(Bpsk)
HSVCONSTELLATION(Qpsk)
HSVCONSTELLATION(8psk)
HSVCONSTELLATION(Qam4)
HSVCONSTELLATION(Qam16)
HSVCONSTELLATION(Qam32)
HSVCONSTELLATION(Qam64)
HSVCONSTELLATION(Qam128)
HSVCONSTELLATION(Qam256)
HSVCONSTELLATION(Qam512)
HSVCONSTELLATION(Qam1024)
HSVCONSTELLATION(Vsb8)
HSVCONSTELLATION(Vsb16)
#ifdef __HSVLASTDEFINED
HSVCONSTELLATION(ConstellationLast)
#endif
    
#undef HSVCONSTELLATION


#ifndef HSVTVSYSTEM
#define HSVTVSYSTEM(a) 
#endif

HSVTVSYSTEM(TvSystemNone)
HSVTVSYSTEM(TvSystemBg)
HSVTVSYSTEM(TvSystemD)
HSVTVSYSTEM(TvSystemDk)
HSVTVSYSTEM(TvSystemDk1)
HSVTVSYSTEM(TvSystemDk2)
HSVTVSYSTEM(TvSystemI)
HSVTVSYSTEM(TvSystemH)
HSVTVSYSTEM(TvSystemK1)
HSVTVSYSTEM(TvSystemL)
HSVTVSYSTEM(TvSystemL1)
HSVTVSYSTEM(TvSystemM)
HSVTVSYSTEM(TvSystemN)
HSVTVSYSTEM(TvSystemC64Qam) 
HSVTVSYSTEM(TvSystemC256Qam)
HSVTVSYSTEM(TvSystemT8Vsb)
HSVTVSYSTEM(TvSystemT16Vsb) 
#ifdef __HSVLASTDEFINED
HSVTVSYSTEM(TvSystemLast)
#endif
    
#undef HSVTVSYSTEM


#ifndef HSVIQMODE
#define HSVIQMODE(a) 
#endif

HSVIQMODE(UnknownIqMode)
HSVIQMODE(IqModeNormal)
HSVIQMODE(IqModeInverse)
HSVIQMODE(IqModeAuto)
#ifdef __HSVLASTDEFINED
HSVIQMODE(IqModeLast)
#endif
    
#undef HSVIQMODE


#ifndef HSVCODERATE
#define HSVCODERATE(a) 
#endif

HSVCODERATE(CodeRateUnknown)
HSVCODERATE(CodeRateInvalid)
HSVCODERATE(CodeRateNone)
HSVCODERATE(CodeRate1_2) 
HSVCODERATE(CodeRate2_3) 
HSVCODERATE(CodeRate3_4) 
HSVCODERATE(CodeRate5_6) 
HSVCODERATE(CodeRate6_7) 
HSVCODERATE(CodeRate7_8) 
HSVCODERATE(CodeRate8_9) 
HSVCODERATE(CodeRateAuto)
#ifdef __HSVLASTDEFINED
HSVCODERATE(CodeRateLast)
#endif
            
#undef HSVCODERATE

#ifndef HSVHIERARCHYMODE
#define HSVHIERARCHYMODE(a) 
#endif

HSVHIERARCHYMODE(HierarchyModeUnknown)
HSVHIERARCHYMODE(HierarchyModeInvalid)
HSVHIERARCHYMODE(HierarchyAlpha1) 
HSVHIERARCHYMODE(HierarchyAlpha2) 
HSVHIERARCHYMODE(HierarchyAlpha4) 
HSVHIERARCHYMODE(HierarchyNone)   
HSVHIERARCHYMODE(HierarchyModeAuto)
#ifdef __HSVLASTDEFINED
HSVHIERARCHYMODE(HierarchyModeLast)
#endif
    
#undef HSVHIERARCHYMODE

#ifndef HSVGUARDINTERVAL
#define HSVGUARDINTERVAL(a) 
#endif

HSVGUARDINTERVAL(GuardIntervalUnknown)
HSVGUARDINTERVAL(GuardIntervalInvalid)
HSVGUARDINTERVAL(GuardInterval1_32)
HSVGUARDINTERVAL(GuardInterval1_16)
HSVGUARDINTERVAL(GuardInterval1_8) 
HSVGUARDINTERVAL(GuardInterval1_4) 
HSVGUARDINTERVAL(GuardIntervalAuto)
#ifdef __HSVLASTDEFINED
HSVGUARDINTERVAL(GuardIntervalLast)
#endif
    
#undef HSVGUARDINTERVAL


#ifndef HSVTXMODE
#define HSVTXMODE(a) 
#endif

HSVTXMODE(TxModeUnknown)
HSVTXMODE(TxModeInvalid)
HSVTXMODE(TxMode2k) 
HSVTXMODE(TxMode8k) 
HSVTXMODE(TxModeAuto)
#ifdef __HSVLASTDEFINED
HSVTXMODE(TxModeLast)
#endif
    
#undef HSVTXMODE


#ifndef HSVCHANBANDWIDTH
#define HSVCHANBANDWIDTH(a) 
#endif

HSVCHANBANDWIDTH(ChanBandwidthAuto) 
HSVCHANBANDWIDTH(ChanBandwidth6MHz) 
HSVCHANBANDWIDTH(ChanBandwidth7MHz) 
HSVCHANBANDWIDTH(ChanBandwidth8MHz) 
HSVCHANBANDWIDTH(ChanBandwidthUnknown)
HSVCHANBANDWIDTH(ChanBandwidthInvalid)
#ifdef __HSVLASTDEFINED
HSVCHANBANDWIDTH(ChanBandwidthLast)
#endif

#undef HSVCHANBANDWIDTH

#ifndef HSVSTREAMPRIORITY
#define HSVSTREAMPRIORITY(a) 
#endif

HSVSTREAMPRIORITY(StreamPriorityHigh)
HSVSTREAMPRIORITY(StreamPriorityLow)
#ifdef __HSVLASTDEFINED
HSVSTREAMPRIORITY(StreamPriorityLast)
#endif

#undef HSVSTREAMPRIORITY

#ifndef HSVFREQUENCYOFFSET
#define HSVFREQUENCYOFFSET(a) 
#endif

HSVFREQUENCYOFFSET(OffsetNone)
HSVFREQUENCYOFFSET(OffsetInvalid)
HSVFREQUENCYOFFSET(OffsetUnknown)
HSVFREQUENCYOFFSET(OffsetP1d6MHz)
HSVFREQUENCYOFFSET(OffsetP2d6MHz)
HSVFREQUENCYOFFSET(OffsetP3d6MHz)
HSVFREQUENCYOFFSET(OffsetM1d6MHz)
HSVFREQUENCYOFFSET(OffsetM2d6MHz)
HSVFREQUENCYOFFSET(OffsetM3d6MHz)
HSVFREQUENCYOFFSET(OffsetAuto)
#ifdef __HSVLASTDEFINED
HSVFREQUENCYOFFSET(FrequencyOffsetLast)
#endif
#undef HSVFREQUENCYOFFSET



