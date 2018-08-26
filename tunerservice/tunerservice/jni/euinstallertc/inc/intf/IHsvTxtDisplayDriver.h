#ifndef IHSVTXTDISPLAYDRIVER_H
#define IHSVTXTDISPLAYDRIVER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTxtDisplayDriver
{
public:
	virtual ~IHsvTxtDisplayDriver(){}
	virtual TWindowId OpenWindow(int PadType,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn)= 0;
	virtual void ClearWindow(TWindowId handl,int colour)= 0;
	virtual void CloseWindow(TWindowId handl)= 0;
	virtual void SetScreenRowColour(Nat8 row,int colour,Bool left)= 0;
	virtual void SetScreenTopBottomColour(int colour,Bool tb,Bool left)= 0;
	virtual void WriteString(TWindowId handl,Nat8 row,Nat8 col,Nat8 len,Nat32 * string)= 0;
	virtual void InitAttrCharacterCode(Nat32 * cc)= 0;
	virtual void SetConvRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left)= 0;
	virtual void SetRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left)= 0;
	virtual void SetScreenRowHeight(Nat8 row,int rh,Bool left)= 0;
	virtual void SetRowsDoubleHeight(int start,Nat8 nr_rows,Bool dh)= 0;
	virtual void SetRowDisplayEnable(Nat8 row,Bool enb,Bool left)= 0;
	virtual void SetRowBoxEnable(Nat8 row,Bool enb,Bool left)= 0;
	virtual void SetAttrBackgroundColour(Nat32 * cc,int bg)= 0;
	virtual void SetAttrForegroundColour(Nat32 * cc,int fg)= 0;
	virtual void SetAttrFontAndCharacter(Nat32 * cc,Font font,Language lng,int ch)= 0;
	virtual int FillerPad(void)= 0;
	virtual int BodyPad(void)= 0;
	virtual int SidePanelL(void)= 0;
	virtual int SidePanelR(void)= 0;
	virtual int StatusPad(void)= 0;
	virtual int HeaderPad(void)= 0;
	virtual int TimePad(void)= 0;
};


#define IHsvTxtDisplayDriverImpl(Comp,intf)    \
virtual TWindowId intf ## _OpenWindow(int PadType,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn);\
virtual void intf ## _ClearWindow(TWindowId handl,int colour);\
virtual void intf ## _CloseWindow(TWindowId handl);\
virtual void intf ## _SetScreenRowColour(Nat8 row,int colour,Bool left);\
virtual void intf ## _SetScreenTopBottomColour(int colour,Bool tb,Bool left);\
virtual void intf ## _WriteString(TWindowId handl,Nat8 row,Nat8 col,Nat8 len,Nat32 * string);\
virtual void intf ## _InitAttrCharacterCode(Nat32 * cc);\
virtual void intf ## _SetConvRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left);\
virtual void intf ## _SetRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left);\
virtual void intf ## _SetScreenRowHeight(Nat8 row,int rh,Bool left);\
virtual void intf ## _SetRowsDoubleHeight(int start,Nat8 nr_rows,Bool dh);\
virtual void intf ## _SetRowDisplayEnable(Nat8 row,Bool enb,Bool left);\
virtual void intf ## _SetRowBoxEnable(Nat8 row,Bool enb,Bool left);\
virtual void intf ## _SetAttrBackgroundColour(Nat32 * cc,int bg);\
virtual void intf ## _SetAttrForegroundColour(Nat32 * cc,int fg);\
virtual void intf ## _SetAttrFontAndCharacter(Nat32 * cc,Font font,Language lng,int ch);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvTxtDisplayDriver \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_FillerPad; \
    InterfaceParam<Comp,int> m_BodyPad; \
    InterfaceParam<Comp,int> m_SidePanelL; \
    InterfaceParam<Comp,int> m_SidePanelR; \
    InterfaceParam<Comp,int> m_StatusPad; \
    InterfaceParam<Comp,int> m_HeaderPad; \
    InterfaceParam<Comp,int> m_TimePad; \
    Comp ## _ ## intf( Comp *parent):m_FillerPad(parent),m_BodyPad(parent),m_SidePanelL(parent),m_SidePanelR(parent),m_StatusPad(parent),m_HeaderPad(parent),m_TimePad(parent) \
    {\
        m_parent = parent;\
    }\
virtual TWindowId OpenWindow(int PadType,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn){ return m_parent->intf ## _OpenWindow(PadType,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn);}\
virtual void ClearWindow(TWindowId handl,int colour){ return m_parent->intf ## _ClearWindow(handl,colour);}\
virtual void CloseWindow(TWindowId handl){ return m_parent->intf ## _CloseWindow(handl);}\
virtual void SetScreenRowColour(Nat8 row,int colour,Bool left){ return m_parent->intf ## _SetScreenRowColour(row,colour,left);}\
virtual void SetScreenTopBottomColour(int colour,Bool tb,Bool left){ return m_parent->intf ## _SetScreenTopBottomColour(colour,tb,left);}\
virtual void WriteString(TWindowId handl,Nat8 row,Nat8 col,Nat8 len,Nat32 * string){ return m_parent->intf ## _WriteString(handl,row,col,len,string);}\
virtual void InitAttrCharacterCode(Nat32 * cc){ return m_parent->intf ## _InitAttrCharacterCode(cc);}\
virtual void SetConvRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left){ return m_parent->intf ## _SetConvRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left);}\
virtual void SetRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left){ return m_parent->intf ## _SetRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left);}\
virtual void SetScreenRowHeight(Nat8 row,int rh,Bool left){ return m_parent->intf ## _SetScreenRowHeight(row,rh,left);}\
virtual void SetRowsDoubleHeight(int start,Nat8 nr_rows,Bool dh){ return m_parent->intf ## _SetRowsDoubleHeight(start,nr_rows,dh);}\
virtual void SetRowDisplayEnable(Nat8 row,Bool enb,Bool left){ return m_parent->intf ## _SetRowDisplayEnable(row,enb,left);}\
virtual void SetRowBoxEnable(Nat8 row,Bool enb,Bool left){ return m_parent->intf ## _SetRowBoxEnable(row,enb,left);}\
virtual void SetAttrBackgroundColour(Nat32 * cc,int bg){ return m_parent->intf ## _SetAttrBackgroundColour(cc,bg);}\
virtual void SetAttrForegroundColour(Nat32 * cc,int fg){ return m_parent->intf ## _SetAttrForegroundColour(cc,fg);}\
virtual void SetAttrFontAndCharacter(Nat32 * cc,Font font,Language lng,int ch){ return m_parent->intf ## _SetAttrFontAndCharacter(cc,font,lng,ch);}\
virtual int FillerPad(void){ return m_FillerPad.Call();}\
virtual int BodyPad(void){ return m_BodyPad.Call();}\
virtual int SidePanelL(void){ return m_SidePanelL.Call();}\
virtual int SidePanelR(void){ return m_SidePanelR.Call();}\
virtual int StatusPad(void){ return m_StatusPad.Call();}\
virtual int HeaderPad(void){ return m_HeaderPad.Call();}\
virtual int TimePad(void){ return m_TimePad.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
