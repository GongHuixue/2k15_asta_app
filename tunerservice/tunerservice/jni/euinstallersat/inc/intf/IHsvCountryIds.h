#ifndef IHSVCOUNTRYIDS_H
#define IHSVCOUNTRYIDS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCountryIds
{
public:
	virtual ~IHsvCountryIds(){}
	#define IHsvCountryIds_CountryAustria		((int)0 )
	#define IHsvCountryIds_CountryBelgium		((int)1 )
	#define IHsvCountryIds_CountryCroatia		((int)2 )
	#define IHsvCountryIds_CountryCzechrep		((int)3 )
	#define IHsvCountryIds_CountryDenmark		((int)4 )
	#define IHsvCountryIds_CountryFinland		((int)5 )
	#define IHsvCountryIds_CountryFrance		((int)6 )
	#define IHsvCountryIds_CountryGermany		((int)7 )
	#define IHsvCountryIds_CountryGreece		((int)8 )
	#define IHsvCountryIds_CountryHungary		((int)9 )
	#define IHsvCountryIds_CountryIreland		((int)10 )
	#define IHsvCountryIds_CountryItaly		((int)11 )
	#define IHsvCountryIds_CountryLuxembourg		((int)12 )
	#define IHsvCountryIds_CountryNetherlands		((int)13 )
	#define IHsvCountryIds_CountryNorway		((int)14 )
	#define IHsvCountryIds_CountryPoland		((int)15 )
	#define IHsvCountryIds_CountryPortugal		((int)16 )
	#define IHsvCountryIds_CountryRomania		((int)17 )
	#define IHsvCountryIds_CountryRussia		((int)18 )
	#define IHsvCountryIds_CountrySerbia		((int)19 )
	#define IHsvCountryIds_CountrySlovakia		((int)20 )
	#define IHsvCountryIds_CountrySlovenia		((int)21 )
	#define IHsvCountryIds_CountrySpain		((int)22 )
	#define IHsvCountryIds_CountrySweden		((int)23 )
	#define IHsvCountryIds_CountrySwitzerland		((int)24 )
	#define IHsvCountryIds_CountryTurkey		((int)25 )
	#define IHsvCountryIds_CountryUK		((int)26 )
	#define IHsvCountryIds_CountryOther		((int)27 )
	#define IHsvCountryIds_CountryAustralia		((int)28 )
	#define IHsvCountryIds_CountryEstonia		((int)29 )
	#define IHsvCountryIds_CountryLithuania		((int)30 )
	#define IHsvCountryIds_CountryLatvia		((int)31 )
	#define IHsvCountryIds_CountryKazakhstan		((int)32 )
	#define IHsvCountryIds_CountryBulgaria		((int)33 )
	#define IHsvCountryIds_CountryChina		((int)34 )
	#define IHsvCountryIds_CountryUkraine		((int)35 )
	#define IHsvCountryIds_CountryBrazil		((int)36 )
	#define IHsvCountryIds_CountryArgentina		((int)37 )
	#define IHsvCountryIds_CountryAlbania		((int)38 )
	#define IHsvCountryIds_CountryArmenia		((int)39 )
	#define IHsvCountryIds_CountryAzerbaijan		((int)40 )
	#define IHsvCountryIds_CountryBelarus		((int)41 )
	#define IHsvCountryIds_CountryBosniaAndHerzegovina		((int)42 )
	#define IHsvCountryIds_CountryGeorgia		((int)43 )
	#define IHsvCountryIds_CountryMontenegro		((int)44 )
	#define IHsvCountryIds_CountryIsrael		((int)45 )
	#define IHsvCountryIds_CountryMacedoniafyrom		((int)46 )
	#define IHsvCountryIds_CountryMax		((int)47 )
};


#define IHsvCountryIdsImpl(Comp,intf)    \
class Comp ## _ ## intf : public IHsvCountryIds \
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
