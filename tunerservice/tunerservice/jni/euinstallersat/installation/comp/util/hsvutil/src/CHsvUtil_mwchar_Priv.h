#ifndef  _CHSVUTIL_MWCHAR_PRIV_H
#define  _CHSVUTIL_MWCHAR_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCharSetUtilityEx.h>
#include <IHsvCharSetUtility2.h>
#include <IHsvCountryIds.h>
#include <IHsvUtilDiv.h>
#include <IHsvHuffmanDecoder.h>
#include <IAppApiMultiLingualStringConversion.h>
#include <IHsvSatSystemSettings.h>
#include <CS2MwBase.h>
class CHsvUtil_mwchar_Priv;
#define CLASSSCOPE CHsvUtil_mwchar_Priv::
#include "locals_mwchar.h"

class CHsvUtil_mwchar_Priv : public CS2MwBase
{
public:
virtual ~CHsvUtil_mwchar_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mwchar.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvCharSetUtilityExImpl(CHsvUtil_mwchar_Priv,charsetutil);
IHsvCharSetUtility2Impl(CHsvUtil_mwchar_Priv,charsetutil2);
public:
ProvidesInterface<IHsvCharSetUtilityEx>	charsetutil;

ProvidesInterface<IHsvCharSetUtility2>	charsetutil2;

//Required interfaces
public:
RequiresInterface<IHsvCountryIds>	cids;
RequiresInterface<IHsvUtilDiv>	div;
RequiresInterface<IHsvHuffmanDecoder>	istringdec;
RequiresInterface<IAppApiMultiLingualStringConversion>	ling;
RequiresInterface<IHsvSatSystemSettings>	sysset;

public:
CHsvUtil_mwchar_Priv():i__charsetutil(this),i__charsetutil2(this)
{
charsetutil	=	&i__charsetutil;
charsetutil2	=	&i__charsetutil2;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define cids_iPresent() (cids.Present())
#define cids_CountryAustria	IHsvCountryIds_CountryAustria
#define cids_CountryBelgium	IHsvCountryIds_CountryBelgium
#define cids_CountryCroatia	IHsvCountryIds_CountryCroatia
#define cids_CountryCzechrep	IHsvCountryIds_CountryCzechrep
#define cids_CountryDenmark	IHsvCountryIds_CountryDenmark
#define cids_CountryFinland	IHsvCountryIds_CountryFinland
#define cids_CountryFrance	IHsvCountryIds_CountryFrance
#define cids_CountryGermany	IHsvCountryIds_CountryGermany
#define cids_CountryGreece	IHsvCountryIds_CountryGreece
#define cids_CountryHungary	IHsvCountryIds_CountryHungary
#define cids_CountryIreland	IHsvCountryIds_CountryIreland
#define cids_CountryItaly	IHsvCountryIds_CountryItaly
#define cids_CountryLuxembourg	IHsvCountryIds_CountryLuxembourg
#define cids_CountryNetherlands	IHsvCountryIds_CountryNetherlands
#define cids_CountryNorway	IHsvCountryIds_CountryNorway
#define cids_CountryPoland	IHsvCountryIds_CountryPoland
#define cids_CountryPortugal	IHsvCountryIds_CountryPortugal
#define cids_CountryRomania	IHsvCountryIds_CountryRomania
#define cids_CountryRussia	IHsvCountryIds_CountryRussia
#define cids_CountrySerbia	IHsvCountryIds_CountrySerbia
#define cids_CountrySlovakia	IHsvCountryIds_CountrySlovakia
#define cids_CountrySlovenia	IHsvCountryIds_CountrySlovenia
#define cids_CountrySpain	IHsvCountryIds_CountrySpain
#define cids_CountrySweden	IHsvCountryIds_CountrySweden
#define cids_CountrySwitzerland	IHsvCountryIds_CountrySwitzerland
#define cids_CountryTurkey	IHsvCountryIds_CountryTurkey
#define cids_CountryUK	IHsvCountryIds_CountryUK
#define cids_CountryOther	IHsvCountryIds_CountryOther
#define cids_CountryAustralia	IHsvCountryIds_CountryAustralia
#define cids_CountryEstonia	IHsvCountryIds_CountryEstonia
#define cids_CountryLithuania	IHsvCountryIds_CountryLithuania
#define cids_CountryLatvia	IHsvCountryIds_CountryLatvia
#define cids_CountryKazakhstan	IHsvCountryIds_CountryKazakhstan
#define cids_CountryBulgaria	IHsvCountryIds_CountryBulgaria
#define cids_CountryChina	IHsvCountryIds_CountryChina
#define cids_CountryUkraine	IHsvCountryIds_CountryUkraine
#define cids_CountryBrazil	IHsvCountryIds_CountryBrazil
#define cids_CountryArgentina	IHsvCountryIds_CountryArgentina
#define cids_CountryAlbania	IHsvCountryIds_CountryAlbania
#define cids_CountryArmenia	IHsvCountryIds_CountryArmenia
#define cids_CountryAzerbaijan	IHsvCountryIds_CountryAzerbaijan
#define cids_CountryBelarus	IHsvCountryIds_CountryBelarus
#define cids_CountryBosniaAndHerzegovina	IHsvCountryIds_CountryBosniaAndHerzegovina
#define cids_CountryGeorgia	IHsvCountryIds_CountryGeorgia
#define cids_CountryMontenegro	IHsvCountryIds_CountryMontenegro
#define cids_CountryIsrael	IHsvCountryIds_CountryIsrael
#define cids_CountryMacedoniafyrom	IHsvCountryIds_CountryMacedoniafyrom
#define cids_CountryMax	IHsvCountryIds_CountryMax
#define div_iPresent() (div.Present())
#define div_DefaultCharacterTable	div->DefaultCharacterTable()
#define div_ForceCharacterTable	div->ForceCharacterTable()
#define div_RegionalCharacterTable	div->RegionalCharacterTable()
#define istringdec_iPresent() (istringdec.Present())
#define istringdec_DtgHuffmanDecoderToString(src,dstBuf,size,dstSize)	istringdec->DtgHuffmanDecoderToString(src,dstBuf,size,dstSize)
#define ling_iPresent() (ling.Present())
#define ling_RESULT_OK	IAppApiMultiLingualStringConversion_RESULT_OK
#define ling_RESULT_ERROR_INVALID_TABLE	IAppApiMultiLingualStringConversion_RESULT_ERROR_INVALID_TABLE
#define ling_RESULT_DESTINATION_TOO_SMALL	IAppApiMultiLingualStringConversion_RESULT_DESTINATION_TOO_SMALL
#define ling_RESULT_NON_EVEN_SIZE	IAppApiMultiLingualStringConversion_RESULT_NON_EVEN_SIZE
#define ling_TableDefault	IAppApiMultiLingualStringConversion_TableDefault
#define ling_TableLatin1	IAppApiMultiLingualStringConversion_TableLatin1
#define ling_TableISO8859_1	IAppApiMultiLingualStringConversion_TableISO8859_1
#define ling_TableLatin2	IAppApiMultiLingualStringConversion_TableLatin2
#define ling_TableISO8859_2	IAppApiMultiLingualStringConversion_TableISO8859_2
#define ling_TableLatin3	IAppApiMultiLingualStringConversion_TableLatin3
#define ling_TableISO8859_3	IAppApiMultiLingualStringConversion_TableISO8859_3
#define ling_TableLatin4	IAppApiMultiLingualStringConversion_TableLatin4
#define ling_TableISO8859_4	IAppApiMultiLingualStringConversion_TableISO8859_4
#define ling_TableCyrillic	IAppApiMultiLingualStringConversion_TableCyrillic
#define ling_TableISO8859_5	IAppApiMultiLingualStringConversion_TableISO8859_5
#define ling_TableArabic	IAppApiMultiLingualStringConversion_TableArabic
#define ling_TableISO8859_6	IAppApiMultiLingualStringConversion_TableISO8859_6
#define ling_TableGreek	IAppApiMultiLingualStringConversion_TableGreek
#define ling_TableISO8859_7	IAppApiMultiLingualStringConversion_TableISO8859_7
#define ling_TableHebrew	IAppApiMultiLingualStringConversion_TableHebrew
#define ling_TableISO8859_8	IAppApiMultiLingualStringConversion_TableISO8859_8
#define ling_TableLatin5	IAppApiMultiLingualStringConversion_TableLatin5
#define ling_TableISO8859_9	IAppApiMultiLingualStringConversion_TableISO8859_9
#define ling_TableLatin6	IAppApiMultiLingualStringConversion_TableLatin6
#define ling_TableISO8859_10	IAppApiMultiLingualStringConversion_TableISO8859_10
#define ling_TableThai	IAppApiMultiLingualStringConversion_TableThai
#define ling_TableISO8859_11	IAppApiMultiLingualStringConversion_TableISO8859_11
#define ling_TableLatin7	IAppApiMultiLingualStringConversion_TableLatin7
#define ling_TableISO8859_13	IAppApiMultiLingualStringConversion_TableISO8859_13
#define ling_TableLatin8	IAppApiMultiLingualStringConversion_TableLatin8
#define ling_TableISO8859_14	IAppApiMultiLingualStringConversion_TableISO8859_14
#define ling_TableLatin9	IAppApiMultiLingualStringConversion_TableLatin9
#define ling_TableISO8859_15	IAppApiMultiLingualStringConversion_TableISO8859_15
#define ling_TableLatin10	IAppApiMultiLingualStringConversion_TableLatin10
#define ling_TableISO8859_16	IAppApiMultiLingualStringConversion_TableISO8859_16
#define ling_TableLegacyCyrillic	IAppApiMultiLingualStringConversion_TableLegacyCyrillic
#define ling_TableLegacyArabic	IAppApiMultiLingualStringConversion_TableLegacyArabic
#define ling_TableLegacyGreek	IAppApiMultiLingualStringConversion_TableLegacyGreek
#define ling_TableLegacyHebrew	IAppApiMultiLingualStringConversion_TableLegacyHebrew
#define ling_TableLegacyLatin5	IAppApiMultiLingualStringConversion_TableLegacyLatin5
#define ling_TableLegacyLatin2	IAppApiMultiLingualStringConversion_TableLegacyLatin2
#define ling_TableUcs2	IAppApiMultiLingualStringConversion_TableUcs2
#define ling_TableChinese	IAppApiMultiLingualStringConversion_TableChinese
#define ling_TableUtf8	IAppApiMultiLingualStringConversion_TableUtf8
#define ling_TableWindows1250	IAppApiMultiLingualStringConversion_TableWindows1250
#define ling_TableWindows1251	IAppApiMultiLingualStringConversion_TableWindows1251
#define ling_TableWindows1252	IAppApiMultiLingualStringConversion_TableWindows1252
#define ling_TableWindows1253	IAppApiMultiLingualStringConversion_TableWindows1253
#define ling_TableWindows1254	IAppApiMultiLingualStringConversion_TableWindows1254
#define ling_MbToWc(table,mbstr,mblen,wcstr,wclen)	ling->MbToWc(table,mbstr,mblen,wcstr,wclen)
#define ling_MbToWcEx(table,mbstr,mblen,wcstr,wclen,skipcontrols)	ling->MbToWcEx(table,mbstr,mblen,wcstr,wclen,skipcontrols)
#define ling_WcToMb(table,wcstr,wclen,mbstr,mblen)	ling->WcToMb(table,wcstr,wclen,mbstr,mblen)
#define ling_WcToMbEx(table,wcstr,wclen,mbstr,mblen,skipcontrols)	ling->WcToMbEx(table,wcstr,wclen,mbstr,mblen,skipcontrols)
#define ling_MbToWcChina(mbstr,mblen,wcstr,wclen)	ling->MbToWcChina(mbstr,mblen,wcstr,wclen)
#define sysset_iPresent() (sysset.Present())
#define sysset_AudioFormatStandard	IHsvSatSystemSettings_AudioFormatStandard
#define sysset_AudioFormatAdvanced	IHsvSatSystemSettings_AudioFormatAdvanced
#define sysset_SetSystemLanguage(lang)	sysset->SetSystemLanguage(lang)
#define sysset_GetSystemLanguage()	sysset->GetSystemLanguage()
#define sysset_SetPreferredPrimaryAudioLanguage(lang)	sysset->SetPreferredPrimaryAudioLanguage(lang)
#define sysset_GetPreferredPrimaryAudioLanguage()	sysset->GetPreferredPrimaryAudioLanguage()
#define sysset_GetPreferredSecondarySubtitleLanguage()	sysset->GetPreferredSecondarySubtitleLanguage()
#define sysset_SetPreferredSecondarySubtitleLanguage(lang)	sysset->SetPreferredSecondarySubtitleLanguage(lang)
#define sysset_GetPreferredSecondaryAudioLanguage()	sysset->GetPreferredSecondaryAudioLanguage()
#define sysset_SetPreferredSecondaryAudioLanguage(lang)	sysset->SetPreferredSecondaryAudioLanguage(lang)
#define sysset_SetPreferredPrimarySubtitleLanguage(lang)	sysset->SetPreferredPrimarySubtitleLanguage(lang)
#define sysset_GetPreferredPrimarySubtitleLanguage()	sysset->GetPreferredPrimarySubtitleLanguage()
#define sysset_SetPreferredAudioFormat(format)	sysset->SetPreferredAudioFormat(format)
#define sysset_GetPreferredAudioFormat()	sysset->GetPreferredAudioFormat()
#define sysset_SetPreferredPrimaryTxtLanguage(lang)	sysset->SetPreferredPrimaryTxtLanguage(lang)
#define sysset_GetPreferredPrimaryTxtLanguage()	sysset->GetPreferredPrimaryTxtLanguage()
#define sysset_SetPreferredSecondaryTxtLanguage(lang)	sysset->SetPreferredSecondaryTxtLanguage(lang)
#define sysset_GetPreferredSecondaryTxtLanguage()	sysset->GetPreferredSecondaryTxtLanguage()
#define sysset_SetSystemCountry(country)	sysset->SetSystemCountry(country)
#define sysset_GetSystemCountry()	sysset->GetSystemCountry()
#define sysset_SetInstallCountry(country)	sysset->SetInstallCountry(country)
#define sysset_GetInstallCountry()	sysset->GetInstallCountry()
#define sysset_SetInstallCity(city)	sysset->SetInstallCity(city)
#define sysset_SetSystemCity(city)	sysset->SetSystemCity(city)
#define sysset_GetInstallCity()	sysset->GetInstallCity()
#define sysset_GetSystemCity()	sysset->GetSystemCity()
#define charsetutil2_ExtractNone	IHsvCharSetUtility2_ExtractNone
#define charsetutil2_ExtractShortName	IHsvCharSetUtility2_ExtractShortName
#define charsetutil2_ExtractEITShortEvent	IHsvCharSetUtility2_ExtractEITShortEvent
#define charsetutil2_ExtractEITExtendedEvent	IHsvCharSetUtility2_ExtractEITExtendedEvent

#define charsetutil2_ExtractBatLrnChannelListName	IHsvCharSetUtility2_ExtractBATLrnChannelListName
#define charsetutil2_ExtractBatLrnChannelListTranslation	IHsvCharSetUtility2_ExtractBATLrnChannelListTranslation



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
#include "locals_mwchar.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

