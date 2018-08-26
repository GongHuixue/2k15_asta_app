#ifndef IHSVDESCRIPTORS_H
#define IHSVDESCRIPTORS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDescriptors
{
public:
	virtual ~IHsvDescriptors(){}
	#define IHsvDescriptors_HiRate		((int)0 )
	#define IHsvDescriptors_MedRate		((int)1 )
	#define IHsvDescriptors_LowRate		((int)2 )
	#define IHsvDescriptors_ReservedSampleRate		((int)3 )
	#define IHsvDescriptors_HiOrMedRate		((int)4 )
	#define IHsvDescriptors_HiOrLowRate		((int)5 )
	#define IHsvDescriptors_MedOrLowRate		((int)6 )
	#define IHsvDescriptors_HiLowOrMedRate		((int)7 )
	#define IHsvDescriptors_Unknown		((int)0 )
	#define IHsvDescriptors_NotDolby		((int)1 )
	#define IHsvDescriptors_Dolby		((int)2 )
	#define IHsvDescriptors_ReservedSurroundMode		((int)3 )
	#define IHsvDescriptors_CodingMode0		((int)0 )
	#define IHsvDescriptors_CodingMode1		((int)1 )
	#define IHsvDescriptors_CodingMode2		((int)2 )
	#define IHsvDescriptors_CodingMode3		((int)3 )
	#define IHsvDescriptors_CodingMode4		((int)4 )
	#define IHsvDescriptors_CodingMode5		((int)5 )
	#define IHsvDescriptors_CodingMode6		((int)6 )
	#define IHsvDescriptors_CodingMode7		((int)7 )
	#define IHsvDescriptors_NumEncCh0		((int)0 )
	#define IHsvDescriptors_NumEncCh01		((int)1 )
	#define IHsvDescriptors_NumEncCh02		((int)2 )
	#define IHsvDescriptors_NumEncCh03		((int)3 )
	#define IHsvDescriptors_NumEncCh04		((int)4 )
	#define IHsvDescriptors_NumEncCh05		((int)5 )
	#define IHsvDescriptors_ReservedValueNumChannels		((int)6 )
	virtual Bool GetAc3AudioInfo(HsvDemux demux,HsvChannel channel,HsvAc3AudioInfo * ac3info)= 0;
	virtual int GetNumCaptionServices(HsvDemux demux,HsvChannel channel)= 0;
	virtual Bool GetCaptionServiceInfo(int index,HsvDemux demux,HsvChannel channel,HsvClosedCaptionInfo * ccinfo)= 0;
	virtual int GetNumEventRatingRegions(HsvDemux demux,HsvChannel channel)= 0;
	virtual Bool GetEventRatingRegionInfo(int index,HsvDemux demux,HsvChannel channel,HsvRatingRegionInfo * ratinginfo)= 0;
};


#define IHsvDescriptorsImpl(Comp,intf)    \
virtual Bool intf ## _GetAc3AudioInfo(HsvDemux demux,HsvChannel channel,HsvAc3AudioInfo * ac3info);\
virtual int intf ## _GetNumCaptionServices(HsvDemux demux,HsvChannel channel);\
virtual Bool intf ## _GetCaptionServiceInfo(int index,HsvDemux demux,HsvChannel channel,HsvClosedCaptionInfo * ccinfo);\
virtual int intf ## _GetNumEventRatingRegions(HsvDemux demux,HsvChannel channel);\
virtual Bool intf ## _GetEventRatingRegionInfo(int index,HsvDemux demux,HsvChannel channel,HsvRatingRegionInfo * ratinginfo);\
class Comp ## _ ## intf : public IHsvDescriptors \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool GetAc3AudioInfo(HsvDemux demux,HsvChannel channel,HsvAc3AudioInfo * ac3info){ return m_parent->intf ## _GetAc3AudioInfo(demux,channel,ac3info);}\
virtual int GetNumCaptionServices(HsvDemux demux,HsvChannel channel){ return m_parent->intf ## _GetNumCaptionServices(demux,channel);}\
virtual Bool GetCaptionServiceInfo(int index,HsvDemux demux,HsvChannel channel,HsvClosedCaptionInfo * ccinfo){ return m_parent->intf ## _GetCaptionServiceInfo(index,demux,channel,ccinfo);}\
virtual int GetNumEventRatingRegions(HsvDemux demux,HsvChannel channel){ return m_parent->intf ## _GetNumEventRatingRegions(demux,channel);}\
virtual Bool GetEventRatingRegionInfo(int index,HsvDemux demux,HsvChannel channel,HsvRatingRegionInfo * ratinginfo){ return m_parent->intf ## _GetEventRatingRegionInfo(index,demux,channel,ratinginfo);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
