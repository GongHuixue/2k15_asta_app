#ifndef  _CHSVEUROPEINSTALLATION_MSYSSET_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MSYSSET_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <ICesCountryIds.h>
#include <IHsvLanguageIds2.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_msysset_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_msysset_Priv::
#include "locals_msysset.h"

class CHsvEuropeInstallation_msysset_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_msysset_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_msysset.h"
#undef MEMBERVARS
//Provided interfaces
private:
ICesCountryIdsImpl(CHsvEuropeInstallation_msysset_Priv,icountid);
IHsvLanguageIds2Impl(CHsvEuropeInstallation_msysset_Priv,ilangid);
public:
ProvidesInterface<ICesCountryIds>	icountid;

ProvidesInterface<IHsvLanguageIds2>	ilangid;


public:
CHsvEuropeInstallation_msysset_Priv():i__icountid(this),i__ilangid(this)
{
icountid	=	&i__icountid;
ilangid	=	&i__ilangid;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define icountid_CountryAustria	ICesCountryIds_CountryAustria
#define icountid_CountryBelgium	ICesCountryIds_CountryBelgium
#define icountid_CountryCroatia	ICesCountryIds_CountryCroatia
#define icountid_CountryCzechrep	ICesCountryIds_CountryCzechrep
#define icountid_CountryDenmark	ICesCountryIds_CountryDenmark
#define icountid_CountryFinland	ICesCountryIds_CountryFinland
#define icountid_CountryFrance	ICesCountryIds_CountryFrance
#define icountid_CountryGermany	ICesCountryIds_CountryGermany
#define icountid_CountryGreece	ICesCountryIds_CountryGreece
#define icountid_CountryHungary	ICesCountryIds_CountryHungary
#define icountid_CountryIreland	ICesCountryIds_CountryIreland
#define icountid_CountryItaly	ICesCountryIds_CountryItaly
#define icountid_CountryLuxembourg	ICesCountryIds_CountryLuxembourg
#define icountid_CountryNetherlands	ICesCountryIds_CountryNetherlands
#define icountid_CountryNorway	ICesCountryIds_CountryNorway
#define icountid_CountryPoland	ICesCountryIds_CountryPoland
#define icountid_CountryPortugal	ICesCountryIds_CountryPortugal
#define icountid_CountryRomania	ICesCountryIds_CountryRomania
#define icountid_CountryRussia	ICesCountryIds_CountryRussia
#define icountid_CountrySerbia	ICesCountryIds_CountrySerbia
#define icountid_CountrySlovakia	ICesCountryIds_CountrySlovakia
#define icountid_CountrySlovenia	ICesCountryIds_CountrySlovenia
#define icountid_CountrySpain	ICesCountryIds_CountrySpain
#define icountid_CountrySweden	ICesCountryIds_CountrySweden
#define icountid_CountrySwitzerland	ICesCountryIds_CountrySwitzerland
#define icountid_CountryTurkey	ICesCountryIds_CountryTurkey
#define icountid_CountryUK	ICesCountryIds_CountryUK
#define icountid_CountryOther	ICesCountryIds_CountryOther
#define icountid_CountryAustralia	ICesCountryIds_CountryAustralia
#define icountid_CountryEstonia	ICesCountryIds_CountryEstonia
#define icountid_CountryLithuania	ICesCountryIds_CountryLithuania
#define icountid_CountryLatvia	ICesCountryIds_CountryLatvia
#define icountid_CountryKazakhstan	ICesCountryIds_CountryKazakhstan
#define icountid_CountryBulgaria	ICesCountryIds_CountryBulgaria
#define icountid_CountryChina	ICesCountryIds_CountryChina
#define icountid_CountryUkraine	ICesCountryIds_CountryUkraine
#define icountid_CountryBrazil	ICesCountryIds_CountryBrazil
#define icountid_CountryArgentina	ICesCountryIds_CountryArgentina
#define icountid_CountryAlbania	ICesCountryIds_CountryAlbania
#define icountid_CountryArmenia	ICesCountryIds_CountryArmenia
#define icountid_CountryAzerbaijan	ICesCountryIds_CountryAzerbaijan
#define icountid_CountryBelarus	ICesCountryIds_CountryBelarus
#define icountid_CountryBosniaAndHerzegovina	ICesCountryIds_CountryBosniaAndHerzegovina
#define icountid_CountryGeorgia	ICesCountryIds_CountryGeorgia
#define icountid_CountryMontenegro	ICesCountryIds_CountryMontenegro
#define icountid_CountryIsrael	ICesCountryIds_CountryIsrael
#define icountid_CountryMacedoniafyrom	ICesCountryIds_CountryMacedoniafyrom
#define cids_CountryParaguay	IHsvCountryIds_CountryParaguay
#define cids_CountryUruguay	IHsvCountryIds_CountryUruguay
#define cids_CountryThailand	IHsvCountryIds_CountryThailand
#define cids_CountryNewZealand	IHsvCountryIds_CountryNewZealand
#define cids_CountrySingapore	IHsvCountryIds_CountrySingapore
#define cids_CountryMalaysia	IHsvCountryIds_CountryMalaysia
#define cids_CountryTaiwan	IHsvCountryIds_CountryTaiwan
#define cids_CountryIndonesia	IHsvCountryIds_CountryIndonesia
#define cids_CountryUAE	IHsvCountryIds_CountryUAE
#define icountid_CountryMax	ICesCountryIds_CountryMax
#define icountid_CountryInvalid	ICesCountryIds_CountryInvalid
#define icountid_iVersion	i__icountid.m_iVersion
#define ilangid_LangEnglish	IHsvLanguageIds2_LangEnglish
#define ilangid_LangGerman	IHsvLanguageIds2_LangGerman
#define ilangid_LangSwedish	IHsvLanguageIds2_LangSwedish
#define ilangid_LangItalian	IHsvLanguageIds2_LangItalian
#define ilangid_LangFrench	IHsvLanguageIds2_LangFrench
#define ilangid_LangSpanish	IHsvLanguageIds2_LangSpanish
#define ilangid_LangCzech	IHsvLanguageIds2_LangCzech
#define ilangid_LangPolish	IHsvLanguageIds2_LangPolish
#define ilangid_LangTurkish	IHsvLanguageIds2_LangTurkish
#define ilangid_LangRussian	IHsvLanguageIds2_LangRussian
#define ilangid_LangGreek	IHsvLanguageIds2_LangGreek
#define ilangid_LangBasque	IHsvLanguageIds2_LangBasque
#define ilangid_LangCatalan	IHsvLanguageIds2_LangCatalan
#define ilangid_LangCroatian	IHsvLanguageIds2_LangCroatian
#define ilangid_LangDanish	IHsvLanguageIds2_LangDanish
#define ilangid_LangDutch	IHsvLanguageIds2_LangDutch
#define ilangid_LangFinnish	IHsvLanguageIds2_LangFinnish
#define ilangid_LangGaelic	IHsvLanguageIds2_LangGaelic
#define ilangid_LangGalligan	IHsvLanguageIds2_LangGalligan
#define ilangid_LangNorwegian	IHsvLanguageIds2_LangNorwegian
#define ilangid_LangPortuguese	IHsvLanguageIds2_LangPortuguese
#define ilangid_LangSerbian	IHsvLanguageIds2_LangSerbian
#define ilangid_LangSlovak	IHsvLanguageIds2_LangSlovak
#define ilangid_LangSlovenian	IHsvLanguageIds2_LangSlovenian
#define ilangid_LangWelsh	IHsvLanguageIds2_LangWelsh
#define ilangid_LangRomanian	IHsvLanguageIds2_LangRomanian
#define ilangid_LangEstonian	IHsvLanguageIds2_LangEstonian
#define ilangid_LangUkrainian	IHsvLanguageIds2_LangUkrainian
#define ilangid_LangArabic	IHsvLanguageIds2_LangArabic
#define ilangid_LangHebrew	IHsvLanguageIds2_LangHebrew
#define ilangid_LangHungarian	IHsvLanguageIds2_LangHungarian
#define ilangid_LangHungal	IHsvLanguageIds2_LangHungal
#define ilangid_LangMalay	IHsvLanguageIds2_LangMalay
#define ilangid_LangPersian	IHsvLanguageIds2_LangPersian
#define ilangid_LangSimplifiedchinese	IHsvLanguageIds2_LangSimplifiedchinese
#define ilangid_LangTaiwanese	IHsvLanguageIds2_LangTaiwanese
#define ilangid_LangBrazilianPortuguese	IHsvLanguageIds2_LangBrazilianPortuguese
#define ilangid_LangBulgarian	IHsvLanguageIds2_LangBulgarian
#define ilangid_LangLatinspanish	IHsvLanguageIds2_LangLatinspanish
#define ilangid_LangLithuanian	IHsvLanguageIds2_LangLithuanian
#define ilangid_LangLatvian	IHsvLanguageIds2_LangLatvian
#define ilangid_LangKazakh	IHsvLanguageIds2_LangKazakh
#define ilangid_LangThai	IHsvLanguageIds2_LangThai
#define ilangid_LangIrish	IHsvLanguageIds2_LangIrish
#define ilangid_LangUndefined	IHsvLanguageIds2_LangUndefined
#define ilangid_LangOriginalVersion	IHsvLanguageIds2_LangOriginalVersion
#define ilangid_LangAudioDescription	IHsvLanguageIds2_LangAudioDescription
#define ilangid_LangNone	IHsvLanguageIds2_LangNone
#define ilangid_MaxNumberOfLanguages	i__ilangid.m_MaxNumberOfLanguages
#define ilangid_iVersion	i__ilangid.m_iVersion
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
#include "locals_msysset.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

