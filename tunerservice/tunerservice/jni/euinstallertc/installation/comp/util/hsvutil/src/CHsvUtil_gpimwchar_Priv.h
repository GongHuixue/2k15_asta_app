#ifndef  _CHSVUTIL_GPIMWCHAR_PRIV_H
#define  _CHSVUTIL_GPIMWCHAR_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IMultiLingualStringConversion.h>
#include <CTCMwBase.h>
class CHsvUtil_gpimwchar_Priv;
#define CLASSSCOPE CHsvUtil_gpimwchar_Priv::
#include "locals_gpimwchar.h"

class CHsvUtil_gpimwchar_Priv : public CTCMwBase
{
public:
virtual ~CHsvUtil_gpimwchar_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_gpimwchar.h"
#undef MEMBERVARS
//Provided interfaces
private:
IMultiLingualStringConversionImpl(CHsvUtil_gpimwchar_Priv,ling);
public:
ProvidesInterface<IMultiLingualStringConversion>	ling;


public:
CHsvUtil_gpimwchar_Priv():i__ling(this)
{
ling	=	&i__ling;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define ling_RESULT_OK	IMultiLingualStringConversion_RESULT_OK
#define ling_RESULT_ERROR_INVALID_TABLE	IMultiLingualStringConversion_RESULT_ERROR_INVALID_TABLE
#define ling_RESULT_DESTINATION_TOO_SMALL	IMultiLingualStringConversion_RESULT_DESTINATION_TOO_SMALL
#define ling_RESULT_NON_EVEN_SIZE	IMultiLingualStringConversion_RESULT_NON_EVEN_SIZE
#define ling_TableDefault	IMultiLingualStringConversion_TableDefault
#define ling_TableLatin1	IMultiLingualStringConversion_TableLatin1
#define ling_TableISO8859_1	IMultiLingualStringConversion_TableISO8859_1
#define ling_TableLatin2	IMultiLingualStringConversion_TableLatin2
#define ling_TableISO8859_2	IMultiLingualStringConversion_TableISO8859_2
#define ling_TableLatin3	IMultiLingualStringConversion_TableLatin3
#define ling_TableISO8859_3	IMultiLingualStringConversion_TableISO8859_3
#define ling_TableLatin4	IMultiLingualStringConversion_TableLatin4
#define ling_TableISO8859_4	IMultiLingualStringConversion_TableISO8859_4
#define ling_TableCyrillic	IMultiLingualStringConversion_TableCyrillic
#define ling_TableISO8859_5	IMultiLingualStringConversion_TableISO8859_5
#define ling_TableArabic	IMultiLingualStringConversion_TableArabic
#define ling_TableISO8859_6	IMultiLingualStringConversion_TableISO8859_6
#define ling_TableGreek	IMultiLingualStringConversion_TableGreek
#define ling_TableISO8859_7	IMultiLingualStringConversion_TableISO8859_7
#define ling_TableHebrew	IMultiLingualStringConversion_TableHebrew
#define ling_TableISO8859_8	IMultiLingualStringConversion_TableISO8859_8
#define ling_TableLatin5	IMultiLingualStringConversion_TableLatin5
#define ling_TableISO8859_9	IMultiLingualStringConversion_TableISO8859_9
#define ling_TableLatin6	IMultiLingualStringConversion_TableLatin6
#define ling_TableISO8859_10	IMultiLingualStringConversion_TableISO8859_10
#define ling_TableThai	IMultiLingualStringConversion_TableThai
#define ling_TableISO8859_11	IMultiLingualStringConversion_TableISO8859_11
#define ling_TableLatin7	IMultiLingualStringConversion_TableLatin7
#define ling_TableISO8859_13	IMultiLingualStringConversion_TableISO8859_13
#define ling_TableLatin8	IMultiLingualStringConversion_TableLatin8
#define ling_TableISO8859_14	IMultiLingualStringConversion_TableISO8859_14
#define ling_TableLatin9	IMultiLingualStringConversion_TableLatin9
#define ling_TableISO8859_15	IMultiLingualStringConversion_TableISO8859_15
#define ling_TableLatin10	IMultiLingualStringConversion_TableLatin10
#define ling_TableISO8859_16	IMultiLingualStringConversion_TableISO8859_16
#define ling_TableLegacyCyrillic	IMultiLingualStringConversion_TableLegacyCyrillic
#define ling_TableLegacyArabic	IMultiLingualStringConversion_TableLegacyArabic
#define ling_TableLegacyGreek	IMultiLingualStringConversion_TableLegacyGreek
#define ling_TableLegacyHebrew	IMultiLingualStringConversion_TableLegacyHebrew
#define ling_TableLegacyLatin5	IMultiLingualStringConversion_TableLegacyLatin5
#define ling_TableLegacyLatin2	IMultiLingualStringConversion_TableLegacyLatin2
#define ling_TableUcs2	IMultiLingualStringConversion_TableUcs2
#define ling_TableChinese	IMultiLingualStringConversion_TableChinese
#define ling_TableUtf8	IMultiLingualStringConversion_TableUtf8
#define ling_TableWindows1250	IMultiLingualStringConversion_TableWindows1250
#define ling_TableWindows1251	IMultiLingualStringConversion_TableWindows1251
#define ling_TableWindows1252	IMultiLingualStringConversion_TableWindows1252
#define ling_TableWindows1253	IMultiLingualStringConversion_TableWindows1253
#define ling_TableWindows1254	IMultiLingualStringConversion_TableWindows1254
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_gpimwchar.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

