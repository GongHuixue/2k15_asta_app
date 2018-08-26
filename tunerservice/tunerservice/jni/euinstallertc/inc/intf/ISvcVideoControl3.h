#ifndef ISVCVIDEOCONTROL3_H
#define ISVCVIDEOCONTROL3_H
#include <intfparam.h>
#include <provreq.h>
class ISvcVideoControl3
{
public:
	virtual ~ISvcVideoControl3(){}
	virtual void Set(int property,int value)= 0;
	virtual int Get(int property)= 0;
	virtual void Set2(int property,int value1,int value2)= 0;
	virtual void Set3(int property,int value1,int value2)= 0;
	virtual Bool IsAvailable(int property,int value)= 0;
	virtual Bool IsControllable(int property,int value)= 0;
	virtual int Freeze(void)= 0;
	virtual int Pan(void)= 0;
	virtual int ViewMode(void)= 0;
	virtual int SeamlessViewMode(void)= 0;
	virtual int PicturePos(void)= 0;
	virtual int PicturePosHoriz(void)= 0;
	virtual int VideoCoding(void)= 0;
	virtual int VideoCodingAux(void)= 0;
	virtual int ImageFormat(void)= 0;
	virtual int AutoFormat(void)= 0;
	#define ISvcVideoControl3_VideoMute		((int)0 )
	virtual int VideoMuteAux(void)= 0;
	virtual int VideoMuteScart2Out(void)= 0;
	virtual int VideoPresenceMain(void)= 0;
	virtual int VideoPresenceAux(void)= 0;
	virtual int IncomingFrameLinesMain(void)= 0;
	virtual int IncomingVisibleFieldLinesMain(void)= 0;
	virtual int IncomingSignalInterlaceMain(void)= 0;
	virtual int IncomingFieldFrequencyMain(void)= 0;
	virtual int IncomingVisiblePixels(void)= 0;
	virtual int IncomingVisiblePixelsAux(void)= 0;
	virtual int IncomingFrameLinesAux(void)= 0;
	virtual int IncomingVisibleFieldLinesAux(void)= 0;
	virtual int IncomingSignalInterlaceAux(void)= 0;
	virtual int IncomingFieldFrequencyAux(void)= 0;
	virtual int AutoVideoMute(void)= 0;
	virtual int AbsPicPosVertical(void)= 0;
	virtual int AbsPicPosHoriz(void)= 0;
	virtual int VideoProtection(void)= 0;
	virtual int LastItem(void)= 0;
	virtual int FreezeOn(void)= 0;
	virtual int FreezeOff(void)= 0;
	virtual int PanUp(void)= 0;
	virtual int PanDown(void)= 0;
	virtual int PanLeft(void)= 0;
	virtual int PanRight(void)= 0;
	virtual int VmNormalScreen4by3(void)= 0;
	virtual int VmMovieExpand14by9(void)= 0;
	virtual int VmMovieExpand16by9(void)= 0;
	virtual int VmSubtitleZoom(void)= 0;
	virtual int VmSuperZoomMode(void)= 0;
	virtual int VmWideScreen(void)= 0;
	virtual int VmMovieExpand21by9(void)= 0;
	virtual int VmNormalScreen(void)= 0;
	virtual int VmVerticalSqueeze(void)= 0;
	virtual int VmExpand4by3(void)= 0;
	virtual int VmPanorama(void)= 0;
	virtual int VmHalfWindow(void)= 0;
	virtual int VmHalfWindowSqueezed(void)= 0;
	virtual int VmHorizontalSqueeze(void)= 0;
	virtual int VmOtherViewMode(void)= 0;
	virtual int VmAmoranap(void)= 0;
	virtual int VmZoomMode(void)= 0;
	virtual int VmHorizontalExpand(void)= 0;
	virtual int VmPseudoPipWindow(void)= 0;
	virtual int VmPreviewWindow(void)= 0;
	virtual int VmNativeMode(void)= 0;
	virtual int VmHighRes(void)= 0;
	virtual int VmUltraWide(void)= 0;
	virtual int VmUltraWideSubtitle(void)= 0;
	virtual int VmUltraWide16by9(void)= 0;
	virtual int VmVideoWindow(void)= 0;
	virtual int VmUltraWideSuperZoomME16by9(void)= 0;
	virtual int VmAutofill(void)= 0;
	virtual int VmAutozoom(void)= 0;
	virtual int AutoFormatMode(void)= 0;
	virtual int PicturePosMin(void)= 0;
	virtual int PicturePosMax(void)= 0;
	virtual int PicturePosHorizMin(void)= 0;
	virtual int PicturePosHorizMax(void)= 0;
	virtual int VcCvbs(void)= 0;
	virtual int VcYc(void)= 0;
	virtual int VcYuv(void)= 0;
	virtual int VcRgb(void)= 0;
	virtual int VcYPbPr(void)= 0;
	virtual int VcYcOrCvbs(void)= 0;
	virtual int VcRgb2Fh(void)= 0;
	virtual int VcYPbPr2Fh(void)= 0;
	virtual int VcYuv2Fh(void)= 0;
	virtual int VcRgb3Fh(void)= 0;
	virtual int VcYPbPr3Fh(void)= 0;
	virtual int VcYuv3Fh(void)= 0;
	#define ISvcVideoControl3_VcVga		((int)0 )
	#define ISvcVideoControl3_VcXvga		((int)0 )
	#define ISvcVideoControl3_VcSvga		((int)0 )
	#define ISvcVideoControl3_VcWxvga		((int)0 )
	virtual int ImageFormatInvalid(void)= 0;
	virtual int ImageFormatUnknown(void)= 0;
	virtual int ImageFormatNoImage(void)= 0;
	virtual int ImageFormat4by3FF(void)= 0;
	virtual int ImageFormat14by9Top(void)= 0;
	virtual int ImageFormat14by9Center(void)= 0;
	virtual int ImageFormat16by9Top(void)= 0;
	virtual int ImageFormat16by9Center(void)= 0;
	virtual int ImageFormat4by3Use14by9(void)= 0;
	virtual int ImageFormat16by9FF(void)= 0;
	virtual int ImageFormatMoreThan16by9Center(void)= 0;
	virtual int ImageFormat16by9Use14by9(void)= 0;
	virtual int ImageFormat16by9Use4by3(void)= 0;
	virtual int VideoPresentInvalid(void)= 0;
	virtual int VideoPresentUnknown(void)= 0;
	virtual int VideoPresent(void)= 0;
	virtual int VideoLost(void)= 0;
	virtual int VideoMuteBlack(void)= 0;
	virtual int VideoMuteBlue(void)= 0;
	virtual int VideoMuteGrey(void)= 0;
	virtual int VideoMuteWhite(void)= 0;
	#define ISvcVideoControl3_VideoMutePogramBlack		((int)0 )
	virtual int VideoMutePogramGrey(void)= 0;
	virtual int VideoMuteColourMin(void)= 0;
	virtual int VideoMuteColourMax(void)= 0;
	virtual int SigInterlace(void)= 0;
	virtual int SigProgressive(void)= 0;
	virtual int SigInterlaceInvalid(void)= 0;
	virtual int SigInterlaceUnknown(void)= 0;
	virtual int SigInterlaceOneOne(void)= 0;
	virtual int SigInterlaceTwoOne(void)= 0;
	virtual int SigInterlaceFourTwo(void)= 0;
	virtual int AbsPicPosVerticalMin(void)= 0;
	virtual int AbsPicPosVerticalMax(void)= 0;
	virtual int AbsPicPosHorizMin(void)= 0;
	virtual int AbsPicPosHorizMax(void)= 0;
	virtual int UnKnown(void)= 0;
	virtual int IgnoreValue(void)= 0;
	virtual int ResetValue(void)= 0;
	#define ISvcVideoControl3_VideoPropertyMaxValue		((int)100 )
};


#define ISvcVideoControl3Impl(Comp,intf)    \
virtual void intf ## _Set(int property,int value);\
virtual int intf ## _Get(int property);\
virtual void intf ## _Set2(int property,int value1,int value2);\
virtual void intf ## _Set3(int property,int value1,int value2);\
virtual Bool intf ## _IsAvailable(int property,int value);\
virtual Bool intf ## _IsControllable(int property,int value);\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public ISvcVideoControl3 \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_Freeze; \
    InterfaceParam<Comp,int> m_Pan; \
    InterfaceParam<Comp,int> m_ViewMode; \
    InterfaceParam<Comp,int> m_SeamlessViewMode; \
    InterfaceParam<Comp,int> m_PicturePos; \
    InterfaceParam<Comp,int> m_PicturePosHoriz; \
    InterfaceParam<Comp,int> m_VideoCoding; \
    InterfaceParam<Comp,int> m_VideoCodingAux; \
    InterfaceParam<Comp,int> m_ImageFormat; \
    InterfaceParam<Comp,int> m_AutoFormat; \
    InterfaceParam<Comp,int> m_VideoMuteAux; \
    InterfaceParam<Comp,int> m_VideoMuteScart2Out; \
    InterfaceParam<Comp,int> m_VideoPresenceMain; \
    InterfaceParam<Comp,int> m_VideoPresenceAux; \
    InterfaceParam<Comp,int> m_IncomingFrameLinesMain; \
    InterfaceParam<Comp,int> m_IncomingVisibleFieldLinesMain; \
    InterfaceParam<Comp,int> m_IncomingSignalInterlaceMain; \
    InterfaceParam<Comp,int> m_IncomingFieldFrequencyMain; \
    InterfaceParam<Comp,int> m_IncomingVisiblePixels; \
    InterfaceParam<Comp,int> m_IncomingVisiblePixelsAux; \
    InterfaceParam<Comp,int> m_IncomingFrameLinesAux; \
    InterfaceParam<Comp,int> m_IncomingVisibleFieldLinesAux; \
    InterfaceParam<Comp,int> m_IncomingSignalInterlaceAux; \
    InterfaceParam<Comp,int> m_IncomingFieldFrequencyAux; \
    InterfaceParam<Comp,int> m_AutoVideoMute; \
    InterfaceParam<Comp,int> m_AbsPicPosVertical; \
    InterfaceParam<Comp,int> m_AbsPicPosHoriz; \
    InterfaceParam<Comp,int> m_VideoProtection; \
    InterfaceParam<Comp,int> m_LastItem; \
    InterfaceParam<Comp,int> m_FreezeOn; \
    InterfaceParam<Comp,int> m_FreezeOff; \
    InterfaceParam<Comp,int> m_PanUp; \
    InterfaceParam<Comp,int> m_PanDown; \
    InterfaceParam<Comp,int> m_PanLeft; \
    InterfaceParam<Comp,int> m_PanRight; \
    InterfaceParam<Comp,int> m_VmNormalScreen4by3; \
    InterfaceParam<Comp,int> m_VmMovieExpand14by9; \
    InterfaceParam<Comp,int> m_VmMovieExpand16by9; \
    InterfaceParam<Comp,int> m_VmSubtitleZoom; \
    InterfaceParam<Comp,int> m_VmSuperZoomMode; \
    InterfaceParam<Comp,int> m_VmWideScreen; \
    InterfaceParam<Comp,int> m_VmMovieExpand21by9; \
    InterfaceParam<Comp,int> m_VmNormalScreen; \
    InterfaceParam<Comp,int> m_VmVerticalSqueeze; \
    InterfaceParam<Comp,int> m_VmExpand4by3; \
    InterfaceParam<Comp,int> m_VmPanorama; \
    InterfaceParam<Comp,int> m_VmHalfWindow; \
    InterfaceParam<Comp,int> m_VmHalfWindowSqueezed; \
    InterfaceParam<Comp,int> m_VmHorizontalSqueeze; \
    InterfaceParam<Comp,int> m_VmOtherViewMode; \
    InterfaceParam<Comp,int> m_VmAmoranap; \
    InterfaceParam<Comp,int> m_VmZoomMode; \
    InterfaceParam<Comp,int> m_VmHorizontalExpand; \
    InterfaceParam<Comp,int> m_VmPseudoPipWindow; \
    InterfaceParam<Comp,int> m_VmPreviewWindow; \
    InterfaceParam<Comp,int> m_VmNativeMode; \
    InterfaceParam<Comp,int> m_VmHighRes; \
    InterfaceParam<Comp,int> m_VmUltraWide; \
    InterfaceParam<Comp,int> m_VmUltraWideSubtitle; \
    InterfaceParam<Comp,int> m_VmUltraWide16by9; \
    InterfaceParam<Comp,int> m_VmVideoWindow; \
    InterfaceParam<Comp,int> m_VmUltraWideSuperZoomME16by9; \
    InterfaceParam<Comp,int> m_VmAutofill; \
    InterfaceParam<Comp,int> m_VmAutozoom; \
    InterfaceParam<Comp,int> m_AutoFormatMode; \
    InterfaceParam<Comp,int> m_PicturePosMin; \
    InterfaceParam<Comp,int> m_PicturePosMax; \
    InterfaceParam<Comp,int> m_PicturePosHorizMin; \
    InterfaceParam<Comp,int> m_PicturePosHorizMax; \
    InterfaceParam<Comp,int> m_VcCvbs; \
    InterfaceParam<Comp,int> m_VcYc; \
    InterfaceParam<Comp,int> m_VcYuv; \
    InterfaceParam<Comp,int> m_VcRgb; \
    InterfaceParam<Comp,int> m_VcYPbPr; \
    InterfaceParam<Comp,int> m_VcYcOrCvbs; \
    InterfaceParam<Comp,int> m_VcRgb2Fh; \
    InterfaceParam<Comp,int> m_VcYPbPr2Fh; \
    InterfaceParam<Comp,int> m_VcYuv2Fh; \
    InterfaceParam<Comp,int> m_VcRgb3Fh; \
    InterfaceParam<Comp,int> m_VcYPbPr3Fh; \
    InterfaceParam<Comp,int> m_VcYuv3Fh; \
    InterfaceParam<Comp,int> m_ImageFormatInvalid; \
    InterfaceParam<Comp,int> m_ImageFormatUnknown; \
    InterfaceParam<Comp,int> m_ImageFormatNoImage; \
    InterfaceParam<Comp,int> m_ImageFormat4by3FF; \
    InterfaceParam<Comp,int> m_ImageFormat14by9Top; \
    InterfaceParam<Comp,int> m_ImageFormat14by9Center; \
    InterfaceParam<Comp,int> m_ImageFormat16by9Top; \
    InterfaceParam<Comp,int> m_ImageFormat16by9Center; \
    InterfaceParam<Comp,int> m_ImageFormat4by3Use14by9; \
    InterfaceParam<Comp,int> m_ImageFormat16by9FF; \
    InterfaceParam<Comp,int> m_ImageFormatMoreThan16by9Center; \
    InterfaceParam<Comp,int> m_ImageFormat16by9Use14by9; \
    InterfaceParam<Comp,int> m_ImageFormat16by9Use4by3; \
    InterfaceParam<Comp,int> m_VideoPresentInvalid; \
    InterfaceParam<Comp,int> m_VideoPresentUnknown; \
    InterfaceParam<Comp,int> m_VideoPresent; \
    InterfaceParam<Comp,int> m_VideoLost; \
    InterfaceParam<Comp,int> m_VideoMuteBlack; \
    InterfaceParam<Comp,int> m_VideoMuteBlue; \
    InterfaceParam<Comp,int> m_VideoMuteGrey; \
    InterfaceParam<Comp,int> m_VideoMuteWhite; \
    InterfaceParam<Comp,int> m_VideoMutePogramGrey; \
    InterfaceParam<Comp,int> m_VideoMuteColourMin; \
    InterfaceParam<Comp,int> m_VideoMuteColourMax; \
    InterfaceParam<Comp,int> m_SigInterlace; \
    InterfaceParam<Comp,int> m_SigProgressive; \
    InterfaceParam<Comp,int> m_SigInterlaceInvalid; \
    InterfaceParam<Comp,int> m_SigInterlaceUnknown; \
    InterfaceParam<Comp,int> m_SigInterlaceOneOne; \
    InterfaceParam<Comp,int> m_SigInterlaceTwoOne; \
    InterfaceParam<Comp,int> m_SigInterlaceFourTwo; \
    InterfaceParam<Comp,int> m_AbsPicPosVerticalMin; \
    InterfaceParam<Comp,int> m_AbsPicPosVerticalMax; \
    InterfaceParam<Comp,int> m_AbsPicPosHorizMin; \
    InterfaceParam<Comp,int> m_AbsPicPosHorizMax; \
    InterfaceParam<Comp,int> m_UnKnown; \
    InterfaceParam<Comp,int> m_IgnoreValue; \
    InterfaceParam<Comp,int> m_ResetValue; \
    Comp ## _ ## intf( Comp *parent):m_Freeze(parent),m_Pan(parent),m_ViewMode(parent),m_SeamlessViewMode(parent),m_PicturePos(parent),m_PicturePosHoriz(parent),m_VideoCoding(parent),m_VideoCodingAux(parent),m_ImageFormat(parent),m_AutoFormat(parent),m_VideoMuteAux(parent),m_VideoMuteScart2Out(parent),m_VideoPresenceMain(parent),m_VideoPresenceAux(parent),m_IncomingFrameLinesMain(parent),m_IncomingVisibleFieldLinesMain(parent),m_IncomingSignalInterlaceMain(parent),m_IncomingFieldFrequencyMain(parent),m_IncomingVisiblePixels(parent),m_IncomingVisiblePixelsAux(parent),m_IncomingFrameLinesAux(parent),m_IncomingVisibleFieldLinesAux(parent),m_IncomingSignalInterlaceAux(parent),m_IncomingFieldFrequencyAux(parent),m_AutoVideoMute(parent),m_AbsPicPosVertical(parent),m_AbsPicPosHoriz(parent),m_VideoProtection(parent),m_LastItem(parent),m_FreezeOn(parent),m_FreezeOff(parent),m_PanUp(parent),m_PanDown(parent),m_PanLeft(parent),m_PanRight(parent),m_VmNormalScreen4by3(parent),m_VmMovieExpand14by9(parent),m_VmMovieExpand16by9(parent),m_VmSubtitleZoom(parent),m_VmSuperZoomMode(parent),m_VmWideScreen(parent),m_VmMovieExpand21by9(parent),m_VmNormalScreen(parent),m_VmVerticalSqueeze(parent),m_VmExpand4by3(parent),m_VmPanorama(parent),m_VmHalfWindow(parent),m_VmHalfWindowSqueezed(parent),m_VmHorizontalSqueeze(parent),m_VmOtherViewMode(parent),m_VmAmoranap(parent),m_VmZoomMode(parent),m_VmHorizontalExpand(parent),m_VmPseudoPipWindow(parent),m_VmPreviewWindow(parent),m_VmNativeMode(parent),m_VmHighRes(parent),m_VmUltraWide(parent),m_VmUltraWideSubtitle(parent),m_VmUltraWide16by9(parent),m_VmVideoWindow(parent),m_VmUltraWideSuperZoomME16by9(parent),m_VmAutofill(parent),m_VmAutozoom(parent),m_AutoFormatMode(parent),m_PicturePosMin(parent),m_PicturePosMax(parent),m_PicturePosHorizMin(parent),m_PicturePosHorizMax(parent),m_VcCvbs(parent),m_VcYc(parent),m_VcYuv(parent),m_VcRgb(parent),m_VcYPbPr(parent),m_VcYcOrCvbs(parent),m_VcRgb2Fh(parent),m_VcYPbPr2Fh(parent),m_VcYuv2Fh(parent),m_VcRgb3Fh(parent),m_VcYPbPr3Fh(parent),m_VcYuv3Fh(parent),m_ImageFormatInvalid(parent),m_ImageFormatUnknown(parent),m_ImageFormatNoImage(parent),m_ImageFormat4by3FF(parent),m_ImageFormat14by9Top(parent),m_ImageFormat14by9Center(parent),m_ImageFormat16by9Top(parent),m_ImageFormat16by9Center(parent),m_ImageFormat4by3Use14by9(parent),m_ImageFormat16by9FF(parent),m_ImageFormatMoreThan16by9Center(parent),m_ImageFormat16by9Use14by9(parent),m_ImageFormat16by9Use4by3(parent),m_VideoPresentInvalid(parent),m_VideoPresentUnknown(parent),m_VideoPresent(parent),m_VideoLost(parent),m_VideoMuteBlack(parent),m_VideoMuteBlue(parent),m_VideoMuteGrey(parent),m_VideoMuteWhite(parent),m_VideoMutePogramGrey(parent),m_VideoMuteColourMin(parent),m_VideoMuteColourMax(parent),m_SigInterlace(parent),m_SigProgressive(parent),m_SigInterlaceInvalid(parent),m_SigInterlaceUnknown(parent),m_SigInterlaceOneOne(parent),m_SigInterlaceTwoOne(parent),m_SigInterlaceFourTwo(parent),m_AbsPicPosVerticalMin(parent),m_AbsPicPosVerticalMax(parent),m_AbsPicPosHorizMin(parent),m_AbsPicPosHorizMax(parent),m_UnKnown(parent),m_IgnoreValue(parent),m_ResetValue(parent) \
    {\
        m_parent = parent;\
    }\
virtual void Set(int property,int value){ return m_parent->intf ## _Set(property,value);}\
virtual int Get(int property){ return m_parent->intf ## _Get(property);}\
virtual void Set2(int property,int value1,int value2){ return m_parent->intf ## _Set2(property,value1,value2);}\
virtual void Set3(int property,int value1,int value2){ return m_parent->intf ## _Set3(property,value1,value2);}\
virtual Bool IsAvailable(int property,int value){ return m_parent->intf ## _IsAvailable(property,value);}\
virtual Bool IsControllable(int property,int value){ return m_parent->intf ## _IsControllable(property,value);}\
virtual int Freeze(void){ return m_Freeze.Call();}\
virtual int Pan(void){ return m_Pan.Call();}\
virtual int ViewMode(void){ return m_ViewMode.Call();}\
virtual int SeamlessViewMode(void){ return m_SeamlessViewMode.Call();}\
virtual int PicturePos(void){ return m_PicturePos.Call();}\
virtual int PicturePosHoriz(void){ return m_PicturePosHoriz.Call();}\
virtual int VideoCoding(void){ return m_VideoCoding.Call();}\
virtual int VideoCodingAux(void){ return m_VideoCodingAux.Call();}\
virtual int ImageFormat(void){ return m_ImageFormat.Call();}\
virtual int AutoFormat(void){ return m_AutoFormat.Call();}\
virtual int VideoMuteAux(void){ return m_VideoMuteAux.Call();}\
virtual int VideoMuteScart2Out(void){ return m_VideoMuteScart2Out.Call();}\
virtual int VideoPresenceMain(void){ return m_VideoPresenceMain.Call();}\
virtual int VideoPresenceAux(void){ return m_VideoPresenceAux.Call();}\
virtual int IncomingFrameLinesMain(void){ return m_IncomingFrameLinesMain.Call();}\
virtual int IncomingVisibleFieldLinesMain(void){ return m_IncomingVisibleFieldLinesMain.Call();}\
virtual int IncomingSignalInterlaceMain(void){ return m_IncomingSignalInterlaceMain.Call();}\
virtual int IncomingFieldFrequencyMain(void){ return m_IncomingFieldFrequencyMain.Call();}\
virtual int IncomingVisiblePixels(void){ return m_IncomingVisiblePixels.Call();}\
virtual int IncomingVisiblePixelsAux(void){ return m_IncomingVisiblePixelsAux.Call();}\
virtual int IncomingFrameLinesAux(void){ return m_IncomingFrameLinesAux.Call();}\
virtual int IncomingVisibleFieldLinesAux(void){ return m_IncomingVisibleFieldLinesAux.Call();}\
virtual int IncomingSignalInterlaceAux(void){ return m_IncomingSignalInterlaceAux.Call();}\
virtual int IncomingFieldFrequencyAux(void){ return m_IncomingFieldFrequencyAux.Call();}\
virtual int AutoVideoMute(void){ return m_AutoVideoMute.Call();}\
virtual int AbsPicPosVertical(void){ return m_AbsPicPosVertical.Call();}\
virtual int AbsPicPosHoriz(void){ return m_AbsPicPosHoriz.Call();}\
virtual int VideoProtection(void){ return m_VideoProtection.Call();}\
virtual int LastItem(void){ return m_LastItem.Call();}\
virtual int FreezeOn(void){ return m_FreezeOn.Call();}\
virtual int FreezeOff(void){ return m_FreezeOff.Call();}\
virtual int PanUp(void){ return m_PanUp.Call();}\
virtual int PanDown(void){ return m_PanDown.Call();}\
virtual int PanLeft(void){ return m_PanLeft.Call();}\
virtual int PanRight(void){ return m_PanRight.Call();}\
virtual int VmNormalScreen4by3(void){ return m_VmNormalScreen4by3.Call();}\
virtual int VmMovieExpand14by9(void){ return m_VmMovieExpand14by9.Call();}\
virtual int VmMovieExpand16by9(void){ return m_VmMovieExpand16by9.Call();}\
virtual int VmSubtitleZoom(void){ return m_VmSubtitleZoom.Call();}\
virtual int VmSuperZoomMode(void){ return m_VmSuperZoomMode.Call();}\
virtual int VmWideScreen(void){ return m_VmWideScreen.Call();}\
virtual int VmMovieExpand21by9(void){ return m_VmMovieExpand21by9.Call();}\
virtual int VmNormalScreen(void){ return m_VmNormalScreen.Call();}\
virtual int VmVerticalSqueeze(void){ return m_VmVerticalSqueeze.Call();}\
virtual int VmExpand4by3(void){ return m_VmExpand4by3.Call();}\
virtual int VmPanorama(void){ return m_VmPanorama.Call();}\
virtual int VmHalfWindow(void){ return m_VmHalfWindow.Call();}\
virtual int VmHalfWindowSqueezed(void){ return m_VmHalfWindowSqueezed.Call();}\
virtual int VmHorizontalSqueeze(void){ return m_VmHorizontalSqueeze.Call();}\
virtual int VmOtherViewMode(void){ return m_VmOtherViewMode.Call();}\
virtual int VmAmoranap(void){ return m_VmAmoranap.Call();}\
virtual int VmZoomMode(void){ return m_VmZoomMode.Call();}\
virtual int VmHorizontalExpand(void){ return m_VmHorizontalExpand.Call();}\
virtual int VmPseudoPipWindow(void){ return m_VmPseudoPipWindow.Call();}\
virtual int VmPreviewWindow(void){ return m_VmPreviewWindow.Call();}\
virtual int VmNativeMode(void){ return m_VmNativeMode.Call();}\
virtual int VmHighRes(void){ return m_VmHighRes.Call();}\
virtual int VmUltraWide(void){ return m_VmUltraWide.Call();}\
virtual int VmUltraWideSubtitle(void){ return m_VmUltraWideSubtitle.Call();}\
virtual int VmUltraWide16by9(void){ return m_VmUltraWide16by9.Call();}\
virtual int VmVideoWindow(void){ return m_VmVideoWindow.Call();}\
virtual int VmUltraWideSuperZoomME16by9(void){ return m_VmUltraWideSuperZoomME16by9.Call();}\
virtual int VmAutofill(void){ return m_VmAutofill.Call();}\
virtual int VmAutozoom(void){ return m_VmAutozoom.Call();}\
virtual int AutoFormatMode(void){ return m_AutoFormatMode.Call();}\
virtual int PicturePosMin(void){ return m_PicturePosMin.Call();}\
virtual int PicturePosMax(void){ return m_PicturePosMax.Call();}\
virtual int PicturePosHorizMin(void){ return m_PicturePosHorizMin.Call();}\
virtual int PicturePosHorizMax(void){ return m_PicturePosHorizMax.Call();}\
virtual int VcCvbs(void){ return m_VcCvbs.Call();}\
virtual int VcYc(void){ return m_VcYc.Call();}\
virtual int VcYuv(void){ return m_VcYuv.Call();}\
virtual int VcRgb(void){ return m_VcRgb.Call();}\
virtual int VcYPbPr(void){ return m_VcYPbPr.Call();}\
virtual int VcYcOrCvbs(void){ return m_VcYcOrCvbs.Call();}\
virtual int VcRgb2Fh(void){ return m_VcRgb2Fh.Call();}\
virtual int VcYPbPr2Fh(void){ return m_VcYPbPr2Fh.Call();}\
virtual int VcYuv2Fh(void){ return m_VcYuv2Fh.Call();}\
virtual int VcRgb3Fh(void){ return m_VcRgb3Fh.Call();}\
virtual int VcYPbPr3Fh(void){ return m_VcYPbPr3Fh.Call();}\
virtual int VcYuv3Fh(void){ return m_VcYuv3Fh.Call();}\
virtual int ImageFormatInvalid(void){ return m_ImageFormatInvalid.Call();}\
virtual int ImageFormatUnknown(void){ return m_ImageFormatUnknown.Call();}\
virtual int ImageFormatNoImage(void){ return m_ImageFormatNoImage.Call();}\
virtual int ImageFormat4by3FF(void){ return m_ImageFormat4by3FF.Call();}\
virtual int ImageFormat14by9Top(void){ return m_ImageFormat14by9Top.Call();}\
virtual int ImageFormat14by9Center(void){ return m_ImageFormat14by9Center.Call();}\
virtual int ImageFormat16by9Top(void){ return m_ImageFormat16by9Top.Call();}\
virtual int ImageFormat16by9Center(void){ return m_ImageFormat16by9Center.Call();}\
virtual int ImageFormat4by3Use14by9(void){ return m_ImageFormat4by3Use14by9.Call();}\
virtual int ImageFormat16by9FF(void){ return m_ImageFormat16by9FF.Call();}\
virtual int ImageFormatMoreThan16by9Center(void){ return m_ImageFormatMoreThan16by9Center.Call();}\
virtual int ImageFormat16by9Use14by9(void){ return m_ImageFormat16by9Use14by9.Call();}\
virtual int ImageFormat16by9Use4by3(void){ return m_ImageFormat16by9Use4by3.Call();}\
virtual int VideoPresentInvalid(void){ return m_VideoPresentInvalid.Call();}\
virtual int VideoPresentUnknown(void){ return m_VideoPresentUnknown.Call();}\
virtual int VideoPresent(void){ return m_VideoPresent.Call();}\
virtual int VideoLost(void){ return m_VideoLost.Call();}\
virtual int VideoMuteBlack(void){ return m_VideoMuteBlack.Call();}\
virtual int VideoMuteBlue(void){ return m_VideoMuteBlue.Call();}\
virtual int VideoMuteGrey(void){ return m_VideoMuteGrey.Call();}\
virtual int VideoMuteWhite(void){ return m_VideoMuteWhite.Call();}\
virtual int VideoMutePogramGrey(void){ return m_VideoMutePogramGrey.Call();}\
virtual int VideoMuteColourMin(void){ return m_VideoMuteColourMin.Call();}\
virtual int VideoMuteColourMax(void){ return m_VideoMuteColourMax.Call();}\
virtual int SigInterlace(void){ return m_SigInterlace.Call();}\
virtual int SigProgressive(void){ return m_SigProgressive.Call();}\
virtual int SigInterlaceInvalid(void){ return m_SigInterlaceInvalid.Call();}\
virtual int SigInterlaceUnknown(void){ return m_SigInterlaceUnknown.Call();}\
virtual int SigInterlaceOneOne(void){ return m_SigInterlaceOneOne.Call();}\
virtual int SigInterlaceTwoOne(void){ return m_SigInterlaceTwoOne.Call();}\
virtual int SigInterlaceFourTwo(void){ return m_SigInterlaceFourTwo.Call();}\
virtual int AbsPicPosVerticalMin(void){ return m_AbsPicPosVerticalMin.Call();}\
virtual int AbsPicPosVerticalMax(void){ return m_AbsPicPosVerticalMax.Call();}\
virtual int AbsPicPosHorizMin(void){ return m_AbsPicPosHorizMin.Call();}\
virtual int AbsPicPosHorizMax(void){ return m_AbsPicPosHorizMax.Call();}\
virtual int UnKnown(void){ return m_UnKnown.Call();}\
virtual int IgnoreValue(void){ return m_IgnoreValue.Call();}\
virtual int ResetValue(void){ return m_ResetValue.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
