#ifndef IHSVACIDISPLAY_H
#define IHSVACIDISPLAY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAciDisplay
{
public:
	virtual ~IHsvAciDisplay(){}
	virtual void StartPageDisplay(void)= 0;
	virtual int GetNoOfMtpItems(void)= 0;
	virtual void SetCursor(Nat8 item)= 0;
	virtual void RemoveCursor(void)= 0;
	virtual void SelectIndex(int index)= 0;
};


#define IHsvAciDisplayImpl(Comp,intf)    \
virtual void intf ## _StartPageDisplay(void);\
virtual int intf ## _GetNoOfMtpItems(void);\
virtual void intf ## _SetCursor(Nat8 item);\
virtual void intf ## _RemoveCursor(void);\
virtual void intf ## _SelectIndex(int index);\
class Comp ## _ ## intf : public IHsvAciDisplay \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void StartPageDisplay(void){ return m_parent->intf ## _StartPageDisplay();}\
virtual int GetNoOfMtpItems(void){ return m_parent->intf ## _GetNoOfMtpItems();}\
virtual void SetCursor(Nat8 item){ return m_parent->intf ## _SetCursor(item);}\
virtual void RemoveCursor(void){ return m_parent->intf ## _RemoveCursor();}\
virtual void SelectIndex(int index){ return m_parent->intf ## _SelectIndex(index);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
