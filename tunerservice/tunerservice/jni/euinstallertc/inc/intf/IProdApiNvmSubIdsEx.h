#ifndef IPRODAPINVMSUBIDSEX_H
#define IPRODAPINVMSUBIDSEX_H
#include <intfparam.h>
#include <provreq.h>
class IProdApiNvmSubIdsEx
{
public:
	virtual ~IProdApiNvmSubIdsEx(){}
	#define IProdApiNvmSubIdsEx_Apps		((int)0x000001 )
	#define IProdApiNvmSubIdsEx_Txt		((int)0x000002 )
	#define IProdApiNvmSubIdsEx_Epg		((int)0x000004 )
	#define IProdApiNvmSubIdsEx_Zap		((int)0x000008 )
	#define IProdApiNvmSubIdsEx_Dlna		((int)0x000010 )
	#define IProdApiNvmSubIdsEx_Ecd		((int)0x000020 )
	#define IProdApiNvmSubIdsEx_Skype		((int)0x000040 )
	#define IProdApiNvmSubIdsEx_Cetv		((int)0x000080 )
	#define IProdApiNvmSubIdsEx_Prod		((int)0x000200 )
	#define IProdApiNvmSubIdsEx_Cbmhg		((int)0x000400 )
	#define IProdApiNvmSubIdsEx_NetTv		((int)0x001000 )
	#define IProdApiNvmSubIdsEx_Play		((int)0x002000 )
	#define IProdApiNvmSubIdsEx_Dvbs2		((int)0x004000 )
	#define IProdApiNvmSubIdsEx_Eu		((int)0x008000 )
	#define IProdApiNvmSubIdsEx_Bra		((int)0x010000 )
	#define IProdApiNvmSubIdsEx_Home		((int)0x020000 )
	#define IProdApiNvmSubIdsEx_Demo		((int)0x040000 )
	#define IProdApiNvmSubIdsEx_Upg		((int)0x080000 )
	#define IProdApiNvmSubIdsEx_Tv		((int)0x100000 )
	#define IProdApiNvmSubIdsEx_Deasvc		((int)0x000002 )
	#define IProdApiNvmSubIdsEx_Txsvc		((int)0x000008 )
	#define IProdApiNvmSubIdsEx_Fac		((int)0x000010 )
	#define IProdApiNvmSubIdsEx_Tvsvc		((int)0x000020 )
	#define IProdApiNvmSubIdsEx_Svpsc		((int)0x000040 )
	#define IProdApiNvmSubIdsEx_Ceinfra		((int)0x000100 )
	#define IProdApiNvmSubIdsEx_Tvint		((int)0x000800 )
	#define IProdApiNvmSubIdsEx_Ols		((int)0x001000 )
	#define IProdApiNvmSubIdsEx_Media		((int)0x002000 )
	#define IProdApiNvmSubIdsEx_NotAllowed		((int)0xFFFF )
};


#define IProdApiNvmSubIdsExImpl(Comp,intf)    \
class Comp ## _ ## intf : public IProdApiNvmSubIdsEx \
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
