#ifndef IPRODAPINVMSUBIDS_H
#define IPRODAPINVMSUBIDS_H
#include <intfparam.h>
#include <provreq.h>
class IProdApiNvmSubIds
{
public:
	virtual ~IProdApiNvmSubIds(){}
	#define IProdApiNvmSubIds_Apps		((int)0x0001 )
	#define IProdApiNvmSubIds_Deasvc		((int)0x0002 )
	#define IProdApiNvmSubIds_Epg		((int)0x0004 )
	#define IProdApiNvmSubIds_Txsvc		((int)0x0008 )
	#define IProdApiNvmSubIds_Fac		((int)0x0010 )
	#define IProdApiNvmSubIds_Tvsvc		((int)0x0020 )
	#define IProdApiNvmSubIds_Svpsc		((int)0x0040 )
	#define IProdApiNvmSubIds_Cetv		((int)0x0080 )
	#define IProdApiNvmSubIds_Ceinfra		((int)0x0100 )
	#define IProdApiNvmSubIds_Prod		((int)0x0200 )
	#define IProdApiNvmSubIds_Cbmhg		((int)0x0400 )
	#define IProdApiNvmSubIds_Tvint		((int)0x0800 )
	#define IProdApiNvmSubIds_NotAllowed		((int)0xFFFF )
};


#define IProdApiNvmSubIdsImpl(Comp,intf)    \
class Comp ## _ ## intf : public IProdApiNvmSubIds \
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
