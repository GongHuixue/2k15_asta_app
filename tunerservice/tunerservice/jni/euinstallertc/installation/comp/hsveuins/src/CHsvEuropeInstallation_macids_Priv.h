#ifndef  _CHSVEUROPEINSTALLATION_MACIDS_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MACIDS_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciNavigation.h>
#include <ISvcCniData.h>
#include <IHsvTxtDisplayDriver.h>
#include <ITxtDisplayDriver3.h>
#include <IHsvTextDisplay.h>
#include <IAppApiTextDisplayConstants.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_macids_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_macids_Priv::
#include "locals_macids.h"

class CHsvEuropeInstallation_macids_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_macids_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_macids.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvAciNavigationImpl(CHsvEuropeInstallation_macids_Priv,iacinv);
ISvcCniDataImpl(CHsvEuropeInstallation_macids_Priv,svpaci_pgcni);
public:
ProvidesInterface<IHsvAciNavigation>	iacinv;

ProvidesInterface<ISvcCniData>	svpaci_pgcni;

//Required interfaces
public:
RequiresInterface<IHsvTxtDisplayDriver>	dsdrv;
RequiresInterface<ITxtDisplayDriver3>	dsdrv3;
RequiresInterface<IHsvTextDisplay>	gfxtxt;
RequiresInterface<IAppApiTextDisplayConstants>	txtdspcons;

public:
CHsvEuropeInstallation_macids_Priv():i__iacinv(this),i__svpaci_pgcni(this)
{
iacinv	=	&i__iacinv;
svpaci_pgcni	=	&i__svpaci_pgcni;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define dsdrv_iPresent() (dsdrv.Present())
#define dsdrv_OpenWindow(PadType,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn)	dsdrv->OpenWindow(PadType,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn)
#define dsdrv_ClearWindow(handl,colour)	dsdrv->ClearWindow(handl,colour)
#define dsdrv_CloseWindow(handl)	dsdrv->CloseWindow(handl)
#define dsdrv_SetScreenRowColour(row,colour,left)	dsdrv->SetScreenRowColour(row,colour,left)
#define dsdrv_SetScreenTopBottomColour(colour,tb,left)	dsdrv->SetScreenTopBottomColour(colour,tb,left)
#define dsdrv_WriteString(handl,row,col,len,string)	dsdrv->WriteString(handl,row,col,len,string)
#define dsdrv_InitAttrCharacterCode(cc)	dsdrv->InitAttrCharacterCode(cc)
#define dsdrv_SetConvRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left)	dsdrv->SetConvRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left)
#define dsdrv_SetRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left)	dsdrv->SetRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left)
#define dsdrv_SetScreenRowHeight(row,rh,left)	dsdrv->SetScreenRowHeight(row,rh,left)
#define dsdrv_SetRowsDoubleHeight(start,nr_rows,dh)	dsdrv->SetRowsDoubleHeight(start,nr_rows,dh)
#define dsdrv_SetRowDisplayEnable(row,enb,left)	dsdrv->SetRowDisplayEnable(row,enb,left)
#define dsdrv_SetRowBoxEnable(row,enb,left)	dsdrv->SetRowBoxEnable(row,enb,left)
#define dsdrv_SetAttrBackgroundColour(cc,bg)	dsdrv->SetAttrBackgroundColour(cc,bg)
#define dsdrv_SetAttrForegroundColour(cc,fg)	dsdrv->SetAttrForegroundColour(cc,fg)
#define dsdrv_SetAttrFontAndCharacter(cc,font,lng,ch)	dsdrv->SetAttrFontAndCharacter(cc,font,lng,ch)
#define dsdrv_FillerPad	dsdrv->FillerPad()
#define dsdrv_BodyPad	dsdrv->BodyPad()
#define dsdrv_SidePanelL	dsdrv->SidePanelL()
#define dsdrv_SidePanelR	dsdrv->SidePanelR()
#define dsdrv_StatusPad	dsdrv->StatusPad()
#define dsdrv_HeaderPad	dsdrv->HeaderPad()
#define dsdrv_TimePad	dsdrv->TimePad()
#define dsdrv3_iPresent() (dsdrv3.Present())
#define dsdrv3_OpenWindow(PadType,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn)	dsdrv3->OpenWindow(PadType,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn)
#define dsdrv3_ClearWindow(handl,colour)	dsdrv3->ClearWindow(handl,colour)
#define dsdrv3_WriteCharacter(hand,row,col,cc)	dsdrv3->WriteCharacter(hand,row,col,cc)
#define dsdrv3_ReadCharacter(handl,row,col)	dsdrv3->ReadCharacter(handl,row,col)
#define dsdrv3_WriteString(handl,row,col,len,string)	dsdrv3->WriteString(handl,row,col,len,string)
#define dsdrv3_GetWindowStartRow(handl)	dsdrv3->GetWindowStartRow(handl)
#define dsdrv3_GetWindowStartColumn(handl)	dsdrv3->GetWindowStartColumn(handl)
#define dsdrv3_GetWindowEndRow(handl)	dsdrv3->GetWindowEndRow(handl)
#define dsdrv3_GetWindowEndColumn(handl)	dsdrv3->GetWindowEndColumn(handl)
#define dsdrv3_CloseWindow(handl)	dsdrv3->CloseWindow(handl)
#define dsdrv3_ChangeWindowCoordinates(handl,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn)	dsdrv3->ChangeWindowCoordinates(handl,TopLeftRow,TopLeftColumn,BottomRightRow,BottomRightColumn)
#define dsdrv3_InitAttrCharacterCode(cc)	dsdrv3->InitAttrCharacterCode(cc)
#define dsdrv3_SetAttrUnderlineSeparate(cc,us)	dsdrv3->SetAttrUnderlineSeparate(cc,us)
#define dsdrv3_GetAttrUnderlineSeparate(cc)	dsdrv3->GetAttrUnderlineSeparate(cc)
#define dsdrv3_SetAttrFontAndCharacter(cc,font,lng,ch)	dsdrv3->SetAttrFontAndCharacter(cc,font,lng,ch)
#define dsdrv3_SetAttrDoubleHeight(cc,dh)	dsdrv3->SetAttrDoubleHeight(cc,dh)
#define dsdrv3_GetAttrDoubleHeight(cc)	dsdrv3->GetAttrDoubleHeight(cc)
#define dsdrv3_SetAttrDoubleWidth(cc,dw)	dsdrv3->SetAttrDoubleWidth(cc,dw)
#define dsdrv3_GetAttrDoubleWidth(cc)	dsdrv3->GetAttrDoubleWidth(cc)
#define dsdrv3_SetAttrFlashMode(cc,fm)	dsdrv3->SetAttrFlashMode(cc,fm)
#define dsdrv3_GetAttrFlashMode(cc)	dsdrv3->GetAttrFlashMode(cc)
#define dsdrv3_SetAttrFlashPhase(cc,fp)	dsdrv3->SetAttrFlashPhase(cc,fp)
#define dsdrv3_GetAttrFlashPhase(cc)	dsdrv3->GetAttrFlashPhase(cc)
#define dsdrv3_SetAttrBox(cc,box)	dsdrv3->SetAttrBox(cc,box)
#define dsdrv3_GetAttrBox(cc)	dsdrv3->GetAttrBox(cc)
#define dsdrv3_SetAttrForegroundColour(cc,fg)	dsdrv3->SetAttrForegroundColour(cc,fg)
#define dsdrv3_GetAttrForegroundColour(cc)	dsdrv3->GetAttrForegroundColour(cc)
#define dsdrv3_SetAttrBackgroundColour(cc,bg)	dsdrv3->SetAttrBackgroundColour(cc,bg)
#define dsdrv3_GetAttrBackgroundColour(cc)	dsdrv3->GetAttrBackgroundColour(cc)
#define dsdrv3_SetConversionCurrentPosition(handl,row,col)	dsdrv3->SetConversionCurrentPosition(handl,row,col)
#define dsdrv3_GetConversionCurrentRow(handl)	dsdrv3->GetConversionCurrentRow(handl)
#define dsdrv3_GetConversionCurrentColumn(handl)	dsdrv3->GetConversionCurrentColumn(handl)
#define dsdrv3_SetConversionLanguageContext(handl,lng)	dsdrv3->SetConversionLanguageContext(handl,lng)
#define dsdrv3_GetConversionLanguageContext(handl)	dsdrv3->GetConversionLanguageContext(handl)
#define dsdrv3_SetConversionUnderlineSeparate(handl,ul_sep)	dsdrv3->SetConversionUnderlineSeparate(handl,ul_sep)
#define dsdrv3_GetConversionUnderlineSeparate(handl)	dsdrv3->GetConversionUnderlineSeparate(handl)
#define dsdrv3_WriteConversionCharacter(handl,charcode,ca)	dsdrv3->WriteConversionCharacter(handl,charcode,ca)
#define dsdrv3_WriteConversionAccentedCharacter(handl,charcode,accentcode,ca)	dsdrv3->WriteConversionAccentedCharacter(handl,charcode,accentcode,ca)
#define dsdrv3_SetConversionAttributes(handl,ca)	dsdrv3->SetConversionAttributes(handl,ca)
#define dsdrv3_ConversionIsOnLeftSide(handl)	dsdrv3->ConversionIsOnLeftSide(handl)
#define dsdrv3_SetConvRowDisplayEnable(row,enb,left)	dsdrv3->SetConvRowDisplayEnable(row,enb,left)
#define dsdrv3_GetConvRowAttributesPointer(row,left)	dsdrv3->GetConvRowAttributesPointer(row,left)
#define dsdrv3_SetConvRowForeAndBackgroundColBank(row,fgColBank,bgColBank,left)	dsdrv3->SetConvRowForeAndBackgroundColBank(row,fgColBank,bgColBank,left)
#define dsdrv3_SetConvRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left)	dsdrv3->SetConvRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left)
#define dsdrv3_SetScreenTopBottomColour(colour,tb,left)	dsdrv3->SetScreenTopBottomColour(colour,tb,left)
#define dsdrv3_GetScreenTopBottomColour(tb,left)	dsdrv3->GetScreenTopBottomColour(tb,left)
#define dsdrv3_SetScreenRowColour(row,colour,left)	dsdrv3->SetScreenRowColour(row,colour,left)
#define dsdrv3_GetScreenRowColour(row,left)	dsdrv3->GetScreenRowColour(row,left)
#define dsdrv3_SetScreenRowHeight(row,rh,left)	dsdrv3->SetScreenRowHeight(row,rh,left)
#define dsdrv3_GetScreenRowHeight(row,left)	dsdrv3->GetScreenRowHeight(row,left)
#define dsdrv3_SetRowsDoubleHeight(start,nr_rows,dh)	dsdrv3->SetRowsDoubleHeight(start,nr_rows,dh)
#define dsdrv3_SetRowDisplayEnable(row,enb,left)	dsdrv3->SetRowDisplayEnable(row,enb,left)
#define dsdrv3_SetRowBoxEnable(row,enb,left)	dsdrv3->SetRowBoxEnable(row,enb,left)
#define dsdrv3_SetRowNewsflashSubtitleEnable(row,enb,left)	dsdrv3->SetRowNewsflashSubtitleEnable(row,enb,left)
#define dsdrv3_GetRowNewsflashSubtitleEnable(row,left)	dsdrv3->GetRowNewsflashSubtitleEnable(row,left)
#define dsdrv3_GetRowAttributesPointer(row,left)	dsdrv3->GetRowAttributesPointer(row,left)
#define dsdrv3_GetRowForegroundColBank(row,left)	dsdrv3->GetRowForegroundColBank(row,left)
#define dsdrv3_GetRowBackgroundColBank(row,left)	dsdrv3->GetRowBackgroundColBank(row,left)
#define dsdrv3_SetRowForeAndBackgroundColBank(row,fgColBank,bgColBank,left)	dsdrv3->SetRowForeAndBackgroundColBank(row,fgColBank,bgColBank,left)
#define dsdrv3_SetRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left)	dsdrv3->SetRowForeAndBackgroundClutSelection(row,fgClutSel,bgClutSel,left)
#define dsdrv3_GetRemapRowClutArea(row,fg,left)	dsdrv3->GetRemapRowClutArea(row,fg,left)
#define dsdrv3_SetRamPalette(start,count,rgba)	dsdrv3->SetRamPalette(start,count,rgba)
#define dsdrv3_GetBodyPadHeaderId()	dsdrv3->GetBodyPadHeaderId()
#define dsdrv3_ReadGfxCharacter(handl,row,col,charbits,charcol,charctrl)	dsdrv3->ReadGfxCharacter(handl,row,col,charbits,charcol,charctrl)
#define dsdrv3_FlashModeNone	ITxtDisplayDriver3_FlashModeNone
#define dsdrv3_FlashModeNormal	ITxtDisplayDriver3_FlashModeNormal
#define dsdrv3_FlashModeInverse	ITxtDisplayDriver3_FlashModeInverse
#define dsdrv3_FlashModeColour	ITxtDisplayDriver3_FlashModeColour
#define dsdrv3_FlashPhase1H50	ITxtDisplayDriver3_FlashPhase1H50
#define dsdrv3_FlashPhase2H501	ITxtDisplayDriver3_FlashPhase2H501
#define dsdrv3_FlashPhase2H502	ITxtDisplayDriver3_FlashPhase2H502
#define dsdrv3_FlashPhase2H503	ITxtDisplayDriver3_FlashPhase2H503
#define dsdrv3_FillerPad	dsdrv3->FillerPad()
#define dsdrv3_HeaderPad	dsdrv3->HeaderPad()
#define dsdrv3_TimePad	dsdrv3->TimePad()
#define dsdrv3_BodyPad	dsdrv3->BodyPad()
#define dsdrv3_SidePanelL	dsdrv3->SidePanelL()
#define dsdrv3_SidePanelR	dsdrv3->SidePanelR()
#define dsdrv3_StatusPad	dsdrv3->StatusPad()
#define gfxtxt_iPresent() (gfxtxt.Present())
#define gfxtxt_MaxDisplayList	gfxtxt->MaxDisplayList()
#define gfxtxt_MaxClutSize	gfxtxt->MaxClutSize()
#define gfxtxt_CreateHeader(NoOfClutEntries)	gfxtxt->CreateHeader(NoOfClutEntries)
#define gfxtxt_DeleteHeader(headerId)	gfxtxt->DeleteHeader(headerId)
#define gfxtxt_TruncateHeader(headerId,sections)	gfxtxt->TruncateHeader(headerId,sections)
#define gfxtxt_ResetHeader(headerId)	gfxtxt->ResetHeader(headerId)
#define gfxtxt_CreateString(headerId,maxChar,ul_x,ul_y)	gfxtxt->CreateString(headerId,maxChar,ul_x,ul_y)
#define gfxtxt_RepositionString(stringId,window,pos,ul_x,ul_y)	gfxtxt->RepositionString(stringId,window,pos,ul_x,ul_y)
#define gfxtxt_CreateFiller(headerId,ul_x,ul_y,lr_x,lr_y,clutIndex)	gfxtxt->CreateFiller(headerId,ul_x,ul_y,lr_x,lr_y,clutIndex)
#define gfxtxt_RepositionFiller(fillerId,ul_x,ul_y,lr_x,lr_y)	gfxtxt->RepositionFiller(fillerId,ul_x,ul_y,lr_x,lr_y)
#define gfxtxt_SetFillerColor(fillerId,clutIndex)	gfxtxt->SetFillerColor(fillerId,clutIndex)
#define gfxtxt_Configure(multipleId,Font,width,ht,fntSize,controlBits)	gfxtxt->Configure(multipleId,Font,width,ht,fntSize,controlBits)
#define gfxtxt_GetBounds(multipleId,ul_x,ul_y,lr_x,lr_y)	gfxtxt->GetBounds(multipleId,ul_x,ul_y,lr_x,lr_y)
#define gfxtxt_SetVisibility(multipleId,visible)	gfxtxt->SetVisibility(multipleId,visible)
#define gfxtxt_PackColors(border,flash,back,fore)	gfxtxt->PackColors(border,flash,back,fore)
#define gfxtxt_SetBorderColor(pCharCol,border)	gfxtxt->SetBorderColor(pCharCol,border)
#define gfxtxt_SetForeColor(pCharCol,fore)	gfxtxt->SetForeColor(pCharCol,fore)
#define gfxtxt_SetBackColor(pCharCol,back)	gfxtxt->SetBackColor(pCharCol,back)
#define gfxtxt_SetFlashColor(pCharCol,flash)	gfxtxt->SetFlashColor(pCharCol,flash)
#define gfxtxt_GetBorderColor(charCol)	gfxtxt->GetBorderColor(charCol)
#define gfxtxt_GetForeColor(charCol)	gfxtxt->GetForeColor(charCol)
#define gfxtxt_GetBackColor(charCol)	gfxtxt->GetBackColor(charCol)
#define gfxtxt_GetFlashColor(charCol)	gfxtxt->GetFlashColor(charCol)
#define gfxtxt_AddCharacter(stringId,charBits,charCol,fntSize,charCtrl)	gfxtxt->AddCharacter(stringId,charBits,charCol,fntSize,charCtrl)
#define gfxtxt_ModifyCharacters(stringId,charNum,charBits,CharCol,fntSize,borderstyle,CharCtrl)	gfxtxt->ModifyCharacters(stringId,charNum,charBits,CharCol,fntSize,borderstyle,CharCtrl)
#define gfxtxt_CopyCharacters(srcStringId,dstStringId,attrib)	gfxtxt->CopyCharacters(srcStringId,dstStringId,attrib)
#define gfxtxt_GetCharacter(stringId,charNum,CharBits,CharCol,CharCtrl,FntSize)	gfxtxt->GetCharacter(stringId,charNum,CharBits,CharCol,CharCtrl,FntSize)
#define gfxtxt_GetCharacterAdvance(CharBits,CharCol,CharCtrl,width,height)	gfxtxt->GetCharacterAdvance(CharBits,CharCol,CharCtrl,width,height)
#define gfxtxt_SetCursor(headerId,ul_x,ul_y,lr_x,lr_y)	gfxtxt->SetCursor(headerId,ul_x,ul_y,lr_x,lr_y)
#define gfxtxt_SetCursorVisiblity(headerId,onoff)	gfxtxt->SetCursorVisiblity(headerId,onoff)
#define gfxtxt_SetCursorBorderColors(headerId,innerBox,outerBox)	gfxtxt->SetCursorBorderColors(headerId,innerBox,outerBox)
#define gfxtxt_SetColor(headerId,start,noOfEntries,pColor)	gfxtxt->SetColor(headerId,start,noOfEntries,pColor)
#define gfxtxt_GetColor(headerId,clutindex)	gfxtxt->GetColor(headerId,clutindex)
#define gfxtxt_PackARGB(alpha,red,green,blue)	gfxtxt->PackARGB(alpha,red,green,blue)
#define gfxtxt_UnPackARGB(value,pAlpha,pRed,pGreen,pBlue)	gfxtxt->UnPackARGB(value,pAlpha,pRed,pGreen,pBlue)
#define gfxtxt_SetFlash(onoff)	gfxtxt->SetFlash(onoff)
#define gfxtxt_StoreBitmaps(headerId,size,pInput,inputType,bitMapId)	gfxtxt->StoreBitmaps(headerId,size,pInput,inputType,bitMapId)
#define gfxtxt_Draw()	gfxtxt->Draw()
#define gfxtxt_DrawTextPad(window,pos)	gfxtxt->DrawTextPad(window,pos)
#define gfxtxt_Scroll(window,pos,UpDown)	gfxtxt->Scroll(window,pos,UpDown)
#define gfxtxt_Register(clientId)	gfxtxt->Register(clientId)
#define gfxtxt_UnRegister(clientId)	gfxtxt->UnRegister(clientId)
#define gfxtxt_SetDisplayVisibility(onOff)	gfxtxt->SetDisplayVisibility(onOff)
#define gfxtxt_GetDisplayVisibility()	gfxtxt->GetDisplayVisibility()
#define gfxtxt_AttachTextPad(window,pos,headerId)	gfxtxt->AttachTextPad(window,pos,headerId)
#define gfxtxt_DetachTextPad(window,pos)	gfxtxt->DetachTextPad(window,pos)
#define gfxtxt_ScrollSetUp(headerId,ScrollIncr)	gfxtxt->ScrollSetUp(headerId,ScrollIncr)
#define gfxtxt_GetRevealMode(window)	gfxtxt->GetRevealMode(window)
#define gfxtxt_SetRevealMode(window,mode)	gfxtxt->SetRevealMode(window,mode)
#define gfxtxt_GetMixMode(window)	gfxtxt->GetMixMode(window)
#define gfxtxt_SetMixedMode(window,mode)	gfxtxt->SetMixedMode(window,mode)
#define gfxtxt_GetPageMode()	gfxtxt->GetPageMode()
#define gfxtxt_SetPageMode(mode)	gfxtxt->SetPageMode(mode)
#define gfxtxt_RowMapInit()	gfxtxt->RowMapInit()
#define gfxtxt_RowMapInitPlain()	gfxtxt->RowMapInitPlain()
#define gfxtxt_SetUpRowMapEntry(txtPadRow,dispEn,doubleHt,showBottom)	gfxtxt->SetUpRowMapEntry(txtPadRow,dispEn,doubleHt,showBottom)
#define gfxtxt_SetRowMapEntry(window,pos,canvasRow,rowEntry)	gfxtxt->SetRowMapEntry(window,pos,canvasRow,rowEntry)
#define gfxtxt_SetRowMapRange(window,pos,canvasRowStart,rowCount,rowEntry)	gfxtxt->SetRowMapRange(window,pos,canvasRowStart,rowCount,rowEntry)
#define gfxtxt_SetFillerMap(window,topEndRow,bottomStartRow)	gfxtxt->SetFillerMap(window,topEndRow,bottomStartRow)
#define txtdspcons_iPresent() (txtdspcons.Present())
#define txtdspcons_ShadowLeft	txtdspcons->ShadowLeft()
#define txtdspcons_ShadowTop	txtdspcons->ShadowTop()
#define txtdspcons_ShadowRight	txtdspcons->ShadowRight()
#define txtdspcons_ShadowBottom	txtdspcons->ShadowBottom()
#define txtdspcons_ShadowAll	txtdspcons->ShadowAll()
#define txtdspcons_ShadowHeader	txtdspcons->ShadowHeader()
#define txtdspcons_ShadowFlash	txtdspcons->ShadowFlash()
#define txtdspcons_Rounded	txtdspcons->Rounded()
#define txtdspcons_Revealed	txtdspcons->Revealed()
#define txtdspcons_CharMode	txtdspcons->CharMode()
#define txtdspcons_GlobalDoubleHeight	txtdspcons->GlobalDoubleHeight()
#define txtdspcons_GlobalDoubleWidth	txtdspcons->GlobalDoubleWidth()
#define txtdspcons_StandardTextFont	txtdspcons->StandardTextFont()
#define txtdspcons_FontDigitalCC	txtdspcons->FontDigitalCC()
#define txtdspcons_gNone	txtdspcons->gNone()
#define txtdspcons_gRaised	txtdspcons->gRaised()
#define txtdspcons_gDepressed	txtdspcons->gDepressed()
#define txtdspcons_gUniform	txtdspcons->gUniform()
#define txtdspcons_gDropShadowLeft	txtdspcons->gDropShadowLeft()
#define txtdspcons_gDropShadowRight	txtdspcons->gDropShadowRight()
#define txtdspcons_FontField	txtdspcons->FontField()
#define txtdspcons_ColorField	txtdspcons->ColorField()
#define txtdspcons_ControlField	txtdspcons->ControlField()
#define txtdspcons_FontSizeField	txtdspcons->FontSizeField()
#define txtdspcons_BorderStyleField	txtdspcons->BorderStyleField()
#define txtdspcons_Translate	txtdspcons->Translate()
#define txtdspcons_DHFromFont	txtdspcons->DHFromFont()
#define txtdspcons_Space	txtdspcons->Space()
#define txtdspcons_Conceal	txtdspcons->Conceal()
#define txtdspcons_Dheight	txtdspcons->Dheight()
#define txtdspcons_Dwidth	txtdspcons->Dwidth()
#define txtdspcons_UnderLine	txtdspcons->UnderLine()
#define txtdspcons_AdvanceChar	txtdspcons->AdvanceChar()
#define txtdspcons_AdvancePixel	txtdspcons->AdvancePixel()
#define txtdspcons_AdvanceDraw	txtdspcons->AdvanceDraw()
#define txtdspcons_Invert	txtdspcons->Invert()
#define txtdspcons_RoundX	txtdspcons->RoundX()
#define txtdspcons_BackSpace	txtdspcons->BackSpace()
#define txtdspcons_FlashFieldMask	txtdspcons->FlashFieldMask()
#define txtdspcons_FlashTypeMask	txtdspcons->FlashTypeMask()
#define txtdspcons_FlashTypeNone	txtdspcons->FlashTypeNone()
#define txtdspcons_FlashTypeNormal	txtdspcons->FlashTypeNormal()
#define txtdspcons_FlashTypeInvert	txtdspcons->FlashTypeInvert()
#define txtdspcons_FlashTypeFlashColor	txtdspcons->FlashTypeFlashColor()
#define txtdspcons_FlashPhaseMask	txtdspcons->FlashPhaseMask()
#define txtdspcons_FlashPhase1Hz	txtdspcons->FlashPhase1Hz()
#define txtdspcons_FlashPhase2HzPhase1	txtdspcons->FlashPhase2HzPhase1()
#define txtdspcons_FlashPhase2HzPhase2	txtdspcons->FlashPhase2HzPhase2()
#define txtdspcons_FlashPhase2HzPhase3	txtdspcons->FlashPhase2HzPhase3()
#define txtdspcons_DheightTop	txtdspcons->DheightTop()
#define txtdspcons_DheightBottom	txtdspcons->DheightBottom()
#define txtdspcons_SeparatedMosiac	txtdspcons->SeparatedMosiac()
#define txtdspcons_Italics	txtdspcons->Italics()
#define txtdspcons_None	txtdspcons->None()
#define txtdspcons_Raised	txtdspcons->Raised()
#define txtdspcons_Depressed	txtdspcons->Depressed()
#define txtdspcons_Uniform	txtdspcons->Uniform()
#define txtdspcons_DropShadowLeft	txtdspcons->DropShadowLeft()
#define txtdspcons_DropShadowRight	txtdspcons->DropShadowRight()
#define txtdspcons_ForeGroundMask	txtdspcons->ForeGroundMask()
#define txtdspcons_BackGroundMask	txtdspcons->BackGroundMask()
#define txtdspcons_FlashColorMask	txtdspcons->FlashColorMask()
#define txtdspcons_BitMapPacked	txtdspcons->BitMapPacked()
#define txtdspcons_BitMapTeleText	txtdspcons->BitMapTeleText()
#define txtdspcons_BitMapChinese1	txtdspcons->BitMapChinese1()
#define txtdspcons_BitMapChinese2	txtdspcons->BitMapChinese2()
#define txtdspcons_BitMapChinese3	txtdspcons->BitMapChinese3()
#define txtdspcons_Periodic	txtdspcons->Periodic()
#define txtdspcons_OnlyPeriodic	txtdspcons->OnlyPeriodic()
#define txtdspcons_ScrollUp	txtdspcons->ScrollUp()
#define txtdspcons_ScrollDown	txtdspcons->ScrollDown()
#define txtdspcons_ScrollLeft	txtdspcons->ScrollLeft()
#define txtdspcons_ScrollRight	txtdspcons->ScrollRight()
#define txtdspcons_PageModeSingle	txtdspcons->PageModeSingle()
#define txtdspcons_PageModeSingle56	txtdspcons->PageModeSingle56()
#define txtdspcons_PageModeDouble	txtdspcons->PageModeDouble()
#define txtdspcons_WindowA	txtdspcons->WindowA()
#define txtdspcons_WindowB	txtdspcons->WindowB()
#define txtdspcons_ScrollIncrUp	txtdspcons->ScrollIncrUp()
#define txtdspcons_ScrollIncrDown	txtdspcons->ScrollIncrDown()
#define iacinv_MinRow	IHsvAciNavigation_MinRow
#define iacinv_MaxRow	IHsvAciNavigation_MaxRow
#define iacinv_NoRow	IHsvAciNavigation_NoRow
#define svpaci_pgcni_InvalidPreset	ISvcCniData_InvalidPreset
#define svpaci_pgcni_MinCNIPreset	i__svpaci_pgcni.m_MinCNIPreset
#define svpaci_pgcni_MaxCNIPreset	i__svpaci_pgcni.m_MaxCNIPreset
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_macids.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

