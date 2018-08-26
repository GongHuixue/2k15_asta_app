/*
 * Copyright Koninklijke Philips Electronics N.V. 2003
 * All rights reserved.
 *
 *          %name: phStdTypes.h %
 *       %version: 2 %
 * %date_modified: Wed Sep 24 17:17:10 2008 %
 *          Owner: %
 */


#ifndef _PHSTDTYPES_H_
#define _PHSTDTYPES_H_



#if defined(__TCS__)			               /* Trimedia compilation System */
#include "phStdTypesTcs.h"

#elif (defined(__mips__) && defined(__vxworks))  /* Tornado gcc compiler */
#include "phStdTypesGccMipsVxWorks.h"

#elif defined(_CC51)                             /* Tasking compiler */
#include "phStdTypesTasking8051.h"

#elif defined(_WIN32)                          /* Windows X86 simulation */
#include "phStdTypesMsvcX86.h"

/* TODO: do we really need different versions of the standard types for the GCC toolchains below ? */
/* #elif defined(__GNUC__)     */
/* #include "phStdTypesGcc.h"  */

/* PR eh24#197 */
/*#elif defined(LINUX) && defined(MONTAVISTA_GNU)*//* Linux MIPS build */
#elif defined(__GNUC__) && defined(MONTAVISTA_GNU)
#if defined(ARCH_IS_ARM)
#include "phStdTypesGccArmLinux.h"
#else
#include "phStdTypesGccMipsLinux.h"
#endif


#elif defined(__linux__)
#include "phStdTypesGccX86Linux.h"             /* Linux X86 build */

#else

#error undefined toolchain, please add a new phStdTypes instance for this toolchain to osapi

#endif


#endif /* _PHSTDTYPES_H_ */

