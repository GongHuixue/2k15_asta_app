/*
 * Copyright Koninklijke Philips Electronics N.V. 2003
 * All rights reserved.
 *
 *          %name: phExtraTypes.h %
 *       %version: 1 %
 * %date_modified: Fri May 30 17:50:31 2008 %
 *          Owner: %
 */


#ifndef _PHEXTRATYPES_H_
#define _PHEXTRATYPES_H_

#if 0

#if defined(__TCS__)			/* Trimedia compilation System */

#@include "phExtraTypesTcs.h"

#elif defined(TORNADO_GNU) || defined(VIPER)   /* Viper Mips VxWorks (SDE4: TORNADO_GNU, SDE1: VIPER) */

#@include "phExtraTypesTornadoMips.h"

#elif defined(STBUP_TASKING) /* 8051 Standby Controller */

#@include "phExtraTypesTasking8051.h"

#elif defined(__WIN32)       /* Windows X86 simulation */

#@include "phExtraTypesMsvcX86.h"

#else

#error undefined toolchain, please add a new phExtraTypes instance for this toolchain to osapi

#endif

#endif


#ifndef TMOAPTMTYPESINCLUDED

#ifndef TMOPSTDTMTYPEDEFS
#define TMOPSTDTMTYPEDEFS

#define	False		0
#define	Null		0
#define	True		1

typedef void            Void;
typedef char       *    Address;
typedef char const *	ConstAddress;
typedef void       *	Pointer;	/* pointer to anonymous object */
typedef void const *	ConstPointer;
typedef char const *	ConstString;

typedef unsigned char   Byte;		/* raw byte */
typedef int		Int;		/* machine-natural integer */
typedef unsigned int	UInt;		/* machine-natural unsigned integer */
typedef float		Float;		/* fast float */
typedef float		Float32;	/* single-precision float */
#if	!defined(__MWERKS__)
typedef double		Float64;	/* double-precision float */
#endif

#if defined(__KERNEL__) && defined(__linux__)
# include <linux/types.h>

typedef unsigned long   Flags;
#else
typedef UInt32          Flags;
typedef enum { TM32 = 0, TM3260, TM5250, TM2270, TM3270,
	       TM64=100 } TMArch;
/* TM32 = 0 for compatibility!, allow many tm32 versions before TM64 */
extern char* TMArch_names[];
/* LTS 601673 - To determnie the TMArch value from the name, we need this
                array because TMArch values are not consecutive */
extern TMArch TMArch_values[];

typedef struct {
  UInt8  majorVersion;
  UInt8  minorVersion;
  UInt16 buildVersion;
} tmVersion_t, *ptmVersion_t;

#endif /*TMOPSTDTMTYPEDEFS*/

#if	defined(_WIN32)
#define	LL_CONST(c)	(c##i64)
#define	ULL_CONST(c)	(c##ui64)
#define LL_MOD		"I64"
#else	/* !defined(_WIN32) */
#define	LL_CONST(c)	(c##LL)
#define	ULL_CONST(c)	(c##ULL)
#define LL_MOD		"ll"
#endif	/* !defined(_WIN32) */

#endif	/* !defined(KERNEL) */

/* PR eh24#207 */
/*#if defined (TMFL_DVP4_BUILD) || defined(SDE4_BUILD)*/

typedef Int		Endian;
#define	BigEndian	0
#define	LittleEndian	1  /* type clashes with winperf.h declaration */

/* PR eh24#207 */
/*#endif*/




extern char *get_TMArch_name(TMArch arch) ;

#endif






#endif /* _PHEXTRATYPES_H_ */
