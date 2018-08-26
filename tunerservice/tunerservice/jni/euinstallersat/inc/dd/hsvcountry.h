#define ASCII(X)    ( (Nat32) (X) )
#define COUNTRYCODE(X,Y,Z)  ( (ASCII(X) << 16) | (ASCII(Y) << 8) | ASCII(Z) )

#ifndef COUNTRYITEM
#define COUNTRYITEM(a, b, c)
#endif


COUNTRYITEM(	COUNTRYCODE('A','U','T'),            Austria    ,40)
COUNTRYITEM(	COUNTRYCODE('B','E','L'),            Belgium    ,56)  
COUNTRYITEM(	COUNTRYCODE('H','R','V'),            Croatia    ,191)
COUNTRYITEM(	COUNTRYCODE('C','Z','E'),            Czechrep   ,203)
COUNTRYITEM(	COUNTRYCODE('D','N','K'),            Denmark    ,208)
COUNTRYITEM(	COUNTRYCODE('F','I','N'),            Finland    ,246)
COUNTRYITEM(	COUNTRYCODE('F','R','A'),            France     ,250)
COUNTRYITEM(	COUNTRYCODE('D','E','U'),            Germany    ,276)
COUNTRYITEM(	COUNTRYCODE('G','R','C'),            Greece     ,300)
COUNTRYITEM(	COUNTRYCODE('H','U','N'),            Hungary    ,711)
COUNTRYITEM(	COUNTRYCODE('I','R','L'),            Ireland    ,372)
COUNTRYITEM(	COUNTRYCODE('I','T','A'),            Italy      ,380)
COUNTRYITEM(	COUNTRYCODE('L','U','X'),            Luxembourg ,56 )
COUNTRYITEM(	COUNTRYCODE('N','L','D'),            Netherlands ,528)
COUNTRYITEM(	COUNTRYCODE('N','O','R'),            Norway     ,578)
COUNTRYITEM(	COUNTRYCODE('P','O','L'),            Poland     ,616)
COUNTRYITEM(	COUNTRYCODE('P','R','T'),            Portugal   ,712)
COUNTRYITEM(	COUNTRYCODE('R','O','U'),            Romania    ,642)
COUNTRYITEM(	COUNTRYCODE('R','U','S'),            Russia     ,643)
COUNTRYITEM(	COUNTRYCODE('S','E','R'),            Serbia     ,687) 
COUNTRYITEM(	COUNTRYCODE('S','V','K'),            Slovakia   ,703)
COUNTRYITEM(	COUNTRYCODE('S','V','N'),            Slovenia   ,711)
COUNTRYITEM(	COUNTRYCODE('E','S','P'),            Spain      ,724)
COUNTRYITEM(	COUNTRYCODE('S','W','E'),            Sweden     ,753)
COUNTRYITEM(	COUNTRYCODE('C','H','E'),            Switzerland ,756)
COUNTRYITEM(	COUNTRYCODE('T','U','R'),            Turkey     ,792)
COUNTRYITEM(	COUNTRYCODE('G','B','R'),            UK         ,826)
COUNTRYITEM(	COUNTRYCODE('X','X','X'),            Other      ,1023)
COUNTRYITEM(	COUNTRYCODE('A','U','S'),            Australia  ,36)
COUNTRYITEM(	COUNTRYCODE('E','S','T'),            Estonia    ,233)
COUNTRYITEM(	COUNTRYCODE('L','T','U'),            Lithuania  ,440)
COUNTRYITEM(	COUNTRYCODE('C','H','N'),            China      ,156)
COUNTRYITEM(	COUNTRYCODE('L','V','A'),            Latvia     ,428)
COUNTRYITEM(	COUNTRYCODE('I','S','R'),            Israel     ,376)
COUNTRYITEM(	COUNTRYCODE('U','K','R'),            Ukraine    ,804)
COUNTRYITEM(	COUNTRYCODE('M','K','D'),            Macedoniafyrom  ,807)
COUNTRYITEM(	COUNTRYCODE('B','L','R'),            Belarus    ,112)

#undef COUNTRYITEM 



