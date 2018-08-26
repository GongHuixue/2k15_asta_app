#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#include <time.h>


/**********************************************************************************
 *   Description:    Decodes MJD Date
 *[In]       :    Date in MJD format (16 bit)
 *[Out]      :    year (Corresponding year)
 *[Out]      :    month (Corresponding month)
 *[Out]      :    day (Corresponding day)
 *Returns    :    None
 ***********************************************************************************/

#define BCD2DEC(_bcd) (int)(((((unsigned int)(_bcd)) >> 4) * 10) + (_bcd) % 16)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
inline void decode_bcd_time(uint32_t bcd, int *hr, int *min, int *sec);
void module__init(void){
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef BCD2DEC(_bcd)
#undef BCD2DEC(_bcd)
#endif //BCD2DEC(_bcd)
#endif //LOCAL_UNDEFINES
