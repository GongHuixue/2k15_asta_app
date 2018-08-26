#if !defined(MEMBERVARS) && !defined(LOCAL_UNDEFINES)
#define tspah_SCHO_minvalue      ( 8 ) 

#define PLANE_T0                 ( 0 )

#define PIXEL_PER_CHAR           ( 12 )

#define SCANLINES_PER_CHAR       (10)

#define VER_OFFSET               (0)

#define HOR_OFFSET               (0)

#endif //INCLUDES and DEFINES
#if defined(MEMBERVARS)
int currentCursor;
static int s__currentCursor;
void module__init(void){
	currentCursor	=	s__currentCursor;
}
#endif //MEMBERVARS
#if defined(LOCAL_UNDEFINES)
#ifdef tspah_SCHO_minvalue
#undef tspah_SCHO_minvalue
#endif //tspah_SCHO_minvalue
#ifdef PLANE_T0
#undef PLANE_T0
#endif //PLANE_T0
#ifdef PIXEL_PER_CHAR
#undef PIXEL_PER_CHAR
#endif //PIXEL_PER_CHAR
#ifdef SCANLINES_PER_CHAR
#undef SCANLINES_PER_CHAR
#endif //SCANLINES_PER_CHAR
#ifdef VER_OFFSET
#undef VER_OFFSET
#endif //VER_OFFSET
#ifdef HOR_OFFSET
#undef HOR_OFFSET
#endif //HOR_OFFSET
#endif //LOCAL_UNDEFINES
