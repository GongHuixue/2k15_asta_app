#ifndef IHSVACINAVIGATION_H
#define IHSVACINAVIGATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAciNavigation
{
public:
	virtual ~IHsvAciNavigation(){}
	#define IHsvAciNavigation_MinRow		((int)2 )
	#define IHsvAciNavigation_MaxRow		((int)22 )
	#define IHsvAciNavigation_NoRow		((int)-1 )
	virtual void SetCursor(int row)= 0;
	virtual int GetCursor(void)= 0;
};


#define IHsvAciNavigationImpl(Comp,intf)    \
virtual void intf ## _SetCursor(int row);\
virtual int intf ## _GetCursor(void);\
class Comp ## _ ## intf : public IHsvAciNavigation \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void SetCursor(int row){ return m_parent->intf ## _SetCursor(row);}\
virtual int GetCursor(void){ return m_parent->intf ## _GetCursor();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
