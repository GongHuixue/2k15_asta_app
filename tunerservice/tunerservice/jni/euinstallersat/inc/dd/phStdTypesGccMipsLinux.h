/*
 * Copyright Koninklijke Philips Electronics N.V. 2003
 * All rights reserved.
 *
 *          %name: phStdTypesGccMipsLinux.h %
 *       %version: 1 %
 * %date_modified: Fri May 30 17:50:37 2008 %
 *          Owner: %
 */


#ifndef _PHSTDTYPESGCCMIPSLINUX_H_
#define _PHSTDTYPESGCCMIPSLINUX_H_


/* PR eh24#197 */
/*#ifndef TMOAPTMTYPESINCLUDED*/
/*---------------------------------------------------------------------*/
#ifndef _BASICTYPES_DEFINED_
#define _BASICTYPES_DEFINED_

typedef char                *String;
typedef unsigned int         Bool;
typedef char                 Char;

typedef signed char          Int8;
typedef short                Int16;
typedef long                 Int32;
typedef long long            Int64;

typedef unsigned char        UInt8;
typedef unsigned short       UInt16;
typedef unsigned long        UInt32;
typedef unsigned long long   UInt64;

#if 0
#if defined(MIPSEL) || defined(MIPSEB)  /* SDE1 & SDE4 Build */
/* Default */
#elif defined(TMFL_ENDIAN)              /* SDE2 Build */
#if (TMFL_ENDIAN == TMFL_ENDIAN_BIG)
#define MIPSEB
#else
#define MIPSEL
#endif
#else
#error Endianess unknown
#endif

typedef struct                          /* Int64: 64-bit signed integer */
{
        /* Get the correct endianness (this has no impact on any other part of
            the system, but it may make memory dumps easier to understand). */
#ifdef MIPSEB
        Int32 hi; UInt32 lo;
#else
        UInt32 lo; Int32 hi;
#endif
}   Int64;

typedef struct                          /* UInt64: 64-bit unsigned integer */
{
#ifdef MIPSEB
        UInt32 hi; UInt32 lo;
#else
        UInt32 lo; UInt32 hi;
#endif
}   UInt64;

/* PR eh24#197 */ /* GR LINUX ?? */
/*#endif*/ /* TMOAPTMTYPESINCLUDED */
#endif

typedef UInt32               tmErrorCode_t;

typedef Int8               * pInt8;
typedef Int16              * pInt16;
typedef Int32              * pInt32;
typedef Int64              * pInt64;

typedef UInt8              * pUInt8;
typedef UInt16             * pUInt16;
typedef UInt32             * pUInt32;
typedef UInt64             * pUInt64;

typedef Bool               * pBool;
typedef Char               * pChar;
typedef String             * pString;
#endif /*_BASICTYPES_DEFINED_*/

/* PR eh24#197 */ /* GR LINUX ?? */
/*typedef int		     wchar_t;
typedef unsigned int         size_t;*/
typedef int                  intptr_t;
typedef unsigned int         uintptr_t;

#include <stdint.h>
#if 0
#define INT8_MIN    (-127-1)
#define INT8_MAX      127

#define INT16_MIN   (-32767-1)
#define INT16_MAX     32767

#define INT32_MIN   (-2147483647-1)          /* minimum long int value */
#define INT32_MAX     2147483647             /* maximum long int value */

#define INT64_MIN   (-9223372036854775807-1) /* minimum long long int value */
#define INT64_MAX     9223372036854775807    /* maximum long long int value */

#define UINT8_MAX      255U
#define UINT16_MAX     65535U
#define UINT32_MAX     4294967295U           /* maximum long int value */
#define UINT64_MAX     18446744073709551615U /* maximum long long int value */
#endif

#ifdef  TRUE
#undef  TRUE
#endif
#define TRUE        1

#ifdef  FALSE
#undef  FALSE
#endif
#define FALSE       0

#undef  NULL
#define NULL        (0)  /* Not cast to void*, because it should also work for ROM pointers */

#define TM_OK       0

#endif /* _PHSTDTYPESGCCMIPSLINUX_H_ */
