#ifndef IHSVTXTPAGECONVERTNOTIFY_H
#define IHSVTXTPAGECONVERTNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtPageConvertNotify
{
public:
	virtual ~IHsvTxtPageConvertNotify(){}
	virtual void OnTxtPageConverted(void)= 0;
	virtual void OnTxtPageConversionTerminated(void)= 0;
	virtual void OnTxtRollingHeaderTerminated(void)= 0;
	virtual void OnTxtRow(int row,int row_colour)= 0;
	virtual void OnTxtPictureOn(void)= 0;
	virtual void OnTxtRevealCancel(void)= 0;
	virtual void OnTxtTopBottomScreenColour(Bool topbottom,int tbscreencol)= 0;
};


#define IHsvTxtPageConvertNotifyImpl(Comp,intf)    \
virtual void intf ## _OnTxtPageConverted(void);\
virtual void intf ## _OnTxtPageConversionTerminated(void);\
virtual void intf ## _OnTxtRollingHeaderTerminated(void);\
virtual void intf ## _OnTxtRow(int row,int row_colour);\
virtual void intf ## _OnTxtPictureOn(void);\
virtual void intf ## _OnTxtRevealCancel(void);\
virtual void intf ## _OnTxtTopBottomScreenColour(Bool topbottom,int tbscreencol);\
class Comp ## _ ## intf : public IHsvTxtPageConvertNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnTxtPageConverted(void){ return m_parent->intf ## _OnTxtPageConverted();}\
virtual void OnTxtPageConversionTerminated(void){ return m_parent->intf ## _OnTxtPageConversionTerminated();}\
virtual void OnTxtRollingHeaderTerminated(void){ return m_parent->intf ## _OnTxtRollingHeaderTerminated();}\
virtual void OnTxtRow(int row,int row_colour){ return m_parent->intf ## _OnTxtRow(row,row_colour);}\
virtual void OnTxtPictureOn(void){ return m_parent->intf ## _OnTxtPictureOn();}\
virtual void OnTxtRevealCancel(void){ return m_parent->intf ## _OnTxtRevealCancel();}\
virtual void OnTxtTopBottomScreenColour(Bool topbottom,int tbscreencol){ return m_parent->intf ## _OnTxtTopBottomScreenColour(topbottom,tbscreencol);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
