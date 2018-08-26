#ifndef  _CHSVACIDECODE_PRIV_H
#define  _CHSVACIDECODE_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvAciDecode.h>
#include <IHsvTxtPageConvertNotify.h>
#include <IHsvPower.h>
#include <IHsvTxtPageAccess.h>
#include <IHsvAciDecodeNotify.h>
#include <IHsvAciNavigation.h>
#include <IHsvTxtPageConvert.h>
#include <ITvColorDecode2.h>
#include <IHsvTxtDecode.h>
#include <IHsvAciDecodeDiv.h>
#include <IHsvTxtDisplayDriver.h>
#include <IEnable.h>
#include <IHsvEuropeConfiguration.h>
#include <IPumpEngine.h>
#include <IHsvTxtPacket0.h>
#include <IPumpExSub.h>
#include <IHsvTxtPageRequest.h>
#include <IString.h>
#include <CTCMwBase.h>
class CHsvAciDecode_Priv;
#define CLASSSCOPE CHsvAciDecode_Priv::
#include "locals_m.h"

class CHsvAciDecode_Priv : public CTCMwBase
{
public:
virtual ~CHsvAciDecode_Priv();
void PageReceivedHandler(int tag, PageNr page,Subcode subcode,Bool arvd_drop,Nat16 ctrlbits);

private:
void params__init(void);
public:
#define MEMBERVARS
#include "locals_m.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvAciDecodeImpl(CHsvAciDecode_Priv,acidec);
IHsvTxtPageConvertNotifyImpl(CHsvAciDecode_Priv,cnvN);
IHsvPowerImpl(CHsvAciDecode_Priv,pow);
public:
ProvidesInterface<IHsvAciDecode>	acidec;

ProvidesInterface<IHsvTxtPageConvertNotify>	cnvN;

ProvidesInterface<IHsvPower>	pow;

//Required interfaces
public:
RequiresInterface<IHsvTxtPageAccess>	acc;
RequiresInterface<IHsvAciDecodeNotify>	acidecN;
RequiresInterface<IHsvAciNavigation>	acinv;
RequiresInterface<IHsvTxtPageConvert>	cnv;
RequiresInterface<ITvColorDecode2>	col;
RequiresInterface<IHsvTxtDecode>	dec;
RequiresInterface<IHsvAciDecodeDiv>	div;
RequiresInterface<IHsvTxtDisplayDriver>	dsdrv;
RequiresInterface<IEnable>	dsenb;
RequiresInterface<IHsvEuropeConfiguration>	euconfig;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvTxtPacket0>	pkt0;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvTxtPageRequest>	req;
RequiresInterface<IString>	str;

void Setacipagehandle( CHsvAciDecode_Priv* acipagehandle);
//void PageReceivedHandler(int tag, PageNr page,Subcode subcode,Bool arvd_drop,Nat16 ctrlbits);

private:
Pumpdefines(CHsvAciDecode_Priv);

public:
CHsvAciDecode_Priv():i__acidec(this),i__cnvN(this),i__pow(this)
{
acidec	=	&i__acidec;
cnvN	=	&i__cnvN;
pow	=	&i__pow;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define acc_iPresent() (acc.Present())
#define acc_OpenPageForRead(page,subcode)	acc->OpenPageForRead(page,subcode)
#define acc_ClosePage(hnd)	acc->ClosePage(hnd)
#define acc_GetPacket(hnd,pkt_num)	acc->GetPacket(hnd,pkt_num)
#define acidecN_iPresent() (acidecN.Present())
#define acidecN_OnReceivedPage()	acidecN->OnReceivedPage()
#define acidecN_OnHeaderDecoded()	acidecN->OnHeaderDecoded()
#define acidecN_OnDecodeSuccessful()	acidecN->OnDecodeSuccessful()
#define acidecN_OnDecodeFailure()	acidecN->OnDecodeFailure()
#define acinv_iPresent() (acinv.Present())
#define acinv_MinRow	IHsvAciNavigation_MinRow
#define acinv_MaxRow	IHsvAciNavigation_MaxRow
#define acinv_NoRow	IHsvAciNavigation_NoRow
#define acinv_SetCursor(row)	acinv->SetCursor(row)
#define acinv_GetCursor()	acinv->GetCursor()
#define cnv_iPresent() (cnv.Present())
#define cnv_ConfInit(pcs)	cnv->ConfInit(pcs)
#define cnv_SetConfWindowId(pcs,window_id)	cnv->SetConfWindowId(pcs,window_id)
#define cnv_GetConfWindowId(pcs)	cnv->GetConfWindowId(pcs)
#define cnv_SetConfPageHandle(pcs,hnd)	cnv->SetConfPageHandle(pcs,hnd)
#define cnv_GetConfPageHandle(pcs)	cnv->GetConfPageHandle(pcs)
#define cnv_SetConfPresentation(pcs,presentation)	cnv->SetConfPresentation(pcs,presentation)
#define cnv_GetConfPresentation(pcs)	cnv->GetConfPresentation(pcs)
#define cnv_SetConfSupRow24(pcs,sup_row_24)	cnv->SetConfSupRow24(pcs,sup_row_24)
#define cnv_GetConfSupRow24(pcs)	cnv->GetConfSupRow24(pcs)
#define cnv_SetConfSupHeader(pcs,sup_header)	cnv->SetConfSupHeader(pcs,sup_header)
#define cnv_GetConfSupHeader(pcs)	cnv->GetConfSupHeader(pcs)
#define cnv_SetConfSupPicture(pcs,sup_picture)	cnv->SetConfSupPicture(pcs,sup_picture)
#define cnv_GetConfSupPicture(pcs)	cnv->GetConfSupPicture(pcs)
#define cnv_SetConfSupSidePanels(pcs,sup_side_pan)	cnv->SetConfSupSidePanels(pcs,sup_side_pan)
#define cnv_GetConfSupSidePanels(pcs)	cnv->GetConfSupSidePanels(pcs)
#define cnv_SetConfSupRowAttribs(pcs,sup_row_attribs)	cnv->SetConfSupRowAttribs(pcs,sup_row_attribs)
#define cnv_GetConfSupRowAttribs(pcs)	cnv->GetConfSupRowAttribs(pcs)
#define cnv_ConfigureTextPageConversion(pcs)	cnv->ConfigureTextPageConversion(pcs)
#define cnv_StartTextPageConversion(x)	cnv->StartTextPageConversion(x)
#define cnv_TerminateTextPageConversion()	cnv->TerminateTextPageConversion()
#define cnv_SetRevealState(rev_state)	cnv->SetRevealState(rev_state)
#define cnv_GetRevealState()	cnv->GetRevealState()
#define cnv_GetPageWidthOffset(hnd,width,offset)	cnv->GetPageWidthOffset(hnd,width,offset)
#define cnv_GetPagePon()	cnv->GetPagePon()
#define cnv_SetRollingHeader(mode,magazine)	cnv->SetRollingHeader(mode,magazine)
#define cnv_SetRollingTime(mode)	cnv->SetRollingTime(mode)
#define cnv_SetHeaderInitialPosition(topleftrow,topleftcol)	cnv->SetHeaderInitialPosition(topleftrow,topleftcol)
#define cnv_HoldConversion(convhold_state)	cnv->HoldConversion(convhold_state)
#define cnv_ResetUpdateCounter()	cnv->ResetUpdateCounter()
#define cnv_IncrementUpdateCounter()	cnv->IncrementUpdateCounter()
#define cnv_LEVEL_10	IHsvTxtPageConvert_LEVEL_10
#define cnv_LEVEL_15	IHsvTxtPageConvert_LEVEL_15
#define cnv_LEVEL_25	IHsvTxtPageConvert_LEVEL_25
#define cnv_TRH_HOLD	IHsvTxtPageConvert_TRH_HOLD
#define cnv_TRH_ROL	IHsvTxtPageConvert_TRH_ROL
#define cnv_TRT_HOLD	IHsvTxtPageConvert_TRT_HOLD
#define cnv_TRT_ROL	IHsvTxtPageConvert_TRT_ROL
#define col_iPresent() (col.Present())
#define col_ColorSystemSupported(colorsystem)	col->ColorSystemSupported(colorsystem)
#define col_ColorSystemSupportedEx(colorsystem,carrierfrequency)	col->ColorSystemSupportedEx(colorsystem,carrierfrequency)
#define col_ForceColorSystem(colorsystem)	col->ForceColorSystem(colorsystem)
#define col_ForceColorSystemEx(colorsystem,carrierfrequency)	col->ForceColorSystemEx(colorsystem,carrierfrequency)
#define col_GetForcedColorSystem()	col->GetForcedColorSystem()
#define col_GetForcedCarrierFrequency()	col->GetForcedCarrierFrequency()
#define col_SuggestColorSystem(colorsystem)	col->SuggestColorSystem(colorsystem)
#define col_SuggestColorSystemEx(colorsystem,carrierfrequency)	col->SuggestColorSystemEx(colorsystem,carrierfrequency)
#define col_GetSuggestedColorSystem()	col->GetSuggestedColorSystem()
#define col_GetSuggestedCarrierFrequency()	col->GetSuggestedCarrierFrequency()
#define col_GetColorSystem()	col->GetColorSystem()
#define col_GetCarrierFrequency()	col->GetCarrierFrequency()
#define col_CombFilterSupported()	col->CombFilterSupported()
#define col_EnableCombFilter(mode)	col->EnableCombFilter(mode)
#define col_CombFilterEnabled()	col->CombFilterEnabled()
#define col_CombFilterActive()	col->CombFilterActive()
#define col_UnknownColorSystem	col->UnknownColorSystem()
#define col_InvalidColorSystem	col->InvalidColorSystem()
#define col_Pal	col->Pal()
#define col_Secam	col->Secam()
#define col_Ntsc	col->Ntsc()
#define col_FreqUnknown	col->FreqUnknown()
#define col_FreqInvalid	col->FreqInvalid()
#define col_Freq4pt433619	col->Freq4pt433619()
#define col_Freq3pt582056	col->Freq3pt582056()
#define col_Freq3pt575611	col->Freq3pt575611()
#define col_Freq3pt579545	col->Freq3pt579545()
#define dec_iPresent() (dec.Present())
#define dec_DecodeOddParity(src,dst,old,size)	dec->DecodeOddParity(src,dst,old,size)
#define div_iPresent() (div.Present())
#define div_PrefetchAciPage	div->PrefetchAciPage()
#define div_PresetNameLength	div->PresetNameLength()
#define div_AciDispStartRow	div->AciDispStartRow()
#define div_AciDispStartCol	div->AciDispStartCol()
#define div_AciDispEndRow	div->AciDispEndRow()
#define div_AciDispEndCol	div->AciDispEndCol()
#define div_AciRowHeight	div->AciRowHeight()
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
#define dsenb_iPresent() (dsenb.Present())
#define dsenb_Enable()	dsenb->Enable()
#define dsenb_Disable()	dsenb->Disable()
#define euconfig_iPresent() (euconfig.Present())
#define euconfig_AutoStoreModeNone	IHsvEuropeConfiguration_AutoStoreModeNone
#define euconfig_AutoStoreModeVpsPdc	IHsvEuropeConfiguration_AutoStoreModeVpsPdc
#define euconfig_AutoStoreModeAci	IHsvEuropeConfiguration_AutoStoreModeAci
#define euconfig_AutoStoreModeVpsPdcAci	IHsvEuropeConfiguration_AutoStoreModeVpsPdcAci
#define euconfig_GetAutoStoreMode()	euconfig->GetAutoStoreMode()
#define euconfig_GetMedium()	euconfig->GetMedium()
#define euconfig_GetBreakOutSource(Source)	euconfig->GetBreakOutSource(Source)
#define euconfig_GetBreakOutChannel(ChannelNo)	euconfig->GetBreakOutChannel(ChannelNo)
#define euconfig_GetDefaultSpdifAssociation(SpdifSource)	euconfig->GetDefaultSpdifAssociation(SpdifSource)
#define euconfig_InstallationCookie	euconfig->InstallationCookie()
#define pen_iPresent() (pen.Present())
#define pen_PumpEngine	pen->PumpEngine()
#define pkt0_iPresent() (pkt0.Present())
#define pkt0_GetLatestHeader(pkt0ptr,mag)	pkt0->GetLatestHeader(pkt0ptr,mag)
#define pkt0_GetLatestTime(time_ptr)	pkt0->GetLatestTime(time_ptr)
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvAciDecode_Priv::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)
#define req_iPresent() (req.Present())
#define req_RequestPage(page,subcode,fnc,tag)	req->RequestPage(page,subcode,fnc,tag)
#define req_UnRequestPage(page,subcode,fnc)	req->UnRequestPage(page,subcode,fnc)
#define req_SuggestPage(page)	req->SuggestPage(page)
#define req_UnSuggestPage(page)	req->UnSuggestPage(page)
#define req_SetType(page,ptype,priority,func)	req->SetType(page,ptype,priority,func)
#define str_iPresent() (str.Present())
#define str_strcmp(str1,str2)	str->strcmp(str1,str2)
#define str_strcmpRom(str1,str2)	str->strcmpRom(str1,str2)
#define str_strncmp(str1,str2,num)	str->strncmp(str1,str2,num)
#define str_strncmpRom(str1,str2,num)	str->strncmpRom(str1,str2,num)
#define str_strlen(str1)	str->strlen(str1)
#define str_strlenRom(str1)	str->strlenRom(str1)
#define str_strcpy(dest,source)	str->strcpy(dest,source)
#define str_strcpyRom(dest,source)	str->strcpyRom(dest,source)
#define str_strncpy(dest,source,num)	str->strncpy(dest,source,num)
#define str_strncpyRom(dest,source,num)	str->strncpyRom(dest,source,num)
#define str_strcat(dest,source)	str->strcat(dest,source)
#define str_strcatRom(dest,source)	str->strcatRom(dest,source)
#define str_strncat(dest,source,num)	str->strncat(dest,source,num)
#define str_strstr(book,word)	str->strstr(book,word)
#define str_strchr(book,letter)	str->strchr(book,letter)
#define acidec_ConstAciPage	IHsvAciDecode_ConstAciPage
#define acidec_StateIdle	IHsvAciDecode_StateIdle
#define acidec_StateDecoding	IHsvAciDecode_StateDecoding
#define acidec_StateSuccess	IHsvAciDecode_StateSuccess
#define acidec_StateFail	IHsvAciDecode_StateFail
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
#include "locals_m.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

