
#define HSVFUNCTION(PlfParameter)	static  Hsv##PlfParameter       ConvertFromPlatform##PlfParameter (tmFe_##PlfParameter##_t inval)

/* convert of plf 2 MW functions prototypes */
HSVFUNCTION(ChanBandwidth);      
HSVFUNCTION(StreamPriority);	   
HSVFUNCTION(Constellation);

HSVFUNCTION(Constellation)
{
    HsvConstellation outval = (HsvConstellation)0;
    switch(inval)
    {
#define HSVCONSTELLATION(a)  case (tmFe_##a): \
        outval  =   Hsv##a;					  \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

    default:
        break;
    }
    return outval;
}

HSVFUNCTION(ChanBandwidth)
{
    HsvChanBandwidth outval = (HsvChanBandwidth)0;
    switch(inval)
    {
#define HSVCHANBANDWIDTH(a)  case (tmFe_##a): \
        outval  =   Hsv##a;					  \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

    default:
        break;
    }
    return outval;
}

HSVFUNCTION(StreamPriority)
{
    HsvStreamPriority outval = HsvStreamPriorityHigh;
switch(inval)
    {
#define HSVSTREAMPRIORITY(a)  case (tmFe_##a): \
        outval  =   Hsv##a;					   \
        break;
#ifndef __cplusplus
#include "../../../prod/hsveur/hsvfe.h"
#else
#include "hsvfe.h"
#endif

    default:
        break;
    }
    return outval;
}

