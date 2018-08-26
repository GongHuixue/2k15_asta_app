#ifndef IAPPAPITEXTDISPLAYCONSTANTS_H
#define IAPPAPITEXTDISPLAYCONSTANTS_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiTextDisplayConstants
{
public:
	virtual ~IAppApiTextDisplayConstants(){}
	virtual Nat32 ShadowLeft(void)= 0;
	virtual Nat32 ShadowTop(void)= 0;
	virtual Nat32 ShadowRight(void)= 0;
	virtual Nat32 ShadowBottom(void)= 0;
	virtual Nat32 ShadowAll(void)= 0;
	virtual Nat32 ShadowHeader(void)= 0;
	virtual Nat32 ShadowFlash(void)= 0;
	virtual Nat32 Rounded(void)= 0;
	virtual Nat32 Revealed(void)= 0;
	virtual Nat32 CharMode(void)= 0;
	virtual Nat32 GlobalDoubleHeight(void)= 0;
	virtual Nat32 GlobalDoubleWidth(void)= 0;
	virtual Nat32 StandardTextFont(void)= 0;
	virtual Nat32 FontDigitalCC(void)= 0;
	virtual Nat32 gNone(void)= 0;
	virtual Nat32 gRaised(void)= 0;
	virtual Nat32 gDepressed(void)= 0;
	virtual Nat32 gUniform(void)= 0;
	virtual Nat32 gDropShadowLeft(void)= 0;
	virtual Nat32 gDropShadowRight(void)= 0;
	virtual Nat32 FontField(void)= 0;
	virtual Nat32 ColorField(void)= 0;
	virtual Nat32 ControlField(void)= 0;
	virtual Nat32 FontSizeField(void)= 0;
	virtual Nat32 BorderStyleField(void)= 0;
	virtual Nat32 Translate(void)= 0;
	virtual Nat32 DHFromFont(void)= 0;
	virtual Nat32 Space(void)= 0;
	virtual Nat32 Conceal(void)= 0;
	virtual Nat32 Dheight(void)= 0;
	virtual Nat32 Dwidth(void)= 0;
	virtual Nat32 UnderLine(void)= 0;
	virtual Nat32 AdvanceChar(void)= 0;
	virtual Nat32 AdvancePixel(void)= 0;
	virtual Nat32 AdvanceDraw(void)= 0;
	virtual Nat32 Invert(void)= 0;
	virtual Nat32 RoundX(void)= 0;
	virtual Nat32 BackSpace(void)= 0;
	virtual Nat32 FlashFieldMask(void)= 0;
	virtual Nat32 FlashTypeMask(void)= 0;
	virtual Nat32 FlashTypeNone(void)= 0;
	virtual Nat32 FlashTypeNormal(void)= 0;
	virtual Nat32 FlashTypeInvert(void)= 0;
	virtual Nat32 FlashTypeFlashColor(void)= 0;
	virtual Nat32 FlashPhaseMask(void)= 0;
	virtual Nat32 FlashPhase1Hz(void)= 0;
	virtual Nat32 FlashPhase2HzPhase1(void)= 0;
	virtual Nat32 FlashPhase2HzPhase2(void)= 0;
	virtual Nat32 FlashPhase2HzPhase3(void)= 0;
	virtual Nat32 DheightTop(void)= 0;
	virtual Nat32 DheightBottom(void)= 0;
	virtual Nat32 SeparatedMosiac(void)= 0;
	virtual Nat32 Italics(void)= 0;
	virtual Nat32 None(void)= 0;
	virtual Nat32 Raised(void)= 0;
	virtual Nat32 Depressed(void)= 0;
	virtual Nat32 Uniform(void)= 0;
	virtual Nat32 DropShadowLeft(void)= 0;
	virtual Nat32 DropShadowRight(void)= 0;
	virtual Nat32 ForeGroundMask(void)= 0;
	virtual Nat32 BackGroundMask(void)= 0;
	virtual Nat32 FlashColorMask(void)= 0;
	virtual Nat8 BitMapPacked(void)= 0;
	virtual Nat8 BitMapTeleText(void)= 0;
	virtual Nat8 BitMapChinese1(void)= 0;
	virtual Nat8 BitMapChinese2(void)= 0;
	virtual Nat8 BitMapChinese3(void)= 0;
	virtual Nat32 Periodic(void)= 0;
	virtual Nat32 OnlyPeriodic(void)= 0;
	virtual Nat32 ScrollUp(void)= 0;
	virtual Nat32 ScrollDown(void)= 0;
	virtual Nat32 ScrollLeft(void)= 0;
	virtual Nat32 ScrollRight(void)= 0;
	virtual Nat8 PageModeSingle(void)= 0;
	virtual Nat8 PageModeSingle56(void)= 0;
	virtual Nat8 PageModeDouble(void)= 0;
	virtual Nat8 WindowA(void)= 0;
	virtual Nat8 WindowB(void)= 0;
	virtual Nat8 ScrollIncrUp(void)= 0;
	virtual Nat8 ScrollIncrDown(void)= 0;
};


#define IAppApiTextDisplayConstantsImpl(Comp,intf)    \
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat32>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
friend class InterfaceParam<Comp,Nat8>;\
class Comp ## _ ## intf : public IAppApiTextDisplayConstants \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,Nat32> m_ShadowLeft; \
    InterfaceParam<Comp,Nat32> m_ShadowTop; \
    InterfaceParam<Comp,Nat32> m_ShadowRight; \
    InterfaceParam<Comp,Nat32> m_ShadowBottom; \
    InterfaceParam<Comp,Nat32> m_ShadowAll; \
    InterfaceParam<Comp,Nat32> m_ShadowHeader; \
    InterfaceParam<Comp,Nat32> m_ShadowFlash; \
    InterfaceParam<Comp,Nat32> m_Rounded; \
    InterfaceParam<Comp,Nat32> m_Revealed; \
    InterfaceParam<Comp,Nat32> m_CharMode; \
    InterfaceParam<Comp,Nat32> m_GlobalDoubleHeight; \
    InterfaceParam<Comp,Nat32> m_GlobalDoubleWidth; \
    InterfaceParam<Comp,Nat32> m_StandardTextFont; \
    InterfaceParam<Comp,Nat32> m_FontDigitalCC; \
    InterfaceParam<Comp,Nat32> m_gNone; \
    InterfaceParam<Comp,Nat32> m_gRaised; \
    InterfaceParam<Comp,Nat32> m_gDepressed; \
    InterfaceParam<Comp,Nat32> m_gUniform; \
    InterfaceParam<Comp,Nat32> m_gDropShadowLeft; \
    InterfaceParam<Comp,Nat32> m_gDropShadowRight; \
    InterfaceParam<Comp,Nat32> m_FontField; \
    InterfaceParam<Comp,Nat32> m_ColorField; \
    InterfaceParam<Comp,Nat32> m_ControlField; \
    InterfaceParam<Comp,Nat32> m_FontSizeField; \
    InterfaceParam<Comp,Nat32> m_BorderStyleField; \
    InterfaceParam<Comp,Nat32> m_Translate; \
    InterfaceParam<Comp,Nat32> m_DHFromFont; \
    InterfaceParam<Comp,Nat32> m_Space; \
    InterfaceParam<Comp,Nat32> m_Conceal; \
    InterfaceParam<Comp,Nat32> m_Dheight; \
    InterfaceParam<Comp,Nat32> m_Dwidth; \
    InterfaceParam<Comp,Nat32> m_UnderLine; \
    InterfaceParam<Comp,Nat32> m_AdvanceChar; \
    InterfaceParam<Comp,Nat32> m_AdvancePixel; \
    InterfaceParam<Comp,Nat32> m_AdvanceDraw; \
    InterfaceParam<Comp,Nat32> m_Invert; \
    InterfaceParam<Comp,Nat32> m_RoundX; \
    InterfaceParam<Comp,Nat32> m_BackSpace; \
    InterfaceParam<Comp,Nat32> m_FlashFieldMask; \
    InterfaceParam<Comp,Nat32> m_FlashTypeMask; \
    InterfaceParam<Comp,Nat32> m_FlashTypeNone; \
    InterfaceParam<Comp,Nat32> m_FlashTypeNormal; \
    InterfaceParam<Comp,Nat32> m_FlashTypeInvert; \
    InterfaceParam<Comp,Nat32> m_FlashTypeFlashColor; \
    InterfaceParam<Comp,Nat32> m_FlashPhaseMask; \
    InterfaceParam<Comp,Nat32> m_FlashPhase1Hz; \
    InterfaceParam<Comp,Nat32> m_FlashPhase2HzPhase1; \
    InterfaceParam<Comp,Nat32> m_FlashPhase2HzPhase2; \
    InterfaceParam<Comp,Nat32> m_FlashPhase2HzPhase3; \
    InterfaceParam<Comp,Nat32> m_DheightTop; \
    InterfaceParam<Comp,Nat32> m_DheightBottom; \
    InterfaceParam<Comp,Nat32> m_SeparatedMosiac; \
    InterfaceParam<Comp,Nat32> m_Italics; \
    InterfaceParam<Comp,Nat32> m_None; \
    InterfaceParam<Comp,Nat32> m_Raised; \
    InterfaceParam<Comp,Nat32> m_Depressed; \
    InterfaceParam<Comp,Nat32> m_Uniform; \
    InterfaceParam<Comp,Nat32> m_DropShadowLeft; \
    InterfaceParam<Comp,Nat32> m_DropShadowRight; \
    InterfaceParam<Comp,Nat32> m_ForeGroundMask; \
    InterfaceParam<Comp,Nat32> m_BackGroundMask; \
    InterfaceParam<Comp,Nat32> m_FlashColorMask; \
    InterfaceParam<Comp,Nat8> m_BitMapPacked; \
    InterfaceParam<Comp,Nat8> m_BitMapTeleText; \
    InterfaceParam<Comp,Nat8> m_BitMapChinese1; \
    InterfaceParam<Comp,Nat8> m_BitMapChinese2; \
    InterfaceParam<Comp,Nat8> m_BitMapChinese3; \
    InterfaceParam<Comp,Nat32> m_Periodic; \
    InterfaceParam<Comp,Nat32> m_OnlyPeriodic; \
    InterfaceParam<Comp,Nat32> m_ScrollUp; \
    InterfaceParam<Comp,Nat32> m_ScrollDown; \
    InterfaceParam<Comp,Nat32> m_ScrollLeft; \
    InterfaceParam<Comp,Nat32> m_ScrollRight; \
    InterfaceParam<Comp,Nat8> m_PageModeSingle; \
    InterfaceParam<Comp,Nat8> m_PageModeSingle56; \
    InterfaceParam<Comp,Nat8> m_PageModeDouble; \
    InterfaceParam<Comp,Nat8> m_WindowA; \
    InterfaceParam<Comp,Nat8> m_WindowB; \
    InterfaceParam<Comp,Nat8> m_ScrollIncrUp; \
    InterfaceParam<Comp,Nat8> m_ScrollIncrDown; \
    Comp ## _ ## intf( Comp *parent):m_ShadowLeft(parent),m_ShadowTop(parent),m_ShadowRight(parent),m_ShadowBottom(parent),m_ShadowAll(parent),m_ShadowHeader(parent),m_ShadowFlash(parent),m_Rounded(parent),m_Revealed(parent),m_CharMode(parent),m_GlobalDoubleHeight(parent),m_GlobalDoubleWidth(parent),m_StandardTextFont(parent),m_FontDigitalCC(parent),m_gNone(parent),m_gRaised(parent),m_gDepressed(parent),m_gUniform(parent),m_gDropShadowLeft(parent),m_gDropShadowRight(parent),m_FontField(parent),m_ColorField(parent),m_ControlField(parent),m_FontSizeField(parent),m_BorderStyleField(parent),m_Translate(parent),m_DHFromFont(parent),m_Space(parent),m_Conceal(parent),m_Dheight(parent),m_Dwidth(parent),m_UnderLine(parent),m_AdvanceChar(parent),m_AdvancePixel(parent),m_AdvanceDraw(parent),m_Invert(parent),m_RoundX(parent),m_BackSpace(parent),m_FlashFieldMask(parent),m_FlashTypeMask(parent),m_FlashTypeNone(parent),m_FlashTypeNormal(parent),m_FlashTypeInvert(parent),m_FlashTypeFlashColor(parent),m_FlashPhaseMask(parent),m_FlashPhase1Hz(parent),m_FlashPhase2HzPhase1(parent),m_FlashPhase2HzPhase2(parent),m_FlashPhase2HzPhase3(parent),m_DheightTop(parent),m_DheightBottom(parent),m_SeparatedMosiac(parent),m_Italics(parent),m_None(parent),m_Raised(parent),m_Depressed(parent),m_Uniform(parent),m_DropShadowLeft(parent),m_DropShadowRight(parent),m_ForeGroundMask(parent),m_BackGroundMask(parent),m_FlashColorMask(parent),m_BitMapPacked(parent),m_BitMapTeleText(parent),m_BitMapChinese1(parent),m_BitMapChinese2(parent),m_BitMapChinese3(parent),m_Periodic(parent),m_OnlyPeriodic(parent),m_ScrollUp(parent),m_ScrollDown(parent),m_ScrollLeft(parent),m_ScrollRight(parent),m_PageModeSingle(parent),m_PageModeSingle56(parent),m_PageModeDouble(parent),m_WindowA(parent),m_WindowB(parent),m_ScrollIncrUp(parent),m_ScrollIncrDown(parent) \
    {\
        m_parent = parent;\
    }\
virtual Nat32 ShadowLeft(void){ return m_ShadowLeft.Call();}\
virtual Nat32 ShadowTop(void){ return m_ShadowTop.Call();}\
virtual Nat32 ShadowRight(void){ return m_ShadowRight.Call();}\
virtual Nat32 ShadowBottom(void){ return m_ShadowBottom.Call();}\
virtual Nat32 ShadowAll(void){ return m_ShadowAll.Call();}\
virtual Nat32 ShadowHeader(void){ return m_ShadowHeader.Call();}\
virtual Nat32 ShadowFlash(void){ return m_ShadowFlash.Call();}\
virtual Nat32 Rounded(void){ return m_Rounded.Call();}\
virtual Nat32 Revealed(void){ return m_Revealed.Call();}\
virtual Nat32 CharMode(void){ return m_CharMode.Call();}\
virtual Nat32 GlobalDoubleHeight(void){ return m_GlobalDoubleHeight.Call();}\
virtual Nat32 GlobalDoubleWidth(void){ return m_GlobalDoubleWidth.Call();}\
virtual Nat32 StandardTextFont(void){ return m_StandardTextFont.Call();}\
virtual Nat32 FontDigitalCC(void){ return m_FontDigitalCC.Call();}\
virtual Nat32 gNone(void){ return m_gNone.Call();}\
virtual Nat32 gRaised(void){ return m_gRaised.Call();}\
virtual Nat32 gDepressed(void){ return m_gDepressed.Call();}\
virtual Nat32 gUniform(void){ return m_gUniform.Call();}\
virtual Nat32 gDropShadowLeft(void){ return m_gDropShadowLeft.Call();}\
virtual Nat32 gDropShadowRight(void){ return m_gDropShadowRight.Call();}\
virtual Nat32 FontField(void){ return m_FontField.Call();}\
virtual Nat32 ColorField(void){ return m_ColorField.Call();}\
virtual Nat32 ControlField(void){ return m_ControlField.Call();}\
virtual Nat32 FontSizeField(void){ return m_FontSizeField.Call();}\
virtual Nat32 BorderStyleField(void){ return m_BorderStyleField.Call();}\
virtual Nat32 Translate(void){ return m_Translate.Call();}\
virtual Nat32 DHFromFont(void){ return m_DHFromFont.Call();}\
virtual Nat32 Space(void){ return m_Space.Call();}\
virtual Nat32 Conceal(void){ return m_Conceal.Call();}\
virtual Nat32 Dheight(void){ return m_Dheight.Call();}\
virtual Nat32 Dwidth(void){ return m_Dwidth.Call();}\
virtual Nat32 UnderLine(void){ return m_UnderLine.Call();}\
virtual Nat32 AdvanceChar(void){ return m_AdvanceChar.Call();}\
virtual Nat32 AdvancePixel(void){ return m_AdvancePixel.Call();}\
virtual Nat32 AdvanceDraw(void){ return m_AdvanceDraw.Call();}\
virtual Nat32 Invert(void){ return m_Invert.Call();}\
virtual Nat32 RoundX(void){ return m_RoundX.Call();}\
virtual Nat32 BackSpace(void){ return m_BackSpace.Call();}\
virtual Nat32 FlashFieldMask(void){ return m_FlashFieldMask.Call();}\
virtual Nat32 FlashTypeMask(void){ return m_FlashTypeMask.Call();}\
virtual Nat32 FlashTypeNone(void){ return m_FlashTypeNone.Call();}\
virtual Nat32 FlashTypeNormal(void){ return m_FlashTypeNormal.Call();}\
virtual Nat32 FlashTypeInvert(void){ return m_FlashTypeInvert.Call();}\
virtual Nat32 FlashTypeFlashColor(void){ return m_FlashTypeFlashColor.Call();}\
virtual Nat32 FlashPhaseMask(void){ return m_FlashPhaseMask.Call();}\
virtual Nat32 FlashPhase1Hz(void){ return m_FlashPhase1Hz.Call();}\
virtual Nat32 FlashPhase2HzPhase1(void){ return m_FlashPhase2HzPhase1.Call();}\
virtual Nat32 FlashPhase2HzPhase2(void){ return m_FlashPhase2HzPhase2.Call();}\
virtual Nat32 FlashPhase2HzPhase3(void){ return m_FlashPhase2HzPhase3.Call();}\
virtual Nat32 DheightTop(void){ return m_DheightTop.Call();}\
virtual Nat32 DheightBottom(void){ return m_DheightBottom.Call();}\
virtual Nat32 SeparatedMosiac(void){ return m_SeparatedMosiac.Call();}\
virtual Nat32 Italics(void){ return m_Italics.Call();}\
virtual Nat32 None(void){ return m_None.Call();}\
virtual Nat32 Raised(void){ return m_Raised.Call();}\
virtual Nat32 Depressed(void){ return m_Depressed.Call();}\
virtual Nat32 Uniform(void){ return m_Uniform.Call();}\
virtual Nat32 DropShadowLeft(void){ return m_DropShadowLeft.Call();}\
virtual Nat32 DropShadowRight(void){ return m_DropShadowRight.Call();}\
virtual Nat32 ForeGroundMask(void){ return m_ForeGroundMask.Call();}\
virtual Nat32 BackGroundMask(void){ return m_BackGroundMask.Call();}\
virtual Nat32 FlashColorMask(void){ return m_FlashColorMask.Call();}\
virtual Nat8 BitMapPacked(void){ return m_BitMapPacked.Call();}\
virtual Nat8 BitMapTeleText(void){ return m_BitMapTeleText.Call();}\
virtual Nat8 BitMapChinese1(void){ return m_BitMapChinese1.Call();}\
virtual Nat8 BitMapChinese2(void){ return m_BitMapChinese2.Call();}\
virtual Nat8 BitMapChinese3(void){ return m_BitMapChinese3.Call();}\
virtual Nat32 Periodic(void){ return m_Periodic.Call();}\
virtual Nat32 OnlyPeriodic(void){ return m_OnlyPeriodic.Call();}\
virtual Nat32 ScrollUp(void){ return m_ScrollUp.Call();}\
virtual Nat32 ScrollDown(void){ return m_ScrollDown.Call();}\
virtual Nat32 ScrollLeft(void){ return m_ScrollLeft.Call();}\
virtual Nat32 ScrollRight(void){ return m_ScrollRight.Call();}\
virtual Nat8 PageModeSingle(void){ return m_PageModeSingle.Call();}\
virtual Nat8 PageModeSingle56(void){ return m_PageModeSingle56.Call();}\
virtual Nat8 PageModeDouble(void){ return m_PageModeDouble.Call();}\
virtual Nat8 WindowA(void){ return m_WindowA.Call();}\
virtual Nat8 WindowB(void){ return m_WindowB.Call();}\
virtual Nat8 ScrollIncrUp(void){ return m_ScrollIncrUp.Call();}\
virtual Nat8 ScrollIncrDown(void){ return m_ScrollIncrDown.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
