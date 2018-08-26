#ifndef  _CSVCPATS_PRIV_H
#define  _CSVCPATS_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvCniPresetName.h>
#include <IHsvPresetSort.h>
#include <ICesCountryIds.h>
#include <ICesPatsDiv.h>
#include <IHsvLanguageIds2.h>
#include <IHsvMemoryPool.h>
#include <IMemoryOperations.h>
#include <IString.h>
#include <IHsvTcSystemSettings.h>
#include <CTCMwBase.h>
class CSvcPats_Priv;
#define CLASSSCOPE CSvcPats_Priv::
#include "locals_m.h"

class CSvcPats_Priv : public CTCMwBase
{
public:
virtual ~CSvcPats_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvCniPresetNameImpl(CSvcPats_Priv,cniname);
IHsvPresetSortImpl(CSvcPats_Priv,prsort);
public:
ProvidesInterface<IHsvCniPresetName>	cniname;

ProvidesInterface<IHsvPresetSort>	prsort;

//Required interfaces
public:
RequiresInterface<ICesCountryIds>	countid;
RequiresInterface<ICesPatsDiv>	div;
RequiresInterface<IHsvLanguageIds2>	langid;
RequiresInterface<IHsvMemoryPool>	mem;
RequiresInterface<IMemoryOperations>	memo;
RequiresInterface<IString>	str;
RequiresInterface<IHsvTcSystemSettings>	sysset;

public:
CSvcPats_Priv():i__cniname(this),i__prsort(this)
{
cniname	=	&i__cniname;
prsort	=	&i__prsort;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define countid_iPresent() (countid.Present())
#define countid_CountryAustria	ICesCountryIds_CountryAustria
#define countid_CountryBelgium	ICesCountryIds_CountryBelgium
#define countid_CountryCroatia	ICesCountryIds_CountryCroatia
#define countid_CountryCzechrep	ICesCountryIds_CountryCzechrep
#define countid_CountryDenmark	ICesCountryIds_CountryDenmark
#define countid_CountryFinland	ICesCountryIds_CountryFinland
#define countid_CountryFrance	ICesCountryIds_CountryFrance
#define countid_CountryGermany	ICesCountryIds_CountryGermany
#define countid_CountryGreece	ICesCountryIds_CountryGreece
#define countid_CountryHungary	ICesCountryIds_CountryHungary
#define countid_CountryIreland	ICesCountryIds_CountryIreland
#define countid_CountryItaly	ICesCountryIds_CountryItaly
#define countid_CountryLuxembourg	ICesCountryIds_CountryLuxembourg
#define countid_CountryNetherlands	ICesCountryIds_CountryNetherlands
#define countid_CountryNorway	ICesCountryIds_CountryNorway
#define countid_CountryPoland	ICesCountryIds_CountryPoland
#define countid_CountryPortugal	ICesCountryIds_CountryPortugal
#define countid_CountryRomania	ICesCountryIds_CountryRomania
#define countid_CountryRussia	ICesCountryIds_CountryRussia
#define countid_CountrySerbia	ICesCountryIds_CountrySerbia
#define countid_CountrySlovakia	ICesCountryIds_CountrySlovakia
#define countid_CountrySlovenia	ICesCountryIds_CountrySlovenia
#define countid_CountrySpain	ICesCountryIds_CountrySpain
#define countid_CountrySweden	ICesCountryIds_CountrySweden
#define countid_CountrySwitzerland	ICesCountryIds_CountrySwitzerland
#define countid_CountryTurkey	ICesCountryIds_CountryTurkey
#define countid_CountryUK	ICesCountryIds_CountryUK
#define countid_CountryOther	ICesCountryIds_CountryOther
#define countid_CountryAustralia	ICesCountryIds_CountryAustralia
#define countid_CountryEstonia	ICesCountryIds_CountryEstonia
#define countid_CountryLithuania	ICesCountryIds_CountryLithuania
#define countid_CountryLatvia	ICesCountryIds_CountryLatvia
#define countid_CountryKazakhstan	ICesCountryIds_CountryKazakhstan
#define countid_CountryBulgaria	ICesCountryIds_CountryBulgaria
#define countid_CountryChina	ICesCountryIds_CountryChina
#define countid_CountryUkraine	ICesCountryIds_CountryUkraine
#define countid_CountryBrazil	ICesCountryIds_CountryBrazil
#define countid_CountryArgentina	ICesCountryIds_CountryArgentina
#define countid_CountryAlbania	ICesCountryIds_CountryAlbania
#define countid_CountryArmenia	ICesCountryIds_CountryArmenia
#define countid_CountryAzerbaijan	ICesCountryIds_CountryAzerbaijan
#define countid_CountryBelarus	ICesCountryIds_CountryBelarus
#define countid_CountryBosniaAndHerzegovina	ICesCountryIds_CountryBosniaAndHerzegovina
#define countid_CountryGeorgia	ICesCountryIds_CountryGeorgia
#define countid_CountryMontenegro	ICesCountryIds_CountryMontenegro
#define countid_CountryIsrael	ICesCountryIds_CountryIsrael
#define countid_CountryMacedoniafyrom	ICesCountryIds_CountryMacedoniafyrom
#define countid_CountryParaguay	ICesCountryIds_CountryParaguay
#define countid_CountryUruguay	ICesCountryIds_CountryUruguay
#define countid_CountryThailand	ICesCountryIds_CountryThailand
#define countid_CountryNewZealand	ICesCountryIds_CountryNewZealand
#define countid_CountrySingapore	ICesCountryIds_CountrySingapore
#define countid_CountryMalaysia	ICesCountryIds_CountryMalaysia
#define countid_CountryTaiwan	ICesCountryIds_CountryTaiwan
#define countid_CountryIndonesia	ICesCountryIds_CountryIndonesia
#define countid_CountryMax	ICesCountryIds_CountryMax
#define countid_CountryInvalid	ICesCountryIds_CountryInvalid
#define countid_iVersion	countid->iVersion()
#define div_iPresent() (div.Present())
#define div_PresetNameLength	ICesPatsDiv_PresetNameLength
#define div_MaxPresets	ICesPatsDiv_MaxPresets
#define div_GetDefaultPresetName	div->GetDefaultPresetName()
#define langid_iPresent() (langid.Present())
#define langid_LangEnglish	IHsvLanguageIds2_LangEnglish
#define langid_LangGerman	IHsvLanguageIds2_LangGerman
#define langid_LangSwedish	IHsvLanguageIds2_LangSwedish
#define langid_LangItalian	IHsvLanguageIds2_LangItalian
#define langid_LangFrench	IHsvLanguageIds2_LangFrench
#define langid_LangSpanish	IHsvLanguageIds2_LangSpanish
#define langid_LangCzech	IHsvLanguageIds2_LangCzech
#define langid_LangPolish	IHsvLanguageIds2_LangPolish
#define langid_LangTurkish	IHsvLanguageIds2_LangTurkish
#define langid_LangRussian	IHsvLanguageIds2_LangRussian
#define langid_LangGreek	IHsvLanguageIds2_LangGreek
#define langid_LangBasque	IHsvLanguageIds2_LangBasque
#define langid_LangCatalan	IHsvLanguageIds2_LangCatalan
#define langid_LangCroatian	IHsvLanguageIds2_LangCroatian
#define langid_LangDanish	IHsvLanguageIds2_LangDanish
#define langid_LangDutch	IHsvLanguageIds2_LangDutch
#define langid_LangFinnish	IHsvLanguageIds2_LangFinnish
#define langid_LangGaelic	IHsvLanguageIds2_LangGaelic
#define langid_LangGalligan	IHsvLanguageIds2_LangGalligan
#define langid_LangNorwegian	IHsvLanguageIds2_LangNorwegian
#define langid_LangPortuguese	IHsvLanguageIds2_LangPortuguese
#define langid_LangSerbian	IHsvLanguageIds2_LangSerbian
#define langid_LangSlovak	IHsvLanguageIds2_LangSlovak
#define langid_LangSlovenian	IHsvLanguageIds2_LangSlovenian
#define langid_LangWelsh	IHsvLanguageIds2_LangWelsh
#define langid_LangRomanian	IHsvLanguageIds2_LangRomanian
#define langid_LangEstonian	IHsvLanguageIds2_LangEstonian
#define langid_LangUkrainian	IHsvLanguageIds2_LangUkrainian
#define langid_LangArabic	IHsvLanguageIds2_LangArabic
#define langid_LangHebrew	IHsvLanguageIds2_LangHebrew
#define langid_LangHungarian	IHsvLanguageIds2_LangHungarian
#define langid_LangHungal	IHsvLanguageIds2_LangHungal
#define langid_LangMalay	IHsvLanguageIds2_LangMalay
#define langid_LangPersian	IHsvLanguageIds2_LangPersian
#define langid_LangSimplifiedchinese	IHsvLanguageIds2_LangSimplifiedchinese
#define langid_LangTaiwanese	IHsvLanguageIds2_LangTaiwanese
#define langid_LangBrazilianPortuguese	IHsvLanguageIds2_LangBrazilianPortuguese
#define langid_LangBulgarian	IHsvLanguageIds2_LangBulgarian
#define langid_LangLatinspanish	IHsvLanguageIds2_LangLatinspanish
#define langid_LangLithuanian	IHsvLanguageIds2_LangLithuanian
#define langid_LangLatvian	IHsvLanguageIds2_LangLatvian
#define langid_LangKazakh	IHsvLanguageIds2_LangKazakh
#define langid_LangThai	IHsvLanguageIds2_LangThai
#define langid_LangIrish	IHsvLanguageIds2_LangIrish
#define langid_LangUndefined	IHsvLanguageIds2_LangUndefined
#define langid_LangOriginalVersion	IHsvLanguageIds2_LangOriginalVersion
#define langid_LangAudioDescription	IHsvLanguageIds2_LangAudioDescription
#define langid_LangNone	IHsvLanguageIds2_LangNone
#define langid_MaxNumberOfLanguages	langid->MaxNumberOfLanguages()
#define langid_iVersion	langid->iVersion()
#define mem_iPresent() (mem.Present())
#define mem_Init(poolid)	mem->Init(poolid)
#define mem_Malloc(poolid)	mem->Malloc(poolid)
#define mem_Free(poolid,addr)	mem->Free(poolid,addr)
#define memo_iPresent() (memo.Present())
#define memo_memcmp(ptr1,ptr2,num)	memo->memcmp(ptr1,ptr2,num)
#define memo_memcmpRom(ptr1,ptr2,num)	memo->memcmpRom(ptr1,ptr2,num)
#define memo_memcpy(dest,source,num)	memo->memcpy(dest,source,num)
#define memo_memcpyRom(dest,source,num)	memo->memcpyRom(dest,source,num)
#define memo_memmove(dest,source,num)	memo->memmove(dest,source,num)
#define memo_memset(ptr,val,num)	memo->memset(ptr,val,num)
#define str_iPresent() (str.Present())
#define str_strcmp(str1,str2)	str->strcmp(str1,str2)
#define str_strcmpRom(str1,str2)	str->strcmpRom(str1,str2)
#define str_strncmp(str1,str2,num)	str->strncmp(str1,str2,num)
#define str_strncmpRom(str1,str2,num)	str->strncmpRom(str1,str2,num)
#define str_strlen(str1)	str->strlen(str1)
#define str_strlenRom(str1)	str->strlenRom(str1)
#define str_strcpy(dest,source)	str->strcpy(dest,source)
#define str_strcpyRom(dest,source)	str->strcpyRom(dest,source)
#define str_strncpy(dest,source,num)	str->strncpy(dest,source,num)
#define str_strncpyRom(dest,source,num)	str->strncpyRom(dest,source,num)
#define str_strcat(dest,source)	str->strcat(dest,source)
#define str_strcatRom(dest,source)	str->strcatRom(dest,source)
#define str_strncat(dest,source,num)	str->strncat(dest,source,num)
#define str_strstr(book,word)	str->strstr(book,word)
#define str_strchr(book,letter)	str->strchr(book,letter)
#define sysset_iPresent() (sysset.Present())
#define sysset_AudioFormatStandard	IHsvTcSystemSettings_AudioFormatStandard
#define sysset_AudioFormatAdvanced	IHsvTcSystemSettings_AudioFormatAdvanced
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
#define cniname_CniNiInvalid	IHsvCniPresetName_CniNiInvalid
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
#include "locals_m.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

