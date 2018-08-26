#ifndef ITVVIDEOPROPERTIES3EX_H
#define ITVVIDEOPROPERTIES3EX_H
#include <intfparam.h>
#include <provreq.h>
class ITvVideoProperties3Ex
{
public:
	virtual ~ITvVideoProperties3Ex(){}
	virtual int VideoPresenceInvalid(void)= 0;
	virtual int VideoPresenceUnknown(void)= 0;
	virtual int VideoPresenceDetected(void)= 0;
	virtual int VideoPresenceNotDetected(void)= 0;
	virtual int FieldFrequencyInvalid(void)= 0;
	virtual int FieldFrequencyUnknown(void)= 0;
	virtual int NumberOfLinesInvalid(void)= 0;
	virtual int NumberOfLinesUnknown(void)= 0;
	virtual int InterlaceInvalid(void)= 0;
	virtual int InterlaceUnknown(void)= 0;
	virtual int InterlaceOneOne(void)= 0;
	virtual int InterlaceTwoOne(void)= 0;
	virtual int InterlaceFourTwo(void)= 0;
	virtual int ImageFormatInvalid(void)= 0;
	virtual int ImageFormatUnknown(void)= 0;
	virtual int ImageFormat4by3FullFormat(void)= 0;
	virtual int ImageFormat14by9Top(void)= 0;
	virtual int ImageFormat14by9Center(void)= 0;
	virtual int ImageFormat16by9Top(void)= 0;
	virtual int ImageFormat16by9Center(void)= 0;
	virtual int ImageFormat4by3Use14by9(void)= 0;
	virtual int ImageFormat16by9Use14by9(void)= 0;
	virtual int ImageFormat16by9Use4by3(void)= 0;
	virtual int ImageFormat16by9FullFormat(void)= 0;
	virtual int ImageFormatMoreThan16by9Center(void)= 0;
	virtual int VideoCodingInvalid(void)= 0;
	virtual int VideoCodingUnknown(void)= 0;
	virtual int VideoCodingCvbs(void)= 0;
	virtual int VideoCodingYc(void)= 0;
	virtual int VideoCodingYuv(void)= 0;
	virtual int VideoCodingYuv2FH(void)= 0;
	virtual int VideoCodingYuv3FH(void)= 0;
	virtual int VideoCodingRgb(void)= 0;
	virtual int VideoCodingRgb2FH(void)= 0;
	virtual int VideoCodingRgb3FH(void)= 0;
	virtual int VideoCodingYPbPr(void)= 0;
	virtual int VideoCodingYPbPr2FH(void)= 0;
	virtual int VideoCodingYPbPr3FH(void)= 0;
	virtual int GetVideoPresent(void)= 0;
	virtual int GetFieldFrequency(void)= 0;
	virtual int GetNumberOfFrameLines(void)= 0;
	virtual int GetNumberOfVisibleLines(void)= 0;
	virtual int GetNumberOfVisiblePixels(void)= 0;
	virtual int GetInterlace(void)= 0;
	virtual int GetImageFormat(void)= 0;
	virtual Bool IsFilmMode(void)= 0;
	virtual Bool IsFromVcr(void)= 0;
	virtual int GetVideoCoding(void)= 0;
	virtual int GetVideoProtection(void)= 0;
	virtual Bool IsVideoDetectionSensitivitySupported(int sensitivity)= 0;
	virtual void SetVideoDetectionSensitivity(int sensitivity)= 0;
	virtual int GetVideoDetectionSensitivity(void)= 0;
};


#define ITvVideoProperties3ExImpl(Comp,intf)    \
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
virtual int intf ## _GetVideoPresent(void);\
virtual int intf ## _GetFieldFrequency(void);\
virtual int intf ## _GetNumberOfFrameLines(void);\
virtual int intf ## _GetNumberOfVisibleLines(void);\
virtual int intf ## _GetNumberOfVisiblePixels(void);\
virtual int intf ## _GetInterlace(void);\
virtual int intf ## _GetImageFormat(void);\
virtual Bool intf ## _IsFilmMode(void);\
virtual Bool intf ## _IsFromVcr(void);\
virtual int intf ## _GetVideoCoding(void);\
virtual int intf ## _GetVideoProtection(void);\
virtual Bool intf ## _IsVideoDetectionSensitivitySupported(int sensitivity);\
virtual void intf ## _SetVideoDetectionSensitivity(int sensitivity);\
virtual int intf ## _GetVideoDetectionSensitivity(void);\
class Comp ## _ ## intf : public ITvVideoProperties3Ex \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_VideoPresenceInvalid; \
    InterfaceParam<Comp,int> m_VideoPresenceUnknown; \
    InterfaceParam<Comp,int> m_VideoPresenceDetected; \
    InterfaceParam<Comp,int> m_VideoPresenceNotDetected; \
    InterfaceParam<Comp,int> m_FieldFrequencyInvalid; \
    InterfaceParam<Comp,int> m_FieldFrequencyUnknown; \
    InterfaceParam<Comp,int> m_NumberOfLinesInvalid; \
    InterfaceParam<Comp,int> m_NumberOfLinesUnknown; \
    InterfaceParam<Comp,int> m_InterlaceInvalid; \
    InterfaceParam<Comp,int> m_InterlaceUnknown; \
    InterfaceParam<Comp,int> m_InterlaceOneOne; \
    InterfaceParam<Comp,int> m_InterlaceTwoOne; \
    InterfaceParam<Comp,int> m_InterlaceFourTwo; \
    InterfaceParam<Comp,int> m_ImageFormatInvalid; \
    InterfaceParam<Comp,int> m_ImageFormatUnknown; \
    InterfaceParam<Comp,int> m_ImageFormat4by3FullFormat; \
    InterfaceParam<Comp,int> m_ImageFormat14by9Top; \
    InterfaceParam<Comp,int> m_ImageFormat14by9Center; \
    InterfaceParam<Comp,int> m_ImageFormat16by9Top; \
    InterfaceParam<Comp,int> m_ImageFormat16by9Center; \
    InterfaceParam<Comp,int> m_ImageFormat4by3Use14by9; \
    InterfaceParam<Comp,int> m_ImageFormat16by9Use14by9; \
    InterfaceParam<Comp,int> m_ImageFormat16by9Use4by3; \
    InterfaceParam<Comp,int> m_ImageFormat16by9FullFormat; \
    InterfaceParam<Comp,int> m_ImageFormatMoreThan16by9Center; \
    InterfaceParam<Comp,int> m_VideoCodingInvalid; \
    InterfaceParam<Comp,int> m_VideoCodingUnknown; \
    InterfaceParam<Comp,int> m_VideoCodingCvbs; \
    InterfaceParam<Comp,int> m_VideoCodingYc; \
    InterfaceParam<Comp,int> m_VideoCodingYuv; \
    InterfaceParam<Comp,int> m_VideoCodingYuv2FH; \
    InterfaceParam<Comp,int> m_VideoCodingYuv3FH; \
    InterfaceParam<Comp,int> m_VideoCodingRgb; \
    InterfaceParam<Comp,int> m_VideoCodingRgb2FH; \
    InterfaceParam<Comp,int> m_VideoCodingRgb3FH; \
    InterfaceParam<Comp,int> m_VideoCodingYPbPr; \
    InterfaceParam<Comp,int> m_VideoCodingYPbPr2FH; \
    InterfaceParam<Comp,int> m_VideoCodingYPbPr3FH; \
    Comp ## _ ## intf( Comp *parent):m_VideoPresenceInvalid(parent),m_VideoPresenceUnknown(parent),m_VideoPresenceDetected(parent),m_VideoPresenceNotDetected(parent),m_FieldFrequencyInvalid(parent),m_FieldFrequencyUnknown(parent),m_NumberOfLinesInvalid(parent),m_NumberOfLinesUnknown(parent),m_InterlaceInvalid(parent),m_InterlaceUnknown(parent),m_InterlaceOneOne(parent),m_InterlaceTwoOne(parent),m_InterlaceFourTwo(parent),m_ImageFormatInvalid(parent),m_ImageFormatUnknown(parent),m_ImageFormat4by3FullFormat(parent),m_ImageFormat14by9Top(parent),m_ImageFormat14by9Center(parent),m_ImageFormat16by9Top(parent),m_ImageFormat16by9Center(parent),m_ImageFormat4by3Use14by9(parent),m_ImageFormat16by9Use14by9(parent),m_ImageFormat16by9Use4by3(parent),m_ImageFormat16by9FullFormat(parent),m_ImageFormatMoreThan16by9Center(parent),m_VideoCodingInvalid(parent),m_VideoCodingUnknown(parent),m_VideoCodingCvbs(parent),m_VideoCodingYc(parent),m_VideoCodingYuv(parent),m_VideoCodingYuv2FH(parent),m_VideoCodingYuv3FH(parent),m_VideoCodingRgb(parent),m_VideoCodingRgb2FH(parent),m_VideoCodingRgb3FH(parent),m_VideoCodingYPbPr(parent),m_VideoCodingYPbPr2FH(parent),m_VideoCodingYPbPr3FH(parent) \
    {\
        m_parent = parent;\
    }\
virtual int VideoPresenceInvalid(void){ return m_VideoPresenceInvalid.Call();}\
virtual int VideoPresenceUnknown(void){ return m_VideoPresenceUnknown.Call();}\
virtual int VideoPresenceDetected(void){ return m_VideoPresenceDetected.Call();}\
virtual int VideoPresenceNotDetected(void){ return m_VideoPresenceNotDetected.Call();}\
virtual int FieldFrequencyInvalid(void){ return m_FieldFrequencyInvalid.Call();}\
virtual int FieldFrequencyUnknown(void){ return m_FieldFrequencyUnknown.Call();}\
virtual int NumberOfLinesInvalid(void){ return m_NumberOfLinesInvalid.Call();}\
virtual int NumberOfLinesUnknown(void){ return m_NumberOfLinesUnknown.Call();}\
virtual int InterlaceInvalid(void){ return m_InterlaceInvalid.Call();}\
virtual int InterlaceUnknown(void){ return m_InterlaceUnknown.Call();}\
virtual int InterlaceOneOne(void){ return m_InterlaceOneOne.Call();}\
virtual int InterlaceTwoOne(void){ return m_InterlaceTwoOne.Call();}\
virtual int InterlaceFourTwo(void){ return m_InterlaceFourTwo.Call();}\
virtual int ImageFormatInvalid(void){ return m_ImageFormatInvalid.Call();}\
virtual int ImageFormatUnknown(void){ return m_ImageFormatUnknown.Call();}\
virtual int ImageFormat4by3FullFormat(void){ return m_ImageFormat4by3FullFormat.Call();}\
virtual int ImageFormat14by9Top(void){ return m_ImageFormat14by9Top.Call();}\
virtual int ImageFormat14by9Center(void){ return m_ImageFormat14by9Center.Call();}\
virtual int ImageFormat16by9Top(void){ return m_ImageFormat16by9Top.Call();}\
virtual int ImageFormat16by9Center(void){ return m_ImageFormat16by9Center.Call();}\
virtual int ImageFormat4by3Use14by9(void){ return m_ImageFormat4by3Use14by9.Call();}\
virtual int ImageFormat16by9Use14by9(void){ return m_ImageFormat16by9Use14by9.Call();}\
virtual int ImageFormat16by9Use4by3(void){ return m_ImageFormat16by9Use4by3.Call();}\
virtual int ImageFormat16by9FullFormat(void){ return m_ImageFormat16by9FullFormat.Call();}\
virtual int ImageFormatMoreThan16by9Center(void){ return m_ImageFormatMoreThan16by9Center.Call();}\
virtual int VideoCodingInvalid(void){ return m_VideoCodingInvalid.Call();}\
virtual int VideoCodingUnknown(void){ return m_VideoCodingUnknown.Call();}\
virtual int VideoCodingCvbs(void){ return m_VideoCodingCvbs.Call();}\
virtual int VideoCodingYc(void){ return m_VideoCodingYc.Call();}\
virtual int VideoCodingYuv(void){ return m_VideoCodingYuv.Call();}\
virtual int VideoCodingYuv2FH(void){ return m_VideoCodingYuv2FH.Call();}\
virtual int VideoCodingYuv3FH(void){ return m_VideoCodingYuv3FH.Call();}\
virtual int VideoCodingRgb(void){ return m_VideoCodingRgb.Call();}\
virtual int VideoCodingRgb2FH(void){ return m_VideoCodingRgb2FH.Call();}\
virtual int VideoCodingRgb3FH(void){ return m_VideoCodingRgb3FH.Call();}\
virtual int VideoCodingYPbPr(void){ return m_VideoCodingYPbPr.Call();}\
virtual int VideoCodingYPbPr2FH(void){ return m_VideoCodingYPbPr2FH.Call();}\
virtual int VideoCodingYPbPr3FH(void){ return m_VideoCodingYPbPr3FH.Call();}\
virtual int GetVideoPresent(void){ return m_parent->intf ## _GetVideoPresent();}\
virtual int GetFieldFrequency(void){ return m_parent->intf ## _GetFieldFrequency();}\
virtual int GetNumberOfFrameLines(void){ return m_parent->intf ## _GetNumberOfFrameLines();}\
virtual int GetNumberOfVisibleLines(void){ return m_parent->intf ## _GetNumberOfVisibleLines();}\
virtual int GetNumberOfVisiblePixels(void){ return m_parent->intf ## _GetNumberOfVisiblePixels();}\
virtual int GetInterlace(void){ return m_parent->intf ## _GetInterlace();}\
virtual int GetImageFormat(void){ return m_parent->intf ## _GetImageFormat();}\
virtual Bool IsFilmMode(void){ return m_parent->intf ## _IsFilmMode();}\
virtual Bool IsFromVcr(void){ return m_parent->intf ## _IsFromVcr();}\
virtual int GetVideoCoding(void){ return m_parent->intf ## _GetVideoCoding();}\
virtual int GetVideoProtection(void){ return m_parent->intf ## _GetVideoProtection();}\
virtual Bool IsVideoDetectionSensitivitySupported(int sensitivity){ return m_parent->intf ## _IsVideoDetectionSensitivitySupported(sensitivity);}\
virtual void SetVideoDetectionSensitivity(int sensitivity){ return m_parent->intf ## _SetVideoDetectionSensitivity(sensitivity);}\
virtual int GetVideoDetectionSensitivity(void){ return m_parent->intf ## _GetVideoDetectionSensitivity();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
