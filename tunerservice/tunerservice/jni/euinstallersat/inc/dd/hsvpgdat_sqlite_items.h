

#if defined FREQMAP_ITEM
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_freqmapitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A
	
#elif defined SATINFO_ITEM
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_satinfoitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A

#elif defined ANALOG_ITEM
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_analogitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A
	
#elif defined DIGTS_ITEM
if (mCurrentTable == ipgdbconst_Satellite) {
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_sat_digtsitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A
}
else {
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_digtsitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A
}

#elif defined DIGSRVC_ITEM
if (mCurrentTable == ipgdbconst_Satellite) {
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_sat_digsrvcitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A
}
else {
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_digsrvcitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A
}
 
#elif defined PRESET_ITEM 
if (mCurrentTable == ipgdbconst_Satellite) {
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_sat_presetitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A
}
else {
/* Based on the macro type fill in the string */
#define		Nat64	"integer"
#define		Nat32	"integer"
#define		Nat16	"smallint"
#define 	int	"integer"
#define		Int16	"smallint"
#define		Nat8	"integer"
#define		NONE	0
#define		A(x)	x
	#include "hsvpgdat_presetitems.h"
#undef	Nat64
#undef	Nat32
#undef	int
#undef	Nat16
#undef	Nat8
#undef	Int16
#undef	NONE
#undef	A
}
#endif



