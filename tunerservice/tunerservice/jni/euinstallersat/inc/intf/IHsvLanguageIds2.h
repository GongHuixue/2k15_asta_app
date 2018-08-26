#ifndef IHSVLANGUAGEIDS2_H
#define IHSVLANGUAGEIDS2_H
#include <intfparam.h>
#include <provreq.h>
class IHsvLanguageIds2
{
public:
	virtual ~IHsvLanguageIds2(){}
	#define IHsvLanguageIds2_LangEnglish		((int)0 )
	#define IHsvLanguageIds2_LangGerman		((int)1 )
	#define IHsvLanguageIds2_LangSwedish		((int)2 )
	#define IHsvLanguageIds2_LangItalian		((int)3 )
	#define IHsvLanguageIds2_LangFrench		((int)4 )
	#define IHsvLanguageIds2_LangSpanish		((int)5 )
	#define IHsvLanguageIds2_LangCzech		((int)6 )
	#define IHsvLanguageIds2_LangPolish		((int)7 )
	#define IHsvLanguageIds2_LangTurkish		((int)8 )
	#define IHsvLanguageIds2_LangRussian		((int)9 )
	#define IHsvLanguageIds2_LangGreek		((int)10 )
	#define IHsvLanguageIds2_LangBasque		((int)11 )
	#define IHsvLanguageIds2_LangCatalan		((int)12 )
	#define IHsvLanguageIds2_LangCroatian		((int)13 )
	#define IHsvLanguageIds2_LangDanish		((int)14 )
	#define IHsvLanguageIds2_LangDutch		((int)15 )
	#define IHsvLanguageIds2_LangFinnish		((int)16 )
	#define IHsvLanguageIds2_LangGaelic		((int)17 )
	#define IHsvLanguageIds2_LangGalligan		((int)18 )
	#define IHsvLanguageIds2_LangNorwegian		((int)19 )
	#define IHsvLanguageIds2_LangPortuguese		((int)20 )
	#define IHsvLanguageIds2_LangSerbian		((int)21 )
	#define IHsvLanguageIds2_LangSlovak		((int)22 )
	#define IHsvLanguageIds2_LangSlovenian		((int)23 )
	#define IHsvLanguageIds2_LangWelsh		((int)24 )
	#define IHsvLanguageIds2_LangRomanian		((int)25 )
	#define IHsvLanguageIds2_LangEstonian		((int)26 )
	#define IHsvLanguageIds2_LangUkrainian		((int)27 )
	#define IHsvLanguageIds2_LangArabic		((int)28 )
	#define IHsvLanguageIds2_LangHebrew		((int)29 )
	#define IHsvLanguageIds2_LangHungarian		((int)30 )
	#define IHsvLanguageIds2_LangHungal		((int)31 )
	#define IHsvLanguageIds2_LangMalay		((int)32 )
	#define IHsvLanguageIds2_LangPersian		((int)33 )
	#define IHsvLanguageIds2_LangSimplifiedchinese		((int)34 )
	#define IHsvLanguageIds2_LangTaiwanese		((int)35 )
	#define IHsvLanguageIds2_LangBrazilianPortuguese		((int)36 )
	#define IHsvLanguageIds2_LangBulgarian		((int)37 )
	#define IHsvLanguageIds2_LangLatinspanish		((int)38 )
	#define IHsvLanguageIds2_LangLithuanian		((int)39 )
	#define IHsvLanguageIds2_LangLatvian		((int)40 )
	#define IHsvLanguageIds2_LangKazakh		((int)41 )
	#define IHsvLanguageIds2_LangThai		((int)42 )
	#define IHsvLanguageIds2_LangIrish		((int)43 )
	#define IHsvLanguageIds2_LangUndefined		((int)44 )
	#define IHsvLanguageIds2_LangOriginalVersion		((int)45 )
	#define IHsvLanguageIds2_LangAudioDescription		((int)46 )
	#define IHsvLanguageIds2_LangORG		((int)47 )
	#define IHsvLanguageIds2_LangORJ		((int)48 )
	#define IHsvLanguageIds2_LangNone		((int)49 )
	#define IHsvLanguageIds2_MaxNumberOfLanguages		((int)50 )
	virtual int iVersion(void)= 0;
};


#define IHsvLanguageIds2Impl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvLanguageIds2 \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_iVersion; \
    Comp ## _ ## intf( Comp *parent):m_iVersion(parent) \
    {\
        m_parent = parent;\
    }\
virtual int iVersion(void){ return m_iVersion.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
