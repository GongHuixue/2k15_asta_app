#ifndef ITXTDISPLAYDRIVER3_H
#define ITXTDISPLAYDRIVER3_H
#include <intfparam.h>
#include <provreq.h>
class ITxtDisplayDriver3
{
public:
	virtual ~ITxtDisplayDriver3(){}
	virtual TWindowId OpenWindow(int PadType,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn)= 0;
	virtual void ClearWindow(TWindowId handl,int colour)= 0;
	virtual void WriteCharacter(TWindowId hand,Nat8 row,Nat8 col,Nat32 cc)= 0;
	virtual Nat32 ReadCharacter(TWindowId handl,Nat8 row,Nat8 col)= 0;
	virtual void WriteString(TWindowId handl,Nat8 row,Nat8 col,Nat8 len,Nat32 * string)= 0;
	virtual Nat8 GetWindowStartRow(TWindowId handl)= 0;
	virtual Nat8 GetWindowStartColumn(TWindowId handl)= 0;
	virtual Nat8 GetWindowEndRow(TWindowId handl)= 0;
	virtual Nat8 GetWindowEndColumn(TWindowId handl)= 0;
	virtual void CloseWindow(TWindowId handl)= 0;
	virtual void ChangeWindowCoordinates(TWindowId handl,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn)= 0;
	virtual void InitAttrCharacterCode(Nat32 * cc)= 0;
	virtual void SetAttrUnderlineSeparate(Nat32 * cc,Bool us)= 0;
	virtual Bool GetAttrUnderlineSeparate(Nat32 cc)= 0;
	virtual void SetAttrFontAndCharacter(Nat32 * cc,Font font,Language lng,int ch)= 0;
	virtual void SetAttrDoubleHeight(Nat32 * cc,Bool dh)= 0;
	virtual Bool GetAttrDoubleHeight(Nat32 cc)= 0;
	virtual void SetAttrDoubleWidth(Nat32 * cc,Bool dw)= 0;
	virtual Bool GetAttrDoubleWidth(Nat32 cc)= 0;
	virtual void SetAttrFlashMode(Nat32 * cc,Nat8 fm)= 0;
	virtual Nat8 GetAttrFlashMode(Nat32 cc)= 0;
	virtual void SetAttrFlashPhase(Nat32 * cc,Nat8 fp)= 0;
	virtual Nat8 GetAttrFlashPhase(Nat32 cc)= 0;
	virtual void SetAttrBox(Nat32 * cc,Bool box)= 0;
	virtual Bool GetAttrBox(Nat32 cc)= 0;
	virtual void SetAttrForegroundColour(Nat32 * cc,int fg)= 0;
	virtual int GetAttrForegroundColour(Nat32 cc)= 0;
	virtual void SetAttrBackgroundColour(Nat32 * cc,int bg)= 0;
	virtual int GetAttrBackgroundColour(Nat32 cc)= 0;
	virtual void SetConversionCurrentPosition(TWindowId handl,Nat8 row,Nat8 col)= 0;
	virtual Nat8 GetConversionCurrentRow(TWindowId handl)= 0;
	virtual Nat8 GetConversionCurrentColumn(TWindowId handl)= 0;
	virtual void SetConversionLanguageContext(TWindowId handl,Language lng)= 0;
	virtual Language GetConversionLanguageContext(TWindowId handl)= 0;
	virtual void SetConversionUnderlineSeparate(TWindowId handl,Bool ul_sep)= 0;
	virtual Bool GetConversionUnderlineSeparate(TWindowId handl)= 0;
	virtual void WriteConversionCharacter(TWindowId handl,int charcode,TConvAttrUnion ca)= 0;
	virtual void WriteConversionAccentedCharacter(TWindowId handl,int charcode,int accentcode,TConvAttrUnion ca)= 0;
	virtual void SetConversionAttributes(TWindowId handl,TConvAttrUnion ca)= 0;
	virtual Bool ConversionIsOnLeftSide(TWindowId handl)= 0;
	virtual void SetConvRowDisplayEnable(Nat8 row,Bool enb,Bool left)= 0;
	virtual Nat32* GetConvRowAttributesPointer(Nat8 row,Bool left)= 0;
	virtual void SetConvRowForeAndBackgroundColBank(Nat8 row,Bool fgColBank,Bool bgColBank,Bool left)= 0;
	virtual void SetConvRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left)= 0;
	virtual void SetScreenTopBottomColour(int colour,Bool tb,Bool left)= 0;
	virtual int GetScreenTopBottomColour(Bool tb,Bool left)= 0;
	virtual void SetScreenRowColour(Nat8 row,int colour,Bool left)= 0;
	virtual int GetScreenRowColour(Nat8 row,Bool left)= 0;
	virtual void SetScreenRowHeight(Nat8 row,int rh,Bool left)= 0;
	virtual int GetScreenRowHeight(Nat8 row,Bool left)= 0;
	virtual void SetRowsDoubleHeight(int start,Nat8 nr_rows,Bool dh)= 0;
	virtual void SetRowDisplayEnable(Nat8 row,Bool enb,Bool left)= 0;
	virtual void SetRowBoxEnable(Nat8 row,Bool enb,Bool left)= 0;
	virtual void SetRowNewsflashSubtitleEnable(Nat8 row,Bool enb,Bool left)= 0;
	virtual Bool GetRowNewsflashSubtitleEnable(Nat8 row,Bool left)= 0;
	virtual Nat32* GetRowAttributesPointer(Nat8 row,Bool left)= 0;
	virtual Nat8 GetRowForegroundColBank(Nat8 row,Bool left)= 0;
	virtual Nat8 GetRowBackgroundColBank(Nat8 row,Bool left)= 0;
	virtual void SetRowForeAndBackgroundColBank(Nat8 row,Bool fgColBank,Bool bgColBank,Bool left)= 0;
	virtual void SetRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left)= 0;
	virtual Bool GetRemapRowClutArea(Nat8 row,Bool fg,Bool left)= 0;
	virtual void SetRamPalette(int start,int count,Nat32 * rgba)= 0;
	virtual Nat32 GetBodyPadHeaderId(void)= 0;
	virtual Bool ReadGfxCharacter(TWindowId handl,Nat32 row,Nat32 col,Nat32 * charbits,Nat32 * charcol,Nat32 * charctrl)= 0;
	#define ITxtDisplayDriver3_FlashModeNone		((int)0 )
	#define ITxtDisplayDriver3_FlashModeNormal		((int)1 )
	#define ITxtDisplayDriver3_FlashModeInverse		((int)2 )
	#define ITxtDisplayDriver3_FlashModeColour		((int)3 )
	#define ITxtDisplayDriver3_FlashPhase1H50		((int)0 )
	#define ITxtDisplayDriver3_FlashPhase2H501		((int)1 )
	#define ITxtDisplayDriver3_FlashPhase2H502		((int)2 )
	#define ITxtDisplayDriver3_FlashPhase2H503		((int)3 )
	virtual int FillerPad(void)= 0;
	virtual int HeaderPad(void)= 0;
	virtual int TimePad(void)= 0;
	virtual int BodyPad(void)= 0;
	virtual int SidePanelL(void)= 0;
	virtual int SidePanelR(void)= 0;
	virtual int StatusPad(void)= 0;
};


#define ITxtDisplayDriver3Impl(Comp,intf)    \
virtual TWindowId intf ## _OpenWindow(int PadType,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn);\
virtual void intf ## _ClearWindow(TWindowId handl,int colour);\
virtual void intf ## _WriteCharacter(TWindowId hand,Nat8 row,Nat8 col,Nat32 cc);\
virtual Nat32 intf ## _ReadCharacter(TWindowId handl,Nat8 row,Nat8 col);\
virtual void intf ## _WriteString(TWindowId handl,Nat8 row,Nat8 col,Nat8 len,Nat32 * string);\
virtual Nat8 intf ## _GetWindowStartRow(TWindowId handl);\
virtual Nat8 intf ## _GetWindowStartColumn(TWindowId handl);\
virtual Nat8 intf ## _GetWindowEndRow(TWindowId handl);\
virtual Nat8 intf ## _GetWindowEndColumn(TWindowId handl);\
virtual void intf ## _CloseWindow(TWindowId handl);\
virtual void intf ## _ChangeWindowCoordinates(TWindowId handl,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn);\
virtual void intf ## _InitAttrCharacterCode(Nat32 * cc);\
virtual void intf ## _SetAttrUnderlineSeparate(Nat32 * cc,Bool us);\
virtual Bool intf ## _GetAttrUnderlineSeparate(Nat32 cc);\
virtual void intf ## _SetAttrFontAndCharacter(Nat32 * cc,Font font,Language lng,int ch);\
virtual void intf ## _SetAttrDoubleHeight(Nat32 * cc,Bool dh);\
virtual Bool intf ## _GetAttrDoubleHeight(Nat32 cc);\
virtual void intf ## _SetAttrDoubleWidth(Nat32 * cc,Bool dw);\
virtual Bool intf ## _GetAttrDoubleWidth(Nat32 cc);\
virtual void intf ## _SetAttrFlashMode(Nat32 * cc,Nat8 fm);\
virtual Nat8 intf ## _GetAttrFlashMode(Nat32 cc);\
virtual void intf ## _SetAttrFlashPhase(Nat32 * cc,Nat8 fp);\
virtual Nat8 intf ## _GetAttrFlashPhase(Nat32 cc);\
virtual void intf ## _SetAttrBox(Nat32 * cc,Bool box);\
virtual Bool intf ## _GetAttrBox(Nat32 cc);\
virtual void intf ## _SetAttrForegroundColour(Nat32 * cc,int fg);\
virtual int intf ## _GetAttrForegroundColour(Nat32 cc);\
virtual void intf ## _SetAttrBackgroundColour(Nat32 * cc,int bg);\
virtual int intf ## _GetAttrBackgroundColour(Nat32 cc);\
virtual void intf ## _SetConversionCurrentPosition(TWindowId handl,Nat8 row,Nat8 col);\
virtual Nat8 intf ## _GetConversionCurrentRow(TWindowId handl);\
virtual Nat8 intf ## _GetConversionCurrentColumn(TWindowId handl);\
virtual void intf ## _SetConversionLanguageContext(TWindowId handl,Language lng);\
virtual Language intf ## _GetConversionLanguageContext(TWindowId handl);\
virtual void intf ## _SetConversionUnderlineSeparate(TWindowId handl,Bool ul_sep);\
virtual Bool intf ## _GetConversionUnderlineSeparate(TWindowId handl);\
virtual void intf ## _WriteConversionCharacter(TWindowId handl,int charcode,TConvAttrUnion ca);\
virtual void intf ## _WriteConversionAccentedCharacter(TWindowId handl,int charcode,int accentcode,TConvAttrUnion ca);\
virtual void intf ## _SetConversionAttributes(TWindowId handl,TConvAttrUnion ca);\
virtual Bool intf ## _ConversionIsOnLeftSide(TWindowId handl);\
virtual void intf ## _SetConvRowDisplayEnable(Nat8 row,Bool enb,Bool left);\
virtual Nat32* intf ## _GetConvRowAttributesPointer(Nat8 row,Bool left);\
virtual void intf ## _SetConvRowForeAndBackgroundColBank(Nat8 row,Bool fgColBank,Bool bgColBank,Bool left);\
virtual void intf ## _SetConvRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left);\
virtual void intf ## _SetScreenTopBottomColour(int colour,Bool tb,Bool left);\
virtual int intf ## _GetScreenTopBottomColour(Bool tb,Bool left);\
virtual void intf ## _SetScreenRowColour(Nat8 row,int colour,Bool left);\
virtual int intf ## _GetScreenRowColour(Nat8 row,Bool left);\
virtual void intf ## _SetScreenRowHeight(Nat8 row,int rh,Bool left);\
virtual int intf ## _GetScreenRowHeight(Nat8 row,Bool left);\
virtual void intf ## _SetRowsDoubleHeight(int start,Nat8 nr_rows,Bool dh);\
virtual void intf ## _SetRowDisplayEnable(Nat8 row,Bool enb,Bool left);\
virtual void intf ## _SetRowBoxEnable(Nat8 row,Bool enb,Bool left);\
virtual void intf ## _SetRowNewsflashSubtitleEnable(Nat8 row,Bool enb,Bool left);\
virtual Bool intf ## _GetRowNewsflashSubtitleEnable(Nat8 row,Bool left);\
virtual Nat32* intf ## _GetRowAttributesPointer(Nat8 row,Bool left);\
virtual Nat8 intf ## _GetRowForegroundColBank(Nat8 row,Bool left);\
virtual Nat8 intf ## _GetRowBackgroundColBank(Nat8 row,Bool left);\
virtual void intf ## _SetRowForeAndBackgroundColBank(Nat8 row,Bool fgColBank,Bool bgColBank,Bool left);\
virtual void intf ## _SetRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left);\
virtual Bool intf ## _GetRemapRowClutArea(Nat8 row,Bool fg,Bool left);\
virtual void intf ## _SetRamPalette(int start,int count,Nat32 * rgba);\
virtual Nat32 intf ## _GetBodyPadHeaderId(void);\
virtual Bool intf ## _ReadGfxCharacter(TWindowId handl,Nat32 row,Nat32 col,Nat32 * charbits,Nat32 * charcol,Nat32 * charctrl);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public ITxtDisplayDriver3 \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_FillerPad; \
    InterfaceParam<Comp,int> m_HeaderPad; \
    InterfaceParam<Comp,int> m_TimePad; \
    InterfaceParam<Comp,int> m_BodyPad; \
    InterfaceParam<Comp,int> m_SidePanelL; \
    InterfaceParam<Comp,int> m_SidePanelR; \
    InterfaceParam<Comp,int> m_StatusPad; \
    Comp ## _ ## intf( Comp *parent):m_FillerPad(parent),m_HeaderPad(parent),m_TimePad(parent),m_BodyPad(parent),m_SidePanelL(parent),m_SidePanelR(parent),m_StatusPad(parent) \
    {\
        m_parent = parent;\
    }\
virtual TWindowId OpenWindow(int PadType,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn){ return m_parent->intf ## _OpenWindow(PadType,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn);}\
virtual void ClearWindow(TWindowId handl,int colour){ return m_parent->intf ## _ClearWindow(handl,colour);}\
virtual void WriteCharacter(TWindowId hand,Nat8 row,Nat8 col,Nat32 cc){ return m_parent->intf ## _WriteCharacter(hand,row,col,cc);}\
virtual Nat32 ReadCharacter(TWindowId handl,Nat8 row,Nat8 col){ return m_parent->intf ## _ReadCharacter(handl,row,col);}\
virtual void WriteString(TWindowId handl,Nat8 row,Nat8 col,Nat8 len,Nat32 * string){ return m_parent->intf ## _WriteString(handl,row,col,len,string);}\
virtual Nat8 GetWindowStartRow(TWindowId handl){ return m_parent->intf ## _GetWindowStartRow(handl);}\
virtual Nat8 GetWindowStartColumn(TWindowId handl){ return m_parent->intf ## _GetWindowStartColumn(handl);}\
virtual Nat8 GetWindowEndRow(TWindowId handl){ return m_parent->intf ## _GetWindowEndRow(handl);}\
virtual Nat8 GetWindowEndColumn(TWindowId handl){ return m_parent->intf ## _GetWindowEndColumn(handl);}\
virtual void CloseWindow(TWindowId handl){ return m_parent->intf ## _CloseWindow(handl);}\
virtual void ChangeWindowCoordinates(TWindowId handl,Nat8 TopLeftRow,Nat8 TopLeftColumn,Nat8 BottomRightRow,Nat8 BottomRightColumn){ return m_parent->intf ## _ChangeWindowCoordinates(handl,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn);}\
virtual void InitAttrCharacterCode(Nat32 * cc){ return m_parent->intf ## _InitAttrCharacterCode(cc);}\
virtual void SetAttrUnderlineSeparate(Nat32 * cc,Bool us){ return m_parent->intf ## _SetAttrUnderlineSeparate(cc,us);}\
virtual Bool GetAttrUnderlineSeparate(Nat32 cc){ return m_parent->intf ## _GetAttrUnderlineSeparate(cc);}\
virtual void SetAttrFontAndCharacter(Nat32 * cc,Font font,Language lng,int ch){ return m_parent->intf ## _SetAttrFontAndCharacter(cc,font,lng,ch);}\
virtual void SetAttrDoubleHeight(Nat32 * cc,Bool dh){ return m_parent->intf ## _SetAttrDoubleHeight(cc,dh);}\
virtual Bool GetAttrDoubleHeight(Nat32 cc){ return m_parent->intf ## _GetAttrDoubleHeight(cc);}\
virtual void SetAttrDoubleWidth(Nat32 * cc,Bool dw){ return m_parent->intf ## _SetAttrDoubleWidth(cc,dw);}\
virtual Bool GetAttrDoubleWidth(Nat32 cc){ return m_parent->intf ## _GetAttrDoubleWidth(cc);}\
virtual void SetAttrFlashMode(Nat32 * cc,Nat8 fm){ return m_parent->intf ## _SetAttrFlashMode(cc,fm);}\
virtual Nat8 GetAttrFlashMode(Nat32 cc){ return m_parent->intf ## _GetAttrFlashMode(cc);}\
virtual void SetAttrFlashPhase(Nat32 * cc,Nat8 fp){ return m_parent->intf ## _SetAttrFlashPhase(cc,fp);}\
virtual Nat8 GetAttrFlashPhase(Nat32 cc){ return m_parent->intf ## _GetAttrFlashPhase(cc);}\
virtual void SetAttrBox(Nat32 * cc,Bool box){ return m_parent->intf ## _SetAttrBox(cc,box);}\
virtual Bool GetAttrBox(Nat32 cc){ return m_parent->intf ## _GetAttrBox(cc);}\
virtual void SetAttrForegroundColour(Nat32 * cc,int fg){ return m_parent->intf ## _SetAttrForegroundColour(cc,fg);}\
virtual int GetAttrForegroundColour(Nat32 cc){ return m_parent->intf ## _GetAttrForegroundColour(cc);}\
virtual void SetAttrBackgroundColour(Nat32 * cc,int bg){ return m_parent->intf ## _SetAttrBackgroundColour(cc,bg);}\
virtual int GetAttrBackgroundColour(Nat32 cc){ return m_parent->intf ## _GetAttrBackgroundColour(cc);}\
virtual void SetConversionCurrentPosition(TWindowId handl,Nat8 row,Nat8 col){ return m_parent->intf ## _SetConversionCurrentPosition(handl,row,col);}\
virtual Nat8 GetConversionCurrentRow(TWindowId handl){ return m_parent->intf ## _GetConversionCurrentRow(handl);}\
virtual Nat8 GetConversionCurrentColumn(TWindowId handl){ return m_parent->intf ## _GetConversionCurrentColumn(handl);}\
virtual void SetConversionLanguageContext(TWindowId handl,Language lng){ return m_parent->intf ## _SetConversionLanguageContext(handl,lng);}\
virtual Language GetConversionLanguageContext(TWindowId handl){ return m_parent->intf ## _GetConversionLanguageContext(handl);}\
virtual void SetConversionUnderlineSeparate(TWindowId handl,Bool ul_sep){ return m_parent->intf ## _SetConversionUnderlineSeparate(handl,ul_sep);}\
virtual Bool GetConversionUnderlineSeparate(TWindowId handl){ return m_parent->intf ## _GetConversionUnderlineSeparate(handl);}\
virtual void WriteConversionCharacter(TWindowId handl,int charcode,TConvAttrUnion ca){ return m_parent->intf ## _WriteConversionCharacter(handl,charcode,ca);}\
virtual void WriteConversionAccentedCharacter(TWindowId handl,int charcode,int accentcode,TConvAttrUnion ca){ return m_parent->intf ## _WriteConversionAccentedCharacter(handl,charcode,accentcode,ca);}\
virtual void SetConversionAttributes(TWindowId handl,TConvAttrUnion ca){ return m_parent->intf ## _SetConversionAttributes(handl,ca);}\
virtual Bool ConversionIsOnLeftSide(TWindowId handl){ return m_parent->intf ## _ConversionIsOnLeftSide(handl);}\
virtual void SetConvRowDisplayEnable(Nat8 row,Bool enb,Bool left){ return m_parent->intf ## _SetConvRowDisplayEnable(row,enb,left);}\
virtual Nat32* GetConvRowAttributesPointer(Nat8 row,Bool left){ return m_parent->intf ## _GetConvRowAttributesPointer(row,left);}\
virtual void SetConvRowForeAndBackgroundColBank(Nat8 row,Bool fgColBank,Bool bgColBank,Bool left){ return m_parent->intf ## _SetConvRowForeAndBackgroundColBank(row,fgColBank,bgColBank,left);}\
virtual void SetConvRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left){ return m_parent->intf ## _SetConvRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left);}\
virtual void SetScreenTopBottomColour(int colour,Bool tb,Bool left){ return m_parent->intf ## _SetScreenTopBottomColour(colour,tb,left);}\
virtual int GetScreenTopBottomColour(Bool tb,Bool left){ return m_parent->intf ## _GetScreenTopBottomColour(tb,left);}\
virtual void SetScreenRowColour(Nat8 row,int colour,Bool left){ return m_parent->intf ## _SetScreenRowColour(row,colour,left);}\
virtual int GetScreenRowColour(Nat8 row,Bool left){ return m_parent->intf ## _GetScreenRowColour(row,left);}\
virtual void SetScreenRowHeight(Nat8 row,int rh,Bool left){ return m_parent->intf ## _SetScreenRowHeight(row,rh,left);}\
virtual int GetScreenRowHeight(Nat8 row,Bool left){ return m_parent->intf ## _GetScreenRowHeight(row,left);}\
virtual void SetRowsDoubleHeight(int start,Nat8 nr_rows,Bool dh){ return m_parent->intf ## _SetRowsDoubleHeight(start,nr_rows,dh);}\
virtual void SetRowDisplayEnable(Nat8 row,Bool enb,Bool left){ return m_parent->intf ## _SetRowDisplayEnable(row,enb,left);}\
virtual void SetRowBoxEnable(Nat8 row,Bool enb,Bool left){ return m_parent->intf ## _SetRowBoxEnable(row,enb,left);}\
virtual void SetRowNewsflashSubtitleEnable(Nat8 row,Bool enb,Bool left){ return m_parent->intf ## _SetRowNewsflashSubtitleEnable(row,enb,left);}\
virtual Bool GetRowNewsflashSubtitleEnable(Nat8 row,Bool left){ return m_parent->intf ## _GetRowNewsflashSubtitleEnable(row,left);}\
virtual Nat32* GetRowAttributesPointer(Nat8 row,Bool left){ return m_parent->intf ## _GetRowAttributesPointer(row,left);}\
virtual Nat8 GetRowForegroundColBank(Nat8 row,Bool left){ return m_parent->intf ## _GetRowForegroundColBank(row,left);}\
virtual Nat8 GetRowBackgroundColBank(Nat8 row,Bool left){ return m_parent->intf ## _GetRowBackgroundColBank(row,left);}\
virtual void SetRowForeAndBackgroundColBank(Nat8 row,Bool fgColBank,Bool bgColBank,Bool left){ return m_parent->intf ## _SetRowForeAndBackgroundColBank(row,fgColBank,bgColBank,left);}\
virtual void SetRowForeAndBackgroundClutSelection(Nat8 row,Bool fgClutSel,Bool bgClutSel,Bool left){ return m_parent->intf ## _SetRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left);}\
virtual Bool GetRemapRowClutArea(Nat8 row,Bool fg,Bool left){ return m_parent->intf ## _GetRemapRowClutArea(row,fg,left);}\
virtual void SetRamPalette(int start,int count,Nat32 * rgba){ return m_parent->intf ## _SetRamPalette(start,count,rgba);}\
virtual Nat32 GetBodyPadHeaderId(void){ return m_parent->intf ## _GetBodyPadHeaderId();}\
virtual Bool ReadGfxCharacter(TWindowId handl,Nat32 row,Nat32 col,Nat32 * charbits,Nat32 * charcol,Nat32 * charctrl){ return m_parent->intf ## _ReadGfxCharacter(handl,row,col,charbits,charcol,charctrl);}\
virtual int FillerPad(void){ return m_FillerPad.Call();}\
virtual int HeaderPad(void){ return m_HeaderPad.Call();}\
virtual int TimePad(void){ return m_TimePad.Call();}\
virtual int BodyPad(void){ return m_BodyPad.Call();}\
virtual int SidePanelL(void){ return m_SidePanelL.Call();}\
virtual int SidePanelR(void){ return m_SidePanelR.Call();}\
virtual int StatusPad(void){ return m_StatusPad.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
