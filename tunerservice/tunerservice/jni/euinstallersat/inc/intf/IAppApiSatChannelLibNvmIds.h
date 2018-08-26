#ifndef IAPPAPISATCHANNELLIBNVMIDS_H
#define IAPPAPISATCHANNELLIBNVMIDS_H
#include <intfparam.h>
#include <provreq.h>
class IAppApiSatChannelLibNvmIds
{
public:
	virtual ~IAppApiSatChannelLibNvmIds(){}
	virtual NvmId InstSettingsInstallMode(void)= 0;
	virtual NvmId LastPresetType(void)= 0;
	virtual NvmId LastPresetlPtc(void)= 0;
	virtual NvmId LastPresetOnePartNo(void)= 0;
	virtual NvmId LastPresetAnalogNo(void)= 0;
	virtual NvmId LastPresetDigit(void)= 0;
	virtual NvmId LastPresetTwoPartMajorNo(void)= 0;
	virtual NvmId LastPresetTwoPartMinorNo(void)= 0;
	virtual NvmId LastSource(void)= 0;
	virtual NvmId LstStatParentalRatingAge(void)= 0;
	virtual NvmId LstStatParentalRatingDrugs(void)= 0;
	virtual NvmId LstStatParentalRatingViolence(void)= 0;
	virtual NvmId LstStatParentalRatingSex(void)= 0;
	virtual NvmId InstSettingsClosedCaptions(void)= 0;
	virtual NvmId InstSettingsSubtitle(void)= 0;
	virtual NvmId LstStatDVBParentalRating(void)= 0;
};


#define IAppApiSatChannelLibNvmIdsImpl(Comp,intf)    \
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
friend class InterfaceParam<Comp,NvmId>;\
class Comp ## _ ## intf : public IAppApiSatChannelLibNvmIds \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,NvmId> m_InstSettingsInstallMode; \
    InterfaceParam<Comp,NvmId> m_LastPresetType; \
    InterfaceParam<Comp,NvmId> m_LastPresetlPtc; \
    InterfaceParam<Comp,NvmId> m_LastPresetOnePartNo; \
    InterfaceParam<Comp,NvmId> m_LastPresetAnalogNo; \
    InterfaceParam<Comp,NvmId> m_LastPresetDigit; \
    InterfaceParam<Comp,NvmId> m_LastPresetTwoPartMajorNo; \
    InterfaceParam<Comp,NvmId> m_LastPresetTwoPartMinorNo; \
    InterfaceParam<Comp,NvmId> m_LastSource; \
    InterfaceParam<Comp,NvmId> m_LstStatParentalRatingAge; \
    InterfaceParam<Comp,NvmId> m_LstStatParentalRatingDrugs; \
    InterfaceParam<Comp,NvmId> m_LstStatParentalRatingViolence; \
    InterfaceParam<Comp,NvmId> m_LstStatParentalRatingSex; \
    InterfaceParam<Comp,NvmId> m_InstSettingsClosedCaptions; \
    InterfaceParam<Comp,NvmId> m_InstSettingsSubtitle; \
    InterfaceParam<Comp,NvmId> m_LstStatDVBParentalRating; \
    Comp ## _ ## intf( Comp *parent):m_InstSettingsInstallMode(parent),m_LastPresetType(parent),m_LastPresetlPtc(parent),m_LastPresetOnePartNo(parent),m_LastPresetAnalogNo(parent),m_LastPresetDigit(parent),m_LastPresetTwoPartMajorNo(parent),m_LastPresetTwoPartMinorNo(parent),m_LastSource(parent),m_LstStatParentalRatingAge(parent),m_LstStatParentalRatingDrugs(parent),m_LstStatParentalRatingViolence(parent),m_LstStatParentalRatingSex(parent),m_InstSettingsClosedCaptions(parent),m_InstSettingsSubtitle(parent),m_LstStatDVBParentalRating(parent) \
    {\
        m_parent = parent;\
    }\
virtual NvmId InstSettingsInstallMode(void){ return m_InstSettingsInstallMode.Call();}\
virtual NvmId LastPresetType(void){ return m_LastPresetType.Call();}\
virtual NvmId LastPresetlPtc(void){ return m_LastPresetlPtc.Call();}\
virtual NvmId LastPresetOnePartNo(void){ return m_LastPresetOnePartNo.Call();}\
virtual NvmId LastPresetAnalogNo(void){ return m_LastPresetAnalogNo.Call();}\
virtual NvmId LastPresetDigit(void){ return m_LastPresetDigit.Call();}\
virtual NvmId LastPresetTwoPartMajorNo(void){ return m_LastPresetTwoPartMajorNo.Call();}\
virtual NvmId LastPresetTwoPartMinorNo(void){ return m_LastPresetTwoPartMinorNo.Call();}\
virtual NvmId LastSource(void){ return m_LastSource.Call();}\
virtual NvmId LstStatParentalRatingAge(void){ return m_LstStatParentalRatingAge.Call();}\
virtual NvmId LstStatParentalRatingDrugs(void){ return m_LstStatParentalRatingDrugs.Call();}\
virtual NvmId LstStatParentalRatingViolence(void){ return m_LstStatParentalRatingViolence.Call();}\
virtual NvmId LstStatParentalRatingSex(void){ return m_LstStatParentalRatingSex.Call();}\
virtual NvmId InstSettingsClosedCaptions(void){ return m_InstSettingsClosedCaptions.Call();}\
virtual NvmId InstSettingsSubtitle(void){ return m_InstSettingsSubtitle.Call();}\
virtual NvmId LstStatDVBParentalRating(void){ return m_LstStatDVBParentalRating.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
