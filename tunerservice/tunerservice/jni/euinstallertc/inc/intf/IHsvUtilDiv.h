#ifndef IHSVUTILDIV_H
#define IHSVUTILDIV_H
#include <intfparam.h>
#include <provreq.h>
class IHsvUtilDiv
{
public:
	virtual ~IHsvUtilDiv(){}
	virtual int DefaultCharacterTable(void)= 0;
	virtual Bool ForceCharacterTable(void)= 0;
	virtual int RegionalCharacterTable(void)= 0;
};


#define IHsvUtilDivImpl(Comp,intf)    \
virtual  int intf ## _DefaultCharacterTable(void);\
virtual  Bool intf ## _ForceCharacterTable(void);\
virtual  int intf ## _RegionalCharacterTable(void);\
class Comp ## _ ## intf : public IHsvUtilDiv \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_DefaultCharacterTable; \
    InterfaceParam<Comp,Bool> m_ForceCharacterTable; \
    InterfaceParam<Comp,int> m_RegionalCharacterTable; \
    Comp ## _ ## intf( Comp *parent):m_DefaultCharacterTable(parent),m_ForceCharacterTable(parent),m_RegionalCharacterTable(parent) \
    {\
        m_parent = parent;\
    }\
virtual int DefaultCharacterTable(void){ return m_parent->intf ## _DefaultCharacterTable();}\
virtual Bool ForceCharacterTable(void){ return m_parent->intf ## _ForceCharacterTable();}\
virtual int RegionalCharacterTable(void){ return m_parent->intf ## _RegionalCharacterTable();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
