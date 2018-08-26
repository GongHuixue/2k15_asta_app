#ifndef ITVCOLORDECODE2_H
#define ITVCOLORDECODE2_H
#include <intfparam.h>
#include <provreq.h>
class ITvColorDecode2
{
public:
	virtual ~ITvColorDecode2(){}
	virtual Bool ColorSystemSupported(int colorsystem)= 0;
	virtual Bool ColorSystemSupportedEx(int colorsystem,int carrierfrequency)= 0;
	virtual void ForceColorSystem(int colorsystem)= 0;
	virtual void ForceColorSystemEx(int colorsystem,int carrierfrequency)= 0;
	virtual int GetForcedColorSystem(void)= 0;
	virtual int GetForcedCarrierFrequency(void)= 0;
	virtual void SuggestColorSystem(int colorsystem)= 0;
	virtual void SuggestColorSystemEx(int colorsystem,int carrierfrequency)= 0;
	virtual int GetSuggestedColorSystem(void)= 0;
	virtual int GetSuggestedCarrierFrequency(void)= 0;
	virtual int GetColorSystem(void)= 0;
	virtual int GetCarrierFrequency(void)= 0;
	virtual Bool CombFilterSupported(void)= 0;
	virtual void EnableCombFilter(Bool mode)= 0;
	virtual Bool CombFilterEnabled(void)= 0;
	virtual Bool CombFilterActive(void)= 0;
	virtual int UnknownColorSystem(void)= 0;
	virtual int InvalidColorSystem(void)= 0;
	virtual int Pal(void)= 0;
	virtual int Secam(void)= 0;
	virtual int Ntsc(void)= 0;
	virtual int FreqUnknown(void)= 0;
	virtual int FreqInvalid(void)= 0;
	virtual int Freq4pt433619(void)= 0;
	virtual int Freq3pt582056(void)= 0;
	virtual int Freq3pt575611(void)= 0;
	virtual int Freq3pt579545(void)= 0;
};


#define ITvColorDecode2Impl(Comp,intf)    \
virtual Bool intf ## _ColorSystemSupported(int colorsystem);\
virtual Bool intf ## _ColorSystemSupportedEx(int colorsystem,int carrierfrequency);\
virtual void intf ## _ForceColorSystem(int colorsystem);\
virtual void intf ## _ForceColorSystemEx(int colorsystem,int carrierfrequency);\
virtual int intf ## _GetForcedColorSystem(void);\
virtual int intf ## _GetForcedCarrierFrequency(void);\
virtual void intf ## _SuggestColorSystem(int colorsystem);\
virtual void intf ## _SuggestColorSystemEx(int colorsystem,int carrierfrequency);\
virtual int intf ## _GetSuggestedColorSystem(void);\
virtual int intf ## _GetSuggestedCarrierFrequency(void);\
virtual int intf ## _GetColorSystem(void);\
virtual int intf ## _GetCarrierFrequency(void);\
virtual Bool intf ## _CombFilterSupported(void);\
virtual void intf ## _EnableCombFilter(Bool mode);\
virtual Bool intf ## _CombFilterEnabled(void);\
virtual Bool intf ## _CombFilterActive(void);\
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
class Comp ## _ ## intf : public ITvColorDecode2 \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_UnknownColorSystem; \
    InterfaceParam<Comp,int> m_InvalidColorSystem; \
    InterfaceParam<Comp,int> m_Pal; \
    InterfaceParam<Comp,int> m_Secam; \
    InterfaceParam<Comp,int> m_Ntsc; \
    InterfaceParam<Comp,int> m_FreqUnknown; \
    InterfaceParam<Comp,int> m_FreqInvalid; \
    InterfaceParam<Comp,int> m_Freq4pt433619; \
    InterfaceParam<Comp,int> m_Freq3pt582056; \
    InterfaceParam<Comp,int> m_Freq3pt575611; \
    InterfaceParam<Comp,int> m_Freq3pt579545; \
    Comp ## _ ## intf( Comp *parent):m_UnknownColorSystem(parent),m_InvalidColorSystem(parent),m_Pal(parent),m_Secam(parent),m_Ntsc(parent),m_FreqUnknown(parent),m_FreqInvalid(parent),m_Freq4pt433619(parent),m_Freq3pt582056(parent),m_Freq3pt575611(parent),m_Freq3pt579545(parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool ColorSystemSupported(int colorsystem){ return m_parent->intf ## _ColorSystemSupported(colorsystem);}\
virtual Bool ColorSystemSupportedEx(int colorsystem,int carrierfrequency){ return m_parent->intf ## _ColorSystemSupportedEx(colorsystem,carrierfrequency);}\
virtual void ForceColorSystem(int colorsystem){ return m_parent->intf ## _ForceColorSystem(colorsystem);}\
virtual void ForceColorSystemEx(int colorsystem,int carrierfrequency){ return m_parent->intf ## _ForceColorSystemEx(colorsystem,carrierfrequency);}\
virtual int GetForcedColorSystem(void){ return m_parent->intf ## _GetForcedColorSystem();}\
virtual int GetForcedCarrierFrequency(void){ return m_parent->intf ## _GetForcedCarrierFrequency();}\
virtual void SuggestColorSystem(int colorsystem){ return m_parent->intf ## _SuggestColorSystem(colorsystem);}\
virtual void SuggestColorSystemEx(int colorsystem,int carrierfrequency){ return m_parent->intf ## _SuggestColorSystemEx(colorsystem,carrierfrequency);}\
virtual int GetSuggestedColorSystem(void){ return m_parent->intf ## _GetSuggestedColorSystem();}\
virtual int GetSuggestedCarrierFrequency(void){ return m_parent->intf ## _GetSuggestedCarrierFrequency();}\
virtual int GetColorSystem(void){ return m_parent->intf ## _GetColorSystem();}\
virtual int GetCarrierFrequency(void){ return m_parent->intf ## _GetCarrierFrequency();}\
virtual Bool CombFilterSupported(void){ return m_parent->intf ## _CombFilterSupported();}\
virtual void EnableCombFilter(Bool mode){ return m_parent->intf ## _EnableCombFilter(mode);}\
virtual Bool CombFilterEnabled(void){ return m_parent->intf ## _CombFilterEnabled();}\
virtual Bool CombFilterActive(void){ return m_parent->intf ## _CombFilterActive();}\
virtual int UnknownColorSystem(void){ return m_UnknownColorSystem.Call();}\
virtual int InvalidColorSystem(void){ return m_InvalidColorSystem.Call();}\
virtual int Pal(void){ return m_Pal.Call();}\
virtual int Secam(void){ return m_Secam.Call();}\
virtual int Ntsc(void){ return m_Ntsc.Call();}\
virtual int FreqUnknown(void){ return m_FreqUnknown.Call();}\
virtual int FreqInvalid(void){ return m_FreqInvalid.Call();}\
virtual int Freq4pt433619(void){ return m_Freq4pt433619.Call();}\
virtual int Freq3pt582056(void){ return m_Freq3pt582056.Call();}\
virtual int Freq3pt575611(void){ return m_Freq3pt575611.Call();}\
virtual int Freq3pt579545(void){ return m_Freq3pt579545.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
