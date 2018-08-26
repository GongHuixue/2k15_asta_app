#ifndef ITVCOLORDECODE2NOTIFYEX_H
#define ITVCOLORDECODE2NOTIFYEX_H
#include <intfparam.h>
#include <provreq.h>
class ITvColorDecode2NotifyEx
{
public:
	virtual ~ITvColorDecode2NotifyEx(){}
	virtual void OnColorSystemChanged(void)= 0;
	virtual void OnCombFilterActiveChanged(void)= 0;
};


#define ITvColorDecode2NotifyExImpl(Comp,intf)    \
virtual void intf ## _OnColorSystemChanged(void);\
virtual void intf ## _OnCombFilterActiveChanged(void);\
class Comp ## _ ## intf : public ITvColorDecode2NotifyEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnColorSystemChanged(void){ return m_parent->intf ## _OnColorSystemChanged();}\
virtual void OnCombFilterActiveChanged(void){ return m_parent->intf ## _OnCombFilterActiveChanged();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
