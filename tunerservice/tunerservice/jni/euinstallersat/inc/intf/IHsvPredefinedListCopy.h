#ifndef IHSVPREDEFINEDLISTCOPY_H
#define IHSVPREDEFINEDLISTCOPY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPredefinedListCopy
{
public:
	virtual ~IHsvPredefinedListCopy(){}
	virtual FResult StartPredefinedListCopy(void)= 0;
};


#define IHsvPredefinedListCopyImpl(Comp,intf)    \
virtual FResult intf ## _StartPredefinedListCopy(void);\
class Comp ## _ ## intf : public IHsvPredefinedListCopy \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult StartPredefinedListCopy(void){ return m_parent->intf ## _StartPredefinedListCopy();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
