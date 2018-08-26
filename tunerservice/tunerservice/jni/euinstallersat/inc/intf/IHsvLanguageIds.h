#ifndef IHSVLANGUAGEIDS_H
#define IHSVLANGUAGEIDS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvLanguageIds
{
public:
	virtual ~IHsvLanguageIds(){}
	#define IHsvLanguageIds_LangEnglish		((int)0 )
	#define IHsvLanguageIds_LangGerman		((int)1 )
	#define IHsvLanguageIds_LangSwedish		((int)2 )
	#define IHsvLanguageIds_LangItalian		((int)3 )
	#define IHsvLanguageIds_LangFrench		((int)4 )
	#define IHsvLanguageIds_LangSpanish		((int)5 )
	#define IHsvLanguageIds_LangCzechSlovak		((int)6 )
	#define IHsvLanguageIds_LangPolish		((int)7 )
	#define IHsvLanguageIds_LangTurkish		((int)8 )
	#define IHsvLanguageIds_LangRumainian		((int)9 )
	#define IHsvLanguageIds_LangRussian		((int)10 )
	#define IHsvLanguageIds_LangEstonian		((int)11 )
	#define IHsvLanguageIds_LangUkrainian		((int)12 )
	#define IHsvLanguageIds_LangGreek		((int)13 )
	#define IHsvLanguageIds_LangArabic		((int)14 )
	#define IHsvLanguageIds_LangHebrew		((int)15 )
	#define IHsvLanguageIds_LangUndefined		((int)16 )
	#define IHsvLanguageIds_MaxNumberOfLanguages		((int)16 )
};


#define IHsvLanguageIdsImpl(Comp,intf)    \
class Comp ## _ ## intf : public IHsvLanguageIds \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
};\
Comp ## _ ## intf i__ ## intf;


#endif
