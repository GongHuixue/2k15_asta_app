#ifndef IHSVTEXTDISPLAY_H
#define IHSVTEXTDISPLAY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTextDisplay
{
public:
	virtual ~IHsvTextDisplay(){}
	virtual int MaxDisplayList(void)= 0;
	virtual int MaxClutSize(void)= 0;
	virtual Nat32 CreateHeader(int NoOfClutEntries)= 0;
	virtual void DeleteHeader(Nat32 headerId)= 0;
	virtual void TruncateHeader(Nat32 headerId,int sections)= 0;
	virtual void ResetHeader(Nat32 headerId)= 0;
	virtual Nat32 CreateString(Nat32 headerId,int maxChar,Nat32 ul_x,Nat32 ul_y)= 0;
	virtual void RepositionString(Nat32 stringId,Nat8 window,Nat16 pos,Nat32 ul_x,Nat32 ul_y)= 0;
	virtual Nat32 CreateFiller(Nat32 headerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y,Nat8 clutIndex)= 0;
	virtual void RepositionFiller(Nat32 fillerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y)= 0;
	virtual void SetFillerColor(Nat32 fillerId,Nat8 clutIndex)= 0;
	virtual void Configure(Nat32 multipleId,Nat32 Font,Nat32 width,Nat32 ht,Nat32 fntSize,Nat32 controlBits)= 0;
	virtual void GetBounds(Nat32 multipleId,Nat32 * ul_x,Nat32 * ul_y,Nat32 * lr_x,Nat32 * lr_y)= 0;
	virtual void SetVisibility(Nat32 multipleId,Bool visible)= 0;
	virtual Nat32 PackColors(Nat8 border,Nat8 flash,Nat8 back,Nat8 fore)= 0;
	virtual void SetBorderColor(Nat32 * pCharCol,Nat8 border)= 0;
	virtual void SetForeColor(Nat32 * pCharCol,Nat8 fore)= 0;
	virtual void SetBackColor(Nat32 * pCharCol,Nat8 back)= 0;
	virtual void SetFlashColor(Nat32 * pCharCol,Nat8 flash)= 0;
	virtual Nat8 GetBorderColor(Nat32 charCol)= 0;
	virtual Nat8 GetForeColor(Nat32 charCol)= 0;
	virtual Nat8 GetBackColor(Nat32 charCol)= 0;
	virtual Nat8 GetFlashColor(Nat32 charCol)= 0;
	virtual void AddCharacter(Nat32 stringId,Nat32 charBits,Nat32 charCol,Nat32 fntSize,Nat32 charCtrl)= 0;
	virtual void ModifyCharacters(Nat32 stringId,Nat32 charNum,Nat32 charBits,Nat32 CharCol,Nat32 fntSize,Nat32 borderstyle,Nat32 CharCtrl)= 0;
	virtual void CopyCharacters(Nat32 srcStringId,Nat32 dstStringId,Nat32 attrib)= 0;
	virtual void GetCharacter(Nat32 stringId,Nat32 charNum,Nat32 * CharBits,Nat32 * CharCol,Nat32 * CharCtrl,Nat32 * FntSize)= 0;
	virtual void GetCharacterAdvance(Nat32 CharBits,Nat32 CharCol,Nat32 CharCtrl,Nat32 * width,Nat32 * height)= 0;
	virtual void SetCursor(Nat32 headerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y)= 0;
	virtual void SetCursorVisiblity(Nat32 headerId,Bool onoff)= 0;
	virtual void SetCursorBorderColors(Nat32 headerId,int innerBox,int outerBox)= 0;
	virtual void SetColor(Nat32 headerId,int start,Nat8 noOfEntries,Nat32 * pColor)= 0;
	virtual Nat32 GetColor(Nat32 headerId,int clutindex)= 0;
	virtual Nat32 PackARGB(Nat8 alpha,Nat8 red,Nat8 green,Nat8 blue)= 0;
	virtual void UnPackARGB(Nat32 value,Nat8 * pAlpha,Nat8 * pRed,Nat8 * pGreen,Nat8 * pBlue)= 0;
	virtual void SetFlash(Bool onoff)= 0;
	virtual Nat32 StoreBitmaps(Nat32 headerId,Nat32 size,Nat32 * pInput,Nat8 inputType,Nat32 bitMapId)= 0;
	virtual void Draw(void)= 0;
	virtual void DrawTextPad(Nat8 window,Nat16 pos)= 0;
	virtual void Scroll(Nat8 window,Nat16 pos,Nat8 UpDown)= 0;
	virtual Bool Register(int clientId)= 0;
	virtual Bool UnRegister(int clientId)= 0;
	virtual void SetDisplayVisibility(Bool onOff)= 0;
	virtual Bool GetDisplayVisibility(void)= 0;
	virtual void AttachTextPad(Nat8 window,int pos,Nat32 headerId)= 0;
	virtual void DetachTextPad(Nat8 window,Nat16 pos)= 0;
	virtual void ScrollSetUp(Nat32 headerId,Nat8 ScrollIncr)= 0;
	virtual Bool GetRevealMode(Nat8 window)= 0;
	virtual void SetRevealMode(Nat8 window,Bool mode)= 0;
	virtual Bool GetMixMode(Nat8 window)= 0;
	virtual void SetMixedMode(Nat8 window,Bool mode)= 0;
	virtual Nat8 GetPageMode(void)= 0;
	virtual void SetPageMode(Nat8 mode)= 0;
	virtual void RowMapInit(void)= 0;
	virtual void RowMapInitPlain(void)= 0;
	virtual Nat32 SetUpRowMapEntry(Nat16 txtPadRow,Bool dispEn,Bool doubleHt,Bool showBottom)= 0;
	virtual void SetRowMapEntry(Nat8 window,Nat16 pos,Nat16 canvasRow,Nat32 rowEntry)= 0;
	virtual void SetRowMapRange(Nat8 window,Nat16 pos,Nat16 canvasRowStart,Nat16 rowCount,Nat32 rowEntry)= 0;
	virtual void SetFillerMap(Nat8 window,Nat16 topEndRow,Nat16 bottomStartRow)= 0;
};


#define IHsvTextDisplayImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual Nat32 intf ## _CreateHeader(int NoOfClutEntries);\
virtual void intf ## _DeleteHeader(Nat32 headerId);\
virtual void intf ## _TruncateHeader(Nat32 headerId,int sections);\
virtual void intf ## _ResetHeader(Nat32 headerId);\
virtual Nat32 intf ## _CreateString(Nat32 headerId,int maxChar,Nat32 ul_x,Nat32 ul_y);\
virtual void intf ## _RepositionString(Nat32 stringId,Nat8 window,Nat16 pos,Nat32 ul_x,Nat32 ul_y);\
virtual Nat32 intf ## _CreateFiller(Nat32 headerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y,Nat8 clutIndex);\
virtual void intf ## _RepositionFiller(Nat32 fillerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y);\
virtual void intf ## _SetFillerColor(Nat32 fillerId,Nat8 clutIndex);\
virtual void intf ## _Configure(Nat32 multipleId,Nat32 Font,Nat32 width,Nat32 ht,Nat32 fntSize,Nat32 controlBits);\
virtual void intf ## _GetBounds(Nat32 multipleId,Nat32 * ul_x,Nat32 * ul_y,Nat32 * lr_x,Nat32 * lr_y);\
virtual void intf ## _SetVisibility(Nat32 multipleId,Bool visible);\
virtual Nat32 intf ## _PackColors(Nat8 border,Nat8 flash,Nat8 back,Nat8 fore);\
virtual void intf ## _SetBorderColor(Nat32 * pCharCol,Nat8 border);\
virtual void intf ## _SetForeColor(Nat32 * pCharCol,Nat8 fore);\
virtual void intf ## _SetBackColor(Nat32 * pCharCol,Nat8 back);\
virtual void intf ## _SetFlashColor(Nat32 * pCharCol,Nat8 flash);\
virtual Nat8 intf ## _GetBorderColor(Nat32 charCol);\
virtual Nat8 intf ## _GetForeColor(Nat32 charCol);\
virtual Nat8 intf ## _GetBackColor(Nat32 charCol);\
virtual Nat8 intf ## _GetFlashColor(Nat32 charCol);\
virtual void intf ## _AddCharacter(Nat32 stringId,Nat32 charBits,Nat32 charCol,Nat32 fntSize,Nat32 charCtrl);\
virtual void intf ## _ModifyCharacters(Nat32 stringId,Nat32 charNum,Nat32 charBits,Nat32 CharCol,Nat32 fntSize,Nat32 borderstyle,Nat32 CharCtrl);\
virtual void intf ## _CopyCharacters(Nat32 srcStringId,Nat32 dstStringId,Nat32 attrib);\
virtual void intf ## _GetCharacter(Nat32 stringId,Nat32 charNum,Nat32 * CharBits,Nat32 * CharCol,Nat32 * CharCtrl,Nat32 * FntSize);\
virtual void intf ## _GetCharacterAdvance(Nat32 CharBits,Nat32 CharCol,Nat32 CharCtrl,Nat32 * width,Nat32 * height);\
virtual void intf ## _SetCursor(Nat32 headerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y);\
virtual void intf ## _SetCursorVisiblity(Nat32 headerId,Bool onoff);\
virtual void intf ## _SetCursorBorderColors(Nat32 headerId,int innerBox,int outerBox);\
virtual void intf ## _SetColor(Nat32 headerId,int start,Nat8 noOfEntries,Nat32 * pColor);\
virtual Nat32 intf ## _GetColor(Nat32 headerId,int clutindex);\
virtual Nat32 intf ## _PackARGB(Nat8 alpha,Nat8 red,Nat8 green,Nat8 blue);\
virtual void intf ## _UnPackARGB(Nat32 value,Nat8 * pAlpha,Nat8 * pRed,Nat8 * pGreen,Nat8 * pBlue);\
virtual void intf ## _SetFlash(Bool onoff);\
virtual Nat32 intf ## _StoreBitmaps(Nat32 headerId,Nat32 size,Nat32 * pInput,Nat8 inputType,Nat32 bitMapId);\
virtual void intf ## _Draw(void);\
virtual void intf ## _DrawTextPad(Nat8 window,Nat16 pos);\
virtual void intf ## _Scroll(Nat8 window,Nat16 pos,Nat8 UpDown);\
virtual Bool intf ## _Register(int clientId);\
virtual Bool intf ## _UnRegister(int clientId);\
virtual void intf ## _SetDisplayVisibility(Bool onOff);\
virtual Bool intf ## _GetDisplayVisibility(void);\
virtual void intf ## _AttachTextPad(Nat8 window,int pos,Nat32 headerId);\
virtual void intf ## _DetachTextPad(Nat8 window,Nat16 pos);\
virtual void intf ## _ScrollSetUp(Nat32 headerId,Nat8 ScrollIncr);\
virtual Bool intf ## _GetRevealMode(Nat8 window);\
virtual void intf ## _SetRevealMode(Nat8 window,Bool mode);\
virtual Bool intf ## _GetMixMode(Nat8 window);\
virtual void intf ## _SetMixedMode(Nat8 window,Bool mode);\
virtual Nat8 intf ## _GetPageMode(void);\
virtual void intf ## _SetPageMode(Nat8 mode);\
virtual void intf ## _RowMapInit(void);\
virtual void intf ## _RowMapInitPlain(void);\
virtual Nat32 intf ## _SetUpRowMapEntry(Nat16 txtPadRow,Bool dispEn,Bool doubleHt,Bool showBottom);\
virtual void intf ## _SetRowMapEntry(Nat8 window,Nat16 pos,Nat16 canvasRow,Nat32 rowEntry);\
virtual void intf ## _SetRowMapRange(Nat8 window,Nat16 pos,Nat16 canvasRowStart,Nat16 rowCount,Nat32 rowEntry);\
virtual void intf ## _SetFillerMap(Nat8 window,Nat16 topEndRow,Nat16 bottomStartRow);\
class Comp ## _ ## intf : public IHsvTextDisplay \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_MaxDisplayList; \
    InterfaceParam<Comp,int> m_MaxClutSize; \
    Comp ## _ ## intf( Comp *parent):m_MaxDisplayList(parent),m_MaxClutSize(parent) \
    {\
        m_parent = parent;\
    }\
virtual int MaxDisplayList(void){ return m_MaxDisplayList.Call();}\
virtual int MaxClutSize(void){ return m_MaxClutSize.Call();}\
virtual Nat32 CreateHeader(int NoOfClutEntries){ return m_parent->intf ## _CreateHeader(NoOfClutEntries);}\
virtual void DeleteHeader(Nat32 headerId){ return m_parent->intf ## _DeleteHeader(headerId);}\
virtual void TruncateHeader(Nat32 headerId,int sections){ return m_parent->intf ## _TruncateHeader(headerId,sections);}\
virtual void ResetHeader(Nat32 headerId){ return m_parent->intf ## _ResetHeader(headerId);}\
virtual Nat32 CreateString(Nat32 headerId,int maxChar,Nat32 ul_x,Nat32 ul_y){ return m_parent->intf ## _CreateString(headerId,maxChar,ul_x,ul_y);}\
virtual void RepositionString(Nat32 stringId,Nat8 window,Nat16 pos,Nat32 ul_x,Nat32 ul_y){ return m_parent->intf ## _RepositionString(stringId,window,pos,ul_x,ul_y);}\
virtual Nat32 CreateFiller(Nat32 headerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y,Nat8 clutIndex){ return m_parent->intf ## _CreateFiller(headerId,ul_x,ul_y,lr_x,lr_y,clutIndex);}\
virtual void RepositionFiller(Nat32 fillerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y){ return m_parent->intf ## _RepositionFiller(fillerId,ul_x,ul_y,lr_x,lr_y);}\
virtual void SetFillerColor(Nat32 fillerId,Nat8 clutIndex){ return m_parent->intf ## _SetFillerColor(fillerId,clutIndex);}\
virtual void Configure(Nat32 multipleId,Nat32 Font,Nat32 width,Nat32 ht,Nat32 fntSize,Nat32 controlBits){ return m_parent->intf ## _Configure(multipleId,Font,width,ht,fntSize,controlBits);}\
virtual void GetBounds(Nat32 multipleId,Nat32 * ul_x,Nat32 * ul_y,Nat32 * lr_x,Nat32 * lr_y){ return m_parent->intf ## _GetBounds(multipleId,ul_x,ul_y,lr_x,lr_y);}\
virtual void SetVisibility(Nat32 multipleId,Bool visible){ return m_parent->intf ## _SetVisibility(multipleId,visible);}\
virtual Nat32 PackColors(Nat8 border,Nat8 flash,Nat8 back,Nat8 fore){ return m_parent->intf ## _PackColors(border,flash,back,fore);}\
virtual void SetBorderColor(Nat32 * pCharCol,Nat8 border){ return m_parent->intf ## _SetBorderColor(pCharCol,border);}\
virtual void SetForeColor(Nat32 * pCharCol,Nat8 fore){ return m_parent->intf ## _SetForeColor(pCharCol,fore);}\
virtual void SetBackColor(Nat32 * pCharCol,Nat8 back){ return m_parent->intf ## _SetBackColor(pCharCol,back);}\
virtual void SetFlashColor(Nat32 * pCharCol,Nat8 flash){ return m_parent->intf ## _SetFlashColor(pCharCol,flash);}\
virtual Nat8 GetBorderColor(Nat32 charCol){ return m_parent->intf ## _GetBorderColor(charCol);}\
virtual Nat8 GetForeColor(Nat32 charCol){ return m_parent->intf ## _GetForeColor(charCol);}\
virtual Nat8 GetBackColor(Nat32 charCol){ return m_parent->intf ## _GetBackColor(charCol);}\
virtual Nat8 GetFlashColor(Nat32 charCol){ return m_parent->intf ## _GetFlashColor(charCol);}\
virtual void AddCharacter(Nat32 stringId,Nat32 charBits,Nat32 charCol,Nat32 fntSize,Nat32 charCtrl){ return m_parent->intf ## _AddCharacter(stringId,charBits,charCol,fntSize,charCtrl);}\
virtual void ModifyCharacters(Nat32 stringId,Nat32 charNum,Nat32 charBits,Nat32 CharCol,Nat32 fntSize,Nat32 borderstyle,Nat32 CharCtrl){ return m_parent->intf ## _ModifyCharacters(stringId,charNum,charBits,CharCol,fntSize,borderstyle,CharCtrl);}\
virtual void CopyCharacters(Nat32 srcStringId,Nat32 dstStringId,Nat32 attrib){ return m_parent->intf ## _CopyCharacters(srcStringId,dstStringId,attrib);}\
virtual void GetCharacter(Nat32 stringId,Nat32 charNum,Nat32 * CharBits,Nat32 * CharCol,Nat32 * CharCtrl,Nat32 * FntSize){ return m_parent->intf ## _GetCharacter(stringId,charNum,CharBits,CharCol,CharCtrl,FntSize);}\
virtual void GetCharacterAdvance(Nat32 CharBits,Nat32 CharCol,Nat32 CharCtrl,Nat32 * width,Nat32 * height){ return m_parent->intf ## _GetCharacterAdvance(CharBits,CharCol,CharCtrl,width,height);}\
virtual void SetCursor(Nat32 headerId,Nat32 ul_x,Nat32 ul_y,Nat32 lr_x,Nat32 lr_y){ return m_parent->intf ## _SetCursor(headerId,ul_x,ul_y,lr_x,lr_y);}\
virtual void SetCursorVisiblity(Nat32 headerId,Bool onoff){ return m_parent->intf ## _SetCursorVisiblity(headerId,onoff);}\
virtual void SetCursorBorderColors(Nat32 headerId,int innerBox,int outerBox){ return m_parent->intf ## _SetCursorBorderColors(headerId,innerBox,outerBox);}\
virtual void SetColor(Nat32 headerId,int start,Nat8 noOfEntries,Nat32 * pColor){ return m_parent->intf ## _SetColor(headerId,start,noOfEntries,pColor);}\
virtual Nat32 GetColor(Nat32 headerId,int clutindex){ return m_parent->intf ## _GetColor(headerId,clutindex);}\
virtual Nat32 PackARGB(Nat8 alpha,Nat8 red,Nat8 green,Nat8 blue){ return m_parent->intf ## _PackARGB(alpha,red,green,blue);}\
virtual void UnPackARGB(Nat32 value,Nat8 * pAlpha,Nat8 * pRed,Nat8 * pGreen,Nat8 * pBlue){ return m_parent->intf ## _UnPackARGB(value,pAlpha,pRed,pGreen,pBlue);}\
virtual void SetFlash(Bool onoff){ return m_parent->intf ## _SetFlash(onoff);}\
virtual Nat32 StoreBitmaps(Nat32 headerId,Nat32 size,Nat32 * pInput,Nat8 inputType,Nat32 bitMapId){ return m_parent->intf ## _StoreBitmaps(headerId,size,pInput,inputType,bitMapId);}\
virtual void Draw(void){ return m_parent->intf ## _Draw();}\
virtual void DrawTextPad(Nat8 window,Nat16 pos){ return m_parent->intf ## _DrawTextPad(window,pos);}\
virtual void Scroll(Nat8 window,Nat16 pos,Nat8 UpDown){ return m_parent->intf ## _Scroll(window,pos,UpDown);}\
virtual Bool Register(int clientId){ return m_parent->intf ## _Register(clientId);}\
virtual Bool UnRegister(int clientId){ return m_parent->intf ## _UnRegister(clientId);}\
virtual void SetDisplayVisibility(Bool onOff){ return m_parent->intf ## _SetDisplayVisibility(onOff);}\
virtual Bool GetDisplayVisibility(void){ return m_parent->intf ## _GetDisplayVisibility();}\
virtual void AttachTextPad(Nat8 window,int pos,Nat32 headerId){ return m_parent->intf ## _AttachTextPad(window,pos,headerId);}\
virtual void DetachTextPad(Nat8 window,Nat16 pos){ return m_parent->intf ## _DetachTextPad(window,pos);}\
virtual void ScrollSetUp(Nat32 headerId,Nat8 ScrollIncr){ return m_parent->intf ## _ScrollSetUp(headerId,ScrollIncr);}\
virtual Bool GetRevealMode(Nat8 window){ return m_parent->intf ## _GetRevealMode(window);}\
virtual void SetRevealMode(Nat8 window,Bool mode){ return m_parent->intf ## _SetRevealMode(window,mode);}\
virtual Bool GetMixMode(Nat8 window){ return m_parent->intf ## _GetMixMode(window);}\
virtual void SetMixedMode(Nat8 window,Bool mode){ return m_parent->intf ## _SetMixedMode(window,mode);}\
virtual Nat8 GetPageMode(void){ return m_parent->intf ## _GetPageMode();}\
virtual void SetPageMode(Nat8 mode){ return m_parent->intf ## _SetPageMode(mode);}\
virtual void RowMapInit(void){ return m_parent->intf ## _RowMapInit();}\
virtual void RowMapInitPlain(void){ return m_parent->intf ## _RowMapInitPlain();}\
virtual Nat32 SetUpRowMapEntry(Nat16 txtPadRow,Bool dispEn,Bool doubleHt,Bool showBottom){ return m_parent->intf ## _SetUpRowMapEntry(txtPadRow,dispEn,doubleHt,showBottom);}\
virtual void SetRowMapEntry(Nat8 window,Nat16 pos,Nat16 canvasRow,Nat32 rowEntry){ return m_parent->intf ## _SetRowMapEntry(window,pos,canvasRow,rowEntry);}\
virtual void SetRowMapRange(Nat8 window,Nat16 pos,Nat16 canvasRowStart,Nat16 rowCount,Nat32 rowEntry){ return m_parent->intf ## _SetRowMapRange(window,pos,canvasRowStart,rowCount,rowEntry);}\
virtual void SetFillerMap(Nat8 window,Nat16 topEndRow,Nat16 bottomStartRow){ return m_parent->intf ## _SetFillerMap(window,topEndRow,bottomStartRow);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
