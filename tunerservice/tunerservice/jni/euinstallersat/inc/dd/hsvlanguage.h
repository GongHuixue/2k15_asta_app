#define ASCII(X)    ( (Nat32) (X) )
#define LANGUAGECODE(X,Y,Z)  ( (ASCII(X) << 16) | (ASCII(Y) << 8) | ASCII(Z) )

#ifndef LANGUAGEITEM
#define LANGUAGEITEM(a, b, c)
#endif


LANGUAGEITEM(	LANGUAGECODE('e','n','g'),            LangEnglish				,0)
LANGUAGEITEM(	LANGUAGECODE('g','e','r'),            LangGerman				,1)  
LANGUAGEITEM(	LANGUAGECODE('s','w','e'),            LangSwedish				,2)
LANGUAGEITEM(	LANGUAGECODE('i','t','a'),            LangItalian				,3)
LANGUAGEITEM(	LANGUAGECODE('f','r','e'),            LangFrench				,4)
LANGUAGEITEM(	LANGUAGECODE('s','p','a'),            LangSpanish				,5)
LANGUAGEITEM(	LANGUAGECODE('c','z','e'),            LangCzech					,6)
LANGUAGEITEM(	LANGUAGECODE('p','o','l'),            LangPolish				,7)
LANGUAGEITEM(	LANGUAGECODE('t','u','r'),            LangTurkish				,8)
LANGUAGEITEM(	LANGUAGECODE('r','u','s'),            LangRussian				,9)
LANGUAGEITEM(	LANGUAGECODE('g','r','e'),            LangGreek					,10)
LANGUAGEITEM(	LANGUAGECODE('b','a','q'),            LangBasque				,11)
LANGUAGEITEM(	LANGUAGECODE('c','a','t'),            LangCatalan				,12)
LANGUAGEITEM(	LANGUAGECODE('s','c','r'),            LangCroatian				,13)
LANGUAGEITEM(	LANGUAGECODE('d','a','n'),            LangDanish				,14)
LANGUAGEITEM(	LANGUAGECODE('d','u','t'),            LangDutch					,15)
LANGUAGEITEM(	LANGUAGECODE('f','i','n'),            LangFinnish				,16)
LANGUAGEITEM(	LANGUAGECODE('g','l','a'),            LangGaelic				,17)
LANGUAGEITEM(	LANGUAGECODE('g','l','g'),            LangGallegan				,18)
LANGUAGEITEM(	LANGUAGECODE('n','o','r'),            LangNorwegian				,19) 
LANGUAGEITEM(	LANGUAGECODE('p','o','r'),            LangPortugese				,20)
LANGUAGEITEM(	LANGUAGECODE('s','c','c'),            LangSerbian				,21)
LANGUAGEITEM(	LANGUAGECODE('s','l','o'),            LangSlovak				,22)
LANGUAGEITEM(	LANGUAGECODE('s','l','v'),            LangSlovenian				,23)
LANGUAGEITEM(	LANGUAGECODE('w','e','l'),            LangWelsh					,24)
LANGUAGEITEM(	LANGUAGECODE('r','u','m'),            LangRumainian				,25)
LANGUAGEITEM(	LANGUAGECODE('e','s','t'),            LangEstonian				,26)
LANGUAGEITEM(	LANGUAGECODE('u','k','r'),            LangUkrainian				,27)
LANGUAGEITEM(	LANGUAGECODE('a','r','a'),            LangArabic				,28)
LANGUAGEITEM(	LANGUAGECODE('h','e','b'),            LangHebrew				,29)
LANGUAGEITEM(	LANGUAGECODE('h','n','g'),            LangHungarian				,30)
LANGUAGEITEM(	LANGUAGECODE('h','u','n'),            LangHungal				,31)
LANGUAGEITEM(	LANGUAGECODE('m','a','l'),            LangMalay					,32)
LANGUAGEITEM(	LANGUAGECODE('p','e','r'),            LangPersian				,33)
LANGUAGEITEM(	LANGUAGECODE('c','h','i'),            LangSimplifiedchinese		,34)
LANGUAGEITEM(	LANGUAGECODE('t','a','i'),            LangTaiwanese				,35)
LANGUAGEITEM(	LANGUAGECODE('u','n','d'),            LangBrazilianPortuguese	,36)
LANGUAGEITEM(	LANGUAGECODE('b','u','l'),            LangBulgarian				,37)
LANGUAGEITEM(	LANGUAGECODE('u','n','d'),            LangLatinspanish			,38)
LANGUAGEITEM(	LANGUAGECODE('l','i','t'),            LangLithuanian			,39)
LANGUAGEITEM(	LANGUAGECODE('l','a','v'),            LangLatvian   			,40)
LANGUAGEITEM(	LANGUAGECODE('k','a','z'),            LangKazakh    			,41)
LANGUAGEITEM(	LANGUAGECODE('t','h','a'),            LangThai      			,42)
LANGUAGEITEM(	LANGUAGECODE('i','r','i'),            LangIrish     			,43)
LANGUAGEITEM(	LANGUAGECODE('u','n','d'),            LangUndefined				,39)

#undef LANGUAGEITEM 




