#ifndef IHSVINSTALLATIONCOUNTRYSPECIFICS_H
#define IHSVINSTALLATIONCOUNTRYSPECIFICS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallationCountrySpecifics
{
public:
	virtual ~IHsvInstallationCountrySpecifics(){}
	virtual Nat16* GetRankingList(int Country)= 0;
};


#define IHsvInstallationCountrySpecificsImpl(Comp,intf)    \
virtual Nat16* intf ## _GetRankingList(int Country);\
class Comp ## _ ## intf : public IHsvInstallationCountrySpecifics \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Nat16* GetRankingList(int Country){ return m_parent->intf ## _GetRankingList(Country);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
